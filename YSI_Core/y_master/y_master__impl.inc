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

#if defined _inc_y_master__impl
	#undef _inc_y_master__impl
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
//	#error Unknown y_master settings.
const static _YSIM_STORED_SETTINGS = YSIM_STORED_SETTINGS;
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
#if !YSIM_HAS_MASTER
	#define FOREIGN__      YSIM_NONE_FOREIGN
	#define GLOBAL__       YSIM_NONE_GLOBAL
	#define MASTER_FUNC__  YSIM_NONE_FUNC
	#define MASTER_HOOK__  YSIM_NONE_HOOK
	#define MASTER_TASK__  YSIM_NONE_TASK
	#define MASTER_PTASK__ YSIM_NONE_PTSK
	#define GROUP_HOOK__   YSIM_NONE_GRUP
	#if _MASTER == 0
		// Less strict (implicit user master).
		#define YSIM_COMMAND YSIM_NONE_ZERO
	#else
		#define YSIM_COMMAND YSIM_NONE_YCMD
	#endif
	#define Master_Caller() (1)
#elseif _YSIM_IS_SERVER
	#define FOREIGN__      YSIM_SERVER_FOREIGN
	#define GLOBAL__       YSIM_SERVER_GLOBAL
	#define MASTER_FUNC__  YSIM_SERVER_FUNC
	#define MASTER_HOOK__  YSIM_SERVER_HOOK
	#define MASTER_TASK__  YSIM_SERVER_TASK
	#define MASTER_PTASK__ YSIM_SERVER_PTSK
	#define GROUP_HOOK__   YSIM_SERVER_GRUP
	#if _MASTER == 0
		// Less strict (implicit user master).
		#define YSIM_COMMAND YSIM_SERVER_ZERO
	#else
		#define YSIM_COMMAND YSIM_SERVER_YCMD
	#endif
	#define Master_Caller() (((I@=V@(8,YSIM_CALLER))==0)?(@_):(I@))
#elseif _YSIM_IS_CLIENT
	#define FOREIGN__      YSIM_CLIENT_FOREIGN
	#define GLOBAL__       YSIM_CLIENT_GLOBAL
	#define MASTER_FUNC__  YSIM_CLIENT_FUNC
	#define MASTER_HOOK__  YSIM_CLIENT_HOOK
	#define MASTER_TASK__  YSIM_CLIENT_TASK
	#define MASTER_PTASK__ YSIM_CLIENT_PTSK
	#define GROUP_HOOK__   YSIM_CLIENT_GRUP
	#if _MASTER == 0
		// Less strict (implicit user master).
		#define YSIM_COMMAND YSIM_CLIENT_ZERO
	#else
		#define YSIM_COMMAND YSIM_CLIENT_YCMD
	#endif
	#define Master_Caller() (-1)
#elseif _YSIM_IS_STUB
	#define FOREIGN__      YSIM_STUB_FOREIGN
	#define GLOBAL__       YSIM_STUB_GLOBAL
	#define MASTER_FUNC__  YSIM_STUB_FUNC
	#define MASTER_HOOK__  YSIM_STUB_HOOK
	#define MASTER_TASK__  YSIM_STUB_TASK
	#define MASTER_PTASK__ YSIM_STUB_PTSK
	#define GROUP_HOOK__   YSIM_STUB_GRUP
	#if _MASTER == 0
		// Less strict (implicit user master).
		#define YSIM_COMMAND YSIM_STUB_ZERO
	#else
		#define YSIM_COMMAND YSIM_STUB_YCMD
	#endif
	#define Master_Caller
#else
	#define FOREIGN__      YSIM_CLOUD_FOREIGN
	#define GLOBAL__       YSIM_CLOUD_GLOBAL
	#define MASTER_FUNC__  YSIM_CLOUD_FUNC
	#define MASTER_HOOK__  YSIM_CLOUD_HOOK
	#define MASTER_TASK__  YSIM_CLOUD_TASK
	#define MASTER_PTASK__ YSIM_CLOUD_PTSK
	#define GROUP_HOOK__   YSIM_CLOUD_GRUP
	#if _MASTER == 0
		// Less strict (implicit user master).
		#define YSIM_COMMAND YSIM_CLOUD_ZERO
	#else
		#define YSIM_COMMAND YSIM_CLOUD_YCMD
	#endif
	#define Master_Caller() (((I@=V@(8,YSIM_CALLER))==0)?(@_):(I@))
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
	// THERES A `#endinput` HERE, because we don't need to co-ordinate.
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

public OnMasterSystemInit(id)
{
	P:1(#_YCM "_OGM");
	Master_GetCurrentMaster();
	#if defined _ALS_OnMasterSystemInit
		#undef OnMasterSystemInit
	#else
		#define _ALS_OnMasterSystemInit
	#endif	// THEN rename the callbacks.
	// FINALLY call the new next one.
	#if _MASTER < 16
		#if _MASTER == 0
			#if defined @aOnScriptInit
				@aOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @aOnScriptInit
		#elseif _MASTER == 1
			#if defined @bOnScriptInit
				@bOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @bOnScriptInit
		#elseif _MASTER == 2
			#if defined @cOnScriptInit
				@cOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @cOnScriptInit
		#elseif _MASTER == 3
			#if defined @dOnScriptInit
				@dOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @dOnScriptInit
		#elseif _MASTER == 4
			#if defined @eOnScriptInit
				@eOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @eOnScriptInit
		#elseif _MASTER == 5
			#if defined @fOnScriptInit
				@fOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @fOnScriptInit
		#elseif _MASTER == 6
			#if defined @gOnScriptInit
				@gOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @gOnScriptInit
		#elseif _MASTER == 7
			#if defined @hOnScriptInit
				@hOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @hOnScriptInit
		#elseif _MASTER == 8
			#if defined @iOnScriptInit
				@iOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @iOnScriptInit
		#elseif _MASTER == 9
			#if defined @jOnScriptInit
				@jOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @jOnScriptInit
		#elseif _MASTER == 10
			#if defined @kOnScriptInit
				@kOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @kOnScriptInit
		#elseif _MASTER == 11
			#if defined @lOnScriptInit
				@lOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @lOnScriptInit
		#elseif _MASTER == 12
			#if defined @mOnScriptInit
				@mOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @mOnScriptInit
		#elseif _MASTER == 13
			#if defined @nOnScriptInit
				@nOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @nOnScriptInit
		#elseif _MASTER == 14
			#if defined @oOnScriptInit
				@oOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @oOnScriptInit
		#elseif _MASTER == 15
			#if defined @pOnScriptInit
				@pOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @pOnScriptInit
		#endif
	#elseif _MASTER < 32
		#if _MASTER == 16
			#if defined @qOnScriptInit
				@qOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @qOnScriptInit
		#elseif _MASTER == 17
			#if defined @rOnScriptInit
				@rOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @rOnScriptInit
		#elseif _MASTER == 18
			#if defined @sOnScriptInit
				@sOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @sOnScriptInit
		#elseif _MASTER == 19
			#if defined @tOnScriptInit
				@tOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @tOnScriptInit
		#elseif _MASTER == 20
			#if defined @uOnScriptInit
				@uOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @uOnScriptInit
		#elseif _MASTER == 21
			#if defined @vOnScriptInit
				@vOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @vOnScriptInit
		#elseif _MASTER == 22
			#if defined @wOnScriptInit
				@wOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @wOnScriptInit
		#elseif _MASTER == 23
			#if defined @xOnScriptInit
				@xOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @xOnScriptInit
		#elseif _MASTER == 24
			#if defined @yOnScriptInit
				@yOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @yOnScriptInit
		#elseif _MASTER == 25
			#if defined @zOnScriptInit
				@zOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @zOnScriptInit
		#elseif _MASTER == 26
			#if defined @AOnScriptInit
				@AOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @AOnScriptInit
		#elseif _MASTER == 27
			#if defined @BOnScriptInit
				@BOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @BOnScriptInit
		#elseif _MASTER == 28
			#if defined @COnScriptInit
				@COnScriptInit(id);
			#endif
			#define OnMasterSystemInit @COnScriptInit
		#elseif _MASTER == 29
			#if defined @DOnScriptInit
				@DOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @DOnScriptInit
		#elseif _MASTER == 30
			#if defined @EOnScriptInit
				@EOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @EOnScriptInit
		#elseif _MASTER == 31
			#if defined @FOnScriptInit
				@FOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @FOnScriptInit
		#endif
	#elseif _MASTER < 48
		#if _MASTER == 32
			#if defined @GOnScriptInit
				@GOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @GOnScriptInit
		#elseif _MASTER == 33
			#if defined @HOnScriptInit
				@HOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @HOnScriptInit
		#elseif _MASTER == 34
			#if defined @IOnScriptInit
				@IOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @IOnScriptInit
		#elseif _MASTER == 35
			#if defined @JOnScriptInit
				@JOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @JOnScriptInit
		#elseif _MASTER == 36
			#if defined @KOnScriptInit
				@KOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @KOnScriptInit
		#elseif _MASTER == 37
			#if defined @LOnScriptInit
				@LOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @LOnScriptInit
		#elseif _MASTER == 38
			#if defined @MOnScriptInit
				@MOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @MOnScriptInit
		#elseif _MASTER == 39
			#if defined @NOnScriptInit
				@NOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @NOnScriptInit
		#elseif _MASTER == 40
			#if defined @OOnScriptInit
				@OOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @OOnScriptInit
		#elseif _MASTER == 41
			#if defined @POnScriptInit
				@POnScriptInit(id);
			#endif
			#define OnMasterSystemInit @POnScriptInit
		#elseif _MASTER == 42
			#if defined @QOnScriptInit
				@QOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @QOnScriptInit
		#elseif _MASTER == 43
			#if defined @ROnScriptInit
				@ROnScriptInit(id);
			#endif
			#define OnMasterSystemInit @ROnScriptInit
		#elseif _MASTER == 44
			#if defined @SOnScriptInit
				@SOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @SOnScriptInit
		#elseif _MASTER == 45
			#if defined @TOnScriptInit
				@TOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @TOnScriptInit
		#elseif _MASTER == 46
			#if defined @UOnScriptInit
				@UOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @UOnScriptInit
		#elseif _MASTER == 47
			#if defined @VOnScriptInit
				@VOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @VOnScriptInit
		#endif
	#else
		#if _MASTER == 48
			#if defined @WOnScriptInit
				@WOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @WOnScriptInit
		#elseif _MASTER == 49
			#if defined @XOnScriptInit
				@XOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @XOnScriptInit
		#elseif _MASTER == 50
			#if defined @YOnScriptInit
				@YOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @YOnScriptInit
		#elseif _MASTER == 51
			#if defined @ZOnScriptInit
				@ZOnScriptInit(id);
			#endif
			#define OnMasterSystemInit @ZOnScriptInit
		#elseif _MASTER == 52
			#if defined @0OnScriptInit
				@0OnScriptInit(id);
			#endif
			#define OnMasterSystemInit @0OnScriptInit
		#elseif _MASTER == 53
			#if defined @1OnScriptInit
				@1OnScriptInit(id);
			#endif
			#define OnMasterSystemInit @1OnScriptInit
		#elseif _MASTER == 54
			#if defined @2OnScriptInit
				@2OnScriptInit(id);
			#endif
			#define OnMasterSystemInit @2OnScriptInit
		#elseif _MASTER == 55
			#if defined @3OnScriptInit
				@3OnScriptInit(id);
			#endif
			#define OnMasterSystemInit @3OnScriptInit
		#elseif _MASTER == 56
			#if defined @4OnScriptInit
				@4OnScriptInit(id);
			#endif
			#define OnMasterSystemInit @4OnScriptInit
		#elseif _MASTER == 57
			#if defined @5OnScriptInit
				@5OnScriptInit(id);
			#endif
			#define OnMasterSystemInit @5OnScriptInit
		#elseif _MASTER == 58
			#if defined @6OnScriptInit
				@6OnScriptInit(id);
			#endif
			#define OnMasterSystemInit @6OnScriptInit
		#elseif _MASTER == 59
			#if defined @7OnScriptInit
				@7OnScriptInit(id);
			#endif
			#define OnMasterSystemInit @7OnScriptInit
		#elseif _MASTER == 60
			#if defined @8OnScriptInit
				@8OnScriptInit(id);
			#endif
			#define OnMasterSystemInit @8OnScriptInit
		#elseif _MASTER == 61
			#if defined @9OnScriptInit
				@9OnScriptInit(id);
			#endif
			#define OnMasterSystemInit @9OnScriptInit
		#elseif _MASTER == 62
			#if defined @@OnScriptInit
				@@OnScriptInit(id);
			#endif
			#define OnMasterSystemInit @@OnScriptInit
		#elseif _MASTER == 63
			#if defined @_OnScriptInit
				@_OnScriptInit(id);
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
	P:1("%d: " #_YCM "<y> called, master = %d", Master_ID(), getproperty(9, #_YCM));
	if (getproperty(9, #_YCM) == Master_ID())
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
	P:1("%d: " #_YCM "<n> called", Master_ID());
	// This has been called remotely from a script which owns the
	// library masterhood (that's the only way this can ever be called).
	Master_GetCurrentMaster();
}

public _YCM() <_YCM:m, _YCM:p>
{
	P:1("%d: " #_YCM "<m,p> called", Master_ID());
	// Do nothing at all (just define states).
}

public _YCM() <_YCM:u>
{
	// Finish initialisation.
	P:1("%d: " #_YCM "<u> called", Master_ID());
	state _YCM:y;
	_YCM@ = _E_YCM@y;
}

public _YCM() <>
{
	// Do nothing at all (just define states).
	P:E(#_YCM "() <> called");
}

