
static stock
	YSI_g_sTimers[MAX_PLAYERS],
	bool:YSI_g_sIsAndoid[MAX_PLAYERS] = bool:-1;

forward FIXES_OnClientCheckResponse(playerid, actionid, memaddr, retndata);

stock bool:IsPCPlayer(playerid)
{
	return YSI_g_sIsAndoid[playerid] == false;
}

stock bool:IsAndroidPlayer(playerid)
{
	return YSI_g_sIsAndoid[playerid] == true;
}

public FIXES_OnClientCheckResponse(playerid, actionid, memaddr, retndata)
{
	if (actionid == 0x48) 
	{
		if (gTimers[playerid])
		{
			KillTimer(gTimers[playerid]);
			gTimers[playerid] = 0;
			if (YSI_g_sIsAndoid[playerid] != false)
			{
				YSI_g_sIsAndoid[playerid] = false;
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
	if (YSI_g_sIsAndoid[playerid] != true)
	{
		CallRemoteFunction("OnAndroidCheck", "ii", playerid, true);
		YSI_g_sIsAndoid[playerid] = true;
	}
#if defined Android_OnAndroidTimer
	Android_OnAndroidTimer(playerid);
#endif
}

public OnPlayerDisconnect(playerid, reason)
{
	if (gTimers[playerid])
	{
		KillTimer(gTimers[playerid]);
		gTimers[playerid] = 0;
	}
#if defined Android_OnPlayerDisconnect
	Android_OnPlayerDisconnect(playerid, reason);
#endif
	return 1;
}

public OnPlayerConnect(playerid)
{
	if (!IS_FILTERSCRIPT)
	{
		SendClientCheck(playerid, 0x48, 0, 0, 2);
		gTimers[playerid] = YSI_SetTimerEx("OnAndroidTimer", 10000, true, "i", playerid);
	}
#if defined Android_OnPlayerConnect
	Android_OnPlayerConnect(playerid);
#endif
	return 1;
}

#if defined _ALS_FIXES_OnClCheckResponse
	#undef FIXES_OnClientCheckResponse
#else
	#define _ALS_FIXES_OnClCheckResponse
#endif
#define FIXES_OnClientCheckResponse Android_OnClientCheckResponse
#if defined Android_OnClientCheckResponse
	forward Android_OnClientCheckResponse(playerid, actionid, memaddr, retndata);
#endif

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect Android_OnPlayerConnect
#if defined Android_OnPlayerConnect
	forward Android_OnPlayerConnect(playerid);
#endif

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect Android_OnPlayerDisconnect
#if defined Android_OnPlayerDisconnect
	forward Android_OnPlayerDisconnect(playerid, reason);
#endif

#if defined _ALS_OnAndroidTimer
	#undef OnAndroidTimer
#else
	#define _ALS_OnAndroidTimer
#endif
#define OnAndroidTimer Android_OnAndroidTimer
#if defined Android_OnAndroidTimer
	forward Android_OnAndroidTimer(playerid, reason);
#endif

