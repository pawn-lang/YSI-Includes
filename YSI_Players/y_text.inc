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

#if defined _inc_y_text
	#undef _inc_y_text
#endif

#if !defined _Y_UNIQUE_INCLUDED
	#tryinclude "..\YSI_Coding\y_unique\y_unique_entry"
#endif
#if !defined _Y_UNIQUE_INCLUDED
	#tryinclude "YSI_Coding\y_unique\y_unique_entry"
#endif
#if !defined _Y_UNIQUE_INCLUDED
	#tryinclude "YSI\YSI_Coding\y_unique\y_unique_entry"
#endif
#if !defined _Y_UNIQUE_INCLUDED
	#tryinclude <YSI_Coding\y_unique\y_unique_entry>
#endif
#if !defined _Y_UNIQUE_INCLUDED
	#tryinclude <YSI\YSI_Coding\y_unique\y_unique_entry>
#endif
#if defined _Y_UNIQUE_INCLUDED
	#undef _Y_UNIQUE_INCLUDED
#else
	#error Did you use `YSI/y_text` instead of `YSI\y_text`?
#endif

#if !defined _INC_y_text
	#tryinclude "y_text\y_text_entry"
#endif
#if !defined _INC_y_text
	#tryinclude "YSI_Players\y_text\y_text_entry"
#endif
#if !defined _INC_y_text
	#tryinclude "YSI\YSI_Players\y_text\y_text_entry"
#endif
#if !defined _INC_y_text
	#tryinclude <YSI_Players\y_text\y_text_entry>
#endif
#if !defined _INC_y_text
	#tryinclude <YSI\YSI_Players\y_text\y_text_entry>
#endif
#if !defined _INC_y_text
	#error Could not find y_text
#endif

