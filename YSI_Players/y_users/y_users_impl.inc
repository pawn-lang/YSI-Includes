/*

       =====================================================================================
       | Why is y_users using `SHA256_PassHash`, when it is such a terrible password hash? |
       =====================================================================================

Simple - it isn't using it to hash the password.  At least, not alone.  Unfortunately, one problem
with a user system like this is that at some point it contains the unhashed password in memory,
because the player just typed it in and we need to verify it.  This means we need to pass it around.
The code does this as little as possible, and cleans up as much memory as possible afterwards
(though it remains in the SA:MP server in memory from raknet packets, which we have no way of
fixing).  To minimise this, we do a single basic (cheap fast) hash of the password using
`SHA256_PassHash` first, and pass the result of THAT to the proper `BCrypt` hash function.  This
means we keep a slightly insecure password in memory during processing, instead of a VERY insecure
password.  It also bypasses the `BCrypt` limit of 77 charater passwords by converting the input to
a constant 64 charaters regardless of the initial length.  Even a bug in the BCrypt plugin won't
expose the original password, because it isn't even passed to there.

*/

enum e_USER_ERROR
{
	e_USER_ERROR_OK = 0,
	e_USER_ERROR_TAKEN,           // Name is already registered.
	e_USER_ERROR_UNMATCHED_PASS,  // Two passwords didn't match when registering.
	e_USER_ERROR_UNMATCHED_EMAIL, // Two emails didn't match when registering.
	e_USER_ERROR_LOGIN,           // Login failed (unregistered OR password mismatch).
	e_USER_ERROR_CONNECTION,      // Can't connect to the database.
	e_USER_ERROR_UNKNOWN,         // Other general error.
}

// Both SHA256 and BCrypt are 256bit hashes.
#define Y_USERS_HASH_LENGTH (64 + 1)

static stock
	// HASHES ONLY!  These shouldn't be kept in memory in an ideal solution, but solely compared in
	// a query, i.e. `WHERE password = %e".  However, that can't work with BCrypt because the seeds
	// and complexities are stored in the hash, thus must be loaded before we can hash the second.
	YSI_g_sUserPassword[MAX_PLAYERS][Y_USERS_HASH_LENGTH],
	// We can somewhat mitigate this by only ever having a SHA256 version of the plaintext password
	// in memory.  This is NOT a secure password hash (despite the SA:MP native being called
	// `SHA256_PassHash`); however, it is fast and marginally better than keeping the entirely
	// unhashed password around in memory until the real hashing is complete.
	YSI_g_sSHA256FirstPhase[Y_USERS_HASH_LENGTH];

static stock const
	Y_USERS_FIRST_PASS_SALT[] = "y_users_salt";

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
			YSI_SHA256Hash_BAD_DONT_USE(password[start], Y_USERS_FIRST_PASS_SALT, YSI_g_sSHA256FirstPhase);
			// Wipe out the password.
			SecureCallbackMemory();
			SecureVariableMemory(password);
			// Now do the full hash on the SHA256 hash of the original password.
			User_HashPassword(playerid, YSI_g_sSHA256FirstPhase);
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

