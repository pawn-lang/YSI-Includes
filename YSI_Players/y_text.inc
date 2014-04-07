/**--------------------------------------------------------------------------**\
					=====================================
					Y Sever Includes - Language Text Core
					=====================================
Description:
	Provides interfaces for displaying text from anywhere by way of native like
	functions using text indexes rather than text.  Due to a compile problem a
	number of the stock functions should be static but can't be.
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
	
	The Original Code is the YSI text include.
	
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
	0.1.1
Changelog:
	17/02/07:
		Added saving of style parameter for text draws.
	27/12/07:
		Added text_draw support.
	24/06/07:
		Modified a few functions to use Bit_GetBit for speed.
	19/06/07:
		Added default language for alt language with no text.
		Added console errors.
		Added support for blank INI strings to ignore the text.
		Increased speed of non format sends by saving each language
	14/06/07:
		Added type and data loading for strings.
		Altered display functions to use files defined styles.
	13/06/07:
		Removed unfound text ignorance in group send functions.
		Added improved error handling to support custom messges.
	02/05/07:
		Added YSI_ prefix to all globals.
	23/03/07:
		First version.
Functions:
	Public:
		Text_ResetAll - Resets the entire text system.
		Text_NewLanguage - Sets up to parse a new language.
		Text_Parse - Sorts loaded text into a binary tree.
		Text_DataSave_data - Saves text appearence data.
		Text_DataSave_colours - Saves file colour defines.
		Text_DataSave_colors - Wrapper for above function.
	Core:
		-
	Stock:
		Text_FindTextPointers - Should be static but can't be :(.
		Text_AddToBuffer - Saves all passed text for processing.
		Text_GetTextFromIndex - Gets text from an array pointer and language.
		Text_GetErrorMessage - Gets an unfound message.
		Text_GetTextStyle - Gets text's style.
		Text_GetTextColour - Gets text's colour.
		Text_GetTextTime - Gets text's time.
		Text_Send - Sends a message to a player.
		Text_SendToAll - Sends a message to all players.
		Text_SendToGroup - Sends a message to a defined group.
		Text_SendToPlayers - Sends a message to a passed group.
		Text_Display - Display an actual string to a player in a given style.
	Static:
		Text_AddText - Adds text to the tree after sorting.
	Inline:
		Text_Text - Constructor - Calls Text_ResetAll.
		Text_SetLangPointer - Sets the pointer for a language to a position.
		Text_ResetLangPointers - Resets all the pointers for one language.
		Text_GetPlayerLanguage - Gets a players language.
		Text_GetText - Gets text from an identifier and language.
		Text_GetPlayerText - Gets text from an identifier and playerid.
		Text_SendFormat - Sends a formatted message to a player.
		Text_SendToAllFormat - Sends a formatted message to all players.
		Text_SendToGroupFormat - Sends a formatted message to a defined group.
		Text_SendToPlayersFormat - Sends a formatted message to a passed group.
	API:
		-
Callbacks:
	-
Definitions:
	MAX_TEXT_NAME - Maximum length of a text identifier.
	MAX_TEXT_ENTRY - Maximum length of a text string.
	TEXT_NO_TEXT - Value for no text for that language.
	TEXT_NO_POINTERS - Value for no text found.
	TEXT_TYPE_CLIENT - Flag for sending a client formatted message (unused).
	TEXT_TYPE_GAME - Flag for sending a game text formatted message (unused).
	MAX_TEXT_COLOURS - Max number of defined colours in an ini file.
Enums:
	E_TEXT_POINTERS - Structure of the language pointer array.
Macros:
	Text_RegisterTag - Placed as a function, calls Text_AddToBuffer for tags.
Tags:
	-
Variables:
	Global:
		-
	Static:
		YSI_g_sTextTable - Array of all text entries.
		YSI_g_sNameTable - Array of all text names and language pointers.
		YSI_g_sSearchTree - Binary tree of text hashes.
		YSI_g_sTextInited - Flag for text binary sorted.
		YSI_g_sBufferIndex - Index of next text slot for the current language.
		YSI_g_sTextCount - Count of largest number of texts in one language.
		YSI_g_sBufferLang - Current language being loaded.
		YSI_g_sLangBuffer - Saves the current position of each language.
		YSI_g_sColours - Saves defined colours for use.
Commands:
	-
Compile options:
	-
Operators:
	-
</remarks>
\**--------------------------------------------------------------------------**/

// Include "y_unique" multiple times.
#include "..\YSI_Internal\y_unique"
#if AUTO_INCLUDE_GUARD
	#if !defined _inc_y_text
		#error Did you do <YSI-Players/y_text> instead of the required <YSI-Players\y_text>?
	#endif
	#undef _inc_y_text
#endif

// Need an include guard here.
#if defined _INC_y_text
	#endinput
#endif
#define _INC_y_text

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
#define DO_MOVE|||%0$$$ %0DO_MOVE|||

#define Text_Send(%0,%1) PSF:_Text_Send(%0,DO_TEXT_SET:%1 UNDO_MOVE|||)
#define Text_Render(%0,%1) _Text_Render(%0,DO_TEXT_SET:%1 UNDO_MOVE|||)

//#define _Text_Send(%0YCMD:%1) _Text_Send(%0_:YCMD_REP_0:YCMD_REP_1:%1)

//#define YCMD_REP_0:YCMD_REP_1:%0, Command_GetID(%0),
//#define YCMD_REP_1:%0) Command_GetID(%0))

// This code allows "DEFAULT_TEXT_SET" to propogate through the text one section
// at a time without detecting later matches too early.  The design of "DO_MOVE"
// and "UNDO_MOVE" means that the compiler will correctly detect the end of the
// code, regardless of the length, and end.
#define Text_MessageBox(%0,%1,%2,%3,%4,%5) PSF:_Text_DialogBox(%0,DIALOG_STYLE_MSGBOX,%1,DO_TEXT_SET:%2 DO_MOVE|||,DO_TEXT_SET:%3 $$$,DO_TEXT_SET:%4 $$$,DO_TEXT_SET:%5 UN$$$)
#define Text_InputBox(%0,%1,%2,%3,%4,%5) PSF:_Text_DialogBox(%0,DIALOG_STYLE_INPUT,%1,DO_TEXT_SET:%2 DO_MOVE|||,DO_TEXT_SET:%3 $$$,DO_TEXT_SET:%4 $$$,DO_TEXT_SET:%5 UN$$$)
#define Text_ListBox(%0,%1,%2,%3,%4,%5) PSF:_Text_DialogBox(%0,DIALOG_STYLE_LIST,%1,DO_TEXT_SET:%2 DO_MOVE|||,DO_TEXT_SET:%3 $$$,DO_TEXT_SET:%4 $$$,DO_TEXT_SET:%5 UN$$$)
#define Text_PasswordBox(%0,%1,%2,%3,%4,%5) PSF:_Text_DialogBox(%0,DIALOG_STYLE_PASSWORD,%1,DO_TEXT_SET:%2 DO_MOVE|||,DO_TEXT_SET:%3 $$$,DO_TEXT_SET:%4 $$$,DO_TEXT_SET:%5 UN$$$)
#define Text_DialogBox(%0,%9,%1,%2,%3,%4,%5) PSF:_Text_DialogBox(%0,%9,%1,DO_TEXT_SET:%2 DO_MOVE|||,DO_TEXT_SET:%3 $$$,DO_TEXT_SET:%4 $$$,DO_TEXT_SET:%5 UN$$$)
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

