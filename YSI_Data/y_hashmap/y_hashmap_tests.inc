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

enum E_HASH_MAP_TEST
{
	//HASH_MAP_DATA<32>,
	E_HASH_MAP_TEST_NAME[32],
	E_HASH_MAP_TEST_DATA[HASH_MAP_DATA]
}

@test(.group = "y_hashmap") y_hashmap_Init()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	ASSERT_NZ(data[0][E_HASH_MAP_TEST_DATA][0]);
	ASSERT_ZE(data[0][E_HASH_MAP_TEST_DATA][1]);
	ASSERT_ZE(data[0][E_HASH_MAP_TEST_DATA][2]);
	ASSERT_NZ(data[88][E_HASH_MAP_TEST_DATA][0]);
	ASSERT_ZE(data[88][E_HASH_MAP_TEST_DATA][1]);
	ASSERT_ZE(data[88][E_HASH_MAP_TEST_DATA][2]);
	ASSERT_ZE(data[99][E_HASH_MAP_TEST_DATA][0]);
	ASSERT_ZE(data[99][E_HASH_MAP_TEST_DATA][1]);
	ASSERT_ZE(data[99][E_HASH_MAP_TEST_DATA][2]);
}

@test(.group = "y_hashmap") RawMemCpy()
{
	new src[100] = "Hello there", dst[100];
	RawMemCpy(AMX_Ref(dst[0]), AMX_Ref(src[0]), 100 * 4);
	ASSERT(bool:dst[0]);
	ASSERT_SAME(dst, "Hello there");
}

@test(.group = "y_hashmap") y_hashmap_Add()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	HashMap_Add(m, "Hello", 42);
	ASSERT(bool:data[42][E_HASH_MAP_TEST_NAME][0]);
	ASSERT_SAME(data[42][E_HASH_MAP_TEST_NAME], "Hello");
	ASSERT_EQ(data[42][E_HASH_MAP_TEST_DATA][0], BernsteinHash("Hello"));
	ASSERT_ZE(data[42][E_HASH_MAP_TEST_DATA][1]);
	ASSERT_ZE(data[42][E_HASH_MAP_TEST_DATA][2]);
}

@test(.group = "y_hashmap") y_hashmap_Get1()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	HashMap_Add(m, "Hello", 42);
	ASSERT_EQ(HashMap_Get(m, "Hello"), 42);
}

@test(.group = "y_hashmap") y_hashmap_GetUnused1()
{
	new HashMap:m<>;
	new data[6][E_HASH_MAP_TEST];
	new prev;
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	prev = data[0][E_HASH_MAP_TEST_DATA][0];
	ASSERT_NZ(prev);
	ASSERT_ZE(HashMap_GetUnused(m));
	ASSERT_EQ(m[260], prev);
	prev = data[1][E_HASH_MAP_TEST_DATA][0];
	ASSERT_NZ(prev);
	ASSERT_NE(prev, data[0][E_HASH_MAP_TEST_DATA][0]);
	ASSERT_EQ(HashMap_GetUnused(m), 1);
	ASSERT_EQ(m[260], prev);
	ASSERT_EQ(HashMap_GetUnused(m), 2);
	ASSERT_EQ(HashMap_GetUnused(m), 3);
	ASSERT_EQ(HashMap_GetUnused(m), 4);
	ASSERT_EQ(HashMap_GetUnused(m), 5);
	ASSERT_EQ(HashMap_GetUnused(m), -1);
	ASSERT_ZE(m[260]);
}

@test(.group = "y_hashmap") y_hashmap_GetUnused2()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	ASSERT_ZE(HashMap_GetUnused(m));
	ASSERT_EQ(HashMap_GetUnused(m), 1);
	ASSERT_EQ(HashMap_GetUnused(m), 2);
	HashMap_AddUnused(m, 2);
	HashMap_AddUnused(m, 0);
	ASSERT_ZE(HashMap_GetUnused(m));
	ASSERT_EQ(HashMap_GetUnused(m), 2);
	ASSERT_EQ(HashMap_GetUnused(m), 3);
	ASSERT_EQ(HashMap_GetUnused(m), 4);
}

@test(.group = "y_hashmap") y_hashmap_GetVarious()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	HashMap_Add(m, "01234567890", 10);
	HashMap_Add(m, "012345678901", 11);
	HashMap_Add(m, "0123456789012", 12);
	HashMap_Add(m, "01234567890123", 13);
	HashMap_Add(m, "012345678901234", 14);
	HashMap_Add(m, "0123456789012345", 15);
	HashMap_Add(m, "01234567890123456", 16);
	HashMap_Add(m, "012345678901234567", 17);
	HashMap_Add(m, "0123456789012345678", 18);
	HashMap_Add(m, "01234567890123456789", 19);
	HashMap_Add(m, "0", 0);
	HashMap_Add(m, "01", 1);
	HashMap_Add(m, "012", 2);
	HashMap_Add(m, "0123", 3);
	HashMap_Add(m, "01234", 4);
	HashMap_Add(m, "012345", 5);
	HashMap_Add(m, "0123456", 6);
	HashMap_Add(m, "01234567", 7);
	HashMap_Add(m, "012345678", 8);
	HashMap_Add(m, "0123456789", 9);
	HashMap_Add(m, "012345678901234567890", 20);
	HashMap_Add(m, "0123456789012345678901", 21);
	HashMap_Add(m, "01234567890123456789012", 22);
	HashMap_Add(m, "012345678901234567890123", 23);
	HashMap_Add(m, "0123456789012345678901234", 24);
	HashMap_Add(m, "01234567890123456789012345", 25);
	HashMap_Add(m, "012345678901234567890123456", 26);
	HashMap_Add(m, "0123456789012345678901234567", 27);
	HashMap_Add(m, "01234567890123456789012345678", 28);
	HashMap_Add(m, "012345678901234567890123456789", 29);
	ASSERT_EQ(HashMap_Get(m, "012345678901234567890"), 20);
	ASSERT_EQ(HashMap_Get(m, "0123456789012345678901"), 21);
	ASSERT_EQ(HashMap_Get(m, "01234567890123456789012"), 22);
	ASSERT_EQ(HashMap_Get(m, "012345678901234567890123"), 23);
	ASSERT_EQ(HashMap_Get(m, "0123456789012345678901234"), 24);
	ASSERT_EQ(HashMap_Get(m, "01234567890123456789012345"), 25);
	ASSERT_EQ(HashMap_Get(m, "012345678901234567890123456"), 26);
	ASSERT_EQ(HashMap_Get(m, "0123456789012345678901234567"), 27);
	ASSERT_EQ(HashMap_Get(m, "01234567890123456789012345678"), 28);
	ASSERT_EQ(HashMap_Get(m, "012345678901234567890123456789"), 29);
	ASSERT_EQ(HashMap_Get(m, "01234567890"), 10);
	ASSERT_EQ(HashMap_Get(m, "012345678901"), 11);
	ASSERT_EQ(HashMap_Get(m, "0123456789012"), 12);
	ASSERT_EQ(HashMap_Get(m, "01234567890123"), 13);
	ASSERT_EQ(HashMap_Get(m, "012345678901234"), 14);
	ASSERT_EQ(HashMap_Get(m, "0123456789012345"), 15);
	ASSERT_EQ(HashMap_Get(m, "01234567890123456"), 16);
	ASSERT_EQ(HashMap_Get(m, "012345678901234567"), 17);
	ASSERT_EQ(HashMap_Get(m, "0123456789012345678"), 18);
	ASSERT_EQ(HashMap_Get(m, "01234567890123456789"), 19);
	ASSERT_ZE(HashMap_Get(m, "0"));
	ASSERT_EQ(HashMap_Get(m, "01"), 1);
	ASSERT_EQ(HashMap_Get(m, "012"), 2);
	ASSERT_EQ(HashMap_Get(m, "0123"), 3);
	ASSERT_EQ(HashMap_Get(m, "01234"), 4);
	ASSERT_EQ(HashMap_Get(m, "012345"), 5);
	ASSERT_EQ(HashMap_Get(m, "0123456"), 6);
	ASSERT_EQ(HashMap_Get(m, "01234567"), 7);
	ASSERT_EQ(HashMap_Get(m, "012345678"), 8);
	ASSERT_EQ(HashMap_Get(m, "0123456789"), 9);
}

@test(.group = "y_hashmap") y_hashmap_RemoveKey1()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	HashMap_Add(m, "Hello", 42);
	ASSERT_EQ(HashMap_Get(m, "Hello"), 42);
	HashMap_RemoveKey(m, "Hello");
	ASSERT_EQ(HashMap_Get(m, "Hello"), -1);
}

@test(.group = "y_hashmap", .slow = true) y_hashmap_Get100()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	for (new i = 0, str[6]; i != 100; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		HashMap_Add(m, str, i);
	}
	for (new i = 0, str[6]; i != 100; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		ASSERT_EQ(HashMap_Get(m, str), i);
	}
}

@test(.group = "y_hashmap", .slow = true) y_hashmap_Get100Hash()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	for (new i = 0, str[6]; i != 100; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		HashMap_Add(m, str, i);
	}
	for (new i = 0, str[6]; i != 100; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		ASSERT_EQ(HashMap_Get(m, str), i);
	}
}

@test(.group = "y_hashmap", .slow = true) y_hashmap_Remove50()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	// Add.
	for (new i = 0, str[6]; i != 100; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		HashMap_Add(m, str, i);
	}
	// ASSERT.
	for (new i = 0, str[6]; i != 100; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		ASSERT_EQ(HashMap_Get(m, str), i);
	}
	// Remove half.
	for (new i = 1, str[6]; i != 101; i += 2)
	{
		format(str, sizeof (str), "hi%d", i);
		HashMap_RemoveKey(m, str);
	}
	// ASSERT.
	for (new i = 0, str[6]; i != 100; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		if (i & 1) ASSERT_EQ(HashMap_Get(m, str), -1);
		else ASSERT_EQ(HashMap_Get(m, str), i);
	}
}

@test(.group = "y_hashmap", .slow = true) y_hashmap_RemoveValues()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	// Add.
	for (new i = 0, str[6]; i != 100; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		HashMap_Add(m, str, i);
	}
	// ASSERT.
	for (new i = 0, str[6]; i != 100; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		ASSERT_EQ(HashMap_Get(m, str), i);
	}
	// Remove half.
	for (new i = 0; i != 100; ++i)
	{
		HashMap_RemoveValue(m, i);
	}
	// ASSERT.
	for (new i = 0, str[6]; i != 100; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		ASSERT_EQ(HashMap_Get(m, str), -1);
	}
}

@test(.group = "y_hashmap", .slow = true) y_hashmap_Get1000()
{
	if (heapspace() < 145000)
	{
		Debug_Info("y_hashmap tests require a large heap, increase it to at least 145000.");
	}
	ASSERT(heapspace() >= 145000);
	new HashMap:m<>;
	new data[1000][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	for (new i = 0, str[6]; i != 1000; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		HashMap_Add(m, str, i);
	}
	for (new i = 0, str[6]; i != 1000; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		ASSERT_EQ(HashMap_Get(m, str), i);
	}
}

@test(.group = "y_hashmap", .slow = true) y_hashmap_Remove500()
{
	if (heapspace() < 145000)
	{
		Debug_Info("y_hashmap tests require a large heap, increase it to at least 145000.");
	}
	ASSERT(heapspace() >= 145000);
	new HashMap:m<>;
	new data[1000][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	// Add.
	for (new i = 0, str[6]; i != 1000; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		HashMap_Add(m, str, i);
	}
	// ASSERT.
	for (new i = 0, str[6]; i != 1000; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		ASSERT_EQ(HashMap_Get(m, str), i);
	}
	// Remove half.
	for (new i = 1, str[6]; i != 1001; i += 2)
	{
		format(str, sizeof (str), "hi%d", i);
		HashMap_RemoveKey(m, str);
	}
	// ASSERT.
	for (new i = 0, str[6]; i != 1000; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		if (i & 1) ASSERT_EQ(HashMap_Get(m, str), -1);
		else ASSERT_EQ(HashMap_Get(m, str), i);
	}
}

@test(.group = "y_hashmap") y_hashmap_Set400Bug()
{
	// You have no idea how long it took me to whittle the code down to these
	// numbers!  There is a pattern - they're all in the same hashmap bin, but
	// while I spotted the pattern after quite a while I still wasn't sure
	// because there were some false positives in the data set throwing the
	// conclusions off.  I eventually managed to remove those though.
	new HashMap:m<>;
	new data[1000][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	HashMap_Add(m, "hi141", 141);
	HashMap_Add(m, "hi242", 242);
	HashMap_Add(m, "hi307", 307);
	HashMap_Add(m, "hi400", 400);
	// The numbers above are all in the same bin (176).
	ASSERT_EQ(HashMap_Get(m, "hi141"), 141);
	ASSERT_EQ(HashMap_Get(m, "hi400"), 400);
	HashMap_RemoveKey(m, "hi141");
	ASSERT_EQ(HashMap_Get(m, "hi141"), -1);
	ASSERT_EQ(HashMap_Get(m, "hi400"), 400);
}

@test(.group = "y_hashmap", .slow = true) y_hashmap_Set500()
{
	if (heapspace() < 145000)
	{
		Debug_Info("y_hashmap tests require a large heap, increase it to at least 145000.");
	}
	ASSERT(heapspace() >= 145000);
	new HashMap:m<>;
	new data[1000][E_HASH_MAP_TEST];
	new str[6];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	// Add.
	for (new i = 0; i != 500; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		HashMap_Add(m, str, i);
	}
	// ASSERT.
	for (new i = 0; i != 500; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		ASSERT_EQ(HashMap_Get(m, str), i);
	}
	for (new i = 1; i != 501; i += 2)
	{
		format(str, sizeof (str), "hi%d", i);
		HashMap_Set(m, str, i + 500);
	}
	// ASSERT.
	for (new i = 0; i != 500; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		if (i & 1) ASSERT_EQ(HashMap_Get(m, str), i + 500);
		else ASSERT_EQ(HashMap_Get(m, str), i);
	}
	for (new i = 500; i != 1000; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		ASSERT_EQ(HashMap_Get(m, str), -1);
	}
}

