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

/*#define _PATTERN_FLAGS     (0x01010000)
#define _PATTERN_FADE_EDGE (0x01000000)

#define _PATTERN_WIDTH     (0xFE000000)
#define _PATTERN_PADDING   (0x00FE0000)

#define _PATTERN_MASK      (0x0000FFFF)

// Pre-defined patterns.
// ---------
#define PATTERN_SOLID    (0b1)
// - - - - -
#define PATTERN_DOTTED   (0b10)
// -- -- -- 
#define PATTERN_DASHED   (0b110)
// - -- - --
#define PATTERN_DOT_DASH (0b10110)
// --  --  --
#define PATTERN_WIDE_DASH (0b1100)
// - - -- - - --
#define PATTERN_DOT_DOT_DASH (0b1010110)
// - -- --- --
#define PATTERN_O_A_O_O_A_O_O_O_A_O_O_A (0b101101110110)*/

/*stock const
	PATTERN_SOLID = "PATTERN_SOLID",
	PATTERN_DOTTED = "PATTERN_DOTTED",
	PATTERN_SOLID = "PATTERN_SOLID";*/

/*#define PATTERN(%0) (_:_MK_PAT(0,%0@)&0xFFFF)
#define _MK_PAT(%1,%0) _yPd:_yPD:_yPS:(%1,%0)
// Dot.
#define _yPd:%9(%1,.%0) _MK_PAT((%1)*2|1,%0)
// Space.
#define _yPD:%9(%1,-%0) _MK_PAT((%1)*2,%0)
#define _yPS:%9(%1,)   (%1)
//#define _yPN:%9(%1,_%0)  _MK_PAT((%1)*2%0)*/

#define PATTERN_MASK_X (256)
#define PATTERN_MASK_Y (256)

stock
	// 8Kb
	YSI_gBitmapAlpha[PATTERN_MASK_Y][PATTERN_MASK_X char],
	YSI_gBitmapAlphaX = 1,
	YSI_gBitmapAlphaY = 1;
	//BitArray:YSI_gBitmapAlpha[PATTERN_MASK_Y]<PATTERN_MASK_X>;

stock const
	YSI_gBitmapBlank[PATTERN_MASK_Y][PATTERN_MASK_X char];// = {Bit:0, ...};
	//BitArray:YSI_gBitmapBlank[PATTERN_MASK_Y]<PATTERN_MASK_X>;// = {Bit:0, ...};

//stock Bitmap_ResetPattern()
//{
//	YSI_gBitmapAlpha = YSI_gBitmapBlank;
//}

#define _Bitmap_ResetPattern() (YSI_gBitmapAlpha=YSI_gBitmapBlank)

#define PATTERN(%0) (_:_PATTERN:(#%0))
#define _PATTERN:(%0,%1) _PATTERN:(%0"\x2c;"#%1)

stock _Bitmap_MakePattern(const pattern[], const posX, const posY, const offsetX, const offsetY)
{
	static
		func[FUNCTION_LENGTH] = "_BMP_PAT@";
	new
		pos = strfind(pattern, ",");
	func[9] = '\0',
	strcat(func, pattern);
	if (pos == -1)
	{
		if (funcidx(func) == -1) func = "_BMP_PAT@SOLID";
		CallLocalFunction(func, "iiiis", posX, posY, offsetX, offsetY, NULL);
	}
	else
	{
		func[pos + 9] = '\0';
		if (funcidx(func) == -1) func = "_BMP_PAT@SOLID";
		CallLocalFunction(func, "iiiis", posX, posY, offsetX, offsetY, pattern[pos]);
	}
}

stock _Bitmap_Param(const str[], const find[])
{
	new
		pos = strfind(str, find, true),
		len = strlen(str),
		ch = 0;
	if (0 < pos)
	{
		ch = str[pos - 1];
		if (ch == ' ' || ch == ',')
		{
			new
				p = pos;
			while (p != len)
			{
				ch = str[p];
				if (ch == '=')
				{
					return strval(str[++p]);
				}
				else if (ch == ',')
				{
					// There, but no value.
					return 0;
				}
				++p;
			}
			return 0;
		}
	}
	return cellmin;
}

forward _BMP_PAT@SOLID(const posX, const posY, const offsetX, const offsetY, const flags[]);

public _BMP_PAT@SOLID(const posX, const posY, const offsetX, const offsetY, const flags[])
{
	#pragma unused posX, posY, offsetX, offsetY, flags
	YSI_gBitmapAlpha[0]{0} = 255,
	YSI_gBitmapAlphaX = 1,
	YSI_gBitmapAlphaY = 1;
}

forward _BMP_PAT@DIAGONAL(const posX, const posY, const offsetX, const offsetY, const flags[]);

public _BMP_PAT@DIAGONAL(const posX, const posY, const offsetX, const offsetY, const flags[])
{
	#pragma unused posX, posY, offsetX, offsetY, flags
	new
		// Alpha.
		stripe1 = _Bitmap_Param(flags, "stripe1"),
		stripe2 = _Bitmap_Param(flags, "stripe2"),
		left = _Bitmap_Param(flags, "right");
	if (stripe1 == cellmin) stripe1 = 8;
	if (stripe2 == cellmin) stripe2 = stripe1;
	// The stripes are the widths of the lines.  Calculate the width of the
	// diagonal line horizontally.
	new
		Float:l1x = stripe1;
	l1x = floatsqroot(l1x * l1x / 2.0);
	new
		// The number of actual pixels across the first line.
		Float:l2w = stripe2,
		stripes = floatround((l1x + floatsqroot(l2w * l2w / 2.0)) * 2.0);
	// For 45 degrees there are only two types of partial pixels.
	stripe2 = floatround(l1x, floatround_floor);
	// Start pos.
	new
		pw = stripe2 / 2, // INTEGER division.
		mw = floatround(-l1x, floatround_floor),
		mp = mw - 1,
		pp = pw + 1;
	// Get the alpha parts.
	l2w = (l1x - stripe2),
	stripe2 = floatround(l2w * l2w / 2.0 * 255.0),
	l2w = 1.0 - l2w,
	stripe1 = floatround((1.0 - l2w * l2w / 2.0) * 255.0);
	// stripe2 is now the minor alpha, stripe1 is the major alpha.
	for (new y = 0; y != stripes; ++y)
	{
		for (new x = 0; x != stripes; ++x)
		{
			new
				xp = (x - mp) % stripes + mp;
			if (mw < xp < pw)
				YSI_gBitmapAlpha[y]{x} = 0xFF;
			else if (xp == mw || xp == pw)
				YSI_gBitmapAlpha[y]{x} = stripe1;
			else if (xp == mp || xp == pp)
				YSI_gBitmapAlpha[y]{x} = stripe2;
			else
				YSI_gBitmapAlpha[y]{x} = 0;
		}
		if (left)
		{
			++pw,
			++mw,
			++mp,
			++pp;
		}
		else
		{
			--pw,
			--mw,
			--mp,
			--pp;
		}
	}
	YSI_gBitmapAlphaX = stripes,
	YSI_gBitmapAlphaY = stripes;
}

forward _BMP_PAT@STRIPED(const posX, const posY, const offsetX, const offsetY, const flags[]);

public _BMP_PAT@STRIPED(const posX, const posY, const offsetX, const offsetY, const flags[])
{
	#pragma unused posX, posY, offsetX, offsetY, flags
	// Calculate the colour information.
	new
		// Alpha.
		stripe1 = _Bitmap_Param(flags, "stripe1"),
		stripe2 = _Bitmap_Param(flags, "stripe2"),
		stripes = _Bitmap_Param(flags, "horizontal");
	if (stripe1 == cellmin) stripe1 = 8;
	if (stripe2 == cellmin) stripe2 = stripe1;
	if (stripes)
	{
		stripes = stripe1 + stripe2,
		stripe2 = 0;
		while (stripe2 != stripe1)
		{
			YSI_gBitmapAlpha[0]{stripe2++} = 255;
		}
		while (stripe2 != stripes)
		{
			YSI_gBitmapAlpha[0]{stripe2++} = 0;
		}
		YSI_gBitmapAlphaX = stripes,
		YSI_gBitmapAlphaY = 1;
	}
	else
	{
		stripes = stripe1 + stripe2,
		stripe2 = 0;
		while (stripe2 != stripe1)
		{
			YSI_gBitmapAlpha[stripe2++]{0} = 255;
		}
		while (stripe2 != stripes)
		{
			YSI_gBitmapAlpha[stripe2++]{0} = 0;
		}
		YSI_gBitmapAlphaX = 1,
		YSI_gBitmapAlphaY = stripes;
	}
}

