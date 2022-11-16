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

/// <p/>

// Sadly these two arrays can't be shared because they have marginally different
// values.  We could write this code to use the other array and do `+ 1`, but
// that adds a WHOLE EXTRA INSTRUCTION!  OH NOES!
static stock const
	/**
	 * <library>y_cell</library>
	 */
	YSI_g_scDeBruijn1[32] =
		{
			 0,  1, 28,  2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17,  4,  8, 
			31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18,  6, 11,  5, 10,  9
		},
	/**
	 * <library>y_cell</library>
	 */
	YSI_g_scDeBruijn2[32] =
		{
			 1,  2, 29,  3, 30, 15, 25,  4, 31, 23, 21, 16, 26, 18,  5,  9, 
			32, 28, 14, 24, 22, 20, 17,  8, 27, 13, 19,  7, 12,  6, 11, 10
		};

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_Reverse32(number);
 * </summary>
 * <param name="data">The number to manipulate.</param>
 * <returns>
 *   The lower four bytes in the input reversed.
 * </returns>
 * <remarks>
 *   1)
 *   Example: 0x1234567812345678
 *   Becomes: 0x0000000078563412
 *
 *   2)
 *   Example: 0x0000000001020304
 *   Becomes: 0x0000000004030201
 *
 *   3)
 *   Example: 0xFFFFFFFFFF00FF00
 *   Becomes: 0x0000000000FF00FF
 * </remarks>
 *//*------------------------------------------------------------------------**/

native Cell_Reverse32(GLOBAL_TAG_TYPES:data) = swapchars;

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_ReverseBits(number);
 * </summary>
 * <param name="data">The number to manipulate.</param>
 * <returns>
 *   All the bits in the input reversed.
 * </returns>
 * <remarks>
 *   1)
 *   Example: 0b11110000000000000000000000000000
 *   Becomes: 0b00000000000000000000000000001111
 *
 *   2)
 *   Example: 0b10110011100011110000111110000010
 *   Becomes: 0b01000001111100001111000111001101
 *
 *   3)
 *   Example: 0b01010101010101010101010101010101
 *   Becomes: 0b10101010101010101010101010101010
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_ReverseBits(GLOBAL_TAG_TYPES:data)
{
	// Swap adjacent bits.
	// data = ((data >>> 1) & 0b01010101010101010101010101010101) | ((data & 0b01010101010101010101010101010101) << 1);
	#emit LOAD.S.pri           data
	#emit PUSH.pri
	#emit CONST.alt            0b01010101010101010101010101010101
	#emit SHR.C.pri            1
	#emit AND
	#emit SWAP.pri
	#emit AND
	#emit SHL.C.pri            1
	#emit POP.alt
	#emit OR
	
	// Swap adjacent pairs.
	// data = ((data >>> 2) & 0b00110011001100110011001100110011) | ((data & 0b00110011001100110011001100110011) << 2);
	#emit PUSH.pri
	#emit CONST.alt            0b00110011001100110011001100110011
	#emit SHR.C.pri            2
	#emit AND
	#emit SWAP.pri
	#emit AND
	#emit SHL.C.pri            2
	#emit POP.alt
	#emit OR
	
	// Swap adjacent nibbles.
	// data = ((data >>> 4) & 0b00001111000011110000111100001111) | ((data & 0b00001111000011110000111100001111) << 4);
	#emit PUSH.pri
	#emit CONST.alt            0b00001111000011110000111100001111
	#emit SHR.C.pri            4
	#emit AND
	#emit SWAP.pri
	#emit AND
	#emit SHL.C.pri            4
	#emit POP.alt
	#emit OR

	// data = ((data & 0b11111111000000001111111100000000) >>> 8) | ((data & 0b00000000111111110000000011111111) << 8);
	// data = ((data & 0b11111111111111110000000000000000) >>> 16) | ((data & 0b00000000000000001111111111111111) << 16);
	#emit PUSH.pri
	#emit PUSH.C               4
	#emit SYSREQ.C             swapchars
	#emit STACK                8

	// return data;
	#emit RETN
	
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_ReverseNibbles(number);
 * </summary>
 * <param name="data">The number to manipulate.</param>
 * <returns>
 *   All the nibbles (4-bit chunks) in the input reversed.
 * </returns>
 * <remarks>
 *   1)
 *   Example: 0x12345678
 *   Becomes: 0x87654321
 *
 *   2)
 *   Example: 0x010F0703
 *   Becomes: 0x3070F010
 *
 *   3)
 *   Example: 0xF0F0F0F0
 *   Becomes: 0x0F0F0F0F
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_ReverseNibbles(GLOBAL_TAG_TYPES:data)
{
	#emit LOAD.S.pri           data
	
	// Swap adjacent nibbles.
	// data = ((data >>> 4) & 0b00001111000011110000111100001111) | ((data & 0b00001111000011110000111100001111) << 4);
	#emit PUSH.pri
	#emit CONST.alt            0b00001111000011110000111100001111
	#emit SHR.C.pri            4
	#emit AND
	#emit SWAP.pri
	#emit AND
	#emit SHL.C.pri            4
	#emit POP.alt
	#emit OR

	// data = ((data & 0b11111111000000001111111100000000) >>> 8) | ((data & 0b00000000111111110000000011111111) << 8);
	// data = ((data & 0b11111111111111110000000000000000) >>> 16) | ((data & 0b00000000000000001111111111111111) << 16);
	#emit PUSH.pri
	#emit PUSH.C               4
	#emit SYSREQ.C             swapchars
	#emit STACK                8

	// return data;
	#emit RETN
	
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_CountBits(number);
 * </summary>
 * <param name="data">The number to get the number of 1s in.</param>
 * <returns>
 *   The number of 1s (set bits) in the input.
 * </returns>
 * <remarks>
 *   1)
 *   Example: 0
 *   Returns: 0
 *
 *   2)
 *   Example: 1
 *   Returns: 1
 *
 *   3)
 *   Example: 0x01010101
 *   Returns: 4
 *
 *   I rewrote this in assembly just to see if I could pretty much.  I also
 *   rewrote the lookup version in assembly.  In theory it should be faster, but
 *   the marshalling of data was a little awkward.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_CountBits(GLOBAL_TAG_TYPES:data)
{
	// This function is a perfect candidate for re-writing in pure assembly.
	// data = data - ((data >>> 1) & 0x55555555);
	#emit LOAD.S.pri           data // From this point on, just use registers!
	#emit PUSH.pri
	#emit SHR.C.pri            1
	#emit CONST.alt            0x55555555
	#emit AND                  // No "AND.C" annoyingly.
	#emit POP.alt
	#emit SUB.alt
	
	// data = (data & 0x33333333) + ((data >>> 2) & 0x33333333);
	#emit PUSH.pri
	#emit SHR.C.pri            2
	#emit CONST.alt            0x33333333
	#emit AND
	#emit SWAP.pri             // Put the second half of the code on the stack.
	#emit AND                  // "alt" is already the correct value.
	#emit POP.alt
	#emit ADD
	
	// return ((data + (data >>> 4) & 0xF0F0F0F) * 0x1010101) >>> 24;
	#emit MOVE.alt
	#emit SHR.C.pri            4
	#emit ADD
	#emit CONST.alt            0xF0F0F0F
	#emit AND
	#emit SMUL.C               0x1010101
	#emit SHR.C.pri            24
	#emit RETN
	
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_GetLowestBit(number);
 * </summary>
 * <param name="data">The number to get the lowest set bit of.</param>
 * <returns>
 *   The integer position of the lowest set bit.
 * </returns>
 * <remarks>
 *   1)
 *   Example: 0b00000000000000000000000000000001
 *   Returns: 0
 *
 *   2)
 *   Example: 0b00000000000000000000000000001000
 *   Returns: 3
 *
 *   3)
 *   Example: 0b00010001100011000011100010001000
 *   Returns: 3
 *
 *   NOTE: This function returns "0" for both numbers with the "1" bit set AND
 *   the number "0", which has NO bits set.  Check that the number is valid
 *   before passing it to this function.
 *
 *   See: <a href="http://supertech.csail.mit.edu/papers/debruijn.pdf" />
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_GetLowestBit(GLOBAL_TAG_TYPES:data)
{
	// return scDeBruijn[((data & -data) * 0x077CB531) >>> 27];
	#emit LOAD.S.pri           data
	#emit MOVE.alt
	#emit NEG
	#emit AND
	#emit SMUL.C               0x077CB531
	#emit SHR.C.pri            27
	
	#emit CONST.alt            YSI_g_scDeBruijn1
	#emit LIDX
	
	#emit RETN
	
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_GetLowestBitEx(number);
 * </summary>
 * <param name="data">The number to get the lowest set bit of PLUS ONE.</param>
 * <returns>
 *   The integer position of the lowest set bit PLUS ONE.
 * </returns>
 * <remarks>
 *   This function is identical to "Cell_GetLowestBit", but gives different
 *   results for 0 and non-zero numbers.  The examples below all have a result
 *   one higher than the "Cell_GetLowestBit" function.
 *
 *   1)
 *   Example: 0b00000000000000000000000000000001
 *   Returns: 1
 *
 *   2)
 *   Example: 0b00000000000000000000000000001000
 *   Returns: 4
 *
 *   3)
 *   Example: 0b00010001100011000011100010001000
 *   Returns: 4
 *
 *   4)
 *   Example: 0
 *   Returns: 0
 *
 *   See: <a href="http://supertech.csail.mit.edu/papers/debruijn.pdf" />
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_GetLowestBitEx(GLOBAL_TAG_TYPES:data)
{
	// We load "data" in to "pri" here, so we don't do it within the "if"
	// statement.  This, combined with the "RETN" straight after, makes this
	// code as optimal as I can manage!  In fact, despite the fact that using
	// code (in this case the "if" statement) is usually less efficient.  I have
	// tweaked the main code to account for the generated code such that I
	// couldn't do better even if it was possible to use "JZER" in assembly (it
	// isn't because the offsets don't compile properly).  Additionally, because
	// if the check fails then "data" must be 0, then we also know that "pri"
	// must be 0 too, so there's no need to re-load that value as "return 0;"
	// would do.
	if (data)
	{
		// return scDeBruijn[((data & -data) * 0x077CB531) >>> 27];
		#emit MOVE.alt
		#emit NEG
		#emit AND
		#emit SMUL.C               0x077CB531
		#emit SHR.C.pri            27
		
		#emit CONST.alt            YSI_g_scDeBruijn2
		#emit LIDX
	}
	{} // Zero-cost bug fix.
	#emit RETN
	
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_CountBlanks(number);
 * </summary>
 * <param name="data">The number to get the number of 0s in.</param>
 * <returns>
 *   The number of 0s (unset bits) in the input.
 * </returns>
 * <remarks>
 *   Like Cell_CountBits, but for 0s not 1s.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_CountBlanks(GLOBAL_TAG_TYPES:data)
{
	// This function is a perfect candidate for re-writing in pure assembly.
	// data = data - ((data >>> 1) & 0x55555555);
	#emit LOAD.S.pri           data // From this point on, just use registers!
	#emit INVERT
	#emit PUSH.pri
	#emit SHR.C.pri            1
	#emit CONST.alt            0x55555555
	#emit AND                  // No "AND.C" annoyingly.
	#emit POP.alt
	#emit SUB.alt
	
	// data = (data & 0x33333333) + ((data >>> 2) & 0x33333333);
	#emit PUSH.pri
	#emit SHR.C.pri            2
	#emit CONST.alt            0x33333333
	#emit AND
	#emit SWAP.pri             // Put the second half of the code on the stack.
	#emit AND                  // "alt" is already the correct value.
	#emit POP.alt
	#emit ADD
	
	// return ((data + (data >>> 4) & 0xF0F0F0F) * 0x1010101) >>> 24;
	#emit MOVE.alt
	#emit SHR.C.pri            4
	#emit ADD
	#emit CONST.alt            0xF0F0F0F
	#emit AND
	#emit SMUL.C               0x1010101
	#emit SHR.C.pri            24
	#emit RETN
	
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_GetLowestBlank(number);
 * </summary>
 * <param name="data">The number to get the lowest unset bit of.</param>
 * <returns>
 *   The integer position of the lowest unset bit.
 * </returns>
 * <remarks>
 *   Like Cell_GetLowestBit, but for 0s not 1s.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_GetLowestBlank(GLOBAL_TAG_TYPES:data)
{
	// return scDeBruijn[((data & -data) * 0x077CB531) >>> 27];
	#emit LOAD.S.pri           data
	#emit INVERT
	#emit MOVE.alt
	#emit NEG
	#emit AND
	#emit SMUL.C               0x077CB531
	#emit SHR.C.pri            27
	
	#emit CONST.alt            YSI_g_scDeBruijn1
	#emit LIDX
	
	#emit RETN
	
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_GetLowestBlankEx(number);
 * </summary>
 * <param name="data">The number to get the lowest unset bit of PLUS ONE.</param>
 * <returns>
 *   The integer position of the lowest unset bit PLUS ONE.
 * </returns>
 * <remarks>
 *   Like Cell_GetLowestBitEx, but for 0s not 1s.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_GetLowestBlankEx(GLOBAL_TAG_TYPES:data)
{
	data = ~data;
	if (data)
	{
		#emit MOVE.alt
		#emit NEG
		#emit AND
		#emit SMUL.C               0x077CB531
		#emit SHR.C.pri            27
		
		#emit CONST.alt            YSI_g_scDeBruijn2
		#emit LIDX
	}
	{} // Zero-cost bug fix.
	#emit RETN
	
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_CompressRightPrecomputed(GLOBAL_TAG_TYPES:x, m, masks[5]);
 * </summary>
 * <param name="x">The number to compress.</param>
 * <param name="m">The mask for which bits to compress.</param>
 * <param name="masks">Precomputed constants for the compression.</param>
 * <returns>
 *   Selected bits from "x", shifted to be LSBs.
 * </returns>
 * <remarks>
 *   Very briefly, do "x &amp; m", to select certain bits, then shift those bits
 *   by various amounts so that they are consecutive:
 *
 *      x = 0b110011
 *      m = 0b011010
 *
 *      x &amp; m = 0b010010
 *
 *   From here, because the mask was three bits we know we want just those three
 *   bits in the LSBs, so the answer becomes:
 *
 *      0b000101
 *
 *   Just read this question, it has a diagram:
 *
 *   <a href="http://stackoverflow.com/questions/28282869/shift-masked-bits-to-the-lsb" />
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_CompressRightPrecomputed(GLOBAL_TAG_TYPES:x, m, const masks[5])
{
	new t = 0;
	return
		x = x & m,
		t = x & masks[0], x = x ^ t | (t >>>  1),
		t = x & masks[1], x = x ^ t | (t >>>  2),
		t = x & masks[2], x = x ^ t | (t >>>  4),
		t = x & masks[3], x = x ^ t | (t >>>  8),
		t = x & masks[4],     x ^ t | (t >>> 16);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_ExpandLeftPrecomputed(GLOBAL_TAG_TYPES:x, m, masks[5])
 * </summary>
 * <param name="x">The number to expand.</param>
 * <param name="m">The mask for which bits to expand to.</param>
 * <param name="masks">Precomputed constants for the expansion.</param>
 * <returns>
 *   LSBs from "x", shifted to selected bit positions.
 * </returns>
 * <remarks>
 *   The reverse of "Cell_CompressRightPrecomputed".  Doesn't return exactly the
 *   original number before a compression, just the original number ANDed with
 *   the mask "m".
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_ExpandLeftPrecomputed(GLOBAL_TAG_TYPES:x, m, const masks[5])
{
	new t = 0;
	return
		t = x << 16, x = (((x ^ t) & masks[4]) ^ x),
		t = x <<  8, x = (((x ^ t) & masks[3]) ^ x),
		t = x <<  4, x = (((x ^ t) & masks[2]) ^ x),
		t = x <<  2, x = (((x ^ t) & masks[1]) ^ x),
		t = x <<  1, m & (((x ^ t) & masks[0]) ^ x);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_PrecomputeMaskPermutation(m)
 * </summary>
 * <param name="m">The mask.</param>
 * <returns>
 *   Five precomputed constants to help expand or contract this mask.
 * </returns>
 * <remarks>
 *   The full maths for generalised expansion and contraction is quite complex;
 *   however, much of the inner loop relies only on the mask and not on the
 *   value being manipulated.  Given this we can do a lot of work in advance,
 *   say outside a loop, to avoid repeated calculations.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_PrecomputeMaskPermutation(m)
{
	// See also: <a href="http://www.hackersdelight.org/hdcodetxt/compress.c.txt" />
	new
		mk = ~m << 1,
		mp = 0,
		mv = 0,
		masks[5];
	// We will count 0's to right.
	for (new i = 0; i != 5; ++i)
	{
		// Parallel prefix.
		mp = mk ^ (mk <<  1),
		mp = mp ^ (mp <<  2),
		mp = mp ^ (mp <<  4),
		mp = mp ^ (mp <<  8),
		mp = mp ^ (mp << 16),
		// Bits to move.
		masks[i] = mv = mp & m,
		// Compress m.
		m = m ^ mv | (mv >>> (1 << i)),
		mk = mk & ~mp;
	}
	return masks;
}

