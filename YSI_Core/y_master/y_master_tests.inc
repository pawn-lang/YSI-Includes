// These really just test that all the combinations compile...

YSIM_NONE_FOREIGN stock y_master_test_1(&a, &e, const b[], c, const string:d[]);
YSIM_NONE_GLOBAL  stock y_master_test_1(&a, &e, const b[], c, const string:d[])
{
	#pragma unused a, e, b, c, d
	a = c + 5;
	e = c;
	ASSERT_SAME(d, "hi");
	return 42;
}

YSIM_CLOUD_FOREIGN stock y_master_test_2(&a, &e, const string:d[], const b[], c = sizeof (b));
YSIM_CLOUD_GLOBAL  stock y_master_test_2(&a, &e, const string:d[], const b[], c = sizeof (b))
{
	#pragma unused a, e, b, c, d
	a = c / 2;
	return 43;
}

YSIM_SERVER_FOREIGN stock y_master_test_3(&a, &e, const b[], c, const string:d[] = "yo");
YSIM_SERVER_GLOBAL  stock y_master_test_3(&a, &e, const b[], c, const string:d[] = "yo")
{
	#pragma unused a, e, b, c, d
	ASSERT_SAME(d, "yo");
	a = 90;
	return 44;
}

YSIM_CLIENT_FOREIGN stock y_master_test_4(&a, &e, const b[], c, const string:d[]);
YSIM_CLIENT_GLOBAL  stock y_master_test_4(&a, &e, const b[], c, const string:d[])
{
	#pragma unused a, e, b, c, d
	a = 101;
	e = 999;
	return 45;
}

YSIM_STUB_FOREIGN stock y_master_test_5(&a, &e, const b[], c = sizeof (b), const string:d[] = "hmm");

TEST__ y_master_IntReturn()
{
	new b1[4], b2[70];
	new a = 6, e = 11;
	ASSERT_EQ(y_master_test_1(a, e, b1, sizeof (b1), "hi"), 42);
	ASSERT_EQ(a, 9);
	ASSERT_EQ(e, 4);
	ASSERT_ZE(y_master_test_4(a, e, b1, sizeof (b1), "hi"));
	ASSERT_EQ(a, 9);
	ASSERT_EQ(e, 4);
	#if !defined YSI_NO_MASTER
		ASSERT_EQ(y_master_test_2(a, e, "yeah", b2), 43);
		ASSERT_EQ(a, 35);
		ASSERT_EQ(e, 4);
	#endif
	ASSERT_EQ(y_master_test_3(a, e, b2, sizeof (b2)), 44);
	ASSERT_EQ(a, 90);
	ASSERT_EQ(e, 4);
	ASSERT_ZE(y_master_test_5(a, e, b2));
	ASSERT_EQ(a, 90);
	ASSERT_EQ(e, 4);
}

YSIM_NONE_FOREIGN stock string:y_master_test_1s(&a, &e, const b[], c, const string:d[]);
YSIM_NONE_GLOBAL  stock string:y_master_test_1s(&a, &e, const b[], c, const string:d[])
{
	#pragma unused a, e, b, c, d
	new ret[YSI_MAX_STRING] = "Returned.";
	return ret;
}

YSIM_CLOUD_FOREIGN stock string:y_master_test_2s(&a, &e, const b[], c, const string:d[]);
YSIM_CLOUD_GLOBAL  stock string:y_master_test_2s(&a, &e, const b[], c, const string:d[])
{
	#pragma unused a, e, b, c, d
	new ret[YSI_MAX_STRING] = "Returned.";
	return ret;
}

YSIM_SERVER_FOREIGN stock string:y_master_test_3s(&a, &e, const b[], c, const string:d[]);
YSIM_SERVER_GLOBAL  stock string:y_master_test_3s(&a, &e, const b[], c, const string:d[])
{
	#pragma unused a, e, b, c, d
	new ret[YSI_MAX_STRING] = "Returned.";
	return ret;
}

YSIM_CLIENT_FOREIGN stock string:y_master_test_4s(&a, &e, const b[], c, const string:d[]);
YSIM_CLIENT_GLOBAL  stock string:y_master_test_4s(&a, &e, const b[], c, const string:d[])
{
	#pragma unused a, e, b, c, d
	new ret[YSI_MAX_STRING] = "Returned.";
	return ret;
}

YSIM_STUB_FOREIGN stock string:y_master_test_5s(&a, &e, const b[], c, const string:d[]);

YSIM_NONE_FOREIGN stock void:y_master_test_1v(&a, &e, const b[], c, const string:d[]);
YSIM_NONE_GLOBAL  stock void:y_master_test_1v(&a, &e, const b[], c, const string:d[])
{
	#pragma unused a, e, b, c, d
}

YSIM_CLOUD_FOREIGN stock void:y_master_test_2v(&a, &e, const b[], c, const string:d[]);
YSIM_CLOUD_GLOBAL  stock void:y_master_test_2v(&a, &e, const b[], c, const string:d[])
{
	#pragma unused a, e, b, c, d
}

YSIM_SERVER_FOREIGN stock void:y_master_test_3v(&a, &e, const b[], c, const string:d[]);
YSIM_SERVER_GLOBAL  stock void:y_master_test_3v(&a, &e, const b[], c, const string:d[])
{
	#pragma unused a, e, b, c, d
}

YSIM_CLIENT_FOREIGN stock void:y_master_test_4v(&a, &e, const b[], c, const string:d[]);
YSIM_CLIENT_GLOBAL  stock void:y_master_test_4v(&a, &e, const b[], c, const string:d[])
{
	#pragma unused a, e, b, c, d
}

YSIM_STUB_FOREIGN stock void:y_master_test_5v(&a, &e, b[], const c, string:d[]);

YSIM_NONE_FOREIGN stock Float:y_master_test_1f(&a, &e, b[], c, const string:d[]);
YSIM_NONE_GLOBAL  stock Float:y_master_test_1f(&a, &e, b[], c, const string:d[])
{
	#pragma unused a, e, b, c, d
	return 44.0;
}

YSIM_CLOUD_FOREIGN stock Float:y_master_test_2f(&a, &e, const b[], c, const string:d[]);
YSIM_CLOUD_GLOBAL  stock Float:y_master_test_2f(&a, &e, const b[], c, const string:d[])
{
	#pragma unused a, e, b, c, d
	return 44.0;
}

YSIM_SERVER_FOREIGN stock Float:y_master_test_3f(&a, &e, const b[], c, const string:d[]);
YSIM_SERVER_GLOBAL  stock Float:y_master_test_3f(&a, &e, const b[], c, const string:d[])
{
	#pragma unused a, e, b, c, d
	return 44.0;
}

YSIM_CLIENT_FOREIGN stock Float:y_master_test_4f(&a, &e, const b[], c, const string:d[]);
YSIM_CLIENT_GLOBAL  stock Float:y_master_test_4f(&a, &e, const b[], c, const string:d[])
{
	#pragma unused a, e, b, c, d
	return 44.0;
}

YSIM_STUB_FOREIGN stock Float:y_master_test_5f(&a, &e, const b[], c, const string:d[]);

YSIM_NONE_FOREIGN stock y_master_test_1n();
YSIM_NONE_GLOBAL  stock y_master_test_1n()
{
	return 43;
}

YSIM_CLOUD_FOREIGN stock y_master_test_2n();
YSIM_CLOUD_GLOBAL  stock y_master_test_2n()
{
	return 43;
}

YSIM_SERVER_FOREIGN stock y_master_test_3n();
YSIM_SERVER_GLOBAL  stock y_master_test_3n()
{
	return 43;
}

YSIM_CLIENT_FOREIGN stock y_master_test_4n();
YSIM_CLIENT_GLOBAL  stock y_master_test_4n()
{
	return 43;
}

YSIM_STUB_FOREIGN stock y_master_test_5n();

YSIM_NONE_FOREIGN stock string:y_master_test_1sn();
YSIM_NONE_GLOBAL  stock string:y_master_test_1sn()
{
	new ret[YSI_MAX_STRING] = "Returned.";
	return ret;
}

YSIM_CLOUD_FOREIGN stock string:y_master_test_2sn();
YSIM_CLOUD_GLOBAL  stock string:y_master_test_2sn()
{
	new ret[YSI_MAX_STRING] = "Returned.";
	return ret;
}

YSIM_SERVER_FOREIGN stock string:y_master_test_3sn();
YSIM_SERVER_GLOBAL  stock string:y_master_test_3sn()
{
	new ret[YSI_MAX_STRING] = "Returned.";
	return ret;
}

YSIM_CLIENT_FOREIGN stock string:y_master_test_4sn();
YSIM_CLIENT_GLOBAL  stock string:y_master_test_4sn()
{
	new ret[YSI_MAX_STRING] = "Returned.";
	return ret;
}

YSIM_STUB_FOREIGN stock string:y_master_test_5sn();

YSIM_NONE_FOREIGN stock void:y_master_test_1vn();
YSIM_NONE_GLOBAL  stock void:y_master_test_1vn()
{
}

YSIM_CLOUD_FOREIGN stock void:y_master_test_2vn();
YSIM_CLOUD_GLOBAL  stock void:y_master_test_2vn()
{
}

YSIM_SERVER_FOREIGN stock void:y_master_test_3vn();
YSIM_SERVER_GLOBAL  stock void:y_master_test_3vn()
{
}

YSIM_CLIENT_FOREIGN stock void:y_master_test_4vn();
YSIM_CLIENT_GLOBAL  stock void:y_master_test_4vn()
{
}

YSIM_STUB_FOREIGN stock void:y_master_test_5vn();

YSIM_NONE_FOREIGN stock Float:y_master_test_1fn();
YSIM_NONE_GLOBAL  stock Float:y_master_test_1fn()
{
	return 44.0;
}

YSIM_CLOUD_FOREIGN stock Float:y_master_test_2fn();
YSIM_CLOUD_GLOBAL  stock Float:y_master_test_2fn()
{
	return 44.0;
}

YSIM_SERVER_FOREIGN stock Float:y_master_test_3fn();
YSIM_SERVER_GLOBAL  stock Float:y_master_test_3fn()
{
	return 44.0;
}

YSIM_CLIENT_FOREIGN stock Float:y_master_test_4fn();
YSIM_CLIENT_GLOBAL  stock Float:y_master_test_4fn()
{
	return 44.0;
}

YSIM_STUB_FOREIGN stock Float:y_master_test_5fn();

static stock
	YSI_g_sTestVar = 0;

HOOK__ OnMasterSystemInit(id)
{
	YSI_g_sTestVar = 6;
}

TEST__ y_master_Init()
{
	ASSERT_EQ(YSI_g_sTestVar, 6);
	ASSERT_NZ(Master_ID());
	ASSERT_EQ(_YCM_g@6, _E_YCM@y);
	ASSERT_SAME(#_YCM, "@6");
}

