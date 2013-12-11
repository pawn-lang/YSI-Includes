/**--------------------------------------------------------------------------**\
					===================================
					 y_inline - PAWN inline functions.
					===================================
Description:
	This library allows a user to write inline functions in their script.  It
	first detects all inline functions and generates data on them, such as
	parameter counts and addresses.  When an inline function is passed in code
	its current context data is stored.  Finally, when an inline function is
	found to be called at some point its current local stack is stored in global
	memory.  When the function actually is called, the stack is restored, and
	additional parameters which are the inline function parameters, are passed.
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
	
	The Original Code is the YSI Inline Function include.
	
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
	22/06/13:
		Rewrote the library from scratch for better performance all round.
	20/10/12:
		Fixed a bug with "Callback_Release" with public functions.
	15/11/11:
		Changed the precedence of "using" types.
	19/09/11:
		First version
\**--------------------------------------------------------------------------**/

#include "..\amx\asm"
#include "..\amx\disasm"
#include "..\amx\frame_info"
#include "..\YSI_Storage\y_amx"
#include "..\YSI_Internal\y_shortfunc"
#include "..\YSI_Core\y_debug"
#include "..\YSI_Core\y_utils"
#include "..\YSI_Data\y_bit"
#include "y_malloc"

#define INLINE_TYPE_VAR (0b00)
#define INLINE_TYPE_REF (0b10)
#define INLINE_TYPE_STR (0b01)
#define INLINE_TYPE_ARR (0b11)

enum E_CALLBACK_DATA
{
	// ===== ALWAYS FIRST =====
	ResolvedAlloc:E_CALLBACK_DATA_ALLOC, // Fully resolved address.
	// ===== ALWAYS AFTER =====
	E_CALLBACK_DATA_POINTER,
	E_CALLBACK_DATA_OFFSET,
	E_CALLBACK_DATA_FORMAT[2]
}

static stock
	YSI_g_sPrevInlineFunc = 0,
	YSI_g_sPrevJumpOver = 0,
	YSI_g_sCurInlineLocals,  // Number of locals in current parent.
	YSI_g_sCurInlineParams,  // Number of parameters to current parent.
	YSI_g_sCurInlinePointer, // Storage for the inline function's return.
	YSI_g_sCurInlineEntry,   // Pointer to the start of the data segment.
	YSI_g_sCurInlineLoop,    // Pointer to the current loopback label.
	YSI_g_sCurInlineCode;    // Pointer to the start of user code.

static stock const
	YSI_g_scError[] = "\7\7\7*** YSI Error: Unrecognised compilation in y_inline";

/**--------------------------------------------------------------------------**\
<summary>I@E</summary>
<param name="s">The array to store an inline function's data in.</param>
<param name="constFunc">Should this function copy the stack back?</param>
<returns>
	-
</returns>
<remarks>
	AKA. Inline_Entry
	
	This function gets the start of an inline function's code block.  It then
	removes itself from the compiled code so that it can never be called agian.
	
	If "constFunc" is 3, copy the stack back, if it isn't don't.
</remarks>
\**--------------------------------------------------------------------------**/

#define mutable

stock I@E(mutable const s[])
{
	P:2("Inline_Entry called: %s", s);
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
		addr1 = AMX_Read(YSI_g_sPrevJumpOver),
		addr2 = start + AMX_HEADER_COD,
		frm = DisasmGetOperand(ctx);
	if (YSI_g_sPrevJumpOver && addr1 == addr2 + AMX_REAL_ADDRESS - AMX_BASE_ADDRESS)
	{
		// Multiple inline functions in a row.  Jump over them all.
		AMX_Write(YSI_g_sPrevJumpOver, frm),
		YSI_g_sCurInlineEntry = start;
	}
	else if (YSI_g_sPrevJumpOver && addr1 == addr2 + AMX_REAL_ADDRESS - AMX_BASE_ADDRESS - 4 && Opcode:AMX_Read(addr2) == RelocateOpcode(OP_BREAK))
	{
		// Multiple inline functions in a row.  Jump over them all.
		AMX_Write(YSI_g_sPrevJumpOver, frm),
		YSI_g_sCurInlineEntry = start - 4;
	}
	else
	{
		new
			ctx2[AsmContext];
		AsmInitPtr(ctx2, addr2, 8),
		AsmEmitJump(ctx2, frm),
		YSI_g_sPrevJumpOver = addr2 + 4,
		YSI_g_sCurInlineEntry = start + 8;
	}
	// Store the pointer to the start of this new inline's available code.
	// =========================================================================
	// Save the data name pointer.
	addr2 = ref(s[strfind(s, ":")]),
	AMX_Write(addr2, '\02;'),
	AMX_Write(addr2 + 4, YSI_g_sCurInlineEntry),
	// Get the number of local variables already in the parent function.
	frm = GetCurrentFramePreviousFrame(),
	YSI_g_sCurInlineLocals = GetFrameLocalSize(frm),
	YSI_g_sCurInlineParams = GetFrameParameterSize(frm),
	// Save parameter counts, shifted for separate components.
	AMX_Write(addr2 + 8, (YSI_g_sCurInlineLocals >>> 2) | (YSI_g_sCurInlineParams << 22)),
	// =========================================================================
	// Build a linked list of inlines that are in scope.
	AMX_Write(addr2 + 16, YSI_g_sPrevInlineFunc),
	YSI_g_sCurInlinePointer = addr2 + 12,
	YSI_g_sPrevInlineFunc = ref(s);
	// Return 1 to enter the main "inline" function block.
	return 1;
}

#undef mutable

/**--------------------------------------------------------------------------**\
<summary>I@F</summary>
<returns>
	-
</returns>
<remarks>
	AKA. Inline_Allocator.
	
	This function determines the exact address of the start of the main inline
	function container loop.  That is, the label that things like "continue"
	jump to so that we know how much space we have to play with and where it is.
</remarks>
\**--------------------------------------------------------------------------**/

stock I@F()
{
	P:2("Inline_Allocator called");
	// This function takes up almost no space in a .pwn, but loads in a .amx.
	// Or at least as much as I want it to in order to give me code space to
	// play with.
	new
		start = GetCurrentFrameReturn(),
		ctx[DisasmContext];
	// "end" isn't currently used in "disasm", but we can't guarantee that.
	DisasmInit(ctx, start, start + 16);
	DisasmDecodeInsn(ctx);
	if (DisasmGetOpcode(ctx) != OP_JZER) return Debug_Print0(YSI_g_scError);
	// Get the end of the outer loop.
	YSI_g_sCurInlineCode = DisasmGetOperand(ctx);
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
	YSI_g_sCurInlineLoop = start + 8;
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>I@L</summary>
<returns>
	0
</returns>
<remarks>
	AKA. Inline_Main.
	
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
	
	"Inline_Allocator" currently marks the end of the first segment, and
	"Inline_Main" marks the end of the second segment.
</remarks>
\**--------------------------------------------------------------------------**/

static stock
	YSI_g_sJumpAddress,
	YSI_g_sRequiredSpace;

forward Inline_OnAsmError(ctx[AsmContext], AsmError:error);

public Inline_OnAsmError(ctx[AsmContext], AsmError:error)
{
	if (numargs() == 1) error = AsmGetError(ctx);
	// Actually USE the error to write the "JUMP" instruction correctly.
	switch (error)
	{
		case ASM_ERROR_SPACE:
		{
			if (YSI_g_sJumpAddress) P:E("ASM_ERROR_SPACE in Inline_Main.");
			else
			{
				// Get where the last instruction started to be written.
				ctx[AsmContext_buffer_offset] = YSI_g_sJumpAddress = AsmGetPreviousWriteOffset(),
				// Calculate how much of the function header was NOT written.
				YSI_g_sRequiredSpace -= YSI_g_sJumpAddress,
				// Save the address of the "JUMP" operand for later.
				YSI_g_sJumpAddress += 4 + ctx[AsmContext_buffer],
				// Allocate space for writing the "JUMP" (previously skipped).
				ctx[AsmContext_buffer_size] = cellmax;
				// Jump over the function end.
				@emit JUMP    0
				new
					target = YSI_g_sCurInlineCode + AMX_HEADER_COD - ctx[AsmContext_buffer] - YSI_g_sRequiredSpace;
				// Pad everything with "NOP"s.
				while (ctx[AsmContext_buffer_offset] != target) @emit NOP
				// Write the jump target as here.
				AMX_Write(YSI_g_sJumpAddress, ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset] - AMX_BASE_ADDRESS + AMX_REAL_ADDRESS);
			}
		}
		case ASM_ERROR_OPCODE : P:E("ASM_ERROR_OPCODE in Inline_Main.");
		case ASM_ERROR_OPERAND: P:E("ASM_ERROR_OPERAND in Inline_Main.");
	}
}

// "tryemit"
// This macro detects when an opcode couldn't be written due to a lack of space
// in the buffer, then instantly re-writes the same opcode to the same context!
// The reason this works is that there is an error handler that is called BEFORE
// "amx_emit_" returns the error code, and that handler deals with all the
// complex reallocations and jumps required to move the code about (in this case
// to fit around the existing jumps in the code around where we are writing new
// code).
#define _@emit%0\32;%1\10;%3 if(asm_emit_(ctx,%1 ) == ASM_ERROR_SPACE) asm_emit_(ctx,%1 );

stock I@K(...)
{
	return numargs() * 3;
}

stock I@L(constFunc, ...)
{
	//new
	//	bool:constFunc = I@;
	P:2("Inline_Main called (%d)", numargs());
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
	// Set this function to return to the end of the outer loop.
	SetCurrentFrameReturn(YSI_g_sCurInlineCode - AMX_REAL_ADDRESS - (AMX_HEADER_COD - AMX_BASE_ADDRESS));
	// =========================================================================
	//     NOW WE CAN DO THE MAIN FUNCTION CODE.
	// =========================================================================
	new
		argSize = GetFrameLocalSize(GetCurrentFramePreviousFrame());
	// Do we have enough space for everything.
	// Get the start of the user's function code.  The real start of THEIR code.
	ret += 8;
	if (DisasmDecodeInsn(dctx) && DisasmGetOpcode(dctx) == OP_BREAK) ret += 4;
	YSI_g_sCurInlineCode = ret;
	P:5("Inline_Main: YSI_g_sCurInlineEntry = %x", YSI_g_sCurInlineEntry);
	P:5("Inline_Main: YSI_g_sCurInlineLoop = %x", YSI_g_sCurInlineLoop);
	P:5("Inline_Main: YSI_g_sCurInlineCode = %x", YSI_g_sCurInlineCode);
	// Get the segment sizes and variable type counts.
	new
		args = numargs() - 1,
		varCount = 0;
	for (new i = 1; i <= args; ++i)
	{
		if (getarg(i) <= 0) ++varCount;
	}
	P:5("Inline_Main: varCount = %d", varCount);
	P:5("Inline_Main: arrCount = %d", args - varCount);
	// So-far, so-good.  The code above in preliminary tests seems to correctly
	// identify all the relevant and important points in the user code.
	new
		ctx[AsmContext];
	// =========================================================================
	//     CODE SPACE AVAILABLE
	// =========================================================================
	//  
	//  Inline_Entry: 6
	//  Vars: 2 v+r
	//  Arrays: 7 a
	//  JUMP: 2
	//  Inline_Allocator: 6
	//  
	//  Arrays: 6 a
	//  Vars: 5 v
	//  Refs: 6 r
	//  
	//  Inline_Main: 19
	//  
	//  Simple Total: 14 + 7v + 8r + 19
	//  Complex Total: 14 + 7v + 8r + 17a + 19
	//  
	//  Simple Required: 15 + 3v + 7r + 16
	//  Complex Required: 15 + 4v + 8r + 6a + 16
	//  
	// =========================================================================
	//     SEGMENT 1 - RESOLVE AND PUSH CLOSURE DATA AND PARAMETERS
	// =========================================================================
	YSI_g_sJumpAddress = 0,
	AsmInitPtr(ctx, YSI_g_sCurInlineEntry + AMX_HEADER_COD, YSI_g_sCurInlineLoop - YSI_g_sCurInlineEntry - 8),
	AsmSetErrorHandler(ctx, GetPublicAddressFromName("Inline_OnAsmError"));
	// Space for params + count.
	new
		// Size of stored closure data.
		offset = (YSI_g_sCurInlineParams + YSI_g_sCurInlineLocals + 12);
	if (varCount == args) // Only variables.
	{
		// =====================================================================
		//     SIMPLE CODE - NO ARRAYS OR STRINGS
		// =====================================================================
		if (YSI_g_sCurInlineLocals)
		{
			YSI_g_sRequiredSpace = 4 * 3 * args + 4 * 13;
			_@emit STACK      (-offset)
			_@emit ADDR.alt   (-offset) // Like "LCTRL 4; XCHG", but shorter.
			_@emit LREF.S.pri 12   // Load "func" variable.
			// Sadly "MOVS" checks that the destination is valid and in the stack, which
			// is what we didn't want.
			_@emit MOVS       offset
			// Reduce the stack again.  This is the shortest way I know (5 cells).
			_@emit STACK      (4 + YSI_g_sCurInlineLocals)
			_@emit PROC       // Set up the new frame.
			_@emit STACK      (-YSI_g_sCurInlineLocals) // Skip other locals again.
			new
				// Get the offset to the calling function's passed parameters.
				// 12 for this function's header, plus this function's parameters, plus
				// the last function's locals (currently none, MUST BE KEPT UP TO DATE),
				// plus the last function's header, plus the "func" variable.
				load = 12 + YSI_g_sCurInlineParams + 0 + 12 + 4,
				i = 0;
			while (i++ < args)
			{
				// Loop over the arguments and push them.
				_@emit LREF.S.pri load
				_@emit PUSH.pri
				load += 4;
			}
		}
		else
		{
			// This is the simplest of the four versions of the code.  Here
			// there are no arrays to copy over, nor are there any local
			// variables from the closure.
			offset -= 4,
			YSI_g_sRequiredSpace = 4 * 3 * args + 4 * 9;
			_@emit STACK      (-offset)
			_@emit ADDR.alt   (-offset)
			_@emit LREF.S.pri 12
			_@emit MOVS       offset
			_@emit PROC
			new
				load = 12 + YSI_g_sCurInlineParams + 0 + 12 + 4,
				i = 0;
			while (i++ < args)
			{
				_@emit LREF.S.pri load
				_@emit PUSH.pri
				load += 4;
			}
			offset += 4;
		}
	}
	else
	{
		// =====================================================================
		//     COMPLEX CODE - ARRAYS OR STRINGS
		// =====================================================================
		if (YSI_g_sCurInlineLocals)
		{
			YSI_g_sRequiredSpace = 4 * 4 * varCount + 4 * 6 * (args - varCount) + 4 * 13;
			_@emit STACK      (-offset)
			_@emit STACK      (YSI_g_sCurInlineLocals - argSize)
			_@emit LREF.S.pri 12
			_@emit MOVS       offset
			new
				load = 12 + 4,
				stor = -offset,
				i = 0;
			while (i < args)
			{
				varCount = getarg(++i) * 4;
				if (varCount <= 0)
				{
					stor -= 4;
					_@emit LREF.S.pri load
					_@emit STOR.S.pri stor
				}
				else
				{
					stor -= varCount;
					_@emit LOAD.S.pri load
					_@emit ADDR.alt   stor
					_@emit MOVS       varCount
				}
				load += 4;
			}
			_@emit STACK      (4 + argSize)
			_@emit PROC
			_@emit STACK      (-argSize)
		}
		else
		{
			offset -= 4,
			YSI_g_sRequiredSpace = 4 * 4 * varCount + 4 * 6 * (args - varCount) + 4 * 11;
			_@emit STACK      (-offset)
			_@emit ADDR.alt   (-offset)
			_@emit LREF.S.pri 12
			_@emit MOVS       offset
			_@emit PROC
			_@emit STACK      (-argSize)
			new
				load = 12 + YSI_g_sCurInlineParams + 0 + 12 + 4,
				stor = 0,
				i = 0;
			while (i < args)
			{
				varCount = getarg(++i) * 4;
				if (varCount <= 0)
				{
					stor -= 4;
					_@emit LREF.S.pri load
					_@emit STOR.S.pri stor
				}
				else
				{
					stor -= varCount;
					_@emit LOAD.S.pri load
					_@emit ADDR.alt   stor
					_@emit MOVS       varCount
				}
				load += 4;
			}
			offset += 4;
		}
	}
	// =========================================================================
	//     SEGMENT 2 - SAVE REFERENCES BACK
	// =========================================================================
	if (YSI_g_sJumpAddress == 0)
	{
		// Fake an error.
		ctx[AsmContext_buffer_size] = 0;
		@emit NOP
	}
	// The maths should now be correct.
	AsmInitPtr(ctx, YSI_g_sCurInlineLoop + AMX_HEADER_COD, cellmax);
	if (argSize) @emit STACK     argSize
	@emit RETN
	// Save this return address, so the instruction above goes to the one below.
	YSI_g_sJumpAddress = YSI_g_sCurInlineLoop + 12;
	// Save references.
	new
		load = -offset,
		stor = 12 + 4,
		i = 0;
	while (i < args)
	{
		varCount = getarg(++i) * 4;
		switch (varCount)
		{
			case -4:
			{
				load -= 4;
				@emit LOAD.S.alt load
				@emit SREF.S.alt stor
			}
			case 0: load -= 4;
			default: load -= varCount;
		}
		stor += 4;
	}
	// Copy the closure back (if there is anything that needs copying).
	if (constFunc && (YSI_g_sCurInlineParams || YSI_g_sCurInlineLocals))
	{
		if (!YSI_g_sCurInlineLocals) offset -= 4;
		@emit STACK      (-offset)
		@emit PUSH.pri
		@emit ADDR.pri   (-offset)
		@emit LREF.S.alt 12
		@emit MOVS       offset
		@emit POP.pri
		@emit STACK      offset
	}
	// Finish.
	@emit RETN
	// =========================================================================
	//     STORE THE RETURN ADDRESS
	// =========================================================================
	AMX_Write(YSI_g_sCurInlinePointer, YSI_g_sJumpAddress),
	AMX_Write(YSI_g_sCurInlinePointer - 12, '\02;');
	// =========================================================================
	//     FUNCTION EPILOG
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

#undef _@emit

/**--------------------------------------------------------------------------**\
<summary>Callback_Release</summary>
<param name="input[E_CALLBACK_DATA]">Callback to release.</param>
<returns>
	-
</returns>
<remarks>
	Releases all the data associated with a given callback (closure storage).
</remarks>
\**--------------------------------------------------------------------------**/

stock Callback_Release(input[E_CALLBACK_DATA])
{
	static
		ResolvedAlloc:ra,
		Alloc:a;
	if (!(input[E_CALLBACK_DATA_POINTER] & 0x80000000))
	{
		ra = input[E_CALLBACK_DATA_ALLOC];
		if (ra)
		{
			#emit CONST.alt     YSI_gMallocMemory
			#emit LOAD.pri      ra
			#emit SUB
			#emit SHR.C.pri     2
			#emit STOR.pri      a
			// Publics don't have any stored data.
			free(a);
		}
		input[E_CALLBACK_DATA_POINTER] = 0,
		input[E_CALLBACK_DATA_ALLOC] = ResolvedAlloc:0;
	}
}

/**--------------------------------------------------------------------------**\
<summary>Callback_Get</summary>
<param name="callback:name">Callback to find by name.</param>
<param name="ret[E_CALLBACK_DATA]">Where to store the pointer.</param>
<returns>
	-
</returns>
<remarks>
	Looks up the callback by name.  If the name has the correct data embedded
	within it that's great and we use that directly.  Otherwise this function
	loops backwards over the callbacks currently in scope (mostly) to the start
	of the parent function.  If a match is still not found this looks for a
	public function of the same name.  If that isn't found either it gives up.
</remarks>
\**--------------------------------------------------------------------------**/

forward _@_y_inline_@_();

public _@_y_inline_@_()
{
	strcmp("", "");
	strfind("", "");
}

stock bool:Callback_Get(callback:name, ret[E_CALLBACK_DATA], expect[] = "")
{
	P:2("Callback_Get called: %s", name);
	static
		fmat[2];
	Inline_EncodeFromatString(expect, fmat),
	ret[E_CALLBACK_DATA_FORMAT] = fmat;
	if (name[0] == callback_tag:'\03')
	{
		new
			ptr;
		if (AMX_GetPublicPointer(0, ptr, name[1], true))
		{
			ret[E_CALLBACK_DATA_POINTER] = ptr | 0x80000000;
			return true;
		}
		return false;
	}
	new
		pos = strfind(name, "\02");
	if (pos == -1)
	{
		new
			frm = GetCurrentFramePreviousFrame(),
			cur = YSI_g_sPrevInlineFunc,
			parent = GetFrameFunction(GetFramePreviousFrame(frm)),
			res;
		pos = strlen(name),
		frm = GetFrameReturn(frm);
		// Find the function by name.
		while (cur)
		{
			#emit PUSH.S      pos
			#emit PUSH.C      0
			#emit PUSH.S      name
			#emit PUSH.S      cur
			#emit PUSH.C      16
			#emit SYSREQ.C    strcmp
			#emit STACK       20
			#emit STOR.S.pri  res
			if (res == 0 && AMX_Read(cur + pos * 4) == '\02')
			{
				if (parent <= AMX_Read(cur + pos * 4 + 1 * 4) <= frm)
				{
					// Rewrite the value of "name" for the subsequent code.
					#emit LOAD.S.pri cur
					#emit STOR.S.pri name
					break;
				}
			}
			static const
				gsSearch[] = "\02";
			#emit PUSH.C      0
			#emit PUSH.C      0
			#emit PUSH.C      gsSearch
			#emit PUSH.S      cur
			#emit PUSH.C      16
			#emit SYSREQ.C    strfind
			#emit STACK       20
			#emit LOAD.S.alt  cur
			#emit IDXADDR
			#emit ADD.C       16
			#emit LOAD.I
			#emit STOR.S.pri  cur
		}
		if (!cur)
		{
			// Try publics...
			if (AMX_GetPublicPointer(0, pos, name, true))
			{
				ret[E_CALLBACK_DATA_POINTER] = pos | 0x80000000;
				return true;
			}
			return false;
		}
	}
	// Load this inline function's data in to our closure (and allocate memory).
	ret[E_CALLBACK_DATA_POINTER] = name[pos + 1];
	new
		to = name[pos + 2],
		local = (to & 0x00FFFFFF),
		params = (to & 0xFF000000) >>> 24;
	params = local + params + (local ? 3 : 2);
	new
		Alloc:a = malloc(params); // Allocate closure space.
	if (a)
	{
		// Get the address of the data.
		#emit CONST.alt     YSI_gMallocMemory
		#emit LOAD.S.pri    a
		#emit IDXADDR
		#emit STOR.S.pri    to
		params <<= 2,
		ret[E_CALLBACK_DATA_ALLOC] = ResolvedAlloc:to,
		ret[E_CALLBACK_DATA_OFFSET] = params;
		// Copy the stack over.  First get the frame of the function that used
		// an inline function, thus calling us indirectly.
		new
			from = GetFramePreviousFrame(GetCurrentFramePreviousFrame()) - (local << 2);
		// Adjust to the bottom of that stack, at least the bottom of the parts
		// we need (there may be more locals declared later that we don't need).
		if (local)
		{
			// Copy "params" bytes from "from" to "to".
			rawMemcpy(to, from, params),
			mset(a, local + 1, name[pos + 3]);
		}
		else
		{
			// Copy "params" bytes from "from" to "to".
			rawMemcpy(to, from + 4, params),
			// Save the "return" address for the inline to our fake stack.
			mset(a, 0, name[pos + 3]);
		}
		P:2("Callback_Get end");
		return true;
	}
	return false;
}

/**--------------------------------------------------------------------------**\
<summary>Inline_DecodeSimple</summary>
<param name="from[]">Array of variable types.</param>
<param name="at">Type slot.</param>
<returns>
	The next variable type stored in the bit array.
</returns>
<remarks>
	Returns data from a bit array when it is known that only basic types are
	stored (i.e. no arrays with length parameters).
</remarks>
\**--------------------------------------------------------------------------**/

#define Inline_DecodeSimple(%0,%1) (I@ = %0[(%1) >>> 5] & (2 << ((%1) & 0x1F)), (%1) += 2, I@)

/**--------------------------------------------------------------------------**\
<summary>Callback_Call</summary>
<param name="func[E_CALLBACK_DATA]">Info on the function to be called.</param>
<returns>
	-
</returns>
<remarks>
	Takes an inline function handler and parameters, and either calls the
	public function while passing through the parameters, or just jumps to the
	carefully crafted inline function code.
</remarks>
\**--------------------------------------------------------------------------**/

stock Callback_Call(func[E_CALLBACK_DATA], GLOBAL_TAG_TYPES:...)
{
	static
		addr;
	addr = func[E_CALLBACK_DATA_POINTER];
	if (addr & 0x80000000)
	{
		static
			ts[2];
		addr &= ~0x80000000,
		ts[0] = func[E_CALLBACK_DATA_FORMAT][0],
		ts[1] = func[E_CALLBACK_DATA_FORMAT][1];
		new
			at = 6,
			mm = (ts[0] & 0b00111110) + 6,
			len,
			end,
			var;
		#emit LOAD.S.alt    8 // Get the parameter count.
		#emit LCTRL         5 // Get the current frame.
		#emit ADD
		#emit ADD.C         8 // Adjust for header and "func".
		#emit STOR.S.pri    var
		#emit LCTRL         5 // Get the end.
		#emit ADD.C         12
		#emit STOR.S.pri    end
		P:5("Inline_Call: at = %d, mm = %d", at, mm);
		if (ts[0] & 0x01)
		{
			// Only has variables and references, easy to decode.
			while (at < mm)
			{
				if (var == end) return P:E("Insufficient parameters for Callback_Call.");
				if (Inline_DecodeSimple(ts, at))
				{
					P:7("INLINE_TYPE_REF");
					#emit LREF.S.pri  var
					#emit PUSH.pri
				}
				else
				{
					P:7("INLINE_TYPE_VAR");
					#emit LREF.S.pri  var
					#emit LOAD.I
					#emit PUSH.pri
				}
				var -= 4;
			}
		}
		else
		{
			// Can have arrays, harder to decode.
			while (at < mm)
			{
				if (var == end) return P:E("Insufficient parameters for Callback_Call.");
				if (Inline_DecodeComplex(ts, at, len) == INLINE_TYPE_VAR)
				{
					P:7("INLINE_TYPE_VAR");
					#emit LREF.S.pri  var
					#emit LOAD.I
					#emit PUSH.pri
				}
				else
				{
					P:7("INLINE_TYPE_REF/STR/ARR: %d", len);
					#emit LREF.S.pri  var
					#emit PUSH.pri
				}
				var -= 4;
			}
		}
		// Push the parameter count.
		var = (numargs() - 1) * 4;
		#emit PUSH.S    var
		// "Standard" function call.
		#emit LCTRL     6
		#emit ADD.C     28
		#emit PUSH.pri
		#emit LOAD.pri  addr
		#emit SCTRL     6
		#emit STACK     20
		#emit RETN
	}
	else
	{
		// Jump straight in to the code.
		#emit LOAD.pri  addr
		#emit SCTRL     6
	}
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>Callback_Array</summary>
<param name="func[E_CALLBACK_DATA]">Info on the function to be called.</param>
<param name="params[]">Array of data pointers.</param>
<param name="num">Size of the array.</param>
<returns>
	-
</returns>
<remarks>
	This is very similar to Callback_Call, but takes an array of ADDRESSES
	instead of normal parameters.  This is designed to help support some
	experimental OO code I was working on...
	
	If the target is a public function, the parameters are resolved and passed
	normally.  If the target is an inline function we are optimised for the
	common case, so move the data on to the stack (currently done value-by-value
	not all at once) and call "Callback_Call".
</remarks>
\**--------------------------------------------------------------------------**/

stock Callback_Array(const func[E_CALLBACK_DATA], const params[], num = sizeof (params))
{
	static
		addr;
	addr = func[E_CALLBACK_DATA_POINTER];
	if (addr & 0x80000000)
	{
		static
			ts[2];
		addr &= ~0x80000000,
		ts[0] = func[E_CALLBACK_DATA_FORMAT][0],
		ts[1] = func[E_CALLBACK_DATA_FORMAT][1];
		new
			at = 6,
			mm = (ts[0] & 0b00111110) + 6,
			len,
			end,
			var;
		// Get "params" into a pointer.
		#emit LOAD.S.alt    params
		#emit STOR.S.alt    end
		#emit LOAD.S.pri    num
		#emit SHL.C.pri     2
		#emit ADD
		#emit STOR.S.pri    var
		P:5("Inline_Call: at = %d, mm = %d", at, mm);
		if (ts[0] & 0x01)
		{
			// Only has variables and references, easy to decode.
			while (at < mm)
			{
				if (var == end) return P:E("Insufficient parameters for Callback_Array.");
				var -= 4;
				if (Inline_DecodeSimple(ts, at))
				{
					P:7("INLINE_TYPE_REF");
					#emit LREF.S.pri  var
					#emit PUSH.pri
				}
				else
				{
					P:7("INLINE_TYPE_VAR");
					#emit LREF.S.pri  var
					#emit LOAD.I
					#emit PUSH.pri
				}
			}
		}
		else
		{
			// Can have arrays, harder to decode.
			while (at < mm)
			{
				if (var == end) return P:E("Insufficient parameters for Callback_Array.");
				var -= 4;
				if (Inline_DecodeComplex(ts, at, len) == INLINE_TYPE_VAR)
				{
					P:7("INLINE_TYPE_VAR");
					#emit LREF.S.pri  var
					#emit LOAD.I
					#emit PUSH.pri
				}
				else
				{
					P:7("INLINE_TYPE_REF/STR/ARR: %d", len);
					#emit LREF.S.pri  var
					#emit PUSH.pri
				}
			}
		}
		// Push the parameter count.
		#emit LOAD.S.pri  num
		#emit SHL.C.pri   2
		#emit PUSH.pri
		// "Standard" function call.
		#emit LCTRL     6
		#emit ADD.C     28
		#emit PUSH.pri
		#emit LOAD.pri  addr
		#emit SCTRL     6
		#emit STACK     20
		#emit RETN
	}
	else
	{
		new
			len,
			end,
			var;
		// Get "params" into a pointer.
		#emit LOAD.S.alt    params
		#emit STOR.S.alt    end
		#emit LOAD.S.pri    num
		#emit SHL.C.pri     2
		#emit ADD
		#emit STOR.S.pri    var
		while (var > end)
		{
			var -= 4;
			#emit LREF.S.pri  var
			#emit PUSH.pri
		}
		#emit PUSH.S      func
		// Push the parameter count.
		#emit LOAD.S.pri  num
		#emit SHL.C.pri   2
		#emit ADD.C       4
		#emit PUSH.pri
		// "Standard" function call.
		#emit LCTRL     6
		#emit ADD.C     28
		#emit PUSH.pri
		#emit CONST.pri Callback_Call
		#emit SCTRL     6
		#emit STACK     12
		#emit RETN
	}
	// Never called, but includes the other function.
	return Callback_Call(func);
}

/**--------------------------------------------------------------------------**\
<summary>operator+</summary>
<param name="InlineRet:a">Dummy variable.</param>
<param name="b">Return value.</param>
<returns>
	-
</returns>
<remarks>
	This is a prefix function that takes some value and returns it to the
	caller's caller.  This makes "@return" in inline functions work.
</remarks>
\**--------------------------------------------------------------------------**/

// Operators for doing "return" from inside an inline function.
#define inline_return YSI_gInlineRet+=
#define @return inline_return

stock
	InlineRet:YSI_gInlineRet;

stock InlineRet:operator+(InlineRet:a, _:b)
{
	#pragma unused a
	// Modify the return address.
	#emit LOAD.S.pri 0
	#emit ADD.C      4
	#emit LOAD.I
	#emit STOR.S.pri 4
	// Get the last function's parameters.
	#emit LOAD.S.pri 0
	#emit ADD.C      8
	#emit LOAD.I
	#emit LOAD.S.alt 0
	#emit ADD
	#emit ADDR.alt   0
	#emit SUB
	#emit STOR.S.pri 8
	// Load the return value.
	#emit LOAD.S.pri b
	// Copy the previous frame.
	#emit LREF.S.alt 0
	#emit STOR.S.alt 0
	// Do the return
	#emit RETN
	return InlineRet:0;
}

stock InlineRet:operator+(InlineRet:a, Float:b)
{
	#pragma unused a
	// Modify the return address.
	#emit LOAD.S.pri 0
	#emit ADD.C      4
	#emit LOAD.I
	#emit STOR.S.pri 4
	// Get the last function's parameters.
	#emit LOAD.S.pri 0
	#emit ADD.C      8
	#emit LOAD.I
	#emit LOAD.S.alt 0
	#emit ADD
	#emit ADDR.alt   0
	#emit SUB
	#emit STOR.S.pri 8
	// Load the return value.
	#emit LOAD.S.pri b
	// Copy the previous frame.
	#emit LREF.S.alt 0
	#emit STOR.S.alt 0
	// Do the return
	#emit RETN
	return InlineRet:0;
}

// This used to be a compile-time macro to convert its parameters to the
// compressed format - it isn't anymore.  I tried to figure out if it was
// possible, and it probably is, but VERY hard, even compared to other macros
// I've written.
#define _F<%0> (#%0)

/**--------------------------------------------------------------------------**\
<summary>Inline_DecodeComplex</summary>
<param name="from[]">Array of variable types.</param>
<param name="at">Type slot.</param>
<param name="len">Return for array sizes.</param>
<returns>
	The next variable type stored in the bit array, and the length of arrays.
</returns>
<remarks>
	Returns data from a bit array when the parameter could be basic (variable or
	reference), or an array with a length (includes strings).  This requries far
	more complex code to decode as the lengths may span multiple cells, types
	can't because they are always 2 bits and always start on an even bit.
</remarks>
\**--------------------------------------------------------------------------**/

static stock Inline_DecodeComplex(from[], &at, &len)
{
	new
		slot = at >>> 5,
		// An encoded value is either 2 or 14 bits depending on type, so there
		// is no way to ever have odd offsets.  As a result there is no way for
		// a type to span two cells, so there's no need for complex switches.
		type = (from[slot] >>> (at & 0x1F)) & 0b11;
	at += 2;
	if (type & 0x01)
	{
		// Fast, cell boundary aware, length extraction.  The length is stored
		// -1 cell, so adjust for that too.
		switch (at & 0x1F)
		{
			// Start of the (next) cell.  For these two, doing "at += 2;"
			// spilled the pointer over in to the next cell.
			case 0: len = (from[slot + 1] & 0x0FFF) + 1;
			#define I@(%0) case %0:len=((from[slot]>>>%0)&0x0FFF)+1;
			// Whole length in one (current) cell.
			I@(02)I@(04)I@(06)I@(08)I@(10)I@(12)I@(14)I@(16)I@(18)
			#undef I@
			// End of the cell.
			case 20: len = (from[slot] >>> 20) + 1;
			// Two cells (let the compiler do the maths for us).
			#define I@(%0) case %0:len=((from[slot]>>>%0)|((from[slot+1]&(0xFFF>>>(32-%0)))<<(32-%0)))+1;
			I@(22)I@(24)I@(26)I@(28)I@(30)
			P:C(default: P:E("Odd offset in y_inline."););
			#undef I@
		}
		at += 12;
	}
	return type;
}

static stock Inline_EncodeFromatString(const str[], ret[2])
{
	new
		size = 0,
		complex = 0,
		b0,
		b1;
	for (new i = 0; ; ++i)
	{
		switch (str[i])
		{
			case '\0': break;
			case 'v':
			{
				// Add variable without length.
				b1 = (b1 << 2) | (b0 >>> 30),
				b0 = (b0 << 2) | INLINE_TYPE_REF,
				++size;
			}
			case 's', 'a':
			{
				if (str[i + 1] == '[')
				{
					new
						j = i + 2,
						len = 0;
					while ('0' <= str[j] <= '9') len = (len * 10) + (str[j++] - '0');
					--len,
					b1 = (b1 << 14) | (b0 >>> 18);
					// Add array with length.
					if (str[i] == 'a') b0 = (b0 << 14) | ((len & 0xFFF) << 2) | INLINE_TYPE_ARR;
					else b0 = (b0 << 14) | ((len & 0xFFF) << 2) | INLINE_TYPE_STR;
					if (str[j] != ']') --j;
					i = j,
					size += 7,
					complex = 1;
				}
				else
				{
					// Add variable without length.
					b1 = (b1 << 2) | (b0 >>> 30),
					b0 = (b0 << 2) | INLINE_TYPE_REF,
					++size;
				}
			}
			default:
			{
				// Add variable without length.
				b1 = (b1 << 2) | (b0 >>> 30),
				b0 = (b0 << 2) | INLINE_TYPE_VAR,
				++size;
			}
		}
	}
	// Add total size.
	ret[1] = (b1 << 6) | (b0 >>> 26),
	ret[0] = (b0 << 6) | ((size & 0b00011111) << 1) | (complex ^ 1);
}

stock Callback_Restore(func[E_CALLBACK_DATA])
{
	// Copy the closure data back over the calling function.
	new
		frm = GetFramePreviousFrame(GetCurrentFramePreviousFrame()),
		ret = GetFrameReturn(frm),
		pfr = GetFramePreviousFrame(frm);
	rawMemcpy(frm + 12 + GetFrameParameterSize(frm) - func[E_CALLBACK_DATA_OFFSET], _:func[E_CALLBACK_DATA_ALLOC], func[E_CALLBACK_DATA_OFFSET]),
	SetFrameReturn(frm, ret),
	SetFramePreviousFrame(frm, pfr);
}


/**--------------------------------------------------------------------------**\
<summary>Inline_Timer</summary>
<param name="func[]">The function to call on a delay.</param>
<param name="delay">how long before the first call?</param>
<param name="interval">How long between subsequent calls?</param>
<param name="repeat">How many times to call the function.</param>
<param name="format[]">The additional parameters' types.</param>
<param name="...">The additional parameters.</param>
<returns>
	-
</returns>
<remarks>
	Calls a function, which may be an inline function, after a given delay, and
	with the given regularity after that.  The parameters are slightly different
	to those in SetTimer - that takes only an interval and a repeat boolean.
	This instead takes two times - the first is the delay before the first call,
	the second is the delay between all subsequent calls (mainly to offset
	different timers within a given period).  The "repeat" parameter is also
	different - instead of being a boolean, it is a count.  "0" no longer means
	"don't repeat", but "repeat forever".  "1" no longer means "repeat forever",
	but "call once".  All other numbers (beside 0) specify an exact number of
	times to call the function before calling it no more.  This is in line with
	the "SetTimer_" and "SetTimerEx_" functions in the fixes2 plugin.
</remarks>
\**--------------------------------------------------------------------------**/

