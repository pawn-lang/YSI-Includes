/**--------------------------------------------------------------------------**\
					==============================
					 y_hooks - Hook any callback!
					==============================
Description:
	Automatically hooks any callbacks with a very simple syntax.
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
	
	The Original Code is the SA:MP callback hooks include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2008
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
	Thanks:
		JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
		Peter, Cam - Support.
		ZeeX, g_aSlice/Slice, Popz, others - Very productive conversations.
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
	
Version:
	2.0
Changelog:
	02/01/13:
		Rewrote the system to do away with ALS.
		Removed overflow checks in every callback.
		Streamlined code.
	14/04/12:
		Added crash fix from Slice, now returning correct values.
		Fixed ALS detection of mode callbacks.
	25/02/12:
		Extracted most of the code to a separate file.
	17/03/11:
		Second complete re-write using another new technique.  Now VERY fast!
		Updated OnPlayerUpdate code using Google63's SCTRL jump code.
	06/08/10:
		First version
</remarks>
\**--------------------------------------------------------------------------**/

#include "internal\y_version"

#include <a_samp>

#include "y_debug"
#include "y_amx"

#include "internal\y_plugins"

#define ALS_MAKE<%0...%1> %0S@@%1

#if !defined YSI_FILTERSCRIPT
	new
		bool:YSI_FILTERSCRIPT = false;
#endif

#define hook%0On%1(%2) UNIQUE_FUNCTION<@yH_%1...>(%2);UNIQUE_FUNCTION<@yH_%1...>(%2)
#define rehook%0On%1(%2) UNIQUE_FUNCTION<@yH_%1...>(%2)

#define Hook:%0On%1(%2) UNIQUE_FUNCTION<@yH_%1...%0>(%2);UNIQUE_FUNCTION<@yH_%1...%0>(%2)

#include "y_als"

#if !defined HOOKS_MAX_UPDATES
	// Slight increase from the previous version.
	#define HOOKS_MAX_UPDATES           (8)
#endif

// These defines now use the much more generic ALS code so that the list of
// callbacks is only done in one place.
#define HOOK_R_INT<%0,%2>(%3) return ALS_MAKE<..._On%0>(ALS_TS_%3);
#define HOOK_RETURN<%0> ALS_DO:HOOK_R_INT<%0>

#define HOOK_F_INT<%0,%2>(%3) forward ALS_MAKE<..._On%0>(ALS_KS_%3);
#define HOOK_FORWARD<%0> ALS_DO:HOOK_F_INT<%0>

#define HOOK_C_INT<%0,%2>(%3) ret=ALS_MAKE<..._On%0>(ALS_TS_%3);hooks_do_hooks_call_no_als:return ret;
#define HOOK_CALL<%0> ALS_DO:HOOK_C_INT<%0>

static stock
	YSI_g_sCallbackAddresses[HOOKS_MAX_UPDATES * _:ALS],
	YSI_g_sCallbackStart[ALS],
	YSI_g_sCallbackEnd[ALS];

static Hooks_Blank_Return1N()
{
	// Bug fix from Slice.
	return -1;
}

static Hooks_Blank_Return0()
{
	return 0;
}

static Hooks_Blank_Return1()
{
	return 1;
}

stock Hooks_RedirectPublic(from[], to[], final = 1)
{
	//return 0;
	P:4("Hooks_RedirectPublic called: \"%s\", \"%s\"", from, to);
	new
		addr = strfind(from, "(");
	if (addr != -1) from[addr] = '\0';
	if (AMX_GetPublicEntry(0, addr, from))
	{
		new
			pointer,
			ret = AMX_Read(addr);
		if (AMX_GetPublicPointer(0, pointer, to))
		{
			AMX_Write(addr, pointer);
		}
		else
		{
			// Can't find the next element, just remove this callback entirely.
			// Note that in some cases the previous ALS include will have
			// already (due to the constant chaining order) determined that
			// there IS a next callback for this type (because there is) and set
			// some internal variable stating this fact.  When it comes to call
			// it, however, the callback will no longer exist (unless PAWN
			// buffers callbacks in an efficient structure, which is possible).
			// UPDATE: Clearly not.
			switch (final)
			{
				case 0:
				{
					#emit CONST.pri   Hooks_Blank_Return0
					#emit STOR.S.pri  pointer
				}
				case -1:
				{
					#emit CONST.pri   Hooks_Blank_Return1N
					#emit STOR.S.pri  pointer
				}
				default:
				{
					#emit CONST.pri   Hooks_Blank_Return1
					#emit STOR.S.pri  pointer
				}
			}
			AMX_Write(addr, pointer);
		}
		return ret;
	}
	return 0;
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_AddOne</summary>
<param name="idx">Public function table index.</param>
<param name="&toaddidx">Current slot in the global array.</param>
<returns>
	-
</returns>
<remarks>
	Stores a public function by index in to the array of function pointers.
</remarks>
\**--------------------------------------------------------------------------**/

static Hooks_AddOne(idx, &toaddidx)
{
	// This is a combination between the count and the end point.
	if (toaddidx == sizeof (YSI_g_sCallbackAddresses))
	{
		P:E("Out of y_hooks callback addresses");
	}
	else
	{
		new
			addr = (idx - 1) * 8 + AMX_HEADER_PUBLICS;
		#emit LREF.S.pri addr
		#emit STOR.S.pri addr
		YSI_g_sCallbackAddresses[toaddidx++] = addr;
	}
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_FindAll</summary>
<param name="name[]">Callback to find.</param>
<param name="&toaddidx">Current slot in the global array.</param>
<param name="&start">Where to store the start index.</param>
<param name="&end">Where to store the end index.</param>
<returns>
	-
</returns>
<remarks>
	Finds all public functions with the standard y_hooks prefix and a suffix of
	the given string, as well as the y_hooks ALS next call (if there is one).
</remarks>
\**--------------------------------------------------------------------------**/

static Hooks_FindAll(name[], &toaddidx, &start, &end)
{
	P:4("Hooks_FindAll called: %s %d", name, toaddidx);
	P:4("Hooks_FindAll called: %s %d", name, toaddidx);
	new
		buffer[32],
		len = strlen(name),
		idx;
	start = toaddidx - 1;
	// Find all the y_hooks "hook" callbacks.
	while ((idx = AMX_GetPublicNamePrefix(idx, buffer, _A<@yH_>)))
	{
		if (!strcmp(name, buffer[1], false, len) && ('0' <= buffer{4 + len} <= '9'))
		{
			P:6("%d (%d) %s", idx, toaddidx, unpack(buffer));
			Hooks_AddOne(idx, toaddidx);
		}
	}
	// Find the next item in the ALS call chain.
	buffer = "S@@_On";
	strcat(buffer, name);
	// Add 1 as the return of "funcidx" doesn't quite match the return of y_amx.
	if ((idx = funcidx(buffer) + 1))
	{
		P:5("%d (%d) %s", idx, toaddidx, buffer);
		Hooks_AddOne(idx, toaddidx);
	}
	end = toaddidx - 1;
	// Don't store the end, if the count goes off the end of the addresses array
	// then we need to just start reading from the AMX directly.
	P:4("Hooks_FindAll end: %s %d %d", name, toaddidx, end - (start + 1));
	return end - start;
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_RemovePublic</summary>
<param name="from[]">Public function to remove.</param>
<param name="final">The return address to use instead.</param>
<returns>
	The address of "func".
</returns>
<remarks>
	Replaces a public function with another function that only returns the given
	value (must be -1, 0, or 1).
</remarks>
\**--------------------------------------------------------------------------**/

static Hooks_RemovePublic(from[], final)
{
	P:4("Hooks_RemovePublic called: \"%s\", %d", from, final);
	// The macros used add an extra "(" on to the name.  Remove it.
	new
		addr = strfind(from, "(");
	from[addr] = '\0';
	if (AMX_GetPublicEntry(0, addr, from))
	{
		new
			pointer,
			ret = AMX_Read(addr);
		switch (final)
		{
			case 0:
			{
				#emit CONST.pri   Hooks_Blank_Return0
				#emit STOR.S.pri  pointer
			}
			case -1:
			{
				#emit CONST.pri   Hooks_Blank_Return1N
				#emit STOR.S.pri  pointer
			}
			default:
			{
				#emit CONST.pri   Hooks_Blank_Return1
				#emit STOR.S.pri  pointer
			}
		}
		AMX_Write(addr, pointer);
		return ret;
	}
	return 0;
}

#define HOOKS_STRIP_ME)%0, ,

#define HOOKS_DO_ONE_CALLBACK<%0> if(!Hooks_FindAll(#%0,cidx,_:YSI_g_sCallbackStart[ALS_On%0],_:YSI_g_sCallbackEnd[ALS_On%0]))Hooks_RemovePublic(#On%0(HOOKS_STRIP_ME),ALS_R_%0);
//#define HOOKS_DO_ONE_CALLBACK<%0> Hooks_FindAll(#%0,cidx,_:YSI_g_sCallbackStart[ALS_On%0],_:YSI_g_sCallbackEnd[ALS_On%0]);

//static Hooks_OnScriptInit()
public OnScriptInit()
{
	P:2("Hooks_OnScriptInit called");
	#if defined S@@_OnScriptInit
		S@@_OnScriptInit();
	#endif
	new
		cidx;
	printf(" ");
	for (new i = 0; i != 1000000; ++i) {}
	printf(" ");
	// Initialise the data for all the callbacks.
	HOOKS_DO_ONE_CALLBACK<ScriptInit>
	HOOKS_DO_ONE_CALLBACK<ScriptExit>
	HOOKS_DO_ONE_CALLBACK<GameModeInit>
	HOOKS_DO_ONE_CALLBACK<GameModeExit>
	HOOKS_DO_ONE_CALLBACK<FilterScriptInit>
	HOOKS_DO_ONE_CALLBACK<FilterScriptExit>
	HOOKS_DO_ONE_CALLBACK<PlayerConnect>
	HOOKS_DO_ONE_CALLBACK<PlayerDisconnect>
	HOOKS_DO_ONE_CALLBACK<PlayerSpawn>
	HOOKS_DO_ONE_CALLBACK<PlayerDeath>
	HOOKS_DO_ONE_CALLBACK<VehicleSpawn>
	HOOKS_DO_ONE_CALLBACK<VehicleDeath>
	HOOKS_DO_ONE_CALLBACK<PlayerText>
	HOOKS_DO_ONE_CALLBACK<PlayerCommandText>
	HOOKS_DO_ONE_CALLBACK<PlayerRequestClass>
	HOOKS_DO_ONE_CALLBACK<PlayerEnterVehicle>
	HOOKS_DO_ONE_CALLBACK<PlayerExitVehicle>
	HOOKS_DO_ONE_CALLBACK<PlayerStateChange>
	HOOKS_DO_ONE_CALLBACK<PlayerEnterCheckpoint>
	HOOKS_DO_ONE_CALLBACK<PlayerLeaveCheckpoint>
	HOOKS_DO_ONE_CALLBACK<PlayerEnterRaceCheckpoint>
	HOOKS_DO_ONE_CALLBACK<PlayerLeaveRaceCheckpoint>
	HOOKS_DO_ONE_CALLBACK<RconCommand>
	HOOKS_DO_ONE_CALLBACK<PlayerRequestSpawn>
	HOOKS_DO_ONE_CALLBACK<ObjectMoved>
	HOOKS_DO_ONE_CALLBACK<PlayerObjectMoved>
	HOOKS_DO_ONE_CALLBACK<PlayerPickUpPickup>
	HOOKS_DO_ONE_CALLBACK<VehicleMod>
	HOOKS_DO_ONE_CALLBACK<EnterExitModShop>
	HOOKS_DO_ONE_CALLBACK<VehiclePaintjob>
	HOOKS_DO_ONE_CALLBACK<VehicleRespray>
	HOOKS_DO_ONE_CALLBACK<VehicleDamageStatusUpdate>
	HOOKS_DO_ONE_CALLBACK<PlayerSelectedMenuRow>
	HOOKS_DO_ONE_CALLBACK<PlayerExitedMenu>
	HOOKS_DO_ONE_CALLBACK<PlayerInteriorChange>
	HOOKS_DO_ONE_CALLBACK<PlayerKeyStateChange>
	HOOKS_DO_ONE_CALLBACK<RconLoginAttempt>
	HOOKS_DO_ONE_CALLBACK<PlayerUpdate>
	HOOKS_DO_ONE_CALLBACK<PlayerStreamIn>
	HOOKS_DO_ONE_CALLBACK<PlayerStreamOut>
	HOOKS_DO_ONE_CALLBACK<VehicleStreamIn>
	HOOKS_DO_ONE_CALLBACK<VehicleStreamOut>
	HOOKS_DO_ONE_CALLBACK<DialogResponse>
	HOOKS_DO_ONE_CALLBACK<PlayerClickPlayer>
	HOOKS_DO_ONE_CALLBACK<PlayerGiveDamage>
	HOOKS_DO_ONE_CALLBACK<PlayerTakeDamage>
	HOOKS_DO_ONE_CALLBACK<PlayerClickMap>
	HOOKS_DO_ONE_CALLBACK<UnoccupiedVehicleUpdate>
	// 0.3e
	HOOKS_DO_ONE_CALLBACK<PlayerClickTextDraw>
	HOOKS_DO_ONE_CALLBACK<PlayerClickPlayerTextDraw>
	HOOKS_DO_ONE_CALLBACK<PlayerEditObject>
	HOOKS_DO_ONE_CALLBACK<PlayerEditAttachedObject>
	HOOKS_DO_ONE_CALLBACK<PlayerSelectObject>
	// YSI
	HOOKS_DO_ONE_CALLBACK<PlayerEnterArea>
	HOOKS_DO_ONE_CALLBACK<PlayerLeaveArea>
	HOOKS_DO_ONE_CALLBACK<PlayerFinishRace>
	HOOKS_DO_ONE_CALLBACK<PlayerExitRace>
	HOOKS_DO_ONE_CALLBACK<RaceEnd>
	// Streamer plugin.
	#if defined _YSI_PLUGINS_STREAMER
		HOOKS_DO_ONE_CALLBACK<DynamicObjectMoved>
		HOOKS_DO_ONE_CALLBACK<PlayerEditDynamicObject>
		HOOKS_DO_ONE_CALLBACK<PlayerSelectDynamicObject>
		HOOKS_DO_ONE_CALLBACK<PlayerPickUpDynamicPickup>
		HOOKS_DO_ONE_CALLBACK<PlayerEnterDynamicCP>
		HOOKS_DO_ONE_CALLBACK<PlayerLeaveDynamicCP>
		HOOKS_DO_ONE_CALLBACK<PlayerEnterDynamicRaceCP>
		HOOKS_DO_ONE_CALLBACK<PlayerLeaveDynamicRaceCP>
		HOOKS_DO_ONE_CALLBACK<PlayerEnterDynamicArea>
		HOOKS_DO_ONE_CALLBACK<PlayerLeaveDynamicArea>
	#endif
	// YSI callbacks.
	HOOKS_DO_ONE_CALLBACK<PlayerLogin>
	HOOKS_DO_ONE_CALLBACK<PlayerLogout>
	#if defined YSI_LOCK_MODE
		YSI_gLockData[1] = floatround(floatlog(_LOCK_LEN_0 + 1), floatround_ceil);
		YSI_gLockData[0] = 5 + YSI_gLockData[1];
		YSI_gLockData[2] = YSI_gLockData[0] - 5;
		if (~strval(YSI_gLockData[5]) != ~_LOCK_IP_0)
		{
			y_lock 2;
		}
		YSI_gLockData[2] -= YSI_gLockData[1];
		YSI_gLockData[YSI_gLockData[2] + 1] -= YSI_gLockData[0];
		YSI_gLockData[1] += '.' + 5;
	#endif
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnScriptInit],
		start = _:YSI_g_sCallbackStart[ALS_OnScriptInit];
	#if defined S@@_OnScriptInit
		// Do all but one other callback - we already did the ALS forward first.
		--end;
	#endif
	while (start++ != end)
	{
		//printf("%d %d", start, end);
		#emit PUSH.C     0
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
	}
	return ALS_R_ScriptInit;
}
#if defined _ALS_OnScriptInit
	#undef OnScriptInit
#else
	#define _ALS_OnScriptInit
#endif
#define OnScriptInit S@@_OnScriptInit
#if defined S@@_OnScriptInit
	forward S@@_OnScriptInit();
#endif

public OnScriptExit()
{
	P:2("Hooks_OnScriptExit called");
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnScriptExit],
		start = _:YSI_g_sCallbackStart[ALS_OnScriptExit];
	while (start++ != end)
	{
		#emit PUSH.C     0
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
	}
	return ALS_R_ScriptExit;
}
#if defined _ALS_OnScriptExit
	#undef OnScriptExit
#else
	#define _ALS_OnScriptExit
#endif
#define OnScriptExit S@@_OnScriptExit
HOOK_FORWARD<ScriptExit>

public OnGameModeInit()
{
	P:2("Hooks_OnGameModeInit called");
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnGameModeInit],
		start = _:YSI_g_sCallbackStart[ALS_OnGameModeInit];
	while (start++ != end)
	{
		//printf("Hooks_OnGameModeInit: %d %d %d", start, end, YSI_g_sCallbackAddresses[start]);
		#emit PUSH.C     0
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
	}
	return ALS_R_GameModeInit;
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit S@@_OnGameModeInit
HOOK_FORWARD<GameModeInit>

public OnGameModeExit()
{
	P:2("Hooks_OnGameModeExit called %d %d %d", _:ALS_OnGameModeExit, _:YSI_g_sCallbackStart[ALS_OnGameModeExit], _:YSI_g_sCallbackEnd[ALS_OnGameModeExit]);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnGameModeExit],
		start = _:YSI_g_sCallbackStart[ALS_OnGameModeExit];
	while (start++ != end)
	{
		//printf("Hooks_OnGameModeExit: %d %d", start, end);
		//printf("Hooks_OnGameModeExit: %d", YSI_g_sCallbackAddresses[start]);
		#emit PUSH.C     0
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
	}
	return ALS_R_GameModeExit;
}
#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit S@@_OnGameModeExit
HOOK_FORWARD<GameModeExit>

public OnFilterScriptInit()
{
	P:2("Hooks_OnFilterScriptInit called");
	#if defined YSI_LOCK_MODE
		if (strval(YSI_gLockData[strfind(YSI_gLockData[5], YSI_gLockData[1])]) | strval(YSI_gLockData[strfind(YSI_gLockData[YSI_gLockData[0]], YSI_gLockData[1], _, 1)]) << 8 != _LOCK_IP_1 | _LOCK_IP_2 << 8)
		{
			y_lock 4;
		}
	#endif
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnFilterScriptInit],
		start = _:YSI_g_sCallbackStart[ALS_OnFilterScriptInit];
	while (start++ != end)
	{
		#emit PUSH.C     0
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
	}
	return ALS_R_FilterScriptInit;
}
#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit S@@_OnFilterScriptInit
HOOK_FORWARD<FilterScriptInit>

public OnFilterScriptExit()
{
	P:2("Hooks_OnFilterScriptExit called");
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnFilterScriptExit],
		start = _:YSI_g_sCallbackStart[ALS_OnFilterScriptExit];
	while (start++ != end)
	{
		#emit PUSH.C     0
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
	}
	return ALS_R_FilterScriptExit;
}
#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit S@@_OnFilterScriptExit
HOOK_FORWARD<FilterScriptExit>

public OnPlayerConnect(playerid)
{
	P:2("Hooks_OnPlayerConnect called: %d", playerid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerConnect],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerConnect],
		ret = ALS_R_PlayerConnect;
	while (start++ != end)
	{
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect S@@_OnPlayerConnect
HOOK_FORWARD<PlayerConnect>

public OnPlayerDisconnect(playerid, reason)
{
	P:2("Hooks_OnPlayerDisconnect called: %d, %d", playerid, reason);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerDisconnect],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerDisconnect],
		ret = ALS_R_PlayerDisconnect;
	while (start++ != end)
	{
		#emit PUSH.S reason
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect S@@_OnPlayerDisconnect
HOOK_FORWARD<PlayerDisconnect>

public OnPlayerSpawn(playerid)
{
	P:2("Hooks_OnPlayerSpawn called: %d", playerid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerSpawn],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerSpawn],
		ret = ALS_R_PlayerSpawn;
	while (start++ != end)
	{
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn S@@_OnPlayerSpawn
HOOK_FORWARD<PlayerSpawn>

public OnPlayerDeath(playerid, killerid, reason)
{
	P:2("Hooks_OnPlayerDeath called: %d, %d, %d", playerid, killerid, reason);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerDeath],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerDeath],
		ret = ALS_R_PlayerDeath;
	while (start++ != end)
	{
		#emit PUSH.S reason
		#emit PUSH.S killerid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath S@@_OnPlayerDeath
HOOK_FORWARD<PlayerDeath>

public OnVehicleSpawn(vehicleid)
{
	P:2("Hooks_OnVehicleSpawn called: %d", vehicleid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnVehicleSpawn],
		start = _:YSI_g_sCallbackStart[ALS_OnVehicleSpawn],
		ret = ALS_R_VehicleSpawn;
	while (start++ != end)
	{
		#emit PUSH.S vehicleid
		#emit PUSH.C     4
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnVehicleSpawn
	#undef OnVehicleSpawn
#else
	#define _ALS_OnVehicleSpawn
#endif
#define OnVehicleSpawn S@@_OnVehicleSpawn
HOOK_FORWARD<VehicleSpawn>

public OnVehicleDeath(vehicleid, killerid)
{
	P:2("Hooks_OnVehicleDeath called: %d, %d", vehicleid, killerid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnVehicleDeath],
		start = _:YSI_g_sCallbackStart[ALS_OnVehicleDeath],
		ret = ALS_R_VehicleDeath;
	while (start++ != end)
	{
		#emit PUSH.S killerid
		#emit PUSH.S vehicleid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnVehicleDeath
	#undef OnVehicleDeath
#else
	#define _ALS_OnVehicleDeath
#endif
#define OnVehicleDeath S@@_OnVehicleDeath
HOOK_FORWARD<VehicleDeath>

public OnPlayerText(playerid, text[])
{
	P:2("Hooks_OnPlayerText called: %d, \"%s\"", playerid, text);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerText],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerText],
		ret = ALS_R_PlayerText;
	while (start++ != end)
	{
		#emit PUSH.S text
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerText
	#undef OnPlayerText
#else
	#define _ALS_OnPlayerText
#endif
#define OnPlayerText S@@_OnPlayerText
HOOK_FORWARD<PlayerText>

public OnPlayerCommandText(playerid, cmdtext[])
{
	P:2("Hooks_OnPlayerCommandText called: %d, \"%s\"", playerid, cmdtext);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerCommandText],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerCommandText],
		ret = ALS_R_PlayerCommandText;
	while (start++ != end)
	{
		#emit PUSH.S cmdtext
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		// THIS CODE IS SUBTLY DIFFERENT!
		#emit LOAD.S.alt ret
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerCommandText
	#undef OnPlayerCommandText
#else
	#define _ALS_OnPlayerCommandText
#endif
#define OnPlayerCommandText S@@_OnPlayerCommandText
HOOK_FORWARD<PlayerCommandText>

public OnPlayerRequestClass(playerid, classid)
{
	P:2("Hooks_OnPlayerRequestClass called: %d, %d", playerid, classid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerRequestClass],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerRequestClass],
		ret = ALS_R_PlayerRequestClass;
	while (start++ != end)
	{
		#emit PUSH.S classid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerRequestClass
	#undef OnPlayerRequestClass
#else
	#define _ALS_OnPlayerRequestClass
#endif
#define OnPlayerRequestClass S@@_OnPlayerRequestClass
HOOK_FORWARD<PlayerRequestClass>

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	P:2("Hooks_OnPlayerEnterVehicle called: %d, %d, %d", playerid, vehicleid, ispassenger);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerEnterVehicle],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerEnterVehicle],
		ret = ALS_R_PlayerEnterVehicle;
	while (start++ != end)
	{
		#emit PUSH.S ispassenger
		#emit PUSH.S vehicleid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerEnterVehicle
	#undef OnPlayerEnterVehicle
#else
	#define _ALS_OnPlayerEnterVehicle
#endif
#define OnPlayerEnterVehicle S@@_OnPlayerEnterVehicle
HOOK_FORWARD<PlayerEnterVehicle>

public OnPlayerExitVehicle(playerid, vehicleid)
{
	P:2("Hooks_OnPlayerExitVehicle called: %d, %d", playerid, vehicleid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerExitVehicle],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerExitVehicle],
		ret = ALS_R_PlayerExitVehicle;
	while (start++ != end)
	{
		#emit PUSH.S vehicleid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerExitVehicle
	#undef OnPlayerExitVehicle
#else
	#define _ALS_OnPlayerExitVehicle
#endif
#define OnPlayerExitVehicle S@@_OnPlayerExitVehicle
HOOK_FORWARD<PlayerExitVehicle>

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	P:2("Hooks_OnPlayerStateChange called: %d, %d, %d", playerid, newstate, oldstate);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerStateChange],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerStateChange],
		ret = ALS_R_PlayerStateChange;
	while (start++ != end)
	{
		#emit PUSH.S oldstate
		#emit PUSH.S newstate
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange S@@_OnPlayerStateChange
HOOK_FORWARD<PlayerStateChange>

public OnPlayerEnterCheckpoint(playerid)
{
	P:2("Hooks_OnPlayerEnterCheckpoint called: %d", playerid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerEnterCheckpoint],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerEnterCheckpoint],
		ret = ALS_R_PlayerEnterCheckpoint;
	while (start++ != end)
	{
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerEnterCheckpoint
	#undef OnPlayerEnterCheckpoint
#else
	#define _ALS_OnPlayerEnterCheckpoint
#endif
#define OnPlayerEnterCheckpoint S@@_OnPlayerEnterCheckpoint
HOOK_FORWARD<PlayerEnterCheckpoint>

public OnPlayerLeaveCheckpoint(playerid)
{
	P:2("Hooks_OnPlayerLeaveCheckpoint called: %d", playerid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerLeaveCheckpoint],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerLeaveCheckpoint],
		ret = ALS_R_PlayerLeaveCheckpoint;
	while (start++ != end)
	{
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerLeaveCheckpoint
	#undef OnPlayerLeaveCheckpoint
#else
	#define _ALS_OnPlayerLeaveCheckpoint
#endif
#define OnPlayerLeaveCheckpoint S@@_OnPlayerLeaveCheckpoint
HOOK_FORWARD<PlayerLeaveCheckpoint>

public OnPlayerEnterRaceCheckpoint(playerid)
{
	P:2("Hooks_OnPlayerEnterRaceCheckpoint called: %d", playerid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerEnterRaceCheckpoint],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerEnterRaceCheckpoint],
		ret = ALS_R_PlayerEnterRaceCheckpoint;
	while (start++ != end)
	{
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerEnterRaceCP
	#undef OnPlayerEnterRaceCheckpoint
#else
	#define _ALS_OnPlayerEnterRaceCP
#endif
#define OnPlayerEnterRaceCheckpoint S@@_OnPlayerEnterRaceCheckpoint
HOOK_FORWARD<PlayerEnterRaceCheckpoint>

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	P:2("Hooks_OnPlayerLeaveRaceCheckpoint called: %d", playerid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerLeaveRaceCheckpoint],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerLeaveRaceCheckpoint],
		ret = ALS_R_PlayerLeaveRaceCheckpoint;
	while (start++ != end)
	{
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerLeaveRaceCP
	#undef OnPlayerLeaveRaceCheckpoint
#else
	#define _ALS_OnPlayerLeaveRaceCP
#endif
#define OnPlayerLeaveRaceCheckpoint S@@_OnPlayerLeaveRaceCheckpoint
HOOK_FORWARD<PlayerLeaveRaceCheckpoint>

public OnRconCommand(cmd[])
{
	P:2("Hooks_OnRconCommand called: \"%s\"", cmd);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnRconCommand],
		start = _:YSI_g_sCallbackStart[ALS_OnRconCommand],
		ret = ALS_R_RconCommand;
	while (start++ != end)
	{
		#emit PUSH.S cmd
		#emit PUSH.C     4
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnRconCommand
	#undef OnRconCommand
#else
	#define _ALS_OnRconCommand
#endif
#define OnRconCommand S@@_OnRconCommand
HOOK_FORWARD<RconCommand>

public OnPlayerRequestSpawn(playerid)
{
	P:2("Hooks_OnPlayerRequestSpawn called: %d", playerid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerRequestSpawn],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerRequestSpawn],
		ret = ALS_R_PlayerRequestSpawn;
	while (start++ != end)
	{
		//printf("start: %d", start);
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
		//printf("ret: %d", ret);
	}
	return ret;
}
#if defined _ALS_OnPlayerRequestSpawn
	#undef OnPlayerRequestSpawn
#else
	#define _ALS_OnPlayerRequestSpawn
#endif
#define OnPlayerRequestSpawn S@@_OnPlayerRequestSpawn
HOOK_FORWARD<PlayerRequestSpawn>

public OnObjectMoved(objectid)
{
	P:2("Hooks_OnObjectMoved called: %d", objectid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnObjectMoved],
		start = _:YSI_g_sCallbackStart[ALS_OnObjectMoved],
		ret = ALS_R_ObjectMoved;
	while (start++ != end)
	{
		#emit PUSH.S objectid
		#emit PUSH.C     4
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnObjectMoved
	#undef OnObjectMoved
#else
	#define _ALS_OnObjectMoved
#endif
#define OnObjectMoved S@@_OnObjectMoved
HOOK_FORWARD<ObjectMoved>

public OnPlayerObjectMoved(playerid, objectid)
{
	P:2("Hooks_OnPlayerObjectMoved called: %d, %d", playerid, objectid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerObjectMoved],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerObjectMoved],
		ret = ALS_R_PlayerObjectMoved;
	while (start++ != end)
	{
		#emit PUSH.S objectid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerObjectMoved
	#undef OnPlayerObjectMoved
#else
	#define _ALS_OnPlayerObjectMoved
#endif
#define OnPlayerObjectMoved S@@_OnPlayerObjectMoved
HOOK_FORWARD<PlayerObjectMoved>

public OnPlayerPickUpPickup(playerid, pickupid)
{
	P:2("Hooks_OnPlayerPickUpPickup called: %d, %d", playerid, pickupid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerPickUpPickup],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerPickUpPickup],
		ret = ALS_R_PlayerPickUpPickup;
	while (start++ != end)
	{
		#emit PUSH.S pickupid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerPickUpPickup
	#undef OnPlayerPickUpPickup
#else
	#define _ALS_OnPlayerPickUpPickup
#endif
#define OnPlayerPickUpPickup S@@_OnPlayerPickUpPickup
HOOK_FORWARD<PlayerPickUpPickup>

public OnVehicleMod(playerid, vehicleid, componentid)
{
	P:2("Hooks_OnVehicleMod called: %d, %d, %d", playerid, vehicleid, componentid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnVehicleMod],
		start = _:YSI_g_sCallbackStart[ALS_OnVehicleMod],
		ret = ALS_R_VehicleMod;
	while (start++ != end)
	{
		#emit PUSH.S componentid
		#emit PUSH.S vehicleid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnVehicleMod
	#undef OnVehicleMod
#else
	#define _ALS_OnVehicleMod
#endif
#define OnVehicleMod S@@_OnVehicleMod
HOOK_FORWARD<VehicleMod>

public OnEnterExitModShop(playerid, enterexit, interiorid)
{
	P:2("Hooks_OnEnterExitModShop called: %d, %d, %d", playerid, enterexit, interiorid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnEnterExitModShop],
		start = _:YSI_g_sCallbackStart[ALS_OnEnterExitModShop],
		ret = ALS_R_EnterExitModShop;
	while (start++ != end)
	{
		#emit PUSH.S interiorid
		#emit PUSH.S enterexit
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnEnterExitModShop
	#undef OnEnterExitModShop
#else
	#define _ALS_OnEnterExitModShop
#endif
#define OnEnterExitModShop S@@_OnEnterExitModShop
HOOK_FORWARD<EnterExitModShop>

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	P:2("Hooks_OnVehiclePaintjob called: %d, %d, %d", playerid, vehicleid, paintjobid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnVehiclePaintjob],
		start = _:YSI_g_sCallbackStart[ALS_OnVehiclePaintjob],
		ret = ALS_R_VehiclePaintjob;
	while (start++ != end)
	{
		#emit PUSH.S paintjobid
		#emit PUSH.S vehicleid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnVehiclePaintjob
	#undef OnVehiclePaintjob
#else
	#define _ALS_OnVehiclePaintjob
#endif
#define OnVehiclePaintjob S@@_OnVehiclePaintjob
HOOK_FORWARD<VehiclePaintjob>

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	P:2("Hooks_OnVehicleRespray called: %d, %d, %d, %d", playerid, vehicleid, color1, color2);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnVehicleRespray],
		start = _:YSI_g_sCallbackStart[ALS_OnVehicleRespray],
		ret = ALS_R_VehicleRespray;
	while (start++ != end)
	{
		#emit PUSH.S color2
		#emit PUSH.S color1
		#emit PUSH.S vehicleid
		#emit PUSH.S playerid
		#emit PUSH.C     16
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnVehicleRespray
	#undef OnVehicleRespray
#else
	#define _ALS_OnVehicleRespray
#endif
#define OnVehicleRespray S@@_OnVehicleRespray
HOOK_FORWARD<VehicleRespray>

public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	P:2("Hooks_OnVehicleDamageStatusUpdate called: %d, %d", vehicleid, playerid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnVehicleDamageStatusUpdate],
		start = _:YSI_g_sCallbackStart[ALS_OnVehicleDamageStatusUpdate],
		ret = ALS_R_VehicleDamageStatusUpdate;
	while (start++ != end)
	{
		#emit PUSH.S playerid
		#emit PUSH.S vehicleid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnVehicleDamageStatusUpd
	#undef OnVehicleDamageStatusUpdate
#else
	#define _ALS_OnVehicleDamageStatusUpd
#endif
#define OnVehicleDamageStatusUpdate S@@_OnVehicleDamageStatusUpdate
HOOK_FORWARD<VehicleDamageStatusUpdate>

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat)
{
	P:2("Hooks_OnUnoccupiedVehicleUpdate called: %d, %d, %d", vehicleid, playerid, passenger_seat);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnUnoccupiedVehicleUpdate],
		start = _:YSI_g_sCallbackStart[ALS_OnUnoccupiedVehicleUpdate],
		ret = ALS_R_UnoccupiedVehicleUpdate;
	while (start++ != end)
	{
		#emit PUSH.S passenger_seat
		#emit PUSH.S playerid
		#emit PUSH.S vehicleid
		// I wonder if I could hack the stack with a negative number so that when
		// the called function returns it puts all the header data BACK on to the
		// stack instead of removing the parameters and header.
		#emit PUSH.C     12
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnUnoccupiedVehicleUpdate
	#undef OnUnoccupiedVehicleUpdate
#else
	#define _ALS_OnUnoccupiedVehicleUpdate
#endif
#define OnUnoccupiedVehicleUpdate S@@_OnUnoccupiedVehicleUpdate
HOOK_FORWARD<UnoccupiedVehicleUpdate>

public OnPlayerSelectedMenuRow(playerid, row)
{
	P:2("Hooks_OnPlayerSelectedMenuRow called: %d, %d", playerid, row);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerSelectedMenuRow],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerSelectedMenuRow],
		ret = ALS_R_PlayerSelectedMenuRow;
	while (start++ != end)
	{
		#emit PUSH.S row
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerSelectedMenuRow
	#undef OnPlayerSelectedMenuRow
#else
	#define _ALS_OnPlayerSelectedMenuRow
#endif
#define OnPlayerSelectedMenuRow S@@_OnPlayerSelectedMenuRow
HOOK_FORWARD<PlayerSelectedMenuRow>

public OnPlayerExitedMenu(playerid)
{
	P:2("Hooks_OnPlayerExitedMenu called: %d", playerid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerExitedMenu],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerExitedMenu],
		ret = ALS_R_PlayerExitedMenu;
	while (start++ != end)
	{
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerExitedMenu
	#undef OnPlayerExitedMenu
#else
	#define _ALS_OnPlayerExitedMenu
#endif
#define OnPlayerExitedMenu S@@_OnPlayerExitedMenu
HOOK_FORWARD<PlayerExitedMenu>

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	P:2("Hooks_OnPlayerInteriorChange called: %d, %d, %d", playerid, newinteriorid, oldinteriorid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerInteriorChange],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerInteriorChange],
		ret = ALS_R_PlayerInteriorChange;
	while (start++ != end)
	{
		#emit PUSH.S oldinteriorid
		#emit PUSH.S newinteriorid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerInteriorChange
	#undef OnPlayerInteriorChange
#else
	#define _ALS_OnPlayerInteriorChange
#endif
#define OnPlayerInteriorChange S@@_OnPlayerInteriorChange
HOOK_FORWARD<PlayerInteriorChange>

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	P:2("Hooks_OnPlayerKeyStateChange called: %d, %d, %d", playerid, newkeys, oldkeys);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerKeyStateChange],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerKeyStateChange],
		ret = ALS_R_PlayerKeyStateChange;
	while (start++ != end)
	{
		#emit PUSH.S oldkeys
		#emit PUSH.S newkeys
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange S@@_OnPlayerKeyStateChange
HOOK_FORWARD<PlayerKeyStateChange>

public OnRconLoginAttempt(ip[], password[], success)
{
	P:2("Hooks_OnRconLoginAttempt called: \"%s\", \"%s\", %d", ip, password, success);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnRconLoginAttempt],
		start = _:YSI_g_sCallbackStart[ALS_OnRconLoginAttempt],
		ret = ALS_R_RconLoginAttempt;
	while (start++ != end)
	{
		#emit PUSH.S success
		#emit PUSH.S password
		#emit PUSH.S ip
		#emit PUSH.C     12
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnRconLoginAttempt
	#undef OnRconLoginAttempt
#else
	#define _ALS_OnRconLoginAttempt
#endif
#define OnRconLoginAttempt S@@_OnRconLoginAttempt
HOOK_FORWARD<RconLoginAttempt>

public OnPlayerUpdate(playerid)
{
	P:7("Hooks_OnPlayerUpdate called: %d", playerid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerUpdate],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerUpdate],
		ret = ALS_R_PlayerUpdate;
	while (start++ != end)
	{
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate S@@_OnPlayerUpdate
HOOK_FORWARD<PlayerUpdate>

public OnPlayerStreamIn(playerid, forplayerid)
{
	P:2("Hooks_OnPlayerStreamIn called: %d, %d", playerid, forplayerid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerStreamIn],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerStreamIn],
		ret = ALS_R_PlayerStreamIn;
	while (start++ != end)
	{
		#emit PUSH.S forplayerid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerStreamIn
	#undef OnPlayerStreamIn
#else
	#define _ALS_OnPlayerStreamIn
#endif
#define OnPlayerStreamIn S@@_OnPlayerStreamIn
HOOK_FORWARD<PlayerStreamIn>

public OnPlayerStreamOut(playerid, forplayerid)
{
	P:2("Hooks_OnPlayerStreamOut called: %d, %d", playerid, forplayerid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerStreamOut],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerStreamOut],
		ret = ALS_R_PlayerStreamOut;
	while (start++ != end)
	{
		#emit PUSH.S forplayerid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerStreamOut
	#undef OnPlayerStreamOut
#else
	#define _ALS_OnPlayerStreamOut
#endif
#define OnPlayerStreamOut S@@_OnPlayerStreamOut
HOOK_FORWARD<PlayerStreamOut>

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	P:2("Hooks_OnVehicleStreamIn called: %d, %d", vehicleid, forplayerid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnVehicleStreamIn],
		start = _:YSI_g_sCallbackStart[ALS_OnVehicleStreamIn],
		ret = ALS_R_VehicleStreamIn;
	while (start++ != end)
	{
		#emit PUSH.S forplayerid
		#emit PUSH.S vehicleid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnVehicleStreamIn
	#undef OnVehicleStreamIn
#else
	#define _ALS_OnVehicleStreamIn
#endif
#define OnVehicleStreamIn S@@_OnVehicleStreamIn
HOOK_FORWARD<VehicleStreamIn>

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	P:2("Hooks_OnVehicleStreamOut called: %d, %d", vehicleid, forplayerid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnVehicleStreamOut],
		start = _:YSI_g_sCallbackStart[ALS_OnVehicleStreamOut],
		ret = ALS_R_VehicleStreamOut;
	while (start++ != end)
	{
		#emit PUSH.S forplayerid
		#emit PUSH.S vehicleid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnVehicleStreamOut
	#undef OnVehicleStreamOut
#else
	#define _ALS_OnVehicleStreamOut
#endif
#define OnVehicleStreamOut S@@_OnVehicleStreamOut
HOOK_FORWARD<VehicleStreamOut>

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	P:2("Hooks_OnDialogResponse called: %d, %d, %d, %d, \"%s\"", playerid, dialogid, response, listitem, inputtext);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnDialogResponse],
		start = _:YSI_g_sCallbackStart[ALS_OnDialogResponse],
		ret = ALS_R_DialogResponse;
	while (start++ != end)
	{
		#emit PUSH.S inputtext
		#emit PUSH.S listitem
		#emit PUSH.S response
		#emit PUSH.S dialogid
		#emit PUSH.S playerid
		#emit PUSH.C     20
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse S@@_OnDialogResponse
HOOK_FORWARD<DialogResponse>

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	P:2("Hooks_OnPlayerClickPlayer called: %d, %d, %d", playerid, clickedplayerid, source);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerClickPlayer],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerClickPlayer],
		ret = ALS_R_PlayerClickPlayer;
	while (start++ != end)
	{
		#emit PUSH.S source
		#emit PUSH.S clickedplayerid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerClickPlayer
	#undef OnPlayerClickPlayer
#else
	#define _ALS_OnPlayerClickPlayer
#endif
#define OnPlayerClickPlayer S@@_OnPlayerClickPlayer
HOOK_FORWARD<PlayerClickPlayer>

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid)
{
	P:2("Hooks_OnPlayerTakeDamage called: %d, %d, %f, %d", playerid, issuerid, Float:amount, weaponid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerTakeDamage],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerTakeDamage],
		ret = ALS_R_PlayerTakeDamage;
	while (start++ != end)
	{
		#emit PUSH.S weaponid
		#emit PUSH.S amount
		#emit PUSH.S issuerid
		#emit PUSH.S playerid
		#emit PUSH.C     16
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerTakeDamage
	#undef OnPlayerTakeDamage
#else
	#define _ALS_OnPlayerTakeDamage
#endif
#define OnPlayerTakeDamage S@@_OnPlayerTakeDamage
HOOK_FORWARD<PlayerTakeDamage>

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid)
{
	P:2("Hooks_OnPlayerGiveDamage called: %d, %d, %f, %d", playerid, damagedid, Float:amount, weaponid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerGiveDamage],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerGiveDamage],
		ret = ALS_R_PlayerGiveDamage;
	while (start++ != end)
	{
		#emit PUSH.S weaponid
		#emit PUSH.S amount
		#emit PUSH.S damagedid
		#emit PUSH.S playerid
		#emit PUSH.C     16
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerGiveDamage
	#undef OnPlayerGiveDamage
#else
	#define _ALS_OnPlayerGiveDamage
#endif
#define OnPlayerGiveDamage S@@_OnPlayerGiveDamage
HOOK_FORWARD<PlayerGiveDamage>

#if !defined _ALS_OnPlayerLogin
	forward OnPlayerLogin(playerid, uid);
#endif

public OnPlayerLogin(playerid, uid)
{
	P:2("Hooks_OnPlayerLogin called: %d, %d", playerid, uid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerLogin],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerLogin],
		ret = ALS_R_PlayerLogin;
	while (start++ != end)
	{
		#emit PUSH.S uid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerLogin
	#undef OnPlayerLogin
#else
	#define _ALS_OnPlayerLogin
#endif
#define OnPlayerLogin S@@_OnPlayerLogin
HOOK_FORWARD<PlayerLogin>

#if !defined _ALS_OnPlayerLogout
	forward OnPlayerLogout(playerid, uid);
#endif

public OnPlayerLogout(playerid, uid)
{
	P:2("Hooks_OnPlayerLogout called: %d, %d", playerid, uid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerLogout],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerLogout],
		ret = ALS_R_PlayerLogout;
	while (start++ != end)
	{
		#emit PUSH.S uid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerLogout
	#undef OnPlayerLogout
#else
	#define _ALS_OnPlayerLogout
#endif
#define OnPlayerLogout S@@_OnPlayerLogout
HOOK_FORWARD<PlayerLogout>

#if !defined _ALS_OnPlayerEnterArea
	forward OnPlayerEnterArea(playerid, areaid);
#endif

public OnPlayerEnterArea(playerid, areaid)
{
	P:2("Hooks_OnPlayerEnterArea called: %d, %d", playerid, areaid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerEnterArea],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerEnterArea],
		ret = ALS_R_PlayerEnterArea;
	while (start++ != end)
	{
		#emit PUSH.S areaid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerEnterArea
	#undef OnPlayerEnterArea
#else
	#define _ALS_OnPlayerEnterArea
#endif
#define OnPlayerEnterArea S@@_OnPlayerEnterArea
HOOK_FORWARD<PlayerEnterArea>

#if !defined _ALS_OnPlayerLeaveArea
	forward OnPlayerLeaveArea(playerid, areaid);
#endif

public OnPlayerLeaveArea(playerid, areaid)
{
	P:2("Hooks_OnPlayerLeaveArea called: %d, %d", playerid, areaid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerLeaveArea],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerLeaveArea],
		ret = ALS_R_PlayerLeaveArea;
	while (start++ != end)
	{
		#emit PUSH.S areaid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerLeaveArea
	#undef OnPlayerLeaveArea
#else
	#define _ALS_OnPlayerLeaveArea
#endif
#define OnPlayerLeaveArea S@@_OnPlayerLeaveArea
HOOK_FORWARD<PlayerLeaveArea>

#if !defined _ALS_OnPlayerFinishRace
	forward OnPlayerFinishRace(playerid, race, position, prize, time);
#endif

public OnPlayerFinishRace(playerid, race, position, prize, time)
{
	P:2("Hooks_OnPlayerFinishRace called: %d, %d, %d, %d, %d", playerid, race, position, prize, time);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerFinishRace],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerFinishRace],
		ret = ALS_R_PlayerFinishRace;
	while (start++ != end)
	{
		#emit PUSH.S time
		#emit PUSH.S prize
		#emit PUSH.S position
		#emit PUSH.S race
		#emit PUSH.S playerid
		#emit PUSH.C     20
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerFinishRace
	#undef OnPlayerFinishRace
#else
	#define _ALS_OnPlayerFinishRace
#endif
#define OnPlayerFinishRace S@@_OnPlayerFinishRace
HOOK_FORWARD<PlayerFinishRace>

#if !defined _ALS_OnPlayerExitRace
	forward OnPlayerExitRace(playerid, race);
#endif

public OnPlayerExitRace(playerid, race)
{
	P:2("Hooks_OnPlayerExitRace called: %d, %d", playerid, race);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerExitRace],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerExitRace],
		ret = ALS_R_PlayerExitRace;
	while (start++ != end)
	{
		#emit PUSH.S race
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerExitRace
	#undef OnPlayerExitRace
#else
	#define _ALS_OnPlayerExitRace
#endif
#define OnPlayerExitRace S@@_OnPlayerExitRace
HOOK_FORWARD<PlayerExitRace>

#if !defined _ALS_OnRaceEnd
	forward OnRaceEnd(race);
#endif

public OnRaceEnd(race)
{
	P:2("Hooks_OnRaceEnd called: %d", race);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnRaceEnd],
		start = _:YSI_g_sCallbackStart[ALS_OnRaceEnd],
		ret = ALS_R_RaceEnd;
	while (start++ != end)
	{
		#emit PUSH.S race
		#emit PUSH.C     4
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnRaceEnd
	#undef OnRaceEnd
#else
	#define _ALS_OnRaceEnd
#endif
#define OnRaceEnd S@@_OnRaceEnd
HOOK_FORWARD<RaceEnd>

#if !defined OnPlayerClickMap
	#undef ALS_MAKE
	#endinput
#endif

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	P:2("Hooks_OnPlayerClickMap called: %d, %f, %f, %f", playerid, fX, fY, fZ);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerClickMap],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerClickMap],
		ret = ALS_R_PlayerClickMap;
	while (start++ != end)
	{
		#emit PUSH.S fZ
		#emit PUSH.S fY
		#emit PUSH.S fX
		#emit PUSH.S playerid
		#emit PUSH.C     16
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerClickMap
	#undef OnPlayerClickMap
#else
	#define _ALS_OnPlayerClickMap
#endif
#define OnPlayerClickMap S@@_OnPlayerClickMap
HOOK_FORWARD<PlayerClickMap>

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	P:2("Hooks_OnPlayerClickTextDraw called: %d, %d", playerid, _:clickedid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerClickTextDraw],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerClickTextDraw],
		ret = ALS_R_PlayerClickTextDraw;
	while (start++ != end)
	{
		#emit PUSH.S clickedid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw S@@_OnPlayerClickTextDraw
HOOK_FORWARD<PlayerClickTextDraw>

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	P:2("Hooks_OnPlayerClickPlayerTextDraw called: %d, %d", playerid, _:playertextid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerClickPlayerTextDraw],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerClickPlayerTextDraw],
		ret = ALS_R_PlayerClickPlayerTextDraw;
	while (start++ != end)
	{
		#emit PUSH.S playertextid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerClickPlayerTD
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTD
#endif
#define OnPlayerClickPlayerTextDraw S@@_OnPlayerClickPlayerTextDraw
HOOK_FORWARD<PlayerClickPlayerTextDraw>

public OnPlayerEditObject(playerid, playerobject, objectid, response, Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ)
{
	P:2("Hooks_OnPlayerEditObject called: %d, %d, %d, %d, %f, %f, %f, %f, %f, %f", playerid, playerobject, objectid, response, fX, fY, fZ, fRotX, fRotY, fRotZ);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerEditObject],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerEditObject],
		ret = ALS_R_PlayerEditObject;
	while (start++ != end)
	{
		#emit PUSH.S fRotZ
		#emit PUSH.S fRotY
		#emit PUSH.S fRotX
		#emit PUSH.S fZ
		#emit PUSH.S fY
		#emit PUSH.S fX
		#emit PUSH.S response
		#emit PUSH.S objectid
		#emit PUSH.S playerobject
		#emit PUSH.S playerid
		#emit PUSH.C     40
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerEditObject
	#undef OnPlayerEditObject
#else
	#define _ALS_OnPlayerEditObject
#endif
#define OnPlayerEditObject S@@_OnPlayerEditObject
HOOK_FORWARD<PlayerEditObject>

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	P:2("Hooks_OnPlayerEditAttachedObject called: %d, %d, %d, %d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f", playerid, response, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerEditAttachedObject],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerEditAttachedObject],
		ret = ALS_R_PlayerEditAttachedObject;
	while (start++ != end)
	{
		#emit PUSH.S fScaleZ
		#emit PUSH.S fScaleY
		#emit PUSH.S fScaleX
		#emit PUSH.S fRotZ
		#emit PUSH.S fRotY
		#emit PUSH.S fRotX
		#emit PUSH.S fOffsetZ
		#emit PUSH.S fOffsetY
		#emit PUSH.S fOffsetX
		#emit PUSH.S boneid
		#emit PUSH.S modelid
		#emit PUSH.S index
		#emit PUSH.S response
		#emit PUSH.S playerid
		#emit PUSH.C     56
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerEditAttachedObject
	#undef OnPlayerEditAttachedObject
#else
	#define _ALS_OnPlayerEditAttachedObject
#endif
#define OnPlayerEditAttachedObject S@@_OnPlayerEditAttachedObject
HOOK_FORWARD<PlayerEditAttachedObject>
//forward S@@_OnPlayerEditAttachedObject(playerid,response,index,modelid,boneid,Float:fOffsetX,Float:fOffsetY,Float:fOffsetZ,Float:fRotX,Float:fRotY,Float:fRotZ,Float:fScaleX,Float:fScaleY,Float:fScaleZ);
//public S@@_OnPlayerEditAttachedObject(playerid,response,index,modelid,boneid,Float:fOffsetX,Float:fOffsetY,Float:fOffsetZ,Float:fRotX,Float:fRotY,Float:fRotZ,Float:fScaleX,Float:fScaleY,Float:fScaleZ)<_ALS_:unhooked>{return 1;}
//public S@@_OnPlayerEditAttachedObject(playerid,response,index,modelid,boneid,Float:fOffsetX,Float:fOffsetY,Float:fOffsetZ,Float:fRotX,Float:fRotY,Float:fRotZ,Float:fScaleX,Float:fScaleY,Float:fScaleZ)<>{return 1;}

public OnPlayerSelectObject(playerid, type, objectid, modelid, Float:fX, Float:fY, Float:fZ)
{
	P:2("Hooks_OnPlayerSelectObject called: %d, %d, %d, %d, %f, %f, %f", playerid, type, objectid, modelid, fX, fY, fZ);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerSelectObject],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerSelectObject],
		ret = ALS_R_PlayerSelectObject;
	while (start++ != end)
	{
		#emit PUSH.S fZ
		#emit PUSH.S fY
		#emit PUSH.S fX
		#emit PUSH.S modelid
		#emit PUSH.S objectid
		#emit PUSH.S type
		#emit PUSH.S playerid
		#emit PUSH.C     28
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerSelectObject
	#undef OnPlayerSelectObject
#else
	#define _ALS_OnPlayerSelectObject
#endif
#define OnPlayerSelectObject S@@_OnPlayerSelectObject
HOOK_FORWARD<PlayerSelectObject>

// Allow hooking of streamer plugin callbacks.
#if !defined _YSI_PLUGINS_STREAMER
	#undef ALS_MAKE
	#endinput
#endif

public OnDynamicObjectMoved(objectid)
{
	P:2("Hooks_OnDynamicObjectMoved called: %d", objectid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnDynamicObjectMoved],
		start = _:YSI_g_sCallbackStart[ALS_OnDynamicObjectMoved],
		ret = ALS_R_DynamicObjectMoved;
	while (start++ != end)
	{
		#emit PUSH.S objectid
		#emit PUSH.C     4
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnDynamicObjectMoved
	#undef OnDynamicObjectMoved
#else
	#define _ALS_OnDynamicObjectMoved
#endif
#define OnDynamicObjectMoved S@@_OnDynamicObjectMoved
HOOK_FORWARD<DynamicObjectMoved>

public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	P:2("Hooks_OnPlayerEditDynamicObject called: %d, %d, %d, %f, %f, %f, %f, %f, %f", playerid, objectid, response, x, y, z, rx, ry, rz);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerEditDynamicObject],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerEditDynamicObject],
		ret = ALS_R_PlayerEditDynamicObject;
	while (start++ != end)
	{
		#emit PUSH.S rz
		#emit PUSH.S ry
		#emit PUSH.S rx
		#emit PUSH.S z
		#emit PUSH.S y
		#emit PUSH.S x
		#emit PUSH.S response
		#emit PUSH.S objectid
		#emit PUSH.S playerid
		#emit PUSH.C     36
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerEditDynamicObject
	#undef OnPlayerEditDynamicObject
#else
	#define _ALS_OnPlayerEditDynamicObject
#endif
#define OnPlayerEditDynamicObject S@@_OnPlayerEditDynamicObject
HOOK_FORWARD<PlayerEditDynamicObject>
//forward S@@_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);
//public S@@_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)<_ALS_:unhooked>{return 1;}
//public S@@_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)<>{return 1;}

public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
{
	P:2("Hooks_OnPlayerSelectDynamicObject called: %d, %d, %d, %f, %f, %f", playerid, objectid, modelid, x, y, z);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerSelectDynamicObject],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerSelectDynamicObject],
		ret = ALS_R_PlayerSelectDynamicObject;
	while (start++ != end)
	{
		#emit PUSH.S z
		#emit PUSH.S y
		#emit PUSH.S x
		#emit PUSH.S modelid
		#emit PUSH.S objectid
		#emit PUSH.S playerid
		#emit PUSH.C     24
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerSelectDynamicObj
	#undef OnPlayerSelectDynamicObject
#else
	#define _ALS_OnPlayerSelectDynamicObj
#endif
#define OnPlayerSelectDynamicObject S@@_OnPlayerSelectDynamicObject
HOOK_FORWARD<PlayerSelectDynamicObject>
//forward S@@_OnPlayerEditDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z);
//public S@@_OnPlayerEditDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)<_ALS_:unhooked>{return 1;}
//public S@@_OnPlayerEditDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)<>{return 1;}

public OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
	P:2("Hooks_OnPlayerPickUpDynamicPickup called: %d, %d", playerid, pickupid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerPickUpDynamicPickup],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerPickUpDynamicPickup],
		ret = ALS_R_PlayerPickUpDynamicPickup;
	while (start++ != end)
	{
		#emit PUSH.S pickupid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerPickUpDynamicPUp
	#undef OnPlayerPickUpDynamicPickup
#else
	#define _ALS_OnPlayerPickUpDynamicPUp
#endif
#define OnPlayerPickUpDynamicPickup S@@_OnPlayerPickUpDynamicPickup
HOOK_FORWARD<PlayerPickUpDynamicPickup>

public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	P:2("Hooks_OnPlayerEnterDynamicCP called: %d, %d", playerid, checkpointid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerEnterDynamicCP],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerEnterDynamicCP],
		ret = ALS_R_PlayerEnterDynamicCP;
	while (start++ != end)
	{
		#emit PUSH.S checkpointid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerEnterDynamicCP
	#undef OnPlayerEnterDynamicCP
#else
	#define _ALS_OnPlayerEnterDynamicCP
#endif
#define OnPlayerEnterDynamicCP S@@_OnPlayerEnterDynamicCP
HOOK_FORWARD<PlayerEnterDynamicCP>

public OnPlayerLeaveDynamicCP(playerid, checkpointid)
{
	P:2("Hooks_OnPlayerLeaveDynamicCP called: %d, %d", playerid, checkpointid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerLeaveDynamicCP],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerLeaveDynamicCP],
		ret = ALS_R_PlayerLeaveDynamicCP;
	while (start++ != end)
	{
		#emit PUSH.S checkpointid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerLeaveDynamicCP
	#undef OnPlayerLeaveDynamicCP
#else
	#define _ALS_OnPlayerLeaveDynamicCP
#endif
#define OnPlayerLeaveDynamicCP S@@_OnPlayerLeaveDynamicCP
HOOK_FORWARD<PlayerLeaveDynamicCP>

public OnPlayerEnterDynamicRaceCP(playerid, checkpointid)
{
	P:2("Hooks_OnPlayerEnterDynamicRaceCP called: %d, %d", playerid, checkpointid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerEnterDynamicRaceCP],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerEnterDynamicRaceCP],
		ret = ALS_R_PlayerEnterDynamicRaceCP;
	while (start++ != end)
	{
		#emit PUSH.S checkpointid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerEnterDynamicRaceCP
	#undef OnPlayerEnterDynamicRaceCP
#else
	#define _ALS_OnPlayerEnterDynamicRaceCP
#endif
#define OnPlayerEnterDynamicRaceCP S@@_OnPlayerEnterDynamicRaceCP
HOOK_FORWARD<PlayerEnterDynamicRaceCP>

public OnPlayerLeaveDynamicRaceCP(playerid, checkpointid)
{
	P:2("Hooks_OnPlayerLeaveDynamicRaceCP called: %d, %d", playerid, checkpointid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerLeaveDynamicRaceCP],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerLeaveDynamicRaceCP],
		ret = ALS_R_PlayerLeaveDynamicRaceCP;
	while (start++ != end)
	{
		#emit PUSH.S checkpointid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerLeaveDynamicRaceCP
	#undef OnPlayerLeaveDynamicRaceCP
#else
	#define _ALS_OnPlayerLeaveDynamicRaceCP
#endif
#define OnPlayerLeaveDynamicRaceCP S@@_OnPlayerLeaveDynamicRaceCP
HOOK_FORWARD<PlayerLeaveDynamicRaceCP>

public OnPlayerEnterDynamicArea(playerid, areaid)
{
	P:2("Hooks_OnPlayerEnterDynamicArea called: %d, %d", playerid, areaid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerEnterDynamicArea],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerEnterDynamicArea],
		ret = ALS_R_PlayerEnterDynamicArea;
	while (start++ != end)
	{
		#emit PUSH.S areaid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea S@@_OnPlayerEnterDynamicArea
HOOK_FORWARD<PlayerEnterDynamicArea>

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
	P:2("Hooks_OnPlayerLeaveDynamicArea called: %d, %d", playerid, areaid);
	new
		end   = _:YSI_g_sCallbackEnd[ALS_OnPlayerLeaveDynamicArea],
		start = _:YSI_g_sCallbackStart[ALS_OnPlayerLeaveDynamicArea],
		ret = ALS_R_PlayerLeaveDynamicArea;
	while (start++ != end)
	{
		#emit PUSH.S areaid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit CONST.alt  YSI_g_sCallbackAddresses
		#emit LOAD.S.pri start
		//#emit INC.pri
		//#emit STOR.S.pri start
		#emit LIDX
		#emit MOVE.alt
		#emit LCTRL      6
		#emit ADD.C      24
		#emit PUSH.pri
		#emit MOVE.pri
		#emit SCTRL      6
		#emit MOVE.alt
		#emit CONST.pri  0xFFFFFFFE
		#emit AND
		#emit PUSH.pri
		#emit LOAD.S.pri ret
		#emit AND
		#emit POP.alt
		#emit OR
		#emit STOR.S.pri ret
		if (ret < 0) return ret + 1;
	}
	return ret;
}
#if defined _ALS_OnPlayerLeaveDynamicArea
	#undef OnPlayerLeaveDynamicArea
#else
	#define _ALS_OnPlayerLeaveDynamicArea
#endif
#define OnPlayerLeaveDynamicArea S@@_OnPlayerLeaveDynamicArea
HOOK_FORWARD<PlayerLeaveDynamicArea>

#undef ALS_MAKE
