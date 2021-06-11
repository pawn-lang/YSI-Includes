enum e_USER_ERROR
{
	e_USER_ERROR_OK = 0,
	e_USER_ERROR_TAKEN, // Name is already registered.
	e_USER_ERROR_FAIL,  // Login failed (username or password).
	e_USER_ERROR_CONN,  // Can't connect.
}

static stock SecureVariableMemory(string:string[])
{
	// Removes the password from memory.
	memset(string, 0, strlen(string));
}

static stock SecureCallbackMemory()
{
	// Blanks the first page in y_malloc space, which is used for callback heap-
	// allocated arguments.  This goes some way to trying to ensure that any
	// copies of the password still in that memory are also destroyed.  This
	// requires y_malloc, not because we allocate things (though we might), but
	// just to know for certain what is in any page of memory.

	// Unfortunately `YSI_DEFAULT_MALLOC` can't be used directly in `FILL`,
	// because compiler reasons...
	rawMemset(AMX_HEADER_HEA, 0, YSI_DEFAULT_MALLOC * cellbytes);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is logging in.</param>
 * <param name="password">Password they entered.</param>
 * <remarks>
 *  Stores a HASHED version of the password, as a first input, for later
 *  confirmation.
 * </remarks>
 *//*------------------------------------------------------------------------**/

User_RegisterPassword(playerid, string:password[])
{
	new
		start,
		end;
	// Find the start of the text.
	for (new i = 0, ch; ((ch = password[i])); ++i)
	{
		if (ch > ' ')
		{
			start = i;
			// Find the end of the text.
			while ((ch = password[i++]))
			{
				if (ch > ' ')
				{
					// NOT an OBOE, despite the `i++` above.
					end = i;
				}
			}
			// End the string.
			password[end] = '\0';
			//_YSI_ConstMod(password[end], '\0');
			// Got the start and the end.
			User_HashPassword(playerid, password[start]);
			// Wipe out the password.
			SecureCallbackMemory();
			SecureVariableMemory(password);
			return true;
		}
	}
	// No text given.
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is logging in.</param>
 * <param name="password">Password they entered.</param>
 * <remarks>
 *  Double-checks the entered password.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock User_ConfirmPassword(playerid, string:password[])
{
	if (isnull(YSI_g_sUserPassword[playerid]))
	{
		// They don't have a password yet.
		return false;
	}
	new
		start,
		end;
	// Find the start of the text.
	for (new i = 0, ch; ((ch = password[i])); ++i)
	{
		if (ch > ' ')
		{
			start = i;
			// Find the end of the text.
			while ((ch = password[i++]))
			{
				if (ch > ' ')
				{
					// NOT an OBOE, despite the `i++` above.
					end = i;
				}
			}
			// End the string.
			password[end] = '\0';
			//_YSI_ConstMod(password[end], '\0');
			// Got the start and the end.
			User_VerifyPassword(playerid, YSI_g_sUserPassword[playerid], password[start]);
			// Wipe out the password.
			SecureCallbackMemory();
			SecureVariableMemory(password);
			return true;
		}
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is logging in.</param>
 * <param name="email">Email they entered.</param>
 * <remarks>
 *  Stores the e-mail the player is registering with.
 * </remarks>
 *//*------------------------------------------------------------------------**/

bool:User_RegisterEmail(playerid, string:email[])
{
	new
		start,
		end;
	// Find the start of the text.
	for (new i = 0, ch; ((ch = email[i])); ++i)
	{
		if (ch > ' ')
		{
			start = i;
			// Find the end of the text.
			while ((ch = email[i++]))
			{
				if (ch > ' ')
				{
					// NOT an OBOE, despite the `i++` above.
					end = i;
				}
			}
			// Got the start and the end.  Just remember it.
			YSI_g_sUserEmail[playerid][0] = '\0';
			// Only copy exactly the right number of characters over.  Trims.
			strcat(YSI_g_sUserEmail[playerid], email[start], min(sizeof (YSI_g_sUserEmail[]), end - start + 1));
			return true;
		}
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is logging in.</param>
 * <param name="email">Email they entered.</param>
 * <remarks>
 *  Double-checks the entered e-mail.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:User_ConfirmEmail(playerid, string:email[])
{
	new len = strlen(YSI_g_sUserEmail[playerid]);
	if (len == 0)
	{
		// They don't have a password yet.
		return false;
	}
	new
		start,
		end;
	// Find the start of the text.
	for (new i = 0, ch; ((ch = email[i])); ++i)
	{
		if (ch > ' ')
		{
			start = i;
			// Find the end of the text.
			while ((ch = email[i++]))
			{
				if (ch > ' ')
				{
					// NOT an OBOE, despite the `i++` above.
					end = i;
				}
			}
			// Defer the call, so it looks like a callback in the same way as
			// confirming a password.  Check the length first.
			YSI_SetTimerEx("OnConfirmEmail", 0, false, "ii", playerid, len == end - start && strcmp(YSI_g_sUserEmail[playerid], email[start], false, len) == 0);
			return true;
		}
	}
	return false;
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

