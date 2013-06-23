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
