enum e_USER_ERROR
{
	e_USER_ERROR_OK = 0,
	e_USER_ERROR_TAKEN, // Name is already registered.
	e_USER_ERROR_FAIL,  // Login failed (username or password).
	e_USER_ERROR_CONN,  // Can't connect.
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is logging in.</param>
 * <param name="password">Password they entered.</param>
 * <param name="f">Show the failed to login message?</param>
 * <remarks>
 *  Tries to log in a player - hashes and checks their password and if it's
 *  right calls the core login code.  It doesn't matter WHICH script does this
 *  as they ALL get called and ALL track the login status of a player.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Player_TryRegister(playerid, string:password[])
{
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is logging in.</param>
 * <param name="password">Password they entered.</param>
 * <param name="f">Show the failed to login message?</param>
 * <remarks>
 *  Tries to log in a player - hashes and checks their password and if it's
 *  right calls the core login code.  It doesn't matter WHICH script does this
 *  as they ALL get called and ALL track the login status of a player.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Player_TryLogin(playerid, string:password[])
{
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is joining a group.</param>
 * <param name="other">A player name already in the group.</param>
 * <param name="password">The password of the group.</param>
 * <remarks>
 *  Links a player with an existing player such that they share all stats.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Player_TryGroup(playerid, string:other[], string:password[])
{
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to check.</param>
 * <remarks>
 *  Get this player's YID (unique ID).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Player_GetYID(playerid)
{
	return YSI_g_sPlayerYID[playerid];
}

stock Player_ChangePassword(playerid, string:password[])
{
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to check.</param>
 * <remarks>
 *  Is this player logged in?
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Player_IsLoggedIn(playerid)
{
	// -2 should never be an issue, but if it is...
	return YSI_g_sPlayerYID[playerid] >= 0;
}

stock Player_ForceGroup(playerid, string:other[])
{
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is logging in.</param>
 * <remarks>
 *  Like "Player_TryLogin" but doesn't take a password so always works.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Player_ForceLogin(playerid)
{
}

