

#include "..\amx\asm"
#include "..\amx\disasm"
#include "..\amx\frame_info"
#include "..\YSI-Storage\y_amx"
#include "..\YSI-Core\y_debug"

static stock
	YSI_g_sCurInlineLocals,  // Number of locals in current parent.
	YSI_g_sCurInlineParams,  // Number of parameters to current parent.
	YSI_g_sCurInlinePointer, // Pointer to the inline function's name.
	YSI_g_sCurInlineEntry,   // Pointer to the start of the data segment.
	YSI_g_sCurInlineLoop,    // Pointer to the current loopback label.
	YSI_g_sCurInlineCode;    // Pointer to the start of user code.

static stock const
	YSI_g_scError[] = "\7\7\7*** YSI Error: Unrecognised compilation in y_inline";

/**--------------------------------------------------------------------------**\
<summary>Inline_End</summary>
<param name="s">The array to store an inline function's data in.</param>
<returns>
	-
</returns>
<remarks>
	This function gets the start of an inline function's code block.  It then
	removes itself from the compiled code so that it can never be called agian.
</remarks>
\**--------------------------------------------------------------------------**/

#define mutable
stock Inline_End(mutable const s[])
{
	P:2("Inline_End called: %s", s);
	new
		start = GetCurrentFrameReturn() - 24,
		ctx[DisasmContext];
	DisasmInit(ctx, start, start + 32);
	// Get parameter.
	// There is a chance that "s" has the same value as an opcode.  However, if
	// that is the case it will EITHER have the same value as "PUSH.C" OR the
	// same value as "PUSH.pri" - it can't have the same value as both, so this
	// code will still catch that case.
	if (!DisasmDecodeInsn(ctx) || DisasmGetOpcode(ctx) != OP_PUSH_C || DisasmGetOperand(ctx) != GetCurrentFrameParameter(0))
	{
		// Compiled with extra debug information.
		start -= 8,
		ctx[DisasmContext_nip] = ctx[DisasmContext_start_ip] -= 8,
		// Consume the leading "break".
		DisasmDecodeInsn(ctx);
		if (DisasmGetOpcode(ctx) != OP_BREAK) return Debug_Print0(YSI_g_scError);
		// This mode uses "CONST.pri x; PUSH.pri" instead of "PUSH.C".
		DisasmDecodeInsn(ctx);
		if (DisasmGetOpcode(ctx) != OP_CONST_PRI || DisasmGetOperand(ctx) != GetCurrentFrameParameter(0)) return Debug_Print0(YSI_g_scError);
		DisasmDecodeInsn(ctx);
		if (DisasmGetOpcode(ctx) != OP_PUSH_PRI) return Debug_Print0(YSI_g_scError);
	}
	// Function parameter count.
	DisasmDecodeInsn(ctx);
	if (DisasmGetOpcode(ctx) != OP_PUSH_C || DisasmGetOperand(ctx) != 4) return Debug_Print0(YSI_g_scError);
	// Function call.
	DisasmDecodeInsn(ctx);
	if (DisasmGetOpcode(ctx) != OP_CALL) return Debug_Print0(YSI_g_scError);
	// Jump.
	DisasmDecodeInsn(ctx);
	if (DisasmGetOpcode(ctx) != OP_JZER) return Debug_Print0(YSI_g_scError);
	// Write out the jump for future calls.
	new
		ctx2[AsmContext];
	AsmInitPtr(ctx2, start + AMX_HEADER_COD, 8),
	// This returns an ABSOLUTE address, despite being compiled as a local jump,
	// and despite being within the AMX VM.  This is, however, very handy.
	AsmEmitJump(ctx2, DisasmGetOperand(ctx)),
	// Store the pointer to the start of this new inline's available code.
	YSI_g_sCurInlineEntry = start + 8;
	// Save the data name pointer.
	printf("s before: %s", s);
	start = strfind(s, ":");
	#emit LOAD.S.alt    s
	#emit LOAD.S.pri    start
	#emit SHL.C.pri     2
	#emit ADD
	#emit STOR.S.pri    start
	#emit ADD.C         4
	#emit STOR.pri      YSI_g_sCurInlinePointer
	// Write out "NULL" in place of ":".
	#emit ZERO.pri
	#emit SREF.S.pri    start
	printf("s after: %s", s);
	// Get the number of local variables already in the parent function.
	start = GetCurrentFramePreviousFrame();
	YSI_g_sCurInlineLocals = GetFrameLocalSize(start);
	YSI_g_sCurInlineParams = GetFrameParameterSize(start);
	// Return 1 to enter the main "inline" function block.
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>Inline_WriteFunctionProlog</summary>
<param name="entry">Address of the start of the inline's code.</param>
<param name="loop">Address of the loop start.</param>
<param name="code">Address of the start of user code.</param>
<returns>
	-
</returns>
<remarks>
	The code before the start of the function is split in to three parts:
	
	The first part comes before the start of the loop condition, and is where
	all the variables are initialised in the compiled code.  As we don't want to
	initialise any variables, this can be repurposed for function entry code.
	The address of this is stored in "entry", and it ends at "loop".
	
	The second part is where the function loops back to.  This MUST start with a
	"RETN" instruction to end the function in all cases, so any startup code in
	the first segment must jump over that "RETN".  The remainder of this section
	can be used for any more entry or exit code that is required.  Note that
	it can also start with a "STACK" opcode when required.  This section starts
	at "loop" and ends at "code".
	
	The final segment is not technically BEFORE the main function code but
	AFTER.  That's normally where the stack is restored, but we now have full
	control of that (so don't forget to write it in to the process exit code).
	
	"Inline_Filler" currently marks the end of the first segment, and
	"Inline_Loop" marks the end of the second segment.
</remarks>
\**--------------------------------------------------------------------------**/

static stock Inline_WriteFunctionProlog(entry, loop, code)
{
}

/**--------------------------------------------------------------------------**\
<summary>Inline_Filler</summary>
<returns>
	-
</returns>
<remarks>
	This function determines the exact address of the start of the main inline
	function container loop.  That is, the label that things like "continue"
	jump to so that we know how much space we have to play with and where it is.
	
	The parameters are irrelevant, all they do is take up space in the compiled
	AMX - this is not a bad thing, they are actually explicitly desiged to do
	exactly that, and take up a known amount of space at that.
	
	Note: NEVER try call this function when you have compiled with "-O2", that
	generates compressed macro opcodes that don't take up enough space.
</remarks>
\**--------------------------------------------------------------------------**/

stock Inline_Filler(
	a =  1, b =  2, c =  3) //, d =  4, e =  5, f =  6, g =  7, h =  8, i =  9, j = 10, k = 11, l = 12, m = 13,
	//n = 14, o = 15, p = 16, q = 17, r = 18, s = 19, t = 20, u = 21, v = 22, w = 23, x = 24, y = 25, z = 26)
{
	#pragma unused a, b, c //, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z
	P:2("Inline_Filler called");
	// This function takes up almost no space in a .pwn, but loads in a .amx.
	// Or at least as much as I want it to in order to give me code space to
	// play with.
	new
		start = GetCurrentFrameReturn(),
		ctx[DisasmContext];
	// "end" isn't currently used in "disasm", but we can't guarantee that.
	DisasmInit(ctx, start, start + 8);
	if (DisasmDecodeInsn(ctx) && DisasmGetOpcode(ctx) == OP_BREAK)
	{
		if (DisasmDecodeInsn(ctx) && DisasmGetOpcode(ctx) == OP_BREAK)
		{
			// Two breaks in a row - skip one.
			start += 4;
		}
		else Debug_Print0(YSI_g_scError);
	}
	// "start" now (hopefully) points to the main loop start address.
	YSI_g_sCurInlineLoop = start;
}

/**--------------------------------------------------------------------------**\
<summary>Inline_Loop</summary>
<returns>
	0
</returns>
<remarks>
	The code before the start of the function is split in to three parts:
	
	The first part comes before the start of the loop condition, and is where
	all the variables are initialised in the compiled code.  As we don't want to
	initialise any variables, this can be repurposed for function entry code.
	The address of this is stored in "entry", and it ends at "loop".
	
	The second part is where the function loops back to.  This MUST start with a
	"RETN" instruction to end the function in all cases, so any startup code in
	the first segment must jump over that "RETN".  The remainder of this section
	can be used for any more entry or exit code that is required.  Note that
	it can also start with a "STACK" opcode when required.  This section starts
	at "loop" and ends at "code".
	
	The final segment is not technically BEFORE the main function code but
	AFTER.  That's normally where the stack is restored, but we now have full
	control of that (so don't forget to write it in to the process exit code).
	
	"Inline_Filler" currently marks the end of the first segment, and
	"Inline_Loop" marks the end of the second segment.
</remarks>
\**--------------------------------------------------------------------------**/

stock Inline_Loop(...)
{
	P:2("Inline_Loop called (%d)", numargs());
	// MOST IMPORTANT THING TO DO FIRST!  Get the address to jump back to.
	new
		ret = GetCurrentFrameReturn(),
		heapClean = 0,
		dctx[DisasmContext];
	DisasmInit(dctx, ret, ret + 20),
	// Get the next code instruction.
	DisasmDecodeInsn(dctx);
	// There is some heap to clean up, how much?
	if (DisasmGetOpcode(dctx) == OP_HEAP)
	{
		ret += 8,
		heapClean = DisasmGetOperand(dctx),
		DisasmDecodeInsn(dctx);
	}
	// Get the jump to the end of the main loop.
	if (DisasmGetOpcode(dctx) != OP_JZER) return Debug_Print0(YSI_g_scError);
	// Set this function to return there.
	SetCurrentFrameReturn(DisasmGetOperand(dctx) - AMX_REAL_ADDRESS - (AMX_HEADER_COD - AMX_BASE_ADDRESS)),
	// NOW WE CAN DO THE MAIN FUNCTION CODE.
	// Do we have enough space for everything.
	// Current assembly costs (in cells):
	//  
	//  SETUP:
	//  - Stack:         14
	//  - Variables:     4 v
	//  - Arrays:        6 a
	//  - Jump:          2
	//  
	//  EXIT 1:
	//  - STACK:         2
	//  - RETN:          1
	//  
	//  EXIT 2:
	//  - References:    4 v
	//  - STACK:         2
	//  - RETN:          1
	//  
	// Current assembly available:
	//  
	//  SETUP:
	//  - Inline_End:    6
	//  - Variables:     2 v
	//  - Arrays:        7 a
	//  - Inline_Filler: 4 + n
	//  
	//  EXIT 1:
	//  - Inline_Loop 1: 3 (+5 = 8)
	//  
	//  EXIT 2:
	//  - References:    6 v
	//  - Inline_Loop 1: 5 (+3 = 8)
	//  
	// I am short:
	//  
	//  SETUP:
	//  - 6 + 2v
	//  
	// Have to make up the difference with Inline_Filler, and steal the extra
	// "2 v" from "EXIT 2" references.  Can also put 2 cells at code start, so
	// we just now need to allocate SIX extra cells with Inline_Filler, that's
	// just 3 dummy parameters.
	// 
	// All this is of course worst case (most optimised compile mode).
	// Get the start of the user's function code.  The real start of THEIR code.
	ret += 8;
	if (DisasmDecodeInsn(dctx) && DisasmGetOpcode(dctx) == OP_BREAK) ret += 4;
	YSI_g_sCurInlineCode = ret;
	P:5("Inline_Loop: YSI_g_sCurInlineEntry = %x", YSI_g_sCurInlineEntry);
	P:5("Inline_Loop: YSI_g_sCurInlineLoop = %x",YSI_g_sCurInlineLoop);
	P:5("Inline_Loop: YSI_g_sCurInlineCode = %x", YSI_g_sCurInlineCode);
	// Get the segment sizes and variable type counts.
	new
		args = numargs(),
		arrCount = 0,
		varCount = 0,
		refCount = 0;
	for (new i = 0; i != args; ++i)
	{
		switch (getarg(i))
		{
			case 0 : ++varCount;
			case -1: ++refCount, ++varCount;
			default: ++arrCount;
		}
	}
	P:5("Inline_Loop: varCount = %d", varCount);
	P:5("Inline_Loop: refCount = %d", refCount);
	P:5("Inline_Loop: arrCount = %d", arrCount);
	// So-far, so-good.  The code above in preliminary tests seems to correctly
	// identify all the relevant and important points in the user code.
	new
		ctx[AsmContext];
	// =========================================================================
	//     SEGMENT 1
	// =========================================================================
	AsmInitPtr(ctx, YSI_g_sCurInlineEntry + AMX_HEADER_COD, YSI_g_sCurInlineLoop - YSI_g_sCurInlineEntry),
	@emit STACK      (-4 - YSI_g_sCurInlineParams) // Space for params + count.
	@emit LCTRL      4                             // Get the stack bottom.
	@emit ADD.C      (-8 - YSI_g_sCurInlineLocals) // Stretch the stack bottom.
	@emit LREF.S.alt 12                            // Load "func" variable.
	@emit XCHG                                     // Copy data from *func to
	@emit MOVS (YSI_g_sCurInlineParams + YSI_g_sCurInlineLocals + 12) // stack.
	// This code copies parameters, header, and locals, but doesn't yet adjust
	// the stack to point to the bottom of all the locals, just to the header.
	ret = ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset] + 4;
	@emit PUSH.C     0 // TODO (in code)  // Add the "return" address.
	@emit PROC                            // Set up the new frame.
	new
		i = 0,
		argSize = 0,
		// Get the offset to the calling function's passed parameters.
		// 12 for this function's header, plus this function's parameters, plus
		// the last function's locals (currently none, MUST BE KEPT UP TO DATE),
		// plus the last function's header.
		load = 12 + YSI_g_sCurInlineParams + 0 + 12,
		stor = -YSI_g_sCurInlineLocals;
	// Now loop over all the parameter types.
	while (i < args)
	{
		new
			arg = getarg(i) * 4;
		if (arg <= 0)
		{
			if (AsmGetBufferSize(ctx) < (4 + 2) * 4) break;
			stor -= 4;
			// Regular variable at this point.
			@emit LREF.S.pri load
			@emit STOR.S.pri stor
			--varCount;
			argSize += 4;
		}
		else
		{
			if (AsmGetBufferSize(ctx) < (6 + 2) * 4) break;
			stor -= arg;
			@emit LOAD.S.pri load
			@emit ADDR.alt   stor
			@emit MOVS       arg
			argSize += arg;
			--arrCount;
		}
		++i,
		load += 4;
	}
	if (AsmGetBufferSize(ctx) < 2 * 4) return P:E("Error writing inline function header.");
	new
		jumpTargetAddress = ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset] + 4;
	@emit JUMP      0
	while (AsmGetBufferSize(ctx))
	{
		@emit NOP
	}
	// =========================================================================
	//     SEGMENT 2
	// =========================================================================
	AsmInitPtr(ctx, YSI_g_sCurInlineLoop + AMX_HEADER_COD, YSI_g_sCurInlineCode - YSI_g_sCurInlineLoop);
	// "Return" to the next instruction to clean up the stack.
	@emit STACK     0 // TODO in code. (YSI_g_sCurInlineLocals + args * 4)
	@emit RETN
	// Write the "return" address now that we know it.
	AMX_Write(ret, ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset] - AMX_HEADER_COD);
	ret = ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset] - 8;
	// Write the function epilog.
	// Clean up reference parameters.
	/*load = 12 + YSI_g_sCurInlineParams + 0 + 12,
	stor = -YSI_g_sCurInlineLocals;
	new
		j = 0;
	while (j < args)
	{
		++j;
		new
			arg = getarg(i);
		if (arg == -1)
		{
		}
	}*/
	// Now actually return to finish our code.  Currently this assumes that
	// "Inline_Call" has no parameters = MUST BE KEPT UP TO DATE.
	//@emit STACK     0
	@emit RETN
	// Write the remainder of the parameters.  First work out EXACTLY how much
	// space is required to write this data out.
	//seg2Size = varCount * (4 * 4) + arrCount * (6 * 4) + (2 * 4);
	//YSI_g_sCurInlineEntry = ctx[AsmContext_buffer_size] - seg2Size;
	YSI_g_sCurInlineCode = ctx[AsmContext_buffer_size] - (varCount * (4 * 4) + arrCount * (6 * 4) + (2 * 4));
	if (YSI_g_sCurInlineCode < ctx[AsmContext_buffer_offset]) return P:E("Unexpected insufficient size in y_inline.");
	// Pad with "NOPs".
	while (ctx[AsmContext_buffer_offset] < YSI_g_sCurInlineCode)
	{
		@emit NOP
	}
	// Write the remainder.
	// Write the jump offset to our newly written code, which should fall
	// EXACTLY before the user code.
	AMX_Write(jumpTargetAddress, ctx[AsmContext_buffer] + YSI_g_sCurInlineCode - AMX_BASE_ADDRESS + AMX_REAL_ADDRESS);
	while (i < args)
	{
		new
			arg = getarg(i) * 4;
		if (arg <= 0) // || arg == cellmin)
		{
			stor -= 4;
			// Regular variable at this point.
			@emit LREF.S.pri load
			@emit STOR.S.pri stor
			argSize += 4;
		}
		else
		{
			stor -= arg;
			@emit LOAD.S.pri load
			@emit ADDR.alt   stor
			@emit MOVS       arg
			argSize += arg;
		}
		++i,
		load += 4;
	}
	// Allocate the memory for our locals. (they've already been written to).
	argSize += YSI_g_sCurInlineLocals;
	AMX_Write(ret, argSize);    // To clean up the stack.
	@emit STACK      (-argSize) // To allocate the stack.
	// =========================================================================
	//     STORAGE.
	// =========================================================================
	// Write this function's pointer to the original data array.
	#emit LOAD.pri YSI_g_sCurInlineEntry
	#emit SREF.pri YSI_g_sCurInlinePointer
	// =========================================================================
	//     FUNCTION EPILOG.
	// =========================================================================
	// Clean up the heap manually because we are jumping straight over the
	// original cleanup code - in fact we may have destroyed it entirely by
	// writing new code over it.
	#emit LCTRL      2
	#emit LOAD.S.alt heapClean
	#emit ADD
	#emit SCTRL      2
	return 0;
}

stock Inline_Call(func[], ...)
{
}
