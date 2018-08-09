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

TEST__ Player_Existing()
{
	new
		ret[E_USER_PRELOAD];
	Player_Preload("TestPlayer", ret);
	ASSERT_EQ(0, ret[E_USER_PRELOAD_YID]);
	ASSERT_EQ(Langs_GetLanguage("EN"), ret[E_USER_PRELOAD_LANG]);
	ASSERT_EQ(0x12345678, ret[E_USER_PRELOAD_BITS]);
	ASSERT(0xAABBCCDD >= ret[E_USER_PRELOAD_DATE]);
	P:I("Note that if these tests fail, you will need to");
	P:I("    first connect to the server as \"TestPlayer\".");
}

new
	gBot = INVALID_PLAYER_ID;

TEST__ Player_ChangeLanguage()
{
	// Connect the bot here so that it is done way before the PTest is run.
	ConnectNPC("TestPlayer", "npcidle");
}

public OnPlayerConnect(playerid)
{
	new
		name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof (name));
	if (!strcmp(name, "TestPlayer")) gBot = playerid;
	#if defined Testing_OnPlayerConnect
		return Testing_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect Testing_OnPlayerConnect
#if defined Testing_OnPlayerConnect
	forward Testing_OnPlayerConnect(playerid);
#endif

PTEST_INIT__ Player_ChangeLanguage(playerid)
{
	// So that their language can be changed.
	Player_ForceLogin(gBot);
}

PTEST__ Player_ChangeLanguage(playerid)
{
	new
		ret[E_USER_PRELOAD];
	// Check their language is English, then change it to Dutch.
	Player_Preload("TestPlayer", ret);
	ASSERT_EQ(Langs_GetLanguage("EN"), ret[E_USER_PRELOAD_LANG]);
	Player_ChangeLanguage(gBot, "NL");
	Player_Preload("TestPlayer", ret);
	ASSERT_EQ(Langs_GetLanguage("NL"), ret[E_USER_PRELOAD_LANG]);
}

PTEST_CLOSE__ Player_ChangeLanguage(playerid)
{
	// Reset the player.
	Player_ChangeLanguage(gBot, "EN");
	//Kick(gBot);
}

PTEST_INIT__ Player_ChangePassword(playerid)
{
	// So that their password can be changed.
	Player_ForceLogin(gBot);
}

PTEST__ Player_ChangePassword(playerid)
{
	new
		ret[E_USER_PRELOAD];
	// Change their password.
	Player_Preload("TestPlayer", ret);
	ASSERT_SAME(ret[E_USER_PRELOAD_PASS], "24954A7C4E607137A70D701986CC3C3140C143E5B5886362A8ACB647B81592CF1F092C65178F6E3FFFC6691B044D2290215058E09BBE029D23D1D67F41640090");
	Player_ChangePassword(gBot, "thisisabadpass");
	Player_Preload("TestPlayer", ret);
	ASSERT_SAME(ret[E_USER_PRELOAD_PASS], "B506FEEEDFB83EF44A5DC2E00BF1535E58E3B37A044730F2A6718497A224B5455A441F39F9EB91967B38607416A9B85E5DE3CBE3A48E7A77AB5808674EF33822");
}

PTEST_CLOSE__ Player_ChangePassword(playerid)
{
	// Reset the player.
	Player_ChangePassword(gBot, "thisisanOKpass");
	//Kick(gBot);
}

PTEST_INIT__ Player_Preload(playerid)
{
	Player_ForceLogin(gBot);
}

PTEST__ Player_Preload(playerid)
{
	new
		//name[MAX_PLAYER_NAME],
		ret[E_USER_PRELOAD];
	//GetPlayerName(playerid, name, sizeof (name));
	Player_Preload("TestPlayer", ret);
	ASSERT_EQ(Player_GetYID(gBot), ret[E_USER_PRELOAD_YID]);
	ASSERT_EQ(Langs_GetPlayerLanguage(gBot), ret[E_USER_PRELOAD_LANG]);
	ASSERT_EQ(0x12345678, ret[E_USER_PRELOAD_BITS]);
	ASSERT(gettime() >= ret[E_USER_PRELOAD_DATE]);
}

PTEST_INIT__ Player_GetID(playerid)
{
	// So that their password can be changed.
	Player_ForceLogin(gBot);
}

PTEST__ Player_GetID(playerid)
{
	ASSERT_ZE(Player_GetYID(gBot));
	ASSERT(Player_GetYID(playerid) < 0);
}
