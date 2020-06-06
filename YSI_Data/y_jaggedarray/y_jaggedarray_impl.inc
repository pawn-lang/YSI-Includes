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
	Portions created by the Initial Developer are Copyright C 2011
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

// Helper macro so people don't need to enter all the sizes all the time.
#define _Jagged(%0) (%0),sizeof(%0),sizeof(%0[])
#define _Jagged_Sum:(%0,%1) _Jagged_Sum:(%0+%1)

// Ceiling division so that all slots will be at least big enough.  Otherwise
//   
//   Jagged:X[3]<12, 1 1>
//   
// Would result in "[3][4]", which doesn't have 14 slots total.
#define Jagged:%0[%1]<%2>; %0[%1][_:_Jagged_Sum:(%2,%1,-1) / (%1)];Jagged_ResizeAll(%0,%2);

static stock Jagged_MovePtr(array[][], maxSize, slot, shift)
{
	new
		//tmp0,
		//tmp1,
		ptr = 0;
	// Get the slot pointer.
	#emit LOAD.S.alt            array
	#emit LOAD.S.pri            slot
	#emit IDXADDR
	//#emit STOR.S.pri tmp0
	//#emit MOVE.alt
	#emit LOAD.I
	#emit STOR.S.pri            ptr
	//printf("Jagged_MovePtr: Moving %d by %d to %d (mod %d)", ptr, shift, ptr + shift, maxSize);
	ptr += shift;
	// I have to do it this way to avoid a bug with "if" statements and "#emit".
	ptr = (ptr > maxSize) ? maxSize : ptr;
	#emit LOAD.S.alt            array
	#emit LOAD.S.pri            slot
	#emit IDXADDR
	//#emit STOR.S.pri tmp1
	#emit STOR.S.pri            shift
	#emit LOAD.S.pri            ptr
	#emit SREF.S.pri            shift
	//printf("%d %d %d %d", tmp0, tmp1, shift, ptr);
	#if _DEBUG >= 7
		printf("Jagged_MovePtr: Header:");
		_Jagged_PrintHeader(array, 4, 0);
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <param name="array">The array we want to resize a slot in.</param>
 * <param name="size1">The number of slots in the array.</param>
 * <param name="size2">The ORIGINAL size of every slot.</param>
 * <param name="slot">The slot to resize.</param>
 * <param name="newSize">The new size of the slot.</param>
 * <remarks>
 *  Resize an array slot, maintining all of its data.  The "slot" variable is
 *  usually used to hold the NEXT slot - we barely need the number of the
 *  current slot once we have its address.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:_Jagged_ResizeOne(array[][], size1, size2, slot, newSize)
{
	if (newSize < 0)
	{
		return false;
	}
	// SLOT GETS INCREMENTED VERY FAST!
	if (0 < ++slot < size1)
	{
		// Get the slot's current size and address.
		newSize *= 4;
		new
			newEnd = _Jagged_Address(array, slot - 1) + newSize,
			arrayEnd = _Jagged_End(array, size1, size2);
		if (newEnd > arrayEnd)
		{
			P:1("Insufficient space to grow jagged array.");
			return false;
		}
		new
			slotEnd = _Jagged_Address(array, slot),
			//oldSize = slotEnd - slotStart,
			shift = newEnd - slotEnd; //newSize - oldSize;
		P:5("Jagged_ResizeOne: Resizing slot %d from %d to %d", slot - 1, _Jagged_SizeOf(array, size1, size2, slot - 1), newSize);
		if (shift != 0)
		{
			new
				remain = arrayEnd - newEnd;
			// Grow the slot.  This has to be done largely in assembly to remove
			// the "BOUNDS" OpCodes that would otherwise be inserted.  Actually,
			// we can't have "BOUNDS" here because there's no way for the
			// compiler to know the array's size in advance.  This works even
			// when "shift" is negative.
			memcpy(array[slot][shift / 4], array[slot], 0, remain, remain / 4);
			// Now shift all the subsequent slots.
			size2 = size2 * size1 * 4;
			while (slot < size1)
			{
				Jagged_MovePtr(array, size2 + (size1 - slot) * 4, slot, shift);
				++slot;
			}
			if (shift > 0)
			{
				// Blank the remainder of the slot we are growing.
				rawMemset(slotEnd, 0, shift);
			}
			else
			{
				// Blank the end of the array.
				rawMemset(arrayEnd + shift, 0, -shift);
			}
		}
		// Do nothing if they're the same.
		return true;
	}
	P:C(else if (slot == size1) printf("Cannot alter the last slot in an array."););
	return false;
}
#define Jagged_ResizeOne(%0,%1) _Jagged_ResizeOne(_Jagged(%0),%1)

/*-------------------------------------------------------------------------*//**
 * <param name="array">The array we want to resize a slot in.</param>
 * <param name="size1">The number of slots in the array.</param>
 * <param name="size2">The ORIGINAL size of every slot.</param>
 * <param name="">Multiple {slot, size} tuples.</param>
 * <remarks>
 *  Resize multiple array slots, maintining all of their data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:_Jagged_Resize(array[][], size1, size2, ...)
{
	new
		num = numargs();
	// Now, as you can imagine, this requires some tricky low-level code, but
	// that is all in other functions now.
	for (new i = 3; i != num; ++i)
	{
		P:7("_Jagged_Resize: loop %d %d %d", i, getarg(i, 0), getarg(i, 1));
		if (!_Jagged_ResizeOne(array, size1, size2, getarg(i, 0), getarg(i, 1)))
			return false;
	}
	return true;
}

#define Jagged_Resize(%0,%1) _Jagged_Resize(_Jagged(%0),%1)
#define _ALS_Jagged_Resize

/*-------------------------------------------------------------------------*//**
 * <param name="array">The array we want to resize a slot in.</param>
 * <param name="size1">The number of slots in the array.</param>
 * <param name="size2">The ORIGINAL size of every slot.</param>
 * <param name="">New sizes for every slot.</param>
 * <remarks>
 *  Resize multilpe array slots, maintining all of their data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:_Jagged_ResizeAll(array[][], size1, size2, ...)
{
	new
		num = min(numargs() - 3, size1);
	// Now, as you can imagine, this requires some tricky low-level code, but
	// that is all in other functions now.
	for (new i = 3, j = 0; j != num; ++i, ++j)
	{
		P:7("_Jagged_Resize: loop %d %d %d", i, j, getarg(i));
		_Jagged_ResizeOne(array, size1, size2, j, getarg(i));
	}
}

#define Jagged_ResizeAll(%0,%1) _Jagged_ResizeAll(_Jagged(%0),%1)
#define _ALS_Jagged_ResizeAll

/*-------------------------------------------------------------------------*//**
 * <param name="array">The array we want to resize a slot in.</param>
 * <param name="size1">The number of slots in the array.</param>
 * <param name="size2">The ORIGINAL size of every slot.</param>
 * <param name="slot">The slot to resize.</param>
 * <param name="newSize">The new size of the slot.</param>
 * <remarks>
 *  The "slot" variable is usually used to hold the NEXT slot - we barely need
 *  the number of the current slot once we have its address.  "Resize" copies
 *  data to keep as much of the original data as possible.  This just moves the
 *  boundaries.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Jagged_MoveOne(array[][], size1, size2, slot, newSize)
{
	if (newSize < 0)
	{
		return false;
	}
	// SLOT GETS INCREMENTED VERY FAST!
	if (0 < ++slot < size1)
	{
		// Get the slot's current size and address.
		newSize *= 4;
		new
			newEnd = _Jagged_Address(array, slot - 1) + newSize,
			arrayEnd = _Jagged_End(array, size1, size2);
		if (newEnd > arrayEnd)
		{
			P:1("Insufficient space to grow jagged array.");
			return false;
		}
		new
			slotEnd = _Jagged_Address(array, slot),
			shift = newEnd - slotEnd;
		P:5("Jagged_MoveOne: Mov slot %d from %d to %d", slot - 1, _Jagged_SizeOf(array, size1, size2, slot - 1), newSize);
		if (shift != 0)
		{
			// Shift all the subsequent slots.
			size2 = size2 * size1 * 4;
			while (slot < size1)
			{
				Jagged_MovePtr(array, size2 + (size1 - slot) * 4, slot, shift);
				++slot;
			}
		}
		// Do nothing if they're the same.
		return true;
	}
	P:C(else if (slot == size1) printf("Cannot alter the last slot in an array."););
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="array">The array we want to resize a slot in.</param>
 * <param name="size1">The number of slots in the array.</param>
 * <param name="size2">The ORIGINAL size of every slot.</param>
 * <param name="">Multiple {slot, size} tuples.</param>
 * <remarks>
 *  "Resize" copies data to keep as much of the original data as possible.  This
 *  just moves the boundaries.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:_Jagged_Move(array[][], size1, size2, ...)
{
	new
		num = numargs();
	// Now, as you can imagine, this requires some tricky low-level code, but
	// that is all in other functions now.
	for (new i = 3; i != num; ++i)
	{
		P:7("_Jagged_Move: loop %d %d %d", i, getarg(i, 0), getarg(i, 1));
		Jagged_MoveOne(array, size1, size2, getarg(i, 0), getarg(i, 1));
	}
}

#define Jagged_Move(%0,%1) _Jagged_Move(_Jagged(%0),%1)
#define _ALS_Jagged_Move

/*-------------------------------------------------------------------------*//**
 * <param name="array">The array we want to resize a slot in.</param>
 * <param name="size1">The number of slots in the array.</param>
 * <param name="size2">The ORIGINAL size of every slot.</param>
 * <remarks>
 *   Changes all pointers except the first one to point at the very end of the
 *   array.  I.e. makes <c>sizeof (array[0]) == sizeof (array) * sizeof
 *   (array[])</c>
 *   and <c>sizeof (array[n &gt; 0]) == 0</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock _Jagged_Empty(array[][], size1, size2)
{
	// The size of the main storage area, including the header.
	size2 = (size1 + size1 * size2) * cellbytes;
	while (--size1)
	{
		#emit LOAD.S.pri array
		#emit ADD.C      4
		#emit MOVE.alt
		#emit LOAD.S.pri size2
		#emit ADD.C      0xFFFFFFFC // -4
		#emit STOR.I
		#emit STOR.S.pri size2
		#emit STOR.S.alt array
	}
}

#define Jagged_Empty(%0) _Jagged_Empty(_Jagged(%0))
#define _ALS_Jagged_Empty

/*-------------------------------------------------------------------------*//**
 * <param name="array">The array we want to resize a slot in.</param>
 * <param name="slot">The slot we want to resize.</param>
 * <param name="newSize">The new size of the slot.</param>
 * <remarks>
 *   This purely moves the next pointer in the array.  It does nothing at all
 *   with any data stored in the array, or any other pointers.  This means many
 *   bad things can happen when it is used incorrectly.  Just one example is
 *   that extending a slot over the next few slots will mean those later slots
 *   will now point in to the middle of the current slot's data.  This is best
 *   used in conjunction with Jagged_Empty, so that the array is an almost blank
 *   slate before dangerous messing.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Jagged_UnsafeResizeOne(array[][], slot, newSize)
{
	// Get a pointer to the next slot.
	#emit LOAD.S.alt array
	#emit LOAD.S.pri slot
	#emit INC.I
	#emit IDXADDR
	#emit PUSH.pri
	// Get the offset to this array's current start point.
	#emit LOAD.S.pri slot
	#emit LIDX
	// Get the offset to the new end.
	#emit LOAD.S.alt newSize
	#emit XCHG
	#emit IDXADDR
	// Subtract 4 to make it the offset for the next slot, save it to the
	// pointer we pushed earlier.
	#emit ADD.C 0xFFFFFFFC
	#emit SREF.S.pri 0xFFFFFFFC
	// End.
	#emit POP.pri
	#emit RETN
	
	__pragma(naked);
}

//#define Jagged_UnsafeResizeOne(%0,%1) _Jagged_UnsafeResizeOne(_Jagged(%0),%1)
//#define _ALS_Jagged_UnsafeResizeOne

/*-------------------------------------------------------------------------*//**
 * <param name="array">The array we want to resize a slot in.</param>
 * <param name="size1">The number of slots in the array.</param>
 * <param name="size2">The ORIGINAL size of every slot.</param>
 * <param name="">New sizes for every slot.</param>
 * <remarks>
 *  "Resize" copies data to keep as much of the original data as possible.  This
 *  just moves the boundaries.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:_Jagged_MoveAll(array[][], size1, size2, ...)
{
	new
		num = min(numargs() - 3, size1);
	// Now, as you can imagine, this requires some tricky low-level code, but
	// that is all in other functions now.
	for (new i = 3, j = 0; j != num; ++i, ++j)
	{
		P:7("_Jagged_Move: loop %d %d %d", i, j, getarg(i));
		Jagged_MoveOne(array, size1, size2, j, getarg(i));
	}
}

#define Jagged_MoveAll(%0,%1) _Jagged_MoveAll(_Jagged(%0),%1)
#define _ALS_Jagged_MoveAll

/*-------------------------------------------------------------------------*//**
 * <param name="array">The array we want to get the size of a slot in.</param>
 * <param name="size1">The number of slots in the array.</param>
 * <param name="size2">The ORIGINAL size of every slot.</param>
 * <param name="slot">The slot to get the size of.</param>
 * <returns>
 *  The current size of this slot.  This is NOT a compile-time operation.
 * </returns>
 * <remarks>
 *  Returns the data in BYTES NOT CELLS.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock _Jagged_SizeOf(array[][], size1, size2, slot)
{
	if (0 <= slot < size1)
	{
		new
			start = _Jagged_Address(array, slot);
		if (++slot == size1)
		{
			// Figure out the end address of the array.
			return _Jagged_End(array, size1, size2) - start;
		}
		else
		{
			return _Jagged_Address(array, slot) - start;
		}
	}
	return -1;
}

#define Jagged_SizeOf(%0,%1) _Jagged_SizeOf(_Jagged(%0),%1)
#define _ALS_Jagged_SizeOf

#define jaggedsizeof(%0[%1]) (_Jagged_SizeOf(_Jagged(%0),%1)>>2)

/*-------------------------------------------------------------------------*//**
 * <param name="array">The array we want to get the address of a slot in.</param>
 * <param name="size1">The number of slots in the array.</param>
 * <param name="size2">The ORIGINAL size of every slot.</param>
 * <param name="slot">The slot to get the address of.</param>
 * <returns>
 *  The absolute address of this slot.
 * </returns>
 *//*------------------------------------------------------------------------**/

#if _DEBUG == 0
	static
#endif
		stock _Jagged_Address(array[][], slot)
		{
			// Get the slot pointer.
			#emit LOAD.S.alt            array
			#emit LOAD.S.pri            slot
			#emit IDXADDR
			#emit MOVE.alt
			#emit LOAD.I
			#emit ADD
			#emit RETN
			
			__pragma(naked);
		}

/*-------------------------------------------------------------------------*//**
 * <param name="array">The array we want to get the end of.</param>
 * <param name="size1">The number of slots in the array.</param>
 * <param name="size2">The ORIGINAL size of every slot.</param>
 * <returns>
 *  The absolute address of the end of this array.
 * </returns>
 *//*------------------------------------------------------------------------**/

#if _DEBUG == 0
	static
#endif
		stock _Jagged_End(array[][], size1, size2)
		{
			#emit LOAD.S.alt            size2
			#emit INC.alt
			#emit LOAD.S.pri            size1
			#emit UMUL
			#emit LOAD.S.alt            array
			#emit IDXADDR
			#emit RETN
			
			__pragma(naked);
		}

stock _Jagged_PrintHeader(array[][], size1, size2)
{
	#pragma unused size2
	for (new ptr = 0, slot = 0; slot != size1; ++slot)
	{
		// Get the slot pointer.
		#emit LOAD.S.alt                array
		#emit LOAD.S.pri                slot
		#emit LIDX
		#emit PUSH.pri
		// Get the relative offset.
		#emit LOAD.S.pri                slot
		#emit LOAD.S.alt                size1
		#emit SUB.alt
		#emit SHL.C.pri                 2
		// Adjust the output to absolute.
		#emit POP.alt
		#emit SUB.alt
		// #emit LOAD.S.alt                array
		// #emit ADD
		#emit STOR.S.pri                ptr
		printf("Array header: %d = %d", slot, ptr);
	}
}

#define Jagged_PrintHeader(%0) _Jagged_PrintHeader(_Jagged(%0))
#define _ALS_Jagged_PrintHeader

