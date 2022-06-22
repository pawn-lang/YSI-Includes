/**
 * <library
 *   name="y_flooding"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Allows a limited number of connections from a single IP."
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
 *     Core
 *   </subsection><ul>
 *     <symbol name="OnPlayerConnect">Called to check IPs.</symbol>
 *     <symbol name="OnYSIInit">Sets the OnPlayerConnect function flag.</symbol>
 *   </ul><subsection>
 *     API
 *   </subsection><ul>
 *     <symbol name="SetMaxConnections">Sets the max allowed connections from an IP.</symbol>
 *   </ul><section>
 *     Enums
 *   </section><ul>
 *     <symbol name="e_FLOOD_ACTION">What to do if too many connections form.</symbol>
 *   </ul><section>
 *     Variables
 *   </section>
 *   <subsection>
 *     Static
 *   </subsection><ul>
 *     <symbol name="YSI_g_sPlayerIPs">People's stored IPs for speed.</symbol>
 *     <symbol name="YSI_g_sMaxConnections">Data for the script.</symbol>
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

#if !defined _INC_y_flooding
	#tryinclude "y_flooding\y_flooding_entry"
#endif
#if !defined _INC_y_flooding
	#tryinclude "YSI_Server\y_flooding\y_flooding_entry"
#endif
#if !defined _INC_y_flooding
	#tryinclude "YSI\YSI_Server\y_flooding\y_flooding_entry"
#endif
#if !defined _INC_y_flooding
	#tryinclude <YSI_Server\y_flooding\y_flooding_entry>
#endif
#if !defined _INC_y_flooding
	#tryinclude <YSI\YSI_Server\y_flooding\y_flooding_entry>
#endif
#if !defined _INC_y_flooding
	#error Could not find y_flooding
#endif

