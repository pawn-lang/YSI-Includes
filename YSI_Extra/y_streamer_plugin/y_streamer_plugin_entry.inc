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

HOOK__ OnDynamicObjectMoved(CB_STREAMER_TAG_OBJECT:objectid)
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

HOOK__ OnPlayerPickUpDynPickup(playerid, CB_STREAMER_TAG_PICKUP:pickupid)
{
	new
		Func:cb<ii>;
	if (Sparse_TryGet(YSI_g_sDynamicPickups, _:pickupid, _:cb))
	{
		@.cb(playerid, _:pickupid);
	}
}

HOOK__ OnPlayerEnterDynamicCP(playerid, CB_STREAMER_TAG_CP:checkpointid)
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

HOOK__ OnPlayerEnterDynRaceCP(playerid, CB_STREAMER_TAG_RACE_CP:checkpointid)
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

HOOK__ OnPlayerEnterDynArea(playerid, CB_STREAMER_TAG_AREA:areaid)
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


stock STREAMER_TAG_PICKUP:cb_CreateDynamicPickup(modelid, type, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_PICKUP_SD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
{
	return CreateDynamicPickup(modelid, type, x, y, z, worldid, interiorid, playerid, streamdistance, areaid, priority);
}

#if defined _ALS_CreateDynamicPickup
	#undef CreateDynamicPickup
#else
	#define _ALS_CreateDynamicPickup
#endif
#define CreateDynamicPickup cb_CreateDynamicPickup

stock cb_DestroyDynamicPickup(STREAMER_TAG_PICKUP:pickupid)
{
	return DestroyDynamicPickup(pickupid);
}

#if defined _ALS_DestroyDynamicPickup
	#undef DestroyDynamicPickup
#else
	#define _ALS_DestroyDynamicPickup
#endif
#define DestroyDynamicPickup cb_DestroyDynamicPickup


stock STREAMER_TAG_CP:cb_CreateDynamicCP(Float:x, Float:y, Float:z, Float:size, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_CP_SD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
{
	return CreateDynamicCP(x, y, z, size, worldid, interiorid, playerid, streamdistance, areaid, priority);
}

#if defined _ALS_CreateDynamicCP
	#undef CreateDynamicCP
#else
	#define _ALS_CreateDynamicCP
#endif
#define CreateDynamicCP cb_CreateDynamicCP

stock cb_DestroyDynamicCP(STREAMER_TAG_CP:checkpointid)
{
	return DestroyDynamicCP(checkpointid);
}

#if defined _ALS_DestroyDynamicCP
	#undef DestroyDynamicCP
#else
	#define _ALS_DestroyDynamicCP
#endif
#define DestroyDynamicCP cb_DestroyDynamicCP


stock STREAMER_TAG_RACE_CP:cb_CreateDynamicRaceCP(type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_RACE_CP_SD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
{
	return CreateDynamicRaceCP(type, x, y, z, nextx, nexty, nextz, size, worldid, interiorid, playerid, streamdistance, areaid, priority);
}

#if defined _ALS_CreateDynamicRaceCP
	#undef CreateDynamicRaceCP
#else
	#define _ALS_CreateDynamicRaceCP
#endif
#define CreateDynamicRaceCP cb_CreateDynamicRaceCP

stock cb_DestroyDynamicRaceCP(STREAMER_TAG_RACE_CP:checkpointid)
{
	return DestroyDynamicRaceCP(checkpointid);
}

#if defined _ALS_DestroyDynamicRaceCP
	#undef DestroyDynamicRaceCP
#else
	#define _ALS_DestroyDynamicRaceCP
#endif
#define DestroyDynamicRaceCP cb_DestroyDynamicRaceCP


stock STREAMER_TAG_AREA:cb_CreateDynamicCircle(Float:x, Float:y, Float:size, worldid = -1, interiorid = -1, playerid = -1, priority = 0)
{
	return CreateDynamicCircle(x, y, size, worldid, interiorid, playerid, priority);
}

#if defined _ALS_CreateDynamicCircle
	#undef CreateDynamicCircle
#else
	#define _ALS_CreateDynamicCircle
#endif
#define CreateDynamicCircle cb_CreateDynamicCircle

stock STREAMER_TAG_AREA:cb_CreateDynamicCylinder(Float:x, Float:y, Float:minz, Float:maxz, Float:size, worldid = -1, interiorid = -1, playerid = -1, priority = 0)
{
	return CreateDynamicCylinder(x, y, minz, maxz, size, worldid, interiorid, playerid, priority);
}

#if defined _ALS_CreateDynamicCylinder
	#undef CreateDynamicCylinder
#else
	#define _ALS_CreateDynamicCylinder
#endif
#define CreateDynamicCylinder cb_CreateDynamicCylinder

stock STREAMER_TAG_AREA:cb_CreateDynamicSphere(Float:x, Float:y, Float:z, Float:size, worldid = -1, interiorid = -1, playerid = -1, priority = 0)
{
	return CreateDynamicSphere(x, y, z, size, worldid, interiorid, playerid, priority);
}

#if defined _ALS_CreateDynamicSphere
	#undef CreateDynamicSphere
#else
	#define _ALS_CreateDynamicSphere
#endif
#define CreateDynamicSphere cb_CreateDynamicSphere

stock STREAMER_TAG_AREA:cb_CreateDynamicRectangle(Float:minx, Float:miny, Float:maxx, Float:maxy, worldid = -1, interiorid = -1, playerid = -1, priority = 0)
{
	return CreateDynamicRectangle(minx, miny, maxx, maxy, worldid, interiorid, playerid, priority);
}

#if defined _ALS_CreateDynamicRectangle
	#undef CreateDynamicRectangle
#else
	#define _ALS_CreateDynamicRectangle
#endif
#define CreateDynamicRectangle cb_CreateDynamicRectangle

stock STREAMER_TAG_AREA:cb_CreateDynamicCuboid(Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, worldid = -1, interiorid = -1, playerid = -1, priority = 0)
{
	return CreateDynamicCuboid(minx, miny, minz, maxx, maxy, maxz, worldid, interiorid, playerid, priority);
}

#if defined _ALS_CreateDynamicCuboid
	#undef CreateDynamicCuboid
#else
	#define _ALS_CreateDynamicCuboid
#endif
#define CreateDynamicCuboid cb_CreateDynamicCuboid

stock STREAMER_TAG_AREA:cb_CreateDynamicCube(Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, worldid = -1, interiorid = -1, playerid = -1, priority = 0)
{
	return CreateDynamicCube(minx, miny, minz, maxx, maxy, maxz, worldid, interiorid, playerid, priority);
}

#if defined _ALS_CreateDynamicCube
	#undef CreateDynamicCube
#else
	#define _ALS_CreateDynamicCube
#endif
#define CreateDynamicCube cb_CreateDynamicCube

stock STREAMER_TAG_AREA:cb_CreateDynamicPolygon(const Float:points[], Float:minz = -FLOAT_INFINITY, Float:maxz = FLOAT_INFINITY, maxpoints = sizeof points, worldid = -1, interiorid = -1, playerid = -1, priority = 0)
{
	return CreateDynamicPolygon(points, minz, maxz, maxpoints, worldid, interiorid, playerid, priority);
}

#if defined _ALS_CreateDynamicPolygon
	#undef CreateDynamicPolygon
#else
	#define _ALS_CreateDynamicPolygon
#endif
#define CreateDynamicPolygon cb_CreateDynamicPolygon

stock cb_DestroyDynamicArea(STREAMER_TAG_AREA:areaid)
{
	return DestroyDynamicArea(STREAMER_TAG_AREA:areaid);
}

#if defined _ALS_DestroyDynamicArea
	#undef DestroyDynamicArea
#else
	#define _ALS_DestroyDynamicArea
#endif
#define DestroyDynamicArea cb_DestroyDynamicArea



stock STREAMER_TAG_PICKUP:cb_CreateDynamicPickupEx(modelid, type, Float:x, Float:y, Float:z, Float:streamdistance = STREAMER_PICKUP_SD, const worlds[] = { -1 }, const interiors[] = { -1 }, const players[] = { -1 }, const STREAMER_TAG_AREA:areas[] = { STREAMER_TAG_AREA:-1 }, priority = 0, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players, maxareas = sizeof areas)
{
	return CreateDynamicPickupEx(modelid, type, x, y, z, streamdistance, worlds, interiors, players, areas, priority, maxworlds, maxinteriors, maxplayers, maxareas);
}

#if defined _ALS_CreateDynamicPickupEx
	#undef CreateDynamicPickupEx
#else
	#define _ALS_CreateDynamicPickupEx
#endif
#define CreateDynamicPickupEx cb_CreateDynamicPickupEx

stock STREAMER_TAG_CP:cb_CreateDynamicCPEx(Float:x, Float:y, Float:z, Float:size, Float:streamdistance = STREAMER_CP_SD, const worlds[] = { -1 }, const interiors[] = { -1 }, const players[] = { -1 }, const STREAMER_TAG_AREA:areas[] = { STREAMER_TAG_AREA:-1 }, priority = 0, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players, maxareas = sizeof areas)
{
	return CreateDynamicCPEx(x, y, z, size, streamdistance, worlds, interiors, players, areas, priority, maxworlds, maxinteriors, maxplayers, maxareas);
}

#if defined _ALS_CreateDynamicCPEx
	#undef CreateDynamicCPEx
#else
	#define _ALS_CreateDynamicCPEx
#endif
#define CreateDynamicCPEx cb_CreateDynamicCPEx

stock STREAMER_TAG_RACE_CP:cb_CreateDynamicRaceCPEx(type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size, Float:streamdistance = STREAMER_RACE_CP_SD, const worlds[] = { -1 }, const interiors[] = { -1 }, const players[] = { -1 }, const STREAMER_TAG_AREA:areas[] = { STREAMER_TAG_AREA:-1 }, priority = 0, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players, maxareas = sizeof areas)
{
	return CreateDynamicRaceCPEx(type, x, y, z, nextx, nexty, nextz, size, streamdistance, worlds, interiors, players, areas, priority, maxworlds, maxinteriors, maxplayers, maxareas);
}

#if defined _ALS_CreateDynamicRaceCPEx
	#undef CreateDynamicRaceCPEx
#else
	#define _ALS_CreateDynamicRaceCPEx
#endif
#define CreateDynamicRaceCPEx cb_CreateDynamicRaceCPEx


stock STREAMER_TAG_AREA:cb_CreateDynamicCircleEx(Float:x, Float:y, Float:size, const worlds[] = { -1 }, const interiors[] = { -1 }, const players[] = { -1 }, priority = 0, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
{
	return CreateDynamicCircleEx(x, y, size, worlds, interiors, players, priority, maxworlds, maxinteriors, maxplayers);
}

#if defined _ALS_CreateDynamicCircleEx
	#undef CreateDynamicCircleEx
#else
	#define _ALS_CreateDynamicCircleEx
#endif
#define CreateDynamicCircleEx cb_CreateDynamicCircleEx

stock STREAMER_TAG_AREA:cb_CreateDynamicCylinderEx(Float:x, Float:y, Float:minz, Float:maxz, Float:size, const worlds[] = { -1 }, const interiors[] = { -1 }, const players[] = { -1 }, priority = 0, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
{
	return CreateDynamicCylinderEx(x, y, minz, maxz, size, worlds, interiors, players, priority, maxworlds, maxinteriors, maxplayers);
}

#if defined _ALS_CreateDynamicCylinderEx
	#undef CreateDynamicCylinderEx
#else
	#define _ALS_CreateDynamicCylinderEx
#endif
#define CreateDynamicCylinderEx cb_CreateDynamicCylinderEx

stock STREAMER_TAG_AREA:cb_CreateDynamicSphereEx(Float:x, Float:y, Float:z, Float:size, const worlds[] = { -1 }, const interiors[] = { -1 }, const players[] = { -1 }, priority = 0, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
{
	return CreateDynamicSphereEx(x, y, z, size, worlds, interiors, players, priority, maxworlds, maxinteriors, maxplayers);
}

#if defined _ALS_CreateDynamicSphereEx
	#undef CreateDynamicSphereEx
#else
	#define _ALS_CreateDynamicSphereEx
#endif
#define CreateDynamicSphereEx cb_CreateDynamicSphereEx

stock STREAMER_TAG_AREA:cb_CreateDynamicRectangleEx(Float:minx, Float:miny, Float:maxx, Float:maxy, const worlds[] = { -1 }, const interiors[] = { -1 }, const players[] = { -1 }, priority = 0, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
{
	return CreateDynamicRectangleEx(minx, miny, maxx, maxy, worlds, interiors, players, priority, maxworlds, maxinteriors, maxplayers);
}

#if defined _ALS_CreateDynamicRectangleEx
	#undef CreateDynamicRectangleEx
#else
	#define _ALS_CreateDynamicRectangleEx
#endif
#define CreateDynamicRectangleEx cb_CreateDynamicRectangleEx

stock STREAMER_TAG_AREA:cb_CreateDynamicCuboidEx(Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, const worlds[] = { -1 }, const interiors[] = { -1 }, const players[] = { -1 }, priority = 0, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
{
	return CreateDynamicCuboidEx(minx, miny, minz, maxx, maxy, maxz, worlds, interiors, players, priority, maxworlds, maxinteriors, maxplayers);
}

#if defined _ALS_CreateDynamicCuboidEx
	#undef CreateDynamicCuboidEx
#else
	#define _ALS_CreateDynamicCuboidEx
#endif
#define CreateDynamicCuboidEx cb_CreateDynamicCuboidEx

stock STREAMER_TAG_AREA:cb_CreateDynamicCubeEx(Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, const worlds[] = { -1 }, const interiors[] = { -1 }, const players[] = { -1 }, priority = 0, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
{
	return CreateDynamicCubeEx(minx, miny, minz, maxx, maxy, maxz, worlds, interiors, players, priority, maxworlds, maxinteriors, maxplayers);
}

#if defined _ALS_CreateDynamicCubeEx
	#undef CreateDynamicCubeEx
#else
	#define _ALS_CreateDynamicCubeEx
#endif
#define CreateDynamicCubeEx cb_CreateDynamicCubeEx

stock STREAMER_TAG_AREA:cb_CreateDynamicPolygonEx(const Float:points[], Float:minz = -FLOAT_INFINITY, Float:maxz = FLOAT_INFINITY, maxpoints = sizeof points, const worlds[] = { -1 }, const interiors[] = { -1 }, const players[] = { -1 }, priority = 0, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
{
	return CreateDynamicPolygonEx(points, minz, maxz, maxpoints, worlds, interiors, players, priority, maxworlds, maxinteriors, maxplayers);
}

#if defined _ALS_CreateDynamicPolygonEx
	#undef CreateDynamicPolygonEx
#else
	#define _ALS_CreateDynamicPolygonEx
#endif
#define CreateDynamicPolygonEx cb_CreateDynamicPolygonEx

stock STREAMER_TAG_ACTOR:cb_CreateDynamicActorEx(modelid, Float:x, Float:y, Float:z, Float:r, invulnerable = 1, Float:health = 100.0, Float:streamdistance = STREAMER_ACTOR_SD, const worlds[] = { -1 }, const interiors[] = { -1 }, const players[] = { -1 }, const STREAMER_TAG_AREA:areas[] = { STREAMER_TAG_AREA:-1 }, priority = 0, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players, maxareas = sizeof areas)
{
	return CreateDynamicActorEx(modelid, x, y, z, r, invulnerable, health, streamdistance, worlds, interiors, players, areas, priority, maxworlds, maxinteriors, maxplayers, maxareas);
}

#if defined _ALS_CreateDynamicActorEx
	#undef CreateDynamicActorEx
#else
	#define _ALS_CreateDynamicActorEx
#endif
#define CreateDynamicActorEx cb_CreateDynamicActorEx


stock cb_DestroyAllDynamicObjects()
{
	return DestroyAllDynamicObjects();
}

#if defined _ALS_DestroyAllDynamicObjects
	#undef DestroyAllDynamicObjects
#else
	#define _ALS_DestroyAllDynamicObjects
#endif
#define DestroyAllDynamicObjects cb_DestroyAllDynamicObjects

stock cb_DestroyAllDynamicPickups()
{
	return DestroyAllDynamicPickups();
}

#if defined _ALS_DestroyAllDynamicPickups
	#undef DestroyAllDynamicPickups
#else
	#define _ALS_DestroyAllDynamicPickups
#endif
#define DestroyAllDynamicPickups cb_DestroyAllDynamicPickups

stock cb_DestroyAllDynamicCPs()
{
	return DestroyAllDynamicCPs();
}

#if defined _ALS_DestroyAllDynamicCPs
	#undef DestroyAllDynamicCPs
#else
	#define _ALS_DestroyAllDynamicCPs
#endif
#define DestroyAllDynamicCPs cb_DestroyAllDynamicCPs

stock cb_DestroyAllDynamicRaceCPs()
{
	return DestroyAllDynamicRaceCPs();
}

#if defined _ALS_DestroyAllDynamicRaceCPs
	#undef DestroyAllDynamicRaceCPs
#else
	#define _ALS_DestroyAllDynamicRaceCPs
#endif
#define DestroyAllDynamicRaceCPs cb_DestroyAllDynamicRaceCPs

stock cb_DestroyAllDynamicAreas()
{
	return DestroyAllDynamicAreas();
}

#if defined _ALS_DestroyAllDynamicAreas
	#undef DestroyAllDynamicAreas
#else
	#define _ALS_DestroyAllDynamicAreas
#endif
#define DestroyAllDynamicAreas cb_DestroyAllDynamicAreas

