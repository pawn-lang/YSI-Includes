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
 *   Const-correct <c>SetTimer</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native YSI_SetTimer__(const funcname[], interval, bool:repeating) = SetTimer;

/*-------------------------------------------------------------------------*//**
 * <library>y_samp_natives</library>
 * <remarks>
 *   Const-correct <c>SetTimerEx</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native YSI_SetTimerEx__(const funcname[], interval, bool:repeating, const format[], GLOBAL_TAG_TYPES:...) = SetTimerEx;

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
 *   Const-correct <c>SendRconCommand</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native YSI_SendRconCommand__(const str[]) = SendRconCommand;

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
 *   Const- and tag-correct <c>ShowPlayerDialog</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if defined _ALS_ShowPlayerDialog
	static stock Dialog_ShowPlayerNative__(playerid, dialogid, DIALOG_STYLE:style, const caption[], const info[], const button1[], const button2[])
	{
		return false;
	}
	#define Dialog_ShowPlayerNative ShowPlayerDialog
#else
	native bool:Dialog_ShowPlayerNative(playerid, dialogid, DIALOG_STYLE:style, const caption[], const info[], const button1[], const button2[]) = ShowPlayerDialog;
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

