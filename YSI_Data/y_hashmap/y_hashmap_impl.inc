/*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (c) 2022
	the Initial Developer. All Rights Reserved.

Contributors:
	Y_Less
	koolk
	JoeBullet/Google63
	g_aSlice/Slice
	Misiur
	samphunter
	tianmeta
	maddinat0r
	spacemud
	Crayder
	Dayvison
	Ahmad45123
	Zeex
	irinel1996
	Yiin-
	Chaprnks
	Konstantinos
	Masterchen09
	Southclaws
	PatchwerkQWER
	m0k1
	paulommu
	udan111
	Cheaterman

Thanks:
	JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
	ZeeX - Very productive conversations.
	koolk - IsPlayerinAreaEx code.
	TheAlpha - Danish translation.
	breadfish - German translation.
	Fireburn - Dutch translation.
	yom - French translation.
	50p - Polish translation.
	Zamaroht - Spanish translation.
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

#define HASH_MAP_SIZE   (256)
#define HASH_MAP_PTR    (HASH_MAP_SIZE)
#define HASH_MAP_SIZE_1 (HASH_MAP_SIZE + 1)
#define HASH_MAP_SIZE_2 (HASH_MAP_SIZE + 2)
#define HASH_MAP_SIZE_3 (HASH_MAP_SIZE + 3)
#define HASH_MAP_UNUSED (HASH_MAP_SIZE + 4)

#define HashMap:%0<%1> %0[HASH_MAP_SIZE + 5]

#define HASH_MAP_DIR_LEFT  (4)
#define HASH_MAP_DIR_RIGHT (8)

// There are three pieces of hash map data associated with each stored string.
// In byte offsets, these are:
//  
//  0 - The hash of the stored string.
//  4 - The left pointer for the binary tree.
//  8 - The right pointer for the binary tree.
//  
#define HASH_MAP_DATA (3)

/*-------------------------------------------------------------------------*//**
 * <param name="str">String to hash.</param>
 * <param name="hash">Desination of the hash.</param>
 * <remarks>
 *  Quickly hashes the string using Bernstein.  Caters for both packed and
 *  unpacked strings.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(HashMap_Hash(str[],&hash));
#define HashMap_Hash(%0,%1) (%1=YHash(%0))

/*-------------------------------------------------------------------------*//**
 * <param name="m">Hash map to initialise.</param>
 * <param name="target">Array to point in to.</param>
 * <param name="slot">Second dimension slot of the hashed data.</param>
 * <remarks>
 *  Finds the location of the hash map linked list data in the passed array data
 *  and uses that to read the data through pointers subsequently.  It doesn't
 *  matter WHERE in the enum the hash map data is, and if its not there you'll
 *  get an error, or at least a warning.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(HashMap_Init(HashMap:m<>, target[][], slot));

/*-------------------------------------------------------------------------*//**
 * <param name="m">Hash map to initialise.</param>
 * <param name="target">Address of the hashmap data.</param>
 * <param name="size1">Number of entries.</param>
 * <param name="size2">Total Size of each entry IN BYTES.</param>
 * <param name="t2">Address of the name AND data start.</param>
 * <remarks>
 *  Finds the location of the hash map linked list data in the passed array data
 *  and uses that to read the data through pointers subsequently.  It doesn't
 *  matter WHERE in the enum the hash map data is, and if its not there you'll
 *  get an error, or at least a warning.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock _HashMap_Init(HashMap:m<>, &target, size1, size2, &t2)
{
	static
		HashMap:sInit<> = {0, ...};
	m = sInit;
	new
		ptr = 0;
	// Save the pointer.
	#emit LOAD.S.pri target
	#emit STOR.S.pri ptr
	m[HASH_MAP_UNUSED] = ptr,
	m[HASH_MAP_PTR] = ptr,
	// Store the number of elements in the array.
	m[HASH_MAP_SIZE_1] = size1,
	// Store the size of each element.
	m[HASH_MAP_SIZE_2] = size2;
	// Store the size of "_E_HASH_MAP_NAME" in bytes.
	#emit LOAD.S.pri target
	#emit LOAD.S.alt t2
	#emit SUB
	#emit STOR.S.pri ptr
	m[HASH_MAP_SIZE_3] = ptr;
	// Using the hash for the list (in "target"), pointing to the hash of the
	// next element; initialise the whole hash map in to a linked list of unused
	// elements.
	while (--size1)
	{
		// Increment "target" by "size2".
		#emit LOAD.S.alt target
		#emit LOAD.S.pri size2
		#emit ADD
		#emit STOR.I
		#emit STOR.S.pri target
	}
	// End the list.
	target = 0;
}

// Uses "%2 - %2" to make a tagged 0 without knowing the tag.
#define HashMap_Init(%0,%1,%2) _HashMap_Init(%0, %1[0][(%2)], sizeof (%1), sizeof (%1[]) * cellbytes, %1[0][(%2) - (%2)])

/*-------------------------------------------------------------------------*//**
 * <param name="m">Hash map to get a free slot in.</param>
 * <returns>
 *   The index of a currently unused slot.
 * </returns>
 * <remarks>
 *   This assumes that you correct use <c>GetUnused</c> and <c>AddUnused</c> in
 *   pairs.  If your code has a different way of tracking unused slots, don't
 *   try and mix that with this!
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock HashMap_GetUnused(HashMap:m<>)
{
	new
		ptr = m[HASH_MAP_UNUSED];
	if (ptr)
	{
		// Get the next slot.
		#emit LOAD.S.pri m
		#emit ADD.C      1040 // (256 + 4) * 4
		#emit MOVE.alt
		#emit LREF.S.pri ptr
		#emit STOR.I
		return (ptr - m[HASH_MAP_PTR]) / m[HASH_MAP_SIZE_2];
	}
	return -1;
}
/*-------------------------------------------------------------------------*//**
 * <param name="m">Hash map to get a free slot in.</param>
 * <returns>
 *   The index of a currently unused slot.
 * </returns>
 * <remarks>
 *   This assumes that you correct use <c>GetUnused</c> and <c>AddUnused</c> in
 *   pairs.  If your code has a different way of tracking unused slots, don't
 *   try and mix that with this!
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock HashMap_AddUnused(HashMap:m<>, value)
{
	if (0 <= value < m[HASH_MAP_SIZE_1])
	{
		// Convert the index to a pointer.
		value = value * m[HASH_MAP_SIZE_2] + m[HASH_MAP_PTR];
		#emit LOAD.S.pri m
		#emit ADD.C      1040 // (256 + 4) * 4
		#emit MOVE.alt
		// Store the current value of "m[HASH_MAP_UNUSED]" in "*value".
		#emit LOAD.I
		#emit SREF.S.pri value
		// Set "m[HASH_MAP_UNUSED]" to "value"
		#emit LOAD.S.pri value
		#emit STOR.I
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">String to get the size of.</param>
 * <returns>
 *  The number of BYTES this string takes up including the NULL.
 * </returns>
 * <remarks>
 *  Caters for both packed and unpacked strings.  The weirdness is basically
 *  just: <code>ispacked(str) ? (* 1) : (* 4)</code>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(HashMap_ByteLen(str[]));
#define HashMap_ByteLen(%0) ((strlen((%0)) + 1) << (2 * _:!ispacked((%0))))

/*-------------------------------------------------------------------------*//**
 * <param name="ignorecase"></param>
 * <param name="hash"></param>
 * <param name="m"></param>
 * <param name="str"></param>
 * <param name="value">More like the target slot.</param>
 * <remarks>
 *  Adds a value to the given hash map under the given string key.
 *
 *  Actually more like adding an index, not a value...
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:HashMap_AddWithHash(HashMap:m<>, const str[], hash, value, bool:ignorecase = false)
{
	P:3("HashMap_Add called: %d <= %d < %d", 0, value, m[HASH_MAP_SIZE_1]);
	if (0 <= value < m[HASH_MAP_SIZE_1])
	{
		// Check if the index is already in a hash map.  Doesn't work if the
		// entry is a leaf, since it will be a member, but also have both
		// pointers as 0...  I don't think there is a nice way to do this.
		// if (AMX_Read(ptr + 4) || AMX_Read(ptr + 8)) return false;
		static
			ptr = 0,
			res = 0;
		// Add this entry to the correct binary tree.
		P:5("HashMap_Add: mask = %d", hash & 0xFF);
		new
			prev = AMX_Ref(m[hash & 0xFF]),
			next = 0;
		for ( ; ; )
		{
			#emit LREF.S.pri  prev
			#emit STOR.S.pri  next
			if (!next)
				break;
			{}
			#emit LREF.S.pri  next
			#emit STOR.pri    res
			if (hash == res)
			{
				// It doesn't matter which way we go on matching hashes, as long
				// as the direction is consistent.
				#emit PUSH.C      0x7FFFFFFF
				#emit PUSH.S      ignorecase
				#emit PUSH.S      str
				#emit LOAD.S.pri  m
				#emit ADD.C       1036 // 256 * 4 + 3 * 4
				#emit LOAD.I
				#emit LOAD.S.alt  next
				#emit SUB.alt
				#emit PUSH.pri
				#emit PUSH.C      16
				#emit SYSREQ.C    strcmp
				#emit STACK       20
				#emit STOR.pri    ptr
				if (ptr == 0)
				{
					P:E("Trying to add two copies of a string to a hashmap: \"%s\", %d", str, value);
					return false;
				}
				else if (ptr < 0) // Lower, move left.
					prev = next + HASH_MAP_DIR_LEFT;
				else // Higher, move right.
					prev = next + HASH_MAP_DIR_RIGHT;
			}
			else if (hash < res) // Lower, move left.
				prev = next + HASH_MAP_DIR_LEFT;
			else // Higher, move right.
				prev = next + HASH_MAP_DIR_RIGHT;
		}
		P:6("HashMap_Add: used = %d", AMX_Read(m[HASH_MAP_PTR] + value * m[HASH_MAP_SIZE_2]));
		// Get the address of this structure.
		ptr = m[HASH_MAP_PTR] + value * m[HASH_MAP_SIZE_2],
		// Copy the hashed value.
		AMX_Write(ptr, hash),
		AMX_Write(ptr + HASH_MAP_DIR_LEFT, 0),
		AMX_Write(ptr + HASH_MAP_DIR_RIGHT, 0),
		// Add this hash to the hash list.
		AMX_Write(prev, ptr),
		// Get the hashed string destination size, and copy the string.
		next = m[HASH_MAP_SIZE_3],
		RawMemCpy(ptr - next, AMX_Ref(str[0]), next);
		return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="ignorecase"></param>
 * <param name="m"></param>
 * <param name="str"></param>
 * <param name="value">More like the target slot.</param>
 * <remarks>
 *  Adds a value to the given hash map under the given string key.
 *
 *  Actually more like adding an index, not a value...
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:HashMap_Add(HashMap:m<>, const str[], value, bool:ignorecase = false)
{
	return HashMap_AddWithHash(m, str, YHash(str, .sensitive = !ignorecase), value, ignorecase);
}

/*-------------------------------------------------------------------------*//**
 * <param name="m">The hash map to search.</param>
 * <param name="str">The key to find.</param>
 * <returns>
 *  Does this hash map contain the given value?
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:HashMap_Has(HashMap:m<>, const str[], bool:ignorecase = false)
{
	return HashMap_GetWithHash(m, str, YHash(str, .sensitive = !ignorecase), ignorecase) != -1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="m">The hash map to search.</param>
 * <param name="str">The key to find.</param>
 * <param name="hash">The hashed key.</param>
 * <returns>
 *  Does this hash map contain the given value?
 * </returns>
 *//*------------------------------------------------------------------------**/

stock bool:HashMap_HasWithHash(HashMap:m<>, const str[], hash, bool:ignorecase = false)
{
	return HashMap_GetWithHash(m, str, hash, ignorecase) != -1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="m">The hash map to search.</param>
 * <param name="str">The key to find.</param>
 * <returns>
 *  The value associated with this key in the given hash map.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock HashMap_Get(HashMap:m<>, const str[], bool:ignorecase = false)
{
	return HashMap_GetWithHash(m, str, YHash(str, .sensitive = !ignorecase), ignorecase);
}

/*-------------------------------------------------------------------------*//**
 * <param name="m">The hash map to search.</param>
 * <param name="str">The key to find.</param>
 * <param name="hash">The hashed key.</param>
 * <returns>
 *  The value associated with this key in the given hash map.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock HashMap_GetWithHash(HashMap:m<>, const str[], hash, bool:ignorecase = false)
{
	P:3("HashMap_Get called: mask = %d (%d)", hash, hash & 0xFF);
	new
		prev = AMX_Ref(m[hash & 0xFF]),
		next = 0;
	static
		res = 0;
	for ( ; ; )
	{
		#emit LREF.S.pri  prev
		#emit STOR.S.pri  next
		if (!next)
			break;
		{}
		#emit LREF.S.pri  next
		#emit STOR.pri    res
		if (hash == res)
		{
			// It doesn't matter which way we go on matching hashes, as long
			// as the direction is consistent.
			#emit PUSH.C      0x7FFFFFFF
			#emit PUSH.S      ignorecase
			#emit PUSH.S      str
			#emit LOAD.S.pri  m
			#emit ADD.C       1036 // 256 * 4 + 3 * 4
			#emit LOAD.I
			#emit LOAD.S.alt  next
			#emit SUB.alt
			#emit PUSH.pri
			#emit PUSH.C      16
			#emit SYSREQ.C    strcmp
			#emit STACK       20
			#emit STOR.pri    res
			if (res == 0)
			{
				return (next - m[HASH_MAP_PTR]) / m[HASH_MAP_SIZE_2];
			}
			else if (res < 0) // Lower, move left.
				prev = next + HASH_MAP_DIR_LEFT;
			else // Higher, move right.
				prev = next + HASH_MAP_DIR_RIGHT;
		}
		else if (hash < res) // Lower, move left.
			prev = next + HASH_MAP_DIR_LEFT;
		else // Higher, move right.
			prev = next + HASH_MAP_DIR_RIGHT;
	}
	return -1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="m">The hash map to modify.</param>
 * <param name="str">The key to remove from the hash map.</param>
 * <remarks>
 *  Removes a given key and its associated value from the given hash map (if it
 *  can be found in the map in the first place).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:HashMap_RemoveKeyWithHash(HashMap:m<>, const str[], hash, bool:ignorecase = false)
{
	// First, find the key and it's parent.
	new
		prev = AMX_Ref(m[hash & 0xFF]),
		next = 0;
	static
		res = 0;
	// First, find this key in the hashmap.
	for ( ; ; )
	{
		#emit LREF.S.pri  prev
		#emit STOR.S.pri  next
		if (!next)
			return false;
		{}
		#emit LREF.S.pri  next
		#emit STOR.pri    res
		if (hash == res)
		{
			// It doesn't matter which way we go on matching hashes, as long
			// as the direction is consistent.
			#emit PUSH.C      0x7FFFFFFF
			#emit PUSH.S      ignorecase
			#emit PUSH.S      str
			#emit LOAD.S.pri  m
			#emit ADD.C       1036 // 256 * 4 + 3 * 4
			#emit LOAD.I
			#emit LOAD.S.alt  next
			#emit SUB.alt
			#emit PUSH.pri
			#emit PUSH.C      16
			#emit SYSREQ.C    strcmp
			#emit STACK       20
			#emit STOR.pri    res
			if (res == 0)
			{
				break;
			}
			else if (res < 0) // Lower, move left.
				prev = next + HASH_MAP_DIR_LEFT;
			else // Higher, move right.
				prev = next + HASH_MAP_DIR_RIGHT;
		}
		else if (hash < res) // Lower, move left.
			prev = next + HASH_MAP_DIR_LEFT;
		else // Higher, move right.
			prev = next + HASH_MAP_DIR_RIGHT;
	}
	// The LEFT/RIGHT apparent swap below is correct.  We want the right-most
	// value on the left branch, and vice-versa.
	new
		left = AMX_Read(next + HASH_MAP_DIR_LEFT),
		right = AMX_Read(next + HASH_MAP_DIR_RIGHT);
	// Find an empty branch, or the smallest branch.
	if (!left)
	{
		if (!right)
			AMX_Write(prev, 0);
		else
			AMX_Write(prev, right);
	}
	else if (!right)
	{
		AMX_Write(prev, left);
	}
	else
	{
		new
			lHeight = 1,
			rHeight = 1,
			lParent = 0,
			rParent = 0,
			lVal = HashMap_GetBranchEnd(left, lHeight, lParent, HASH_MAP_DIR_RIGHT),
			rVal = HashMap_GetBranchEnd(right, rHeight, rParent, HASH_MAP_DIR_LEFT);
		if (lHeight < rHeight)
		{
			// Reduce the right (larger) branch.  If this branch is bigger, and
			// no branch is empty, then this branch MUST be at least two nodes
			// high, and so MUST have a parent.
			AMX_Write(prev, rVal),
			rHeight = AMX_Read(rVal + HASH_MAP_DIR_RIGHT),
			AMX_Write(rParent + HASH_MAP_DIR_LEFT, rHeight),
			AMX_Write(rVal + HASH_MAP_DIR_RIGHT, right),
			AMX_Write(rVal + HASH_MAP_DIR_LEFT, left);
		}
		else if (lParent)
		{
			// Reduce the left (larger) branch.  This branch MAY NOT have a
			// parent, if both branches are equal at one node high.
			AMX_Write(prev, lVal),
			lHeight = AMX_Read(lVal + HASH_MAP_DIR_LEFT),
			AMX_Write(lParent + HASH_MAP_DIR_RIGHT, lHeight),
			AMX_Write(lVal + HASH_MAP_DIR_RIGHT, right),
			AMX_Write(lVal + HASH_MAP_DIR_LEFT, left);
		}
		else
		{
			// This branch doesn't have a parent, if both branches are equal at
			// one node high.
			AMX_Write(prev, lVal),
			AMX_Write(lVal + HASH_MAP_DIR_RIGHT, right);
		}
	}
	// Clear the removed node's pointers and string.
	AMX_Write(next + HASH_MAP_DIR_LEFT, 0),
	AMX_Write(next + HASH_MAP_DIR_RIGHT, 0),
	AMX_Write(next - m[HASH_MAP_SIZE_3], 0);
	return true;
}

stock bool:HashMap_RemoveKey(HashMap:m<>, const str[], bool:ignorecase = false)
{
	return HashMap_RemoveKeyWithHash(m, str, YHash(str, .sensitive = !ignorecase), ignorecase);
}

static stock HashMap_GetBranchEnd(cur, &height, &parent, dir)
{
	// Find the node as close in (hash) value to the current node as possible.
	for (new next = 0; (next = AMX_Read(cur + dir)); ++height, parent = cur, cur = next)
	{
	}
	return cur;
}

/*-------------------------------------------------------------------------*//**
 * <param name="m">Hash map to modify.</param>
 * <param name="value">Value to remove.</param>
 * <remarks>
 *  Removes a value from the hash map.  First it gets the string key for the
 *  value, then removes that (to update associated linked lists correctly).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:HashMap_RemoveValue(HashMap:m<>, value)
{
	if (0 <= value < m[HASH_MAP_SIZE_1])
	{
		static
			sString[128 char];
		new
			size = m[HASH_MAP_SIZE_3];
		RawMemCpy(AMX_Ref(sString[0]), m[HASH_MAP_PTR] + value * m[HASH_MAP_SIZE_2] - size, min(size, sizeof (sString) * 4));
		return HashMap_RemoveKey(m, sString);
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="m">The hash map to modify.</param>
 * <param name="str">The key to modify.</param>
 * <param name="value">The new value for the given key.</param>
 * <remarks>
 *  If this key is already in the hash map it is removed, and then the new value
 *  is added in its place.  If the string already exists, its associated data is
 *  removed.  If the value already exists, it is removed as well.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock HashMap_Set(HashMap:m<>, const str[], const value)
{
	new
		hash = YHash(str, .sensitive = true);
	return
		HashMap_RemoveKeyWithHash(m, str, hash),
		HashMap_RemoveValue(m, value),
		HashMap_AddWithHash(m, str, hash, value);
}

