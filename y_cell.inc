/**--------------------------------------------------------------------------**\
					============================
					Y Sever Includes - Cell Core
					============================
Description:
	Provides a few functions for manipulating the bits in single cells.  Note
	that this is distinct from the y_bit library.
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
	18/06/11:
		First version.
Functions:
	Public:
		-
	Core:
		-
	Stock:
		-
	Static:
		-
	Inline:
		-
	API:
		-
Callbacks:
	-
Definitions:
	-
Enums:
	-
Macros:
	-
Tags:
	-
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

#include "internal\y_version"
#include "y_utils"

stock Cell_ReverseBits(GLOBAL_TAG_TYPES:data)
{
	// Swap adjacent bits.
	data = ((data & 0b10101010101010101010101010101010) >>> 1) | ((data & 0b01010101010101010101010101010101) << 1);
	// Swap adjacent pairs.
	data = ((data & 0b11001100110011001100110011001100) >>> 2) | ((data & 0b00110011001100110011001100110011) << 2);
	// Swap adjacent nibbles.
	data = ((data & 0b11110000111100001111000011110000) >>> 4) | ((data & 0b00001111000011110000111100001111) << 4);
	// Swap all bytes.
	return (data >>> 24) | ((data & 0x00FF0000) >> 8) | ((data & 0x0000FF00) << 8) | (data << 24);
}

stock Cell_ReverseNibbles(GLOBAL_TAG_TYPES:data)
{
	// Swap adjacent nibbles.
	data = ((data & 0b11110000111100001111000011110000) >>> 4) | ((data & 0b00001111000011110000111100001111) << 4);
	// Swap all bytes.
	return (data >>> 24) | ((data & 0x00FF0000) >> 8) | ((data & 0x0000FF00) << 8) | (data << 24);
}

stock Cell_ReverseBytes(GLOBAL_TAG_TYPES:data)
{
	// Swap all bytes.
	return (data >>> 24) | ((data & 0x00FF0000) >> 8) | ((data & 0x0000FF00) << 8) | (data << 24);
}

stock Cell_CountBits(GLOBAL_TAG_TYPES:data)
{
	data = data - ((data >>> 1) & 0x55555555);
	data = (data & 0x33333333) + ((data >>> 2) & 0x33333333);
	return ((data + (data >>> 4) & 0xF0F0F0F) * 0x1010101) >>> 24;
}

stock Cell_GetLowestBit(GLOBAL_TAG_TYPES:data)
{
	static const
		scDeBruijn[] =
			{
				0,  1,  28, 2,  29, 14, 24, 3,  30, 22, 20, 15, 25, 17, 4,  8, 
				31, 27, 13, 23, 21, 19, 16, 7,  26, 12, 18, 6,  11, 5,  10, 9
			};
	// http://supertech.csail.mit.edu/papers/debruijn.pdf
	return scDeBruijn[((data & -data) * 0x077CB531) >>> 27];
}

stock Cell_GetLowestComponent(GLOBAL_TAG_TYPES:data)
{
	return data & -data;
}
