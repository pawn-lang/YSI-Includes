/*----------------------------------------------------------------------------*\
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
\*----------------------------------------------------------------------------*/

#undef _inc_y_overridemaster

#if _YSIM_OVERRIDE == 0
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_0
	#define MASTER                      0
#elseif _YSIM_OVERRIDE == 1
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_1
	#define MASTER                      1
#elseif _YSIM_OVERRIDE == 2
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_2
	#define MASTER                      2
#elseif _YSIM_OVERRIDE == 3
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_3
	#define MASTER                      3
#elseif _YSIM_OVERRIDE == 4
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_4
	#define MASTER                      4
#elseif _YSIM_OVERRIDE == 5
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_5
	#define MASTER                      5
#elseif _YSIM_OVERRIDE == 6
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_6
	#define MASTER                      6
#elseif _YSIM_OVERRIDE == 7
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_7
	#define MASTER                      7
#elseif _YSIM_OVERRIDE == 8
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_8
	#define MASTER                      8
#elseif _YSIM_OVERRIDE == 9
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_9
	#define MASTER                      9
#elseif _YSIM_OVERRIDE == 10
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_10
	#define MASTER                      10
#elseif _YSIM_OVERRIDE == 11
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_11
	#define MASTER                      11
#elseif _YSIM_OVERRIDE == 12
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_12
	#define MASTER                      12
#elseif _YSIM_OVERRIDE == 13
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_13
	#define MASTER                      13
#elseif _YSIM_OVERRIDE == 14
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_14
	#define MASTER                      14
#elseif _YSIM_OVERRIDE == 15
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_15
	#define MASTER                      15
#elseif _YSIM_OVERRIDE == 16
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_16
	#define MASTER                      16
#elseif _YSIM_OVERRIDE == 17
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_17
	#define MASTER                      17
#elseif _YSIM_OVERRIDE == 18
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_18
	#define MASTER                      18
#elseif _YSIM_OVERRIDE == 19
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_19
	#define MASTER                      19
#elseif _YSIM_OVERRIDE == 20
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_20
	#define MASTER                      20
#elseif _YSIM_OVERRIDE == 21
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_21
	#define MASTER                      21
#elseif _YSIM_OVERRIDE == 22
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_22
	#define MASTER                      22
#elseif _YSIM_OVERRIDE == 23
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_23
	#define MASTER                      23
#elseif _YSIM_OVERRIDE == 24
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_24
	#define MASTER                      24
#elseif _YSIM_OVERRIDE == 25
	#define YSIM_STORED_SETTINGS        YSIM_RECALL_25
	#define MASTER                      25
#endif
