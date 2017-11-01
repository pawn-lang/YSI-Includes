#if defined _INC_y_ini
	#endinput
#endif
#define _INC_y_ini

/**
 * <library name="y_ini">
 * <section>
 *  Description
 * </section>
 *  Reads the INI and also exports a number of functions to other "classes" for
 *  easy reading of data files there.
 * <section>
 *  Version
 * </section>
 *  1.5
 * <section>
 *  Functions
 * </section>
 * <subsection>
 * Stock
 * </subsection><ul>
 *  <symbol name="INI_Load">Loads an INI file using standard features.</symbol>
 *  <symbol name="INI_ParseFile">Loads a file as an ini and distributes data.</symbol>
 *  <symbol name="INI_GetEntryName">Gets the name of an INI item.</symbol>
 *  <symbol name="INI_GetEntryText">Gets the value of an INI item.</symbol>
 *  <symbol name="INI_Open">Opens an INI for writing.</symbol>
 *  <symbol name="INI_Close">Closes an INI being written to.</symbol>
 *  <symbol name="INI_SetTag">Sets a subheading in an INI fo subsequent writes.</symbol>
 *  <symbol name="INI_WriteString">Writes a string to an INI.</symbol>
 *  <symbol name="INI_WriteInt">Writes an int to an INI.</symbol>
 *  <symbol name="INI_WriteFloat">Writes a float to an INI.</symbol>
 *  <symbol name="INI_WriteHex">Writes a hex to an INI.</symbol>
 *  <symbol name="INI_WriteBin">Writes a binary to an INI.</symbol>
 *  <symbol name="INI_WriteBool">Writes a boolean to an INI.</symbol>
 *  <symbol name="INI_RemoveEntry">Remove an entry from a file.</symbol>
 * </ul><subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="INI_WriteBuffer">Writes an INI's buffer to the file.</symbol>
 *  <symbol name="INI_AddToBuffer">Adds a string to an INI buffer.</symbol>
 * </ul><subsection>
 * Inline
 * </subsection><ul>
 *  <symbol name="INI_Int">Parse an integer INI entry.</symbol>
 *  <symbol name="INI_Float">Parse a float INI entry.</symbol>
 *  <symbol name="INI_Hex">Parse a hex INI entry.</symbol>
 *  <symbol name="INI_Bin">Parse a binary INI entry.</symbol>
 *  <symbol name="INI_Bool">Parse a binary INI entry.</symbol>
 *  <symbol name="INI_String">Parse a string INI entry.</symbol>
 * </ul><section>
 *  Definitions
 * </section><ul>
 *  <symbol name="MAX_INI_TAG">Maximum length of an INI tagname.</symbol>
 *  <symbol name="MAX_INI_ENTRY_NAME">Maximum length of an INI entry name.</symbol>
 *  <symbol name="MAX_INI_ENTRY_TEXT">Maximum length of an INI's entries' value.</symbol>
 *  <symbol name="MAX_INI_LINE">Maximum length of a line in a file.</symbol>
 *  <symbol name="INI_NEW_LINE">String for new lines.</symbol>
 *  <symbol name="INI_MAX_WRITES">Maximum concurrent files open for writing.</symbol>
 *  <symbol name="MAX_INI_TAGS">Number of tags the buffer can hold data for at once.</symbol>
 * </ul><section>
 *  Enums
 * </section><ul>
 *  <symbol name="E_INI_WRITE">Storage for entries to be written.</symbol>
 *  <symbol name="E_INI_TAGS">Data for tags with data.</symbol>
 * </ul><section>
 *  Macros
 * </section><ul>
 *  <symbol name="INI_Parse">Header for ini parsing functions.</symbol>
 * </ul><section>
 *  Tags
 * </section><ul>
 *  <symbol name="INI">Handle to an INI file being written to.</symbol>
 * </ul><section>
 *  Variables
 * </section>
 * <subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="YSI_g_sINIWriteBuffer">Basic data to be written.</symbol>
 *  <symbol name="YSI_g_sINIWritePos">Next slot to write to.</symbol>
 *  <symbol name="YSI_g_sINITagPos">Next slot to add a tag to.</symbol>
 *  <symbol name="YSI_g_sINICurrentTag">Pointer to the tag been writen to.</symbol>
 *  <symbol name="YSI_g_sINIWriteTag">Data for tags,</symbol>
 *  <symbol name="YSI_g_sINIWriteFile">Current files been written to.</symbol>
 * </ul>
 * </library>
 *//** *//*
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

#include "..\YSI_Internal\y_compilerdata"

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

#include "..\YSI_Internal\y_thirdpartyinclude"
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

