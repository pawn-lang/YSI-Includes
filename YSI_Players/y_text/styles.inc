/**--------------------------------------------------------------------------**\
					=================================
					 y_styles - Text style handling.
					=================================
Description:
	Determines how a piece of text should be shown.
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
	25/02/12:
		First version.
Functions:
	Stock:
		-
	Inline:
		-
Variables:
	Global:
		-
</remarks>
\**--------------------------------------------------------------------------**/

// Load the styles for the current item.  I have decided to completely switch
// over to XML as there are just too many options now to make INI files worth
// the effort.

enum e_STYLE_TYPE (+= 0x10000000)   // ALWAYS ADD!
{
	e_STYLE_TYPE_GT_0 = 0x10000000, // ALWAYS FIRST!
	e_STYLE_TYPE_GT_1,
	e_STYLE_TYPE_GT_2,
	e_STYLE_TYPE_GT_3,
	e_STYLE_TYPE_GT_4,
	e_STYLE_TYPE_GT_5,
	e_STYLE_TYPE_GT_6,
	e_STYLE_TYPE_TD,
	e_STYLE_TYPE_3D,
	// This is the point after which ~n~ is not used for new lines.
	e_STYLE_TYPE_CLIENT,
	e_STYLE_TYPE_PLAYER,
	e_STYLE_TYPE_OTHER,
	e_STYLE_TYPE_DIALOG,
	e_STYLE_TYPE_MASK   = 0xF0000000,
	e_STYLE_TYPE_SHIFT  = 28
}

enum E_STYLE_DATA
{
	e_STYLE_TYPE:E_STYLE_DATA_TYPE = 0,
	E_STYLE_DATA_COLOUR       = 0, // SCM colour (RRGGBBA (only 1 A)).
	E_STYLE_DATA_STYLE        = 0, // GT style (set later).
	E_STYLE_DATA_TIME         = 1, // GT  time.
	Style:E_STYLE_DATA_TD_ID  = 1, // TD style to show this as.
	E_STYLE_DATA_3D_ID        = 1  // 3D style to show this as.
}

enum e_3D_FLAGS
{
	e_3D_FLAGS_VW  = 0x0003FFFF, // Max VWs of 262144 (>500 per player).
	e_3D_FLAGS_DD  = 0x7FFC0000, // Max draw distance of 8192 (1.3x SA).
	e_3D_FLAGS_LOS = 0x80000000,
	e_3D_FLAGS_VW_SHIFT = 0,
	e_3D_FLAGS_DD_SHIFT = 18
}

enum E_3D_DATA
{
	Float:E_3D_DATA_X,
	Float:E_3D_DATA_Y,
	Float:E_3D_DATA_Z,
	E_3D_DATA_ATTACH, // -1 = None, < 500 = player, >= 500 = vehicle + 500.
	e_3D_FLAGS:E_3D_DATA_FLAGS
}

#if !defined MAX_STYLES
	#define MAX_STYLES (MAX_TEXT_ENTRIES)
#endif

#if !defined MAX_3D_STYLES
	#define MAX_3D_STYLES (MAX_STYLES / 4)
#endif

#define STYLES_FORMAT_FILE "YSI/%s_LANG_DATA.yml"

static stock
	YSI_g_sStyleData[MAX_STYLES][E_STYLE_DATA],
	YSI_g_s3DLabelData[MAX_3D_STYLES][E_3D_DATA],
	//YSI_g_s3DBlankData[E_3D_DATA],
	YSI_g_sStyleBlankData[E_STYLE_DATA] = {e_STYLE_TYPE_CLIENT | e_STYLE_TYPE:0x0FF0000A, -1},
	XML:YSI_g_sXMLRules = NO_XML_FILE,
	YSI_g_sCurFile[32] = "\1\0",
	YSI_g_sCur3D;

stock _Style_Init(id)
{
	YSI_g_sStyleData[id] = YSI_g_sStyleBlankData;
}

forward _Styles_SpecialInit();

stock Styles_GetData(index, style[E_STYLE_DATA], label[E_3D_DATA])
{
	if (0 <= index < MAX_STYLES)
	{
		style = YSI_g_sStyleData[index];
		if ((style[E_STYLE_DATA_TYPE] & e_STYLE_TYPE_MASK) == e_STYLE_TYPE_3D)
		{
			label = YSI_g_s3DLabelData[style[E_STYLE_DATA_3D_ID]];
		}
	}
	else
	{
		style = YSI_g_sStyleBlankData;
	}
}

/**--------------------------------------------------------------------------**\
<summary>Styles_EntryTag</summary>
<returns>
	-
</returns>
<remarks>
	Called to load "<entry>" tags from XML style files.
</remarks>
\**--------------------------------------------------------------------------**/

forward Styles_EntryTag();

public Styles_EntryTag()
{
	P:2("Styles_EntryTag called");
	static
		name[MAX_XML_ENTRY_NAME],
		val[MAX_XML_ENTRY_TEXT],
		e_STYLE_TYPE:type = e_STYLE_TYPE_OTHER,
		data,
		colour,
		id,
		time;
	if (!XML_GetParentValue("name", val))
	{
		return 0;
	}
	// "_Text_CheckOwnership" MUST be called before "_Text_LookupName".
	if (!_Text_CheckOwnership(YSI_g_sCurFile, val))
	{
		P:5("Styles_EntryTag: Don't own %s", val);
		// This script doesn't own this text group.
		return 0;
	}
	// Got the name of this group that this text entries is in.
	while (XML_GetKeyValue(name, val))
	{
		if (!strcmp(name, "name", true))
		{
			// Use the parent name to help look this up.  Also check if we are
			// the owner of this group.  Actually, use internal text functions
			// to do this given that it will know what file it is currently
			// loading and has better knowledge of its own internal structure.
			// This means we MUST call a style file parse function from inside
			// y_textint.
			id = _Text_LookupName(val);
			P:5("Styles_EntryTag: %s = %d", val, id);
		}
		else if (!strcmp(name, "type", true) || !strcmp(name, "style", true))
		{
			// The searched for strings are very lenient.
			if (strfind(val, "Client", true) != -1)
			{
				type = e_STYLE_TYPE_CLIENT;
			}
			else if (strfind(val, "Player", true) != -1)
			{
				type = e_STYLE_TYPE_PLAYER;
			}
			else if (strfind(val, "Draw", true) != -1)
			{
				type = e_STYLE_TYPE_TD;
			}
			else if (strfind(val, "3D", true) != -1)
			{
				type = e_STYLE_TYPE_3D;
			}
			else
			{
				// Better "strval" for short numbers.
				new
					tmp = val[0] - '0';
				if (0 <= tmp <= 6)
				{
					type = e_STYLE_TYPE_GT_0 * e_STYLE_TYPE:tmp;
				}
			}
		}
		else if (!strcmp(name, "3d", true))
		{
			data = strval(val);
			type = e_STYLE_TYPE_3D;
		}
		else if (!strcmp(name, "textdraw", true))
		{
			type = e_STYLE_TYPE_TD;
			if (isnumeric(val))
			{
				data = strval(val);
			}
			else
			{
				data = _:TD_GetNamed(val);
			}
		}
		else if (!strcmp(name, "time", true))
		{
			time = strval(val);
		}
		else if (!strcmp(name, "colour", true) || !strcmp(name, "color", true))
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
	if (0 <= id < MAX_STYLES)
	{
		//printf("SAVING %d", id);
		switch (type)
		{
			case e_STYLE_TYPE_GT_0, e_STYLE_TYPE_GT_1, e_STYLE_TYPE_GT_2, e_STYLE_TYPE_GT_3, e_STYLE_TYPE_GT_4, e_STYLE_TYPE_GT_5, e_STYLE_TYPE_GT_6:
			// This doesn't seem to want to work...
			//case e_STYLE_TYPE_GT_0 .. e_STYLE_TYPE_GT_6:
			{
				YSI_g_sStyleData[id][E_STYLE_DATA_TIME] = time;
				// Don't set ANY colours here!
				YSI_g_sStyleData[id][E_STYLE_DATA_TYPE] = type;
			}
			case e_STYLE_TYPE_TD:
			{
				YSI_g_sStyleData[id][E_STYLE_DATA_TYPE] = type;
				YSI_g_sStyleData[id][E_STYLE_DATA_TD_ID] = Style:data;
			}
			default:
			{
				//printf("SAVING %d", id);
				YSI_g_sStyleData[id][E_STYLE_DATA_3D_ID] = -1;
				//printf("SAVING %d", id);
				YSI_g_sStyleData[id][E_STYLE_DATA_TYPE] = e_STYLE_TYPE:(colour >>> 4 ) | type;
				//printf("SAVING %d", id);
			}
			/*case e_STYLE_TYPE_PLAYER:
			{
			}
			case e_STYLE_TYPE_TD:
			{
			}
			case e_STYLE_TYPE_3D:
			{
			}
			case e_STYLE_TYPE_OTHER:
			{
				YSI_g_sStyleData[id] = 
			}*/
		}
	}
	//printf("SAVING %d", id);
	// Return value is not important here.
	return 1;
}

forward Styles_3DTag();

public Styles_3DTag()
{
	P:2("Styles_EntryTag called");
	static
		name[MAX_XML_ENTRY_NAME],
		val[MAX_XML_ENTRY_TEXT],
		#if !defined _inc_sscanf2 && !defined unformat
			tmp,
		#endif
		Float:x,
		Float:y,
		Float:z,
		e_3D_FLAGS:flags;
	if (YSI_g_sCur3D == MAX_3D_STYLES)
	{
		return -1;
	}
	while (XML_GetKeyValue(name, val))
	{
		if (!strcmp(name, "x", true))
		{
			x = floatstr(val);
		}
		else if (!strcmp(name, "y", true))
		{
			y = floatstr(val);
		}
		else if (!strcmp(name, "z", true))
		{
			z = floatstr(val);
		}
		else if (!strcmp(name, "pos", true))
		{
			// A good example of the advantages of sscanf.
			#if defined _inc_sscanf2 || defined unformat
				unformat(val, "p<,>fff", x, y, z);
			#else
				x = floatstr(val);
				tmp = strfind(val, ",") + 1;
				if (tmp)
				{
					y = floatstr(val[tmp]);
					tmp = strfind(val, ",") + 1;
					if (tmp)
					{
						z = floatstr(val[tmp]);
					}
				}
			#endif
		}
		else if (!strcmp(name, "vw", true) || !strcmp(name, "virtualworld", true))
		{
			flags = (flags & ~e_3D_FLAGS_VW) | ((e_3D_FLAGS:strval(val)) & e_3D_FLAGS_VW);
		}
		else if (!strcmp(name, "los", true) || !strcmp(name, "lineofsight", true))
		{
			if (!strcmp(val, "true", true) || strval(val))
			{
				flags |= e_3D_FLAGS_LOS;
			}
			else
			{
				flags &= ~e_3D_FLAGS_LOS;
			}
		}
		else if (!strcmp(name, "drawdistance", true))
		{
			flags = (flags & ~e_3D_FLAGS_DD) | ((e_3D_FLAGS:strval(val) << e_3D_FLAGS_DD_SHIFT) & e_3D_FLAGS_DD);
		}
	}
	YSI_g_s3DLabelData[YSI_g_sCur3D][E_3D_DATA_X] = x;
	YSI_g_s3DLabelData[YSI_g_sCur3D][E_3D_DATA_Y] = y;
	YSI_g_s3DLabelData[YSI_g_sCur3D][E_3D_DATA_Z] = z;
	YSI_g_s3DLabelData[YSI_g_sCur3D][E_3D_DATA_FLAGS] = flags;
	YSI_g_s3DLabelData[YSI_g_sCur3D][E_3D_DATA_ATTACH] = -1;
	return YSI_g_sCur3D++;
}

/**--------------------------------------------------------------------------**\
<summary>Styles_OnScriptInit</summary>
<returns>
	-
</returns>
<remarks>
	Loads all the style files relevant to this script.  Filters by text group in
	the XML callback.  Loops through all publics, then loops through them all
	again to check that the current file hasn't already been loaded.  Despite
	the filtering, it is done this way to ensure that all relevant text draw
	styles are loaded for when we are displaying text.
</remarks>
\**--------------------------------------------------------------------------**/

//hook OnScriptInit()
public _Styles_SpecialInit()
{
	if (YSI_g_sXMLRules == NO_XML_FILE)
	{
		YSI_g_sXMLRules = XML_New();
		if (YSI_g_sXMLRules != NO_XML_FILE)
		{
			// This is copied directly from y_td.
			XML_AddHandler(YSI_g_sXMLRules, "color", "TD_LoadColour");
			XML_AddHandler(YSI_g_sXMLRules, "colour", "TD_LoadColour");
			XML_AddHandler(YSI_g_sXMLRules, "textdraw", "TD_Textdraw");
			//XML_AddHandler(YSI_g_sXMLRules, "box", "TD_Box");
			//XML_AddHandler(YSI_g_sXMLRules, "background", "TD_Background");
			//XML_AddHandler(YSI_g_sXMLRules, "style", "TD_Style");
			XML_AddHandler(YSI_g_sXMLRules, "entry", "Styles_EntryTag");
			XML_AddHandler(YSI_g_sXMLRules, "3d", "Styles_3DTag");
			XML_AddHandler(YSI_g_sXMLRules, "group", NULL);
		}
	}
	YSI_g_sCur3D = 0;
	new
		idx = 0,
		buffer[32],
		b2[32],
		pos;
	// Load the data for ALL the files this script uses (to get textdraw data).
	while ((idx = AMX_GetPublicNameSuffix(idx, buffer, _A<@yX_>)))
	{
		if ((pos = strfind(buffer, "@")) != -1)
		{
			buffer{pos} = '\0';
			if (strcmp(buffer, YSI_g_sCurFile))
			{
				// Different - check for more matches.
				new
					i2 = 0;
				for ( ; ; )
				{
					i2 = AMX_GetPublicNameSuffix(i2, b2, _A<@yX_>);
					if (i2 == idx)
					{
						// Unique entry found.  Load the file.
						strunpack(YSI_g_sCurFile, buffer);
						format(b2, sizeof (b2), STYLES_FORMAT_FILE, YSI_g_sCurFile);
						XML_Parse(YSI_g_sXMLRules, b2);
						break;
					}
					else if (!strcmp(b2, buffer))
					{
						break;
					}
				}
			}
		}
	}
}

/*stock _Styles_ParseOne(file[])
{
	new
		fname[64];
	format(fname, sizeof (fname), STYLES_LANG_DATA, file);
	XML_Parse(YSI_g_sXMLRules, fname);
}*/

/**--------------------------------------------------------------------------**\
<summary>Styles_Reload</summary>
<returns>
	-
</returns>
<remarks>
	Reloads all the string styles in all scripts.  Use sparingly!
</remarks>
\**--------------------------------------------------------------------------**/

stock Styles_Reload()
{
	CallRemoteFunction("_Styles_SpecialInit", "");
}
