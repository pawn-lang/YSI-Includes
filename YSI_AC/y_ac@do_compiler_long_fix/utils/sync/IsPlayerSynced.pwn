/**
 * <summary>Checks a player's sync status.</summary>
 * <param name="playerid">Player's ID.</param>
 * <param name="sync">Sync's ID.</param>
 * <returns>True if player is synced, false if not.</returns>
 */
AC_STOCK AC_IsPlayerSynced(playerid, sync) {
	if (IsPlayerConnected(playerid)) {
		return (AC_players[playerid][AC_pSync] & (1 << sync)) ? true : false;
	}
	return false;
}
