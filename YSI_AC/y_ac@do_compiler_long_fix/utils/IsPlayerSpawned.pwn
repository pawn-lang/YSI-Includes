/**
 * <summary>Checks if a player is spawned.</summary>
 * <param name="playerid">Player's ID.</param>
 * <returns>True if player is spawned, false if not.</returns>
 */
foreign AC_IsPlayerSpawned(playerid);
global AC_IsPlayerSpawned(playerid) {
	if (IsPlayerConnected(playerid)) {
		return AC_players[playerid][AC_pState] & AC_psSpawn ? true : false;
	}
	return false;
}
