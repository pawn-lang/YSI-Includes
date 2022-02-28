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
	Portions created by the Initial Developer are Copyright (c) 2022
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
	Cheaterman

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
		// Client or stub - never master.
		stock
			_E_YCM:_YCM@ = _E_YCM@n;
	#else
		// No master system - always master.
		stock
			_E_YCM:_YCM@ = _E_YCM@y;
	#endif

	// There's a `#endinput` here because we don't need to co-ordinate.
	#endinput
#endif

// Variable to hold the current master state for ease of access.
stock
	_E_YCM:_YCM@ = _E_YCM@u;

#if _YSIM_IS_SERVER
	forward MAKE_YCM<YSIM_VERSION...>();

	public MAKE_YCM<YSIM_VERSION...>() <_YCM:y, _YCM:u>
	{
		P:3(#MAKE_YCM<YSIM_VERSION...> "() <y,u> called");
		// For making sure the latest version of a library is the one used.
		if (YSI_gModuleShutdown)
		{
			return cellmin;
		}
		
		setproperty(8, YSIM_VERRET, cellmax);
		setproperty(8, YSIM_VERMAX, cellmax);
		return cellmax;
	}

	public MAKE_YCM<YSIM_VERSION...>() <_YCM:n>
	{
		P:3(#MAKE_YCM<YSIM_VERSION...> "() <n> called");
		if (YSI_gModuleShutdown)
		{
			return cellmin;
		}
		
		// For making sure the latest version of a library is the one used.
		setproperty(8, YSIM_VERMAX, cellmax);
		return cellmax;
	}

	public MAKE_YCM<YSIM_VERSION...>() <>
	{
		// Called if this script is ending.
		P:3(#MAKE_YCM<YSIM_VERSION...> "() <> called");
		if (YSI_gModuleShutdown)
		{
			return cellmin;
		}

		return cellmax;
	}
#elseif _YSIM_IS_CLOUD
		forward MAKE_YCM<YSIM_VERSION...>();

		public MAKE_YCM<YSIM_VERSION...>() <>
		{
			// Return here for local (current version) gets.
			P:3(#MAKE_YCM<YSIM_VERSION...> "() <> called");
			if (YSI_gModuleShutdown)
			{
				return cellmin;
			}

	#if defined YSIM_VERSION
			return YSIM_VERSION;
		}
		
		public MAKE_YCM<YSIM_VERSION...>() <_YCM:y>
		{
			P:3(#MAKE_YCM<YSIM_VERSION...> "() <y> called");
			if (YSI_gModuleShutdown)
			{
				return cellmin;
			}
			
			// For making sure the latest version of a library is the one used.
			setproperty(8, YSIM_VERRET, YSIM_VERSION);
			setproperty(8, YSIM_VERMAX, max(getproperty(8, YSIM_VERMAX), YSIM_VERSION));
			return YSIM_VERSION;
		}

		public MAKE_YCM<YSIM_VERSION...>() <_YCM:n>
		{
			P:3(#MAKE_YCM<YSIM_VERSION...> "() <n> called");
			if (YSI_gModuleShutdown)
			{
				return cellmin;
			}
			
			// For making sure the latest version of a library is the one used.
			setproperty(8, YSIM_VERMAX, max(getproperty(8, YSIM_VERMAX), YSIM_VERSION));
			return YSIM_VERSION;
		}

		#undef YSIM_VERSION
	#else
			return 0;
		}
	#endif
		
		public MAKE_YCM<YSIM_VERSION...>() <_YCM:u>
		{
			if (YSI_gModuleShutdown)
			{
				return cellmin;
			}
			
			P:3(#MAKE_YCM<YSIM_VERSION...> "() <u> called");
			// This script already claimed the master, we can't reverse that.
			setproperty(8, YSIM_VERRET, cellmax);
			setproperty(8, YSIM_VERMAX, cellmax);
			return cellmax;
		}
#endif

forward _YCM();

/*-----------------------------------------------------------------*//**
 * <transition keep="true" target="_YCM : y" />
 * <transition keep="true" target="_YCM : u" />
 * <transition keep="true" target="_YCM : y" />
 * <transition keep="true" target="_YCM : n" />
 *//*----------------------------------------------------------------**/

static stock Master_GetCurrentMaster(installState)
{
	// THIS CODE IS COPIED IN y_classes (mostly).
	#if _YSIM_IS_SERVER
		// Steal the master.
		switch (_Master_Get(#_YCM, true))
	#else //if _YSIM_IS_CLOUD
		// See if this script should be master.
		switch (_Master_Get(#_YCM, false))
	#endif
		{
			case e_YSIM_GET_TYPE_NO_CONTEST:
			{
				// Nothing changed, or we took it without force.
				P:2("Master_GetCurrentMaster: Got master " #_YCM);
				state _YCM:y;
				_YCM@ = _E_YCM@y;
				// Already installed = 1 + 1, does nothing.
				// Not installed = 0 + 1, installs.
				++installState;
			}
			case e_YSIM_GET_TYPE_STOLE:
			{
				P:2("Master_GetCurrentMaster: Stole master " #_YCM);
				// Something changed, tell other scripts.  Set the state here to `:u` not `:y` so that
				// the only call to a `:y` function does relinquishing.  We don't want to be set as
				// master here then instantly relinquish everything.
				state _YCM:u;
				_YCM@ = _E_YCM@u;
				// Determine the next unique name.
				CallRemoteFunction(#_YCM, YSI_EMPTY);
				// Servers always get all data, so it doesn't matter that
				// for now this is state "u".
				++installState;
			}
			case e_YSIM_GET_TYPE_NOT_GOT:
			{
				P:2("Master_GetCurrentMaster: Not master " #_YCM);
				state _YCM:n;
				_YCM@ = _E_YCM@n;
				// Already installed = 1 - 1, uninstalls.
				// Not installed = 0 - 1, does nothing.
				--installState;
			}
			default:
			{
				P:E("Master_GetCurrentMaster: Unknown return " #_YCM);
				state _YCM:n;
				_YCM@ = _E_YCM@n;
				--installState;
			}
		}
		// We are now in charge of `_MASTER`.  Rename relevant functions.
		if (installState == 1)
		{
			P:6("Master_GetCurrentMaster: Installing %d", _MASTER);
			_Master_RenameAll(_MASTER);
		}
		else if (installState == 0)
		{
			P:6("Master_GetCurrentMaster: Uninstalling %d", _MASTER);
			_Master_UnnameAll(_MASTER);
		}
		P:C(else { P:6("Master_GetCurrentMaster: Neither %d", _MASTER); });
}

public OnMasterSystemInit(id)
{
	P:1(#_YCM "_OGM");
	deleteproperty(8, YSIM_VERMAX);
	Master_GetCurrentMaster(1);
	#if defined _ALS_OnMasterSystemInit
		#undef OnMasterSystemInit
	#else
		#define _ALS_OnMasterSystemInit
	#endif	// THEN rename the callbacks.
	// FINALLY call the new next one.
	#if _MASTER < 16
		#if _MASTER == 0
			#if defined @aOnYSIInit
				@aOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @aOnYSIInit
		#elseif _MASTER == 1
			#if defined @bOnYSIInit
				@bOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @bOnYSIInit
		#elseif _MASTER == 2
			#if defined @cOnYSIInit
				@cOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @cOnYSIInit
		#elseif _MASTER == 3
			#if defined @dOnYSIInit
				@dOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @dOnYSIInit
		#elseif _MASTER == 4
			#if defined @eOnYSIInit
				@eOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @eOnYSIInit
		#elseif _MASTER == 5
			#if defined @fOnYSIInit
				@fOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @fOnYSIInit
		#elseif _MASTER == 6
			#if defined @gOnYSIInit
				@gOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @gOnYSIInit
		#elseif _MASTER == 7
			#if defined @hOnYSIInit
				@hOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @hOnYSIInit
		#elseif _MASTER == 8
			#if defined @iOnYSIInit
				@iOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @iOnYSIInit
		#elseif _MASTER == 9
			#if defined @jOnYSIInit
				@jOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @jOnYSIInit
		#elseif _MASTER == 10
			#if defined @kOnYSIInit
				@kOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @kOnYSIInit
		#elseif _MASTER == 11
			#if defined @lOnYSIInit
				@lOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @lOnYSIInit
		#elseif _MASTER == 12
			#if defined @mOnYSIInit
				@mOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @mOnYSIInit
		#elseif _MASTER == 13
			#if defined @nOnYSIInit
				@nOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @nOnYSIInit
		#elseif _MASTER == 14
			#if defined @oOnYSIInit
				@oOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @oOnYSIInit
		#elseif _MASTER == 15
			#if defined @pOnYSIInit
				@pOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @pOnYSIInit
		#endif
	#elseif _MASTER < 32
		#if _MASTER == 16
			#if defined @qOnYSIInit
				@qOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @qOnYSIInit
		#elseif _MASTER == 17
			#if defined @rOnYSIInit
				@rOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @rOnYSIInit
		#elseif _MASTER == 18
			#if defined @sOnYSIInit
				@sOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @sOnYSIInit
		#elseif _MASTER == 19
			#if defined @tOnYSIInit
				@tOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @tOnYSIInit
		#elseif _MASTER == 20
			#if defined @uOnYSIInit
				@uOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @uOnYSIInit
		#elseif _MASTER == 21
			#if defined @vOnYSIInit
				@vOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @vOnYSIInit
		#elseif _MASTER == 22
			#if defined @wOnYSIInit
				@wOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @wOnYSIInit
		#elseif _MASTER == 23
			#if defined @xOnYSIInit
				@xOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @xOnYSIInit
		#elseif _MASTER == 24
			#if defined @yOnYSIInit
				@yOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @yOnYSIInit
		#elseif _MASTER == 25
			#if defined @zOnYSIInit
				@zOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @zOnYSIInit
		#elseif _MASTER == 26
			#if defined @AOnYSIInit
				@AOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @AOnYSIInit
		#elseif _MASTER == 27
			#if defined @BOnYSIInit
				@BOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @BOnYSIInit
		#elseif _MASTER == 28
			#if defined @COnYSIInit
				@COnYSIInit(id);
			#endif
			#define OnMasterSystemInit @COnYSIInit
		#elseif _MASTER == 29
			#if defined @DOnYSIInit
				@DOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @DOnYSIInit
		#elseif _MASTER == 30
			#if defined @EOnYSIInit
				@EOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @EOnYSIInit
		#elseif _MASTER == 31
			#if defined @FOnYSIInit
				@FOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @FOnYSIInit
		#endif
	#elseif _MASTER < 48
		#if _MASTER == 32
			#if defined @GOnYSIInit
				@GOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @GOnYSIInit
		#elseif _MASTER == 33
			#if defined @HOnYSIInit
				@HOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @HOnYSIInit
		#elseif _MASTER == 34
			#if defined @IOnYSIInit
				@IOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @IOnYSIInit
		#elseif _MASTER == 35
			#if defined @JOnYSIInit
				@JOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @JOnYSIInit
		#elseif _MASTER == 36
			#if defined @KOnYSIInit
				@KOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @KOnYSIInit
		#elseif _MASTER == 37
			#if defined @LOnYSIInit
				@LOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @LOnYSIInit
		#elseif _MASTER == 38
			#if defined @MOnYSIInit
				@MOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @MOnYSIInit
		#elseif _MASTER == 39
			#if defined @NOnYSIInit
				@NOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @NOnYSIInit
		#elseif _MASTER == 40
			#if defined @OOnYSIInit
				@OOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @OOnYSIInit
		#elseif _MASTER == 41
			#if defined @POnYSIInit
				@POnYSIInit(id);
			#endif
			#define OnMasterSystemInit @POnYSIInit
		#elseif _MASTER == 42
			#if defined @QOnYSIInit
				@QOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @QOnYSIInit
		#elseif _MASTER == 43
			#if defined @ROnYSIInit
				@ROnYSIInit(id);
			#endif
			#define OnMasterSystemInit @ROnYSIInit
		#elseif _MASTER == 44
			#if defined @SOnYSIInit
				@SOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @SOnYSIInit
		#elseif _MASTER == 45
			#if defined @TOnYSIInit
				@TOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @TOnYSIInit
		#elseif _MASTER == 46
			#if defined @UOnYSIInit
				@UOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @UOnYSIInit
		#elseif _MASTER == 47
			#if defined @VOnYSIInit
				@VOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @VOnYSIInit
		#endif
	#else
		#if _MASTER == 48
			#if defined @WOnYSIInit
				@WOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @WOnYSIInit
		#elseif _MASTER == 49
			#if defined @XOnYSIInit
				@XOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @XOnYSIInit
		#elseif _MASTER == 50
			#if defined @YOnYSIInit
				@YOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @YOnYSIInit
		#elseif _MASTER == 51
			#if defined @ZOnYSIInit
				@ZOnYSIInit(id);
			#endif
			#define OnMasterSystemInit @ZOnYSIInit
		#elseif _MASTER == 52
			#if defined @0OnYSIInit
				@0OnYSIInit(id);
			#endif
			#define OnMasterSystemInit @0OnYSIInit
		#elseif _MASTER == 53
			#if defined @1OnYSIInit
				@1OnYSIInit(id);
			#endif
			#define OnMasterSystemInit @1OnYSIInit
		#elseif _MASTER == 54
			#if defined @2OnYSIInit
				@2OnYSIInit(id);
			#endif
			#define OnMasterSystemInit @2OnYSIInit
		#elseif _MASTER == 55
			#if defined @3OnYSIInit
				@3OnYSIInit(id);
			#endif
			#define OnMasterSystemInit @3OnYSIInit
		#elseif _MASTER == 56
			#if defined @4OnYSIInit
				@4OnYSIInit(id);
			#endif
			#define OnMasterSystemInit @4OnYSIInit
		#elseif _MASTER == 57
			#if defined @5OnYSIInit
				@5OnYSIInit(id);
			#endif
			#define OnMasterSystemInit @5OnYSIInit
		#elseif _MASTER == 58
			#if defined @6OnYSIInit
				@6OnYSIInit(id);
			#endif
			#define OnMasterSystemInit @6OnYSIInit
		#elseif _MASTER == 59
			#if defined @7OnYSIInit
				@7OnYSIInit(id);
			#endif
			#define OnMasterSystemInit @7OnYSIInit
		#elseif _MASTER == 60
			#if defined @8OnYSIInit
				@8OnYSIInit(id);
			#endif
			#define OnMasterSystemInit @8OnYSIInit
		#elseif _MASTER == 61
			#if defined @9OnYSIInit
				@9OnYSIInit(id);
			#endif
			#define OnMasterSystemInit @9OnYSIInit
		#elseif _MASTER == 62
			#if defined @@OnYSIInit
				@@OnYSIInit(id);
			#endif
			#define OnMasterSystemInit @@OnYSIInit
		#elseif _MASTER == 63
			#if defined @_OnYSIInit
				@_OnYSIInit(id);
			#endif
			#define OnMasterSystemInit @_OnYSIInit
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
	P:1("%d: " #_YCM "() <y> called, master = %d", Master_ID(), getproperty(9, #_YCM));
	if (getproperty(9, #_YCM) == Master_ID())
	{
		P:2(#_YCM " natural end");
		if (YSI_gModuleShutdown)
		{
			// Disable the current mastership.
			state _YCM:w;
			_YCM@ = _E_YCM@w;
			return;
		}
		P:2(#_YCM " not shut down");
		// Disable the current mastership.
		state _YCM:p;
		_YCM@ = _E_YCM@p;
		// Ending normally, relinquish control peacefully to the highest version.
		setproperty(8, YSIM_VERMAX, 0);
		CallRemoteFunction(#MAKE_YCM<YSIM_VERSION...>, YSI_EMPTY);
		setproperty(9, #_YCM, 0);
		// Called locally to begin the hand off process.
		_Master_UnnameAll(_MASTER);
		CallRemoteFunction(#_YCM, YSI_EMPTY);
	}
	else
	{
		P:2(#_YCM " stolen!");
		// Brutally stolen, but can be later reclaimed.
		state _YCM:n;
		_YCM@ = _E_YCM@n;
		_Master_Relinquish(#_YCM);
		_Master_UnnameAll(_MASTER);
	}
	if (getproperty(9, #_YCM))
	{
		// This is where we need to to the handoff.
		CallLocalFunction(#MAKE_YCM<HANDOFF_SOURCE...>, YSI_EMPTY);
		CallLocalFunction(#MAKE_YCM<HANDOFF_SOURCE...Group>, YSI_EMPTY);
	}
}

public _YCM() <_YCM:n>
{
	P:1("%d: " #_YCM "() <n> called", Master_ID());
	if (YSI_gModuleShutdown)
	{
		// This wasn't the master, but is in a module that's now shutting down.  null-route all
		// further calls.
		state _YCM:p;
		_YCM@ = _E_YCM@p;
	}
	else
	{
		// This has been called remotely from a script which owns the
		// library masterhood (that's the only way this can ever be called).
		Master_GetCurrentMaster(0);
	}
}

public _YCM() <_YCM:m, _YCM:p>
{
	P:1("%d: " #_YCM "() <m,p> called", Master_ID());
	// Do nothing at all (just define states).
}

public _YCM() <_YCM:u>
{
	// Finish initialisation.
	P:1("%d: " #_YCM "() <u> called", Master_ID());
	state _YCM:y;
	_YCM@ = _E_YCM@y;
}

public _YCM() <_YCM:w>
{
	P:1("%d: " #_YCM "() <w> called", Master_ID());
	// Disable the current mastership.
	state _YCM:p;
	_YCM@ = _E_YCM@p;
	
	// Ending normally, relinquish control peacefully to the highest version.
	setproperty(8, YSIM_VERMAX, 0);
	CallRemoteFunction(#MAKE_YCM<YSIM_VERSION...>, YSI_EMPTY);
	setproperty(9, #_YCM, 0);
	// Called locally to begin the hand off process.
	CallRemoteFunction(#_YCM, YSI_EMPTY);

	// Now try pass everything off.
	if (getproperty(9, #_YCM))
	{
		// This is where we need to to the handoff.
		CallLocalFunction(#MAKE_YCM<HANDOFF_SOURCE...>, YSI_EMPTY);
		CallLocalFunction(#MAKE_YCM<HANDOFF_SOURCE...Group>, YSI_EMPTY);
	}
}

public _YCM() <>
{
	// Do nothing at all (just define states).
	P:E("%d: " #_YCM "() <> called", Master_ID());
}

