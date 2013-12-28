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
	ASSERT(INI_GetCommentPos("; ") == 0);
	ASSERT(INI_GetCommentPos("hello ; hi") == 6);
	ASSERT(INI_GetCommentPos("woop") == cellmax);
	ASSERT(INI_GetCommentPos("there \\; you") == cellmax);
	ASSERT(INI_GetCommentPos("maybe works? \\\\; nope") == 15);
	ASSERT(INI_GetCommentPos("[bad;tag]") == 4);
}


