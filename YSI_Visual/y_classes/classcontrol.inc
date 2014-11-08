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
		YSI_g_sPlayerFlags - Player's current classes.
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

enum e_SPAWN_FLAGS (<<= 1)
{
	e_SPAWN_FLAGS_NONE  = 0,
	// Control flags.
	e_SPAWN_FLAGS_RETURNED = 1, // Back in class selection.
	e_SPAWN_FLAGS_SPAWNSINCE,   // Spawned after class selection.
	e_SPAWN_FLAGS_ENABLED,      // Class selection disabled.
	e_SPAWN_FLAGS_RESELECT,     // Class reselection disabled.
	e_SPAWN_FLAGS_HADFIRST,     // Spawned ever.
	e_SPAWN_FLAGS_INSTANT,      // Sent straight to class selection.
	e_SPAWN_FLAGS_FORCED,       // Sent to class selection manually.
	e_SPAWN_FLAGS_INSELECT,     // In class selection.
	e_SPAWN_FLAGS_IGNORE_ONCE,
	e_SPAWN_FLAGS_HELD          // Can't see, but in, class selection.
}

static stock
	e_SPAWN_FLAGS:YSI_g_sPlayerFlags[MAX_PLAYERS];

/**--------------------------------------------------------------------------**\
<summary>Player_InSelection</summary>
<param name="playerid">Player to check.</param>
<returns>
	Is this player currently in the class selection screen?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

foreign bool:Player_InSelection(playerid);

global bool:Player_InSelection(playerid)
{
	return bool:(YSI_g_sPlayerFlags[playerid] & e_SPAWN_FLAGS_INSELECT);
}

/**--------------------------------------------------------------------------**\
<summary>Player_HasSpawned</summary>
<param name="playerid">Player to check.</param>
<returns>
	Has this player ever spawned?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

foreign bool:Player_HasSpawned(playerid);

global bool:Player_HasSpawned(playerid)
{
	return bool:(YSI_g_sPlayerFlags[playerid] & e_SPAWN_FLAGS_HADFIRST);
}

/**--------------------------------------------------------------------------**\
<summary>Player_IsSpawned</summary>
<param name="playerid">Player to check.</param>
<returns>
	Is this player spawned now?
</returns>
<remarks>
	Returns true if they are not in class selection, and if they have ever
	spawned.  It could be that both "Player_IsSpawned" and "Player_InSelection"
	return "false" - if they haven't even reached the class selection screen yet
	(mainly happens in "OnPlayerConnect").
</remarks>
\**--------------------------------------------------------------------------**/

foreign bool:Player_IsSpawned(playerid);

global bool:Player_IsSpawned(playerid)
{
	return (YSI_g_sPlayerFlags[playerid] & (e_SPAWN_FLAGS_INSELECT | e_SPAWN_FLAGS_HADFIRST)) == e_SPAWN_FLAGS_HADFIRST;
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
	YSI_g_sPlayerFlags[playerid] = e_SPAWN_FLAGS_RESELECT | e_SPAWN_FLAGS_ENABLED;
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>Class_OnPlayerRequestClass</summary>
<param name="playerid">Player who requested a class.</param>
<param name="class">Class they requested.</param>
<returns>
	-
</returns>
<remarks>
	Not the first call of this function by y_classes.
</remarks>
\**--------------------------------------------------------------------------**/

Class_Spawn(playerid)
{
	TogglePlayerSpectating(playerid, true);
	PlayerSpectatePlayer(playerid, playerid, SPECTATE_MODE_NORMAL);
	SpawnPlayer(playerid);
	TogglePlayerSpectating(playerid, false);
	SetCameraBehindPlayer(playerid);
}

Class_ShowHold(playerid)
{
	SpawnPlayer(playerid);
	YSI_g_sPlayerFlags[playerid] |= e_SPAWN_FLAGS_HELD;
	TogglePlayerSpectating(playerid, true);
	TogglePlayerControllable(playerid, false);
	//ForceClassSelection(playerid);
}

Class_HideHold(playerid)
{
	YSI_g_sPlayerFlags[playerid] &= ~e_SPAWN_FLAGS_HELD;
	TogglePlayerSpectating(playerid, false);
	ForceClassSelection(playerid);
	// SetPlayerHealth(playerid, 0.0);
	TogglePlayerSpectating(playerid, true);
	PlayerSpectatePlayer(playerid, playerid, SPECTATE_MODE_NORMAL);
	TogglePlayerSpectating(playerid, false);
	TogglePlayerControllable(playerid, false);
	//SetCameraBehindPlayer(playerid);
	//SpawnPlayer(playerid);
}

mhook OnPlayerRequestClass(playerid, classid)
{
	//TogglePlayerSpectating(playerid, true);
	YSI_g_sPlayerFlags[playerid] |= e_SPAWN_FLAGS_INSELECT;
	new
		e_SPAWN_FLAGS:flags = YSI_g_sPlayerFlags[playerid];
	// These are all the cases where class selection is allowed.
	if (flags & e_SPAWN_FLAGS_FORCED)
	{
		return 1;
	}
	if (flags & e_SPAWN_FLAGS_HADFIRST)
	{
		if (flags & e_SPAWN_FLAGS_RESELECT)
		{
			return 1;
		}
		SpawnPlayer(playerid);
		//Class_Spawn(playerid);
	}
	else
	{
		if (flags & e_SPAWN_FLAGS_ENABLED)
		{
			return 1;
		}
		Class_ShowHold(playerid);
	}
	//Class_Spawn(playerid);
	return -2;
}

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
	if (YSI_g_sPlayerFlags[playerid] & e_SPAWN_FLAGS_HELD) return -1;
	if (!(YSI_g_sPlayerFlags[playerid] & e_SPAWN_FLAGS_RESELECT))
	{
		// Seems backwards, but this disables the message.
		ForceClassSelection(playerid);
	}
	YSI_g_sPlayerFlags[playerid] = (YSI_g_sPlayerFlags[playerid] & ~e_SPAWN_FLAGS_INSELECT) | e_SPAWN_FLAGS_HADFIRST;
	return 1;
}

// forward _Class_SpawnPlayer1(playerid);

// public _Class_SpawnPlayer1(playerid)
// {
	// P:1("_Class_SpawnPlayer1 called: %d", playerid);
	// //SpawnPlayer(playerid);
	// YSI_g_sPlayerFlags[playerid] |= (e_SPAWN_FLAGS_IGNORE_ONCE);
	// TogglePlayerSpectating(playerid, false);
	// //SpawnPlayer(playerid);
	// //YSI_g_sTimer[playerid] = SetTimerEx("_Class_SpawnPlayer3", 20, 0, "i", playerid);
	// //Class_TK(playerid);
// }

// forward _Class_SpawnPlayer2(playerid);

// public _Class_SpawnPlayer2(playerid)
// {
	// P:1("_Class_SpawnPlayer2 called: %d", playerid);
	// //SpawnPlayer(playerid);
	// //YSI_g_sPlayerFlags[playerid] |= (e_SPAWN_FLAGS_IGNORE_ONCE);
	// TogglePlayerSpectating(playerid, false);
	// //Class_TK(playerid);
// }

// forward _Class_SpawnPlayer3(playerid);

// public _Class_SpawnPlayer3(playerid)
// {
	// P:1("_Class_SpawnPlayer3 called: %d", playerid);
	// SpawnPlayer(playerid);
	// //Class_TK(playerid);
	// //YSI_g_sPlayerFlags[playerid] |= (e_SPAWN_FLAGS_IGNORE_ONCE);
	// //TogglePlayerSpectating(playerid, false);
	// //Class_TK(playerid);
// }

// forward _Class_SpawnPlayer4(playerid);

// public _Class_SpawnPlayer4(playerid)
// {
	// P:1("_Class_SpawnPlayer4 called: %d", playerid);
	// //SpawnPlayer(playerid);
	// Class_Spectate(playerid);
	// if (YSI_g_sPlayerFlags[playerid] & (e_SPAWN_FLAGS_ENABLED))
	// {
		// YSI_g_sTimer[playerid] = SetTimerEx("_Class_SpawnPlayer1", 10, 0, "i", playerid);
	// }
	// else
	// {
		// YSI_g_sTimer[playerid] = SetTimerEx("_Class_SpawnPlayer2", 10, 0, "i", playerid);
	// }
	// //Class_TK(playerid);
	// //YSI_g_sPlayerFlags[playerid] |= (e_SPAWN_FLAGS_IGNORE_ONCE);
	// //TogglePlayerSpectating(playerid, false);
	// //Class_TK(playerid);
// }

// forward _Class_Return(playerid);

// public _Class_Return(playerid)
// {
	// P:1("_Class_Return called: %d", playerid);
	// Class_ReturnToSelection(playerid);
	// //Class_TK(playerid);
	// //YSI_g_sTimer[playerid] = SetTimerEx("_Class_NotSpawned", 500, 0, "i", playerid);
// }

// forward _Class_NotSpawned(playerid);

// public _Class_NotSpawned(playerid)
// {
	// P:1("_Class_NotSpawned called: %d", playerid);
	// // Called if they don't connect properly.
	// Class_DisableSelection(playerid);
	// //SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	// //SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	// SetTimerEx("_Class_Return", 10, 0, "i", playerid);
	// YSI_g_sPlayerFlags[playerid] |= (e_SPAWN_FLAGS_RETURNED | e_SPAWN_FLAGS_INSTANT);
// }

// static stock Class_TK(playerid)
// {
	// // "Timer Kill".
	// if (YSI_g_sTimer[playerid])
	// {
		// KillTimer(YSI_g_sTimer[playerid]);
		// YSI_g_sTimer[playerid] = 0;
	// }
// }

stock void:Class_DisableReselection(playerid)
{
	Class_SetReselection(playerid, false);
}

stock void:Class_EnableReselection(playerid)
{
	Class_SetReselection(playerid, true);
}

foreign void:Class_SetReselection(playerid, bool:s);

global void:Class_SetReselection(playerid, bool:s)
{
	if (s) YSI_g_sPlayerFlags[playerid] |= (e_SPAWN_FLAGS_RESELECT);
	else YSI_g_sPlayerFlags[playerid] &= ~(e_SPAWN_FLAGS_RESELECT);
}

foreign void:Class_ForceReselection(playerid);

global void:Class_ForceReselection(playerid)
{
	YSI_g_sPlayerFlags[playerid] |= e_SPAWN_FLAGS_FORCED;
	ForceClassSelection(playerid);
}

stock void:Class_DisableSelection(playerid)
{
	Class_SetSelection(playerid, false);
}

stock void:Class_EnableSelection(playerid)
{
	Class_SetSelection(playerid, true);
}

foreign void:Class_SetSelection(playerid, bool:s);

global void:Class_SetSelection(playerid, bool:s)
{
	if (s)
	{
		YSI_g_sPlayerFlags[playerid] |= (e_SPAWN_FLAGS_ENABLED);
		if (YSI_g_sPlayerFlags[playerid] & e_SPAWN_FLAGS_HELD)
		{
			Class_HideHold(playerid);
		}
	}
	else
	{
		YSI_g_sPlayerFlags[playerid] &= ~(e_SPAWN_FLAGS_ENABLED);
		if (YSI_g_sPlayerFlags[playerid] & e_SPAWN_FLAGS_INSELECT)
		{
			Class_ShowHold(playerid);
			// Class_TK(playerid);
		}
	}
	//return 1;
}

foreign void:Class_ReturnToSelection(playerid);

global void:Class_ReturnToSelection(playerid)
{
	YSI_g_sPlayerFlags[playerid] |= (e_SPAWN_FLAGS_INSTANT);
	Class_ForceReselection(playerid);
	TogglePlayerSpectating(playerid, false);
	//return 1;
}

// static stock Class_Spectate(playerid)
// {
	// new
		// Float:x1,
		// Float:y1,
		// Float:z1;
	// GetPlayerCameraPos(playerid, x1, y1, z1);
	// new
		// Float:x2,
		// Float:y2,
		// Float:z2;
	// GetPlayerCameraFrontVector(playerid, x2, y2, z2);
	// TogglePlayerSpectating(playerid, true);
	// SetPlayerCameraPos(playerid, x1, y1, z1);
	// SetPlayerCameraLookAt(playerid, x2, y2, z2);
	// PlayerSpectatePlayer(playerid, playerid, SPECTATE_MODE_FIXED);
// }

