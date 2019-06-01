#define HOOK_NATIVE__%0(%1)

#define HOOK_STOCK__%0(%1) FUNC_PARSER(YHNPS,ARR_MUL_CST:STR_CST_DEF:NUM_CST_DEF:REF_DEF:EXT_TAG:)(%0(%1))()()(1,0)
#define HOOK_NATIVE__ HOOK_STOCK__

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
#define YHNPS_END(%0)%8$(,%5)(,%6)(%9,%4) %8$YHNPS_U0<%0>(%5);YHNPS_U1<%0>(%5);YHNPS_U1<%0>(%5)_yH@(%4),%0(%6),_@yH();YHNPS_U0<%0>(%5)
#define YHNPS_NUL(%0)%8$()() YHNPS_END(%0)%8$(,)(,)

// Helper macro to generate the unique function name without bloating the
// generated code multiple times.
#define YHNPS_U0<%1> UNIQUE_FUNCTION<@Hy_%1@...>
#define YHNPS_U1<%1> UNIQUE_FUNCTION<@_Hy%1@...>

#define _yH@(%0),%1@%2(%3),_@yH(); _yH@(%0),%1(%3),_@yH();

new
	YSI_g_sNPSBaseCall,
	YSI_g_sNPSTrampoline,
	YSI_g_sNPSReplace,
	YSI_g_sNPSHeap,
	YSI_g_sNPSStack;

static stock YHNPS_Find(heap, end, value, ptr)
{
	new
		start = 0,
		mid;
	--end;
	while (start <= end)
	{
		mid = (start + end) / 2;
		new diff = AMX_Read(heap + mid * 8) - value;
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
			return mid;
		}
	}
	return -1;
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
			diff = AMX_Read(heap + mid * 8) - value;
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
		printf("Inserting %d at index %d", value, count);
		// Shift all the greater values up.
		AMX_Write(heap + count * 8, value);
		AMX_Write(heap + count * 8 + 4, ptr);
	}
	else
	{
		printf("Inserting %d at index %d", value, mid);
		// Shift all the greater values up.
		rawMemcpy(heap + mid * 8 + 8, heap + mid * 8, (count - mid) * 8);
		AMX_Write(heap + mid * 8, value);
		AMX_Write(heap + mid * 8 + 4, ptr);
	}
}

static stock YHNPS_Push(heap, allocated, &nativeCount, &stockCount)
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
	if (YSI_g_sNPSBaseCall < 0)
	{
		printf("Insert native");
		YHNPS_Insert(heap, nativeCount, -YSI_g_sNPSBaseCall, YSI_g_sNPSTrampoline);
		YHNPS_Insert(heap + allocated * 16, nativeCount, GetNativeAddressFromIndex(-YSI_g_sNPSBaseCall), YSI_g_sNPSTrampoline);
		++nativeCount;
	}
	else
	{
		printf("Insert stock");
		YHNPS_Insert(heap + allocated * 8, stockCount, YSI_g_sNPSBaseCall, YSI_g_sNPSTrampoline);
		++stockCount;
	}
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
		entry,
		pn[32 char],
		name[32 char],
		idx1,
		idx2;
	YSI_g_sNPSStack = cellmin;
	// Needs to be split over multiple lines because macros (`_A`).
	while (
		(idx1 = AMX_GetPublicEntryPrefix(idx1, entry, _A<@Hy_>))
		&&
		(idx2 = AMX_GetPublicPointerPrefix(idx2, YSI_g_sNPSTrampoline, _A<@_Hy>))
	)
	{
		YSI_g_sNPSReplace = AMX_Read(entry);
		AMX_ReadString(AMX_Read(entry + 4) + AMX_BASE_ADDRESS, name);
		name{strfind(name, "@", .pos = 4)} = '\0';
		if (YSI_g_sNPSStack == cellmin)
		{
			// New hook.
			memcpy(pn, name[1], 0, 28, 32 char);
		}
		else if (strcmp(name[1], pn))
		{
			YHNPS_Push(heap, allocated, nativeCount, stockCount);
			// `YSI_g_sNPSStack` points to the start of the last chain.  Store
			// it.
			// New hook.
			memcpy(pn, name[1], 0, 28, 32 char);
			YSI_g_sNPSStack = cellmin;
		}
		@.YSI_g_sNPSTrampoline();
		YSI_g_sNPSStack = YSI_g_sNPSTrampoline;
	}
	if (YSI_g_sNPSStack != cellmin)
	{
		// Store the final chain.
		YHNPS_Push(heap, allocated, nativeCount, stockCount);
	}

	// Step 2:
	//
	//   Iterate over the entire mode and replace all relevant calls.
	//

	// `SYSREQ.C` is always followed by `STACK`, except with `#emit` usage.  We
	// need to change the pair in to a single `CALL`.  Don't forget `SYSREQ.D`.

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

stock _@yH(&a = 0, &b = 0, &c = 0, &d = 0, &e = 0, &f = 0)
{
	#pragma unused a, b, c, d, e, f
	// This function does nothing.  It merely exists to reserve space for
	// codegen.  According to my experiments, just 4 parameters are enough to
	// reserve enough space (exactly) for the code generated below, even for a
	// function with no parameters.  But better to be safe than sorry.
}

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
			addr = DisasmGetOperand(dctx);
			type = 2;
			break;
		}
		case OP_SYSREQ_D:
		{
			type = 3;
			break;
		}
		}
	}
	if (type == 2)
	{
		// Native function call.
		addr = -addr;
	}

	AsmInitPtr(ctx, YSI_g_sNPSTrampoline + AMX_HEADER_COD, YSI_g_sNPSReplace - YSI_g_sNPSTrampoline);
	// Forward the function, storing the chain data in the heap.   Note that no
	// `PROC` is added to this new trambopoline:
	//
	//   https://www.youtube.com/watch?v=geHqnV4Mk_4
	//

	// Build the structure in the stack first.
	@emit POP.pri
	@emit PUSH.C       compressedFormat

	// Chain the functions.
	if (YSI_g_sNPSStack == cellmin)
	{
		@emit PUSH.C       addr
		YSI_g_sNPSBaseCall = addr;
	}
	else
	{
		@emit PUSH.C       YSI_g_sNPSStack
	}

	@emit PUSH.C       8
	@emit PUSH.pri     // Save the return address again.
	@emit PUSH         ref(YSI_g_sNPSStack)

	// Copy 20 bytes over (includes the return address and fake param count).
	@emit HEAP         20
	@emit LCTRL        4
	@emit MOVS         20
	@emit STOR.alt     ref(YSI_g_sNPSStack)

	// Call, and return to here to clean up the heap.
	@emit STACK        20
	@emit CALL.abs     YSI_g_sNPSReplace

	// Put data (and return value) on the stack.
	@emit STACK        -20
	@emit STACK        0
	@emit PUSH.pri

	// Copy from the heap.
	@emit LOAD.pri     ref(YSI_g_sNPSStack)
	@emit MOVS         20

	// Restore the return address and `continue` stack.
	@emit POP.pri
	@emit POP.alt
	@emit STOR.alt     ref(YSI_g_sNPSStack)
	@emit HEAP         -20

	// Return from this "function", with our fake parameters and return address.
	// We do this instead of using `SCTRL 6`, as is the normal way, to preserve
	// `pri` as the return value.
	@emit PROC
	@emit RETN

	AsmEmitPadding(ctx);

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

stock Hooks_Continue_(GLOBAL_TAG_TYPES:...)
{
	static
		addr,
		args;

	#emit ADDR.pri     8
	#emit STOR.pri     addr

	#emit LOAD.pri     YSI_g_sNPSStack
	#emit ADD.C        16
	#emit LOAD.I
	#emit STOR.pri     args

	while ((args >>>= 1))
	{
		addr += 4;
		if (args & 1)
		{
			#emit LREF.pri     addr
			#emit LOAD.I
			#emit SREF.pri     addr
		}
	}
	{}

	#emit LOAD.pri     YSI_g_sNPSStack
	#emit ADD.C        12
	#emit LOAD.I
	#emit STOR.pri     addr

	// `CALL` or `SYSREQ`.
	if (addr > 0)
	{
		// Reset the current frame.
		#emit POP.pri
		#emit SCTRL        5

		// Jump to the function.
		#emit LOAD.pri     addr
		#emit LCTRL        8
		#emit SCTRL        6
	}
	else
	{
		// Save the bottom of the stack.
		#emit POP.alt
		#emit LOAD.pri     addr
		#emit STOR.alt     addr
		#emit POP.alt

		#emit NEG
		#emit SYSREQ.pri

		// Returns to here.
		#emit PUSH.alt
		#emit PUSH         addr
		#emit RETN
	}

	return 0;

/*
	Fast target jump code (for v0.2)

	// Replace calls to this function from:

//	#emit PUSH.S       args__
//	#emit PUSH.S       func__
//	#emit PUSH.C       n
//	#emit CALL         FastJump

	// To:

//	#emit CONST.alt    ARGS
//	#emit CONST.pri    FUNC + 4
//	#emit PUSH.C       n - 8
//	#emit CALL         FastJump

	// If `FUNC` is `0`:

//	#emit NOP
//	#emit NOP
//	#emit NOP
//	#emit NOP
//	#emit STACK        n - 8
//	#emit CONST.pri    0

	// Function:

	#emit PROC                 // Auto-generated.

//	#emit JZER         FastJump_retn

	#emit PUSH.pri             // Store the function to call.
	// Get the start of the normal arguments.
	#emit ADDR.pri     8
	#emit PUSH.pri

FastJump_loop:
		#emit POP.pri
		#emit ADD.C        4
		#emit PUSH.pri

		// Check if `alt` is `0` (no parameters) or odd (move this parameter).
		#emit CONST.pri    1
		#emit SHR.C.alt    1
		#emit JGRTR        FastJump_done
		#emit AND
		#emit JZER         FastJump_loop

		// Adjust the given parameter.
		#emit LREF.S.pri   -8
		#emit LOAD.I
		#emit SREF.S.pri   -8
		#emit JUMP         FastJump_loop

FastJump_done:
	#emit POP.pri
	#emit POP.pri
	#emit SCTRL        6

//FastJump_retn:
//	#emit RETN

*/
}

