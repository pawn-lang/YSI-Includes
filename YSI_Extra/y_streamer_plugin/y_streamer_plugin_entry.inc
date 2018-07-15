#if defined _INC_y_streamer_plugin
	#endinput
#endif
#define _INC_y_streamer_plugin

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

#include "..\..\YSI_Data\y_sparsearray"
#include "..\..\YSI_Coding\y_inline"
#include "..\..\YSI_Coding\y_hooks"

#if defined STREAMER_ENABLE_TAGS
	#define CB_STREAMER_TAG_OBJECT DynamicObject
	#define CB_STREAMER_TAG_PICKUP DynamicPickup
	#define CB_STREAMER_TAG_CP DynamicCP
	#define CB_STREAMER_TAG_RACE_CP DynamicRaceCP
	#define CB_STREAMER_TAG_MAP_ICON DynamicMapIcon
	#define CB_STREAMER_TAG_3D_TEXT_LABEL DynamicText3D
	#define CB_STREAMER_TAG_AREA DynamicArea
	#define CB_STREAMER_TAG_ACTOR DynamicActor
#else
	#define CB_STREAMER_TAG_OBJECT _
	#define CB_STREAMER_TAG_PICKUP _
	#define CB_STREAMER_TAG_CP _
	#define CB_STREAMER_TAG_RACE_CP _
	#define CB_STREAMER_TAG_MAP_ICON _
	#define CB_STREAMER_TAG_AREA _
	#define CB_STREAMER_TAG_ACTOR _
#endif

static stock
	SparseArray:YSI_g_sDynamicObjects<>,
	SparseArray:YSI_g_sDynamicAreas<>,
	SparseArray:YSI_g_sDynamicPickups<>,
	SparseArray:YSI_g_sDynamicCPs<>,
	SparseArray:YSI_g_sDynamicRaceCPs<>;

stock cb_DestroyDynamicObject(CB_STREAMER_TAG_OBJECT:objectid)
{
	new
		Func:cb<i>;
	if (Sparse_Exchange(YSI_g_sDynamicObjects, _:objectid, _:cb))
		Indirect_Release(cb);
	return DestroyDynamicObject(objectid);
}

#if defined _ALS_DestroyDynamicObject
	#undef DestroyDynamicObject
#else
	#define _ALS_DestroyDynamicObject
#endif
#define DestroyDynamicObject cb_DestroyDynamicObject

stock cb_StopDynamicObject(CB_STREAMER_TAG_OBJECT:objectid)
{
	new
		Func:cb<i>;
	if (Sparse_Exchange(YSI_g_sDynamicObjects, _:objectid, _:cb))
		Indirect_Release(cb);
	return StopDynamicObject(objectid);
}

#if defined _ALS_StopDynamicObject
	#undef StopDynamicObject
#else
	#define _ALS_StopDynamicObject
#endif
#define StopDynamicObject cb_StopDynamicObject

// `Streamer_CallbackHook` seems like it would be perfect here.  Shame...

stock cb_MoveDynamicObject(Func:onMoved<i>, CB_STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z, Float:speed, Float:rx = -1000.0, Float:ry = -1000.0, Float:rz = -1000.0)
{
	new
		Func:cb<i>;
	if (Sparse_Exchange(YSI_g_sDynamicObjects, _:objectid, _:cb, _:onMoved))
		Indirect_Release(cb);
	Indirect_Claim(onMoved);
	return MoveDynamicObject(objectid, x, y, z, speed, rx, ry, rz);
}

//stock Streamer_GetCallback(type, STREAMER_ALL_TAGS:id)
//{
//	switch (type)
//	{
//		case STREAMER_TYPE_OBJECT: {}
//		case STREAMER_TYPE_PICKUP: {}
//		case STREAMER_TYPE_CP: {}
//		case STREAMER_TYPE_RACE_CP: {}
//		case STREAMER_TYPE_MAP_ICON: {}
//		case STREAMER_TYPE_3D_TEXT_LABEL: {}
//		case STREAMER_TYPE_AREA: {}
//		case STREAMER_TYPE_ACTOR: {}
//	}
//}

hook OnDynamicObjectMoved(CB_STREAMER_TAG_OBJECT:objectid)
{
	new
		Func:cb<i>;
	if (Sparse_Exchange(YSI_g_sDynamicObjects, _:objectid, _:cb))
	{
		@.cb(_:objectid);
		Indirect_Release(cb);
	}
}

//hook OnPlayerEditDynamicObject(playerid, CB_STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
//{
//	
//}

//hook OnPlayerSelectDynamicObject(playerid, CB_STREAMER_TAG_OBJECT:objectid, modelid, Float:x, Float:y, Float:z)
//{
//	
//}

//hook OnPlayerShootDynamicObject(playerid, weaponid, CB_STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z)
//{
//	
//}

hook OnPlayerPickUpDynPickup(playerid, CB_STREAMER_TAG_PICKUP:pickupid)
{
	new
		Func:cb<ii>;
	if (Sparse_TryGet(YSI_g_sDynamicPickups, _:pickupid, _:cb))
	{
		@.cb(playerid, _:pickupid);
	}
}

hook OnPlayerEnterDynamicCP(playerid, CB_STREAMER_TAG_CP:checkpointid)
{
	new
		Func:cb<ii>;
	if (Sparse_TryGet(YSI_g_sDynamicCPs, _:checkpointid, _:cb))
	{
		@.cb(playerid, _:checkpointid);
	}
}

//hook OnPlayerLeaveDynamicCP(playerid, CB_STREAMER_TAG_CP:checkpointid)
//{
//	
//}

hook OnPlayerEnterDynRaceCP(playerid, CB_STREAMER_TAG_RACE_CP:checkpointid)
{
	new
		Func:cb<ii>;
	if (Sparse_TryGet(YSI_g_sDynamicRaceCPs, _:checkpointid, _:cb))
	{
		@.cb(playerid, _:checkpointid);
	}
}

//hook OnPlayerLeaveDynamicRaceCP(playerid, CB_STREAMER_TAG_RACE_CP:checkpointid)
//{
//	
//}

hook OnPlayerEnterDynArea(playerid, CB_STREAMER_TAG_AREA:areaid)
{
	new
		Func:cb<ii>;
	if (Sparse_TryGet(YSI_g_sDynamicAreas, _:areaid, _:cb))
	{
		@.cb(playerid, _:areaid);
	}
}

//hook OnPlayerLeaveDynamicArea(playerid, CB_STREAMER_TAG_AREA:areaid)
//{
//	
//}

//hook OnPlayerGiveDamageDynamicActor(playerid, CB_STREAMER_TAG_ACTOR:actorid, Float:amount, weaponid, bodypart)
//{
//	
//}

//hook OnDynamicActorStreamIn(CB_STREAMER_TAG_ACTOR:actorid, forplayerid)
//{
//	
//}

//hook OnDynamicActorStreamOut(CB_STREAMER_TAG_ACTOR:actorid, forplayerid)
//{
//	
//}

//hook Streamer_OnItemStreamIn(type, CB_STREAMER_ALL_TAGS:id)
//{
//	
//}

//hook Streamer_OnItemStreamOut(type, CB_STREAMER_ALL_TAGS:id)
//{
//	
//}

//hook Streamer_OnPluginError(const error[])
//{
//	
//}

