foreign stock M_Func1();
foreign stock M_Func2(in);
foreign stock void:M_Func3(&ret, in);
foreign stock string:M_Func4();
foreign stock string:M_Func5(const string:in[]);
foreign stock M_Func6();

global M_Func1()
{
	return YSIM_TEST_MODULE;
}

global M_Func2(in)
{
	return YSIM_TEST_MODULE * in;
}

global void:M_Func3(&ret, in)
{
	ret = YSIM_TEST_MODULE + in;
}

global string:M_Func4()
{
	new
		str[YSI_MAX_STRING];
	format(str, sizeof (str), "MODULE %d", YSIM_TEST_MODULE);
	return str;
}

global string:M_Func5(const string:in[])
{
	new
		str[YSI_MAX_STRING];
	format(str, sizeof (str), in, YSIM_TEST_MODULE);
	return str;
}

global M_Func6()
{
	return Master_Caller() << 16 | YSIM_TEST_MODULE;
}

