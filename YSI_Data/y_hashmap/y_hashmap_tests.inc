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

enum E_HASH_MAP_TEST
{
	//HASH_MAP_DATA<32>,
	E_HASH_MAP_TEST_NAME[32],
	E_HASH_MAP_TEST_DATA[HASH_MAP_DATA]
}

TEST__ y_hashmap_Init()
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

TEST__ rawMemcpy()
{
	new src[100] = "Hello there", dst[100];
	rawMemcpy(ref(dst), ref(src), 100 * 4);
	ASSERT(bool:dst[0]);
	ASSERT_SAME(dst, "Hello there");
}

TEST__ y_hashmap_Add()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	HashMap_Add(m, "Hello", 42);
	ASSERT(bool:data[42][E_HASH_MAP_TEST_NAME][0]);
	ASSERT_SAME(data[42][E_HASH_MAP_TEST_NAME], "Hello");
	ASSERT_EQ(data[42][E_HASH_MAP_TEST_DATA][0], bernstein("Hello"));
	ASSERT_ZE(data[42][E_HASH_MAP_TEST_DATA][1]);
	ASSERT_ZE(data[42][E_HASH_MAP_TEST_DATA][2]);
}

TEST__ y_hashmap_Get1()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	HashMap_Add(m, "Hello", 42);
	ASSERT_EQ(HashMap_Get(m, "Hello"), 42);
}

TEST__ y_hashmap_GetUnused1()
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

TEST__ y_hashmap_GetUnused2()
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

TEST__ y_hashmap_GetVarious()
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

TEST__ y_hashmap_RemoveKey1()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	HashMap_Add(m, "Hello", 42);
	ASSERT_EQ(HashMap_Get(m, "Hello"), 42);
	HashMap_RemoveKey(m, "Hello");
	ASSERT_EQ(HashMap_Get(m, "Hello"), -1);
}

TEST__ y_hashmap_Get100()
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

TEST__ y_hashmap_Get100Hash()
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

TEST__ y_hashmap_Remove50()
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

TEST__ y_hashmap_RemoveValues()
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

TEST__ y_hashmap_Get1000()
{
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

TEST__ y_hashmap_Remove500()
{
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

TEST__ y_hashmap_Set500()
{
	ASSERT(heapspace() >= 145000);
	new HashMap:m<>;
	new data[1000][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	// Add.
	for (new i = 0, str[6]; i != 500; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		HashMap_Add(m, str, i);
	}
	// ASSERT.
	for (new i = 0, str[6]; i != 500; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		ASSERT_EQ(HashMap_Get(m, str), i);
	}
	// Remove half.
	for (new i = 1, str[6]; i != 501; i += 2)
	{
		format(str, sizeof (str), "hi%d", i);
		HashMap_Set(m, str, i + 500);
	}
	// ASSERT.
	for (new i = 0, str[6]; i != 500; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		if (i & 1) ASSERT_EQ(HashMap_Get(m, str), i + 500);
		else ASSERT_EQ(HashMap_Get(m, str), i);
	}
	for (new i = 500, str[6]; i != 1000; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		ASSERT_EQ(HashMap_Get(m, str), -1);
	}
}

