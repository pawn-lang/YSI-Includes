TEST__ _Sorted_Contains()
{
	new
		arr[32] = { 1, 3, 5, 7, 9, 10, 11, 12, 13, 0 },
		size = 9;
	ASSERT(!_Sorted_Contains(arr, size, -1));
	ASSERT(!_Sorted_Contains(arr, size, 0));
	ASSERT(_Sorted_Contains(arr, size, 1));
	ASSERT(!_Sorted_Contains(arr, size, 2));
	ASSERT(_Sorted_Contains(arr, size, 3));
	ASSERT(!_Sorted_Contains(arr, size, 4));
	ASSERT(_Sorted_Contains(arr, size, 5));
	ASSERT(!_Sorted_Contains(arr, size, 6));
	ASSERT(_Sorted_Contains(arr, size, 7));
	ASSERT(!_Sorted_Contains(arr, size, 8));
	ASSERT(_Sorted_Contains(arr, size, 9));
	ASSERT(_Sorted_Contains(arr, size, 10));
	ASSERT(_Sorted_Contains(arr, size, 11));
	ASSERT(_Sorted_Contains(arr, size, 12));
	ASSERT(_Sorted_Contains(arr, size, 13));
	ASSERT(!_Sorted_Contains(arr, size, 14));
	ASSERT(!_Sorted_Contains(arr, size, 14000));
}

TEST__ _Sorted_FindInsert()
{
	new
		arr[32] = { 1, 3, 5, 7, 9, 10, 11, 12, 13, 0 },
		size = 9;
	ASSERT_ZE(_Sorted_FindInsert(arr, size, -1));
	ASSERT_ZE(_Sorted_FindInsert(arr, size, 0));
	ASSERT_ZE(_Sorted_FindInsert(arr, size, 1));
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 2), 1);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 3), 1);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 4), 2);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 5), 2);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 6), 3);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 7), 3);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 8), 4);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 9), 4);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 10), 5);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 11), 6);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 12), 7);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 13), 8);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 14), 9);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 14000), 9);
}

TEST__ _Sorted_FindInsert2()
{
	new
		arr[32] = { 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5 },
		size = 20;
	ASSERT_ZE(_Sorted_FindInsert(arr, size, -1));
	ASSERT_ZE(_Sorted_FindInsert(arr, size, 0));
	ASSERT(_Sorted_FindInsert(arr, size, 1) >= 0 && _Sorted_FindInsert(arr, size, 1) < 5);
	ASSERT(_Sorted_FindInsert(arr, size, 2) >= 5 && _Sorted_FindInsert(arr, size, 2) < 10);
	ASSERT(_Sorted_FindInsert(arr, size, 3) >= 10 && _Sorted_FindInsert(arr, size, 3) < 15);
	ASSERT(_Sorted_FindInsert(arr, size, 5) >= 15 && _Sorted_FindInsert(arr, size, 5) < 20);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 4), 15);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 6), 20);
	ASSERT_EQ(_Sorted_FindInsert(arr, size, 6000), 20);
}

TEST__ _Sorted_Add()
{
	new
		arr[32] = { 10, 20, 30, 40, 0 },
		size = 4;
	_Sorted_Add(arr, size, 15);
	ASSERT_EQ(size, 5);
	ASSERT(!memcmp(arr, { 10, 15, 20, 30, 40, 0 }, 6));
	_Sorted_Add(arr, size, 0);
	ASSERT_EQ(size, 6);
	ASSERT(!memcmp(arr, { 0, 10, 15, 20, 30, 40, 0 }, 7));
	_Sorted_Add(arr, size, 15);
	ASSERT_EQ(size, 7);
	ASSERT(!memcmp(arr, { 0, 10, 15, 15, 20, 30, 40, 0 }, 8));
	_Sorted_Add(arr, size, 100);
	ASSERT_EQ(size, 8);
	ASSERT(!memcmp(arr, { 0, 10, 15, 15, 20, 30, 40, 100, 0 }, 9));
	_Sorted_Add(arr, size, 1);
	ASSERT_EQ(size, 9);
	ASSERT(!memcmp(arr, { 0, 1, 10, 15, 15, 20, 30, 40, 100, 0 }, 10));
	_Sorted_Add(arr, size, 41);
	ASSERT_EQ(size, 10);
	ASSERT(!memcmp(arr, { 0, 1, 10, 15, 15, 20, 30, 40, 41, 100, 0 }, 11));
	_Sorted_Add(arr, size, 51);
	ASSERT_EQ(size, 11);
	ASSERT(!memcmp(arr, { 0, 1, 10, 15, 15, 20, 30, 40, 41, 51, 100, 0 }, 12));
}

