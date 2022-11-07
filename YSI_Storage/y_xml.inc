#if defined _INC_y_xml
	#endinput
#endif

/**
 * <library
 *   name="y_xml"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <remarks>
 *     <p>Parses XML files according to a set of defined rules.  A rule is a custom
 *     function called on a tag when all the data for that tag has been collected.
 *     The data for a tag could consist of simple <c>bla="bla"</c> pairs,
 *     <c>&lt;tag&gt;data&lt;/tag&gt;</c> pairs or cominations of the two,
 *     including subtags, each with their own possible custom handlers.</p>
 *     
 *     <p>Data for the tag is retrieved from a custom function using only:</p>
 *     
 *     <code>while (XML_GetKeyValue(ident, data)) {}</code>
 *   </remarks>
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

#if !defined _INC_y_xml
	#tryinclude "y_xml\y_xml_entry"
#endif
#if !defined _INC_y_xml
	#tryinclude "YSI_Storage\y_xml\y_xml_entry"
#endif
#if !defined _INC_y_xml
	#tryinclude "YSI\YSI_Storage\y_xml\y_xml_entry"
#endif
#if !defined _INC_y_xml
	#tryinclude <YSI_Storage\y_xml\y_xml_entry>
#endif
#if !defined _INC_y_xml
	#tryinclude <YSI\YSI_Storage\y_xml\y_xml_entry>
#endif
#if !defined _INC_y_xml
	#error Could not find y_xml
#endif

