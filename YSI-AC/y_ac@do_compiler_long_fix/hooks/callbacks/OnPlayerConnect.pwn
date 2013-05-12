// OnPlayerConnect mhook.
mhook OnPlayerConnect(playerid) {
	AC_memset(AC_players[playerid], 0, AC_ePlayer);
	return 1;
}
