/**
 * <library
 *   name="y_ini"
 *   version="1.5"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Reads the INI and also exports a number of functions to other "classes" for easy reading of data files there."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <section>
 *     Functions
 *   </section>
 *   <subsection>
 *     Stock
 *   </subsection><ul>
 *     <symbol name="INI_Load">Loads an INI file using standard features.</symbol>
 *     <symbol name="INI_ParseFile">Loads a file as an ini and distributes data.</symbol>
 *     <symbol name="INI_GetEntryName">Gets the name of an INI item.</symbol>
 *     <symbol name="INI_GetEntryText">Gets the value of an INI item.</symbol>
 *     <symbol name="INI_Open">Opens an INI for writing.</symbol>
 *     <symbol name="INI_Close">Closes an INI being written to.</symbol>
 *     <symbol name="INI_SetTag">Sets a subheading in an INI fo subsequent writes.</symbol>
 *     <symbol name="INI_WriteString">Writes a string to an INI.</symbol>
 *     <symbol name="INI_WriteInt">Writes an int to an INI.</symbol>
 *     <symbol name="INI_WriteFloat">Writes a float to an INI.</symbol>
 *     <symbol name="INI_WriteHex">Writes a hex to an INI.</symbol>
 *     <symbol name="INI_WriteBin">Writes a binary to an INI.</symbol>
 *     <symbol name="INI_WriteBool">Writes a boolean to an INI.</symbol>
 *     <symbol name="INI_RemoveEntry">Remove an entry from a file.</symbol>
 *   </ul><subsection>
 *     Static
 *   </subsection><ul>
 *     <symbol name="INI_WriteBuffer">Writes an INI's buffer to the file.</symbol>
 *     <symbol name="INI_AddToBuffer">Adds a string to an INI buffer.</symbol>
 *   </ul><subsection>
 *     Inline
 *   </subsection><ul>
 *     <symbol name="INI_Int">Parse an integer INI entry.</symbol>
 *     <symbol name="INI_Float">Parse a float INI entry.</symbol>
 *     <symbol name="INI_Hex">Parse a hex INI entry.</symbol>
 *     <symbol name="INI_Bin">Parse a binary INI entry.</symbol>
 *     <symbol name="INI_Bool">Parse a binary INI entry.</symbol>
 *     <symbol name="INI_String">Parse a string INI entry.</symbol>
 *   </ul><section>
 *     Definitions
 *   </section><ul>
 *     <symbol name="MAX_INI_TAG">Maximum length of an INI tagname.</symbol>
 *     <symbol name="MAX_INI_ENTRY_NAME">Maximum length of an INI entry name.</symbol>
 *     <symbol name="MAX_INI_ENTRY_TEXT">Maximum length of an INI's entries' value.</symbol>
 *     <symbol name="MAX_INI_LINE">Maximum length of a line in a file.</symbol>
 *     <symbol name="INI_NEW_LINE">String for new lines.</symbol>
 *     <symbol name="INI_MAX_WRITES">Maximum concurrent files open for writing.</symbol>
 *     <symbol name="MAX_INI_TAGS">Number of tags the buffer can hold data for at once.</symbol>
 *   </ul><section>
 *     Enums
 *   </section><ul>
 *     <symbol name="E_INI_WRITE">Storage for entries to be written.</symbol>
 *     <symbol name="E_INI_TAGS">Data for tags with data.</symbol>
 *   </ul><section>
 *     Macros
 *   </section><ul>
 *     <symbol name="INI_Parse">Header for ini parsing functions.</symbol>
 *   </ul><section>
 *     Tags
 *   </section><ul>
 *     <symbol name="INI">Handle to an INI file being written to.</symbol>
 *   </ul><section>
 *     Variables
 *   </section>
 *   <subsection>
 *     Static
 *   </subsection><ul>
 *     <symbol name="YSI_g_sINIWriteBuffer">Basic data to be written.</symbol>
 *     <symbol name="YSI_g_sINIWritePos">Next slot to write to.</symbol>
 *     <symbol name="YSI_g_sINITagPos">Next slot to add a tag to.</symbol>
 *     <symbol name="YSI_g_sINICurrentTag">Pointer to the tag been writen to.</symbol>
 *     <symbol name="YSI_g_sINIWriteTag">Data for tags,</symbol>
 *     <symbol name="YSI_g_sINIWriteFile">Current files been written to.</symbol>
 *   </ul>
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

#if !defined _INC_y_ini
	#tryinclude "y_ini\y_ini_entry"
#endif
#if !defined _INC_y_ini
	#tryinclude "YSI_Storage\y_ini\y_ini_entry"
#endif
#if !defined _INC_y_ini
	#tryinclude "YSI\YSI_Storage\y_ini\y_ini_entry"
#endif
#if !defined _INC_y_ini
	#tryinclude <YSI_Storage\y_ini\y_ini_entry>
#endif
#if !defined _INC_y_ini
	#tryinclude <YSI\YSI_Storage\y_ini\y_ini_entry>
#endif
#if !defined _INC_y_ini
	#error Could not find y_ini
#endif

