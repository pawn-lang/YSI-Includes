/**
<file>
					y_foreach
</file>
<section>
	Description
</section>
	Provides efficient looping through sparse data sets, such as connected
	players.  Significantly improved from the original version to be a generic
	loop system, rather then purely a player loop system.  When used for
	players this has constant time O(n) for number of connected players (n),
	unlike standard player loops which are O(MAX_PLAYERS), regardless of the
	actual number of connected players.  Even when n is MAX_PLAYERS this is
	still faster.
	
	For extensive documentation on writing and using iterators, see this topic:
	
		<a href="http://forum.sa-mp.com/showthread.php?t=481877" />
	
<section>
	Version
</section>
	0.4
<section>
	Changelog
</section><ul>
	29/03/15:
		More testing.
		Repaired special iterators.
	28/03/15:
		Breaking change: "Iter_Add" returns value added, not true/false.
		Breaking change: Special iterators take "cellmin", not "-1".
		Wrote many tests.
		Split in to multiple files.
		Added multi-iterators.
		Officially deprecated "foreach (Player, i)".
	26/03/15:
		Re-added reverse iterators.
		Added support for extra spaces in "foreach".
	26/12/13:
		Added sections.
	17/10/12:
		Fixed a bug that was here but not in "foreach.inc".
	04/10/12:
		Added a tiny tweak to detect tag-returning iterator functions.
		Added Iter_InternalSize.
	13/01/12:
		Fixed the count thanks to AndreT.
	05/01/12:
		Fixed multi-dimensional iterators.
		Fixed "FOREACH_NO_BOTS".
		Made "Iterator:" support multi-dimensional arrays.
	24/12/11:
		Added _YSI_SPECIAL_DEBUG support.
		Added fix for function iterators.
		Ported back to YSI.
		Changed to use internal YSI "__" natives.
		Fixed calls order by using ALS.
	31/10/11:
		Changed the underlying loop code to be slightly faster.
		Added support for Iter_SafeRemove, prompting refactoring.
	17/09/11:
		Fixed arrays under the new syntax.
	28/04/11:
		Moved iterator identifiers to end of variables.
		Rewrote "foreach" to accept two syntaxes for "foreach (new i : Iter)".
	16/08/10:
		Removed all the "2" versions of the functions.
	14/08/10:
		Added Iter_Clear to reset an array.
	06/08/10:
		Added special array declaration format.
	18/12/09:
		Added Iter_Func2 functions for multi-dimensional iterators.
		Renamed foreact et al as keywords in the documentation.
		Changed licensing from GPL to MPL.
	02/09/09:
		Fixed (again) for 0.3.
		Added free slot finding.
	21/08/09:
		Updated to include random functions.
		Made entirely stand alone.
		Ported to 0.3 (separate version).
		Added automatic callback hook code.
		Removed debug information from stand alone version.
	06/01/08:
		Added debug information.
	09/10/07:
		Moved to system.
	16/09/07:
		Added list sorting.
		Made this part of Y SeRver Includes, not Y Sever Includes.
		Made list sorting optional.
		Fixed version number.
	08/09/07:
		First version.
</ul><section>
	Functions
</section><ul>
<li><subsection>Public</subsection><ul>
<entry name="OnPlayerDisconnect">Called when a player leaves to remove them.</entry>
<entry name="OnPlayerConnect">Called when a player connects to add them.</entry>
</ul></li><li><subsection>Stock</subsection><ul>
<entry name="Iter_ShowArray">Displays the contents of the array.</entry>
<entry name="Iter_AddInternal">Add a value to an iterator.</entry>
<entry name="Iter_RemoveInternal">Remove a value from an iterator.</entry>
<entry name="Iter_RandomInternal">Get a random item from an iterator.</entry>
<entry name="Iter_FreeInternal">Gets the first free slot in the iterator.</entry>
<entry name="Iter_InitInternal">Initialises a multi-dimensional iterator.</entry>
</ul></li><li><subsection>Inline</subsection><ul>
<entry name="Iter_Create">Create a new iterator value set.</entry>
<entry name="Iter_Add">Wraps Iter_AddInternal.</entry>
<entry name="Iter_Remove">Wraps Iter_RemoveInternal.</entry>
<entry name="Iter_Random">Wraps Iter_RandomInternal.</entry>
<entry name="Iter_Count">Gets the number of items in an iterator.</entry>
<entry name="Iter_Debug">Wraps around Iter_ShowArray.</entry>
<entry name="Iter_Free">Wraps around Iter_FreeInternal.</entry>
<entry name="Iter_Create2">Create a new iterator array value set.</entry>
<entry name="Iter_Add2">Wraps Iter_AddInternal for arrays.</entry>
<entry name="Iter_Remove2">Wraps Iter_RemoveInternal for arrays.</entry>
<entry name="Iter_Random2">Wraps Iter_RandomInternal for arrays.</entry>
<entry name="Iter_Count2">Gets the number of items in an iterator array.</entry>
<entry name="Iter_Debug2">Wraps around Iter_ShowArray for arrays.</entry>
<entry name="Iter_Free2">Wraps around Iter_FreeInternal for arrays.</entry>
</ul></li></ul><section>
	Hooks
</section><ul>
<entry name="Iter_OnPlayerConnect">Hook for the OnPlayerConnect callback.</entry>
<entry name="Iter_OnPlayerDisconnect">Hook for the OnPlayerDisconnect callback.</entry>
<entry name="Iter_OnGameModeInit">Only exists to make the code compile correctly...</entry>
</ul><section>
	Keywords
</section><ul>
<entry name="foreach">Command to loop an iterator.</entry>
<entry name="foreachex">Like foreach but without a new variable.</entry>
<entry name="foreach2">Command to loop through an iterator array.</entry>
<entry name="foreachex">Like foreach2 but without a new variable.</entry>
</ul><section>
	Tags
</section><ul>
<entry name="Iterator">Declare an iterator.</entry>
</ul><section>
	Variables
</section><ul>
<li><subsection>Static</subsection><ul>
<entry name="YSI_g_OPC">Records wether Iter_OnPlayerConnect exists for speed.</entry>
<entry name="YSI_g_OPDC">Records wether Iter_OnPlayerDisconnect exists for speed.</entry>
</ul></li></ul><section>Compile options</section><ul>
<entry name="YSI_ITTER_NO_SORT">Removed.</entry>
<entry name="FOREACH_NO_BOTS">Remove the bot iterators for smaller code.</entry>
<entry name="FOREACH_NO_PLAYERS">Remove all default code for player itteration.</entry>
</ul><section>
	Iterators
</section><ul>
<entry name="Player">List of all players connected.</entry>
<entry name="Bot">List of all bots (npcs) connected.</entry>
<entry name="NPC">Alias of Bot.</entry>
<entry name="Character">All players and bots.</entry>
</ul>
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

#include "y_iterate"

