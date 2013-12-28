Test:INI_AtStartOfLine1()
{
	ASSERT(INI_AtStartOfLine("hi", 0));
	ASSERT(INI_AtStartOfLine("  hi", 0));
	ASSERT(INI_AtStartOfLine("	hi", 0));
	ASSERT(INI_AtStartOfLine("  hi", 2));
	ASSERT(INI_AtStartOfLine("	hi", 3));
	ASSERT(INI_AtStartOfLine("\nhi", 1));
	ASSERT(!INI_AtStartOfLine("x\nhi", 1));
	ASSERT(INI_AtStartOfLine("\rhi", 1));
	ASSERT(!INI_AtStartOfLine("x\rhi", 1));
	ASSERT(!INI_AtStartOfLine("hhi", 1));
	ASSERT(!INI_AtStartOfLine("c hi", 2));
}

Test:INI_IsEscapeSequence1()
{
	ASSERT(INI_IsEscapeSequence("\\;", 1));
	ASSERT(INI_IsEscapeSequence("\\\\", 1));
	ASSERT(INI_IsEscapeSequence("\\\\\\;", 3));
	ASSERT(INI_IsEscapeSequence("\\\\\\\\", 3));
	ASSERT(INI_IsEscapeSequence("\\\\\\n", 3));
	ASSERT(INI_IsEscapeSequence("v\\\\\\\\", 4));
	ASSERT(INI_IsEscapeSequence("hi\\n", 3));
	ASSERT(!INI_IsEscapeSequence(";", 0));
	ASSERT(!INI_IsEscapeSequence("\\", 0));
	ASSERT(!INI_IsEscapeSequence("hi\\\\n", 4));
	ASSERT(!INI_IsEscapeSequence("\\\\", 0));
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
	// Invalid lines.
	ASSERT(INI_IdentifyLineType("[badtag", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_INVALID);
	ASSERT(INI_IdentifyLineType("   [tag", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_INVALID);
	ASSERT(INI_IdentifyLineType("[tag;end]", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_INVALID);
	ASSERT(INI_IdentifyLineType("[tag\\;end]", p0s, p0e, p1s, p1e, p2s, p2e) != e_INI_LINE_TYPE_INVALID);
	ASSERT(INI_IdentifyLineType(" [tag\\]", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_INVALID);
	ASSERT(INI_IdentifyLineType(" [tag\\\\]", p0s, p0e, p1s, p1e, p2s, p2e) != e_INI_LINE_TYPE_INVALID);
	ASSERT(INI_IdentifyLineType("key", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_INVALID);
	ASSERT(INI_IdentifyLineType("key\\=", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_INVALID);
	ASSERT(INI_IdentifyLineType("key\\\\\\=value", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_INVALID);
	ASSERT(INI_IdentifyLineType("\\;\r\n", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_INVALID);
	// // Entry lines.
	// ASSERT(INI_IdentifyLineType("", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	// ASSERT(INI_IdentifyLineType("", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	// ASSERT(INI_IdentifyLineType("", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_ENTRY);
	// // Tag lines.
	// ASSERT(INI_IdentifyLineType("", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	// ASSERT(INI_IdentifyLineType("", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
	// ASSERT(INI_IdentifyLineType("", p0s, p0e, p1s, p1e, p2s, p2e) == e_INI_LINE_TYPE_TAG);
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
	ASSERT(end == 12);
}



