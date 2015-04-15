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
		Itter_AddInternal - Add a value to an iterator.
		Itter_RemoveInternal - Remove a value from an iterator.
		Itter_RandomInternal - Get a random item from an iterator.
		Itter_FreeInternal - Gets the first free slot in the iterator.
		Itter_InitInternal - Initialises a multi-dimensional iterator.
	Static:
		-
	Inline:
		Itter_Create - Create a new iterator value set.
		Itter_Add - Wraps Itter_AddInternal.
		Itter_Remove - Wraps Itter_RemoveInternal.
		Itter_Random - Wraps Itter_RandomInternal.
		Itter_Count - Gets the number of items in an iterator.
		Itter_Debug - Wraps around Itter_ShowArray.
		Itter_Free - Wraps around Itter_FreeInternal.
		Itter_Create2 - Create a new iterator array value set.
		Itter_Add2 - Wraps Itter_AddInternal for arrays.
		Itter_Remove2 - Wraps Itter_RemoveInternal for arrays.
		Itter_Random2 - Wraps Itter_RandomInternal for arrays.
		Itter_Count2 - Gets the number of items in an iterator array.
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
#define _Y_ITERATE_LOCAL_VERSION        33

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

#include "..\YSI_Internal\y_natives"
#include "..\YSI_Core\y_debug"

#if defined SendChat || defined FOREACH_NO_PLAYERS
	#define BOTSYNC_IS_BOT     (true)
#endif

#if defined IsPlayerNPC
	#define _FOREACH_BOT
#endif

#if defined YSI_ITTER_NO_SORT
	#error YSI_ITTER_NO_SORT is no longer supported by foreach.
#endif

#if !defined BOTSYNC_IS_BOT
	forward Itter_OPDCInternal(playerid);
#endif

/*

    88      a8P                                                                           88            
    88    ,88'                                                                            88            
    88  ,88"                                                                              88            
    88,d88'      ,adPPYba, 8b       d8 8b      db      d8  ,adPPYba,  8b,dPPYba,  ,adPPYb,88 ,adPPYba,  
    8888"88,    a8P_____88 `8b     d8' `8b    d88b    d8' a8"     "8a 88P'   "Y8 a8"    `Y88 I8[    ""  
    88P   Y8b   8PP"""""""  `8b   d8'   `8b  d8'`8b  d8'  8b       d8 88         8b       88  `"Y8ba,   
    88     "88, "8b,   ,aa   `8b,d8'     `8bd8'  `8bd8'   "8a,   ,a8" 88         "8a,   ,d88 aa    ]8I  
    88       Y8b `"Ybbd8"'     Y88'        YP      YP      `"YbbdP"'  88          `"8bbdP"Y8 `"YbbdP"'  
                               d8'                                                                      
                              d8'                                                                       

*/

/**--------------------------------------------------------------------------**\
Array:
	Iterator
</returns>
<remarks>
	Creates a new iterator start/array pair.
</remarks>
\**--------------------------------------------------------------------------**/

#define Iterator:%1<%2> Iterator@%1[_:_Y_ITER_D1:_Y_ITER_D2:((%2)+1)]={0,1,...}_Y_ITER_D4$,YSII_Cg@%1 _Y_ITER_D4$
#define iterator%0<%1> new Iterator:%0<%1>

/**--------------------------------------------------------------------------**\
<summary>foreach</summary>
<param name="data">Data to itterate through.</param>
<param name="as">Variable to set value to.</param>
<returns>
	-
</returns>
<remarks>
	Not exactly the same as PHP foreach, just itterates through a list and
	returns the value of the current slot but uses that slot as the next index
	too.  Variables must be in the form @YSII_<gname>S for the start index and
	@YSII_<gname>A for the data array where <name> is what's entered in data.
</remarks>
\**--------------------------------------------------------------------------**/

#define foreach(%0) for(new Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||%0|||)

/*

    88b           d88            88                       db        88888888ba  88  
    888b         d888            ""                      d88b       88      "8b 88  
    88`8b       d8'88                                   d8'`8b      88      ,8P 88  
    88 `8b     d8' 88 ,adPPYYba, 88 8b,dPPYba,         d8'  `8b     88aaaaaa8P' 88  
    88  `8b   d8'  88 ""     `Y8 88 88P'   `"8a       d8YaaaaY8b    88""""""'   88  
    88   `8b d8'   88 ,adPPPPP88 88 88       88      d8""""""""8b   88          88  
    88    `888'    88 88,    ,88 88 88       88     d8'        `8b  88          88  
    88     `8'     88 `"8bbdP"Y8 88 88       88    d8'          `8b 88          88  

*/

/**--------------------------------------------------------------------------**\
<summary>Itter_Init2</summary>
<param name="itter">Name of the iterator array to initialise.</param>
<returns>
	-
</returns>
<remarks>
	Wrapper for Itter_InitInternal.

native Iter_Init(IteratorArray:Name[]<>);

</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_Init Itter_Init
#define Itter_Init(%1) Itter_InitInternal(_Y_ITER_ARRAY$%1$YSII_Ag,_Y_ITER_MAYBE_ARRAY(%1)+1,_Y_ITER_MAYBE_ARRAY(%1[]))

/**--------------------------------------------------------------------------**\
<summary>Itter_Add</summary>
<param name="itter">Name of the iterator to add the data to.</param>
<param name="value">Value to add to the iterator.</param>
<returns>
	-
</returns>
<remarks>
	Wrapper for Itter_AddInternal.

native Iter_Add(Iterator:Name<>, value);

</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_Add Itter_Add
#define Itter_Add(%1,%2) Itter_AddInternal(YSII_Cg@%1,_Y_ITER_ARRAY$%1$YSII_Ag,%2,_Y_ITER_MAYBE_ARRAY(%1))

/**--------------------------------------------------------------------------**\
<summary>Itter_Remove</summary>
<param name="itter">Name of the iterator to remove data from.</param>
<param name="value">Data to remove.</param>
<returns>
	-
</returns>
<remarks>
	Wrapper for Itter_RemoveInternal.

native Iter_Remove(Iterator:Name<>, value);

</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_Remove Itter_Remove
#define Itter_Remove(%1,%2) Itter_RemoveInternal(YSII_Cg@%1,_Y_ITER_ARRAY$%1$YSII_Ag,%2,_Y_ITER_MAYBE_ARRAY(%1))

/**--------------------------------------------------------------------------**\
<summary>Itter_Free</summary>
<param name="itter">Name of the iterator to get the first free slot in.</param>
<returns>
	-
</returns>
<remarks>
	Wrapper for Itter_FreeInternal.

native Iter_Free(Iterator:Name<>);

</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_Free Itter_Free
#define Itter_Free(%1) Itter_FreeInternal(_Y_ITER_ARRAY$%1$YSII_Ag,_Y_ITER_MAYBE_ARRAY(%1))

/**--------------------------------------------------------------------------**\
<summary>Itter_Contains</summary>
<param name="itter">Name of the iterator to check membership of.</param>
<param name="value">Value to check.</param>
<returns>
	-
</returns>
<remarks>
	Checks if the given value is in the given iterator.

native Iter_Remove(Iterator:Name<>, value);

</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_Contains Itter_Contains
#define Itter_Contains(%1,%2) Itter_ContainsInternal(_Y_ITER_ARRAY$%1$YSII_Ag,%2,_Y_ITER_MAYBE_ARRAY(%1))

/**--------------------------------------------------------------------------**\
<summary>Itter_SafeRemove</summary>
<param name="itter">Name of the iterator to remove data from.</param>
<param name="value">Data to remove.</param>
<param name="next">Container for the pointer to the next element.</param>
<returns>
	-
</returns>
<remarks>
	Wrapper for Itter_SafeRemoveInternal.  Common use:
	
	Iter_SafeRemove(iter, i, i);

native Iter_SafeRemove(Iterator:Name<>, value, &next);

</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_SafeRemove Itter_SafeRemove
#define Itter_SafeRemove(%1,%2,%3) Itter_SafeRemoveInternal(YSII_Cg@%1,_Y_ITER_ARRAY$%1$YSII_Ag,%2,%3,_Y_ITER_MAYBE_ARRAY(%1))

/**--------------------------------------------------------------------------**\
<summary>Itter_Random</summary>
<param name="itter">Name of the iterator to get a random slot from.</param>
<returns>
	-
</returns>
<remarks>
	Wrapper for Itter_RandomInternal.

native Iter_Random(Iterator:Name<>);

</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_Random Itter_Random
#define Itter_Random(%1) Itter_RandomInternal(YSII_Cg@%1,_Y_ITER_ARRAY$%1$YSII_Ag,_Y_ITER_MAYBE_ARRAY(%1))

/**--------------------------------------------------------------------------**\
<summary>Itter_Count</summary>
<param name="itter">Name of the iterator to get a random slot from.</param>
<returns>
	-
</returns>
<remarks>
	Returns the number of items in this iterator.

native Iter_Count(Iterator:Name<>);

</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_Count Itter_Count
#define Itter_Count(%1) (YSII_Cg@%1 _Y_ITER_D3,)

/**--------------------------------------------------------------------------**\
<summary>Itter_Clear</summary>
<param name="iter">Name of the iterator to empty.</param>
<returns>
	-
</returns>
<remarks>
	Wrapper for Itter_ClearInternal.

native Iter_Clear(IteratorArray:Name[]<>);

</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_Clear Itter_Clear
#define Itter_Clear(%1) Itter_ClearInternal(YSII_Cg@%1,_Y_ITER_ARRAY$%1$YSII_Ag,_Y_ITER_MAYBE_ARRAY(%1))

/**--------------------------------------------------------------------------**\
<summary>Itter_FastClear</summary>
<param name="iter">Name of the iterator to empty.</param>
<returns>
	-
</returns>
<remarks>
	Uses a static array copy to blank the iterator instead of a loop.

native Iter_FastClear(IteratorArray:Name[]<>);

</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_FastClear Itter_FastClear
#define Itter_FastClear(%1); {static __CLEAR[_:_Y_ITER_C1:(sizeof %1@YSII_Ag+1-1)]={(_:_Y_ITER_C1:(sizeof %1@YSII_Ag-1))*2,(_:_Y_ITER_C1:(sizeof %1@YSII_Ag-1))*2-1,...};(YSII_Cg@%1=0 _Y_ITER_D3,),(_Y_ITER_ARRAY$%1$YSII_Ag=__CLEAR);}

/*

    88888888888                                                     db        88888888ba  88  
    88                        ,d                                   d88b       88      "8b 88  
    88                        88                                  d8'`8b      88      ,8P 88  
    88aaaaa     8b,     ,d8 MM88MMM 8b,dPPYba, ,adPPYYba,        d8'  `8b     88aaaaaa8P' 88  
    88"""""      `Y8, ,8P'    88    88P'   "Y8 ""     `Y8       d8YaaaaY8b    88""""""'   88  
    88             )888(      88    88         ,adPPPPP88      d8""""""""8b   88          88  
    88           ,d8" "8b,    88,   88         88,    ,88     d8'        `8b  88          88  
    88888888888 8P'     `Y8   "Y888 88         `"8bbdP"Y8    d8'          `8b 88          88  

*/

/**--------------------------------------------------------------------------**\
<summary>Iter_Begin</summary>
<param name="iter">Name of the iterator to get the start of.</param>
<returns>
	-
</returns>
<remarks>
	Gets a point BEFORE the start of the iterator (the theoretical beginning).
</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_Begin(%1) (_Y_ITER_MAYBE_ARRAY(%1))
#define Itter_Begin(%1) (_Y_ITER_MAYBE_ARRAY(%1))

/**--------------------------------------------------------------------------**\
<summary>Iter_End</summary>
<param name="iter">Name of the iterator to get the end of.</param>
<returns>
	-
</returns>
<remarks>
	Gets a point AFTER the end of the iterator (think "MAX_PLAYERS").
</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_End(%1) (_Y_ITER_MAYBE_ARRAY(%1))
#define Itter_End(%1) (_Y_ITER_MAYBE_ARRAY(%1))

/**--------------------------------------------------------------------------**\
<summary>Iter_First</summary>
<param name="iter">Name of the iterator to get the first valid element in.</param>
<returns>
	-
</returns>
<remarks>
	Gets the first element in an iterator.
</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_First(%1) (_Y_ITER_ARRAY$%1$YSII_Ag[_Y_ITER_MAYBE_ARRAY(%1)])
#define Itter_First(%1) (_Y_ITER_ARRAY$%1$YSII_Ag[_Y_ITER_MAYBE_ARRAY(%1)])

/**--------------------------------------------------------------------------**\
<summary>Iter_Last</summary>
<param name="iter">Name of the iterator to</param>
<returns>
	-
</returns>
<remarks>
	Gets the last element in an iterator.  Works by getting the previous item
	from the one BEFORE the first element (i.e. the one before the sentinel).
</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_Last(%1) Itter_PrevInternal(_Y_ITER_ARRAY$%1$YSII_Ag,_Y_ITER_MAYBE_ARRAY(%1),_Y_ITER_MAYBE_ARRAY(%1))
#define Itter_Last(%1) Itter_PrevInternal(_Y_ITER_ARRAY$%1$YSII_Ag,_Y_ITER_MAYBE_ARRAY(%1),_Y_ITER_MAYBE_ARRAY(%1))

/**--------------------------------------------------------------------------**\
<summary>Iter_Next</summary>
<param name="iter">Name of the iterator to get the next element in.</param>
<param name="cur">The current element.</param>
<returns>
	-
</returns>
<remarks>
	Gets the element in an interator after the current one.
</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_Next(%1,%2) (_Y_ITER_ARRAY$%1$YSII_Ag[(%2)])
#define Itter_Next(%1,%2) (_Y_ITER_ARRAY$%1$YSII_Ag[(%2)])

/**--------------------------------------------------------------------------**\
<summary>Iter_Prev</summary>
<param name="iter">Name of the iterator to get the previous element in.</param>
<param name="cur">The current element.</param>
<returns>
	-
</returns>
<remarks>
	Gets the element in an iterator before the current one.  Slow.
</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_Prev(%1,%2) Itter_PrevInternal(_Y_ITER_ARRAY$%1$YSII_Ag,_Y_ITER_MAYBE_ARRAY(%1),(%2))
#define Itter_Prev(%1,%2) Itter_PrevInternal(_Y_ITER_ARRAY$%1$YSII_Ag,_Y_ITER_MAYBE_ARRAY(%1),(%2))

/**--------------------------------------------------------------------------**\
<summary>Iter_InternalArray</summary>
<param name="iter">Name of the iterator to get the true name of.</param>
<returns>
	-
</returns>
<remarks>
	Accesses the internal array of an iterator.
</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_InternalArray(%1) (_Y_ITER_ARRAY$%1$YSII_Ag)
#define Itter_InternalArray(%1) (_Y_ITER_ARRAY$%1$YSII_Ag)

/**--------------------------------------------------------------------------**\
<summary>Iter_InternalSize</summary>
<param name="iter">Name of the iterator to get the true size of.</param>
<returns>
	-
</returns>
<remarks>
	Accesses the internal size of an iterator.
</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_InternalSize(%1) (_Y_ITER_MAYBE_ARRAY(%1)+1)
#define Itter_InternalSize(%1) (_Y_ITER_MAYBE_ARRAY(%1)+1)

/**--------------------------------------------------------------------------**\
<summary>Iter_Size</summary>
<param name="iter">Name of the iterator to get the size of.</param>
<returns>
	-
</returns>
<remarks>
	Accesses the internal size of an iterator.
</remarks>
\**--------------------------------------------------------------------------**/

#define Iter_Size(%1) (_Y_ITER_MAYBE_ARRAY(%1))
#define Itter_Size(%1) (_Y_ITER_MAYBE_ARRAY(%1))

/*

    88b           d88                                                         
    888b         d888                                                         
    88`8b       d8'88                                                         
    88 `8b     d8' 88 ,adPPYYba,  ,adPPYba, 8b,dPPYba,  ,adPPYba,  ,adPPYba,  
    88  `8b   d8'  88 ""     `Y8 a8"     "" 88P'   "Y8 a8"     "8a I8[    ""  
    88   `8b d8'   88 ,adPPPPP88 8b         88         8b       d8  `"Y8ba,   
    88    `888'    88 88,    ,88 "8a,   ,aa 88         "8a,   ,a8" aa    ]8I  
    88     `8'     88 `"8bbdP"Y8  `"Ybbd8"' 88          `"YbbdP"'  `"YbbdP"'  

*/

// This now uses "$" not ":" because it is ALWAYS stripped out (it isn't a tag
// based macro that may not be detected), and that way we can detect the "$" in
// "C2" even when there is a custom tag involved.  The second "$" allows us to
// pick up all array subscripts at once without recursion.  I'm not overly happy
// about the trailing ")" on the macros, but I can't see any other way atm.
#define _Y_ITER_ARRAY$ _:_Y_ITER_C0:_Y_ITER_C3:
#define _Y_ITER_C0:%0[%1$YSII_%4g%5) %0$YSII_%4g[%1%5)

// Find out if the passed iterator is multi-dimensional or an old function.
#define _Y_ITER_FOREACH_SIZE(%1) _:_Y_ITER_C1:_Y_ITER_C2:(sizeof %1@YSII_Ag-1)

// This macro detects multi-dimensional iterator arrays and moves the square
// brackets to the correct location AFTER the iterator name (not in the middle).
// If we get anything in "%8" don't bother putting it back as we can no longer
// match against it because we have matched against "C1" instead.
#define _Y_ITER_C1:%8(%0[%1]%2@YSII_Ag%9-1) _Y_ITER_C1:(%0%2@YSII_Ag[]%9-1)

// I will deprecate these later.  The code to do so is in revision c9ca7fd.
#define _Y_ITER_C2:(sizeof%0(%1)@YSII_Ag-1);_:(%2=%9$%3(%4)$YSII_Ag[%5])!=_Y_ITER_MAYBE_ARRAY(%6);) _Y_ITER_C4:(sizeof %3@YSII_Ag-1);(sizeof %3@YSII_Ag-1)!=_:(%2=%3@YSII_Ag[%4][%5]);)

#define _Y_ITER_C4:%9;%8!=_:(%2=%3[][%5]);) %9;%9!=_:(%2=%3[%5]);)

#define _Y_ITER_C5:%9[%1]%2(%0(%5));) (%0(%5%1));)
#define _Y_ITER_C6:_Y_ITER_C5:%9[%1]%2[%3]%4(%0(%5));) _Y_ITER_C6:_Y_ITER_C5:%2[%3]%4(%0(%5%1,));)

#define @iterfunc%1()%7:(%0=%8)%9) YSI_NULL_ITERATOR-3);-1!=_:_Y_ITER_C6:_Y_ITER_C5:%8(%0=%1@YSII_Ag());)
#define iterfunc%0(%1) %0@YSII_Ag(%1)

// Check if this is an array or a single variable.
#define _Y_ITER_MAYBE_ARRAY(%1) _:_Y_ITER_C1:(sizeof %1@YSII_Ag-1)



// Remove trailing spaces.  This looks really unsafe because of the "%0\32;"
// allowing anything to come before the space, but it would have to be
// "anything" not text immediately following a "YSII_X@" prefix.
#define Iterator@%0\32;%1$ Iterator@%0%1$
#define YSII_Cg@%0\32;%1$ YSII_Cg@%0%1$

// A nice "match" symbol that we can scan for, then remove after it is used.
#define _Y_ITER_D4$

// Detect array declarations: "Iterator:X[20]<4>", "Iterator:X<10, 4>", and the
// frankly silly "Iterator:X[20]<10, 4>".
#define _Y_ITER_D1:_Y_ITER_D2:((%0,%1)+1)]%2$,YSII_Cg@%9$ _Y_ITER_D2:((%0)+(%1))]_Y_ITER_D4$,YSII_Mg@%9$[%0]
#define _Y_ITER_D2:%0]%2$%9[%3$ %0]%9[%3$

// Special "sizeof" that strips subscripts.  "$" prevents "sizeof" recursion.
#define _SIZEOF_REP:%0(%1[%2]%3$%4) _SIZEOF_REP:%0(%1%3$%4[])
#define _SIZEOF_END$
#define SIZEOF(%0) (_:_SIZEOF_REP:sizeof _SIZEOF_END$(%0 _SIZEOF_END$))

// // Get a reference to the count store.
// #define _ITER_COUNT(%0) YSII_Cg@%0 _Y_ITER_D4$
// #define _ITER_MULTI(%0,%2) YSII_Mg@%0[%2] _Y_ITER_D4$

// // Get the actual array storing the data.
// #define _ITER_ARRAY(%0) Iterator@%0 _Y_ITER_D4$

// // Get the number of elements within the iterator.
// #define _ITER_SLOTS(%0) (SIZEOF (Iterator@%0) - SIZEOF (YSII_Mg@%0))
// #define _ITER_SIZE(%0) (SIZEOF (Iterator@%0) - 1)

// // Calculate the start point for this multi-iterator.
// #define _ITER_START(%0,%1) _ITER_SIZE(%0) - (%1)

// y_iterate parser.  Takes an array input, and splits up all the components.
#define _ITER<%0>(%1) (_:_Y_ITER_P0:_Y_ITER_P1:$_Y_ITER_DO<%0>(%1))

// Separate "<>"s.
#define _Y_ITER_P0:%7$%8<%9>(%0<%2>%1) _Y_ITER_P4:_Y_ITER_P5:_Y_ITER_P6:$%8_A<%9>(%2,%0%1)
#define _Y_ITER_P1:%7$%8<%9>(%0) _Y_ITER_P2:_Y_ITER_P3:$%8_B<%9>(%0)

// Add extra parameters.
#define _Y_ITER_P2:%7$%8<%9>(%0,%1)    %8<%9>(%0,%1)
#define _Y_ITER_P3:%7$%8<%9>(%0)       %8<%9>(%0,0)
#define _Y_ITER_P4:%7$%8<%9>(%0,%1,%2) %8<%9>(%0,%1,%2)
#define _Y_ITER_P5:%7$%8<%9>(%0,%1)    %8<%9>(%0,%1,0)
#define _Y_ITER_P6:%7$%8<%9>(%0)       %8<%9>(%0,0,0)

// Parameters:
//  
//  %0 - Iterator name, fully qualified.
//  %1 - Value.
//  %2 - Multi-iterator position.
//  
// #define _Y_ITER_DO_A<%8>(%2,%0,%1) Iter_%8InternalA(_ITER_MULTI(%0, %2), _ITER_ARRAY(%0), _ITER_START(%0, %2), _ITER_SLOTS(%0), %1)
// #define _Y_ITER_DO_B<%8>(%0,%1)    Iter_%8InternalB(_ITER_COUNT(%0), _ITER_ARRAY(%0), _ITER_SIZE(%0), %1)

#define _Y_ITER_DO_A<%8>(%2,%0,%1) Iter_%8InternalA(YSII_Mg@%0[%2], Iterator@%0, (SIZEOF (Iterator@%0) - 1) - (%2), SIZEOF (Iterator@%0) - SIZEOF (YSII_Mg@%0), %1 _Y_ITER_D4$)
#define _Y_ITER_DO_B<%8>(%0,%1)    Iter_%8InternalB(YSII_Cg@%0    , Iterator@%0, (SIZEOF (Iterator@%0) - 1)                                                  , %1 _Y_ITER_D4$)

#define Iter_Add    _ITER<Add>
#define Iter_Remove _ITER<Remove>
#define Iter_Init   _ITER<Init>
#define Iter_Count  _ITER<Count>
#define Iter_Extra  _ITER<Extra>

/**--------------------------------------------------------------------------**\
<summary>Itter_Create2</summary>
<param name="name">iterator identifier.</param>
<param name="size0">Number of iterators.</param>
<param name="size1">Number of items per iterator.</param>
<returns>
	-
</returns>
<remarks>
	Creates a new array of iterator start/array pair.
</remarks>
\**--------------------------------------------------------------------------**/

// If this ever changes, update the size reference in y_users.
#define IteratorArray Iterator

/**--------------------------------------------------------------------------**\
	The workings of these macros are very extensively documented at:
	
		http://forum.sa-mp.com/showpost.php?p=2823668
	
\**--------------------------------------------------------------------------**/

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
#define Y_FOREACH_SEVENTH|||%9Y_FOREACH_SIXTH;%0|||%1|||%2||| new %0:%1=%0:_Y_ITER_FOREACH_SIZE(%2);_:(%1=%0:_Y_ITER_ARRAY$%2$YSII_Ag[%1])!=_Y_ITER_MAYBE_ARRAY(%2);

// This is called when there aren't.
#define Y_FOREACH_SIXTH;%0|||Y_FOREACH_SEVENTH|||%2||| %0=_Y_ITER_FOREACH_SIZE(%2);_:(%0=_Y_ITER_ARRAY$%2$YSII_Ag[%0])!=_Y_ITER_MAYBE_ARRAY(%2);

// This is called if "%1" didn't have "new" at the start.
#define Y_FOREACH_FIFTH|||Y_FOREACH_FOURTH|||%1:%2||| _Y_ITER_FOREACH_SIZE(%2);_:(%1=_Y_ITER_ARRAY$%2$YSII_Ag[%1])!=_Y_ITER_MAYBE_ARRAY(%2);

// This is the old version, but DON'T add "new" because that already exists from
// the failed "new" macro call above.
#define Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||%1,%2||| %2=_Y_ITER_FOREACH_SIZE(%1);_:(%2=_Y_ITER_ARRAY$%1$YSII_Ag[%2])!=_Y_ITER_MAYBE_ARRAY(%1);

/**--------------------------------------------------------------------------**\
<summary>foreachex</summary>
<param name="data">Data to itterate through.</param>
<param name="as">Variable to set value to.</param>
<returns>
	-
</returns>
<remarks>
	Similar to foreach but doesn't declare a new variable for the iterator.
</remarks>
\**--------------------------------------------------------------------------**/

#define foreachex(%1,%2) foreach(%2:%1)

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
		
		#define YSII_Cg@NPC YSII_Cg@Bot
		#define Iterator@NPC Iterator@Bot
	#endif
#endif

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
	YSI_gsOnGameModeInit[] = "Itter_OnGameModeInit",
	YSI_gsSpecifier@[] = "";

// This is a hack to build the constant number "-1" with "sizeof".
stock const
	YSI_NULL_ITERATOR[2]; // NULL target only used for "sizeof".

/**--------------------------------------------------------------------------**\
<summary>Itter_OPDCInternal</summary>
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
<summary>Itter_OnFilterScriptInit</summary>
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
			YSII_Cg@Bot = _Y_ITER_C9:0;
			YSII_Cg@Character = _Y_ITER_C9:0;
			new
				lastBot = MAX_PLAYERS,
				lastCharacter = MAX_PLAYERS;
		#endif
		YSII_Cg@Player = _Y_ITER_C9:0;
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
						++YSII_Cg@Player;
						lastPlayer = i;
					}
					#if !defined FOREACH_NO_BOTS
						else
						{
							Bot@YSII_Ag[lastBot] = i;
							++YSII_Cg@Bot;
							lastBot = i;
						}
						#pragma tabsize 4
						Character@YSII_Ag[lastCharacter] = i;
						++YSII_Cg@Character;
						lastCharacter = i;
					#endif
				#else
					Player@YSII_Ag[lastPlayer] = i;
					++YSII_Cg@Player;
					lastPlayer = i;
				#endif
			}
			else
			{
				#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
					Bot@YSII_Ag[i] = MAX_PLAYERS + 1;
					Character@YSII_Ag[i] = MAX_PLAYERS + 1;
				#endif
				Player@YSII_Ag[i] = MAX_PLAYERS + 1;
			}
		}
		#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
			Bot@YSII_Ag[lastPlayer] = MAX_PLAYERS;
			Character@YSII_Ag[lastPlayer] = MAX_PLAYERS;
		#endif
		Player@YSII_Ag[lastPlayer] = MAX_PLAYERS;
		#if defined Itter_OnFilterScriptInit
			Itter_OnFilterScriptInit();
		#endif
		return 1;
	}
	
	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit Itter_OnFilterScriptInit
	#if defined Itter_OnFilterScriptInit
		forward Itter_OnFilterScriptInit();
	#endif
#endif

/**--------------------------------------------------------------------------**\
<summary>Itter_OnGameModeInit</summary>
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
		if (!YSII_Cg@Player)
		{
			#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
				CallLocalFunction(YSI_gsOnGameModeInit, YSI_gsSpecifier@, YSII_Cg@Bot, YSII_Cg@Character, YSII_Cg@Player);
			#else
				CallLocalFunction(YSI_gsOnGameModeInit, YSI_gsSpecifier@, YSII_Cg@Player);
			#endif
			#if defined _YSI_SPECIAL_DEBUG
				for (new i = 0; i != MAX_PLAYERS; ++i)
				{
					Player@YSII_Ag[i] = i + 1;
				}
				Player@YSII_Ag[MAX_PLAYERS] = 0;
				YSII_Cg@Player = _Y_ITER_C9:MAX_PLAYERS;
			#endif
			P:1("Iter_OnGameModeInit: first");
			return 1;
		}
		// Do the forward iterator list.
		#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
			YSII_Cg@Bot = _Y_ITER_C9:0;
			Bot@YSII_Ag[MAX_PLAYERS] = MAX_PLAYERS;
			Character@YSII_Ag[MAX_PLAYERS] = MAX_PLAYERS;
			YSII_Cg@Character = _Y_ITER_C9:0;
			new
				lastBot = MAX_PLAYERS,
				lastCharacter = MAX_PLAYERS;
		#endif
		YSII_Cg@Player = _Y_ITER_C9:0;
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
						++YSII_Cg@Player;
						lastPlayer = i;
					}
					#if !defined FOREACH_NO_BOTS
						else
						{
							Bot@YSII_Ag[lastBot] = i;
							++YSII_Cg@Bot;
							lastBot = i;
						}
						#pragma tabsize 4
						Character@YSII_Ag[lastCharacter] = i;
						++YSII_Cg@Character;
						lastCharacter = i;
					#endif
				#else
					Player@YSII_Ag[lastPlayer] = i;
					++YSII_Cg@Player;
					lastPlayer = i;
				#endif
			}
			else
			{
				#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
					Bot@YSII_Ag[i] = MAX_PLAYERS + 1;
					Character@YSII_Ag[i] = MAX_PLAYERS + 1;
				#endif
				Player@YSII_Ag[i] = MAX_PLAYERS + 1;
			}
		}
		#if defined _FOREACH_BOT && !defined FOREACH_NO_BOTS
			Bot@YSII_Ag[lastPlayer] = MAX_PLAYERS;
			Character@YSII_Ag[lastPlayer] = MAX_PLAYERS;
		#endif
		Player@YSII_Ag[lastPlayer] = MAX_PLAYERS;
		P:1("Iter_OnGameModeInit: lastplayer = %d", lastPlayer);
		CallLocalFunction(YSI_gsOnGameModeInit, YSI_gsSpecifier@);
		#if defined _YSI_SPECIAL_DEBUG
			for (new i = 0; i != MAX_PLAYERS; ++i)
			{
				Player@YSII_Ag[i] = i + 1;
			}
			Player@YSII_Ag[MAX_PLAYERS] = 0;
			YSII_Cg@Player = _Y_ITER_C9:MAX_PLAYERS;
		#endif
		return 1;
	}
	
	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit Itter_OnGameModeInit
	#if defined Itter_OnGameModeInit
		forward Itter_OnGameModeInit();
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
<summary>Itter_OnPlayerConnect</summary>
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
		P:2("Iter_OnPlayerConnect end");
		#if defined Itter_OnPlayerConnect
			Itter_OnPlayerConnect(playerid);
		#endif
		return 1;
	}
	
	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif
	#define OnPlayerConnect Itter_OnPlayerConnect
	#if defined Itter_OnPlayerConnect
		forward Itter_OnPlayerConnect(playerid);
	#endif
#endif

/**--------------------------------------------------------------------------**\
<summary>Itter_OnPlayerDisconnect</summary>
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
		SetTimerEx("Itter_OPDCInternal", 0, false, "i", playerid);
		#if defined Itter_OnPlayerDisconnect
			Itter_OnPlayerDisconnect(playerid, reason);
		#endif
		return 1;
	}
	
	#if defined _ALS_OnPlayerDisconnect
		#undef OnPlayerDisconnect
	#else
		#define _ALS_OnPlayerDisconnect
	#endif
	#define OnPlayerDisconnect Itter_OnPlayerDisconnect
	#if defined Itter_OnPlayerDisconnect
		forward Itter_OnPlayerDisconnect(playerid, reason);
	#endif
#endif

/*

           db        88888888ba  88      ,ad8888ba,                       88             
          d88b       88      "8b 88     d8"'    `"8b                      88             
         d8'`8b      88      ,8P 88    d8'                                88             
        d8'  `8b     88aaaaaa8P' 88    88             ,adPPYba,   ,adPPYb,88  ,adPPYba,  
       d8YaaaaY8b    88""""""'   88    88            a8"     "8a a8"    `Y88 a8P_____88  
      d8""""""""8b   88          88    Y8,           8b       d8 8b       88 8PP"""""""  
     d8'        `8b  88          88     Y8a.    .a8P "8a,   ,a8" "8a,   ,d88 "8b,   ,aa  
    d8'          `8b 88          88      `"Y8888Y"'   `"YbbdP"'   `"8bbdP"Y8  `"Ybbd8"'  

*/

/**--------------------------------------------------------------------------**\
<summary>Itter_RandomInternal</summary>
<param name="count">Number of items in the iterator.</param>
<param name="array[]">iterator data.</param>
<param name="size">Size of the iterator.</param>
<returns>
	-
</returns>
<remarks>
	Returns a random value from an iterator.
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>Itter_FreeInternal</summary>
<param name="count">Number of items in the iterator.</param>
<param name="array[]">iterator data.</param>
<param name="size">Size of the iterator.</param>
<returns>
	-
</returns>
<remarks>
	Finds the first free slot in the iterator.  iterators now HAVE to be
	sorted for this function to work correctly as it uses that fact to decide
	wether a slot is unused or the last one.  If you want to use the slot
	straight after finding it the iterator will need to re-find it to add in
	the data.
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>Itter_AddInternal</summary>
<param name="&start">Array start index.</param>
<param name="&count">Number of items in the iterator.</param>
<param name="array[]">iterator data.</param>
<param name="value">Item to add.</param>
<returns>
	-
</returns>
<remarks>
	Adds a value to a given iterator set.  Now detects when you try and add the
	last item multiple times, as well as all the other items.  Now simplified even
	further with the new internal representation.
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>Itter_RemoveInternal</summary>
<param name="&count">Number of items in the iterator.</param>
<param name="array[]">iterator data.</param>
<param name="value">Item to remove.</param>
<returns>
	-
</returns>
<remarks>
	Removes a value from an iterator.
</remarks>
\**--------------------------------------------------------------------------**/

stock
	Itter_RemoveInternal(&count, array[], value, size)
{
	new
		last;
	return Itter_SafeRemoveInternal(count, array, value, last, size);
}

/**--------------------------------------------------------------------------**\
<summary>Itter_SafeRemoveInternal</summary>
<param name="&count">Number of items in the iterator.</param>
<param name="array[]">Iterator data.</param>
<param name="back[]">Reverse iterator data.</param>
<param name="value">Item to remove.</param>
<param name="&last">Pointer in which to store the last pointer.</param>
<returns>
	-
</returns>
<remarks>
	Removes a value from an iterator safely.
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>Itter_ContainsInternal</summary>
<param name="array[]">iterator data.</param>
<param name="value">Item to check.</param>
<param name="size">Size of the iterator.</param>
<returns>
	-
</returns>
<remarks>
	Checks if this item is in the iterator.
</remarks>
\**--------------------------------------------------------------------------**/

stock
	Itter_ContainsInternal(array[], value, size)
{
	return 0 <= value < size && array[value] <= size;
}

/**--------------------------------------------------------------------------**\
<summary>Itter_ClearInternal</summary>
<param name="&count">Number of items in the iterator.</param>
<param name="array[]">iterator data.</param>
<param name="back[]">Reverse data.</param>
<param name="size">Size of the iterator.</param>
<returns>
	-
</returns>
<remarks>
	Resets an iterator.
</remarks>
\**--------------------------------------------------------------------------**/

stock
	Itter_ClearInternal(&count, array[], size)
{
	for (new i = 0, t = size * 2; i < size; )
	{
		array[i++] = t--;
	}
	array[size] = size;
	count = 0;
}

/**--------------------------------------------------------------------------**\
<summary>Itter_InitInternal</summary>
<param name="array[][]">iterator array to initialise.</param>
<param name="s0">Size of first dimension.</param>
<param name="s1">Size of second dimension.</param>
<returns>
	-
</returns>
<remarks>
	Multi-dimensional arrays can't be initialised at compile time, so need to be
	done at run time, which is slightly annoying.
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>Itter_PrevInternal</summary>
<param name="array[]">iterator data.</param>
<param name="size">Size of the iterator.</param>
<param name="slot">The current slot.</param>
<returns>
	-
</returns>
<remarks>
	Gets the element in an iterator that points to the current element.
</remarks>
\**--------------------------------------------------------------------------**/

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

