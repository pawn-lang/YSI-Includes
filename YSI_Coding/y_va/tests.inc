static
	YSI_g_sVariable;

forward y_va_PublicTestFunction(vara, varb);

public y_va_PublicTestFunction(vara, varb)
{
	if (vara)
	{
		YSI_g_sVariable = varb;
	}
	else
	{
		++YSI_g_sVariable;
	}
}

static stock y_va_CallRemoteFunction(va_args<>)
{
	va_CallRemoteFunction("y_va_PublicTestFunction", "ii", va_start<0>);
}

Test:y_va_CallRemoteFunction()
{
	YSI_g_sVariable = 5;
	y_va_CallRemoteFunction(0, 11);
	ASSERT(YSI_g_sVariable == 6);
	y_va_CallRemoteFunction(1, 11);
	ASSERT(YSI_g_sVariable == 11);
}

static stock y_va_CallLocalFunction(va_args<>)
{
	va_CallLocalFunction("y_va_PublicTestFunction", "ii", va_start<0>);
}

Test:y_va_CallLocalFunction()
{
	YSI_g_sVariable = 8;
	y_va_CallLocalFunction(0, 45);
	ASSERT(YSI_g_sVariable == 9);
	y_va_CallLocalFunction(1, 45);
	ASSERT(YSI_g_sVariable == 45);
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
