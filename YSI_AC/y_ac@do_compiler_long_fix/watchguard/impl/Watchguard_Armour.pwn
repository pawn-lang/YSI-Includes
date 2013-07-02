/**
 * <summary>Checks if a player is using armour hack.</summary>
 * <param name="playerid">Player's ID.</param>
 */
AC_STOCK AC_Watchguard_Armour(playerid) {
	new Float:armour;
	GetPlayerArmour(playerid, armour);
	if (!AC_IsPlayerSynced(playerid, AC_sArmour)) {
		AC_SetPlayerSync(playerid, AC_sArmour, armour == AC_players[playerid][AC_pArmour]);
	} else {
		if (armour > AC_players[playerid][AC_pArmour]) {
			AC_CheatDetected(playerid, AC_cArmour);
		}
		AC_players[playerid][AC_pArmour] = armour;
	}
}
