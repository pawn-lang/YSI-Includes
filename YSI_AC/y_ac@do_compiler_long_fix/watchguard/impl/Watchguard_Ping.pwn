/**
 * <summary>Checks if a player is using armour hack.</summary>
 * <param name="playerid">Player's ID.</param>
 */
AC_STOCK AC_Watchguard_Ping(playerid) {
	if (GetPlayerPing(playerid) > AC_MAX_PING) {
		AC_CheatDetected(playerid, AC_cPing);
	}
}
