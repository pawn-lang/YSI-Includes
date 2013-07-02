// ResetPlayerMoney hook.
foreign AC_ResetPlayerMoney(playerid);
global AC_ResetPlayerMoney(playerid) {
	if (IsPlayerConnected(playerid)) {
		AC_players[playerid][AC_pMoney] = 0;
	}
	return ResetPlayerMoney(playerid);
}
#if defined _ALS_ResetPlayerMoney
	#undef ResetPlayerMoney
#else
	#define _ALS_ResetPlayerMoney
#endif
#define ResetPlayerMoney AC_ResetPlayerMoney
