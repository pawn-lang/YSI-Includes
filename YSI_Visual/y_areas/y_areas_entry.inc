#if defined _INC_y_areas
	#endinput
#endif
#define _INC_y_areas

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

#include "..\..\YSI_Core\y_utils"

#include "..\..\YSI_Data\y_bit"
#include "..\..\YSI_Data\y_playerarray"

#include "..\..\YSI_Data\y_iterate"

#include "..\..\YSI_Coding\y_inline"
#include "..\..\YSI_Coding\y_remote"

#if defined AREAS_USE_TIMER
	#include "..\..\YSI_Coding\y_timers"
#endif

#if !defined MAX_AREAS
	#define MAX_AREAS (1024)
// Now supports as many as you want (pretty much), and in a VASTLY better way!
#elseif MAX_AREAS >= 0x3FFFF
	#error This version does not support more than 262142 areas.
#endif

#define Y_AREAS_GROUP_NAME<%0...%1> %0Area%1
#define Y_AREAS_GROUP_LIMIT         MAX_AREAS
#define Y_AREAS_GROUP_TAG           _
#include "..\..\YSI_Players\y_groups\y_groups__include"

// Set commands as master 50.
#define MASTER 50
#define YSIM_U_DISABLE
#include "..\..\YSI_Core\y_master"

#include "..\..\YSI_Coding\y_hooks"

stock _YSI_HAS_y_areas(_do_not_call_me_ever_, _like_never_)
{
	P:E("You called _YSI_HAS_y_areas!  Bad, don't do that!", _do_not_call_me_ever_, _like_never_);
	assert(false);
	return 0;
}

#define NO_AREA          (-1)
//#define SINGLE_SLOT_AREA (e_AREA_FLAGS_NEXT)
#define AREA_NO_NEXT     (_:e_AREA_FLAGS_NEXT)

// This will divide the world up in to 400 blocks, the fact that 400=400 is
// PURE fluke.  Setting this to 500 would result in 256 blocks:
//  
//  ((AREAS_ZONE_BOUNDS / AREAS_ZONE_SIZE) ** 2) * 4
//  
#if !defined AREAS_ZONE_SIZE
	#define AREAS_ZONE_SIZE 400
#endif

#if !defined AREAS_ZONE_BOUNDS
	#define AREAS_ZONE_BOUNDS 4000
#endif

// You can of course have more, but if you do have more the extras will be dealt
// with separately.  I can see three happening sometimes, but not often.  More
// than that will probably be very rare, and less will be more common, so we can
// use the third slot usually to store the "NO_AREA" terminator.
#if !defined AREAS_MAX_OVERLAPS
	#define AREAS_MAX_OVERLAPS (3)
#endif

#define AREAS_ZONE_ARRAY (ceildiv(AREAS_ZONE_BOUNDS * 2, AREAS_ZONE_SIZE))

#if !defined AREA_WORLDS
	#define AREA_WORLDS 256
#endif

#define AREAS_ZONE_PARTS (ceildiv(AREAS_ZONE_BOUNDS, AREAS_ZONE_SIZE))
#define Area_MakeZone(%0) (floatround((%0) / AREAS_ZONE_SIZE.0, floatround_floor)) // - AREAS_ZONE_PARTS)

#define _AREAS_ADD_TO_ZONE(%0,%1,%2,%3) YSI_g_sAreas[%2][E_AREA_FLAGS]=(YSI_g_sAreas[%2][E_AREA_FLAGS]&e_AREA_FLAGS_REST)|(e_AREA_FLAGS:%0&e_AREA_FLAGS_NEXT|e_AREA_FLAGS:(%3<<18)&e_AREA_FLAGS_ZONE),%0=%1

//#define _AREAS_ZONES_O(%0) return e_AREA_ZONE_O_%0
//#define _AREAS_ZONES_I(%0) return e_AREA_ZONE_I_%0
//#define _AREAS_ZONES_X(%0) return e_AREA_ZONE_X_%0

#define _AREAS_ZONES_O(%0) return _AREAS_ADD_TO_ZONE(YSI_g_sZoneO%0,area,last,e_AREA_ZONE_O_%0)
#define _AREAS_ZONES_I(%0) return _AREAS_ADD_TO_ZONE(YSI_g_sZoneI%0,area,last,e_AREA_ZONE_I_%0)
#define _AREAS_ZONES_X(%0) return _AREAS_ADD_TO_ZONE(YSI_g_sZoneX%0,area,last,e_AREA_ZONE_X_%0)

#define _AREAS_ZONES_I_GRID zx=1// zx=Area_MakeZone(minx);zy=Area_MakeZone(miny);if(zx==Area_MakeZone(maxx)&&zy==Area_MakeZone(maxy))return _AREAS_MAKE_ZONE(zx,zy),_AREAS_ADD_TO_ZONE(YSI_g_sZones[zy],area,last,zy)

#define _AREAS_MAKE_ZONE(%0,%1) %1+=((%0)+AREAS_ZONE_PARTS)*AREAS_ZONE_ARRAY+AREAS_ZONE_PARTS

//#define _AREA_DO_ALL(%0) sCur=%0;while(sCur!=AREA_NO_NEXT)if(Area_CheckArea(playerid,sW,sCur,sX,sY,sZ))return Area_DoEnter(playerid,(YSI_g_sPlayerArea[playerid]=sCur))
#define _AREA_DO_ALL(%0) sNext=%0;while((sCur=sNext)!=AREA_NO_NEXT)if(Area_CheckArea(playerid,sW,sCur,sX,sY,sZ,sNext,sAreas,sAlready))Area_DoEnter(playerid,sCur,in)

/*#define _AREA_DO_ALL(%0) 
sCur = zone;
while (sCur != AREA_NO_NEXT)
	if (Area_CheckArea(playerid, sW, sCur, sX, sY, sZ))
		return Area_DoEnter(playerid, (YSI_g_sPlayerArea[playerid] = sCur));
*/

#define _AREAS_DO_REMOVE(%0,%1,%2) new __z=-1,__y=%0;while(__y!=%1)__z=__y,__y=_:(YSI_g_sAreas[__z][E_AREA_FLAGS] & e_AREA_FLAGS_NEXT);return ((__z==-1)?(%0=%2):(_:(YSI_g_sAreas[__z][E_AREA_FLAGS]=YSI_g_sAreas[__z][E_AREA_FLAGS]&e_AREA_FLAGS_I_NEXT|(e_AREA_FLAGS:%2&e_AREA_FLAGS_NEXT))))

enum e_AREA_FLAGS:
{
	// These aren't used any more either, they get encoded in the "POS" array
	// (sort of) with polys.
	//e_AREA_FLAGS_NEXT   = 0x2000 - 1 <<  0, //0x00001FFF,
	e_AREA_FLAGS_NEXT   = 0x0003FFFF,
	//e_AREA_FLAGS_ZONE   = 1023 << 18, //0x0FFC0000,
	e_AREA_FLAGS_ZONE   = 0x0FFC0000,
	e_AREA_FLAGS_I_NEXT = ~(e_AREA_FLAGS_NEXT),
	e_AREA_FLAGS_REST   = ~(e_AREA_FLAGS_NEXT | e_AREA_FLAGS_ZONE),
	//e_AREA_FLAGS_TYPE   = 0x38000000,
	e_AREA_FLAGS_SPHERE = 1 << 28, //0x08000000,
	e_AREA_FLAGS_POLY   = 2 << 28, //0x10000000,
	e_AREA_FLAGS_CUBE   = 3 << 28, //0x18000000,
	//e_AREA_FLAGS_BOX    = 4 << 28, //0x20000000,
	e_AREA_FLAGS_OVOID  = 4 << 28, //0x08000000,
	e_AREA_FLAGS_OVAL = 5 << 28, //0x28000000,
	// The reserved type is now in use as a poly area child.
	//e_AREA_FLAGS_RES_0  = 6 << 28, //0x28000000,
	e_AREA_FLAGS_CHILD  = 6 << 28, //0x30000000,
	e_AREA_FLAGS_CIRCLE = 7 << 28, //0x30000000,
	// Type mask.
	e_AREA_FLAGS_UNUSED = 0b000 << 28, //0x00000000,
	e_AREA_FLAGS_TYPE   = 0b111 << 28, //0x38000000,
	// The "USED" flag isn't really needed any more, it's encoded in the type.
	// It seems the "used" flag was never read anyway...
	e_AREA_FLAGS_ACTIVE = 1 << 31,
	//e_AREA_FLAGS_USED   = 1 << 31
	// If this is true AND AREA_VERY_FAST is on, the bounds check is identical
	// to the sphere check, so only do one.
	//e_AREA_FLAGS_BOUNDS = 1 << 31
	//e_AREA_FLAGS_SPHERE   = 1 << 31
}

// Go backwards, so these all have the upper bit set.
enum (+= -1)
{
	e_AREA_ZONE_I_N = -1,
	e_AREA_ZONE_I_NE, // -2
	e_AREA_ZONE_I_E,  // -3
	e_AREA_ZONE_I_SE, // -4
	e_AREA_ZONE_I_S,  // -5
	e_AREA_ZONE_I_SW, // -6
	e_AREA_ZONE_I_W,  // -7
	e_AREA_ZONE_I_NW, // -8
	e_AREA_ZONE_I_,   // -9
	// "Outer" zones.  -4000 > x, y > 4000;
	e_AREA_ZONE_O_N,  // -10
	e_AREA_ZONE_O_NE, // -11
	e_AREA_ZONE_O_E,  // -12
	e_AREA_ZONE_O_SE, // -13
	e_AREA_ZONE_O_S,  // -14
	e_AREA_ZONE_O_SW, // -15
	e_AREA_ZONE_O_W,  // -16
	e_AREA_ZONE_O_NW, // -17
	//e_AREA_ZONE_O_,   // Can't be in all of O, but none of I.
	// "Extra" zones.  In a quadrant, but spanning the +-4000 boundary.
	e_AREA_ZONE_X_N,  // -18
	e_AREA_ZONE_X_NE, // -19
	e_AREA_ZONE_X_E,  // -20
	e_AREA_ZONE_X_SE, // -21
	e_AREA_ZONE_X_S,  // -22
	e_AREA_ZONE_X_SW, // -23
	e_AREA_ZONE_X_W,  // -24
	e_AREA_ZONE_X_NW, // -25
	// Extra zones.  For when areas are too big for a quadrant.
	e_AREA_ZONE_X_,   // -26
	e_AREA_ZONE_NONE = cellmin
}

// =============================================================================
// =============================================================================
// IMPORTANT NOTE: The order of elements in this enum is INCREDIBLY important.
// Because this is three enums in one, they share some pieces of data that must
// not get overridden.
// =============================================================================
// =============================================================================
// This might just be the most complex enum I've ever made!
enum E_AREA
{
	//union
	//{
	//    struct
	//    {
			#if YSIM_HAS_MASTER
				E_AREA_MASTER,
			#endif
			// This has increased from 4 to 6, so we can store cubes and ovoids
			// in a single slot.
			Float:E_AREA_POS[6],
			PlayerArray:E_AREA_PLAYERS<MAX_PLAYERS>,
			// This MUST go between "E_AREA_PLAYERS" and "E_AREA_FLAGS" to
			// remain constant in subsequent unions.
			//#if defined AREA_VERY_FAST
			//	Float:E_AREA_BOUNDING[4],
			//#endif
			// As must this.
			#if AREA_WORLDS > 0
				BitArray:E_AREA_WORLDS<AREA_WORLDS>,
			#endif
			// ALWAYS last (actually used by EVERY type).
			e_AREA_FLAGS:E_AREA_FLAGS,
	//    }
	//    // Start of poly data.
	//    struct
	//    {
			// Reset the enum counter to 0 (on the next item).
			_E_AREA_RESET_@1 = -1,
			// Now restart.
			#if YSIM_HAS_MASTER
				// Skip the master flag if it exists.
				_E_AREA_MASTER_@1,
			#endif
			// This is where polys differ from all others.
			E_AREA_POLY_COUNT,
			E_AREA_POLY_NEXT,
			//Float:E_AREA_POLY_POS[4],
			// This slot holds ONLY the polygon bounding data, it doesn't hold
			// any co-ordinates AT ALL.
			//Float:E_AREA_BOUNDING[4],
			Float:E_AREA_POLY_BOUND_X,
			Float:E_AREA_POLY_BOUND_Y,
			Float:E_AREA_POLY_BOUND_R,
			Float:E_AREA_POLY_BOUND_H,
			// Skip all the array and flag data, they stay the same.
			_E_AREA_ARRAYS_@1[E_AREA_FLAGS - E_AREA_PLAYERS],
			// Skip the flags.
			E_AREA_UNUSED_NEXT,
	//    }
	//    // Start of poly child data.
	//    struct
	//    {
			// Reset the enum counter to 0 (on the next item).
			_E_AREA_RESET_@2 = -1,
			// Now restart.
			#if YSIM_HAS_MASTER
				// Skip the master flag if it exists.
				_E_AREA_MASTER_@2,
			#endif
			// Store a link to the parent of this poly child.
			E_AREA_CHILD_PARENT,
			// And the next one in VERY rare cases (I hope).
			// THIS SHARES A SLOT WITH "E_AREA_POLY_NEXT", so we can always just
			// use that slot when iterating.
			#if _:(E_AREA_FLAGS - E_AREA_CHILD_PARENT) & 1
				// There are an ODD number of available slots.  We can store an
				// extra pair iff we don't need to use "NEXT".
				//_E_AREA_SKIP_@2,
				E_AREA_CHILD_OPT_Y,
			#endif
			E_AREA_CHILD_OPT_X,
			// Just store a vast number of X/Y pairs in this child.
			Float:E_AREA_CHILD_ELEMS[_:E_AREA_FLAGS - _:E_AREA_CHILD_OPT_X - 1],
			// Skip the flags.
			_E_AREA_CHILD_ELEMS_END
	//    }
}

#define CHILD_AREA_SLOTS ((_:_E_AREA_CHILD_ELEMS_END - _:E_AREA_CHILD_ELEMS))

static stock
	YSI_g_sUnusedAreas = 0,
	//YSI_g_sLastUnused = MAX_AREAS - 1,
	YSI_g_sFreeCount = MAX_AREAS,
	YSI_g_sAreas[MAX_AREAS][E_AREA],
	YSI_g_sPlayerArea[MAX_PLAYERS][AREAS_MAX_OVERLAPS], // = {NO_AREA, ...},
	YSI_g_sHasCallbacks,
	YSI_g_sZones[AREAS_ZONE_ARRAY * AREAS_ZONE_ARRAY] = {AREA_NO_NEXT, ...},
	// "Inner" zones.  -4000 <= x, y <= 4000; Z(x) != Z(y)
	YSI_g_sZoneIN  = AREA_NO_NEXT, // -1
	YSI_g_sZoneINE = AREA_NO_NEXT, // -2
	YSI_g_sZoneIE  = AREA_NO_NEXT, // -3
	YSI_g_sZoneISE = AREA_NO_NEXT, // -4
	YSI_g_sZoneIS  = AREA_NO_NEXT, // -5
	YSI_g_sZoneISW = AREA_NO_NEXT, // -6
	YSI_g_sZoneIW  = AREA_NO_NEXT, // -7
	YSI_g_sZoneINW = AREA_NO_NEXT, // -8
	// "Outer" zones.  -4000 > x, y > 4000;
	YSI_g_sZoneON  = AREA_NO_NEXT, // -9
	YSI_g_sZoneONE = AREA_NO_NEXT, // -10
	YSI_g_sZoneOE  = AREA_NO_NEXT, // -11
	YSI_g_sZoneOSE = AREA_NO_NEXT, // -12
	YSI_g_sZoneOS  = AREA_NO_NEXT, // -13
	YSI_g_sZoneOSW = AREA_NO_NEXT, // -14
	YSI_g_sZoneOW  = AREA_NO_NEXT, // -15
	YSI_g_sZoneONW = AREA_NO_NEXT, // -16
	// "Extra" zones.  In a quadrant, but spanning the +-4000 boundary.
	YSI_g_sZoneXN  = AREA_NO_NEXT, // -17
	YSI_g_sZoneXNE = AREA_NO_NEXT, // -18
	YSI_g_sZoneXE  = AREA_NO_NEXT, // -19
	YSI_g_sZoneXSE = AREA_NO_NEXT, // -20
	YSI_g_sZoneXS  = AREA_NO_NEXT, // -21
	YSI_g_sZoneXSW = AREA_NO_NEXT, // -22
	YSI_g_sZoneXW  = AREA_NO_NEXT, // -23
	YSI_g_sZoneXNW = AREA_NO_NEXT, // -24
	// Extra zones.  For when areas are too big for a quadrant.
	YSI_g_sZoneI   = AREA_NO_NEXT, // -25
	//YSI_g_sZoneO   = AREA_NO_NEXT, // -26
	YSI_g_sZoneX   = AREA_NO_NEXT; // -27

forward Area_Loop();

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Sets up required variables.  Note that this hooks "OnScriptInit",
 *  "OnGameModeInit" and "OnFilterScript".  This is because ALL scripts need to
 *  initialise some things, and only the master needs to initialise others.
 * </remarks>
 *//*------------------------------------------------------------------------**/

MASTER_HOOK__ OnScriptInit()
{
	for (new i = 0; i != MAX_AREAS - 1; ++i)
	{
		YSI_g_sAreas[i][E_AREA_UNUSED_NEXT] = (i + 1);
	}
	YSI_g_sAreas[MAX_AREAS - 1][E_AREA_UNUSED_NEXT] = AREA_NO_NEXT;
	//for (new i = 0; i != AREAS_ZONE_ARRAY * AREAS_ZONE_ARRAY; ++i)
	//{
	//	YSI_g_sZones[i] = -1;
	//}
	return 1;
}

#if !defined FILTERSCRIPT
	HOOK__ OnGameModeInit()
	{
		if (!YSI_FILTERSCRIPT)
		{
			new
				buffer = 0;
			YSI_g_sHasCallbacks = 0;
			YSI_g_sHasCallbacks |= funcidx("OnPlayerEnterArea") == -1 ? 0 : 1;
			YSI_g_sHasCallbacks |= funcidx("OnPlayerLeaveArea") == -1 ? 0 : 2;
			YSI_g_sHasCallbacks |= AMX_GetPublicEntry(0, buffer, "@yH_PlayerEnterArea") ? 4 : 0;
			YSI_g_sHasCallbacks |= AMX_GetPublicEntry(0, buffer, "@yH_PlayerLeaveArea") ? 8 : 0;
		}
	}
#endif

HOOK__ OnFilterScriptInit()
{
	new
		buffer = 0;
	YSI_g_sHasCallbacks = 0;
	YSI_g_sHasCallbacks |= funcidx("OnPlayerEnterArea") == -1 ? 0 : 1;
	YSI_g_sHasCallbacks |= funcidx("OnPlayerLeaveArea") == -1 ? 0 : 2;
	YSI_g_sHasCallbacks |= AMX_GetPublicEntry(0, buffer, "@yH_PlayerEnterArea") ? 4 : 0;
	YSI_g_sHasCallbacks |= AMX_GetPublicEntry(0, buffer, "@yH_PlayerLeaveArea") ? 8 : 0;
}

/*-------------------------------------------------------------------------*//**
 * <returns>
 *  Number of unused area slots.
 * </returns>
 *//*------------------------------------------------------------------------**/

P:D(Area_GetEmptySlotCount());
#define Area_GetEmptySlotCount() \
	(YSI_g_sFreeCount)

/*-------------------------------------------------------------------------*//**
 * <param name="num">Number of slots to add.</param>
 * <remarks>
 *  Actually removes slots from the unused count.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Area_AddSlots(num));
#define Area_AddSlots(%1) \
	YSI_g_sFreeCount -= (%1)

/*-------------------------------------------------------------------------*//**
 * <param name="area">Area to check validity of</param>
 * <remarks>
 *  An area slot could be used but still invalid if it's not the first slot in
 *  an area set.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(bool:Area_IsActive(area));
#define Area_IsActive(%1) \
	((%1) >= 0 && (%1) < MAX_AREAS && (YSI_g_sAreas[(%1)][E_AREA_FLAGS] & e_AREA_FLAGS_ACTIVE))

/*-------------------------------------------------------------------------*//**
 * <param name="area">Area to print information about.</param>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Area_Debug(area);

GLOBAL__ void:Area_Debug(area)
{
	new
		e_AREA_FLAGS:flags = YSI_g_sAreas[area][E_AREA_FLAGS];
	if ((flags & e_AREA_FLAGS_ACTIVE))
	{
		switch (flags & e_AREA_FLAGS_TYPE)
		{
			case e_AREA_FLAGS_POLY:
			{
				new
					count = YSI_g_sAreas[area][E_AREA_POLY_COUNT];
				printf("Poly Area %d:", area);
				printf("\tPoints = %d", count);
				printf("\tNext = %d", YSI_g_sAreas[area][E_AREA_UNUSED_NEXT] & AREA_NO_NEXT);
				#if AREA_WORLDS > 0
					printf("\tWorlds = %s", Bit_Display(YSI_g_sAreas[area][E_AREA_WORLDS], bits<AREA_WORLDS>));
				#else
					printf("\tNo Worlds");
				#endif
				printf("\tPlayers = %s", Bit_Display(YSI_g_sAreas[area][E_AREA_PLAYERS][1], bits<MAX_PLAYERS>));
				printf("\tBounding Circle: %.2f, %.2f, %.2f, %.2f", YSI_g_sAreas[area][E_AREA_POLY_BOUND_X], YSI_g_sAreas[area][E_AREA_POLY_BOUND_Y], floatsqroot(YSI_g_sAreas[area][E_AREA_POLY_BOUND_R]), YSI_g_sAreas[area][E_AREA_POLY_BOUND_H]);
				new
					next = YSI_g_sAreas[area][E_AREA_POLY_NEXT];
				while (count > 0)
				{
					printf("\tPoints Set %d:", next);
					for (new i = 0, j = min(count, CHILD_AREA_SLOTS); i < j; i += 2)
					{
						printf("\t\t(%.2f, %.2f)", YSI_g_sAreas[next][E_AREA_CHILD_ELEMS][i], YSI_g_sAreas[next][E_AREA_CHILD_ELEMS][i + 1]);
					}
					next = YSI_g_sAreas[next][E_AREA_POLY_NEXT];
					count -= CHILD_AREA_SLOTS;
				}
			}
		}
		//return 1;
	}
	//return 0;
}

/*-------------------------------------------------------------------------*//**
 * <returns>
 *  Next available slot.
 * </returns>
 * <remarks>
 *  Gets an empty slot, removes it from the unused list and returs a pointer.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Area_GetFreeSlot()
{
	P:4("Area_GetFreeSlot called");
	if (YSI_g_sUnusedAreas == AREA_NO_NEXT) return NO_AREA;
	P:7("Area_GetFreeSlot: 1");
	new
		old = YSI_g_sUnusedAreas;
	YSI_g_sUnusedAreas = YSI_g_sAreas[old][E_AREA_UNUSED_NEXT];
	--YSI_g_sFreeCount;
	return old;
}

/*-------------------------------------------------------------------------*//**
 * <param name="area">Area to remove from the list.</param>
 * <remarks>
 *  You can only remove areas which are at the start of a list.
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Area_Delete(area);

GLOBAL__ void:Area_Delete(area)
{
	if (!Area_IsActive(area))
	{
		return; //0;
	}
	new
		e_AREA_FLAGS:flags = YSI_g_sAreas[area][E_AREA_FLAGS];
	switch (flags & e_AREA_FLAGS_TYPE)
	{
		case e_AREA_FLAGS_UNUSED:
		{
			return; //0;
		}
		case e_AREA_FLAGS_CHILD:
		{
			// This is just part of a poly, remove the whole thing.
			Area_Delete(YSI_g_sAreas[area][E_AREA_CHILD_PARENT]);
		}
		case e_AREA_FLAGS_POLY:
		{
			// Many blocks used - hard.
			new
				count = YSI_g_sAreas[area][E_AREA_POLY_COUNT],
				next = YSI_g_sAreas[area][E_AREA_POLY_NEXT],
				prev = YSI_g_sUnusedAreas;
			// All all of this poly area to the old area.
			while (count > 0)
			{
				// Increase the free count.
				++YSI_g_sFreeCount;
				// Decrease the stored points.
				count -= CHILD_AREA_SLOTS;
				// Change the poly list to an unused list.
				YSI_g_sAreas[next][E_AREA_UNUSED_NEXT] = prev;
				prev = next;
				next = YSI_g_sAreas[next][E_AREA_POLY_NEXT];
			}
			// Remove the poly header.
			++YSI_g_sFreeCount;
			YSI_g_sAreas[area][E_AREA_UNUSED_NEXT] = prev;
			YSI_g_sUnusedAreas = area;
		}
		default:
		{
			// Only one block used - easy.
			YSI_g_sAreas[area][E_AREA_UNUSED_NEXT] = YSI_g_sUnusedAreas;
			YSI_g_sUnusedAreas = area;
			++YSI_g_sFreeCount;
		}
	}
	// Remove this one from the zone it was in.
	Area_DoRemove(_:(flags & e_AREA_FLAGS_ZONE), area, _:(flags & e_AREA_FLAGS_NEXT));
	//return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="zone">The zone this area is in (right shifted 18).</param>
 * <param name="start">The first of the allocated areas being removed.</param>
 * <param name="end">The area in this zone after the last removed one.</param>
 * <remarks>
 *  Very tightly integrated with "Area_Delete", to the point where I could just
 *  make them one function if I wanted (but I won't).
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Area_DoRemove(zone, area, next)
{
	//printf("remove %d %d %d %d", zone << 18, area, next, (e_AREA_ZONE_I_   << 18 & _:e_AREA_FLAGS_ZONE));
	// Actually "zone << 18", but that's not important.
	switch (zone)
	{
		case (e_AREA_ZONE_I_N  << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneIN,  area, next);}
		case (e_AREA_ZONE_I_NE << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneINE, area, next);}
		case (e_AREA_ZONE_I_E  << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneIE,  area, next);}
		case (e_AREA_ZONE_I_SE << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneISE, area, next);}
		case (e_AREA_ZONE_I_S  << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneIS,  area, next);}
		case (e_AREA_ZONE_I_SW << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneISW, area, next);}
		case (e_AREA_ZONE_I_W  << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneIW,  area, next);}
		case (e_AREA_ZONE_I_NW << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneINW, area, next);}
		case (e_AREA_ZONE_I_   << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneI,   area, next);}
		// "Outer" zones.  -4000 > x, y > 4000;
		case (e_AREA_ZONE_O_N  << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneON,  area, next);}
		case (e_AREA_ZONE_O_NE << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneONE, area, next);}
		case (e_AREA_ZONE_O_E  << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneOE,  area, next);}
		case (e_AREA_ZONE_O_SE << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneOSE, area, next);}
		case (e_AREA_ZONE_O_S  << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneOS,  area, next);}
		case (e_AREA_ZONE_O_SW << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneOSW, area, next);}
		case (e_AREA_ZONE_O_W  << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneOW,  area, next);}
		case (e_AREA_ZONE_O_NW << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneONW, area, next);}
		//e_AREA_ZONE_O_,   // Can't be in all of O, but none of I.
		// "Extra" zones.  In a quadrant, but spanning the +-4000 boundary.
		case (e_AREA_ZONE_X_N  << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneXN,  area, next);}
		case (e_AREA_ZONE_X_NE << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneXNE, area, next);}
		case (e_AREA_ZONE_X_E  << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneXE,  area, next);}
		case (e_AREA_ZONE_X_SE << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneXSE, area, next);}
		case (e_AREA_ZONE_X_S  << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneXS,  area, next);}
		case (e_AREA_ZONE_X_SW << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneXSW, area, next);}
		case (e_AREA_ZONE_X_W  << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneXW,  area, next);}
		case (e_AREA_ZONE_X_NW << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneXNW, area, next);}
		// Extra zones.  For when areas are too big for a quadrant.
		case (e_AREA_ZONE_X_   << 18 & _:e_AREA_FLAGS_ZONE): {_AREAS_DO_REMOVE(YSI_g_sZoneX,   area, next);}
		default: {_AREAS_DO_REMOVE(YSI_g_sZones[zone >> 18], area, next);}
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="x">Start of an area.</param>
 * <param name="y">Start of an area.</param>
 * <returns>
 *  All the zones this position overlaps.
 * </returns>
 * <remarks>
 *  The most zones you can be in at once is 9 - I_, I_S, I_E, I_SE, X_, X_S,
 *  X_E, X_SE, Z_ (or similar corners - NOT in O_ though).
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Area_GetZones(Float:x, Float:y)
{
	// Always end with e_AREA_ZONE_X_ as they will ALWAYS be in that one (that's
	// basically everywhere and means the area exists somewhere ever).  Once
	// that zone is detected, stop next loop.
	static const
		scZones[16][9] =
			{
				{e_AREA_ZONE_O_N , e_AREA_ZONE_O_NE, e_AREA_ZONE_O_E , e_AREA_ZONE_X_N , e_AREA_ZONE_X_NE, e_AREA_ZONE_X_E , e_AREA_ZONE_X_  , e_AREA_ZONE_NONE, e_AREA_ZONE_NONE},
				{e_AREA_ZONE_O_NE, e_AREA_ZONE_O_E , e_AREA_ZONE_X_N , e_AREA_ZONE_X_NE, e_AREA_ZONE_X_E , e_AREA_ZONE_X_  , e_AREA_ZONE_NONE, e_AREA_ZONE_NONE, e_AREA_ZONE_NONE},
				{e_AREA_ZONE_O_SE, e_AREA_ZONE_O_E , e_AREA_ZONE_X_S , e_AREA_ZONE_X_SE, e_AREA_ZONE_X_E , e_AREA_ZONE_X_  , e_AREA_ZONE_NONE, e_AREA_ZONE_NONE, e_AREA_ZONE_NONE},
				{e_AREA_ZONE_O_S , e_AREA_ZONE_O_SE, e_AREA_ZONE_O_E , e_AREA_ZONE_X_S , e_AREA_ZONE_X_SE, e_AREA_ZONE_X_E , e_AREA_ZONE_X_  , e_AREA_ZONE_NONE, e_AREA_ZONE_NONE},
				
				{e_AREA_ZONE_O_N , e_AREA_ZONE_O_NE, e_AREA_ZONE_X_N , e_AREA_ZONE_X_NE, e_AREA_ZONE_X_E , e_AREA_ZONE_X_  , e_AREA_ZONE_NONE, e_AREA_ZONE_NONE, e_AREA_ZONE_NONE},
				{e_AREA_ZONE_NONE, e_AREA_ZONE_I_N , e_AREA_ZONE_I_NE, e_AREA_ZONE_I_E , e_AREA_ZONE_I_  , e_AREA_ZONE_X_N , e_AREA_ZONE_X_NE, e_AREA_ZONE_X_E , e_AREA_ZONE_X_  },
				{e_AREA_ZONE_NONE, e_AREA_ZONE_I_S , e_AREA_ZONE_I_SE, e_AREA_ZONE_I_E , e_AREA_ZONE_I_  , e_AREA_ZONE_X_S , e_AREA_ZONE_X_SE, e_AREA_ZONE_X_E , e_AREA_ZONE_X_  },
				{e_AREA_ZONE_O_S , e_AREA_ZONE_O_SE, e_AREA_ZONE_X_S , e_AREA_ZONE_X_SE, e_AREA_ZONE_X_E , e_AREA_ZONE_X_  , e_AREA_ZONE_NONE, e_AREA_ZONE_NONE, e_AREA_ZONE_NONE},
				
				{e_AREA_ZONE_O_N , e_AREA_ZONE_O_NW, e_AREA_ZONE_X_N , e_AREA_ZONE_X_NW, e_AREA_ZONE_X_W , e_AREA_ZONE_X_  , e_AREA_ZONE_NONE, e_AREA_ZONE_NONE, e_AREA_ZONE_NONE},
				{e_AREA_ZONE_NONE, e_AREA_ZONE_I_N , e_AREA_ZONE_I_NW, e_AREA_ZONE_I_W , e_AREA_ZONE_I_  , e_AREA_ZONE_X_N , e_AREA_ZONE_X_NW, e_AREA_ZONE_X_W , e_AREA_ZONE_X_  },
				{e_AREA_ZONE_NONE, e_AREA_ZONE_I_S , e_AREA_ZONE_I_SW, e_AREA_ZONE_I_W , e_AREA_ZONE_I_  , e_AREA_ZONE_X_S , e_AREA_ZONE_X_SW, e_AREA_ZONE_X_W , e_AREA_ZONE_X_  },
				{e_AREA_ZONE_O_S , e_AREA_ZONE_O_SW, e_AREA_ZONE_X_S , e_AREA_ZONE_X_SW, e_AREA_ZONE_X_W , e_AREA_ZONE_X_  , e_AREA_ZONE_NONE, e_AREA_ZONE_NONE, e_AREA_ZONE_NONE},
				
				{e_AREA_ZONE_O_N , e_AREA_ZONE_O_NW, e_AREA_ZONE_O_W , e_AREA_ZONE_X_N , e_AREA_ZONE_X_NW, e_AREA_ZONE_X_W , e_AREA_ZONE_X_  , e_AREA_ZONE_NONE, e_AREA_ZONE_NONE},
				{e_AREA_ZONE_O_NW, e_AREA_ZONE_O_W , e_AREA_ZONE_X_N , e_AREA_ZONE_X_NW, e_AREA_ZONE_X_W , e_AREA_ZONE_X_  , e_AREA_ZONE_NONE, e_AREA_ZONE_NONE, e_AREA_ZONE_NONE},
				{e_AREA_ZONE_O_SW, e_AREA_ZONE_O_W , e_AREA_ZONE_X_S , e_AREA_ZONE_X_SW, e_AREA_ZONE_X_W , e_AREA_ZONE_X_  , e_AREA_ZONE_NONE, e_AREA_ZONE_NONE, e_AREA_ZONE_NONE},
				{e_AREA_ZONE_O_S , e_AREA_ZONE_O_SW, e_AREA_ZONE_O_W , e_AREA_ZONE_X_S , e_AREA_ZONE_X_SW, e_AREA_ZONE_X_W , e_AREA_ZONE_X_  , e_AREA_ZONE_NONE, e_AREA_ZONE_NONE}
			};
	if (AREAS_ZONE_BOUNDS.0 <= x)
	{
		if (AREAS_ZONE_BOUNDS.0 <= y)       return scZones[ 0];
		else if (0.0 <= y)                  return scZones[ 1];
		else if (-AREAS_ZONE_BOUNDS.0 <= y) return scZones[ 2];
		else                                return scZones[ 3];
	}
	else if (0.0 <= x)
	{
		if (AREAS_ZONE_BOUNDS.0 <= y)       return scZones[ 4];
		else if (0.0 <= y)                  return scZones[ 5]; //, ret[0] = _AREAS_MAKE_ZONE(Area_MakeZone(x), Area_MakeZone(y)));
		else if (-AREAS_ZONE_BOUNDS.0 <= y) return scZones[ 6]; //, ret[0] = _AREAS_MAKE_ZONE(Area_MakeZone(x), Area_MakeZone(y)));
		else                                return scZones[ 7];
	}
	else if (-AREAS_ZONE_BOUNDS.0 <= x)
	{
		if (AREAS_ZONE_BOUNDS.0 <= y)       return scZones[ 8];
		else if (0.0 <= y)                  return scZones[ 9]; //, ret[0] = _AREAS_MAKE_ZONE(Area_MakeZone(x), Area_MakeZone(y)));
		else if (-AREAS_ZONE_BOUNDS.0 <= y) return scZones[10]; //, ret[0] = _AREAS_MAKE_ZONE(Area_MakeZone(x), Area_MakeZone(y)));
		else                                return scZones[11];
	}
	else 
	{
		if (AREAS_ZONE_BOUNDS.0 <= y)       return scZones[12];
		else if (0.0 <= y)                  return scZones[13];
		else if (-AREAS_ZONE_BOUNDS.0 <= y) return scZones[14];
		else                                return scZones[15];
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="minx">Start of an area.</param>
 * <param name="miny">Start of an area.</param>
 * <param name="maxx">End of an area.</param>
 * <param name="maxy">End of an area.</param>
 * <param name="area">The area to add to the determined zone.</param>
 * <param name="last">The last slot that makes up the current zone.</param>
 * <remarks>
 *  Finds the smallest zone that this area will fit in completely.  Note that
 *  due to a limitation in the code, any zones with a node touching the upper
 *  edge of a zone will spill in to the next zone too.  Only lower zone edges
 *  are inclusive.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Area_DetermineZone(Float:minx, Float:miny, Float:maxx, Float:maxy, area, last)
{
	new
		zx = 0,
		zy = 0;
	// This optimises based on the fact that (by definition) maxx can't be lower
	// than minx and maxy can't be lower than miny, meaning we can skip certain
	// checks in some cases.
	if (AREAS_ZONE_BOUNDS.0 <= minx)       // Western edge.
	{
		if (0.0 <= miny)                  // Southern edge.
		{
			_AREAS_ZONES_O(NE);
			//YSI_g_sAreas[last][E_AREA_FLAGS]=(YSI_g_sAreas[last][E_AREA_FLAGS]&e_AREA_FLAGS_REST)|(e_AREA_FLAGS:YSI_g_sZoneXNE&e_AREA_FLAGS_NEXT|e_AREA_FLAGS(e_AREA_ZONE_X_NE<<18)&e_AREA_FLAGS_ZONE),YSI_g_sZoneXNE=area;
			//return _AREAS_ADD_TO_ZONE(YSI_g_sZoneXNE,area,last,e_AREA_ZONE_X_NE)
		}
		else                                   // Southern edge.
		{
			if (0.0 <= maxy)                  // Northern edge.
			{
				_AREAS_ZONES_O(E);
			}
			else                                   // Northern edge.
			{
				_AREAS_ZONES_O(SE);
			}
		}
	}
	else if (0.0 <= minx)                  // Western edge.
	{
		if (AREAS_ZONE_BOUNDS.0 <= miny)       // Southern edge.
		{
			_AREAS_ZONES_O(NE);
		}
		else if (0.0 <= miny)                  // Southern edge.
		{
			if (AREAS_ZONE_BOUNDS.0 <= maxx)       // Eastern edge.
			{
				_AREAS_ZONES_X(NE);
			}
			else // Eastern edge.
			{
				// Interesting case - y > 0, 0 <= x < 4000.
				if (AREAS_ZONE_BOUNDS.0 <= maxy)       // Northern edge.
				{
					_AREAS_ZONES_X(NE);
				}
				else                 // Northern edge.
				{
					//_AREAS_ZONES_I_GRID;
					zx = Area_MakeZone(minx);
					zy = Area_MakeZone(miny);
					if (zx == Area_MakeZone(maxx) && zy == Area_MakeZone(maxy))
					{
						zy += ((zx + AREAS_ZONE_PARTS) * AREAS_ZONE_ARRAY) + AREAS_ZONE_PARTS;
						YSI_g_sAreas[last][E_AREA_FLAGS] =
							(YSI_g_sAreas[last][E_AREA_FLAGS] & e_AREA_FLAGS_REST) |
							(e_AREA_FLAGS:YSI_g_sZones[zy] & e_AREA_FLAGS_NEXT) |
							(e_AREA_FLAGS:(zy << 18) & e_AREA_FLAGS_ZONE);
						P:7("Area_DetermineZone: Added to North-Eastern square");
						return YSI_g_sZones[zy] = area;
					}
					_AREAS_ZONES_I(NE);
				}
			}
		}
		else if (-AREAS_ZONE_BOUNDS.0 <= miny) // Southern edge.
		{
			if (AREAS_ZONE_BOUNDS.0 <= maxx)       // Eastern edge.
			{
				if (0.0 <= maxy)       // Northern edge.
				{
					_AREAS_ZONES_X(E);
				}
				else                 // Northern edge.
				{
					_AREAS_ZONES_X(SE);
				}
			}
			else               // Eastern edge.
			{
				if (AREAS_ZONE_BOUNDS.0 <= maxy)       // Northern edge.
				{
					_AREAS_ZONES_X(E);
				}
				if (0.0 <= maxy)       // Northern edge.
				{
					_AREAS_ZONES_I(E);
				}
				else                 // Northern edge.
				{
					zx = Area_MakeZone(minx);
					zy = Area_MakeZone(miny);
					if (zx == Area_MakeZone(maxx) && zy == Area_MakeZone(maxy))
					{
						zy += ((zx + AREAS_ZONE_PARTS) * AREAS_ZONE_ARRAY) + AREAS_ZONE_PARTS;
						YSI_g_sAreas[last][E_AREA_FLAGS] =
							(YSI_g_sAreas[last][E_AREA_FLAGS] & e_AREA_FLAGS_REST) |
							(e_AREA_FLAGS:YSI_g_sZones[zy] & e_AREA_FLAGS_NEXT) |
							(e_AREA_FLAGS:(zy << 18) & e_AREA_FLAGS_ZONE);
						return YSI_g_sZones[zy] = area;
					}
					_AREAS_ZONES_I(SE);
				}
			}
		}
		else                                   // Southern edge.
		{
			if (0.0 <= maxy) // Northern edge.
			{
				_AREAS_ZONES_X(E);
			}
			if (-AREAS_ZONE_BOUNDS.0 <= maxy) // Northern edge.
			{
				_AREAS_ZONES_X(SE);
			}
			else                                   // Northern edge.
			{
				_AREAS_ZONES_O(SE);
			}
		}
	}
	else if (-AREAS_ZONE_BOUNDS.0 <= minx) // Western edge.
	{
		if (AREAS_ZONE_BOUNDS.0 <= miny)       // Southern edge.
		{
			if (0.0 <= maxx)                  // Eastern edge.
			{
				_AREAS_ZONES_O(N);
			}
			else                                   // Eastern edge.
			{
				_AREAS_ZONES_O(NW);
			}
		}
		else if (0.0 <= miny)                  // Southern edge.
		{
			if (AREAS_ZONE_BOUNDS.0 <= maxx)       // Eastern edge.
			{
				_AREAS_ZONES_X(N);
			}
			else if (0.0 <= maxx)                  // Eastern edge.
			{
				if (AREAS_ZONE_BOUNDS.0 <= maxy)       // Northern edge.
				{
					_AREAS_ZONES_X(N);
				}
				else                                   // Northern edge.
				{
					_AREAS_ZONES_I(N);
				}
			}
			else                                   // Eastern edge.
			{
				if (AREAS_ZONE_BOUNDS.0 <= maxy)       // Northern edge.
				{
					_AREAS_ZONES_X(NW);
				}
				else                                   // Northern edge.
				{
					zx = Area_MakeZone(minx);
					zy = Area_MakeZone(miny);
					if (zx == Area_MakeZone(maxx) && zy == Area_MakeZone(maxy))
					{
						zy += ((zx + AREAS_ZONE_PARTS) * AREAS_ZONE_ARRAY) + AREAS_ZONE_PARTS;
						YSI_g_sAreas[last][E_AREA_FLAGS] =
							(YSI_g_sAreas[last][E_AREA_FLAGS] & e_AREA_FLAGS_REST) |
							(e_AREA_FLAGS:YSI_g_sZones[zy] & e_AREA_FLAGS_NEXT) |
							(e_AREA_FLAGS:(zy << 18) & e_AREA_FLAGS_ZONE);
						return YSI_g_sZones[zy] = area;
					}
					_AREAS_ZONES_I(NW);
				}
			}
		}
		else if (-AREAS_ZONE_BOUNDS.0 <= miny) // Southern edge.
		{
			if (AREAS_ZONE_BOUNDS.0 <= maxx)       // Eastern edge.
			{
				if (0.0 <= maxy)                  // Northern edge.
				{
					_AREAS_ZONES_X();
				}
				else                                   // Northern edge.
				{
					_AREAS_ZONES_X(S);
				}
			}
			else if (0.0 <= maxx)                  // Eastern edge.
			{
				if (AREAS_ZONE_BOUNDS.0 <= maxy)       // Northern edge.
				{
					_AREAS_ZONES_X();
				}
				else if (0.0 <= maxy)                  // Northern edge.
				{
					_AREAS_ZONES_I();
				}
				else                                   // Northern edge.
				{
					_AREAS_ZONES_I(S);
				}
			}
			else                                   // Eastern edge.
			{
				if (AREAS_ZONE_BOUNDS.0 <= maxy)       // Northern edge.
				{
					_AREAS_ZONES_X(W);
				}
				else if (0.0 <= maxy)                  // Northern edge.
				{
					_AREAS_ZONES_I(W);
				}
				else                                   // Northern edge.
				{
					zx = Area_MakeZone(minx);
					zy = Area_MakeZone(miny);
					if (zx == Area_MakeZone(maxx) && zy == Area_MakeZone(maxy))
					{
						zy += ((zx + AREAS_ZONE_PARTS) * AREAS_ZONE_ARRAY) + AREAS_ZONE_PARTS;
						YSI_g_sAreas[last][E_AREA_FLAGS] =
							(YSI_g_sAreas[last][E_AREA_FLAGS] & e_AREA_FLAGS_REST) |
							(e_AREA_FLAGS:YSI_g_sZones[zy] & e_AREA_FLAGS_NEXT) |
							(e_AREA_FLAGS:(zy << 18) & e_AREA_FLAGS_ZONE);
						return YSI_g_sZones[zy] = area;
					}
					_AREAS_ZONES_I(SW);
				}
			}
		}
		else                                   // Southern edge.
		{
			if (0.0 <= maxx)                  // Eastern edge.
			{
				if (-AREAS_ZONE_BOUNDS.0 <= maxy) // Northern edge.
				{
					_AREAS_ZONES_X(S);
				}
				else                                   // Northern edge.
				{
					_AREAS_ZONES_O(S);
				}
			}
			else                                   // Eastern edge.
			{
				if (-AREAS_ZONE_BOUNDS.0 <= maxy) // Northern edge.
				{
					_AREAS_ZONES_X(SW);
				}
				else                                   // Northern edge.
				{
					_AREAS_ZONES_O(SW);
				}
			}
		}
	}
	else                                   // Western edge.
	{
		if (AREAS_ZONE_BOUNDS.0 <= miny)       // Southern edge.
		{
			if (0.0 <= maxx)                  // Eastern edge.
			{
				_AREAS_ZONES_O(N);
			}
			else                                   // Eastern edge.
			{
				// I missed this one and the compiler didn't complain about the
				// path not returning - I think I confused it!
				_AREAS_ZONES_O(NW);
			}
		}
		else if (0.0 <= miny)                  // Southern edge.
		{
			if (0.0 <= maxx)                  // Eastern edge.
			{
				_AREAS_ZONES_X(N);
			}
			else if (-AREAS_ZONE_BOUNDS.0 <= maxx) // Eastern edge.
			{
				_AREAS_ZONES_X(NW);
			}
			else                                   // Eastern edge.
			{
				_AREAS_ZONES_O(NW);
			}
		}
		else if (-AREAS_ZONE_BOUNDS.0 <= miny) // Southern edge.
		{
			if (0.0 <= maxx)                  // Eastern edge.
			{
				if (0.0 <= maxy)                  // Northern edge.
				{
					_AREAS_ZONES_X();
				}
				else
				{
					_AREAS_ZONES_X(S);
				}
			}
			else if (-AREAS_ZONE_BOUNDS.0 <= maxx) // Eastern edge.
			{
				if (0.0 <= maxy)                  // Northern edge.
				{
					_AREAS_ZONES_X(W);
				}
				else                                   // Northern edge.
				{
					_AREAS_ZONES_X(SW);
				}
			}
			else                                   // Eastern edge.
			{
				if (0.0 <= maxy)                  // Northern edge.
				{
					_AREAS_ZONES_O(W);
				}
				else                                   // Northern edge.
				{
					_AREAS_ZONES_O(SW);
				}
			}
		}
		else                                   // Southern edge.
		{
			if (0.0 <= maxx)                  // Eastern edge.
			{
				if (0.0 <= maxy)                  // Northern edge.
				{
					_AREAS_ZONES_X();
				}
				else if (-AREAS_ZONE_BOUNDS.0 <= maxy) // Northern edge.
				{
					_AREAS_ZONES_X(S);
				}
				else                                   // Northern edge.
				{
					_AREAS_ZONES_O(S);
				}
			}
			else if (-AREAS_ZONE_BOUNDS.0 <= maxx) // Eastern edge.
			{
				if (0.0 <= maxy)                  // Northern edge.
				{
					_AREAS_ZONES_X(W);
				}
				else if (-AREAS_ZONE_BOUNDS.0 <= maxy) // Northern edge.
				{
					_AREAS_ZONES_X(SW);
				}
				else                                   // Northern edge.
				{
					_AREAS_ZONES_O(SW);
				}
			}
			else                                   // Eastern edge.
			{
				if (0.0 <= maxy)                  // Northern edge.
				{
					_AREAS_ZONES_O(W);
				}
				else                                   // Northern edge.
				{
					_AREAS_ZONES_O(SW);
				}
			}
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="area">Area to set for.</param>
 * <param name="set">Wether or not this area is usable in all worlds.</param>
 *//*------------------------------------------------------------------------**/

/*-------------------------------------------------------------------------*//**
 * <param name="area">Area to set for.</param>
 * <param name="set">Wether or not this area is usable in all worlds.</param>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Area_SetAllWorlds(area, bool:set);

GLOBAL__ void:Area_SetAllWorlds(area, bool:set)
{
	#if AREA_WORLDS > 0
		if (Area_IsActive(area))
		{
			Bit_SetAll(YSI_g_sAreas[area][E_AREA_WORLDS], set, bits<AREA_WORLDS>);
			//return 1;
		}
	#else
		#pragma unused area, set
	#endif
	//return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="type">Type of area.</param>
 * <param name="">Points.</param>
 * <remarks>
 *  Types:
 *      CUBE, Cube
 *      CUBOID, Cuboid
 *      BOX, Box
 *      CIRCLE, Circle
 *      OVAL, Oval
 *      OVOID, Ovoid
 *      SPHERE, Sphere
 *      POLY, Poly
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Area_Add(type,Float:...));
#define Area_Add(%0,%1) Area_Add%0(%1)
#define Area_AddCUBE Area_AddCube
#define Area_AddCUBOID Area_AddCuboid
#define Area_AddBOX Area_AddBox
#define Area_AddCIRCLE Area_AddCircle
#define Area_AddOVAL Area_AddOval
#define Area_AddOVOID Area_AddOvoid
#define Area_AddSPHERE Area_AddSphere
#define Area_AddPOLY Area_AddPoly

/*-------------------------------------------------------------------------*//**
 * <param name="minx">Lowest X corner of box</param>
 * <param name="miny">Lowest Y corner of box.</param>
 * <param name="minx">Lowest Z corner of box.</param>
 * <param name="maxx">Highest X corner of box.</param>
 * <param name="maxy">Highest Y corner of box.</param>
 * <param name="maxz">Highest Z corner of box.</param>
 * <returns>
 *  Area slot or NO_AREA
 * </returns>
 *//*------------------------------------------------------------------------**/

P:D(_AREA_MIN(&Float:minx,&Float:miny));
#define _AREA_MIN(%0,%1) if (%1 < %0) %0 ^= %1, %1 ^= %0, %0 ^= %1

FOREIGN__ Area_AddCuboid(Float:x0,Float:y0,Float:z0,Float:x1,Float:y1,Float:z1);

GLOBAL__ Area_AddCuboid(Float:x0,Float:y0,Float:z0,Float:x1,Float:y1,Float:z1)
{
	new
		slot = Area_GetFreeSlot();
	if (slot == NO_AREA) return NO_AREA;
	_AREA_MIN(x0, x1);
	_AREA_MIN(y0, y1);
	_AREA_MIN(z0, z1);
	YSI_g_sAreas[slot][E_AREA_FLAGS] = e_AREA_FLAGS_CUBE | e_AREA_FLAGS_ACTIVE;
	YSI_g_sAreas[slot][E_AREA_POS][0] = x0;
	YSI_g_sAreas[slot][E_AREA_POS][1] = y0;
	YSI_g_sAreas[slot][E_AREA_POS][2] = z0;
	YSI_g_sAreas[slot][E_AREA_POS][3] = x1;
	YSI_g_sAreas[slot][E_AREA_POS][4] = y1;
	YSI_g_sAreas[slot][E_AREA_POS][5] = z1;
	PA_FastInit(YSI_g_sAreas[slot][E_AREA_PLAYERS]);
	NO_GROUPS<Area>(slot)
	{
		PA_Init(YSI_g_sAreas[slot][E_AREA_PLAYERS], true);
	}
	#if YSIM_HAS_MASTER
		YSI_g_sAreas[slot][E_AREA_MASTER] = Master_Caller();
	#endif
	Area_SetAllWorlds(slot, true);
	Area_DetermineZone(x0, y0, x1, y1, slot, slot);
	/*#if defined AREA_VERY_FAST
		new
			rx = (x1 - z0) / 2.0,
			ry = (y1 - y0) / 2.0,
			rz = (z1 - z0) / 2.0;
		YSI_g_sAreas[slot][E_AREA_BOUNDING][0] = x0 + rx;
		YSI_g_sAreas[slot][E_AREA_BOUNDING][1] = y0 + ry;
		YSI_g_sAreas[slot][E_AREA_BOUNDING][2] = z0 + rz;
		if (rx > ry && rx > rz)
		{
			YSI_g_sAreas[slot][E_AREA_BOUNDING][3] = rx * rx;
		}
		else if (ry > rz)
		{
			YSI_g_sAreas[slot][E_AREA_BOUNDING][3] = ry * ry;
		}
		else
		{
			YSI_g_sAreas[slot][E_AREA_BOUNDING][3] = rz * rz;
		}
	#endif*/
	return slot;
}

#undef _AREA_MIN

#define Area_AddCube Area_AddCuboid

/*-------------------------------------------------------------------------*//**
 * <param name="minx">Lowest X corner of box</param>
 * <param name="miny">Lowest Y corner of box.</param>
 * <param name="maxx">Highest X corner of box.</param>
 * <param name="maxy">Highest Y corner of box.</param>
 * <returns>
 *  Area slot or NO_AREA
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Area_AddBox(Float:minx, Float:miny, Float:maxx, Float:maxy)
{
	return Area_AddCuboid(minx, miny, FLOAT_NEGATIVE_INFINITY, maxx, maxy, FLOAT_INFINITY);
}

/*
FOREIGN__ Area_AddBox(Float:minx, Float:miny, Float:maxx, Float:maxy);

GLOBAL__ Area_AddBox(Float:minx, Float:miny, Float:maxx, Float:maxy)
{
	
	new
		slot = 0;
	if (minx > maxx)
	{
		slot = _:minx;
		minx = maxx;
		maxx = Float:slot;
	}
	if (miny > maxy)
	{
		slot = _:miny;
		miny = maxy;
		maxy = Float:slot;
	}
	slot = Area_GetFreeSlot();
	if (slot == NO_AREA) return NO_AREA;
	YSI_g_sAreas[slot][E_AREA_FLAGS] = SINGLE_SLOT_AREA | e_AREA_FLAGS_BOX | e_AREA_FLAGS_USED | e_AREA_FLAGS_ACTIVE | e_AREA_FLAGS:(1 << 18);
	YSI_g_sAreas[slot][E_AREA_POS][0] = minx;
	YSI_g_sAreas[slot][E_AREA_POS][1] = miny;
	YSI_g_sAreas[slot][E_AREA_POS][2] = maxx;
	YSI_g_sAreas[slot][E_AREA_POS][3] = maxy;
	PA_FastInit(YSI_g_sAreas[slot][E_AREA_PLAYERS]);
	NO_GROUPS<Area>(slot)
	{
		PA_Init(YSI_g_sAreas[slot][E_AREA_PLAYERS], true);
	}
	#if YSIM_HAS_MASTER
		YSI_g_sAreas[slot][E_AREA_MASTER] = Master_Caller();
	#endif
	Area_SetAllWorlds(slot, true);
	Area_DetermineZone(minx, miny, maxx, maxy, slot, slot);
	return slot;
}
*/

/*-------------------------------------------------------------------------*//**
 * <param name="x">X position of circle.</param>
 * <param name="y">Y position of circle.</param>
 * <param name="r">Radius of circle.</param>
 * <param name="height">Ceiling of circle.</param>
 * <param name="depth">Bottom of circle.</param>
 * <returns>
 *  Area slot or NO_AREA
 * </returns>
 * <remarks>
 *  Technically a cylinder, no lower bound (ceiling added cos there was a
 *  spare slot in the 4 float design which may as well have been used).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Area_AddCircle(Float:x, Float:y, Float:r, Float:height = FLOAT_INFINITY)
{
	return Area_AddOval(x, y, r, r, height, FLOAT_NEGATIVE_INFINITY);
}

/*-------------------------------------------------------------------------*//**
 * <param name="x">X position of circle.</param>
 * <param name="y">Y position of circle.</param>
 * <param name="rx">X Radius of oval.</param>
 * <param name="ry">Y Radius of oval.</param>
 * <param name="height">Ceiling of circle.</param>
 * <param name="depth">Bottom of circle.</param>
 * <returns>
 *  Area slot or NO_AREA
 * </returns>
 * <remarks>
 *  Technically a cylinder, no lower bound (ceiling added cos there was a
 *  spare slot in the 4 float design which may as well have been used).
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Area_AddOval(Float:x,Float:y,Float:rx,Float:ry,Float:h,Float:d);

GLOBAL__ Area_AddOval(Float:x,Float:y,Float:rx,Float:ry,Float:h,Float:d)
{
	new
		slot = Area_GetFreeSlot();
	if (slot == NO_AREA) return NO_AREA;
	//printf("%f %f %f %f", x - r, y - r, x + r, y + r);
	YSI_g_sAreas[slot][E_AREA_FLAGS] = e_AREA_FLAGS_ACTIVE;
	YSI_g_sAreas[slot][E_AREA_POS][0] = x;
	YSI_g_sAreas[slot][E_AREA_POS][1] = y;
	YSI_g_sAreas[slot][E_AREA_POS][2] = rx * rx;
	YSI_g_sAreas[slot][E_AREA_POS][3] = ry * ry;
	YSI_g_sAreas[slot][E_AREA_POS][4] = h;
	YSI_g_sAreas[slot][E_AREA_POS][5] = d;
	PA_FastInit(YSI_g_sAreas[slot][E_AREA_PLAYERS]);
	NO_GROUPS<Area>(slot)
	{
		PA_Init(YSI_g_sAreas[slot][E_AREA_PLAYERS], true);
	}
	#if YSIM_HAS_MASTER
		YSI_g_sAreas[slot][E_AREA_MASTER] = Master_Caller();
	#endif
	Area_SetAllWorlds(slot, true);
	Area_DetermineZone(x - rx, y - ry, x + rx, y + ry, slot, slot);
	if (rx == ry && h == FLOAT_INFINITY && d == FLOAT_NEGATIVE_INFINITY)
	{
		YSI_g_sAreas[slot][E_AREA_FLAGS] |= e_AREA_FLAGS_CIRCLE;
	}
	else
	{
		YSI_g_sAreas[slot][E_AREA_FLAGS] |= e_AREA_FLAGS_OVAL;
	}
	// Bounding sphere.  I'm not convinced this is needed on the simple shapes,
	// I may only use it on polys and special-case 
	/*#if defined AREA_VERY_FAST
		YSI_g_sAreas[slot][E_AREA_BOUNDING][0] = x;
		YSI_g_sAreas[slot][E_AREA_BOUNDING][1] = y;
		// Z radius of the bounding sphere (may be VERY huge).
		new
			rz = (h - d) / 2.0;
		YSI_g_sAreas[slot][E_AREA_BOUNDING][2] = h - rz;
		if (rx > ry && rx > rz)
		{
			YSI_g_sAreas[slot][E_AREA_BOUNDING][3] = rx * rx;
		}
		else if (ry > rz)
		{
			YSI_g_sAreas[slot][E_AREA_BOUNDING][3] = ry * ry;
		}
		else
		{
			YSI_g_sAreas[slot][E_AREA_BOUNDING][3] = rz * rz;
		}
	#endif*/
	return slot;
}

/*-------------------------------------------------------------------------*//**
 * <param name="x">X position of sphere.</param>
 * <param name="y">Y position of sphere.</param>
 * <param name="z">Z position of sphere.</param>
 * <param name="r">Radius of sphere.</param>
 * <returns>
 *  Area slot or NO_AREA
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Area_AddSphere(Float:x, Float:y, Float:z, Float:r)
{
	return Area_AddOvoid(x, y, z, r, r, r);
}

/*-------------------------------------------------------------------------*//**
 * <param name="x">X position of sphere.</param>
 * <param name="y">Y position of sphere.</param>
 * <param name="z">Z position of sphere.</param>
 * <param name="rx">X radius of ovoid.</param>
 * <param name="ry">Y radius of ovoid.</param>
 * <param name="rz">Z radius of ovoid.</param>
 * <returns>
 *  Area slot or NO_AREA
 * </returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ Area_AddOvoid(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz);

GLOBAL__ Area_AddOvoid(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz)
{
	new
		slot = Area_GetFreeSlot();
	if (slot == NO_AREA) return NO_AREA;
	YSI_g_sAreas[slot][E_AREA_FLAGS] = e_AREA_FLAGS_ACTIVE;
	YSI_g_sAreas[slot][E_AREA_POS][0] = x;
	YSI_g_sAreas[slot][E_AREA_POS][1] = y;
	YSI_g_sAreas[slot][E_AREA_POS][2] = z;
	YSI_g_sAreas[slot][E_AREA_POS][3] = rx * rx;
	YSI_g_sAreas[slot][E_AREA_POS][4] = ry * ry;
	YSI_g_sAreas[slot][E_AREA_POS][5] = rz * rz;
	PA_FastInit(YSI_g_sAreas[slot][E_AREA_PLAYERS]);
	NO_GROUPS<Area>(slot)
	{
		PA_Init(YSI_g_sAreas[slot][E_AREA_PLAYERS], true);
	}
	#if YSIM_HAS_MASTER
		YSI_g_sAreas[slot][E_AREA_MASTER] = Master_Caller();
	#endif
	Area_SetAllWorlds(slot, true);
	Area_DetermineZone(x - rx, y - ry, x + rx, y + ry, slot, slot);
	// Create the bounding sphere for this zone.  The player has to be inside
	// the bounding sphere before they can be inside the oval.  Of course, if
	// the oval is also a sphere then these two checks are identical.
	#if defined AREA_VERY_FAST
		YSI_g_sAreas[slot][E_AREA_BOUNDING][0] = x;
		YSI_g_sAreas[slot][E_AREA_BOUNDING][1] = y;
		YSI_g_sAreas[slot][E_AREA_BOUNDING][2] = z;
		if (rx > ry && rx > rz)
		{
			YSI_g_sAreas[slot][E_AREA_BOUNDING][3] = rx * rx;
		}
		else if (ry > rz)
		{
			YSI_g_sAreas[slot][E_AREA_BOUNDING][3] = ry * ry;
		}
		else
		{
			YSI_g_sAreas[slot][E_AREA_BOUNDING][3] = rz * rz;
		}
		if (rx == ry && rx == rz)
		{
			YSI_g_sAreas[slot][E_AREA_FLAGS] |= e_AREA_FLAGS_SPHERE;
		}
		else
	#endif
		{
			// Create the zone bounds.
			YSI_g_sAreas[slot][E_AREA_POS][0] = x;
			YSI_g_sAreas[slot][E_AREA_POS][1] = y;
			YSI_g_sAreas[slot][E_AREA_POS][2] = z;
			YSI_g_sAreas[slot][E_AREA_POS][3] = rx * rx;
			YSI_g_sAreas[slot][E_AREA_POS][4] = ry * ry;
			YSI_g_sAreas[slot][E_AREA_POS][5] = rz * rz;
			// Set this as not a sphere.
			YSI_g_sAreas[slot][E_AREA_FLAGS] |= e_AREA_FLAGS_OVOID;
		}
	#pragma tabsize 4
	return slot;
}

/*-------------------------------------------------------------------------*//**
 * <param name="">X/Ys of points</param>
 * <returns>
 *  Area slot or NO_AREA
 * </returns>
 * <remarks>
 *  Creates an irregular shape to detect players in.  This is a 2d area made
 *  up of a load of XY points.  If an odd number of parameters is passed the
 *  extra one is assumed to be a ceiling so you can ignore interiors or planes.
 *
 *  The height parameter goes first as it's easiest to check.
 *
 *  This is one of a few functions still written using the master system at a
 *  low level (the other obvious one is "Class_Add").
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if YSIM_HAS_MASTER
	#if _YSIM_IS_SERVER
		forward Area_AddPoly(Float:x1, Float:y1, Float:x2, Float:y2, Float:x3, Float:y3, Float:...);
		
		forward Area_AddPoly@(Float:points[], size, count);
		
		stock Area_AddPoly(Float:x1, Float:y1, Float:x2, Float:y2, Float:x3, Float:y3, Float:...)
		{
			new
				args = numargs();
			if (args > 128)
			{
				return NO_AREA;
			}
			new
				Float:points[128];
			points[0] = x1;
			points[1] = y1;
			points[2] = x2;
			points[3] = y2;
			points[4] = x3;
			points[5] = y3;
			for (new i = 6; i != args; ++i)
			{
				points[i] = Float:getarg(i);
			}
			return Area_AddPoly@(points, sizeof (points), args);
		}
		
		public Area_AddPoly@(Float:points[], size, count)
	#else
		stock Area_AddPoly(Float:x1, Float:y1, Float:x2, Float:y2, Float:x3, Float:y3, Float:...) <>
		{
			new
				args = numargs();
			if (args > 128)
			{
				return NO_AREA;
			}
			new
				Float:points[128];
			points[0] = x1;
			points[1] = y1;
			points[2] = x2;
			points[3] = y2;
			points[4] = x3;
			points[5] = y3;
			for (new i = 6; i != args; ++i)
			{
				points[i] = Float:getarg(i);
			}
			new
				p = getproperty(8, YSIM_CALLER);
			setproperty(8, YSIM_CALLER, Master_ID());
			CallRemoteFunction("Area_AddPoly@", "aii", points, sizeof (points), args);
			setproperty(8, YSIM_CALLER, p);
			return getproperty(8, YSIM_RETURN);
		}
		
		forward Area_AddPoly@(Float:points[], size, count);
		
		stock Area_AddPoly(Float:x1, Float:y1, Float:x2, Float:y2, Float:x3, Float:y3, Float:...) <_YCM : m>
		{
			#pragma unused x1, y1, x2, y2, x3, y3
			return NO_AREA;
		}
		#if _YSIM_IS_CLIENT
			static stock Area_AddPoly_(Float:x1, Float:y1, Float:x2, Float:y2, Float:x3, Float:y3, Float:...)
		#else
			#if _YSIM_IS_STUB
				#error _YSIM_IS_STUB set in y_areas.
			#else
				public Area_AddPoly@(Float:points[], size, count) <>
				{
					return 0;
				}
				
				stock Area_AddPoly(Float:x1, Float:y1, Float:x2, Float:y2, Float:x3, Float:y3, Float:...) <_YCM : y>
				{
					new
						args = numargs();
					if (args > 128)
					{
						return NO_AREA;
					}
					new
						Float:points[128];
					points[0] = x1;
					points[1] = y1;
					points[2] = x2;
					points[3] = y2;
					points[4] = x3;
					points[5] = y3;
					for (new i = 6; i != args; ++i)
					{
						points[i] = Float:getarg(i);
					}
					return Area_AddPoly@(points, sizeof (points), args);
				}
				
				public Area_AddPoly@(Float:points[], size, count) <_YCM : y>
			#endif
		#endif
	#endif
#else
	stock Area_AddPoly(Float:x1, Float:y1, Float:x2, Float:y2, Float:x3, Float:y3, Float:...)
	{
		new
			args = numargs();
		if (args > 128)
		{
			return NO_AREA;
		}
		new
			Float:points[128];
		points[0] = x1;
		points[1] = y1;
		points[2] = x2;
		points[3] = y2;
		points[4] = x3;
		points[5] = y3;
		for (new i = 6; i != args; ++i)
		{
			points[i] = Float:getarg(i);
		}
		return Area_AddPoly_(points, sizeof (points), args);
	}
	
	static stock Area_AddPoly_(Float:points[], size, count)
#endif
{
	// This is the main chunk of the code.
	new
		Float:height = Float:isodd(count);
	count &= ~1;
	new
		reqSlots = ceildiv(count, CHILD_AREA_SLOTS) + 1;
	if (Area_GetEmptySlotCount() < reqSlots) return NO_AREA;
	if (_:height)
	{
		height = points[count];
	}
	else
	{
		height = FLOAT_INFINITY;
	}
	// Get the header.  This stores meta-data about the poly area, and the
	// bounding cylinder, it doesn't actually store any points.
	new
		header = Area_GetFreeSlot();
	// Initialise the header.  Area type, players, worlds, and count.
	// This stores the number of pairs, not the number of co-ordinates.
	YSI_g_sAreas[header][E_AREA_POLY_COUNT] = count;
	YSI_g_sAreas[header][E_AREA_FLAGS] = e_AREA_FLAGS_POLY | e_AREA_FLAGS_ACTIVE;
	PA_FastInit(YSI_g_sAreas[header][E_AREA_PLAYERS]);
	NO_GROUPS<Area>(header)
	{
		PA_Init(YSI_g_sAreas[header][E_AREA_PLAYERS], true);
	}
	#if YSIM_HAS_MASTER
		YSI_g_sAreas[header][E_AREA_MASTER] = Master_Caller();
	#endif
	Area_SetAllWorlds(header, true);
	// Now loop through and store all the data points.
	new
		slot = 0,
		prev = header,
		done = 0,
		Float:cur = 0.0,
		Float:minx = FLOAT_INFINITY,
		Float:miny = FLOAT_INFINITY,
		Float:maxx = FLOAT_NEGATIVE_INFINITY,
		Float:maxy = FLOAT_NEGATIVE_INFINITY;
	while (done < count)
	//while (done < count)
	{
		slot = Area_GetFreeSlot();
		YSI_g_sAreas[slot][E_AREA_FLAGS] = e_AREA_FLAGS_ACTIVE | e_AREA_FLAGS_CHILD;
		// Rely purely on counts, not ended lists.  This is because the system
		// MAY (if I get around to it) reuse this data in the last slot to
		//YSI_g_sAreas[slot][E_AREA_POLY_NEXT] = NO_AREA;
		YSI_g_sAreas[slot][E_AREA_CHILD_PARENT] = header;
		YSI_g_sAreas[prev][E_AREA_POLY_NEXT] = slot;
		#if YSIM_HAS_MASTER
			YSI_g_sAreas[slot][E_AREA_MASTER] = Master_Caller();
		#endif
		// Now loop and put points in this slot.
		size = min(count, done + CHILD_AREA_SLOTS);
		for (new idx = 0; done < size; )
		{
			// X point.
			cur = points[done++];
			//printf("%d X: %0.2f", done, cur);
			//printf("%04x%04x %04x%04x %.2f %d %d", _:minx >>> 16, _:minx & 0xFFFF, _:maxx >>> 16, _:maxx & 0xFFFF, cur, cur > maxx, cur < minx);
			if (cur > maxx) maxx = cur;
			if (cur < minx) minx = cur;
			YSI_g_sAreas[slot][E_AREA_CHILD_ELEMS][idx++] = cur;
			// Y point.
			cur = points[done++];
			//printf("%d Y: %0.2f", done, cur);
			// Can be both on the first loop (WILL be both on the first loop).
			if (cur > maxy) maxy = cur;
			if (cur < miny) miny = cur;
			YSI_g_sAreas[slot][E_AREA_CHILD_ELEMS][idx++] = cur;
		}
		prev = slot;
		//count -= CHILD_AREA_SLOTS * 2;
	}
	// Now clean up.
	#if YSIM_HAS_MASTER
		setproperty(8, YSIM_RETURN, header);
	#endif
	Area_DetermineZone(minx, miny, maxx, maxy, header, header);
	// Create the bounding cylinder so we can quickly determine if it is even
	// at all possible for the player to be in this polygon.
	// TODO: This doesn't YET create an accurate bounding cylinder as the
	// diagonals of a square are longer than the width and height, and that fact
	// isn't taken in to account by the radius.  The question is, why are these
	// sums returning -0.0 for 20.0-0.0?
	// BIZZARE BUG FIX.
	//printf("%f %f %f %f", minx, miny, maxx, maxy);
	//printf("%f %f", maxx - minx, maxy - miny);
	//printf("%04x%04x", _:minx >>> 16, _:minx & 0xFFFF);
	//printf("%04x%04x", _:maxx >>> 16, _:maxx & 0xFFFF);
	//if (maxx && minx) printf("1: %d", (maxx = (maxx - minx) / 2.0));
	//else if (maxx) printf("2: %d", (maxx /= 2.0));
	//else printf("3: %d", (maxx = minx / 2.0));
	//if (maxx < 0.0) maxx = -maxx;
	//if (maxy && miny) maxy = (maxy - miny) / 2.0;
	//else if (maxy) maxy /= 2.0;
	//else maxy = miny / 2.0;
	//if (maxy < 0.0) maxy = -maxy;
	//printf("%f %f %f %f", (maxx - minx) / 2.0, (maxy - miny) / 2.0, minx + (maxx - minx) / 2.0, miny + (maxy - miny) / 2.0);
	maxx = (maxx - minx) / 2.0;
	maxy = (maxy - miny) / 2.0;
	//printf("%f %f %f %f", maxx, maxy, minx + maxx, miny + maxy);
	minx += maxx;
	miny += maxy;
	YSI_g_sAreas[header][E_AREA_POLY_BOUND_X] = minx;
	YSI_g_sAreas[header][E_AREA_POLY_BOUND_Y] = miny;
	// Now find the radius.  Note that it might actually make more sense to not
	// use the dead centre but a point which minimises the R^2 distance, but
	// that will require a lot more work.
	slot = YSI_g_sAreas[header][E_AREA_POLY_NEXT];
	count = YSI_g_sAreas[header][E_AREA_POLY_COUNT];
	cur = 0.0;
	while (count > 0)
	{
		for (new i = 0, j = min(count, CHILD_AREA_SLOTS); i < j; i += 2)
		{
			// Get the difference between the points.
			maxx = YSI_g_sAreas[slot][E_AREA_CHILD_ELEMS][i] - minx;
			maxy = YSI_g_sAreas[slot][E_AREA_CHILD_ELEMS][i + 1] - miny;
			maxx = maxx * maxx + maxy * maxy;
			if (maxx > cur) cur = maxx;
		}
		slot = YSI_g_sAreas[slot][E_AREA_POLY_NEXT];
		count -= CHILD_AREA_SLOTS;
	}
	YSI_g_sAreas[header][E_AREA_POLY_BOUND_R] = cur;
	YSI_g_sAreas[header][E_AREA_POLY_BOUND_H] = height;
	return header;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who connected</param>
 *//*------------------------------------------------------------------------**/

MASTER_HOOK__ OnPlayerConnect(playerid)
{
	for (new i = 0; i != AREAS_MAX_OVERLAPS; ++i)
	{
		YSI_g_sPlayerArea[playerid][i] = NO_AREA;
	}
	NO_GROUPS<Area>()
	{
		new
			slot = Bit_Slot(playerid) + 1,
			Bit:mask = Bit_Mask(playerid);
		for (new i = 0; i != MAX_AREAS; ++i)
		{
			YSI_g_sAreas[i][E_AREA_PLAYERS][slot] |= mask;
		}
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">The player to check for.</param>
 * <remarks>
 *  Main processing for the system.  Takes one player and checks if they're in
 *  some sort of range of somewhere.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined AREAS_USE_TIMER
	
	#error AREAS_USE_TIMER is currently unsupported sorry.
	
	ptask Area_Loop[200](playerid)
	{
		new
			Float:x = 0.0,
			Float:y = 0.0,
			Float:z = 0.0,
			area = YSI_g_sPlayerArea[playerid],
			world = GetPlayerVirtualWorld(playerid);
		GetPlayerPos(playerid, x, y, z);
		if (area != NO_AREA)
		{
			if (Area_CheckArea(playerid, world, area, x, y, z)) continue;
			YSI_g_sPlayerArea[playerid] = NO_AREA;
			#if defined _YSI_GAMEMODE_PROPERTIES
				if (!Property_OnPlayerLeaveArea(playerid, area))
			#endif
					CallRemoteFunction("OnPlayerLeaveArea", "ii", playerid, area);
		}
		for (area = 0; area < MAX_AREAS; area++)
		{
			if (Area_CheckArea(playerid, world, area, x, y, z))
			{
				YSI_g_sPlayerArea[playerid] = area;
				CallRemoteFunction("OnPlayerEnterArea", "ii", playerid, area);
				break;
			}
		}
	}
#else
	HOOK__ OnPlayerUpdate(playerid)
	{
		static
			// Another hard-coded limit (max areas we can actually be in, more
			// than the max that is globally stored, but still not infinate).
			sAreas[16],
			sZones[9],
			Float:sX = 0.0,
			Float:sY = 0.0,
			Float:sZ = 0.0,
			sCur = 0,
			sNext = 0,
			sW = 0,
			sAlready = 0;
		new
			in = 0,
			idx = 0;
		// Get all the zones for this player.
		GetPlayerPos(playerid, sX, sY, sZ);
		P:7("Areas_OnPlayerUpdate: pos = %f %f %f", sX, sY, sZ);
		#if AREA_WORLDS > 0
			sW = GetPlayerVirtualWorld(playerid);
		#endif
		for ( ; (sCur = _Area_GetPlayerAreas(playerid, idx)) != NO_AREA; )
		{
			// In this zone too.
			if (Area_CheckArea(playerid, sW, sCur, sX, sY, sZ, sNext, sAreas, 0))
			{
				++idx;
				sAreas[in++] = sCur;
			}
			else
			{
				// No longer in the area they used to be in.
				Area_DoLeave(playerid, sCur, idx);
				// "Area_DoLeave" shifts all the slots, so you end up with not
				// needing to change "idx" at all.
			}
		}
		sAlready = in;
		sZones = Area_GetZones(sX, sY);
		for (idx = 0; ; )
		{
			P:7("Areas_OnPlayerUpdate: zone = %d", sZones[idx]);
			switch (sZones[idx++])
			{
				case e_AREA_ZONE_I_N:
				{
					_AREA_DO_ALL(YSI_g_sZoneIN);
				}
				case e_AREA_ZONE_I_NE:
				{
					_AREA_DO_ALL(YSI_g_sZoneINE);
				}
				case e_AREA_ZONE_I_E:
				{
					_AREA_DO_ALL(YSI_g_sZoneIE);
				}
				case e_AREA_ZONE_I_SE:
				{
					_AREA_DO_ALL(YSI_g_sZoneISE);
				}
				case e_AREA_ZONE_I_S:
				{
					_AREA_DO_ALL(YSI_g_sZoneIS);
				}
				case e_AREA_ZONE_I_SW:
				{
					_AREA_DO_ALL(YSI_g_sZoneISW);
				}
				case e_AREA_ZONE_I_W:
				{
					_AREA_DO_ALL(YSI_g_sZoneIW);
				}
				case e_AREA_ZONE_I_NW:
				{
					_AREA_DO_ALL(YSI_g_sZoneINW);
				}
				case e_AREA_ZONE_I_:
				{
					_AREA_DO_ALL(YSI_g_sZoneI);
				}
				// "Outer" zones.
				case e_AREA_ZONE_O_N:
				{
					_AREA_DO_ALL(YSI_g_sZoneON);
				}
				case e_AREA_ZONE_O_NE:
				{
					_AREA_DO_ALL(YSI_g_sZoneONE);
				}
				case e_AREA_ZONE_O_E:
				{
					_AREA_DO_ALL(YSI_g_sZoneOE);
				}
				case e_AREA_ZONE_O_SE:
				{
					_AREA_DO_ALL(YSI_g_sZoneOSE);
				}
				case e_AREA_ZONE_O_S:
				{
					_AREA_DO_ALL(YSI_g_sZoneOS);
				}
				case e_AREA_ZONE_O_SW:
				{
					_AREA_DO_ALL(YSI_g_sZoneOSW);
				}
				case e_AREA_ZONE_O_W:
				{
					_AREA_DO_ALL(YSI_g_sZoneOW);
				}
				case e_AREA_ZONE_O_NW:
				{
					_AREA_DO_ALL(YSI_g_sZoneONW);
				}
				//case e_AREA_ZONE_O_:
				//{
				//	_AREA_DO_ALL(YSI_g_sZoneO);
				//}
				case e_AREA_ZONE_X_N:
				{
					_AREA_DO_ALL(YSI_g_sZoneXN);
				}
				case e_AREA_ZONE_X_NE:
				{
					_AREA_DO_ALL(YSI_g_sZoneXNE);
				}
				case e_AREA_ZONE_X_E:
				{
					_AREA_DO_ALL(YSI_g_sZoneXE);
				}
				case e_AREA_ZONE_X_SE:
				{
					_AREA_DO_ALL(YSI_g_sZoneXSE);
				}
				case e_AREA_ZONE_X_S:
				{
					_AREA_DO_ALL(YSI_g_sZoneXS);
				}
				case e_AREA_ZONE_X_SW:
				{
					_AREA_DO_ALL(YSI_g_sZoneXSW);
				}
				case e_AREA_ZONE_X_W:
				{
					_AREA_DO_ALL(YSI_g_sZoneXW);
				}
				case e_AREA_ZONE_X_NW:
				{
					_AREA_DO_ALL(YSI_g_sZoneXNW);
				}
				case e_AREA_ZONE_X_:
				{
					// Always the last zone in the list.
					_AREA_DO_ALL(YSI_g_sZoneX);
					break;
				}
				case e_AREA_ZONE_NONE:
				{
					// Specific zone (which).
					_AREA_DO_ALL(YSI_g_sZones[((Area_MakeZone(sX) + AREAS_ZONE_PARTS) * AREAS_ZONE_ARRAY) + AREAS_ZONE_PARTS + Area_MakeZone(sY)]);
				}
			}
		}
		return 1;
	}
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player being checked for.</param>
 * <param name="world">VW the player is in.</param>
 * <param name="area">Area to check against.</param>
 * <param name="x">X position to check.</param>
 * <param name="y">Y position to check.</param>
 * <param name="z">Z position to check.</param>
 * <remarks>
 *  Checks if the given position is in the give area.  All parameters are passed
 *  to avoid calling functions over and over and over again.  If the return is
 *  not true, "area" is updated to the next one in the chain.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Area_CheckArea(playerid, world, area, Float:x, Float:y, Float:z, &next, const areas[16], already)
{
	new
		e_AREA_FLAGS:flags = YSI_g_sAreas[area][E_AREA_FLAGS];
	next = YSI_g_sAreas[area][E_AREA_UNUSED_NEXT] & AREA_NO_NEXT;
	// Are they already in this area?
	while (already--)
	{
		if (areas[already] == area)
		{
			return 0;
		}
	}
	if ((flags & e_AREA_FLAGS_ACTIVE))
	{
		P:7("Area_CheckArea: %d %d %d %f %f %f = %d", playerid, world, area, Float:x, Float:y, Float:z, _:(flags & e_AREA_FLAGS_TYPE) >>> 28);
		switch (flags & e_AREA_FLAGS_TYPE)
		{
			case e_AREA_FLAGS_CIRCLE:
			{
				// In range of a sphere perfectly level with them.
				if (!IsPlayerInRangeOfPoint(playerid, YSI_g_sAreas[area][E_AREA_POS][2], YSI_g_sAreas[area][E_AREA_POS][0], YSI_g_sAreas[area][E_AREA_POS][1], z))
				{
					return 0;
				}
			}
			case e_AREA_FLAGS_OVAL:
			{
				if (!Area_IsInCircle(x, y, x, YSI_g_sAreas[area][E_AREA_POS]))
				{
					return 0;
				}
			}
			case e_AREA_FLAGS_OVOID:
			{
				if (!Area_IsInOvoid(x, y, z, YSI_g_sAreas[area][E_AREA_POS]))
				{
					return 0;
				}
			}
			case e_AREA_FLAGS_SPHERE:
			{
				if (!IsPlayerInRangeOfPoint(playerid, YSI_g_sAreas[area][E_AREA_POS][3], YSI_g_sAreas[area][E_AREA_POS][0], YSI_g_sAreas[area][E_AREA_POS][1], YSI_g_sAreas[area][E_AREA_POS][2]))
				{
					return 0;
				}
			}
			case e_AREA_FLAGS_POLY:
			{
				if (!Area_IsInPoly(x, y, z, area))
				{
					return 0;
				}
			}
			case e_AREA_FLAGS_CUBE:
			{
				if (!Area_IsInCube(x, y, z, YSI_g_sAreas[area][E_AREA_POS]))
				{
					return 0;
				}
			}
		}
		P:7("Area_CheckArea: MAYBE");
		if (PA_Get(YSI_g_sAreas[area][E_AREA_PLAYERS], playerid))
		{
			#if AREA_WORLDS > 0
				if (Bit_Get(YSI_g_sAreas[area][E_AREA_WORLDS], world))
				{
					return 1;
				}
			#else
				#pragma unused world
				return 1;
			#endif
		}
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="x">X position to check.</param>
 * <param name="y">Y position to check.</param>
 * <param name="z">Z position to check.</param>
 * <param name="bounds">Data for the area position.</param>
 * <remarks>
 *  Checks if a point is in a given circle.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Area_IsInCircle(Float:x, Float:y, Float:z, const Float:bounds[])
{
	x -= bounds[0];
	y -= bounds[1];
	return (bounds[4] <= z <= bounds[5] && ((x * x) / bounds[2] + (y * y) / bounds[3]) < 1.0);
}

/*-------------------------------------------------------------------------*//**
 * <param name="x">X position to check.</param>
 * <param name="y">Y position to check.</param>
 * <param name="z">Z position to check.</param>
 * <param name="bounds">Data for the area position.</param>
 * <remarks>
 *  Checks if a point is in a given sphere.
 * </remarks>
 *//*------------------------------------------------------------------------**/

/*static stock Area_IsInSphere(Float:x, Float:y, Float:z, Float:bounds[])
{
	x -= bounds[0];
	y -= bounds[1];
	z -= bounds[2];
	return (((x * x) + (y * y) + (z * z)) < bounds[3]);
}*/

/*-------------------------------------------------------------------------*//**
 * <param name="x">X position to check.</param>
 * <param name="y">Y position to check.</param>
 * <param name="z">Z position to check.</param>
 * <param name="bounds">Data for the area position.</param>
 * <remarks>
 *  Checks if a point is in a given ovoid.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Area_IsInOvoid(Float:x, Float:y, Float:z, const Float:bounds[])
{
	x -= bounds[0];
	y -= bounds[1];
	z -= bounds[2];
	return (((x * x) / bounds[3] + (y * y) / bounds[4] + (z * z) / bounds[5]) < 1.0);
}

/*-------------------------------------------------------------------------*//**
 * <param name="x">X position to check.</param>
 * <param name="y">Y position to check.</param>
 * <param name="z">Z position to check.</param>
 * <param name="header">Pointer to the start of the polygon data in the array.</param>
 * <remarks>
 *  Based on IsPlayerInAreaEx by koolk in the useful functions topic.  The
 *  passed pointer is the pointer to the first set of co-ordinates in a one-
 *  way not looping linked list of points in the polygod as the data may be
 *  spread throughout the areas array.  This is as otherwise there may be
 *  enough free spaces but not in one block.
 *
 *  The code first checks if there is a height component as it's the easiest
 *  to check thus may save a load of pointless processing.  If this passes it
 *  then does the main loop.  This loops till there are no points left to do
 *  (monitored by decreasing count).  When 2 points (four pieces of data) have
 *  been checked the poiner for the data is moved on to the next group and the
 *  checking continues.
 *
 *  For simplicity's sake (and thus speed's sake) the lower pointes from the
 *  last check are saved amd used as the upper points for the next check to
 *  avoid loads of repeated array accesses and saving the last array position.
 * </remarks>
 *//*------------------------------------------------------------------------**/

/*static*/
stock Area_IsInPoly(Float:x, Float:y, Float:z, header)
{
	// First check the bounding zone.
	new
		Float:bx = x - YSI_g_sAreas[header][E_AREA_POLY_BOUND_X],
		Float:by = y - YSI_g_sAreas[header][E_AREA_POLY_BOUND_Y];
	P:7("Area_IsInPoly: %f %f %f %d", x, y, z, header);
	P:7("Area_IsInPoly: %f %f %f %d", YSI_g_sAreas[header][E_AREA_POLY_BOUND_H], (bx * bx + by * by),YSI_g_sAreas[header][E_AREA_POLY_BOUND_R], (z <= YSI_g_sAreas[header][E_AREA_POLY_BOUND_H] && (bx * bx + by * by) <= YSI_g_sAreas[header][E_AREA_POLY_BOUND_R]));
	if (!(z <= YSI_g_sAreas[header][E_AREA_POLY_BOUND_H] && (bx * bx + by * by) <= YSI_g_sAreas[header][E_AREA_POLY_BOUND_R]))
	{
		return 0;
	}
	// Within the bounding cylinder, do the more complex checks.
	new
		count = YSI_g_sAreas[header][E_AREA_POLY_COUNT];
	P:7("Area_IsInPoly: In the bounds: %d %d", count, CHILD_AREA_SLOTS);
	if (count <= CHILD_AREA_SLOTS)
	{
		// Only uses one single child slot.
		header = YSI_g_sAreas[header][E_AREA_POLY_NEXT];
		new
			lines = 0,
			done = 2,
			Float:fx = YSI_g_sAreas[header][E_AREA_CHILD_ELEMS][0],
			Float:fy = YSI_g_sAreas[header][E_AREA_CHILD_ELEMS][1],
			Float:x0 = fx,
			Float:y0 = fy,
			Float:x1 = 0.0,
			Float:y1 = 0.0;
		while (done < count)
		{
			x1 = YSI_g_sAreas[header][E_AREA_CHILD_ELEMS][done++];
			y1 = YSI_g_sAreas[header][E_AREA_CHILD_ELEMS][done++];
			// Crosses this line.
			//P:7("Area_IsInPoly: %f %f %f", y0, y, y1);
			if (((y0 <= y <= y1) || (y1 <= y <= y0)) && ((x0 + ((y - y0) * (x1 - x0) / (y1 - y0))) <= x)) ++lines;
			//P:7("Area_IsInPoly: %d %d %d %d %d", (y0 <= y <= y1), (y1 <= y <= y0), (y0 <= y <= y1) || (y1 <= y <= y0), (x0 + ((y - y0) * (x1 - x0) / (y1 - y0))) <= x, lines);
			x0 = x1;
			y0 = y1;
		}
		//P:7("Area_IsInPoly: %f %f %f", y0, y, fy);
		if (((y0 <=y <= fy) || (fy <= y <= y0)) && (x0 + ((y - y0) * (fx - x0) / (fy - y0))) <= x) ++lines;
		//P:7("Area_IsInPoly: %d %d %d %d %d", (y0 <= y <= fy), (fy <= y <= y0), (y0 <= y <= fy) || (fy <= y <= y0), (x0 + ((y - y0) * (fx - x0) / (fy - y0))) <= x, lines);
		//P:7("Area_IsInPoly: Return %d", lines);
		return isodd(lines);
	}
	else
	{
		// Has multiple children
		header = YSI_g_sAreas[header][E_AREA_POLY_NEXT];
		new
			stp = 0,
			lines = 0,
			done = 2,
			Float:fx = YSI_g_sAreas[header][E_AREA_CHILD_ELEMS][0],
			Float:fy = YSI_g_sAreas[header][E_AREA_CHILD_ELEMS][1],
			Float:x0 = fx,
			Float:y0 = fy,
			Float:x1 = 0.0,
			Float:y1 = 0.0;
		while (count > 0)
		{
			stp = min(count, CHILD_AREA_SLOTS);
			while (done < stp)
			{
				x1 = YSI_g_sAreas[header][E_AREA_CHILD_ELEMS][done++];
				y1 = YSI_g_sAreas[header][E_AREA_CHILD_ELEMS][done++];
				// Crosses this line.
				if (((y0 <= y <= y1) || (y1 <= y <= y0)) && (x0 + ((y - y0) * (x1 - x0) / (y1 - y0))) <= x) ++lines;
				x0 = x1;
				y0 = y1;
			}
			count -= CHILD_AREA_SLOTS;
			done = 0;
			header = YSI_g_sAreas[header][E_AREA_POLY_NEXT];
		}
		//x1 = YSI_g_sAreas[pointer][E_AREA_CHILD_ELEMS][0];
		// Link the last and first points to complete the perimeter.
		if (((y0 <=y <= fy) || (fy <= y <= y0)) && (x0 + ((y - y0) * (fx - x0) / (fy - y0))) <= x) ++lines;
		//printf("Area_IsInPoly: Return %d", lines);
		return isodd(lines);
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="x">X position to check.</param>
 * <param name="y">Y position to check.</param>
 * <param name="z">Z position to check.</param>
 * <param name="lower">The lower corner of the cube.</param>
 * <param name="upper">The upper corner of the cube.</param>
 * <remarks>
 *  Checks if a point is in a given cube.  This is another multi slot shape
 *  but is much simpler than the poly as it's always 2 slots so we can easilly
 *  get the data in one lump.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Area_IsInCube(Float:x, Float:y, Float:z, const Float:bounds[])
{
	return (bounds[0] <= x <= bounds[3] && bounds[1] <= y <= bounds[4] && bounds[2] <= z <= bounds[5]);
}

/*-------------------------------------------------------------------------*//**
 * <param name="x">X position to check.</param>
 * <param name="y">Y position to check.</param>
 * <param name="bounds">Data for the area position.</param>
 * <remarks>
 *  Checks if a point is in a given box.  There is no height check with this
 *  one as any one area slot has 4 points which for this are upper and lower
 *  x and y, adding a height check would make it require 2 slots and basically
 *  make it a cube check.
 * </remarks>
 *//*------------------------------------------------------------------------**/

/*static stock Area_IsInBox(Float:x, Float:y, Float:bounds[])
{
	return (bounds[0] <= x <= bounds[2] && bounds[1] <= y <= bounds[3]);
}*/

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to get area of.</param>
 * <returns>
 *  The area a player is in or -1.
 * </returns>
 * <remarks>
 *  Deprecated.
 * </remarks>
 *//*------------------------------------------------------------------------**/

//foreign Area_GetPlayerArea(playerid);

#pragma deprecated Use Area_GetPlayerAreas
stock Area_GetPlayerArea(playerid)
{
	if (VALID_PLAYERID(playerid))
	{
		return YSI_g_sPlayerArea[playerid][0];
	}
	return NO_AREA;
}


/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to set areas of.</param>
 * <param name="idx">Which slot to set.</param>
 * <param name="area">The area to store in that slot.</param>
 * <remarks>
 *  Sets a player as in a slot.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock
	_Area_SetPlayerAreas(playerid, idx, area)
{
	if (idx < AREAS_MAX_OVERLAPS)
	{
		YSI_g_sPlayerArea[playerid][idx] = area;
	}
	else
	{
		// Use PVars to store extended areas.
		static
			sProp[12] = "y_areas_";
		valstr(sProp[8], idx);
		if (area == NO_AREA)
		{
			DeletePVar(playerid, sProp);
		}
		else
		{
			SetPVarInt(playerid, sProp, area);
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  _Area_GetPlayerAreas
 *  Area_GetPlayerAreas
 * </summary>
 * <param name="playerid">Player to get areas of.</param>
 * <param name="idx">Which area to get.</param>
 * <returns>
 *  The area a player is in or -1.
 * </returns>
 * <remarks>
 *  Replaces Area_GetPlayerArea for multiple areas.  Includes an internal
 *  version for tighter loops within this code to use once it is known that a
 *  player exists, and without using the global function system.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock
	_Area_GetPlayerAreas(playerid, idx)
{
	if (idx < AREAS_MAX_OVERLAPS)
	{
		return YSI_g_sPlayerArea[playerid][idx];
	}
	else
	{
		// Use PVars to store extended areas.
		static
			sProp[12] = "y_areas_";
		valstr(sProp[8], idx);
		if (GetPVarType(playerid, sProp) == PLAYER_VARTYPE_INT)
		{
			return GetPVarInt(playerid, sProp);
		}
	}
	return NO_AREA;
}

FOREIGN__ Area_GetPlayerAreas(playerid, idx);

GLOBAL__ Area_GetPlayerAreas(playerid, idx)
{
	if (VALID_PLAYERID(playerid))
	{
		if (0 <= idx <= 999)
		{
			return _Area_GetPlayerAreas(playerid, idx);
		}
	}
	return NO_AREA;
}

/*-------------------------------------------------------------------------*//**
 * <param name="area">Area to set for.</param>
 * <param name="playerid">Player to set for.</param>
 * <param name="set">Wether or not the player can use the area.</param>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Area_SetPlayer(area, playerid, bool:set);

GLOBAL__ void:Area_SetPlayer(area, playerid, bool:set)
{
	if (Area_IsActive(area))
	{
		PA_Set(YSI_g_sAreas[area][E_AREA_PLAYERS], playerid, set);
		//return 1;
	}
	//return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="area">Area to get for.</param>
 * <param name="playerid">Player to get for.</param>
 * <remarks>
 *  Can the player USE this area (not are they in it)?
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Area_GetPlayer(area, playerid);

GLOBAL__ bool:Area_GetPlayer(area, playerid)
{
	if (Area_IsActive(area))
	{
		return PA_Get(YSI_g_sAreas[area][E_AREA_PLAYERS], playerid);
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="area">Area to set for.</param>
 * <param name="world">World to set for.</param>
 * <param name="set">Wether or not the area is active in this world.</param>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Area_SetWorld(area, world, bool:set);

GLOBAL__ void:Area_SetWorld(area, world, bool:set)
{
	#if AREA_WORLDS > 0
		if (Area_IsActive(area))
		{
			Bit_Set(YSI_g_sAreas[area][E_AREA_WORLDS], world, set);
			//return 1;
		}
	#else
		#pragma unused area, world, set
	#endif
	//return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="area">Area to set for.</param>
 * <param name="world">World to set for.</param>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Area_GetWorld(area, world);

GLOBAL__ bool:Area_GetWorld(area, world)
{
	#if AREA_WORLDS > 0
		if (Area_IsActive(area))
		{
			return Bit_Get(YSI_g_sAreas[area][E_AREA_WORLDS], world);
		}
		return false;
	#else
		#pragma unused area, world
		return true;
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <param name="area">Area to set for.</param>
 * <param name="set">Wether or not all players can use this area.</param>
 *//*------------------------------------------------------------------------**/

FOREIGN__ void:Area_SetAllPlayers(area, bool:set);

GLOBAL__ void:Area_SetAllPlayers(area, bool:set)
{
	if (Area_IsActive(area))
	{
		PA_Init(YSI_g_sAreas[area][E_AREA_PLAYERS], set);
		//return 1;
	}
	//return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="area">Area to check.</param>
 * <returns>
 *  Is the passed area valid and active.
 * </returns>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Area_IsValid(area);

GLOBAL__ bool:Area_IsValid(area)
{
	return bool:Area_IsActive(area);
}

/*-------------------------------------------------------------------------*//**
 * <param name="area">Area to check.</param>
 * <returns>
 *  Is the passed area valid and empty.
 * </returns>
 * <remarks>
 *  Currently very slow as it has to loop through multiple players!  I may add
 *  an entry counter to zones to make this O(1) instead of O(nm).
 * </remarks>
 *//*------------------------------------------------------------------------**/

FOREIGN__ bool:Area_IsEmpty(area);

GLOBAL__ bool:Area_IsEmpty(area)
{
	new
		z = 0;
	if (Area_IsActive(area))
	{
		FOREACH__ (new playerid : Player)
		{
			for (new i = 0; ; ++i)
			{
				z = _Area_GetPlayerAreas(playerid, i);
				if (z == NO_AREA)
				{
					break;
				}
				else if (z == area)
				{
					return false;
				}
			}
		}
	}
	return true;
}

/*-------------------------------------------------------------------------*//**
 * <param name="area">Area to set for.</param>
 * <param name="callback">Callback to use.</param>
 * <remarks>
 *  Adds a y_inline style callback (publics included) to an area to be called
 *  when a player enters it.  This is NOT a remote function and instead records
 *  the data locally to call functions in the correct script (or they'll just
 *  end up crashing as you will be jumping to an arbitrary address in a script
 *  that doesn't have sensible code at that address.
 * </remarks>
 *//*------------------------------------------------------------------------**/

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">The player that just entered the area.</param>
 * <param name="areaid">The area they entered.</param>
 *//*------------------------------------------------------------------------**/

static stock Area_DoEnter(playerid, areaid, &idx)
{
	// Save their area to the list of areas that they are currently in.
	//YSI_g_sPlayerArea[playerid] = sCur;
	_Area_SetPlayerAreas(playerid, idx++, areaid);
	// Call the callback in all scripts.
	CallRemoteFunction("OnPlayerEnterArea", "ii", playerid, areaid);
	//broadcastfunc _Area_DoEnter(playerid, areaid);
}

/*remotefunc _Area_DoEnter(playerid, areaid)
{
	if (YSI_g_sHasCallbacks & 1)
	{
		CallLocalFunction("OnPlayerEnterArea", "ii", playerid, areaid);
	}
	if (YSI_g_sHasCallbacks & 4)
	{
		//Hook_OnPlayerEnterArea(playerid, areaid);
	}
	return 1;
}*/

forward OnPlayerEnterArea(playerid, areaid);

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">The player that just left the area.</param>
 * <param name="areaid">The area they left.</param>
 *//*------------------------------------------------------------------------**/

//remotefunc Area_DoLeave(playerid, areaid)
static stock Area_DoLeave(playerid, areaid, idx)
{
	// Remove this area from the list of areas.
	new
		cur = 0;
	// Shift up the zones.
	while ((cur = _Area_GetPlayerAreas(playerid, idx + 1)) != NO_AREA)
	{
		_Area_SetPlayerAreas(playerid, idx++, cur);
	}
	_Area_SetPlayerAreas(playerid, idx, NO_AREA);
	// Call the callback.
	CallRemoteFunction("OnPlayerLeaveArea", "ii", playerid, areaid);
	/*if (YSI_g_sHasCallbacks & 2)
	{
		CallLocalFunction("OnPlayerLeaveArea", "ii", playerid, areaid);
	}
	if (YSI_g_sHasCallbacks & 8)
	{
		//Hook_OnPlayerLeaveArea(playerid, areaid);
	}*/
	return 1;
}

forward OnPlayerLeaveArea(playerid, areaid);

//#undef _GROUP_MAKE_LIMIT
//#undef _GROUP_MAKE_NAME

#include "..\..\YSI_Core\y_master"

