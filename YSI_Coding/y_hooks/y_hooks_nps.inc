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

#define HOOK_STOCK__%0(%1) FUNC_PARSER(YHNPS,ARR_MUL_CST:STR_CST_DEF:NUM_CST_DEF:REF_DEF:EXT_TAG:)(%0(%1))()()(1,0)
#define HOOK_NATIVE__ HOOK_STOCK__
#define HOOK_native__ HOOK_STOCK__
#define HOOK_stock__ HOOK_STOCK__
#define HOOK_FUNCTION__ HOOK_STOCK__
#define HOOK_function__ HOOK_STOCK__

// Strip spaces from the generated function names.
#define @yH_%0\32; @yH_ // hook
#define @_Hy%0\32; @_Hy // extra stock/native info
#define @Hy_%0\32; @Hy_ // hook stock/native
#define @H_y%0\32; @H_y // hook public
#define @y_H%0\32; @y_H // DEFINE_HOOK_RETURN
#define @_yH%0\32; @_yH // DEFINE_HOOK_REPLACEMENT

// Arrays.
//
// %0  = `const`
// %1  = Tag (unused)
// %2  = Name
// %4+ = Dims
#define YHNPS_ARR(%0,%1,%2,%4)%8$ YHNPS_BYREF(%0%2[%4],%2)%8$
#define YHNPS_ARR_ARR(%0,%1,%2,%4,%5)%8$ YHNPS_BYREF(%0%2[%4][%5],%2)%8$
#define YHNPS_ARR_ARR_ARR(%0,%1,%2,%4,%5,%6)%8$ YHNPS_BYREF(%0%2[%4][%5][%6],%2)%8$

// Strings.
//
// %0  = `const`
// %1  = Tag (unused)
// %2  = Name
// %4  = Size
// %3  = Default (unused)
#define YHNPS_STR(%0,%1,%2,%4)%8$ YHNPS_BYREF(%0%2[%4],%2)%8$
#define YHNPS_STR_DEF(%0,%1,%2,%4,%3)%8$ YHNPS_BYREF(%0%2[%4],%2)%8$

// Varargs.
//
// %0  = `const` (unused)
// %1  = Tag
// %2  = Name (unused)
// %5  = Prototype parameters
// %6  = Call parameters
#define YHNPS_EXT(%0,%1,%2)%8$(%5)(%6)(%9,%4) %8$(%5,%1...)(%6)(%9,%4)

// References.
//
// %0  = `const` (unused)
// %1  = Tag (unused)
// %2  = Name
// %3  = Default (unused)
#define YHNPS_REF(%0,%1,%2)%8$ YHNPS_BYREF(&%2,%2)%8$
#define YHNPS_REF_DEF(%0,%1,%2,%3)%8$ YHNPS_BYREF(&%2,%2)%8$

// Variables.
//
// %0  = `const`
// %1  = Tag (unused)
// %2  = Name
// %3  = Default (unused)
#define YHNPS_NUM(%0,%1,%2)%8$ YHNPS_BYVAL(%0%2,%2)%8$
#define YHNPS_NUM_DEF(%0,%1,%2,%3)%8$ YHNPS_BYVAL(%0%2,%2)%8$

// Generate the parameter descriptions.
//
// %0  = Name in prototype
// %1  = Name in call
// %5  = Prototype parameters
// %6  = Call parameters
// %9  = Shift
// %4  = Existing values
// %7  = Prefix
#define YHNPS_BYREF(%0,%1)%8$(%5)(%6)(%9,%4) %8$(%5,%0)(%6,%1)(%9+1,%4)
#define YHNPS_BYVAL(%0,%1)%8$(%5)(%6)(%9,%4) %8$(%5,%0)(%6,%1)(%9+1,1<<%9|%4)

// End, generate the code.
//
// %0  = Name
// %3  = Descriptor
// %5  = Prototype parameters
// %6  = Call parameters
// %9  = Shift
// %4  = Existing values
// %7  = Prefix0
// %1  = Prefix1
#define YHNPS_END(%0)%8$(,%5)(,%6)(%9,%4) %8$forward YHNPS_U0<%0>(%5);YHNPS_U1<%0>(%5);YHNPS_U1<%0>(%5)_yH@(%4),%0(%6),_@yH();YHNPS_U0<%0>(%5)
#define YHNPS_NUL(%0)%8$()() YHNPS_END(%0)%8$(,)(,)

// Helper macro to generate the unique function name without bloating the
// generated code multiple times.
#define YHNPS_U0<%1> UNIQUE_FUNCTION<@Hy_%1@...>
#define YHNPS_U1<%1> UNIQUE_FUNCTION<@_Hy%1@...>

// Doing `hook native` instead of `HOOK_NATIVE__` attaches the `forward` and
// unique value earlier.  This just does all the same code, but with a reduced
// ending name generation.
#define HOOK_REDO__%0(%1) FUNC_PARSER(YHNPS2,ARR_MUL_CST:STR_CST_DEF:NUM_CST_DEF:REF_DEF:EXT_TAG:)(%0(%1))()()(1,0)
#define YHNPS2_ARR YHNPS_ARR
#define YHNPS2_ARR_ARR YHNPS_ARR_ARR
#define YHNPS2_ARR_ARR_ARR YHNPS_ARR_ARR_ARR
#define YHNPS2_STR YHNPS_STR
#define YHNPS2_STR_DEF YHNPS_STR_DEF
#define YHNPS2_EXT YHNPS_EXT
#define YHNPS2_REF YHNPS_REF
#define YHNPS2_REF_DEF YHNPS_REF_DEF
#define YHNPS2_NUM YHNPS_NUM
#define YHNPS2_NUM_DEF YHNPS_NUM_DEF
#define YHNPS2_BYREF YHNPS_BYREF
#define YHNPS2_BYVAL YHNPS_BYVAL
#define YHNPS2_END(%0)%8$(,%5)(,%6)(%9,%4) %8$@Hy_%0(%5);@_Hy%0(%5);@_Hy%0(%5)_yH@(%4),%0(%6),_@yH();@Hy_%0(%5)
#define YHNPS2_NUL(%0)%8$()() YHNPS2_END(%0)%8$(,)(,)

// Remove specified priorities from the original call.
#define _yH@(%0),%1@%2(%3),_@yH(); _yH@(%0),%1(%3),_@yH();

new
	YSI_g_sNPSBaseCall,
	YSI_g_sNPSTrampoline,
	YSI_g_sNPSReplace,
	YSI_g_sNPSStack;

static
	YSI_g_sTempRet;

static stock YHNPS_Find(heap, end, value)
{
	new
		start = 0,
		mid;
	--end;
	while (start <= end)
	{
		mid = (start + end) / 2;
		new
			diff = value - AMX_Read(heap + mid * 8);
		if (diff < 0)
		{
			start = mid + 1;
		}
		else if (diff > 0)
		{
			end = mid - 1;
		}
		else
		{
			return AMX_Read(heap + mid * 8 + 4);
		}
	}
	return cellmin;
}

static stock YHNPS_Insert(heap, count, value, ptr)
{
	new
		start = 0,
		mid,
		end = count - 1;
	while (start <= end)
	{
		mid = (start + end) / 2;
		new
			diff = value - AMX_Read(heap + mid * 8);
		if (diff < 0)
		{
			start = mid + 1;
		}
		else if (diff > 0)
		{
			end = mid - 1;
		}
		else
		{
			return;
		}
	}
	if (start == count)
	{
		// Shift all the greater values up.
		AMX_Write(heap + count * 8, value);
		AMX_Write(heap + count * 8 + 4, ptr);
	}
	else
	{
		// Shift all the greater values up.
		rawMemcpy(heap + mid * 8 + 8, heap + mid * 8, (count - mid) * 8);
		AMX_Write(heap + mid * 8, value);
		AMX_Write(heap + mid * 8 + 4, ptr);
	}
}

Hooks_Continue_(GLOBAL_TAG_TYPES:...)
{
	return 0;
}

static stock YHNPS_Push(heap, &allocated, &nativeCount, &stockCount, base, find, replace)
{
	if (allocated == max(nativeCount, stockCount))
	{
		// Space to insert 32 new values for each hook type.
		HeapAllocCells(6 * 32);
		// Move the arrays up in memory.
		if (nativeCount)
		{
			rawMemcpy(heap + allocated * 16 + 32 * 16, heap + allocated * 16, nativeCount * 8);
		}
		if (stockCount)
		{
			rawMemcpy(heap + allocated * 8 + 32 * 8, heap + allocated * 8, stockCount * 8);
		}
		allocated += 32;
	}
	if (find < 0)
	{
		YHNPS_Insert(heap, nativeCount, -find, replace + base);
		YHNPS_Insert(heap + allocated * 16, nativeCount, GetNativeAddressFromIndex(-find), replace + base);
		++nativeCount;
	}
	else
	{
		YHNPS_Insert(heap + allocated * 8, stockCount, find, replace + base);
		++stockCount;
	}
}

_@yH(&a = 0, &b = 0, &c = 0, &d = 0, &e = 0, &f = 0)
{
	#pragma unused a, b, c, d, e, f
	// This function does nothing.  It merely exists to reserve space for
	// codegen.  According to my experiments, just 4 parameters are enough to
	// reserve enough space (exactly) for the code generated below, even for a
	// function with no parameters.  But better to be safe than sorry.
}

public OnCodeInit()
{
	Indirect_Init();

	// Step 1:
	//
	//   Read the AMX header to loop over all the `@_Hy` functions.  These
	//   contain the call to `_yH@` which generates the trambopoline code.
	//
	//   From this data we build a list of all calls to replace.
	new
		heap = GetAmxHeapTop(),
		allocated = 0,
		nativeCount = 0,
		stockCount = 0,
		idx1,
		idx2,
		base;
	{
		new hdr[AMX_HDR];
		GetAmxHeader(hdr);
		base = GetAmxBaseAddress() + hdr[AMX_HDR_COD];
	}
	{
		YSI_g_sNPSBaseCall = cellmin;
		// Needs to be split over multiple lines because macros (`_A`).
		while (
			(idx1 = AMX_GetPublicPointerPrefix(idx1, YSI_g_sNPSReplace, _A<@Hy_>))
			&&
			(idx2 = AMX_GetPublicPointerPrefix(idx2, YSI_g_sNPSTrampoline, _A<@_Hy>))
		)
		{
			@.YSI_g_sNPSTrampoline();
			if (YSI_g_sNPSStack != YSI_g_sNPSTrampoline)
			{
				YHNPS_Push(heap, allocated, nativeCount, stockCount, base, YSI_g_sNPSReplace, YSI_g_sNPSStack);
				YSI_g_sNPSStack = YSI_g_sNPSTrampoline;
			}
		}
	}
	if (YSI_g_sNPSBaseCall != cellmin)
	{
		// Store the final chain.
		YHNPS_Push(heap, allocated, nativeCount, stockCount, base, YSI_g_sNPSBaseCall, YSI_g_sNPSTrampoline);
	}

	// Step 2:
	//
	//   Iterate over the entire mode and replace all relevant calls.
	//
	new
		Opcode:call = RelocateOpcode(OP_CALL),
		Opcode:nop = RelocateOpcode(OP_NOP),
		Opcode:proc = RelocateOpcode(OP_PROC),
		dctx[DisasmContext];
	DisasmInit(dctx);
	for ( ; ; )
	{
		switch (DisasmNextInsn(dctx))
		{
		case OP_NONE:
		{
			break;
		}
		case OP_SYSREQ_C:
		{
			// Check that the previous OP is `PUSH.C`.  That reqpresents a real native call, not our
			// wrapper.
			if (Opcode:AMX_Read(DisasmGetCurIp(dctx) - 8) == proc)
			{
				continue;
			}
			idx1 = YHNPS_Find(heap, nativeCount, DisasmGetOperand(dctx));
		}
		case OP_SYSREQ_D:
		{
			if (Opcode:AMX_Read(DisasmGetCurIp(dctx) - 8) == proc)
			{
				continue;
			}
			idx1 = YHNPS_Find(heap + allocated * 16, nativeCount, DisasmGetOperand(dctx));
		}
		case OP_CALL:
		{
			idx1 = YHNPS_Find(heap + allocated * 8, stockCount, DisasmGetOperandReloc(dctx));
			if (idx1 != cellmin)
			{
				// Write a different target address.
				AMX_Write(DisasmGetCurIp(dctx) + 4, idx1);
			}
			continue;
		}
		default:
		{
			continue;
		}
		}
		// `SYSREQ.C` is always followed by `STACK`, except with `#emit` usage.
		// We need to change the pair in to a single `CALL`.  Don't forget
		// `SYSREQ.D`.
		if (idx1 != cellmin)
		{
			// Write a different target address.
			base = DisasmGetCurIp(dctx);
			AMX_Write(base, _:call);
			AMX_Write(base + 4, idx1);
			if (DisasmNextInsn(dctx) == OP_STACK)
			{
				AMX_Write(base + 8, _:nop);
				AMX_Write(base + 12, _:nop);
			}
		}
	}

	// Step 2:
	//
	//   Generate `continue`.
	//
	Hooks_GenerateContinue();

	// Clear the stack.
	YSI_g_sNPSStack = 0;
	HeapRelease(heap);
	#if defined YHNPS_OnCodeInit
		YHNPS_OnCodeInit();
	#endif
	return 1;
}

#undef OnCodeInit
#define OnCodeInit YHNPS_OnCodeInit
#if defined YHNPS_OnCodeInit
	forward YHNPS_OnCodeInit();
#endif

/*

Trampoline code, to add the indirection pattern to the start of the parameter
list.  I.e. change this:

	SetPlayerHealth(playerid, 5.5);

To:

	SetPlayerHealth("if", playerid, 5.5);

This function is called, and just needs to insert a new function.

// No `PROC`, so no adjusted frame yet.
#emit POP.alt                 // Store return address.
#emit POP.pri                 // Store parameter count.
#emit PUSH.C   "param-string" // Pre-get the address.
#emit ADD.C    4              // Increase the parameter count.
#emit PUSH.pri
#emit PUSH.alt
#emit JUMP     TrueFunction   // Jump to the start of the implementation.

*/

#define continue(%0) Hooks_Continue_(%0)

stock _yH@(compressedFormat)
{
	#pragma unused compressedFormat
	// Get the next function call address, being the original function.  This
	// can also tell us if it is a native, public, or stock (which is a nice
	// side-effect I wasn't planning).
	new
		dctx[DisasmContext],
		ctx[AsmContext],
		addr,
		type = 0;
	DisasmInit(dctx, GetCurrentFrameReturn());
	while (DisasmNext(dctx))
	{
		switch (DisasmGetOpcode(dctx))
		{
		case OP_CALL:
		{
			addr = DisasmGetOperandReloc(dctx);
			type = 1;
			break;
		}
		case OP_SYSREQ_C:
		{
			addr = -DisasmGetOperand(dctx);
			type = -(YSI_g_sNPSTrampoline + 39 * cellbytes);
			break;
		}
		case OP_SYSREQ_D:
		{
			type = -(YSI_g_sNPSTrampoline + 39 * cellbytes);
			break;
		}
		}
	}
	//if (type < 0)
	//{
	//	// Native function call.
	//	addr = -addr;
	//}

	AsmInitPtr(ctx, YSI_g_sNPSTrampoline + AMX_HEADER_COD, YSI_g_sNPSReplace - YSI_g_sNPSTrampoline);
	// Forward the function, storing the chain data in the heap.   Note that no
	// `PROC` is added to this new trambopoline:
	//
	//   https://www.youtube.com/watch?v=geHqnV4Mk_4
	//

	// Build the structure in the stack first.
	@emit POP.pri                                                               // 1
	@emit PUSH.C       compressedFormat                                         // 3

	// Chain the functions.
	if (YSI_g_sNPSBaseCall == addr)
	{
		@emit PUSH.C       YSI_g_sNPSStack                                      // 5
		YSI_g_sNPSStack = YSI_g_sNPSTrampoline; // Replace.
	}
	else if (YSI_g_sNPSBaseCall == cellmin)
	{
		@emit PUSH.C       (type < 0 ? type : addr)                             // 5
		YSI_g_sNPSStack = YSI_g_sNPSTrampoline;
	}
	else
	{
		@emit PUSH.C       (type < 0 ? type : addr)                             // 5
	}

	@emit PUSH.C       8                                                        // 7
	@emit PUSH.pri     // Save the return address again.                        // 8
	@emit PUSH         ref(YSI_g_sNPSStack)                                     // 10

	// Copy 20 bytes over (includes the return address and fake param count).
	@emit HEAP         20                                                       // 12
	@emit LCTRL        4                                                        // 14
	@emit MOVS         20                                                       // 16
	@emit STOR.alt     ref(YSI_g_sNPSStack)                                     // 18

	// Call, and return to here to clean up the heap.
	@emit STACK        20                                                       // 20
	@emit CALL.abs     YSI_g_sNPSReplace                                        // 22

	// Put data (and return value) on the stack.
	@emit STACK        -20                                                      // 24
	@emit STACK        0                                                        // 26
	@emit PUSH.pri                                                              // 27

	// Copy from the heap.
	@emit LOAD.pri     ref(YSI_g_sNPSStack)                                     // 29
	@emit MOVS         20                                                       // 31

	// Restore the return address and `continue` stack.
	@emit POP.pri                                                               // 32
	@emit POP.alt                                                               // 33
	@emit STOR.alt     ref(YSI_g_sNPSStack)                                     // 35
	@emit HEAP         -20                                                      // 37

	// Return from this "function", with our fake parameters and return address.
	// We do this instead of using `SCTRL 6`, as is the normal way, to preserve
	// `pri` as the return value.
	@emit PROC                                                                  // 38
	@emit RETN                                                                  // 39

	if (type < 0)
	{
		// Missed this one apparently...
		@emit SYSREQ.C     -addr
		//@emit SYSREQ.pri

		// Returns to here.
		@emit PUSH.alt
		@emit PUSH         ref(YSI_g_sTempRet)
		@emit RETN
	}

	AsmEmitPadding(ctx);

	YSI_g_sNPSReplace = YSI_g_sNPSBaseCall; // Find
	YSI_g_sNPSBaseCall = addr;

	// Do a double return - exit the calling function as well as this function,
	// so that the next call is never actually made.
	#emit LOAD.S.pri   0
	#emit SCTRL        5
	#emit SCTRL        4
	// Clear faked parameter counts.   The outer public (maybe) expects lots of
	// parameters.  We call it with none.
	#emit ZERO.S       8
	#emit RETN
}

static stock Hooks_GenerateContinue(GLOBAL_TAG_TYPES:...)
{
	// This generates new code in a given location.  That location just happens
	// to entirely clobber `YHNPS_Push`, but we no longer need it.
	new
		ctx[AsmContext],
		ptr = _:addressof(Hooks_Continue_<>);

	AsmInitPtr(ctx, ptr + AMX_HEADER_COD, _:addressof(_@yH<>) - ptr);

	@emit PROC
	@emit ADDR.pri     8
	@emit PUSH.pri

	@emit LOAD.pri     ref(YSI_g_sNPSStack)
	@emit ADD.C        16
	@emit LOAD.I
	@emit MOVE.alt

	@emit Hooks_Continue_loop:

	@emit POP.pri
	@emit ADD.C        4
	@emit PUSH.pri

	// Check if `alt` is `0` (no parameters) or odd (move this parameter).
	@emit CONST.pri    1
	@emit SHR.C.alt    1
	@emit JGRTR.label  Hooks_Continue_done
	@emit AND
	@emit JZER.label   Hooks_Continue_loop

	// Adjust the given parameter.
	@emit LREF.S.pri   -4
	@emit LOAD.I
	@emit SREF.S.pri   -4
	@emit JUMP.label   Hooks_Continue_loop

	@emit Hooks_Continue_done:

	@emit POP.pri

	@emit LOAD.pri     ref(YSI_g_sNPSStack)
	@emit ADD.C        12
	@emit LOAD.I

	// `alt` is `0` here, thanks to the loop above.
	@emit JSLEQ.label  Hooks_Continue_native

	@emit MOVE.alt
	@emit POP.pri
	@emit SCTRL        5

	// Jump to the function.
	@emit MOVE.pri
	@emit LCTRL        8
	@emit SCTRL        6

	@emit Hooks_Continue_native:

	// Save the bottom of the stack.
	@emit POP.alt
	@emit STOR.alt     ref(YSI_g_sTempRet)
	@emit POP.alt

	@emit NEG
	@emit LCTRL        8
	@emit SCTRL        6

	//// Missed this one apparently...
	//AsmEmitSysreqPri(ctx);
	////@emit SYSREQ.pri
    //
	//// Returns to here.
	//@emit PUSH.alt
	//@emit PUSH         ref(YSI_g_sTempRet)
	//@emit RETN

	AsmEmitPadding(ctx);
}

