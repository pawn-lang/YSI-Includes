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

#if _FOREACH_PLAYERS
	new
		Iterator:Player<MAX_PLAYERS>;
#endif

#if _FOREACH_BOTS
	new
		Iterator:Bot<MAX_PLAYERS>,
		Iterator:Character<MAX_PLAYERS>;
	
	#define Iter_Single@NPC Iter_Single@Bot
	#define Iterator@NPC Iterator@Bot
#endif

#if _FOREACH_ACTORS
	new
		#if _FOREACH_LOCALS
			Iterator:LocalActor<MAX_ACTORS>,
		#endif
		Iterator:Actor<MAX_ACTORS>;
#endif

#if _FOREACH_VEHICLES
	new
		#if _FOREACH_LOCALS
			Iterator:LocalVehicle<MAX_VEHICLES + 1>,
		#endif
		Iterator:Vehicle<MAX_VEHICLES + 1>;
#endif

stock iterfunc Range(cur, min, max, step = 1)
{
	if (cur == cellmin) cur = min;
	else cur += step;
	return (min <= cur < max || max <= cur < min) ? cur : cellmin;
}

#define iterstart@Range cellmin

stock iterfunc Powers(&iterstate, cur, base)
{
	// Returns all the powers of the given number that can be stored in a PAWN
	// cell.
	//   
	//   foreach (new i : Powers(3))
	//   {
	//       // 3^0, 3^1, 3^2, 3^3, etc...
	//   }
	//   
	if (cur)
	{
		return
			iterstate = base * cur,
			_:(iterstate > cur) * iterstate;
	}
	return 1;
}

#define iterstart@Powers iterstate(0, 0)

stock iterfunc Fib(&iterstate, cur)
{
	// Returns every number in the Fibaonacci sequence that can be stored in a
	// PAWN cell.
	//   
	//   foreach (new i : Fib())
	//   {
	//   }
	//   
	switch (cur)
	{
	case -1:
		return 0;
	case 1836311903:
		// End point (statically calculated largest Fibaonacci number that can
		// be stored in a signed 32-bit integer.  Does make this not totally
		// portable, because it can't be used in the 64-bit version quickly.
		return -1;
	}
	// Based on the "+--" swap method (like "^^^"), but without the last one.
	return (iterstate = iterstate + cur) - cur;
}

#define iterstart@Fib iterstate(-1, 1)

stock iterfunc Random(&iterstate, cur, count, min = cellmax, max = 0)
{
	// Return a given count of random numbers:
	//   
	//   foreach (new i : Random(5))
	//   {
	//       // 5 random numbers.
	//   }
	//   
	//   foreach (new i : Random(12, 10))
	//   {
	//       // 12 random numbers between 0 and 10 (0 to 9 inclusive).
	//   }
	//   
	//   foreach (new i : Random(100, -10, 10))
	//   {
	//       // 100 random numbers between -10 and 10 (-10 to 9 inclusive).
	//   }
	//   
	// Note that this function has internal state, so you cannot call this in a
	// nested manner.  This will probably fail:
	//   
	//   foreach (new i : Random(10, 70))
	//   {
	//       foreach (new j : Random(10, 80))
	//       {
	//           // Will NOT get 100 randoms 0 to 80, plus 10 randoms 0 to 70.
	//       }
	//   }
	//   
	if (cur == cellmin)
	{
		iterstate = 0;
	}
	if (++iterstate > count)
	{
		return cellmin;
	}
	if (min >= max)
	{
		return random(min);
	}
	else
	{
		return random(max - min) + min;
	}
}

#define iterstart@Random iterstate(cellmin, 0)

stock iterfunc Null(cur, arr[], size = sizeof (arr))
{
	// Loop over all the indexes of this array that are zero.
	//   
	//   new array[] = { ... };
	//   foreach (new i : Null(array))
	//   {
	//   }
	//   
	while (++cur < size)
	{
		if (!arr[cur])
		{
			return cur;
		}
	}
	return -1;
}

#define iterstart@Null (-1)

stock iterfunc NonNull(cur, arr[], size = sizeof (arr))
{
	// Loop over all the indexes of this array that are not zero.
	//   
	//   new array[] = { ... };
	//   foreach (new i : NonNull(array))
	//   {
	//   }
	//   
	while (++cur < size)
	{
		if (arr[cur])
		{
			return cur;
		}
	}
	return -1;
}

#define iterstart@NonNull (-1)

stock iterfunc Until(cur, val, arr[], size = sizeof (arr))
{
	// Loop over all the indexes of this array until one equals the given value:
	//   
	//   new array[] = { ... };
	//   foreach (new i : Until(5, array))
	//   {
	//   }
	//   
	return (++cur >= size || arr[cur] == val) ? -1 : cur;
}

#define iterstart@Until (-1)

stock iterfunc Filter(cur, val, arr[], size = sizeof (arr))
{
	while (++cur < size)
	{
		if (arr[cur] == val)
		{
			return cur;
		}
	}
	return -1;
}

#define iterstart@Filter (-1)

#define Iter_Func@None(%0,%1) _ITER<None>(%1,%0)
#define iterstart@None (-1)
#define Iter_None_InternalA(%0,%1,%9) Iter_None_Internal(%1,F@s(%1)-1,%9)
#define Iter_None_InternalB(%0,%2,%1,%9) Iter_None_Internal(%1,F@s(%1)-F@s(%0),%9)

stock Iter_None_Internal(array[], size, value)
{
	// Loop over all values NOT in any iterator.  Similar to repeatedly calling
	// "Iter_Free", though that will return the same value twice if called twice
	// in a row.  Instead, this function will loop through the missing ones.
	while (++value < size)
	{
		if (array[value] <= value)
		{
			return value;
		}
	}
	return -1;
}

#define Iter_Func@All(%0,%1) _ITER<All>(%1,%0)
#define iterstart@All (-1)
#define Iter_All_InternalA(%0,%1,%9) Iter_All_Internal(%1,F@s(%1)-1,%9)
#define Iter_All_InternalB(%0,%2,%1,%9) Iter_All_Internal(%1,F@s(%1)-F@s(%0),%9)

stock Iter_All_Internal(array[], size, value)
{
	// Loop over all values in any iterator.  This is different to looping over
	// the iterator normally for multi-dimensional iterators, since it will
	// return all values in ANY iterator in their numerical order.  For single-
	// dimensional iterators it is exactly the same, just a little slower.
	while (++value < size)
	{
		if (array[value] > value)
		{
			return value;
		}
	}
	return -1;
}

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
<summary>Iter_OnScriptInit</summary>
<returns>
	-
</returns>
<remarks>
	Sets up all existing iterators.  Does nothing for "XXLocal" ones, since they
	are by definition empty when a script starts.
</remarks>
\**--------------------------------------------------------------------------**/

hook OnScriptInit()
{
	#if _FOREACH_VEHICLES
		Iter_Clear(Vehicle);
		for (new i = 1; i <= MAX_VEHICLES; ++i)
		{
			if (GetVehicleModel(i))
			{
				Iter_Add(Vehicle, i);
			}
		}
	#endif
	#if _FOREACH_ACTORS
		Iter_Clear(Actor);
		for (new i = 0; i != MAX_ACTORS; ++i)
		{
			if (IsValidActor(i))
			{
				Iter_Add(Actor, i);
			}
		}
	#endif
	#if _FOREACH_CHARACTERS
		#if _FOREACH_BOTS
			Iter_Clear(Bot);
			Iter_Clear(Character);
		#endif
		#if _FOREACH_PLAYERS
			Iter_Clear(Player);
		#endif
		for (new i = 0; i != MAX_PLAYERS; ++i)
		{
			if (IsPlayerConnected(i))
			{
				#if _FOREACH_BOTS
					Iter_Add(Character, i);
					if (IsPlayerNPC(i))
					{
						Iter_Add(Bot, i);
					}
					else
				#endif
				#if _FOREACH_PLAYERS
					{
						Iter_Add(Player, i);
					}
				#endif
			}
		}
	#endif
	return 1;
}

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

#if _FOREACH_CHARACTERS
	hook OnPlayerConnect(playerid)
	{
		P:1("Iter_OnPlayerConnect called: %d, %d", playerid, IsPlayerNPC(playerid));
		#if _FOREACH_BOTS
			Iter_Add(Character, playerid);
			if (IsPlayerNPC(playerid))
			{
				Iter_Add(Bot, playerid);
			}
			else
		#endif
		#if _FOREACH_PLAYERS
			{
				Iter_Add(Player, playerid);
			}
		#endif
		P:2("Iter_OnPlayerConnect end");
		return 1;
	}
	
	/**----------------------------------------------------------------------**\
	<summary>Iter_OnPlayerDisconnect</summary>
	<param name="playerid">Player who left.</param>
	<returns>
		-
	</returns>
	<remarks>
		Removes a player from the loop data.  No longer uses "hook" to ENSURE
		that this is always last.  Previously I think that the order of
		evaluation in y_hooks meant that this got called before the user
		"OnPlayerDisconnect".
	</remarks>
	\**----------------------------------------------------------------------**/
	
	hook OnPlayerDisconnect(playerid, reason)
	{
		SetTimerEx("Iter_OPDCInternal", 0, false, "i", playerid);
		return 1;
	}
	
	/**----------------------------------------------------------------------**\
	<summary>Iter_OPDCInternal</summary>
	<param name="playerid">Player who left.</param>
	<returns>
		-
	</returns>
	<remarks>
		Called AFTER "OnPlayerDisconnect" so that using "Kick" inside a
		"foreach" loop doesn't crash the server due to an OOB error.
	</remarks>
	\**----------------------------------------------------------------------**/
	
	public Iter_OPDCInternal(playerid)
	{
		if (IsPlayerConnected(playerid))
		{
			return;
		}
		#if _FOREACH_BOTS
			Iter_Remove(Character, playerid);
			if (IsPlayerNPC(playerid))
			{
				Iter_Remove(Bot, playerid);
			}
			else
		#endif
		#if _FOREACH_PLAYERS
			{
				Iter_Remove(Player, playerid);
			}
		#endif
	}
#endif

/*

           db                                                           
          d88b                   ,d                                     
         d8'`8b                  88                                     
        d8'  `8b     ,adPPYba, MM88MMM ,adPPYba,  8b,dPPYba, ,adPPYba,  
       d8YaaaaY8b   a8"     ""   88   a8"     "8a 88P'   "Y8 I8[    ""  
      d8""""""""8b  8b           88   8b       d8 88          `"Y8ba,   
     d8'        `8b "8a,   ,aa   88,  "8a,   ,a8" 88         aa    ]8I  
    d8'          `8b `"Ybbd8"'   "Y888 `"YbbdP"'  88         `"YbbdP"'  

*/

#if _FOREACH_ACTORS
	remotefunc void:Iter_ActorDo(bool:add, actorid)
	{
		// Because there may be multiple scripts running, we need to tell all of
		// them when an actor is created or destroyed.
		if (add)
			Iter_Add(Actor, actorid);
		else
			Iter_Remove(Actor, actorid);
	}
	
	stock Iter_CreateActor(modelid, Float:X, Float:Y, Float:Z, Float:Rotation)
	{
		new
			ret = CreateActor(modelid, X, Y, Z, Rotation);
		broadcastfunc Iter_ActorDo(true, ret);
		#if _FOREACH_LOCALS
			Iter_Add(LocalActor, ret);
		#endif
		return ret;
	}
	
	#if defined _ALS_CreateActor
		#undef CreateActor
	#else
		#define _ALS_CreateActor
	#endif
	#define CreateActor Iter_CreateActor
	
	stock Iter_DestroyActor(actorid)
	{
		broadcastfunc Iter_ActorDo(false, actorid);
		#if _FOREACH_LOCALS
			Iter_Remove(LocalActor, actorid);
		#endif
		return DestroyActor(actorid);
	}
	
	#if defined _ALS_DestroyActor
		#undef DestroyActor
	#else
		#define _ALS_DestroyActor
	#endif
	#define DestroyActor Iter_DestroyActor
#endif

/*

    8b           d8         88          88            88                       
    `8b         d8'         88          ""            88                       
     `8b       d8'          88                        88                       
      `8b     d8' ,adPPYba, 88,dPPYba,  88  ,adPPYba, 88  ,adPPYba, ,adPPYba,  
       `8b   d8' a8P_____88 88P'    "8a 88 a8"     "" 88 a8P_____88 I8[    ""  
        `8b d8'  8PP""""""" 88       88 88 8b         88 8PP"""""""  `"Y8ba,   
         `888'   "8b,   ,aa 88       88 88 "8a,   ,aa 88 "8b,   ,aa aa    ]8I  
          `8'     `"Ybbd8"' 88       88 88  `"Ybbd8"' 88  `"Ybbd8"' `"YbbdP"'  

*/

#if _FOREACH_VEHICLES
	remotefunc void:Iter_VehicleDo(bool:add, vehicleid)
	{
		// Because there may be multiple scripts running, we need to tell all of
		// them when a vehicle is created or destroyed.
		if (add)
			Iter_Add(Vehicle, vehicleid);
		else
			Iter_Remove(Vehicle, vehicleid);
	}
	
	stock Iter_CreateVehicle(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, respawn_delay, addsiren = 0)
	{
		#if _FOREACH_ACTORS
			new
				ret = CreateVehicle(modelid, x, y, z, angle, color1, color2, respawn_delay, addsiren);
		#else
			#pragma unused addsiren
			new
				ret = CreateVehicle(modelid, x, y, z, angle, color1, color2, respawn_delay);
		#endif
		broadcastfunc Iter_VehicleDo(true, ret);
		#if _FOREACH_LOCALS
			Iter_Add(LocalVehicle, ret);
		#endif
		return ret;
	}
	
	#if defined _ALS_CreateVehicle
		#undef CreateVehicle
	#else
		#define _ALS_CreateVehicle
	#endif
	#define CreateVehicle Iter_CreateVehicle
	
	stock Iter_AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:angle, color1, color2)
	{
		new
			ret = AddStaticVehicle(modelid, spawn_x, spawn_y, spawn_z, angle, color1, color2);
		broadcastfunc Iter_VehicleDo(true, ret);
		#if _FOREACH_LOCALS
			Iter_Add(LocalVehicle, ret);
		#endif
		return ret;
	}
	
	#if defined _ALS_AddStaticVehicle
		#undef AddStaticVehicle
	#else
		#define _ALS_AddStaticVehicle
	#endif
	#define AddStaticVehicle Iter_AddStaticVehicle
	
	stock Iter_AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:angle, color1, color2, respawn_delay, addsiren = 0)
	{
		#if _FOREACH_ACTORS
			new
				ret = AddStaticVehicleEx(modelid, spawn_x, spawn_y, spawn_z, angle, color1, color2, respawn_delay, addsiren);
		#else
			#pragma unused addsiren
			new
				ret = AddStaticVehicleEx(modelid, spawn_x, spawn_y, spawn_z, angle, color1, color2, respawn_delay);
		#endif
		broadcastfunc Iter_VehicleDo(true, ret);
		#if _FOREACH_LOCALS
			Iter_Add(LocalVehicle, ret);
		#endif
		return ret;
	}
	
	#if defined _ALS_AddStaticVehicleEx
		#undef AddStaticVehicleEx
	#else
		#define _ALS_AddStaticVehicleEx
	#endif
	#define AddStaticVehicleEx Iter_AddStaticVehicleEx
	
	stock Iter_DestroyVehicle(vehicleid)
	{
		broadcastfunc Iter_VehicleDo(false, vehicleid);
		#if _FOREACH_LOCALS
			Iter_Remove(LocalVehicle, vehicleid);
		#endif
		return DestroyVehicle(vehicleid);
	}
	
	#if defined _ALS_DestroyVehicle
		#undef DestroyVehicle
	#else
		#define _ALS_DestroyVehicle
	#endif
	#define DestroyVehicle Iter_DestroyVehicle
#endif

