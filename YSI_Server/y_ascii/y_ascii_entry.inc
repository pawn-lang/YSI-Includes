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

static stock
	YSI_gsSmallHeader[] = " ========================================== ",
	YSI_gsSmallBody[] = " |                                        | ";

static stock
	YSI_gsLargeHeader[] = "         ==============================================================",
	YSI_gsLargeBody[] = "         |                                                            |";

static stock
	YSI_gsPillarsHeader0[] = " ||||                                                                     |||| ",
	YSI_gsPillarsHeader1[] = " |---------------------------------------------------------------------------| ",
	YSI_gsPillarsHeader2[] = " |___-----___-----___-----___-----___-----___-----___-----___-----___-----___| ",
	YSI_gsPillarsHeader3[] = " / _ \\===/ _ \\   / _ \\===/ _ \\   / _ \\===/ _ \\   / _ \\===/ _ \\   / _ \\===/ _ \\ ",
	YSI_gsPillarsHeader4[] = "( (.\\ oOo /.) ) ( (.\\ oOo /.) ) ( (.\\ oOo /.) ) ( (.\\ oOo /.) ) ( (.\\ oOo /.) )",
	YSI_gsPillarsHeader5[] = " \\__/=====\\__/   \\__/=====\\__/   \\__/=====\\__/   \\__/=====\\__/   \\__/=====\\__/ ",
	YSI_gsPillarsBody0[] = "    |||||||         |||||||         |||||||         |||||||         |||||||    ",
	YSI_gsPillarsBody1[] = "    |||||||                                                         |||||||    ",
	YSI_gsPillarsFooter0[] = "    (oOoOo)         (oOoOo)         (oOoOo)         (oOoOo)         (oOoOo)    ",
	YSI_gsPillarsFooter1[] = "    J%%%%%L         J%%%%%L         J%%%%%L         J%%%%%L         J%%%%%L    ",
	YSI_gsPillarsFooter2[] = "   ZZZZZZZZZ       ZZZZZZZZZ       ZZZZZZZZZ       ZZZZZZZZZ       ZZZZZZZZZ   ",
	YSI_gsPillarsFooter3[] = "  ===========================================================================  ";

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

_Y_CORE_STATIC stock ASCII_PrintLinePart(const text[], len, bool:hyphen, ASCII_BORDER_STYLE:border, ASCII_ALIGNMENT_STYLE:alignment, padding = 1)
{
	new
		spacer[] = "",
		ch0,
		ch1;
	// End the string.
	if (hyphen)
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
		case ASCII_ALIGNMENT_STYLE_CENTRE: padding = (40 - len) / 2;
		default: {}
		}
		YSI_PrintF(" |%*s%*s%*s| ", padding, spacer, 40 - padding - padding, text, padding, spacer);
	}
	case ASCII_BORDER_STYLE_LARGE:
	{
		switch (alignment)
		{
		case ASCII_ALIGNMENT_STYLE_CENTRE: padding = (54 - len) / 2;
		default: {}
		}
		YSI_PrintF("         |%*s%*s%*s|", padding, spacer, 54 - padding - padding, text, padding, spacer);
	}
	case ASCII_BORDER_STYLE_PILLARS:
	{
		switch (alignment)
		{
		case ASCII_ALIGNMENT_STYLE_CENTRE: padding = (57 - len) / 2;
		default: {}
		}
		YSI_PrintF("    |||||||%*s%*s%*s|||||||", padding, spacer, 57 - padding - padding, text, padding, spacer);
	}
	}
	// Reset the string.
	if (hyphen)
	{
		_YSI_ConstMod(text[len - 1], ch0);
	}
	_YSI_ConstMod(text[len], ch1);
}

stock ASCII_PrintSection(const text[], ASCII_BORDER_STYLE:border, ASCII_ALIGNMENT_STYLE:alignment, padding = 1)
{
	new
		width;
	switch (border)
	{
	case ASCII_BORDER_STYLE_SMALL: width = 40 - padding - padding;
	case ASCII_BORDER_STYLE_LARGE: width = 54 - padding - padding;
	case ASCII_BORDER_STYLE_PILLARS: width = 57 - padding - padding;
	}
	new
		start = 0,
		end,
		next,
		bool:hyphen,
		bool:cont;
	do
	{
		cont = IterativeTextSplitter(text, width, start, end, next, hyphen),
		ASCII_PrintLinePart(text[start], end - start, hyphen, border, alignment, padding),
		start = next;
	}
	while (cont);
}

stock ASCII_StartDisplay(ASCII_BORDER_STYLE:border)
{
	switch (border)
	{
	case ASCII_BORDER_STYLE_SMALL:
	{
		YSI_PrintF(YSI_gsSmallHeader);
	}
	case ASCII_BORDER_STYLE_LARGE:
	{
		YSI_Print(YSI_gsLargeHeader);
	}
	case ASCII_BORDER_STYLE_PILLARS:
	{
		YSI_Print("                                   ___---___                                   "),
		YSI_Print("                             ___---___---___---___                             "),
		YSI_Print("                       ___---___---    *    ---___---___                       "),
		YSI_Print("                 ___---___---    o/ 0_/  @  o ^   ---___---___                 "),
		YSI_Print("           ___---___--- @  i_e J-U /|  -+D O|-| (o) /   ---___---___           "),
		YSI_Print("     ___---___---    __/|  //\\  /|  |\\  /\\  |\\|  |_  __--oj   ---___---___     "),
		YSI_Print("__---___---_________________________________________________________---___---__"),
		YSI_Print("==============================================================================="),
		YSI_Print(YSI_gsPillarsHeader0),
		YSI_Print(YSI_gsPillarsHeader1),
		YSI_Print(YSI_gsPillarsHeader2),
		YSI_Print(YSI_gsPillarsHeader3),
		YSI_Print(YSI_gsPillarsHeader4),
		YSI_Print(YSI_gsPillarsHeader5),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsFooter0),
		YSI_Print(YSI_gsPillarsFooter1),
		YSI_Print(YSI_gsPillarsFooter2),
		YSI_Print(YSI_gsPillarsFooter3);
	}
	}
}

stock ASCII_StartSection(ASCII_BORDER_STYLE:border)
{
	switch (border)
	{
	case ASCII_BORDER_STYLE_SMALL:
	{
		YSI_Print(YSI_gsSmallBody);
	}
	case ASCII_BORDER_STYLE_LARGE:
	{
		YSI_Print(YSI_gsLargeBody),
		YSI_Print(YSI_gsLargeBody);
	}
	case ASCII_BORDER_STYLE_PILLARS:
	{
		YSI_Print(YSI_gsPillarsHeader0);
		YSI_Print(YSI_gsPillarsHeader1);
		YSI_Print(YSI_gsPillarsHeader2);
		YSI_Print(" / _ \\===/ _ \\                                                   / _ \\===/ _ \\ ");
		YSI_Print("( (.\\ oOo /.) )                                                 ( (.\\ oOo /.) )");
		YSI_Print(" \\__/=====\\__/                                                   \\__/=====\\__/ ");
		YSI_Print(YSI_gsPillarsBody1);
		YSI_Print(YSI_gsPillarsBody1);
		YSI_Print(YSI_gsPillarsBody1);
		YSI_Print(YSI_gsPillarsBody1);
	}
	}
}

stock ASCII_EndSection(ASCII_BORDER_STYLE:border)
{
	switch (border)
	{
	case ASCII_BORDER_STYLE_SMALL:
	{
		YSI_Print(YSI_gsSmallBody);
	}
	case ASCII_BORDER_STYLE_LARGE:
	{
		YSI_Print(YSI_gsLargeBody),
		YSI_Print(YSI_gsLargeBody);
	}
	case ASCII_BORDER_STYLE_PILLARS:
	{
		YSI_Print(YSI_gsPillarsBody1),
		YSI_Print(YSI_gsPillarsBody1),
		YSI_Print(YSI_gsPillarsBody1),
		YSI_Print(YSI_gsPillarsBody1),
		YSI_Print("    (oOoOo)                                                         (oOoOo)    "),
		YSI_Print("    J%%%%%L                                                         J%%%%%L    "),
		YSI_Print("   ZZZZZZZZZ                                                       ZZZZZZZZZ   "),
		YSI_Print(YSI_gsPillarsFooter3);
	}
	}
}

stock ASCII_Separate(ASCII_BORDER_STYLE:border)
{
	switch (border)
	{
	case ASCII_BORDER_STYLE_SMALL:
	{
		YSI_Print(YSI_gsSmallHeader);
	}
	case ASCII_BORDER_STYLE_LARGE:
	{
		YSI_Print(YSI_gsLargeHeader);
	}
	case ASCII_BORDER_STYLE_PILLARS:
	{
		YSI_Print(YSI_gsPillarsHeader0),
		YSI_Print(YSI_gsPillarsHeader1),
		YSI_Print(YSI_gsPillarsHeader2),
		YSI_Print(YSI_gsPillarsHeader3),
		YSI_Print(YSI_gsPillarsHeader4),
		YSI_Print(YSI_gsPillarsHeader5),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsFooter0),
		YSI_Print(YSI_gsPillarsFooter1),
		YSI_Print(YSI_gsPillarsFooter2),
		YSI_Print(YSI_gsPillarsFooter3);
	}
	}
}

stock ASCII_EndDisplay(ASCII_BORDER_STYLE:border)
{
	switch (border)
	{
	case ASCII_BORDER_STYLE_SMALL:
	{
		YSI_Print(YSI_gsSmallHeader);
	}
	case ASCII_BORDER_STYLE_LARGE:
	{
		YSI_Print(YSI_gsLargeHeader);
	}
	case ASCII_BORDER_STYLE_PILLARS:
	{
		YSI_Print(YSI_gsPillarsHeader0),
		YSI_Print(YSI_gsPillarsHeader1),
		YSI_Print(YSI_gsPillarsHeader2),
		YSI_Print(YSI_gsPillarsHeader3),
		YSI_Print(YSI_gsPillarsHeader4),
		YSI_Print(YSI_gsPillarsHeader5),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsBody0),
		YSI_Print(YSI_gsPillarsFooter0),
		YSI_Print(YSI_gsPillarsFooter1),
		YSI_Print(YSI_gsPillarsFooter2),
		YSI_Print(YSI_gsPillarsFooter3),
		YSI_Print("  |_________________________________________________________________________|  "),
		YSI_Print(" |___________________________________________________________________________| "),
		YSI_Print("|_____________________________________________________________________________|"),
		YSI_Print("_______________________________________________________________________________");
	}
	}
}

#if defined YSI_TESTS
	#include "y_ascii_tests"
#endif

