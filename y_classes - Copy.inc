/*----------------------------------------------------------------------------*\
					======================================
					 y_classes - Advanced class selection 
					======================================
Description:
	Allows greater control over classes so not everyone has every class.  Uses
	a form of compression for locations.
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
	02/01/08:
		First '08 edit - Fixed minus numbers in spawn points.
	18/11/07:
		Improved location compression to allow larger areas.
		Moved position code to Class_OnPlayerSpawn to reduce overhead.
	10/10/07:
		Fixed spawn data problem.
	31/08/07:
		Added cheap master system - YSI_SLAVE_CLASSs can't be master.
	05/08/07:
		Fixed a few bugs with repeated selection.
	04/08/07:
		First version.
Functions:
	Public:
		Class_AddRemote - Adds a class to the remote master.
		Class_Remote - Updates settings remotely.
	Core:
		Class_Class - Sets up the system.
		Class_OnPlayerRequestSpawn - Called when a player requests a spawn.
		Class_OnPlayerRequestClass - Called when a player requests a class.
		Class_OnPlayerConnect - Called when a player connects.
	Stock:
		Class_Delete - Removes a class.
		Class_SetPlayer - Sets whether or not a player can use a class.
		Class_Disable - Disables a class.
		Class_Enable - Enables a disabled class.
		Class_AddForGroup - Adds a class to the system for only one group.
		Class_Add - Adds a class to the system.
		Class_AddEx - Adds a class to the system with group selection and setting.
		Class_AddWithGroupSet - Adds a class and sets their group on selection.
		Class_AllowReselection - Allows or disallows people to return to reselect a class.
		Class_RequireSpawnLogin - Require people to login before spawning.
		Class_RequireSelectionLogin - Require people to login before selecting.
		Class_RequireSelectionReg - Require people to register before selecting.
		Class_RequireSpawnReg - Require people to register before spawning.
	Static:
		Class_AddClass - Adds a class, wrapped by API and remote functions.
	Inline:
		Class_IsActive - Checks a class is active.
		Class_Enabled - Checks a class is enabled.
		Class_IsValid - Checks a class is valid.
		Class_X - Gets a classes x position.
		Class_Y - Gets a classes y position.
		Class_Z - Gets a classes z position.
		Class_A - Gets a classes angle.
		Class_Skin - Gets a classes skin.
	API:
		-
Callbacks:
	-
Definitions:
	MAX_CLASSES - Maximum number of classes storeable by the system.
	CLASS_LEFT - Flag for last internal class viewed.
	CLASS_MIDDLE - Flag for last internal class viewed.
	CLASS_RIGHT - Flag for last internal class viewed.
Enums:
	e_CLASS_FLAGS - Small data for individual classes.
	E_CLASS - Class data structure.
Macros:
	-
Tags:
	-
Variables:
	Global:
		-
	Static:
		YSI_g_sClasses - Data for classes.
		YSI_g_sPlayerClass - Player's current classes.
		YSI_g_sLeft - Handle for the first internal class.
		YSI_g_sMiddle - Handle for the second internal class.
		YSI_g_sRight - Handle for the third internal class.
		YSI_g_sClassCount - Number of classes stored.
Commands:
	-
Compile options:
	-
Operators:
	-
\*----------------------------------------------------------------------------*/

#include "internal\y_version"
#include "y_bit"
#include "y_debug"

#define YSIM_U_DISABLE
#include "y_master"

#include "y_iterate"

#include "y_hooks"

#if !defined MAX_CLASSES
	#define MAX_CLASSES                 (256)
#endif

#if !defined MAX_CLASS_SPAWN_WEAPONS
	#define MAX_CLASS_SPAWN_WEAPONS     (13)
#endif

#if !defined WEAPON_ARMOUR
	#define WEAPON_ARMOUR               (100)
#endif

#define OnPlayerRequestClassEx(%0) OnPlayerRequestClassEx_(%0)if(!YSI_gOPRCE)return 0;else
#define OnPlayerRequestSpawnEx(%0) OnPlayerRequestSpawnEx_(%0)if(!YSI_gOPRSE)return 0;else

#define INFINATE_ARMOUR                 (0x00800000)

#define _CLASS_WEAPON_CODE if((n-w)&0x01)while(w!=n&&s<MAX_CLASS_SPAWN_WEAPONS){cw=getarg(w++);if(cw==WEAPON_ARMOUR)weapons[MAX_CLASS_SPAWN_WEAPONS]=WEAPON_ARMOUR|(100<<8);else if(w==n)P:E(": Insufficient class weapon data.");else weapons[s++]=(cw&0xFF)|(getarg(w++)<<8);}else while(w!=n&&s<MAX_CLASS_SPAWN_WEAPONS){cw=getarg(w++);if(cw==WEAPON_ARMOUR)weapons[MAX_CLASS_SPAWN_WEAPONS]=WEAPON_ARMOUR|(getarg(w++)<<8);else weapons[s++]=(cw&0xFF)|(getarg(w++)<<8);}

#define _GROUP_MAKE_NAME_CLASSES<%0...%1>   %0Class%1
#define _GROUP_MAKE_LIMIT_CLASSES           MAX_CLASSES

//forward Class_ResolveGroups(class, Group:forgroup, bool:cp);

#include "y_groups"
#include "y_playerarray"

#include "y_iterate"

enum e_CLASS_FLAGS (<<= 1)
{
	e_CLASS_FLAGS_SKIN   = 0x0000FFFF,
	e_CLASS_FLAGS_ACTIVE = 0x01000000,
	e_CLASS_FLAGS_ENABLED,
	e_CLASS_FLAGS_DEFAULT
}

enum E_CLASS
{
	e_CLASS_FLAGS:E_CLASS_FLAGS,
	Float:E_CLASS_X,
	Float:E_CLASS_Y,
	Float:E_CLASS_Z,
	Float:E_CLASS_A,
	E_CLASS_WEAPONS[MAX_CLASS_SPAWN_WEAPONS + 1],
	//#if defined _YSI_SYSTEM_GROUPS
	Group:E_CLASS_GROUP,
	//#endif
	PlayerArray:E_CLASS_PLAYERS<MAX_PLAYERS>
	//Bit:E_CLASS_PLAYERS[PLAYER_BIT_ARRAY]
}

enum e_CLASS_OPTION (<<= 1)
{
	e_CLASS_OPTION_PAUSED = 0x0000FFFF,
	e_CLASS_OPTION_NORE = 0x00010000,
	e_CLASS_OPTION_LOGIN_SELECT,
	e_CLASS_OPTION_LOGIN_SPAWN,
	e_CLASS_OPTION_REG_SELECT,
	e_CLASS_OPTION_REG_SPAWN,
	e_CLASS_OPTION_HAS_RC_CALLBACK,
	e_CLASS_OPTION_HAS_RS_CALLBACK,
	e_CLASS_OPTION_REFRESH_PAUSE
}

enum e_PLAYER_CLASS (<<= 1)
{
	e_PLAYER_CLASS_SKIN  = 0x000FFFFF,
	e_PLAYER_CLASS_PRESS = 0x00E00000,
	e_PLAYER_CLASS_RIGHT = 0x00200000,
	e_PLAYER_CLASS_MIDDLE,
	e_PLAYER_CLASS_LEFT,
	e_PLAYER_CLASS_EVER, // Has this player EVER spawned?
	e_PLAYER_CLASS_DENY, // Is this player not allowed to see class selection?
	e_PLAYER_CLASS_SPAWNED, // Should this player NOT be allowed to reselect?
	e_PLAYER_CLASS_SELECT,
	e_PLAYER_CLASS_RETURN, // Player is returning to class selection.
	e_PLAYER_CLASS_AFTER_RETURN, // Prevent the double class selection screen.
	e_PLAYER_CLASS_TEMP_SPAWN // Player has spawned once, respawn them.
}

#define e_PLAYER_CLASS_SPAWN_CHECK      (e_PLAYER_CLASS_AFTER_RETURN | e_PLAYER_CLASS_TEMP_SPAWN)

#define CLASS_MOVE_LEFT                 (e_PLAYER_CLASS:-1)
#define CLASS_MOVE_RIGHT                (e_PLAYER_CLASS:1)

static stock
	YSI_g_sClasses[MAX_CLASSES][E_CLASS],
	e_PLAYER_CLASS:YSI_g_sPlayerClass[MAX_PLAYERS],
	YSI_g_sLeft,
	YSI_g_sMiddle,
	YSI_g_sRight,
	YSI_g_sClassCount,
	e_CLASS_OPTION:YSI_g_sClassOptions,
	YSI_g_sLastRefuse[MAX_PLAYERS];

static
	bool:YSI_g_sIsFirst = false;

stock
	bool:YSI_gOPRCE = true,
	bool:YSI_gOPRSE = true;

forward OnPlayerRequestSpawnEx_(playerid, classid);
forward OnPlayerRequestClassEx_(playerid, classid);

// This is set to not have to repeatedly update a player in a large set of
// group updates.  It is set and cleared in the request callbacks.
#define Class_PauseRefresh(%1) \
	(YSI_g_sClassOptions |= e_CLASS_OPTION_REFRESH_PAUSE | e_CLASS_OPTION:(%1))

#define Class_IsPaused(%1) \
	((YSI_g_sClassOptions & (e_CLASS_OPTION_REFRESH_PAUSE | e_CLASS_OPTION_PAUSED)) == (e_CLASS_OPTION_REFRESH_PAUSE | e_CLASS_OPTION:(%1)))

/*----------------------------------------------------------------------------*\
Function:
	Class_IsActive
Params:
	classid - Class to check.
Return:
	-
Notes:
	Checks if a class is currently in use.
\*----------------------------------------------------------------------------*/

#define Class_IsActive(%1) \
	(YSI_g_sClasses[(%1)][E_CLASS_FLAGS] & e_CLASS_FLAGS_ACTIVE)

/*----------------------------------------------------------------------------*\
Function:
	Class_Enabled
Params:
	classid - Class to check.
Return:
	-
Notes:
	Checks if a class is currently available for viewing.
\*----------------------------------------------------------------------------*/

#define Class_Enabled(%1) \
	(YSI_g_sClasses[(%1)][E_CLASS_FLAGS] & e_CLASS_FLAGS_ENABLED)

/*----------------------------------------------------------------------------*\
Function:
	Class_IsValid
Params:
	classid - Class to check.
Return:
	-
Notes:
	Checks if a number is a valid classid and active.
\*----------------------------------------------------------------------------*/

#define Class_IsValid(%1) \
	((%1) >= 0 && (%1) < MAX_CLASSES && Class_IsActive((%1)))

/*----------------------------------------------------------------------------*\
Function:
	Class_X
Params:
	classid - Class to get X location for.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Class_X(%1) \
	YSI_g_sClasses[(%1)][E_CLASS_X]
	//(float(YSI_g_sClasses[(%1)][E_CLASS_XY] >> 16) / 10.0)

/*----------------------------------------------------------------------------*\
Function:
	Class_Y
Params:
	classid - Class to get Y location for.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Class_Y(%1) \
	YSI_g_sClasses[(%1)][E_CLASS_Y]
	//(float((YSI_g_sClasses[(%1)][E_CLASS_XY] & 0x7FFF) | ((YSI_g_sClasses[(%1)][E_CLASS_XY] & 0x8000) ? (0xFFFF8000) : (0))) / 10.0)

/*----------------------------------------------------------------------------*\
Function:
	Class_Z
Params:
	classid - Class to get Z location for.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Class_Z(%1) \
	YSI_g_sClasses[(%1)][E_CLASS_Z]
	//(float(YSI_g_sClasses[(%1)][E_CLASS_ZA] >> 16) / 10.0)

/*----------------------------------------------------------------------------*\
Function:
	Class_A
Params:
	classid - Class to get angle for.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Class_A(%1) \
	YSI_g_sClasses[(%1)][E_CLASS_A]
	//(float((YSI_g_sClasses[(%1)][E_CLASS_ZA] & 0x7FFF) | (YSI_g_sClasses[(%1)][E_CLASS_ZA] & 0x8000) ? (0xFFFF8000) : (0)) / 10.0)

/*----------------------------------------------------------------------------*\
Function:
	Class_Skin
Params:
	classid - Class to get skin for.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

#define Class_Skin(%1) \
	(YSI_g_sClasses[(%1)][E_CLASS_FLAGS] & e_CLASS_FLAGS_SKIN)

/*----------------------------------------------------------------------------*\
Function:
	Class_Class
Params:
	-
Return:
	-
Notes:
	Creates three real player classes so you can scroll correctly with the
	direction being detected.
\*----------------------------------------------------------------------------*/

forward _Class_DetermineOrder();

public _Class_DetermineOrder()
{
	YSI_g_sIsFirst = false;
	if (getproperty(8, YSIM_HFIRST) == 1)
	{
		// This is the first script called by "__CallRemoteFunction", and this is
		// updated every time a new script is started.
		setproperty(8, YSIM_HFIRST, 0);
		YSI_g_sIsFirst = true;
	}
}

/*hook OnAnyScriptInit()
{
	// A whole new callback created just for this!  Should maybe pass an ID
	// parameter, but that would mean more binding with the master system.
	setproperty(8, YSIM_HFIRST, 1);
	CallRemoteFunction("_Class_DetermineOrder", "");
}*/

//mhook OnScriptInit()
hook OnScriptInit()
{
	setproperty(8, YSIM_HFIRST, 1);
	CallRemoteFunction("_Class_DetermineOrder", "");
	#if !_YSIM_IS_CLIENT
		if (!YSI_FILTERSCRIPT)
		{
			// This code placement is not generic.
			YSI_g_sLeft = AddPlayerClass(0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
			YSI_g_sMiddle = AddPlayerClass(0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
			YSI_g_sRight = AddPlayerClass(0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
			YSI_g_sClassOptions = ((funcidx("OnPlayerRequestClassEx_") == -1) ? (e_CLASS_OPTION:0) : (e_CLASS_OPTION_HAS_RC_CALLBACK)) | ((funcidx("OnPlayerRequestSpawnEx_") == -1) ? (e_CLASS_OPTION:0) : (e_CLASS_OPTION_HAS_RS_CALLBACK));
			#if !defined YSI_NO_MASTER
				// Steal the master system.
				_Master_Get(#_YCM, true);
				#if _YSIM_IS_CLOUD
					// Set to uninitialised.
					state _YCM:u;
				#endif
				CallRemoteFunction(#_YCM, "");
				#if _YSIM_IS_CLOUD
					// Fully master.
					state _YCM:y;
				#endif
			#endif
		}
	#endif
	return 1;
}

stock Class_ResolveGroups(class, Group:forgroup, bool:cp) <YSI_has_groups : n>
{
	#pragma unused forgroup
	P:2("Class_ResolveGroups<n>: call Resolve %d %d %d", class, _:forgroup, cp);
	if (!cp) PA_Init(YSI_g_sClasses[class][E_CLASS_PLAYERS], true);
	//else if (forgroup) {}
	//Bit_SetAll(YSI_g_sClasses[class][E_CLASS_PLAYERS], true, bits<MAX_PLAYERS>);
}

stock Class_ResolveGroups(class, Group:forgroup, bool:cp) <>
{
	#pragma unused forgroup
	P:2("Class_ResolveGroups<>: call Resolve %d %d %d", class, _:forgroup, cp);
	if (!cp) PA_Init(YSI_g_sClasses[class][E_CLASS_PLAYERS], true);
	//else if (forgroup) {}
	//Bit_SetAll(YSI_g_sClasses[class][E_CLASS_PLAYERS], true, bits<MAX_PLAYERS>);
}

/*----------------------------------------------------------------------------*\
Function:
	Class_OnPlayerRequestSpawn
Params:
	playerid - Player who selected a spawn.
Return:
	-
Notes:
	Has inbuilt protection for a bug where selections aren't correctly
	debounced so you can press shift twice at once which can mess up some
	scripts (e.g. the example team selection script).  Calls
	OnPlayerRequestSpawnEx with an additional class parameter.
\*----------------------------------------------------------------------------*/

mhook OnPlayerRequestSpawn(playerid)
{
	P:2("hook Class_OnPlayerRequestSpawn called: %d", playerid);
	//P:2("Class_OnPlayerRequestSpawn called");
	Class_PauseRefresh(playerid);
	if (YSI_g_sClassCount)
	{
		P:5("Class_OnPlayerRequestSpawn: Has class count");
		new
			e_PLAYER_CLASS:playerclass = YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN;
		if (!(Class_Enabled(playerclass) && PA_Get(YSI_g_sClasses[playerclass][E_CLASS_PLAYERS], playerid)))
		{
			Class_ResumeRefresh(playerid);
			return 1;
		}
		P:5("Class_OnPlayerRequestSpawn: Can spawn");
		// Don't need this line anymore - it's all done in OnPlayerRequestClass
		// OnPlayerSpawn.
		//SetSpawnInfo(playerid, NO_TEAM, Class_Skin(playerclass), Class_X(playerclass), Class_Y(playerclass), Class_Z(playerclass), Class_A(playerclass), 0, 0, 0, 0, 0, 0);
		new
			time = GetTickCount();
		if ((time - YSI_g_sLastRefuse[playerid]) >= 1000)
		{
			YSI_gOPRSE = false;
			CallRemoteFunction("OnPlayerRequestSpawnEx_", "ii", playerid, playerclass);
			new
				ret = 1;
			if (YSI_g_sClassOptions & e_CLASS_OPTION_HAS_RS_CALLBACK)
			{
				YSI_gOPRSE = true;
				ret = CallLocalFunction("OnPlayerRequestSpawnEx_", "ii", playerid, playerclass);
			}
			P:4("Class_OnPlayerRequestSpawn() return: %d", ret);
			if (ret)
			{
				//#if defined _YSI_SYSTEM_GROUPS
				new
					Group:newgroup = YSI_g_sClasses[playerclass][E_CLASS_GROUP];
				P:4("Class_OnPlayerRequestSpawn() newgroup: %d", _:newgroup);
				if (newgroup != Group:-1) Class_ResolveGroups(playerid, newgroup, true); //Group_AddPlayer(newgroup, playerid);
				//#endif
				if (ret == 1)
				{
					//ALS_CALL<PlayerRequestSpawn>
					Class_ResumeRefresh(playerid);
					return 1;
				}
				else if(ret == -1)
				{
					YSI_g_sPlayerClass[playerid] |= e_PLAYER_CLASS_SKIN;
					// The order is VERY important here - this will actually
					// call the function further down (directly below in fact).
					//OnPlayerRequestClass(playerid, YSI_g_sLeft);
					Class_DoOnPlayerRequestClass(playerid, YSI_g_sLeft);
				}
			}
		}
		YSI_g_sLastRefuse[playerid] = time;
		Class_ResumeRefresh(playerid);
		P:5("Class_OnPlayerRequestSpawn: Return 0");
		return 0;
	}
	//ALS_CALL<PlayerRequestSpawn>
	Class_ResumeRefresh(playerid);
	P:5("Class_OnPlayerRequestSpawn: Return 1");
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_OnPlayerRequestClass
Params:
	playerid - Player who requested a class.
	class - Class they requested.
Return:
	-
Notes:
	The input is one of the three real classes used to detect selected
	direction of alteration.  Scans for a class the player is allowed to use
	and hot swaps it out.  Uses SetPlayerSkin AND SetSpawnInfo to combat bugs
	with calling this from OnPlayerRequestSpawn (e.g. the example team script).
	Calls OnPlayerRequestClassEx with the current internal class not the real
	one.
\*----------------------------------------------------------------------------*/

static stock e_PLAYER_CLASS:Class_FindNew(playerid, e_PLAYER_CLASS:playerclass, e_PLAYER_CLASS:dir)
{
	P:4("e_PLAYER_CLASS:Class_FindNew called: %i, %i, %i", playerid, _:playerclass, _:dir);
	if (playerclass >= e_PLAYER_CLASS:YSI_g_sClassCount)
	{
		playerclass = -dir;
	}
	new
		e_PLAYER_CLASS:old = playerclass % e_PLAYER_CLASS:YSI_g_sClassCount;
	do
	{
		playerclass = (playerclass + dir) % e_PLAYER_CLASS:YSI_g_sClassCount;
		//P:4("Class_OnPlayerRequestClass() playerclass: %d", playerclass);
		/*if (playerclass < e_PLAYER_CLASS:0)
		{
			playerclass = e_PLAYER_CLASS:(YSI_g_sClassCount - 1);
		}
		else if (playerclass >= e_PLAYER_CLASS:YSI_g_sClassCount)
		{
			playerclass = e_PLAYER_CLASS:0;
		}*/
		P:4("Class_FindNew: %d %d", playerclass, playerid);
	}
	while (playerclass != old && !(Class_Enabled(playerclass) && PA_Get(YSI_g_sClasses[playerclass][E_CLASS_PLAYERS], playerid)));
	return playerclass;
}

static stock Class_ResumeRefresh(playerid)
{
	P:4("Class_ResumeRefresh called: %i", playerid);
	YSI_g_sClassOptions &= ~(e_CLASS_OPTION_REFRESH_PAUSE | e_CLASS_OPTION_PAUSED);
	new
		e_PLAYER_CLASS:curclass = YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN;
	if (!PA_Get(YSI_g_sClasses[curclass][E_CLASS_PLAYERS], playerid))
	{
		Class_Goto(playerid, Class_FindNew(playerid, e_PLAYER_CLASS:curclass, CLASS_MOVE_RIGHT));
	}
	/*if (YSI_g_sClassOptions & e_CLASS_OPTION_NORE)
	{
		// Yes, if they're NOT allowed to change class, send them back to class
		// selection!  This is so the message doesn't appear.
		ForceClassSelection(playerid);
	}*/
}

#if !_YSIM_IS_CLIENT
	forward _Class_DoRespawn(playerid);
	
	public _Class_DoRespawn(playerid)
	{
		SpawnPlayer(playerid);
	}
#endif

mhook OnPlayerRequestClass(playerid, classid)
{
	P:2("hook OnPlayerRequestClass called: %d, %d", playerid, classid);
	return Class_DoOnPlayerRequestClass(playerid, classid);
}

static stock Class_DoOnPlayerRequestClass(playerid, classid)
{
	P:4("Class_DoOnPlayerRequestClass called: %d, %d", playerid, classid);
	//P:2("Class_OnPlayerRequestClass() start");
	Class_PauseRefresh(playerid);
	//YSI_g_sPlayerClass[playerid] |= e_PLAYER_CLASS_SELECT;
	new
		e_PLAYER_CLASS:playerclass = YSI_g_sPlayerClass[playerid],
		e_PLAYER_CLASS:dir = CLASS_MOVE_RIGHT;
	if ((YSI_g_sClassOptions & e_CLASS_OPTION_NORE) && (playerclass & e_PLAYER_CLASS_SPAWNED))
	{
		//ForceClassSelection(playerid);
		YSI_g_sPlayerClass[playerid] &= ~e_PLAYER_CLASS_AFTER_RETURN;
		// People aren't allowed to return to class selection.
		//SpawnPlayer(playerid);
		SetTimerEx("_Class_DoRespawn", 0, 0, "i", playerid);
		//Class_ResumeRefresh(playerid);
		return -1;
	}
	// Spawned from returning to class selection but not meant to.
	P:5("Class_OnPlayerRequestClass(): Spawn check %d %d", (playerclass & e_PLAYER_CLASS_SPAWN_CHECK), e_PLAYER_CLASS_SPAWN_CHECK);
	/*if ((playerclass & e_PLAYER_CLASS_SPAWN_CHECK) == e_PLAYER_CLASS_SPAWN_CHECK)
	{
		YSI_g_sPlayerClass[playerid] &= ~e_PLAYER_CLASS_SPAWN_CHECK;
		// People aren't allowed to return to class selection.
		playerclass &= e_PLAYER_CLASS_SKIN;
		SetSpawnInfo(playerid, NO_TEAM, Class_Skin(e_PLAYER_CLASS:playerclass), Class_X(e_PLAYER_CLASS:playerclass), Class_Y(e_PLAYER_CLASS:playerclass), Class_Z(e_PLAYER_CLASS:playerclass), Class_A(e_PLAYER_CLASS:playerclass), 0, 0, 0, 0, 0, 0);
		//SpawnPlayer(playerid);
		SetTimerEx("_Class_DoRespawn", 0, 0, "i", playerid);
		//Class_ResumeRefresh(playerid);
		return 1;
	}*/
	if (playerclass & e_PLAYER_CLASS_DENY)
	{
		TogglePlayerControllable(playerid, false);
		TogglePlayerSpectating(playerid, true);
		Class_ResumeRefresh(playerid);
		return 0;
	}
	switch (playerclass & e_PLAYER_CLASS_PRESS)
	{
		case e_PLAYER_CLASS_RIGHT:
		{
			if (classid == YSI_g_sMiddle)
			{
				// Went from the right to the middle - that's a move left.
				dir = CLASS_MOVE_LEFT;
			}
		}
		case e_PLAYER_CLASS_MIDDLE:
		{
			if (classid == YSI_g_sLeft)
			{
				// Went from the middle to the left - that's a move left.
				dir = CLASS_MOVE_LEFT;
			}
		}
		default:
		{
			if (classid == YSI_g_sRight)
			{
				// Went from the left to the right - that's a wrap move left.
				dir = CLASS_MOVE_LEFT;
			}
		}
	}
	if (classid == YSI_g_sMiddle) YSI_g_sPlayerClass[playerid] = e_PLAYER_CLASS_MIDDLE | (playerclass & (e_PLAYER_CLASS_AFTER_RETURN | e_PLAYER_CLASS_EVER));
	else if (classid == YSI_g_sLeft) YSI_g_sPlayerClass[playerid] = e_PLAYER_CLASS_LEFT | (playerclass & (e_PLAYER_CLASS_AFTER_RETURN | e_PLAYER_CLASS_EVER));
	else if (classid == YSI_g_sRight) YSI_g_sPlayerClass[playerid] = e_PLAYER_CLASS_RIGHT | (playerclass & (e_PLAYER_CLASS_AFTER_RETURN | e_PLAYER_CLASS_EVER));
	if (playerclass & (e_PLAYER_CLASS_SPAWNED | e_PLAYER_CLASS_RETURN))
	{
		playerclass = e_PLAYER_CLASS_SKIN;
	}
	else
	{
		playerclass &= e_PLAYER_CLASS_SKIN;
	}
	if (!YSI_g_sClassCount)
	{
		SetSpawnInfo(playerid, NO_TEAM, 0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
		SetPlayerSkin(playerid, 0);
		P:E("No YSI classes found");
	}
	else
	{
		// Find the next available skin for this player.  I'm still not sure how
		// this handles the case where you can't use any skin.  I'll have to
		// look in to that.
		playerclass = Class_FindNew(playerid, playerclass, dir);
		P:5("Class_OnPlayerRequestClass() selected: %d", playerclass);
	}
	//Class_ResumeRefresh(playerid);
	YSI_g_sClassOptions &= ~(e_CLASS_OPTION_REFRESH_PAUSE | e_CLASS_OPTION_PAUSED);
	return Class_Goto(playerid, _:playerclass);
	//ALS_CALL_EX<PlayerRequestClass, ret>
}

foreign Class_Goto(playerid, playerclass);
global Class_Goto(playerid, playerclass)
{
	P:2("Class_Goto called: %i, %i", playerid, playerclass);
	// This now sets the REAL spawn information, including spawn location.
	// 0.2 code
	//SetSpawnInfo(playerid, NO_TEAM, Class_Skin(e_PLAYER_CLASS:playerclass), Class_X(e_PLAYER_CLASS:playerclass), Class_Y(e_PLAYER_CLASS:playerclass), Class_Z(e_PLAYER_CLASS:playerclass), Class_A(e_PLAYER_CLASS:playerclass), weapon1 & 0xFF, weapon1 >>> 8, weapon2 & 0xFF, weapon2 >>> 8, weapon3 & 0xFF, weapon3 >>> 8);
	// 0.3 code
	SetSpawnInfo(playerid, NO_TEAM, Class_Skin(e_PLAYER_CLASS:playerclass), Class_X(e_PLAYER_CLASS:playerclass), Class_Y(e_PLAYER_CLASS:playerclass), Class_Z(e_PLAYER_CLASS:playerclass), Class_A(e_PLAYER_CLASS:playerclass), 0, 0, 0, 0, 0, 0);
	SetPlayerSkin(playerid, Class_Skin(e_PLAYER_CLASS:playerclass));
	YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & (e_PLAYER_CLASS_PRESS | e_PLAYER_CLASS_EVER | e_PLAYER_CLASS_AFTER_RETURN)) | e_PLAYER_CLASS:playerclass | e_PLAYER_CLASS_SELECT;
	// Save the last viewed class so that we know which direction the person
	// went next time OnPlayerRequestClass is called.
	P:2("Class_Goto() end");
	// Call the OnPlayerRequestClassEx functions.
	YSI_gOPRCE = false;
	CallRemoteFunction("OnPlayerRequestClassEx_", "ii", playerid, playerclass);
	if (YSI_g_sClassOptions & e_CLASS_OPTION_HAS_RC_CALLBACK)
	{
		YSI_gOPRCE = true;
		return CallLocalFunction("OnPlayerRequestClassEx_", "ii", playerid, playerclass);
	}
	return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_OnPlayerConnect
Params:
	playerid - Player who joined.
Return:
	-
Notes:
	Resets the player's current class.
\*----------------------------------------------------------------------------*/

mhook OnPlayerConnect(playerid)
{
	P:2("Class_OnPlayerConnect called: %d", playerid);
	//P:2("Class_OnPlayerConnect called");
	YSI_g_sPlayerClass[playerid] = e_PLAYER_CLASS_SKIN;
	if (YSI_g_sClassOptions & e_CLASS_OPTION_LOGIN_SELECT)
	{
		Class_DenySelection(playerid);
	}
	return 1;
}

mhook OnPlayerLogin(playerid, yid)
{
	if (YSI_g_sClassOptions & e_CLASS_OPTION_LOGIN_SELECT)
	{
		Class_ReturnToSelection(playerid);
	}
	return 1;
}

foreign Class_ReturnToSelection(playerid);
global Class_ReturnToSelection(playerid)
{
	P:2("Class_ReturnToSelection called: %i", playerid);
	// All of these lines are required to correctly send the player back to the
	// class selection, unfortunately they also cause nasty side effects.
	//TogglePlayerControllable(playerid, true);
	// if (YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_EVER)
	// {
		// //TogglePlayerControllable(playerid, true);
		// //YSI_g_sPlayerClass[playerid] &= e_PLAYER_CLASS_SPAWNED;
		// //SetPlayerHealth(playerid, 0.0);
		// ForceClassSelection(playerid);
		// SetPlayerHealth(playerid, 0.0);
		// TogglePlayerControllable(playerid, false);
	// }
	// else
	// {
		// TogglePlayerSpectating(playerid, false);
		ForceClassSelection(playerid);
		SetPlayerHealth(playerid, 0.0);
	// }
//	ForceClassSelection(playerid);
	TogglePlayerSpectating(playerid, false);
//	SetPlayerHealth(playerid, 0.0);
	// TogglePlayerControllable(playerid, true);
	//ForceClassSelection(playerid);
	//YSI_g_sPlayerClass[playerid] &= ~(e_PLAYER_CLASS_DENY | e_PLAYER_CLASS_SPAWNED);
//	TogglePlayerControllable(playerid, true);
	//YSI_g_sPlayerClass[playerid] &= e_PLAYER_CLASS_SPAWNED;
	//ForceClassSelection(playerid);
	//SetPlayerHealth(playerid, 0.0);
	//TogglePlayerControllable(playerid, false);
	//YSI_g_sPlayerClass[playerid] = YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_PRESS | e_PLAYER_CLASS_SKIN;
//	Class_Goto(playerid, Class_FindNew(playerid, e_PLAYER_CLASS_SKIN, CLASS_MOVE_RIGHT));
	//YSI_g_sPlayerClass[playerid] |= e_PLAYER_CLASS_RETURN | e_PLAYER_CLASS_AFTER_RETURN;
	YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] | e_PLAYER_CLASS_RETURN | e_PLAYER_CLASS_AFTER_RETURN) & ~(e_PLAYER_CLASS_DENY | e_PLAYER_CLASS_SPAWNED);
	//YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] | e_PLAYER_CLASS_RETURN) & ~e_PLAYER_CLASS_SPAWNED;
	return 1;
}

foreign Class_DenySelection(playerid);
global Class_DenySelection(playerid)
{
	P:2("Class_DenySelection called: %i", playerid);
	//SpawnPlayer(playerid);
	TogglePlayerControllable(playerid, false);
	TogglePlayerSpectating(playerid, true);
	SetSpawnInfo(playerid, 0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	// "e_PLAYER_CLASS_DENY" is unset by not being re-set in "Class_Goto".
	YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] | e_PLAYER_CLASS_DENY) & ~e_PLAYER_CLASS_SELECT;
	//ForceClassSelection
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_OnPlayerDeath
Params:
	playerid - Player who dies.
	reason - The reason they died.
Return:
	-1 on fake deaths.
Notes:
	Catches and hides fake deaths caused by the spawn system.  Called first.
\*----------------------------------------------------------------------------*/

// We need this definition as we are using "mhook" instead of "hook", which
// can't handle the extra number used to force a call order.
//#define ALS_R_PlayerDeath0 ALS_R_PlayerDeath
hook OnPlayerDeath0(playerid, killerid, reason)
{
	// For consistency all scripts return -1 if the class system thinks this is
	// a fake death caused by the weird respawn selection system.
	if (YSI_g_sIsFirst)
	{
		new
			ret = Class_DoPlayerDeath(playerid, killerid, reason);
		setproperty(8, YSIM_OPDRET, ret);
		return ret;
	}
	return getproperty(8, YSIM_OPDRET);
}

foreign Class_DoPlayerDeath(playerid, killerid, reason);

global Class_DoPlayerDeath(playerid, killerid, reason)
{
	P:2("Class_OnPlayerDeath called: %d, %d, %d", playerid, killerid, reason);
	#pragma unused killerid, reason
	P:2("Class_OnPlayerDeath called");
	//new
	//	time = GetTickCount();
	//new
	//	e_PLAYER_CLASS:playerclass = YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN;
	//SetSpawnInfo(playerid, NO_TEAM, Class_Skin(e_PLAYER_CLASS:playerclass), Class_X(e_PLAYER_CLASS:playerclass), Class_Y(e_PLAYER_CLASS:playerclass), Class_Z(e_PLAYER_CLASS:playerclass), Class_A(e_PLAYER_CLASS:playerclass), 0, 0, 0, 0, 0, 0);
	//return -1;
	//if ((YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SPAWN_CHECK) == e_PLAYER_CLASS_SPAWN_CHECK)// || (time - YSI_g_sLastRefuse[playerid]) < 200)
	if ((YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_AFTER_RETURN) == e_PLAYER_CLASS_AFTER_RETURN)// || (time - YSI_g_sLastRefuse[playerid]) < 200)
	{
		P:2("Class_OnPlayerDeath: Inner");
		new
			e_PLAYER_CLASS:playerclass = YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN;
		// Fake death to get the ForceClassSelection out the system.
		//SetTimerEx("_Class_DoRespawn", 0, 0, "i", playerid);
		//SetPlayerHealth(playerid, 100.0);
		if ((YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_TEMP_SPAWN) == e_PLAYER_CLASS_TEMP_SPAWN)
		{
			SetSpawnInfo(playerid, NO_TEAM, Class_Skin(e_PLAYER_CLASS:playerclass), Class_X(e_PLAYER_CLASS:playerclass), Class_Y(e_PLAYER_CLASS:playerclass), Class_Z(e_PLAYER_CLASS:playerclass), Class_A(e_PLAYER_CLASS:playerclass), 0, 0, 0, 0, 0, 0);
			SpawnPlayer(playerid);
			YSI_g_sPlayerClass[playerid] &= ~(e_PLAYER_CLASS_AFTER_RETURN | e_PLAYER_CLASS_TEMP_SPAWN);
		}
		//YSI_g_sLastRefuse[playerid] = time;
		// Cancel all other callbacks.
		return -1;
	}
	//TogglePlayerControllable(playerid, false);
	if (YSI_g_sClassOptions & e_CLASS_OPTION_NORE)
	{
		/*new
			e_PLAYER_CLASS:playerclass = YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN;
		SetSpawnInfo(playerid, NO_TEAM, Class_Skin(e_PLAYER_CLASS:playerclass), Class_X(e_PLAYER_CLASS:playerclass), Class_Y(e_PLAYER_CLASS:playerclass), Class_Z(e_PLAYER_CLASS:playerclass), Class_A(e_PLAYER_CLASS:playerclass), 0, 0, 0, 0, 0, 0);
		SpawnPlayer(playerid);
		SetPlayerHealth(playerid, 100.0);*/
		SetTimerEx("_Class_DoRespawn", 2500, 0, "i", playerid);
		//ForceClassSelection(playerid);
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_OnPlayerSpawn
Params:
	playerid - Player who spawned.
Return:
	-
Notes:
	Sets a player's position based on skin.
\*----------------------------------------------------------------------------*/

mhook OnPlayerSpawn(playerid)
{
	P:2("Class_OnPlayerSpawn called: %d", playerid);
	//P:2("Class_OnPlayerSpawn called: %d %d", YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_AFTER_RETURN, e_PLAYER_CLASS_AFTER_RETURN);
	if (YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_AFTER_RETURN)
	{
		// Fake spawn.
		//SetPlayer
		YSI_g_sPlayerClass[playerid] |= e_PLAYER_CLASS_TEMP_SPAWN;
		return -1;
	}
	YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] | e_PLAYER_CLASS_SPAWNED | e_PLAYER_CLASS_EVER) & ~e_PLAYER_CLASS_SELECT;
	new
		playerclass = YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN,
		weapon;
	for (new i = 0; i != MAX_CLASS_SPAWN_WEAPONS; ++i)
	{
		weapon = YSI_g_sClasses[playerclass][E_CLASS_WEAPONS][i];
		//if (weapon == WEAPON_ARMOUR) SetPlayerArmour(playerid, 100.0);
		if (weapon)
		{
			GivePlayerWeapon(playerid, weapon & 0xFF, weapon >>> 8);
		}
		else
		{
			break;
		}
	}
	weapon = YSI_g_sClasses[playerclass][E_CLASS_WEAPONS][MAX_CLASS_SPAWN_WEAPONS];
	P:5("Class_OnPlayerSpawn: Armour %d %d %d", weapon, weapon & 0xFF, WEAPON_ARMOUR);
	if ((weapon & 0xFF) == WEAPON_ARMOUR)
	{
		weapon >>>= 8;
		if (weapon == 0x00800000)
		{
			// INFINITY
			SetPlayerArmour(playerid, Float:0x7F800000);
		}
		else
		{
			SetPlayerArmour(playerid, weapon);
		}
	}
	/*if (YSI_g_sClassOptions & e_CLASS_OPTION_NORE)
	{
		// Yes, if they're NOT allowed to change class, send them back to class
		// selection!  This is so the message doesn't appear.
		ForceClassSelection(playerid);
	}*/
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_Add
Params:
	skin - Skin of the class.
	Float:x - X spawn location.
	Float:y - Y spawn location.
	Float:z - Z spawn location.
	Float:a - A spawn location.
	... - Spawn weapons and ammo (weapon then ammo)
Return:
	-
Notes:
	Pretty much AddPlayerClass but allows greater control over the classes.
	Now has infinate (MAX_CLASS_SPAWN_WEAPONS) spawn weapons.  This is one of
	the few API functions which is not entirely remote.  This is because it has
	variable parameters which is need to collect in to a single array to pass to
	the remote function.
\*----------------------------------------------------------------------------*/

stock Class_Add(skin, Float:x, Float:y, Float:z, Float:a, ...)
{
	P:3("Class_Add called: %i, %i, %i, %i, %i, %i (+%i)", skin, x, y, z, a, numargs() - 5);
	new
		n = numargs(),
		w = 5,
		s,
		weapons[MAX_CLASS_SPAWN_WEAPONS + 1],
		cw;
	_CLASS_WEAPON_CODE
	return Class_AddClass(skin, x, y, z, a, weapons, MAX_CLASS_SPAWN_WEAPONS + 1, Group:-1, Group:-1);
}

/*----------------------------------------------------------------------------*\
Function:
	Class_AddEx
Params:
	forgroup - Group that can use the skin.
	setgroup - Group to add the player to on selection.
	skin - Skin of the class.
	Float:x - X spawn location.
	Float:y - Y spawn location.
	Float:z - Z spawn location.
	Float:a - A spawn location.
	... - Spawn weapons and ammo (weapon then ammo)
Return:
	-
Notes:
	Pretty much AddPlayerClass but allows greater control over the classes.
	Now has infinate (MAX_CLASS_SPAWN_WEAPONS) spawn weapons.
\*----------------------------------------------------------------------------*/

stock Class_AddEx(Group:forgroup, Group:setgroup, skin, Float:x, Float:y, Float:z, Float:a, ...)
{
	P:3("Class_AddEx called: %i, %i, %i, %f, %f, %f, %f (+%i)", _:forgroup, _:setgroup, skin, x, y, z, a, numargs() - 7);
	new
		n = numargs(),
		w = 7,
		s,
		weapons[MAX_CLASS_SPAWN_WEAPONS + 1],
		cw;
	_CLASS_WEAPON_CODE
	return Class_AddClass(skin, x, y, z, a, weapons, MAX_CLASS_SPAWN_WEAPONS + 1, forgroup, setgroup);
}

/*----------------------------------------------------------------------------*\
Function:
	Class_AddClass
Params:
	skin - Skin of the class.
	Float:x - X spawn location.
	Float:y - Y spawn location.
	Float:z - Z spawn location.
	Float:a - A spawn location.
	weapons[] - Array of spawn weapon data.
	count - Number of weapons added.
	forgroup - Group that can use the class.
	asgroup - Group to assign people to with this class.
Return:
	-
Notes:
	Does the hard work.  This took a long time to get working correctly with the
	new master system, infact getting just this one function to compile took a
	major re-working of the macros to reduce the length of intermediate stages.
\*----------------------------------------------------------------------------*/

foreign Class_AddClass(s,Float:x,Float:y,Float:z,Float:a,w[],c,Group:f,Group:g);
global Class_AddClass(s,Float:x,Float:y,Float:z,Float:a,w[],c,Group:f,Group:g)
{
	P:2("Class_AddClass called: %i, %f, %f, %f, %f, %a, %i, %i, %i", s, x, y, z, a, w, c, _:f, _:g);
	new
		i;
	while (i < MAX_CLASSES)
	{
		if (!Class_IsActive(i)) break;
		i++;
	}
	if (i == MAX_CLASSES) return -1;
	YSI_g_sClasses[i][E_CLASS_FLAGS] = 	e_CLASS_FLAGS_ACTIVE | e_CLASS_FLAGS_ENABLED | e_CLASS_FLAGS:s;
	YSI_g_sClasses[i][E_CLASS_X] = x;
	YSI_g_sClasses[i][E_CLASS_Y] = y;
	YSI_g_sClasses[i][E_CLASS_Z] = z;
	YSI_g_sClasses[i][E_CLASS_A] = a;
	new
		j;
	// This may be better with a memcpy.
	while (j < c)
	{
		P:5("Class_AddClass: weapon %d %d %d", j, c, w[j]);
		YSI_g_sClasses[i][E_CLASS_WEAPONS][j] = w[j];
		++j;
	}
	//Bit_SetAll(YSI_g_sClasses[class][E_CLASS_PLAYERS], false, bits<MAX_PLAYERS>);
	PA_FastInit(YSI_g_sClasses[i][E_CLASS_PLAYERS]);
	Class_ResolveGroups(i, f, false);
	YSI_g_sClasses[i][E_CLASS_GROUP] = g;
	//YSI_g_sClasses[i][E_CLASS_WEAPONS][MAX_CLASS_SPAWN_WEAPONS] = w[MAX_CLASS_SPAWN_WEAPONS];
	YSI_g_sClassCount++;
	//setproperty(0, "LReqClass", i);
	//#if !defined YSI_CLASS_INVERT
	//	Bit_SetAll(YSI_g_sClasses[i][E_CLASS_PLAYERS], true, bits<MAX_PLAYERS>);
	//#endif
	return i;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_AddForGroup
Params:
	group - Group to allow to use the class.
	skin - Skin of the class.
	Float:x - X spawn location.
	Float:y - Y spawn location.
	Float:z - Z spawn location.
	Float:a - A spawn location.
	... - Weapon data.
Return:
	-
Notes:
	Adds a class only people in the specified group can use.
\*----------------------------------------------------------------------------*/

//#if defined _YSI_SYSTEM_GROUPS
	stock Class_AddForGroup(Group:group, skin, Float:x, Float:y, Float:z, Float:a, ...)
	{
		P:3("Class_AddForGroup called: %i, %i, %f, %f, %f, %f (+%i)", _:group, skin, x, y, z, a, numargs() - 6);
		new
			n = numargs(),
			w = 6,
			s,
			weapons[MAX_CLASS_SPAWN_WEAPONS + 1],
			cw;
		_CLASS_WEAPON_CODE
		return Class_AddClass(skin, x, y, z, a, weapons, MAX_CLASS_SPAWN_WEAPONS + 1, group, Group:-1);
	}
/*#else
	#define Class_AddForGroup(%1,%2) \
		Class_Add(%2)
#endif*/

/*----------------------------------------------------------------------------*\
Function:
	Class_AddWithGroupSet
Params:
	group - Group to make players who use this group.
	skin - Skin of the class.
	Float:x - X spawn location.
	Float:y - Y spawn location.
	Float:z - Z spawn location.
	Float:a - A spawn location.
	... - Spawn weapons.
Return:
	-
Notes:
	Adds a class which puts you in the specified group when selected.
\*----------------------------------------------------------------------------*/

//#if defined _YSI_SYSTEM_GROUPS
	stock Class_AddWithGroupSet(Group:group, skin, Float:x, Float:y, Float:z, Float:a, ...)
	{
		P:3("Class_AddWithGroupSet called: %i, %i, %f, %f, %f, %f (+%i)", _:group, skin, x, y, z, a, numargs() - 6);
		new
			n = numargs(),
			w = 6,
			s,
			weapons[MAX_CLASS_SPAWN_WEAPONS + 1],
			cw;
		_CLASS_WEAPON_CODE
		return Class_AddClass(skin, x, y, z, a, weapons, MAX_CLASS_SPAWN_WEAPONS + 1, Group:-1, group);
	}
/*#else
	#define Class_AddWithGroupSet(%1,%2) \
		Class_Add(%2)
#endif*/

/*----------------------------------------------------------------------------*\
Function:
	Class_Enable
Params:
	classid - Class to re-enable.
Return:
	-
Notes:
	Reallow use of this class.
\*----------------------------------------------------------------------------*/

foreign Class_Enable(classid);
global Class_Enable(classid)
{
	P:2("Class_Enable called: %i", classid);
	if (Class_IsValid(classid)) YSI_g_sClasses[classid][E_CLASS_FLAGS] |= e_CLASS_FLAGS_ENABLED;
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_Disable
Params:
	classid - Class to disable.
Return:
	-
Notes:
	Stop people being able to use this class.
\*----------------------------------------------------------------------------*/

foreign Class_Disable(classid);
global Class_Disable(classid)
{
	P:2("Class_Disable called: %i", classid);
	if (Class_IsValid(classid))
	{
		YSI_g_sClasses[classid][E_CLASS_FLAGS] &= ~e_CLASS_FLAGS_ENABLED;
		foreach (new playerid : Player)
		{
			new
				e_PLAYER_CLASS:curclass = YSI_g_sPlayerClass[playerid];
			if (curclass & e_PLAYER_CLASS_SELECT)
			{
				if (e_PLAYER_CLASS:classid == curclass & e_PLAYER_CLASS_SKIN) Class_Goto(playerid, Class_FindNew(playerid, e_PLAYER_CLASS:classid, CLASS_MOVE_RIGHT));
			}
		}
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_Remote
Params:
	allow - Wether or not to allow changing class.
Return:
	-
Notes:
	Sets wether or not people can change class after first spawning.
\*----------------------------------------------------------------------------*/

foreign Class_AllowReselection(allow);
global Class_AllowReselection(allow)
{
	P:2("Class_AllowReselection called: %i", allow);
	if (allow)
	{
		YSI_g_sClassOptions &= ~e_CLASS_OPTION_NORE;
	}
	else
	{
		YSI_g_sClassOptions |= e_CLASS_OPTION_NORE;
		/*foreach (new playerid : Player)
		{
			// So they can't see any message if they press F4.
			ForceClassSelection(playerid);
		}*/
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_Delete
Params:
	classid - Class to delete.
Return:
	-
Notes:
	Completely removes a class from the system.
\*----------------------------------------------------------------------------*/

foreign Class_Delete(classid);
global Class_Delete(classid)
{
	P:2("Class_Delete called: %i", classid);
	if (Class_IsValid(classid))
	{
		YSI_g_sClasses[classid][E_CLASS_FLAGS] = e_CLASS_FLAGS:0;
		foreach (new playerid : Player)
		{
			new
				e_PLAYER_CLASS:curclass = YSI_g_sPlayerClass[playerid];
			P:4("Class_Delete: %d %d %d", playerid, curclass, e_PLAYER_CLASS_SELECT);
			if (curclass & e_PLAYER_CLASS_SELECT)
			{
				if (e_PLAYER_CLASS:classid == curclass & e_PLAYER_CLASS_SKIN) Class_Goto(playerid, Class_FindNew(playerid, e_PLAYER_CLASS:classid, CLASS_MOVE_RIGHT));
			}
		}
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_SetPlayer
Params:
	classid - Class to set permissions for.
	playerid - Player to set for.
	set - Whether or not they can use this class.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign Class_SetPlayer(cl, pid, bool:s);

global Class_SetPlayer(cl, pid, bool:s)
{
	P:2("Class_SetPlayer called: %i, %i, %i", cl, pid, s);
	P:5("Class_SetPlayer %d %d %d", cl, pid, s);
	if (Class_IsValid(cl) && 0 <= pid < MAX_PLAYERS)
	{
		if (s) PA_Let(YSI_g_sClasses[cl][E_CLASS_PLAYERS], pid);
		else
		{
			PA_Vet(YSI_g_sClasses[cl][E_CLASS_PLAYERS], pid);
			if (!Class_IsPaused(pid))
			{
				new
					e_PLAYER_CLASS:curclass = YSI_g_sPlayerClass[pid];
				if (curclass & e_PLAYER_CLASS_SELECT)
				{
					if (e_PLAYER_CLASS:cl == curclass & e_PLAYER_CLASS_SKIN) Class_Goto(pid, Class_FindNew(pid, e_PLAYER_CLASS:cl, CLASS_MOVE_RIGHT));
				}
			}
		}
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_GetPlayer
Params:
	classid - Class to set permissions for.
	playerid - Player to set for.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign bool:Class_GetPlayer(cl,pid);

global bool:Class_GetPlayer(cl,pid)
{
	P:2("bool:Class_GetPlayer called: %i, %i", cl, pid);
	if (Class_IsValid(cl) && 0 <= pid < MAX_PLAYERS)
	{
		return PA_Get(YSI_g_sClasses[cl][E_CLASS_PLAYERS], pid);
	}
	return false;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_RequireSelectionLogin
Params:
	allow - Wether or not people must login.
Return:
	-
Notes:
	Don't let registered people select a class till they log in.
\*----------------------------------------------------------------------------*/

foreign Class_RequireSelectionLogin(allow);

global Class_RequireSelectionLogin(allow)
{
	P:2("Class_RequireSelectionLogin called: %i", allow);
	if (allow) YSI_g_sClassOptions |= e_CLASS_OPTION_LOGIN_SELECT;
	else YSI_g_sClassOptions &= ~e_CLASS_OPTION_LOGIN_SELECT;
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_RequireSpawnLogin
Params:
	allow - Wether or not people must login.
Return:
	-
Notes:
	Don't let registered people spawn till they log in.
\*----------------------------------------------------------------------------*/

foreign Class_RequireSpawnLogin(allow);

global Class_RequireSpawnLogin(allow)
{
	P:2("Class_RequireSpawnLogin called: %i", allow);
	if (allow) YSI_g_sClassOptions |= e_CLASS_OPTION_LOGIN_SPAWN;
	else YSI_g_sClassOptions &= ~e_CLASS_OPTION_LOGIN_SPAWN;
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Class_RequireSelectionReg
Params:
	allow - Wether or not people must register.
Return:
	-
Notes:
	Don't let people select a class till they register.
\*----------------------------------------------------------------------------*/

foreign Class_RequireSelectionReg(allow);

global Class_RequireSelectionReg(allow)
{
	P:2("Class_RequireSelectionReg called: %i", allow);
	if (allow) YSI_g_sClassOptions |= e_CLASS_OPTION_REG_SELECT;
	else YSI_g_sClassOptions &= ~e_CLASS_OPTION_REG_SELECT;
	return 1;
}

#define Class_RequireSelectionRegistration Class_RequireSelectionReg

/*----------------------------------------------------------------------------*\
Function:
	Class_RequireSpawnReg
Params:
	allow - Wether or not people must register.
Return:
	-
Notes:
	Don't let people spawn till they register.
\*----------------------------------------------------------------------------*/

foreign Class_RequireSpawnReg(allow);

global Class_RequireSpawnReg(allow)
{
	P:2("Class_RequireSpawnReg called: %i", allow);
	if (allow) YSI_g_sClassOptions |= e_CLASS_OPTION_REG_SPAWN;
	else YSI_g_sClassOptions &= ~e_CLASS_OPTION_REG_SPAWN;
	return 1;
}

#define Class_RequireSpawnRegistration Class_RequireSpawnReg

// Clean up - there's no way to do this like in the master system as people can
// use any arbitrary string here, not just a restricted set of numbers.

//#define YSI_SET_LAST_GROUP 22	
#include "internal\y_grouprevert"
