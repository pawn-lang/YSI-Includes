/**--------------------------------------------------------------------------**\
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
	1.5
Changelog:
	07/01/13:
		Rewrote almost everything!
		Split in to multiple files.
		Added sections.
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
\**--------------------------------------------------------------------------**/

#if defined _INC_y_ini
	#endinput
#endif
#define _INC_y_ini

#define MAX_INI_LINE                    (MAX_INI_ENTRY_NAME + MAX_INI_ENTRY_TEXT + 32)

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
	#define MAX_INI_ENTRY_TEXT          YSI_MAX_INLINE_STRING
#endif

#if !defined INI_MAX_WRITES
	#define INI_MAX_WRITES              (4)
#endif

#if !defined INI_BUFFER_SIZE
	#define INI_BUFFER_SIZE             (128)
#endif

#if !defined MAX_INI_TAGS
	#define MAX_INI_TAGS                (8)
#endif

#define MAX_INI_STRING                  FUNCTION_LENGTH

#define Y_INI_WRITE_ARRAY_SIZE ((MAX_INI_ENTRY_TEXT - 1) / 16 * 16)

stock const
	INI_NO_TAG[] = "\1"; // NULL

#define INI_NO_FILE (INI:-1)

#include "..\amx\os"
#include "..\YSI_Internal\y_version"

#include "..\YSI_Core\y_utils"
#include "..\YSI_Coding\y_malloc"
#include "..\YSI_Coding\y_inline"
#include "..\YSI_Coding\y_stringhash"

#if defined YSI_TESTS
	#define _Y_INI_STATIC
#else
	#define _Y_INI_STATIC static
#endif

#if defined YSI_TESTS && defined YSI_MOCK_READER
	#include "..\YSI_Internal\y_mock"
#endif

#include "..\YSI_Coding\y_hooks"

forward e_INI_LINE_TYPE:
	INI_IdentifyLineType(const str[], &p0s, &p0e, &p1s, &p1e, &p2s, &p2e);

#include "y_ini/reading"
#include "y_ini/writing"

#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_ini/tests"
#endif

