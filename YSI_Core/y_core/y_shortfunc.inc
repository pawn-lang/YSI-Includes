/*+
 * <library name="y_shortfunc">
 * <section>
 *  Description
 * </section>
 *  Defines new names for native functions.
 * <section>
 *  Version
 * </section>
 *  0.2
 * <section>
 *  Natives
 * </section><ul>
 *  <symbol name="W@">Renaming of <symbolref name="__CallRemoteFunction" /> for size reasons.</symbol>
 *  <symbol name="V@">Renaming of <symbolref name="getproperty" /> for size reasons.</symbol>
 *  <symbol name="S@">Renaming of <symbolref name="setproperty" /> for size reasons.</symbol>
 *  <symbol name="P@">Renaming of <symbolref name="__CallLocalFunction" /> for size reasons.</symbol>
 * </ul>
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

// 
// A@ - PARSER_DROP()
// B@ - Fix "On"
// C@ - CallRemoteFunction string return wrapper
// D@ - CallRemoteFunction wrapper
// E@ - Set caller / LENGTH_REQUIRED{}
// F@ - Also get string return without caller / PARSER_NO:
// G@ - Ignore parameters with string return / PARSER_GRP:
// H@ - Ignore parameters / PARSER_ID:
// I@ - Temp var
// J@ - Temp var
// K@ - SetTimer
// L@ - Return storage / PARSER_WANT:
// M@ - y_svar callback
// N@ - y_uvar callback
// O@ - SetTimerEx
// P@ - CallLocalFunction
// Q@ - Temp string
// R@ - Set string return
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
	YSI_g_sPropVarArg[3] = YSIM_VARARG,
	YSI_g_sCallData;

static stock const
	YSI_g_sPropCaller[] = YSIM_CALLER,
	YSI_g_sPropReturn[] = YSIM_RETURN,
	YSI_g_sPropEmpty[] = "",
	YSI_g_sYSIM_STRING = YSIM_STRING,
	YSI_g_sYSI_MAX_STRING = YSI_MAX_STRING;

// CallRemoteFunction wrapper that handles references and string returns.
stock C@(const function[], const fmat[], GLOBAL_TAG_TYPES:...)
{
	P:5("C@ called: %s, %s", function, fmat);

	#pragma unused function, fmat
	// New implementation of "CallRemoteFunction".  Wraps the old function
	// efficiently (using assembly stack manipulation tricks, better even than
	// the ones in "y_va" since we have more control over exactly how this is
	// called and what other locals there are).  Also pushes and pops the
	// current master, and uses properties for return values instead of normal
	// ones which don't work well for "CallRemoteFunction" (they depend on
	// script call order).
	
	// Swap the last two parameters - one is the hidden return value, the other
	// is the hidden master ID pointer.
	#emit LOAD.S.pri   8
	#emit ADDR.alt     12
	#emit ADD
	#emit PUSH.pri
	#emit ADD.C        4
	#emit PUSH.pri
	#emit LREF.S.pri   0xFFFFFFFC
	#emit LREF.S.alt   0xFFFFFFF8
	#emit SREF.S.pri   0xFFFFFFF8
	#emit SREF.S.alt   0xFFFFFFFC
	#emit STACK        8
	
	// Push the current master ID on to the master stack.  Returns the old
	// master ID stored in the property, which we can shove on to the heap to
	// restore later.
	#emit PUSH.C       Q@
	#emit PUSH         @_
	#emit PUSH.C       YSI_g_sPropCaller
	#emit PUSH.C       8
	#emit PUSH.C       16
	#emit SYSREQ.C     setproperty
	
	// Back up the frame header information and the return value.  "MOVS" copies
	// from "pri" to "alt".
	#emit STOR.S.pri   0xFFFFFFF8 // -8
	#emit HEAP         28
	#emit LCTRL        4
	#emit MOVS         28
	
	// Call "CallRemoteFunction".
	if (YSI_g_sCallData)
	{
		#emit STACK        28
		#emit SYSREQ.C     CallRemoteFunction
		#emit STOR.pri     YSI_g_sCallData
	}
	else
	{
		#emit STACK        28
		#emit SYSREQ.C     CallLocalFunction
		#emit STOR.pri     YSI_g_sCallData
	}
	{}
	
	// Restore the stack.
	#emit STACK        0xFFFFFFE4 // -28
	#emit STACK        0          // Load new stack pointer in to "alt".
	#emit LCTRL        2
	#emit ADD.C        0xFFFFFFE4
	#emit MOVS         28
	#emit HEAP         0xFFFFFFE4
	
	// Restore the master caller.  Already pushed the parameters earlier, before
	// backing them up on the heap (saved extra work now sorting out which saved
	// parameter went where).
	#emit SYSREQ.C     setproperty
	if (YSI_g_sCallData)
	{
		// Get the return value.  Already have most of the parameters pushed,
		// just modify one of them (the name).
		#emit CONST.pri    YSI_g_sPropEmpty
		#emit STOR.S.pri   0xFFFFFFF4 // -12
		#emit LOAD.pri     YSI_g_sYSIM_STRING
		#emit STOR.S.pri   0xFFFFFFF8 // -8
		#emit SYSREQ.C     getproperty
		
		// Unpack the return to the previous function's return string.
		#emit PUSH         YSI_g_sYSI_MAX_STRING
		#emit PUSH.C       Q@
		#emit LOAD.S.pri   0
		#emit MOVE.alt
		#emit ADD.C        8
		#emit LOAD.I
		#emit ADD.C        12
		#emit ADD
		#emit LOAD.I
		#emit PUSH.pri
		#emit PUSH.C       12
		#emit SYSREQ.C     strunpack
		
		// Get all the varargs (without using our corrupted stack).
		static i, j, ch;
		for (i = j = 0; (ch = fmat[i]); ++i) if (ch == 'd')
		{
			YSI_g_sPropVarArg[1] = '@' + ++j,
			P:7("C@: Write back: %d %d %d %s %d", i, j, ch, YSI_g_sPropVarArg, getproperty(8, YSI_g_sPropVarArg));
			setarg(i + 2, 0, getproperty(8, YSI_g_sPropVarArg));
		}
	}
	else
	{
		// NULL the return.
		#emit LOAD.S.pri   0
		#emit MOVE.alt
		#emit ADD.C        8
		#emit LOAD.I
		#emit ADD.C        12
		#emit ADD
		#emit LOAD.I
		#emit MOVE.alt
		#emit ZERO.pri
		#emit STOR.I
	}
	{}
	
	// Return from two functions at once, while unpopping all our data.  By
	// doing this we know out string return fix/optimisation will apply.
	#emit LOAD.S.pri   0
	#emit SCTRL        5
	#emit LOAD.S.alt   0xFFFFFFFC
	#emit SCTRL        4
	#emit MOVE.pri
	#emit SCTRL        2
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

// CallRemoteFunction wrapper that handles references and regular returns.
stock D@(const function[], const fmat[], GLOBAL_TAG_TYPES:...)
{
	P:5("D@ called: %s, %s", function, fmat);

	#pragma unused function, fmat
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
	#emit PUSH.C       YSI_g_sPropEmpty
	#emit PUSH         @_
	#emit PUSH.C       YSI_g_sPropCaller
	#emit PUSH.C       8
	#emit PUSH.C       16
	#emit SYSREQ.C     setproperty
	
	// Back up the frame header information and the return value.  "MOVS" copies
	// from "pri" to "alt".
	#emit STOR.S.pri   0xFFFFFFF8 // -8
	#emit HEAP         28
	#emit LCTRL        4
	#emit MOVS         28
	
	// Call "CallRemoteFunction".
	if (YSI_g_sCallData)
	{
		#emit STACK        28
		#emit SYSREQ.C     CallRemoteFunction
		#emit STOR.pri     YSI_g_sCallData
	}
	else
	{
		#emit STACK        28
		#emit SYSREQ.C     CallLocalFunction
		#emit STOR.pri     YSI_g_sCallData
	}
	{}
	
	// Restore the stack.
	#emit STACK        0xFFFFFFE4 // -28
	#emit STACK        0          // Load new stack pointer in to "alt".
	#emit LCTRL        2
	#emit ADD.C        0xFFFFFFE4
	#emit MOVS         28
	#emit HEAP         0xFFFFFFE4
	
	// Restore the master caller.  Already pushed the parameters earlier, before
	// backing them up on the heap (saved extra work now sorting out which saved
	// parameter went where).
	#emit SYSREQ.C     setproperty
	
	if (YSI_g_sCallData)
	{
		// Get the return value.  Already have most of the parameters pushed,
		// just modify one of them (the name).
		#emit CONST.pri    YSI_g_sPropReturn
		#emit STOR.S.pri   0xFFFFFFF4 // -12
		#emit SYSREQ.C     getproperty
		#emit STOR.pri     YSI_g_sCallData
		
		// Get all the varargs (without using our corrupted stack).
		static i, j, ch;
		for (i = j = 0; (ch = fmat[i]); ++i) if (ch == 'd')
		{
			YSI_g_sPropVarArg[1] = '@' + ++j,
			P:7("D@: Write back: %d %d %d %s %d", i, j, ch, YSI_g_sPropVarArg, getproperty(8, YSI_g_sPropVarArg));
			setarg(i + 2, 0, getproperty(8, YSI_g_sPropVarArg));
		}
	}
	{}
	
	#emit LOAD.S.pri   0
	#emit SCTRL        5
	#emit LOAD.S.alt   0xFFFFFFFC
	#emit SCTRL        4
	#emit MOVE.pri
	#emit SCTRL        2
	#emit LOAD.pri     YSI_g_sCallData
	#emit RETN
	
	return 0;
}

#define @@%0\32; @@
#define _@%0\32; _@

stock F@(calltype = 1, master = -1, heapptr = 0)
{
	P:5("F@ called: %d, %d, %d", calltype, master, heapptr);
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
	#emit LCTRL        2
	#emit STOR.S.pri   heapptr
	#emit ZERO.S       8
	#emit RETN
	return 0;
}

stock L@(GLOBAL_TAG_TYPES:ret, GLOBAL_TAG_TYPES:...)
{
	P:5("L@ called: %d", ret);
	// Return possibly multiple values remotely.
	setproperty(8, YSI_g_sPropReturn, ret);
	for (new i = 1, j = numargs(); i != j; ++i)
	{
		P:7("L@: loop %d = %d", i, getarg(i));
		YSI_g_sPropVarArg[1] = '@' + i,
		setproperty(8, YSI_g_sPropVarArg, getarg(i));
	}
	return 1;
}

stock T@(const string:ret[YSI_MAX_STRING], GLOBAL_TAG_TYPES:...)
{
	P:5("T@ called: %s", ret);
	// Return possibly multiple values remotely.
	setproperty(8, YSI_g_sPropEmpty, YSIM_STRING, ret);
	for (new i = 1, j = numargs(); i != j; ++i)
	{
		P:7("T@: loop %d = %d", i, getarg(i));
		YSI_g_sPropVarArg[1] = '@' + i,
		setproperty(8, YSI_g_sPropVarArg, getarg(i));
	}
	return 1;
}

// Used by y_master and y_remote.  Re-evaluate after rewrites.
native U@(id=0, const name[]="", value=cellmin, const string[]="") = setproperty;
native V@(GLOBAL_TAG_TYPES:id=0, const name[]="", value=cellmin, string[]="") = getproperty;

// Define this command with basically every strong tag in existence to avoid
// tag mismatch warnings with remote functions with strong tag parameters.
native W@(const function[], const format[], GLOBAL_TAG_TYPES:...) = CallRemoteFunction;
native O@(const function[], time, repeat, const format[] = "", GLOBAL_TAG_TYPES:...) = SetTimerEx;

stock S@(GLOBAL_TAG_TYPES:v = -1)
{
	P:4("S@ called");
	return
		getproperty(8, "", YSIM_STRING, Q@),
		strunpack(Q@, Q@),
		setproperty(8, YSIM_CALLER, v);
}

stock X@(GLOBAL_TAG_TYPES:n)
{
	// THIS MUST REMAIN FOREVER!  Detected by fixes.inc.
	P:4("X@ called: %i", n);
	setproperty(8, YSIM_RETURN, n);
}

stock E@()
{
	P:4("E@ called");
	// Already returns the previous value.
	return setproperty(8, YSIM_CALLER, Master_ID());
}

stock Z@(GLOBAL_TAG_TYPES:v = -1)
{
	P:4("Z@ called");
	return
		setproperty(8, YSIM_CALLER, v),
		getproperty(8, YSIM_RETURN);
}

stock R@(const buffer[])
{
	// To remove on completion of y_remote upgrade.
	P:4("R@ called: \"%s\"", buffer);
	return setproperty(8, "", YSIM_STRING, buffer);
}

stock H@(GLOBAL_TAG_TYPES:...)
{
	// Just a dead-end for spare parameters.
	return 0;
}

#define _UNUSED(%0) H@(_:_H@0:_H@1:%0)
#define _H@0:_H@1:%0&%1) _H@0:_H@1:%0%1)
#define _H@1:%0[%9]%1) _H@1:%0%1)

// Correctly stringise "On" callbacks without ALS interferring.
#define B@:#On%0) "On"#%0)

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

