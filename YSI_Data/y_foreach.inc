/**
<library>
					y_foreach
</library>
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
<changelog date="29/03/15">
<li>More testing.</li>
<li>Repaired special iterators.</li>
</changelog>
<changelog date="28/03/15">
<li>Breaking change: "Iter_Add" returns value added, not true/false.</li>
<li>Breaking change: Special iterators take "cellmin", not "-1".</li>
<li>Wrote many tests.</li>
<li>Split in to multiple files.</li>
<li>Added multi-iterators.</li>
<li>Officially deprecated "foreach (Player, i)".</li>
</changelog>
<changelog date="26/03/15">
<li>Re-added reverse iterators.</li>
<li>Added support for extra spaces in "foreach".</li>
</changelog>
<changelog date="26/12/13">
<li>Added sections.</li>
</changelog>
<changelog date="17/10/12">
<li>Fixed a bug that was here but not in "foreach.inc".</li>
</changelog>
<changelog date="04/10/12">
<li>Added a tiny tweak to detect tag-returning iterator functions.</li>
<li>Added Iter_InternalSize.</li>
</changelog>
<changelog date="13/01/12">
<li>Fixed the count thanks to AndreT.</li>
</changelog>
<changelog date="05/01/12">
<li>Fixed multi-dimensional iterators.</li>
<li>Fixed "FOREACH_NO_BOTS".</li>
<li>Made "Iterator:" support multi-dimensional arrays.</li>
</changelog>
<changelog date="24/12/11">
<li>Added _YSI_SPECIAL_DEBUG support.</li>
<li>Added fix for function iterators.</li>
<li>Ported back to YSI.</li>
<li>Changed to use internal YSI "__" natives.</li>
<li>Fixed calls order by using ALS.</li>
</changelog>
<changelog date="31/10/11">
<li>Changed the underlying loop code to be slightly faster.</li>
<li>Added support for Iter_SafeRemove, prompting refactoring.</li>
</changelog>
<changelog date="17/09/11">
<li>Fixed arrays under the new syntax.</li>
</changelog>
<changelog date="28/04/11">
<li>Moved iterator identifiers to end of variables.</li>
<li>Rewrote "foreach" to accept two syntaxes for "foreach (new i : Iter)".</li>
</changelog>
<changelog date="16/08/10">
<li>Removed all the "2" versions of the functions.</li>
</changelog>
<changelog date="14/08/10">
<li>Added Iter_Clear to reset an array.</li>
</changelog>
<changelog date="06/08/10">
<li>Added special array declaration format.</li>
</changelog>
<changelog date="18/12/09">
<li>Added Iter_Func2 functions for multi-dimensional iterators.</li>
<li>Renamed foreact et al as keywords in the documentation.</li>
<li>Changed licensing from GPL to MPL.</li>
</changelog>
<changelog date="02/09/09">
<li>Fixed (again) for 0.3.</li>
<li>Added free slot finding.</li>
</changelog>
<changelog date="21/08/09">
<li>Updated to include random functions.</li>
<li>Made entirely stand alone.</li>
<li>Ported to 0.3 (separate version).</li>
<li>Added automatic callback hook code.</li>
<li>Removed debug information from stand alone version.</li>
</changelog>
<changelog date="06/01/08">
<li>Added debug information.</li>
</changelog>
<changelog date="09/10/07">
<li>Moved to system.</li>
</changelog>
<changelog date="16/09/07">
<li>Added list sorting.</li>
<li>Made this part of Y SeRver Includes, not Y Sever Includes.</li>
<li>Made list sorting optional.</li>
<li>Fixed version number.</li>
</changelog>
<changelog date="08/09/07">
<li>First version.</li>
</changelog>
</ul><section>
	Functions
</section>
<subsection>
Public
</subsection><ul>
	<symbol name="OnPlayerDisconnect">Called when a player leaves to remove them.</symbol>
	<symbol name="OnPlayerConnect">Called when a player connects to add them.</symbol>
</ul><subsection>
Stock
</subsection><ul>
	<symbol name="Iter_ShowArray">Displays the contents of the array.</symbol>
	<symbol name="Iter_AddInternal">Add a value to an iterator.</symbol>
	<symbol name="Iter_RemoveInternal">Remove a value from an iterator.</symbol>
	<symbol name="Iter_RandomInternal">Get a random item from an iterator.</symbol>
	<symbol name="Iter_FreeInternal">Gets the first free slot in the iterator.</symbol>
	<symbol name="Iter_InitInternal">Initialises a multi-dimensional iterator.</symbol>
</ul><subsection>
Inline
</subsection><ul>
	<symbol name="Iter_Create">Create a new iterator value set.</symbol>
	<symbol name="Iter_Add">Wraps Iter_AddInternal.</symbol>
	<symbol name="Iter_Remove">Wraps Iter_RemoveInternal.</symbol>
	<symbol name="Iter_Random">Wraps Iter_RandomInternal.</symbol>
	<symbol name="Iter_Count">Gets the number of items in an iterator.</symbol>
	<symbol name="Iter_Debug">Wraps around Iter_ShowArray.</symbol>
	<symbol name="Iter_Free">Wraps around Iter_FreeInternal.</symbol>
	<symbol name="Iter_Create2">Create a new iterator array value set.</symbol>
	<symbol name="Iter_Add2">Wraps Iter_AddInternal for arrays.</symbol>
	<symbol name="Iter_Remove2">Wraps Iter_RemoveInternal for arrays.</symbol>
	<symbol name="Iter_Random2">Wraps Iter_RandomInternal for arrays.</symbol>
	<symbol name="Iter_Count2">Gets the number of items in an iterator array.</symbol>
	<symbol name="Iter_Debug2">Wraps around Iter_ShowArray for arrays.</symbol>
	<symbol name="Iter_Free2">Wraps around Iter_FreeInternal for arrays.</symbol>
</ul><section>
	Hooks
</section><ul>
	<symbol name="Iter_OnPlayerConnect">Hook for the OnPlayerConnect callback.</symbol>
	<symbol name="Iter_OnPlayerDisconnect">Hook for the OnPlayerDisconnect callback.</symbol>
	<symbol name="Iter_OnGameModeInit">Only exists to make the code compile correctly...</symbol>
</ul><section>
	Keywords
</section><ul>
	<symbol name="foreach">Command to loop an iterator.</symbol>
	<symbol name="foreachex">Like foreach but without a new variable.</symbol>
	<symbol name="foreach2">Command to loop through an iterator array.</symbol>
	<symbol name="foreachex">Like foreach2 but without a new variable.</symbol>
</ul><section>
	Tags
</section><ul>
	<symbol name="Iterator">Declare an iterator.</symbol>
</ul><section>
	Variables
</section>
<subsection>
Static
</subsection><ul>
	<symbol name="YSI_g_OPC">Records wether Iter_OnPlayerConnect exists for speed.</symbol>
	<symbol name="YSI_g_OPDC">Records wether Iter_OnPlayerDisconnect exists for speed.</symbol>
</ul><section>Compile options</section><ul>
	<symbol name="YSI_ITTER_NO_SORT">Removed.</symbol>
	<symbol name="FOREACH_NO_BOTS">Remove the bot iterators for smaller code.</symbol>
	<symbol name="FOREACH_NO_PLAYERS">Remove all default code for player itteration.</symbol>
</ul><section>
	Iterators
</section><ul>
	<symbol name="Player">List of all players connected.</symbol>
	<symbol name="Bot">List of all bots (npcs) connected.</symbol>
	<symbol name="NPC">Alias of Bot.</symbol>
	<symbol name="Character">All players and bots.</symbol>
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

