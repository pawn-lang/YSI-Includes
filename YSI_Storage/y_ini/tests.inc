Test:INI_AtStartOfLine1()
{
	ASSERT(INI_AtStartOfLine("hi", 0));
	ASSERT(INI_AtStartOfLine("  hi", 0));
	ASSERT(INI_AtStartOfLine("	hi", 0));
	ASSERT(INI_AtStartOfLine("  hi", 2));
	ASSERT(INI_AtStartOfLine("\thi", 1));
	ASSERT(INI_AtStartOfLine("\nhi", 1));
	ASSERT(!INI_AtStartOfLine("x\nhi", 1));
	ASSERT(INI_AtStartOfLine("\rhi", 1));
	ASSERT(!INI_AtStartOfLine("x\rhi", 1));
	ASSERT(!INI_AtStartOfLine("hhi", 1));
	ASSERT(!INI_AtStartOfLine("c hi", 2));
}

Test:INI_IsEscapeSequence1()
{
	new
		str[16];
	str = "\\;";
	ASSERT(INI_IsEscapeSequence(str, 1));
	str = "\\\\";
	ASSERT(INI_IsEscapeSequence(str, 1));
	str = "\\\\\\;";
	ASSERT(INI_IsEscapeSequence(str, 3));
	str = "\\\\\\\\";
	ASSERT(INI_IsEscapeSequence(str, 3));
	str = "\\\\\\n";
	ASSERT(INI_IsEscapeSequence(str, 3));
	str = "v\\\\\\\\";
	ASSERT(INI_IsEscapeSequence(str, 4));
	str = "hi\\n";
	ASSERT(INI_IsEscapeSequence(str, 3));
	str = ";";
	ASSERT(!INI_IsEscapeSequence(str, 0));
	str = "\\";
	ASSERT(!INI_IsEscapeSequence(str, 0));
	str = "hi\\\\n";
	ASSERT(!INI_IsEscapeSequence(str, 4));
	str = "\\\\";
	ASSERT(!INI_IsEscapeSequence(str, 0));
	// TODO: What should happen in this case?
	//ASSERT(INI_IsEscapeSequence("\\\\\\", 1));
	
}

Test:INI_GetCommentPos1()
{
	new
		val = cellmax;
	ASSERT(val >= cellmax);
	ASSERT(cellmax >= val);
	ASSERT(0 < val);
	ASSERT(cellmin < val);
	ASSERT(!(100000 >= val));
}

Test:INI_GetCommentPos2()
{
	ASSERT(INI_FindString("; ", ";") == 0);
	ASSERT(INI_FindString("hello ; hi", ";") == 6);
	ASSERT(INI_FindString("woop", ";") == cellmax);
	ASSERT(INI_FindString("there \\; you", ";") == cellmax);
	ASSERT(INI_FindString("maybe works? \\\\; nope", ";") == 15);
	ASSERT(INI_FindString("[bad;tag]", ";") == 4);
}

Test:INI_ReverseWhitespace1()
{
	ASSERT(INI_ReverseWhitespace("a b", 2) == 1);
	ASSERT(INI_ReverseWhitespace("abb", 2) == 2);
	ASSERT(INI_ReverseWhitespace("  b", 2) == 0);
	ASSERT(INI_ReverseWhitespace("b", 0) == 0);
}

Test:INI_IdentifyLineType1()
{
	// Comment lines and blank lines may as well be treated as the same thing,
	// except when rewriting the file.
	new p0s, p0e, p1s, p1e, p2s, p2e, bool:cont;
	// Comment lines.
	ASSERT(INI_IdentifyLineType("; Hello", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType("   ; There", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType("	; Hi", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType(";", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType(";\r\n", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType("\\;\r\n", p0s, p0e, p1s, p1e, p2s, p2e, cont) != e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType("hi ; there", p0s, p0e, p1s, p1e, p2s, p2e, cont) != e_INI_LINE_TYPE_BLANK);
	// Blank lines.
	ASSERT(INI_IdentifyLineType("", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType("    ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType("	\r\n", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_BLANK);
	ASSERT(INI_IdentifyLineType("\r\n", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_BLANK);
}

Test:INI_IdentifyLineType2()
{
	new p0s, p0e, p1s, p1e, p2s, p2e, bool:cont;
	// Invalid lines.
	new
		e_INI_LINE_TYPE:result;
	result = INI_IdentifyLineType("[badtag", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("   [tag", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("   [   ]", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("[tag;end]", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("[tag\\;end]", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result != e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType(" [tag\\]", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType(" [tag\\\\]", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result != e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("key", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("key\\=", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("key\\\\\\=value", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("\\;\r\n", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("key =  ", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType(" = value", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("thing", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
	result = INI_IdentifyLineType("thing ; comment", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result == e_INI_LINE_TYPE_INVALID);
}

Test:INI_IdentifyLineType3()
{
	new p0s, p0e, p1s, p1e, p2s, p2e, bool:cont;
	// Entry lines.
	ASSERT(INI_IdentifyLineType("key = value", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("key=value", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 4 && p1e == 9 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("key = value ; comment", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_ENTRY);
	//printf("%d %d %d %d %d %d", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == 12 && p2e == 21);
	ASSERT(INI_IdentifyLineType("key = value ; comment\r\n", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == 12 && p2e == 21);
	ASSERT(INI_IdentifyLineType("key =  value   ; com ment  \r\n", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 7 && p1e == 12 && p2s == 15 && p2e == 25);
	ASSERT(INI_IdentifyLineType("key = value\r\n", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 6 && p1e == 11 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("key	=value", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 3 && p1s == 5 && p1e == 10 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("   key=	value", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 3 && p0e == 6 && p1s == 8 && p1e == 13 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("   key=	value    ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 3 && p0e == 6 && p1s == 8 && p1e == 13 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("	key   =value  ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 1 && p0e == 4 && p1s == 8 && p1e == 13 && p2s == p2e);
}

Test:INI_IdentifyLineType4()
{
	new p0s, p0e, p1s, p1e, p2s, p2e, bool:cont;
	// Tag lines.
	ASSERT(INI_IdentifyLineType("[hello]", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType(" [hello] ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 2 && p0e == 7 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType(" [ hello] ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 3 && p0e == 8 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType(" [hello ] ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 2 && p0e == 7 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType("[ hello] ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 2 && p0e == 7 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType("[hello ]", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType("[hello   ]", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType("[   hello ]", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	// printf("%d %d %d %d %d %d", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(p0s == 4 && p0e == 9 && p1s == p1e && p2s == p2e);
}

Test:INI_IdentifyLineType5()
{
	new p0s, p0e, p1s, p1e, p2s, p2e, bool:cont;
	// Inheritance.
	ASSERT(INI_IdentifyLineType("[hello] : ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == p2e);
	ASSERT(INI_IdentifyLineType("[hello] : first", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == 10 && p1e == 15 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("[hello] : first, second", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == 10 && p1e == 23 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("[hello]   : first, second     ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == 12 && p1e == 25 && p2s == p2e);
	ASSERT(INI_IdentifyLineType("[hello] :    first, second   ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == 13 && p1e == 26 && p2s == p2e);
	// Commented out.
	ASSERT(INI_IdentifyLineType("[hello] ;: ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == 8 && p2e == 10);
	ASSERT(INI_IdentifyLineType("[hello] ; : first, second ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 1 && p0e == 6 && p1s == p1e && p2s == 8 && p2e == 25);
	// printf("%d %d %d %d %d %d", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	// Both.
	ASSERT(INI_IdentifyLineType(" [ hello ]  :  inheritance  ;  : first, second ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_TAG);
	ASSERT(p0s == 3 && p0e == 8 && p1s == 15 && p1e == 26 && p2s == 28 && p2e == 46);
	// printf("%d %d %d %d %d %d", p0s, p0e, p1s, p1e, p2s, p2e, cont);
}

Test:INI_IdentifyLineType6()
{
	new p0s, p0e, p1s, p1e, p2s, p2e, bool:cont;
	// Continuation.
	new
		e_INI_LINE_TYPE:result;
	cont = false;
	result = INI_IdentifyLineType("hi = there\\ ", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result == e_INI_LINE_TYPE_ENTRY);
	//printf("%d %d %d %d %d %d", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(p0s == 0 && p1e == 10);
	ASSERT(cont);
	cont = false;
	ASSERT(INI_IdentifyLineType("hi = there  \\   ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p1e == 10);
	ASSERT(cont);
	cont = false;
	ASSERT(INI_IdentifyLineType("hi =    \\   ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_ENTRY);
	ASSERT(p0s == 0 && p0e == 2);
	ASSERT(p1s == p1e);
	ASSERT(cont);
	cont = true;
	ASSERT(INI_IdentifyLineType("hello there ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == p0e && p1s == 0 && p1e == 11);
	ASSERT(!cont);
	cont = true;
	ASSERT(INI_IdentifyLineType("hello there \\  ", p0s, p0e, p1s, p1e, p2s, p2e, cont) == e_INI_LINE_TYPE_CONT);
	ASSERT(p0s == p0e && p1s == 0 && p1e == 11);
	ASSERT(cont);
	cont = true;
	result = INI_IdentifyLineType("   \\", p0s, p0e, p1s, p1e, p2s, p2e, cont);
	ASSERT(result == e_INI_LINE_TYPE_CONT);
	ASSERT(cont);
	ASSERT(p0s == p0e && p1s == p1e);
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
		// printf("%s (%d): %d %d %d", tag, YHash(tag, false),
			// _I<>,
			// _I<atag>,
			// _I<tag2>);
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
	gs_K4;

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



