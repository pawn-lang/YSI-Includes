/*----------------------------------------------------------------------------*\
                             =====================
                              YSI - Strip Numbers
                             =====================
Description:
	Removes tag overrides which are actually numbers.  This allows for:
		
		uvar g_a[MAX_PLAYERS][E_SOME_ENUM];
		uvar g_b[MAX_PLAYERS][42];
		
	Without stripping you would end with code doing "42:0" or getting a tag
	mismatch on "E_SOME_ENUM", both of which are problems.
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
	
	The Original Code is the YSI master systems include.
	
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
	-
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
		-
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
\*----------------------------------------------------------------------------*/

#define STRIP_NUMBERS:%0|||%1:%2||| _:@S0:@S1:@S2:@S3:@S4:@S5:@S6:@S7:@S8:@S9:@S_:%0|||%1:%2|||

#define @S0:@S1:@S2:@S3:@S4:@S5:@S6:@S7:@S8:@S9:@S_:%0|||0%1:%2||| %0[%2]
#define @S1:@S2:@S3:@S4:@S5:@S6:@S7:@S8:@S9:@S_:%0|||1%1:%2||| %0[%2]
#define @S2:@S3:@S4:@S5:@S6:@S7:@S8:@S9:@S_:%0|||2%1:%2||| %0[%2]
#define @S3:@S4:@S5:@S6:@S7:@S8:@S9:@S_:%0|||3%1:%2||| %0[%2]
#define @S4:@S5:@S6:@S7:@S8:@S9:@S_:%0|||4%1:%2||| %0[%2]
#define @S5:@S6:@S7:@S8:@S9:@S_:%0|||5%1:%2||| %0[%2]
#define @S6:@S7:@S8:@S9:@S_:%0|||6%1:%2||| %0[%2]
#define @S7:@S8:@S9:@S_:%0|||7%1:%2||| %0[%2]
#define @S8:@S9:@S_:%0|||8%1:%2||| %0[%2]
#define @S9:@S_:%0|||9%1:%2||| %0[%2]
#define @S_:%0|||%1:%2||| %0[%1:%2]
