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

static PS_FakePlayers(bool:add)
{
	for (new i = 0; i != MAX_PLAYERS; ++i)
	{
		if (add) Iter_Add(Player, i);
		else Iter_Remove(Player, i);
	}
}

static PS_CountMembers(@PlayerSet:players)
{
	new count = 0;
	foreach (new playerid : PS(players))
	{
		++count;
	}
	return count;
}

#define PS_CountMembers( @PSF() PS_CountMembers(

@testinit() PS_SinglePlayer()
{
	PS_FakePlayers(true);
}

@test(.group = "y_playerset") PS_SinglePlayer()
{
	new playerid = 42;
	new count = PS_CountMembers(playerid);
	ASSERT_EQ(count, 1);
}

@testclose() PS_SinglePlayer()
{
	PS_FakePlayers(false);
}

//@testinit() PS_PlayerGroup()
//{
//	PS_FakePlayers(true);
//}
//
//@test(.group = "y_playerset") PS_PlayerGroup()
//{
//	new Group:admins = Group_Create("admins");
//	Group_SetPlayer(admins, 6, true);
//	Group_SetPlayer(admins, 8, true);
//	Group_SetPlayer(admins, 11, true);
//	Group_SetPlayer(admins, 17, true);
//	Group_SetPlayer(admins, 9, true);
//	new count = PS_CountMembers(admins);
//	ASSERT_EQ(count, 5);
//}
//
//@testclose() PS_PlayerGroup()
//{
//	PS_FakePlayers(false);
//}

@testinit() PS_YSIArray()
{
	PS_FakePlayers(true);
}

@test(.group = "y_playerset") PS_YSIArray()
{
	new PlayerArray:jailed<MAX_PLAYERS>;
	PA_FastInit(jailed);
	PA_Set(jailed, 5, true);
	PA_Set(jailed, 9, true);
	PA_Set(jailed, 101, true);
	PA_Set(jailed, 111, true);
	PA_Set(jailed, 5, true);
	PA_Set(jailed, 9, true);
	new count = PS_CountMembers(jailed);
	ASSERT_EQ(count, 4);
}

@testclose() PS_YSIArray()
{
	PS_FakePlayers(false);
}

@testinit() PS_PlayerList()
{
	PS_FakePlayers(true);
}

@test(.group = "y_playerset") PS_PlayerList()
{
	new list[MAX_PLAYERS];
	list[0] = 0;
	list[1] = 5;
	list[2] = 88;
	list[3] = INVALID_PLAYER_ID;
	new count = PS_CountMembers(@list);
	ASSERT_EQ(count, 3);
}

@testclose() PS_PlayerList()
{
	PS_FakePlayers(false);
}

@testinit() PS_AllPlayers()
{
	PS_FakePlayers(true);
}

@test(.group = "y_playerset") PS_AllPlayers()
{
	new count = PS_CountMembers(ALL_PLAYERS);
	ASSERT_EQ(count, MAX_PLAYERS);
}

@testclose() PS_AllPlayers()
{
	PS_FakePlayers(false);
}

@testinit() PS_PlayerArray()
{
	PS_FakePlayers(true);
}

@test(.group = "y_playerset") PS_PlayerArray()
{
	new bool:flags[MAX_PLAYERS];
	flags[0] = true;
	flags[5] = true;
	flags[88] = true;
	flags[288] = true;
	flags[788] = true;
	flags[789] = true;
	flags[790] = true;
	flags[791] = true;
	flags[792] = true;
	flags[793] = true;
	new count = PS_CountMembers(@flags);
	ASSERT_EQ(count, 10);
}

@testclose() PS_PlayerArray()
{
	PS_FakePlayers(false);
}

//@testinit() PS_EnumOffset()
//{
//	PS_FakePlayers(true);
//}
//
//enum E_PS_TEST_DATA
//{
//	E_PS_TEST_DATA_SOMETHING,
//	bool:E_PS_TEST_DATA_ADMIN,
//	E_PS_TEST_DATA_OTHER,
//}
//
//@test(.group = "y_playerset") PS_EnumOffset()
//{
//	new psEnumTest[MAX_PLAYERS][E_PS_TEST_DATA];
//
//	psEnumTest[55][E_PS_TEST_DATA_ADMIN] = true;
//	psEnumTest[858][E_PS_TEST_DATA_ADMIN] = true;
//	new count = PS_CountMembers(@psEnumTest<E_PS_TEST_DATA_ADMIN>);
//	ASSERT_EQ(count, 2);
//}
//
//@testclose() PS_EnumOffset()
//{
//	PS_FakePlayers(false);
//}

