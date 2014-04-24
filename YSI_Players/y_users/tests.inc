Test:Player_Existing()
{
	new
		ret[E_USER_PRELOAD];
	Player_Preload("TestPlayer", ret);
	ASSERT(0 == ret[E_USER_PRELOAD_YID]);
	ASSERT(Langs_GetLanguage("EN") == ret[E_USER_PRELOAD_LANG]);
	ASSERT(0x12345678 == ret[E_USER_PRELOAD_BITS]);
	ASSERT(0xAABBCCDD >= ret[E_USER_PRELOAD_DATE]);
	P:I("Note that if these tests fail, you will need to");
	P:I("    first connect to the server as \"TestPlayer\".");
}

new
	gBot = INVALID_PLAYER_ID;

Test:Player_ChangeLanguage()
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

PTestInit:Player_ChangeLanguage(playerid)
{
	// So that their language can be changed.
	Player_ForceLogin(gBot);
}

PTest:Player_ChangeLanguage(playerid)
{
	new
		ret[E_USER_PRELOAD];
	// Check their language is English, then change it to Dutch.
	Player_Preload("TestPlayer", ret);
	ASSERT(Langs_GetLanguage("EN") == ret[E_USER_PRELOAD_LANG]);
	Player_ChangeLanguage(gBot, "NL");
	Player_Preload("TestPlayer", ret);
	ASSERT(Langs_GetLanguage("NL") == ret[E_USER_PRELOAD_LANG]);
}

PTestClose:Player_ChangeLanguage(playerid)
{
	// Reset the player.
	Player_ChangeLanguage(gBot, "EN");
	//Kick(gBot);
}

PTestInit:Player_ChangePassword(playerid)
{
	// So that their password can be changed.
	Player_ForceLogin(gBot);
}

PTest:Player_ChangePassword(playerid)
{
	new
		ret[E_USER_PRELOAD];
	// Change their password.
	Player_Preload("TestPlayer", ret);
	ASSERT(!strcmp(ret[E_USER_PRELOAD_PASS], "24954A7C4E607137A70D701986CC3C3140C143E5B5886362A8ACB647B81592CF1F092C65178F6E3FFFC6691B044D2290215058E09BBE029D23D1D67F41640090"));
	Player_ChangePassword(gBot, "thisisabadpass");
	Player_Preload("TestPlayer", ret);
	ASSERT(!strcmp(ret[E_USER_PRELOAD_PASS], "B506FEEEDFB83EF44A5DC2E00BF1535E58E3B37A044730F2A6718497A224B5455A441F39F9EB91967B38607416A9B85E5DE3CBE3A48E7A77AB5808674EF33822"));
}

PTestClose:Player_ChangePassword(playerid)
{
	// Reset the player.
	Player_ChangePassword(gBot, "thisisanOKpass");
	//Kick(gBot);
}

PTestInit:Player_Preload(playerid)
{
	Player_ForceLogin(gBot);
}

PTest:Player_Preload(playerid)
{
	new
		//name[MAX_PLAYER_NAME],
		ret[E_USER_PRELOAD];
	//GetPlayerName(playerid, name, sizeof (name));
	Player_Preload("TestPlayer", ret);
	ASSERT(Player_GetYID(gBot) == ret[E_USER_PRELOAD_YID]);
	ASSERT(Langs_GetPlayerLanguage(gBot) == ret[E_USER_PRELOAD_LANG]);
	ASSERT(0x12345678 == ret[E_USER_PRELOAD_BITS]);
	ASSERT(gettime() >= ret[E_USER_PRELOAD_DATE]);
}

PTestInit:Player_GetID(playerid)
{
	// So that their password can be changed.
	Player_ForceLogin(gBot);
}

PTest:Player_GetID(playerid)
{
	ASSERT(Player_GetYID(gBot) == 0);
	ASSERT(Player_GetYID(playerid) < 0);
}
