/*----------------------------------------------------------------------------*-
					===============================
					Y Sever Includes - Objects Core
					===============================
Description:
	Handles object streaming for >150 objects per player.  Also provides VW
	support and improved object attachment (i.e. it works).  New versions
	combines mine and Peter's streaming systems to narrow down objects by
	approximation by a grid system then check all objects visible in near
	by sections.
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
	0.2.7
Changelog:
	27/12/07:
		Fixed a bug in the moved object list system.
	26/11/07:
		Finished up master system.
		Fixed DestroyDynamicObject not removing client objects.
	16/11/07:
		Removed global flag as it wasn't doing anything.
	27/10/07:
		Fixed moving objects so they actually move
	26/10/07:
		Added object children to attach objects to each other.
	09/10/07:
		FINALLY found compile hang bug.
		Repaired removed code.
		Put object co-ordinate code in Object_ParseSet
	23/09/07:
		Updated FindSector, AddToSector and RemoveFromSector to use new system.
	22/09/07:
		Started work on new sector system, minor macro changes, lots of maths.
		Wrote squareroot macro.
		Updated constructor.
	21/09/07:
		Overhauled sector code, skips columns and interiors plus more efficient.
	20/09/07:
		Made some core functions static so they don't get called by accident.
		Changed auto-adjust code so it rounds to nearest whole log number.
		Moved zone-find code around to skip whole columns at once.
		Added zone sorting so they're done in order of distance.
		Added breakout code so once all objects are found processing is exited.
	19/09/07:
		Added auto-adjusting zone sizes based on object limits.
		Altered zone find code to return only possible visible zones.
		Fixed rare hanging bug in close list code.
	18/09/07:
		My birthday - yes I'm that sad to code on it and put it in a changelog.
		Rewrote sectors code to use known sectors instead of position.
	17/09/07:
		Rewrote find code to find closest objects instead of random close ones.
	03/08/07:
		Updated timer system.
	07/05/07:
		Added groups support via default settings.
		Corrected (unused) flag - bit pointless but meh.
	02/05/07:
		Added YSI_ prefix to all globals.
		Added dynamic object API calls.
	30/04/07:
		Fixed bug in DestroyDynamicObject with OOB objects not 1st in list.
		Exported sector removal code to Object_RemoveFromSector.
		Added SECTOR parameter to E_OBJECT for ease of modification.
	25/04/07:
		Added 3d checking.
		Added DestroyDynamicObject API function.
		Fixed location checking on attached objects.
		Fixed loop itteration for cyclic list structure.
	24/04/07:
		Fixed range leave checking.
		Added moving objects list.
	18/04/07:
		Second version - completely rewritten after a chat with Peter.
	16/04/07:
		First version - adapted from my earlier e_objects.inc include.
Functions:
	Public:
		Object_Loop - Main loop for checking.
		Object_CoOrdRemote - Does object location manipulation remotely.
		Object_Remote - Does normal functions remotely.
		Object_UpdateUnused - Adds an object to the remote unused list.
		Object_Broadcast - Saves an object remotely.
		Object_GetLimit - Gets the number of objects the remove master can hold.
		YSIM_Objects - Processes master system instructions.
		Object_AddRem - Remote wrapper for Object_Add.
	Core:
		Object_Object - Constructor.
		Object_OnPlayerDisconnect - Disconnects objects.
	Stock:
		Object_AddToWorld - Make visible in world.
		Object_RemoveFromWorld - Make invisible in world.
		Object_AddToPlayer - Make visible to player.
		Object_RemoveFromPlayer - Make invisible to player.
		Object_AddToAllWorlds - Make visible in all worlds.
		Object_RemoveFromAllWorlds - Make invisible in all worlds.
		Object_AddToAllPlayers - Make visible to all players.
		Object_RemoveFromAllPlayers - Make invisible to all players.
		Object_IsValidModel - Checks if an object is good to be displayed.
		Object_IsGlobal - Checks if an object is visible by default.
		Object_SetViewDistance - Sets an object's view distance.
		Object_IsDescendant - Checks if an object is related to another object.
	Static:
		Object_Add - Internal add function.
		Object_FindSector - Find a location's sector.
		Object_AddToOOB - Add an object to the OOB list.
		Object_AddToSector - Add an object to the specified list.
		Object_RemoveFromSector - Remove an object from the given sector.
		Object_FindSectors - Get near sectors.
		Object_ParseSet - Check objects in list.
		Object_Update - Updates the position of a moving object.
		Object_UpdateChildSectors - Updates the sectors of moved object children.
		Object_SetPos - Moves an object to the given position.
		Object_UpdateAttach - Updates children after dynamic stop.
		Object_Move - Reursive MoveDynamicObject for children.
		Object_RemoveFromParent - Removes an object from it's parent.
		Object_AddToParent - Adds an object to another object.
		Object_AttachToPlayer - Attaches objects to a player recursively.
		Object_CheckDescendant - Recursive call for Object_IsDescendant.
		Object_Destroy - Delete an object with no checks.
		Object_AddToUpdate - Safely adds an object to the moved update list.
	Inline:
		Object_IsValid - Internal validity check.
		Object_GetAttach - Get player an object's attached to.
		Object_SetAttach - objSet player an object's attached to.
		Object_HasPlayer - Checks if a player can see an object.
	API:
		MoveDynamicObject - Wrapper for MoveObject.
		StopDynamicObject - Wrapper for StopObject.
		IsValidDynamicObject - Wrapper for IsValidObject.
		CreateDynamicObject - Wrapper for CreateObject.
		CreatePlayerDynamicObject - Wrapper for CreatePlayerObject.
		CreateVWDynamicObject - Creates an object in only one world.
		CreatePlayerVWDynamicObject - Creates an object for one player in one world.
		DestroyDynamicObject - Wrapper for DestroyObject.
		GetDynamicObjectPos - Wrapper for GetObjectPos.
		GetDynamicObjectRot - Wrapper for GetObjectRot.
		SetDynamicObjectPos = Wrapper for SetObjectPos.
		SetDynamicObjectRot - Wrapper for SetObjectRot.
		AttachDynamicObjectToPlayer - Wrapper for AttachObjectToPlayer.
		DetachDynamicObjectFromPlayer - Removes an object from a player.
		AttachObjectToObject - Attaches an object to another object.
		RemoveObjectFromParent - Removes an object from another object.
Callbacks:
	OnDynamicObjectMoved
Definitions:
	OBJECT_SECTOR_SIZE - Size of edge of a grid square for approximations.
	MAX_DYN_OBJECTS - Maximum number of objects.
	OBJECT_VIEW_DISTANCE - Range to stream objects for.
	NO_OBJECT - No object pointer.
	NO_SECTOR - No sector pointer.
	OBJECT_NO_SECTOR - OOB object marker.
	OBJECT_LOOP_GRANULARITY - Number of itterations per second for the loop.
	NO_ATTACH_PLAYER - Marker for object not attached to anyone.
	OBJECT_WORLDS - Maximum number of worlds objects show up in.
	OBJECT_WORLD_COUNT - Size of bit array of worlds.
	OBJECT_PLAYER_COUNT - Size of bit array of players.
Enums:
	E_OBJECT - Structure of the dynamic object data.
	e_OBJ_FLAG - Flags for the object.
Macros:
	OBJECT_SECTOR_EDGE - Number of sectors on one edge of the world.
	OBJECT_SECTOR_ARRAY - Number of grid squares.
	OBJECT_SIGHT - OBJECT_VIEW_DISTANCE squared for speed.
	OBJECT_VIEW_RATIO - Number of sectors per view radius.
	OBJECT_VIEW_EDGES - Max width of view range in sectors.
	OBJECT_VIEW_SECTORS - Max sectors visible at once.
	NO_OBJECT_CHECK - Invalid model.
	OBJECT_BITS - Number of bits to hold all dynamic objects.
	e_OBJ_FLAG_MOVED - Extension of e_OBJ_FLAG, both move flags together.
	NEW_SECTOR - Sector based on origin sector and current offset.
Tags:
	e_OBJ_FLAG - Flags for objects.
Variables:
	Global:
		-
	Static:
		YSI_g_sObjectSectors - Array of pointers to sector object lists.
		YSI_g_sObjects - Array of objects.
		YSI_g_sOtherSector - Pointer to OOB object list.
		YSI_g_sMovingObjects - Pointer to moving object list.
		YSI_g_sNoObjects - Pointer to unused object list.
Commands:
	-
Compile options:
	NO_PERSONAL_OBJECTS - All players see all objects.
	NO_OBJECT_ATTACH - Objects can't be attached to each other.
	NO_OBJECTS_MOVE - No processing is done for moving objects.
	OBJECT_WORLDS 0 - All objects are visible in all worlds.
Operators:
	-
-*----------------------------------------------------------------------------*/

#if !defined OBJECT_BOUNDS_MINX
	#if defined OBJECT_BOUNDS
		#define OBJECT_BOUNDS_MINX (-OBJECT_BOUNDS)
	#else
		#define OBJECT_BOUNDS_MINX (-5000)
	#endif
#endif

#if !defined OBJECT_BOUNDS_MINY
	#if defined OBJECT_BOUNDS
		#define OBJECT_BOUNDS_MINY (-OBJECT_BOUNDS)
	#else
		#define OBJECT_BOUNDS_MINY (-5000)
	#endif
#endif

#if !defined OBJECT_BOUNDS_MAXX
	#if defined OBJECT_BOUNDS
		#define OBJECT_BOUNDS_MAXX (OBJECT_BOUNDS)
	#else
		#define OBJECT_BOUNDS_MAXX (5000)
	#endif
#endif

#if !defined OBJECT_BOUNDS_MAXY
	#if defined OBJECT_BOUNDS
		#define OBJECT_BOUNDS_MAXY (OBJECT_BOUNDS)
	#else
		#define OBJECT_BOUNDS_MAXY (5000)
	#endif
#endif

#define OBJECT_BOUNDS_X_SIZE (OBJECT_BOUNDS_MAXX - OBJECT_BOUNDS_MINX)
#define OBJECT_BOUNDS_Y_SIZE (OBJECT_BOUNDS_MAXY - OBJECT_BOUNDS_MINY)

#if !defined MAX_DYN_OBJECTS
	#define MAX_DYN_OBJECTS (10000)
#endif

#define AVERAGE_OBJECTS_PER_SECTOR (500)

#define OBJECT_DISTRIBUTION (((OBJECT_BOUNDS_X_SIZE * OBJECT_BOUNDS_Y_SIZE) / MAX_DYN_OBJECTS) * AVERAGE_OBJECTS_PER_SECTOR)

#if !defined OBJECT_SECTOR_SIZE
	#if OBJECT_DISTRIBUTION <= 10
		#define OBJECT_SECTOR_SIZE (1)
	#endif
#endif

#if !defined OBJECT_SECTOR_SIZE
	#if OBJECT_DISTRIBUTION <= 100
		#define OBJECT_SECTOR_SIZE (5)
	#endif
#endif

#if !defined OBJECT_SECTOR_SIZE
	#if OBJECT_DISTRIBUTION <= 1000
		#define OBJECT_SECTOR_SIZE (10)
	#endif
#endif

#if !defined OBJECT_SECTOR_SIZE
	#if OBJECT_DISTRIBUTION <= 10000
		#define OBJECT_SECTOR_SIZE (50)
	#endif
#endif

#if !defined OBJECT_SECTOR_SIZE
	#if OBJECT_DISTRIBUTION <= 100000
		#define OBJECT_SECTOR_SIZE (100)
	#endif
#endif

#if !defined OBJECT_SECTOR_SIZE
	#if OBJECT_DISTRIBUTION <= 1000000
		#define OBJECT_SECTOR_SIZE (500)
	#endif
#endif

#if !defined OBJECT_SECTOR_SIZE
	#if OBJECT_DISTRIBUTION <= 10000000
		#define OBJECT_SECTOR_SIZE (1000)
	#endif
#endif

#if !defined OBJECT_SECTOR_SIZE
	#if OBJECT_DISTRIBUTION <= 100000000
		#define OBJECT_SECTOR_SIZE (5000)
	#endif
#endif

#if !defined OBJECT_SECTOR_SIZE
	#if OBJECT_DISTRIBUTION <= 1000000000
		#define OBJECT_SECTOR_SIZE (10000)
	#endif
#endif

#define OBJECT_SECTOR_X_EDGE (ceildiv(OBJECT_BOUNDS_X_SIZE, OBJECT_SECTOR_SIZE))
#define OBJECT_SECTOR_Y_EDGE (ceildiv(OBJECT_BOUNDS_Y_SIZE, OBJECT_SECTOR_SIZE))

#define OBJECT_SECTOR_ARRAY (OBJECT_SECTOR_X_EDGE * OBJECT_SECTOR_Y_EDGE)

#define OBJECT_REAL_X_SECTOR_SIZE (float(OBJECT_BOUNDS_X_SIZE) / float(OBJECT_SECTOR_X_EDGE))
#define OBJECT_REAL_Y_SECTOR_SIZE (float(OBJECT_BOUNDS_Y_SIZE) / float(OBJECT_SECTOR_Y_EDGE))

#if !defined OBJECT_MAX_VIEW_DISTANCE
	#define OBJECT_MAX_VIEW_DISTANCE 500
#endif

#if !defined DEFAULT_OBJECT_VIEW
	#if defined OBJECT_VIEW_DISTANCE
		#define DEFAULT_OBJECT_VIEW (OBJECT_VIEW_DISTANCE)
	#else
		#define DEFAULT_OBJECT_VIEW (200)
	#endif
#endif

#define OBJECT_SIGHT (DEFAULT_OBJECT_VIEW * DEFAULT_OBJECT_VIEW)
#define OBJECT_VIEW_RATIO (ceildiv(OBJECT_MAX_VIEW_DISTANCE, OBJECT_SECTOR_SIZE))
#define OBJECT_VIEW_EDGES ((OBJECT_VIEW_RATIO * 2) + 1)
#define OBJECT_VIEW_SECTORS (OBJECT_VIEW_EDGES * OBJECT_VIEW_EDGES)
#define NO_OBJECT -1
#define NO_OBJECT_CHECK (NO_OBJECT & _:e_OBJ_FLAG_MODEL)
#define NO_SECTOR -1
#define OBJECT_NO_SECTOR 0x7FFFFFFF
#define OBJECT_LOD_SECTOR 0x6FFFFFFF
#define OBJECT_INT_SECTOR 0x5FFFFFFF
#define OBJECT_BITS Bit_Bits(MAX_DYN_OBJECTS)
#if !defined OBJECT_LOOP_GRANULARITY
	#define OBJECT_LOOP_GRANULARITY 2
#endif
#define NO_ATTACH_PLAYER 0xFF

#define NO_GATE (-1)

#define SECTOR_CHECK_TIME (1000)
#define SECTOR_CHECK_FREQUENCY ceildiv(SECTOR_CHECK_TIME, (1000 / OBJECT_LOOP_GRANULARITY))

#define MAY_OBJECTS (150)

#if !defined OBJECT_WORLDS
	#define OBJECT_WORLDS MAX_WORLDS
#endif

#if OBJECT_WORLDS > 32
	#define OBJECT_WORLD_COUNT Bit_Bits(OBJECT_WORLDS)
#else
	#define OBJECT_WORLD_COUNT 2
#endif

#define GATE_AREA_TRIGGER (0x80000000)
#define GATE_OPENING (0x40000000)

#define ONE_OVER_ROOT_TWO (0.70710678118654752440084436210485)

enum e_OBJ_FLAG (<<= 1)
{
	e_OBJ_FLAG_MODEL = 0x00007FFF,
	e_OBJ_FLAG_ATTACH = 0x007F8000,
	e_OBJ_FLAG_ATTACHED = 0x00800000,
	e_OBJ_FLAG_JUMPED,
	e_OBJ_FLAG_MOVED1,
	e_OBJ_FLAG_MOVED2,
	e_OBJ_FLAG_ROTATED,
	e_OBJ_FLAG_ACTIVE,
	e_OBJ_FLAG_RECREATED,
	e_OBJ_FLAG_GATE
}

#define e_OBJ_FLAG_MOVED (e_OBJ_FLAG_MOVED1 | e_OBJ_FLAG_MOVED2)

enum E_OBJECT
{
	e_OBJ_FLAG:E_OBJECT_MODEL,
	#if defined _YSI_SETUP_MASTER
		E_OBJECT_SCRIPT,
	#endif
	Float:E_OBJECT_X,
	Float:E_OBJECT_Y,
	Float:E_OBJECT_Z,
	Float:E_OBJECT_RX,
	Float:E_OBJECT_RY,
	Float:E_OBJECT_RZ,
	Float:E_OBJECT_VIEW,
	#if OBJECT_WORLDS > 0
		Bit:E_OBJECT_WORLDS[OBJECT_WORLD_COUNT],
	#endif
	#if !defined NO_PERSONAL_OBJECTS
		Bit:E_OBJECT_PLAYERS[PLAYER_BIT_ARRAY],
	#endif
	#if !defined NO_OBJECTS_MOVE
		Float:E_OBJECT_MX,
		Float:E_OBJECT_MY,
		Float:E_OBJECT_MZ,
		Float:E_OBJECT_MS,
	#endif
	E_OBJECT_UPDATES,
	#if !defined NO_OBJECT_ATTACH
		E_OBJECT_PARENT,
		E_OBJECT_SIBLINGS,
		E_OBJECT_CHILDREN,
	#endif
	E_OBJECT_NEXT,
	E_OBJECT_SECTOR
}

enum E_OBJECT_ITTER
{
	Float:E_OBJECT_ITTER_DISTANCE,
	E_OBJECT_ITTER_NEXT,
	E_OBJECT_ITTER_LAST,
	E_OBJECT_ITTER_OBJ,
	Float:E_OBJECT_ITTER_X,
	Float:E_OBJECT_ITTER_Y,
	Float:E_OBJECT_ITTER_Z
}

enum E_OBJ_SECTOR
{
	E_OBJ_SECTOR_POINTER,
	Float:E_OBJ_SECTOR_MAX_VIEW
}

enum E_OSEC_ITTER
{
	E_OSEC_ITTER_SECTOR,
	E_OSEC_ITTER_NEXT,
	Float:E_OSEC_ITTER_DIFF
}

enum
{
	E_OBJECT_REMOTE_ISG,
	E_OBJECT_REMOTE_VIEW,
	E_OBJECT_REMOTE_DESTROY,
	E_OBJECT_REMOTE_SETPOS,
	E_OBJECT_REMOTE_SETROT,
	E_OBJECT_REMOTE_ADDW,
	E_OBJECT_REMOTE_REMW,
	E_OBJECT_REMOTE_ADDP,
	E_OBJECT_REMOTE_REMP,
	E_OBJECT_REMOTE_ALLWA,
	E_OBJECT_REMOTE_ALLWR,
	E_OBJECT_REMOTE_ALLPA,
	E_OBJECT_REMOTE_ALLPR,
	E_OBJECT_REMOTE_ISVALID,
	E_OBJECT_REMOTE_DETATCH,
	E_OBJECT_REMOTE_ATTACHOO,
	E_OBJECT_REMOTE_REMOO,
	E_OBJECT_REMOTE_STOP,
	E_OBJECT_REMOTE_GETROT,
	E_OBJECT_REMOTE_GETPOS,
	E_OBJECT_REMOTE_MOVETO,
	E_OBJECT_REMOTE_CHECKDESC,
	E_OBJECT_REMOTE_GET_AREA,
	E_OBJECT_REMOTE_GATE_POS,
	E_OBJECT_REMOTE_GATE
}

enum E_GATE_INFO
{
	E_GATE_INFO_OBJECT,
	E_GATE_INFO_TIME,
	E_GATE_INFO_TRIGGER,
	E_GATE_INFO_XY,
	E_GATE_INFO_ZA
}

#if !defined MAX_GATE_OBJECTS
	#define MAX_GATE_OBJECTS 32
#endif

#if MAX_GATE_OBJECTS > 256
	#if !defined EXTENDED_GATE_CODE
		#define EXTENDED_GATE_CODE
	#endif
#endif

#if MAX_GATE_OBJECTS > 65536
	#if !defined NO_GATE_AREA_LOOKUP
		#error Only 65536 gates supported in lookup mode
	#endif
#endif

forward Object_Loop();
#if defined _YSI_SETUP_MASTER
	forward Object_GetLimit();
	forward Object_AddRem(master, model, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);
	forward Object_Remote(ident, info, instruction);
	forward Object_CoOrdRemote(ident, instruction, Float:f1, Float:f2, Float:f3, Float:f4);
	forward Object_OnPlayerEnterArea(playerid, areaid);
	forward Object_Broadcast(id, e_OBJ_FLAG:model, master, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:view,
				Float:mx, Float:my, Float:mz, Float:ms, parent, siblings, children, Bit:worlds[], wCount, Bit:players[], pCount);
	forward YSIM_Objects(command);
	forward Object_UpdateUnused(obj);
	#if !defined NO_OBJECTS_MOVE
		forward Object_AttachRemote(objectid, playerid, Float:X, Float:Y, Float:Z, Float:RX, Float:RY, Float:RZ);
	#endif
#endif
#if defined _YSI_VISUAL_AREAS
	forward Object_GateClose(gate);
#endif

static
	Float:YSI_g_sXSectorLocations[OBJECT_SECTOR_X_EDGE + 1],
	Float:YSI_g_sYSectorLocations[OBJECT_SECTOR_Y_EDGE + 1],
	Float:YSI_g_sXSectorSize,
	Float:YSI_g_sYSectorSize,
	YSI_g_sObjectSectors[OBJECT_SECTOR_ARRAY][E_OBJ_SECTOR],
	YSI_g_sObjects[MAX_DYN_OBJECTS][E_OBJECT],
	YSI_g_sOtherSector = NO_OBJECT,
	YSI_g_sMovingObjects = NO_OBJECT,
	YSI_g_sLODObjects = NO_OBJECT,
	YSI_g_sInteriorObjects = NO_OBJECT,
	YSI_g_sPlayerObjects[MAX_PLAYERS][MAY_OBJECTS],
	YSI_g_sSomethingMoved = NO_OBJECT,
	#if defined _YSI_SETUP_MASTER
		YSI_g_sIsMaster,
	#endif
	#if defined _YSI_VISUAL_AREAS
		YSI_g_sGateInfo[MAX_GATE_OBJECTS][E_GATE_INFO],
		#if !defined NO_GATE_AREA_LOOKUP
			YSI_g_sGateAreas[ceildiv(MAX_AREAS, 2)],
		#endif
	#endif
	YSI_g_sNoObjects;

/*----------------------------------------------------------------------------*-
Function:
	Object_IsValid
Params:
	objectid - Object to check
Return:
	-
Notes:
	Checks if a passed id is a valid object.
-*----------------------------------------------------------------------------*/

#define Object_IsValid(%1) \
	((%1) >= 0 && (%1) < MAX_DYN_OBJECTS && YSI_g_sObjects[(%1)][E_OBJECT_MODEL] & e_OBJ_FLAG_ACTIVE)

/*----------------------------------------------------------------------------*-
Function:
	Object_GetAttach
Params:
	flags - Flags to check.
Return:
	Player the object is attached to.
Notes:
	Actually checks a objSet of passed flags, not a passed object.
-*----------------------------------------------------------------------------*/

#define Object_GetAttach(%1) \
	((_:(%1) >> 15) & NO_ATTACH_PLAYER)

/*----------------------------------------------------------------------------*-
Function:
	Object_IsAttached
Params:
	flags - Flags to check.
Return:
	If the object is attached to a player.
Notes:
	Actually checks a objSet of passed flags, not a passed object.
-*----------------------------------------------------------------------------*/

#define Object_IsAttached(%1) \
	(Object_GetAttach(%1) != NO_ATTACH_PLAYER)

/*----------------------------------------------------------------------------*-
Function:
	Object_SetGateTarget
Params:
	gate - Gate to objSet target for.
	Float:tx - X point to open to.
	Float:ty - Y point to open to.
	Float:tz - Z point to open to.
	Float:ts - Speed to open at.
Return:
	-
Notes:
	Stores a location into the two variables provided for targets.  Uses
	complex bit shifting to fit the floats nicely into 2 cells.  Assumes a max
	of +/-13107.2 for x, y and z and a max of 102.4 for the speed to compress.
-*----------------------------------------------------------------------------*/

#define Object_SetGateTarget(%1,%2,%3,%4,%5) \
	new \
		_o_sgt_y = floatround((%3) * 10); \
	YSI_g_sGateInfo[(%1)][E_GATE_INFO_XY] = ((floatround((%2) * 10) & 0x3FFFF) << 14) | (_o_sgt_y & 0x3FFF); \
	YSI_g_sGateInfo[(%1)][E_GATE_INFO_ZA] = ((_o_sgt_y & 0x3C000) << 14) | ((floatround((%4) * 10) & 0x3FFFF) << 10) | (floatround((%5) * 10) & 0x3FF)

/*----------------------------------------------------------------------------*-
Function:
	Object_SetAttach
Params:
	flags - Flags to check.
Return:
	-
Notes:
	Actually checks a objSet of passed flags, not a passed object.
-*----------------------------------------------------------------------------*/

#define Object_SetAttach(%1) \
	e_OBJ_FLAG:(((%1) & NO_ATTACH_PLAYER) << 15)

#if defined _YSI_SETUP_MASTER

	/*----------------------------------------------------------------------------*-
	Function:
		Object_Remote
	Params:
		ident - Object to do code on.
		info - Extra data for function.
		instruction - Function to perform.
	Return:
		-
	Notes:
		Performs operations on objects remotely.
	-*----------------------------------------------------------------------------*/

	public Object_Remote(ident, info, instruction)
	{
		setproperty(0, "YSIReq", 0);
		if (!YSI_g_sIsMaster) return 0;
		switch (instruction & 0x0FFF)
		{
			case E_OBJECT_REMOTE_VIEW:
			{
				Object_SetViewDistance(ident, Float:info);
			}
			case E_OBJECT_REMOTE_DESTROY:
			{
				if (Object_IsValid(ident)) Object_Destroy(ident);
			}
			case E_OBJECT_REMOTE_ADDW:
			{
				if (Object_IsValid(ident)) Bit_Set(YSI_g_sObjects[ident][E_OBJECT_WORLDS], info, 1, OBJECT_WORLD_COUNT);
			}
			case E_OBJECT_REMOTE_REMW:
			{
				if (Object_IsValid(ident)) Bit_Set(YSI_g_sObjects[ident][E_OBJECT_WORLDS], info, 0, OBJECT_WORLD_COUNT);
			}
			case E_OBJECT_REMOTE_ADDP:
			{
				if (Object_IsValid(ident)) Bit_Set(YSI_g_sObjects[ident][E_OBJECT_PLAYERS], info, 1, PLAYER_BIT_ARRAY);
			}
			case E_OBJECT_REMOTE_REMP:
			{
				if (Object_IsValid(ident)) Bit_Set(YSI_g_sObjects[ident][E_OBJECT_PLAYERS], info, 0, PLAYER_BIT_ARRAY);
			}
			case E_OBJECT_REMOTE_ALLWA:
			{
				if (Object_IsValid(ident)) Bit_SetAll(YSI_g_sObjects[ident][E_OBJECT_WORLDS], 1, OBJECT_WORLD_COUNT);
			}
			case E_OBJECT_REMOTE_ALLWR:
			{
				if (Object_IsValid(ident)) Bit_SetAll(YSI_g_sObjects[ident][E_OBJECT_WORLDS], 0, OBJECT_WORLD_COUNT);
			}
			case E_OBJECT_REMOTE_ALLPA:
			{
				if (Object_IsValid(ident))
				{
					Bit_SetAll(YSI_g_sObjects[ident][E_OBJECT_PLAYERS], 1, PLAYER_BIT_ARRAY);
				}
			}
			case E_OBJECT_REMOTE_ALLPR:
			{
				if (Object_IsValid(ident))
				{
					Bit_SetAll(YSI_g_sObjects[ident][E_OBJECT_PLAYERS], 0, PLAYER_BIT_ARRAY);
				}
			}
			case E_OBJECT_REMOTE_ISVALID:
			{
				if (Object_IsValid(ident)) setproperty(0, "YSIReq", 1);
			}
			case E_OBJECT_REMOTE_DETATCH:
			{
				DetachDynamicObjectFromPlayer(ident);
			}
			case E_OBJECT_REMOTE_ATTACHOO:
			{
				AttachObjectToObject(ident, info);
			}
			case E_OBJECT_REMOTE_REMOO:
			{
				RemoveObjectFromParent(ident);
			}
			case E_OBJECT_REMOTE_STOP:
			{
				StopDynamicObject(ident);
			}
			case E_OBJECT_REMOTE_GETROT:
			{
				if (!Object_IsValid(ident) || Object_IsAttached(YSI_g_sObjects[ident][E_OBJECT_MODEL]))
				{
					setproperty(0, "YSIReq", 0);
					setproperty(0, "YSIReq2", 0);
					setproperty(0, "YSIReq3", 0);
				}
				else
				{
					setproperty(0, "YSIReq", _:YSI_g_sObjects[ident][E_OBJECT_RX]);
					setproperty(0, "YSIReq2", _:YSI_g_sObjects[ident][E_OBJECT_RY]);
					setproperty(0, "YSIReq3", _:YSI_g_sObjects[ident][E_OBJECT_RZ]);
				}
			}
			case E_OBJECT_REMOTE_GETPOS:
			{
				if (!Object_IsValid(ident))
				{
					setproperty(0, "YSIReq", 0);
					setproperty(0, "YSIReq2", 0);
					setproperty(0, "YSIReq3", 0);
				}
				else
				{
					new
						Float:x,
						Float:y,
						Float:z;
					Object_GetPos(ident, x, y, z);
					setproperty(0, "YSIReq", _:x);
					setproperty(0, "YSIReq2", _:y);
					setproperty(0, "YSIReq3", _:z);
				}
			}
			case E_OBJECT_REMOTE_CHECKDESC:
			{
				if (Object_CheckDescendant(ident, info)) setproperty(0, "YSIReq", 1);
			}
			case E_OBJECT_REMOTE_GET_AREA:
			{
				if (ident >= 0 && ident < MAX_GATE_OBJECTS)
				{
					setproperty(0, "YSIReq", YSI_g_sGateInfo[ident][E_GATE_INFO_TRIGGER]);
				}
			}
			case E_OBJECT_REMOTE_GATE:
			{
				setproperty(0, "YSIReq", NO_GATE);
				#if !defined NO_OBJECTS_MOVE
					#if defined _YSI_VISUAL_AREAS
						if (Object_IsValid(ident) && !Object_IsAttached(YSI_g_sObjects[ident][E_OBJECT_MODEL]) && Area_IsValid(info))
						{
							new
								gate;
							while (gate < MAX_GATE_OBJECTS)
							{
								if (!YSI_g_sGateInfo[gate][E_GATE_INFO_OBJECT]) break;
								gate++;
							}
							if (gate == MAX_GATE_OBJECTS) return NO_GATE;
							
							DBGP4("Object_Remote() Gates: %d %d %d %d", gate, ident, instruction >>> 12, info);
							YSI_g_sGateInfo[gate][E_GATE_INFO_OBJECT] = ident | GATE_AREA_TRIGGER;
							YSI_g_sGateInfo[gate][E_GATE_INFO_TIME] = instruction >>> 12;
							YSI_g_sGateInfo[gate][E_GATE_INFO_TRIGGER] = info;
							YSI_g_sObjects[ident][E_OBJECT_MODEL] |= e_OBJ_FLAG_GATE;
							DBGP4("Object_Remote() Gate ID: %d", gate);
							#if !defined NO_GATE_AREA_LOOKUP
								new
									slot = info / 2,
									shift = (info % 2) * 16;
								YSI_g_sGateAreas[slot] = (YSI_g_sGateAreas[slot] & (0xFFFF0000 >>> shift)) | (gate << shift);
								DBGP4("Object_Remote() Lookup: %d %d %d", slot, shift, YSI_g_sGateAreas[slot]);
							#endif
							setproperty(0, "YSIReq", gate);
							DBGP4("Object_Remote() Return");
							return 1;
						}
					#endif
				#endif
			}
		}
		return 1;
	}
	
	/*----------------------------------------------------------------------------*-
	Function:
		YSIM_Objects
	Params:
		command - Instruction from the master system.
	Return:
		-
	Notes:
		Performs instructions on script start/end.
	-*----------------------------------------------------------------------------*/

	public YSIM_Objects(command)
	{
		#if OBJECT_WORLDS <= 0 || defined NO_PERSONAL_OBJECTS
			static
				sFake[2] = {-1, -1};
		#endif
		switch (command & 0xFF000000)
		{
			case E_MASTER_SET_MASTER:
			{
				YSI_g_sIsMaster = 1;
			}
			case E_MASTER_RELINQUISH:
			{
				new
					master = (command & 0x00FFFFFF);
				if (master == YSI_gMasterID)
				{
					CallRemoteFunction("Object_GetLimit", "");
					new
						parent = NO_OBJECT,
						siblings = NO_OBJECT,
						children = NO_OBJECT,
						Float:mx,
						Float:my,
						Float:mz,
						Float:ms,
						maxObjs = getproperty(0, "YSIReq"),
						i;
					for ( ; i < MAX_DYN_OBJECTS && i < maxObjs; i++)
					{
						if (YSI_g_sObjects[i][E_OBJECT_MODEL] & e_OBJ_FLAG_ACTIVE)
						{
							if (YSI_g_sObjects[i][E_OBJECT_SCRIPT] == master)
							{
								Object_Destroy(i, 0);
							}
							else
							{
								#if !defined NO_OBJECT_ATTACH
									parent = YSI_g_sObjects[i][E_OBJECT_PARENT];
									while (parent != NO_OBJECT && (YSI_g_sObjects[parent][E_OBJECT_SCRIPT] == master || parent > maxObjs))
									{
										Object_Destroy(parent, 0);
										parent = YSI_g_sObjects[i][E_OBJECT_PARENT];
									}
									siblings = YSI_g_sObjects[i][E_OBJECT_SIBLINGS];
									while (siblings != NO_OBJECT && (YSI_g_sObjects[siblings][E_OBJECT_SCRIPT] == master || siblings > maxObjs))
									{
										Object_Destroy(siblings, 0);
										siblings = YSI_g_sObjects[i][E_OBJECT_SIBLINGS];
									}
									children = YSI_g_sObjects[i][E_OBJECT_CHILDREN];
									while (children != NO_OBJECT && (YSI_g_sObjects[children][E_OBJECT_SCRIPT] == master || children > maxObjs))
									{
										Object_Destroy(children, 0);
										children = YSI_g_sObjects[i][E_OBJECT_CHILDREN];
									}
								#endif
								#if !defined NO_OBJECTS_MOVE
									mx = YSI_g_sObjects[i][E_OBJECT_MX];
									my = YSI_g_sObjects[i][E_OBJECT_MY];
									mz = YSI_g_sObjects[i][E_OBJECT_MZ];
									ms = YSI_g_sObjects[i][E_OBJECT_MS];
								#endif
								#if OBJECT_WORLDS > 0
									#if !defined NO_PERSONAL_OBJECTS
										CallRemoteFunction("Object_Broadcast", "iiifffffffffffiiiaiai", i,
											_:YSI_g_sObjects[i][E_OBJECT_MODEL],
											YSI_g_sObjects[i][E_OBJECT_SCRIPT],
											YSI_g_sObjects[i][E_OBJECT_X],
											YSI_g_sObjects[i][E_OBJECT_Y],
											YSI_g_sObjects[i][E_OBJECT_Z],
											YSI_g_sObjects[i][E_OBJECT_RX],
											YSI_g_sObjects[i][E_OBJECT_RY],
											YSI_g_sObjects[i][E_OBJECT_RZ],
											YSI_g_sObjects[i][E_OBJECT_VIEW],
											mx, my, mz, ms,
											parent, siblings, children,
											_:YSI_g_sObjects[i][E_OBJECT_WORLDS], OBJECT_WORLD_COUNT,
											_:YSI_g_sObjects[i][E_OBJECT_PLAYERS], PLAYER_BIT_ARRAY
										);
									#else
										CallRemoteFunction("Object_Broadcast", "iiifffffffffffiiiaiai", i,
											_:YSI_g_sObjects[i][E_OBJECT_MODEL],
											YSI_g_sObjects[i][E_OBJECT_SCRIPT],
											YSI_g_sObjects[i][E_OBJECT_X],
											YSI_g_sObjects[i][E_OBJECT_Y],
											YSI_g_sObjects[i][E_OBJECT_Z],
											YSI_g_sObjects[i][E_OBJECT_RX],
											YSI_g_sObjects[i][E_OBJECT_RY],
											YSI_g_sObjects[i][E_OBJECT_RZ],
											YSI_g_sObjects[i][E_OBJECT_VIEW],
											mx, my, mz, ms,
											parent, siblings, children,
											_:YSI_g_sObjects[i][E_OBJECT_WORLDS], OBJECT_WORLD_COUNT,
											sFake, 2
										);
									#endif
								#else
									#if !defined NO_PERSONAL_OBJECTS
										CallRemoteFunction("Object_Broadcast", "iiifffffffffffiiiaiai", i,
											_:YSI_g_sObjects[i][E_OBJECT_MODEL],
											YSI_g_sObjects[i][E_OBJECT_SCRIPT],
											YSI_g_sObjects[i][E_OBJECT_X],
											YSI_g_sObjects[i][E_OBJECT_Y],
											YSI_g_sObjects[i][E_OBJECT_Z],
											YSI_g_sObjects[i][E_OBJECT_RX],
											YSI_g_sObjects[i][E_OBJECT_RY],
											YSI_g_sObjects[i][E_OBJECT_RZ],
											YSI_g_sObjects[i][E_OBJECT_VIEW],
											mx, my, mz, ms,
											parent, siblings, children,
											sFake, 2,
											_:YSI_g_sObjects[i][E_OBJECT_PLAYERS], PLAYER_BIT_ARRAY
										);
									#else
										CallRemoteFunction("Object_Broadcast", "iiifffffffffffiiiaiai", i,
											_:YSI_g_sObjects[i][E_OBJECT_MODEL],
											YSI_g_sObjects[i][E_OBJECT_SCRIPT],
											YSI_g_sObjects[i][E_OBJECT_X],
											YSI_g_sObjects[i][E_OBJECT_Y],
											YSI_g_sObjects[i][E_OBJECT_Z],
											YSI_g_sObjects[i][E_OBJECT_RX],
											YSI_g_sObjects[i][E_OBJECT_RY],
											YSI_g_sObjects[i][E_OBJECT_RZ],
											YSI_g_sObjects[i][E_OBJECT_VIEW],
											mx, my, mz, ms,
											parent, siblings, children,
											sFake, 2,
											sFake, 2
										);
									#endif
								#endif
								continue;
							}
						}
						CallRemoteFunction("Object_UpdateUnused", "i", i);
					}
					while (i < maxObjs)
					{
						CallRemoteFunction("Object_UpdateUnused", "i", i);
						i++;
					}
					foreach (Player, playerid)
					{
						for (new obj = 1; obj <= MAY_OBJECTS; obj++)
						{
							if (IsValidPlayerObject(playerid, obj))
							{
								DestroyPlayerObject(playerid, obj);
								break;
							}
						}
					}
				}
				else
				{
					for (new i = 0; i < MAX_DYN_OBJECTS; i++)
					{
						if (YSI_g_sObjects[i][E_OBJECT_MODEL] & e_OBJ_FLAG_ACTIVE && YSI_g_sObjects[i][E_OBJECT_SCRIPT] == master)
						{
							Object_Destroy(i);
						}
					}
				}
			}
			case E_MASTER_NOT_MASTER:
			{
				YSI_g_sIsMaster = 0;
			}
		}
	}
	
	/*----------------------------------------------------------------------------*-
	Function:
		Object_GetLimit
	Params:
		-
	Return:
		-
	Notes:
		Sets up the new master for streaming and gets the number of objects it
		can handle.
	-*----------------------------------------------------------------------------*/

	public Object_GetLimit()
	{
		if (!YSI_g_sIsMaster) return;
		setproperty(0, "YSIReq", MAX_DYN_OBJECTS);
		YSI_g_sNoObjects = NO_OBJECT;
	}
	
	/*----------------------------------------------------------------------------*-
	Function:
		Object_Broadcast
	Params:
		id - Slot of the object.
		e_OBJ_FLAG:model - Object model data and flags.
		master - Script which owns the object.
		Float:x - X position.
		Float:y - Y position.
		Float:z - Z position.
		Float:rx - X rotation.
		Float:ry - Y rotation.
		Float:rz - Z rotation.
		Float:view - Object view distance.
		Float:mx - Movement x target.
		Float:my - Movement y target.
		Float:mz - Movement z target.
		Float:ms - Movement speed.
		parent - Object attachment parent.
		siblings - Object attachment sibling list.
		children - Object attachment children list.
		Bit:worlds[] - Worlds the object is in.
		wCount - Size of the world array.
		Bit:players[] - Players who can see the object.
		pCount - Size of the players array.
	Return:
		-
	Notes:
		Recieves data sent from the old master to the new master and stores it in
		the object data array.
	-*----------------------------------------------------------------------------*/

	public Object_Broadcast(id, e_OBJ_FLAG:model, master, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:view,
				Float:mx, Float:my, Float:mz, Float:ms, parent, siblings, children, Bit:worlds[], wCount, Bit:players[], pCount)
	{
		if (!YSI_g_sIsMaster) return 0;
		#if !defined NO_OBJECT_ATTACH
			YSI_g_sObjects[id][E_OBJECT_PARENT] = parent;
			YSI_g_sObjects[id][E_OBJECT_SIBLINGS] = siblings;
			YSI_g_sObjects[id][E_OBJECT_CHILDREN] = children;
		#else
			#pragma unused parent, siblings, children
		#endif
		#if !defined NO_OBJECTS_MOVE
			YSI_g_sObjects[id][E_OBJECT_MX] = mx;
			YSI_g_sObjects[id][E_OBJECT_MY] = my;
			YSI_g_sObjects[id][E_OBJECT_MZ] = mz;
			YSI_g_sObjects[id][E_OBJECT_MS] = ms;
		#else
			#pragma unused mx, my, mz, ms
		#endif
		YSI_g_sObjects[id][E_OBJECT_MODEL] = model | e_OBJ_FLAG_RECREATED;
		YSI_g_sObjects[id][E_OBJECT_SCRIPT] = master;
		YSI_g_sObjects[id][E_OBJECT_X] = x;
		YSI_g_sObjects[id][E_OBJECT_Y] = y;
		YSI_g_sObjects[id][E_OBJECT_Z] = z;
		YSI_g_sObjects[id][E_OBJECT_RX] = rx;
		YSI_g_sObjects[id][E_OBJECT_RY] = ry;
		YSI_g_sObjects[id][E_OBJECT_RZ] = rz;
		YSI_g_sObjects[id][E_OBJECT_VIEW] = view;
		#if OBJECT_WORLDS > 0
			for (new i = 0; i < wCount && i < Bit_Bits(OBJECT_WORLDS); i++)
			{
				YSI_g_sObjects[id][E_OBJECT_WORLDS][i] = worlds[i];
			}
		#else
			#pragma unused worlds, wCount
		#endif
		#if !defined NO_PERSONAL_OBJECTS
			for (new i = 0; i < pCount && i < PLAYER_BIT_ARRAY; i++)
			{
				YSI_g_sObjects[id][E_OBJECT_PLAYERS][i] = players[i];
			}
		#else
			#pragma unused players, pCount
		#endif
		Object_AddToUpdate(id);
		Object_AddToSector(Object_FindSector(x, y, z), id, view);
		return 1;
	}
	
	/*----------------------------------------------------------------------------*-
	Function:
		Object_UpdateUnused
	Params:
		obj - Object to add to the remote unused list.
	Return:
		-
	Notes:
		-
	-*----------------------------------------------------------------------------*/
	
	public Object_UpdateUnused(obj)
	{
		YSI_g_sObjects[obj][E_OBJECT_NEXT] = YSI_g_sNoObjects;
		YSI_g_sNoObjects = obj;
	}

	/*----------------------------------------------------------------------------*-
	Function:
		Object_CoOrdRemote
	Params:
		ident - Object to do code on.
		instruction - Function to perform.
		Float:f1 - First float data.
		Float:f2 - Second float data.
		Float:f3 - Third float data.
		Float:f4 - Fourth float data.
	Return:
		-
	Notes:
		Performs operations with locations on objects remotely.
	-*----------------------------------------------------------------------------*/

	public Object_CoOrdRemote(ident, instruction, Float:f1, Float:f2, Float:f3, Float:f4)
	{
		setproperty(0, "YSIReq", 0);
		if (!YSI_g_sIsMaster) return 0;
		switch (instruction)
		{
			case E_OBJECT_REMOTE_SETROT:
			{
				if (!Object_IsValid(ident) || Object_IsAttached(YSI_g_sObjects[ident][E_OBJECT_MODEL])) return 0;
				YSI_g_sObjects[ident][E_OBJECT_RX] = f1;
				YSI_g_sObjects[ident][E_OBJECT_RY] = f2;
				YSI_g_sObjects[ident][E_OBJECT_RZ] = f3;
				YSI_g_sObjects[ident][E_OBJECT_MODEL] |= e_OBJ_FLAG_ROTATED;
				Object_AddToUpdate(ident);
				setproperty(0, "YSIReq", 1);
				return 1;
			}
			case E_OBJECT_REMOTE_SETPOS:
			{
				if (!Object_IsValid(ident) || Object_IsAttached(YSI_g_sObjects[ident][E_OBJECT_MODEL])) return 0;
				#if !defined NO_OBJECT_ATTACH
					Object_UpdateChildSectors(YSI_g_sObjects[ident][E_OBJECT_CHILDREN], f1, f2, f3);
				#endif
				setproperty(0, "YSIReq", Object_SetPos(ident, f1, f2, f3));
			}
			case E_OBJECT_REMOTE_MOVETO:
			{
				if (Object_IsValid(ident))
				{
					Object_Move(ident, f1, f2, f3, f4);
					Object_AddToUpdate(ident);
					setproperty(0, "YSIReq", 1);
					return 1;
				}
			}
			case E_OBJECT_REMOTE_GATE_POS:
			{
				Object_SetGateTarget(ident, f1, f2, f3, f4);
			}
		}
		return 0;
	}
#endif

/*----------------------------------------------------------------------------*-
Function:
	Object_SetViewDistance
Params:
	objectid - Object to objSet custom view distance for.
	Float:view - Distance the object can be seen from.
Return:
	-
Notes:
	Sets how far away an object can be seen from.
-*----------------------------------------------------------------------------*/

stock Object_SetViewDistance(objectid, Float:view)
{
	#if defined _YSI_SETUP_MASTER
		if (YSI_g_sIsMaster)
		{
	#endif
			if (Object_IsValid(objectid))
			{
				view *= view;
				YSI_g_sObjects[objectid][E_OBJECT_VIEW] = view;
				new
					sector = YSI_g_sObjects[objectid][E_OBJECT_SECTOR];
				if (view > OBJECT_MAX_VIEW_DISTANCE)
				{
					if (sector != OBJECT_LOD_SECTOR)
					{
						Object_RemoveFromSector(sector, objectid);
						Object_AddToLOD(objectid);
					}
				}
				else if (sector == OBJECT_LOD_SECTOR)
				{
					Object_RemoveFromSector(sector, objectid);
					Object_AddToSector(Object_FindSector(YSI_g_sObjects[objectid][E_OBJECT_X], YSI_g_sObjects[objectid][E_OBJECT_Y], YSI_g_sObjects[objectid][E_OBJECT_Z]), objectid, view);
				}
				else if (sector < sizeof (YSI_g_sObjectSectors))
				{
					if (YSI_g_sObjectSectors[sector][E_OBJ_SECTOR_MAX_VIEW] < view) YSI_g_sObjectSectors[sector][E_OBJ_SECTOR_MAX_VIEW] = view;
				}
				return 1;
			}
			return 0;
	#if defined _YSI_SETUP_MASTER
		}
		else
		{
			return CallRemoteFunction("Object_Remote", "iii", objectid, _:view, E_OBJECT_REMOTE_VIEW);
		}
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	Object_AddToUpdate
Params:
	objectid - Object to add to the update list.
Return:
	-
Notes:
	Safely adds an object to the moved update list.
-*----------------------------------------------------------------------------*/

static stock Object_AddToUpdate(objectid)
{
	if (YSI_g_sObjects[objectid][E_OBJECT_UPDATES] == NO_OBJECT)
	{
		YSI_g_sObjects[objectid][E_OBJECT_UPDATES] = YSI_g_sSomethingMoved;
		YSI_g_sSomethingMoved = objectid;
	}
}

/*----------------------------------------------------------------------------*-
Function:
	Object_Object
Params:
	-
Return:
	-
Notes:
	Sets up variables for initial use.
-*----------------------------------------------------------------------------*/

Object_Object()
{
	static
		timer;
	if (!timer)
	{
		#if defined _YSI_SETUP_MASTER
			YSI_g_sIsMaster = Master_Add("YSIM_Objects");
		#endif
		YSI_g_sNoObjects = 0;
		new
			i;
		while (i < MAX_DYN_OBJECTS)
		{
			YSI_g_sObjects[i][E_OBJECT_UPDATES] = NO_OBJECT;
			YSI_g_sObjects[i++][E_OBJECT_NEXT] = i;
		}
		YSI_g_sObjects[MAX_DYN_OBJECTS - 1][E_OBJECT_NEXT] = NO_OBJECT;
		
		for (i = 0; i < OBJECT_SECTOR_ARRAY; i++)
		{
			YSI_g_sObjectSectors[i][E_OBJ_SECTOR_POINTER] = NO_OBJECT;
			YSI_g_sObjectSectors[i][E_OBJ_SECTOR_MAX_VIEW] = OBJECT_SIGHT;
		}
		
		YSI_g_sXSectorLocations[0] = OBJECT_BOUNDS_MINX;
		for (i = 1; i < OBJECT_SECTOR_X_EDGE; i++)
		{
			YSI_g_sXSectorLocations[i] = (float(OBJECT_BOUNDS_X_SIZE * i) / OBJECT_SECTOR_X_EDGE) + OBJECT_BOUNDS_MINX;
		}
		YSI_g_sXSectorLocations[OBJECT_SECTOR_X_EDGE] = OBJECT_BOUNDS_MAXX;
		YSI_g_sXSectorSize = (YSI_g_sXSectorLocations[1] - YSI_g_sXSectorLocations[0]);
		
		YSI_g_sYSectorLocations[0] = OBJECT_BOUNDS_MINY;
		for (i = 1; i < OBJECT_SECTOR_Y_EDGE; i++)
		{
			YSI_g_sYSectorLocations[i] = (float(OBJECT_BOUNDS_Y_SIZE * i) / OBJECT_SECTOR_Y_EDGE) + OBJECT_BOUNDS_MINY;
		}
		YSI_g_sYSectorLocations[OBJECT_SECTOR_Y_EDGE] = OBJECT_BOUNDS_MAXY;
		YSI_g_sYSectorSize = (YSI_g_sYSectorLocations[1] - YSI_g_sYSectorLocations[0]);

		#if defined _YSI_VISUAL_AREAS
			#if defined NO_GATE_AREA_LOOKUP
				for (i = 0; i < MAX_GATE_OBJECTS; i++)
				{
					YSI_g_sGateInfo[i][E_GATE_INFO_TRIGGER] = NO_GATE;
				}
			#else
				for (i = 0; i < sizeof (YSI_g_sGateAreas); i++)
				{
					YSI_g_sGateAreas[i] = NO_GATE;
				}
			#endif
		#endif
		for (i = 0; i < MAX_PLAYERS; i++)
		{
			for (new j = 0; j < MAY_OBJECTS; j++)
			{
				YSI_g_sPlayerObjects[i][j] = NO_OBJECT;
			}
		}
		timer = Timer_Add("Object_Loop", OBJECT_LOOP_GRANULARITY);
	}
	return 1;
}

/*----------------------------------------------------------------------------*-
Function:
	CreateDynamicObject
Params:
	model - Model of object.
	Float:X - x position.
	Float:Y - y position.
	Float:Z - z position.
	Float:RX - x rotation.
	Float:RY - y rotation.
	Float:RZ - z rotation.
Return:
	-
Notes:
	Dynamic wrapper for CreateObject.
-*----------------------------------------------------------------------------*/

stock CreateDynamicObject(model, Float:X, Float:Y, Float:Z, Float:RX = 0.0, Float:RY = 0.0, Float:RZ = 0.0)
{
	new
		object = Object_Add(model, X, Y, Z, RX, RY, RZ);
	if (object != NO_OBJECT)
	{
		Object_AddToAllWorlds(object);
		Object_AddToAllPlayers(object);
	}
	return object;
}

/*----------------------------------------------------------------------------*-
Function:
	CreatePlayerDynamicObject
Params:
	playerid - Player to create it for.
	model - Model of object.
	Float:X - x position.
	Float:Y - y position.
	Float:Z - z position.
	Float:RX - x rotation.
	Float:RY - y rotation.
	Float:RZ - z rotation.
Return:
	-
Notes:
	Dynamic wrapper for CreatePlayerObject.
-*----------------------------------------------------------------------------*/

stock CreatePlayerDynamicObject(playerid, model, Float:X, Float:Y, Float:Z, Float:RX = 0.0, Float:RY = 0.0, Float:RZ = 0.0)
{
	new
		object;
	#if !defined NO_PLAYER_ONLY
		object = Object_Add(model, X, Y, Z, RX, RY, RZ);
		if (object != NO_OBJECT)
		{
			Object_RemoveFromAllPlayers(object);
			Object_AddToPlayer(object, playerid);
			Object_AddToAllWorlds(object);
		}
	#else
		#pragma unused playerid
		object = CreateDynamicObject(model, X, Y, Z, RX, RY, RZ);
	#endif
	return object;
}

/*----------------------------------------------------------------------------*-
Function:
	CreateVWDynamicObject
Params:
	virtualworld - World to create it in.
	model - Model of object.
	Float:X - x position.
	Float:Y - y position.
	Float:Z - z position.
	Float:RX - x rotation.
	Float:RY - y rotation.
	Float:RZ - z rotation.
Return:
	-
Notes:
	Dynamic wrapper for CreateObject with VW support.
-*----------------------------------------------------------------------------*/

stock CreateVWDynamicObject(virtualworld, model, Float:X, Float:Y, Float:Z, Float:RX = 0.0, Float:RY = 0.0, Float:RZ = 0.0)
{
	new
		object;
	#if OBJECT_WORLDS > 0
		object = Object_Add(model, X, Y, Z, RX, RY, RZ);
		if (object != NO_OBJECT)
		{
			Object_RemoveFromAllWorlds(object);
			Object_AddToWorld(object, virtualworld);
			Object_AddToAllPlayers(object);
		}
	#else
		#pragma unused virtualworld
		object = CreateDynamicObject(model, X, Y, Z, RX, RY, RZ);
	#endif
	return object;
}

/*----------------------------------------------------------------------------*-
Function:
	CreatePlayerVWDynamicObject
Params:
	playerid 0 Player to create it for.
	virtualworld - World to create it in.
	model - Model of object.
	Float:X - x position.
	Float:Y - y position.
	Float:Z - z position.
	Float:RX - x rotation.
	Float:RY - y rotation.
	Float:RZ - z rotation.
Return:
	-
Notes:
	Dynamic wrapper for CreatePlayerObject with VW support.
-*----------------------------------------------------------------------------*/

stock CreatePlayerVWDynamicObject(playerid, virtualworld, model, Float:X, Float:Y, Float:Z, Float:RX = 0.0, Float:RY = 0.0, Float:RZ = 0.0)
{
	new
		object;
	#if !defined NO_PLAYER_ONLY
		#if OBJECT_WORLDS > 0
			object = Object_Add(model, X, Y, Z, RX, RY, RZ);
			if (object != NO_OBJECT)
			{
				Object_AddToWorld(object, virtualworld);
				Object_AddToPlayer(object, playerid);
			}
		#else
			object = CreatePlayerDynamicObject(playerid, model, X, Y, Z, RX, RY, RZ);
			#pragma unused virtualworld
		#endif
	#else
		#if OBJECT_WORLDS > 0
			object = CreateVWDynamicObject(virtualworld, model, X, Y, Z, RX, RY, RZ);
			#pragma unused playerid
		#else
			object = CreateDynamicObject(model, X, Y, Z, RX, RY, RZ);
			#pragma unused playerid, virtualworld
		#endif
	#endif
	return object;
}

/*----------------------------------------------------------------------------*-
Function:
	Object_Add
Params:
	model - The object model.
	Float:x - X position.
	Float:y - Y position.
	Float:z - Z position.
	Float:rx - X rotation.
	Float:ry - Y rotation.
	Float:rz - Z rotation.
Return:
	-
Notes:
	Internal object addition function.  Checks if there are any slots open
	and adds the object to the list if there are.  Sets up initial flags and
	stores the position.
-*----------------------------------------------------------------------------*/

static stock Object_Add(model, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
#if defined _YSI_SETUP_MASTER
		if (!Object_IsValidModel(model)) return NO_OBJECT;
		if (!YSI_g_sIsMaster)
		{
			CallRemoteFunction("Object_AddRem", "iiffffff", YSI_gMasterID, model, x, y, z, rx, ry, rz);
			return getproperty(0, "YSIReq");
		}
		else
		{
			return Object_AddRem(YSI_gMasterID, model, x, y, z, rx, ry, rz);
		}
	}
	
/*----------------------------------------------------------------------------*-
Function:
	Object_AddRem
Params:
	master - The script which owns the object being made.
	model - The object model.
	Float:x - X position.
	Float:y - Y position.
	Float:z - Z position.
	Float:rx - X rotation.
	Float:ry - Y rotation.
	Float:rz - Z rotation.
Return:
	-
Notes:
	Remote wrapper for Object_Add.
-*----------------------------------------------------------------------------*/

	public Object_AddRem(master, model, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
	{
		DBGP3("Object_AddRem() start %d", YSI_gMasterID);
		if (!YSI_g_sIsMaster) return NO_OBJECT;
		DBGP3("Object_AddRem() Master");
		setproperty(0, "YSIReq", NO_OBJECT);
#endif
	model &= _:e_OBJ_FLAG_MODEL;
	if (YSI_g_sNoObjects == NO_OBJECT) return NO_OBJECT;
#if !defined _YSI_SETUP_MASTER
		if (!Object_IsValidModel(model)) return NO_OBJECT;
#endif
	new
		pointer = YSI_g_sNoObjects;
	YSI_g_sNoObjects = YSI_g_sObjects[pointer][E_OBJECT_NEXT];
	#if defined _YSI_SETUP_MASTER
		YSI_g_sObjects[pointer][E_OBJECT_SCRIPT] = master;
	#endif
	YSI_g_sObjects[pointer][E_OBJECT_MODEL] = e_OBJ_FLAG:model | e_OBJ_FLAG_ACTIVE | e_OBJ_FLAG_RECREATED | Object_SetAttach(NO_ATTACH_PLAYER);
	YSI_g_sObjects[pointer][E_OBJECT_X] = x;
	YSI_g_sObjects[pointer][E_OBJECT_Y] = y;
	YSI_g_sObjects[pointer][E_OBJECT_Z] = z;
	YSI_g_sObjects[pointer][E_OBJECT_RX] = rx;
	YSI_g_sObjects[pointer][E_OBJECT_RY] = ry;
	YSI_g_sObjects[pointer][E_OBJECT_RZ] = rz;
	YSI_g_sObjects[pointer][E_OBJECT_VIEW] = OBJECT_SIGHT;
	#if !defined NO_OBJECT_ATTACH
		YSI_g_sObjects[pointer][E_OBJECT_PARENT] = NO_OBJECT;
		YSI_g_sObjects[pointer][E_OBJECT_SIBLINGS] = NO_OBJECT;
		YSI_g_sObjects[pointer][E_OBJECT_CHILDREN] = NO_OBJECT;
	#endif
	Object_AddToUpdate(pointer);
	Object_AddToSector(Object_FindSector(x, y, z), pointer, OBJECT_SIGHT);
#if defined _YSI_SETUP_MASTER
		setproperty(0, "YSIReq", pointer);
#endif
	return pointer;
}

/*----------------------------------------------------------------------------*-
Function:
	Object_FindSector
Params:
	Float:x - X point.
	Float:y - Y point.
	Float:z - Z point.
Return:
	Point's sector.
Notes:
	Finds the sector of a point.
-*----------------------------------------------------------------------------*/

static stock Object_FindSector(Float:x, Float:y, Float:z)
{
	if (z > 800.0) return OBJECT_INT_SECTOR;
	if (x < OBJECT_BOUNDS_MINX || x >= OBJECT_BOUNDS_MAXX || y < OBJECT_BOUNDS_MINY || y >= OBJECT_BOUNDS_MAXY) return OBJECT_NO_SECTOR;
	x = floatsub(x, float(OBJECT_BOUNDS_MINX)) / OBJECT_REAL_X_SECTOR_SIZE;
	y = floatsub(y, float(OBJECT_BOUNDS_MINY)) / OBJECT_REAL_Y_SECTOR_SIZE;
	new
		val;
	val = (floatround(x, floatround_floor) * OBJECT_SECTOR_X_EDGE) + floatround(y, floatround_floor);
	return val;
}

/*----------------------------------------------------------------------------*-
Function:
	Object_AddToOOB
Params:
	pointer - Index of the object to add.
Return:
	-
Notes:
	Adds an object to the linked list for objects out of bounds of the grid
	system (i.e. stores objects out the +/-OBJECT_BOUNDS world limit).
-*----------------------------------------------------------------------------*/

static stock Object_AddToOOB(pointer)
{
	if (YSI_g_sOtherSector == NO_OBJECT)
	{
		YSI_g_sOtherSector = pointer;
		YSI_g_sObjects[pointer][E_OBJECT_NEXT] = pointer;
	}
	else
	{
		YSI_g_sObjects[pointer][E_OBJECT_NEXT] = YSI_g_sObjects[YSI_g_sOtherSector][E_OBJECT_NEXT];
		YSI_g_sObjects[YSI_g_sOtherSector][E_OBJECT_NEXT] = pointer;
	}
	YSI_g_sObjects[pointer][E_OBJECT_SECTOR] = OBJECT_NO_SECTOR;
}

/*----------------------------------------------------------------------------*-
Function:
	Object_AddToLOD
Params:
	pointer - Index of the object to add.
Return:
	-
Notes:
	Adds an object to the linked list for objects with views > OBJECT_MAX_VIEW
-*----------------------------------------------------------------------------*/

static stock Object_AddToLOD(pointer)
{
	if (YSI_g_sLODObjects == NO_OBJECT)
	{
		YSI_g_sLODObjects = pointer;
		YSI_g_sObjects[pointer][E_OBJECT_NEXT] = pointer;
	}
	else
	{
		YSI_g_sObjects[pointer][E_OBJECT_NEXT] = YSI_g_sObjects[YSI_g_sLODObjects][E_OBJECT_NEXT];
		YSI_g_sObjects[YSI_g_sLODObjects][E_OBJECT_NEXT] = pointer;
	}
	YSI_g_sObjects[pointer][E_OBJECT_SECTOR] = OBJECT_LOD_SECTOR;
}

/*----------------------------------------------------------------------------*-
Function:
	Object_AddToINT
Params:
	pointer - Index of the object to add.
Return:
	-
Notes:
	Adds an object to the linked list for objects in interiors.
-*----------------------------------------------------------------------------*/

static stock Object_AddToINT(pointer)
{
	if (YSI_g_sInteriorObjects == NO_OBJECT)
	{
		YSI_g_sInteriorObjects = pointer;
		YSI_g_sObjects[pointer][E_OBJECT_NEXT] = pointer;
	}
	else
	{
		YSI_g_sObjects[pointer][E_OBJECT_NEXT] = YSI_g_sObjects[YSI_g_sInteriorObjects][E_OBJECT_NEXT];
		YSI_g_sObjects[YSI_g_sInteriorObjects][E_OBJECT_NEXT] = pointer;
	}
	YSI_g_sObjects[pointer][E_OBJECT_SECTOR] = OBJECT_LOD_SECTOR;
}

/*----------------------------------------------------------------------------*-
Function:
	Object_AddToMovingList
Params:
	pointer - Index of the object to add.
Return:
	-
Notes:
	Adds an object to the linked list for dynamic objects.
-*----------------------------------------------------------------------------*/

static stock Object_AddToMovingList(pointer)
{
	if (YSI_g_sMovingObjects == NO_OBJECT)
	{
		YSI_g_sMovingObjects = pointer;
		YSI_g_sObjects[pointer][E_OBJECT_NEXT] = pointer;
	}
	else
	{
		YSI_g_sObjects[pointer][E_OBJECT_NEXT] = YSI_g_sObjects[YSI_g_sMovingObjects][E_OBJECT_NEXT];
		YSI_g_sObjects[YSI_g_sMovingObjects][E_OBJECT_NEXT] = pointer;
	}
	YSI_g_sObjects[pointer][E_OBJECT_SECTOR] = OBJECT_NO_SECTOR;
}
 
/*----------------------------------------------------------------------------*-
Function:
	Object_AddToSector
Params:
	sector - Sector of object.
	pointer - Index of object.
	Float:view - Distance the object can be seen from.
Return:
	-
Notes:
	Saves an object as being in a sector.
-*----------------------------------------------------------------------------*/

static stock Object_AddToSector(sector, pointer, Float:view)
{
	if (sector == OBJECT_NO_SECTOR) Object_AddToOOB(pointer);
	else if (sector == OBJECT_INT_SECTOR) Object_AddToINT(pointer);
	else if (view > (OBJECT_MAX_VIEW_DISTANCE * OBJECT_MAX_VIEW_DISTANCE)) Object_AddToLOD(pointer);
	else
	{
		new
			data = YSI_g_sObjectSectors[sector][E_OBJ_SECTOR_POINTER];
		if (data == NO_OBJECT)
		{
			YSI_g_sObjectSectors[sector][E_OBJ_SECTOR_POINTER] = pointer;
			YSI_g_sObjects[pointer][E_OBJECT_NEXT] = pointer;
		}
		else
		{
			YSI_g_sObjects[pointer][E_OBJECT_NEXT] = YSI_g_sObjects[data][E_OBJECT_NEXT];
			YSI_g_sObjects[data][E_OBJECT_NEXT] = pointer;
		}
		YSI_g_sObjects[pointer][E_OBJECT_SECTOR] = sector;
		if (view > YSI_g_sObjectSectors[sector][E_OBJ_SECTOR_MAX_VIEW]) YSI_g_sObjectSectors[sector][E_OBJ_SECTOR_MAX_VIEW] = view;
	}
}

/*----------------------------------------------------------------------------*-
Function:
	DestroyDynamicObject
Params:
	objectid - Object to destroy.
Return:
	-
Notes:
	Dynamic wrapper for DestroyObject.  Removes the object from it's list by
	using the cyclic property to find the previous object and repointing it to
	the object after the removed one.  This ay make it point to itself but
	this is a good thing.  The object is then added to the unassigned list in
	the same way as it's added to a normal list and finally the object flags
	are reset to destroy the data.
-*----------------------------------------------------------------------------*/

stock DestroyDynamicObject(objectid)
{
#if defined _YSI_SETUP_MASTER
	if (YSI_g_sIsMaster)
	{
#endif
		if (Object_IsValid(objectid))
		{
			return Object_Destroy(objectid);
		}
		return 0;
#if defined _YSI_SETUP_MASTER
	}
	else
	{
		CallRemoteFunction("Object_Remote", "iii", objectid, 0, E_OBJECT_REMOTE_DESTROY);
		return getproperty(0, "YSIReq");
	}
#endif
}

/*----------------------------------------------------------------------------*-
Function:
	Object_Destroy
Params:
	objectid - Object to destroy.
	remove - Wether to update client side objects.
Return:
	-
Notes:
	Does the hard work for DestroyDynamicObject.
-*----------------------------------------------------------------------------*/

static stock Object_Destroy(objectid, remove = 1)
{
	Object_RemoveFromSector(YSI_g_sObjects[objectid][E_OBJECT_SECTOR], objectid);
	if (YSI_g_sNoObjects == NO_OBJECT)
	{
		YSI_g_sNoObjects = objectid;
		YSI_g_sObjects[objectid][E_OBJECT_NEXT] = objectid;
	}
	else
	{
		YSI_g_sObjects[objectid][E_OBJECT_NEXT] = YSI_g_sObjects[YSI_g_sNoObjects][E_OBJECT_NEXT];
		YSI_g_sObjects[YSI_g_sNoObjects][E_OBJECT_NEXT] = objectid;
	}
	#if !defined NO_OBJECT_ATTACH
		new
			children = YSI_g_sObjects[objectid][E_OBJECT_CHILDREN],
			parent = YSI_g_sObjects[objectid][E_OBJECT_PARENT],
			old = NO_OBJECT,
			last = NO_OBJECT;
		while (children != NO_OBJECT)
		{
			last = children;
			YSI_g_sObjects[children][E_OBJECT_PARENT] = parent;
			children = YSI_g_sObjects[children][E_OBJECT_SIBLINGS];
		}
		if (parent != NO_OBJECT)
		{
			old = YSI_g_sObjects[parent][E_OBJECT_CHILDREN];
			if (old == objectid)
			{
				old = YSI_g_sObjects[objectid][E_OBJECT_SIBLINGS];
			}
			else
			{
				children = old;
				new
					obj;
				do
				{
					obj = children;
					children = YSI_g_sObjects[children][E_OBJECT_SIBLINGS];
				}
				while (children != objectid);
				YSI_g_sObjects[obj][E_OBJECT_SIBLINGS] = YSI_g_sObjects[objectid][E_OBJECT_SIBLINGS];
			}
			if (last != NO_OBJECT)
			{
				YSI_g_sObjects[last][E_OBJECT_SIBLINGS] = old;
			}
			YSI_g_sObjects[parent][E_OBJECT_CHILDREN] = YSI_g_sObjects[objectid][E_OBJECT_CHILDREN];
		}
	#endif
	YSI_g_sObjects[objectid][E_OBJECT_MODEL] = e_OBJ_FLAG:0;
	if (remove)
	{
		foreach (Player, playerid)
		{
			for (new i = 0; i < MAY_OBJECTS; i++)
			{
				if (YSI_g_sPlayerObjects[playerid][i] == objectid)
				{
					DestroyPlayerObject(playerid, i + 1);
					break;
				}
			}
		}
	}
	return 1;
}

/*----------------------------------------------------------------------------*-
Function:
	Object_RemoveFromSector
Params:
	sector - Sector list to modify.
	objectid - Object to remove.
Return:
	-
Notes:
	Used to be part of DestroyDynamicObject but is needed by other API
	functions.
-*----------------------------------------------------------------------------*/

static stock Object_RemoveFromSector(sector, objectid)
{
	new
		pointer = objectid,
		last,
		Float:newview = OBJECT_SIGHT;
	do
	{
		last = pointer;
		pointer = YSI_g_sObjects[last][E_OBJECT_NEXT];
		if (last != objectid && YSI_g_sObjects[last][E_OBJECT_VIEW] > newview) newview = YSI_g_sObjects[last][E_OBJECT_VIEW];
	}
	while (pointer != objectid);
	if (last == objectid)
	{
		if (YSI_g_sObjects[objectid][E_OBJECT_MODEL] & e_OBJ_FLAG_MOVED) YSI_g_sMovingObjects = NO_OBJECT;
		else if (sector == OBJECT_NO_SECTOR) YSI_g_sOtherSector = NO_OBJECT;
		else if (sector == OBJECT_LOD_SECTOR) YSI_g_sLODObjects = NO_OBJECT;
		else if (sector == OBJECT_INT_SECTOR) YSI_g_sInteriorObjects = NO_OBJECT;
		else
		{
			YSI_g_sObjectSectors[sector][E_OBJ_SECTOR_POINTER] = NO_OBJECT;
			YSI_g_sObjectSectors[sector][E_OBJ_SECTOR_MAX_VIEW] = OBJECT_SIGHT;
		}
	}
	else
	{
		if (YSI_g_sObjects[objectid][E_OBJECT_MODEL] & e_OBJ_FLAG_MOVED)
		{
			if (YSI_g_sMovingObjects == objectid) YSI_g_sMovingObjects = last;
		}
		else if (sector == OBJECT_NO_SECTOR)
		{
			if (YSI_g_sOtherSector == objectid) YSI_g_sOtherSector = last;
		}
		else if (sector == OBJECT_LOD_SECTOR)
		{
			if (YSI_g_sLODObjects == objectid) YSI_g_sLODObjects = last;
		}
		else if (sector == OBJECT_INT_SECTOR)
		{
			if (YSI_g_sInteriorObjects == objectid) YSI_g_sInteriorObjects = last;
		}
		else if (YSI_g_sObjectSectors[sector][E_OBJ_SECTOR_POINTER] == objectid)
		{
			YSI_g_sObjectSectors[sector][E_OBJ_SECTOR_POINTER] = last;
			YSI_g_sObjectSectors[sector][E_OBJ_SECTOR_MAX_VIEW] = newview;
		}
		YSI_g_sObjects[last][E_OBJECT_NEXT] = YSI_g_sObjects[objectid][E_OBJECT_NEXT];
	}
}

/*----------------------------------------------------------------------------*-
Function:
	SetDynamicObjectPos
Params:
	objectid - Object to objSet new position of.
	Float:x - X co-ordinate.
	Float:y - Y co-ordintae.
	Float:z - Z co-ordinate.
Return:
	-
Notes:
	Updated to update child positions to (but NOT parent).
-*----------------------------------------------------------------------------*/

stock SetDynamicObjectPos(objectid, Float:x, Float:y, Float:z)
{
	#if defined _YSI_SETUP_MASTER
		if (YSI_g_sIsMaster)
		{
	#endif
			if (!Object_IsValid(objectid) || Object_IsAttached(YSI_g_sObjects[objectid][E_OBJECT_MODEL])) return 0;
			#if !defined NO_OBJECT_ATTACH
				Object_UpdateChildSectors(YSI_g_sObjects[objectid][E_OBJECT_CHILDREN], x, y, z);
			#endif
			return Object_SetPos(objectid, x, y, z);
	#if defined _YSI_SETUP_MASTER
		}
		else
		{
			CallRemoteFunction("Object_CoOrdRemote", "iiffff", objectid, E_OBJECT_REMOTE_SETPOS, x, y, z, 0.0);
			return getproperty(0, "YSIReq");
		}
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	Object_SetPos
Params:
	objectid - Object to objSet new position of.
	Float:x - X co-ordinate.
	Float:y - Y co-ordintae.
	Float:z - Z co-ordinate.
Return:
	-
Notes:
	Does the actual relocation of an object.
-*----------------------------------------------------------------------------*/

static stock Object_SetPos(objectid, Float:x, Float:y, Float:z)
{
	new
		newsec = Object_FindSector(x, y, z),
		oldsec;
	if (newsec != (oldsec = YSI_g_sObjects[objectid][E_OBJECT_SECTOR]))
	{
		Object_RemoveFromSector(oldsec, objectid);
		Object_AddToSector(newsec, objectid, YSI_g_sObjects[objectid][E_OBJECT_VIEW]);
	}
	#if !defined NO_OBJECT_ATTACH
		new
			parent = YSI_g_sObjects[objectid][E_OBJECT_PARENT];
		if (parent != NO_OBJECT)
		{
			new
				Float:nx,
				Float:ny,
				Float:nz;
			Object_GetPos(parent, nx, ny, nz);
			YSI_g_sObjects[objectid][E_OBJECT_X] = x - nx;
			YSI_g_sObjects[objectid][E_OBJECT_Y] = y - ny;
			YSI_g_sObjects[objectid][E_OBJECT_Z] = z - nz;
		}
		else
		{
	#endif
			YSI_g_sObjects[objectid][E_OBJECT_X] = x;
			YSI_g_sObjects[objectid][E_OBJECT_Y] = y;
			YSI_g_sObjects[objectid][E_OBJECT_Z] = z;
	#if !defined NO_OBJECT_ATTACH
		}
	#endif
	YSI_g_sObjects[objectid][E_OBJECT_MODEL] |= e_OBJ_FLAG_JUMPED;
	Object_AddToUpdate(objectid);
	return 1;
}

/*----------------------------------------------------------------------------*-
Function:
	Object_UpdateChildSectors
Params:
	objectid - Object to update children of.
	Float:x - X co-ordinate of parent.
	Float:y - Y co-ordintae of parent.
	Float:z - Z co-ordinate of parent.
Return:
	-
Notes:
	Doesn't update the position parameter as that's relative to the parent for
	child objects.  Recursive function to update sectors of children of
	children.
-*----------------------------------------------------------------------------*/

#if !defined NO_OBJECT_ATTACH
static stock Object_UpdateChildSectors(objectid, Float:x, Float:y, Float:z)
{
	new
		Float:nx,
		Float:ny,
		Float:nz,
		newsec,
		oldsec;
	while (objectid != NO_OBJECT)
	{
		if (Object_IsAttached(objectid))
		{
			nx = x + YSI_g_sObjects[objectid][E_OBJECT_X];
			ny = y + YSI_g_sObjects[objectid][E_OBJECT_Y];
			nz = z + YSI_g_sObjects[objectid][E_OBJECT_Z];
			newsec = Object_FindSector(nx, ny, nz);
			if (newsec != (oldsec = YSI_g_sObjects[objectid][E_OBJECT_SECTOR]))
			{
				Object_RemoveFromSector(oldsec, objectid);
				Object_AddToSector(newsec, objectid, YSI_g_sObjects[objectid][E_OBJECT_VIEW]);
			}
			Object_UpdateChildSectors(YSI_g_sObjects[objectid][E_OBJECT_CHILDREN], nx, ny, nz);
			YSI_g_sObjects[objectid][E_OBJECT_MODEL] |= e_OBJ_FLAG_JUMPED;
		}
		objectid = YSI_g_sObjects[objectid][E_OBJECT_SIBLINGS];
	}
}
#endif

/*----------------------------------------------------------------------------*-
Function:
	SetDynamicObjectRot
Params:
	objectid - Object to objSet new rotation of.
	Float:x - X rotation.
	Float:y - Y rotation.
	Float:z - Z rotation.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

stock SetDynamicObjectRot(objectid, Float:x, Float:y, Float:z)
{
	#if defined _YSI_SETUP_MASTER
		if (YSI_g_sIsMaster)
		{
	#endif
			if (!Object_IsValid(objectid) || Object_IsAttached(YSI_g_sObjects[objectid][E_OBJECT_MODEL])) return 0;
			YSI_g_sObjects[objectid][E_OBJECT_RX] = x;
			YSI_g_sObjects[objectid][E_OBJECT_RY] = y;
			YSI_g_sObjects[objectid][E_OBJECT_RZ] = z;
			YSI_g_sObjects[objectid][E_OBJECT_MODEL] |= e_OBJ_FLAG_ROTATED;
			Object_AddToUpdate(objectid);
			return 1;
	#if defined _YSI_SETUP_MASTER
		}
		else
		{
			CallRemoteFunction("Object_CoOrdRemote", "iiffff", objectid, E_OBJECT_REMOTE_SETROT, x, y, z, 0.0);
			return getproperty(0, "YSIReq");
		}
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	GetDynamicObjectRot
Params:
	objectid - Object to objSet new rotation of.
	&Float:x - X rotation store.
	&Float:y - Y rotation store.
	&Float:z - Z rotation store.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

stock GetDynamicObjectRot(objectid, &Float:x, &Float:y, &Float:z)
{
	#if defined _YSI_SETUP_MASTER
		if (YSI_g_sIsMaster)
		{
	#endif
			if (!Object_IsValid(objectid) || Object_IsAttached(YSI_g_sObjects[objectid][E_OBJECT_MODEL])) return 0;
			x = YSI_g_sObjects[objectid][E_OBJECT_RX];
			y = YSI_g_sObjects[objectid][E_OBJECT_RY];
			z = YSI_g_sObjects[objectid][E_OBJECT_RZ];
			return 1;
	#if defined _YSI_SETUP_MASTER
		}
		else
		{
			CallRemoteFunction("Object_Remote", "iii", objectid, 0, E_OBJECT_REMOTE_GETROT);
			x = Float:getproperty(0, "YSIReq");
			y = Float:getproperty(0, "YSIReq2");
			z = Float:getproperty(0, "YSIReq3");
			deleteproperty(0, "YSIReq2");
			deleteproperty(0, "YSIReq3");
		}
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	Object_AddToWorld
Params:
	object - Object to add.
	world - World to add to.
Return:
	-
Notes:
	Makes an object visible in a world.
-*----------------------------------------------------------------------------*/

stock Object_AddToWorld(object, world)
{
	#if OBJECT_WORLDS > 0
		#if defined _YSI_SETUP_MASTER
			if (YSI_g_sIsMaster)
			{
		#endif
				if (Object_IsValid(object)) Bit_Set(YSI_g_sObjects[object][E_OBJECT_WORLDS], world, 1, OBJECT_WORLD_COUNT);
		#if defined _YSI_SETUP_MASTER
			}
			else
			{
				CallRemoteFunction("Object_Remote", "iii", object, world, E_OBJECT_REMOTE_ADDW);
			}
		#endif
	#else
		#pragma unused object, world
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	Object_RemoveFromWorld
Params:
	object - Object to remove.
	world - World to remove from.
Return:
	-
Notes:
	Makes an object invisible in a world.
-*----------------------------------------------------------------------------*/

stock Object_RemoveFromWorld(object, world)
{
	#if OBJECT_WORLDS > 0
		#if defined _YSI_SETUP_MASTER
			if (YSI_g_sIsMaster)
			{
		#endif
				if (Object_IsValid(object)) Bit_Set(YSI_g_sObjects[object][E_OBJECT_WORLDS], world, 0, OBJECT_WORLD_COUNT);
		#if defined _YSI_SETUP_MASTER
			}
			else
			{
				CallRemoteFunction("Object_Remote", "iii", object, world, E_OBJECT_REMOTE_REMW);
			}
		#endif
	#else
		#pragma unused object, world
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	Object_AddToPlayer
Params:
	object - Object to add.
	playerid - Player to add to.
Return:
	-
Notes:
	Makes an object visible to a player.
-*----------------------------------------------------------------------------*/

stock Object_AddToPlayer(object, playerid)
{
	#if !defined NO_PERSONAL_OBJECTS
		#if defined _YSI_SETUP_MASTER
			if (YSI_g_sIsMaster)
			{
		#endif
				if (Object_IsValid(object)) Bit_Set(YSI_g_sObjects[object][E_OBJECT_PLAYERS], playerid, 1, PLAYER_BIT_ARRAY);
		#if defined _YSI_SETUP_MASTER
			}
			else
			{
				CallRemoteFunction("Object_Remote", "iii", object, playerid, E_OBJECT_REMOTE_ADDP);
			}
		#endif
	#else
		#pragma unused object, playerid
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	Object_RemoveFromWorld
Params:
	object - Object to remove.
	playerid - Player to remove from.
Return:
	-
Notes:
	Makes an object invisible to a player.
-*----------------------------------------------------------------------------*/

stock Object_RemoveFromPlayer(object, playerid)
{
	#if !defined NO_PERSONAL_OBJECTS
		#if defined _YSI_SETUP_MASTER
			if (YSI_g_sIsMaster)
			{
		#endif
				if (Object_IsValid(object)) Bit_Set(YSI_g_sObjects[object][E_OBJECT_PLAYERS], playerid, 0, PLAYER_BIT_ARRAY);
		#if defined _YSI_SETUP_MASTER
			}
			else
			{
				CallRemoteFunction("Object_Remote", "iii", object, playerid, E_OBJECT_REMOTE_REMP);
			}
		#endif
	#else
		#pragma unused object, playerid
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	Object_AddToAllWorlds
Params:
	object - Object to add.
Return:
	-
Notes:
	Makes an object visible in all worlds.
-*----------------------------------------------------------------------------*/

stock Object_AddToAllWorlds(object)
{
	#if OBJECT_WORLDS > 0
		#if defined _YSI_SETUP_MASTER
			if (YSI_g_sIsMaster)
			{
		#endif
				if (Object_IsValid(object)) Bit_SetAll(YSI_g_sObjects[object][E_OBJECT_WORLDS], 1, OBJECT_WORLD_COUNT);
		#if defined _YSI_SETUP_MASTER
			}
			else
			{
				CallRemoteFunction("Object_Remote", "iii", object, 0, E_OBJECT_REMOTE_ALLWA);
			}
		#endif
	#else
		#pragma unused object
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	Object_RemoveFromAllWorlds
Params:
	object - Object to remove.
Return:
	-
Notes:
	Makes an object invisible in all worlds.
-*----------------------------------------------------------------------------*/

stock Object_RemoveFromAllWorlds(object)
{
	#if OBJECT_WORLDS > 0
		#if defined _YSI_SETUP_MASTER
			if (YSI_g_sIsMaster)
			{
		#endif
				if (Object_IsValid(object)) Bit_SetAll(YSI_g_sObjects[object][E_OBJECT_WORLDS], 0, OBJECT_WORLD_COUNT);
		#if defined _YSI_SETUP_MASTER
			}
			else
			{
				CallRemoteFunction("Object_Remote", "iii", object, 0, E_OBJECT_REMOTE_ALLWR);
			}
		#endif
	#else
		#pragma unused object
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	Object_AddToAllPlayers
Params:
	object - Object to add.
Return:
	-
Notes:
	Makes an object visible to all players.
-*----------------------------------------------------------------------------*/

stock Object_AddToAllPlayers(object)
{
	#if !defined NO_PERSONAL_OBJECTS
		#if defined _YSI_SETUP_MASTER
			if (YSI_g_sIsMaster)
			{
		#endif
				if (Object_IsValid(object))
				{
					Bit_SetAll(YSI_g_sObjects[object][E_OBJECT_PLAYERS], 1, PLAYER_BIT_ARRAY);
				}
		#if defined _YSI_SETUP_MASTER
			}
			else
			{
				CallRemoteFunction("Object_Remote", "iii", object, 0, E_OBJECT_REMOTE_ALLPA);
			}
		#endif
	#else
		#pragma unused object
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	Object_RemoveFromAllPlayers
Params:
	object - Object to remove.
Return:
	-
Notes:
	Makes an object invisible to all players.
-*----------------------------------------------------------------------------*/

stock Object_RemoveFromAllPlayers(object)
{
	#if !defined NO_PERSONAL_OBJECTS
		#if defined _YSI_SETUP_MASTER
			if (YSI_g_sIsMaster)
			{
		#endif
				if (Object_IsValid(object))
				{
					Bit_SetAll(YSI_g_sObjects[object][E_OBJECT_PLAYERS], 0, PLAYER_BIT_ARRAY);
				}
		#if defined _YSI_SETUP_MASTER
			}
			else
			{
				CallRemoteFunction("Object_Remote", "iii", object, 0, E_OBJECT_REMOTE_ALLPR);
			}
		#endif
	#else
		#pragma unused object
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	Object_GetPos
Params:
	objectid - Object to get position of.
	&Float:x - X return.
	&Float:y - Y return.
	&Float:z - Z return.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

static stock Object_GetPos(objectid, &Float:x, &Float:y, &Float:z)
{
	new
		playerid = Object_GetAttach(YSI_g_sObjects[objectid][E_OBJECT_MODEL]);
	if (playerid != NO_ATTACH_PLAYER && IsPlayerConnected(playerid))
	{
		GetPlayerPos(playerid, x, y, z);
	}
	#if !defined NO_OBJECT_ATTACH
		else if ((playerid = YSI_g_sObjects[objectid][E_OBJECT_PARENT]) != NO_OBJECT)
		{
			Object_GetPos(playerid, x, y, z);
		}
	#endif
	#pragma tabsize 0
	else
	#pragma tabsize 4
	{
		x = YSI_g_sObjects[objectid][E_OBJECT_X];
		y = YSI_g_sObjects[objectid][E_OBJECT_Y];
		z = YSI_g_sObjects[objectid][E_OBJECT_Z];
		return;
	}
	x += YSI_g_sObjects[objectid][E_OBJECT_X];
	y += YSI_g_sObjects[objectid][E_OBJECT_Y];
	z += YSI_g_sObjects[objectid][E_OBJECT_Z];
}

/*----------------------------------------------------------------------------*-
Function:
	GetDynamicObjectPos
Params:
	objectid - Object to get position of.
	&Float:x - X return.
	&Float:y - Y return.
	&Float:z - Z return.
Return:
	-
Notes:
	API wrapper for Object_GetPos.
-*----------------------------------------------------------------------------*/

stock GetDynamicObjectPos(objectid, &Float:x, &Float:y, &Float:z)
{
	#if defined _YSI_SETUP_MASTER
		if (YSI_g_sIsMaster)
		{
	#endif
			if (!Object_IsValid(objectid)) return 0;
			Object_GetPos(objectid, x, y, z);
	#if defined _YSI_SETUP_MASTER
		}
		else
		{
			CallRemoteFunction("Object_Remote", "iii", objectid, 0, E_OBJECT_REMOTE_GETPOS);
			x = Float:getproperty(0, "YSIReq");
			y = Float:getproperty(0, "YSIReq2");
			z = Float:getproperty(0, "YSIReq3");
			deleteproperty(0, "YSIReq2");
			deleteproperty(0, "YSIReq3");
		}
	#endif
	return 1;
}

/*----------------------------------------------------------------------------*-
Function:
	Object_HasPlayer
Params:
	objectid - Object to check.
	playerid - Player to check.
	worldid - World to check.
Return:
	Whether the object is visible to that player in that world.
Notes:
	This is a variable function.  Depending on the compile time settings it may
	or may not use all the parameters (it may use none).
-*----------------------------------------------------------------------------*/

#if !defined NO_PERSONAL_OBJECTS
	#if OBJECT_WORLDS > 0
		#define Object_HasPlayer(%1,%2,%3) \
			(Bit_Get(YSI_g_sObjects[(%1)][E_OBJECT_WORLDS], (%3)) && Bit_Get(YSI_g_sObjects[(%1)][E_OBJECT_PLAYERS], (%2)))
	#else
		#define Object_HasPlayer(%1,%2,%3) \
			(Bit_Get(YSI_g_sObjects[(%1)][E_OBJECT_PLAYERS], (%2)))
	#endif
#else
	#if OBJECT_WORLDS > 0
		#define Object_HasPlayer(%1,%2,%3) \
			(Bit_Get(YSI_g_sObjects[(%1)][E_OBJECT_WORLDS], (%3)))
	#else
		#define Object_HasPlayer(%1,%2,%3) \
			(TRUE)
	#endif
#endif

/*----------------------------------------------------------------------------*-
Function:
	IsValidDynamicObject
Params:
	objectid - Object to check.
Return:
	Object_IsValid.
Notes:
	-
-*----------------------------------------------------------------------------*/

stock IsValidDynamicObject(objectid)
{
	#if defined _YSI_SETUP_MASTER
		if (YSI_g_sIsMaster)
		{
	#endif
			return Object_IsValid(objectid);
	#if defined _YSI_SETUP_MASTER
		}
		else
		{
			CallRemoteFunction("Object_Remote", "iii", objectid, 0, E_OBJECT_REMOTE_ISVALID);
			return getproperty(0, "YSIReq");
		}
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	AttachDynamicObjectToPlayer
Params:
	objectid - Object to attach.
	playerid - Player to attach to.
	Float:X - X offset.
	Float:Y - Y offset.
	Float:Z - Z offset.
	Float:RX - X rotation.
	Float:RY - Y rotation.
	Float:RZ - Z rotation.
	Float:S - Speed.
Return:
	-
Notes:
	Updated for children.
-*----------------------------------------------------------------------------*/

stock AttachDynamicObjectToPlayer(objectid, playerid, Float:X, Float:Y, Float:Z, Float:RX, Float:RY, Float:RZ)
{
	#if !defined NO_OBJECTS_MOVE
		#if defined _YSI_SETUP_MASTER
			if (YSI_g_sIsMaster)
			{
		#endif
				if (Object_IsValid(objectid) && Object_IsAttached(YSI_g_sObjects[objectid][E_OBJECT_MODEL]))
				{
					return Object_AttachToPlayer(objectid, playerid, X, Y, Z, RX, RY, RZ);
				}
		#if defined _YSI_SETUP_MASTER
			}
			else
			{
				CallRemoteFunction("Object_AttachRemote", "iiffffff", objectid, playerid, X, Y, Z, RX, RY, RZ);
				return getproperty(0, "YSIReq");
			}
		#endif
	#else
		#pragma unused objectid, X, Y, Z, S
	#endif
	return 0;
}

#if !defined NO_OBJECTS_MOVE

	#if defined _YSI_SETUP_MASTER
		/*----------------------------------------------------------------------------*-
		Function:
			Object_AttachRemote
		Params:
			objectid - Object to attach.
			playerid - Player to attach to.
			Float:X - X offset.
			Float:Y - Y offset.
			Float:Z - Z offset.
			Float:RX - X rotation.
			Float:RY - Y rotation.
			Float:RZ - Z rotation.
			Float:S - Speed.
		Return:
			-
		Notes:
			Remote call for AttachDynamicObjectToPlayer.
		-*----------------------------------------------------------------------------*/
		
		public Object_AttachRemote(objectid, playerid, Float:X, Float:Y, Float:Z, Float:RX, Float:RY, Float:RZ)
		{
			if (!YSI_g_sIsMaster) return 0;
			setproperty(0, "YSIReq", 0);
			if (Object_IsValid(objectid) && Object_IsAttached(YSI_g_sObjects[objectid][E_OBJECT_MODEL]))
			{
				setproperty(0, "YSIReq", Object_AttachToPlayer(objectid, playerid, X, Y, Z, RX, RY, RZ));
				return 1;
			}
			return 0;
		}
	#endif

	/*----------------------------------------------------------------------------*-
	Function:
		Object_AttachToPlayer
	Params:
		objectid - Object to attach.
		playerid - Player to attach to.
		Float:X - X offset.
		Float:Y - Y offset.
		Float:Z - Z offset.
		Float:RX - X rotation.
		Float:RY - Y rotation.
		Float:RZ - Z rotation.
		Float:S - Speed.
	Return:
		-
	Notes:
		Recursive call for AttachDynamicObjectToPlayer.
	-*----------------------------------------------------------------------------*/

	static stock Object_AttachToPlayer(objectid, playerid, Float:X, Float:Y, Float:Z, Float:RX, Float:RY, Float:RZ)
	{
		YSI_g_sObjects[objectid][E_OBJECT_MODEL] |= e_OBJ_FLAG_ATTACHED;
		YSI_g_sObjects[objectid][E_OBJECT_X] = X;
		YSI_g_sObjects[objectid][E_OBJECT_Y] = Y;
		YSI_g_sObjects[objectid][E_OBJECT_Z] = Z;
		YSI_g_sObjects[objectid][E_OBJECT_RX] = RX;
		YSI_g_sObjects[objectid][E_OBJECT_RY] = RY;
		YSI_g_sObjects[objectid][E_OBJECT_RZ] = RZ;
		Object_RemoveFromSector(YSI_g_sObjects[objectid][E_OBJECT_SECTOR], objectid);
		Object_AddToMovingList(objectid);
		YSI_g_sObjects[objectid][E_OBJECT_MODEL] = (YSI_g_sObjects[objectid][E_OBJECT_MODEL] & ~e_OBJ_FLAG_ATTACH) | Object_SetAttach(playerid);
		Object_AddToUpdate(objectid);
		#if !defined NO_OBJECT_ATTACH
			new
				child = YSI_g_sObjects[objectid][E_OBJECT_CHILDREN];
			while (child != NO_OBJECT)
			{
				Object_AttachToPlayer(child, playerid, X + YSI_g_sObjects[child][E_OBJECT_X], Y + YSI_g_sObjects[child][E_OBJECT_Y], Z + YSI_g_sObjects[child][E_OBJECT_Z], RX, RY, RZ);
				child = YSI_g_sObjects[child][E_OBJECT_SIBLINGS];
			}
		#endif
		return 1;
	}
#endif

/*----------------------------------------------------------------------------*-
Function:
	DetachDynamicObjectFromPlayer
Params:
	objectid - Object to detach.
Return:
	-
Notes:
	Detaches an object from a player.
-*----------------------------------------------------------------------------*/

stock DetachDynamicObjectFromPlayer(objectid)
{
	#if !defined NO_OBJECTS_MOVE
		#if defined _YSI_SETUP_MASTER
			if (YSI_g_sIsMaster)
			{
		#endif
				if (!Object_IsValid(objectid)) return;
				new
					playerid = Object_GetAttach(YSI_g_sObjects[objectid][E_OBJECT_MODEL]);
				if (playerid != NO_ATTACH_PLAYER)
				{
					Object_RemoveFromSector(OBJECT_NO_SECTOR, objectid);
					new
						Float:x,
						Float:y,
						Float:z;
					GetPlayerPos(playerid, x, y, z);
					new
						Float:nx = YSI_g_sObjects[objectid][E_OBJECT_X],
						Float:ny = YSI_g_sObjects[objectid][E_OBJECT_Y],
						Float:nz = YSI_g_sObjects[objectid][E_OBJECT_Z];
					Object_SetPos(objectid, x + nx, y + ny, z + nz);
					#if !defined NO_OBJECT_ATTACH
						Object_UpdateAttach(YSI_g_sObjects[objectid][E_OBJECT_CHILDREN], nx, ny, nz, x + nx, y + ny, z + nz, false);
					#endif
					YSI_g_sObjects[objectid][E_OBJECT_MODEL] |= e_OBJ_FLAG_ATTACHED | e_OBJ_FLAG_ATTACH | e_OBJ_FLAG_RECREATED;
					Object_AddToUpdate(objectid);
				}
				return;
		#if defined _YSI_SETUP_MASTER
			}
			else
			{
				CallRemoteFunction("Object_Remote", "iii", objectid, 0, E_OBJECT_REMOTE_DETATCH);
			}
		#endif
	#else
		#pragma unused objectid
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	Object_UpdateAttach
Params:
	child - Start of children list to positionally update.
	Float:x - x offset of parent.
	Float:y - y offset of parent.
	Float:z - z offset of parent.
	Float:rx - Real x location.
	Float:ry - Real y location.
	Float:rz - Real z location.
	moved - Wether the object was previously moving or attached.
Return:
	-
Notes:
	Restores the object sectors and offsets from parents based on positions
	relative to other items (origin or a player).
-*----------------------------------------------------------------------------*/

#if !defined NO_OBJECT_ATTACH
static stock Object_UpdateAttach(child, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, moving = true)
{
	while (child != NO_OBJECT)
	{
		new
			Float:nx = YSI_g_sObjects[child][E_OBJECT_X],
			Float:ny = YSI_g_sObjects[child][E_OBJECT_Y],
			Float:nz = YSI_g_sObjects[child][E_OBJECT_Z],
			Float:mx = nx - x,
			Float:my = ny - y,
			Float:mz = nz - z;
		Object_UpdateAttach(YSI_g_sObjects[child][E_OBJECT_CHILDREN], nx, ny, nz, rx + mx, ry + my, rz + mz);
		YSI_g_sObjects[child][E_OBJECT_X] = mx;
		YSI_g_sObjects[child][E_OBJECT_Y] = my;
		YSI_g_sObjects[child][E_OBJECT_Z] = mz;
		Object_RemoveFromSector(OBJECT_NO_SECTOR, child);
		Object_AddToSector(Object_FindSector(rx + mx, ry + my, rz + mz), child, YSI_g_sObjects[child][E_OBJECT_VIEW]);
		child = YSI_g_sObjects[child][E_OBJECT_SIBLINGS];
		if (moving)
		{
			YSI_g_sObjects[child][E_OBJECT_MODEL] = (YSI_g_sObjects[child][E_OBJECT_MODEL] & ~(e_OBJ_FLAG_MOVED)) | e_OBJ_FLAG_RECREATED;
		}
		else
		{
			YSI_g_sObjects[child][E_OBJECT_MODEL] |= e_OBJ_FLAG_ATTACHED | e_OBJ_FLAG_ATTACH | e_OBJ_FLAG_RECREATED;
		}
	}
}
#endif

/*----------------------------------------------------------------------------*-
Function:
	MoveDynamicObject
Params:
	objectid - Object to move.
	Float:X - X position of target.
	Float:Y - Y position of target.
	Float:Z - Z position of target.
	Float:S - Speed.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

stock MoveDynamicObject(objectid, Float:X, Float:Y, Float:Z, Float:S)
{
	#if !defined NO_OBJECTS_MOVE
		#if defined _YSI_SETUP_MASTER
			if (YSI_g_sIsMaster)
			{
		#endif
				if (Object_IsValid(objectid))
				{
					Object_Move(objectid, X, Y, Z, S);
					Object_AddToUpdate(objectid);
					return 1;
				}
		#if defined _YSI_SETUP_MASTER
			}
			else
			{
				CallRemoteFunction("Object_CoOrdRemote", "iiffff", objectid, E_OBJECT_REMOTE_MOVETO, X, Y, Z, S);
				return getproperty(0, "YSIReq");
			}
		#endif
	#else
		#pragma unused objectid, X, Y, Z, S
	#endif
	return 0;
}

#if !defined NO_OBJECTS_MOVE
/*----------------------------------------------------------------------------*-
Function:
	Object_Move
Params:
	objectid - Object to move.
	Float:X - X position of target.
	Float:Y - Y position of target.
	Float:Z - Z position of target.
	Float:S - Speed.
Return:
	-
Notes:
	Recursive function for MoveDynamicObject to move children.
-*----------------------------------------------------------------------------*/

static stock Object_Move(objectid, Float:X, Float:Y, Float:Z, Float:S)
{
	if (xor:(YSI_g_sObjects[objectid][E_OBJECT_MODEL] & e_OBJ_FLAG_MOVED1) == xor:(YSI_g_sObjects[objectid][E_OBJECT_MODEL] & e_OBJ_FLAG_MOVED2))
	{
		YSI_g_sObjects[objectid][E_OBJECT_MODEL] ^= e_OBJ_FLAG_MOVED;
	}
	else
	{
		YSI_g_sObjects[objectid][E_OBJECT_MODEL] = (YSI_g_sObjects[objectid][E_OBJECT_MODEL] & ~e_OBJ_FLAG_MOVED) | e_OBJ_FLAG_MOVED1;
	}
	YSI_g_sObjects[objectid][E_OBJECT_MX] = X;
	YSI_g_sObjects[objectid][E_OBJECT_MY] = Y;
	YSI_g_sObjects[objectid][E_OBJECT_MZ] = Z;
	YSI_g_sObjects[objectid][E_OBJECT_MS] = S;
	Object_RemoveFromSector(YSI_g_sObjects[objectid][E_OBJECT_SECTOR], objectid);
	Object_AddToMovingList(objectid);
	#if !defined NO_OBJECT_ATTACH
		new
			child = YSI_g_sObjects[objectid][E_OBJECT_CHILDREN];
		while (child != NO_OBJECT)
		{
			Object_Move(child, X + YSI_g_sObjects[child][E_OBJECT_X], Y + YSI_g_sObjects[child][E_OBJECT_Y], Z + YSI_g_sObjects[child][E_OBJECT_Z], S);
			child = YSI_g_sObjects[child][E_OBJECT_SIBLINGS];
		}
	#endif
}
#endif

/*----------------------------------------------------------------------------*-
Function:
	AttachObjectToObject
Params:
	attachobject - Object to attach.
	toobject - Object to attach to.
Return:
	-
Notes:
	Variables named to hopefully avoid confusion.  Now checks the parent is not
	a descendent of the child to avoid infinate loops.
-*----------------------------------------------------------------------------*/

stock AttachObjectToObject(attachobject, toobject)
{
	#if !defined NO_OBJECT_ATTACH
		#if defined _YSI_SETUP_MASTER
			if (YSI_g_sIsMaster)
			{
		#endif
				if (Object_IsValid(attachobject) && Object_IsValid(toobject))
				{
					if (Object_CheckDescendant(toobject, attachobject)) return 0;
					new
						Float:px,
						Float:py,
						Float:pz,
						Float:cx,
						Float:cy,
						Float:cz;
					Object_GetPos(toobject, px, py, pz);
					Object_GetPos(attachobject, cx, cy, cz);
					new
						parent = YSI_g_sObjects[attachobject][E_OBJECT_PARENT];
					if (parent != NO_OBJECT) Object_RemoveFromParent(attachobject, parent);
					Object_AddToParent(attachobject, toobject);
					YSI_g_sObjects[attachobject][E_OBJECT_X] = cx - px;
					YSI_g_sObjects[attachobject][E_OBJECT_Y] = cy - py;
					YSI_g_sObjects[attachobject][E_OBJECT_Z] = cz - pz;
					return 1;
				}
		#if defined _YSI_SETUP_MASTER
			}
			else
			{
				CallRemoteFunction("Object_Remote", "iii", attachobject, toobject, E_OBJECT_REMOTE_ATTACHOO);
				return getproperty(0, "YSIReq");
			}
		#endif
	#else
		#pragma unused attachobject, toobject
	#endif
	return 0;
}

/*----------------------------------------------------------------------------*-
Function:
	Object_IsDesendant
Params:
	objectid - Object to check.
	ancestor - Object to check family tree of for objectid.
Return:
	-
Notes:
	Checks if objectid is a descendant of the ancestor object.
-*----------------------------------------------------------------------------*/

stock Object_IsDescendant(objectid, ancestor)
{
	#if !defined NO_OBJECT_ATTACH
		#if defined _YSI_SETUP_MASTER
			if (YSI_g_sIsMaster)
			{
		#endif
				if (Object_IsValid(objectid) && Object_IsValid(ancestor))
				{
					return Object_CheckDescendant(objectid, ancestor);
				}
		#if defined _YSI_SETUP_MASTER
			}
			else
			{
				CallRemoteFunction("Object_Remote", "iii", objectid, ancestor, E_OBJECT_REMOTE_CHECKDESC);
				return getproperty(0, "YSIReq");
			}
		#endif
	#else
		#pragma unused objectid, ancestor
	#endif
	return 0;
}

/*----------------------------------------------------------------------------*-
Function:
	Object_CheckDesendant
Params:
	objectid - Object to check.
	ancestor - Object to check family tree of for objectid.
Return:
	-
Notes:
	Recursive call for Object_IsDescendant.
-*----------------------------------------------------------------------------*/

static stock Object_CheckDescendant(objectid, ancestor)
{
	if (objectid == ancestor) return 1;
	new
		child = YSI_g_sObjects[ancestor][E_OBJECT_CHILDREN];
	while (child != NO_OBJECT)
	{
		if (Object_CheckDescendant(objectid, child)) return 1;
		child = YSI_g_sObjects[child][E_OBJECT_SIBLINGS];
	}
	return 0;
}

/*----------------------------------------------------------------------------*-
Function:
	RemoveObjectFromParent
Params:
	objectid - Object to remove from it's parent.
Return:
	-
Notes:
	-
-*----------------------------------------------------------------------------*/

stock RemoveObjectFromParent(objectid)
{
	#if !defined NO_OBJECT_ATTACH
		#if defined _YSI_SETUP_MASTER
			if (YSI_g_sIsMaster)
			{
		#endif
				if (Object_IsValid(objectid))
				{
					new
						parent = YSI_g_sObjects[objectid][E_OBJECT_PARENT];
					if (parent != NO_OBJECT)
					{
						new
							Float:x,
							Float:y,
							Float:z;
						Object_GetPos(objectid, x, y, z);
						Object_RemoveFromParent(objectid, parent);
						YSI_g_sObjects[objectid][E_OBJECT_X] = x;
						YSI_g_sObjects[objectid][E_OBJECT_Y] = y;
						YSI_g_sObjects[objectid][E_OBJECT_Z] = z;
					}
				}
		#if defined _YSI_SETUP_MASTER
			}
			else
			{
				CallRemoteFunction("Object_Remote", "iii", objectid, 0, E_OBJECT_REMOTE_REMOO);
			}
		#endif
	#else
		#pragma unused objectid
	#endif
}

#if !defined NO_OBJECT_ATTACH

/*----------------------------------------------------------------------------*-
Function:
	Object_RemoveFromParent
Params:
	objectid - Object to remove from an object.
	parent - Object to remove from.
Return:
	-
Notes:
	Removes an object from another object's children list.  Has parent passed
	as existance is checked in calling function so is already retrieved.
-*----------------------------------------------------------------------------*/

static stock Object_RemoveFromParent(objectid, parent)
{
	new
		children = YSI_g_sObjects[parent][E_OBJECT_CHILDREN],
		next;
	if (children == objectid)
	{
		YSI_g_sObjects[parent][E_OBJECT_CHILDREN] = YSI_g_sObjects[objectid][E_OBJECT_SIBLINGS];
	}
	else
	{
		while ((next = YSI_g_sObjects[children][E_OBJECT_SIBLINGS]) != objectid) children = next;
		YSI_g_sObjects[children][E_OBJECT_SIBLINGS] = YSI_g_sObjects[objectid][E_OBJECT_SIBLINGS];
	}
	YSI_g_sObjects[objectid][E_OBJECT_PARENT] = NO_OBJECT;
	YSI_g_sObjects[objectid][E_OBJECT_SIBLINGS] = NO_OBJECT;
}

/*----------------------------------------------------------------------------*-
Function:
	Object_AddToParent
Params:
	objectid - Object to attach.
	parentid - Object to attach to.
Return:
	-
Notes:
	Adds an object to another objects child list.
-*----------------------------------------------------------------------------*/

static stock Object_AddToParent(objectid, parentid)
{
	if (YSI_g_sObjects[objectid][E_OBJECT_PARENT] == NO_OBJECT)
	{
		YSI_g_sObjects[objectid][E_OBJECT_SIBLINGS] = YSI_g_sObjects[parentid][E_OBJECT_CHILDREN];
		YSI_g_sObjects[objectid][E_OBJECT_PARENT] = parentid;
		YSI_g_sObjects[parentid][E_OBJECT_CHILDREN] = objectid;
	}
}

#endif

/*----------------------------------------------------------------------------*-
Function:
	StopDynamicObject
Params:
	objectid - Object to stop.
Return:
	-
Notes:
	Stops an object and reassigns it's sector.
-*----------------------------------------------------------------------------*/

stock StopDynamicObject(objectid)
{
	#if defined _YSI_SETUP_MASTER
		if (YSI_g_sIsMaster)
		{
	#endif
			if (Object_IsValid(objectid))
			{
				Object_RemoveFromSector(OBJECT_NO_SECTOR, objectid);
				new
					Float:x,
					Float:y,
					Float:z;
				Object_GetPos(objectid, x, y, z);
				Object_AddToSector(Object_FindSector(x, y, z), objectid, YSI_g_sObjects[objectid][E_OBJECT_VIEW]);
				YSI_g_sObjects[objectid][E_OBJECT_MODEL] = (YSI_g_sObjects[objectid][E_OBJECT_MODEL] & ~(e_OBJ_FLAG_MOVED)) | e_OBJ_FLAG_RECREATED;
				Object_AddToUpdate(objectid);
				#if !defined NO_OBJECT_ATTACH
					Object_UpdateAttach(YSI_g_sObjects[objectid][E_OBJECT_CHILDREN], x, y, z, x, y, z);
				#endif
			}
	#if defined _YSI_SETUP_MASTER
		}
		else
		{
			CallRemoteFunction("Object_Remote", "iii", objectid, 0, E_OBJECT_REMOTE_STOP);
		}
	#endif
}

#if !defined NO_OBJECTS_MOVE

/*----------------------------------------------------------------------------*-
Function:
	Object_Update
Params:
	objectid - Object to process.
	Float:elapsedTime - Time since last update in seconds.
Return:
	-
Notes:
	Updates a moving object's position in our internal memory based on speed
	and time (d = s * t)
-*----------------------------------------------------------------------------*/

static Object_Update(objectid, Float:elapsedTime)
{
	new
		Float:x = YSI_g_sObjects[objectid][E_OBJECT_X],
		Float:y = YSI_g_sObjects[objectid][E_OBJECT_Y],
		Float:z = YSI_g_sObjects[objectid][E_OBJECT_Z],
		Float:mx = YSI_g_sObjects[objectid][E_OBJECT_MX],
		Float:my = YSI_g_sObjects[objectid][E_OBJECT_MY],
		Float:mz = YSI_g_sObjects[objectid][E_OBJECT_MZ],
		Float:distance = elapsedTime * YSI_g_sObjects[objectid][E_OBJECT_MS];
	x -= mx;
	y -= my;
	z -= mz;
	new
		Float:remaining = floatsqroot((x * x) + (y * y) + (z * z));
	if (distance >= remaining)
	{
		YSI_g_sObjects[objectid][E_OBJECT_X] = mx;
		YSI_g_sObjects[objectid][E_OBJECT_Y] = my;
		YSI_g_sObjects[objectid][E_OBJECT_Z] = mz;
		new
			e_OBJ_FLAG:oldmove = YSI_g_sObjects[objectid][E_OBJECT_MODEL] & e_OBJ_FLAG_MOVED;
		if (!Object_GateMoved(objectid)) CallRemoteFunction("OnDynamicObjectMoved", "i", objectid);
		if (oldmove == YSI_g_sObjects[objectid][E_OBJECT_MODEL] & e_OBJ_FLAG_MOVED)
		{
			StopDynamicObject(objectid);
		}
		return 1;
	}
	else
	{
		remaining /= distance;
		YSI_g_sObjects[objectid][E_OBJECT_X] += (0.0 - x) / remaining;
		YSI_g_sObjects[objectid][E_OBJECT_Y] += (0.0 - y) / remaining;
		YSI_g_sObjects[objectid][E_OBJECT_Z] += (0.0 - z) / remaining;
	}
	return 0;
}

#endif

/*----------------------------------------------------------------------------*-
Function:
	Object_Loop
Params:
	-
Return:
	-
Notes:
	Checks what objects are in the player's range repeatedly to stream them
	as required.  Only checks objects near the player, based on sectors, and
	moving objects which are handled as their own 'sector'.  If the player is
	near the edge of the grid (+/-OBJECT_BOUNDS x/y) OOB objects are also checked, only
	one sector is used for all those regardless of location.  Moving objects
	and already visible objects are assumed higher priority.
	
	Now orders objects so only the closest are displayed.
	
	Fixed moving objects.
-*----------------------------------------------------------------------------*/

public Object_Loop()
{
	#if defined _YSI_SETUP_MASTER
		if (!YSI_g_sIsMaster) return;
	#endif
	#if !defined NO_OBJECTS_MOVE
		static
			Float:s_fTime;
		new
			Float:tick = float(GetTickCount()) / 1000.0;
		if (YSI_g_sMovingObjects != NO_OBJECT)
		{
			new
				Float:fTime = tick - s_fTime,
				objectid = YSI_g_sMovingObjects;
			do
			{
				new
					next = YSI_g_sObjects[objectid][E_OBJECT_NEXT];
				if (YSI_g_sObjects[objectid][E_OBJECT_MODEL] & e_OBJ_FLAG_MOVED) Object_Update(objectid, fTime);
				if (objectid == next) break;
				objectid = next;
			}
			while (objectid != NO_OBJECT);
		}
		s_fTime = tick;
	#endif
	foreach (Player, playerid)
	{
		static
			sectors[MAX_PLAYERS][OBJECT_VIEW_SECTORS][E_OSEC_ITTER],
			secStart[MAX_PLAYERS] = {-1, ...},
			Bit:objects[OBJECT_BITS],
			sObjList[MAY_OBJECTS][E_OBJECT_ITTER];
		new
			Float:x,
			Float:y,
			Float:z,
			world = GetPlayerVirtualWorld(playerid),
			i,
			j,
			objStart = -1,
			objEnd = -1,
			objCount;
		GetPlayerPos(playerid, x, y, z);
		if (z < 800.0)
		{
			Object_FindSectors(playerid, x, y, sectors[playerid], secStart[playerid]);
			i = secStart[playerid];
			while (i != -1)
			{
				if (objCount >= MAY_OBJECTS && sectors[playerid][i][E_OSEC_ITTER_DIFF] >= sObjList[objEnd][E_OBJECT_ITTER_DISTANCE]) break;
				else
				{
					if ((j = sectors[playerid][i][E_OSEC_ITTER_SECTOR]) == OBJECT_NO_SECTOR) Object_ParseSet(playerid, YSI_g_sOtherSector, x, y, z, world, sObjList, objStart, objEnd, objCount, false);
					else Object_ParseSet(playerid, YSI_g_sObjectSectors[j][E_OBJ_SECTOR_POINTER], x, y, z, world, sObjList, objStart, objEnd, objCount, false);
				}
				i = sectors[playerid][i][E_OSEC_ITTER_NEXT];
			}
		}
		else Object_ParseSet(playerid, YSI_g_sInteriorObjects, x, y, z, world, sObjList, objStart, objEnd, objCount, false);
		#if !defined NO_OBJECTS_MOVE
			Object_ParseSet(playerid, YSI_g_sMovingObjects, x, y, z, world, sObjList, objStart, objEnd, objCount, true);
		#endif
		Object_ParseSet(playerid, YSI_g_sLODObjects, x, y, z, world, sObjList, objStart, objEnd, objCount, false);
		for (j = objStart; j != -1; j = sObjList[j][E_OBJECT_ITTER_NEXT])
		{
			Bit_Let(objects, sObjList[j][E_OBJECT_ITTER_OBJ]);
		}
		new
			object;
		for (i = 0; i < MAY_OBJECTS; i++)
		{
			new
				objectid = i + 1;
			if ((object = YSI_g_sPlayerObjects[playerid][i] & 0xFFFFFF) != (NO_OBJECT & 0xFFFFFF) && IsValidPlayerObject(playerid, objectid))
			{
				if (YSI_g_sSomethingMoved != NO_OBJECT)
				{
					new
						e_OBJ_FLAG:flag = YSI_g_sObjects[object][E_OBJECT_MODEL];
					if (Bit_Get(objects, object) && !(flag & e_OBJ_FLAG_RECREATED))
					{
						#if !defined NO_OBJECTS_MOVE
							if  (flag & e_OBJ_FLAG_ATTACHED)
							{
								AttachPlayerObjectToPlayer(playerid, objectid, Object_GetAttach(object), YSI_g_sObjects[object][E_OBJECT_X], YSI_g_sObjects[object][E_OBJECT_Y], YSI_g_sObjects[object][E_OBJECT_Z], YSI_g_sObjects[object][E_OBJECT_RX], YSI_g_sObjects[object][E_OBJECT_RY], YSI_g_sObjects[object][E_OBJECT_RZ]);
							}
							if (flag & e_OBJ_FLAG_MOVED != e_OBJ_FLAG:YSI_g_sPlayerObjects[playerid][i] & e_OBJ_FLAG_MOVED)
							{
								YSI_g_sPlayerObjects[playerid][i] = (YSI_g_sPlayerObjects[playerid][i] & 0xFFFFFF) | _:(flag & e_OBJ_FLAG_MOVED);
								MovePlayerObject(playerid, objectid, YSI_g_sObjects[object][E_OBJECT_MX], YSI_g_sObjects[object][E_OBJECT_MY], YSI_g_sObjects[object][E_OBJECT_MZ], YSI_g_sObjects[object][E_OBJECT_MS]);
								flag |= e_OBJ_FLAG_JUMPED;
							}
						#endif
						if (flag & e_OBJ_FLAG_JUMPED)
						{
							Object_GetPos(object, x, y, z);
							SetPlayerObjectPos(playerid, objectid, x, y, z);
						}
						if (flag & e_OBJ_FLAG_ROTATED)
						{
							SetPlayerObjectRot(playerid, objectid, YSI_g_sObjects[object][E_OBJECT_RX], YSI_g_sObjects[object][E_OBJECT_RY], YSI_g_sObjects[object][E_OBJECT_RZ]);
						}
						Bit_Set(objects, object, 0, OBJECT_BITS);
					}
					else
					{
						DestroyPlayerObject(playerid, objectid);
						YSI_g_sPlayerObjects[playerid][i] = NO_OBJECT;
					}
				}
				else
				{
					if (Bit_Get(objects, object))
					{
						Bit_Set(objects, object, 0, OBJECT_BITS);
					}
					else
					{
						DestroyPlayerObject(playerid, objectid);
						YSI_g_sPlayerObjects[playerid][i] = NO_OBJECT;
					}
				}
			}
		}
		for (i = objStart; i != -1; i = sObjList[i][E_OBJECT_ITTER_NEXT])
		{
			new
				objSet = sObjList[i][E_OBJECT_ITTER_OBJ],
				e_OBJ_FLAG:flag = YSI_g_sObjects[objSet][E_OBJECT_MODEL];
			if (Bit_Get(objects, objSet))
			{
				new
					obj = CreatePlayerObject(playerid, flag & e_OBJ_FLAG_MODEL, sObjList[i][E_OBJECT_ITTER_X], sObjList[i][E_OBJECT_ITTER_Y], sObjList[i][E_OBJECT_ITTER_Z], YSI_g_sObjects[objSet][E_OBJECT_RX], YSI_g_sObjects[objSet][E_OBJECT_RY], YSI_g_sObjects[objSet][E_OBJECT_RZ]);
				if (obj != 0xFF)
				{
					YSI_g_sPlayerObjects[playerid][obj - 1] = objSet;
					Bit_Set(objects, objSet, 0, OBJECT_BITS);
					#if !defined NO_OBJECTS_MOVE
						if  (flag & e_OBJ_FLAG_MOVED)
						{
							MovePlayerObject(playerid, obj, YSI_g_sObjects[objSet][E_OBJECT_MX], YSI_g_sObjects[objSet][E_OBJECT_MY], YSI_g_sObjects[objSet][E_OBJECT_MZ], YSI_g_sObjects[objSet][E_OBJECT_MS]);
							YSI_g_sPlayerObjects[playerid][obj - 1] |= _:(flag & e_OBJ_FLAG_MOVED);
						}
						if  (flag & e_OBJ_FLAG_ATTACHED)
						{
							AttachPlayerObjectToPlayer(playerid, obj, Object_GetAttach(objSet), YSI_g_sObjects[objSet][E_OBJECT_X], YSI_g_sObjects[objSet][E_OBJECT_Y], YSI_g_sObjects[objSet][E_OBJECT_Z], YSI_g_sObjects[objSet][E_OBJECT_RX], YSI_g_sObjects[objSet][E_OBJECT_RY], YSI_g_sObjects[objSet][E_OBJECT_RZ]);
						}
					#endif
				}
			}
		}
	}
	if (YSI_g_sSomethingMoved != NO_OBJECT)
	{
		for (new objectid = YSI_g_sSomethingMoved; objectid != NO_OBJECT; objectid = YSI_g_sObjects[objectid][E_OBJECT_UPDATES])
		{
			YSI_g_sObjects[objectid][E_OBJECT_MODEL] &= ~(e_OBJ_FLAG_ATTACHED | e_OBJ_FLAG_JUMPED | e_OBJ_FLAG_ROTATED | e_OBJ_FLAG_RECREATED);
			YSI_g_sObjects[objectid][E_OBJECT_UPDATES] = NO_OBJECT;
		}
		YSI_g_sSomethingMoved = NO_OBJECT;
	}
}

/*----------------------------------------------------------------------------*-
Function:
	Object_ParseSet
Params:
	playerid - Player to check for.
	objSet - Pointer to first object in the list.
	Float:x - Player's x position.
	Float:y - Player's y position.
	Float:z - Player's z position.
	world - Player's world.
	objList[][E_OBJECT_ITTER] - List of closest objects.
	&objStart - Entrypoint to list.
	&objEnd - Last object in list.
	&objCount - Number of objects in list.
	bool:dynam - Is this the dynamic objSet.
Return:
	-
Notes:
	Itterates through the linked list for one sector of objects and checks
	their real location relative to the player, if in range displays them.
-*----------------------------------------------------------------------------*/

static Object_ParseSet(playerid, objSet, Float:x, Float:y, Float:z, world, objList[][E_OBJECT_ITTER], &objStart, &objEnd, &objCount, bool:dynam)
{
	if (objSet == NO_OBJECT) return;
	new
		#if !defined NO_OBJECTS_MOVE && defined NO_OBJECT_ATTACH
			attach,
		#endif
		start = objSet,
		Float:px,
		Float:py,
		Float:pz,
		Float:diff;
	do
	{
		new
			e_OBJ_FLAG:flag = YSI_g_sObjects[objSet][E_OBJECT_MODEL];
		if (flag & e_OBJ_FLAG_ACTIVE)
		{
			if (Object_HasPlayer(objSet, playerid, world))
			{
				#if !defined NO_OBJECT_ATTACH
					Object_GetPos(objSet, px, py, pz);
					#pragma unused dynam
				#else
					#if !defined NO_OBJECTS_MOVE
						if (!dynam || (attach = Object_GetAttach(YSI_g_sObjects[objSet][E_OBJECT_MODEL])) == NO_ATTACH_PLAYER || !IsPlayerConnected(attach))
						{
					#endif
							px = YSI_g_sObjects[objSet][E_OBJECT_X];
							py = YSI_g_sObjects[objSet][E_OBJECT_Y];
							pz = YSI_g_sObjects[objSet][E_OBJECT_Z];
					#if !defined NO_OBJECTS_MOVE
						}
						else
						{
							GetPlayerPos(attach, px, py, pz);
							px += YSI_g_sObjects[objSet][E_OBJECT_X];
							py += YSI_g_sObjects[objSet][E_OBJECT_Y];
							pz += YSI_g_sObjects[objSet][E_OBJECT_Z];
						}
					#else
						#pragma unused dynam
					#endif
				#endif
				new
					Float:ox = px - x,
					Float:oy = py - y,
					Float:oz = pz - z;
				diff = ((ox * ox) + (oy * oy) + (oz * oz)) / YSI_g_sObjects[objSet][E_OBJECT_VIEW];
				if (diff < 1.0)
				{
					if (objStart == -1)
					{
						objList[0][E_OBJECT_ITTER_NEXT] = -1;
						objList[0][E_OBJECT_ITTER_LAST] = -1;
						objList[0][E_OBJECT_ITTER_OBJ] = objSet;
						objList[0][E_OBJECT_ITTER_DISTANCE] = diff;
						objList[0][E_OBJECT_ITTER_X] = px;
						objList[0][E_OBJECT_ITTER_Y] = py;
						objList[0][E_OBJECT_ITTER_Z] = pz;
						objStart = 0;
						objEnd = 0;
						objCount = 1;
					}
					else if (objCount < MAY_OBJECTS)
					{
						objList[objCount][E_OBJECT_ITTER_OBJ] = objSet;
						objList[objCount][E_OBJECT_ITTER_DISTANCE] = diff;
						objList[objCount][E_OBJECT_ITTER_X] = px;
						objList[objCount][E_OBJECT_ITTER_Y] = py;
						objList[objCount][E_OBJECT_ITTER_Z] = pz;
						if (objList[objEnd][E_OBJECT_ITTER_DISTANCE] < diff)
						{
							objList[objCount][E_OBJECT_ITTER_LAST] = objEnd;
							objList[objCount][E_OBJECT_ITTER_NEXT] = -1;
							objList[objEnd][E_OBJECT_ITTER_NEXT] = objCount;
							objEnd = objCount++;
						}
						else
						{
							new
								i = objStart,
								j = -1;
							while (objList[i][E_OBJECT_ITTER_DISTANCE] < diff) i = objList[(j = i)][E_OBJECT_ITTER_NEXT];
							objList[objCount][E_OBJECT_ITTER_NEXT] = i;
							objList[objCount][E_OBJECT_ITTER_LAST] = j;
							objList[i][E_OBJECT_ITTER_LAST] = objCount;
							if (j == -1) objStart = objCount++;
							else objList[j][E_OBJECT_ITTER_NEXT] = objCount++;
						}
					}
					else if (objList[objEnd][E_OBJECT_ITTER_DISTANCE] > diff)
					{
						new
							i = objStart,
							j = -1,
							newend = objList[objEnd][E_OBJECT_ITTER_LAST];
						while (objList[i][E_OBJECT_ITTER_DISTANCE] < diff) i = objList[(j = i)][E_OBJECT_ITTER_NEXT];
						objList[objEnd][E_OBJECT_ITTER_OBJ] = objSet;
						objList[objEnd][E_OBJECT_ITTER_DISTANCE] = diff;
						objList[objEnd][E_OBJECT_ITTER_X] = px;
						objList[objEnd][E_OBJECT_ITTER_Y] = py;
						objList[objEnd][E_OBJECT_ITTER_Z] = pz;
						if (i != objEnd)
						{
							objList[objEnd][E_OBJECT_ITTER_NEXT] = i;
							objList[objEnd][E_OBJECT_ITTER_LAST] = j;
							objList[i][E_OBJECT_ITTER_LAST] = objEnd;
							if (j == -1) objStart = objEnd;
							else objList[j][E_OBJECT_ITTER_NEXT] = objEnd;
							objEnd = newend;
							objList[newend][E_OBJECT_ITTER_NEXT] = -1;
						}
					}
				}
			}
		}
		objSet = YSI_g_sObjects[objSet][E_OBJECT_NEXT];
	}
	while (objSet != start);
}

/*----------------------------------------------------------------------------*-
Function:
	Object_FindSectors
Params:
	playerid - Player we're finding the sectors for.
	Float:x - X location to check.
	Float:y - Y location to check.
	sectors[OBJECT_VIEW_SECTORS][E_OSEC_ITTER] - Array to store all visible sectors.
	&secStart - Start point to itterator
Return:
	-
Notes:
	Finds all the sectors which encompas points within the sight range of the
	player.  Initial checks are done as a square so some returned sectors may
	not have points within a circular range of the player.
	
	The original version tested if the edges of each sector were visible and
	if not excluded them from the list.  This would have been faster in terms
	of objects checked but slower if there were no objects, which is likely to
	be more frequently the case.  The code also didn't actually work but that's
	a minor point as the theory was there.  This is also alot neater.
	
	Rewritten to not use Object_FindSector on a new area, just calculate the
	area from known initial area.
	
	Now also only returns the zones visible, not the zones theoretically
	visible (still assumes square vision though which the code doesn't use).
-*----------------------------------------------------------------------------*/

static Object_FindSectors(playerid, Float:x, Float:y, sectors[][E_OSEC_ITTER], &secStart)
{
	static
		sLastCheck[MAX_PLAYERS],
		sLX[MAX_PLAYERS] = {cellmin, ...},
		sLY[MAX_PLAYERS] = {cellmax, ...};
	new
		xsector = floatround(((x - OBJECT_BOUNDS_MINX) / YSI_g_sXSectorSize), floatround_floor),
		ysector = floatround(((y - OBJECT_BOUNDS_MINY) / YSI_g_sYSectorSize), floatround_floor);
	if (!sLastCheck[playerid] || sLX[playerid] != xsector || sLY[playerid] != ysector)
	{
		secStart = -1;
		new
			go = 0,
			Float:diff = 10.0,
			xstart = -OBJECT_VIEW_RATIO,
			xend = OBJECT_VIEW_RATIO,
			ystart = -OBJECT_VIEW_RATIO,
			yend = OBJECT_VIEW_RATIO,
			k;
		if (xsector < -OBJECT_VIEW_RATIO)
		{
			xstart = cellmax;
			go = 1;
			diff = 0.0;
		}
		else if (xsector < OBJECT_VIEW_RATIO)
		{
			xstart = 0 - xsector;
			go = 1;
			new
				Float:nd = ((x - OBJECT_BOUNDS_MINX) * (x - OBJECT_BOUNDS_MINX)) / (OBJECT_MAX_VIEW_DISTANCE * OBJECT_MAX_VIEW_DISTANCE);
			if (nd < diff) diff = nd;
		}
		if (ysector < -OBJECT_VIEW_RATIO)
		{
			ystart = cellmax;
			go = 1;
			diff = 0.0;
		}
		else if (ysector < OBJECT_VIEW_RATIO)
		{
			ystart = 0 - ysector;
			go = 1;
			new
				Float:nd = ((y - OBJECT_BOUNDS_MINY) * (y - OBJECT_BOUNDS_MINY)) / (OBJECT_MAX_VIEW_DISTANCE * OBJECT_MAX_VIEW_DISTANCE);
			if (nd < diff) diff = nd;
		}
		if (xsector >= OBJECT_SECTOR_X_EDGE + OBJECT_VIEW_RATIO)
		{
			xend = cellmin;
			go = 1;
			diff = 0.0;
		}
		else if (xsector >= OBJECT_SECTOR_X_EDGE - OBJECT_VIEW_RATIO)
		{
			xend = OBJECT_SECTOR_X_EDGE - (xsector + 1);
			if (xsector >= OBJECT_SECTOR_X_EDGE)
			{
				go = 1;
				diff = 0.0;
			}
			else if (go == -1 || go > xend + 1)
			{
				go = 1;
				new
					Float:nd = ((x - OBJECT_BOUNDS_MAXX) * (x - OBJECT_BOUNDS_MAXX)) / (OBJECT_MAX_VIEW_DISTANCE * OBJECT_MAX_VIEW_DISTANCE);
				if (nd < diff) diff = nd;
			}
		}
		if (ysector >= OBJECT_SECTOR_Y_EDGE + OBJECT_VIEW_RATIO)
		{
			yend = cellmin;
			go = 1;
			diff = 0.0;
		}
		else if (ysector >= OBJECT_SECTOR_Y_EDGE - OBJECT_VIEW_RATIO)
		{
			yend = OBJECT_SECTOR_Y_EDGE - (ysector + 1);
			if (ysector >= OBJECT_SECTOR_Y_EDGE)
			{
				go = 1;
				diff = 0.0;
			}
			else if (go == -1 || go > yend + 1)
			{
				go = 1;
				new
					Float:nd = ((y - OBJECT_BOUNDS_MAXY) * (y - OBJECT_BOUNDS_MAXY)) / (OBJECT_MAX_VIEW_DISTANCE * OBJECT_MAX_VIEW_DISTANCE);
				if (nd < diff) diff = nd;
			}
		}
		if (go)
		{
			go = 0;
			sectors[0][E_OSEC_ITTER_SECTOR] = OBJECT_NO_SECTOR;
			sectors[0][E_OSEC_ITTER_DIFF] = diff;
			sectors[0][E_OSEC_ITTER_NEXT] = -1;
			secStart = 0;
			k = 1;
		}
		else secStart = -1;
		for (new i = xstart; i <= xend; i++)
		{
			new
				xsec = xsector + i;
			new
				Float:xsmin = x - YSI_g_sXSectorLocations[xsec + 1],
				Float:xsmax = YSI_g_sXSectorLocations[xsec] - x;
			if (i > 0)
			{
				if (xsmax < OBJECT_MAX_VIEW_DISTANCE) go = 1;
				else break;
			}
			else if (i < 0)
			{
				if (xsmin < OBJECT_MAX_VIEW_DISTANCE) go = 1;
			}
			else go = 1;
			if (go)
			{
				go = 0;
				for (new j = ystart; j <= yend; j++)
				{
					new
						ysec = ysector + j,
						cursec = (xsec * OBJECT_SECTOR_X_EDGE) + ysec;
					diff = 10.0;
					if (i || j)
					{
						new
							Float:ysmin = y - YSI_g_sYSectorLocations[ysec + 1],
							Float:ysmax = YSI_g_sYSectorLocations[ysec] - y;
						if (j > 0)
						{
							if (ysmax < OBJECT_MAX_VIEW_DISTANCE) go = 1;
							else
							{
								yend--;
								break;
							}
						}
						else if (j < 0)
						{
							if (ysmin < OBJECT_MAX_VIEW_DISTANCE) go = 1;
							else ystart++;
						}
						else go = 1;
						if (go)
						{
							go = 0;
							if (!i) diff = (j < 0) ? (ysmin * ysmin) : (ysmax * ysmax);
							else if (!j) diff = (i < 0) ? (xsmin * xsmin) : (xsmax * xsmax);
							else if (i < 0) diff = (j < 0) ? ((ysmin * ysmin) + (xsmin * xsmin)) : ((ysmax * ysmax) + (xsmin * xsmin));
							else if (i > 0) diff = (j < 0) ? ((ysmin * ysmin) + (xsmax * xsmax)) : ((ysmax * ysmax) + (xsmax * xsmax));
							diff /= YSI_g_sObjectSectors[cursec][E_OBJ_SECTOR_MAX_VIEW];
						}
					}
					else diff = 0.0;
					if (diff < 1.0)
					{
						new
							itterCur = secStart,
							itterLast = -1;
						while (itterCur != -1 && sectors[itterCur][E_OSEC_ITTER_DIFF] < diff) itterCur = sectors[(itterLast = itterCur)][E_OSEC_ITTER_NEXT];
						if (itterLast == -1) secStart = k;
						else sectors[itterLast][E_OSEC_ITTER_NEXT] = k;
						sectors[k][E_OSEC_ITTER_NEXT] = itterCur;
						sectors[k][E_OSEC_ITTER_SECTOR] = cursec;
						sectors[k][E_OSEC_ITTER_DIFF] = diff;
						k++;
					}
				}
			}
		}
		sLastCheck[playerid] = SECTOR_CHECK_FREQUENCY;
		sLX[playerid] = xsector;
		sLY[playerid] = ysector;
	}
	sLastCheck[playerid]--;
	return 1;
}

/*----------------------------------------------------------------------------*-
Function:
	Object_IsValidModel
Params:
	modelid - Model to check won't crash SA.
Return:
	-
Notes:
	I wrote this function a long time ago and have barely updated it at all.
	The only changes are the formatting and the use of the Bit class now,
	despite the fact this was the first large bit array I did and is thus
	the founding array of the whole idea behind the bit class.
-*----------------------------------------------------------------------------*/

stock Object_IsValidModel(modelid)
{
	static
		modeldat[] =
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -128,
			-515899393, -134217729, -1, -1, 33554431, -1, -1, -1, -14337, -1, -33,
			127, 0, 0, 0, 0, 0, -8388608, -1, -1, -1, -16385, -1, -1, -1, -1, -1,
			-1, -1, -33, -1, -771751937, -1, -9, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, 33554431, -25, -1, -1, -1, -1, -1, -1,
			-1073676289, -2147483648, 34079999, 2113536, -4825600, -5, -1, -3145729,
			-1, -16777217, -63, -1, -1, -1, -1, -201326593, -1, -1, -1, -1, -1,
			-257, -1, 1073741823, -133122, -1, -1, -65, -1, -1, -1, -1, -1, -1,
			-2146435073, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1073741823, -64, -1,
			-1, -1, -1, -2635777, 134086663, 0, -64, -1, -1, -1, -1, -1, -1, -1,
			-536870927, -131069, -1, -1, -1, -1, -1, -1, -1, -1, -16384, -1,
			-33554433, -1, -1, -1, -1, -1, -1610612737, 524285, -128, -1,
			2080309247, -1, -1, -1114113, -1, -1, -1, 66977343, -524288, -1, -1, -1,
			-1, -2031617, -1, 114687, -256, -1, -4097, -1, -4097, -1, -1,
			1010827263, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -32768, -1, -1, -1, -1, -1,
			2147483647, -33554434, -1, -1, -49153, -1148191169, 2147483647,
			-100781080, -262145, -57, 134217727, -8388608, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1048577, -1, -449, -1017, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1835009, -2049, -1, -1, -1, -1, -1, -1,
			-8193, -1, -536870913, -1, -1, -1, -1, -1, -87041, -1, -1, -1, -1, -1,
			-1, -209860, -1023, -8388609, -2096897, -1, -1048577, -1, -1, -1, -1,
			-1, -1, -897, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1610612737,
			-3073, -28673, -1, -1, -1, -1537, -1, -1, -13, -1, -1, -1, -1, -1985,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1056964609, -1, -1, -1,
			-1, -1, -1, -1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-236716037, -1, -1, -1, -1, -1, -1, -1, -536870913, 3, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -2097153, -2109441, -1, 201326591, -4194304, -1, -1,
			-241, -1, -1, -1, -1, -1, -1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, -32768, -1, -1, -1, -2, -671096835, -1, -8388609, -66323585, -13,
			-1793, -32257, -247809, -1, -1, -513, 16252911, 0, 0, 0, -131072,
			33554383, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8356095, 0, 0, 0, 0, 0,
			0, -256, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-268435449, -1, -1, -2049, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			92274627, -65536, -2097153, -268435457, 591191935, 1, 0, -16777216, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 127
		};
	return Bit_Get(Bit:modeldat, modelid);
}

/*----------------------------------------------------------------------------*-
Function:
	Object_OnPlayerDisconnect
Params:
	playerid - Player who left.
	reason - Why they left.
Return:
	-
Notes:
	Just to automatically disconnect attached objects from players.
-*----------------------------------------------------------------------------*/

Object_OnPlayerDisconnect(playerid, reason)
{
	#if defined _YSI_SETUP_MASTER
		if (!YSI_g_sIsMaster) return 0;
	#endif
	for (new objectid = 0; objectid < MAY_OBJECTS; objectid++)
	{
		YSI_g_sPlayerObjects[playerid][objectid] = NO_OBJECT;
	}
	#if !defined NO_OBJECTS_MOVE
		new
			sets = YSI_g_sMovingObjects;
		if (sets == NO_OBJECT) return 0;
		new
			start = sets;
		do
		{
			new
				e_OBJ_FLAG:flag = YSI_g_sObjects[sets][E_OBJECT_MODEL];
			if (flag & e_OBJ_FLAG_ACTIVE)
			{
				if (Object_GetAttach(flag) == playerid) DetachDynamicObjectFromPlayer(sets);
			}
			sets = YSI_g_sObjects[sets][E_OBJECT_NEXT];
		}
		while (sets != start);
	#endif
	return 1;
	#pragma unused reason
}

/*----------------------------------------------------------------------------*-
Function:
	Object_SetAreaGate
Params:
	objectid - Object to make into a gate.
	areaid - Area to trigger gate in.
	Float:tx - X point to open to.
	Float:ty - Y point to open to.
	Float:tz - Z point to open to.
	Float:ts - Speed to open at.
Return:
	-
Notes:
	Just to automatically disconnect attached objects from players.
-*----------------------------------------------------------------------------*/

stock Object_SetAreaGate(objectid, areaid, Float:tx, Float:ty, Float:tz, Float:ts, time = 10000)
{
	#if defined _YSI_SETUP_MASTER
		if (YSI_g_sIsMaster)
		{
	#endif
			#if !defined NO_OBJECTS_MOVE
				#if defined _YSI_VISUAL_AREAS
					if (Object_IsValid(objectid) && !Object_IsAttached(YSI_g_sObjects[objectid][E_OBJECT_MODEL]) && Area_IsValid(areaid))
					{
						new
							gate;
						while (gate < MAX_GATE_OBJECTS)
						{
							if (!YSI_g_sGateInfo[gate][E_GATE_INFO_OBJECT]) break;
							gate++;
						}
						if (gate == MAX_GATE_OBJECTS) return NO_GATE;
						
						YSI_g_sGateInfo[gate][E_GATE_INFO_OBJECT] = objectid | GATE_AREA_TRIGGER;
						YSI_g_sGateInfo[gate][E_GATE_INFO_TIME] = time;
						YSI_g_sGateInfo[gate][E_GATE_INFO_TRIGGER] = areaid;
						YSI_g_sObjects[objectid][E_OBJECT_MODEL] |= e_OBJ_FLAG_GATE;
						Object_SetGateTarget(gate, tx, ty, tz, ts);
						#if !defined NO_GATE_AREA_LOOKUP
							new
								slot = areaid / 2,
								shift = (areaid % 2) * 16;
							YSI_g_sGateAreas[slot] = (YSI_g_sGateAreas[slot] & (0xFFFF0000 >>> shift)) | (gate << shift);
						#endif
						return gate;
					}
				#endif
			#endif
			return NO_GATE;
	#if defined _YSI_SETUP_MASTER
		}
		else
		{
			DBGP4("Object_SetAreaGate() else: %d %d %d", objectid, areaid, time);
			CallRemoteFunction("Object_Remote", "iii", objectid, areaid, E_OBJECT_REMOTE_GATE | (time << 12));
			new
				gate = getproperty(0, "YSIReq");
			DBGP4("Object_SetAreaGate() gate: %d %d", gate, NO_GATE);
			if (gate != NO_GATE)
			{
				DBGP3("Object_SetAreaGate() ok: %.2f %.2f %.2f %.2f", tx, ty, tz, ts);
				CallRemoteFunction("Object_CoOrdRemote", "iiffff", gate, E_OBJECT_REMOTE_GATE_POS, tx, ty, tz, ts);
			}
			return gate;
		}
	#endif
}

#if defined _YSI_VISUAL_AREAS
/*----------------------------------------------------------------------------*-
Function:
	Object_OnPlayerEnterArea
Params:
	playerid - Player who entered an area.
	areaid - Area they entered.
Return:
	-
Notes:
	Internal callback from YSI_areas.
-*----------------------------------------------------------------------------*/

#if defined _YSI_SETUP_MASTER
	public Object_OnPlayerEnterArea(playerid, areaid)
	if (!YSI_g_sIsMaster) return 0;
	else
#else
	Object_OnPlayerEnterArea(playerid, areaid)
#endif
{
	DBGP2("Object_OnPlayerEnterArea() start");
	#if defined _YSI_SETUP_MASTER
		setproperty(0, "YSIReq", 0);
	#else
		#pragma unused playerid
	#endif
	#if defined NO_OBJECTS_MOVE
		return 0;
	#else
		new
			gate;
		#if defined NO_GATE_AREA_LOOKUP
			DBGP3("Object_OnPlayerEnterArea() Lookup");
			while (gate < MAX_GATE_OBJECTS)
			{
				if (YSI_g_sGateInfo[gate][E_GATE_INFO_OBJECT] & GATE_AREA_TRIGGER && YSI_g_sGateInfo[gate][E_GATE_INFO_TRIGGER] == areaid) break;
			}
			if (gate == MAX_GATE_OBJECTS) return 0;
		#else
			gate = (YSI_g_sGateAreas[areaid / 2] >>> ((areaid % 2) * 16)) & 0xFFFF;
			DBGP3("Object_OnPlayerEnterArea() Known %d %d %d", areaid, gate, YSI_g_sGateAreas[areaid / 2]);
			if (gate == 0xFFFF) return 0;
		#endif
		#if defined _YSI_SETUP_MASTER
			setproperty(0, "YSIReq", 1);
		#endif
		DBGP3("Object_OnPlayerEnterArea() Get");
		new
			objectid = YSI_g_sGateInfo[gate][E_GATE_INFO_OBJECT] & (~(GATE_AREA_TRIGGER | GATE_OPENING));
		if (Object_IsValid(objectid))
		{
			DBGP3("Object_OnPlayerEnterArea() Valid");
			if (YSI_g_sObjects[objectid][E_OBJECT_MODEL] & e_OBJ_FLAG_MOVED || YSI_g_sGateInfo[gate][E_GATE_INFO_OBJECT] & GATE_OPENING) return 1;
			DBGP3("Object_OnPlayerEnterArea() Static");
			new
				Float:x,
				Float:y,
				Float:z,
				Float:tx = (float((YSI_g_sGateInfo[gate][E_GATE_INFO_XY] >> 14) & 0x1FFFF) * ((YSI_g_sGateInfo[gate][E_GATE_INFO_XY] & 0x80000000) ? (-1.0) : (1.0)) / 10.0),
				Float:ty = (float((YSI_g_sGateInfo[gate][E_GATE_INFO_XY] & 0x03FFF) | ((YSI_g_sGateInfo[gate][E_GATE_INFO_ZA] >> 14) & 0x1C000)) * ((YSI_g_sGateInfo[gate][E_GATE_INFO_ZA] & 0x80000000) ? (-1.0) : (1.0)) / 10.0),
				Float:tz = (float((YSI_g_sGateInfo[gate][E_GATE_INFO_ZA] >> 10) & 0x1FFFF) * ((YSI_g_sGateInfo[gate][E_GATE_INFO_ZA] & 0x08000000) ? (-1.0) : (1.0)) / 10.0),
				Float:s = (float(YSI_g_sGateInfo[gate][E_GATE_INFO_ZA] & 0x3FF) / 10.0);
			Object_GetPos(objectid, x, y, z);
			YSI_g_sGateInfo[gate][E_GATE_INFO_OBJECT] |= GATE_OPENING;
			Object_SetGateTarget(gate, x, y, z, s);
			Object_Move(objectid, tx, ty, tz, s);
			Object_AddToUpdate(objectid);
			DBGP3("Object_OnPlayerEnterArea() Moved");
		}
		else
		{
			YSI_g_sGateInfo[gate][E_GATE_INFO_TRIGGER] = NO_GATE;
			#if !defined NO_GATE_AREA_LOOKUP
				YSI_g_sGateAreas[areaid / 2] |= 0xFFFF << ((areaid % 2) * 16);
			#endif
			Area_Delete(areaid);
		}
		DBGP3("Object_OnPlayerEnterArea() end");
		return 1;
	#endif
}
#endif

#if !defined NO_OBJECTS_MOVE
/*----------------------------------------------------------------------------*-
Function:
	Object_GateMoved
Params:
	objectid - Object that moved.
Return:
	-
Notes:
	Checks if the object which moved is a gate.
-*----------------------------------------------------------------------------*/

static stock Object_GateMoved(objectid)
{
	#if defined _YSI_VISUAL_AREAS
		if (YSI_g_sObjects[objectid][E_OBJECT_MODEL] & e_OBJ_FLAG_GATE)
		{
			new
				gate = 0;
			while (gate < MAX_GATE_OBJECTS)
			{
				if (objectid == (YSI_g_sGateInfo[gate][E_GATE_INFO_OBJECT] & (~(GATE_AREA_TRIGGER | GATE_OPENING)))) break;
				gate++;
			}
			if (gate == MAX_GATE_OBJECTS)
			{
				YSI_g_sObjects[objectid][E_OBJECT_MODEL] &= ~e_OBJ_FLAG_GATE;
				return 0;
			}
			if (YSI_g_sGateInfo[gate][E_GATE_INFO_OBJECT] & (GATE_AREA_TRIGGER | GATE_OPENING) == (GATE_AREA_TRIGGER | GATE_OPENING))
			{
				SetTimerEx("Object_GateClose", 500000, 0, "i", gate);
			}
			return 1;
		}
	#else
		#pragma unused objectid
	#endif
	return 0;
}
#endif

#if defined _YSI_VISUAL_AREAS
/*----------------------------------------------------------------------------*-
Function:
	Object_GateClose
Params:
	gate - Gate to close.
Return:
	-
Notes:
	Closes an area triggered gate after a delay.
-*----------------------------------------------------------------------------*/

public Object_GateClose(gate)
{
	if (Area_IsEmpty(YSI_g_sGateInfo[gate][E_GATE_INFO_TRIGGER]))
	{
		new
			objectid = YSI_g_sGateInfo[gate][E_GATE_INFO_OBJECT] & ~(GATE_AREA_TRIGGER | GATE_OPENING);
		if (Object_IsValid(objectid))
		{
			new
				Float:x,
				Float:y,
				Float:z,
				Float:tx = (float((YSI_g_sGateInfo[gate][E_GATE_INFO_XY] >> 14) & 0x1FFFF) * ((YSI_g_sGateInfo[gate][E_GATE_INFO_XY] & 0x80000000) ? (-0.1) : (0.1))),
				Float:ty = (float((YSI_g_sGateInfo[gate][E_GATE_INFO_XY] & 0x03FFF) | ((YSI_g_sGateInfo[gate][E_GATE_INFO_ZA] >> 14) & 0x1C000)) * ((YSI_g_sGateInfo[gate][E_GATE_INFO_ZA] & 0x80000000) ? (-0.1) : (0.1))),
				Float:tz = (float((YSI_g_sGateInfo[gate][E_GATE_INFO_ZA] >> 10) & 0x1FFFF) * ((YSI_g_sGateInfo[gate][E_GATE_INFO_ZA] & 0x08000000) ? (-0.1) : (0.1))),
				Float:s = (float(YSI_g_sGateInfo[gate][E_GATE_INFO_ZA] & 0x3FF) / 10.0);
			Object_GetPos(objectid, x, y, z);
			Object_SetGateTarget(gate, x, y, z, s);
			Object_Move(objectid, tx, ty, tz, s);
			Object_AddToUpdate(objectid);
		}
		else
		{
			new
				areaid = YSI_g_sGateInfo[gate][E_GATE_INFO_TRIGGER];
			YSI_g_sGateInfo[gate][E_GATE_INFO_TRIGGER] = NO_GATE;
			#if !defined NO_GATE_AREA_LOOKUP
				YSI_g_sGateAreas[areaid / 2] |= 0xFFFF << ((areaid % 2) * 16);
			#endif
			Area_Delete(areaid);
		}
	}
	else
	{
		SetTimerEx("Object_GateClose", 1000, 0, "i", gate);
	}
}
#endif

/*----------------------------------------------------------------------------*-
Function:
	CreateGate
Params:
	modelid - Model of the gate.
	Float:x - X start location.
	Float:y - Y start location.
	Float:z - Z start location.
	Float:tx - X target location.
	Float:ty - Y target location.
	Float:tz - Z target location.
	Float:rx - X rotation.
	Float:ry - Y rotation.
	Float:rz - Z rotation.
	Float:speed - Speed the gate will move at.
Return:
	-
Notes:
	Creates a gate.
-*----------------------------------------------------------------------------*/

stock CreateGate(modelid, Float:x, Float:y, Float:z, Float:tx, Float:ty, Float:tz, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0, Float:speed = 2.0)
{
	#if defined _YSI_VISUAL_AREAS
		new
			obj = CreateDynamicObject(modelid, x, y, z, rx, ry, rz);
		if (obj == NO_OBJECT) return NO_GATE;
		new
			Float:xx = floatabs(x - tx),
			Float:yy = floatabs(y - ty),
			area = Area_AddCircle(x, y, ((yy > xx) ? (yy) : (xx)) * 2.0, z + 20.0);
		if (area == NO_AREA)
		{
			DestroyDynamicObject(obj);
			return NO_GATE;
		}
		return Object_SetAreaGate(obj, area, tx, ty, tz, speed, 10000);
	#else
		#pragma unused modelid, x, y, z, tx, ty, tz, rx, ry, rz, speed
		return NO_GATE;
	#endif
}

/*----------------------------------------------------------------------------*-
Function:
	Object_GetGateArea
Params:
	gate - Gate to get the area of for permissions.
Return:
	-
Notes:
	Returns the areaid used by the gate for detection.
-*----------------------------------------------------------------------------*/

stock Object_GetGateArea(gate)
{
	#if defined _YSI_SETUP_MASTER
		if (YSI_g_sIsMaster)
		{
	#endif
			#if defined _YSI_VISUAL_AREAS
				if (gate >= 0 && gate < MAX_GATE_OBJECTS)
				{
					return YSI_g_sGateInfo[gate][E_GATE_INFO_TRIGGER];
				}
			#else
				#pragma unused gate
			#endif
			return -1;
	#if defined _YSI_SETUP_MASTER
		}
		else
		{
			CallRemoteFunction("Object_Remote", "iii", gate, 0, E_OBJECT_REMOTE_GET_AREA);
			return getproperty(0, "YSIReq");
		}
	#endif
}

