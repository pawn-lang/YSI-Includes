/*----------------------------------------------------------------------------*-
					=============================
					Y Sever Includes - Areas Core
					=============================
Description:
	Handles area checks for player location based code not involving CPs.
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
	27/08/07:
		Made master compatible.
	03/08/07:
		Updated timer system.
	31/07/07:
		Made Area_GetPlayerArea safe.
	08/05/07:
		First version.
Functions:
	Public:
		Area_Loop - Main loop for checking who's where.
		Area_Remote - Does minor functions remotely.
		Area_AddRemote - Adds areas remotely.
		YSIM_Areas - Master system interface.
		Area_Broadcast - Recieves transmitted areas.
		Area_UpdateEmpty - Resets the empty array after master change.
	Core:
		Area_Area - Constructor.
		Area_CheckArea - Gets an area's type anx calls the relevant function.
		Area_OnPlayerConnect - Called when a player connects.
	Stock:
		Area_Delete - Deletes an area.
		Area_AddCube - Adds a cube.
		Area_AddBox - Adds a box.
		Area_AddCircle - Adds a circle.
		Area_AddSphere - Adds a sphere.
		Area_AddPoly - Adds a polygon.
		Area_GetPlayerArea - Gets the area a player is in.
		Area_SetPlayer - Sets wether a player can use this area.
		Area_SetAllPlayers - Sets wether all players can use this area.
		Area_SetAllWorlds - Sets wether all worlds have this are.
		Area_SetWorld - Sets wether this world has this area.
		Area_IsValid - Checks if an area is valid.
	Static:
		Area_IsInCircle - Checks if a player is in this circular area.
		Area_IsInSphere - Checks if a player is in this spherical area.
		Area_IsInPoly - Checks if a player is in this polygonal area.
		Area_IsInCube - Checks if a player is in this cubic area.
		Area_IsInBox - Checks if a player is in this rectangular area.
		Area_AddToUnused - Adds a area pointer to the unused list.
		Area_GetFreeSlot - Gets the next free area slot.
	Inline:
		Area_IsActive - Checks if an area is active.
		Area_GetEmptySlotCount - Gets the number of empty slots.
		Area_AddSlots - Removes slots from the unused count.
	API:
		-
Callbacks:
	OnPlayerEnterArea - Called when a player enters an area.
	OnPlayerLeaveArea - Called when a player leaves an area.
Definitions:
	MAX_AREAS - Max number of areas.
	NO_AREA - Fail return.
	SINGLE_SLOT_AREA - Marker for only one part to the area.
	AREA_NO_NEXT - Marker for end of a list.
	AREA_WORLDS - Number of worlds an area can be in.
	AREA_WORLD_COUNT - Number of cells required for a bit array of AREA_WORLDS.
Enums:
	e_AREA_FLAGS - Flags for each area.
	E_AREA - Structure for part of an areas data.
Macros:
	-
Tags:
	-
Variables:
	Global:
		-
	Static:
		YSI_g_sUnusedAreas - Pointer to the first unused area.
		YSI_g_sLastUnused - Pointer to the last unused area.
		YSI_g_sFreeCount - Number of unused slots.
		YSI_g_sAreas - Array of area data.
		YSI_g_sPlayerArea - Array of players' current areas.
Commands:
	-
Compile options:
	-
Operators:
	-
-*----------------------------------------------------------------------------*/

#include "internal\y_version"

#include "y_bit"
#include "y_playerarray"

#include "y_iterate"
#include "y_debug"

#include "y_inline"
#include "y_remote"

#if defined AREAS_USE_TIMER
	#include "y_timers"
#endif
#include "internal\y_natives"

#if !defined MAX_AREAS
	#define MAX_AREAS (1024)
#elseif MAX_AREAS >= 0x1FFF
	#error This version does not support more than 8190 areas
#endif

#define _GROUP_MAKE_NAME_AREAS<%0...%1>   %0Area%1
#define _GROUP_MAKE_LIMIT_AREAS           MAX_AREAS

#include "y_groups"

#define YSIM_U_DISABLE
#include "y_master"

#include "y_hooks"

#define NO_AREA          (-1)
#define SINGLE_SLOT_AREA (e_AREA_FLAGS_NEXT)
#define AREA_NO_NEXT     (_:e_AREA_FLAGS_NEXT)

#if !defined AREAS_ZONE_SIZE
	#define AREAS_ZONE_SIZE 500
#endif

#if !defined AREAS_ZONE_BOUNDS
	#define AREAS_ZONE_BOUNDS 4000
#endif

#define AREAS_ZONE_ARRAY (ceildiv(AREAS_ZONE_BOUNDS * 2, AREAS_ZONE_SIZE))

#if !defined AREA_WORLDS
	#define AREA_WORLDS 256
#endif

#define AREAS_ZONE_PARTS (ceildiv(AREAS_ZONE_BOUNDS, AREAS_ZONE_SIZE))
#define Area_MakeZone(%0) (floatround((%0) / AREAS_ZONE_SIZE.0, floatround_floor)) // - AREAS_ZONE_PARTS)

#define _AREAS_ADD_TO_ZONE(%0,%1,%2,%3) YSI_g_sAreas[%2][E_AREA_FLAGS]=(YSI_g_sAreas[%2][E_AREA_FLAGS]&e_AREA_FLAGS_REST)|(e_AREA_FLAGS:%0&e_AREA_FLAGS_NEXT|e_AREA_FLAGS:(%3<<14)&e_AREA_FLAGS_COUNT),%0=%1

//#define _AREAS_ZONES_O(%0) return e_AREA_ZONE_O_%0
//#define _AREAS_ZONES_I(%0) return e_AREA_ZONE_I_%0
//#define _AREAS_ZONES_X(%0) return e_AREA_ZONE_X_%0

#define _AREAS_ZONES_O(%0) return _AREAS_ADD_TO_ZONE(YSI_g_sZoneO%0,area,last,e_AREA_ZONE_O_%0)
#define _AREAS_ZONES_I(%0) return _AREAS_ADD_TO_ZONE(YSI_g_sZoneI%0,area,last,e_AREA_ZONE_I_%0)
#define _AREAS_ZONES_X(%0) return _AREAS_ADD_TO_ZONE(YSI_g_sZoneX%0,area,last,e_AREA_ZONE_X_%0)

#define _AREAS_ZONES_I_GRID zx=1// zx=Area_MakeZone(minx);zy=Area_MakeZone(miny);if(zx==Area_MakeZone(maxx)&&zy==Area_MakeZone(maxy))return _AREAS_MAKE_ZONE(zx,zy),_AREAS_ADD_TO_ZONE(YSI_g_sZones[zy],area,last,zy)

#define _AREAS_MAKE_ZONE(%0,%1) %1+=((%0)+AREAS_ZONE_PARTS)*AREAS_ZONE_ARRAY+AREAS_ZONE_PARTS

#define _AREA_DO_ALL(%0) sCur=%0;while(sCur!=AREA_NO_NEXT)if(Area_CheckArea(playerid,sW,sCur,sX,sY,sZ))return Area_DoEnter(playerid,(YSI_g_sPlayerArea[playerid]=sCur))

#define _AREAS_DO_REMOVE(%0,%1,%2) new __z=-1,__y=%0;while(__y!=%1)__z=__y,__y=_:(YSI_g_sAreas[__z][E_AREA_FLAGS] & e_AREA_FLAGS_NEXT);return ((__z==-1)?(%0=%2):(_:(YSI_g_sAreas[__z][E_AREA_FLAGS]=YSI_g_sAreas[__z][E_AREA_FLAGS]&e_AREA_FLAGS_REST|(e_AREA_FLAGS:%2&e_AREA_FLAGS_NEXT))))

enum e_AREA_FLAGS
{
	e_AREA_FLAGS_NEXT   = 0x2000 - 1 <<  0, //0x00001FFF,
	e_AREA_FLAGS_COUNT  = 0x2000 - 1 << 14, //0x07FFC000,
	e_AREA_FLAGS_REST   = ~(e_AREA_FLAGS_NEXT | e_AREA_FLAGS_COUNT),
	
	//e_AREA_FLAGS_TYPE   = 0x38000000,
	e_AREA_FLAGS_SPHERE = 1 << 27, //0x08000000,
	e_AREA_FLAGS_POLY   = 2 << 27, //0x10000000,
	e_AREA_FLAGS_CUBE   = 3 << 27, //0x18000000,
	e_AREA_FLAGS_BOX    = 4 << 27, //0x20000000,
	e_AREA_FLAGS_CIRCLE = 5 << 27, //0x28000000,
	e_AREA_FLAGS_RES_0  = 6 << 27, //0x28000000,
	e_AREA_FLAGS_TYPE   = 7 << 27, //0x28000000,
	
	e_AREA_FLAGS_ACTIVE = 1 << 30,
	e_AREA_FLAGS_USED   = 1 << 31
}

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

enum E_AREA
{
	e_AREA_FLAGS:E_AREA_FLAGS,
	#if AREA_WORLDS > 0
		BitArray:E_AREA_WORLDS<AREA_WORLDS>,
	#endif
	#if YSIM_HAS_MASTER
		E_AREA_MASTER,
	#endif
	PlayerArray:E_AREA_PLAYERS<MAX_PLAYERS>,
	Float:E_AREA_POS[4]
}

static stock
	YSI_g_sUnusedAreas = 0,
	//YSI_g_sLastUnused = MAX_AREAS - 1,
	YSI_g_sFreeCount = MAX_AREAS,
	YSI_g_sAreas[MAX_AREAS][E_AREA],
	YSI_g_sPlayerArea[MAX_PLAYERS] = {NO_AREA, ...},
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

/*----------------------------------------------------------------------------*-
Function:
	OnScriptInit
Params:
	-
Return:
	-
Notes:
	Sets up required variables.  Note that this hooks "OnScriptInit",
	"OnGameModeInit" and "OnFilterScript".  This is because ALL scripts need to
	initialise some things, and only the master needs to initialise others.
-*----------------------------------------------------------------------------*/

mhook OnScriptInit()
{
	for (new i = 0; i != MAX_AREAS - 1; ++i)
	{
		YSI_g_sAreas[i][E_AREA_FLAGS] = e_AREA_FLAGS:(i + 1);
	}
	YSI_g_sAreas[MAX_AREAS - 1][E_AREA_FLAGS] = e_AREA_FLAGS:AREA_NO_NEXT;
	//for (new i = 0; i != AREAS_ZONE_ARRAY * AREAS_ZONE_ARRAY; ++i)
	//{
	//	YSI_g_sZones[i] = -1;
	//}
	return 1;
}

#if !defined FILTERSCRIPT
	hook OnGameModeInit()
	{
		if (!YSI_FILTERSCRIPT)
		{
			new
				buffer;
			YSI_g_sHasCallbacks = 0;
			YSI_g_sHasCallbacks |= funcidx("OnPlayerEnterArea") == -1 ? 0 : 1;
			YSI_g_sHasCallbacks |= funcidx("OnPlayerLeaveArea") == -1 ? 0 : 2;
			YSI_g_sHasCallbacks |= AMX_GetPublicEntry(0, buffer, "@yH_PlayerEnterArea") ? 4 : 0;
			YSI_g_sHasCallbacks |= AMX_GetPublicEntry(0, buffer, "@yH_PlayerLeaveArea") ? 8 : 0;
		}
	}
#endif

hook OnFilterScriptInit()
{
	new
		buffer;
	YSI_g_sHasCallbacks = 0;
	YSI_g_sHasCallbacks |= funcidx("OnPlayerEnterArea") == -1 ? 0 : 1;
	YSI_g_sHasCallbacks |= funcidx("OnPlayerLeaveArea") == -1 ? 0 : 2;
	YSI_g_sHasCallbacks |= AMX_GetPublicEntry(0, buffer, "@yH_PlayerEnterArea") ? 4 : 0;
	YSI_g_sHasCallbacks |= AMX_GetPublicEntry(0, buffer, "@yH_PlayerLeaveArea") ? 8 : 0;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_GetEmptySlotCount
Params:
	-
Return:
	Number of unused area slots.
Notes:
	-
-*----------------------------------------------------------------------------*/

#define Area_GetEmptySlotCount() \
	(YSI_g_sFreeCount)

/*----------------------------------------------------------------------------*-
Function:
	Area_AddSlots
Params:
	num - Number of slots to add.
Return:
	-
Notes:
	Actually removes slots from the unused count.
-*----------------------------------------------------------------------------*/

#define Area_AddSlots(%1) \
	YSI_g_sFreeCount -= (%1)

/*----------------------------------------------------------------------------*-
Function:
	Area_IsActive
Params:
	area - Area to check validity of
Return:
	-
Notes:
	An area slot could be used but still invalid if it's not the first slot in
	an area set.
-*----------------------------------------------------------------------------*/

#define Area_IsActive(%1) \
	((%1) >= 0 && (%1) < MAX_AREAS && (YSI_g_sAreas[(%1)][E_AREA_FLAGS] & e_AREA_FLAGS_ACTIVE))

/*----------------------------------------------------------------------------*-
Function:
	Area_GetFreeSlot
Params:
	-
Return:
	Next available slot.
Notes:
	Gets an empty slot, removes it from the unused list and returs a pointer.
-*----------------------------------------------------------------------------*/

static stock Area_GetFreeSlot()
{
	P:4("Area_GetFreeSlot called");
	if (YSI_g_sUnusedAreas == AREA_NO_NEXT) return NO_AREA;
	P:7("Area_GetFreeSlot: 1");
	new
		old = YSI_g_sUnusedAreas;
	YSI_g_sUnusedAreas = YSI_g_sAreas[old][E_AREA_FLAGS];
	--YSI_g_sFreeCount;
	return old;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_Delete
Params:
	area - Area to remove from the list.
Return:
	-
Notes:
	You can only remove areas which are at the start of a list.
-*----------------------------------------------------------------------------*/

foreign Area_Delete(area);

global Area_Delete(area)
{
	if (!Area_IsActive(area))
	{
		return 0;
	}
	new
		e_AREA_FLAGS:flags = YSI_g_sAreas[area][E_AREA_FLAGS];
	switch (flags & e_AREA_FLAGS_TYPE)
	{
		case e_AREA_FLAGS_CUBE:
		{
			// Two blocks used - simple.
			new
				second = _:(flags & e_AREA_FLAGS_NEXT);
			flags = YSI_g_sAreas[second][E_AREA_FLAGS];
			YSI_g_sAreas[second][E_AREA_FLAGS] = e_AREA_FLAGS:YSI_g_sUnusedAreas;
			YSI_g_sAreas[area][E_AREA_FLAGS] = e_AREA_FLAGS:second;
			YSI_g_sUnusedAreas = area;
			YSI_g_sFreeCount += 2;
			// Remove this one from the zone it was in.
		}
		case e_AREA_FLAGS_POLY:
		{
			// Many blocks used - hard.
			new
				count =  _:(flags & e_AREA_FLAGS_COUNT) >> 14,
				next = _:(YSI_g_sAreas[area][E_AREA_FLAGS] = flags & e_AREA_FLAGS_NEXT);
			count = ceildiv(count, 4);
			YSI_g_sFreeCount += count;
			while (--count)
			{
				next = _:(YSI_g_sAreas[next][E_AREA_FLAGS] = YSI_g_sAreas[next][E_AREA_FLAGS] & e_AREA_FLAGS_NEXT);
			}
			flags = YSI_g_sAreas[next][E_AREA_FLAGS];
			YSI_g_sAreas[next][E_AREA_FLAGS] = e_AREA_FLAGS:YSI_g_sUnusedAreas;
			YSI_g_sUnusedAreas = area;
		}
		default:
		{
			// Only one block used - easy.
			YSI_g_sAreas[area][E_AREA_FLAGS] = e_AREA_FLAGS:YSI_g_sUnusedAreas;
			YSI_g_sUnusedAreas = area;
			++YSI_g_sFreeCount;
			// Remove this one from the zone it was in.
		}
	}
	Area_DoRemove(_:(flags & e_AREA_FLAGS_COUNT), area, _:(flags & e_AREA_FLAGS_NEXT));
	return 1;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_DoRemove
Params:
	zone - The zone this area is in (right shifted 14).
	start - The first of the allocated areas being removed.
	end - The area in this zone after the last removed one.
Return:
	-
Notes:
	Very tightly integrated with "Area_Delete", to the point where I could just
	make them one function if I wanted (but I won't).
-*----------------------------------------------------------------------------*/

static stock Area_DoRemove(zone, start, end)
{
	//printf("remove %d %d %d %d", zone << 14, start, end, (e_AREA_ZONE_I_   << 14 & _:e_AREA_FLAGS_COUNT));
	// Actually "zone << 14", but that's not important.
	switch (zone)
	{
		case (e_AREA_ZONE_I_N  << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneIN,  start, end);}
		case (e_AREA_ZONE_I_NE << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneINE, start, end);}
		case (e_AREA_ZONE_I_E  << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneIE,  start, end);}
		case (e_AREA_ZONE_I_SE << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneISE, start, end);}
		case (e_AREA_ZONE_I_S  << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneIS,  start, end);}
		case (e_AREA_ZONE_I_SW << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneISW, start, end);}
		case (e_AREA_ZONE_I_W  << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneIW,  start, end);}
		case (e_AREA_ZONE_I_NW << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneINW, start, end);}
		case (e_AREA_ZONE_I_   << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneI,   start, end);}
		// "Outer" zones.  -4000 > x, y > 4000;
		case (e_AREA_ZONE_O_N  << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneON,  start, end);}
		case (e_AREA_ZONE_O_NE << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneONE, start, end);}
		case (e_AREA_ZONE_O_E  << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneOE,  start, end);}
		case (e_AREA_ZONE_O_SE << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneOSE, start, end);}
		case (e_AREA_ZONE_O_S  << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneOS,  start, end);}
		case (e_AREA_ZONE_O_SW << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneOSW, start, end);}
		case (e_AREA_ZONE_O_W  << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneOW,  start, end);}
		case (e_AREA_ZONE_O_NW << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneONW, start, end);}
		//e_AREA_ZONE_O_,   // Can't be in all of O, but none of I.
		// "Extra" zones.  In a quadrant, but spanning the +-4000 boundary.
		case (e_AREA_ZONE_X_N  << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneXN,  start, end);}
		case (e_AREA_ZONE_X_NE << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneXNE, start, end);}
		case (e_AREA_ZONE_X_E  << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneXE,  start, end);}
		case (e_AREA_ZONE_X_SE << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneXSE, start, end);}
		case (e_AREA_ZONE_X_S  << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneXS,  start, end);}
		case (e_AREA_ZONE_X_SW << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneXSW, start, end);}
		case (e_AREA_ZONE_X_W  << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneXW,  start, end);}
		case (e_AREA_ZONE_X_NW << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneXNW, start, end);}
		// Extra zones.  For when areas are too big for a quadrant.
		case (e_AREA_ZONE_X_   << 14 & _:e_AREA_FLAGS_COUNT): {_AREAS_DO_REMOVE(YSI_g_sZoneX,   start, end);}
		default: {_AREAS_DO_REMOVE(YSI_g_sZones[zone], start, end);}
	}
	return 0;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_GetZones
Params:
	Float:x - Start of an area.
	Float:y - Start of an area.
Return:
	All the zones this position overlaps.
Notes:
	The most zones you can be in at once is 9 - I_, I_S, I_E, I_SE, X_, X_S,
	X_E, X_SE, Z_ (or similar corners - NOT in O_ though).
-*----------------------------------------------------------------------------*/

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

/*----------------------------------------------------------------------------*-
Function:
	Area_DetermineZone
Params:
	Float:minx - Start of an area.
	Float:miny - Start of an area.
	Float:maxx - End of an area.
	Float:maxy - End of an area.
	area - The area to add to the determined zone.
	last - The last slot that makes up the current zone.
Return:
	-
Notes:
	Finds the smallest zone that this area will fit in completely.
-*----------------------------------------------------------------------------*/

static stock Area_DetermineZone(Float:minx, Float:miny, Float:maxx, Float:maxy, area, last)
{
	new
		zx,
		zy;
	// This optimises based on the fact that (by definition) maxx can't be lower
	// than minx and maxy can't be lower than miny, meaning we can skip certain
	// checks in some cases.
	if (AREAS_ZONE_BOUNDS.0 <= minx)       // Western edge.
	{
		if (0.0 <= miny)                  // Southern edge.
		{
			_AREAS_ZONES_O(NE);
			//YSI_g_sAreas[last][E_AREA_FLAGS]=(YSI_g_sAreas[last][E_AREA_FLAGS]&e_AREA_FLAGS_REST)|(e_AREA_FLAGS:YSI_g_sZoneXNE&e_AREA_FLAGS_NEXT|e_AREA_FLAGS(e_AREA_ZONE_X_NE<<14)&e_AREA_FLAGS_COUNT),YSI_g_sZoneXNE=area;
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
							(e_AREA_FLAGS:(zy << 14) & e_AREA_FLAGS_COUNT);
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
							(e_AREA_FLAGS:(zy << 14) & e_AREA_FLAGS_COUNT);
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
							(e_AREA_FLAGS:(zy << 14) & e_AREA_FLAGS_COUNT);
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
							(e_AREA_FLAGS:(zy << 14) & e_AREA_FLAGS_COUNT);
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

/*----------------------------------------------------------------------------*-
Function:
	Area_AddTo
Params:
	area - Area to set for.
	set - Wether or not this area is usable in all worlds.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*-
Function:
	Area_SetAllWorlds
Params:
	area - Area to set for.
	set - Wether or not this area is usable in all worlds.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

foreign Area_SetAllWorlds(area, bool:set);

global Area_SetAllWorlds(area, bool:set)
{
	#if AREA_WORLDS > 0
		if (Area_IsActive(area))
		{
			Bit_SetAll(YSI_g_sAreas[area][E_AREA_WORLDS], set, bits<AREA_WORLDS>);
			return 1;
		}
	#else
		#pragma unused area, set
	#endif
	return 0;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_AddCube
Params:
	Float:minx - Lowest X corner of box
	Float:miny - Lowest Y corner of box.
	Float:minx - Lowest Z corner of box.
	Float:maxx - Highest X corner of box.
	Float:maxy - Highest Y corner of box.
	Float:maxz - Highest Z corner of box.
Return:
	Area slot or NO_AREA
Notes:
	-
-*----------------------------------------------------------------------------*/

foreign Area_AddCube(Float:x0, Float:y0, Float:z0, Float:x1, Float:y1, Float:z1);

global Area_AddCube(Float:x0, Float:y0, Float:z0, Float:x1, Float:y1, Float:z1)
{
	if (Area_GetEmptySlotCount() < 2) return NO_AREA;
	new
		slot = Area_GetFreeSlot(),
		next = Area_GetFreeSlot();
	YSI_g_sAreas[slot][E_AREA_FLAGS] = e_AREA_FLAGS_CUBE | e_AREA_FLAGS_ACTIVE | e_AREA_FLAGS_USED | e_AREA_FLAGS:next | e_AREA_FLAGS:(2 << 14);
	YSI_g_sAreas[slot][E_AREA_POS][0] = x0;
	YSI_g_sAreas[slot][E_AREA_POS][1] = y0;
	YSI_g_sAreas[slot][E_AREA_POS][2] = z0;
	YSI_g_sAreas[next][E_AREA_FLAGS] = SINGLE_SLOT_AREA | e_AREA_FLAGS_USED;
	YSI_g_sAreas[next][E_AREA_POS][0] = x1;
	YSI_g_sAreas[next][E_AREA_POS][1] = y1;
	YSI_g_sAreas[next][E_AREA_POS][2] = z1;
	PA_FastInit(YSI_g_sAreas[slot][E_AREA_PLAYERS]);
	NO_GROUPS()
	{
		PA_Init(YSI_g_sAreas[slot][E_AREA_PLAYERS], true);
	}
	#if YSIM_HAS_MASTER
		YSI_g_sAreas[slot][E_AREA_MASTER] = YSI_g_sAreas[next][E_AREA_MASTER] = Master_Caller();
	#endif
	Area_SetAllWorlds(slot, true);
	Area_DetermineZone(x0, y0, x1, y1, slot, next);
	return slot;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_AddBox
Params:
	Float:minx - Lowest X corner of box
	Float:miny - Lowest Y corner of box.
	Float:maxx - Highest X corner of box.
	Float:maxy - Highest Y corner of box.
Return:
	Area slot or NO_AREA
Notes:
	-
-*----------------------------------------------------------------------------*/

foreign Area_AddBox(Float:minx, Float:miny, Float:maxx, Float:maxy);

global Area_AddBox(Float:minx, Float:miny, Float:maxx, Float:maxy)
{
	new
		slot;
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
	YSI_g_sAreas[slot][E_AREA_FLAGS] = SINGLE_SLOT_AREA | e_AREA_FLAGS_BOX | e_AREA_FLAGS_USED | e_AREA_FLAGS_ACTIVE | e_AREA_FLAGS:(1 << 14);
	YSI_g_sAreas[slot][E_AREA_POS][0] = minx;
	YSI_g_sAreas[slot][E_AREA_POS][1] = miny;
	YSI_g_sAreas[slot][E_AREA_POS][2] = maxx;
	YSI_g_sAreas[slot][E_AREA_POS][3] = maxy;
	PA_FastInit(YSI_g_sAreas[slot][E_AREA_PLAYERS]);
	NO_GROUPS()
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

/*----------------------------------------------------------------------------*-
Function:
	Area_AddCircle
Params:
	Float:x - X position of circle.
	Float:y - Y position of circle.
	Float:r - Radius of circle.
	Float:h - Ceiling of circle.
Return:
	Area slot or NO_AREA
Notes:
	Technically a cylinder, no lower bound (ceiling added cos there was a
	spare slot in the 4 float design which may as well have been used).
-*----------------------------------------------------------------------------*/

stock Area_AddCircle(Float:x, Float:y, Float:r, Float:h = FLOAT_INFINITY)
{
	return _Area_AddCircle(x, y, r, h);
}

foreign _Area_AddCircle(Float:x, Float:y, Float:r, Float:h);

global _Area_AddCircle(Float:x, Float:y, Float:r, Float:h)
{
	new
		slot = Area_GetFreeSlot();
	if (slot == NO_AREA) return NO_AREA;
	printf("%f %f %f %f", x - r, y - r, x + r, y + r);
	YSI_g_sAreas[slot][E_AREA_FLAGS] = SINGLE_SLOT_AREA | e_AREA_FLAGS_CIRCLE | e_AREA_FLAGS_USED | e_AREA_FLAGS_ACTIVE | e_AREA_FLAGS:(1 << 14);
	YSI_g_sAreas[slot][E_AREA_POS][0] = x;
	YSI_g_sAreas[slot][E_AREA_POS][1] = y;
	YSI_g_sAreas[slot][E_AREA_POS][2] = r * r;
	YSI_g_sAreas[slot][E_AREA_POS][3] = h;
	PA_FastInit(YSI_g_sAreas[slot][E_AREA_PLAYERS]);
	NO_GROUPS()
	{
		PA_Init(YSI_g_sAreas[slot][E_AREA_PLAYERS], true);
	}
	#if YSIM_HAS_MASTER
		YSI_g_sAreas[slot][E_AREA_MASTER] = Master_Caller();
	#endif
	Area_SetAllWorlds(slot, true);
	Area_DetermineZone(x - r, y - r, x + r, y + r, slot, slot);
	return slot;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_AddSphere
Params:
	Float:x - X position of sphere.
	Float:y - Y position of sphere.
	Float:z - Z position of sphere.
	Float:r - Radius of sphere.
Return:
	Area slot or NO_AREA
Notes:
	-
-*----------------------------------------------------------------------------*/

foreign Area_AddSphere(Float:x, Float:y, Float:z, Float:r);
global Area_AddSphere(Float:x, Float:y, Float:z, Float:r)
{
	new
		slot = Area_GetFreeSlot();
	if (slot == NO_AREA) return NO_AREA;
	YSI_g_sAreas[slot][E_AREA_FLAGS] = SINGLE_SLOT_AREA | e_AREA_FLAGS_SPHERE | e_AREA_FLAGS_USED | e_AREA_FLAGS_ACTIVE | e_AREA_FLAGS:(1 << 14);
	YSI_g_sAreas[slot][E_AREA_POS][0] = x;
	YSI_g_sAreas[slot][E_AREA_POS][1] = y;
	YSI_g_sAreas[slot][E_AREA_POS][2] = z;
	YSI_g_sAreas[slot][E_AREA_POS][3] = r * r;
	PA_FastInit(YSI_g_sAreas[slot][E_AREA_PLAYERS]);
	NO_GROUPS()
	{
		PA_Init(YSI_g_sAreas[slot][E_AREA_PLAYERS], true);
	}
	#if YSIM_HAS_MASTER
		YSI_g_sAreas[slot][E_AREA_MASTER] = Master_Caller();
	#endif
	Area_SetAllWorlds(slot, true);
	Area_DetermineZone(x - r, y - r, x + r, y + r, slot, slot);
	return slot;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_AddPoly
Params:
	Float:... - X/Ys of points
Return:
	Area slot or NO_AREA
Notes:
	Creates an irregular shape to detect players in.  This is a 2d area made
	up of a load of XY points.  If an odd number of parameters is passed the
	extra one is assumed to be a ceiling so you can ignore interiors or planes.
	
	Checks that there is enough space to store the data first (as the array
	is split up into 4 float sections for general efficiency) so this check
	uses at least 2 slots (smallest 2d shape is a triangle - 3 points, 6 co-
	ordinates, 2 slots).
	
	The height parameter goes first as it's easiest to check.
	
	This is one of a few functions still written using the master system at a
	low level (the other obvious one is "Class_Add").
-*----------------------------------------------------------------------------*/

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
			setproperty(8, YSIM_CALLER, _@);
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
				
				/*{
					X@(_:@Zk:_YM@CP:%0(%1,,));
					setproperty(8, YSIM_RETURN, n);
				}*/
				
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
	if (Area_GetEmptySlotCount() < ceildiv(count, 4)) return NO_AREA;
	new
		first = Area_GetFreeSlot(),
		done = 4,
		real = first,
		Float:cur,
		Float:minx = FLOAT_INFINITY,
		Float:miny = FLOAT_INFINITY,
		Float:maxx = FLOAT_NEGATIVE_INFINITY,
		Float:maxy = FLOAT_NEGATIVE_INFINITY;
	YSI_g_sAreas[real][E_AREA_FLAGS] = e_AREA_FLAGS_USED | e_AREA_FLAGS_POLY | e_AREA_FLAGS_ACTIVE | (e_AREA_FLAGS:(count << 14) & e_AREA_FLAGS_COUNT);
	PA_FastInit(YSI_g_sAreas[real][E_AREA_PLAYERS]);
	NO_GROUPS()
	{
		PA_Init(YSI_g_sAreas[real][E_AREA_PLAYERS], true);
	}
	#if YSIM_HAS_MASTER
		YSI_g_sAreas[real][E_AREA_MASTER] = Master_Caller();
	#endif
	if (count & 1)
	{
		YSI_g_sAreas[real][E_AREA_POS][0] = points[count - 1];
		minx = maxx = YSI_g_sAreas[real][E_AREA_POS][2] = points[0];
		miny = maxy = YSI_g_sAreas[real][E_AREA_POS][3] = points[1];
		done = 2;
		// If 1 AND 2 are set, make "size" 0 as we've used a full empty slot.
		size = ~count & 2;
		// Strip the odd value, but leave the odd points value.
		count &= ~1;
	}
	else
	{
		minx = maxx = YSI_g_sAreas[real][E_AREA_POS][0] = points[0];
		miny = maxy = YSI_g_sAreas[real][E_AREA_POS][1] = points[1];
		// X point.
		cur = points[2];
		if (cur > maxx) maxx = cur;
		else if (cur < minx) minx = cur;
		YSI_g_sAreas[real][E_AREA_POS][2] = cur;
		// Y point.
		cur = points[3];
		if (cur > maxx) maxx = cur;
		else if (cur < minx) minx = cur;
		YSI_g_sAreas[real][E_AREA_POS][3] = cur;
		size = count & 2;
		count &= ~2;
	}
	while (done < count)
	{
		new
			next = Area_GetFreeSlot();
		YSI_g_sAreas[real][E_AREA_FLAGS] |= e_AREA_FLAGS:next;
		real = next;
		YSI_g_sAreas[real][E_AREA_FLAGS] = e_AREA_FLAGS_USED;
		// X point.
		cur = points[done];
		if (cur > maxx) maxx = cur;
		else if (cur < minx) minx = cur;
		YSI_g_sAreas[real][E_AREA_POS][0] = cur;
		// Y point.
		cur = points[done + 1];
		if (cur > maxx) maxx = cur;
		else if (cur < minx) minx = cur;
		YSI_g_sAreas[real][E_AREA_POS][1] = cur;
		// X point.
		cur = points[done + 2];
		if (cur > maxx) maxx = cur;
		else if (cur < minx) minx = cur;
		YSI_g_sAreas[real][E_AREA_POS][2] = cur;
		// Y point.
		cur = points[done + 3];
		if (cur > maxx) maxx = cur;
		else if (cur < minx) minx = cur;
		YSI_g_sAreas[real][E_AREA_POS][3] = cur;
		#if YSIM_HAS_MASTER
			YSI_g_sAreas[real][E_AREA_MASTER] = Master_Caller();
		#endif
		done += 4;
	}
	if (size)
	{
		// EITHER height XOR odd number of points.  Not both or neither (set above).
		new
			next = Area_GetFreeSlot();
		YSI_g_sAreas[real][E_AREA_FLAGS] |= e_AREA_FLAGS:next;
		real = next;
		YSI_g_sAreas[real][E_AREA_FLAGS] = SINGLE_SLOT_AREA | e_AREA_FLAGS_USED;
		// X point.
		cur = points[done];
		if (cur > maxx) maxx = cur;
		else if (cur < minx) minx = cur;
		YSI_g_sAreas[real][E_AREA_POS][0] = cur;
		// Y point.
		cur = points[done + 1];
		if (cur > maxx) maxx = cur;
		else if (cur < minx) minx = cur;
		YSI_g_sAreas[real][E_AREA_POS][1] = cur;
		#if YSIM_HAS_MASTER
			YSI_g_sAreas[real][E_AREA_MASTER] = Master_Caller();
		#endif
	}
	else
	{
		YSI_g_sAreas[real][E_AREA_FLAGS] |= SINGLE_SLOT_AREA;
	}
	#if YSIM_HAS_MASTER
		setproperty(8, YSIM_RETURN, first);
	#endif
	Area_SetAllWorlds(first, true);
	Area_DetermineZone(minx, miny, maxx, maxy, first, real);
	return first;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_OnPlayerConnect
Params:
	playerid - Player who connected
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

mhook OnPlayerConnect(playerid)
{
	YSI_g_sPlayerArea[playerid] = NO_AREA;
	NO_GROUPS()
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

/*----------------------------------------------------------------------------*-
Function:
	Area_loop
Params:
	playerid - The player to check for.
Return:
	-
Notes:
	Main processing for the system.  Takes one player and checks if they're in
	some sort of range of somewhere.
-*----------------------------------------------------------------------------*/

#if defined AREAS_USE_TIMER
	ptask Area_Loop[200](playerid)
	{
		new
			Float:x,
			Float:y,
			Float:z,
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
	hook OnPlayerUpdate(playerid)
	{
		static
			sZones[9],
			Float:sX,
			Float:sY,
			Float:sZ,
			sCur,
			sW;
		new
			idx;
		// Get all the zones for this player.
		GetPlayerPos(playerid, sX, sY, sZ);
		#if AREA_WORLDS > 0
			sW = GetPlayerVirtualWorld(playerid);
		#endif
		if ((sCur = YSI_g_sPlayerArea[playerid]) != NO_AREA)
		{
			if (Area_CheckArea(playerid, sW, sCur, sX, sY, sZ))
			{
				// Still in the old area, don't check for new ones.
				return 1;
			}
			else
			{
				// No longer in the area they used to be in.
				YSI_g_sPlayerArea[playerid] = NO_AREA;
				Area_DoLeave(playerid, sCur);
			}
		}
		sZones = Area_GetZones(sX, sY);
		for ( ; ; )
		{
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

/*----------------------------------------------------------------------------*-
Function:
	Area_CheckArea
Params:
	playerid - Player being checked for.
	world - VW the player is in.
	area - Area to check against.
	Float:x - X position to check.
	Float:y - Y position to check.
	Float:z - Z position to check.
Return:
	-
Notes:
	Checks if the given position is in the give area.  All parameters are passed
	to avoid calling functions over and over and over again.  If the return is
	not true, "area" is updated to the next one in the chain.
-*----------------------------------------------------------------------------*/

static stock Area_CheckArea(playerid, world, &area, Float:x, Float:y, Float:z)
{
	new
		e_AREA_FLAGS:flags = YSI_g_sAreas[area][E_AREA_FLAGS],
		next,
		ret;
	if ((flags & e_AREA_FLAGS_ACTIVE))
	{
		switch (flags & e_AREA_FLAGS_TYPE)
		{
			case e_AREA_FLAGS_CIRCLE:
			{
				ret = Area_IsInCircle(x, y, z, YSI_g_sAreas[area][E_AREA_POS]);
				next = _:(flags & e_AREA_FLAGS_NEXT);
			}
			case e_AREA_FLAGS_SPHERE:
			{
				ret = IsPlayerInRangeOfPoint(playerid, YSI_g_sAreas[area][E_AREA_POS][3], YSI_g_sAreas[area][E_AREA_POS][0], YSI_g_sAreas[area][E_AREA_POS][1], YSI_g_sAreas[area][E_AREA_POS][2]);
				next = _:(flags & e_AREA_FLAGS_NEXT);
			}
			case e_AREA_FLAGS_POLY:
			{
				ret = Area_IsInPoly(x, y, z, area, _:(flags & e_AREA_FLAGS_COUNT) >> 14, next);
			}
			case e_AREA_FLAGS_CUBE:
			{
				next = _:(flags & e_AREA_FLAGS_NEXT);
				ret = Area_IsInCube(x, y, z, YSI_g_sAreas[area][E_AREA_POS], YSI_g_sAreas[next][E_AREA_POS]);
				next = _:(YSI_g_sAreas[next][E_AREA_FLAGS] & e_AREA_FLAGS_NEXT);
			}
			case e_AREA_FLAGS_BOX:
			{
				ret = Area_IsInBox(x, y, YSI_g_sAreas[area][E_AREA_POS]);
				next = _:(flags & e_AREA_FLAGS_NEXT);
			}
		}
	}
	#if AREA_WORLDS > 0
		if (!Bit_Get(YSI_g_sAreas[area][E_AREA_WORLDS], world))
		{
			area = next;
			return 0;
		}
	#else
		#pragma unused world
	#endif
	if (!ret || !PA_Get(YSI_g_sAreas[area][E_AREA_PLAYERS], playerid))
	{
		area = next;
		return 0;
	}
	return ret;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_IsInCircle
Params:
	Float:x - X position to check.
	Float:y - Y position to check.
	Float:z - Z position to check.
	Float:bounds[] - Data for the area position.
Return:
	-
Notes:
	Checks if a point is in a given circle.
-*----------------------------------------------------------------------------*/

static stock Area_IsInCircle(Float:x, Float:y, Float:z, Float:bounds[])
{
	x -= bounds[0];
	y -= bounds[1];
	return (z < bounds[3] && ((x * x) + (y * y)) < bounds[2]);
}

/*----------------------------------------------------------------------------*-
Function:
	Area_IsInSphere
Params:
	Float:x - X position to check.
	Float:y - Y position to check.
	Float:z - Z position to check.
	Float:bounds[] - Data for the area position.
Return:
	-
Notes:
	Checks if a point is in a given sphere.
-*----------------------------------------------------------------------------*/

static stock Area_IsInSphere(Float:x, Float:y, Float:z, Float:bounds[])
{
	x -= bounds[0];
	y -= bounds[1];
	z -= bounds[2];
	return (((x * x) + (y * y) + (z * z)) < bounds[3]);
}

/*----------------------------------------------------------------------------*-
Function:
	Area_IsInPoly
Params:
	Float:x - X position to check.
	Float:y - Y position to check.
	Float:z - Z position to check.
	pointer - Pointer to the start of the polygon data in the array.
	count - Number of points in the polygon (x/y are counted separate).
	&next - Return for the area after this one.
Return:
	-
Notes:
	Based on IsPlayerInAreaEx by koolk in the useful functions topic.  The
	passed pointer is the pointer to the first set of co-ordinates in a one-
	way not looping linked list of points in the polygod as the data may be
	spread throughout the areas array.  This is as otherwise there may be
	enough free spaces but not in one block.
	
	The code first checks if there is a height component as it's the easiest
	to check thus may save a load of pointless processing.  If this passes it
	then does the main loop.  This loops till there are no points left to do
	(monitored by decreasing count).  When 2 points (four pieces of data) have
	been checked the poiner for the data is moved on to the next group and the
	checking continues.
	
	For simplicity's sake (and thus speed's sake) the lower pointes from the
	last check are saved amd used as the upper points for the next check to
	avoid loads of repeated array accesses and saving the last array position.
-*----------------------------------------------------------------------------*/

static stock Area_IsInPoly(Float:x, Float:y, Float:z, pointer, count, &next)
{
	new
		slot;
	if (isodd(count))
	{
		if (YSI_g_sAreas[pointer][E_AREA_POS][0] < z)
		{
			count = ceildiv(count, 4);
			while (count--)
			{
				pointer = _:(YSI_g_sAreas[pointer][E_AREA_FLAGS] & e_AREA_FLAGS_NEXT);
			}
			next = pointer;
			return 0;
		}
		slot = 2;
		count--;
	}
	new
		lines,
		Float:fx = YSI_g_sAreas[pointer][E_AREA_POS][slot++],
		Float:fy = YSI_g_sAreas[pointer][E_AREA_POS][slot++],
		Float:minx = fx,
		Float:miny = fy,
		Float:maxx,
		Float:maxy;
	while (count)
	{
		if (slot == 4)
		{
			pointer = _:(YSI_g_sAreas[pointer][E_AREA_FLAGS] & e_AREA_FLAGS_NEXT);
			slot = 0;
		}
		if (count == 2)
		{
			maxx = fx;
			maxy = fy;
		}
		else
		{
			maxx = YSI_g_sAreas[pointer][E_AREA_POS][slot++];
			maxy = YSI_g_sAreas[pointer][E_AREA_POS][slot++];
		}
		if (((y >= miny && y <= maxy) || (y >= maxy && y <= miny)) && (minx + ((y - miny) * (maxx - minx) / (maxy - miny))) < x) lines++;
		count -= 2;
		minx = maxx;
		miny = maxy;
	}
	next = _:(YSI_g_sAreas[pointer][E_AREA_FLAGS] & e_AREA_FLAGS_NEXT);
	return isodd(lines);
}

/*----------------------------------------------------------------------------*-
Function:
	Area_IsInCube
Params:
	Float:x - X position to check.
	Float:y - Y position to check.
	Float:z - Z position to check.
	Float:lower[] - The lower corner of the cube.
	Float:upper[] - The upper corner of the cube.
Return:
	-
Notes:
	Checks if a point is in a given cube.  This is another multi slot shape
	but is much simpler than the poly as it's always 2 slots so we can easilly
	get the data in one lump.
-*----------------------------------------------------------------------------*/

static stock Area_IsInCube(Float:x, Float:y, Float:z, Float:lower[], Float:upper[])
{
	return (x > lower[0] && x < upper[0] && y > lower[1] && y < upper[1] && z > lower[2] && z < upper[2]);
}

/*----------------------------------------------------------------------------*-
Function:
	Area_IsInBox
Params:
	Float:x - X position to check.
	Float:y - Y position to check.
	Float:bounds[] - Data for the area position.
Return:
	-
Notes:
	Checks if a point is in a given box.  There is no height check with this
	one as any one area slot has 4 points which for this are upper and lower
	x and y, adding a height check would make it require 2 slots and basically
	make it a cube check.
-*----------------------------------------------------------------------------*/

static stock Area_IsInBox(Float:x, Float:y, Float:bounds[])
{
	return (x > bounds[0] && x < bounds[2] && y > bounds[1] && y < bounds[3]);
}

/*----------------------------------------------------------------------------*-
Function:
	Area_GetPlayerArea
Params:
	playerid - Player to get area of.
Return:
	The area a player is in or -1.
Notes:
	-
-*----------------------------------------------------------------------------*/

foreign Area_GetPlayerArea(playerid);

global Area_GetPlayerArea(playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		return YSI_g_sPlayerArea[playerid];
	}
	return NO_AREA;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_SetPlayer
Params:
	area - Area to set for.
	playerid - Player to set for.
	set - Wether or not the player can use the area.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

foreign Area_SetPlayer(area, playerid, bool:set);

global Area_SetPlayer(area, playerid, bool:set)
{
	if (Area_IsActive(area))
	{
		PA_Set(YSI_g_sAreas[area][E_AREA_PLAYERS], playerid, set);
		return 1;
	}
	return 0;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_GetPlayer
Params:
	area - Area to set for.
	playerid - Player to set for.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

foreign bool:Area_GetPlayer(area, playerid);

global bool:Area_GetPlayer(area, playerid)
{
	if (Area_IsActive(area))
	{
		return PA_Get(YSI_g_sAreas[area][E_AREA_PLAYERS], playerid);
	}
	return false;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_SetWorld
Params:
	area - Area to set for.
	world - World to set for.
	set - Wether or not the area is active in this world.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

foreign Area_SetWorld(area, world, bool:set);

global Area_SetWorld(area, world, bool:set)
{
	#if AREA_WORLDS > 0
		if (Area_IsActive(area))
		{
			Bit_Set(YSI_g_sAreas[area][E_AREA_WORLDS], world, set);
			return 1;
		}
	#else
		#pragma unused area, world, set
	#endif
	return 0;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_GetWorld
Params:
	area - Area to set for.
	world - World to set for.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

foreign bool:Area_GetWorld(area, world);

global bool:Area_GetWorld(area, world)
{
	if (Area_IsActive(area))
	{
		return Bit_Get(YSI_g_sAreas[area][E_AREA_WORLDS], world);
	}
	return false;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_SetAllPlayers
Params:
	area - Area to set for.
	set - Wether or not all players can use this area.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

foreign Area_SetAllPlayers(area, bool:set);

global Area_SetAllPlayers(area, bool:set)
{
	if (Area_IsActive(area))
	{
		PA_Init(YSI_g_sAreas[area][E_AREA_PLAYERS], set);
		return 1;
	}
	return 0;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_IsValid
Params:
	area - Area to check.
Return:
	Is the passed area valid and active.
Notes:
	-
-*----------------------------------------------------------------------------*/

foreign bool:Area_IsValid(area);

global bool:Area_IsValid(area)
{
	return bool:Area_IsActive(area);
}

/*----------------------------------------------------------------------------*-
Function:
	Area_IsEmpty
Params:
	area - Area to check.
Return:
	Is the passed area valid and empty.
Notes:
	-
-*----------------------------------------------------------------------------*/

foreign bool:Area_IsEmpty(area);

global bool:Area_IsEmpty(area)
{
	if (Area_IsActive(area))
	{
		foreach (new playerid : Player)
		{
			if (YSI_g_sPlayerArea[playerid] == area) return false;
		}
	}
	return true;
}

/*----------------------------------------------------------------------------*-
Function:
	Area_SetCallback
Params:
	area - Area to set for.
	callback:callback - Callback to use.
Return:
	-
Notes:
	Adds a y_inline style callback (publics included) to an area to be called
	when a player enters it.  This is NOT a remote function and instead records
	the data locally to call functions in the correct script (or they'll just
	end up crashing as you will be jumping to an arbitrary address in a script
	that doesn't have sensible code at that address.
-*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*-
Function:
	Area_DoEnter
Params:
	playerid - The player that just entered the area.
	areaid - The area they entered.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

remotefunc Area_DoEnter(playerid, areaid)
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
}

forward OnPlayerEnterArea(playerid, areaid);

/*----------------------------------------------------------------------------*-
Function:
	Area_DoLeave
Params:
	playerid - The player that just left the area.
	areaid - The area they left.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

remotefunc Area_DoLeave(playerid, areaid)
{
	if (YSI_g_sHasCallbacks & 2)
	{
		CallLocalFunction("OnPlayerLeaveArea", "ii", playerid, areaid);
	}
	if (YSI_g_sHasCallbacks & 8)
	{
		//Hook_OnPlayerLeaveArea(playerid, areaid);
	}
	return 1;
}

forward OnPlayerLeaveArea(playerid, areaid);

//#define YSI_SET_LAST_GROUP 19
#include "internal\y_grouprevert"
