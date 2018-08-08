loadtext test[ysi_test];

TEST__ y_text_formatex_cellmin_d()
{
	static
		result[] = "-2147483648";
	TextTest_Reset();
	Text_FormatEx(YSI_gTextTestOutput[0], MAX_Y_TEXT_TEST_LENGTH, "%d", cellmin);
	P:3("y_text_formatex_cellmin_d:\r\n    player: %d\r\n    colour: %04x%04x\r\n    output: \"%s\"", YSI_gTextTestPlayer[0], YSI_gTextTestStyle[0] >>> 16, YSI_gTextTestStyle[0] & 0xFFFF, YSI_gTextTestOutput[0]);
	ASSERT(YSI_gTextTestOutput[0][0] && !strcmp(YSI_gTextTestOutput[0], result));
}

TEST__ y_text_formatex_cellmin_x()
{
	static
		result[] = "80000000";
	TextTest_Reset();
	Text_FormatEx(YSI_gTextTestOutput[0], MAX_Y_TEXT_TEST_LENGTH, "%x", cellmin);
	P:3("y_text_formatex_cellmin_x:\r\n    player: %d\r\n    colour: %04x%04x\r\n    output: \"%s\"", YSI_gTextTestPlayer[0], YSI_gTextTestStyle[0] >>> 16, YSI_gTextTestStyle[0] & 0xFFFF, YSI_gTextTestOutput[0]);
	ASSERT(YSI_gTextTestOutput[0][0] && !strcmp(YSI_gTextTestOutput[0], result));
}

TEST__ y_text_formatex_cellmin_b()
{
	static
		result[] = "10000000000000000000000000000000";
	TextTest_Reset();
	Text_FormatEx(YSI_gTextTestOutput[0], MAX_Y_TEXT_TEST_LENGTH, "%b", cellmin);
	P:3("y_text_formatex_cellmin_b:\r\n    player: %d\r\n    colour: %04x%04x\r\n    output: \"%s\"", YSI_gTextTestPlayer[0], YSI_gTextTestStyle[0] >>> 16, YSI_gTextTestStyle[0] & 0xFFFF, YSI_gTextTestOutput[0]);
	ASSERT(YSI_gTextTestOutput[0][0] && !strcmp(YSI_gTextTestOutput[0], result));
}

TEST__ y_text_Text_Send_1()
{
	static
		result[] = "Hello World";
	TextTest_Reset();
	Text_Send(42, Language:0, $TEST_STRING_C, "World");
	P:3("y_text_Text_Send_1:\r\n    player: %d\r\n    colour: %04x%04x\r\n    output: \"%s\"", YSI_gTextTestPlayer[0], YSI_gTextTestStyle[0] >>> 16, YSI_gTextTestStyle[0] & 0xFFFF, YSI_gTextTestOutput[0]);
	ASSERT(YSI_gTextTestOutput[0][0] && !strcmp(YSI_gTextTestOutput[0], result));
}

