/*----------------------------------------------------------------------------*\
					==============================
					 y_als - Useful codes for ALS
					==============================
Description:
	Provides a number of macros for making ALS (Advanced Library System)
	callback hooking simpler.
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
	
	The Original Code is the YSI ALS include.
	
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
	
Version:
	1.0
Changelog:
	29/04/11:
		Added "call" macro to make testing easier.
	21/10/10:
		First version
\*----------------------------------------------------------------------------*/

#include "internal\y_version"
#include "y_amx"
#include "y_utils"

// Allow multiple inclusions.
#if !defined _inc_y_als
	#error Did you do <YSI/y_als> instead of the required <YSI\y_als>?
#endif
#undef _inc_y_als

#if !defined _Y_ALS_INCLUDED
	// This is an include guard with a purpose - we need more control than the
	// standard include guards give.
	#define _Y_ALS_INCLUDED
	#include "y_bit"
	#include "internal\y_shortfunc"
	
	enum ALS
	{
		//Bit:ALS_OnAnyScriptInit,
		//Bit:ALS_OnAnyScriptExit,
		Bit:ALS_OnScriptInit,
		Bit:ALS_OnScriptExit,
		Bit:ALS_OnGameModeInit,
		Bit:ALS_OnGameModeExit,
		Bit:ALS_OnFilterScriptInit,
		Bit:ALS_OnFilterScriptExit,
		Bit:ALS_OnPlayerConnect,
		Bit:ALS_OnPlayerDisconnect,
		Bit:ALS_OnPlayerSpawn,
		Bit:ALS_OnPlayerDeath,
		Bit:ALS_OnVehicleSpawn,
		Bit:ALS_OnVehicleDeath,
		Bit:ALS_OnPlayerText,
		Bit:ALS_OnPlayerCommandText,
		Bit:ALS_OnPlayerRequestClass,
		Bit:ALS_OnPlayerEnterVehicle,
		Bit:ALS_OnPlayerExitVehicle,
		Bit:ALS_OnPlayerStateChange,
		Bit:ALS_OnPlayerEnterCheckpoint,
		Bit:ALS_OnPlayerLeaveCheckpoint,
		Bit:ALS_OnPlayerEnterRaceCheckpoint,
		Bit:ALS_OnPlayerLeaveRaceCheckpoint,
		Bit:ALS_OnRconCommand,
		Bit:ALS_OnPlayerRequestSpawn,
		Bit:ALS_OnObjectMoved,
		Bit:ALS_OnPlayerObjectMoved,
		Bit:ALS_OnPlayerPickUpPickup,
		Bit:ALS_OnVehicleMod,
		Bit:ALS_OnEnterExitModShop,
		Bit:ALS_OnVehiclePaintjob,
		Bit:ALS_OnVehicleRespray,
		Bit:ALS_OnVehicleDamageStatusUpdate,
		Bit:ALS_OnPlayerSelectedMenuRow,
		Bit:ALS_OnPlayerExitedMenu,
		Bit:ALS_OnPlayerInteriorChange,
		Bit:ALS_OnPlayerKeyStateChange,
		Bit:ALS_OnRconLoginAttempt,
		Bit:ALS_OnPlayerUpdate,
		Bit:ALS_OnPlayerStreamIn,
		Bit:ALS_OnPlayerStreamOut,
		Bit:ALS_OnVehicleStreamIn,
		Bit:ALS_OnVehicleStreamOut,
		Bit:ALS_OnDialogResponse,
		Bit:ALS_OnPlayerClickPlayer,
		Bit:ALS_OnPlayerLogin,
		Bit:ALS_OnPlayerLogout,
		Bit:ALS_OnPlayerTakeDamage,
		Bit:ALS_OnPlayerGiveDamage,
		Bit:ALS_OnPlayerClickMap,
		Bit:ALS_OnPlayerCommandReceived,
		Bit:ALS_OnPlayerCommandPerformed,
		Bit:ALS_OnUnoccupiedVehicleUpdate
	}
	
	#define ALS_DATA<> static stock BitArray:gs_ALS<_:ALS>;
	
	#define ALS_DETECT<%0> if(funcidx(#ALS_PREFIX"_On"#%0)!=-1)Bit_Let(gs_ALS,_:ALS_On%0);
	
	//#define ALS_DETECT_SHORT<On%0> if(funcidx(#ALS_PREFIX"_"#%0)!=-1)Bit_Let(gs_ALS,_:ALS_On%0);
	
	//#define ALS_CALL_INT<%0,%2>(%3) return Bit_GetBit(Bit:gs_ALS,_:ALS_On%0)?P@(#ALS_PREFIX"_On"#%0,#%2#x,%3):1;
	
	// ALS Callback.
	#define _ALS_C_INT<%0,%2>(%3) Bit_GetBit(Bit:gs_ALS,_:ALS_On%0)?P@(#ALS_PREFIX"_On"#%0,#%2#q,ALS_RS_%3):ALS_R_%0;
	#define ALS_C_INT<%0,%2>(%3) return _ALS_C_INT<%0,%2>(%3)
	// ALS Forward.
	#define ALS_F_INT<%0,%8>(%1) forward On%0(ALS_KS_%1);
	// ALS Go (ignore extra parameters).
	#define ALS_G_INT<%0,%1>(%8)(%2) W@(#On#%0,#%1#x,%2)
	
	// Default return value definitions.
	//#define ALS_R_AnyScriptInit             1
	//#define ALS_R_AnyScriptExit             1
	#define ALS_R_ScriptInit                1
	#define ALS_R_ScriptExit                1
	#define ALS_R_GameModeInit              1
	#define ALS_R_GameModeExit              1
	#define ALS_R_FilterScriptInit          1
	#define ALS_R_FilterScriptExit          1
	#define ALS_R_PlayerConnect             1
	#define ALS_R_PlayerDisconnect          1
	#define ALS_R_PlayerSpawn               1
	#define ALS_R_PlayerDeath               1
	#define ALS_R_VehicleSpawn              1
	#define ALS_R_VehicleDeath              1
	#define ALS_R_PlayerText                1
	#define ALS_R_PlayerCommandText         0
	#define ALS_R_PlayerRequestClass        1
	#define ALS_R_PlayerEnterVehicle        1
	#define ALS_R_PlayerExitVehicle         1
	#define ALS_R_PlayerStateChange         1
	#define ALS_R_PlayerEnterCheckpoint     1
	#define ALS_R_PlayerLeaveCheckpoint     1
	#define ALS_R_PlayerEnterRaceCheckpoint 1
	#define ALS_R_PlayerLeaveRaceCheckpoint 1
	#define ALS_R_RconCommand               1
	#define ALS_R_PlayerRequestSpawn        1
	#define ALS_R_ObjectMoved               1
	#define ALS_R_PlayerObjectMoved         1
	#define ALS_R_PlayerPickUpPickup        1
	#define ALS_R_VehicleMod                1
	#define ALS_R_EnterExitModShop          1
	#define ALS_R_VehiclePaintjob           1
	#define ALS_R_VehicleRespray            1
	#define ALS_R_VehicleDamageStatusUpdate 1
	#define ALS_R_PlayerSelectedMenuRow     1
	#define ALS_R_PlayerExitedMenu          1
	#define ALS_R_PlayerInteriorChange      1
	#define ALS_R_PlayerKeyStateChange      1
	#define ALS_R_RconLoginAttempt          1
	#define ALS_R_PlayerUpdate              1
	#define ALS_R_PlayerStreamIn            1
	#define ALS_R_PlayerStreamOut           1
	#define ALS_R_VehicleStreamIn           1
	#define ALS_R_VehicleStreamOut          1
	#define ALS_R_DialogResponse            1
	#define ALS_R_PlayerClickPlayer         1
	#define ALS_R_PlayerLogin               1
	#define ALS_R_PlayerLogout              1
	#define ALS_R_PlayerTakeDamage          1
	#define ALS_R_PlayerGiveDamage          1
	#define ALS_R_PlayerClickMap            1
	#define ALS_R_PlayerCommandReceived     1
	#define ALS_R_PlayerCommandPerformed    -1
	#define ALS_R_UnoccupiedVehicleUpdate   1
	
	// Chain call declarations.
	#define ALS_DO_ScriptInit<%0>                %0<ScriptInit               ,>(end:)
	#define ALS_DO_ScriptExit<%0>                %0<ScriptExit               ,>(end:)
	#define ALS_DO_GameModeInit<%0>              %0<GameModeInit             ,>(end:)
	#define ALS_DO_GameModeExit<%0>              %0<GameModeExit             ,>(end:)
	#define ALS_DO_FilterScriptInit<%0>          %0<FilterScriptInit         ,>(end:)
	#define ALS_DO_FilterScriptExit<%0>          %0<FilterScriptExit         ,>(end:)
	#define ALS_DO_PlayerConnect<%0>             %0<PlayerConnect            ,i>(end:playerid)
	#define ALS_DO_PlayerDisconnect<%0>          %0<PlayerDisconnect         ,ii>(more:playerid,end:reason)
	#define ALS_DO_PlayerSpawn<%0>               %0<PlayerSpawn              ,i>(end:playerid)
	#define ALS_DO_PlayerDeath<%0>               %0<PlayerDeath              ,iii>(more:playerid,more:killerid,end:reason)
	#define ALS_DO_VehicleSpawn<%0>              %0<VehicleSpawn             ,i>(end:vehicleid)
	#define ALS_DO_VehicleDeath<%0>              %0<VehicleDeath             ,ii>(more:vehicleid,end:killerid)
	#define ALS_DO_PlayerText<%0>                %0<PlayerText               ,is>(more:playerid,end_string:text[])
	#define ALS_DO_PlayerCommandText<%0>         %0<PlayerCommandText        ,is>(more:playerid,end_string:cmdtext[])
	#define ALS_DO_PlayerRequestClass<%0>        %0<PlayerRequestClass       ,ii>(more:playerid,end:classid)
	#define ALS_DO_PlayerEnterVehicle<%0>        %0<PlayerEnterVehicle       ,iii>(more:playerid,more:vehicleid,end:ispassenger)
	#define ALS_DO_PlayerExitVehicle<%0>         %0<PlayerExitVehicle        ,ii>(more:playerid,end:vehicleid)
	#define ALS_DO_PlayerStateChange<%0>         %0<PlayerStateChange        ,iii>(more:playerid,more:newstate,end:oldstate)
	#define ALS_DO_PlayerEnterCheckpoint<%0>     %0<PlayerEnterCheckpoint    ,i>(end:playerid)
	#define ALS_DO_PlayerLeaveCheckpoint<%0>     %0<PlayerLeaveCheckpoint    ,i>(end:playerid)
	#define ALS_DO_PlayerEnterRaceCheckpoint<%0> %0<PlayerEnterRaceCheckpoint,i>(end:playerid)
	#define ALS_DO_PlayerLeaveRaceCheckpoint<%0> %0<PlayerLeaveRaceCheckpoint,i>(end:playerid)
	#define ALS_DO_RconCommand<%0>               %0<RconCommand              ,s>(end_string:cmd[])
	#define ALS_DO_PlayerRequestSpawn<%0>        %0<PlayerRequestSpawn       ,i>(end:playerid)
	#define ALS_DO_ObjectMoved<%0>               %0<ObjectMoved              ,i>(end:objectid)
	#define ALS_DO_PlayerObjectMoved<%0>         %0<PlayerObjectMoved        ,ii>(more:playerid,end:objectid)
	#define ALS_DO_PlayerPickUpPickup<%0>        %0<PlayerPickUpPickup       ,ii>(more:playerid,end:pickupid)
	#define ALS_DO_VehicleMod<%0>                %0<VehicleMod               ,iii>(more:playerid,more:vehicleid,end:componentid)
	#define ALS_DO_EnterExitModShop<%0>          %0<EnterExitModShop         ,iii>(more:playerid,more:enterexit,end:interiorid)
	#define ALS_DO_VehiclePaintjob<%0>           %0<VehiclePaintjob          ,iii>(more:playerid,more:vehicleid,end:paintjobid)
	#define ALS_DO_VehicleRespray<%0>            %0<VehicleRespray           ,iiii>(more:playerid,more:vehicleid,more:color1,end:color2)
	#define ALS_DO_VehicleDamageStatusUpdate<%0> %0<VehicleDamageStatusUpdate,ii>(more:vehicleid,end:playerid)
	#define ALS_DO_PlayerSelectedMenuRow<%0>     %0<PlayerSelectedMenuRow    ,ii>(more:playerid,end:row)
	#define ALS_DO_PlayerExitedMenu<%0>          %0<PlayerExitedMenu         ,i>(end:playerid)
	#define ALS_DO_PlayerInteriorChange<%0>      %0<PlayerInteriorChange     ,iii>(more:playerid,more:newinteriorid,end:oldinteriorid)
	#define ALS_DO_PlayerKeyStateChange<%0>      %0<PlayerKeyStateChange     ,iii>(more:playerid,more:newkeys,end:oldkeys)
	#define ALS_DO_RconLoginAttempt<%0>          %0<RconLoginAttempt         ,ssi>(string:ip[],string:password[],end:success)
	#define ALS_DO_PlayerUpdate<%0>              %0<PlayerUpdate             ,i>(end:playerid)
	#define ALS_DO_PlayerStreamIn<%0>            %0<PlayerStreamIn           ,ii>(more:playerid,end:forplayerid)
	#define ALS_DO_PlayerStreamOut<%0>           %0<PlayerStreamOut          ,ii>(more:playerid,end:forplayerid)
	#define ALS_DO_VehicleStreamIn<%0>           %0<VehicleStreamIn          ,ii>(more:vehicleid,end:forplayerid)
	#define ALS_DO_VehicleStreamOut<%0>          %0<VehicleStreamOut         ,ii>(more:vehicleid,end:forplayerid)
	#define ALS_DO_DialogResponse<%0>            %0<DialogResponse           ,iiiis>(more:playerid,more:dialogid,more:response,more:listitem,end_string:inputtext[])
	#define ALS_DO_PlayerClickPlayer<%0>         %0<PlayerClickPlayer        ,iii>(more:playerid,more:clickedplayerid,end:source)
	#define ALS_DO_PlayerLogin<%0>               %0<PlayerLogin              ,ii>(more:playerid,end:uid)
	#define ALS_DO_PlayerLogout<%0>              %0<PlayerLogout             ,ii>(more:playerid,end:uid)
	#define ALS_DO_PlayerGiveDamage<%0>          %0<PlayerGiveDamage         ,iifi>(more:playerid,more:damagedid,tag:Float:amount,end:weaponid)
	#define ALS_DO_PlayerTakeDamage<%0>          %0<PlayerTakeDamage         ,iifi>(more:playerid,more:issuerid,tag:Float:amount,end:weaponid)
	#define ALS_DO_PlayerClickMap<%0>            %0<PlayerClickMap           ,ifff>(more:playerid,tag:Float:fX,tag:Float:fY,end_tag:Float:fZ)
	#define ALS_DO_PlayerCommandReceived<%0>     %0<PlayerCommandReceived    ,is>(more:playerid,end_string:cmdtext[])
	#define ALS_DO_PlayerCommandPerformed<%0>    %0<PlayerCommandPerformed   ,isi>(more:playerid,string:cmdtext[],end:success)
	#define ALS_DO_UnoccupiedVehicleUpdate<%0>    %0<UnoccupiedVehicleUpdate   ,iii>(more:vehicleid,more:playerid,end:passenger_seat)
	//#define ALS_CALL<%0> ALS_C_%0
	//#define ALS_FORWARD<%0> ALS_F_%0
	
	//#define call%0On%1(%2) ALS_G_%1(%2)
	
	#define ALS_KS_more:%0,         %0,ALS_KS_
	#define ALS_KS_string:%0[],     %0[],ALS_KS_
	#define ALS_KS_tag:%3:%0,       %3:%0,ALS_KS_
	#define ALS_KS_end:%0)          %0)
	#define ALS_KS_end_string:%0[]) %0[])
	#define ALS_KS_end_tag:%3:%0)   %3:%0)

	#define ALS_RS_more:%0,         %0,ALS_RS_
	#define ALS_RS_string:%0[],     ((%0[0])?(%0):NULL),ALS_RS_
	#define ALS_RS_tag:%3:%0,       %0,ALS_RS_
	#define ALS_RS_end:%0)          %0)
	#define ALS_RS_end_string:%0[]) ((%0[0])?(%0):NULL))
	#define ALS_RS_end_tag:%3:%0)   %0)
	
	#define ALS_DO:%9<%0> ALS_DO_%0<%9>
	
	#define ALS_CALL<%0> ALS_DO:ALS_C_INT<%0>
	#define ALS_GET<%0> ALS_DO:_ALS_C_INT<%0>
	#define ALS_FORWARD<%0> ALS_DO:ALS_F_INT<%0>
	
	#define call%0On%1(%2) ALS_DO:ALS_G_INT<%1>(%2)
	
	
	/*ALS_DoDetect(const str[]);
	public ALS_DoDetect(const str[])
	{
		new
			addr;
		addr = funcidx(str);
		if (addr != -1)
		{
			// Get the actual function address, not just the structure offset.
			addr *= 8;
			addr += AMX_HEADER_PUBLICS;
			#emit LREF.S.pri addr
			#emit STOR.S.pri addr
		}
		return addr;
	}*/
	
#endif

#if !defined ALS_PREFIX
	//#error You must define a callback prefix before including y_als.
	#define ALS_PREFIX Mode
#endif
