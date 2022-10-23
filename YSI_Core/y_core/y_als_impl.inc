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

#define ALS_DATA<>

#define ALS_DETECT<%0>

// ALS Callback.
#define _ALS_C_INT<%0,%2>(%3) ALS_MAKE<..._On%0>(ALS_RS_%3);
#define ALS_D_INT<%0,%2>(%3) On%0(ALS_DS_%3)
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
#define CALL@OnScriptInit ALS_DO_ScriptInit<ALS_D_INT>
#define CALL@OnScriptExit ALS_DO_ScriptExit<ALS_D_INT>
#define CALL@OnGameModeInit ALS_DO_GameModeInit<ALS_D_INT>
#define CALL@OnGameModeExit ALS_DO_GameModeExit<ALS_D_INT>
#define CALL@OnFilterScriptInit ALS_DO_FilterScriptInit<ALS_D_INT>
#define CALL@OnFilterScriptExit ALS_DO_FilterScriptExit<ALS_D_INT>
#define CALL@OnPlayerConnect ALS_DO_PlayerConnect<ALS_D_INT>
#define CALL@OnPlayerDisconnect ALS_DO_PlayerDisconnect<ALS_D_INT>
#define CALL@OnPlayerSpawn ALS_DO_PlayerSpawn<ALS_D_INT>
#define CALL@OnPlayerDeath ALS_DO_PlayerDeath<ALS_D_INT>
#define CALL@OnVehicleSpawn ALS_DO_VehicleSpawn<ALS_D_INT>
#define CALL@OnVehicleDeath ALS_DO_VehicleDeath<ALS_D_INT>
#define CALL@OnPlayerText ALS_DO_PlayerText<ALS_D_INT>
#define CALL@OnPlayerCommandText ALS_DO_PlayerCommandText<ALS_D_INT>
#define CALL@OnPlayerRequestClass ALS_DO_PlayerRequestClass<ALS_D_INT>
#define CALL@OnPlayerEnterVehicle ALS_DO_PlayerEnterVehicle<ALS_D_INT>
#define CALL@OnPlayerExitVehicle ALS_DO_PlayerExitVehicle<ALS_D_INT>
#define CALL@OnPlayerStateChange ALS_DO_PlayerStateChange<ALS_D_INT>
#define CALL@OnPlayerEnterCheckpoint ALS_DO_PlayerEnterCheckpoint<ALS_D_INT>
#define CALL@OnPlayerLeaveCheckpoint ALS_DO_PlayerLeaveCheckpoint<ALS_D_INT>
#define CALL@OnPlayerEnterRaceCheckpoint ALS_DO_PlayerEnterRaceCheckpoint<ALS_D_INT>
#define CALL@OnPlayerLeaveRaceCheckpoint ALS_DO_PlayerLeaveRaceCheckpoint<ALS_D_INT>
#define CALL@OnRconCommand ALS_DO_RconCommand<ALS_D_INT>
#define CALL@OnPlayerRequestSpawn ALS_DO_PlayerRequestSpawn<ALS_D_INT>
#define CALL@OnObjectMoved ALS_DO_ObjectMoved<ALS_D_INT>
#define CALL@OnPlayerObjectMoved ALS_DO_PlayerObjectMoved<ALS_D_INT>
#define CALL@OnPlayerPickUpPickup ALS_DO_PlayerPickUpPickup<ALS_D_INT>
#define CALL@OnVehicleMod ALS_DO_VehicleMod<ALS_D_INT>
#define CALL@OnEnterExitModShop ALS_DO_EnterExitModShop<ALS_D_INT>
#define CALL@OnVehiclePaintjob ALS_DO_VehiclePaintjob<ALS_D_INT>
#define CALL@OnVehicleRespray ALS_DO_VehicleRespray<ALS_D_INT>
#define CALL@OnVehicleDamageStatusUpdate ALS_DO_VehicleDamageStatusUpdate<ALS_D_INT>
#define CALL@OnPlayerSelectedMenuRow ALS_DO_PlayerSelectedMenuRow<ALS_D_INT>
#define CALL@OnPlayerExitedMenu ALS_DO_PlayerExitedMenu<ALS_D_INT>
#define CALL@OnPlayerInteriorChange ALS_DO_PlayerInteriorChange<ALS_D_INT>
#define CALL@OnPlayerKeyStateChange ALS_DO_PlayerKeyStateChange<ALS_D_INT>
#define CALL@OnRconLoginAttempt ALS_DO_RconLoginAttempt<ALS_D_INT>
#define CALL@OnPlayerUpdate ALS_DO_PlayerUpdate<ALS_D_INT>
#define CALL@OnPlayerStreamIn ALS_DO_PlayerStreamIn<ALS_D_INT>
#define CALL@OnPlayerStreamOut ALS_DO_PlayerStreamOut<ALS_D_INT>
#define CALL@OnVehicleStreamIn ALS_DO_VehicleStreamIn<ALS_D_INT>
#define CALL@OnVehicleStreamOut ALS_DO_VehicleStreamOut<ALS_D_INT>
#define CALL@OnDialogResponse ALS_DO_DialogResponse<ALS_D_INT>
#define CALL@OnPlayerClickPlayer ALS_DO_PlayerClickPlayer<ALS_D_INT>
#define CALL@OnPlayerLogin ALS_DO_PlayerLogin<ALS_D_INT>
#define CALL@OnPlayerLogout ALS_DO_PlayerLogout<ALS_D_INT>
#define CALL@OnPlayerTakeDamage ALS_DO_PlayerTakeDamage<ALS_D_INT>
#define CALL@OnPlayerGiveDamage ALS_DO_PlayerGiveDamage<ALS_D_INT>
#define CALL@OnPlayerClickMap ALS_DO_PlayerClickMap<ALS_D_INT>
#define CALL@OnPlayerCommandReceived ALS_DO_PlayerCommandReceived<ALS_D_INT>
#define CALL@OnPlayerCommandPerformed ALS_DO_PlayerCommandPerformed<ALS_D_INT>
#define CALL@OnUnoccupiedVehicleUpdate ALS_DO_UnoccupiedVehicleUpdate<ALS_D_INT>
// 0.3e
#define CALL@OnPlayerClickTextDraw ALS_DO_PlayerClickTextDraw<ALS_D_INT>
#define CALL@OnPlayerClickPlayerTextDraw ALS_DO_PlayerClickPlayerTextDraw<ALS_D_INT>
#define CALL@OnPlayerEditObject ALS_DO_PlayerEditObject<ALS_D_INT>
#define CALL@OnPlayerEditAttachedObject ALS_DO_PlayerEditAttachedObject<ALS_D_INT>
#define CALL@OnPlayerSelectObject ALS_DO_PlayerSelectObject<ALS_D_INT>
// YSI
#define CALL@OnPlayerEnterArea ALS_DO_PlayerEnterArea<ALS_D_INT>
#define CALL@OnPlayerLeaveArea ALS_DO_PlayerLeaveArea<ALS_D_INT>
#define CALL@OnPlayerFinishRace ALS_DO_PlayerFinishRace<ALS_D_INT>
#define CALL@OnPlayerExitRace ALS_DO_PlayerExitRace<ALS_D_INT>
#define CALL@OnRaceEnd ALS_DO_RaceEnd<ALS_D_INT>
#define CALL@OnMasterSystemClose ALS_DO_MasterSystemClose<ALS_D_INT>
// Streamer plugins.
#define CALL@OnDynamicObjectMoved ALS_DO_DynamicObjectMoved<ALS_D_INT>
#define CALL@OnPlayerEditDynamicObject ALS_DO_PlayerEditDynamicObject<ALS_D_INT>
#define CALL@OnPlayerSelectDynamicObject ALS_DO_PlayerSelectDynamicObject<ALS_D_INT>
#define CALL@OnPlayerPickUpDynamicPickup ALS_DO_PlayerPickUpDynamicPickup<ALS_D_INT>
#define CALL@OnPlayerEnterDynamicCP ALS_DO_PlayerEnterDynamicCP<ALS_D_INT>
#define CALL@OnPlayerLeaveDynamicCP ALS_DO_PlayerLeaveDynamicCP<ALS_D_INT>
#define CALL@OnPlayerEnterDynamicRaceCP ALS_DO_PlayerEnterDynamicRaceCP<ALS_D_INT>
#define CALL@OnPlayerLeaveDynamicRaceCP ALS_DO_PlayerLeaveDynamicRaceCP<ALS_D_INT>
#define CALL@OnPlayerEnterDynamicArea ALS_DO_PlayerEnterDynamicArea<ALS_D_INT>
#define CALL@OnPlayerLeaveDynamicArea ALS_DO_PlayerLeaveDynamicArea<ALS_D_INT>
// Alternates
#define CALL@OnPlayerLeaveRaceCP ALS_DO_PlayerLeaveRaceCP<ALS_D_INT>
#define CALL@OnPlayerEnterRaceCP ALS_DO_PlayerEnterRaceCP<ALS_D_INT>
#define CALL@OnVehicleDamageStatusUpd ALS_DO_VehicleDamageStatusUpd<ALS_D_INT>
#define CALL@OnUnoccupiedVehicleUpd ALS_DO_UnoccupiedVehicleUpd<ALS_D_INT>
#define CALL@OnPlayerClickPlayerTD ALS_DO_PlayerClickPlayerTD<ALS_D_INT>
#define CALL@OnPlayerEditAttachedObj ALS_DO_PlayerEditAttachedObj<ALS_D_INT>
#define CALL@OnPlayerCmdPerformed ALS_DO_PlayerCmdPerformed<ALS_D_INT>
#define CALL@OnPlayerEditDynObject ALS_DO_PlayerEditDynObject<ALS_D_INT>
#define CALL@OnPlayerSelectDynObject ALS_DO_PlayerSelectDynObject<ALS_D_INT>
#define CALL@OnPlayerPickUpDynPickup ALS_DO_PlayerPickUpDynPickup<ALS_D_INT>
#define CALL@OnPlayerEnterDynRaceCP ALS_DO_PlayerEnterDynRaceCP<ALS_D_INT>
#define CALL@OnPlayerLeaveDynRaceCP ALS_DO_PlayerLeaveDynRaceCP<ALS_D_INT>
#define CALL@OnPlayerEnterDynArea ALS_DO_PlayerEnterDynArea<ALS_D_INT>
#define CALL@OnPlayerLeaveDynArea ALS_DO_PlayerLeaveDynArea<ALS_D_INT>
// Added 05/07/17
#define CALL@OnPlayerWeaponShot ALS_DO_PlayerWeaponShot<ALS_D_INT>
#define CALL@OnIncomingConnection ALS_DO_IncomingConnection<ALS_D_INT>
#define CALL@OnTrailerUpdate ALS_DO_TrailerUpdate<ALS_D_INT>
#define CALL@OnVehicleSirenStateChange ALS_DO_VehicleSirenStateChange<ALS_D_INT>
#define CALL@OnPlayerGiveDamageActor ALS_DO_PlayerGiveDamageActor<ALS_D_INT>
#define CALL@OnActorStreamIn ALS_DO_ActorStreamIn<ALS_D_INT>
#define CALL@OnActorStreamOut ALS_DO_ActorStreamOut<ALS_D_INT>

