#if defined _INC_y_colours
	#endinput
#endif
#define _INC_y_colours

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

#include "..\..\YSI_Coding\y_stringhash"

#if !defined MAX_TEXT_COLOURS
	#if defined MAX_TEXT_COLORS
		#define MAX_TEXT_COLOURS	    MAX_TEXT_COLORS
	#else
		#define MAX_TEXT_COLOURS	    (32)
	#endif
#endif

#if !defined NO_X11_COLOURS && !defined NO_X11_COLORS && !defined YSI_NO_X11
	#define _YSI_USE_X11 true
#else
	#define _YSI_USE_X11 false
#endif

// Note that these are VERY unsafe, they're not designed for general use!
#define MK_RGB(%0,%1,%2)                ((%0)<<24|(%1)<<16|(%2)<<8|0xAA)
#define MK_RGBA(%0,%1,%2,%3)            ((%0)<<24|(%1)<<16|(%2)<<8|(%3))
#define MK_D_RGB(%0,%1,%2)              ((%0)<<24|(%1)<<16|(%2)<<8|0xAA)
#define MK_D_RGBA(%0,%1,%2,%3)          ((%0)<<24|(%1)<<16|(%2)<<8|(%3))
#define MK_S_RGB(%0,%1,%2)              #%0#%1#%2
#define MK_S_RGBA(%0,%1,%2,%3)          #%0#%1#%2
#define MK_S_DEF(%0)                    ((%0) >>> 8)

#if _YSI_USE_X11
	#include "y_colours_x11def"
#endif

#include "y_colours_gtdef"

// Special macro for adding game text colours.
#define GT(%0) GT_%0

#define GT_~%0~ "{"#AeC01e"}{"#_GT_%0"}"

// This does redefine a possible colour, but with a very obscure pattern.  Also
// with awkward mixed case to not match "AEC01E" or "aec01e".
#define AeC01e"}{"#%0"}"~h~ AeC01e"}{"#%0h"}"

// Main code start.  Apparently there is a copy of the hash code in y_td.
#define COLOUR_NAME_HASH(%0)            YHash((%0), false, hash_bernstein, (YSI_g_sCheckSpaces) ? (-1) : (strfind((%0), YSI_SPACE)))
#define COLOR_NAME_HASH                 COLOUR_NAME_HASH

#if !defined X11_ALLOW_SPACES
	#define X11_ALLOW_SPACES (false)
#endif

static stock
	YSI_g_sColours[MAX_TEXT_COLOURS][2],
	bool:YSI_g_sCheckSpaces = X11_ALLOW_SPACES;

forward void:_SetColoursCanHaveSpaces(bool:set);

public void:_SetColoursCanHaveSpaces(bool:set)
{
	YSI_g_sCheckSpaces = set;
}

#define SetColorsCanHaveSpaces SetColoursCanHaveSpaces
stock SetColoursCanHaveSpaces(bool:set)
{
	// Set this true/false in ALL scripts, since the text system is distributed.
	CallRemoteFunction("_SetColoursCanHaveSpaces", YSI_gcI, set);
	//return 1;
}

#define SetColor SetColour
stock SetColour(const name[], color)
{
	Debug_Print3("SetColour called: \"%s\", %i", name, color);
	#if _YSI_USE_X11
		//if (name[0] | 0x20 == 'x' && name[1] == '1' && name[2] == '1')
		if (!strcmp(name, "X11", true, 3))
		{
			if (name[3] == ' ' || name[3] == '_')
			{
				SetColourHash(COLOUR_NAME_HASH(name[4]), color);
			}
			else
			{
				SetColourHash(COLOUR_NAME_HASH(name[3]), color);
			}
		}
		else
	#endif
	{
		SetColourHash(COLOUR_NAME_HASH(name), color);
	}
}

stock SetColourHash(hash, color)
{
	CallRemoteFunction("_SetColourHash", "ii", hash, color);
}

#define SetColorHash SetColourHash
forward void:_SetColourHash(hash, color);

public void:_SetColourHash(hash, color)
{
	Debug_Print3("SetColourHash called: %i, %i", hash, color);
	color &= 0xFFFFFF00;
	#if _YSI_USE_X11
		new
			id = GetColourHash(hash);
		if (id != 0)
		{
			for (new i = 0; i != MAX_TEXT_COLOURS; ++i)
			{
				new
					iColor = YSI_g_sColours[i][0];
				if (iColor == hash)
				{
					YSI_g_sColours[i][1] = color;
					return; // i;
				}
				else if (iColor == 0)
				{
					// Tried to rename an X11 colour.
					return; // -1;
				}
			}
		}
	#endif
	for (new i = 0; i != MAX_TEXT_COLOURS; ++i)
	{
		new
			iColor = YSI_g_sColours[i][0];
		if (iColor == hash || iColor == 0)
		{
			YSI_g_sColours[i][0] = hash;
			YSI_g_sColours[i][1] = color;
			return; // i;
		}
	}
	return; // -1;
}

// This now uses REVERSE bernstein hash for switch compatibility.

#define GetColor GetColour
stock GetColour(const name[], alpha = 0xAA)
{
	Debug_Print3("GetColour called: \"%s\", %i", name, alpha);
	//if (name[0] | 0x20 == 'x' && name[1] == '1' && name[2] == '2')
	#if _YSI_USE_X11
		if (!strcmp(name, "X11", true, 3))
		{
			if ((YSI_g_sCheckSpaces && name[3] == ' ') || name[3] == '_')
			{
				return GetColourHash(COLOUR_NAME_HASH(name[4]), alpha);
			}
			else
			{
				return GetColourHash(COLOUR_NAME_HASH(name[3]), alpha);
			}
		}
		else
	#endif
	{
		return GetColourHash(COLOUR_NAME_HASH(name), alpha);
	}
}

#define GetColorStream GetColourStream
stock GetColourStream(const str[], &idx, alpha = 0xAA)
{
	Debug_Print3("GetColourStream called: \"%s\", %i, %i", str, idx, alpha);
	// This doesn't work because the hash is backwards, not forwards.  You can't
	// do a reverse hash incrementally.  Actually you can, but not well.
	new
		pos = idx,
		ret = -1;
	#if _YSI_USE_X11
		//new
		//	bool:checkSpace = YSI_g_sCheckSpaces;
		if (!strcmp(str[pos], "X11", true, 3))
		{
			pos += 3;
			if ((YSI_g_sCheckSpaces && str[pos] == ' ') || str[pos] == '_')
			{
				++pos;
			}
		}
		ret = Colours_DoHashParse(str[pos], pos, YSI_g_sCheckSpaces);
		if (ret != -1)
		{
			idx = pos;
			return ret | alpha;
		}
	#endif
	// Do the incremental hash.  This *should* be "idx = pos + 16;", but it
	// isn't as you shouldn't prefix custom colours with "X11" as they're not.
	new
		test = min(strlen(str[pos]), 16);
	while (test)
	{
		// This is a greedy test, and restricts custom text to 16 characters.
		ret = YHash(str[pos], false, hash_bernstein, test);
		for (new i = 0; i != MAX_TEXT_COLOURS; ++i)
		{
			new
				iColor = YSI_g_sColours[i][0];
			if (iColor == ret)
			{
				idx = pos + test;
				return alpha | YSI_g_sColours[i][1];
			}
			else if (iColor == 0)
			{
				break;
			}
		}
		--test;
	}
	return 0;
}

#define GetColorHash GetColourHash
stock GetColourHash(hash, alpha = 0xAA)
{
	Debug_Print3("GetColourHash called: %i, %i", hash, alpha);
	alpha &= 0xFF;
	// Do the REVERSE hash from YHash
	#pragma tabsize 4
	#if _YSI_USE_X11
		#include "y_colours_x11switch"
	#endif
	#pragma tabsize 4
	// Do the default code here.
	for (new i = 0; i != MAX_TEXT_COLOURS; ++i)
	{
		new
			iColor = YSI_g_sColours[i][0];
		if (iColor == hash)
		{
			return alpha | YSI_g_sColours[i][1];
		}
		else if (iColor == 0)
		{
			return 0;
		}
	}
	return 0;
}

#if _YSI_USE_X11
	static stock Colours_DoHashParse(const str[], &idx, bool:checkSpace)
	{
		// You can't use custom colours with the "#COLOR" format, but you can
		// with the "{COLOR}" format, this is to save on memory.  It is in
		// theory possible to get it working with the hash format using an
		// incremental hash and compare.  NOW SUPPORTED!
		#include "y_colours_x11parse"
		#pragma tabsize 4
		return -1;
	}
#endif

#define _COLOUR_GT_SPACE_DEF_0(%0)      SAMP_GAME_TEXT_%0
#define _COLOUR_GT_SPACE_DEF_1(%0)      SAMP_GAME_TEXT_%0H
#define _COLOUR_GT_SPACE_DEF_2(%0)      SAMP_GAME_TEXT_%0HH
#define _COLOUR_GT_SPACE_DEF_3(%0)      SAMP_GAME_TEXT_%0HHH
#define _COLOUR_GT_SPACE_DEF_4(%0)      SAMP_GAME_TEXT_%0HHHH
#define _COLOUR_GT_SPACE_DEF_5(%0)      SAMP_GAME_TEXT_%0HHHHH

#define _COLOUR_GT_SPACE(%0,%1)         {('%0'|0x20)|(%1<<8),_COLOUR_GT_SPACE_DEF_%1(%0)>>>24,_COLOUR_GT_SPACE_DEF_%1(%0)>>16&0xFF,_COLOUR_GT_SPACE_DEF_%1(%0)>>8&0xFF}

#define Colors_SAMPToGT Colours_SAMPToGT
stock Colours_SAMPToGT(colour, start)
{
	Debug_Print4("Colours_SAMPToGT called: %i", colour);
	// Find the closest matching game text colour to the given SA:MP colour.
	static const
		sc_aColours[][4] =
		{
			// These can't be used as you can't set text to them.  You can
			// however use them at the start by not changing.
			_COLOUR_GT_SPACE(X,0), _COLOUR_GT_SPACE(X,1),
			_COLOUR_GT_SPACE(X,2),
			
			_COLOUR_GT_SPACE(R,0), _COLOUR_GT_SPACE(R,1),
			_COLOUR_GT_SPACE(R,2), _COLOUR_GT_SPACE(R,3),
			_COLOUR_GT_SPACE(R,4), _COLOUR_GT_SPACE(R,5),
			
			_COLOUR_GT_SPACE(G,0), _COLOUR_GT_SPACE(G,1),
			_COLOUR_GT_SPACE(G,2), _COLOUR_GT_SPACE(G,3),
			//_COLOUR_GT_SPACE(G,4), // Don't want this twice (see Y2).
			
			_COLOUR_GT_SPACE(B,0), _COLOUR_GT_SPACE(B,1),
			_COLOUR_GT_SPACE(B,2), _COLOUR_GT_SPACE(B,3),
			
			_COLOUR_GT_SPACE(Y,0), _COLOUR_GT_SPACE(Y,1),
			_COLOUR_GT_SPACE(Y,2),
			
			_COLOUR_GT_SPACE(P,0), _COLOUR_GT_SPACE(P,1),
			_COLOUR_GT_SPACE(P,2),
			
			_COLOUR_GT_SPACE(W,0),
			
			_COLOUR_GT_SPACE(L,0)
		};
	new
		dist = cellmax,
		found = '\0',
		r = colour >> 16,
		g = (colour >> 8) & 0xFF,
		b = colour & 0xFF,
		tr = 0,
		tg = 0,
		tb = 0,
		cur = 0;
	for ( ; start != sizeof (sc_aColours); ++start)
	{
		tr = r - sc_aColours[start][1],
		tg = g - sc_aColours[start][2],
		tb = b - sc_aColours[start][3],
		cur = (tr * tr) + (tg * tg) + (tb * tb);
		Debug_Print6("Colours_SAMPToGT: Test %x %d", sc_aColours[start][0], cur);
		if (cur < dist)
		{
			Debug_Print6("Colours_SAMPToGT: Change %x %d", found, dist);
			// This may sometimes give odd results in fades for draw results.
			// Though I've not seen it happen yet.
			dist = cur,
			found = sc_aColours[start][0];
		}
	}
	return found;
}

stock Colours_EncodeGameText(str[])
{
	new
		ret = 0;
	if (str[0] == '~')
	{
		switch (str[1] | 0x20)
		{
			case 'r', 'g', 'b', 'y', 'p', 'w', 'l', 'x':
			{
				ret = str[1] | 0x20;
			}
			case 'h':
			{
				ret = 0x100 | 'x';
			}
			default: return 0;
		}
		if (str[2] != '~') return 0;
		new
			pos = 3;
		while (str[pos++] == '~' && str[pos++] | 0x20 == 'h' && str[pos++] == '~')
		{
			ret += 0x100;
		}
	}
	return ret;
}

