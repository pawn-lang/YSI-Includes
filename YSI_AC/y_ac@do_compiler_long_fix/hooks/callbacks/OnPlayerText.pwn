// OnPlayerText mhook.
mhook OnPlayerText(playerid, text[]) {
	AC_players[playerid][AC_pLastUpdate] = GetTickCount();
	return 1;
}
