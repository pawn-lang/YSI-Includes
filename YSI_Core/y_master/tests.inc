// These really just test that all the combinations compile...

YSIM_NONE_FOREIGN stock y_master_test_1(a, b[], c, string:d[]);
YSIM_NONE_GLOBAL  stock y_master_test_1(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
	return 42;
}

YSIM_CLOUD_FOREIGN stock y_master_test_2(a, b[], c, string:d[]);
YSIM_CLOUD_GLOBAL  stock y_master_test_2(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
	return 42;
}

YSIM_SERVER_FOREIGN stock y_master_test_3(a, b[], c, string:d[]);
YSIM_SERVER_GLOBAL  stock y_master_test_3(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
	return 42;
}

YSIM_CLIENT_FOREIGN stock y_master_test_4(a, b[], c, string:d[]);
YSIM_CLIENT_GLOBAL  stock y_master_test_4(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
	return 42;
}

YSIM_STUB_FOREIGN stock y_master_test_5(a, b[], c, string:d[]);

YSIM_NONE_FOREIGN stock string:y_master_test_1s(a, b[], c, string:d[]);
YSIM_NONE_GLOBAL  stock string:y_master_test_1s(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
	new ret[YSI_MAX_STRING] = "Returned.";
	return ret;
}

YSIM_CLOUD_FOREIGN stock string:y_master_test_2s(a, b[], c, string:d[]);
YSIM_CLOUD_GLOBAL  stock string:y_master_test_2s(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
	new ret[YSI_MAX_STRING] = "Returned.";
	return ret;
}

YSIM_SERVER_FOREIGN stock string:y_master_test_3s(a, b[], c, string:d[]);
YSIM_SERVER_GLOBAL  stock string:y_master_test_3s(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
	new ret[YSI_MAX_STRING] = "Returned.";
	return ret;
}

YSIM_CLIENT_FOREIGN stock string:y_master_test_4s(a, b[], c, string:d[]);
YSIM_CLIENT_GLOBAL  stock string:y_master_test_4s(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
	new ret[YSI_MAX_STRING] = "Returned.";
	return ret;
}

YSIM_STUB_FOREIGN stock string:y_master_test_5s(a, b[], c, string:d[]);

YSIM_NONE_FOREIGN stock void:y_master_test_1v(a, b[], c, string:d[]);
YSIM_NONE_GLOBAL  stock void:y_master_test_1v(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
}

YSIM_CLOUD_FOREIGN stock void:y_master_test_2v(a, b[], c, string:d[]);
YSIM_CLOUD_GLOBAL  stock void:y_master_test_2v(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
}

YSIM_SERVER_FOREIGN stock void:y_master_test_3v(a, b[], c, string:d[]);
YSIM_SERVER_GLOBAL  stock void:y_master_test_3v(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
}

YSIM_CLIENT_FOREIGN stock void:y_master_test_4v(a, b[], c, string:d[]);
YSIM_CLIENT_GLOBAL  stock void:y_master_test_4v(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
}

YSIM_STUB_FOREIGN stock void:y_master_test_5v(a, b[], c, string:d[]);

YSIM_NONE_FOREIGN stock Float:y_master_test_1f(a, b[], c, string:d[]);
YSIM_NONE_GLOBAL  stock Float:y_master_test_1f(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
	return 44.0;
}

YSIM_CLOUD_FOREIGN stock Float:y_master_test_2f(a, b[], c, string:d[]);
YSIM_CLOUD_GLOBAL  stock Float:y_master_test_2f(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
	return 44.0;
}

YSIM_SERVER_FOREIGN stock Float:y_master_test_3f(a, b[], c, string:d[]);
YSIM_SERVER_GLOBAL  stock Float:y_master_test_3f(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
	return 44.0;
}

YSIM_CLIENT_FOREIGN stock Float:y_master_test_4f(a, b[], c, string:d[]);
YSIM_CLIENT_GLOBAL  stock Float:y_master_test_4f(a, b[], c, string:d[])
{
	#pragma unused a, b, c, d
	return 44.0;
}

YSIM_STUB_FOREIGN stock Float:y_master_test_5f(a, b[], c, string:d[]);

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

