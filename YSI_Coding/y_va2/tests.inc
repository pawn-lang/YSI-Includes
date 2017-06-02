static
	YSI_g_sVariable;

//static stock y_va2_CallRemoteFunction(GLOBAL_TAG_TYPES:...)
//{
//	CallRemoteFunction("y_va2_PublicTestFunction", "ii", ___);
//}
//
//static stock y_va2_CallLocalFunction(GLOBAL_TAG_TYPES:...)
//{
//	new
//		local1 = 123,
//		local2 = 1,
//		local3 = 7,
//		local4 = 7;
//	va_CallLocalFunction("y_va2_PublicTestFunction", "ii", ___);
//	return local1 * local2 + local3 - local4;
//}
//
//static stock y_va2_CallLocalFunction_X(func[], GLOBAL_TAG_TYPES:...)
//{
//	new
//		local1 = 61,
//		local2 = 2,
//		local3 = 8,
//		local4 = 7;
//	CallLocalFunction(func, "si", ___(1));
//	return local1 * local2 + local3 - local4;
//}
//
//static stock y_va2_CallRemoteFunction_X(func[], GLOBAL_TAG_TYPES:...)
//{
//	CallRemoteFunction(func, "si", ___(1));
//}
//
//forward y_va2_PublicTestFunction(vara, varb);
//
//public y_va2_PublicTestFunction(vara, varb)
//{
//	new
//		varc = 55,
//		vard = 101;
//	if (vara)
//	{
//		YSI_g_sVariable = varb;
//	}
//	else
//	{
//		++YSI_g_sVariable;
//	}
//	// Just use them so they can't be optimised out.
//	vara = clamp(varb, varc, vard);
//}
//
//forward y_va2_PublicRecurseFunction(func[], vara);
//
//public y_va2_PublicRecurseFunction(func[], vara)
//{
//	// "" Passed to "CallLocalFunction" crashes it.
//	ASSERT(123 == y_va2_CallLocalFunction_X(func, "\1", vara));
//}
//
//forward y_va2_PublicCallFunction(func[], vara);
//
//public y_va2_PublicCallFunction(func[], vara)
//{
//	y_va2_PublicTestFunction(vara, 123456);
//}
//
//Test:y_va2_CallRemoteFunction()
//{
//	YSI_g_sVariable = 5;
//	y_va2_CallRemoteFunction(0, 11);
//	ASSERT(YSI_g_sVariable == 6);
//	y_va2_CallRemoteFunction(1, 11);
//	ASSERT(YSI_g_sVariable == 11);
//}

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

//Test:y_va2_recurse_local()
//{
//	YSI_g_sVariable = 0;
//	y_va2_CallLocalFunction_X("y_va2_PublicRecurseFunction", "y_va2_PublicCallFunction", true);
//	ASSERT(YSI_g_sVariable == 123456);
//	y_va2_CallLocalFunction_X("y_va2_PublicRecurseFunction", "y_va2_PublicCallFunction", false);
//	ASSERT(YSI_g_sVariable == 123457);
//}
//
//Test:y_va2_recurse_remote()
//{
//	YSI_g_sVariable = 0;
//	y_va2_CallRemoteFunction_X("y_va2_PublicRecurseFunction", "y_va2_PublicCallFunction", true);
//	ASSERT(YSI_g_sVariable == 123456);
//	y_va2_CallRemoteFunction_X("y_va2_PublicRecurseFunction", "y_va2_PublicCallFunction", false);
//	ASSERT(YSI_g_sVariable == 123457);
//}
//
//Test:y_va2_CallLocalFunction()
//{
//	YSI_g_sVariable = 8;
//	y_va2_CallLocalFunction(0, 45);
//	ASSERT(YSI_g_sVariable == 9);
//	ASSERT(123 == y_va2_CallLocalFunction(1, 45));
//	ASSERT(YSI_g_sVariable == 45);
//}
//
//static stock y_va2_SetTimerEx(GLOBAL_TAG_TYPES:...)
//{
//	return va_SetTimerEx("y_va2_SetTimerExPublic", 1000, false, "iii", ___);
//}
//
//Test:va_SetTimerEx()
//{
//	ASSERT(y_va2_SetTimerEx(5, 6, 7) != 0);
//}

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
	//strcpy(dest, va_return(fmat, ___(3)), size);
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
	printf(dest);
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

