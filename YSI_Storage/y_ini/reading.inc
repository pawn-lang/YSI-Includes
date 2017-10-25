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

/*

     ad88888ba                                              
    d8"     "8b              ,d                             
    Y8,                      88                             
    `Y8aaaaa,    ,adPPYba, MM88MMM 88       88 8b,dPPYba,   
      `"""""8b, a8P_____88   88    88       88 88P'    "8a  
            `8b 8PP"""""""   88    88       88 88       d8  
    Y8a     a8P "8b,   ,aa   88,   "8a,   ,a88 88b,   ,a8"  
     "Y88888P"   `"Ybbd8"'   "Y888  `"YbbdP'Y8 88`YbbdP"'   
                                               88           
                                               88           
    
*/

enum e_INI_LINE_TYPE
{
	e_INI_LINE_TYPE_INVALID,
	e_INI_LINE_TYPE_DATALESS,
	e_INI_LINE_TYPE_ENTRY,
	e_INI_LINE_TYPE_CONT,
	e_INI_LINE_TYPE_TAG
}

_Y_INI_STATIC stock
	YSI_g_sParentPos,
	File:YSI_g_sCurFile,
	Alloc:YSI_g_sExtendedLine,
	YSI_g_sExtendedName[MAX_INI_ENTRY_NAME],
	YSI_g_sExtendedType,
	YSI_g_sCurLine[MAX_INI_LINE];

/*

    88b           d88                                                         
    888b         d888                                                         
    88`8b       d8'88                                                         
    88 `8b     d8' 88 ,adPPYYba,  ,adPPYba, 8b,dPPYba,  ,adPPYba,  ,adPPYba,  
    88  `8b   d8'  88 ""     `Y8 a8"     "" 88P'   "Y8 a8"     "8a I8[    ""  
    88   `8b d8'   88 ,adPPPPP88 8b         88         8b       d8  `"Y8ba,   
    88    `888'    88 88,    ,88 "8a,   ,aa 88         "8a,   ,a8" aa    ]8I  
    88     `8'     88 `"8bbdP"Y8  `"Ybbd8"' 88          `"YbbdP"'  `"YbbdP"'  

*/

#define INI_Parse(%1,%2) \
	forward @INI_%1_%2(name[], value[]); \
	@INI_%1_%2(name[], value[])

#define INI:%0[%1](%2) \
	forward @INI_%0_%1(%2); \
	@INI_%0_%1(%2)

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the INI key.</param>
 * <param name="variable">Variable to fill with integer value.</param>
 *//*------------------------------------------------------------------------**/

P:D(INI_Int(const name[],&variable));
#define INI_Int(%1,%2) \
	if (!strcmp((%1), name, true)) return %2 = strval(value)

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the INI key.</param>
 * <param name="variable">Variable to fill with float value.</param>
 *//*------------------------------------------------------------------------**/

P:D(INI_Float(const name[],&Float:variable));
#define INI_Float(%1,%2) \
	if (!strcmp((%1), name, true)) return _:(%2 = floatstr(value))

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the INI key.</param>
 * <param name="variable">Variable to fill with hex value.</param>
 *//*------------------------------------------------------------------------**/

P:D(INI_Hex(const name[],&variable));
#define INI_Hex(%1,%2) \
	if (!strcmp((%1), name, true)) return %2 = hexstr(value)

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the INI key.</param>
 * <param name="variable">Variable to fill with binary value.</param>
 *//*------------------------------------------------------------------------**/

P:D(INI_Bin(const name[],&variable));
#define INI_Bin(%1,%2) \
	if (!strcmp((%1), name, true)) return %2 = binstr(value)

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the INI key.</param>
 * <param name="variable">Variable to fill with string value.</param>
 * <param name="len">Optional string length.</param>
 * <remarks>
 *  The old version of "INI_String" didn't like not having a length.  It gave a
 *  very odd error message too.  This has now been corrected by making the
 *  length parameter optional.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(INI_String(const name[],variable[]));
#define INI_String(%1,%2) \
	if (!strcmp((%1), name, true)) return _:INI_CHECK_LEN:strcpy(%2, value)

#define INI_CHECK_LEN:strcpy(%0,%1,%2) strcpy(%0,%2,%1)

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the INI key.</param>
 * <param name="variable">Variable to fill with string value.</param>
 *//*------------------------------------------------------------------------**/

P:D(INI_Bool(const name[],&bool:variable));
#define INI_Bool(%1,%2) \
	if (!strcmp((%1), name, true)) return %2 = boolstr(value)

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the INI key.</param>
 * <param name="">Variable to fill with array value.</param>
 *//*------------------------------------------------------------------------**/

// Taken from y_iterate.  Safe `sizeof` that corrects `sizeof (x[0])`.
#define F@a$
#define F@b|||
#define F@e:%0|||(%1[%2]%3|||%4)) F@e:%0|||(%1%3|||%4[]))
#define F@f:%0|||(F@g(%1,%5)%3|||) %0|||(%1 %3|||)
#define F@s(%0) (_:F@f:F@e:sizeof F@b|||(%0 F@a$F@b|||))

P:D(INI_Array(const name[],variable[]));
#define INI_Array(%1,%2) \
	if (!strcmp((%1), name, true)) return _INI_Array((%1), strval(value), _:%2[0])

/*

    88        88         88 88            
    88        88   ,d    "" 88            
    88        88   88       88            
    88        88 MM88MMM 88 88 ,adPPYba,  
    88        88   88    88 88 I8[    ""  
    88        88   88    88 88  `"Y8ba,   
    Y8a.    .a8P   88,   88 88 aa    ]8I  
     `"Y8888Y"'    "Y888 88 88 `"YbbdP"'  

*/

#define INI_SkipWhitespace(%0,%1) while (IS_IN_RANGE(%0[%1], '\0' + 1, ' ' + 1)) ++%1

/*-------------------------------------------------------------------------*//**
 * <param name="callback">The callback destination.</param>
 * <param name="format">The function name format.</param>
 * <param name="tag">The tag destination.</param>
 * <param name="input">The tag source.</param>
 * <param name="callbackFormat">The callback parameter specifiers.</param>
 * <param name="remote">Use "CallRemoteFunction".</param>
 * <returns>
 *  Was the function found?
 * </returns>
 * <remarks>
 *  Gets a callback given a partial function name and a tag name.  Also saves
 *  the tag elsewhere.  This might not work as a separate function - it will
 *  need to be in the function called by the function with the inlines in.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(INI_GetCallback(callback,format,tag,input,callbackFormat,remote));
#define INI_GetCallback(%0,%1,%2,%3,%4,%5) \
	( \
		strcpy((%2), (%3)), \
		Inline_Reset((%0)), \
		format(YSI_g_sCurLine, sizeof (YSI_g_sCurLine), (%1), (%2)), \
		Callback_Get(callback_tag:YSI_g_sCurLine, (%0), (%4), (%5)) \
	)

/*

    88b           d88            88                       db        88888888ba  88  
    888b         d888            ""                      d88b       88      "8b 88  
    88`8b       d8'88                                   d8'`8b      88      ,8P 88  
    88 `8b     d8' 88 ,adPPYYba, 88 8b,dPPYba,         d8'  `8b     88aaaaaa8P' 88  
    88  `8b   d8'  88 ""     `Y8 88 88P'   `"8a       d8YaaaaY8b    88""""""'   88  
    88   `8b d8'   88 ,adPPPPP88 88 88       88      d8""""""""8b   88          88  
    88    `888'    88 88,    ,88 88 88       88     d8'        `8b  88          88  
    88     `8'     88 `"8bbdP"Y8 88 88       88    d8'          `8b 88          88  

*/

/*-------------------------------------------------------------------------*//**
 * <param name="filename">The file to load.</param>
 * <param name="remoteFormat">The format string to generate the remote function to
 * pass the data to once loaded.</param>
 * <param name="bFileFirst">The order of the remoteFormat parameters.</param>
 * <param name="bExtra">Send additional data.</param>
 * <param name="extra">Additional data to send.</param>
 * <param name="bLocal">Call local functions instead of global ones.</param>
 * <param name="bPassTag">Pass the tag as an extra parameter not the function
 * name.</param>
 * <param name="bFilter">Apply the tag name filter to all tags or just prefixed
 * ones?</param>
 * <param name="filter">Text to use to search for which tags to load.</param>
 * <remarks>
 *  bFileFirst sets the order and inclusion of the possible remoteFormat
 *  parameters.  If true the format will add the filename first then the 
 *  current tag, if false the order will be reversed.  This can also be used
 *  to exclude one or the other from the function name by setting the required
 *  parameter to be entered first and then only having one %s in the format
 *  sting.  The default order is tag first for languages compatibility.
 *
 *  This function is now EXTENSIVELY documented here:
 *
 *      <a href="http://forum.sa-mp.com/showthread.php?t=485611" />
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:INI_ParseFile(fname[], remoteFormat[], bool:bFileFirst = false, bool:bExtra = false, extra = 0, bool:bLocal = true, bool:bPassTag = false, bool:bFilter = true, filter[] = "", bool:bPassFile = false)
{
	P:3("bool:INI_ParseFile called: \"%s\", \"%s\", %i, %i, %i, %i, %i, %i, \"%s\"", fname, remoteFormat, bFileFirst, bExtra, extra, bLocal, bPassTag, bFilter, filter);
	static
		file[32],
		callback[E_CALLBACK_DATA],
		tag[32],    // The current tag being parsed.
		cbSpec[6],  // The callback specifier.
		cbName[32]; // The callback name format.
	YSI_g_sCurFile = fopen(fname, io_read);
	if (!YSI_g_sCurFile)
		return false;
	new
		rlen,
		p0s, p0e, p1s, p1e, p2s, p2e;
	// Get just the filename.
	YSI_g_sParentPos = strlen(fname);
	while (YSI_g_sParentPos && fname[YSI_g_sParentPos - 1] != '/' && fname[YSI_g_sParentPos - 1] != '\\')
		--YSI_g_sParentPos;
	rlen = YSI_g_sParentPos;
	while (fname[rlen] && fname[rlen] != '.')
		++rlen;
	file[0] = '\0';
	strcat(file, fname[YSI_g_sParentPos], rlen - YSI_g_sParentPos + 1);
	rlen = YSI_g_sParentPos = 0;
	P:5("INI_ParseFile: Opened.");
	bLocal = !bLocal, // Invert for "remote".
	INI_MakeCallbackFormat(bExtra, bPassTag, bPassFile, cbSpec),
	INI_SetupCallbackName(cbName, remoteFormat, file, bFileFirst);
	new
		bool:handle = INI_GetCallback(callback, cbName, tag, "", cbSpec, bLocal);
	YSI_g_sExtendedType = 0;
	while ((rlen = fread(YSI_g_sCurFile, YSI_g_sCurLine)))
	{
		YSI_g_sParentPos += rlen;
		switch (INI_IdentifyLineType(YSI_g_sCurLine, p0s, p0e, p1s, p1e, p2s, p2e))
		{
			case e_INI_LINE_TYPE_INVALID:
			{
				P:W("Invalid line in INI file \"%s\": %s", fname, YSI_g_sCurLine);
			}
			case e_INI_LINE_TYPE_DATALESS:
			{
				// Do nothing.
			}
			case e_INI_LINE_TYPE_TAG:
			{
				// A new tag.
				Callback_Restore(callback),
				Callback_Release(callback),
				// First, check if it is a tag we might care about.
				YSI_g_sCurLine[p0e] = '\0';
				if (YSI_g_sCurLine[p0s] == '@' && YSI_g_sCurLine[p0s + 1] == '@' && (p0e = strfind(YSI_g_sCurLine, "-")) != -1)
				{
					// Check if the current tag is one of the ones we want to
					// filer for.  The "@@" prefix is the "filterable" prefix.
					// If there is no filter then everything will be loaded.
					if (p0e == p0s + 2 || !YSI_g_sCurLine[p0e + 1])
					{
						P:W("Invalid line in INI file \"%s\": %s", fname, YSI_g_sCurLine);
						continue;
					}
					YSI_g_sCurLine[p0e] = '\0';
					if (bFilter && strcmp(YSI_g_sCurLine[p0s + 2], filter))
					{
						// Only skip this if filtering is enabled.  We can't put
						// the "bFilter" check higher or the "-" won't be found
						// to resolve the tag name accurately.
						handle = false;
						continue;
					}
					p0s = p0e + 1;
				}
				// This is a tag we can use, is there a handler for it?
				// Is this based on another tag?  If so recurse and do that one
				// first.
				new
					parent[32];
				YSI_g_sCurLine[p1e] = '\0', strcat(parent, YSI_g_sCurLine[p1s]);
				if ((handle = INI_GetCallback(callback, cbName, tag, YSI_g_sCurLine[p0s], cbSpec, bLocal)) && p1s != p1e)
				{
					// No point recursing if there's no handler is there?
					if (!INI_DoParentTag(parent, file, callback, bExtra, extra, bPassTag, tag, bFilter, filter, bPassFile))
						P:W("Invalid hierarchy in INI file: \"%s\" for tag \"%s\"", fname, tag);
					fseek(YSI_g_sCurFile, YSI_g_sParentPos, seek_start);
				}
			}
			case e_INI_LINE_TYPE_CONT:
			{
				// Do nothing, wait for the rest of the line.
			}
			case e_INI_LINE_TYPE_ENTRY:
			{
				if (!handle)
				{
					if (YSI_g_sExtendedLine)
					{
						free(YSI_g_sExtendedLine),
						YSI_g_sExtendedLine = NO_ALLOC,
						YSI_g_sExtendedName[0] = '\0';
					}
					continue;
				}
				else if (YSI_g_sExtendedLine)
				{
					if (Malloc_Get(YSI_g_sExtendedLine, 1) == '@')
					{
						P:E("Binary arrays cannot use continuation lines.");
					}
					else if (bExtra)
					{
						if (bPassFile)
						{
							if (bPassTag) Callback_Call(callback, extra, file, tag, YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
							else          Callback_Call(callback, extra, file,      YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
						}
						else
						{
							if (bPassTag) Callback_Call(callback, extra,       tag, YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
							else          Callback_Call(callback, extra,            YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
						}
					}
					else
					{
						if (bPassFile)
						{
							if (bPassTag) Callback_Call(callback,        file, tag, YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
							else          Callback_Call(callback,        file,      YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
						}
						else
						{
							if (bPassTag) Callback_Call(callback,              tag, YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
							else          Callback_Call(callback,                   YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
						}
					}
					free(YSI_g_sExtendedLine),
					YSI_g_sExtendedLine = NO_ALLOC,
					YSI_g_sExtendedName[0] = '\0';
				}
				else
				{
					// Skip lines starting with `@` here.  They indicate packed
					// array data, which is only read by using `INI_Array`.
					if (YSI_g_sCurLine[p0s] == '@')
						continue;
					// Standard key-value pair.
					YSI_g_sCurLine[p0e] = YSI_g_sCurLine[p1e] = '\0';
					if (bExtra)
					{
						if (bPassFile)
						{
							if (bPassTag) Callback_Call(callback, extra, file, tag, YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
							else          Callback_Call(callback, extra, file,      YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
						}
						else
						{
							if (bPassTag) Callback_Call(callback, extra,       tag, YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
							else          Callback_Call(callback, extra,            YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
						}
					}
					else
					{
						if (bPassFile)
						{
							if (bPassTag) Callback_Call(callback,        file, tag, YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
							else          Callback_Call(callback,        file,      YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
						}
						else
						{
							if (bPassTag) Callback_Call(callback,              tag, YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
							else          Callback_Call(callback,                   YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
						}
					}
				}
			}
		}
		// Don't put any code down here (at the end of the loop).
	}
	return
		Callback_Restore(callback),
		Callback_Release(callback),
		fclose(YSI_g_sCurFile),
		true;
}

/*-------------------------------------------------------------------------*//**
 * <param name="filename">The file to load.</param>
 * <param name="bExtra">Send additional data.</param>
 * <param name="extra">Additional data to send.</param>
 * <param name="bLocal">Call local functions instead of gloabal ones.</param>
 * <returns>
 *  INI_ParseFile
 * </returns>
 * <remarks>
 *  Wrapper for INI_ParseFile to use standard API features so people can
 *  worry even less.  Designed for use with INI_Parse.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:INI_Load(filename[], bool:bExtra = false, extra = 0, bool:bLocal = true)
{
	P:3("bool:INI_Load called: \"%s\", %i, %i, %i", filename, _:bExtra, extra, _:bLocal);
	return INI_ParseFile(filename, "@INI_%s_%s", .bFileFirst = true, .bExtra = bExtra, .extra = extra, .bLocal = bLocal);
}

/*

    88          88                               88    ad88              
    88          88                         ,d    ""   d8"                
    88          88                         88         88                 
    88  ,adPPYb,88  ,adPPYba, 8b,dPPYba, MM88MMM 88 MM88MMM 8b       d8  
    88 a8"    `Y88 a8P_____88 88P'   `"8a  88    88   88    `8b     d8'  
    88 8b       88 8PP""""""" 88       88  88    88   88     `8b   d8'   
    88 "8a,   ,d88 "8b,   ,aa 88       88  88,   88   88      `8b,d8'    
    88  `"8bbdP"Y8  `"Ybbd8"' 88       88  "Y888 88   88        Y88'     
                                                                d8'      
                                                               d8'       

*/

/*-------------------------------------------------------------------------*//**
 * <param name="str">The string you want to type analyse.</param>
 * <param name="p0s">Start of part 0.</param>
 * <param name="p0e">End of part 0.</param>
 * <param name="p1s">Start of part 1.</param>
 * <param name="p1e">End of part 1.</param>
 * <param name="p2s">Start of part 2.</param>
 * <param name="p2e">End of part 2.</param>
 * <param name="cont">Is this a line continuation?</param>
 * <returns>
 *  e_INI_LINE_TYPE
 * </returns>
 * <remarks>
 *  This function's signature is so long that I put it on a separate line.  This
 *  takes a line and determines what it is and where the parts are.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock e_INI_LINE_TYPE:
	INI_IdentifyLineType(str[MAX_INI_LINE], &p0s, &p0e, &p1s, &p1e, &p2s, &p2e)
{
	// Reset everything.
	p0s = p0e = p1s = p1e = p2s = p2e = 0;
	// Do this purely with a single main loop, and a state machine.
	new
		end,
		e_INI_LINE_TYPE:ret = e_INI_LINE_TYPE_DATALESS,
		pos;
	// If there is memory allocated for a line continuation, that means the
	// previous line ended with '\\', so this line is just part of that one,
	// regardless of what it contains.
	if (YSI_g_sExtendedLine)
		goto state_in_continue_line;
	INI_SkipWhitespace(str, pos);
	switch (str[pos++])
	{
		case '\0': return e_INI_LINE_TYPE_DATALESS;
		case  ';': goto state_in_comment;
		case  '[': goto state_in_tag;
		case '\\':
			if (str[pos])
			{
				p0s = pos - 1,
				end = ++pos;
			}
			else return e_INI_LINE_TYPE_INVALID;
		case '=': return e_INI_LINE_TYPE_INVALID;
		default: p0s = pos - 1;
	}
	// Default end point, for single-character lines.
	end = pos;
//state_in_entry: // Default (fall-through).
	// Get the key.
	for ( ; ; ) switch (str[pos++])
	{
		case '\0', ';':
			return e_INI_LINE_TYPE_INVALID;      // No value.
		case '\\':
			if (str[pos]) end = ++pos;           // Skip next character too.
			else return e_INI_LINE_TYPE_INVALID; // Escaping nothing.
		case '=':
			break;
		case '\1' .. ' ':
			{} // Whitespace, skip it.
		default:
			end = pos;  // Characters, save this position.
	}
	p0e = end;
state_in_continue_line:
	// See what comes next.
	INI_SkipWhitespace(str, pos);
	p1s = end = pos;
	for ( ; ; ) switch (str[pos++])
	{
		case '\0':
			if (YSI_g_sExtendedLine)
			{
				p1e = end,
				ret = e_INI_LINE_TYPE_ENTRY;
				goto state_in_continuation;
			}
			else
				return p1e = end, e_INI_LINE_TYPE_ENTRY;
		case  ';':
		{
			p1e = end,
			ret = e_INI_LINE_TYPE_ENTRY;
			goto state_in_comment;
		}
		case '\\':
		{
			// Only allow ';' to immediately follow '\\'.
			end = pos - 1;
			switch (str[pos])
			{
#if defined Y_INI_NO_ESCAPES
				case ';':
					end = ++pos;
#else
				case 'n':
					str[pos] = '\n',
					strdel(str[pos - 1], 0, 1),
					end = pos;
				case 'r':
					str[pos] = '\r',
					strdel(str[pos - 1], 0, 1),
					end = pos;
				case 't':
					str[pos] = '\t',
					strdel(str[pos - 1], 0, 1),
					end = pos;
				case '\\':
					strdel(str[pos - 1], 0, 1),
					end = pos;
				case ';':
					strdel(str[pos - 1], 0, 1),
					end = pos;
#endif
				default: for ( ; ; ) switch (str[pos])
				{
					case '\0', '\r', '\n':
					{
						p1e = end,
						ret  = e_INI_LINE_TYPE_CONT;
						goto state_in_continuation;
					}
					case ';':
					{
						// We saw a comment, but separated from '\\' by at least one
						// space.  This means we have a line continuation that also
						// has a comment at the end.
						p1e = end,
						ret  = e_INI_LINE_TYPE_CONT;
						goto state_in_comment;
					}
					case ' ', '\t':
					{
						++pos;
						continue;
					}
					default:
					{
						end = ++pos;
						break;
					}
				}
			}
		}
		case '\1' .. ' ': {} // Whitespace, skip it.
		default: end = pos;  // Characters, save this position.
	}
state_in_tag:
	// Get the tag name.
	INI_SkipWhitespace(str, pos);
	p0s = pos;
	for ( ; ; ) switch (str[pos++])
	{
		case '\0', ';':
			return e_INI_LINE_TYPE_INVALID;      // No tag end.
		case '\\':
			if (str[pos]) end = ++pos;           // Skip next character too.
			else return e_INI_LINE_TYPE_INVALID; // Escaping nothing.
		case ']':
			if (end) break;                      // End of the tag.
			else return e_INI_LINE_TYPE_INVALID; // Tag is empty.
		case '\1' .. ' ': {} // Whitespace, skip it.
		default: end = pos;  // Characters, save this position.
	}
	p0e = end;
	// See what comes next.
	INI_SkipWhitespace(str, pos);
	switch (str[pos++])
	{
		case '\0': return e_INI_LINE_TYPE_TAG; // Line over.
		case  ';':
		{
			// Skip over the comments.
			ret = e_INI_LINE_TYPE_TAG;
			goto state_in_comment;
		}
		case  ':': {}
		default  : return e_INI_LINE_TYPE_INVALID; // Unexpected characters.
	}
	// Get the inheritance.
	INI_SkipWhitespace(str, pos);
	if (!str[pos]) return e_INI_LINE_TYPE_INVALID; // No parent tag.
	p1s = pos;
	while (str[pos] > ' ') ++pos;
	p1e = pos;
	INI_SkipWhitespace(str, pos);
	switch (str[pos++])
	{
		case '\0': return e_INI_LINE_TYPE_TAG;     // Line over.
		case  ';': ret  = e_INI_LINE_TYPE_TAG;
		default  : return e_INI_LINE_TYPE_INVALID; // Unexpected characters.
	}
state_in_comment:
	INI_SkipWhitespace(str, pos);
	if (str[pos])
	{
		p2s = pos,
		// Non-empty comment.
		pos = strlen(str);
		while (pos-- && str[pos] <= ' ') {}
		p2e = pos + 1;
	}
	if (ret != e_INI_LINE_TYPE_CONT && !YSI_g_sExtendedLine)
		return ret;
	// Fall through to handle continuations before comments.
state_in_continuation:
	// We get here if a line ended with `\\`.  We need to copy the data from
	// this line in to allocated space.
	if (!YSI_g_sExtendedName[0])
	{
		// Haven't yet stored the name of this line.  Do so.
		end = str[p0e],
		str[p0e] = '\0',
		strcpy(YSI_g_sExtendedName, str[p0s]),
		str[p0e] = end;
	}
	// Get the length of this new part.
	pos = p1e - p1s;
	if (YSI_g_sExtendedLine)
	{
		// Enough space for the new string, the old string, the length, and the
		// NULL.
		if (pos + mget(YSI_g_sExtendedLine, 0) + 2 > Malloc_SlotSize(YSI_g_sExtendedLine))
		{
			// Not enough memory - reallocate.
			YSI_g_sExtendedLine = realloc(YSI_g_sExtendedLine, Malloc_SlotSize(YSI_g_sExtendedLine) + MAX_INI_LINE, false);
			if (!YSI_g_sExtendedLine)
			{
				P:E("Could not allocate memory for continuation line.");
				return e_INI_LINE_TYPE_INVALID;
			}
		}
	}
	else
	{
		// There was no previous allocation, implying this the first line of a
		// continuation.
		YSI_g_sExtendedLine = malloc(MAX_INI_LINE + 1, false);
		if (!YSI_g_sExtendedLine)
		{
			P:E("Could not allocate memory for continuation line.");
			return e_INI_LINE_TYPE_INVALID;
		}
		mset(YSI_g_sExtendedLine, 0, 0);
	}
	return
		// Copy the string over.
		end = str[p1e],
		str[p1e] = '\0',
		msets(YSI_g_sExtendedLine, mget(YSI_g_sExtendedLine, 0) + 1, str[p1s]),
		str[p1e] = end,
		// Store the new length.
		mset(YSI_g_sExtendedLine, 0, mget(YSI_g_sExtendedLine, 0) + pos),
		ret;
}

/*

    88                                                                88  
    88              ,d                                                88  
    88              88                                                88  
    88 8b,dPPYba, MM88MMM ,adPPYba, 8b,dPPYba, 8b,dPPYba,  ,adPPYYba, 88  
    88 88P'   `"8a  88   a8P_____88 88P'   "Y8 88P'   `"8a ""     `Y8 88  
    88 88       88  88   8PP""""""" 88         88       88 ,adPPPPP88 88  
    88 88       88  88,  "8b,   ,aa 88         88       88 88,    ,88 88  
    88 88       88  "Y888 `"Ybbd8"' 88         88       88 `"8bbdP"Y8 88  

*/

/*-------------------------------------------------------------------------*//**
 * <param name="fmat">The format destination.</param>
 * <param name="remoteFormat">The source format.</param>
 * <param name="filename">The file we are currently parsing.</param>
 * <param name="bFileFirst">The format parameter ordering.</param>
 * <remarks>
 *  Generates a partial function name for processing callbacks.  Includes the
 *  filename and a placeholder for the tag name.  This now takes extra
 *  characters in to account and strips or converts bits:
 *
 *      some/dir/file name.ext
 *
 *  Becomes:
 *
 *      file_name
 *
 *  Before being formatted in to the specified remote format.  The filename
 *  also takes in to account "/" directory separators and "\\" ones on Windows.
 *
 *  Because the	majority of this function is concerned with formatting just part
 *  of the function name correctly, it short-circuits if it detects that there
 *  is no place for the function name to go.
 *
 *  This is quite a complex function, but is only called once per file parse.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_INI_STATIC stock INI_SetupCallbackName(fmat[32], const remoteFormat[], filename[], const bool:bFileFirst)
{
	// Make the secondary format.
	if (bFileFirst)
		format(fmat, sizeof (fmat), remoteFormat, filename, "%s");
	else
		format(fmat, sizeof (fmat), remoteFormat, "%s", filename);
	// Add spaces as "_".
	new
		pos = -1;
	while ((pos = strfind(fmat, " ", false, pos + 1)) != -1)
		fmat[pos] = '_';
	return 1;
}

_Y_INI_STATIC stock INI_MakeCallbackFormat(const bool:bExtra, const bool:bPassTag, const bool:bPassFile, callbackFormat[6])
{
	if (bExtra)
	{
		if (bPassFile)
		{
			if (bPassTag) callbackFormat = _F<issss>;
			else          callbackFormat = _F<isss>;
		}
		else
		{
			if (bPassTag) callbackFormat = _F<isss>;
			else          callbackFormat = _F<iss>;
		}
	}
	else
	{
		if (bPassFile)
		{
			if (bPassTag) callbackFormat = _F<ssss>;
			else          callbackFormat = _F<sss>;
		}
		else
		{
			if (bPassTag) callbackFormat = _F<sss>;
			else          callbackFormat = _F<ss>;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="filename">The file to load.</param>
 * <param name="remoteFormat">The format string to generate the remote function
 * t pass the data to once loaded.</param>
 * <param name="bFileFirst">The order of the remoteFormat parameters.</param>
 * <param name="bExtra">Send additional data.</param>
 * <param name="extra">Additional data to send.</param>
 * <param name="bLocal">Call local functions instead of global ones.</param>
 * <param name="bPassTag">Pass the tag as an extra parameter not the function
 * name.</param>
 * <param name="bFilter">Apply the tag name filter to all tags or just prefixed
 * ones?</param>
 * <param name="filter">Text to use to search for which tags to load.</param>
 * <remarks>
 *  bFileFirst sets the order and inclusion of the possible remoteFormat
 *  parameters.  If true the format will add the filename first then the 
 *  current tag, if false the order will be reversed.  This can also be used
 *  to exclude one or the other from the function name by setting the required
 *  parameter to be entered first and then only having one %s in the format
 *  sting.  The default order is tag first for languages compatibility.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock INI_DoParentTag(const search[], const file[], callback[E_CALLBACK_DATA], bool:bExtra, extra, bool:bPassTag, tag[], bool:bFilter, filter[], bool:bPassFile)
{
	// The bulk of this function is basically the same as INI_ParseFile (which
	// is a shame as it is a symptom of poor, unmaintainable code).
	fseek(YSI_g_sCurFile, 0, seek_start); // Jump back to the start.
	P:4("bool:INI_DoParentTag called: \"%s\", %i, %i, %i, %i, \"%s\"", search, bExtra, extra, bPassTag, bFilter, filter);
	new
		epos = YSI_g_sParentPos,
		bool:handle = false,
		p0s, p0e, p1s, p1e, p2s, p2e;
	YSI_g_sParentPos = 0;
	while ((YSI_g_sParentPos += fread(YSI_g_sCurFile, YSI_g_sCurLine)) < epos)
	{
		switch (INI_IdentifyLineType(YSI_g_sCurLine, p0s, p0e, p1s, p1e, p2s, p2e))
		{
			case e_INI_LINE_TYPE_INVALID, e_INI_LINE_TYPE_DATALESS: {}
			case e_INI_LINE_TYPE_TAG:
			{
				// A new tag.
				// First, check if it is a tag we might care about.
				YSI_g_sCurLine[p0e] = '\0';
				if (YSI_g_sCurLine[p0s] == '@' && YSI_g_sCurLine[p0s + 1] == '@' && (p0e = strfind(YSI_g_sCurLine, "-")) != -1)
				{
					// Check if the current tag is one of the ones we want to
					// filer for.  The "@@" prefix is the "filterable" prefix.
					// If there is no filter then everything will be loaded.
					if (p0e == p0s + 2 || !YSI_g_sCurLine[p0e + 1]) continue;
					YSI_g_sCurLine[p0e] = '\0';
					if (bFilter && strcmp(YSI_g_sCurLine[p0s + 2], filter))
					{
						// Only skip this if filtering is enabled.  We can't put
						// the "bFilter" check higher or the "-" won't be found
						// to resolve the tag name accurately.
						continue;
					}
					p0s = p0e + 1;
				}
				if (!strcmp(YSI_g_sCurLine[p0s], search))
				{
					handle = true;
					if (p1s != p1e)
					{
						new
							parent[32];
						YSI_g_sCurLine[p1e] = '\0',
						strcat(parent, YSI_g_sCurLine[p1s]);
						if (!INI_DoParentTag(parent, file, callback, bExtra, extra, bPassTag, tag, bFilter, filter, bPassFile))
						{
							return
								YSI_g_sParentPos = epos,
								false;
						}
						fseek(YSI_g_sCurFile, YSI_g_sParentPos, seek_start);
					}
				}
				else if (handle)
				{
					// Parent tag over.
					return
						YSI_g_sParentPos = epos,
						true;
				}
			}
			case e_INI_LINE_TYPE_CONT:
			{
				// Do nothing, wait for the rest of the line.
			}
			case e_INI_LINE_TYPE_ENTRY:
			{
				if (!handle)
				{
					if (YSI_g_sExtendedLine)
					{
						free(YSI_g_sExtendedLine),
						YSI_g_sExtendedLine = NO_ALLOC,
						YSI_g_sExtendedName[0] = '\0';
					}
					continue;
				}
				else if (YSI_g_sExtendedLine)
				{
					if (Malloc_Get(YSI_g_sExtendedLine, 1) == '@')
					{
						P:E("Binary arrays cannot use continuation lines.");
					}
					else if (bExtra)
					{
						if (bPassFile)
						{
							if (bPassTag) Callback_Call(callback, extra, file, tag, YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
							else          Callback_Call(callback, extra, file,      YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
						}
						else
						{
							if (bPassTag) Callback_Call(callback, extra,       tag, YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
							else          Callback_Call(callback, extra,            YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
						}
					}
					else
					{
						if (bPassFile)
						{
							if (bPassTag) Callback_Call(callback,        file, tag, YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
							else          Callback_Call(callback,        file,      YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
						}
						else
						{
							if (bPassTag) Callback_Call(callback,              tag, YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
							else          Callback_Call(callback,                   YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
						}
					}
					free(YSI_g_sExtendedLine),
					YSI_g_sExtendedLine = NO_ALLOC,
					YSI_g_sExtendedName[0] = '\0';
				}
				else
				{
					// Skip lines starting with `@` here.  They indicate packed
					// array data, which is only read by using `INI_Array`.
					if (YSI_g_sCurLine[p0s] == '@')
						continue;
					// Standard key-value pair.
					YSI_g_sCurLine[p0e] = YSI_g_sCurLine[p1e] = '\0';
					if (bExtra)
					{
						if (bPassFile)
						{
							if (bPassTag) Callback_Call(callback, extra, file, tag, YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
							else          Callback_Call(callback, extra, file,      YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
						}
						else
						{
							if (bPassTag) Callback_Call(callback, extra,       tag, YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
							else          Callback_Call(callback, extra,            YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
						}
					}
					else
					{
						if (bPassFile)
						{
							if (bPassTag) Callback_Call(callback,        file, tag, YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
							else          Callback_Call(callback,        file,      YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
						}
						else
						{
							if (bPassTag) Callback_Call(callback,              tag, YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
							else          Callback_Call(callback,                   YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
						}
					}
				}
			}
		}
	}
	// Return to where we were before.
	return
		YSI_g_sParentPos = epos,
		handle;
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the INI key.</param>
 * <param name="len">Size of the data in the file.</param>
 * <param name="">Variable to fill with array value.</param>
 *//*------------------------------------------------------------------------**/

stock _INI_Array(const name[], len, ...)
{
	// Load an array from the file, putting the data directly in to the
	// desired memory storage location.
	// 
	// Continue reading through the file.  Since this code is now in y_ini, we
	// can guarantee that the data will be in order in the file.
	new
		rlen,
		offset = 0,
		packed[YSI_MAX_STRING char],
		p0s, p0e, p1s, p1e, p2s, p2e;
	while ((rlen = fread(YSI_g_sCurFile, YSI_g_sCurLine)))
	{
		switch (INI_IdentifyLineType(YSI_g_sCurLine, p0s, p0e, p1s, p1e, p2s, p2e))
		{
			case e_INI_LINE_TYPE_INVALID:
			{
				P:W("Invalid line in INI file: %s", YSI_g_sCurLine);
			}
			case e_INI_LINE_TYPE_DATALESS:
			{
				// Do nothing.
			}
			case e_INI_LINE_TYPE_TAG:
			{
				break;
			}
			case e_INI_LINE_TYPE_CONT:
			{
				// Do nothing, wait for the rest of the line.
			}
			case e_INI_LINE_TYPE_ENTRY:
			{
				if (YSI_g_sExtendedLine)
				{
					if (Malloc_Get(YSI_g_sExtendedLine, 1) == '@')
					{
						P:E("Binary arrays cannot use continuation lines.");
					}
					free(YSI_g_sExtendedLine),
					YSI_g_sExtendedLine = NO_ALLOC,
					YSI_g_sExtendedName[0] = '\0';
					break;
				}
				// Read lines starting with `@` here.  They indicate packed
				// array data, which is only read by using `INI_Array`.
				if (YSI_g_sCurLine[p0s] != '@')
					break;
				YSI_g_sCurLine[p0e] = '\0';
				if (YSI_g_sCurLine[p0s + 1] == '@')
				{
					if (strcmp(YSI_g_sCurLine[p0s + 2], name))
						break;
					// Old-style packed arrays.  Used a double `@` prefix and a
					// custom packing system.
					
				}
				else
				{
					if (strcmp(YSI_g_sCurLine[p0s + 1], name))
						break;
					// Base 64 encoded data.
					YSI_g_sCurLine[p1e] = '\0',
					strpack(packed, YSI_g_sCurLine[p1s]),
					p2e = Base64Decode(argderef(2), packed, len, offset),
					len -= p2e,
					offset += p2e;
				}
				// Move on.
				YSI_g_sParentPos += rlen;
			}
		}
	}
	if (len)
		P:W("Incomplete array data in INI file for \"%s\"", name);
	// Reparse the previous line.
	fseek(YSI_g_sCurFile, YSI_g_sParentPos, seek_start);
	return 0;
}

