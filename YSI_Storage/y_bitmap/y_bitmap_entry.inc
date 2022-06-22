#if defined _INC_y_bitmap
	#endinput
#endif
#define _INC_y_bitmap

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

#include "..\..\YSI_Core\y_utils"
#include "..\..\YSI_Data\y_bit"
#include "..\..\YSI_Coding\y_malloc"
// Because having colours is always good...
#include "..\..\YSI_Server\y_colours"

#if defined YSI_MALLOC_SECURE
	#error y_bitmap does not (well) work with YSI_MALLOC_SECURE.
#endif

// Used by both `read` and write`.
stock
	_YSI_g_sFileHeader[] =
	{
		'B', 'M',   // bfType      (Just "BM" for Windows BMP).
		1, 1, 1, 1, // bfSize      (File size in bytes).
		0, 0,       // bfReserved1 (Unused).
		0, 0,       // bfReserved2 (Unused).
		2, 2, 2, 2  // bfOffBits   (Offset to the start of the data).
	},
	_YSI_g_sInfoHeader[] =
	{
		40, 0, 0, 0,  // biSize          (This header's size).
		4,  4, 4, 4,  // biWidth         (Image width).
		5,  5, 5, 5,  // biHeight        (Image height).
		1,  0,        // biPlanes        (1 "plane").
		24, 0,        // biBitCount      (24-bit image).
		0,  0, 0, 0,  // biCompression   (Unused).
		0,  0, 0, 0,  // biSizeImage     (Unused).
		0,  0, 0, 0,  // biXPelsPerMeter (Unused).
		0,  0, 0, 0,  // biYPelsPerMeter (Unused).
		0,  0, 0, 0,  // biClrUsed       (Unused).
		0,  0, 0, 0   // biClrImportant  (Unused).
	};

#include "y_bitmap_impl"
#include "y_bitmap_fonts"
#include "y_bitmap_blending"
#include "y_bitmap_subpixel"
#include "y_bitmap_patterns"
#include "y_bitmap_shapes"

#include "y_bitmap_read"
#include "y_bitmap_write"

// Hide the variables.
#define _YSI_g_sFileHeader
#define _YSI_g_sInfoHeader

#if defined YSI_TESTS
	#include "y_bitmap_tests"
#endif

