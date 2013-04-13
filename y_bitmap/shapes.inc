/**--------------------------------------------------------------------------**\
					=================================
					   y_bitmap - Generate bitmaps.
					=================================
Description:
	Code to generate images on the server in the bitmap format.  This is by far
	the simplest format to write to as it is just a huge array of colours (at
	least 24-bit bitmaps are, and we only do them).
	
	This file contains functions to draw various shapes.
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

/**--------------------------------------------------------------------------**\
<summary>Bitmap_DrawRectangle</summary>
<param name="Bitmap:ctx">The bitmap to modify.</param>
<param name="const minX">The left of the array.</param>
<param name="const minY">The top of the array.</param>
<param name="const maxX">The right of the array.</param>
<param name="const maxY">The bottom of the array.</param>
<param name="fillColour">The colour of the inside of the rectangle.</param>
<param name="lineColour = 0">The colour of the rectangle border.</param>
<param name="linePattern[] = \"SOLID\"">How to draw the inside.</param>
<param name="fillPattern[] = \"SOLID\"">How to draw the border.</param>
<returns>
	-
</returns>
<remarks>
	This function draws a rectangle between two given co-ordinates.  It can also
	draw a border around the rectangle OUTSIDE the specified area of the
	rectangle.  If you want the border within the area specified you need to use
	a smaller area.
</remarks>
\**--------------------------------------------------------------------------**/

// End the input above because all this code is being written with no testing
// or compiling until I am home again.  So in the interests of leaving the code
// stable, this is all ignored.
stock Bitmap_DrawRectangle(Bitmap:ctx, const minX, const minY, const maxX, const maxY, fillColour, lineColour = 0, linePattern[] = "SOLID", fillPattern[] = "SOLID")
{
	if (fillColour)
	{
		_Bitmap_DoRectangle(ctx, minX, minY, maxX, maxY, fillColour, fillPattern);
	}
	if (lineColour)
	{
		// Do the borders.
		if (strcmp(linePattern, "DOTTED", true, 6))
		{
			new
				border = _Bitmap_Param(linePattern, "border");
			if (border == cellmin) border = 8;
			//printf("border = %d", border);
			//printf("1");
			_Bitmap_DoRectangle(ctx, minX - border, minY - border, maxX + border, minY, lineColour, linePattern),
			//printf("1");
			_Bitmap_DoRectangle(ctx, minX - border, minY, minX, maxY, lineColour, linePattern),
			//printf("1");
			_Bitmap_DoRectangle(ctx, minX - border, maxY, maxX + border, maxY + border, lineColour, linePattern),
			//printf("1");
			_Bitmap_DoRectangle(ctx, maxX, minY, maxX + border, maxY, lineColour, linePattern);
			//printf("1");
		}
		else
		{
			new
				border = _Bitmap_Param(linePattern, "border"),
				pat[128] = "STRIPED";
			strcat(pat, linePattern[6]);
			if (border == cellmin) border = 8;
			_Bitmap_DoRectangle(ctx, minX - border, minY - border, maxX + border, minY, lineColour, pat),
			_Bitmap_DoRectangle(ctx, minX - border, maxY, maxX + border, maxY + border, lineColour, pat),
			strcat(pat, ",HORIZONTAL"),
			_Bitmap_DoRectangle(ctx, minX - border, minY, minX, maxY, lineColour, pat),
			_Bitmap_DoRectangle(ctx, maxX, minY, maxX + border, maxY, lineColour, pat);
		}
	}
}

static stock _Bitmap_DoRectangle(Bitmap:ctx, minX, minY, maxX, maxY, colour, pattern[])
{
	new
		width = Bitmap_Width(ctx);
	minY = max(0, minY),
	maxY = min(maxY, Bitmap_Height(ctx)),
	minX = max(0, minX),
	maxX = min(maxX, width),
	_Bitmap_MakePattern(pattern, minX, minY, 0, 0);
	new
		ya,
		read,
		a = (colour & 0xFF) + 1,
		na,
		suba,
		r = ((colour & 0xFF000000) >>> 16),
		g = ((colour & 0x00FF0000) >>> 16),
		b = ((colour & 0x0000FF00) >>>  8),
		orig;
	for (new y = minY; y != maxY; ++y)
	{
		read = Bitmap_IndexInt(ctx, minX, width, y),
		ya = y % YSI_gBitmapAlphaY;
		for (new x = minX; x != maxX; ++x)
		{
			suba = YSI_gBitmapAlpha[ya]{x % YSI_gBitmapAlphaX} * a;
			if (suba == 0xFF00)
			{
				YSI_gMallocMemory[read] = colour;
			}
			else if (suba >= 256)
			{
				// This is where we compensate for the odd shifts.
				na = 0xFF00 - suba,
				// Want this pixel in the final image.
				orig = YSI_gMallocMemory[read],
				YSI_gMallocMemory[read] = 0xFF |
					((((orig & 0xFF000000) >>> 16) * na + r * suba) & 0xFF000000) |
					((((orig & 0x00FF0000) >>> 16) * na + g * suba) & 0x00FF0000) |
					(((((orig & 0x0000FF00) >>> 8) * na + b * suba) & 0x00FF0000) >>> 8) ;
			}
			++read;
		}
	}
}

static stock _Bitmap_RectangleRecopy(n, BitArray:pattern<PATTERN_MASK_X>)
{
	for (new y = 1; y != n; ++y)
	{
		YSI_gBitmapAlpha[y] = pattern;
	}
}
