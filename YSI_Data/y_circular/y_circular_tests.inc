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

GetHeaderValue(...)
{
	new idx = getarg(1);
	return getarg(0, idx);
}

Test:Circular_Init()
{
	new arr[5][5];
	Circular_Init(arr);
	ASSERT_EQ(GetHeaderValue(arr, 0), 20 + 5 * 4 * 0);
	ASSERT_EQ(GetHeaderValue(arr, 1), 16 + 5 * 4 * 1);
	ASSERT_EQ(GetHeaderValue(arr, 2), 12 + 5 * 4 * 2);
	ASSERT_EQ(GetHeaderValue(arr, 3),  8 + 5 * 4 * 3);
	ASSERT_EQ(GetHeaderValue(arr, 4), -20);
}

Test:Circular_Capacity()
{
	new arr[5][5];
	new data[5];
	ASSERT_EQ(Circular_Capacity(arr), 5);
	Circular_Init(arr);
	ASSERT_EQ(Circular_Capacity(arr), 5);
	Circular_Push(arr, data);
	ASSERT_EQ(Circular_Capacity(arr), 5);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	ASSERT_EQ(Circular_Capacity(arr), 5);
}

Test:Circular_Push1()
{
	new arr[5][5];
	new data[5];
	Circular_Init(arr);
	Circular_Push(arr, data);
	ASSERT_EQ(GetHeaderValue(arr, 0), 20 + 5 * 4 * 0);
	ASSERT_EQ(GetHeaderValue(arr, 1), 16 + 5 * 4 * 1);
	ASSERT_EQ(GetHeaderValue(arr, 2), 12 + 5 * 4 * 2);
	ASSERT_EQ(GetHeaderValue(arr, 3),  8 + 5 * 4 * 3);
	ASSERT_EQ(GetHeaderValue(arr, 4), -16);
}

Test:Circular_Push4()
{
	new arr[5][5];
	new data[5];
	Circular_Init(arr);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	ASSERT_EQ(GetHeaderValue(arr, 0), 20 + 5 * 4 * 0);
	ASSERT_EQ(GetHeaderValue(arr, 1), 16 + 5 * 4 * 1);
	ASSERT_EQ(GetHeaderValue(arr, 2), 12 + 5 * 4 * 2);
	ASSERT_EQ(GetHeaderValue(arr, 3),  8 + 5 * 4 * 3);
	ASSERT_EQ(GetHeaderValue(arr, 4), -4);
}

Test:Circular_Push5()
{
	new arr[5][5];
	new data[5];
	Circular_Init(arr);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	ASSERT_EQ(GetHeaderValue(arr, 0), 20 + 5 * 4 * 0);
	ASSERT_EQ(GetHeaderValue(arr, 1), 16 + 5 * 4 * 1);
	ASSERT_EQ(GetHeaderValue(arr, 2), 12 + 5 * 4 * 2);
	ASSERT_EQ(GetHeaderValue(arr, 3),  8 + 5 * 4 * 3);
	ASSERT_EQ(GetHeaderValue(arr, 4),  4 + 5 * 4 * 4);
}

Test:Circular_Push6()
{
	new arr[5][5];
	new data[5];
	Circular_Init(arr);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	ASSERT_EQ(GetHeaderValue(arr, 0), 20 + 5 * 4 * 0);
	ASSERT_EQ(GetHeaderValue(arr, 1), 16 + 5 * 4 * 1);
	ASSERT_EQ(GetHeaderValue(arr, 2), 12 + 5 * 4 * 2);
	ASSERT_EQ(GetHeaderValue(arr, 3),  8 + 5 * 4 * 3);
	ASSERT_EQ(GetHeaderValue(arr, 4),  4 + 5 * 4 * 4);
	Circular_Push(arr, data);
	ASSERT_EQ(GetHeaderValue(arr, 0), 20 + 5 * 4 * 1);
	ASSERT_EQ(GetHeaderValue(arr, 1), 16 + 5 * 4 * 2);
	ASSERT_EQ(GetHeaderValue(arr, 2), 12 + 5 * 4 * 3);
	ASSERT_EQ(GetHeaderValue(arr, 3),  8 + 5 * 4 * 4);
	ASSERT_EQ(GetHeaderValue(arr, 4),  4 + 5 * 4 * 0);
}

Test:Circular_Slot()
{
	new arr[5][5];
	new data[5];
	Circular_Init(arr);
	ASSERT_EQ(Circular_Push(arr, data), 0);
	ASSERT_EQ(Circular_Push(arr, data), 1);
	ASSERT_EQ(Circular_Push(arr, data), 2);
	ASSERT_EQ(Circular_Push(arr, data), 3);
	ASSERT_EQ(Circular_Push(arr, data), 4);
	ASSERT_EQ(Circular_Push(arr, data), 4);
	ASSERT_EQ(Circular_Push(arr, data), 4);
	ASSERT_EQ(Circular_Push(arr, data), 4);
	ASSERT_EQ(Circular_Push(arr, data), 4);
}

Test:Circular_Rotate()
{
	new arr[5][5];
	Circular_Init(arr);
	ASSERT_EQ(Circular_Rotate(arr), 0);
	ASSERT_EQ(Circular_Rotate(arr), 1);
	ASSERT_EQ(Circular_Rotate(arr), 2);
	ASSERT_EQ(Circular_Rotate(arr), 3);
	ASSERT_EQ(Circular_Rotate(arr), 4);
	ASSERT_EQ(Circular_Rotate(arr), 4);
	ASSERT_EQ(Circular_Rotate(arr), 4);
	ASSERT_EQ(Circular_Rotate(arr), 4);
	ASSERT_EQ(Circular_Rotate(arr), 4);
}

Test:Circular_RotateContent()
{
	new buffer[5][5];
	Circular_Init(buffer);
	ASSERT_EQ(Circular_Push(buffer, "h 0"), 0);
	ASSERT_EQ(Circular_Push(buffer, "h 1"), 1);
	ASSERT_EQ(Circular_Push(buffer, "h 2"), 2);
	ASSERT_EQ(Circular_Push(buffer, "h 3"), 3);
	ASSERT_EQ(Circular_Push(buffer, "h 4"), 4);
	ASSERT_SAME(buffer[0], "h 0");
	ASSERT_SAME(buffer[1], "h 1");
	ASSERT_SAME(buffer[2], "h 2");
	ASSERT_SAME(buffer[3], "h 3");
	ASSERT_SAME(buffer[4], "h 4");
	ASSERT_EQ(Circular_Rotate(buffer), 4);
	ASSERT_SAME(buffer[0], "h 1");
	ASSERT_SAME(buffer[1], "h 2");
	ASSERT_SAME(buffer[2], "h 3");
	ASSERT_SAME(buffer[3], "h 4");
	ASSERT_SAME(buffer[4], "h 0");
	ASSERT_EQ(Circular_Rotate(buffer), 4);
	ASSERT_SAME(buffer[0], "h 2");
	ASSERT_SAME(buffer[1], "h 3");
	ASSERT_SAME(buffer[2], "h 4");
	ASSERT_SAME(buffer[3], "h 0");
	ASSERT_SAME(buffer[4], "h 1");
	ASSERT_EQ(Circular_Rotate(buffer), 4);
	ASSERT_SAME(buffer[0], "h 3");
	ASSERT_SAME(buffer[1], "h 4");
	ASSERT_SAME(buffer[2], "h 0");
	ASSERT_SAME(buffer[3], "h 1");
	ASSERT_SAME(buffer[4], "h 2");
	ASSERT_EQ(Circular_Rotate(buffer), 4);
	ASSERT_SAME(buffer[0], "h 4");
	ASSERT_SAME(buffer[1], "h 0");
	ASSERT_SAME(buffer[2], "h 1");
	ASSERT_SAME(buffer[3], "h 2");
	ASSERT_SAME(buffer[4], "h 3");
	ASSERT_EQ(Circular_Rotate(buffer), 4);
	ASSERT_SAME(buffer[0], "h 0");
	ASSERT_SAME(buffer[1], "h 1");
	ASSERT_SAME(buffer[2], "h 2");
	ASSERT_SAME(buffer[3], "h 3");
	ASSERT_SAME(buffer[4], "h 4");
}

Test:Circular_IsFull1()
{
	new arr[5][5];
	Circular_Init(arr);
	ASSERT_ZE(Circular_Full(arr));
}

Test:Circular_IsFull2()
{
	new arr[5][5];
	new data[5];
	Circular_Init(arr);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	ASSERT_NZ(Circular_Full(arr));
}

Test:Circular_GetCount0()
{
	new arr[5][5];
	Circular_Init(arr);
	ASSERT_EQ(Circular_Count(arr), 0);
}

Test:Circular_GetCount1()
{
	new arr[5][5];
	new data[5];
	Circular_Init(arr);
	Circular_Push(arr, data);
	ASSERT_EQ(Circular_Count(arr), 1);
}

Test:Circular_GetCount4()
{
	new arr[5][5];
	new data[5];
	Circular_Init(arr);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	ASSERT_EQ(Circular_Count(arr), 4);
}

Test:Circular_GetCount5()
{
	new arr[5][5];
	new data[5];
	Circular_Init(arr);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	ASSERT_EQ(Circular_Count(arr), 5);
}

Test:Circular_GetCount6()
{
	new arr[5][5];
	new data[5];
	Circular_Init(arr);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	ASSERT_EQ(Circular_Count(arr), 5);
}

Test:Circular_PushFull()
{
	// This is really the only test that is needed.  Checks that the arrays do a full loop.
	new arr[5][5];
	new data[5];
	ASSERT_EQ(GetHeaderValue(arr, 0), 20 + 5 * 4 * 0);
	ASSERT_EQ(GetHeaderValue(arr, 1), 16 + 5 * 4 * 1);
	ASSERT_EQ(GetHeaderValue(arr, 2), 12 + 5 * 4 * 2);
	ASSERT_EQ(GetHeaderValue(arr, 3),  8 + 5 * 4 * 3);
	ASSERT_EQ(GetHeaderValue(arr, 4),  4 + 5 * 4 * 4);
	Circular_Init(arr);
	ASSERT_EQ(GetHeaderValue(arr, 4), -20);
	ASSERT_ZE(Circular_Full(arr));
	ASSERT_EQ(Circular_Count(arr), 0);
	Circular_Push(arr, data);
	ASSERT_EQ(GetHeaderValue(arr, 4), -16);
	ASSERT_ZE(Circular_Full(arr));
	ASSERT_EQ(Circular_Count(arr), 1);
	Circular_Push(arr, data);
	ASSERT_EQ(GetHeaderValue(arr, 4), -12);
	ASSERT_ZE(Circular_Full(arr));
	ASSERT_EQ(Circular_Count(arr), 2);
	Circular_Push(arr, data);
	ASSERT_EQ(GetHeaderValue(arr, 4), -8);
	ASSERT_ZE(Circular_Full(arr));
	ASSERT_EQ(Circular_Count(arr), 3);
	Circular_Push(arr, data);
	ASSERT_EQ(GetHeaderValue(arr, 4), -4);
	ASSERT_ZE(Circular_Full(arr));
	ASSERT_EQ(Circular_Count(arr), 4);
	Circular_Push(arr, data);
	ASSERT_EQ(GetHeaderValue(arr, 4),  4 + 5 * 4 * 4);
	Circular_Push(arr, data);
	ASSERT_EQ(Circular_Count(arr), 5);
	ASSERT_EQ(GetHeaderValue(arr, 0), 20 + 5 * 4 * 1);
	ASSERT_EQ(GetHeaderValue(arr, 1), 16 + 5 * 4 * 2);
	ASSERT_EQ(GetHeaderValue(arr, 2), 12 + 5 * 4 * 3);
	ASSERT_EQ(GetHeaderValue(arr, 3),  8 + 5 * 4 * 4);
	ASSERT_EQ(GetHeaderValue(arr, 4),  4 + 5 * 4 * 0);
	ASSERT_NZ(Circular_Full(arr));
	ASSERT_EQ(Circular_Count(arr), 5);
	Circular_Push(arr, data);
	ASSERT_EQ(GetHeaderValue(arr, 0), 20 + 5 * 4 * 2);
	ASSERT_EQ(GetHeaderValue(arr, 1), 16 + 5 * 4 * 3);
	ASSERT_EQ(GetHeaderValue(arr, 2), 12 + 5 * 4 * 4);
	ASSERT_EQ(GetHeaderValue(arr, 3),  8 + 5 * 4 * 0);
	ASSERT_EQ(GetHeaderValue(arr, 4),  4 + 5 * 4 * 1);
	ASSERT_NZ(Circular_Full(arr));
	ASSERT_EQ(Circular_Count(arr), 5);
	Circular_Push(arr, data);
	ASSERT_EQ(GetHeaderValue(arr, 0), 20 + 5 * 4 * 3);
	ASSERT_EQ(GetHeaderValue(arr, 1), 16 + 5 * 4 * 4);
	ASSERT_EQ(GetHeaderValue(arr, 2), 12 + 5 * 4 * 0);
	ASSERT_EQ(GetHeaderValue(arr, 3),  8 + 5 * 4 * 1);
	ASSERT_EQ(GetHeaderValue(arr, 4),  4 + 5 * 4 * 2);
	ASSERT_NZ(Circular_Full(arr));
	ASSERT_EQ(Circular_Count(arr), 5);
	Circular_Push(arr, data);
	ASSERT_EQ(GetHeaderValue(arr, 0), 20 + 5 * 4 * 4);
	ASSERT_EQ(GetHeaderValue(arr, 1), 16 + 5 * 4 * 0);
	ASSERT_EQ(GetHeaderValue(arr, 2), 12 + 5 * 4 * 1);
	ASSERT_EQ(GetHeaderValue(arr, 3),  8 + 5 * 4 * 2);
	ASSERT_EQ(GetHeaderValue(arr, 4),  4 + 5 * 4 * 3);
	ASSERT_NZ(Circular_Full(arr));
	ASSERT_EQ(Circular_Count(arr), 5);
	Circular_Push(arr, data);
	ASSERT_EQ(GetHeaderValue(arr, 0), 20 + 5 * 4 * 0);
	ASSERT_EQ(GetHeaderValue(arr, 1), 16 + 5 * 4 * 1);
	ASSERT_EQ(GetHeaderValue(arr, 2), 12 + 5 * 4 * 2);
	ASSERT_EQ(GetHeaderValue(arr, 3),  8 + 5 * 4 * 3);
	ASSERT_EQ(GetHeaderValue(arr, 4),  4 + 5 * 4 * 4);
	ASSERT_NZ(Circular_Full(arr));
	ASSERT_EQ(Circular_Count(arr), 5);
}

Test:Circular_PushContent()
{
	new strings[6][32];
	Circular_Init(strings);
	Circular_Push(strings, "String 1");
	ASSERT_SAME(strings[0], "String 1");
	Circular_Push(strings, "String 2");
	ASSERT_SAME(strings[0], "String 1");
	ASSERT_SAME(strings[1], "String 2");
	Circular_Push(strings, "String 3");
	ASSERT_SAME(strings[0], "String 1");
	ASSERT_SAME(strings[1], "String 2");
	ASSERT_SAME(strings[2], "String 3");
	Circular_Push(strings, "String 4");
	ASSERT_SAME(strings[0], "String 1");
	ASSERT_SAME(strings[1], "String 2");
	ASSERT_SAME(strings[2], "String 3");
	ASSERT_SAME(strings[3], "String 4");
	Circular_Push(strings, "String 5");
	ASSERT_SAME(strings[0], "String 1");
	ASSERT_SAME(strings[1], "String 2");
	ASSERT_SAME(strings[2], "String 3");
	ASSERT_SAME(strings[3], "String 4");
	ASSERT_SAME(strings[4], "String 5");
	Circular_Push(strings, "String 6");
	ASSERT_SAME(strings[0], "String 1");
	ASSERT_SAME(strings[1], "String 2");
	ASSERT_SAME(strings[2], "String 3");
	ASSERT_SAME(strings[3], "String 4");
	ASSERT_SAME(strings[4], "String 5");
	ASSERT_SAME(strings[5], "String 6");
	Circular_Push(strings, "String 7");
	ASSERT_SAME(strings[0], "String 2");
	ASSERT_SAME(strings[1], "String 3");
	ASSERT_SAME(strings[2], "String 4");
	ASSERT_SAME(strings[3], "String 5");
	ASSERT_SAME(strings[4], "String 6");
	ASSERT_SAME(strings[5], "String 7");
	Circular_Push(strings, "String 8");
	ASSERT_SAME(strings[0], "String 3");
	ASSERT_SAME(strings[1], "String 4");
	ASSERT_SAME(strings[2], "String 5");
	ASSERT_SAME(strings[3], "String 6");
	ASSERT_SAME(strings[4], "String 7");
	ASSERT_SAME(strings[5], "String 8");
}

Test:Circular_Contents()
{
	new arr[5][5];
	new data[5] = { 5, 6, 7, 8, 9 };
	Circular_Init(arr);
	ASSERT_EQ(Circular_Push(arr, data), 0);
	ASSERT_EQ(arr[0][0], 5);
	ASSERT_EQ(arr[0][1], 6);
	ASSERT_EQ(arr[0][2], 7);
	ASSERT_EQ(arr[0][3], 8);
	ASSERT_EQ(arr[0][4], 9);
	ASSERT_EQ(Circular_Push(arr, data), 1);
	ASSERT_EQ(Circular_Push(arr, data), 2);
	ASSERT_EQ(Circular_Push(arr, data), 3);
	ASSERT_EQ(Circular_Push(arr, data), 4);
	ASSERT_EQ(Circular_Push(arr, data), 4);
	ASSERT_EQ(Circular_Push(arr, data), 4);
}

