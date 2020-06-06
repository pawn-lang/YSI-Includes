// The prototypes to call.

FOREIGN__ M_Func1();
FOREIGN__ M_Func2(in);
FOREIGN__ void:M_Func3(&ret, in);
FOREIGN__ string:M_Func4();
FOREIGN__ string:M_Func5(const string:in[]);
FOREIGN__ M_Func6();

static stock Master_TestAll(base)
{
	new
		ret = 0;
	ASSERT_EQ(M_Func1(), base);
	ASSERT_EQ(M_Func2(42), 42 * base);
	ret = 0;
	M_Func3(ret, 11);
	if (base)
	{
		new
			str[32];
		ASSERT_EQ(ret, 11 + base);
		format(str, sizeof (str), "MODULE %d", base);
		ASSERT_SAME(M_Func4(), str);
		format(str, sizeof (str), "AA %d AA", base);
		ASSERT_SAME(M_Func5("AA %d AA"), str);
		ASSERT_EQ(M_Func6(), Master_ID() << 16 | base);
	}
	else
	{
		ASSERT_EQ(ret, 0);
		ASSERT_SAME(M_Func4(), "");
		ASSERT_SAME(M_Func5("AA %d AA"), "");
		ASSERT_EQ(M_Func6(), 0);
	}
}

TEST__ Master_ModulesPhase0a()
{
	// Run the tests, without any server module loaded.
	new
		ret = 0;
	ASSERT_EQ(M_Func1(), 0);
	ASSERT_EQ(M_Func2(42), 0);
	ret = 0;
	M_Func3(ret, 11);
	ASSERT_EQ(ret, 0);
	ASSERT_SAME(M_Func4(), "");
	ASSERT_SAME(M_Func5("AA %d AA"), "");
	ASSERT_EQ(M_Func6(), 0);
}

TEST__ Master_ModulesPhase0b()
{
	Master_TestAll(0);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(1);
	Master_UnloadModule("y_master_test_1");
	// Check the string returns are cleared.
	Master_TestAll(0);
}

TEST__ Master_ModulesPhase1a()
{
	// Loading a server after a cloud will steal it.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(1);
	Master_LoadModule("y_master_test_2");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_2");
	Master_TestAll(0);
}

TEST__ Master_ModulesPhase1b()
{
	// Loading a server after a cloud will steal it.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(1);
	Master_LoadModule("y_master_test_2");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_2");
	Master_TestAll(1);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(0);
}

TEST__ Master_ModulesPhase2a()
{
	// Loading a cloud after a server won't.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_2");
	Master_TestAll(2);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_2");
	Master_TestAll(0);
}

TEST__ Master_ModulesPhase2b()
{
	// Loading a cloud after a server won't.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_2");
	Master_TestAll(2);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_2");
	Master_TestAll(1);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(0);
}

TEST__ Master_ModulesPhase3a()
{
	// Even if the version is higher.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_2");
	Master_TestAll(2);
	Master_LoadModule("y_master_test_4");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_4");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_2");
	Master_TestAll(0);
}

TEST__ Master_ModulesPhase3b()
{
	// Even if the version is higher.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_2");
	Master_TestAll(2);
	Master_LoadModule("y_master_test_4");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_2");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_4");
	Master_TestAll(0);
}

TEST__ Master_ModulesPhase4a()
{
	// Higher cloud version.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(1);
	Master_LoadModule("y_master_test_4");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_4");
	Master_TestAll(0);
}

TEST__ Master_ModulesPhase4b()
{
	// Higher cloud version.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(1);
	Master_LoadModule("y_master_test_4");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_4");
	Master_TestAll(1);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(0);
}

TEST__ Master_ModulesPhase5a()
{
	// Lower cloud version.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_4");
	Master_TestAll(4);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_4");
	Master_TestAll(0);
}

TEST__ Master_ModulesPhase5b()
{
	// Lower cloud version.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_4");
	Master_TestAll(4);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_4");
	Master_TestAll(1);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(0);
}

TEST__ Master_ModulesPhase6()
{
	// Loading a client won't make any difference.
	Master_TestAll(0);
	Master_LoadModule("y_master_test_3");
	Master_TestAll(0);
	Master_LoadModule("y_master_test_1");
	Master_TestAll(1);
	Master_LoadModule("y_master_test_4");
	Master_TestAll(4);
	Master_LoadModule("y_master_test_2");
	Master_TestAll(2);
	Master_UnloadModule("y_master_test_2");
	Master_TestAll(4);
	Master_UnloadModule("y_master_test_4");
	Master_TestAll(1);
	Master_UnloadModule("y_master_test_1");
	Master_TestAll(0);
	Master_UnloadModule("y_master_test_3");
	Master_TestAll(0);
}

