#define FUNC_CHECK_ARR(%0,%1) for (new __i, __j = min(sizeof (%0), sizeof (%1)); __i != __j; ++__i) ASSERT(%0[__i] == %1[__i])

Test:FUNC_Map1()
{
	new
		a0[10] = {0, 1, 2, ...},
		a1[10] = {0, 2, 4, ...};
	inline const Double(x)
	{
		@return x * 2;
	}
	Map(using inline Double, a0, a0);
	FUNC_CHECK_ARR(a0, a1);
}

Test:FUNC_Map2()
{
	new
		a0[10] = {0, 1, 2, ...},
		a1[10] = {0, 2, 4, ...},
		a2[10] = {0, 1, 2, ...},
		a3[10];
	inline const Double(x)
	{
		@return x * 2;
	}
	Map(using inline Double, a0, a3);
	FUNC_CHECK_ARR(a0, a2);
	FUNC_CHECK_ARR(a3, a1);
}

Test:FUNC_Map3()
{
	new
		a0[10] = {0, 1, 2, ...},
		a1[10] = {1, 4, 7, ...},
		a2[10] = {0, 1, 2, ...},
		a3[10];
	Map({_0 * 3 + 1}, a0, a3);
	FUNC_CHECK_ARR(a0, a2);
	FUNC_CHECK_ARR(a3, a1);
}

Test:FUNC_Map_1()
{
	new
		a0[10] = {0, 1, 2, ...},
		a1[10] = {0, 1, 2, ...};
	inline const Triple(x)
	{
		@return x * 3;
	}
	Map_(using inline Triple, a0);
	FUNC_CHECK_ARR(a0, a1);
}

Test:FUNC_Map_2()
{
	new
		a0[10] = {0, 1, 2, ...},
		a1[10] = {0, 1, 2, ...};
	Map_({_0 * 4}, a0);
	FUNC_CHECK_ARR(a0, a1);
}

Test:FUNC_MapIdx()
{
	new
		a0[10] = {1, ...},
		a1[10] = {2, 4, 6, ...};
	inline const AddAndMul(idx, x)
	{
		@return (x + idx) * 2;
	}
	MapIdx(using inline AddAndMul, a0, a0);
	FUNC_CHECK_ARR(a0, a1);
}

Test:FUNC_MapIdx_()
{
	new
		a0[10] = {0, 1, 2, ...},
		a1[10] = {0, 1, 2, ...};
	inline const Thing(idx, x)
	{
		#pragma unused idx, x
		@return 42;
	}
	MapIdx_(using inline Thing, a0);
	FUNC_CHECK_ARR(a0, a1);
}

Test:FUNC_ZipWith()
{
	new
		a0[10] = { 0,  1,  2, ...},
		a1[10] = {10, 20, 30, ...},
		a2[10],
		a3[10] = { 0, 20, 60, 120, 200, 300, 420, 560, 720, 900};
	inline const Mul(a, b) @return a * b;
	ZipWith(using inline Mul, a0, a1, a2);
	FUNC_CHECK_ARR(a2, a3);
}

Test:FUNC_ZipWith3()
{
	new
		a0[10] = { 0,  1,  2, ...},
		a1[10] = {10, 20, 30, ...},
		a9[10] = {22, ...},
		a2[10],
		a3[10] = {22, 42, 82, 142, 222, 322, 442, 582, 742, 922};
	inline const MulAdd(a, b, c) @return a * b + c;
	ZipWith3(using inline MulAdd, a0, a1, a9, a2);
	FUNC_CHECK_ARR(a2, a3);
}

Test:FUNC_FoldR1()
{
	new
		a0[10] = { 0,  1,  2, ...},
		ret;
	ret = FoldR({_0 * _1}, a0, 10);
	ASSERT(ret == 0);
}

Test:FUNC_FoldR2()
{
	new
		a0[10] = { 1,  2,  3, ...},
		ret;
	ret = FoldR({_0 * _1}, a0, 10);
	ASSERT(ret == 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 10);
}

Test:FUNC_FoldL1()
{
	new
		a0[10] = { 1,  2,  3, ...},
		ret;
	ret = FoldL({_0 * _1}, 11, a0);
	ASSERT(ret == 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11);
}

Test:FUNC_FoldR3()
{
	new
		a0[10] = { 1,  2,  3, ...},
		ret;
	ret = FoldR({_0 * _1}, a0, 15, 0);
	ASSERT(ret == 15);
}

Test:FUNC_FoldL2()
{
	new
		a0[10] = { 1,  2,  3, ...},
		ret;
	ret = FoldL({_0 * _1}, 99, a0, 0);
	ASSERT(ret == 99);
}

#undef FUNC_CHECK_ARR

