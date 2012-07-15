/*----------------------------------------------------------------------------*\
					 ============================
					  y_mouse - On-screen mouse.
					 ============================
Description:
	Makes a mouse cursor on the screen.
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
	
	The Original Code is the YSI vararg include.
	
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
	02/05/11:
		First version.
Functions:
	Public:
		-
	Core:
		-
	Stock:
		-
	Static:
		-
	Inline:
		-
	API:
		-
Callbacks:
	-
Definitions:
	-
Enums:
	-
Macros:
	-
Tags:
	-
Variables:
	Global:
		-
	Static:
		-
Commands:
	-
Compile options:
	-
Operators:
	-
\*----------------------------------------------------------------------------*/

#include "internal\y_version"
#include "y_hooks"

enum E_MOUSE_PLAYER_RESTORE
{
	Float:E_MOUSE_PLAYER_RESTORE_X,
	Float:E_MOUSE_PLAYER_RESTORE_Y,
	Float:E_MOUSE_PLAYER_RESTORE_Z,
	Float:E_MOUSE_PLAYER_RESTORE_A,
	E_MOUSE_PLAYER_RESTORE_INT,
	E_MOUSE_PLAYER_RESTORE_VW
}

static stock
	Text:YSI_g_sCursor[MAX_PLAYERS] = {Text:-1, ...},
	YSI_g_sMouseData[MAX_PLAYERS],
	Float:YSI_g_sMousePos[MAX_PLAYERS][2],
	YSI_g_sRestore[MAX_PLAYERS][E_MOUSE_PLAYER_RESTORE],
	YSI_g_sCameraVehicle;

stock Mouse_Move(playerid, Float:dx, Float:dy)
{
	Mouse_SetPos(playerid, YSI_g_sMousePos[playerid][0] + dx, YSI_g_sMousePos[playerid][1] + dy);
}

stock Mouse_SetPos(playerid, Float:x, Float:y)
{
	if (x > 640.0) x = 640.0;
	else if (x < 0.0) x = 0.0;
	if (y > 480.0) y = 480.0;
	else if (y < 0.0) y = 0.0;
	if (YSI_g_sMousePos[playerid][0] != x)
	{
		YSI_g_sMousePos[playerid][0] = x;
		YSI_g_sMousePos[playerid][1] = y;
	}
	else if (YSI_g_sMousePos[playerid][1] != y)
	{
		YSI_g_sMousePos[playerid][1] = y;
	}
	else
	{
		return;
	}
    if (YSI_g_sCursor[playerid] != Text:-1)
	{
		TextDrawDestroy(YSI_g_sCursor[playerid]);
	}
    new
        Text:t = TextDrawCreate(x, y, "\\");
    YSI_g_sCursor[playerid] = t;
    TextDrawFont(t, 0);
    TextDrawLetterSize(t, 5.0, 5.0);
    TextDrawColor(t, 0xFF0000AA);
    TextDrawShowForPlayer(playerid, t);
}

stock Mouse_GetPos(playerid, &Float:x, &Float:y)
{
	x = YSI_g_sMousePos[playerid][0];
	y = YSI_g_sMousePos[playerid][1];
}

stock Mouse_Enable(playerid)
{
	// Save settings.
	GetPlayerPos(playerid, YSI_g_sRestore[playerid][E_MOUSE_PLAYER_RESTORE_X], YSI_g_sRestore[playerid][E_MOUSE_PLAYER_RESTORE_Y], YSI_g_sRestore[playerid][E_MOUSE_PLAYER_RESTORE_Z]);
	GetPlayerFacingAngle(playerid, YSI_g_sRestore[playerid][E_MOUSE_PLAYER_RESTORE_A]);
	YSI_g_sRestore[playerid][E_MOUSE_PLAYER_RESTORE_INT] = GetPlayerInterior(playerid);
	YSI_g_sRestore[playerid][E_MOUSE_PLAYER_RESTORE_VW] = GetPlayerVirtualWorld(playerid);
	// May put the player in a vehicle in an interior, but on the ground so they
	// can't see anything, then change the VW of the vehicle so they can't even
	// see themselves (and while I'm at it, desync them).
	SetVehiclePos(YSI_g_sCameraVehicle, -4000.0, -4000.0, 10.0);
	SetPlayerPos(playerid, -6000.0, -6000.0, -6000.0);
	//SetPlayerFacingAngle(playerid, 0.0);
	//SetCameraBehindPlayer(playerid);
	// "Extreme" start delay.
	YSI_g_sMouseData[playerid] = 0x1000000F;
//	LinkVehicleToInterior(YSI_g_sCameraVehicle, 1);
//	SetPlayerInterior(playerid, 1);
	// These are NOT the same world to hide the vehicle.
//	SetVehicleVirtualWorld(YSI_g_sCameraVehicle, 0xA137C013);
//	SetPlayerVirtualWorld(playerid, 0xA137C014);
	// Everyone gets put in the same vehicle.
	PutPlayerInVehicle(playerid, YSI_g_sCameraVehicle, 0);
	Mouse_SetPos(playerid, 320.0, 240.0);
//	SetPlayerHealth(playerid, FLOAT_INFINITY);
//	SetVehicleVirtualWorld(YSI_g_sCameraVehicle, 0xA137C013);
//	SetPlayerVirtualWorld(playerid, 0xA137C014);
}

hook OnPlayerConnect(playerid)
{
	YSI_g_sMouseData[playerid] = 0;
}

stock Mouse_Disable(playerid)
{
	RemovePlayerFromVehicle(playerid);
	SetPlayerPos(playerid, YSI_g_sRestore[playerid][E_MOUSE_PLAYER_RESTORE_X], YSI_g_sRestore[playerid][E_MOUSE_PLAYER_RESTORE_Y], YSI_g_sRestore[playerid][E_MOUSE_PLAYER_RESTORE_Z]);
	SetPlayerFacingAngle(playerid, YSI_g_sRestore[playerid][E_MOUSE_PLAYER_RESTORE_A]);
	SetPlayerInterior(playerid, YSI_g_sRestore[playerid][E_MOUSE_PLAYER_RESTORE_INT]);
	SetPlayerVirtualWorld(playerid, YSI_g_sRestore[playerid][E_MOUSE_PLAYER_RESTORE_VW]);
	SetCameraBehindPlayer(playerid);
	YSI_g_sMouseData[playerid] = 0;
}

hook OnScriptInit()
{
	YSI_g_sCameraVehicle = CreateVehicle(564, -4000.0, -4000.0, 10.0, 0.0, 0, 0, -1);
}

hook OnPlayerUpdate99(playerid)
{
	// I have no idea why, but this combination of parameters seems to trigger
	// the fast updates to work fully.  No idea why (it does seem to be ONLY
	// this combination, which makes it frankly amazing that I found it).
	if (YSI_g_sMouseData[playerid])
	{
		static
			Float:sLastVector[MAX_PLAYERS][3];
		if (++YSI_g_sMouseData[playerid] == 0x10000010) //0x10000002) //
		{
//			SetPlayerInterior(playerid, 1);
//			PutPlayerInVehicle(playerid, YSI_g_sCameraVehicle, 0);
			// These are NOT the same world to hide the vehicle.
			//SetVehicleVirtualWorld(YSI_g_sCameraVehicle, 0xA137C013);
			//SetPlayerVirtualWorld(playerid, 0xA137C014);
			// Reset.
			SetVehiclePos(YSI_g_sCameraVehicle, -4000.0, -4000.0, 10.0);
			SetVehicleZAngle(YSI_g_sCameraVehicle, 0.0);
//			SetPlayerFacingAngle(playerid, 0.0);
//			SetPlayerCameraPos(playerid, 1946.195800, 1302.83012, 80.509375);
			YSI_g_sMouseData[playerid] = 0x10000000;
			SetCameraBehindPlayer(playerid);
			//SetVehicleVelocity(YSI_g_sCameraVehicle, 0.0, 0.2, 0.1);
		}
		//else
		//{
		SetVehicleVelocity(YSI_g_sCameraVehicle, 0.0, 0.2, 0.0);
		//}
		//if (YSI_g_sMouseData[playerid] & 1)
		//{
		//	SetCameraBehindPlayer(playerid);
		//}
		new
			Float:x,
			Float:y,
			Float:z;
		GetPlayerCameraFrontVector(playerid, x, y, z);
		/*if (y >= 0)
		{
			y = -0.01;
		}*/
		//z += 0.098737;
		// Invert.
		//y = 1.0 / y;
		// Invert and project to a large screen!
		//x /= y * -10.0;
		/*if (!(-0.001 < x < 0.001))
		{
			//x /= -y; // * -8.0;
		}
		else
		{
			//z = 0.0;
		}
		if (!(-0.001 < z < 0.001))
		{
			//z /= y; // * 8.0;
		}
		else
		{
			//z = 0.0;
		}*/
		/*if (x < -0.02) x = -30.0;
		else if (x > 0.02) x = 30.0;
		else x = 0;
		
		if (y < -0.16) y = -30.0;
		else if (y > -0.12) y = 30.0;
		else y = 0.0;
		// Update.*/
		printf("%f %f %f",
			sLastVector[playerid][0] - x,
			sLastVector[playerid][1] - y,
			sLastVector[playerid][2] - z);
		sLastVector[playerid][0] = x;
		sLastVector[playerid][1] = y;
		sLastVector[playerid][2] = z;
		//Mouse_Move(playerid, x, z);
		//printf("TO:  %f %f %f", x, y, z);
		//GetPlayerCameraPos(playerid, x, y, z);
		//printf("POS: %f %f %f", x, y, z);
		return 0;
	}
	// Do not sync anyone as in this vehicle ever!
	return GetPlayerVehicleID(playerid) != YSI_g_sCameraVehicle;
}
