/**--------------------------------------------------------------------------**\
					=================================
					   y_bitmap - Generate bitmaps.
					=================================
Description:
	Code to generate images on the server in the bitmap format.  This is by far
	the simplest format to write to as it is just a huge array of colours (at
	least 24-bit bitmaps are, and we only do them).
	
	This file combines a colour with alpha on to the pixel already at the given
	location.
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
	
	The Original Code is the YSI utils include.
	
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
	0.1
Changelog:
	29/03/13:
		First version.
Functions:
	Stock:
		-
	Inline:
		-
Variables:
	Global:
		-
\**--------------------------------------------------------------------------**/

stock Bitmap_WritePixel(Bitmap:ctx, const x, const y, const colour)
{
	new
		a = colour & 0xFF;
	switch (a)
	{
		case 0: return;
		case 0xFF: Bitmap_WriteCtx(ctx, x, y, colour);
		default:
		{
			new
				r = ((colour & 0xFF000000) >>> 8) * a,
				g = ((colour & 0x00FF0000) >>> 8) * a,
				b = ((colour & 0x0000FF00) >>> 8) * a,
				oc = Bitmap_ReadCtx(ctx, x, y);
			a = 256 - a;
			oc =
				((((oc & 0xFF000000) >>> 8) * a + r) & 0xFF000000) |
				((((oc & 0x00FF0000) >>> 8) * a + g) & 0x00FF0000) |
				((((oc & 0x0000FF00) >>> 8) * a + b) & 0x0000FF00) ;
			Bitmap_WriteCtx(ctx, x, y, oc);
		}
	}
}
