#if defined _INC_y_als
	#endinput
#endif
#define _INC_y_als

/**
 * <library
 *   name="y_als"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Provides a number of macros for making ALS (Advanced Library System) callback hooking simpler."
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
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (c) 2022
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

/**
 * <library>y_als</library>
 */
enum ALS
{
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
	Bit:ALS_OnUnoccupiedVehicleUpdate,
	Bit:ALS_OnPlayerClickTextDraw,
	Bit:ALS_OnPlayerClickPlayerTextDraw,
	Bit:ALS_OnPlayerEditObject,
	Bit:ALS_OnPlayerEditAttachedObject,
	// Added 05/07/17
	Bit:ALS_OnPlayerWeaponShot,
	Bit:ALS_OnIncomingConnection,
	Bit:ALS_OnTrailerUpdate,
	Bit:ALS_OnVehicleSirenStateChange,
	Bit:ALS_OnPlayerGiveDamageActor,
	Bit:ALS_OnActorStreamIn,
	Bit:ALS_OnActorStreamOut,
	// YSI
	Bit:ALS_OnPlayerEnterArea,
	Bit:ALS_OnPlayerLeaveArea,
	Bit:ALS_OnPlayerFinishRace,
	Bit:ALS_OnPlayerExitRace,
	Bit:ALS_OnRaceEnd,
	#if defined _YSI_PLUGINS_STREAMER
		Bit:ALS_OnDynamicObjectMoved,
		Bit:ALS_OnPlayerEditDynamicObject,
		Bit:ALS_OnPlayerSelectDynamicObject,
		Bit:ALS_OnPlayerPickUpDynamicPickup,
		Bit:ALS_OnPlayerEnterDynamicCP,
		Bit:ALS_OnPlayerLeaveDynamicCP,
		Bit:ALS_OnPlayerEnterDynamicRaceCP,
		Bit:ALS_OnPlayerLeaveDynamicRaceCP,
		Bit:ALS_OnPlayerEnterDynamicArea,
		Bit:ALS_OnPlayerLeaveDynamicArea,
	#endif
	Bit:ALS_OnPlayerSelectObject
}
static stock ALS:_@ALS() { return ALS; }

#define ALS_DATA<>

#define ALS_DETECT<%0>

// ALS Callback.
#define _ALS_C_INT<%0,%2>(%3) ALS_MAKE<..._On%0>(ALS_RS_%3);
#define ALS_D_INT%8<%0,%2>(%3) On%0%8(ALS_DS_%3)
#define ALS_C_INT<%0,%2>(%3) return _ALS_C_INT<%0,%2>(%3)
#define ALS_DC_(%0)%1(%2) %1(S%0%2)
// ALS Forward.
#define ALS_F_INT<%0,%8>(%1) forward ALS_MAKE<..._On%0>(ALS_KS_%1);//ALS_F_INT1<%0,%8>(%1)ALS_F_INT2<%0,%8>(%1)
//#define ALS_F_INT1<%0,%8>(%1) public ALS_MAKE<..._On%0>(ALS_KS_%1)<_ALS_:unhooked>{return ALS_R_%0;}
//#define ALS_F_INT2<%0,%8>(%1) public ALS_MAKE<..._On%0>(ALS_KS_%1)<>{return ALS_R_%0;}

// ALS Go (ignore extra parameters).
#define ALS_G_INT<%0,%1>(%8)(%2) W@(#On#%0,(x:#%1#),%2)

// Default return value definitions.
#define ALS_R_ScriptInit 1
#define ALS_R_ScriptExit 1
#define ALS_R_GameModeInit 1
#define ALS_R_GameModeExit 1
#define ALS_R_FilterScriptInit 1
#define ALS_R_FilterScriptExit 1
#define ALS_R_PlayerConnect 1
#define ALS_R_PlayerDisconnect 1
#define ALS_R_PlayerSpawn 1
#define ALS_R_PlayerDeath 1
#define ALS_R_VehicleSpawn 1
#define ALS_R_VehicleDeath 1
#define ALS_R_PlayerText 1
#define ALS_R_PlayerCommandText 0
#define ALS_R_PlayerRequestClass 1
#define ALS_R_PlayerEnterVehicle 1
#define ALS_R_PlayerExitVehicle 1
#define ALS_R_PlayerStateChange 1
#define ALS_R_PlayerEnterCheckpoint 1
#define ALS_R_PlayerLeaveCheckpoint 1
#define ALS_R_PlayerEnterRaceCheckpoint 1
#define ALS_R_PlayerLeaveRaceCheckpoint 1
#define ALS_R_RconCommand 1
#define ALS_R_PlayerRequestSpawn 1
#define ALS_R_ObjectMoved 1
#define ALS_R_PlayerObjectMoved 1
#define ALS_R_PlayerPickUpPickup 1
#define ALS_R_VehicleMod 1
#define ALS_R_EnterExitModShop 1
#define ALS_R_VehiclePaintjob 1
#define ALS_R_VehicleRespray 1
#define ALS_R_VehicleDamageStatusUpdate 1
#define ALS_R_PlayerSelectedMenuRow 1
#define ALS_R_PlayerExitedMenu 1
#define ALS_R_PlayerInteriorChange 1
#define ALS_R_PlayerKeyStateChange 1
#define ALS_R_RconLoginAttempt 1
#define ALS_R_PlayerUpdate 1
#define ALS_R_PlayerStreamIn 1
#define ALS_R_PlayerStreamOut 1
#define ALS_R_VehicleStreamIn 1
#define ALS_R_VehicleStreamOut 1
#define ALS_R_DialogResponse 1
#define ALS_R_PlayerClickPlayer 1
#define ALS_R_PlayerLogin 1
#define ALS_R_PlayerLogout 1
#define ALS_R_PlayerTakeDamage 1
#define ALS_R_PlayerGiveDamage 1
#define ALS_R_PlayerClickMap 1
#define ALS_R_PlayerCommandReceived 1
#define ALS_R_PlayerCommandPerformed -1
#define ALS_R_UnoccupiedVehicleUpdate 1
// 0.3e
#define ALS_R_PlayerClickTextDraw 1
#define ALS_R_PlayerClickPlayerTextDraw 1
#define ALS_R_PlayerEditObject 1
#define ALS_R_PlayerEditAttachedObject 1
#define ALS_R_PlayerSelectObject 1
// YSI
#define ALS_R_PlayerEnterArea 1
#define ALS_R_PlayerLeaveArea 1
#define ALS_R_PlayerFinishRace 1
#define ALS_R_PlayerExitRace 1
#define ALS_R_RaceEnd 1
#define ALS_R_MasterSystemClose 1
// Streamer plugins.
#define ALS_R_DynamicObjectMoved 1
#define ALS_R_PlayerEditDynamicObject 1
#define ALS_R_PlayerSelectDynamicObject 1
#define ALS_R_PlayerPickUpDynamicPickup 1
#define ALS_R_PlayerEnterDynamicCP 1
#define ALS_R_PlayerLeaveDynamicCP 1
#define ALS_R_PlayerEnterDynamicRaceCP 1
#define ALS_R_PlayerLeaveDynamicRaceCP 1
#define ALS_R_PlayerEnterDynamicArea 1
#define ALS_R_PlayerLeaveDynamicArea 1
// Alternates
#define ALS_R_PlayerLeaveRaceCP 1
#define ALS_R_PlayerEnterRaceCP 1
#define ALS_R_VehicleDamageStatusUpd 1
#define ALS_R_UnoccupiedVehicleUpd 1
#define ALS_R_PlayerClickPlayerTD 1
#define ALS_R_PlayerEditAttachedObj 1
#define ALS_R_PlayerCmdPerformed 1
#define ALS_R_PlayerEditDynObject 1
#define ALS_R_PlayerSelectDynObject 1
#define ALS_R_PlayerPickUpDynPickup 1
#define ALS_R_PlayerEnterDynRaceCP 1
#define ALS_R_PlayerLeaveDynRaceCP 1
#define ALS_R_PlayerEnterDynArea 1
#define ALS_R_PlayerLeaveDynArea 1
// Added 05/07/17
#define ALS_R_PlayerWeaponShot 1
#define ALS_R_IncomingConnection 1
#define ALS_R_TrailerUpdate 1
#define ALS_R_VehicleSirenStateChange 1
#define ALS_R_PlayerGiveDamageActor 1
#define ALS_R_ActorStreamIn 1
#define ALS_R_ActorStreamOut 1

// Chain call declarations.
#define ALS_DO_ScriptInit<%0> %0<ScriptInit,>(none:)
#define ALS_DO_ScriptExit<%0> %0<ScriptExit,>(none:)
#define ALS_DO_GameModeInit<%0> %0<GameModeInit,>(none:)
#define ALS_DO_GameModeExit<%0> %0<GameModeExit,>(none:)
#define ALS_DO_FilterScriptInit<%0> %0<FilterScriptInit,>(none:)
#define ALS_DO_FilterScriptExit<%0> %0<FilterScriptExit,>(none:)
#define ALS_DO_PlayerConnect<%0> %0<PlayerConnect,i>(end:playerid)
#define ALS_DO_PlayerDisconnect<%0> %0<PlayerDisconnect,ii>(more:playerid,end:reason)
#define ALS_DO_PlayerSpawn<%0> %0<PlayerSpawn,i>(end:playerid)
#define ALS_DO_PlayerDeath<%0> %0<PlayerDeath,iii>(more:playerid,more:killerid,end:reason)
#define ALS_DO_VehicleSpawn<%0> %0<VehicleSpawn,i>(end:vehicleid)
#define ALS_DO_VehicleDeath<%0> %0<VehicleDeath,ii>(more:vehicleid,end:killerid)
#define ALS_DO_PlayerText<%0> %0<PlayerText,is>(more:playerid,end_string:text[])
#define ALS_DO_PlayerCommandText<%0> %0<PlayerCommandText,is>(more:playerid,end_string:cmdtext[])
#define ALS_DO_PlayerRequestClass<%0> %0<PlayerRequestClass,ii>(more:playerid,end:classid)
#define ALS_DO_PlayerEnterVehicle<%0> %0<PlayerEnterVehicle,iii>(more:playerid,more:vehicleid,end:ispassenger)
#define ALS_DO_PlayerExitVehicle<%0> %0<PlayerExitVehicle,ii>(more:playerid,end:vehicleid)
#define ALS_DO_PlayerStateChange<%0> %0<PlayerStateChange,iii>(more:playerid,more:newstate,end:oldstate)
#define ALS_DO_PlayerEnterCheckpoint<%0> %0<PlayerEnterCheckpoint,i>(end:playerid)
#define ALS_DO_PlayerLeaveCheckpoint<%0> %0<PlayerLeaveCheckpoint,i>(end:playerid)
#define ALS_DO_PlayerEnterRaceCheckpoint<%0> %0<PlayerEnterRaceCheckpoint,i>(end:playerid)
#define ALS_DO_PlayerLeaveRaceCheckpoint<%0> %0<PlayerLeaveRaceCheckpoint,i>(end:playerid)
#define ALS_DO_RconCommand<%0> %0<RconCommand,s>(end_string:cmd[])
#define ALS_DO_PlayerRequestSpawn<%0> %0<PlayerRequestSpawn,i>(end:playerid)
#define ALS_DO_ObjectMoved<%0> %0<ObjectMoved,i>(end:objectid)
#define ALS_DO_PlayerObjectMoved<%0> %0<PlayerObjectMoved,ii>(more:playerid,end:objectid)
#define ALS_DO_PlayerPickUpPickup<%0> %0<PlayerPickUpPickup,ii>(more:playerid,end:pickupid)
#define ALS_DO_VehicleMod<%0> %0<VehicleMod,iii>(more:playerid,more:vehicleid,end:componentid)
#define ALS_DO_EnterExitModShop<%0> %0<EnterExitModShop,iii>(more:playerid,more:enterexit,end:interiorid)
#define ALS_DO_VehiclePaintjob<%0> %0<VehiclePaintjob,iii>(more:playerid,more:vehicleid,end:paintjobid)
#define ALS_DO_VehicleRespray<%0> %0<VehicleRespray,iiii>(more:playerid,more:vehicleid,more:color1,end:color2)
#define ALS_DO_VehicleDamageStatusUpdate<%0> %0<VehicleDamageStatusUpdate,ii>(more:vehicleid,end:playerid)
#define ALS_DO_PlayerSelectedMenuRow<%0> %0<PlayerSelectedMenuRow,ii>(more:playerid,end:row)
#define ALS_DO_PlayerExitedMenu<%0> %0<PlayerExitedMenu,i>(end:playerid)
#define ALS_DO_PlayerInteriorChange<%0> %0<PlayerInteriorChange,iii>(more:playerid,more:newinteriorid,end:oldinteriorid)
#define ALS_DO_PlayerKeyStateChange<%0> %0<PlayerKeyStateChange,iii>(more:playerid,more:newkeys,end:oldkeys)
#define ALS_DO_RconLoginAttempt<%0> %0<RconLoginAttempt,ssi>(string:ip[],string:password[],end:success)
#define ALS_DO_PlayerUpdate<%0> %0<PlayerUpdate,i>(end:playerid)
#define ALS_DO_PlayerStreamIn<%0> %0<PlayerStreamIn,ii>(more:playerid,end:forplayerid)
#define ALS_DO_PlayerStreamOut<%0> %0<PlayerStreamOut,ii>(more:playerid,end:forplayerid)
#define ALS_DO_VehicleStreamIn<%0> %0<VehicleStreamIn,ii>(more:vehicleid,end:forplayerid)
#define ALS_DO_VehicleStreamOut<%0> %0<VehicleStreamOut,ii>(more:vehicleid,end:forplayerid)
#define ALS_DO_DialogResponse<%0> %0<DialogResponse,iiiis>(more:playerid,more:dialogid,more:response,more:listitem,end_string:inputtext[])
#define ALS_DO_PlayerClickPlayer<%0> %0<PlayerClickPlayer,iii>(more:playerid,more:clickedplayerid,end:source)
#define ALS_DO_PlayerLogin<%0> %0<PlayerLogin,ii>(more:playerid,end:uid)
#define ALS_DO_PlayerLogout<%0> %0<PlayerLogout,ii>(more:playerid,end:uid)
#if defined GetPlayerLastShotVectors // 0.3z RC4
	#define ALS_DO_PlayerGiveDamage<%0> %0<PlayerGiveDamage,iifii>(more:playerid,more:damagedid,Float:amount,more:weaponid,end:bodypart)
	#define ALS_DO_PlayerTakeDamage<%0> %0<PlayerTakeDamage,iifii>(more:playerid,more:issuerid,Float:amount,more:weaponid,end:bodypart)
#else
	#define ALS_DO_PlayerGiveDamage<%0> %0<PlayerGiveDamage,iifi>(more:playerid,more:damagedid,Float:amount,end:weaponid)
	#define ALS_DO_PlayerTakeDamage<%0> %0<PlayerTakeDamage,iifi>(more:playerid,more:issuerid,Float:amount,end:weaponid)
#endif
#define ALS_DO_PlayerClickMap<%0> %0<PlayerClickMap,ifff>(more:playerid,Float:fX,Float:fY,end_Float:fZ)
#define ALS_DO_PlayerCommandReceived<%0> %0<PlayerCommandReceived,is>(more:playerid,end_string:cmdtext[])
#define ALS_DO_PlayerCommandPerformed<%0> %0<PlayerCommandPerformed,isi>(more:playerid,string:cmdtext[],end:success)
#if defined GetServerTickRate // 0.3z RC5
	#define ALS_DO_UnoccupiedVehicleUpdate<%0> %0<UnoccupiedVehicleUpdate,iiifff>(more:vehicleid,more:playerid,more:passenger_seat,Float:new_x,Float:new_y,end_Float:new_z)
#else
	#define ALS_DO_UnoccupiedVehicleUpdate<%0> %0<UnoccupiedVehicleUpdate,iii>(more:vehicleid,more:playerid,end:passenger_seat)
#endif
// 0.3e
#define ALS_DO_PlayerClickTextDraw<%0> %0<PlayerClickTextDraw,ii>(more:playerid,end_tag:Text:clickedid)
#define ALS_DO_PlayerClickPlayerTextDraw<%0> %0<PlayerClickPlayerTextDraw,iii>(more:playerid,end_tag:PlayerText:playertextid)
#define ALS_DO_PlayerEditObject<%0> %0<PlayerEditObject,iiiiffffff>(more:playerid,more:playerobject,more:objectid,more:response,Float:fX,Float:fY,Float:fZ,Float:fRotX,Float:fRotY,end_Float:fRotZ)
#define ALS_DO_PlayerEditAttachedObject<%0> %0<PlayerEditAttachedObject,iiiiifffffffff>(more:playerid,more:response,more:index,more:modelid,more:boneid,Float:fOffsetX,Float:fOffsetY,Float:fOffsetZ,Float:fRotX,Float:fRotY,Float:fRotZ,Float:fScaleX,Float:fScaleY,end_Float:fScaleZ)
#define ALS_DO_PlayerSelectObject<%0> %0<PlayerSelectObject,iiiifff>(more:playerid,more:type,more:objectid,more:modelid,Float:fX,Float:fY,end_Float:fZ)
// YSI
#define ALS_DO_PlayerEnterArea<%0> %0<PlayerEnterArea,ii>(more:playerid,end:areaid)
#define ALS_DO_PlayerLeaveArea<%0> %0<PlayerLeaveArea,ii>(more:playerid,end:areaid)
#define ALS_DO_PlayerFinishRace<%0> %0<PlayerFinishRace,iiiii>(more:playerid,more:race,more:position,more:prize,end:time)
#define ALS_DO_PlayerExitRace<%0> %0<PlayerExitRace,ii>(more:playerid,end:race)
#define ALS_DO_RaceEnd<%0> %0<RaceEnd,i>(end:race)
// Streamer plugin.
#define ALS_DO_DynamicObjectMoved<%0> %0<DynamicObjectMoved,i>(end:objectid)
#define ALS_DO_PlayerEditDynamicObject<%0> %0<PlayerEditDynamicObject,iiiffffff>(more:playerid,more:objectid,more:response,Float:x,Float:y,Float:z,Float:rx,Float:ry,end_Float:rz)
#define ALS_DO_PlayerSelectDynamicObject<%0> %0<PlayerSelectDynamicObject,iiifff>(more:playerid,more:objectid,more:modelid,Float:x,Float:y,end_Float:z)
#define ALS_DO_PlayerPickUpDynamicPickup<%0> %0<PlayerPickUpDynamicPickup,ii>(more:playerid,end:pickupid)
#define ALS_DO_PlayerEnterDynamicCP<%0> %0<PlayerEnterDynamicCP,ii>(more:playerid,end:checkpointid)
#define ALS_DO_PlayerLeaveDynamicCP<%0> %0<PlayerLeaveDynamicCP,ii>(more:playerid,end:checkpointid)
#define ALS_DO_PlayerEnterDynamicRaceCP<%0> %0<PlayerEnterDynamicRaceCP,ii>(more:playerid,end:checkpointid)
#define ALS_DO_PlayerLeaveDynamicRaceCP<%0> %0<PlayerLeaveDynamicRaceCP,ii>(more:playerid,end:checkpointid)
#define ALS_DO_PlayerEnterDynamicArea<%0> %0<PlayerEnterDynamicArea,ii>(more:playerid,end:areaid)
#define ALS_DO_PlayerLeaveDynamicArea<%0> %0<PlayerLeaveDynamicArea,ii>(more:playerid,end:areaid)
// Added 05/07/17
#define ALS_DO_PlayerWeaponShot<%0> %0<PlayerWeaponShot,iiiifff>(more:playerid,more:weaponid,more:hittype,more:hitid,Float:fX,Float:fY,end_Float:fZ)
#define ALS_DO_IncomingConnection<%0> %0<IncomingConnection,i>(more:playerid,string:ip_address[],end:port)
#define ALS_DO_TrailerUpdate<%0> %0<TrailerUpdate,ii>(more:playerid,end:vehicleid)
#define ALS_DO_VehicleSirenStateChange<%0> %0<VehicleSirenStateChange,iii>(more:playerid,more:vehicleid,end:newstate)
#define ALS_DO_PlayerGiveDamageActor<%0> %0<PlayerGiveDamageActor,iifii>(more:playerid,more:damaged_actorid,Float:amount,more:weaponid,end:bodypart)
#define ALS_DO_ActorStreamIn<%0> %0<ActorStreamIn,ii>(more:actorid,end:forplayerid)
#define ALS_DO_ActorStreamOut<%0> %0<ActorStreamOut,ii>(more:actorid,end:forplayerid)

#define ALS_KS_more:%0,         %0,ALS_KS_
#define ALS_KS_string:%0[],     %0[],ALS_KS_
#define ALS_KS_Float:%0,        Float:%0,ALS_KS_
#define ALS_KS_tag:%3:%0,       %3:%0,ALS_KS_
#define ALS_KS_array:%0[%1],    %0[%1],ALS_KS_
#define ALS_KS_end:%0)          %0)
#define ALS_KS_none:)           )
#define ALS_KS_end_string:%0[]) %0[])
#define ALS_KS_end_Float:%0)    Float:%0)
#define ALS_KS_end_tag:%3:%0)   %3:%0)
#define ALS_KS_end_array:%0[%1]) %0[%1])

#define ALS_KS_const%9: const ALS_KS_%9:
#define ALS_KS_%0\32; ALS_KS_

#define ALS_TS_more:%0,         %0,ALS_TS_
#define ALS_TS_string:%0[],     (%0),ALS_TS_
#define ALS_TS_Float%0,         Float:%0,ALS_TS_
#define ALS_TS_tag:%3:%0,       %3:%0,ALS_TS_
#define ALS_TS_array:%0[%1],    (%0),ALS_TS_
#define ALS_TS_end:%0)          %0)
#define ALS_TS_none:)           )
#define ALS_TS_end_string:%0[]) (%0))
#define ALS_TS_end_Float:%0)    Float:%0)
#define ALS_TS_end_tag:%3:%0)   %3:%0)
#define ALS_TS_end_array:%0[%1]) (%0))

#define ALS_TS_const%9: ALS_TS_%9:
#define ALS_TS_%0\32; ALS_TS_

#define ALS_RS_more:%0,         %0,ALS_RS_
#define ALS_RS_string:%0[],     ((%0[0])?(%0):NULL),ALS_RS_
#define ALS_RS_Float:%0,        (_:%0),ALS_RS_
#define ALS_RS_tag:%3:%0,       (_:%0),ALS_RS_
#define ALS_RS_array:%0[%1],    (_:%0),ALS_RS_
#define ALS_RS_end:%0)          %0)
#define ALS_RS_none:)           )
#define ALS_RS_end_string:%0[]) ((%0[0])?(%0):NULL))
#define ALS_RS_end_Float:%0)    (_:%0))
#define ALS_RS_end_tag:%3:%0)   (_:%0))
#define ALS_RS_end_array:%0[%1]) (_:%0))

#define ALS_RS_const%9: ALS_RS_%9:
#define ALS_RS_%0\32; ALS_RS_

#define ALS_DS_more:%0,         0,ALS_DS_
#define ALS_DS_string:%0[],     __ARR,ALS_DS_
#define ALS_DS_Float:%0,        0.0,ALS_DS_
#define ALS_DS_tag:%3:%0,       %3:0,ALS_DS_
#define ALS_DS_array:%0[%1],    __ARR,ALS_DS_
#define ALS_DS_end:%0)          0)
#define ALS_DS_none:)           )
#define ALS_DS_end_string:%0[]) __ARR)
#define ALS_DS_end_Float:%0)    0.0)
#define ALS_DS_end_tag:%3:%0)   %3:0)
#define ALS_DS_end_array:%0[%1]) __ARR)

#define ALS_DS_const%9: ALS_DS_%9:
#define ALS_DS_%0\32; ALS_DS_

#define ALS_DO:%9<%0> ALS_DO_%0<%9>
#define ALS_MAIN_RET_ ALS_MRET_
#define ALS_main_:%0( ALS_DC_(C)ALS_MAIN_RET_(M) public %0(

#define ALS_CALL<%0> ALS_DO:ALS_C_INT<%0>
#define ALS_GET<%0> ALS_DO:_ALS_C_INT<%0>
#define ALS_FORWARD<%0> ALS_DO:ALS_F_INT<%0>

#define call%0On%1(%2) ALS_DO:ALS_G_INT<%1>(%2)

// Convert to the `CALL@` syntax from `addressof()`.
#define CALL@OnScriptInit%8() OnScriptInit%8()
#define CALL@OnScriptExit%8() OnScriptExit%8()
#define CALL@OnGameModeInit%8() OnGameModeInit%8()
#define CALL@OnGameModeExit%8() OnGameModeExit%8()
#define CALL@OnFilterScriptInit%8() OnFilterScriptInit%8()
#define CALL@OnFilterScriptExit%8() OnFilterScriptExit%8()
#define CALL@OnPlayerConnect%8() OnPlayerConnect%8(0)
#define CALL@OnPlayerDisconnect%8() OnPlayerDisconnect%8(0,0)
#define CALL@OnPlayerSpawn%8() OnPlayerSpawn%8(0)
#define CALL@OnPlayerDeath%8() OnPlayerDeath%8(0,0,0)
#define CALL@OnVehicleSpawn%8() OnVehicleSpawn%8(0)
#define CALL@OnVehicleDeath%8() OnVehicleDeath%8(0,0)
#define CALL@OnPlayerText%8() OnPlayerText%8(0,__ARR)
#define CALL@OnPlayerCommandText%8() OnPlayerCommandText%8(0,__ARR)
#define CALL@OnPlayerRequestClass%8() OnPlayerRequestClass%8(0,0)
#define CALL@OnPlayerEnterVehicle%8() OnPlayerEnterVehicle%8(0,0,0)
#define CALL@OnPlayerExitVehicle%8() OnPlayerExitVehicle%8(0,0)
#define CALL@OnPlayerStateChange%8() OnPlayerStateChange%8(0,0,0)
#define CALL@OnPlayerEnterCheckpoint%8() OnPlayerEnterCheckpoint%8(0)
#define CALL@OnPlayerLeaveCheckpoint%8() OnPlayerLeaveCheckpoint%8(0)
#define CALL@OnPlayerEnterRaceCheckpoint%8() OnPlayerEnterRaceCheckpoint%8(0)
#define CALL@OnPlayerLeaveRaceCheckpoint%8() OnPlayerLeaveRaceCheckpoint%8(0)
#define CALL@OnRconCommand%8() OnRconCommand%8(__ARR)
#define CALL@OnPlayerRequestSpawn%8() OnPlayerRequestSpawn%8(0)
#define CALL@OnObjectMoved%8() OnObjectMoved%8(0)
#define CALL@OnPlayerObjectMoved%8() OnPlayerObjectMoved%8(0,0)
#define CALL@OnPlayerPickUpPickup%8() OnPlayerPickUpPickup%8(0,0)
#define CALL@OnVehicleMod%8() OnVehicleMod%8(0,0,0)
#define CALL@OnEnterExitModShop%8() OnEnterExitModShop%8(0,0,0)
#define CALL@OnVehiclePaintjob%8() OnVehiclePaintjob%8(0,0,0)
#define CALL@OnVehicleRespray%8() OnVehicleRespray%8(0,0,0,0)
#define CALL@OnVehicleDamageStatusUpdate%8() OnVehicleDamageStatusUpdate%8(0,0)
#define CALL@OnPlayerSelectedMenuRow%8() OnPlayerSelectedMenuRow%8(0,0)
#define CALL@OnPlayerExitedMenu%8() OnPlayerExitedMenu%8(0)
#define CALL@OnPlayerInteriorChange%8() OnPlayerInteriorChange%8(0,0,0)
#define CALL@OnPlayerKeyStateChange%8() OnPlayerKeyStateChange%8(0,0,0)
#define CALL@OnRconLoginAttempt%8() OnRconLoginAttempt%8(__ARR,__ARR,0)
#define CALL@OnPlayerUpdate%8() OnPlayerUpdate%8(0)
#define CALL@OnPlayerStreamIn%8() OnPlayerStreamIn%8(0,0)
#define CALL@OnPlayerStreamOut%8() OnPlayerStreamOut%8(0,0)
#define CALL@OnVehicleStreamIn%8() OnVehicleStreamIn%8(0,0)
#define CALL@OnVehicleStreamOut%8() OnVehicleStreamOut%8(0,0)
#define CALL@OnDialogResponse%8() OnDialogResponse%8(0,0,0,0,__ARR)
#define CALL@OnPlayerClickPlayer%8() OnPlayerClickPlayer%8(0,0,0)
#define CALL@OnPlayerLogin%8() OnPlayerLogin%8(0,0)
#define CALL@OnPlayerLogout%8() OnPlayerLogout%8(0,0)
#if defined GetPlayerLastShotVectors // 0.3z RC4
	#define CALL@OnPlayerGiveDamage%8() OnPlayerGiveDamage%8(0,0,0.0,0,0)
	#define CALL@OnPlayerTakeDamage%8() OnPlayerTakeDamage%8(0,0,0.0,0,0)
#else
	#define CALL@OnPlayerGiveDamage%8() OnPlayerGiveDamage%8(0,0,0.0,0)
	#define CALL@OnPlayerTakeDamage%8() OnPlayerTakeDamage%8(0,0,0.0,0)
#endif
#define CALL@OnPlayerClickMap%8() OnPlayerClickMap%8(0,0.0,0.0,0.0)
#define CALL@OnPlayerCommandReceived%8() OnPlayerCommandReceived%8(0,__ARR)
#define CALL@OnPlayerCommandPerformed%8() OnPlayerCommandPerformed%8(0,__ARR,0)
#if defined GetServerTickRate // 0.3z RC5
	#define CALL@OnUnoccupiedVehicleUpdate%8() OnUnoccupiedVehicleUpdate%8(0,0,0,0.0,0.0,0.0)
#else
	#define CALL@OnUnoccupiedVehicleUpdate%8() OnUnoccupiedVehicleUpdate%8(0,0,0)
#endif
// 0.3e
#define CALL@OnPlayerClickTextDraw%8() OnPlayerClickTextDraw%8(0,Text:0)
#define CALL@OnPlayerClickPlayerTextDraw%8() OnPlayerClickPlayerTextDraw%8(0,PlayerText:0)
#define CALL@OnPlayerEditObject%8() OnPlayerEditObject%8(0,0,0,0,0.0,0.0,0.0,0.0,0.0,0.0)
#define CALL@OnPlayerEditAttachedObject%8() OnPlayerEditAttachedObject%8(0,0,0,0,0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0)
#define CALL@OnPlayerSelectObject%8() OnPlayerSelectObject%8(0,0,0,0,0.0,0.0,0.0)
// YSI
#define CALL@OnPlayerEnterArea%8() OnPlayerEnterArea%8(0,0)
#define CALL@OnPlayerLeaveArea%8() OnPlayerLeaveArea%8(0,0)
#define CALL@OnPlayerFinishRace%8() OnPlayerFinishRace%8(0,0,0,0,0)
#define CALL@OnPlayerExitRace%8() OnPlayerExitRace%8(0,0)
#define CALL@OnRaceEnd%8() OnRaceEnd%8(0)
// Streamer plugin.
#define CALL@OnDynamicObjectMoved%8() OnDynamicObjectMoved%8(0)
#define CALL@OnPlayerEditDynamicObject%8() OnPlayerEditDynamicObject%8(0,0,0,0.0,0.0,0.0,0.0,0.0,0.0)
#define CALL@OnPlayerSelectDynamicObject%8() OnPlayerSelectDynamicObject%8(0,0,0,0.0,0.0,0.0)
#define CALL@OnPlayerPickUpDynamicPickup%8() OnPlayerPickUpDynamicPickup%8(0,0)
#define CALL@OnPlayerEnterDynamicCP%8() OnPlayerEnterDynamicCP%8(0,0)
#define CALL@OnPlayerLeaveDynamicCP%8() OnPlayerLeaveDynamicCP%8(0,0)
#define CALL@OnPlayerEnterDynamicRaceCP%8() OnPlayerEnterDynamicRaceCP%8(0,0)
#define CALL@OnPlayerLeaveDynamicRaceCP%8() OnPlayerLeaveDynamicRaceCP%8(0,0)
#define CALL@OnPlayerEnterDynamicArea%8() OnPlayerEnterDynamicArea%8(0,0)
#define CALL@OnPlayerLeaveDynamicArea%8() OnPlayerLeaveDynamicArea%8(0,0)

#define CALL@OnPlayerWeaponShot%8() OnPlayerWeaponShot%8(0,0,0,0,0.0,0.0,0.0)
#define CALL@OnIncomingConnection%8() OnIncomingConnection%8(0,__ARR,0)
#define CALL@OnTrailerUpdate%8() OnTrailerUpdate%8(0,0)
#define CALL@OnVehicleSirenStateChange%8() OnVehicleSirenStateChange%8(0,0,0)
#define CALL@OnPlayerGiveDamageActor%8() OnPlayerGiveDamageActor%8(0,0,0.0,0,0)
#define CALL@OnActorStreamIn%8() OnActorStreamIn%8(0,0)
#define CALL@OnActorStreamOut%8() OnActorStreamOut%8(0,0)

