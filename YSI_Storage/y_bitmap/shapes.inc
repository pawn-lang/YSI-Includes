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

/*-------------------------------------------------------------------------*//**
 * <param name="ctx">The bitmap to modify.</param>
 * <param name="minX">The left of the array.</param>
 * <param name="minY">The top of the array.</param>
 * <param name="maxX">The right of the array.</param>
 * <param name="maxY">The bottom of the array.</param>
 * <param name="fillColour">The colour of the inside of the rectangle.</param>
 * <param name="lineColour">The colour of the rectangle border.</param>
 * <param name="linePattern[] = \"SOLID\"">How to draw the inside.</param>
 * <param name="fillPattern[] = \"SOLID\"">How to draw the border.</param>
 * <remarks>
 *  This function draws a rectangle between two given co-ordinates.  It can also
 *  draw a border around the rectangle OUTSIDE the specified area of the
 *  rectangle.  If you want the border within the area specified you need to use
 *  a smaller area.
 * </remarks>
 *//*------------------------------------------------------------------------**/

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

/*-------------------------------------------------------------------------*//**
 * <param name="ctx">The bitmap to modify.</param>
 * <param name="x">The x co-ordinate of the circle centre.</param>
 * <param name="y">The y co-ordinate of the circle centre.</param>
 * <param name="radius">The size of the circle.</param>
 * <param name="fillColour">The colour of the inside of the circle.</param>
 * <param name="lineColour">The colour of the circle border.</param>
 * <param name="linePattern[] = \"SOLID\"">How to draw the inside.</param>
 * <param name="fillPattern[] = \"SOLID\"">How to draw the border.</param>
 * <remarks>
 *  This function draws a circle centered on the given co-ordinates with the
 *  given FLOAT radius, not an integer size because of diagonals. It can also
 *  draw a border around the circle OUTSIDE the specified area of the circle.
 *  If you want the border within the area specified you need to use a smaller
 *  area.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Bitmap_DrawCircle(Bitmap:ctx, const x, const y, const Float:radius, fillColour, lineColour = 0, linePattern[] = "SOLID", fillPattern[] = "SOLID")
{
	P:3("Bitmap_DrawCircle called: %d, %d, %d, %.2f, 0x%04x%04x, 0x%04x%04x, \"%s\", \"%s\"", _:ctx, x, y, radius, fillColour >>> 16, fillColour & 0xFFFF, lineColour >>> 16, lineColour & 0xFFFF, linePattern, fillPattern);
	Bitmap_DrawRing(ctx, x, y, 0.0, radius, fillColour, fillPattern);
}

/*-------------------------------------------------------------------------*//**
 * <param name="ctx">The bitmap to modify.</param>
 * <param name="x">The x co-ordinate of the ring centre.</param>
 * <param name="y">The y co-ordinate of the ring centre.</param>
 * <param name="inner">The inner size of the ring.</param>
 * <param name="outer">The outer size of the ring.</param>
 * <param name="colour">The colour of the ring.</param>
 * <param name="pattern[] = \"SOLID\"">How to draw the inside.</param>
 * <remarks>
 *  This function draws a ring centered on the given co-ordinates with the
 *  given FLOAT radius, not an integer size because of diagonals.  This does not
 *  draw a border as it is used for borders, and a border on a ring is ambiguous
 *  - do you have it on the inside or not?  Better to let the user decide.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Bitmap_DrawRing(Bitmap:ctx, x, y, Float:inner, Float:outer, colour, pattern[] = "SOLID")
{
	P:3("Bitmap_DrawRing called: %d, %d, %d, %.2f, %.2f, 0x%04x%04x, \"%s\"", _:ctx, x, y, inner, outer, colour >>> 16, colour & 0xFFFF, pattern);
	new
		rad = max(floatround(outer, floatround_ceil), 0);
	if (rad == 0) return;
	new
		width = Bitmap_Width(ctx),
		// Get the circle bounds.
		minY = max(0, y - rad),
		maxY = min(y + rad + 1, Bitmap_Height(ctx)),
		minX = max(0, x - rad),
		maxX = min(x + rad + 1, width),
		// Get the approximate edges of the circle so we know how much blending
		// to use on the outer pixels.
		Float:outerMax = outer + 1.0,
		Float:rootMax = outer - 1.0,
		Float:outerMin = rootMax * rootMax,
		Float:innerMax = inner + 1.0,
		Float:rootMin = inner - 1.0,
		Float:innerMin;
	outerMax *= outerMax,
	innerMax *= innerMax;
	if (inner <= 0.0)
	{
		inner = 0.0;
		//innerMin = 0.0;
	}
	else innerMin = rootMin * rootMin;
	//new
	//	Float:outerDiff = outerMax - outerMin,
	//	Float:innerDiff = innerMax - innerMin;
	_Bitmap_MakePattern(pattern, minX, minY, 0, 0);
	new
		ya,
		// Get the float co-ordinates for ease of calculation.
		Float:fX = float(-rad), // Converted back from the integer version to.
		Float:fXX,
		Float:fY = float(-rad), // Make up for rounding errors.
		Float:fYY,
		Float:pos,
		read,
		a = (colour & 0xFF) + 1,
		na,
		suba,
		r = ((colour & 0xFF000000) >>> 16),
		g = ((colour & 0x00FF0000) >>> 16),
		b = ((colour & 0x0000FF00) >>>  8),
		orig;
	P:5("Bitmap_DrawRing: minX = %d, minY = %d, width = %d, height = %d", minX, minY, width, Bitmap_Height(ctx));
	for (y = minY; y != maxY; ++y, ++fY)
	{
		// "y" portion of the radius calculation.
		fYY = fY * fY,
		read = Bitmap_IndexInt(ctx, minX, width, y),
		ya = y % YSI_gBitmapAlphaY;
		P:6("Bitmap_DrawRing: 4: %.2f, %d, %d", fYY, read, ya);
		fXX = fX;
		for (x = minX; x != maxX; ++x, ++fXX, ++read)
		{
			pos = fXX * fXX + fYY;
			P:7("Bitmap_DrawRing: 5: %.2f <= %.2f <= %.2f", outerMin, pos, outerMax);
			// Slightly redundant check if "inner" is 0.0, but in that case will
			// at least never fail!
			if (pos >= innerMin)
			{
				// Calculate the full colour.
				suba = YSI_gBitmapAlpha[ya]{x % YSI_gBitmapAlphaX} * a;
				if (inner != 0.0 && pos <= innerMax)
				{
					// Draw partially (blending for the ring inner edge).
					//YSI_gMallocMemory[read] = 0xFF; // Black for now.
					suba = floatround((floatsqroot(pos) - rootMin) / 2.0 * float(suba));
				}
				else if (pos <= outerMin)
				{
					// Draw fully (part of the ring).
					//YSI_gMallocMemory[read] = suba;
					// Do nothing, but also don't end.
				}
				else if (pos <= outerMax)
				{
					// Draw partially (blending for the ring outer edge).
					//YSI_gMallocMemory[read] = 0xFF; // Black for now.
					suba = floatround((1.0 - (floatsqroot(pos) - rootMax) / 2.0) * float(suba));
				}
				else
				{
					// Otherwise don't draw anything at all - we are outside the ring.
					continue;
				}
				if (suba >= 0xFF00)
				{
					YSI_gMallocMemory[read] = colour;
				}
				else if (suba > 0xFF)
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
			}
		}
	}
}
