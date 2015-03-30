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

#define iterstart@Test2a_y_iter -1
iterfunc Test2a_y_iter(start)
{
	switch (start)
	{
		case   -1: return 0;
		case    0: return 2;
		case    2: return 3;
		case    3: return 100;
		case  100: return 999;
		case  999: return 1000;
		case 1000: return 10000;
	}
	return -1;
}

#define iterstart@Test2b_y_iter -1
iterfunc Test2b_y_iter(start )
{
	switch (start)
	{
		case -1: return 0;
		case  0: return 1;
		case  1: return 2;
		case  2: return 3;
		case  3: return 4;
		case  4: return 5;
		case  5: return 6;
	}
	return -1;
}

#define iterstart@Test2c_y_iter -1
iterfunc Test2c_y_iter (start)
{
	switch (start)
	{
		case   -1: return 0;
		case    0: return 2;
		case    2: return 3;
		case    3: return 100;
		case  100: return 999;
		case  999: return 1000;
		case 1000: return 10000;
	}
	return -1;
}

#define iterstart@Test2d_y_iter -1
iterfunc Test2d_y_iter (start )
{
	switch (start)
	{
		case -1: return 0;
		case  0: return 1;
		case  1: return 2;
		case  2: return 3;
		case  3: return 4;
		case  4: return 5;
		case  5: return 6;
	}
	return -1;
}

Test:y_iter_Range()
{
	new
		count;
	count = 0;
	foreach (new i : Range(0, 10))
	{
		ASSERT(0 <= i < 10);
		++count;
	}
	ASSERT(count == 10);
	count = 0;
	foreach (new i : Range(-10, 10))
	{
		ASSERT(-10 <= i < 10);
		++count;
	}
	ASSERT(count == 20);
	count = 0;
	foreach (new i : Range(10, 10))
	{
		++count;
	}
	ASSERT(count == 0);
}

Test:y_iter_Add1()
{
	// Check we can only add a number once, and that we don't mess up the order.
	new
		Iterator:iter<20>,
		count,
		i;
	Iter_Add(iter, 5);
	ASSERT(Iter_Count(iter) == 1);
	for (i = 0; i != 20; ++i)
	{
		if (i == 5) ASSERT(Iter_Contains(iter, i));
		else ASSERT(!Iter_Contains(iter, i));
	}
	count = 0;
	foreach (i : iter)
	{
		ASSERT(i == 5);
		++count;
	}
	ASSERT(count == 1);
	Iter_Add(iter, 5);
	ASSERT(Iter_Count(iter) == 1);
	for (i = 0; i != 20; ++i)
	{
		if (i == 5) ASSERT(Iter_Contains(iter, i));
		else ASSERT(!Iter_Contains(iter, i));
	}
	count = 0;
	foreach (i : iter)
	{
		ASSERT(i == 5);
		++count;
	}
	ASSERT(count == 1);
}

Test:y_iter_Add2()
{
	// Check we can only add a number once, and that we don't mess up the order.
	new
		Iterator:iter<20>,
		count,
		i;
	Iter_Add(iter, 3);
	Iter_Add(iter, 15);
	ASSERT(Iter_Count(iter) == 2);
	for (i = 0; i != 20; ++i)
	{
		if (i == 3 || i == 15) ASSERT(Iter_Contains(iter, i));
		else ASSERT(!Iter_Contains(iter, i));
	}
	count = 0;
	foreach (i : iter)
	{
		ASSERT(i == 3 || i == 15);
		++count;
	}
	ASSERT(count == 2);
	Iter_Add(iter, 3);
	ASSERT(Iter_Count(iter) == 2);
	for (i = 0; i != 20; ++i)
	{
		if (i == 3 || i == 15) ASSERT(Iter_Contains(iter, i));
		else ASSERT(!Iter_Contains(iter, i));
	}
	count = 0;
	foreach (i : iter)
	{
		ASSERT(i == 3 || i == 15);
		++count;
	}
	ASSERT(count == 2);
	Iter_Add(iter, 15);
	ASSERT(Iter_Count(iter) == 2);
	for (i = 0; i != 20; ++i)
	{
		if (i == 3 || i == 15) ASSERT(Iter_Contains(iter, i));
		else ASSERT(!Iter_Contains(iter, i));
	}
	count = 0;
	foreach (i : iter)
	{
		ASSERT(i == 3 || i == 15);
		++count;
	}
	ASSERT(count == 2);
}

Test:y_iter_Prev()
{
	// Check we can only add a number once, and that we don't mess up the order.
	new
		Iterator:iter<20>,
		count,
		i;
	Iter_Add(iter, 3);
	Iter_Add(iter, 4);
	ASSERT(Iter_Count(iter) == 2);
	for (i = 0; i != 20; ++i)
	{
		if (i == 3 || i == 4) ASSERT(Iter_Contains(iter, i));
		else ASSERT(!Iter_Contains(iter, i));
	}
	count = 0;
	foreach (i : iter)
	{
		ASSERT(i == 3 || i == 4);
		++count;
	}
	ASSERT(count == 2);
	ASSERT(Iter_Next(iter, 3) == 4);
	ASSERT(Iter_Prev(iter, 4) == 3);
	ASSERT(Iter_First(iter) == 3);
	ASSERT(Iter_Last(iter) == 4);
	Iter_Add(iter, 18);
	ASSERT(Iter_Last(iter) == 18);
	Iter_Add(iter, 19);
	ASSERT(Iter_Last(iter) == 19);
	Iter_Add(iter, 19);
	ASSERT(Iter_Last(iter) == 19);
	ASSERT(Iter_Prev(iter, 20) == 19);
	ASSERT(Iter_Prev(iter, 19) == 18);
	ASSERT(Iter_Prev(iter, 18) == 4);
	ASSERT(Iter_Next(iter, 19) == 20);
	ASSERT(Iter_Next(iter, 18) == 19);
	ASSERT(Iter_Next(iter, 4) == 18);
	Iter_Add(iter, 0);
	ASSERT(Iter_Prev(iter, 0) == 20);
	ASSERT(Iter_Next(iter, 20) == 0);
}

Test:y_iter_Add3()
{
	// Check OOB numbers.
	new
		Iterator:iter<20>,
		count,
		i;
	Iter_Add(iter, 4);
	Iter_Add(iter, 20);
	ASSERT(Iter_Count(iter) == 1);
	for (i = 0; i != 20; ++i)
	{
		if (i == 4) ASSERT(Iter_Contains(iter, i));
		else ASSERT(!Iter_Contains(iter, i));
	}
	count = 0;
	foreach (i : iter)
	{
		ASSERT(i == 4);
		++count;
	}
	ASSERT(count == 1);
}

Test:y_iter_Add4()
{
	// Check OOB numbers.
	new
		Iterator:iter<20>,
		count,
		i;
	Iter_Add(iter, 0);
	Iter_Add(iter, 50);
	ASSERT(Iter_Count(iter) == 1);
	for (i = 0; i != 20; ++i)
	{
		if (i == 0) ASSERT(Iter_Contains(iter, i));
		else ASSERT(!Iter_Contains(iter, i));
	}
	count = 0;
	foreach (i : iter)
	{
		ASSERT(i == 0);
		++count;
	}
	ASSERT(count == 1);
}

Test:y_iter_Add5()
{
	// Add all numbers.
	new
		Iterator:iter<20>,
		count,
		i;
	ASSERT(Iter_Count(iter) == 0);
	for (i = 0; i != 20; ++i)
	{
		ASSERT(Iter_Add(iter, i) == i);
	}
	for (i = 20; i != 40; ++i)
	{
		ASSERT(Iter_Add(iter, i) != i);
	}
	ASSERT(Iter_Count(iter) == 20);
	count = 0;
	foreach (i : iter)
	{
		ASSERT(0 <= i < 20);
		++count;
	}
	ASSERT(count == 20);
}

Test:y_iter_MultiAdd1()
{
	// Add all numbers.
	new
		Iterator:iter<5, 15>,
		count,
		i = 6;
	ASSERT(Iter_Add(iter<0>, 0) == 0);
	ASSERT(Iter_Add(iter<0>, 0) != 0);
	ASSERT(Iter_Add(iter<0>, 1) == 1);
	// ASSERT(Iter_Add(iter<i>, 2) != 2);
	ASSERT(Iter_Add(iter<2>, 2) == 2);
	ASSERT(Iter_Add(iter<2>, 16) != 16);
	ASSERT(Iter_Count(iter<0>) == 2);
	ASSERT(Iter_Count(iter<1>) == 0);
	ASSERT(Iter_Count(iter<2>) == 1);
	ASSERT(Iter_Count(iter<3>) == 0);
	ASSERT(Iter_Count(iter<4>) == 0);
	count = 0;
	foreach (i : iter<0>)
	{
		ASSERT(i == 0 || i == 1);
		++count;
	}
	ASSERT(count == 2);
	count = 0;
	foreach (i : iter<2>)
	{
		ASSERT(i == 2);
		++count;
	}
	ASSERT(count == 1);
}

Test:y_iter_Remove1()
{
	new
		Iterator:iter<50>,
		count;
	for (new i = 0; i != 20; ++i)
	{
		Iter_Add(iter, i * 2 + 1);
	}
	ASSERT(Iter_Count(iter) == 20);
	foreach (new i : iter)
	{
		ASSERT((i & 1) == 1);
		++count;
	}
	ASSERT(count == 20);
	Iter_Remove(iter, 1);
	ASSERT(Iter_Count(iter) == 19);
	Iter_Remove(iter, 1);
	ASSERT(Iter_Count(iter) == 19);
	ASSERT(Iter_Count(iter) == 19);
	ASSERT(Iter_First(iter) == 3);
	ASSERT(Iter_Prev(iter, 3) == 50);
	ASSERT(Iter_Next(iter, 3) == 5);
	ASSERT(Iter_Prev(iter, 5) == 3);
	ASSERT(Iter_Next(iter, 5) == 7);
	ASSERT(Iter_Prev(iter, 7) == 5);
	Iter_Remove(iter, 5);
	ASSERT(Iter_First(iter) == 3);
	ASSERT(Iter_Prev(iter, 3) == 50);
	ASSERT(Iter_Next(iter, 3) == 7);
	ASSERT(Iter_Prev(iter, 7) == 3);
	ASSERT(Iter_Count(iter) == 18);
	count = 0;
	foreach (new i : iter)
	{
		ASSERT(i == 3 || i > 5);
		++count;
	}
	ASSERT(count == 18);
	Iter_Remove(iter, 1);
	count = 0;
	foreach (new i : iter)
	{
		ASSERT(i == 3 || i > 5);
		++count;
	}
	ASSERT(count == 18);
}

Test:y_iter_Reverse1()
{
	new
		count,
		Iterator:iter<10>;
	Iter_Add(iter, 2);
	Iter_Add(iter, 4);
	Iter_Add(iter, 6);
	Iter_Add(iter, 3);
	Iter_Add(iter, 6);
	Iter_Add(iter, 9);
	count = 0;
	foreach (new i : Reverse(iter))
	{
		++count;
	}
	ASSERT(count == 5);
}

Test:y_iter_Reverse2()
{
	new
		count,
		Iterator:iter<5, 10>;
	Iter_Add(iter<1>, 2);
	Iter_Add(iter<1>, 4);
	Iter_Add(iter<1>, 6);
	Iter_Add(iter<2>, 0);
	Iter_Add(iter<2>, 3);
	Iter_Add(iter<2>, 6);
	Iter_Add(iter<2>, 9);
	count = 0;
	foreach (new i : Reverse(iter<1>))
	{
		++count;
	}
	ASSERT(count == 3);
	count = 0;
	foreach (new i : Reverse(iter<2>))
	{
		++count;
	}
	ASSERT(count == 3);
}

Test:y_iter_Remove2()
{
	new
		Iterator:iter<5, 10>;
	Iter_Add(iter<1>, 2);
	Iter_Add(iter<1>, 4);
	Iter_Add(iter<1>, 6);
	Iter_Add(iter<2>, 0);
	Iter_Add(iter<2>, 3);
	Iter_Add(iter<2>, 6);
	Iter_Add(iter<2>, 9);
	ASSERT(Iter_First(iter<1>) == 2);
	ASSERT(Iter_First(iter<2>) == 0);
	ASSERT(Iter_Next(iter<1>, 2) == 4);
	ASSERT(Iter_Next(iter<2>, 0) == 3);
	ASSERT(Iter_Next(iter<2>, 3) == 9);
	ASSERT(Iter_Prev(iter<1>, 4) == 2);
	ASSERT(Iter_Prev(iter<2>, 3) == 0);
	ASSERT(Iter_Prev(iter<2>, 9) == 3);
	ASSERT(Iter_Count(iter<1>) == 3);
	ASSERT(Iter_Count(iter<2>) == 3);
	Iter_Remove(iter<1>, 0);
	ASSERT(Iter_First(iter<1>) == 2);
	ASSERT(Iter_First(iter<2>) == 0);
	ASSERT(Iter_Next(iter<1>, 2) == 4);
	ASSERT(Iter_Next(iter<2>, 0) == 3);
	ASSERT(Iter_Next(iter<2>, 3) == 9);
	ASSERT(Iter_Prev(iter<1>, 4) == 2);
	ASSERT(Iter_Prev(iter<2>, 3) == 0);
	ASSERT(Iter_Prev(iter<2>, 9) == 3);
	ASSERT(Iter_Count(iter<1>) == 3);
	ASSERT(Iter_Count(iter<2>) == 3);
	Iter_Remove(iter<2>, 0);
	ASSERT(Iter_First(iter<1>) == 2);
	ASSERT(Iter_First(iter<2>) == 3);
	ASSERT(Iter_Next(iter<1>, 2) == 4);
	ASSERT(Iter_Next(iter<2>, 3) == 9);
	ASSERT(Iter_Prev(iter<1>, 4) == 2);
	ASSERT(Iter_Prev(iter<2>, 3) >= 10);
	ASSERT(Iter_Prev(iter<2>, 9) == 3);
	ASSERT(Iter_Prev(iter<3>, Iter_Begin(iter<3>)) >= 10);
	ASSERT(Iter_Count(iter<1>) == 3);
	ASSERT(Iter_Count(iter<2>) == 2);
}

Test:y_iter_Tags()
{
	new
		Iterator:iter[5]<4>,
		GG:gg = GG:4;
	Iter_Init(iter);
	Iter_Add(iter[_:gg], 2);
	Iter_Clear(iter[_:gg]);
}

Test:y_iter_Iter_Init1()
{
	new
		Iterator:iter[10]<20>;
	#pragma unused Iter_Single@iter
	Iter_Init(iter);
	ASSERT(Iter_TrueArray(iter)[0][20] == 20);
	ASSERT(Iter_TrueArray(iter)[0][19] == 0);
	ASSERT(Iter_TrueArray(iter)[1][20] == 20);
	ASSERT(Iter_TrueArray(iter)[1][19] == 0);
	ASSERT(Iter_TrueArray(iter)[9][20] == 20);
	ASSERT(Iter_TrueArray(iter)[9][19] == 0);
}

Test:y_iter_Iter_Init2()
{
	new
		Iterator:iter[10]<5, 20>;
	#pragma unused Iter_Multi@iter
	Iter_Init(iter);
	ASSERT(Iter_TrueArray(iter)[0][21] >= 20);
	ASSERT(Iter_TrueArray(iter)[0][20] == 20);
	ASSERT(Iter_TrueArray(iter)[0][19] <= 19);
	ASSERT(Iter_TrueArray(iter)[2][24] >= 20);
	ASSERT(Iter_TrueArray(iter)[2][20] == 20);
	ASSERT(Iter_TrueArray(iter)[2][19] <= 19);
	ASSERT(Iter_TrueArray(iter)[8][24] >= 20);
	ASSERT(Iter_TrueArray(iter)[8][20] == 20);
	ASSERT(Iter_TrueArray(iter)[8][19] <= 19);
}

Test:y_iter_Starting()
{
	new
		Iterator:Test1_y_iter<100>,
		i,
		j;
	Iter_Add(Test1_y_iter, 4);
	Iter_Add(Test1_y_iter, 8);
	Iter_Add(Test1_y_iter, 2);
	Iter_Add(Test1_y_iter, 60);
	ASSERT(Iter_Begin(Test1_y_iter) >= 100);
	ASSERT(Iter_First(Test1_y_iter) == 2);
	ASSERT(Iter_Next(Test1_y_iter, Iter_First(Test1_y_iter)) == 4);
	ASSERT(Iter_Next(Test1_y_iter, Iter_Begin(Test1_y_iter)) == 2);
	i = Iter_Begin(Test1_y_iter);
	ASSERT(!Iter_Contains(Test1_y_iter, i));
	i = Iter_First(Test1_y_iter);
	ASSERT(Iter_Contains(Test1_y_iter, i));
	i = Iter_Begin(Test1_y_iter);
	ASSERT((i = Iter_Next(Test1_y_iter, i)) == 2);
	ASSERT((i = Iter_Next(Test1_y_iter, i)) == 4);
	ASSERT((i = Iter_Next(Test1_y_iter, i)) == 8);
	ASSERT((i = Iter_Next(Test1_y_iter, i)) == 60);
	j = Iter_End(Test1_y_iter);
	ASSERT((i = Iter_Next(Test1_y_iter, i)) == j);
	j = Iter_Free(Test1_y_iter);
	ASSERT(!Iter_Contains(Test1_y_iter, j));
	j = Iter_Alloc(Test1_y_iter);
	ASSERT(Iter_Contains(Test1_y_iter, j));
}

Test:y_iter_Iter_Contains()
{
	new
		Iterator:iter1<60>;
	ASSERT(!Iter_Contains(iter1, 7));
	Iter_Add(iter1, 7);
	ASSERT(Iter_Contains(iter1, 7));
	new
		Iterator:iter2<5, 60>;
	ASSERT(!Iter_Contains(iter2<>, 5));
	ASSERT(!Iter_Contains(iter2<0>, 5));
	ASSERT(!Iter_Contains(iter2<4>, 5));
	Iter_Add(iter2<4>, 5);
	ASSERT(Iter_Contains(iter2<>, 5));
	ASSERT(Iter_Contains(iter2< >, 5));
	ASSERT(!Iter_Contains(iter2<0>, 5));
	ASSERT(Iter_Contains(iter2<4>, 5));
}

Test:y_iter_Iter_Free()
{
	new
		Iterator:iter1<60>;
	ASSERT(Iter_Free(iter1) == 0);
	Iter_Add(iter1, 0);
	ASSERT(Iter_Free(iter1) != 0);
	new
		Iterator:iter2<5, 60>;
	ASSERT(Iter_Free(iter2<>) == 0);
	ASSERT(Iter_Free(iter2<1>) == 0);
	ASSERT(Iter_Free(iter2<3>) == 0);
	Iter_Add(iter2<3>, 0);
	ASSERT(Iter_Free(iter2<>) != 0);
	ASSERT(Iter_Free(iter2<1>) != 0);
	ASSERT(Iter_Free(iter2<3>) != 0);
}

Test:y_iter_Normal()
{
	new
		Iterator: Test1_y_iter<100>;
	Iter_Add(Test1_y_iter, 70);
	Iter_Add(Test1_y_iter, 51);
	Iter_Add(Test1_y_iter, 11);
	Iter_Add(Test1_y_iter, 88);
	Iter_Add(Test1_y_iter, 202);
	Iter_Add(Test1_y_iter, -7);
	new
		Test2_y_iter[100];
	foreach (new i : Test1_y_iter)
	{
		Test2_y_iter[i] = 1;
	}
	for (new i = 0; i != sizeof (Test2_y_iter); ++i)
	{
		if (i == 11 || i == 51 || i == 70 || i == 88)
		{
			ASSERT(Test2_y_iter[i] != 0);
		}
		else
		{
			ASSERT(Test2_y_iter[i] == 0);
		}
	}
	ASSERT(Iter_Count(Test1_y_iter) == 4);
	for (new i = 0; i != 50; ++i)
	{
		ASSERT(Test2_y_iter[Iter_Random(Test1_y_iter)] != 0);
		new
			j = Iter_Random(Test1_y_iter);
		ASSERT(Iter_Contains(Test1_y_iter, j));
	}
}

Test:y_iter_Syntax1()
{
	new
		Iterator:Test1_y_iter <100>;
	Iter_Add(Test1_y_iter, 11);
	Iter_Add(Test1_y_iter, 12);
	Iter_Add(Test1_y_iter, 13);
	Iter_Add(Test1_y_iter, 16);
	Iter_Add(Test1_y_iter, 19);
	Iter_Add(Test1_y_iter, 22);
	Iter_Add(Test1_y_iter, 23);
	new
		count = 0;
	foreach(new i:Test1_y_iter) { ++count; }
	foreach(new i:Test1_y_iter ) { ++count; }
	foreach(new i: Test1_y_iter) { ++count; }
	foreach(new i: Test1_y_iter ) { ++count; }
	foreach(new i :Test1_y_iter) { ++count; }
	foreach(new i :Test1_y_iter ) { ++count; }
	foreach(new i : Test1_y_iter) { ++count; }
	foreach(new i : Test1_y_iter ) { ++count; }
	foreach( new i:Test1_y_iter) { ++count; }
	foreach( new i:Test1_y_iter ) { ++count; }
	foreach( new i: Test1_y_iter) { ++count; }
	foreach( new i: Test1_y_iter ) { ++count; }
	foreach( new i :Test1_y_iter) { ++count; }
	foreach( new i :Test1_y_iter ) { ++count; }
	foreach( new i : Test1_y_iter) { ++count; }
	foreach( new i : Test1_y_iter ) { ++count; }
	foreach (new i:Test1_y_iter) { ++count; }
	foreach (new i:Test1_y_iter ) { ++count; }
	foreach (new i: Test1_y_iter) { ++count; }
	foreach (new i: Test1_y_iter ) { ++count; }
	foreach (new i :Test1_y_iter) { ++count; }
	foreach (new i :Test1_y_iter ) { ++count; }
	foreach (new i : Test1_y_iter) { ++count; }
	foreach (new i : Test1_y_iter ) { ++count; }
	foreach ( new i:Test1_y_iter) { ++count; }
	foreach ( new i:Test1_y_iter ) { ++count; }
	foreach ( new i: Test1_y_iter) { ++count; }
	foreach ( new i: Test1_y_iter ) { ++count; }
	foreach ( new i :Test1_y_iter) { ++count; }
	foreach ( new i :Test1_y_iter ) { ++count; }
	foreach ( new i : Test1_y_iter) { ++count; }
	foreach ( new i : Test1_y_iter ) { ++count; }
	new
		j;
	foreach(j:Test1_y_iter) { ++count; }
	foreach(j:Test1_y_iter ) { ++count; }
	foreach(j: Test1_y_iter) { ++count; }
	foreach(j: Test1_y_iter ) { ++count; }
	foreach(j :Test1_y_iter) { ++count; }
	foreach(j :Test1_y_iter ) { ++count; }
	foreach(j : Test1_y_iter) { ++count; }
	foreach(j : Test1_y_iter ) { ++count; }
	foreach( j:Test1_y_iter) { ++count; }
	foreach( j:Test1_y_iter ) { ++count; }
	foreach( j: Test1_y_iter) { ++count; }
	foreach( j: Test1_y_iter ) { ++count; }
	foreach( j :Test1_y_iter) { ++count; }
	foreach( j :Test1_y_iter ) { ++count; }
	foreach( j : Test1_y_iter) { ++count; }
	foreach( j : Test1_y_iter ) { ++count; }
	foreach (j:Test1_y_iter) { ++count; }
	foreach (j:Test1_y_iter ) { ++count; }
	foreach (j: Test1_y_iter) { ++count; }
	foreach (j: Test1_y_iter ) { ++count; }
	foreach (j :Test1_y_iter) { ++count; }
	foreach (j :Test1_y_iter ) { ++count; }
	foreach (j : Test1_y_iter) { ++count; }
	foreach (j : Test1_y_iter ) { ++count; }
	foreach ( j:Test1_y_iter) { ++count; }
	foreach ( j:Test1_y_iter ) { ++count; }
	foreach ( j: Test1_y_iter) { ++count; }
	foreach ( j: Test1_y_iter ) { ++count; }
	foreach ( j :Test1_y_iter) { ++count; }
	foreach ( j :Test1_y_iter ) { ++count; }
	foreach ( j : Test1_y_iter) { ++count; }
	foreach ( j : Test1_y_iter ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax5a()
{
	new
		Iterator:Test5a_y_iter[4]< 20, 100>;
	Iter_Init(Test5a_y_iter);
	Iter_Add(Test5a_y_iter[2]<11>, 11);
	Iter_Add(Test5a_y_iter[2]<11>, 12);
	Iter_Add(Test5a_y_iter[2]<11>, 13);
	Iter_Add(Test5a_y_iter[2]<11>, 16);
	Iter_Add(Test5a_y_iter[2]<11>, 19);
	Iter_Add(Test5a_y_iter[2]<11>, 22);
	Iter_Add(Test5a_y_iter[2]<11>, 23);
	new
		count = 0;
	foreach(new i:Test5a_y_iter[2] <11>) { ++count; }
	foreach(new i:Test5a_y_iter[2] <11> ) { ++count; }
	foreach(new i: Test5a_y_iter[2] <11>) { ++count; }
	foreach(new i: Test5a_y_iter[2] <11> ) { ++count; }
	foreach(new i :Test5a_y_iter[2] <11>) { ++count; }
	foreach(new i :Test5a_y_iter[2] <11> ) { ++count; }
	foreach(new i : Test5a_y_iter[2] <11>) { ++count; }
	foreach(new i : Test5a_y_iter[2] <11> ) { ++count; }
	foreach( new i:Test5a_y_iter[2] <11>) { ++count; }
	foreach( new i:Test5a_y_iter[2] <11> ) { ++count; }
	foreach( new i: Test5a_y_iter[2] <11>) { ++count; }
	foreach( new i: Test5a_y_iter[2] <11> ) { ++count; }
	foreach( new i :Test5a_y_iter[2] <11>) { ++count; }
	foreach( new i :Test5a_y_iter[2] <11> ) { ++count; }
	foreach( new i : Test5a_y_iter[2] <11>) { ++count; }
	foreach( new i : Test5a_y_iter[2] <11> ) { ++count; }
	foreach (new i:Test5a_y_iter[2] <11>) { ++count; }
	foreach (new i:Test5a_y_iter[2] <11> ) { ++count; }
	foreach (new i: Test5a_y_iter[2] <11>) { ++count; }
	foreach (new i: Test5a_y_iter[2] <11> ) { ++count; }
	foreach (new i :Test5a_y_iter[2] <11>) { ++count; }
	foreach (new i :Test5a_y_iter[2] <11> ) { ++count; }
	foreach (new i : Test5a_y_iter[2] <11>) { ++count; }
	foreach (new i : Test5a_y_iter[2] <11> ) { ++count; }
	foreach ( new i:Test5a_y_iter[2] <11>) { ++count; }
	foreach ( new i:Test5a_y_iter[2] <11> ) { ++count; }
	foreach ( new i: Test5a_y_iter[2] <11>) { ++count; }
	foreach ( new i: Test5a_y_iter[2] <11> ) { ++count; }
	foreach ( new i :Test5a_y_iter[2] <11>) { ++count; }
	foreach ( new i :Test5a_y_iter[2] <11> ) { ++count; }
	foreach ( new i : Test5a_y_iter[2] <11>) { ++count; }
	foreach ( new i : Test5a_y_iter[2] <11> ) { ++count; }
	new
		j;
	foreach(j:Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach(j:Test5a_y_iter[ 2]< 11> ) { ++count; }
	foreach(j: Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach(j: Test5a_y_iter[ 2]< 11> ) { ++count; }
	foreach(j :Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach(j :Test5a_y_iter[ 2]< 11> ) { ++count; }
	foreach(j : Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach(j : Test5a_y_iter[ 2]< 11> ) { ++count; }
	foreach( j:Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach( j:Test5a_y_iter[ 2]< 11> ) { ++count; }
	foreach( j: Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach( j: Test5a_y_iter[ 2]< 11> ) { ++count; }
	foreach( j :Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach( j :Test5a_y_iter[ 2]< 11> ) { ++count; }
	foreach( j : Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach( j : Test5a_y_iter[ 2]< 11> ) { ++count; }
	foreach (j:Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach (j:Test5a_y_iter[ 2]< 11> ) { ++count; }
	foreach (j: Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach (j: Test5a_y_iter[ 2]< 11> ) { ++count; }
	foreach (j :Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach (j :Test5a_y_iter[ 2]< 11> ) { ++count; }
	foreach (j : Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach (j : Test5a_y_iter[ 2]< 11> ) { ++count; }
	foreach ( j:Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach ( j:Test5a_y_iter[ 2]< 11> ) { ++count; }
	foreach ( j: Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach ( j: Test5a_y_iter[ 2]< 11> ) { ++count; }
	foreach ( j :Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach ( j :Test5a_y_iter[ 2]< 11> ) { ++count; }
	foreach ( j : Test5a_y_iter[ 2]< 11>) { ++count; }
	foreach ( j : Test5a_y_iter[ 2]< 11> ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax5b()
{
	new
		Iterator:Test5b_y_iter[4]<20, 100 >;
	Iter_Init(Test5b_y_iter);
	Iter_Add(Test5b_y_iter[2]<11>, 11);
	Iter_Add(Test5b_y_iter[2]<11>, 12);
	Iter_Add(Test5b_y_iter[2]<11>, 13);
	Iter_Add(Test5b_y_iter[2]<11>, 16);
	Iter_Add(Test5b_y_iter[2]<11>, 19);
	Iter_Add(Test5b_y_iter[2]<11>, 22);
	Iter_Add(Test5b_y_iter[2]<11>, 23);
	new
		count = 0;
	foreach(new i:Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach(new i:Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	foreach(new i: Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach(new i: Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	foreach(new i :Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach(new i :Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	foreach(new i : Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach(new i : Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	foreach( new i:Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach( new i:Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	foreach( new i: Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach( new i: Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	foreach( new i :Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach( new i :Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	foreach( new i : Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach( new i : Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	foreach (new i:Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach (new i:Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	foreach (new i: Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach (new i: Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	foreach (new i :Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach (new i :Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	foreach (new i : Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach (new i : Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	foreach ( new i:Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach ( new i:Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	foreach ( new i: Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach ( new i: Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	foreach ( new i :Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach ( new i :Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	foreach ( new i : Test5b_y_iter[ 2 ] < 11>) { ++count; }
	foreach ( new i : Test5b_y_iter[ 2 ] < 11> ) { ++count; }
	new
		j;
	foreach(j:Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach(j:Test5b_y_iter[2 ]<11 > ) { ++count; }
	foreach(j: Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach(j: Test5b_y_iter[2 ]<11 > ) { ++count; }
	foreach(j :Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach(j :Test5b_y_iter[2 ]<11 > ) { ++count; }
	foreach(j : Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach(j : Test5b_y_iter[2 ]<11 > ) { ++count; }
	foreach( j:Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach( j:Test5b_y_iter[2 ]<11 > ) { ++count; }
	foreach( j: Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach( j: Test5b_y_iter[2 ]<11 > ) { ++count; }
	foreach( j :Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach( j :Test5b_y_iter[2 ]<11 > ) { ++count; }
	foreach( j : Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach( j : Test5b_y_iter[2 ]<11 > ) { ++count; }
	foreach (j:Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach (j:Test5b_y_iter[2 ]<11 > ) { ++count; }
	foreach (j: Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach (j: Test5b_y_iter[2 ]<11 > ) { ++count; }
	foreach (j :Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach (j :Test5b_y_iter[2 ]<11 > ) { ++count; }
	foreach (j : Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach (j : Test5b_y_iter[2 ]<11 > ) { ++count; }
	foreach ( j:Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach ( j:Test5b_y_iter[2 ]<11 > ) { ++count; }
	foreach ( j: Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach ( j: Test5b_y_iter[2 ]<11 > ) { ++count; }
	foreach ( j :Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach ( j :Test5b_y_iter[2 ]<11 > ) { ++count; }
	foreach ( j : Test5b_y_iter[2 ]<11 >) { ++count; }
	foreach ( j : Test5b_y_iter[2 ]<11 > ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax5c()
{
	new
		Iterator: Test5c_y_iter[4]< 20, 100>;
	Iter_Init(Test5c_y_iter);
	Iter_Add(Test5c_y_iter[2]<11>, 11);
	Iter_Add(Test5c_y_iter[2]<11>, 12);
	Iter_Add(Test5c_y_iter[2]<11>, 13);
	Iter_Add(Test5c_y_iter[2]<11>, 16);
	Iter_Add(Test5c_y_iter[2]<11>, 19);
	Iter_Add(Test5c_y_iter[2]<11>, 22);
	Iter_Add(Test5c_y_iter[2]<11>, 23);
	new
		count = 0;
	foreach(new i:Test5c_y_iter [2] <11 >) { ++count; }
	foreach(new i:Test5c_y_iter [2] <11 > ) { ++count; }
	foreach(new i: Test5c_y_iter [2] <11 >) { ++count; }
	foreach(new i: Test5c_y_iter [2] <11 > ) { ++count; }
	foreach(new i :Test5c_y_iter [2] <11 >) { ++count; }
	foreach(new i :Test5c_y_iter [2] <11 > ) { ++count; }
	foreach(new i : Test5c_y_iter [2] <11 >) { ++count; }
	foreach(new i : Test5c_y_iter [2] <11 > ) { ++count; }
	foreach( new i:Test5c_y_iter [2] <11 >) { ++count; }
	foreach( new i:Test5c_y_iter [2] <11 > ) { ++count; }
	foreach( new i: Test5c_y_iter [2] <11 >) { ++count; }
	foreach( new i: Test5c_y_iter [2] <11 > ) { ++count; }
	foreach( new i :Test5c_y_iter [2] <11 >) { ++count; }
	foreach( new i :Test5c_y_iter [2] <11 > ) { ++count; }
	foreach( new i : Test5c_y_iter [2] <11 >) { ++count; }
	foreach( new i : Test5c_y_iter [2] <11 > ) { ++count; }
	foreach (new i:Test5c_y_iter [2] <11 >) { ++count; }
	foreach (new i:Test5c_y_iter [2] <11 > ) { ++count; }
	foreach (new i: Test5c_y_iter [2] <11 >) { ++count; }
	foreach (new i: Test5c_y_iter [2] <11 > ) { ++count; }
	foreach (new i :Test5c_y_iter [2] <11 >) { ++count; }
	foreach (new i :Test5c_y_iter [2] <11 > ) { ++count; }
	foreach (new i : Test5c_y_iter [2] <11 >) { ++count; }
	foreach (new i : Test5c_y_iter [2] <11 > ) { ++count; }
	foreach ( new i:Test5c_y_iter [2] <11 >) { ++count; }
	foreach ( new i:Test5c_y_iter [2] <11 > ) { ++count; }
	foreach ( new i: Test5c_y_iter [2] <11 >) { ++count; }
	foreach ( new i: Test5c_y_iter [2] <11 > ) { ++count; }
	foreach ( new i :Test5c_y_iter [2] <11 >) { ++count; }
	foreach ( new i :Test5c_y_iter [2] <11 > ) { ++count; }
	foreach ( new i : Test5c_y_iter [2] <11 >) { ++count; }
	foreach ( new i : Test5c_y_iter [2] <11 > ) { ++count; }
	new
		j;
	foreach(j:Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach(j:Test5c_y_iter [ 2]< 11 > ) { ++count; }
	foreach(j: Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach(j: Test5c_y_iter [ 2]< 11 > ) { ++count; }
	foreach(j :Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach(j :Test5c_y_iter [ 2]< 11 > ) { ++count; }
	foreach(j : Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach(j : Test5c_y_iter [ 2]< 11 > ) { ++count; }
	foreach( j:Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach( j:Test5c_y_iter [ 2]< 11 > ) { ++count; }
	foreach( j: Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach( j: Test5c_y_iter [ 2]< 11 > ) { ++count; }
	foreach( j :Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach( j :Test5c_y_iter [ 2]< 11 > ) { ++count; }
	foreach( j : Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach( j : Test5c_y_iter [ 2]< 11 > ) { ++count; }
	foreach (j:Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach (j:Test5c_y_iter [ 2]< 11 > ) { ++count; }
	foreach (j: Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach (j: Test5c_y_iter [ 2]< 11 > ) { ++count; }
	foreach (j :Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach (j :Test5c_y_iter [ 2]< 11 > ) { ++count; }
	foreach (j : Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach (j : Test5c_y_iter [ 2]< 11 > ) { ++count; }
	foreach ( j:Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach ( j:Test5c_y_iter [ 2]< 11 > ) { ++count; }
	foreach ( j: Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach ( j: Test5c_y_iter [ 2]< 11 > ) { ++count; }
	foreach ( j :Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach ( j :Test5c_y_iter [ 2]< 11 > ) { ++count; }
	foreach ( j : Test5c_y_iter [ 2]< 11 >) { ++count; }
	foreach ( j : Test5c_y_iter [ 2]< 11 > ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax5d()
{
	new
		Iterator: Test5d_y_iter [ 4 ] < 20, 100 >;
	Iter_Init(Test5d_y_iter);
	Iter_Add(Test5d_y_iter[2]<11>, 11);
	Iter_Add(Test5d_y_iter[2]<11>, 12);
	Iter_Add(Test5d_y_iter[2]<11>, 13);
	Iter_Add(Test5d_y_iter[2]<11>, 16);
	Iter_Add(Test5d_y_iter[2]<11>, 19);
	Iter_Add(Test5d_y_iter[2]<11>, 22);
	Iter_Add(Test5d_y_iter[2]<11>, 23);
	new
		count = 0;
	foreach(new i:Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach(new i:Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	foreach(new i: Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach(new i: Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	foreach(new i :Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach(new i :Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	foreach(new i : Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach(new i : Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	foreach( new i:Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach( new i:Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	foreach( new i: Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach( new i: Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	foreach( new i :Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach( new i :Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	foreach( new i : Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach( new i : Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	foreach (new i:Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach (new i:Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	foreach (new i: Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach (new i: Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	foreach (new i :Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach (new i :Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	foreach (new i : Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach (new i : Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	foreach ( new i:Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach ( new i:Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	foreach ( new i: Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach ( new i: Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	foreach ( new i :Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach ( new i :Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	foreach ( new i : Test5d_y_iter [ 2 ] < 11 >) { ++count; }
	foreach ( new i : Test5d_y_iter [ 2 ] < 11 > ) { ++count; }
	new
		j;
	foreach(j:Test5d_y_iter [2 ]<11>) { ++count; }
	foreach(j:Test5d_y_iter [2 ]<11> ) { ++count; }
	foreach(j: Test5d_y_iter [2 ]<11>) { ++count; }
	foreach(j: Test5d_y_iter [2 ]<11> ) { ++count; }
	foreach(j :Test5d_y_iter [2 ]<11>) { ++count; }
	foreach(j :Test5d_y_iter [2 ]<11> ) { ++count; }
	foreach(j : Test5d_y_iter [2 ]<11>) { ++count; }
	foreach(j : Test5d_y_iter [2 ]<11> ) { ++count; }
	foreach( j:Test5d_y_iter [2 ]<11>) { ++count; }
	foreach( j:Test5d_y_iter [2 ]<11> ) { ++count; }
	foreach( j: Test5d_y_iter [2 ]<11>) { ++count; }
	foreach( j: Test5d_y_iter [2 ]<11> ) { ++count; }
	foreach( j :Test5d_y_iter [2 ]<11>) { ++count; }
	foreach( j :Test5d_y_iter [2 ]<11> ) { ++count; }
	foreach( j : Test5d_y_iter [2 ]<11>) { ++count; }
	foreach( j : Test5d_y_iter [2 ]<11> ) { ++count; }
	foreach (j:Test5d_y_iter [2 ]<11>) { ++count; }
	foreach (j:Test5d_y_iter [2 ]<11> ) { ++count; }
	foreach (j: Test5d_y_iter [2 ]<11>) { ++count; }
	foreach (j: Test5d_y_iter [2 ]<11> ) { ++count; }
	foreach (j :Test5d_y_iter [2 ]<11>) { ++count; }
	foreach (j :Test5d_y_iter [2 ]<11> ) { ++count; }
	foreach (j : Test5d_y_iter [2 ]<11>) { ++count; }
	foreach (j : Test5d_y_iter [2 ]<11> ) { ++count; }
	foreach ( j:Test5d_y_iter [2 ]<11>) { ++count; }
	foreach ( j:Test5d_y_iter [2 ]<11> ) { ++count; }
	foreach ( j: Test5d_y_iter [2 ]<11>) { ++count; }
	foreach ( j: Test5d_y_iter [2 ]<11> ) { ++count; }
	foreach ( j :Test5d_y_iter [2 ]<11>) { ++count; }
	foreach ( j :Test5d_y_iter [2 ]<11> ) { ++count; }
	foreach ( j : Test5d_y_iter [2 ]<11>) { ++count; }
	foreach ( j : Test5d_y_iter [2 ]<11> ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax4a()
{
	new
		Iterator:Test4a_y_iter[ 4 ] < 100 >;
	Iter_Init(Test4a_y_iter);
	Iter_Add(Test4a_y_iter[3], 11);
	Iter_Add(Test4a_y_iter[3], 12);
	Iter_Add(Test4a_y_iter[3], 13);
	Iter_Add(Test4a_y_iter[3], 16);
	Iter_Add(Test4a_y_iter[3], 19);
	Iter_Add(Test4a_y_iter[3], 22);
	Iter_Add(Test4a_y_iter[3], 23);
	new
		count = 0;
	foreach(new i:Test4a_y_iter[3]) { ++count; }
	foreach(new i:Test4a_y_iter[3] ) { ++count; }
	foreach(new i: Test4a_y_iter[3]) { ++count; }
	foreach(new i: Test4a_y_iter[3] ) { ++count; }
	foreach(new i :Test4a_y_iter[3]) { ++count; }
	foreach(new i :Test4a_y_iter[3] ) { ++count; }
	foreach(new i : Test4a_y_iter[3]) { ++count; }
	foreach(new i : Test4a_y_iter[3] ) { ++count; }
	foreach( new i:Test4a_y_iter[3]) { ++count; }
	foreach( new i:Test4a_y_iter[3] ) { ++count; }
	foreach( new i: Test4a_y_iter[3]) { ++count; }
	foreach( new i: Test4a_y_iter[3] ) { ++count; }
	foreach( new i :Test4a_y_iter[3]) { ++count; }
	foreach( new i :Test4a_y_iter[3] ) { ++count; }
	foreach( new i : Test4a_y_iter[3]) { ++count; }
	foreach( new i : Test4a_y_iter[3] ) { ++count; }
	foreach (new i:Test4a_y_iter[3]) { ++count; }
	foreach (new i:Test4a_y_iter[3] ) { ++count; }
	foreach (new i: Test4a_y_iter[3]) { ++count; }
	foreach (new i: Test4a_y_iter[3] ) { ++count; }
	foreach (new i :Test4a_y_iter[3]) { ++count; }
	foreach (new i :Test4a_y_iter[3] ) { ++count; }
	foreach (new i : Test4a_y_iter[3]) { ++count; }
	foreach (new i : Test4a_y_iter[3] ) { ++count; }
	foreach ( new i:Test4a_y_iter[3]) { ++count; }
	foreach ( new i:Test4a_y_iter[3] ) { ++count; }
	foreach ( new i: Test4a_y_iter[3]) { ++count; }
	foreach ( new i: Test4a_y_iter[3] ) { ++count; }
	foreach ( new i :Test4a_y_iter[3]) { ++count; }
	foreach ( new i :Test4a_y_iter[3] ) { ++count; }
	foreach ( new i : Test4a_y_iter[3]) { ++count; }
	foreach ( new i : Test4a_y_iter[3] ) { ++count; }
	new
		j;
	foreach(j:Test4a_y_iter[ 3]) { ++count; }
	foreach(j:Test4a_y_iter[ 3] ) { ++count; }
	foreach(j: Test4a_y_iter[ 3]) { ++count; }
	foreach(j: Test4a_y_iter[ 3] ) { ++count; }
	foreach(j :Test4a_y_iter[ 3]) { ++count; }
	foreach(j :Test4a_y_iter[ 3] ) { ++count; }
	foreach(j : Test4a_y_iter[ 3]) { ++count; }
	foreach(j : Test4a_y_iter[ 3] ) { ++count; }
	foreach( j:Test4a_y_iter[ 3]) { ++count; }
	foreach( j:Test4a_y_iter[ 3] ) { ++count; }
	foreach( j: Test4a_y_iter[ 3]) { ++count; }
	foreach( j: Test4a_y_iter[ 3] ) { ++count; }
	foreach( j :Test4a_y_iter[ 3]) { ++count; }
	foreach( j :Test4a_y_iter[ 3] ) { ++count; }
	foreach( j : Test4a_y_iter[ 3]) { ++count; }
	foreach( j : Test4a_y_iter[ 3] ) { ++count; }
	foreach (j:Test4a_y_iter[ 3]) { ++count; }
	foreach (j:Test4a_y_iter[ 3] ) { ++count; }
	foreach (j: Test4a_y_iter[ 3]) { ++count; }
	foreach (j: Test4a_y_iter[ 3] ) { ++count; }
	foreach (j :Test4a_y_iter[ 3]) { ++count; }
	foreach (j :Test4a_y_iter[ 3] ) { ++count; }
	foreach (j : Test4a_y_iter[ 3]) { ++count; }
	foreach (j : Test4a_y_iter[ 3] ) { ++count; }
	foreach ( j:Test4a_y_iter[ 3]) { ++count; }
	foreach ( j:Test4a_y_iter[ 3] ) { ++count; }
	foreach ( j: Test4a_y_iter[ 3]) { ++count; }
	foreach ( j: Test4a_y_iter[ 3] ) { ++count; }
	foreach ( j :Test4a_y_iter[ 3]) { ++count; }
	foreach ( j :Test4a_y_iter[ 3] ) { ++count; }
	foreach ( j : Test4a_y_iter[ 3]) { ++count; }
	foreach ( j : Test4a_y_iter[ 3] ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax4b()
{
	new
		Iterator: Test4b_y_iter [4]<100>;
	Iter_Init(Test4b_y_iter);
	Iter_Add(Test4b_y_iter[0], 11);
	Iter_Add(Test4b_y_iter[0], 12);
	Iter_Add(Test4b_y_iter[0], 13);
	Iter_Add(Test4b_y_iter[0], 16);
	Iter_Add(Test4b_y_iter[0], 19);
	Iter_Add(Test4b_y_iter[0], 22);
	Iter_Add(Test4b_y_iter[0], 23);
	new
		count = 0;
	foreach(new i:Test4b_y_iter[ 0 ]) { ++count; }
	foreach(new i:Test4b_y_iter[ 0 ] ) { ++count; }
	foreach(new i: Test4b_y_iter[ 0 ]) { ++count; }
	foreach(new i: Test4b_y_iter[ 0 ] ) { ++count; }
	foreach(new i :Test4b_y_iter[ 0 ]) { ++count; }
	foreach(new i :Test4b_y_iter[ 0 ] ) { ++count; }
	foreach(new i : Test4b_y_iter[ 0 ]) { ++count; }
	foreach(new i : Test4b_y_iter[ 0 ] ) { ++count; }
	foreach( new i:Test4b_y_iter[ 0 ]) { ++count; }
	foreach( new i:Test4b_y_iter[ 0 ] ) { ++count; }
	foreach( new i: Test4b_y_iter[ 0 ]) { ++count; }
	foreach( new i: Test4b_y_iter[ 0 ] ) { ++count; }
	foreach( new i :Test4b_y_iter[ 0 ]) { ++count; }
	foreach( new i :Test4b_y_iter[ 0 ] ) { ++count; }
	foreach( new i : Test4b_y_iter[ 0 ]) { ++count; }
	foreach( new i : Test4b_y_iter[ 0 ] ) { ++count; }
	foreach (new i:Test4b_y_iter[ 0 ]) { ++count; }
	foreach (new i:Test4b_y_iter[ 0 ] ) { ++count; }
	foreach (new i: Test4b_y_iter[ 0 ]) { ++count; }
	foreach (new i: Test4b_y_iter[ 0 ] ) { ++count; }
	foreach (new i :Test4b_y_iter[ 0 ]) { ++count; }
	foreach (new i :Test4b_y_iter[ 0 ] ) { ++count; }
	foreach (new i : Test4b_y_iter[ 0 ]) { ++count; }
	foreach (new i : Test4b_y_iter[ 0 ] ) { ++count; }
	foreach ( new i:Test4b_y_iter[ 0 ]) { ++count; }
	foreach ( new i:Test4b_y_iter[ 0 ] ) { ++count; }
	foreach ( new i: Test4b_y_iter[ 0 ]) { ++count; }
	foreach ( new i: Test4b_y_iter[ 0 ] ) { ++count; }
	foreach ( new i :Test4b_y_iter[ 0 ]) { ++count; }
	foreach ( new i :Test4b_y_iter[ 0 ] ) { ++count; }
	foreach ( new i : Test4b_y_iter[ 0 ]) { ++count; }
	foreach ( new i : Test4b_y_iter[ 0 ] ) { ++count; }
	new
		j;
	foreach(j:Test4b_y_iter[0 ]) { ++count; }
	foreach(j:Test4b_y_iter[0 ] ) { ++count; }
	foreach(j: Test4b_y_iter[0 ]) { ++count; }
	foreach(j: Test4b_y_iter[0 ] ) { ++count; }
	foreach(j :Test4b_y_iter[0 ]) { ++count; }
	foreach(j :Test4b_y_iter[0 ] ) { ++count; }
	foreach(j : Test4b_y_iter[0 ]) { ++count; }
	foreach(j : Test4b_y_iter[0 ] ) { ++count; }
	foreach( j:Test4b_y_iter[0 ]) { ++count; }
	foreach( j:Test4b_y_iter[0 ] ) { ++count; }
	foreach( j: Test4b_y_iter[0 ]) { ++count; }
	foreach( j: Test4b_y_iter[0 ] ) { ++count; }
	foreach( j :Test4b_y_iter[0 ]) { ++count; }
	foreach( j :Test4b_y_iter[0 ] ) { ++count; }
	foreach( j : Test4b_y_iter[0 ]) { ++count; }
	foreach( j : Test4b_y_iter[0 ] ) { ++count; }
	foreach (j:Test4b_y_iter[0 ]) { ++count; }
	foreach (j:Test4b_y_iter[0 ] ) { ++count; }
	foreach (j: Test4b_y_iter[0 ]) { ++count; }
	foreach (j: Test4b_y_iter[0 ] ) { ++count; }
	foreach (j :Test4b_y_iter[0 ]) { ++count; }
	foreach (j :Test4b_y_iter[0 ] ) { ++count; }
	foreach (j : Test4b_y_iter[0 ]) { ++count; }
	foreach (j : Test4b_y_iter[0 ] ) { ++count; }
	foreach ( j:Test4b_y_iter[0 ]) { ++count; }
	foreach ( j:Test4b_y_iter[0 ] ) { ++count; }
	foreach ( j: Test4b_y_iter[0 ]) { ++count; }
	foreach ( j: Test4b_y_iter[0 ] ) { ++count; }
	foreach ( j :Test4b_y_iter[0 ]) { ++count; }
	foreach ( j :Test4b_y_iter[0 ] ) { ++count; }
	foreach ( j : Test4b_y_iter[0 ]) { ++count; }
	foreach ( j : Test4b_y_iter[0 ] ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax4c()
{
	new
		Iterator: Test4c_y_iter[4 ]<100 >;
	Iter_Init(Test4c_y_iter);
	Iter_Add(Test4c_y_iter[3], 11);
	Iter_Add(Test4c_y_iter[3], 12);
	Iter_Add(Test4c_y_iter[3], 13);
	Iter_Add(Test4c_y_iter[3], 16);
	Iter_Add(Test4c_y_iter[3], 19);
	Iter_Add(Test4c_y_iter[3], 22);
	Iter_Add(Test4c_y_iter[3], 23);
	new
		count = 0;
	foreach(new i:Test4c_y_iter [3]) { ++count; }
	foreach(new i:Test4c_y_iter [3] ) { ++count; }
	foreach(new i: Test4c_y_iter [3]) { ++count; }
	foreach(new i: Test4c_y_iter [3] ) { ++count; }
	foreach(new i :Test4c_y_iter [3]) { ++count; }
	foreach(new i :Test4c_y_iter [3] ) { ++count; }
	foreach(new i : Test4c_y_iter [3]) { ++count; }
	foreach(new i : Test4c_y_iter [3] ) { ++count; }
	foreach( new i:Test4c_y_iter [3]) { ++count; }
	foreach( new i:Test4c_y_iter [3] ) { ++count; }
	foreach( new i: Test4c_y_iter [3]) { ++count; }
	foreach( new i: Test4c_y_iter [3] ) { ++count; }
	foreach( new i :Test4c_y_iter [3]) { ++count; }
	foreach( new i :Test4c_y_iter [3] ) { ++count; }
	foreach( new i : Test4c_y_iter [3]) { ++count; }
	foreach( new i : Test4c_y_iter [3] ) { ++count; }
	foreach (new i:Test4c_y_iter [3]) { ++count; }
	foreach (new i:Test4c_y_iter [3] ) { ++count; }
	foreach (new i: Test4c_y_iter [3]) { ++count; }
	foreach (new i: Test4c_y_iter [3] ) { ++count; }
	foreach (new i :Test4c_y_iter [3]) { ++count; }
	foreach (new i :Test4c_y_iter [3] ) { ++count; }
	foreach (new i : Test4c_y_iter [3]) { ++count; }
	foreach (new i : Test4c_y_iter [3] ) { ++count; }
	foreach ( new i:Test4c_y_iter [3]) { ++count; }
	foreach ( new i:Test4c_y_iter [3] ) { ++count; }
	foreach ( new i: Test4c_y_iter [3]) { ++count; }
	foreach ( new i: Test4c_y_iter [3] ) { ++count; }
	foreach ( new i :Test4c_y_iter [3]) { ++count; }
	foreach ( new i :Test4c_y_iter [3] ) { ++count; }
	foreach ( new i : Test4c_y_iter [3]) { ++count; }
	foreach ( new i : Test4c_y_iter [3] ) { ++count; }
	new
		j;
	foreach(j:Test4c_y_iter [ 3]) { ++count; }
	foreach(j:Test4c_y_iter [ 3] ) { ++count; }
	foreach(j: Test4c_y_iter [ 3]) { ++count; }
	foreach(j: Test4c_y_iter [ 3] ) { ++count; }
	foreach(j :Test4c_y_iter [ 3]) { ++count; }
	foreach(j :Test4c_y_iter [ 3] ) { ++count; }
	foreach(j : Test4c_y_iter [ 3]) { ++count; }
	foreach(j : Test4c_y_iter [ 3] ) { ++count; }
	foreach( j:Test4c_y_iter [ 3]) { ++count; }
	foreach( j:Test4c_y_iter [ 3] ) { ++count; }
	foreach( j: Test4c_y_iter [ 3]) { ++count; }
	foreach( j: Test4c_y_iter [ 3] ) { ++count; }
	foreach( j :Test4c_y_iter [ 3]) { ++count; }
	foreach( j :Test4c_y_iter [ 3] ) { ++count; }
	foreach( j : Test4c_y_iter [ 3]) { ++count; }
	foreach( j : Test4c_y_iter [ 3] ) { ++count; }
	foreach (j:Test4c_y_iter [ 3]) { ++count; }
	foreach (j:Test4c_y_iter [ 3] ) { ++count; }
	foreach (j: Test4c_y_iter [ 3]) { ++count; }
	foreach (j: Test4c_y_iter [ 3] ) { ++count; }
	foreach (j :Test4c_y_iter [ 3]) { ++count; }
	foreach (j :Test4c_y_iter [ 3] ) { ++count; }
	foreach (j : Test4c_y_iter [ 3]) { ++count; }
	foreach (j : Test4c_y_iter [ 3] ) { ++count; }
	foreach ( j:Test4c_y_iter [ 3]) { ++count; }
	foreach ( j:Test4c_y_iter [ 3] ) { ++count; }
	foreach ( j: Test4c_y_iter [ 3]) { ++count; }
	foreach ( j: Test4c_y_iter [ 3] ) { ++count; }
	foreach ( j :Test4c_y_iter [ 3]) { ++count; }
	foreach ( j :Test4c_y_iter [ 3] ) { ++count; }
	foreach ( j : Test4c_y_iter [ 3]) { ++count; }
	foreach ( j : Test4c_y_iter [ 3] ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax4d()
{
	new
		Iterator: Test4d_y_iter[ 4]< 100>;
	Iter_Init(Test4d_y_iter);
	Iter_Add(Test4d_y_iter[0], 11);
	Iter_Add(Test4d_y_iter[0], 12);
	Iter_Add(Test4d_y_iter[0], 13);
	Iter_Add(Test4d_y_iter[0], 16);
	Iter_Add(Test4d_y_iter[0], 19);
	Iter_Add(Test4d_y_iter[0], 22);
	Iter_Add(Test4d_y_iter[0], 23);
	new
		count = 0;
	foreach(new i:Test4d_y_iter [ 0 ]) { ++count; }
	foreach(new i:Test4d_y_iter [ 0 ] ) { ++count; }
	foreach(new i: Test4d_y_iter [ 0 ]) { ++count; }
	foreach(new i: Test4d_y_iter [ 0 ] ) { ++count; }
	foreach(new i :Test4d_y_iter [ 0 ]) { ++count; }
	foreach(new i :Test4d_y_iter [ 0 ] ) { ++count; }
	foreach(new i : Test4d_y_iter [ 0 ]) { ++count; }
	foreach(new i : Test4d_y_iter [ 0 ] ) { ++count; }
	foreach( new i:Test4d_y_iter [ 0 ]) { ++count; }
	foreach( new i:Test4d_y_iter [ 0 ] ) { ++count; }
	foreach( new i: Test4d_y_iter [ 0 ]) { ++count; }
	foreach( new i: Test4d_y_iter [ 0 ] ) { ++count; }
	foreach( new i :Test4d_y_iter [ 0 ]) { ++count; }
	foreach( new i :Test4d_y_iter [ 0 ] ) { ++count; }
	foreach( new i : Test4d_y_iter [ 0 ]) { ++count; }
	foreach( new i : Test4d_y_iter [ 0 ] ) { ++count; }
	foreach (new i:Test4d_y_iter [ 0 ]) { ++count; }
	foreach (new i:Test4d_y_iter [ 0 ] ) { ++count; }
	foreach (new i: Test4d_y_iter [ 0 ]) { ++count; }
	foreach (new i: Test4d_y_iter [ 0 ] ) { ++count; }
	foreach (new i :Test4d_y_iter [ 0 ]) { ++count; }
	foreach (new i :Test4d_y_iter [ 0 ] ) { ++count; }
	foreach (new i : Test4d_y_iter [ 0 ]) { ++count; }
	foreach (new i : Test4d_y_iter [ 0 ] ) { ++count; }
	foreach ( new i:Test4d_y_iter [ 0 ]) { ++count; }
	foreach ( new i:Test4d_y_iter [ 0 ] ) { ++count; }
	foreach ( new i: Test4d_y_iter [ 0 ]) { ++count; }
	foreach ( new i: Test4d_y_iter [ 0 ] ) { ++count; }
	foreach ( new i :Test4d_y_iter [ 0 ]) { ++count; }
	foreach ( new i :Test4d_y_iter [ 0 ] ) { ++count; }
	foreach ( new i : Test4d_y_iter [ 0 ]) { ++count; }
	foreach ( new i : Test4d_y_iter [ 0 ] ) { ++count; }
	new
		j;
	foreach(j:Test4d_y_iter [0 ]) { ++count; }
	foreach(j:Test4d_y_iter [0 ] ) { ++count; }
	foreach(j: Test4d_y_iter [0 ]) { ++count; }
	foreach(j: Test4d_y_iter [0 ] ) { ++count; }
	foreach(j :Test4d_y_iter [0 ]) { ++count; }
	foreach(j :Test4d_y_iter [0 ] ) { ++count; }
	foreach(j : Test4d_y_iter [0 ]) { ++count; }
	foreach(j : Test4d_y_iter [0 ] ) { ++count; }
	foreach( j:Test4d_y_iter [0 ]) { ++count; }
	foreach( j:Test4d_y_iter [0 ] ) { ++count; }
	foreach( j: Test4d_y_iter [0 ]) { ++count; }
	foreach( j: Test4d_y_iter [0 ] ) { ++count; }
	foreach( j :Test4d_y_iter [0 ]) { ++count; }
	foreach( j :Test4d_y_iter [0 ] ) { ++count; }
	foreach( j : Test4d_y_iter [0 ]) { ++count; }
	foreach( j : Test4d_y_iter [0 ] ) { ++count; }
	foreach (j:Test4d_y_iter [0 ]) { ++count; }
	foreach (j:Test4d_y_iter [0 ] ) { ++count; }
	foreach (j: Test4d_y_iter [0 ]) { ++count; }
	foreach (j: Test4d_y_iter [0 ] ) { ++count; }
	foreach (j :Test4d_y_iter [0 ]) { ++count; }
	foreach (j :Test4d_y_iter [0 ] ) { ++count; }
	foreach (j : Test4d_y_iter [0 ]) { ++count; }
	foreach (j : Test4d_y_iter [0 ] ) { ++count; }
	foreach ( j:Test4d_y_iter [0 ]) { ++count; }
	foreach ( j:Test4d_y_iter [0 ] ) { ++count; }
	foreach ( j: Test4d_y_iter [0 ]) { ++count; }
	foreach ( j: Test4d_y_iter [0 ] ) { ++count; }
	foreach ( j :Test4d_y_iter [0 ]) { ++count; }
	foreach ( j :Test4d_y_iter [0 ] ) { ++count; }
	foreach ( j : Test4d_y_iter [0 ]) { ++count; }
	foreach ( j : Test4d_y_iter [0 ] ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax3a()
{
	new
		Iterator: Test3a_y_iter <10, 100>;
	Iter_Add(Test3a_y_iter<4>, 11);
	Iter_Add(Test3a_y_iter<4>, 12);
	Iter_Add(Test3a_y_iter<4>, 13);
	Iter_Add(Test3a_y_iter<4>, 16);
	Iter_Add(Test3a_y_iter<4>, 19);
	Iter_Add(Test3a_y_iter<4>, 22);
	Iter_Add(Test3a_y_iter<4>, 23);
	new
		count = 0;
	foreach(new i:Test3a_y_iter<4>) { ++count; }
	foreach(new i:Test3a_y_iter<4> ) { ++count; }
	foreach(new i: Test3a_y_iter<4>) { ++count; }
	foreach(new i: Test3a_y_iter<4> ) { ++count; }
	foreach(new i :Test3a_y_iter<4>) { ++count; }
	foreach(new i :Test3a_y_iter<4> ) { ++count; }
	foreach(new i : Test3a_y_iter<4>) { ++count; }
	foreach(new i : Test3a_y_iter<4> ) { ++count; }
	foreach( new i:Test3a_y_iter<4>) { ++count; }
	foreach( new i:Test3a_y_iter<4> ) { ++count; }
	foreach( new i: Test3a_y_iter<4>) { ++count; }
	foreach( new i: Test3a_y_iter<4> ) { ++count; }
	foreach( new i :Test3a_y_iter<4>) { ++count; }
	foreach( new i :Test3a_y_iter<4> ) { ++count; }
	foreach( new i : Test3a_y_iter<4>) { ++count; }
	foreach( new i : Test3a_y_iter<4> ) { ++count; }
	foreach (new i:Test3a_y_iter<4>) { ++count; }
	foreach (new i:Test3a_y_iter<4> ) { ++count; }
	foreach (new i: Test3a_y_iter<4>) { ++count; }
	foreach (new i: Test3a_y_iter<4> ) { ++count; }
	foreach (new i :Test3a_y_iter<4>) { ++count; }
	foreach (new i :Test3a_y_iter<4> ) { ++count; }
	foreach (new i : Test3a_y_iter<4>) { ++count; }
	foreach (new i : Test3a_y_iter<4> ) { ++count; }
	foreach ( new i:Test3a_y_iter<4>) { ++count; }
	foreach ( new i:Test3a_y_iter<4> ) { ++count; }
	foreach ( new i: Test3a_y_iter<4>) { ++count; }
	foreach ( new i: Test3a_y_iter<4> ) { ++count; }
	foreach ( new i :Test3a_y_iter<4>) { ++count; }
	foreach ( new i :Test3a_y_iter<4> ) { ++count; }
	foreach ( new i : Test3a_y_iter<4>) { ++count; }
	foreach ( new i : Test3a_y_iter<4> ) { ++count; }
	new
		j;
	foreach(j:Test3a_y_iter< 4>) { ++count; }
	foreach(j:Test3a_y_iter< 4> ) { ++count; }
	foreach(j: Test3a_y_iter< 4>) { ++count; }
	foreach(j: Test3a_y_iter< 4> ) { ++count; }
	foreach(j :Test3a_y_iter< 4>) { ++count; }
	foreach(j :Test3a_y_iter< 4> ) { ++count; }
	foreach(j : Test3a_y_iter< 4>) { ++count; }
	foreach(j : Test3a_y_iter< 4> ) { ++count; }
	foreach( j:Test3a_y_iter< 4>) { ++count; }
	foreach( j:Test3a_y_iter< 4> ) { ++count; }
	foreach( j: Test3a_y_iter< 4>) { ++count; }
	foreach( j: Test3a_y_iter< 4> ) { ++count; }
	foreach( j :Test3a_y_iter< 4>) { ++count; }
	foreach( j :Test3a_y_iter< 4> ) { ++count; }
	foreach( j : Test3a_y_iter< 4>) { ++count; }
	foreach( j : Test3a_y_iter< 4> ) { ++count; }
	foreach (j:Test3a_y_iter< 4>) { ++count; }
	foreach (j:Test3a_y_iter< 4> ) { ++count; }
	foreach (j: Test3a_y_iter< 4>) { ++count; }
	foreach (j: Test3a_y_iter< 4> ) { ++count; }
	foreach (j :Test3a_y_iter< 4>) { ++count; }
	foreach (j :Test3a_y_iter< 4> ) { ++count; }
	foreach (j : Test3a_y_iter< 4>) { ++count; }
	foreach (j : Test3a_y_iter< 4> ) { ++count; }
	foreach ( j:Test3a_y_iter< 4>) { ++count; }
	foreach ( j:Test3a_y_iter< 4> ) { ++count; }
	foreach ( j: Test3a_y_iter< 4>) { ++count; }
	foreach ( j: Test3a_y_iter< 4> ) { ++count; }
	foreach ( j :Test3a_y_iter< 4>) { ++count; }
	foreach ( j :Test3a_y_iter< 4> ) { ++count; }
	foreach ( j : Test3a_y_iter< 4>) { ++count; }
	foreach ( j : Test3a_y_iter< 4> ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax3b()
{
	new
		Iterator:Test3b_y_iter< 10, 100 >;
	Iter_Add(Test3b_y_iter<6>, 11);
	Iter_Add(Test3b_y_iter<6>, 12);
	Iter_Add(Test3b_y_iter<6>, 13);
	Iter_Add(Test3b_y_iter<6>, 16);
	Iter_Add(Test3b_y_iter<6>, 19);
	Iter_Add(Test3b_y_iter<6>, 22);
	Iter_Add(Test3b_y_iter<6>, 23);
	new
		count = 0;
	foreach(new i:Test3b_y_iter< 6 >) { ++count; }
	foreach(new i:Test3b_y_iter< 6 > ) { ++count; }
	foreach(new i: Test3b_y_iter< 6 >) { ++count; }
	foreach(new i: Test3b_y_iter< 6 > ) { ++count; }
	foreach(new i :Test3b_y_iter< 6 >) { ++count; }
	foreach(new i :Test3b_y_iter< 6 > ) { ++count; }
	foreach(new i : Test3b_y_iter< 6 >) { ++count; }
	foreach(new i : Test3b_y_iter< 6 > ) { ++count; }
	foreach( new i:Test3b_y_iter< 6 >) { ++count; }
	foreach( new i:Test3b_y_iter< 6 > ) { ++count; }
	foreach( new i: Test3b_y_iter< 6 >) { ++count; }
	foreach( new i: Test3b_y_iter< 6 > ) { ++count; }
	foreach( new i :Test3b_y_iter< 6 >) { ++count; }
	foreach( new i :Test3b_y_iter< 6 > ) { ++count; }
	foreach( new i : Test3b_y_iter< 6 >) { ++count; }
	foreach( new i : Test3b_y_iter< 6 > ) { ++count; }
	foreach (new i:Test3b_y_iter< 6 >) { ++count; }
	foreach (new i:Test3b_y_iter< 6 > ) { ++count; }
	foreach (new i: Test3b_y_iter< 6 >) { ++count; }
	foreach (new i: Test3b_y_iter< 6 > ) { ++count; }
	foreach (new i :Test3b_y_iter< 6 >) { ++count; }
	foreach (new i :Test3b_y_iter< 6 > ) { ++count; }
	foreach (new i : Test3b_y_iter< 6 >) { ++count; }
	foreach (new i : Test3b_y_iter< 6 > ) { ++count; }
	foreach ( new i:Test3b_y_iter< 6 >) { ++count; }
	foreach ( new i:Test3b_y_iter< 6 > ) { ++count; }
	foreach ( new i: Test3b_y_iter< 6 >) { ++count; }
	foreach ( new i: Test3b_y_iter< 6 > ) { ++count; }
	foreach ( new i :Test3b_y_iter< 6 >) { ++count; }
	foreach ( new i :Test3b_y_iter< 6 > ) { ++count; }
	foreach ( new i : Test3b_y_iter< 6 >) { ++count; }
	foreach ( new i : Test3b_y_iter< 6 > ) { ++count; }
	new
		j;
	foreach(j:Test3b_y_iter<6 >) { ++count; }
	foreach(j:Test3b_y_iter<6 > ) { ++count; }
	foreach(j: Test3b_y_iter<6 >) { ++count; }
	foreach(j: Test3b_y_iter<6 > ) { ++count; }
	foreach(j :Test3b_y_iter<6 >) { ++count; }
	foreach(j :Test3b_y_iter<6 > ) { ++count; }
	foreach(j : Test3b_y_iter<6 >) { ++count; }
	foreach(j : Test3b_y_iter<6 > ) { ++count; }
	foreach( j:Test3b_y_iter<6 >) { ++count; }
	foreach( j:Test3b_y_iter<6 > ) { ++count; }
	foreach( j: Test3b_y_iter<6 >) { ++count; }
	foreach( j: Test3b_y_iter<6 > ) { ++count; }
	foreach( j :Test3b_y_iter<6 >) { ++count; }
	foreach( j :Test3b_y_iter<6 > ) { ++count; }
	foreach( j : Test3b_y_iter<6 >) { ++count; }
	foreach( j : Test3b_y_iter<6 > ) { ++count; }
	foreach (j:Test3b_y_iter<6 >) { ++count; }
	foreach (j:Test3b_y_iter<6 > ) { ++count; }
	foreach (j: Test3b_y_iter<6 >) { ++count; }
	foreach (j: Test3b_y_iter<6 > ) { ++count; }
	foreach (j :Test3b_y_iter<6 >) { ++count; }
	foreach (j :Test3b_y_iter<6 > ) { ++count; }
	foreach (j : Test3b_y_iter<6 >) { ++count; }
	foreach (j : Test3b_y_iter<6 > ) { ++count; }
	foreach ( j:Test3b_y_iter<6 >) { ++count; }
	foreach ( j:Test3b_y_iter<6 > ) { ++count; }
	foreach ( j: Test3b_y_iter<6 >) { ++count; }
	foreach ( j: Test3b_y_iter<6 > ) { ++count; }
	foreach ( j :Test3b_y_iter<6 >) { ++count; }
	foreach ( j :Test3b_y_iter<6 > ) { ++count; }
	foreach ( j : Test3b_y_iter<6 >) { ++count; }
	foreach ( j : Test3b_y_iter<6 > ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax3c()
{
	new
		Iterator: Test3c_y_iter <10, 100>;
	Iter_Add(Test3c_y_iter<4>, 11);
	Iter_Add(Test3c_y_iter<4>, 12);
	Iter_Add(Test3c_y_iter<4>, 13);
	Iter_Add(Test3c_y_iter<4>, 16);
	Iter_Add(Test3c_y_iter<4>, 19);
	Iter_Add(Test3c_y_iter<4>, 22);
	Iter_Add(Test3c_y_iter<4>, 23);
	new
		count = 0;
	foreach(new i:Test3c_y_iter <4>) { ++count; }
	foreach(new i:Test3c_y_iter <4> ) { ++count; }
	foreach(new i: Test3c_y_iter <4>) { ++count; }
	foreach(new i: Test3c_y_iter <4> ) { ++count; }
	foreach(new i :Test3c_y_iter <4>) { ++count; }
	foreach(new i :Test3c_y_iter <4> ) { ++count; }
	foreach(new i : Test3c_y_iter <4>) { ++count; }
	foreach(new i : Test3c_y_iter <4> ) { ++count; }
	foreach( new i:Test3c_y_iter <4>) { ++count; }
	foreach( new i:Test3c_y_iter <4> ) { ++count; }
	foreach( new i: Test3c_y_iter <4>) { ++count; }
	foreach( new i: Test3c_y_iter <4> ) { ++count; }
	foreach( new i :Test3c_y_iter <4>) { ++count; }
	foreach( new i :Test3c_y_iter <4> ) { ++count; }
	foreach( new i : Test3c_y_iter <4>) { ++count; }
	foreach( new i : Test3c_y_iter <4> ) { ++count; }
	foreach (new i:Test3c_y_iter <4>) { ++count; }
	foreach (new i:Test3c_y_iter <4> ) { ++count; }
	foreach (new i: Test3c_y_iter <4>) { ++count; }
	foreach (new i: Test3c_y_iter <4> ) { ++count; }
	foreach (new i :Test3c_y_iter <4>) { ++count; }
	foreach (new i :Test3c_y_iter <4> ) { ++count; }
	foreach (new i : Test3c_y_iter <4>) { ++count; }
	foreach (new i : Test3c_y_iter <4> ) { ++count; }
	foreach ( new i:Test3c_y_iter <4>) { ++count; }
	foreach ( new i:Test3c_y_iter <4> ) { ++count; }
	foreach ( new i: Test3c_y_iter <4>) { ++count; }
	foreach ( new i: Test3c_y_iter <4> ) { ++count; }
	foreach ( new i :Test3c_y_iter <4>) { ++count; }
	foreach ( new i :Test3c_y_iter <4> ) { ++count; }
	foreach ( new i : Test3c_y_iter <4>) { ++count; }
	foreach ( new i : Test3c_y_iter <4> ) { ++count; }
	new
		j;
	foreach(j:Test3c_y_iter < 4>) { ++count; }
	foreach(j:Test3c_y_iter < 4> ) { ++count; }
	foreach(j: Test3c_y_iter < 4>) { ++count; }
	foreach(j: Test3c_y_iter < 4> ) { ++count; }
	foreach(j :Test3c_y_iter < 4>) { ++count; }
	foreach(j :Test3c_y_iter < 4> ) { ++count; }
	foreach(j : Test3c_y_iter < 4>) { ++count; }
	foreach(j : Test3c_y_iter < 4> ) { ++count; }
	foreach( j:Test3c_y_iter < 4>) { ++count; }
	foreach( j:Test3c_y_iter < 4> ) { ++count; }
	foreach( j: Test3c_y_iter < 4>) { ++count; }
	foreach( j: Test3c_y_iter < 4> ) { ++count; }
	foreach( j :Test3c_y_iter < 4>) { ++count; }
	foreach( j :Test3c_y_iter < 4> ) { ++count; }
	foreach( j : Test3c_y_iter < 4>) { ++count; }
	foreach( j : Test3c_y_iter < 4> ) { ++count; }
	foreach (j:Test3c_y_iter < 4>) { ++count; }
	foreach (j:Test3c_y_iter < 4> ) { ++count; }
	foreach (j: Test3c_y_iter < 4>) { ++count; }
	foreach (j: Test3c_y_iter < 4> ) { ++count; }
	foreach (j :Test3c_y_iter < 4>) { ++count; }
	foreach (j :Test3c_y_iter < 4> ) { ++count; }
	foreach (j : Test3c_y_iter < 4>) { ++count; }
	foreach (j : Test3c_y_iter < 4> ) { ++count; }
	foreach ( j:Test3c_y_iter < 4>) { ++count; }
	foreach ( j:Test3c_y_iter < 4> ) { ++count; }
	foreach ( j: Test3c_y_iter < 4>) { ++count; }
	foreach ( j: Test3c_y_iter < 4> ) { ++count; }
	foreach ( j :Test3c_y_iter < 4>) { ++count; }
	foreach ( j :Test3c_y_iter < 4> ) { ++count; }
	foreach ( j : Test3c_y_iter < 4>) { ++count; }
	foreach ( j : Test3c_y_iter < 4> ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax3d()
{
	new
		Iterator:Test3d_y_iter < 10, 100 >;
	Iter_Add(Test3d_y_iter<6>, 11);
	Iter_Add(Test3d_y_iter<6>, 12);
	Iter_Add(Test3d_y_iter<6>, 13);
	Iter_Add(Test3d_y_iter<6>, 16);
	Iter_Add(Test3d_y_iter<6>, 19);
	Iter_Add(Test3d_y_iter<6>, 22);
	Iter_Add(Test3d_y_iter<6>, 23);
	new
		count = 0;
	foreach(new i:Test3d_y_iter < 6 >) { ++count; }
	foreach(new i:Test3d_y_iter < 6 > ) { ++count; }
	foreach(new i: Test3d_y_iter < 6 >) { ++count; }
	foreach(new i: Test3d_y_iter < 6 > ) { ++count; }
	foreach(new i :Test3d_y_iter < 6 >) { ++count; }
	foreach(new i :Test3d_y_iter < 6 > ) { ++count; }
	foreach(new i : Test3d_y_iter < 6 >) { ++count; }
	foreach(new i : Test3d_y_iter < 6 > ) { ++count; }
	foreach( new i:Test3d_y_iter < 6 >) { ++count; }
	foreach( new i:Test3d_y_iter < 6 > ) { ++count; }
	foreach( new i: Test3d_y_iter < 6 >) { ++count; }
	foreach( new i: Test3d_y_iter < 6 > ) { ++count; }
	foreach( new i :Test3d_y_iter < 6 >) { ++count; }
	foreach( new i :Test3d_y_iter < 6 > ) { ++count; }
	foreach( new i : Test3d_y_iter < 6 >) { ++count; }
	foreach( new i : Test3d_y_iter < 6 > ) { ++count; }
	foreach (new i:Test3d_y_iter < 6 >) { ++count; }
	foreach (new i:Test3d_y_iter < 6 > ) { ++count; }
	foreach (new i: Test3d_y_iter < 6 >) { ++count; }
	foreach (new i: Test3d_y_iter < 6 > ) { ++count; }
	foreach (new i :Test3d_y_iter < 6 >) { ++count; }
	foreach (new i :Test3d_y_iter < 6 > ) { ++count; }
	foreach (new i : Test3d_y_iter < 6 >) { ++count; }
	foreach (new i : Test3d_y_iter < 6 > ) { ++count; }
	foreach ( new i:Test3d_y_iter < 6 >) { ++count; }
	foreach ( new i:Test3d_y_iter < 6 > ) { ++count; }
	foreach ( new i: Test3d_y_iter < 6 >) { ++count; }
	foreach ( new i: Test3d_y_iter < 6 > ) { ++count; }
	foreach ( new i :Test3d_y_iter < 6 >) { ++count; }
	foreach ( new i :Test3d_y_iter < 6 > ) { ++count; }
	foreach ( new i : Test3d_y_iter < 6 >) { ++count; }
	foreach ( new i : Test3d_y_iter < 6 > ) { ++count; }
	new
		j;
	foreach(j:Test3d_y_iter <6 >) { ++count; }
	foreach(j:Test3d_y_iter <6 > ) { ++count; }
	foreach(j: Test3d_y_iter <6 >) { ++count; }
	foreach(j: Test3d_y_iter <6 > ) { ++count; }
	foreach(j :Test3d_y_iter <6 >) { ++count; }
	foreach(j :Test3d_y_iter <6 > ) { ++count; }
	foreach(j : Test3d_y_iter <6 >) { ++count; }
	foreach(j : Test3d_y_iter <6 > ) { ++count; }
	foreach( j:Test3d_y_iter <6 >) { ++count; }
	foreach( j:Test3d_y_iter <6 > ) { ++count; }
	foreach( j: Test3d_y_iter <6 >) { ++count; }
	foreach( j: Test3d_y_iter <6 > ) { ++count; }
	foreach( j :Test3d_y_iter <6 >) { ++count; }
	foreach( j :Test3d_y_iter <6 > ) { ++count; }
	foreach( j : Test3d_y_iter <6 >) { ++count; }
	foreach( j : Test3d_y_iter <6 > ) { ++count; }
	foreach (j:Test3d_y_iter <6 >) { ++count; }
	foreach (j:Test3d_y_iter <6 > ) { ++count; }
	foreach (j: Test3d_y_iter <6 >) { ++count; }
	foreach (j: Test3d_y_iter <6 > ) { ++count; }
	foreach (j :Test3d_y_iter <6 >) { ++count; }
	foreach (j :Test3d_y_iter <6 > ) { ++count; }
	foreach (j : Test3d_y_iter <6 >) { ++count; }
	foreach (j : Test3d_y_iter <6 > ) { ++count; }
	foreach ( j:Test3d_y_iter <6 >) { ++count; }
	foreach ( j:Test3d_y_iter <6 > ) { ++count; }
	foreach ( j: Test3d_y_iter <6 >) { ++count; }
	foreach ( j: Test3d_y_iter <6 > ) { ++count; }
	foreach ( j :Test3d_y_iter <6 >) { ++count; }
	foreach ( j :Test3d_y_iter <6 > ) { ++count; }
	foreach ( j : Test3d_y_iter <6 >) { ++count; }
	foreach ( j : Test3d_y_iter <6 > ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax2a()
{
	new
		count = 0;
	foreach(new i:Test2a_y_iter()) { ++count; }
	foreach(new i:Test2a_y_iter() ) { ++count; }
	foreach(new i: Test2a_y_iter()) { ++count; }
	foreach(new i: Test2a_y_iter() ) { ++count; }
	foreach(new i :Test2a_y_iter()) { ++count; }
	foreach(new i :Test2a_y_iter() ) { ++count; }
	foreach(new i : Test2a_y_iter()) { ++count; }
	foreach(new i : Test2a_y_iter() ) { ++count; }
	foreach( new i:Test2a_y_iter()) { ++count; }
	foreach( new i:Test2a_y_iter() ) { ++count; }
	foreach( new i: Test2a_y_iter()) { ++count; }
	foreach( new i: Test2a_y_iter() ) { ++count; }
	foreach( new i :Test2a_y_iter()) { ++count; }
	foreach( new i :Test2a_y_iter() ) { ++count; }
	foreach( new i : Test2a_y_iter()) { ++count; }
	foreach( new i : Test2a_y_iter() ) { ++count; }
	foreach (new i:Test2a_y_iter()) { ++count; }
	foreach (new i:Test2a_y_iter() ) { ++count; }
	foreach (new i: Test2a_y_iter()) { ++count; }
	foreach (new i: Test2a_y_iter() ) { ++count; }
	foreach (new i :Test2a_y_iter()) { ++count; }
	foreach (new i :Test2a_y_iter() ) { ++count; }
	foreach (new i : Test2a_y_iter()) { ++count; }
	foreach (new i : Test2a_y_iter() ) { ++count; }
	foreach ( new i:Test2a_y_iter()) { ++count; }
	foreach ( new i:Test2a_y_iter() ) { ++count; }
	foreach ( new i: Test2a_y_iter()) { ++count; }
	foreach ( new i: Test2a_y_iter() ) { ++count; }
	foreach ( new i :Test2a_y_iter()) { ++count; }
	foreach ( new i :Test2a_y_iter() ) { ++count; }
	foreach ( new i : Test2a_y_iter()) { ++count; }
	foreach ( new i : Test2a_y_iter() ) { ++count; }
	new
		j;
	foreach(j:Test2a_y_iter()) { ++count; }
	foreach(j:Test2a_y_iter() ) { ++count; }
	foreach(j: Test2a_y_iter()) { ++count; }
	foreach(j: Test2a_y_iter() ) { ++count; }
	foreach(j :Test2a_y_iter()) { ++count; }
	foreach(j :Test2a_y_iter() ) { ++count; }
	foreach(j : Test2a_y_iter()) { ++count; }
	foreach(j : Test2a_y_iter() ) { ++count; }
	foreach( j:Test2a_y_iter()) { ++count; }
	foreach( j:Test2a_y_iter() ) { ++count; }
	foreach( j: Test2a_y_iter()) { ++count; }
	foreach( j: Test2a_y_iter() ) { ++count; }
	foreach( j :Test2a_y_iter()) { ++count; }
	foreach( j :Test2a_y_iter() ) { ++count; }
	foreach( j : Test2a_y_iter()) { ++count; }
	foreach( j : Test2a_y_iter() ) { ++count; }
	foreach (j:Test2a_y_iter()) { ++count; }
	foreach (j:Test2a_y_iter() ) { ++count; }
	foreach (j: Test2a_y_iter()) { ++count; }
	foreach (j: Test2a_y_iter() ) { ++count; }
	foreach (j :Test2a_y_iter()) { ++count; }
	foreach (j :Test2a_y_iter() ) { ++count; }
	foreach (j : Test2a_y_iter()) { ++count; }
	foreach (j : Test2a_y_iter() ) { ++count; }
	foreach ( j:Test2a_y_iter()) { ++count; }
	foreach ( j:Test2a_y_iter() ) { ++count; }
	foreach ( j: Test2a_y_iter()) { ++count; }
	foreach ( j: Test2a_y_iter() ) { ++count; }
	foreach ( j :Test2a_y_iter()) { ++count; }
	foreach ( j :Test2a_y_iter() ) { ++count; }
	foreach ( j : Test2a_y_iter()) { ++count; }
	foreach ( j : Test2a_y_iter() ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax2b()
{
	new
		count = 0;
	foreach(new i:Test2b_y_iter( )) { ++count; }
	foreach(new i:Test2b_y_iter( ) ) { ++count; }
	foreach(new i: Test2b_y_iter( )) { ++count; }
	foreach(new i: Test2b_y_iter( ) ) { ++count; }
	foreach(new i :Test2b_y_iter( )) { ++count; }
	foreach(new i :Test2b_y_iter( ) ) { ++count; }
	foreach(new i : Test2b_y_iter( )) { ++count; }
	foreach(new i : Test2b_y_iter( ) ) { ++count; }
	foreach( new i:Test2b_y_iter( )) { ++count; }
	foreach( new i:Test2b_y_iter( ) ) { ++count; }
	foreach( new i: Test2b_y_iter( )) { ++count; }
	foreach( new i: Test2b_y_iter( ) ) { ++count; }
	foreach( new i :Test2b_y_iter( )) { ++count; }
	foreach( new i :Test2b_y_iter( ) ) { ++count; }
	foreach( new i : Test2b_y_iter( )) { ++count; }
	foreach( new i : Test2b_y_iter( ) ) { ++count; }
	foreach (new i:Test2b_y_iter( )) { ++count; }
	foreach (new i:Test2b_y_iter( ) ) { ++count; }
	foreach (new i: Test2b_y_iter( )) { ++count; }
	foreach (new i: Test2b_y_iter( ) ) { ++count; }
	foreach (new i :Test2b_y_iter( )) { ++count; }
	foreach (new i :Test2b_y_iter( ) ) { ++count; }
	foreach (new i : Test2b_y_iter( )) { ++count; }
	foreach (new i : Test2b_y_iter( ) ) { ++count; }
	foreach ( new i:Test2b_y_iter( )) { ++count; }
	foreach ( new i:Test2b_y_iter( ) ) { ++count; }
	foreach ( new i: Test2b_y_iter( )) { ++count; }
	foreach ( new i: Test2b_y_iter( ) ) { ++count; }
	foreach ( new i :Test2b_y_iter( )) { ++count; }
	foreach ( new i :Test2b_y_iter( ) ) { ++count; }
	foreach ( new i : Test2b_y_iter( )) { ++count; }
	foreach ( new i : Test2b_y_iter( ) ) { ++count; }
	new
		j;
	foreach(j:Test2b_y_iter( )) { ++count; }
	foreach(j:Test2b_y_iter( ) ) { ++count; }
	foreach(j: Test2b_y_iter( )) { ++count; }
	foreach(j: Test2b_y_iter( ) ) { ++count; }
	foreach(j :Test2b_y_iter( )) { ++count; }
	foreach(j :Test2b_y_iter( ) ) { ++count; }
	foreach(j : Test2b_y_iter( )) { ++count; }
	foreach(j : Test2b_y_iter( ) ) { ++count; }
	foreach( j:Test2b_y_iter( )) { ++count; }
	foreach( j:Test2b_y_iter( ) ) { ++count; }
	foreach( j: Test2b_y_iter( )) { ++count; }
	foreach( j: Test2b_y_iter( ) ) { ++count; }
	foreach( j :Test2b_y_iter( )) { ++count; }
	foreach( j :Test2b_y_iter( ) ) { ++count; }
	foreach( j : Test2b_y_iter( )) { ++count; }
	foreach( j : Test2b_y_iter( ) ) { ++count; }
	foreach (j:Test2b_y_iter( )) { ++count; }
	foreach (j:Test2b_y_iter( ) ) { ++count; }
	foreach (j: Test2b_y_iter( )) { ++count; }
	foreach (j: Test2b_y_iter( ) ) { ++count; }
	foreach (j :Test2b_y_iter( )) { ++count; }
	foreach (j :Test2b_y_iter( ) ) { ++count; }
	foreach (j : Test2b_y_iter( )) { ++count; }
	foreach (j : Test2b_y_iter( ) ) { ++count; }
	foreach ( j:Test2b_y_iter( )) { ++count; }
	foreach ( j:Test2b_y_iter( ) ) { ++count; }
	foreach ( j: Test2b_y_iter( )) { ++count; }
	foreach ( j: Test2b_y_iter( ) ) { ++count; }
	foreach ( j :Test2b_y_iter( )) { ++count; }
	foreach ( j :Test2b_y_iter( ) ) { ++count; }
	foreach ( j : Test2b_y_iter( )) { ++count; }
	foreach ( j : Test2b_y_iter( ) ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax2c()
{
	new
		count = 0;
	foreach(new i:Test2c_y_iter ()) { ++count; }
	foreach(new i:Test2c_y_iter () ) { ++count; }
	foreach(new i: Test2c_y_iter ()) { ++count; }
	foreach(new i: Test2c_y_iter () ) { ++count; }
	foreach(new i :Test2c_y_iter ()) { ++count; }
	foreach(new i :Test2c_y_iter () ) { ++count; }
	foreach(new i : Test2c_y_iter ()) { ++count; }
	foreach(new i : Test2c_y_iter () ) { ++count; }
	foreach( new i:Test2c_y_iter ()) { ++count; }
	foreach( new i:Test2c_y_iter () ) { ++count; }
	foreach( new i: Test2c_y_iter ()) { ++count; }
	foreach( new i: Test2c_y_iter () ) { ++count; }
	foreach( new i :Test2c_y_iter ()) { ++count; }
	foreach( new i :Test2c_y_iter () ) { ++count; }
	foreach( new i : Test2c_y_iter ()) { ++count; }
	foreach( new i : Test2c_y_iter () ) { ++count; }
	foreach (new i:Test2c_y_iter ()) { ++count; }
	foreach (new i:Test2c_y_iter () ) { ++count; }
	foreach (new i: Test2c_y_iter ()) { ++count; }
	foreach (new i: Test2c_y_iter () ) { ++count; }
	foreach (new i :Test2c_y_iter ()) { ++count; }
	foreach (new i :Test2c_y_iter () ) { ++count; }
	foreach (new i : Test2c_y_iter ()) { ++count; }
	foreach (new i : Test2c_y_iter () ) { ++count; }
	foreach ( new i:Test2c_y_iter ()) { ++count; }
	foreach ( new i:Test2c_y_iter () ) { ++count; }
	foreach ( new i: Test2c_y_iter ()) { ++count; }
	foreach ( new i: Test2c_y_iter () ) { ++count; }
	foreach ( new i :Test2c_y_iter ()) { ++count; }
	foreach ( new i :Test2c_y_iter () ) { ++count; }
	foreach ( new i : Test2c_y_iter ()) { ++count; }
	foreach ( new i : Test2c_y_iter () ) { ++count; }
	new
		j;
	foreach(j:Test2c_y_iter ()) { ++count; }
	foreach(j:Test2c_y_iter () ) { ++count; }
	foreach(j: Test2c_y_iter ()) { ++count; }
	foreach(j: Test2c_y_iter () ) { ++count; }
	foreach(j :Test2c_y_iter ()) { ++count; }
	foreach(j :Test2c_y_iter () ) { ++count; }
	foreach(j : Test2c_y_iter ()) { ++count; }
	foreach(j : Test2c_y_iter () ) { ++count; }
	foreach( j:Test2c_y_iter ()) { ++count; }
	foreach( j:Test2c_y_iter () ) { ++count; }
	foreach( j: Test2c_y_iter ()) { ++count; }
	foreach( j: Test2c_y_iter () ) { ++count; }
	foreach( j :Test2c_y_iter ()) { ++count; }
	foreach( j :Test2c_y_iter () ) { ++count; }
	foreach( j : Test2c_y_iter ()) { ++count; }
	foreach( j : Test2c_y_iter () ) { ++count; }
	foreach (j:Test2c_y_iter ()) { ++count; }
	foreach (j:Test2c_y_iter () ) { ++count; }
	foreach (j: Test2c_y_iter ()) { ++count; }
	foreach (j: Test2c_y_iter () ) { ++count; }
	foreach (j :Test2c_y_iter ()) { ++count; }
	foreach (j :Test2c_y_iter () ) { ++count; }
	foreach (j : Test2c_y_iter ()) { ++count; }
	foreach (j : Test2c_y_iter () ) { ++count; }
	foreach ( j:Test2c_y_iter ()) { ++count; }
	foreach ( j:Test2c_y_iter () ) { ++count; }
	foreach ( j: Test2c_y_iter ()) { ++count; }
	foreach ( j: Test2c_y_iter () ) { ++count; }
	foreach ( j :Test2c_y_iter ()) { ++count; }
	foreach ( j :Test2c_y_iter () ) { ++count; }
	foreach ( j : Test2c_y_iter ()) { ++count; }
	foreach ( j : Test2c_y_iter () ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Syntax2d()
{
	new
		count = 0;
	foreach(new i:Test2d_y_iter ( )) { ++count; }
	foreach(new i:Test2d_y_iter ( ) ) { ++count; }
	foreach(new i: Test2d_y_iter ( )) { ++count; }
	foreach(new i: Test2d_y_iter ( ) ) { ++count; }
	foreach(new i :Test2d_y_iter ( )) { ++count; }
	foreach(new i :Test2d_y_iter ( ) ) { ++count; }
	foreach(new i : Test2d_y_iter ( )) { ++count; }
	foreach(new i : Test2d_y_iter ( ) ) { ++count; }
	foreach( new i:Test2d_y_iter ( )) { ++count; }
	foreach( new i:Test2d_y_iter ( ) ) { ++count; }
	foreach( new i: Test2d_y_iter ( )) { ++count; }
	foreach( new i: Test2d_y_iter ( ) ) { ++count; }
	foreach( new i :Test2d_y_iter ( )) { ++count; }
	foreach( new i :Test2d_y_iter ( ) ) { ++count; }
	foreach( new i : Test2d_y_iter ( )) { ++count; }
	foreach( new i : Test2d_y_iter ( ) ) { ++count; }
	foreach (new i:Test2d_y_iter ( )) { ++count; }
	foreach (new i:Test2d_y_iter ( ) ) { ++count; }
	foreach (new i: Test2d_y_iter ( )) { ++count; }
	foreach (new i: Test2d_y_iter ( ) ) { ++count; }
	foreach (new i :Test2d_y_iter ( )) { ++count; }
	foreach (new i :Test2d_y_iter ( ) ) { ++count; }
	foreach (new i : Test2d_y_iter ( )) { ++count; }
	foreach (new i : Test2d_y_iter ( ) ) { ++count; }
	foreach ( new i:Test2d_y_iter ( )) { ++count; }
	foreach ( new i:Test2d_y_iter ( ) ) { ++count; }
	foreach ( new i: Test2d_y_iter ( )) { ++count; }
	foreach ( new i: Test2d_y_iter ( ) ) { ++count; }
	foreach ( new i :Test2d_y_iter ( )) { ++count; }
	foreach ( new i :Test2d_y_iter ( ) ) { ++count; }
	foreach ( new i : Test2d_y_iter ( )) { ++count; }
	foreach ( new i : Test2d_y_iter ( ) ) { ++count; }
	new
		j;
	foreach(j:Test2d_y_iter ( )) { ++count; }
	foreach(j:Test2d_y_iter ( ) ) { ++count; }
	foreach(j: Test2d_y_iter ( )) { ++count; }
	foreach(j: Test2d_y_iter ( ) ) { ++count; }
	foreach(j :Test2d_y_iter ( )) { ++count; }
	foreach(j :Test2d_y_iter ( ) ) { ++count; }
	foreach(j : Test2d_y_iter ( )) { ++count; }
	foreach(j : Test2d_y_iter ( ) ) { ++count; }
	foreach( j:Test2d_y_iter ( )) { ++count; }
	foreach( j:Test2d_y_iter ( ) ) { ++count; }
	foreach( j: Test2d_y_iter ( )) { ++count; }
	foreach( j: Test2d_y_iter ( ) ) { ++count; }
	foreach( j :Test2d_y_iter ( )) { ++count; }
	foreach( j :Test2d_y_iter ( ) ) { ++count; }
	foreach( j : Test2d_y_iter ( )) { ++count; }
	foreach( j : Test2d_y_iter ( ) ) { ++count; }
	foreach (j:Test2d_y_iter ( )) { ++count; }
	foreach (j:Test2d_y_iter ( ) ) { ++count; }
	foreach (j: Test2d_y_iter ( )) { ++count; }
	foreach (j: Test2d_y_iter ( ) ) { ++count; }
	foreach (j :Test2d_y_iter ( )) { ++count; }
	foreach (j :Test2d_y_iter ( ) ) { ++count; }
	foreach (j : Test2d_y_iter ( )) { ++count; }
	foreach (j : Test2d_y_iter ( ) ) { ++count; }
	foreach ( j:Test2d_y_iter ( )) { ++count; }
	foreach ( j:Test2d_y_iter ( ) ) { ++count; }
	foreach ( j: Test2d_y_iter ( )) { ++count; }
	foreach ( j: Test2d_y_iter ( ) ) { ++count; }
	foreach ( j :Test2d_y_iter ( )) { ++count; }
	foreach ( j :Test2d_y_iter ( ) ) { ++count; }
	foreach ( j : Test2d_y_iter ( )) { ++count; }
	foreach ( j : Test2d_y_iter ( ) ) { ++count; }
	ASSERT(count == 7 * 2 * 32);
}

Test:y_iter_Array()
{
	new
		Iterator:Test3[5]<20>;
	Iter_Init(Test3);
	#pragma unused Iter_Single@Test3
	new
		count = 0;
	foreach (new i : Test3[1])
	{
		++count;
	}
	ASSERT(count == 0);
}

Test:y_iter_Multi()
{
	new
		Iterator: Test4<7, 11>;
	#pragma unused Iter_Multi@Test4
	new
		count = 0;
	foreach (new i : Test4<2>)
	{
		++count;
	}
	ASSERT(count == 0);
}

Test:y_iter_Clear()
{
	new
		Iterator:a<30>,
		Iterator:b<5, 30>,
		Iterator:c<5, 30>;
	ASSERT(Iter_Count(a) == 0);
	ASSERT(Iter_Count(b<0>) == 0);
	ASSERT(Iter_Count(b<1>) == 0);
	ASSERT(Iter_Count(b<2>) == 0);
	ASSERT(Iter_Count(b<3>) == 0);
	ASSERT(Iter_Count(b<4>) == 0);
	ASSERT(Iter_Count(c<0>) == 0);
	ASSERT(Iter_Count(c<1>) == 0);
	ASSERT(Iter_Count(c<2>) == 0);
	ASSERT(Iter_Count(c<3>) == 0);
	ASSERT(Iter_Count(c<4>) == 0);
	for (new i = 0; i != 10; ++i)
	{
		Iter_Add(a, i + 6);
		Iter_Add(b<3>, i * 2 + 1);
		Iter_Add(b<0>, i * 2);
		Iter_Add(c<1>, i * 2);
		Iter_Add(c<4>, i * 3);
	}
	ASSERT(Iter_Count(a) == 10);
	ASSERT(Iter_Count(b<0>) == 10);
	ASSERT(Iter_Count(b<1>) == 0);
	ASSERT(Iter_Count(b<2>) == 0);
	ASSERT(Iter_Count(b<3>) == 10);
	ASSERT(Iter_Count(b<4>) == 0);
	ASSERT(Iter_Count(c<0>) == 0);
	ASSERT(Iter_Count(c<1>) == 7);
	ASSERT(Iter_Count(c<2>) == 0);
	ASSERT(Iter_Count(c<3>) == 0);
	ASSERT(Iter_Count(c<4>) == 9);
	Iter_Clear(a);
	ASSERT(Iter_Count(a) == 0);
	Iter_Clear(b<0>);
	ASSERT(Iter_Count(b<0>) == 0);
	ASSERT(Iter_Count(b<1>) == 0);
	ASSERT(Iter_Count(b<2>) == 0);
	ASSERT(Iter_Count(b<3>) == 10);
	ASSERT(Iter_Count(b<4>) == 0);
	Iter_Clear(c<>);
	Iter_Clear(c< >);
	ASSERT(Iter_Count(c<0>) == 0);
	ASSERT(Iter_Count(c<1>) == 0);
	ASSERT(Iter_Count(c<2>) == 0);
	ASSERT(Iter_Count(c<3>) == 0);
	ASSERT(Iter_Count(c<4>) == 0);
}

Test:y_iter_ArrayMulti()
{
	new Iterator : Test5 [ 10 ] < 50, 25 >;
	new
		count = 0;
	Iter_Init(Test5);
	// Check the array is empty.
	foreach (new i : Test5[4]<3>)
	{
		++count;
	}
	ASSERT(count == 0);
	count = 0;
	// Check they are all added in the right place.
	Iter_Add(Test5[7]<40>, 0);
	Iter_Add(Test5[7]<40>, 4);
	Iter_Add(Test5[7]<40>, 8);
	Iter_Add(Test5[7]<40>, 12);
	Iter_Add(Test5[7]<40>, 16);
	Iter_Add(Test5[7]<40>, 20);
	Iter_Add(Test5[7]<40>, 24);
	foreach (new i : Test5[4]<3>)
	{
		++count;
	}
	ASSERT(count == 0);
	count = 0;
	foreach (new i : Test5[7]<40>)
	{
		++count;
	}
	ASSERT(count == 7);
	// Remove some.
	Iter_Remove(Test5[7]<40>, 24);
	Iter_Remove(Test5[7]<40>, 25);
	count = 0;
	foreach (new i : Test5[7]<40>)
	{
		++count;
	}
	ASSERT(count == 6);
	// Remove ones not in this iterator.
	Iter_Remove(Test5[7]<40>, 4);
	Iter_Remove(Test5[7]<40>, 5);
	ASSERT(Iter_Count(Test5[7]<40>) == 5);
	count = 0;
	foreach (new i : Test5[7]<40>)
	{
		++count;
	}
	ASSERT(count == 5);
	// Create a interleaved iterator.
	Iter_Add(Test5[7]<42>, 5);
	count = 0;
	ASSERT(Iter_Count(Test5[7]<40>) == 5);
	ASSERT(Iter_Count(Test5[7]<42>) == 1);
	foreach (new i : Test5[7]<42>)
	{
		++count;
	}
	ASSERT(count == 1);
	// Test that you can't remove something from the wrong interleaving.
	Iter_Remove(Test5[7]<40>, 5);
	count = 0;
	ASSERT(Iter_Count(Test5[7]<40>) == 5);
	ASSERT(Iter_Count(Test5[7]<42>) == 1);
	foreach (new i : Test5[7]<42>)
	{
		++count;
	}
	ASSERT(count == 1);
	Iter_Remove(Test5[7]<42>, 5);
	count = 0;
	ASSERT(Iter_Count(Test5[7]<40>) == 5);
	ASSERT(Iter_Count(Test5[7]<42>) == 0);
	foreach (new i : Test5[7]<42>)
	{
		++count;
	}
	ASSERT(count == 0);
}

Test:y_iter_Deprecate()
{
	foreach (Player, i)
	{
	}
}

