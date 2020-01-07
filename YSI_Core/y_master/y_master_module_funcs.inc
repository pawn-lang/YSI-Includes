foreign M_Func1();
foreign M_Func2(in);
foreign void:M_Func3(&ret, in);
foreign string:M_Func4();
foreign string:M_Func5(const string:in[]);
foreign M_Func6();

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
		str[32];
	format(str, sizeof (str), "MODULE %d", YSIM_TEST_MODULE);
	return str;
}

global string:M_Func5(const string:in[])
{
	new
		str[32];
	format(str, sizeof (str), in, YSIM_TEST_MODULE);
	return str;
}

global M_Func6()
{
	return Master_Caller() << 8 | YSIM_TEST_MODULE;
}

