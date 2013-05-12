// GetPlayerSpecialAction hook.
foreign AC_GetPlayerSpecialAction(playerid);
global AC_GetPlayerSpecialAction(playerid) {
	if (IsPlayerConnected(playerid)) {
		return AC_players[playerid][AC_pSpecialAction];
	}
	return SPECIAL_ACTION_NONE;
}
#if defined _ALS_GetPlayerSpecialAction
	#undef GetPlayerSpecialAction
#else
	#define _ALS_GetPlayerSpecialAction
#endif
#define GetPlayerSpecialAction AC_GetPlayerSpecialAction
