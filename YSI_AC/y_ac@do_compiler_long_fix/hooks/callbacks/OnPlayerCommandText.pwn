mhook OnPlayerCommandText(playerid, cmdtext[]) {
	AC_players[playerid][AC_pLastUpdate] = GetTickCount();
	return 0;
}
