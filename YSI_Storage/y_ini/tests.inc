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


