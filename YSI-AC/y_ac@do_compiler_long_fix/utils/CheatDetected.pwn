/**
 * Triggers the `Anticheat_OnCheatDetected` callback.
 * <param name="playerid">Player's ID.</param>
 * <param name="cheatid">Cheat ID.</param>
 * <param name="extraid">Additional cheat ID (depends on hack tool, detection method, etc.).</param>
 * <param name="info">Additional information.</param>
 */
AC_STOCK AC_CheatDetected(playerid, cheatid, extraid = 0, info[] = "") {
	P:1("[anticheat] AC_CheatDetected(playerid = %d, cheatid = %d, extraid = %d, info = %s", playerid, cheatid, extraid, info);
	if (isnull(info)) {
		CallLocalFunction(#AC_OnCheatDetected, "iiis", playerid, cheatid, extraid, "\1");
	} else {
		CallLocalFunction(#AC_OnCheatDetected, "iiis", playerid, cheatid, extraid, info);
	}
}