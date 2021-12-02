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

#include "..\..\YSI_Coding\y_inline"
#include "..\..\YSI_Coding\y_hooks"

#if defined E_STREAMER_CUSTOM && 0
	// Store the callback data in `E_STREAMER_CUSTOM`
	#define E_STREAMER_YSI_OBJECT_MOVED    E_STREAMER_CUSTOM(0x59534900) // YSI 00
	#define E_STREAMER_YSI_OBJECT_EDITED   E_STREAMER_CUSTOM(0x59534901) // YSI 01
	#define E_STREAMER_YSI_OBJECT_SELECTED E_STREAMER_CUSTOM(0x59534902) // YSI 02
	#define E_STREAMER_YSI_OBJECT_SHOT     E_STREAMER_CUSTOM(0x59534903) // YSI 03
	#define E_STREAMER_YSI_PICKUP          E_STREAMER_CUSTOM(0x59534910) // YSI 10
	#define E_STREAMER_YSI_CP_ENTER        E_STREAMER_CUSTOM(0x59534920) // YSI 20
	#define E_STREAMER_YSI_CP_LEAVE        E_STREAMER_CUSTOM(0x59534921) // YSI 21
	#define E_STREAMER_YSI_RACE_CP_ENTER   E_STREAMER_CUSTOM(0x59534930) // YSI 30
	#define E_STREAMER_YSI_RACE_CP_LEAVE   E_STREAMER_CUSTOM(0x59534931) // YSI 31
	#define E_STREAMER_YSI_AREA            E_STREAMER_CUSTOM(0x59534940) // YSI 40

	#define E_STREAMER_YSI(%0) E_STREAMER_YSI_%0
#else
	// Store the callback data in a per-entity sparse array.
	#include "..\..\YSI_Data\y_sparsearray"

	static stock
		SparseArray:YSI_g_sDynamic_OBJECT_MOVED<>,
		SparseArray:YSI_g_sDynamic_OBJECT_EDITED<>,
		SparseArray:YSI_g_sDynamic_OBJECT_SELECTED<>,
		SparseArray:YSI_g_sDynamic_OBJECT_SHOT<>,
		SparseArray:YSI_g_sDynamic_PICKUP<>,
		SparseArray:YSI_g_sDynamic_CP_ENTER<>,
		SparseArray:YSI_g_sDynamic_CP_LEAVE<>,
		SparseArray:YSI_g_sDynamic_RACE_CP_ENTER<>,
		SparseArray:YSI_g_sDynamic_RACE_CP_LEAVE<>,
		SparseArray:YSI_g_sDynamic_AREA<>,
		Func:YSI_g_sStreamerError<s>;

	#define Y_STREAMER_DESTROY(%0,%1) \
		for (new y_streamer_cb = 0; __once && Sparse_Exchange(YSI_g_sDynamic_%0, _:(%1), y_streamer_cb); Indirect_Release(y_streamer_cb)) \
			continue

	#define Y_STREAMER_EXCHANCE(%0,%1,%2) \
		for (new y_streamer_cb = 0; __once && Sparse_Exchange(YSI_g_sDynamic_%0, _:(%1), y_streamer_cb, _:(%2)); Indirect_Release(y_streamer_cb), Indirect_Claim(_:(%2))) \
			continue

	#define Y_STREAMER_MULTI(%0,%1,%2) \
		for (new %2; __once && Sparse_TryGet(YSI_g_sDynamic_%0, _:(%1), _:(%2)); ) \

	#define Y_STREAMER_ONCE(%0,%1,%2) \
		for (new %2; __once && Sparse_TryGet(YSI_g_sDynamic_%0, _:(%1), _:(%2)); Indirect_Release(_:(%2))) \
#endif

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

stock cb_DestroyDynamicObject(CB_STREAMER_TAG_OBJECT:objectid)
{
	Y_STREAMER_DESTROY(OBJECT_MOVED, objectid);
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
	Y_STREAMER_DESTROY(OBJECT_MOVED, objectid);
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
	Y_STREAMER_EXCHANCE(OBJECT_MOVED, objectid, onMoved);
	return MoveDynamicObject(objectid, x, y, z, speed, rx, ry, rz);
}

HOOK__ OnDynamicObjectMoved(CB_STREAMER_TAG_OBJECT:objectid)
{
	// This only happens once, then the callback is redundant.  Free it.
	Y_STREAMER_ONCE(OBJECT_MOVED, objectid, Func:cb<i>)
	{
		@.cb(_:objectid);
	}
}

HOOK__ OnPlayerEditDynamicObject(playerid, CB_STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	Y_STREAMER_MULTI(OBJECT_EDITED, objectid, Func:cb<iiiffffff>)
	{
		@.cb(playerid, _:objectid, response, x, y, z, rx, ry, rz);
	}
}

HOOK__ OnPlayerSelectDynamicObject(playerid, CB_STREAMER_TAG_OBJECT:objectid, modelid, Float:x, Float:y, Float:z)
{
	Y_STREAMER_MULTI(OBJECT_SELECTED, objectid, Func:cb<iiifff>)
	{
		@.cb(playerid, _:objectid, modelid, x, y, z);
	}
}

HOOK__ OnPlayerShootDynamicObject(playerid, weaponid, CB_STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z)
{
	Y_STREAMER_MULTI(OBJECT_SHOT, objectid, Func:cb<iiifff>)
	{
		@.cb(playerid, weaponid, _:objectid, x, y, z);
	}
}

HOOK__ OnPlayerPickUpDynPickup(playerid, CB_STREAMER_TAG_PICKUP:pickupid)
{
	Y_STREAMER_MULTI(PICKUP, pickupid, Func:cb<ii>)
	{
		@.cb(playerid, _:pickupid);
	}
}

HOOK__ OnPlayerEnterDynamicCP(playerid, CB_STREAMER_TAG_CP:checkpointid)
{
	Y_STREAMER_MULTI(CP_ENTER, checkpointid, Func:cb<ii>)
	{
		@.cb(playerid, _:checkpointid);
	}
}

HOOK__ OnPlayerLeaveDynamicCP(playerid, CB_STREAMER_TAG_CP:checkpointid)
{
	Y_STREAMER_MULTI(CP_LEAVE, checkpointid, Func:cb<ii>)
	{
		@.cb(playerid, _:checkpointid);
	}
}

HOOK__ OnPlayerEnterDynRaceCP(playerid, CB_STREAMER_TAG_RACE_CP:checkpointid)
{
	Y_STREAMER_MULTI(RACE_CP_ENTER, checkpointid, Func:cb<ii>)
	{
		@.cb(playerid, _:checkpointid);
	}
}

HOOK__ OnPlayerLeaveDynRaceCP(playerid, CB_STREAMER_TAG_RACE_CP:checkpointid)
{
	Y_STREAMER_MULTI(RACE_CP_LEAVE, checkpointid, Func:cb<ii>)
	{
		@.cb(playerid, _:checkpointid);
	}
}

HOOK__ OnPlayerEnterDynArea(playerid, CB_STREAMER_TAG_AREA:areaid)
{
	Y_STREAMER_MULTI(RACE_AREA_ENTER, areaid, Func:cb<ii>)
	{
		@.cb(playerid, _:areaid);
	}
}

HOOK__ OnPlayerLeaveDynArea(playerid, CB_STREAMER_TAG_AREA:areaid)
{
	Y_STREAMER_MULTI(RACE_AREA_LEAVE, areaid, Func:cb<ii>)
	{
		@.cb(playerid, _:areaid);
	}
}

HOOK__ OnPlayerGiveDamageDynActor(playerid, CB_STREAMER_TAG_ACTOR:actorid, Float:amount, weaponid, bodypart)
{
	Y_STREAMER_MULTI(ACTOR_DAMAGE, actorid, Func:cb<iifii>)
	{
		@.cb(playerid, _:actorid, amount, weaponid, bodypart);
	}
}

HOOK__ OnDynamicActorStreamIn(CB_STREAMER_TAG_ACTOR:actorid, forplayerid)
{
	Y_STREAMER_MULTI(ACTOR_IN, actorid, Func:cb<ii>)
	{
		@.cb(_:actorid, forplayerid);
	}
}

HOOK__ OnDynamicActorStreamOut(CB_STREAMER_TAG_ACTOR:actorid, forplayerid)
{
	Y_STREAMER_MULTI(ACTOR_OUT, actorid, Func:cb<ii>)
	{
		@.cb(_:actorid, forplayerid);
	}
}

HOOK__ Streamer_OnItemStreamIn(type, CB_STREAMER_ALL_TAGS:id, forplayerid)
{
	Y_STREAMER_MULTI(ITEM_IN, id, Func:cb<iii>)
	{
		@.cb(type, _:id, forplayerid);
	}
	switch (type)
	{
	case STREAMER_TYPE_OBJECT:
		Y_STREAMER_MULTI(OBJECT_IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_PICKUP:
		Y_STREAMER_MULTI(PICKUP_IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_CP:
		Y_STREAMER_MULTI(CP_IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_RACE_CP:
		Y_STREAMER_MULTI(RACE_CP_IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_MAP_ICON:
		Y_STREAMER_MULTI(MAP_ICON_IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_3D_TEXT_LABEL:
		Y_STREAMER_MULTI(3D_TEXT_LABEL_IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_AREA:
		Y_STREAMER_MULTI(AREA_IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_ACTOR:
		Y_STREAMER_MULTI(ACTOR_IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	}
}

HOOK__ Streamer_OnItemStreamOut(type, CB_STREAMER_ALL_TAGS:id, forplayerid)
{
	Y_STREAMER_MULTI(ITEM_OUT, id, Func:cb<iii>)
	{
		@.cb(type, _:id, forplayerid);
	}
	switch (type)
	{
	case STREAMER_TYPE_OBJECT:
		Y_STREAMER_MULTI(OBJECT_OUT, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_PICKUP:
		Y_STREAMER_MULTI(PICKUP_OUT, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_CP:
		Y_STREAMER_MULTI(CP_OUT, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_RACE_CP:
		Y_STREAMER_MULTI(RACE_CP_OUT, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_MAP_ICON:
		Y_STREAMER_MULTI(MAP_ICON_OUT, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_3D_TEXT_LABEL:
		Y_STREAMER_MULTI(3D_TEXT_LABEL_OUT, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_AREA:
		Y_STREAMER_MULTI(AREA_OUT, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_ACTOR:
		Y_STREAMER_MULTI(ACTOR_OUT, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	}
}

HOOK__ Streamer_OnPluginError(const error[])
{
	if (YSI_g_sStreamerError)
	{
		@.YSI_g_sStreamerError(error);
	}
}

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

