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

#if defined FORMAT_REPLACE_NATIVES
	#if FORMAT_REPLACE_NATIVES && defined FormatSpecifier
		// The `formatex` library was included first.  Make the defines nicer so
		// that they don't conflict with native redefinitions.
		#undef printf
		#undef format
		#define format( formatex(
		#define printf( printfex(
		#define _ALS_format
		#define _ALS_printf
	#endif
#endif

// TODO: Detect new line requirements.
//
// TODO: Figure out what I meant by that `TODO` above...

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   These should pretty much always exist, but are defined in "a_samp" in SA:MP,
 *   when they should really be "core" functions.  They are defined in "console"
 *   in open.mp, and here in YSI so that they are always available.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native YSI_Print__(const string[]) = print;

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   These should pretty much always exist, but are defined in "a_samp" in SA:MP,
 *   when they should really be "core" functions.  They are defined in "console"
 *   in open.mp, and here in YSI so that they are always available.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native YSI_PrintF__(const format[], GLOBAL_TAG_TYPES:...) = printf;

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   The name of the public wrapper function to call.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock const
	YSI_gscTimerStub[] = "@_yT";

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   This is a tiny stub function to call other public functions via an address
 *   instead of via a name.  This allows the compiler to skip functions that
 *   aren't used at all.  It does require amx-assembly though.  The prefix
 *   <c>@_yT</c> is used to denote timers in <em>y_timers</em>, so we may as
 *   well reuse it here for the ultimate timer.  I might even rewrite
 *   <em>y_timers</em> to use this timer.
 * </remarks>
 *//*------------------------------------------------------------------------**/

@_yT(addr);

@_yT(addr)
{
	// Reset the frame.
	#emit POP.pri
	#emit SCTRL        5
	// Get the return address (always 0).
	#emit POP.alt
	// Decrease the parameter count.
	#emit POP.pri
	#emit ADD.C        __m1_cell
	// Get the target address.
	#emit SWAP.pri
	#emit PUSH.alt
	#emit SCTRL        __cip
}

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   <c>SetTimer</c> version that takes function addresses, not names.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock SetTimerAddr(addr, time, bool:repeat)
{
	return SetTimerEx(__const(YSI_gscTimerStub), time, repeat, __const(YSI_gcI), addr);
}

#if defined _ALS_SetTimer
	#undef SetTimer
#endif
#define _ALS_SetTimer

// Force all function passed to `SetTimer` to have no parameters.
#define @yS2:addressof(%0<%9><>) @yS2:addressof(%0<>)

#define SetTimer(&%0,%1) SetTimerAddr(_:@yS2:addressof(%0<>),%1)

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   <c>SetTimerEx</c> version that takes function addresses, not names.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock SetTimerExAddr(dummy__ = 0, time, bool:repeat, const fmt[], addr, GLOBAL_TAG_TYPES:...)
{
	#pragma unused time, repeat
	Q@ = "i",
	strcat(Q@, fmt, sizeof (Q@));
	
	// Convert the address parameter to a reference to an address.  This is
	// better than making `addr` a reference, which would seem to be correct.
	// It avoids a load of additional heap allocations and actually compiles
	// when using the `addressof` macro (which could be fixed by not using
	// `?1:2` in it, but that's not important).
	#emit LOAD.S.pri   addr
	#emit STOR.pri     I@
	#emit CONST.pri    I@
	#emit STOR.S.pri   addr
	#emit CONST.pri    Q@
	#emit STOR.S.pri   fmt
	
	// Inject the target function.
	#emit CONST.pri    YSI_gscTimerStub
	#emit STOR.S.pri   dummy__
	
	// Restore the frame.
	#emit POP.pri
	#emit SCTRL        __frm
	
	// Get the return address.
	#emit POP.alt
	
	// Call the function.
	#emit SYSREQ.C     SetTimerEx
	
	// Return.
	#emit PUSH.alt
	#emit PROC
	#emit RETN
	
	return 0;
}

#if defined _ALS_SetTimerEx
	#undef SetTimerEx
#endif
#define _ALS_SetTimerEx

// Normal addressof.
// TODO: Extract the format specifier.
#define @yS0:@yS1:addressof(%0<%8>) addressof(%0<%8>)
// Ensure the parameters are correct.
#define Y_HOOKS_ADDRESSOF(%0(%1)) (O@D_:O@A_())?(((_:%0(%1)),O@V_)?1:2):(O@V_)
#define @yS1:addressof(%0),%1) (Y_HOOKS_ADDRESSOF(%0(%1))),%1)

#define SetTimerEx(&%0,%1,%2,%3,%4) SetTimerExAddr(_,%1,%2,%3,_:@yS0:@yS1:addressof(%0),%4)

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   Const-correct <c>HTTP</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if !defined HTTP_METHOD
	#define HTTP_METHOD: _:
#endif
native YSI_HTTP__(index, HTTP_METHOD:method, const url[], const data[], const callback[]) = HTTP;

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   Const-correct <c>format</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native YSI_Format__(dest[], size = sizeof (dest), const format[], GLOBAL_TAG_TYPES:...) = format;

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   Const-correct <c>SendClientCheck</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native YSI_SendClientCheck__(playerid, type, memoryAddress, memoryOffset, byteCount) = SendClientCheck;

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   Const-correct <c>SHA256_PassHash</c>.  Also tries to discourage its usage
 *   without actually deprecating it.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native YSI_SHA256Hash_BAD_DONT_USE__(const password[], const salt[], output[], size = sizeof (output)) = SHA256_PassHash;

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   Case-correct <c>random</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native YSI_Random__(max) = random;

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   Case-correct <c>memcpy</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native _YSI_ConstCpy__(const dst[], const src[], index, numbytes, maxlength) = memcpy;

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   Case-correct <c>CallRemoteFunction</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native YSI_CallRemoteFunction__(const function[], const format[], GLOBAL_TAG_TYPES:...) = CallRemoteFunction;

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   Case-correct <c>CallLocalFunction</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native YSI_CallLocalFunction__(const function[], const format[], GLOBAL_TAG_TYPES:...) = CallLocalFunction;

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   Case-correct <c>strunpack</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native YSI_StrUnpack__(dest[], const source[], maxlength = sizeof (dest)) = strunpack;

#define YSI_JOIN(%0,%1,%2) %0And%1And%2

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   Case-correct <c>fgetchar</c>, with macros to hide the superfluous parameter.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native _YSI_FGetChar__(File:handle, value, bool:utf8 = true) = fgetchar;
#define YSI_FGetChar__(%0,%1) _YSI_FGetChar__((%0),_:(%1),(%1))

#if !defined DIALOG_STYLE
	#define DIALOG_STYLE: _:
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   Original version of <c>numargs</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native YSI_NumArgs() = numargs;

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   Inlined version of <c>numargs</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER___EMIT_U
	#if defined _ALS_numargs
		static stock YSI_numargs__()
		{
			return 0;
		}
		#undef numargs
	#else
		native BAD_numargs() = numargs;
		#define _ALS_numargs
	#endif
	// `numargs` implementation in fewer instructions than just calling the
	// native, let alone adding in what the native does.
	#define numargs() __emit(LOAD.S.pri __args_offset, SHR.C.pri __cell_shift)
#elseif defined _ALS_numargs
	static stock YSI_numargs__()
	{
		return 0;
	}
#else
	native BAD_numargs() = numargs;
#endif

forward bool:YSI_IsLocalVarPackedString__(const string:str[]);

#if __COMPILER___EMIT_U
	#define YSI_IsLocalVarPackedString__(%0) \
		__emit(                           \
			LREF.S.pri           %0      ,\
			CONST.alt            ucharmax,\
			GRTR                          \
		)
	#endinput
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <summary>
 *   YSI_IsLocalVarPackedString__(str[]);
 * </summary>
 * <param name="str">The string to test the packing of.</param>
 * <remarks>
 *   There is a bug in the SA:MP implementation of <c>ispacked</c>, it doesn't
 *   work with high unicode values.  This is fixed in open.mp, and the same fix
 *   is used here (just change the comparison to unsigned).  The inline assembly
 *   version above is actually faster than the native for locals.  This code only
 *   works on local variables because <c>LREF.U</c> doesn't work for array names,
 *   only individual cells, hence the weird function name.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:YSI_IsLocalVarPackedString__(const string:str[])
{
	#emit LREF.S.pri           str
	#emit CONST.alt            ucharmax
	#emit GRTR
	#emit RETN

	return false;
}

