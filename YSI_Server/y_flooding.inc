/**--------------------------------------------------------------------------**\
					===================================
					Y Sever Includes - Connections Core
					===================================
Description:
	Allows a limited number of connections from a single IP.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI flooding include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
	Thanks:
		JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
		ZeeX - Very productive conversations.
		koolk - IsPlayerinAreaEx code.
		TheAlpha - Danish translation.
		breadfish - German translation.
		Fireburn - Dutch translation.
		yom - French translation.
		50p - Polish translation.
		Zamaroht - Spanish translation.
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Changelog:
	15/11/10:
		Updated to YSI 1.0.
	11/03/08:
		First version.
Functions:
	Public:
		-
	Core:
		OnPlayerConnect - Called to check IPs.
		OnScriptInit - Sets the OnPlayerConnect function flag.
	Stock:
		-
	Static:
		-
	Inline:
		-
	API:
		SetMaxConnections - Sets the max allowed connections from an IP.
Callbacks:
	-
Definitions:
	-
Enums:
	e_FLOOD_ACTION - What to do if too many connections form.
Macros:
	-
Tags:
	-
Variables:
	Global:
		-
	Static:
		YSI_g_sPlayerIPs - People's stored IPs for speed.
		YSI_g_sMaxConnections - Data for the script.
Commands:
	-
Compile options:
	-
Operators:
	-
\**--------------------------------------------------------------------------**/

#if defined _INC_y_flooding
	#endinput
#endif
#define _INC_y_flooding

#include "..\YSI_Internal\y_version"
#include "..\YSI_Data\y_iterate"
#include "..\YSI_Core\y_debug"
#include "..\YSI_Core\y_utils"
#include "..\YSI_Coding\y_hooks"

enum e_FLOOD_ACTION (+= 0x00010000)
{
	e_FLOOD_ACTION_COUNT = 0x0000FFFF,
	e_FLOOD_ACTION_ACTION = 0x000F0000,
	e_FLOOD_ACTION_NOTHING = 0,
	e_FLOOD_ACTION_BLOCK,
	e_FLOOD_ACTION_KICK,
	e_FLOOD_ACTION_BAN,
	e_FLOOD_ACTION_FBAN,
	e_FLOOD_ACTION_GHOST,
	e_FLOOD_ACTION_OTHER
}

static
	YSI_g_sPlayerIPs[MAX_PLAYERS],
	e_FLOOD_ACTION:YSI_g_sMaxConnections = e_FLOOD_ACTION_COUNT | e_FLOOD_ACTION_BLOCK;

forward OnFloodLimitExceeded(ip[16], count);

stock
	Iterator:FloodingPlayer<MAX_PLAYERS>;

/**--------------------------------------------------------------------------**\
<summary>SetMaxConnections</summary>
<param name="max">Maximum number of connections allowed from the same IP.</param>
<param name="e_FLOOD_ACTION:action">What to do if there's too many.</param>
<returns>
	-
</returns>
<remarks>
	Sets the maximum connections allowed from a single IP.
	
	Options:
	
	e_FLOOD_ACTION_BLOCK - Kick the latest player on this IP.
	e_FLOOD_ACTION_KICK - Kick all players on this IP.
	e_FLOOD_ACTION_BAN - Ban the IP and have players time out.
	e_FLOOD_ACTION_FBAN - Ban the IP and kick all the players instantly.
	e_FLOOD_ACTION_GHOST - Silently force all players on the IP to reconnect.
	e_FLOOD_ACTION_OTHER - Call a callback.
</remarks>
\**--------------------------------------------------------------------------**/

stock SetMaxConnections(max = -1, e_FLOOD_ACTION:action = e_FLOOD_ACTION_BLOCK)
{
	P:3("SetMaxConnections called: %i, %i", max, _:action);
	YSI_g_sMaxConnections = (e_FLOOD_ACTION:max & e_FLOOD_ACTION_COUNT) | action;
}

/**--------------------------------------------------------------------------**\
<summary>Flooding_UnbanIP</summary>
<param name="ip32">32-bit representation of the IP to unban.</param>
<returns>
	-
</returns>
<remarks>
	Timers, by default, are not good with strings, so we can't pass the IP to
	unban in dot notation.  Fortunately, this is easilly solved.
</remarks>
\**--------------------------------------------------------------------------**/

forward Flooding_UnbanIP(ip32);

public Flooding_UnbanIP(ip32)
{
	new
		cmd[24] = "unbanip ";
	format(cmd[8], 16, "%d.%d.%d.%d", ip32 >>> 24, (ip32 >>> 16) & 0xFF, (ip32 >>> 8) & 0xFF, ip32 & 0xFF);
	SendRconCommand(cmd);
}

/**--------------------------------------------------------------------------**\
<summary>OnPlayerConnect</summary>
<param name="playerid">Player who joined.</param>
<returns>
	-
</returns>
<remarks>
	Checks for too many connections from the same IP address and acts
	accordingly.
	
	Could be edited to only loop through players once but I'm not sure the
	extra code required would be faster anyway, definately not easier.
</remarks>
\**--------------------------------------------------------------------------**/

hook OnPlayerConnect(playerid)
{
	new
		ret = 1;
	if ((YSI_g_sMaxConnections & e_FLOOD_ACTION_COUNT) != e_FLOOD_ACTION_COUNT)
	{
		new
			ip[16];
		GetPlayerIp(playerid, ip, sizeof (ip));
		new
			ip32 = IPToInt(ip);
		YSI_g_sPlayerIPs[playerid] = ip32;
		foreach (new i : Player)
		{
			if (YSI_g_sPlayerIPs[i] == ip32)
			{
				Iter_Add(FloodingPlayer, i);
			}
		}
		if (Iter_Count(FloodingPlayer) > _:(YSI_g_sMaxConnections & e_FLOOD_ACTION_COUNT))
		{
			P:I("Max Connections exceeded");
			ret = 0;
			switch (YSI_g_sMaxConnections & e_FLOOD_ACTION_ACTION)
			{
				case e_FLOOD_ACTION_BLOCK:
				{
					// Kick the latest player.
					Kick(playerid);
				}
				case e_FLOOD_ACTION_KICK:
				{
					// Kick all the players.
					foreach (new i : FloodingPlayer)
					{
						Kick(i);
					}
				}
				case e_FLOOD_ACTION_BAN:
				{
					// Ban the IP.
					BanEx(playerid, "YSI max connections auto-ban");
				}
				case e_FLOOD_ACTION_FBAN:
				{
					// Ban the IP.
					BanEx(playerid, "YSI max connections auto-ban");
					// Kick all the players.
					foreach (new i : FloodingPlayer)
					{
						Kick(i);
					}
				}
				case e_FLOOD_ACTION_GHOST:
				{
					// Time out all the players on the IP silently.
					new
						cmd[22] = "banip ";
					strcat(cmd, ip);
					SendRconCommand(cmd);
					SetTimerEx("Flooding_UnbanIP", 10000, 0, "i", ip32);
				}
				case e_FLOOD_ACTION_OTHER:
				{
					ret = CallLocalFunction("OnFloodLimitExceeded", "si", ip, Iter_Count(FloodingPlayer));
				}
			}
		}
		// Ultra fast iterator clear.
		for (new i = Iter_Begin(FloodingPlayer); (ip32 = Iter_Next(FloodingPlayer, i)) != i; )
		{
			Iter_TrueArray(FloodingPlayer)[i] = i;
			i = ip32;
		}	
		Iter_TrueCount(FloodingPlayer) = 0;
	}
	return ret;
}

