/*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright C 2011
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
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

#if defined _inc__impl
	#undef _inc__impl
#endif

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
		
		#if _MASTER == 0
			// Less strict (implicit user master).
			#define RC:%0(%1) @yC_%0(a,b[],c,i);@yC_%0(a,b[],c,i)i==_@&&U@(8,YSIM_RETURN,@_yC%0(a,b,c));@_yC%0(%1);@_yC%0(%1)
		#else
			#define RC:%0(%1) @yC_%0(a,b[],c);@yC_%0(a,b[],c)U@(8,YSIM_RETURN,@_yC%0(a,b,c));@_yC%0(%1);@_yC%0(%1)
		#endif
		
		#define RA:%0_On%1(%3) public On%1(%3)
		
		#define Master_Caller() (((I@=V@(8,YSIM_CALLER))==0)?(_@):(I@))
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
			
			#if _MASTER == 0
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
				
				#if _MASTER == 0
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
				#define Master_Caller() (((I@=V@(8,YSIM_CALLER))==0)?(_@):(I@))
				
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

#if defined YSIM_DEFINED
	#endinput
#endif

#if !_YSIM_IS_SERVER && !_YSIM_IS_CLOUD
	#if YSIM_HAS_MASTER
		stock
			_E_YCM:_YCM@ = _E_YCM@n;
	#else
		stock
			_E_YCM:_YCM@ = _E_YCM@y;
	#endif
	#endinput
#endif

// Variable to hold the current master state for ease of access.
stock
	_E_YCM:_YCM@ = _E_YCM@u;

forward _YCM();

/*-----------------------------------------------------------------*//**
 * <transition keep="true" target="_YCM : y" />
 * <transition keep="true" target="_YCM : u" />
 * <transition keep="true" target="_YCM : y" />
 * <transition keep="true" target="_YCM : n" />
 *//*----------------------------------------------------------------**/

static stock Master_GetCurrentMaster()
{
	// THIS CODE IS COPIED IN y_classes (mostly).
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
	#undef OnMasterSystemInit
	// THEN rename the callbacks.
	// FINALLY call the new next one.
	#if _MASTER < 16
		#if _MASTER == 0
			#if defined @aOnScriptInit
				@aOnScriptInit();
			#endif
			#define OnMasterSystemInit @aOnScriptInit
		#elseif _MASTER == 1
			#if defined @bOnScriptInit
				@bOnScriptInit();
			#endif
			#define OnMasterSystemInit @bOnScriptInit
		#elseif _MASTER == 2
			#if defined @cOnScriptInit
				@cOnScriptInit();
			#endif
			#define OnMasterSystemInit @cOnScriptInit
		#elseif _MASTER == 3
			#if defined @dOnScriptInit
				@dOnScriptInit();
			#endif
			#define OnMasterSystemInit @dOnScriptInit
		#elseif _MASTER == 4
			#if defined @eOnScriptInit
				@eOnScriptInit();
			#endif
			#define OnMasterSystemInit @eOnScriptInit
		#elseif _MASTER == 5
			#if defined @fOnScriptInit
				@fOnScriptInit();
			#endif
			#define OnMasterSystemInit @fOnScriptInit
		#elseif _MASTER == 6
			#if defined @gOnScriptInit
				@gOnScriptInit();
			#endif
			#define OnMasterSystemInit @gOnScriptInit
		#elseif _MASTER == 7
			#if defined @hOnScriptInit
				@hOnScriptInit();
			#endif
			#define OnMasterSystemInit @hOnScriptInit
		#elseif _MASTER == 8
			#if defined @iOnScriptInit
				@iOnScriptInit();
			#endif
			#define OnMasterSystemInit @iOnScriptInit
		#elseif _MASTER == 9
			#if defined @jOnScriptInit
				@jOnScriptInit();
			#endif
			#define OnMasterSystemInit @jOnScriptInit
		#elseif _MASTER == 10
			#if defined @kOnScriptInit
				@kOnScriptInit();
			#endif
			#define OnMasterSystemInit @kOnScriptInit
		#elseif _MASTER == 11
			#if defined @lOnScriptInit
				@lOnScriptInit();
			#endif
			#define OnMasterSystemInit @lOnScriptInit
		#elseif _MASTER == 12
			#if defined @mOnScriptInit
				@mOnScriptInit();
			#endif
			#define OnMasterSystemInit @mOnScriptInit
		#elseif _MASTER == 13
			#if defined @nOnScriptInit
				@nOnScriptInit();
			#endif
			#define OnMasterSystemInit @nOnScriptInit
		#elseif _MASTER == 14
			#if defined @oOnScriptInit
				@oOnScriptInit();
			#endif
			#define OnMasterSystemInit @oOnScriptInit
		#elseif _MASTER == 15
			#if defined @pOnScriptInit
				@pOnScriptInit();
			#endif
			#define OnMasterSystemInit @pOnScriptInit
		#endif
	#elseif _MASTER < 32
		#if _MASTER == 16
			#if defined @qOnScriptInit
				@qOnScriptInit();
			#endif
			#define OnMasterSystemInit @qOnScriptInit
		#elseif _MASTER == 17
			#if defined @rOnScriptInit
				@rOnScriptInit();
			#endif
			#define OnMasterSystemInit @rOnScriptInit
		#elseif _MASTER == 18
			#if defined @sOnScriptInit
				@sOnScriptInit();
			#endif
			#define OnMasterSystemInit @sOnScriptInit
		#elseif _MASTER == 19
			#if defined @tOnScriptInit
				@tOnScriptInit();
			#endif
			#define OnMasterSystemInit @tOnScriptInit
		#elseif _MASTER == 20
			#if defined @uOnScriptInit
				@uOnScriptInit();
			#endif
			#define OnMasterSystemInit @uOnScriptInit
		#elseif _MASTER == 21
			#if defined @vOnScriptInit
				@vOnScriptInit();
			#endif
			#define OnMasterSystemInit @vOnScriptInit
		#elseif _MASTER == 22
			#if defined @wOnScriptInit
				@wOnScriptInit();
			#endif
			#define OnMasterSystemInit @wOnScriptInit
		#elseif _MASTER == 23
			#if defined @xOnScriptInit
				@xOnScriptInit();
			#endif
			#define OnMasterSystemInit @xOnScriptInit
		#elseif _MASTER == 24
			#if defined @yOnScriptInit
				@yOnScriptInit();
			#endif
			#define OnMasterSystemInit @yOnScriptInit
		#elseif _MASTER == 25
			#if defined @zOnScriptInit
				@zOnScriptInit();
			#endif
			#define OnMasterSystemInit @zOnScriptInit
		#elseif _MASTER == 26
			#if defined @AOnScriptInit
				@AOnScriptInit();
			#endif
			#define OnMasterSystemInit @AOnScriptInit
		#elseif _MASTER == 27
			#if defined @BOnScriptInit
				@BOnScriptInit();
			#endif
			#define OnMasterSystemInit @BOnScriptInit
		#elseif _MASTER == 28
			#if defined @COnScriptInit
				@COnScriptInit();
			#endif
			#define OnMasterSystemInit @COnScriptInit
		#elseif _MASTER == 29
			#if defined @DOnScriptInit
				@DOnScriptInit();
			#endif
			#define OnMasterSystemInit @DOnScriptInit
		#elseif _MASTER == 30
			#if defined @EOnScriptInit
				@EOnScriptInit();
			#endif
			#define OnMasterSystemInit @EOnScriptInit
		#elseif _MASTER == 31
			#if defined @FOnScriptInit
				@FOnScriptInit();
			#endif
			#define OnMasterSystemInit @FOnScriptInit
		#endif
	#elseif _MASTER < 48
		#if _MASTER == 32
			#if defined @GOnScriptInit
				@GOnScriptInit();
			#endif
			#define OnMasterSystemInit @GOnScriptInit
		#elseif _MASTER == 33
			#if defined @HOnScriptInit
				@HOnScriptInit();
			#endif
			#define OnMasterSystemInit @HOnScriptInit
		#elseif _MASTER == 34
			#if defined @IOnScriptInit
				@IOnScriptInit();
			#endif
			#define OnMasterSystemInit @IOnScriptInit
		#elseif _MASTER == 35
			#if defined @JOnScriptInit
				@JOnScriptInit();
			#endif
			#define OnMasterSystemInit @JOnScriptInit
		#elseif _MASTER == 36
			#if defined @KOnScriptInit
				@KOnScriptInit();
			#endif
			#define OnMasterSystemInit @KOnScriptInit
		#elseif _MASTER == 37
			#if defined @LOnScriptInit
				@LOnScriptInit();
			#endif
			#define OnMasterSystemInit @LOnScriptInit
		#elseif _MASTER == 38
			#if defined @MOnScriptInit
				@MOnScriptInit();
			#endif
			#define OnMasterSystemInit @MOnScriptInit
		#elseif _MASTER == 39
			#if defined @NOnScriptInit
				@NOnScriptInit();
			#endif
			#define OnMasterSystemInit @NOnScriptInit
		#elseif _MASTER == 40
			#if defined @OOnScriptInit
				@OOnScriptInit();
			#endif
			#define OnMasterSystemInit @OOnScriptInit
		#elseif _MASTER == 41
			#if defined @POnScriptInit
				@POnScriptInit();
			#endif
			#define OnMasterSystemInit @POnScriptInit
		#elseif _MASTER == 42
			#if defined @QOnScriptInit
				@QOnScriptInit();
			#endif
			#define OnMasterSystemInit @QOnScriptInit
		#elseif _MASTER == 43
			#if defined @ROnScriptInit
				@ROnScriptInit();
			#endif
			#define OnMasterSystemInit @ROnScriptInit
		#elseif _MASTER == 44
			#if defined @SOnScriptInit
				@SOnScriptInit();
			#endif
			#define OnMasterSystemInit @SOnScriptInit
		#elseif _MASTER == 45
			#if defined @TOnScriptInit
				@TOnScriptInit();
			#endif
			#define OnMasterSystemInit @TOnScriptInit
		#elseif _MASTER == 46
			#if defined @UOnScriptInit
				@UOnScriptInit();
			#endif
			#define OnMasterSystemInit @UOnScriptInit
		#elseif _MASTER == 47
			#if defined @VOnScriptInit
				@VOnScriptInit();
			#endif
			#define OnMasterSystemInit @VOnScriptInit
		#endif
	#else
		#if _MASTER == 48
			#if defined @WOnScriptInit
				@WOnScriptInit();
			#endif
			#define OnMasterSystemInit @WOnScriptInit
		#elseif _MASTER == 49
			#if defined @XOnScriptInit
				@XOnScriptInit();
			#endif
			#define OnMasterSystemInit @XOnScriptInit
		#elseif _MASTER == 50
			#if defined @YOnScriptInit
				@YOnScriptInit();
			#endif
			#define OnMasterSystemInit @YOnScriptInit
		#elseif _MASTER == 51
			#if defined @ZOnScriptInit
				@ZOnScriptInit();
			#endif
			#define OnMasterSystemInit @ZOnScriptInit
		#elseif _MASTER == 52
			#if defined @0OnScriptInit
				@0OnScriptInit();
			#endif
			#define OnMasterSystemInit @0OnScriptInit
		#elseif _MASTER == 53
			#if defined @1OnScriptInit
				@1OnScriptInit();
			#endif
			#define OnMasterSystemInit @1OnScriptInit
		#elseif _MASTER == 54
			#if defined @2OnScriptInit
				@2OnScriptInit();
			#endif
			#define OnMasterSystemInit @2OnScriptInit
		#elseif _MASTER == 55
			#if defined @3OnScriptInit
				@3OnScriptInit();
			#endif
			#define OnMasterSystemInit @3OnScriptInit
		#elseif _MASTER == 56
			#if defined @4OnScriptInit
				@4OnScriptInit();
			#endif
			#define OnMasterSystemInit @4OnScriptInit
		#elseif _MASTER == 57
			#if defined @5OnScriptInit
				@5OnScriptInit();
			#endif
			#define OnMasterSystemInit @5OnScriptInit
		#elseif _MASTER == 58
			#if defined @6OnScriptInit
				@6OnScriptInit();
			#endif
			#define OnMasterSystemInit @6OnScriptInit
		#elseif _MASTER == 59
			#if defined @7OnScriptInit
				@7OnScriptInit();
			#endif
			#define OnMasterSystemInit @7OnScriptInit
		#elseif _MASTER == 60
			#if defined @8OnScriptInit
				@8OnScriptInit();
			#endif
			#define OnMasterSystemInit @8OnScriptInit
		#elseif _MASTER == 61
			#if defined @9OnScriptInit
				@9OnScriptInit();
			#endif
			#define OnMasterSystemInit @9OnScriptInit
		#elseif _MASTER == 62
			#if defined @@OnScriptInit
				@@OnScriptInit();
			#endif
			#define OnMasterSystemInit @@OnScriptInit
		#elseif _MASTER == 63
			#if defined @_OnScriptInit
				@_OnScriptInit();
			#endif
			#define OnMasterSystemInit @_OnScriptInit
		#endif
	#endif
	return 1;
}

// Define a load of fake functions to cater for the compiler's need to
// know all the possible states.  y means master, n means not master, m
// means master system missing, p means previous (ending master), u
// means sort of uninitialised (though technically initialised).  This
// also doubles as a handy call in function for resetting masters when a
// script ends.  Just to clarify - this function is NOT called _YCM,
// that is a macro which is expanded every time this file is included.
// m is also now client/stub.

/*-----------------------------------------------------------------*//**
 * <transition keep="true" target="_YCM : m" source="_YCM : y" />
 * <transition keep="true" target="_YCM : p" source="_YCM : y" />
 * <transition keep="true" target="_YCM : n" source="_YCM : y" />
 * <transition keep="true" target="_YCM : y" source="_YCM : u" />
 *//*----------------------------------------------------------------**/

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

