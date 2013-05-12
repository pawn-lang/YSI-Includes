/**
 * <summary>Checks if a player is using a joypad.</summary>
 * <param name="playerid">Player's ID.</param>
 */
AC_STOCK AC_Watchguard_Joypad(playerid) {
	new keys, ud, lr;
	GetPlayerKeys(playerid, keys, ud, lr);
	if (((ud != 128) && (ud != 0) && (ud != -128)) || ((lr != 128) && (lr != 0) && (lr != -128))) {
		AC_CheatDetected(playerid, AC_cJoypad);
	}
}
