#define Y_UTILS_NO_VALUE
#define Y_UTILS_VALUE (42)
#define Y_UTILS_INVALID (999999)

TEST_COMPILE__ y_utils()
{
#if !__COMPILER_1ST_PASS
	#assert NO_VALUE(Y_UTILS_NO_VALUE)
	#assert !NO_VALUE(Y_UTILS_VALUE)
	#assert IS_IN_RANGE(Y_UTILS_VALUE, -30, 43)
	#assert !IS_IN_RANGE(Y_UTILS_VALUE, -30, 42)
	#assert NOT_IN_RANGE(Y_UTILS_VALUE, 0, 10)
	#assert !NOT_IN_RANGE(Y_UTILS_VALUE, 20, 100)
	#assert VALID_PLAYERID(Y_UTILS_VALUE)
	#assert !VALID_PLAYERID(Y_UTILS_INVALID)
	#assert UCMP(4, 100)
	#assert !UCMP(-4, 100)
	BeautifyProfilingTime(0, 0);
	#assert ceildiv(12, 3) == 4
	#assert ceildiv(11, 3) == 4
	#assert ceildiv(10, 3) == 4
	#assert ceildiv(9, 3) == 3
	#assert ceildiv(8, 3) == 3
	#assert floordiv(12, 3) == 4
	#assert floordiv(11, 3) == 3
	#assert floordiv(10, 3) == 3
	#assert floordiv(9, 3) == 3
	#assert floordiv(8, 3) == 2
	#assert IsOdd(3)
	#assert !IsOdd(8)
	#assert IsEven(8)
	#assert !IsEven(3)
#endif
	new str[32];
	ASSERT(IsNull(str));
	StrToLower(str);
	StrToUpper(str);
	Random(0);
	RandomFloat(0.0);
	StripNL(str);
	StripR(str);
	StripL(str);
	Strip(str);
	EndOfLine(str, 0);
	ChrFind(' ', str);
	// Gives a deprecation warning.  That's fine (for tests).
	chrfindp(' ', str);
	IPToInt(str);
	// Gives a deprecation warning.  That's fine (for tests).
	bernstein(str);
	IsHex(str);
	Unpack(str);
	#if defined _samp_included && !defined YSI_NO_GET_IP
		ASSERT_ZE(GetIP(0));
	#endif
	ReturnStringArg(0);
	va_return(str);
	IsNumeric(str);
}

static stock
	gCalls_y_utils_va_return = 0;

forward y_utils_va_return(const str[]);

public y_utils_va_return(const str[])
{
	ASSERT_SAME(str, "Hello World 42 9.455");
	++gCalls_y_utils_va_return;
}

TEST__ y_utils_va_return()
{
	gCalls_y_utils_va_return = 0;
	y_utils_va_return(va_return("Hello %s %d %.3f", "World", 42, 9.4554));
	R@("y_utils_va_return", "s", va_return("Hello %s %d %.3f", "World", 42, 9.4554));
	R@(va_return("%s_%s", "y_utils", "va_return"), "s", "Hello World 42 9.455");
	R@(va_return("%s_%s", "y_utils", "va_return"), va_return("s"), va_return("Hello %s %d %.3f", "World", 42, 9.4554));
	ASSERT_EQ(gCalls_y_utils_va_return, 4);
}

TEST__ y_utils_LevenshteinDistance()
{
	ASSERT_EQ(LevenshteinDistance("hello", "hello"), 0);
	ASSERT_EQ(LevenshteinDistance("Hello", "hello"), 1);
	ASSERT_EQ(LevenshteinDistance("helllo", "hello"), 1);
	ASSERT_EQ(LevenshteinDistance("helo", "hello"), 1);
	ASSERT_EQ(LevenshteinDistance("hellllo", "hello"), 2);
	ASSERT_EQ(LevenshteinDistance("heo", "hello"), 2);
	ASSERT_EQ(LevenshteinDistance("he,,o", "hello"), 2);
	ASSERT_EQ(LevenshteinDistance("HhlTo", "hello"), 3);
	ASSERT_EQ(LevenshteinDistance("hello", "there"), 4);
	ASSERT_EQ(LevenshteinDistance("hello", ""), 5);
	ASSERT_EQ(LevenshteinDistance("", "hello"), 5);
	ASSERT_EQ(LevenshteinDistance("", "01234567890123456789012345678901234567890123456789012345678901234567890123456789"), 80);
	ASSERT_EQ(LevenshteinDistance("01234567890123456789012345678901234567890123456789012345678901234567890123456789", "01234567890123456789012345678901234567890123456789012345678901234567890123456789"), 0);
	ASSERT_EQ(LevenshteinDistance("aa", "01234567890123456789012345678901"), 32);
	// Error case.
	ASSERT_EQ(LevenshteinDistance("012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789", "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"), 40);
}

TEST__ IsRPName1()
{
	// Standard names.
	ASSERT(IsRPName("Bob_Bobson"));
	ASSERT(IsRPName("Y_Less"));
	ASSERT(!IsRPName("_hello"));
	ASSERT(!IsRPName("Y__Less"));
	ASSERT(!IsRPName("William"));
	ASSERT(IsRPName("William Thompson"));
	ASSERT(!IsRPName("William Thompson."));
	ASSERT(!IsRPName("0_0"));
	ASSERT(!IsRPName("0_0"));
	ASSERT(!IsRPName("Tim1 Tom"));
	ASSERT(!IsRPName("Tim_"));
}

TEST__ IsRPName2()
{
	// Casing.
	ASSERT(IsRPName("Bob_Bobson", false, false));
	ASSERT(IsRPName("bob_bobson", false, false));
	ASSERT(IsRPName("Bob_Bobson", true, false));
	ASSERT(!IsRPName("bob_bobson", true, false));
	ASSERT(!IsRPName("James_Bob_Bobson", false, false));
	ASSERT(!IsRPName("James_bob_bobson", false, false));
	ASSERT(!IsRPName("James_Bob_Bobson", true, false));
	ASSERT(!IsRPName("James_bob_bobson", true, false));
}

TEST__ IsRPName3()
{
	// Long.
	ASSERT(IsRPName("Bob_Bobson", false, true));
	ASSERT(IsRPName("bob_bobson", false, true));
	ASSERT(IsRPName("Bob_Bobson", true, true));
	ASSERT(!IsRPName("bob_bobson", true, true));
	ASSERT(IsRPName("James_Bob_Bobson", false, true));
	ASSERT(IsRPName("James_bob_bobson", false, true));
	ASSERT(IsRPName("James_Bob_Bobson", true, true));
	ASSERT(!IsRPName("James_bob_bobson", true, true));
}

TEST__ Random1()
{
	for (new i = 0; i != 10000; ++i)
	{
		new rnd = Random(10);
		ASSERT(0 <= rnd < 10);
	}
}

TEST__ Random2a()
{
	new values[10];
	for (new i = 0; i != 10000; ++i)
	{
		new rnd = Random(10, 20);
		ASSERT(10 <= rnd < 20);
		++values[rnd - 10];
	}
	for (new i = 0; i != sizeof (values); ++i)
	{
		ASSERT_NZ(values[i]);
	}
}

TEST__ Random2b()
{
	new values[30];
	for (new i = 0; i != 10000; ++i)
	{
		new rnd = Random(-10, 20);
		ASSERT(-10 <= rnd < 20);
		++values[rnd + 10];
	}
	for (new i = 0; i != sizeof (values); ++i)
	{
		ASSERT_NZ(values[i]);
	}
}

TEST__ Random2c()
{
	new values[10];
	for (new i = 0; i != 10000; ++i)
	{
		new rnd = Random(-20, -10);
		ASSERT(-20 <= rnd < -10);
		++values[rnd + 20];
	}
	for (new i = 0; i != sizeof (values); ++i)
	{
		ASSERT_NZ(values[i]);
	}
}

TEST__ Random3a()
{
	new values[10];
	for (new i = 0; i != 10000; ++i)
	{
		new rnd = Random(10, 20, 13);
		ASSERT(10 <= rnd < 20);
		ASSERT_NE(rnd, 13);
		++values[rnd - 10];
	}
	for (new i = 0; i != sizeof (values); ++i)
	{
		if (i == 3)
		{
			ASSERT_ZE(values[i]);
		}
		else
		{
			ASSERT_NZ(values[i]);
		}
	}
}

TEST__ Random3b()
{
	new values[10];
	for (new i = 0; i != 10000; ++i)
	{
		new rnd = Random(10, 20, 30);
		ASSERT(10 <= rnd < 20);
		++values[rnd - 10];
	}
	for (new i = 0; i != sizeof (values); ++i)
	{
		ASSERT_NZ(values[i]);
	}
}

TEST__ Random3c()
{
	new values[10];
	for (new i = 0; i != 10000; ++i)
	{
		new rnd = Random(10, 20, 9);
		ASSERT(10 <= rnd < 20);
		++values[rnd - 10];
	}
	for (new i = 0; i != sizeof (values); ++i)
	{
		ASSERT_NZ(values[i]);
	}
}

TEST__ RandomN()
{
	for (new i = 0; i != 10000; ++i)
	{
		new rnd = Random(10, 20, 13, 14, 9, 40, 15);
		ASSERT(10 <= rnd < 20);
		ASSERT_NE(rnd, 13);
		ASSERT_NE(rnd, 14);
		ASSERT_NE(rnd, 15);
	}
}

TEST__ IterativeTextSplitter1()
{
	new end, next, bool:hyphen;
	IterativeTextSplitter("This is the first line with short words", 20, 0, end, next, hyphen);
	ASSERT_EQ(end, 17);
	ASSERT_EQ(next, 18);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter("This is the first line with short words", 21, 0, end, next, hyphen);
	ASSERT_EQ(end, 17);
	ASSERT_EQ(next, 18);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter("This is the first line with short words", 22, 0, end, next, hyphen);
	ASSERT_EQ(end, 22);
	ASSERT_EQ(next, 23);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter("This is the first  line with short words", 22, 0, end, next, hyphen);
	ASSERT_EQ(end, 17);
	ASSERT_EQ(next, 19);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter("This is the first  line with short words", 22, 19, end, next, hyphen);
	ASSERT_EQ(end, 40);
	ASSERT_EQ(next, 40);
	ASSERT_EQ(hyphen, false);
}

TEST__ IterativeTextSplitter2()
{
	new end, next, bool:hyphen;
	IterativeTextSplitter("This is the secondlinewithlongwords", 20, 0, end, next, hyphen);
	ASSERT_EQ(end, 19);
	ASSERT_EQ(next, 19);
	ASSERT_EQ(hyphen, true);
	IterativeTextSplitter("This is the secondlinewithlongwords", 34, 0, end, next, hyphen);
	ASSERT_EQ(end, 32);
	ASSERT_EQ(next, 32);
	ASSERT_EQ(hyphen, true);
	IterativeTextSplitter("This is the secondlinewithlongwords", 15, 0, end, next, hyphen);
	ASSERT_EQ(end, 11);
	ASSERT_EQ(next, 12);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter("This is the secondlinewithlongwords", 15, 12, end, next, hyphen);
	ASSERT_EQ(end, 26);
	ASSERT_EQ(next, 26);
	ASSERT_EQ(hyphen, true);
}

TEST__ IterativeTextSplitter3()
{
	new end, next, bool:hyphen;
	IterativeTextSplitter("This is the thirdline", 15, 0, end, next, hyphen);
	ASSERT_EQ(end, 11);
	ASSERT_EQ(next, 12);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter("This is the thirdline", 15, 12, end, next, hyphen);
	ASSERT_EQ(end, 21);
	ASSERT_EQ(next, 21);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter("This is the fourthlineisnice", 15, 0, end, next, hyphen);
	ASSERT_EQ(end, 11);
	ASSERT_EQ(next, 12);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter("This is the fourthlineisnice", 15, 12, end, next, hyphen);
	ASSERT_EQ(end, 25);
	ASSERT_EQ(next, 25);
	ASSERT_EQ(hyphen, true);
}

TEST__ IterativeTextSplitter4()
{
	new end, next, bool:hyphen;
	IterativeTextSplitter("This is the fifth\r\nand sixth\r\n\n\n\nand seventh           \n     lines", 15, 0, end, next, hyphen);
	ASSERT_EQ(end, 11);
	ASSERT_EQ(next, 12);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter("This is the fifth\r\nand sixth\r\n\n\n\nand seventh           \n     lines", 15, 12, end, next, hyphen);
	ASSERT_EQ(end, 17);
	ASSERT_EQ(next, 19);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter("This is the fifth\r\nand sixth\r\n\n\n\nand seventh           \n     lines", 15, 19, end, next, hyphen);
	ASSERT_EQ(end, 28);
	ASSERT_EQ(next, 30);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter("This is the fifth\r\nand sixth\r\n\n\n\nand seventh           \n     lines", 15, 30, end, next, hyphen);
	ASSERT_EQ(end, 30);
	ASSERT_EQ(next, 31);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter("This is the fifth\r\nand sixth\r\n\n\n\nand seventh           \n     lines", 15, 31, end, next, hyphen);
	ASSERT_EQ(end, 31);
	ASSERT_EQ(next, 32);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter("This is the fifth\r\nand sixth\r\n\n\n\nand seventh           \n     lines", 15, 32, end, next, hyphen);
	ASSERT_EQ(end, 32);
	ASSERT_EQ(next, 33);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter("This is the fifth\r\nand sixth\r\n\n\n\nand seventh           \n     lines", 15, 33, end, next, hyphen);
	ASSERT_EQ(end, 44);
	ASSERT_EQ(next, 56);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter("This is the fifth\r\nand sixth\r\n\n\n\nand seventh           \n     lines", 15, 56, end, next, hyphen);
	ASSERT_EQ(end, 66);
	ASSERT_EQ(next, 66);
	ASSERT_EQ(hyphen, false);
}

TEST__ IterativeTextSplitter5()
{
	new end, next, bool:hyphen;
	ASSERT(IterativeTextSplitter("Trying to find some worst cases       \r\n", 31, 0, end, next, hyphen));
	ASSERT_EQ(end, 31);
	ASSERT_EQ(next, 40);
	ASSERT_EQ(hyphen, false);
	ASSERT(!IterativeTextSplitter("Trying to find some worst cases       \r\n", 31, 40, end, next, hyphen));
	ASSERT_EQ(end, 40);
	ASSERT_EQ(next, 40);
	ASSERT_EQ(hyphen, false);
}

TEST__ IterativeTextSplitter6()
{
	new end, next, bool:hyphen;
	new str[] = "Generating code, this may take a little bit of time.  Note that this code generation works best with the JIT plugin, which you are not currently using.  Get it here:\n\nhttps://git.io/jit-plugin\n\nPlease wait...";
	IterativeTextSplitter(str, 38, 0, end, next, hyphen, false);
	ASSERT_EQ(end, 32);
	ASSERT_EQ(next, 33);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter(str, 38, 33, end, next, hyphen, false);
	ASSERT_EQ(end, 68);
	ASSERT_EQ(next, 69);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter(str, 38, 69, end, next, hyphen, false);
	ASSERT_EQ(end, 104);
	ASSERT_EQ(next, 105);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter(str, 38, 105, end, next, hyphen, false);
	ASSERT_EQ(end, 134);
	ASSERT_EQ(next, 135);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter(str, 38, 135, end, next, hyphen, false);
	ASSERT_EQ(end, 165);
	ASSERT_EQ(next, 166);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter(str, 38, 166, end, next, hyphen, false);
	ASSERT_EQ(end, 166);
	ASSERT_EQ(next, 167);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter(str, 38, 167, end, next, hyphen, false);
	ASSERT_EQ(end, 192);
	ASSERT_EQ(next, 193);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter(str, 38, 193, end, next, hyphen, false);
	ASSERT_EQ(end, 193);
	ASSERT_EQ(next, 194);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter(str, 38, 194, end, next, hyphen, false);
	ASSERT_EQ(end, 208);
	ASSERT_EQ(next, 208);
	ASSERT_EQ(hyphen, false);
}

TEST__ IterativeTextSplitter7()
{
	new end, next, bool:hyphen;
	new str[] = "Generating code, this may take a little bit of time.  Note that this code generation works best with the JIT plugin, which you are not currently using.  Get it here:\n\nhttps://git.io/jit-plugin\n\nPlease wait...";
	IterativeTextSplitter(str, 38, 0, end, next, hyphen);
	ASSERT_EQ(end, 32);
	ASSERT_EQ(next, 33);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter(str, 38, 33, end, next, hyphen);
	ASSERT_EQ(end, 68);
	ASSERT_EQ(next, 69);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter(str, 38, 69, end, next, hyphen);
	ASSERT_EQ(end, 104);
	ASSERT_EQ(next, 105);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter(str, 38, 105, end, next, hyphen);
	ASSERT_EQ(end, 141);
	ASSERT_EQ(next, 141);
	ASSERT_EQ(hyphen, true);
	IterativeTextSplitter(str, 38, 141, end, next, hyphen);
	ASSERT_EQ(end, 165);
	ASSERT_EQ(next, 166);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter(str, 38, 166, end, next, hyphen);
	ASSERT_EQ(end, 166);
	ASSERT_EQ(next, 167);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter(str, 38, 167, end, next, hyphen);
	ASSERT_EQ(end, 192);
	ASSERT_EQ(next, 193);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter(str, 38, 193, end, next, hyphen);
	ASSERT_EQ(end, 193);
	ASSERT_EQ(next, 194);
	ASSERT_EQ(hyphen, false);
	IterativeTextSplitter(str, 38, 194, end, next, hyphen);
	ASSERT_EQ(end, 208);
	ASSERT_EQ(next, 208);
	ASSERT_EQ(hyphen, false);
}

TEST__ IterativeColouredSkipWords1()
{
	new end, bool:hyphen, colour = 8;
	end = IterativeColouredSkipWords("alongwordwithnosymbols", 10, 0, hyphen, colour);
	ASSERT_EQ(end, 9);
	ASSERT_EQ(hyphen, true);
	ASSERT_EQ(colour, 8);
	end = IterativeColouredSkipWords("alongwordw", 10, 0, hyphen, colour);
	ASSERT_EQ(end, 10);
	ASSERT_EQ(hyphen, false);
	ASSERT_EQ(colour, 8);
	end = IterativeColouredSkipWords("alongwordwi", 10, 0, hyphen, colour);
	ASSERT_EQ(end, 8);
	ASSERT_EQ(hyphen, true);
	ASSERT_EQ(colour, 8);
	end = IterativeColouredSkipWords("alongwordwit", 10, 0, hyphen, colour);
	ASSERT_EQ(end, 9);
	ASSERT_EQ(hyphen, true);
	ASSERT_EQ(colour, 8);
	end = IterativeColouredSkipWords("alongwordwith", 10, 0, hyphen, colour);
	ASSERT_EQ(end, 9);
	ASSERT_EQ(hyphen, true);
	ASSERT_EQ(colour, 8);
}

TEST__ IterativeColouredSkipWords2()
{
	new end, bool:hyphen, colour = 8;
	end = IterativeColouredSkipWords("{000000}longword", 10, 0, hyphen, colour);
	ASSERT_EQ(end, 0);
	ASSERT_EQ(hyphen, false);
	ASSERT_EQ(colour, 0);
	colour = 9;
	end = IterativeColouredSkipWords("long{000000}word", 10, 0, hyphen, colour);
	ASSERT_EQ(end, 4);
	ASSERT_EQ(hyphen, true);
	ASSERT_EQ(colour, 9);
	colour = 7;
	end = IterativeColouredSkipWords("longg{000000}word", 10, 0, hyphen, colour);
	ASSERT_EQ(end, 5);
	ASSERT_EQ(hyphen, true);
	ASSERT_EQ(colour, 7);
	colour = 6;
	end = IterativeColouredSkipWords("longg{000000}wo", 10, 0, hyphen, colour);
	ASSERT_EQ(end, 4);
	ASSERT_EQ(hyphen, true);
	ASSERT_EQ(colour, 6);
	colour = 5;
	end = IterativeColouredSkipWords("longgg{000000}w", 10, 0, hyphen, colour);
	ASSERT_EQ(end, 4);
	ASSERT_EQ(hyphen, true);
	ASSERT_EQ(colour, 5);
}

TEST__ IterativeColouredSkipWords3()
{
	new end, bool:hyphen, colour = 8;
	end = IterativeColouredSkipWords("abcdefg   {000000}longword", 20, 10, hyphen, colour);
	ASSERT_EQ(end, 10);
	ASSERT_EQ(hyphen, false);
	ASSERT_EQ(colour, 0);
	colour = 9;
	end = IterativeColouredSkipWords("abcdefg   long{000000}word", 20, 10, hyphen, colour);
	ASSERT_EQ(end, 14);
	ASSERT_EQ(hyphen, true);
	ASSERT_EQ(colour, 9);
	colour = 7;
	end = IterativeColouredSkipWords("abcdefg   longg{000000}word", 20, 10, hyphen, colour);
	ASSERT_EQ(end, 15);
	ASSERT_EQ(hyphen, true);
	ASSERT_EQ(colour, 7);
	colour = 6;
	end = IterativeColouredSkipWords("abcdefg   longg{000000}wo", 20, 10, hyphen, colour);
	ASSERT_EQ(end, 14);
	ASSERT_EQ(hyphen, true);
	ASSERT_EQ(colour, 6);
	colour = 5;
	end = IterativeColouredSkipWords("abcdefg   longgg{000000}w", 20, 10, hyphen, colour);
	ASSERT_EQ(end, 14);
	ASSERT_EQ(hyphen, true);
	ASSERT_EQ(colour, 5);
}

TEST__ IterativeColouredSkipWS1()
{
	new end, colour = 8;
	end = IterativeColouredSkipWhitespace("    hi", 0, colour);
	ASSERT_EQ(end, 4);
	ASSERT_EQ(colour, 8);
	colour = 9;
	end = IterativeColouredSkipWhitespace("  \n  hi", 0, colour);
	ASSERT_EQ(end, 2);
	ASSERT_EQ(colour, 9);
	colour = 7;
	end = IterativeColouredSkipWhitespace("    hi", 0, colour);
	ASSERT_EQ(end, 4);
	ASSERT_EQ(colour, 7);
	colour = 5;
	end = IterativeColouredSkipWhitespace(" {112233}   hi", 0, colour);
	ASSERT_EQ(end, 12);
	ASSERT_EQ(colour, 0x112233);
}

TEST__ IterativeColouredText1()
{
	new end, next, bool:hyphen, colour;
	new str[] = "Hello, I'm just splitting a string normally.";
	colour = 33;
	IterativeColouredTextSplitter(str, 20, 0, end, next, hyphen, colour);
	ASSERT_EQ(end, 19);
	ASSERT_EQ(next, 19);
	ASSERT_EQ(colour, 33);
	ASSERT(hyphen);
	colour = 32;
	IterativeColouredTextSplitter(str, 20, 19, end, next, hyphen, colour);
	ASSERT_EQ(end, 38);
	ASSERT_EQ(next, 38);
	ASSERT_EQ(colour, 32);
	ASSERT(hyphen);
	colour = 31;
	IterativeColouredTextSplitter(str, 20, 38, end, next, hyphen, colour);
	ASSERT_EQ(end, 44);
	ASSERT_EQ(next, 44);
	ASSERT_EQ(colour, 31);
	ASSERT(!hyphen);
}

TEST__ IterativeColouredText2()
{
	new end, next, bool:hyphen, colour;
	new str[] = "Hello, {FFAA11}I'm just splitting a string normally.";
	colour = 33;
	IterativeColouredTextSplitter(str, 20, 0, end, next, hyphen, colour);
	ASSERT_EQ(end, 18);
	ASSERT_EQ(next, 19);
	ASSERT_EQ(colour, 0xFFAA11);
	ASSERT(!hyphen);
	colour = 32;
	IterativeColouredTextSplitter(str, 20, 19, end, next, hyphen, colour);
	ASSERT_EQ(end, 35);
	ASSERT_EQ(next, 36);
	ASSERT_EQ(colour, 32);
	ASSERT(!hyphen);
	colour = 31;
	IterativeColouredTextSplitter(str, 20, 36, end, next, hyphen, colour);
	ASSERT_EQ(end, 52);
	ASSERT_EQ(next, 52);
	ASSERT_EQ(colour, 31);
	ASSERT(!hyphen);
}

TEST__ IterativeColouredText3()
{
	new end, next, bool:hyphen, colour;
	new str[] = "Hello, {FFAA11}I'm      just {123456}splitting a string normally.";
	colour = 33;
	IterativeColouredTextSplitter(str, 20, 0, end, next, hyphen, colour);
	ASSERT_EQ(end, 18);
	ASSERT_EQ(next, 24);
	ASSERT_EQ(colour, 0xFFAA11);
	ASSERT(!hyphen);
	colour = 32;
	IterativeColouredTextSplitter(str, 20, 24, end, next, hyphen, colour);
	ASSERT_EQ(end, 43);
	ASSERT_EQ(next, 43);
	ASSERT_EQ(colour, 0x123456);
	ASSERT(hyphen);
	colour = 31;
	IterativeColouredTextSplitter(str, 20, 43, end, next, hyphen, colour);
	ASSERT_EQ(end, 61);
	ASSERT_EQ(next, 61);
	ASSERT_EQ(colour, 31);
	ASSERT(hyphen);
	colour = 30;
	IterativeColouredTextSplitter(str, 20, 61, end, next, hyphen, colour);
	ASSERT_EQ(end, 65);
	ASSERT_EQ(next, 65);
	ASSERT_EQ(colour, 30);
	ASSERT(!hyphen);
}

