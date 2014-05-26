/**--------------------------------------------------------------------------**\
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
	14/04/12:
		Readded OnRequestSpawn logic.
		Fixed Class_AddWithGroupSet.
		Improved GM/FS interaction.
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
		_Class_IsActive - Checks a class is active.
		_Class_Enabled - Checks a class is enabled.
		_Class_IsValid - Checks a class is valid.
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
\**--------------------------------------------------------------------------**/

PRE_HOOK(Class)

forward Class_ResolveGroups(class, Group:forgroup, bool:cp);

enum e_CLASS_FLAGS (<<= 1)
{
	e_CLASS_FLAGS_SKIN    = 0x0000FFFF,
	e_CLASS_FLAGS_ENABLED = 0x00010000,
	e_CLASS_FLAGS_ACTIVE
}

enum E_CLASS
{
	e_CLASS_FLAGS:E_CLASS_FLAGS,
	Float:E_CLASS_X,
	Float:E_CLASS_Y,
	Float:E_CLASS_Z,
	Float:E_CLASS_A,
	E_CLASS_WEAPONS[MAX_CLASS_SPAWN_WEAPONS + 1],
	Group:E_CLASS_GROUP,
	PlayerArray:E_CLASS_PLAYERS<MAX_PLAYERS>
}

enum e_PLAYER_CLASS (<<= 1)
{
	e_PLAYER_CLASS_NONE  = 0,
	e_PLAYER_CLASS_SKIN  = 0x000FFFFF,
	e_PLAYER_CLASS_PRESS = 0x00700000,
	e_PLAYER_CLASS_RIGHT = 0x00100000,
	e_PLAYER_CLASS_MIDDLE,
	e_PLAYER_CLASS_LEFT
}

#define CLASS_MOVE_LEFT                 (-1)
#define CLASS_MOVE_RIGHT                (1)
#define CLASS_MOVE_NONE                 (0)

static stock
	YSI_g_sClasses[MAX_CLASSES][E_CLASS],
	e_PLAYER_CLASS:YSI_g_sPlayerClass[MAX_PLAYERS],
	YSI_g_sLeft,
	YSI_g_sMiddle,
	YSI_g_sRight,
	YSI_g_sClassCount,
	YSI_g_sLastRefuse[MAX_PLAYERS];

stock Class_ResolveGroups(class, Group:forgroup, bool:cp) <YSI_has_groups : n>
{
	#pragma unused forgroup
	P:2("Class_ResolveGroups<n>: call Resolve %d %d %d", class, _:forgroup, cp);
	if (!cp) PA_Init(YSI_g_sClasses[class][E_CLASS_PLAYERS], true);
}

stock Class_ResolveGroups(class, Group:forgroup, bool:cp) <>
{
	#pragma unused forgroup
	P:2("Class_ResolveGroups<>: call Resolve %d %d %d", class, _:forgroup, cp);
	if (!cp) PA_Init(YSI_g_sClasses[class][E_CLASS_PLAYERS], true);
}

/**--------------------------------------------------------------------------**\
<summary>_Class_IsActive</summary>
<param name="classid">Class to check if active.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define _Class_IsActive(%1) (YSI_g_sClasses[(%1)][E_CLASS_FLAGS] & e_CLASS_FLAGS_ACTIVE)

/**--------------------------------------------------------------------------**\
<summary>_Class_IsValid</summary>
<param name="classid">Class to check if valid.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define _Class_IsValid(%1) (IS_IN_RANGE((%1), 0, MAX_CLASSES) && _Class_IsActive(%1))

/**--------------------------------------------------------------------------**\
<summary>_Class_Enabled</summary>
<param name="classid">Class to check.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define _Class_Enabled(%1) (YSI_g_sClasses[(%1)][E_CLASS_FLAGS] & e_CLASS_FLAGS_ENABLED)

/**--------------------------------------------------------------------------**\
<summary>Class_X</summary>
<param name="classid">Class to get X location for.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Class_X(%1) YSI_g_sClasses[(%1)][E_CLASS_X]

/**--------------------------------------------------------------------------**\
<summary>Class_Y</summary>
<param name="classid">Class to get Y location for.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Class_Y(%1) YSI_g_sClasses[(%1)][E_CLASS_Y]

/**--------------------------------------------------------------------------**\
<summary>Class_Z</summary>
<param name="classid">Class to get Z location for.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Class_Z(%1) YSI_g_sClasses[(%1)][E_CLASS_Z]

/**--------------------------------------------------------------------------**\
<summary>Class_A</summary>
<param name="classid">Class to get angle for.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Class_A(%1) YSI_g_sClasses[(%1)][E_CLASS_A]

/**--------------------------------------------------------------------------**\
<summary>Class_Skin</summary>
<param name="classid">Class to get skin for.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Class_Skin(%1) (YSI_g_sClasses[(%1)][E_CLASS_FLAGS] & e_CLASS_FLAGS_SKIN)

/**--------------------------------------------------------------------------**\
<summary>Class_Class</summary>
<returns>
	-
</returns>
<remarks>
	Creates three real player classes so you can scroll correctly with the
	direction being detected.
</remarks>
\**--------------------------------------------------------------------------**/

hook OnScriptInit()
{
	#if !_YSIM_IS_CLIENT
		if (!YSI_FILTERSCRIPT)
		{
			// This code placement is not generic.
			YSI_g_sLeft = AddPlayerClass(0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
			YSI_g_sMiddle = AddPlayerClass(0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
			YSI_g_sRight = AddPlayerClass(0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
			//printf("==========================");
			P:4("Class_OnScriptInit: classes = %d %d %d", YSI_g_sLeft, YSI_g_sMiddle, YSI_g_sRight);
			//printf("==========================");
			#if !defined YSI_NO_MASTER
				// Steal the master system.
				_Master_Get(#_YCM, true);
				#if _YSIM_IS_CLOUD
					// Set to uninitialised.
					state _YCM:u;
					//_YCM = _YCM@u;
					_YCM@ = _E_YCM@u;
				#endif
				CallRemoteFunction(#_YCM, "");
				#if _YSIM_IS_CLOUD
					// Fully master.
					state _YCM:y;
					//_YCM = _YCM@y;
					_YCM@ = _E_YCM@y;
				#endif
			#endif
		}
	#endif
	return 1;
}

static stock Class_FindNew(playerid, playerclass, dir)
{
	P:4("Class_FindNew called: %i, %i, %i", playerid, playerclass, dir);
	// Handles the special case where "dir" = 0 very nicely with no extra code
	// slowing down the common case (as it should be)!  This is simply because
	// "playerclass != old" will fail on the first loop with "+ 0";
	new
		old = playerclass % YSI_g_sClassCount;
	do
	{
		playerclass = (playerclass + dir) % YSI_g_sClassCount;
		P:4("Class_FindNew: %d %d", playerclass, playerid);
	}
	while (playerclass != old && (!_Class_Enabled(playerclass) || !PA_Get(YSI_g_sClasses[playerclass][E_CLASS_PLAYERS], playerid)));
	// (!(playerclass == old || (_Class_Enabled(playerclass) && PA_Get(YSI_g_sClasses[playerclass][E_CLASS_PLAYERS], playerid))))
	return playerclass;
}

/**--------------------------------------------------------------------------**\
<summary>Class_OnPlayerRequestClass</summary>
<param name="playerid">Player who requested a class.</param>
<param name="class">Class they requested.</param>
<returns>
	-
</returns>
<remarks>
	The input is one of the three real classes used to detect selected
	direction of alteration.  Scans for a class the player is allowed to use
	and hot swaps it out.  Uses SetPlayerSkin AND SetSpawnInfo to combat bugs
	with calling this from OnPlayerRequestSpawn (e.g. the example team script).
	Calls OnPlayerRequestClassEx with the current internal class not the real
	one.
</remarks>
\**--------------------------------------------------------------------------**/

// Pre-empt y_hooks.
#if !defined YSI_NO_MASTER && _YSIM_IS_CLIENT
	public OnPlayerRequestClass(playerid, classid)
	{
		return 1;
	}
#else
	#if !defined YSI_NO_MASTER && _YSIM_IS_CLOUD
		public OnPlayerRequestClass(playerid, classid) <>
		{
			return 1;
		}
		
		public OnPlayerRequestClass(playerid, classid) <_YCM:y>
	#else
		public OnPlayerRequestClass(playerid, classid)
	#endif
		{
			P:1("_Class_OnPlayerRequestClass called: %d %d", playerid, classid);
			new
				dir = CLASS_MOVE_RIGHT;
			// Spawned from returning to class selection but not meant to.
			// Find which direction they pressed.
			switch (YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_PRESS)
			{
				case e_PLAYER_CLASS_RIGHT:
				{
					if (classid == YSI_g_sMiddle)
					{
						// Went from the right to the middle - that's a move left.
						dir = CLASS_MOVE_LEFT;
					}
					else if (classid != YSI_g_sLeft)
					{
						dir = CLASS_MOVE_NONE;
					}
				}
				case e_PLAYER_CLASS_MIDDLE:
				{
					if (classid == YSI_g_sLeft)
					{
						// Went from the middle to the left - that's a move left.
						dir = CLASS_MOVE_LEFT;
					}
					else if (classid != YSI_g_sRight)
					{
						dir = CLASS_MOVE_NONE;
					}
				}
				default:
				{
					if (classid == YSI_g_sRight)
					{
						// Went from the left to the right - that's a wrap move left.
						dir = CLASS_MOVE_LEFT;
					}
					else if (classid != YSI_g_sMiddle)
					{
						dir = CLASS_MOVE_NONE;
					}
				}
			}
			// Store which class they are now on.
			if (classid == YSI_g_sMiddle)
			{
				YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~e_PLAYER_CLASS_PRESS) | e_PLAYER_CLASS_MIDDLE;
			}
			else if (classid == YSI_g_sLeft)
			{
				YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~e_PLAYER_CLASS_PRESS) | e_PLAYER_CLASS_LEFT;
			}
			else if (classid == YSI_g_sRight)
			{
				YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~e_PLAYER_CLASS_PRESS) | e_PLAYER_CLASS_RIGHT;
			}
			P:C(else {P:E("y_classes unidentified classid.");YSI_g_sPlayerClass[playerid] = e_PLAYER_CLASS_NONE;});
			classid = (YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN);
			if (YSI_g_sClassCount)
			{
				// Find the next available skin for this player.  I'm still not sure how
				// this handles the case where you can't use any skin.  I'll have to
				// look in to that.
				// Don't want to get stuck constantly adding "0".
				classid = Class_FindNew(playerid, classid, dir);
				P:5("Class_OnPlayerRequestClass() selected: %d", classid);
				Class_Goto(playerid, _:classid);
			}
			else
			{
				SetSpawnInfo(playerid, NO_TEAM, 0, 1958.0, 1343.0, 15.0, 269.0, 0, 0, 0, 0, 0, 0);
				SetPlayerSkin(playerid, 0);
				P:E("No YSI classes found");
				classid = -1;
			}
			// Now sort out if they actually should be spawned.
			if (YSI_g_sPlayerClass[playerid] & (e_PLAYER_CLASS_RETURNED | e_PLAYER_CLASS_SPAWNSINCE) == (e_PLAYER_CLASS_RETURNED | e_PLAYER_CLASS_SPAWNSINCE))
			{
				YSI_g_sPlayerClass[playerid] &= ~(e_PLAYER_CLASS_RETURNED | e_PLAYER_CLASS_SPAWNSINCE);
				Class_Spectate(playerid);
				SetTimerEx("_Class_SpawnPlayer2", 10, 0, "i", playerid);
				CallRemoteFunction("_Class_OtherRequestClass", "ii", playerid, -1);
			}
			else if (YSI_g_sPlayerClass[playerid] & (e_PLAYER_CLASS_RETURNED | e_PLAYER_CLASS_DISABLED | e_PLAYER_CLASS_HADFIRST) == (e_PLAYER_CLASS_DISABLED | e_PLAYER_CLASS_HADFIRST))
			{
				// If class selection is disabled for this player, they have already selected
				// a class and we haven't manually sent them back to the menu.
				Class_Spectate(playerid);
				SetTimerEx("_Class_SpawnPlayer1", 10, 0, "i", playerid);
				CallRemoteFunction("_Class_OtherRequestClass", "ii", playerid, -1);
			}
			else
			{
				CallRemoteFunction("_Class_OtherRequestClass", "ii", playerid, classid);
			}
			return 1;
		}
#endif

HOOK_FORWARD:Class_OnPlayerRequestClass(playerid, classid);
#if defined _ALS_OnPlayerRequestClass
	#undef OnPlayerRequestClass
#else
	#define _ALS_OnPlayerRequestClass
#endif
#define OnPlayerRequestClass(%0) Class_OnPlayerRequestClass(%0) <_ALS : _ALS_go>

foreign void:Class_Goto(playerid, playerclass);

global void:Class_Goto(playerid, playerclass)
{
	P:2("Class_Goto called: %i, %i", playerid, playerclass);
	// This now sets the REAL spawn information, including spawn location.
	SetSpawnInfo(playerid, NO_TEAM, Class_Skin(e_PLAYER_CLASS:playerclass), Class_X(e_PLAYER_CLASS:playerclass), Class_Y(e_PLAYER_CLASS:playerclass), Class_Z(e_PLAYER_CLASS:playerclass), Class_A(e_PLAYER_CLASS:playerclass), 0, 0, 0, 0, 0, 0);
	SetPlayerSkin(playerid, Class_Skin(e_PLAYER_CLASS:playerclass));
	YSI_g_sPlayerClass[playerid] = (YSI_g_sPlayerClass[playerid] & ~(e_PLAYER_CLASS_SKIN)) | (e_PLAYER_CLASS:playerclass);
	// Save the last viewed class so that we know which direction the person
	// went next time OnPlayerRequestClass is called.
	//return 1;
}

/**--------------------------------------------------------------------------**\
<summary>Class_OnPlayerRequestSpawn</summary>
<param name="playerid">Player who selected a spawn.</param>
<returns>
	-
</returns>
<remarks>
	Has inbuilt protection for a bug where selections aren't correctly
	debounced so you can press shift twice at once which can mess up some
	scripts (e.g. the example team selection script).  Calls
	OnPlayerRequestSpawnEx with an additional class parameter.
</remarks>
\**--------------------------------------------------------------------------**/

//mhook OnPlayerRequestSpawn(playerid)

#if !defined YSI_NO_MASTER && (_YSIM_IS_CLIENT || _YSIM_IS_STUB)
	public _Class_OnPlayerRequestSpawn(playerid)
	{
		return 1;
	}
#else
	#if !defined YSI_NO_MASTER && _YSIM_IS_CLOUD
		//mhook OnPlayerRequestClass(playerid, classid)
		public _Class_OnPlayerRequestSpawn(playerid) <>
		{
			return 1;
		}
		
		//mhook OnPlayerRequestClass(playerid, classid)
		public _Class_OnPlayerRequestSpawn(playerid) <_YCM:y>
		{
	#else
		//mhook OnPlayerRequestClass(playerid, classid)
		public _Class_OnPlayerRequestSpawn(playerid)
		{
	#endif
			P:2("hook Class_OnPlayerRequestSpawn called: %d", playerid);
			new
				time = GetTickCount();
			if ((time - YSI_g_sLastRefuse[playerid]) >= 1000)
			{
				//YSI_gOPRSE = false;
				//new
				//	ret = 1;
				//if (YSI_g_sClassOptions & e_CLASS_OPTION_HAS_RS_CALLBACK)
				//{
				//	YSI_gOPRSE = true;
				//	ret = CallLocalFunction("OnPlayerRequestSpawnEx_", "ii", playerid, playerclass);
				//}
				new
					ret = CallRemoteFunction("_Class_OtherRequestSpawn", "i", playerid);
				P:4("Class_OnPlayerRequestSpawn() return: %d", ret);
				if (ret)
				{
					//#if defined _YSI_SYSTEM_GROUPS
					new
						Group:newgroup = YSI_g_sClasses[(YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN)][E_CLASS_GROUP];
					P:4("Class_OnPlayerRequestSpawn() newgroup: %d", _:newgroup);
					if (newgroup != Group:-1) Class_ResolveGroups(playerid, newgroup, true); //Group_AddPlayer(newgroup, playerid);
					//#endif
					if (ret == -1)
					{
						YSI_g_sPlayerClass[playerid] |= e_PLAYER_CLASS_SKIN;
						// The order is VERY important here - this will actually
						// call the function further down (directly below in fact).
						//OnPlayerRequestClass(playerid, YSI_g_sLeft);
						//Class_DoOnPlayerRequestClass(playerid, YSI_g_sLeft);
						switch (YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_PRESS)
						{
							case e_PLAYER_CLASS_RIGHT:
							{
								_Class_OnPlayerRequestClass(playerid, YSI_g_sLeft);
							}
							case e_PLAYER_CLASS_MIDDLE:
							{
								_Class_OnPlayerRequestClass(playerid, YSI_g_sRight);
							}
							case e_PLAYER_CLASS_LEFT:
							{
								_Class_OnPlayerRequestClass(playerid, YSI_g_sMiddle);
							}
						}
					}
					else
					{
						return 1;
					}
				}
			}
			YSI_g_sLastRefuse[playerid] = time;
			//Class_ResumeRefresh(playerid);
			P:5("Class_OnPlayerRequestSpawn: Return 0");
			return 0;
		}
#endif

/**--------------------------------------------------------------------------**\
<summary>Class_OnPlayerSpawn</summary>
<param name="playerid">Player who spawned.</param>
<returns>
	-
</returns>
<remarks>
	Sets a player's position based on skin.
</remarks>
\**--------------------------------------------------------------------------**/

mhook OnPlayerSpawn(playerid)
{
	P:2("Class_OnPlayerSpawn called: %d", playerid);
	new
		playerclass = _:(YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN),
		weapon;
	for (new i = 0; i != MAX_CLASS_SPAWN_WEAPONS; ++i)
	{
		weapon = YSI_g_sClasses[playerclass][E_CLASS_WEAPONS][i];
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
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>Class_OnPlayerConnect</summary>
<param name="playerid">Player who joined the server.</param>
<returns>
	-
</returns>
<remarks>
	Reset all the data on this player's current classes.
</remarks>
\**--------------------------------------------------------------------------**/

mhook OnPlayerConnect(playerid)
{
	YSI_g_sPlayerClass[playerid] = e_PLAYER_CLASS_NONE;
	NO_GROUPS()
	{
		new
			slot = PA_Slot(playerid),
			Bit:mask = PA_Mask(playerid);
		for (new i = 0; i != MAX_CLASSES; ++i)
		{
			YSI_g_sClasses[i][E_CLASS_PLAYERS][slot] |= mask;
		}
	}
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>_CLASS_WEAPON_CODE</summary>
<returns>
	-
</returns>
<remarks>
	Converts the variable arguments to an array.
</remarks>
\**--------------------------------------------------------------------------**/

// #define _CLASS_WEAPON_CODE if((n-w)&0x01)while(w!=n&&s<MAX_CLASS_SPAWN_WEAPONS){cw=getarg(w++);if(cw==WEAPON_ARMOUR)weapons[MAX_CLASS_SPAWN_WEAPONS]=WEAPON_ARMOUR|(100<<8);else if(w==n)P:E(": Insufficient class weapon data.");else weapons[s++]=(cw&0xFF)|(getarg(w++)<<8);}else while(w!=n&&s<MAX_CLASS_SPAWN_WEAPONS){cw=getarg(w++);if(cw==WEAPON_ARMOUR)weapons[MAX_CLASS_SPAWN_WEAPONS]=WEAPON_ARMOUR|(getarg(w++)<<8);else weapons[s++]=(cw&0xFF)|(getarg(w++)<<8);}

#define _CLASS_WEAPON_CODE \
	{if((n-w+1)/2>MAX_CLASS_SPAWN_WEAPONS) P:E("Excessive class weapon data."); \
	if((n-w)&0x01){while(w!=n)if((cw=getarg(w++))==WEAPON_ARMOUR)weapons[MAX_CLASS_SPAWN_WEAPONS]=WEAPON_ARMOUR|(100<<8);else if(w==n)P:E(": Insufficient class weapon data.");else weapons[s++]=(cw&0xFF)|(getarg(w++)<<8);} \
	else{while(w!=n)weapons[((cw=getarg(w++))==WEAPON_ARMOUR)?MAX_CLASS_SPAWN_WEAPONS:(s++)]=(cw&0xFF)|(getarg(w++)<<8);}}

// cw=getarg(w++);if(cw==WEAPON_ARMOUR)weapons[MAX_CLASS_SPAWN_WEAPONS]=WEAPON_ARMOUR|(getarg(w++)<<8);else weapons[s++]=(cw&0xFF)|(getarg(w++)<<8);

// cw=getarg(w++);

// if((getarg(w++))==WEAPON_ARMOUR)
	// weapons[MAX_CLASS_SPAWN_WEAPONS]=WEAPON_ARMOUR|(100<<8);
// else if(w==n)
	// P:E(": Insufficient class weapon data.");
// else
	// weapons[s++]=(cw&0xFF)|(getarg(w++)<<8);

/**--------------------------------------------------------------------------**\
<summary>Class_Add</summary>
<param name="skin">Skin of the class.</param>
<param name="Float:x">X spawn location.</param>
<param name="Float:y">Y spawn location.</param>
<param name="Float:z">Z spawn location.</param>
<param name="Float:a">A spawn location.</param>
<param name="...">Spawn weapons and ammo (weapon then ammo)</param>
<returns>
	-
</returns>
<remarks>
	Pretty much AddPlayerClass but allows greater control over the classes.
	Now has infinate (MAX_CLASS_SPAWN_WEAPONS) spawn weapons.  This is one of
	the few API functions which is not entirely remote.  This is because it has
	variable parameters which is need to collect in to a single array to pass to
	the remote function.
</remarks>
\**--------------------------------------------------------------------------**/

stock Class_Add(skin, Float:x, Float:y, Float:z, Float:a, ...)
{
	P:3("Class_Add called: %i, %f, %f, %f, %f, (+%i)", skin, x, y, z, a, numargs() - 5);
	new
		n = numargs(),
		w = 5,
		s,
		weapons[MAX_CLASS_SPAWN_WEAPONS + 1],
		cw;
	_CLASS_WEAPON_CODE
	return Class_AddClass(skin, x, y, z, a, weapons, MAX_CLASS_SPAWN_WEAPONS + 1, Group:-1, Group:-1);
}

/**--------------------------------------------------------------------------**\
<summary>Class_AddEx</summary>
<param name="forgroup">Group that can use the skin.</param>
<param name="setgroup">Group to add the player to on selection.</param>
<param name="skin">Skin of the class.</param>
<param name="Float:x">X spawn location.</param>
<param name="Float:y">Y spawn location.</param>
<param name="Float:z">Z spawn location.</param>
<param name="Float:a">A spawn location.</param>
<param name="...">Spawn weapons and ammo (weapon then ammo)</param>
<returns>
	-
</returns>
<remarks>
	Pretty much AddPlayerClass but allows greater control over the classes.
	Now has infinate (MAX_CLASS_SPAWN_WEAPONS) spawn weapons.
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>Class_AddForGroup</summary>
<param name="group">Group to allow to use the class.</param>
<param name="skin">Skin of the class.</param>
<param name="Float:x">X spawn location.</param>
<param name="Float:y">Y spawn location.</param>
<param name="Float:z">Z spawn location.</param>
<param name="Float:a">A spawn location.</param>
<param name="...">Weapon data.</param>
<returns>
	-
</returns>
<remarks>
	Adds a class only people in the specified group can use.
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>Class_AddWithGroupSet</summary>
<param name="group">Group to make players who use this group.</param>
<param name="skin">Skin of the class.</param>
<param name="Float:x">X spawn location.</param>
<param name="Float:y">Y spawn location.</param>
<param name="Float:z">Z spawn location.</param>
<param name="Float:a">A spawn location.</param>
<param name="...">Spawn weapons.</param>
<returns>
	-
</returns>
<remarks>
	Adds a class which puts you in the specified group when selected.
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>Class_AddClass</summary>
<param name="skin">Skin of the class.</param>
<param name="Float:x">X spawn location.</param>
<param name="Float:y">Y spawn location.</param>
<param name="Float:z">Z spawn location.</param>
<param name="Float:a">A spawn location.</param>
<param name="weapons[]">Array of spawn weapon data.</param>
<param name="count">Number of weapons added.</param>
<param name="forgroup">Group that can use the class.</param>
<param name="asgroup">Group to assign people to with this class.</param>
<returns>
	-
</returns>
<remarks>
	Does the hard work.  This took a long time to get working correctly with the
	new master system, infact getting just this one function to compile took a
	major re-working of the macros to reduce the length of intermediate stages.
</remarks>
\**--------------------------------------------------------------------------**/

foreign Class_AddClass(s,Float:x,Float:y,Float:z,Float:a,w[],c,Group:f,Group:g);

global Class_AddClass(s,Float:x,Float:y,Float:z,Float:a,w[],c,Group:f,Group:g)
{
	P:2("Class_AddClass called: %i, %f, %f, %f, %f, %s, %i, %i, %i", s, x, y, z, a, Debug_PrintArray(w, c), c, _:f, _:g);
	new
		i;
	while (i != MAX_CLASSES && _Class_IsActive(i)) ++i;
	if (i == MAX_CLASSES) return -1;
	YSI_g_sClasses[i][E_CLASS_FLAGS] = e_CLASS_FLAGS_ACTIVE | e_CLASS_FLAGS_ENABLED | e_CLASS_FLAGS:s,
	YSI_g_sClasses[i][E_CLASS_X] = x,
	YSI_g_sClasses[i][E_CLASS_Y] = y,
	YSI_g_sClasses[i][E_CLASS_Z] = z,
	YSI_g_sClasses[i][E_CLASS_A] = a,
	memcpy(YSI_g_sClasses[i][E_CLASS_WEAPONS], w, 0, (MAX_CLASS_SPAWN_WEAPONS + 1) * 4, MAX_CLASS_SPAWN_WEAPONS + 1);
	// P:7("Class_AddClass: weapon %d %d %d", j, c, i);
	PA_FastInit(YSI_g_sClasses[i][E_CLASS_PLAYERS]);
	// P:7("Class_AddClass: weapon %d %d %d", j, c, f);
	Class_ResolveGroups(i, f, false);
	// P:7("Class_AddClass: weapon %d %d %d", j, c, g);
	YSI_g_sClasses[i][E_CLASS_GROUP] = g;
	YSI_g_sClassCount++;
	// P:7("Class_AddClass: weapon %d %d %d", j, c, YSI_g_sClassCount);
	return i;
}

/**--------------------------------------------------------------------------**\
<summary>Class_HasGroup</summary>
<param name="classid">The class to test.</param>
<param name="Group:group">The group to test setting of.</param>
<returns>
	Does this class add players to the given group on spawn?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

foreign Class_HasGroup(classid, Group:group);

global Class_HasGroup(classid, Group:group)
{
	return YSI_g_sClasses[classid][E_CLASS_GROUP] == group;
}

/**--------------------------------------------------------------------------**\
<summary>Class_Enable</summary>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

foreign Class_Enable(classid, bool:toggle);

global Class_Enable(classid, bool:toggle)
{
	if (_Class_IsValid(classid))
	{
		if (toggle)
		{
			YSI_g_sClasses[classid][E_CLASS_FLAGS] |= e_CLASS_FLAGS_ENABLED;
		}
		else
		{
			YSI_g_sClasses[classid][E_CLASS_FLAGS] &= ~e_CLASS_FLAGS_ENABLED;
			// TODO!  Hide the class for anyone currently viewing it.
			// foreach (new playerid : Player)
			// {
				// new
					// e_PLAYER_CLASS:curclass = YSI_g_sPlayerClass[playerid];
				// P:4("Class_Delete: %d %d %d", playerid, curclass, e_PLAYER_CLASS_SELECT);
				// if (curclass & e_PLAYER_CLASS_SELECT)
				// {
					// if (e_PLAYER_CLASS:classid == curclass & e_PLAYER_CLASS_SKIN) Class_Goto(playerid, Class_FindNew(playerid, e_PLAYER_CLASS:classid, CLASS_MOVE_RIGHT));
				// }
			// }
		}
		return 1;
	}
	return 0;
}

/**--------------------------------------------------------------------------**\
<summary>Class_Delete</summary>
<param name="classid">Class to delete.</param>
<returns>
	-
</returns>
<remarks>
	Completely removes a class from the system.
</remarks>
\**--------------------------------------------------------------------------**/

foreign void:Class_Delete(classid);

global void:Class_Delete(classid)
{
	P:2("Class_Delete called: %i", classid);
	if (Class_Enable(classid, false))
	{
		YSI_g_sClasses[classid][E_CLASS_FLAGS] = e_CLASS_FLAGS:0;
	}
}

/**--------------------------------------------------------------------------**\
<summary>Class_SetPlayer</summary>
<param name="classid">Class to set permissions for.</param>
<param name="playerid">Player to set for.</param>
<param name="set">Whether or not they can use this class.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

foreign void:Class_SetPlayer(cl, pid, bool:s);

global void:Class_SetPlayer(cl, pid, bool:s)
{
	PA_Set(YSI_g_sClasses[cl][E_CLASS_PLAYERS], pid, s);
}

/**--------------------------------------------------------------------------**\
<summary>Class_GetPlayer</summary>
<param name="classid">Class to set permissions for.</param>
<param name="playerid">Player to set for.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

foreign bool:Class_GetPlayer(cl,pid);

global bool:Class_GetPlayer(cl,pid)
{
	return PA_Get(YSI_g_sClasses[cl][E_CLASS_PLAYERS], pid);
}

/**--------------------------------------------------------------------------**\
<summary>Class_Get</summary>
<param name="playerid">Player to get the current class of.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

foreign Class_Get(playerid);

global Class_Get(playerid)
{
	if (VALID_PLAYERID(playerid))
	{
		return _:(YSI_g_sPlayerClass[playerid] & e_PLAYER_CLASS_SKIN);
	}
	return -1;
}

#if defined _ALS_AddPlayerClass
	#undef AddPlayerClass
#else
	#define _ALS_AddPlayerClass
#endif
#define AddPlayerClass Class_Add

// Reset.
#undef _GROUP_MAKE_LIMIT
#undef _GROUP_MAKE_NAME

#include "..\YSI_Core\y_master"

