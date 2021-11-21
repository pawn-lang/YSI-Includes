FOREIGN__ stock M_FuncP();
FOREIGN__ stock M_FuncR(in);
FOREIGN__ stock void:M_FuncT(&ret, in);
FOREIGN__ stock string:M_FuncV();
FOREIGN__ stock string:M_FuncX(const string:in[]);
FOREIGN__ stock M_FuncZ();

GLOBAL__ M_FuncP()
{
	return YSIM_TEST_MODULE;
}

GLOBAL__ M_FuncR(in)
{
	return YSIM_TEST_MODULE * in;
}

GLOBAL__ void:M_FuncT(&ret, in)
{
	ret = YSIM_TEST_MODULE + in;
}

GLOBAL__ string:M_FuncV()
{
	new
		str[YSI_MAX_STRING];
	format(str, sizeof (str), "MODULE %d", YSIM_TEST_MODULE);
	return str;
}

GLOBAL__ string:M_FuncX(const string:in[])
{
	new
		str[YSI_MAX_STRING];
	format(str, sizeof (str), in, YSIM_TEST_MODULE);
	return str;
}

GLOBAL__ M_FuncZ()
{
	return Master_Caller() << 16 | YSIM_TEST_MODULE;
}

