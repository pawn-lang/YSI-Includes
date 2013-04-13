/**--------------------------------------------------------------------------**\
					===============================
					Y Sever Includes - Master Auto
					===============================
Description:
	Attempts to figure out from what library the current instance of the master
	system was included from.
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
	
	The Original Code is the YSI master include.
	
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
	0.1
Changelog:
	06/08/10:
		First version.
Functions:
	Public:
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
	Hooks:
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
		-.
	Static:
		-
Commands:
	-
Compile options:
	-
Operators:
	-
Natives:
	-
</remarks>
\**--------------------------------------------------------------------------**/

// =============================================================================
// =============================================================================
// 
//   MAKE SURE THE RECALL CODE IN y_groups HAS THE RIGHT NUMBERS - THATS GIVEN
//   ODD ERRORS TWICE NOW!!!
// 
// =============================================================================
// =============================================================================

#undef _inc__auto

//#define _YSIM_USED_AUTO

#if defined YSI_TESTS
	/*#if defined _inc_y_testing
		#if !defined _YCM_j@
			#define MASTER              9
			#endinput
		#endif
	#endif*/
	#if defined _MASTER_TEST_ID
		#if !defined _YCM_i@
			#define MASTER              8
			//#undef _MASTER_TEST_ID
			#endinput
		#endif
	#endif
	//#include "y_testing"
	//#define _MASTER_TEST_ID
#endif

// Commands are set as master number 25
#if defined _inc_y_commands
	#if !defined _YCM_z@ // z is letter 25
		#define MASTER                  25
		#endinput
	#endif
#endif

// Groups are set as master number 24
#if defined _inc_y_grouponce
	#if !defined _YCM_y@ // y is letter 24
		#define MASTER                  24
		#endinput
	#endif
#endif

// Reserve this number (only in terms of not using it).
//#define DEFAULT_USER_COMMAND_MASTER   23

// Classes are set as master number 22
#if defined _inc_y_classes
	#if !defined _YCM_w@ // w is letter 22
		#define MASTER                  22
		//#if defined _inc_y_classes_do
		//	// Make sure only the implementation file calls y_master.
		//	#define YSIM_DISABLE_RECALL
		//#endif
		#endinput
	#endif
#endif

// Languages are set as master number 21.  This is the first library I've done
// since largely finishing the y_master system (I hope anyway) and it is now, I
// have to say, VERY smooth adding in a new YSI mastered library!  Actually, I
// need to remember to add the "revert" code, but it's only hard with groups.
#if defined _inc_y_languages
	#if !defined _YCM_v@ // v is letter 21
		#define MASTER                  21
		#endinput
	#endif
#endif

// Players are set as master number 20
#if defined _inc_y_users
	#if !defined _YCM_u@ // u is letter 20
		#define MASTER                  20
		#endinput
	#endif
#endif

// Dialogs are set as master number 19
#if defined _inc_y_dialog
	#if !defined _YCM_t@ // t is letter 19
		#define MASTER                  19
		#endinput
	#endif
#endif

// Areas are set as master number 18
#if defined _inc_y_areas
	#if !defined _YCM_s@ // s is letter 18
		#define MASTER                  18
		#endinput
	#endif
#endif

// PHP is set as master number 17
#if defined _inc_y_php
	#if !defined _YCM_r@ // r is letter 17
		#define MASTER                  17
		#endinput
	#endif
#endif

// Incognito's streamer is set as master number 16
#if defined _inc_streamer
	#if !defined _YCM_q@ // q is letter 16
		#define MASTER                  16
		#endinput
	#endif
#endif

// Incognito's streamer is set as master number 16
#if defined _inc_y_phone
	#if !defined _YCM_p@ // q is letter 16
		#define MASTER                  15
		#endinput
	#endif
#endif

// Races are set as master number 14
#if defined _inc_y_races
	#if !defined _YCM_o@ // o is letter 14
		#define MASTER                  14
		#endinput
	#endif
#endif
#if defined _inc_y_zonenames
	#if !defined _YCM_n@ // o is letter 14
		#define MASTER                  13
		#endinput
	#endif
#endif

// The help system is set as master number 29
/*#if defined _inc_y_help
	#if !defined _YCM_u@ // D is letter 29
		#define MASTER                  20
		#endinput
	#endif
#endif*/

#if defined _YSI_ALLOW_INTERNAL_TEST
	/*#if defined _inc_y_inttest
		#if !defined _YCM_j@
			#define MASTER              9
			#endinput
		#endif
	#endif
	#if defined _inc_y_inttest2
		#if !defined _YCM_i@
			#define MASTER              8
			#endinput
		#endif
	#endif*/
#endif
