/**
 * <summary>Checks if a player is AFK.</summary>
 * <param name="playerid">Player's ID.</param>
 * <returns>True if player is AFK, false if not.</returns>
 */
foreign AC_IsPlayerAFK(playerid);
global AC_IsPlayerAFK(playerid) {
	if (IsPlayerConnected(playerid)) {
		return (GetTickCount() - AC_players[playerid][AC_pLastUpdate]) > AC_AFK_TIME;
	}
	return false;
}
