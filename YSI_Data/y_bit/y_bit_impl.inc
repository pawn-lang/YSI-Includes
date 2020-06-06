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

/*-------------------------------------------------------------------------*//**
 * <param name="size">Number of bits required.</param>
 * <returns>
 *  Number of cells required for the bit array.
 * </returns>
 *//*------------------------------------------------------------------------**/

// If this ever changes, update the size reference in y_users.
P:D(Bit_Bits(size));
#define Bit_Bits(%1) (((%1)+cellbits-1)/cellbits)

/*-------------------------------------------------------------------------*//**
 * <param name="value">Value to get the slot for.</param>
 * <returns>
 *  The true array slot for this value.
 * </returns>
 *//*------------------------------------------------------------------------**/

P:D(Bit_Slot(value));
#define Bit_Slot(%1) ((_:%1)>>>CELLSHIFT)

/*-------------------------------------------------------------------------*//**
 * <param name="value">Value to get the mask for</param>
 * <returns>
 *  The bit in the array slot to use.
 * </returns>
 *//*------------------------------------------------------------------------**/

P:D(Bit_Mask(value));
#define Bit_Mask(%1) (Bit:(1<<((_:%1)&cellbits-1)))

/*-------------------------------------------------------------------------*//**
 * <param name="array">Array of bits.</param>
 * <param name="slot">Bit slot.</param>
 * <returns>
 *  State of the provided slot, 0 on fail.
 * </returns>
 * <remarks>
 *  Unsafe but faster for when you're sure you're within range.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(bool:Bit_GetBit(BitArray:array<>,slot));
#define Bit_GetBit(%1,%2) (%1[(%2)>>>CELLSHIFT]&Bit:(1<<((%2)&cellbits-1)))

/*-------------------------------------------------------------------------*//**
 * <param name="array">Array of bits.</param>
 * <param name="slot">Bit slot.</param>
 * <param name="size">Size of array.</param>
 * <returns>
 *  State of the provided slot, 0 on fail.
 * </returns>
 * <remarks>
 *  -
 *
 * native Bit_Get(BitArray:array&lt;&gt;, slot);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(bool:Bit_Get(BitArray:array<>,slot));
#define Bit_Get(%1,%2) bool:Bit_GetBit(Bit:%1,_:%2)

/*-------------------------------------------------------------------------*//**
 * <param name="array">Array of bits.</param>
 * <param name="slot">Bit slot.</param>
 * <remarks>
 *  Sets the slot to 1.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Bit_Let(BitArray:array<>,slot));
#define Bit_Let(%1,%2) %1[(%2)>>>CELLSHIFT]|=Bit:(1<<((%2)&cellbits-1))

/*-------------------------------------------------------------------------*//**
 * <param name="array">Array of bits.</param>
 * <param name="slot">Bit slot.</param>
 * <remarks>
 *  Sets the slot to 0.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Bit_Vet(BitArray:array<>,slot));
#define Bit_Vet(%1,%2) %1[(%2)>>>CELLSHIFT]&=Bit:~(1<<((%2)&cellbits-1))

/*-------------------------------------------------------------------------*//**
 * <param name="array">Array of bits.</param>
 * <param name="slot">Bit slot.</param>
 * <param name="set">State to set the slot to.</param>
 * <param name="size">Size of array.</param>
 *//*------------------------------------------------------------------------**/

stock Bit_Set(BitArray:array<>, slot, bool:set)//, size = sizeof (array))
{
	//if (slot >>> CELLSHIFT >= size) return;
	if (set) Bit_Let(array, slot);
	else Bit_Vet(array, slot);
}

/*-------------------------------------------------------------------------*//**
 * <param name="array">Array of bits.</param>
 * <param name="slot">Bit slot.</param>
 * <param name="set">State to set the slot to.</param>
 * <param name="size">Size of array.</param>
 * <remarks>
 *  Exactly the same as "Bit_Set", but as a macro not a function.
 *
 * native Bit_FastSet(BitArray:array&lt;&gt;, slot, bool:set, size = sizeof (array));
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Bit_FastSet(BitArray:array<>,slot,bool:set,size = sizeof (array)));
#define Bit_FastSet(%0,%1,%2) ((%2)?(Bit_Let(%0,(%1))):(Bit_Vet(%0,(%1))))

/*-------------------------------------------------------------------------*//**
 * <param name="array">Array to set all values of.</param>
 * <param name="set">Wether to set them all 0 or 1.</param>
 * <param name="size">Size of array.</param>
 *//*------------------------------------------------------------------------**/

stock Bit_SetAll(BitArray:array<>, bool:set, size = sizeof (array))
{
	memset(_:array, set ? 0xFFFFFFFF : 0, size);
}

/*-------------------------------------------------------------------------*//**
 * <param name="array">Array to count.</param>
 * <param name="size">Size of array.</param>
 * <returns>
 *  Number of 1s in the array.
 * </returns>
 * <remarks>
 *  Code from:
 *  <a href="http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel" />
 *
 * native Bit_Count(BitArray:array&lt;&gt;, size = sizeof (array));
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define Bit_Count Bit_GetCount
stock Bit_GetCount(const BitArray:array<>, size = sizeof (array))
{
	new
		count = 0;
	for (new i = 0; i != size; ++i)
	{
		count += Cell_CountBits(array[i]);
	}
	return count;
}

stock Bit_Display(const BitArray:array<>, size = sizeof (array))
{
	new
		ret[YSI_MAX_STRING],
		val = 0;
	while (size--)
	{
		val = _:array[size];
		format(ret, sizeof (ret), "%s%016b%016b", ret, val >>> 16, val & 0xFFFF);
	}
	//P:7("Bit_Display called: %s, %i", ret, size);
	return ret;
}

#define bitsof(%0) (sizeof(%0)*cellbits)

stock Iter_Func@Bits(start, const BitArray:data<>, size = sizeof (data))
{
	P:3("Iter_Func@Bits called: %s, %i", Bit_Display(data, size), start);
	new
		cur = 0,
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

#define Iterator@Bits iterstart(-1)

stock Iter_Func@Blanks(start, const BitArray:data<>, size = sizeof (data))
{
	P:3("Iter_Func@Blanks called: %s, %i", Bit_Display(data, size), start);
	new
		cur = 0,
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

#define Iterator@Blanks iterstart(-1)

#define bits<%1> Bit_Bits(%1) 

#undef BitArray
#define BitArray:%1<%2> Bit:%1[bits<%2>]

