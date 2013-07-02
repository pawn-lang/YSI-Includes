// OnPlayerDeath mhook.
mhook OnPlayerDeath(playerid) {
	AC_players[playerid][AC_pState] &= ~AC_psSpawn;
	return 1;
}
