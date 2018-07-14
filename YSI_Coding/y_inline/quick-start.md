# Quick Start

```pawn
#include <YSI_Coding\y_inline>

ShowLogin(MySQL:handle, playerid)
{
	// Called when the player responds to the dialog.
	inline const Login(pid, dialogid, response, listitem, string:inputtext[])
	{
		// `playerid` and `pid` are always the same - so we only really need
		// one of them (`pid` would be required if the inline was elsewhere).
		#pragma unused pid, dialogid, listitem
		
		// Did the user click cancel or not type anything?
		if (!response || isnull(inputtext))
		{
			// Try again.
			SendClientMessage(playerid, COLOUR_ERROR, "Login failed - please enter a password.");
			ShowLogin(handle, playerid);
			return;
		}
		
		// Called when the data is fully loaded from the database.
		inline const Loaded()
		{
			// Was the user found?
			if (cache_get_row_count() != 1)
			{
				// Try again.
				SendClientMessage(playerid, COLOUR_ERROR, "Login failed - unknown username or password.");
				ShowLogin(handle, playerid);
				return;
			}
			
			// Get the password hash and unique (user) ID.
			new
				uid,
				hash[BCRYPT_HASH_LENGTH];
			if (!cache_get_row(0, 0, hash) || !cache_get_row_int(0, 1, uid))
			{
				// There was an error loading the data.  Try again.
				SendClientMessage(playerid, COLOUR_ERROR, "Login failed - please try again.");
				ShowLogin(handle, playerid);
				return;
			}
			
			// Called when the comparison between the stored and entered
			// passwords is complete (so the login is complete).
			inline const Checked()
			{
				// Are the passwords the same?
				if (bcrypt_is_equal())
				{
					// The player logged in.  Tell everything else so they can
					// respond appropriately (start loading data etc.)
					CallRemoteFunction("OnPlayerLogin", "ii", playerid, uid);
				}
				else
				{
					// Typed the wrong password.  But never let the user know
					// the exact reason for the failure - saying `incorrect
					// password` tells them that the account exists, which may
					// be too much information.
					SendClientMessage(playerid, COLOUR_ERROR, "Login failed - unknown username or password.");
					
					// Try again.
					ShowLogin(handle, playerid);
				}
			}
			
			// Check that the DB hash is equal to `inputtext` after hashing.
			// `inputtext` is still in scope here thanks to "closures" -
			// anything defined in an outer function is available in an inner
			// inline.
			BCrypt_CheckInline(inputtext, hash, using inline Checked);
		}
		
		// Request data from the DB on this player.  Search by name.
		new name[MAX_PLAYER_NAME];
		GetPlayerName(playerid, name, sizeof (name));
		MySQL_QueryInline(handle, using inline Loaded, "SELECT `password_hash`, `uid` FROM `users` WHERE `username` = '%e'", name);
	}
	
	// Show the login dialog box.  When it is responded to, the inline function
	// called `Login` is called.  Because inline functions follow scoping rules,
	// this must be defined BEFORE it is used (i.e. above).
	Dialog_ShowCallback(playerid, using inline Login, DIALOG_STYLE_PASSWORD, "Login", "Enter your password below", "OK", "Cancel");
}

public OnPlayerConnect(playerid)
{
	ShowLogin(gMySQL, playerid);
}
```

