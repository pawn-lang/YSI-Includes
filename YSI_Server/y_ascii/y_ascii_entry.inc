#if defined _INC_y_ascii
	#endinput
#endif
#define _INC_y_ascii

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

enum ASCII_BORDER_STYLE
{
	ASCII_BORDER_STYLE_SMALL,
	ASCII_BORDER_STYLE_LARGE,
	ASCII_BORDER_STYLE_PILLARS,
}

enum ASCII_ALIGNMENT_STYLE
{
	ASCII_ALIGNMENT_STYLE_LEFT,
	ASCII_ALIGNMENT_STYLE_CENTRE,
}

stock ASCII_PrintLine(const text[], len, bool:hypen, ASCII_BORDER_STYLE:border, ASCII_ALIGNMENT_STYLE:alignment, padding = 0)
{
	new
		spacer[] = "",
		ch0,
		ch1;
	// End the string.
	if (hypen)
	{
		ch0 = _YSI_ConstMod(text[len++], '-');
	}
	ch1 = _YSI_ConstMod(text[len], '\0');
	switch (border)
	{
	case ASCII_BORDER_STYLE_SMALL:
	{
		switch (alignment)
		{
		case ASCII_ALIGNMENT_STYLE_LEFT:
			YSI_PrintF(" | %38s | ", text);
		case ASCII_ALIGNMENT_STYLE_CENTRE:
			padding = (38 - len) / 2 + padding,
			YSI_PrintF(" | %*s%*s | ", padding, spacer, 38 - padding, text);
		}
	}
	case ASCII_BORDER_STYLE_LARGE:
	{
		switch (alignment)
		{
		case ASCII_ALIGNMENT_STYLE_LEFT:
			YSI_PrintF("         | %52s |", text);
		case ASCII_ALIGNMENT_STYLE_CENTRE:
			padding = (52 - len) / 2 + padding,
			YSI_PrintF("         | %*s%*s |", padding, spacer, 52 - padding, text);
		}
	}
	case ASCII_BORDER_STYLE_PILLARS:
	{
		switch (alignment)
		{
		case ASCII_ALIGNMENT_STYLE_LEFT:
			YSI_PrintF("    |||||||  %53s  |||||||", text);
		case ASCII_ALIGNMENT_STYLE_CENTRE:
			padding = (53 - len) / 2 + padding,
			YSI_PrintF("    |||||||  %*s%*s  |||||||", padding, spacer, 53 - padding, text);
		}
	}
	}
	// Reset the string.
	if (hypen)
	{
		_YSI_ConstMod(text[len - 1], ch0);
	}
	_YSI_ConstMod(text[len], ch1);
}


#if !defined YSI_LARGE_FILE_SIZE
	#define YSI_LARGE_FILE_SIZE (1024 * 1024) // 1Mb
#endif

#if defined YSI_TESTS
	#include "y_ascii_tests"
#endif

