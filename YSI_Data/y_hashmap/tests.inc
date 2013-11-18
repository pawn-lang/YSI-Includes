/**--------------------------------------------------------------------------**\
					  ====================================
					   y_hashmap - Link strings to values
					  ====================================
Description:
	Maps string indexes to integer indexes.  Uses a fast hash to get an array
	slot, then a linked list to resolve collisions.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI hashmap include.
	
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
	2.0
Changelog:
	23/06/13:
		First version.
Functions:
	stock:
		HashMap_Init - Associate a hash map with an array.
		HashMap_Add - Add a value under a given string.
		HashMap_Get - Get a value from a string.
		HashMap_RemoveKey - Remove a string and its value from a hash map.
		HashMap_Set - Change the value associated with a key.
Definitions:
	HASH_MAP_DATA - What should be added to enums to be hash map referenced.
	HashMap - Declare a new hash map.
\**--------------------------------------------------------------------------**/

enum E_HASH_MAP_TEST
{
	//HASH_MAP_DATA<32>,
	E_HASH_MAP_TEST_NAME[32],
	E_HASH_MAP_TEST_DATA[HASH_MAP_DATA]
}

Test:y_hashmap_Init()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	ASSERT(data[88][E_HASH_MAP_TEST_DATA] == -1);
}

Test:rawMemcpy()
{
	new src[100] = "Hello there", dst[100];
	rawMemcpy(ref(dst), ref(src), 100 * 4);
	ASSERT(bool:dst[0]);
	ASSERT(!strcmp(dst, "Hello there"));
}

Test:y_hashmap_Add()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	HashMap_Add(m, "Hello", 42);
	ASSERT(bool:data[42][E_HASH_MAP_TEST_NAME][0]);
	ASSERT(!strcmp(data[42][E_HASH_MAP_TEST_NAME], "Hello"));
	ASSERT(data[42][E_HASH_MAP_TEST_DATA] == -1);
}

Test:y_hashmap_Get1()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	HashMap_Add(m, "Hello", 42);
	/*printf("%s %d %d %d %d"
		, data[42][_E_HASH_MAP_NAME]
		, data[42][_E_HASH_MAP_NEXT]
		, data[42][_E_HASH_MAP_HASH]
		, data[42][E_HASH_MAP_TEST_1]
		, data[42][E_HASH_MAP_TEST_2]);*/
	ASSERT(HashMap_Get(m, "Hello") == 42);
}

Test:y_hashmap_GetVarious()
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
	ASSERT(HashMap_Get(m, "012345678901234567890") == 20);
	ASSERT(HashMap_Get(m, "0123456789012345678901") == 21);
	ASSERT(HashMap_Get(m, "01234567890123456789012") == 22);
	ASSERT(HashMap_Get(m, "012345678901234567890123") == 23);
	ASSERT(HashMap_Get(m, "0123456789012345678901234") == 24);
	ASSERT(HashMap_Get(m, "01234567890123456789012345") == 25);
	ASSERT(HashMap_Get(m, "012345678901234567890123456") == 26);
	ASSERT(HashMap_Get(m, "0123456789012345678901234567") == 27);
	ASSERT(HashMap_Get(m, "01234567890123456789012345678") == 28);
	ASSERT(HashMap_Get(m, "012345678901234567890123456789") == 29);
	ASSERT(HashMap_Get(m, "01234567890") == 10);
	ASSERT(HashMap_Get(m, "012345678901") == 11);
	ASSERT(HashMap_Get(m, "0123456789012") == 12);
	ASSERT(HashMap_Get(m, "01234567890123") == 13);
	ASSERT(HashMap_Get(m, "012345678901234") == 14);
	ASSERT(HashMap_Get(m, "0123456789012345") == 15);
	ASSERT(HashMap_Get(m, "01234567890123456") == 16);
	ASSERT(HashMap_Get(m, "012345678901234567") == 17);
	ASSERT(HashMap_Get(m, "0123456789012345678") == 18);
	ASSERT(HashMap_Get(m, "01234567890123456789") == 19);
	ASSERT(HashMap_Get(m, "0") == 0);
	ASSERT(HashMap_Get(m, "01") == 1);
	ASSERT(HashMap_Get(m, "012") == 2);
	ASSERT(HashMap_Get(m, "0123") == 3);
	ASSERT(HashMap_Get(m, "01234") == 4);
	ASSERT(HashMap_Get(m, "012345") == 5);
	ASSERT(HashMap_Get(m, "0123456") == 6);
	ASSERT(HashMap_Get(m, "01234567") == 7);
	ASSERT(HashMap_Get(m, "012345678") == 8);
	ASSERT(HashMap_Get(m, "0123456789") == 9);
}

Test:y_hashmap_RemoveKey1()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data, E_HASH_MAP_TEST_DATA);
	HashMap_Add(m, "Hello", 42);
	ASSERT(HashMap_Get(m, "Hello") == 42);
	HashMap_RemoveKey(m, "Hello");
	ASSERT(HashMap_Get(m, "Hello") == -1);
}

Test:y_hashmap_Get100()
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
		ASSERT(HashMap_Get(m, str) == i);
	}
}

Test:y_hashmap_Get100Hash()
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
		ASSERT(HashMap_Get(m, str) == i);
	}
}

Test:y_hashmap_Remove50()
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
		ASSERT(HashMap_Get(m, str) == i);
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
		if (i & 1) ASSERT(HashMap_Get(m, str) == -1);
		else ASSERT(HashMap_Get(m, str) == i);
	}
}

Test:y_hashmap_RemoveValues()
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
		ASSERT(HashMap_Get(m, str) == i);
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
		ASSERT(HashMap_Get(m, str) == -1);
	}
}

Test:y_hashmap_Get1000()
{
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
		ASSERT(HashMap_Get(m, str) == i);
	}
}

Test:y_hashmap_Remove500()
{
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
		ASSERT(HashMap_Get(m, str) == i);
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
		if (i & 1) ASSERT(HashMap_Get(m, str) == -1);
		else ASSERT(HashMap_Get(m, str) == i);
	}
}

Test:y_hashmap_Set500()
{
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
		ASSERT(HashMap_Get(m, str) == i);
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
		if (i & 1) ASSERT(HashMap_Get(m, str) == i + 500);
		else ASSERT(HashMap_Get(m, str) == i);
	}
	for (new i = 500, str[6]; i != 1000; ++i)
	{
		format(str, sizeof (str), "hi%d", i);
		ASSERT(HashMap_Get(m, str) == -1);
	}
}
