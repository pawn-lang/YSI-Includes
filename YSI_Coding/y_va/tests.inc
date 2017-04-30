static
	YSI_g_sVariable;

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

static stock y_va_CallLocalFunction_X(func[], va_args<>)
{
	new
		local1 = 61,
		local2 = 2,
		local3 = 8,
		local4 = 7;
	va_CallLocalFunction(func, "si", va_start<1>);
	return local1 * local2 + local3 - local4;
}

static stock y_va_CallRemoteFunction_X(func[], va_args<>)
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

forward y_va_PublicRecurseFunction(func[], vara);

public y_va_PublicRecurseFunction(func[], vara)
{
	// "" Passed to "CallLocalFunction" crashes it.
	ASSERT(123 == y_va_CallLocalFunction_X(func, "\1", vara));
}

forward y_va_PublicCallFunction(func[], vara);

public y_va_PublicCallFunction(func[], vara)
{
	y_va_PublicTestFunction(vara, 123456);
}

Test:y_va_CallRemoteFunction()
{
	YSI_g_sVariable = 5;
	y_va_CallRemoteFunction(0, 11);
	ASSERT(YSI_g_sVariable == 6);
	y_va_CallRemoteFunction(1, 11);
	ASSERT(YSI_g_sVariable == 11);
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

static stock y_va_printf_3(num, other, str[], va_args<>)
{
	#pragma unused num, other, str
	va_printf("", va_start<3>);
}

Test:y_va_printf()
{
	y_va_printf_0(42, 1, "hi", I@);
	y_va_printf_1(42, 1, "hi", I@);
	y_va_printf_2(42, 1, "hi", I@);
	y_va_printf_3(42, 1, "hi", I@);
}

Test:y_va_recurse_local()
{
	YSI_g_sVariable = 0;
	y_va_CallLocalFunction_X("y_va_PublicRecurseFunction", "y_va_PublicCallFunction", true);
	ASSERT(YSI_g_sVariable == 123456);
	y_va_CallLocalFunction_X("y_va_PublicRecurseFunction", "y_va_PublicCallFunction", false);
	ASSERT(YSI_g_sVariable == 123457);
}

Test:y_va_recurse_remote()
{
	YSI_g_sVariable = 0;
	y_va_CallRemoteFunction_X("y_va_PublicRecurseFunction", "y_va_PublicCallFunction", true);
	ASSERT(YSI_g_sVariable == 123456);
	y_va_CallRemoteFunction_X("y_va_PublicRecurseFunction", "y_va_PublicCallFunction", false);
	ASSERT(YSI_g_sVariable == 123457);
}

Test:y_va_CallLocalFunction()
{
	YSI_g_sVariable = 8;
	y_va_CallLocalFunction(0, 45);
	ASSERT(YSI_g_sVariable == 9);
	ASSERT(123 == y_va_CallLocalFunction(1, 45));
	ASSERT(YSI_g_sVariable == 45);
}

static stock y_va_SetTimerEx(va_args<>)
{
	return va_SetTimerEx("y_va_SetTimerExPublic", 1000, false, "iii", va_start<0>);
}

Test:va_SetTimerEx()
{
	ASSERT(y_va_SetTimerEx(5, 6, 7) != 0);
}

static stock y_va_format(dest[], size, fmat[], va_args<>)
{
	va_format(dest, size, fmat, va_start<3>);
}

Test:y_va_format()
{
	new
		str[64];
	y_va_format(str, sizeof (str), "Hello %d %04x %s", 99, 0x1F, "woop");
	ASSERT(!strcmp(str, "Hello 99 001F woop"));
}

static stock y_va_return(dest[], size, fmat[], va_args<>)
{
	strcpy(dest, va_return(fmat, va_start<3>), size);
}

Test:y_va_return()
{
	new
		str[YSI_MAX_STRING * 8];
	y_va_return(str, sizeof (str), "Hi %.3f %8.8s %8.8s", 5.5, "this is a very long string", "short");
	ASSERT(!strcmp(str, "Hi 5.500 this is  short   "));
}

static stock y_va_DoubleIndirection(dest[1040], fmat[], var0, var1, var2, va_args<>) //var3, var4, size = sizeof (dest))
{
	#pragma unused var0, var1, var2
	// va_format(dest, 32, fmat, va_start<5>);
	dest = va_return(fmat, va_start<5>);
}

Test:y_va_DoubleIndirection()
{
	new
		dest[1040],
		var0 = 44,
		var1 = 55,
		var2 = 66,
		var3 = 77,
		var4 = 88;
	y_va_DoubleIndirection(dest, "%d %d", var0, var1, var2, var3, var4);
	ASSERT(var0 == 44);
	ASSERT(var1 == 55);
	ASSERT(var2 == 66);
	ASSERT(var3 == 77);
	ASSERT(var4 == 88);
	ASSERT(!strcmp(dest, "77 88"));
}

static stock bool:y_va_Locals(real[], fmat[], va_args<>)
{
	new
		dest[128];
	va_format(dest, sizeof (dest), fmat, va_start<2>);
	return !strcmp(dest, real);
}

Test:y_va_Locals()
{
	ASSERT(y_va_Locals("42", "%d", 42));
	ASSERT(y_va_Locals("42 43 44", "%d %d %d", 42, 43, 44));
	ASSERT(y_va_Locals("hi", "%s", "hi"));
	ASSERT(y_va_Locals("he -1", "%.2s %d", "hello", -1));
}

