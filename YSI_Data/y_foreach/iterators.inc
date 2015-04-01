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

    88                                                                                  
    88   ,d                                      ,d                                     
    88   88                                      88                                     
    88 MM88MMM ,adPPYba, 8b,dPPYba, ,adPPYYba, MM88MMM ,adPPYba,  8b,dPPYba, ,adPPYba,  
    88   88   a8P_____88 88P'   "Y8 ""     `Y8   88   a8"     "8a 88P'   "Y8 I8[    ""  
    88   88   8PP""""""" 88         ,adPPPPP88   88   8b       d8 88          `"Y8ba,   
    88   88,  "8b,   ,aa 88         88,    ,88   88,  "8a,   ,a8" 88         aa    ]8I  
    88   "Y888 `"Ybbd8"' 88         `"8bbdP"Y8   "Y888 `"YbbdP"'  88         `"YbbdP"'  

*/

/**--------------------------------------------------------------------------**\
Create the internal iterators.
\**--------------------------------------------------------------------------**/

#if !defined BOTSYNC_IS_BOT
	new
		Iterator:Player<MAX_PLAYERS>;
	
	#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
		new
			Iterator:Bot<MAX_PLAYERS>,
			Iterator:Character<MAX_PLAYERS>;
		
		#define Iter_Single@NPC Iter_Single@Bot
		#define Iterator@NPC Iterator@Bot
	#endif
#endif

#define iterstart@Range cellmin

stock iterfunc Range(cur, min, max, step = 1)
{
	if (cur == cellmin) cur = min;
	else cur += step;
	return (min <= cur < max || max <= cur < min) ? cur : cellmin;
}

/*

    88                                                                88  
    88              ,d                                                88  
    88              88                                                88  
    88 8b,dPPYba, MM88MMM ,adPPYba, 8b,dPPYba, 8b,dPPYba,  ,adPPYYba, 88  
    88 88P'   `"8a  88   a8P_____88 88P'   "Y8 88P'   `"8a ""     `Y8 88  
    88 88       88  88   8PP""""""" 88         88       88 ,adPPPPP88 88  
    88 88       88  88,  "8b,   ,aa 88         88       88 88,    ,88 88  
    88 88       88  "Y888 `"Ybbd8"' 88         88       88 `"8bbdP"Y8 88  

*/

/**--------------------------------------------------------------------------**\
	Variables to optimise memory usage by only having one copy of each string.
	Note that only strings used more than once are put here because only they
	have any gain to being located in only one place.
\**--------------------------------------------------------------------------**/

static stock
	YSI_gsOnGameModeInit[] = "Iter_OnGameModeInit",
	YSI_gsSpecifier@[] = "";

/**--------------------------------------------------------------------------**\
<summary>Iter_OPDCInternal</summary>
<param name="playerid">Player who left.</param>
<returns>
	-
</returns>
<remarks>
	Called AFTER "OnPlayerDisconnect" so that using "Kick" inside a "foreach"
	loop doesn't crash the server due to an OOB error.
</remarks>
\**--------------------------------------------------------------------------**/

#if !defined BOTSYNC_IS_BOT
	public Iter_OPDCInternal(playerid)
	{
		if (IsPlayerConnected(playerid))
		{
			return;
		}
		#if defined _FOREACH_BOT
			if (!IsPlayerNPC(playerid))
			{
				Iter_Remove(Player, playerid);
			}
			#if !defined FOREACH_NO_BOTS
				else
				{
					Iter_Remove(Bot, playerid);
				}
				#pragma tabsize 4
				Iter_Remove(Character, playerid);
			#endif
		#else
			Iter_Remove(Player, playerid);
		#endif
	}
#endif

/*

    88        88                         88                   
    88        88                         88                   
    88        88                         88                   
    88aaaaaaaa88  ,adPPYba,   ,adPPYba,  88   ,d8  ,adPPYba,  
    88""""""""88 a8"     "8a a8"     "8a 88 ,a8"   I8[    ""  
    88        88 8b       d8 8b       d8 8888[      `"Y8ba,   
    88        88 "8a,   ,a8" "8a,   ,a8" 88`"Yba,  aa    ]8I  
    88        88  `"YbbdP"'   `"YbbdP"'  88   `Y8a `"YbbdP"'  

*/

/**--------------------------------------------------------------------------**\
<summary>Iter_OnFilterScriptInit</summary>
<returns>
	-
</returns>
<remarks>
	Fixes a bug where callbacks are not detected when "loadfs" is used after the
	GM has already started.  If this is a GM this is just never used called.
</remarks>
\**--------------------------------------------------------------------------**/

#if !defined BOTSYNC_IS_BOT
	public OnFilterScriptInit()
	{
		P:1("Iter_OnFilterScriptInit start: %d", MAX_PLAYERS);
		#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
			Iter_Single@Bot = _Y_ITER_C9:0;
			Iter_Single@Character = _Y_ITER_C9:0;
			new
				lastBot = MAX_PLAYERS,
				lastCharacter = MAX_PLAYERS;
		#endif
		Iter_Single@Player = _Y_ITER_C9:0;
		new
			lastPlayer = MAX_PLAYERS;
		for (new i = 0; i != MAX_PLAYERS; ++i)
		{
			if (IsPlayerConnected(i))
			{
				#if defined _FOREACH_BOT
					// Had to do "if ! else" due to compile options.
					if (!IsPlayerNPC(i))
					{
						Iterator@Player[lastPlayer] = i;
						++Iter_Single@Player;
						lastPlayer = i;
					}
					#if !defined FOREACH_NO_BOTS
						else
						{
							Iterator@Bot[lastBot] = i;
							++Iter_Single@Bot;
							lastBot = i;
						}
						#pragma tabsize 4
						Iterator@Character[lastCharacter] = i;
						++Iter_Single@Character;
						lastCharacter = i;
					#endif
				#else
					Iterator@Player[lastPlayer] = i;
					++Iter_Single@Player;
					lastPlayer = i;
				#endif
			}
			else
			{
				#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
					Iterator@Bot[i] = MAX_PLAYERS + 1;
					Iterator@Character[i] = MAX_PLAYERS + 1;
				#endif
				Iterator@Player[i] = MAX_PLAYERS + 1;
			}
		}
		#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
			Iterator@Bot[lastPlayer] = MAX_PLAYERS;
			Iterator@Character[lastPlayer] = MAX_PLAYERS;
		#endif
		Iterator@Player[lastPlayer] = MAX_PLAYERS;
		#if defined Iter_OnFilterScriptInit
			Iter_OnFilterScriptInit();
		#endif
		return 1;
	}
	
	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit Iter_OnFilterScriptInit
	#if defined Iter_OnFilterScriptInit
		forward Iter_OnFilterScriptInit();
	#endif
#endif

/**--------------------------------------------------------------------------**\
<summary>Iter_OnGameModeInit</summary>
<returns>
	-
</returns>
<remarks>
	There are WIERD bugs in this script, seemingly caused by the compiler, so
	this hopefully fixes them.  The OnFilterScriptInit code is written to be
	very fast by utilising the internal array structure instead of the regular
	Add functions.
</remarks>
\**--------------------------------------------------------------------------**/

#if !defined BOTSYNC_IS_BOT
	public OnGameModeInit()
	{
		P:1("Iter_OnGameModeInit start: %d", MAX_PLAYERS);
		if (!Iter_Single@Player)
		{
			#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
				CallLocalFunction(YSI_gsOnGameModeInit, YSI_gsSpecifier@, Iter_Single@Bot, Iter_Single@Character, Iter_Single@Player);
			#else
				CallLocalFunction(YSI_gsOnGameModeInit, YSI_gsSpecifier@, Iter_Single@Player);
			#endif
			#if defined _YSI_SPECIAL_DEBUG
				for (new i = 0; i != MAX_PLAYERS; ++i)
				{
					Iterator@Player[i] = i + 1;
				}
				Iterator@Player[MAX_PLAYERS] = 0;
				Iter_Single@Player = _Y_ITER_C9:MAX_PLAYERS;
			#endif
			P:1("Iter_OnGameModeInit: first");
			return 1;
		}
		// Do the forward iterator list.
		#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
			Iter_Single@Bot = _Y_ITER_C9:0;
			Iterator@Bot[MAX_PLAYERS] = MAX_PLAYERS;
			Iterator@Character[MAX_PLAYERS] = MAX_PLAYERS;
			Iter_Single@Character = _Y_ITER_C9:0;
			new
				lastBot = MAX_PLAYERS,
				lastCharacter = MAX_PLAYERS;
		#endif
		Iter_Single@Player = _Y_ITER_C9:0;
		Iterator@Player[MAX_PLAYERS] = MAX_PLAYERS;
		new
			lastPlayer = MAX_PLAYERS;
		for (new i = 0; i != MAX_PLAYERS; ++i)
		{
			if (IsPlayerConnected(i))
			{
				#if defined _FOREACH_BOT
					// Had to do "if ! else" due to compile options.
					if (!IsPlayerNPC(i))
					{
						Iterator@Player[lastPlayer] = i;
						++Iter_Single@Player;
						lastPlayer = i;
					}
					#if !defined FOREACH_NO_BOTS
						else
						{
							Iterator@Bot[lastBot] = i;
							++Iter_Single@Bot;
							lastBot = i;
						}
						#pragma tabsize 4
						Iterator@Character[lastCharacter] = i;
						++Iter_Single@Character;
						lastCharacter = i;
					#endif
				#else
					Iterator@Player[lastPlayer] = i;
					++Iter_Single@Player;
					lastPlayer = i;
				#endif
			}
			else
			{
				#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
					Iterator@Bot[i] = MAX_PLAYERS + 1;
					Iterator@Character[i] = MAX_PLAYERS + 1;
				#endif
				Iterator@Player[i] = MAX_PLAYERS + 1;
			}
		}
		#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
			Iterator@Bot[lastPlayer] = MAX_PLAYERS;
			Iterator@Character[lastPlayer] = MAX_PLAYERS;
		#endif
		Iterator@Player[lastPlayer] = MAX_PLAYERS;
		P:1("Iter_OnGameModeInit: lastplayer = %d", lastPlayer);
		CallLocalFunction(YSI_gsOnGameModeInit, YSI_gsSpecifier@);
		#if defined _YSI_SPECIAL_DEBUG
			for (new i = 0; i != MAX_PLAYERS; ++i)
			{
				Iterator@Player[i] = i + 1;
			}
			Iterator@Player[MAX_PLAYERS] = 0;
			Iter_Single@Player = _Y_ITER_C9:MAX_PLAYERS;
		#endif
		return 1;
	}
	
	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit Iter_OnGameModeInit
	#if defined Iter_OnGameModeInit
		forward Iter_OnGameModeInit();
	#endif
#endif

/*

    88888888ba  88                                                         
    88      "8b 88                                                         
    88      ,8P 88                                                         
    88aaaaaa8P' 88 ,adPPYYba, 8b       d8  ,adPPYba, 8b,dPPYba, ,adPPYba,  
    88""""""'   88 ""     `Y8 `8b     d8' a8P_____88 88P'   "Y8 I8[    ""  
    88          88 ,adPPPPP88  `8b   d8'  8PP""""""" 88          `"Y8ba,   
    88          88 88,    ,88   `8b,d8'   "8b,   ,aa 88         aa    ]8I  
    88          88 `"8bbdP"Y8     Y88'     `"Ybbd8"' 88         `"YbbdP"'  
                                  d8'                                      
                                 d8'                                       

*/

/**--------------------------------------------------------------------------**\
<summary>Iter_OnPlayerConnect</summary>
<param name="playerid">Player who joined.</param>
<returns>
	-
</returns>
<remarks>
	Adds a player to the loop data.  Now sorts the list too.  Note that I found
	the most bizzare bug ever (I *think* it may be a compiler but, but it
	requires further investigation), basically it seems that multiple variables
	were being treated as the same variable (namely @YSII_EgotS and
	@YSII_CgharacterS were the same and @YSII_EgotC and @YSII_CgharacterC were the
	same).  Adding print statements which reference these variables seem to fix
	the problem, and I've tried to make sure that the values will never actually
	get printed.
</remarks>
\**--------------------------------------------------------------------------**/

#if !defined BOTSYNC_IS_BOT
	public OnPlayerConnect(playerid)
	{
		P:1("Iter_OnPlayerConnect called: %d, %d", playerid, IsPlayerNPC(playerid));
		#if defined _FOREACH_BOT
			if (!IsPlayerNPC(playerid))
			{
				Iter_Add(Player, playerid);
			}
			#if !defined FOREACH_NO_BOTS
				else
				{
					Iter_Add(Bot, playerid);
				}
				#pragma tabsize 4
				Iter_Add(Character, playerid);
			#endif
		#else
			Iter_Add(Player, playerid);
		#endif
		P:2("Iter_OnPlayerConnect end");
		#if defined Iter_OnPlayerConnect
			Iter_OnPlayerConnect(playerid);
		#endif
		return 1;
	}
	
	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif
	#define OnPlayerConnect Iter_OnPlayerConnect
	#if defined Iter_OnPlayerConnect
		forward Iter_OnPlayerConnect(playerid);
	#endif
#endif

/**--------------------------------------------------------------------------**\
<summary>Iter_OnPlayerDisconnect</summary>
<param name="playerid">Player who left.</param>
<returns>
	-
</returns>
<remarks>
	Removes a player from the loop data.  No longer uses "hook" to ENSURE that
	this is always last.  Previously I think that the order of evaluation in
	y_hooks meant that this got called before the user "OnPlayerDisconnect".
</remarks>
\**--------------------------------------------------------------------------**/

#if !defined BOTSYNC_IS_BOT
	public OnPlayerDisconnect(playerid, reason)
	{
		SetTimerEx("Iter_OPDCInternal", 0, false, "i", playerid);
		#if defined Iter_OnPlayerDisconnect
			Iter_OnPlayerDisconnect(playerid, reason);
		#endif
		return 1;
	}
	
	#if defined _ALS_OnPlayerDisconnect
		#undef OnPlayerDisconnect
	#else
		#define _ALS_OnPlayerDisconnect
	#endif
	#define OnPlayerDisconnect Iter_OnPlayerDisconnect
	#if defined Iter_OnPlayerDisconnect
		forward Iter_OnPlayerDisconnect(playerid, reason);
	#endif
#endif

