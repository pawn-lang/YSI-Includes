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
		sPushRequirements,
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
	#emit POP.pri
	#emit STOR.pri     sPushRequirements
	// The stack is now back to where it was before this function was called.
	// So is the frame, so technically now everything is in the same stack.
	// We must copy parameters from the previous stack to the current stack.
	// There are two methods for this - increase the stack and 'memcpy' in, or
	// loop over all the parameters and re-push them.  I suspect the memcpy
	// version MAY be faster, but there is some trickyness with the stack to
	// call a function while inserting in to the stack.  The best non-JIT method
	// would be `MOVS`, but that requires more run-time code modification, which
	// we can't do (I don't think, never ACTUALLY tried...).  For now, just loop
	// through them - I can improve the code later.
	if (sPushRequirements < 0)
	{
		// Push the number of parameters for the outer call.
		#emit STACK        0 // Load `[stk]` in to `alt`.
		#emit PUSH         sTotalParameters
		#emit LOAD.pri     sPushRequirements
		#emit ADD
		#emit SCTRL        4 // Move the stack down a load at once.
		// That code actually gets the stack position, THEN pushes, THEN adjusts
		// it (and the result may not move).  This is because we know one value
		// that needs to go on the stack and how many temp values need to go on,
		// but if we pushed one then adjusted how much we needed to alter the
		// stack by, that would actually take MORE code.
	}
	else if (sPushRequirements > 0)
	{
		// Already got the offset - use it.
		#emit LOAD.pri     sTotalParameters
		#emit SREF.pri     sPushRequirements
	}
	{}
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
#define CALL@YVA2_DummyPush YVA2_DummyPush(-1, -1, -1, -1, -1, -1, -1)
stock YVA2_DummyPush(const skippedBytes = 0, const pushedBytes = 0, const pushRequirements = 4, const dummy0 = 0, const dummy1 = 0, const dummy2 = 0, const dummy3 = 0)
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
		YVA2_DoPush(pushedBytes, skippedBytes, pushRequirements);
	}
	P:W("Bare `___` usage found - make sure it is a function parameter.");
	return 0;
}

static stock YVA2_CodeGenPushSite(ctx[AsmContext], const pushedBytes, const skippedBytes, const depth, const offset)
{
	// `pushedBytes` is the number of bytes originally pushed to the target
	// function (which includes four for the `___` return value).
	// Use `ctx` so we can use `@emit`.
	if (depth)
	{
		@emit PUSH.C       depth * -cellbytes  // 8
		@emit NOP                              // 12
	}
	else
	{
		@emit ADDR.pri     offset              // 8
		@emit PUSH.pri                         // 12
	}
	@emit PUSH.C       pushedBytes - 4         // 28
	@emit PUSH.C       skippedBytes            // 20
	@emit PUSH.C       12                      // 36
	@emit CALL.abs     addressof (YVA2_DoPush) // 44
	// We keep the `HEAP` here since we know that the original code wants to
	// clean up an extra four bytes from the heap, so it still needs to exist.
	@emit HEAP         4                       // 52
	// We have at least 40 bytes left to play with after `CALL`:
	//   
	//   // If this is the last call of many:
	//   STACK      N // Remove all temp variables.
	//   // If this is the only call:
	//   POP.alt      // Remove the parameter count storage.
	//   
	// Or after `SYSREQ.C`:
	//   
	//   POP.alt      // Load the parameter count.
	//   PUSH.pri     // Store the function return value.
	//   LCTRL      4 // Load the stack value.
	//   ADD          // Add them together.
	//   POP.alt      // Move the parameter count.
	//   SCTRL      4 // Store the stack pointer back.
	//   MOVE.pri     // Move the parameter count.
	//   // If this is the last call.
	//   STACK      N // Remove all temp variables.
	//   // If this is the only call:
	//   POP.alt      // Remove the parameter count storage.
	//   
	// Longer alternative (not good to be longer...)
	//   
	//   LOAD.S.alt p // Load the parameter count.
	//   STOR.S.pri p // Store the function return value.
	//   LCTRL      4 // Load the stack value.
	//   ADD          // Add them together.
	//   SCTRL      4 // Store the stack pointer back.
	//   POP.alt      // Remove the pushed parameter count.
	//   LOAD.S.pri p // Load the parameter count.
	//   // If this is the last call.
	//   STACK      N // Remove all temp variables.
	//   // If this is the only call:
	//   POP.alt      // Remove the parameter count storage.
	//   
	// Need to account for the worst-case, which is 11 bytes (44 cells).  Need
	// extra pushes to account for this (only in `-O1`, all other modes are fine
	// but will unfortunately get worse as a result - just use `-O1`)!
	// 
	// Actually, the worst case is not too bad - if there are two (or more)
	// nested calls then one will use 9 cells and the other 11.  This averages
	// out to 10, which we have!  If there is only one, there is only 10 bytes.
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

static stock YVA2_CodeGenDeepCleanup(ctx[AsmContext], depth)
{
	// Remove all the temporary storage locations.
	@emit STACK        depth * cellbytes
}

static stock YVA2_CodeGenSimpleCleanup(ctx[AsmContext])
{
	// Remove a single temporary storage location.
	@emit POP.alt
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
		if (CodeScanGetMatchStack(m) < YSI_g_sStacks[pos])
		{
			YSI_g_sPassthroughNestings = pos,
			// First, rewrite the `___` call-site to call `YVA2_DoPush` instead.
			YVA2_CodeGenPushSite(
				YSI_g_sContexts[pos],
				CodeScanGetMatchHole(m, 0),
				YSI_g_sSkips[pos],
				pos ? 0 : (YSI_g_sMaxNesting + 1),
				-YSI_g_sStacks[0] - pos * cellbytes); // YSI_g_sStacks[0]!!!
			// Shift the code up.
			new
				dest = YSI_g_sContexts[pos][AsmContext_buffer],
				len = CodeScanGetMatchLength(m),
				end = CodeScanGetMatchAddressData(m) + len;
			YVA2_CodeGenShiftCode(
				dest + YSI_g_sContexts[pos][AsmContext_buffer_offset],
				dest + YSI_g_sLength[pos],
				end);
			// Adjust the assembly context.  52 is the length of the code from
			// `YVA2_CodeGenPushSite`.
			YSI_g_sContexts[pos][AsmContext_buffer_offset] = (end - dest) - (YSI_g_sLength[pos] - 52) - 16;
			if (len == 24)
			{
				YSI_g_sContexts[pos][AsmContext_buffer_offset] -= 8;
			}
			YVA2_CodeGenPushVariable(YSI_g_sContexts[pos], -YSI_g_sStacks[0] - pos * cellbytes);
			YSI_g_sContexts[pos][AsmContext_buffer_offset] += 8;
			if (len == 24)
			{
				YVA2_CodeGenMainCleanup(YSI_g_sContexts[pos]);
			}
			if (YSI_g_sPassthroughNestings)
			{
				// Is a nesting.  Do nothing.
			}
			else if (YSI_g_sMaxNesting)
			{
				// Was nested - needs multiple call's cleanups.
				YVA2_CodeGenDeepCleanup(YSI_g_sContexts[pos], (YSI_g_sMaxNesting + 1));
				YSI_g_sMaxNesting = 0;
			}
			else
			{
				// Never nested - simple cleanup (just a pop).
				YVA2_CodeGenSimpleCleanup(YSI_g_sContexts[pos]);
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
	YSI_g_sSkips[YSI_g_sPassthroughNestings] = (YSI_g_sLength[YSI_g_sPassthroughNestings] == 96) ? 0 : CodeScanGetMatchHole(m, 0),
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

hook OnScriptInit()
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
		OP(PUSH_C,     28)              // 68
		OP(CALL,       &YVA2_DummyPush) // 76
		OP(HEAP,       4)               // 84
		OP(STOR_I)                      // 88
		OP(MOVE_PRI)                    // 92
		OP(PUSH_PRI)                    // 96
	);
	CodeScanAddMatcher(scanner, csmO0A);
	CodeScanMatcherInit(csmO0B, &YVA2_FoundPush);
	CodeScanMatcherPattern(csmO0B,
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
		OP(PUSH_C,     28)              // 72
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
		OP(PUSH_C,     0)               // 8
		OP(PUSH_C,     0)               // 16
		OP(PUSH_C,     0)               // 24
		OP(PUSH_C,     0)               // 32
		OP(PUSH_C,     4)               // 40
		OP(PUSH_C,     0)               // 48
		OP(PUSH_C,     ???)             // 56
		OP(PUSH_C,     28)              // 64
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
}

