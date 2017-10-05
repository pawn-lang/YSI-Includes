#if defined _inc_y_text
	#undef _inc_y_text
#endif

// Multiple includes!
#include "..\YSI_Internal\y_unique"

// Need an include guard here.
#if defined _INC_y_text
	#endinput
#endif
#define _INC_y_text

/**
 * <library name="y_text">
 * <section>
 *  Description
 * </section>
 *  Provides interfaces for displaying text from anywhere by way of native like
 *  functions using text indexes rather than text.  Due to a compile problem a
 *  number of the stock functions should be static but can't be.
 * <section>
 *  Version
 * </section>
 *  0.1.1
 * <section>
 *  Functions
 * </section>
 * <subsection>
 * Public
 * </subsection><ul>
 *  <symbol name="Text_ResetAll">Resets the entire text system.</symbol>
 *  <symbol name="Text_NewLanguage">Sets up to parse a new language.</symbol>
 *  <symbol name="Text_Parse">Sorts loaded text into a binary tree.</symbol>
 *  <symbol name="Text_DataSave_data">Saves text appearence data.</symbol>
 *  <symbol name="Text_DataSave_colours">Saves file colour defines.</symbol>
 *  <symbol name="Text_DataSave_colors">Wrapper for above function.</symbol>
 * </ul><subsection>
 * Stock
 * </subsection><ul>
 *  <symbol name="Text_FindTextPointers">Should be static but can't be :(.</symbol>
 *  <symbol name="Text_AddToBuffer">Saves all passed text for processing.</symbol>
 *  <symbol name="Text_GetTextFromIndex">Gets text from an array pointer and language.</symbol>
 *  <symbol name="Text_GetErrorMessage">Gets an unfound message.</symbol>
 *  <symbol name="Text_GetTextStyle">Gets text's style.</symbol>
 *  <symbol name="Text_GetTextColour">Gets text's colour.</symbol>
 *  <symbol name="Text_GetTextTime">Gets text's time.</symbol>
 *  <symbol name="Text_Send">Sends a message to a player.</symbol>
 *  <symbol name="Text_SendToAll">Sends a message to all players.</symbol>
 *  <symbol name="Text_SendToGroup">Sends a message to a defined group.</symbol>
 *  <symbol name="Text_SendToPlayers">Sends a message to a passed group.</symbol>
 *  <symbol name="Text_Display">Display an actual string to a player in a given style.</symbol>
 * </ul><subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="Text_AddText">Adds text to the tree after sorting.</symbol>
 * </ul><subsection>
 * Inline
 * </subsection><ul>
 *  <symbol name="Text_Text">Constructor - Calls Text_ResetAll.</symbol>
 *  <symbol name="Text_SetLangPointer">Sets the pointer for a language to a position.</symbol>
 *  <symbol name="Text_ResetLangPointers">Resets all the pointers for one language.</symbol>
 *  <symbol name="Text_GetPlayerLanguage">Gets a players language.</symbol>
 *  <symbol name="Text_GetText">Gets text from an identifier and language.</symbol>
 *  <symbol name="Text_GetPlayerText">Gets text from an identifier and playerid.</symbol>
 *  <symbol name="Text_SendFormat">Sends a formatted message to a player.</symbol>
 *  <symbol name="Text_SendToAllFormat">Sends a formatted message to all players.</symbol>
 *  <symbol name="Text_SendToGroupFormat">Sends a formatted message to a defined group.</symbol>
 *  <symbol name="Text_SendToPlayersFormat">Sends a formatted message to a passed group.</symbol>
 * </ul><section>
 *  Definitions
 * </section><ul>
 *  <symbol name="MAX_TEXT_NAME">Maximum length of a text identifier.</symbol>
 *  <symbol name="MAX_TEXT_ENTRY">Maximum length of a text string.</symbol>
 *  <symbol name="TEXT_NO_TEXT">Value for no text for that language.</symbol>
 *  <symbol name="TEXT_NO_POINTERS">Value for no text found.</symbol>
 *  <symbol name="TEXT_TYPE_CLIENT">Flag for sending a client formatted message (unused).</symbol>
 *  <symbol name="TEXT_TYPE_GAME">Flag for sending a game text formatted message (unused).</symbol>
 *  <symbol name="MAX_TEXT_COLOURS">Max number of defined colours in an ini file.</symbol>
 * </ul><section>
 *  Enums
 * </section><ul>
 *  <symbol name="E_TEXT_POINTERS">Structure of the language pointer array.</symbol>
 * </ul><section>
 *  Macros
 * </section><ul>
 *  <symbol name="Text_RegisterTag">Placed as a function, calls Text_AddToBuffer for tags.</symbol>
 * </ul><section>
 *  Variables
 * </section>
 * <subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="YSI_g_sTextTable">Array of all text entries.</symbol>
 *  <symbol name="YSI_g_sNameTable">Array of all text names and language pointers.</symbol>
 *  <symbol name="YSI_g_sSearchTree">Binary tree of text hashes.</symbol>
 *  <symbol name="YSI_g_sTextInited">Flag for text binary sorted.</symbol>
 *  <symbol name="YSI_g_sBufferIndex">Index of next text slot for the current language.</symbol>
 *  <symbol name="YSI_g_sTextCount">Count of largest number of texts in one language.</symbol>
 *  <symbol name="YSI_g_sBufferLang">Current language being loaded.</symbol>
 *  <symbol name="YSI_g_sLangBuffer">Saves the current position of each language.</symbol>
 *  <symbol name="YSI_g_sColours">Saves defined colours for use.</symbol>
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

#include <a_samp>

#include "..\YSI_Internal\y_version"

// Make sure this is included early.
#include "..\YSI_Data\y_playerset"

// Apparently I'd already written the internal code to support this and forgot!
#define Y_TEXT_UNIQUE

#if !defined Y_TEXT_MAX_SETS
	#define Y_TEXT_MAX_SETS             (16)
#endif

#if !defined Y_TEXT_PER_SET
	#define Y_TEXT_PER_SET              (64)
#endif

#if !defined MAX_TEXT_ENTRIES
	#define MAX_TEXT_ENTRIES (Y_TEXT_PER_SET * Y_TEXT_MAX_SETS)
#endif

#include "..\YSI_Internal\y_version"

#include "..\YSI_Storage\y_xml"
#include "..\YSI_Server\y_td"
#include "..\YSI_Server\y_colours"

//#include "..\y_hooks"

#include "..\YSI_Internal\y_natives"

#include "y_text/styles"

// This is a horribly eclectic collection of libraries from all over the place
// and written at different times with different aims - frankly I'll be AMAZED
// if it all comes together and works.


#include <a_samp>
#include "..\YSI_Core\y_debug"
#include "..\YSI_Server\y_colours"

#include "y_text/load"

#include "..\YSI_Core\y_utils"
#include "..\YSI_Internal\y_shortfunc"
#include "..\YSI_Internal\y_natives"
#include "..\YSI_Coding\y_va"

#include "y_text/render"

#include "..\YSI_Storage\y_amx"
#include "..\YSI_Storage\y_ini"
#include "..\YSI_Data\y_iterate"
#include "..\YSI_Server\y_scriptinit"
#include "..\YSI_Players\y_languages"
#include "..\YSI_Visual\y_dialog"
#include "..\YSI_Coding\y_inline"
#include "..\YSI_Coding\y_hooks"

#include "y_text/impl"

#define UNDO_MOVE|||
#define DO_MOVE|||%0``` %0DO_MOVE|||

#define Text_Send(%0,%1) PSF:_Text_Send(%0,DO_TEXT_SET:%1 UNDO_MOVE|||)
#define Text_Render(%0,%1) _Text_Render(%0,DO_TEXT_SET:%1 UNDO_MOVE|||)
#define Text_Format(%0,%1,%2,%3,%4) _Text_Format(%0,%1,%2,%3,DO_TEXT_SET:%4 UNDO_MOVE|||)

#define Text_Format_GT_0(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_GT_0,%3)
#define Text_Format_GT_1(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_GT_1,%3)
#define Text_Format_GT_2(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_GT_2,%3)
#define Text_Format_GT_3(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_GT_3,%3)
#define Text_Format_GT_4(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_GT_4,%3)
#define Text_Format_GT_5(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_GT_5,%3)
#define Text_Format_GT_6(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_GT_6,%3)
#define Text_Format_TD(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_TD,%3)
#define Text_Format_3D(%0,%1,%2,%3 Text_Format(%0,%1,%2, e_STYLE_TYPE_3D,%3)
#define Text_Format_Client(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_CLIENT,%3)
#define Text_Format_Player(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_PLAYER,%3)
#define Text_Format_Other(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_OTHER,%3)
#define Text_Format_Dialog(%0,%1,%2,%3) Text_Format(%0,%1,%2, e_STYLE_TYPE_DIALOG,%3)

//#define _Text_Send(%0YCMD:%1) _Text_Send(%0_:YCMD_REP_0:YCMD_REP_1:%1)

//#define YCMD_REP_0:YCMD_REP_1:%0, Command_GetID(%0),
//#define YCMD_REP_1:%0) Command_GetID(%0))

// This code allows "DEFAULT_TEXT_SET" to propogate through the text one section
// at a time without detecting later matches too early.  The design of "DO_MOVE"
// and "UNDO_MOVE" means that the compiler will correctly detect the end of the
// code, regardless of the length, and end.
#define Text_MessageBox(%0,%1,%2,%3,%4,%5) PSF:_Text_DialogBox(%0,DIALOG_STYLE_MSGBOX,%1,DO_TEXT_SET:%2 DO_MOVE|||,DO_TEXT_SET:%3 ```,DO_TEXT_SET:%4 ```,DO_TEXT_SET:%5 UN```)
#define Text_InputBox(%0,%1,%2,%3,%4,%5) PSF:_Text_DialogBox(%0,DIALOG_STYLE_INPUT,%1,DO_TEXT_SET:%2 DO_MOVE|||,DO_TEXT_SET:%3 ```,DO_TEXT_SET:%4 ```,DO_TEXT_SET:%5 UN```)
#define Text_ListBox(%0,%1,%2,%3,%4,%5) PSF:_Text_DialogBox(%0,DIALOG_STYLE_LIST,%1,DO_TEXT_SET:%2 DO_MOVE|||,DO_TEXT_SET:%3 ```,DO_TEXT_SET:%4 ```,DO_TEXT_SET:%5 UN```)
#define Text_PasswordBox(%0,%1,%2,%3,%4,%5) PSF:_Text_DialogBox(%0,DIALOG_STYLE_PASSWORD,%1,DO_TEXT_SET:%2 DO_MOVE|||,DO_TEXT_SET:%3 ```,DO_TEXT_SET:%4 ```,DO_TEXT_SET:%5 UN```)
#define Text_DialogBox(%0,%9,%1,%2,%3,%4,%5) PSF:_Text_DialogBox(%0,%9,%1,DO_TEXT_SET:%2 DO_MOVE|||,DO_TEXT_SET:%3 ```,DO_TEXT_SET:%4 ```,DO_TEXT_SET:%5 UN```)
//#define Text_MessageBox(%0,%1,%2,%3) PSF:_Text_MessageBox(%0,%1,DEFAULT_TEXT_SET,#%2 DO_MOVE|||,DEFAULT_TEXT_SET,#%3 $$$,DEFAULT_TEXT_SET,#%4 $$$,DEFAULT_TEXT_SET,#%5 UN$$$)

//#define _Text_MessageBox(%0YCMD:%1) _Text_MessageBox(%0_:YCMD_REP_0:YCMD_REP_1:%1)

//stock Text_GetAllIDs(

stock formatex(output[], len, const format[], GLOBAL_TAG_TYPES:...)
{
	static
		sFormat[1024],
		sTemp[1024];
	// "Format_Standardise" modifies "input" repeatedly.
	//strcpy(sTemp, format);
	strcpy(sFormat, format);
	Format_Standardise(sFormat, sTemp);
	new
		n = (numargs() - 3) * 4;
	if (n)
	{
		// Push all passed parameters.
		new
			arg_start,
			arg_end;
		// Load the real address of the last static parameter.  Do this by
		// loading the address of the parameter and then adding the value of
		// [FRM] (frame pointer).
		#emit CONST.alt                 format
		#emit LCTRL                     5
		#emit ADD
		#emit STOR.S.pri                arg_start
		// Load the address of the last variable parameter.  Do this by adding
		// the number of variables on the value just loaded.
		#emit LOAD.S.alt                n
		#emit ADD
		#emit STOR.S.pri                arg_end
		new
			arg_cur = arg_end;
		do
		{
			#emit LOAD.S.pri            arg_cur
			#emit LOAD.I
			#emit PUSH.pri
			arg_cur -= 4;
		}
		while (arg_cur > arg_start);
		Format_Render(INVALID_PLAYER_ID, NO_LANGUAGE, output, len - 1, 0, e_FORMAT_FLAGS_NONE, sTemp, n / 4);
		#emit LCTRL                     4
		#emit LOAD.S.alt                n
		#emit ADD
		#emit SCTRL                     4
	}
	else
	{
		Format_Render(INVALID_PLAYER_ID, NO_LANGUAGE, output, len - 1, 0, e_FORMAT_FLAGS_NONE, sTemp, 0);
	}
}

stock printfex(const format[], GLOBAL_TAG_TYPES:...)
{
	static
		sFormat[1024],
		sTemp[1024];
	// "Format_Standardise" modifies "input" repeatedly.
	strcpy(sFormat, format);
	Format_Standardise(sFormat, sTemp);
	new
		n = (numargs() - 1) * 4;
	if (n)
	{
		// Push all passed parameters.
		new
			arg_start,
			arg_end;
		// Load the real address of the last static parameter.  Do this by
		// loading the address of the parameter and then adding the value of
		// [FRM] (frame pointer).
		#emit CONST.alt                 format
		#emit LCTRL                     5
		#emit ADD
		#emit STOR.S.pri                arg_start
		// Load the address of the last variable parameter.  Do this by adding
		// the number of variables on the value just loaded.
		#emit LOAD.S.alt                n
		#emit ADD
		#emit STOR.S.pri                arg_end
		new
			arg_cur = arg_end;
		do
		{
			#emit LOAD.S.pri            arg_cur
			#emit LOAD.I
			#emit PUSH.pri
			arg_cur -= 4;
		}
		while (arg_cur > arg_start);
		Format_Render(INVALID_PLAYER_ID, NO_LANGUAGE, sFormat, sizeof (sFormat) - 1, 0, e_FORMAT_FLAGS_NONE, sTemp, n / 4);
		#emit LCTRL                     4
		#emit LOAD.S.alt                n
		#emit ADD
		#emit SCTRL                     4
	}
	else
	{
		Format_Render(INVALID_PLAYER_ID, NO_LANGUAGE, sFormat, sizeof (sFormat) - 1, 0, e_FORMAT_FLAGS_NONE, sTemp, 0);
	}
	print(sFormat);
}

