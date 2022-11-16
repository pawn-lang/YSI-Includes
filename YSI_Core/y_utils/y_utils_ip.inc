/**
 * <library
 *   name="y_utils - ip"
 *   version="0.1.3"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Misc functions used throughout."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 *//** *//*
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
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
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
	Cheaterman

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

/// <p/>

#if defined _samp_included && !defined YSI_NO_GET_IP
	stock
		YSI_gPlayerIP[MAX_PLAYERS + 1] = {-1, ...};

	public OnPlayerConnect(playerid)
	{
		new
			ip[16];
		GetPlayerIp(playerid, ip, sizeof (ip)),
		YSI_gPlayerIP[playerid] = IPToInt(ip);
		ScriptInit_OnPlayerConnect(playerid);
		return 1;
	}

	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif
	#define OnPlayerConnect(%0) CHAIN_PUBLIC:ScriptInit_OnPlayerConnect(%0)
	CHAIN_FORWARD:ScriptInit_OnPlayerConnect(playerid) = 1;

	public OnPlayerDisconnect(playerid, reason)
	{
		ScriptInit_OnPlayerDisconnect(playerid, reason);
		YSI_gPlayerIP[playerid] = -1;
		return 1;
	}

	#if defined _ALS_OnPlayerDisconnect
		#undef OnPlayerDisconnect
	#else
		#define _ALS_OnPlayerDisconnect
	#endif
	#define OnPlayerDisconnect(%0) CHAIN_PUBLIC:ScriptInit_OnPlayerDisconnect(%0)
	CHAIN_FORWARD:ScriptInit_OnPlayerDisconnect(playerid, reason) = 1;

	/*-------------------------------------------------------------------------*//**
	 * <library>y_utils - ip</library>
	 * <param name="playerid">Player to get IP of.</param>
	 * <returns>
	 *   IP as a 32bit int.
	 * </returns>
	 *//*------------------------------------------------------------------------**/

	// Cunning macro only uses "%0" once, yet is still safe.
	FUNC_PAWNDOC(GetIP(playerid));
	#define GetIP(%0) (YSI_gPlayerIP[min((%0) + cellmin, MAX_PLAYERS + cellmin) - cellmin])
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - ip</library>
 * <param name="ip">Dot notation IP to convert to an integer.</param>
 * <returns>
 *   The IP.
 * </returns>
 * <remarks>
 *   Converts an IP from a string, such as <c>192.168.0.1</c>, converted to a
 *   32-bit integer, such as <c>0xC0A80001</c>.  Does far fewer checks on the
 *   input than the newer <c>DottedToIntIP</c>, but this function isn't
 *   deprecated for use in situations where the input format is know, such as
 *   directly after a call to <c>GetPlayerIp</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock IPToInt(const string:ip[])
{
	if (YSI_IsLocalVarPackedString__(ip))
	{
		new
			ipv = 0;
		// `strmid` doesn't seem to work correctly on packed strings in SA:MP.
		// Do this the hard way...
		for (new i = 0, ch, tmp, pos = 0; i != 4; ++i)
		{
			tmp = 0;
			while ((ch = ip{pos++}) && ch != '.')
			{
				tmp = tmp * 10 + ch - '0';
			}
			ipv = ipv << 8 | tmp;
		}
		return ipv;
	}
	else
	{
		new
			ipv = strval(ip) << 24,
			pos = 0;
		while (pos < 15 && ip[pos++] != '.') {}
		ipv += strval(ip[pos]) << 16;
		while (pos < 15 && ip[pos++] != '.') {}
		ipv += strval(ip[pos]) << 8;
		while (pos < 15 && ip[pos++] != '.') {}
		return ipv + strval(ip[pos]);
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - ip</library>
 * <param name="ip">Dot notation IP to convert to an integer.</param>
 * <param name="out">Destination.</param>
 * <returns>
 *   <c>true</c> if the conversion worked, <c>false</c> if the input didn't start
 *   with a valid IP.
 * </returns>
 * <remarks>
 *   Converts an IP from a string, such as <c>192.168.0.1</c>, converted to a
 *   32-bit integer, such as <c>0xC0A80001</c>.  Does far more checks on the
 *   input than the older <c>IPToInt</c>, but that function isn't deprecated for
 *   use in situations where the input format is know, such as directly after a
 *   call to <c>GetPlayerIp</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:DottedToIntIP(const string:ip[], &out)
{
	if (YSI_IsLocalVarPackedString__(ip))
	{
		new
			part = 0,
			idx = 0,
			component = -1,
			ch;
		for ( ; ; )
		{
			switch ((ch = ip{idx++}))
			{
			case '.':
			{
				// No value in the last section.
				if (component == -1)
				{
					break;
				}
				// Save the segment.
				out = (out << 8) | component;
				// Trailing `.`, just allow it.
				if (++part == 4)
				{
					return true;
				}
				component = -1;
			}
			case '0'..'9':
			{
				if (component == -1)
				{
					component = ch - '0';
				}
				else if ((component = (component * 10) + (ch - '0')) > 255)
				{
					// The current IP part got too large.
					break;
				}
			}
			default:
			{
				// No value in the last section.
				if (part == 3 && component != -1)
				{
					// Save the segment.  We only allow trailing rubbish after
					// the last component.
					out = (out << 8) | component;
					return true;
				}
				break;
			}
			}
		}
	}
	else
	{
		new
			part = 0,
			idx = 0,
			component = -1,
			ch;
		for ( ; ; )
		{
			switch ((ch = ip[idx++]))
			{
			case '.':
			{
				// No value in the last section.
				if (component == -1)
				{
					break;
				}
				// Save the segment.
				out = (out << 8) | component;
				// Trailing `.`, just allow it.
				if (++part == 4)
				{
					return true;
				}
				component = -1;
			}
			case '0'..'9':
			{
				if (component == -1)
				{
					component = ch - '0';
				}
				else if ((component = (component * 10) + (ch - '0')) > 255)
				{
					// The current IP part got too large.
					break;
				}
			}
			default:
			{
				// No value in the last section.
				if (part == 3 && component != -1)
				{
					// Save the segment.  We only allow trailing rubbish after
					// the last component.
					out = (out << 8) | component;
					return true;
				}
				break;
			}
			}
		}
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - ip</library>
 * <param name="dest">Where to render the dotted notation IP.</param>
 * <param name="ip">Integer IP version.</param>
 * <param name="len">Size of the destination string.</param>
 *//*------------------------------------------------------------------------**/

stock IntToIP(string:dest[], ip, len = sizeof (dest))
{
	format(dest, len, "%d.%d.%d.%d", ip >>> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - ip</library>
 * <param name="dest">Destination string.</param>
 * <param name="ip">The IP to censor, as a 32-bit int.</param>
 * <param name="parts">How many parts of the IP to keep.</param>
 * <param name="len">Maximum length of the destination.</param>
 * <returns>
 *   <c>false</c> if <c>parts</c> was invalid, otherwise <c>true</c>.
 * </returns>
 * <remarks>
 *   Replaces some parts of an IP with stars (<c>*</c>) to hide the full thing.
 *   There are four components in a dotted IP, so the number of stars returned is
 *   <c>4 - parts</c>.  For example <c>CensorIntIP(dest, 0xC0A80001, 3);</c> may
 *   return <c>"192.168.0.*"</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:CensorIntIP(string:dest[], ip, parts = 2, len = sizeof (dest))
{
	switch (parts)
	{
	case 0:
		// *.*.*.*
		strcpy(dest, "*.*.*.*", len);
	case 1:
		// 192.*.*.*
		format(dest, len, "%d.*.*.*", ip >>> 24);
	case 2:
		// 192.168.*.*
		format(dest, len, "%d.%d.*.*", ip >>> 24, (ip >> 16) & 0xFF);
	case 3:
		// 192.168.0.*
		format(dest, len, "%d.%d.%d.*", ip >>> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF);
	case 4:
		// 192.168.0.1
		format(dest, len, "%d.%d.%d.%d", ip >>> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
	default:
		return false;
	}
	return true;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - ip</library>
 * <param name="dest">Destination string.</param>
 * <param name="ip">Input IP address in dotted notation.</param>
 * <param name="parts">How many parts of the IP to keep.</param>
 * <param name="len">Maximum length of the destination.</param>
 * <returns>
 *   <c>true</c> if the censoring worked, <c>false</c> if the input wasn't a
 *   valid IP, or <c>parts</c> was invalid.
 * </returns>
 * <remarks>
 *   Replaces some parts of an IP with stars (<c>*</c>) to hide the full thing.
 *   There are four components in a dotted IP, so the number of stars returned is
 *   <c>4 - parts</c>.  For example <c>CensorIP(dest, "192.168.0.1", 3);</c> will
 *   return <c>"192.168.0.*"</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:CensorDottedIP(string:dest[], const string:ip[], parts = 2, len = sizeof (dest))
{
	new out;
	if (!DottedToIntIP(ip, out))
	{
		return false;
	}
	return CensorIntIP(dest, out, parts, len);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - ip</library>
 * <param name="dest">Destination string.</param>
 * <param name="playerid">The player whose IP will be used.</param>
 * <param name="parts">How many parts of the IP to keep.</param>
 * <param name="len">Maximum length of the destination.</param>
 * <returns>
 *   <c>true</c> if the censoring worked, <c>false</c> if the input wasn't a
 *   valid IP.
 * </returns>
 * <remarks>
 *   Replaces some parts of an IP with stars (<c>*</c>) to hide the full thing.
 *   There are four components in a dotted IP, so the number of stars returned is
 *   <c>4 - parts</c>.  For example <c>CensorPlayerIP(dest, playerid, 3);</c> may
 *   return <c>"192.168.0.*"</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:CensorPlayerIP(string:dest[], playerid, parts = 2, len = sizeof (dest))
{
	if (IS_IN_RANGE(playerid, 0, MAX_PLAYERS))
	{
		return CensorIntIP(YSI_gPlayerIP[playerid]);
	}
	return false;
}

