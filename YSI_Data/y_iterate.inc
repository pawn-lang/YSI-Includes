/*+
 * <library
 *   name="y_iterate"
 *   version="0.4"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <remarks>
 *    <p>
 *    Provides efficient looping through sparse data sets, such as connected
 *    players.  Significantly improved from the original version to be a generic
 *    loop system, rather then purely a player loop system.  When used for
 *    players this has constant time O(n) for number of connected players (n),
 *    unlike standard player loops which are O(MAX_PLAYERS), regardless of the
 *    actual number of connected players.  Even when n is MAX_PLAYERS this is
 *    still faster.
 *    </p>
 *   
 *    <p>
 *    For extensive documentation on writing and using iterators, see
 *    <a href="http://forum.sa-mp.com/showthread.php?t=481877">this topic</a>
 *    </p>
 *   </remarks>
 *   <section>
 *     Examples
 *   </section>
 *   
 *   
 *   
 *   
 *   <subsection>Basic Iterators</subsection>
 *   
 *     <p>
 *     Basic iterators are simply collections of numbers - little more than an array.
 *     A number is either in the array, or not in the array, <em>y_iterate</em> loops
 *     through only the <em>in</em> numbers.</p>
 *     
 *     <p><em>Players</em><br /><br />
 *     
 *     This code will loop through every player connected to the server.
 *     
 *     <code>
 *     foreach (new i : Player)																				<br />
 *     {																				<br /><indent />
 *      printf("player %d is connected", i);																				<br />
 *     }
 *     </code>
 *     </p>
 *     
 *     <p><em>Vehicles</em><br /><br />
 *     
 *     This code will loop through all the created vehicles on the server (including
 *     those made in other running scripts).
 *     
 *     <code>
 *     foreach (new vid : Vehicle)																				<br />
 *     {																				<br /><indent />
 *      printf("vehicleid %d has been created", vid);																				<br />
 *     }
 *     </code>
 *     </p>
 *     
 *     <p><em>Create An Iterator</em><br /><br />
 *     
 *     To create your own iterator, first declare it, then add things to it, then loop
 *     over it:
 *     
 *     <code>
 *     new																				<br /><indent />
 *      Iterator:MyIter&lt;100&gt;; // First declare it (this has room for 100 items numbered 0-99).																				<br />
 *     // Then add things to it.																				<br />
 *     Iter_Add(MyIter, 0);  // Fine.																				<br />
 *     Iter_Add(MyIter, 55); // Fine.																				<br />
 *     Iter_Add(MyIter, 100); // Will fail.																				<br />
 *     // Then loop over it.																				<br />
 *     foreach (new i : MyIter)																				<br />
 *     {																				<br /><indent />
 *      printf("%d", i); // Will print "0" then "55".																				<br />
 *     }
 *     </code>
 *     </p>
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

#if !defined _INC_y_iterate
	#tryinclude "y_foreach\y_foreach_entry"
#endif
#if !defined _INC_y_iterate
	#tryinclude "YSI_Data\y_foreach\y_foreach_entry"
#endif
#if !defined _INC_y_iterate
	#tryinclude "YSI\YSI_Data\y_foreach\y_foreach_entry"
#endif
#if !defined _INC_y_iterate
	#tryinclude <YSI_Data\y_foreach\y_foreach_entry>
#endif
#if !defined _INC_y_iterate
	#tryinclude <YSI\YSI_Data\y_foreach\y_foreach_entry>
#endif
#if !defined _INC_y_iterate
	#error Could not find y_iterate
#endif

