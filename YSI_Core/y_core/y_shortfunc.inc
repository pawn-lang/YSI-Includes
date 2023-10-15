#if defined _INC_y_shortfunc
	#endinput
#endif
#define _INC_y_shortfunc

/**
 * <library
 *   name="y_shortfunc"
 *   version="0.2"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Defines new names for native functions."
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

// 
// A@ - PARSER_DROP()
// B@ - Fix "On"
// C@ - New `C:`.
// D@ - CallRemoteFunction wrapper
// E@ - Set caller / LENGTH_REQUIRED{}
// F@ - Also get string return without caller / PARSER_NO:
// G@ - Ignore parameters with string return / PARSER_GRP:
// H@ - Ignore parameters / PARSER_ID:
// I@ - Temp var
// J@ - Temp var
// K@ - CallRemoteFunction string return wrapper
// L@ - Return storage / PARSER_WANT:
// M@ - y_svar callback
// N@ - y_uvar callback
// O@ - SetTimerEx
// P@ - New `P:`.
// Q@ - Temp string
// R@ - CallLocalFunction
// S@ - Get string return
// T@ - String return storage
// U@ - setproperty
// V@ - getproperty
// W@ - CallRemoteFunction
// X@ - Set return
// Z@ - Detect string
// @_ - Script ID
// _@ - Unused function prefix
// @@ - Public function prefix
// 
// I didn't want to use `@@` for that, but there is some symmetry to it - now
// all these internal macros end with `@`, and the one that needs to be public
// starts with `@` as well.  I'm still saving `#define @` for something very
// VERY special.  It's taken several years, but I finally have an idea of what
// it would be good for - the indirection operator.  I won't say more yet...
// 

static stock
	/**
	 * <library>y_shortfunc</library>
	 */
	YSI_g_sPropVarArg[3] = __COMPILER_UNPACK YSIM_VARARG,
	/**
	 * <library>y_shortfunc</library>
	 */
	YSI_g_sCallData = 0;

static stock const
	/**
	 * <library>y_shortfunc</library>
	 */
	YSI_g_sPropCaller[] = YSIM_CALLER,
	/**
	 * <library>y_shortfunc</library>
	 */
	YSI_g_sPropReturn[] = YSIM_RETURN,
	/**
	 * <library>y_shortfunc</library>
	 */
	YSI_g_sYSIM_STRING = YSIM_STRING,
	/**
	 * <library>y_shortfunc</library>
	 */
	YSI_g_sYSI_MAX_STRING = YSI_MAX_STRING;

/*-------------------------------------------------------------------------*//**
 * <library>y_shortfunc</library>
 * <returns>
 *   A number, the result of a named function call.
 * </returns>
 * <remarks>
 *   <c>CallRemoteFunction</c> wrapper that handles references and string
 *   returns.  Once the call is complete it loops through the specifier string to
 *   look for any <c>v</c>s and gets their return values from specially named
 *   properties (<c>"V" + idx</c> in group 8).  Can also call in the current
 *   script instead of a remote script.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock K@(const function[], const fmat[], GLOBAL_TAG_TYPES:...)
{
	Debug_Print5("K@ called: %s, %s", function, fmat);

	#pragma unused function
	// New implementation of "CallRemoteFunction".  Wraps the old function
	// efficiently (using assembly stack manipulation tricks, better even than
	// the ones in "y_va" since we have more control over exactly how this is
	// called and what other locals there are).  Also pushes and pops the
	// current master, and uses properties for return values instead of normal
	// ones which don't work well for "CallRemoteFunction" (they depend on
	// script call order).
	
	// Swap the last two parameters - one is the hidden return value, the other
	// is the hidden master ID pointer.
	#emit LOAD.S.pri   __args_offset
	#emit ADDR.alt     __param0_offset
	#emit ADD
	#emit PUSH.pri
	#emit ADD.C        __1_cell
	#emit PUSH.pri
	#emit LREF.S.pri   __local0_offset
	#emit LREF.S.alt   __local1_offset
	#emit SREF.S.pri   __local1_offset
	#emit SREF.S.alt   __local0_offset
	#emit STACK        __2_cells
	
	// Push the current master ID on to the master stack.  Returns the old
	// master ID stored in the property, which we can shove on to the heap to
	// restore later.
	#emit PUSH.C       Q@
	#emit PUSH         @_
	#emit PUSH.C       YSI_g_sPropCaller
	#emit PUSH.C       8          // Property group, not in cells.
	#emit PUSH.C       __4_cells
	#emit SYSREQ.C     setproperty
	
	// Back up the frame header information and the return value.  "MOVS" copies
	// from "pri" to "alt".
	#emit STOR.S.pri   __local1_offset
	#emit HEAP         __7_cells
	#emit LCTRL        __stk
	#emit MOVS         __7_cells
	
	// Call "CallRemoteFunction".
	if (YSI_g_sCallData)
	{
		#emit STACK        __7_cells
		#emit SYSREQ.C     CallRemoteFunction
		#emit STOR.pri     YSI_g_sCallData
	}
	else
	{
		#emit STACK        __7_cells
		#emit SYSREQ.C     CallLocalFunction
		#emit STOR.pri     YSI_g_sCallData
	}
	{}
	
	// Restore the stack.
	#emit STACK        __m7_cells
	#emit STACK        0          // Load new stack pointer in to "alt".
	#emit LCTRL        __hea
	#emit ADD.C        __m7_cells
	#emit MOVS         __7_cells
	#emit HEAP         __m7_cells
	
	// Restore the master caller.  Already pushed the parameters earlier, before
	// backing them up on the heap (saved extra work now sorting out which saved
	// parameter went where).
	#emit SYSREQ.C     setproperty
	
	if (YSI_g_sCallData)
	{
		// Get the return value.  Already have most of the parameters pushed,
		// just modify one of them (the name).
		#emit CONST.pri    YSI_EMPTY
		#emit STOR.S.pri   __local2_offset
		#emit LOAD.pri     YSI_g_sYSIM_STRING
		#emit STOR.S.pri   __local1_offset
		#emit SYSREQ.C     getproperty
		
		// Unpack the return to the previous function's return string.
		#emit PUSH         YSI_g_sYSI_MAX_STRING
		#emit PUSH.C       Q@
		#emit LOAD.S.pri   __frame_offset
		#emit MOVE.alt
		#emit ADD.C        __2_cells
		#emit LOAD.I
		#emit ADD.C        __3_cells
		#emit ADD
		#emit LOAD.I
		#emit PUSH.pri
		#emit PUSH.C       __3_cells
		#emit SYSREQ.C     strunpack
		
		// Get all the varargs (without using our corrupted stack).
		static i = 0, j = 0, ch = 0;
		if (YSI_IsLocalVarPackedString__(fmat))
		{
			for (i = j = 0; (ch = fmat{i}); ++i) if (ch == 'd')
			{
				YSI_g_sPropVarArg[1] = '@' + ++j;
				Debug_Print7("K@: Write back: %d %d %d %s %d", i, j, ch, YSI_g_sPropVarArg, getproperty(8, YSI_g_sPropVarArg));
				setarg(i + 2, 0, getproperty(8, YSI_g_sPropVarArg));
			}
		}
		else
		{
			for (i = j = 0; (ch = fmat[i]); ++i) if (ch == 'd')
			{
				YSI_g_sPropVarArg[1] = '@' + ++j;
				Debug_Print7("K@: Write back: %d %d %d %s %d", i, j, ch, YSI_g_sPropVarArg, getproperty(8, YSI_g_sPropVarArg));
				setarg(i + 2, 0, getproperty(8, YSI_g_sPropVarArg));
			}
		}
	}
	else
	{
		// NULL the return.
		#emit LOAD.S.pri   __frame_offset
		#emit MOVE.alt
		#emit ADD.C        __2_cells
		#emit LOAD.I
		#emit ADD.C        __3_cells
		#emit ADD
		#emit LOAD.I
		#emit MOVE.alt
		#emit ZERO.pri
		#emit STOR.I
	}
	{}
	
	// Return from two functions at once, while unpopping all our data.  By
	// doing this we know out string return fix/optimisation will apply.
	#emit LOAD.S.pri   __frame_offset
	#emit SCTRL        __frm
	#emit LOAD.S.alt   __local0_offset
	#emit SCTRL        __stk
	#emit MOVE.pri
	#emit SCTRL        __hea
	#emit ZERO.pri
	#emit RETN
	
	// Let the compiler do size checks.  There is a bug in the old compiler
	// where returning a string from a varargs function won't work, we work
	// around that bug by using raw assembly.  We also make the return more
	// efficient by unpacking straight in to the destination, instead of
	// unpacking to a local array then copying that to the return, as even the
	// new compiler would do with separate statements.  Fortunately, the old
	// compiler at least gets the size checks right, we so have that going for
	// us - meaning that we know that code that compiles will return correctly.
	return Q@;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_shortfunc</library>
 * <returns>
 *   A string, the result of a named function call.
 * </returns>
 * <remarks>
 *   <c>CallRemoteFunction</c> wrapper that handles references and string
 *   returns.  Once the call is complete it loops through the specifier string to
 *   look for any <c>v</c>s and gets their return values from specially named
 *   properties (<c>"V" + idx</c> in group 8).  Can also call in the current
 *   script instead of a remote script.  Also uses properties to enable returning
 *   remote strings.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock D@(const function[], const fmat[], GLOBAL_TAG_TYPES:...)
{
	Debug_Print5("D@ called: %s, %s", function, fmat);

	#pragma unused function
	// New implementation of "CallRemoteFunction".  Wraps the old function
	// efficiently (using assembly stack manipulation tricks, better even than
	// the ones in "y_va" since we have more control over exactly how this is
	// called and what other locals there are).  Also pushes and pops the
	// current master, and uses properties for return values instead of normal
	// ones which don't work well for "CallRemoteFunction" (they depend on
	// script call order).
	
	// Push the current master ID on to the master stack.  Returns the old
	// master ID stored in the property, which we can shove on to the heap to
	// restore later.
	#emit PUSH.C       YSI_EMPTY
	#emit PUSH         @_
	#emit PUSH.C       YSI_g_sPropCaller
	#emit PUSH.C       8 // Property group, not in cells.
	#emit PUSH.C       __4_cells
	#emit SYSREQ.C     setproperty
	
	// Back up the frame header information and the return value.  "MOVS" copies
	// from "pri" to "alt".
	#emit STOR.S.pri   __local1_offset
	#emit HEAP         __7_cells
	#emit LCTRL        __stk
	#emit MOVS         __7_cells
	
	// Call "CallRemoteFunction".
	if (YSI_g_sCallData)
	{
		#emit STACK        __7_cells
		#emit SYSREQ.C     CallRemoteFunction
		#emit STOR.pri     YSI_g_sCallData
	}
	else
	{
		#emit STACK        __7_cells
		#emit SYSREQ.C     CallLocalFunction
		#emit STOR.pri     YSI_g_sCallData
	}
	{}
	
	// Restore the stack.
	#emit STACK        __m7_cells
	#emit STACK        0          // Load new stack pointer in to "alt".
	#emit LCTRL        __hea
	#emit ADD.C        __m7_cells
	#emit MOVS         __7_cells
	#emit HEAP         __m7_cells
	
	// Restore the master caller.  Already pushed the parameters earlier, before
	// backing them up on the heap (saved extra work now sorting out which saved
	// parameter went where).
	#emit SYSREQ.C     setproperty
	
	if (YSI_g_sCallData)
	{
		// Get the return value.  Already have most of the parameters pushed,
		// just modify one of them (the name).
		#emit CONST.pri    YSI_g_sPropReturn
		#emit STOR.S.pri   __local2_offset
		#emit SYSREQ.C     getproperty
		#emit STOR.pri     YSI_g_sCallData
		
		// Get all the varargs (without using our corrupted stack).
		static i = 0, j = 0, ch = 0;
		if (YSI_IsLocalVarPackedString__(fmat))
		{
			for (i = j = 0; (ch = fmat{i}); ++i) if (ch == 'd')
			{
				YSI_g_sPropVarArg[1] = '@' + ++j;
				Debug_Print7("D@: Write back: %d %d %d %s %d", i, j, ch, YSI_g_sPropVarArg, getproperty(8, YSI_g_sPropVarArg));
				setarg(i + 2, 0, getproperty(8, YSI_g_sPropVarArg));
			}
		}
		else
		{
			for (i = j = 0; (ch = fmat[i]); ++i) if (ch == 'd')
			{
				YSI_g_sPropVarArg[1] = '@' + ++j;
				Debug_Print7("D@: Write back: %d %d %d %s %d", i, j, ch, YSI_g_sPropVarArg, getproperty(8, YSI_g_sPropVarArg));
				setarg(i + 2, 0, getproperty(8, YSI_g_sPropVarArg));
			}
		}
	}
	{}
	
	#emit LOAD.S.pri   __frame_offset
	#emit SCTRL        __frm
	#emit LOAD.S.alt   __local0_offset
	#emit SCTRL        __stk
	#emit MOVE.pri
	#emit SCTRL        __hea
	#emit LOAD.pri     YSI_g_sCallData
	#emit RETN
	
	return 0;
}

#define @@%0\32; @@
#define _@%0\32; _@

/*-------------------------------------------------------------------------*//**
 * <library>y_shortfunc</library>
 * <remarks>
 *   A precursor to <c>D@</c> and <c>E@</c> that does some stack and heap
 *   manipulation before they are called.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock F@(calltype = 1, master = -1, heapptr = 0)
{
	Debug_Print5("F@ called: %d, %d, %d", calltype, master, heapptr);
	// First copy the calltype to a global, so it can be read from the functions
	// that actually call `CallLocalFunction` (0) and `CallRemoteFunction` (1).
	YSI_g_sCallData = calltype;
	// The store the address of the second parameter in the first parameter,
	// which means the bottom of the stack becomes a reference parameter to
	// elsewhere on the stack, and the string specifier in the call will spill
	// in to this memory.
	#emit ADDR.pri     master
	#emit STOR.S.pri   calltype
	// This function stores the heap size before certain calls so that we can
	// revert afterwards.  It puts the size on the stack, then lies about the
	// stack size for the return, so that the value stays on.
	#emit LCTRL        __hea
	#emit STOR.S.pri   heapptr
	#emit ZERO.S       __args_offset
	#emit RETN
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_shortfunc</library>
 * <remarks>
 *   Used in remote function wrappers to put reference parameter retusn in to the
 *   specially named properties (<c>"V" + idx</c> in group 8) for their return.
 *   Also put the true return number in to a property, because remote call order
 *   can't be relied on.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock L@(GLOBAL_TAG_TYPES:ret, GLOBAL_TAG_TYPES:...)
{
	Debug_Print5("L@ called: %d", ret);
	// Return possibly multiple values remotely.
	setproperty(8, YSI_g_sPropReturn, ret);
	for (new i = 1, j = numargs(); i != j; ++i)
	{
		Debug_Print7("L@: loop %d = %d", i, getarg(i));
		YSI_g_sPropVarArg[1] = '@' + i,
		setproperty(8, YSI_g_sPropVarArg, getarg(i));
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_shortfunc</library>
 * <remarks>
 *   Used in remote function wrappers to put reference parameter retusn in to the
 *   specially named properties (<c>"V" + idx</c> in group 8) for their return.
 *   Also put the true return string in to a property, because remote call order
 *   can't be relied on, and can't return strings even if it could.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock T@(const string:ret[YSI_MAX_STRING], GLOBAL_TAG_TYPES:...)
{
	Debug_Print5("T@ called: %s", ret);
	// Return possibly multiple values remotely.
	setproperty(8, YSI_EMPTY, YSIM_STRING, ret);
	for (new i = 1, j = numargs(); i != j; ++i)
	{
		Debug_Print7("T@: loop %d = %d", i, getarg(i));
		YSI_g_sPropVarArg[1] = '@' + i,
		setproperty(8, YSI_g_sPropVarArg, getarg(i));
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_shortfunc</library>
 * <remarks>
 *   Put the true remote call return number in to a property, because remote call
 *   order can't be relied on.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock X@(GLOBAL_TAG_TYPES:n)
{
	// THIS MUST REMAIN FOREVER!  Detected by fixes.inc.
	Debug_Print4("X@ called: %i", n);
	setproperty(8, YSI_g_sPropReturn, n);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_shortfunc</library>
 * <remarks>
 *   Just a dead-end for spare parameters.  Implementation of
 *   <c>__pragma("unused", x);</c>, which disables the warning for a unused
 *   variable, by using it!
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock H@(GLOBAL_TAG_TYPES:...)
{
	return 0;
}

#define _UNUSED(%0) H@(_:_H@0:_H@1:%0)
#define _H@0:_H@1:%0&%1) _H@0:_H@1:%0%1)
#define _H@1:%0[%9]%1) _H@1:%0%1)

#if _YSI_SAFE_STARTUP
	#define OnChaosTimer(%0,%1) YSI_JOIN(,r%0_On,r%0Timer)(%1)
#endif

// Correctly stringise "On" callbacks without ALS interferring.
#define B@:#On%0) "On"#%0)

/*-------------------------------------------------------------------------*//**
 * <library>y_shortfunc</library>
 * <remarks>
 *   Just a dead-end for spare parameters.  Implementation of
 *   <c>__pragma("unused", x);</c>, which disables the warning for a unused
 *   variable, by using it!  Returns a string, in case that's useful in macros.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock G@(GLOBAL_TAG_TYPES:...)
{
	// Just a dead-end for spare parameters which returns a string.
	return Q@;
}

// Consume trailing spaces.  Despite being a common letter, this is unlkely to
// ever be matched due to the unusual series of operators after it.  If anyone
// else tries to define "x" however they may have a slight problem (they can't).
#define x:##),) #))
#define q:##),ALS_RS_none:) #))

// This is for getting excess parameters on non-strings.  Now safely recursive.
#define _:%0,) _:%0)

