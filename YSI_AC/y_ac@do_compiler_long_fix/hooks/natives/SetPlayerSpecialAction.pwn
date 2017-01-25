// SetPlayerSpecialAction hook.
foreign AC_SetPlayerSpecialAction(playerid, actionid);
global AC_SetPlayerSpecialAction(playerid, actionid) {
	if (IsPlayerConnected(playerid)) {
		AC_players[playerid][AC_pSpecialAction] = actionid;
	}
	return SetPlayerSpecialAction(playerid, actionid);
}
#if defined _ALS_SetPlayerSpecialAction
	#undef SetPlayerSpecialAction
#else
	#define _ALS_SetPlayerSpecialAction
#endif
#define SetPlayerSpecialAction AC_SetPlayerSpecialAction
