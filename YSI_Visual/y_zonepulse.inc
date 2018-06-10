/**
 * <library name="y_zonepulse">
 * <section>
 *  Description
 * </section>
 *  Gradually fades a zone's colour between one colour and another, then back.
 * <section>
 *  Version
 * </section>
 *  0.1
 * <section>
 *  Functions
 * </section>
 * <subsection>
 * Public
 * </subsection><ul>
 *  <symbol name="__GangZonePulse">The timer that does the hard work.</symbol>
 * </ul><subsection>
 * Stock
 * </subsection><ul>
 *  <symbol name="GangZonePulse">Pulse a zone for player or collection of players.</symbol>
 *  <symbol name="GangZonePulseForPlayer">Pulse a zone for a player.</symbol>
 *  <symbol name="GangZonePulseForAll">Pulse a zone for everyone.</symbol>
 *  <symbol name="GangZoneStopPulse">Stop a zone pulsing for a set of players.</symbol>
 *  <symbol name="GangZoneStopPulseForPlayer">Stop a zone pulsing for a single player.</symbol>
 *  <symbol name="GangZoneStopPulseForAll">Stop a zone pulsing for everyone.</symbol>
 * </ul><section>Compile options</section><ul>
 *  <symbol name="ZONE_PULSE_STAGE_TIME">ms between each pulse frame.</symbol>
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

#if !defined _INC_y_zonepulse
	#tryinclude "y_zonepulse\y_zonepulse_entry"
#endif
#if !defined _INC_y_zonepulse
	#tryinclude "YSI_Visual\y_zonepulse\y_zonepulse_entry"
#endif
#if !defined _INC_y_zonepulse
	#tryinclude "YSI\YSI_Visual\y_zonepulse\y_zonepulse_entry"
#endif
#if !defined _INC_y_zonepulse
	#tryinclude <YSI_Visual\y_zonepulse\y_zonepulse_entry>
#endif
#if !defined _INC_y_zonepulse
	#tryinclude <YSI\YSI_Visual\y_zonepulse\y_zonepulse_entry>
#endif
#if !defined _INC_y_zonepulse
	#error Could not find y_zonepulse
#endif

