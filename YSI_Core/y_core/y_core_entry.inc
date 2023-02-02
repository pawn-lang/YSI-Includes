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

// Similar to `YSI_KEYWORD`, but disabled by default.
#define YSI_OPTIONAL(%0) (defined YSI_KEYWORD_%0 && !defined YSI_NO_KEYWORD_%0)

// Define "volatile" as nothing.
#if !defined volatile
	#define volatile
#endif

// The most first include, since it determines compiler settings that might be
// used by literally any other include.
#include "y_compilerdata"

// The second include, because it sets up comments in all the others and has no
// non-standard code.  Needs compiler pass information though.
#include "y_pawndoc"

// Avoid an error with `forward OnRuntimeError(code, &bool:suppress);` in here after already ALS
// hooking it (#266).
#tryinclude "..\..\crashdetect"
#tryinclude <crashdetect>
#tryinclude "..\..\..\crashdetect"
#tryinclude "crashdetect"

// `FIX_OnRconCommand` and `FIX_OnClientCheckResponse` might use `_FIXES_DEFAULT`.

#if defined YSI_OPEN
	#if 1 YSI_OPEN.MP == 1
		#define YSI_OPENMP__
	#endif
#endif

#if defined _INC_SAMP_Community_fixes
	#if defined FIXES_DefaultDisabled
		#if FIXES_DefaultDisabled == 1
			#define _FIXES_DEFAULT (0)
		#elseif FIXES_DefaultDisabled == 2
			#define _FIXES_DEFAULT FIXES_EnableAll
		#else
			#define _FIXES_DEFAULT (1)
		#endif
	#else
		#define _FIXES_DEFAULT (1)
	#endif

	#if !defined FIX_OnRconCommand || !defined FIX_OnClientCheckResponse
		#define YSI_FIX_CALLBACKS
	#else
		#if FIX_OnRconCommand == 0 && FIX_OnClientCheckResponse == 0
			#define YSI_FIX_CALLBACKS
		#endif
	#endif

	#undef _FIXES_DEFAULT
#else
	#define YSI_FIX_CALLBACKS
#endif

/**
 * <library>y_core</library>
 * <remarks>
 *   This variable denotes that someone has signed the contract promising not to
 *   complain when things go wrong in YSI if they disable all the checks.  You
 *   need to know what you're doing in pawn in order to use YSI in this way, and
 *   thus also to sign the contract.  To date no-one has ever figured out how to
 *   do this, despite the fact that it is written right here in the code.
 * </remarks>
 */
#if defined ENABLE_YSI_UNSAFE_STARTUP && defined @_I_KNOW_WHAT_IM_DOING_AND_KNOW && defined @_THAT_USING && defined @___ENABLE_YSI_UNSAFE_STARTUP__ && defined @_MAY_RESULT_IN_STARTUP_CRASHES && defined @_AND_OTHER_BROKEN_CODE && defined @_HEREBY_PROMISE_I_WONT_RELEASE && defined @_ANY_CODE_WITH_IT_ENABLED && defined @_THAT_ALL_RESULTING_ERRORS_AND && defined @_CRASHES_ARE_SOLEY_MY_OWN && defined @_RESPONSIBILITY_NOT_Y_Less && defined @_SIGNED
	#if 1 @_THAT_USING: != 1
		#error ENABLE_YSI_UNSAFE_STARTUP contract incomplete.  Please complete it!
	#endif
	#if 1 @_AND_OTHER_BROKEN_CODE.__I != 1
		#error ENABLE_YSI_UNSAFE_STARTUP contract incomplete.  Please complete it!
	#endif
	#if 1 @_ANY_CODE_WITH_IT_ENABLED,_AND != 1
		#error ENABLE_YSI_UNSAFE_STARTUP contract incomplete.  Please complete it!
	#endif
	#if 1 @_RESPONSIBILITY_NOT_Y_Less'. != 1
		#error ENABLE_YSI_UNSAFE_STARTUP contract incomplete.  Please complete it!
	#endif
	
	#define _YSI_SAFE_STARTUP 0
	stock const
		YSI_gcUnsafeStartupContract[] = #@_SIGNED;

	#if sizeof (YSI_gcUnsafeStartupContract) == 1
		#error ENABLE_YSI_UNSAFE_STARTUP contract unsigned.  Please sign it!
	#endif
#elseif defined ENABLE_YSI_UNSAFE_STARTUP || defined @_I_KNOW_WHAT_IM_DOING_AND_KNOW || defined @_THAT_USING || defined @___ENABLE_YSI_UNSAFE_STARTUP__ || defined @_MAY_RESULT_IN_STARTUP_CRASHES || defined @_AND_OTHER_BROKEN_CODE || defined @_HEREBY_PROMISE_I_WONT_RELEASE || defined @_ANY_CODE_WITH_IT_ENABLED || defined @_THAT_ALL_RESULTING_ERRORS_AND || defined @_CRASHES_ARE_SOLEY_MY_OWN || defined @_RESPONSIBILITY_NOT_Y_Less || defined @_SIGNED
	static stock
		YSI_gcUnsafeStartupContract__ = 0;

	#error ENABLE_YSI_UNSAFE_STARTUP contract incomplete.  Please complete it!
#elseif defined _YSI_UNSAFE_STARTUP
	static stock
		YSI_gcUnsafeStartupContract__ = 0;

	#error _YSI_UNSAFE_STARTUP defined.
#else
	static stock
		YSI_gcUnsafeStartupContract__ = 0;

	#define _YSI_SAFE_STARTUP 1
#endif

#if !defined YSI_TEMP_FILE_LENGTH
	// Filename size.
	#define YSI_TEMP_FILE_LENGTH (10)
#endif

#if !defined YSI_TEMP_FILE_AGE
	// 1 month.
	#define YSI_TEMP_FILE_AGE (60 * 60 * 24 * 30)
#endif

stock const
	/**
	 * <library>y_core</library>
	 */
	YSI_TEMP_FILE_NAME[] = ".tempfiles";

#define YSI_DIR_LENGTH (12)

#if !defined _DEBUG
	#define _DEBUG 0
#endif

/// <p/>

/**
 * <library>y_core</library>
 */

enum E_YSI_DIR
{
#if _DEBUG
	E_YSI_DIR_DEBUG,
#endif
#if defined YSI_TESTS
	E_YSI_DIR_TESTS,
	E_YSI_DIR_YDBG,
#endif
	//E_YSI_DIR_TEXT,
	//E_YSI_DIR_USERS,
	E_YSI_DIR_FIXES,
	E_YSI_DIR_TEMP
}
static stock E_YSI_DIR:_@E_YSI_DIR() { return E_YSI_DIR; }

forward bool:DumpAMX_Write(const filename[]);
forward GetYSIScriptfilesDir(E_YSI_DIR:dir);
forward bool:DisasmWrite(const filename[]);

#define Master_ID() (@_)

/**
 * <library>y_core</library>
 * <remarks>
 *   The ID of this script.  <c>-1</c> initially in case there is no master
 *   system.  So we respond to everything.
 * </remarks>
 */
#if defined FIXES_ID
	static stock
		y_core_MasterID = 0;
#else
	public
		@_ = -1;
#endif

/**
 *   <remarks>
 *   If running on SA:MP this will remain <c>0</c>, open.mp will set it.
 *   open.mp versions look like:
 *   <code>
 *      01.04.02.0544
 *   </code>
 *   Thus they are encoded here as:
 *   <code>
 *      (major << 28) | (minor << 21) | (patch << 14) | (prerel)
 *   </code>
 *   </remarks>
 */
#if defined __OPEN_MP_VERSION
	static stock
		y_core_OPEN_MP_VERSION = 0;
#else
	public const
		__OPEN_MP_VERSION = 0;
	#pragma unused __OPEN_MP_VERSION
#endif

// Magical macro.
#define u@$ 1]);
//#define MY_THING u@(u[_:%0 u@$

// These three includes are just defines.  They declare no code at all, only
// variables.
#include "y_globaltags"
#include "y_prehook"
#include "y_stripnumbers"
#include "y_samp_natives"

#include "y_shortvar"
#include "y_pp"
#include "y_emit"
#include "y_als_impl"

// A few nicely named short strings used for properties.
#define YSIM_MASTER #M

/**
 * <library>y_core</library>
 * <remarks>
 *   The property name used for some short code.
 * </remarks>
 */
stock const YSIM_VERRET[] = "W";

/**
 * <library>y_core</library>
 * <remarks>
 *   The property name used for some short code.
 * </remarks>
 */
stock const YSIM_VERMAX[] = "X";
#define YSIM_RETURN #R
#define YSIM_CALLER #C
#define YSIM_TEXT_D #T
#define YSIM_TXTFND #X
#define YSIM_TXTIND #I
#define YSIM_LOG_IN #U
#define YSIM_VARARG #V

#define Debug_Error(%1); \
	Debug_Print0("\7\7\7*** YSI Error: " #%1);

#define Debug_Warning(%1); \
	Debug_Print0("\7*** YSI Warning: " #%1);

#define Debug_Info(%1); \
	Debug_Print0("*** YSI Info: " #%1);

#define Debug_Fatal(%1); \
	Debug_Print0("\7\7\7\7\7*** YSI Fatal Error: " #%1),Debug_Kill_();

// New create the `OnScriptInit` and `OnCodeInit` callbacks, which many YSI
// includes use to start themselves.
#include "y_scriptinit_impl"

// The ever loved `y_version`.
#include "y_version"

#if defined YSI_TESTS
	#define _Y_CORE_STATIC
#else
	#define _Y_CORE_STATIC static
#endif

// More common utilities and user-facing functions.
#include "y_debug_impl"
#if cellbits == 32
	#include "y_cell32"
#else
	#include "y_cell64"
#endif
#include "y_cell_impl"
#include "y_amx_impl"
#include "y_shortfunc"
#include "..\..\YSI_Players\y_android\y_android_entry"

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *   Thank you for using YSI!
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Y_Less_says_ta_for_using_YSI();

public Y_Less_says_ta_for_using_YSI()
{
}

/*-------------------------------------------------------------------------*//*+
 * <remarks>
 *   No pawndoc comments for this function, it only exists in internal tests.
 * </remarks>
 *//*------------------------------------------------------------------------**/
#if defined YSI_TESTS && __COMPILER_FUNC_DECL_BUG
	#if (__COMPILER_FIRST_PASS && !defined IsNumeric) || defined YSI_IsNumericTest__
		// Test a compiler crash doesn't.
		stock IsNumeric(const number[])
		{
			Debug_Print4("IsNumeric called: \"%s\"", number);
			// This function is copied in `y_utils_impl` to test a compiler bug.
			new
				i = -1;
			if (YSI_IsLocalVarPackedString__(number))
			{
				if (number{0} == '-') ++i;
				while ('0' <= number{++i} <= '9') {}
				return !number{i};
			}
			else
			{
				if (number[0] == '-') ++i;
				while ('0' <= number[++i] <= '9') {}
				return !number[i];
			}
		}

	#if __COMPILER_WARNING_SUPPRESSION
		// On old compilers, only issue the warning at the call site.
		#pragma warning push
		#pragma warning disable 234
	#endif

		#pragma deprecated Use `IsNumeric` (i.e. use proper capitalisation).
		stock isnumeric(const number[])
		{
			return IsNumeric(number);
		}

	#if __COMPILER_WARNING_SUPPRESSION
		#pragma warning pop
	#endif

		// Ensure this branch is hit a second time.
		stock YSI_IsNumericTest__()
		{
		}
	#endif
#endif

#include "../y_utils/y_utils_misc"
#include "../y_utils/y_utils_maths"
#include "../y_utils/y_utils_varargs"
#include "../y_utils/y_utils_arrays"
#include "../y_utils/y_utils_colour"
#include "../y_utils/y_utils_conversions"
#include "../y_utils/y_utils_encodings"
#include "../y_utils/y_utils_strings"
#include "../y_utils/y_utils_files"
#include "../y_utils/y_utils_ip"
#include "../y_utils/y_utils_names"
#include "../y_utils/y_utils_random"
#include "../y_utils/y_utils_similarity"
#include "../y_utils/y_utils_textwrap"

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <remarks>
 *   Calls all the <c>@init(init_code)</c> functions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

ScriptInit_CodeInitFuncs_()
{
	new
		idx = 0,
		ptr = 0;
	while ((idx = AMX_GetPublicPointerPrefix(idx, ptr, _A<@y_I>)))
	{
		#emit PUSH.C     0
		#emit LCTRL      __cip
		#emit ADD.C      __9_cells
		#emit LCTRL      __jmp
		#emit PUSH.pri
		#emit LOAD.S.pri ptr
		#emit SCTRL      __cip
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <remarks>
 *   Calls all the <c>@init(init_main)</c> functions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

ScriptInit_MainInitFuncs_()
{
	new
		idx = 0,
		ptr = 0;
	while ((idx = AMX_GetPublicPointerPrefix(idx, ptr, _A<@I_y>)))
	{
		#emit PUSH.C     0
		#emit LCTRL      __cip
		#emit ADD.C      __9_cells
		#emit LCTRL      __jmp
		#emit PUSH.pri
		#emit LOAD.S.pri ptr
		#emit SCTRL      __cip
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <remarks>
 *   Calls all the <c>@init(init_script)</c> functions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

ScriptInit_PreInitFuncs_()
{
	new
		idx = 0,
		ptr = 0;
	while ((idx = AMX_GetPublicPointerPrefix(idx, ptr, _A<@yI_>)))
	{
		#emit PUSH.C     0
		#emit LCTRL      __cip
		#emit ADD.C      __9_cells
		#emit LCTRL      __jmp
		#emit PUSH.pri
		#emit LOAD.S.pri ptr
		#emit SCTRL      __cip
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <remarks>
 *   Calls all the <c>@init(init_mode)</c> functions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

ScriptInit_PostInitFuncs_()
{
	new
		idx = 0,
		ptr = 0;
	while ((idx = AMX_GetPublicPointerPrefix(idx, ptr, _A<@_yI>)))
	{
		#emit PUSH.C     0
		#emit LCTRL      __cip
		#emit ADD.C      __9_cells
		#emit LCTRL      __jmp
		#emit PUSH.pri
		#emit LOAD.S.pri ptr
		#emit SCTRL      __cip
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <remarks>
 *   Calls all the <c>@exit(exit_mode)</c> functions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

ScriptInit_PreExitFuncs_()
{
	new
		idx = 0,
		ptr = 0;
	while ((idx = AMX_GetPublicPointerPrefix(idx, ptr, _A<@Iy_>)))
	{
		#emit PUSH.C     0
		#emit LCTRL      __cip
		#emit ADD.C      __9_cells
		#emit LCTRL      __jmp
		#emit PUSH.pri
		#emit LOAD.S.pri ptr
		#emit SCTRL      __cip
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_scriptinit</library>
 * <remarks>
 *   Calls all the <c>@exit(exit_script)</c> functions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

ScriptInit_PostExitFuncs_()
{
	new
		idx = 0,
		ptr = 0;
	while ((idx = AMX_GetPublicPointerPrefix(idx, ptr, _A<@_Iy>)))
	{
		#emit PUSH.C     0
		#emit LCTRL      __cip
		#emit ADD.C      __9_cells
		#emit LCTRL      __jmp
		#emit PUSH.pri
		#emit LOAD.S.pri ptr
		#emit SCTRL      __cip
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_code</library>
 * <param name="var">The variable to modify.</param>
 * <param name="val">The new value.</param>
 * <returns>
 *   The old value of the variable.
 * </returns>
 * <remarks>
 *   Bypasses the compiler to modify a <c>const</c>.  This should obviously not
 *   be done without extreme care.  The general rule is only use this if the
 *   change is promptly undone, so the changes are not externally visible from a
 *   function.  For example when adding a null terminator to a constant string
 *   to display it, then restoring it before ending:
 *
 *   <code>
 *     PrintSome(const string[], n)                 <br />
 *     {                                            <br /><indent />
 *         new ch = _YSI_ConstMod(string[n], '\0'); <br /><indent />
 *         print(string);                           <br /><indent />
 *         _YSI_ConstMod(string[n], ch);            <br />
 *     }
 *   </code>
 *
 *   That will add a null terminator, use the shorter string, then (most
 *   importantly) restore the old value of the string before the function ends.
 *   From the perspective of anyone calling this example function the string is
 *   the same after the call as it was before the call, hence the guarantees
 *   offered by <c>const</c> are maintained, even if there's some internal
 *   trickery going on.
 *   <p />
 *   It is also used to set <c>final</c> values, which aren't restored to their
 *   old value, they are set once and never changed again.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_CONST_REF
	#pragma warning push
	#pragma warning disable 238
#endif

stock _YSI_ConstMod(const &var, const val)
{
	#pragma unused var, val
	#emit LREF.S.pri var
	#emit LOAD.S.alt val
	#emit SREF.S.alt var
	#emit RETN
	__pragma("naked");
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

#if defined YSI_YES_MODE_CACHE
	#include "..\..\YSI_Server\y_thirdpartyinclude\y_thirdpartyinclude_entry"
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_code</library>
 * <remarks>
 *   I tried so many ways to fully break `SCM` for all cases:
 *   <ul>
 *     <li><c>#define</c> to give a redefinition warning.</li>
 *     <li>Using a function to stop <c>#undef</c>.</li>
 *     <li>Mixing compiler passes to make it both function and macro together.</li>
 *   </ul>
 *   Couldn't get it to work in all cases.  There's always a way around it.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated It's just unreadable rubbish.
stock DONT_USE_SCM(a, b, const c[])
{
	#pragma unused a, b, c
}
#if defined SCM
	#undef SCM
#endif
#define SCM D0NT_USE

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#define __COMPILER_EARLY_PASS

