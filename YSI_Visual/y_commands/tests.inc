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

YCMD:y_commands_removable(playerid, params[], help)
{
	return 1;
}

Test:y_commands_removable()
{
	Command_SetPlayerNamed("y_commands_removable", 103, true);
	ASSERT(call OnPlayerCommandText(103, "/y_commands_removable") == 1);
	Command_SetPlayerNamed("y_commands_removable", 103, false);
	ASSERT(call OnPlayerCommandText(103, "/y_commands_removable") == 0);
	Command_SetPlayerNamed("y_commands_removable", 103, true);
	ASSERT(call OnPlayerCommandText(103, "/y_commands_removable") == 1);
	Command_RemoveNamed("y_commands_removable");
	ASSERT(call OnPlayerCommandText(103, "/y_commands_removable") == 0);
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
	ASSERT(len == strlen(dst1));
	// CASE SENSITIVE.
	Puny_Encode(dst0, "Hello\x102;you", .delimiter = '@');
	HashMap_Hash(dst0, hash0);
	// V2.
	len = Puny_EncodeHash(dst1, "Hello\x102;you there", hash1, .delimiter = '@');
	ASSERT(!!strcmp(dst0, dst1));
	ASSERT(hash0 != hash1);
	ASSERT(len == strlen(dst1));
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

Test:y_commands_4()
{
}

