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

enum e_INI_LINE_TYPE:
{
	e_INI_LINE_TYPE_INVALID,
	e_INI_LINE_TYPE_DATALESS,
	e_INI_LINE_TYPE_ENTRY,
	e_INI_LINE_TYPE_CONT,
	e_INI_LINE_TYPE_TAG
}

//enum E_INI_TAGS
//{
//	E_INI_TAGS_NAME[MAX_INI_TAG char],
//	E_INI_TAGS_NEXT,
//	Alloc:E_INI_TAGS_START,
//}

// Variables for reading.
_Y_INI_STATIC stock
	Alloc:YSI_g_sExtendedLine = NO_ALLOC,
	YSI_g_sExtendedName[MAX_INI_ENTRY_NAME],
	YSI_g_sExtra = 0,
	YSI_g_sFile[FUNCTION_LENGTH],
	YSI_g_sTag[FUNCTION_LENGTH],
	YSI_g_sFormat[FUNCTION_LENGTH],
	bool:YSI_g_sRemote = false,
	YSI_g_sCurLine[MAX_INI_LINE];

// Variables for callbacks.
static stock
	Func:YSI_g_sCB_issss<issss> = Func:0<issss>,
	Func:YSI_g_sCB_isss<isss>   = Func:0<isss>,
	Func:YSI_g_sCB_iss<iss>     = Func:0<iss>,
	Func:YSI_g_sCB_ssss<ssss>   = Func:0<ssss>,
	Func:YSI_g_sCB_sss<sss>     = Func:0<sss>,
	Func:YSI_g_sCB_ss<ss>       = Func:0<ss>;

// Variables for writing.
_Y_INI_STATIC stock
	// The file names.
	YSI_g_sINIWriteFile[INI:INI_MAX_WRITES][64],
	// Linked list of "ENTRIES, NEXT, REMOVED, NAME".
	Alloc:YSI_g_sINITagBuffer[INI:INI_MAX_WRITES],
	Alloc:YSI_g_sINICurrentTag[INI:INI_MAX_WRITES],
	// The data being dumped.
	Alloc:YSI_g_sCurrentTag = NO_ALLOC,
	INI:YSI_g_sCurrentINI = INI:0,
	File:YSI_g_sCurrentFile = File:0,
	bool:YSI_g_sNL = false,
	bool:YSI_g_sTagNeeded = false;

forward bool:INI_FindCallback(const cb[]);

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

#define INI_IsValid(%0) (0 <= _:(%0) < INI_MAX_WRITES && YSI_g_sINITagBuffer[(%0)])

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
	if (!strcmp((%1), name, true)) return _:INI_CHECK_LEN:StrCpy(%2, value)

#define INI_CHECK_LEN:StrCpy(%0,%1,%2) StrCpy(%0,%2,%1)

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the INI key.</param>
 * <param name="variable">Variable to fill with string value.</param>
 *//*------------------------------------------------------------------------**/

P:D(INI_Bool(const name[],&bool:variable));
#define INI_Bool(%1,%2) \
	if (!strcmp((%1), name, true)) return %2 = BoolStr(value)

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

static stock INI_WriteTag(File:file, const tag[], format[])
{
	if (YSI_g_sTagNeeded)
	{
		YSI_g_sNL = !YSI_g_sNL || fwrite(file, "\n"),
		fwrite(file, "["),
		fwrite(file, tag),
		YSI_g_sTagNeeded = false;
		if (format[0])
		{
			fwrite(file, "] : "),
			fwrite(file, format),
			format[0] = '\0';
		}
		else
		{
			fwrite(file, "]");
		}
	}
}

#define INI_TagListGetEntries(%0) (Alloc:mget((%0), 0))
#define INI_TagListGetNext(%0) (Alloc:mget((%0), 1))
#define INI_TagListGetDelete(%0) (bool:mget((%0), 2))
#define INI_TagListGetName(%0) (mget((%0), 3))

#define INI_TagListSetEntries(%0,%1) (mset((%0), 0, (%1)))
#define INI_TagListSetNext(%0,%1) (mset((%0), 1, _:(%1)))
#define INI_TagListSetDelete(%0,%1) (mset((%0), 2, (%1)))
#define INI_TagListSetName(%0,%1) (msets((%0), 3, (%1)))

#define INI_KeyListGetNext(%0) (Alloc:mget((%0), 0))
#define INI_KeyListGetKey(%0) (mget((%0), 2))
#define INI_KeyListGetValue(%0) (mget((%0), mget((%0), 1) + 1))

#define INI_KeyListMakeWritable(%0) (mset((%0), mget((%0), 1), '='))

#define INI_KeyListRemove(%0,%1) (mset((%0), 0, mget((%1), 0)))
#define INI_KeyListAdd(%0,%1) (mset((%1), 0, mget((%0), 0)), mset((%0), 0, _:(%1)))

#define INI_KeyListSetNext(%0,%1) (mset((%0), 0, (%1)))
#define INI_KeyListSetKeyValue(%0,%1,%2) (I@ = strlen(%1), msets((%0), 2, (%1)), mset((%0), 1, I@ + 2), msets((%0), I@ + 3, (%2)))

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
		StrCpy((%2), (%3)), \
		Inline_Reset((%0)), \
		format(YSI_g_sCurLine, sizeof (YSI_g_sCurLine), (%1), (%2)), \
		Callback_Get(callback_tag:YSI_g_sCurLine, (%0), (%4), (%5)) \
	)

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

static stock Alloc:INI_GetTag(Alloc:cur, const tag[])
{
	if (tag[0])
	{
		while (cur)
		{
			if (INI_TagListGetName(cur) && !strcmp(tag, INI_TagListGetName(cur)))
			{
				return cur;
			}
			cur = INI_TagListGetNext(cur);
		}
		return NO_ALLOC;
	}
	else
	{
		// Blank (no) tag.
		while (cur)
		{
			if (!INI_TagListGetName(cur))
			{
				return cur;
			}
			cur = INI_TagListGetNext(cur);
		}
		return NO_ALLOC;
	}
}

static stock Alloc:INI_GetKey(Alloc:cur, const key[], &Alloc:prev)
{
	P:4("INI_GetKey called: prev = %d %s", _:cur, INI_TagListGetName(cur));
	for ( ; ; )
	{
		prev = cur,
		cur = INI_KeyListGetNext(prev);
		if (!cur)
			break;
		if (!strcmp(key, INI_KeyListGetKey(cur)))
		{
			return cur;
		}
	}
	return NO_ALLOC;
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">INI file to write to.</param>
 * <param name="name">Data name to write.</param>
 * <param name="data">Data to write.</param>
 * <returns>
 *  The slot written to, or -1 on failure.
 * </returns>
 * <remarks>
 *  First checks the name doesn't already exist under the current tag header
 *  and if it does overwrites the current value.  If not checks there's room
 *  in the buffer to write to and purges the buffer if not.  Finally saves the
 *  data in the buffer for writing when required and adds the data to the
 *  relevant list for tag inclusion.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_INI_STATIC stock bool:INI_AddToBuffer(INI:file, const key[], const value[], semis = 0)
{
	P:4("INI_AddToBuffer called: %i, \"%s\", \"%s\"", _:file, key, value);
	if (strfind(key, YSI_SPACE) != -1)
	{
		P:E("INI key \"%s\" must not contain spaces", key);
		return false;
	}
	if (INI_IsValid(file) && key[0])
	{
		if (INI_TagListGetDelete(YSI_g_sINICurrentTag[file]))
		{
			// The tag is deleted - no point writing anything to it!
			return false;
		}
		new
			len = strlen(key) + strlen(value) + 4 + semis, // 2 * NULL + next + keylen + semis.
			Alloc:prev = Alloc:0,
			Alloc:mem = INI_GetKey(YSI_g_sINICurrentTag[file], key, prev);
		if (mem)
		{
			// We already wrote this value.  Can we change it?
			if (Malloc_GetSlotSize(mem) >= len)
			{
				// Write this new value at the value offset.
				if (semis)
				{
					// Get semi-colons we need to escape.  Do it the hard way.
					len = 0,
					semis = mget(mem, 1) + 1;
					while ((_:file = strfind(value, ";", false, len)) != -1)
					{
						_YSI_ConstMod(value[_:file], '\0');
						msets(mem, semis, value[len]);
						semis += _:file - len;
						mset(mem, semis, '\\');
						mset(mem, semis, ';');
						semis += 2;
						_YSI_ConstMod(value[_:file], ';');
						len = _:file + 1;
					}
					msets(mem, semis, value[len]);
				}
				else
				{
					msets(mem, mget(mem, 1) + 1, value);
				}
				return true;
			}
			// Not enough space to replace, so don't bother.  First remove it
			// from the linked list (this will even work for the first value
			// because we use the same offset for initial and next).
			INI_KeyListRemove(prev, mem);
			free(mem);
		}
		for ( ; ; )
		{
			// Allocate new memory.
			mem = malloc(len);
			if (mem)
			{
				I@ = strlen(key),
				msets(mem, 2, key),
				mset(mem, 1, I@ + 2);
				if (semis)
				{
					// Get semi-colons we need to escape.  Do it the hard way.
					len = 0,
					semis = I@ + 3;
					for (new pos = 0; (pos = strfind(value, ";", false, len)) != -1; len = pos + 1)
					{
						_YSI_ConstMod(value[pos], '\0');
						msets(mem, semis, value[len]);
						semis += pos - len;
						mset(mem, semis, '\\');
						mset(mem, semis + 1, ';');
						semis += 2;
						_YSI_ConstMod(value[pos], ';');
					}
					msets(mem, semis, value[len]);
				}
				else
					msets(mem, I@ + 3, value);
				return
					// Add this to the linked list.
					INI_KeyListAdd(YSI_g_sINICurrentTag[file], mem),
					true;
			}
			// Try again.
			INI_FlushWithRestore(file);
		}
	}
	return false;
}

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

stock bool:INI_ParseFile(const fname[], const remoteFormat[], bool:bFileFirst = false, bool:bExtra = false, extra = 0, bool:bLocal = true, bool:bPassTag = false, bool:bPassFile = false)
{
	P:4("INI_ParseFile called");
	new
		File:fhnd = fopen(fname, io_read);
	if (!fhnd)
		return false;
	StrCpy(YSI_g_sFormat, remoteFormat);
	new
		start = strlen(fname);
	{
		while (start && fname[start - 1] != '/' && fname[start - 1] != '\\')
			--start;
		new
			end = start;
		while (fname[end] && fname[end] != '.')
			++end;
		StrCpy(YSI_g_sFile, fname[start], end - start + 1);
	}
	YSI_g_sRemote = !bLocal;
	YSI_g_sExtra = extra;
	if (bFileFirst)
	{
		if (bExtra)
		{
			if (bPassTag)
			{
				P:6("INI_ParseFile: call type %s", bPassFile ? ("yyyy") : ("yyyn"));
				if (bPassFile)
					state y_ini:y_ini_reading_yyyy;
				else
					state y_ini:y_ini_reading_yyyn;
			}
			else
			{
				P:6("INI_ParseFile: call type %s", bPassFile ? ("yyny") : ("yynn"));
				if (bPassFile)
					state y_ini:y_ini_reading_yyny;
				else
					state y_ini:y_ini_reading_yynn;
			}
		}
		else
		{
			if (bPassTag)
			{
				P:6("INI_ParseFile: call type %s", bPassFile ? ("ynyy") : ("ynyn"));
				if (bPassFile)
					state y_ini:y_ini_reading_ynyy;
				else
					state y_ini:y_ini_reading_ynyn;
			}
			else
			{
				P:6("INI_ParseFile: call type %s", bPassFile ? ("ynny") : ("ynnn"));
				if (bPassFile)
					state y_ini:y_ini_reading_ynny;
				else
					state y_ini:y_ini_reading_ynnn;
			}
		}
	}
	else
	{
		if (bExtra)
		{
			if (bPassTag)
			{
				P:6("INI_ParseFile: call type %s", bPassFile ? ("nyyy") : ("nyyn"));
				if (bPassFile)
					state y_ini:y_ini_reading_nyyy;
				else
					state y_ini:y_ini_reading_nyyn;
			}
			else
			{
				P:6("INI_ParseFile: call type %s", bPassFile ? ("nyny") : ("nynn"));
				if (bPassFile)
					state y_ini:y_ini_reading_nyny;
				else
					state y_ini:y_ini_reading_nynn;
			}
		}
		else
		{
			if (bPassTag)
			{
				P:6("INI_ParseFile: call type %s", bPassFile ? ("nnyy") : ("nnyn"));
				if (bPassFile)
					state y_ini:y_ini_reading_nnyy;
				else
					state y_ini:y_ini_reading_nnyn;
			}
			else
			{
				P:6("INI_ParseFile: call type %s", bPassFile ? ("nnny") : ("nnnn"));
				if (bPassFile)
					state y_ini:y_ini_reading_nnny;
				else
					state y_ini:y_ini_reading_nnnn;
			}
		}
	}
	{
		// Set up the initial callback.
		new
			pos = -1,
			cb[FUNCTION_LENGTH];
		YSI_g_sTag[0] = '\1';
		YSI_g_sTag[1] = '\0';
		if (bFileFirst)
			format(cb, sizeof (cb), YSI_g_sFormat, YSI_g_sFile, YSI_EMPTY);
		else
			format(cb, sizeof (cb), YSI_g_sFormat, YSI_EMPTY, YSI_g_sFile);
		while ((pos = strfind(cb, YSI_SPACE, false, pos + 1)) != -1)
			cb[pos] = '_';
		start = INI_FindCallback(cb);
	}
	{
		// Read the file.  We have no parent and want to be in read mode.  What we
		// do with the lines is determined by the state and the current line type.
		new parent[FUNCTION_LENGTH] = "";
		INI_ReadFile(fhnd, parent, !!start),
		fclose(fhnd);
	}
	return true;
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

stock bool:INI_Load(const filename[], bool:bExtra = false, extra = 0, bool:bLocal = true)
{
	P:3("bool:INI_Load called: \"%s\", %i, %i, %i", filename, _:bExtra, extra, _:bLocal);
	return INI_ParseFile(filename, "@INI_%s_%s", .bFileFirst = true, .bExtra = bExtra, .extra = extra, .bLocal = bLocal);
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the INI key.</param>
 * <param name="len">Size of the data in the file.</param>
 * <param name="">Variable to fill with array value.</param>
 *//*------------------------------------------------------------------------**/

//stock _INI_Array(const name[], len, ...)
//{
//	// Load an array from the file, putting the data directly in to the
//	// desired memory storage location.
//	// 
//	// Continue reading through the file.  Since this code is now in y_ini, we
//	// can guarantee that the data will be in order in the file.
//	new
//		rlen,
//		offset = 0,
//		packed[YSI_MAX_STRING char],
//		p0s, p0e, p1s, p1e, p2s, p2e;
//	while ((rlen = fread(YSI_g_sCurrentFile, YSI_g_sCurLine)))
//	{
//		switch (INI_IdentifyLineType(YSI_g_sCurLine, p0s, p0e, p1s, p1e, p2s, p2e))
//		{
//			case e_INI_LINE_TYPE_INVALID:
//			{
//				P:W("Invalid line in INI file: %s", YSI_g_sCurLine);
//			}
//			case e_INI_LINE_TYPE_DATALESS:
//			{
//				// Do nothing.
//			}
//			case e_INI_LINE_TYPE_TAG:
//			{
//				break;
//			}
//			case e_INI_LINE_TYPE_CONT:
//			{
//				// Do nothing, wait for the rest of the line.
//			}
//			case e_INI_LINE_TYPE_ENTRY:
//			{
//				if (YSI_g_sExtendedLine)
//				{
//					if (Malloc_Get(YSI_g_sExtendedLine, 1) == '@')
//					{
//						P:E("Binary arrays cannot use continuation lines.");
//					}
//					free(YSI_g_sExtendedLine),
//					YSI_g_sExtendedLine = NO_ALLOC,
//					YSI_g_sExtendedName[0] = '\0';
//					break;
//				}
//				// Read lines starting with `@` here.  They indicate packed
//				// array data, which is only read by using `INI_Array`.
//				if (YSI_g_sCurLine[p0s] != '@')
//					break;
//				YSI_g_sCurLine[p0e] = '\0';
//				if (YSI_g_sCurLine[p0s + 1] == '@')
//				{
//					if (strcmp(YSI_g_sCurLine[p0s + 2], name))
//						break;
//					// Old-style packed arrays.  Used a double `@` prefix and a
//					// custom packing system.
//					
//				}
//				else
//				{
//					if (strcmp(YSI_g_sCurLine[p0s + 1], name))
//						break;
//					// Base 64 encoded data.
//					YSI_g_sCurLine[p1e] = '\0',
//					strpack(packed, YSI_g_sCurLine[p1s]),
//					p2e = Base64Decode(argderef(2), packed, len, offset),
//					len -= p2e,
//					offset += p2e;
//				}
//				// Move on.
//				YSI_g_sParentPos += rlen;
//				if (!len)
//					return 0;
//			}
//		}
//	}
//	if (len)
//		P:W("Incomplete array data in INI file for \"%s\"", name);
//	// Reparse the previous line.
//	fseek(YSI_g_sCurrentFile, YSI_g_sParentPos, seek_start);
//	return 0;
//}

/*-------------------------------------------------------------------------*//**
 * <param name="file">INI file handle to write to.</param>
 * <param name="tag">Name of the new file subsection for subsequent data to write to.</param>
 * <remarks>
 *  Sets a new [tag] section header.  Subsequent data is written under this
 *  header.  Uses lists for constant tag switching and checks the tag doesn't
 *  already exist.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock bool:INI_SetTag_(INI:file, const tag[])
{
	// Loop through the tags for this file.
	new
		Alloc:cur = INI_GetTag(YSI_g_sINITagBuffer[file], tag);
	if (cur)
	{
		P:5("INI_SetTag_: Found old key");
		YSI_g_sINICurrentTag[file] = cur;
		return true;
	}
	for ( ; ; )
	{
		// Allocate a new tag.
		cur = malloc(strlen(tag) + 4);
		if (cur)
		{
			INI_TagListSetDelete(cur, false),
			INI_TagListSetEntries(cur, 0),
			INI_TagListSetNext(cur, YSI_g_sINITagBuffer[file]),
			INI_TagListSetName(cur, tag),
			YSI_g_sINITagBuffer[file] = cur,
			YSI_g_sINICurrentTag[file] = cur;
			P:7("INI_SetTag_: allocated %s", INI_TagListGetName(YSI_g_sINICurrentTag[file]));
			break;
		}
		// Allocating a new tag failed.  Clear memory and try again.  When
		// flushing, don't restore the current tag, since we're about to
		// write a new one.
		INI_FlushWithoutRestore(file);
	}
	return true;
}

/*-------------------------------------------------------------------------*//**
 * <param name="filename">INI file to open.</param>
 * <returns>
 *  INI - handle to the file or INI_NO_FILE.
 * </returns>
 * <remarks>
 *  Doesn't actually open the file, just starts a new buffer if possible.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock INI:INI_Open(const filename[])
{
	P:3("INI:INI_Open called: \"%s\"", filename);
	if (ftouch(filename) == -1)
	{
		P:W("INI_Open could not find or create file %s", filename);
	}
	new
		INI:i = INI:0;
	while (i != INI:INI_MAX_WRITES && YSI_g_sINITagBuffer[i])
	{
		++i;
	}
	if (i == INI:INI_MAX_WRITES)
	{
		return INI_NO_FILE;
	}
	return
		// Reset tags.
		INI_SetTag_(i, YSI_EMPTY),
		StrCpy(YSI_g_sINIWriteFile[i], filename, YSI_MAX_STRING),
		i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">Handle to the ini to close.</param>
 * <remarks>
 *  Writes any outstanding buffer data to the file and ends the stream.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock INI_Close(INI:file)
{
	P:3("INI_Close called: %i", _:file);
	if (INI_IsValid(file))
	{
		INI_FlushWithoutRestore(file),
		YSI_g_sINITagBuffer[file] = NO_ALLOC;
	}
}

stock bool:INI_SetTag(INI:file, const tag[])
{
	P:3("INI_SetTag called: %i, \"%s\"", _:file, tag);
	if (strfind(tag, YSI_SPACE) != -1)
	{
		P:E("INI tag \"%s\" must not contain spaces", tag);
		if (INI_IsValid(file))
		{
			YSI_g_sINICurrentTag[file] = NO_ALLOC;
		}
	}
	else if (INI_IsValid(file))
	{
		return INI_SetTag_(file, tag);
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">INI file handle to write to.</param>
 * <param name="tag">Name of the whole section to delete.</param>
 * <remarks>
 *  Removes a [tag] section from a file.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:INI_DeleteTag(INI:file, const tag[])
{
	if (INI_SetTag(file, tag))
	{
		// A setting of `tag[2] = true;` means "deleted".
		INI_TagListSetDelete(YSI_g_sINICurrentTag[file], true);
		return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">File to write to.</param>
 * <param name="name">Item to remove.</param>
 * <remarks>
 *  Wrapper for INI_AddToBuffer for removing data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:INI_RemoveEntry(INI:file, const name[])
{
	P:3("INI_RemoveEntry called: %i, \"%s\"", _:file, name);
	return INI_AddToBuffer(file, name, YSI_EMPTY);
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

#if !defined Y_INI_NO_ESCAPES
static stock INI_DealWithSemiColonEscape(str[], &pos, &end) <y_ini:y_ini_writing_fast, y_ini:y_ini_writing_slow>
{
	#pragma unused str // https://github.com/pawn-lang/compiler/issues/371
	end = ++pos;
}

static stock INI_DealWithSemiColonEscape(str[], &pos, &end) <>
{
	strdel(str[pos - 1], 0, 1),
	end = pos;
}
#endif

_Y_INI_STATIC stock e_INI_LINE_TYPE:
	INI_IdentifyLineType(str[MAX_INI_LINE], &p0s, &p0e, &p1s, &p1e, &p2s, &p2e)
{
	// Reset everything.
	p0s = p0e = p1s = p1e = p2s = p2e = 0;
	// Do this purely with a single main loop, and a state machine.
	new
		end = 0,
		e_INI_LINE_TYPE:ret = e_INI_LINE_TYPE_DATALESS,
		pos = 0;
	// If there is memory allocated for a line continuation, that means the
	// previous line ended with '\\', so this line is just part of that one,
	// regardless of what it contains.
	if (YSI_g_sExtendedLine)
		goto state_in_continue_line;
	INI_SkipWhitespace(str, pos);
	switch (str[pos])
	{
		case '\0': return e_INI_LINE_TYPE_DATALESS;
		case  ';':
		{
			++pos;
			goto state_in_comment;
		}
		case  '[':
		{
			++pos;
			goto state_in_tag;
		}
		case '\\':
		{
			if (str[++pos])
				p0s = pos;
			else
				return e_INI_LINE_TYPE_INVALID;
		}
		case '=': return e_INI_LINE_TYPE_INVALID;
		default: p0s = pos;
	}
	// Default end point, for single-character lines.
	end = pos + 1;
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
	P:6("INI_IdentifyLineType: In continue line, %d, %d (%.*s)", p0s, p0e, p0e - p0s, str[p0s]);
	// See what comes next.
	INI_SkipWhitespace(str, pos);
	p1s = end = pos;
	for ( ; ; ) switch (str[pos++])
	{
		case '\r', '\n':
			if (YSI_g_sExtendedLine)
			{
				p1e = end,
				ret = e_INI_LINE_TYPE_ENTRY;
				goto state_in_continuation;
			}
			else
				return p1e = end, e_INI_LINE_TYPE_ENTRY;
		case '\0':
		{
			// Couldn't fit the whole read line in to the given variable.  This
			// is an implicit continuation - it isn't actually one, the line
			// just spans multiple reads.
			p1e = end,
			ret = e_INI_LINE_TYPE_CONT;
			goto state_in_continuation;
		}
		case  ';':
		{
			p1e = end,
			ret = e_INI_LINE_TYPE_ENTRY;
			goto state_in_comment;
		}
		case '\\':
		{
			end = pos - 1;
			switch (str[pos])
			{
#if defined Y_INI_NO_ESCAPES
				case ';':
					// Only allow ';' to immediately follow '\\'.
					end = ++pos;
#else
				case 'n':
				{
					str[pos] = '\n',
					strdel(str[pos - 1], 0, 1),
					end = pos;
				}
				case 'r':
				{
					str[pos] = '\r',
					strdel(str[pos - 1], 0, 1),
					end = pos;
				}
				case 't':
				{
					str[pos] = '\t',
					strdel(str[pos - 1], 0, 1),
					end = pos;
				}
				case '\\':
				{
					strdel(str[pos - 1], 0, 1),
					end = pos;
				}
				case ';':
					INI_DealWithSemiColonEscape(str, pos, end);
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
		case '\1' .. '\9', '\11', '\12', '\14' .. ' ': {} // Whitespace, skip it.
		default: end = pos;  // Characters, save this position.
	}
state_in_tag:
	P:6("INI_IdentifyLineType: In tag: %s", str);
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
	P:6("INI_IdentifyLineType: In comment: %s", str);
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
	P:6("INI_IdentifyLineType: In continuation: %s", str);
	// We get here if a line ended with `\\`.  We need to copy the data from
	// this line in to allocated space.
	if (!YSI_g_sExtendedName[0])
	{
		// Haven't yet stored the name of this line.  Do so.
		StrCpy(YSI_g_sExtendedName, str[p0s], p0e - p0s + 1);
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

    I8,        8        ,8I          88         88                          
    `8b       d8b       d8'          ""   ,d    ""                          
     "8,     ,8"8,     ,8"                88                                
      Y8     8P Y8     8P 8b,dPPYba, 88 MM88MMM 88 8b,dPPYba,   ,adPPYb,d8  
      `8b   d8' `8b   d8' 88P'   "Y8 88   88    88 88P'   `"8a a8"    `Y88  
       `8a a8'   `8a a8'  88         88   88    88 88       88 8b       88  
        `8a8'     `8a8'   88         88   88,   88 88       88 "8a,   ,d88  
         `8'       `8'    88         88   "Y888 88 88       88  `"YbbdP"Y8  
                                                                aa,    ,88  
                                                                 "Y8bbdP"   

*/

/*-------------------------------------------------------------------------*//**
 * <param name="file">File to write to.</param>
 * <param name="name">Data name.</param>
 * <param name="data">Data.</param>
 * <remarks>
 *  Wrapper for INI_AddToBuffer for strings.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:INI_WriteString(INI:file, const name[], const data[])
{
	P:3("INI_WriteString called: %i, \"%s\", \"%s\"", _:file, name, data);
	new
		pos = 0,
		semis = 0;
	while ((pos = strfind(data, ";", false, pos) + 1))
		++semis;
	return INI_AddToBuffer(file, name, data, semis);
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">File to write to.</param>
 * <param name="name">Data name.</param>
 * <param name="data">Integer data.</param>
 * <remarks>
 *  Wrapper for INI_AddToBuffer for integers.  Fixed for very large numbers
 *  based on code by Slice from "fixes.inc" for "valstr".
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:INI_WriteInt(INI:file, const name[], data)
{
	P:3("INI_WriteInt called: %i, \"%s\", %i", _:file, name, data);
	static const
		sc_szCellmin[] = "-2147483648";
	if (data == cellmin)
	{
		return INI_AddToBuffer(file, name, sc_szCellmin);
	}
	else
	{
		return
			format(Q@, sizeof (Q@), "%d", data),
			INI_AddToBuffer(file, name, Q@);
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">File to write to.</param>
 * <param name="name">Data name.</param>
 * <param name="data">Hex data.</param>
 * <remarks>
 *  Wrapper for INI_AddToBuffer for integers to be written as hex values.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:INI_WriteHex(INI:file, const name[], data)
{
	P:3("INI_WriteHex called: %i, \"%s\", %i", _:file, name, data);
	return
		format(Q@, sizeof (Q@), "0x%04x%04x", data >>> 16, data & 0xFFFF),
		INI_AddToBuffer(file, name, Q@);
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">File to write to.</param>
 * <param name="name">Data name.</param>
 * <param name="data">Binary data.</param>
 * <remarks>
 *  Wrapper for INI_AddToBuffer for integers to be written as binary values.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:INI_WriteBin(INI:file, const name[], data)
{
	P:3("INI_WriteBin called: %i, \"%s\", %i", _:file, name, data);
	if (data < 0) format(Q@, sizeof (Q@), "0b1%031b", data & 0x7FFFFFFF);
	else format(Q@, sizeof (Q@), "0b%b", data);
	return INI_AddToBuffer(file, name, Q@);
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">File to write to.</param>
 * <param name="name">Data name.</param>
 * <param name="data">Boolean data.</param>
 * <remarks>
 *  Wrapper for INI_AddToBuffer for booleans.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:INI_WriteBool(INI:file, const name[], bool:data)
{
	P:3("INI_WriteBool called: %i, \"%s\", %i", _:file, name, _:data);
	return INI_AddToBuffer(file, name, data ? ("true") : ("false"));
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">File to write to.</param>
 * <param name="name">Data name.</param>
 * <param name="data">Float data.</param>
 * <param name="accuracy">number of decimal places to write.</param>
 * <remarks>
 *  Wrapper for INI_AddToBuffer for floats.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:INI_WriteFloat(INI:file, const name[], Float:data, accuracy = 6)
{
	P:3("INI_WriteFloat called: %i, \"%s\", %f, %i", _:file, name, data, accuracy);
	return
		format(Q@, sizeof (Q@), "%.*f", accuracy, data),
		INI_AddToBuffer(file, name, Q@);
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
 * <param name="file">File to write to.</param>
 * <param name="name">Data name.</param>
 * <param name="data">Float data.</param>
 * <param name="accuracy">number of decimal places to write.</param>
 * <remarks>
 *  Wrapper for INI_AddToBuffer for floats.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock INI_ReadFile(File:fhnd, parent[FUNCTION_LENGTH], bool:handle = true)
{
	P:5("INI_ReadFile called: %d, %s, %d", _:fhnd, parent, handle);
	new
		bool:doneParent = false,
		pos = 0,
		rlen = 0,
		p0s = 0, p0e = 0, p1s = 0, p1e = 0, p2s = 0, p2e = 0;
	// Read from the start of the file.
	fseek(fhnd, 0, seek_start);
	while ((rlen = fread(fhnd, YSI_g_sCurLine)))
	{
		P:7("INI_ReadFile: %d, %s", rlen, YSI_g_sCurLine);
		pos += rlen;
		switch (INI_IdentifyLineType(YSI_g_sCurLine, p0s, p0e, p1s, p1e, p2s, p2e))
		{
			case e_INI_LINE_TYPE_INVALID:
			{
				P:7("INI_ReadFile: e_INI_LINE_TYPE_INVALID");
				P:W("Invalid line in INI file \"%s\": %s", YSI_g_sFile, YSI_g_sCurLine);
			}
			case e_INI_LINE_TYPE_DATALESS:
			{
				P:7("INI_ReadFile: e_INI_LINE_TYPE_DATALESS");
				// Do nothing.
			}
			case e_INI_LINE_TYPE_TAG:
			{
				P:7("INI_ReadFile: e_INI_LINE_TYPE_TAG");
				if (doneParent)
				{
					// This was only called to recursively deal with parents.
					return;
				}
				// First, check if it is a tag we might care about.
				YSI_g_sCurLine[p0e] = '\0';
				if (YSI_g_sCurLine[p0s] == '@' && YSI_g_sCurLine[p0s + 1] == '@' && (p0e = strfind(YSI_g_sCurLine, "-") + 1))
				{
					P:W("Filtered tags are deprecated - just use specified callbacks");
					p0s = p0e;
				}
				if (parent[0])
				{
					if (strcmp(YSI_g_sCurLine[p0s], parent))
					{
						handle = false;
						continue;
					}
					doneParent = true;
				}
				else switch (INI_HandleTag(YSI_g_sCurLine[p0s]))
				{
					case 0:
					{
						// Don't deal with this tag.
						handle = false;
						continue;
					}
					case 1:
					{
						// Only deal with local values.
						StrCpy(YSI_g_sTag, YSI_g_sCurLine[p0s], p0e - p0s + 1),
						StrCpy(YSI_g_sFormat, YSI_g_sCurLine[p1s], p1e - p1s + 1),
						handle = true;
						goto INI_ReadFile_cont;
					}
				}
				// This parent may have its own parent.
				if (p1s != p1e)
				{
					// Is there a parent tag to deal with?
					StrCpy(parent, YSI_g_sCurLine[p1s], p1e - p1s + 1);
					P:7("INI_ReadFile: tag has parent (%s)", parent);
					// Do local and parent values.
					INI_ReadFile(fhnd, parent),
					fseek(fhnd, pos, seek_start);
					parent[0] = '\0';
				}
				P:C(else { print("INI_ReadFile: tag has no parent"); });
				// https://github.com/pawn-lang/compiler/issues/669
				#pragma unused handle
				handle = true;
			}
			case e_INI_LINE_TYPE_CONT:
			{
				P:7("INI_ReadFile: e_INI_LINE_TYPE_CONT");
				// Do nothing, wait for the rest of the line.
				if (!handle)
				{
					continue;
				}
			}
			case e_INI_LINE_TYPE_ENTRY:
			{
				P:7("INI_ReadFile: e_INI_LINE_TYPE_ENTRY");
				if (handle)
				{
					if (YSI_g_sExtendedLine)
					{
						INI_HandleEntry(YSI_g_sExtendedName, Malloc_Get(YSI_g_sExtendedLine, 1));
						free(YSI_g_sExtendedLine),
						YSI_g_sExtendedLine = NO_ALLOC,
						YSI_g_sExtendedName[0] = '\0';
					}
					else if (handle)
					{
						YSI_g_sCurLine[p0e] = YSI_g_sCurLine[p1e] = '\0';
						INI_HandleEntry(YSI_g_sCurLine[p0s], YSI_g_sCurLine[p1s]);
					}
				}
				else
				{
					if (YSI_g_sExtendedLine)
					{
						free(YSI_g_sExtendedLine),
						YSI_g_sExtendedLine = NO_ALLOC,
						YSI_g_sExtendedName[0] = '\0';
					}
					continue;
				}
			}
		}
INI_ReadFile_cont:
		if (p2s != p2e)
		{
			YSI_g_sCurLine[p2e] = '\0';
			INI_HandleComment(YSI_g_sCurLine[p2s]);
		}
	}
	INI_HandleEnd();
}

/*-------------------------------------------------------------------------*//**
 * <param name="key">The key of the data loaded.</param>
 * <param name="value">The data loaded.</param>
 * <remarks>
 *  Reading: Calls the correct type of callback based on earlier settings.
 *  Writing: Writes out the line with the new or old data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock INI_HandleEntry(const key[], const value[]) <y_ini:y_ini_reading_yyyy, y_ini:y_ini_reading_nyyy>
{
	@.YSI_g_sCB_issss(YSI_g_sExtra, YSI_g_sFile, YSI_g_sTag, key, value);
}

static stock INI_HandleEntry(const key[], const value[]) <y_ini:y_ini_reading_yyyn, y_ini:y_ini_reading_nyyn>
{
	@.YSI_g_sCB_isss(YSI_g_sExtra, YSI_g_sTag, key, value);
}

static stock INI_HandleEntry(const key[], const value[]) <y_ini:y_ini_reading_yyny, y_ini:y_ini_reading_nyny>
{
	@.YSI_g_sCB_isss(YSI_g_sExtra, YSI_g_sFile, key, value);
}

static stock INI_HandleEntry(const key[], const value[]) <y_ini:y_ini_reading_yynn, y_ini:y_ini_reading_nynn>
{
	@.YSI_g_sCB_iss(YSI_g_sExtra, key, value);
}

static stock INI_HandleEntry(const key[], const value[]) <y_ini:y_ini_reading_ynyy, y_ini:y_ini_reading_nnyy>
{
	@.YSI_g_sCB_ssss(YSI_g_sFile, YSI_g_sTag, key, value);
}

static stock INI_HandleEntry(const key[], const value[]) <y_ini:y_ini_reading_ynyn, y_ini:y_ini_reading_nnyn>
{
	@.YSI_g_sCB_sss(YSI_g_sTag, key, value);
}

static stock INI_HandleEntry(const key[], const value[]) <y_ini:y_ini_reading_ynny, y_ini:y_ini_reading_nnny>
{
	@.YSI_g_sCB_sss(YSI_g_sFile, key, value);
}

static stock INI_HandleEntry(const key[], const value[]) <y_ini:y_ini_reading_ynnn, y_ini:y_ini_reading_nnnn>
{
	@.YSI_g_sCB_ss(key, value);
}

static stock INI_HandleEntry(const key[], const value[]) <y_ini:y_ini_writing_slow>
{
	// Used when reading.  Checks if the key is being overwritten, and if not
	// writes it out to the new file.
	INI_WriteTag(YSI_g_sCurrentFile, YSI_g_sTag, YSI_g_sFormat);
	if (YSI_g_sNL)
	{
		// Write a new line if needed.
		fwrite(YSI_g_sCurrentFile, "\n");
	}
	new
		Alloc:prev = Alloc:0,
		Alloc:mem = INI_GetKey(YSI_g_sCurrentTag, key, prev);
	if (mem)
	{
		// Not deleted.
		if (INI_KeyListGetValue(mem))
		{
			INI_KeyListRemove(prev, mem),
			INI_KeyListMakeWritable(mem),
			fwrite(YSI_g_sCurrentFile, INI_KeyListGetKey(mem)),
			// Remove this from the list.
			free(mem);
		}
	}
	else
	{
		// Write the entry.
		fwrite(YSI_g_sCurrentFile, key),
		fwrite(YSI_g_sCurrentFile, "="),
		fwrite(YSI_g_sCurrentFile, value);
	}
	YSI_g_sNL = true;
}

static stock INI_HandleEntry(const key[], const value[]) <y_ini:y_ini_writing_fast>
{
	// Nothing in the current tag is being overwritten, just dump this
	// key/value pair straight to disk with no extra checks.
	INI_WriteTag(YSI_g_sCurrentFile, YSI_g_sTag, YSI_g_sFormat);
	if (YSI_g_sNL)
	{
		// Write a new line if needed.
		fwrite(YSI_g_sCurrentFile, "\n");
	}
	// Write the entry.
	fwrite(YSI_g_sCurrentFile, key),
	fwrite(YSI_g_sCurrentFile, "="),
	fwrite(YSI_g_sCurrentFile, value),
	YSI_g_sNL = true;
}

/*-------------------------------------------------------------------------*//**
 * <param name="comment">The comment from the file.</param>
 * <remarks>
 *  Reading: Does nothing.
 *  Writing: Writes the comment to the file.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock INI_HandleComment(const comment[]) <y_ini:y_ini_writing_fast, y_ini:y_ini_writing_slow>
{
	#pragma unused comment
	INI_WriteTag(YSI_g_sCurrentFile, YSI_g_sTag, YSI_g_sFormat);
	// Write the comment.
	fwrite(YSI_g_sCurrentFile, " ; "),
	fwrite(YSI_g_sCurrentFile, comment),
	// Write a new line and mark as not needed.
	fwrite(YSI_g_sCurrentFile, "\n"),
	YSI_g_sNL = false;
}

static stock INI_HandleComment(const comment[]) <>
{
	#pragma unused comment
	// All the reading states ignore comments.
}

/*-------------------------------------------------------------------------*//**
 * <param name="tag">The tag from the file.</param>
 * <remarks>
 *  Reading: Does nothing.
 *  Writing: Dumps the remainder of the previous tag and switches to the new
 *    one.  If there's nothing to dump, moves to the fast dump mode.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock INI_DumpTag(Alloc:dump)
{
	// Do we need the tag name or not?  Even for unknown tags.
	INI_WriteTag(YSI_g_sCurrentFile, YSI_g_sTag, YSI_g_sFormat);
	if (dump)
	{
		// We were writing a known tag.
		new
			Alloc:next = INI_TagListGetEntries(dump);
		INI_TagListSetEntries(dump, 0);
		while (next)
		{
			if (!INI_KeyListGetValue(next))
			{
				dump = next,
				next = INI_KeyListGetNext(dump),
				free(dump);
				continue;
			}
			// Write a new line if needed.
			if (YSI_g_sNL)
			{
				fwrite(YSI_g_sCurrentFile, "\n");
			}
			// Insert the `=`.
			dump = next,
			INI_KeyListMakeWritable(dump),
			fwrite(YSI_g_sCurrentFile, INI_KeyListGetKey(dump)),
			next = INI_KeyListGetNext(dump),
			free(dump),
			YSI_g_sNL = true;
		}
	}
}

static stock bool:INI_FreeTag(Alloc:dump)
{
	if (INI_TagListGetDelete(dump))
	{
		new
			Alloc:next = INI_TagListGetEntries(dump);
		INI_TagListSetEntries(dump, 0);
		// This tag is deleted - ignore it entirely.
		while (next)
		{
			dump = next,
			next = INI_KeyListGetNext(dump),
			free(dump);
		}
		return true;
	}
	return false;
}

static stock INI_HandleTag(const tag[]) <y_ini:y_ini_writing_fast, y_ini:y_ini_writing_slow>
{
	// Quickly dump any not written data.  Everything left has no written
	// equivalent, so there's no need to do the slow comparison method.
	INI_DumpTag(YSI_g_sCurrentTag),
	// Determine if we have new data for the current tag or not.
	YSI_g_sCurrentTag = INI_GetTag(YSI_g_sINITagBuffer[YSI_g_sCurrentINI], tag);
	if (YSI_g_sCurrentTag)
	{
		if (INI_FreeTag(YSI_g_sCurrentTag))
		{
			YSI_g_sCurrentTag = NO_ALLOC;
			return 0;
		}
		else if (INI_TagListGetEntries(YSI_g_sCurrentTag))
		{
			// Slightly slower, as for every key we need to check if there is a
			// new value being written.
			state y_ini:y_ini_writing_slow;
		}
		else
		{
			// Nothing to write, just copy all the existing data.
			YSI_g_sCurrentTag = NO_ALLOC;
			state y_ini:y_ini_writing_fast;
		}
	}
	//// Write the tag.
	YSI_g_sTagNeeded = true;
	//if (YSI_g_sNL)
	//{
	//	fwrite(YSI_g_sCurrentFile, "\n");
	//}
	//// TODO: Write parent.
	//fwrite(YSI_g_sCurrentFile, "["),
	//fwrite(YSI_g_sCurrentFile, tag),
	//fwrite(YSI_g_sCurrentFile, "]"),
	//YSI_g_sNL = true;
	// Parse this tag, but not its parents.
	return 1;
}

static stock INI_HandleTag(const tag[]) <
	y_ini:y_ini_reading_yyyy, y_ini:y_ini_reading_yyyn,
	y_ini:y_ini_reading_yyny, y_ini:y_ini_reading_yynn,
	y_ini:y_ini_reading_ynyy, y_ini:y_ini_reading_ynyn,
	y_ini:y_ini_reading_ynny, y_ini:y_ini_reading_ynnn>
{
	P:5("INI_HandleTag<y> called: %s", tag);
	new
		pos = -1,
		cb[FUNCTION_LENGTH];
	StrCpy(YSI_g_sTag, tag),
	format(cb, sizeof (cb), YSI_g_sFormat, YSI_g_sFile, tag);
	while ((pos = strfind(cb, YSI_SPACE, false, pos + 1)) != -1)
		cb[pos] = '_';
	P:5("INI_HandleTag<y>: Find callback %s", cb);
	return INI_FindCallback(cb) ? -1 : 0;
}

static stock INI_HandleTag(const tag[]) <
	y_ini:y_ini_reading_nyyy, y_ini:y_ini_reading_nyyn,
	y_ini:y_ini_reading_nyny, y_ini:y_ini_reading_nynn,
	y_ini:y_ini_reading_nnyy, y_ini:y_ini_reading_nnyn,
	y_ini:y_ini_reading_nnny, y_ini:y_ini_reading_nnnn>
{
	P:5("INI_HandleTag<n> called: %s", tag);
	new
		pos = -1,
		cb[FUNCTION_LENGTH];
	StrCpy(YSI_g_sTag, tag),
	format(cb, sizeof (cb), YSI_g_sFormat, tag, YSI_g_sFile);
	while ((pos = strfind(cb, YSI_SPACE, false, pos + 1)) != -1)
		cb[pos] = '_';
	P:5("INI_HandleTag<n>: Find callback %s", cb);
	return INI_FindCallback(cb) ? -1 : 0;
}

static stock bool:INI_FindCallback(const cb[]) <y_ini:y_ini_reading_yyyy, y_ini:y_ini_reading_nyyy>
{
	Callback_Restore(YSI_g_sCB_issss);
	return Callback_Find(cb, YSI_g_sCB_issss, YSI_g_sRemote);
}

static stock bool:INI_FindCallback(const cb[]) <y_ini:y_ini_reading_yyyn, y_ini:y_ini_reading_nyyn, y_ini:y_ini_reading_yyny, y_ini:y_ini_reading_nyny>
{
	Callback_Restore(YSI_g_sCB_isss);
	return Callback_Find(cb, YSI_g_sCB_isss, YSI_g_sRemote);
}

static stock bool:INI_FindCallback(const cb[]) <y_ini:y_ini_reading_yynn, y_ini:y_ini_reading_nynn>
{
	Callback_Restore(YSI_g_sCB_iss);
	return Callback_Find(cb, YSI_g_sCB_iss, YSI_g_sRemote);
}

static stock bool:INI_FindCallback(const cb[]) <y_ini:y_ini_reading_ynyy, y_ini:y_ini_reading_nnyy>
{
	Callback_Restore(YSI_g_sCB_ssss);
	return Callback_Find(cb, YSI_g_sCB_ssss, YSI_g_sRemote);
}

static stock bool:INI_FindCallback(const cb[]) <y_ini:y_ini_reading_ynyn, y_ini:y_ini_reading_nnyn, y_ini:y_ini_reading_ynny, y_ini:y_ini_reading_nnny>
{
	Callback_Restore(YSI_g_sCB_sss);
	return Callback_Find(cb, YSI_g_sCB_sss, YSI_g_sRemote);
}

static stock bool:INI_FindCallback(const cb[]) <y_ini:y_ini_reading_ynnn, y_ini:y_ini_reading_nnnn>
{
	Callback_Restore(YSI_g_sCB_ss);
	return Callback_Find(cb, YSI_g_sCB_ss, YSI_g_sRemote);
}

static stock bool:INI_FindCallback(const cb[]) <>
{
	#pragma unused cb
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Clean up once all the file has been read.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock INI_HandleEnd() <y_ini:y_ini_writing_fast, y_ini:y_ini_writing_slow>
{
	// Dump the remaining data.
	INI_DumpTag(YSI_g_sCurrentTag);
	new
		Alloc:tag = NO_ALLOC,
		Alloc:next = YSI_g_sINITagBuffer[YSI_g_sCurrentINI];
	while (next)
	{
		tag = next;
		if (!INI_FreeTag(tag) && INI_TagListGetEntries(tag))
		{
			if (YSI_g_sNL)
			{
				fwrite(YSI_g_sCurrentFile, "\n");
			}
			fwrite(YSI_g_sCurrentFile, "["),
			fwrite(YSI_g_sCurrentFile, INI_TagListGetName(tag));
			fwrite(YSI_g_sCurrentFile, "]"),
			YSI_g_sNL = true,
			INI_DumpTag(tag);
		}
		next = INI_TagListGetNext(tag),
		free(tag);
	}
	YSI_g_sINITagBuffer[YSI_g_sCurrentINI] = NO_ALLOC,
	fwrite(YSI_g_sCurrentFile, "\n\n");
}

static stock INI_HandleEnd() <>
{
	// Clean up - release/clear resources.  Notably any claimed callbacks.
	if (YSI_g_sCB_issss)
	{
		Callback_Restore(YSI_g_sCB_issss),
		YSI_g_sCB_issss = Func:0<issss>;
	}
	else if (YSI_g_sCB_isss)
	{
		Callback_Restore(YSI_g_sCB_isss),
		YSI_g_sCB_isss = Func:0<isss>;
	}
	else if (YSI_g_sCB_iss)
	{
		Callback_Restore(YSI_g_sCB_iss),
		YSI_g_sCB_iss = Func:0<iss>;
	}
	else if (YSI_g_sCB_ssss)
	{
		Callback_Restore(YSI_g_sCB_ssss),
		YSI_g_sCB_ssss = Func:0<ssss>;
	}
	else if (YSI_g_sCB_sss)
	{
		Callback_Restore(YSI_g_sCB_sss),
		YSI_g_sCB_sss = Func:0<sss>;
	}
	else if (YSI_g_sCB_ss)
	{
		Callback_Restore(YSI_g_sCB_ss),
		YSI_g_sCB_ss = Func:0<ss>;
	}
	if (YSI_g_sExtendedLine)
	{
		free(YSI_g_sExtendedLine),
		YSI_g_sExtendedLine = NO_ALLOC,
		YSI_g_sExtendedName[0] = '\0';
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="file">INI file to write to disk now.</param>
 * <param name="restoreTag">After writing, reset the current tag?</param>
 * <remarks>
 *  Dumps all the current data to disk.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock INI_Flush_(INI:file)
{
	YSI_g_sNL = false;
	YSI_g_sTagNeeded = false;
	YSI_g_sCurrentFile = ftemp();
	if (!YSI_g_sCurrentFile)
	{
		return;
	}
	state y_ini:y_ini_writing_fast;
	// Parse the file, writing as we go.
	YSI_g_sCurrentTag = INI_GetTag(YSI_g_sINITagBuffer[YSI_g_sCurrentINI], YSI_EMPTY);
	if (YSI_g_sCurrentTag)
	{
		// You can't delete the no-tag tag.
		if (INI_TagListGetEntries(YSI_g_sCurrentTag))
		{
			// Slightly slower, as for every key we need to check if there is a
			// new value being written.
			state y_ini:y_ini_writing_slow;
		}
		else
		{
			// Nothing to write, just copy all the existing data.
			YSI_g_sCurrentTag = NO_ALLOC;
		}
	}
	YSI_g_sCurrentINI = file;
	new
		File:fhnd = fopen(YSI_g_sINIWriteFile[file], io_read);
	if (!fhnd)
	{
		// Dump the file.
		fclose(YSI_g_sCurrentFile);
		YSI_g_sCurrentFile = fopen(YSI_g_sINIWriteFile[file], io_write);
		if (!YSI_g_sCurrentFile)
		{
			return;
		}
		INI_HandleEnd();
		return;
	}
	// Now parse the file.
	{
		new parent[FUNCTION_LENGTH] = "";
		INI_ReadFile(fhnd, parent);
	}
	fclose(fhnd),
	Files_DoCopy(YSI_g_sCurrentFile, YSI_g_sINIWriteFile[file]);
}

static stock INI_FlushWithRestore(INI:file)
{
	new
		tag[MAX_INI_TAG],
		bool:deleted = INI_TagListGetDelete(YSI_g_sINICurrentTag[file]);
	mgets(tag, MAX_INI_TAG, YSI_g_sINICurrentTag[file], 3);
	INI_Flush_(file);
	// Don't forget to restore if this tag is deleted.
	INI_SetTag_(file, tag);
	INI_TagListSetDelete(YSI_g_sINICurrentTag[file], deleted);
}

static stock INI_FlushWithoutRestore(INI:file)
{
	// This is to avoid a recursive function.  Previously `INI_Flush` took a
	// parameter to restore the tag or not.  `INI_SetTag` always set that to
	// `false`, which meant that no recursive call could ever happen.  However,
	// the compiler didn't know that.  This way just ensures it isn't possible.
	INI_Flush_(file);
}

