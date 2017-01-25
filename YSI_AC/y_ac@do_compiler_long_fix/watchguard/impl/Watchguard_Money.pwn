/**
 * <summary>Checks if a player is using money hack.</summary>
 * <param name="playerid">Player's ID.</param>
 */
AC_STOCK AC_Watchguard_Money(playerid) {
	new bad_money = U_GetPlayerMoney(playerid), money = GetPlayerMoney(playerid);
	if (bad_money > money) {
		AC_CheatDetected(playerid, AC_cMoney);
	}
}
