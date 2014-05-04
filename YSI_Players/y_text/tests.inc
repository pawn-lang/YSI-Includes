Test:TextR_DoStraightFade0SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		bool:pending = false,
		str[64] = "Hello There",
		curColour = 0xFEFEFE00;
	ASSERT(TextR_DoStraightFade(str, sizeof (str), curColour, 6, 0xAAAAAAAA, 5, 0xFFFFFFFF, pending) == 8 * 5);
	ASSERT(!strcmp(str, "Hello {AAAAAA}T{BABABA}h{CCCCCC}e{DCDCDC}r{EEEEEE}e"));
	ASSERT(curColour == 0xEEEEEE00);
	ASSERT(pending == false);
}

Test:TextR_DoStraightFade1SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		bool:pending = false,
		str[64] = "Hello There",
		curColour = 0xFEFEFE00;
	ASSERT(TextR_DoStraightFade(str, sizeof (str), curColour, 6, 0xFFFFFFFF, 5, 0xAAAAAAAA, pending) == 8 * 4);
	ASSERT(!strcmp(str, "Hello T{EEEEEE}h{DCDCDC}e{CCCCCC}r{BABABA}e"));
	ASSERT(curColour == 0xBABABA00);
	ASSERT(pending == false);
}

Test:TextR_DoStraightFade2SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		bool:pending = false,
		str[64] = "Hello There",
		curColour = 0;
	ASSERT(TextR_DoStraightFade(str, sizeof (str), curColour, 5, 0x00EE2200, 6, 0x0022EE00, pending) == 8 * 5);
	// TODO: account for pointless colourings of spaces, as below.
	ASSERT(!strcmp(str, "Hello {00CC44}T{00AA66}h{008888}e{0066AA}r{0044CC}e"));
	ASSERT(curColour == 0x0044CC00);
	ASSERT(pending == false);
}

Test:TextR_DoStraightFade3SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		bool:pending = false,
		str[64] = "Hello There",
		curColour = 0xFEFEFE00;
	ASSERT(TextR_DoStraightFade(str, sizeof (str), curColour, 4, 0x00EE2200, 6, 0x0022EE00, pending) == 8 * 5);
	// TODO: account for pointless colourings of spaces, as below.
	ASSERT(!strcmp(str, "Hell{00EE22}o {00AA66}T{008888}h{0066AA}e{0044CC}re"));
	ASSERT(curColour == 0x0044CC00);
	ASSERT(pending == false);
}




Test:TextR_InsertColour0SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		bool:pending = false,
		str[32] = "Hello There",
		curColour = 0xFEFEFE00;
	ASSERT(TextR_InsertColour(str, sizeof (str), 6, curColour, 0xAAAAAAAA, pending) == 8);
	ASSERT(!strcmp(str, "Hello {AAAAAA}There"));
	ASSERT(curColour == 0xAAAAAA00);
	ASSERT(pending == false);
}

Test:TextR_InsertColour1SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		bool:pending = false,
		str[32] = "Hello There",
		curColour = 0xFEFEFE00;
	ASSERT(TextR_InsertColour(str, sizeof (str), 6, curColour, 0xFFFFFFAA, pending) == 0);
	ASSERT(!strcmp(str, "Hello There"));
	ASSERT(curColour == 0xFEFEFE00);
	ASSERT(pending == false);
}

Test:TextR_InsertColour2SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		bool:pending = false,
		str[32] = "Hello There",
		curColour = 0xFEFEFE00;
	ASSERT(TextR_InsertColour(str, sizeof (str), 6, curColour, 0xABABABAB, pending) == 8);
	ASSERT(!strcmp(str, "Hello {AAAAAA}There"));
	ASSERT(curColour == 0xAAAAAA00);
	ASSERT(pending == false);
}

Test:TextR_InsertColour3SCM()
{
	state y_text_colour : y_text_colour_scm;
	// Don't insert colours at the end of the string (no point).
	new
		bool:pending = false,
		str[32] = "Hello There",
		curColour = 0xFEFEFE00;
	ASSERT(TextR_InsertColour(str, sizeof (str), 11, curColour, 0xAAAAAAAA, pending) == 0);
	ASSERT(!strcmp(str, "Hello There"));
	ASSERT(curColour == 0xFEFEFE00);
	ASSERT(pending == true);
}

Test:TextR_InsertColour4SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		bool:pending = false,
		str[32] = "Hello There",
		curColour = 0xFEFEFE00;
	ASSERT(TextR_InsertColour(str, sizeof (str), 0, curColour, 0x23456789, pending) == 8);
	ASSERT(!strcmp(str, "{224466}Hello There"));
	ASSERT(curColour == 0x22446600);
	ASSERT(pending == false);
}

Test:TextR_InsertColour5SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		bool:pending = false,
		str[32] = "Hello There",
		curColour = 0xFEFEFE00;
	ASSERT(TextR_InsertColour(str, sizeof (str), 5, curColour, 0x23456789, pending) == 0);
	ASSERT(!strcmp(str, "Hello There"));
	ASSERT(curColour == 0xFEFEFE00);
	ASSERT(pending == true);
}

Test:TextR_InsertColour0GT()
{
	state y_text_colour : y_text_colour_gt;
	new
		bool:pending = false,
		str[32] = "Hello There",
		curColour = 0x100 | 'r';
	ASSERT(TextR_InsertColour(str, sizeof (str), 0, curColour, SAMP_GAME_TEXT_RH, pending) == 0);
	ASSERT(!strcmp(str, "Hello There"));
	ASSERT(curColour == 0x100 | 'r');
	ASSERT(pending == false);
}

Test:TextR_InsertColour1GT()
{
	state y_text_colour : y_text_colour_gt;
	new
		bool:pending = false,
		str[32] = "Hello There",
		curColour = 0x100 | 'r';
	ASSERT(TextR_InsertColour(str, sizeof (str), 0, curColour, SAMP_GAME_TEXT_RHH, pending) == 3);
	ASSERT(!strcmp(str, "~h~Hello There"));
	ASSERT(curColour == 0x200 | 'r');
	ASSERT(pending == false);
}

Test:TextR_InsertColour2GT()
{
	state y_text_colour : y_text_colour_gt;
	new
		bool:pending = false,
		str[32] = "Hello There",
		curColour = 0x100 | 'r';
	ASSERT(TextR_InsertColour(str, sizeof (str), 0, curColour, SAMP_GAME_TEXT_R, pending) == 3);
	ASSERT(!strcmp(str, "~r~Hello There"));
	ASSERT(curColour == 0x000 | 'r');
	ASSERT(pending == false);
}

Test:TextR_InsertColour3GT()
{
	state y_text_colour : y_text_colour_gt;
	new
		bool:pending = false,
		str[32] = "Hello There",
		curColour = 0x100 | 'r';
	ASSERT(TextR_InsertColour(str, sizeof (str), 0, curColour, SAMP_GAME_TEXT_RHHHH, pending) == 9);
	ASSERT(!strcmp(str, "~h~~h~~h~Hello There"));
	ASSERT(curColour == 0x400 | 'r');
	ASSERT(pending == false);
}

Test:TextR_InsertColour4GT()
{
	state y_text_colour : y_text_colour_gt;
	new
		bool:pending = false,
		str[32] = "Hello There",
		curColour = 0x100 | 'g';
	ASSERT(TextR_InsertColour(str, sizeof (str), 0, curColour, SAMP_GAME_TEXT_YH, pending) == 6);
	ASSERT(!strcmp(str, "~y~~h~Hello There"));
	ASSERT(curColour == 0x100 | 'y');
	ASSERT(pending == false);
}

Test:TextR_InsertColour5GT()
{
	state y_text_colour : y_text_colour_gt;
	new
		bool:pending = false,
		str[32] = "Hello There",
		curColour = 0x200 | 'p';
	ASSERT(TextR_InsertColour(str, sizeof (str), 0, curColour, SAMP_GAME_TEXT_BHHH, pending) == 12);
	ASSERT(!strcmp(str, "~b~~h~~h~~h~Hello There"));
	ASSERT(curColour == 0x300 | 'b');
	ASSERT(pending == false);
}

Test:TextR_InsertColour6GT()
{
	state y_text_colour : y_text_colour_gt;
	new
		bool:pending = false,
		str[32] = "Hello There",
		curColour = 0;
	ASSERT(TextR_InsertColour(str, sizeof (str), 0, curColour, SAMP_GAME_TEXT_HH, pending) == 6);
	ASSERT(!strcmp(str, "~h~~h~Hello There"));
	ASSERT(curColour == 0x200 | 'x');
	ASSERT(pending == false);
}

Test:TextR_InsertColour7GT()
{
	state y_text_colour : y_text_colour_gt;
	new
		bool:pending = false,
		str[32] = "Hello There",
		curColour = 0x100 | 'x';
	ASSERT(TextR_InsertColour(str, sizeof (str), 0, curColour, SAMP_GAME_TEXT_HH, pending) == 3);
	ASSERT(!strcmp(str, "~h~Hello There"));
	ASSERT(curColour == 0x200 | 'x');
	ASSERT(pending == false);
}

Test:TextR_Complete0()
{
	// String 1.
	new
		idx = 0,
		//str[32] = "Hello There, are you?",
		rel[6] = {5, -2, 11, -3, 0},
		abs[6] = {0, 55, 55, 55, 55};
		// Insert "how ".
	TextR_CompleteRelToAbs(rel, abs,idx);
	
	ASSERT(abs[-1 + 1] == 4);
	ASSERT(abs[-1 + 2] == -2);
	ASSERT(abs[-1 + 3] == 5);
	ASSERT(abs[-1 + 4] == -3);
	ASSERT(abs[-1 + 5] == 16);
	ASSERT(idx == 4);
}

Test:TextR_RelToAbs0()
{
	// String 1.
	new
		idx = 0,
		//str[32] = "Hello There, are you?",
		rel[6] = {5, -2, 11, -3, 0},
		abs[6] = {0, 55, 55, 55, 55};
		// Insert "how ".
	TextR_UpdateRelToAbs(rel, abs, idx, 4, 13);
	TextR_CompleteRelToAbs(rel, abs,idx);
	
	ASSERT(abs[-1 + 1] == 4);
	ASSERT(abs[-1 + 2] == -2);
	ASSERT(abs[-1 + 3] == 5);
	ASSERT(abs[-1 + 4] == -3);
	ASSERT(abs[-1 + 5] == 20);
}

Test:TextR_RelToAbs1()
{
	// String 1.
	new
		idx = 0,
		//str[32] = "Hello There, are you?",
		rel[8] = {5, -2, 11, -3, 5, -3, 0},
		abs[8] = {0, 55, 55, 55, 55, 66, 66};
		// Insert "how ".
	TextR_UpdateRelToAbs(rel, abs, idx, 4, 13);
	TextR_CompleteRelToAbs(rel, abs,idx);
	
	ASSERT(abs[-1 + 1] == 6);
	ASSERT(abs[-1 + 2] == -2);
	ASSERT(abs[-1 + 3] == 5);
	ASSERT(abs[-1 + 4] == -3);
	ASSERT(abs[-1 + 5] == 20);
	ASSERT(abs[-1 + 6] == -3);
	ASSERT(abs[-1 + 7] == 25);
}

Test:TextR_RelToAbs2()
{
	// String 1.
	new
		idx = 0,
		//str[32] = "Hello There, are you?",
		rel[6] = {5, -2, 11, -3, 0},
		abs[6] = {0, 55, 55, 55, 55};
		// Insert "how ".
	TextR_UpdateRelToAbs(rel, abs, idx, 4, 13);
	TextR_UpdateRelToAbs(rel, abs, idx, 5, 20);
	TextR_UpdateRelToAbs(rel, abs, idx, 6, 80);
	TextR_CompleteRelToAbs(rel, abs,idx);
	
	ASSERT(abs[-1 + 1] == 4);
	ASSERT(abs[-1 + 2] == -2);
	ASSERT(abs[-1 + 3] == 5);
	ASSERT(abs[-1 + 4] == -3);
	ASSERT(abs[-1 + 5] == 20);
}

Test:TextR_RelToAbs3()
{
	// String 1.
	new
		idx = 0,
		//str[32] = "Hello There, are you?",
		rel[8] = {5, -2, 11, -3, 5, -4, 0},
		abs[8] = {0, 55, 55, 55, 55, 66, 66};
		// Insert "how ".
	TextR_UpdateRelToAbs(rel, abs, idx, 4, 13);
	TextR_UpdateRelToAbs(rel, abs, idx, 5, 20);
	TextR_UpdateRelToAbs(rel, abs, idx, 6, 80);
	TextR_CompleteRelToAbs(rel, abs,idx);
	
	ASSERT(abs[-1 + 1] == 6);
	ASSERT(abs[-1 + 2] == -2);
	ASSERT(abs[-1 + 3] == 5);
	ASSERT(abs[-1 + 4] == -3);
	ASSERT(abs[-1 + 5] == 20);
	ASSERT(abs[-1 + 6] == -4);
	ASSERT(abs[-1 + 7] == 30);
}

Test:TextR_RelToAbs4()
{
	// String 1.
	new
		idx = 0,
		//str[32] = "Hello There, are you?",
		rel[8] = {5, -2, 11, -3, 5, -4, 0},
		abs[8] = {0, 55, 55, 55, 55, 66, 66};
		// Insert "how ".
	TextR_UpdateRelToAbs(rel, abs, idx, 4, 13);
	TextR_UpdateRelToAbs(rel, abs, idx, -2, 20);
	TextR_UpdateRelToAbs(rel, abs, idx, 6, 80);
	TextR_CompleteRelToAbs(rel, abs,idx);
	
	ASSERT(abs[-1 + 1] == 6);
	ASSERT(abs[-1 + 2] == -2);
	ASSERT(abs[-1 + 3] == 5);
	ASSERT(abs[-1 + 4] == -3);
	ASSERT(abs[-1 + 5] == 20);
	ASSERT(abs[-1 + 6] == -4);
	ASSERT(abs[-1 + 7] == 23);
}








Test:Colours_EncodeGameText0()
{
	ASSERT(Colours_EncodeGameText("~r~") == 0x00 | 'r');
	ASSERT(Colours_EncodeGameText("~r~~h~") == 0x100 | 'r');
	ASSERT(Colours_EncodeGameText("~R~") == 0x00 | 'r');
	ASSERT(Colours_EncodeGameText("~r~~H~~h~") == 0x200 | 'r');
	ASSERT(Colours_EncodeGameText("~h~") == 0x100 | 'x');
	ASSERT(Colours_EncodeGameText("~h~~h~") == 0x200 | 'x');
	ASSERT(Colours_EncodeGameText("~r~") == 0x00 | 'r');
	ASSERT(Colours_EncodeGameText("~g~") == 0x00 | 'g');
	ASSERT(Colours_EncodeGameText("~b~") == 0x00 | 'b');
	ASSERT(Colours_EncodeGameText("~y~") == 0x00 | 'y');
	ASSERT(Colours_EncodeGameText("~p~") == 0x00 | 'p');
	ASSERT(Colours_EncodeGameText("~w~") == 0x00 | 'w');
	ASSERT(Colours_EncodeGameText("~l~") == 0x00 | 'l');
	ASSERT(Colours_EncodeGameText("~l~~h~") == 0x100 | 'l');
	ASSERT(Colours_EncodeGameText("~l~~h~~h~") == 0x200 | 'l');
	ASSERT(Colours_EncodeGameText("~l~~h~~h~~h~") == 0x300 | 'l');
	ASSERT(Colours_EncodeGameText("~l~~h~~h~~h~~h~") == 0x400 | 'l');
	ASSERT(Colours_EncodeGameText("~l~~h~~h~~h~~h~~h~") == 0x500 | 'l');
	ASSERT(Colours_EncodeGameText("~x~") == 0x00 | 'x');
}

Test:Colours_EncodeGameText1()
{
	ASSERT(Colours_EncodeGameText("~z~") == 0);
	ASSERT(Colours_EncodeGameText("~~~") == 0);
	ASSERT(Colours_EncodeGameText("~r") == 0);
	ASSERT(Colours_EncodeGameText("~Y") == 0);
	ASSERT(Colours_EncodeGameText("~Y") == 0);
}

Test:TextR_GetFadeData0()
{
	new
		colourLocations[] = {0,
			0xAAAAAAAA | _:e_TEXT_RENDER_COLOUR_FADE, 10,
			0x22222222, 20},
		endColour,
		endPos,
		newlines;
	TextR_GetFadeData(colourLocations, 2, endColour, endPos, newlines);
	ASSERT(endColour == 0x22222222);
	ASSERT(endPos == 20);
	ASSERT(newlines == 0);
}

Test:TextR_GetFadeData1()
{
	new
		colourLocations[] = {0,
			0xAAAAAAAA | _:e_TEXT_RENDER_COLOUR_FADE | _:e_TEXT_RENDER_COLOUR_LINE, 10,
			0x22222222, 20},
		endColour,
		endPos,
		newlines;
	TextR_GetFadeData(colourLocations, 2, endColour, endPos, newlines);
	ASSERT(endColour == 0x22222222);
	ASSERT(endPos == 20);
	ASSERT(newlines == 1);
}

Test:TextR_GetFadeData2()
{
	new
		colourLocations[] = {0,
			0xAAAAAAAA | _:e_TEXT_RENDER_COLOUR_FADE, 10,
			0x22222222 | _:e_TEXT_RENDER_COLOUR_LINE, 20},
		endColour,
		endPos,
		newlines;
	TextR_GetFadeData(colourLocations, 2, endColour, endPos, newlines);
	ASSERT(endColour == 0x22222222 | _:e_TEXT_RENDER_COLOUR_LINE);
	ASSERT(endPos == 20);
	ASSERT(newlines == 0);
}

Test:TextR_GetFadeData3()
{
	new
		colourLocations[] = {0,
			0xAAAAAAAA | _:e_TEXT_RENDER_COLOUR_FADE | _:e_TEXT_RENDER_COLOUR_LINE, 10,
			0x22222222 | _:e_TEXT_RENDER_COLOUR_LINE, 20},
		endColour,
		endPos,
		newlines;
	TextR_GetFadeData(colourLocations, 2, endColour, endPos, newlines);
	ASSERT(endColour == 0x22222222 | _:e_TEXT_RENDER_COLOUR_LINE);
	ASSERT(endPos == 20);
	ASSERT(newlines == 1);
}

Test:TextR_GetFadeData4()
{
	new
		colourLocations[] = {0,
			0xAAAAAAAA | _:e_TEXT_RENDER_COLOUR_FADE, 10,
			_:e_TEXT_RENDER_COLOUR_LINE, 15,
			0x22222222, 20},
		endColour,
		endPos,
		newlines;
	TextR_GetFadeData(colourLocations, 2, endColour, endPos, newlines);
	ASSERT(endColour == 0x22222222);
	ASSERT(endPos == 20);
	ASSERT(newlines == 1);
}

Test:TextR_GetFadeData5()
{
	new
		colourLocations[] = {0,
			0xAAAAAAAA | _:e_TEXT_RENDER_COLOUR_FADE | _:e_TEXT_RENDER_COLOUR_LINE, 10,
			0x22222222, 20,
			0x66666666, 30},
		endColour,
		endPos,
		newlines;
	TextR_GetFadeData(colourLocations, 2, endColour, endPos, newlines);
	ASSERT(endColour == 0x22222222);
	ASSERT(endPos == 20);
	ASSERT(newlines == 1);
}

Test:TextR_GetFadeData6()
{
	new
		colourLocations[] = {0,
			0xAAAAAAAA | _:e_TEXT_RENDER_COLOUR_FADE, 10,
			0x66666666, 15,
			0x22222222 | _:e_TEXT_RENDER_COLOUR_LINE, 20},
		endColour,
		endPos,
		newlines;
	TextR_GetFadeData(colourLocations, 2, endColour, endPos, newlines);
	ASSERT(endColour == 0x66666666);
	ASSERT(endPos == 15);
	ASSERT(newlines == 0);
}

Test:TextR_GetFadeData7()
{
	new
		colourLocations[] = {0,
			0xAAAAAAAA | _:e_TEXT_RENDER_COLOUR_FADE | _:e_TEXT_RENDER_COLOUR_LINE, 10,
			0x88888800 | _:e_TEXT_RENDER_COLOUR_LINE, 14,
			0x22222222 | _:e_TEXT_RENDER_COLOUR_LINE, 20},
		endColour,
		endPos,
		newlines;
	TextR_GetFadeData(colourLocations, 2, endColour, endPos, newlines);
	ASSERT(endColour == 0x88888800 | _:e_TEXT_RENDER_COLOUR_LINE);
	ASSERT(endPos == 14);
	ASSERT(newlines == 1);
}

Test:TextR_GetFadeData8()
{
	new
		colourLocations[] = {0,
			0xAAAAAAAA | _:e_TEXT_RENDER_COLOUR_FADE | _:e_TEXT_RENDER_COLOUR_LINE, 10,
			_:e_TEXT_RENDER_COLOUR_LINE, 14,
			0x22222222 | _:e_TEXT_RENDER_COLOUR_LINE, 20},
		endColour,
		endPos,
		newlines;
	TextR_GetFadeData(colourLocations, 2, endColour, endPos, newlines);
	ASSERT(endColour == 0x22222222 | _:e_TEXT_RENDER_COLOUR_LINE);
	ASSERT(endPos == 20);
	ASSERT(newlines == 2);
}



Test:TextR_DoNLFade0SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		colourLocations[] = {0,
			0x20408000 | _:e_TEXT_RENDER_COLOUR_LINE, 2,
			_:e_TEXT_RENDER_COLOUR_LINE, 4,
			_:e_TEXT_RENDER_COLOUR_LINE, 7,
			0x00000002, 10, // Special encoding for pure white.
			0, 65536},
		endPos,
		endColour,
		newLines,
		oc = 0xFEFEFEFE,
		bool:pending,
		idx = 2,
		str[64] = "A longer string.",
		sc = colourLocations[idx - 1];
	TextR_GetFadeData(colourLocations, idx, endColour, endPos, newLines);
	// printf("%d %d %d", endPos, endColour, newLines);
	ASSERT(endPos == 10);
	ASSERT(endColour == 0x00000002);
	ASSERT(newLines == 3);
	TextR_DoNLFade(str, sizeof (str), oc, colourLocations[idx], sc, endPos - colourLocations[idx], endColour, colourLocations, idx, pending, 0);
	//printf(str);
	// ASSERT(!strcmp(str, "A {204080}l{1C3870}o{183060}n{142850}g{102040}e{0C1830}r{081020} {040810}s{000000}tring."));
	ASSERT(!strcmp(str, "A l{1C3870}on{142850}g{102040}er {040810}string."));
	ASSERT(colourLocations[1] == 0x20408000 | _:e_TEXT_RENDER_COLOUR_LINE);
	ASSERT(colourLocations[3] == 0x18306000 | _:e_TEXT_RENDER_COLOUR_LINE);
	ASSERT(colourLocations[5] == 0x0C183000 | _:e_TEXT_RENDER_COLOUR_LINE);
	// printf("%x", colourLocations[1]);
	// printf("%x", colourLocations[3]);
	// printf("%x", colourLocations[5]);
}






Test:TextR_ResolvePending0()
{
	state y_text_colour : y_text_colour_scm;
	new
		oldColour,
		str[64] = "{222222}Hello There",
		colourLocations[] = {0,
			-1, 65536};
	ASSERT(TextR_ResolvePending(str, sizeof (str), 13, colourLocations, 2, 0xAABBCC99, 0, oldColour) == 8);
	ASSERT(!strcmp(str, "{222222}Hello {AABACC}There"));
}

Test:TextR_ResolvePending1()
{
	state y_text_colour : y_text_colour_scm;
	new
		oldColour,
		str[64] = "{222222}Hello    There",
		colourLocations[] = {0,
			-1, 65536};
	ASSERT(TextR_ResolvePending(str, sizeof (str), 13, colourLocations, 2, 0xAABBCC99, 0, oldColour) == 8);
	ASSERT(!strcmp(str, "{222222}Hello    {AABACC}There"));
}

Test:TextR_ResolvePending2()
{
	state y_text_colour : y_text_colour_scm;
	new
		oldColour,
		str[64] = "{222222}Hello      There",
		colourLocations[] = {0,
			-1, 65536};
	ASSERT(TextR_ResolvePending(str, sizeof (str), 13, colourLocations, 2, 0xAABBCC99, 0, oldColour) == 8);
	ASSERT(!strcmp(str, "{222222}Hello      {AABACC}There"));
}

Test:TextR_ResolvePending3()
{
	state y_text_colour : y_text_colour_scm;
	new
		oldColour,
		str[64] = "{222222}Hello      There",
		colourLocations[] = {0,
			-1, 16};
	ASSERT(TextR_ResolvePending(str, sizeof (str), 13, colourLocations, 2, 0xAABBCC99, 0, oldColour) == 0);
	ASSERT(!strcmp(str, "{222222}Hello      There"));
}

Test:TextR_ResolvePending4()
{
	state y_text_colour : y_text_colour_scm;
	new
		oldColour,
		str[64] = "{222222}Hello      ",
		colourLocations[] = {0,
			-1, 65536};
	ASSERT(TextR_ResolvePending(str, sizeof (str), 13, colourLocations, 2, 0xAABBCC99, 0, oldColour) == 0);
	ASSERT(!strcmp(str, "{222222}Hello      "));
}

Test:TextR_ResolvePending5()
{
	state y_text_colour : y_text_colour_scm;
	new
		str[64] = "{222222}Hello      There",
		colourLocations[] = {0,
			0xFEFEFE00, 16,
			-1, 65536},
		bool:pending,
		oldColour = 0x22222200;
	ASSERT(TextR_ResolvePending(str, sizeof (str), 13, colourLocations, 2, 0xAABBCC99, 0, oldColour) == 0);
	ASSERT(!strcmp(str, "{222222}Hello      There"));
	ASSERT(TextR_InsertColour(str, sizeof (str), colourLocations[2], oldColour, colourLocations[1], pending) == 0);
	ASSERT(!strcmp(str, "{222222}Hello      There"));
	ASSERT(pending == true);
	ASSERT(TextR_ResolvePending(str, sizeof (str), 13, colourLocations, 4, colourLocations[1], 0, oldColour) == 8);
	ASSERT(!strcmp(str, "{222222}Hello      {FEFEFE}There"));
}

Test:TextR_ResolvePending6()
{
	state y_text_colour : y_text_colour_scm;
	new
		str[64] = "{222222}Hello      There",
		colourLocations[] = {0,
			0x22222200, 16,
			-1, 65536},
		bool:pending,
		oldColour = 0x22222200;
	ASSERT(TextR_ResolvePending(str, sizeof (str), 13, colourLocations, 2, 0xAABBCC99, 0, oldColour) == 0);
	ASSERT(!strcmp(str, "{222222}Hello      There"));
	ASSERT(TextR_InsertColour(str, sizeof (str), colourLocations[2], oldColour, colourLocations[1], pending) == 0);
	ASSERT(!strcmp(str, "{222222}Hello      There"));
	ASSERT(pending == false);
}

Test:TextR_ResolvePending7()
{
	state y_text_colour : y_text_colour_scm;
	new
		str[64] = "{222222}Hello      There",
		colourLocations[] = {0,
			0xFEFEFE00, 16,
			-1, 65536},
		bool:pending,
		oldColour = 0x22222200;
	ASSERT(TextR_ResolvePending(str, sizeof (str), 13, colourLocations, 2, 0xAABBCC99, 0, oldColour) == 0);
	ASSERT(!strcmp(str, "{222222}Hello      There"));
	ASSERT(TextR_InsertColour(str, sizeof (str), colourLocations[2], oldColour, colourLocations[1], pending) == 0);
	ASSERT(!strcmp(str, "{222222}Hello      There"));
	ASSERT(pending == true);
	ASSERT(TextR_ResolvePending(str, sizeof (str), 13, colourLocations, 4, colourLocations[1], 0, oldColour) == 8);
	ASSERT(!strcmp(str, "{222222}Hello      {FEFEFE}There"));
}


Test:TextR_NoFadeSCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		str[64] = "Hello There",
		bool:pending,
		curColour = -1;
	ASSERT(TextR_DoStraightFade(str, sizeof (str), curColour, 0, 0xABCDEF00, 10, 0xABCDEF00, pending) == 8);
	ASSERT(!strcmp(str, "{AACCEE}Hello There"));
	ASSERT(curColour == 0xAACCEE00);
	ASSERT(TextR_InsertColour(str, sizeof (str), 10, curColour, 0xABCDEF00, pending) == 0);
	ASSERT(!strcmp(str, "{AACCEE}Hello There"));
	ASSERT(curColour == 0xAACCEE00);
}

Test:TextR_GetSlotColour()
{
	// {/}
	ASSERT(TextR_GetSlotColour(_:e_TEXT_RENDER_COLOUR_END, 0xFF00BBAA, 0xCCDDEEBB) == 0xFF00BBAA);
	ASSERT(TextR_GetSlotColour(0x12345678 | _:e_TEXT_RENDER_COLOUR_END, 0xFF00BBAA, 0xCCDDEEBB) == 0xFF00BBAA);
	ASSERT(TextR_GetSlotColour(0x01 | _:e_TEXT_RENDER_COLOUR_END, 0xFF00BBAA, 0xCCDDEEBB) == 0xFF00BBAA);
	ASSERT(TextR_GetSlotColour(_:e_TEXT_RENDER_COLOUR_STAR | _:e_TEXT_RENDER_COLOUR_END, 0xFF00BBAA, 0xCCDDEEBB) == 0xFF00BBAA);
	// {*}
	ASSERT(TextR_GetSlotColour(_:e_TEXT_RENDER_COLOUR_STAR, 0xFF00BBAA, 0xCCDDEEBB) == 0xFEFEFE00);
	ASSERT(TextR_GetSlotColour((0x09876543 & _:e_TEXT_RENDER_COLOUR_MASK) | _:e_TEXT_RENDER_COLOUR_STAR, 0xFF00BBAA, 0xCCDDEEBB) == 0xFEFEFE00);
	ASSERT(TextR_GetSlotColour(0x01 | _:e_TEXT_RENDER_COLOUR_STAR, 0xFF00BBAA, 0xCCDDEEBB) == 0xFEFEFE00);
	// "\n"
	ASSERT(TextR_GetSlotColour(0, 0xFF00BBAA, 0xCCDDEEBB) == 0xCCDDEEBB);
	ASSERT(TextR_GetSlotColour(_:e_TEXT_RENDER_COLOUR_LINE, 0xFF00BBAA, 0xCCDDEEBB) == 0xCCDDEEBB);
	ASSERT(TextR_GetSlotColour(_:e_TEXT_RENDER_COLOUR_LINE | _:e_TEXT_RENDER_COLOUR_FADE, 0xFF00BBAA, 0xCCDDEEBB) == 0xCCDDEEBB);
	ASSERT(TextR_GetSlotColour(_:e_TEXT_RENDER_COLOUR_FADE, 0xFF00BBAA, 0xCCDDEEBB) == 0xCCDDEEBB);
	// {XXXXXX}
	ASSERT(TextR_GetSlotColour((0x771234AB & _:e_TEXT_RENDER_COLOUR_MASK), 0xFF00BBAA, 0xCCDDEEBB) == (0x771234AB & _:e_TEXT_RENDER_COLOUR_MASK));
	ASSERT(TextR_GetSlotColour((0x771234AB & _:e_TEXT_RENDER_COLOUR_MASK) | _:e_TEXT_RENDER_COLOUR_LINE, 0xFF00BBAA, 0xCCDDEEBB) == (0x771234AB & _:e_TEXT_RENDER_COLOUR_MASK));
	ASSERT(TextR_GetSlotColour((0x771234AB & _:e_TEXT_RENDER_COLOUR_MASK) | _:e_TEXT_RENDER_COLOUR_LINE | _:e_TEXT_RENDER_COLOUR_FADE, 0xFF00BBAA, 0xCCDDEEBB) == (0x771234AB & _:e_TEXT_RENDER_COLOUR_MASK));
	ASSERT(TextR_GetSlotColour((0x771234AB & _:e_TEXT_RENDER_COLOUR_MASK) | _:e_TEXT_RENDER_COLOUR_FADE, 0xFF00BBAA, 0xCCDDEEBB) == (0x771234AB & _:e_TEXT_RENDER_COLOUR_MASK));
}

Test:TextR_DoOneColour0SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		str[64] = "This is a string to test :D.",
		len = sizeof (str),
		offset = 0,
		colourLocations[] = {0,
			0xFEF00000, 5,
			0xAA882200, 10,
			0x12345678, 15,
			-1, 65536},
		idx = 2,
		curColour = 0,
		initialColour = 0xFE001000;
	while (colourLocations[idx] != 65536)
	{
		offset += TextR_DoOneColour(str, len, offset, colourLocations, idx, curColour, initialColour);
		idx += 2;
	}
	ASSERT(!strcmp(str, "This {FEF000}is a {AA8822}strin{123456}g to test :D."));
	ASSERT(offset == 24);
	ASSERT(idx == 8);
	ASSERT(curColour == 0x12345600);
}

Test:TextR_DoOneColour1SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		str[64] = "This is a string to test :D.",
		len = sizeof (str),
		offset = 0,
		colourLocations[] = {0,
			0xFEF00000, 4,
			0xAA882200, 9,
			0x12345678, 16,
			-1, 65536},
		idx = 2,
		curColour = 0,
		initialColour = 0xFE001000;
	while (colourLocations[idx] != 65536)
	{
		offset += TextR_DoOneColour(str, len, offset, colourLocations, idx, curColour, initialColour);
		idx += 2;
	}
	//printf(str);
	ASSERT(!strcmp(str, "This {FEF000}is a {AA8822}string {123456}to test :D."));
	ASSERT(offset == 24);
	ASSERT(idx == 8);
	ASSERT(curColour == 0x12345600);
}

Test:TextR_DoOneColour2SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		str[64] = "This is a string to test :D.",
		len = sizeof (str),
		offset = 0,
		colourLocations[] = {0,
			0xFEF00000, 9,
			0xAA882200, 10,
			0x12345678, 15,
			-1, 65536},
		idx = 2,
		curColour = 0,
		initialColour = 0xFE001000;
	while (colourLocations[idx] != 65536)
	{
		offset += TextR_DoOneColour(str, len, offset, colourLocations, idx, curColour, initialColour);
		idx += 2;
	}
	ASSERT(!strcmp(str, "This is a {AA8822}strin{123456}g to test :D."));
	ASSERT(offset == 16);
	ASSERT(idx == 8);
	ASSERT(curColour == 0x12345600);
}

Test:TextR_DoOneColour3SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		str[100] = "This is a string to test :D.",
		len = sizeof (str),
		offset = 0,
		colourLocations[] = {0,
			0x00000002 | _:e_TEXT_RENDER_COLOUR_FADE, 5,
			0x0A0A0A00, 10,
			0x12345678, 15,
			-1, 65536},
		idx = 2,
		curColour = -1,
		initialColour = 0xFE001000;
	while (colourLocations[idx] != 65536)
	{
		offset += TextR_DoOneColour(str, len, offset, colourLocations, idx, curColour, initialColour);
		idx += 2;
	}
	//printf(str);
	ASSERT(!strcmp(str, "This {000000}i{020202}s {060606}a {0A0A0A}strin{123456}g to test :D."));
	ASSERT(offset == 40);
	ASSERT(idx == 8);
	ASSERT(curColour == 0x12345600);
}

Test:TextR_DoOneColour4SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		str[64] = "This is a string to test :D.",
		len = sizeof (str),
		offset = 0,
		colourLocations[] = {0,
			0x00000002 | _:e_TEXT_RENDER_COLOUR_FADE, 5,
			0x0A0A0A00 | _:e_TEXT_RENDER_COLOUR_LINE, 10,
			0x12345678, 15,
			-1, 65536},
		idx = 2,
		curColour = -1,
		initialColour = 0xFE001000;
	while (colourLocations[idx] != 65536)
	{
		offset += TextR_DoOneColour(str, len, offset, colourLocations, idx, curColour, initialColour);
		idx += 2;
	}
	//printf(str);
	ASSERT(!strcmp(str, "This {000000}i{020202}s {060606}a strin{123456}g to test :D."));
	ASSERT(offset == 32);
	ASSERT(idx == 8);
	ASSERT(curColour == 0x12345600);
}

Test:TextR_DoOneColour3bSCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		str[64] = "This is a string to test :D.",
		len = sizeof (str),
		offset = 0,
		colourLocations[] = {0,
			0x0000000 | _:e_TEXT_RENDER_COLOUR_FADE, 5,
			0x0A0A0A00, 10,
			0x12345678, 15,
			-1, 65536},
		idx = 2,
		curColour = 0,
		initialColour = 0xFE001000;
	while (colourLocations[idx] != 65536)
	{
		offset += TextR_DoOneColour(str, len, offset, colourLocations, idx, curColour, initialColour);
		idx += 2;
	}
	//printf(str);
	ASSERT(!strcmp(str, "This i{020202}s {060606}a {0A0A0A}strin{123456}g to test :D."));
	ASSERT(offset == 32);
	ASSERT(idx == 8);
	ASSERT(curColour == 0x12345600);
}

Test:TextR_DoOneColour4bSCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		str[64] = "This is a string to test :D.",
		len = sizeof (str),
		offset = 0,
		colourLocations[] = {0,
			0x00000002 | _:e_TEXT_RENDER_COLOUR_FADE, 5,
			0x0A0A0A00 | _:e_TEXT_RENDER_COLOUR_LINE, 10,
			0x12345678, 15,
			-1, 65536},
		idx = 2,
		curColour = 0,
		initialColour = 0xFE001000;
	while (colourLocations[idx] != 65536)
	{
		offset += TextR_DoOneColour(str, len, offset, colourLocations, idx, curColour, initialColour);
		idx += 2;
	}
	//printf(str);
	ASSERT(!strcmp(str, "This i{020202}s {060606}a strin{123456}g to test :D."));
	ASSERT(offset == 24);
	ASSERT(idx == 8);
	ASSERT(curColour == 0x12345600);
}

Test:TextR_DoOneColour5SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		str[64] = "This is a string to test :D.",
		len = sizeof (str),
		offset = 0,
		colourLocations[] = {0,
			0x00000002 | _:e_TEXT_RENDER_COLOUR_FADE, 5,
			_:e_TEXT_RENDER_COLOUR_LINE, 6,
			0x0A0A0A00 | _:e_TEXT_RENDER_COLOUR_LINE, 10,
			0x12345678, 15,
			-1, 65536},
		idx = 2,
		curColour = -1,
		initialColour = 0xFE001000;
	while (colourLocations[idx] != 65536)
	{
		offset += TextR_DoOneColour(str, len, offset, colourLocations, idx, curColour, initialColour);
		idx += 2;
	}
	ASSERT(!strcmp(str, "This {000000}is {060606}a strin{123456}g to test :D."));
	ASSERT(offset == 24);
	ASSERT(idx == 10);
	ASSERT(curColour == 0x12345600);
	ASSERT(colourLocations[3] == 0x02020200 | _:e_TEXT_RENDER_COLOUR_LINE);
}

Test:TextR_DoOneColour6SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		str[64] = "This is a string to test :D.",
		len = sizeof (str),
		offset = 0,
		colourLocations[] = {0,
			0x00000002, 5,
			_:e_TEXT_RENDER_COLOUR_LINE, 6,
			0x0A0A0A00 | _:e_TEXT_RENDER_COLOUR_LINE, 10,
			_:e_TEXT_RENDER_COLOUR_END, 15,
			-1, 65536},
		idx = 2,
		curColour = 0,
		initialColour = 0xFE001000;
	while (colourLocations[idx] != 65536)
	{
		offset += TextR_DoOneColour(str, len, offset, colourLocations, idx, curColour, initialColour);
		idx += 2;
	}
	ASSERT(!strcmp(str, "This is a strin{FE0010}g to test :D."));
	ASSERT(offset == 8);
	ASSERT(idx == 10);
	ASSERT(curColour == 0xFE001000);
	ASSERT(colourLocations[3] == 0x00000000 | _:e_TEXT_RENDER_COLOUR_LINE);
	ASSERT(colourLocations[4] == 6);
	ASSERT(colourLocations[6] == 10);
}

Test:TextR_DoOneColour7SCM()
{
	state y_text_colour : y_text_colour_scm;
	new
		str[64] = "This is a string to test :D.",
		len = sizeof (str),
		offset = 0,
		colourLocations[] = {0,
			_:e_TEXT_RENDER_COLOUR_STAR | _:e_TEXT_RENDER_COLOUR_FADE, 5,
			_:e_TEXT_RENDER_COLOUR_LINE, 6,
			_:e_TEXT_RENDER_COLOUR_END | _:e_TEXT_RENDER_COLOUR_LINE, 10,
			_:e_TEXT_RENDER_COLOUR_END, 15,
			-1, 65536},
		idx = 2,
		curColour = 0,
		initialColour = 0xF4F4F400;
	while (colourLocations[idx] != 65536)
	{
		//printf("cc: %04x%04x", curColour >>> 16, curColour & 0xFFFF);
		offset += TextR_DoOneColour(str, len, offset, colourLocations, idx, curColour, initialColour);
		idx += 2;
	}
	//printf(str);
	ASSERT(!strcmp(str, "This {FEFEFE}is {F8F8F8}a string to test :D."));
	ASSERT(offset == 16);
	ASSERT(idx == 10);
	ASSERT(curColour == 0xF4F4F400);
	ASSERT(colourLocations[4] == 6);
	ASSERT(colourLocations[6] == 10);
	ASSERT(colourLocations[3] == 0xFCFCFC00 | _:e_TEXT_RENDER_COLOUR_LINE);
	ASSERT(colourLocations[5] == 0xF4F4F400 | _:e_TEXT_RENDER_COLOUR_LINE);
}

/*Test:TextR_FindLast()
{
	ASSERT(TextR_FindLast("Hello", 1, " ") == -1);
	ASSERT(TextR_FindLast("Hello", 5, " ") == -1);
	ASSERT(TextR_FindLast("Hello", 55, " ") == -1);
	ASSERT(TextR_FindLast("Hello There", 1, " ") == -1);
	ASSERT(TextR_FindLast("Hello There", 5, " ") == -1);
	ASSERT(TextR_FindLast("Hello There", 55, " ") == 5);
	ASSERT(TextR_FindLast(" Hello There", 1, " ") == 0);
	ASSERT(TextR_FindLast(" Hello There", 5, " ") == 0);
	ASSERT(TextR_FindLast(" Hello There", 55, " ") == 6);
	ASSERT(TextR_FindLast("::::", 4, ":") == 3);
	ASSERT(TextR_FindLast("iii:", 4, ":") == 3);
	ASSERT(TextR_FindLast("i:i:", 4, ":") == 3);
	ASSERT(TextR_FindLast("i:i:", 4, ":") == 3);
	ASSERT(TextR_FindLast(":::::", 4, ":") == 3);
	ASSERT(TextR_FindLast(":::::::", 4, ":") == 3);
	ASSERT(TextR_FindLast(":::::::", 5, ":") == 4);
	ASSERT(TextR_FindLast(":::::::", 6, ":") == 5);
	ASSERT(TextR_FindLast(":::::::", 7, ":") == 6);
	ASSERT(TextR_FindLast(":::::::", 7, ":") == 6);
}

Test:TextR_RTrim()
{
	ASSERT(TextR_RTrim("Hello   ", 0, 8) == 5);
	ASSERT(TextR_RTrim("Hello   ", 0, 7) == 5);
	ASSERT(TextR_RTrim("Hello   ", 1, 8) == 5);
	ASSERT(TextR_RTrim("Hello   ", 1, 7) == 5);
	ASSERT(TextR_RTrim("Hello   ", 1, 5) == 5);
	ASSERT(TextR_RTrim("Hello   ", 1, 4) == 4);
	ASSERT(TextR_RTrim("Hello   ", 0, 4) == 4);
	ASSERT(TextR_RTrim("Hello", 0, 5) == 5);
	ASSERT(TextR_RTrim("      ", 0, 5) == 0);
	ASSERT(TextR_RTrim("      ", 0, 6) == 0);
	ASSERT(TextR_RTrim("      ", 1, 5) == 1);
	ASSERT(TextR_RTrim("      ", 1, 6) == 1);
	ASSERT(TextR_RTrim("1     ", 1, 6) == 1);
	ASSERT(TextR_RTrim("11    ", 1, 6) == 2);
}*/




Test:TextR_SkipChars()
{
	ASSERT(TextR_SkipChars("", 0, 0) == 0);
	ASSERT(TextR_SkipChars("Hello World", 0, 1) == 1);
	ASSERT(TextR_SkipChars("Hello World", 5, 1) == 6);
	ASSERT(TextR_SkipChars("{112233}Hello World", 0, 3) == 11);
	ASSERT(TextR_SkipChars("{112233}H{112233}e{112233}llo World", 0, 3) == 27);
	ASSERT(TextR_SkipChars("{112233}H{112233}e{112233}llo World", 8, 3) == 27);
	ASSERT(TextR_SkipChars("{112233}H{112233}e{112233}llo World", 9, 3) == 28);
}

Test:TextR_CountCharsFore()
{
	ASSERT(TextR_CountCharsFore("", 0) == 0);
	ASSERT(TextR_CountCharsFore("{112233}", 0) == 0);
	ASSERT(TextR_CountCharsFore("Hello", 0) == 5);
	ASSERT(TextR_CountCharsFore("Hello There", 0) == 5);
	ASSERT(TextR_CountCharsFore("{112233}Hello There", 0) == 5);
	ASSERT(TextR_CountCharsFore("{xxyyzz}Hello There", 0) == 6);
	ASSERT(TextR_CountCharsFore("Hello_There", 0) == 6);
	ASSERT(TextR_CountCharsFore("{112233}Hello_There", 0) == 6);
	ASSERT(TextR_CountCharsFore("He{112233}llo_There", 0) == 6);
	ASSERT(TextR_CountCharsFore("He{112233}ll{112233}o_There", 0) == 6);
	ASSERT(TextR_CountCharsFore("He{112233}ll{112233}o_{112233}There", 0) == 6);
	ASSERT(TextR_CountCharsFore("{112233}H{112233}e{112233}l{112233}l{112233}o There", 0) == 5);
}

Test:TextR_CountCharsBack()
{
	new str[100], pos;
	str = "                ", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 0);
	ASSERT(pos == 16);
	str = "                {112233}x", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 1);
	ASSERT(pos == 16);
	str = "                Hello", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 5);
	ASSERT(pos == 16);
	str = "                Hello There", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 5);
	ASSERT(pos == 22);
	str = "                {112233}Hello There", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 5);
	ASSERT(pos == 30);
	str = "                {xxyyzz}Hello There", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 5);
	ASSERT(pos == 30);
	str = "                Hello_There", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 10);
	ASSERT(pos == 17);
	str = "                {112233}Hello_There", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 10);
	ASSERT(pos == 25);
	str = "                He{112233}llo_There", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 10);
	ASSERT(pos == 17);
	str = "                He{112233}ll{112233}o_There", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 10);
	ASSERT(pos == 17);
	str = "                He{112233}ll{112233}o_{112233}There", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 10);
	ASSERT(pos == 17);
	str = "                {112233}H{112233}e{112233}l{112233}l{112233}o There", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 5);
	ASSERT(pos == 62);
	str = "                {112233}H{112233}e{112233}l{112233}l{112233}o_There", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 10);
	ASSERT(pos == 25);
	str = "                Hello {xxyyzz}There", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 10);
	ASSERT(pos == 25);
	str = "                Hello {112233}There", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 5);
	ASSERT(pos == 22);
	str = "                Hello {112233}The{112233}re", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 5);
	ASSERT(pos == 22);
	str = "                Hello Th{112233}er{112233}e", pos = strlen(str);
	ASSERT(TextR_CountCharsBack(str, pos) == 5);
	ASSERT(pos == 22);
}

Test:TextR_LTrim()
{
	ASSERT(TextR_LTrim("", 0) == 0);
	ASSERT(TextR_LTrim("Hello", 0) == 0);
	ASSERT(TextR_LTrim(" Hello", 0) == 1);
	ASSERT(TextR_LTrim(" Hello", 1) == 1);
	ASSERT(TextR_LTrim("    Hello", 0) == 4);
	ASSERT(TextR_LTrim("    Hello", 2) == 4);
	ASSERT(TextR_LTrim("    Hello", 4) == 4);
	ASSERT(TextR_LTrim("     ", 0) == 5);
	ASSERT(TextR_LTrim("     ", 5) == 5);
}

Test:TextR_RTrim()
{
	ASSERT(TextR_RTrim("", 0) == 0);
	ASSERT(TextR_RTrim("hi  ", 4) == 2);
	ASSERT(TextR_RTrim("    ", 4) == 0);
	ASSERT(TextR_RTrim("    ", 2) == 0);
	ASSERT(TextR_RTrim("  ", 2) == 0);
	ASSERT(TextR_RTrim("  hi", 2) == 0);
	ASSERT(TextR_RTrim("  hi", 4) == 4);
}

Test:TextR_GetSplitPoint0()
{
	new
		str[64],
		start,
		end;
	// Split falls in a space.
	str = "Hello There";
	TextR_GetSplitPoint(str, 5, 64, end, start);
	ASSERT(!strcmp(str, "Hello There"));
	ASSERT(end == 5);
	ASSERT(start == 6);
	// 
	str = "Hello    There";
	TextR_GetSplitPoint(str, 5, 64, end, start);
	ASSERT(!strcmp(str, "Hello    There"));
	ASSERT(end == 5);
	ASSERT(start == 9);
	// 
	str = "Hello    There";
	TextR_GetSplitPoint(str, 6, 64, end, start);
	ASSERT(!strcmp(str, "Hello    There"));
	ASSERT(end == 5);
	ASSERT(start == 9);
	// 
	str = "Hello    There";
	TextR_GetSplitPoint(str, 7, 64, end, start);
	ASSERT(!strcmp(str, "Hello    There"));
	ASSERT(end == 5);
	ASSERT(start == 9);
	// 
	str = "Hello    There";
	TextR_GetSplitPoint(str, 9, 64, end, start);
	ASSERT(!strcmp(str, "Hello    There"));
	ASSERT(end == 5);
	ASSERT(start == 9);
	// 
}

Test:TextR_GetSplitPoint1()
{
	new
		str[64],
		start,
		end;
	// Split falls in a colour.
	str = "Hello {098765}There";
	TextR_GetSplitPoint(str, 10, 64, end, start);
	ASSERT(!strcmp(str, "Hello {098765}There"));
	ASSERT(end == 5);
	ASSERT(start == 14);
	// 
	str = "Hello   {098765}There";
	TextR_GetSplitPoint(str, 10, 64, end, start);
	ASSERT(!strcmp(str, "Hello   {098765}There"));
	ASSERT(end == 5);
	ASSERT(start == 16);
	// 
	str = "Hello   {098765}There";
	TextR_GetSplitPoint(str, 8, 64, end, start);
	ASSERT(!strcmp(str, "Hello   {098765}There"));
	ASSERT(end == 5);
	ASSERT(start == 16);
	// 
	str = "Hello   {098765}There";
	TextR_GetSplitPoint(str, 16, 64, end, start);
	ASSERT(!strcmp(str, "Hello   {098765}There"));
	ASSERT(end == 5);
	ASSERT(start == 16);
	// 
	str = "Hello   {098765}There";
	TextR_GetSplitPoint(str, 9, 64, end, start);
	ASSERT(!strcmp(str, "Hello   {098765}There"));
	ASSERT(end == 5);
	ASSERT(start == 16);
	// 
	str = "Hello   {098765}There";
	TextR_GetSplitPoint(str, 15, 64, end, start);
	ASSERT(!strcmp(str, "Hello   {098765}There"));
	ASSERT(end == 5);
	ASSERT(start == 16);
	//
	str = "Hello   {098765}There";
	TextR_GetSplitPoint(str, 6, 64, end, start);
	ASSERT(!strcmp(str, "Hello   {098765}There"));
	ASSERT(end == 5);
	ASSERT(start == 16);
	//
	str = "Hello   {098765}There";
	TextR_GetSplitPoint(str, 7, 64, end, start);
	ASSERT(!strcmp(str, "Hello   {098765}There"));
	ASSERT(end == 5);
	ASSERT(start == 16);
	//
	str = "Hello   {098765}There";
	TextR_GetSplitPoint(str, 8, 64, end, start);
	ASSERT(!strcmp(str, "Hello   {098765}There"));
	ASSERT(end == 5);
	ASSERT(start == 16);
	//
}

Test:TextR_GetSplitPoint2()
{
	new
		str[64],
		start,
		end;
	// Split falls near the start of a word.
	str = "Other Hello_There";
	TextR_GetSplitPoint(str, 8, 64, end, start);
	ASSERT(!strcmp(str, "Other Hello_There"));
	ASSERT(end == 6);
	ASSERT(start == 6);
	// 
	str = "Other Hello_There";
	TextR_GetSplitPoint(str, 9, 64, end, start);
	ASSERT(!strcmp(str, "Other Hello_There"));
	ASSERT(end == 6);
	ASSERT(start == 6);
	// 
	str = "Other Hello_There";
	TextR_GetSplitPoint(str, 9, 64, end, start);
	ASSERT(!strcmp(str, "Other Hello_There"));
	ASSERT(end == 6);
	ASSERT(start == 6);
	// 
	str = "Other Hello";
	TextR_GetSplitPoint(str, 10, 64, end, start);
	ASSERT(!strcmp(str, "Other Hello"));
	ASSERT(end == 6);
	ASSERT(start == 6);
	// 
	str = "Other Hello There";
	TextR_GetSplitPoint(str, 10, 64, end, start);
	ASSERT(!strcmp(str, "Other Hello There"));
	ASSERT(end == 6);
	ASSERT(start == 6);
	// 
}

Test:TextR_GetSplitPoint3()
{
	new
		str[64],
		start,
		end;
	// Split falls near the middle of a word.
	str = "Other Hello_There";
	TextR_GetSplitPoint(str, 10, 64, end, start);
	ASSERT(!strcmp(str, "Other Hel-lo_There"));
	ASSERT(end == 10);
	ASSERT(start == 10);
	// 
	str = "Other Hello_There_Very_Long";
	TextR_GetSplitPoint(str, 10, 64, end, start);
	ASSERT(!strcmp(str, "Other Hel-lo_There_Very_Long"));
	ASSERT(end == 10);
	ASSERT(start == 10);
	// 
	str = "Other Hello_There_Very_Long";
	TextR_GetSplitPoint(str, 12, 64, end, start);
	ASSERT(!strcmp(str, "Other Hello-_There_Very_Long"));
	ASSERT(end == 12);
	ASSERT(start == 12);
	// 
	str = "Other Hello_There_Very_Long";
	TextR_GetSplitPoint(str, 13, 64, end, start);
	ASSERT(!strcmp(str, "Other Hello_-There_Very_Long"));
	ASSERT(end == 13);
	ASSERT(start == 13);
	// 
	str = "Other Hello_There_Very_Long";
	TextR_GetSplitPoint(str, 24, 64, end, start);
	ASSERT(!strcmp(str, "Other Hello_There_Ve-ry_Long"));
	ASSERT(end == 21);
	ASSERT(start == 21);
	// 
}

Test:TextR_GetSplitPoint4()
{
	new
		str[64],
		start,
		end;
	// Split has colours.
	str = "Other He{654321}llo";
	TextR_GetSplitPoint(str, 8, 64, end, start);
	ASSERT(!strcmp(str, "Other He{654321}llo"));
	ASSERT(end == 6);
	ASSERT(start == 6);
	// 
	str = "Other He{654321}llo";
	TextR_GetSplitPoint(str, 16, 64, end, start);
	ASSERT(!strcmp(str, "Other He{654321}llo"));
	ASSERT(end == 6);
	ASSERT(start == 6);
	// 
	str = "Other He{654321}llo";
	TextR_GetSplitPoint(str, 17, 64, end, start);
	ASSERT(!strcmp(str, "Other He{654321}llo"));
	ASSERT(end == 6);
	ASSERT(start == 6);
	// 
	str = "Other He{654321}lloo";
	TextR_GetSplitPoint(str, 17, 64, end, start);
	ASSERT(!strcmp(str, "Other He{654321}lloo"));
	ASSERT(end == 6);
	ASSERT(start == 6);
	// 
	str = "Other He{654321}lloo0";
	TextR_GetSplitPoint(str, 17, 64, end, start);
	ASSERT(!strcmp(str, "Other He{654321}lloo0"));
	ASSERT(end == 6);
	ASSERT(start == 6);
	// 
	str = "Other He{654321}lloo0";
	TextR_GetSplitPoint(str, 18, 64, end, start);
	ASSERT(!strcmp(str, "Other He{654321}l-loo0"));
	ASSERT(end == 18);
	ASSERT(start == 18);
	// 
	str = "Other He{654321}lloo_L{567890}ong";
	TextR_GetSplitPoint(str, 21, 64, end, start);
	ASSERT(!strcmp(str, "Other He{654321}llo-o_L{567890}ong"));
	ASSERT(end == 20);
	ASSERT(start == 20);
	// 
}

Test:TextR_GetSplitPoint5()
{
	new
		str[64],
		start,
		end;
	// Split has many colours.
	str = "Other {654321}H{654321}e{654321}l{654321}l{654321}o";
	TextR_GetSplitPoint(str, 38, 64, end, start);
	ASSERT(!strcmp(str, "Other {654321}H{654321}e{654321}l{654321}l{654321}o"));
	ASSERT(end == 6);
	ASSERT(start == 14);
	// 
	str = "Other {654321}H{654321}e{654321}l{654321}l{654321}o{654321}2";
	TextR_GetSplitPoint(str, 42, 64, end, start);
	ASSERT(!strcmp(str, "Other {654321}H{654321}e{654321}l-{654321}l{654321}o{654321}2"));
	ASSERT(end == 34);
	ASSERT(start == 42);
	// 
}

Test:TextR_IsColour()
{
	new str[16];
	ASSERT(TextR_IsColour("{123456}"));
	ASSERT(TextR_IsColour("{AABBCC}"));
	ASSERT(TextR_IsColour("{0A0B04}"));
	ASSERT(!TextR_IsColour("{12345}"));
	ASSERT(!TextR_IsColour("{00000G}"));
	ASSERT(!TextR_IsColour("{00000#}"));
	ASSERT(!TextR_IsColour("{@12345}"));
	str = "{{12345}"; // Doesn't work in "ASSERT".
	ASSERT(!TextR_IsColour(str));
	ASSERT(!TextR_IsColour("{2212345}"));
	ASSERT(!TextR_IsColour("{0KBEEF}"));
	ASSERT(TextR_IsColour("{BDBEEF}"));
	str = "BDBEEF}";
	ASSERT(!TextR_IsColour(str));
	str = "{BDBEEF";
	ASSERT(!TextR_IsColour(str));
	ASSERT(!TextR_IsColour("BDBEEF"));
	ASSERT(!TextR_IsColour(""));
}


Test:zzz_TextR_RunPhase2_0()
{
	new
		colourLocations[] = {0xFEFEFE00,
			0xAAAAAAAA | _:e_TEXT_RENDER_COLOUR_FADE, 10,
			0x22222222, 20,
			0, 65536},
		str[128] = "Hello there, how are you?  This is quite long";
	TextR_RunPhase2(str, sizeof (str), colourLocations);
	//print(str);
	//printf("%d %d", colourLocations[2], colourLocations[4]);
	ASSERT(colourLocations[2] == 10);
	ASSERT(colourLocations[4] == 84);
	ASSERT(!strcmp(str, "Hello ther{AAAAAA}e{9C9C9C}, {808080}h{727272}o{666666}w {4A4A4A}a{3C3C3C}r{2E2E2E}e {222222}you?  This is quite long"));
}

Test:zzz_TextR_RunPhase2_1()
{
	new
		colourLocations[] = {0xFEFEFE00,
			0xAAAAAAAA | _:e_TEXT_RENDER_COLOUR_FADE, 10,
			0x22222222 | _:e_TEXT_RENDER_COLOUR_LINE, 20,
			0, 65536},
		str[128] = "Hello there, how are you?  This is quite long";
	TextR_RunPhase2(str, sizeof (str), colourLocations);
	//print(str);
	//printf("%d %d", colourLocations[2], colourLocations[4]);
	ASSERT(colourLocations[2] == 10);
	ASSERT(colourLocations[4] == 84);
	ASSERT(!strcmp(str, "Hello ther{AAAAAA}e{9C9C9C}, {808080}h{727272}o{666666}w {4A4A4A}a{3C3C3C}r{2E2E2E}e you?  This is quite long"));
	TextR_RunPhase3(str, sizeof (str), colourLocations);
}


