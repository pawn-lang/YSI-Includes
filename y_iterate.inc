/*----------------------------------------------------------------------------*\
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
		Added Itter_Func2 functions for multi-dimensional iterators.
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
		Itter_ShowArray - Displays the contents of the array.
		Itter_AddInternal - Add a value to an itterator.
		Itter_RemoveInternal - Remove a value from an itterator.
		Itter_RandomInternal - Get a random item from an itterator.
		Itter_FreeInternal - Gets the first free slot in the itterator.
		Itter_InitInternal - Initialises a multi-dimensional itterator.
	Static:
		-
	Inline:
		Itter_Create - Create a new itterator value set.
		Itter_Add - Wraps Itter_AddInternal.
		Itter_Remove - Wraps Itter_RemoveInternal.
		Itter_Random - Wraps Itter_RandomInternal.
		Itter_Count - Gets the number of items in an itterator.
		Itter_Debug - Wraps around Itter_ShowArray.
		Itter_Free - Wraps around Itter_FreeInternal.
		Itter_Create2 - Create a new itterator array value set.
		Itter_Add2 - Wraps Itter_AddInternal for arrays.
		Itter_Remove2 - Wraps Itter_RemoveInternal for arrays.
		Itter_Random2 - Wraps Itter_RandomInternal for arrays.
		Itter_Count2 - Gets the number of items in an itterator array.
		Itter_Debug2 - Wraps around Itter_ShowArray for arrays.
		Itter_Free2 - Wraps around Itter_FreeInternal for arrays.
	API:
		-
Callbacks:
	-
Hooks:
	Itter_OnPlayerConnect - Hook for the OnPlayerConnect callback.
	Itter_OnPlayerDisconnect - Hook for the OnPlayerDisconnect callback.
	Itter_OnGameModeInit - Only exists to make the code compile correctly...
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
		YSI_g_OPC - Records wether Itter_OnPlayerConnect exists for speed.
		YSI_g_OPDC - Records wether Itter_OnPlayerDisconnect exists for speed.
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
\*----------------------------------------------------------------------------*/

// "y_iterate" is always higher than "foreach".
#define _Y_ITERATE_LOCAL_VERSION        20

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
	#if defined _inc_foreach
		#if !defined _FOREACH_CUR_VERSION
			// Foreach exists, but it's an old version - don't try use this
			// system or the variables will conflict.
			#error "Old foreach.inc files are no longer compatible with YSI."
			#endinput
		#endif
		#if _FOREACH_CUR_VERSION > _Y_ITERATE_LOCAL_VERSION
			// Foreach is newer.
			#undef _inc_foreach
			#define _FOREACH_NO_TEST
			#include <foreach>
			#endinput
		#endif
	#endif
#endif

#if !defined _samp_included
	#error "Please include a_samp or a_npc before foreach"
#endif

#if defined _YSI_SPECIAL_DEBUG
	#define PS_IS_PLAYER_CONNECTED(%0) (%0 != INVALID_PLAYER_ID)
#else
	#define PS_IS_PLAYER_CONNECTED IsPlayerConnected
#endif

//#include "y_debug"
//#include "y_hooks"

#include "internal\y_natives"
#include "y_debug"
//#include "y_als"

#if defined SendChat || defined FOREACH_NO_PLAYERS
	#define BOTSYNC_IS_BOT     (true)
#endif

#if defined IsPlayerNPC
	#define _FOREACH_BOT
#endif

#if defined YSI_ITTER_NO_SORT
	#error YSI_ITTER_NO_SORT is no longer supported by foreach.
#endif

#define _Y_ITER_ARRAY: _:_Y_ITER_C0:
#define _Y_ITER_ARRAY_SIZE(%1) _:_Y_ITER_C1:_Y_ITER_C2:sizeof %1@YSII_Ag-1

#define _Y_ITER_C0:%0[%1]@YSII_%4g%3) %0@YSII_%4g[%1]%3)
#define _Y_ITER_C1:_Y_ITER_C2:%0[%1]@YSII_Ag%3) %0@YSII_Ag[]%3)
#define _Y_ITER_C2:sizeof%0(%1)@YSII_Ag-1;_:(%2=_Y_ITER_ARRAY:%3(%4)@YSII_Ag[%5])!=%9_Y_ITER_ARRAY_SIZE(%6);) -1;_:(%2=%3@YSII_Ag(%4,%5))!=-1;)

#define _Y_ITER_C3:%0[%1]@YSII_Cg,%2[%3]@YSII_Ag[%4]={%5} _Y_ITER_C3:%0@YSII_Cg[%4-1],%0@YSII_Ag[%1][%4]

//#if !defined BOTSYNC_IS_BOT
//	static stock
//		YSI_g_sCallbacks = 0;
//#endif

#if !defined BOTSYNC_IS_BOT
	forward Itter_OPDCInternal(playerid);
#endif

/*----------------------------------------------------------------------------*\
Function:
	Itter_Create2
Params:
	name - Itterator identifier.
	size0 - Number of iterators.
	size1 - Number of items per iterator.
Return:
	-
Notes:
	Creates a new array of itterator start/array pair.
\*----------------------------------------------------------------------------*/

// If this ever changes, update the size reference in y_users.
/*#define Iter_Create2 Itter_Create2
#define Itter_Create2(%1,%2,%3) \
	new \
		%1@YSII_Sg[%2] = {-1, ...}, \
		%1@YSII_Cg[%2] = {0}, \
		%1@YSII_Ag[%2][%3]*/

#define IteratorArray:%1[%2]<%3> %1@YSII_Cg[%2],%1@YSII_Ag[%2][%3+1]//,%1@YSII_Rg[%2][%3+1]

/*----------------------------------------------------------------------------*\
Array:
	Iterator
Notes:
	Creates a new itterator start/array pair.
\*----------------------------------------------------------------------------*/

#define Iterator:%1<%2> _Y_ITER_C3:%1@YSII_Cg,%1@YSII_Ag[(%2)+1]={(%2)*2,(%2)*2-1,...}
#define iterator%0<%1> Iterator:%0<%1>

/*----------------------------------------------------------------------------*\
Function:
	Itter_Init2
Params:
	itter - Name of the itterator array to initialise.
Return:
	-
Notes:
	Wrapper for Itter_InitInternal.

native Iter_Init(IteratorArray:Name[]<>);

\*----------------------------------------------------------------------------*/

#define Iter_Init Itter_Init
#define Itter_Init(%1) \
	Itter_InitInternal(%1@YSII_Ag,sizeof %1@YSII_Ag,sizeof %1@YSII_Ag[]-1)

/*----------------------------------------------------------------------------*\
Function:
	Itter_Create
Params:
	name - Itterator identifier.
	size - Number of values.
Return:
	-
Notes:
	Creates a new itterator start/array pair.
\*----------------------------------------------------------------------------*/

// If this ever changes, update the size reference in y_users.
/*#define Iter_Create Itter_Create
#define Itter_Create(%1,%2) \
	new \
		%1@YSII_Sg = -1, \
		%1@YSII_Cg = 0, \
		%1@YSII_Ag[%2] = {-1, ...}*/

/*----------------------------------------------------------------------------*\
Function:
	Itter_Add
Params:
	itter - Name of the itterator to add the data to.
	value - Value to add to the itterator.
Return:
	-
Notes:
	Wrapper for Itter_AddInternal.

native Iter_Add(Iterator:Name<>, value);

\*----------------------------------------------------------------------------*/

#define Iter_Add Itter_Add
#define Itter_Add(%1,%2) Itter_AddInternal(_Y_ITER_ARRAY:%1@YSII_Cg,_Y_ITER_ARRAY:%1@YSII_Ag,%2,_Y_ITER_ARRAY_SIZE(%1))

/*#define Iter_AddSafe Itter_AddSafe
#define Itter_AddSafe(%1,%2) \
	Itter_AddSafeInternal(%1@YSII_Sg, %1@YSII_Cg, %1@YSII_Ag, %1@YSII_Rg, %2)*/

/*----------------------------------------------------------------------------*\
Function:
	Itter_Free
Params:
	itter - Name of the itterator to get the first free slot in.
Return:
	-
Notes:
	Wrapper for Itter_FreeInternal.

native Iter_Free(Iterator:Name<>);

\*----------------------------------------------------------------------------*/

#define Iter_Free Itter_Free
#define Itter_Free(%1) Itter_FreeInternal(_Y_ITER_ARRAY:%1@YSII_Ag,_Y_ITER_ARRAY_SIZE(%1))

/*----------------------------------------------------------------------------*\
Function:
	Itter_Remove
Params:
	itter - Name of the itterator to remove data from.
	value - Data to remove.
Return:
	-
Notes:
	Wrapper for Itter_RemoveInternal.

native Iter_Remove(Iterator:Name<>, value);

\*----------------------------------------------------------------------------*/

#define Iter_Remove Itter_Remove
#define Itter_Remove(%1,%2) Itter_RemoveInternal(_Y_ITER_ARRAY:%1@YSII_Cg,_Y_ITER_ARRAY:%1@YSII_Ag,%2,_Y_ITER_ARRAY_SIZE(%1))

/*----------------------------------------------------------------------------*\
Function:
	Itter_Contains
Params:
	itter - Name of the itterator to check membership of.
	value - Value to check.
Return:
	-
Notes:
	Checks if the given value is in the given iterator.

native Iter_Remove(Iterator:Name<>, value);

\*----------------------------------------------------------------------------*/

#define Iter_Contains Itter_Contains
#define Itter_Contains(%1,%2) Itter_ContainsInternal(_Y_ITER_ARRAY:%1@YSII_Ag,%2,_Y_ITER_ARRAY_SIZE(%1))

/*----------------------------------------------------------------------------*\
Function:
	Itter_SafeRemove
Params:
	itter - Name of the itterator to remove data from.
	value - Data to remove.
	next - Container for the pointer to the next element.
Return:
	-
Notes:
	Wrapper for Itter_SafeRemoveInternal.  Common use:
	
	Iter_SafeRemove(iter, i, i);

native Iter_SafeRemove(Iterator:Name<>, value, &next);

\*----------------------------------------------------------------------------*/

#define Iter_SafeRemove Itter_SafeRemove
#define Itter_SafeRemove(%1,%2,%3) Itter_SafeRemoveInternal(_Y_ITER_ARRAY:%1@YSII_Cg,_Y_ITER_ARRAY:%1@YSII_Ag,%2,%3,_Y_ITER_ARRAY_SIZE(%1))

/*----------------------------------------------------------------------------*\
Function:
	Itter_Random
Params:
	itter - Name of the itterator to get a random slot from.
Return:
	-
Notes:
	Wrapper for Itter_RandomInternal.

native Iter_Random(Iterator:Name<>);

\*----------------------------------------------------------------------------*/

#define Iter_Random Itter_Random
#define Itter_Random(%1) Itter_RandomInternal(_Y_ITER_ARRAY:%1@YSII_Cg,_Y_ITER_ARRAY:%1@YSII_Ag,_Y_ITER_ARRAY_SIZE(%1))

/*----------------------------------------------------------------------------*\
Function:
	Itter_Debug
Params:
	itter - Name of the itterator to output debug information from.
Return:
	-
Notes:
	Wrapper for Itter_ShowArray.
\*----------------------------------------------------------------------------*/

//#define Iter_Debug Itter_Debug
//#define Itter_Debug(%1) Itter_ShowArray(_Y_ITER_ARRAY:%1@YSII_Cg,_Y_ITER_ARRAY:%1@YSII_Ag)

/*----------------------------------------------------------------------------*\
Function:
	Itter_Count
Params:
	itter - Name of the itterator to get a random slot from4.
Return:
	-
Notes:
	Returns the number of items in this itterator.

native Iter_Count(Iterator:Name<>);

\*----------------------------------------------------------------------------*/

#define Iter_Count Itter_Count
#define Itter_Count(%1) (_Y_ITER_ARRAY:%1@YSII_Cg)

/*----------------------------------------------------------------------------*\
Function:
	Itter_Clear
Params:
	itter - Name of the itterator empty.
Return:
	-
Notes:
	Wrapper for Itter_ClearInternal.

native Iter_Clear(IteratorArray:Name[]<>);

\*----------------------------------------------------------------------------*/

#define Iter_Clear Itter_Clear
#define Itter_Clear(%1) Itter_ClearInternal(_Y_ITER_ARRAY:%1@YSII_Cg,_Y_ITER_ARRAY:%1@YSII_Ag,_Y_ITER_ARRAY_SIZE(%1))

/*----------------------------------------------------------------------------*\
Create the internal itterators.
\*----------------------------------------------------------------------------*/

#if !defined BOTSYNC_IS_BOT
	new
		Iterator:Player<MAX_PLAYERS>;
	
	#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
		new
			Iterator:Bot<MAX_PLAYERS>,
			Iterator:Character<MAX_PLAYERS>;
		
		//#define NPC@YSII_Sg Bot@YSII_Sg
		#define NPC@YSII_Cg Bot@YSII_Cg
		#define NPC@YSII_Ag Bot@YSII_Ag
		//#define NPC@YSII_Eg Bot@YSII_Eg
		//#define NPC@YSII_Rg Bot@YSII_Rg
	#endif
#endif

/*----------------------------------------------------------------------------*\
	Variables to optimise memory usage by only having one copy of each string.
	Note that only strings used more than once are put here because only they
	have any gain to being located in only one place.
\*----------------------------------------------------------------------------*/

static stock
	YSI_gsOnGameModeInit[] = "Itter_OnGameModeInit",
	YSI_gsSpecifier@[] = "";
/*	YSI_gsOnPlayerConnect[] = "Itter_OnPlayerConnect",
	YSI_gsOnPlayerDisconnect[] = "Itter_OnPlayerDisconnect",
	YSI_gsOnGameModeInit[] = "Itter_OnGameModeInit",
	YSI_gsSpecifier@i[] = "i",
	YSI_gsSpecifier@[] = "";*/

/*----------------------------------------------------------------------------*\
Function:
	foreach
Params:
	data - Data to itterate through.
	as - Variable to set value to.
Return:
	-
Notes:
	Not exactly the same as PHP foreach, just itterates through a list and
	returns the value of the current slot but uses that slot as the next index
	too.  Variables must be in the form @YSII_<gname>S for the start index and
	@YSII_<gname>A for the data array where <name> is what's entered in data.
\*----------------------------------------------------------------------------*/

//#define foreach(%1,%2)
//	for (new %2 = %1@YSII_Sg; _:%2 != -1; %2 = %1@YSII_Ag[%2])
#define foreach%1(%0) for(new Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||%0|||)
// This allows us to use "new" multiple times - stripping off ONLY whole words.
#define new%0|||%9|||%1:%2||| %9|||%0|||%1|||%2|||

// This one is called if the new syntax is required, but the state of "new" is
// as-yet unknown.  This attempts to call "%1" as a macro, if it starts with
// "new" as a whole word then it will (and will also helpfully strip off the
// "new" keyword for us).
#define Y_FOREACH_THIRD|||%0|||%1|||%2||| %1=Y_FOREACH_FIFTH|||Y_FOREACH_FOURTH|||%1:%2|||

// This is called if the "new" macro is called for a second time.
#define Y_FOREACH_FOURTH|||%0=Y_FOREACH_FIFTH|||%1|||%2||| new Y_FOREACH_SIXTH;%0|||Y_FOREACH_SEVENTH|||%2|||

// This is called when there are tags on the "new" declaration.
#define Y_FOREACH_SEVENTH|||%9Y_FOREACH_SIXTH;%0|||%1|||%2||| new %0:%1=%0:_Y_ITER_ARRAY_SIZE(%2);_:(%1=_Y_ITER_ARRAY:%2@YSII_Ag[%1])!=%0:_Y_ITER_ARRAY_SIZE(%2);

// This is called when there aren't.
#define Y_FOREACH_SIXTH;%0|||Y_FOREACH_SEVENTH|||%2||| %0=_Y_ITER_ARRAY_SIZE(%2);_:(%0=_Y_ITER_ARRAY:%2@YSII_Ag[%0])!=_Y_ITER_ARRAY_SIZE(%2);
//hta:%0=hta:%2@YSII_Sg;_:%0!=-1;%0=hta:%2@YSII_Ag[%0]
//#define Y_FOREACH_FOURTH|||%0=Y_FOREACH_FIFTH|||%1|||%2||| new hta:%0=hta:%2@YSII_Sg;_:%0!=-1;%0=hta:%2@YSII_Ag[%0]

// Move any tags from the second half to the first half.
//#define hta:%0=hta:%1:%2;_:%3!=-1;%4=hta:%5:%6[%7] %0:%1=%2;_:%1!=-1;%1=%6[%1]

// This is called if "%1" didn't have "new" at the start.
#define Y_FOREACH_FIFTH|||Y_FOREACH_FOURTH|||%1:%2||| _Y_ITER_ARRAY_SIZE(%2);_:(%1=_Y_ITER_ARRAY:%2@YSII_Ag[%1])!=_Y_ITER_ARRAY_SIZE(%2);

//%1=%2@YSII_Sg;_:Y_FOREACH_NONEW:%1!=-1;%1=%2@YSII_Ag[%1]
// This is the old version, but DON'T add "new" because that already exists from
// the failed "new" macro call above.
#define Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||%1,%2||| %2=_Y_ITER_ARRAY_SIZE(%1);_:(%2=_Y_ITER_ARRAY:%1@YSII_Ag[%2])!=_Y_ITER_ARRAY_SIZE(%1);
//#define Y_FOREACH_NONEW:new%0!=-1;new%1=%2[new%3] %0!=-1;%1=%2[%3]

//#define Y_FOREACH_EIGHTH:%0[%1]@YSII_Sg;%2;%3=%4[%5]@YSII_Ag[%6] %0@YSII_Sg[%1];%2;%3=%4@YSII_Ag[%5][%6]

/*----------------------------------------------------------------------------*\
Function:
	foreachex
Params:
	data - Data to itterate through.
	as - Variable to set value to.
Return:
	-
Notes:
	Similar to foreach but doesn't declare a new variable for the itterator.
\*----------------------------------------------------------------------------*/

#define foreachex(%1,%2) foreach(%2:%1)
	//for (%2=_Y_ITER_ARRAY_SIZE(%1);(%2=_Y_ITER_ARRAY:%1@YSII_Ag[%2])!=_Y_ITER_ARRAY_SIZE(%1);)

/*----------------------------------------------------------------------------*\
Function:
	Itter_OnPlayerConnect
Params:
	playerid - Player who joined.
Return:
	-
Notes:
	Adds a player to the loop data.  Now sorts the list too.  Note that I found
	the most bizzare bug ever (I *think* it may be a compiler but, but it
	requires further investigation), basically it seems that multiple variables
	were being treated as the same variable (namely @YSII_EgotS and
	@YSII_CgharacterS were the same and @YSII_EgotC and @YSII_CgharacterC were the
	same).  Adding print statements which reference these variables seem to fix
	the problem, and I've tried to make sure that the values will never actually
	get printed.
\*----------------------------------------------------------------------------*/

#if !defined BOTSYNC_IS_BOT
	public OnPlayerConnect(playerid)
	{
		P:2("Iter_OnPlayerConnect: %d", playerid);
		#if defined _FOREACH_BOT
			if (!IsPlayerNPC(playerid))
			{
				Itter_Add(Player, playerid);
			}
			#if !defined FOREACH_NO_BOTS
				else
				{
					Itter_Add(Bot, playerid);
				}
				#pragma tabsize 4
				Itter_Add(Character, playerid);
			#endif
		#else
			Itter_Add(Player, playerid);
		#endif
		//if (YSI_g_sCallbacks & 2)
		//{
		//	CallLocalFunction(YSI_gsOnPlayerConnect, YSI_gsSpecifier@i, playerid);
		//}
		Itter_OnPlayerConnect(playerid);
		P:2("Iter_OnPlayerConnect end");
		return 1;
	}
	
	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif
	#define OnPlayerConnect(%0) Itter_OnPlayerConnect(%0) <_ALS_:hooked>
	forward Itter_OnPlayerConnect(playerid);public Itter_OnPlayerConnect(playerid)<_ALS_:unhooked>{return 1;}public Itter_OnPlayerConnect(playerid)<>{return 1;}
#endif

/*----------------------------------------------------------------------------*\
Function:
	Itter_OnFilterScriptInit
Params:
	-
Return:
	-
Notes:
	Fixes a bug where callbacks are not detected when "loadfs" is used after the
	GM has already started.  If this is a GM this is just never used called.
\*----------------------------------------------------------------------------*/

#if !defined BOTSYNC_IS_BOT
	public OnFilterScriptInit()
	{
		P:0("Iter_OnFilterScriptInit start: %d", MAX_PLAYERS);
		//if (funcidx(YSI_gsOnPlayerDisconnect) != -1)
		//{
		//	YSI_g_sCallbacks |= 1;
		//}
		//if (funcidx(YSI_gsOnPlayerConnect) != -1)
		//{
		//	YSI_g_sCallbacks |= 2;
		//}
		#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
			Bot@YSII_Cg = _Y_ITER_C3:0;
			Character@YSII_Cg = _Y_ITER_C3:0;
			new
				lastBot = MAX_PLAYERS,
				lastCharacter = MAX_PLAYERS;
		#endif
		Player@YSII_Cg = _Y_ITER_C3:0;
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
						Player@YSII_Ag[lastPlayer] = i;
						++Player@YSII_Cg;
						lastPlayer = i;
					}
					#if !defined FOREACH_NO_BOTS
						else
						{
							Bot@YSII_Ag[lastBot] = i;
							++Bot@YSII_Cg;
							lastBot = i;
						}
						#pragma tabsize 4
						Character@YSII_Ag[lastCharacter] = i;
						++Character@YSII_Cg;
						lastCharacter = i;
					#endif
				#else
					Player@YSII_Ag[lastPlayer] = i;
					++Player@YSII_Cg;
					lastPlayer = i;
				#endif
			}
			else
			{
				#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
					Bot@YSII_Ag[i] = MAX_PLAYERS + 1;
					//Bot@YSII_Rg[i] = -1;
					Character@YSII_Ag[i] = MAX_PLAYERS + 1;
					//Character@YSII_Rg[i] = -1;
				#endif
				Player@YSII_Ag[i] = MAX_PLAYERS + 1;
				//Player@YSII_Rg[i] = -1;
			}
		}
		#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
			Bot@YSII_Ag[lastPlayer] = MAX_PLAYERS;
			Character@YSII_Ag[lastPlayer] = MAX_PLAYERS;
		#endif
		Player@YSII_Ag[lastPlayer] = MAX_PLAYERS;
		//CallLocalFunction("Itter_OnFilterScriptInit", YSI_gsSpecifier@);
		Itter_OnFilterScriptInit();
		P:0("Iter_OnFilterScriptInit end");
		return 1;
	}
	
	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit(%0) Itter_OnFilterScriptInit(%0) <_ALS_:hooked>
	forward Itter_OnFilterScriptInit();public Itter_OnFilterScriptInit()<_ALS_:unhooked>{return 1;}public Itter_OnFilterScriptInit()<>{return 1;}
#endif

/*----------------------------------------------------------------------------*\
Function:
	Itter_OnGameModeInit
Params:
	-
Return:
	-
Notes:
	There are WIERD bugs in this script, seemingly caused by the compiler, so
	this hopefully fixes them.  The OnFilterScriptInit code is written to be
	very fast by utilising the internal array structure instead of the regular
	Add functions.
\*----------------------------------------------------------------------------*/

#if !defined BOTSYNC_IS_BOT
	public OnGameModeInit()
	{
		P:0("Iter_OnGameModeInit start: %d", MAX_PLAYERS);
		// Clear everything.
		//if (funcidx(YSI_gsOnPlayerDisconnect) != -1)
		//{
		//	YSI_g_sCallbacks |= 1;
		//}
		//if (funcidx(YSI_gsOnPlayerConnect) != -1)
		//{
		//	YSI_g_sCallbacks |= 2;
		//}
		if (!Player@YSII_Cg)
		{
			#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
				CallLocalFunction(YSI_gsOnGameModeInit, YSI_gsSpecifier@, Bot@YSII_Cg, Character@YSII_Cg, Player@YSII_Cg);
			#else
				CallLocalFunction(YSI_gsOnGameModeInit, YSI_gsSpecifier@, Player@YSII_Cg);
			#endif
			#if defined _YSI_SPECIAL_DEBUG
				for (new i = 0; i != MAX_PLAYERS; ++i)
				{
					Player@YSII_Ag[i] = i + 1;
				}
				Player@YSII_Ag[MAX_PLAYERS] = 0;
				Player@YSII_Cg = _Y_ITER_C3:MAX_PLAYERS;
			#endif
			P:0("Iter_OnGameModeInit: first");
			return 1;
		}
		// Do the forward iterator list.
		#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
			Bot@YSII_Cg = _Y_ITER_C3:0;
			Bot@YSII_Ag[MAX_PLAYERS] = MAX_PLAYERS;
			Character@YSII_Ag[MAX_PLAYERS] = MAX_PLAYERS;
			Character@YSII_Cg = _Y_ITER_C3:0;
			new
				lastBot = MAX_PLAYERS,
				lastCharacter = MAX_PLAYERS;
		#endif
		Player@YSII_Cg = _Y_ITER_C3:0;
		Player@YSII_Ag[MAX_PLAYERS] = MAX_PLAYERS;
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
						Player@YSII_Ag[lastPlayer] = i;
						++Player@YSII_Cg;
						lastPlayer = i;
					}
					#if !defined FOREACH_NO_BOTS
						else
						{
							Bot@YSII_Ag[lastBot] = i;
							++Bot@YSII_Cg;
							lastBot = i;
						}
						#pragma tabsize 4
						Character@YSII_Ag[lastCharacter] = i;
						++Character@YSII_Cg;
						lastCharacter = i;
					#endif
				#else
					Player@YSII_Ag[lastPlayer] = i;
					++Player@YSII_Cg;
					lastPlayer = i;
				#endif
			}
			else
			{
				#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
					Bot@YSII_Ag[i] = MAX_PLAYERS + 1;
					//Bot@YSII_Rg[i] = -1;
					Character@YSII_Ag[i] = MAX_PLAYERS + 1;
					//Character@YSII_Rg[i] = -1;
				#endif
				Player@YSII_Ag[i] = MAX_PLAYERS + 1;
				//Player@YSII_Rg[i] = -1;
			}
		}
		#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
			Bot@YSII_Ag[lastPlayer] = MAX_PLAYERS;
			Character@YSII_Ag[lastPlayer] = MAX_PLAYERS;
		#endif
		Player@YSII_Ag[lastPlayer] = MAX_PLAYERS;
		P:0("Iter_OnGameModeInit: lastplayer = %d", lastPlayer);
		CallLocalFunction(YSI_gsOnGameModeInit, YSI_gsSpecifier@);
		#if defined _YSI_SPECIAL_DEBUG
			for (new i = 0; i != MAX_PLAYERS; ++i)
			{
				Player@YSII_Ag[i] = i + 1;
			}
			Player@YSII_Ag[MAX_PLAYERS] = 0;
			Player@YSII_Cg = _Y_ITER_C3:MAX_PLAYERS;
		#endif
		return 1;
	}
	
	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	//#define OnGameModeInit(%0) Itter_OnGameModeInit(%0) <_ALS_:hooked>
	//forward Itter_OnGameModeInit();public Itter_OnGameModeInit()<_ALS_:unhooked>{return 1;}public Itter_OnGameModeInit()<>{return 1;}
	#define OnGameModeInit Itter_OnGameModeInit
	forward Itter_OnGameModeInit();
#endif

/*----------------------------------------------------------------------------*\
Function:
	Itter_OnPlayerDisconnect
Params:
	playerid - Player who left.
Return:
	-
Notes:
	Removes a player from the loop data.  No longer uses "hook" to ENSURE that
	this is always last.  Previously I think that the order of evaluation in
	y_hooks meant that this got called before the user "OnPlayerDisconnect".
\*----------------------------------------------------------------------------*/

#if !defined BOTSYNC_IS_BOT
	public OnPlayerDisconnect(playerid, reason)
	{
		//if (YSI_g_sCallbacks & 1)
		//{
		//	CallLocalFunction(YSI_gsOnPlayerDisconnect, "ii", playerid, reason);
		//}
		Itter_OnPlayerDisconnect(playerid, reason);
		SetTimerEx("Itter_OPDCInternal", 0, false, "i", playerid);
		return 1;
	}
	
	#if defined _ALS_OnPlayerDisconnect
		#undef OnPlayerDisconnect
	#else
		#define _ALS_OnPlayerDisconnect
	#endif
	#define OnPlayerDisconnect(%0) Itter_OnPlayerDisconnect(%0) <_ALS_:hooked>
	forward Itter_OnPlayerDisconnect(playerid, reason);public Itter_OnPlayerDisconnect(playerid, reason)<_ALS_:unhooked>{return 1;}public Itter_OnPlayerDisconnect(playerid, reason)<>{return 1;}
#endif

/*----------------------------------------------------------------------------*\
Function:
	Itter_OPDCInternal
Params:
	playerid - Player who left.
Return:
	-
Notes:
	Called AFTER "OnPlayerDisconnect" so that using "Kick" inside a "foreach"
	loop doesn't crash the server due to an OOB error.
\*----------------------------------------------------------------------------*/

#if !defined BOTSYNC_IS_BOT
	public Itter_OPDCInternal(playerid)
	{
		if (IsPlayerConnected(playerid))
		{
			return;
		}
		#if defined _FOREACH_BOT
			if (!IsPlayerNPC(playerid))
			{
				Itter_Remove(Player, playerid);
			}
			#if !defined FOREACH_NO_BOTS
				else
				{
					Itter_Remove(Bot, playerid);
				}
				#pragma tabsize 4
				Itter_Remove(Character, playerid);
			#endif
		#else
			Itter_Remove(Player, playerid);
		#endif
	}
#endif

/*----------------------------------------------------------------------------*\
Function:
	Itter_ShowArray
Params:
	start - Itterator start point.
	members[] - Itterator contents.
	size - Number of itterator values
Return:
	-
Notes:
	Pure debug function.  Has regular prints not debug prints
	as it's only called when debug is on.
\*----------------------------------------------------------------------------*/

/*stock
	Itter_ShowArray(size, members[])
{
	static
		sString[61];
	new
		i,
		j = 10;
	printf("Start: %d", start);
	printf("Size:  %d", size);
	while (i < size)
	{
		sString[0] = '\0';
		while (i < j && i < size)
		{
			format(sString, sizeof (sString), "%s, %d", sString, members[i]);
			i++;
		}
		printf("Array (%d): %s", j, sString);
		j += 10;
	}
}*/

/*----------------------------------------------------------------------------*\
Function:
	Itter_RandomInternal
Params:
	count - Number of items in the itterator.
	array[] - Itterator data.
	size - Size of the iterator.
Return:
	-
Notes:
	Returns a random value from an iterator.
\*----------------------------------------------------------------------------*/

stock
	Itter_RandomInternal(count, array[], size)
{
	if (count == 0)
	{
		return -1;
	}
	new
		rnd = random(count),
		cur = array[size];
	while (cur != size)
	{
		if (rnd-- == 0)
		{
			return cur;
		}
		cur = array[cur];
	}
	return -1;
}

/*----------------------------------------------------------------------------*\
Function:
	Itter_FreeInternal
Params:
	count - Number of items in the itterator.
	array[] - Itterator data.
	size - Size of the itterator.
Return:
	-
Notes:
	Finds the first free slot in the itterator.  Itterators now HAVE to be
	sorted for this function to work correctly as it uses that fact to decide
	wether a slot is unused or the last one.  If you want to use the slot
	straight after finding it the itterator will need to re-find it to add in
	the data.
\*----------------------------------------------------------------------------*/

stock
	Itter_FreeInternal(array[], size)
{
	for (new i = 0; i != size; ++i)
	{
		if (array[i] > size)
		{
			return i;
		}
	}
	return -1;
}

/*----------------------------------------------------------------------------*\
Function:
	Itter_AddInternal
Params:
	&start - Array start index.
	&count - Number of items in the itterator.
	array[] - Itterator data.
	value - Item to add.
Return:
	-
Notes:
	Adds a value to a given itterator set.  Now detects when you try and add the
	last item multiple times, as well as all the other items.  Now simplified even
	further with the new internal representation.
\*----------------------------------------------------------------------------*/

stock
	Itter_AddInternal(&count, array[], value, size)
{
	if (0 <= value < size && array[value] > size)
	{
		new
			last = size,
			next = array[last];
		while (next < value)
		{
			last = next;
			next = array[last];
		}
		array[last] = value;
		array[value] = next;
		++count;
		return 1;
	}
	return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	Itter_RemoveInternal
Params:
	&count - Number of items in the itterator.
	array[] - Itterator data.
	value - Item to remove.
Return:
	-
Notes:
	Removes a value from an itterator.
\*----------------------------------------------------------------------------*/

stock
	Itter_RemoveInternal(&count, array[], value, size)
{
	new
		last;
	return Itter_SafeRemoveInternal(count, array, value, last, size);
}

/*----------------------------------------------------------------------------*\
Function:
	Itter_SafeRemoveInternal
Params:
	&count - Number of items in the itterator.
	array[] - Iterator data.
	back[] - Reverse iterator data.
	value - Item to remove.
	&last - Pointer in which to store the last pointer.
Return:
	-
Notes:
	Removes a value from an itterator safely.
\*----------------------------------------------------------------------------*/

stock
	Itter_SafeRemoveInternal(&count, array[], value, &last, size)
{
	if (0 <= value < size && array[value] <= size)
	{
		last = size;
		new
			next = array[last];
		while (next != value)
		{
			last = next;
			next = array[last];
		}
		array[last] = array[value];
		array[value] = size + 1;
		--count;
		return 1;
	}
	return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	Itter_ContainsInternal
Params:
	array[] - Itterator data.
	value - Item to check.
	size - Size of the iterator.
Return:
	-
Notes:
	Checks if this item is in the iterator.
\*----------------------------------------------------------------------------*/

stock
	Itter_ContainsInternal(array[], value, size)
{
	return 0 <= value < size && array[value] <= size;
}

/*----------------------------------------------------------------------------*\
Function:
	Itter_ClearInternal
Params:
	&count - Number of items in the itterator.
	array[] - Itterator data.
	back[] - Reverse data.
	size - Size of the iterator.
Return:
	-
Notes:
	Resets an iterator.
\*----------------------------------------------------------------------------*/

stock
	Itter_ClearInternal(&count, array[], size)
{
	for (new i = 0, t = size + 1; i < size; ++i)
	{
		array[i] = t;
	}
	array[size] = size;
	count = 0;
}

/*----------------------------------------------------------------------------*\
Function:
	Itter_InitInternal
Params:
	array[][] - Itterator array to initialise.
	s0 - Size of first dimension.
	s1 - Size of second dimension.
Return:
	-
Notes:
	Multi-dimensional arrays can't be initialised at compile time, so need to be
	done at run time, which is slightly annoying.
\*----------------------------------------------------------------------------*/

stock
	Itter_InitInternal(arr[][], s0, s1)
{
	for (new i = 0, t = s1 + 1; i < s0; ++i)
	{
		for (new j = 0; j < s1; ++j)
		{
			arr[i][j] = t;
		}
		arr[i][s1] = s1;
	}
}

/*----------------------------------------------------------------------------*\
Function:
	Itter_PrevInternal
Params:
	array[] - Itterator data.
	size - Size of the iterator.
	slot - The current slot.
Return:
	-
Notes:
	Gets the element in an iterator that points to the current element.
\*----------------------------------------------------------------------------*/

stock
	Itter_PrevInternal(array[], size, slot)
{
	if (0 <= slot <= size && array[slot] <= size)
	{
		for (new last = slot; last--; )
		{
			if (array[last] == slot)
			{
				return last;
			}
		}
	}
	return size;
}

/*----------------------------------------------------------------------------*\
Function:
	Iter_Begin
Params:
	iter - Name of the iterator to get the start of.
Return:
	-
Notes:
	Gets a point BEFORE the start of the iterator (the theoretical beginning).
\*----------------------------------------------------------------------------*/

#define Iter_Begin(%1) (_Y_ITER_ARRAY_SIZE(%1))
#define Itter_Begin(%1) (_Y_ITER_ARRAY_SIZE(%1))

/*----------------------------------------------------------------------------*\
Function:
	Iter_End
Params:
	iter - Name of the iterator to get the end of.
Return:
	-
Notes:
	Gets a point AFTER the end of the iterator (think "MAX_PLAYERS").
\*----------------------------------------------------------------------------*/

#define Iter_End(%1) (_Y_ITER_ARRAY_SIZE(%1))
#define Itter_End(%1) (_Y_ITER_ARRAY_SIZE(%1))

/*----------------------------------------------------------------------------*\
Function:
	Iter_First
Params:
	iter - Name of the iterator to get the first valid element in.
Return:
	-
Notes:
	Gets the first element in an iterator.
\*----------------------------------------------------------------------------*/

#define Iter_First(%1) (_Y_ITER_ARRAY:%1@YSII_Ag[_Y_ITER_ARRAY_SIZE(%1)])
#define Itter_First(%1) (_Y_ITER_ARRAY:%1@YSII_Ag[_Y_ITER_ARRAY_SIZE(%1)])

/*----------------------------------------------------------------------------*\
Function:
	Iter_Last
Params:
	iter - Name of the iterator to
Return:
	-
Notes:
	Gets the last element in an iterator.
\*----------------------------------------------------------------------------*/

#define Iter_Last(%1) Itter_PrevInternal(_Y_ITER_ARRAY:%1@YSII_Ag,_Y_ITER_ARRAY_SIZE(%1),_Y_ITER_ARRAY_SIZE(%1))
#define Itter_Last(%1) Itter_PrevInternal(_Y_ITER_ARRAY:%1@YSII_Ag,_Y_ITER_ARRAY_SIZE(%1),_Y_ITER_ARRAY_SIZE(%1))

/*----------------------------------------------------------------------------*\
Function:
	Iter_Next
Params:
	iter - Name of the iterator to get the next element in.
	cur - The current element.
Return:
	-
Notes:
	Gets the element in an interator after the current one.
\*----------------------------------------------------------------------------*/

#define Iter_Next(%1,%2) (_Y_ITER_ARRAY:%1@YSII_Ag[(%2)])
#define Itter_Next(%1,%2) (_Y_ITER_ARRAY:%1@YSII_Ag[(%2)])

/*----------------------------------------------------------------------------*\
Function:
	Iter_Prev
Params:
	iter - Name of the iterator to get the previous element in.
	cur - The current element.
Return:
	-
Notes:
	Gets the element in an iterator before the current one.  Slow.
\*----------------------------------------------------------------------------*/

#define Iter_Prev(%1,%2) Itter_PrevInternal(_Y_ITER_ARRAY:%1@YSII_Ag,_Y_ITER_ARRAY_SIZE(%1),(%2))
#define Itter_Prev(%1,%2) Itter_PrevInternal(_Y_ITER_ARRAY:%1@YSII_Ag,_Y_ITER_ARRAY_SIZE(%1),(%2))

/*----------------------------------------------------------------------------*\
Function:
	Iter_InternalArray
Params:
	iter - Name of the iterator to get the true name of.
Return:
	-
Notes:
	Accesses the internal array of an iterator.
\*----------------------------------------------------------------------------*/

#define Iter_InternalArray(%1) (_Y_ITER_ARRAY:%1@YSII_Ag)
#define Itter_InternalArray(%1) (_Y_ITER_ARRAY:%1@YSII_Ag)

/*----------------------------------------------------------------------------*\
Function:
	Iter_InternalSize
Params:
	iter - Name of the iterator to get the true size of.
Return:
	-
Notes:
	Accesses the internal size of an iterator.
\*----------------------------------------------------------------------------*/

#define _Y_ITER_INT_SIZE:%0(%2[%1]@YSII_Ag)) %0(%2@YSII_Ag[]))

#define Iter_InternalSize(%1) (_:_Y_ITER_INT_SIZE:sizeof (%1@YSII_Ag))
#define Itter_InternalSize(%1) (_:_Y_ITER_INT_SIZE:sizeof (%1@YSII_Ag))
