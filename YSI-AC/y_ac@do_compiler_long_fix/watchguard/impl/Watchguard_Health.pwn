/**
 * <summary>Checks if a player is using health hack.</summary>
 * <param name="playerid">Player's ID.</param>
 */
AC_STOCK AC_Watchguard_Health(playerid) {
	new Float:health;
	GetPlayerHealth(playerid, health);
	if (!AC_IsPlayerSynced(playerid, AC_sHealth)) {
		AC_SetPlayerSync(playerid, AC_sHealth, health == AC_players[playerid][AC_pHealth]);
	} else {
		if ((!AC_IsPlayerAtVendingMachine(playerid)) && (health > AC_players[playerid][AC_pHealth])) {
			AC_CheatDetected(playerid, AC_cHealth);
		}
		AC_players[playerid][AC_pHealth] = health;
	}
}
