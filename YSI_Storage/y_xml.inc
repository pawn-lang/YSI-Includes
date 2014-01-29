/**--------------------------------------------------------------------------**\
					=============================
					 y_xml - XML file functions!
					=============================
Description:
	Parses XML files according to a set of defined rules.  A rule is a custom
	function called on a tag when all the data for that tag has been collected.
	The data for a tag could consist of simple bla="bla" pairs, <tag>data</tag>
	pairs or cominations of the two, including subtags, each with their own
	possible custom handlers.
	
	Data for the tag is retrieved from a custom function using only:
	
	while (XML_GetKeyValue(ident, data)) {}
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
	
	The Original Code is the YSI XML include.
	
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
	06/08/10:
		First version
\**--------------------------------------------------------------------------**/

#if defined _INC_y_xml
	#endinput
#endif
#define _INC_y_xml

#include "..\YSI_Internal\y_version"

#include <a_samp>

#include "..\YSI_Core\y_debug"
#include "..\YSI_Core\y_utils"

#include "..\YSI_Internal\y_natives"

#if !defined MAX_XML_FILES
	#define MAX_XML_FILES               (5)
#endif

#define XML_MAX_XML_FILES               (XML:MAX_XML_FILES)

#define NO_XML_FILE                     (XML:-1)

#define MAX_XML_FUNCTION                FUNCTION_LENGTH
#define MAX_XML_ENTRY_NAME              (32)
#define MAX_XML_ENTRY_TEXT              (80)

#define XML_BUFFER_SIZE                 (512)

#define MAX_XML_HANDLERS                (16)

#if !defined XML_WRITE_BUFFER_SIZE
	#define XML_WRITE_BUFFER_SIZE           (512)
#endif

#define XML_NO_WRITE (XMLEntry:cellmax)

enum E_XML_PARA
{
	E_XML_PARA_NAME[MAX_XML_ENTRY_NAME],
	E_XML_PARA_VALUE[MAX_XML_ENTRY_TEXT],
	E_XML_PARA_LEVEL
}

enum E_XML_HANDLER
{
	E_XML_HANDLER_TRIGGER[MAX_XML_ENTRY_NAME],
	E_XML_HANDLER_FUNCTION[MAX_XML_FUNCTION]
}

enum E_XML_WRITE
{
	E_XML_WRITE_TAG[MAX_XML_ENTRY_NAME],
	E_XML_WRITE_VALUE[MAX_XML_ENTRY_TEXT],
	E_XML_WRITE_CHILDREN,
	E_XML_WRITE_SIBLINGS
}

static stock
	YSI_g_sXMLWriteBuffer[XML_WRITE_BUFFER_SIZE][E_XML_WRITE],
	YSI_g_sXMLWritePointer,
	YSI_g_sParameters[XML_BUFFER_SIZE][E_XML_PARA],
	YSI_g_sHandlers[XML_MAX_XML_FILES][MAX_XML_HANDLERS][E_XML_HANDLER],
	YSI_g_sCurHandler[XML_MAX_XML_FILES] = {-1, ...},
	YSI_g_sCurBuffer = -1,
	YSI_g_sEndTag = 0;

/**--------------------------------------------------------------------------**\
<summary>XML_IsValid</summary>
<param name="XML:file">File to check validity of.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define XML_IsValid(%1) \
	((%1) >= XML:0 && (%1) < XML_MAX_XML_FILES && YSI_g_sCurHandler[(%1)] != -1)

/**--------------------------------------------------------------------------**\
<summary>XML_IsChar</summary>
<param name="char">Checks if a cell is a valid identifier character.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define XML_IsChar(%1) \
	(((%1) >= 'a' && (%1) <= 'z') || ((%1) >= 'A' && (%1) <= 'Z') || ((%1) >= '0' && (%1) <= '9') || (%1 == '_'))

/**--------------------------------------------------------------------------**\
<summary>XML_New</summary>
<returns>
	XML
</returns>
<remarks>
	Creates a new set of rules for parsing XML files.
</remarks>
\**--------------------------------------------------------------------------**/

stock XML:XML_New()
{
	P:3("XML:XML_New called");
	new
		XML:i;
	while (i < XML_MAX_XML_FILES && YSI_g_sCurHandler[i] != -1) i++;
	if (i == XML_MAX_XML_FILES) return NO_XML_FILE;
	YSI_g_sCurHandler[i] = 0;
	return i;
}

/**--------------------------------------------------------------------------**\
<summary>XML_Destroy</summary>
<param name="XML:rule">Removes a set of rules from the system</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

stock XML_Destroy(XML:rule)
{
	P:3("XML_Destroy called: %i", _:rule);
	if (!XML_IsValid(rule)) return 0;
	YSI_g_sCurBuffer = -1;
	YSI_g_sCurHandler[rule] = -1;
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>XML_Parse</summary>
<param name="XML:rule">Set of XML rules to parse against.</param>
<param name="filename[]">XML file to parse.</param>
<returns>
	-
</returns>
<remarks>
	Now supports self-closing tags and XML comments.
</remarks>
\**--------------------------------------------------------------------------**/

stock XML_Parse(XML:rule, filename[])
{
	P:3("XML_Parse called: %i, \"%s\"", _:rule, filename);
	if (!XML_IsValid(rule)) return 0;
	YSI_g_sCurBuffer = 0;
	new
		File:xFile = fopen(filename);
	if (xFile)
	{
		new
			line[YSI_MAX_STRING],
			tagCount,
			gotLastValue,
			inClose,
			inOpen,
			inComment,
			value[MAX_XML_ENTRY_TEXT],
			name[MAX_XML_ENTRY_NAME],
			inPar;
		while (fread(xFile, line))
		{
			P:5("XML_Parse() line: %s", line);
			new
				pos,
				ch;
			if (inComment)
			{
				pos = strfind(line, "-->", false, 0);
				if (pos == -1)
				{
					// Skip this whole line.
					continue;
				}
				else
				{
					pos += 3;
					inComment = 0;
				}
			}
			while ((ch = line[pos]) && ch <= ' ') pos++;
			while (ch)
			{
				if (ch <= ' ') pos++;
				else if (ch == '<')
				{
					pos++;
					if (line[pos] == '/')
					{
						pos++;
						tagCount--;
						if (gotLastValue)
						{
							XML_Push(XML_GetName(line, pos), value, tagCount);
						}
						else
						{
							name = XML_GetName(line, pos);
							value = XML_ParseTag(rule, name, tagCount);
							if (value[0] && tagCount > 1)
							{
								XML_Push(name, value, tagCount);
							}
						}
						inClose = 1;
					}
					else if (line[pos] == '!' && line[pos + 1] == '-' && line[pos + 2] == '-')
					{
						// XML comments.
						pos = strfind(line, "-->", false, pos + 3);
						if (pos == -1)
						{
							inComment = 1;
							break;
						}
						else
						{
							pos += 3;
						}
					}
					else
					{
						inOpen = 1;
						tagCount++;
						while ((ch = line[pos]) && XML_IsChar(ch)) pos++;
						//name = XML_GetName(line, pos);
					}
					gotLastValue = 0;
					inPar = 0;
				}
				else if (ch == '>')
				{
					inPar = inClose ? 0 : 1;
					inOpen = 0;
					inClose = 0;
					pos++;
				}
				else if (ch == '/')
				{
					// Self-closing tags (FINALLY)!
					pos++;
					if (inOpen)
					{
						tagCount--;
						inOpen = strfind(line, "<") + 1;
						if (inOpen)
						{
							name = XML_GetName(line, inOpen);
							value = XML_ParseTag(rule, name, tagCount);
							if (value[0] && tagCount > 1)
							{
								XML_Push(name, value, tagCount);
							}
							inOpen = 0;
						}
						inClose = 1; // Well, we sort of are...
					}
				}
				else if (inPar)
				{
					value = XML_GetValue(line, pos);
					gotLastValue = 1;
				}
				else if (inOpen)
				{
					name = XML_GetName(line, pos);
					value = XML_GetParameter(line, pos);
					XML_Push(name, value, tagCount);
				}
				else
				{
					pos++;
				}
				ch = line[pos];
			}
		}
		fclose(xFile);
		return 1;
	}
	return 0;
}

/**--------------------------------------------------------------------------**\
<summary>XML_Push</summary>
<param name="name[]">Identifer of data.</param>
<param name="text[]">Data.</param>
<param name="depth">Current XML tree depth.</param>
<returns>
	-
</returns>
<remarks>
	Pushes an identifier and it's value (either explicitaly stated or returned
	from another function) to the stack with basic parent info.
</remarks>
\**--------------------------------------------------------------------------**/

stock XML_Push(name[], text[], depth)
{
	P:3("XML_Push called: \"%s\", \"%s\", %i, %i", name, text, depth, YSI_g_sCurBuffer);
	if (YSI_g_sCurBuffer < XML_BUFFER_SIZE && YSI_g_sCurBuffer >= 0)
	{
		P:7("XML_Push: first");
		strcpy(YSI_g_sParameters[YSI_g_sCurBuffer][E_XML_PARA_NAME], name, MAX_XML_ENTRY_NAME);
		P:7("XML_Push: second");
		strcpy(YSI_g_sParameters[YSI_g_sCurBuffer][E_XML_PARA_VALUE], text, MAX_XML_ENTRY_TEXT);
		P:7("XML_Push: third");
		YSI_g_sParameters[YSI_g_sCurBuffer][E_XML_PARA_LEVEL] = depth;
		P:7("XML_Push: fourth");
		++YSI_g_sCurBuffer;
		P:7("XML_Push: fifth");
	}
	P:5("XML_Push: YSI_g_sCurBuffer = %d", YSI_g_sCurBuffer);
}

/**--------------------------------------------------------------------------**\
<summary>XML_GetParameter</summary>
<param name="line[]">Data to extract from.</param>
<param name="&pos">Start/end point of the text.</param>
<returns>
	-
</returns>
<remarks>
	Gets the data from inside ""s in an identifier.  Now supports
	\ for escape characters.
</remarks>
\**--------------------------------------------------------------------------**/

stock XML_GetParameter(line[], &pos)
{
	P:3("XML_GetParameter called: \"%s\", %i", line, pos);
	new
		ch,
		ret[MAX_XML_ENTRY_TEXT],
		i;
	while ((ch = line[pos++]) && ch != '"') {}
	if (ch)
	{
		while ((ch = line[pos++]) && i < (sizeof (ret) - 1))
		{
			if (ch == '\\')
			{
				switch (line[pos++])
				{
					case '"':
					{
						ch = '"';
					}
					case 'n':
					{
						ch = '\n';
					}
					case 'r':
					{
						ch = '\r';
					}
					case '\\': {}
					default:
					{
						pos--;
						continue;
					}
				}
			}
			else if (ch == '"')
			{
				break;
			}
			ret[i++] = ch;
		}
	}
	if (i == (sizeof (ret) - 1))
	{
		while ((ch = line[pos++]))
		{
			if (ch == '\\')
			{
				switch (line[pos++])
				{
					case '\\', '"', 'n', 'r': {}
					default:
					{
						pos--;
					}
				}
			}
			else if (ch == '"') break;
		}
	}
	ret[i] = '\0';
	return ret;
}

/**--------------------------------------------------------------------------**\
<summary>XML_GetValue</summary>
<param name="line[]">Line to get data from.</param>
<param name="&pos">Start and end position of the data.</param>
<returns>
	-
</returns>
<remarks>
	Gets the text between tags.
</remarks>
\**--------------------------------------------------------------------------**/

stock XML_GetValue(line[], &pos)
{
	P:3("XML_GetValue called: \"%s\", %i", line, pos);
	new
		ch,
		ret[MAX_XML_ENTRY_TEXT],
		i;
	while (((ch = line[pos++]) >= ' ' || ch == '\t') && (ch != '<') && i < (sizeof (ret) - 1)) ret[i++] = ch;
	pos--;
	if (i == (sizeof (ret) - 1))
	{
		while (((ch = line[pos]) >= ' ' || ch == '\t') && (ch != '<')) pos++;
	}
	ret[i] = '\0';
	return ret;
}

/**--------------------------------------------------------------------------**\
<summary>XML_GetName</summary>
<param name="line[]">Line to get data from.</param>
<param name="&pos">Start and end position of text.</param>
<returns>
	-
</returns>
<remarks>
	Gets the identifier of a piece of data.
</remarks>
\**--------------------------------------------------------------------------**/

stock XML_GetName(line[], &pos)
{
	P:3("XML_GetName called: \"%s\", %i", line, pos);
	new
		ch,
		ret[MAX_XML_ENTRY_NAME],
		i;
	while ((ch = line[pos++]) && XML_IsChar(ch) && i < (sizeof (ret) - 1)) ret[i++] = ch;
	pos--;
	if (i == (sizeof (ret) - 1))
	{
		while ((ch = line[pos]) >= ' ' && XML_IsChar(ch)) pos++;
	}
	ret[i] = '\0';
	return ret;
}

/**--------------------------------------------------------------------------**\
<summary>XML_ParseTag</summary>
<param name="XML:rule">Rule set to parse according to.</param>
<param name="name[]">Name if identifier.</param>
<param name="tagCount">New tree depth.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

stock XML_ParseTag(XML:rule, name[], tagCount)
{
	P:3("XML_ParseTag called: %i, \"%s\", %i", _:rule, name, tagCount);
	new
		i,
		j = YSI_g_sCurHandler[rule],
		ret[MAX_XML_ENTRY_TEXT] = "\1";
	YSI_g_sEndTag = tagCount;
	while (i < j)
	{
		if (!strcmp(YSI_g_sHandlers[rule][i][E_XML_HANDLER_TRIGGER], name, true))
		{
			break;
		}
		i++;
	}
	P:5("XML_ParseTag: Check %d != %d", i, j);
	if (i != j)
	{
		//format(ret, sizeof (ret), "%d", CallLocalFunction(YSI_g_sHandlers[rule][i][E_XML_HANDLER_FUNCTION], ""));
		valstr(ret, CallLocalFunction(YSI_g_sHandlers[rule][i][E_XML_HANDLER_FUNCTION], ""));
	}
	while (YSI_g_sCurBuffer-- && YSI_g_sParameters[YSI_g_sCurBuffer][E_XML_PARA_LEVEL] > tagCount)
	{
		P:3("XML_ParseTag item: %d %s %d", YSI_g_sCurBuffer, YSI_g_sParameters[YSI_g_sCurBuffer][E_XML_PARA_NAME], YSI_g_sParameters[YSI_g_sCurBuffer][E_XML_PARA_LEVEL]);
		//--YSI_g_sCurBuffer;
	}
	++YSI_g_sCurBuffer;
	/*while (YSI_g_sCurBuffer)
	{
		if (YSI_g_sParameters[--YSI_g_sCurBuffer][E_XML_PARA_LEVEL] <= tagCount)
		{
			++YSI_g_sCurBuffer;
			break;
		}
	}*/
	return ret;
}

/**--------------------------------------------------------------------------**\
<summary>XML_GetKeyValue</summary>
<param name="key[]">Variable to return identifier in.</param>
<param name="value[]">Variable to return value in.</param>
<returns>
	Data found.
</returns>
<remarks>
	Pops items off the stack for use in custom functions.
</remarks>
\**--------------------------------------------------------------------------**/

stock XML_GetKeyValue(key[], value[])
{
	P:3("XML_GetKeyValue called: \"%s\", \"%s\"", key, value);
	key[0] = 1;
	key[1] = 0;
	value[0] = 1;
	value[1] = 0;
	P:5("XML_GetKeyValue: YSI_g_sCurBuffer: %d", YSI_g_sCurBuffer);
	if (YSI_g_sCurBuffer)
	{
		--YSI_g_sCurBuffer;
		if (YSI_g_sParameters[YSI_g_sCurBuffer][E_XML_PARA_LEVEL] <= YSI_g_sEndTag)
		{
			++YSI_g_sCurBuffer;
			return 0;
		}
		P:5("XML_GetKeyValue: first");
		strcpy(key, YSI_g_sParameters[YSI_g_sCurBuffer][E_XML_PARA_NAME], MAX_XML_ENTRY_NAME);
		P:5("XML_GetKeyValue: second");
		strcpy(value, YSI_g_sParameters[YSI_g_sCurBuffer][E_XML_PARA_VALUE], MAX_XML_ENTRY_TEXT);
		P:3("XML_GetKeyValue ending: \"%s\", \"%s\"", key, value);
		return 1;
	}
	return 0;
}

/**--------------------------------------------------------------------------**\
<summary>XML_GetParentValue</summary>
<param name="key[]">Name of the parameter to get.</param>
<param name="value[]">Variable to return value in.</param>
<returns>
	Data found.
</returns>
<remarks>
	Does no poping, just searches for a value with the right name at the right
	depth so children can use the data if they HAVE to.
</remarks>
\**--------------------------------------------------------------------------**/

stock XML_GetParentValue(const key[], value[])
{
	P:3("XML_GetParentValue called: \"%s\"", key);
	value[0] = 1;
	value[1] = 0;
	P:7("XML_GetParentValue: first");
	//P:C(for (new i = 0; i != YSI_g_sCurBuffer; ++i) P:0("XML_GetParentValue: buffer[%d] = %s", i, YSI_g_sParameters[i][E_XML_PARA_NAME]););
	for (new i = 0; i != YSI_g_sCurBuffer; ++i)
	{
		P:7("XML_GetParentValue: second %d %d %d", i, YSI_g_sParameters[i][E_XML_PARA_LEVEL], YSI_g_sEndTag);
		if (YSI_g_sParameters[i][E_XML_PARA_LEVEL] == YSI_g_sEndTag)
		{
			P:7("XML_GetParentValue: 2b: %s %s", key, YSI_g_sParameters[i][E_XML_PARA_NAME]);
			if (!strcmp(key, YSI_g_sParameters[i][E_XML_PARA_NAME]))
			{
				P:7("XML_GetParentValue: third");
				strcpy(value, YSI_g_sParameters[i][E_XML_PARA_VALUE], MAX_XML_ENTRY_TEXT);
				return 1;
			}
		}
		else if (YSI_g_sParameters[i][E_XML_PARA_LEVEL] > YSI_g_sEndTag)
		{
			P:7("XML_GetParentValue: fourth");
			// In to child data.
			return 0;
		}
	}
	P:7("XML_GetParentValue: fifth");
	return 0;
}

/**--------------------------------------------------------------------------**\
<summary>XML_AddHandler</summary>
<param name="XML:ruls">Rule set to add data to.</param>
<param name="trigger[]">Identifier which calls it.</param>
<param name="function[]">Function to parse identifier in.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

stock XML_AddHandler(XML:rule, trigger[], function[])
{
	P:3("XML_AddHandler called: %i, \"%s\", \"%s\"", _:rule, trigger, function);
	new
		handle;
	if (!XML_IsValid(rule) || (handle = YSI_g_sCurHandler[rule]) >= MAX_XML_HANDLERS && handle >= 0) return 0;
	strcpy(YSI_g_sHandlers[rule][handle][E_XML_HANDLER_TRIGGER], trigger, MAX_XML_ENTRY_NAME);
	strcpy(YSI_g_sHandlers[rule][handle][E_XML_HANDLER_FUNCTION], function, MAX_XML_FUNCTION);
	YSI_g_sCurHandler[rule]++;
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>XML_RemoveHandler</summary>
<param name="XML:rule">Set to remove handler from.</param>
<param name="trigger[]">Handler name to remove.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

stock XML_RemoveHandler(XML:rule, trigger[])
{
	P:3("XML_RemoveHandler called: %i, \"%s\"", _:rule, trigger);
	if (XML_IsValid(rule))
	{
		for (new i = 0, j = YSI_g_sCurHandler[rule]; i < j; i++)
		{
			if (!strcmp(YSI_g_sHandlers[rule][i][E_XML_HANDLER_TRIGGER], trigger, true))
			{
				new
					last = --YSI_g_sCurHandler[rule];
				if (last)
				{
					strcpy(YSI_g_sHandlers[rule][i][E_XML_HANDLER_TRIGGER], YSI_g_sHandlers[rule][last][E_XML_HANDLER_TRIGGER], MAX_XML_ENTRY_NAME);
					strcpy(YSI_g_sHandlers[rule][i][E_XML_HANDLER_FUNCTION], YSI_g_sHandlers[rule][last][E_XML_HANDLER_FUNCTION], MAX_XML_FUNCTION);
				}
				return 1;
			}
		}
	}
	return 0;
}

/**--------------------------------------------------------------------------**\
<summary>XML_AddParameter</summary>
<param name="parent">Tag this is a parameter of.</param>
<param name="tag[]">Name of this data.</param>
<param name="value[]">Value of this data, if this is blank there is sub parameters.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

//#define XML_AddSubEntry XML_AddParameter
stock XMLEntry:XML_AddParameter(XMLEntry:parent, tag[], value[] = "")
{
	P:3("XMLEntry:XML_AddParameter called: %i, \"%s\", \"%s\"", _:parent, tag, value);
	if (_:parent < YSI_g_sXMLWritePointer < XML_WRITE_BUFFER_SIZE)
	{
		strcpy(YSI_g_sXMLWriteBuffer[YSI_g_sXMLWritePointer][E_XML_WRITE_TAG], tag, MAX_XML_ENTRY_NAME);
		strcpy(YSI_g_sXMLWriteBuffer[YSI_g_sXMLWritePointer][E_XML_WRITE_VALUE], value, MAX_XML_ENTRY_TEXT);
		YSI_g_sXMLWriteBuffer[YSI_g_sXMLWritePointer][E_XML_WRITE_CHILDREN] = -1;
		YSI_g_sXMLWriteBuffer[YSI_g_sXMLWritePointer][E_XML_WRITE_SIBLINGS] = YSI_g_sXMLWriteBuffer[_:parent][E_XML_WRITE_CHILDREN];
		YSI_g_sXMLWriteBuffer[_:parent][E_XML_WRITE_CHILDREN] = YSI_g_sXMLWritePointer;
		return XMLEntry:YSI_g_sXMLWritePointer++;
	}
	return XMLEntry:cellmax;
}

/**--------------------------------------------------------------------------**\
<summary>XML_AddItem</summary>
<param name="tag[]">Type of data being added.</param>
<param name="name[]">The optional name parameter for identifying tags.</param>
<returns>
	-
</returns>
<remarks>
	Starts the creation of a new tag to be written to a file, the structure
	has to be manually created then written.  There is no buffering of multiple
	tags before writing as a single tag can have quite a bit of data.
</remarks>
\**--------------------------------------------------------------------------**/

#define XML_CreateEntry XML_AddItem
#define XML_AddSubEntry XML_AddItem
stock XMLEntry:XML_AddItem(tag[], name[] = "", XMLEntry:parent = XMLEntry:cellmax)
{
	P:3("XMLEntry:XML_AddItem called: \"%s\", \"%s\", %i", tag, name, _:parent);
	if (_:parent != cellmax)
	{
		return XML_AddParameter(parent, tag, name);
	}
	if (YSI_g_sXMLWritePointer < XML_WRITE_BUFFER_SIZE)
	{
		strcpy(YSI_g_sXMLWriteBuffer[YSI_g_sXMLWritePointer][E_XML_WRITE_TAG], tag, MAX_XML_ENTRY_NAME);
		strcpy(YSI_g_sXMLWriteBuffer[YSI_g_sXMLWritePointer][E_XML_WRITE_VALUE], name, MAX_XML_ENTRY_TEXT);
		YSI_g_sXMLWriteBuffer[YSI_g_sXMLWritePointer][E_XML_WRITE_CHILDREN] = -1;
		YSI_g_sXMLWriteBuffer[YSI_g_sXMLWritePointer][E_XML_WRITE_SIBLINGS] = -1;
		return XMLEntry:YSI_g_sXMLWritePointer++;
	}
	return XMLEntry:cellmax;
}

/**--------------------------------------------------------------------------**\
<summary>XML_WriteItem</summary>
<param name="filename[]">File to write to.</param>
<param name="item">Handle to the tag to write.</param>
<param name="bool:bIncludeXML">Write the default <XML> tags or not?</param>
<param name="bool:bFavourShort">Write the shortest tags possible.</param>
<returns>
	-
</returns>
<remarks>
	Writea the data for a tag to a file.
</remarks>
\**--------------------------------------------------------------------------**/

#define XML_WriteEntry XML_WriteItem
stock XML_WriteItem(filename[], XMLEntry:item, bool:bIncludeXML = true, bool:bFavourShort = false)
{
	P:3("XML_WriteItem called: \"%s\", %i", filename, _:item);
	if (_:item < YSI_g_sXMLWritePointer)
	{
		new
			data;
		if (fexist(filename))
		{
			new
				File:fHnd = fopen(filename, io_read),
				File:__ftemp = ftemp();//fopen("_temp_ysi_user_file_.ysi", io_write);
			if (fHnd && __ftemp)
			{
				new
					str[YSI_MAX_STRING];
				while (fread(fHnd, str))
				{
					fwrite(__ftemp, str);
					if (!data)
					{
						new
							i,
							ch;
						while ((ch = str[i++]) && ch <= ' ') {}
						if (ch == '<')
						{
							if (bFavourShort) XML_WriteItemDataShort(_:item, __ftemp, 2);
							else XML_WriteItemData(_:item, __ftemp, 2);
							data = 1;
						}
					}
				}
				fclose(fHnd);
				//fclose(__ftemp);
				fremove(filename);
				if (data)
				{
					fHnd = fopen(filename, io_write);
					fseek(__ftemp);
					//__ftemp = fopen("_temp_ysi_user_file_.ysi", io_read);
					if (fHnd)// && __ftemp)
					{
						while (fread(__ftemp, str)) fwrite(fHnd, str);
						fclose(fHnd);
						fclose(__ftemp);
						//fremove("_temp_ysi_user_file_.ysi");
						YSI_g_sXMLWritePointer = _:item;
						return 1;
					}
				}
			}
			if (fHnd)
			{
				fclose(fHnd);
			}
			if (__ftemp)
			{
				fclose(__ftemp);
				//fremove("_temp_ysi_user_file_.ysi");
			}
		}
		if (!data)
		{
			new
				File:fHnd = fopen(filename, io_write);
			if (fHnd)
			{
				if (bIncludeXML) fwrite(fHnd, "<XML>\r\n");
				if (bFavourShort) XML_WriteItemDataShort(_:item, fHnd, _:bIncludeXML * 2);
				else XML_WriteItemData(_:item, fHnd, _:bIncludeXML * 2);
				if (bIncludeXML) fwrite(fHnd, "</XML>");
				fclose(fHnd);
				YSI_g_sXMLWritePointer = _:item;
				return 1;
			}
		}
	}
	return 0;
}

/**--------------------------------------------------------------------------**\
<summary>XML_WriteItemData</summary>
<param name="item">Item to write data for.</param>
<param name="File:fHnd">File to write to.</param>
<param name="depth">Current indentation.</param>
<returns>
	-
</returns>
<remarks>
	Recursive function to write a tag and it's children to a file.
</remarks>
\**--------------------------------------------------------------------------**/

static stock XML_WriteItemData(item, File:fHnd, depth)
{
	P:4("XML_WriteItemData called: %i, %i, %i", item, _:fHnd, depth);
	new
		str[YSI_MAX_STRING],
		i = YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_CHILDREN];
	if (i == -1)
	{
		format(str, sizeof (str), "%*s<%s>%s</%s>\n", depth, "", YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_TAG], YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_VALUE], YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_TAG]);
		fwrite(fHnd, str);
		P:7("XML_WriteItemData: writing %s", str);
	}
	else
	{
		if (YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_VALUE][0]) format(str, sizeof (str), "%*s<%s name=\"%s\">\n", depth, "", YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_TAG], YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_VALUE]);
		else format(str, sizeof (str), "%*s<%s>\n", depth, "", YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_TAG]);
		P:7("XML_WriteItemData: writing %s", str);
		fwrite(fHnd, str);
		depth += 2;
		while (i != -1)
		{
			XML_WriteItemData(i, fHnd, depth);
			i = YSI_g_sXMLWriteBuffer[i][E_XML_WRITE_SIBLINGS];
		}
		depth -= 2;
		format(str, sizeof (str), "%*s</%s>\n", depth, "", YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_TAG]);
		P:7("XML_WriteItemData: writing %s", str);
		fwrite(fHnd, str);
	}
}

/**--------------------------------------------------------------------------**\
<summary>XML_WriteItemDataShort</summary>
<param name="item">Item to write data for.</param>
<param name="File:fHnd">File to write to.</param>
<param name="depth">Current indentation.</param>
<returns>
	-
</returns>
<remarks>
	Recursive function to write a tag and it's children to a file.  Writes tags
	in the shortest manner possible.  This does make it slower however (not much
	though given the use of linked lists).
</remarks>
\**--------------------------------------------------------------------------**/

static stock XML_WriteItemDataShort(item, File:fHnd, depth)
{
	P:4("XML_WriteItemDataShort called: %i, %i, %i", item, _:fHnd, depth);
	new
		str[YSI_MAX_STRING],
		i = YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_CHILDREN];
	if (i == -1)
	{
		format(str, sizeof (str), "%*s<%s>%s</%s>\n", depth, "", YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_TAG], YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_VALUE], YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_TAG]);
		fwrite(fHnd, str);
		P:7("XML_WriteItemDataShort: writing 0 %s", str);
	}
	else
	{
		// Loop through all children to find those with no children.
		format(str, sizeof (str), "%*s<%s", depth, "", YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_TAG]);
		P:7("XML_WriteItemDataShort: writing 1 %s", str);
		fwrite(fHnd, str);
		new
			notDone = 0;
		do
		{
			if (YSI_g_sXMLWriteBuffer[i][E_XML_WRITE_CHILDREN] == -1)
			{
				format(str, sizeof (str), " %s=\"%s\"", YSI_g_sXMLWriteBuffer[i][E_XML_WRITE_TAG], YSI_g_sXMLWriteBuffer[i][E_XML_WRITE_VALUE]);
				P:7("XML_WriteItemDataShort: writing 2 %s", str);
				fwrite(fHnd, str);
			}
			else
			{
				++notDone;
			}
			i = YSI_g_sXMLWriteBuffer[i][E_XML_WRITE_SIBLINGS];
		}
		while (i != -1);
		if (notDone)
		{
			P:7("XML_WriteItemDataShort: writing 3 >\n");
			fwrite(fHnd, ">\n");
			depth += 2;
			i = YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_CHILDREN];
			do
			{
				if (YSI_g_sXMLWriteBuffer[i][E_XML_WRITE_CHILDREN] != -1)
				{
					XML_WriteItemDataShort(i, fHnd, depth);
				}
				i = YSI_g_sXMLWriteBuffer[i][E_XML_WRITE_SIBLINGS];
			}
			while (i != -1);
			depth -= 2;
			format(str, sizeof (str), "%*s</%s>\n", depth, "", YSI_g_sXMLWriteBuffer[item][E_XML_WRITE_TAG]);
			fwrite(fHnd, str);
			P:7("XML_WriteItemDataShort: writing 4 %s", str);
		}
		else
		{
			P:7("XML_WriteItemData: writing 5 />\n");
			fwrite(fHnd, " />\n");
		}
	}
}

/**--------------------------------------------------------------------------**\
<summary>XML_RemoveItem</summary>
<param name="file[]">File to remove the tag from.</param>
<param name="tag[]">Type of tag to remove.</param>
<param name="name[]">Name of the tag to remove.</param>
<returns>
	-
</returns>
<remarks>
	Does a replace on data in a file with no new data.
</remarks>
\**--------------------------------------------------------------------------**/

stock XML_RemoveItem(file[], tag[], name[])
{
	P:3("XML_RemoveItem called: \"%s\", \"%s\", \"%s\", ", file, tag, name);
	return XML_ReplaceItem(file, tag, name, -1);
}

/**--------------------------------------------------------------------------**\
<summary>XML_ReplaceItem</summary>
<param name="file[]">File to replace an item in.</param>
<param name="tag[]">Tag type of data to replace.</param>
<param name="name[]">Name of data to replace.</param>
<param name="replacement">Handle to the replacement data.</param>
<returns>
	-
</returns>
<remarks>
	Replaces a tag's data with new data, basically changes a tag's value.
</remarks>
\**--------------------------------------------------------------------------**/

stock XML_ReplaceItem(file[], tag[], name[], replacement)
{
	P:3("XML_ReplaceItem called: \"%s\", \"%s\", \"%s\", %i", file, tag, name, replacement);
	if (fexist(file))
	{
		new
			File:fHnd = fopen(file, io_read),
			File:__ftemp = ftemp();//fopen("_temp_ysi_user_file_.ysi", io_write);
		if (fHnd && __ftemp)
		{
			new
				tagCount,
				line[YSI_MAX_STRING],
				inTag,
				atStart;
			while (fread(fHnd, line))
			{
				new
					pos,
					ch;
				while ((ch = line[pos]) && ch <= ' ') pos++;
				while (ch)
				{
					if (ch <= ' ') pos++;
					else if (ch == '<')
					{
						if (line[++pos] == '/')
						{
							pos++;
							tagCount--;
							if (inTag && tagCount <= atStart) inTag = 3;
						}
						else
						{
							tagCount++;
							if (!inTag)
							{
								if (!strcmp(XML_GetName(line, pos), tag)) inTag = 1;
							}
							else while ((ch = line[pos]) && XML_IsChar(ch)) pos++;
						}
					}
					else if (ch == '>')
					{
						if (inTag == 1) inTag = 0;
						pos++;
					}
					else if (inTag == 1)
					{
						if (!strcmp(XML_GetName(line, pos), "name"))
						{
							if (!(strcmp(XML_GetParameter(line, pos), name)))
							{
								inTag = 2;
								atStart = tagCount - 1;
								if (replacement != -1)
								{
									if (replacement >= YSI_g_sXMLWritePointer) replacement = -1;
									else XML_WriteItemData(replacement, __ftemp, (tagCount - 1) * 2);
								}
							}
						}
						else XML_GetParameter(line, pos);
					}
					else pos++;
					ch = line[pos];
				}
				if (!inTag) fwrite(__ftemp, line);
				if (inTag == 3) inTag = 0;
			}
			fclose(fHnd);
			//fclose(__ftemp);
			fremove(file);
			fHnd = fopen(file, io_write);
			//__ftemp = fopen("_temp_ysi_user_file_.ysi", io_read);
			fseek(__ftemp);
			if (fHnd && __ftemp)
			{
				while (fread(__ftemp, line)) fwrite(fHnd, line);
				fclose(fHnd);
				fclose(__ftemp);
				//fremove("_temp_ysi_user_file_.ysi");
				if (replacement != -1) YSI_g_sXMLWritePointer = replacement;
				return 1;
			}
		}
		if (fHnd)
		{
			fclose(fHnd);
		}
		if (__ftemp)
		{
			fclose(__ftemp);
			//fremove("_temp_ysi_user_file_.ysi");
		}
		return 0;
	}
	return 1;
}
