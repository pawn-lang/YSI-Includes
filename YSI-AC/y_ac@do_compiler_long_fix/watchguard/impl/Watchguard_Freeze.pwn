/**
 * <summary>Checks if a player is freezed and make sure it stays so.</summary>
 * <param name="playerid">Player's ID.</param>
 */
AC_STOCK AC_Watchguard_Freeze(playerid) {
	if (AC_players[playerid][AC_pState] & AC_psFreeze) {
		TogglePlayerControllable(playerid, false);
	}
}
