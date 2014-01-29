/**--------------------------------------------------------------------------**\
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
\**--------------------------------------------------------------------------**/

// ALWAYS!  The compiler defines this automatically, don't use it as this is
// included multiple times to handle multiple master systems.
#include "..\YSI_Internal\y_compilerpass"
#if AUTO_INCLUDE_GUARD
	#if !defined _inc_y_master
		#error Did you do <YSI-Core/y_master> instead of the required <YSI-Core\y_master>?
	#endif
	#undef _inc_y_master
#endif

#if !defined _INC_y_master
	#include "..\YSI_Internal\y_version"
	#include "y_debug"
	#include "..\YSI_Coding\y_hooks"
	#include "..\YSI_Internal\y_shortfunc"
	
	#include "..\YSI_Internal\y_natives"
	
	#include "y_master/once"
#endif

#if defined MASTER
	#if defined _MASTER
		// Store the last master.
		#include "y_master\_push_master"
	#endif
#else
	// Get the previous master (or 0 by default).
	#include "y_master\_pop_master"
	
	// Useful debug information (isn't compiled, but shows up with "-l").
	P:C(static stock const _POPPED_MASTER = MASTER;);
#endif

#if MASTER < 0 || MASTER >= MAX_MASTERS
	#error Invalid MASTER ID.
#endif

#if defined _INC_y_master
	// Run at least once - clear previous data.
	#include "y_master\_cleanup"
#endif

// Initialise the current master if it hasn't already been done.  This is split
// in to 5 parts to reduce compilation times in the common case of not that many
// master systems.
#if     MASTER < 16
	#include "y_master\_setup_master_A"
#elseif MASTER < 32
	#include "y_master\_setup_master_B"
#elseif MASTER < 48
	#include "y_master\_setup_master_C"
#else
	#include "y_master\_setup_master_D"
#endif
#undef MASTER

// Include all the correct macro versions for the settings we have just found.
#include "y_master\_impl"

#if !defined _INC_y_master
	// Only include this lot once.
	#define _INC_y_master
	
	#if defined YSI_TESTS
		#include "..\YSI_Core\y_testing"
		// Get the new master.
		#define MASTER 58
		#include "y_master"
		// Include the tests.
		#include "y_master/tests"
		// Pop the master.
		#include "y_master"
	#endif
#endif

