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
</remarks>
\**--------------------------------------------------------------------------**/

#undef _inc__impl1

#if defined _YSIM_RESET_USER
	#undef _YSIM_RESET_USER
	//#if !defined _YSIM_MANUAL_SET
	//	#endinput
	//#endif
	//#define MASTER _YSIM_LAST_MANUAL
	#define _YSIM_OVERRIDE _YSIM_LAST_MANUAL
	#include "_override"
#elseif defined MASTER
	#if !defined _YSIM_MANUAL_SET
		#define _YSIM_MANUAL_SET
	#endif
	#if defined _YSIM_LAST_MANUAL
		#undef _YSIM_LAST_MANUAL
	#endif
	#if MASTER == 0
		#define _YSIM_LAST_MANUAL 0
		// This master was already included, the user just didn't realise.
		/*#if defined _YSIM_FAKE_MANUAL_SET
			#define _YSIM_OVERRIDE 0
			#define YSIM_STORED_SETTINGS 0
			#undef _YSIM_FAKE_MANUAL_SET
		#endif*/
	#elseif MASTER == 1
		#define _YSIM_LAST_MANUAL 1
	#elseif MASTER == 2
		#define _YSIM_LAST_MANUAL 2
	#elseif MASTER == 3
		#define _YSIM_LAST_MANUAL 3
	#elseif MASTER == 4
		#define _YSIM_LAST_MANUAL 4
	#elseif MASTER == 5
		#define _YSIM_LAST_MANUAL 5
	#elseif MASTER == 6
		#define _YSIM_LAST_MANUAL 6
	#elseif MASTER == 7
		#define _YSIM_LAST_MANUAL 7
	#elseif MASTER == 8
		#define _YSIM_LAST_MANUAL 8
	#elseif MASTER == 9
		#define _YSIM_LAST_MANUAL 9
	#elseif MASTER == 10
		#define _YSIM_LAST_MANUAL 10
	#elseif MASTER == 11
		#define _YSIM_LAST_MANUAL 11
	#elseif MASTER == 12
		#define _YSIM_LAST_MANUAL 12
	#elseif MASTER == 13
		#define _YSIM_LAST_MANUAL 13
	#elseif MASTER == 14
		#define _YSIM_LAST_MANUAL 14
	#elseif MASTER == 15
		#define _YSIM_LAST_MANUAL 15
	#elseif MASTER == 16
		#define _YSIM_LAST_MANUAL 16
	#elseif MASTER == 17
		#define _YSIM_LAST_MANUAL 17
	#elseif MASTER == 18
		#define _YSIM_LAST_MANUAL 18
	#elseif MASTER == 19
		#define _YSIM_LAST_MANUAL 19
	#elseif MASTER == 20
		#define _YSIM_LAST_MANUAL 20
	#elseif MASTER == 21
		#define _YSIM_LAST_MANUAL 21
	#elseif MASTER == 22
		#define _YSIM_LAST_MANUAL 22
	#elseif MASTER == 23
		#define _YSIM_LAST_MANUAL 23
	#elseif MASTER == 24
		#define _YSIM_LAST_MANUAL 24
	#elseif MASTER == 25
		#define _YSIM_LAST_MANUAL 25
	#endif
#else
	//#define YSIM_STORED_SETTINGS YSIM_RECALL_19
	//#define _YSIM_AUTODEF
	#if defined _YSIM_OVERRIDE
		#include "_override"
		#if !defined MASTER
			#error _YSIM_OVERRIDE used with an invalid master value.
		#endif
	#else
		#tryinclude "_auto"
		#if !defined MASTER
			//#error "You must define a unique MASTER number from 0 to 25."
			#if defined LIBRARY_MASTER
				#define MASTER LIBRARY_MASTER
				#if defined _YSIM_LAST_LIBRARY_MASTER
					#if LIBRARY_MASTER == _YSIM_LAST_LIBRARY_MASTER
						// Not a stub.
						#if defined YSIM_U_ENABLE
							#undef YSIM_U_ENABLE
						#endif
						#if !defined YSIM_U_DISABLE
							#define YSIM_U_DISABLE
						#endif
						#define YSIM_LIBRARY_OVERRIDE
					#else//if !defined YSIM_CORE_LIBRARY
						// A stub.
						#if !defined YSIM_U_ENABLE
							#define YSIM_U_ENABLE
						#endif
						#if defined YSIM_U_DISABLE
							#undef YSIM_U_DISABLE
						#endif
					#endif
				#else
					// A stub.
					#if !defined YSIM_U_ENABLE
						#define YSIM_U_ENABLE
					#endif
					#if defined YSIM_U_DISABLE
						#undef YSIM_U_DISABLE
					#endif
				#endif
			#elseif defined _YSIM_LAST_MANUAL
				#define _YSIM_OVERRIDE _YSIM_LAST_MANUAL
				#include "_override"
			#else
				// Default for user scripts.
				#define MASTER 23
				#if defined _YSIM_LAST_MANUAL
					#undef _YSIM_LAST_MANUAL
				#endif
				#define _YSIM_LAST_MANUAL 23
				#if !defined _YSIM_MANUAL_SET
					#define _YSIM_MANUAL_SET
				#endif
			#endif
			// Detect reinclusions.
			/*#if defined _YSIM_FAKE_MANUAL_SET
				#define _YSIM_OVERRIDE 0
				#define YSIM_STORED_SETTINGS 0
				#undef _YSIM_FAKE_MANUAL_SET
			#endif*/
		#endif
	#endif
#endif

#if MASTER > 25 || MASTER < 0
	// There are some secret ones reserved purely for YSI!  <- Wait, what?
	//#if !defined _YSIM_USED_AUTO || MASTER > 42
	//#if !defined _YSIM_OVERRIDE
		#error Invalid MASTER value, must be between 0 and 25 (inclusive).
	//#endif
#endif

#if defined YSIM_HAS_MASTER
	#undef YSIM_HAS_MASTER
#endif

#if defined _YSIM_IS_CLIENT
	#undef _YSIM_IS_CLIENT
#endif

#if defined _YSIM_IS_SERVER
	#undef _YSIM_IS_SERVER
#endif

#if defined _YSIM_IS_STUB
	#undef _YSIM_IS_STUB
#endif

#if defined _YSIM_IS_CLOUD
	#undef _YSIM_IS_CLOUD
#endif

//#if defined YSIM_NOT_CLIENT
//	#undef YSIM_NOT_CLIENT
//#endif

#if defined _YSIM_OVERRIDE
	// Get stored settings for YSI libraries.  This allows the group system to
	// use the same master settings as another library without being there at
	// the time.
	#if YSIM_STORED_SETTINGS == 0
		#define YSIM_HAS_MASTER 0
	#else
		#define YSIM_HAS_MASTER 1
	#endif
	
	#if YSIM_STORED_SETTINGS == 1
		#define _YSIM_IS_CLIENT 1
	#else
		#define _YSIM_IS_CLIENT 0
	#endif
	
	#if YSIM_STORED_SETTINGS == 2
		#define _YSIM_IS_SERVER 1
	#else
		#define _YSIM_IS_SERVER 0
	#endif
	
	#if YSIM_STORED_SETTINGS == 3
		#define _YSIM_IS_CLOUD 1
	#else
		#define _YSIM_IS_CLOUD 0
	#endif
	
	#if YSIM_STORED_SETTINGS == 4
		#define _YSIM_IS_STUB 1
	#else
		#define _YSIM_IS_STUB 0
	#endif
#else
	// This section of code just got a lot more complicated given that you may
	// want to define "YSI_IS_STUB" for custom libraries AND "YSI_IS_OTHER" for
	// YSI libraries to default to when not stubs.
	#include "_resolve"
	// Can't have a global stub (it makes no sense as all the YSI code exists).
	/*#if defined YSI_IS_STUB
		#error Cannot have a global stub, use YSIM_U_ENABLE.
	#endif
	
	#if defined YSIM_U_ENABLE && !defined YSIM_U_DISABLE
		#define _YSIM_IS_STUB 1
	#else
		#define _YSIM_IS_STUB 0
	#endif*/
#endif
