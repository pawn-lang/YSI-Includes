/*----------------------------------------------------------------------------*\
						================================
						 y_jaggedarray - Uneven arrays. 
						================================
Description:
	Provides code to easilly manipulate the sizes of 2d array slots.
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
	
	The Original Code is the YSI group include.
	
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
	06/10/12:
		First version
		Fixed a bug calling "rawMemset".
\*----------------------------------------------------------------------------*/

#include "internal\y_version"
#include "y_utils"
#include "y_debug"
//#include "y_rewrite"

// Helper macro so people don't need to enter all the sizes all the time.
#define _Jagged(%0) (%0),sizeof(%0),sizeof(%0[])

static stock Jagged_MovePtr(array[][], maxSize, slot, shift)
{
	new
		tmp0,
		tmp1,
		ptr;
	// Get the slot pointer.
	#emit LOAD.S.alt            array
	#emit LOAD.S.pri            slot
	#emit IDXADDR
	#emit STOR.S.pri tmp0
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
	#emit STOR.S.pri tmp1
	#emit STOR.S.pri            shift
	#emit LOAD.S.pri            ptr
	#emit SREF.S.pri            shift
	//printf("%d %d %d %d", tmp0, tmp1, shift, ptr);
	#if _DEBUG >= 7
		printf("Jagged_MovePtr: Header:");
		_Jagged_PrintHeader(array, 4, 0);
	#endif
}

/*----------------------------------------------------------------------------*\
Function:
	Jagged_ResizeOne
Params:
	array[][] - The array we want to resize a slot in.
	size1 - The number of slots in the array.
	size2 - The ORIGINAL size of every slot.
	slot - The slot to resize.
	newSize - The new size of the slot.
Return:
	-
Notes:
	The "slot" variable is usually used to hold the NEXT slot - we barely need
	the number of the current slot once we have its address.
\*----------------------------------------------------------------------------*/

stock bool:Jagged_ResizeOne(array[][], size1, size2, slot, newSize)
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
				rawMemset(slotEnd, shift, 0);
			}
			else
			{
				// Blank the end of the array.
				rawMemset(arrayEnd + shift, -shift, 0);
			}
		}
		// Do nothing if they're the same.
		return true;
	}
	P:C(else if (slot == size1) printf("Cannot alter the last slot in an array."););
	return false;
}

/*----------------------------------------------------------------------------*\
Function:
	_Jagged_Resize
Params:
	array[][] - The array we want to resize a slot in.
	size1 - The number of slots in the array.
	size2 - The ORIGINAL size of every slot.
	... - Multiple {slot, size} tuples.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

stock bool:_Jagged_Resize(array[][], size1, size2, ...)
{
	new
		num = numargs();
	// Now, as you can imagine, this requires some tricky low-level code, but
	// that is all in other functions now.
	for (new i = 3; i != num; ++i)
	{
		P:7("_Jagged_Resize: loop %d %d %d", i, getarg(i, 0), getarg(i, 1));
		Jagged_ResizeOne(array, size1, size2, getarg(i, 0), getarg(i, 1));
	}
	//#pragma unused tuples
}

#define Jagged_Resize(%0,%1) _Jagged_Resize(_Jagged(%0),%1)
#define _ALS_Jagged_Resize

/*----------------------------------------------------------------------------*\
Function:
	_Jagged_SizeOf
Params:
	array[][] - The array we want to get the size of a slot in.
	size1 - The number of slots in the array.
	size2 - The ORIGINAL size of every slot.
	slot - The slot to get the size of.
Return:
	The current size of this slot.  This is NOT a compile-time operation.
Notes:
	Returns the data in BYTES NOT CELLS.
\*----------------------------------------------------------------------------*/

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

/*----------------------------------------------------------------------------*\
Function:
	_Jagged_Address
Params:
	array[][] - The array we want to get the address of a slot in.
	size1 - The number of slots in the array.
	size2 - The ORIGINAL size of every slot.
	slot - The slot to get the address of.
Return:
	The absolute address of this slot.
Notes:
	-
\*----------------------------------------------------------------------------*/

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
			return 0;
		}

/*----------------------------------------------------------------------------*\
Function:
	_Jagged_End
Params:
	array[][] - The array we want to get the end of.
	size1 - The number of slots in the array.
	size2 - The ORIGINAL size of every slot.
Return:
	The absolute address of the end of this array.
Notes:
	-
\*----------------------------------------------------------------------------*/

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
			return 0;
		}

stock _Jagged_PrintHeader(array[][], size1, size2)
{
	#pragma unused size2
	for (new ptr, slot = 0; slot != size1; ++slot)
	{
		// Get the slot pointer.
		#emit LOAD.S.alt            array
		#emit LOAD.S.pri            slot
		#emit IDXADDR
		//#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri            ptr
		printf("Array header: %d = %d", slot, ptr);
	}
}
