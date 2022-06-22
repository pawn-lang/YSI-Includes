#if defined _INC_y_users
	#endinput
#endif
#define _INC_y_users

/*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (c) 2022
	the Initial Developer. All Rights Reserved.

Contributors:
	Y_Less
	koolk
	JoeBullet/Google63
	g_aSlice/Slice
	Misiur
	samphunter
	tianmeta
	maddinat0r
	spacemud
	Crayder
	Dayvison
	Ahmad45123
	Zeex
	irinel1996
	Yiin-
	Chaprnks
	Konstantinos
	Masterchen09
	Southclaws
	PatchwerkQWER
	m0k1
	paulommu
	udan111
	Cheaterman

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
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

#if !defined MODE_NAME
	#error Please define "MODE_NAME" before including y_users.
#endif

forward OnPlayerLogin(playerid, uid);

forward OnPlayerLogout(playerid, uid);

forward OnPlayerSaved(playerid, uid);

#include "..\..\YSI_Core\y_utils"

#include "..\..\YSI_Players\y_text"

#include "..\..\YSI_Coding\y_remote"
#include "..\..\YSI_Storage\y_ini"
#include "..\..\YSI_Coding\y_timers"

#define YSIM_U_DISABLE
#define MASTER 55
#include "..\..\YSI_Core\y_master"

#define MAX_INDEX_LENGTH                8

#include "..\..\YSI_Coding\y_hooks"

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
		#define USER_FILE_PATH                  "YSI/tests/y_users/"
		#define USER_FILE_LENGTH                15
	#else
		#define USER_FILE_PATH                  "YSI/users/"
		#define USER_FILE_LENGTH                10
	#endif
#endif

#define OnUserData[%0](%1) @yU_%0(%1)
#define PINI:%0(%1) forward OnUserData[%0](%1);public OnUserData[%0](%1)

FOREIGN__ Player_TryRegister(playerid, string:password[]);

FOREIGN__ Player_TryLogin(playerid, string:password[]);

FOREIGN__ Player_TryGroup(playerid, string:other[], string:password[]);

FOREIGN__ Player_ChangePassword(playerid, string:password[]);

FOREIGN__ Player_ForceGroup(playerid, string:other[]);

FOREIGN__ Player_ForceLogin(playerid);

FOREIGN__ Player_ChangeLanguage(playerid, string:code[]);

#if defined USERS_USE_MYSQL
	/*
	#if _YSI_PLUGINS_MYSQL == 7
		#include "y_users_blueg7"
	#elseif _YSI_PLUGINS_MYSQL == 6
		#include "y_users_blueg6"
	#elseif _YSI_PLUGINS_MYSQL == 7
		#include "y_users_stricken"
	#else
		#error No MySQL plugin found.
	#endif
	*/
	
	// I know it is a bit odd that this should need y_ini for database access, but
	// there is a very good reason (loading passwords).
	#include "..\..\YSI_Storage\y_ini"
	#include "..\..\YSI_Data\y_iterate"
	
	#include "y_users_dan10"
#elseif defined USERS_USE_SQLITE
	#include "y_users_sqlite"
#else
	#include "y_users_ini"
#endif
#if defined YSI_TESTS
	#include "y_users_tests"
#endif

#include "..\..\YSI_Core\y_master"

