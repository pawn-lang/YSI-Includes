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
	HASH_MAP_DATA<32>,
	E_HASH_MAP_TEST_1,
	E_HASH_MAP_TEST_2
}

Test:y_hashmap_Init()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data);
	ASSERT(data[88][_E_HASH_MAP_NEXT] == -1);
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
	HashMap_Init(m, data);
	HashMap_Add(m, "Hello", 42);
	ASSERT(bool:data[42][_E_HASH_MAP_NAME][0]);
	ASSERT(!strcmp(data[42][_E_HASH_MAP_NAME], "Hello"));
	ASSERT(data[42][_E_HASH_MAP_NEXT] == -1);
}

Test:y_hashmap_Get1()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data);
	HashMap_Add(m, "Hello", 42);
	/*printf("%s %d %d %d %d"
		, data[42][_E_HASH_MAP_NAME]
		, data[42][_E_HASH_MAP_NEXT]
		, data[42][_E_HASH_MAP_HASH]
		, data[42][E_HASH_MAP_TEST_1]
		, data[42][E_HASH_MAP_TEST_2]);*/
	ASSERT(HashMap_Get(m, "Hello") == 42);
}

Test:y_hashmap_RemoveKey1()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data);
	HashMap_Add(m, "Hello", 42);
	ASSERT(HashMap_Get(m, "Hello") == 42);
	HashMap_RemoveKey(m, "Hello");
	ASSERT(HashMap_Get(m, "Hello") == -1);
}

Test:y_hashmap_Get100()
{
	new HashMap:m<>;
	new data[100][E_HASH_MAP_TEST];
	HashMap_Init(m, data);
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
	HashMap_Init(m, data);
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

Test:y_hashmap_Get1000()
{
	new HashMap:m<>;
	new data[1000][E_HASH_MAP_TEST];
	HashMap_Init(m, data);
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
	HashMap_Init(m, data);
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
	HashMap_Init(m, data);
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
