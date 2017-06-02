/**--------------------------------------------------------------------------**\
					===============================
					 y_va2 - Enhanced vararg code!
					===============================
Description:
	This library provides a new macro - the triple underscore (___) which fully
	passes all of a function's parameters on to another function.
	
	This is a replacement for all other solutions like y_va.
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
	
	The Original Code is the YSI vararg include.
	
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
	01/06/17:
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
Callbacks:
	-
Definitions:
	-
Enums:
	-
Macros:
	___ - Passes all variable arguments to another function.
Tags:
	-
Variables:
	Global:
		-
	Static:
		-
Commands:
	-
Compile options:
	-
Operators:
	-
\**--------------------------------------------------------------------------**/

#if defined _INC_y_va2
	#endinput
#endif
#define _INC_y_va2

#if 0

	// Example:
	stock MyPrintf(const format[], {Float, File, _}:...)
	{
		// The triple underscore is used to mirror the triple dots in the
		// function definition.  You can't easily tell it is three from a
		// glance, but it is.
		printf(format, ___1); // Or `___(1)`.
		print("Printed many things");
		return 42;
	}

#endif

//#define va_args<%0> %0
#define ___ YVA2_DummyPush(0)
// For optional parameter skips.
#define YVA2_DummyPush(%0)(%1) YVA2_DummyPush((%0),(%1) * 4)

// Shortcuts.
#define ___0 ___(0)
#define ___1 ___(1)
#define ___2 ___(2)
#define ___3 ___(3)
#define ___4 ___(4)
#define ___5 ___(5)
#define ___6 ___(6)
#define ___7 ___(7)
#define ___8 ___(8)
#define ___9 ___(9)

#if defined YSI_TESTS
	#include "..\YSI_Data\y_foreach"
#endif

#include "..\YSI_Internal\y_version"
#include "..\YSI_Internal\y_funcinc"
#include "..\YSI_Core\y_utils"
#include "..\YSI_Coding\y_hooks"

#include "y_va2/impl"

#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_va2/tests"
#endif

