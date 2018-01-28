#define Y_UTILS_NO_VALUE
#define Y_UTILS_VALUE (42)
#define Y_UTILS_INVALID (999999)

static stock
	gCalls_y_utils_va_return;

forward y_utils_va_return(str[]);

public y_utils_va_return(str[])
{
	ASSERT(!strcmp(str, "Hello World 42 9.455"));
	++gCalls_y_utils_va_return;
}

Test:y_utils_va_return()
{
	gCalls_y_utils_va_return = 0;
	y_utils_va_return(va_return("Hello %s %d %.3f", "World", 42, 9.4554));
	CallLocalFunction("y_utils_va_return", "s", va_return("Hello %s %d %.3f", "World", 42, 9.4554));
	CallLocalFunction(va_return("%s_%s", "y_utils", "va_return"), "s", "Hello World 42 9.455");
	CallLocalFunction(va_return("%s_%s", "y_utils", "va_return"), va_return("s"), va_return("Hello %s %d %.3f", "World", 42, 9.4554));
	ASSERT(gCalls_y_utils_va_return == 4);
}

static stock va_return_Pass(message[], va_args<>)
{
	new
		str[64];
	printf("<prefix> %s", va_return(message, va_start<1>));
	return str;
}

Test:va_return_PassParameters()
{
	new
		str[64];
	str = va_return_Pass("Something");
	ASSERT(!strcmp(str, "<prefix> Something"));
	str = va_return_Pass("Something, %i", 5);
	ASSERT(!strcmp(str, "<prefix> Something, 5"));
}

