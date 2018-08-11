/*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright C 2011
	the Initial Developer. All Rights Reserved.

Contributors:
	Y_Less
	koolk
	JoeBullet/Google63
	g_aSlice/Slice
	Misiur
	samphunter
	tianmeta
	maddinat0r
	spacemud
	Crayder
	Dayvison
	Ahmad45123
	Zeex
	irinel1996
	Yiin-
	Chaprnks
	Konstantinos
	Masterchen09
	Southclaws
	PatchwerkQWER
	m0k1
	paulommu
	udan111

Thanks:
	JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
	ZeeX - Very productive conversations.
	koolk - IsPlayerinAreaEx code.
	TheAlpha - Danish translation.
	breadfish - German translation.
	Fireburn - Dutch translation.
	yom - French translation.
	50p - Polish translation.
	Zamaroht - Spanish translation.
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

TEST__ y_commands_Syntax()
{
	new
		id1 = YCMD:y_commands_1,
		id2 = (YCMD:y_commands_2),
		id3 = YCMD:y_commands_3;
	ASSERT_NE(id1, -1);
	ASSERT_EQ(id2, -1);
	ASSERT_NE(id3, -1);
}

TEST__ y_commands_Valid()
{
	ASSERT(Command_IsValid(YCMD:y_commands_1));
	ASSERT(Command_IsValid(Command_GetID("y_commands_1")));
	// ASSERT(Command_IsValid(YCMD:y_commands_1));
}

TEST__ y_commands_YCMD()
{
	ASSERT_EQ(Command_GetID("y_commands_1"), _:YCMD:y_commands_1);
	ASSERT_NE(Command_GetID("y_commands_1"), _:YCMD:y_commands_2);
	ASSERT_NE(Command_GetID("y_commands_1"), _:YCMD:y_commands_3);
	ASSERT_EQ(Command_GetID("y_commands_DO_NOT_MAKE"), COMMAND_NOT_FOUND);
}

TEST__ y_commands_GetName()
{
	new
		id = Command_GetID("y_commands_1");
	ASSERT_SAME(Command_GetName(id), "y_commands_1");
	ASSERT_ZE(strlen(Command_GetName(-1)));
}

TEST__ y_commands_AddAlt()
{
	new
		id1 = YCMD:y_commands_1,
		id2 = Command_AddAlt(id1, "y_commands_alt1"),
		id3 = Command_AddAltNamed("y_commands_1", "y_commands_alt1");
	ASSERT_NE(id1, id2);
	ASSERT_NE(id2, COMMAND_NOT_FOUND);
	ASSERT_EQ(id2, id3);
}

TEST__ y_commands_AddAlt2()
{
	new
		id1 = YCMD:y_commands_1,
		id2 = Command_AddAlt(id1, "y_cómmańds_ąlt"),
		id3 = Command_AddAltNamed("y_commands_1", "y_cómmańds_ąlt");
	ASSERT_NE(id1, id2);
	ASSERT_NE(id2, COMMAND_NOT_FOUND);
	ASSERT_EQ(id2, id3);
}

TEST__ y_commands_Perms()
{
	new
		id = (YCMD:y_commands_1);
	Command_SetPlayer(id, 101, false);
	ASSERT(!Command_GetPlayer(id, 101));
	ASSERT(!Command_GetPlayerNamed("y_commands_1", 101));
	Command_SetPlayerNamed("y_commands_1", 101, true);
	printf("%d", Command_Find("y_commands_1"));
	printf("%d", id);
	ASSERT(Command_GetPlayer(id, 101));
	ASSERT(Command_GetPlayerNamed("y_commands_1", 101));
}

TEST__ y_commands_Perms2()
{
	new
		id = Command_Find("y_cómmańds_ąlt");
	Command_SetPlayer(id, 101, false);
	ASSERT(!Command_GetPlayer(id, 101));
	ASSERT(!Command_GetPlayerNamed("y_cómmańds_ąlt", 101));
	Command_SetPlayerNamed("y_cómmańds_ąlt", 101, true);
	ASSERT(Command_GetPlayer(id, 101));
	ASSERT(Command_GetPlayerNamed("y_cómmańds_ąlt", 101));
}

static stock
	YSI_g_sRemovableRan = 0;

YCMD:y_commands_removable(playerid, params[], help)
{
	YSI_g_sRemovableRan = 1;
	return 1;
}

TEST__ y_commands_removable()
{
	YSI_g_sRemovableRan = 0;
	Command_SetPlayerNamed("y_commands_removable", 103, true);
	ASSERT_NZ(call OnPlayerCommandText(103, "/y_commands_removable"));
	ASSERT_EQ(YSI_g_sRemovableRan, 1);
	YSI_g_sRemovableRan = 0;
	Command_SetPlayerNamed("y_commands_removable", 103, false);
	Command_SetDeniedReturn(false);
	ASSERT_ZE(call OnPlayerCommandText(103, "/y_commands_removable"));
	Command_SetDeniedReturn(true);
	ASSERT_NZ(call OnPlayerCommandText(103, "/y_commands_removable"));
	Command_SetDeniedReturn(false);
	ASSERT_ZE(YSI_g_sRemovableRan);
	YSI_g_sRemovableRan = 0;
	Command_SetPlayerNamed("y_commands_removable", 103, true);
	ASSERT_NZ(call OnPlayerCommandText(103, "/y_commands_removable"));
	ASSERT_EQ(YSI_g_sRemovableRan, 1);
	YSI_g_sRemovableRan = 0;
	Command_RemoveNamed("y_commands_removable");
	ASSERT_ZE(call OnPlayerCommandText(103, "/y_commands_removable"));
	ASSERT_ZE(YSI_g_sRemovableRan);
}

YCMD:y_commands_removable2(playerid, params[], help)
{
	return 1;
}

TEST__ y_commands_removable2()
{
	//printf("%d", YCMD:y_commands_removable2);
	Command_SetPlayer(YCMD:y_commands_removable2, 103, true);
	ASSERT_NZ(call OnPlayerCommandText(103, "/y_commands_removable2"));
	Command_Remove(YCMD:y_commands_removable2);
	ASSERT_ZE(call OnPlayerCommandText(103, "/y_commands_removable2"));
}

TEST__ y_commands_count()
{
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		Command_SetPlayer(i, 22, false);
	}
	ASSERT_ZE(Command_GetPlayerCommandCount(22));
	Command_SetPlayerNamed("y_commands_1", 22, true);
	ASSERT_NZ(Command_GetPlayerCommandCount(22));
}

TEST__ y_commands_display1()
{
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		Command_SetPlayer(i, 23, false);
	}
	ASSERT_ZE(strlen(Command_GetDisplayNamed("y_commands_1", 23)));
	Command_SetPlayerNamed("y_commands_1", 23, true);
	ASSERT_NZ(strlen(Command_GetDisplayNamed("y_commands_1", 23)));
	ASSERT_SAME(Command_GetDisplayNamed("y_commands_1", 23), "y_commands_1");
}

TEST__ y_commands_display2()
{
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		Command_SetPlayer(i, 23, false);
	}
	ASSERT_ZE(strlen(Command_GetDisplay(YCMD:y_commands_3, 23)));
	Command_SetPlayer(YCMD:y_commands_3, 23, true);
	ASSERT_NZ(strlen(Command_GetDisplay(YCMD:y_commands_3, 23)));
	ASSERT_SAME(Command_GetDisplay(YCMD:y_commands_3, 23), "y_commands_3");
}

TEST__ y_commands_display3()
{
	Command_AddAlt(YCMD:y_commands_3, "y_commands_alt7");
	Command_AddAlt(YCMD:y_commands_alt7, "y_commands_alt2");
	Command_AddAlt(YCMD:y_commands_alt2, "y_commands_alt3");
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		Command_SetPlayer(i, 25, false);
	}
	ASSERT_ZE(strlen(Command_GetDisplay(YCMD:y_commands_3, 25)));
	// Get a name from the original.
	Command_SetPlayer(YCMD:y_commands_alt3, 25, true);
	ASSERT_NZ(strlen(Command_GetDisplay(YCMD:y_commands_3, 25)));
	ASSERT_SAME(Command_GetDisplay(YCMD:y_commands_3, 25), "y_commands_alt3");
	// Get an y_commands_alternate from a different y_commands_alternate.
	Command_SetPlayer(YCMD:y_commands_alt7, 25, true);
	ASSERT_NZ(strlen(Command_GetDisplay(YCMD:y_commands_alt2, 25)));
	ASSERT_SAME(Command_GetDisplay(YCMD:y_commands_alt2, 25), "y_commands_alt7");
	// Get the original from an y_commands_alternate.
	Command_SetPlayer(YCMD:y_commands_3, 25, true);
	ASSERT_NZ(strlen(Command_GetDisplay(YCMD:y_commands_alt2, 25)));
	ASSERT_SAME(Command_GetDisplay(YCMD:y_commands_alt2, 25), "y_commands_3");
}

TEST__ y_commands_count3()
{
	Command_AddAlt(YCMD:y_commands_1, "y_commands_alt4");
	Command_AddAlt(YCMD:y_commands_alt4, "y_commands_alt5");
	Command_AddAlt(YCMD:y_commands_alt4, "y_commands_alt6");
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		Command_SetPlayer(i, 26, false);
	}
	ASSERT_ZE(Command_GetPlayerCommandCount(26));
	Command_SetPlayer(YCMD:y_commands_1, 26, true);
	ASSERT_EQ(Command_GetPlayerCommandCount(26), 1);
	Command_SetPlayer(YCMD:y_commands_alt4, 26, true);
	ASSERT_EQ(Command_GetPlayerCommandCount(26), 2);
	Command_SetPlayer(YCMD:y_commands_alt5, 26, true);
	ASSERT_EQ(Command_GetPlayerCommandCount(26), 3);
	Command_SetPlayer(YCMD:y_commands_alt6, 26, true);
	ASSERT_EQ(Command_GetPlayerCommandCount(26), 4);
}

TEST__ y_commands_Hashing()
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
	ASSERT_EQ(hash0, hash1);
	//ASSERT_EQ(len, strlen(dst1));
	ASSERT_EQ(len, 9);
	// CASE SENSITIVE.
	Puny_Encode(dst0, "Hello\x102;there", .delimiter = '@');
	HashMap_Hash(dst0, hash0);
	// V2.
	len = Puny_EncodeHash(dst1, "Hello\x102;there you", hash1, .delimiter = '@');
	ASSERT_DIFF(dst0, dst1);
	ASSERT_NE(hash0, hash1);
	ASSERT_EQ(len, 11);
}

static
	gSomeVar;

YCMD:y_commands_1(playerid, cmdtext[], help)
{
	return 1;
}

TEST__ y_commands_1()
{
	call OnPlayerConnect(142);
	ASSERT_NZ(call OnPlayerCommandText(142, "/y_commands_1"));
	ASSERT_NZ(call OnPlayerCommandText(142, "/y_comMands_1"));
	ASSERT_NZ(call OnPlayerCommandText(142, "/Y_COMMANDS_1"));
	ASSERT_NZ(call OnPlayerCommandText(142, "/Y_commandS_1"));
	ASSERT_NZ(call OnPlayerCommandText(142, "/y_Commands_1"));
}

TEST__ y_commands_2()
{
	call OnPlayerConnect(143);
	ASSERT_ZE(call OnPlayerCommandText(143, "/y_commands__NONONONO"));
	ASSERT_ZE(call OnPlayerCommandText(143, "/y_commands_0"));
	ASSERT_ZE(call OnPlayerCommandText(143, "/y_comMands_2"));
	ASSERT_ZE(call OnPlayerCommandText(143, "/Y_COMMANDS_2"));
	ASSERT_ZE(call OnPlayerCommandText(143, "/Y_commandS_I"));
	ASSERT_ZE(call OnPlayerCommandText(143, "/y_Commands_l"));
}

YCMD:y_commands_3(playerid, cmdtext[], help)
{
	gSomeVar = 52;
	return 1;
}

TEST__ y_commands_3()
{
	call OnPlayerConnect(144);
	gSomeVar = 42;
	call OnPlayerCommandText(144, "/y_commands_3");
	ASSERT_EQ(gSomeVar, 52);
}

YCMD:y_commands_4(playerid, cmdtext[], help)
{
	gSomeVar = playerid + strval(cmdtext);
	return 1;
}

YCMD:y_commands_5(playerid, cmdtext[], help) = y_commands_4;

TEST__ y_commands_4()
{
	call OnPlayerConnect(80);
	gSomeVar = 42;
	call OnPlayerCommandText(80, "/y_commands_4 40");
	ASSERT_EQ(gSomeVar, 120);
	call OnPlayerCommandText(80, "/y_commands_5 50");
	ASSERT_EQ(gSomeVar, 130);
	ASSERT_NE(YCMD:y_commands_4, COMMAND_NOT_FOUND);
	ASSERT_NE(YCMD:y_commands_5, COMMAND_NOT_FOUND);
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

TEST__ y_commands_ReProcess()
{
	call OnPlayerConnect(33);
	// 1.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	Command_ReProcess(33, "y_commands_ReProcess", 0);
	ASSERT_EQ(YSI_gsPlayerid, 33);
	ASSERT_EQ(YSI_gsParams[0], '\0');
	ASSERT_ZE(YSI_gsHelp);
	// 2.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	Command_ReProcess(33, "y_commands_ReProcess one", 1);
	ASSERT_EQ(YSI_gsPlayerid, 33);
	ASSERT_NE(YSI_gsParams[0], '\0');
	ASSERT_SAME(YSI_gsParams, "one");
	ASSERT_EQ(YSI_gsHelp, 1);
	// 3.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	Command_ReProcess(33, "y_commands_ReProcess two and three", 0);
	ASSERT_EQ(YSI_gsPlayerid, 33);
	ASSERT_NE(YSI_gsParams[0], '\0');
	ASSERT_SAME(YSI_gsParams, "two and three");
	ASSERT_ZE(YSI_gsHelp);
	// 4.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	Command_ReProcess(33, "y_commands_ReProcess 99", 1);
	ASSERT_EQ(YSI_gsPlayerid, 33);
	ASSERT_NE(YSI_gsParams[0], '\0');
	ASSERT_SAME(YSI_gsParams, "99");
	ASSERT_EQ(YSI_gsHelp, 1);
	// 5.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	Command_ReProcess(33, "y_commands_ReProcess yeah......", 0);
	ASSERT_EQ(YSI_gsPlayerid, 33);
	ASSERT_NE(YSI_gsParams[0], '\0');
	ASSERT_SAME(YSI_gsParams, "yeah......");
	ASSERT_ZE(YSI_gsHelp);
	// 6.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	Command_ReProcess(33, "y_commands_ReProcess Hello World", 1);
	ASSERT_EQ(YSI_gsPlayerid, 33);
	ASSERT_NE(YSI_gsParams[0], '\0');
	ASSERT_SAME(YSI_gsParams, "Hello World");
	ASSERT_EQ(YSI_gsHelp, 1);
}

TEST__ y_commands_Parameters()
{
	call OnPlayerConnect(34);
	// 1.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	call OnPlayerCommandText(34, "/y_commands_ReProcess");
	ASSERT_EQ(YSI_gsPlayerid, 34);
	ASSERT_EQ(YSI_gsParams[0], '\0');
	ASSERT_ZE(YSI_gsHelp);
	// 2.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	call OnPlayerCommandText(34, "/y_commands_ReProcess one");
	ASSERT_EQ(YSI_gsPlayerid, 34);
	ASSERT_NE(YSI_gsParams[0], '\0');
	ASSERT_SAME(YSI_gsParams, "one");
	ASSERT_ZE(YSI_gsHelp);
	// 3.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	call OnPlayerCommandText(34, "/y_commands_ReProcess two and three");
	ASSERT_EQ(YSI_gsPlayerid, 34);
	ASSERT_NE(YSI_gsParams[0], '\0');
	ASSERT_SAME(YSI_gsParams, "two and three");
	ASSERT_ZE(YSI_gsHelp);
	// 4.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	call OnPlayerCommandText(34, "/y_commands_ReProcess 99");
	ASSERT_EQ(YSI_gsPlayerid, 34);
	ASSERT_NE(YSI_gsParams[0], '\0');
	ASSERT_SAME(YSI_gsParams, "99");
	ASSERT_ZE(YSI_gsHelp);
	// 5.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	call OnPlayerCommandText(34, "/y_commands_ReProcess yeah......");
	ASSERT_EQ(YSI_gsPlayerid, 34);
	ASSERT_NE(YSI_gsParams[0], '\0');
	ASSERT_SAME(YSI_gsParams, "yeah......");
	ASSERT_ZE(YSI_gsHelp);
	// 6.
	YSI_gsPlayerid = INVALID_PLAYER_ID;
	YSI_gsParams[0] = '\0';
	YSI_gsHelp = -1;
	call OnPlayerCommandText(34, "/y_commands_ReProcess Hello World");
	ASSERT_EQ(YSI_gsPlayerid, 34);
	ASSERT_NE(YSI_gsParams[0], '\0');
	ASSERT_SAME(YSI_gsParams, "Hello World");
	ASSERT_ZE(YSI_gsHelp);
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

TEST__ y_commands_iterator0()
{
	new
		found,
		total = 0;
	FOREACH__ (new c : Command())
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
	ASSERT_NZ(total);
	ASSERT_EQ(found, 6);
}

TEST__ y_commands_iterator1()
{
	new
		found,
		total = 0;
	FOREACH__ (new c : Command)
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
	ASSERT_NZ(total);
	ASSERT_EQ(found, 6);
}

TEST__ y_commands_lengths()
{
	call OnPlayerConnect(88);
	ASSERT_NZ(call OnPlayerCommandText(88, "/y_commands_t1"));
	ASSERT_NZ(call OnPlayerCommandText(88, "/y_commands_t11"));
	ASSERT_NZ(call OnPlayerCommandText(88, "/y_commands_t111"));
	ASSERT_NZ(call OnPlayerCommandText(88, "/y_commands_t1111"));
	ASSERT_NZ(call OnPlayerCommandText(88, "/y_commands_t11111"));
	ASSERT_NZ(call OnPlayerCommandText(88, "/y_commands_t111111"));
	ASSERT_ZE(call OnPlayerCommandText(88, "/y_commands_t1111111"));
}

#if defined Y_COMMANDS_USE_CHARS
	YCMD:y_commands_prefix1(playerid, params[], help)
	{
		return 1;
	}
	
	TEST__ y_commands_prefix1()
	{
		new
			a = _C<@_yC>,
			b = ('@' << 24) | ('_' << 16) | ('y' << 08) | ('C' << 00);
		ASSERT_EQ(a, b);
		call OnPlayerConnect(89);
		ASSERT_NZ(call OnPlayerCommandText(89, "/y_commands_prefix1"));
		ASSERT_NZ(call OnPlayerText(89, "!y_commands_prefix1"));
		ASSERT_EQ(Command_SetPrefix(YCMD:y_commands_prefix1, 'q'), false);
		ASSERT_EQ(Command_SetPrefix(YCMD:y_commands_prefix1, '!'), true);
		ASSERT_ZE(call OnPlayerCommandText(89, "/y_commands_prefix1"));
		ASSERT_ZE(call OnPlayerText(89, "!y_commands_prefix1"));
		ASSERT_EQ(Command_GetPrefixNamed("y_commands_prefix1"), '!');
		ASSERT(Command_IsValidPrefix('!'));
		ASSERT(!Command_IsValidPrefix('a'));
		ASSERT(Command_IsPrefixUsed('!'));
		ASSERT(!Command_IsPrefixUsed('_'));
		ASSERT(!Command_IsPrefixUsed('a'));
		ASSERT_EQ(Command_SetPrefix(YCMD:y_commands_prefix1, '~'), true);
		ASSERT(!Command_IsPrefixUsed('!'));
	}
#endif

