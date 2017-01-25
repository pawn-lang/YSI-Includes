// TogglePlayerControllable hook.
foreign AC_TogglePlayerControllable(playerid, toggle);
global AC_TogglePlayerControllable(playerid, toggle) {
	if (IsPlayerConnected(playerid)) {
		if (toggle) {
			AC_players[playerid][AC_pState] &= ~AC_psFreeze;
		} else {
			AC_players[playerid][AC_pState] |= AC_psFreeze;
		}
	}
	return TogglePlayerControllable(playerid, toggle);
}
#if defined _ALS_TogglePlayerControllable
	#undef TogglePlayerControllable
#else
	#define _ALS_TogglePlayerControllable
#endif
#define TogglePlayerControllable AC_TogglePlayerControllable
