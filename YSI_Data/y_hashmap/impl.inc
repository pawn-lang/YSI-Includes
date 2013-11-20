/**--------------------------------------------------------------------------**\
					  ====================================
					   y_hashmap - Link strings to values
					  ====================================
Description:
	Maps string indexes to integer indexes.  Uses a fast hash to get an array
	slot, then a linked list to resolve collisions.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI hashmap include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
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
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	1.0
Changelog:
	23/06/13:
		First version.
Functions:
	stock:
		HashMap_Init - Associate a hash map with an array.
		HashMap_Add - Add a value under a given string.
		HashMap_Get - Get a value from a string.
		HashMap_RemoveKey - Remove a string and its value from a hash map.
		HashMap_RemoveValue - Remove a value from a hash map.
		HashMap_Set - Change the value associated with a key.
Definitions:
	HASH_MAP_DATA - What should be added to enums to be hash map referenced.
	HashMap - Declare a new hash map.
\**--------------------------------------------------------------------------**/

#define HASH_MAP_SIZE   (256)
#define HASH_MAP_PTR    (HASH_MAP_SIZE)
#define HASH_MAP_SIZE_1 (HASH_MAP_SIZE + 1)
#define HASH_MAP_SIZE_2 (HASH_MAP_SIZE + 2)
#define HASH_MAP_SIZE_3 (HASH_MAP_SIZE + 3)

#define HashMap:%0<%1> %0[HASH_MAP_SIZE + 4]

#define HASH_MAP_DATA (2)

/**--------------------------------------------------------------------------**\
<summary>HashMap_Hash</summary>
<param name="str[]">String to hash.</param>
<param name="&hash">Desination of the hash.</param>
<returns>
	-
</returns>
<remarks>
	Quickly hashes the string using Bernstein.  Caters for both packed and
	unpacked strings.
</remarks>
\**--------------------------------------------------------------------------**/

#define HashMap_Hash(%0,%1) (%1=YHash(%0))

/**--------------------------------------------------------------------------**\
<summary>HashMap_Init</summary>
<param name="HashMap:m<>">Hash map to initialise.</param>
<param name="&target">Address of the hashmap data.</param>
<param name="size1">Number of entries.</param>
<param name="size2">Total Size of each entry IN BYTES.</param>
<param name="&t2">Address of the name AND data start.</param>
<returns>
	-
</returns>
<remarks>
	Finds the location of the hash map linked list data in the passed array data
	and uses that to read the data through pointers subsequently.  It doesn't
	matter WHERE in the enum the hash map data is, and if its not there you'll
	get an error, or at least a warning.
</remarks>
\**--------------------------------------------------------------------------**/

stock _HashMap_Init(HashMap:m<>, &target, size1, size2, &t2)
{
	static
		HashMap:sInit<> = {-1, ...};
	m = sInit;
	new
		ptr;
	// Save the pointer.
	#emit LOAD.S.pri target
	#emit STOR.S.pri ptr
	m[HASH_MAP_PTR] = ptr,
	// Store the number of elements in the array.
	m[HASH_MAP_SIZE_1] = size1,
	// Store the size of each element.
	m[HASH_MAP_SIZE_2] = size2;
	// Set up the main array.
	while (size1--)
	{
		AMX_Write(ptr, -1),
		ptr += size2;
	}
	#emit LOAD.S.pri target
	#emit LOAD.S.alt t2
	#emit SUB
	#emit STOR.S.pri ptr
	// Store the size of "_E_HASH_MAP_NAME" in bytes.
	m[HASH_MAP_SIZE_3] = ptr;
}

// Uses "%2 - %2" to make a tagged 0 without knowing the tag.
#define HashMap_Init(%0,%1,%2) _HashMap_Init(%0, %1[0][(%2)], sizeof (%1), sizeof (%1[]) * 4, %1[0][(%2) - (%2)])

/**--------------------------------------------------------------------------**\
<summary>HashMap_ByteLen</summary>
<param name="str[]">String to get the size of.</param>
<returns>
	The number of BYTES this string takes up including the NULL.
</returns>
<remarks>
	Caters for both packed and unpacked strings.  The weirdness is basically
	just: "ispacked(str) ? (* 1) : (* 4)".
</remarks>
\**--------------------------------------------------------------------------**/

#define HashMap_ByteLen(%0) ((strlen((%0)) + 1) << (2 * _:!ispacked((%0))))

/**--------------------------------------------------------------------------**\
<summary>HashMap_Add</summary>
<param name="HashMap:m<>"></param>
<param name="const str[]"></param>
<param name="const value"></param>
<returns>
	-
</returns>
<remarks>
	Adds a value to the given hash map under the given string key.
</remarks>
\**--------------------------------------------------------------------------**/

stock bool:HashMap_Add(HashMap:m<>, const str[], const value)
{
	P:3("HashMap_Add called: %d <= %d < %d", 0, value, m[HASH_MAP_SIZE_1]);
	if (0 <= value < m[HASH_MAP_SIZE_1])
	{
		new
			ptr  = m[HASH_MAP_PTR] + value * m[HASH_MAP_SIZE_2];
		P:6("HashMap_Add: used = %d", AMX_Read(ptr));
		if (AMX_Read(ptr) != -1) return false;
		static
			hash,
			mask;
		HashMap_Hash(str, hash);
		P:5("HashMap_Add: mask = %d", hash & 0xFF);
		mask = hash & 0xFF,
		// Add this hash to the hash list.
		AMX_Write(ptr, m[mask]),
		m[mask] = ptr,
		// Get the hashed string destination size.
		mask = m[HASH_MAP_SIZE_3],
		rawMemcpy(ptr - mask, ref(str), mask),
		// Copy the hashed value.
		AMX_Write(ptr + 4, hash);
		return true;
	}
	return false;
}

/**--------------------------------------------------------------------------**\
<summary>HashMap_Get</summary>
<param name="HashMap:m<>">The hash map to search.</param>
<param name="const str[]">The key to find.</param>
<returns>
	The value associated with this key in the given hash map.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

stock HashMap_Get(HashMap:m<>, const str[], bool:ignorecase = false)
{
	static
		hash,
		res;
	HashMap_Hash(str, hash);
	res = hash & 0xFF;
	P:3("HashMap_Get called: \"%s\" mask = %d", str, res);
	for (new ptr = m[res]; ptr != -1; )
	{
		#emit LOAD.S.pri  ptr
		#emit ADD.C       4
		#emit LOAD.I
		#emit STOR.pri    res
		if (res == hash)
		{
			P:6("HashMap_Get: Candidate %d: %d == %d", (ptr - m[HASH_MAP_PTR]) / m[HASH_MAP_SIZE_2], AMX_Read(ptr + 4), hash);
			// Maybe collisions.
			#emit PUSH.C      0x7FFFFFFF
			#emit PUSH.S      ignorecase
			#emit PUSH.S      str
			#emit LOAD.S.pri  m
			#emit ADD.C       1036 // 256 * 4 + 3 * 4
			#emit LOAD.I
			#emit LOAD.S.alt  ptr
			#emit SUB.alt
			#emit PUSH.pri
			#emit PUSH.C      16
			#emit SYSREQ.C    strcmp
			#emit STACK       20
			#emit STOR.pri    res
			/*new dest[32];
			static const sss[] = "str = %s";
			// printf
			#emit LOAD.S.pri  m
			#emit ADD.C       1036 // 256 * 4 + 3 * 4
			#emit LOAD.I
			#emit LOAD.S.alt  ptr
			#emit SUB.alt
			#emit PUSH.pri
			#emit PUSH.C      sss
			#emit PUSH.C      8
			#emit SYSREQ.C    printf
			#emit STACK       12
			// strunpack
			#emit PUSH.C 32
			#emit LOAD.S.pri  m
			#emit ADD.C       1036 // 256 * 4 + 3 * 4
			#emit LOAD.I
			#emit LOAD.S.alt  ptr
			#emit SUB.alt
			#emit PUSH.pri
			#emit ADDR.pri    dest
			#emit PUSH.pri
			#emit PUSH.C      12
			#emit SYSREQ.C    strunpack
			#emit STACK       16
			printf("%s = %d", dest, res);*/
			if (res == 0) return (ptr - m[HASH_MAP_PTR]) / m[HASH_MAP_SIZE_2];
		}
		{} // Zero-cost bug fix.
		#emit LREF.S.pri  ptr
		#emit STOR.S.pri  ptr
	}
	return -1;
}

/**--------------------------------------------------------------------------**\
<summary>HashMap_GetWithHash</summary>
<param name="HashMap:m<>">The hash map to search.</param>
<param name="const str[]">The key to find.</param>
<param name="hash">The hashed key.</param>
<returns>
	The value associated with this key in the given hash map.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

stock HashMap_GetWithHash(HashMap:m<>, const str[], hash, bool:ignorecase = false)
{
	static
		res;
	res = hash & 0xFF;
	P:3("HashMap_Get called: mask = %d", res);
	for (new ptr = m[res]; ptr != -1; )
	{
		#emit LOAD.S.pri  ptr
		#emit ADD.C       4
		#emit LOAD.I
		#emit STOR.pri    res
		if (res == hash)
		{
			P:6("HashMap_Get: Candidate %d: %d == %d", (ptr - m[HASH_MAP_PTR]) / m[HASH_MAP_SIZE_2], AMX_Read(ptr + 4), hash);
			// Maybe collisions.
			#emit PUSH.C      0x7FFFFFFF
			#emit PUSH.S      ignorecase
			#emit PUSH.S      str
			#emit LOAD.S.pri  m
			#emit ADD.C       1036 // 256 * 4 + 3 * 4
			#emit LOAD.I
			#emit LOAD.S.alt  ptr
			#emit SUB.alt
			#emit PUSH.pri
			#emit PUSH.C      16
			#emit SYSREQ.C    strcmp
			#emit STACK       20
			#emit STOR.pri    res
			if (res == 0) return (ptr - m[HASH_MAP_PTR]) / m[HASH_MAP_SIZE_2];
		}
		{} // Zero-cost bug fix.
		#emit LREF.S.pri  ptr
		#emit STOR.S.pri  ptr
	}
	return -1;
}

/**--------------------------------------------------------------------------**\
<summary>HashMap_RemoveKey</summary>
<param name="HashMap:m<>">The hash map to modify.</param>
<param name="const str[]">The key to remove from the hash map.</param>
<returns>
	-
</returns>
<remarks>
	Removes a given key and its associated value from the given hash map (if it
	can be found in the map in the first place).
</remarks>
\**--------------------------------------------------------------------------**/

stock bool:HashMap_RemoveKey(HashMap:m<>, const str[])
{
	static
		hash,
		res,
		prev;
	HashMap_Hash(str, hash);
	res = hash & 0xFF,
	prev = ref(m[res]);
	P:3("HashMap_RemoveKey called: mask = %d", res);
	for (new ptr = AMX_Read(prev); ptr != -1; )
	{
		#emit LOAD.S.pri  ptr
		#emit ADD.C       4
		#emit LOAD.I
		#emit STOR.pri    res
		if (res == hash)
		{
			P:6("HashMap_RemoveKey: Candidate %d: %d == %d", (ptr - m[HASH_MAP_PTR]) / m[HASH_MAP_SIZE_2], AMX_Read(ptr + 4), hash);
			// Maybe collisions.
			#emit PUSH.C      0x7FFFFFFF
			#emit PUSH.C      0
			#emit PUSH.S      str
			#emit LOAD.S.pri  m
			#emit ADD.C       1036 // 256 * 4 + 3 * 4
			#emit LOAD.I
			#emit LOAD.S.alt  ptr
			#emit SUB.alt
			#emit PUSH.pri
			#emit PUSH.C      16
			#emit SYSREQ.C    strcmp
			#emit STACK       20
			#emit STOR.pri    res
			if (res == 0)
			{
				// Remove this from the linked list.
				AMX_Write(prev, AMX_Read(ptr)),
				AMX_Write(ptr, -1),
				AMX_Write(ptr - m[HASH_MAP_SIZE_3], 0);
				return true;
			}
		}
		prev = ptr;
		#emit LREF.S.pri  ptr
		#emit STOR.S.pri  ptr
	}
	return false;
}

/**--------------------------------------------------------------------------**\
<summary>HashMap_RemoveValue</summary>
<param name="HashMap:m<>">Hash map to modify.</param>
<param name="value">Value to remove.</param>
<returns>
	-
</returns>
<remarks>
	Removes a value from the hash map.  First it gets the string key for the
	value, then removes that (to update associated linked lists correctly).
</remarks>
\**--------------------------------------------------------------------------**/

stock bool:HashMap_RemoveValue(HashMap:m<>, value)
{
	if (0 <= value < m[HASH_MAP_SIZE_1])
	{
		static
			sString[128 char];
		new
			size = m[HASH_MAP_SIZE_3];
		rawMemcpy(ref(sString), m[HASH_MAP_PTR] + value * m[HASH_MAP_SIZE_2] - size, min(size, sizeof (sString) * 4));
		return HashMap_RemoveKey(m, sString);
	}
	return false;
}

/**--------------------------------------------------------------------------**\
<summary>HashMap_Set</summary>
<param name="HashMap:m<>">The hash map to modify.</param>
<param name="const str[]">The key to modify.</param>
<param name="const value">The new value for the given key.</param>
<returns>
	-
</returns>
<remarks>
	If this key is already in the hash map it is removed, and then the new value
	is added in its place.  If the string already exists, its associated data is
	removed.  If the value already exists, it is removed as well.
</remarks>
\**--------------------------------------------------------------------------**/

stock HashMap_Set(HashMap:m<>, const str[], const value)
{
	return
		HashMap_RemoveKey(m, str),
		HashMap_RemoveValue(m, value),
		HashMap_Add(m, str, value);
}

