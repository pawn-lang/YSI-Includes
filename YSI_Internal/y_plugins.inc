#if defined _INC_y_plugins
	#endinput
#endif
#define _INC_y_plugins

/*+
 * <library name="y_plugins">
 * <section>
 *  Description
 * </section>
 *  Configuration and detection for third-party SA:MP plugins (including
 *  ones by Y_Less).
 * <section>
 *  Version
 * </section>
 *  1.0
 * </library>
 *//** *//*
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
	Portions created by the Initial Developer are Copyright C 2011
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

// All the code in here relies on detecting FEATURES, not FILENAMES.
#if defined Streamer_IncludeFileVersion
	#define _YSI_PLUGINS_STREAMER
	
	#if !defined IPS_MAX_OBJECTS
		#define IPS_MAX_OBJECTS (20000)
	#endif
	
	#if !defined IPS_MAX_PICKUPS
		#define IPS_MAX_PICKUPS (5000)
	#endif
	
	#if !defined IPS_MAX_CPS
		#define IPS_MAX_CPS (1000)
	#endif
	
	#if !defined IPS_MAX_RACE_CPS
		#define IPS_MAX_RACE_CPS (1000)
	#endif
	
	#if !defined IPS_MAX_MAP_ICONS
		#define IPS_MAX_MAP_ICONS (2000)
	#endif
	
	#if !defined IPS_MAX_3D_TEXT_LABELS
		#define IPS_MAX_3D_TEXT_LABELS (1000)
	#endif
	
	#if !defined IPS_MAX_AREAS
		#define IPS_MAX_AREAS (1000)
	#endif
	#include <streamer>
#endif

#if defined WP_Hash
	#define _YSI_PLUGINS_WHIRLPOOL
#endif

#if defined gps_AddPlayer
	#define _YSI_PLUGINS_GPS
	// This plugin was included later on in the script and found first time,
	// include it here in the second compile pass.
	#include <RouteConnector>
	#include "y_gamerzps"
#endif

#if defined SetTimerEx_
	#define _YSI_PLUGINS_FIXES_2
#endif

/*
#if defined mysql_function_query
	// BlueG R7 MySQL
	#define _YSI_PLUGINS_MYSQL 7
#elseif defined mysql_init
	// StrickenKid MySQL
	#define _YSI_PLUGINS_MYSQL 1
#elseif defined mysql_debug
	// BlueG R5/R6 MySQL
	#define _YSI_PLUGINS_MYSQL 6
#else
	// No MySQL
*/
	#define _YSI_PLUGINS_MYSQL 0
/*
#endif
*/
