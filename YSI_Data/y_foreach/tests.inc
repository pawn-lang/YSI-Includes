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

#define Iterator@Test2a_y_iter iterstart(-1)

iterfunc static stock Test2b_y_iter(start )
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

#define Iterator@Test2b_y_iter iterstart(-1)

iterfunc static Test2c_y_iter (start)//__declspec(stock)
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

#define Iterator@Test2c_y_iter iterstart(-1)

iterfunc stock Test2d_y_iter (start )
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

#define Iterator@Test2d_y_iter iterstart(-1)

iterfunc stock TestState1_y_iter(&iterstate, cur)
{
	new
		ret = iterstate;
	iterstate = cur;
	return ret;
}

#define Iterator@TestState1_y_iter iterstate(-1, 800)

Test:TestState1_y_iter()
{
	new
		count = 0;
	foreach (new i : TestState1_y_iter())
	{
		ASSERT(i == 800);
		++count;
	}
	ASSERT(count == 1);
}

iterfunc stock TestState2_y_iter(iterstate[2], cur)
{
	new
		ret = iterstate[0];
	iterstate[0] = iterstate[1];
	iterstate[1] = cur;
	return ret;
}

#define Iterator@TestState2_y_iter iterstate(-1, 500, 600)

Test:TestState2_y_iter()
{
	new
		count = 0;
	foreach (new i : TestState2_y_iter())
	{
		if (count)
			ASSERT(i == 600);
		else
			ASSERT(i == 500);
		++count;
	}
	ASSERT(count == 2);
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
	foreach (new i : Range(0, 10, 2))
	{
		ASSERT(0 <= i < 10);
		++count;
	}
	ASSERT(count == 5);
	count = 0;
	foreach (new i : Range(0, 9, 2))
	{
		ASSERT(0 <= i < 10);
		++count;
	}
	ASSERT(count == 5);
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
	count = 0;
	foreach (new i : Range(10, 5, -1))
	{
		++count;
	}
	ASSERT(count == 5);
	count = 0;
	foreach (new i : Range(10, 5, -5))
	{
		++count;
	}
	ASSERT(count == 1);
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

Test:y_iter_RandomRemove1()
{
	new
		Iterator:iter<10>;
	Iter_Add(iter, 2);
	ASSERT(Iter_RandomRemove(iter) != cellmin);
	ASSERT(Iter_RandomRemove(iter) == cellmin);
	ASSERT(Iter_RandomRemove(iter) == cellmin);
	ASSERT(Iter_RandomRemove(iter) == cellmin);
	ASSERT(Iter_Count(iter) == 0);
}

Test:y_iter_RandomRemove2()
{
	new
		Iterator:iter[3]<10>;
	Iter_Init(iter);
	Iter_Add(iter[0], 2);
	Iter_Add(iter[0], 3);
	Iter_Add(iter[0], 4);
	Iter_Add(iter[0], 5);
	Iter_Add(iter[0], 6);
	Iter_Add(iter[0], 9);
	ASSERT(Iter_RandomRemove(iter[0]) != cellmin);
	ASSERT(Iter_RandomRemove(iter[0]) != cellmin);
	ASSERT(Iter_RandomRemove(iter[0]) != cellmin);
	ASSERT(Iter_RandomRemove(iter[0]) != cellmin);
	ASSERT(Iter_RandomRemove(iter[0]) != cellmin);
	ASSERT(Iter_RandomRemove(iter[0]) != cellmin);
	ASSERT(Iter_RandomRemove(iter[0]) == cellmin);
	ASSERT(Iter_RandomRemove(iter[0]) == cellmin);
	ASSERT(Iter_RandomRemove(iter[0]) == cellmin);
	ASSERT(Iter_RandomRemove(iter[0]) == cellmin);
	ASSERT(Iter_Count(iter[0]) == 0);
	ASSERT(Iter_Count(iter[1]) == 0);
}

Test:y_iter_RandomRemove3()
{
	new
		Iterator:iter<2, 10>;
	Iter_Add(iter<0>, 2);
	ASSERT(Iter_RandomRemove(iter<0>) != cellmin);
	ASSERT(Iter_RandomRemove(iter<1>) == cellmin);
	ASSERT(Iter_RandomRemove(iter<0>) == cellmin);
	ASSERT(Iter_Count(iter<0>) == 0);
	ASSERT(Iter_Count(iter<1>) == 0);
}

Test:y_iter_RandomAdd1()
{
	new
		Iterator:iter<10>;
	Iter_Add(iter, 2);
	ASSERT(Iter_RandomAdd(iter) != cellmin);
	ASSERT(Iter_RandomAdd(iter) != cellmin);
	ASSERT(Iter_RandomAdd(iter) != cellmin);
	ASSERT(Iter_RandomAdd(iter) != cellmin);
	ASSERT(Iter_RandomAdd(iter) != cellmin);
	ASSERT(Iter_RandomAdd(iter) != cellmin);
	ASSERT(Iter_RandomAdd(iter) != cellmin);
	ASSERT(Iter_RandomAdd(iter) != cellmin);
	ASSERT(Iter_RandomAdd(iter) != cellmin);
	ASSERT(Iter_RandomAdd(iter) == cellmin);
	ASSERT(Iter_RandomAdd(iter) == cellmin);
	ASSERT(Iter_RandomAdd(iter) == cellmin);
	ASSERT(Iter_Count(iter) == 10);
}

Test:y_iter_RandomAdd2()
{
	new
		Iterator:iter[3]<10>;
	Iter_Init(iter);
	Iter_Add(iter[0], 2);
	ASSERT(Iter_RandomAdd(iter[0]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[0]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[0]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[0]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[0]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[0]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[0]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[0]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[0]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[0]) == cellmin);
	ASSERT(Iter_RandomAdd(iter[0]) == cellmin);
	ASSERT(Iter_RandomAdd(iter[0]) == cellmin);
	ASSERT(Iter_RandomAdd(iter[1]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[1]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[1]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[1]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[1]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[1]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[1]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[1]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[1]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[1]) != cellmin);
	ASSERT(Iter_RandomAdd(iter[0]) == cellmin);
	ASSERT(Iter_RandomAdd(iter[0]) == cellmin);
	ASSERT(Iter_RandomAdd(iter[0]) == cellmin);
	ASSERT(Iter_Count(iter[0]) == 10);
	ASSERT(Iter_Count(iter[1]) == 10);
}

Test:y_iter_RandomAdd3()
{
	new
		Iterator:iter<2, 10>;
	Iter_Add(iter<0>, 2);
	ASSERT(Iter_RandomAdd(iter<0>) != cellmin);
	ASSERT(Iter_RandomAdd(iter<0>) != cellmin);
	ASSERT(Iter_RandomAdd(iter<0>) != cellmin);
	ASSERT(Iter_RandomAdd(iter<1>) != cellmin);
	ASSERT(Iter_RandomAdd(iter<1>) != cellmin);
	ASSERT(Iter_RandomAdd(iter<1>) != cellmin);
	ASSERT(Iter_RandomAdd(iter<1>) != cellmin);
	ASSERT(Iter_RandomAdd(iter<1>) != cellmin);
	ASSERT(Iter_RandomAdd(iter<1>) != cellmin);
	ASSERT(Iter_RandomAdd(iter<0>) == cellmin);
	ASSERT(Iter_RandomAdd(iter<1>) == cellmin);
	ASSERT(Iter_RandomAdd(iter<0>) == cellmin);
	ASSERT(Iter_Count(iter<0>) == 4);
	ASSERT(Iter_Count(iter<1>) == 6);
}

Test:y_iter_RandomFree1()
{
	new
		Iterator:iter<10>,
		vals[10];
	Iter_Add(iter, 2);
	Iter_Add(iter, 4);
	Iter_Add(iter, 6);
	Iter_Add(iter, 3);
	Iter_Add(iter, 6);
	Iter_Add(iter, 9);
	for (new i = 0; i != 10000; ++i)
	{
		new v = Iter_RandomFree(iter);
		ASSERT(v != 2);
		ASSERT(v != 4);
		ASSERT(v != 6);
		ASSERT(v != 3);
		ASSERT(v != 9);
		++vals[v];
	}
	ASSERT(vals[0] != 0);
	ASSERT(vals[1] != 0);
	ASSERT(vals[5] != 0);
	ASSERT(vals[7] != 0);
	ASSERT(vals[8] != 0);
	Iter_Add(iter, 0);
	Iter_Add(iter, 1);
	Iter_Add(iter, 5);
	Iter_Add(iter, 7);
	Iter_Add(iter, 8);
	ASSERT(Iter_RandomFree(iter) == cellmin);
}

Test:y_iter_RandomFree2()
{
	new
		Iterator:iter<2, 10>,
		vals[10];
	Iter_Add(iter<0>, 2);
	Iter_Add(iter<0>, 4);
	Iter_Add(iter<0>, 6);
	Iter_Add(iter<1>, 3);
	Iter_Add(iter<1>, 6);
	Iter_Add(iter<1>, 9);
	for (new i = 0; i != 10000; ++i)
	{
		new v = Iter_RandomFree(iter<>);
		ASSERT(v != 2);
		ASSERT(v != 4);
		ASSERT(v != 6);
		ASSERT(v != 3);
		ASSERT(v != 9);
		++vals[v];
	}
	ASSERT(vals[0] != 0);
	ASSERT(vals[1] != 0);
	ASSERT(vals[5] != 0);
	ASSERT(vals[7] != 0);
	ASSERT(vals[8] != 0);
	Iter_Add(iter<0>, 0);
	Iter_Add(iter<0>, 1);
	Iter_Add(iter<0>, 5);
	Iter_Add(iter<0>, 7);
	Iter_Add(iter<0>, 8);
	ASSERT(Iter_RandomFree(iter<0>) == cellmin);
	ASSERT(Iter_RandomFree(iter<1>) == cellmin);
}

Test:y_iter_RandomFree3()
{
	new
		Iterator:iter[2]<10>,
		vals[2][10];
	Iter_Init(iter);
	Iter_Add(iter[0], 2);
	Iter_Add(iter[0], 4);
	Iter_Add(iter[0], 6);
	Iter_Add(iter[1], 3);
	Iter_Add(iter[1], 6);
	Iter_Add(iter[1], 9);
	for (new v, i = 0; i != 10000; ++i)
	{
		v = Iter_RandomFree(iter[0]);
		ASSERT(v != 2);
		ASSERT(v != 4);
		ASSERT(v != 6);
		++vals[0][v];
		v = Iter_RandomFree(iter[1]);
		ASSERT(v != 6);
		ASSERT(v != 3);
		ASSERT(v != 9);
		++vals[1][v];
	}
	ASSERT(vals[0][0] != 0);
	ASSERT(vals[0][1] != 0);
	ASSERT(vals[0][3] != 0);
	ASSERT(vals[0][5] != 0);
	ASSERT(vals[0][7] != 0);
	ASSERT(vals[0][8] != 0);
	ASSERT(vals[0][9] != 0);
	ASSERT(vals[1][0] != 0);
	ASSERT(vals[1][1] != 0);
	ASSERT(vals[1][2] != 0);
	ASSERT(vals[1][4] != 0);
	ASSERT(vals[1][5] != 0);
	ASSERT(vals[1][7] != 0);
	ASSERT(vals[1][8] != 0);
	Iter_Add(iter[0], 0);
	Iter_Add(iter[0], 1);
	Iter_Add(iter[0], 3);
	Iter_Add(iter[0], 5);
	Iter_Add(iter[0], 7);
	Iter_Add(iter[0], 8);
	Iter_Add(iter[0], 9);
	ASSERT(Iter_RandomFree(iter[0]) == cellmin);
	ASSERT(Iter_RandomFree(iter[1]) != cellmin);
	Iter_Remove(iter[0], 0);
	Iter_Remove(iter[0], 1);
	Iter_Remove(iter[0], 2);
	Iter_Remove(iter[0], 3);
	Iter_Add(iter[1], 0);
	Iter_Add(iter[1], 1);
	Iter_Add(iter[1], 2);
	Iter_Add(iter[1], 4);
	Iter_Add(iter[1], 5);
	Iter_Add(iter[1], 7);
	Iter_Add(iter[1], 8);
	ASSERT(Iter_RandomFree(iter[0]) != cellmin);
	ASSERT(Iter_RandomFree(iter[1]) == cellmin);
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
	Iter_Add(iter[_:gg], 1);
	Iter_Clear(iter[_:gg]);
}

Test:y_iter_Iter_Init1()
{
	new
		Iterator:iter[10]<20>;
	#pragma unused Iter_Single@iter
	Iter_Init(iter);
	ASSERT(Iter_TrueArray(iter)[0][20] == 20);
	ASSERT(Iter_TrueArray(iter)[0][19] <= 19);
	ASSERT(Iter_TrueArray(iter)[1][20] == 20);
	ASSERT(Iter_TrueArray(iter)[1][19] <= 19);
	ASSERT(Iter_TrueArray(iter)[9][20] == 20);
	ASSERT(Iter_TrueArray(iter)[9][19] <= 19);
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

Test:y_iter_Iter_Contains1()
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

Test:y_iter_Iter_Contains2()
{
	new
		Iterator:iter1[4]<60>;
	Iter_Init(iter1);
	ASSERT(!Iter_Contains(iter1[0], 7));
	ASSERT(!Iter_Contains(iter1[1], 7));
	Iter_Add(iter1[0], 7);
	ASSERT(Iter_Contains(iter1[0], 7));
	ASSERT(!Iter_Contains(iter1[1], 7));
	new
		Iterator:iter2[7]<5, 60>;
	Iter_Init(iter2);
	ASSERT(!Iter_Contains(iter2[3]<>, 5));
	ASSERT(!Iter_Contains(iter2[3]<0>, 5));
	ASSERT(!Iter_Contains(iter2[3]<4>, 5));
	Iter_Add(iter2[3]<4>, 5);
	ASSERT(Iter_Contains(iter2[3]<>, 5));
	ASSERT(Iter_Contains(iter2[3]< >, 5));
	ASSERT(!Iter_Contains(iter2[3]<0>, 5));
	ASSERT(Iter_Contains(iter2[3]<4>, 5));
	ASSERT(!Iter_Contains(iter2[5]<>, 5));
	ASSERT(!Iter_Contains(iter2[5]< >, 5));
	ASSERT(!Iter_Contains(iter2[5]<0>, 5));
	ASSERT(!Iter_Contains(iter2[5]<4>, 5));
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

Test:y_iter_Tag()
{
	new
		Iterator:Group:iter1<60>;
	Iter_Add(iter1, Group:33);
	#pragma tabsize 4
	/* ====================================================================== */
	/* | THERE IS MEANT TO BE A WARNING ON THIS LINE                        | */
	/* |                                                                    | */
	/* | */ Iter_Add(iter1, 44);                                         /* | */
	/* |                                                                    | */
	/* | It tests that iterators use tags correctly and warn otherwise.     | */
	/* ====================================================================== */
	#pragma tabsize 4
	Iter_Add(iter1, Group:55);
	Iter_Add(iter1, Group:22);
	Iter_Add(iter1, Group:11);
	#pragma tabsize 4
	/* ====================================================================== */
	/* | THERE IS MEANT TO BE A WARNING ON THIS LINE                        | */
	/* |                                                                    | */
	/* | */ Iter_Remove(iter1, 11);                                      /* | */
	/* |                                                                    | */
	/* | It tests that iterators use tags correctly and warn otherwise.     | */
	/* ====================================================================== */
	#pragma tabsize 4
	Iter_Alloc(iter1);
	foreach (new Group:i : iter1)
	{
		ASSERT(i / Group:11 * Group:11 == i);
	}
}

Test:y_iter_Iter_Alloc()
{
	new
		Iterator:iter1<60>;
	ASSERT(Iter_Alloc(iter1) == 0);
	ASSERT(Iter_Alloc(iter1) == 1);
	ASSERT(Iter_Alloc(iter1) == 2);
	ASSERT(Iter_Alloc(iter1) == 3);
	ASSERT(Iter_Alloc(iter1) == 4);
	ASSERT(Iter_Alloc(iter1) == 5);
	Iter_Remove(iter1, 5);
	ASSERT(Iter_Alloc(iter1) == 5);
	ASSERT(Iter_Alloc(iter1) == 6);
	ASSERT(Iter_Alloc(iter1) == 7);
	ASSERT(Iter_Alloc(iter1) == 8);
	ASSERT(Iter_Alloc(iter1) == 9);
	Iter_Remove(iter1, 5);
	Iter_Remove(iter1, 6);
	Iter_Remove(iter1, 7);
	ASSERT(Iter_Alloc(iter1) == 5);
	ASSERT(Iter_Alloc(iter1) == 6);
	ASSERT(Iter_Alloc(iter1) == 7);
	ASSERT(Iter_Alloc(iter1) == 10);
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

Test:y_iter_InfiniteLoop()
{
    new Iterator:iter<20>;
    Iter_Add(iter, 1);
    Iter_Add(iter, 2);
    Iter_Remove(iter, 1);
    Iter_Remove(iter, 2);
    foreach (new i : iter)
    {
        ASSERT(false);
        return;
    }
	ASSERT(true);
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

stock iterfunc y_iter_Syntax6(&iterstate, cur, inc)
{
	cur += (inc * iterstate);
	return cur;
}

#define Iterator@y_iter_Syntax6 iterstate(0, 1024)

Test:y_iter_Syntax6a()
{
	new
		count = 0;
	foreach (new i : y_iter_Syntax6(1024))
	{
		ASSERT(i % 1048576 == 0);
		++count;
	}
	ASSERT(count == 4095);
}

Test:y_iter_Syntax6b()
{
	new
		count = 0;
	foreach(new i:y_iter_Syntax6(1024)) { ++count; }
	foreach(new i:y_iter_Syntax6(1024) ) { ++count; }
	foreach(new i: y_iter_Syntax6(1024)) { ++count; }
	foreach(new i: y_iter_Syntax6(1024) ) { ++count; }
	foreach(new i :y_iter_Syntax6(1024)) { ++count; }
	foreach(new i :y_iter_Syntax6(1024) ) { ++count; }
	foreach(new i : y_iter_Syntax6(1024)) { ++count; }
	foreach(new i : y_iter_Syntax6(1024) ) { ++count; }
	foreach( new i:y_iter_Syntax6(1024)) { ++count; }
	foreach( new i:y_iter_Syntax6(1024) ) { ++count; }
	foreach( new i: y_iter_Syntax6(1024)) { ++count; }
	foreach( new i: y_iter_Syntax6(1024) ) { ++count; }
	foreach( new i :y_iter_Syntax6(1024)) { ++count; }
	foreach( new i :y_iter_Syntax6(1024) ) { ++count; }
	foreach( new i : y_iter_Syntax6(1024)) { ++count; }
	foreach( new i : y_iter_Syntax6(1024) ) { ++count; }
	foreach (new i:y_iter_Syntax6(1024)) { ++count; }
	foreach (new i:y_iter_Syntax6(1024) ) { ++count; }
	foreach (new i: y_iter_Syntax6(1024)) { ++count; }
	foreach (new i: y_iter_Syntax6(1024) ) { ++count; }
	foreach (new i :y_iter_Syntax6(1024)) { ++count; }
	foreach (new i :y_iter_Syntax6(1024) ) { ++count; }
	foreach (new i : y_iter_Syntax6(1024)) { ++count; }
	foreach (new i : y_iter_Syntax6(1024) ) { ++count; }
	foreach ( new i:y_iter_Syntax6(1024)) { ++count; }
	foreach ( new i:y_iter_Syntax6(1024) ) { ++count; }
	foreach ( new i: y_iter_Syntax6(1024)) { ++count; }
	foreach ( new i: y_iter_Syntax6(1024) ) { ++count; }
	foreach ( new i :y_iter_Syntax6(1024)) { ++count; }
	foreach ( new i :y_iter_Syntax6(1024) ) { ++count; }
	foreach ( new i : y_iter_Syntax6(1024)) { ++count; }
	foreach ( new i : y_iter_Syntax6(1024) ) { ++count; }
	ASSERT(count == 4095 * 1 * 32);
#if _DEBUG
	new TODO@issue_217;
#endif
//	new
//		j;
//	foreach(j:y_iter_Syntax6(1024)) { ++count; }
//	foreach(j:y_iter_Syntax6(1024) ) { ++count; }
//	foreach(j: y_iter_Syntax6(1024)) { ++count; }
//	foreach(j: y_iter_Syntax6(1024) ) { ++count; }
//	foreach(j :y_iter_Syntax6(1024)) { ++count; }
//	foreach(j :y_iter_Syntax6(1024) ) { ++count; }
//	foreach(j : y_iter_Syntax6(1024)) { ++count; }
//	foreach(j : y_iter_Syntax6(1024) ) { ++count; }
//	foreach( j:y_iter_Syntax6(1024)) { ++count; }
//	foreach( j:y_iter_Syntax6(1024) ) { ++count; }
//	foreach( j: y_iter_Syntax6(1024)) { ++count; }
//	foreach( j: y_iter_Syntax6(1024) ) { ++count; }
//	foreach( j :y_iter_Syntax6(1024)) { ++count; }
//	foreach( j :y_iter_Syntax6(1024) ) { ++count; }
//	foreach( j : y_iter_Syntax6(1024)) { ++count; }
//	foreach( j : y_iter_Syntax6(1024) ) { ++count; }
//	foreach (j:y_iter_Syntax6(1024)) { ++count; }
//	foreach (j:y_iter_Syntax6(1024) ) { ++count; }
//	foreach (j: y_iter_Syntax6(1024)) { ++count; }
//	foreach (j: y_iter_Syntax6(1024) ) { ++count; }
//	foreach (j :y_iter_Syntax6(1024)) { ++count; }
//	foreach (j :y_iter_Syntax6(1024) ) { ++count; }
//	foreach (j : y_iter_Syntax6(1024)) { ++count; }
//	foreach (j : y_iter_Syntax6(1024) ) { ++count; }
//	foreach ( j:y_iter_Syntax6(1024)) { ++count; }
//	foreach ( j:y_iter_Syntax6(1024) ) { ++count; }
//	foreach ( j: y_iter_Syntax6(1024)) { ++count; }
//	foreach ( j: y_iter_Syntax6(1024) ) { ++count; }
//	foreach ( j :y_iter_Syntax6(1024)) { ++count; }
//	foreach ( j :y_iter_Syntax6(1024) ) { ++count; }
//	foreach ( j : y_iter_Syntax6(1024)) { ++count; }
//	foreach ( j : y_iter_Syntax6(1024) ) { ++count; }
//	ASSERT(count == 4095 * 2 * 32);
}

Test:y_iter_Syntax6c()
{
	new
		count = 0;
	foreach(new i:y_iter_Syntax6[1024]) { ++count; }
	foreach(new i:y_iter_Syntax6[1024] ) { ++count; }
	foreach(new i: y_iter_Syntax6[1024]) { ++count; }
	foreach(new i: y_iter_Syntax6[1024] ) { ++count; }
	foreach(new i :y_iter_Syntax6[1024]) { ++count; }
	foreach(new i :y_iter_Syntax6[1024] ) { ++count; }
	foreach(new i : y_iter_Syntax6[1024]) { ++count; }
	foreach(new i : y_iter_Syntax6[1024] ) { ++count; }
	foreach( new i:y_iter_Syntax6[1024]) { ++count; }
	foreach( new i:y_iter_Syntax6[1024] ) { ++count; }
	foreach( new i: y_iter_Syntax6[1024]) { ++count; }
	foreach( new i: y_iter_Syntax6[1024] ) { ++count; }
	foreach( new i :y_iter_Syntax6[1024]) { ++count; }
	foreach( new i :y_iter_Syntax6[1024] ) { ++count; }
	foreach( new i : y_iter_Syntax6[1024]) { ++count; }
	foreach( new i : y_iter_Syntax6[1024] ) { ++count; }
	foreach (new i:y_iter_Syntax6[1024]) { ++count; }
	foreach (new i:y_iter_Syntax6[1024] ) { ++count; }
	foreach (new i: y_iter_Syntax6[1024]) { ++count; }
	foreach (new i: y_iter_Syntax6[1024] ) { ++count; }
	foreach (new i :y_iter_Syntax6[1024]) { ++count; }
	foreach (new i :y_iter_Syntax6[1024] ) { ++count; }
	foreach (new i : y_iter_Syntax6[1024]) { ++count; }
	foreach (new i : y_iter_Syntax6[1024] ) { ++count; }
	foreach ( new i:y_iter_Syntax6[1024]) { ++count; }
	foreach ( new i:y_iter_Syntax6[1024] ) { ++count; }
	foreach ( new i: y_iter_Syntax6[1024]) { ++count; }
	foreach ( new i: y_iter_Syntax6[1024] ) { ++count; }
	foreach ( new i :y_iter_Syntax6[1024]) { ++count; }
	foreach ( new i :y_iter_Syntax6[1024] ) { ++count; }
	foreach ( new i : y_iter_Syntax6[1024]) { ++count; }
	foreach ( new i : y_iter_Syntax6[1024] ) { ++count; }
	ASSERT(count == 4095 * 1 * 32);
#if _DEBUG
	new TODO@issue_217;
#endif
//	new
//		j;
//	foreach(j:y_iter_Syntax6[1024]) { ++count; }
//	foreach(j:y_iter_Syntax6[1024] ) { ++count; }
//	foreach(j: y_iter_Syntax6[1024]) { ++count; }
//	foreach(j: y_iter_Syntax6[1024] ) { ++count; }
//	foreach(j :y_iter_Syntax6[1024]) { ++count; }
//	foreach(j :y_iter_Syntax6[1024] ) { ++count; }
//	foreach(j : y_iter_Syntax6[1024]) { ++count; }
//	foreach(j : y_iter_Syntax6[1024] ) { ++count; }
//	foreach( j:y_iter_Syntax6[1024]) { ++count; }
//	foreach( j:y_iter_Syntax6[1024] ) { ++count; }
//	foreach( j: y_iter_Syntax6[1024]) { ++count; }
//	foreach( j: y_iter_Syntax6[1024] ) { ++count; }
//	foreach( j :y_iter_Syntax6[1024]) { ++count; }
//	foreach( j :y_iter_Syntax6[1024] ) { ++count; }
//	foreach( j : y_iter_Syntax6[1024]) { ++count; }
//	foreach( j : y_iter_Syntax6[1024] ) { ++count; }
//	foreach (j:y_iter_Syntax6[1024]) { ++count; }
//	foreach (j:y_iter_Syntax6[1024] ) { ++count; }
//	foreach (j: y_iter_Syntax6[1024]) { ++count; }
//	foreach (j: y_iter_Syntax6[1024] ) { ++count; }
//	foreach (j :y_iter_Syntax6[1024]) { ++count; }
//	foreach (j :y_iter_Syntax6[1024] ) { ++count; }
//	foreach (j : y_iter_Syntax6[1024]) { ++count; }
//	foreach (j : y_iter_Syntax6[1024] ) { ++count; }
//	foreach ( j:y_iter_Syntax6[1024]) { ++count; }
//	foreach ( j:y_iter_Syntax6[1024] ) { ++count; }
//	foreach ( j: y_iter_Syntax6[1024]) { ++count; }
//	foreach ( j: y_iter_Syntax6[1024] ) { ++count; }
//	foreach ( j :y_iter_Syntax6[1024]) { ++count; }
//	foreach ( j :y_iter_Syntax6[1024] ) { ++count; }
//	foreach ( j : y_iter_Syntax6[1024]) { ++count; }
//	foreach ( j : y_iter_Syntax6[1024] ) { ++count; }
//	ASSERT(count == 4095 * 2 * 32);
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

Test:y_iter_Syntax2e()
{
	new
		count = 0;
	foreach(new i:Test2a_y_iter) { ++count; }
	foreach(new i:Test2a_y_iter ) { ++count; }
	foreach(new i: Test2a_y_iter) { ++count; }
	foreach(new i: Test2a_y_iter ) { ++count; }
	foreach(new i :Test2a_y_iter) { ++count; }
	foreach(new i :Test2a_y_iter ) { ++count; }
	foreach(new i : Test2a_y_iter) { ++count; }
	foreach(new i : Test2a_y_iter ) { ++count; }
	foreach( new i:Test2a_y_iter) { ++count; }
	foreach( new i:Test2a_y_iter ) { ++count; }
	foreach( new i: Test2a_y_iter) { ++count; }
	foreach( new i: Test2a_y_iter ) { ++count; }
	foreach( new i :Test2a_y_iter) { ++count; }
	foreach( new i :Test2a_y_iter ) { ++count; }
	foreach( new i : Test2a_y_iter) { ++count; }
	foreach( new i : Test2a_y_iter ) { ++count; }
	foreach (new i:Test2a_y_iter) { ++count; }
	foreach (new i:Test2a_y_iter ) { ++count; }
	foreach (new i: Test2a_y_iter) { ++count; }
	foreach (new i: Test2a_y_iter ) { ++count; }
	foreach (new i :Test2a_y_iter) { ++count; }
	foreach (new i :Test2a_y_iter ) { ++count; }
	foreach (new i : Test2a_y_iter) { ++count; }
	foreach (new i : Test2a_y_iter ) { ++count; }
	foreach ( new i:Test2a_y_iter) { ++count; }
	foreach ( new i:Test2a_y_iter ) { ++count; }
	foreach ( new i: Test2a_y_iter) { ++count; }
	foreach ( new i: Test2a_y_iter ) { ++count; }
	foreach ( new i :Test2a_y_iter) { ++count; }
	foreach ( new i :Test2a_y_iter ) { ++count; }
	foreach ( new i : Test2a_y_iter) { ++count; }
	foreach ( new i : Test2a_y_iter ) { ++count; }
	new
		j;
	foreach(j:Test2a_y_iter) { ++count; }
	foreach(j:Test2a_y_iter ) { ++count; }
	foreach(j: Test2a_y_iter) { ++count; }
	foreach(j: Test2a_y_iter ) { ++count; }
	foreach(j :Test2a_y_iter) { ++count; }
	foreach(j :Test2a_y_iter ) { ++count; }
	foreach(j : Test2a_y_iter) { ++count; }
	foreach(j : Test2a_y_iter ) { ++count; }
	foreach( j:Test2a_y_iter) { ++count; }
	foreach( j:Test2a_y_iter ) { ++count; }
	foreach( j: Test2a_y_iter) { ++count; }
	foreach( j: Test2a_y_iter ) { ++count; }
	foreach( j :Test2a_y_iter) { ++count; }
	foreach( j :Test2a_y_iter ) { ++count; }
	foreach( j : Test2a_y_iter) { ++count; }
	foreach( j : Test2a_y_iter ) { ++count; }
	foreach (j:Test2a_y_iter) { ++count; }
	foreach (j:Test2a_y_iter ) { ++count; }
	foreach (j: Test2a_y_iter) { ++count; }
	foreach (j: Test2a_y_iter ) { ++count; }
	foreach (j :Test2a_y_iter) { ++count; }
	foreach (j :Test2a_y_iter ) { ++count; }
	foreach (j : Test2a_y_iter) { ++count; }
	foreach (j : Test2a_y_iter ) { ++count; }
	foreach ( j:Test2a_y_iter) { ++count; }
	foreach ( j:Test2a_y_iter ) { ++count; }
	foreach ( j: Test2a_y_iter) { ++count; }
	foreach ( j: Test2a_y_iter ) { ++count; }
	foreach ( j :Test2a_y_iter) { ++count; }
	foreach ( j :Test2a_y_iter ) { ++count; }
	foreach ( j : Test2a_y_iter) { ++count; }
	foreach ( j : Test2a_y_iter ) { ++count; }
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

#if _FOREACH_PLAYERS
	Test:y_iter_Deprecate()
	{
		#pragma tabsize 4
		/* ================================================================== */
		/* | THERE IS MEANT TO BE A WARNING ON THIS LINE                    | */
		/* |                                                                | */
		/* | */ foreach (Player, i)                                      /* | */
		/* |                                                                | */
		/* | It tests that the old syntax is nicely deprecated.             | */
		/* ================================================================== */
		#pragma tabsize 4
		{
		}
	}
#endif

Test:y_iter_Random()
{
	new
		c = 0;
	foreach (new i : Random(10))
	{
		++c;
	}
	ASSERT(c == 10);
	foreach (new i : Random(1000, -5, 10))
	{
		++c;
		ASSERT(-5 <= i < 10);
	}
	ASSERT(c == 1010);
}

Test:y_iter_RandomNested()
{
	new
		c = 0;
	foreach (new i : Random(10, 20))
	{
		ASSERT(0 <= i < 20);
		foreach (new j : Random(10, -20, 20))
		{
			ASSERT(-20 <= j < 20);
			++c;
		}
	}
	ASSERT(c == 100);
}

Test:y_iter_Powers()
{
	new
		c = 1;
	foreach (new i : Powers(2))
	{
		ASSERT(i == c);
		c *= 2;
	}
	ASSERT(c == 0x40000000 * 2);
}

Test:y_iter_Fib()
{
	new
		a = 0,
		b = 1;
	foreach (new i : Fib())
	{
		ASSERT(i == a);
		b = a + b;
		a = b - a;
	}
}

Test:y_iter_Null()
{
	new
		c = 0,
		arr[10] = {1, 2, 0, 3, 4, 0, 5, 0, 0, 7};
	foreach (new i : Null(arr))
	{
		++c;
		ASSERT(i == 2 || i == 5 || i == 7 || i == 8);
	}
	ASSERT(c == 4);
}

Test:y_iter_Filter1()
{
	new
		c = 0,
		arr[10] = {1, 2, 0, 3, 4, 0, 5, 0, 0, 7};
	foreach (new i : Filter(0, arr))
	{
		++c;
		ASSERT(i == 2 || i == 5 || i == 7 || i == 8);
	}
	ASSERT(c == 4);
}

Test:y_iter_Filter2()
{
	new
		c = 0,
		arr[10] = {1, 2, 0, 3, 2, 0, 5, 0, 2, 7};
	foreach (new i : Filter(2, arr))
	{
		++c;
		ASSERT(i == 1 || i == 4 || i == 8);
	}
	ASSERT(c == 3);
}

Test:y_iter_NonNull()
{
	new
		c = 0,
		arr[10] = {1, 2, 0, 3, 4, 0, 5, 0, 0, 7};
	foreach (new i : NonNull(arr))
	{
		++c;
		ASSERT(i != 2 && i != 5 && i != 7 && i != 8);
	}
	ASSERT(c == 6);
}

Test:y_iter_Until()
{
	new
		c = 0,
		arr[10] = {1, 2, 0, 3, 4, 0, 5, 0, 0, 7};
	foreach (new i : Until(5, arr))
	{
		++c;
		ASSERT(0 <= i < 6);
	}
	ASSERT(c == 6);
}

Test:y_iter_All1()
{
	new Iterator:a<10>;
	Iter_Add(a, 3);
	Iter_Add(a, 4);
	Iter_Add(a, 7);
	Iter_Add(a, 9);
	new count = 0;
	foreach (new i : All(a))
	{
		ASSERT(i == 3 || i == 4 || i == 7 || i == 9);
		++count;
	}
	ASSERT(count == 4);
}

Test:y_iter_None1()
{
	new Iterator:a<10>;
	Iter_Add(a, 3);
	Iter_Add(a, 4);
	Iter_Add(a, 7);
	Iter_Add(a, 9);
	new count = 0;
	foreach (new i : None(a))
	{
		ASSERT(i != 3 && i != 4 && i != 7 && i != 9);
		++count;
	}
	ASSERT(count == 6);
}

Test:y_iter_All2()
{
	new Iterator:a<3, 10>;
	Iter_Add(a<0>, 3);
	Iter_Add(a<2>, 4);
	Iter_Add(a<2>, 7);
	Iter_Add(a<1>, 9);
	new count = 0;
	foreach (new i : All(a<>))
	{
		ASSERT(i == 3 || i == 4 || i == 7 || i == 9);
		++count;
	}
	ASSERT(count == 4);
}

Test:y_iter_None2()
{
	new Iterator:a<3, 10>;
	Iter_Add(a<2>, 3);
	Iter_Add(a<0>, 4);
	Iter_Add(a<0>, 7);
	Iter_Add(a<0>, 9);
	new count = 0;
	foreach (new i : None(a<>))
	{
		ASSERT(i != 3 && i != 4 && i != 7 && i != 9);
		++count;
	}
	ASSERT(count == 6);
}

Test:y_iter_Index1()
{
	new Iterator:a<20>;
	Iter_Add(a, 6);
	Iter_Add(a, 8);
	Iter_Add(a, 9);
	Iter_Add(a, 14);
	Iter_Add(a, 17);
	Iter_Add(a, 19);
	ASSERT(Iter_Index(a, -100) == cellmin);
	ASSERT(Iter_Index(a, -100, true) == cellmin);
	ASSERT(Iter_Index(a, -1) == cellmin);
	ASSERT(Iter_Index(a, -1, true) == cellmin);
	ASSERT(Iter_Index(a, 0) == 6);
	ASSERT(Iter_Index(a, 0, true) == 6);
	ASSERT(Iter_Index(a, 1) == 8);
	ASSERT(Iter_Index(a, 1, true) == 8);
	ASSERT(Iter_Index(a, 2) == 9);
	ASSERT(Iter_Index(a, 2, true) == 9);
	ASSERT(Iter_Index(a, 3) == 14);
	ASSERT(Iter_Index(a, 3, true) == 14);
	ASSERT(Iter_Index(a, 4) == 17);
	ASSERT(Iter_Index(a, 4, true) == 17);
	ASSERT(Iter_Index(a, 5) == 19);
	ASSERT(Iter_Index(a, 5, true) == 19);
	ASSERT(Iter_Index(a, 6) == cellmin);
	ASSERT(Iter_Index(a, 6, true) == 6);
	ASSERT(Iter_Index(a, 7) == cellmin);
	ASSERT(Iter_Index(a, 7, true) == 8);
	ASSERT(Iter_Index(a, 8) == cellmin);
	ASSERT(Iter_Index(a, 8, true) == 9);
	ASSERT(Iter_Index(a, 9) == cellmin);
	ASSERT(Iter_Index(a, 9, true) == 14);
	ASSERT(Iter_Index(a, 10) == cellmin);
	ASSERT(Iter_Index(a, 10, true) == 17);
	ASSERT(Iter_Index(a, 11) == cellmin);
	ASSERT(Iter_Index(a, 11, true) == 19);
	ASSERT(Iter_Index(a, 12) == cellmin);
	ASSERT(Iter_Index(a, 12, true) == 6);
	ASSERT(Iter_Index(a, 13) == cellmin);
	ASSERT(Iter_Index(a, 13, true) == 8);
	ASSERT(Iter_Index(a, 130) == cellmin);
	ASSERT(Iter_Index(a, 130, true) == 17);
}

Test:y_iter_Index2()
{
	new Iterator:a<5, 20>;
	Iter_Add(a<3>, 0);
	Iter_Add(a<3>, 1);
	Iter_Add(a<3>, 2);
	Iter_Add(a<3>, 14);
	Iter_Add(a<4>, 10);
	Iter_Add(a<4>, 11);
	Iter_Add(a<4>, 15);
	Iter_Add(a<4>, 18);
	ASSERT(Iter_Index(a<0>, -1) == cellmin);
	ASSERT(Iter_Index(a<0>, -1, true) == cellmin);
	ASSERT(Iter_Index(a<0>, 0) == cellmin);
	ASSERT(Iter_Index(a<0>, 10) == cellmin);
	ASSERT(Iter_Index(a<0>, 0, true) == cellmin);
	ASSERT(Iter_Index(a<0>, 10, true) == cellmin);
	ASSERT(Iter_Index(a<1>, 0) == cellmin);
	ASSERT(Iter_Index(a<1>, 10) == cellmin);
	ASSERT(Iter_Index(a<1>, 0, true) == cellmin);
	ASSERT(Iter_Index(a<1>, 10, true) == cellmin);
	ASSERT(Iter_Index(a<2>, 0) == cellmin);
	ASSERT(Iter_Index(a<2>, 10) == cellmin);
	ASSERT(Iter_Index(a<2>, 0, true) == cellmin);
	ASSERT(Iter_Index(a<2>, 10, true) == cellmin);
	ASSERT(Iter_Index(a<3>, 0) == 0);
	ASSERT(Iter_Index(a<3>, 1) == 1);
	ASSERT(Iter_Index(a<3>, 2) == 2);
	ASSERT(Iter_Index(a<3>, 3) == 14);
	ASSERT(Iter_Index(a<3>, 4) == cellmin);
	ASSERT(Iter_Index(a<3>, 4, true) == 0);
	ASSERT(Iter_Index(a<3>, 5) == cellmin);
	ASSERT(Iter_Index(a<3>, 5, true) == 1);
	ASSERT(Iter_Index(a<3>, 403) == cellmin);
	ASSERT(Iter_Index(a<3>, 403, true) == 14);
	ASSERT(Iter_Index(a<4>, -1) == cellmin);
	ASSERT(Iter_Index(a<4>, -1, true) == cellmin);
	ASSERT(Iter_Index(a<4>, 0) == 10);
	ASSERT(Iter_Index(a<4>, 0, true) == 10);
	ASSERT(Iter_Index(a<4>, 10) == cellmin);
	ASSERT(Iter_Index(a<4>, 10, true) == 15);
}

iterfunc              y_iterDecl1[cellmin](cur) { return cur == cellmin ? 5 : cellmin; }
stock iterfunc        y_iterDecl2(cur) { return cur == cellmin ? 5 : cellmin; }
#define iterstart@y_iterDecl2 (cellmin)
static stock iterfunc y_iterDecl3(cur) { return cur == -1 ? 5 : -1; }
static iterfunc stock y_iterDecl4(cur) { return cur == 0 ? 5 : 0; }
#define Iterator@y_iterDecl4 iterstart(0)
iterfunc static       y_iterDecl5[0](cur) { return cur == 0 ? 5 : 0; }
iterfunc stock static y_iterDecl6(&iterstate, cur) { return cur == -1 ? iterstate : -1; }
#define iterstart@y_iterDecl6 iterstate(-1, 5)

/* ========================================================================== */
/* | THERE IS MEANT TO BE A WARNING ON THIS LINE                            | */
/* |                                                                        | */
/* | */ iterfunc y_iterDecl1X[cellmin](cur)                              /* | */
/* | */ {                                                                /* | */
/* | */     return cur == cellmin ? 5 : cellmin;                         /* | */
/* | */ }                                                                /* | */
/* |                                                                        | */
/* | It tests the lack of "stock" with "iterfunc".                          | */
/* ========================================================================== */

/* ========================================================================== */
/* | THERE IS NOT MEANT TO BE A WARNING ON THIS LINE...                     | */
/* |          ===                                                           | */
/* | */ stock iterfunc y_iterDecl2X(cur)                                 /* | */
/* | */ {                                                                /* | */
/* | */     return cur == cellmin ? 5 : cellmin;                         /* | */
/* | */ }                                                                /* | */
/* |                                                                        | */
/* | It tests that "stock iterfunc" works.  TODO: Fix it.                   | */
/* ========================================================================== */
#define iterstart@y_iterDecl2X (cellmin)

/* ========================================================================== */
/* | THERE IS NOT MEANT TO BE A WARNING ON THIS LINE...                     | */
/* |          ===                                                           | */
/* | */ static stock iterfunc y_iterDecl3X(cur)                          /* | */
/* | */ {                                                                /* | */
/* | */     return cur == -1 ? 5 : -1;                                   /* | */
/* | */ }                                                                /* | */
/* |                                                                        | */
/* | It tests that "static stock iterfunc" works.  TODO: Fix it.            | */
/* ========================================================================== */

static iterfunc stock y_iterDecl4X(cur) { return cur == 0 ? 5 : 0; }
#define Iterator@y_iterDecl4X iterstart(0)

/* ========================================================================== */
/* | THERE IS MEANT TO BE A WARNING ON THIS LINE                            | */
/* |                                                                        | */
/* | */ static iterfunc y_iterDecl5X[0](cur)                             /* | */
/* | */ {                                                                /* | */
/* | */     return cur == 0 ? 5 : 0;                                     /* | */
/* | */ }                                                                /* | */
/* |                                                                        | */
/* | It tests the lack of "stock" with "static iterfunc".                   | */
/* ========================================================================== */

iterfunc stock static y_iterDecl6X(&iterstate, cur) { return cur == -1 ? iterstate : -1; }
#define iterstart@y_iterDecl6X iterstate(-1, 5)

Test:y_iter_MacroLess()
{
	new i;
	foreach (i : y_iterDecl1()) { ASSERT(i == 5); }
	ASSERT(i == cellmin);
	foreach (i : y_iterDecl5()) { ASSERT(i == 5); }
	ASSERT(i == 0);
	foreach (i : y_iterDecl3()) { ASSERT(i == 5); }
	ASSERT(i == -1);
	foreach (i : y_iterDecl2()) { ASSERT(i == 5); }
	ASSERT(i == cellmin);
	foreach (i : y_iterDecl4()) { ASSERT(i == 5); }
	ASSERT(i == 0);
	foreach (new j : y_iterDecl6()) { ASSERT(j == 5); }
	ASSERT(i == 0);
}

iterfunc stock y_iter_yield0()
{
}
#define Iterator@y_iter_yield0 iteryield

Test:y_iter_yield0a()
{
	new
		count;
	count = 0;
	foreach (new i : y_iter_yield0())
	{
		#pragma unused i
		++count;
	}
	ASSERT(count == 0);
	count = 0;
	foreach (new i : y_iter_yield0)
	{
		#pragma unused i
		++count;
	}
	ASSERT(count == 0);
	count = 0;
	foreach (new i : y_iter_yield0[])
	{
		#pragma unused i
		++count;
	}
	ASSERT(count == 0);
}

iterfunc stock y_iter_yield1()
{
	for (new i = 0; i != 10; ++i)
	{
		yield return i;
	}
}
#define Iterator@y_iter_yield1 iteryield

Test:y_iter_yield1a()
{
	new
		count;
	count = 0;
	foreach (new i : y_iter_yield1())
	{
		#pragma unused i
		++count;
	}
	ASSERT(count == 10);
	count = 0;
	foreach (new i : y_iter_yield1)
	{
		#pragma unused i
		++count;
	}
	ASSERT(count == 10);
	count = 0;
	foreach (new i : y_iter_yield1[])
	{
		#pragma unused i
		++count;
	}
	ASSERT(count == 10);
}

iterfunc stock y_iter_yield2(step, target = 100)
{
	new
		total = 0;
	while (total < target)
	{
		yield return total;
		total += step;
	}
}
#define Iterator@y_iter_yield2 iteryield

Test:y_iter_yield2a()
{
	new
		count;
	count = 0;
	foreach (new i : y_iter_yield2(10))
	{
		ASSERT(i % 10 == 0);
		++count;
	}
	ASSERT(count == 10);
	count = 0;
	foreach (new i : y_iter_yield2(10, 20))
	{
		ASSERT(i == 0 || i == 10);
		++count;
	}
	ASSERT(count == 2);
	count = 0;
	foreach (new i : y_iter_yield2[5])
	{
		ASSERT(i % 5 == 0);
		++count;
	}
	ASSERT(count == 20);
}

iterfunc stock y_iter_yield3(step, target = 100)
{
	new
		total = 0;
	for ( ; ; )
	{
		if (total >= target)
			yield break;
		yield return total;
		total += step;
	}
}
#define Iterator@y_iter_yield3 iteryield

Test:y_iter_yield3a()
{
	new
		count;
	count = 0;
	foreach (new i : y_iter_yield3(10))
	{
		ASSERT(i % 10 == 0);
		++count;
	}
	ASSERT(count == 10);
	count = 0;
	foreach (new i : y_iter_yield3(10, 20))
	{
		ASSERT(i == 0 || i == 10);
		++count;
	}
	ASSERT(count == 2);
	count = 0;
	foreach (new i : y_iter_yield3[5])
	{
		ASSERT(i % 5 == 0);
		++count;
	}
	ASSERT(count == 20);
}

iterfunc stock y_iter_yield4(arr[], size = sizeof (arr))
{
	for (new i = 0; i != size; ++i)
	{
		yield return arr[i];
	}
}
#define Iterator@y_iter_yield4 iteryield

Test:y_iter_yield4a()
{
	new
		count = 0,
		arr[] = { 2, 3, 6, 7, 110, 5432 };
	foreach (new i : y_iter_yield4(arr))
	{
		ASSERT(i == 2 || i == 3 || i == 6 || i == 7 || i == 110 || i == 5432);
		++count;
	}
}

#if defined YSI_SLOW_TESTS

	iterfunc stock y_iter_yield5()
	{
		new
			k = 0;
		for (new i = 0; i != 65536; ++i)
		{
			if (i % 655 == 0)
				printf("%d%%...", i / 655);
			for (new j = 0; j != 65536; ++j)
			{
				yield return k;
				++k;
			}
		}
	}
	#define Iterator@y_iter_yield5 iteryield
	
	Test:y_iter_yield5a()
	{
		new
			k = 0;
		for (new i = 0; i != 65536; ++i)
		{
			if (i % 655 == 0)
				printf("%d%%...", i / 655);
			for (new j = 0; j != 65536; ++j)
			{
				++k;
			}
		}
		ASSERT(k == 0); // Overflow.
		new
			count = 0,
			bool:ever = false;
		foreach (new i : y_iter_yield5)
		{
			#pragma unused i
			++count;
			ever = true;
		}
		ASSERT(count == 0); // Overflow.
		ASSERT(ever);
	}

#endif

iterfunc stock y_iter_yield6()
{
	for (new i = 0; i != 3; ++i)
	{
		yield return i;
	}
	yield return 10;
	yield return 20;
	for (new i = 501; i != 505; ++i)
	{
		yield return i;
	}
}
#define Iterator@y_iter_yield6 iteryield

Test:y_iter_yield6a()
{
	new
		answers[] = { 0, 1, 2, 10, 20, 501, 502, 503, 504 },
		idx = 0;
	foreach (new i : y_iter_yield6)
	{
		ASSERT(idx < sizeof (answers) && i == answers[idx]);
		++idx;
	}
	ASSERT(idx == sizeof(answers));
}

iterfunc stock y_iter_yield7c(n)
{
	while (n--)
	{
		yield return 10;
	}
}
#define Iterator@y_iter_yield7c iteryield

iterfunc stock y_iter_yield7b()
{
	foreach (new i : y_iter_yield7c(4))
	{
		yield return i;
	}
	yield return 20;
}
#define Iterator@y_iter_yield7b iteryield

iterfunc stock y_iter_yield7a(x)
{
	foreach (new i : y_iter_yield7b)
	{
		yield return i + 5;
		yield return i + 6;
		yield return i + 7;
		yield return i + 9;
		yield return i + 4;
		yield return i + 3;
	}
	yield return x;
}
#define Iterator@y_iter_yield7a iteryield

Test:y_iter_yield7a()
{
	new
		answers[] = {
			15, 16, 17, 19, 14, 13,
			15, 16, 17, 19, 14, 13,
			15, 16, 17, 19, 14, 13,
			15, 16, 17, 19, 14, 13,
			25, 26, 27, 29, 24, 23,
			2
		},
		idx = 0;
	foreach (new i : y_iter_yield7a[2])
	{
		ASSERT(idx < sizeof (answers) && i == answers[idx]);
		++idx;
	}
	ASSERT(idx == sizeof(answers));
}

