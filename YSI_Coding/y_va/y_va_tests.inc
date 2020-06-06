static
	YSI_g_sVariable = 0;

static stock y_va_CallRemoteFunction(va_args<>)
{
	va_CallRemoteFunction("y_va_PublicTestFunction", "ii", va_start<0>);
}

static stock y_va_CallLocalFunction(va_args<>)
{
	new
		local1 = 123,
		local2 = 1,
		local3 = 7,
		local4 = 7;
	va_CallLocalFunction("y_va_PublicTestFunction", "ii", va_start<0>);
	return local1 * local2 + local3 - local4;
}

static stock y_va_CallLocalFunction_X(const func[], va_args<>)
{
	new
		local1 = 61,
		local2 = 2,
		local3 = 8,
		local4 = 7;
	va_CallLocalFunction(func, "si", va_start<1>);
	return local1 * local2 + local3 - local4;
}

static stock y_va_CallRemoteFunction_X(const func[], va_args<>)
{
	va_CallRemoteFunction(func, "si", va_start<1>);
}

forward y_va_PublicTestFunction(vara, varb);

public y_va_PublicTestFunction(vara, varb)
{
	new
		varc = 55,
		vard = 101;
	if (vara)
	{
		YSI_g_sVariable = varb;
	}
	else
	{
		++YSI_g_sVariable;
	}
	// Just use them so they can't be optimised out.
	vara = clamp(varb, varc, vard);
}

forward y_va_PublicRecurseFunction(const func[], vara);

public y_va_PublicRecurseFunction(const func[], vara)
{
	// "" Passed to "CallLocalFunction" crashes it.
	ASSERT_EQ(123, y_va_CallLocalFunction_X(func, "\1", vara));
}

forward y_va_PublicCallFunction(const func[], vara);

public y_va_PublicCallFunction(const func[], vara)
{
	y_va_PublicTestFunction(vara, 123456);
}

TEST__ y_va_CallRemoteFunction()
{
	YSI_g_sVariable = 5;
	y_va_CallRemoteFunction(0, 11);
	ASSERT_EQ(YSI_g_sVariable, 6);
	y_va_CallRemoteFunction(1, 11);
	ASSERT_EQ(YSI_g_sVariable, 11);
}

static stock y_va_printf_0(va_args<>)
{
	va_printf("", va_start<0>);
}

static stock y_va_printf_1(num, va_args<>)
{
	#pragma unused num
	va_printf("", va_start<1>);
}

static stock y_va_printf_2(num, other, va_args<>)
{
	#pragma unused num, other
	va_printf("", va_start<2>);
}

static stock y_va_printf_3(num, other, const str[], va_args<>)
{
	#pragma unused num, other, str
	va_printf("", va_start<3>);
}

TEST__ y_va_printf()
{
	y_va_printf_0(42, 1, "hi", I@);
	y_va_printf_1(42, 1, "hi", I@);
	y_va_printf_2(42, 1, "hi", I@);
	y_va_printf_3(42, 1, "hi", I@);
}

TEST__ y_va_recurse_local()
{
	YSI_g_sVariable = 0;
	y_va_CallLocalFunction_X("y_va_PublicRecurseFunction", "y_va_PublicCallFunction", true);
	ASSERT_EQ(YSI_g_sVariable, 123456);
	y_va_CallLocalFunction_X("y_va_PublicRecurseFunction", "y_va_PublicCallFunction", false);
	ASSERT_EQ(YSI_g_sVariable, 123457);
}

TEST__ y_va_recurse_remote()
{
	YSI_g_sVariable = 0;
	y_va_CallRemoteFunction_X("y_va_PublicRecurseFunction", "y_va_PublicCallFunction", true);
	ASSERT_EQ(YSI_g_sVariable, 123456);
	y_va_CallRemoteFunction_X("y_va_PublicRecurseFunction", "y_va_PublicCallFunction", false);
	ASSERT_EQ(YSI_g_sVariable, 123457);
}

TEST__ y_va_CallLocalFunction()
{
	YSI_g_sVariable = 8;
	y_va_CallLocalFunction(0, 45);
	ASSERT_EQ(YSI_g_sVariable, 9);
	ASSERT_EQ(123, y_va_CallLocalFunction(1, 45));
	ASSERT_EQ(YSI_g_sVariable, 45);
}

static stock y_va_SetTimerEx(va_args<>)
{
	return va_SetTimerEx("y_va_SetTimerExPublic", 1000, false, "iii", va_start<0>);
}

TEST__ y_va_SetTimerEx()
{
	ASSERT_NZ(y_va_SetTimerEx(5, 6, 7));
}

static stock y_va_format(dest[], size, const fmat[], va_args<>)
{
	va_format(dest, size, fmat, va_start<3>);
}

TEST__ y_va_format()
{
	new
		str[64];
	y_va_format(str, sizeof (str), "Hello %d %04x %s", 99, 0x1F, "woop");
	ASSERT_SAME(str, "Hello 99 001F woop");
}

static stock y_va_return(dest[], size, const fmat[], va_args<>)
{
	strcpy(dest, va_return(fmat, va_start<3>), size);
}

TEST__ y_va_return()
{
	new
		str[YSI_MAX_STRING];
	y_va_return(str, sizeof (str), "Hi %.3f %8.8s %8.8s", 5.5, "this is a very long string", "short");
	ASSERT_SAME(str, "Hi 5.500 this is  short   ");
}

static stock y_va_DoubleIndirection(dest[YSI_MAX_STRING], const fmat[], var0, var1, var2, va_args<>) //var3, var4, size = sizeof (dest))
{
	#pragma unused var0, var1, var2
	// va_format(dest, 32, fmat, va_start<5>);
	//dest = "hello 03/06/17";
	dest = va_return(fmat, va_start<5>);
	//print(dest);
}

TEST__ y_va_DoubleIndirection()
{
	new
		dest[YSI_MAX_STRING],
		var0 = 44,
		var1 = 55,
		var2 = 66,
		var3 = 77,
		var4 = 88;
	y_va_DoubleIndirection(dest, "%d %d", var0, var1, var2, var3, var4);
	ASSERT_EQ(var0, 44);
	ASSERT_EQ(var1, 55);
	ASSERT_EQ(var2, 66);
	ASSERT_EQ(var3, 77);
	ASSERT_EQ(var4, 88);
	ASSERT_SAME(dest, "77 88");
}

static stock bool:y_va_Locals(const real[], const fmat[], va_args<>)
{
	new
		dest[128];
	va_format(dest, sizeof (dest), fmat, va_start<2>);
	return !strcmp(dest, real);
}

TEST__ y_va_Locals()
{
	ASSERT(y_va_Locals("42", "%d", 42));
	ASSERT(y_va_Locals("42 43 44", "%d %d %d", 42, 43, 44));
	ASSERT(y_va_Locals("hi", "%s", "hi"));
	ASSERT(y_va_Locals("he -1", "%.2s %d", "hello", -1));
}

static stock y_va2_printf_0(GLOBAL_TAG_TYPES:...)
{
	printf("", ___);
}

static stock y_va2_printf_1(num, GLOBAL_TAG_TYPES:...)
{
	#pragma unused num
	printf("", ___(1));
}

static stock y_va2_printf_2(num, other, GLOBAL_TAG_TYPES:...)
{
	#pragma unused num, other
	printf("", ___2);
}

static stock y_va2_printf_3(num, other, const str[], GLOBAL_TAG_TYPES:...)
{
	#pragma unused num, other, str
	printf("", ___(3));
}

TEST__ y_va2_printf()
{
	y_va2_printf_0(42, 1, "hi", I@);
	y_va2_printf_1(42, 1, "hi", I@);
	y_va2_printf_2(42, 1, "hi", I@);
	y_va2_printf_3(42, 1, "hi", I@);
}

static stock y_va2_Extract(num, ...)
{
	new
		ret[YSI_MAX_STRING];
	va_getstring(ret, num + 1);
	__COMPILER_STRING_RETURN(ret);
}

static stock y_va2_Three(...)
{
	return 3;
}

static stock y_va2_Nest2(const fmat[YSI_MAX_STRING], ...)
{
	new
		dest[YSI_MAX_STRING];
	format(dest, sizeof (dest), fmat, ___1);
	ASSERT_SAME(dest, "second param second param final param");
}

static stock y_va2_Nest1(...)
{
	y_va2_Nest2(y_va2_Extract(1, ___), y_va2_Extract(y_va2_Three(___), ___), y_va2_Extract(2, ___(1)), ___);
}

TEST__ y_va2_Nesting()
{
	y_va2_Nest1("final param", "%s %s %s", "third param", "second param");
}

static stock y_va2_format(dest[], size, const fmat[], GLOBAL_TAG_TYPES:...)
{
	format(dest, size, fmat, ___(3));
}

TEST__ y_va2_format()
{
	new
		str[64];
	y_va2_format(str, sizeof (str), "Hello %d %04x %s", 99, 0x1F, "woop");
	ASSERT_SAME(str, "Hello 99 001F woop");
}

static stock y_va2_return(dest[], size, const fmat[], GLOBAL_TAG_TYPES:...)
{
	format(dest, size, fmat, ___(3));
}

TEST__ y_va2_return()
{
	new
		str[YSI_MAX_STRING];
	y_va2_return(str, sizeof (str), "Hi %.3f %8.8s %8.8s", 5.5, "this is a very long string", "short");
	ASSERT_SAME(str, "Hi 5.500 this is  short   ");
}

static stock y_va2_DoubleIndirection(dest[1040], const fmat[], var0, var1, var2, GLOBAL_TAG_TYPES:...) //var3, var4, size = sizeof (dest))
{
	#pragma unused var0, var1, var2
	// va_format(dest, 32, fmat, ___(5));
	format(dest, sizeof (dest), fmat, ___(5));
}

TEST__ y_va2_DoubleIndirection()
{
	new
		dest[1040],
		var0 = 44,
		var1 = 55,
		var2 = 66,
		var3 = 77,
		var4 = 88;
	y_va2_DoubleIndirection(dest, "%d %d", var0, var1, var2, var3, var4);
	ASSERT_EQ(var0, 44);
	ASSERT_EQ(var1, 55);
	ASSERT_EQ(var2, 66);
	ASSERT_EQ(var3, 77);
	ASSERT_EQ(var4, 88);
	ASSERT_SAME(dest, "77 88");
}

static stock y_va2_TripleIndirectionC(dest[1040], const fmat[], var0, var1, var2, GLOBAL_TAG_TYPES:...)
{
	#pragma unused var0, var1, var2
	format(dest, sizeof (dest), fmat, ___(5));
	setarg(5, 0, 101);
}

static stock y_va2_TripleIndirectionB(dest[1040], const fmat[], var0, var1, var2, GLOBAL_TAG_TYPES:...)
{
	y_va2_TripleIndirectionC(dest, fmat, var0, var1, var2, ___(5));
}

static stock y_va2_TripleIndirectionA(dest[1040], const fmat[], var0, var1, var2, GLOBAL_TAG_TYPES:...)
{
	y_va2_TripleIndirectionB(dest, fmat, var0, var1, var2, ___(5));
}

TEST__ y_va2_TripleIndirection()
{
	new
		dest[1040],
		var0 = 44,
		var1 = 55,
		var2 = 66,
		var3 = 77,
		var4 = 88;
	y_va2_TripleIndirectionA(dest, "%d %d", var0, var1, var2, var3, var4);
	ASSERT_EQ(var0, 44);
	ASSERT_EQ(var1, 55);
	ASSERT_EQ(var2, 66);
	ASSERT_EQ(var3, 101);
	ASSERT_EQ(var4, 88);
	ASSERT_SAME(dest, "77 88");
}

static stock bool:y_va2_Locals(const real[], const fmat[], GLOBAL_TAG_TYPES:...)
{
	new
		dest[128];
	format(dest, sizeof (dest), fmat, ___2);
	return !strcmp(dest, real);
}

TEST__ y_va2_Locals()
{
	ASSERT(y_va2_Locals("42", "%d", 42));
	ASSERT(y_va2_Locals("42 43 44", "%d %d %d", 42, 43, 44));
	ASSERT(y_va2_Locals("hi", "%s", "hi"));
	ASSERT(y_va2_Locals("he -1", "%.2s %d", "hello", -1));
}

TEST__ y_va2_Types()
{
	ASSERT(y_va2_Locals("4.67", "%.2f", 4.672));
	ASSERT(y_va2_Locals("Hello World", "%s", "Hello World"));
}

TEST__ y_va2_NoParameters()
{
	ASSERT(y_va2_Locals("hello", "hello"));
	ASSERT(y_va2_Locals("Hello World", "Hello World"));
	ASSERT(y_va2_Locals("42 43 44 45 46 47", "42 43 44 45 46 47"));
}

static stock
	YSI_g_sDestString[YSI_MAX_STRING];

TEST__ y_va2_PassThree()
{
	y_va2_MyFunc1("Hello", "there", "world");
	ASSERT_SAME(YSI_g_sDestString, "woo there world");
	y_va2_MyFunc1("In", "the", "world");
	ASSERT_SAME(YSI_g_sDestString, "woo the world");
	y_va2_MyFunc1("Hello", "one", "world");
	ASSERT_SAME(YSI_g_sDestString, "woo one world");
	y_va2_MyFunc1("Hello", "there", "yeah");
	ASSERT_SAME(YSI_g_sDestString, "woo there yeah");
	y_va2_MyFunc1("Hello", "there", "5");
	ASSERT_SAME(YSI_g_sDestString, "woo there 5");
	y_va2_MyFunc1("Hello", "there", "C");
	ASSERT_SAME(YSI_g_sDestString, "woo there C");
}

static stock y_va2_MyFunc3(...)
{
	new woo[32] = "woo";
	__COMPILER_STRING_RETURN(woo);
	//__COMPILER_STRING_RETURN("woo", 32);
}

static stock y_va2_MyFunc1(...)
{
	y_va2_MyFunc2(y_va2_MyFunc3(___), ___(1));
}

static stock y_va2_MyFunc2(...)
{
	format(YSI_g_sDestString, sizeof (YSI_g_sDestString), "%s %s %s", ___);
}

static stock y_va_BlankFormat1(...)
{
	new string[144];
	va_format(string, sizeof (string), "%s", ___);
//	print(string);
}

TEST__ y_va_BlankFormat1()
{
	new abc[32] = "WAT";
	y_va_BlankFormat1(abc);
	y_va_BlankFormat1(abc);
	y_va_BlankFormat1(abc);
	y_va_BlankFormat1(abc);
}

static stock
	YSI_g_sString[144];

static stock y_va_BlankFormat2(...)
{
	new string[144];
	va_format(YSI_g_sString, sizeof (YSI_g_sString), "%s", ___);
	#pragma unused string
//	print(string);
}

TEST__ y_va_BlankFormat2()
{
	new abc[32] = "WAT";
	YSI_g_sString[0] = '\0';
	y_va_BlankFormat2(abc);
	ASSERT_SAME(YSI_g_sString, "WAT");
	YSI_g_sString[0] = '\0';
	y_va_BlankFormat2(abc);
	ASSERT_SAME(YSI_g_sString, "WAT");
	YSI_g_sString[0] = '\0';
	y_va_BlankFormat2(abc);
	ASSERT_SAME(YSI_g_sString, "WAT");
	YSI_g_sString[0] = '\0';
	y_va_BlankFormat2(abc);
	ASSERT_SAME(YSI_g_sString, "WAT");
}

static stock va_return_Pass(const message[], va_args<>)
{
	new
		str[64];
	format(str, sizeof (str), "<prefix> %s", va_return(message, va_start<1>));
	return str;
}

TEST__ va_return_PassParameters()
{
	new
		str[64];
	str = va_return_Pass("Something");
	ASSERT_SAME(str, "<prefix> Something");
	str = va_return_Pass("Something, %i", 5);
	ASSERT_SAME(str, "<prefix> Something, 5");
}

