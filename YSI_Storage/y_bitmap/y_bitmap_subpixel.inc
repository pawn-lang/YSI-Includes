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

stock Bitmap_StraightLine(Bitmap:ctx, sX, sY, eX, eY, Float:lineWidth, colour, const pattern[] = "SOLID")
{
	Debug_Print3("Bitmap_DrawRing called: %d, %d, %d, %.2f, %.2f, 0x%04x%04x, \"%s\"", _:ctx, x, y, inner, outer, colour >>> 16, colour & 0xFFFF, pattern);
	new
		imageWidth = Bitmap_Width(ctx),
		minY = 0, // = max(0, min(sY, eY)),
		maxY = Bitmap_Height(ctx), // = min(max(sY, eY), Bitmap_Height(ctx)),
		minX = 0, // = max(0, min(sX, eX)),
		maxX = Bitmap_Width(ctx), // = min(max(sX, eX), imageWidth),
		Float:angle = 0.0,
		read = 0,
		a = (colour & 0xFF) + 1,
		na = 0,
		suba = 0,
		r = ((colour & 0xFF000000) >>> 16),
		g = ((colour & 0x00FF0000) >>> 16),
		b = ((colour & 0x0000FF00) >>>  8),
		orig = 0;
	_Bitmap_MakePattern(pattern, minX, minY, 0, 0);

	// Sort out the line angle, in degrees, to get the corners.
	if (sX > eX)
	{
		// Swap the direction.
		sX ^= eX;
		eX ^= sX;
		sX ^= eX;
		sY ^= eY;
		eY ^= sY;
		sY ^= eY;
	}
	angle = (sX == eX) ? 0.0 : atan((eY - sY) / (eX - sX));

	// Now we find the box to draw in by the corners, not the centre line.
	














	
}

