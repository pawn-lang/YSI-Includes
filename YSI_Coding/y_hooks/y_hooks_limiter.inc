/*
 * YSI Hooking System Limiter
 * ==========================
 *
 * - This include stabilizes
 *   y_hooks callback hooking
 *   system by adding errors and warnings
 *   to it (more information).
 *
 * - Made by: DEntisT Brace
 *
 * - Version: 1.0
 *
 */

#if defined INC_y_hooks_limiter
 	#endinput
 #endif

#define INC_y_hooks_limiter

/*

#if defined @yH_ CALLBACK@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: CALLBACK
#endif

*/

// Code:

#if defined @yH_OnGameModeInit@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnGameModeInit()
#endif
#if defined @yH_OnGameModeExit@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnGameModeExit()
#endif
#if defined @yH_OnFilterScriptInit@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnFilterScriptInit()
#endif
#if defined @yH_OnFilterScriptExit@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnFilterScriptExit()
#endif
#if defined @yH_OnPlayerConnect@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerConnect(playerid)
#endif
#if defined @yH_OnPlayerDisconnect@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerDisconnect(playerid, reason)
#endif
#if defined @yH_OnPlayerSpawn@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerSpawn(playerid)
#endif
#if defined @yH_OnPlayerDeath@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerDeath(playerid)
#endif
#if defined @yH_OnVehicleSpawn@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnVehicleSpawn(vehicleid)
#endif
#if defined @yH_OnVehicleDeath@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnVehicleDeath(vehicleid, killerid)
#endif
#if defined @yH_OnPlayerText@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerText(playerid, text[])
#endif
#if defined @yH_OnPlayerCommandText@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerCommandText(playerid, cmdtext[])
#endif
#if defined @yH_OnPlayerRequestClass@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerRequestClass(playerid, classid)
#endif
#if defined @yH_OnPlayerEnterVehicle@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
#endif
#if defined @yH_OnPlayerExitVehicle@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerExitVehicle(playerid, vehicleid)
#endif
#if defined @yH_OnPlayerStateChange@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerStateChange(playerid, newstate, oldstate)
#endif
#if defined @yH_OnPlayerEnterCheckpoint@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerEnterCheckpoint(playerid)
#endif
#if defined @yH_OnPlayerLeaveCheckpoint@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerLeaveCheckpoint(playerid)
#endif
#if defined @yH_OnPlayerEnterRaceCheckpoint@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerEnterRaceCheckpoint(playerid)
#endif
#if defined @yH_OnPlayerLeaveRaceCheckpoint@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerLeaveRaceCheckpoint(playerid)
#endif
#if defined @yH_OnRconCommand@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnRconCommand(cmd[])
#endif
#if defined @yH_OnPlayerRequestSpawn@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerRequestSpawn(playerid)
#endif
#if defined @yH_OnObjectMoved@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnObjectMoved(objectid)
#endif
#if defined @yH_OnPlayerObjectMoved@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerObjectMoved(playerid, objectid)
#endif
#if defined @yH_OnPlayerPickUpPickup@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerPickUpPickup(playerid, pickupid)
#endif
#if defined @yH_OnVehicleMod@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnVehicleMod(playerid, vehicleid, componentid)
#endif
#if defined @yH_OnEnterExitModShop@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnEnterExitModShop(playerid, enterexit, interiorid)
#endif
#if defined @yH_OnVehiclePaintjob@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnVehiclePaintjob(playerid, vehicleid, paintjobid)
#endif
#if defined @yH_OnVehicleRespray@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnVehicleRespray(playerid, vehicleid, color1, color2)
#endif
#if defined @yH_OnVehicleDamageStatusUpdate@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnVehicleDamageStatusUpdate(vehicleid, playerid)
#endif
#if defined @yH_OnUnoccupiedVehicleUpdate@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
#endif
#if defined @yH_OnPlayerSelectedMenuRow@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerSelectedMenuRow(playerid, row)
#endif
#if defined @yH_OnPlayerExitedMenu@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerExitedMenu(playerid)
#endif
#if defined @yH_OnPlayerInteriorChange@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
#endif
#if defined @yH_OnPlayerKeyStateChange@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
#endif
#if defined @yH_OnRconLoginAttempt@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnRconLoginAttempt(ip[], password[], success)
#endif
#if defined @yH_OnPlayerUpdate@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerUpdate(playerid)
#endif
#if defined @yH_OnPlayerStreamIn@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerStreamIn(playerid, forplayerid)
#endif
#if defined @yH_OnPlayerStreamOut@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerStreamOut(playerid, forplayerid)
#endif
#if defined @yH_OnVehicleStreamIn@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnVehicleStreamIn(vehicleid, forplayerid)
#endif
#if defined @yH_OnVehicleStreamOut@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnVehicleStreamOut(vehicleid, forplayerid)
#endif
#if defined @yH_OnActorStreamIn@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnActorStreamIn(actorid, forplayerid)
#endif
#if defined @yH_OnActorStreamOut@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnActorStreamOut(actorid, forplayerid)
#endif
#if defined @yH_OnDialogResponse@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
#endif
#if defined @yH_OnPlayerTakeDamage@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
#endif
#if defined @yH_OnPlayerGiveDamage@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
#endif
#if defined @yH_OnPlayerGiveDamageActor@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerGiveDamageActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart)
#endif
#if defined @yH_OnPlayerClickMap@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
#endif
#if defined @yH_OnPlayerClickTextDraw@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerClickTextDraw(playerid, Text:clickedid)
#endif
#if defined @yH_OnPlayerClickPlayerTextDraw@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
#endif
#if defined @yH_OnIncomingConnection@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnIncomingConnection(playerid, ip_address[], port)
#endif
#if defined @yH_OnTrailerUpdate@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnTrailerUpdate(playerid, vehicleid)
#endif
#if defined @yH_OnVehicleSirenStateChange@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnVehicleSirenStateChange(playerid, vehicleid, newstate)
#endif
#if defined @yH_OnPlayerClickPlayer@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerClickPlayer(playerid, clickedplayerid, source)
#endif
#if defined @yH_OnPlayerEditObject@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerEditObject(playerid, ...)
 	//(playerid, playerobject, objectid, response, Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ )
#endif
#if defined @yH_OnPlayerEditAttachedObject@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerEditAttachedObject(playerid, ...)
//(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ )
#endif
#if defined @yH_OnPlayerSelectObject@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerSelectObject(playerid, type, objectid, modelid, Float:fX, Float:fY, Float:fZ)
#endif
#if defined @yH_OnPlayerWeaponShot@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
#endif

// Code left for upcoming new callbacks:

/*

#if defined @yH_@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: CALLBACK
#endif
#if defined @yH_@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: CALLBACK
#endif
#if defined @yH_@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: CALLBACK
#endif
#if defined @yH_@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: CALLBACK
#endif
#if defined @yH_@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: CALLBACK
#endif
#if defined @yH_@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: CALLBACK
#endif
#if defined @yH_@999
 	#error YSI - fatal error: Callback's maximum hook id reached. Callback: CALLBACK
#endif

*/