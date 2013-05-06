/**--------------------------------------------------------------------------**\
					=======================================
					 y_groups - Player group abstractions! 
					=======================================
Description:
	Admin levels, gangs, teams etc - they're all "groups" of people, this
	provides an abstraction for all of these collections.
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
	
	The Original Code is the YSI groups include.
	
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
	1.0
Changelog:
	29/11/10:
		First version
\**--------------------------------------------------------------------------**/

#include "..\YSI-Internal\y_version"

#if !defined _inc_y_groups
	#error Did you do <YSI/y_groups> instead of the required <YSI\y_groups>?
#endif
#undef _inc_y_groups

// Get basic defines.
#include "..\YSI-Internal\y_plugins"
#include "y_groups/setup"
#include "y_groups/impl"

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
		#include "..\YSI-Players\y_groups\_funcs"
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

stock _YSI_HAS_y_groups(_do_not_call_me_ever_, _like_never_)
{
	P:E("You called _YSI_HAS_y_groups!  Bad, don't do that!", _do_not_call_me_ever_, _like_never_);
	assert(false);
	return 0;
}

#if defined YSI_TESTS
	#include "..\YSI-Core\y_testing"
	#include "y_groups/tests"
#endif
