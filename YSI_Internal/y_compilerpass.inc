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
#elseif __Pawn == 0x030A
	#define AUTO_INCLUDE_GUARD 0
#elseif __Pawn >= 0x0300
	#define AUTO_INCLUDE_GUARD 1
#else
	#error YSI does not yet support PAWN 2.0/1.0
#endif

