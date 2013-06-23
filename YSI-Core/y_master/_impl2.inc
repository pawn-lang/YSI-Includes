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

#undef _inc__impl2

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
#endif

#undef YSIM_STORED_SETTINGS

// Check for non-unique masters here.
#if defined YSIM_DEFINED && !defined _YSIM_OVERRIDE && !defined YSIM_LIBRARY_OVERRIDE
	//#error Non-unique master used.
	#if _MASTER == 0
		#error Master 0 already defined (Non-unique master used).
	#elseif _MASTER == 1
		#error Master 1 already defined (Non-unique master used).
	#elseif _MASTER == 2
		#error Master 2 already defined (Non-unique master used).
	#elseif _MASTER == 3
		#error Master 3 already defined (Non-unique master used).
	#elseif _MASTER == 4
		#error Master 4 already defined (Non-unique master used).
	#elseif _MASTER == 5
		#error Master 5 already defined (Non-unique master used).
	#elseif _MASTER == 6
		#error Master 6 already defined (Non-unique master used).
	#elseif _MASTER == 7
		#error Master 7 already defined (Non-unique master used).
	#elseif _MASTER == 8
		#error Master 8 already defined (Non-unique master used).
	#elseif _MASTER == 9
		#error Master 9 already defined (Non-unique master used).
	#elseif _MASTER == 10
		#error Master 10 already defined (Non-unique master used).
	#elseif _MASTER == 11
		#error Master 11 already defined (Non-unique master used).
	#elseif _MASTER == 12
		#error Master 12 already defined (Non-unique master used).
	#elseif _MASTER == 13
		#error Master 13 already defined (Non-unique master used).
	#elseif _MASTER == 14
		#error Master 14 already defined (Non-unique master used).
	#elseif _MASTER == 15
		#error Master 15 already defined (Non-unique master used).
	#elseif _MASTER == 16
		#error Master 16 already defined (Non-unique master used).
	#elseif _MASTER == 17
		#error Master 17 already defined (Non-unique master used).
	#elseif _MASTER == 18
		#error Master 18 already defined (Non-unique master used).
	#elseif _MASTER == 19
		#error Master 19 already defined (Non-unique master used).
	#elseif _MASTER == 20
		#error Master 20 already defined (Non-unique master used).
	#elseif _MASTER == 21
		#error Master 21 already defined (Non-unique master used).
	#elseif _MASTER == 22
		#error Master 22 already defined (Non-unique master used).
	#elseif _MASTER == 23
		#error Master 23 already defined (Non-unique master used).
	#elseif _MASTER == 24
		#error Master 24 already defined (Non-unique master used).
	#elseif _MASTER == 25
		#error Master 25 already defined (Non-unique master used).
	#else
		#error Non-unique (and invalid) master used.
	#endif
#endif

#if YSIM_HAS_MASTER && !_YSIM_IS_CLIENT && !_YSIM_IS_STUB && (!defined YSIM_DEFINED || defined YSIM_LIBRARY_OVERRIDE)
	// FIRST declare the next callback in the chain.
	//#if defined FILTERSCRIPT
	//	public OnFilterScriptInit()
	//#else
	//	public OnGameModeInit()
	//#endif
	stock
		_E_YCM:_YCM@ = _E_YCM@u;
	
	public OnMasterSystemInit()
	{
		P:1(#_YCM "_OGM");
		// THEN rename the callbacks.
		#if defined _YCM_CALLBACK
			#undef _YCM_CALLBACK
		#endif
		#if _MASTER == 0
			#define _YCM_CALLBACK a@OnScriptInit
		#elseif _MASTER == 1
			#define _YCM_CALLBACK b@OnScriptInit
		#elseif _MASTER == 2
			#define _YCM_CALLBACK c@OnScriptInit
		#elseif _MASTER == 3
			#define _YCM_CALLBACK d@OnScriptInit
		#elseif _MASTER == 4
			#define _YCM_CALLBACK e@OnScriptInit
		#elseif _MASTER == 5
			#define _YCM_CALLBACK f@OnScriptInit
		#elseif _MASTER == 6
			#define _YCM_CALLBACK g@OnScriptInit
		#elseif _MASTER == 7
			#define _YCM_CALLBACK h@OnScriptInit
		#elseif _MASTER == 8
			#define _YCM_CALLBACK i@OnScriptInit
		#elseif _MASTER == 9
			#define _YCM_CALLBACK j@OnScriptInit
		#elseif _MASTER == 10
			#define _YCM_CALLBACK k@OnScriptInit
		#elseif _MASTER == 11
			#define _YCM_CALLBACK l@OnScriptInit
		#elseif _MASTER == 12
			#define _YCM_CALLBACK m@OnScriptInit
		#elseif _MASTER == 13
			#define _YCM_CALLBACK n@OnScriptInit
		#elseif _MASTER == 14
			#define _YCM_CALLBACK o@OnScriptInit
		#elseif _MASTER == 15
			#define _YCM_CALLBACK p@OnScriptInit
		#elseif _MASTER == 16
			#define _YCM_CALLBACK q@OnScriptInit
		#elseif _MASTER == 17
			#define _YCM_CALLBACK r@OnScriptInit
		#elseif _MASTER == 18
			#define _YCM_CALLBACK s@OnScriptInit
		#elseif _MASTER == 19
			#define _YCM_CALLBACK t@OnScriptInit
		#elseif _MASTER == 20
			#define _YCM_CALLBACK u@OnScriptInit
		#elseif _MASTER == 21
			#define _YCM_CALLBACK v@OnScriptInit
		#elseif _MASTER == 22
			#define _YCM_CALLBACK w@OnScriptInit
		#elseif _MASTER == 23
			#define _YCM_CALLBACK x@OnScriptInit
		#elseif _MASTER == 24
			#define _YCM_CALLBACK y@OnScriptInit
		#elseif _MASTER == 25
			#define _YCM_CALLBACK z@OnScriptInit
		#endif
		#if _YSIM_IS_SERVER
			// Steal the master.
			_Master_Get(#_YCM, true);
			_YCM@ = _E_YCM@y;
			// Determine the next unique name.
			CallRemoteFunction(#_YCM, "");
		#elseif _YSIM_IS_CLOUD
			// See if this script should be master.
			if (_Master_Get(#_YCM))
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
		// FINALLY call the new next one.
		//CallLocalFunction(#_YCM_CALLBACK, "");
		#if _MASTER == 0
			#if defined a@OnScriptInit
				return a@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 1
			#if defined b@OnScriptInit
				return b@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 2
			#if defined c@OnScriptInit
				return c@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 3
			#if defined d@OnScriptInit
				return d@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 4
			#if defined e@OnScriptInit
				return e@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 5
			#if defined f@OnScriptInit
				return f@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 6
			#if defined g@OnScriptInit
				return g@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 7
			#if defined h@OnScriptInit
				return h@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 8
			#if defined i@OnScriptInit
				return i@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 9
			#if defined j@OnScriptInit
				return j@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 10
			#if defined k@OnScriptInit
				return k@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 11
			#if defined l@OnScriptInit
				return l@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 12
			#if defined m@OnScriptInit
				return m@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 13
			#if defined n@OnScriptInit
				return n@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 14
			#if defined o@OnScriptInit
				return o@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 15
			#if defined p@OnScriptInit
				return p@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 16
			#if defined q@OnScriptInit
				return q@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 17
			#if defined r@OnScriptInit
				return r@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 18
			#if defined s@OnScriptInit
				return s@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 19
			#if defined t@OnScriptInit
				return t@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 20
			#if defined u@OnScriptInit
				return u@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 21
			#if defined v@OnScriptInit
				return v@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 22
			#if defined w@OnScriptInit
				return w@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 23
			#if defined x@OnScriptInit
				return x@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 24
			#if defined y@OnScriptInit
				return y@OnScriptInit();
			#else
				return 1;
			#endif
		#elseif _MASTER == 25
			#if defined z@OnScriptInit
				return z@OnScriptInit();
			#else
				return 1;
			#endif
		#endif
	}
	
	// Don't need extra checks here as we KNOW it is already defined.
	#undef OnMasterSystemInit
	#define OnMasterSystemInit _YCM_CALLBACK
	#if _MASTER == 0
		#if defined a@OnScriptInit
			forward a@OnScriptInit();
		#endif
	#elseif _MASTER == 1
		#if defined b@OnScriptInit
			forward b@OnScriptInit();
		#endif
	#elseif _MASTER == 2
		#if defined c@OnScriptInit
			forward c@OnScriptInit();
		#endif
	#elseif _MASTER == 3
		#if defined d@OnScriptInit
			forward d@OnScriptInit();
		#endif
	#elseif _MASTER == 4
		#if defined e@OnScriptInit
			forward e@OnScriptInit();
		#endif
	#elseif _MASTER == 5
		#if defined f@OnScriptInit
			forward f@OnScriptInit();
		#endif
	#elseif _MASTER == 6
		#if defined g@OnScriptInit
			forward g@OnScriptInit();
		#endif
	#elseif _MASTER == 7
		#if defined h@OnScriptInit
			forward h@OnScriptInit();
		#endif
	#elseif _MASTER == 8
		#if defined i@OnScriptInit
			forward i@OnScriptInit();
		#endif
	#elseif _MASTER == 9
		#if defined j@OnScriptInit
			forward j@OnScriptInit();
		#endif
	#elseif _MASTER == 10
		#if defined k@OnScriptInit
			forward k@OnScriptInit();
		#endif
	#elseif _MASTER == 11
		#if defined l@OnScriptInit
			forward l@OnScriptInit();
		#endif
	#elseif _MASTER == 12
		#if defined m@OnScriptInit
			forward m@OnScriptInit();
		#endif
	#elseif _MASTER == 13
		#if defined n@OnScriptInit
			forward n@OnScriptInit();
		#endif
	#elseif _MASTER == 14
		#if defined o@OnScriptInit
			forward o@OnScriptInit();
		#endif
	#elseif _MASTER == 15
		#if defined p@OnScriptInit
			forward p@OnScriptInit();
		#endif
	#elseif _MASTER == 16
		#if defined q@OnScriptInit
			forward q@OnScriptInit();
		#endif
	#elseif _MASTER == 17
		#if defined r@OnScriptInit
			forward r@OnScriptInit();
		#endif
	#elseif _MASTER == 18
		#if defined s@OnScriptInit
			forward s@OnScriptInit();
		#endif
	#elseif _MASTER == 19
		#if defined t@OnScriptInit
			forward t@OnScriptInit();
		#endif
	#elseif _MASTER == 20
		#if defined u@OnScriptInit
			forward u@OnScriptInit();
		#endif
	#elseif _MASTER == 21
		#if defined v@OnScriptInit
			forward v@OnScriptInit();
		#endif
	#elseif _MASTER == 22
		#if defined w@OnScriptInit
			forward w@OnScriptInit();
		#endif
	#elseif _MASTER == 23
		#if defined x@OnScriptInit
			forward x@OnScriptInit();
		#endif
	#elseif _MASTER == 24
		#if defined y@OnScriptInit
			forward y@OnScriptInit();
		#endif
	#elseif _MASTER == 25
		#if defined z@OnScriptInit
			forward z@OnScriptInit();
		#endif
	#endif
#endif

// The code below is now deprecated in favour of foreign/global!
// There are the following remote function definitions:
// 
// RF - A basic function.
// RF@p - A function with special parameters which need passing hints.
// RF@c - A function with lots of paramteres that needs special code.
// RF@v - A function with no return value.
// RF@t - A function with a tag result.
// RC - A callback function.
// RH - A y_hooks hook.
// RS - Return a string.
// 
// 
// Supported combinations:
// 
// pc, cp
// pcv, pvc, cpv, cvp, vpc, vcp
// pv, vp
// cv, vc
// cpt ctp pct ptc tcp tpc
// ct tc
// pt tp
// 
// p and c are for special parameter sets, n is for no parameters, so those two
// groups can never be mixed together.  t is for tag result and v is for no
// return, so they can never be used together.
// 
// Note that the callback thing won't work with OnPlayerCommandText as it has a
// different default return to everything else.
// 

// These parts are redefined every time the master system is included.
#if YSIM_HAS_MASTER
	#if _YSIM_IS_SERVER
		
		#define foreign%0(%1) %0(%1);%0@(%1)
		#define @foreign foreign
		//#define global%0(%1) %0@(%1);public%0@(%1)X@(_:@Zk:%0(_YM@CP:%1,,));%0(%1)
		#define global%0(%1) public%0@(%1)(@Zz:X@(@Zk:_YM@CP:%0(%1,,)));%0(%1)
		
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
	
	#define group_hook%0On%2(%3) _GROUP_MAKE_NAME<hook On%2...>(%3)
	
	#define RC:%0(%1) @yC_%0(%1);@yC_%0(%1)
	
	#define Master_Caller() (_@)
	
	// Shortcut for y_als hooks.
	#define RA:%0_On%1(%3) public On%1(%3)
#endif

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
#undef _MASTER

#if !defined YSIM_DEFINED || defined YSIM_LIBRARY_OVERRIDE
	#if _YSIM_IS_CLOUD || _YSIM_IS_SERVER
		// Define a load of fake functions to cater for the compiler's need to
		// know all the possible states.  y means master, n means not master, m
		// means master system missing, p means previous (ending master), u
		// means sort of uninitialised (though technically initialised).  This
		// also doubles as a handy call in function for resetting masters when a
		// script ends.  Just to clarify - this function is NOT called _YCM,
		// that is a macro which is expanded every time this file is included.
		// m is also now client/stub.
		forward _YCM();
		public _YCM() <_YCM:y>
		{
			P:1("%d: " #_YCM "<y> called", _@);
			if (getproperty(8, #_YCM) != _@)
			{
				// Master, but not.  A server has claimed this.
				state _YCM:n;
				_YCM@ = _E_YCM@n;
			}
			else
			{
				P:2("%d: " #_YCM ":y called", _@);
				// Disable the current mastership.
				state _YCM:p;
				_YCM@ = _E_YCM@p;
				setproperty(8, #_YCM, -1);
				// Called locally to begin the hand off process.
				CallRemoteFunction(#_YCM, "");
			}
		}
		
		public _YCM() <_YCM:n>
		{
			P:1("%d: " #_YCM "<n> called", _@);
			// This has been called remotely from a script which owns the
			// library masterhood (that's the only way this can ever be called).
			if (_Master_Get(#_YCM))
			{
				P:2("%d: " "Got master " #_YCM, _@);
				state _YCM:y;
				_YCM@ = _E_YCM@y;
			}
		}
		
		public _YCM() <_YCM:m, _YCM:p, _YCM:u>
		{
			P:1("%d: " #_YCM "<m,p,u,x> called", _@);
			// Do nothing at all (just define states).
		}
		
		public _YCM() <>
		{
			P:1("%d: " #_YCM "<> called", _@);
			if (_Master_Get(#_YCM))
			{
				P:2("%d: " "Got master " #_YCM, _@);
				state _YCM:y;
				_YCM@ = _E_YCM@y;
			}
			else
			{
				state _YCM:n;
				_YCM@ = _E_YCM@n;
			}
			// Do nothing at all (just define states).
		}
	/*#elseif _YSIM_IS_SERVER
		forward _YCM();
		public _YCM() <_YCM:y>
		{
			P:1("%d: " #_YCM "<y> called", _@);
			// Disable the current mastership.
			state _YCM:p;
			setproperty(8, #_YCM, -1);
			// Called locally to begin the hand off process.
			CallRemoteFunction(#_YCM, "");
		}
		
		public _YCM() <_YCM:n, _YCM:m, _YCM:p, _YCM:u>
		{
			P:1("%d: " #_YCM "<n,m,p,u,x> called", _@);
			// Do nothing at all (just define states).
		}
		
		public _YCM() <>
		{
			P:1("%d: " #_YCM "<> called", _@);
			//_Master_Get(#_YCM, true);
			P:2("%d: " "Got master " #_YCM, _@);
			state _YCM:y;
			// Do nothing at all (just define states).
		}*/
		
	/*#else
		#if _YSIM_IS_CLIENT || _YSIM_IS_STUB
			static stock _YCM() <_YCM:m>
			{
			}
			
			static stock _YCM() <>
			{
			}
		#endif*/
	#elseif YSIM_HAS_MASTER
		stock
			_E_YCM:_YCM@ = _E_YCM@n;
	#else
		stock
			_E_YCM:_YCM@ = _E_YCM@y;
	#endif
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

// Allow YSI scripts to use the extended master system
/*#if defined _YSIM_USED_AUTO
	#undef _YSIM_USED_AUTO
#endif*/

#if defined _YSIM_OVERRIDE
	#undef _YSIM_OVERRIDE
#endif

#if defined YSIM_STORED_SETTINGS
	#undef YSIM_STORED_SETTINGS
#endif

// Clean up the new library definition code.
#if defined _YSIM_LAST_LIBRARY_MASTER
	#undef _YSIM_LAST_LIBRARY_MASTER
#endif

#if defined LIBRARY_MASTER
	#if LIBRARY_MASTER == 0
		#define _YSIM_LAST_LIBRARY_MASTER 0
	#elseif LIBRARY_MASTER == 1
		#define _YSIM_LAST_LIBRARY_MASTER 1
	#elseif LIBRARY_MASTER == 2
		#define _YSIM_LAST_LIBRARY_MASTER 2
	#elseif LIBRARY_MASTER == 3
		#define _YSIM_LAST_LIBRARY_MASTER 3
	#elseif LIBRARY_MASTER == 4
		#define _YSIM_LAST_LIBRARY_MASTER 4
	#elseif LIBRARY_MASTER == 5
		#define _YSIM_LAST_LIBRARY_MASTER 5
	#elseif LIBRARY_MASTER == 6
		#define _YSIM_LAST_LIBRARY_MASTER 6
	#elseif LIBRARY_MASTER == 7
		#define _YSIM_LAST_LIBRARY_MASTER 7
	#elseif LIBRARY_MASTER == 8
		#define _YSIM_LAST_LIBRARY_MASTER 8
	#elseif LIBRARY_MASTER == 9
		#define _YSIM_LAST_LIBRARY_MASTER 9
	#elseif LIBRARY_MASTER == 10
		#define _YSIM_LAST_LIBRARY_MASTER 10
	#elseif LIBRARY_MASTER == 11
		#define _YSIM_LAST_LIBRARY_MASTER 11
	#elseif LIBRARY_MASTER == 12
		#define _YSIM_LAST_LIBRARY_MASTER 12
	#elseif LIBRARY_MASTER == 13
		#define _YSIM_LAST_LIBRARY_MASTER 13
	#elseif LIBRARY_MASTER == 14
		#define _YSIM_LAST_LIBRARY_MASTER 14
	#elseif LIBRARY_MASTER == 15
		#define _YSIM_LAST_LIBRARY_MASTER 15
	#elseif LIBRARY_MASTER == 16
		#define _YSIM_LAST_LIBRARY_MASTER 16
	#elseif LIBRARY_MASTER == 17
		#define _YSIM_LAST_LIBRARY_MASTER 17
	#elseif LIBRARY_MASTER == 18
		#define _YSIM_LAST_LIBRARY_MASTER 18
	#elseif LIBRARY_MASTER == 19
		#define _YSIM_LAST_LIBRARY_MASTER 19
	#elseif LIBRARY_MASTER == 20
		#define _YSIM_LAST_LIBRARY_MASTER 20
	#elseif LIBRARY_MASTER == 21
		#define _YSIM_LAST_LIBRARY_MASTER 21
	#elseif LIBRARY_MASTER == 22
		#define _YSIM_LAST_LIBRARY_MASTER 22
	#elseif LIBRARY_MASTER == 23
		#define _YSIM_LAST_LIBRARY_MASTER 23
	#elseif LIBRARY_MASTER == 24
		#define _YSIM_LAST_LIBRARY_MASTER 24
	#elseif LIBRARY_MASTER == 25
		#define _YSIM_LAST_LIBRARY_MASTER 25
	#endif
	#undef LIBRARY_MASTER
#endif

#if defined YSIM_LIBRARY_OVERRIDE
	#undef YSIM_LIBRARY_OVERRIDE
#endif
