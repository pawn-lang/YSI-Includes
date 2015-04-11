/**--------------------------------------------------------------------------**\
					===========================
					Y Sever Includes - Bit Core
					===========================
Description:
	Provides functions for bit manipulation and bit arrays greater than 32bits.
	The arrays are usually bigger than required due to cell boundaries but this
	shouldn't cause a major problem (bit tests on the 101st bit of a 100 bit
	array won't return 0 for out of bounds, but the 129th will).
	
	Note that y_commands has a few optimisations which bypass the code in here
	so any modifications to bit array layouts will need to be reflected there.
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
	
	The Original Code is the YSI bit include.
	
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
	0.2
Changelog:
	21/10/12:
		Changed "Bit_Display" to print in the correct order.
	22/02/12:
		Added the "BITS" iterator.
	01/12/08:
		Rewrote most of the code to use shifts and ands not divs and mods.
	24/06/07:
		Added Bit_GetBit
	18/06/07:
		Added Bit_GetCount
	30/04/07:
		Added Bit_SetAll
	15/04/07:
		First version.
Functions:
	Public:
		-
	Core:
		-
	Stock:
		Bit_Set - Sets a slot to the given value.
		Bit_Get - Gets a slot state.
		Bit_SetAll - Sets all the slots in an array to the same thing.
		Bit_GetCount - Gets the number of 1s in a bit array.
	Static:
		-
	Inline:
		Bit_Bits - Gets the number of cells required for a bit array.
		Bit_Let - Sets a slot to 1.
		Bit_Vet - Sets a slot to 0.
		Bit_GetBits - Gets the bit at a slot unsafely.
	API:
		-
Callbacks:
	-
Definitions:
	CELLSHIFT - Number of bits that can hold "cellbits"
Enums:
	-
Macros:
	-
Tags:
	Bit - Bit array type.
Variables:
	Global:
		-
	Static:
		-
Commands:
	-
Compile options:
	-
</remarks>
\**--------------------------------------------------------------------------**/

#if defined _INC_y_bit
	#endinput
#endif
#define _INC_y_bit

#include "..\YSI_Internal\y_version"
#include "..\YSI_Core\y_debug"
#include "..\YSI_Core\y_utils"
#include "..\YSI_Core\y_cell"

// This is redefined below, don't worry.  It's like this so the function
// prototypes can use a familiar syntax.
#define BitArray:%1<%2> Bit:%1[%2]

#if cellbits == 32
	#define CELLSHIFT (5)
#else
	#if cellbits == 64
		#define CELLSHIFT (6)
	#else
		#if cellbits == 16
			#define CELLSHIFT (4)
		#else
			#error Unkown cell size
		#endif
	#endif
#endif

/**--------------------------------------------------------------------------**\
<summary>Bit_Bits</summary>
<param name="size">Number of bits required.</param>
<returns>
	Number of cells required for the bit array.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

// If this ever changes, update the size reference in y_users.
#define Bit_Bits(%1) (((%1)+cellbits-1)/cellbits)

/**--------------------------------------------------------------------------**\
<summary>Bit_Slot</summary>
<param name="value">Value to get the slot for.</param>
<returns>
	The true array slot for this value.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Bit_Slot(%1) ((_:%1)>>>CELLSHIFT)

/**--------------------------------------------------------------------------**\
<summary>Bit_Mask</summary>
<param name="value">Value to get the mask for</param>
<returns>
	The bit in the array slot to use.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Bit_Mask(%1) (Bit:(1<<((_:%1)&cellbits-1)))

/**--------------------------------------------------------------------------**\
<summary>Bit_GetBit</summary>
<param name="Bit:array[]">Array of bits.</param>
<param name="slot">Bit slot.</param>
<returns>
	State of the provided slot, 0 on fail.
</returns>
<remarks>
	Unsafe but faster for when you're sure you're within range.
</remarks>
\**--------------------------------------------------------------------------**/

#define Bit_GetBit(%1,%2) (%1[(%2)>>>CELLSHIFT]&Bit:(1<<((%2)&cellbits-1)))

/**--------------------------------------------------------------------------**\
<summary>Bit_Get</summary>
<param name="Bit:array[]">Array of bits.</param>
<param name="slot">Bit slot.</param>
<param name="size">Size of array.</param>
<returns>
	State of the provided slot, 0 on fail.
</returns>
<remarks>
	-

native Bit_Get(BitArray:array<>, slot);

</remarks>
\**--------------------------------------------------------------------------**/

#define Bit_Get(%1,%2) bool:Bit_GetBit(Bit:%1,_:%2)

/**--------------------------------------------------------------------------**\
<summary>Bit_Let</summary>
<param name="Bit:array[]">Array of bits.</param>
<param name="slot">Bit slot.</param>
<returns>
	-
</returns>
<remarks>
	Sets the slot to 1.
</remarks>
\**--------------------------------------------------------------------------**/

#define Bit_Let(%1,%2) %1[(%2)>>>CELLSHIFT]|=Bit:(1<<((%2)&cellbits-1))

/**--------------------------------------------------------------------------**\
<summary>Bit_Vet</summary>
<param name="Bit:array[]">Array of bits.</param>
<param name="slot">Bit slot.</param>
<returns>
	-
</returns>
<remarks>
	Sets the slot to 0.
</remarks>
\**--------------------------------------------------------------------------**/

#define Bit_Vet(%1,%2) %1[(%2)>>>CELLSHIFT]&=Bit:~(1<<((%2)&cellbits-1))

/**--------------------------------------------------------------------------**\
<summary>Bit_Set</summary>
<param name="Bit:array[]">Array of bits.</param>
<param name="slot">Bit slot.</param>
<param name="bool:set">State to set the slot to.</param>
<param name="size">Size of array.</param>
<returns>
	-
</returns>
<remarks>
	-

native Bit_Set(BitArray:array<>, slot, bool:set, size = sizeof (array));

</remarks>
\**--------------------------------------------------------------------------**/

stock Bit_Set(BitArray:array<>, slot, bool:set)//, size = sizeof (array))
{
	//if (slot >>> CELLSHIFT >= size) return;
	if (set) Bit_Let(array, slot);
	else Bit_Vet(array, slot);
}

/**--------------------------------------------------------------------------**\
<summary>Bit_FastSet</summary>
<param name="Bit:array[]">Array of bits.</param>
<param name="slot">Bit slot.</param>
<param name="bool:set">State to set the slot to.</param>
<param name="size">Size of array.</param>
<returns>
	-
</returns>
<remarks>
	Exactly the same as "Bit_Set", but as a macro not a function.

native Bit_FastSet(BitArray:array<>, slot, bool:set, size = sizeof (array));

</remarks>
\**--------------------------------------------------------------------------**/

#define Bit_FastSet(%0,%1,%2) ((%2)?(Bit_Let(%0,(%1))):(Bit_Vet(%0,(%1))))

/**--------------------------------------------------------------------------**\
<summary>Bit_SetAll</summary>
<param name="Bit:array[]">Array to set all values of.</param>
<param name="bool:set">Wether to set them all 0 or 1.</param>
<param name="size">Size of array.</param>
<returns>
	-
</returns>
<remarks>
	-

native Bit_SetAll(BitArray:array<>, bool:set, size = sizeof (array));

</remarks>
\**--------------------------------------------------------------------------**/

stock Bit_SetAll(BitArray:array<>, bool:set, size = sizeof (array))
{
	//new
	//	Bit:val = (set) ? (Bit:0xFFFFFFFF) : (Bit:0);
	memset(_:array, set ? 0xFFFFFFFF : 0, size);
	//for (new i = 0; i != size; ++i) array[i] = val;
}

/**--------------------------------------------------------------------------**\
<summary>Bit_GetCount</summary>
<param name="Bit:array[]">Array to count.</param>
<param name="size">Size of array.</param>
<returns>
	Number of 1s in the array.
</returns>
<remarks>
	Code from:
	http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel

native Bit_Count(BitArray:array<>, size = sizeof (array));

</remarks>
\**--------------------------------------------------------------------------**/

#define Bit_Count Bit_GetCount
stock Bit_GetCount(BitArray:array<>, size = sizeof (array))
{
	new
		count,
		v;
	for (new i = 0; i != size; ++i)
	{
		count += Cell_CountBits(array[i]);
	}
	return count;
}

stock Bit_Display(BitArray:array<>, size = sizeof (array))
{
	new
		ret[YSI_MAX_STRING],
		val;
	while (size--)
	{
		val = Cell_ReverseBits(array[size]);
		format(ret, sizeof (ret), "%016b%016b%s", val >>> 16, val & 0xFFFF, ret);
	}
	//P:7("Bit_Display called: %s, %i", ret, size);
	return ret;
}

#define bitsof(%0) (sizeof(%0)*cellbits)

stock Iter_Func@Bits(start, BitArray:data<>, size = sizeof (data))
{
	P:3("Iter_Func@Bits called: %s, %i", Bit_Display(data, size), start);
	new
		cur,
		i = Bit_Slot(++start);
	if (i == size)
	{
		return -1;
	}
	// Blank out the lowest bits to get the lowest bit not yet used.
	if ((cur = _:(data[i] & ~(Bit_Mask(start) - Bit:1))))
	{
		P:7("Iter_Func@Bits: %d %d %d %d", cur, _:data[i], start, _:~(Bit_Mask(start) - Bit:1));
		// Bits left in the current cell.
		return Cell_GetLowestBit(cur) + (i << CELLSHIFT);
	}
	while (++i != size)
	{
		if ((cur = _:data[i]))
		{
			return Cell_GetLowestBit(cur) + (i << CELLSHIFT);
		}
	}
	return -1;
}

#define iterstart@Bits -1

stock Iter_Func@Blanks(start, BitArray:data<>, size = sizeof (data))
{
	P:3("Iter_Func@Blanks called: %s, %i", Bit_Display(data), start);
	new
		cur,
		i = Bit_Slot(++start);
	if (i == size)
	{
		return -1;
	}
	if ((cur = _:(~data[i] & ~(Bit_Mask(start) - Bit:1))))
	{
		// Bits left in the current cell.
		return Cell_GetLowestBit(cur) + (i << CELLSHIFT);
	}
	while (++i != size)
	{
		if ((cur = ~_:data[i]))
		{
			return Cell_GetLowestBit(cur) + (i << CELLSHIFT);
		}
	}
	return -1;
}

#define iterstart@Blanks -1

#define bits<%1> Bit_Bits(%1) 

#undef BitArray
#define BitArray:%1<%2> Bit:%1[bits<%2>]

