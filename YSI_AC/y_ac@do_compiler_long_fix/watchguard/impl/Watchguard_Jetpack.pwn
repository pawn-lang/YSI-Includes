/**
 * <summary>Checks if a player is using jetpack hack.</summary>
 * <param name="playerid">Player's ID.</param>
 */
AC_STOCK AC_Watchguard_Jetpack(playerid) {
	new bad_action = U_GetPlayerSpecialAction(playerid), action = GetPlayerSpecialAction(playerid);
	if ((bad_action == SPECIAL_ACTION_USEJETPACK) && (action != SPECIAL_ACTION_USEJETPACK)) {
		// TODO: Check if the player is near a jetpack pickup.
		AC_CheatDetected(playerid, AC_cJetpack);
	}
}
