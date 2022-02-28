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
	#define CB_STREAMER_TAG_OBJECT DynamicObject
#else
	#define CB_STREAMER_TAG_OBJECT _
#endif

#if !defined _ALS_Streamer_HasIntData
	// Push a fake extra parameter.
	native bool:BAD_Streamer_HasIntData(type, STREAMER_ALL_TAGS:id, data, fakeExtraParameter = 0) = Streamer_HasIntData;

	stock bool:YSI_Streamer_HasIntData(type, STREAMER_ALL_TAGS:id, data)
	{
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
	native bool:BAD_Streamer_RemoveIntData(type, STREAMER_ALL_TAGS:id, data, fakeExtraParameter = 0) = Streamer_RemoveIntData;

	stock bool:YSI_Streamer_RemoveIntData(type, STREAMER_ALL_TAGS:id, data)
	{
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

#if defined E_STREAMER_CUSTOM
	#define E_YSI_DYNAMIC_OBJECT_MOVED E_STREAMER_CUSTOM(0x59534921) // YSI!

	forward OnDynamicObjectMoved(CB_STREAMER_TAG_OBJECT:objectid);

	public OnDynamicObjectMoved(CB_STREAMER_TAG_OBJECT:objectid)
	{
		new ret = 0;
		if (Streamer_HasIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_OBJECT_MOVED))
		{
			new Func:cb<i> = Func:Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_OBJECT_MOVED)<i>;
			Streamer_RemoveIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_OBJECT_MOVED);
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
		forward Inline_OnDynamicObjectMoved(CB_STREAMER_TAG_OBJECT:objectid);
	#endif

	// Hook stoping and destroying objects to remove the callbacks.
	stock Inline_StopDynamicObject(CB_STREAMER_TAG_OBJECT:objectid)
	{
		if (Streamer_HasIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_OBJECT_MOVED))
		{
			new Func:cb<i> = Func:Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_OBJECT_MOVED)<i>;
			Streamer_RemoveIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_OBJECT_MOVED);
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
	stock Inline_DestroyDynamicObject(CB_STREAMER_TAG_OBJECT:objectid)
	{
		if (Streamer_HasIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_OBJECT_MOVED))
		{
			new Func:cb<i> = Func:Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_OBJECT_MOVED)<i>;
			Streamer_RemoveIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_OBJECT_MOVED);
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

	stock MoveDynamicObjectCallback(CB_STREAMER_TAG_OBJECT:objectid, Func:onMoved<i>, Float:x, Float:y, Float:z, Float:speed, Float:rx = -1000.0, Float:ry = -1000.0, Float:rz = -1000.0)
	{
		if (Streamer_HasIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_OBJECT_MOVED))
		{
			new Func:cb<i> = Func:Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_OBJECT_MOVED)<i>;
			Indirect_Release(cb);
		}
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_YSI_DYNAMIC_OBJECT_MOVED, _:onMoved);
		Indirect_Claim(onMoved);
		return MoveDynamicObject(objectid, x, y, z, speed, rx, ry, rz);
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
		SparseArray:YSI_g_sDynamicObjectMoved<>;

	forward OnDynamicObjectMoved(CB_STREAMER_TAG_OBJECT:objectid);

	public OnDynamicObjectMoved(CB_STREAMER_TAG_OBJECT:objectid)
	{
		new Func:cb<i>;
		new ret = 0;
		if (Sparse_Exchange(YSI_g_sDynamicObjectMoved, objectid, _:cb))
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
		forward Inline_OnDynamicObjectMoved(CB_STREAMER_TAG_OBJECT:objectid);
	#endif

	// Hook stoping and destroying objects to remove the callbacks.
	stock Inline_StopDynamicObject(CB_STREAMER_TAG_OBJECT:objectid)
	{
		new Func:cb<i>;
		if (Sparse_Exchange(YSI_g_sDynamicObjectMoved, objectid, _:cb))
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
	stock Inline_DestroyDynamicObject(CB_STREAMER_TAG_OBJECT:objectid)
	{
		new Func:cb<i>;
		if (Sparse_Exchange(YSI_g_sDynamicObjectMoved, objectid, _:cb))
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

	stock MoveDynamicObjectCallback(CB_STREAMER_TAG_OBJECT:objectid, Func:onMoved<i>, Float:x, Float:y, Float:z, Float:speed, Float:rx = -1000.0, Float:ry = -1000.0, Float:rz = -1000.0)
	{
		// Swap any old callback for the new one.
		new Func:cb<i>;
		if (Sparse_Exchange(YSI_g_sDynamicObjectMoved, objectid, _:cb, _:onMoved))
		{
			Indirect_Release(cb);
		}
		Indirect_Claim(onMoved);
		return MoveDynamicObject(objectid, x, y, z, speed, rx, ry, rz);
	}
#endif

