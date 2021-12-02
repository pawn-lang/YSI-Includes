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

#if defined E_STREAMER_CUSTOM
	static stock bool:_Streamer_TryGet(type, id, data, &oldValue)
	{
		if (Streamer_HasIntData(type, CB_STREAMER_TAG_OBJECT:id, data))
		{
			oldValue = Streamer_GetIntData(type, CB_STREAMER_TAG_OBJECT:id, data);
			return true;
		}
		return false;
	}

	static stock bool:_Streamer_Exchange0(type, id, data, &oldValue)
	{
		if (Streamer_HasIntData(type, CB_STREAMER_TAG_OBJECT:id, data))
		{
			oldValue = Streamer_GetIntData(type, CB_STREAMER_TAG_OBJECT:id, data);
			Streamer_RemoveIntData(type, CB_STREAMER_TAG_OBJECT:id, data);
			return true;
		}
		return false;
	}

	static stock bool:_Streamer_Exchange1(type, id, data, &oldValue, newValue)
	{
		new bool:ret = Streamer_HasIntData(type, CB_STREAMER_TAG_OBJECT:id, data);
		if (ret)
		{
			oldValue = Streamer_GetIntData(type, CB_STREAMER_TAG_OBJECT:id, data);
		}
		Streamer_SetIntData(type, CB_STREAMER_TAG_OBJECT:id, data, newValue);
		return ret;
	}

	#define Y_STREAMER_CB
	// Store the callback data in `E_STREAMER_CUSTOM`
	#define E_YSI_DYN@OBJECT@MOVED      E_STREAMER_CUSTOM(0x59534900) // YSI 00
	#define E_YSI_DYN@OBJECT@EDITED     E_STREAMER_CUSTOM(0x59534901) // YSI 01
	#define E_YSI_DYN@OBJECT@SELECTED   E_STREAMER_CUSTOM(0x59534902) // YSI 02
	#define E_YSI_DYN@OBJECT@SHOT       E_STREAMER_CUSTOM(0x59534903) // YSI 03
	#define E_YSI_DYN@OBJECT@IN         E_STREAMER_CUSTOM(0x59534904) // YSI 04
	#define E_YSI_DYN@OBJECT@OUT        E_STREAMER_CUSTOM(0x59534905) // YSI 05
	#define E_YSI_DYN@PICKUP@PICKUP     E_STREAMER_CUSTOM(0x59534910) // YSI 10
	#define E_YSI_DYN@PICKUP@IN         E_STREAMER_CUSTOM(0x59534911) // YSI 11
	#define E_YSI_DYN@PICKUP@OUT        E_STREAMER_CUSTOM(0x59534912) // YSI 12
	#define E_YSI_DYN@CP@ENTER          E_STREAMER_CUSTOM(0x59534920) // YSI 20
	#define E_YSI_DYN@CP@LEAVE          E_STREAMER_CUSTOM(0x59534921) // YSI 21
	#define E_YSI_DYN@CP@IN             E_STREAMER_CUSTOM(0x59534922) // YSI 22
	#define E_YSI_DYN@CP@OUT            E_STREAMER_CUSTOM(0x59534923) // YSI 23
	#define E_YSI_DYN@RACE_CP@ENTER     E_STREAMER_CUSTOM(0x59534930) // YSI 30
	#define E_YSI_DYN@RACE_CP@LEAVE     E_STREAMER_CUSTOM(0x59534931) // YSI 31
	#define E_YSI_DYN@RACE_CP@IN        E_STREAMER_CUSTOM(0x59534932) // YSI 32
	#define E_YSI_DYN@RACE_CP@OUT       E_STREAMER_CUSTOM(0x59534933) // YSI 33
	#define E_YSI_DYN@AREA@ENTER        E_STREAMER_CUSTOM(0x59534940) // YSI 40
	#define E_YSI_DYN@AREA@LEAVE        E_STREAMER_CUSTOM(0x59534941) // YSI 41
	#define E_YSI_DYN@AREA@IN           E_STREAMER_CUSTOM(0x59534942) // YSI 42
	#define E_YSI_DYN@AREA@OUT          E_STREAMER_CUSTOM(0x59534943) // YSI 43
	#define E_YSI_DYN@ACTOR@DAMAGE      E_STREAMER_CUSTOM(0x59534950) // YSI 50
	#define E_YSI_DYN@ACTOR@IN          E_STREAMER_CUSTOM(0x59534951) // YSI 51
	#define E_YSI_DYN@ACTOR@OUT         E_STREAMER_CUSTOM(0x59534952) // YSI 52
	#define E_YSI_DYN@MAP_ICON@IN       E_STREAMER_CUSTOM(0x59534960) // YSI 60
	#define E_YSI_DYN@MAP_ICON@OUT      E_STREAMER_CUSTOM(0x59534961) // YSI 61
	#define E_YSI_DYN@3D_TEXT_LABEL@IN  E_STREAMER_CUSTOM(0x59534970) // YSI 70
	#define E_YSI_DYN@3D_TEXT_LABEL@OUT E_STREAMER_CUSTOM(0x59534971) // YSI 71
	//#define E_YSI_DYN@ITEM@IN           E_STREAMER_CUSTOM(0x59534980) // YSI 80
	//#define E_YSI_DYN@ITEM@OUT          E_STREAMER_CUSTOM(0x59534981) // YSI 81

	#define E_STREAMER_YSI(%0,%1) E_YSI_DYN@%0@%1

	#define Y_STREAMER_DESTROY(%0,%9\32;%3,%1) \
		if (_Streamer_Exchange0(STREAMER_TYPE_%0, _:(%1), E_YSI_DYN@%0@%3, cb)) \
			Indirect_Release(cb)

	#define Y_STREAMER_EXCHANGE(%0,%9\32;%3,%1,%2) \
		if (_Streamer_Exchange1(STREAMER_TYPE_%0, _:(%1), E_YSI_DYN@%0@%3, cb, _:(%2))) \
			Indirect_Release(cb)

	#define Y_STREAMER_MULTI(%0,%9\32;%3,%1,%2) \
		for (new %2; __once && _Streamer_TryGet(STREAMER_TYPE_%0, _:(%1), E_YSI_DYN@%0@%3, _:(%2)); )

	#define Y_STREAMER_ONCE(%0,%9\32;%3,%1,%2) \
		for (new %2; __once && _Streamer_Exchange0(STREAMER_TYPE_%0, _:(%1), E_YSI_DYN@%0@%3, _:(%2)); Indirect_Release(_:(%2)))
#else
	// Store the callback data in a per-entity sparse array.
	#include "..\..\YSI_Data\y_sparsearray"
	
	#define Y_STREAMER_CB new cb;

	static stock
		SparseArray:YSI_g_sDyn@OBJECT@MOVED<>,
		SparseArray:YSI_g_sDyn@OBJECT@EDITED<>,
		SparseArray:YSI_g_sDyn@OBJECT@SELECTED<>,
		SparseArray:YSI_g_sDyn@OBJECT@SHOT<>,
		SparseArray:YSI_g_sDyn@OBJECT@IN<>,
		SparseArray:YSI_g_sDyn@OBJECT@OUT<>,
		SparseArray:YSI_g_sDyn@PICKUP@PICKUP<>,
		SparseArray:YSI_g_sDyn@PICKUP@IN<>,
		SparseArray:YSI_g_sDyn@PICKUP@OUT<>,
		SparseArray:YSI_g_sDyn@CP@ENTER<>,
		SparseArray:YSI_g_sDyn@CP@LEAVE<>,
		SparseArray:YSI_g_sDyn@CP@IN<>,
		SparseArray:YSI_g_sDyn@CP@OUT<>,
		SparseArray:YSI_g_sDyn@RACE_CP@ENTER<>,
		SparseArray:YSI_g_sDyn@RACE_CP@LEAVE<>,
		SparseArray:YSI_g_sDyn@RACE_CP@IN<>,
		SparseArray:YSI_g_sDyn@RACE_CP@OUT<>,
		SparseArray:YSI_g_sDyn@AREA@ENTER<>,
		SparseArray:YSI_g_sDyn@AREA@LEAVE<>,
		SparseArray:YSI_g_sDyn@AREA@IN<>,
		SparseArray:YSI_g_sDyn@AREA@OUT<>,
		SparseArray:YSI_g_sDyn@ACTOR@DAMAGE<>,
		SparseArray:YSI_g_sDyn@ACTOR@IN<>,
		SparseArray:YSI_g_sDyn@ACTOR@OUT<>,
		SparseArray:YSI_g_sDyn@MAP_ICON@IN<>,
		SparseArray:YSI_g_sDyn@MAP_ICON@OUT<>,
		SparseArray:YSI_g_sDyn@3D_TEXT_LABEL@IN<>,
		SparseArray:YSI_g_sDyn@3D_TEXT_LABEL@OUT<>;
		//SparseArray:YSI_g_sDyn@ITEM@IN<>,
		//SparseArray:YSI_g_sDyn@ITEM@OUT<>,

	#define Y_STREAMER_DESTROY(%0,%9\32;%3,%1) \
		if (Sparse_Exchange(YSI_g_sDyn@%0@%3, _:(%1), cb)) \
			Indirect_Release(cb)

	#define Y_STREAMER_EXCHANGE(%0,%9\32;%3,%1,%2) \
		if (Sparse_Exchange(YSI_g_sDyn@%0@%3, _:(%1), cb, _:(%2))) \
			Indirect_Release(cb)

	#define Y_STREAMER_MULTI(%0,%9\32;%3,%1,%2) \
		for (new %2; __once && Sparse_TryGet(YSI_g_sDyn@%0@%3, _:(%1), _:(%2)); )

	#define Y_STREAMER_ONCE(%0,%9\32;%3,%1,%2) \
		for (new %2; __once && Sparse_Exchange(YSI_g_sDyn@%0@%3, _:(%1), _:(%2)); Indirect_Release(_:(%2)))
#endif

static stock
	Func:YSI_g_sStreamerError<s>;

stock cb_StopDynamicObject(CB_STREAMER_TAG_OBJECT:objectid)
{
	Y_STREAMER_CB
	Y_STREAMER_DESTROY(OBJECT, MOVED, objectid);
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
	Y_STREAMER_CB
	Y_STREAMER_EXCHANGE(OBJECT, MOVED, objectid, onMoved);
	Indirect_Claim(onMoved);
	return MoveDynamicObject(objectid, x, y, z, speed, rx, ry, rz);
}
/*

      ,ad8888ba,               88  88  88                                   88                    
     d8"'    `"8b              88  88  88                                   88                    
    d8'                        88  88  88                                   88                    
    88             ,adPPYYba,  88  88  88,dPPYba,   ,adPPYYba,   ,adPPYba,  88   ,d8   ,adPPYba,  
    88             ""     `Y8  88  88  88P'    "8a  ""     `Y8  a8"     ""  88 ,a8"    I8[    ""  
    Y8,            ,adPPPPP88  88  88  88       d8  ,adPPPPP88  8b          8888[       `"Y8ba,   
     Y8a.    .a8P  88,    ,88  88  88  88b,   ,a8"  88,    ,88  "8a,   ,aa  88`"Yba,   aa    ]8I  
      `"Y8888Y"'   `"8bbdP"Y8  88  88  8Y"Ybbd8"'   `"8bbdP"Y8   `"Ybbd8"'  88   `Y8a  `"YbbdP"'  



*/

HOOK__ OnDynamicObjectMoved(CB_STREAMER_TAG_OBJECT:objectid)
{
	// This only happens once, then the callback is redundant.  Free it.
	Y_STREAMER_ONCE(OBJECT, MOVED, objectid, Func:cb<i>)
	{
		@.cb(_:objectid);
	}
}

HOOK__ OnPlayerEditDynObject(playerid, CB_STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	Y_STREAMER_MULTI(OBJECT, EDITED, objectid, Func:cb<iiiffffff>)
	{
		@.cb(playerid, _:objectid, response, x, y, z, rx, ry, rz);
	}
}

HOOK__ OnPlayerSelectDynObject(playerid, CB_STREAMER_TAG_OBJECT:objectid, modelid, Float:x, Float:y, Float:z)
{
	Y_STREAMER_MULTI(OBJECT, SELECTED, objectid, Func:cb<iiifff>)
	{
		@.cb(playerid, _:objectid, modelid, x, y, z);
	}
}

HOOK__ OnPlayerShootDynObject(playerid, weaponid, CB_STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z)
{
	Y_STREAMER_MULTI(OBJECT, SHOT, objectid, Func:cb<iiifff>)
	{
		@.cb(playerid, weaponid, _:objectid, x, y, z);
	}
}

HOOK__ OnPlayerPickUpDynPickup(playerid, CB_STREAMER_TAG_PICKUP:pickupid)
{
	Y_STREAMER_MULTI(PICKUP, PICKUP, pickupid, Func:cb<ii>)
	{
		@.cb(playerid, _:pickupid);
	}
}

HOOK__ OnPlayerEnterDynamicCP(playerid, CB_STREAMER_TAG_CP:checkpointid)
{
	Y_STREAMER_MULTI(CP, ENTER, checkpointid, Func:cb<ii>)
	{
		@.cb(playerid, _:checkpointid);
	}
}

HOOK__ OnPlayerLeaveDynamicCP(playerid, CB_STREAMER_TAG_CP:checkpointid)
{
	Y_STREAMER_MULTI(CP, LEAVE, checkpointid, Func:cb<ii>)
	{
		@.cb(playerid, _:checkpointid);
	}
}

HOOK__ OnPlayerEnterDynRaceCP(playerid, CB_STREAMER_TAG_RACE_CP:checkpointid)
{
	Y_STREAMER_MULTI(RACE_CP, ENTER, checkpointid, Func:cb<ii>)
	{
		@.cb(playerid, _:checkpointid);
	}
}

HOOK__ OnPlayerLeaveDynRaceCP(playerid, CB_STREAMER_TAG_RACE_CP:checkpointid)
{
	Y_STREAMER_MULTI(RACE_CP, LEAVE, checkpointid, Func:cb<ii>)
	{
		@.cb(playerid, _:checkpointid);
	}
}

HOOK__ OnPlayerEnterDynArea(playerid, CB_STREAMER_TAG_AREA:areaid)
{
	Y_STREAMER_MULTI(AREA, ENTER, areaid, Func:cb<ii>)
	{
		@.cb(playerid, _:areaid);
	}
}

HOOK__ OnPlayerLeaveDynArea(playerid, CB_STREAMER_TAG_AREA:areaid)
{
	Y_STREAMER_MULTI(AREA, LEAVE, areaid, Func:cb<ii>)
	{
		@.cb(playerid, _:areaid);
	}
}

DEFINE_HOOK_REPLACEMENT__(DynamicActor, DAct);
DEFINE_HOOK_REPLACEMENT__(ItemStream, ItStream);

HOOK__ OnPlayerGiveDamageDAct(playerid, CB_STREAMER_TAG_ACTOR:actorid, Float:amount, weaponid, bodypart)
{
	Y_STREAMER_MULTI(ACTOR, DAMAGE, actorid, Func:cb<iifii>)
	{
		@.cb(playerid, _:actorid, amount, weaponid, bodypart);
	}
}

HOOK__ OnDynamicActorStreamIn(CB_STREAMER_TAG_ACTOR:actorid, forplayerid)
{
	Y_STREAMER_MULTI(ACTOR, IN, actorid, Func:cb<ii>)
	{
		@.cb(_:actorid, forplayerid);
	}
}

HOOK__ OnDynamicActorStreamOut(CB_STREAMER_TAG_ACTOR:actorid, forplayerid)
{
	Y_STREAMER_MULTI(ACTOR, OUT, actorid, Func:cb<ii>)
	{
		@.cb(_:actorid, forplayerid);
	}
}

HOOK__ Streamer_OnItStreamIn(type, CB_STREAMER_ALL_TAGS:id, forplayerid)
{
	//Y_STREAMER_MULTI(ITEM, IN, id, Func:cb<iii>)
	//{
	//	@.cb(type, _:id, forplayerid);
	//}
	switch (type)
	{
	case STREAMER_TYPE_OBJECT:
		Y_STREAMER_MULTI(OBJECT, IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_PICKUP:
		Y_STREAMER_MULTI(PICKUP, IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_CP:
		Y_STREAMER_MULTI(CP, IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_RACE_CP:
		Y_STREAMER_MULTI(RACE_CP, IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_MAP_ICON:
		Y_STREAMER_MULTI(MAP_ICON, IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_3D_TEXT_LABEL:
		Y_STREAMER_MULTI(3D_TEXT_LABEL, IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_AREA:
		Y_STREAMER_MULTI(AREA, IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_ACTOR:
		Y_STREAMER_MULTI(ACTOR, IN, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	}
}

HOOK__ Streamer_OnItStreamOut(type, CB_STREAMER_ALL_TAGS:id, forplayerid)
{
	//Y_STREAMER_MULTI(ITEM, OUT, id, Func:cb<iii>)
	//{
	//	@.cb(type, _:id, forplayerid);
	//}
	switch (type)
	{
	case STREAMER_TYPE_OBJECT:
		Y_STREAMER_MULTI(OBJECT, OUT, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_PICKUP:
		Y_STREAMER_MULTI(PICKUP, OUT, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_CP:
		Y_STREAMER_MULTI(CP, OUT, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_RACE_CP:
		Y_STREAMER_MULTI(RACE_CP, OUT, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_MAP_ICON:
		Y_STREAMER_MULTI(MAP_ICON, OUT, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_3D_TEXT_LABEL:
		Y_STREAMER_MULTI(3D_TEXT_LABEL, OUT, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_AREA:
		Y_STREAMER_MULTI(AREA, OUT, id, Func:cb<ii>)
		{
			@.cb(_:id, forplayerid);
		}
	case STREAMER_TYPE_ACTOR:
		Y_STREAMER_MULTI(ACTOR, OUT, id, Func:cb<ii>)
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

/*

    88888888ba,                                                                          
    88      `"8b                            ,d                                           
    88        `8b                           88                                           
    88         88   ,adPPYba,  ,adPPYba,  MM88MMM  8b,dPPYba,   ,adPPYba,   8b       d8  
    88         88  a8P_____88  I8[    ""    88     88P'   "Y8  a8"     "8a  `8b     d8'  
    88         8P  8PP"""""""   `"Y8ba,     88     88          8b       d8   `8b   d8'   
    88      .a8P   "8b,   ,aa  aa    ]8I    88,    88          "8a,   ,a8"    `8b,d8'    
    88888888Y"'     `"Ybbd8"'  `"YbbdP"'    "Y888  88           `"YbbdP"'       Y88'     
                                                                                d8'      
                                                                               d8'       

*/

stock cb_DestroyDynamicObject(CB_STREAMER_TAG_OBJECT:objectid)
{
	Y_STREAMER_CB
	Y_STREAMER_DESTROY(OBJECT, MOVED, objectid);
	Y_STREAMER_DESTROY(OBJECT, EDITED, objectid);
	Y_STREAMER_DESTROY(OBJECT, SELECTED, objectid);
	Y_STREAMER_DESTROY(OBJECT, SHOT, objectid);
	Y_STREAMER_DESTROY(OBJECT, IN, objectid);
	Y_STREAMER_DESTROY(OBJECT, OUT, objectid);
	return DestroyDynamicObject(objectid);
}

#if defined _ALS_DestroyDynamicObject
	#undef DestroyDynamicObject
#else
	#define _ALS_DestroyDynamicObject
#endif
#define DestroyDynamicObject cb_DestroyDynamicObject

stock cb_DestroyDynamicPickup(STREAMER_TAG_PICKUP:pickupid)
{
	Y_STREAMER_CB
	Y_STREAMER_DESTROY(PICKUP, PICKUP, pickupid);
	Y_STREAMER_DESTROY(PICKUP, IN, pickupid);
	Y_STREAMER_DESTROY(PICKUP, OUT, pickupid);
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
	Y_STREAMER_CB
	Y_STREAMER_DESTROY(CP, ENTER, checkpointid);
	Y_STREAMER_DESTROY(CP, LEAVE, checkpointid);
	Y_STREAMER_DESTROY(CP, IN, checkpointid);
	Y_STREAMER_DESTROY(CP, OUT, checkpointid);
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
	Y_STREAMER_CB
	Y_STREAMER_DESTROY(RACE_CP, ENTER, checkpointid);
	Y_STREAMER_DESTROY(RACE_CP, LEAVE, checkpointid);
	Y_STREAMER_DESTROY(RACE_CP, IN, checkpointid);
	Y_STREAMER_DESTROY(RACE_CP, OUT, checkpointid);
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
	Y_STREAMER_CB
	Y_STREAMER_DESTROY(AREA, ENTER, areaid);
	Y_STREAMER_DESTROY(AREA, LEAVE, areaid);
	Y_STREAMER_DESTROY(AREA, IN, areaid);
	Y_STREAMER_DESTROY(AREA, OUT, areaid);
	return DestroyDynamicArea(areaid);
}

#if defined _ALS_DestroyDynamicArea
	#undef DestroyDynamicArea
#else
	#define _ALS_DestroyDynamicArea
#endif
#define DestroyDynamicArea cb_DestroyDynamicArea

stock cb_DestroyDynamicActor(STREAMER_TAG_ACTOR:actorid)
{
	Y_STREAMER_CB
	Y_STREAMER_DESTROY(ACTOR, DAMAGE, actorid);
	Y_STREAMER_DESTROY(ACTOR, IN, actorid);
	Y_STREAMER_DESTROY(ACTOR, OUT, actorid);
	return DestroyDynamicActor(actorid);
}

#if defined _ALS_DestroyDynamicActor
	#undef DestroyDynamicActor
#else
	#define _ALS_DestroyDynamicActor
#endif
#define DestroyDynamicActor cb_DestroyDynamicActor

stock cb_DestroyDynamicMapIcon(STREAMER_TAG_MAP_ICON:iconid)
{
	Y_STREAMER_CB
	Y_STREAMER_DESTROY(MAP_ICON, IN, iconid);
	Y_STREAMER_DESTROY(MAP_ICON, OUT, iconid);
	return DestroyDynamicMapIcon(iconid);
}

#if defined _ALS_DestroyDynamicMapIcon
	#undef DestroyDynamicMapIcon
#else
	#define _ALS_DestroyDynamicMapIcon
#endif
#define DestroyDynamicMapIcon cb_DestroyDynamicMapIcon

stock cb_DestroyDynamic3DTextLabel(STREAMER_TAG_3D_TEXT_LABEL:id)
{
	Y_STREAMER_CB
	Y_STREAMER_DESTROY(3D_TEXT_LABEL, IN, id);
	Y_STREAMER_DESTROY(3D_TEXT_LABEL, OUT, id);
	return DestroyDynamic3DTextLabel(id);
}

#if defined _ALS_DestroyDynamic3DTextLabel
	#undef DestroyDynamic3DTextLabel
#else
	#define _ALS_DestroyDynamic3DTextLabel
#endif
#define DestroyDynamic3DTextLabel cb_DestroyDynamic3DTextLabel

/*

           db         88  88  
          d88b        88  88  
         d8'`8b       88  88  
        d8'  `8b      88  88  
       d8YaaaaY8b     88  88  
      d8""""""""8b    88  88  
     d8'        `8b   88  88  
    d8'          `8b  88  88  



*/

stock cb_DestroyAllDynamicObjects()
{
	Y_STREAMER_CB
	for (new i = 0, j = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT); i != j; ++i)
	{
		if (IsValidDynamicObject(CB_STREAMER_TAG_OBJECT:i))
		{
			Y_STREAMER_DESTROY(OBJECT, MOVED, i);
			Y_STREAMER_DESTROY(OBJECT, EDITED, i);
			Y_STREAMER_DESTROY(OBJECT, SELECTED, i);
			Y_STREAMER_DESTROY(OBJECT, SHOT, i);
			Y_STREAMER_DESTROY(OBJECT, IN, i);
			Y_STREAMER_DESTROY(OBJECT, OUT, i);
		}
	}
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
	Y_STREAMER_CB
	for (new i = 0, j = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT); i != j; ++i)
	{
		if (IsValidDynamicPickup(CB_STREAMER_TAG_PICKUP:i))
		{
			Y_STREAMER_DESTROY(PICKUP, i);
			Y_STREAMER_DESTROY(PICKUP, IN, i);
			Y_STREAMER_DESTROY(PICKUP, OUT, i);
		}
	}
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
	Y_STREAMER_CB
	for (new i = 0, j = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT); i != j; ++i)
	{
		if (IsValidDynamicCP(CB_STREAMER_TAG_CP:i))
		{
			Y_STREAMER_DESTROY(CP, ENTER, i);
			Y_STREAMER_DESTROY(CP, LEAVE, i);
			Y_STREAMER_DESTROY(CP, IN, i);
			Y_STREAMER_DESTROY(CP, OUT, i);
		}
	}
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
	Y_STREAMER_CB
	for (new i = 0, j = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT); i != j; ++i)
	{
		if (IsValidDynamicRaceCP(CB_STREAMER_TAG_RACE_CP:i))
		{
			Y_STREAMER_DESTROY(RACE_CP, ENTER, i);
			Y_STREAMER_DESTROY(RACE_CP, LEAVE, i);
			Y_STREAMER_DESTROY(RACE_CP, IN, i);
			Y_STREAMER_DESTROY(RACE_CP, OUT, i);
		}
	}
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
	Y_STREAMER_CB
	for (new i = 0, j = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT); i != j; ++i)
	{
		if (IsValidDynamicArea(CB_STREAMER_TAG_AREA:i))
		{
			Y_STREAMER_DESTROY(AREA, ENTER, i);
			Y_STREAMER_DESTROY(AREA, LEAVE, i);
			Y_STREAMER_DESTROY(AREA, IN, i);
			Y_STREAMER_DESTROY(AREA, OUT, i);
		}
	}
	return DestroyAllDynamicAreas();
}

#if defined _ALS_DestroyAllDynamicAreas
	#undef DestroyAllDynamicAreas
#else
	#define _ALS_DestroyAllDynamicAreas
#endif
#define DestroyAllDynamicAreas cb_DestroyAllDynamicAreas

stock cb_DestroyAllDynamicMapIcons()
{
	Y_STREAMER_CB
	for (new i = 0, j = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT); i != j; ++i)
	{
		if (IsValidDynamicMapIcon(CB_STREAMER_TAG_MAP_ICON:i))
		{
			Y_STREAMER_DESTROY(MAP_ICON, IN, i);
			Y_STREAMER_DESTROY(MAP_ICON, OUT, i);
		}
	}
	return DestroyAllDynamicMapIcons();
}

#if defined _ALS_DestroyAllDynamicMapIcons
	#undef DestroyAllDynamicMapIcons
#else
	#define _ALS_DestroyAllDynamicMapIcons
#endif
#define DestroyAllDynamicMapIcons cb_DestroyAllDynamicMapIcons

stock cb_DestroyAllDyn3DTextLabels()
{
	Y_STREAMER_CB
	for (new i = 0, j = Streamer_GetUpperBound(STREAMER_TYPE_OBJECT); i != j; ++i)
	{
		if (IsValidDynamic3DTextLabel(CB_STREAMER_TAG_3D_TEXT_LABEL:i))
		{
			Y_STREAMER_DESTROY(3D_TEXT_LABEL, IN, i);
			Y_STREAMER_DESTROY(3D_TEXT_LABEL, OUT, i);
		}
	}
	return DestroyAllDynamic3DTextLabels();
}

#if defined _ALS_DestroyAllDyn3DTextLabels
	#undef DestroyAllDynamic3DTextLabels
#else
	#define _ALS_DestroyAllDyn3DTextLabels
#endif
#define DestroyAllDynamic3DTextLabels cb_DestroyAllDynDTextLabels

