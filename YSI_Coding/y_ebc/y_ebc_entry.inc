#if defined _INC_y_ebc
	#endinput
#endif
#define _INC_y_ebc

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

#include "..\y_inline"

// The fake definition from y_inline to give nicer errors.
#undef EBC

// The true definition which relies on a better compiler.
#define EBC(%0) Inline_EBC__(_:(%0),_:tagof(%0))
#define TBC(%0) Inline_EBC__(_:(%0),(_:-1,)) // `_:` is one of the oldest macros
// in YSI, and removes trailing commas in cases like this.

#define Inline_EBC__(_:(%0,%1),%2(%3,%9)) (%1)$(Inline_EBC__(_:(%0),%2(%3)))

// Common EBC tags.
__COMPILER_TAG_DATA(Vehicle, INVALID_VEHICLE_ID);
__COMPILER_TAG_DATA(Player, INVALID_PLAYER_ID);
__COMPILER_TAG_DATA(Object, INVALID_OBJECT_ID);
__COMPILER_TAG_DATA(PlayerObject, INVALID_OBJECT_ID);
__COMPILER_TAG_DATA(Pickup, INVALID_PICKUP);

stock EBC_Deactivate_(owner, tag)
{
	Indirect_Disconnect(Inline_EBC__(owner, tag));
}
#define EBC_Deactivate(%0) EBC_Deactivate_(_:(%0), tagof (%0))
#define EBC_Deactivate_(_:(%0,%1),%9) EBC_Deactivate_(_:(%0), (%1))

// Hook standard destructors.

public OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	EBC_Deactivate(playerid, tagof(playerid)); // _: (default).
	EBC_Deactivate(playerid, tagof(Player:));
	#if defined EBC_OnPlayerDisconnect
		return EBC_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#endif
#define _ALS_OnPlayerDisconnect
#define OnPlayerDisconnect( EBC_OnPlayerDisconnect(
#if defined EBC_OnPlayerDisconnect
	forward EBC_OnPlayerDisconnect(playerid, reason);
#endif

stock bool:EBC_DestroyVehicle(vehicleid)
{
	EBC_Deactivate(vehicleid, tagof(Vehicle:));
	return bool:DestroyVehicle(vehicleid);
}

#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#endif
#define _ALS_DestroyVehicle
#define DestroyVehicle( EBC_DestroyVehicle(

stock bool:EBC_DestroyObject(objectid)
{
	EBC_Deactivate(objectid, tagof(Object:));
	return bool:DestroyObject(objectid);
}

#if defined _ALS_DestroyObject
	#undef DestroyObject
#endif
#define _ALS_DestroyObject
#define DestroyObject( EBC_DestroyObject(

stock bool:EBC_DestroyPlayerObject(playerid, objectid)
{
	EBC_Deactivate((objectid << 10) | playerid, tagof(PlayerObject:));
	return bool:DestroyPlayerObject(playerid, objectid);
}

#if defined _ALS_DestroyPlayerObject
	#undef DestroyPlayerObject
#endif
#define _ALS_DestroyPlayerObject
#define DestroyPlayerObject( EBC_DestroyPlayerObject(

stock bool:EBC_DestroyPickup(pickupid)
{
	EBC_Deactivate(pickupid, tagof(Pickup:));
	return bool:DestroyPickup(pickupid);
}

#if defined _ALS_DestroyPickup
	#undef DestroyPickup
#endif
#define _ALS_DestroyPickup
#define DestroyPickup( EBC_DestroyPickup(

//stock bool:EBC_DisablePlayerCheckpoint(playerid)
//{
//	EBC_Deactivate(playerid, tagof(Checkpoint:));
//	return bool:DisablePlayerCheckpoint(playerid);
//}
//
//#if defined _ALS_DisablePlayerCheckpoint
//	#undef DisablePlayerCheckpoint
//#endif
//#define _ALS_DisablePlayerCheckpoint
//#define DisablePlayerCheckpoint( EBC_DisablePlayerCheckpoint(

