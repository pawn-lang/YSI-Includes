// OnPlayerUpdate mhook.
mhook OnPlayerUpdate(playerid) {
	AC_players[playerid][AC_pLastUpdate] = GetTickCount();
	return 1;
}
