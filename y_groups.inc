/*----------------------------------------------------------------------------*\
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
\*----------------------------------------------------------------------------*/

#include "internal\y_version"

#if !defined _inc_y_groups
	#error Did you do <YSI/y_groups> instead of the required <YSI\y_groups>?
#endif
#undef _inc_y_groups

#include "internal\y_nogroups"
#include "internal\y_plugins"

/*#if defined YSI_GROUPS_LAST
	#if YSI_GROUPS_LAST == 25
		#undef _GROUP_MAKE_NAME
		#undef _GROUP_MAKE_LIMIT
		#define _GROUP_MAKE_NAME        _GROUP_MAKE_NAME_CMD
		#define _GROUP_MAKE_LIMIT       _GROUP_MAKE_LIMIT_CMD
	#elseif YSI_GROUPS_LAST == 22
		#undef _GROUP_MAKE_NAME
		#undef _GROUP_MAKE_LIMIT
		#define _GROUP_MAKE_NAME        _GROUP_MAKE_NAME_CLASSES
		#define _GROUP_MAKE_LIMIT       _GROUP_MAKE_LIMIT_CLASSES
	#elseif YSI_GROUPS_LAST == 9
		#undef _GROUP_MAKE_NAME
		#undef _GROUP_MAKE_LIMIT
		#define _GROUP_MAKE_NAME        _GROUP_MAKE_NAME_INTTEST
		#define _GROUP_MAKE_LIMIT       _GROUP_MAKE_LIMIT_INTTEST
	#elseif YSI_GROUPS_LAST == 8
		#undef _GROUP_MAKE_NAME
		#undef _GROUP_MAKE_LIMIT
		#define _GROUP_MAKE_NAME        _GROUP_MAKE_NAME_INTTEST2
		#define _GROUP_MAKE_LIMIT       _GROUP_MAKE_LIMIT_INTTEST2
	#endif
	#undef YSI_GROUPS_LAST
#endif*/

#if defined _YSI_GROUPS_FIRST_HALF
	#undef _YSI_GROUPS_FIRST_HALF
#endif

// First, detect which library has included this.  If none then it was the user.
#if defined _inc_y_classes
	#if !defined _YSI_GROUP_CLASSES_INCLUDED
		// Although this is included before _GROUP_MAKE_NAME is set, it will
		// still be the correct value eventually.
		// Mark this library as existing.
		#define _YSI_GROUP_CLASSES_INCLUDED
		// These all need doing twice - once here and once below.
		//#if defined _YSI_HAS_GROUP_SYSTEM
		//	#include "internal\y_groupfirst"
		//#endif
		#undef _GROUP_MAKE_NAME
		#undef _GROUP_MAKE_LIMIT
		#define _GROUP_MAKE_NAME        _GROUP_MAKE_NAME_CLASSES
		#define _GROUP_MAKE_LIMIT       _GROUP_MAKE_LIMIT_CLASSES
		#if defined _YSI_HAS_GROUP_SYSTEM
			#include "internal\y_groupsecond"
			#include "internal\y_classgroups"
		#endif
		#include "internal\y_groupsingle"
		// End.
		#endinput
	#endif
#endif
#if defined _inc_y_commands
	#if !defined _YSI_GROUP_COMMANDS_INCLUDED
		// Although this is included before _GROUP_MAKE_NAME is set, it will
		// still be the correct value eventually.
		// Mark this library as existing.
		#define _YSI_GROUP_COMMANDS_INCLUDED
		// These all need doing twice - once here and once below.
		//#if defined _YSI_HAS_GROUP_SYSTEM
		//	#include "internal\y_groupfirst"
		//#endif
		#undef _GROUP_MAKE_NAME
		#undef _GROUP_MAKE_LIMIT
		#define _GROUP_MAKE_NAME        _GROUP_MAKE_NAME_CMD
		#define _GROUP_MAKE_LIMIT       _GROUP_MAKE_LIMIT_CMD
		#if defined _YSI_HAS_GROUP_SYSTEM
			#include "internal\y_groupsecond"
		#endif
		#include "internal\y_groupsingle"
		// End.
		#endinput
	#endif
#endif
#if defined _inc_y_areas
	#if !defined _YSI_GROUP_AREAS_INCLUDED
		// Although this is included before _GROUP_MAKE_NAME is set, it will
		// still be the correct value eventually.
		// Mark this library as existing.
		#define _YSI_GROUP_AREAS_INCLUDED
		// These all need doing twice - once here and once below.
		//#if defined _YSI_HAS_GROUP_SYSTEM
		//	#include "internal\y_groupfirst"
		//#endif
		#undef _GROUP_MAKE_NAME
		#undef _GROUP_MAKE_LIMIT
		#define _GROUP_MAKE_NAME        _GROUP_MAKE_NAME_AREAS
		#define _GROUP_MAKE_LIMIT       _GROUP_MAKE_LIMIT_AREAS
		#if defined _YSI_HAS_GROUP_SYSTEM
			#include "internal\y_groupsecond"
		#endif
		#include "internal\y_groupsingle"
		// End.
		#endinput
	#endif
#endif
#if defined _YSI_ALLOW_INTERNAL_TEST
	#if defined _inc_y_inttest
		#if !defined _YSI_GROUP_INTTEST_INCLUDED
			// Mark this library as existing.
			#define _YSI_GROUP_INTTEST_INCLUDED
			// These all need doing twice - once here and once below.
			//#if defined _YSI_HAS_GROUP_SYSTEM
			//	#include "internal\y_groupfirst"
			//#endif
			#undef _GROUP_MAKE_NAME
			#undef _GROUP_MAKE_LIMIT
			#define _GROUP_MAKE_NAME    _GROUP_MAKE_NAME_INTTEST
			#define _GROUP_MAKE_LIMIT   _GROUP_MAKE_LIMIT_INTTEST
			#if defined _YSI_HAS_GROUP_SYSTEM
				#include "internal\y_groupsecond"
			#endif
			#include "internal\y_groupsingle"
			// End.
			#endinput
		#endif
	#endif
	#if defined _inc_y_inttest2
		#if !defined _YSI_GROUP_INTTEST2_INCLUDED
			// Mark this library as existing.
			#define _YSI_GROUP_INTTEST2_INCLUDED
			// These all need doing twice - once here and once below.
			//#if defined _YSI_HAS_GROUP_SYSTEM
			//	#include "internal\y_groupfirst"
			//#endif
			#undef _GROUP_MAKE_NAME
			#undef _GROUP_MAKE_LIMIT
			#define _GROUP_MAKE_NAME    _GROUP_MAKE_NAME_INTTEST2
			#define _GROUP_MAKE_LIMIT   _GROUP_MAKE_LIMIT_INTTEST2
			#if defined _YSI_HAS_GROUP_SYSTEM
				#include "internal\y_groupsecond"
			#endif
			#include "internal\y_groupsingle"
			// End.
			#endinput
		#endif
	#endif
#endif

// ||                                                                         ||
// =============================================================================
// ||                                                                         ||
#define _YSI_GROUPS_FIRST_HALF
// ||                                                                         ||
// =============================================================================
// ||                                                                         ||

// User inclusion.
#if !defined _YSI_HAS_GROUP_SYSTEM
	#define _YSI_HAS_GROUP_SYSTEM
	// Include the main code.
	#include <a_samp>
	#include "internal\y_grouponce"
	
	// Include code for previous libraries.
	#if defined _YSI_GROUP_CLASSES_INCLUDED
		// This only needs to be done if the library was previously included.
		#define _YSIM_OVERRIDE          22
		#include "y_master"
		// Include the first half of the file for the call chain.
		//#include "internal\y_groupfirst"
		#undef _GROUP_MAKE_NAME
		#undef _GROUP_MAKE_LIMIT
		#define _GROUP_MAKE_NAME        _GROUP_MAKE_NAME_CLASSES
		#define _GROUP_MAKE_LIMIT       _GROUP_MAKE_LIMIT_CLASSES
		// Include the second half of the file for the methods.
		#include "internal\y_groupsecond"
		#include "internal\y_classgroups"
	#endif
	#if defined _YSI_GROUP_COMMANDS_INCLUDED
		// This only needs to be done if the library was previously included.
		#define _YSIM_OVERRIDE          25
		#include "y_master"
		// Include the first half of the file for the call chain.
		//#include "internal\y_groupfirst"
		#undef _GROUP_MAKE_NAME
		#undef _GROUP_MAKE_LIMIT
		#define _GROUP_MAKE_NAME        _GROUP_MAKE_NAME_CMD
		#define _GROUP_MAKE_LIMIT       _GROUP_MAKE_LIMIT_CMD
		// Include the second half of the file for the methods.
		#include "internal\y_groupsecond"
	#endif
	#if defined _YSI_GROUP_AREAS_INCLUDED
		// This only needs to be done if the library was previously included.
		#define _YSIM_OVERRIDE          18
		#include "y_master"
		// Include the first half of the file for the call chain.
		//#include "internal\y_groupfirst"
		#undef _GROUP_MAKE_NAME
		#undef _GROUP_MAKE_LIMIT
		#define _GROUP_MAKE_NAME        _GROUP_MAKE_NAME_AREAS
		#define _GROUP_MAKE_LIMIT       _GROUP_MAKE_LIMIT_AREAS
		// Include the second half of the file for the methods.
		#include "internal\y_groupsecond"
	#endif
	#if defined _YSI_PLUGINS_STREAMER
		#if defined _YCM_q@
			#define _YSIM_OVERRIDE          16
		#endif
		#include "y_master"
		// Include the first half of the file for the call chain.
		//#include "internal\y_groupfirst"
		//#undef _GROUP_MAKE_NAME
		//#undef _GROUP_MAKE_LIMIT
		//#define _GROUP_MAKE_NAME<%0...%1> %0SObject%1
		//#define _GROUP_MAKE_LIMIT<%0...%1> 
		// Include the second half of the file for the methods.
		//#include "internal\y_groupsecond"
		#include "internal\y_incognitostreamer"
	#endif
	// Internal test library.
	#if defined _YSI_ALLOW_INTERNAL_TEST
		#if defined _YSI_GROUP_INTTEST_INCLUDED
			#define _YSIM_OVERRIDE      9
			#include "y_master"
			//#include "internal\y_groupfirst"
			#undef _GROUP_MAKE_NAME
			#undef _GROUP_MAKE_LIMIT
			#define _GROUP_MAKE_NAME    _GROUP_MAKE_NAME_INTTEST
			#define _GROUP_MAKE_LIMIT   _GROUP_MAKE_LIMIT_INTTEST
			#include "internal\y_groupsecond"
		#endif
		#if defined _YSI_GROUP_INTTEST2_INCLUDED
			#define _YSIM_OVERRIDE      8
			#include "y_master"
			//#include "internal\y_groupfirst"
			#undef _GROUP_MAKE_NAME
			#undef _GROUP_MAKE_LIMIT
			#define _GROUP_MAKE_NAME    _GROUP_MAKE_NAME_INTTEST2
			#define _GROUP_MAKE_LIMIT   _GROUP_MAKE_LIMIT_INTTEST2
			#include "internal\y_groupsecond"
		#endif
	#endif
	// Recursive group functions to make groups of groups.  Make this code pure
	// client code so that 90% of it is not included ever.
	/*#define _YSIM_OVERRIDE      24
	//#define YSIM_C_ENABLE
	#include "y_master"
	#undef _GROUP_MAKE_NAME
	#undef _GROUP_MAKE_LIMIT*/
	/*#define _GROUP_MAKE_NAME        _GROUP_MAKE_NAME_GROUP
	#define _GROUP_MAKE_LIMIT       _GROUP_MAKE_LIMIT_GROUP
	#define _GROUP_MAKE_TAG         Group
	//#include "internal\y_groupsecond"
	#undef _YSI_GROUPS_FIRST_HALF
	// Disable the OnPlayerConnect code.
	#undef ghook
	#define ghook%0On%1(%2) stock _GROUP_MAKE_NAME<On%2...>(%3)
	#include "internal\y_groupsecond"
	#undef ghook
	#define ghook group_hook
	#define _YSI_GROUPS_FIRST_HALF
	#define _GROUP_MAKE_TAG         Group
	#include "internal\y_groupsingle"*/
	// These need VERY different defaults.
#endif

// Now include any user defined libraries.
#if defined GROUP_LIBRARY_NAME
	#if defined GROUP_LIBRARY_SIZE
		// Include the generic group code for this new custom group.
		#if defined _YSIM_MANUAL_SET
			#define _YSIM_RESET_USER
		#endif
		#include "y_master"
		//#include "internal\y_groupsingle"
		//#include "internal\y_groupfirst"
		#undef _GROUP_MAKE_NAME
		#undef _GROUP_MAKE_LIMIT
		#define _GROUP_MAKE_NAME        GROUP_LIBRARY_NAME
		#define _GROUP_MAKE_LIMIT       GROUP_LIBRARY_SIZE
		//#if defined GROUP_LIBRARY_TAG
		//	#define _GROUP_MAKE_TAG       GROUP_LIBRARY_TAG
		//#endif
		#undef _YSI_GROUPS_FIRST_HALF
		// Include the second half of the file for the methods.
		#include "internal\y_groupsecond"
		#define _YSI_GROUPS_FIRST_HALF
		#include "internal\y_groupsingle"
		// Remove the definitions.
		//#undef GROUP_LIBRARY_SIZE
		//#undef GROUP_LIBRARY_NAME
	#else
		#error You must define both GROUP_LIBRARY_SIZE and GROUP_LIBRARY_NAME.
	#endif
#else
	#if defined GROUP_LIBRARY_SIZE
		#error You must define both GROUP_LIBRARY_SIZE and GROUP_LIBRARY_NAME.
	#endif
#endif

// Revert to the user's included definition if y_groups was included after all
// group using libraries and after explicit y_master inclusion.
//#include "internal\y_grouprevert"

//#define YSI_SET_LAST_GROUP 24
#include "internal\y_grouprevert"
