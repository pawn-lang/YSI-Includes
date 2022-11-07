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

#define _Y_MASTER_INCLUDED

#if !defined _INC_y_master
	#include "..\y_utils"
	#include "..\..\YSI_Server\y_thirdpartyinclude\y_codeparse"

	CHAIN_HOOK(Master)
	#undef CHAIN_ORDER
	#define CHAIN_ORDER CHAIN_NEXT(Master)
	
	#if !defined YSI_NO_MASTER
		#include "..\y_core\y_rconfix"
	#endif
	#include "y_master_once"
	#include "y_distribute"
#endif

// ALWAYS!  The compiler defines this automatically, don't use it as this is
// included multiple times to handle multiple master systems.
#if defined _inc_y_master_entry
	#undef _inc_y_master_entry
#endif

#if defined MASTER
	#if defined _MASTER
		// Store the last master.
		#include "y_master__push_master"
	#endif
#else
	// Get the previous master (or 0 by default).
	#include "y_master__pop_master"
	
	// Useful debug information (isn't compiled, but shows up with "-l").
	Debug_CodeX{static stock const _POPPED_MASTER = MASTER;}
#endif

#if MASTER < 0 || MASTER >= MAX_MASTERS
	#error Invalid MASTER ID.
#endif

#if defined _INC_y_master
	// Run at least once - clear previous data.
	#include "y_master__cleanup"
#endif

// Initialise the current master if it hasn't already been done.  This is split
// in to 5 parts to reduce compilation times in the common case of not that many
// master systems.
#if     MASTER < 16
	#include "y_master__setup_master_A"
#elseif MASTER < 32
	#include "y_master__setup_master_B"
#elseif MASTER < 48
	#include "y_master__setup_master_C"
#else
	#include "y_master__setup_master_D"
#endif
#undef MASTER

// Include all the correct macro versions for the settings we have just found.
#include "y_master__impl"

#if defined _INC_y_master
	#endinput
#endif
#define _INC_y_master

/**
 * <library
 *   name="y_master"
 *   version="0.2"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <remarks>
 *     <p>
 *     Handles distribution of control of code segments across all running scripts
 *     with YSI to avoid conflicts of checkpoint streamers etc and allow features
 *     like "/commands" displaying all commands on the server.
 *     </p>
 *     
 *     <p>
 *     Now fully autonomous - to use the master system simply define which one you
 *     want and include the script:
 *     
 *     <code>
 *       #define MASTER 14 <br />
 *       #include "Master"
 *     </code>
 *     
 *     That will make the current script attempt to make itself the main master -
 *     you don't need ANY other code for initialisation anywhere (which took a
 *     while to figure out)...
 *     </p>
 *     
 *     <p>
 *     This is now over 2000 lines of repetitive and complex macros!
 *     </p>
 *   </remarks>
 * </library>
 *//** */

// Only include this lot once.
#if defined YSI_TESTS
	#include "..\..\YSI_Coding\y_hooks"
	// Get the new master.
	#define MASTER 58
	#include "y_master_entry"
	// Include the tests.
	#include "y_master_tests"
	// Pop the master.
	#include "y_master_entry"

	#define MASTER 57
	#define YSIM_U_ENABLE
	#include "y_master_entry"
	#include "y_master_module_tests"
	#include "y_master_entry"
#elseif defined YSIM_TEST_MODULE
	#if YSIM_TEST_MODULE == 1
	
	/*
		#define YSI_NO_VERSION_CHECK
		#define YSI_NO_OPTIMISATION_MESSAGE
		#define YSIM_TEST_MODULE 1

		#define YSI_NO_MODE_CACHE
		#define print print2
		#define printf printf2
		#include <a_samp>
		#undef print
		#undef printf

		#include <YSI_Core\y_master>
	*/

		#define MASTER 57
		#include "y_master_entry"
		#include "y_master_module_funcs"
		#include "y_master_entry"
	#elseif YSIM_TEST_MODULE == 2
	
	/*
		#define YSI_NO_VERSION_CHECK
		#define YSI_NO_OPTIMISATION_MESSAGE
		#define YSIM_TEST_MODULE 2
		#define _DEBUG 2

		#define YSI_NO_MODE_CACHE
		#define print print2
		#define printf printf2
		#include <a_samp>
		#undef print
		#undef printf

		#include <YSI_Core\y_master>
	*/

		#define MASTER 57
		#define YSIM_S_ENABLE
		#include "y_master_entry"
		#include "y_master_module_funcs"
		#include "y_master_entry"
	#elseif YSIM_TEST_MODULE == 3
	
	/*
		#define YSI_NO_VERSION_CHECK
		#define YSI_NO_OPTIMISATION_MESSAGE
		#define YSIM_TEST_MODULE 3

		#define YSI_NO_MODE_CACHE
		#define print print2
		#define printf printf2
		#include <a_samp>
		#undef print
		#undef printf

		#include <YSI_Core\y_master>
	*/

		#define MASTER 57
		#define YSIM_C_ENABLE
		#include "y_master_entry"
		#include "y_master_module_funcs"
		#include "y_master_entry"
	#elseif YSIM_TEST_MODULE == 4
	
	/*
		#define YSI_NO_VERSION_CHECK
		#define YSI_NO_OPTIMISATION_MESSAGE
		#define YSIM_TEST_MODULE 4
		#define _DEBUG 3

		#define YSI_NO_MODE_CACHE
		#define print print2
		#define printf printf2
		#include <a_samp>
		#undef print
		#undef printf

		#include <YSI_Core\y_master>
	*/

		#define MASTER 57
		#define YSIM_VERSION 8
		#include "y_master_entry"
		#include "y_master_module_funcs"
		#include "y_master_entry"
	#endif
#endif

