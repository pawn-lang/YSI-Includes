/* 
 * ===============
 *  INTRODUCTION: 
 * ===============
 * 
 * fixes.inc - Community patch for buggy SA:MP functions.
 * 
 * ================
 *  LIST OF FIXES: 
 * ================
 * 
 * FIX:      GetPlayerColor
 * PROBLEM:  Returns "0" if "SetPlayerColor" has never been called.
 * SOLUTION: Call "SetPlayerColor" in "OnPlayerConnect".
 * SEE:      "OnPlayerConnect".
 * AUTHOR:   KoczkaHUN
 * POST:     http://forum.sa-mp.com/showpost.php?p=1486048
 * 
 * FIX:      FILTERSCRIPT
 * PROBLEM:  Despite the fact that is in every new script, many people don't
 *           define "FILTERSCRIPT" where appropriate.
 * SOLUTION: Provide an "IS_FILTERSCRIPT" variable (note the naming to match
 *           the original macro).
 * AUTHOR:   Y_Less
 * SEE:      "OnFilterScriptInit" and "OnGameModeInit".
 * 
 * FIX:      SpawnPlayer
 * PROBLEM:  Kills the player if they are in a vehicle.
 * SOLUTION: Remove the from the vehicle.
 * SEE:      "FIXES_SpawnPlayer".
 * AUTHOR:   Y_Less
 * 
 * FIX:      SetPlayerName
 * PROBLEM:  Using "SetPlayerName" when the new name only differs from the old
 *           name in case does not alter the name at all.
 * SOLUTION: Change their name twice - once to "_FIXES TEMP NAME" and then to
 *           the actual required name.
 * SEE:      "OnPlayerConnect" and "FIXES_SetPlayerName".
 * AUTHOR:   Y_Less/Slice
 * 
 * FIX:      GetPlayerSkin
 * PROBLEM:  Returns the new skin after "SetSpawnInfo" is called but before the
 *           player actually respawns to get the new skin.
 * SOLUTION: Record the skin in "OnPlayerSpawn" and always return that one.
 * SEE:      "OnPlayerSpawn", "FIXES_GetPlayerSkin" and "FIXES_SetPlayerSkin".
 * AUTHOR:   Y_Less
 * 
 * FIX:      GetWeaponName
 * PROBLEM:  Returns nothing for 18, 44, and 45.
 * SOLUTION: Return the correct names ("Molotov Cocktail", "Thermal Goggles",
 *           and "Night vision Goggles").
 * SEE:      "FIXES_GetWeaponName".
 * AUTHOR:   Y_Less
 * 
 * FIX:      SetPlayerWorldBounds
 * PROBLEM:  Aiming can bypass the edge.
 * SOLUTION: Check for the player leaving the area and reset them to their last
 *           good position if they leave the area (aiming or not).
 * SEE:      "OnPlayerUpdate" and "FIXES_SetPlayerWorldBounds".
 * AUTHOR:   Y_Less
 * 
 * FIX:      TogglePlayerControllable
 * PROBLEM:  Other players see you moving on the spot.
 * SOLUTION: Return 0 in OnPlayerUpdate.
 * SEE:      "FIXES_TogglePlayerControllable" and "OnPlayerUpdate".
 * AUTHOR:   Slice
 * POST:     http://forum.sa-mp.com/showpost.php?p=876854
 * 
 * FIX:      HydraSniper
 * PROBLEM:  Entring military aircraft with a sniper rifle messes up vies.
 * SOLUTION: Set their armed weapon to fists.
 * SEE:      "OnPlayerStateChange", "FIXES_GivePlayerWeapon",
 *           "FIXES_SetPlayerArmedWeapon".
 * AUTHOR:   funky1234
 * POST:     http://forum.sa-mp.com/showpost.php?p=965644
 * 
 * FIX:      IsPlayerInCheckpoint
 * PROBLEM:  Function returns an undefined value if it is called before any
 *           other checkpoint functions are called to initialise the value.
 * SOLUTION: Call "DisablePlayerCheckpoint" when they connect.
 * SEE:      "OnPlayerConnect".
 * AUTHOR:   Y_Less
 * 
 * FIX:      IsPlayerInRaceCheckpoint
 * PROBLEM:  Function returns an undefined value if it is called before any
 *           other race checkpoint functions are called to initialise the value.
 * SOLUTION: Call "DisablePlayerRaceCheckpoint" when they connect.
 * SEE:      "OnPlayerConnect".
 * AUTHOR:   Y_Less
 * 
 * FIX:      GetPlayerWeapon
 * PROBLEM:  Returns the old value after using "SetPlayerArmedWeapon" when they
 *           are in a vehicle.
 * SOLUTION: If "SetPlayerArmedWeapon" is called in a vehicle, store the new
 *           value and return that instead.
 * SEE:      "OnPlayerStateChange", "FIXES_SetPlayerArmedWeapon", and
 *           "FIXES_GetPlayerWeapon".
 * AUTHOR:   Y_Less
 * 
 * FIX:      PutPlayerInVehicle
 * PROBLEM:  If this is used on a passenger the driver of their old vehicle
 *           doesn't see them in their new vehicle.
 * SOLUTION: Remove them from the vehicle first.
 * SEE:      "OnPlayerStateChange" and "FIXES_PutPlayerInVehicle".
 * AUTHOR:   leong124/Y_Less
 * POST:     http://forum.sa-mp.com/showpost.php?p=1265965
 * 
 * FIX:      KEY_AIM
 * PROBLEM:  "KEY_AIM" isn't defined by default.
 * SOLUTION: Define it.
 * SEE:      N/A.
 * AUTHOR:   Y_Less
 * 
 * FIX:      SetPlayerCheckpoint
 * PROBLEM:  If a checkpoint is already set it will use the size of that
 *           checkpoint instead of the new one.
 * SOLUTION: Call "DisablePlayerCheckpoint" before setting the checkpoint.
 * SEE:      "FIXES_SetPlayerCheckpoint".
 * AUTHOR:   KoczkaHUN
 * POST:     http://forum.sa-mp.com/showpost.php?p=1482401
 *
 * FIX:      SetPlayerRaceCheckpoint
 * PROBLEM:  If a checkpoint is already set it will use the size of that
 *           checkpoint instead of the new one.
 * SOLUTION: Call "DisablePlayerRaceCheckpoint" before setting the checkpoint.
 * SEE:      "FIXES_SetPlayerRaceCheckpoint".
 * AUTHOR:   KoczkaHUN
 * POST:     http://forum.sa-mp.com/showpost.php?p=1482401
 *
 * FIX:      TextDrawCreate
 * PROBLEM:  Crashes on a blank string.
 * SOLUTION: Intercept blank strings.
 * SEE:      "FIXES_TextDrawCreate".
 * AUTHOR:   wups
 * POST:     http://forum.sa-mp.com/showpost.php?p=1484008
 * 
 * FIX:      TextDrawSetString
 * PROBLEM:  Crashes on a blank string and size greater than 1024.
 * SOLUTION: Intercept blank strings and truncate long strings.
 * SEE:      "FIXES_TextDrawSetString".
 * AUTHOR:   TomTrox
 * POST:     http://forum.sa-mp.com/showpost.php?p=1487870
 * 
 * FIX:      AllowInteriorWeapons
 * PROBLEM:  Does nothing.
 * SOLUTION: Set the player's weapon to fists in an interior.
 * SEE:      "FIXES_AllowInteriorWeapons", "OnGameModeInit" and
 *           "OnPlayerUpdate".
 * AUTHOR:   KoczkaHUN
 * POST:     http://forum.sa-mp.com/showpost.php?p=1502696
 * 
 * FIX:      OnPlayerEnterVehicle
 * PROBLEM:  Crashes other players when people enter an invalid seat.
 * SOLUTION: Desync the people with invalid seats.
 * SEE:      "OnPlayerStateChange" and "OnPlayerUpdate".
 * AUTHOR:   RyDeR`/Y_Less
 * POST:     http://forum.sa-mp.com/showpost.php?p=1410296
 * 
 * FIX:      OnPlayerEnterVehicle_2
 * PROBLEM:  Crashes the server when hacks enter an invalid vehicle.
 * SOLUTION: Desync the people with invalid vehicles.
 * SEE:      "OnPlayerEnterVehicle".
 * AUTHOR:   im/Y_Less
 * POST:     http://forum.sa-mp.com/showpost.php?p=2340900
 * 
 * FIX:      AllowTeleport
 * PROBLEM:  0.3dRC9 removed "AllowPlayerTeleport" and "AllowAdminTeleport" in
 *           favour of "OnPlayerClickMap".  Some scripts used the old code and.
 * SOLUTION: Teleport the player in "OnPlayerClickMap".
 * SEE:      "OnPlayerClickMap", "FIXES_AllowPlayerTeleport", and
 *           "FIXES_AllowAdminTeleport".
 * AUTHOR:   Y_Less
 * 
 * FIX:      SetPlayerSpecialAction
 * PROBLEM:  Removing jetpacks from players by setting their special action to 0
 *           causes the sound to stay until death.
 * SOLUTION: Call "ClearAnimations" before "SetPlayerSpecialAction".
 * SEE:      "FIXES_SetPlayerSpecialAction".
 * AUTHOR:   MP2
 * POST:     Private message from MP2.
 * 
 * FIX:      OnDialogResponse
 * PROBLEM:  Cheaters can spoof the dialogid they are using to respond to ones
 *           they can't actually see.
 * SOLUTION: Store the displayed dialogid and use that instead.
 * SEE:      "FIXES_OnDialogResponse", "FIXES_ShowPlayerDialog".
 * AUTHOR:   Y_Less
 * FIXED IN: 0.3e RC6
 * 
 * FIX:      GetPlayerDialog
 * PROBLEM:  This function doesn't exist.  Fixed for hidden dialogs.
 * SOLUTION: Add it.  DEFAULTS TO FALSE!
 * SEE:      "FIXES_GetPlayerDialog".
 * AUTHOR:   Y_Less/xX_Simon_Xx
 * POST:     http://forum.sa-mp.com/showpost.php?p=2141254
 * 
 * FIX:      SetSpawnInfo
 * PROBLEM:  Kicks the player if "SpawnPlayer" is called before "SetSpawnInfo".
 * SOLUTION: Call "SetSpawnInfo" at least once.
 * SEE:      "OnPlayerConnect".
 * AUTHOR:   Y_Less
 * 
 * FIX:      SetPlayerSkin
 * PROBLEM:  Breaks sitting on bikes.
 * SOLUTION: Put them back in the vehicle after setting their skin.
 * SEE:      "FIXES_SetPlayerSkin".
 * AUTHOR:   CyNiC
 * POST:     http://forum.sa-mp.com/showpost.php?p=1756094
 * 
 * FIX:      HideMenuForPlayer
 * PROBLEM:  Crashes when passed an invalid menu ID.
 * SOLUTION: Don't hide it when passed an invalid menu.
 * SEE:      "FIXES_HideMenuForPlayer".
 * AUTHOR:   Y_Less
 * POST:     http://forum.sa-mp.com/showpost.php?p=1787297
 * 
 * FIX:      valstr
 * PROBLEM:  Crashes on large numbers.
 * SOLUTION: Use "format" instead.
 * SEE:      "FIXES_valstr".
 * AUTHOR:   Slice
 * POST:     http://forum.sa-mp.com/showpost.php?p=1790300
 * 
 * FIX:      fclose
 * PROBLEM:  Crashes on an invalid handle.
 * SOLUTION: Check for an invalid handle.
 * SEE:      "FIXES_fclose".
 * AUTHOR:   Slice
 * POST:     http://forum.sa-mp.com/showpost.php?p=1790300
 * 
 * FIX:      fwrite
 * PROBLEM:  Crashes on an invalid handle.
 * SOLUTION: Check for an invalid handle.
 * SEE:      "FIXES_fwrite".
 * AUTHOR:   Slice
 * POST:     http://forum.sa-mp.com/showpost.php?p=1790300
 * 
 * FIX:      fread
 * PROBLEM:  Crashes on an invalid handle.
 * SOLUTION: Check for an invalid handle.
 * SEE:      "FIXES_fread".
 * AUTHOR:   Slice
 * POST:     http://forum.sa-mp.com/showpost.php?p=1790300
 * 
 * FIX:      fputchar
 * PROBLEM:  Crashes on an invalid handle.
 * SOLUTION: Check for an invalid handle.
 * SEE:      "FIXES_fputchar".
 * AUTHOR:   Slice
 * POST:     http://forum.sa-mp.com/showpost.php?p=1790300
 * 
 * FIX:      fgetchar
 * PROBLEM:  Crashes on an invalid handle.
 * SOLUTION: Check for an invalid handle.
 * SEE:      "FIXES_fgetchar".
 * AUTHOR:   Slice
 * POST:     http://forum.sa-mp.com/showpost.php?p=1790300
 * 
 * FIX:      fblockwrite
 * PROBLEM:  Crashes on an invalid handle.
 * SOLUTION: Check for an invalid handle.
 * SEE:      "FIXES_fblockwrite".
 * AUTHOR:   Slice
 * POST:     http://forum.sa-mp.com/showpost.php?p=1790300
 * 
 * FIX:      fblockread
 * PROBLEM:  Crashes on an invalid handle.
 * SOLUTION: Check for an invalid handle.
 * SEE:      "FIXES_fblockread".
 * AUTHOR:   Slice
 * POST:     http://forum.sa-mp.com/showpost.php?p=1790300
 * 
 * FIX:      fseek
 * PROBLEM:  Crashes on an invalid handle.
 * SOLUTION: Check for an invalid handle.
 * SEE:      "FIXES_fseek".
 * AUTHOR:   Slice
 * POST:     http://forum.sa-mp.com/showpost.php?p=1790300
 * 
 * FIX:      flength
 * PROBLEM:  Crashes on an invalid handle.
 * SOLUTION: Check for an invalid handle.
 * SEE:      "FIXES_flength".
 * AUTHOR:   Slice
 * POST:     http://forum.sa-mp.com/showpost.php?p=1790300
 * 
 * FIX:      file_inc
 * PROBLEM:  All file.inc fixes are included separately for major overhead.
 * SOLUTION: Optionally group them all under one define.  DEFAULTS TO FALSE!
 * SEE:      "FIX_file_inc".
 * AUTHOR:   Y_Less
 * 
 * FIX:      IsPlayerAttachedObjectSlotUsed
 * PROBLEM:  Doesn't work in OnPlayerDisconnect.
 * SOLUTION: Maintain an internal record of slots used.
 * SEE:      "FIXES_SetPlayerAttachedObject",
 *           "FIXES_RemovePlayerAttachedObject",
 *           "FIXES_IsPAttachedObjectSlotUsed", and
 *           "OnPlayerDisconnect".
 * AUTHOR:   Y_Less
 * 
 * FIX:      SetPlayerAttachedObject
 * PROBLEM:  Doesn't remove objects when the mode ends.
 * SOLUTION: Remove them.
 * SEE:      "FIXES_SetPlayerAttachedObject",
 *           "FIXES_RemovePlayerAttachedObject", and
 *           "OnPlayerDisconnect".
 * AUTHOR:   Y_Less
 * 
 * FIX:      OnPlayerDeath
 * PROBLEM:  Clients get stuck when they die with an animation applied.
 * SOLUTION: Clear their animations.
 * SEE:      "OnPlayerDeath" and "OnPlayerUpdate".
 * AUTHOR:   h02
 * POST:     http://forum.sa-mp.com/showpost.php?p=1641144
 * 
 * FIX:      strins
 * PROBLEM:  Ignores the "maxlength" parameter causing possible crashes.
 * SOLUTION: Manually check the length.
 * SEE:      "FIXES_strins".
 * AUTHOR:   Slice/Y_Less
 * POST:     http://forum.sa-mp.com/showpost.php?p=1860495
 * POST:     http://forum.sa-mp.com/showpost.php?p=1864706
 * 
 * FIX:      IsPlayerConnected
 * PROBLEM:  Only uses the lower two bytes of a passed ID.
 * SOLUTION: Mask the numbers.
 * SEE:      "FIXES_IsPlayerConnected".
 * AUTHOR:   Slice
 * POST:     http://forum.sa-mp.com/showpost.php?p=1860464
 * 
 * FIX:      OnPlayerCommandText
 * PROBLEM:  Can crash ZCMD when passed a null string.
 * SOLUTION: Pass NULL if invalid inputs given.
 * SEE:      "OnPlayerCommandText".
 * AUTHOR:   Y_Less
 * POST:     http://forum.sa-mp.com/showpost.php?p=1909511
 * 
 * FIX:      TrainExit
 * PROBLEM:  When getting out of a train entered by "PutPlayerInVehicle", the
 *           camera does not reset properly.
 * SOLUTION: Reset the camera.
 * SEE:      "FIXES_PutPlayerInVehicle", "FIXES_OnPlayerStateChange".
 * AUTHOR:   Terminator3/Y_Less
 * POST:     http://forum.sa-mp.com/showpost.php?p=1980214
 * 
 * FIX:      Kick
 * PROBLEM:  Calling "Kick" in "OnPlayerConnect" doesn't work properly.
 * SOLUTION: Defer it.
 * SEE:      "OnPlayerConnect", "FIXES_Kick".
 * AUTHOR:   Y_Less
 * POST:     http://forum.sa-mp.com/showpost.php?p=1989453
 * 
 * FIX:      OnVehicleMod
 * PROBLEM:  Crashes other players when invalid mods are applied.
 * SOLUTION: Desync the player.
 * SEE:      "OnVehicleMod".
 * AUTHOR:   JernejL/Y_Less
 * POST:     http://forum.sa-mp.com/showpost.php?p=1671500
 * 
 * FIX:      random
 * PROBLEM:  Doesn't work with negative numbers.
 * SOLUTION: Invert then reinvert.  DEFAULTS TO FALSE!
 * SEE:      "FIXES_random".
 * AUTHOR:   xX_Simon_Xx
 * POST:     http://forum.sa-mp.com/showpost.php?p=2141254
 * 
 * FIX:      sleep
 * PROBLEM:  Leaks bytes from the stack.
 * SOLUTION: Invoke "SYSREQ.C" and "RETN" first to store the correct values.
 * SEE:      "FIXES_sleep".
 * AUTHOR:   Y_Less
 * 
 * FIX:      AddMenuItem
 * PROBLEM:  Crashes when passed an invalid menu ID.
 * SOLUTION: Don't hide it when passed an invalid menu.
 * SEE:      "FIXES_AddMenuItem".
 * AUTHOR:   Y_Less
 * 
 * FIX:      SetMenuColumnHeader
 * PROBLEM:  Crashes when passed an invalid menu ID.
 * SOLUTION: Don't hide it when passed an invalid menu.
 * SEE:      "FIXES_SetMenuColumnHeader".
 * AUTHOR:   Y_Less
 * 
 * FIX:      ShowMenuForPlayer
 * PROBLEM:  Crashes when passed an invalid menu ID.
 * SOLUTION: Don't hide it when passed an invalid menu.
 * SEE:      "FIXES_ShowMenuForPlayer".
 * AUTHOR:   Y_Less
 * 
 * FIX:      HideMenuForPlayer
 * PROBLEM:  Crashes when passed an invalid menu ID.
 * SOLUTION: Don't hide it when passed an invalid menu.
 * SEE:      "FIXES_HideMenuForPlayer".
 * AUTHOR:   Y_Less
 * POST:     http://forum.sa-mp.com/showpost.php?p=1787297
 * 
 * FIX:      HideMenuForPlayer_2
 * PROBLEM:  Ignores the "menuid" parameter.
 * SOLUTION: Only hide the correct menu.  DEFAULTS TO FALSE!
 * SEE:      "FIXES_HideMenuForPlayer".
 * AUTHOR:   Y_Less
 * 
 * FIX:      DisableMenu
 * PROBLEM:  Crashes when passed an invalid menu ID.
 * SOLUTION: Don't hide it when passed an invalid menu.
 * SEE:      "FIXES_DisableMenu".
 * AUTHOR:   Y_Less
 * 
 * FIX:      DisableMenuRow
 * PROBLEM:  Crashes when passed an invalid menu ID.
 * SOLUTION: Don't hide it when passed an invalid menu.
 * SEE:      "FIXES_DisableMenuRow".
 * AUTHOR:   Y_Less
 * 
 * FIX:      Menus
 * PROBLEM:  All menu function fixes are included separately for major overhead.
 * SOLUTION: Optionally group them all under one define.
 * SEE:      "FIX_Menus", "_FIX_Menus"
 * AUTHOR:   Y_Less
 * 
 * FIX:      GetPlayerMenu
 * PROBLEM:  Returns previous menu when none is displayed.
 * SOLUTION: Return the correct value.
 * SEE:      "FIXES_GetPlayerMenu", "OnPlayerSelectedMenuRow".
 * AUTHOR:   Y_Less
 * POST:     http://forum.sa-mp.com/showpost.php?p=2295867
 * 
 * FIX:      GetPlayerInterior
 * PROBLEM:  Always returns 0 for NPCs.
 * SOLUTION: Return the correct value.
 * SEE:      "FIXES_GetPlayerInterior", "FIXES_SetPlayerInterior".
 * AUTHOR:   Y_Less
 * POST:     http://forum.sa-mp.com/showpost.php?p=2309246
 * 
 * ==============
 *  STYLE RULES: 
 * ==============
 * 
 * All globals should be "static stock" whenever possible (so they can only be
 *     accessed from this one file).
 * 
 * Statics must start with "FIXES_gs", and all other globals with "FIXES_g".
 * 
 * All functions not overriding existing functions must start with "FIXES_".
 * 
 * Macros must be upper case, use underscores, and start "FIXES_":
 *     "FIXES_LIKE_THIS".
 * 
 * Functions should be upper camel case (as the original functions are)
 *     "FIXES_LikeThis".
 * 
 * Globals (after the prefix) should be upper camel case, and locals lower camel
 *     case "likeThis".
 * 
 * ALS should be used to hook functions and callbacks.
 * 
 * The ALS prefix for chaining is also "FIXES_"
 * 
 * Enums start with "E_" or "e_" depending on type, then follow rules for
 *     macros.
 * 
 * Use "FIXES_gsCallbackHooks" and "E_FIXES_CALLBACK_HOOKS" for ALS chaining.
 * 
 * NO libraries should be included - not even the default SA:MP ones.  Let the
 *     user do it.
 * 
 * Due to the above rule, you cannot assume any third party libraries AT ALL, so
 *     do not use them.
 * 
 * Certain terms may be shortened when dealing with long callback names to avoid
 *     compile truncation warnings (max symbol length is 31).  Current list:
 *     
 *     "Checkpoint" -> "CP"
 *     "Update"     -> "Upd"
 *     "TextDraw"   -> "TD"
 *     "Object"     -> "Obj"
 *     "Player"     -> "P"
 * 
 * Document all fixes at the top of the file, and highlight code.
 * 
 * 4 space TABS - do not edit this file in PAWNO unless you know how to correct
 *     the indentation.
 * 
 * All rules have exceptions, but they must be justifiable.  For example
 *     "IS_FILTERSCRIPT" is a global variable, but is not called
 *     "FIXES_gIsFilterscript" to better match the "FILTERSCRIPT" macro it
 *     replaces.  Now a macro for "_FIXES_gIsFilterscript".
 * 
 * Variables which need to be fully global (i.e. not "static"), but should not
 *     actually be used by other people (e.g. appear inside a macro) should be
 *     prefixed with "_FIXES" instead of "FIXES" to indicate their private use.
 * 
 * No comments beyond the end of column 80 (where the line in "PAWNO" is).
 * 
 * When redefining a native, add a "BAD_" external name declaration with the
 *     "_ALS_" definition so that others may use the original native if they so
 *     desire (with the caveat that it may break all fixes).  Note the "BAD_"
 *     name is meant to indicate the possibility of breaking the fix, not a
 *     comment on the original native function.
 * 
 * If a bug is fixed in some version of the server it can be conditionally
 *     included here.  This is done by checking for the existance of a native
 *     function introduced in the same server version.  For example
 *     "TogglePlayerControllable" was fixed in 0.3eRC6, the same time as the
 *     "SetObjectMaterial" native was introduced, thus the inclusion becomes:
 *     
 *     #if !defined FIX_TogglePlayerControllable
 *         #define FIX_TogglePlayerControllable (!defined SetObjectMaterial)
 *     #endif
 *     
 *     This only includes this fix if that native doesn't exist.
 * 
 * To reduce general memory consumption, strings in this include are stored
 *     globally in constant arrays and referenced.  This is EXACTLY as fast as
 *     using the string constants directly, but means that strings are not
 *     stored in the assembly multiple times (unless the string is only used
 *     once, in which case it's more work for no gain).  See this post for more
 *     details:
 *     
 *     http://forum.sa-mp.com/showpost.php?p=1795601
 * 
 * Documentation explanation:
 * 
 *     FIX:      <Short name>
 *     PROBLEM:  <Description of problem>
 *     SOLUTION: <Description of solution>
 *     SEE:      <List of relevant functions>
 *     AUTHOR:   <Person who wrote the fix>
 *     POST:     <Link to the original post where applicable>
 *     FIXED IN: <Server version of official fix where applicable>
 */

#define _FIXES_IS_UNSET(%0) ((2*%0-1+1)==-1)

// We can add server version compiler code here to only compile fixes that apply
// to the version of the includes for which the user is compiling.
#if !defined FIX_GetPlayerColor
	#if defined FIX_GetPlayerColour
		#define FIX_GetPlayerColor       (FIX_GetPlayerColour)
	#else
		#define FIX_GetPlayerColor       (1)
	#endif
#endif
#if _FIXES_IS_UNSET(FIX_GetPlayerColor)
	#undef FIX_GetPlayerColor
	#define FIX_GetPlayerColor           (0)
#endif

#if !defined FIX_FILTERSCRIPT
	#define FIX_FILTERSCRIPT             (1)
#elseif _FIXES_IS_UNSET(FIX_FILTERSCRIPT)
	#undef FIX_FILTERSCRIPT
	#define FIX_FILTERSCRIPT             (0)
#endif

#if !defined FIX_SpawnPlayer
	#define FIX_SpawnPlayer              (1)
#elseif _FIXES_IS_UNSET(FIX_SpawnPlayer)
	#undef FIX_SpawnPlayer
	#define FIX_SpawnPlayer              (0)
#endif

#if !defined FIX_SetPlayerName
	#define FIX_SetPlayerName            (1)
#elseif _FIXES_IS_UNSET(FIX_SetPlayerName)
	#undef FIX_SetPlayerName
	#define FIX_SetPlayerName            (0)
#endif

#if !defined FIX_GetPlayerSkin
	#define FIX_GetPlayerSkin            (1)
#elseif _FIXES_IS_UNSET(FIX_GetPlayerSkin)
	#undef FIX_GetPlayerSkin
	#define FIX_GetPlayerSkin            (0)
#endif

#if !defined FIX_GetWeaponName
	#define FIX_GetWeaponName            (1)
#elseif _FIXES_IS_UNSET(FIX_GetWeaponName)
	#undef FIX_GetWeaponName
	#define FIX_GetWeaponName            (0)
#endif

#if !defined FIX_SetPlayerWorldBounds
	#define FIX_SetPlayerWorldBounds     (1)
#elseif _FIXES_IS_UNSET(FIX_SetPlayerWorldBounds)
	#undef FIX_SetPlayerWorldBounds
	#define FIX_SetPlayerWorldBounds     (0)
#endif

#if !defined FIX_TogglePlayerControllable
	#if defined SetObjectMaterial
		#define FIX_TogglePlayerControllable (0)
	#else
		#define FIX_TogglePlayerControllable (1)
	#endif
#elseif _FIXES_IS_UNSET(FIX_TogglePlayerControllable)
	#undef FIX_TogglePlayerControllable
	#define FIX_TogglePlayerControllable (0)
#endif

#if !defined FIX_HydraSniper
	#define FIX_HydraSniper              (1)
#elseif _FIXES_IS_UNSET(FIX_HydraSniper)
	#undef FIX_HydraSniper
	#define FIX_HydraSniper              (0)
#endif

#if !defined FIX_IsPlayerInCheckpoint
	#define FIX_IsPlayerInCheckpoint     (1)
#elseif _FIXES_IS_UNSET(FIX_IsPlayerInCheckpoint)
	#undef FIX_IsPlayerInCheckpoint
	#define FIX_IsPlayerInCheckpoint     (0)
#endif

#if !defined FIX_IsPlayerInRaceCheckpoint
	#define FIX_IsPlayerInRaceCheckpoint (1)
#elseif _FIXES_IS_UNSET(FIX_IsPlayerInRaceCheckpoint)
	#undef FIX_IsPlayerInRaceCheckpoint
	#define FIX_IsPlayerInRaceCheckpoint (0)
#endif

#if !defined FIX_GetPlayerWeapon
	#define FIX_GetPlayerWeapon          (1)
#elseif _FIXES_IS_UNSET(FIX_GetPlayerWeapon)
	#undef FIX_GetPlayerWeapon
	#define FIX_GetPlayerWeapon          (0)
#endif

#if !defined FIX_PutPlayerInVehicle
	#define FIX_PutPlayerInVehicle       (1)
#elseif _FIXES_IS_UNSET(FIX_PutPlayerInVehicle)
	#undef FIX_PutPlayerInVehicle
	#define FIX_PutPlayerInVehicle       (0)
#endif

#if !defined FIX_KEY_AIM
	#if defined KEY_AIM
		#define FIX_KEY_AIM              (0)
	#else
		#define FIX_KEY_AIM              (1)
	#endif
#elseif _FIXES_IS_UNSET(FIX_KEY_AIM)
	#undef FIX_KEY_AIM
	#define FIX_KEY_AIM                  (0)
#endif

#if !defined FIX_SetPlayerCheckpoint
	#define FIX_SetPlayerCheckpoint      (1)
#elseif _FIXES_IS_UNSET(FIX_SetPlayerCheckpoint)
	#undef FIX_SetPlayerCheckpoint
	#define FIX_SetPlayerCheckpoint      (0)
#endif

#if !defined FIX_SetPlayerRaceCheckpoint
	#define FIX_SetPlayerRaceCheckpoint  (1)
#elseif _FIXES_IS_UNSET(FIX_SetPlayerRaceCheckpoint)
	#undef FIX_SetPlayerRaceCheckpoint
	#define FIX_SetPlayerRaceCheckpoint  (0)
#endif

#if !defined FIX_TextDrawCreate
	#define FIX_TextDrawCreate           (1)
#elseif _FIXES_IS_UNSET(FIX_TextDrawCreate)
	#undef FIX_TextDrawCreate
	#define FIX_TextDrawCreate           (0)
#endif

#if !defined FIX_TextDrawSetString
	#define FIX_TextDrawSetString        (1)
#elseif _FIXES_IS_UNSET(FIX_TextDrawSetString)
	#undef FIX_TextDrawSetString
	#define FIX_TextDrawSetString        (0)
#endif

#if !defined FIX_AllowInteriorWeapons
	#define FIX_AllowInteriorWeapons     (1)
#elseif _FIXES_IS_UNSET(FIX_AllowInteriorWeapons)
	#undef FIX_AllowInteriorWeapons
	#define FIX_AllowInteriorWeapons     (0)
#endif

#if !defined FIX_OnPlayerEnterVehicle
	#if defined OnPlayerClickMap
		#define FIX_OnPlayerEnterVehicle (0)
	#else
		#define FIX_OnPlayerEnterVehicle (1)
	#endif
#elseif _FIXES_IS_UNSET(FIX_OnPlayerEnterVehicle)
	#undef FIX_OnPlayerEnterVehicle
	#define FIX_OnPlayerEnterVehicle     (0)
#endif

#if !defined FIX_OnPlayerEnterVehicle_2
	#define FIX_OnPlayerEnterVehicle_2   (1)
#elseif _FIXES_IS_UNSET(FIX_OnPlayerEnterVehicle)
	#undef FIX_OnPlayerEnterVehicle_2
	#define FIX_OnPlayerEnterVehicle_2   (0)
#endif

#if !defined FIX_AllowTeleport
	#if defined OnPlayerClickMap
		#define FIX_AllowTeleport        (1)
	#else
		#define FIX_AllowTeleport        (0)
	#endif
#elseif _FIXES_IS_UNSET(FIX_AllowTeleport)
	#undef FIX_AllowTeleport
	#define FIX_AllowTeleport            (0)
#endif

#if !defined FIX_SetPlayerSpecialAction
	#define FIX_SetPlayerSpecialAction   (1)
#elseif _FIXES_IS_UNSET(FIX_SetPlayerSpecialAction)
	#undef FIX_SetPlayerSpecialAction
	#define FIX_SetPlayerSpecialAction   (0)
#endif

#if !defined FIX_OnDialogResponse
	#if defined GetVehicleModelInfo
		#define FIX_OnDialogResponse     (0)
	#else
		#define FIX_OnDialogResponse     (1)
	#endif
#elseif _FIXES_IS_UNSET(FIX_OnDialogResponse)
	#undef FIX_OnDialogResponse
	#define FIX_OnDialogResponse         (0)
#endif

#if !defined FIX_GetPlayerDialog
	#define FIX_GetPlayerDialog          (0)
#elseif _FIXES_IS_UNSET(FIX_GetPlayerDialog)
	#undef FIX_GetPlayerDialog
	#define FIX_GetPlayerDialog          (0)
#endif

#if !defined FIX_SetSpawnInfo
	#if defined GetPlayerVersion
		#define FIX_SetSpawnInfo         (0)
	#else
		#define FIX_SetSpawnInfo         (1)
	#endif
#elseif _FIXES_IS_UNSET(FIX_SetSpawnInfo)
	#undef FIX_SetSpawnInfo
	#define FIX_SetSpawnInfo             (0)
#endif

#if !defined FIX_SetPlayerSkin
	#define FIX_SetPlayerSkin            (1)
#elseif _FIXES_IS_UNSET(FIX_SetPlayerSkin)
	#undef FIX_SetPlayerSkin
	#define FIX_SetPlayerSkin            (0)
#endif

#if !defined FIX_HideMenuForPlayer
	#define FIX_HideMenuForPlayer        (1)
#elseif _FIXES_IS_UNSET(FIX_HideMenuForPlayer)
	#undef FIX_HideMenuForPlayer
	#define FIX_HideMenuForPlayer        (0)
#endif

#if !defined FIX_valstr
	#define FIX_valstr                   (1)
#elseif _FIXES_IS_UNSET(FIX_valstr)
	#undef FIX_valstr
	#define FIX_valstr                   (0)
#endif

#if !defined FIX_file_inc
	#define FIX_file_inc                 (0)
#elseif _FIXES_IS_UNSET(FIX_file_inc)
	#undef FIX_file_inc
	#define FIX_file_inc                 (0)
#endif

#if !defined FIX_fclose
	#define FIX_fclose                   (FIX_file_inc)
#elseif _FIXES_IS_UNSET(FIX_fclose)
	#undef FIX_fclose
	#define FIX_fclose                   (0)
#endif

#if !defined FIX_fwrite
	#define FIX_fwrite                   (FIX_file_inc)
#elseif _FIXES_IS_UNSET(FIX_fwrite)
	#undef FIX_fwrite
	#define FIX_fwrite                   (0)
#endif

#if !defined FIX_fread
	#define FIX_fread                    (FIX_file_inc)
#elseif _FIXES_IS_UNSET(FIX_fread)
	#undef FIX_fread
	#define FIX_fread                    (0)
#endif

#if !defined FIX_fputchar
	#define FIX_fputchar                 (FIX_file_inc)
#elseif _FIXES_IS_UNSET(FIX_fputchar)
	#undef FIX_fputchar
	#define FIX_fputchar                 (0)
#endif

#if !defined FIX_fgetchar
	#define FIX_fgetchar                 (FIX_file_inc)
#elseif _FIXES_IS_UNSET(FIX_fgetchar)
	#undef FIX_fgetchar
	#define FIX_fgetchar                 (0)
#endif

#if !defined FIX_fblockwrite
	#define FIX_fblockwrite              (FIX_file_inc)
#elseif _FIXES_IS_UNSET(FIX_fblockwrite)
	#undef FIX_fblockwrite
	#define FIX_fblockwrite              (0)
#endif

#if !defined FIX_fblockread
	#define FIX_fblockread               (FIX_file_inc)
#elseif _FIXES_IS_UNSET(FIX_fblockread)
	#undef FIX_fblockread
	#define FIX_fblockread               (0)
#endif

#if !defined FIX_fseek
	#define FIX_fseek                    (FIX_file_inc)
#elseif _FIXES_IS_UNSET(FIX_fseek)
	#undef FIX_fseek
	#define FIX_fseek                    (0)
#endif

#if !defined FIX_flength
	#define FIX_flength                  (FIX_file_inc)
#elseif _FIXES_IS_UNSET(FIX_flength)
	#undef FIX_flength
	#define FIX_flength                  (0)
#endif

#if !defined FIX_IsPlayerAttachedObjSlotUsed
	#define FIX_IsPlayerAttachedObjSlotUsed (1)
#elseif _FIXES_IS_UNSET(FIX_IsPlayerAttachedObjSlotUsed)
	#undef FIX_IsPlayerAttachedObjSlotUsed
	#define FIX_IsPlayerAttachedObjSlotUsed (0)
#endif

#if !defined FIX_SetPlayerAttachedObject
	#define FIX_SetPlayerAttachedObject  (1)
#elseif _FIXES_IS_UNSET(FIX_SetPlayerAttachedObject)
	#undef FIX_SetPlayerAttachedObject
	#define FIX_SetPlayerAttachedObject  (0)
#endif

#if !defined FIX_OnPlayerDeath
	#define FIX_OnPlayerDeath            (1)
#elseif _FIXES_IS_UNSET(FIX_OnPlayerDeath)
	#undef FIX_OnPlayerDeath
	#define FIX_OnPlayerDeath            (0)
#endif

#if !defined FIX_strins
	#define FIX_strins                   (1)
#elseif _FIXES_IS_UNSET(FIX_strins)
	#undef FIX_strins
	#define FIX_strins                   (0)
#endif

#if !defined FIX_IsPlayerConnected
	#define FIX_IsPlayerConnected        (1)
#elseif _FIXES_IS_UNSET(FIX_IsPlayerConnected)
	#undef FIX_IsPlayerConnected
	#define FIX_IsPlayerConnected        (0)
#endif

#if !defined FIX_OnPlayerCommandText
	#if defined _ALS_OnPlayerCommandText
		#define FIX_OnPlayerCommandText  (0)
	#else
		#define FIX_OnPlayerCommandText  (1)
	#endif
#elseif _FIXES_IS_UNSET(FIX_OnPlayerCommandText)
	#undef FIX_OnPlayerCommandText
	#define FIX_OnPlayerCommandText      (0)
#endif

#if !defined FIX_TrainExit
	#define FIX_TrainExit                (1)
#elseif _FIXES_IS_UNSET(FIX_TrainExit)
	#undef FIX_TrainExit
	#define FIX_TrainExit                (0)
#endif

#if !defined FIX_Kick
	#define FIX_Kick                     (1)
#elseif _FIXES_IS_UNSET(FIX_Kick)
	#undef FIX_Kick
	#define FIX_Kick                     (0)
#endif

#if !defined FIX_OnVehicleMod
	#define FIX_OnVehicleMod             (1)
#elseif _FIXES_IS_UNSET(FIX_OnVehicleMod)
	#undef FIX_OnVehicleMod
	#define FIX_OnVehicleMod             (0)
#endif

#if !defined FIX_random
	#define FIX_random                   (0)
#elseif _FIXES_IS_UNSET(FIX_random)
	#undef FIX_random
	#define FIX_random                   (0)
#endif

#if !defined FIX_sleep
	#define FIX_sleep                    (1)
#elseif _FIXES_IS_UNSET(FIX_sleep)
	#undef FIX_sleep
	#define FIX_sleep                    (0)
#endif

#if !defined FIX_Menus
	#define FIX_Menus                    (1)
#elseif _FIXES_IS_UNSET(FIX_Menus)
	#undef FIX_Menus
	#define FIX_Menus                    (0)
#endif

#if !defined FIX_AddMenuItem
	#define FIX_AddMenuItem              (FIX_Menus)
#elseif _FIXES_IS_UNSET(FIX_AddMenuItem)
	#undef FIX_AddMenuItem
	#define FIX_AddMenuItem              (0)
#endif

#if !defined FIX_SetMenuColumnHeader
	#define FIX_SetMenuColumnHeader      (FIX_Menus)
#elseif _FIXES_IS_UNSET(FIX_SetMenuColumnHeader)
	#undef FIX_SetMenuColumnHeader
	#define FIX_SetMenuColumnHeader      (0)
#endif

#if !defined FIX_ShowMenuForPlayer
	#define FIX_ShowMenuForPlayer        (FIX_Menus)
#elseif _FIXES_IS_UNSET(FIX_ShowMenuForPlayer)
	#undef FIX_ShowMenuForPlayer
	#define FIX_ShowMenuForPlayer        (0)
#endif

#if !defined FIX_HideMenuForPlayer
	#define FIX_HideMenuForPlayer        (FIX_Menus)
#elseif _FIXES_IS_UNSET(FIX_HideMenuForPlayer)
	#undef FIX_HideMenuForPlayer
	#define FIX_HideMenuForPlayer        (0)
#endif

#if !defined FIX_GetPlayerMenu
	#define FIX_GetPlayerMenu            (1)
#elseif _FIXES_IS_UNSET(FIX_GetPlayerMenu)
	#undef FIX_GetPlayerMenu
	#define FIX_GetPlayerMenu            (0)
#endif

#if !defined FIX_HideMenuForPlayer_2
	#define FIX_HideMenuForPlayer_2      (0)
#elseif _FIXES_IS_UNSET(FIX_HideMenuForPlayer_2)
	#undef FIX_HideMenuForPlayer_2
	#define FIX_HideMenuForPlayer_2      (0)
#elseif FIX_HideMenuForPlayer_2 && !FIX_GetPlayerMenu
	#error FIX_HideMenuForPlayer_2 requires FIX_GetPlayerMenu
#endif

#if !defined FIX_DisableMenu
	#define FIX_DisableMenu              (FIX_Menus)
#elseif _FIXES_IS_UNSET(FIX_DisableMenu)
	#undef FIX_DisableMenu
	#define FIX_DisableMenu              (0)
#endif

#if !defined FIX_DisableMenuRow
	#define FIX_DisableMenuRow           (FIX_Menus)
#elseif _FIXES_IS_UNSET(FIX_DisableMenuRow)
	#undef FIX_DisableMenuRow
	#define FIX_DisableMenuRow           (0)
#endif

#if FIX_Menus || FIX_AddMenuItem || FIX_SetMenuColumnHeader || FIX_ShowMenuForPlayer || FIX_HideMenuForPlayer || FIX_DisableMenu || FIX_DisableMenuRow
	#define _FIX_Menus                (1)
#else
	#define _FIX_Menus                (0)
#endif

#if !defined FIX_GetPlayerInterior
	#define FIX_GetPlayerInterior        (1)
#elseif _FIXES_IS_UNSET(FIX_GetPlayerInterior)
	#undef FIX_GetPlayerInterior
	#define FIX_GetPlayerInterior        (0)
#endif

/* 
 * FIXES_SilentKick
 * 
 * If this define is set to 1, then players will not be given a message when
 * they are kicked for cheats, instead they will just loose connection to the
 * server.
 */
#if !defined FIXES_SilentKick
	#define FIXES_SilentKick 0
#elseif _FIXES_IS_UNSET(FIXES_SilentKick)
	#undef FIXES_SilentKick
	#define FIXES_SilentKick 0
#endif

/* 
 * FIXES_Debug
 * 
 * If this define is set to 1, then debug printing is turned on for any
 * functions which may use it.  Otherwise, the compiler entirely removes the
 * code to print anything, leaving 0 run-time overhead.
 */
#if defined FIXES_Debug
	#if _FIXES_IS_UNSET(FIXES_Debug)
		#undef FIXES_Debug
	#elseif FIXES_Debug == 1
		#define FIXES_PRINTF(%0); print(_FIXES_gIsFilterscript ? ("* FIXES_PRINTF (FS):") : ("* FIXES_PRINTF (GM):")),printf("*** " %0);
	#else
		#undef FIXES_Debug
	#endif
#endif
#if !defined FIXES_PRINTF
	#define FIXES_Debug 0
	#define FIXES_PRINTF(%0);
#endif

/* 
 * INVALID_DIALOG_ID
 * 
 * Set when a player can't see a dialog.
 */
#if !defined INVALID_DIALOG_ID
	#define INVALID_DIALOG_ID (-1)
#endif

/* 
 * FIXES_Single
 * 
 * If this define is set to 1, then the old style include is used, with no
 * support for multiple scripts running at the same time on the server (i.e. no
 * gamemodes and filter scripts at the same time).  You can only have one or the
 * other or bugs.
 */
#if !defined FIXES_Single
	#define FIXES_Single (0)
#elseif _FIXES_IS_UNSET(FIXES_Single)
	#undef FIXES_Single
	#define FIXES_Single (1)
#endif

/* 
 * E_FIXES_WORLDBOUND_DATA
 * 
 * Store data for each player on their worldbound data.
 */
enum E_FIXES_WORLDBOUND_DATA
{
	// "Previous".
	Float:E_FIXES_WORLDBOUND_DATA_PX,
	Float:E_FIXES_WORLDBOUND_DATA_PY,
	Float:E_FIXES_WORLDBOUND_DATA_PZ,
	// "Lower".
	Float:E_FIXES_WORLDBOUND_DATA_LX,
	Float:E_FIXES_WORLDBOUND_DATA_LY,
	// "Upper".
	Float:E_FIXES_WORLDBOUND_DATA_UX,
	Float:E_FIXES_WORLDBOUND_DATA_UY
}

/* 
 * e_FIXES_BOOLS
 * 
 * Collection of boolean values for players, designed to collect multiple checks
 * in to one variable to reduce memory consumption.
 */
enum e_FIXES_BOOLS (<<= 1)
{
	// Handy definition for nothing set.
	e_FIXES_BOOLS_NONE = 0,
	// Does this player have worldbounds enabled?
	e_FIXES_BOOLS_WORLDBOUNDS = 1,
	e_FIXES_BOOLS_UNCONTROLLABLE,
	e_FIXES_BOOLS_PUT_IN_VEHICLE,
	e_FIXES_BOOLS_BLOCK,
	e_FIXES_BOOLS_TELEPORT,
	e_FIXES_BOOLS_CONNECTED,
	e_FIXES_BOOLS_INTERIOR,
	e_FIXES_BOOLS_PUT_IN_TRAIN,
	e_FIXES_BOOLS_KICKED,
	e_FIXES_BOOLS_ON_PLAYER_CONNECT
}

/* 
 * e_FIXES_SETTINGS
 * 
 * Collection of boolean values for the script as a whole.  Stores a variety of
 * settings that are true/false.
 */
enum e_FIXES_SETTINGS (<<= 1)
{
	// Handy definition for nothing set.
	e_FIXES_SETTINGS_NONE = 0,
	e_FIXES_SETTINGS_INTERIOR = 1,
	e_FIXES_SETTINGS_ADMIN_TELEPORT,
	e_FIXES_SETTINGS_IN_CHARGE,
	e_FIXES_SETTINGS_DROP_ALL_DATA,
	e_FIXES_SETTINGS_MENU_SET,
	e_FIXES_SETTINGS_ENDING
}

/* 
 * _FIXES_CEILDIV
 * 
 * Do a ceiling division of the first number by the second number.
 */
#define _FIXES_CEILDIV(%0,%1) (((%0) + (%1) - 1) / (%1))

/* 
 * _FIXES_INFINITY
 * 
 * IEEE 754 definition of infinity.
 */
#define _FIXES_INFINITY (Float:0x7F800000)

/* 
 * _FIXES_N_INFINITY
 * 
 * IEEE 754 definition of negative infinity.
 */
#define _FIXES_N_INFINITY (Float:0xFF800000)

/* 
 * _FIXES_ATTACHMENTS
 * 
 * The number of players whose attachment data (10-bits) can be stored in one
 * cell.
 */
#define _FIXES_ATTACHMENTS (cellbits / MAX_PLAYER_ATTACHED_OBJECTS)

// These varaibles are NOT pre-processor dependent as they are stock.  It's just
// simpler than trying to figure out when or if a semi-colon is needed.
#if !FIX_FILTERSCRIPT
static
#endif
stock
	/* 
	 * bool:_FIXES_gIsFilterscript
	 * 
	 * Runtime equivalent of "FILTERSCRIPT" for when it is not set by the user.
	 */
	bool:_FIXES_gIsFilterscript;

static stock
	/* 
	 * FIXES_gsValidMenus[_FIXES_CEILDIV(MAX_MENUS, cellbits)]
	 * 
	 * A record of which menus have and haven't been shown yet.
	 */
	FIXES_gsValidMenus[_FIXES_CEILDIV(MAX_MENUS, cellbits)],
	/* 
	 * FIXES_gsPlayerIP[MAX_PLAYERS]
	 * 
	 * A player's IP as a 32-bit integer.
	 */
	FIXES_gsPlayerIP[MAX_PLAYERS] = {-1, ...},
	/* 
	 * FIXES_gsPlayerSkin[MAX_PLAYERS]
	 * 
	 * The skin the player is currently using.
	 */
	FIXES_gsPlayerSkin[MAX_PLAYERS],
	/* 
	 * e_FIXES_BOOLEAN_DATA:FIXES_gsPlayerBools[MAX_PLAYERS]
	 * 
	 * Collection of boolean values for players.
	 */
	e_FIXES_BOOLS:FIXES_gsPlayerBools[MAX_PLAYERS],
	/* 
	 * FIXES_gsWorldbounds[MAX_PLAYERS][E_FIXES_WORLDBOUND_DATA]
	 * 
	 * All data for players on where their worldbounds are and where they last
	 * were before they went through the bounds by crouching.
	 */
	FIXES_gsWorldbounds[MAX_PLAYERS][E_FIXES_WORLDBOUND_DATA],
	/* 
	 * FIXES_gsPlayerWeapon[MAX_PLAYERS]
	 * 
	 * Stores the weapon set by "SetPlayerArmedWeapon" when in a vehicle.
	 */
	FIXES_gsPlayerWeapon[MAX_PLAYERS],
	/* 
	 * FIXES_gsVehicleSeatData[MAX_PLAYERS]
	 * 
	 * What vehicle the player is due to go in.
	 */
	FIXES_gsVehicleSeatData[MAX_PLAYERS],
	/* 
	 * FIXES_gsVehicleLocked[(MAX_PLAYERS * MAX_VEHICLES + cellbits - 1) / cellbits]
	 * 
	 * Is this vehicle locked for a player.  This is a compressed 2D binary
	 * array, made by concatenating many bits together (saves 1kb-3kb)!  Is
	 * there a reason this array exists?
	 */
	//FIXES_gsVehicleLocked[_FIXES_CEILDIV(MAX_PLAYERS * MAX_VEHICLES, cellbits)],
	/* 
	 * FIXES_gsDialogID[MAX_PLAYERS]
	 * 
	 * Stores the true ID of the dialog the player is looking at to prevent
	 * spoofing.
	 */
	FIXES_gsDialogID[MAX_PLAYERS] = {-1, ...},
	/* 
	 * e_FIXES_SETTINGS:FIXES_gsSettings
	 * 
	 * A collection of 1-bit options, compressed together to save space.
	 */
	e_FIXES_SETTINGS:FIXES_gsSettings,
	/* 
	 * FIXES_gsObjectSlots[_FIXES_CEILDIV(MAX_PLAYERS, _FIXES_ATTACHMENTS)]
	 * 
	 * A record of which attached object slots a player has used.
	 */
	FIXES_gsObjectSlots[_FIXES_CEILDIV(MAX_PLAYERS, _FIXES_ATTACHMENTS)],
	/* 
	 * FIXES_gsLastAnimation[MAX_PLAYERS]
	 * 
	 * The last animation a player used.
	 */
	FIXES_gsLastAnimation[MAX_PLAYERS],
	/* 
	 * FIXES_gsCurrentMenu[MAX_PLAYERS]
	 * 
	 * The menu the player can currently see.
	 */
	Menu:FIXES_gsCurrentMenu[MAX_PLAYERS] = {Menu:INVALID_MENU, ...};

static stock const
	/* 
	 * FIXES_gscPlayerColours[100]
	 * 
	 * There are only 100 colours used by default, with SA:MP looping through
	 * them repeatedly.
	 */
	FIXES_gscPlayerColours[100] =
		{
			0xFF8C13FF, 0xC715FFFF, 0x20B2AAFF, 0xDC143CFF, 0x6495EDFF,
			0xF0E68CFF, 0x778899FF, 0xFF1493FF, 0xF4A460FF, 0xEE82EEFF,
			0xFFD720FF, 0x8B4513FF, 0x4949A0FF, 0x148B8BFF, 0x14FF7FFF,
			0x556B2FFF, 0x0FD9FAFF, 0x10DC29FF, 0x534081FF, 0x0495CDFF,
			0xEF6CE8FF, 0xBD34DAFF, 0x247C1BFF, 0x0C8E5DFF, 0x635B03FF,
			0xCB7ED3FF, 0x65ADEBFF, 0x5C1ACCFF, 0xF2F853FF, 0x11F891FF,
			0x7B39AAFF, 0x53EB10FF, 0x54137DFF, 0x275222FF, 0xF09F5BFF,
			0x3D0A4FFF, 0x22F767FF, 0xD63034FF, 0x9A6980FF, 0xDFB935FF,
			0x3793FAFF, 0x90239DFF, 0xE9AB2FFF, 0xAF2FF3FF, 0x057F94FF, 
			0xB98519FF, 0x388EEAFF, 0x028151FF, 0xA55043FF, 0x0DE018FF,
			0x93AB1CFF, 0x95BAF0FF, 0x369976FF, 0x18F71FFF, 0x4B8987FF,
			0x491B9EFF, 0x829DC7FF, 0xBCE635FF, 0xCEA6DFFF, 0x20D4ADFF,
			0x2D74FDFF, 0x3C1C0DFF, 0x12D6D4FF, 0x48C000FF, 0x2A51E2FF,
			0xE3AC12FF, 0xFC42A8FF, 0x2FC827FF, 0x1A30BFFF, 0xB740C2FF,
			0x42ACF5FF, 0x2FD9DEFF, 0xFAFB71FF, 0x05D1CDFF, 0xC471BDFF,
			0x94436EFF, 0xC1F7ECFF, 0xCE79EEFF, 0xBD1EF2FF, 0x93B7E4FF,
			0x3214AAFF, 0x184D3BFF, 0xAE4B99FF, 0x7E49D7FF, 0x4C436EFF,
			0xFA24CCFF, 0xCE76BEFF, 0xA04E0AFF, 0x9F945CFF, 0xDCDE3DFF, 
			0x10C9C5FF, 0x70524DFF, 0x0BE472FF, 0x8A2CD7FF, 0x6152C2FF,
			0xCF72A9FF, 0xE59338FF, 0xEEDC2DFF, 0xD8C762FF, 0xD8C762FF
		},
	/* 
	 * FIXES_gscMaxPassengers[]
	 * 
	 * This is a compressed (4-bit) list of the maximum number of passengers in
	 * any vehicle, confirmed by a number of sources. "F" (15) means invalid
	 * vehicle.
	 */
	FIXES_gscMaxPassengers[] =
		{
			0x10331113, 0x11311131, 0x11331313, 0x80133301, 0x1381F110, 0x10311103, 0x10001F10, 0x11113311, 0x13113311,
			0x31101100, 0x30001301, 0x11031311, 0x11111331, 0x10013111, 0x01131100, 0x11111110, 0x11100031, 0x11130221,
			0x33113311, 0x11111101, 0x33101133, 0x101001F0, 0x03133111, 0xFF11113F, 0x13330111, 0xFF131111, 0x0000FF3F
		},
	/*
	 * FIXES_gscVehicleMods[][]
	 * 
	 * This is a bit array of all the valid mods (-1000) for all vehicles (-400)
	 * EXCEPT for vehicle 576 (Tornado), which has just TWO extra mods on it,
	 * that should spill over in to an extra cell of data (requiring an extra
	 * 848 bytes of data total to make the array work).  Instead this (hopefully
	 * rare) case is handled explicitly in "OnVehicleMod".
	 */
	FIXES_gscVehicleMods[][] =
		{
			{0b00000011001111000010011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000110100010011111111010, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000111100000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010001110110010011110000101, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010101111000100011100000011, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000011101110100010011110001010, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010100011100000011110001010, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010001100010000011101000100, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010001010000000011100111010, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010101111010100011100000001, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010001110100010011110000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010001010000000011101111010, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010011110100010011111001010, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010100000100010011110001010, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000111100000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010001111100000011111000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000011011100000011011100110000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000011000111010010011101110101, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010101111100100011110001000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000111100000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000010000011101110001, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010100110100000111111001110, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000001100000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000011001110000010011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010001111111000011110010101, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010100111110000011110001100, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000111100000000000000, 0b00000000000000000000000000000000},
			{0b00000010100101100010011111101010, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000111100000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010001101101100011110000010, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010100111100001111111001010, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b11111100000000000000010000110111, 0b00000000000000000000000000000000, 0b00000010000111000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000011111111100110000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000001101110000111, 0b00000000000000000000000000000001, 0b00000001111000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000011100111100000011111010010, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000111100000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010001111001100011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000110000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000011100011100000011111010110, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000111100000000000000, 0b00000000000000000000000000000000},
			{0b00000010001111010000011100001001, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000001100000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010100111100001111110001010, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000111100000000000000, 0b00000000000000000000000000000000},
			{0b00000010100111000000011101111010, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000111100000000000000, 0b00000000000000000000000000000000},
			{0b00000010101111010000011101101100, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b11111111111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000111111000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111111111110, 0b00000000000000000000000000000111, 0b11000000000000000000000000000000, 0b00000000000000000010000000000111},
			{0b11111110000000000000011100000000, 0b00000000000000000000000000000011, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000011110000000000, 0b00000000000000000000011000000000},
			{0b11001110000000000000011100000000, 0b11111111100000000000000000000000, 0b00000000111111111111111000000001, 0b00000000000000000000000000000111, 0b00111100000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000001111111100, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000001111000000000000000000, 0b00000000000000000001100000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000011111111110000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000011110000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000001000111, 0b00000000000000000000000000111110, 0b00111100000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000001110000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000001111, 0b00000000000000000000000000000000, 0b00000000000000111100000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000001111000000, 0b11000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010100101100000011111000010, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000011000101110010011111110001, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000110000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010010101100010011111110000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000011100111100000011111000010, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000111100000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000},
			{0b00000010000000000000011100000000, 0b00000000000000000000000000000000, 0b00000000111111111111111000000000, 0b00000000000000000000000000000111, 0b00000000000000000000000000000000, 0b00000000000000000000000000000000}
		},
	/*
	 * FIXES_gscNULL[]
	 * 
	 * NULL.  This is stored as a global string to reduce memory usage.
	 */
	FIXES_gscNULL[] = "\1\0",
	/*
	 * FIXES_gscDot[]
	 * 
	 * ".".
	 */
	FIXES_gscDot[] = ".",
	/*
	 * FIXES_gscSpec@[]
	 * 
	 * Specifier "".
	 */
	FIXES_gscSpec@[] = "",
	/*
	 * FIXES_gscSpec@i[]
	 * 
	 * Specifier "i".
	 */
	FIXES_gscSpec@i[] = "i",
	/*
	 * FIXES_gscSpec@ii[]
	 * 
	 * Specifier "ii".
	 */
	FIXES_gscSpec@ii[] = "ii",
	/*
	 * FIXES_gscSpec@iii[]
	 * 
	 * Specifier "iii".
	 */
	FIXES_gscSpec@iii[] = "iii",
	/*
	 * FIXES_gscSpec@ifff[]
	 * 
	 * Specifier "ifff".
	 */
	FIXES_gscSpec@ifff[] = "ifff",
	/*
	 * FIXES_gscSpec@iffff[]
	 * 
	 * Specifier "iffff".
	 */
	FIXES_gscSpec@iffff[] = "iffff",
	/*
	 * FIXES_gscSpec@is[]
	 * 
	 * Specifier "is".
	 */
	FIXES_gscSpec@is[] = "is",
	/*
	 * FIXES_gscSpec@iiiis[]
	 * 
	 * Specifier "iiiis".
	 */
	FIXES_gscSpec@iiiis[] = "iiiis",
	/*
	 * FIXES_gscSpec@iiiii[]
	 * 
	 * Specifier "iiiii".
	 */
	FIXES_gscSpec@iiiii[] = "iiiii",
	/*
	 * FIXES_gscTempName[]
	 * 
	 * The temporary name to give when renaming people.
	 */
	FIXES_gscTempName[] = "FIXES_TEMP_NAME",
	/*
	 * FIXES_gscOrderProperty[]
	 * 
	 * The property to check for script ordering.
	 */
	FIXES_gscOrderProperty[] = "FIXES_gscOrderProperty",
	/*
	 * FIXES_gscNoGMProperty[]
	 * 
	 * Call "_FIXES_DetermineOrder" in the GM or not?
	 */
	FIXES_gscNoGMProperty[] = "FIXES_gscNoGMProperty",
	/*
	 * FIXES_gscDetermineOrder[]
	 * 
	 * Name of the ordering callback.
	 */
	FIXES_gscDetermineOrder[] = "_FIXES_DetermineOrder",
	/*
	 * FIXES_gscSetPlayerMenu[]
	 * 
	 * Name of the remote set player menu function.
	 */
	FIXES_gscSetPlayerMenu[] = "_FIXES_SetPlayerMenu",
	/*
	 * FIXES_gscClearPlayerMenu[]
	 * 
	 * Name of the remote function to clear a player's menu set.
	 */
	FIXES_gscClearPlayerMenu[] = "_FIXES_ClearPlayerMenu",
	/*
	 * FIXES_gscAllowTeleport[]
	 * 
	 * Name of the remote allow teleport function.
	 */
	FIXES_gscAllowTeleport[] = "_FIXES_AllowTeleport",
	/*
	 * FIXES_gscPutPlayerInVehicle[]
	 * 
	 * Name of the remote vehicle entry function.
	 */
	FIXES_gscPutPlayerInVehicle[] = "_FIXES_PutPlayerInVehicle",
	/*
	 * FIXES_gscAllowInteriorWeapons[]
	 * 
	 * Name of the remote interior weapons function.
	 */
	FIXES_gscAllowInteriorWeapons[] = "_FIXES_AllowInteriorWeapons",
	/*
	 * FIXES_gscSetPlayerAttachedObj[]
	 * 
	 * Name of the remote attache object function.
	 */
	FIXES_gscSetPlayerAttachedObj[] = "_FIXES_SetPlayerAttachedObject",
	/*
	 * FIXES_gscTogglePlayerControl[]
	 * 
	 * Name of the remote player toggle function.
	 */
	FIXES_gscTogglePlayerControl[] = "_FIXES_TogglePlayerControllable",
	/*
	 * FIXES_gscSetPlayerWorldBounds[]
	 * 
	 * Name of the remote world bounds function.
	 */
	FIXES_gscSetPlayerWorldBounds[] = "_FIXES_SetPlayerWorldBounds",
	/*
	 * FIXES_gscReturnProperty[]
	 * 
	 * The property for accurate returns.
	 */
	FIXES_gscReturnProperty[] = "FIXES_gscReturnProperty",
	/*
	 * FIXES_gscMenuProperty[]
	 * 
	 * The property for a player's current menu.
	 */
	FIXES_gscMenuProperty[] = "FIXES_gscMenuProperty";

static stock
	/*
	 * FIXES_pvarNotNewPlayer[]
	 * 
	 * This variable records wether or not this player is brand new to the
	 * server, and not just having "OnPlayerConnect" called due to a script
	 * load.  There are certain functions that need applying only the very first
	 * time they connect, then this gets set.
	 */
	FIXES_pvarNotNewPlayer[] = "FIXES_pvarNotNewPlayer",
	/*
	 * FIXES_pvarPlayerWeapon[]
	 * 
	 * Name of the pvar in which to store the player's current weapon.
	 */
	FIXES_pvarPlayerWeapon[] = "FIXES_pvarPlayerWeapon",
	/*
	 * FIXES_pvarPlayerSkin[]
	 * 
	 * Name of the pvar in which to store the player's current skin.
	 */
	FIXES_pvarPlayerSkin[] = "FIXES_pvarPlayerSkin",
	/*
	 * FIXES_gscKick[]
	 * 
	 * Name of the kick timer function.
	 */
	FIXES_gscKick[] = "_FIXES_Kick",
	/*
	 * FIXES_pvarKick[]
	 * 
	 * Name of the pvar in which to store a player's kick timer.
	 */
	FIXES_pvarKick[] = "FIXES_pvarKick",
	/*
	 * FIXES_pvarPlayerDialog[]
	 * 
	 * Name of the pvar in which to store the player's current dialogid.
	 */
	FIXES_pvarPlayerDialog[] = "FIXES_pvarPlayerDialog",
	/*
	 * FIXES_pvarCurrentDialog[]
	 * 
	 * Used in OnDialogResponse to be able to get the correct ID in multiple
	 * scripts while still correctly resetting the ID for future use.
	 */
	FIXES_pvarCurrentDialog[] = "FIXES_pvarCurrentDialog";

/* 
 * _FIXES_KEY_AIM
 * KEY_AIM
 * 
 * Because the default SA:MP includes missed this one.
 */
#define _FIXES_KEY_AIM                   (128)
#if FIX_KEY_AIM
	#define KEY_AIM                      _FIXES_KEY_AIM
#endif

/* 
 * IS_FILTERSCRIPT
 * 
 * "FILTERSCRIPT" can't always be relied on to be set.  This is not a pre-
 * processor macro, but may be better than nothing (also used internally).
 */
#if FIX_FILTERSCRIPT
	#define IS_FILTERSCRIPT _FIXES_gIsFilterscript
#endif

/* 
 * FIXES_DetermineOrder()
 * 
 * Figure out which script is called first by callbacks.
 */
#if !FIXES_Single
	forward _FIXES_DetermineOrder();
	
	static FIXES_DetermineOrder()
	{
		deleteproperty(5, FIXES_gscOrderProperty),
		// Called in the Game Mode first (thus needs correcting).
		setproperty(5, FIXES_gscNoGMProperty, 1),
		CallRemoteFunction(FIXES_gscDetermineOrder, FIXES_gscSpec@),
		deleteproperty(5, FIXES_gscNoGMProperty),
		CallRemoteFunction(FIXES_gscDetermineOrder, FIXES_gscSpec@);
	}
#endif

/* 
 * _FIXES_IncludeFuncs()
 * 
 * Include functions used by "SYSREQ.C".
 */

#if FIX_sleep
	forward _FIXES_IncludeFuncs();
	
	public _FIXES_IncludeFuncs()
	{
		#if FIX_sleep
			heapspace();
		#endif
	}
#endif

/*
 * FIXES_IsPlayerConnected(playerid)
 *
 * FIXES:
 *     IsPlayerConnected
 */
#if FIX_IsPlayerConnected
	stock FIXES_IsPlayerConnected(playerid)
	{
		if (playerid & 0xFFFF0000)
		{
			return false;
		}
		return IsPlayerConnected(playerid);
	}
	
	#if defined _ALS_IsPlayerConnected
		#undef IsPlayerConnected
	#else
		
		native BAD_IsPlayerConnected(playerid) = IsPlayerConnected;
		
		#define _ALS_IsPlayerConnected
	#endif
	#define IsPlayerConnected FIXES_IsPlayerConnected
#endif

/* 
 * OnFilterScriptInit()
 * 
 * Set "IS_FILTERSCRIPT" to true as this callback is ONLY called if this script
 * is actually a FilterScript.  Then call "FIXES_OnScriptInit".
 * 
 * FIXES:
 *     IS_FILTERSCRIPT
 */
public OnFilterScriptInit()
{
	_FIXES_gIsFilterscript = true;
	#if !FIXES_Single
		FIXES_DetermineOrder(),
		FIXES_gsSettings &= ~e_FIXES_SETTINGS_DROP_ALL_DATA;
	#endif
	#if defined FIXES_OnFilterScriptInit
		return FIXES_OnFilterScriptInit();
	#else
		return 1;
	#endif
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit FIXES_OnFilterScriptInit

#if defined FIXES_OnFilterScriptInit
	forward FIXES_OnFilterScriptInit();
#endif

/* 
 * OnGameModeInit()
 * 
 * Call "FIXES_OnScriptInit" if this is not a FilterScript.
 * 
 * FIXES:
 *     IS_FILTERSCRIPT
 *     AllowInteriorWeapons
 *     AllowTeleport
 */
public OnGameModeInit()
{
	// =============================
	//  START: AllowInteriorWeapons 
	// =============================
	#if FIX_AllowInteriorWeapons
		FIXES_gsSettings &= ~e_FIXES_SETTINGS_INTERIOR;
	#endif
	// ===========================
	//  END: AllowInteriorWeapons 
	// ===========================
	
	// ======================
	//  START: AllowTeleport 
	// ======================
	#if FIX_AllowTeleport && !defined FILTERSCRIPT
		FIXES_gsSettings &= ~e_FIXES_SETTINGS_ADMIN_TELEPORT;
	#endif
	// ======================
	//  END:   AllowTeleport 
	// ======================
	
	#if !FIXES_Single
		if (!_FIXES_gIsFilterscript)
		{
			FIXES_DetermineOrder();
		}
		FIXES_gsSettings &= ~e_FIXES_SETTINGS_DROP_ALL_DATA;
	#endif
	
	#if defined FIXES_OnGameModeInit
		return FIXES_OnGameModeInit();
	#else
		return 1;
	#endif
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit FIXES_OnGameModeInit

#if defined FIXES_OnGameModeInit
	forward FIXES_OnGameModeInit();
#endif

/* 
 * OnGameModeExit()
 * 
 * Fast way of detecting not to retain any data.
 */
#if !FIXES_Single
	public OnGameModeExit()
	{
		FIXES_gsSettings |= e_FIXES_SETTINGS_DROP_ALL_DATA;
		if (!_FIXES_gIsFilterscript && FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE)
		{
			FIXES_gsSettings |= e_FIXES_SETTINGS_ENDING,
			FIXES_DetermineOrder();
		}
		#if defined FIXES_OnGameModeExit
			return FIXES_OnGameModeExit();
		#else
			return 1;
		#endif
	}
	
	#if defined _ALS_OnGameModeExit
		#undef OnGameModeExit
	#else
		#define _ALS_OnGameModeExit
	#endif
	#define OnGameModeExit FIXES_OnGameModeExit
	
	#if defined FIXES_OnGameModeExit
		forward FIXES_OnGameModeExit();
	#endif
#endif

/* 
 * OnFilterScriptExit()
 * 
 * Fast way of detecting not to retain any data.
 */
#if !FIXES_Single
	public OnFilterScriptExit()
	{
		if (_FIXES_gIsFilterscript && FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE)
		{
			FIXES_gsSettings |= e_FIXES_SETTINGS_ENDING,
			FIXES_DetermineOrder();
		}
		#if defined FIXES_OnFilterScriptExit
			return FIXES_OnFilterScriptExit();
		#else
			return 1;
		#endif
	}
	
	#if defined _ALS_OnFilterScriptExit
		#undef OnFilterScriptExit
	#else
		#define _ALS_OnFilterScriptExit
	#endif
	#define OnFilterScriptExit FIXES_OnFilterScriptExit
	
	#if defined FIXES_OnFilterScriptExit
		forward FIXES_OnFilterScriptExit();
	#endif
#endif

/* 
 * OnPlayerCommandText(playerid, cmdtext[])
 * 
 * FIXES:
 *     OnPlayerCommandText
 */
#if FIX_OnPlayerCommandText
	public OnPlayerCommandText(playerid, cmdtext[])
	{
		// ============================
		//  START: OnPlayerCommandText 
		// ============================
		#if FIX_OnPlayerCommandText
			// If this "#if" is around the whole function, it doesn't always
			// compile properly.
			#if defined FIXES_OnPlayerCommandText
				if (cmdtext[0] <= '\1')
				{
					return FIXES_OnPlayerCommandText(playerid, FIXES_gscNULL);
				}
				else
				{
					return FIXES_OnPlayerCommandText(playerid, cmdtext);
				}
			#else
				return 0;
			#endif
		#endif
		// ============================
		//  START: OnPlayerCommandText 
		// ============================
	}
	
	#if defined _ALS_OnPlayerCommandText
		#undef OnPlayerCommandText
	#else
		#define _ALS_OnPlayerCommandText
	#endif
	#define OnPlayerCommandText FIXES_OnPlayerCommandText
	
	#if defined FIXES_OnPlayerCommandText
		forward FIXES_OnPlayerCommandText(playerid, cmdtext[]);
	#endif
#endif

/* 
 * OnPlayerConnect(playerid)
 * 
 * Almost every fix uses this callback for initialisation.  It is only
 * explicitly referenced for those fixes where this is all the code.
 * 
 * FIXES:
 *     TogglePlayerControllable
 *     SetPlayerWorldBounds
 *     GetPlayerColor
 *     SetPlayerName
 *     GetPlayerSkin
 *     IsPlayerInCheckpoint
 *     IsPlayerInRaceCheckpoint
 *     GetPlayerWeapon
 *     PutPlayerInVehicle
 *     OnPlayerEnterVehicle
 *     AllowTeleport
 *     OnDialogResponse
 *     SetSpawnInfo
 *     AllowInteriorWeapons
 *     TrainExit
 *     Kick
 */
#if FIX_SetPlayerWorldBounds || FIX_TogglePlayerControllable || FIX_SetPlayerName || FIX_GetPlayerColor || FIX_GetPlayerSkin || FIX_IsPlayerInCheckpoint || FIX_IsPlayerInRaceCheckpoint || FIX_GetPlayerWeapon || FIX_PutPlayerInVehicle || FIX_OnPlayerEnterVehicle || FIX_AllowTeleport || FIX_OnDialogResponse || FIX_GetPlayerDialog || FIX_SetSpawnInfo || FIX_AllowInteriorWeapons || FIX_TrainExit || FIX_Kick || FIX_OnPlayerEnterVehicle_2
	public OnPlayerConnect(playerid)
	{
		FIXES_PRINTF("FIXES_OnPlayerConnect: %d", playerid);
		#if FIX_SetPlayerWorldBounds || FIX_TogglePlayerControllable || FIX_PutPlayerInVehicle || FIX_OnPlayerEnterVehicle || FIX_AllowTeleport || FIX_AllowInteriorWeapons || FIX_TrainExit || FIX_OnPlayerEnterVehicle_2
			// This is only reset when the Game Mode changes or when a new
			// player connects, which is what we want.  The other items are the
			// same, but must be done only once.  This variable will tend to
			// hold data relevant only in the master script (the first
			// filterscript).
			#if FIX_Kick
				FIXES_gsPlayerBools[playerid] = e_FIXES_BOOLS_ON_PLAYER_CONNECT;
			#else
				FIXES_gsPlayerBools[playerid] = e_FIXES_BOOLS_NONE;
			#endif
		#endif
		
		#if !FIXES_Single
			if (!GetPVarInt(playerid, FIXES_pvarNotNewPlayer))
		#endif
			{
				FIXES_PRINTF("FIXES_OnPlayerConnect: First (%d)", FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE);
				// ======================
				//  START: SetPlayerName 
				// ======================
				#if FIX_SetPlayerName
					new
						name[MAX_PLAYER_NAME];
					GetPlayerName(playerid, name, MAX_PLAYER_NAME);
					if (strcmp(name, FIXES_gscTempName) == 0)
					{
						Kick(playerid);
					}
				#endif
				// ======================
				//  END:   SetPlayerName 
				// ======================
				
				// =============================
				//  START: SetPlayerWorldBounds 
				// =============================
				#if FIX_SetPlayerWorldBounds && !FIXES_Single
					FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LX] =
						FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UX] =
							FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LY] =
								FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UY] =
									0.0;
				#endif
				// =============================
				//  END:   SetPlayerWorldBounds 
				// =============================
				
				// =======================
				//  START: SetPlayerColor 
				// =======================
				#if FIX_GetPlayerColor
					SetPlayerColor(playerid, FIXES_gscPlayerColours[playerid % 100]);
				#endif
				// =======================
				//  END:   SetPlayerColor 
				// =======================
				
				// ======================
				//  START: GetPlayerSkin 
				// ======================
				#if FIX_GetPlayerSkin
					#if FIXES_Single
						FIXES_gsPlayerSkin[playerid] = 0;
					#else
						SetPVarInt(playerid, FIXES_pvarPlayerSkin, 0);
					#endif
				#endif
				// ======================
				//  END:   GetPlayerSkin 
				// ======================
				
				// =============================
				//  START: IsPlayerInCheckpoint 
				// =============================
				#if FIX_IsPlayerInCheckpoint
					DisablePlayerCheckpoint(playerid);
				#endif
				// =============================
				//  END:   IsPlayerInCheckpoint 
				// =============================
				
				// =================================
				//  START: IsPlayerInRaceCheckpoint 
				// =================================
				#if FIX_IsPlayerInRaceCheckpoint
					DisablePlayerRaceCheckpoint(playerid);
				#endif
				// =================================
				//  END:   IsPlayerInRaceCheckpoint 
				// =================================
				
				// ========================
				//  START: GetPlayerWeapon 
				// ========================
				#if FIX_GetPlayerWeapon
					#if FIXES_Single
						FIXES_gsPlayerWeapon[playerid] = -1;
					#else
						SetPVarInt(playerid, FIXES_pvarPlayerWeapon, -1);
					#endif
				#endif
				// ========================
				//  END:   GetPlayerWeapon 
				// ========================
				
				// =========================
				//  START: OnDialogResponse 
				// =========================
				#if FIX_OnDialogResponse || FIX_GetPlayerDialog
					#if FIXES_Single
						FIXES_gsDialogID[playerid] = INVALID_DIALOG_ID;
					#else
						SetPVarInt(playerid, FIXES_pvarPlayerDialog, INVALID_DIALOG_ID);
					#endif
				#endif
				// =========================
				//  END:   OnDialogResponse 
				// =========================
				
				// =====================
				//  START: SetSpawnInfo 
				// =====================
				#if FIX_SetSpawnInfo
					SetSpawnInfo(playerid, NO_TEAM, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
				#endif
				// =====================
				//  END:   SetSpawnInfo 
				// =====================
				
				#if !FIXES_Single
					// No longer their first time.
					SetPVarInt(playerid, FIXES_pvarNotNewPlayer, 1);
				#endif
			}
		// =============
		//  START: Kick 
		// =============
		#if FIX_Kick
			#if defined FIXES_OnPlayerConnect
				new
					ret = FIXES_OnPlayerConnect(playerid);
			#endif
			FIXES_gsPlayerBools[playerid] &= ~e_FIXES_BOOLS_ON_PLAYER_CONNECT;
			#if defined FIXES_OnPlayerConnect
				return ret;
			#else
				return 1;
			#endif
		#else
			#if defined FIXES_OnPlayerConnect
				return FIXES_OnPlayerConnect(playerid);
			#else
				return 1;
			#endif
		#endif
		// =============
		//  END:   Kick 
		// =============
	}
	
	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif
	#define OnPlayerConnect FIXES_OnPlayerConnect
	
	#if defined FIXES_OnPlayerConnect
		forward FIXES_OnPlayerConnect(playerid);
	#endif
#endif

/* 
 * OnPlayerDisonnect(playerid, reason)
 * 
 * FIXES:
 *     SetPlayerAttachedObject
 *     IsPlayerAttachedObjectSlotUsed
 *     Kick
 *     GetPlayerMenu
 */
#if FIX_SetPlayerAttachedObject || FIX_IsPlayerAttachedObjSlotUsed || FIX_Kick || (FIXES_SilentKick && (FIX_OnVehicleMod || FIX_OnPlayerEnterVehicle || FIX_OnPlayerEnterVehicle_2)) || FIX_GetPlayerMenu
	public OnPlayerDisconnect(playerid, reason)
	{
		#if defined FIXES_OnPlayerDisconnect
			new
				ret = FIXES_OnPlayerDisconnect(playerid, reason);
		#endif
		
		// ======================
		//  START: GetPlayerMenu 
		// ======================
		#if FIX_GetPlayerMenu
			FIXES_gsCurrentMenu[playerid] = Menu:INVALID_MENU;
		#endif
		// ======================
		//  END:   GetPlayerMenu 
		// ======================
		
		// ==========================
		//  START: FIXES_SilentKick 
		// ==========================
		#if FIXES_SilentKick && (FIX_OnVehicleMod || FIX_OnPlayerEnterVehicle || FIX_OnPlayerEnterVehicle_2)
			new
				shift = FIXES_gsPlayerIP[playerid];
			if (shift != -1)
			{
				// Unban the IP (timed out).
				new
					ip[16];
				format(ip, sizeof (ip), "unbanip %d.%d.%d.%d", shift >>> 24, (shift >>> 16) & 0xFF, (shift >>> 8) & 0xFF, shift & 0xFF),
				FIXES_gsPlayerIP[playerid] = -1;
			}
		#endif
		// ==========================
		//  END:   FIXES_SilentKick 
		// ==========================
		
		// ================================
		//  START: SetPlayerAttachedObject 
		// ================================
		#if FIX_SetPlayerAttachedObject
			#if !(FIXES_SilentKick && (FIX_OnVehicleMod || FIX_OnPlayerEnterVehicle || FIX_OnPlayerEnterVehicle_2))
				new
			#endif
					shift = playerid % _FIXES_ATTACHMENTS * MAX_PLAYER_ATTACHED_OBJECTS;
			#pragma tabsize 4
			new
				slot = playerid / _FIXES_ATTACHMENTS;
			#if !FIXES_Single
				if (!_FIXES_gIsFilterscript)
			#endif
				{
					for (new i = 0; i != MAX_PLAYER_ATTACHED_OBJECTS; ++i)
					{
						if (FIXES_gsObjectSlots[slot] & 1 << shift + i)
						{
							RemovePlayerAttachedObject(playerid, i);
						}
					}
				}
			#pragma tabsize 4
			FIXES_gsObjectSlots[slot] &= ~((1 << MAX_PLAYER_ATTACHED_OBJECTS) - 1 << shift);
		#endif
		// ================================
		//  END:   SetPlayerAttachedObject 
		// ================================
		
		// =======================================
		//  START: IsPlayerAttachedObjectSlotUsed 
		// =======================================
		#if FIX_IsPlayerAttachedObjSlotUsed && !FIX_SetPlayerAttachedObject
			FIXES_gsObjectSlots[playerid / _FIXES_ATTACHMENTS] &= ~((1 << MAX_PLAYER_ATTACHED_OBJECTS) - 1 << playerid % _FIXES_ATTACHMENTS * MAX_PLAYER_ATTACHED_OBJECTS);
		#endif
		// =======================================
		//  END:   IsPlayerAttachedObjectSlotUsed 
		// =======================================
		
		// =============
		//  START: Kick 
		// =============
		#if FIX_Kick
			if (FIXES_gsPlayerBools[playerid] & e_FIXES_BOOLS_KICKED)
			{
				// Stop the timer if it is still running.
				KillTimer(GetPVarInt(playerid, FIXES_pvarKick));
			}
		#endif
		// =============
		//  END:   Kick 
		// =============
		
		#if defined FIXES_OnPlayerDisconnect
			return ret;
		#else
			return 1;
		#endif
	}
	
	#if defined _ALS_OnPlayerDisconnect
		#undef OnPlayerDisconnect
	#else
		#define _ALS_OnPlayerDisconnect
	#endif
	#define OnPlayerDisconnect FIXES_OnPlayerDisconnect
	
	#if defined FIXES_OnPlayerDisconnect
		forward FIXES_OnPlayerDisconnect(playerid, reason);
	#endif
#endif

/* 
 * OnPlayerDeath(playerid, killerid, reason)
 * 
 * FIXES:
 *     OnPlayerDeath
 */
#if FIX_OnPlayerDeath
	public OnPlayerDeath(playerid, killerid, reason)
	{
		#if !FIXES_Single
			if (FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE)
		#endif
			{
				// ======================
				//  START: OnPlayerDeath 
				// ======================
				#if FIX_OnPlayerDeath
					static
						sAnimlib[32],
						sAnimname[32];
					GetAnimationName(FIXES_gsLastAnimation[playerid], sAnimlib, sizeof (sAnimlib), sAnimname, sizeof (sAnimname));
					if (strcmp(sAnimlib, "PED", true))
					{
						ClearAnimations(playerid);
					}
				#endif
				// ======================
				//  END:   OnPlayerDeath 
				// ======================
			}
		#if defined FIXES_OnPlayerDeath
			return FIXES_OnPlayerDeath(playerid, killerid, reason);
		#else
			return 1;
		#endif
	}
	
	#if defined _ALS_OnPlayerDeath
		#undef OnPlayerDeath
	#else
		#define _ALS_OnPlayerDeath
	#endif
	#define OnPlayerDeath FIXES_OnPlayerDeath
	
	#if defined FIXES_OnPlayerDeath
		forward FIXES_OnPlayerDeath(playerid, killerid, reason);
	#endif
#endif

/* 
 * FIXES_SpawnPlayer(playerid)
 * 
 * FIXES:
 *     SpawnPlayer
 */
#if FIX_SpawnPlayer
	stock FIXES_SpawnPlayer(playerid)
	{
		// Valid "playerid" check inside "GetPlayerVehicleID".
		new
			vid = GetPlayerVehicleID(playerid);
		if (vid)
		{
			new
				Float:x,
				Float:y,
				Float:z;
			// Remove them without the animation.
			GetVehiclePos(vid, x, y, z),
			SetPlayerPos(playerid, x, y, z);
		}
		return SpawnPlayer(playerid);
	}
	
	#if defined _ALS_SpawnPlayer
		#undef SpawnPlayer
	#else
		
		native BAD_SpawnPlayer(playerid) = SpawnPlayer;
		
		#define _ALS_SpawnPlayer
	#endif
	#define SpawnPlayer FIXES_SpawnPlayer
#endif

/* 
 * FIXES_SetPlayerName(playerid, name[])
 * 
 * FIXES:
 *     SetPlayerName
 */
#if FIX_SetPlayerName
	stock FIXES_SetPlayerName(playerid, name[])
	{
		if (!strcmp(name, FIXES_gscTempName, true))
		{
			return 0;
		}
		static
			sOldName[MAX_PLAYER_NAME];
		GetPlayerName(playerid, sOldName, sizeof (sOldName));
		if (strcmp(name, sOldName, true))
		{
			return SetPlayerName(playerid, name);
		}
		SetPlayerName(playerid, FIXES_gscTempName);
		new
			retval = SetPlayerName(playerid, name);
		if (retval != 1)
		{
			SetPlayerName(playerid, sOldName);
		}
		return retval;
	}
	#if defined _ALS_SetPlayerName
		#undef SetPlayerName
	#else
		
		native BAD_SetPlayerName(playerid, const name[]) = SetPlayerName;
		
		#define _ALS_SetPlayerName
	#endif
	#define SetPlayerName FIXES_SetPlayerName
#endif

/* 
 * OnPlayerSpawn(playerid)
 * 
 * FIXES:
 *     GetPlayerSkin
 *     TogglePlayerControllable
 */
#if FIX_GetPlayerSkin || FIX_TogglePlayerControllable
	public OnPlayerSpawn(playerid)
	{
		// ======================
		//  START: GetPlayerSkin 
		// ======================
		#if FIX_GetPlayerSkin
			#if FIXES_Single
				FIXES_gsPlayerSkin[playerid] = GetPlayerSkin(playerid);
			#else
				SetPVarInt(playerid, FIXES_pvarPlayerSkin, GetPlayerSkin(playerid));
			#endif
		#endif
		// ======================
		//  END:   GetPlayerSkin 
		// ======================
		
		// =================================
		//  START: TogglePlayerControllable 
		// =================================
		#if FIX_TogglePlayerControllable
			FIXES_gsPlayerBools[playerid] &= ~e_FIXES_BOOLS_UNCONTROLLABLE;
		#endif
		// =================================
		//  END:   TogglePlayerControllable 
		// =================================
		
		#if defined FIXES_OnPlayerSpawn
			return FIXES_OnPlayerSpawn(playerid);
		#else
			return 1;
		#endif
	}
	
	#if defined _ALS_OnPlayerSpawn
		#undef OnPlayerSpawn
	#else
		#define _ALS_OnPlayerSpawn
	#endif
	#define OnPlayerSpawn FIXES_OnPlayerSpawn
	
	#if defined FIXES_OnPlayerSpawn
		forward FIXES_OnPlayerSpawn(playerid);
	#endif
#endif

/* 
 * OnVehicleMod(playerid, vehicleid, componentid)
 * 
 * FIXES:
 *     OnVehicleMod
 */
#if FIX_OnVehicleMod
	public OnVehicleMod(playerid, vehicleid, componentid)
	{
		#if !FIXES_Single
			if (!(FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE))
			{
				#if defined FIXES_OnVehicleMod
					return FIXES_OnVehicleMod(playerid, vehicleid, componentid);
				#else
					return 1;
				#endif
			}
		#endif
		
		// =====================
		//  START: OnVehicleMod 
		// =====================
		new
			modelid = GetVehicleModel(vehicleid);
		if (400 <= modelid <= 611)
		{
			switch (componentid)
			{
				case 1000 .. 1191:
				{
					if (FIXES_gscVehicleMods[modelid - 400][(componentid - 1000) >>> 5] & (1 << ((componentid - 1000) & 0b00011111)))
					{
						#if defined FIXES_OnVehicleMod
							return FIXES_OnVehicleMod(playerid, vehicleid, componentid);
						#else
							return 1;
						#endif
					}
				}
				case 1192, 1193:
				{
					if (modelid == 576)
					{
						// This save a whole cell off EVERY other vehicle!  This
						// is the ONLY vehicle with any mods over "6 * 32 + 999"
						// (1191), the highest value you can fit in 6 cells of a
						// bit array (minus 1000).
						#if defined FIXES_OnVehicleMod
							return FIXES_OnVehicleMod(playerid, vehicleid, componentid);
						#else
							return 1;
						#endif
					}
				}
			}
		}
		// Desync the player entirely.
		FIXES_BlockUpdate(playerid, true);
		return 0;
		// =====================
		//  END:   OnVehicleMod 
		// =====================
	}
	
	#if defined _ALS_OnVehicleMod
		#undef OnVehicleMod
	#else
		#define _ALS_OnVehicleMod
	#endif
	#define OnVehicleMod FIXES_OnVehicleMod
	
	#if defined FIXES_OnVehicleMod
		forward FIXES_OnVehicleMod(playerid, vehicleid, componentid);
	#endif
#endif

/* 
 * FIXES_SetPlayerSkin(playerid, skinid)
 * 
 * FIXES:
 *     GetPlayerSkin
 *     SetPlayerSkin
 */
#if FIX_GetPlayerSkin || FIX_SetPlayerSkin
	stock FIXES_SetPlayerSkin(playerid, skinid)
	{
		// ======================
		//  START: SetPlayerSkin 
		// ======================
		#if FIX_SetPlayerSkin
			new
				vehicleid = GetPlayerVehicleID(playerid);
			if (vehicleid)
			{
				new
					seat = GetPlayerVehicleSeat(playerid);
				ClearAnimations(playerid);
				new
					ret = SetPlayerSkin(playerid, skinid);
				PutPlayerInVehicle(playerid, vehicleid, seat);
				
				// ======================
				//  START: GetPlayerSkin 
				// ======================
				#if FIX_GetPlayerSkin
					#if FIXES_Single
						FIXES_gsPlayerSkin[playerid] = skinid;
					#else
						SetPVarInt(playerid, FIXES_pvarPlayerSkin, skinid);
					#endif
				#endif
				// ======================
				//  END:   GetPlayerSkin 
				// ======================
				
				return ret;
			}
			
			// ======================
			//  START: GetPlayerSkin 
			// ======================
			#if FIX_GetPlayerSkin
				else
			#endif
			// ======================
			//  END:   GetPlayerSkin 
			// ======================
		#endif
		// ======================
		//  END:   SetPlayerSkin 
		// ======================
		
		// ======================
		//  START: GetPlayerSkin 
		// ======================
		#if FIX_GetPlayerSkin
			// Watch fot the "else" above if this code ever changes.
			#if FIXES_Single
				FIXES_gsPlayerSkin[playerid] = skinid;
			#else
				SetPVarInt(playerid, FIXES_pvarPlayerSkin, skinid);
			#endif
		#endif
		// ======================
		//  END:   GetPlayerSkin 
		// ======================
		
		return SetPlayerSkin(playerid, skinid);
	}
	
	#if defined _ALS_SetPlayerSkin
		#undef SetPlayerSkin
	#else
		
		native BAD_SetPlayerSkin(playerid, skinid) = SetPlayerSkin;
		
		#define _ALS_SetPlayerSkin
	#endif
	#define SetPlayerSkin FIXES_SetPlayerSkin
#endif

/* 
 * FIXES_GetPlayerSkin(playerid, skinid)
 * 
 * FIXES:
 *     GetPlayerSkin
 */
#if FIX_GetPlayerSkin
	stock FIXES_GetPlayerSkin(playerid)
	{
		#if FIXES_Single
			return FIXES_gsPlayerSkin[playerid];
		#else
			return GetPVarInt(playerid, FIXES_pvarPlayerSkin);
		#endif
	}
	
	#if defined _ALS_GetPlayerSkin
		#undef GetPlayerSkin
	#else
		
		native BAD_GetPlayerSkin(playerid) = GetPlayerSkin;
		
		#define _ALS_GetPlayerSkin
	#endif
	#define GetPlayerSkin FIXES_GetPlayerSkin
#endif

/* 
 * FIXES_GetWeaponName(weaponid, weapon[], len)
 * 
 * FIXES:
 *     GetWeaponName
 */
#if FIX_GetWeaponName
	stock FIXES_GetWeaponName(weaponid, weapon[], len)
	{
		switch (weaponid)
		{
			case 18:
			{
				return
					weapon[0] = 0,
					strcat(weapon, "Molotov Cocktail", len),
					1;
			}
			case 44:
			{
				return
					weapon[0] = 0,
					strcat(weapon, "Thermal Goggles", len),
					1;
			}
			case 45:
			{
				return
					weapon[0] = 0,
					strcat(weapon, "Night Vision Goggles", len),
					1;
			}
			default:
			{
				return GetWeaponName(weaponid, weapon, len);
			}
		}
		return 0;
	}
	
	#if defined _ALS_GetWeaponName
		#undef GetWeaponName
	#else
		
		native BAD_GetWeaponName(weaponid, weapon[], len) = GetWeaponName;
		
		#define _ALS_GetWeaponName
	#endif
	#define GetWeaponName FIXES_GetWeaponName
#endif

/* 
 * OnPlayerUpdate(playerid)
 * 
 * FIXES:
 *     SetPlayerWorldBounds
 *     TogglePlayerControllable
 *     AllowInteriorWeapons
 *     OnPlayerDeath
 *     Kick
 *     OnVehicleMod
 *     OnPlayerEnterVehicle
 *     OnPlayerEnterVehicle_2
 */
#if FIX_SetPlayerWorldBounds || FIX_TogglePlayerControllable || FIX_AllowInteriorWeapons || FIX_OnPlayerEnterVehicle || FIX_OnPlayerEnterVehicle_2 || FIX_OnPlayerDeath || FIX_Kick || FIX_OnVehicleMod
	public OnPlayerUpdate(playerid)
	{
		// =============================
		//  BEGIN: OnPlayerEnterVehicle 
		// =============================
		#if FIX_OnPlayerEnterVehicle || FIX_Kick || FIX_OnVehicleMod || FIX_OnPlayerEnterVehicle_2
			if (FIXES_gsPlayerBools[playerid] & e_FIXES_BOOLS_BLOCK)
			{
				return 0;
			}
		#endif
		// =============================
		//  END:   OnPlayerEnterVehicle 
		// =============================
		
		#if !FIXES_Single
			if (!(FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE))
			{
				#if defined FIXES_OnPlayerUpdate
					return FIXES_OnPlayerUpdate(playerid);
				#else
					return 1;
				#endif
			}
		#endif
		
		#if FIX_OnPlayerEnterVehicle || FIX_AllowInteriorWeapons || FIX_SetPlayerWorldBounds || FIX_TogglePlayerControllable
			new
				e_FIXES_BOOLS:pbools = FIXES_gsPlayerBools[playerid];
		#endif
		
		// =============================
		//  START: AllowInteriorWeapons 
		// =============================
		#if FIX_AllowInteriorWeapons
			//if (FIXES_gsSettings & e_FIXES_SETTINGS_INTERIOR && GetPlayerInterior(playerid) && GetPlayerWeapon(playerid))
			if (pbools & e_FIXES_BOOLS_INTERIOR)
			{
				// DONE: May need integration with "FIX_GetPlayerWeapon".
				SetPlayerArmedWeapon(playerid, 0);
			}
		#endif
		// ============================
		//  END: AllowInteriorWeapons 
		// ============================
		
		#if FIX_SetPlayerWorldBounds || FIX_TogglePlayerControllable
			new
				ud,
				lr,
				keys;
			GetPlayerKeys(playerid, keys, ud, lr);
		#endif
		
		#if FIX_SetPlayerWorldBounds && !FIX_TogglePlayerControllable
			#pragma unused ud, lr
		#endif
		
		// =============================
		//  START: SetPlayerWorldBounds 
		// =============================
		#if FIX_SetPlayerWorldBounds
			if (pbools & e_FIXES_BOOLS_WORLDBOUNDS && keys & _FIXES_KEY_AIM)
			{
				new
					Float:x,
					Float:y,
					Float:z;
				GetPlayerPos(playerid, x, y, z);
				if (FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LX] < x < FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UX] && FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LY] < y < FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UY])
				{
					FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PX] = x,
					FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PY] = y,
					FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PZ] = z;
				}
				else
				{
					SetPlayerPos(playerid, FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PX], FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PY], FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PZ]);
				}
			}
		#endif
		// =============================
		//  END:   SetPlayerWorldBounds 
		// =============================
		
		// ======================
		//  START: OnPlayerDeath 
		// ======================
		#if FIX_OnPlayerDeath
			FIXES_gsLastAnimation[playerid] = GetPlayerAnimationIndex(playerid);
		#endif
		// ======================
		//  END:   OnPlayerDeath 
		// ======================
		
		// =================================
		//  START: TogglePlayerControllable 
		// =================================
		#if FIX_TogglePlayerControllable
			// MUST come last.
			if (pbools & e_FIXES_BOOLS_UNCONTROLLABLE)
			{
				// Keys based sync blocking, modified based on a post by Slice:
				// http://forum.sa-mp.com/showpost.php?p=876854&postcount=1
				// Use "playerid" here as it's a variable that already exists,
				// but note that after this point, you CANNOT use "playerid" as
				// it has been "clobbered" (and yes, that's the technical term).
				// This is just to avoid "statement has no effect" warnings.
				// ALWAYS return 0 in this case, regardless of what other
				// callbacks return.
				#if defined FIXES_OnPlayerUpdate
					playerid = FIXES_OnPlayerUpdate(playerid);
				#endif
				if (keys || ud || lr)
				{
					return 0;
				}
				else
				{
					#if defined FIXES_OnPlayerUpdate
						return playerid;
					#else
						return 1;
					#endif
				}
			}
		#endif
		// =================================
		//  END:   TogglePlayerControllable 
		// =================================
		
		#if defined FIXES_OnPlayerUpdate
			return FIXES_OnPlayerUpdate(playerid);
		#else
			return 1;
		#endif
	}
	
	#if defined _ALS_OnPlayerUpdate
		#undef OnPlayerUpdate
	#else
		#define _ALS_OnPlayerUpdate
	#endif
	#define OnPlayerUpdate FIXES_OnPlayerUpdate
	
	#if defined FIXES_OnPlayerUpdate
		forward FIXES_OnPlayerUpdate(playerid);
	#endif
#endif

/* 
 * FIXES_SetPlayerWorldBounds(playerid, Float:x_max, Float:x_min, Float:y_max, Float:y_min)
 * 
 * TODO: Modify this to remove aim animations when they get to the boundaries.
 * 
 * FIXES:
 *     SetPlayerWorldBounds
 */
#if FIX_SetPlayerWorldBounds
	#if FIXES_Single
		stock FIXES_SetPlayerWorldBounds(playerid, Float:x_max, Float:x_min, Float:y_max, Float:y_min)
		{
			if (0 <= playerid < MAX_PLAYERS)
			{
				FIXES_PRINTF("Call SetPlayerWorldBounds");
				if (x_max == x_min || y_max == y_min)
				{
					// Impossibly small area, disable checks entirely.
					return
						FIXES_gsPlayerBools[playerid] &= ~e_FIXES_BOOLS_WORLDBOUNDS,
						SetPlayerWorldBounds(playerid, _FIXES_INFINITY, _FIXES_N_INFINITY, _FIXES_INFINITY, _FIXES_N_INFINITY);
				}
				// This code could do with a way to mostly remove the checks.  Maybe
				// when setting everything to FIXES_INFINITY (with default
				// parameters).
				FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_WORLDBOUNDS;
				new
					Float:tmp;
				if (x_max < x_min)
				{
					tmp = x_min,
					x_min = x_max,
					x_max = tmp;
				}
				if (y_max < y_min)
				{
					tmp = y_min,
					y_min = y_max,
					y_max = tmp;
				}
				// Give a little leway so this fix isn't noticed if you're not
				// trying to break through the world bounds.  Leway removed in
				// favour of keys.
				return
					FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LX] = x_min,
					FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UX] = x_max,
					
					FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LY] = y_min,
					FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UY] = y_max,
					
					GetPlayerPos(playerid, tmp, tmp, tmp),
					FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PX] = (x_max - x_min) / 2 + x_min,
					FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PY] = (y_max - y_min) / 2 + y_min,
					FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PZ] = tmp,
					
					SetPlayerWorldBounds(playerid, x_max, x_min, y_max, y_min);
			}
			return 0;
		}
	#else
		forward _FIXES_SetPlayerWorldBounds(playerid, Float:x_max, Float:x_min, Float:y_max, Float:y_min);
		
		stock FIXES_SetPlayerWorldBounds(playerid, Float:x_max, Float:x_min, Float:y_max, Float:y_min)
		{
			if (0 <= playerid < MAX_PLAYERS)
			{
				FIXES_PRINTF("Call SetPlayerWorldBounds");
				return
					CallRemoteFunction(FIXES_gscSetPlayerWorldBounds, FIXES_gscSpec@iffff, playerid, x_max, x_min, y_max, y_min),
					getproperty(5, FIXES_gscReturnProperty);
			}
			return 0;
		}
		
		public _FIXES_SetPlayerWorldBounds(playerid, Float:x_max, Float:x_min, Float:y_max, Float:y_min)
		{
			FIXES_PRINTF("_FIXES_SetPlayerWorldBounds: %d %.2f %.2f %.2f %.2f", playerid, x_max, x_min, y_max, y_min);
			if (FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE)
			{
				FIXES_PRINTF("SetPlayerWorldBounds");
				//if (x_max == _FIXES_INFINITY && x_min == _FIXES_INFINITY && y_max == _FIXES_INFINITY && y_min == _FIXES_INFINITY)
				if (x_max == x_min || y_max == y_min)
				{
					// Impossibly small area, disable checks entirely.
					return
						FIXES_gsPlayerBools[playerid] &= ~e_FIXES_BOOLS_WORLDBOUNDS,
						FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LX] =
							FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UX] =
								FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LY] =
									FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UY] =
										0.0,
						setproperty(5, FIXES_gscReturnProperty, SetPlayerWorldBounds(playerid, _FIXES_INFINITY, _FIXES_N_INFINITY, _FIXES_INFINITY, _FIXES_N_INFINITY)),
						-1;
				}
				// This code could do with a way to mostly remove the checks.  Maybe
				// when setting everything to FIXES_INFINITY (with default
				// parameters).
				FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_WORLDBOUNDS;
				new
					Float:tmp;
				if (x_max < x_min)
				{
					tmp = x_min,
					x_min = x_max,
					x_max = tmp;
				}
				if (y_max < y_min)
				{
					tmp = y_min,
					y_min = y_max,
					y_max = tmp;
				}
				// Give a little leway so this fix isn't noticed if you're not
				// trying to break through the world bounds.  Leway removed in
				// favour of keys.
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LX] = x_min,
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UX] = x_max,
				
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LY] = y_min,
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UY] = y_max,
				
				GetPlayerPos(playerid, tmp, tmp, tmp),
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PX] = (x_max - x_min) / 2 + x_min,
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PY] = (y_max - y_min) / 2 + y_min,
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PZ] = tmp,
				
				setproperty(5, FIXES_gscReturnProperty, SetPlayerWorldBounds(playerid, x_max, x_min, y_max, y_min));
			}
			return 0;
		}
	#endif
	
	#if defined _ALS_SetPlayerWorldBounds
		#undef SetPlayerWorldBounds
	#else
		
		native BAD_SetPlayerWorldBounds(playerid, Float:x_max, Float:x_min, Float:y_max, Float:y_min) = SetPlayerWorldBounds;
		
		#define _ALS_SetPlayerWorldBounds
	#endif
	#define SetPlayerWorldBounds FIXES_SetPlayerWorldBounds
#endif

/* 
 * FIXES_TogglePlayerControllable(playerid, toggle)
 * 
 * FIXES:
 *     TogglePlayerControllable
 */
#if FIX_TogglePlayerControllable
	#if FIXES_Single
		stock FIXES_TogglePlayerControllable(playerid, toggle)
		{
			if (TogglePlayerControllable(playerid, toggle))
			{
				if (toggle)
				{
					FIXES_gsPlayerBools[playerid] &= ~e_FIXES_BOOLS_UNCONTROLLABLE;
				}
				else
				{
					FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_UNCONTROLLABLE;
				}
				return 1;
			}
			return 0;
		}
	#else
		forward _FIXES_TogglePlayerControllable(playerid, toggle);
		
		stock FIXES_TogglePlayerControllable(playerid, toggle)
		{
			if (0 <= playerid < MAX_PLAYERS)
			{
				return
					CallRemoteFunction(FIXES_gscTogglePlayerControl, FIXES_gscSpec@ii, playerid, toggle),
					getproperty(5, FIXES_gscReturnProperty);
			}
			return 0;
		}
		
		public _FIXES_TogglePlayerControllable(playerid, toggle)
		{
			if (FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE)
			{
				if (toggle)
				{
					FIXES_gsPlayerBools[playerid] &= ~e_FIXES_BOOLS_UNCONTROLLABLE;
				}
				else
				{
					FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_UNCONTROLLABLE;
				}
				setproperty(5, FIXES_gscReturnProperty, TogglePlayerControllable(playerid, toggle));
			}
		}
	#endif
	
	#if defined _ALS_TogglePlayerControllable
		#undef TogglePlayerControllable
	#else
		
		native BAD_TogglePlayerControllable(playerid, toggle) = TogglePlayerControllable;
		
		#define _ALS_TogglePlayerControllable
	#endif
	#define TogglePlayerControllable FIXES_TogglePlayerControllable
#endif

/* 
 * OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
 * 
 * FIXES:
 *     AllowInteriorWeapons
 */

#if FIX_AllowInteriorWeapons
	public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
	{
		// =============================
		//  BEGIN: AllowInteriorWeapons 
		// =============================
		#if FIX_AllowInteriorWeapons
			if (newinteriorid)
			{
				if (FIXES_gsSettings & e_FIXES_SETTINGS_INTERIOR)
				{
					// This only needs doing here if "GetPlayerWeapon" is set.
					// If it isn't, even though "AllowInteriorWeapons" can use
					// this code on its own, it doesn't as "OnPlayerUpdate"
					// takes care of it all.
					// TODO: Rewrite this code to use a single bit to indicate
					// if a player can have a weapon or not, and just use the in
					// the "OnPlayerUpdate" callback, instead of several checks.
					// DONE!
					FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_INTERIOR;
					#if !FIXES_Single
						if (FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE)
					#endif
						{
							SetPlayerArmedWeapon(playerid, 0);
							#if FIX_GetPlayerWeapon
								if (IsPlayerInAnyVehicle(playerid))
								{
									#if FIXES_Single
										FIXES_gsPlayerWeapon[playerid] = 0;
									#else
										SetPVarInt(playerid, FIXES_pvarPlayerWeapon, 0);
									#endif
								}
							#endif
						}
				}
			}
			else
			{
				FIXES_gsPlayerBools[playerid] &= ~e_FIXES_BOOLS_INTERIOR;
			}
		#endif
		// ===========================
		//  END: AllowInteriorWeapons 
		// ===========================
		#if defined FIXES_OnPlayerInteriorChange
			return FIXES_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
		#else
			return 1;
		#endif
	}
	
	#if defined _ALS_OnPlayerInteriorChange
		#undef OnPlayerInteriorChange
	#else
		#define _ALS_OnPlayerInteriorChange
	#endif
	#define OnPlayerInteriorChange FIXES_OnPlayerInteriorChange
	
	#if defined FIXES_OnPlayerInteriorChange
		forward FIXES_OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
	#endif
#endif

/* 
 * OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
 * 
 * FIXES:
 *     OnPlayerEnterVehicle_2
 */
#if FIX_OnPlayerEnterVehicle_2
	public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
	{
		// ===============================
		//  BEGIN: OnPlayerEnterVehicle_2 
		// ===============================
		#if FIX_OnPlayerEnterVehicle_2
			if (0 < vehicleid < MAX_VEHICLES)
			{
				#if defined FIXES_OnPlayerEnterVehicle
					return FIXES_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
				#else
					return 1;
				#endif
			}
			FIXES_BlockUpdate(playerid, true);
			return 0;
		#endif
		// =============================
		//  END: OnPlayerEnterVehicle_2 
		// =============================
	}
	
	#if defined _ALS_OnPlayerEnterVehicle
		#undef OnPlayerEnterVehicle
	#else
		#define _ALS_OnPlayerEnterVehicle
	#endif
	#define OnPlayerEnterVehicle FIXES_OnPlayerEnterVehicle
	
	#if defined FIXES_OnPlayerEnterVehicle
		forward FIXES_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	#endif
#endif

/* 
 * OnPlayerExitVehicle(playerid, vehicleid)
 * 
 * FIXES:
 *     OnPlayerEnterVehicle_2
 */
#if FIX_OnPlayerEnterVehicle_2
	public OnPlayerExitVehicle(playerid, vehicleid)
	{
		// ===============================
		//  BEGIN: OnPlayerEnterVehicle_2 
		// ===============================
		#if FIX_OnPlayerEnterVehicle_2
			if (0 < vehicleid < MAX_VEHICLES)
			{
				#if defined FIXES_OnPlayerExitVehicle
					return FIXES_OnPlayerExitVehicle(playerid, vehicleid);
				#else
					return 1;
				#endif
			}
			FIXES_BlockUpdate(playerid, true);
			return 0;
		#endif
		// =============================
		//  END: OnPlayerEnterVehicle_2 
		// =============================
	}
	
	#if defined _ALS_OnPlayerExitVehicle
		#undef OnPlayerExitVehicle
	#else
		#define _ALS_OnPlayerExitVehicle
	#endif
	#define OnPlayerExitVehicle FIXES_OnPlayerExitVehicle
	
	#if defined FIXES_OnPlayerExitVehicle
		forward FIXES_OnPlayerExitVehicle(playerid, vehicleid);
	#endif
#endif

/*
 * FIXES_BlockUpdate(playerid, bool:block)
 *
 * Block a player from using OnPlayerUpdate at all.
 */
#if FIX_OnPlayerEnterVehicle || FIX_Kick || FIX_OnVehicleMod
	static stock FIXES_BlockUpdate(playerid, bool:block, kick = 6)
	{
		if (kick)
		{
			#if FIXES_SilentKick
				new
					ip[22];
				GetPlayerIp(playerid, ip, sizeof (ip)),
				format(ip, sizeof (ip), "banip %s", ip),
				SendRconCommand(ip),
				FIXES_gsPlayerIP[playerid] = strval(ip[kick]) << 24,
				kick = strfind(ip, FIXES_gscDot, false, kick) + 1,
				FIXES_gsPlayerIP[playerid] |= strval(ip[kick]) << 16,
				kick = strfind(ip, FIXES_gscDot, false, kick) + 1,
				FIXES_gsPlayerIP[playerid] |= strval(ip[kick]) << 8,
				kick = strfind(ip, FIXES_gscDot, false, kick) + 1,
				FIXES_gsPlayerIP[playerid] |= strval(ip[kick]);
			#else
				Kick(playerid);
			#endif
		}
		if (block)
		{
			FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_BLOCK;
			return 0;
		}
		else
		{
			FIXES_gsPlayerBools[playerid] &= ~e_FIXES_BOOLS_BLOCK;
			return 1;
		}
	}
#endif

/* 
 * OnPlayerSelectedMenuRow(playerid, row)
 * 
 * FIXES:
 *     GetPlayerMenu
 */
#if FIX_GetPlayerMenu
	public OnPlayerSelectedMenuRow(playerid, row)
	{
		// ======================
		//  BEGIN: GetPlayerMenu 
		// ======================
		#if FIXES_Single
			FIXES_gsSettings &= ~e_FIXES_SETTINGS_MENU_SET;
			#if defined FIXES_OnPlayerSelectedMenuRow
				new
					ret = FIXES_OnPlayerSelectedMenuRow(playerid, row);
			#endif
			if (!(FIXES_gsSettings & e_FIXES_SETTINGS_MENU_SET))
			{
				FIXES_gsCurrentMenu[playerid] = Menu:INVALID_MENU;
			}
			#if defined FIXES_OnPlayerSelectedMenuRow
				return ret;
			#else
				return 1;
			#endif
		#else
			if (FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE)
			{
				CallRemoteFunction(FIXES_gscClearPlayerMenu, FIXES_gscSpec@i, playerid);
				setproperty(5, FIXES_gscMenuProperty, _:FIXES_gsCurrentMenu[playerid]);
				#if defined FIXES_OnPlayerSelectedMenuRow
					new
						ret = FIXES_OnPlayerSelectedMenuRow(playerid, row);
				#endif
				if (!(FIXES_gsSettings & e_FIXES_SETTINGS_MENU_SET))
				{
					FIXES_gsCurrentMenu[playerid] = Menu:INVALID_MENU;
				}
				#if defined FIXES_OnPlayerSelectedMenuRow
					return ret;
				#else
					return 1;
				#endif
			}
			else
			{
				new
					setyet = _:(FIXES_gsSettings & e_FIXES_SETTINGS_MENU_SET),
					Menu:cur = FIXES_gsCurrentMenu[playerid];
				FIXES_gsCurrentMenu[playerid] = Menu:getproperty(5, FIXES_gscMenuProperty);
				FIXES_gsSettings &= ~e_FIXES_SETTINGS_MENU_SET;
				#if defined FIXES_OnPlayerSelectedMenuRow
					new
						ret = FIXES_OnPlayerSelectedMenuRow(playerid, row);
				#endif
				if (!(FIXES_gsSettings & e_FIXES_SETTINGS_MENU_SET))
				{
					if (setyet)
					{
						FIXES_gsCurrentMenu[playerid] = cur;
					}
					else
					{
						FIXES_gsCurrentMenu[playerid] = Menu:INVALID_MENU;
					}
				}
				#if defined FIXES_OnPlayerSelectedMenuRow
					return ret;
				#else
					return 1;
				#endif
			}
		#endif
		// ======================
		//  END:   GetPlayerMenu 
		// ======================
	}
	
	#if defined _ALS_OnPlayerSelectedMenuRow
		#undef OnPlayerSelectedMenuRow
	#else
		#define _ALS_OnPlayerSelectedMenuRow
	#endif
	#define OnPlayerSelectedMenuRow FIXES_OnPlayerSelectedMenuRow
	
	#if defined FIXES_OnPlayerSelectedMenuRow
		forward FIXES_OnPlayerSelectedMenuRow(playerid, row);
	#endif
#endif

/* 
 * OnPlayerExitedMenu(playerid)
 * 
 * FIXES:
 *     GetPlayerMenu
 */
#if FIX_GetPlayerMenu
	public OnPlayerExitedMenu(playerid)
	{
		// ======================
		//  BEGIN: GetPlayerMenu 
		// ======================
		#if FIXES_Single
			#if defined FIXES_OnPlayerExitedMenu
				FIXES_gsSettings &= ~e_FIXES_SETTINGS_MENU_SET;
				new
					ret = FIXES_OnPlayerExitedMenu(playerid);
				if (!(FIXES_gsSettings & e_FIXES_SETTINGS_MENU_SET))
				{
			#endif
					FIXES_gsCurrentMenu[playerid] = Menu:INVALID_MENU;
			#if defined FIXES_OnPlayerExitedMenu
				}
				return ret;
			#else
				return 1;
			#endif
		#else
			#if defined FIXES_OnPlayerExitedMenu
				if (FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE)
				{
					CallRemoteFunction(FIXES_gscClearPlayerMenu, FIXES_gscSpec@i, playerid);
					setproperty(5, FIXES_gscMenuProperty, _:FIXES_gsCurrentMenu[playerid]);
					new
						ret = FIXES_OnPlayerExitedMenu(playerid);
					if (!(FIXES_gsSettings & e_FIXES_SETTINGS_MENU_SET))
					{
						FIXES_gsCurrentMenu[playerid] = Menu:INVALID_MENU;
					}
					return ret;
				}
				else
				{
					new
						setyet = _:(FIXES_gsSettings & e_FIXES_SETTINGS_MENU_SET),
						Menu:cur = FIXES_gsCurrentMenu[playerid];
					FIXES_gsCurrentMenu[playerid] = Menu:getproperty(5, FIXES_gscMenuProperty);
					FIXES_gsSettings &= ~e_FIXES_SETTINGS_MENU_SET;
					new
						ret = FIXES_OnPlayerExitedMenu(playerid);
					if (!(FIXES_gsSettings & e_FIXES_SETTINGS_MENU_SET))
					{
						if (setyet)
						{
							FIXES_gsCurrentMenu[playerid] = cur;
						}
						else
						{
			#endif
							FIXES_gsCurrentMenu[playerid] = Menu:INVALID_MENU;
			#if defined FIXES_OnPlayerExitedMenu
						}
					}
					return ret;
				}
			#else
				return 1;
			#endif
		#endif
		// ======================
		//  END:   GetPlayerMenu 
		// ======================
	}
	
	#if defined _ALS_OnPlayerExitedMenu
		#undef OnPlayerExitedMenu
	#else
		#define _ALS_OnPlayerExitedMenu
	#endif
	#define OnPlayerExitedMenu FIXES_OnPlayerExitedMenu
	
	#if defined FIXES_OnPlayerExitedMenu
		forward FIXES_OnPlayerExitedMenu(playerid);
	#endif
#endif

/* 
 * FIXES_IS_VALID_MENU(Menu:menuid)
 * 
 * FIXES:
 *     Menus
 */
#if _FIX_Menus
	#define FIXES_IS_VALID_MENU(%0) ((0 <= _:(%0) < MAX_MENUS) && (FIXES_gsValidMenus[_:(%0) >>> 5] & (1 << (_:(%0) & 0x1F))))
#endif

/* 
 * Menu:FIXES_CreateMenu(const title[], columns, Float:x, Float:y, Float:col1width, Float:col2width = 0.0)
 * 
 * FIXES:
 *     Menus
 */
#if _FIX_Menus
	#if !FIXES_Single
		forward _FIXES_CreateMenu(ret);
		
		public _FIXES_CreateMenu(ret)
		{
			FIXES_gsValidMenus[ret >>> 5] |= 1 << (ret & 0x1F);
		}
	#endif
	
	stock Menu:FIXES_CreateMenu(const title[], columns, Float:x, Float:y, Float:col1width, Float:col2width = 0.0)
	{
		new
			Menu:ret = CreateMenu(title, columns, x, y, col1width, col2width);
		if (Menu:0 <= ret < Menu:MAX_MENUS)
		{
			#if FIXES_Single
				FIXES_gsValidMenus[_:ret >>> 5] |= 1 << (_:ret & 0x1F);
			#else
				CallRemoteFunction("_FIXES_CreateMenu", FIXES_gscSpec@i, _:ret);
			#endif
		}
		return ret;
	}
	
	#if defined _ALS_CreateMenu
		#undef CreateMenu
	#else
		
		native Menu:BAD_CreateMenu(const title[], columns, Float:x, Float:y, Float:col1width, Float:col2width = 0.0) = CreateMenu;
		
		#define _ALS_CreateMenu
	#endif
	#define CreateMenu FIXES_CreateMenu
#endif

/* 
 * _FIXES_SetPlayerMenu(playerid, Menu:menuid)
 * 
 * FIXES:
 *     GetPlayerMenu
 */
#if FIX_GetPlayerMenu && !FIXES_Single
	forward _FIXES_SetPlayerMenu(playerid, Menu:menuid);
	
	public _FIXES_SetPlayerMenu(playerid, Menu:menuid)
	{
		FIXES_gsSettings |= e_FIXES_SETTINGS_MENU_SET;
		FIXES_gsCurrentMenu[playerid] = menuid;
	}
#endif

/* 
 * _FIXES_ClearPlayerMenu(playerid)
 * 
 * FIXES:
 *     GetPlayerMenu
 */
#if FIX_GetPlayerMenu && !FIXES_Single
	forward _FIXES_ClearPlayerMenu(playerid);
	
	public _FIXES_ClearPlayerMenu(playerid)
	{
		FIXES_gsSettings &= ~e_FIXES_SETTINGS_MENU_SET;
		FIXES_gsCurrentMenu[playerid] = Menu:INVALID_MENU;
	}
#endif

/* 
 * Menu:FIXES_DestroyMenu(Menu:menuid)
 * 
 * FIXES:
 *     GetPlayerMenu
 */
#if _FIX_Menus || FIX_GetPlayerMenu
	#if _FIX_Menus && !FIXES_Single
		forward _FIXES_DestroyMenu(ret);
		
		public _FIXES_DestroyMenu(ret)
		{
			FIXES_gsValidMenus[ret >>> 5] &= ~(1 << (ret & 0x1F));
		}
	#endif
	
	stock FIXES_DestroyMenu(Menu:menuid)
	{
		#if _FIX_Menus
			if (FIXES_IS_VALID_MENU(menuid))
		#endif
			{
				if (DestroyMenu(Menu:menuid))
				{
					#if _FIX_Menus
						#if FIXES_Single
							FIXES_gsValidMenus[_:menuid >>> 5] &= ~(1 << (_:menuid & 0x1F));
						#else
							CallRemoteFunction("_FIXES_DestroyMenu", FIXES_gscSpec@i, _:menuid);
						#endif
					#endif
					for (new playerid = 0; playerid != MAX_PLAYERS; ++playerid)
					{
						if (FIXES_gsCurrentMenu[playerid] = menuid)
						{
							if (HideMenuForPlayer(menuid, i))
							{
								#if FIXES_Single
									FIXES_gsSettings &= ~e_FIXES_SETTINGS_MENU_SET;
									FIXES_gsCurrentMenu[playerid] = Menu:INVALID_MENU;
								#else
									CallRemoteFunction(FIXES_gscSetPlayerMenu, FIXES_gscSpec@ii, playerid, INVALID_MENU);
								#endif
							}
						}
					}
					return 1;
				}
			}
		return 0;
	}
	
	#if defined _ALS_DestroyMenu
		#undef DestroyMenu
	#else
		
		native BAD_DestroyMenu(Menu:menuid) = DestroyMenu;
		
		#define _ALS_DestroyMenu
	#endif
	#define DestroyMenu FIXES_DestroyMenu
#endif

/* 
 * FIXES_AddMenuItem(Menu:menuid, column, const menutext[])
 * 
 * FIXES:
 *     AddMenuItem
 */
#if FIX_AddMenuItem
	stock FIXES_AddMenuItem(Menu:menuid, column, const menutext[])
	{
		if (FIXES_IS_VALID_MENU(menuid))
		{
			return AddMenuItem(menuid, column, menutext);
		}
		return 0;
	}
	
	#if defined _ALS_AddMenuItem
		#undef AddMenuItem
	#else
		
		native BAD_AddMenuItem(Menu:menuid, column, const menutext[]) = AddMenuItem;
		
		#define _ALS_AddMenuItem
	#endif
	#define AddMenuItem FIXES_AddMenuItem
#endif

/* 
 * FIXES_SetMenuColumnHeader(Menu:menuid, column, const columnheader[])
 * 
 * FIXES:
 *     SetMenuColumnHeader
 */
#if FIX_SetMenuColumnHeader
	stock FIXES_SetMenuColumnHeader(Menu:menuid, column, const columnheader[])
	{
		if (FIXES_IS_VALID_MENU(menuid))
		{
			return SetMenuColumnHeader(menuid, column, columnheader);
		}
		return 0;
	}
	
	#if defined _ALS_SetMenuColumnHeader
		#undef SetMenuColumnHeader
	#else
		
		native BAD_SetMenuColumnHeader(Menu:menuid, column, const columnheader[]) = SetMenuColumnHeader;
		
		#define _ALS_SetMenuColumnHeader
	#endif
	#define SetMenuColumnHeader FIXES_SetMenuColumnHeader
#endif

/* 
 * FIXES_ShowMenuForPlayer(Menu:menuid, playerid)
 * 
 * FIXES:
 *     ShowMenuForPlayer
 *     GetPlayerMenu
 */
#if FIX_ShowMenuForPlayer || FIX_GetPlayerMenu
	stock FIXES_ShowMenuForPlayer(Menu:menuid, playerid)
	{
		#if FIX_ShowMenuForPlayer
			if (FIXES_IS_VALID_MENU(menuid))
		#endif
			{
				#if FIX_GetPlayerMenu
					if (ShowMenuForPlayer(menuid, playerid))
					{
						#if FIXES_Single
							FIXES_gsSettings |= ~e_FIXES_SETTINGS_MENU_SET;
							FIXES_gsCurrentMenu[playerid] = menuid;
						#else
							CallRemoteFunction(FIXES_gscSetPlayerMenu, FIXES_gscSpec@ii, playerid, _:menuid);
						#endif
						return 1;
					}
				#else
					return ShowMenuForPlayer(menuid, playerid);
				#endif
			}
		return 0;
	}
	
	#if defined _ALS_ShowMenuForPlayer
		#undef ShowMenuForPlayer
	#else
		
		native BAD_ShowMenuForPlayer(Menu:menuid, playerid) = ShowMenuForPlayer;
		
		#define _ALS_ShowMenuForPlayer
	#endif
	#define ShowMenuForPlayer FIXES_ShowMenuForPlayer
#endif

/* 
 * FIXES_HideMenuForPlayer(Menu:menuid, playerid)
 * 
 * FIXES:
 *     HideMenuForPlayer
 *     HideMenuForPlayer_2
 *     GetPlayerMenu
 */
#if FIX_HideMenuForPlayer || FIX_GetPlayerMenu
	stock FIXES_HideMenuForPlayer(Menu:menuid, playerid)
	{
		#if FIX_HideMenuForPlayer
			if (FIXES_IS_VALID_MENU(menuid))
		#endif
			{
				#if FIX_GetPlayerMenu
					#if FIX_HideMenuForPlayer_2
						if (0 <= playerid < MAX_PLAYERS && FIXES_gsCurrentMenu[playerid] == menuid)
					#else
						if (FIXES_gsCurrentMenu[playerid] == menuid && HideMenuForPlayer(menuid, playerid))
					#endif
						{
							#if FIXES_Single
								FIXES_gsSettings &= ~e_FIXES_SETTINGS_MENU_SET;
								FIXES_gsCurrentMenu[playerid] = Menu:INVALID_MENU;
							#else
								CallRemoteFunction(FIXES_gscSetPlayerMenu, FIXES_gscSpec@ii, playerid, INVALID_MENU);
							#endif
							#if FIX_HideMenuForPlayer_2
								return HideMenuForPlayer(menuid, playerid);
							#else
								return 1;
							#endif
						}
				#else
					return HideMenuForPlayer(menuid, playerid);
				#endif
			}
		return 0;
	}
	
	#if defined _ALS_HideMenuForPlayer
		#undef HideMenuForPlayer
	#else
		
		native BAD_HideMenuForPlayer(Menu:menuid, playerid) = HideMenuForPlayer;
		
		#define _ALS_HideMenuForPlayer
	#endif
	#define HideMenuForPlayer FIXES_HideMenuForPlayer
#endif

/* 
 * FIXES_DisableMenu(Menu:menuid)
 * 
 * FIXES:
 *     DisableMenu
 */
#if FIX_DisableMenu
	stock FIXES_DisableMenu(Menu:menuid)
	{
		if (FIXES_IS_VALID_MENU(menuid))
		{
			return DisableMenu(menuid);
		}
		return 0;
	}
	
	#if defined _ALS_DisableMenu
		#undef DisableMenu
	#else
		
		native BAD_DisableMenu(Menu:menuid) = DisableMenu;
		
		#define _ALS_DisableMenu
	#endif
	#define DisableMenu FIXES_DisableMenu
#endif

/* 
 * FIXES_DisableMenuRow(Menu:menuid, row)
 * 
 * FIXES:
 *     DisableMenuRow
 */
#if FIX_DisableMenuRow
	stock FIXES_DisableMenuRow(Menu:menuid, row)
	{
		if (FIXES_IS_VALID_MENU(menuid))
		{
			return DisableMenuRow(menuid, row);
		}
		return 0;
	}
	
	#if defined _ALS_DisableMenuRow
		#undef DisableMenuRow
	#else
		
		native BAD_DisableMenuRow(Menu:menuid, row) = DisableMenuRow;
		
		#define _ALS_DisableMenuRow
	#endif
	#define DisableMenuRow FIXES_DisableMenuRow
#endif

/* 
 * Menu:FIXES_GetPlayerMenu(playerid)
 * 
 * FIXES:
 *     GetPlayerMenu
 */
#if FIX_GetPlayerMenu
	stock Menu:FIXES_GetPlayerMenu(playerid)
	{
		if (0 <= playerid < MAX_PLAYERS)
		{
			return FIXES_gsCurrentMenu[playerid];
		}
		return Menu:INVALID_MENU;
	}
	
	#if defined _ALS_GetPlayerMenu
		#undef GetPlayerMenu
	#else
		
		native BAD_GetPlayerMenu(playerid) = GetPlayerMenu;
		
		#define _ALS_GetPlayerMenu
	#endif
	#define GetPlayerMenu FIXES_GetPlayerMenu
#endif

/* 
 * OnPlayerStateChange(playerid, newstate, oldstate)
 * 
 * FIXES:
 *     HydraSniper
 *     GetPlayerWeapon
 *     PutPlayerInVehicle
 *     TrainExit
 */
#if FIX_HydraSniper || FIX_GetPlayerWeapon || FIX_PutPlayerInVehicle || FIX_OnPlayerEnterVehicle || FIX_TrainExit
	public OnPlayerStateChange(playerid, newstate, oldstate)
	{
		#if !FIXES_Single
			if (!(FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE))
			{
				#if defined FIXES_OnPlayerStateChange
					return FIXES_OnPlayerStateChange(playerid, newstate, oldstate);
				#else
					return 1;
				#endif
			}
		#endif
		
		// =============================
		//  BEGIN: OnPlayerEnterVehicle 
		// =============================
		#if FIX_OnPlayerEnterVehicle
				if (newstate == PLAYER_STATE_PASSENGER)
				{
					new
						model = GetVehicleModel(GetPlayerVehicleID(playerid)) - 400;
					if (0 <= model <= 211)
					{
						new
							seat = GetPlayerVehicleSeat(playerid);
						if (seat != 128)
						{
							model = (FIXES_gscMaxPassengers[model >>> 3] >>> ((model & 7) << 2)) & 0xF;
							if (model == 0 || model == 15)
							{
								// Shouldn't be in this vehicle at all.
								FIXES_BlockUpdate(playerid, true);
							}
							else if (!(0 < seat <= model))
							{
								// In an out of range seat.
								FIXES_BlockUpdate(playerid, true);
							}
						}
					}
					else
					{
						FIXES_BlockUpdate(playerid, true);
					}
				}
				else if (newstate == PLAYER_STATE_DRIVER)
				{
						new
							model = GetPlayerVehicleSeat(playerid);
						if (model != 128)
						{
							if (model == 0)
							{
								model = GetVehicleModel(GetPlayerVehicleID(playerid)) - 400;
								if (!(0 <= model <= 211) || FIXES_gscMaxPassengers[model >>> 3] >>> ((model & 7) << 2) & 0xF == 15)
								{
									// In an invalid vehicle (one you can't drive).
									FIXES_BlockUpdate(playerid, true);
								}
							}
							else
							{
								// They are a driver, but not in the driver's seat.
								FIXES_BlockUpdate(playerid, true);
							}
						}
					#if FIX_HydraSniper
						else
						{
							model = GetVehicleModel(GetPlayerVehicleID(playerid));
						}
					#endif
			#if !FIX_HydraSniper
				}
			#endif
		#endif
		// =============================
		//  END:   OnPlayerEnterVehicle 
		// =============================
		
		// ====================
		//  BEGIN: HydraSniper 
		// ====================
		#if FIX_HydraSniper
			#if !FIX_OnPlayerEnterVehicle
				// Only called if the same check above isn't called.
				if (newstate == PLAYER_STATE_DRIVER)
				{
					new
						model = GetVehicleModel(GetPlayerVehicleID(playerid));
			#endif
					if (GetPlayerWeapon(playerid) == 34 && (model == 520 || model == 425))
					{
						SetPlayerArmedWeapon(playerid, 0);
						#if FIX_GetPlayerWeapon
							// This is the first cross-dependednt fix.
							#if FIXES_Single
								FIXES_gsPlayerWeapon[playerid] = 0;
							#else
								SetPVarInt(playerid, FIXES_pvarPlayerWeapon, 0);
							#endif
						#endif
					}
				}
		#endif
		// ====================
		//  END:   HydraSniper 
		// ====================
		
		#if FIX_GetPlayerWeapon || FIX_PutPlayerInVehicle || FIX_TrainExit
			#if PLAYER_STATE_PASSENGER != PLAYER_STATE_DRIVER + 1
				#error FIX_GetPlayerWeapon/FIX_PutPlayerInVehicle state assertation failed.
			#endif
			if (PLAYER_STATE_DRIVER <= oldstate <= PLAYER_STATE_PASSENGER)
			//if (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
			{
				#if FIX_PutPlayerInVehicle || FIX_TrainExit
					new
						e_FIXES_BOOLS:bools = FIXES_gsPlayerBools[playerid];
				#endif
				
				// ========================
				//  BEGIN: GetPlayerWeapon 
				// ========================
				#if FIX_GetPlayerWeapon
					#if FIXES_Single
						FIXES_gsPlayerWeapon[playerid] = -1;
					#else
						SetPVarInt(playerid, FIXES_pvarPlayerWeapon, -1);
					#endif
				#endif
				// ========================
				//  END:   GetPlayerWeapon 
				// ========================
				
				// ==================
				//  BEGIN: TrainExit
				// ==================
				#if FIX_TrainExit
					FIXES_PRINTF("train exit");
					if (bools & e_FIXES_BOOLS_PUT_IN_TRAIN)
					{
						FIXES_PRINTF("OK");
						SetCameraBehindPlayer(playerid),
						bools &= ~e_FIXES_BOOLS_PUT_IN_TRAIN;
					}
				#endif
				// ==================
				//  END:   TrainExit
				// ==================
				
				// ===========================
				//  START: PutPlayerInVehicle 
				// ===========================
				#if FIX_PutPlayerInVehicle
					// Update their vehicle once we KNOW the client has done the
					// removal from the vehicle.
					if (bools & e_FIXES_BOOLS_PUT_IN_VEHICLE)
					{
						new
							vid = FIXES_gsVehicleSeatData[playerid] & 0x00FFFFFF;
						// Limited to "only" 16777216 vehicles and 256 seats.
						PutPlayerInVehicle(playerid, vid, FIXES_gsVehicleSeatData[playerid] >>> 24),
						bools &= ~e_FIXES_BOOLS_PUT_IN_VEHICLE;
						#if FIX_TrainExit
							switch (GetVehicleModel(vid))
							{
								case 449, 537, 538:
								{
									bools |= e_FIXES_BOOLS_PUT_IN_TRAIN;
								}
							}
						#endif
					}
				#endif
				// ===========================
				//  END:   PutPlayerInVehicle 
				// ===========================
				
				#if FIX_PutPlayerInVehicle || FIX_TrainExit
					FIXES_gsPlayerBools[playerid] = bools;
				#endif
			}
		#endif
		
		#if defined FIXES_OnPlayerStateChange
			return FIXES_OnPlayerStateChange(playerid, newstate, oldstate);
		#else
			return 1;
		#endif
	}
	
	#if defined _ALS_OnPlayerStateChange
		#undef OnPlayerStateChange
	#else
		#define _ALS_OnPlayerStateChange
	#endif
	#define OnPlayerStateChange FIXES_OnPlayerStateChange
	
	#if defined FIXES_OnPlayerStateChange
		forward FIXES_OnPlayerStateChange(playerid, newstate, oldstate);
	#endif
#endif

/* 
 * FIXES_GivePlayerWeapon(playerid, weaponid, ammo)
 * 
 * FIXES:
 *     HydraSniper
 */
#if FIX_HydraSniper
	stock FIXES_GivePlayerWeapon(playerid, weaponid, ammo)
	{
		new
			vid = GetPlayerVehicleID(playerid);
		if (vid)
		{
			vid = GetVehicleModel(vid);
			if (weaponid == 34 && (vid == 520 || vid == 425))
			{
				vid = GivePlayerWeapon(playerid, weaponid, ammo),
				SetPlayerArmedWeapon(playerid, 0);
				#if FIX_GetPlayerWeapon
					#if FIXES_Single
						FIXES_gsPlayerWeapon[playerid] = 0;
					#else
						SetPVarInt(playerid, FIXES_pvarPlayerWeapon, 0);
					#endif
				#endif
				return vid;
			}
		}
		return GivePlayerWeapon(playerid, weaponid, ammo);
	}
	
	#if defined _ALS_GivePlayerWeapon
		#undef GivePlayerWeapon
	#else
		
		native BAD_GivePlayerWeapon(playerid, weaponid, ammo) = GivePlayerWeapon;
		
		#define _ALS_GivePlayerWeapon
	#endif
	#define GivePlayerWeapon FIXES_GivePlayerWeapon
#endif

/* 
 * FIXES_SetPlayerArmedWeapon(playerid, weaponid)
 * 
 * FIXES:
 *     GetPlayerWeapon
 */
#if FIX_GetPlayerWeapon
	stock FIXES_SetPlayerArmedWeapon(playerid, weaponid)
	{
		#if FIX_AllowInteriorWeapons
			if (FIXES_gsSettings & e_FIXES_SETTINGS_INTERIOR && GetPlayerInterior(playerid))
			{
				// Not allowed weapons.
				return 0;
			}
		#endif
		new
			vid = GetPlayerVehicleID(playerid);
		if (vid)
		{
			#if FIX_HydraSniper
				vid = GetVehicleModel(vid);
				if (weaponid == 34 && (vid == 520 || vid == 425))
				{
					return 0;
				}
			#endif
			//FIXES_gsPlayerWeapon[playerid] = weaponid;
			#if FIXES_Single
				FIXES_gsPlayerWeapon[playerid] = weaponid;
			#else
				SetPVarInt(playerid, FIXES_pvarPlayerWeapon, weaponid);
			#endif
		}
		return SetPlayerArmedWeapon(playerid, weaponid);
	}
	
	#if defined _ALS_SetPlayerArmedWeapon
		#undef SetPlayerArmedWeapon
	#else
		
		native BAD_SetPlayerArmedWeapon(playerid, weaponid) = SetPlayerArmedWeapon;
		
		#define _ALS_SetPlayerArmedWeapon
	#endif
	#define SetPlayerArmedWeapon FIXES_SetPlayerArmedWeapon
#endif

/* 
 * FIXES_GetPlayerWeapon(playerid)
 * 
 * FIXES:
 *     GetPlayerWeapon
 */
#if FIX_GetPlayerWeapon
	stock FIXES_GetPlayerWeapon(playerid)
	{
		#if FIXES_Single
			new
				ret = FIXES_gsPlayerWeapon[playerid];
		#else
			new
				ret = GetPVarInt(playerid, FIXES_pvarPlayerWeapon);
		#endif
		if (ret == -1)
		{
			return GetPlayerWeapon(playerid);
		}
		return ret;
	}
	
	#if defined _ALS_GetPlayerWeapon
		#undef GetPlayerWeapon
	#else
		
		native BAD_GetPlayerWeapon(playerid) = GetPlayerWeapon;
		
		#define _ALS_GetPlayerWeapon
	#endif
	#define GetPlayerWeapon FIXES_GetPlayerWeapon
#endif

/* 
 * FIXES_PutPlayerInVehicle(playerid, vehicleid, seatid)
 * 
 * FIXES:
 *     PutPlayerInVehicle
 */
#if FIX_PutPlayerInVehicle || FIX_TrainExit
	#if FIXES_Single
		stock FIXES_PutPlayerInVehicle(playerid, vehicleid, seatid)
		{
			// ==================
			//  BEGIN: TrainExit
			// ==================
			#if FIX_TrainExit
				FIXES_PRINTF("TrainExit %d", GetVehicleModel(vehicleid));
				switch (GetVehicleModel(vehicleid))
				{
					case 449, 537, 538:
					{
						FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_PUT_IN_TRAIN;
					}
				}
			#endif
			// ==================
			//  END:   TrainExit
			// ==================
			
			// ===========================
			//  BEGIN: PutPlayerInVehicle 
			// ===========================
			#if FIX_PutPlayerInVehicle
				new
					vid = GetPlayerVehicleID(playerid);
				if (vid)
				{
					new
						Float:x,
						Float:y,
						Float:z;
					// Remove them without the animation.
					return
						GetVehiclePos(vid, x, y, z),
						SetPlayerPos(playerid, x, y, z),
						FIXES_gsVehicleSeatData[playerid] = seatid << 24 | vehicleid,
						FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_PUT_IN_VEHICLE,
						1;
				}
			#endif
			// ===========================
			//  END:   PutPlayerInVehicle 
			// ===========================
			return PutPlayerInVehicle(playerid, vehicleid, seatid);
		}
	#else
		forward _FIXES_PutPlayerInVehicle(playerid, vehicleid, seatid, from, data);
		
		stock FIXES_PutPlayerInVehicle(playerid, vehicleid, seatid)
		{
			FIXES_PRINTF("NOT SINGLE");
			// ===========================
			//  BEGIN: PutPlayerInVehicle 
			// ===========================
			#if FIX_PutPlayerInVehicle
				new
					vid = GetPlayerVehicleID(playerid);
				if (vid)
				{
					new
						Float:x,
						Float:y,
						Float:z;
					// Remove them without the animation.
					return
						GetVehiclePos(vid, x, y, z),
						SetPlayerPos(playerid, x, y, z),
						CallRemoteFunction(FIXES_gscPutPlayerInVehicle, FIXES_gscSpec@iiiii, playerid, vehicleid, seatid, 1, vid),
						1;
				}
			#endif
			// ===========================
			//  END:   PutPlayerInVehicle 
			// ===========================
			
			// ==================
			//  BEGIN: TrainExit
			// ==================
			#if FIX_TrainExit
				new
					model = GetVehicleModel(vehicleid);
				switch (model)
				{
					case 449, 537, 538:
					{
						CallRemoteFunction(FIXES_gscPutPlayerInVehicle, FIXES_gscSpec@iiiii, playerid, vehicleid, seatid, 0, model);
						//FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_PUT_IN_TRAIN;
					}
				}
			#endif
			// ==================
			//  END:   TrainExit
			// ==================
			return PutPlayerInVehicle(playerid, vehicleid, seatid);
		}
		
		public _FIXES_PutPlayerInVehicle(playerid, vehicleid, seatid, from, data)
		{
			FIXES_PRINTF("IN CHARGE: %d", (FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE));
			if (FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE)
			{
				// ===========================
				//  BEGIN: PutPlayerInVehicle 
				// ===========================
				#if FIX_PutPlayerInVehicle
					if (from)
					{
						FIXES_gsVehicleSeatData[playerid] = seatid << 24 | vehicleid,
						FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_PUT_IN_VEHICLE;
					}
				#endif
				// ===========================
				//  END:   PutPlayerInVehicle 
				// ===========================
				
				// ==================
				//  BEGIN: TrainExit
				// ==================
				#if FIX_TrainExit
					#if FIX_PutPlayerInVehicle
						else
					#else
						if (!from)
					#endif
						{
							switch (data)
							{
								case 449, 537, 538:
								{
									FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_PUT_IN_TRAIN;
								}
							}
						}
				#endif
				// ==================
				//  END:   TrainExit
				// ==================
			}
			return 1;
		}
	#endif
	
	#if defined _ALS_PutPlayerInVehicle
		#undef PutPlayerInVehicle
	#else
		
		native BAD_PutPlayerInVehicle(playerid, vehicleid, seatid) = PutPlayerInVehicle;
		
		#define _ALS_PutPlayerInVehicle
	#endif
	#define PutPlayerInVehicle FIXES_PutPlayerInVehicle
#endif

/*
 * FIXES_SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size)
 *
 * FIXES:
 *     SetPlayerCheckpoint
 */
#if FIX_SetPlayerCheckpoint
	stock FIXES_SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size)
	{
		return
			DisablePlayerCheckpoint(playerid),
			SetPlayerCheckpoint(playerid, x, y, z, size);
	}
	
	#if defined _ALS_SetPlayerCheckpoint
		#undef SetPlayerCheckpoint
	#else
		
		native BAD_SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size) = SetPlayerCheckpoint;
		
		#define _ALS_SetPlayerCheckpoint
	#endif
	#define SetPlayerCheckpoint FIXES_SetPlayerCheckpoint
#endif

/*
 * FIXES_SetPlayerRaceCheckpoint(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size)
 *
 * FIXES:
 *     SetPlayerRaceCheckpoint
 */
#if FIX_SetPlayerRaceCheckpoint
	stock FIXES_SetPlayerRaceCheckpoint(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size)
	{
		return
			DisablePlayerRaceCheckpoint(playerid),
			SetPlayerRaceCheckpoint(playerid, type, x, y, z, nextx, nexty, nextz, size);
	}
	
	#if defined _ALS_SetPlayerRaceCheckpoint
		#undef SetPlayerRaceCheckpoint
	#else
		
		native BAD_SetPlayerRaceCheckpoint(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size) = SetPlayerRaceCheckpoint;
		
		#define _ALS_SetPlayerRaceCheckpoint
	#endif
	#define SetPlayerRaceCheckpoint FIXES_SetPlayerRaceCheckpoint
#endif

/*
 * Text:FIXES_TextDrawCreate(Float:x, Float:y, text[])
 *
 * FIXES:
 *     TextDrawCreate
 */
#if FIX_TextDrawCreate
	stock Text:FIXES_TextDrawCreate(Float:x, Float:y, text[])
	{
		if (text[0] == '\0' || text[0] == '\1' && text[1] == '\0')
		{
			return TextDrawCreate(x, y, " ");
		}
		else
		{
			return TextDrawCreate(x, y, text);
		}
	}
	
	#if defined _ALS_TextDrawCreate
		#undef TextDrawCreate
	#else
		
		native Text:BAD_TextDrawCreate(Float:x, Float:y, text[]) = TextDrawCreate;
		
		#define _ALS_TextDrawCreate
	#endif
	#define TextDrawCreate FIXES_TextDrawCreate
#endif

/*
 * FIXES_TextDrawSetString(Text:text, string[])
 *
 * FIXES:
 *     TextDrawSetString
 */
#if FIX_TextDrawSetString
	stock FIXES_TextDrawSetString(Text:text, string[])
	{
		if (string[0] == '\0' || string[0] == '\1' && string[1] == '\0')
		{
			return TextDrawSetString(text, " ");
		}
		else
		{
			return TextDrawSetString(text, string);
		}
	}
	
	#if defined _ALS_TextDrawSetString
		#undef TextDrawSetString
	#else
		
		native BAD_TextDrawSetString(Text:text, string[]) = TextDrawSetString;
		
		#define _ALS_TextDrawSetString
	#endif
	#define TextDrawSetString FIXES_TextDrawSetString
#endif

/*
 * FIXES_AllowInteriorWeapons(allow)
 *
 * FIXES:
 *     AllowInteriorWeapons
 */
#if FIX_AllowInteriorWeapons
	#if FIXES_Single
		stock FIXES_AllowInteriorWeapons(allow)
		{
			if (allow)
			{
				FIXES_gsSettings &= ~e_FIXES_SETTINGS_INTERIOR;
				for (new i = 0; i != MAX_PLAYERS; ++i)
				{
					FIXES_gsPlayerBools[i] &= ~e_FIXES_BOOLS_INTERIOR;
				}
			}
			else
			{
				FIXES_gsSettings |= e_FIXES_SETTINGS_INTERIOR;
				for (new i = 0; i != MAX_PLAYERS; ++i)
				{
					if (GetPlayerInterior(i))
					{
						FIXES_gsPlayerBools[i] |= e_FIXES_BOOLS_INTERIOR;
					}
				}
			}
			return allow;
		}
	#else
		forward _FIXES_AllowInteriorWeapons(allow);
		
		stock FIXES_AllowInteriorWeapons(allow)
		{
			CallRemoteFunction(FIXES_gscAllowInteriorWeapons, FIXES_gscSpec@i, allow);
			return allow;
		}
		
		public _FIXES_AllowInteriorWeapons(allow)
		{
			if (allow)
			{
				FIXES_gsSettings &= ~e_FIXES_SETTINGS_INTERIOR;
				for (new i = 0; i != MAX_PLAYERS; ++i)
				{
					FIXES_gsPlayerBools[i] &= ~e_FIXES_BOOLS_INTERIOR;
				}
			}
			else
			{
				FIXES_gsSettings |= e_FIXES_SETTINGS_INTERIOR;
				for (new i = 0; i != MAX_PLAYERS; ++i)
				{
					if (GetPlayerInterior(i))
					{
						FIXES_gsPlayerBools[i] |= e_FIXES_BOOLS_INTERIOR;
					}
				}
			}
			return allow;
		}
	#endif
	
	#if defined _ALS_AllowInteriorWeapons
		#undef AllowInteriorWeapons
	#else
		
		native BAD_AllowInteriorWeapons(allow) = AllowInteriorWeapons;
		
		#define _ALS_AllowInteriorWeapons
	#endif
	#define AllowInteriorWeapons FIXES_AllowInteriorWeapons
#endif

/* 
 * OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
 * 
 * FIXES:
 *     AllowTeleport
 */
#if FIX_AllowTeleport && !defined FILTERSCRIPT
	forward _FIXES_AllowTeleport(playerid, allow);
	
	public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
	{
		// ======================
		//  BEGIN: AllowTeleport 
		// ======================
		#if FIX_AllowTeleport
			if (!_FIXES_gIsFilterscript)
			{
				// Unusually, the call order here is always Game Mode first -
				// most callbacks are Filter Script first.
				if ((FIXES_gsPlayerBools[playerid] & e_FIXES_BOOLS_TELEPORT) || ((FIXES_gsSettings & e_FIXES_SETTINGS_ADMIN_TELEPORT) && (IsPlayerAdmin(playerid))))
				{
					SetPlayerPosFindZ(playerid, fX, fY, fZ);
				}
			}
		#endif
		// ======================
		//  END:   AllowTeleport 
		// ======================
		#if defined FIXES_OnPlayerClickMap
			return FIXES_OnPlayerClickMap(playerid, fX, fY, fZ);
		#else
			return 1;
		#endif
	}
	
	#if defined _ALS_OnPlayerClickMap
		#undef OnPlayerClickMap
	#else
		#define _ALS_OnPlayerClickMap
	#endif
	#define OnPlayerClickMap FIXES_OnPlayerClickMap
	
	#if defined FIXES_OnPlayerClickMap
		forward FIXES_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ);
	#endif
#endif

/*
 * FIXES_AllowPlayerTeleport(playerid, allow)
 *
 * FIXES:
 *     AllowTeleport
 */
#if FIX_AllowTeleport
	#if FIXES_Single
		stock FIXES_AllowPlayerTeleport(playerid, allow)
		{
			if (0 <= playerid < MAX_PLAYERS)
			{
				if (allow)
				{
					FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_TELEPORT;
				}
				else
				{
					FIXES_gsPlayerBools[playerid] &= ~e_FIXES_BOOLS_TELEPORT;
				}
			}
			return 0;
		}
	#else
		stock FIXES_AllowPlayerTeleport(playerid, allow)
		{
			if (0 <= playerid < MAX_PLAYERS)
			{
				CallRemoteFunction(FIXES_gscAllowTeleport, FIXES_gscSpec@ii, playerid, allow);
			}
			return 0;
		}
	#endif
	
	#if defined _ALS_AllowPlayerTeleport
		#undef AllowPlayerTeleport
	#else
		
		native BAD_AllowPlayerTeleport(playerid, allow) = AllowPlayerTeleport;
		
		#define _ALS_AllowPlayerTeleport
	#endif
	#define AllowPlayerTeleport FIXES_AllowPlayerTeleport
#endif

/*
 * FIXES_AllowAdminTeleport(allow)
 *
 * FIXES:
 *     AllowTeleport
 */
#if FIX_AllowTeleport
	#if FIXES_Single
		stock FIXES_AllowAdminTeleport(allow)
		{
			if (allow)
			{
				FIXES_gsSettings |= e_FIXES_SETTINGS_ADMIN_TELEPORT;
			}
			else
			{
				FIXES_gsSettings &= ~e_FIXES_SETTINGS_ADMIN_TELEPORT;
			}
			return allow;
		}
	#else
		stock FIXES_AllowAdminTeleport(allow)
		{
			CallRemoteFunction(FIXES_gscAllowTeleport, FIXES_gscSpec@ii, INVALID_PLAYER_ID, allow)
			return allow;
		}
	#endif
	
	#if defined _ALS_AllowAdminTeleport
		#undef AllowAdminTeleport
	#else
		
		native BAD_AllowAdminTeleport(allow) = AllowAdminTeleport;
		
		#define _ALS_AllowAdminTeleport
	#endif
	#define AllowAdminTeleport FIXES_AllowAdminTeleport
#endif

/*
 * FIXES_AllowAdminTeleport(allow)
 *
 * FIXES:
 *     AllowTeleport
 */
#if FIX_AllowTeleport && !defined FILTERSCRIPT && !FIXES_Single
	public _FIXES_AllowTeleport(playerid, allow)
	{
		if (!_FIXES_gIsFilterscript)
		{
			if (playerid == INVALID_PLAYER_ID)
			{
				if (allow)
				{
					FIXES_gsSettings |= e_FIXES_SETTINGS_ADMIN_TELEPORT;
				}
				else
				{
					FIXES_gsSettings &= ~e_FIXES_SETTINGS_ADMIN_TELEPORT;
				}
			}
			else
			{
				if (allow)
				{
					FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_TELEPORT;
				}
				else
				{
					FIXES_gsPlayerBools[playerid] &= ~e_FIXES_BOOLS_TELEPORT;
				}
			}
		}
	}
#endif

/*
 * FIXES_SetPlayerSpecialAction(playerid, actionid)
 *
 * FIXES:
 *     SetPlayerSpecialAction
 */
#if FIX_SetPlayerSpecialAction
	stock FIXES_SetPlayerSpecialAction(playerid, actionid)
	{
		if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK) 
		{
			ClearAnimations(playerid);
		}
		SetPlayerSpecialAction(playerid, actionid);
		return 1;
	}
	
	#if defined _ALS_SetPlayerSpecialAction
		#undef SetPlayerSpecialAction
	#else
		
		native BAD_SetPlayerSpecialAction(playerid, actionid) = SetPlayerSpecialAction;
		
		#define _ALS_SetPlayerSpecialAction
	#endif
	#define SetPlayerSpecialAction FIXES_SetPlayerSpecialAction
#endif

/*
 * FIXES_ShowPlayerDialog(playerid, dialog, style, title[], caption[], button1[], button2[])
 *
 * FIXES:
 *     OnDialogResponse
 *     GetPlayerDialog
 */
#if FIX_OnDialogResponse || FIX_GetPlayerDialog
	stock FIXES_ShowPlayerDialog(playerid, dialog, style, title[], caption[], button1[], button2[])
	{
		if (0 <= playerid < MAX_PLAYERS)
		{
			#if FIXES_Single
				FIXES_gsDialogID[playerid] = dialog;
			#else
				SetPVarInt(playerid, FIXES_pvarPlayerDialog, dialog);
			#endif
			return ShowPlayerDialog(playerid, dialog, style, title, caption, button1, button2);
		}
		return 0;
	}
	
	#if defined _ALS_ShowPlayerDialog
		#undef ShowPlayerDialog
	#else
		
		native BAD_ShowPlayerDialog(playerid, dialog, style, title[], caption[], button1[], button2[]) = ShowPlayerDialog;
		
		#define _ALS_ShowPlayerDialog
	#endif
	#define ShowPlayerDialog FIXES_ShowPlayerDialog
#endif

/* 
 * OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
 * 
 * FIXES:
 *     OnDialogResponse
 *     GetPlayerDialog
 */
#if FIX_OnDialogResponse || FIX_GetPlayerDialog
	public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
	{
		// =========================
		//  BEGIN: OnDialogResponse 
		// =========================
		#if FIX_OnDialogResponse || FIX_GetPlayerDialog
			#if FIXES_Single
				#if FIX_OnDialogResponse
					dialogid = FIXES_gsDialogID[playerid];
				#endif
				FIXES_gsDialogID[playerid] = INVALID_DIALOG_ID;
			#elseif FIX_OnDialogResponse
				if (FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE)
				{
					// If there are multiple scripts, we can't just wipe the
					// current dialog data or subsequent scripts will display
					// the wrong value.
					dialogid = GetPVarInt(playerid, FIXES_pvarPlayerDialog),
					SetPVarInt(playerid, FIXES_pvarCurrentDialog, dialogid),
					SetPVarInt(playerid, FIXES_pvarPlayerDialog, INVALID_DIALOG_ID);
				}
				else
				{
					dialogid = GetPVarInt(playerid, FIXES_pvarCurrentDialog);
				}
			#else
				SetPVarInt(playerid, FIXES_pvarPlayerDialog, INVALID_DIALOG_ID);
			#endif
			if (inputtext[0])
			{
				#if defined FIXES_OnDialogResponse
					return FIXES_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
				#else
					return 1;
				#endif
			}
			else
			{
				#if defined FIXES_OnDialogResponse
					return FIXES_OnDialogResponse(playerid, dialogid, response, listitem, FIXES_gscNULL);
				#else
					return 1;
				#endif
			}
		#endif
		// =========================
		//  END:   OnDialogResponse 
		// =========================
	}
	
	#if defined _ALS_OnDialogResponse
		#undef OnDialogResponse
	#else
		#define _ALS_OnDialogResponse
	#endif
	#define OnDialogResponse FIXES_OnDialogResponse
	
	#if defined FIXES_OnDialogResponse
		forward FIXES_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
	#endif
#endif

/*
 * FIXES_GetPlayerDialog(playerid)
 *
 * FIXES:
 *     GetPlayerDialog
 */
#if FIX_GetPlayerDialog
	stock FIXES_GetPlayerDialog(playerid)
	{
		if (0 <= playerid < MAX_PLAYERS)
		{
			#if FIXES_Single
				return FIXES_gsDialogID[playerid];
			#else
				return GetPVarInt(playerid, FIXES_pvarPlayerDialog);
			#endif
		}
		return -1;
	}
	
	#if defined _ALS_GetPlayerDialog
		#undef GetPlayerDialog
	#else
		#define _ALS_GetPlayerDialog
	#endif
	#define GetPlayerDialog FIXES_GetPlayerDialog
#endif

/*
 * FIXES_valstr(dest[], value, bool:pack = false)
 *
 * FIXES:
 *     valstr
 */
#if FIX_valstr
	stock FIXES_valstr(dest[], value, bool:pack = false)
	{
		// "format" can't handle cellmin properly.
		static const
			sc_szCellmin[] = !"-2147483648";
		if (value == cellmin)
		{
			pack && strpack(dest, sc_szCellmin, 12) || strunpack(dest, sc_szCellmin, 12);
		}
		else
		{
			format(dest, 12, "%d", value),
			pack && strpack(dest, dest, 12);
		}
		return 0;
	}
	
	#if defined _ALS_valstr
		#undef valstr
	#else
		
		native BAD_valstr(dest[], value, bool:pack = false) = valstr;
		
		#define _ALS_valstr
	#endif
	#define valstr FIXES_valstr
#endif

/*
 * FIXES_fclose(File:handle)
 *
 * FIXES:
 *     fclose
 */
#if FIX_fclose
	stock bool:FIXES_fclose(File:handle)
	{
		if (handle)
		{
			return fclose(handle);
		}
		return false;
	}
	
	#if defined _ALS_fclose
		#undef fclose
	#else
		
		native BAD_fclose(File:handle) = fclose;
		
		#define _ALS_fclose
	#endif
	#define fclose FIXES_fclose
#endif

/*
 * FIXES_fwrite(File:handle, const string[])
 *
 * FIXES:
 *     fwrite
 */
#if FIX_fwrite
	stock FIXES_fwrite(File:handle, const string[])
	{
		if (handle)
		{
			return fwrite(handle, string);
		}
		return 0;
	}
	
	#if defined _ALS_fwrite
		#undef fwrite
	#else
		
		native BAD_fwrite(File:handle, const string[]) = fwrite;
		
		#define _ALS_fwrite
	#endif
	#define fwrite FIXES_fwrite
#endif

/*
 * FIXES_fread(File:handle, string[], size = sizeof (string), bool:pack = false)
 *
 * FIXES:
 *     fread
 */
#if FIX_fread
	stock FIXES_fread(File:handle, string[], size = sizeof (string), bool:pack = false)
	{
		if (handle)
		{
			return fread(handle, string, size, pack);
		}
		return 0;
	}
	
	#if defined _ALS_fread
		#undef fread
	#else
		
		native BAD_fread(File:handle, string[], size = sizeof (string), bool:pack = false) = fread;
		
		#define _ALS_fread
	#endif
	#define fread FIXES_fread
#endif

/*
 * FIXES_fputchar(File:handle, value, bool:utf8 = true)
 *
 * FIXES:
 *     fputchar
 */
#if FIX_fputchar
	stock bool:FIXES_fputchar(File:handle, value, bool:utf8 = true)
	{
		if (handle)
		{
			return fputchar(handle, value, utf8);
		}
		return false;
	}
	
	#if defined _ALS_fputchar
		#undef fputchar
	#else
		
		native BAD_fputchar(File:handle, value, bool:utf8 = true) = fputchar;
		
		#define _ALS_fputchar
	#endif
	#define fputchar FIXES_fputchar
#endif

/*
 * FIXES_fgetchar(File:handle, value, bool:utf8 = true)
 *
 * FIXES:
 *     fgetchar
 */
#if FIX_fgetchar
	stock FIXES_fgetchar(File:handle, value, bool:utf8 = true)
	{
		if (handle)
		{
			return fgetchar(handle, value, utf8);
		}
		return 0;
	}
	
	#if defined _ALS_fgetchar
		#undef fgetchar
	#else
		
		native BAD_fgetchar(File:handle, value, bool:utf8 = true) = fgetchar;
		
		#define _ALS_fgetchar
	#endif
	#define fgetchar FIXES_fgetchar
#endif

/*
 * FIXES_fblockwrite(File:handle, const buffer[], size = sizeof (buffer))
 *
 * FIXES:
 *     fblockwrite
 */
#if FIX_fblockwrite
	stock FIXES_fblockwrite(File:handle, const buffer[], size = sizeof (buffer))
	{
		if (handle)
		{
			return fblockwrite(handle, buffer, size);
		}
		return 0;
	}
	
	#if defined _ALS_fblockwrite
		#undef fblockwrite
	#else
		
		native BAD_fblockwrite(File:handle, const buffer[], size = sizeof (buffer)) = fblockwrite;
		
		#define _ALS_fblockwrite
	#endif
	#define fblockwrite FIXES_fblockwrite
#endif

/*
 * FIXES_fblockread(File:handle, buffer[], size = sizeof (buffer))
 *
 * FIXES:
 *     fblockread
 */
#if FIX_fblockread
	stock FIXES_fblockread(File:handle, buffer[], size = sizeof (buffer))
	{
		if (handle)
		{
			return fblockread(handle, buffer, size);
		}
		return 0;
	}
	
	#if defined _ALS_fblockread
		#undef fblockread
	#else
		
		native BAD_fblockread(File:handle, buffer[], size = sizeof (buffer)) = fblockread;
		
		#define _ALS_fblockread
	#endif
	#define fblockread FIXES_fblockread
#endif

/*
 * FIXES_fseek(File:handle, position = 0, seek_whence:whence = seek_start)
 *
 * FIXES:
 *     fseek
 */
#if FIX_fseek
	stock FIXES_fseek(File:handle, position = 0, seek_whence:whence = seek_start)
	{
		if (handle)
		{
			return fseek(handle, position, whence);
		}
		return 0;
	}
	
	#if defined _ALS_fseek
		#undef fseek
	#else
		
		native BAD_fseek(File:handle, position = 0, seek_whence:whence = seek_start) = fseek;
		
		#define _ALS_fseek
	#endif
	#define fseek FIXES_fseek
#endif

/*
 * FIXES_flength(File:handle)
 *
 * FIXES:
 *     flength
 */
#if FIX_flength
	stock FIXES_flength(File:handle)
	{
		if (handle)
		{
			return flength(handle);
		}
		return 0;
	}
	
	#if defined _ALS_flength
		#undef flength
	#else
		
		native BAD_flength(File:handle) = flength;
		
		#define _ALS_flength
	#endif
	#define flength FIXES_flength
#endif

/*
 * FIXES_Kick(playerid)
 *
 * FIXES:
 *     Kick
 */
#if FIX_Kick
	forward _FIXES_Kick(playerid);
	
	public _FIXES_Kick(playerid)
	{
		FIXES_gsPlayerBools[playerid] &= ~e_FIXES_BOOLS_KICKED;
		Kick(playerid);
	}
	
	#if !FIXES_Single
		forward @FIXES_Kick(playerid);
		
		public @FIXES_Kick(playerid)
		{
			FIXES_BlockUpdate(playerid, true, 0);
		}
	#endif
	
	stock FIXES_Kick(playerid)
	{
		if (FIXES_gsPlayerBools[playerid] & e_FIXES_BOOLS_ON_PLAYER_CONNECT)
		{
			// Disable as much of the server as possible quickly.
			#if FIXES_Single
				FIXES_BlockUpdate(playerid, true, 0);
			#else
				CallRemoteFunction("@FIXES_Kick", "i", playerid);
			#endif
			return
				TogglePlayerSpectating(playerid, true),
				TogglePlayerControllable(playerid, false),
				SetPVarInt(playerid, FIXES_pvarKick, SetTimerEx(FIXES_gscKick, 1000, 0, FIXES_gscSpec@i, playerid)),
				FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_KICKED,
				1;
		}
		else
		{
			return Kick(playerid);
		}
	}
	
	#if defined _ALS_Kick
		#undef Kick
	#else
		
		native BAD_Kick(playerid) = Kick;
		
		#define _ALS_Kick
	#endif
	#define Kick FIXES_Kick
#endif

/*
 * FIXES_IsPAttachedObjectSlotUsed(playerid, index)
 *
 * FIXES:
 *     IsPlayerAttachedObjectSlotUsed
 */
#if FIX_IsPlayerAttachedObjSlotUsed
	stock FIXES_IsPAttachedObjectSlotUsed(playerid, index)
	{
		if (IsPlayerConnected(playerid))
		{
			return FIXES_gsObjectSlots[playerid / _FIXES_ATTACHMENTS] & 1 << playerid % _FIXES_ATTACHMENTS * MAX_PLAYER_ATTACHED_OBJECTS + index;
		}
		return 0;
	}
	
	#if defined _ALS_IsPAttachedObjSlotUsed
		#undef IsPlayerAttachedObjectSlotUsed
	#else
		
		native BAD_IsPlayerAttachedObjSlotUsed(playerid, index) = IsPlayerAttachedObjectSlotUsed;
		
		#define _ALS_IsPAttachedObjSlotUsed
	#endif
	#define IsPlayerAttachedObjectSlotUsed FIXES_IsPAttachedObjectSlotUsed
#endif

/*
 * _FIXES_SetPlayerAttachedObject(slot, to)
 *
 * FIXES:
 *     IsPlayerAttachedObjectSlotUsed
 */
#if (FIX_IsPlayerAttachedObjSlotUsed || FIX_SetPlayerAttachedObject) && !FIXES_Single
	forward _FIXES_SetPlayerAttachedObject(slot, to);
	
	public _FIXES_SetPlayerAttachedObject(slot, to)
	{
		FIXES_gsObjectSlots[slot] = to;
	}
#endif

/*
 * FIXES_SetPlayerAttachedObject(playerid, index, modelid, bone, Float:fOffsetX = 0.0, Float:fOffsetY = 0.0, Float:fOffsetZ = 0.0, Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0, Float:fScaleX = 1.0, Float:fScaleY = 1.0, Float:fScaleZ = 1.0)
 *
 * FIXES:
 *     IsPlayerAttachedObjectSlotUsed
 *     SetPlayerAttachedObject
 */
#if FIX_IsPlayerAttachedObjSlotUsed || FIX_SetPlayerAttachedObject
	stock FIXES_SetPlayerAttachedObject(playerid, index, modelid, bone, Float:fOffsetX = 0.0, Float:fOffsetY = 0.0, Float:fOffsetZ = 0.0, Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0, Float:fScaleX = 1.0, Float:fScaleY = 1.0, Float:fScaleZ = 1.0, materialcolor1 = 0, materialcolor2 = 0)
	{
		if (SetPlayerAttachedObject(playerid, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, materialcolor1, materialcolor2))
		{
			#if FIXES_Single
				FIXES_gsObjectSlots[playerid / _FIXES_ATTACHMENTS] |= (1 << playerid % _FIXES_ATTACHMENTS * MAX_PLAYER_ATTACHED_OBJECTS + index);
			#else
				new
					slot = playerid / _FIXES_ATTACHMENTS;
				CallRemoteFunction(FIXES_gscSetPlayerAttachedObj, FIXES_gscSpec@ii, slot, FIXES_gsObjectSlots[slot] | (1 << playerid % _FIXES_ATTACHMENTS * MAX_PLAYER_ATTACHED_OBJECTS + index));
			#endif
			return 1;
		}
		return 0;
	}
	
	#if defined _ALS_SetPlayerAttachedObject
		#undef SetPlayerAttachedObject
	#else
		
		native BAD_SetPlayerAttachedObject(playerid, index, modelid, bone, Float:fOffsetX = 0.0, Float:fOffsetY = 0.0, Float:fOffsetZ = 0.0, Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0, Float:fScaleX = 1.0, Float:fScaleY = 1.0, Float:fScaleZ = 1.0, materialcolor1 = 0, materialcolor2 = 0) = SetPlayerAttachedObject;
		
		#define _ALS_SetPlayerAttachedObject
	#endif
	#define SetPlayerAttachedObject FIXES_SetPlayerAttachedObject
#endif

/*
 * FIXES_RemovePlayerAttachedObj(playerid, index)
 *
 * FIXES:
 *     IsPlayerAttachedObjectSlotUsed
 */
#if FIX_IsPlayerAttachedObjSlotUsed || FIX_SetPlayerAttachedObject
	stock FIXES_RemovePlayerAttachedObj(playerid, index)
	{
		if (RemovePlayerAttachedObject(playerid, index))
		{
			#if FIXES_Single
				FIXES_gsObjectSlots[playerid / _FIXES_ATTACHMENTS] &= ~(1 << playerid % _FIXES_ATTACHMENTS * MAX_PLAYER_ATTACHED_OBJECTS + index);
			#else
				new
					slot = playerid / _FIXES_ATTACHMENTS;
				CallRemoteFunction(FIXES_gscSetPlayerAttachedObj, FIXES_gscSpec@ii, slot, FIXES_gsObjectSlots[slot] & ~(1 << playerid % _FIXES_ATTACHMENTS * MAX_PLAYER_ATTACHED_OBJECTS + index));
			#endif
			return 1;
		}
		return 0;
	}
	
	#if defined _ALS_RemovePlayerAttachedObject
		#undef RemovePlayerAttachedObject
	#else
		
		native BAD_RemovePlayerAttachedObject(playerid, index) = RemovePlayerAttachedObject;
		
		#define _ALS_RemovePlayerAttachedObject
	#endif
	#define RemovePlayerAttachedObject FIXES_RemovePlayerAttachedObj
#endif

/*
 * FIXES_%%%!!!
 *
 * FIXES:
 *     %%%
 */
/*#if FIX_%%%
	stock FIXES_%%%!!!
	{
		return 0;
	}
	
	#if defined _ALS_%%%
		#undef %%%
	#else
		
		native BAD_%%%!!! = %%%;
		
		#define _ALS_%%%
	#endif
	#define %%% FIXES_%%%
#endif
*/

/*
 * _FIXES_DetermineOrder()
 *
 * Figure out which the first filterscript to be called is so that it can do the
 * majority of the work.  More detail:  Serveral pieces of code for some fixes
 * rely on things like blocking "OnPlayerUpdate".  This should be done in the
 * first script in which "OnPlayerUpdate" is called only, so we need to find out
 * in advance which script will be called first (at least out of all the fixed
 * scripts).
 */
#if !FIXES_Single
	public _FIXES_DetermineOrder()
	{
		// TODO: Graceful handoff.  I thought I was past all this rubbish!
		if (!_FIXES_gIsFilterscript)
		{
			/*if (!existproperty(5, FIXES_gscNoGMProperty))
			{
				// Either this is a Filter Script (1) and we don't want Game
				// Modes (1) or this isn't a filterscript (0) and we do want
				// Game Modes (0).  All other cases return here due to a logic
				// mismatch.  This is to rectify the difference in call orders
				// between "CallRemoteFunction" and normal callbacks.
				return 0;
			}
		}
		else
		{*/
			if (existproperty(5, FIXES_gscNoGMProperty))
			{
				// Either this is a Filter Script (1) and we don't want Game
				// Modes (1) or this isn't a filterscript (0) and we do want
				// Game Modes (0).  All other cases return here due to a logic
				// mismatch.  This is to rectify the difference in call orders
				// between "CallRemoteFunction" and normal callbacks.
				// Now DOESN'T end on the second time round for filterscripts to
				// correctly pass on the data to GameModes.
				return 0;
			}
			// Make sure certain data is synced with what the GM thinks it is.
			// =============================
			//  START: AllowInteriorWeapons 
			// =============================
			#if FIX_AllowInteriorWeapons
				CallRemoteFunction(FIXES_gscAllowInteriorWeapons, FIXES_gscSpec@i, !(FIXES_gsSettings & e_FIXES_SETTINGS_INTERIOR));
			#endif
			// =============================
			//  START: AllowInteriorWeapons 
			// =============================
			
			// ================================
			//  START: SetPlayerAttachedObject 
			// ================================
			#if FIX_IsPlayerAttachedObjSlotUsed || FIX_SetPlayerAttachedObject
				for (new i = 0; i != _FIXES_ATTACHMENTS; ++i)
				{
					CallRemoteFunction(FIXES_gscSetPlayerAttachedObj, FIXES_gscSpec@ii, i, FIXES_gsObjectSlots[i]);
				}
			#endif
			// ==============================
			//  END: SetPlayerAttachedObject 
			// ==============================
		}
		if (existproperty(5, FIXES_gscOrderProperty))
		{
			if (!existproperty(5, FIXES_gscNoGMProperty) && _FIXES_gIsFilterscript == bool:getproperty(5, FIXES_gscOrderProperty))
			{
				// The game mode is not in charge, which means we are checking
				// the filterscripts a second time and shouldn't be.
				return 0;
			}
			// If this script was previously the owner, and we are not ending
			// the game mode (in which case discard all data), and if we are
			// only dealing with filterscripts or the gamemode is now the
			// master.
			if (FIXES_gsSettings & (e_FIXES_SETTINGS_IN_CHARGE | e_FIXES_SETTINGS_DROP_ALL_DATA) == e_FIXES_SETTINGS_IN_CHARGE)
			{
				FIXES_PRINTF("_FIXES_DetermineOrder: Was in charge");
				// This script is currently in charge, but a new script has
				// usurped it!  Pass all relevant data over to the new script.
				// Also, this wasn't triggered by a game mode change (where we
				// just want to dump and reset all data).  There is no need to
				// reset the admin teleport data as that is always handled by
				// the Game Mode, so it will either be correct, or it will be
				// blank.
				FIXES_gsSettings &= ~e_FIXES_SETTINGS_IN_CHARGE;
				#if FIX_SetPlayerWorldBounds || FIX_TogglePlayerControllable
					for (new i = 0; i != MAX_PLAYERS; ++i)
					{
						if (IsPlayerConnected(i))
						{
							// =============================
							//  START: SetPlayerWorldBounds 
							// =============================
							#if FIX_SetPlayerWorldBounds
								//if (FIXES_gsPlayerBools[i] & e_FIXES_BOOLS_WORLDBOUNDS)
								//{
								// I realised that you could have the GM in
								// charge, set their bounds, load an FS, remove
								// their bounds then unload the FS again and it
								// would result in the old GM setting of them
								// HAVING bounds being re-applied, so the check
								// was removed and.
								CallRemoteFunction(FIXES_gscSetPlayerWorldBounds, FIXES_gscSpec@iffff, i, FIXES_gsWorldbounds[i][E_FIXES_WORLDBOUND_DATA_UX], FIXES_gsWorldbounds[i][E_FIXES_WORLDBOUND_DATA_LX], FIXES_gsWorldbounds[i][E_FIXES_WORLDBOUND_DATA_UY], FIXES_gsWorldbounds[i][E_FIXES_WORLDBOUND_DATA_LY]);
								//}
							#endif
							// =============================
							//  END:   SetPlayerWorldBounds 
							// =============================
							
							// =================================
							//  START: TogglePlayerControllable 
							// =================================
							#if FIX_TogglePlayerControllable
								CallRemoteFunction(FIXES_gscTogglePlayerControl, FIXES_gscSpec@ii, i, !(FIXES_gsPlayerBools[i] & e_FIXES_BOOLS_UNCONTROLLABLE));
							#endif
							// =================================
							//  END:   TogglePlayerControllable 
							// =================================
							
							// ===========================
							//  START: PutPlayerInVehicle 
							// ===========================
							#if FIX_PutPlayerInVehicle
								if (FIXES_gsPlayerBools[i] & e_FIXES_BOOLS_PUT_IN_VEHICLE)
								{
									CallRemoteFunction(FIXES_gscPutPlayerInVehicle, FIXES_gscSpec@iii, i, FIXES_gsVehicleSeatData[i] & 0x00FFFFFF, FIXES_gsVehicleSeatData[i] >>> 24);
								}
							#endif
							// ===========================
							//  END:   PutPlayerInVehicle 
							// ===========================
						}
					}
				#endif
				FIXES_PRINTF("_FIXES_DetermineOrder: Not in charge");
				return 0;
			}
			else
			{
				FIXES_gsSettings &= ~e_FIXES_SETTINGS_IN_CHARGE;
				FIXES_PRINTF("_FIXES_DetermineOrder: Not in charge");
				return 0;
			}
		}
		else if (!(FIXES_gsSettings & e_FIXES_SETTINGS_ENDING))
		{
			setproperty(5, FIXES_gscOrderProperty, _FIXES_gIsFilterscript);
			#if FIXES_Debug
				if (FIXES_gsSettings & e_FIXES_SETTINGS_IN_CHARGE)
				{
					FIXES_PRINTF("_FIXES_DetermineOrder: Already in charge");
				}
			#endif
			FIXES_gsSettings |= e_FIXES_SETTINGS_IN_CHARGE;
			FIXES_PRINTF("_FIXES_DetermineOrder: Now in charge");
			return 1;
		}
		#if FIXES_Debug
			else
			{
				FIXES_PRINTF("_FIXES_DetermineOrder: Ending");
			}
		#endif
		return 0;
	}
#endif

/*
 * FIXES_strins(string[], const substr[], pos, maxlength = sizeof string)
 *
 * FIXES:
 *     strins
 */
#if FIX_strins
	stock FIXES_strins(string[], const substr[], pos, maxlength = sizeof string)
	{
		if (string[0] > 255)
		{
			new
				strlength = strlen(string),
				sublength = strlen(substr),
				m4 = maxlength * 4;
			// Packed - format doesn't like these strings.
			if (strlength + sublength >= m4)
			{
				if (pos + sublength >= m4)
				{
					return
						string{pos} = '\0',
						// Hopefully this doesn't ignore maxlength and does packed.
						strcat(string, substr, maxlength);
				}
				else
				{
					// pos + sublength is less than maxlength, so this sum MUST
					// be positive and gte than "pos", so there's no need for
					// additional checks.
					string{maxlength - sublength - 1} = '\0';
				}
			}
			return strins(string, substr, pos, maxlength);
		}
		else if (substr[0] > 255)
		{
			new
				strlength = strlen(string),
				sublength = strlen(substr);
			// Packed - format doesn't like these strings.
			if (strlength + sublength >= maxlength)
			{
				if (pos + sublength >= maxlength)
				{
					return
						string[pos] = '\0',
						// Hopefully this doesn't ignore maxlength and does packed.
						strcat(string, substr, maxlength);
				}
				else
				{
					// pos + sublength is less than maxlength, so this sum MUST
					// be positive and gte than "pos", so there's no need for
					// additional checks.
					string[maxlength - sublength - 1] = '\0';
				}
			}
			return strins(string, substr, pos, maxlength);
		}
		else
		{
			return format(string, maxlength, "%.*s%s%s", pos, string, substr, string[pos]);
		}
	}
	
	#if defined _ALS_strins
		#undef strins
	#else
		
		native BAD_strins(string[], const substr[], pos, maxlength = sizeof string) = strins;
		
		#define _ALS_strins
	#endif
	#define strins FIXES_strins
#endif

/*
 * FIXES_random(max)
 *
 * FIXES:
 *     random
 */
#if FIX_random
	stock FIXES_random(max)
	{
		if (max < 0)
		{
			return -random(-max);
		}
		else
		{
			return random(max);
		}
	}
	
	#if defined _ALS_random
		#undef random
	#else
		
		native BAD_random(max) = random;
		
		#define _ALS_random
	#endif
	#define random FIXES_random
#endif

/*
 * FIXES_sleep(const time)
 *
 * FIXES:
 *     sleep
 */
#if FIX_sleep
	stock FIXES_sleep(ms)
	{
		// Call a native function that does very little, but saves the current
		// heap pointer.  Then return to save the accurate stack pointer.
		return heapspace(), ms;
	}
	
	#if defined _ALS_sleep
		#undef sleep
	#else
		
		// Uses a little trick to consume part of the line and thus not match
		// our hooked version.
		#define BAD_sleep%0\n%9 sleep%0
		
		#define _ALS_sleep
	#endif
	
	#define sleep%0\n%9 sleep FIXES_sleep(%0)
	// This fixes another BIZZARE bug.  Just doing:
	//  
	//  #define FIXES_sleep(%0;) FIXES_sleep(%0)
	//  
	// Results in:
	//  
	//  FIXES_sleep(n));
	//  
	// Which clearly it shouldn't.  I've stepped through the compilation and that
	// extra bracket comes from nowhere!
	#define FIXES_sleep(%0;) FIXES_sleep _FIXES_SLEEP_BRACKET %0);
	#define _FIXES_SLEEP_BRACKET (
#endif

#undef _FIXES_CEILDIV
#undef _FIXES_INFINITY
#undef _FIXES_N_INFINITY
#undef _FIXES_ATTACHMENTS
#undef _FIXES_IS_UNSET
#undef FIXES_PRINTF
