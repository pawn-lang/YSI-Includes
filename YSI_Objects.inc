/*----------------------------------------------------------------------------*-
					==================================
					Y Sever Includes - Objects Include
					==================================
Description:
	Stand alone wrapper for YSI_objects.own.  Provides wrappers for required
	functions.
Legal:
	Copyright (C) 2007 Alex "Y_Less" Cole

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
	MA 02110-1301, USA.
Version:
	0.1
Changelog:
	20/11/07:
		First version - adapted from my earlier e_objects.inc include.
Functions:
	Public:
		-
	Core:
		-
	Stock:
		Bit_Set - Sets a specified bit to a given value.
		Bit_SetAll - Sets all of a bit array to a single value.
	Static:
		-
	Inline:
		Timer_Add - Wrapper for SetTimer.
		ceildiv - Divides an interger and rounds up.
		foreach - Wrapper for for() and IsPlayerConnected().
		Bit_Bits - Number of cells required for the given number of bits.
		Bit_GetBit - Gets a specified bit.
		Bit_Get - Wrapper for Bit_GetBit.
		Bit_Let - Sets a specified bit to 1.
		Bit_Vet - Sets a specified bit to 0.
	API:
		-
Callbacks:
	-
Definitions:
	MAX_WORLDS - Maximum number of worlds objects can be in.
Enums:
	-
Macros:
	 PLAYER_BIT_ARRAY - Number of cells required for MAX_PLAYER bits.
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
-*----------------------------------------------------------------------------*/

/*
native Object_AddToPlayer(objectid, playerid);
native Object_AddToWorld(objectid, virtualworld);
native Object_AddToAllPlayers(objectid);
native Object_AddToAllWorlds(objectid);
native Object_RemoveFromPlayer(objectid, playerid);
native Object_RemoveFromWorld(objectid, virtualworld);
native Object_RemoveFromAllPlayers(objectid);
native Object_RemoveFromAllWorlds(objectid);
native Object_IsGlobal(objectid);
native Object_SetViewDistance(objectid, Float:view);
native Object_IsDescendant(objectid, ancestor);
native Object_GetGateArea(gate);
native Object_SetAreaGate(objectid, areaid, Float:tx, Float:ty, Float:tz, Float:ts, time = 10000)
	native
native MoveDynamicObject(objectid, Float:X, Float:Y, Float:Z, Float:S);
native StopDynamicObject(objectid);
native IsValidDynamicObject(objectid);
native CreateDynamicObject(model, Float:X, Float:Y, Float:Z, Float:RX = 0.0, Float:RY = 0.0, Float:RZ = 0.0);
native CreatePlayerDynamicObject(playerid, model, Float:X, Float:Y, Float:Z, Float:RX = 0.0, Float:RY = 0.0, Float:RZ = 0.0);
native CreateVWDynamicObject(virtualworld, model, Float:X, Float:Y, Float:Z, Float:RX = 0.0, Float:RY = 0.0, Float:RZ = 0.0);
native CreatePlayerVWDynamicObject(playerid, virtualworld, model, Float:X, Float:Y, Float:Z, Float:RX = 0.0, Float:RY = 0.0, Float:RZ = 0.0);
native DestroyDynamicObject(objectid);
native GetDynamicObjectPos(objectid, &Float:X, &Float:Y, &Float:Z);
native GetDynamicObjectRot(objectid, &Float:RX, &Float:RY, &Float:RZ);
native SetDynamicObjectPos(objectid, Float:X, Float:Y, Float:Z);
native SetDynamicObjectRot(objectid, Float:RX, Float:RY, Float:RZ);
native AttachDynamicObjectToPlayer(objectid, playerid, Float:offX, Float:offY, Float:offZ, Float:rX, Float:rY, Float:rZ);
native DetachDynamicObjectFromPlayer(objectid);
native IsValidModel(modelid);
native RemoveObjectFromParent(objectid);
native AttachObjectToObject(attachobject, toobject);
native CreateGate(modelid, Float:x, Float:y, Float:z, Float:tx, Float:ty, Float:tz, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0, Float:speed = 2.0);
	native
*/

#define Timer_Add(%1,%2) \
	SetTimer(%1, 1000 / (%2), 1)

#if !defined ceildiv
	#define ceildiv(%1,%2) \
		(((%1) + (%2) - 1) / (%2))
#endif

#define PLAYER_BIT_ARRAY Bit_Bits(MAX_PLAYERS)

#define foreach(%1,%2) \
	for (new %2 = 0; %2 < MAX_PLAYERS; %2++) if (IsPlayerConnected(%2))

#if !defined MAX_WORLDS
	#define MAX_WORLDS (256)
#endif

#define Bit_Bits(%1) \
	ceildiv((%1), cellbits)

#define Bit_GetBit(%1,%2) \
	((%1[(%2) / cellbits]) & Bit:(1 << ((%2) % cellbits)))

#define Bit_Get(%1,%2) \
	_:Bit_GetBit(Bit:%1, _:%2)

#define Bit_Let(%1,%2) \
	%1[(%2) / cellbits] |= Bit:(1 << ((%2) % cellbits))

#define Bit_Vet(%1,%2) \
	%1[(%2) / cellbits] &= Bit:~(1 << ((%2) % cellbits))

stock Bit_Set(Bit:array[], slot, set, size)
{
	if (slot / cellbits >= size) return;
	if (set) Bit_Let(array, slot);
	else Bit_Vet(array, slot);
}

stock Bit_SetAll(Bit:array[], set, size)
{
	new
		Bit:val = (set) ? (Bit:0xFFFFFFFF) : (Bit:0);
	for (new i = 0; i < size; i++) array[i] = val;
}

#include "Visual/YSI_objects.own"
