/*
				             ======================
				              YSI - Master Include
				             ======================
Description:
	Handles distribution of control of code segments across all running scripts
	with YSI to avoid conflicts of checkpoint streamers etc and allow features
	like "/commands" displaying all commands on the server.
	
	Now fully autonomous - to use the master system simply define which one you
	want and include the script:
	
	  #define MASTER 14
	  #include "Master"
	
	That will make the current script attempt to make itself the main master -
	you don't need ANY other code for initialisation anywhere (which took a
	while to figure out)...
	
	This is now over 2000 lines of repetitive and complex macros!
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
		Y_Less
		koolk
		JoeBullet/Google63
		g_aSlice/Slice
		Misiur
		samphunter
		tianmeta
		maddinat0r
		spacemud
		Crayder
		Dayvison
		Ahmad45123
		Zeex
		irinel1996
		Yiin-
		Chaprnks
		Konstantinos
		Masterchen09
		Southclaws
		PatchwerkQWER
		m0k1
		paulommu
		udan111
	
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
	0.2
Changelog:
	06/08/10:
		Managed the ultimate - got completely transparent inclusion!
	05/08/10:
		Completed new master system, now does all syncing and clients.
	06/10/09:
		Rewrote using states.
		Added remote function macros.
		Reduced the number of masters to a single one.  It must have them all.
		Vastly simplified the master model - ending the master ends everything.
	06/01/08:
		Added code to not pass data if no other script exists.
	17/11/07:
		Added code for a script to remove itself from the global list.
	11/10/07:
		Not first version but added documentation months late.
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
	RF - Declare a function which may be remote.
	RV - Declare a void function which may be remote.
	RS - Declare an optional callback.
	RFN - Declare an optional callback with no parameters.
	RFC - Declare a slower but shorter function.
	RFP - Declare a function with tags and give recall hints.
	RFPC - Combination of P and C.
	RFCP - Combination of P and C.
Tags:
	-
Variables:
	Global:
		_@ - ID of this script.
	Static:
		-
Commands:
	-
Compile options:
	YSI_NO_MASTER - Don't use the master system.
	YSI_IS_CLIENT - Script is a client only script.
	YSI_IS_SERVER - Script is a server only script.
Operators:
	-
Natives:
	-
**/

#if AUTO_INCLUDE_GUARD
	#undef _inc__stack_push_008
#endif

#undef _YSIM_PUSH_INDEX
#define _YSIM_PUSH_INDEX 9
#if defined _YSIM_STACK_SLOT_8
	#undef _YSIM_STACK_SLOT_8
#endif
#if     _MASTER == 0
	#define _YSIM_STACK_SLOT_8 0
	#endinput
#elseif _MASTER == 1
	#define _YSIM_STACK_SLOT_8 1
	#endinput
#elseif _MASTER == 2
	#define _YSIM_STACK_SLOT_8 2
	#endinput
#elseif _MASTER == 3
	#define _YSIM_STACK_SLOT_8 3
	#endinput
#elseif _MASTER == 4
	#define _YSIM_STACK_SLOT_8 4
	#endinput
#elseif _MASTER == 5
	#define _YSIM_STACK_SLOT_8 5
	#endinput
#elseif _MASTER == 6
	#define _YSIM_STACK_SLOT_8 6
	#endinput
#elseif _MASTER == 7
	#define _YSIM_STACK_SLOT_8 7
	#endinput
#elseif _MASTER == 8
	#define _YSIM_STACK_SLOT_8 8
	#endinput
#elseif _MASTER == 9
	#define _YSIM_STACK_SLOT_8 9
	#endinput
#elseif _MASTER == 10
	#define _YSIM_STACK_SLOT_8 10
	#endinput
#elseif _MASTER == 11
	#define _YSIM_STACK_SLOT_8 11
	#endinput
#elseif _MASTER == 12
	#define _YSIM_STACK_SLOT_8 12
	#endinput
#elseif _MASTER == 13
	#define _YSIM_STACK_SLOT_8 13
	#endinput
#elseif _MASTER == 14
	#define _YSIM_STACK_SLOT_8 14
	#endinput
#elseif _MASTER == 15
	#define _YSIM_STACK_SLOT_8 15
	#endinput
#elseif _MASTER == 16
	#define _YSIM_STACK_SLOT_8 16
	#endinput
#elseif _MASTER == 17
	#define _YSIM_STACK_SLOT_8 17
	#endinput
#elseif _MASTER == 18
	#define _YSIM_STACK_SLOT_8 18
	#endinput
#elseif _MASTER == 19
	#define _YSIM_STACK_SLOT_8 19
	#endinput
#elseif _MASTER == 20
	#define _YSIM_STACK_SLOT_8 20
	#endinput
#elseif _MASTER == 21
	#define _YSIM_STACK_SLOT_8 21
	#endinput
#elseif _MASTER == 22
	#define _YSIM_STACK_SLOT_8 22
	#endinput
#elseif _MASTER == 23
	#define _YSIM_STACK_SLOT_8 23
	#endinput
#elseif _MASTER == 24
	#define _YSIM_STACK_SLOT_8 24
	#endinput
#elseif _MASTER == 25
	#define _YSIM_STACK_SLOT_8 25
	#endinput
#elseif _MASTER == 26
	#define _YSIM_STACK_SLOT_8 26
	#endinput
#elseif _MASTER == 27
	#define _YSIM_STACK_SLOT_8 27
	#endinput
#elseif _MASTER == 28
	#define _YSIM_STACK_SLOT_8 28
	#endinput
#elseif _MASTER == 29
	#define _YSIM_STACK_SLOT_8 29
	#endinput
#elseif _MASTER == 30
	#define _YSIM_STACK_SLOT_8 30
	#endinput
#elseif _MASTER == 31
	#define _YSIM_STACK_SLOT_8 31
	#endinput
#elseif _MASTER == 32
	#define _YSIM_STACK_SLOT_8 32
	#endinput
#elseif _MASTER == 33
	#define _YSIM_STACK_SLOT_8 33
	#endinput
#elseif _MASTER == 34
	#define _YSIM_STACK_SLOT_8 34
	#endinput
#elseif _MASTER == 35
	#define _YSIM_STACK_SLOT_8 35
	#endinput
#elseif _MASTER == 36
	#define _YSIM_STACK_SLOT_8 36
	#endinput
#elseif _MASTER == 37
	#define _YSIM_STACK_SLOT_8 37
	#endinput
#elseif _MASTER == 38
	#define _YSIM_STACK_SLOT_8 38
	#endinput
#elseif _MASTER == 39
	#define _YSIM_STACK_SLOT_8 39
	#endinput
#elseif _MASTER == 40
	#define _YSIM_STACK_SLOT_8 40
	#endinput
#elseif _MASTER == 41
	#define _YSIM_STACK_SLOT_8 41
	#endinput
#elseif _MASTER == 42
	#define _YSIM_STACK_SLOT_8 42
	#endinput
#elseif _MASTER == 43
	#define _YSIM_STACK_SLOT_8 43
	#endinput
#elseif _MASTER == 44
	#define _YSIM_STACK_SLOT_8 44
	#endinput
#elseif _MASTER == 45
	#define _YSIM_STACK_SLOT_8 45
	#endinput
#elseif _MASTER == 46
	#define _YSIM_STACK_SLOT_8 46
	#endinput
#elseif _MASTER == 47
	#define _YSIM_STACK_SLOT_8 47
	#endinput
#elseif _MASTER == 48
	#define _YSIM_STACK_SLOT_8 48
	#endinput
#elseif _MASTER == 49
	#define _YSIM_STACK_SLOT_8 49
	#endinput
#elseif _MASTER == 50
	#define _YSIM_STACK_SLOT_8 50
	#endinput
#elseif _MASTER == 51
	#define _YSIM_STACK_SLOT_8 51
	#endinput
#elseif _MASTER == 52
	#define _YSIM_STACK_SLOT_8 52
	#endinput
#elseif _MASTER == 53
	#define _YSIM_STACK_SLOT_8 53
	#endinput
#elseif _MASTER == 54
	#define _YSIM_STACK_SLOT_8 54
	#endinput
#elseif _MASTER == 55
	#define _YSIM_STACK_SLOT_8 55
	#endinput
#elseif _MASTER == 56
	#define _YSIM_STACK_SLOT_8 56
	#endinput
#elseif _MASTER == 57
	#define _YSIM_STACK_SLOT_8 57
	#endinput
#elseif _MASTER == 58
	#define _YSIM_STACK_SLOT_8 58
	#endinput
#elseif _MASTER == 59
	#define _YSIM_STACK_SLOT_8 59
	#endinput
#elseif _MASTER == 60
	#define _YSIM_STACK_SLOT_8 60
	#endinput
#elseif _MASTER == 61
	#define _YSIM_STACK_SLOT_8 61
	#endinput
#elseif _MASTER == 62
	#define _YSIM_STACK_SLOT_8 62
	#endinput
#elseif _MASTER == 63
	#define _YSIM_STACK_SLOT_8 63
	#endinput
#endif

