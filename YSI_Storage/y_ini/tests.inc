Test:INI_IdentifyLineType1()
{
	// Comment lines and blank lines may as well be treated as the same thing,
	// except when rewriting the file.
	new p0s, p0e, p1s, p1e, p2s, p2e;
	// Comment lines.
	ASSERT(INI_IdentifyLineType("; Hello", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType("   ; There", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType("	; Hi", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType(";", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType(";\r\n", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType("\\;\r\n", p0s, p0e, p1s, p1e, p2s, p2e) != e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType("hi ; there", p0s, p0e, p1s, p1e, p2s, p2e) != e_INI_LINE_TYPE_BLANK);
	// Blank lines.
	ASSERT(INI_IdentifyLineType("", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType("    ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType("	\r\n", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType("\r\n", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_BLANK);
}

Test:INI_IdentifyLineType2()
{
	new p0s, p0e, p1s, p1e, p2s, p2e;
	// Invalid lines.
	new
		e_INI_LINE_TYPE:result;
	result = INI_IdentifyLineType("[badtag", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("   [tag", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("   [   ]", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("[tag;end]", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("[tag\\;end]", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result != e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType(" [tag\\]", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType(" [tag\\\\]", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result != e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("key", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("key\\=", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("key\\\\\\=value", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("\\;\r\n", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("key =  ", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result == e_INI_LINE_TYPE_ENTRY); // Now allowed again!
	result = INI_IdentifyLineType(" = value", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("thing", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("thing ; comment", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
}

Test:INI_IdentifyLineType3()
{
	new p0s, p0e, p1s, p1e, p2s, p2e;
	// Entry lines.
	ASSERT(INI_IdentifyLineType("key = value", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("key=value", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 4 && p1e == 9 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("key = value ; comment", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	//printf("%d %d %d %d %d %d", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == 14 && p2e == 21);
	ASSERT(INI_IdentifyLineType("key = value ;   comment\r\n", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == 16 && p2e == 23);
	ASSERT(INI_IdentifyLineType("key =  value   ; com ment  \r\n", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 7 && p1e == 12 && p2s == 17 && p2e == 25);
	ASSERT(INI_IdentifyLineType("key = value\r\n", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("key	=value", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 5 && p1e == 10 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("   key=	value", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 3 && p0e == 6 && p1s == 8 && p1e == 13 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("   key=	value    ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 3 && p0e == 6 && p1s == 8 && p1e == 13 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("	key   =value  ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 1 && p0e == 4 && p1s == 8 && p1e == 13 && p2s == p2e);
}

Test:INI_IdentifyLineType4()
{
	new p0s, p0e, p1s, p1e, p2s, p2e;
	// Tag lines.
	ASSERT(INI_IdentifyLineType("[hello]", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType(" [hello] ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 2 && p0e == 7 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType(" [ hello] ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 3 && p0e == 8 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType(" [hello ] ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 2 && p0e == 7 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType("[ hello] ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 2 && p0e == 7 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType("[hello ]", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType("[hello   ]", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType("[   hello ]", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	// printf("%d %d %d %d %d %d", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(p0s == 4 && p0e == 9 && p1s == p1e && p2s == p2e);
}

Test:INI_IdentifyLineType5()
{
	new p0s, p0e, p1s, p1e, p2s, p2e;
	// Inheritance.
	ASSERT(INI_IdentifyLineType("[hello] : ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_INVALID);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType("[hello] : first", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == 10 && p1e == 15 && p2s == p2e);
	// ASSERT(INI_IdentifyLineType("[hello] : first, second", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 10 && p1e == 23 && p2s == p2e);
	// ASSERT(INI_IdentifyLineType("[hello]   : first, second     ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 12 && p1e == 25 && p2s == p2e);
	// ASSERT(INI_IdentifyLineType("[hello] :    first, second   ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 13 && p1e == 26 && p2s == p2e);
	// These used to work, now they don't.
	ASSERT(INI_IdentifyLineType("[hello] : first, second", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_INVALID);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 10 && p1e == 23 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("[hello]   : first, second     ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_INVALID);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 12 && p1e == 25 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("[hello] :    first, second   ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_INVALID);
	// ASSERT(p0s == 1 && p0e == 6 && p1s == 13 && p1e == 26 && p2s == p2e);
	// Commented out.
	ASSERT(INI_IdentifyLineType("[hello] ;: ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == 9 && p2e == 10);
	ASSERT(INI_IdentifyLineType("[hello] ; : first, second ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == 10 && p2e == 25);
	// printf("%d %d %d %d %d %d", p0s, p0e, p1s, p1e, p2s, p2e);
	// Both.
	ASSERT(INI_IdentifyLineType(" [ hello ]  :  inheritance  ;  : first, second ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 3 && p0e == 8 && p1s == 15 && p1e == 26 && p2s == 31 && p2e == 46);
	// printf("%d %d %d %d %d %d", p0s, p0e, p1s, p1e, p2s, p2e);
}

// Test:INI_IdentifyLineType6()
// {
	// new p0s, p0e, p1s, p1e, p2s, p2e, bool:;;
	// // Continuation.
	// new
		// e_INI_LINE_TYPE:result;
	// cont = false;
	// result = INI_IdentifyLineType("hi = there\\ ", p0s, p0e, p1s, p1e, p2s, p2e);
	// ASSERT(result == e_INI_LINE_TYPE_ENTRY);
	// //printf("%d %d %d %d %d %d", p0s, p0e, p1s, p1e, p2s, p2e);
	// ASSERT(p0s == 0 && p1e == 10);
	// ASSERT(cont);
	// cont = false;
	// ASSERT(INI_IdentifyLineType("hi = there  \\   ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	// ASSERT(p0s == 0 && p1e == 10);
	// ASSERT(cont);
	// cont = false;
	// ASSERT(INI_IdentifyLineType("hi =    \\   ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	// ASSERT(p0s == 0 && p0e == 2);
	// ASSERT(p1s == p1e);
	// ASSERT(cont);
	// cont = true;
	// ASSERT(INI_IdentifyLineType("hello there ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_CONT);
	// ASSERT(p0s == p0e && p1s == 0 && p1e == 11);
	// ASSERT(!cont);
	// cont = true;
	// ASSERT(INI_IdentifyLineType("hello there \\  ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_CONT);
	// ASSERT(p0s == p0e && p1s == 0 && p1e == 11);
	// ASSERT(cont);
	// cont = true;
	// result = INI_IdentifyLineType("   \\", p0s, p0e, p1s, p1e, p2s, p2e);
	// ASSERT(result == e_INI_LINE_TYPE_CONT);
	// ASSERT(cont);
	// ASSERT(p0s == p0e && p1s == p1e);
// }

Test:INI_IdentifyLineType6()
{
	new p0s, p0e, p1s, p1e, p2s, p2e;
	// Continuation.
	new
		e_INI_LINE_TYPE:result;
	result = INI_IdentifyLineType("hi = there\\ ", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(result == e_INI_LINE_TYPE_ENTRY);
	//printf("%d %d %d %d %d %d", p0s, p0e, p1s, p1e, p2s, p2e);
	ASSERT(p0s == 0 && p1e == 12);
	// ASSERT(cont);
	ASSERT(INI_IdentifyLineType("hi = there  \\   ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p1e == 14);
	// ASSERT(cont);
	ASSERT(INI_IdentifyLineType("hi =    \\   ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 2);
	// ASSERT(p1s == p1e);
	ASSERT(p1s == 8 && p1e == 10);
	// ASSERT(cont);
	// cont = true;
	ASSERT(INI_IdentifyLineType("hello there ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_INVALID);
	// ASSERT(p0s == p0e && p1s == 0 && p1e == 11);
	// cont = true;
	ASSERT(INI_IdentifyLineType("hello there \\  ", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_INVALID);
	// ASSERT(p0s == p0e && p1s == 0 && p1e == 11);
	// ASSERT(cont);
	// cont = true;
	// result = INI_IdentifyLineType("   \\", p0s, p0e, p1s, p1e, p2s, p2e);
	// ASSERT(result == e_INI_LINE_TYPE_CONT);
	// // ASSERT(cont);
	// ASSERT(p0s == p0e && p1s == p1e);
}

Test:Trim1()
{
	new start, end;
	start = 0, end = 9;
	Trim("  hello  ", start, end);
	ASSERT(start == 2);
	ASSERT(end == 7);
	start = 0, end = 9;
	Trim("         ", start, end);
	ASSERT(start == 9);
	ASSERT(end == 9);
	start = 6, end = 13;
	Trim(" hello there ", start, end);
	ASSERT(start == 7);
	ASSERT(end == 12);
	start = 0, end = 13;
	Trim("hello there ", start, end);
	ASSERT(start == 0);
	ASSERT(end == 11);
}

Test:INI_SetupCallbackName0()
{
	new
		dest[32];
	INI_SetupCallbackName(dest, "%s", "", false);
	ASSERT(!strcmp(dest, "%s"));
	INI_SetupCallbackName(dest, "%s", "", true);
	ASSERT(dest[0] == '\0');
	INI_SetupCallbackName(dest, "%s", "fname", true);
	ASSERT(!strcmp(dest, "fname"));
	INI_SetupCallbackName(dest, "hello%sthere", "", false);
	ASSERT(!strcmp(dest, "hello%sthere"));
	INI_SetupCallbackName(dest, "hello%sthere", "", true);
	ASSERT(!strcmp(dest, "hellothere"));
	INI_SetupCallbackName(dest, "how%sare%syou", "", false);
	ASSERT(!strcmp(dest, "how%sareyou"));
	INI_SetupCallbackName(dest, "how%sare%syou", "", true);
	ASSERT(!strcmp(dest, "howare%syou"));
	INI_SetupCallbackName(dest, "hello%sthere", "fname", false);
	ASSERT(!strcmp(dest, "hello%sthere"));
	INI_SetupCallbackName(dest, "hello%sthere", "fname", true);
	ASSERT(!strcmp(dest, "hellofnamethere"));
	INI_SetupCallbackName(dest, "how%sare%syou", "fname", false);
	ASSERT(!strcmp(dest, "how%sarefnameyou"));
	INI_SetupCallbackName(dest, "how%sare%syou", "fname", true);
	ASSERT(!strcmp(dest, "howfnameare%syou"));
	INI_SetupCallbackName(dest, "foobar", "fname", true);
	ASSERT(!strcmp(dest, "foobar"));
	INI_SetupCallbackName(dest, "foobar", "fname", false);
	ASSERT(!strcmp(dest, "foobar"));
	INI_SetupCallbackName(dest, "%s%s", "fname", true);
	ASSERT(!strcmp(dest, "fname%s"));
	INI_SetupCallbackName(dest, "%s%s", "fname", false);
	ASSERT(!strcmp(dest, "%sfname"));
}

Test:INI_SetupCallbackName1()
{
	new
		dest[32];
	INI_SetupCallbackName(dest, "%s", "hi/there", false);
	ASSERT(!strcmp(dest, "%s"));
	INI_SetupCallbackName(dest, "%s", "hi/there", true);
	ASSERT(!strcmp(dest, "there"));
	INI_SetupCallbackName(dest, "%s%s", "hi/there", false);
	ASSERT(!strcmp(dest, "%sthere"));
	INI_SetupCallbackName(dest, "%s%s", "hi/there.txt", false);
	ASSERT(!strcmp(dest, "%sthere"));
	INI_SetupCallbackName(dest, "%s%s", "hi/there", true);
	ASSERT(!strcmp(dest, "there%s"));
	INI_SetupCallbackName(dest, "%s%s", "hi/there.txt", true);
	ASSERT(!strcmp(dest, "there%s"));
}

Test:INI_SetupCallbackName2()
{
	new
		dest[32];
	INI_SetupCallbackName(dest, "%s", "hi/there you", false);
	ASSERT(!strcmp(dest, "%s"));
	INI_SetupCallbackName(dest, "%s", "hi/there you", true);
	ASSERT(!strcmp(dest, "there_you"));
	INI_SetupCallbackName(dest, "%s%s", "hi/there you", false);
	ASSERT(!strcmp(dest, "%sthere_you"));
	INI_SetupCallbackName(dest, "%s%s", "hi/there you.txt", false);
	ASSERT(!strcmp(dest, "%sthere_you"));
	INI_SetupCallbackName(dest, "%s%s", "hi/there you", true);
	ASSERT(!strcmp(dest, "there_you%s"));
	INI_SetupCallbackName(dest, "%s%s", "hi/there you.txt", true);
	ASSERT(!strcmp(dest, "there_you%s"));
}

Test:INI_SetupCallbackName3()
{
	new
		dest[32];
	INI_SetupCallbackName(dest, "%s%s", "one/two/three/hello_there you.some.ini", false);
	ASSERT(!strcmp(dest, "%shello_there_you"));
	INI_SetupCallbackName(dest, "%s%s", "one\\two\\three\\four.five.six", false);
	// My first conditional assertation.
	if (IsWindows()) ASSERT(!strcmp(dest, "%sfour"));
	else ASSERT(!strcmp(dest, "%sone"));
}

static stock
	YSI_g_sINI_Parse0;

forward TestINI_Parse0_test1(key[], value[]);

public TestINI_Parse0_test1(key[], value[])
{
	//printf("called");
	++YSI_g_sINI_Parse0;
}

Test:INI_Parse0()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s", .bFileFirst = true);
	ASSERT(YSI_g_sINI_Parse0 == 10 && 1);
	if (IsWindows())
	{
		YSI_g_sINI_Parse0 = 0;
		INI_ParseFile("YSI\\test_ini\\test1.ini", "TestINI_Parse0_%s", .bFileFirst = true);
		ASSERT(YSI_g_sINI_Parse0 == 10 && 2);
	}
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s", .bFileFirst = true, .bFilter = true, .filter = "unf");
	ASSERT(YSI_g_sINI_Parse0 == 8 && 3);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s", .bFileFirst = true, .bFilter = true, .filter = "filter");
	ASSERT(YSI_g_sINI_Parse0 == 10 && 4);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s%s", .bFileFirst = true, .bFilter = true, .filter = "filter");
	ASSERT(YSI_g_sINI_Parse0 == 5 && 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s%s", .bFileFirst = false, .bFilter = true, .filter = "filter");
	ASSERT(YSI_g_sINI_Parse0 == 5 && 6);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s", .bFileFirst = true, .bFilter = false, .filter = "unf");
	ASSERT(YSI_g_sINI_Parse0 == 10 && 7);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s", .bFileFirst = true, .bFilter = false, .filter = "filter");
	ASSERT(YSI_g_sINI_Parse0 == 10 && 8);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s%s", .bFileFirst = true, .bFilter = false, .filter = "filter");
	ASSERT(YSI_g_sINI_Parse0 == 5 && 9);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse0_%s%s", .bFileFirst = false, .bFilter = false, .filter = "filter");
	ASSERT(YSI_g_sINI_Parse0 == 5 && 10);
}

forward TestINI_Parse1_test1_(key[], value[]);

public TestINI_Parse1_test1_(key[], value[])
{
	++YSI_g_sINI_Parse0;
}

Test:INI_Parse1()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse1_%s_%s", .bFileFirst = true);
	ASSERT(YSI_g_sINI_Parse0 == 5);
}

forward TestINI_Parse2_test1_(key[], value[]);

public TestINI_Parse2_test1_(key[], value[])
{
	++YSI_g_sINI_Parse0;
}

forward TestINI_Parse2_test1_tag2(key[], value[]);

public TestINI_Parse2_test1_tag2(key[], value[])
{
	++YSI_g_sINI_Parse0;
}

Test:INI_Parse2()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse2_%s_%s", .bFileFirst = true);
	ASSERT(YSI_g_sINI_Parse0 == 7);
}

forward TestINI_Parse3__test1(key[], value[]);

public TestINI_Parse3__test1(key[], value[])
{
	++YSI_g_sINI_Parse0;
}

forward TestINI_Parse3_atag_test1(key[], value[]);

public TestINI_Parse3_atag_test1(key[], value[])
{
	++YSI_g_sINI_Parse0;
}

forward TestINI_Parse3_tag2_test1(key[], value[]);

public TestINI_Parse3_tag2_test1(key[], value[])
{
	++YSI_g_sINI_Parse0;
}

Test:INI_Parse3()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false);
	ASSERT(YSI_g_sINI_Parse0 == 10 && 1);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = true, .filter = "filter");
	ASSERT(YSI_g_sINI_Parse0 == 10 && 2);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = true, .filter = "other");
	ASSERT(YSI_g_sINI_Parse0 == 8 && 3);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = false, .filter = "filter");
	ASSERT(YSI_g_sINI_Parse0 == 10 && 4);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = false, .filter = "other");
	ASSERT(YSI_g_sINI_Parse0 == 10 && 5);
}

Test:INI_Parse4()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false, .bLocal = false);
	ASSERT(YSI_g_sINI_Parse0 == 10 && 1);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = true, .filter = "filter", .bLocal = false);
	ASSERT(YSI_g_sINI_Parse0 == 10 && 2);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = true, .filter = "other", .bLocal = false);
	ASSERT(YSI_g_sINI_Parse0 == 8 && 3);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = false, .filter = "filter", .bLocal = false);
	ASSERT(YSI_g_sINI_Parse0 == 10 && 4);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse3_%s_%s", .bFileFirst = false, .bFilter = false, .filter = "other", .bLocal = false);
	ASSERT(YSI_g_sINI_Parse0 == 10 && 5);
}

// Test passing the tag.

forward TestINI_Parse5_test1(tag[], key[], value[]);

public TestINI_Parse5_test1(tag[], key[], value[])
{
	if (isnull(tag)) ++YSI_g_sINI_Parse0;
}

Test:INI_Parse5()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true);
	ASSERT(YSI_g_sINI_Parse0 == 5 && 1);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = true, .filter = "filter");
	ASSERT(YSI_g_sINI_Parse0 == 5 && 2);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = true, .filter = "other");
	ASSERT(YSI_g_sINI_Parse0 == 5 && 3);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = false);
	ASSERT(YSI_g_sINI_Parse0 == 5 && 4);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = false);
	ASSERT(YSI_g_sINI_Parse0 == 5 && 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s%s", .bFileFirst = true, .bPassTag = true, .bFilter = false);
	ASSERT(YSI_g_sINI_Parse0 == 5 && 5);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_%sParse5_%s", .bFileFirst = false, .bPassTag = true, .bFilter = false);
	ASSERT(YSI_g_sINI_Parse0 == 5 && 5);
}

Test:INI_Parse6()
{
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bLocal = false);
	ASSERT(YSI_g_sINI_Parse0 == 5 && 1);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = true, .filter = "filter", .bLocal = false);
	ASSERT(YSI_g_sINI_Parse0 == 5 && 2);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = true, .filter = "other", .bLocal = false);
	ASSERT(YSI_g_sINI_Parse0 == 5 && 3);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = false, .bLocal = false);
	ASSERT(YSI_g_sINI_Parse0 == 5 && 4);
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "TestINI_Parse5_%s", .bFileFirst = true, .bPassTag = true, .bFilter = false, .bLocal = false);
	ASSERT(YSI_g_sINI_Parse0 == 5 && 5);
}

Test:INI_Parse7()
{
	inline const F_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		YSI_g_sINI_Parse0 += 1;
	}
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "F_%s", .bFileFirst = true);
	ASSERT(YSI_g_sINI_Parse0 == 10 && 1);
}

Test:INI_Parse8()
{
	inline F_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		YSI_g_sINI_Parse0 += 2;
	}
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "F_%s", .bFileFirst = true);
	ASSERT(YSI_g_sINI_Parse0 == 20 && 1);
}

Test:INI_Parse9()
{
	inline const F_atag_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		YSI_g_sINI_Parse0 += 3;
	}
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "F_%s_%s");
	ASSERT(YSI_g_sINI_Parse0 == 9 && 1);
}

Test:INI_Parse10()
{
	inline const F_tag2_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		YSI_g_sINI_Parse0 += 4;
	}
	YSI_g_sINI_Parse0 = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "F_%s_%s");
	ASSERT(YSI_g_sINI_Parse0 == 8 && 1);
}

Test:INI_Parse11()
{
	new
		a;
	inline const F_tag2_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		a += 4;
	}
	a = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "F_%s_%s");
	ASSERT(a == 0 && 1);
}

Test:INI_Parse12()
{
	static
		a;
	inline const F_tag2_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		a += 4;
	}
	a = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "F_%s_%s");
	ASSERT(a == 8 && 1);
}

Test:INI_Parse13()
{
	new
		a;
	inline F_tag2_test1(string:key[], string:value[])
	{
		#pragma unused key, value
		a += 4;
	}
	a = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "F_%s_%s");
	ASSERT(a == 8 && 1);
}

Test:INI_ParseInline()
{
	new
		num,
		ret;
	inline Inline1(string:key[], string:value[])
	{
		#pragma unused key, value
		++num;
	}
	num = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "Inline1", .bFilter = true, .filter = "other");
	ASSERT(num == 8);
	// This line also seems to have the -O1 -d0 bug.  It must be caused by the
	// extra "tag" parameter somehow...
	inline Inline2(string:tag[], string:key[], string:value[])
	{
		#pragma unused key, value
		if (isnull(tag)) ++num;
	}
	num = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "Inline2", .bFilter = true, .filter = "other", .bPassTag = true);
	ASSERT(num == 5);
	inline Inline3(extra, string:key[], string:value[])
	{
		#pragma unused key, value
		num += extra;
	}
	num = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "Inline3%s", .bExtra = true, .extra = 11);
	ASSERT(num == 55);
	inline Inline4(extra, string:tag[], string:key[], string:value[])
	{
		#pragma unused key, value
		ret = extra;
		if (!isnull(tag) && !strcmp(tag, "tag2")) ++num;
	}
	ret = 0;
	num = 0;
	INI_ParseFile("YSI/test_ini/test1.ini", "Inline4", .bPassTag = true, .bExtra = true, .extra = 42);
	ASSERT(num == 2);
	ASSERT(ret == 42);
}

Test:INI_Int0()
{
	DoINI_Int0();
}

static stock DoINI_Int0()
{
	new
		k0,
		k1,
		k2,
		k3,
		k4;
	inline Inl_(string:name[], string:value[])
	{
		INI_Int("key0", k0);
		INI_Int("key1", k1);
		INI_Int("key2", k2);
		INI_Int("key3", k3);
		INI_Int("key4", k4);
	}
	INI_ParseFile("YSI/test_ini/test1.ini", "Inl_%s");
	ASSERT(k0 == 42);
	ASSERT(k1 == 43);
	ASSERT(k2 == 45);
	ASSERT(k3 == 47);
	ASSERT(k4 == 46);
	return 0;
}

Test:INI_Int2()
{
	DoINI_Int2();
}

static stock DoINI_Int2()
{
	new
		k0,
		k1,
		k2,
		k3,
		k4;
	inline const Inl_(string:name[], string:value[])
	{
		INI_Int("key0", k0);
		INI_Int("key1", k1);
		INI_Int("key2", k2);
		INI_Int("key3", k3);
		INI_Int("key4", k4);
	}
	INI_ParseFile("YSI/test_ini/test1.ini", "Inl_%s");
	ASSERT(k0 == 0);
	ASSERT(k1 == 0);
	ASSERT(k2 == 0);
	ASSERT(k3 == 0);
	ASSERT(k4 == 0);
	return 0;
}

Test:INI_Int3()
{
	DoINI_Int3();
}

static stock DoINI_Int3()
{
	new
		k0,
		k1,
		k2,
		k3,
		k4;
	new
		sk0[8],
		Float:sk1,
		bool:sk2 = true;
	new
		tk0[8],
		tk1[8];
	inline Inl_(string:tag[], string:name[], string:value[])
	{
		// #emit NOP
		// #emit NOP
		// #emit NOP
		// #emit NOP
		// printf("%s (%d): %d %d %d", tag, YHash(tag, false),
			// _I<>,
			// _I<atag>,
			// _I<tag2>);
		// TODO:  I think there's a bug in here somewhere, with "GTYPE=0 MTYPE=1
		// -O1 -d0", which crashes on ENTRY to this inlineю  I think that the
		// problem may be too much, or incorrect, code being output.
		switch (YHash(tag, false))
		{
			case _I<>:
			{
				INI_Int("key0", k0);
				INI_Int("key1", k1);
				INI_Int("key2", k2);
				INI_Int("key3", k3);
				INI_Int("key4", k4);
			}
			case _I<atag>:
			{
				INI_String("key0", sk0);
				INI_Float("otherKey", sk1);
				INI_Bool("myKey", sk2);
			}
			case _I<tag2>:
			{
				INI_String("filtered1", tk0);
				INI_String("filtered2", tk1);
			}
		}
	}
	INI_ParseFile("YSI/test_ini/test1.ini", "Inl_", .bPassTag = true);
	// First.
	ASSERT(k0 == 42);
	ASSERT(k1 == 43);
	ASSERT(k2 == 45);
	ASSERT(k3 == 47);
	ASSERT(k4 == 46);
	// Second.
	ASSERT(!isnull(sk0) && !strcmp(sk0, "hello"));
	ASSERT(sk1 == 5.5);
	ASSERT(!sk2);
	// Third.
	ASSERT(!isnull(tk0) && !strcmp(tk0, "yes"));
	ASSERT(!isnull(tk1) && !strcmp(tk1, "no"));
	return 0;
}

static stock
	gs_K0,
	gs_K1,
	gs_K2,
	gs_K3,
	gs_K4,
	gs_K5;

forward INI_PUB_Inl_(string:name[], string:value[]);

public INI_PUB_Inl_(string:name[], string:value[])
{
	INI_Int("key0", gs_K0);
	INI_Int("key1", gs_K1);
	INI_Int("key2", gs_K2);
	INI_Int("key3", gs_K3);
	INI_Int("key4", gs_K4);
	return 0;
}

Test:INI_Int1()
{
	INI_ParseFile("YSI/test_ini/test1.ini", "INI_PUB_Inl_%s");
	ASSERT(gs_K0 == 42);
	ASSERT(gs_K1 == 43);
	ASSERT(gs_K2 == 45);
	ASSERT(gs_K3 == 47);
	ASSERT(gs_K4 == 46);
}

forward INI_Inher0_tag0(string:tag[], string:name[], string:value[]);

public INI_Inher0_tag0(string:tag[], string:name[], string:value[])
{
	ASSERT(!isnull(tag) && !strcmp(tag, "tag0"));
	INI_Int("key0", gs_K0);
	INI_Int("key1", gs_K1);
	INI_Int("key2", gs_K2);
	INI_Int("key3", gs_K3);
	INI_Int("key4", gs_K4);
	INI_Int("key5", gs_K5);
	return 0;
}

Test:INI_Inherit0()
{
	gs_K0 = 0;
	gs_K1 = 0;
	gs_K2 = 0;
	gs_K3 = 0;
	gs_K4 = 0;
	gs_K5 = 0;
	INI_ParseFile("YSI/test_ini/test2.ini", "INI_Inher0_%s", .bPassTag = true);
	ASSERT(gs_K0 == 101);
	ASSERT(gs_K1 == 102);
	ASSERT(gs_K2 ==   0);
	ASSERT(gs_K3 ==   0);
	ASSERT(gs_K4 ==   0);
	ASSERT(gs_K5 ==   0);
}

forward INI_Inher1_tag1(string:tag[], string:name[], string:value[]);

public INI_Inher1_tag1(string:tag[], string:name[], string:value[])
{
	ASSERT(!isnull(tag) && !strcmp(tag, "tag1"));
	INI_Int("key0", gs_K0);
	INI_Int("key1", gs_K1);
	INI_Int("key2", gs_K2);
	INI_Int("key3", gs_K3);
	INI_Int("key4", gs_K4);
	INI_Int("key5", gs_K5);
	return 0;
}

Test:INI_Inherit1()
{
	gs_K0 = 0;
	gs_K1 = 0;
	gs_K2 = 0;
	gs_K3 = 0;
	gs_K4 = 0;
	gs_K5 = 0;
	INI_ParseFile("YSI/test_ini/test2.ini", "INI_Inher1_%s", .bPassTag = true);
	ASSERT(gs_K0 == 101);
	ASSERT(gs_K1 == 102);
	ASSERT(gs_K2 == 103);
	ASSERT(gs_K3 == 104);
	ASSERT(gs_K4 ==   0);
	ASSERT(gs_K5 ==   0);
}

forward INI_Inher2_tag2(string:tag[], string:name[], string:value[]);

public INI_Inher2_tag2(string:tag[], string:name[], string:value[])
{
	ASSERT(!isnull(tag) && !strcmp(tag, "tag2"));
	INI_Int("key0", gs_K0);
	INI_Int("key1", gs_K1);
	INI_Int("key2", gs_K2);
	INI_Int("key3", gs_K3);
	INI_Int("key4", gs_K4);
	INI_Int("key5", gs_K5);
	return 0;
}

Test:INI_Inherit2()
{
	gs_K0 = 0;
	gs_K1 = 0;
	gs_K2 = 0;
	gs_K3 = 0;
	gs_K4 = 0;
	gs_K5 = 0;
	INI_ParseFile("YSI/test_ini/test2.ini", "INI_Inher2_%s", .bPassTag = true);
	ASSERT(gs_K0 == 107);
	ASSERT(gs_K1 == 102);
	ASSERT(gs_K2 == 103);
	ASSERT(gs_K3 == 104);
	ASSERT(gs_K4 == 105);
	ASSERT(gs_K5 == 106);
}

// Writing tests.

Test:INI_AddToBuffer0()
{
	new
		INI:i = INI_Open("YSI/test_ini/test3.ini");
	ASSERT(i != INI_NO_FILE);
	ASSERT(INI_AddToBuffer(i, "", "hi") == -1);
	ASSERT(INI_AddToBuffer(INI_NO_FILE, "foo", "bar") == -1);
	ASSERT(INI_AddToBuffer(i, "key", "value") != -1);
	new
		s = INI_AddToBuffer(i, "first", "second");
	ASSERT(s != -1);
	ASSERT(INI_AddToBuffer(i, "first", "third") == s);
	ASSERT(INI_AddToBuffer(i, "first", "fourth") == s);
	ASSERT(INI_AddToBuffer(i, "first", "fifth") == s);
	INI_Close(i);
}

Test:INI_AddToBuffer1()
{
	new
		INI:i = INI_Open("YSI/test_ini/test4.ini");
	new
		s = INI_AddToBuffer(i, "key2", "value2");
	ASSERT(s != -1);
	INI_SetTag(i, "tag0");
	ASSERT(INI_AddToBuffer(i, "key2", "value3") != s);
	ASSERT(INI_AddToBuffer(i, "key2", "value4") != -1);
	INI_DeleteTag(i, "tag0");
	ASSERT(INI_AddToBuffer(i, "key2", "value5") == -1);
	INI_Close(i);
}

Test:INI_VariousWriting0()
{
	new
		INI:i = INI_Open("YSI/test_ini/test5.ini");
	new
		s = INI_AddToBuffer(i, "writing", "written");
	ASSERT(s != -1);
	ASSERT(!strcmp("writing", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("written", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	new
		t = YSI_g_sINICurrentTag[i];
	ASSERT(!strcmp("\1\0", YSI_g_sINITagBuffer[t][E_INI_TAGS_NAME], true));
	ASSERT(YSI_g_sINITagBuffer[t][E_INI_TAGS_START] == s);
	ASSERT(YSI_g_sINITagBuffer[t][E_INI_TAGS_NEXT] == -1);
	new
		x = INI_SetTag(i, "hello");
	ASSERT(x != -1);
	ASSERT(YSI_g_sINITagBuffer[t][E_INI_TAGS_NEXT] == -1);
	ASSERT(YSI_g_sINITagBuffer[x][E_INI_TAGS_NEXT] == t);
	ASSERT(YSI_g_sINITagBuffer[x][E_INI_TAGS_START] == -1);
	INI_Close(i);
}

Test:INI_VariousWriting1()
{
	new
		INI:f = INI_Open("YSI/test_ini/test5.ini"),
		s;
	// String.
	s = INI_WriteString(f, "vvv", "yyy");
	ASSERT(!strcmp("vvv", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("yyy", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	// Dec.
	s = INI_WriteInt(f, "vvv", 57);
	ASSERT(!strcmp("vvv", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("57", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	s = INI_WriteInt(f, "vvv", cellmin);
	ASSERT(!strcmp("vvv", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("-2147483648", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	s = INI_WriteInt(f, "vvv", -99);
	ASSERT(!strcmp("vvv", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("-99", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	// Hex.
	s = INI_WriteHex(f, "vvv", 0x112233);
	ASSERT(!strcmp("vvv", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("0x00112233", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	s = INI_WriteHex(f, "vvv", cellmin);
	ASSERT(!strcmp("vvv", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("0x80000000", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	s = INI_WriteHex(f, "vvv", cellmax);
	ASSERT(!strcmp("vvv", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("0x7FFFFFFF", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	// Bin.
	s = INI_WriteBin(f, "vvv", 0);
	ASSERT(!strcmp("vvv", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("0b0", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	s = INI_WriteBin(f, "vvv", 1);
	ASSERT(!strcmp("vvv", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("0b1", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	s = INI_WriteBin(f, "vvv", -1);
	ASSERT(!strcmp("vvv", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("0b11111111111111111111111111111111", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	// Bool.
	s = INI_WriteBool(f, "vvv", false);
	ASSERT(!strcmp("vvv", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("false", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	s = INI_WriteBool(f, "vvv", true);
	ASSERT(!strcmp("vvv", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("true", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	// Float.
	s = INI_WriteFloat(f, "vvv", 0.0);
	ASSERT(!strcmp("vvv", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("0.000000", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	s = INI_WriteFloat(f, "vvv", 0.2);
	ASSERT(!strcmp("vvv", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("0.200000", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	//printf("%s %f", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], 0.2);
	s = INI_WriteFloat(f, "vvv", 0.2, 2);
	ASSERT(!strcmp("vvv", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_NAME], true));
	ASSERT(!strcmp("0.20", YSI_g_sINIWriteBuffer[s][E_INI_KV_ENTRY_TEXT], true));
	INI_Close(f);
}

Test:INI_Write0()
{
	new
		INI:f = INI_Open("YSI/test_ini/test6.ini"),
		str[32];
	for (new i = 0; i != 12; ++i)
	{
		format(str, sizeof (str), "key%d", i);
		INI_WriteInt(f, str, i);
	}
	INI_SetTag(f, "hello");
	for (new i = 0; i != 64; ++i)
	{
		format(str, sizeof (str), "key%d", i);
		INI_WriteInt(f, str, i);
	}
	INI_SetTag(f, "woo");
	for (new i = 0; i != 64; ++i)
	{
		format(str, sizeof (str), "key%d", i);
		INI_WriteInt(f, str, i);
	}
	INI_Close(f);
}

Test:INI_Write1()
{
	new
		INI:f = INI_Open("YSI/test_ini/test6.ini"),
		str[32];
	for (new i = 0; i != 16; ++i)
	{
		format(str, sizeof (str), "key%d", i);
		INI_WriteInt(f, str, i + 42);
	}
	INI_SetTag(f, "hello");
	for (new i = 0; i != 32; ++i)
	{
		format(str, sizeof (str), "key%d", i);
		INI_WriteInt(f, str, i + 42);
	}
	INI_SetTag(f, "woo");
	for (new i = 0; i != 20; ++i)
	{
		format(str, sizeof (str), "key%d", i);
		INI_WriteInt(f, str, i + 42);
	}
	INI_Close(f);
}

Test:INI_Write2()
{
	new
		INI:f = INI_Open("YSI/test_ini/test6.ini");
	INI_DeleteTag(f, "woo");
	INI_Close(f);
}

