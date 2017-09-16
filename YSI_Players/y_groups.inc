/*                                                                                              *
 *                                                                                             *
 *     _____ ______ ______   ____  ______ _      ______          __  ______ ____  _____        *
 *    / ____|  ____|  ____| |  _ \|  ____| |    / __ \ \        / / |  ____/ __ \|  __ \       *
 *   | (___ | |__  | |__    | |_) | |__  | |   | |  | \ \  /\  / /  | |__ | |  | | |__) |      *
 *    \___ \|  __| |  __|   |  _ <|  __| | |   | |  | |\ \/  \/ /   |  __|| |  | |  _  /       *
 *    ____) | |____| |____  | |_) | |____| |___| |__| | \  /\  /    | |   | |__| | | \ \       *
 *   |_____/|______|______| |____/|______|______\____/   \/  \/     |_|    \____/|_|  \_\      *
 *                                                                                             *
 *    _____   ____   _____ _    _ __  __ ______ _   _ _______    _______ _____ ____  _   _     *
 *   |  __ \ / __ \ / ____| |  | |  \/  |  ____| \ | |__   __|/\|__   __|_   _/ __ \| \ | |    *
 *   | |  | | |  | | |    | |  | | \  / | |__  |  \| |  | |  /  \  | |    | || |  | |  \| |    *
 *   | |  | | |  | | |    | |  | | |\/| |  __| | . ` |  | | / /\ \ | |    | || |  | | . ` |    *
 *   | |__| | |__| | |____| |__| | |  | | |____| |\  |  | |/ ____ \| |   _| || |__| | |\  |    *
 *   |_____/ \____/ \_____|\____/|_|  |_|______|_| \_|  |_/_/    \_\_|  |_____\____/|_| \_|    *
 *                                                                                             *
 *   This is required for technical reasons - to place it after `#endinput` to not generate    *
 *                   multiple copies of it in XML when compiling with `-r`.                    *
 *                                                                                             *
*//*
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

#include "..\YSI_Internal\y_version"

#if defined _inc_y_groups
	#undef _inc_y_groups
#endif

#if !defined _INC_y_groups
	#include <a_samp>
	
	// Get basic defines.
	#include "..\YSI_Internal\y_plugins"
	
	#include "..\YSI_Internal\y_compilerdata"
	#include "..\YSI_Data\y_bit"
	
	#if !defined _INC_y_groups__funcs
		#define _INC_y_groups__funcs
		#include "y_groups/setup"
		#include "..\YSI_Internal\y_shortfunc"
		#include "..\YSI_Data\y_iterate"
	#endif
	
	#include "..\YSI_Server\y_scriptinit"
	#include "..\YSI_Data\y_playerarray"
	
	#include "..\YSI_Coding\y_stringhash"
	#include "..\YSI_Core\y_debug"
	#include "..\YSI_Coding\y_remote"
	
	#include "..\YSI_Storage\y_amx"
	
	
	#define YSIM_U_DISABLE
	#define MASTER 59
	#include "..\YSI_Core\y_master"
	#include "..\YSI_Internal\y_distribute"
	
	#include "..\YSI_Coding\y_hooks"
	
	#include "y_groups/impl"
	
	#include "..\YSI_Core\y_master"
#endif

#if defined GROUP_LIBRARY_NAME
	#if defined GROUP_LIBRARY_SIZE
		// Include the generic group code for this new custom group.
		// User-inclusion.
		#define _GROUP_MAKE_LIMIT       GROUP_LIBRARY_SIZE
		#define _GROUP_MAKE_NAME        GROUP_LIBRARY_NAME
		#if defined GROUP_LIBRARY_TAGS
			#define _GROUP_MAKE_TAG         GROUP_LIBRARY_TAGS
		#else
			#define _GROUP_MAKE_TAG _
		#endif
		#include "y_groups\_funcs"
		// Now remove the defines.
		#if defined GROUP_LIBRARY_TAGS
			#undef GROUP_LIBRARY_TAGS
		#endif
		#undef _GROUP_MAKE_LIMIT
		#undef _GROUP_MAKE_NAME
		#undef GROUP_LIBRARY_NAME
		#undef GROUP_LIBRARY_SIZE
	#else
		#error You must define both GROUP_LIBRARY_SIZE and GROUP_LIBRARY_NAME.
	#endif
#else
	#if defined GROUP_LIBRARY_SIZE
		#error You must define both GROUP_LIBRARY_SIZE and GROUP_LIBRARY_NAME.
	#endif
#endif

// Only include the remainder just once.
#if defined _INC_y_groups
	#endinput
#endif
#define _INC_y_groups

/**
 * <library name="y_groups">
 * <section>
 *  Description
 * </section>
 *  Admin levels, gangs, teams etc - they're all "groups" of people, this
 *  provides an abstraction for all of these collections.
 * <section>
 *  Version
 * </section>
 *  1.0
 * </library>
 *//** */

stock _YSI_HAS_y_groups(_do_not_call_me_ever_, _like_never_)
{
	P:E("You called _YSI_HAS_y_groups!  Bad, don't do that!", _do_not_call_me_ever_, _like_never_);
	assert(false);
	return 0;
}

#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_groups/tests"
#endif

