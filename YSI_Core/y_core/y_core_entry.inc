#if defined _INC_y_core
	#endinput
#endif
#define _INC_y_core

/*
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
	
	The Original Code is the YSI framework.
	
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

// These includes are in quite a strict order, since there's a lot of inter-
// dependencies.  That's why they're all together in here.

// Macro for checking if certain keywords should be defined.  Example:
//
//   #if YSI_KEYWORD(hook)
//       #define hook HOOK__
//   #endif
//
// This defines `hook` in the following cases:
//
//   1) Nothing special is defined (default, backwards-compatible).
//   2) `YSI_KEYWORD_hook` is defined and `YSI_NO_KEYWORD_hook` is not defined
//      (safest - will define `hook` even if someone else defines
//      `YSI_COMPATIBILITY_MODE`).
//   3) `YSI_KEYWORD_hook` and `YSI_COMPATIBILITY_MODE` are both defined.
//   4) `YSI_COMPATIBILITY_MODE` is NOT defined and neither is
//      `YSI_NO_KEYWORD_hook`.
//
// In short, if `YSI_COMPATIBILITY_MODE` is defined, custom keywords must be
// explicity enabled with `YSI_KEYWORD_name`.  If `YSI_COMPATIBILITY_MODE` is
// NOT defined, custom keywords must be explicitly disabled with
// `YSI_NO_KEYWORD_name`.  Note that the name is exactly the custom keyword (or
// more strictly, custom syntax), so may be lower- or mixed-case, not upper-case
// as most macros are.
#define YSI_KEYWORD(%0) ((defined YSI_COMPATIBILITY_MODE && defined YSI_KEYWORD_%0) || (!defined YSI_COMPATIBILITY_MODE && !defined YSI_NO_KEYWORD_%0))

// Define `cellbytes` as a symbol that really should exist already!
#if !defined cellbytes
	#define cellbytes (cellbits / 8)
#endif

// Define "volatile" as nothing.
#if !defined volatile
	#define volatile
#endif

// The most first include, since it determines compiler settings that might be
// used by literally any other include.
#include "y_compilerdata"

#if __COMPILER_sNAMEMAX != 31
	#error YSI assumes `sNAMEMAX` is 31.
#endif

#if !defined HTTP
	#tryinclude <a_http>
#endif

// Avoid an error with `forward OnRuntimeError(code, &bool:suppress);` in here after already ALS
// hooking it (#266).
#tryinclude "..\..\crashdetect"
#tryinclude <crashdetect>
#tryinclude "..\..\..\crashdetect"
#tryinclude "crashdetect"

// These three includes are just defines.  They declare no code at all, only
// variables.
#include "y_globaltags"
#include "y_pp"
#include "y_prehook"
#include "y_stripnumbers"

// These should pretty much always exist, but are defined in "a_samp" in SA:MP,
// when they should really be "core" functions.
// 
// TODO: Detect new line requirements.
native YSIPrint(const string[]) = print;
native YSIPrintF(const format[], GLOBAL_TAG_TYPES:...) = printf;

#include "y_shortvar"
#include "y_als_impl"

// A few nicely named short strings used for properties.
#define YSIM_MASTER #M
#define YSIM_RETURN #R
#define YSIM_CALLER #C
#define YSIM_TEXT_D #T
#define YSIM_TXTFND #X
#define YSIM_TXTIND #I
#define YSIM_LOG_IN #U
#define YSIM_VARARG #V

// New create the `OnScriptInit` and `OnCodeInit` callbacks, which many YSI
// includes use to start themselves.
#include "y_scriptinit_impl"

// The ever loved `y_version`.
#include "y_version"

// More common utilities and user-facing functions.
#include "y_debug_impl"
#include "y_amx_impl"
#include "y_shortfunc"
#include "y_cell_impl"
#include "y_utils_impl"

// Part of "y_scriptinit", but requires "y_amx".
ScriptInit_PreInitFuncs_()
{
	new
		idx,
		ptr;
	while ((idx = AMX_GetPublicPointerPrefix(idx, ptr, _A<@yI_>)))
	{
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      36
		#emit LCTRL      8
		#emit PUSH.pri
		#emit LOAD.S.pri ptr
		#emit SCTRL      6
	}
}

ScriptInit_PostInitFuncs_()
{
	new
		idx,
		ptr;
	while ((idx = AMX_GetPublicPointerPrefix(idx, ptr, _A<@_yI>)))
	{
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      36
		#emit LCTRL      8
		#emit PUSH.pri
		#emit LOAD.S.pri ptr
		#emit SCTRL      6
	}
}

ScriptInit_PreExitFuncs_()
{
	new
		idx,
		ptr;
	while ((idx = AMX_GetPublicPointerPrefix(idx, ptr, _A<@Iy_>)))
	{
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      36
		#emit LCTRL      8
		#emit PUSH.pri
		#emit LOAD.S.pri ptr
		#emit SCTRL      6
	}
}

ScriptInit_PostExitFuncs_()
{
	new
		idx,
		ptr;
	while ((idx = AMX_GetPublicPointerPrefix(idx, ptr, _A<@_Iy>)))
	{
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      36
		#emit LCTRL      8
		#emit PUSH.pri
		#emit LOAD.S.pri ptr
		#emit SCTRL      6
	}
}

#if __COMPILER_CONST_REF
	#pragma warning push
	#pragma warning disable 238
#endif
stock _YSI_ConstMod(const &var, const val)
{
	#pragma unused var, val
	#emit LOAD.S.pri val
	#emit SREF.S.pri var
}
#if __COMPILER_CONST_REF
	#pragma warning pop
#endif

#if defined CODE_SCAN_MAX_PATTERN
	#if CODE_SCAN_MAX_PATTERN < (32)
		#if defined CODESCAN_INC
			#error Include "YSI" before "codescan", or increase `CODE_SCAN_MAX_PATTERN`.
		#endif
		#undef CODE_SCAN_MAX_PATTERN
		#define CODE_SCAN_MAX_PATTERN (32)
	#endif
#else
	#define CODE_SCAN_MAX_PATTERN (32)
#endif

// These are conditional, and use most of the preceeding code.
#if defined YSI_TESTS
	#include "..\y_testing"
#endif

