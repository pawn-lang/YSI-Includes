// Include pretty much 90% of YSI in one fell swoop!

//#include "..\y_users"
#include "..\y_inline"

loadtext core[ysi_players], core[ysi_extras], core[ysi_dialog];

YCMD:login(playerid, params[], help)
{
	if (help)
	{
		Text_Send(playerid, $YSI_LOGIN_HELP);
	}
	else
	{
		if (Player_IsLoggedIn(playerid))
		{
			Text_Send(playerid, $YSI_LOGIN_ALREADY);
			return 1;
		}
		if (!isnull(params))
		{
			Player_TryLogin(playerid, params);
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
		if (Player_IsLoggedIn(playerid))
		{
			Text_Send(playerid, $YSI_LOGIN_ALREADY);
			return 1;
		}
		new
			pass[32];
		if (!isnull(params))
		{
			// Store the password localy in the function.
			strcpy(pass, params);
			inline Response2(pid2, dialogid2, response2, listitem2, string:text2[])
			{
				#pragma unused listitem2, dialogid2, pid2
				if (response2)
				{
					if (strcmp(pass, text2))
					{
						Text_Send(playerid, $YSI_EXTRA_REGISTER_MISMATCH);
					}
					else
					{
						Player_TryRegister(playerid, text2);
					}
				}
			}
			Text_PasswordBox(playerid, using inline Response2, $YSI_EXTRA_REGISTER_TITLE, $YSI_EXTRA_CONFIRM_PROMPT, $DIALOG_OK, $DIALOG_CANCEL);
			return 1;
		}
		// Didn't type any text, ask for the password twice.
		inline Response1(pid1, dialogid1, response1, listitem1, string:text1[])
		{
			#pragma unused listitem1, dialogid1, pid1
			if (response1)
			{
				inline Response2(pid2, dialogid2, response2, listitem2, string:text2[])
				{
					#pragma unused listitem2, dialogid2, pid2
					if (response2)
					{
						if (strcmp(text1, text2))
						{
							Text_Send(playerid, $YSI_EXTRA_REGISTER_MISMATCH);
						}
						else
						{
							Player_TryRegister(playerid, text2);
						}
					}
				}
				Text_PasswordBox(playerid, using inline Response2, $YSI_EXTRA_REGISTER_TITLE, $YSI_EXTRA_CONFIRM_PROMPT, $DIALOG_OK, $DIALOG_CANCEL);
			}
		}
		Text_PasswordBox(playerid, using inline Response1, $YSI_EXTRA_REGISTER_TITLE, $YSI_EXTRA_REGISTER_PROMPT, $DIALOG_OK, $DIALOG_CANCEL);
	}
	return 1;
}
