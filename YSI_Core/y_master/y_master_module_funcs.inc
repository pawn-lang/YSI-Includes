FOREIGN__ stock M_Func1();
FOREIGN__ stock M_Func2(in);
FOREIGN__ stock void:M_Func3(&ret, in);
FOREIGN__ stock string:M_Func4();
FOREIGN__ stock string:M_Func5(const string:in[]);
FOREIGN__ stock M_Func6();

GLOBAL__ M_Func1()
{
	return YSIM_TEST_MODULE;
}

GLOBAL__ M_Func2(in)
{
	return YSIM_TEST_MODULE * in;
}

GLOBAL__ void:M_Func3(&ret, in)
{
	ret = YSIM_TEST_MODULE + in;
}

GLOBAL__ string:M_Func4()
{
	new
		str[YSI_MAX_STRING];
	format(str, sizeof (str), "MODULE %d", YSIM_TEST_MODULE);
	return str;
}

GLOBAL__ string:M_Func5(const string:in[])
{
	new
		str[YSI_MAX_STRING];
	format(str, sizeof (str), in, YSIM_TEST_MODULE);
	return str;
}

GLOBAL__ M_Func6()
{
	return Master_Caller() << 16 | YSIM_TEST_MODULE;
}

