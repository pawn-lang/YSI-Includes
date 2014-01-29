/**--------------------------------------------------------------------------**\
					==============================
					 y_als - Useful codes for ALS
					==============================
Description:
	Provides a number of macros for making ALS (Advanced Library System)
	callback hooking simpler.
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
	
	The Original Code is the YSI ALS include.
	
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
	29/04/11:
		Added "call" macro to make testing easier.
	21/10/10:
		First version
</remarks>
\**--------------------------------------------------------------------------**/

#if !defined _INC_y_als
	
	#include "..\YSI_Internal\y_version"
	#include "y_utils"
	#include "..\YSI_Server\y_scriptinit"
	#include "..\YSI_Data\y_bit"
	#include "..\YSI_Internal\y_shortfunc"
	
	#include "y_als/impl"
	
	#if defined YSI_TESTS
		#include "..\YSI_Coding\y_va"
		
		#include "y_testing"
		#include "y_als/tests"
	#endif
	#define _INC_y_als
#endif

// Allow multiple inclusions.
#include "..\YSI_Internal\y_compilerpass"
#if AUTO_INCLUDE_GUARD
	#if !defined _inc_y_als
		#error Did you do <YSI/y_als> instead of the required <YSI\y_als>?
	#endif
	#undef _inc_y_als
#endif

#if !defined ALS_MAKE
	#if defined ALS_PREFIX
		#error Use ALS_MAKE not ALS_PREFIX
	#endif
	//&&&
	#define ALS_MAKE<%0...%1> %0Mode_%1
#endif
