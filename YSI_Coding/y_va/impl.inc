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
	2.0
Changelog:
	02/05/11:
		First version.
	01/06/17:
		Second version.
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

static stock
	YSI_g_sLength[MAX_NESTED_PASSTHROUGHS], // false = O0, true = O1.
	YSI_g_sSkips[MAX_NESTED_PASSTHROUGHS],
	YSI_g_sStacks[MAX_NESTED_PASSTHROUGHS],
	YSI_g_sContexts[MAX_NESTED_PASSTHROUGHS][AsmContext],
	YSI_g_sMaxNesting = 0,
	YSI_g_sPassthroughNestings = 0;

#define CALL@YVA2_DoPush YVA2_DoPush(-1, -1, -1)
static stock YVA2_DoPush(const skippedBytes, const pushedBytes, const pushRequirements)
{
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
	// Used in reality, but copied to statics first.
	#pragma unused pushedBytes, skippedBytes, pushRequirements
	static
		sReturnAddress,
		sPushedParameters,
		sParametersBase,
		sTotalParameters;
	// Although "pushedBytes" is "const", we actually rewrite the value at
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
	//   16 - pushedBytes.
	//   12 - skippedBytes.
	//   08 - Parameter count in bytes (8).
	//   04 - Return address.
	//   00 - Previous frame.
	//   
	// This means there is 24 bytes of information we need to move to globals,
	// since we are about to totally destroy our own stack.
	#emit POP.pri
	#emit SCTRL        5 // Go back to the previous frame.
	// The frame is now the same.
	#emit POP.pri
	#emit STOR.pri     sReturnAddress
	#emit POP.pri        // Don't care about this parameter count (don't save).
	#emit POP.alt                        // skippedBytes
	#emit LCTRL        5                 // frame
	#emit ADD.C        12                // frame + 12
	#emit ADD                            // frame + 12 + skippedBytes
	#emit STOR.pri     sParametersBase
	#emit LOAD.S.pri   8                 // parameterCount
	#emit SUB                            // parameterCount - skippedBytes
	#emit STOR.pri     sPushedParameters
	#emit POP.alt                        // pushedBytes
	#emit ADD                            // parameterCount - skippedBytes + pushedBytes
	#emit STOR.pri     sTotalParameters  // (Adjusted).
	#emit POP.alt
	// The stack is now back to where it was before this function was called.
	// So is the frame, so technically now everything is in the same stack.
	// We must copy parameters from the previous stack to the current stack.
	// There are two methods for this - increase the stack and 'memcpy' in, or
	// loop over all the parameters and re-push them.
	// Already got the offset - use it.
	#emit LOAD.pri     sTotalParameters
	#emit STOR.I
	// Move the stack down enough for the new parameters.  `[stk]` is in `pri`.
	#emit LCTRL        4
	#emit LOAD.alt     sPushedParameters
	#emit SUB
	#emit SCTRL        4 // Move the stack down a load at once.
	// The stack pointer should be in `alt`.  This code is just:
	//   
	//	 memcpy(&stack, sParametersBase, 0, sPushedParameters, cellmax);
	//   
	// We know we MUST have enough space on the stack since we allocated it!
	#emit STACK        0
	#emit PUSH.C       0x10000000
	#emit PUSH         sPushedParameters
	#emit PUSH.C       0
	#emit PUSH         sParametersBase
	#emit PUSH.alt
	#emit PUSH.C       20
	#emit SYSREQ.C     memcpy
	#emit STACK        24
	// Return from this function.  We are already in the parent frame and have
	// no parameters on the stack, so function postamble is not required.
	#emit LOAD.pri     sReturnAddress
	#emit SCTRL        6
}

// Enable `&YVA2_DummyPush` WITHOUT matching it within the scanner itself.
#define CALL@YVA2_DummyPush YVA2_DummyPush(-1, -1, -1, -1, -1, -1, -1, -1, -1)
// IF YOU EVER CHANGE THE NUMBER OF DUMMY PARAMETERS, DON'T FORGET TO CHANGE THE
// PARAMETER BYTE COUNT IN THE SCANNER!  ONLY DONE IT EVERY TIME SO FAR...
stock YVA2_DummyPush(const skippedBytes = 0, const pushedBytes = 0, const pushRequirements = 4, const dummy0 = 0, const dummy1 = 0, const dummy2 = 0, const dummy3 = 0, const dummy4 = 0, const dummy5 = 0)
{
	#pragma unused dummy0, dummy1, dummy2, dummy3, dummy4, dummy5
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
		YVA2_DoPush(pushedBytes, skippedBytes, pushRequirements);
	}
	P:W("Bare `___` usage found - make sure it is a function parameter.");
	return 0;
}

static stock YVA2_CodeGenPushSite(ctx[AsmContext], const pushedBytes, const skippedBytes/*, const depth*/, const offset)
{
	// `pushedBytes` is the number of bytes originally pushed to the target
	// function (which includes four for the `___` return value).
	// Use `ctx` so we can use `@emit`.
	@emit ADDR.pri     offset                  // 8
	@emit PUSH.pri                             // 12
	@emit PUSH.C       pushedBytes - 4         // 28
	@emit PUSH.C       skippedBytes            // 20
	@emit PUSH.C       12                      // 36
	@emit CALL.abs     addressof (YVA2_DoPush) // 44
	// We keep the `HEAP` here since we know that the original code wants to
	// clean up an extra four bytes from the heap, so it still needs to exist.
	@emit HEAP         4                       // 52
}

static stock YVA2_CodeGenShiftCode(dest, src, end)
{
	// Shift some the code up.  We can't use `memcpy` as the destination most
	// probably overlaps the source.
	while (src != end)
	{
		#emit LREF.S.pri   src
		#emit SREF.S.pri   dest
		src += 4;
		dest += 4;
	}
	// NOP out the remaining code.
	src = _:RelocateOpcode(OP_NOP);
	while (dest != end)
	{
		#emit LOAD.S.pri   src
		#emit SREF.S.pri   dest
		dest += 4;
	}
}

static stock YVA2_CodeGenMainCleanup(ctx[AsmContext])
{
	static
		sTemp;
	// Get the number of pushed parameters.
	@emit POP.alt                 // 4
	// Save the return value.
	@emit STOR.pri     ref(sTemp) // 12
	// Load the stack pointer.
	@emit LCTRL        4          // 20
	// Remove the number of pushed parameters.
	@emit ADD                     // 24
	// Store the stack pointer.
	@emit SCTRL        4          // 32
	// Restore the return value.
	@emit LOAD.pri     ref(sTemp) // 40
}

static stock YVA2_CodeGenDeepCleanup(ctx[AsmContext], depth, returningString)
{
	if (returningString)
		@emit POP.pri
	// Remove all the temporary storage locations.
	@emit STACK        depth * cellbytes
}

static stock YVA2_CodeGenPushVariable(ctx[AsmContext], stack)
{
	// Remove a single temporary storage location.
	@emit PUSH.S       stack
}

static stock YVA2_FoundCall(m[CodeScanner])
{
	if (YSI_g_sPassthroughNestings)
	{
		new
			pos = YSI_g_sPassthroughNestings - 1;
		if ((CodeScanGetMatchStack(m) < YSI_g_sStacks[pos]) || (!pos && YSI_g_sSkips[0] & cellmin && CodeScanGetMatchStack(m) < YSI_g_sStacks[pos] + cellbytes))
		{
			new
				len = CodeScanGetMatchLength(m),
				end = CodeScanGetMatchAddressData(m) + len,
				hole = CodeScanGetMatchHole(m, 0),
				returningString = 0,
				codeLength = 52;
			YSI_g_sPassthroughNestings = pos;
			if (!pos && YSI_g_sSkips[0] & cellmin)
			{
				YSI_g_sSkips[0] &= cellmax;
				// Check if this function is returning a string.  It has an extra hidden
				// parameter that we need to account for and that is always pushed
				// before our various ones.  This is only a problem for an outer call
				// since our local parameter count variables will be pushed after that
				// return address and hide it.  Inner calls don't push their own locals
				// and so don't interrupt their own return values.
				new
					dctx[DisasmContext];
				CodeScanGetMatchDisasm(m, dctx, len);
				switch (DisasmNextInsn(dctx))
				{
					// Check the next instruction instead.
					case OP_HEAP:
						returningString = (DisasmNextInsn(dctx) == OP_POP_PRI) ? 3 * cellbytes : 0;
					case OP_POP_PRI:
						returningString = 1 * cellbytes;
					default:
						returningString = 0;
				}
				if (!returningString)
					P:F("Found string return preamble without postamble - Y_Less needs to fix this!");
			}
			if (returningString)
			{
				// Shift the three cells before this code down to make room for
				// the local storage stack adjustment code.
				YSI_g_sContexts[0][AsmContext_buffer] -= 3 * cellbytes,
				codeLength = ReadAmxMemory(YSI_g_sContexts[0][AsmContext_buffer] + cellbytes),
				AsmEmitStack(YSI_g_sContexts[0], (YSI_g_sMaxNesting + 1) * -cellbytes),
				AsmEmitHeap(YSI_g_sContexts[0], codeLength),
				AsmEmitPushAlt(YSI_g_sContexts[0]),
				codeLength = 52 + 5 * cellbytes;
			}
			else if (!pos)
			{
				AsmEmitStack(YSI_g_sContexts[0], (YSI_g_sMaxNesting + 1) * -cellbytes),
				codeLength += 2 * cellbytes;
			}
			new
				dest = YSI_g_sContexts[pos][AsmContext_buffer];
			// First, rewrite the `___` call-site to call `YVA2_DoPush` instead.
			YVA2_CodeGenPushSite(YSI_g_sContexts[pos], hole, YSI_g_sSkips[pos], -YSI_g_sStacks[0] - pos * cellbytes), // YSI_g_sStacks[0]!!!
			// Shift the code up.
			YVA2_CodeGenShiftCode(
				dest + YSI_g_sContexts[pos][AsmContext_buffer_offset],
				dest + YSI_g_sLength[pos] + (returningString ? 12 : 0),
				end + returningString),
			// Adjust the assembly context.  `codeLength` is the length of the
			// code from `YVA2_CodeGenPushSite`.
			YSI_g_sContexts[pos][AsmContext_buffer_offset] = (end - dest) - (YSI_g_sLength[pos] - codeLength + returningString) - 16;
			if (len == 24)
				YSI_g_sContexts[pos][AsmContext_buffer_offset] -= 8;
			YVA2_CodeGenPushVariable(YSI_g_sContexts[pos], -YSI_g_sStacks[0] - pos * cellbytes);
			YSI_g_sContexts[pos][AsmContext_buffer_offset] += 8;
			if (returningString == 12)
				YSI_g_sContexts[pos][AsmContext_buffer_offset] += 8;
			if (len == 24)
				YVA2_CodeGenMainCleanup(YSI_g_sContexts[pos]);
			if (YSI_g_sPassthroughNestings)
			{
				// Is a nesting.  Do nothing.
			}
			else //if (YSI_g_sMaxNesting)
			{
				// Was nested - needs multiple call's cleanups.
				YVA2_CodeGenDeepCleanup(YSI_g_sContexts[pos], (YSI_g_sMaxNesting + 1), returningString),
				YSI_g_sMaxNesting = 0;
			}
			// Just keep going - this code is designed to recurse (maybe...).
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
	YSI_g_sMaxNesting = max(YSI_g_sMaxNesting, YSI_g_sPassthroughNestings),
	// Do something with the found address (of the START of the match), and the
	// stack size (of the END of the match) - different for reasons...
	YSI_g_sLength[YSI_g_sPassthroughNestings] = CodeScanGetMatchLength(m),
	CodeScanGetMatchAsm(m, YSI_g_sContexts[YSI_g_sPassthroughNestings]),
	YSI_g_sStacks[YSI_g_sPassthroughNestings] = CodeScanGetMatchStack(m),
	// If the code is 96 bytes long, `ZERO_PRI` was used not a constant number.
	YSI_g_sSkips[YSI_g_sPassthroughNestings] = (YSI_g_sLength[YSI_g_sPassthroughNestings] == 120) ? 0 : CodeScanGetMatchHole(m, 0);
	if (!YSI_g_sPassthroughNestings)
	{
		// Check if this function is returning a string.  It has an extra hidden
		// parameter that we need to account for and that is always pushed
		// before our various ones.  This is only a problem for an outer call
		// since our local parameter count variables will be pushed after that
		// return address and hide it.  Inner calls don't push their own locals
		// and so don't interrupt their own return values.
		new
			dctx[DisasmContext];
		CodeScanGetMatchDisasm(m, dctx, -12);
		if (DisasmNextInsn(dctx) == OP_HEAP && DisasmNextInsn(dctx) == OP_PUSH_ALT)
		{
			// Correct preamble.  Mark this to check the postamble.
			YSI_g_sSkips[YSI_g_sPassthroughNestings] |= cellmin,
			YSI_g_sStacks[0] -= cellbytes;
		}
	}
	++YSI_g_sPassthroughNestings;
	P:3("YVA2_FoundPush: %d", CodeScanGetMatchStack(m));
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

public OnScriptInit()
{
	new
		scanner[CodeScanner],
		csmO0A[CodeScanMatcher],
		csmO0B[CodeScanMatcher],
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
	CodeScanMatcherInit(csmO0A, &YVA2_FoundPush);
	CodeScanMatcherPattern(csmO0A,
		OP(ZERO_PRI)                    // 12
		OP(PUSH_PRI)                    // 16
		OP(ZERO_PRI)                    // 20
		OP(PUSH_PRI)                    // 24
		OP(ZERO_PRI)                    // 4
		OP(PUSH_PRI)                    // 8
		OP(ZERO_PRI)                    // 12
		OP(PUSH_PRI)                    // 16
		OP(ZERO_PRI)                    // 20
		OP(PUSH_PRI)                    // 24
		OP(ZERO_PRI)                    // 28
		OP(PUSH_PRI)                    // 32
		OP(CONST_PRI,  4)               // 40
		OP(PUSH_PRI)                    // 44
		OP(ZERO_PRI)                    // 48
		OP(PUSH_PRI)                    // 52
		OP(ZERO_PRI)                    // 56
		OP(PUSH_PRI)                    // 60
		OP(PUSH_C,     36)              // 68
		OP(CALL,       &YVA2_DummyPush) // 76
		OP(HEAP,       4)               // 84
		OP(STOR_I)                      // 88
		OP(MOVE_PRI)                    // 92
		OP(PUSH_PRI)                    // 96
	);
	CodeScanAddMatcher(scanner, csmO0A);
	CodeScanMatcherInit(csmO0B, &YVA2_FoundPush);
	CodeScanMatcherPattern(csmO0B,
		OP(ZERO_PRI)                    // 12
		OP(PUSH_PRI)                    // 16
		OP(ZERO_PRI)                    // 20
		OP(PUSH_PRI)                    // 24
		OP(ZERO_PRI)                    // 4
		OP(PUSH_PRI)                    // 8
		OP(ZERO_PRI)                    // 12
		OP(PUSH_PRI)                    // 16
		OP(ZERO_PRI)                    // 20
		OP(PUSH_PRI)                    // 24
		OP(ZERO_PRI)                    // 28
		OP(PUSH_PRI)                    // 32
		OP(CONST_PRI,  4)               // 40
		OP(PUSH_PRI)                    // 44
		OP(ZERO_PRI)                    // 52
		OP(PUSH_PRI)                    // 56
		OP(CONST_PRI,  ???)             // 60
		OP(PUSH_PRI)                    // 64
		OP(PUSH_C,     36)              // 72
		OP(CALL,       &YVA2_DummyPush) // 80
		OP(HEAP,       4)               // 88
		OP(STOR_I)                      // 92
		OP(MOVE_PRI)                    // 96
		OP(PUSH_PRI)                    // 100
	);
	CodeScanAddMatcher(scanner, csmO0B);
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
		OP(PUSH_C,     0)               // 16
		OP(PUSH_C,     0)               // 24
		OP(PUSH_C,     0)               // 8
		OP(PUSH_C,     0)               // 16
		OP(PUSH_C,     0)               // 24
		OP(PUSH_C,     0)               // 32
		OP(PUSH_C,     4)               // 40
		OP(PUSH_C,     0)               // 48
		OP(PUSH_C,     ???)             // 56
		OP(PUSH_C,     36)              // 64
		OP(CALL,       &YVA2_DummyPush) // 72
		OP(HEAP,       4)               // 80
		OP(STOR_I)                      // 84
		OP(PUSH_ALT)                    // 88
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
	//DisasmDump("yva2.asm");
	#if defined _y_va_OnScriptInit
		_y_va_OnScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnScriptInit
	#undef OnScriptInit
#else
	#define _ALS_OnScriptInit
#endif
#define OnScriptInit _y_va_OnScriptInit

#if defined _y_va_OnScriptInit
	forward _y_va_OnScriptInit();
#endif

stock va_strlen(arg)
{
	// Get the length of the string at the given position on the previous
	// function's stack (convenience function).
	// Get the address of the previous function's stack.  First get the index of
	// the argument required.
	#emit LOAD.S.pri arg
	// Then convert that number to bytes from cells.
	#emit SMUL.C     4
	// Get the previous function's frame.  Stored in variable 0 (in the current
	// frame).  Parameters are FRM+n+12, locals are FRM-n, previous frame is
	// FRM+0, return address is FRM+4, parameter count is FRM+8.  We could add
	// checks that "arg * 4 < *(*(FRM + 0) + 8)", for the previous frame parameter
	// count (in C pointer speak).
	#emit LOAD.S.alt 0
	// Add the frame pointer to the argument offset in bytes.
	#emit ADD
	// Add 12 to skip over the function header.
	#emit ADD.C      12
	// Load the address stored in the specified address.
	#emit LOAD.I
	// Push the address we just determined was the source.
	#emit PUSH.pri
	// Push the number of parameters passed (in bytes) to the function.
	#emit PUSH.C     4
	// Call the function.
	#emit SYSREQ.C   strlen
	// Restore the stack to its level before we called this native.
	#emit STACK      8
	#emit RETN
	// Never called.
	return 0;
}

stock va_getstring(dest[], arg, len = sizeof (dest))
{
	// Get the address of the previous function's stack.  First get the index of
	// the argument required.
	#emit LOAD.S.pri arg
	// Then convert that number to bytes from cells.
	#emit SMUL.C     4
	// Get the previous function's frame.  Stored in variable 0 (in the current
	// frame).  Parameters are FRM+n+12, locals are FRM-n, previous frame is
	// FRM+0, return address is FRM+4, parameter count is FRM+8.  We could add
	// checks that "arg * 4 < *(*(FRM + 0) + 8)", for the previous frame parameter
	// count (in C pointer speak).
	#emit LOAD.S.alt 0
	// Add the frame pointer to the argument offset in bytes.
	#emit ADD
	// Add 12 to skip over the function header.
	#emit ADD.C      12
	// Load the address stored in the specified address.
	#emit LOAD.I
	// Push the length for "strcat".
	#emit PUSH.S     len
	// Push the address we just determined was the source.
	#emit PUSH.pri
	// Load the address of the destination.
	#emit LOAD.S.alt dest
	// Blank the first cell so "strcat" behaves like "strcpy".
	#emit ZERO.pri
	// Store the loaded number 0 to the loaded address.
	#emit STOR.I
	// Push the loaded address.
	#emit PUSH.alt
	// Push the number of parameters passed (in bytes) to the function.
	#emit PUSH.C     12
	// Call the function.
	#emit SYSREQ.C   strcat
	// Restore the stack to its level before we called this native.
	#emit STACK      16
}

stock PlayerText:va_CreatePlayerTextDraw(playerid, Float:x, Float:y, fmat[], va_args<>)
{
	return CreatePlayerTextDraw(playerid, x, y, va_return(fmat, va_start<4>));
}

stock Text:va_TextDrawCreate(Float:x, Float:y, fmat[], va_args<>)
{
	return TextDrawCreate(x, y, va_return(fmat, va_start<3>));
}

stock va_SendClientMessage(playerid, colour, const fmat[], va_args<>)
{
	return SendClientMessage(playerid, colour, va_return(fmat, va_start<3>));
}

stock va_SendClientMessageToAll(colour, const fmat[], va_args<>)
{
	return SendClientMessageToAll(colour, va_return(fmat, va_start<2>));
}

stock va_SendPlayerMessageToPlayer(playerid, senderid, const fmat[], va_args<>)
{
	return SendPlayerMessageToPlayer(playerid, senderid, va_return(fmat, va_start<3>));
}

stock va_SendPlayerMessageToAll(senderid, const fmat[], va_args<>)
{
	return SendPlayerMessageToAll(senderid, va_return(fmat, va_start<2>));
}

stock va_GameTextForPlayer(playerid, const fmat[], time, style, va_args<>)
{
	return GameTextForPlayer(playerid, va_return(fmat, va_start<4>), time, style);
}

stock va_GameTextForAll(const fmat[], time, style, va_args<>)
{
	return GameTextForAll(va_return(fmat, va_start<3>), time, style);
}

stock va_print(const fmat[], va_args<>)
{
	return print(va_return(fmat, va_start<1>));
}

stock va_fprintf(File:fhnd, const fmat[], va_args<>)
{
	return fwrite(fhnd, va_return(fmat, va_start<2>));
}

