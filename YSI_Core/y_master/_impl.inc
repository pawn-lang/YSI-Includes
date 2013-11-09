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
			#undef OnMasterSystemInit
			// THEN rename the callbacks.
			// FINALLY call the new next one.
			#if _MASTER < 26
				#if     _MASTER == 0
					#if defined a@OnScriptInit
						a@OnScriptInit();
						#define OnMasterSystemInit a@OnScriptInit
					#endif
				#elseif _MASTER == 1
					#if defined b@OnScriptInit
						b@OnScriptInit();
						#define OnMasterSystemInit b@OnScriptInit
					#endif
				#elseif _MASTER == 2
					#if defined c@OnScriptInit
						c@OnScriptInit();
						#define OnMasterSystemInit c@OnScriptInit
					#endif
				#elseif _MASTER == 3
					#if defined d@OnScriptInit
						d@OnScriptInit();
						#define OnMasterSystemInit d@OnScriptInit
					#endif
				#elseif _MASTER == 4
					#if defined e@OnScriptInit
						e@OnScriptInit();
						#define OnMasterSystemInit e@OnScriptInit
					#endif
				#elseif _MASTER == 5
					#if defined f@OnScriptInit
						f@OnScriptInit();
						#define OnMasterSystemInit f@OnScriptInit
					#endif
				#elseif _MASTER == 6
					#if defined g@OnScriptInit
						g@OnScriptInit();
						#define OnMasterSystemInit g@OnScriptInit
					#endif
				#elseif _MASTER == 7
					#if defined h@OnScriptInit
						h@OnScriptInit();
						#define OnMasterSystemInit h@OnScriptInit
					#endif
				#elseif _MASTER == 8
					#if defined i@OnScriptInit
						i@OnScriptInit();
						#define OnMasterSystemInit i@OnScriptInit
					#endif
				#elseif _MASTER == 9
					#if defined j@OnScriptInit
						j@OnScriptInit();
						#define OnMasterSystemInit j@OnScriptInit
					#endif
				#elseif _MASTER == 10
					#if defined k@OnScriptInit
						k@OnScriptInit();
						#define OnMasterSystemInit k@OnScriptInit
					#endif
				#elseif _MASTER == 11
					#if defined l@OnScriptInit
						l@OnScriptInit();
						#define OnMasterSystemInit l@OnScriptInit
					#endif
				#elseif _MASTER == 12
					#if defined m@OnScriptInit
						m@OnScriptInit();
						#define OnMasterSystemInit m@OnScriptInit
					#endif
				#elseif _MASTER == 13
					#if defined n@OnScriptInit
						n@OnScriptInit();
						#define OnMasterSystemInit n@OnScriptInit
					#endif
				#elseif _MASTER == 14
					#if defined o@OnScriptInit
						o@OnScriptInit();
						#define OnMasterSystemInit o@OnScriptInit
					#endif
				#elseif _MASTER == 15
					#if defined p@OnScriptInit
						p@OnScriptInit();
						#define OnMasterSystemInit p@OnScriptInit
					#endif
				#elseif _MASTER == 16
					#if defined q@OnScriptInit
						q@OnScriptInit();
						#define OnMasterSystemInit q@OnScriptInit
					#endif
				#elseif _MASTER == 17
					#if defined r@OnScriptInit
						r@OnScriptInit();
						#define OnMasterSystemInit r@OnScriptInit
					#endif
				#elseif _MASTER == 18
					#if defined s@OnScriptInit
						s@OnScriptInit();
						#define OnMasterSystemInit s@OnScriptInit
					#endif
				#elseif _MASTER == 19
					#if defined t@OnScriptInit
						t@OnScriptInit();
						#define OnMasterSystemInit t@OnScriptInit
					#endif
				#elseif _MASTER == 20
					#if defined u@OnScriptInit
						u@OnScriptInit();
						#define OnMasterSystemInit u@OnScriptInit
					#endif
				#elseif _MASTER == 21
					#if defined v@OnScriptInit
						v@OnScriptInit();
						#define OnMasterSystemInit v@OnScriptInit
					#endif
				#elseif _MASTER == 22
					#if defined w@OnScriptInit
						w@OnScriptInit();
						#define OnMasterSystemInit w@OnScriptInit
					#endif
				#elseif _MASTER == 23
					#if defined x@OnScriptInit
						x@OnScriptInit();
						#define OnMasterSystemInit x@OnScriptInit
					#endif
				#elseif _MASTER == 24
					#if defined y@OnScriptInit
						y@OnScriptInit();
						#define OnMasterSystemInit y@OnScriptInit
					#endif
				#elseif _MASTER == 25
					#if defined z@OnScriptInit
						z@OnScriptInit();
						#define OnMasterSystemInit z@OnScriptInit
					#endif
				#endif
			#elseif _MASTER < 52
				#if     _MASTER == 26
					#if defined A@OnScriptInit
						A@OnScriptInit();
						#define OnMasterSystemInit A@OnScriptInit
					#endif
				#elseif _MASTER == 27
					#if defined B@OnScriptInit
						B@OnScriptInit();
						#define OnMasterSystemInit B@OnScriptInit
					#endif
				#elseif _MASTER == 28
					#if defined C@OnScriptInit
						C@OnScriptInit();
						#define OnMasterSystemInit C@OnScriptInit
					#endif
				#elseif _MASTER == 29
					#if defined D@OnScriptInit
						D@OnScriptInit();
						#define OnMasterSystemInit D@OnScriptInit
					#endif
				#elseif _MASTER == 30
					#if defined E@OnScriptInit
						E@OnScriptInit();
						#define OnMasterSystemInit E@OnScriptInit
					#endif
				#elseif _MASTER == 31
					#if defined F@OnScriptInit
						F@OnScriptInit();
						#define OnMasterSystemInit F@OnScriptInit
					#endif
				#elseif _MASTER == 32
					#if defined G@OnScriptInit
						G@OnScriptInit();
						#define OnMasterSystemInit G@OnScriptInit
					#endif
				#elseif _MASTER == 33
					#if defined H@OnScriptInit
						H@OnScriptInit();
						#define OnMasterSystemInit H@OnScriptInit
					#endif
				#elseif _MASTER == 34
					#if defined I@OnScriptInit
						I@OnScriptInit();
						#define OnMasterSystemInit I@OnScriptInit
					#endif
				#elseif _MASTER == 35
					#if defined J@OnScriptInit
						J@OnScriptInit();
						#define OnMasterSystemInit J@OnScriptInit
					#endif
				#elseif _MASTER == 36
					#if defined K@OnScriptInit
						K@OnScriptInit();
						#define OnMasterSystemInit K@OnScriptInit
					#endif
				#elseif _MASTER == 37
					#if defined L@OnScriptInit
						L@OnScriptInit();
						#define OnMasterSystemInit L@OnScriptInit
					#endif
				#elseif _MASTER == 38
					#if defined M@OnScriptInit
						M@OnScriptInit();
						#define OnMasterSystemInit M@OnScriptInit
					#endif
				#elseif _MASTER == 39
					#if defined N@OnScriptInit
						N@OnScriptInit();
						#define OnMasterSystemInit N@OnScriptInit
					#endif
				#elseif _MASTER == 40
					#if defined O@OnScriptInit
						O@OnScriptInit();
						#define OnMasterSystemInit O@OnScriptInit
					#endif
				#elseif _MASTER == 41
					#if defined P@OnScriptInit
						P@OnScriptInit();
						#define OnMasterSystemInit P@OnScriptInit
					#endif
				#elseif _MASTER == 42
					#if defined Q@OnScriptInit
						Q@OnScriptInit();
						#define OnMasterSystemInit Q@OnScriptInit
					#endif
				#elseif _MASTER == 43
					#if defined R@OnScriptInit
						R@OnScriptInit();
						#define OnMasterSystemInit R@OnScriptInit
					#endif
				#elseif _MASTER == 44
					#if defined S@OnScriptInit
						S@OnScriptInit();
						#define OnMasterSystemInit S@OnScriptInit
					#endif
				#elseif _MASTER == 45
					#if defined T@OnScriptInit
						T@OnScriptInit();
						#define OnMasterSystemInit T@OnScriptInit
					#endif
				#elseif _MASTER == 46
					#if defined U@OnScriptInit
						U@OnScriptInit();
						#define OnMasterSystemInit U@OnScriptInit
					#endif
				#elseif _MASTER == 47
					#if defined V@OnScriptInit
						V@OnScriptInit();
						#define OnMasterSystemInit V@OnScriptInit
					#endif
				#elseif _MASTER == 48
					#if defined W@OnScriptInit
						W@OnScriptInit();
						#define OnMasterSystemInit W@OnScriptInit
					#endif
				#elseif _MASTER == 49
					#if defined X@OnScriptInit
						X@OnScriptInit();
						#define OnMasterSystemInit X@OnScriptInit
					#endif
				#elseif _MASTER == 50
					#if defined Y@OnScriptInit
						Y@OnScriptInit();
						#define OnMasterSystemInit Y@OnScriptInit
					#endif
				#elseif _MASTER == 51
					#if defined Z@OnScriptInit
						Z@OnScriptInit();
						#define OnMasterSystemInit Z@OnScriptInit
					#endif
				#endif
			#elseif _MASTER < 78
				#if     _MASTER == 52
					#if defined @aOnScriptInit
						@aOnScriptInit();
						#define OnMasterSystemInit @aOnScriptInit
					#endif
				#elseif _MASTER == 53
					#if defined @bOnScriptInit
						@bOnScriptInit();
						#define OnMasterSystemInit @bOnScriptInit
					#endif
				#elseif _MASTER == 54
					#if defined @cOnScriptInit
						@cOnScriptInit();
						#define OnMasterSystemInit @cOnScriptInit
					#endif
				#elseif _MASTER == 55
					#if defined @dOnScriptInit
						@dOnScriptInit();
						#define OnMasterSystemInit @dOnScriptInit
					#endif
				#elseif _MASTER == 56
					#if defined @eOnScriptInit
						@eOnScriptInit();
						#define OnMasterSystemInit @eOnScriptInit
					#endif
				#elseif _MASTER == 57
					#if defined @fOnScriptInit
						@fOnScriptInit();
						#define OnMasterSystemInit @fOnScriptInit
					#endif
				#elseif _MASTER == 58
					#if defined @gOnScriptInit
						@gOnScriptInit();
						#define OnMasterSystemInit @gOnScriptInit
					#endif
				#elseif _MASTER == 59
					#if defined @hOnScriptInit
						@hOnScriptInit();
						#define OnMasterSystemInit @hOnScriptInit
					#endif
				#elseif _MASTER == 60
					#if defined @iOnScriptInit
						@iOnScriptInit();
						#define OnMasterSystemInit @iOnScriptInit
					#endif
				#elseif _MASTER == 61
					#if defined @jOnScriptInit
						@jOnScriptInit();
						#define OnMasterSystemInit @jOnScriptInit
					#endif
				#elseif _MASTER == 62
					#if defined @kOnScriptInit
						@kOnScriptInit();
						#define OnMasterSystemInit @kOnScriptInit
					#endif
				#elseif _MASTER == 63
					#if defined @lOnScriptInit
						@lOnScriptInit();
						#define OnMasterSystemInit @lOnScriptInit
					#endif
				#elseif _MASTER == 64
					#if defined @mOnScriptInit
						@mOnScriptInit();
						#define OnMasterSystemInit @mOnScriptInit
					#endif
				#elseif _MASTER == 65
					#if defined @nOnScriptInit
						@nOnScriptInit();
						#define OnMasterSystemInit @nOnScriptInit
					#endif
				#elseif _MASTER == 66
					#if defined @oOnScriptInit
						@oOnScriptInit();
						#define OnMasterSystemInit @oOnScriptInit
					#endif
				#elseif _MASTER == 67
					#if defined @pOnScriptInit
						@pOnScriptInit();
						#define OnMasterSystemInit @pOnScriptInit
					#endif
				#elseif _MASTER == 68
					#if defined @qOnScriptInit
						@qOnScriptInit();
						#define OnMasterSystemInit @qOnScriptInit
					#endif
				#elseif _MASTER == 69
					#if defined @rOnScriptInit
						@rOnScriptInit();
						#define OnMasterSystemInit @rOnScriptInit
					#endif
				#elseif _MASTER == 70
					#if defined @sOnScriptInit
						@sOnScriptInit();
						#define OnMasterSystemInit @sOnScriptInit
					#endif
				#elseif _MASTER == 71
					#if defined @tOnScriptInit
						@tOnScriptInit();
						#define OnMasterSystemInit @tOnScriptInit
					#endif
				#elseif _MASTER == 72
					#if defined @uOnScriptInit
						@uOnScriptInit();
						#define OnMasterSystemInit @uOnScriptInit
					#endif
				#elseif _MASTER == 73
					#if defined @vOnScriptInit
						@vOnScriptInit();
						#define OnMasterSystemInit @vOnScriptInit
					#endif
				#elseif _MASTER == 74
					#if defined @wOnScriptInit
						@wOnScriptInit();
						#define OnMasterSystemInit @wOnScriptInit
					#endif
				#elseif _MASTER == 75
					#if defined @xOnScriptInit
						@xOnScriptInit();
						#define OnMasterSystemInit @xOnScriptInit
					#endif
				#elseif _MASTER == 76
					#if defined @yOnScriptInit
						@yOnScriptInit();
						#define OnMasterSystemInit @yOnScriptInit
					#endif
				#elseif _MASTER == 77
					#if defined @zOnScriptInit
						@zOnScriptInit();
						#define OnMasterSystemInit @zOnScriptInit
					#endif
				#endif
			#elseif _MASTER < 104
				#if     _MASTER == 78
					#if defined @AOnScriptInit
						@AOnScriptInit();
						#define OnMasterSystemInit @AOnScriptInit
					#endif
				#elseif _MASTER == 79
					#if defined @BOnScriptInit
						@BOnScriptInit();
						#define OnMasterSystemInit @BOnScriptInit
					#endif
				#elseif _MASTER == 80
					#if defined @COnScriptInit
						@COnScriptInit();
						#define OnMasterSystemInit @COnScriptInit
					#endif
				#elseif _MASTER == 81
					#if defined @DOnScriptInit
						@DOnScriptInit();
						#define OnMasterSystemInit @DOnScriptInit
					#endif
				#elseif _MASTER == 82
					#if defined @EOnScriptInit
						@EOnScriptInit();
						#define OnMasterSystemInit @EOnScriptInit
					#endif
				#elseif _MASTER == 83
					#if defined @FOnScriptInit
						@FOnScriptInit();
						#define OnMasterSystemInit @FOnScriptInit
					#endif
				#elseif _MASTER == 84
					#if defined @GOnScriptInit
						@GOnScriptInit();
						#define OnMasterSystemInit @GOnScriptInit
					#endif
				#elseif _MASTER == 85
					#if defined @HOnScriptInit
						@HOnScriptInit();
						#define OnMasterSystemInit @HOnScriptInit
					#endif
				#elseif _MASTER == 86
					#if defined @IOnScriptInit
						@IOnScriptInit();
						#define OnMasterSystemInit @IOnScriptInit
					#endif
				#elseif _MASTER == 87
					#if defined @JOnScriptInit
						@JOnScriptInit();
						#define OnMasterSystemInit @JOnScriptInit
					#endif
				#elseif _MASTER == 88
					#if defined @KOnScriptInit
						@KOnScriptInit();
						#define OnMasterSystemInit @KOnScriptInit
					#endif
				#elseif _MASTER == 89
					#if defined @LOnScriptInit
						@LOnScriptInit();
						#define OnMasterSystemInit @LOnScriptInit
					#endif
				#elseif _MASTER == 90
					#if defined @MOnScriptInit
						@MOnScriptInit();
						#define OnMasterSystemInit @MOnScriptInit
					#endif
				#elseif _MASTER == 91
					#if defined @NOnScriptInit
						@NOnScriptInit();
						#define OnMasterSystemInit @NOnScriptInit
					#endif
				#elseif _MASTER == 92
					#if defined @OOnScriptInit
						@OOnScriptInit();
						#define OnMasterSystemInit @OOnScriptInit
					#endif
				#elseif _MASTER == 93
					#if defined @POnScriptInit
						@POnScriptInit();
						#define OnMasterSystemInit @POnScriptInit
					#endif
				#elseif _MASTER == 94
					#if defined @QOnScriptInit
						@QOnScriptInit();
						#define OnMasterSystemInit @QOnScriptInit
					#endif
				#elseif _MASTER == 95
					#if defined @ROnScriptInit
						@ROnScriptInit();
						#define OnMasterSystemInit @ROnScriptInit
					#endif
				#elseif _MASTER == 96
					#if defined @SOnScriptInit
						@SOnScriptInit();
						#define OnMasterSystemInit @SOnScriptInit
					#endif
				#elseif _MASTER == 97
					#if defined @TOnScriptInit
						@TOnScriptInit();
						#define OnMasterSystemInit @TOnScriptInit
					#endif
				#elseif _MASTER == 98
					#if defined @UOnScriptInit
						@UOnScriptInit();
						#define OnMasterSystemInit @UOnScriptInit
					#endif
				#elseif _MASTER == 99
					#if defined @VOnScriptInit
						@VOnScriptInit();
						#define OnMasterSystemInit @VOnScriptInit
					#endif
				#elseif _MASTER == 100
					#if defined @WOnScriptInit
						@WOnScriptInit();
						#define OnMasterSystemInit @WOnScriptInit
					#endif
				#elseif _MASTER == 101
					#if defined @XOnScriptInit
						@XOnScriptInit();
						#define OnMasterSystemInit @XOnScriptInit
					#endif
				#elseif _MASTER == 102
					#if defined @YOnScriptInit
						@YOnScriptInit();
						#define OnMasterSystemInit @YOnScriptInit
					#endif
				#elseif _MASTER == 103
					#if defined @ZOnScriptInit
						@ZOnScriptInit();
						#define OnMasterSystemInit @ZOnScriptInit
					#endif
				#endif
			#else
				#if     _MASTER == 104
					#if defined @0OnScriptInit
						@0OnScriptInit();
						#define OnMasterSystemInit @0OnScriptInit
					#endif
				#elseif _MASTER == 105
					#if defined @1OnScriptInit
						@1OnScriptInit();
						#define OnMasterSystemInit @1OnScriptInit
					#endif
				#elseif _MASTER == 106
					#if defined @2OnScriptInit
						@2OnScriptInit();
						#define OnMasterSystemInit @2OnScriptInit
					#endif
				#elseif _MASTER == 107
					#if defined @3OnScriptInit
						@3OnScriptInit();
						#define OnMasterSystemInit @3OnScriptInit
					#endif
				#elseif _MASTER == 108
					#if defined @4OnScriptInit
						@4OnScriptInit();
						#define OnMasterSystemInit @4OnScriptInit
					#endif
				#elseif _MASTER == 109
					#if defined @5OnScriptInit
						@5OnScriptInit();
						#define OnMasterSystemInit @5OnScriptInit
					#endif
				#elseif _MASTER == 110
					#if defined @6OnScriptInit
						@6OnScriptInit();
						#define OnMasterSystemInit @6OnScriptInit
					#endif
				#elseif _MASTER == 111
					#if defined @7OnScriptInit
						@7OnScriptInit();
						#define OnMasterSystemInit @7OnScriptInit
					#endif
				#elseif _MASTER == 112
					#if defined @8OnScriptInit
						@8OnScriptInit();
						#define OnMasterSystemInit @8OnScriptInit
					#endif
				#elseif _MASTER == 113
					#if defined @9OnScriptInit
						@9OnScriptInit();
						#define OnMasterSystemInit @9OnScriptInit
					#endif
				#elseif _MASTER == 114
					#if defined @@OnScriptInit
						@@OnScriptInit();
						#define OnMasterSystemInit @@OnScriptInit
					#endif
				#elseif _MASTER == 115
					#if defined @_OnScriptInit
						@_OnScriptInit();
						#define OnMasterSystemInit @_OnScriptInit
					#endif
				#elseif _MASTER == 116
					#if defined _@OnScriptInit
						_@OnScriptInit();
						#define OnMasterSystemInit _@OnScriptInit
					#endif
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
		
		#if _MASTER == 0
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

