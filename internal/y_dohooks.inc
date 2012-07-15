/*----------------------------------------------------------------------------*\
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
\*----------------------------------------------------------------------------*/

#include "y_version"
#include <a_samp>
#include "..\y_debug"

#include "..\y_amx"

#define ALS_PREFIX S@@

#if !defined YSI_FILTERSCRIPT
	new
		bool:YSI_FILTERSCRIPT = false;
#endif

#define hook%0On%1(%2) UNIQUE_FUNCTION<@yH_%1...>(%2);UNIQUE_FUNCTION<@yH_%1...>(%2)
//#define master_hook%0On%1(%2) UNIQUE_FUNCTION<@yH_%1...>(%2);UNIQUE_FUNCTION<@yH_%1...>(%2)<>{return ALS_R_%1;}UNIQUE_FUNCTION<@yH_%1...>(%2)<_YCM:y>
#define rehook%0On%1(%2) UNIQUE_FUNCTION<@yH_%1...>(%2)

#define Hook:%0On%1(%2) UNIQUE_FUNCTION<@yH_%1...%0>(%2);UNIQUE_FUNCTION<@yH_%1...%0>(%2)

#include "..\y_als"

/*#if !defined OnPlayerLogin
#endif

#if !defined OnPlayerLogout
#endif*/

//forward Hooks_OnPlayerLogin(playerid, yid);

//forward Hooks_OnPlayerLogout(playerid, yid);

//hook OnPlayerConnect

#if !defined HOOKS_MAX_UPDATES
	// Slight increase from the previous version.
	#define HOOKS_MAX_UPDATES           (8)
#endif

// One of the few places where this is still used.
ALS_DATA<>

// These defines now use the much more generic ALS code so that the list of
// callbacks is only done in one place.
#define HOOK_R_INT<%0,%2>(%3) return Bit_GetBit(Bit:gs_ALS,_:ALS_On%0)?P@(#ALS_PREFIX"_On"#%0,#%2#q,ALS_RS_%3):ret;
#define HOOK_RETURN<%0> ALS_DO:HOOK_R_INT<%0>

#define HOOK_C_INT<%0,%2>(%3) if(Bit_GetBit(Bit:gs_ALS,_:ALS_On%0))return P@(#ALS_PREFIX"_On"#%0,#%2#q,ALS_RS_%3);hooks_do_hooks_call_no_als:return ret;
#define HOOK_CALL<%0> ALS_DO:HOOK_C_INT<%0>


enum E_FUNC_HOOK_DATA
{
	E_FUNC_HOOK_DATA_START,
	E_FUNC_HOOK_DATA_END
}

static stock
	YSI_g_sCallbackAddresses[HOOKS_MAX_UPDATES * _:ALS],
	YSI_g_sCallbackData[ALS][E_FUNC_HOOK_DATA],
	YSI_g_sLastFoundIndex;

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

Hooks_RedirectPublic(from[], to[], final = 1)
{
	P:4("Hooks_RedirectPublic called: \"%s\", \"%s\"", from, to);
	new
		addr;
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
			//AMX_Write(addr, -1);
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

static Hooks_AddOne(idx, &toaddidx, struc[E_FUNC_HOOK_DATA])
{
	// This is a combination between the count and the end point.
	++struc[E_FUNC_HOOK_DATA_END];
	if (toaddidx == sizeof (YSI_g_sCallbackAddresses))
	{
		if (struc[E_FUNC_HOOK_DATA_START] != sizeof (YSI_g_sCallbackAddresses))
		{
			YSI_g_sLastFoundIndex = idx;
		}
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

static Hooks_FindAll(name[], &toaddidx, struc[E_FUNC_HOOK_DATA]) //, &count)
{
	P:4("Hooks_FindAll called: %s %d", name, toaddidx);
	new
		buffer[32],
		len = strlen(name);
	struc[E_FUNC_HOOK_DATA_START] = toaddidx;
	struc[E_FUNC_HOOK_DATA_END] = toaddidx;
	for (new idx; (idx = AMX_GetPublicNamePrefix(idx, buffer, _A<@yH_>)); )
	{
		if (!strcmp(name, buffer[1], false, len))
		{
			Hooks_AddOne(idx, toaddidx, struc);
		}
	}
	if (struc[E_FUNC_HOOK_DATA_START] < sizeof (YSI_g_sCallbackAddresses) && struc[E_FUNC_HOOK_DATA_END] >= sizeof (YSI_g_sCallbackAddresses))
	{
		P:W("y_hooks buffer exhausted, resorting to slow method.");
	}
	// Don't store the end, if the count goes off the end of the addresses array
	// then we need to just start reading from the AMX directly.
	P:4("Hooks_FindAll end: %s %d %d", name, toaddidx, struc[E_FUNC_HOOK_DATA_END] - struc[E_FUNC_HOOK_DATA_START]);
	//count = struc[E_FUNC_HOOK_DATA_END] - struc[E_FUNC_HOOK_DATA_START];
	return struc[E_FUNC_HOOK_DATA_END] - struc[E_FUNC_HOOK_DATA_START];
}

#define HOOKS_DO_ONE_CALLBACK<%0> ALS_DETECT<%0>if(!Hooks_FindAll(#%0,cidx,YSI_g_sCallbackData[ALS_On%0]))Hooks_RedirectPublic(#On%0,#S@@_On%0,ALS_R_%0);
#define HOOKS_DO_ONE_SPECIAL<%0> if(Hooks_FindAll(#%0,cidx,YSI_g_sCallbackData[ALS_On%0]))state y_hooks_%0 : y_hooks_%0_some;else state y_hooks_%0 : y_hooks_%0_none;

static Hooks_OnScriptInit()
{
	P:2("Hooks_OnScriptInit called");
	new
		cidx;
	//HOOKS_DO_ONE_CALLBACK<AnyScriptInit>
	//HOOKS_DO_ONE_CALLBACK<AnyScriptExit>
	//HOOKS_DO_ONE_CALLBACK<ScriptInit>
	//HOOKS_DO_ONE_CALLBACK<ScriptExit>
	//HOOKS_DO_ONE_CALLBACK<GameModeInit>
	//HOOKS_DO_ONE_CALLBACK<GameModeExit>
	//HOOKS_DO_ONE_CALLBACK<FilterScriptInit>
	//HOOKS_DO_ONE_CALLBACK<FilterScriptExit>
	ALS_DETECT<ScriptInit>
	ALS_DETECT<ScriptExit>
	ALS_DETECT<GameModeInit>
	ALS_DETECT<GameModeExit>
	ALS_DETECT<FilterScriptInit>
	ALS_DETECT<FilterScriptExit>
	Hooks_FindAll(#ScriptInit, cidx, YSI_g_sCallbackData[ALS_OnScriptInit]);
	if (YSI_FILTERSCRIPT)
	{
		if (!(Hooks_FindAll(#FilterScriptExit, cidx, YSI_g_sCallbackData[ALS_OnFilterScriptExit]) + Hooks_FindAll(#ScriptExit, cidx, YSI_g_sCallbackData[ALS_OnScriptExit])))
		{
			Hooks_RedirectPublic(#OnFilterScriptExit, #S@@_OnFilterScriptExit);
		}
		//HOOKS_DO_ONE_CALLBACK<FilterScriptInit>
		Hooks_FindAll(#FilterScriptInit, cidx, YSI_g_sCallbackData[ALS_OnFilterScriptInit]);
		HOOKS_DO_ONE_CALLBACK<GameModeInit>
		HOOKS_DO_ONE_CALLBACK<GameModeExit>
		//Hooks_FindAll(#FilterScriptExit, cidx, YSI_g_sCallbackData[ALS_OnFilterScriptExit], count);
	}
	else
	{
		if (!(Hooks_FindAll(#GameModeExit, cidx, YSI_g_sCallbackData[ALS_OnGameModeExit]) + Hooks_FindAll(#ScriptExit, cidx, YSI_g_sCallbackData[ALS_OnScriptExit])))
		{
			Hooks_RedirectPublic(#OnGameModeExit, #S@@_OnGameModeExit);
		}
		Hooks_FindAll(#GameModeInit, cidx, YSI_g_sCallbackData[ALS_OnGameModeInit]);
		//Hooks_RedirectPublic(#OnGameModeInit, #S@@_OnGameModeInit);
		Hooks_RedirectPublic(#OnFilterScriptInit, #S@@_OnFilterScriptInit);
		Hooks_RedirectPublic(#OnFilterScriptExit, #S@@_OnFilterScriptExit);
	}
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
	// YSI callbacks.
	HOOKS_DO_ONE_SPECIAL<PlayerLogin>
	HOOKS_DO_ONE_SPECIAL<PlayerLogout>
	//ALS_DETECT<%0>Hooks_FindAll(#%0,cidx,YSI_g_sCallbackData[ALS_On%0],count);if(!count)Hooks_RedirectPublic(#On%0,#S@@_On%0);
	//ALS_DETECT<%0>Hooks_FindAll(#%0,cidx,YSI_g_sCallbackData[ALS_On%0],count);if(!count)Hooks_RedirectPublic(#On%0,#S@@_On%0);
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
		/*if (~strval(YSI_gLockData[5]) != 0xFFFFFF80)
		{
			y_lock 3;
		}*/
	#endif
	new
		end   = YSI_g_sCallbackData[ALS_OnScriptInit][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnScriptInit][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_ScriptInit;
	if (start == end)
	{
		// We need to use this version of the return code instead of jumping to
		// the end of the function because "#emit" can only see labels BEFORE
		// where it is in the code.  This is quite annoying but can be worked
		// around in this case.
		P:2("Hooks_OnScriptInit end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnScriptInit));
hooks_do_hooks_call_no_als:
		return;
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		//#emit CONST.alt  0xFFFFFFFF
		//#emit PUSH.alt
		/*#emit HEAP 4
		#emit STOR.I
		#emit PUSH.alt
		printf("%d");
		#emit STACK 4
		#emit HEAP 0xFFFFFFFC*/
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_ScriptInit");
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnScriptInit end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnScriptInit));
}

static Hooks_OnScriptExit()
{
	P:2("Hooks_OnScriptExit called");
	new
		end   = YSI_g_sCallbackData[ALS_OnScriptExit][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnScriptExit][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_ScriptExit;
	if (start == end)
	{
		P:2("Hooks_OnScriptExit end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnScriptExit));
hooks_do_hooks_call_no_als:
		return;
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_ScriptExit");
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnScriptExit end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnScriptExit));
}

public OnGameModeInit()
{
	P:2("Hooks_OnGameModeInit called: %d", YSI_FILTERSCRIPT);
	if (!YSI_FILTERSCRIPT)
	{
		Hooks_OnScriptInit();
		//Hooks_OnAnyScriptInit();
		#if defined YSI_LOCK_MODE
			//if (strval(YSI_gLockData[9]) + strval(YSI_gLockData[11]) + strval(YSI_gLockData[13]) != 1)
			if (strval(YSI_gLockData[strfind(YSI_gLockData[5], YSI_gLockData[1])]) | strval(YSI_gLockData[strfind(YSI_gLockData[YSI_gLockData[0]], YSI_gLockData[1], _, 1)]) << 8 != _LOCK_IP_1 | _LOCK_IP_2 << 8)
			{
				y_lock 4;
			}
		#endif
	}
	new
		end   = YSI_g_sCallbackData[ALS_OnGameModeInit][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnGameModeInit][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_GameModeInit;
	if (start == end)
	{
		P:2("Hooks_OnGameModeInit end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnGameModeInit));
		//printf("%d", ret);
		//printf("%d", Bit_GetBit(Bit:gs_ALS, _:ALS_OnGameModeInit));
		//printf("%d", P@("S@@_OnGameModeInit", ""));
		HOOK_CALL<GameModeInit>
		//hooks_do_hooks_call_no_als:
		//printf("end 2");
		//return 1;
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		// Note that this label is embedded in the "HOOK_CALL" macro above.
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_GameModeInit");
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnGameModeInit end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnGameModeInit));
	HOOK_RETURN<GameModeInit>
	//return 1;
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit S@@_OnGameModeInit
ALS_FORWARD<GameModeInit>

public OnGameModeExit()
{
	P:2("Hooks_OnGameModeExit called");
	if (!YSI_FILTERSCRIPT)
	{
		Hooks_OnScriptExit();
		//Hooks_OnAnyScriptExit();
	}
	new
		end   = YSI_g_sCallbackData[ALS_OnGameModeExit][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnGameModeExit][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_GameModeExit;
	if (start == end)
	{
		P:2("Hooks_OnGameModeExit end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnGameModeExit));
		HOOK_CALL<GameModeExit>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_GameModeExit");
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnGameModeExit end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnGameModeExit));
	HOOK_RETURN<GameModeExit>
}
#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit S@@_OnGameModeExit
ALS_FORWARD<GameModeExit>

/*static Hooks_OnAnyScriptInit()
{
	P:2("Hooks_OnAnyScriptInit called");
	new
		end   = YSI_g_sCallbackData[ALS_OnAnyScriptInit][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnAnyScriptInit][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerCommandText;
	if (start == end)
	{
		P:2("Hooks_OnAnyScriptInit end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnAnyScriptInit));
		//HOOK_CALL<AnyScriptInit>
hooks_do_hooks_call_no_als:
		return;
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		// Note that this label is embedded in the "HOOK_CALL" macro above.
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_AnyScriptInit");
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnAnyScriptInit end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnAnyScriptInit));
	//HOOK_RETURN<AnyScriptInit>
}

static Hooks_OnAnyScriptExit()
{
	P:2("Hooks_OnAnyScriptExit called");
	new
		end   = YSI_g_sCallbackData[ALS_OnAnyScriptExit][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnAnyScriptExit][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerCommandText;
	if (start == end)
	{
		P:2("Hooks_OnAnyScriptExit end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnAnyScriptExit));
		//HOOK_CALL<AnyScriptExit>
hooks_do_hooks_call_no_als:
		return;
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_AnyScriptExit");
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnAnyScriptExit end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnAnyScriptExit));
	//HOOK_RETURN<AnyScriptExit>
}*/

public OnFilterScriptInit()
{
	P:2("Hooks_OnFilterScriptInit called");
	Hooks_OnScriptInit();
	#if defined YSI_LOCK_MODE
		if (strval(YSI_gLockData[strfind(YSI_gLockData[5], YSI_gLockData[1])]) | strval(YSI_gLockData[strfind(YSI_gLockData[YSI_gLockData[0]], YSI_gLockData[1], _, 1)]) << 8 != _LOCK_IP_1 | _LOCK_IP_2 << 8)
		{
			y_lock 4;
		}
		/*if (strval(YSI_gLockData[9]) + strval(YSI_gLockData[11]) + strval(YSI_gLockData[13]) != 1)
		{
			y_lock 5;
		}*/
	#endif
	//Hooks_OnAnyScriptInit();
	YSI_FILTERSCRIPT = true;
	new
		end   = YSI_g_sCallbackData[ALS_OnFilterScriptInit][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnFilterScriptInit][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_FilterScriptInit;
	if (start == end)
	{
		P:2("Hooks_OnFilterScriptInit end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnFilterScriptInit));
		HOOK_CALL<FilterScriptInit>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_FilterScriptInit");
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnFilterScriptInit end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnFilterScriptInit));
	HOOK_RETURN<FilterScriptInit>
}
#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit S@@_OnFilterScriptInit
ALS_FORWARD<FilterScriptInit>

public OnFilterScriptExit()
{
	P:2("Hooks_OnFilterScriptExit called");
	Hooks_OnScriptExit();
	//Hooks_OnAnyScriptExit();
	new
		end   = YSI_g_sCallbackData[ALS_OnFilterScriptExit][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnFilterScriptExit][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_FilterScriptExit;
	if (start == end)
	{
		P:2("Hooks_OnFilterScriptExit end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnFilterScriptExit));
		HOOK_CALL<FilterScriptExit>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_FilterScriptExit");
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnFilterScriptExit end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnFilterScriptExit));
	HOOK_RETURN<FilterScriptExit>
}
#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit S@@_OnFilterScriptExit
ALS_FORWARD<FilterScriptExit>

public OnPlayerConnect(playerid)
{
	P:2("Hooks_OnPlayerConnect called: %d", playerid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerConnect][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerConnect][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerConnect;
	if (start == end)
	{
		P:2("Hooks_OnPlayerConnect end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerConnect));
		HOOK_CALL<PlayerConnect>
	}
	new
		pointer,
		idx,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.  This was an experiment to play with the
	// stack so we only ever need to push the parameters and return address once
	// and do the loop using the return address!  Shame I've not got it working
	// yet really!
	/*#emit PUSH.S playerid
	#emit PUSH.C     4
	#emit LCTRL      6
	#emit ADD.C      20
	#emit PUSH.pri
	// This is done twice so that the second time the loop runs (which isn't
	// actually done by "while" anymore, the loop is hidden) the code's correct.
	#emit STACK      12
	// This is where the code above makes the SCTRL call return to!
	#emit STACK      0xFFFFFFF4
	//while (start != re)
	// NOTE: THIS IS A LOOP!  I know it doesn't look like one but it is!
	if (start != re)*/
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Clean up the stack.
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerConnect");
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	//#emit STACK      12
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerConnect end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerConnect));
	HOOK_RETURN<PlayerConnect>
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect S@@_OnPlayerConnect
ALS_FORWARD<PlayerConnect>

public OnPlayerDisconnect(playerid, reason)
{
	P:2("Hooks_OnPlayerDisconnect called: %d, %d", playerid, reason);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerDisconnect][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerDisconnect][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerDisconnect;
	if (start == end)
	{
		P:2("Hooks_OnPlayerDisconnect end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerDisconnect));
		HOOK_CALL<PlayerDisconnect>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S reason
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerDisconnect");
		#emit PUSH.S reason
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerDisconnect end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerDisconnect));
	HOOK_RETURN<PlayerDisconnect>
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect S@@_OnPlayerDisconnect
ALS_FORWARD<PlayerDisconnect>

public OnPlayerSpawn(playerid)
{
	P:2("Hooks_OnPlayerSpawn called: %d", playerid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerSpawn][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerSpawn][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerSpawn;
	if (start == end)
	{
		P:2("Hooks_OnPlayerSpawn end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerSpawn));
		HOOK_CALL<PlayerSpawn>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerSpawn");
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerSpawn end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerSpawn));
	HOOK_RETURN<PlayerSpawn>
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn S@@_OnPlayerSpawn
ALS_FORWARD<PlayerSpawn>

public OnPlayerDeath(playerid, killerid, reason)
{
	P:2("Hooks_OnPlayerDeath called: %d, %d, %d", playerid, killerid, reason);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerDeath][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerDeath][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerDeath;
	if (start == end)
	{
		P:2("Hooks_OnPlayerDeath end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerDeath));
		HOOK_CALL<PlayerDeath>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S reason
		#emit PUSH.S killerid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerDeath");
		#emit PUSH.S reason
		#emit PUSH.S killerid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerDeath end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerDeath));
	HOOK_RETURN<PlayerDeath>
}
#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath S@@_OnPlayerDeath
ALS_FORWARD<PlayerDeath>

public OnVehicleSpawn(vehicleid)
{
	P:2("Hooks_OnVehicleSpawn called: %d", vehicleid);
	new
		end   = YSI_g_sCallbackData[ALS_OnVehicleSpawn][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnVehicleSpawn][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_VehicleSpawn;
	if (start == end)
	{
		P:2("Hooks_OnVehicleSpawn end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehicleSpawn));
		HOOK_CALL<VehicleSpawn>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S vehicleid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_VehicleSpawn");
		#emit PUSH.S vehicleid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnVehicleSpawn end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehicleSpawn));
	HOOK_RETURN<VehicleSpawn>
}
#if defined _ALS_OnVehicleSpawn
	#undef OnVehicleSpawn
#else
	#define _ALS_OnVehicleSpawn
#endif
#define OnVehicleSpawn S@@_OnVehicleSpawn
ALS_FORWARD<VehicleSpawn>

public OnVehicleDeath(vehicleid, killerid)
{
	P:2("Hooks_OnVehicleDeath called: %d, %d", vehicleid, killerid);
	new
		end   = YSI_g_sCallbackData[ALS_OnVehicleDeath][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnVehicleDeath][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_VehicleDeath;
	if (start == end)
	{
		P:2("Hooks_OnVehicleDeath end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehicleDeath));
		HOOK_CALL<VehicleDeath>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S killerid
		#emit PUSH.S vehicleid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_VehicleDeath");
		#emit PUSH.S killerid
		#emit PUSH.S vehicleid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnVehicleDeath end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehicleDeath));
	HOOK_RETURN<VehicleDeath>
}
#if defined _ALS_OnVehicleDeath
	#undef OnVehicleDeath
#else
	#define _ALS_OnVehicleDeath
#endif
#define OnVehicleDeath S@@_OnVehicleDeath
ALS_FORWARD<VehicleDeath>

public OnPlayerText(playerid, text[])
{
	P:2("Hooks_OnPlayerText called: %d, \"%s\"", playerid, text);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerText][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerText][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerText;
	if (start == end)
	{
		P:2("Hooks_OnPlayerText end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerText));
		HOOK_CALL<PlayerText>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S text
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerText");
		#emit PUSH.S text
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerText end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerText));
	HOOK_RETURN<PlayerText>
}
#if defined _ALS_OnPlayerText
	#undef OnPlayerText
#else
	#define _ALS_OnPlayerText
#endif
#define OnPlayerText S@@_OnPlayerText
ALS_FORWARD<PlayerText>

public OnPlayerCommandText(playerid, cmdtext[])
{
	P:2("Hooks_OnPlayerCommandText called: %d, \"%s\"", playerid, cmdtext);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerCommandText][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerCommandText][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerCommandText;
	if (start == end)
	{
		P:2("Hooks_OnPlayerCommandText end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerCommandText));
		HOOK_CALL<PlayerCommandText>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S cmdtext
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerCommandText");
		#emit PUSH.S cmdtext
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerCommandText end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerCommandText));
	HOOK_RETURN<PlayerCommandText>
}
#if defined _ALS_OnPlayerCommandText
	#undef OnPlayerCommandText
#else
	#define _ALS_OnPlayerCommandText
#endif
#define OnPlayerCommandText S@@_OnPlayerCommandText
ALS_FORWARD<PlayerCommandText>

public OnPlayerRequestClass(playerid, classid)
{
	P:2("Hooks_OnPlayerRequestClass called: %d, %d", playerid, classid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerRequestClass][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerRequestClass][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerRequestClass;
	if (start == end)
	{
		P:2("Hooks_OnPlayerRequestClass end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerRequestClass));
		HOOK_CALL<PlayerRequestClass>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S classid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerRequestClass");
		#emit PUSH.S classid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerRequestClass end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerRequestClass));
	HOOK_RETURN<PlayerRequestClass>
}
#if defined _ALS_OnPlayerRequestClass
	#undef OnPlayerRequestClass
#else
	#define _ALS_OnPlayerRequestClass
#endif
#define OnPlayerRequestClass S@@_OnPlayerRequestClass
ALS_FORWARD<PlayerRequestClass>

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	P:2("Hooks_OnPlayerEnterVehicle called: %d, %d, %d", playerid, vehicleid, ispassenger);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerEnterVehicle][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerEnterVehicle][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerEnterVehicle;
	if (start == end)
	{
		P:2("Hooks_OnPlayerEnterVehicle end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerEnterVehicle));
		HOOK_CALL<PlayerEnterVehicle>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S ispassenger
		#emit PUSH.S vehicleid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerEnterVehicle");
		#emit PUSH.S ispassenger
		#emit PUSH.S vehicleid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerEnterVehicle end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerEnterVehicle));
	HOOK_RETURN<PlayerEnterVehicle>
}
#if defined _ALS_OnPlayerEnterVehicle
	#undef OnPlayerEnterVehicle
#else
	#define _ALS_OnPlayerEnterVehicle
#endif
#define OnPlayerEnterVehicle S@@_OnPlayerEnterVehicle
ALS_FORWARD<PlayerEnterVehicle>

public OnPlayerExitVehicle(playerid, vehicleid)
{
	P:2("Hooks_OnPlayerExitVehicle called: %d, %d", playerid, vehicleid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerExitVehicle][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerExitVehicle][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerExitVehicle;
	if (start == end)
	{
		P:2("Hooks_OnPlayerExitVehicle end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerExitVehicle));
		HOOK_CALL<PlayerExitVehicle>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S vehicleid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerExitVehicle");
		#emit PUSH.S vehicleid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerExitVehicle end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerExitVehicle));
	HOOK_RETURN<PlayerExitVehicle>
}
#if defined _ALS_OnPlayerExitVehicle
	#undef OnPlayerExitVehicle
#else
	#define _ALS_OnPlayerExitVehicle
#endif
#define OnPlayerExitVehicle S@@_OnPlayerExitVehicle
ALS_FORWARD<PlayerExitVehicle>

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	P:2("Hooks_OnPlayerStateChange called: %d, %d, %d", playerid, newstate, oldstate);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerStateChange][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerStateChange][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerStateChange;
	if (start == end)
	{
		P:2("Hooks_OnPlayerStateChange end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerStateChange));
		HOOK_CALL<PlayerStateChange>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S oldstate
		#emit PUSH.S newstate
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerStateChange");
		#emit PUSH.S oldstate
		#emit PUSH.S newstate
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerStateChange end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerStateChange));
	HOOK_RETURN<PlayerStateChange>
}
#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange S@@_OnPlayerStateChange
ALS_FORWARD<PlayerStateChange>

public OnPlayerEnterCheckpoint(playerid)
{
	P:2("Hooks_OnPlayerEnterCheckpoint called: %d", playerid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerEnterCheckpoint][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerEnterCheckpoint][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerEnterCheckpoint;
	if (start == end)
	{
		P:2("Hooks_OnPlayerEnterCheckpoint end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerEnterCheckpoint));
		HOOK_CALL<PlayerEnterCheckpoint>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerEnterCheckpoint");
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerEnterCheckpoint end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerEnterCheckpoint));
	HOOK_RETURN<PlayerEnterCheckpoint>
}
#if defined _ALS_OnPlayerEnterCheckpoint
	#undef OnPlayerEnterCheckpoint
#else
	#define _ALS_OnPlayerEnterCheckpoint
#endif
#define OnPlayerEnterCheckpoint S@@_OnPlayerEnterCheckpoint
ALS_FORWARD<PlayerEnterCheckpoint>

public OnPlayerLeaveCheckpoint(playerid)
{
	P:2("Hooks_OnPlayerLeaveCheckpoint called: %d", playerid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerLeaveCheckpoint][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerLeaveCheckpoint][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerLeaveCheckpoint;
	if (start == end)
	{
		P:2("Hooks_OnPlayerLeaveCheckpoint end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerLeaveCheckpoint));
		HOOK_CALL<PlayerLeaveCheckpoint>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerLeaveCheckpoint");
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerLeaveCheckpoint end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerLeaveCheckpoint));
	HOOK_RETURN<PlayerLeaveCheckpoint>
}
#if defined _ALS_OnPlayerLeaveCheckpoint
	#undef OnPlayerLeaveCheckpoint
#else
	#define _ALS_OnPlayerLeaveCheckpoint
#endif
#define OnPlayerLeaveCheckpoint S@@_OnPlayerLeaveCheckpoint
ALS_FORWARD<PlayerLeaveCheckpoint>

public OnPlayerEnterRaceCheckpoint(playerid)
{
	P:2("Hooks_OnPlayerEnterRaceCheckpoint called: %d", playerid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerEnterRaceCheckpoint][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerEnterRaceCheckpoint][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerEnterRaceCheckpoint;
	if (start == end)
	{
		P:2("Hooks_OnPlayerEnterRaceCheckpoint end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerEnterRaceCheckpoint));
		HOOK_CALL<PlayerEnterRaceCheckpoint>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerEnterRaceCheckpoint");
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerEnterRaceCheckpoint end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerEnterRaceCheckpoint));
	HOOK_RETURN<PlayerEnterRaceCheckpoint>
}
#if defined _ALS_OnPlayerEnterRaceCP
	#undef OnPlayerEnterRaceCheckpoint
#else
	#define _ALS_OnPlayerEnterRaceCP
#endif
#define OnPlayerEnterRaceCheckpoint S@@_OnPlayerEnterRaceCheckpoint
ALS_FORWARD<PlayerEnterRaceCheckpoint>

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	P:2("Hooks_OnPlayerLeaveRaceCheckpoint called: %d", playerid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerLeaveRaceCheckpoint][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerLeaveRaceCheckpoint][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerLeaveRaceCheckpoint;
	if (start == end)
	{
		P:2("Hooks_OnPlayerLeaveRaceCheckpoint end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerLeaveRaceCheckpoint));
		HOOK_CALL<PlayerLeaveRaceCheckpoint>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerLeaveRaceCheckpoint");
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerLeaveRaceCheckpoint end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerLeaveRaceCheckpoint));
	HOOK_RETURN<PlayerLeaveRaceCheckpoint>
}
#if defined _ALS_OnPlayerLeaveRaceCP
	#undef OnPlayerLeaveRaceCheckpoint
#else
	#define _ALS_OnPlayerLeaveRaceCP
#endif
#define OnPlayerLeaveRaceCheckpoint S@@_OnPlayerLeaveRaceCheckpoint
ALS_FORWARD<PlayerLeaveRaceCheckpoint>

public OnRconCommand(cmd[])
{
	P:2("Hooks_OnRconCommand called: \"%s\"", cmd);
	new
		end   = YSI_g_sCallbackData[ALS_OnRconCommand][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnRconCommand][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_RconCommand;
	if (start == end)
	{
		P:2("Hooks_OnRconCommand end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnRconCommand));
		HOOK_CALL<RconCommand>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S cmd
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_RconCommand");
		#emit PUSH.S cmd
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnRconCommand end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnRconCommand));
	HOOK_RETURN<RconCommand>
}
#if defined _ALS_OnRconCommand
	#undef OnRconCommand
#else
	#define _ALS_OnRconCommand
#endif
#define OnRconCommand S@@_OnRconCommand
ALS_FORWARD<RconCommand>

public OnPlayerRequestSpawn(playerid)
{
	P:2("Hooks_OnPlayerRequestSpawn called: %d", playerid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerRequestSpawn][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerRequestSpawn][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerRequestSpawn;
	if (start == end)
	{
		P:2("Hooks_OnPlayerRequestSpawn end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerRequestSpawn));
		HOOK_CALL<PlayerRequestSpawn>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerRequestSpawn");
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerRequestSpawn end: %d %d", _:Bit_GetBit(Bit:gs_ALS,_:ALS_OnPlayerRequestSpawn), ret);
	HOOK_RETURN<PlayerRequestSpawn>
}
#if defined _ALS_OnPlayerRequestSpawn
	#undef OnPlayerRequestSpawn
#else
	#define _ALS_OnPlayerRequestSpawn
#endif
#define OnPlayerRequestSpawn S@@_OnPlayerRequestSpawn
ALS_FORWARD<PlayerRequestSpawn>

public OnObjectMoved(objectid)
{
	P:2("Hooks_OnObjectMoved called: %d", objectid);
	new
		end   = YSI_g_sCallbackData[ALS_OnObjectMoved][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnObjectMoved][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_ObjectMoved;
	if (start == end)
	{
		P:2("Hooks_OnObjectMoved end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnObjectMoved));
		HOOK_CALL<ObjectMoved>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S objectid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_ObjectMoved");
		#emit PUSH.S objectid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnObjectMoved end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnObjectMoved));
	HOOK_RETURN<ObjectMoved>
}
#if defined _ALS_OnObjectMoved
	#undef OnObjectMoved
#else
	#define _ALS_OnObjectMoved
#endif
#define OnObjectMoved S@@_OnObjectMoved
ALS_FORWARD<ObjectMoved>

public OnPlayerObjectMoved(playerid, objectid)
{
	P:2("Hooks_OnPlayerObjectMoved called: %d, %d", playerid, objectid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerObjectMoved][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerObjectMoved][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerObjectMoved;
	if (start == end)
	{
		P:2("Hooks_OnPlayerObjectMoved end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerObjectMoved));
		HOOK_CALL<PlayerObjectMoved>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S objectid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerObjectMoved");
		#emit PUSH.S objectid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerObjectMoved end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerObjectMoved));
	HOOK_RETURN<PlayerObjectMoved>
}
#if defined _ALS_OnPlayerObjectMoved
	#undef OnPlayerObjectMoved
#else
	#define _ALS_OnPlayerObjectMoved
#endif
#define OnPlayerObjectMoved S@@_OnPlayerObjectMoved
ALS_FORWARD<PlayerObjectMoved>

public OnPlayerPickUpPickup(playerid, pickupid)
{
	P:2("Hooks_OnPlayerPickUpPickup called: %d, %d", playerid, pickupid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerPickUpPickup][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerPickUpPickup][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerPickUpPickup;
	if (start == end)
	{
		P:2("Hooks_OnPlayerPickUpPickup end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerPickUpPickup));
		HOOK_CALL<PlayerPickUpPickup>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S pickupid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerPickUpPickup");
		#emit PUSH.S pickupid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerPickUpPickup end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerPickUpPickup));
	HOOK_RETURN<PlayerPickUpPickup>
}
#if defined _ALS_OnPlayerPickUpPickup
	#undef OnPlayerPickUpPickup
#else
	#define _ALS_OnPlayerPickUpPickup
#endif
#define OnPlayerPickUpPickup S@@_OnPlayerPickUpPickup
ALS_FORWARD<PlayerPickUpPickup>

public OnVehicleMod(playerid, vehicleid, componentid)
{
	P:2("Hooks_OnVehicleMod called: %d, %d, %d", playerid, vehicleid, componentid);
	new
		end   = YSI_g_sCallbackData[ALS_OnVehicleMod][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnVehicleMod][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_VehicleMod;
	if (start == end)
	{
		P:2("Hooks_OnVehicleMod end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehicleMod));
		HOOK_CALL<VehicleMod>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S componentid
		#emit PUSH.S vehicleid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_VehicleMod");
		#emit PUSH.S componentid
		#emit PUSH.S vehicleid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnVehicleMod end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehicleMod));
	HOOK_RETURN<VehicleMod>
}
#if defined _ALS_OnVehicleMod
	#undef OnVehicleMod
#else
	#define _ALS_OnVehicleMod
#endif
#define OnVehicleMod S@@_OnVehicleMod
ALS_FORWARD<VehicleMod>

public OnEnterExitModShop(playerid, enterexit, interiorid)
{
	P:2("Hooks_OnEnterExitModShop called: %d, %d, %d", playerid, enterexit, interiorid);
	new
		end   = YSI_g_sCallbackData[ALS_OnEnterExitModShop][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnEnterExitModShop][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_EnterExitModShop;
	if (start == end)
	{
		P:2("Hooks_OnEnterExitModShop end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnEnterExitModShop));
		HOOK_CALL<EnterExitModShop>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S interiorid
		#emit PUSH.S enterexit
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_EnterExitModShop");
		#emit PUSH.S interiorid
		#emit PUSH.S enterexit
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnEnterExitModShop end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnEnterExitModShop));
	HOOK_RETURN<EnterExitModShop>
}
#if defined _ALS_OnEnterExitModShop
	#undef OnEnterExitModShop
#else
	#define _ALS_OnEnterExitModShop
#endif
#define OnEnterExitModShop S@@_OnEnterExitModShop
ALS_FORWARD<EnterExitModShop>

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	P:2("Hooks_OnVehiclePaintjob called: %d, %d, %d", playerid, vehicleid, paintjobid);
	new
		end   = YSI_g_sCallbackData[ALS_OnVehiclePaintjob][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnVehiclePaintjob][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_VehiclePaintjob;
	if (start == end)
	{
		P:2("Hooks_OnVehiclePaintjob end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehiclePaintjob));
		HOOK_CALL<VehiclePaintjob>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S paintjobid
		#emit PUSH.S vehicleid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_VehiclePaintjob");
		#emit PUSH.S paintjobid
		#emit PUSH.S vehicleid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnVehiclePaintjob end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehiclePaintjob));
	HOOK_RETURN<VehiclePaintjob>
}
#if defined _ALS_OnVehiclePaintjob
	#undef OnVehiclePaintjob
#else
	#define _ALS_OnVehiclePaintjob
#endif
#define OnVehiclePaintjob S@@_OnVehiclePaintjob
ALS_FORWARD<VehiclePaintjob>

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	P:2("Hooks_OnVehicleRespray called: %d, %d, %d, %d", playerid, vehicleid, color1, color2);
	new
		end   = YSI_g_sCallbackData[ALS_OnVehicleRespray][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnVehicleRespray][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_VehicleRespray;
	if (start == end)
	{
		P:2("Hooks_OnVehicleRespray end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehicleRespray));
		HOOK_CALL<VehicleRespray>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S color2
		#emit PUSH.S color1
		#emit PUSH.S vehicleid
		#emit PUSH.S playerid
		#emit PUSH.C     16
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_VehicleRespray");
		#emit PUSH.S color2
		#emit PUSH.S color1
		#emit PUSH.S vehicleid
		#emit PUSH.S playerid
		#emit PUSH.C     16
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnVehicleRespray end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehicleRespray));
	HOOK_RETURN<VehicleRespray>
}
#if defined _ALS_OnVehicleRespray
	#undef OnVehicleRespray
#else
	#define _ALS_OnVehicleRespray
#endif
#define OnVehicleRespray S@@_OnVehicleRespray
ALS_FORWARD<VehicleRespray>

public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	P:2("Hooks_OnVehicleDamageStatusUpdate called: %d, %d", vehicleid, playerid);
	new
		end   = YSI_g_sCallbackData[ALS_OnVehicleDamageStatusUpdate][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnVehicleDamageStatusUpdate][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_VehicleDamageStatusUpdate;
	if (start == end)
	{
		P:2("Hooks_OnVehicleDamageStatusUpdate end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehicleDamageStatusUpdate));
		HOOK_CALL<VehicleDamageStatusUpdate>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S playerid
		#emit PUSH.S vehicleid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_VehicleDamageStatusUpdate");
		#emit PUSH.S playerid
		#emit PUSH.S vehicleid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnVehicleDamageStatusUpdate end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehicleDamageStatusUpdate));
	HOOK_RETURN<VehicleDamageStatusUpdate>
}
#if defined _ALS_OnVehicleDamageStatusUpd
	#undef OnVehicleDamageStatusUpdate
#else
	#define _ALS_OnVehicleDamageStatusUpd
#endif
#define OnVehicleDamageStatusUpdate S@@_OnVehicleDamageStatusUpdate
ALS_FORWARD<VehicleDamageStatusUpdate>

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat)
{
	P:2("Hooks_OnUnoccupiedVehicleUpdate called: %d, %d, %d", vehicleid, playerid, passenger_seat);
	new
		end   = YSI_g_sCallbackData[ALS_OnUnoccupiedVehicleUpdate][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnUnoccupiedVehicleUpdate][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_UnoccupiedVehicleUpdate;
	if (start == end)
	{
		P:2("Hooks_OnUnoccupiedVehicleUpdate end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnUnoccupiedVehicleUpdate));
		HOOK_CALL<UnoccupiedVehicleUpdate>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S passenger_seat
		#emit PUSH.S playerid
		#emit PUSH.S vehicleid
		// I wonder if I could hack the stack with a negative number so that when
		// the called function returns it puts all the header data BACK on to the
		// stack instead of removing the parameters and header.
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_UnoccupiedVehicleUpdate");
		#emit PUSH.S passenger_seat
		#emit PUSH.S playerid
		#emit PUSH.S vehicleid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnUnoccupiedVehicleUpdate end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnUnoccupiedVehicleUpdate));
	HOOK_RETURN<UnoccupiedVehicleUpdate>
}
#if defined _ALS_OnUnoccupiedVehicleUpdate
	#undef OnUnoccupiedVehicleUpdate
#else
	#define _ALS_OnUnoccupiedVehicleUpdate
#endif
#define OnUnoccupiedVehicleUpdate S@@_OnUnoccupiedVehicleUpdate
ALS_FORWARD<UnoccupiedVehicleUpdate>

public OnPlayerSelectedMenuRow(playerid, row)
{
	P:2("Hooks_OnPlayerSelectedMenuRow called: %d, %d", playerid, row);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerSelectedMenuRow][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerSelectedMenuRow][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerSelectedMenuRow;
	if (start == end)
	{
		P:2("Hooks_OnPlayerSelectedMenuRow end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerSelectedMenuRow));
		HOOK_CALL<PlayerSelectedMenuRow>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S row
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerSelectedMenuRow");
		#emit PUSH.S row
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerSelectedMenuRow end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerSelectedMenuRow));
	HOOK_RETURN<PlayerSelectedMenuRow>
}
#if defined _ALS_OnPlayerSelectedMenuRow
	#undef OnPlayerSelectedMenuRow
#else
	#define _ALS_OnPlayerSelectedMenuRow
#endif
#define OnPlayerSelectedMenuRow S@@_OnPlayerSelectedMenuRow
ALS_FORWARD<PlayerSelectedMenuRow>

public OnPlayerExitedMenu(playerid)
{
	P:2("Hooks_OnPlayerExitedMenu called: %d", playerid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerExitedMenu][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerExitedMenu][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerExitedMenu;
	if (start == end)
	{
		P:2("Hooks_OnPlayerExitedMenu end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerExitedMenu));
		HOOK_CALL<PlayerExitedMenu>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerExitedMenu");
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerExitedMenu end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerExitedMenu));
	HOOK_RETURN<PlayerExitedMenu>
}
#if defined _ALS_OnPlayerExitedMenu
	#undef OnPlayerExitedMenu
#else
	#define _ALS_OnPlayerExitedMenu
#endif
#define OnPlayerExitedMenu S@@_OnPlayerExitedMenu
ALS_FORWARD<PlayerExitedMenu>

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	P:2("Hooks_OnPlayerInteriorChange called: %d, %d, %d", playerid, newinteriorid, oldinteriorid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerInteriorChange][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerInteriorChange][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerInteriorChange;
	if (start == end)
	{
		P:2("Hooks_OnPlayerInteriorChange end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerInteriorChange));
		HOOK_CALL<PlayerInteriorChange>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S oldinteriorid
		#emit PUSH.S newinteriorid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerInteriorChange");
		#emit PUSH.S oldinteriorid
		#emit PUSH.S newinteriorid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerInteriorChange end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerInteriorChange));
	HOOK_RETURN<PlayerInteriorChange>
}
#if defined _ALS_OnPlayerInteriorChange
	#undef OnPlayerInteriorChange
#else
	#define _ALS_OnPlayerInteriorChange
#endif
#define OnPlayerInteriorChange S@@_OnPlayerInteriorChange
ALS_FORWARD<PlayerInteriorChange>

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	P:2("Hooks_OnPlayerKeyStateChange called: %d, %d, %d", playerid, newkeys, oldkeys);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerKeyStateChange][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerKeyStateChange][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerKeyStateChange;
	if (start == end)
	{
		P:2("Hooks_OnPlayerKeyStateChange end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerKeyStateChange));
		HOOK_CALL<PlayerKeyStateChange>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S oldkeys
		#emit PUSH.S newkeys
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerKeyStateChange");
		#emit PUSH.S oldkeys
		#emit PUSH.S newkeys
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerKeyStateChange end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerKeyStateChange));
	HOOK_RETURN<PlayerKeyStateChange>
}
#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange S@@_OnPlayerKeyStateChange
ALS_FORWARD<PlayerKeyStateChange>

public OnRconLoginAttempt(ip[], password[], success)
{
	P:2("Hooks_OnRconLoginAttempt called: \"%s\", \"%s\", %d", ip, password, success);
	new
		end   = YSI_g_sCallbackData[ALS_OnRconLoginAttempt][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnRconLoginAttempt][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_RconLoginAttempt;
	if (start == end)
	{
		P:2("Hooks_OnRconLoginAttempt end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnRconLoginAttempt));
		HOOK_CALL<RconLoginAttempt>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S success
		#emit PUSH.S password
		#emit PUSH.S ip
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_RconLoginAttempt");
		#emit PUSH.S success
		#emit PUSH.S password
		#emit PUSH.S ip
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnRconLoginAttempt end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnRconLoginAttempt));
	HOOK_RETURN<RconLoginAttempt>
}
#if defined _ALS_OnRconLoginAttempt
	#undef OnRconLoginAttempt
#else
	#define _ALS_OnRconLoginAttempt
#endif
#define OnRconLoginAttempt S@@_OnRconLoginAttempt
ALS_FORWARD<RconLoginAttempt>

public OnPlayerUpdate(playerid)
{
	P:7("Hooks_OnPlayerUpdate called: %d", playerid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerUpdate][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerUpdate][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerUpdate;
	if (start == end)
	{
		P:7("Hooks_OnPlayerUpdate end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerUpdate));
		HOOK_CALL<PlayerUpdate>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerUpdate");
		#emit PUSH.S playerid
		#emit PUSH.C     4
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:7("Hooks_OnPlayerUpdate end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerUpdate));
	HOOK_RETURN<PlayerUpdate>
}
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate S@@_OnPlayerUpdate
ALS_FORWARD<PlayerUpdate>

public OnPlayerStreamIn(playerid, forplayerid)
{
	P:2("Hooks_OnPlayerStreamIn called: %d, %d", playerid, forplayerid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerStreamIn][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerStreamIn][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerStreamIn;
	if (start == end)
	{
		P:2("Hooks_OnPlayerStreamIn end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerStreamIn));
		HOOK_CALL<PlayerStreamIn>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S forplayerid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerStreamIn");
		#emit PUSH.S forplayerid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerStreamIn end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerStreamIn));
	HOOK_RETURN<PlayerStreamIn>
}
#if defined _ALS_OnPlayerStreamIn
	#undef OnPlayerStreamIn
#else
	#define _ALS_OnPlayerStreamIn
#endif
#define OnPlayerStreamIn S@@_OnPlayerStreamIn
ALS_FORWARD<PlayerStreamIn>

public OnPlayerStreamOut(playerid, forplayerid)
{
	P:2("Hooks_OnPlayerStreamOut called: %d, %d", playerid, forplayerid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerStreamOut][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerStreamOut][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerStreamOut;
	if (start == end)
	{
		P:2("Hooks_OnPlayerStreamOut end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerStreamOut));
		HOOK_CALL<PlayerStreamOut>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S forplayerid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerStreamOut");
		#emit PUSH.S forplayerid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerStreamOut end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerStreamOut));
	HOOK_RETURN<PlayerStreamOut>
}
#if defined _ALS_OnPlayerStreamOut
	#undef OnPlayerStreamOut
#else
	#define _ALS_OnPlayerStreamOut
#endif
#define OnPlayerStreamOut S@@_OnPlayerStreamOut
ALS_FORWARD<PlayerStreamOut>

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	P:2("Hooks_OnVehicleStreamIn called: %d, %d", vehicleid, forplayerid);
	new
		end   = YSI_g_sCallbackData[ALS_OnVehicleStreamIn][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnVehicleStreamIn][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_VehicleStreamIn;
	if (start == end)
	{
		P:2("Hooks_OnVehicleStreamIn end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehicleStreamIn));
		HOOK_CALL<VehicleStreamIn>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S forplayerid
		#emit PUSH.S vehicleid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_VehicleStreamIn");
		#emit PUSH.S forplayerid
		#emit PUSH.S vehicleid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnVehicleStreamIn end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehicleStreamIn));
	HOOK_RETURN<VehicleStreamIn>
}
#if defined _ALS_OnVehicleStreamIn
	#undef OnVehicleStreamIn
#else
	#define _ALS_OnVehicleStreamIn
#endif
#define OnVehicleStreamIn S@@_OnVehicleStreamIn
ALS_FORWARD<VehicleStreamIn>

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	P:2("Hooks_OnVehicleStreamOut called: %d, %d", vehicleid, forplayerid);
	new
		end   = YSI_g_sCallbackData[ALS_OnVehicleStreamOut][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnVehicleStreamOut][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_VehicleStreamOut;
	if (start == end)
	{
		P:2("Hooks_OnVehicleStreamOut end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehicleStreamOut));
		HOOK_CALL<VehicleStreamOut>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S forplayerid
		#emit PUSH.S vehicleid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_VehicleStreamOut");
		#emit PUSH.S forplayerid
		#emit PUSH.S vehicleid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnVehicleStreamOut end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnVehicleStreamOut));
	HOOK_RETURN<VehicleStreamOut>
}
#if defined _ALS_OnVehicleStreamOut
	#undef OnVehicleStreamOut
#else
	#define _ALS_OnVehicleStreamOut
#endif
#define OnVehicleStreamOut S@@_OnVehicleStreamOut
ALS_FORWARD<VehicleStreamOut>

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	P:2("Hooks_OnDialogResponse called: %d, %d, %d, %d, \"%s\"", playerid, dialogid, response, listitem, inputtext);
	new
		end   = YSI_g_sCallbackData[ALS_OnDialogResponse][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnDialogResponse][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_DialogResponse;
	if (start == end)
	{
		P:2("Hooks_OnDialogResponse end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnDialogResponse));
		HOOK_CALL<DialogResponse>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S inputtext
		#emit PUSH.S listitem
		#emit PUSH.S response
		#emit PUSH.S dialogid
		#emit PUSH.S playerid
		#emit PUSH.C     20
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_DialogResponse");
		#emit PUSH.S inputtext
		#emit PUSH.S listitem
		#emit PUSH.S response
		#emit PUSH.S dialogid
		#emit PUSH.S playerid
		#emit PUSH.C     20
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnDialogResponse end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnDialogResponse));
	HOOK_RETURN<DialogResponse>
}
#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse S@@_OnDialogResponse
ALS_FORWARD<DialogResponse>

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	P:2("Hooks_OnPlayerClickPlayer called: %d, %d, %d", playerid, clickedplayerid, source);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerClickPlayer][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerClickPlayer][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerClickPlayer;
	if (start == end)
	{
		P:2("Hooks_OnPlayerClickPlayer end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerClickPlayer));
		HOOK_CALL<PlayerClickPlayer>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S source
		#emit PUSH.S clickedplayerid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerClickPlayer");
		#emit PUSH.S source
		#emit PUSH.S clickedplayerid
		#emit PUSH.S playerid
		#emit PUSH.C     12
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerClickPlayer end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerClickPlayer));
	HOOK_RETURN<PlayerClickPlayer>
}
#if defined _ALS_OnPlayerClickPlayer
	#undef OnPlayerClickPlayer
#else
	#define _ALS_OnPlayerClickPlayer
#endif
#define OnPlayerClickPlayer S@@_OnPlayerClickPlayer
ALS_FORWARD<PlayerClickPlayer>

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid)
{
	P:2("Hooks_OnPlayerTakeDamage called: %d, %d, %f, %d", playerid, issuerid, Float:amount, weaponid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerTakeDamage][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerTakeDamage][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerTakeDamage;
	if (start == end)
	{
		P:2("Hooks_OnPlayerTakeDamage end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerTakeDamage));
		HOOK_CALL<PlayerTakeDamage>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S weaponid
		#emit PUSH.S amount
		#emit PUSH.S issuerid
		#emit PUSH.S playerid
		#emit PUSH.C     16
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerTakeDamage");
		#emit PUSH.S weaponid
		#emit PUSH.S amount
		#emit PUSH.S issuerid
		#emit PUSH.S playerid
		#emit PUSH.C     16
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerTakeDamage end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerTakeDamage));
	HOOK_RETURN<PlayerTakeDamage>
}
#if defined _ALS_OnPlayerTakeDamage
	#undef OnPlayerTakeDamage
#else
	#define _ALS_OnPlayerTakeDamage
#endif
#define OnPlayerTakeDamage S@@_OnPlayerTakeDamage
ALS_FORWARD<PlayerTakeDamage>

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid)
{
	P:2("Hooks_OnPlayerGiveDamage called: %d, %d, %f, %d", playerid, damagedid, Float:amount, weaponid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerGiveDamage][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerGiveDamage][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerGiveDamage;
	if (start == end)
	{
		P:2("Hooks_OnPlayerGiveDamage end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerGiveDamage));
		HOOK_CALL<PlayerGiveDamage>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S weaponid
		#emit PUSH.S amount
		#emit PUSH.S damagedid
		#emit PUSH.S playerid
		#emit PUSH.C     16
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerGiveDamage");
		#emit PUSH.S weaponid
		#emit PUSH.S amount
		#emit PUSH.S damagedid
		#emit PUSH.S playerid
		#emit PUSH.C     16
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerGiveDamage end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerGiveDamage));
	HOOK_RETURN<PlayerGiveDamage>
}
#if defined _ALS_OnPlayerGiveDamage
	#undef OnPlayerGiveDamage
#else
	#define _ALS_OnPlayerGiveDamage
#endif
#define OnPlayerGiveDamage S@@_OnPlayerGiveDamage
ALS_FORWARD<PlayerGiveDamage>

stock Hooks_OnPlayerLogin(playerid, uid) <y_hooks_PlayerLogin : y_hooks_PlayerLogin_none>
{
	#pragma unused playerid, uid
}

stock Hooks_OnPlayerLogin(playerid, uid) <y_hooks_PlayerLogin : y_hooks_PlayerLogin_some>
{
	P:2("Hooks_OnPlayerLogin called: %d, %d", playerid, uid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerLogin][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerLogin][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerLogin;
	if (start == end)
	{
		P:2("Hooks_OnPlayerLogin end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerLogin));
hooks_do_hooks_call_no_als:
		return;
		//HOOK_CALL<PlayerLogin>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S uid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerLogin");
		#emit PUSH.S uid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerLogin end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerLogin));
	//HOOK_RETURN<PlayerLogin>
}
/*#if defined _ALS_OnPlayerLogin
	#undef OnPlayerLogin
#else
	#define _ALS_OnPlayerLogin
#endif
#define OnPlayerLogin S@@_OnPlayerLogin
ALS_FORWARD<PlayerLogin>*/

stock Hooks_OnPlayerLogout(playerid, uid) <y_hooks_PlayerLogout : y_hooks_PlayerLogout_none>
{
	#pragma unused playerid, uid
}

stock Hooks_OnPlayerLogout(playerid, uid) <y_hooks_PlayerLogout : y_hooks_PlayerLogout_some>
{
	P:2("Hooks_OnPlayerLogout called: %d, %d", playerid, uid);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerLogout][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerLogout][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerLogout;
	if (start == end)
	{
		P:2("Hooks_OnPlayerLogout end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerLogout));
		//HOOK_CALL<PlayerLogout>
hooks_do_hooks_call_no_als:
		return;
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S uid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerLogout");
		#emit PUSH.S uid
		#emit PUSH.S playerid
		#emit PUSH.C     8
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerLogout end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerLogout));
	//HOOK_RETURN<PlayerLogout>
}
/*#if defined _ALS_OnPlayerLogout
	#undef OnPlayerLogout
#else
	#define _ALS_OnPlayerLogout
#endif
#define OnPlayerLogout S@@_OnPlayerlogout
ALS_FORWARD<PlayerLogout>*/

#if !defined OnPlayerClickMap
	#undef ALS_PREFIX
	#endinput
#endif

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	P:2("Hooks_OnPlayerClickMap called: %d, %f, %f, %f", playerid, fX, fY, fZ);
	new
		end   = YSI_g_sCallbackData[ALS_OnPlayerClickMap][E_FUNC_HOOK_DATA_END],
		start = YSI_g_sCallbackData[ALS_OnPlayerClickMap][E_FUNC_HOOK_DATA_START],
		ret = ALS_R_PlayerClickMap;
	if (start == end)
	{
		P:2("Hooks_OnPlayerClickMap end 1: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerClickMap));
		HOOK_CALL<PlayerClickMap>
	}
	new
		idx,
		pointer,
		re = end;
	if (end > sizeof (YSI_g_sCallbackAddresses))
	{
		re = sizeof (YSI_g_sCallbackAddresses);
		if (start != sizeof (YSI_g_sCallbackAddresses)) idx = YSI_g_sLastFoundIndex;
	}
	// Do the initial fast elements.
	while (start != re)
	{
		pointer = YSI_g_sCallbackAddresses[start++];
		#emit PUSH.S fZ
		#emit PUSH.S fY
		#emit PUSH.S fX
		#emit PUSH.S playerid
		#emit PUSH.C     16
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Get any remaining pointers the old way.
	while (start++ != end)
	{
		idx = AMX_GetPublicPointer(idx, pointer, "@yH_PlayerClickMap");
		#emit PUSH.S fZ
		#emit PUSH.S fY
		#emit PUSH.S fX
		#emit PUSH.S playerid
		#emit PUSH.C     16
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri pointer
		#emit SCTRL      6
		#emit CONST.alt  0xFFFFFFFF
		#emit STOR.S.pri ret
		#emit JEQ        hooks_do_hooks_call_no_als
	}
	// Do ALS just in case (YSI no longer uses this though now).
	P:2("Hooks_OnPlayerClickMap end 2: %d %d", ret, _:Bit_GetBit(Bit:gs_ALS, _:ALS_OnPlayerClickMap));
	HOOK_RETURN<PlayerClickMap>
}
#if defined _ALS_OnPlayerClickMap
	#undef OnPlayerClickMap
#else
	#define _ALS_OnPlayerClickMap
#endif
#define OnPlayerClickMap S@@_OnPlayerClickMap
ALS_FORWARD<PlayerClickMap>

#undef ALS_PREFIX