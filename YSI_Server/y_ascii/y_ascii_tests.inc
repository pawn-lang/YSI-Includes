@test(.group = "y_ascii") y_ascii_Prints0()
{
	ASCII_PrintLinePart("Hello World!", 12, false, ASCII_BORDER_STYLE_SMALL, ASCII_ALIGNMENT_STYLE_LEFT);
	ASCII_PrintLinePart("Hello World!", 12, false, ASCII_BORDER_STYLE_SMALL, ASCII_ALIGNMENT_STYLE_CENTRE);
	ASCII_PrintLinePart("Hello World!", 12, false, ASCII_BORDER_STYLE_LARGE, ASCII_ALIGNMENT_STYLE_LEFT);
	ASCII_PrintLinePart("Hello World!", 12, false, ASCII_BORDER_STYLE_LARGE, ASCII_ALIGNMENT_STYLE_CENTRE);
	ASCII_PrintLinePart("Hello World!", 12, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT);
	ASCII_PrintLinePart("Hello World!", 12, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_CENTRE);
	ASCII_PrintLinePart("Hello World!", 12, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT, 8);
	ASCII_PrintSection("Hello World!\n\n", ASCII_BORDER_STYLE_SMALL, ASCII_ALIGNMENT_STYLE_CENTRE);
	ASCII_PrintSection("This is some long text that I hope will wrap.  To that end I am including a variety of relatively verbose verbiage and excessively long words.", ASCII_BORDER_STYLE_SMALL, ASCII_ALIGNMENT_STYLE_LEFT);
	ASCII_PrintSection("Hello World!\n\n", ASCII_BORDER_STYLE_LARGE, ASCII_ALIGNMENT_STYLE_CENTRE);
	ASCII_PrintSection("This is some long text that I hope will wrap.  To that end I am including a variety of relatively verbose verbiage and excessively long words.", ASCII_BORDER_STYLE_LARGE, ASCII_ALIGNMENT_STYLE_LEFT);
	ASCII_PrintSection("Hello World!\n\n", ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_CENTRE);
	ASCII_PrintSection("This is some long text that I hope will wrap.  To that end I am including a variety of relatively verbose verbiage and excessively long words.", ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT, 2);
}

@test(.group = "y_ascii") y_ascii_Prints1()
{
	printf(" ");
	printf(" ");
	printf(" ");
	ASCII_StartDisplay(ASCII_BORDER_STYLE_PILLARS);
	ASCII_StartSection(ASCII_BORDER_STYLE_PILLARS);
	ASCII_PrintLinePart(" YYYYYYY       YYYYYYY    SSSSSSSSSSSSSSS  IIIIIIIIII ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT),
	ASCII_PrintLinePart(" Y:::::Y       Y:::::Y  SS:::::::::::::::S I::::::::I ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT),
	ASCII_PrintLinePart(" Y:::::Y       Y:::::Y S:::::SSSSSS::::::S I::::::::I ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT),
	ASCII_PrintLinePart(" Y::::::Y     Y::::::Y S:::::S     SSSSSSS II::::::II ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT),
	ASCII_PrintLinePart(" YYY:::::Y   Y:::::YYY S:::::S               I::::I   ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT),
	ASCII_PrintLinePart("    Y:::::Y Y:::::Y    S:::::S               I::::I   ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT),
	ASCII_PrintLinePart("     Y:::::Y:::::Y      S::::SSSS            I::::I   ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT),
	ASCII_PrintLinePart("      Y:::::::::Y        SS::::::SSSSS       I::::I   ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT),
	ASCII_PrintLinePart("       Y:::::::Y           SSS::::::::SS     I::::I   ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT),
	ASCII_PrintLinePart("        Y:::::Y               SSSSSS::::S    I::::I   ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT),
	ASCII_PrintLinePart("        Y:::::Y                    S:::::S   I::::I   ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT),
	ASCII_PrintLinePart("        Y:::::Y                    S:::::S   I::::I   ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT),
	ASCII_PrintLinePart("        Y:::::Y        SSSSSSS     S:::::S II::::::II ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT),
	ASCII_PrintLinePart("     YYYY:::::YYYY     S::::::SSSSSS:::::S I::::::::I ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT),
	ASCII_PrintLinePart("     Y:::::::::::Y     S:::::::::::::::SS  I::::::::I ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT),
	ASCII_PrintLinePart("     YYYYYYYYYYYYY      SSSSSSSSSSSSSSS    IIIIIIIIII ", 54, false, ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT);
	ASCII_EndSection(ASCII_BORDER_STYLE_PILLARS);
	ASCII_Separate(ASCII_BORDER_STYLE_PILLARS);
	ASCII_StartSection(ASCII_BORDER_STYLE_PILLARS);
	ASCII_PrintSection("Hello World!\n\n", ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_CENTRE, 8);
	ASCII_PrintSection("This is some long text that I hope will wrap.  To that end I am including a variety of relatively verbose verbiage and excessively long words.", ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT, 8);
	ASCII_EndSection(ASCII_BORDER_STYLE_PILLARS);
	ASCII_Separate(ASCII_BORDER_STYLE_PILLARS);
	ASCII_EndDisplay(ASCII_BORDER_STYLE_PILLARS);
}

@test(.group = "y_ascii") y_ascii_Prints2()
{
	ASCII_StartDisplay(ASCII_BORDER_STYLE_PILLARS);
	ASCII_StartSection(ASCII_BORDER_STYLE_PILLARS);
	ASCII_PrintSection("Generating code, this may take a little bit of time.  Note that this code generation works best with the JIT plugin, which you are not currently using.  Get it here:\n\nhttps://git.io/jit-plugin\n\nPlease wait...\n\nDone!", ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_CENTRE, 8);
	ASCII_EndSection(ASCII_BORDER_STYLE_PILLARS);
	ASCII_EndDisplay(ASCII_BORDER_STYLE_PILLARS);
}

