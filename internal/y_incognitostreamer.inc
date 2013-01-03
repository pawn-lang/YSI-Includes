/*----------------------------------------------------------------------------*\
					=========================================
					 y_incognitostream - y_groups + streamer 
					=========================================
Description:
	This file unites the YSI y_groups system with Incognito's streamer plugin so
	that you can use more objects/areas etc with y_groups style permissions.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI classes include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
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
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	0.1
Changelog:
	20/10/12:
		First version.
Functions:
	Public:
		-
	Core:
		-
	Stock:
		-
	Static:
		-
	Inline:
		-
	API:
		-
Callbacks:
	-
Definitions:
	-
Enums:
	-
Macros:
	-
Tags:
	-
Variables:
	Global:
		-
	Static:
		-
Commands:
	-
Compile options:
	-
Operators:
	-
\*----------------------------------------------------------------------------*/

#include "y_plugins"

static stock const
	YSI_gscEmpty[2] = {-1, -1};

#if IPS_MAX_OBJECTS != 0
	#undef _GROUP_MAKE_NAME
	#undef _GROUP_MAKE_LIMIT
	#define _GROUP_MAKE_NAME<%0...%1> %0SObject%1
	#define _GROUP_MAKE_LIMIT IPS_MAX_OBJECTS
	// Include the second half of the file for the methods.
	#include "y_groupsingle"
	#include "y_groupsecond"
	
	/*------------------------------------------------------------------------*\
	Function:
		SObject_SetPlayer
	Params:
		o - Object to set.
		p - Player to set.
		bool:s - Add or remove this object from this player.
	Return:
		-
	Notes:
		Translate the YSI permissions system to the streamer plugin permissions
		system.
	\*------------------------------------------------------------------------*/
	
	foreign void:SObject_SetPlayer(o,p,bool:s);
	
	global void:SObject_SetPlayer(o,p,bool:s)
	{
		if (s) Streamer_AppendArrayData(STREAMER_TYPE_OBJECT, o, E_STREAMER_PLAYER_ID, p);
		else Streamer_RemoveArrayData(STREAMER_TYPE_OBJECT, o, E_STREAMER_PLAYER_ID, p);
		//return s;
	}
	
	/*------------------------------------------------------------------------*\
	Function:
		IPS_CreateDynamicObject
	Params:
		-
	Return:
		-
	Notes:
		Hook the streamer creation function so that we can initialise the groups
		system for this thing.  The remainder of this file is just these two
		functions in various forms repeatedly.
	\*------------------------------------------------------------------------*/
	
	stock IPS_CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 100.0)
	{
		// Create an object for no players.
		new
			id = CreateDynamicObject(modelid, x, y, z, rx, ry, rz, worldid, interiorid, playerid, streamdistance);
		Streamer_SetArrayData(STREAMER_TYPE_OBJECT, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SObject_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicObject
		#undef CreateDynamicObject
	#else
		#define _ALS_CreateDynamicObject
	#endif
	#define CreateDynamicObject IPS_CreateDynamicObject
	
	stock IPS_CreateDynamicObjectEx(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:drawdistance = 0.0, Float:streamdistance = 200.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
	{
		// Create an object for no players.
		new
			id = CreateDynamicObjectEx(modelid, x, y, z, rx, ry, rz, drawdistance, streamdistance, worlds, interiors, players, maxworlds, maxinteriors, maxplayers);
		Streamer_SetArrayData(STREAMER_TYPE_OBJECT, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SObject_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicObjectEx
		#undef CreateDynamicObjectEx
	#else
		#define _ALS_CreateDynamicObjectEx
	#endif
	#define CreateDynamicObjectEx IPS_CreateDynamicObjectEx
#endif

#if IPS_MAX_PICKUPS != 0
	#undef _GROUP_MAKE_NAME
	#undef _GROUP_MAKE_LIMIT
	#define _GROUP_MAKE_NAME<%0...%1> %0SPickup%1
	#define _GROUP_MAKE_LIMIT IPS_MAX_PICKUPS
	// Include the second half of the file for the methods.
	#include "y_groupsingle"
	#include "y_groupsecond"
	
	foreign void:SPickup_SetPlayer(o,p,bool:s);
	
	global void:SPickup_SetPlayer(o,p,bool:s)
	{
		if (s) Streamer_AppendArrayData(STREAMER_TYPE_PICKUP, o, E_STREAMER_PLAYER_ID, p);
		else Streamer_RemoveArrayData(STREAMER_TYPE_PICKUP, o, E_STREAMER_PLAYER_ID, p);
		//return s;
	}
	
	stock IPS_CreateDynamicPickup(modelid, type, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 100.0)
	{
		// Create an object for no players.
		new
			id = CreateDynamicPickup(modelid, type, x, y, z, worldid, interiorid, playerid, streamdistance);
		Streamer_SetArrayData(STREAMER_TYPE_PICKUP, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SPickup_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicPickup
		#undef CreateDynamicPickup
	#else
		#define _ALS_CreateDynamicPickup
	#endif
	#define CreateDynamicPickup IPS_CreateDynamicPickup
	
	stock IPS_CreateDynamicPickupEx(modelid, type, Float:x, Float:y, Float:z, Float:streamdistance = 100.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
	{
		// Create an object for no players.
		new
			id = CreateDynamicPickupEx(modelid, type, x, y, z, streamdistance, worlds, interiors, players, maxworlds, maxinteriors, maxplayers);
		Streamer_SetArrayData(STREAMER_TYPE_PICKUP, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SPickup_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicPickupEx
		#undef CreateDynamicPickupEx
	#else
		#define _ALS_CreateDynamicPickupEx
	#endif
	#define CreateDynamicPickupEx IPS_CreateDynamicPickupEx
#endif

#if IPS_MAX_CPS != 0
	#undef _GROUP_MAKE_NAME
	#undef _GROUP_MAKE_LIMIT
	#define _GROUP_MAKE_NAME<%0...%1> %0SCP%1
	#define _GROUP_MAKE_LIMIT IPS_MAX_CPS
	// Include the second half of the file for the methods.
	#include "y_groupsingle"
	#include "y_groupsecond"
	
	foreign void:SCP_SetPlayer(o,p,bool:s);
	
	global void:SCP_SetPlayer(o,p,bool:s)
	{
		if (s) Streamer_AppendArrayData(STREAMER_TYPE_CP, o, E_STREAMER_PLAYER_ID, p);
		else Streamer_RemoveArrayData(STREAMER_TYPE_CP, o, E_STREAMER_PLAYER_ID, p);
		//return s;
	}
	
	stock IPS_CreateDynamicCP(Float:x, Float:y, Float:z, Float:size, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 100.0)
	{
		// Create an object for no players.
		new
			id = CreateDynamicCP(x, y, z, size, worldid, interiorid, playerid, streamdistance);
		Streamer_SetArrayData(STREAMER_TYPE_CP, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SCP_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicCP
		#undef CreateDynamicCP
	#else
		#define _ALS_CreateDynamicCP
	#endif
	#define CreateDynamicCP IPS_CreateDynamicCP
	
	stock IPS_CreateDynamicCPEx(Float:x, Float:y, Float:z, Float:size, Float:streamdistance = 100.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
	{
		// Create an object for no players.
		new
			id = CreateDynamicCPEx(x, y, z, size, streamdistance, worlds, interiors, players, maxworlds, maxinteriors, maxplayers);
		Streamer_SetArrayData(STREAMER_TYPE_CP, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SCP_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicCPEx
		#undef CreateDynamicCPEx
	#else
		#define _ALS_CreateDynamicCPEx
	#endif
	#define CreateDynamicCPEx IPS_CreateDynamicCPEx
#endif

#if IPS_MAX_RACE_CPS != 0
	#undef _GROUP_MAKE_NAME
	#undef _GROUP_MAKE_LIMIT
	#define _GROUP_MAKE_NAME<%0...%1> %0SRaceCP%1
	#define _GROUP_MAKE_LIMIT IPS_MAX_RACE_CPS
	// Include the second half of the file for the methods.
	#include "y_groupsingle"
	#include "y_groupsecond"
	
	foreign void:SRaceCP_SetPlayer(o,p,bool:s);
	
	global void:SRaceCP_SetPlayer(o,p,bool:s)
	{
		if (s) Streamer_AppendArrayData(STREAMER_TYPE_RACE_CP, o, E_STREAMER_PLAYER_ID, p);
		else Streamer_RemoveArrayData(STREAMER_TYPE_RACE_CP, o, E_STREAMER_PLAYER_ID, p);
		//return s;
	}
	
	stock IPS_CreateDynamicRaceCP(type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 100.0)
	{
		// Create an object for no players.
		new
			id = CreateDynamicRaceCP(type, x, y, z, nextx, nexty, nextz, size, worldid, interiorid, playerid, streamdistance);
		Streamer_SetArrayData(STREAMER_TYPE_RACE_CP, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SRaceCP_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicRaceCP
		#undef CreateDynamicRaceCP
	#else
		#define _ALS_CreateDynamicRaceCP
	#endif
	#define CreateDynamicRaceCP IPS_CreateDynamicRaceCP
	
	stock IPS_CreateDynamicRaceCPEx(type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size, Float:streamdistance = 100.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
	{
		// Create an object for no players.
		new
			id = CreateDynamicRaceCPEx(type, x, y, z, nextx, nexty, nextz, size, streamdistance, worlds, interiors, players, maxworlds, maxinteriors, maxplayers);
		Streamer_SetArrayData(STREAMER_TYPE_RACE_CP, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SRaceCP_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicRaceCPEx
		#undef CreateDynamicRaceCPEx
	#else
		#define _ALS_CreateDynamicRaceCPEx
	#endif
	#define CreateDynamicRaceCPEx IPS_CreateDynamicRaceCPEx
#endif

#if IPS_MAX_MAP_ICONS != 0
	#undef _GROUP_MAKE_NAME
	#undef _GROUP_MAKE_LIMIT
	#define _GROUP_MAKE_NAME<%0...%1> %0SMapIcon%1
	#define _GROUP_MAKE_LIMIT IPS_MAX_MAP_ICONS
	// Include the second half of the file for the methods.
	#include "y_groupsingle"
	#include "y_groupsecond"
	
	foreign void:SMapIcon_SetPlayer(o,p,bool:s);
	
	global void:SMapIcon_SetPlayer(o,p,bool:s)
	{
		if (s) Streamer_AppendArrayData(STREAMER_TYPE_MAP_ICON, o, E_STREAMER_PLAYER_ID, p);
		else Streamer_RemoveArrayData(STREAMER_TYPE_MAP_ICON, o, E_STREAMER_PLAYER_ID, p);
		//return s;
	}
	
	stock IPS_CreateDynamicMapIcon(Float:x, Float:y, Float:z, type, color, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 100.0)
	{
		// Create an object for no players.
		new
			id = CreateDynamicMapIcon(x, y, z, type, color, worldid, interiorid, playerid, streamdistance);
		Streamer_SetArrayData(STREAMER_TYPE_MAP_ICON, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SMapIcon_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicMapIcon
		#undef CreateDynamicMapIcon
	#else
		#define _ALS_CreateDynamicMapIcon
	#endif
	#define CreateDynamicMapIcon IPS_CreateDynamicMapIcon
	
	stock IPS_CreateDynamicMapIconEx(Float:x, Float:y, Float:z, type, color, style, Float:streamdistance = 100.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
	{
		// Create an object for no players.
		new
			id = CreateDynamicMapIconEx(x, y, z, type, color, style, streamdistance, worlds, interiors, players, maxworlds, maxinteriors, maxplayers);
		Streamer_SetArrayData(STREAMER_TYPE_MAP_ICON, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SMapIcon_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicMapIconEx
		#undef CreateDynamicMapIconEx
	#else
		#define _ALS_CreateDynamicMapIconEx
	#endif
	#define CreateDynamicMapIconEx IPS_CreateDynamicMapIconEx
#endif

#if IPS_MAX_3D_TEXT_LABELS != 0
	#undef _GROUP_MAKE_NAME
	#undef _GROUP_MAKE_LIMIT
	#define _GROUP_MAKE_NAME<%0...%1> %0SText3D%1
	#define _GROUP_MAKE_LIMIT IPS_MAX_3D_TEXT_LABELS
	#define _GROUP_MAKE_TAG         Text3D
	// Include the second half of the file for the methods.
	#include "y_groupsingle"
	#define _GROUP_MAKE_TAG         Text3D
	#include "y_groupsecond"
	//#undef _GROUP_MAKE_TAG
	
	foreign void:SText3D_SetPlayer(Text3D:o,p,bool:s);
	
	global void:SText3D_SetPlayer(Text3D:o,p,bool:s)
	{
		if (s) Streamer_AppendArrayData(STREAMER_TYPE_3D_TEXT_LABEL, o, E_STREAMER_PLAYER_ID, p);
		else Streamer_RemoveArrayData(STREAMER_TYPE_3D_TEXT_LABEL, o, E_STREAMER_PLAYER_ID, p);
		//return s;
	}
	
	stock Text3D:IPS_CreateDynamic3DTextLabel(const text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 100.0)
	{
		// Create an object for no players.
		new
			Text3D:id = CreateDynamic3DTextLabel(text, color, x, y, z, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance);
		Streamer_SetArrayData(STREAMER_TYPE_3D_TEXT_LABEL, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SText3D_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamic3DTextLabel
		#undef CreateDynamic3DTextLabel
	#else
		#define _ALS_CreateDynamic3DTextLabel
	#endif
	#define CreateDynamic3DTextLabel IPS_CreateDynamic3DTextLabel
	
	stock Text3D:IPS_CreateDynamic3DTextLabelEx(const text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, Float:streamdistance = 100.0, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
	{
		// Create an object for no players.
		new
			Text3D:id = CreateDynamic3DTextLabelEx(text, color, x, y, z, drawdistance, attachedplayer, attachedvehicle, testlos, streamdistance, worlds, interiors, players, maxworlds, maxinteriors, maxplayers);
		Streamer_SetArrayData(STREAMER_TYPE_3D_TEXT_LABEL, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SText3D_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamic3DTextLabelEx
		#undef CreateDynamic3DTextLabelEx
	#else
		#define _ALS_CreateDynamic3DTextLabelEx
	#endif
	#define CreateDynamic3DTextLabelEx IPS_CreateDynamic3DTextLabelEx
#endif

#if IPS_MAX_AREAS != 0
	#undef _GROUP_MAKE_NAME
	#undef _GROUP_MAKE_LIMIT
	#define _GROUP_MAKE_NAME<%0...%1> %0SArea%1
	#define _GROUP_MAKE_LIMIT IPS_MAX_AREAS
	// Include the second half of the file for the methods.
	#include "y_groupsingle"
	#include "y_groupsecond"
	
	foreign void:SArea_SetPlayer(o,p,bool:s);
	
	global void:SArea_SetPlayer(o,p,bool:s)
	{
		if (s) Streamer_AppendArrayData(STREAMER_TYPE_AREA, o, E_STREAMER_PLAYER_ID, p);
		else Streamer_RemoveArrayData(STREAMER_TYPE_AREA, o, E_STREAMER_PLAYER_ID, p);
		//return s;
	}
	
	stock IPS_CreateDynamicCircle(Float:x, Float:y, Float:size, worldid = -1, interiorid = -1, playerid = -1)
	{
		new
			id = CreateDynamicCircle(x, y, size, worldid, interiorid, playerid);
		Streamer_SetArrayData(STREAMER_TYPE_AREA, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SArea_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicCircle
		#undef CreateDynamicCircle
	#else
		#define _ALS_CreateDynamicCircle
	#endif
	#define CreateDynamicCircle IPS_CreateDynamicCircle
	
	stock IPS_CreateDynamicRectangle(Float:minx, Float:miny, Float:maxx, Float:maxy, worldid = -1, interiorid = -1, playerid = -1)
	{
		new
			id = CreateDynamicRectangle(minx, miny, maxx, maxy, worldid, interiorid, playerid);
		Streamer_SetArrayData(STREAMER_TYPE_AREA, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SArea_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicRectangle
		#undef CreateDynamicRectangle
	#else
		#define _ALS_CreateDynamicRectangle
	#endif
	#define CreateDynamicRectangle IPS_CreateDynamicRectangle
	
	stock IPS_CreateDynamicSphere(Float:x, Float:y, Float:z, Float:size, worldid = -1, interiorid = -1, playerid = -1)
	{
		new
			id = CreateDynamicSphere(x, y, z, size, worldid, interiorid, playerid);
		Streamer_SetArrayData(STREAMER_TYPE_AREA, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SArea_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicSphere
		#undef CreateDynamicSphere
	#else
		#define _ALS_CreateDynamicSphere
	#endif
	#define CreateDynamicSphere IPS_CreateDynamicSphere
	
	stock IPS_CreateDynamicCube(Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, worldid = -1, interiorid = -1, playerid = -1)
	{
		new
			id = CreateDynamicCube(minx, miny, minz, maxx, maxy, maxz, worldid, interiorid, playerid);
		Streamer_SetArrayData(STREAMER_TYPE_AREA, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SArea_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicCube
		#undef CreateDynamicCube
	#else
		#define _ALS_CreateDynamicCube
	#endif
	#define CreateDynamicCube IPS_CreateDynamicCube
	
	stock IPS_CreateDynamicPolygon(Float:points[], Float:minz = -FLOAT_INFINITY, Float:maxz = FLOAT_INFINITY, maxpoints = sizeof points, worldid = -1, interiorid = -1, playerid = -1)
	{
		new
			id = CreateDynamicPolygon(points[], minz, maxz, maxpoints, worldid, interiorid, playerid);
		Streamer_SetArrayData(STREAMER_TYPE_AREA, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SArea_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicPolygon
		#undef CreateDynamicPolygon
	#else
		#define _ALS_CreateDynamicPolygon
	#endif
	#define CreateDynamicPolygon IPS_CreateDynamicPolygon
	
	stock IPS_CreateDynamicCircleEx(Float:x, Float:y, Float:size, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
	{
		new
			id = CreateDynamicCircleEx(x, y, size, worlds, interiors, players, maxworlds, maxinteriors, maxplayers);
		Streamer_SetArrayData(STREAMER_TYPE_AREA, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SArea_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicCircleEx
		#undef CreateDynamicCircleEx
	#else
		#define _ALS_CreateDynamicCircleEx
	#endif
	#define CreateDynamicCircleEx IPS_CreateDynamicCircleEx
	
	stock IPS_CreateDynamicRectangleEx(Float:minx, Float:miny, Float:maxx, Float:maxy, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
	{
		new
			id = CreateDynamicRectangleEx(minx, miny, maxx, maxy, worlds, interiors, players, maxworlds, maxinteriors, maxplayers);
		Streamer_SetArrayData(STREAMER_TYPE_AREA, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SArea_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicRectangleEx
		#undef CreateDynamicRectangleEx
	#else
		#define _ALS_CreateDynamicRectangleEx
	#endif
	#define CreateDynamicRectangleEx IPS_CreateDynamicRectangleEx
	
	stock IPS_CreateDynamicSphereEx(Float:x, Float:y, Float:z, Float:size, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
	{
		new
			id = CreateDynamicSphereEx(x, y, z, size, worlds, interiors, players, maxworlds, maxinteriors, maxplayers);
		Streamer_SetArrayData(STREAMER_TYPE_AREA, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SArea_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicSphereEx
		#undef CreateDynamicSphereEx
	#else
		#define _ALS_CreateDynamicSphereEx
	#endif
	#define CreateDynamicSphereEx IPS_CreateDynamicSphereEx
	
	stock IPS_CreateDynamicCubeEx(Float:minx, Float:miny, Float:minz, Float:maxx, Float:maxy, Float:maxz, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
	{
		new
			id = CreateDynamicCubeEx(minx, miny, minz, maxx, maxy, maxz, worlds, interiors, players, maxworlds, maxinteriors, maxplayers);
		Streamer_SetArrayData(STREAMER_TYPE_AREA, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SArea_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicCubeEx
		#undef CreateDynamicCubeEx
	#else
		#define _ALS_CreateDynamicCubeEx
	#endif
	#define CreateDynamicCubeEx IPS_CreateDynamicCubeEx
	
	stock IPS_CreateDynamicPolygonEx(Float:points[], Float:minz = -FLOAT_INFINITY, Float:maxz = FLOAT_INFINITY, maxpoints = sizeof points, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players)
	{
		new
			id = CreateDynamicPolygonEx(points, minz, maxz, maxpoints, worlds, interiors, players, maxworlds, maxinteriors, maxplayers);
		Streamer_SetArrayData(STREAMER_TYPE_AREA, id, E_STREAMER_PLAYER_ID, YSI_gscEmpty, 0);
		SArea_InitialiseFromGroups(id);
		return id;
	}
	
	#if defined _ALS_CreateDynamicPolygonEx
		#undef CreateDynamicPolygonEx
	#else
		#define _ALS_CreateDynamicPolygonEx
	#endif
	#define CreateDynamicPolygonEx IPS_CreateDynamicPolygonEx
#endif
