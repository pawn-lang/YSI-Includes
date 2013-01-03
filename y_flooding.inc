/*----------------------------------------------------------------------------*\
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
\*----------------------------------------------------------------------------*/

#include "internal\y_version"
#include "y_iterate"
#include "y_debug"
#include "y_hooks"

enum e_FLOOD_ACTION (+= 0x00010000)
{
	e_FLOOD_ACTION_COUNT = 0x0000FFFF,
	e_FLOOD_ACTION_ACTION = 0x000F0000,
	e_FLOOD_ACTION_NOTHING = 0,
	e_FLOOD_ACTION_BLOCK,
	e_FLOOD_ACTION_KICK,
	e_FLOOD_ACTION_BAN,
	e_FLOOD_ACTION_FBAN
}

static
	YSI_g_sPlayerIPs[MAX_PLAYERS],
	e_FLOOD_ACTION:YSI_g_sMaxConnections = e_FLOOD_ACTION_COUNT | e_FLOOD_ACTION_BLOCK;

/*----------------------------------------------------------------------------*\
Function:
	SetMaxConnections
Params:
	max - Maximum number of connections allowed from the same IP.
	e_FLOOD_ACTION:action - What to do if there's too many.
Return:
	-
Notes:
	Sets the maximum connections allowed from a single IP.
	
	Options:
	
	e_FLOOD_ACTION_BLOCK - Kick the latest player on this IP.
	e_FLOOD_ACTION_KICK - Kick all players on this IP.
	e_FLOOD_ACTION_BAN - Ban the IP and have players time out.
	e_FLOOD_ACTION_FBAN - Ban the IP and kick all the players instantly.
\*----------------------------------------------------------------------------*/

stock SetMaxConnections(max = -1, e_FLOOD_ACTION:action = e_FLOOD_ACTION_BLOCK)
{
	P:3("SetMaxConnections called: %i, %i", max, _:action);
	YSI_g_sMaxConnections = (e_FLOOD_ACTION:max & e_FLOOD_ACTION_COUNT) | action;
}

/*----------------------------------------------------------------------------*\
Function:
	Conn_OnPlayerConnect
Params:
	playerid - Player who joined.
Return:
	-
Notes:
	Checks for too many connections from the same IP address and acts
	accordingly.
	
	Could be edited to only loop through players once but I'm not sure the
	extra code required would be faster anyway, definately not easier.
\*----------------------------------------------------------------------------*/

hook OnPlayerConnect(playerid)
{
	if ((YSI_g_sMaxConnections & e_FLOOD_ACTION_COUNT) != e_FLOOD_ACTION_COUNT)
	{
		new
			count = 0,
			IP = GetIP(playerid);
		YSI_g_sPlayerIPs[playerid] = IP;
		foreach (new i : Player)
		{
			if (YSI_g_sPlayerIPs[i] == IP)
			{
				++count;
			}
		}
		if (count > _:(YSI_g_sMaxConnections & e_FLOOD_ACTION_COUNT))
		{
			P:0("*** Internal Alert: Max Connections exceeded");
			switch (YSI_g_sMaxConnections & e_FLOOD_ACTION_ACTION)
			{
				case e_FLOOD_ACTION_BLOCK:
				{
					// Kick the latest player.
					Kick(playerid);
					return 0;
				}
				case e_FLOOD_ACTION_KICK:
				{
					// Kick all the players.
					foreach (new i : Player)
					{
						if(YSI_g_sPlayerIPs[i] == IP)
						{
							Kick(i);
						}
					}
					return 0;
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
					foreach (new i : Player)
					{
						if(YSI_g_sPlayerIPs[i] == IP)
						{
							Kick(i);
						}
					}
					return 0;
				}
				default:
				{
					// Do nothing.
					return 1;
				}
			}
		}
		return 0;
	}
	return 1;
}
