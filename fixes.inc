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
 * E_FIXES_CALLBACK_HOOKS_1
 * E_FIXES_CALLBACK_HOOKS_2
 * 
 * Two enums to define the bits used to efficiently store wether of not the next
 * callback in the ALS chain exists.  Breaks naming convention for elements from
 * "E_FIXES_ON_GAME_MODE_INIT" to "E_FIXES_OnGameModeInit" for compatibility
 * with existing names.  Note that "Checkpoint" and "Update" have been shortened
 * to "CP" and "Upd" in certain symbols to stay below the 31 character limit.
 */
enum E_FIXES_CALLBACK_HOOKS_1 (<<= 1)
{
	E_FIXES_OnGameModeInit = 1,
	E_FIXES_OnGameModeExit,
	E_FIXES_OnFilterScriptInit,
	E_FIXES_OnFilterScriptExit,
	E_FIXES_OnPlayerConnect,
	E_FIXES_OnPlayerDisconnect,
	E_FIXES_OnPlayerSpawn,
	E_FIXES_OnPlayerDeath,
	E_FIXES_OnVehicleSpawn,
	E_FIXES_OnVehicleDeath,
	E_FIXES_OnPlayerText,
	E_FIXES_OnPlayerCommandText,
	E_FIXES_OnPlayerRequestClass,
	E_FIXES_OnPlayerEnterVehicle,
	E_FIXES_OnPlayerExitVehicle,
	E_FIXES_OnPlayerStateChange,
	E_FIXES_OnPlayerEnterCheckpoint,
	E_FIXES_OnPlayerLeaveCheckpoint,
	E_FIXES_OnPlayerEnterRaceCP,
	E_FIXES_OnPlayerLeaveRaceCP,
	E_FIXES_OnRconCommand,
	E_FIXES_OnPlayerRequestSpawn,
	E_FIXES_OnObjectMoved,
	E_FIXES_OnPlayerObjectMoved,
	E_FIXES_OnPlayerPickUpPickup,
	E_FIXES_OnVehicleMod,
	E_FIXES_OnEnterExitModShop,
	E_FIXES_OnVehiclePaintjob,
	E_FIXES_OnVehicleRespray,
	E_FIXES_OnVehicleDamageStatusUp,
	E_FIXES_OnPlayerSelectedMenuRow,
	E_FIXES_OnPlayerExitedMenu
}

enum E_FIXES_CALLBACK_HOOKS_2 (<<= 1)
{
	E_FIXES_OnPlayerInteriorChange = 1,
	E_FIXES_OnPlayerKeyStateChange,
	E_FIXES_OnRconLoginAttempt,
	E_FIXES_OnPlayerUpdate,
	E_FIXES_OnPlayerStreamIn,
	E_FIXES_OnPlayerStreamOut,
	E_FIXES_OnVehicleStreamIn,
	E_FIXES_OnVehicleStreamOut,
	E_FIXES_OnDialogResponse,
	E_FIXES_OnPlayerClickPlayer,
	E_FIXES_OnPlayerClickMap,
	E_FIXES_OnPlayerClickTextDraw,
	E_FIXES_OnPlayerClickPlayerTD,
	E_FIXES_OnPlayerEditObject,
	E_FIXES_OnPlayerEditAttachedObj,
	E_FIXES_OnPlayerSelectObject,
	E_FIXES_OnPlayerTakeDamage,
	E_FIXES_OnPlayerGiveDamage
}

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
	 * E_FIXES_CALLBACK_HOOKS_1:FIXES_gsCallbackHooks1
	 * E_FIXES_CALLBACK_HOOKS_1:FIXES_gsCallbackHooks2
	 * 
	 * Bit arrays of callbacks.  You can only have 32 callbacks per variable,
	 * and there are more than that many, so we need more than one variable.
	 * Add new callback detection to "FIXES_ScriptInit" - only actually used
	 * callbacks are currently hooked.
	 */
	E_FIXES_CALLBACK_HOOKS_1:FIXES_gsCallbackHooks1,
	E_FIXES_CALLBACK_HOOKS_2:FIXES_gsCallbackHooks2,
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
	FIXES_gsLastAnimation[MAX_PLAYERS];

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
	FIXES_gscReturnProperty[] = "FIXES_gscReturnProperty";

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
 * FIXES_DEFINE_STRING(callback)
 * 
 * Define strings for every callback name.  This macro creates "static stock
 * const" strings for every next callback name (i.e. the ones called to continue
 * the chain after "fixes.inc" is done.  This is done this way to only need to
 * include every callback name ONCE in the compiled ".amx" file, the old method
 * had multiple copies of the same string literal in the final code.
 */
#define FIXES_DEFINE_STRING(%0On%1) static stock const FIXES_gsc%1[] = "FIXES_On"#%1

FIXES_DEFINE_STRING(OnGameModeInit);
FIXES_DEFINE_STRING(OnGameModeExit);
FIXES_DEFINE_STRING(OnFilterScriptInit);
FIXES_DEFINE_STRING(OnFilterScriptExit);
FIXES_DEFINE_STRING(OnPlayerConnect);
FIXES_DEFINE_STRING(OnPlayerDisconnect);
FIXES_DEFINE_STRING(OnPlayerSpawn);
FIXES_DEFINE_STRING(OnPlayerDeath);
FIXES_DEFINE_STRING(OnVehicleSpawn);
FIXES_DEFINE_STRING(OnVehicleDeath);
FIXES_DEFINE_STRING(OnPlayerText);
FIXES_DEFINE_STRING(OnPlayerCommandText);
FIXES_DEFINE_STRING(OnPlayerRequestClass);
FIXES_DEFINE_STRING(OnPlayerEnterVehicle);
FIXES_DEFINE_STRING(OnPlayerExitVehicle);
FIXES_DEFINE_STRING(OnPlayerStateChange);
FIXES_DEFINE_STRING(OnPlayerEnterCheckpoint);
FIXES_DEFINE_STRING(OnPlayerLeaveCheckpoint);
FIXES_DEFINE_STRING(OnPlayerEnterRaceCP);
FIXES_DEFINE_STRING(OnPlayerLeaveRaceCP);
FIXES_DEFINE_STRING(OnRconCommand);
FIXES_DEFINE_STRING(OnPlayerRequestSpawn);
FIXES_DEFINE_STRING(OnObjectMoved);
FIXES_DEFINE_STRING(OnPlayerObjectMoved);
FIXES_DEFINE_STRING(OnPlayerPickUpPickup);
FIXES_DEFINE_STRING(OnVehicleMod);
FIXES_DEFINE_STRING(OnEnterExitModShop);
FIXES_DEFINE_STRING(OnVehiclePaintjob);
FIXES_DEFINE_STRING(OnVehicleRespray);
FIXES_DEFINE_STRING(OnVehicleDamageStatusUp);
FIXES_DEFINE_STRING(OnPlayerSelectedMenuRow);
FIXES_DEFINE_STRING(OnPlayerExitedMenu);
FIXES_DEFINE_STRING(OnPlayerInteriorChange);
FIXES_DEFINE_STRING(OnPlayerKeyStateChange);
FIXES_DEFINE_STRING(OnRconLoginAttempt);
FIXES_DEFINE_STRING(OnPlayerUpdate);
FIXES_DEFINE_STRING(OnPlayerStreamIn);
FIXES_DEFINE_STRING(OnPlayerStreamOut);
FIXES_DEFINE_STRING(OnVehicleStreamIn);
FIXES_DEFINE_STRING(OnVehicleStreamOut);
FIXES_DEFINE_STRING(OnDialogResponse);
FIXES_DEFINE_STRING(OnPlayerClickPlayer);
FIXES_DEFINE_STRING(OnPlayerClickMap);
FIXES_DEFINE_STRING(OnPlayerClickTextDraw);
FIXES_DEFINE_STRING(OnPlayerClickPlayerTD);
FIXES_DEFINE_STRING(OnPlayerEditObject);
FIXES_DEFINE_STRING(OnPlayerEditAttachedObj);
FIXES_DEFINE_STRING(OnPlayerSelectObject);
FIXES_DEFINE_STRING(OnPlayerTakeDamage);
FIXES_DEFINE_STRING(OnPlayerGiveDamage);

#undef FIXES_DEFINE_STRING

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
 * FIXES_DETECT_CALLBACK_1(callback)
 * FIXES_DETECT_CALLBACK_2(callback)
 * 
 * Macro to make detecting callbacks simpler.  The number relates to which
 * variable the callback is found it.  This explicity detects the "On" part of
 * the callback because some scripts redefine the callback names and we need to
 * always correctly detect them, and always have "FIXES_On"#%0 work without
 * using the redefined name (e.g. if a prior script uses ALS).
 */
#define FIXES_DETECT_CALLBACK_1(%0On%1) (FIXES_gsCallbackHooks1|=E_FIXES_On%1*E_FIXES_CALLBACK_HOOKS_1:(funcidx(FIXES_gsc%1)!=-1))
#define FIXES_DETECT_CALLBACK_2(%0On%1) (FIXES_gsCallbackHooks2|=E_FIXES_On%1*E_FIXES_CALLBACK_HOOKS_2:(funcidx(FIXES_gsc%1)!=-1))

/* 
 * FIXES_CALL_CALLBACK_1(callback, default, format[], ...)
 * FIXES_CALL_CALLBACK_2(callback, default, format[], ...)
 * 
 * Macro to make calling callbacks simpler.  This takes the name of a callback
 * to chain - if it exists then it is called, if it doesn't exist the default
 * is returned.  Note that this DOES NOT end the current function, use in
 * conjunction with "return", or store the value to call the next element in the
 * chain before some bits of processing.
 */
#define FIXES_CALL_CALLBACK_1(%0On%1,%2,%3) ((FIXES_gsCallbackHooks1&E_FIXES_On%1)?(CallLocalFunction(FIXES_gsc%1,%3)):(%2))
#define FIXES_CALL_CALLBACK_2(%0On%1,%2,%3) ((FIXES_gsCallbackHooks2&E_FIXES_On%1)?(CallLocalFunction(FIXES_gsc%1,%3)):(%2))

/* 
 * FIXES_DetermineOrder()
 * 
 * Figure out which script is called first by callbacks.
 */
#if !FIXES_Single
	forward _FIXES_DetermineOrder();
	
	static FIXES_DetermineOrder()
	{
		deleteproperty(5, FIXES_gscOrderProperty);
		// Called in the Game Mode first (thus needs correcting).
		setproperty(5, FIXES_gscNoGMProperty, 1);
		CallRemoteFunction(FIXES_gscDetermineOrder, FIXES_gscSpec@);
		deleteproperty(5, FIXES_gscNoGMProperty);
		//if (!existproperty(5, FIXES_gscOrderProperty))
		//{
		CallRemoteFunction(FIXES_gscDetermineOrder, FIXES_gscSpec@);
		//}
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
 * FIXES_OnScriptInit()
 * 
 * Do all initialisation code in here.  Is called once when the script starts,
 * regardless of HOW the script is started (FilterScript or GameMode).  Add
 * detection of new callbacks here.
 * 
 * FIXES:
 */
static FIXES_OnScriptInit()
{
	#if !FIXES_Single
		FIXES_DetermineOrder();
	#endif
	// Called in the Game Mode first.
	FIXES_DETECT_CALLBACK_1(OnGameModeInit);
	#if !FIXES_Single
		FIXES_DETECT_CALLBACK_1(OnGameModeExit);
	#endif
	FIXES_DETECT_CALLBACK_1(OnFilterScriptInit);
	#if !FIXES_Single
		FIXES_DETECT_CALLBACK_1(OnFilterScriptExit);
	#endif
	#if FIX_SetPlayerWorldBounds || FIX_TogglePlayerControllable || FIX_SetPlayerName || FIX_GetPlayerColor || FIX_GetPlayerSkin || FIX_IsPlayerInCheckpoint || FIX_IsPlayerInRaceCheckpoint || FIX_GetPlayerWeapon || FIX_PutPlayerInVehicle || FIX_OnPlayerEnterVehicle || FIX_AllowTeleport || FIX_OnDialogResponse || FIX_GetPlayerDialog || FIX_SetSpawnInfo || FIX_AllowInteriorWeapons || FIX_TrainExit || FIX_Kick
		// Not called after "loadfs" or "reloadfs" (useful for us).
		FIXES_DETECT_CALLBACK_1(OnPlayerConnect);
	#endif
	#if FIX_SetPlayerAttachedObject || FIX_IsPlayerAttachedObjSlotUsed || FIX_Kick || (FIXES_SilentKick && (FIX_OnVehicleMod || FIX_OnPlayerEnterVehicle))
		// Called in the Game Mode first when the mode changes, in Filter
		// Scripts when the player leaves.
		FIXES_DETECT_CALLBACK_1(OnPlayerDisconnect);
	#endif
	#if FIX_GetPlayerSkin || FIX_TogglePlayerControllable
		FIXES_DETECT_CALLBACK_1(OnPlayerSpawn);
	#endif
	#if FIX_SetPlayerWorldBounds || FIX_TogglePlayerControllable || FIX_AllowInteriorWeapons || FIX_OnPlayerEnterVehicle || FIX_OnPlayerDeath || FIX_OnVehicleMod
		FIXES_DETECT_CALLBACK_2(OnPlayerUpdate);
	#endif
	#if FIX_HydraSniper || FIX_GetPlayerWeapon || FIX_PutPlayerInVehicle || FIX_OnPlayerEnterVehicle || FIX_TrainExit
		FIXES_DETECT_CALLBACK_1(OnPlayerStateChange);
	#endif
	#if FIX_AllowTeleport && !defined FILTERSCRIPT
		// Called in the Game Mode first.
		FIXES_DETECT_CALLBACK_2(OnPlayerClickMap);
	#endif
	#if FIX_OnDialogResponse || FIX_GetPlayerDialog
		FIXES_DETECT_CALLBACK_2(OnDialogResponse);
	#endif
	#if FIX_OnPlayerDeath
		FIXES_DETECT_CALLBACK_1(OnPlayerDeath);
	#endif
	#if FIX_AllowInteriorWeapons
		FIXES_DETECT_CALLBACK_2(OnPlayerInteriorChange);
	#endif
	#if FIX_OnPlayerCommandText
		FIXES_DETECT_CALLBACK_1(OnPlayerCommandText);
	#endif
	#if FIX_OnVehicleMod
		FIXES_DETECT_CALLBACK_1(OnVehicleMod);
	#endif
}

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
	FIXES_OnScriptInit();
	#if !FIXES_Single
		FIXES_gsSettings &= ~e_FIXES_SETTINGS_DROP_ALL_DATA;
	#endif
	return FIXES_CALL_CALLBACK_1(OnFilterScriptInit, 1, FIXES_gscSpec@);
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit FIXES_OnFilterScriptInit

forward OnFilterScriptInit();

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
	
	if (!_FIXES_gIsFilterscript)
	{
		FIXES_OnScriptInit();
	}
	
	#if !FIXES_Single
		FIXES_gsSettings &= ~e_FIXES_SETTINGS_DROP_ALL_DATA;
	#endif
	
	return FIXES_CALL_CALLBACK_1(OnGameModeInit, 1, FIXES_gscSpec@);
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit FIXES_OnGameModeInit

forward OnGameModeInit();

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
			FIXES_gsSettings |= e_FIXES_SETTINGS_ENDING;
			FIXES_DetermineOrder();
		}
		return FIXES_CALL_CALLBACK_1(OnGameModeExit, 1, FIXES_gscSpec@);
	}
	
	#if defined _ALS_OnGameModeExit
		#undef OnGameModeExit
	#else
		#define _ALS_OnGameModeExit
	#endif
	#define OnGameModeExit FIXES_OnGameModeExit
	
	forward OnGameModeExit();
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
			FIXES_gsSettings |= e_FIXES_SETTINGS_ENDING;
			FIXES_DetermineOrder();
		}
		return FIXES_CALL_CALLBACK_1(OnFilterScriptExit, 1, FIXES_gscSpec@);
	}
	
	#if defined _ALS_OnFilterScriptExit
		#undef OnFilterScriptExit
	#else
		#define _ALS_OnFilterScriptExit
	#endif
	#define OnFilterScriptExit FIXES_OnFilterScriptExit
	
	forward OnFilterScriptExit();
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
			if (cmdtext[0] == '\0' || (cmdtext[0] == '\1' && cmdtext[1] == '\0'))
			{
				return FIXES_CALL_CALLBACK_1(OnPlayerCommandText, 1, FIXES_gscSpec@is, playerid, FIXES_gscNULL);
			}
			else
			{
				return FIXES_CALL_CALLBACK_1(OnPlayerCommandText, 1, FIXES_gscSpec@is, playerid, cmdtext);
			}
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
	
	forward OnPlayerCommandText(playerid, cmdtext[]);
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
#if FIX_SetPlayerWorldBounds || FIX_TogglePlayerControllable || FIX_SetPlayerName || FIX_GetPlayerColor || FIX_GetPlayerSkin || FIX_IsPlayerInCheckpoint || FIX_IsPlayerInRaceCheckpoint || FIX_GetPlayerWeapon || FIX_PutPlayerInVehicle || FIX_OnPlayerEnterVehicle || FIX_AllowTeleport || FIX_OnDialogResponse || FIX_GetPlayerDialog || FIX_SetSpawnInfo || FIX_AllowInteriorWeapons || FIX_TrainExit || FIX_Kick
	public OnPlayerConnect(playerid)
	{
		FIXES_PRINTF("FIXES_OnPlayerConnect: %d", playerid);
		#if FIX_SetPlayerWorldBounds || FIX_TogglePlayerControllable || FIX_PutPlayerInVehicle || FIX_OnPlayerEnterVehicle || FIX_AllowTeleport || FIX_AllowInteriorWeapons || FIX_TrainExit
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
			new
				ret = FIXES_CALL_CALLBACK_1(OnPlayerConnect, 1, FIXES_gscSpec@i, playerid);
			FIXES_gsPlayerBools[playerid] &= ~e_FIXES_BOOLS_ON_PLAYER_CONNECT;
			return ret;
		#else
			return FIXES_CALL_CALLBACK_1(OnPlayerConnect, 1, FIXES_gscSpec@i, playerid);
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
	
	forward OnPlayerConnect(playerid);
#endif

/* 
 * OnPlayerDisonnect(playerid, reason)
 * 
 * FIXES:
 *     SetPlayerAttachedObject
 *     IsPlayerAttachedObjectSlotUsed
 *     Kick
 */
#if FIX_SetPlayerAttachedObject || FIX_IsPlayerAttachedObjSlotUsed || FIX_Kick || (FIXES_SilentKick && (FIX_OnVehicleMod || FIX_OnPlayerEnterVehicle))
	public OnPlayerDisconnect(playerid, reason)
	{
		new
			ret = FIXES_CALL_CALLBACK_1(OnPlayerDisconnect, 1, FIXES_gscSpec@ii, playerid, reason);
		
		// ==========================
		//  START: FIXES_SilentKick 
		// ==========================
		#if FIXES_SilentKick && (FIX_OnVehicleMod || FIX_OnPlayerEnterVehicle)
			new
				shift = FIXES_gsPlayerIP[playerid];
			if (shift != -1)
			{
				// Unban the IP (timed out).
				new
					ip[16];
				format(ip, sizeof (ip), "unbanip %d.%d.%d.%d", shift >>> 24, (shift >>> 16) & 0xFF, (shift >>> 8) & 0xFF, shift & 0xFF);
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
			#if !(FIXES_SilentKick && (FIX_OnVehicleMod || FIX_OnPlayerEnterVehicle))
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
		
		return ret;
	}
	
	#if defined _ALS_OnPlayerDisconnect
		#undef OnPlayerDisconnect
	#else
		#define _ALS_OnPlayerDisconnect
	#endif
	#define OnPlayerDisconnect FIXES_OnPlayerDisconnect
	
	forward OnPlayerDisconnect(playerid, reason);
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
					if (!strcmp(sAnimlib, "PED", true))
					{
						ClearAnimations(playerid);
					}
				#endif
				// ======================
				//  END:   OnPlayerDeath 
				// ======================
			}
		return FIXES_CALL_CALLBACK_1(OnPlayerDeath, 1, FIXES_gscSpec@iii, playerid, killerid, reason);
	}
	
	#if defined _ALS_OnPlayerDeath
		#undef OnPlayerDeath
	#else
		#define _ALS_OnPlayerDeath
	#endif
	#define OnPlayerDeath FIXES_OnPlayerDeath
	
	forward OnPlayerDeath(playerid, killerid, reason);
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
			GetVehiclePos(vid, x, y, z);
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
		if (strcmp(name, FIXES_gscTempName) == 0)
		{
			return 0;
		}
		static
			sOldName[MAX_PLAYER_NAME];
		GetPlayerName(playerid, sOldName, sizeof (sOldName));
		if (strcmp(name, sOldName, true) == 0)
		{
			return 0;
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
		
		return FIXES_CALL_CALLBACK_1(OnPlayerSpawn, 1, FIXES_gscSpec@i, playerid);
	}
	
	#if defined _ALS_OnPlayerSpawn
		#undef OnPlayerSpawn
	#else
		#define _ALS_OnPlayerSpawn
	#endif
	#define OnPlayerSpawn FIXES_OnPlayerSpawn
	
	forward OnPlayerSpawn(playerid);
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
				return FIXES_CALL_CALLBACK_1(OnVehicleMod, 1, FIXES_gscSpec@iii, playerid, vehicleid, componentid);
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
						return FIXES_CALL_CALLBACK_1(OnVehicleMod, 1, FIXES_gscSpec@iii, playerid, vehicleid, componentid);
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
						return FIXES_CALL_CALLBACK_1(OnVehicleMod, 1, FIXES_gscSpec@iii, playerid, vehicleid, componentid);
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
	
	forward OnVehicleMod(playerid, vehicleid, componentid);
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
				weapon[0] = 0;
				strcat(weapon, "Molotov Cocktail", len);
				return 1;
			}
			case 44:
			{
				weapon[0] = 0;
				strcat(weapon, "Thermal Goggles", len);
				return 1;
			}
			case 45:
			{
				weapon[0] = 0;
				strcat(weapon, "Night Vision Goggles", len);
				return 1;
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
 */
#if FIX_SetPlayerWorldBounds || FIX_TogglePlayerControllable || FIX_AllowInteriorWeapons || FIX_OnPlayerEnterVehicle || FIX_OnPlayerDeath || FIX_Kick || FIX_OnVehicleMod
	public OnPlayerUpdate(playerid)
	{
		// =============================
		//  BEGIN: OnPlayerEnterVehicle 
		// =============================
		#if FIX_OnPlayerEnterVehicle || FIX_Kick || FIX_OnVehicleMod
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
				return FIXES_CALL_CALLBACK_2(OnPlayerUpdate, 1, FIXES_gscSpec@i, playerid);
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
					FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PX] = x;
					FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PY] = y;
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
				playerid = FIXES_CALL_CALLBACK_2(OnPlayerUpdate, 1, FIXES_gscSpec@i, playerid);
				if (keys || ud || lr)
				{
					return 0;
				}
				else
				{
					return playerid;
				}
			}
		#endif
		// =================================
		//  END:   TogglePlayerControllable 
		// =================================
		
		return FIXES_CALL_CALLBACK_2(OnPlayerUpdate, 1, FIXES_gscSpec@i, playerid);
	}
	
	#if defined _ALS_OnPlayerUpdate
		#undef OnPlayerUpdate
	#else
		#define _ALS_OnPlayerUpdate
	#endif
	#define OnPlayerUpdate FIXES_OnPlayerUpdate
	
	forward OnPlayerUpdate(playerid);
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
					FIXES_gsPlayerBools[playerid] &= ~e_FIXES_BOOLS_WORLDBOUNDS;
					return SetPlayerWorldBounds(playerid, _FIXES_INFINITY, _FIXES_N_INFINITY, _FIXES_INFINITY, _FIXES_N_INFINITY);
				}
				// This code could do with a way to mostly remove the checks.  Maybe
				// when setting everything to FIXES_INFINITY (with default
				// parameters).
				FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_WORLDBOUNDS;
				new
					Float:tmp;
				if (x_max < x_min)
				{
					tmp = x_min;
					x_min = x_max;
					x_max = tmp;
				}
				if (y_max < y_min)
				{
					tmp = y_min;
					y_min = y_max;
					y_max = tmp;
				}
				// Give a little leway so this fix isn't noticed if you're not
				// trying to break through the world bounds.  Leway removed in
				// favour of keys.
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LX] = x_min;
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UX] = x_max;
				
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LY] = y_min;
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UY] = y_max;
				
				GetPlayerPos(playerid, tmp, tmp, tmp);
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PX] = (x_max - x_min) / 2 + x_min;
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PY] = (y_max - y_min) / 2 + y_min;
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PZ] = tmp;
				
				return SetPlayerWorldBounds(playerid, x_max, x_min, y_max, y_min);
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
				CallRemoteFunction(FIXES_gscSetPlayerWorldBounds, FIXES_gscSpec@iffff, playerid, x_max, x_min, y_max, y_min);
				return getproperty(5, FIXES_gscReturnProperty);
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
					FIXES_gsPlayerBools[playerid] &= ~e_FIXES_BOOLS_WORLDBOUNDS;
					FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LX] =
						FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UX] =
							FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LY] =
								FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UY] =
									0.0;
					setproperty(5, FIXES_gscReturnProperty, SetPlayerWorldBounds(playerid, _FIXES_INFINITY, _FIXES_N_INFINITY, _FIXES_INFINITY, _FIXES_N_INFINITY));
					return -1;
				}
				// This code could do with a way to mostly remove the checks.  Maybe
				// when setting everything to FIXES_INFINITY (with default
				// parameters).
				FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_WORLDBOUNDS;
				new
					Float:tmp;
				if (x_max < x_min)
				{
					tmp = x_min;
					x_min = x_max;
					x_max = tmp;
				}
				if (y_max < y_min)
				{
					tmp = y_min;
					y_min = y_max;
					y_max = tmp;
				}
				// Give a little leway so this fix isn't noticed if you're not
				// trying to break through the world bounds.  Leway removed in
				// favour of keys.
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LX] = x_min;
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UX] = x_max;
				
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_LY] = y_min;
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_UY] = y_max;
				
				GetPlayerPos(playerid, tmp, tmp, tmp);
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PX] = (x_max - x_min) / 2 + x_min;
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PY] = (y_max - y_min) / 2 + y_min;
				FIXES_gsWorldbounds[playerid][E_FIXES_WORLDBOUND_DATA_PZ] = tmp;
				
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
				CallRemoteFunction(FIXES_gscTogglePlayerControl, FIXES_gscSpec@ii, playerid, toggle);
				return getproperty(5, FIXES_gscReturnProperty);
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
		return FIXES_CALL_CALLBACK_2(OnPlayerInteriorChange, 1, FIXES_gscSpec@iii, playerid, newinteriorid, oldinteriorid);
	}
	
	#if defined _ALS_OnPlayerInteriorChange
		#undef OnPlayerInteriorChange
	#else
		#define _ALS_OnPlayerInteriorChange
	#endif
	#define OnPlayerInteriorChange FIXES_OnPlayerInteriorChange
	
	forward OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
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
				GetPlayerIp(playerid, ip, sizeof (ip));
				format(ip, sizeof (ip), "banip %s", ip);
				SendRconCommand(ip);
				FIXES_gsPlayerIP[playerid] = strval(ip[kick]) << 24;
				kick = strfind(ip, FIXES_gscDot, false, kick) + 1;
				FIXES_gsPlayerIP[playerid] |= strval(ip[kick]) << 16;
				kick = strfind(ip, FIXES_gscDot, false, kick) + 1;
				FIXES_gsPlayerIP[playerid] |= strval(ip[kick]) << 8;
				kick = strfind(ip, FIXES_gscDot, false, kick) + 1;
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
				return FIXES_CALL_CALLBACK_1(OnPlayerStateChange, 1, FIXES_gscSpec@iii, playerid, newstate, oldstate);
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
						SetCameraBehindPlayer(playerid);
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
						PutPlayerInVehicle(playerid, vid, FIXES_gsVehicleSeatData[playerid] >>> 24);
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
		
		return FIXES_CALL_CALLBACK_1(OnPlayerStateChange, 1, FIXES_gscSpec@iii, playerid, newstate, oldstate);
	}
	
	#if defined _ALS_OnPlayerStateChange
		#undef OnPlayerStateChange
	#else
		#define _ALS_OnPlayerStateChange
	#endif
	#define OnPlayerStateChange FIXES_OnPlayerStateChange
	
	forward OnPlayerStateChange(playerid, newstate, oldstate);
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
				vid = GivePlayerWeapon(playerid, weaponid, ammo);
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
					GetVehiclePos(vid, x, y, z);
					SetPlayerPos(playerid, x, y, z);
					FIXES_gsVehicleSeatData[playerid] = seatid << 24 | vehicleid;
					FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_PUT_IN_VEHICLE;
					return 1;
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
					GetVehiclePos(vid, x, y, z);
					SetPlayerPos(playerid, x, y, z);
					CallRemoteFunction(FIXES_gscPutPlayerInVehicle, FIXES_gscSpec@iiiii, playerid, vehicleid, seatid, 1, vid);
					return 1;
				}
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
						FIXES_gsVehicleSeatData[playerid] = seatid << 24 | vehicleid;
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
		DisablePlayerCheckpoint(playerid);
		return SetPlayerCheckpoint(playerid, x, y, z, size);
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
		DisablePlayerRaceCheckpoint(playerid);
		return SetPlayerRaceCheckpoint(playerid, type, x, y, z, nextx, nexty, nextz, size);
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
		return FIXES_CALL_CALLBACK_2(OnPlayerClickMap, 1, FIXES_gscSpec@ifff, playerid, fX, fY, fZ);
	}
	
	#if defined _ALS_OnPlayerClickMap
		#undef OnPlayerClickMap
	#else
		#define _ALS_OnPlayerClickMap
	#endif
	#define OnPlayerClickMap FIXES_OnPlayerClickMap
	
	forward OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ);
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
				CallRemoteFunction(FIXES_gscAllowTeleport, FIXES_gscSpec@ii, playerid, allow)
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
					dialogid = GetPVarInt(playerid, FIXES_pvarPlayerDialog);
					SetPVarInt(playerid, FIXES_pvarCurrentDialog, dialogid);
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
				return FIXES_CALL_CALLBACK_2(OnDialogResponse, 1, FIXES_gscSpec@iiiis, playerid, dialogid, response, listitem, inputtext);
			}
			else
			{
				return FIXES_CALL_CALLBACK_2(OnDialogResponse, 1, FIXES_gscSpec@iiiis, playerid, dialogid, response, listitem, FIXES_gscNULL);
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
	
	forward OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
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
 * FIXES_HideMenuForPlayer(Menu:menuid, playerid
 *
 * FIXES:
 *     HideMenuForPlayer
 */
#if FIX_HideMenuForPlayer
	stock FIXES_HideMenuForPlayer(Menu:menuid, playerid)
	{
		if (IsValidMenu(menuid))
		{
			return HideMenuForPlayer(menuid, playerid);
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
			format(dest, 12, "%d", value);
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
			TogglePlayerSpectating(playerid, true);
			TogglePlayerControllable(playerid, false);
			SetPVarInt(playerid, FIXES_pvarKick, SetTimerEx(FIXES_gscKick, 1000, 0, FIXES_gscSpec@i, playerid));
			FIXES_gsPlayerBools[playerid] |= e_FIXES_BOOLS_KICKED;
			return 1;
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
					string{pos} = '\0';
					// Hopefully this doesn't ignore maxlength and does packed.
					return strcat(string, substr, maxlength);
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
					string[pos] = '\0';
					// Hopefully this doesn't ignore maxlength and does packed.
					return strcat(string, substr, maxlength);
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
 * FIXES_random(const maxint)
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

#undef _FIXES_CEILDIV
#undef _FIXES_INFINITY
#undef _FIXES_N_INFINITY
#undef _FIXES_ATTACHMENTS
#undef _FIXES_IS_UNSET
#undef FIXES_DETECT_CALLBACK_1
#undef FIXES_DETECT_CALLBACK_2
#undef FIXES_CALL_CALLBACK_1
#undef FIXES_CALL_CALLBACK_2
#undef FIXES_PRINTF