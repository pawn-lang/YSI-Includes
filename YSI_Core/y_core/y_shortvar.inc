#if defined _INC_y_shortvar
	#endinput
#endif
#define _INC_y_shortvar

/**
 * <library
 *   name="y_shortvar"
 *   version="0.2"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Declares a few variables with very short names, used all over YSI."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 *//** *//*
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

// VERY VERY VERY IMPORTANT!!! y_text uses "144" explicitly.  Change it too.
#if !defined YSI_MAX_STRING
	#define YSI_MAX_STRING (144)
#endif
#if YSI_MAX_STRING != 144
	//#error Please update all explicit YSI_MAX_STRING uses.
	#define Y_COMPILERDATA_WARNING 3
	#include "y_compilerdata_warning"
#endif

#if !defined YSIM_STRING
	#define YSIM_STRING (1000)
#endif

new
	/**
	 * <library>y_shortvar</library>
	 * <remarks>
	 *   A temporary string variable, mainly for interim results.
	 * </remarks>
	 */
	Q@[YSI_MAX_STRING];

stock
	/**
	 * <library>y_shortvar</library>
	 * <remarks>
	 *   A "nul" target - send things there if they need ignoring or if a
	 *   parameter needs ignoring.  Not guaranteed to keep its value for any
	 *   length of time.  If you set it, don't expect it to remain the same!
	 * </remarks>
	 */
	I@ = 0,
	/**
	 * <library>y_shortvar</library>
	 * <remarks>
	 *   A "nul" target - send things there if they need ignoring or if a
	 *   parameter needs ignoring.  Not guaranteed to keep its value for any
	 *   length of time.  If you set it, don't expect it to remain the same!
	 * </remarks>
	 */
	J@ = 0;

#if !defined MAX_LANGUAGES
	#define MAX_LANGUAGES (4)
#endif

stock
	/**
	 * <library>y_shortvar</library>
	 * <remarks>
	 *   A massive string.  That's it.  Just for internal formatting when the
	 *   length isn't known in advance and we need to just go massively OTT to
	 *   ensure that all user code works.  It is split in to individual arrays
	 *   for using per-language, but the whole lot can be used as an even bigger
	 *   concatenated string with <c>YSI_UNSAFE_HUGE_STRING</c>, of length
	 *   <c>YSI_UNSAFE_HUGE_LENGTH</c>.
	 * </remarks>
	 */
	YSI_gUnsafeHugeString[MAX_LANGUAGES][2048];

#define YSI_UNSAFE_HUGE_STRING (YSI_gUnsafeHugeString[0])
#define YSI_UNSAFE_HUGE_LENGTH (MAX_LANGUAGES * sizeof (YSI_gUnsafeHugeString[]))

/*-------------------------------------------------------------------------*//**
 * <library>y_shortfunc</library>
 * <remarks>
 *   Used by y_master and y_remote.  Re-evaluate after rewrites.  Just an alias
 *   for <c>setproperty</c>, but with a shorter name (for macro length limits)
 *   and better defaults.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native U@(id = 0, const name[] = "", value = cellmin, const string[] = "") = setproperty;

/*-------------------------------------------------------------------------*//**
 * <library>y_shortfunc</library>
 * <remarks>
 *   Used by y_master and y_remote.  Re-evaluate after rewrites.  Just an alias
 *   for <c>getproperty</c>, but with a shorter name (for macro length limits)
 *   and better defaults.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native V@(GLOBAL_TAG_TYPES:id = 0, const name[] = "", value = cellmin, string[] = "") = getproperty;

/*-------------------------------------------------------------------------*//**
 * <library>y_shortfunc</library>
 * <remarks>
 *   An alias for <c>CallLocalFunction</c>, but with a shorter name (for macro
 *   length limits) and better tag support.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined OPENMP
	native R@(const function[], const format[], GLOBAL_TAG_TYPES:...) = Script_Call;
#else
	native R@(const function[], const format[], GLOBAL_TAG_TYPES:...) = CallLocalFunction;
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_shortfunc</library>
 * <remarks>
 *   An alias for <c>CallRemoteFunction</c>, but with a shorter name (for macro
 *   length limits) and better tag support.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined OPENMP
	native W@(const function[], const format[], GLOBAL_TAG_TYPES:...) = Script_CallAll;
#else
	native W@(const function[], const format[], GLOBAL_TAG_TYPES:...) = CallRemoteFunction;
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_shortfunc</library>
 * <remarks>
 *   An alias for <c>SetTimerEx</c>, but with a shorter name (for macro length
 *   limits) and better tag support.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined OPENMP
	native O@(const function[], time, repeat, const format[] = "", GLOBAL_TAG_TYPES:...) = SetTimerEx;
#else
	native O@(const function[], time, repeat, const format[] = "", GLOBAL_TAG_TYPES:...) = SetTimerEx;
#endif

#define D0NT_USE(%9);}%9(){} }

/**
 * <library>y_shortvar</library>
 * <remarks>
 *   <c>true</c>, but usable in tests without a constant expression warning.
 * </remarks>
 */
#if defined TRUE
	static stock
		bool:TRUE__ = true;
#else
	stock const
		bool:TRUE = true;
#endif

/**
 * <library>y_shortvar</library>
 * <remarks>
 *   <c>false</c>, but usable in tests without a constant expression warning.
 * </remarks>
 */
#if defined FALSE
	static stock
		bool:FALSE__ = false;
#else
	stock const
		bool:FALSE = false;
#endif

/**
 * <library>y_shortvar</library>
 * <remarks>
 *   The null string with <c>\1</c> as the first character.  This isn't a true
 *   null string, that is the string of length 0, but this string is often used
 *   instead due to a bug with passing empty strings to and from the VM.  Every
 *   <c>IsNull</c> check ever has been designed to detect this version.
 * </remarks>
 */
#if defined NULL
	static stock
		NULL__[2] = "\1";
#else
	stock const
		NULL[2] = "\1";
#endif

#if __COMPILER_MODIFIED
	#endinput
#endif

forward @_y_shortvar_y_@();

/*-------------------------------------------------------------------------*//**
 * <library>y_shortfunc</library>
 * <remarks>
 *   The old compiler has a bug when using <c>SYSREQ.C</c> - the natives aren't
 *   marked as used, so won't be included in the output if they aren't used
 *   normally elsewhere.  This function, on the old compiler, calls the natives
 *   defined in this file to ensure that they go in to the native function table.
 *   However, they are called with nonsense parameters so this function must
 *   itself never be called.  That would normally mean that this is itself
 *   elided from the AMX, hence it is <c>public</c>.
 * </remarks>
 */

public @_y_shortvar_y_@()
{
	new tmp[2];
	// This function calls any functions used in assembly code in YSI to ensure
	// that they are included in the native function table.
	R@(tmp, tmp);
	W@(tmp, tmp);
	O@(tmp, 0, false);
}

