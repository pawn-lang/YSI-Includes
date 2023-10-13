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
	Portions created by the Initial Developer are Copyright (c) 2022
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
	Cheaterman

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

@test(.group = "y_commands") y_commands_Simple()
{
	new
		id = Command_Find("y_commands_1");
	ASSERT_NE(id, -1);
}

@test(.group = "y_commands") y_commands_Syntax()
{
	new
		id1 = YCMD:y_commands_1,
		id2 = (YCMD:y_commands_2),
		id3 = YCMD:y_commands_3;
	ASSERT_NE(id1, -1);
	ASSERT_EQ(id2, -1);
	ASSERT_NE(id3, -1);
}

@test(.group = "y_commands") y_commands_Valid()
{
	ASSERT(Command_IsValid(YCMD:y_commands_1));
	ASSERT(Command_IsValid(Command_GetID("y_commands_1")));
	// ASSERT(Command_IsValid(YCMD:y_commands_1));
}

@test(.group = "y_commands") y_commands_YCMD()
{
	ASSERT_EQ(Command_GetID("y_commands_1"), _:YCMD:y_commands_1);
	ASSERT_NE(Command_GetID("y_commands_1"), _:YCMD:y_commands_2);
	ASSERT_NE(Command_GetID("y_commands_1"), _:YCMD:y_commands_3);
	ASSERT_EQ(Command_GetID("y_commands_DO_NOT_MAKE"), COMMAND_NOT_FOUND);
}

@test(.group = "y_commands") y_commands_GetName()
{
	new
		id = Command_GetID("y_commands_1");
	ASSERT_SAME(Command_GetName(id), "y_commands_1");
	ASSERT_ZE(strlen(Command_GetName(-1)));
}

@test(.group = "y_commands") y_commands_Find()
{
	new
		id = YCMD:y_commands_1;
	ASSERT_NE(id, COMMAND_NOT_FOUND);
}

@test(.group = "y_commands") y_commands_AddAlt()
{
	new
		id1 = YCMD:y_commands_1,
		id2 = Command_AddAlt(id1, "y_commands_alt1"),
		id3 = Command_AddAltNamed("y_commands_1", "y_commands_alt1");
	ASSERT_NE(id1, COMMAND_NOT_FOUND);
	ASSERT_NE(id1, id2);
	ASSERT_NE(id2, COMMAND_NOT_FOUND);
	// The semantics of this has now changed...  We can have two alt commands
	// with the same name pointing to the same command.  Quite why you would, I
	// don't know...  Actually, maybe we should special-case that.
	ASSERT_EQ(id2, id3);
}

@test(.group = "y_commands") y_commands_AddAlt2()
{
	new
		id1 = YCMD:y_commands_1,
		id2 = Command_AddAlt(id1, "y_cómmańds_ąlt"),
		id3 = Command_AddAltNamed("y_commands_1", "y_cómmańds_ąlt");
	ASSERT_NE(id1, id2);
	ASSERT_NE(id2, COMMAND_NOT_FOUND);
	ASSERT_EQ(id2, id3);
}

@test(.group = "y_commands") y_commands_Perms()
{
	new
		id = (YCMD:y_commands_1);
	Command_SetPlayer(id, 101, false);
	ASSERT(!Command_GetPlayer(id, 101));
	ASSERT(!Command_GetPlayerNamed("y_commands_1", 101));
	Command_SetPlayerNamed("y_commands_1", 101, true);
	//printf("%d", Command_Find("y_commands_1"));
	//printf("%d", id);
	ASSERT(Command_GetPlayer(id, 101));
	ASSERT(Command_GetPlayerNamed("y_commands_1", 101));
}

@test(.group = "y_commands") y_commands_Perms2()
{
	Command_AddAltNamed("y_commands_1", "y_commands_alt0");
	Command_AddAltNamed("y_commands_1", "y_cómmańds_ąlt2");
	new
		id = Command_Find("y_cómmańds_ąlt2");
	Command_SetPlayer(id, 101, false);
	ASSERT(!Command_GetPlayer(id, 101));
	ASSERT(!Command_GetPlayerNamed("y_cómmańds_ąlt2", 101));
	Command_SetPlayerNamed("y_cómmańds_ąlt2", 101, true);
	ASSERT(Command_GetPlayer(id, 101));
	ASSERT(Command_GetPlayerNamed("y_cómmańds_ąlt2", 101));
}

//@test(.group = "y_commands") y_commands_Find()
//{
//	new
//		id = Command_Find("y_cómmańds_ąlt");
//	ASSERT_NE(id, COMMAND_NOT_FOUND);
//}

static stock
	YSI_g_sRemovableRan = 0;

YCMD:y_commands_removable(playerid, params[], help)
{
	YSI_g_sRemovableRan = 1;
	return 1;
}

@test(.group = "y_commands") y_commands_removable()
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

@test(.group = "y_commands") y_commands_removable2()
{
	//printf("%d", YCMD:y_commands_removable2);
	Command_SetPlayer(YCMD:y_commands_removable2, 103, true);
	ASSERT_NZ(call OnPlayerCommandText(103, "/y_commands_removable2"));
	Command_Remove(YCMD:y_commands_removable2);
	ASSERT_ZE(call OnPlayerCommandText(103, "/y_commands_removable2"));
}

@test(.group = "y_commands") y_commands_count()
{
	for (new i = 0; i != MAX_COMMANDS; ++i)
	{
		Command_SetPlayer(i, 22, false);
	}
	ASSERT_ZE(Command_GetPlayerCommandCount(22));
	Command_SetPlayerNamed("y_commands_1", 22, true);
	ASSERT_NZ(Command_GetPlayerCommandCount(22));
}

@test(.group = "y_commands") y_commands_display1()
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

@test(.group = "y_commands") y_commands_display2()
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

@test(.group = "y_commands") y_commands_display3()
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

@test(.group = "y_commands") y_commands_count3()
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

@test(.group = "y_commands") y_commands_Hashing()
{
	new
		dst0[32],
		dst1[32],
		hash0 = 0,
		hash1 = 0;
	// CASE INSENSITIVE.
	// V1.
	Puny_Encode(dst0, __COMPILER_UNPACK"hello\x102;you", .delimiter = '@');
	HashMap_Hash(dst0, hash0);
	// V2.
	new
		len = Puny_EncodeHash(dst1, __COMPILER_UNPACK"Hello\x102;you there", hash1, .delimiter = '@');
	// Same.
	//printf("%s %s", dst0, dst1);
	ASSERT(!strcmp(dst0, dst1));
	ASSERT_EQ(hash0, hash1);
	//ASSERT_EQ(len, strlen(dst1));
	ASSERT_EQ(len, 9);
	// CASE SENSITIVE.
	Puny_Encode(dst0, __COMPILER_UNPACK"Hello\x102;there", .delimiter = '@');
	HashMap_Hash(dst0, hash0);
	// V2.
	len = Puny_EncodeHash(dst1, __COMPILER_UNPACK"Hello\x102;there you", hash1, .delimiter = '@');
	ASSERT_DIFF(dst0, dst1);
	ASSERT_NE(hash0, hash1);
	ASSERT_EQ(len, 11);
}

static
	gSomeVar = 0;

YCMD:y_commands_1(playerid, cmdtext[], help)
{
	//printf("%08x", addressof)
	return 1;
}

@test(.group = "y_commands") y_commands_1()
{
	call OnPlayerConnect(142);
	ASSERT_NZ(call OnPlayerCommandText(142, "/y_commands_1"));
	ASSERT_NZ(call OnPlayerCommandText(142, "/y_comMands_1"));
	ASSERT_NZ(call OnPlayerCommandText(142, "/Y_COMMANDS_1"));
	ASSERT_NZ(call OnPlayerCommandText(142, "/Y_commandS_1"));
	ASSERT_NZ(call OnPlayerCommandText(142, "/y_Commands_1"));
}

@test(.group = "y_commands") y_commands_2()
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

@test(.group = "y_commands") y_commands_3()
{
	call OnPlayerConnect(144);
	gSomeVar = 42;
	call OnPlayerCommandText(144, "/y_commands_3");
	ASSERT_EQ(gSomeVar, 52);
}

YCMD:y_commands_4(playerid, cmdtext[], help)
{
	//printf("y_commands_4 %d %s %d", playerid, cmdtext, help);
	gSomeVar = playerid + strval(cmdtext);
	return 1;
}

YCMD:y_commands_6(playerid, cmdtext[], help) = y_commands_4;
YCMD:y_commands_8(playerid, cmdtext[], help) = y_commands_6;

// TODO: Make this line an error.
YCMD:y_commands_12(playerid, cmdtext[], help) = y_commands_10;

@test(.group = "y_commands") y_commands_4()
{
	call OnPlayerConnect(80);
	gSomeVar = 42;
	//printf("gSomeVar: %d", gSomeVar);
	call OnPlayerCommandText(80, "/y_commands_4 40");
	//printf("gSomeVar: %d", gSomeVar);
	ASSERT_EQ(gSomeVar, 120);
	call OnPlayerCommandText(80, "/y_commands_6 50");
	//printf("gSomeVar: %d", gSomeVar);
	ASSERT_EQ(gSomeVar, 130);
	call OnPlayerCommandText(80, "/y_commands_8 70");
	//printf("gSomeVar: %d", gSomeVar);
	ASSERT_EQ(gSomeVar, 150);
	ASSERT_NE(_:YCMD:y_commands_4, COMMAND_NOT_FOUND);
	ASSERT_NE(_:YCMD:y_commands_6, COMMAND_NOT_FOUND);
	ASSERT_NE(_:YCMD:y_commands_8, COMMAND_NOT_FOUND);
	ASSERT_EQ(_:YCMD:y_commands_10, COMMAND_NOT_FOUND);
	ASSERT_EQ(_:YCMD:y_commands_12, COMMAND_NOT_FOUND);
}

static stock
	YSI_gsPlayerid = 0,
	YSI_gsParams[32],
	YSI_gsHelp = 0;

YCMD:y_commands_reprocess(playerid, params[], help)
{
	//printf("%d %x %d", playerid, params[0], help);
	YSI_gsPlayerid = playerid;
	StrCpy(YSI_gsParams, params);
	YSI_gsHelp = help;
	return 1;
}

@test(.group = "y_commands") y_commands_ReProcess()
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

@test(.group = "y_commands") y_commands_Parameters()
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

@test(.group = "y_commands") y_commands_iterator0()
{
	new
		found = 0,
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

@test(.group = "y_commands") y_commands_iterator1()
{
	new
		found = 0,
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

@test(.group = "y_commands") y_commands_lengths()
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
	
	@test(.group = "y_commands") y_commands_prefix1()
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

@cmd() ycmdtest1(playerid, params[], help)
{
	SendClientMessage(playerid, 0xFF0000AA, "/ycmdtest1 called");
	return 1;
}

YCMD:ycmdtest2(playerid, params[], help) = ycmdtest1;

@cmd(.alts = { "ycmdtest4" }) ycmdtest3(playerid, params[], help)
{
	SendClientMessage(playerid, 0xFF0000AA, "/ycmdtest3 called");
	return 1;
}

@cmd(.name = "усмдтест") ycmdtest7(playerid, params[], help)
{
	SendClientMessage(playerid, 0xFF0000AA, "/ycmdtest3 called");
	return 1;
}

@cmd(.name = "ycmdtest9") ycmdtest10(playerid, params[], help)
{
	SendClientMessage(playerid, 0xFF0000AA, "/ycmdtest3 called");
	return 1;
}

@cmd(.disabled = true) ycmdtest8(playerid, params[], help)
{
	SendClientMessage(playerid, 0xFF0000AA, "/ycmdtest3 called");
	return 1;
}

@testinit() y_commands_perm0(playerid)
{
	Command_AddAltNamed("ycmdtest3", "ycmdtest5", true);
	Command_AddAltNamed("ycmdtest3", "ycmdtest6", false);
}

@test(.group = "y_commands") y_commands_perm0(playerid)
{
	#pragma unused playerid
}

@testinit() y_commands_perm1(playerid)
{
	Command_SetPlayer(YCMD:ycmdtest1, playerid, true);
	Command_SetPlayer(YCMD:ycmdtest2, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest3, playerid, true);
	Command_SetPlayer(YCMD:ycmdtest4, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest5, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest6, playerid, false);
}

@test(.group = "y_commands") y_commands_perm1(playerid)
{
	ASK("Can you use /ycmdtest1?");
}

@testinit() y_commands_perm2(playerid)
{
	Command_SetPlayer(YCMD:ycmdtest1, playerid, true);
	Command_SetPlayer(YCMD:ycmdtest2, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest3, playerid, true);
	Command_SetPlayer(YCMD:ycmdtest4, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest5, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest6, playerid, false);
}

@test(.group = "y_commands") y_commands_perm2(playerid)
{
	ASK("Can you not use /ycmdtest2?");
}

@testinit() y_commands_perm3(playerid)
{
	Command_SetPlayer(YCMD:ycmdtest1, playerid, true);
	Command_SetPlayer(YCMD:ycmdtest2, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest3, playerid, true);
	Command_SetPlayer(YCMD:ycmdtest4, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest5, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest6, playerid, false);
}

@test(.group = "y_commands") y_commands_perm3(playerid)
{
	ASK("Can you use /ycmdtest3?");
}

@testinit() y_commands_perm4(playerid)
{
	Command_SetPlayer(YCMD:ycmdtest1, playerid, true);
	Command_SetPlayer(YCMD:ycmdtest2, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest3, playerid, true);
	Command_SetPlayer(YCMD:ycmdtest4, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest5, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest6, playerid, false);
}

@test(.group = "y_commands") y_commands_perm4(playerid)
{
	ASK("Can you not use /ycmdtest4?");
}

@testinit() y_commands_perm5(playerid)
{
	Command_SetPlayer(YCMD:ycmdtest1, playerid, true);
	Command_SetPlayer(YCMD:ycmdtest2, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest3, playerid, true);
	Command_SetPlayer(YCMD:ycmdtest4, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest5, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest6, playerid, false);
}

@test(.group = "y_commands") y_commands_perm5(playerid)
{
	ASK("Can you use /ycmdtest5?");
}

@testinit() y_commands_perm6(playerid)
{
	Command_SetPlayer(YCMD:ycmdtest1, playerid, true);
	Command_SetPlayer(YCMD:ycmdtest2, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest3, playerid, true);
	Command_SetPlayer(YCMD:ycmdtest4, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest5, playerid, false);
	Command_SetPlayer(YCMD:ycmdtest6, playerid, false);
}

@test(.group = "y_commands") y_commands_perm6(playerid)
{
	ASK("Can you not use /ycmdtest6?");
}

@testinit() y_commands_perm7a(playerid)
{
	Command_SetPlayer(YCMD:ycmdtest7, playerid, false);
}

@test(.group = "y_commands") y_commands_perm7a(playerid)
{
	ASK("Can you not use /ycmdtest7?");
}

@testinit() y_commands_perm7b(playerid)
{
	Command_SetPlayer(YCMD:ycmdtest7, playerid, true);
}

@test(.group = "y_commands") y_commands_perm7b(playerid)
{
	ASK("Can you not use /ycmdtest7?");
}

@testinit() y_commands_perm8(playerid)
{
}

@test(.group = "y_commands") y_commands_perm8(playerid)
{
	ASK("Can you not use /ycmdtest8?");
}

@testinit() y_commands_perm9(playerid)
{
	Command_SetPlayer(YCMD:ycmdtest7, playerid, true);
}

@test(.group = "y_commands") y_commands_perm9(playerid)
{
	ASK("Can you use /усмдтест?");
}

@testinit() y_commands_perm10(playerid)
{
	Command_SetPlayer(YCMD:ycmdtest7, playerid, false);
}

@test(.group = "y_commands") y_commands_perm10(playerid)
{
	ASK("Can you not use /усмдтест?");
}

@testinit() y_commands_perm11(playerid)
{
	Command_SetPlayer(YCMD:ycmdtest7, playerid, true);
}

@test(.group = "y_commands") y_commands_perm11(playerid)
{
	ASK("Can you use /усмдтест?");
}

@testinit() y_commands_perm12(playerid)
{
	Command_SetPlayer(YCMD:ycmdtest10, playerid, true);
}

@test(.group = "y_commands") y_commands_perm12(playerid)
{
	ASK("Can you use /ycmdtest9?");
}

@testinit() y_commands_perm13(playerid)
{
	Command_SetPlayer(YCMD:ycmdtest10, playerid, false);
}

@test(.group = "y_commands") y_commands_perm13(playerid)
{
	ASK("Can you not use /ycmdtest9?");
}

@testinit() y_commands_perm14(playerid)
{
	Command_SetPlayer(YCMD:ycmdtest10, playerid, true);
}

@test(.group = "y_commands") y_commands_perm14(playerid)
{
	ASK("Can you not use /ycmdtest10?");
}

@testinit() y_commands_perm15(playerid)
{
	Command_SetPlayer(YCMD:ycmdtest10, playerid, false);
}

@test(.group = "y_commands") y_commands_perm15(playerid)
{
	ASK("Can you not use /ycmdtest10?");
}

#if defined Group_Create

	final Group:groupCommandTest = Group_Create("y_commands_group");

	@cmd(.group = groupCommandTest) ycmdtest16(playerid, params[], help)
	{
		SendClientMessage(playerid, 0xFF0000AA, "/ycmdtest16 called");
		return 1;
	}

	@testinit() y_commands_perm16(playerid)
	{
		Group_SetPlayer(groupCommandTest, playerid, true);
	}

	@test(.group = "y_commands") y_commands_perm16(playerid)
	{
		ASK("Can you use /ycmdtest16?");
	}

	@testinit() y_commands_perm17(playerid)
	{
		Group_SetPlayer(groupCommandTest, playerid, false);
	}

	@test(.group = "y_commands") y_commands_perm17(playerid)
	{
		ASK("Can you not use /ycmdtest16?");
	}
#endif

static stock
	YSI_g_sy_commands_EnableableA = COMMAND_NOT_FOUND,
	YSI_g_sy_commands_EnableableB = COMMAND_NOT_FOUND;

YCMD:y_commands_enableablea(playerid, params[], help)
{
}

YCMD:y_commands_alternativea(playerid, params[], help) = y_commands_enableablea;

@test(.group = "y_commands") y_commands_Disable()
{
	new str[YSI_MAX_STRING];
	YSI_g_sy_commands_EnableableA = YCMD:y_commands_enableablea;
	str = Command_GetDisplay(YSI_g_sy_commands_EnableableA, 0);
	ASSERT_SAME(str, "y_commands_enableablea");
	str = Command_GetDisplayNamed("y_commands_alternativea", 0);
	ASSERT_SAME(str, "y_commands_alternativea");
	Command_SetDisabled(YSI_g_sy_commands_EnableableA, true);
	str = Command_GetDisplay(YSI_g_sy_commands_EnableableA, 0);
	ASSERT_SAME(str, "y_commands_alternativea");
	str = Command_GetDisplayNamed("y_commands_alternativea", 0);
	ASSERT_SAME(str, "y_commands_alternativea");
	Command_SetDisabled(YCMD:y_commands_alternativea, true);
	str = Command_GetDisplay(YSI_g_sy_commands_EnableableA, 0);
	ASSERT_SAME(str, "");
	str = Command_GetDisplayNamed("y_commands_alternativea", 0);
	ASSERT_SAME(str, "");
	Command_SetDisabled(YSI_g_sy_commands_EnableableA, false);
	str = Command_GetDisplay(YSI_g_sy_commands_EnableableA, 0);
	ASSERT_SAME(str, "y_commands_enableablea");
	str = Command_GetDisplayNamed("y_commands_alternativea", 0);
	ASSERT_SAME(str, "y_commands_enableablea");
	ASSERT(Command_GetDisabled(YCMD:y_commands_alternativea));
	ASSERT(!Command_GetDisabled(YSI_g_sy_commands_EnableableA));
	Command_SetDisabled(YCMD:y_commands_alternativea, false);
	str = Command_GetDisplay(YSI_g_sy_commands_EnableableA, 0);
	ASSERT_SAME(str, "y_commands_enableablea");
	str = Command_GetDisplayNamed("y_commands_alternativea", 0);
	ASSERT_SAME(str, "y_commands_alternativea");
}

@cmd(.alts = { "y_commands_alternativeb" }, .id = YSI_g_sy_commands_EnableableB) y_commands_enableableb(playerid, params[], help)
{
}

@test(.group = "y_commands") y_commands_DisableB()
{
	new str[YSI_MAX_STRING];
	str = Command_GetDisplay(YSI_g_sy_commands_EnableableB, 0);
	ASSERT_SAME(str, "y_commands_enableableb");
	str = Command_GetDisplayNamed("y_commands_alternativeb", 0);
	ASSERT_SAME(str, "y_commands_alternativeb");
	Command_SetDisabled(YSI_g_sy_commands_EnableableB, true);
	str = Command_GetDisplay(YSI_g_sy_commands_EnableableB, 0);
	ASSERT_SAME(str, "y_commands_alternativeb");
	str = Command_GetDisplayNamed("y_commands_alternativeb", 0);
	ASSERT_SAME(str, "y_commands_alternativeb");
	Command_SetDisabled(YCMD:y_commands_alternativeb, true);
	str = Command_GetDisplay(YSI_g_sy_commands_EnableableB, 0);
	ASSERT_SAME(str, "");
	str = Command_GetDisplayNamed("y_commands_alternativeb", 0);
	ASSERT_SAME(str, "");
	Command_SetDisabled(YSI_g_sy_commands_EnableableB, false);
	str = Command_GetDisplay(YSI_g_sy_commands_EnableableB, 0);
	ASSERT_SAME(str, "y_commands_enableableb");
	str = Command_GetDisplayNamed("y_commands_alternativeb", 0);
	ASSERT_SAME(str, "y_commands_enableableb");
	ASSERT(Command_GetDisabled(YCMD:y_commands_alternativeb));
	ASSERT(!Command_GetDisabled(YSI_g_sy_commands_EnableableB));
	Command_SetDisabled(YCMD:y_commands_alternativeb, false);
	str = Command_GetDisplay(YSI_g_sy_commands_EnableableB, 0);
	ASSERT_SAME(str, "y_commands_enableableb");
	str = Command_GetDisplayNamed("y_commands_alternativeb", 0);
	ASSERT_SAME(str, "y_commands_alternativeb");
}

@test(.group = "y_commands") y_commands_AddCallback()
{
	static
		var = 0;
	call OnPlayerConnect(202);
	call OnPlayerConnect(203);
	ASSERT_ZE(Command_ReProcess(202, "/inline_cmd_1 200", 0));
	ASSERT_ZE(Command_ReProcess(203, "/inline_cmd_1 200", 0));
	inline inline_cmd_1(string:params[])
	{
		var += strval(params);
		@return 1;
	}
	var = 0;
	Command_AddCallback("inline_cmd_1", 202, using inline inline_cmd_1);
	ASSERT_NZ(Command_ReProcess(202, "/inline_cmd_1 200", 0));
	ASSERT_ZE(Command_ReProcess(203, "/inline_cmd_1 200", 0));
	ASSERT_EQ(var, 200);
	inline inline_cmd_2(playerid, string:params[], help)
	{
		var += playerid;
		var += strval(params);
		var += help ? 10 : 11;
		@return 1;
	}
	var = 0;
	Command_AddCallback("inline_cmd_1", 203, using inline inline_cmd_2);
	ASSERT_NZ(Command_ReProcess(202, "/inline_cmd_1 200", 0));
	ASSERT_NZ(Command_ReProcess(203, "/inline_cmd_1 200", 0));
	ASSERT_EQ(var, 200 + 200 + 11 + 203);
	var = 0;
	Command_AddCallback("inline_cmd_1", 202, using inline inline_cmd_2);
	ASSERT_NZ(Command_ReProcess(202, "/inline_cmd_1 200", 0));
	ASSERT_NZ(Command_ReProcess(203, "/inline_cmd_1 200", 0));
	ASSERT_EQ(var, 200 + 11 + 202 + 200 + 11 + 203);
	Command_AddCallback("inline_cmd_2", 202, using inline inline_cmd_2);
	Command_RemoveCallback("inline_cmd_1", 202);
	var = 0;
	ASSERT_ZE(Command_ReProcess(202, "/inline_cmd_1 200", 0));
	ASSERT_NZ(Command_ReProcess(203, "/inline_cmd_1 200", 0));
	ASSERT_EQ(var, 200 + 11 + 203);
	ASSERT_NZ(Command_ReProcess(202, "/inline_cmd_2 300", 0));
	ASSERT_EQ(var, 300 + 11 + 202 + 200 + 11 + 203);
}

static
	gScriptTotal = 0;

@cmd() scriptcom1(playerid, params[], help)
{
	gScriptTotal = gScriptTotal + strval(params) + strval(params[2]);
	return 1;
}

@cmd() scriptcom2(playerid, params[], help)
{
	gScriptTotal = gScriptTotal + strval(params) * strval(params[2]);
	return 1;
}

@test(.group = "y_commands") y_commands_RunScript()
{
	gScriptTotal = 0;
	ASSERT(Command_RunScript(202, "/scriptcom1 5 6 ; /scriptcom2 5 6 ; /scriptcom1 8 9"));
	ASSERT_EQ(gScriptTotal, 5 + 6 + 5 * 6 + 8 + 9);
}

