// SetPlayerHealth hook.
foreign AC_SetPlayerHealth(playerid, Float:health);
global AC_SetPlayerHealth(playerid, Float:health) {
	if (IsPlayerConnected(playerid)) {
		AC_players[playerid][AC_pHealth] = health;
		AC_SetPlayerSync(playerid, AC_sHealth, false);
	}
	return SetPlayerHealth(playerid, health);
}
#if defined _ALS_SetPlayerHealth
	#undef SetPlayerHealth
#else
	#define _ALS_SetPlayerHealth
#endif
#define SetPlayerHealth AC_SetPlayerHealth
