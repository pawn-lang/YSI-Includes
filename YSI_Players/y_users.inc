/**--------------------------------------------------------------------------**\
					===================================
					 y_users - Registration functions.
					===================================
Description:
	Provides access to a user system for registering and saving users.
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
	
	The Original Code is the YSI malloc include.
	
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
	2.2
Changelog:
	02/02/13:
		Added bits and join timestamp to preload data.
		Added backwards compatible salting to the hash.
	15/11/11:
		Added comments.
		Added language to the top-level player data (needed for login).
	11/11/11:
		First version.
Functions:
	Public
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
\**--------------------------------------------------------------------------**/

#if defined _INC_y_users
	#endinput
#endif
#define _INC_y_users

#if !defined MODE_NAME
	#error Please define "MODE_NAME" before including y_users.
#endif

#include <a_samp>

forward OnPlayerLogin(playerid, uid);

forward OnPlayerLogout(playerid, uid);

forward OnPlayerSaved(playerid, uid);

//#if !defined HAS_USER_CALLBACKS
//	#define HAS_USER_CALLBACKS
//#endif

#include "..\YSI_Internal\y_version"

#include "..\YSI_Players\y_text"

#include "..\YSI_Coding\y_remote"
#include "..\YSI_Core\y_debug"
#include "..\YSI_Storage\y_ini"
#include "..\YSI_Core\y_utils"
#include "..\YSI_Coding\y_timers"

#define YSIM_U_DISABLE
#define MASTER 55
#include "..\YSI_Core\y_master"

#define MAX_INDEX_LENGTH                8

#include "..\YSI_Internal\y_plugins"
#include "..\YSI_Internal\y_natives"

#include "..\YSI_Coding\y_hooks"

#if defined PP_ADLER32
	//#define MAX_PASSWORD_LENGTH             11
	#error Adler32 sucks!
#elseif defined PP_MD5
	#if defined MD5_Hash
		#define MAX_PASSWORD_LENGTH             32
	#else
		#error Could not find MD5_Hash.
	#endif
#elseif defined PP_SHA1
	#error SHA1 unsupported.
#elseif defined PP_YSI
	#define MAX_PASSWORD_LENGTH             16
#elseif defined PP_WP || defined PP_WHIRLPOOL
	#if defined _YSI_PLUGINS_WHIRLPOOL
		#define MAX_PASSWORD_LENGTH             128
	#else
		#error Could not find WP_Hash.
	#endif
#else
	#error Default hash removed: See YSI topic for details.
	//#define PP_YSI
	//#define MAX_PASSWORD_LENGTH             16
#endif

//#define INDEX_DATA_LINE_LENGTH          (MAX_INDEX_LENGTH + 1 + MAX_PLAYER_NAME + 1 + MAX_PASSWORD_LENGTH + 3 + 3 + 9 + 9)
// MAX_INDEX_LENGTH - The player's ID.
// 1 - Space.
// MAX_PLAYER_NAME - The player's name.
// 1 - Space.
// MAX_PASSWORD_LENGTH - The password hash.
// 1 - Space.
// 2 - Language.
// 1 - Space.
// 8 - Free HEX bits.
// 1 - Space.
// 8 - Join timestamp.
// 3 - Newline + Null.
const
	INDEX_DATA_LINE_LENGTH = MAX_INDEX_LENGTH + 1 + MAX_PLAYER_NAME + 1 + MAX_PASSWORD_LENGTH + 1 + 2 + 1 + 8 + 1 + 8 + 3;

#if !defined USER_FILE_PATH
	#if defined YSI_TESTS
		// Create a separate path for any test data so that we don't ruin any
		// live user data.
		#define USER_FILE_PATH                  "YSI/test_users/"
		#define USER_FILE_LENGTH                15
	#else
		#define USER_FILE_PATH                  "YSI/users/"
		#define USER_FILE_LENGTH                10
	#endif
#endif

#define OnUserData[%0](%1) @yU_%0(%1)
#define PINI:%0(%1) forward OnUserData[%0](%1);public OnUserData[%0](%1)

foreign Player_TryRegister(playerid, string:password[]);

foreign Player_TryLogin(playerid, string:password[]);

foreign Player_TryGroup(playerid, string:other[], string:password[]);

foreign Player_ChangePassword(playerid, string:password[]);

foreign Player_ForceGroup(playerid, string:other[]);

foreign Player_ForceLogin(playerid);

foreign Player_ChangeLanguage(playerid, string:code[]);

#if defined USERS_USE_MYSQL
	/*
	#if _YSI_PLUGINS_MYSQL == 7
		#include "y_users/blueg7"
	#elseif _YSI_PLUGINS_MYSQL == 6
		#include "y_users/blueg6"
	#elseif _YSI_PLUGINS_MYSQL == 7
		#include "y_users/stricken"
	#else
		#error No MySQL plugin found.
	#endif
	*/
	
	// I know it is a bit odd that this should need y_ini for database access, but
	// there is a very good reason (loading passwords).
	#include "..\YSI_Storage\y_ini"
	#include "..\YSI_Data\y_iterate"
	
	#include "y_users/dan10"
#elseif defined USERS_USE_SQLITE
	#include "y_users/sqlite"
#else
	#include "y_users/ini"
#endif
#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_users/tests"
#endif

#include "..\YSI_Core\y_master"

