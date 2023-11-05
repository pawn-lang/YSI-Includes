#if defined _INC_y_td
	#endinput
#endif
#define _INC_y_td

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

#include "..\..\YSI_Storage\y_xml"

#include "..\..\YSI_Server\y_colours"
#include "..\..\YSI_Coding\y_stringhash"

#include "..\..\YSI_Coding\y_timers"

#include "..\..\YSI_Data\y_iterate"
#include "..\..\YSI_Coding\y_hooks"

#if !defined MAX_TEXT_DRAW_STYLES
	#define MAX_TEXT_DRAW_STYLES        (Style:32)
#endif

#define MAX_TEXT_DRAW_LINE              (128)
#define TEXT_DRAW_NO_NEXT               (Text:-1)

#define TEXT_DRAW_NAN                   (0xFFFFFFFF)

//#define TEXT_DRAW_NO_STYLE_NAME

//#tryinclude <sscanf2>

enum td_align
{
	td_align_none,
	td_align_left,
	td_align_center,
	td_align_centre = td_align_center,
	td_align_right
}

enum e_TD_BITS:(<<= 1)
{
	e_TD_BITS_SHADOW = 0x000000FF,
	e_TD_BITS_OUTLINE = 0x0000FF00,
	e_TD_BITS_ALIGN = 0x000F0000,
	e_TD_BITS_FONT = 0x00F00000,
	e_TD_BITS_BOX = 0x01000000,
	e_TD_BITS_PROP
}

enum E_TD_DATA
{
	#if !defined TEXT_DRAW_NO_STYLE_NAME
		E_TD_DATA_NAME[MAX_XML_ENTRY_NAME char],
	#endif
	E_TD_DATA_HASH,
	Float:E_TD_DATA_X,
	Float:E_TD_DATA_Y,
	Float:E_TD_DATA_LX,
	Float:E_TD_DATA_LY,
	Float:E_TD_DATA_TX,
	Float:E_TD_DATA_TY,
	E_TD_DATA_COLOUR,
	e_TD_BITS:E_TD_DATA_BITS,
	E_TD_DATA_BOX,
	E_TD_DATA_BG,
	E_TD_DATA_TIME,
	Text:E_TD_DATA_USE,
	E_TD_DATA_UPDATE
}

enum E_TD_DISPLAY
{
	E_TD_DISPLAY_TEXT[MAX_TEXT_DRAW_LINE char],
	Float:E_TD_DISPLAY_X,
	Float:E_TD_DISPLAY_Y,
	Text:E_TD_DISPLAY_NEXT,
	Style:E_TD_DISPLAY_STYLE,
	E_TD_DISPLAY_LIFE,
	Text:E_TD_DISPLAY_REAL,
	E_TD_DISPLAY_REVISION, // Used to protect against ABA errors.
	Text:E_TD_DISPLAY_LINKED // Links two TDs together for languages.
}

forward TD_LoadColour();
forward TD_Textdraw();
forward TD_HideForPlayerPub(playerid, Text:textDraw, revision);

static stock
	XML:YSI_g_sXMLRules = NO_XML_FILE,
	YSI_g_sTDData[MAX_TEXT_DRAW_STYLES][E_TD_DATA],
	YSI_g_sTDDisplay[Text:MAX_TEXT_DRAWS][E_TD_DISPLAY],
	//YSI_g_sTDTimers[Text:MAX_TEXT_DRAWS][MAX_PLAYERS],
	// This is actually dual purpose.
	Text:YSI_g_sUnused = Text:0,
	BitArray:YSI_g_sPlayerDraws[MAX_PLAYERS]<_:MAX_TEXT_DRAWS>;
	//Bit:YSI_g_sPlayerDraws[MAX_PLAYERS][Bit_Bits(MAX_TEXT_DRAWS)];

//static stock TD_SetTimer(playerid, Text:td, time, revision)
//{
//	SetTimerEx(__const("TD_HideForPlayer"), time, false, __const("iii"), playerid, _:td, revision);
//}

#define TD_SetTimer(%0,%1,%2,%3) SetTimerEx(__const("TD_HideForPlayerPub"), (%2), false, __const("iii"), (%0), _:(%1), (%3))

/*-------------------------------------------------------------------------*//**
 * <param name="id">Text draw style to check validity of,</param>
 *//*------------------------------------------------------------------------**/

FUNC_PAWNDOC(bool:TD_IsValidStyle(Style:id));
#define TD_IsValidStyle(%1) \
	(Style:0 <= (%1) < MAX_TEXT_DRAW_STYLES && YSI_g_sTDData[(%1)][E_TD_DATA_HASH])

#define _TD_IsValid(%1) \
	((%1) < MAX_TEXT_DRAW_STYLES && YSI_g_sTDData[(%1)][E_TD_DATA_HASH])

#define _TD_TextValid(%0) \
	(Text:0 <= (%0) < Text:MAX_TEXT_DRAWS && YSI_g_sTDDisplay[(%0)][E_TD_DISPLAY_TEXT][0])

//#define TDL_START(%0) new __tdl_base=%1;do{
//#define TDL_END(%0) %1=YSI_g_sTDDisplay[(%1)][E_TD_DISPLAY_LINKED];}while(%1!=__tdl_base);

#define TDL_START(%1) for (new Text:__tdl_base = %1; ; ) {
#define TDL_END(%1) {%1 = YSI_g_sTDDisplay[(%1)][E_TD_DISPLAY_LINKED]; if (%1 == __tdl_base) break;}}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *   Constructor.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HOOK__ OnYSIInit()
{
	if (YSI_g_sXMLRules == NO_XML_FILE)
	{
		YSI_g_sXMLRules = XML_New();
		if (YSI_g_sXMLRules != NO_XML_FILE)
		{
			// y_styles has a copy of these rules.
			XML_AddHandler(YSI_g_sXMLRules, "color", "TD_LoadColour");
			XML_AddHandler(YSI_g_sXMLRules, "colour", "TD_LoadColour");
			XML_AddHandler(YSI_g_sXMLRules, "textdraw", "TD_Textdraw");
			//XML_AddHandler(YSI_g_sXMLRules, "box", "TD_Box");
			//XML_AddHandler(YSI_g_sXMLRules, "background", "TD_Background");
			//XML_AddHandler(YSI_g_sXMLRules, "style", "TD_Style");
		}
	}
	for (new Text:i = Text:0; Text:i < Text:MAX_TEXT_DRAWS; i++)
	{
		YSI_g_sTDDisplay[i][E_TD_DISPLAY_REAL] = Text:INVALID_TEXT_DRAW;
		YSI_g_sTDDisplay[i][E_TD_DISPLAY_NEXT] = i + Text:1;
	}
	YSI_g_sTDDisplay[Text:MAX_TEXT_DRAWS - Text:1][E_TD_DISPLAY_NEXT] = TEXT_DRAW_NO_NEXT;
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="filename">File to parse as a textdraw data file.</param>
 *//*------------------------------------------------------------------------**/

stock TD_Parse(const filename[])
{
	Debug_Print3("TD_Parse called: \"%s\"", filename);
	return XML_Parse(YSI_g_sXMLRules, filename);
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *   XML callback for loading the &lt;colour&gt; tag.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public TD_LoadColour()
{
	Debug_Print2("TD_LoadColour called");
	static
		name[MAX_XML_ENTRY_NAME],
		val[MAX_XML_ENTRY_TEXT];
	new
		colour = 0,
		hash = 0;
	while (XML_GetKeyValue(name, val))
	{
		if (!strcmp(name, "name", true))
		{
			hash = YHash(val, false, hash_bernstein); //COLOUR_NAME_HASH(val);
		}
		else if (!strcmp(name, "hex", true))
		{
			#if defined _inc_sscanf2 || defined unformat
				unformat(val, "x", colour);
			#else
				colour = hexstr(val);
			#endif
		}
		else if (!strcmp(name, "value", true))
		{
			#if defined _inc_sscanf2 || defined unformat
				if (unformat(val, "n", colour))
			#else
				if (ishex(val)) colour = hexstr(val);
				else if (isnumeric(val)) colour = strval(val);
				else
			#endif
					colour = GetColour(val);
		}
	}
	//if (hash) Text_SetColour(hash, colour);
	if (hash) SetColourHash(hash, colour);
	return colour;
}

/*-------------------------------------------------------------------------*//**
 * <param name="x">X position the text will appear at.</param>
 * <param name="y">Y position the text will appear at,</param>
 * <param name="letterX">Letter X size.</param>
 * <param name="letterY">Letter Y size.</param>
 * <param name="textX">Box X size.</param>
 * <param name="textY">Box Y size.</param>
 * <param name="colour">Text colour.</param>
 * <param name="boxColour">Colour of the text box.</param>
 * <param name="bgColour">Colour of the text background.</param>
 * <param name="shadow">Text shadow size.</param>
 * <param name="outline">Text outline size.</param>
 * <param name="align">Text alignment.</param>
 * <param name="font">Text font style.</param>
 * <param name="proportional">Wether to make the text proportional.</param>
 * <param name="box">Wether to use a box.</param>
 * <param name="time">Time for the text to display in ms (0 = infinate).</param>
 * <param name="name">Name of the style.</param>
 * <remarks>
 *   Creates a text draw style structure according to given
 *   parameters, can be used to display any text in the given
 *   style without repeated redefinitions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Style:TD_Create(Float:x = 0.0, Float:y = 0.0, Float:letterX = 0.48, Float:letterY = 1.12, Float:textX = 1280.0, Float:textY = 1280.0, colour = 0xE1E1E1FF, boxColour = 0x80808080, bgColour = 0x000000FF, shadow = 2, outline = 0, align = _:td_align_none, font = 1, bool:proportional = false, bool:box = false, time = 0, const name[] = "\1")
{
	Debug_Print3("Text:TD_Create called: %f, %f, %f, %f, %f, %f, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, \"%s\"", x, y, letterX, letterY, textX, textY, colour, boxColour, bgColour, shadow, outline, align, font, _:proportional, _:box, time, name);
	new
		Style:i = Style:0;
	while (_TD_IsValid(i))
	{
		++i;
	}
	if (i == MAX_TEXT_DRAW_STYLES)
	{
		return MAX_TEXT_DRAW_STYLES;
	}
	#if !defined TEXT_DRAW_NO_STYLE_NAME
		strpack(YSI_g_sTDData[i][E_TD_DATA_NAME], name, MAX_XML_ENTRY_NAME);
	#endif
	YSI_g_sTDData[i][E_TD_DATA_HASH] = BernsteinHash(name);
	YSI_g_sTDData[i][E_TD_DATA_X] = x;
	YSI_g_sTDData[i][E_TD_DATA_Y] = y;
	YSI_g_sTDData[i][E_TD_DATA_LX] = letterX;
	YSI_g_sTDData[i][E_TD_DATA_LY] = letterY;
	YSI_g_sTDData[i][E_TD_DATA_TX] = textX;
	YSI_g_sTDData[i][E_TD_DATA_TY] = textY;
	YSI_g_sTDData[i][E_TD_DATA_COLOUR] = colour;
	YSI_g_sTDData[i][E_TD_DATA_BITS] =
		((box) ? (e_TD_BITS_BOX) : (e_TD_BITS:0)) |
		((proportional) ? (e_TD_BITS_PROP) : (e_TD_BITS:0)) |
		(e_TD_BITS:(shadow << 0) & e_TD_BITS_SHADOW) |
		(e_TD_BITS:(outline << 8) & e_TD_BITS_OUTLINE) |
		(e_TD_BITS:(align << 16) & e_TD_BITS_ALIGN) |
		(e_TD_BITS:(font << 20) & e_TD_BITS_FONT);
	YSI_g_sTDData[i][E_TD_DATA_BOX] = boxColour;
	YSI_g_sTDData[i][E_TD_DATA_BG] = bgColour;
	YSI_g_sTDData[i][E_TD_DATA_TIME] = time;
	YSI_g_sTDData[i][E_TD_DATA_USE] = TEXT_DRAW_NO_NEXT;
	YSI_g_sTDData[i][E_TD_DATA_UPDATE] = -1;
	return Style:i;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *   XML callback for loading the &lt;textdraw&gt; tag.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public TD_Textdraw()
{
	// Set all the default values quickly.
	Debug_Print1("TD_Textdraw called");
	new
		Style:i = TD_Create();
	if (i != MAX_TEXT_DRAW_STYLES)
	{
		Debug_Print5("TD_Textdraw: created %i", _:i);
		static
			name[MAX_XML_ENTRY_NAME],
			val[MAX_XML_ENTRY_TEXT];
		new
			e_TD_BITS:bits = e_TD_BITS:0,
			// Bernstein hash of 1.
			hash = -32;
		// !"\1"
		//YSI_g_sTDData[i][E_TD_DATA_NAME] = 0x01000000;
		while (XML_GetKeyValue(name, val))
		{
			Debug_Print7("TD_Textdraw: loop");
			if (!strcmp(name, "x", true))
			{
				YSI_g_sTDData[i][E_TD_DATA_X] = floatstr(val);
			}
			else if (!strcmp(name, "y", true))
			{
				YSI_g_sTDData[i][E_TD_DATA_Y] = floatstr(val);
			}
			else if (!strcmp(name, "letterx", true))
			{
				YSI_g_sTDData[i][E_TD_DATA_LX] = floatstr(val);
			}
			else if (!strcmp(name, "lettery", true))
			{
				YSI_g_sTDData[i][E_TD_DATA_LY] = floatstr(val);
			}
			else if (!strcmp(name, "textx", true))
			{
				YSI_g_sTDData[i][E_TD_DATA_TX] = floatstr(val);
			}
			else if (!strcmp(name, "texty", true))
			{
				YSI_g_sTDData[i][E_TD_DATA_TY] = floatstr(val);
			}
			else if (!strcmp(name, "alignment", true))
			{
				bits &= ~e_TD_BITS_ALIGN;
				if (!strcmp(val, "left", true)) bits |= e_TD_BITS:(_:td_align_left << 16) & e_TD_BITS_ALIGN;
				else if (!strcmp(val, "right", true)) bits |= e_TD_BITS:(_:td_align_right << 16) & e_TD_BITS_ALIGN;
				else if (!strcmp(val, "center", true) || !strcmp(val, "centre", true)) bits |= e_TD_BITS:(_:td_align_center << 16) & e_TD_BITS_ALIGN;
			}
			else if (!strcmp(name, "color", true) || !strcmp(name, "colour", true))
			{
				Debug_Print2("TD_Textdraw: colour called");
				// This could now be done with the sscanf "n" type for "number".
				#if defined _inc_sscanf2 || defined unformat
					new
						colour = 0;
					if (!unformat(val, "n", colour)) YSI_g_sTDData[i][E_TD_DATA_COLOUR] = colour;
				#else
					if (ishex(val)) YSI_g_sTDData[i][E_TD_DATA_COLOUR] = hexstr(val);
					else if (isnumeric(val)) YSI_g_sTDData[i][E_TD_DATA_COLOUR] = strval(val);
				#endif
					else YSI_g_sTDData[i][E_TD_DATA_COLOUR] = GetColour(val);
			}
			else if (!strcmp(name, "box", true))
			{
				new
					box = strval(val);
				if (box)
				{
					bits |= e_TD_BITS_BOX;
					YSI_g_sTDData[i][E_TD_DATA_BOX] = box;
				}
			}
			else if (!strcmp(name, "shadow", true))
			{
				bits = (bits & ~e_TD_BITS_SHADOW) | (e_TD_BITS:(strval(val)) & e_TD_BITS_SHADOW);
			}
			else if (!strcmp(name, "outline", true))
			{
				bits = (bits & ~e_TD_BITS_OUTLINE) | (e_TD_BITS:(strval(val) << 8) & e_TD_BITS_OUTLINE);
			}
			else if (!strcmp(name, "background", true))
			{
				#if defined _inc_sscanf2 || defined unformat
					new
						colour = 0;
					if (!unformat(val, "n", colour)) YSI_g_sTDData[i][E_TD_DATA_BG] = colour;
				#else
					if (ishex(val)) YSI_g_sTDData[i][E_TD_DATA_BG] = hexstr(val);
					else if (isnumeric(val)) YSI_g_sTDData[i][E_TD_DATA_BG] = strval(val);
				#endif
					else YSI_g_sTDData[i][E_TD_DATA_BG] = GetColour(val);
					Debug_Print5("TD_Textdraw(): Background color: \"%s\", %d, %d: 0x%04x%04x", val, ishex(val), isnumeric(val), YSI_g_sTDData[i][E_TD_DATA_BG] >>> 16, YSI_g_sTDData[i][E_TD_DATA_BG] & 0xFFFF);
			}
			else if (!strcmp(name, "font", true))
			{
				bits = (bits & ~e_TD_BITS_FONT) | (e_TD_BITS:(strval(val) << 20) & e_TD_BITS_FONT);
			}
			else if (!strcmp(name, "proportional", true))
			{
				Debug_Print7("TD_Textdraw: proportional");
				bits |= e_TD_BITS_PROP;
			}
			else if (!strcmp(name, "time", true))
			{
				YSI_g_sTDData[i][E_TD_DATA_TIME] = strval(val);
			}
			else if (!strcmp(name, "name", true))
			{
				#if !defined TEXT_DRAW_NO_STYLE_NAME
					strpack(YSI_g_sTDData[i][E_TD_DATA_NAME], val, MAX_XML_ENTRY_NAME);
				#endif
				hash = BernsteinHash(val);
			}
		}
		YSI_g_sTDData[i][E_TD_DATA_BITS] = bits;
		/*if (!(YSI_g_sTDData[i][E_TD_DATA_NAME] & 0xFF000000))
		{
			YSI_g_sTDData[i][E_TD_DATA_NAME] = 0x01000000;
		}*/
		//YSI_g_sTDData[i][E_TD_DATA_HASH] = BernsteinHash(YSI_g_sTDData[i][E_TD_DATA_NAME]);
		YSI_g_sTDData[i][E_TD_DATA_HASH] = hash;
		Debug_Print5("TD data: %.2f %.2f %.2f %.2f %.2f %.2f %x %d %x %d %d", YSI_g_sTDData[i][E_TD_DATA_X], YSI_g_sTDData[i][E_TD_DATA_Y], YSI_g_sTDData[i][E_TD_DATA_LX], YSI_g_sTDData[i][E_TD_DATA_LY], YSI_g_sTDData[i][E_TD_DATA_TX], YSI_g_sTDData[i][E_TD_DATA_TY], YSI_g_sTDData[i][E_TD_DATA_COLOUR], YSI_g_sTDData[i][E_TD_DATA_BOX], YSI_g_sTDData[i][E_TD_DATA_BG], YSI_g_sTDData[i][E_TD_DATA_TIME], YSI_g_sTDData[i][E_TD_DATA_BITS]);//, YSI_g_sTDData[i][E_TD_DATA_NAME]);
	}
	return _:i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">A style name to get a style index for.</param>
 *//*------------------------------------------------------------------------**/

stock Style:TD_GetNamed(const name[])
{
	new
		hash = BernsteinHash(name);
	Debug_Print3("Text:TD_GetID called: %i", hash);
	new
		Style:i = Style:0;
	while (i != MAX_TEXT_DRAW_STYLES && YSI_g_sTDData[i][E_TD_DATA_HASH] != hash)
	{
		++i;
	}
	return i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="hash">Hash of a style name to get a style index for.</param>
 *//*------------------------------------------------------------------------**/

stock Style:TD_GetID(hash)
{
	Debug_Print3("Text:TD_GetID called: %i", hash);
	new
		Style:i = Style:0;
	while (i != MAX_TEXT_DRAW_STYLES && YSI_g_sTDData[i][E_TD_DATA_HASH] != hash)
	{
		++i;
	}
	return i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to clone.</param>
 * <param name="name">Name of the new style.</param>
 * <remarks>
 *   Copies a text draw style and returns the new handle.
 * </remarks>
 *//*------------------------------------------------------------------------**/
//#if 0
stock Style:TD_Clone(Style:styleID, const name[] = "\1")
{
	Debug_Print3("Text:TD_Clone called: %i, \"%s\"", _:styleID, name);
	if (!TD_IsValidStyle(styleID))
	{
		return MAX_TEXT_DRAW_STYLES;
	}
	new
		Style:i = Style:0;
	while (_TD_IsValid(i))
	{
		i++;
	}
	if (i == MAX_TEXT_DRAW_STYLES)
	{
		return MAX_TEXT_DRAW_STYLES;
	}
	YSI_g_sTDData[i] = YSI_g_sTDData[styleID];
	#if !defined TEXT_DRAW_NO_STYLE_NAME
		strpack(YSI_g_sTDData[i][E_TD_DATA_NAME], name, MAX_XML_ENTRY_NAME);
	#endif
	YSI_g_sTDData[i][E_TD_DATA_HASH] = BernsteinHash(name);
	// memcpy?
	/*YSI_g_sTDData[i][E_TD_DATA_X] = YSI_g_sTDData[styleID][E_TD_DATA_X];
	YSI_g_sTDData[i][E_TD_DATA_Y] = YSI_g_sTDData[styleID][E_TD_DATA_Y];
	YSI_g_sTDData[i][E_TD_DATA_LX] = YSI_g_sTDData[styleID][E_TD_DATA_LX];
	YSI_g_sTDData[i][E_TD_DATA_LY] = YSI_g_sTDData[styleID][E_TD_DATA_LY];
	YSI_g_sTDData[i][E_TD_DATA_TX] = YSI_g_sTDData[styleID][E_TD_DATA_TX];
	YSI_g_sTDData[i][E_TD_DATA_TY] = YSI_g_sTDData[styleID][E_TD_DATA_TY];
	YSI_g_sTDData[i][E_TD_DATA_COLOUR] = YSI_g_sTDData[styleID][E_TD_DATA_COLOUR];
	YSI_g_sTDData[i][E_TD_DATA_BITS] = YSI_g_sTDData[styleID][E_TD_DATA_BITS];
	YSI_g_sTDData[i][E_TD_DATA_BOX] = YSI_g_sTDData[styleID][E_TD_DATA_BOX];
	YSI_g_sTDData[i][E_TD_DATA_BG] = YSI_g_sTDData[styleID][E_TD_DATA_BG];
	YSI_g_sTDData[i][E_TD_DATA_TIME] = YSI_g_sTDData[styleID][E_TD_DATA_TIME];*/
	YSI_g_sTDData[i][E_TD_DATA_USE] = TEXT_DRAW_NO_NEXT;
	YSI_g_sTDData[i][E_TD_DATA_UPDATE] = -1;
	return Style:i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to get the data of.</param>
 * <param name="data">Return array.</param>
 *//*------------------------------------------------------------------------**/

stock TD_GetStyleData(Style:styleID, data[E_TD_DATA])
{
	if (TD_IsValidStyle(styleID))
	{
		data = YSI_g_sTDData[styleID];
		return 1;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="name">Name to give the style.</param>
 *//*------------------------------------------------------------------------**/

stock TD_Name(Style:styleID, const name[])
{
	Debug_Print3("TD_Name called: %i, \"%s\"", _:styleID, name);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	#if !defined TEXT_DRAW_NO_STYLE_NAME
		strpack(YSI_g_sTDData[styleID][E_TD_DATA_NAME], name, MAX_XML_ENTRY_NAME);
	#endif
	YSI_g_sTDData[styleID][E_TD_DATA_HASH] = BernsteinHash(name);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="textID">Text to modify.</param>
 * <param name="x">New horizontal position.</param>
 * <param name="y">New vertical position.</param>
 * <remarks>
 *   Moves a single bit of text, not all with a style.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_TextPosition(Text:textID, Float:x, Float:y)
{
	Debug_Print3("TD_TextPosition called: %i, %i, %i", _:textID, x, y);
	if (!_TD_TextValid(textID))
	{
		return 0;
	}
	TDL_START(textID)
	{
		YSI_g_sTDDisplay[textID][E_TD_DISPLAY_X] = x;
		YSI_g_sTDDisplay[textID][E_TD_DISPLAY_Y] = y;
		TD_UpdateOne(textID, YSI_g_sTDDisplay[textID][E_TD_DISPLAY_STYLE]);
	}
	TDL_END(textID)
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="textID">Text to modify.</param>
 * <param name="x">New horizontal position.</param>
 * <remarks>
 *   Moves a single bit of text, not all with a style.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_TextXPos(Text:textID, Float:x)
{
	Debug_Print3("TD_TextXPos called: %i, %i", _:textID, x);
	if (!_TD_TextValid(textID))
	{
		return 0;
	}
	TDL_START(textID)
	{
		YSI_g_sTDDisplay[textID][E_TD_DISPLAY_X] = x;
		TD_UpdateOne(textID, YSI_g_sTDDisplay[textID][E_TD_DISPLAY_STYLE]);
	}
	TDL_END(textID)
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="textID">Text to modify.</param>
 * <param name="y">New vertical position.</param>
 * <remarks>
 *   Moves a single bit of text, not all with a style.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_TextYPos(Text:textID, Float:y)
{
	Debug_Print3("TD_TextYPos called: %i, %i", _:textID, y);
	if (!_TD_TextValid(textID))
	{
		return 0;
	}
	TDL_START(textID)
	{
		YSI_g_sTDDisplay[textID][E_TD_DISPLAY_Y] = y;
		TD_UpdateOne(textID, YSI_g_sTDDisplay[textID][E_TD_DISPLAY_STYLE]);
	}
	TDL_END(textID)
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="x">New horizontal position.</param>
 * <param name="y">New vertical position.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 * <remarks>
 *   Update is default false to not modify moved texts.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_StylePosition(Style:styleID, Float:x, Float:y)
{
	Debug_Print3("TD_StylePosition called: %i, %i, %i", _:styleID, x, y);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_X] = x;
	YSI_g_sTDData[styleID][E_TD_DATA_Y] = y;
	if (update) TD_Update(styleID, true);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="x">New horizontal position.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 * <remarks>
 *   Update is default false to not modify moved texts.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_StyleXPos(Style:styleID, Float:x)
{
	Debug_Print3("TD_StyleXPos called: %i, %i", _:styleID, x);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_X] = x;
	if (update) TD_Update(styleID, true);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="y">New vertical position.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 * <remarks>
 *   Update is default false to not modify moved texts.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_StyleYPos(Style:styleID, Float:y)
{
	Debug_Print3("TD_StyleYPos called: %i, %i", _:styleID, y);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_Y] = y;
	if (update) TD_Update(styleID, true);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="x">New letter width.</param>
 * <param name="y">New letter height.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 *//*------------------------------------------------------------------------**/

stock TD_LetterSize(Style:styleID, Float:x, Float:y)
{
	Debug_Print3("TD_LetterSize called: %i, %i, %i", _:styleID, x, y);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_LX] = x;
	YSI_g_sTDData[styleID][E_TD_DATA_LY] = y;
	TD_Update(styleID);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="x">New letter width.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 *//*------------------------------------------------------------------------**/

stock TD_LetterX(Style:styleID, Float:x)
{
	Debug_Print3("TD_LetterX called: %i, %i", _:styleID, x);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_LX] = x;
	TD_Update(styleID);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="y">New letter height.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 *//*------------------------------------------------------------------------**/

stock TD_LetterY(Style:styleID, Float:y)
{
	Debug_Print3("TD_LetterY called: %i, %i", _:styleID, y);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_LY] = y;
	TD_Update(styleID);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="x">New text width.</param>
 * <param name="y">New text height.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 *//*------------------------------------------------------------------------**/

stock TD_TextSize(Style:styleID, Float:x, Float:y)
{
	Debug_Print3("TD_TextSize called: %i, %i, %i", _:styleID, x, y);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_TX] = x;
	YSI_g_sTDData[styleID][E_TD_DATA_TY] = y;
	TD_Update(styleID);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="x">New text width.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 *//*------------------------------------------------------------------------**/

stock TD_TextX(Style:styleID, Float:x)
{
	Debug_Print3("TD_TextX called: %i, %i", _:styleID, x);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_TX] = x;
	TD_Update(styleID);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="y">New text height.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 *//*------------------------------------------------------------------------**/

stock TD_TextY(Style:styleID, Float:y)
{
	Debug_Print3("TD_TextY called: %i, %i", _:styleID, y);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_TY] = y;
	TD_Update(styleID);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="alignment">Where to align the text in it's box.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 * <remarks>
 *   Designed to take ta_align enum values and numbers.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_Alignment(Style:styleID, alignment = _:td_align_none)
{
	Debug_Print3("TD_Alignment called: %i, %i", _:styleID, alignment);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_BITS] = (YSI_g_sTDData[styleID][E_TD_DATA_BITS] & ~e_TD_BITS_ALIGN) | (e_TD_BITS:(alignment << 16) & e_TD_BITS_ALIGN);
	TD_Update(styleID);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="colour">New text colour.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 *//*------------------------------------------------------------------------**/

stock TD_Colour(Style:styleID, colour)
{
	Debug_Print3("TD_Colour called: %i, %i", _:styleID, colour);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_COLOUR] = colour;
	TD_Update(styleID);
	return 1;
}

#define TD_Color TD_Colour

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="use">Wether or not to show a box round the text.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 *//*------------------------------------------------------------------------**/

stock TD_UseBox(Style:styleID, bool:use)
{
	Debug_Print3("TD_UseBox called: %i, %i", _:styleID, _:use);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	if (use) YSI_g_sTDData[styleID][E_TD_DATA_BITS] |= e_TD_BITS_BOX;
	else YSI_g_sTDData[styleID][E_TD_DATA_BITS] &= ~e_TD_BITS_BOX;
	TD_Update(styleID);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="colour">New box colour.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 *//*------------------------------------------------------------------------**/

stock TD_BoxColour(Style:styleID, colour)
{
	Debug_Print3("TD_BoxColour called: %i, %i", _:styleID, colour);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_BOX] = colour;
	TD_Update(styleID);
	return 1;
}

#define TD_BoxColor TD_BoxColour

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="size">Size of the letter shadow,</param>
 * <param name="update">Wether to update the appearence for players.</param>
 *//*------------------------------------------------------------------------**/

stock TD_SetShadow(Style:styleID, size)
{
	Debug_Print3("TD_SetShadow called: %i, %i", _:styleID, size);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_BITS] = (YSI_g_sTDData[styleID][E_TD_DATA_BITS] & ~e_TD_BITS_SHADOW) | (e_TD_BITS:(size) & e_TD_BITS_SHADOW);
	TD_Update(styleID);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="size">Size of the letter outline.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 *//*------------------------------------------------------------------------**/

stock TD_SetOutline(Style:styleID, size)
{
	Debug_Print3("TD_SetOutline called: %i, %i", _:styleID, size);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_BITS] = (YSI_g_sTDData[styleID][E_TD_DATA_BITS] & ~e_TD_BITS_OUTLINE) | (e_TD_BITS:(size << 8) & e_TD_BITS_OUTLINE);
	TD_Update(styleID);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="colour">New background (outline/shadow) colour.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 *//*------------------------------------------------------------------------**/

stock TD_BackgroundColour(Style:styleID, colour)
{
	Debug_Print3("TD_BackgroundColour called: %i, %i", _:styleID, colour);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_BG] = colour;
	TD_Update(styleID);
	return 1;
}

#define TD_BackgroundColor TD_BackgroundColour

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="font">New text font style.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 *//*------------------------------------------------------------------------**/

stock TD_Font(Style:styleID, font)
{
	Debug_Print3("TD_Font called: %i, %i", _:styleID, font);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_BITS] = (YSI_g_sTDData[styleID][E_TD_DATA_BITS] & ~e_TD_BITS_FONT) | (e_TD_BITS:(font << 20) & e_TD_BITS_FONT);
	TD_Update(styleID);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="set">Wether to make the letters proportional or not.</param>
 * <param name="update">Wether to update the appearence for players.</param>
 *//*------------------------------------------------------------------------**/

stock TD_SetProportional(Style:styleID, bool:set)
{
	Debug_Print3("TD_SetProportional called: %i, %i", _:styleID, _:set);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	if (set) YSI_g_sTDData[styleID][E_TD_DATA_BITS] |= e_TD_BITS_PROP;
	else YSI_g_sTDData[styleID][E_TD_DATA_BITS] &= ~e_TD_BITS_PROP;
	TD_Update(styleID);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleID">Style to modify.</param>
 * <param name="time">New time for the text to display for.</param>
 * <param name="existing">Whether or not to change the display of existing text draws.</param>
 * <remarks>
 *   Doesn't update existing timed texts, just new ones.  Now does all of them.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_SetTime(Style:styleID, time, bool:existing = false)
{
	Debug_Print3("TD_SetTime called: %i, %i, %i", _:styleID, time, _:existing);
	if (!TD_IsValidStyle(styleID))
	{
		return 0;
	}
	YSI_g_sTDData[styleID][E_TD_DATA_TIME] = time;
	if (existing)
	{
		// Hide this after the given time for all players.
		new
			Text:next = YSI_g_sTDData[styleId][E_TD_DATA_USE],
			Text:last = TEXT_DRAW_NO_NEXT;
		while (next != TEXT_DRAW_NO_NEXT)
		{
			// DO update the revision here!
			new
				index = Bit_Slot(next),
				Bit:mod = Bit_Mask(next),
				revision = ++YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REVISION];
			FOREACH__ (new playerid : Player)
			{
				if (YSI_g_sPlayerDraws[playerid][index] & mod)
				{
					TD_SetTimer(playerid, next, time, revision);
				}
			}
			last = next;
			next = YSI_g_sTDDisplay[next][E_TD_DISPLAY_NEXT];
		}
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <summary>Text:TD_RenderInternal</summary>
 * <param name="text">String to output.</param>
 * <param name="id">Text draw style to render the text in.</param>
 * <param name="slot">the slot the text is stored in.</param>
 * <returns>
 *   TextDraw id.
 * </returns>
 * <remarks>
 *   Basically the application layer, creates a text_draw with the
 *   saved data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined _ALS_TextDrawCreate
	#define TD_TextDrawCreate TextDrawCreate
#else
	native Text:TD_TextDrawCreate(Float:x, Float:y, const text[]) = TextDrawCreate;
#endif

static stock Text:TD_RenderInternal(const text[], const style[E_TD_DATA], Float:x, Float:y)
{
	//Debug_Print4("Text:TD_Render called: \"%s\", %i, %i", text, _:id, _:slot);
	new
		Text:textDraw = TD_TextDrawCreate(x, y, text);
	if (textDraw != Text:INVALID_TEXT_DRAW)
	{
		new
			e_TD_BITS:bits = style[E_TD_DATA_BITS];
		TextDrawLetterSize(textDraw, style[E_TD_DATA_LX], style[E_TD_DATA_LY]);
		TextDrawTextSize(textDraw, style[E_TD_DATA_TX], style[E_TD_DATA_TY]);
		TextDrawAlignment(textDraw, e_TEXT_DRAW_ALIGN:(_:(bits & e_TD_BITS_ALIGN) >> 16));
		TextDrawColor(textDraw, style[E_TD_DATA_COLOUR]);
		TextDrawUseBox(textDraw, !!(bits & e_TD_BITS_BOX));
		TextDrawBoxColor(textDraw, style[E_TD_DATA_BOX]);
		TextDrawSetShadow(textDraw, _:(bits & e_TD_BITS_SHADOW));
		TextDrawSetOutline(textDraw, _:(bits & e_TD_BITS_OUTLINE) >> 8);
		TextDrawBackgroundColor(textDraw, style[E_TD_DATA_BG]);
		TextDrawFont(textDraw, _:(bits & e_TD_BITS_FONT) >> 20);
		TextDrawSetProportional(textDraw, !!(bits & e_TD_BITS_PROP));
	}
	return textDraw;
}

/*-------------------------------------------------------------------------*//**
 * <summary>Text:TD_Render</summary>
 * <param name="text">String to output.</param>
 * <param name="id">Text draw style to render the text in.</param>
 * <param name="slot">the slot the text is stored in.</param>
 * <returns>
 *   TextDraw id.
 * </returns>
 * <remarks>
 *   Basically the application layer, creates a text_draw with the
 *   saved data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Text:TD_Render(const text[], Style:id, Text:slot)
{
	Debug_Print4("Text:TD_Render called: \"%s\", %i, %i", text, _:id, _:slot);
	return TD_RenderInternal(text, YSI_g_sTDData[id], YSI_g_sTDDisplay[slot][E_TD_DISPLAY_X], YSI_g_sTDDisplay[slot][E_TD_DISPLAY_Y]);
}

/*-------------------------------------------------------------------------*//**
 * <param name="id">Style to update for players.</param>
 * <param name="pos">Wether or not to update children's positions.</param>
 * <remarks>
 *   Loops through all texts displayed using the current render style and updates
 *   their real display.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_Update(Style:id, bool:pos = false)
{
	Debug_Print3("TD_Update called: %i, %i", _:id, _:pos);
	if (!TD_IsValidStyle(id))
	{
		return;
	}
	if (pos)
	{
		// Put this all in one "if" block.
		new
			Text:next = YSI_g_sTDData[id][E_TD_DATA_USE],
			Float:x = YSI_g_sTDData[id][E_TD_DATA_X],
			Float:y = YSI_g_sTDData[id][E_TD_DATA_Y];
		while (next != TEXT_DRAW_NO_NEXT)
		{
			YSI_g_sTDDisplay[next][E_TD_DISPLAY_X] = x;
			YSI_g_sTDDisplay[next][E_TD_DISPLAY_Y] = y;
			next = YSI_g_sTDDisplay[next][E_TD_DISPLAY_NEXT];
		}
	}
	// Update the apperance after a load of updates have been applied.
	if (YSI_g_sTDData[id][E_TD_DATA_UPDATE] == -1)
	{
		YSI_g_sTDData[id][E_TD_DATA_UPDATE] = SetTimerEx(__const("TD_UpdateInternal"), 1, false, __const(YSI_gcI), _:id);
	}
}

forward TD_UpdateInternal(Style:id);

public TD_UpdateInternal(Style:id)
{
	new
		Text:next = YSI_g_sTDData[id][E_TD_DATA_USE];
	while (next != TEXT_DRAW_NO_NEXT)
	{
		TD_UpdateOne(next, id);
		next = YSI_g_sTDDisplay[next][E_TD_DISPLAY_NEXT];
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="slot">Text to update.</param>
 * <param name="id">Style to use.</param>
 * <remarks>
 *   Updates a single text's appearance.  Modified to use a timer with a delay of
 *   1ms, to be called after the current slew of updates.  This means that doing
 *   a whole load of modifications at once will all be committed to players at
 *   the same time.  This used to be done with the optional "update" parameter.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_UpdateOne(Text:slot, Style:id)
{
	Debug_Print3("TD_UpdateOne called: %i, %i", _:slot, _:id);
	// DON'T update the revision in here - if you show a TD to a player for 5
	// seconds and change it after 2, they should just get the new version for
	// 3 seconds, it shouldn't reset the timer.
	new
		Text:real = YSI_g_sTDDisplay[slot][E_TD_DISPLAY_REAL];
	TextDrawDestroy(real);
	real = TD_Render(YSI_g_sTDDisplay[slot][E_TD_DISPLAY_TEXT], id, slot);
	YSI_g_sTDDisplay[slot][E_TD_DISPLAY_REAL] = real;
	if (real != Text:INVALID_TEXT_DRAW)
	{
		new
			index = Bit_Slot(slot),
			Bit:mod = Bit_Mask(slot);
		FOREACH__ (new playerid : Player)
		{
			if (YSI_g_sPlayerDraws[playerid][index] & mod)
			{
				TextDrawShowForPlayer(playerid, real);
			}
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="styleId">Text draw style ID you want to remove.</param>
 * <remarks>
 *   Just nulls the name to remove it's active marker.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_Delete(Style:styleId)
{
	Debug_Print3("TD_Delete called: %i", _:styleId);
	if (!TD_IsValidStyle(styleId))
	{
		return 0;
	}
	if (YSI_g_sTDData[styleId][E_TD_DATA_UPDATE] != -1)
	{
		KillTimer(YSI_g_sTDData[styleId][E_TD_DATA_UPDATE]);
		YSI_g_sTDData[styleId][E_TD_DATA_UPDATE] = -1;
	}
	new
		Text:next = YSI_g_sTDData[styleId][E_TD_DATA_USE],
		Text:last = TEXT_DRAW_NO_NEXT;
	// Loop through all the TDs using this style.
	while (next != TEXT_DRAW_NO_NEXT)
	{
		TextDrawDestroy(YSI_g_sTDDisplay[next][E_TD_DISPLAY_REAL]);
		YSI_g_sTDDisplay[next][E_TD_DISPLAY_REAL] = Text:INVALID_TEXT_DRAW;
		YSI_g_sTDDisplay[next][E_TD_DISPLAY_TEXT][0] = '\0';
		++YSI_g_sTDDisplay[next][E_TD_DISPLAY_REVISION];
		new
			index = Bit_Slot(next),
			Bit:mod = ~Bit_Mask(next);
		FOREACH__ (new playerid : Player)
		{
			// TODO: Update.
			/*if (YSI_g_sTDTimers[next][playerid])
			{
				KillTimer(YSI_g_sTDTimers[next][playerid]);
			}
			YSI_g_sTDTimers[next][playerid] = 0;*/
			// Kill the update timer.
			// Mark this player as not having this TD.
			YSI_g_sPlayerDraws[playerid][index] &= mod;
		}
		last = next;
		next = YSI_g_sTDDisplay[next][E_TD_DISPLAY_NEXT];
	}
	// Add the entire style list to the unused list at once.
	if (last != TEXT_DRAW_NO_NEXT)
	{
		// There are items to add.
		YSI_g_sTDDisplay[last][E_TD_DISPLAY_NEXT] = YSI_g_sUnused;
		YSI_g_sUnused = YSI_g_sTDData[styleId][E_TD_DATA_USE];
	}
	// Mark the style as unused.
	YSI_g_sTDData[styleId][E_TD_DATA_USE] = TEXT_DRAW_NO_NEXT;
	#if !defined TEXT_DRAW_NO_STYLE_NAME
		YSI_g_sTDData[styleId][E_TD_DATA_NAME] = 0;
	#endif
	YSI_g_sTDData[styleId][E_TD_DATA_HASH] = 0;
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="textDraw">Text draw to destroy safely.</param>
 * <remarks>
 *   Destroys this text draw only if it is marked for garbage collection.  It
 *   does not however check that no-one can see the text draw, so those people
 *   who can currently see it will loose it.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock TD_TryDestroy(Text:textDraw)
{
	Debug_Print4("TD_TryDestroy called: %i", _:textDraw);
	// Destroy this if it is marked to be garbage collected.
	if (YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_LIFE] & 0x80000000)
	{
		TD_Destroy(textDraw);
		return 1;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="textDraw">Text draw to destroy safely.</param>
 * <remarks>
 *   Optimised for multiple people.  Not very well though...
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_Destroy(Text:textDraw)
{
	Debug_Print3("TD_Destroy called: %i", _:textDraw);
	if (Text:0 <= textDraw < Text:MAX_TEXT_DRAWS)
	{
		TDL_START(textDraw)
		{
			// Find the TD before this one in the style list.
			new
				Style:style = YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_STYLE],
				Text:next = YSI_g_sTDData[style][E_TD_DATA_USE],
				Text:last = TEXT_DRAW_NO_NEXT;
			while (next != TEXT_DRAW_NO_NEXT)
			{
				if (next == textDraw)
				{
					break;
				}
				last = next;
				next = YSI_g_sTDDisplay[next][E_TD_DISPLAY_NEXT];
			}
			// Destroy the SA:MP text draw.
			new
				Text:real = YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REAL];
			YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REAL] = Text:INVALID_TEXT_DRAW;
			YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_TEXT][0] = '\0';
			++YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REVISION];
			if (real != Text:INVALID_TEXT_DRAW)
			{
				// TextDrawDestroy
				TextDrawDestroy(real);
				// Now kill timers for players.
				// TODO: Update.
				new
					index = Bit_Slot(textDraw),
					Bit:mod = ~Bit_Mask(textDraw);
				FOREACH__ (new playerid : Player)
				{
					/*if (YSI_g_sTDTimers[textDraw][playerid])
					{
						KillTimer(YSI_g_sTDTimers[textDraw][playerid]);
					}
					YSI_g_sTDTimers[textDraw][playerid] = 0;*/
					YSI_g_sPlayerDraws[playerid][index] &= mod;
				}
			}
			// Remove from the style use list and add to the unused list.
			if (next == textDraw)
			{
				if (last == TEXT_DRAW_NO_NEXT)
				{
					YSI_g_sTDData[style][E_TD_DATA_USE] = YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_NEXT];
				}
				else
				{
					YSI_g_sTDDisplay[last][E_TD_DISPLAY_NEXT] = YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_NEXT];
				}
				YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_NEXT] = YSI_g_sUnused;
				YSI_g_sUnused = textDraw;
			}
			Debug_CodeX{else Debug_Warning("Orphaned text draw found.");}
		}
		TDL_END(textDraw)
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="td">Text draw to stop updating.</param>
 * <remarks>
 *   Unlinks a text draw from another one, so that updating the other one does
 *   not update this one.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_Unlink(Text:td)
{
	new
		Text:orig = YSI_g_sTDDisplay[td][E_TD_DISPLAY_LINKED],
		Text:next = orig,
		Text:other = td;
	for ( ; ; )
	{
		if (next == td)
		{
			// Unlinking from no list works fine.
			YSI_g_sTDDisplay[other][E_TD_DISPLAY_LINKED] = orig;
			YSI_g_sTDDisplay[td][E_TD_DISPLAY_LINKED] = td;
			return;
		}
		other = next;
		next = YSI_g_sTDDisplay[next][E_TD_DISPLAY_LINKED];
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="base">Text draw whose updates will be propogated.</param>
 * <param name="other">Text draw that will receive a parent's updates.</param>
 * <remarks>
 *   Links two TDs so that manipulating one does the other too.  They are already
 *   linked through their style, but that's only for style updates.  This handles
 *   things like screen position updates etc.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_Link(Text:base, Text:other)
{
	if (YSI_g_sTDDisplay[other][E_TD_DISPLAY_LINKED] != other)
	{
		TD_Unlink(other);
	}
	// This is an unordered linked list.
	YSI_g_sTDDisplay[other][E_TD_DISPLAY_LINKED] = YSI_g_sTDDisplay[base][E_TD_DISPLAY_LINKED];
	YSI_g_sTDDisplay[base][E_TD_DISPLAY_LINKED] = other;
}

/*-------------------------------------------------------------------------*//**
 * <summary>Text:TD_Display</summary>
 * <param name="text">Text to display onscreen.</param>
 * <param name="id">Style to use to style text.</param>
 * <returns>
 *   Internal Text: id, not actual text draw's id.
 * </returns>
 * <remarks>
 *   Generates a text draw for to display to people.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Text:TD_Display(const text[], Style:id, Float:x = (Float:TEXT_DRAW_NAN), Float:y = (Float:TEXT_DRAW_NAN))
{
	if (YSI_g_sUnused == TEXT_DRAW_NO_NEXT)
	{
		return Text:INVALID_TEXT_DRAW;
	}
	if (!TD_IsValidStyle(id))
	{
		return Text:INVALID_TEXT_DRAW;
	}
	// if (x != x)
	// Determine the screen position.
	if (_:x == TEXT_DRAW_NAN)
	{
		YSI_g_sTDDisplay[YSI_g_sUnused][E_TD_DISPLAY_X] = YSI_g_sTDData[id][E_TD_DATA_X];
	}
	else
	{
		YSI_g_sTDDisplay[YSI_g_sUnused][E_TD_DISPLAY_X] = x;
	}
	if (_:y == TEXT_DRAW_NAN)
	{
		YSI_g_sTDDisplay[YSI_g_sUnused][E_TD_DISPLAY_Y] = YSI_g_sTDData[id][E_TD_DATA_Y];
	}
	else
	{
		YSI_g_sTDDisplay[YSI_g_sUnused][E_TD_DISPLAY_Y] = y;
	}
	YSI_g_sTDDisplay[YSI_g_sUnused][E_TD_DISPLAY_STYLE] = id;
	// Render the code to an internal TD.  All TD_Render does is call SA:MP
	// functions, it does no variable sets.
	new
		Text:textDraw = TD_Render(text, id, YSI_g_sUnused);
	if (textDraw == Text:INVALID_TEXT_DRAW)
	{
		return Text:INVALID_TEXT_DRAW;
	}
	YSI_g_sTDDisplay[YSI_g_sUnused][E_TD_DISPLAY_REAL] = textDraw;
	YSI_g_sTDDisplay[YSI_g_sUnused][E_TD_DISPLAY_LINKED] = YSI_g_sUnused;
	// I don't know wether or not to use strpack here.
	//StrCpy(YSI_g_sTDDisplay[YSI_g_sUnused][E_TD_DISPLAY_TEXT], text, MAX_TEXT_DRAW_LINE);
	strpack(YSI_g_sTDDisplay[YSI_g_sUnused][E_TD_DISPLAY_TEXT], text, MAX_TEXT_DRAW_LINE char);
	textDraw = Text:YSI_g_sUnused;
	YSI_g_sUnused = YSI_g_sTDDisplay[YSI_g_sUnused][E_TD_DISPLAY_NEXT];
	// Add to the list of items using this style.
	YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_NEXT] = YSI_g_sTDData[id][E_TD_DATA_USE];
	YSI_g_sTDData[id][E_TD_DATA_USE] = textDraw;
	// Nobody can see it, but don't destroy it.
	YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_LIFE] = 0;
	// Increment this every time this slot is used and cleared.
	++YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REVISION];
	return textDraw;
}

stock Text:TD_DisplayForPlayer(playerid, const text[], Style:id, Float:x = (Float:TEXT_DRAW_NAN), Float:y = (Float:TEXT_DRAW_NAN))
{
	new
		Text:td = TD_Display(text, id, x, y);
	TD_Garbage(td);
	TD_ShowForPlayer(playerid, td);
	return td;
}

stock Text:TD_DisplayForAll(const text[], Style:id, Float:x = (Float:TEXT_DRAW_NAN), Float:y = (Float:TEXT_DRAW_NAN))
{
	new
		Text:td = TD_Display(text, id, x, y);
	TD_Garbage(td);
	TD_ShowForAll(td);
	return td;
}

stock Style:TD_GetDisplayStyle(Text:td)
{
	return YSI_g_sTDDisplay[td][E_TD_DISPLAY_STYLE];
}

/*-------------------------------------------------------------------------*//**
 * <param name="td">The text draw to modify.</param>
 * <param name="text">Text to display onscreen.</param>
 * <remarks>
 *   Changes the text on people's screens quickly.
 *
 *   This function DOES NOT update linked TDs as the point is that they display
 *   the same data in different ways, so will need to be updated in different
 *   ways.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined _ALS_TextDrawSetString
	#define TD_TextDrawSetString TextDrawSetString
#else
	native TD_TextDrawSetString(Text:text, const string[]) = TextDrawSetString;
#endif

stock TD_SetString(Text:td, const text[])
{
	Debug_Print3("TD_SetString called: %i, \"%s\"", _:td, text);
	if (_TD_TextValid(td))
	{
		//StrCpy(YSI_g_sTDDisplay[td][E_TD_DISPLAY_TEXT], text, MAX_TEXT_DRAW_LINE);
		strpack(YSI_g_sTDDisplay[td][E_TD_DISPLAY_TEXT], text, MAX_TEXT_DRAW_LINE char);
		new
			Text:real = YSI_g_sTDDisplay[td][E_TD_DISPLAY_REAL];
		// This may have lost it's real rendering
		if (real == Text:INVALID_TEXT_DRAW)
		{
			return 0;
		}
		// Get the style information for showing this TD.
		TD_TextDrawSetString(real, text);
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <summary>Text:TD_DisplayHashed</summary>
 * <param name="text">Text to display.</param>
 * <param name="hash">Hashed style name for styling.</param>
 *//*------------------------------------------------------------------------**/

stock Text:TD_DisplayHashed(const text[], hash, Float:x = (Float:TEXT_DRAW_NAN), Float:y = (Float:TEXT_DRAW_NAN))
{
	new
		Style:id = TD_GetID(hash);
	if (id != MAX_TEXT_DRAW_STYLES)
	{
		return TD_Display(text, id, x, y);
	}
	return Text:INVALID_TEXT_DRAW;
}

stock Text:TD_DisplayHashedForPlayer(playerid, const text[], hash, Float:x = (Float:TEXT_DRAW_NAN), Float:y = (Float:TEXT_DRAW_NAN))
{
	new
		Style:id = TD_GetID(hash);
	if (id != MAX_TEXT_DRAW_STYLES)
	{
		return TD_DisplayForPlayer(playerid, text, id, x, y);
	}
	return Text:INVALID_TEXT_DRAW;
}

stock Text:TD_DisplayHashedForAll(const text[], hash, Float:x = (Float:TEXT_DRAW_NAN), Float:y = (Float:TEXT_DRAW_NAN))
{
	new
		Style:id = TD_GetID(hash);
	if (id != MAX_TEXT_DRAW_STYLES)
	{
		return TD_DisplayForAll(text, id, x, y);
	}
	return Text:INVALID_TEXT_DRAW;
}

/*-------------------------------------------------------------------------*//**
 * <summary>Text:TD_DisplayNamed</summary>
 * <param name="text">Text to display.</param>
 * <param name="style">Named style to display the text with.</param>
 *//*------------------------------------------------------------------------**/

stock Text:TD_DisplayNamed(const text[], const style[], Float:x = (Float:TEXT_DRAW_NAN), Float:y = (Float:TEXT_DRAW_NAN))
{
	return TD_DisplayHashed(text, BernsteinHash(style), x, y);
}

stock Text:TD_DisplayNamedForPlayer(playerid, const text[], const style[], Float:x = (Float:TEXT_DRAW_NAN), Float:y = (Float:TEXT_DRAW_NAN))
{
	return TD_DisplayHashedForPlayer(playerid, text, BernsteinHash(style), x, y);
}

stock Text:TD_DisplayNamedForAll(const text[], const style[], Float:x = (Float:TEXT_DRAW_NAN), Float:y = (Float:TEXT_DRAW_NAN))
{
	return TD_DisplayHashedForAll(text, BernsteinHash(style), x, y);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to show the text to.</param>
 * <param name="textDraw">ID of the text to show.</param>
 * <remarks>
 *   Now destroys any existing text draws using the same style in
 *   the same place to avoid overlaps.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_ShowForPlayer(playerid, Text:textDraw)
{
	Debug_Print3("TD_ShowForPlayer called: %i, %i", playerid, _:textDraw);
	if (Text:0 <= textDraw < Text:MAX_TEXT_DRAWS && !Bit_GetBit(YSI_g_sPlayerDraws[playerid], _:textDraw))
	{
		new
			Text:real = YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REAL],
			Style:style = YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_STYLE];
		// This may have lost it's real rendering
		if (real == Text:INVALID_TEXT_DRAW)
		{
			if (!YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_TEXT][0])
			{
				// There is no text to render.
				return 0;
			}
			real = TD_Render(YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_TEXT], style, textDraw);
			if (real == Text:INVALID_TEXT_DRAW)
			{
				return 0;
			}
			YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REAL] = real;
		}
		// Now show this for a player.
		TextDrawShowForPlayer(playerid, real);
		Bit_Let(YSI_g_sPlayerDraws[playerid], _:textDraw);
		++YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_LIFE];
		new
			time = YSI_g_sTDData[style][E_TD_DATA_TIME];
		// TODO: Update.
		/*if (YSI_g_sTDTimers[textDraw][playerid])
		{
			KillTimer(YSI_g_sTDTimers[textDraw][playerid]);
		}*/
		if (time)
		{
			//YSI_g_sTDTimers[textDraw][playerid] = SetTimerEx(__const("TD_HideForPlayer"), time, false, __const(YSI_gcII), playerid, _:textDraw);
			TD_SetTimer(playerid, textDraw, time, YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REVISION]);
		}
		return 1;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to hide the text for.</param>
 * <param name="textDraw">Text to hide.</param>
 * <param name="revision">The version of the text draw which existed when this was set.</param>
 * <remarks>
 *   Public so the timer can call it to hide texts with a time set.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public TD_HideForPlayerPub(playerid, Text:textDraw, revision)
{
	// Hide the TD only if it's not changed since last time (avoids ABA errors).
	// It CAN, however, get ABCD...A errors if you manage to change this one
	// over 4,000,000,000 times before the timer is called...
	if (YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REVISION] == revision)
	{
		//if (playerid == INVALID_PLAYER_ID)
		//{
		//	TD_HideForAll(textDraw);
		//}
		//else
		//{
			TD_HideForPlayer(playerid, textDraw);
		//}
	}
}

stock TD_HideForPlayer(playerid, Text:textDraw)
{
	Debug_Print3("TD_HideForPlayer called: %i, %i", playerid, _:textDraw);
	if (IsPlayerConnected(playerid))
	{
		// Find the REAL TD for this player from the base TD.
		TDL_START(textDraw)
		{
			if (Text:0 <= textDraw < Text:MAX_TEXT_DRAWS && Bit_GetBit(YSI_g_sPlayerDraws[playerid], _:textDraw))
			{
				// TODO: Update this to find the correct timer.
				/*if (YSI_g_sTDTimers[textDraw][playerid])
				{
					KillTimer(YSI_g_sTDTimers[textDraw][playerid]);
				}
				YSI_g_sTDTimers[textDraw][playerid] = 0;*/
				//YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_LIFE] = (count & 0x80000000) | ((count & 0x7FFFFFFF) - 1);
				if (--YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_LIFE] == 0x80000000)
				{
					// No-one uses this any more, destroy it.  Looking back on
					// the code, this doesn't seem well implemented at all!
					// Actually itis, ignore me.  I forgot that you have to
					// MANUALLY mark TDs as garbage for collection here.
					TD_Destroy(textDraw);
				}
				else
				{
					Bit_Vet(YSI_g_sPlayerDraws[playerid], _:textDraw);
					TextDrawHideForPlayer(playerid, YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REAL]);
				}
				return 1;
			}
		}
		TDL_END(textDraw)
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="textDraw">Text to show to all players.</param>
 *//*------------------------------------------------------------------------**/

stock TD_ShowForAll(Text:textDraw)
{
	Debug_Print3("TD_ShowForAll called: %i", _:textDraw);
	if (Text:0 <= textDraw < Text:MAX_TEXT_DRAWS)
	{
		new
			Text:real = YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REAL],
			Style:style = YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_STYLE];
		// This may have lost it's real rendering
		if (real == Text:INVALID_TEXT_DRAW)
		{
			if (!YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_TEXT][0])
			{
				// There is no text to render.
				return 0;
			}
			real = TD_Render(YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_TEXT], style, textDraw);
			if (real == Text:INVALID_TEXT_DRAW)
			{
				return 0;
			}
			YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REAL] = real;
		}
		TextDrawShowForAll(real);
		new
			count = 0,
			index = Bit_Slot(textDraw),
			Bit:mod = Bit_Mask(textDraw),
			time = YSI_g_sTDData[style][E_TD_DATA_TIME],
			revision = YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REVISION];
		FOREACH__ (new playerid : Player)
		{
			// Count the number of players with this TD (destroy it if none).
			YSI_g_sPlayerDraws[playerid][index] |= mod;
			++count;
			if (time)
			{
				TD_SetTimer(playerid, textDraw, time, revision);
			}
		}
		if (count)
		{
			// People can see it.
			YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_LIFE] = (YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_LIFE] & 0x80000000) | count;
		}
		else
		{
			TD_TryDestroy(textDraw);
		}
		return 1;
		//}
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="textDraw">Text to hide from all players.</param>
 * <remarks>
 *   Destroys the real text draw if marked for garbage collection.
 *
 *   Hides all linked TDs.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_HideForAll(Text:textDraw)
{
	Debug_Print3("TD_HideForAll called: %i", _:textDraw);
	if (Text:0 <= textDraw < Text:MAX_TEXT_DRAWS)
	{
		TDL_START(textDraw)
		{
			new
				Text:real = YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REAL];
			if (!TD_TryDestroy(textDraw))
			{
				if (real != Text:INVALID_TEXT_DRAW)
				{
					YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_LIFE] = 0;
					new
						index = Bit_Slot(textDraw),
						Bit:inv = ~Bit_Mask(textDraw);//,
						//Bit:inv = ~mod;
					// Hide it for all players but don't destroy it.
					TextDrawHideForAll(real);
					++YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REVISION];
					FOREACH__ (new playerid : Player)
					{
						YSI_g_sPlayerDraws[playerid][index] &= inv;
					}
				}
			}
		}
		TDL_END(textDraw)
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who left.</param>
 * <param name="reason">Why they left.</param>
 * <remarks>
 *   Required to fix bugs in the textdraw system by hiding all
 *   visible ones.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HOOK__ OnPlayerDisconnect(playerid, reason)
{
	for (new i = 0; i < bits<_:MAX_TEXT_DRAWS>; i++)
	{
		new
			Bit:s = YSI_g_sPlayerDraws[playerid][i],
			j = 0,
			ix = i << __COMPILER_BIT_SHIFT;
		while (s)
		{
			// Get rid of data for textdraws which this player can see.  We
			// don't need to actually hide the textdraw as the player has left.
			if (s & Bit:1)
			{
				new
					Text:textDraw = Text:(ix + j);
				/*if (YSI_g_sTDTimers[textDraw][playerid])
				{
					// TODO: Update.
					KillTimer(YSI_g_sTDTimers[textDraw][playerid]);
					YSI_g_sTDTimers[textDraw][playerid] = 0;
				}*/
				if (--YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_LIFE] == 0x80000000)
				{
					TD_Destroy(textDraw);
				}
				//TD_TryDestroy(textDraw);
			}
			s >>>= Bit:1;
			++j;
		}
		YSI_g_sPlayerDraws[playerid][i] = Bit:0;
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="textDraw">Text to mark as garbage.</param>
 * <remarks>
 *   Tells the system to remove a text draw when no-one can see it
 *   anymore to free up text draw slots.
 *
 *   Note that linked TDs don't share garbage status.  This is because I said so,
 *   not for any good reason (other that I can't be bothered to code it up).
 *   Ergo this behaviour is a feature, not a bug!
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock TD_Garbage(Text:textDraw)
{
	Debug_Print3("TD_Garbage called: %i", _:textDraw);
	if (Text:0 <= textDraw < Text:MAX_TEXT_DRAWS)
	{
		if (YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_LIFE] & 0x7FFFFFFF)
		{
			// Players can still see it.
			YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_LIFE] |= 0x80000000;
		}
		else
		{
			// No-one can see it.
			TD_Destroy(textDraw);
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="textDraw">Text to morph from it's current style to another style.</param>
 * <param name="style">The style to morph to.</param>
 * <param name="time">The time to take in this morph.</param>
 * <param name="delay">In how long to start this morph (default now).</param>
 * <remarks>
 *   Entry point for changing the apperance of a text draw to look like another
 *   one.  How smooth this is depends on the difference and the time given.  The
 *   default update time is 50ms (20fps), which isn't too bad.  Don't modify
 *   revision versions in here as if there is a hide timer, it still applies
 *   regardless of what style is currently applied.
 *
 *   No longer takes a playerid parameter - it's just tough but easy to work
 *   around using y_text.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if !defined Y_TD_FRAME_TIME
	#define Y_TD_FRAME_TIME 50
#endif

forward TD_MorphTDInternal(Text:td, Style:from, Style:to, speed, pos, revision);

stock TD_Morph(Text:textDraw, Style:style, time, delay = 0)
{
	Debug_Print2("TD_Morph called: %d %d", TD_IsValidStyle(style), _TD_TextValid(textDraw));
	if (TD_IsValidStyle(style) && _TD_TextValid(textDraw))
	{
		//FOREACH__ (new playerid : PS(players))
		//{
			//TD_MorphInternal(playerid, textDraw, style);
		SetTimerEx(__const("TD_MorphTDInternal"), delay + Y_TD_FRAME_TIME, false, __const("iiiiii"), _:textDraw, _:TD_GetDisplayStyle(textDraw), _:style, time, Y_TD_FRAME_TIME, YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REVISION]); //, YSI_g_sTDDisplay[textDraw][E_TD_DISPLAY_REAL]);
		//SetTimerEx(__const("TD_MorphTDInternal"), delay + Y_TD_FRAME_TIME, false, __const("iiiiii"), _:textDraw, TD_GetDisplayStyle());
		//}
		return 1;
	}
	return 0;
}

public TD_MorphTDInternal(Text:td, Style:from, Style:to, speed, pos, revision)
{
	Debug_Print2("TD_MorphTDInternal called: %d %d %d %d %d %d", _:td, _:from, _:to, speed, pos, revision);
	if (!(Text:0 <= td < Text:MAX_TEXT_DRAWS))
	{
		return 0;
	}
	if (YSI_g_sTDDisplay[td][E_TD_DISPLAY_REVISION] != revision)
	{
		return 0;
	}
	static
		sFrom[E_TD_DATA],
		sTo[E_TD_DATA];
	// Get the current style data.
	TD_GetStyleData(to, sTo);
	new
		Text:real = Text:0,
		index = 0,
		Bit:mask = Bit:0;
	if (pos >= speed)
	{
		// We could add a callback here to indicate that the morph is done.
		// Note that the callback should be BEFORE the TDL loop to include the
		// correct "td" value.
		// Show the TD using the end point only (no interpolation).
		new
			Float:x = sTo[E_TD_DATA_X] - YSI_g_sTDDisplay[td][E_TD_DISPLAY_X],
			Float:y = sTo[E_TD_DATA_Y] - YSI_g_sTDDisplay[td][E_TD_DISPLAY_Y];
		TDL_START(td)
		{
			// Hide this TD for everyone.
			new
				Text:old = YSI_g_sTDDisplay[td][E_TD_DISPLAY_REAL];
			//TextDrawDestroy(real);
			// Render the new version.
			real = TD_RenderInternal(YSI_g_sTDDisplay[td][E_TD_DISPLAY_TEXT], sTo, YSI_g_sTDDisplay[td][E_TD_DISPLAY_X] + x, YSI_g_sTDDisplay[td][E_TD_DISPLAY_Y] + y);
			// Show for all players who had it before.
			index = Bit_Slot(_:td);
			mask = Bit_Mask(_:td);
			FOREACH__ (new playerid : Player)
			{
				if (YSI_g_sPlayerDraws[playerid][index] & mask)
				{
					TextDrawShowForPlayer(playerid, real);
				}
			}
			// Only update the new location pointer.  Things like garbage
			// status stay the same as the TD is technically still visible
			// (even if they are fading it out).
			TextDrawDestroy(old);
			YSI_g_sTDDisplay[td][E_TD_DISPLAY_REAL] = real;
		}
		TDL_END(td)
	}
	else
	{
		// Get the BASE position (linked TDs move REALTIVE to this one, as
		// location is not a style parameter).
		new
			Float:x = (sTo[E_TD_DATA_X] - YSI_g_sTDDisplay[td][E_TD_DISPLAY_X]) * pos / speed,
			Float:y = (sTo[E_TD_DATA_Y] - YSI_g_sTDDisplay[td][E_TD_DISPLAY_Y]) * pos / speed;
		TD_GetStyleData(from, sFrom);
		// Calculate how far between the morph stages we are.
		#define MORPH_TD_FROM_TO(%0) sFrom[E_TD_DATA_%0] += (sTo[E_TD_DATA_%0] - sFrom[E_TD_DATA_%0]) * pos / speed
		MORPH_TD_FROM_TO(LX);
		MORPH_TD_FROM_TO(LY);
		MORPH_TD_FROM_TO(TX);
		MORPH_TD_FROM_TO(TY);
		MORPH_TD_FROM_TO(COLOUR);
		//MORPH_TD_FROM_TO(BITS);
		sFrom[E_TD_DATA_BITS] += e_TD_BITS:(_:(sTo[E_TD_DATA_BITS] - sFrom[E_TD_DATA_BITS]) * pos / speed);
		MORPH_TD_FROM_TO(BOX);
		MORPH_TD_FROM_TO(BG);
		#undef MORPH_TD_FROM_TO
		// Loop through all linked TDs and show them to all players.
		TDL_START(td)
		{
			//print("TDL_Start");
			// Hide this TD for everyone.
			new
				Text:old = YSI_g_sTDDisplay[td][E_TD_DISPLAY_REAL];
			//print("Destroyed");
			// Render the new version.
			real = TD_RenderInternal(YSI_g_sTDDisplay[td][E_TD_DISPLAY_TEXT], sFrom, YSI_g_sTDDisplay[td][E_TD_DISPLAY_X] + x, YSI_g_sTDDisplay[td][E_TD_DISPLAY_Y] + y);
			printf("New real: %d %f %f", _:real, YSI_g_sTDDisplay[td][E_TD_DISPLAY_X] + x, YSI_g_sTDDisplay[td][E_TD_DISPLAY_Y] + y);
			// Show for all players who had it before.
			index = Bit_Slot(_:td);
			mask = Bit_Mask(_:td);
			FOREACH__ (new playerid : Player)
			{
				//print("player %d");
				if (YSI_g_sPlayerDraws[playerid][index] & mask)
				{
					//print("yes");
					TextDrawShowForPlayer(playerid, real);
				}
			}
			TextDrawDestroy(old);
			// Only update the new location pointer.  Things like garbage
			// status stay the same as the TD is technically still visible
			// (even if they are fading it out).
			YSI_g_sTDDisplay[td][E_TD_DISPLAY_REAL] = real;
		}
		TDL_END(td)
		// Even though "td" changes in the loop, the end condition is that "td"
		// is the same as when the loop started, meaning that it's fine to reuse
		// it here.
		SetTimerEx(__const("TD_MorphTDInternal"), Y_TD_FRAME_TIME, false, __const("iiiiii"), _:td, _:from, _:to, speed, pos + Y_TD_FRAME_TIME, revision);
	}
	return 1;
}

#undef TDL_START
#undef TDL_END

