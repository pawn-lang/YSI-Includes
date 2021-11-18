/*
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

#if defined _INC_y_android
	#endinput
#endif
#define _INC_y_android

#if defined YSI_NO_ANDROID_CHECK
	forward Android_UnusedPublic(playerid);
	#define Android_OnAndroidTimer(%0) Android_UnusedPublic(%0){} static stock Android_UnusedStock(%0)

	#endinput
#endif

#if !defined _samp_included
	#endinput
#endif

#include "..\..\YSI_Core\y_core\y_core_entry"
#include "..\..\YSI_Core\y_core\y_rconfix"

static stock
	YSI_g_sTimers[MAX_PLAYERS],
	bool:YSI_g_sIsAndroid[MAX_PLAYERS] = bool:-1;

forward OnAndroidCheck(playerid, bool:isDisgustingThiefToBeBanned);

stock bool:IsPCPlayer(playerid)
{
	return YSI_g_sIsAndroid[playerid] == false;
}

stock bool:IsAndroidPlayer(playerid)
{
	return YSI_g_sIsAndroid[playerid] == true;
}

public OnClientCheckResponse(playerid, actionid, memaddr, retndata)
{
	if (actionid == 0x48) 
	{
		if (YSI_g_sTimers[playerid])
		{
			KillTimer(YSI_g_sTimers[playerid]);
			YSI_g_sTimers[playerid] = 0;
			if (YSI_g_sIsAndroid[playerid] != false)
			{
				YSI_g_sIsAndroid[playerid] = false;
				CallRemoteFunction("OnAndroidCheck", "ii", playerid, false);
			}
		}
	}
	#if defined Android_OnClientCheckResponse
		Android_OnClientCheckResponse(playerid, actionid, memaddr, retndata);
	#endif
	return 1;
}

forward OnAndroidTimer(playerid);

public OnAndroidTimer(playerid)
{
	if (YSI_g_sIsAndroid[playerid] != true)
	{
		YSI_g_sIsAndroid[playerid] = true;
		CallRemoteFunction("OnAndroidCheck", "ii", playerid, true);
	}
//#if defined Android_OnAndroidTimer
//	Android_OnAndroidTimer(playerid);
//#endif
}

public OnPlayerDisconnect(playerid, reason)
{
	if (YSI_g_sTimers[playerid])
	{
		KillTimer(YSI_g_sTimers[playerid]);
		YSI_g_sTimers[playerid] = 0;
	}
#if defined Android_OnPlayerDisconnect
	Android_OnPlayerDisconnect(playerid, reason);
#endif
	return 1;
}

public OnPlayerConnect(playerid)
{
	if (!Script_IsFilterscript())
	{
		YSI_SendClientCheck(playerid, 0x48, 0, 0, 2);
		YSI_g_sTimers[playerid] = YSI_SetTimerEx("OnAndroidTimer", 10000, true, "i", playerid);
	}
#if defined Android_OnPlayerConnect
	Android_OnPlayerConnect(playerid);
#endif
	return 1;
}

#if _YSI_SAFE_STARTUP
	public OnYSIInit()
	{
		if (Script_IsGameMode())
		{
			y_rconfix_Load();
		}
		#if defined Android_OnYSIInit
			Android_OnYSIInit();
		#endif
		return 1;
	}

	#if defined _ALS_OnYSIInit
		#undef OnYSIInit
	#else
		#define _ALS_OnYSIInit
	#endif
	#define OnYSIInit Android_OnYSIInit

	#if defined Android_OnYSIInit
		forward Android_OnYSIInit();
	#endif
#endif

#if defined _ALS_OnClientCheckResponse
	#undef OnClientCheckResponse
#else
	#define _ALS_OnClientCheckResponse
#endif
#define OnClientCheckResponse( Android_OnClientCheckResponse(
#if defined Android_OnClientCheckResponse
	forward Android_OnClientCheckResponse(playerid, actionid, memaddr, retndata);
#endif

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect( Android_OnPlayerConnect(
#if defined Android_OnPlayerConnect
	forward Android_OnPlayerConnect(playerid);
#endif

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect( Android_OnPlayerDisconnect(
#if defined Android_OnPlayerDisconnect
	forward Android_OnPlayerDisconnect(playerid, reason);
#endif

#if defined _ALS_OnAndroidTimer
	#undef OnAndroidTimer
#else
	#define _ALS_OnAndroidTimer
#endif
#define OnAndroidTimer( Android_OnAndroidTimer(
#if defined Android_OnAndroidTimer
	forward Android_OnAndroidTimer(playerid);
#endif

