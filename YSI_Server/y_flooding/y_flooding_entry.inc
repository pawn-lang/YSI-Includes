#if defined _INC_y_flooding
	#endinput
#endif
#define _INC_y_flooding

/*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright C 2011
	the Initial Developer. All Rights Reserved.

Contributors:
	Y_Less
	koolk
	JoeBullet/Google63
	g_aSlice/Slice
	Misiur
	samphunter
	tianmeta
	maddinat0r
	spacemud
	Crayder
	Dayvison
	Ahmad45123
	Zeex
	irinel1996
	Yiin-
	Chaprnks
	Konstantinos
	Masterchen09
	Southclaws
	PatchwerkQWER
	m0k1
	paulommu
	udan111

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
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

#include "..\..\YSI_Core\y_utils"
#include "..\..\YSI_Data\y_iterate"
#include "..\..\YSI_Coding\y_hooks"

enum e_FLOOD_ACTION
{
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
	YSI_g_sMaxConnections = -1,
	e_FLOOD_ACTION:YSI_g_sConnectionAction = e_FLOOD_ACTION_NOTHING,
	YSI_g_sOnIncomingConnection = 0;

forward OnFloodLimitExceeded(ip[16], count);

new
	Iterator:FloodingPlayer<MAX_PLAYERS>;

/*-------------------------------------------------------------------------*//**
 * <param name="max">Maximum number of connections allowed from the same IP.</param>
 * <param name="action">What to do if there's too many.</param>
 * <remarks>
 *   Sets the maximum connections allowed from a single IP.
 *   
 *   Options:
 *   
 *   e_FLOOD_ACTION_BLOCK - Kick the latest player on this IP.
 *   e_FLOOD_ACTION_KICK - Kick all players on this IP.
 *   e_FLOOD_ACTION_BAN - Ban the IP and have players time out.
 *   e_FLOOD_ACTION_FBAN - Ban the IP and kick all the players instantly.
 *   e_FLOOD_ACTION_GHOST - Silently force all players on the IP to reconnect.
 *   e_FLOOD_ACTION_OTHER - Call a callback.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock SetMaxConnections(max = -1, e_FLOOD_ACTION:action = e_FLOOD_ACTION_BLOCK)
{
	P:3("SetMaxConnections called: %i, %i", max, _:action);
	YSI_g_sMaxConnections = max;
	YSI_g_sConnectionAction = action;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *   Gets the maximum connections allowed from a single IP.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Flooding_GetMaxConnections()
{
	return YSI_g_sMaxConnections;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *   Gets the action to perform when the limit is exceeded.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock e_FLOOD_ACTION:Flooding_GetConnectionAction()
{
	return YSI_g_sConnectionAction;
}

/*-------------------------------------------------------------------------*//**
 * <param name="ip32">32-bit representation of the IP to unban.</param>
 * <remarks>
 *  Timers, by default, are not good with strings, so we can't pass the IP to
 *  unban in dot notation.  Fortunately, this is easilly solved.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Flooding_UnbanIP(ip32);

public Flooding_UnbanIP(ip32)
{
	new
		cmd[24] = "unbanip ";
	format(cmd[8], 16, "%d.%d.%d.%d", ip32 >>> 24, (ip32 >>> 16) & 0xFF, (ip32 >>> 8) & 0xFF, ip32 & 0xFF);
	SendRconCommand(cmd);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who joined.</param>
 * <param name="ip">Their IP address as a string.</param>
 * <remarks>
 *  Checks for too many connections from the same IP address and acts
 *  accordingly.
 *
 *  Could be edited to only loop through players once but I'm not sure the
 *  extra code required would be faster anyway, definately not easier.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static Flooding_CheckIP(playerid, ip[])
{
	if (0 <= YSI_g_sMaxConnections < MAX_PLAYERS && YSI_g_sConnectionAction)
	{
		new
			ip32 = IPToInt(ip);
		YSI_g_sPlayerIPs[playerid] = ip32;
		// May not have been added to `Player` yet if this is called from
		// `OnIncomingConnection`.
		Iter_Add(FloodingPlayer, playerid);
		FOREACH__ (new i : Player)
		{
			if (YSI_g_sPlayerIPs[i] == ip32)
			{
				Iter_Add(FloodingPlayer, i);
			}
		}
		if (Iter_Count(FloodingPlayer) > YSI_g_sMaxConnections)
		{
			P:I("Max Connections exceeded");
			switch (YSI_g_sConnectionAction)
			{
				case e_FLOOD_ACTION_BLOCK:
				{
					// Kick the latest player.
					Kick(playerid);
				}
				case e_FLOOD_ACTION_KICK:
				{
					// Kick all the players.
					FOREACH__ (new i : FloodingPlayer)
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
					FOREACH__ (new i : FloodingPlayer)
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
					YSI_SetTimerEx("Flooding_UnbanIP", 10000, false, "i", ip32);
				}
				case e_FLOOD_ACTION_OTHER:
				{
					new
						ret = CallLocalFunction("OnFloodLimitExceeded", "si", ip, Iter_Count(FloodingPlayer));
					Iter_Clear(FloodingPlayer);
					return ret;
				}
			}
		}
		Iter_Clear(FloodingPlayer);
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who joined.</param>
 * <param name="ip">Their IP address as a string.</param>
 * <param name="port">Their port.</param>
 * <remarks>
 *  Called before much of the player structure is set up to check incoming
 *  connections.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HOOK__ OnIncomingConnection(playerid, ip_address[], port)
{
	YSI_g_sOnIncomingConnection = true;
	return Flooding_CheckIP(playerid, ip_address);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who joined.</param>
 * <remarks>
 *  Called when a player is connected, for checking on older versions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HOOK__ OnPlayerConnect(playerid)
{
	// To support older versions.
	if (YSI_g_sOnIncomingConnection)
	{
		return 1;
	}
	new
		ip[16];
	GetPlayerIp(playerid, ip, sizeof (ip));
	return Flooding_CheckIP(playerid, ip);
}

