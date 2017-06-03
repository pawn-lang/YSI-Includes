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

static stock y_va2_printf_3(num, other, str[], GLOBAL_TAG_TYPES:...)
{
	#pragma unused num, other, str
	printf("", ___(3));
}

Test:y_va2_printf()
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
	return ret;
}

static stock y_va2_Three(...)
{
	return 3;
}

static stock y_va2_Nest2(fmat[YSI_MAX_STRING], ...)
{
	new
		dest[YSI_MAX_STRING];
	format(dest, sizeof (dest), fmat, ___1);
	ASSERT(!strcmp(dest, "second param second param final param"));
}

static stock y_va2_Nest1(...)
{
	y_va2_Nest2(y_va2_Extract(1, ___), y_va2_Extract(y_va2_Three(___), ___), y_va2_Extract(2, ___(1)), ___);
}

Test:y_va2_Nesting()
{
	y_va2_Nest1("final param", "%s %s %s", "third param", "second param");
}

static stock y_va2_format(dest[], size, fmat[], GLOBAL_TAG_TYPES:...)
{
	format(dest, size, fmat, ___(3));
}

Test:y_va2_format()
{
	new
		str[64];
	y_va2_format(str, sizeof (str), "Hello %d %04x %s", 99, 0x1F, "woop");
	ASSERT(!strcmp(str, "Hello 99 001F woop"));
}

static stock y_va2_return(dest[], size, fmat[], GLOBAL_TAG_TYPES:...)
{
	format(dest, size, fmat, ___(3));
}

Test:y_va2_return()
{
	new
		str[YSI_MAX_STRING * 8];
	y_va2_return(str, sizeof (str), "Hi %.3f %8.8s %8.8s", 5.5, "this is a very long string", "short");
	ASSERT(!strcmp(str, "Hi 5.500 this is  short   "));
}

static stock y_va2_DoubleIndirection(dest[1040], fmat[], var0, var1, var2, GLOBAL_TAG_TYPES:...) //var3, var4, size = sizeof (dest))
{
	#pragma unused var0, var1, var2
	// va_format(dest, 32, fmat, ___(5));
	format(dest, sizeof (dest), fmat, ___(5));
}

Test:y_va2_DoubleIndirection()
{
	new
		dest[1040],
		var0 = 44,
		var1 = 55,
		var2 = 66,
		var3 = 77,
		var4 = 88;
	y_va2_DoubleIndirection(dest, "%d %d", var0, var1, var2, var3, var4);
	ASSERT(var0 == 44);
	ASSERT(var1 == 55);
	ASSERT(var2 == 66);
	ASSERT(var3 == 77);
	ASSERT(var4 == 88);
	ASSERT(!strcmp(dest, "77 88"));
}

static stock y_va2_TripleIndirectionC(dest[1040], fmat[], var0, var1, var2, GLOBAL_TAG_TYPES:...)
{
	#pragma unused var0, var1, var2
	format(dest, sizeof (dest), fmat, ___(5));
	setarg(5, 0, 101);
}

static stock y_va2_TripleIndirectionB(dest[1040], fmat[], var0, var1, var2, GLOBAL_TAG_TYPES:...)
{
	y_va2_TripleIndirectionC(dest, fmat, var0, var1, var2, ___(5));
}

static stock y_va2_TripleIndirectionA(dest[1040], fmat[], var0, var1, var2, GLOBAL_TAG_TYPES:...)
{
	y_va2_TripleIndirectionB(dest, fmat, var0, var1, var2, ___(5));
}

Test:y_va2_TripleIndirection()
{
	new
		dest[1040],
		var0 = 44,
		var1 = 55,
		var2 = 66,
		var3 = 77,
		var4 = 88;
	y_va2_TripleIndirectionA(dest, "%d %d", var0, var1, var2, var3, var4);
	ASSERT(var0 == 44);
	ASSERT(var1 == 55);
	ASSERT(var2 == 66);
	ASSERT(var3 == 101);
	ASSERT(var4 == 88);
	ASSERT(!strcmp(dest, "77 88"));
}

static stock bool:y_va2_Locals(real[], fmat[], GLOBAL_TAG_TYPES:...)
{
	new
		dest[128];
	format(dest, sizeof (dest), fmat, ___2);
	return !strcmp(dest, real);
}

Test:y_va2_Locals()
{
	ASSERT(y_va2_Locals("42", "%d", 42));
	ASSERT(y_va2_Locals("42 43 44", "%d %d %d", 42, 43, 44));
	ASSERT(y_va2_Locals("hi", "%s", "hi"));
	ASSERT(y_va2_Locals("he -1", "%.2s %d", "hello", -1));
}

static stock
	YSI_g_sDestString[YSI_MAX_STRING];

Test:y_va2_PassThree()
{
	y_va2_MyFunc1("Hello", "there", "world");
	ASSERT(!strcmp(YSI_g_sDestString, "woo there world"));
	y_va2_MyFunc1("In", "the", "world");
	ASSERT(!strcmp(YSI_g_sDestString, "woo the world"));
	y_va2_MyFunc1("Hello", "one", "world");
	ASSERT(!strcmp(YSI_g_sDestString, "woo one world"));
	y_va2_MyFunc1("Hello", "there", "yeah");
	ASSERT(!strcmp(YSI_g_sDestString, "woo there yeah"));
	y_va2_MyFunc1("Hello", "there", "5");
	ASSERT(!strcmp(YSI_g_sDestString, "woo there 5"));
	y_va2_MyFunc1("Hello", "there", "C");
	ASSERT(!strcmp(YSI_g_sDestString, "woo there C"));
}

static stock y_va2_MyFunc3(...)
{
	new woo[32] = "woo";
	FIX_STRING_RETURN(woo);
}

static stock y_va2_MyFunc1(...)
{
	y_va2_MyFunc2(y_va2_MyFunc3(___), ___(1));
}

static stock y_va2_MyFunc2(...)
{
	format(YSI_g_sDestString, sizeof (YSI_g_sDestString), "%s %s %s", ___);
}

