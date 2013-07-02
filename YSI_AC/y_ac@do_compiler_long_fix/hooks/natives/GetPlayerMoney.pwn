// GetPlayerMoney hook.
foreign AC_GetPlayerMoney(playerid);
global AC_GetPlayerMoney(playerid) {
	if (IsPlayerConnected(playerid)) {
		new bad_money = U_GetPlayerMoney(playerid);
		return bad_money < AC_players[playerid][AC_pMoney] ? bad_money : AC_players[playerid][AC_pMoney];
	}
	return 0;
}
#if defined _ALS_GetPlayerMoney
	#undef GetPlayerMoney
#else
	#define _ALS_GetPlayerMoney
#endif
#define GetPlayerMoney AC_GetPlayerMoney
