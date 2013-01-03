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
	
	The Original Code is the YSI group include.
	
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
	04/10/12:
		Major update to better distribute group data.  Now all script have it.
		Changed the code to favour common cases of element creation not groups.
		Added group hierarchys.
	29/11/10:
		First version
\*----------------------------------------------------------------------------*/

#include <a_samp>

#include "..\y_scriptinit"

//#include "..\y_master"
#define YSIM_U_DISABLE
#include "..\y_master"
#include "..\y_playerarray"

#include "..\y_stringhash"
#include "..\y_debug"
#include "..\y_remote"

//#include "..\y_hooks"
#include "..\y_amx"
//#include "..\y_cell"

#include "..\y_iterate"

#include "..\y_hooks"



//#define _YSI_HAS_GROUP_SYSTEM

//#define _GROUP_MAKE_NAME<%0...%1> %0_%1
// Dummy value
//#define _GROUP_MAKE_LIMIT               0

// Dummy values.
#undef _GROUP_MAKE_NAME
#undef _GROUP_MAKE_LIMIT
#define _GROUP_MAKE_NAME<%0...%1>       %0_%1
#define _GROUP_MAKE_LIMIT               0

#define _GROUP_MAKE_NAME_GROUP<%0...%1> %0Group%1
#define _GROUP_MAKE_LIMIT_GROUP _MAX_GROUPS

// Example:
//  #define _GROUP_MAKE_NAME<%0...%1> %0Checkpoint%1
/*#if !defined _GROUP_MAKE_NAME
	#error Please define _GROUP_MAKE_NAME before including y_groupsone.
#endif
#if !defined _GROUP_MAKE_LIMIT
	#error Please define _GROUP_MAKE_LIMIT before including y_groupsone.
#endif*/

// Define local variable names.  This will go in the single call file.
//#define _GROUP_LOCAL_NAME               _GROUP_MAKE_NAME<i...>
#define _GROUP_GROUP_NAME               _GROUP_MAKE_NAME<YSI_gs_Group...Data>
#define _GROUP_GLOBAL_NAME              //_GROUP_MAKE_NAME<YSI_gs_GroupGlobal...>

/*stock _Group_ErrorFunc()
{
	// BEST FUNCTION EVER!
	group group group
}*/

//#define _GROUP_SET_PLAYER               _GROUP_MAKE_NAME<..._SetPlayer>

/*#define _GROUP_UPDATE                   _GROUP_MAKE_NAME<Group_UpdatePlayer...>
#define _GROUP_UPDATE_ALL               _GROUP_MAKE_NAME<Group_UpdateAll...>

#define _GROUP_GROUP_FUNC               _GROUP_MAKE_NAME<Group_Set...>
#define _GROUP_GLOBAL_FUNC              _GROUP_MAKE_NAME<Group_SetGlobal...>

#define _GROUP_GLOBAL_DEF               _GROUP_MAKE_NAME<Group_SetGlobal...Default>
#define _GROUP_GROUP_DEF                _GROUP_MAKE_NAME<Group_Set...Default>

//#define _GROUP_ON_PLAYER_CONNECT        _GROUP_MAKE_NAME<@yH_PlayerConnect_...@yG>
#define _GROUP_ON_PLAYER_CONNECT        _GROUP_MAKE_NAME<@yH_PlayerConnect...@yG>

#define _GROUP_DEFAULTS                 _GROUP_MAKE_NAME<Group_...Defaults>

#define _GROUP_INIT                     _GROUP_MAKE_NAME<Group_...Init>*/

#define _GROUP_CREATE                   _GROUP_MAKE_NAME<@yG_Init...>
#define _GROUP_UPDATE_PLAYER            _GROUP_MAKE_NAME<@yG_Upd...>
//#define _GROUP_ON_PLAYER_CONNECT        _GROUP_MAKE_NAME<@yG_..._PlayerConnect>
//#define _GROUP_ON_PLAYER_CONNECT        RH:_GROUP_MAKE_NAME<...@yG_OnPlayerConnect>

/*#define _GROUP_OPC_OTHER_CALLED   _GROUP_MAKE_NAME<_@yGPlayerConnect_...>
#define _GROUP_OPC_IS_CALLED   _GROUP_MAKE_NAME<_yG@PlayerConnect_...>
#define _GROUP_OPC_PUBLIC      _GROUP_MAKE_NAME<@yG_PlayerConnect_...>*/

//#define group_hook%0On%1(%2) _GROUP_MAKE_NAME<master_hook On%1...>(%2)

/*#define ghook%0(%1)

#include "y_groupsecond.inc"

#undef ghook
#define ghook group_hook*/

#define gforeign%1(%2); _GROUP_MAKE_NAME<foreign%1>(%2);
#define gglobal%1(%2) _GROUP_MAKE_NAME<global%1>(%2)

/*----------------------------------------------------------------------------*\
Function:
	GROUP_CHAIN
Params:
	%9 - Check if the function exists?
	%0 - Variable holding the function.
	%1 - Parameters.
Return:
	-
Notes:
	Calls the correct function to chain a function with the given number of
	parameters, calls the function stored in a variable and passes parameters
	BY REFERENCE - ALL of them!
\*----------------------------------------------------------------------------*/

#define GROUP_CHAIN%9<%0>(%1) (J@=_:(_Y_G@C_YES:_Y_G@C_NO:%0%9|||(_:_Y_G@C3:_Y_G@C2:_Y_G@C0:_Y_G@C1:%0(%1))))

#define _Y_G@C3:_Y_G@C2:_Y_G@C0:_Y_G@C1:%0(%1,%2,%3) _Y_G@C_3(%0,_:_Y_G@P:_Y_G@Q:_Y_G@R:%1,_:%2,_:%3|||)
#define _Y_G@C2:_Y_G@C0:_Y_G@C1:%0(%1,%2) _Y_G@C_2(%0,_:_Y_G@P:_Y_G@Q:_Y_G@R:%1,_:%2|||)
#define _Y_G@C0:_Y_G@C1:%0() _Y_G@C_0(%0)
#define _Y_G@C1:%0(%1) _Y_G@C_1(%0,_:_Y_G@P:_Y_G@Q:_Y_G@R:%1|||)
#define _Y_G@C_YES:_Y_G@C_NO:%0?||| (!(%0))?(0):
#define _Y_G@C_NO:%0|||
// Can strip out multiple brackets in one go.
#define _Y_G@P:%0[]%1||| _Y_G@P:%0%1|||
#define _Y_G@Q:%0&%1||| _Y_G@Q:%0%1|||
#define _Y_G@R:%0||| %0

//#define master_hook%0On%2(%3) hook On%2(%3)<>return 1;rehook On%2(%3)<_YCM:y>

#if !defined MAX_GROUP_NAME
	#define MAX_GROUP_NAME              (24)
#endif

#if defined MAX_GROUPS
	// Round up to the next nice number (or not, we could with long macros).
	#define _MAX_GROUPS                  (_:MAX_GROUPS)
#else
	// 1 less than a nice number (with good reason).
	#define _MAX_GROUPS                  (_:127)
#endif

#define _MAX_GROUPS_G (_:_MAX_GROUPS + 1)

// Note that these macros always do the last element before all the others
// (which may or may not be in order).  This is as the last element holds the
// "default" group, which is the most likely to be a good match.
#if _MAX_GROUPS < 32
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[0]&%1[0])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[0]&%1[0]==%0[0])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[0]==%1[0])
	#define _GROUPS_CHECK_NONE(%0,%1) if(!(%0[0]&%1[0]))
#elseif _MAX_GROUPS < 64
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[1]&%1[1]||%0[0]&%1[0])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[1]&%1[1]||%0[0]&%1[0])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[1]&%1[1]||%0[0]&%1[0])
	#define _GROUPS_CHECK_NONE(%0,%1) if(%0[1]&%1[1]||%0[0]&%1[0])
#elseif _MAX_GROUPS < 96
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[2]&%1[2]||%0[0]&%1[0]||%0[1]&%1[1])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[2]&%1[2]||%0[0]&%1[0]||%0[1]&%1[1])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[2]&%1[2]||%0[0]&%1[0]||%0[1]&%1[1])
	#define _GROUPS_CHECK_NONE(%0,%1) if(%0[2]&%1[2]||%0[0]&%1[0]||%0[1]&%1[1])
#elseif _MAX_GROUPS < 128
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[3]&%1[3]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[3]&%1[3]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[3]&%1[3]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2])
	#define _GROUPS_CHECK_NONE(%0,%1) if(%0[3]&%1[3]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2])
#elseif _MAX_GROUPS < 160
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[4]&%1[4]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[4]&%1[4]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[4]&%1[4]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3])
	#define _GROUPS_CHECK_NONE(%0,%1) if(%0[4]&%1[4]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3])
#elseif _MAX_GROUPS < 192
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[5]&%1[5]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[5]&%1[5]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[5]&%1[5]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4])
	#define _GROUPS_CHECK_NONE(%0,%1) if(%0[5]&%1[5]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4])
#elseif _MAX_GROUPS < 224
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[6]&%1[6]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[6]&%1[6]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[6]&%1[6]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5])
	#define _GROUPS_CHECK_NONE(%0,%1) if(%0[6]&%1[6]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5])
#elseif _MAX_GROUPS < 256
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[7]&%1[7]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[7]&%1[7]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[7]&%1[7]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6])
	#define _GROUPS_CHECK_NONE(%0,%1) if(%0[7]&%1[7]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6])
#elseif _MAX_GROUPS < 288
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[8]&%1[8]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[8]&%1[8]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[8]&%1[8]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7])
	#define _GROUPS_CHECK_NONE(%0,%1) if(%0[8]&%1[8]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7])
#elseif _MAX_GROUPS < 320
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[9]&%1[9]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[9]&%1[9]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[9]&%1[9]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8])
	#define _GROUPS_CHECK_NONE(%0,%1) if(%0[9]&%1[9]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8])
#elseif _MAX_GROUPS < 352
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[10]&%1[10]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[10]&%1[10]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[10]&%1[10]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9])
	#define _GROUPS_CHECK_NONE(%0,%1) if(%0[10]&%1[10]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9])
#elseif _MAX_GROUPS < 384
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[11]&%1[11]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[11]&%1[11]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[11]&%1[11]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10])
	#define _GROUPS_CHECK_NONE(%0,%1) if(%0[11]&%1[11]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10])
#elseif _MAX_GROUPS < 416
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[12]&%1[12]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[12]&%1[12]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[12]&%1[12]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11])
	#define _GROUPS_CHECK_NONE(%0,%1) if(%0[12]&%1[12]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11])
#elseif _MAX_GROUPS < 448
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[13]&%1[13]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[13]&%1[13]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[13]&%1[13]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12])
	#define _GROUPS_CHECK_NONE(%0,%1) if(%0[13]&%1[13]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12])
#elseif _MAX_GROUPS < 480
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[14]&%1[14]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12]||%0[13]&%1[13])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[14]&%1[14]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12]||%0[13]&%1[13])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[14]&%1[14]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12]||%0[13]&%1[13])
	#define _GROUPS_CHECK_NONE(%0,%1) if(%0[14]&%1[14]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12]||%0[13]&%1[13])
#elseif _MAX_GROUPS < 512
	#define _GROUPS_CHECK_ANY(%0,%1) if(%0[15]&%1[15]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12]||%0[13]&%1[13]||%0[14]&%1[14])
	#define _GROUPS_CHECK_ALL(%0,%1) if(%0[15]&%1[15]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12]||%0[13]&%1[13]||%0[14]&%1[14])
	#define _GROUPS_CHECK_BOTH(%0,%1) if(%0[15]&%1[15]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12]||%0[13]&%1[13]||%0[14]&%1[14])
	#define _GROUPS_CHECK_NONE(%0,%1) if(%0[15]&%1[15]||%0[0]&%1[0]||%0[1]&%1[1]||%0[2]&%1[2]||%0[3]&%1[3]||%0[4]&%1[4]||%0[5]&%1[5]||%0[6]&%1[6]||%0[7]&%1[7]||%0[8]&%1[8]||%0[9]&%1[9]||%0[10]&%1[10]||%0[11]&%1[11]||%0[12]&%1[12]||%0[13]&%1[13]||%0[14]&%1[14])
#else
	#define _GROUPS_CHECK(%0,%1) \
		for (new __g = bits<_:_MAX_GROUPS + 1>; __g-- != 0; ) if (_:%0[__g] & _:%1[__g])
		//for (new __g = 0; __g != bits<_:_MAX_GROUPS + 1>; ++__g) if (_:%0[__g] & _:%1[__g])
#endif

/*
New groups check:

if (ALL A == ALL B)
{
	if (ALL A == P)
	{
		// Add.
	}
	else
	{
		// Remove.
	}
}
else
{
	if (ANY A == P && NO B == P)
	{
		// Add.
	}
	else
	{
		// Remove.
	}
}
*/

enum e_GROUP_FLAGS (<<= 1)
{
	e_GROUP_FLAGS_NONE = 0,
	e_GROUP_FLAGS_GANG = 1,
	// I can't remember why I had this!
	//e_GROUP_FLAGS_CHAT,
	e_GROUP_FLAGS_ACTIVE,
	// Only ever set for one group.
	e_GROUP_FLAGS_GLOBAL,
	// Has no name.
	e_GROUP_FLAGS_TEMP,
	e_GROUP_FLAGS_COLOR = 0xFFFFFF00
}

enum E_GROUP_DATA
{
	E_GROUP_DATA_NAME[MAX_GROUP_NAME char],
	//E_GROUP_DATA_COUNT,
	E_GROUP_DATA_HASH,
	e_GROUP_FLAGS:E_GROUP_DATA_FLAGS,
}

// Define the groups iterator in terms of the underlying bits, but without the
// need for users to know about the "YSI_gGroupPlayers" array, just the player.
#define PlayerGroups@YSII_Ag(%0,%1) Group:Bits@YSII_Ag(YSI_gGroupPlayers[%0],_:%1)|GROUP_MASK

// I have "new", "stock", "static", "static stock" and "static stock const" - 
// that is pretty much every meaningful combination possible!  The only other
// vaguely useful one would be "stock const".  In fact I now have that too!
new //stock
	//PlayerArray:YSI_gGroupPlayers[_MAX_GROUPS]<MAX_PLAYERS>,
	BitArray:YSI_gGroupPlayers[MAX_PLAYERS]<_MAX_GROUPS_G>;

stock
	BitArray:YSI_gTempGroups<_MAX_GROUPS_G>;

stock const
	BitArray:YSI_g_cEmptyGroups<_MAX_GROUPS_G>;

//#define GROUPS_MAX_LIBRARIES            4

static
	// Function pointers for chaining.
	YSI_g_sNextInitFunc,
	YSI_g_sNextUpdFunc,
	YSI_g_sNextAddFunc,
	YSI_g_sGroupCount;

static stock const
	YSI_g_scGlobalName[] = "__GLOBAL",
	BitArray:RG@<_MAX_GROUPS_G>;

static stock
	// Create group hierarchys.
	YSI_gGroupData[_MAX_GROUPS_G][E_GROUP_DATA],
	BitArray:YSI_g_sChildGroups[_MAX_GROUPS_G]<_MAX_GROUPS_G>,
	//BitArray:YSI_g_sChildDefaults<_MAX_GROUPS_G>,
	Iterator:GroupPlayers[_MAX_GROUPS_G]<MAX_PLAYERS>;

MASTER_DATA<_MAX_GROUPS_G>

//#define GROUP_BITS<%0> BitArray:%0<_MAX_GROUPS_G>,

#define _Group_HasPlayer(%0,%1) \
	Bit_Get(YSI_gGroupPlayers[(%1)],(%0)) //, _MAX_GROUPS_G)
	//PA_Get(YSI_gGroupPlayers[(%0)],(%1))
	//Bit_Get(YSI_gGroupPlayers[(%0)], (%1), MAX_PLAYERS)

#define _Group_GetColor(%0) \
	(_:(YSI_gGroupData[_:(%0)][E_GROUP_DATA_FLAGS] & e_GROUP_FLAGS_COLOR) | 0xAA)

#define _Group_SetColor(%0,%1) \
	(YSI_gGroupData[_:(%0)][E_GROUP_DATA_FLAGS] = (YSI_gGroupData[_:(%0)][E_GROUP_DATA_FLAGS] & ~e_GROUP_FLAGS_COLOR) | (e_GROUP_FLAGS:(%1) & e_GROUP_FLAGS_COLOR))

#define _Group_GetGang(%0) \
	(bool:(YSI_gGroupData[_:(%0)][E_GROUP_DATA_FLAGS] & e_GROUP_FLAGS_GANG))

#define _Group_LetGang(%0) \
	(YSI_gGroupData[_:(%0)][E_GROUP_DATA_FLAGS] |= e_GROUP_FLAGS_GANG)

#define _Group_VetGang(%0) \
	(YSI_gGroupData[_:(%0)][E_GROUP_DATA_FLAGS] &= ~e_GROUP_FLAGS_GANG)

#define _Group_IsActive(%0) \
	(YSI_gGroupData[_:(%0)][E_GROUP_DATA_FLAGS] & e_GROUP_FLAGS_ACTIVE)

//#define _Group_IsValid(%0) 
//	(0 <= (%0) < _MAX_GROUPS && Group_IsActive(%0))

#define _Group_IsValid(%0) \
	((_:GROUP_MASK<=_:(%0)<=_:GROUP_GLOBAL)&&(_Group_IsActive(GROUP_TEMP_FIX(%0))))

//#define Group_IsActive(%0) 
//	(YSI_gGroupData[_:GROUP_FIX(%0)][E_GROUP_DATA_FLAGS] & e_GROUP_FLAGS_ACTIVE)

/*----------------------------------------------------------------------------*\
Function:
	GROUP_ADD
Params:
	Group:g - Group to add the following items to.
Return:
	-
Notes:
	This sets up a temporary environment, during which all items are ONLY added
	to the specified group and no others, with no complex extra code required.
\*----------------------------------------------------------------------------*/

#define GROUP_ADD<%0> for(J@=_Group_AddInternal(1,(%0));J@;J@=_Group_AddInternal(0,(%0)))

stock _Group_AddInternal(a, Group:g)
{
	//printf("_Group_AddInternal %d %d", a, _:g);
	if (_Group_IsValid(g))
	{
		broadcastfunc __Group_AddInternal(a, _:GROUP_TEMP_FIX(g));
		return a;
	}
	else
	{
		return 0;
	}
}

static remotefunc void:__Group_AddInternal(a,g)
{
	GROUP_CHAIN?<YSI_g_sNextInitFunc>(-1, a, g);
}

/*----------------------------------------------------------------------------*\
Function:
	Group_IsValid
Params:
	Group:g - Group to check.
Return:
	bool: - Is the group active and valid?
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign bool:Group_IsValid(Group:g);

global bool:Group_IsValid(Group:g)
{
	//GROUP_FIX(g);
	return _Group_IsValid(g);
}

/*----------------------------------------------------------------------------*\
Function:
	OnScriptInit
Params:
	-
Return:
	-
Notes:
	Finds three functions by prefix:
	
	_yGI - An init function to set up a script using groups.
	_yGA - An add function called when a new group is created.
	_yGU - An update function called when a player's groups change.
\*----------------------------------------------------------------------------*/

public OnScriptInit()
{
	P:1("Group_OnScriptInit called");
	state YSI_has_groups:y;
	// Set up the global groups.
	#if !(YSIM_HAS_MASTER && (_YSIM_IS_STUB || _YSIM_IS_CLIENT))
		#if _YSIM_IS_CLOUD
			if (_YCM@y)
		#endif
			{
				P:5("Group_OnScriptInit: Master");
				Iter_Init(GroupPlayers);
				strpack(YSI_gGroupData[_MAX_GROUPS][E_GROUP_DATA_NAME], YSI_g_scGlobalName, MAX_GROUP_NAME char);
				YSI_gGroupData[_MAX_GROUPS][E_GROUP_DATA_FLAGS] = e_GROUP_FLAGS_ACTIVE | e_GROUP_FLAGS_GLOBAL;
				YSI_gGroupData[_MAX_GROUPS][E_GROUP_DATA_HASH] = YHash(YSI_g_scGlobalName);
				Bit_Let(YSI_g_sChildGroups[_MAX_GROUPS], _:_MAX_GROUPS);
			}
	#endif
	// Call the other group init functions.
	new
		ni = AMX_GetPublicPointerPrefix(0, YSI_g_sNextInitFunc, _A<_yGI>),
		na = AMX_GetPublicPointerPrefix(0, YSI_g_sNextAddFunc, _A<_yGA>),
		nu = AMX_GetPublicPointerPrefix(0, YSI_g_sNextUpdFunc, _A<_yGU>);
	//printf("Group_OnScriptInit: %d, %d, %d", ni, na, nu);
	P:5("Group_OnScriptInit: %d, %d, %d", ni, na, nu);
	GROUP_CHAIN?<YSI_g_sNextInitFunc>(ni, na, nu);
	//CallLocalFunction("_Group_SpecialInit", "");
	return _Group_SpecialInit();
}

#undef OnScriptInit
#define OnScriptInit(%0) _Group_SpecialInit(%0) <_ALS_:hooked>
forward _Group_SpecialInit();public _Group_SpecialInit()<_ALS_:unhooked>{return 1;}public _Group_SpecialInit()<>{return 1;}

/*----------------------------------------------------------------------------*\
Function:
	OnScriptExit
Params:
	-
Return:
	-
Notes:
	Destroy all this script's groups.  This is an instance of "_YSI_SpecialExit"
	which can't be y_hooked and is called after (almost) every other callback,
	at least after every one controlled via y_scriptinit.
\*----------------------------------------------------------------------------*/

public _YSI_SpecialExit()
{
	_Group_TryRemove();
	//CallLocalFunction("_Group_SpecialExit", "");
	return _Group_SpecialExit();
}

#undef _YSI_SpecialExit
#define _YSI_SpecialExit(%0) _Group_SpecialExit(%0) <_ALS_:hooked>
forward _Group_SpecialExit();public _Group_SpecialExit()<_ALS_:unhooked>{return 1;}public _Group_SpecialExit()<>{return 1;}

/*----------------------------------------------------------------------------*\
FunctiOn:
	_Group_TryRemove
Params:
	-
Return:
	-
Notes:
	Removes all groups purely owned by the calling script.
\*----------------------------------------------------------------------------*/

@foreign void:_Group_TryRemove();

@global void:_Group_TryRemove()
{
	for (new i = 0; i != _MAX_GROUPS; ++i)
	{
		MASTER_REMOVE<i>
		MASTER_EMPTY<i>
		{
			broadcastfunc _Group_Destroy(i, Iter_InternalArray(GroupPlayers[i]), Iter_InternalSize(GroupPlayers[i]));
			YSI_gGroupData[i][E_GROUP_DATA_FLAGS] = e_GROUP_FLAGS:0;
			YSI_gGroupData[i][E_GROUP_DATA_HASH] = 0;
			Iter_Clear(GroupPlayers[i]);
		}
	}
	//return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	OnPlayerDisconnect
Params:
	playerid - The player that left.
	reason - Why they left (unused).
Return:
	-
Notes:
	Removes this player from all groups.  Unfortunately there's no way to
	combine multiple iterator removals to improve their efficiency - currently
	they have to loop through all previous ones to find the one to modify to
	skip over that player.  I did debate updating foreach to doubly-linked
	lists for this reason - that would make reverse traversal and removal faster
	by doubling memory consumption but only very slightly affecting adds.
\*----------------------------------------------------------------------------*/

hook OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	P:2("hook OnPlayerDisconnect called: %d, %d", playerid, reason);
	// Can't - can't what?  Don't stop typing mid comment!
	//foreach (new Group:g : PlayerGroups(playerid))
	#if !(YSIM_HAS_MASTER && (_YSIM_IS_STUB || _YSIM_IS_CLIENT))
		#if _YSIM_IS_CLOUD
			if (_YCM@y)
		#endif
			{
				foreach (new g : Bits(YSI_gGroupPlayers[playerid]))
				{
					Iter_Remove(GroupPlayers[g], playerid);
					Bit_Vet(YSI_gGroupPlayers[playerid], g);
				}
			}
	#endif
	// Remove them from everything ever.
	//static const
	//	BitArray:scEmpty<_MAX_GROUPS_G>;
	//GROUP_CHAIN?<YSI_g_sNextUpdFunc>(playerid, YSI_gGroupPlayers[p], scEmpty);
	YSI_gGroupPlayers[playerid] = YSI_g_cEmptyGroups;
}

/*----------------------------------------------------------------------------*\
Function:
	OnPlayerConnect
Params:
	playerid - The player that joined.
Return:
	-
Notes:
	The player may not have ACTUALLY joined the server, they may have just been
	added to this newly loaded script.  In that case we need to initialise the
	locally stored group data to the new data.  Of course, if this script is the
	group master, then we need to do significantly more!  This is more complex
	than other scripts with master as they don't have some things to do in non-
	master scripts as well, whereas this one does.
\*----------------------------------------------------------------------------*/

hook OnPlayerConnect9(playerid)
{
	#if !(YSIM_HAS_MASTER && (_YSIM_IS_STUB || _YSIM_IS_CLIENT))
		#if _YSIM_IS_CLOUD
			if (_YCM@y)
		#endif
			{
				P:6("Group_OnPlayerConnect: Master %d", playerid);
				// Is master.  ALWAYS reset all players - if they start screwing
				// around with loading orders then that's their own fault!
				//_Group_InitPlayer(playerid);
				broadcastfunc _Group_FakePlayer(playerid, YSI_g_sChildGroups[_MAX_GROUPS], bits<_MAX_GROUPS_G>);
			}
		#if _YSIM_IS_CLOUD
			else
		#endif
	#endif
	#if YSIM_HAS_MASTER
			{
				P:6("Group_OnPlayerConnect: Slave %d", playerid);
				static const
					BitArray:scF<_MAX_GROUPS_G> = {Bit:-1, ...};
				_GROUPS_CHECK_ANY(scF, YSI_gGroupPlayers[playerid])
				{
					// Already been set up - return.
					return 1;
				}
				//_Group_
				_Group_InitPlayer(playerid, _@);
			}
	#endif
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	_Group_InitPlayer
Params:
	p - The player that joined.
	master - The script that just started.
Return:
	-
Notes:
	Request all a player's groups from the master system.
\*----------------------------------------------------------------------------*/

foreign void:_Group_InitPlayer(p, master);

global void:_Group_InitPlayer(p, master)
{
	targetfunc _Group_FakePlayer<master>(p, YSI_gGroupPlayers[p], bits<_MAX_GROUPS_G>);
	//Set their groups to the global group.
	//foreach (new i : Bits(YSI_gGroupData[_MAX_GROUPS]))
	//{
	//	Iter_Add(GroupPlayers[i], playerid);
	//}
	//YSI_gGroupPlayers[playerid] = YSI_gGroupData[_MAX_GROUPS];
	//return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	_Group_SetSome
Params:
	playerid - Player to add to multiple groups.
	group - Parent group to add to.
Return:
	A new array of groups.
Notes:
	Takes a group and adds a player to that group and every child group of
	which they are not already a member.
\*----------------------------------------------------------------------------*/

static stock Bit:_Group_SetSome(playerid, group)
{
	// If you overflow this stack there is something VERY wrong!  The manual
	// stack is intended to help us combat very long inheritance chains.  This
	// code also neatly ignores recursion by only doing any one group if the
	// player doesn't already have it.
	static
		sStack[128][2];//,
		//BitArray:n<_MAX_GROUPS_G>;
	new
		g = -1,
		s = 0;
	YSI_gTempGroups = YSI_gGroupPlayers[playerid];
	Bit_Let(YSI_gTempGroups, group);
	for ( ; ; )
	{
		g = Bits@YSII_Ag(YSI_g_sChildGroups[group], g, bits<_MAX_GROUPS_G>);
		if (g == -1)
		{
			// Finished this child group, pop off the stack.
			if (s--)
			{
				g = sStack[s][0];
				group = sStack[s][1];
			}
			else break;
		}
		else if (!Bit_Get(YSI_gTempGroups, g)) //_Group_HasPlayer(g, playerid))
		{
			// This player isn't in this group, add them.
			Bit_Let(YSI_gTempGroups, g);
			sStack[s][0] = g;
			sStack[s][1] = group;
			++s;
			group = g;
			g = -1;
		}
	}
	return YSI_gTempGroups;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_SetPlayer
Params:
	Group:g - Group to modify.
	p - Player to modify the group for.
	bool:s - Add the player (true) or remove them (false).
Return:
	-
Notes:
	Will in some cases update all settings, unless they are being added through
	a recursive call due to being added to child groups.
	
	There is an internal version that ONLY adds them to the group and DOES NOT
	update any of their other settings.  As a result it has less checks in it.
\*----------------------------------------------------------------------------*/

foreign void:Group_SetPlayer(Group:g,p,bool:s);

global void:Group_SetPlayer(Group:g,p,bool:s)
{
	if (_Group_IsValid(g) && 0 <= p < MAX_PLAYERS)
	{
		GROUP_FIX(g);
		//static
		//	BitArray:n<_MAX_GROUPS_G>;
		if (s)
		{
			if (!_Group_HasPlayer(g, p))
			{
				// Added to a group they don't already have.  Make a new list of
				// groups they're in, taking in to account the new groups
				// hierarchy and pass that new array about.
				broadcastfunc _Group_SetPlayer(p, _Group_SetSome(p, _:g), sizeof (YSI_gTempGroups));
				return; //1;
			}
		}
		else
		{
			if (_Group_HasPlayer(g, p))
			{
				YSI_gTempGroups = YSI_gGroupPlayers[p];
				Bit_Vet(YSI_gTempGroups, _:g);
				broadcastfunc _Group_SetPlayer(p, YSI_gTempGroups, sizeof (YSI_gTempGroups));
				return; //1;
			}
		}
	}
	//return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	_Group_FakePlayer
Params:
	p - Player who connected.
	Bit:g[] - The player's new groups.
	s - Size of "g".
Return:
	-
Notes:
	Pretend the player is in all the groups they won't be in shortly so that
	they have a complete blank slate when they connect - the system KNOWS they
	are not in some groups and are in others.
	
	Uses an unusual size in "g" to reduce the string length.
\*----------------------------------------------------------------------------*/

static remotefunc void:_Group_FakePlayer(p,Bit:g[sizeof RG@],s)
{
	for (new i = 0; i != s; ++i)
	{
		// Set their current groups to the inverse of what they are now in.
		YSI_gGroupPlayers[p][i] = ~g[i];
	}
	_Group_SetPlayer(p, g, s);
}
//#endinput
/*----------------------------------------------------------------------------*\
Function:
	_Group_SetPlayer
Params:
	p - Player to set.
	Bit:g[bits<_MAX_GROUPS_G>] - The player's new groups.
	s - Size of "g".
Return:
	-
Notes:
	Pass a list of groups that the player is now in or not in.  This is a
	complete replacement for their existing list of groups, and so multiple
	updates can be done at once.
\*----------------------------------------------------------------------------*/

static remotefunc void:_Group_SetPlayer(p, Bit:g[sizeof RG@], s)
{
	#pragma unused s
	#if !(YSIM_HAS_MASTER && (_YSIM_IS_STUB || _YSIM_IS_CLIENT))
		#if _YSIM_IS_CLOUD
			if (_YCM@y)
		#endif
			{
				P:2("Group_SetPlayer called: %i, %s, %s, %i", p, Bit_Display(YSI_gGroupPlayers[p]), Bit_Display(g), s);
				// http://supertech.csail.mit.edu/papers/debruijn.pdf
				static const
					scDeBruijn[] =
						{
							0,  1,  28, 2,  29, 14, 24, 3,  30, 22, 20, 15, 25, 17, 4,  8, 
							31, 27, 13, 23, 21, 19, 16, 7,  26, 12, 18, 6,  11, 5,  10, 9
						};
				new
					Bit:cur,
					Bit:exor,
					Bit:bit,
					group;
				//sOld = YSI_gGroupPlayers[p];
				for (new i = 0; i != sizeof (g); ++i)
				{
					// Get the difference between the old and new groups.
					cur = YSI_gGroupPlayers[p][i];
					exor = g[i] ^ cur;
					P:7("_Group_SetPlayer: Loop %d %d %d", i, _:cur, _:exor);
					// Low-level bit twiddling.
					while ((bit = exor & -exor))
					{
						group = i * cellbits + (scDeBruijn[(_:bit * 0x077CB531) >>> 27]);
						P:7("_Group_SetPlayer: Add %d %d %d", p, group, _:(cur & bit));
						if (cur & bit)
						{
							// Used to have this group, now don't.
							//printf("=============");
							//printf("%d", Iter_Count(GroupPlayers[group]));
							Iter_Remove(GroupPlayers[group], p);
							//printf("%d", Iter_Count(GroupPlayers[group]));
							//printf("=============");
						}
						else
						{
							// Didn't have this group, now do.
							Iter_Add(GroupPlayers[group], p);
						}
						exor ^= bit;
					}
				}
			}
	#endif
	#pragma tabsize 4
	//printf("chain");
	GROUP_CHAIN?<YSI_g_sNextUpdFunc>(p, YSI_gGroupPlayers[p], g);
	// NOW save the new version, after everything else has had a chance to
	// update according to the changes.
	YSI_gGroupPlayers[p] = g;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_SetBalancedInternal
Params:
	p - Player to add to the smallest group.
	Group:gs[] - An array of possible groups.
	c - The number of USED items in the array.
Return:
	The group they have been added to.
Notes:
	Chains the call with "Group_SetPlayer" to use its hierarchy code.
\*----------------------------------------------------------------------------*/

foreign Group:Group_SetBalancedInternal(p,Group:gs[],c);

global Group:Group_SetBalancedInternal(p,Group:gs[],c)
{
	// Find which of the listed groups has the least players in.
	//#pragma unused s
	new
		count = cellmax,
		Group:id = INVALID_GROUP;
	for (new i = 0; i != c; ++i)
	{
		// Find the group with the least players.
		new
			gi = _:gs[i];
		if (_Group_IsValid(Group:gi))
		{
			gi = _:GROUP_TEMP_FIX(Group:gi);
			//GROUP_FIX(gi);
			new
				cc = Iter_Count(GroupPlayers[gi]);
			if (Bit_Get(YSI_gGroupPlayers[p], gi))
			{
				// The player is already in this group - prefer it to others.
				--cc;
			}
			if (cc < count)
			{
				count = cc;
				id = Group:gi;
			}
		}
	}
	Group_SetPlayer(id, p, true);
	return id;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_SetBalanced
Params:
	playerid - Player to put in one of a number of groups
	{Group, _}:... - Either an array size then array, or a list of groups.
Return:
	-
Notes:
	Puts a player in whichever of the given groups currently has the least
	players.
\*----------------------------------------------------------------------------*/

stock Group:Group_SetBalanced(playerid, {Group, _}:...)
{
	if (!(0 < p <= MAX_PLAYERS))
	{
		return INVALID_GROUP;
	}
	new
		Group:possible[_MAX_GROUPS_G],
		count = numargs();
	switch (count)
	{
		case 1, 2:
		{
			P:W("Group_AddBalanced requires at least 2 groups or an array.");
		}
		case 3:
		{
			new
				third = getarg(2);
			if (third & _:GROUP_MASK)
			{
				// Two groups.
				possible[0] = Group:getarg(1);
				possible[1] = Group:third;
				return Group_SetBalancedInternal(playerid, possible, 2);
			}
			else
			{
				third = min(third, _MAX_GROUPS_G);
				// Array of groups.
				for (new i = 0; i != third; ++i)
				{
					possible[i] = getarg(1, i);
				}
				return Group_SetBalancedInternal(playerid, possible, third);
			}
		}
		default:
		{
			for (new i = 1; i != count; ++i)
			{
				possible[i - 1] = getarg(i);
			}
			return Group_SetBalancedInternal(playerid, possible, count - 1);
		}
	}
	return INVALID_GROUP;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_GetPlayer
Params:
	Group:g - Group to check.
	p - Player to check.
Return:
	Is this player in this group?
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign bool:Group_GetPlayer(Group:g,p);

global bool:Group_GetPlayer(Group:g,p)
{
	P:2("bool:Group_GetPlayer called: %i, %i", _:g, p);
	if (_Group_IsValid(g) && 0 <= p < MAX_PLAYERS)
	{
		GROUP_FIX(g);
		return Bit_Get(YSI_gGroupPlayers[p], _:g);
		//Bit_Set(YSI_gGroupPlayers[g], p, s, bits<MAX_PLAYERS>);
	}
	return false;
}

/*----------------------------------------------------------------------------*\
Function:
	
Params:
	Group:g - Group to set the name of.
	string:n[] - The new name of the group.
Return:
	-
Notes:
	Sets the name of a group.
\*----------------------------------------------------------------------------*/

foreign void:Group_SetName(Group:g,string:n[]);

global void:Group_SetName(Group:g,string:n[])
{
	P:2("Group_SetName called: %i, \"%s\"", _:g, n);
	if (_Group_IsValid(g))
	{
		GROUP_FIX(g);
		if (isnull(n))
		{
			YSI_gGroupData[_:g][E_GROUP_DATA_NAME][0] = 0;
			YSI_gGroupData[_:g][E_GROUP_DATA_HASH] = 0;
		}
		else
		{
			strpack(YSI_gGroupData[_:g][E_GROUP_DATA_NAME], n, MAX_GROUP_NAME char);
			YSI_gGroupData[_:g][E_GROUP_DATA_HASH] = YHash(n);
		}
	}
	//return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_GetName
Params:
	Group:g - Group to get the name of.
Return:
	string:
Notes:
	Gets the name of a group.
\*----------------------------------------------------------------------------*/

foreign string:Group_GetName(Group:g);

global string:Group_GetName(Group:g)
{
	P:2("Group_GetName called: %i", _:g);
	new
		ret[YSI_MAX_STRING];
	if (_Group_IsValid(g))
	{
		//return Bit_Get(YSI_gGroupPlayers[g], p);
		//Bit_Set(YSI_gGroupPlayers[g], p, s, bits<MAX_PLAYERS>);
		strunpack(ret, YSI_gGroupData[_:GROUP_TEMP_FIX(g)][E_GROUP_DATA_NAME], YSI_MAX_STRING);
	}
	return ret;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_GetID
Params:
	string:name[] - Name of a group to get.
Return:
	Group: - The ID of the group with this name.
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign Group:Group_GetID(string:name[]);

global Group:Group_GetID(string:name[])
{
	P:2("Group_GetID called: %s", name);
	new
		i,
		hash = YHash(name);
	while (i != _MAX_GROUPS)
	{
		if (_Group_IsActive(i) && YSI_gGroupData[i][E_GROUP_DATA_HASH] == hash)
		{
			break;
		}
		++i;
	}
	if (i == _MAX_GROUPS) return INVALID_GROUP;
	return Group:i | GROUP_MASK;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_SetGane
Params:
	Group:g - Group to set for.
	bool:n - Set or not?
Return:
	-
Notes:
	I actually can't remember what the "Gang" setting on a group does - I don't
	think it actually does anything in the latest code version!
\*----------------------------------------------------------------------------*/

foreign void:Group_SetGang(Group:g,bool:n);

global void:Group_SetGang(Group:g,bool:n)
{
	P:2("Group_SetGang called: %i, %i", _:g, n);
	if (_Group_IsValid(g))
	{
		if (n)
		{
			_Group_LetGang(GROUP_TEMP_FIX(g));
		}
		else
		{
			_Group_VetGang(GROUP_TEMP_FIX(g));
		}
	}
	//return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_GetGang
Params:
	Group:g - Group to get the gang status of.
Return:
	bool:
Notes:
	I still don't remember what this once did!
\*----------------------------------------------------------------------------*/

foreign bool:Group_GetGang(Group:g);

global bool:Group_GetGang(Group:g)
{
	P:2("bool:Group_GetGang called: %i", _:g);
	if (_Group_IsValid(g))
	{
		return _Group_GetGang(GROUP_TEMP_FIX(g));
	}
	return false;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_SetColor
	Group_SetColour
Params:
	Group:g - The group to set the colour of.
	c - An RGBA colour.
Return:
	-
Notes:
	This colour is not actually currently used anywhere.
\*----------------------------------------------------------------------------*/

foreign void:Group_SetColour(Group:g,c);

global void:Group_SetColour(Group:g,c)
{
	P:2("Group_SetColour called: %i, %i", _:g, c);
	if (_Group_IsValid(g))
	{
		GROUP_FIX(g);
		_Group_SetColor(g, c);
	}
	//return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_GetColor
	Group_GetColour
Params:
	Group:g - The group to get the colour of.
Return:
	An RGBA colour.
Notes:
	This colour is not actually currently used anywhere.
\*----------------------------------------------------------------------------*/

foreign Group_GetColour(Group:g);

global Group_GetColour(Group:g)
{
	P:2("Group_GetColour called: %i", _:g);
	if (_Group_IsValid(g))
	{
		return _Group_GetColor(GROUP_TEMP_FIX(g));
		//Bit_Set(YSI_gGroupPlayers[g], p, s, bits<MAX_PLAYERS>);
	}
	return 0;
}

#define Group_SetColor Group_SetColour
#define Group_GetColor Group_GetColour

/*----------------------------------------------------------------------------*\
Function:
	Group_GetCount
Params:
	Group:g - The group to get the membership for.
Return:
	The number of players in the group.
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign Group_GetCount(Group:g);

global Group_GetCount(Group:g)
{
	P:2("Group_GetCount called: %i", _:g);
	if (_Group_IsValid(g))
	{
		GROUP_FIX(g);
		return Iter_Count(GroupPlayers[_:g]);
	}
	return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_Create
Params:
	string:name[] - The optional name of the new group.
Return:
	The group ID with a tag of "Group:", or "INVALID_GROUP".
Notes:
	Group_Create - Local function to detect and "NULL"ify empty strings.
	_Group_Create - Global function that does most of the work.
	_Group_CreateChain - Remote function that updates all master scripts with
		the new group's existence.
\*----------------------------------------------------------------------------*/

@foreign Group:_Group_Create(string:name[]);

@global Group:_Group_Create(string:name[])
{
	P:2("Group:Group_Create called: \"%s\"", name);
	P:2("Group_Create called in %d", _@);
	new
		i;
	if (!isnull(name))
	{
		// Get a group of the same name if it already exists.
		i = _:Group_GetID(name);
		if (i != _:INVALID_GROUP)
		{
			MASTER_ADD<_:GROUP_TEMP_FIX(Group:i)>
			return Group:i;
		}
	}
	i = 0;
	while (i != _MAX_GROUPS && _Group_IsActive(i))
	{
		++i;
	}
	if (i == _MAX_GROUPS) return INVALID_GROUP;
	if (isnull(name))
	{
		YSI_gGroupData[i][E_GROUP_DATA_NAME][0] = 0;
		YSI_gGroupData[i][E_GROUP_DATA_FLAGS] = e_GROUP_FLAGS_TEMP | e_GROUP_FLAGS_ACTIVE;
		YSI_gGroupData[i][E_GROUP_DATA_HASH] = 0;
	}
	else
	{
		strpack(YSI_gGroupData[i][E_GROUP_DATA_NAME], name, MAX_GROUP_NAME char);
		YSI_gGroupData[i][E_GROUP_DATA_FLAGS] = e_GROUP_FLAGS_ACTIVE;
		if (!(YSI_gGroupData[i][E_GROUP_DATA_HASH] = YHash(name)))
		{
			P:E("Group %d has hash 0.", name);
		}
	}
	MASTER_SET<i>
	++YSI_g_sGroupCount;
	// Reset the group members iterator.
	//Iter_Clear(GroupPlayers[i]);
	// Set the child groups to only this group - this is in theory recursive,
	// but actually isn't.
	//static const
	//	BitArray:scEmpty<_MAX_GROUPS_G>;
	YSI_g_sChildGroups[i] = YSI_g_cEmptyGroups;
	Bit_Let(YSI_g_sChildGroups[i], i);
	//PA_Init(YSI_gGroupPlayers[i]);
	// Add this group to other groups.
	// TODO: CHAIN.  Done
	// TODO: Spread data over all other scripts.  NO.
	broadcastfunc _Group_CreateChain(Group:i);
	return Group:i | GROUP_MASK;
}

static remotefunc void:_Group_CreateChain(Group:g)
{
	GROUP_CHAIN?<YSI_g_sNextAddFunc>(g);
}

stock Group:Group_Create(string:name[] = "")
{
	if (name[0])
	{
		return _Group_Create(name);
	}
	else
	{
		return _Group_Create(NULL);
	}
}

/*----------------------------------------------------------------------------*\
Function:
	Group_Destroy
Params:
	Group:group - Group to destroy from the system.
Return:
	-
Notes:
	-
\*----------------------------------------------------------------------------*/

// Added for the fun of it.
foreign void:Group_Destroy(Group:group);

global void:Group_Destroy(Group:group)
{
	// TODO: Remove this group from all players and all other groups.
	P:2("Group_Destroy called: %i", _:group);
	P:2("Group_Destroy called in %d", _@);
	// You can't destroy the global group.
	if (_Group_IsValid(group) && group != GROUP_GLOBAL)
	{
		GROUP_FIX(group);
		broadcastfunc _Group_Destroy(_:group, Iter_InternalArray(GroupPlayers[_:group]), Iter_InternalSize(GroupPlayers[_:group]));
		YSI_gGroupData[_:group][E_GROUP_DATA_FLAGS] = e_GROUP_FLAGS:0;
		YSI_gGroupData[_:group][E_GROUP_DATA_HASH] = 0;
		Iter_Clear(GroupPlayers[_:group]);
		//return 1;
	}
	//return 0;
}

static remotefunc void:_Group_Destroy(g, gp@YSII_Ag[MAX_PLAYERS + 1], s)
{
	#pragma unused s
	new
		ps = Bit_Slot(g),
		Bit:pm = ~Bit_Mask(g);
	//static
	//	BitArray:sOld<_MAX_GROUPS_G>;
	if (YSI_g_sNextUpdFunc)
	{
		// Update all players who were in this group as they may have lost
		// some permissions.  This is the simplest update because we don't
		// need to worry about the effect of removing this group on the
		// players' memberships in other groups.  Maybe they were added to
		// that other group as a direct result of being added to this group,
		// but maybe they weren't - there's no way to know!
		// Check it!  Local parameter iterator!
		foreach (new p : gp)
		{
			// TODO: SOMETHING!
			YSI_gTempGroups = YSI_gGroupPlayers[p];
			// If these parameters were the other way round I could do this:
			//GROUP_CHAIN<YSI_g_sNextUpdFunc>(p, (YSI_gGroupPlayers[p], YSI_gGroupPlayers[p][ps] &= pm), YSI_gGroupPlayers[p]);
			// But they're currently not so I can't.
			GROUP_CHAIN<YSI_g_sNextUpdFunc>(p, YSI_gTempGroups, YSI_gGroupPlayers[p]);
			YSI_gGroupPlayers[p][ps] &= pm;
		}
	}
	else
	{
		foreach (new p : gp)
		{
			// Remove all players from this group.
			YSI_gGroupPlayers[p][ps] &= pm;
		}
	}
}

/*----------------------------------------------------------------------------*\
Function:
	Group@YSII_Ag
Params:
	Group:group - Group to loop over.
	start - Last value.
Return:
	The next player.
Notes:
	Internal implementation of the "Group()" iterator for "foreach".  Returns
	all the players in a group one at a time.  Now just wraps the "GroupPlayers"
	iterator that is only stored in the GROUP master script.
\*----------------------------------------------------------------------------*/

foreign Group@YSII_Ag(Group:group, start);

global Group@YSII_Ag(Group:group, start)
{
	return Iter_Next(GroupPlayers[_:GROUP_TEMP_FIX(group)], start);
}

/*----------------------------------------------------------------------------*\
Function:
	_Y_G@C_0
	_Y_G@C_1
	_Y_G@C_2
	_Y_G@C_3
Params:
	func - Function to call.
	... - 0, 1, 2, or 3 parameters.
Return:
	0 - ALWAYS zero to make "_gchain" work properly.
Notes:
	Basically function indirection, call a function through a pointer and use
	the compiler to figure out the assembly to generate instead of having a
	run-time loop inside a single instance of this function.  Using just one
	macro ("GROUP_CHAIN") one of these four functions are selected and called.
	Adding more is fairly trivial too, the parameters are just:
	
	#emit PUSH.S     <16 + n * 4>
	#emit PUSH.S     ...
	#emit PUSH.S     20
	#emit PUSH.S     16
	#emit PUSH.C     <n * 4>
	
\*----------------------------------------------------------------------------*/

stock _Y_G@C_0(func)
{
	#emit PUSH.C     0
	#emit LCTRL      6
	#emit ADD.C      28
	#emit PUSH.pri
	#emit LOAD.S.pri func
	#emit SCTRL      6
	// ALWAYS return 0;
	return 0;
}

stock _Y_G@C_1(func, GLOBAL_TAG_TYPES:...)
{
	#emit PUSH.S     16
	#emit PUSH.C     4
	#emit LCTRL      6
	#emit ADD.C      28
	#emit PUSH.pri
	#emit LOAD.S.pri func
	#emit SCTRL      6
	//#emit RETN
	return 0;
}

stock _Y_G@C_2(func, GLOBAL_TAG_TYPES:...)
{
	#emit PUSH.S     20
	#emit PUSH.S     16
	#emit PUSH.C     8
	#emit LCTRL      6
	#emit ADD.C      28
	#emit PUSH.pri
	#emit LOAD.S.pri func
	#emit SCTRL      6
	//#emit RETN
	return 0;
}

stock _Y_G@C_3(func, GLOBAL_TAG_TYPES:...)
{
	#emit PUSH.S     24
	#emit PUSH.S     20
	#emit PUSH.S     16
	#emit PUSH.C     12
	#emit LCTRL      6
	#emit ADD.C      28
	#emit PUSH.pri
	#emit LOAD.S.pri func
	#emit SCTRL      6
	//#emit RETN
	return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_SetGroup
Params:
	Group:g - Group to set for.
	el - Element to set.
	bool:s - Set or unset?
Return:
	-
Notes:
	IMPORTANT NOTE: Groups are SLIGHTLY different to other systems - if you
	REMOVE a group from another group then players WILL NOT be removed from
	that second group, or any child groups.
\*----------------------------------------------------------------------------*/

foreign void:Group_SetGroup(Group:g,Group:el,bool:s);

global void:Group_SetGroup(Group:g,Group:el,bool:s)
{
	P:2(#Group_SetGroup " called: %i, %i, %i", _:g, _:el, s);
	// Set wether a group can use this item.
	if (g != el && _Group_IsValid(g) && _Group_IsValid(el))
	{
		GROUP_FIX(g);
		GROUP_FIX(el);
		if (s)
		{
			if (Bit_Get(YSI_g_sChildGroups[_:g], _:el))
			{
				// Child is already part of parent.
				return; //1;
			}
			Bit_Let(YSI_g_sChildGroups[_:g], _:el);
			foreach (new p : GroupPlayers[_:g])
			{
				if (!_Group_HasPlayer(el, p))
				{
					broadcastfunc _Group_SetPlayer(p, _Group_SetSome(p, _:el), bits<_MAX_GROUPS_G>);
				}
			}
			//return 1;
		}
		else
		{
			if (Bit_Get(YSI_g_sChildGroups[_:g], _:el))
			{
				// Child is a part of parent.
				Bit_Vet(YSI_g_sChildGroups[_:g], _:el);
				//return 1;
			}
			// DO NOT REMOVE PLAYERS.
			//return 1;
		}
	}
	//return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	Group_SetGlobalGroup
Params:
	el - Element to set.
	bool:s - Set or unset?
Return:
	-
Notes:
	If "s" is true, then one element is added to the global group.  False it is
	removed.
\*----------------------------------------------------------------------------*/

foreign void:Group_SetGlobalGroup(Group:el,bool:s);

global void:Group_SetGlobalGroup(Group:el,bool:s)
{
	P:2(#Group_SetGlobalGroup " called: %i, %i", _:el, s);
	Group_SetGroup(GROUP_GLOBAL, el, s);
}

/*----------------------------------------------------------------------------*\
Function:
	Group_Get...
Params:
	Group:g - Group to get from.
	Group:el - Element to get.
Return:
	bool: Does the group have the element?
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign bool:Group_GetGroup(Group:g,Group:el);

global bool:Group_GetGroup(Group:g,Group:el)
{
	P:2(#Group_GetGroup " called: %i, %i", _:g, _:el);
	return (GROUP_MASK <= el <= GROUP_GLOBAL && GROUP_MASK <= g <= GROUP_GLOBAL && Bit_Get(YSI_g_sChildGroups[_:GROUP_TEMP_FIX(g)], _:GROUP_TEMP_FIX(el)));
}

/*----------------------------------------------------------------------------*\
Function:
	Group_GetGlobal...
Params:
	Group:el - Element to get.
Return:
	bool: Does the global group have the element?
Notes:
	-
\*----------------------------------------------------------------------------*/

foreign Group_GetGlobalGroup(Group:el);

global Group_GetGlobalGroup(Group:el)
{
	P:2(#Group_GetGlobalGroup " called: %i", _:el);
	return Group_GetGroup(GROUP_GLOBAL, el);
}

#define _YSIM_RESET_USER
#include "..\y_master"
