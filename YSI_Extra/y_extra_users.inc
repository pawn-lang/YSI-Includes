#if defined _INC_y_extra_users
	#endinput
#endif
#define _INC_y_extra_users

// Include pretty much 90% of YSI in one fell swoop!

//#include "..\y_users"
#include "..\YSI_Coding\y_inline"

loadtext core[ysi_players], core[ysi_extras], core[ysi_dialog];

/**--------------------------------------------------------------------------**\
<summary>
	Extra_DoLogin
	Commands: /login
</summary>
<param name="playerid">Player trying to log in.</param>
<param name="string:pw[]">The password they entered.</param>
<returns>
	-
</returns>
<remarks>
	Called when a player attempts to log in.  If "pw" is empty (NULL) this
	prompts the user for a password with a dialog.  If it isn't empty then it
	takes that as the password.
</remarks>
\**--------------------------------------------------------------------------**/

stock Extra_DoLogin(playerid, string:pw[])
{
	if (Player_IsLoggedIn(playerid))
	{
		Text_Send(playerid, $YSI_LOGIN_ALREADY);
		return 1;
	}
	else if (!Player_IsRegistered(playerid))
	{
		//Text_Send(playerid, $YSI_LOGIN_ALREADY);
		Text_Send(playerid, $YSI_LOGIN_NOTF);
		Extra_DoRegister(playerid, NULL);
		return 1;
	}
	if (!isnull(pw))
	{
		Player_TryLogin(playerid, pw);
		return 1;
	}
	inline Response(pid, dialogid, response, listitem, string:text0[])
	{
		#pragma unused pid, dialogid, listitem
		if (response)
		{
			Player_TryLogin(playerid, text0);
		}
	}
	Text_PasswordBox(playerid, using inline Response, $YSI_EXTRA_LOGIN_TITLE, $YSI_EXTRA_LOGIN_PROMPT, $DIALOG_OK, $DIALOG_CANCEL);
	return 1;
}

YCMD:login(playerid, params[], help)
{
	if (help)
	{
		Text_Send(playerid, $YSI_LOGIN_HELP);
	}
	else
	{
		Extra_DoLogin(playerid, params);
	}
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>
	Extra_DoRegister
	Command: /register
</summary>
<param name="playerid">Player trying to log in.</param>
<param name="string:pw[]">The password they entered.</param>
<returns>
	-
</returns>
<remarks>
	Called when a player attempts to register.  If "pw" is empty (NULL) this
	prompts the user for a password with a dialog.  If it isn't empty then it
	takes that as the password and asks for confirmation.
	
	Currently this only checks the length of the password for strength, it
	doesn't check other properties such as number/case/symbol mixes.
</remarks>
\**--------------------------------------------------------------------------**/

stock Extra_DoRegister(playerid, string:pw[])
{
	if (Player_IsLoggedIn(playerid))
	{
		Text_Send(playerid, $YSI_LOGIN_ALREADY);
		return 1;
	}
	else if (Player_IsRegistered(playerid))
	{
		//Text_Send(playerid, $YSI_LOGIN_ALREADY);
		Text_Send(playerid, $YSI_REG_TAKEN);
		Extra_DoLogin(playerid, NULL);
		return 1;
	}
	if (isnull(pw))
	{
		// Enter password.
		inline Response1(pid1, dialogid1, response1, listitem1, string:text1[])
		{
			#pragma unused listitem1, dialogid1, pid1
			if (response1)
			{
				switch (strlen(text1))
				{
					case 0:
					{
						Text_Send(playerid, $YSI_LOGIN_ENTER);
					}
					case 1:
					{
						if (isnull(text1)) Text_Send(playerid, $YSI_LOGIN_ENTER);
						else Text_Send(playerid, $YSI_LOGIN_LENGTH);
					}
					case 2 .. 5:
					{
						Text_Send(playerid, $YSI_LOGIN_LENGTH);
					}
					default:
					{
						// Can add code here to test the strength of the pass.
						Extra_DoRegister(playerid, text1);
						return 1;
					}
				}
				Extra_DoRegister(playerid, NULL);
			}
		}
		Text_PasswordBox(playerid, using inline Response1, $YSI_EXTRA_REGISTER_TITLE, $YSI_EXTRA_REGISTER_PROMPT, $DIALOG_OK, $DIALOG_CANCEL);
	}
	else
	{
		// Store the password localy in the function and get confirmation.
		new
			pass[32];
		strcpy(pass, pw);
		inline Response2(pid2, dialogid2, response2, listitem2, string:text2[])
		{
			#pragma unused listitem2, dialogid2, pid2
			if (response2)
			{
				switch (strlen(text2))
				{
					case 0:
					{
						Text_Send(playerid, $YSI_LOGIN_ENTER);
					}
					case 1:
					{
						if (isnull(text2)) Text_Send(playerid, $YSI_LOGIN_ENTER);
						else Text_Send(playerid, $YSI_LOGIN_LENGTH);
					}
					case 2 .. 5:
					{
						Text_Send(playerid, $YSI_LOGIN_LENGTH);
					}
					default:
					{
						if (strcmp(pass, text2))
						{
							Text_Send(playerid, $YSI_EXTRA_REGISTER_MISMATCH);
						}
						else
						{
							Player_TryRegister(playerid, text2);
							return 1;
						}
					}
				}
				// Try again.
				Extra_DoRegister(playerid, pass);
			}
		}
		Text_PasswordBox(playerid, using inline Response2, $YSI_EXTRA_REGISTER_TITLE, $YSI_EXTRA_CONFIRM_PROMPT, $DIALOG_OK, $DIALOG_CANCEL);
	}
	return 1;
}

YCMD:register(playerid, params[], help)
{
	if (help)
	{
		Text_Send(playerid, $YSI_REGISTER_HELP);
	}
	else
	{
		Extra_DoRegister(playerid, params);
	}
	return 1;
}
