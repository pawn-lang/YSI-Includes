/**
 * Copyright (c) 2013, Dan
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and\or other materials provided with the distribution. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Special thanks to:
 *	  cessil - useful anticheat tips
 *	  Slice - memset
 *	  Y_Less - very thorough research
 */

/*
This file has a VERY odd inclusion method because most of the files in the AC
code have very generic names, and the PAWN compiler isn't very friendly to
generic names.  If two files have the same name, even if they're not in the
same folder, it will only include one of them.  You can partially get around
this by using "/" instead of "\" (which forces the compiler to include the path
in the name check too), but it is limited to 30 characters*.  To get around
this as well, we just make sure that we know what these 30 characters are and
remove that symbol.  Note that the folder name "y_ac@do_compiler_long_fix" is 25
characters, which, when added to "_inc_" makes our 30 exactly.

* It should be 31, but the variable in the compiler was declared as "sNAMEMAX"
chars instead of "sNAMEMAX+1" as all other similar instances are.
*/

#if defined _INC_y_ac
	#endinput
#endif
#define _INC_y_ac

#include "..\YSI_Internal\y_compilerpass"
#include "..\YSI_Internal\y_version"

#include "..\YSI_Core\y_debug"
#include "..\YSI_Data\y_iterate"

#define YSIM_U_DISABLE
#define MASTER 57
#include "..\YSI_Core\y_master"

/**
 * Callback triggered when a cheat is detected.
 * <param name="playerid">Player's ID.<\param>
 * <param name="cheatid">Cheat ID.<\param>
 * <param name="extraid">Additional cheat ID (depends on hack tool, detection method, etc.).<\param>
 * <param name="info">Additional information.<\param>
 */
forward AC_OnCheatDetected(playerid, cheatid, extraid, info[]);

/**
 * <summary>Generate forward declarations for public and stock functions.<\summary>
 */
#define AC_STOCK%0(%1) stock%0(%1)
//#define AC_STOCK%0(%1) %0(%1)

// Defines new functions. Not the real purpose of this anticheat.
#if defined AC_NEW_FUNCTIONS
	#define IsPlayerAFK				AC_IsPlayerAFK
	#define IsPlayerSpawned			AC_IsPlayerSpawned
#endif

// Rename old natives (unprotected).
#if defined _ALS_GetPlayerMoney
	#if defined BAD_GetPlayerMoney
		#define U_GetPlayerMoney BAD_GetPlayerMoney
	#else
		#error Unable to set U_GetPlayerMoney
	#endif
#else
	native U_GetPlayerMoney(playerid) = GetPlayerMoney;
#endif

#if defined _ALS_GetPlayerSpecialAction
	#if defined BAD_GetPlayerSpecialAction
		#define U_GetPlayerSpecialAction BAD_GetPlayerSpecialAction
	#else
		#error Unable to set U_GetPlayerSpecialAction
	#endif
#else
	native U_GetPlayerSpecialAction(playerid) = GetPlayerSpecialAction;
#endif

// Include the constants.
#include   "y_ac@do_compiler_long_fix/constants/cheats.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/constants/game.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/constants/player.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif

// Include the variables.
#include   "y_ac@do_compiler_long_fix/variables.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif

// Include the utilities.
#include "..\YSI_Core\y_utils"

#include   "y_ac@do_compiler_long_fix/utils/CheatDetected.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/utils/GetSpeed.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/utils/IsPlayerAFK.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/utils/IsPlayerAtVendingMachine.pwn" // Rewrite to use y_areas.
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/utils/IsPlayerSpawned.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
// #include "y_ac@do_compiler_long_fix/utils/memset"
// #if AUTO_INCLUDE_GUARD
	// #undef _inc_y_ac@do_compiler_long_fix
// #endif
#define AC_memset memset // Already defined by YSI.
#include   "y_ac@do_compiler_long_fix/utils/sync/IsPlayerSynced.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/utils/sync/SetPlayerSync.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif

// Include the callback hooks.
#include "..\YSI_Coding\y_hooks"

#include   "y_ac@do_compiler_long_fix/hooks/callbacks/OnPlayerCommandText.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/hooks/callbacks/OnPlayerConnect.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/hooks/callbacks/OnPlayerDeath.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/hooks/callbacks/OnPlayerSpawn.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/hooks/callbacks/OnPlayerText.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/hooks/callbacks/OnPlayerUpdate.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/hooks/callbacks/OnScriptExit.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/hooks/callbacks/OnScriptInit.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif

// Include the watchguard timer.
#include "..\YSI_Coding\y_timers"

#include   "y_ac@do_compiler_long_fix/watchguard/impl/Watchguard_Armour.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/watchguard/impl/Watchguard_Freeze.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/watchguard/impl/Watchguard_Health.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/watchguard/impl/Watchguard_Jetpack.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/watchguard/impl/Watchguard_Joypad.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/watchguard/impl/Watchguard_Money.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/watchguard/impl/Watchguard_Ping.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/watchguard/Watchguard.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif

// Include the function hooks.
#include   "y_ac@do_compiler_long_fix/hooks/natives/GetPlayerMoney.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/hooks/natives/GetPlayerSpecialAction.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/hooks/natives/GivePlayerMoney.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/hooks/natives/ResetPlayerMoney.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/hooks/natives/SetPlayerArmour.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/hooks/natives/SetPlayerHealth.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/hooks/natives/SetPlayerSpecialAction.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/hooks/natives/TogglePlayerControllable.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
#include   "y_ac@do_compiler_long_fix/hooks/natives/TogglePlayerSpectating.pwn"
#if AUTO_INCLUDE_GUARD
	#undef _inc_y_ac@do_compiler_long_fix
#endif
