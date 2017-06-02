/**--------------------------------------------------------------------------**\
					===============================
					 y_va2 - Enhanced vararg code!
					===============================
Description:
	This library provides a new macro - the triple underscore (___) which fully
	passes all of a function's parameters on to another function.
	
	This is a replacement for all other solutions like y_va.
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
	
	The Original Code is the YSI vararg include.
	
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
	1.0
Changelog:
	01/06/17:
		First version.
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
Callbacks:
	-
Definitions:
	-
Enums:
	-
Macros:
	___ - Passes all variable arguments to another function.
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
\**--------------------------------------------------------------------------**/

#if !defined MAX_NESTED_PASSTHROUGHS
	#define MAX_NESTED_PASSTHROUGHS (4) // Should be MORE than enough!
#endif

enum E_VARARG_PASSTHROUGH
{
	E_VARARG_PASSTHROUGH_OTYPE, // 0 = -O0, 1 = -O1.
	E_VARARG_PASSTHROUGH_STACK,
	E_VARARG_PASSTHROUGH_ASM[AsmContext]
}

static stock
	YSI_g_sPassthroughs[MAX_NESTED_PASSTHROUGHS][E_VARARG_PASSTHROUGH],
	YSI_g_sPassthroughNestings = 0,
	YSI_g_sStaticParameters;

static stock YVA2_DoPush(const staticParameters, const skippedParameters, const pushRequirements)
{
	// Used in reality, but copied to statics first.
	#pragma unused staticParameters, skippedParameters, pushRequirements
	static
		sFramePointer,
		sParameterCount,
		sReturnAddress,
		sSkippedParameters,
		sPushRequirements;
	// Although "staticParameters" is "const", we actually rewrite the value at
	// the call site when the mode starts.  By default it is ALWAYS 0, because
	// we have no way to determine the true value at compile time.  We must
	// read it from the number of parameters given to the target function.
	// "pushRequirements" is not currently used.  It will be the number of bytes
	// that each nested function will need to add to the stack for parameter
	// count references.
	// 
	// During the execution of this function, we have to actually modify our own
	// stack to make room UNDER it for all the parameters being pushed.  Then
	// when this function is returned from, the bottom of the stack already has
	// all the parameters on it.  Normally, because this function call is a
	// parameter to another function, its return value will also be pushed to
	// the stack, but we NOP that out at initialisation time.
	// 
	// Or entry to this function, the stack looks like:
	// 
	//   20 - pushRequirements.
	//   16 - skippedParameters.
	//   12 - staticParameters.
	//   08 - Parameter count in bytes (8).
	//   04 - Return address.
	//   00 - Previous frame.
	//   
	// This means there is 24 bytes of information we need to move to globals,
	// since we are about to totally destroy our own stack.
	#emit POP.pri
	#emit STOR.pri             sFramePointer
	#emit SCTRL                5 // Go back to the previous frame.
	#emit POP.pri
	#emit STOR.pri             sReturnAddress
	#emit POP.pri              // Don't care about parameter count (don't save).
	#emit POP.pri
	#emit STOR.pri             YSI_g_sStaticParameters // (Adjusted).
	#emit POP.pri
	#emit STOR.pri             sSkippedParameters
	#emit POP.pri
	#emit STOR.pri             sPushRequirements
	// The stack is now back to where it was before this function was called.
	// We must copy parameters from the previous stack to the current stack.
	// The frame is also the same, so technically now everything is in the same
	// stack.
	#emit LOAD.S.pri           8 // Parameter count.
	#emit STOR.pri             sParameterCount
	// There are two methods for this - increase the stack and 'memcpy' in, or
	// loop over all the parameters and re-push them.  I suspect the memcpy
	// version MAY be faster, but there is some trickyness with the stack to
	// call a function while inserting in to the stack.  The best non-JIT method
	// would be `MOVS`, but that requires more run-time code modification, which
	// we can't do (I don't think, never ACTUALLY tried...).
	YSI_g_sStaticParameters = sParameterCount - sSkippedParameters + YSI_g_sStaticParameters;
	sSkippedParameters = sFramePointer + 12 + sSkippedParameters;
	sFramePointer = sFramePointer + 12 + sParameterCount;
	// For now, just loop through them - I can improve the code later.
	for ( ; ; )
	{
		sFramePointer -= 4;
		if (sFramePointer == sSkippedParameters)
		{
			break;
		}
		{}
		#emit LREF.pri sFramePointer
		#emit PUSH.pri
	}
	// We need to tell the real call how many parameters are being pushed, via
	// the hidden 'numargs' parameter.  The first obvious solution would be
	// code rewriting to change the 'PUSH.C', but that doesn't work with JIT or
	// recursion.  The next obvious solution is a global with 'PUSH', but that
	// again doesn't work with recursion and is tricky with nested calls.  The
	// only other solution is to create a local variable and use that.  This
	// means pushing extra data and shifting and modifying code to remove the
	// extra data from the stack after the 'PUSH.S' and 'CALL'.  This is by far
	// the trickiest method, but also the most robust.
	// 
	// Nested calls are still a problem - the outer call must allocate all the
	// stack data for all of the parameter counts at once so that they have a
	// constant offset from the current frame pointer.  This is TODO:  I want it
	// working for just one outer call first before I start complicating it.
	// This also means that the first version will use a global variable and
	// ignore recursion and code shifting.
	// 
	// Return from this function.  We are already in the parent frame and have
	// no parameters on the stack, so function postamble is not required.
	#emit LOAD.pri             sReturnAddress
	#emit SCTRL                6
}

// Enable `&YVA2_DummyPush` WITHOUT matching it within the scanner itself.
#define CALL@YVA2_DummyPush YVA2_DummyPush(-1, -1, -1, -1, -1, -1, -1)
stock YVA2_DummyPush(const staticParameters = 0, const skippedParameters = 0, const pushRequirements = 4, const dummy0 = 0, const dummy1 = 0, const dummy2 = 0, const dummy3 = 0)
{
	#pragma unused dummy0, dummy1, dummy2, dummy3
	// This function serves four purposes:
	//   
	//   1) It is the function called if `___` is used incorrectly, so the code
	//       will give an error instead of just crashing.
	//   
	//   2) It uses more code space to call than `YVA2_DoPush` does, so adds
	//       extra space we can inject code in to.
	//   
	//   3) It protects `YVA2_DoPush` from being directly called by users.
	//   
	//   4) It ensures that `YVA2_DoPush` is included in the binary only when
	//       this function is called.  This doesn't save LOADS of space, since
	//       we always have all the matcher functions - but if they are
	//       including this library they probably want to use this library!
	//   
	if (FALSE)
	{
		YVA2_DoPush(staticParameters, skippedParameters, pushRequirements);
	}
	P:W("Bare `___` usage found - make sure it is a function parameter.");
	return 0;
}

static stock YVA2_FoundCall(m[CodeScanner])
{
	if (YSI_g_sPassthroughNestings)
	{
		new
			pos = YSI_g_sPassthroughNestings - 1;
		if (CodeScanGetMatchStack(m) < YSI_g_sPassthroughs[pos][E_VARARG_PASSTHROUGH_STACK])
		{
			new
				isSysreq = CodeScanGetMatchLength(m) == 24;
			printf("found %s", (isSysreq) ? ("sysreq") : ("call"));
			// We found the end of the call.
			printf("Found the end at: %x", CodeScanGetMatchAddress(m));
			--YSI_g_sPassthroughNestings;
			return 0;
		}
	}
	return -1;
}

static stock YVA2_FoundPush(m[CodeScanner])
{
	if (YSI_g_sPassthroughNestings >= MAX_NESTED_PASSTHROUGHS)
	{
		P:F("`___` nested too deeply - increase `MAX_NESTED_PASSTHROUGHS`.");
		return;
	}
	// Do something with the found address (of the START of the match), and the
	// stack size (of the END of the match) - different for reasons...
	printf("found push: %d %d %x", CodeScanGetMatchLength(m), CodeScanGetMatchStack(m), CodeScanGetMatchAddress(m));
	switch (CodeScanGetMatchLength(m))
	{
	case 72:
	{
		// -O0
		// Get rid of `STOR.I` and `PUSH.pri`.  Leave all the heap modification
		// code, since the cleanup will rely on it still existing.
		YSI_g_sPassthroughs[YSI_g_sPassthroughNestings][E_VARARG_PASSTHROUGH_OTYPE] = 0;
	}
	case 64:
	{
		// -O1
		// Get rid of `STOR.I` and `PUSH.alt`.  Leave all the heap modification
		// code, since the cleanup will rely on it still existing.  In the
		// future, this will give us two cells to play with for our own stack
		// cleanup code.
		YSI_g_sPassthroughs[YSI_g_sPassthroughNestings][E_VARARG_PASSTHROUGH_OTYPE] = 1;
	}
	}
	// Can't do this in one line sadly, this gives an error:
	//   
	//   	CodeScanGetMatchAsm(m, YSI_g_sPassthroughs[YSI_g_sPassthroughNestings][E_VARARG_PASSTHROUGH_ASM]);
	//   
	// I think it should work, but it doesn't.
	new
		asm[AsmContext];
	CodeScanGetMatchAsm(m, asm);
	YSI_g_sPassthroughs[YSI_g_sPassthroughNestings][E_VARARG_PASSTHROUGH_ASM] = asm;
	YSI_g_sPassthroughs[YSI_g_sPassthroughNestings][E_VARARG_PASSTHROUGH_STACK] = CodeScanGetMatchStack(m);
	++YSI_g_sPassthroughNestings;
}

// Add a scanner to find the `___` function call.

// Add a scanner to find the next point at which the stack is smaller than it
// was when `___` was called.  We have to be careful here as there may have been
// another `___` call in the interim, which would have been fully resolved
// first.  As in:
// 
//   Func1(Func2(___), ___);
// 
// `Func1`'s `___` will be first in the code, but before finding the call to
// `Func1` itself, we would see the inner `___` AND the inner function call.

hook OnScriptInit()
{
	new
		scanner[CodeScanner],
		csmO0[CodeScanMatcher],
		csmO1[CodeScanMatcher],
		csm2[CodeScanMatcher],
		csm3[CodeScanMatcher];
	CodeScanInit(scanner);
	/*
		// O0:
		const.pri 4
		push.pri
		zero.pri
		push.pri
		zero.pri
		push.pri
		push.c c
		call YVA2_DoPush
		heap 4
		stor.i
		move.pri
		push.pri
	*/
	CodeScanMatcherInit(csmO0, &YVA2_FoundPush);
	CodeScanMatcherPattern(csmO0,
		OP(PUSH_PRI)
		OP(ZERO_PRI)
		OP(PUSH_PRI)
		OP(ZERO_PRI)
		OP(PUSH_PRI)
		OP(ZERO_PRI)
		OP(PUSH_PRI)
		OP(ZERO_PRI)
		OP(CONST_PRI,  4)
		OP(PUSH_PRI)
		OP(ZERO_PRI)
		OP(PUSH_PRI)
		OP(ZERO_PRI)
		OP(PUSH_PRI)
		OP(PUSH_C,     28)
		OP(CALL,       &YVA2_DummyPush)
		OP(HEAP,       4)
		OP(STOR_I)
		OP(MOVE_PRI)
		OP(PUSH_PRI)
	);
	CodeScanAddMatcher(scanner, csmO0);
	/*
		// O1:
		push.c 4
		push.c 0
		push.c 0
		push.c c
		call YVA2_DoPush
		heap 4
		stor.i
		push.alt
	*/
	CodeScanMatcherInit(csmO1, &YVA2_FoundPush);
	CodeScanMatcherPattern(csmO1,
		OP(PUSH_C,     0)
		OP(PUSH_C,     0)
		OP(PUSH_C,     0)
		OP(PUSH_C,     0)
		OP(PUSH_C,     4)
		OP(PUSH_C,     0)
		OP(PUSH_C,     0)
		OP(PUSH_C,     28)
		OP(CALL,       &YVA2_DummyPush)
		OP(HEAP,       4)
		OP(STOR_I)
		OP(PUSH_ALT)
	);
	CodeScanAddMatcher(scanner, csmO1);
	// Match ANY function calls anywhere.  Will even match calls to `___`, but
	// we can ignore them (and many others).  I need some way to determine that
	// "amx_assembly" is up-to-date with the very latest "codescan" changes to
	// add scanner ignoring.
	/*
		push.c ???
		call   ???
		stack  ???
	*/
	CodeScanMatcherInit(csm2, &YVA2_FoundCall);
	CodeScanMatcherPattern(csm2,
		OP(PUSH_C,     ???)
		OP(CALL,       ???)
	);
	CodeScanAddMatcher(scanner, csm2);
	/*
		push.c   ???
		sysreq.c ???
		stack    ???
	*/
	CodeScanMatcherInit(csm3, &YVA2_FoundCall);
	CodeScanMatcherPattern(csm3,
		OP(PUSH_C,     ???)
		OP(SYSREQ_C,   ???)
		OP(STACK,      ???)
	);
	CodeScanAddMatcher(scanner, csm3);
	// Replace calls with the correct parameter counts etc.
	CodeScanRun(scanner);
}























































