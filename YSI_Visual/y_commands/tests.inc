Test:y_commands_Valid()
{
	ASSERT(Command_IsValid(YCMD:y_commands_1));
	ASSERT(Command_IsValid(Command_GetID("y_commands_1")));
	// ASSERT(Command_IsValid(YCMD:y_commands_1));
}

Test:y_commands_YCMD()
{
	ASSERT(Command_GetID("y_commands_1") == _:YCMD:y_commands_1);
	ASSERT(Command_GetID("y_commands_1") != _:YCMD:y_commands_2);
	ASSERT(Command_GetID("y_commands_1") != _:YCMD:y_commands_3);
	ASSERT(Command_GetID("y_commands_DO_NOT_MAKE") == COMMAND_NOT_FOUND);
}

Test:y_commands_GetName()
{
	new
		id = Command_GetID("y_commands_1");
	ASSERT(!strcmp(Command_GetName(id), "y_commands_1"));
	ASSERT(strlen(Command_GetName(-1)) == 0);
}

Test:y_commands_AddAlt()
{
	new
		id1 = YCMD:y_commands_1,
		id2 = Command_AddAlt(id1, "y_commands_alt1"),
		id3 = Command_AddAltNamed("y_commands_1", "y_commands_alt1");
	ASSERT(id1 != id2);
	ASSERT(id2 != COMMAND_NOT_FOUND);
	ASSERT(id2 == id3);
}

Test:y_commands_Perms()
{
	new
		id = (YCMD:y_commands_1);
	Command_SetPlayer(id, 101, false);
	ASSERT(!Command_GetPlayer(id, 101));
	ASSERT(!Command_GetPlayerNamed("y_commands_1", 101));
	Command_SetPlayerNamed("y_commands_1", 101, true);
	ASSERT(Command_GetPlayer(id, 101));
	ASSERT(Command_GetPlayerNamed("y_commands_1", 101));
}

static stock
	YSI_g_sRemovableRan = 0;

YCMD:y_commands_removable(playerid, params[], help)
{
	YSI_g_sRemovableRan = 1;
	return 1;
}

Test:y_commands_removable()
{
	YSI_g_sRemovableRan = 0;
	Command_SetPlayerNamed("y_commands_removable", 103, true);
	ASSERT(call OnPlayerCommandText(103, "/y_commands_removable") == 1);
	ASSERT(YSI_g_sRemovableRan == 1);
	YSI_g_sRemovableRan = 0;
	Command_SetPlayerNamed("y_commands_removable", 103, false);
	ASSERT(call OnPlayerCommandText(103, "/y_commands_removable") == 1);
	ASSERT(YSI_g_sRemovableRan == 0);
	YSI_g_sRemovableRan = 0;
	Command_SetPlayerNamed("y_commands_removable", 103, true);
	ASSERT(call OnPlayerCommandText(103, "/y_commands_removable") == 1);
	ASSERT(YSI_g_sRemovableRan == 1);
	YSI_g_sRemovableRan = 0;
	Command_RemoveNamed("y_commands_removable");
	ASSERT(call OnPlayerCommandText(103, "/y_commands_removable") == 0);
	ASSERT(YSI_g_sRemovableRan == 0);
}

YCMD:y_commands_removable2(playerid, params[], help)
{
	return 1;
}

Test:y_commands_removable2()
{
	//printf("%d", YCMD:y_commands_removable2);
	Command_SetPlayer(YCMD:y_commands_removable2, 103, true);
	ASSERT(call OnPlayerCommandText(103, "/y_commands_removable2") == 1);
	Command_Remove(YCMD:y_commands_removable2);
	ASSERT(call OnPlayerCommandText(103, "/y_commands_removable2") == 0);
}

Test:y_commands_count()
{
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		Command_SetPlayer(i, 22, false);
	}
	ASSERT(Command_GetPlayerCommandCount(22) == 0);
	Command_SetPlayerNamed("y_commands_1", 22, true);
	ASSERT(Command_GetPlayerCommandCount(22) == 1);
}

Test:y_commands_display1()
{
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		Command_SetPlayer(i, 23, false);
	}
	ASSERT(strlen(Command_GetDisplayNamed("y_commands_1", 23)) == 0);
	Command_SetPlayerNamed("y_commands_1", 23, true);
	ASSERT(strlen(Command_GetDisplayNamed("y_commands_1", 23)) != 0);
	ASSERT(!strcmp(Command_GetDisplayNamed("y_commands_1", 23), "y_commands_1"));
}

Test:y_commands_display2()
{
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		Command_SetPlayer(i, 23, false);
	}
	ASSERT(strlen(Command_GetDisplay(YCMD:y_commands_3, 23)) == 0);
	Command_SetPlayer(YCMD:y_commands_3, 23, true);
	ASSERT(strlen(Command_GetDisplay(YCMD:y_commands_3, 23)) != 0);
	ASSERT(!strcmp(Command_GetDisplay(YCMD:y_commands_3, 23), "y_commands_3"));
}

Test:y_commands_display3()
{
	Command_AddAlt(YCMD:y_commands_3, "y_commands_alt7");
	Command_AddAlt(YCMD:y_commands_alt7, "y_commands_alt2");
	Command_AddAlt(YCMD:y_commands_alt2, "y_commands_alt3");
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		Command_SetPlayer(i, 25, false);
	}
	ASSERT(strlen(Command_GetDisplay(YCMD:y_commands_3, 25)) == 0);
	// Get a name from the original.
	Command_SetPlayer(YCMD:y_commands_alt3, 25, true);
	ASSERT(strlen(Command_GetDisplay(YCMD:y_commands_3, 25)) != 0);
	ASSERT(!strcmp(Command_GetDisplay(YCMD:y_commands_3, 25), "y_commands_alt3"));
	// Get an y_commands_alternate from a different y_commands_alternate.
	Command_SetPlayer(YCMD:y_commands_alt7, 25, true);
	ASSERT(strlen(Command_GetDisplay(YCMD:y_commands_alt2, 25)) != 0);
	ASSERT(!strcmp(Command_GetDisplay(YCMD:y_commands_alt2, 25), "y_commands_alt7"));
	// Get the original from an y_commands_alternate.
	Command_SetPlayer(YCMD:y_commands_3, 25, true);
	ASSERT(strlen(Command_GetDisplay(YCMD:y_commands_alt2, 25)) != 0);
	ASSERT(!strcmp(Command_GetDisplay(YCMD:y_commands_alt2, 25), "y_commands_3"));
}

Test:y_commands_count3()
{
	Command_AddAlt(YCMD:y_commands_1, "y_commands_alt4");
	Command_AddAlt(YCMD:y_commands_alt4, "y_commands_alt5");
	Command_AddAlt(YCMD:y_commands_alt4, "y_commands_alt6");
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		Command_SetPlayer(i, 26, false);
	}
	ASSERT(Command_GetPlayerCommandCount(26) == 0);
	Command_SetPlayer(YCMD:y_commands_1, 26, true);
	ASSERT(Command_GetPlayerCommandCount(26) == 1);
	Command_SetPlayer(YCMD:y_commands_alt4, 26, true);
	ASSERT(Command_GetPlayerCommandCount(26) == 2);
	Command_SetPlayer(YCMD:y_commands_alt5, 26, true);
	ASSERT(Command_GetPlayerCommandCount(26) == 3);
	Command_SetPlayer(YCMD:y_commands_alt6, 26, true);
	ASSERT(Command_GetPlayerCommandCount(26) == 4);
}

Test:y_commands_Hashing()
{
	new
		dst0[32],
		dst1[32],
		hash0,
		hash1;
	// CASE INSENSITIVE.
	// V1.
	Puny_Encode(dst0, "hello\x102;you", .delimiter = '@');
	HashMap_Hash(dst0, hash0);
	// V2.
	new
		len = Puny_EncodeHash(dst1, "Hello\x102;you there", hash1, .delimiter = '@');
	// Same.
	//printf("%s %s", dst0, dst1);
	ASSERT(!strcmp(dst0, dst1));
	ASSERT(hash0 == hash1);
	//ASSERT(len == strlen(dst1));
	ASSERT(len == 9);
	// CASE SENSITIVE.
	Puny_Encode(dst0, "Hello\x102;there", .delimiter = '@');
	HashMap_Hash(dst0, hash0);
	// V2.
	len = Puny_EncodeHash(dst1, "Hello\x102;there you", hash1, .delimiter = '@');
	ASSERT(!!strcmp(dst0, dst1));
	ASSERT(hash0 != hash1);
	ASSERT(len == 11);
}

static
	gSomeVar;

YCMD:y_commands_1(playerid, cmdtext[], help)
{
	return 1;
}

Test:y_commands_1()
{
	call OnPlayerConnect(142);
	ASSERT(call OnPlayerCommandText(142, "/y_commands_1") == 1);
	ASSERT(call OnPlayerCommandText(142, "/y_comMands_1") == 1);
	ASSERT(call OnPlayerCommandText(142, "/Y_COMMANDS_1") == 1);
	ASSERT(call OnPlayerCommandText(142, "/Y_commandS_1") == 1);
	ASSERT(call OnPlayerCommandText(142, "/y_Commands_1") == 1);
}

Test:y_commands_2()
{
	call OnPlayerConnect(143);
	ASSERT(call OnPlayerCommandText(143, "/y_commands__NONONONO") == 0);
	ASSERT(call OnPlayerCommandText(143, "/y_commands_0") == 0);
	ASSERT(call OnPlayerCommandText(143, "/y_comMands_2") == 0);
	ASSERT(call OnPlayerCommandText(143, "/Y_COMMANDS_2") == 0);
	ASSERT(call OnPlayerCommandText(143, "/Y_commandS_I") == 0);
	ASSERT(call OnPlayerCommandText(143, "/y_Commands_l") == 0);
}

YCMD:y_commands_3(playerid, cmdtext[], help)
{
	gSomeVar = 52;
	return 1;
}

Test:y_commands_3()
{
	call OnPlayerConnect(144);
	gSomeVar = 42;
	call OnPlayerCommandText(144, "/y_commands_3");
	ASSERT(gSomeVar == 52);
}

static stock
	YSI_gsPlayerid,
	YSI_gsParams[32],
	YSI_gsHelp;

YCMD:y_commands_reprocess(playerid, params[], help)
{
	//printf("%d %x %d", playerid, params[0], help);
	YSI_gsPlayerid = playerid;
	strcpy(YSI_gsParams, params);
	YSI_gsHelp = help;
	return 1;
}

Test:y_commands_ReProcess()
{
	call OnPlayerConnect(33);
	// 1.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	Command_ReProcess(33, "y_commands_ReProcess", 0);
	ASSERT(YSI_gsPlayerid == 33);
	ASSERT(YSI_gsParams[0] == '\0');
	ASSERT(YSI_gsHelp == 0);
	// 2.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	Command_ReProcess(33, "y_commands_ReProcess one", 1);
	ASSERT(YSI_gsPlayerid == 33);
	ASSERT(YSI_gsParams[0] != '\0');
	ASSERT(!strcmp(YSI_gsParams, "one"));
	ASSERT(YSI_gsHelp == 1);
	// 3.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	Command_ReProcess(33, "y_commands_ReProcess two and three", 0);
	ASSERT(YSI_gsPlayerid == 33);
	ASSERT(YSI_gsParams[0] != '\0');
	ASSERT(!strcmp(YSI_gsParams, "two and three"));
	ASSERT(YSI_gsHelp == 0);
	// 4.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	Command_ReProcess(33, "y_commands_ReProcess 99", 1);
	ASSERT(YSI_gsPlayerid == 33);
	ASSERT(YSI_gsParams[0] != '\0');
	ASSERT(!strcmp(YSI_gsParams, "99"));
	ASSERT(YSI_gsHelp == 1);
	// 5.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	Command_ReProcess(33, "y_commands_ReProcess yeah......", 0);
	ASSERT(YSI_gsPlayerid == 33);
	ASSERT(YSI_gsParams[0] != '\0');
	ASSERT(!strcmp(YSI_gsParams, "yeah......"));
	ASSERT(YSI_gsHelp == 0);
	// 6.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	Command_ReProcess(33, "y_commands_ReProcess Hello World", 1);
	ASSERT(YSI_gsPlayerid == 33);
	ASSERT(YSI_gsParams[0] != '\0');
	ASSERT(!strcmp(YSI_gsParams, "Hello World"));
	ASSERT(YSI_gsHelp == 1);
}

Test:y_commands_Parameters()
{
	call OnPlayerConnect(34);
	// 1.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	call OnPlayerCommandText(34, "/y_commands_ReProcess");
	ASSERT(YSI_gsPlayerid == 34);
	ASSERT(YSI_gsParams[0] == '\0');
	ASSERT(YSI_gsHelp == 0);
	// 2.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	call OnPlayerCommandText(34, "/y_commands_ReProcess one");
	ASSERT(YSI_gsPlayerid == 34);
	ASSERT(YSI_gsParams[0] != '\0');
	ASSERT(!strcmp(YSI_gsParams, "one"));
	ASSERT(YSI_gsHelp == 0);
	// 3.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	call OnPlayerCommandText(34, "/y_commands_ReProcess two and three");
	ASSERT(YSI_gsPlayerid == 34);
	ASSERT(YSI_gsParams[0] != '\0');
	ASSERT(!strcmp(YSI_gsParams, "two and three"));
	ASSERT(YSI_gsHelp == 0);
	// 4.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	call OnPlayerCommandText(34, "/y_commands_ReProcess 99");
	ASSERT(YSI_gsPlayerid == 34);
	ASSERT(YSI_gsParams[0] != '\0');
	ASSERT(!strcmp(YSI_gsParams, "99"));
	ASSERT(YSI_gsHelp == 0);
	// 5.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	call OnPlayerCommandText(34, "/y_commands_ReProcess yeah......");
	ASSERT(YSI_gsPlayerid == 34);
	ASSERT(YSI_gsParams[0] != '\0');
	ASSERT(!strcmp(YSI_gsParams, "yeah......"));
	ASSERT(YSI_gsHelp == 0);
	// 6.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	call OnPlayerCommandText(34, "/y_commands_ReProcess Hello World");
	ASSERT(YSI_gsPlayerid == 34);
	ASSERT(YSI_gsParams[0] != '\0');
	ASSERT(!strcmp(YSI_gsParams, "Hello World"));
	ASSERT(YSI_gsHelp == 0);
}

YCMD:y_commands_t1(playerid, params[], help)
{
	return 1;
}

YCMD:y_commands_t11(playerid, params[], help)
{
	return 1;
}

YCMD:y_commands_t111(playerid, params[], help)
{
	return 1;
}

YCMD:y_commands_t1111(playerid, params[], help)
{
	return 1;
}

YCMD:y_commands_t11111(playerid, params[], help)
{
	return 1;
}

YCMD:y_commands_t111111(playerid, params[], help)
{
	return 1;
}

Test:y_commands_iterator0()
{
	new
		found,
		total = 0;
	foreach (new c : Command())
	{
		++total;
		if (FALSE) {}
		else if (c == _:YCMD:y_commands_t1) ++found;
		else if (c == _:YCMD:y_commands_t11) ++found;
		else if (c == _:YCMD:y_commands_t111) ++found;
		else if (c == _:YCMD:y_commands_t1111) ++found;
		else if (c == _:YCMD:y_commands_t11111) ++found;
		else if (c == _:YCMD:y_commands_t111111) ++found;
	}
	// Very difficult to do much more.
	ASSERT(total != 0);
	ASSERT(found == 6);
}

Test:y_commands_iterator1()
{
	new
		found,
		total = 0;
	foreach (new c : Command)
	{
		++total;
		if (FALSE) {}
		else if (c == _:YCMD:y_commands_t1) ++found;
		else if (c == _:YCMD:y_commands_t11) ++found;
		else if (c == _:YCMD:y_commands_t111) ++found;
		else if (c == _:YCMD:y_commands_t1111) ++found;
		else if (c == _:YCMD:y_commands_t11111) ++found;
		else if (c == _:YCMD:y_commands_t111111) ++found;
	}
	// Very difficult to do much more.
	ASSERT(total != 0);
	ASSERT(found == 6);
}

Test:y_commands_lengths()
{
	call OnPlayerConnect(88);
	ASSERT(call OnPlayerCommandText(88, "/y_commands_t1") == 1);
	ASSERT(call OnPlayerCommandText(88, "/y_commands_t11") == 1);
	ASSERT(call OnPlayerCommandText(88, "/y_commands_t111") == 1);
	ASSERT(call OnPlayerCommandText(88, "/y_commands_t1111") == 1);
	ASSERT(call OnPlayerCommandText(88, "/y_commands_t11111") == 1);
	ASSERT(call OnPlayerCommandText(88, "/y_commands_t111111") == 1);
	ASSERT(call OnPlayerCommandText(88, "/y_commands_t1111111") == 0);
}

#if defined Y_COMMANDS_USE_CHARS
	YCMD:y_commands_prefix1(playerid, params[], help)
	{
		return 1;
	}
	
	Test:y_commands_prefix1()
	{
		call OnPlayerConnect(89);
		ASSERT(call OnPlayerCommandText(89, "/y_commands_prefix1") == 1);
		ASSERT(call OnPlayerText(89, "!y_commands_prefix1") == 1);
		ASSERT(Command_SetPrefix(YCMD:y_commands_prefix1, 'q') == false);
		ASSERT(Command_SetPrefix(YCMD:y_commands_prefix1, '!') == true);
		ASSERT(call OnPlayerCommandText(89, "/y_commands_prefix1") == 0);
		ASSERT(call OnPlayerText(89, "!y_commands_prefix1") == 0);
		ASSERT(Command_GetPrefixNamed("y_commands_prefix1") == '!');
		ASSERT(Command_IsValidPrefix('!'));
		ASSERT(!Command_IsValidPrefix('a'));
		ASSERT(Command_IsPrefixUsed('!'));
		ASSERT(!Command_IsPrefixUsed('_'));
		ASSERT(!Command_IsPrefixUsed('a'));
		ASSERT(Command_SetPrefix(YCMD:y_commands_prefix1, '~') == true);
		ASSERT(!Command_IsPrefixUsed('!'));
	}
#endif

