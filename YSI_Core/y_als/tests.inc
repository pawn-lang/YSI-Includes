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
	Portions created by the Initial Developer are Copyright C 2011
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

#if !defined ALS_MAKE
	#define ALS_MAKE<%0...%1> %0__T_%1
	#define __ALS_MAKE_DEFINED
#endif

static stock y_als_Print(result[], fmat[], va_args<>)
{
	// This function formats the incoming data and compares it to the reference.
	static
		msg[256];
	//printf("ONE: %d", numargs());
	// printf("\"%s\" \"%s\"", result, fmat);
	//printf("%s", result);
	//printf("%s", fmat);
	//printf("%s", msg);
	// msg[0] = '\0';
	// format(msg, sizeof (msg), fmat, 0);
	va_format(msg, sizeof (msg), fmat, va_start<2>);
	//printf("TWO");
	//printf("%s", msg);
	new
		bool:cmp = !strcmp(result, msg);
	//va_format(msg, sizeof (msg), fmat, va_start<2>);
	//printf("%s", msg);
	//printf("%s %s", result, fmat);
	format(msg, sizeof (msg), "\"%s\" != \"%s\" (%d)", result, msg, cmp);
	Testing_Test(cmp, msg);
	//printf("THREE");
	//printf("%s", msg);
}

// Defines for our "__PRINT" macro, see:
// http://ysi.wikia.com/wiki/Library:YSI\y_als
#define __ALS_PS_more:%0,         "%d, "__ALS_PS_
#define __ALS_PS_string:%0[],     "%s, "__ALS_PS_
#define __ALS_PS_Float:%0,        "%f, "__ALS_PS_
#define __ALS_PS_tag:%3:%0,       "%d, "__ALS_PS_
#define __ALS_PS_end:%0)          "%d"
#define __ALS_PS_none:%0)
#define __ALS_PS_end_string:%0[]) "%s"
#define __ALS_PS_end_Float:%0)    "%f"
#define __ALS_PS_end_tag:%3:%0)   "%d"

#define __ALS_R2_more:%0,         ,%0 __ALS_R2_
#define __ALS_R2_string:%0[],     ,((%0[0])?(%0):NULL) __ALS_R2_
#define __ALS_R2_Float:%0,        ,(_:%0) __ALS_R2_
#define __ALS_R2_tag:%3:%0,       ,(_:%0) __ALS_R2_
#define __ALS_R2_end:%0)          ,%0)
#define __ALS_R2_none:)           )
#define __ALS_R2_end_string:%0[]) ,((%0[0])?(%0):NULL))
#define __ALS_R2_end_Float:%0)    ,(_:%0))
#define __ALS_R2_end_tag:%3:%0)   ,(_:%0))

#define __DO_PRINT(%9)<%0,%1>(%2) y_als_Print(%9,"On"#%0"("__ALS_PS_%2)")"__ALS_R2_%2);

#define __PRINT<%0,%9> ALS_DO:__DO_PRINT(%9)<%0>

// Set up a fake callback to test.
#define ALS_R_FakeCallback 708
#define ALS_DO_FakeCallback<%0> %0<FakeCallback,isfi>(more:playerid,string:text[],Float:pos,end:last)

Test:y_als_Fake()
{
	// Test that the defines for our fake callback are set up correctly (and the
	// print macro at the same time).
	new
		playerid = 709,
		text[] = "T_E_X_T_",
		Float:pos = 710.017,
		last = 711;
	// Floats don't print quite exactly.
	__PRINT<FakeCallback, "OnFakeCallback(709, T_E_X_T_, 710.017028, 711)">
}

static stock y_als_DoCall(playerid, text[], Float:pos, last)
{
	ALS_CALL<FakeCallback>
}

Test:y_als_Call()
{
	// Test the "ALS_CALL" macro.
	ASSERT(y_als_DoCall(6000, "", 0.0, 0) == 6000);
}

static stock y_als_DoGet(playerid, text[], Float:pos, last)
{
	new
		ret = ALS_GET<FakeCallback>
	ASSERT(ret == playerid);
	//return ret;
}

Test:y_als_Get()
{
	// Test the "ALS_GET" macro.
	y_als_DoGet(6003, "", 0.0, 0);
}

// The original version.
forward OnFakeCallback(playerid, text[], Float:pos, last);
public OnFakeCallback(playerid, text[], Float:pos, last)
{
	return last;
}

// Forward our callback.
ALS_FORWARD<FakeCallback>
#define OnFakeCallback ALS_MAKE<..._OnFakeCallback>

public OnFakeCallback(playerid, text[], Float:pos, last)
{
	return playerid;
}

Test:y_als_call()
{
	// Test that "call" calls the original one, not the latest one.
	new
		ret;
	ret = call OnFakeCallback(6010, NULL, 0.0, 6011);
	ASSERT(ret == 6011);
}

Test:y_als_Generation()
{
	// Test all default callbacks.
	new
		playerid = 42;
	__PRINT<ScriptInit, "OnScriptInit()">
	__PRINT<ScriptExit, "OnScriptExit()">
	__PRINT<GameModeInit, "OnGameModeInit()">
	__PRINT<GameModeExit, "OnGameModeExit()">
	__PRINT<FilterScriptInit, "OnFilterScriptInit()">
	__PRINT<FilterScriptExit, "OnFilterScriptExit()">
	__PRINT<PlayerConnect, "OnPlayerConnect(42)">
	new
		reason = 11;
	__PRINT<PlayerDisconnect, "OnPlayerDisconnect(42, 11)">
	__PRINT<PlayerSpawn, "OnPlayerSpawn(42)">
	new
		killerid = INVALID_PLAYER_ID;
	ASSERT(INVALID_PLAYER_ID == 65535);
	__PRINT<PlayerDeath, "OnPlayerDeath(42, 65535, 11)">
	new
		vehicleid = 606;
	__PRINT<VehicleSpawn, "OnVehicleSpawn(606)">
	__PRINT<VehicleDeath, "OnVehicleDeath(606, 65535)">
	new
		text[] = "Hello There!";
	__PRINT<PlayerText, "OnPlayerText(42, Hello There!)">
	new
		cmdtext[] = "/help";
	__PRINT<PlayerCommandText, "OnPlayerCommandText(42, /help)">
	new
		classid = 101;
	__PRINT<PlayerRequestClass, "OnPlayerRequestClass(42, 101)">
	new
		ispassenger = 99;
	__PRINT<PlayerEnterVehicle, "OnPlayerEnterVehicle(42, 606, 99)">
	__PRINT<PlayerExitVehicle, "OnPlayerExitVehicle(42, 606)">
	new
		newstate = 1,
		oldstate = 3;
	__PRINT<PlayerStateChange, "OnPlayerStateChange(42, 1, 3)">
	__PRINT<PlayerEnterCheckpoint, "OnPlayerEnterCheckpoint(42)">
	__PRINT<PlayerLeaveCheckpoint, "OnPlayerLeaveCheckpoint(42)">
	__PRINT<PlayerEnterRaceCheckpoint, "OnPlayerEnterRaceCheckpoint(42)">
	__PRINT<PlayerLeaveRaceCheckpoint, "OnPlayerLeaveRaceCheckpoint(42)">
	new
		cmd[] = "changemode lvdm";
	__PRINT<RconCommand, "OnRconCommand(changemode lvdm)">
	__PRINT<PlayerRequestSpawn, "OnPlayerRequestSpawn(42)">
	new
		objectid = 1234;
	__PRINT<ObjectMoved, "OnObjectMoved(1234)">
	__PRINT<PlayerObjectMoved, "OnPlayerObjectMoved(42, 1234)">
	new
		pickupid = 4321;
	__PRINT<PlayerPickUpPickup, "OnPlayerPickUpPickup(42, 4321)">
	new
		componentid = 77;
	__PRINT<VehicleMod, "OnVehicleMod(42, 606, 77)">
	new
		enterexit = 0,
		interiorid = 10;
	__PRINT<EnterExitModShop, "OnEnterExitModShop(42, 0, 10)">
	new
		paintjobid = 654;
	__PRINT<VehiclePaintjob, "OnVehiclePaintjob(42, 606, 654)">
	new
		color1 = 421,
		color2 = 422;
	__PRINT<VehicleRespray, "OnVehicleRespray(42, 606, 421, 422)">
	__PRINT<VehicleDamageStatusUpdate, "OnVehicleDamageStatusUpdate(606, 42)">
	new
		row = 12;
	__PRINT<PlayerSelectedMenuRow, "OnPlayerSelectedMenuRow(42, 12)">
	__PRINT<PlayerExitedMenu, "OnPlayerExitedMenu(42)">
	new
		newinteriorid = 88,
		oldinteriorid = 89;
	__PRINT<PlayerInteriorChange, "OnPlayerInteriorChange(42, 88, 89)">
	new
		newkeys = 4,
		oldkeys = 5;
	__PRINT<PlayerKeyStateChange, "OnPlayerKeyStateChange(42, 4, 5)">
	new
		ip[] = "IP HERE",
		password[] = "PASS HERE",
		success = -11;
	__PRINT<RconLoginAttempt, "OnRconLoginAttempt(IP HERE, PASS HERE, -11)">
	__PRINT<PlayerUpdate, "OnPlayerUpdate(42)">
	new
		forplayerid = 43;
	__PRINT<PlayerStreamIn, "OnPlayerStreamIn(42, 43)">
	__PRINT<PlayerStreamOut, "OnPlayerStreamOut(42, 43)">
	__PRINT<VehicleStreamIn, "OnVehicleStreamIn(606, 43)">
	__PRINT<VehicleStreamOut, "OnVehicleStreamOut(606, 43)">
	new
		dialogid = 500,
		response = 404,
		listitem = 200,
		inputtext[] = "SOME TEXT";
	__PRINT<DialogResponse, "OnDialogResponse(42, 500, 404, 200, SOME TEXT)">
	new
		clickedplayerid = 44,
		source = -20;
	__PRINT<PlayerClickPlayer, "OnPlayerClickPlayer(42, 44, -20)">
	new
		uid = 4242;
	__PRINT<PlayerLogin, "OnPlayerLogin(42, 4242)">
	__PRINT<PlayerLogout, "OnPlayerLogout(42, 4242)">
	new
		damagedid = 45,
		Float:amount = 1.2,
		weaponid = 50,
		bodypart = 2;
	#if defined GetPlayerLastShotVectors
		__PRINT<PlayerGiveDamage, "OnPlayerGiveDamage(42, 45, 1.200000, 50, 2)">
	#else
		__PRINT<PlayerGiveDamage, "OnPlayerGiveDamage(42, 45, 1.200000, 50)">
		#pragma unused bodypart
	#endif
	new
		issuerid = 46;
	#if defined GetPlayerLastShotVectors
		__PRINT<PlayerTakeDamage, "OnPlayerTakeDamage(42, 46, 1.200000, 50, 2)">
	#else
		__PRINT<PlayerTakeDamage, "OnPlayerTakeDamage(42, 46, 1.200000, 50)">
		#pragma unused bodypart
	#endif
	new
		Float:fX = 10.24,
		Float:fY = 11.34,
		Float:fZ = 12.44;
	__PRINT<PlayerClickMap, "OnPlayerClickMap(42, 10.239999, 11.340000, 12.439999)">
	__PRINT<PlayerCommandReceived, "OnPlayerCommandReceived(42, /help)">
	__PRINT<PlayerCommandPerformed, "OnPlayerCommandPerformed(42, /help, -11)">
	new
		passenger_seat = 70,
		Float:new_x = 3.3,
		Float:new_y = 4.4,
		Float:new_z = 5.5;
	#if defined GetServerTickRate
		__PRINT<UnoccupiedVehicleUpdate, "OnUnoccupiedVehicleUpdate(606, 42, 70, 3.299999, 4.400000, 5.500000)">
	#else
		__PRINT<UnoccupiedVehicleUpdate, "OnUnoccupiedVehicleUpdate(606, 42, 70)">
		#pragma unused new_x, new_y, new_z
	#endif
	new
		clickedid = 90;
	// Actually revealed an issue in y_als with ALL tags being interpreted as
	// floats instead of just tagged integers.
	__PRINT<PlayerClickTextDraw, "OnPlayerClickTextDraw(42, 90)">
	new
		playertextid = 92;
	__PRINT<PlayerClickPlayerTextDraw, "OnPlayerClickPlayerTextDraw(42, 92)">
	new
		playerobject = 2234,
		Float:fRotX = 20.24,
		Float:fRotY = 21.34,
		Float:fRotZ = 22.44;
	__PRINT<PlayerEditObject, "OnPlayerEditObject(42, 2234, 1234, 404, 10.239999, 11.340000, 12.439999, 20.239999, 21.340000, 22.440000)">
	#if 0
		// This ends up too long to compile :(.
		new
			index = 650,
			modelid = 651,
			boneid = 652,
			Float:fOffsetX = 101.01,
			Float:fOffsetY = 202.02,
			Float:fOffsetZ = 303.03,
			Float:fScaleX = 404.04,
			Float:fScaleY = 505.05,
			Float:fScaleZ = 606.06;
		__PRINT<PlayerEditAttachedObject, "OnPlayerEditAttachedObject(42, 404, 650, 651, 652, 20.240000, 21.340000, 22.440000, 101.010000, 202.020000, 303.030000, 404.040000, 505.050000, 606.060000)">
	#endif
}

#undef __ALS_PS_more
#undef __ALS_PS_string
#undef __ALS_PS_tag
#undef __ALS_PS_end
#undef __ALS_PS_none
#undef __ALS_PS_end_string
#undef __ALS_PS_end_tag

#undef __ALS_R2_more
#undef __ALS_R2_string
#undef __ALS_R2_tag
#undef __ALS_R2_end
#undef __ALS_R2_none
#undef __ALS_R2_end_string
#undef __ALS_R2_end_tag

#undef __DO_PRINT

#undef __PRINT

#if defined __ALS_MAKE_DEFINED
	#undef ALS_MAKE
	#undef __ALS_MAKE_DEFINED
#endif

#undef ALS_R_FakeCallback
#undef ALS_DO_FakeCallback

#undef OnFakeCallback
