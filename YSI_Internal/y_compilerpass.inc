/**--------------------------------------------------------------------------**\
					================================
					Y Sever Includes - Compiler Pass
					================================
Description:
	Detect which pass the compiler is on.  Used by y_groups to include code that
	might be needed before it is known if it is needed (it can be dumped later).
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
	14/04/13:
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
\**--------------------------------------------------------------------------**/

#if defined _INC_y_compilerpass
	#endinput
#endif
#define _INC_y_compilerpass

#if defined __COMPILER_SECOND_PASS
	#define __COMPILER_PASS (1)
#else
	#define __COMPILER_PASS (0)
#endif
#define COMPILER_1ST_PASS (__COMPILER_PASS == (0))
#define COMPILER_2ND_PASS (__COMPILER_PASS == (1))
#define COMPILER_FIRST_PASS  COMPILER_1ST_PASS
#define COMPILER_SECOND_PASS COMPILER_2ND_PASS
static stock __COMPILER_SECOND_PASS() {}

#if __Pawn >= 0x0400
	#error YSI does not yet support PAWN 4.0
#elseif __Pawn < 0x0300
	#error YSI does not yet support PAWN 2.0/1.0
#endif

#if !defined __compat
	#define __compat 1
#endif

#if __Pawn == 0x030A && !__compat
	#define AUTO_INCLUDE_GUARD 0
#else
	#define AUTO_INCLUDE_GUARD 1
#endif

#if __Pawn == 0x030A
	#define NESTED_ELLIPSIS
	//#define __only_one_fix_string_parameter:%8(%0,%1)%8(%9) (%0)%8(%0)
	//#define __mayb_raw_fix_string_parameter:("%0"%1)%8(%9)
	//#define __neither_fix_string_parameter:(%0)
	//#define YSI_STRING_RETURN(%0) return __only_one_fix_string_parameter:__mayb_raw_fix_string_parameter:(%0)__neither_fix_string_parameter:(%0)
	#define __only_one_fix_string_parameter:%8(%0,%1) (%0)
	#define YSI_STRING_RETURN(%0) return __only_one_fix_string_parameter:(%0)
	// Disable the recursion warning in the Russian compiler.
	#pragma warning push
	#pragma warning disable 207
	#pragma disablerecursion
	#pragma warning pop
#else
	#define __only_one_fix_string_parameter:%8(%0,%1) (%0)
	#define YSI_STRING_RETURN(%0) __FixStringReturn(%0);return (__only_one_fix_string_parameter:(%0))
	#define __FixStringReturn("%0"%1);return%8(%8:(%3)) return $
	//#define __FixStringDummy[YSI_MAX_STRING,%1] __FixStringDummy[%1]
	
	/**----------------------------------------------------------------------**\
	<summary>FixStringReturn</summary>
	<param name="str">String to return.</param>
	<param name="size">Size of the string.</param>
	<param name="dummy">Ignored parameter for raw string given sizes.</param>
	<returns>
		string
	</returns>
	<remarks>
		The old compiler has a very annoying bug where returning a string from a
		function that takes variable parameters will not work correctly.  This
		is because string returns are done with a secret extra parameter but it
		is not correctly selected when the count is unknown or variable.
	</remarks>
	\**----------------------------------------------------------------------**/
	
	#include "y_funcinc"
	
	stock __FixStringReturn(const str[], size = sizeof (str), dummy = 0)
	{
		#pragma unused dummy
		#emit PUSH.S       size   // Push the first parameter.
		#emit PUSH.S       str    // Push the second parameter.
		#emit LOAD.S.alt   0      // Load the previous frame pointer.
		#emit MOVE.pri            // Copy the pointer.
		#emit ADD.C        8      // Get the pointer to the parameter count.
		#emit LOAD.I              // Load the parameter count.
		#emit ADD.C        12     // Adjust for the function header size.
		#emit ADD                 // Get the pointer to after the parameters.
		#emit LOAD.I              // Load the pointer in the (secret) parameter.
		#emit PUSH.pri            // Push the destination.
		#emit MOVE.alt            // Make a copy of the pointer.
		#emit ZERO.pri            // `pri = 0`.
		#emit STOR.I              // Set the first cell of the target to NULL.
		#emit PUSH.C       12     // Push the parameters for `strcpy`.
		#emit SYSREQ.C     strcat // Call `strcat`.
		#emit LOAD.S.pri   0      // Reload the previous frame pointer.
		#emit SCTRL        4      // Wipe out the stack.
		#emit SCTRL        5      // Wipe out the frame (go to parent context).
		#emit RETN                // Return (now within the parent context).
		return 0;
	}
	
#endif

