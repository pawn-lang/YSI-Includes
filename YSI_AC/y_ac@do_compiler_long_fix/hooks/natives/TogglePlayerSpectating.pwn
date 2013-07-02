// TogglePlayerSpectating hook.
foreign AC_TogglePlayerSpectating(playerid, toggle);
global AC_TogglePlayerSpectating(playerid, toggle) {
	if (IsPlayerConnected(playerid)) {
		if (toggle) {
			AC_players[playerid][AC_pState] &= ~AC_psSpawn;
		}
	}
	return TogglePlayerSpectating(playerid, toggle);
}
#if defined _ALS_TogglePlayerSpectating
	#undef TogglePlayerSpectating
#else
	#define _ALS_TogglePlayerSpectating
#endif
#define TogglePlayerSpectating AC_TogglePlayerSpectating
