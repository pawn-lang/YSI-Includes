/**--------------------------------------------------------------------------**\
					==============================
					 y_hooks - Hook any callback!
					==============================
Description:
	Automatically hooks any callbacks with a very simple syntax.
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
	
	The Original Code is the SA:MP callback hooks include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2008
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
	Thanks:
		JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
		Peter, Cam - Support.
		ZeeX, g_aSlice/Slice, Popz, others - Very productive conversations.
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
	2.0
Changelog:
	25/02/12:
		Extracted most of the code to a separate file.
	17/03/11:
		Second complete re-write using another new technique.  Now VERY fast!
		Updated OnPlayerUpdate code using Google63's SCTRL jump code.
	06/08/10:
		First version
</remarks>
\**--------------------------------------------------------------------------**/

#include "..\YSI_Internal\y_compilerpass"
#if AUTO_INCLUDE_GUARD
	#if !defined _inc_y_hooks
		#error Did you do <YSI/y_hooks> instead of the required <YSI\y_hooks>?
	#endif
	#undef _inc_y_hooks
#endif

// Multiple includes!
#include "..\YSI_Internal\y_unique"

#if defined _INC_y_hooks
	#endinput
#endif
#define _INC_y_hooks

#if defined YSI_TESTS
	#define _Y_HOOKS_STATIC
#else
	#define _Y_HOOKS_STATIC static
#endif

#include "..\YSI_Internal\y_unique"
#include "..\YSI_Core\y_cell"
#include "..\YSI_Core\y_utils"
#include "..\YSI_Storage\y_amx"
#include "..\YSI_Core\y_als"

#include "..\YSI_Internal\y_cgen"

#include "..\amx\asm"
//asm"

#include "y_hooks/impl"

#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_hooks/tests"
	// Get some new IDs.
	//#include "..\YSI_Internal\y_unique"
#endif

