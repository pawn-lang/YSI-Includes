/**--------------------------------------------------------------------------**\
					===========================
					 foreach efficient looping
					===========================
Description:
	Provides efficient looping through sparse data sets, such as connected
	players.  Significantly improved from the original version to be a generic
	loop system, rather then purely a player loop system.  When used for
	players this has constant time O(n) for number of connected players (n),
	unlike standard player loops which are O(MAX_PLAYERS), regardless of the
	actual number of connected players.  Even when n is MAX_PLAYERS this is
	still faster.
	
	For extensive documentation on writing and using iterators, see this topic:
	
		http://forum.sa-mp.com/showthread.php?t=481877
	
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	[url]http://www.mozilla.org/MPL/[/url]
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI foreach include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
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
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	0.4
Changelog:
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
Functions:
	Public:
		OnPlayerDisconnect - Called when a player leaves to remove them.
		OnPlayerConnect - Called when a player connects to add them.
	Core:
		-
	Stock:
		Iter_ShowArray - Displays the contents of the array.
		Iter_AddInternal - Add a value to an iterator.
		Iter_RemoveInternal - Remove a value from an iterator.
		Iter_RandomInternal - Get a random item from an iterator.
		Iter_FreeInternal - Gets the first free slot in the iterator.
		Iter_InitInternal - Initialises a multi-dimensional iterator.
	Static:
		-
	Inline:
		Iter_Create - Create a new iterator value set.
		Iter_Add - Wraps Iter_AddInternal.
		Iter_Remove - Wraps Iter_RemoveInternal.
		Iter_Random - Wraps Iter_RandomInternal.
		Iter_Count - Gets the number of items in an iterator.
		Iter_Debug - Wraps around Iter_ShowArray.
		Iter_Free - Wraps around Iter_FreeInternal.
		Iter_Create2 - Create a new iterator array value set.
		Iter_Add2 - Wraps Iter_AddInternal for arrays.
		Iter_Remove2 - Wraps Iter_RemoveInternal for arrays.
		Iter_Random2 - Wraps Iter_RandomInternal for arrays.
		Iter_Count2 - Gets the number of items in an iterator array.
		Iter_Debug2 - Wraps around Iter_ShowArray for arrays.
		Iter_Free2 - Wraps around Iter_FreeInternal for arrays.
	API:
		-
Callbacks:
	-
Hooks:
	Iter_OnPlayerConnect - Hook for the OnPlayerConnect callback.
	Iter_OnPlayerDisconnect - Hook for the OnPlayerDisconnect callback.
	Iter_OnGameModeInit - Only exists to make the code compile correctly...
Definitions:
	-
Enums:
	-
Macros:
	-
Keywords:
	foreach - Command to loop an iterator.
	foreachex - Like foreach but without a new variable.
	foreach2 - Command to loop through an iterator array.
	foreachex - Like foreach2 but without a new variable.
Tags:
	Iterator - Declare an iterator.
Variables:
	Global:
		-
	Static:
		YSI_g_OPC - Records wether Iter_OnPlayerConnect exists for speed.
		YSI_g_OPDC - Records wether Iter_OnPlayerDisconnect exists for speed.
Commands:
	-
Compile options:
	YSI_ITTER_NO_SORT - Removed.
	FOREACH_NO_BOTS - Remove the bot iterators for smaller code.
	FOREACH_NO_PLAYERS - Remove all default code for player itteration.
Operators:
	-
Iterators:
	Player - List of all players connected.
	Bot - List of all bots (npcs) connected.
	NPC - Alias of Bot.
	Character - All players and bots.
\**--------------------------------------------------------------------------**/

/*

     ad88888ba                                              
    d8"     "8b              ,d                             
    Y8,                      88                             
    `Y8aaaaa,    ,adPPYba, MM88MMM 88       88 8b,dPPYba,   
      `"""""8b, a8P_____88   88    88       88 88P'    "8a  
            `8b 8PP"""""""   88    88       88 88       d8  
    Y8a     a8P "8b,   ,aa   88,   "8a,   ,a88 88b,   ,a8"  
     "Y88888P"   `"Ybbd8"'   "Y888  `"YbbdP'Y8 88`YbbdP"'   
                                               88           
                                               88           
    
*/

// "y_iterate" is always higher than "foreach".
#define _Y_ITERATE_LOCAL_VERSION        41

#if __Pawn != 0x030A
	#define NO_CUSTOM_WARNINGS
#endif

// Foreach is testing us.
#if defined _FOREACH_INC_TEST
	#define _FOREACH_CUR_VERSION _Y_ITERATE_LOCAL_VERSION
	#endinput
#endif
#if !defined _FOREACH_NO_TEST
	#define _FOREACH_INC_TEST
	#tryinclude <foreach>
	#undef _FOREACH_INC_TEST
	// <foreach> exists - test which is newer.
	#if defined _FOREACH_LOCAL_VERSION
		#if _FOREACH_LOCAL_VERSION > _Y_ITERATE_LOCAL_VERSION
			// Foreach is newer.
			#if defined _inc_foreach
				#undef _inc_foreach
			#endif
			#define _FOREACH_NO_TEST
			#include <foreach>
			#endinput
		#endif
	#elseif defined foreach
		#if __Pawn == 0x030A
			#define WARNING 1
			#include "y_iterate/warning" // Backwards-compatible directive.
			#endinput
		#else
			#error Old foreach.inc files are no longer compatible with YSI.
		#endif
	#endif
#endif
#define _FOREACH_INC_TEST

#if !defined _samp_included
	#error "Please include a_samp or a_npc before foreach"
#endif

#if defined _YSI_SPECIAL_DEBUG
	#define PS_IS_PLAYER_CONNECTED(%0) (%0 != INVALID_PLAYER_ID)
#else
	#define PS_IS_PLAYER_CONNECTED IsPlayerConnected
#endif

// 
// _FOREACH_BOTS
// 
// Should the "NPC", "Bot", and "Character" iterators be included by default?
// Disabled by declaring "FOREACH_NO_BOTS".
// 

#define _FOREACH_BOTS 0

#if defined IsPlayerNPC
	#define _FOREACH_BOT
	#if !defined FOREACH_NO_BOTS
		#undef _FOREACH_BOTS
		#define _FOREACH_BOTS 1
	#endif
#endif

// 
// _FOREACH_LOCALS
// 
// Should the "LocalActor" and "LocalVehicle" iterators be included?  These only
// loop through ones created by the current script, instead of through ones
// created in any script.
// 

#define _FOREACH_LOCALS 1

#if defined SendChat || defined FOREACH_NO_LOCALS
	#undef _FOREACH_LOCALS
	#define _FOREACH_LOCALS 0
#endif

// 
// _FOREACH_VEHICLES
// 
// Should the "Vehicle" iterator be included?  "Vehicle" loops over all vehicles
// created on the server, "LocalVehicle" iterates over vehicles created only in
// the current script.  They are the same when "YSI_NO_MASTER" is declared.
// Disabled by declaring "FOREACH_NO_VEHICLES".
// 

#define _FOREACH_VEHICLES 1

#if defined SendChat || defined FOREACH_NO_VEHICLES
	#undef _FOREACH_VEHICLES
	#define _FOREACH_VEHICLES 0
#endif

// 
// _FOREACH_ACTORS
// 
// Should the "Actor" iterator be included?  "Actor" loops over all actors
// created on the server, "LocalActor" iterates over actors created only in the
// current script.  They are the same when "YSI_NO_MASTER" is declared.
// Disabled by declaring "FOREACH_NO_ACTORS".
// 

#define _FOREACH_ACTORS 0

#if defined GetActorPos
	#if !defined FOREACH_NO_ACTORS
		#undef _FOREACH_ACTORS
		#define _FOREACH_ACTORS 1
	#endif
#endif

// 
// _FOREACH_PLAYERS
// 
// Should the "Player" iterator be included?  If "_FOREACH_BOTS" is set, the
// "Player" iterator only loops over human players, "NPC" and "Bot" loop over
// computer players, and "Character" loops over them all.  If "_FOREACH_BOTS" is
// not set, then the "Player" iterator loops over every player in the server,
// the same as "Character" would do otherwise, since it has no way to know if a
// player is human or not.  Disabled by declaring "FOREACH_NO_PLAYERS".
// 

#define _FOREACH_PLAYERS 1

#if defined SendChat || defined FOREACH_NO_PLAYERS
	#undef _FOREACH_PLAYERS
	#define _FOREACH_PLAYERS 0
#endif

// 
// _FOREACH_CHARACTERS
// 
// Bot or Player iterators included.
// 

#define _FOREACH_CHARACTERS (_FOREACH_BOTS || _FOREACH_PLAYERS)

#if !defined BOTSYNC_IS_BOT
	forward Iter_OPDCInternal(playerid);
#endif

#include "..\YSI_Internal\y_natives"
#include "..\YSI_Internal\y_shortfunc"
#include "..\YSI_Internal\y_compilerpass"
#include "..\YSI_Core\y_debug"

#include "y_foreach/impl"
#include "..\YSI_Coding\y_hooks"
#include "..\YSI_Coding\y_remote"
#include "y_foreach/iterators"

#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_foreach/tests"
#endif

