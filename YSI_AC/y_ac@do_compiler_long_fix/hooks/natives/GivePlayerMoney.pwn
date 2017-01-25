// GivePlayerMoney hook.
foreign AC_GivePlayerMoney(playerid, money);
global AC_GivePlayerMoney(playerid, money) {
	if (IsPlayerConnected(playerid)) {
		AC_players[playerid][AC_pMoney] += money;
	}
	return GivePlayerMoney(playerid, money);
}
#if defined _ALS_GivePlayerMoney
	#undef GivePlayerMoney
#else
	#define _ALS_GivePlayerMoney
#endif
#define GivePlayerMoney AC_GivePlayerMoney
