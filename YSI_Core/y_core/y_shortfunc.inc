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
 *  <symbol name="R@">Renaming of <symbolref name="__CallLocalFunction" /> for size reasons.</symbol>
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
	YSI_g_sPropVarArg[3] = YSIM_VARARG,
	YSI_g_sCallData = 0;

static stock const
	YSI_g_sPropCaller[] = YSIM_CALLER,
	YSI_g_sPropReturn[] = YSIM_RETURN,
	YSI_g_sPropEmpty[] = "",
	YSI_g_sYSIM_STRING = YSIM_STRING,
	YSI_g_sYSI_MAX_STRING = YSI_MAX_STRING;

// CallRemoteFunction wrapper that handles references and string returns.
stock K@(const function[], const fmat[], GLOBAL_TAG_TYPES:...)
{
	P:5("K@ called: %s, %s", function, fmat);

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
		static i = 0, j = 0, ch = 0;
		for (i = j = 0; (ch = fmat[i]); ++i) if (ch == 'd')
		{
			YSI_g_sPropVarArg[1] = '@' + ++j;
			P:7("K@: Write back: %d %d %d %s %d", i, j, ch, YSI_g_sPropVarArg, getproperty(8, YSI_g_sPropVarArg));
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
		static i = 0, j = 0, ch = 0;
		for (i = j = 0; (ch = fmat[i]); ++i) if (ch == 'd')
		{
			YSI_g_sPropVarArg[1] = '@' + ++j;
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

stock X@(GLOBAL_TAG_TYPES:n)
{
	// THIS MUST REMAIN FOREVER!  Detected by fixes.inc.
	P:4("X@ called: %i", n);
	setproperty(8, YSI_g_sPropReturn, n);
}

stock H@(GLOBAL_TAG_TYPES:...)
{
	// Just a dead-end for spare parameters.
	return 0;
}

#define _UNUSED(%0) H@(_:_H@0:_H@1:%0)
#define _H@0:_H@1:%0&%1) _H@0:_H@1:%0%1)
#define _H@1:%0[%9]%1) _H@1:%0%1)
#define OnChaosTimer(%0,%1) YSI_JOIN(,r%0_On,r%0Timer)(%1)

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

#if !defined FIXES_PAWNDOC
	// The fixes.inc pawndoc cleverness is not already defined, we don't need to
	// modify it here.  We have to use `#endinput` to avoid the comments
	// appearing in the output anyway.
	#endinput
#endif

/**
	This variable only exists to re-show other variables.  It end a tiny comment
	in the output XML started by fixes.inc with the immediately preceeding
	(which should be called <c>ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZY</c>) so that we
	can document several seemingly "internal" variables that are actually for
	end-user use (<c>_0</c> - <c>_9</c>).  We then re-start the block comment to
	have it ended again later by the original fixes.inc end variable
	(<c>_zzzzzzzzzzzzzzzzzzzzzzzzzzzzzy</c>).  This only works because the
	fixes.inc function of the same name as this variable is in a different
	scope, and so fixes.inc also needed to use a different name for its hiding
	variable since all its variables are in the same scope.

	-->
*/

static stock ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ;

/**
	The first parameter in a <emph>y_functional</emph> lambda function.  This is
	implicitly declared.

	<!--

	Hide future declarations with <c>_0</c> prefix.
*/

static stock _0;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_0</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _0zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The second parameter in a <emph>y_functional</emph> lambda function.  This
	is implicitly declared.

	<!--

	Hide future declarations with <c>_1</c> prefix.
*/

static stock _1;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_1</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _1zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The third parameter in a <emph>y_functional</emph> lambda function.  This is
	implicitly declared.

	<!--

	Hide future declarations with <c>_2</c> prefix.
*/

static stock _2;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_2</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _2zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The fourth parameter in a <emph>y_functional</emph> lambda function.  This
	is implicitly declared.

	<!--

	Hide future declarations with <c>_3</c> prefix.
*/

static stock _3;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_3</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _3zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The fifth parameter in a <emph>y_functional</emph> lambda function.  This is
	implicitly declared.

	<!--

	Hide future declarations with <c>_4</c> prefix.
*/

static stock _4;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_4</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _4zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The sixth parameter in a <emph>y_functional</emph> lambda function.  This is
	implicitly declared.

	<!--

	Hide future declarations with <c>_5</c> prefix.
*/

static stock _5;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_5</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _5zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The seventh parameter in a <emph>y_functional</emph> lambda function.  This
	is implicitly declared.

	<!--

	Hide future declarations with <c>_6</c> prefix.
*/

static stock _6;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_6</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _6zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The eighth parameter in a <emph>y_functional</emph> lambda function.  This
	is implicitly declared.

	<!--

	Hide future declarations with <c>_7</c> prefix.
*/

static stock _7;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_7</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _7zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The ninth parameter in a <emph>y_functional</emph> lambda function.  This is
	implicitly declared.

	<!--

	Hide future declarations with <c>_8</c> prefix.
*/

static stock _8;

/**
	This variable only exists to hide other variables.  It end a massive comment
	block in the pawndoc XML output that hides all internal variables - that is,
	those that start with <c>_</c>.  This is a very common pattern used
	throughout YSI (and most of programming).  Unfortunately these weirdly named
	internal variables appear in the generated documentation always.  This is
	the best way to hide them.  You still see one variable (<c>_8</c>), but that
	one has a legitimate use that can be documented and is fine to be seen.

	-->
*/

static stock _8zzzzzzzzzzzzzzzzzzzzzzzzzzzzz;

/**
	The tenth parameter in a <emph>y_functional</emph> lambda function.  This is
	implicitly declared.

	<!--

	Hide future declarations with <c>_9</c> prefix.
*/

static stock _9;

