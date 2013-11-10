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

