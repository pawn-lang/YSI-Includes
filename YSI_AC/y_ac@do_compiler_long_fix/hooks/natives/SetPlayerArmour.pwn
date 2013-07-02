// SetPlayerArmour hook.
foreign AC_SetPlayerArmour(playerid, Float:armour);
global AC_SetPlayerArmour(playerid, Float:armour) {
	if (IsPlayerConnected(playerid)) {
		AC_players[playerid][AC_pArmour] = armour;
		AC_SetPlayerSync(playerid, AC_sArmour, false);
	}
	return SetPlayerArmour(playerid, armour);
}
#if defined _ALS_SetPlayerArmour
	#undef SetPlayerArmour
#else
	#define _ALS_SetPlayerArmour
#endif
#define SetPlayerArmour AC_SetPlayerArmour
