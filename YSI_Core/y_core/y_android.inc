
static stock gTimers[MAX_PLAYERS];

forward FIXES_OnClientCheckResponse(playerid, actionid, memaddr, retndata);

public FIXES_OnClientCheckResponse(playerid, actionid, memaddr, retndata)
{
	if (actionid == 0x48) 
	{
		if (gTimers[playerid])
		{
			KillTimer(gTimers[playerid]);
			gTimers[playerid] = 0;
		}
	}
	#if defined Android_OnClientCheckResponse
		Android_OnClientCheckResponse(playerid, actionid, memaddr, retndata);
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

forward Android_OnCheckFinished(playerid);

public Android_OnCheckFinished(playerid)
{
	// Silent ban.
	new str[32] = "banip ";
	GetPlayerIp(playerid, str[6], sizeof (str) - 6);
	YSI_SendRconCommand(str);
	gTimers[playerid] = YSI_SetTimerEx("Android_Unban", 1000, false, "i", PlayerIp(playerid));
}

public OnPlayerConnect(playerid)
{
	if (gTimers[playerid])
	{
		KillTimer(gTimers[playerid]);
		gTimers[playerid] = 0;
	}
	SendClientCheck(playerid, 0x48, 0, 0, 2);
	gTimers[playerid] = YSI_SetTimerEx("Android_OnCheckFinished", 1000, false, "i", playerid);
	return 1;
}

