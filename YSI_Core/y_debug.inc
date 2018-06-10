/**
 * <library name="y_debug">
 * <section>
 *  Description
 * </section>
 *  <p>Ensures debug levels are set and defines debug functions.</p>
 *
 *  <p>General debug levels:</p>
 *
 *  <ul>
 *  <li>-1 - Run-time selected debug level.</li>
 *  <li>0 - No debug information.</li>
 *  <li>1 - Callbacks and timers.</li>
 *  <li>2 - Remote functions.</li>
 *  <li>3 - Stock functions.</li>
 *  <li>4 - Static functions.</li>
 *  <li>5 - Code.</li>
 *  <li>6 - Loops.</li>
 *  <li>7 - Extra loop code.</li>
 *  </ul>
 *
 *  <p>If you use <c>P:0</c> you get an optional debug print controlled by the
 *  global state <c>ysi_debug</c> - which is either on or off.</p>
 * <section>
 *  Version
 * </section>
 *  1.0
 * <section>
 *  Functions
 * </section>
 * <subsection>
 * Inline
 * </subsection><ul>
 *  <symbol name="Debug_Code">Runs defined code if a certain level is active.</symbol>
 *  <symbol name="Debug_Print">Prints the formatted string provided at the given level.</symbol>
 * </ul><subsection>
 * Stock
 * </subsection><ul>
 *  <symbol name="Debug_PrintArray">Print several items from an array for debugging purposes.</symbol>
 *  <symbol name="Debug_Enable">Turn on level 0 prints.</symbol>
 *  <symbol name="Debug_Disable">Turn off level 0 prints.</symbol>
 *  <symbol name="Debug_Level">Set the debug level when the code is compiled with
 *  <c>_DEBUG=-1</c>, which means full run-time selection.</symbol>
 * </ul><section>
 *  Definitions
 * </section><ul>
 *  <symbol name="P:&lt;0-6&gt;">Print a message.</symbol>
 *  <symbol name="P:C">Run debug code.</symbol>
 *  <symbol name="P:E">Print an error message.</symbol>
 *  <symbol name="P:W">Print a warning message.</symbol>
 * </ul><section>Compile options</section><ul>
 *  <symbol name="_DEBUG">Debugging level to use.</symbol>
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

#if !defined _INC_y_utils
	#tryinclude "y_core\y_core_entry"
#endif
#if !defined _INC_y_core
	#tryinclude "YSI_Core\y_core\y_core_entry"
#endif
#if !defined _INC_y_core
	#tryinclude "YSI\YSI_Core\y_core\y_core_entry"
#endif
#if !defined _INC_y_core
	#tryinclude <YSI_Core\y_core\y_core_entry>
#endif
#if !defined _INC_y_core
	#tryinclude <YSI\YSI_Core\y_core\y_core_entry>
#endif
#if !defined _INC_y_core
	#error Could not find y_debug
#endif

