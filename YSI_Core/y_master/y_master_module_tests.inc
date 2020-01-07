// The prototypes to call.

foreign M_Func1();
foreign M_Func2(in);
foreign void:M_Func3(&ret, in);
foreign string:M_Func4();
foreign string:M_Func5(string:in[]);
foreign M_Func6();

static stock Master_TestAll(base)
{
	new
		ret,
		str[32];
	ASSERT_EQ(M_Func1(), base);
	ASSERT_EQ(M_Func2(42), 42 * base);
	ret = 0;
	M_Func3(ret, 11);
	ASSERT_EQ(ret, 11 + base);
	format(str, sizeof (str), "MODULE %d", base);
	ASSERT_SAME(M_Func4(), str);
	format(str, sizeof (str), "AA %d AA", base);
	ASSERT_SAME(M_Func5("AA %d AA"), str);
	ASSERT_EQ(M_Func6(), Master_ID() << 16 | base);
}

TEST__ Master_ModulesPhase0()
{
	// Run the tests, without any server module loaded.
	new
		ret;
	ASSERT_EQ(M_Func1(), base);
	ASSERT_EQ(M_Func2(42), 0);
	ret = 0;
	M_Func3(ret, 11);
	ASSERT_EQ(ret, 0);
	ASSERT_SAME(M_Func4(), "");
	ASSERT_SAME(M_Func5("AA %d AA"), "");
	ASSERT_EQ(M_Func6(), 0);
}

TEST__ Master_ModulesPhase1()
{
	Master_LoadModule("y_master_test_1");
	Master_TestAll(1);
	Master_UnloadModule("y_master_test_1");
	// Check the string returns are cleared.
	ASSERT_SAME(M_Func4(), "");
}

