/*                                                                                              *
 *                                                                                             *
 *     _____ ______ ______   ____  ______ _      ______          __  ______ ____  _____        *
 *    / ____|  ____|  ____| |  _ \|  ____| |    / __ \ \        / / |  ____/ __ \|  __ \       *
 *   | (___ | |__  | |__    | |_) | |__  | |   | |  | \ \  /\  / /  | |__ | |  | | |__) |      *
 *    \___ \|  __| |  __|   |  _ <|  __| | |   | |  | |\ \/  \/ /   |  __|| |  | |  _  /       *
 *    ____) | |____| |____  | |_) | |____| |___| |__| | \  /\  /    | |   | |__| | | \ \       *
 *   |_____/|______|______| |____/|______|______\____/   \/  \/     |_|    \____/|_|  \_\      *
 *                                                                                             *
 *    _____   ____   _____ _    _ __  __ ______ _   _ _______    _______ _____ ____  _   _     *
 *   |  __ \ / __ \ / ____| |  | |  \/  |  ____| \ | |__   __|/\|__   __|_   _/ __ \| \ | |    *
 *   | |  | | |  | | |    | |  | | \  / | |__  |  \| |  | |  /  \  | |    | || |  | |  \| |    *
 *   | |  | | |  | | |    | |  | | |\/| |  __| | . ` |  | | / /\ \ | |    | || |  | | . ` |    *
 *   | |__| | |__| | |____| |__| | |  | | |____| |\  |  | |/ ____ \| |   _| || |__| | |\  |    *
 *   |_____/ \____/ \_____|\____/|_|  |_|______|_| \_|  |_/_/    \_\_|  |_____\____/|_| \_|    *
 *                                                                                             *
 *   This is required for technical reasons - to place it after `#endinput` to not generate    *
 *                   multiple copies of it in XML when compiling with `-r`.                    *
 *                                                                                             *
*//*
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

/**
 * <library name="y_iterate">
 * <section>
 *  Description
 * </section>
 *  Provides efficient looping through sparse data sets, such as connected
 *  players.  Significantly improved from the original version to be a generic
 *  loop system, rather then purely a player loop system.  When used for
 *  players this has constant time O(n) for number of connected players (n),
 *  unlike standard player loops which are O(MAX_PLAYERS), regardless of the
 *  actual number of connected players.  Even when n is MAX_PLAYERS this is
 *  still faster.
 *
 *  For extensive documentation on writing and using iterators, see this topic:
 *
 *      <a href="http://forum.sa-mp.com/showthread.php?t=481877" />
 *
 * <section>
 *  Version
 * </section>
 *  0.4
 * <section>
 *  Functions
 * </section>
 * <subsection>
 * Public
 * </subsection><ul>
 *  <symbol name="OnPlayerDisconnect">Called when a player leaves to remove them.</symbol>
 *  <symbol name="OnPlayerConnect">Called when a player connects to add them.</symbol>
 * </ul><subsection>
 * Stock
 * </subsection><ul>
 *  <symbol name="Iter_ShowArray">Displays the contents of the array.</symbol>
 *  <symbol name="Iter_AddInternal">Add a value to an iterator.</symbol>
 *  <symbol name="Iter_RemoveInternal">Remove a value from an iterator.</symbol>
 *  <symbol name="Iter_RandomInternal">Get a random item from an iterator.</symbol>
 *  <symbol name="Iter_FreeInternal">Gets the first free slot in the iterator.</symbol>
 *  <symbol name="Iter_InitInternal">Initialises a multi-dimensional iterator.</symbol>
 * </ul><subsection>
 * Inline
 * </subsection><ul>
 *  <symbol name="Iter_Create">Create a new iterator value set.</symbol>
 *  <symbol name="Iter_Add">Wraps Iter_AddInternal.</symbol>
 *  <symbol name="Iter_Remove">Wraps Iter_RemoveInternal.</symbol>
 *  <symbol name="Iter_Random">Wraps Iter_RandomInternal.</symbol>
 *  <symbol name="Iter_Count">Gets the number of items in an iterator.</symbol>
 *  <symbol name="Iter_Debug">Wraps around Iter_ShowArray.</symbol>
 *  <symbol name="Iter_Free">Wraps around Iter_FreeInternal.</symbol>
 *  <symbol name="Iter_Create2">Create a new iterator array value set.</symbol>
 *  <symbol name="Iter_Add2">Wraps Iter_AddInternal for arrays.</symbol>
 *  <symbol name="Iter_Remove2">Wraps Iter_RemoveInternal for arrays.</symbol>
 *  <symbol name="Iter_Random2">Wraps Iter_RandomInternal for arrays.</symbol>
 *  <symbol name="Iter_Count2">Gets the number of items in an iterator array.</symbol>
 *  <symbol name="Iter_Debug2">Wraps around Iter_ShowArray for arrays.</symbol>
 *  <symbol name="Iter_Free2">Wraps around Iter_FreeInternal for arrays.</symbol>
 * </ul><section>
 *  Hooks
 * </section><ul>
 *  <symbol name="Iter_OnPlayerConnect">Hook for the OnPlayerConnect callback.</symbol>
 *  <symbol name="Iter_OnPlayerDisconnect">Hook for the OnPlayerDisconnect callback.</symbol>
 *  <symbol name="Iter_OnGameModeInit">Only exists to make the code compile correctly...</symbol>
 * </ul><section>
 *  Keywords
 * </section><ul>
 *  <symbol name="foreach">Command to loop an iterator.</symbol>
 *  <symbol name="foreachex">Like foreach but without a new variable.</symbol>
 *  <symbol name="foreach2">Command to loop through an iterator array.</symbol>
 *  <symbol name="foreachex">Like foreach2 but without a new variable.</symbol>
 * </ul><section>
 *  Tags
 * </section><ul>
 *  <symbol name="Iterator">Declare an iterator.</symbol>
 * </ul><section>
 *  Variables
 * </section>
 * <subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="YSI_g_OPC">Records wether Iter_OnPlayerConnect exists for speed.</symbol>
 *  <symbol name="YSI_g_OPDC">Records wether Iter_OnPlayerDisconnect exists for speed.</symbol>
 * </ul><section>Compile options</section><ul>
 *  <symbol name="YSI_ITTER_NO_SORT">Removed.</symbol>
 *  <symbol name="FOREACH_NO_BOTS">Remove the bot iterators for smaller code.</symbol>
 *  <symbol name="FOREACH_NO_PLAYERS">Remove all default code for player itteration.</symbol>
 * </ul><section>
 *  Iterators
 * </section><ul>
 *  <symbol name="Player">List of all players connected.</symbol>
 *  <symbol name="Bot">List of all bots (npcs) connected.</symbol>
 *  <symbol name="NPC">Alias of Bot.</symbol>
 *  <symbol name="Character">All players and bots.</symbol>
 * </ul><section>
 *  Examples
 * </section>
 *
 *
 *
 *
 * <subsection>Basic Iterators</subsection>
 *
 * <p>
 * Basic iterators are simply collections of numbers - little more than an array.
 * A number is either in the array, or not in the array, <em>y_iterate</em> loops
 * through only the <em>in</em> numbers.</p>
 *
 * <p><em>Players</em><br /><br />
 *
 * This code will loop through every player connected to the server.
 *
 * <code>
 * foreach (new i : Player)																				<br />
 * {																				<br /><indent />
 *  printf("player %d is connected", i);																				<br />
 * }
 * </code>
 * </p>
 *
 * <p><em>Vehicles</em><br /><br />
 *
 * This code will loop through all the created vehicles on the server (including
 * those made in other running scripts).
 *
 * <code>
 * foreach (new vid : Vehicle)																				<br />
 * {																				<br /><indent />
 *  printf("vehicleid %d has been created", vid);																				<br />
 * }
 * </code>
 * </p>
 *
 * <p><em>Create An Iterator</em><br /><br />
 *
 * To create your own iterator, first declare it, then add things to it, then loop
 * over it:
 *
 * <code>
 * new																				<br /><indent />
 *  Iterator:MyIter&lt;100&gt;; // First declare it (this has room for 100 items numbered 0-99).																				<br />
 * // Then add things to it.																				<br />
 * Iter_Add(MyIter, 0);  // Fine.																				<br />
 * Iter_Add(MyIter, 55); // Fine.																				<br />
 * Iter_Add(MyIter, 100); // Will fail.																				<br />
 * // Then loop over it.																				<br />
 * foreach (new i : MyIter)																				<br />
 * {																				<br /><indent />
 *  printf("%d", i); // Will print "0" then "55".																				<br />
 * }
 * </code>
 * </p>
 *
 * <subsection>Special Iterators</subsection>
 *
 * </library>
 *//** */


