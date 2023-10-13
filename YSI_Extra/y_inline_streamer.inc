#if defined _INC_y_inline_streamer
	#endinput
#endif
#define _INC_y_inline_streamer

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

#if !defined _INC_y_inline
	#tryinclude "..\YSI_Coding\y_inline\y_inline_entry"
#endif
#if !defined _INC_y_inline
	#tryinclude "YSI_Coding\y_inline\y_inline_entry"
#endif
#if !defined _INC_y_inline
	#tryinclude "YSI\YSI_Coding\y_inline\y_inline_entry"
#endif
#if !defined _INC_y_inline
	#tryinclude <YSI_Coding\y_inline\y_inline_entry>
#endif
#if !defined _INC_y_inline
	#tryinclude <YSI\YSI_Coding\y_inline\y_inline_entry>
#endif
#if !defined _INC_y_inline
	#error Could not find y_inline
#endif

// In some versions the tags are wrong.
#if defined STREAMER_ENABLE_TAGS
	#define STREAMER_TAG_OBJECT DynamicObject
	#define STREAMER_TAG_PICKUP DynamicPickup
	#define STREAMER_TAG_CP DynamicCP
	#define STREAMER_TAG_RACE_CP DynamicRaceCP
	#define STREAMER_TAG_MAP_ICON DynamicMapIcon
	#define STREAMER_TAG_3D_TEXT_LABEL DynamicText3D
	#define STREAMER_TAG_AREA DynamicArea
	#define STREAMER_TAG_ACTOR DynamicActor
#else
	#define STREAMER_TAG_OBJECT _
	#define STREAMER_TAG_PICKUP _
	#define STREAMER_TAG_CP _
	#define STREAMER_TAG_RACE_CP _
	#define STREAMER_TAG_MAP_ICON _
	#define STREAMER_TAG_AREA _
	#define STREAMER_TAG_ACTOR _

	#if defined STREAMER_REMOVE_TEXT3D_TAG
		#define STREAMER_TAG_3D_TEXT_LABEL _
	#elseif defined STREAMER_USE_DYNAMIC_TEXT3D_TAG
		#define STREAMER_TAG_3D_TEXT_LABEL DynamicText3D
	#else
		#define STREAMER_TAG_3D_TEXT_LABEL Text3D
	#endif
#endif

#if !defined STREAMER_TYPE
	#define STREAMER_TYPE: _:
#endif

#if !defined STREAMER_CP_SD
	#define STREAMER_CP_SD 200.0
#endif

#if !defined _ALS_Streamer_HasIntData
	// Push a fake extra parameter.
	native bool:BAD_Streamer_HasIntData(STREAMER_TYPE:type, STREAMER_ALL_TAGS:id, data, fakeExtraParameter = 0) = Streamer_HasIntData;

	stock bool:YSI_Streamer_HasIntData(STREAMER_TYPE:type, STREAMER_ALL_TAGS:id, data, fakeExtraParameter = 0)
	{
		#pragma unused fakeExtraParameter
		// This isn't a compile-time constant, so we can't use `#if`.
		if (Streamer_IncludeFileVersion > 0x295)
		{
			return bool:Streamer_HasIntData(type, id, data);
		}
		// https://github.com/samp-incognito/samp-streamer-plugin/pull/380
		return BAD_Streamer_HasIntData(type, id, data);
	}

	#define _ALS_Streamer_HasIntData
	#define Streamer_HasIntData( YSI_Streamer_HasIntData(
#endif

#if !defined _ALS_Streamer_RemoveIntData
	// Push a fake extra parameter.
	native bool:BAD_Streamer_RemoveIntData(STREAMER_TYPE:type, STREAMER_ALL_TAGS:id, data, fakeExtraParameter = 0) = Streamer_RemoveIntData;

	stock bool:YSI_Streamer_RemoveIntData(STREAMER_TYPE:type, STREAMER_ALL_TAGS:id, data, fakeExtraParameter = 0)
	{
		#pragma unused fakeExtraParameter
		// This isn't a compile-time constant, so we can't use `#if`.
		if (Streamer_IncludeFileVersion > 0x295)
		{
			return bool:Streamer_RemoveIntData(type, id, data);
		}
		// https://github.com/samp-incognito/samp-streamer-plugin/pull/380
		return BAD_Streamer_RemoveIntData(type, id, data);
	}

	#define _ALS_Streamer_RemoveIntData
	#define Streamer_RemoveIntData( YSI_Streamer_RemoveIntData(
#endif

stock bool:YSI_Streamer_GetFloatData(STREAMER_TYPE:type, STREAMER_ALL_TAGS:id, data, &Float:result)
{
	if (data & 0x40000000)
	{
		// Custom data
		if (Streamer_HasIntData(type, id, data))
		{
			return
				result = Float:Streamer_GetIntData(type, id, data),
				true;
		}
		return false;
	}
	else
	{
		return bool:Streamer_GetFloatData(type, id, data, result);
	}
}

#if defined _ALS_Streamer_GetFloatData
	#undef Streamer_GetFloatData
#endif
#define _ALS_Streamer_GetFloatData
#define Streamer_GetFloatData( YSI_Streamer_GetFloatData(

stock bool:YSI_Streamer_SetFloatData(STREAMER_TYPE:type, STREAMER_ALL_TAGS:id, data, Float:value)
{
	if (data & 0x40000000)
	{
		// Custom data
		return bool:Streamer_SetIntData(type, id, data, _:value);
	}
	else
	{
		return bool:Streamer_SetFloatData(type, id, data, value);
	}
}

#if defined _ALS_Streamer_SetFloatData
	#undef Streamer_SetFloatData
#endif
#define _ALS_Streamer_SetFloatData
#define Streamer_SetFloatData( YSI_Streamer_SetFloatData(

stock bool:YSI_Streamer_HasFloatData(STREAMER_TYPE:type, STREAMER_ALL_TAGS:id, data)
{
	// Custom data
	return (data & 0x40000000) && bool:Streamer_HasIntData(type, id, data);
}

#if defined _ALS_Streamer_HasFloatData
	#undef Streamer_HasFloatData
#endif
#define _ALS_Streamer_HasFloatData
#define Streamer_HasFloatData( YSI_Streamer_HasFloatData(

stock bool:YSI_Streamer_RemoveFloatData(STREAMER_TYPE:type, STREAMER_ALL_TAGS:id, data)
{
	// Custom data
	return (data & 0x40000000) && Streamer_RemoveIntData(type, id, data);
}

#if defined _ALS_Streamer_RemoveFloatData
	#undef Streamer_RemoveFloatData
#endif
#define _ALS_Streamer_RemoveFloatData
#define Streamer_RemoveFloatData( YSI_Streamer_RemoveFloatData(

#if defined E_STREAMER_CUSTOM
	#define E_YSI_DYNAMIC_CALLBACK E_STREAMER_CUSTOM(0x59534921) // YSI!

	forward OnDynamicObjectMoved(STREAMER_TAG_OBJECT:objectid);

	public OnDynamicObjectMoved(STREAMER_TAG_OBJECT:objectid)
	{
		new ret = 0;
		if (Streamer_HasIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_CALLBACK))
		{
			new
				Func:cb<i> = Func:Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_CALLBACK)<i>;
			Streamer_RemoveIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_CALLBACK);
			ret = @.cb();
			Indirect_Release(cb);
		}
		#if defined Inline_OnDynamicObjectMoved
			return Inline_OnDynamicObjectMoved(objectid);
		#else
			return ret;
		#endif
	}

	#if defined _ALS_OnDynamicObjectMoved
		#undef OnDynamicObjectMoved
	#else
		#define _ALS_OnDynamicObjectMoved
	#endif
	#define OnDynamicObjectMoved( Inline_OnDynamicObjectMoved(
	#if defined Inline_OnDynamicObjectMoved
		forward Inline_OnDynamicObjectMoved(STREAMER_TAG_OBJECT:objectid);
	#endif

	// Hook stoping and destroying objects to remove the callbacks.
	stock Inline_StopDynamicObject(STREAMER_TAG_OBJECT:objectid)
	{
		if (Streamer_HasIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_CALLBACK))
		{
			new
				Func:cb<i> = Func:Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_CALLBACK)<i>;
			Streamer_RemoveIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_CALLBACK);
			Indirect_Release(cb);
		}
		return StopDynamicObject(objectid);
	}

	#if defined _ALS_StopDynamicObject
		#undef StopDynamicObject
	#else
		#define _ALS_StopDynamicObject
	#endif
	#define StopDynamicObject( Inline_StopDynamicObject(

	// Hook stoping and destroying objects to remove the callbacks.
	stock Inline_DestroyDynamicObject(STREAMER_TAG_OBJECT:objectid)
	{
		Indirect_Disconnect(Inline_EBC__(_:objectid, tagof (DynamicObject:)));
		if (Streamer_HasIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_CALLBACK))
		{
			new Func:cb<i> = Func:Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_CALLBACK)<i>;
			Streamer_RemoveIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_CALLBACK);
			Indirect_Release(cb);
		}
		return DestroyDynamicObject(objectid);
	}

	#if defined _ALS_DestroyDynamicObject
		#undef DestroyDynamicObject
	#else
		#define _ALS_DestroyDynamicObject
	#endif
	#define DestroyDynamicObject( Inline_DestroyDynamicObject(

	stock MoveDynamicObjectCallback(STREAMER_TAG_OBJECT:objectid, Func:onMoved<i>, Float:x, Float:y, Float:z, Float:speed, Float:rx = -1000.0, Float:ry = -1000.0, Float:rz = -1000.0)
	{
		if (Streamer_HasIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_CALLBACK))
		{
			new
				Func:cb<i> = Func:Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_CALLBACK)<i>;
			Indirect_Release(cb);
		}
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_CALLBACK, _:onMoved);
		Indirect_Claim(onMoved);
		return MoveDynamicObject(objectid, x, y, z, speed, rx, ry, rz);
	}
	
	// Hook destroying CPs to remove the callbacks.
	stock Inline_DestroyDynamicCP(STREAMER_TAG_CP:checkpointid)
	{
		Indirect_Disconnect(Inline_EBC__(_:checkpointid, tagof (DynamicCP:)));
		if (Streamer_HasIntData(STREAMER_TYPE_CP, checkpointid, E_YSI_DYNAMIC_CALLBACK))
		{
			new Func:cb<ii> = Func:Streamer_GetIntData(STREAMER_TYPE_CP, checkpointid, E_YSI_DYNAMIC_CALLBACK)<ii>;
			Streamer_RemoveIntData(STREAMER_TYPE_CP, checkpointid, E_YSI_DYNAMIC_CALLBACK);
			Indirect_Release(cb);
		}
		return DestroyDynamicCP(checkpointid);
	}

	#if defined _ALS_DestroyDynamicCP
		#undef DestroyDynamicCP
	#else
		#define _ALS_DestroyDynamicCP
	#endif
	#define DestroyDynamicCP( Inline_DestroyDynamicCP(

	stock STREAMER_TAG_CP:CreateDynamicCPCallback(Func:onEnter<ii>, Float:x, Float:y, Float:z, Float:size, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_CP_SD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
	{
		// Swap any old callback for the new one.
		new
			STREAMER_TAG_CP:checkpointid = CreateDynamicCP(x, y, z, size, worldid, interiorid, playerid, streamdistance, areaid, priority);
		if (Streamer_HasIntData(STREAMER_TYPE_CP, checkpointid, E_YSI_DYNAMIC_CALLBACK))
		{
			new
				Func:cb<ii> = Func:Streamer_GetIntData(STREAMER_TYPE_CP, checkpointid, E_YSI_DYNAMIC_CALLBACK)<ii>;
			Indirect_Release(cb);
		}
		Streamer_SetIntData(STREAMER_TYPE_CP, checkpointid, E_YSI_DYNAMIC_CALLBACK, _:onEnter);
		Indirect_Claim(onEnter);
		return checkpointid;
	}

	// Hook destroying Pickups to remove the callbacks.
	stock Inline_DestroyDynamicPickup(STREAMER_TAG_PICKUP:pickupid)
	{
		Indirect_Disconnect(Inline_EBC__(_:pickupid, tagof (DynamicPickup:)));
		if (Streamer_HasIntData(STREAMER_TYPE_PICKUP, pickupid, E_YSI_DYNAMIC_CALLBACK))
		{
			new Func:cb<ii> = Func:Streamer_GetIntData(STREAMER_TYPE_PICKUP, pickupid, E_YSI_DYNAMIC_CALLBACK)<ii>;
			Streamer_RemoveIntData(STREAMER_TYPE_PICKUP, pickupid, E_YSI_DYNAMIC_CALLBACK);
			Indirect_Release(cb);
		}
		return DestroyDynamicPickup(pickupid);
	}

	#if defined _ALS_DestroyDynamicPickup
		#undef DestroyDynamicPickup
	#else
		#define _ALS_DestroyDynamicPickup
	#endif
	#define DestroyDynamicPickup( Inline_DestroyDynamicPickup(

	stock STREAMER_TAG_PICKUP:CreateDynamicPickupCallback(Func:onEnter<ii>, modelid, type, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_PICKUP_SD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
	{
		// Swap any old callback for the new one.
		new
			STREAMER_TAG_PICKUP:pickupid = CreateDynamicPickup(modelid, type, x, y, z, worldid, interiorid, playerid, streamdistance, areaid, priority);
		if (Streamer_HasIntData(STREAMER_TYPE_PICKUP, pickupid, E_YSI_DYNAMIC_CALLBACK))
		{
			new
				Func:cb<ii> = Func:Streamer_GetIntData(STREAMER_TYPE_PICKUP, pickupid, E_YSI_DYNAMIC_CALLBACK)<ii>;
			Indirect_Release(cb);
		}
		Streamer_SetIntData(STREAMER_TYPE_PICKUP, pickupid, E_YSI_DYNAMIC_CALLBACK, _:onEnter);
		Indirect_Claim(onEnter);
		return pickupid;
	}

	// Hook destroying RaceCPs to remove the callbacks.
	stock Inline_DestroyDynamicRaceCP(STREAMER_TAG_RACE_CP:checkpointid)
	{
		Indirect_Disconnect(Inline_EBC__(_:checkpointid, tagof (DynamicRaceCP:)));
		if (Streamer_HasIntData(STREAMER_TYPE_RACE_CP, checkpointid, E_YSI_DYNAMIC_CALLBACK))
		{
			new Func:cb<ii> = Func:Streamer_GetIntData(STREAMER_TYPE_RACE_CP, checkpointid, E_YSI_DYNAMIC_CALLBACK)<ii>;
			Streamer_RemoveIntData(STREAMER_TYPE_RACE_CP, checkpointid, E_YSI_DYNAMIC_CALLBACK);
			Indirect_Release(cb);
		}
		return DestroyDynamicRaceCP(checkpointid);
	}

	#if defined _ALS_DestroyDynamicRaceCP
		#undef DestroyDynamicRaceCP
	#else
		#define _ALS_DestroyDynamicRaceCP
	#endif
	#define DestroyDynamicRaceCP( Inline_DestroyDynamicRaceCP(

	stock STREAMER_TAG_RACE_CP:CreateDynamicRaceCPCallback(Func:onEnter<ii>, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_RACE_CP_SD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
	{
		// Swap any old callback for the new one.
		new
			STREAMER_TAG_RACE_CP:checkpointid = CreateDynamicRaceCP(type, x, y, z, nextx, nexty, nextz, size, worldid, interiorid, playerid, streamdistance, areaid, priority);
		if (Streamer_HasIntData(STREAMER_TYPE_RACE_CP, checkpointid, E_YSI_DYNAMIC_CALLBACK))
		{
			new
				Func:cb<ii> = Func:Streamer_GetIntData(STREAMER_TYPE_RACE_CP, checkpointid, E_YSI_DYNAMIC_CALLBACK)<ii>;
			Indirect_Release(cb);
		}
		Streamer_SetIntData(STREAMER_TYPE_RACE_CP, checkpointid, E_YSI_DYNAMIC_CALLBACK, _:onEnter);
		Indirect_Claim(onEnter);
		return checkpointid;
	}

	// Hook destroying Areas to remove the callbacks.
	stock Inline_DestroyDynamicArea(STREAMER_TAG_AREA:areaid)
	{
		Indirect_Disconnect(Inline_EBC__(_:areaid, tagof (DynamicArea:)));
		if (Streamer_HasIntData(STREAMER_TYPE_AREA, areaid, E_YSI_DYNAMIC_CALLBACK))
		{
			new Func:cb<ii> = Func:Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_YSI_DYNAMIC_CALLBACK)<ii>;
			Streamer_RemoveIntData(STREAMER_TYPE_AREA, areaid, E_YSI_DYNAMIC_CALLBACK);
			Indirect_Release(cb);
		}
		return DestroyDynamicArea(areaid);
	}

	static stock STREAMER_TAG_AREA:Inline_CreateAreaCallback(Func:onEnter<ii>, STREAMER_TAG_AREA:areaid)
	{
		// Swap any old callback for the new one.
		if (Streamer_HasIntData(STREAMER_TYPE_AREA, areaid, E_YSI_DYNAMIC_CALLBACK))
		{
			new
				Func:cb<ii> = Func:Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_YSI_DYNAMIC_CALLBACK)<ii>;
			Indirect_Release(cb);
		}
		Streamer_SetIntData(STREAMER_TYPE_AREA, areaid, E_YSI_DYNAMIC_CALLBACK, _:onEnter);
		Indirect_Claim(onEnter);
		return areaid;
	}
#else
	#if !defined _INC_y_sparsearray
		#tryinclude "..\YSI_Data\y_sparsearray\y_sparsearray_entry"
	#endif
	#if !defined _INC_y_sparsearray
		#tryinclude "YSI_Data\y_sparsearray\y_sparsearray_entry"
	#endif
	#if !defined _INC_y_sparsearray
		#tryinclude "YSI\YSI_Data\y_sparsearray\y_sparsearray_entry"
	#endif
	#if !defined _INC_y_sparsearray
		#tryinclude <YSI_Data\y_sparsearray\y_sparsearray_entry>
	#endif
	#if !defined _INC_y_sparsearray
		#tryinclude <YSI\YSI_Data\y_sparsearray\y_sparsearray_entry>
	#endif
	#if !defined _INC_y_sparsearray
		#error Could not find y_sparsearray
	#endif

	static stock
		SparseArray:YSI_g_sDynamicObjectMoved<>,
		SparseArray:YSI_g_sDynamicCP<>,
		SparseArray:YSI_g_sDynamicRaceCP<>,
		SparseArray:YSI_g_sDynamicPickup<>,
		SparseArray:YSI_g_sDynamicArea<>;

	forward OnDynamicObjectMoved(STREAMER_TAG_OBJECT:objectid);

	public OnDynamicObjectMoved(STREAMER_TAG_OBJECT:objectid)
	{
		new
			Func:cb<i>,
			ret = 0;
		if (Sparse_Exchange(YSI_g_sDynamicObjectMoved, _:objectid, _:cb))
		{
			ret = @.cb();
			Indirect_Release(cb);
		}
		#if defined Inline_OnDynamicObjectMoved
			return Inline_OnDynamicObjectMoved(objectid);
		#else
			return ret;
		#endif
	}

	#if defined _ALS_OnDynamicObjectMoved
		#undef OnDynamicObjectMoved
	#else
		#define _ALS_OnDynamicObjectMoved
	#endif
	#define OnDynamicObjectMoved( Inline_OnDynamicObjectMoved(
	#if defined Inline_OnDynamicObjectMoved
		forward Inline_OnDynamicObjectMoved(STREAMER_TAG_OBJECT:objectid);
	#endif

	// Hook stoping and destroying objects to remove the callbacks.
	stock Inline_StopDynamicObject(STREAMER_TAG_OBJECT:objectid)
	{
		new
			Func:cb<i>;
		if (Sparse_Exchange(YSI_g_sDynamicObjectMoved, _:objectid, _:cb))
		{
			Indirect_Release(cb);
		}
		return StopDynamicObject(objectid);
	}

	#if defined _ALS_StopDynamicObject
		#undef StopDynamicObject
	#else
		#define _ALS_StopDynamicObject
	#endif
	#define StopDynamicObject( Inline_StopDynamicObject(

	// Hook stoping and destroying objects to remove the callbacks.
	stock Inline_DestroyDynamicObject(STREAMER_TAG_OBJECT:objectid)
	{
		Indirect_Disconnect(Inline_EBC__(_:objectid, tagof (DynamicObject:)));
		new
			Func:cb<i>;
		if (Sparse_Exchange(YSI_g_sDynamicObjectMoved, _:objectid, _:cb))
		{
			Indirect_Release(cb);
		}
		return DestroyDynamicObject(objectid);
	}

	#if defined _ALS_DestroyDynamicObject
		#undef DestroyDynamicObject
	#else
		#define _ALS_DestroyDynamicObject
	#endif
	#define DestroyDynamicObject( Inline_DestroyDynamicObject(

	stock MoveDynamicObjectCallback(STREAMER_TAG_OBJECT:objectid, Func:onMoved<i>, Float:x, Float:y, Float:z, Float:speed, Float:rx = -1000.0, Float:ry = -1000.0, Float:rz = -1000.0)
	{
		// Swap any old callback for the new one.
		new
			Func:cb<i>;
		if (Sparse_Exchange(YSI_g_sDynamicObjectMoved, _:objectid, _:cb, _:onMoved))
		{
			Indirect_Release(cb);
		}
		Indirect_Claim(onMoved);
		return MoveDynamicObject(objectid, x, y, z, speed, rx, ry, rz);
	}

	// Hook destroying CPs to remove the callbacks.
	stock Inline_DestroyDynamicCP(STREAMER_TAG_CP:checkpointid)
	{
		Indirect_Disconnect(Inline_EBC__(_:checkpointid, tagof (DynamicCP:)));
		new
			Func:cb<ii>;
		if (Sparse_Exchange(YSI_g_sDynamicCP, _:checkpointid, _:cb))
		{
			Indirect_Release(cb);
		}
		return DestroyDynamicCP(checkpointid);
	}

	#if defined _ALS_DestroyDynamicCP
		#undef DestroyDynamicCP
	#else
		#define _ALS_DestroyDynamicCP
	#endif
	#define DestroyDynamicCP( Inline_DestroyDynamicCP(

	stock STREAMER_TAG_CP:CreateDynamicCPCallback(Func:onEnter<ii>, Float:x, Float:y, Float:z, Float:size, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_CP_SD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
	{
		// Swap any old callback for the new one.
		new
			STREAMER_TAG_CP:checkpointid = CreateDynamicCP(x, y, z, size, worldid, interiorid, playerid, streamdistance, areaid, priority),
			Func:cb<ii>;
		if (Sparse_Exchange(YSI_g_sDynamicCP, checkpointid, _:cb, _:onEnter))
		{
			Indirect_Release(cb);
		}
		Indirect_Claim(onEnter);
		return checkpointid;
	}

	// Hook destroying Pickups to remove the callbacks.
	stock Inline_DestroyDynamicPickup(STREAMER_TAG_PICKUP:pickupid)
	{
		Indirect_Disconnect(Inline_EBC__(_:pickupid, tagof (DynamicPickup:)));
		new
			Func:cb<ii>;
		if (Sparse_Exchange(YSI_g_sDynamicPickup, _:pickupid, _:cb))
		{
			Indirect_Release(cb);
		}
		return DestroyDynamicPickup(pickupid);
	}

	#if defined _ALS_DestroyDynamicPickup
		#undef DestroyDynamicPickup
	#else
		#define _ALS_DestroyDynamicPickup
	#endif
	#define DestroyDynamicPickup( Inline_DestroyDynamicPickup(

	stock STREAMER_TAG_PICKUP:CreateDynamicPickupCallback(Func:onEnter<ii>, modelid, type, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_PICKUP_SD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
	{
		// Swap any old callback for the new one.
		new
			STREAMER_TAG_PICKUP:pickupid = CreateDynamicPickup(modelid, type, x, y, z, worldid, interiorid, playerid, streamdistance, areaid, priority),
			Func:cb<ii>;
		if (Sparse_Exchange(YSI_g_sDynamicPickup, pickupid, _:cb, _:onEnter))
		{
			Indirect_Release(cb);
		}
		Indirect_Claim(onEnter);
		return pickupid;
	}

	// Hook destroying RaceCPs to remove the callbacks.
	stock Inline_DestroyDynamicRaceCP(STREAMER_TAG_RACE_CP:checkpointid)
	{
		Indirect_Disconnect(Inline_EBC__(_:checkpointid, tagof (DynamicRaceCP:)));
		new
			Func:cb<ii>;
		if (Sparse_Exchange(YSI_g_sDynamicRaceCP, _:checkpointid, _:cb))
		{
			Indirect_Release(cb);
		}
		return DestroyDynamicRaceCP(checkpointid);
	}

	#if defined _ALS_DestroyDynamicRaceCP
		#undef DestroyDynamicRaceCP
	#else
		#define _ALS_DestroyDynamicRaceCP
	#endif
	#define DestroyDynamicRaceCP( Inline_DestroyDynamicRaceCP(

	stock STREAMER_TAG_RACE_CP:CreateDynamicRaceCPCallback(Func:onEnter<ii>, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_RACE_CP_SD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
	{
		// Swap any old callback for the new one.
		new
			STREAMER_TAG_RACE_CP:checkpointid = CreateDynamicRaceCP(type, x, y, z, nextx, nexty, nextz, size, worldid, interiorid, playerid, streamdistance, areaid, priority),
			Func:cb<ii>;
		if (Sparse_Exchange(YSI_g_sDynamicRaceCP, checkpointid, _:cb, _:onEnter))
		{
			Indirect_Release(cb);
		}
		Indirect_Claim(onEnter);
		return checkpointid;
	}

	// Hook destroying Areas to remove the callbacks.
	stock Inline_DestroyDynamicArea(STREAMER_TAG_AREA:areaid)
	{
		Indirect_Disconnect(Inline_EBC__(_:areaid, tagof (DynamicArea:)));
		new
			Func:cb<ii>;
		if (Sparse_Exchange(YSI_g_sDynamicArea, _:areaid, _:cb))
		{
			Indirect_Release(cb);
		}
		return DestroyDynamicArea(areaid);
	}

	#if defined _ALS_DestroyDynamicArea
		#undef DestroyDynamicArea
	#else
		#define _ALS_DestroyDynamicArea
	#endif
	#define DestroyDynamicArea( Inline_DestroyDynamicArea(
	
	static stock STREAMER_TAG_AREA:Inline_CreateAreaCallback(Func:onEnter<ii>, STREAMER_TAG_AREA:areaid)
	{
		// Swap any old callback for the new one.
		new
			Func:cb<ii>;
		if (Sparse_Exchange(YSI_g_sDynamicArea, areaid, _:cb, _:onEnter))
		{
			Indirect_Release(cb);
		}
		Indirect_Claim(onEnter);
		return areaid;
	}
#endif

// Hook destroying MapIcons to remove the callbacks.
stock Inline_DestroyDynamicMapIcon(STREAMER_TAG_MAP_ICON:iconid)
{
	Indirect_Disconnect(Inline_EBC__(_:iconid, tagof (DynamicMapIcon:)));
	return DestroyDynamicMapIcon(iconid);
}

#if defined _ALS_DestroyDynamicMapIcon
	#undef DestroyDynamicMapIcon
#else
	#define _ALS_DestroyDynamicMapIcon
#endif
#define DestroyDynamicMapIcon( Inline_DestroyDynamicMapIcon(

// Hook destroying 3DTextLabels to remove the callbacks.
stock Inline_DestroyDynamic3DTextLabel(STREAMER_TAG_3D_TEXT_LABEL:id)
{
	Indirect_Disconnect(Inline_EBC__(_:id, tagof (DynamicText3D:)));
	return DestroyDynamic3DTextLabel(id);
}

#if defined _ALS_DestroyDynamic3DTextLabel
	#undef DestroyDynamic3DTextLabel
#else
	#define _ALS_DestroyDynamic3DTextLabel
#endif
#define DestroyDynamic3DTextLabel( Inline_DestroyDynamic3DTextLabel(

// Hook destroying Actors to remove the callbacks.
stock Inline_DestroyDynamicActor(STREAMER_TAG_ACTOR:actorid)
{
	Indirect_Disconnect(Inline_EBC__(_:actorid, tagof (DynamicActor:)));
	return DestroyDynamicActor(actorid);
}

#if defined _ALS_DestroyDynamicActor
	#undef DestroyDynamicActor
#else
	#define _ALS_DestroyDynamicActor
#endif
#define DestroyDynamicActor( Inline_DestroyDynamicActor(

stock STREAMER_TAG_AREA:CreateDynamicCircleCallback(Func:onEnter<ii>, Float:x, Float:y, Float:size, worldid = -1, interiorid = -1, playerid = -1, priority = 0)
{
	return Inline_CreateAreaCallback(onEnter, CreateDynamicCircle(x, y, size, worldid, interiorid, playerid, priority));
}

stock STREAMER_TAG_AREA:CreateDynamicCylinderCallback(Func:onEnter<ii>, Float:x, Float:y, Float:minz, Float:maxz, Float:size, worldid = -1, interiorid = -1, playerid = -1, priority = 0)
{
	return Inline_CreateAreaCallback(onEnter, CreateDynamicCylinder(x, y, minz, maxz, size, worldid, interiorid, playerid, priority));
}

stock STREAMER_TAG_AREA:CreateDynamicSphereCallback(Func:onEnter<ii>, Float:x, Float:y, Float:z, Float:size, worldid = -1, interiorid = -1, playerid = -1, priority = 0)
{
	return Inline_CreateAreaCallback(onEnter, CreateDynamicSphere(x, y, z, size, worldid, interiorid, playerid, priority));
}

stock STREAMER_TAG_AREA:CreateDynamicRectangleCallback(Func:onEnter<ii>, Float:minx, Float:miny, Float:maxx, Float:maxy, worldid = -1, interiorid = -1, playerid = -1, priority = 0)
{
	return Inline_CreateAreaCallback(onEnter, CreateDynamicRectangle(minx, miny, maxx, maxy, worldid, interiorid, playerid, priority));
}

stock STREAMER_TAG_AREA:CreateDynamicCuboidCallback(Func:onEnter<ii>, Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, worldid = -1, interiorid = -1, playerid = -1, priority = 0)
{
	return Inline_CreateAreaCallback(onEnter, CreateDynamicCuboid(minx, miny, minz, maxx, maxy, maxz, worldid, interiorid, playerid, priority));
}

stock STREAMER_TAG_AREA:CreateDynamicCubeCallback(Func:onEnter<ii>, Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, worldid = -1, interiorid = -1, playerid = -1, priority = 0)
{
	return Inline_CreateAreaCallback(onEnter, CreateDynamicCube(minx, miny, minz, maxx, maxy, maxz, worldid, interiorid, playerid, priority));
}

stock STREAMER_TAG_AREA:CreateDynamicPolygonCallback(Func:onEnter<ii>, const Float:points[], Float:minz = -FLOAT_INFINITY, Float:maxz = FLOAT_INFINITY, maxpoints = sizeof (points), worldid = -1, interiorid = -1, playerid = -1, priority = 0)
{
	return Inline_CreateAreaCallback(onEnter, CreateDynamicPolygon(points, minz, maxz, maxpoints, worldid, interiorid, playerid, priority));
}

