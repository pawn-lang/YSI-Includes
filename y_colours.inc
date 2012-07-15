/*----------------------------------------------------------------------------*\
					==========================
					 y_colours - X11 colours!
					==========================
Description:
	This holds the colour information that used to be part of the text system
	but which is far more useful than just for text.  This now supports the full
	set of X11 colours, both by name and by definition.  You can also define
	your own if you so choose (up to 32 - should be enough given that this
	includes the X11 colours).
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
	
	The Original Code is the YSI colours include.
	
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
	1.0
Changelog:
	20/02/12:
		Added broadcastfunc of colours.	
	29/11/10:
		Added the ability to use "X11" prefixes in strings.
		Added colourspace resolution for converting {FF0000} to ~r~.
	25/11/10:
		First version.
\*----------------------------------------------------------------------------*/

#include "internal\y_version"

#include "y_stringhash"
#include "y_debug"
#include "y_remote"

#include "y_utils"

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

// These are the RGB values for the gametext colours (got manually using GIMP).
// These need to be added in to the main system so you can type and use them.
#define SAMP_GAME_TEXT                  MK_RGB(144,  98,  16)
#define SAMP_GAME_TEXT_                 MK_RGB(144,  98,  16)
#define SAMP_GAME_TEXT_H                MK_RGB(216, 147,  24)
#define SAMP_GAME_TEXT_HH               MK_RGB(255, 255,  54)
#define SAMP_GAME_TEXT_X                MK_RGB(144,  98,  16)
#define SAMP_GAME_TEXT_XH               MK_RGB(216, 147,  24)
#define SAMP_GAME_TEXT_XHH              MK_RGB(255, 255,  54)

#define SAMP_GAME_TEXT_R                MK_RGB(180,  25,  29)
#define SAMP_GAME_TEXT_RH               MK_RGB(255,  37,  43)
#define SAMP_GAME_TEXT_RHH              MK_RGB(255,  55,  64)
#define SAMP_GAME_TEXT_RHHH             MK_RGB(255,  82,  96)
#define SAMP_GAME_TEXT_RHHHH            MK_RGB(255, 123, 144)
#define SAMP_GAME_TEXT_RHHHHH           MK_RGB(255, 184, 216)

#define SAMP_GAME_TEXT_G                MK_RGB( 54, 104,  44)
#define SAMP_GAME_TEXT_GH               MK_RGB( 81, 156,  66)
#define SAMP_GAME_TEXT_GHH              MK_RGB(121, 234,  99)
#define SAMP_GAME_TEXT_GHHH             MK_RGB(181, 255, 148)
#define SAMP_GAME_TEXT_GHHHH            MK_RGB(255, 255, 222)

#define SAMP_GAME_TEXT_B                MK_RGB( 50,  60, 127)
#define SAMP_GAME_TEXT_BH               MK_RGB( 75,  90, 190)
#define SAMP_GAME_TEXT_BHH              MK_RGB(112, 135, 255)
#define SAMP_GAME_TEXT_BHHH             MK_RGB(168, 202, 255)

#define SAMP_GAME_TEXT_Y                MK_RGB(226, 192,  99)
#define SAMP_GAME_TEXT_YH               MK_RGB(255, 255, 148)
#define SAMP_GAME_TEXT_YHH              MK_RGB(255, 255, 222) // Also in green

#define SAMP_GAME_TEXT_P                MK_RGB(168, 110, 252)
#define SAMP_GAME_TEXT_PH               MK_RGB(252, 165, 255)
#define SAMP_GAME_TEXT_PHH              MK_RGB(255, 247, 255)

#define SAMP_GAME_TEXT_W                MK_RGB(255, 255, 255)

#define SAMP_GAME_TEXT_L                MK_RGB(  0,   0,   0)

// Second spellings.
#define SAMP_GAMETEXT                  MK_RGB(144,  98,  16)
#define SAMP_GAMETEXT_                 MK_RGB(144,  98,  16)
#define SAMP_GAMETEXT_H                MK_RGB(216, 147,  24)
#define SAMP_GAMETEXT_HH               MK_RGB(255, 255,  54)
#define SAMP_GAMETEXT_X                MK_RGB(144,  98,  16)
#define SAMP_GAMETEXT_XH               MK_RGB(216, 147,  24)
#define SAMP_GAMETEXT_XHH              MK_RGB(255, 255,  54)

#define SAMP_GAMETEXT_R                MK_RGB(180,  25,  29)
#define SAMP_GAMETEXT_RH               MK_RGB(255,  37,  43)
#define SAMP_GAMETEXT_RHH              MK_RGB(255,  55,  64)
#define SAMP_GAMETEXT_RHHH             MK_RGB(255,  82,  96)
#define SAMP_GAMETEXT_RHHHH            MK_RGB(255, 123, 144)
#define SAMP_GAMETEXT_RHHHHH           MK_RGB(255, 184, 216)

#define SAMP_GAMETEXT_G                MK_RGB( 54, 104,  44)
#define SAMP_GAMETEXT_GH               MK_RGB( 81, 156,  66)
#define SAMP_GAMETEXT_GHH              MK_RGB(121, 234,  99)
#define SAMP_GAMETEXT_GHHH             MK_RGB(181, 255, 148)
#define SAMP_GAMETEXT_GHHHH            MK_RGB(255, 255, 222)

#define SAMP_GAMETEXT_B                MK_RGB( 50,  60, 127)
#define SAMP_GAMETEXT_BH               MK_RGB( 75,  90, 190)
#define SAMP_GAMETEXT_BHH              MK_RGB(112, 135, 255)
#define SAMP_GAMETEXT_BHHH             MK_RGB(168, 202, 255)

#define SAMP_GAMETEXT_Y                MK_RGB(226, 192,  99)
#define SAMP_GAMETEXT_YH               MK_RGB(255, 255, 148)
#define SAMP_GAMETEXT_YHH              MK_RGB(255, 255, 222) // Also in green

#define SAMP_GAMETEXT_P                MK_RGB(168, 110, 252)
#define SAMP_GAMETEXT_PH               MK_RGB(252, 165, 255)
#define SAMP_GAMETEXT_PHH              MK_RGB(255, 247, 255)

#define SAMP_GAMETEXT_W                MK_RGB(255, 255, 255)

#define SAMP_GAMETEXT_L                MK_RGB(  0,   0,   0)

// Main code start.  Apparently there is a copy of the hash code in y_td.
#define COLOUR_NAME_HASH(%0)            YHash((%0), false, hash_bernstein, (YSI_g_sCheckSpaces) ? (-1) : (strfind((%0), " ")))
#define COLOR_NAME_HASH                 COLOUR_NAME_HASH

//#include "internal\y_colourparse"

#if _YSI_USE_X11
	#include "internal\y_x11def"
#endif

#if !defined X11_ALLOW_SPACES
	#define X11_ALLOW_SPACES (false)
#endif

static stock
	YSI_g_sColours[MAX_TEXT_COLOURS][2],
	bool:YSI_g_sCheckSpaces = X11_ALLOW_SPACES;

remotefunc _SetColoursCanHaveSpaces(bool:set)
{
	YSI_g_sCheckSpaces = set;
}

#define SetColorsCanHaveSpaces SetColoursCanHaveSpaces
stock SetColoursCanHaveSpaces(bool:set)
{
	// Set this true/false in ALL scripts, since the text system is distributed.
	broadcastfunc _SetColoursCanHaveSpaces(set);
	//return 1;
}

#define SetColor SetColour
stock SetColour(const name[], color)
{
	P:3("SetColour called: \"%s\", %i", name, color);
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
	broadcastfunc _SetColourHash(hash, color);
}

#define SetColorHash SetColourHash
remotefunc _SetColourHash(hash, color)
{
	P:3("SetColourHash called: %i, %i", hash, color);
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
	P:3("GetColour called: \"%s\", %i", name, alpha);
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
	P:3("GetColourStream called: \"%s\", %i, %i", str, idx, alpha);
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
	P:3("GetColourHash called: %i, %i", hash, alpha);
	alpha &= 0xFF;
	// Do the REVERSE hash from YHash
	#if _YSI_USE_X11
		#include "internal\y_x11switch"
	#endif
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
		#include "internal\y_x11parse"
		#pragma tabsize 4
		return -1;
	}
#endif
