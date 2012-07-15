/*----------------------------------------------------------------------------*\
					===========================
					Y Sever Includes - INI Core
					===========================
Description:
	Reads the INI and also exports a number of functions to other "classes" for
	easy reading of data files there.
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
	
	The Original Code is the YSI ini include.
	
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
	08/09/10:
		Started adding sscanf and file plugin compatibility.
		Added tagless data at the start of a file (dini compatible).
		Added new INI:file[tag]() syntax.
		Added options to default file load.
		Fixed bugs in default file load configuration.
		Modified to be stand alone.
	20/02/08:
		Added INI_RemoveEntry.
	18/08/07:
		Fixed bug reading identifiers starting with a tag (i.e. names).
		Added local file reading for non-serverwide broadcasting.
		Added tag passing instead of tag based functions option.
		Increased default pool size.
	30/07/07:
		Added auto creation of non-existant files.
	13/07/07:
		Fixed INI writing to actually work.
		Added support for blank lines in INIs decently and quickly.
	25/06/07:
		Altered file write options to use lists.
		Added buffer overwriting for updating values.
	24/06/07:
		Added file write options.
	21/06/07:
		Added INI_NEW_LINE for future writing functions.
	20/06/07:
		Added support for an optional parameter in broadcastfunc data.
	15/04/07:
		Updated for more whitespaces.
		Added INI comment code.
		Added support for value-less entries.
		Modified entry extraction to use end of name location parameter.
		Removed INI_GetTagName, now done via INI_GetEntryName.
	14/04/07:
		Updated header documentation with more than changelog.
	24/03/07:
		First version.
Functions:
	Public:
		-
	Core:
		-
	Stock:
		INI_Load - Loads an INI file using standard features.
		INI_ParseFile - Loads a file as an ini and distributes data.
		INI_GetEntryName - Gets the name of an INI item.
		INI_GetEntryText - Gets the value of an INI item.
		INI_Open - Opens an INI for writing.
		INI_Close - Closes an INI being written to.
		INI_SetTag - Sets a subheading in an INI fo subsequent writes.
		INI_WriteString - Writes a string to an INI.
		INI_WriteInt - Writes an int to an INI.
		INI_WriteFloat - Writes a float to an INI.
		INI_WriteHex - Writes a hex to an INI.
		INI_WriteBin - Writes a binary to an INI.
		INI_WriteBool - Writes a boolean to an INI.
		INI_RemoveEntry - Remove an entry from a file.
	Static:
		INI_WriteBuffer - Writes an INI's buffer to the file.
		INI_AddToBuffer - Adds a string to an INI buffer.
	Inline:
		INI_Int - Parse an integer INI entry.
		INI_Float - Parse a float INI entry.
		INI_Hex - Parse a hex INI entry.
		INI_Bin - Parse a binary INI entry.
		INI_Bool - Parse a binary INI entry.
		INI_String - Parse a string INI entry.
	API:
		-
Callbacks:
	-
Definitions:
	MAX_INI_TAG - Maximum length of an INI tagname.
	MAX_INI_ENTRY_NAME - Maximum length of an INI entry name.
	MAX_INI_ENTRY_TEXT - Maximum length of an INI's entries' value.
	MAX_INI_LINE - Maximum length of a line in a file.
	INI_NEW_LINE - String for new lines.
	INI_MAX_WRITES - Maximum concurrent files open for writing.
	MAX_INI_TAGS - Number of tags the buffer can hold data for at once.
Enums:
	E_INI_WRITE - Storage for entries to be written.
	E_INI_TAGS - Data for tags with data.
Macros:
	INI_Parse - Header for ini parsing functions.
Tags:
	INI - Handle to an INI file being written to.
Variables:
	Global:
		-
	Static:
		YSI_g_sINIWriteBuffer - Basic data to be written.
		YSI_g_sINIWritePos - Next slot to write to.
		YSI_g_sINITagPos - Next slot to add a tag to.
		YSI_g_sINICurrentTag - Pointer to the tag been writen to.
		YSI_g_sINIWriteTag - Data for tags,
		YSI_g_sINIWriteFile - Current files been written to.
Commands:
	-
Compile options:
	-
Operators:
	-
\*----------------------------------------------------------------------------*/

// Ini file reading is not distributed.  User file reading may be, though I
// doubt it.

#include "internal\y_version"

//#tryinclude <sscanf>

#include "y_utils"
#include "y_bit"
#include "y_debug"
#include "y_inline"

#include "internal\y_natives"

#define MAX_INI_LINE                    (MAX_INI_ENTRY_NAME + MAX_INI_ENTRY_TEXT + 32)

#define INI_NO_FILE                     (INI:-1)

#if !defined INI_NEW_LINE
	#define INI_NEW_LINE                "\r\n"
#endif

#if !defined MAX_INI_TAG
	#define MAX_INI_TAG                 (32)
#endif

#if !defined MAX_INI_ENTRY_NAME
	#define MAX_INI_ENTRY_NAME          (32)
#endif

#if !defined MAX_INI_ENTRY_TEXT
	#define MAX_INI_ENTRY_TEXT          YSI_MAX_STRING
#endif

#if !defined INI_MAX_WRITES
	// I doubt many people will use the multiple ini function.
	#define INI_MAX_WRITES              (2)
#endif

#if !defined INI_BUFFER_SIZE
	#define INI_BUFFER_SIZE             (64)
#endif

/*#if INI_BUFFER_SIZE <= 32
	#define INI_BUFFER_BITS 2
#else
	#define INI_BUFFER_BITS Bit_Bits(INI_BUFFER_SIZE)
#endif*/

#if !defined MAX_INI_TAGS
	#define MAX_INI_TAGS 3
/*#else
	#if MAX_INI_TAGS > 32
		#error Current code only supports up to 32 buffer tags
	#endif*/
#endif

//#define MAX_INI_STRING                  (64)

#define MAX_INI_STRING                  FUNCTION_LENGTH

#define Y_INI_WRITE_ARRAY_SIZE ((MAX_INI_ENTRY_TEXT - 1) / 16 * 16)

enum E_INI_WRITE
{
	E_INI_WRITE_NAME[MAX_INI_ENTRY_NAME],
	E_INI_WRITE_TEXT[MAX_INI_ENTRY_TEXT],
	E_INI_WRITE_NEXT
}

enum E_INI_TAGS
{
	E_INI_TAGS_NAME[MAX_INI_TAG char],
	E_INI_TAGS_START,
	E_INI_TAGS_LAST
}

static stock
	YSI_g_sINIWriteBuffer[INI_MAX_WRITES][INI_BUFFER_SIZE][E_INI_WRITE],
	YSI_g_sINIWritePos[INI_MAX_WRITES],
	YSI_g_sINITagPos[INI_MAX_WRITES],
	YSI_g_sINICurrentTag[INI_MAX_WRITES],
	YSI_g_sINIWriteTag[INI_MAX_WRITES][MAX_INI_TAGS][E_INI_TAGS],
	YSI_g_sINIWriteFile[INI_MAX_WRITES][YSI_MAX_STRING];

#define INI_Parse(%1,%2) \
	forward @INI_%1_%2(name[], value[]); \
	@INI_%1_%2(name[], value[])

#define INI:%0[%1](%2) \
	forward @INI_%0_%1(%2); \
	@INI_%0_%1(%2)

#if defined _inc_sscanf && 0
	/*------------------------------------------------------------------------*-
	Function:
		INI_Int
	Params:
		name[] - Name of the INI textual identifier.
		function - Function to call with integer value.
	Return:
		function().
	Notes:
		-
	-*------------------------------------------------------------------------*/
	
	#define INI_Int(%1,%2) \
		if(!strcmp((%1),name,true)&&!sscanf(value,"d",%2))return;
		//if(!strcmp(){%2=floatstr(value);return;}
		//if (!strcmp((%1), name, true)) return %2(strval(value))
	
	/*------------------------------------------------------------------------*-
	Function:
		INI_Float
	Params:
		name[] - Name of the INI textual identifier.
		function - Function to call with float value.
	Return:
		function().
	Notes:
		-
	-*------------------------------------------------------------------------*/
	
	#define INI_Float(%1,%2) \
		if(!strcmp((%1),name,true)&&!sscanf(value,"f",%2))return;
		//if (!strcmp((%1), name, true)) return %2(floatstr(value))
	
	/*------------------------------------------------------------------------*-
	Function:
		INI_Hex
	Params:
		name[] - Name of the INI textual identifier.
		function - Function to call with hex value.
	Return:
		function().
	Notes:
		-
	-*------------------------------------------------------------------------*/
	
	#define INI_Hex(%1,%2) \
		if(!strcmp((%1),name,true)&&!sscanf(value,"h",%2))return;
		//if (!strcmp((%1), name, true)) return %2(hexstr(value))
	
	/*------------------------------------------------------------------------*-
	Function:
		INI_Bin
	Params:
		name[] - Name of the INI textual identifier.
		function - Function to call with binary value.
	Return:
		function().
	Notes:
		-
	-*------------------------------------------------------------------------*/
	
	#define INI_Bin(%1,%2) \
		if(!strcmp((%1),name,true)&&!sscanf(value,"l",%2))return;
		//if (!strcmp((%1), name, true)) return %2(binstr(value))
	
	/*------------------------------------------------------------------------*-
	Function:
		INI_String
	Params:
		name[] - Name of the INI textual identifier.
		function - Function to call with string value.
	Return:
		function().
	Notes:
		-
	-*------------------------------------------------------------------------*/
	
	#define INI_String(%1,%2,%3) \
		if(!strcmp((%1),name,true)&&!sscanf(value,"s["#%3"]",%2))return;
		//if (!strcmp((%1), name, true)) return %2(value)
#else
	#define INI_Int(%1,%2) \
		if(!strcmp((%1),name,true))return %2=strval(value)
	
	#define INI_Float(%1,%2) \
		if(!strcmp((%1),name,true))return _:(%2=floatstr(value))
	
	#define INI_Hex(%1,%2) \
		if(!strcmp((%1),name,true))return %2=hexstr(value)
	
	#define INI_Bin(%1,%2) \
		if(!strcmp((%1),name,true))return %2=binstr(value)
	
	#define INI_Bool(%1,%2) \
		if(!strcmp((%1),name,true))return %2=boolstr(value)
	
	#define INI_String(%1,%2,%3) \
		if(!strcmp((%1),name,true))return strcpy(%2,value,%3)
#endif

/*----------------------------------------------------------------------------*\
Function:
	INI_GetEntryName
Params:
	source - The string you want to get an entry name from.
	dest - The place you want to store the entry name to
Return:
	bool: Found the name correctly.
Notes:
	-
\*----------------------------------------------------------------------------*/

stock bool:INI_GetEntryName(source[], dest[], &i)
{
	P:3("bool:INI_GetEntryName called: \"%s\", %i, %i", source, dest, i);
	new
		j;
	while (source[j] && source[j] <= ' ') j++;
	P:7("bool:INI_GetEntryName: progress 0");
	i = j;
	while (source[i] > ' ' && source[i] != '=') i++;
	P:7("bool:INI_GetEntryName: progress 1");
	if (i == j) return false;
	P:7("bool:INI_GetEntryName: progress 2");
	i -= j;
	memcpy(dest, source, j, i * 4, MAX_INI_ENTRY_NAME);
	dest[i] = '\0';
	P:7("bool:INI_GetEntryName: progress 3, %s, %i, %s", dest, i, source);
	return true;
}

/*----------------------------------------------------------------------------*\
Function:
	INI_GetEntryText
Params:
	source - The string you want to get an entry from.
	dest - The place you want to store the entry to
Return:
	-
Notes:
\*----------------------------------------------------------------------------*/

stock INI_GetEntryText(source[], dest[], i)
{
	P:3("INI_GetEntryText called: \"%s\", %i, %i", source, dest, i);
	while ('\0' < source[i] <= ' ')
	{
		++i;
	}
	P:7("bool:INI_GetEntryText: progress 1");
	if (source[i] == '=')
	{
		while ('\0' < source[++i] <= ' ')
		{
			// Do nothing.
		}
	}
	P:7("bool:INI_GetEntryText: progress 2");
	while (source[i] && (source[i] <= ' ' || source[i] == '=')) i++;
	//while (source[i] && (source[i] <= ' ' || source[i] == '=')) i++;
	P:7("bool:INI_GetEntryText: progress 3");
	dest[0] = 1;
	dest[1] = '\0';
	if (!source[i]) return;
	P:7("bool:INI_GetEntryText: progress 4, %s, %d, %s", dest, i, source);
	strcpy(dest, source[i], MAX_INI_ENTRY_TEXT);
}

/*----------------------------------------------------------------------------*\
Function:
	INI_ParseFile
Params:
	filename[] - The file to load.
	remoteFormat[] - The format string to generate the remote function to
		pass the data to once loaded.
	bool:bFileFirst - The order of the remoteFormat parameters.
	bool:bExtra - Send additional data.
	extra - Additional data to send.
	bLocal - Call local functions instead of gloabal ones.
	bPassTag - Pass the tag as an extra parameter not the function name.
	bFilter - Apply the tag name filter to all tags or just prefixed ones?
	filter - Text to use to search for which tags to load.
Return:
	-
Notes:
	bFileFirst sets the order and inclusion of the possible remoteFormat
	parameters.  If true the format will add the filename first then the 
	current tag, if false the order will be reversed.  This can also be used
	to exclude one or the other from the function name by setting the required
	parameter to be entered first and then only haing one %s in the format
	sting.  The default order is tag first for languages compatability.
\*----------------------------------------------------------------------------*/

stock bool:INI_ParseFile(fname[], remoteFormat[], bool:bFileFirst = false, bool:bExtra = false, extra = 0, bool:bLocal = true, bool:bPassTag = false, bool:bFilter = true, filter[] = "")
{
	P:3("bool:INI_ParseFile called: \"%s\", \"%s\", %i, %i, %i, %i, %i", fname, remoteFormat, bFileFirst, bExtra, extra, bLocal, bPassTag);
	new
		File:f,
		filename[64],
		callbackFormat;
	if (bExtra)
	{
		if (bPassTag) callbackFormat = _F<isss>;
		else callbackFormat = _F<iss>;
	}
	else
	{
		if (bPassTag) callbackFormat = _F<sss>;
		else callbackFormat = _F<ss>;
	}
	strcpy(filename, fname, 64);
	if (!(f = fopen(filename, io_read))) return false;
	P:5("INI_ParseFile: open");
	new
		line[MAX_INI_LINE],
		tagName[MAX_INI_STRING] = "\1\0",
		function[MAX_INI_STRING],
		comment,
		pos,
		bool:bCallback,
		callback[E_CALLBACK_DATA];
	// Strip the extension from the filename.
	comment = chrfind('.', filename);
	if (comment != -1) filename[comment] = '\0';
	// Now reduce it to only the filename, no path.
	while (comment != -1)
	{
		if (filename[comment] == '\\' || filename[comment] == '/')
		{
			//strcpy(filename, filename[comment + 1], MAX_INI_STRING);
			++comment;
			new
				i = 0;
			while ((filename[i] = filename[comment + i]))
			{
				++i;
			}
			break;
		}
		--comment;
	}
	P:5("INI_ParseFile: filename only");
	// Set the default tag value.
	if (bFileFirst)
	{
		format(function, sizeof (function), remoteFormat, filename, "");
	}
	else
	{
		format(function, sizeof (function), remoteFormat, "", filename);
	}
	if (bLocal)
	{
		bCallback = bool:Callback_Get(callback_tag:function, callback, callbackFormat);
	}
	// Now read in the whole data.
	P:5("INI_ParseFile: parse");
	while (fread(f, line))
	{
		StripNL(line);
		if (!line[0]) continue;
		new
			stringIdent[MAX_INI_ENTRY_NAME];
		comment = chrfind(';', line);
		if (comment != -1)
		{
			line[comment] = '\0';
		}
		if (!INI_GetEntryName(line, stringIdent, pos))
		{
			continue;
		}
		if (stringIdent[0] == '[' && (comment = chrfind(']', stringIdent)) != -1 && !stringIdent[comment + 1])
		{
			// Got a tag, update the function to call.
			stringIdent[comment] = '\0';
			P:5("INI_ParseFile: Is checkable %d %d %d", stringIdent[1] == '@', stringIdent[2] == '@', (comment = chrfind('-', stringIdent)) != -1);
			if (stringIdent[1] == '@' && stringIdent[2] == '@' && (comment = chrfind('-', stringIdent)) != -1)
			{
				// We are keeping the ability to filter by tag names, but now
				// we are just using the existing unique tag load code in y_ini.
				stringIdent[comment] = '\0';
				P:5("INI_ParseFile: SingleTag check");
				if (strcmp(filter, stringIdent[3]))
				{
					P:5("INI_ParseFile: Not this time");
					// Skip tags we don't care about.  This will not skip
					// anything if the passed tag is "" (here I'm (ab)using the
					// fact that "strcmp" returns 0 when an empty string is
					// involved).
					function[0] = '\0';
					continue;
				}
				stringIdent[comment] = '-';
				++comment;
			}
			else
			{
				P:5("INI_ParseFile: SingleTag check");
				// Apply the filter to non-prefixed tags if desired.
				if (bFilter && strcmp(filter, stringIdent[1]))
				{
					P:5("INI_ParseFile: Not this time");
					// Skip tags we don't care about.  This will not skip
					// anything if the passed tag is "" (here I'm (ab)using the
					// fact that "strcmp" returns 0 when an empty string is
					// involved).
					function[0] = '\0';
					continue;
				}
				comment = 1;
			}
			if (bFileFirst)
			{
				format(function, sizeof (function), remoteFormat, filename, stringIdent[comment]);
			}
			else
			{
				format(function, sizeof (function), remoteFormat, stringIdent[comment], filename);
			}
			if (bLocal)
			{
				bCallback = bool:Callback_Get(callback_tag:function, callback, callbackFormat);
			}
			P:5("INI_ParseFile: Call it \"%s\", %d, %d", function, bLocal, funcidx(function) == -1);
			// Skip complex checks where possible.
			if (bLocal && funcidx(function) == -1)
			{
				// This needs updating for inline functions.
				function[0] = '\0';
			}
			else
			{
				if (bPassTag)
				{
					strcpy(tagName, stringIdent[1], MAX_INI_STRING);
				}
			}
		}
		else if (function[0])
		{
			new
				stringText[MAX_INI_ENTRY_TEXT];
			INI_GetEntryText(line, stringText, pos);
			// Read in a value - distribute it as required.
			if (bCallback)
			{
				if (bExtra)
				{
					if (bPassTag)
					{
						Callback_Call(callback, extra, tagName, stringIdent, stringText);
						//CallLocalFunction(function, "isss", extra, tagName, stringIdent, stringText);
					}
					else
					{
						Callback_Call(callback, extra, stringIdent, stringText);
						//CallLocalFunction(function, "iss", extra, stringIdent, stringText);
					}
				}
				else
				{
					if (bPassTag)
					{
						Callback_Call(callback, tagName, stringIdent, stringText);
						//CallLocalFunction(function, "sss", tagName, stringIdent, stringText);
					}
					else
					{
						Callback_Call(callback, stringIdent, stringText);
						//CallLocalFunction(function, "ss", stringIdent, stringText);
					}
				}
			}
			else if (!bLocal)
			{
				// Can't use inilne functions remotely (it makes no sense at all
				// - inline functions come from the call point, and the call
				// point is in this local script.
				if (bExtra)
				{
					if (bPassTag)
					{
						CallRemoteFunction(function, "isss", extra, tagName, stringIdent, stringText);
					}
					else
					{
						CallRemoteFunction(function, "iss", extra, stringIdent, stringText);
					}
				}
				else
				{
					if (bPassTag)
					{
						CallRemoteFunction(function, "sss", tagName, stringIdent, stringText);
					}
					else
					{
						CallRemoteFunction(function, "ss", stringIdent, stringText);
					}
				}
			}
		}
	}
	fclose(f);
	return true;
}

/*----------------------------------------------------------------------------*\
Function:
	INI_Load
Params:
	filename[] - The file to load.
	bool:bExtra - Send additional data.
	extra - Additional data to send.
	bLocal - Call local functions instead of gloabal ones.
Return:
	INI_ParseFile
Notes:
	Wrapper for INI_ParseFile to use standard API features so people can
	worry even less.  Designed for use with INI_Parse.
\*----------------------------------------------------------------------------*/

stock bool:INI_Load(filename[], bool:bExtra = false, extra = 0, bool:bLocal = true)
{
	P:3("bool:INI_Load called: \"%s\", %i, %i, %i", filename, _:bExtra, extra, _:bLocal);
	return INI_ParseFile(filename, "@INI_%s_%s", true, bExtra, extra, bLocal, false);
}

/*----------------------------------------------------------------------------*\
Function:
	INI_Open
Params:
	filename[] - INI file to open.
Return:
	INI - handle to the file or INI_NO_FILE.
Notes:
	Doesn't actually open the file, just starts a new buffer if possible.
\*----------------------------------------------------------------------------*/

stock INI:INI_Open(filename[])
{
	if (ftouch(filename) == -1)
	{
		P:E("INI_Open could not find or create file %s", filename);
	}
	P:3("INI:INI_Open called: \"%s\"", filename);
	new
		i;
	for (i = 0; i < INI_MAX_WRITES; i++)
	{
		if (!YSI_g_sINIWriteFile[i][0]) break;
	}
	if (i == INI_MAX_WRITES)
	{
		return INI_NO_FILE;
	}
	strcpy(YSI_g_sINIWriteFile[i], filename, sizeof (YSI_g_sINIWriteFile[]));
	YSI_g_sINIWritePos[i] = 0;
	YSI_g_sINITagPos[i] = 0;
	// Reset tags.
	YSI_g_sINICurrentTag[i] = 0;
	YSI_g_sINIWriteTag[i][0][E_INI_TAGS_NAME][0] = '\0';
	YSI_g_sINIWriteTag[i][0][E_INI_TAGS_START] = -1;
/*	if (!fexist(filename))
	{
		new
			File:fHnd = fopen(filename, io_write);
		if (fHnd)
		{
			fclose(fHnd);
		}
		else P:E("Could not create target file");
	}*/
	return INI:i;
}

/*----------------------------------------------------------------------------*\
Function:
	INI_Close
Params:
	INI:file - Handle to the ini to close.
Return:
	-
Notes:
	Writes any outstanding buffer data to the file and ends the stream.
\*----------------------------------------------------------------------------*/

stock INI_Close(INI:file)
{
	P:3("INI_Close called: %i", _:file);
	if (YSI_g_sINIWritePos[_:file] || YSI_g_sINITagPos[_:file]) INI_WriteBuffer(file);
	YSI_g_sINIWriteFile[_:file][0] = '\0';
}

/*----------------------------------------------------------------------------*\
Function:
	INI_SetTag
Params:
	INI:file - INI file handle to write to.
	tag[] - Name of the new file subsection for subsequent data to write to.
Return:
	-
Notes:
	Sets a new [tag] section header.  Subsequent data is written under this
	header.  Uses lists for constant tag switching and checks the tag doesn't
	already exist.
\*----------------------------------------------------------------------------*/

stock INI_SetTag(INI:file, tag[])
{
	P:3("INI_SetTag called: %i, \"%s\"", _:file, tag);
	if (file < INI:0 || file >= INI:INI_MAX_WRITES) return;
	new
		pos = YSI_g_sINITagPos[_:file];
	for (new i = 0; i < pos; i++)
	{
		if (YSI_g_sINIWriteTag[_:file][i][E_INI_TAGS_NAME][0] && !strcmp(tag, YSI_g_sINIWriteTag[_:file][i][E_INI_TAGS_NAME], true))
		{
			YSI_g_sINICurrentTag[_:file] = i;
			return;
		}
	}
	// Allow untagged data (not sure how it will go down...).
	/*if (pos == 0 && YSI_g_sINIWriteTag[_:file][0][E_INI_TAGS_START] != -1)
	{
		++pos;
		++YSI_g_sINITagPos[_:file];
	}*/
	if (pos >= MAX_INI_TAGS)
	{
		if (!INI_WriteBuffer(file)) return;
		// Loop.
		pos = 0;
	}
	//strcpy(YSI_g_sINIWriteTag[_:file][pos][E_INI_TAGS_NAME], tag, MAX_INI_TAG);
	strpack(YSI_g_sINIWriteTag[_:file][pos][E_INI_TAGS_NAME], tag, MAX_INI_TAG);
	YSI_g_sINIWriteTag[_:file][pos][E_INI_TAGS_START] = -1;
	YSI_g_sINICurrentTag[_:file] = pos;
	++YSI_g_sINITagPos[_:file];
}

/*----------------------------------------------------------------------------*\
Function:
	INI_DeleteTag
Params:
	INI:file - INI file handle to write to.
	tag[] - Name of the whole section to delete.
Return:
	-
Notes:
	Removes a [tag] section from a file.
\*----------------------------------------------------------------------------*/

stock INI_DeleteTag(INI:file, tag[])
{
	P:3("INI_DeleteTag called: %i, \"%s\"", _:file, tag);
	if (file < INI:0 || file >= INI:INI_MAX_WRITES) return;
	new
		pos = YSI_g_sINITagPos[_:file];
	for (new i = 0; i < pos; i++)
	{
		P:6("INI_DeleteTag: %i, \"%s\", \"%s\"", i, tag, unpack(YSI_g_sINIWriteTag[_:file][i][E_INI_TAGS_NAME]));
		if (YSI_g_sINIWriteTag[_:file][i][E_INI_TAGS_NAME][0] && !strcmp(tag, YSI_g_sINIWriteTag[_:file][i][E_INI_TAGS_NAME], true))
		{
			YSI_g_sINICurrentTag[_:file] = i;
			YSI_g_sINIWriteTag[_:file][i][E_INI_TAGS_START] = cellmax;
			return;
		}
	}
	if (pos >= MAX_INI_TAGS)
	{
		if (!INI_WriteBuffer(file)) return;
		// Loop.
		pos = 0;
	}
	strpack(YSI_g_sINIWriteTag[_:file][pos][E_INI_TAGS_NAME], tag, MAX_INI_TAG);
	YSI_g_sINIWriteTag[_:file][pos][E_INI_TAGS_START] = cellmax;
	YSI_g_sINICurrentTag[_:file] = pos;
	++YSI_g_sINITagPos[_:file];
}

stock INI_WriteArray(INI:file, const name[], data[], len)
{
	// Write 6 bits at a time, in 3 cell chunks.  It takes 16 bytes to record
	// three cells with 6 bits per byte.
	P:4("INI_WriteArray called");
	new
		dname[MAX_INI_ENTRY_NAME],
		write[Y_INI_WRITE_ARRAY_SIZE + 1],
		idx,
		wi,
		iter;
	// Write the length first just so the data exists.
	//INI_WriteInt(file, name, len);
	valstr(write, len);
	INI_AddToBuffer(file, name, write);
	write[0] = '\0';
	while (idx + 3 < len)
	{
		// Store all the data fast.
		//write[wi++] = (((data[idx] & 0xFC000000) >>> 2) | ((data[idx] & 0x03F00000) >> 4) | ((data[idx] & 0x000FC000) >> 6) | ((data[idx] & 0x00003F00) >> 8))
		write[wi++] = ((data[idx] & 0xFC000000) >>> 26) + '>';
		write[wi++] = ((data[idx] & 0x03F00000) >>> 20) + '>';
		write[wi++] = ((data[idx] & 0x000FC000) >>> 14) + '>';
		write[wi++] = ((data[idx] & 0x00003F00) >>> 8) + '>';
		//write[wi++] = (((data[idx - 1] & 0x000000FC) << 22) | ((data[idx - 1] & 0x00000003) << 20) | ((data[idx] & 0xF0000000) >>> 12) | ((data[idx] & 0x0FC00000) >> 14) | ((data[idx] & 0x003F0000) >> 16))
		write[wi++] = ((data[idx] & 0x000000FC) >>> 2) + '>';
		write[wi++] = (((data[idx] & 0x00000003) << 4) | ((data[idx + 1] & 0xF0000000) >>> 28)) + '>';
		++idx;
		write[wi++] = ((data[idx] & 0x0FC00000) >>> 22) + '>';
		write[wi++] = ((data[idx] & 0x003F0000) >>> 16) + '>';
		//write[wi++] = (((data[idx] & 0x0000FC00) << 14) | ((data[idx] & 0x000003F0) << 12) | ((data[idx] & 0x0000000F) << 10) | ((data[idx + 1] & 0xC0000000) >>> 22) | ((data[idx + 1] & 0x3F000000) >> 24))
		write[wi++] = ((data[idx] & 0x0000FC00) >>> 10) + '>';
		write[wi++] = ((data[idx] & 0x000003F0) >>> 4) + '>';
		write[wi++] = (((data[idx] & 0x0000000F) << 2) | ((data[idx + 1] & 0xC0000000) >>> 30)) + '>';
		++idx;
		write[wi++] = ((data[idx] & 0x3F000000) >>> 24) + '>';
		//write[wi++] = (((data[idx] & 0x00FC0000) << 6) | ((data[idx] & 0x0003F000) << 4) | ((data[idx] & 0x00000FC0) << 2) | ((data[idx] & 0x0000003F) << 0))
		write[wi++] = ((data[idx] & 0x00FC0000) >>> 18) + '>';
		write[wi++] = ((data[idx] & 0x0003F000) >>> 12) + '>';
		write[wi++] = ((data[idx] & 0x00000FC0) >>> 6) + '>';
		write[wi++] = ((data[idx] & 0x0000003F) >>> 0) + '>';
		++idx;
		if (wi == Y_INI_WRITE_ARRAY_SIZE)
		{
			format(dname, sizeof (dname), "@@%s-%d", name, iter++);
			//printf("%s = %s", dname, write);
			P:5("Uvar_WriteArray: write %s = %s", dname, write);
			//Player_WriteString(dname, write);
			write[wi] = '\0';
			INI_AddToBuffer(file, dname, write);
			write[0] = '\0';
			wi = 0;
		}
	}
	// Do the straggling bytes.
	if (idx != len)
	{
		write[wi++] = ((data[idx] & 0xFC000000) >>> 26) + '>';
		write[wi++] = ((data[idx] & 0x03F00000) >>> 20) + '>';
		write[wi++] = ((data[idx] & 0x000FC000) >>> 14) + '>';
		write[wi++] = ((data[idx] & 0x00003F00) >>> 8) + '>';
		//write[wi++] = (((data[idx - 1] & 0x000000FC) << 22) | ((data[idx - 1] & 0x00000003) << 20) | ((data[idx] & 0xF0000000) >>> 12) | ((data[idx] & 0x0FC00000) >> 14) | ((data[idx] & 0x003F0000) >> 16))
		write[wi++] = ((data[idx] & 0x000000FC) >>> 2) + '>';
		if (++idx == len)
		{
			write[wi++] = ((data[idx - 1] & 0x00000003) << 4) + '>';
		}
		else
		{
			write[wi++] = (((data[idx - 1] & 0x00000003) << 4) | ((data[idx] & 0xF0000000) >>> 28)) + '>';
			write[wi++] = ((data[idx] & 0x0FC00000) >>> 22) + '>';
			write[wi++] = ((data[idx] & 0x003F0000) >>> 16) + '>';
			//write[wi++] = (((data[idx] & 0x0000FC00) << 14) | ((data[idx] & 0x000003F0) << 12) | ((data[idx] & 0x0000000F) << 10) | ((data[idx + 1] & 0xC0000000) >>> 22) | ((data[idx + 1] & 0x3F000000) >> 24))
			write[wi++] = ((data[idx] & 0x0000FC00) >>> 10) + '>';
			write[wi++] = ((data[idx] & 0x000003F0) >>> 4) + '>';
			if (++idx == len)
			{
				write[wi++] = ((data[idx - 1] & 0x0000000F) << 2) + '>';
			}
			else
			{
				write[wi++] = (((data[idx - 1] & 0x0000000F) << 2) | ((data[idx] & 0xC0000000) >>> 30)) + '>';
				//++idx;
				write[wi++] = ((data[idx] & 0x3F000000) >>> 24) + '>';
				//write[wi++] = (((data[idx] & 0x00FC0000) << 6) | ((data[idx] & 0x0003F000) << 4) | ((data[idx] & 0x00000FC0) << 2) | ((data[idx] & 0x0000003F) << 0))
				write[wi++] = ((data[idx] & 0x00FC0000) >>> 18) + '>';
				write[wi++] = ((data[idx] & 0x0003F000) >>> 12) + '>';
				write[wi++] = ((data[idx] & 0x00000FC0) >>> 6) + '>';
				write[wi++] = ((data[idx] & 0x0000003F) >>> 0) + '>';
			}
		}
		format(dname, sizeof (dname), "@@%s-%d", name, iter++);
		//printf("%s = %s", dname, write);
		P:5("Uvar_WriteArray: write %s = %s", dname, write);
		//Player_WriteString(dname, write);
		write[wi] = '\0';
		INI_AddToBuffer(file, dname, write);
		write[0] = '\0';
		wi = 0;
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	INI_AddToBuffer
Params:
	INI:file - INI file to write to.
	name[] - Data name to write.
	data[] - Data to write.
Return:
	-
Notes:
	First checks the name doesn't already exist under the current tag header
	and if it does overwrites the current value.  If not checks there's room
	in the buffer to write to and purges the buffer if not.  Finally saves the
	data in the buffer for writing when required and adds the data to the
	relevant list for tag inclusion.
\*----------------------------------------------------------------------------*/

static stock INI_AddToBuffer(INI:file, const name[], data[])
{
	P:4("INI_AddToBuffer called: %i, \"%s\", \"%s\"", _:file, name, data);
	if (file < INI:0 || file >= INI:INI_MAX_WRITES)
	{
		return 0;
	}
	if (!YSI_g_sINITagPos[_:file])
	{
		// Tagless data.
		YSI_g_sINITagPos[_:file] = 1;
		YSI_g_sINIWriteTag[_:file][0][E_INI_TAGS_START] = -1;
		YSI_g_sINIWriteTag[_:file][0][E_INI_TAGS_NAME][0] = 0;
	}
	new
		pos = YSI_g_sINIWritePos[_:file],
		tmptag = YSI_g_sINICurrentTag[_:file],
		start = YSI_g_sINIWriteTag[_:file][tmptag][E_INI_TAGS_START];
	if (start == cellmax)
	{
		// Don't write to a deleted tag.
		return 0;
	}
	while (start != -1)
	{
		if (!strcmp(name, YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_NAME], true))
		{
			strcpy(YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_TEXT], data, MAX_INI_ENTRY_TEXT);
			//strpack(YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_TEXT], data, MAX_INI_ENTRY_TEXT);
			return 1;
		}
		start = YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_NEXT];
	}
	if (pos >= INI_BUFFER_SIZE)
	{
		if (!INI_WriteBuffer(file))
		{
			return 0;
		}
		INI_SetTag(file, YSI_g_sINIWriteTag[_:file][tmptag][E_INI_TAGS_NAME]);
		pos = 0;
	}
	new
		curtag = YSI_g_sINICurrentTag[_:file];
	if (YSI_g_sINIWriteTag[_:file][curtag][E_INI_TAGS_START] == -1)
	{
		YSI_g_sINIWriteTag[_:file][curtag][E_INI_TAGS_START] = pos;
	}
	else
	{
		YSI_g_sINIWriteBuffer[_:file][YSI_g_sINIWriteTag[_:file][curtag][E_INI_TAGS_LAST]][E_INI_WRITE_NEXT] = pos;
	}
	strcpy(YSI_g_sINIWriteBuffer[_:file][pos][E_INI_WRITE_NAME], name, MAX_INI_ENTRY_NAME);
	//strpack(YSI_g_sINIWriteBuffer[_:file][pos][E_INI_WRITE_NAME], name, MAX_INI_ENTRY_NAME);
	strcpy(YSI_g_sINIWriteBuffer[_:file][pos][E_INI_WRITE_TEXT], data, MAX_INI_ENTRY_TEXT);
	YSI_g_sINIWriteBuffer[_:file][pos][E_INI_WRITE_NEXT] = -1;
	YSI_g_sINIWriteTag[_:file][curtag][E_INI_TAGS_LAST] = pos;
	YSI_g_sINIWritePos[_:file]++;
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	INI_RemoveEntry
Params:
	INI:file - File to write to.
	name[] - Item to remove.
Return:
	-
Notes:
	Wrapper for INI_AddToBuffer for removing data.
\*----------------------------------------------------------------------------*/

stock INI_RemoveEntry(INI:file, name[])
{
	P:3("INI_RemoveEntry called: %i, \"%s\"", _:file, name);
	static
		sData[2] = {-1, 0};
	INI_AddToBuffer(file, name, sData);
}

/*----------------------------------------------------------------------------*\
Function:
	INI_WriteString
Params:
	INI:file - File to write to.
	name[] - Data name.
	data[] - Data.
Return:
	-
Notes:
	Wrapper for INI_AddToBuffer for strings.
\*----------------------------------------------------------------------------*/

stock INI_WriteString(INI:file, name[], data[])
{
	P:3("INI_WriteString called: %i, \"%s\", \"%s\"", _:file, name, data);
	INI_AddToBuffer(file, name, data);
}

/*----------------------------------------------------------------------------*\
Function:
	INI_WriteInt
Params:
	INI:file - File to write to.
	name[] - Data name.
	data - Integer data.
Return:
	-
Notes:
	Wrapper for INI_AddToBuffer for integers.
\*----------------------------------------------------------------------------*/

stock INI_WriteInt(INI:file, name[], data)
{
	P:3("INI_WriteInt called: %i, \"%s\", %i", _:file, name, data);
	new
		str[12];
	valstr(str, data);
	INI_AddToBuffer(file, name, str);
}

/*----------------------------------------------------------------------------*\
Function:
	INI_WriteHex
Params:
	INI:file - File to write to.
	name[] - Data name.
	data - Hex data.
Return:
	-
Notes:
	Wrapper for INI_AddToBuffer for integers to be written as hex values.
\*----------------------------------------------------------------------------*/

stock INI_WriteHex(INI:file, name[], data)
{
	P:3("INI_WriteHex called: %i, \"%s\", %i", _:file, name, data);
	static const
		sc_values[] = !"0123456789ABCDEF";
	new
		str[11],
		i = 9;
	do
	{
		str[i--] = sc_values{data & 0x0F};
		data >>>= 4;
	}
	while (data);
	str[i--] = 'x';
	str[i] = '0';
	INI_AddToBuffer(file, name, str[i]);
}

/*----------------------------------------------------------------------------*\
Function:
	INI_WriteBin
Params:
	INI:file - File to write to.
	name[] - Data name.
	data - Binary data.
Return:
	-
Notes:
	Wrapper for INI_AddToBuffer for integers to be written as binary values.
\*----------------------------------------------------------------------------*/

stock INI_WriteBin(INI:file, name[], data)
{
	P:3("INI_WriteBin called: %i, \"%s\", %i", _:file, name, data);
	// Do four values at once for speed.  This uses a packed string and unpacks
	// it so that we can quickly write four values at once.
	static const
		sc_values[] = !"0000" "0001" "0010" "0011" "0100" "0101" "0110" "0111" "1000" "1001" "1010" "1011" "1100" "1101" "1110" "1111";
	new
		str[35],
		i = 10;
	do
	{
		str[--i] = sc_values[data & 0x0F];
		data >>>= 4;
	}
	while (data);
	// Convert the coalesced values to individual values.
	strunpack(str[i], str[i], 33);
	str[--i] = 'b';
	str[--i] = '0';
	INI_AddToBuffer(file, name, str[i]);
}

/*----------------------------------------------------------------------------*\
Function:
	INI_WriteBool
Params:
	INI:file - File to write to.
	name[] - Data name.
	data - Boolean data.
Return:
	-
Notes:
	Wrapper for INI_AddToBuffer for booleans.
\*----------------------------------------------------------------------------*/

stock INI_WriteBool(INI:file, name[], bool:data)
{
	P:3("INI_WriteBool called: %i, \"%s\", %i", _:file, name, _:data);
	if (data)
	{
		INI_AddToBuffer(file, name, "true");
	}
	else
	{
		INI_AddToBuffer(file, name, "false");
	}
}

/*----------------------------------------------------------------------------*\
Function:
	INI_WriteFloat
Params:
	INI:file - File to write to.
	name[] - Data name.
	Float:data - Float data.
	accuracy - number of decimal places to write.
Return:
	-
Notes:
	Wrapper for INI_AddToBuffer for floats.  Uses custom code instead of
	format() as it's actually faster for something simple like this.
\*----------------------------------------------------------------------------*/

stock INI_WriteFloat(INI:file, name[], Float:data, accuracy = 6)
{
	P:3("INI_WriteFloat called: %i, \"%s\", %f, %i", _:file, name, data, accuracy);
	new
		str[32];
	format(str, sizeof (str), "%.*f", accuracy, data);
	INI_AddToBuffer(file, name, str);
}

/*----------------------------------------------------------------------------*\
Function:
	INI_WriteBuffer
Params:
	INI:file - INI stream to write to file.
Return:
	Success/fail.
Notes:
	Opens the required file for reading and a temp file for read/writing.  Goes
	through the entire file reading all contained data.  If it reaches a tag
	line ([tag_name]) it dumps any unwritten data from the last tag (if there
	was one) and starts processing the new tag.  While a tag is being processed
	every line is compared against the UNWRITTEN new data for that tag in the
	buffer, if they're the same it writes the new data instead (it also writes
	any comments which were after the data in the original line back), else it
	writes the original line back.
	
	Once all the new data is written to the temp file any tags which haven't
	been processed at all (i.e. were not found in the original file) are
	written to the temp file along with all their data.  The original file is
	then destroyed and reopend and all the data copied out from the temp file
	to the newly opened original file, closed and saved.
\*----------------------------------------------------------------------------*/

static stock INI_WriteBuffer(INI:file)
{
	P:4("INI_WriteBuffer called: %i", _:file);
	if (_:file < 0 || _:file >= INI_MAX_WRITES) return 0;
	new
		//File:buffer = fopen("_temp_ysi_user_file_.ysi", io_write),
		File:buffer = ftemp(),
		File:source = fopen(YSI_g_sINIWriteFile[_:file], io_read);
	if (buffer)
	{
		new
			line[MAX_INI_LINE],
			BitArray:read<INI_BUFFER_SIZE>, //:read[INI_BUFFER_BITS],
			writing = 0,
			skipTag = 0,
			//Bit:tagswritten,
			BitArray:tagswritten<MAX_INI_TAGS>,
			tagpos = YSI_g_sINITagPos[_:file],
			start = -1,
			blank;
		if (source)
		{
			// Write tagless data.
			if (!YSI_g_sINIWriteTag[_:file][0][E_INI_TAGS_NAME][0])
			{
				start = YSI_g_sINIWriteTag[_:file][0][E_INI_TAGS_START];
				// Will be -1 if there is no tagless data.
				if (start != -1)
				{
					if (start == cellmax)
					{
						skipTag = 1;
						start = -1;
					}
					else
					{
						writing = 1;
					}
					Bit_Set(tagswritten, 0, true);
				}
			}
			while (fread(source, line))
			{
				new
					pos = 1;
				for (new i = 0; line[i]; i++)
				{
					if (line[i] == ';')
					{
						goto INI_WriteBuffer_cont1;
					}
					else if (line[i] > ' ')
					{
						// Determine that the line is not blank.
						pos = 0;
						break;
					}
				}
				if (pos)
				{
					blank++;
					continue;
				}
				if (line[0] == '[' && (pos = chrfind(']', line)) != -1 && endofline(line, pos + 1))
				{
					//pos--;
					writing = 0;
					new
						form[MAX_INI_LINE];
					// Reached a new tag - flush the rest of the last tag.
					while (start != -1)
					{
						if (!Bit_GetBit(read, start))
						{
							if (YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_TEXT][0] != -1)
							{
								format(form, sizeof (form), "%s = %s" INI_NEW_LINE, YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_NAME], YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_TEXT]);
								fwrite(buffer, form);
							}
							Bit_Set(read, start, true);
						}
						start = YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_NEXT];
					}
					if (!skipTag)
					{
						while (blank--) fwrite(buffer, INI_NEW_LINE);
					}
					blank = 0;
					skipTag = 0;
					// Note the start of the new tag.
					line[pos] = '\0';
					for (new j = 0; j < tagpos; j++)
					{
						//if (!Bit_Get(tagswritten, j) && !YSI_g_sINIWriteTag[_:file][j][E_INI_TAGS_NAME][pos] && !strcmp(YSI_g_sINIWriteTag[_:file][j][E_INI_TAGS_NAME], line[1], true, pos))
						//printf("compare %d, %s, %s", Bit_Get(tagswritten, j), unpack(YSI_g_sINIWriteTag[_:file][j][E_INI_TAGS_NAME]), line[1]);
						if (!Bit_Get(tagswritten, j) && !strcmp(YSI_g_sINIWriteTag[_:file][j][E_INI_TAGS_NAME], line[1])) //, true, pos))
						{
							/*if (YSI_g_sINIWriteTag[_:file][j][E_INI_TAGS_NAME])
							{
								continue;
							}*/
							start = YSI_g_sINIWriteTag[_:file][j][E_INI_TAGS_START];
							P:7("INI_WriteBuffer: Next tag: %s, %d", line[1], start);
							if (start == cellmax)
							{
								skipTag = 1;
								start = -1;
								writing = 0;
							}
							else
							{
								writing = 1;
							}
							//tagswritten |= Bit:(1 << j);
							Bit_Set(tagswritten, j, true);
							break;
						}
					}
					line[pos--] = ']';
				}
				else if (writing)
				{
					new
						name[MAX_INI_ENTRY_NAME],
						temp,
						liststart = start;
					INI_GetEntryName(line, name, temp);
					pos = chrfind(';', line, temp);
					while (blank--) fwrite(buffer, INI_NEW_LINE);
					blank = 0;
					while (start != -1)
					{
						if (!Bit_GetBit(read, start) && !strcmp(name, YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_NAME]))
						{
							Bit_Set(read, start, true);//, INI_BUFFER_SIZE);
							// Delete the current entry from the file, as per
							// our request.
							if (YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_TEXT][0] == -1)
							{
								// Can't use "continue" as we're in an inner
								// loop.
								goto INI_WriteBuffer_cont2;
							}
							if (pos != -1)
							{
								format(line, sizeof (line), "%s = %s %s", name, YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_TEXT], line[pos]);
							}
							else
							{
								format(line, sizeof (line), "%s = %s" INI_NEW_LINE, name, YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_TEXT]);
							}
							//start = -1;
							break;
						}
						else
						{
							start = YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_NEXT];
						}
					}
					/*if (start == -1)
					{
						// Wasn't found.
						start = strlen(line);
						if (line[start - 1] > ' ')
						{
							strcat(line, INI_NEW_LINE);
						}
					}*/
					start = liststart;
				}
				INI_WriteBuffer_cont1:
				if (!skipTag)
				{
					fwrite(buffer, line);
				}
				INI_WriteBuffer_cont2:
			}
			// Write any data from this tag group not in the original file.
			// I.e. flush the final read tag.
			while (start != -1)
			{
				if (!Bit_GetBit(read, start))
				{
					if (YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_TEXT][0] != -1)
					{
						format(line, sizeof (line), "%s = %s" INI_NEW_LINE, YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_NAME], YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_TEXT]);
						fwrite(buffer, line);
					}
				}
				start = YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_NEXT];
			}
			fclose(source);
		}
		// Write any tag groups not found in the original file.
		//printf("write some tag");
		for (new j = 0; j < tagpos; j++)
		{
			//if (!(tagswritten & Bit:(1 << j)))
			//printf("write this tag: %s", unpack(YSI_g_sINIWriteTag[_:file][j][E_INI_TAGS_NAME]));
			if (!Bit_Get(tagswritten, j))
			{
				start = YSI_g_sINIWriteTag[_:file][j][E_INI_TAGS_START];
				if (start == cellmax)
				{
					continue;
				}
				if (j || YSI_g_sINIWriteTag[_:file][0][E_INI_TAGS_NAME][0])
				{
					strunpack(line, YSI_g_sINIWriteTag[_:file][j][E_INI_TAGS_NAME]);
					format(line, sizeof (line), "[%s]" INI_NEW_LINE, line);
					fwrite(buffer, line);
				}
				while (start != -1)
				{
					if (YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_TEXT][0] != -1)
					{
						format(line, sizeof (line), "%s = %s" INI_NEW_LINE, YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_NAME], YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_TEXT]);
						fwrite(buffer, line);
					}
					start = YSI_g_sINIWriteBuffer[_:file][start][E_INI_WRITE_NEXT];
				}
			}
		}
		//fclose(buffer);
		// This renames the file back (by copying all the data).
		fremove(YSI_g_sINIWriteFile[_:file]);
		#if defined _inc_TODO_COPY_INC
		#else
			#if defined _int_TODO_OTHER_COPY_INC
			#else
				source = fopen(YSI_g_sINIWriteFile[_:file], io_write);
				//buffer = fopen("_temp_ysi_user_file_.ysi", io_read);
				fseek(buffer);
				if (source) // && buffer)
				{
					while (fread(buffer, line)) fwrite(source, line);
					/*new
						val;
					printf("start: %d", _:E_INI_WRITE * INI_BUFFER_SIZE);
					while ((val = fblockread(buffer, YSI_g_sINIWriteBuffer[_:file][0][E_INI_WRITE_NAME], _:E_INI_WRITE * INI_BUFFER_SIZE)))
					{
						printf("%d %d", val, strlen(YSI_g_sINIWriteBuffer[_:file][0][E_INI_WRITE_NAME]));
						printf("%s", YSI_g_sINIWriteBuffer[_:file][0][E_INI_WRITE_NAME]);
						fblockwrite(source, YSI_g_sINIWriteBuffer[_:file][0][E_INI_WRITE_NAME], val);
					}*/
					fclose(buffer);
					fclose(source);
				}
				//fremove("_temp_ysi_user_file_.ysi");
			#endif
		#endif
		// Reset the write buffer.
		YSI_g_sINITagPos[_:file] = 0;
		YSI_g_sINIWritePos[_:file] = 0;
		YSI_g_sINICurrentTag[_:file] = 0;
		return 1;
	}
	return 0;
}
