/**
 * <summary>Checks if a player is around a vending machine.</summary>
 * <param name="playerid">Player's ID.</param>
 * <returns>True if the player is near a vending machine or false if not.</returns>
 */
AC_STOCK AC_IsPlayerAtVendingMachine(playerid) {
	for (new i = 0; i != sizeof(AC_VENDING_MACHINES); ++i) {
		if (IsPlayerInRangeOfPoint(playerid, AC_VENDING_MACHINE_RANGE, AC_VENDING_MACHINES[i][0], AC_VENDING_MACHINES[i][1], AC_VENDING_MACHINES[i][2])) {
			return true;
		}
	}
	return false;
}
