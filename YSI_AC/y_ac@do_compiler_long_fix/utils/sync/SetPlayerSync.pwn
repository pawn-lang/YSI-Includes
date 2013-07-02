/**
 * <summary>Sets a player's sync status.</summary>
 * <param name="playerid">Player's ID.</param>
 * <param name="sync">Sync's ID.</param>
 * <param name="status">Is player synced or not?</param>
 */
AC_STOCK AC_SetPlayerSync(playerid, sync, status = true) {
	if (IsPlayerConnected(playerid)) {
		if (status) {
			AC_players[playerid][AC_pSync] |= 1 << sync;
			AC_players[playerid][AC_pSyncFails][sync] = 0;
		} else {
			AC_players[playerid][AC_pSync] &= ~(1 << sync);
			++AC_players[playerid][AC_pSyncFails][sync];
			if (AC_players[playerid][AC_pSyncFails][sync] % AC_SYNC_MAX_FAILS == 0) {
				AC_CheatDetected(playerid, AC_cSync, sync, "");
			}
		}
	}
}
