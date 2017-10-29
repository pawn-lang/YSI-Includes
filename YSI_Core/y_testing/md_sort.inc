static bool:MD_InASCOrder(const array[][], const slot, const size = sizeof (array))
{
	new
		prev = cellmin;
	for (new i = 0; i != size; ++i)
	{
		if (array[i][slot] < prev)
			return false;
		prev = array[i][slot];
	}
	return true;
}

static bool:MD_InDESCOrder(const array[][], const slot, const size = sizeof (array))
{
	new
		prev = cellmax;
	for (new i = 0; i != size; ++i)
	{
		if (array[i][slot] > prev)
			return false;
		prev = array[i][slot];
	}
	return true;
}

static bool:MD_InASCOrderFloat(const Float:array[][], const slot, const size = sizeof (array))
{
	new
		Float:prev = FLOAT_NEGATIVE_INFINITY;
	for (new i = 0; i != size; ++i)
	{
		new
			Float:next = array[i][slot];
		if (next == next)
		{
			// Number after NAN.
			if (prev != prev)
				return false;
			if (next < prev)
				return false;
		}
		prev = next;
	}
	return true;
}

static bool:MD_InDESCOrderFloat(const Float:array[][], const slot, const size = sizeof (array))
{
	new
		Float:prev = FLOAT_INFINITY;
	for (new i = 0; i != size; ++i)
	{
		new
			Float:next = array[i][slot];
		if (next == next)
		{
			// Number after NAN.
			if (prev != prev)
				return false;
			if (next > prev)
				return false;
		}
		prev = next;
	}
	return true;
}

Test:MD_SortNumASC()
{
	new
		array[100][3];
	for (new i = 0; i != sizeof (array); ++i)
	{
		array[i][0] = Random(-7654);
		ASSERT(-7654 < array[i][0] <= 0);
		array[i][1] = Random(50);
		ASSERT(0 <= array[i][1] < 50);
		array[i][2] = Random(-3214, -8912);
		ASSERT(-8912 <= array[i][2] < -3214);
	}
	SortDeepArray(array, 0, .order = SORT_ASC);
	ASSERT(MD_InASCOrder(array, 0));
	SortDeepArray(array, 2, .order = SORT_ASC);
	ASSERT(MD_InASCOrder(array, 2));
}

Test:MD_SortNumDESC()
{
	new
		array[100][5];
	for (new i = 0; i != sizeof (array); ++i)
	{
		for (new j = 0; j != sizeof (array[]); ++j)
		{
			array[i][j] = Random(100, 1000);
			ASSERT(100 <= array[i][j] < 1000);
		}
	}
	SortDeepArray(array, 0, .order = SORT_DESC);
	ASSERT(MD_InDESCOrder(array, 0));
	SortDeepArray(array, 2, .order = SORT_DESC);
	ASSERT(MD_InDESCOrder(array, 2));
}

Test:MD_SortNumASCFloat()
{
	new
		Float:array[100][4];
	for (new i = 0; i != sizeof (array); ++i)
	{
		array[i][0] = RandomFloat(-88.99);
		ASSERT(-88.99 < array[i][0] <= 0.0);
		array[i][1] = RandomFloat(765.0);
		ASSERT(0.0 <= array[i][1] < 765.0);
		array[i][2] = RandomFloat(-5000.0, 2000.0);
		ASSERT(-5000.0 <= array[i][2] < 2000.0);
		ASSERT(array[i][0] == array[i][0]);
		ASSERT(array[i][1] == array[i][1]);
		ASSERT(array[i][2] == array[i][2]);
		if (i > 10)
			array[i][3] = FLOAT_NAN;
		else
			array[i][3] = RandomFloat(10.0);
	}
	SortDeepArray(array, 0, .order = SORT_ASC);
	ASSERT(MD_InASCOrderFloat(array, 0));
	SortDeepArray(array, 2, .order = SORT_ASC);
	ASSERT(MD_InASCOrderFloat(array, 2));
	SortDeepArray(array, 3, .order = SORT_ASC);
	ASSERT(MD_InASCOrderFloat(array, 3));
}

Test:MD_SortNumDESCFloat()
{
	new
		Float:array[100][6];
	for (new i = 0; i != sizeof (array); ++i)
	{
		for (new j = 0; j != sizeof (array[]); ++j)
		{
			array[i][j] = RandomFloat(2000.0, -9000.0, random(4));
			ASSERT(-9000.0 <= array[i][j] < 2000.0);
		}
		ASSERT(array[i][0] == array[i][0]);
		ASSERT(array[i][1] == array[i][1]);
		ASSERT(array[i][2] == array[i][2]);
		ASSERT(array[i][3] == array[i][3]);
		ASSERT(array[i][4] == array[i][4]);
		if (i > 50)
			array[i][5] = FLOAT_NAN;
		else
			array[i][5] = RandomFloat(20.0);
	}
	SortDeepArray(array, 0, .order = SORT_DESC);
	ASSERT(MD_InDESCOrderFloat(array, 0));
	SortDeepArray(array, 2, .order = SORT_DESC);
	ASSERT(MD_InDESCOrderFloat(array, 2));
	SortDeepArray(array, 5, .order = SORT_DESC);
	ASSERT(MD_InDESCOrderFloat(array, 5));
}

enum MD_TEST_ENUM_TWO_DIRECTIONS
{
	E_SORT_ORDER:MD_TEST_ORDER_FIELD,
	MD_TEST_VALUE_FIELD
}

Comparator:MD_TEST_Comparator(left[MD_TEST_ENUM_TWO_DIRECTIONS], right[MD_TEST_ENUM_TWO_DIRECTIONS])
{
	// Put ascending slots first, then descending ones.
	if (left[MD_TEST_ORDER_FIELD] == SORT_ASC)
	{
		if (right[MD_TEST_ORDER_FIELD] == SORT_ASC)
			return left[MD_TEST_VALUE_FIELD] - right[MD_TEST_VALUE_FIELD];
		else
			return -1;
	}
	else
	{
		if (right[MD_TEST_ORDER_FIELD] == SORT_ASC)
			return 1;
		else
			return right[MD_TEST_VALUE_FIELD] - left[MD_TEST_VALUE_FIELD];
	}
}

Test:MD_Sort_ShuffleAndReset()
{
	new array[100][MD_TEST_ENUM_TWO_DIRECTIONS];
	new copied[100][MD_TEST_ENUM_TWO_DIRECTIONS];
	for (new i = 0; i != sizeof (array); ++i)
	{
		copied[i][MD_TEST_ORDER_FIELD] = array[i][MD_TEST_ORDER_FIELD] = random(2) ? SORT_ASC : SORT_DESC;
		copied[i][MD_TEST_VALUE_FIELD] = array[i][MD_TEST_VALUE_FIELD] = random(200);
	}
	SortArrayUsingComparator(array, MD_TEST_Comparator);
	ResetDeepArray(array);
	for (new i = 0; i != sizeof (array); ++i)
	{
		ASSERT(array[i][MD_TEST_VALUE_FIELD] == copied[i][MD_TEST_VALUE_FIELD]);
		ASSERT(array[i][MD_TEST_ORDER_FIELD] == copied[i][MD_TEST_ORDER_FIELD]);
	}
	ShuffleDeepArray(array);
	ResetDeepArray(array);
	for (new i = 0; i != sizeof (array); ++i)
	{
		ASSERT(array[i][MD_TEST_VALUE_FIELD] == copied[i][MD_TEST_VALUE_FIELD]);
		ASSERT(array[i][MD_TEST_ORDER_FIELD] == copied[i][MD_TEST_ORDER_FIELD]);
	}
	ShuffleDeepArray(array);
	ResetDeepArray(array);
	for (new i = 0; i != sizeof (array); ++i)
	{
		ASSERT(array[i][MD_TEST_VALUE_FIELD] == copied[i][MD_TEST_VALUE_FIELD]);
		ASSERT(array[i][MD_TEST_ORDER_FIELD] == copied[i][MD_TEST_ORDER_FIELD]);
	}
}

