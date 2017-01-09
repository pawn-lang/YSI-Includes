/**--------------------------------------------------------------------------**\
                              ====================
                               YSI - Master Funcs
                              ====================
Description:
	Defines new names for native functions.
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
	
	The Original Code is the YSI master include.
	
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
	21/10/10:
		Split in to y_shortfunc.
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
	-
Tags:
	-
Variables:
	Global:
		-
	Static:
		-
Commands:
	-
Compile options:
	-
Operators:
	-
Natives:
	-
\**--------------------------------------------------------------------------**/

#if defined _INC_y_shortfunc
	#endinput
#endif
#define _INC_y_shortfunc

// Used to get rid of the "string:" tag once it has been used.
#if !defined string
	#define string:
#endif

#if !defined void
	#define void:
#endif

#include "..\YSI_Core\y_utils"
#include "..\YSI_Coding\y_va"
#include "y_globaltags"
#include "y_funcinc"
#include "y_renative"
#include "y_shortvar"
#include "..\YSI_Core\y_debug"

// Y@ - Script ID
// N@ - y_uvar callback
// M@ - y_svar callback
// Q@ - Temp string
// I@ - Temp var
// J@ - Temp var
// F@ - Also get string return without caller
// W@ - CallRemoteFunction
// V@ - getproperty
// S@ - Get string return
// Z@ - Detect string
// X@ - Set return
// R@ - Set string return
// U@ - setproperty
// E@ - Set caller
// O@ - SetTimerEx
// H@ - Ignore parameters
// B@ - Fix "On"
// 
// G@ - Ignore parameters with string return
// K@ - SetTimer
// P@ - CallLocalFunction
// 
// A@
// C@ - CallRemoteFunction string return wrapper
// D@ - CallRemoteFunction wrapper
// L@ - Return storage
// T@ - String return storage

new
	Q@[YSI_MAX_STRING];

static stock
	YSI_g_sPropVarArg[3] = YSIM_VARARG;

static stock const
	YSI_g_sPropCaller[] = YSIM_CALLER,
	YSI_g_sPropReturn[] = YSIM_RETURN,
	YSI_g_sPropEmpty[] = "",
	YSI_g_sYSIM_STRING = YSIM_STRING,
	YSI_g_sYSI_MAX_STRING = YSI_MAX_STRING;

stock C@(const function[], const fmat[], GLOBAL_TAG_TYPES:...)
{
	static lRet;
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
	#emit PUSH.C       Q@
	#emit PUSH         Y@
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
	#emit STACK        28
	#emit SYSREQ.C     CallRemoteFunction
	#emit STOR.pri     lRet
	
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
	if (lRet)
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
	#emit SCTRL        4
	#emit HEAP         0xFFFFFDF8 // -520
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

stock D@(const function[], const fmat[], GLOBAL_TAG_TYPES:...)
{
	static lRet;
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
	#emit PUSH         Y@
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
	#emit STACK        28
	#emit SYSREQ.C     CallRemoteFunction
	#emit STOR.pri     lRet
	
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
	
	if (lRet)
	{
		// Get the return value.  Already have most of the parameters pushed,
		// just modify one of them (the name).
		#emit CONST.pri    YSI_g_sPropReturn
		#emit STOR.S.pri   0xFFFFFFF4 // -12
		#emit SYSREQ.C     getproperty
		#emit STOR.pri     lRet
		
		// Get all the varargs (without using our corrupted stack).
		static i, j, ch;
		for (i = j = 0; (ch = fmat[i]); ++i) if (ch == 'd')
		{
			YSI_g_sPropVarArg[1] = '@' + ++j,
			setarg(i + 2, 0, getproperty(8, YSI_g_sPropVarArg));
		}
	}
	{}
	
	// Return from two functions at once, while unpopping all our data.
	#emit LOAD.S.pri   0
	#emit SCTRL        5
	#emit SCTRL        4
	#emit LOAD.pri     lRet
	#emit RETN
	
	return 0;
}

#define C@(%9:%0);%1; C@(%0); // Get word.
#define D@(%9:%0);%1; D@(%0); // Get string.

#define @_%0\32; @_
#define _@%0\32; _@

//stock T@(const function[], const fmat[], GLOBAL_TAG_TYPES:...)
//{
//	static lRet;
//	#pragma unused function, fmat
//	// New implementation of "CallLocalFunction".  Wraps the old function
//	// efficiently (using assembly stack manipulation tricks, better even than
//	// the ones in "y_va" since we have more control over exactly how this is
//	// called and what other locals there are).  Also pushes and pops the
//	// current master, and uses properties for return values instead of normal
//	// ones which don't work well for "CallLocalFunction" (they depend on script
//	// call order).
//	
//	// Push the current master ID on to the master stack.  Returns the old
//	// master ID stored in the property, which we can shove on to the heap to
//	// restore later.
//	#emit PUSH.C       Q@
//	#emit PUSH         Y@
//	#emit PUSH.C       YSI_g_sPropCaller
//	#emit PUSH.C       8
//	#emit PUSH.C       16
//	#emit SYSREQ.C     setproperty
//	
//	// Back up the frame header information and the return value.  "MOVS" copies
//	// from "pri" to "alt".
//	#emit STOR.S.pri   0xFFFFFFF8 // -8
//	#emit HEAP         28
//	#emit LCTRL        4
//	#emit MOVS         28
//	
//	// Call "CallLocalFunction".
//	#emit STACK        28
//	#emit SYSREQ.C     CallLocalFunction
//	#emit STOR.pri     lRet
//	
//	// Restore the stack.
//	#emit STACK        0xFFFFFFE4 // -28
//	#emit STACK        0          // Load new stack pointer in to "alt".
//	#emit LCTRL        2
//	#emit ADD.C        0xFFFFFFE4
//	#emit MOVS         28
//	#emit HEAP         0xFFFFFFE4
//	
//	// Restore the master caller.  Already pushed the parameters earlier, before
//	// backing them up on the heap (saved extra work now sorting out which saved
//	// parameter went where).
//	#emit SYSREQ.C     setproperty
//	if (lRet)
//	{
//		// Get the return value.  Already have most of the parameters pushed,
//		// just modify one of them (the name).
//		#emit CONST.pri    YSI_g_sPropEmpty
//		#emit STOR.S.pri   0xFFFFFFF4 // -12
//		#emit LOAD.pri     YSI_g_sYSIM_STRING
//		#emit STOR.S.pri   0xFFFFFFF8 // -8
//		#emit SYSREQ.C     getproperty
//		
//		// Unpack the return to the previous function's return string.
//		#emit PUSH         YSI_g_sYSI_MAX_STRING
//		#emit PUSH.C       Q@
//		#emit LOAD.S.pri   0
//		#emit MOVE.alt
//		#emit ADD.C        8
//		#emit LOAD.I
//		#emit ADD.C        12
//		#emit ADD
//		#emit LOAD.I
//		#emit PUSH.pri
//		#emit PUSH.C       12
//		#emit SYSREQ.C     strunpack
//		
//		// Get all the varargs (without using our corrupted stack).
//		static i, j, ch;
//		for (i = j = 0; (ch = fmat[i]); ++i) if (ch == 'd')
//		{
//			YSI_g_sPropVarArg[1] = '@' + ++j,
//			setarg(i + 2, 0, getproperty(8, YSI_g_sPropVarArg));
//		}
//	}
//	else
//	{
//		// NULL the return.
//		#emit LOAD.S.pri   0
//		#emit MOVE.alt
//		#emit ADD.C        8
//		#emit LOAD.I
//		#emit ADD.C        12
//		#emit ADD
//		#emit LOAD.I
//		#emit MOVE.alt
//		#emit ZERO.pri
//		#emit STOR.I
//	}
//	{}
//	
//	// Return from two functions at once, while unpopping all our data.  By
//	// doing this we know out string return fix/optimisation will apply.
//	#emit LOAD.S.pri   0
//	#emit SCTRL        5
//	#emit SCTRL        4
//	#emit HEAP         0xFFFFFDF8 // -520
//	#emit RETN
//	
//	// Let the compiler do size checks.  There is a bug in the old compiler
//	// where returning a string from a varargs function won't work, we work
//	// around that bug by using raw assembly.  We also make the return more
//	// efficient by unpacking straight in to the destination, instead of
//	// unpacking to a local array then copying that to the return, as even the
//	// new compiler would do with separate statements.  Fortunately, the old
//	// compiler at least gets the size checks right, we so have that going for
//	// us - meaning that we know that code that compiles will return correctly.
//	return Q@;
//}
//
//stock U@(const function[], const fmat[], GLOBAL_TAG_TYPES:...)
//{
//	static lRet;
//	#pragma unused function, fmat
//	// New implementation of "CallLocalFunction".  Wraps the old function
//	// efficiently (using assembly stack manipulation tricks, better even than
//	// the ones in "y_va" since we have more control over exactly how this is
//	// called and what other locals there are).  Also pushes and pops the
//	// current master, and uses properties for return values instead of normal
//	// ones which don't work well for "CallLocalFunction" (they depend on script
//	// call order).
//	
//	// Push the current master ID on to the master stack.  Returns the old
//	// master ID stored in the property, which we can shove on to the heap to
//	// restore later.
//	#emit PUSH.C       YSI_g_sPropEmpty
//	#emit PUSH         Y@
//	#emit PUSH.C       YSI_g_sPropCaller
//	#emit PUSH.C       8
//	#emit PUSH.C       16
//	#emit SYSREQ.C     setproperty
//	
//	// Back up the frame header information and the return value.  "MOVS" copies
//	// from "pri" to "alt".
//	#emit STOR.S.pri   0xFFFFFFF8 // -8
//	#emit HEAP         28
//	#emit LCTRL        4
//	#emit MOVS         28
//	
//	// Call "CallLocalFunction".
//	#emit STACK        28
//	#emit SYSREQ.C     CallLocalFunction
//	#emit STOR.pri     lRet
//	
//	// Restore the stack.
//	#emit STACK        0xFFFFFFE4 // -28
//	#emit STACK        0          // Load new stack pointer in to "alt".
//	#emit LCTRL        2
//	#emit ADD.C        0xFFFFFFE4
//	#emit MOVS         28
//	#emit HEAP         0xFFFFFFE4
//	
//	// Restore the master caller.  Already pushed the parameters earlier, before
//	// backing them up on the heap (saved extra work now sorting out which saved
//	// parameter went where).
//	#emit SYSREQ.C     setproperty
//	
//	if (lRet)
//	{
//		// Get the return value.  Already have most of the parameters pushed,
//		// just modify one of them (the name).
//		#emit CONST.pri    YSI_g_sPropReturn
//		#emit STOR.S.pri   0xFFFFFFF4 // -12
//		#emit SYSREQ.C     getproperty
//		#emit STOR.pri     lRet
//		
//		// Get all the varargs (without using our corrupted stack).
//		static i, j, ch;
//		for (i = j = 0; (ch = fmat[i]); ++i) if (ch == 'd')
//		{
//			YSI_g_sPropVarArg[1] = '@' + ++j,
//			setarg(i + 2, 0, getproperty(8, YSI_g_sPropVarArg));
//		}
//	}
//	{}
//	
//	// Return from two functions at once, while unpopping all our data.
//	#emit LOAD.S.pri   0
//	#emit SCTRL        5
//	#emit SCTRL        4
//	#emit LOAD.pri     lRet
//	#emit RETN
//	
//	return 0;
//}

stock L@(GLOBAL_TAG_TYPES:...)
{
	// Return possibly multiple values remotely.
	setproperty(8, YSI_g_sPropReturn, getarg(0));
	for (new i = 1, j = numargs(); i != j; ++i)
	{
		YSI_g_sPropVarArg[1] = '@' + i,
		setproperty(8, YSI_g_sPropVarArg, getarg(i));
	}
	return 1;
}

stock T@(string:ret[YSI_MAX_STRING], GLOBAL_TAG_TYPES:...)
{
	// Return possibly multiple values remotely.
	setproperty(8, YSI_g_sPropEmpty, YSIM_STRING, ret);
	for (new i = 1, j = numargs(); i != j; ++i)
	{
		YSI_g_sPropVarArg[1] = '@' + i,
		setproperty(8, YSI_g_sPropVarArg, getarg(i));
	}
	return 1;
}

native _YSI_RE_NATIVE<U@|||id=0, const name[]="", value=cellmin, const string[]=""|||setproperty>

native _YSI_RE_NATIVE<V@|||GLOBAL_TAG_TYPES:id=0, const name[]="", value=cellmin, string[]=""|||getproperty>

#if defined _YSI_MINI_MODE
	#undef CallRemoteFunction
	#undef CallLocalFunction
#endif

#if defined _ALS_CallRemoteFunction
	#if defined BAD_CallRemoteFunction
		#undef CallRemoteFunction
	#else
		#error Unknown redefinition of CallRemoteFunction.
	#endif
#endif

// Define this command with basically every strong tag in existence to avoid
// tag mismatch warnings with remote functions with strong tag parameters.
native _YSI_RE_NATIVE<W@|||const function[], const format[], GLOBAL_TAG_TYPES:...|||CallRemoteFunction>

native _YSI_RE_NATIVE<P@|||const function[], const format[], GLOBAL_TAG_TYPES:...|||CallLocalFunction>

#if defined _ALS_CallRemoteFunction
	#if defined BAD_CallRemoteFunction
		#define CallRemoteFunction FIXES_CallRemoteFunction
	#endif
#endif

#if defined _YSI_MINI_MODE
	#if defined _ALS_CallRemoteFunction
		#undef CallRemoteFunction
	#else
		#define _ALS_CallRemoteFunction
	#endif
	
	#define CallRemoteFunction _MMD(CallRemoteFunction)
	
	#if defined _ALS_CallLocalFunction
		#undef CallLocalFunction
	#else
		#define _ALS_CallLocalFunction
	#endif
	
	#define CallLocalFunction  _MMD(CallLocalFunction)
#endif

native _YSI_RE_NATIVE<O@|||const function[], time, repeat, const format[], GLOBAL_TAG_TYPES:...|||SetTimerEx>

native _YSI_RE_NATIVE<K@|||const function[], time, repeat|||SetTimer>

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
	P:4("X@ called: %i", n);
	setproperty(8, YSIM_RETURN, n);
}

stock E@()
{
	P:4("E@ called");
	// Already returns the previous value.
	return setproperty(8, YSIM_CALLER, Y@);
}

stock Z@(GLOBAL_TAG_TYPES:v = -1)
{
	P:4("Z@ called");
	return
		setproperty(8, YSIM_CALLER, v),
		getproperty(8, YSIM_RETURN);
}

stock R@(buffer[])
{
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

stock F@()
{
	P:4("F@ called");
	return
		getproperty(8, "", YSIM_STRING, Q@),
		strunpack(Q@, Q@);
}

// Consume trailing spaces.  Despite being a common letter, this is unlkely to
// ever be matched due to the unusual series of operators after it.  If anyone
// else tries to define "x" however they may have a slight problem (they can't).
#define x:##),) #))
#define q:##),ALS_RS_none:) #))

// This is for getting excess parameters on non-strings.  Now safely recursive.
#define _:%0,) _:%0)

#if defined YSI_LOCK_MODE

	#include "..\YSI_Internal\y_unique"
	
	forward UNIQUE_FUNCTION<@yH_OnScriptInit@...>();
	
	public UNIQUE_FUNCTION<@yH_OnScriptInit@...>()
	{
		new
			find = strfind(YSI_gLockData[5], YSI_gLockData[1]) + 6;
		find = strfind(YSI_gLockData[5], YSI_gLockData[1], _, find - 5) + 6;
		new
			found = strfind(YSI_gLockData[5], YSI_gLockData[1], _, find - 5) + 6;
		if (strval(YSI_gLockData[found]) ^ UNIQUE_SYMBOL != _LOCK_IP_3 ^ UNIQUE_SYMBOL || strval(YSI_gLockData[find]) - _LOCK_IP_3 != _LOCK_IP_2 - _LOCK_IP_3)
		{
			y_lock 1;
		}
	}
#endif

