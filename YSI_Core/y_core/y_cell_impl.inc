/**
 * <library
 *   name="y_cell"
 *   version="0.2"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Provides a few functions for manipulating the bits in single cells.  Note that this is distinct from the y_bit library."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 *//** *//*
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

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_ReverseBytes(number);
 * </summary>
 * <param name="data">The number to manipulate.</param>
 * <returns>
 *   All the bytes in the input reversed.
 * </returns>
 * <remarks>
 *   1)
 *   Example: 0x12345678
 *   Becomes: 0x78563412
 *
 *   2)
 *   Example: 0x01020304
 *   Becomes: 0x04030201
 *
 *   3)
 *   Example: 0xFF00FF00
 *   Becomes: 0x00FF00FF
 * </remarks>
 *//*------------------------------------------------------------------------**/

native Cell_ReverseBytes(GLOBAL_TAG_TYPES:data) = swapchars;

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_CompressRight(GLOBAL_TAG_TYPES:x, m);
 * </summary>
 * <param name="x">The number to compress.</param>
 * <param name="m">The mask for which bits to compress.</param>
 * <returns>
 *   Selected bits from "x", shifted to be LSBs.
 * </returns>
 * <remarks>
 *   Doesn't require precomputation.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_CompressRight(GLOBAL_TAG_TYPES:x, m)
{
	// Compress the result so that all the masked bits are next to each other,
	// regardless of their value.
	// 
	// <a href="http://stackoverflow.com/questions/28282869/shift-masked-bits-to-the-lsb" />
	// Also Hackers Delight, section 7-4.
	// 
	return Cell_CompressRightPrecomputed(x, m, Cell_PrecomputeMaskPermutation(m));
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_ExpandLeft(GLOBAL_TAG_TYPES:x, m)
 * </summary>
 * <param name="x">The number to expand.</param>
 * <param name="m">The mask for which bits to expand to.</param>
 * <returns>
 *   LSBs from "x", shifted to selected bit positions.
 * </returns>
 * <remarks>
 *   Doesn't require precomputation.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_ExpandLeft(GLOBAL_TAG_TYPES:x, m)
{
	// Compress the result so that all the masked bits are next to each other,
	// regardless of their value.
	// 
	// <a href="http://stackoverflow.com/questions/28282869/shift-masked-bits-to-the-lsb" />
	// Also Hackers Delight, section 7-5 (2nd edition only, which it turns out I
	// don't have...)
	// 
	return Cell_ExpandLeftPrecomputed(x, m, Cell_PrecomputeMaskPermutation(m));
}

// `- 1` also works.
const y_utils_abs_shift = cellbits - 1;

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_Abs(GLOBAL_TAG_TYPES:x, m)
 * </summary>
 * <param name="number">The number to get the absolute value of.</param>
 * <param name="tag">The tag of the number, in case its <c>Float</c>.</param>
 * <returns>
 *   The absolute value of a number.
 * </returns>
 * <remarks>
 *   Get the absolute value of a number.  Floats just remove MSB.  For ints,
 *   multiply the whole number by the MSB shifted OR 1 (1 or -1).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_Abs(GLOBAL_TAG_TYPES:number, tag = tagof (number))
{
	Debug_Print4("Cell_Abs: %d %016x %016x %d %d %d", tag == _:tagof (Float:), number, number & cellmax, y_utils_abs_shift, number >> y_utils_abs_shift | 1, (number >> y_utils_abs_shift | 1) * number);
	return (tag == _:tagof (Float:)) ? (number & cellmax) : ((number >> y_utils_abs_shift | 1) * number);
}

/**
 * <library>y_cell</library>
 */
#if cellbits == 32
	const YSI_g_cFEs = -0x01010101; // 0xFEFEFEFE
#else
	const YSI_g_cFEs = -0x0101010101010101; // 0xFEFEFEFEFEFEFEFE
#endif

/**
 * <library>y_cell</library>
 */
#if cellbits == 32
	const YSI_g_c80s = 0x80808080;
#else
	const YSI_g_c80s = 0x8080808080808080;
#endif

/**
 * <library>y_cell</library>
 */
#if cellbits == 32
	const YSI_g_c20s = ~0x20202020;
#else
	const YSI_g_c20s = ~0x2020202020202020;
#endif

#if __COMPILER___EMIT_U
	#define Cell_GetLowestComponent(%0) \
		__emit(                         \
			LOAD.U.pri  %0             ,\
			MOVE.alt                   ,\
			NEG                        ,\
			AND                         \
		)

	#define Cell_GetLowestEmpty(%0) \
		__emit(                         \
			LOAD.U.pri  %0             ,\
			INVERT                     ,\
			MOVE.alt                   ,\
			NEG                        ,\
			AND                         \
		)
	
	#define Cell_HasZeroByte(%0) \
		(bool:__emit(                   \
			LOAD.U.pri  %0             ,\
			INVERT                     ,\
			MOVE.alt                   ,\
			INVERT                     ,\
			ADD.C       YSI_g_cFEs     ,\
			AND                        ,\
			CONST.alt   YSI_g_c80s     ,\
			AND                         \
		))
	
	#define Cell_HasSpaceByte(%0) \
		(bool:__emit(                   \
			LOAD.U.pri  %0             ,\
			CONST.alt   YSI_g_c20s     ,\
			XOR                        ,\
			MOVE.alt                   ,\
			INVERT                     ,\
			ADD.C       YSI_g_cFEs     ,\
			AND                        ,\
			CONST.alt   YSI_g_c80s     ,\
			AND                         \
		))
	#endinput
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_GetLowestComponent(number);
 * </summary>
 * <param name="data">The number to get the lowest 1 in.</param>
 * <returns>
 *   The lowest set bit.
 * </returns>
 * <remarks>
 *   Similar to Cell_GetLowestBit, but returns the bit, not the position of the
 *   bit.
 *
 *   1)
 *   Example: 0b00000000000000000000000000000001
 *   Returns: 0b00000000000000000000000000000001
 *
 *   2)
 *   Example: 0b00000000000000000000000000001000
 *   Returns: 0b00000000000000000000000000001000
 *
 *   3)
 *   Example: 0b00010001100011000011100010001000
 *   Returns: 0b00000000000000000000000000001000
 *
 *   4)
 *   Example: 0b00000000000000000000000000000000
 *   Returns: 0b00000000000000000000000000000000
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_GetLowestComponent(GLOBAL_TAG_TYPES:data)
{
	// return data & -data;
	#emit LOAD.S.pri           data
	#emit MOVE.alt
	#emit NEG
	#emit AND
	#emit RETN
	
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_GetLowestEmpty(number);
 * </summary>
 * <param name="data">The number to get the lowest 0 in.</param>
 * <returns>
 *   The lowest unset bit.
 * </returns>
 * <remarks>
 *   Like Cell_GetLowestComponent, but for 0s not 1s.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Cell_GetLowestEmpty(GLOBAL_TAG_TYPES:data)
{
	// return ~data & -~data;
	#emit LOAD.S.pri           data
	#emit INVERT
	#emit MOVE.alt
	#emit NEG
	#emit AND
	#emit RETN
	
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_HasZeroByte(number);
 * </summary>
 * <param name="data">The number to get the lowest 0 in.</param>
 * <returns>
 *   The lowest null byte.
 * </returns>
 * <remarks>
 *   Check if any of the 4 bytes are zero:
 *   https://jameshfisher.com/2017/01/24/bitwise-check-for-zero-byte/
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Cell_HasZeroByte(GLOBAL_TAG_TYPES:data)
{
	// return (data - 0x01010101) & ~data & 0x80808080;
	#emit LOAD.S.pri           data
	#emit INVERT
	#emit MOVE.alt
	#emit INVERT
	#emit ADD.C                YSI_g_cFEs
	#emit AND
	#emit CONST.alt            YSI_g_c80s
	#emit AND
	#emit RETN
	
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cell</library>
 * <summary>
 *   Cell_HasSpaceByte(number);
 * </summary>
 * <param name="data">The number to get the lowest space in.</param>
 * <returns>
 *   The lowest space byte.
 * </returns>
 * <remarks>
 *   Check if any of the 4 bytes are a space:
 *   https://jameshfisher.com/2017/01/24/bitwise-check-for-zero-byte/
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Cell_HasSpaceByte(GLOBAL_TAG_TYPES:data)
{
	// return (data - 0x01010101) & ~data & 0x80808080;
	#emit LOAD.S.pri           data
	#emit CONST.alt            YSI_g_c20s
	#emit XOR
	#emit MOVE.alt
	#emit INVERT
	#emit ADD.C                YSI_g_cFEs
	#emit AND
	#emit CONST.alt            YSI_g_c80s
	#emit AND
	#emit RETN
	
	return false;
}

