/*
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

/*-------------------------------------------------------------------------*//**
 * Create the internal iterators.
 *//*------------------------------------------------------------------------**/

#if _FOREACH_PLAYERS
	new
		#if _FOREACH_STREAMED
			ITERATOR__ StreamedPlayer[MAX_PLAYERS]<MAX_PLAYERS>,
		#endif
		ITERATOR__ RconAdmin<MAX_PLAYERS>,
		ITERATOR__ Player<MAX_PLAYERS>;
#endif

#if _FOREACH_BOTS
	new
		#if _FOREACH_STREAMED
			ITERATOR__ StreamedBot[MAX_PLAYERS]<MAX_PLAYERS>,
		#endif
		ITERATOR__ Bot<MAX_PLAYERS>,
		#if _FOREACH_STREAMED
			ITERATOR__ StreamedCharacter[MAX_PLAYERS]<MAX_PLAYERS>,
		#endif
		ITERATOR__ Character<MAX_PLAYERS>;
	
	#define Iter_Single@NPC Iter_Single@Bot
	#define Iterator@NPC Iterator@Bot
#endif

#if _FOREACH_ACTORS
	new
		#if _FOREACH_LOCALS
			ITERATOR__ LocalActor<MAX_ACTORS>,
		#endif
		#if _FOREACH_STREAMED
			ITERATOR__ StreamedActor[MAX_PLAYERS]<MAX_ACTORS>,
		#endif
		ITERATOR__ Actor<MAX_ACTORS>;
#endif

#if _FOREACH_VEHICLES
	new
		#if _FOREACH_LOCALS
			ITERATOR__ LocalVehicle<MAX_VEHICLES>,
		#endif
		#if _FOREACH_STREAMED
			ITERATOR__ StreamedVehicle[MAX_PLAYERS]<MAX_VEHICLES>,
		#endif
		ITERATOR__ Vehicle<MAX_VEHICLES>;

	static
		ITERATOR__ PlayersFromVehicles<MAX_PLAYERS>;
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="cur">The current iterator step.</param>
 * <param name="min">The start value.</param>
 * <param name="max">The end value.</param>
 * <param name="step">How many values to increase by each time.</param>
 * <remarks>
 *   Pretty much used to replicate a normal loop with <c>foreach</c>.  This:
 * 
 *   <code>
 *      for (new i = 10; i != 100; i += 2) <br />
 *      {                                  <br />
 *      }
 *   </code>
 * 
 *   Becomes:
 * 
 *   <code>
 *      foreach (new i : Range(10, 100, 2)) <br />
 *      {                                   <br />
 *      }
 *   </code>
 * 
 *   The increment value is optional, and defaults to <c>1</c>.  If you want a
 *   <c>step</c> of <c>1</c> and a <c>min</c> of <c>0</c>, consider using
 *   <c>N(max)</c> instead, which is specifically optimised for that scenario.
 * </remarks>
 *//*------------------------------------------------------------------------**/

iterfunc stock Range[cellmin](cur, min, max, step = 1)
{
	if (cur == cellmin) cur = min;
	else cur += step;
	return (min <= cur < max || max < cur <= min) ? cur : cellmin;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="cur">The current iterator step.</param>
 * <param name="n">The target number.</param>
 * <remarks>
 *   Loop until the given target is reached.
 *    
 *   <code>  
 *    foreach (new i : N(6))  <br />
 *    {                       <br /><indent />
 *        // 0, 1, 2, 3, 4, 5 <br />
 *    }
 *   </code>  
 *    
 *   This is equivalent to:
 * 
 *   <code>
 *      for (new i = 0; i != 6; ++i) <br />
 *      {                            <br />
 *      }
 *   </code>
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

iterfunc stock N(cur, n)
{
	if (++cur == n) return -1;
	return cur;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="iterstate">Internal state of the iterator.</param>
 * <param name="cur">The current iterator step.</param>
 * <param name="base">The number to get the powers of.</param>
 * <remarks>
 *   Returns all the powers of the given number that can be stored in a PAWN
 *   cell.
 *    
 *   <code>  
 *    foreach (new i : Powers(3))       <br />
 *    {                                 <br /><indent />
 *        // 3^0, 3^1, 3^2, 3^3, etc... <br />
 *    }
 *   </code>  
 *    
 * </remarks>
 *//*------------------------------------------------------------------------**/

iterfunc stock Powers(&iterstate, cur, base)
{
	if (cur)
	{
		return
			iterstate = base * cur,
			_:(iterstate > cur) * iterstate;
	}
	return 1;
}

#define iterstart@Powers iterstate(0, 0)

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="iterstate">Internal state of the iterator.</param>
 * <param name="cur">The current iterator step.</param>
 * <remarks>
 *   Returns every number in the Fibonacci sequence that can be stored in a
 *   PAWN cell.
 *    
 *   <code>  
 *    foreach (new i : Fib())         <br />
 *    {                               <br /><indent />
 *        // 0, 1, 1, 2, 3, 5, etc... <br />
 *    }
 *   </code>  
 *    
 * </remarks>
 *//*------------------------------------------------------------------------**/

iterfunc stock Fib(&iterstate, cur)
{
	switch (cur)
	{
		case -1:
			return 0;
	#if cellbits == 32
		case 1836311903:
			// End point (statically calculated largest Fibonacci number that
			// can be stored in a signed 32-bit integer).
			return -1;
	#elseif cellbits == 64
		case 7540113804746346429:
			return -1;
	#else
		#error Unsupported `cellbits`.
	#endif
	}
	// Based on the "+--" swap method (like "^^^"), but without the last one.
	return (iterstate = iterstate + cur) - cur;
}

#define iterstart@Fib iterstate(-1, 1)

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="iterstate">Internal state of the iterator.</param>
 * <param name="cur">The current iterator step.</param>
 * <param name="count">How many random numbers to generate.</param>
 * <param name="min">Lowest possible number (inclusive).</param>
 * <param name="max">Highest possible number (exclusive).</param>
 * <remarks>
 *   Return a given count of random numbers:
 *    
 *   <code>
 *    foreach (new i : Random(5)) <br />
 *    {                           <br /><indent />
 *        // 5 random numbers.    <br />
 *    }
 *   </code>
 *    
 *   <code>
 *    foreach (new i : Random(12, 10))                              <br />
 *    {                                                             <br /><indent />
 *        // 12 random numbers between 0 and 10 (0 to 9 inclusive). <br />
 *    }
 *   </code>
 *    
 *   <code>
 *    foreach (new i : Random(100, -10, 10))                             <br />
 *    {                                                                  <br /><indent />
 *        // 100 random numbers between -10 and 10 (-10 to 9 inclusive). <br />
 *    }
 *   </code>
 *    
 *   If only <c>min</c> is given, not <c>max</c>, it is used as the max instead
 *   and the minimum is <c>0</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

iterfunc stock Random(&iterstate, cur, count, min = cellmax, max = 0)
{
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

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="cur">The current iterator step.</param>
 * <param name="arr">Teh array to search through.</param>
 * <param name="size">The size of the array.</param>
 * <remarks>
 *   Loop over all the indexes of this array that are zero.
 *    
 *   <code>
 *    new array[] = { ... };        <br />
 *    foreach (new i : Null(array)) <br />
 *    {                             <br />
 *    }
 *   </code>
 *    
 * </remarks>
 *//*------------------------------------------------------------------------**/

iterfunc stock Null(cur, const arr[], size = sizeof (arr))
{
	while (++cur < size)
	{
		if (!arr[cur])
		{
			return cur;
		}
	}
	return -1;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="cur">The current iterator step.</param>
 * <param name="arr">Teh array to search through.</param>
 * <param name="size">The size of the array.</param>
 * <remarks>
 *   Loop over all the indexes of this array that are not zero.
 *    
 *   <code>
 *    new array[] = { ... };           <br />
 *    foreach (new i : NonNull(array)) <br />
 *    {                                <br />
 *    }
 *   </code>
 *    
 * </remarks>
 *//*------------------------------------------------------------------------**/

iterfunc stock NonNull(cur, const arr[], size = sizeof (arr))
{
	while (++cur < size)
	{
		if (arr[cur])
		{
			return cur;
		}
	}
	return -1;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="cur">The current iterator step.</param>
 * <param name="val">The number to search the array for.</param>
 * <param name="arr">Teh array to search through.</param>
 * <param name="size">The size of the array.</param>
 * <remarks>
 *   Loop over all the indexes of this array until one equals the given value.
 *    
 *   <code>
 *    new array[] = { ... };            <br />
 *    foreach (new i : Until(5, array)) <br />
 *    {                                 <br />
 *    }
 *   </code>
 *    
 * </remarks>
 *//*------------------------------------------------------------------------**/

iterfunc stock Until(cur, val, const arr[], size = sizeof (arr))
{
	return (++cur >= size || arr[cur] == val) ? -1 : cur;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="cur">The current iterator step.</param>
 * <param name="val">The number to search the array for.</param>
 * <param name="arr">Teh array to search through.</param>
 * <param name="size">The size of the array.</param>
 * <remarks>
 *   Loop over all the indexes of this array which contain the given value.
 *    
 *   <code>
 *    new array[] = { ... };             <br />
 *    foreach (new i : Filter(5, array)) <br />
 *    {                                  <br />
 *    }
 *   </code>
 *    
 * </remarks>
 *//*------------------------------------------------------------------------**/

iterfunc stock Filter(cur, val, const arr[], size = sizeof (arr))
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

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="array">The internal iterator data.</param>
 * <param name="size">The internal iterator size.</param>
 * <param name="value">The current iterator step.</param>
 * <remarks>
 *   Loop over all values NOT in any iterator.  Similar to repeatedly calling
 *   <c>Iter_Free</c>, though that will return the same value twice if called
 *   twice in a row.  Instead, this function will loop through the missing ones.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define Iter_Func@None(%0,%1) _ITER<Iter_None_Internal>(%1,%0)
#define Iterator@None iterstart(-1)
#define Iter_None_InternalA(%0,%1,%9) Iter_None_Internal(%1,F@s(%1)-1,%9)
#define Iter_None_InternalB(%0,%2,%1,%9) Iter_None_Internal(%1,F@s(%1)-F@s(%0),%9)

stock Iter_None_Internal(const array[], size, value)
{
	while (++value < size)
	{
		if (array[value] <= value)
		{
			return value;
		}
	}
	return -1;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <param name="array">The internal iterator data.</param>
 * <param name="size">The internal iterator size.</param>
 * <param name="value">The current iterator step.</param>
 * <remarks>
 *   Loop over all values in any iterator.  This is different to looping over the
 *   iterator normally for multi-dimensional iterators, since it will return all
 *   values in ANY iterator in their numerical order.  For single dimensional
 *   iterators it is exactly the same, just a little slower.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define Iter_Func@All(%0,%1) _ITER<Iter_All_Internal>(%1,%0)
#define Iterator@All iterstart(-1)
#define Iter_All_InternalA(%0,%1,%9) Iter_All_Internal(%1,F@s(%1)-1,%9)
#define Iter_All_InternalB(%0,%2,%1,%9) Iter_All_Internal(%1,F@s(%1)-F@s(%0),%9)

stock Iter_All_Internal(const array[], size, value)
{
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

/*-------------------------------------------------------------------------*//**
 * <library>y_iterate</library>
 * <remarks>
 *   Sets up all existing iterators.  Does nothing for "XXLocal" ones, since they
 *   are by definition empty when a script starts.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if _FOREACH_CHARACTERS || _FOREACH_VEHICLES || _FOREACH_ACTORS
	public OnYSIInit()
	{
		#if _FOREACH_VEHICLES
			Iter_Clear(Vehicle);
			#if _FOREACH_STREAMED
				Iter_InitAndClear(StreamedVehicle);
			#endif
			for (new i = 1; i <= MAX_VEHICLES; ++i)
			{
				if (GetVehicleModel(i))
				{
					Iter_Add(Vehicle, i);
					#if _FOREACH_STREAMED
						for (new j = 0; j != MAX_PLAYERS; ++j)
						{
							if (IsVehicleStreamedIn(i, j))
							{
								Iter_Add(StreamedVehicle[j], i);
							}
						}
					#endif
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
					#if _FOREACH_STREAMED
						for (new j = 0; j != MAX_PLAYERS; ++j)
						{
							if (IsActorStreamedIn(i, j))
							{
								Iter_Add(StreamedActor[j], i);
							}
						}
					#endif
				}
			}
			#if _FOREACH_STREAMED
				Iter_InitAndClear(StreamedActor);
			#endif
		#endif
		#if _FOREACH_CHARACTERS
			#if _FOREACH_BOTS
				Iter_Clear(Bot);
				Iter_Clear(Character);
				#if _FOREACH_STREAMED
					Iter_InitAndClear(StreamedBot);
					Iter_InitAndClear(StreamedCharacter);
				#endif
			#endif
			#if _FOREACH_PLAYERS
				Iter_Clear(Player);
				Iter_Clear(RconAdmin);
				#if _FOREACH_STREAMED
					Iter_InitAndClear(StreamedPlayer);
				#endif
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
							#if _FOREACH_STREAMED
								for (new j = 0; j != MAX_PLAYERS; ++j)
								{
									if (IsPlayerStreamedIn(i, j))
									{
										Iter_Add(StreamedCharacter[j], i);
										Iter_Add(StreamedBot[j], i);
									}
								}
							#endif
						}
						else
					#endif
						{
					#if _FOREACH_PLAYERS
							Iter_Add(Player, i);
							if (IsPlayerAdmin(i))
							{
								Iter_Add(RconAdmin, i);
							}
							#if _FOREACH_STREAMED
								for (new j = 0; j != MAX_PLAYERS; ++j)
								{
									if (IsPlayerStreamedIn(i, j))
									{
										#if _FOREACH_BOTS
											Iter_Add(StreamedCharacter[j], i);
										#endif
										Iter_Add(StreamedPlayer[j], i);
									}
								}
							#endif
					#endif
						}
				}
			}
		#endif
		return Iter_OnYSIInit();
	}

	#if defined _ALS_OnYSIInit
		#undef OnYSIInit
	#endif
	#define _ALS_OnYSIInit
	#define OnYSIInit(%0) CHAIN_PUBLIC:Iter_OnYSIInit(%0)
	CHAIN_FORWARD:Iter_OnYSIInit() = 1;
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

#if _FOREACH_CHARACTERS
	/*-------------------------------------------------------------------------*//**
	 * <library>y_iterate</library>
	 * <param name="playerid">Player who joined.</param>
	 * <remarks>
	 *   Adds a player to the loop data.  Now sorts the list too.  Note that I found
	 *   the most bizzare bug ever (I *think* it may be a compiler but, but it
	 *   requires further investigation), basically it seems that multiple variables
	 *   were being treated as the same variable (namely @YSII_EgotS and
	 *   @YSII_CgharacterS were the same and @YSII_EgotC and @YSII_CgharacterC were the
	 *   same).  Adding print statements which reference these variables seem to fix
	 *   the problem, and I've tried to make sure that the values will never actually
	 *   get printed.
	 * </remarks>
	 *//*------------------------------------------------------------------------**/

	public OnPlayerConnect(playerid)
	{
		Debug_Print1("Iter_OnPlayerConnect called: %d, %d", playerid, IsPlayerNPC(playerid));
		#if _FOREACH_BOTS
			Iter_Add(Character, playerid);
			if (IsPlayerNPC(playerid))
			{
				Iter_Add(Bot, playerid);
			}
			else
		#endif
			{
		#if _FOREACH_PLAYERS
				Iter_Add(Player, playerid);
		#endif
			}
		Debug_Print2("Iter_OnPlayerConnect end");
		return Iter_OnPlayerConnect(playerid);
	}

	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#endif
	#define _ALS_OnPlayerConnect
	#define OnPlayerConnect(%0) CHAIN_PUBLIC:Iter_OnPlayerConnect(%0)
	CHAIN_FORWARD:Iter_OnPlayerConnect(playerid) = 1;

	/*-------------------------------------------------------------------------*//**
	 * <library>y_iterate</library>
	 * <param name="playerid">Player who joined.</param>
	 * <remarks>
	 *   Adds a player to the loop data.  Now sorts the list too.  Note that I found
	 *   the most bizzare bug ever (I *think* it may be a compiler but, but it
	 *   requires further investigation), basically it seems that multiple variables
	 *   were being treated as the same variable (namely @YSII_EgotS and
	 *   @YSII_CgharacterS were the same and @YSII_EgotC and @YSII_CgharacterC were the
	 *   same).  Adding print statements which reference these variables seem to fix
	 *   the problem, and I've tried to make sure that the values will never actually
	 *   get printed.
	 * </remarks>
	 *//*------------------------------------------------------------------------**/

	#if _FOREACH_PLAYERS
		public OnRconLoginAttempt(ip[], password[], success)
		{
			Debug_Print1("Iter_OnRconLoginAttempt called: %s, %s, %d", ip, password, success);
			if (success)
			{
				// Rebuild the iterator.
				FOREACH__ (new i : Player)
				{
					if (IsPlayerAdmin(i))
					{
						// Add all admins.  It doesn't matter if they're already
						// added, since `Iter_Add` has internal checks for that.
						Iter_Add(RconAdmin, i);
					}
				}
			}
			Debug_Print2("Iter_OnRconLoginAttempt end");
			return Iter_OnRconLoginAttempt(ip, password, success);
		}
		
		#if defined _ALS_OnRconLoginAttempt
			#undef OnRconLoginAttempt
		#endif
		#define _ALS_OnRconLoginAttempt
		#define OnRconLoginAttempt(%0) CHAIN_PUBLIC:Iter_OnRconLoginAttempt(%0)
		CHAIN_FORWARD:Iter_OnRconLoginAttempt(ip[], password[], success) = 1;
	#endif
	
	/*---------------------------------------------------------------------*//**
	 * <library>y_iterate</library>
	 * <param name="playerid">Player who left.</param>
	 * <remarks>
	 *   Removes a player from the loop data.  No longer uses "hook" to ENSURE
	 *   that this is always last.  Previously I think that the order of
	 *   evaluation in y_hooks meant that this got called before the user
	 *   "OnPlayerDisconnect".
	 * </remarks>
	 *//*--------------------------------------------------------------------**/
	
	public OnPlayerDisconnect(playerid, reason)
	{
			new ret = Iter_OnPlayerDisconnect(playerid, reason);
		#if _FOREACH_VEHICLES 
			Iter_Remove(PlayersFromVehicles, playerid);
		#endif
		#if _FOREACH_BOTS
			Iter_Remove(Character, playerid);
			if (IsPlayerNPC(playerid))
			{
				Iter_Remove(Bot, playerid);
			}
			else
		#endif
			{
		#if _FOREACH_PLAYERS
				Iter_Remove(Player, playerid);
				Iter_Remove(RconAdmin, playerid);
		#endif
			}
			return ret;
	}

	#if defined _ALS_OnPlayerDisconnect
		#undef OnPlayerDisconnect
	#endif
	#define _ALS_OnPlayerDisconnect
	#define OnPlayerDisconnect(%0) CHAIN_PUBLIC:Iter_OnPlayerDisconnect(%0)
	CHAIN_FORWARD:Iter_OnPlayerDisconnect(playerid, reason) = 1;
	
	#if _FOREACH_STREAMED
		/*---------------------------------------------------------------------*//**
		 * <library>y_iterate</library>
		 * <param name="playerid">Player who entered streaming range.</param>
		 * <param name="forplayerid">The viewing player.</param>
		 * <remarks>
		 *   Update the internal list of which players <c>forplayerid</c> can see.
		 * </remarks>
		 *//*--------------------------------------------------------------------**/
		
		public OnPlayerStreamIn(playerid, forplayerid)
		{
			Debug_Print1("Iter_OnPlayerStreamIn called: %d, %d", playerid, forplayerid);
			#if _FOREACH_BOTS
				Iter_Add(StreamedCharacter[forplayerid], playerid);
				if (IsPlayerNPC(playerid))
				{
					Iter_Add(StreamedBot[forplayerid], playerid);
				}
				else
			#endif
				{
			#if _FOREACH_PLAYERS
					Iter_Add(StreamedPlayer[forplayerid], playerid);
			#endif
				}
			Debug_Print2("Iter_OnPlayerStreamIn end");
			return Iter_OnPlayerStreamIn(playerid, forplayerid);
		}

		#if defined _ALS_OnPlayerStreamIn
			#undef OnPlayerStreamIn
		#endif
		#define _ALS_OnPlayerStreamIn
		#define OnPlayerStreamIn(%0) CHAIN_PUBLIC:Iter_OnPlayerStreamIn(%0)
		CHAIN_FORWARD:Iter_OnPlayerStreamIn(playerid, forplayerid) = 1;

		/*---------------------------------------------------------------------*//**
		 * <library>y_iterate</library>
		 * <param name="playerid">Player who left streaming range.</param>
		 * <param name="forplayerid">The viewing player.</param>
		 * <remarks>
		 *   Update the internal list of which players <c>forplayerid</c> can see.
		 * </remarks>
		 *//*--------------------------------------------------------------------**/
		
		public OnPlayerStreamOut(playerid, forplayerid)
		{
			Debug_Print1("Iter_OnPlayerStreamOut called: %d, %d", playerid, forplayerid);
			new ret = Iter_OnPlayerStreamOut(playerid, forplayerid);
			#if _FOREACH_BOTS
				Iter_Remove(StreamedCharacter[forplayerid], playerid);
				if (IsPlayerNPC(playerid))
				{
					Iter_Remove(StreamedBot[forplayerid], playerid);
				}
				else
			#endif
				{
			#if _FOREACH_PLAYERS
					Iter_Remove(StreamedPlayer[forplayerid], playerid);
			#endif
				}
			Debug_Print2("Iter_OnPlayerStreamOut end");
			return ret;
		}

		#if defined _ALS_OnPlayerStreamOut
			#undef OnPlayerStreamOut
		#endif
		#define _ALS_OnPlayerStreamOut
		#define OnPlayerStreamOut(%0) CHAIN_PUBLIC:Iter_OnPlayerStreamOut(%0)
		CHAIN_FORWARD:Iter_OnPlayerStreamOut(playerid, forplayerid) = 1;
	#endif
#endif

static stock const
	/**
	 * <library>y_iterate</library>
	 */
	YSI_gsIter_VehicleDo[] = "Iter_VehicleDo",
	/**
	 * <library>y_iterate</library>
	 */
	YSI_gsIter_ActorDo[] = "Iter_ActorDo";

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
	forward void:Iter_ActorDo(bool:add, actorid);

	public void:Iter_ActorDo(bool:add, actorid)
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
		CallRemoteFunction(YSI_gsIter_ActorDo, YSI_gcII, true, ret);
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
		CallRemoteFunction(YSI_gsIter_ActorDo, YSI_gcII, false, actorid);
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

	#if _FOREACH_STREAMED
		public OnActorStreamIn(actorid, forplayerid)
		{
			Debug_Print1("Iter_OnActorStreamIn called: %d, %d", actorid, forplayerid);
			Iter_Add(StreamedActor[forplayerid], actorid);
			Debug_Print2("Iter_OnActorStreamIn end");
			return Iter_OnActorStreamIn(actorid, forplayerid);
		}

		#if defined _ALS_OnActorStreamIn
			#undef OnActorStreamIn
		#endif
		#define _ALS_OnActorStreamIn
		#define OnActorStreamIn(%0) CHAIN_PUBLIC:Iter_OnActorStreamIn(%0)
		CHAIN_FORWARD:Iter_OnActorStreamIn(actorid, forplayerid) = 1;

		public OnActorStreamOut(actorid, forplayerid)
		{
			new ret = Iter_OnActorStreamOut(actorid, forplayerid);
			Debug_Print1("Iter_OnActorStreamOut called: %d, %d", actorid, forplayerid);
			Iter_Remove(StreamedActor[forplayerid], actorid);
			Debug_Print2("Iter_OnActorStreamOut end");
			return ret;
		}

		#if defined _ALS_OnActorStreamOut
			#undef OnActorStreamOut
		#endif
		#define _ALS_OnActorStreamOut
		#define OnActorStreamOut(%0) CHAIN_PUBLIC:Iter_OnActorStreamOut(%0)
		CHAIN_FORWARD:Iter_OnActorStreamOut(actorid, forplayerid) = 1;
	#endif
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

#if defined SAMP_CONST_CORRECT || defined FIXES_TAG_CORRECT
	#define YSI_ADD_SIREN_TAG bool
#else
	#define YSI_ADD_SIREN_TAG _
#endif

#if _FOREACH_VEHICLES
	forward void:Iter_VehicleDo(bool:add, vehicleid);
	
	public void:Iter_VehicleDo(bool:add, vehicleid)
	{
		// Because there may be multiple scripts running, we need to tell all of
		// them when a vehicle is created or destroyed.
		if (add)
		{
			Iter_Add(Vehicle, vehicleid);
		}
		else
		{
			Iter_Remove(Vehicle, vehicleid);
		}
	}
	
	stock Iter_CreateVehicle(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, respawn_delay, YSI_ADD_SIREN_TAG:addSiren = false)
	{
		#if defined GetActorPos
			new
				ret = CreateVehicle(modelid, x, y, z, angle, color1, color2, respawn_delay, addSiren);
		#else
			#pragma unused addSiren
			new
				ret = CreateVehicle(modelid, x, y, z, angle, color1, color2, respawn_delay);
		#endif
		if (ret)
		{
			CallRemoteFunction(YSI_gsIter_VehicleDo, YSI_gcII, true, ret);
			#if _FOREACH_LOCALS
				Iter_Add(LocalVehicle, ret);
			#endif
		}
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
		if (ret)
		{
			CallRemoteFunction(YSI_gsIter_VehicleDo, YSI_gcII, true, ret);
			#if _FOREACH_LOCALS
				Iter_Add(LocalVehicle, ret);
			#endif
		}
		return ret;
	}
	
	#if defined _ALS_AddStaticVehicle
		#undef AddStaticVehicle
	#else
		#define _ALS_AddStaticVehicle
	#endif
	#define AddStaticVehicle Iter_AddStaticVehicle
	
	stock Iter_AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:angle, color1, color2, respawn_delay, YSI_ADD_SIREN_TAG:addSiren = false)
	{
		#if defined GetActorPos
			new
				ret = AddStaticVehicleEx(modelid, spawn_x, spawn_y, spawn_z, angle, color1, color2, respawn_delay, addSiren);
		#else
			#pragma unused addSiren
			new
				ret = AddStaticVehicleEx(modelid, spawn_x, spawn_y, spawn_z, angle, color1, color2, respawn_delay);
		#endif
		if (ret)
		{
			CallRemoteFunction(YSI_gsIter_VehicleDo, YSI_gcII, true, ret);
			#if _FOREACH_LOCALS
				Iter_Add(LocalVehicle, ret);
			#endif
		}
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
		CallRemoteFunction(YSI_gsIter_VehicleDo, YSI_gcII, false, vehicleid);
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

	#if _FOREACH_STREAMED
		public OnVehicleStreamIn(vehicleid, forplayerid)
		{
			Debug_Print1("Iter_OnVehicleStreamIn called: %d, %d", vehicleid, forplayerid);
			Iter_Add(StreamedVehicle[forplayerid], vehicleid);
			Debug_Print2("Iter_OnVehicleStreamIn end");
			return Iter_OnVehicleStreamIn(vehicleid, forplayerid);
		}

		#if defined _ALS_OnVehicleStreamIn
			#undef OnVehicleStreamIn
		#endif
		#define _ALS_OnVehicleStreamIn
		#define OnVehicleStreamIn(%0) CHAIN_PUBLIC:Iter_OnVehicleStreamIn(%0)
		CHAIN_FORWARD:Iter_OnVehicleStreamIn(vehicleid, forplayerid) = 1;

		public OnVehicleStreamOut(vehicleid, forplayerid)
		{
			new ret = Iter_OnVehicleStreamOut(vehicleid, forplayerid);
			Debug_Print1("Iter_OnVehicleStreamOut called: %d, %d", vehicleid, forplayerid);
			Iter_Remove(StreamedVehicle[forplayerid], vehicleid);
			Debug_Print2("Iter_OnVehicleStreamOut end");
			return ret;
		}

		#if defined _ALS_OnVehicleStreamOut
			#undef OnVehicleStreamOut
		#endif
		#define _ALS_OnVehicleStreamOut
		#define OnVehicleStreamOut(%0) CHAIN_PUBLIC:Iter_OnVehicleStreamOut(%0)
		CHAIN_FORWARD:Iter_OnVehicleStreamOut(vehicleid, forplayerid) = 1;
	#endif

	#if !defined PLAYER_STATE
		#define PLAYER_STATE: _:
	#endif
	public OnPlayerStateChange(playerid, PLAYER_STATE:newstate, PLAYER_STATE:oldstate)
	{
		new ret = Iter_OnPlayerStateChange(playerid, newstate, oldstate);

		if (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
		{
			Iter_Add(PlayersFromVehicles, playerid);
		}
		else if (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) 
		{
			Iter_Remove(PlayersFromVehicles, playerid);
		}
		return ret;
	}

	#if defined _ALS_OnPlayerStateChange
		#undef OnPlayerStateChange
	#endif
	#define _ALS_OnPlayerStateChange
	#define OnPlayerStateChange(%0,%1,%2) CHAIN_PUBLIC:Iter_OnPlayerStateChange(%0, %1, %2)
	CHAIN_FORWARD:Iter_OnPlayerStateChange(playerid, PLAYER_STATE:newstate, PLAYER_STATE:oldstate) = 1;
	
	iterfunc stock VehicleOccupant(vehicleid = INVALID_VEHICLE_ID, bool:includeDriver = true, bool:includePassenger = true)
	{
		if (includeDriver && includePassenger)
		{
			if (vehicleid == INVALID_VEHICLE_ID)
			{
				FOREACH__ (new i : PlayersFromVehicles)
				{
					YIELD__ return i;
				}
			}
			else
			{
				new
					vehicleSeatsOccupied, 
					vehicleModelSeats = Vehicle_Seats(vehicleid);
				FOREACH__ (new i : PlayersFromVehicles)
				{
					if (GetPlayerVehicleID(i) == vehicleid)
					{
						YIELD__ return i;
						if (++vehicleSeatsOccupied == vehicleModelSeats) 
						{
							return;
						}
					}
				}
			}
		}
		else if (includeDriver)
		{
			if (vehicleid == INVALID_VEHICLE_ID)
			{
				FOREACH__ (new i : PlayersFromVehicles)
				{
					if (GetPlayerState(i) == PLAYER_STATE_DRIVER)
					{
						YIELD__ return i;
					}
				}
			}
			else
			{
				FOREACH__ (new i : PlayersFromVehicles)
				{
					if (GetPlayerVehicleID(i) == vehicleid && GetPlayerState(i) == PLAYER_STATE_DRIVER)
					{
						YIELD__ return i;
						// You can only have one driver.
						return;
					}
				}
			}
		}
		else if (includePassenger)
		{
			if (vehicleid == INVALID_VEHICLE_ID)
			{
				FOREACH__ (new i : PlayersFromVehicles)
				{
					if (GetPlayerState(i) == PLAYER_STATE_PASSENGER)
					{
						YIELD__ return i;
					}
				}
			}
			else
			{
				new
					vehicleSeatsOccupied, 
					vehicleModelSeats = Vehicle_Seats(vehicleid) - 1;
				if (vehicleModelSeats == 0)
				{
					// Can't have passengers.
					return;
				}
				FOREACH__ (new i : PlayersFromVehicles)
				{
					if (GetPlayerVehicleID(i) == vehicleid && GetPlayerState(i) == PLAYER_STATE_PASSENGER)
					{
						YIELD__ return i;
						if (++vehicleSeatsOccupied == vehicleModelSeats) 
						{
							return;
						}
					}
				}
			}
		}
		// Else no loop - we want everyone who is in a vehicle, but not a driver or
		// a passenger.  I think that limits us to captives in the boot and Sideshow
		// Bob strapped to the underside.
	}
	#define Iterator@VehicleOccupant iteryield
	
	iterfunc stock VehiclePassenger(vehicleid = INVALID_VEHICLE_ID)
	{
		Iter_Func@VehicleOccupant(vehicleid, false, true);
	}
	#define Iterator@VehiclePassenger iteryield
	
	iterfunc stock VehicleDriver(vehicleid = INVALID_VEHICLE_ID)
	{
		Iter_Func@VehicleOccupant(vehicleid, true, false);
	}
	#define Iterator@VehicleDriver iteryield
#endif

