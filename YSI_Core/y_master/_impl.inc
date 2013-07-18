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

#undef _inc__impl

// Get the settings, regardless of where they came from.
#if     YSIM_STORED_SETTINGS == 0
	#define YSIM_HAS_MASTER 0
	#define _YSIM_IS_CLIENT 0
	#define _YSIM_IS_SERVER 0
	#define _YSIM_IS_CLOUD  0
	#define _YSIM_IS_STUB   0
#elseif YSIM_STORED_SETTINGS == 1
	#define YSIM_HAS_MASTER 1
	#define _YSIM_IS_CLIENT 1
	#define _YSIM_IS_SERVER 0
	#define _YSIM_IS_CLOUD  0
	#define _YSIM_IS_STUB   0
#elseif YSIM_STORED_SETTINGS == 2
	#define YSIM_HAS_MASTER 1
	#define _YSIM_IS_CLIENT 0
	#define _YSIM_IS_SERVER 1
	#define _YSIM_IS_CLOUD  0
	#define _YSIM_IS_STUB   0
#elseif YSIM_STORED_SETTINGS == 3
	#define YSIM_HAS_MASTER 1
	#define _YSIM_IS_CLIENT 0
	#define _YSIM_IS_SERVER 0
	#define _YSIM_IS_CLOUD  1
	#define _YSIM_IS_STUB   0
#elseif YSIM_STORED_SETTINGS == 4
	#define YSIM_HAS_MASTER 1
	#define _YSIM_IS_CLIENT 0
	#define _YSIM_IS_SERVER 0
	#define _YSIM_IS_CLOUD  0
	#define _YSIM_IS_STUB   1
#else
	#error Unknown y_master settings.
#endif

#undef YSIM_STORED_SETTINGS

// Never used, purely for "-l" debugging purposes.
#if !YSIM_HAS_MASTER
	static stock const THE_CURRENT_MASTER_IS_UNSET   = _MASTER;
#elseif _YSIM_IS_CLIENT
	static stock const THE_CURRENT_MASTER_IS_CLIENT  = _MASTER;
#elseif _YSIM_IS_SERVER
	static stock const THE_CURRENT_MASTER_IS_SERVER  = _MASTER;
#elseif _YSIM_IS_CLOUD
	static stock const THE_CURRENT_MASTER_IS_CLOUD   = _MASTER;
#elseif _YSIM_IS_STUB
	static stock const THE_CURRENT_MASTER_IS_STUB    = _MASTER;
#else
	static stock const THE_CURRENT_MASTER_IS_UNKNOWN = _MASTER;
#endif

#if !defined YSIM_DEFINED
	#if (_YSIM_IS_SERVER || _YSIM_IS_CLOUD)
		// Variable to hold the current master state for ease of access.
		stock
			_E_YCM:_YCM@ = _E_YCM@u;
		
		forward _YCM();
		
		static stock Master_GetCurrentMaster()
		{
			#if _YSIM_IS_SERVER
				// Steal the master.
				if (_Master_Get(#_YCM, true))
				{
					// Nothing changed, or we took it without force.
					state _YCM:y;
					_YCM@ = _E_YCM@y;
				}
				else
				{
					// Something changed, tell other scripts.
					state _YCM:u;
					_YCM@ = _E_YCM@u;
					// Determine the next unique name.
					CallRemoteFunction(#_YCM, "");
					// Servers always get all data, so it doesn't matter that
					// for now this is state "u".
				}
			#else //if _YSIM_IS_CLOUD
				// See if this script should be master.
				if (_Master_Get(#_YCM, false))
				{
					P:2("Got master " #_YCM);
					state _YCM:y;
					_YCM@ = _E_YCM@y;
				}
				else
				{
					state _YCM:n;
					_YCM@ = _E_YCM@n;
				}
			#endif
		}
		
		public OnMasterSystemInit()
		{
			P:1(#_YCM "_OGM");
			Master_GetCurrentMaster();
			// THEN rename the callbacks.
			// FINALLY call the new next one.
			#if _MASTER == 0
				#if defined a@OnScriptInit
					a@OnScriptInit();
				#endif
			#elseif _MASTER == 1
				#if defined b@OnScriptInit
					b@OnScriptInit();
				#endif
			#elseif _MASTER == 2
				#if defined c@OnScriptInit
					c@OnScriptInit();
				#endif
			#elseif _MASTER == 3
				#if defined d@OnScriptInit
					d@OnScriptInit();
				#endif
			#elseif _MASTER == 4
				#if defined e@OnScriptInit
					e@OnScriptInit();
				#endif
			#elseif _MASTER == 5
				#if defined f@OnScriptInit
					f@OnScriptInit();
				#endif
			#elseif _MASTER == 6
				#if defined g@OnScriptInit
					g@OnScriptInit();
				#endif
			#elseif _MASTER == 7
				#if defined h@OnScriptInit
					h@OnScriptInit();
				#endif
			#elseif _MASTER == 8
				#if defined i@OnScriptInit
					i@OnScriptInit();
				#endif
			#elseif _MASTER == 9
				#if defined j@OnScriptInit
					j@OnScriptInit();
				#endif
			#elseif _MASTER == 10
				#if defined k@OnScriptInit
					k@OnScriptInit();
				#endif
			#elseif _MASTER == 11
				#if defined l@OnScriptInit
					l@OnScriptInit();
				#endif
			#elseif _MASTER == 12
				#if defined m@OnScriptInit
					m@OnScriptInit();
				#endif
			#elseif _MASTER == 13
				#if defined n@OnScriptInit
					n@OnScriptInit();
				#endif
			#elseif _MASTER == 14
				#if defined o@OnScriptInit
					o@OnScriptInit();
				#endif
			#elseif _MASTER == 15
				#if defined p@OnScriptInit
					p@OnScriptInit();
				#endif
			#elseif _MASTER == 16
				#if defined q@OnScriptInit
					q@OnScriptInit();
				#endif
			#elseif _MASTER == 17
				#if defined r@OnScriptInit
					r@OnScriptInit();
				#endif
			#elseif _MASTER == 18
				#if defined s@OnScriptInit
					s@OnScriptInit();
				#endif
			#elseif _MASTER == 19
				#if defined t@OnScriptInit
					t@OnScriptInit();
				#endif
			#elseif _MASTER == 20
				#if defined u@OnScriptInit
					u@OnScriptInit();
				#endif
			#elseif _MASTER == 21
				#if defined v@OnScriptInit
					v@OnScriptInit();
				#endif
			#elseif _MASTER == 22
				#if defined w@OnScriptInit
					w@OnScriptInit();
				#endif
			#elseif _MASTER == 23
				#if defined x@OnScriptInit
					x@OnScriptInit();
				#endif
			#elseif _MASTER == 24
				#if defined y@OnScriptInit
					y@OnScriptInit();
				#endif
			#elseif _MASTER == 25
				#if defined z@OnScriptInit
					z@OnScriptInit();
				#endif
			#endif
			return 1;
		}
		
		#undef OnMasterSystemInit
		#if _MASTER == 0
			#define OnMasterSystemInit a@OnScriptInit
		#elseif _MASTER == 1
			#define OnMasterSystemInit b@OnScriptInit
		#elseif _MASTER == 2
			#define OnMasterSystemInit c@OnScriptInit
		#elseif _MASTER == 3
			#define OnMasterSystemInit d@OnScriptInit
		#elseif _MASTER == 4
			#define OnMasterSystemInit e@OnScriptInit
		#elseif _MASTER == 5
			#define OnMasterSystemInit f@OnScriptInit
		#elseif _MASTER == 6
			#define OnMasterSystemInit g@OnScriptInit
		#elseif _MASTER == 7
			#define OnMasterSystemInit h@OnScriptInit
		#elseif _MASTER == 8
			#define OnMasterSystemInit i@OnScriptInit
		#elseif _MASTER == 9
			#define OnMasterSystemInit j@OnScriptInit
		#elseif _MASTER == 10
			#define OnMasterSystemInit k@OnScriptInit
		#elseif _MASTER == 11
			#define OnMasterSystemInit l@OnScriptInit
		#elseif _MASTER == 12
			#define OnMasterSystemInit m@OnScriptInit
		#elseif _MASTER == 13
			#define OnMasterSystemInit n@OnScriptInit
		#elseif _MASTER == 14
			#define OnMasterSystemInit o@OnScriptInit
		#elseif _MASTER == 15
			#define OnMasterSystemInit p@OnScriptInit
		#elseif _MASTER == 16
			#define OnMasterSystemInit q@OnScriptInit
		#elseif _MASTER == 17
			#define OnMasterSystemInit r@OnScriptInit
		#elseif _MASTER == 18
			#define OnMasterSystemInit s@OnScriptInit
		#elseif _MASTER == 19
			#define OnMasterSystemInit t@OnScriptInit
		#elseif _MASTER == 20
			#define OnMasterSystemInit u@OnScriptInit
		#elseif _MASTER == 21
			#define OnMasterSystemInit v@OnScriptInit
		#elseif _MASTER == 22
			#define OnMasterSystemInit w@OnScriptInit
		#elseif _MASTER == 23
			#define OnMasterSystemInit x@OnScriptInit
		#elseif _MASTER == 24
			#define OnMasterSystemInit y@OnScriptInit
		#elseif _MASTER == 25
			#define OnMasterSystemInit z@OnScriptInit
		#endif
		
		// Define a load of fake functions to cater for the compiler's need to
		// know all the possible states.  y means master, n means not master, m
		// means master system missing, p means previous (ending master), u
		// means sort of uninitialised (though technically initialised).  This
		// also doubles as a handy call in function for resetting masters when a
		// script ends.  Just to clarify - this function is NOT called _YCM,
		// that is a macro which is expanded every time this file is included.
		// m is also now client/stub.
		
		public _YCM() <_YCM:y>
		{
			P:1("%d: " #_YCM "<y> called, master = %d", _@, getproperty(9, #_YCM));
			if (getproperty(9, #_YCM) == _@)
			{
				P:2(#_YCM " natural end");
				// Disable the current mastership.
				state _YCM:m;
				_YCM@ = _E_YCM@m;
				// Ending normally, relinquish control peacefully.
				setproperty(9, #_YCM, -1);
				// Called locally to begin the hand off process.
				CallRemoteFunction(#_YCM, "");
			}
			else
			{
				P:2(#_YCM " stolen!");
				// Brutally stolen!
				_Master_Relinquish(#_YCM);
			}
			// This is where we need to to the handoff.
			state _YCM:p;
			_YCM@ = _E_YCM@p;
			CallLocalFunction(#MAKE_YCM<HANDOFF_SOURCE...>, "");
			CallLocalFunction(#MAKE_YCM<HANDOFF_SOURCE...Group>, "");
			// Could, in theory, return to be master if the script doesn't end.
			state _YCM:n;
			_YCM@ = _E_YCM@n;
		}
		
		public _YCM() <_YCM:n>
		{
			P:1("%d: " #_YCM "<n> called", _@);
			// This has been called remotely from a script which owns the
			// library masterhood (that's the only way this can ever be called).
			Master_GetCurrentMaster();
		}
		
		public _YCM() <_YCM:m, _YCM:p>
		{
			P:1("%d: " #_YCM "<m,p> called", _@);
			// Do nothing at all (just define states).
		}
		
		public _YCM() <_YCM:u>
		{
			// Finish initialisation.
			P:1("%d: " #_YCM "<u> called", _@);
			state _YCM:y;
			_YCM@ = _E_YCM@y;
		}
		
		public _YCM() <>
		{
			// Do nothing at all (just define states).
			P:E(#_YCM "() <> called");
		}
	#elseif YSIM_HAS_MASTER
		stock
			_E_YCM:_YCM@ = _E_YCM@n;
	#else
		stock
			_E_YCM:_YCM@ = _E_YCM@y;
	#endif
#endif

// These parts are redefined every time the master system is included.
#if YSIM_HAS_MASTER
	#if _YSIM_IS_SERVER
		
		#define foreign%0(%1) %0(%1);%0@(%1)
		#define @foreign foreign
		#define global%0(%1) public%0@(%1)(@Zz:X@(@Zk:_YM@CP:%0(%1,,)));%0(%1)
		#define master_func%0(%1)<%9> %0(%1);public%0(%1)<>{}public%0(%1)<_YCM:%9>
		
		#define RH:On%2(%3) hook On%2(%3)
		
		#define master_hook%0On%2(%3) hook On%2(%3)
		#define master_task%0(%3) task%0(%3)
		#define master_ptask%0(%3) ptask%0(%3)
		#define group_hook%0On%2(%3) _GROUP_MAKE_NAME<hook On%2...>(%3)
		
		#define RT:%0[%1](%2) @yT_%1_%0();@yT_%1_%0()
		
		#if _MASTER == 23
			// Less strict (implicit user master).
			#define RC:%0(%1) @yC_%0(a,b[],c,i);@yC_%0(a,b[],c,i)i==_@&&U@(8,YSIM_RETURN,@_yC%0(a,b,c));@_yC%0(%1);@_yC%0(%1)
		#else
			#define RC:%0(%1) @yC_%0(a,b[],c);@yC_%0(a,b[],c)U@(8,YSIM_RETURN,@_yC%0(a,b,c));@_yC%0(%1);@_yC%0(%1)
		#endif
		
		#define RA:%0_On%1(%3) public On%1(%3)
		
		#define Master_Caller() (((I@=V@(8,YSIM_CALLER))==-1)?(_@):(I@))
	#else
		// Define "foreign" more generically.  If you want "server" or "none"
		// you will need to define this specifically, otherwise you just need to
		// include the master system and then you can use "#tryinclude".  This
		// means that if "global" definitions aren't found this system will try
		// default to STUB.  This is NOT a complete definition - the "@Zu:"
		// definition means that more processing is done (mainly for the
		// definition of the "_YCM:m" function to not give warnings.
		// The "@" versions of the functions are used when the caller's master
		// ID is needed, the normal version is used when it isn't.
		#define @foreign%0(%1) stock%0(%1)<>{new i=Y@();W@(@Zu:#%0@#,_YM@Cj:%1,,);return Z@(i);}%0(%1)<_YCM:m>;%0@(%1)
		
		#define foreign%0(%1) stock%0(%1)<>{W@(@Zu:#%0@#,_YM@Cl:%1,,);return V@(8,YSIM_RETURN);}%0(%1)<_YCM:m>;%0@(%1)
		
		#if _YSIM_IS_CLIENT
			#define global%0(%1) stock %0_(%1)
			
			#define RH:On%2(%3)
			
			#define master_hook%0On%2(%3) stock UNIQUE_FUNCTION<_yH@%2...>(%3)
			#define master_task%0(%3) stock %0(%3)
			#define master_ptask%0(%3) stock %0(%3)
			#define group_hook%0On%2(%3) stock _GROUP_MAKE_NAME<On%2...>(%3)
			#define master_func%0(%1)<%9> static stock %0(%1)
			
			#define RT:%0[%1](%2) stock _yT@%1_%0()
			
			#if _MASTER == 23
				// Less strict (implicit user master).
				#define RC:%0(%1) @yC_%0(a,b[],c,i);@yC_%0(a,b[],c,i)i==_@&&U@(8,YSIM_RETURN,@_yC%0(a,b,c));@_yC%0(%1);@_yC%0(%1)
			#else
				#define RC:%0(%1) static stock _@yC%0()
			#endif
			
			#define RA:%0_On%1(%3) public On%1(%3)ALS_CALL<%1> static stock _%0_%1(%3)
			
			#define Master_Caller() (-1)
		#else
			#if _YSIM_IS_STUB
				#define global%0(%1)
				
				// NOT DEFINED!  Should not be used if this is a stub.
				#define RC
				
				// NOT DEFINED!  Should not be used if this is a stub.
				//#define RC@v
				
				// NOT DEFINED!  Should not be used if this is a stub.
				#define RH
				
				#define master_hook
				#define master_task
				#define master_ptask
				#define master_func
				
				#define group_hook
				
				// NOT DEFINED!  Should not be used if this is a stub.
				#define RT
				
				// Shortcut for y_als hooks.
				#define RA
				
				// NOT DEFINED!  Should not be used if this is a stub.
				#define Master_Caller
			#else
				#define global%0(%1) public%0@(%1)<>{}public%0@(%1)<_YCM:y>(@Zz:X@(@Zk:_YM@CP:%0(%1,,)));stock%0(%1)<_YCM:y>
				
				// Requires the y_hooks library.
				#define RH:On%2(%3) hook On%2(%3)<>return ALS_R_%2;rehook On%2(%3)<_YCM:y>
				
				#define master_hook%0On%2(%3) hook On%2(%3)<>return ALS_R_%2;rehook On%2(%3)<_YCM:y>
				#define master_task%0[%1](%3) task%0[%1](%3)<>return;public%0(%3)<_YCM:y>
				#define master_ptask%0[%1](%3) ptask%0[%1](%3)<>return;public%0(%3)<_YCM:y>
				#define master_func%0(%1)<%9> %0(%1);public%0(%1)<>{}public%0(%1)<_YCM:%9>
				
				#define group_hook%0On%2(%3) _GROUP_MAKE_NAME<hook On%2...>(%3)<>return ALS_R_%2;_GROUP_MAKE_NAME<rehook On%2...>(%3)<_YCM:y>
				
				// Requires the y_timers library.
				#define RT:%0[%1](%2) @yT_%1_%0();@yT_%1_%0()<>{}@yT_%1_%0()<_YCM:y>
				
				#if _MASTER == 23
					// Less strict (implicit user master).
					#define RC:%0(%1) @yC_%0(a,b[],c,i);@yC_%0(a,b[],c,i)i==_@&&U@(8,YSIM_RETURN,@_yC%0(a,b,c));@_yC%0(%1);@_yC%0(%1)
				#else
					// Strict libraries.
					#define RC:%0(%1) @yC_%0(a,b[],c);@yC_%0(a,b[],c)<>{}@yC_%0(a,b[],c)<_YCM:y>U@(8,YSIM_RETURN,@_yC%0(a,b,c));@_yC%0(%1);@_yC%0(%1)
				#endif
				
				// This fixes the most bizzare bug I've ever encountered!
				// Calling a native function and passing a constant string,
				// while in the condition of the ternary operator causes the
				// compiler to try allocate vast amounts of heap space for no
				// apparent reason.
				#define Master_Caller() (((I@=V@(8,YSIM_CALLER))==-1)?(_@):(I@))
				
				#define RA:%0_On%1(%3) public On%1(%3)<>ALS_CALL<%1> public On%1(%3)<_YCM:y>
			#endif
		#endif
	#endif
#else
	
	#define foreign forward
	#define @foreign forward
	#define global stock
	
	#define RT:%0[%1](%2) @yT_%1_%0();@yT_%1_%0()
	
	#define RH:On%2(%3) hook On%2(%3)
	
	#define master_hook%0On%2(%3) hook On%2(%3)
	#define master_task%0(%3) task%0(%3)
	#define master_ptask%0(%3) ptask%0(%3)
	#define master_func%0(%1)<%9> static stock%0(%1)
	
	#define group_hook%0On%2(%3) _GROUP_MAKE_NAME<hook On%2...>(%3)
	
	#define RC:%0(%1) @yC_%0(%1);@yC_%0(%1)
	
	#define Master_Caller() (_@)
	
	// Shortcut for y_als hooks.
	#define RA:%0_On%1(%3) public On%1(%3)
#endif

#if defined YSIM_T_ENABLE
	#undef YSIM_T_ENABLE
#endif

#if defined YSIM_T_DISABLE
	#undef YSIM_T_DISABLE
#endif

#if defined YSIM_C_ENABLE
	#undef YSIM_C_ENABLE
#endif

#if defined YSIM_C_DISABLE
	#undef YSIM_C_DISABLE
#endif

#if defined YSIM_S_ENABLE
	#undef YSIM_S_ENABLE
#endif

#if defined YSIM_S_DISABLE
	#undef YSIM_S_DISABLE
#endif

#if defined YSIM_U_ENABLE
	#undef YSIM_U_ENABLE
#endif

#if defined YSIM_U_DISABLE
	#undef YSIM_U_DISABLE
#endif
