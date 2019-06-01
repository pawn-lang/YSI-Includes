#define HOOK_NATIVE__%0(%1)

#define HOOK_PUBLIC__%0(%1) FUNC_PARSER(YH_NPS,ARR_MUL_CST:STR_CST_DEF:NUM_CST_DEF:REF_DEF:EXT_TAG:)(%0(%1))()()(1,0,(@H_y,@K_y))
#define HOOK_NATIVE__ HOOK_PUBLIC__

#define @H_y%0\32; @H_y // hook public
#define @K_y%0\32; @K_y // public extras

// Arrays.
//
// %0  = `const`
// %1  = Tag (unused)
// %2  = Name
// %4+ = Dims
#define YH_NPS_ARR(%0,%1,%2,%4)%8$ YH_NPS_BYREF(%0%2[%4],%2)%8$
#define YH_NPS_ARR_ARR(%0,%1,%2,%4,%5)%8$ YH_NPS_BYREF(%0%2[%4][%5],%2)%8$
#define YH_NPS_ARR_ARR_ARR(%0,%1,%2,%4,%5,%6)%8$ YH_NPS_BYREF(%0%2[%4][%5][%6],%2)%8$

// Strings.
//
// %0  = `const`
// %1  = Tag (unused)
// %2  = Name
// %4  = Size
// %3  = Default (unused)
#define YH_NPS_STR(%0,%1,%2,%4)%8$ YH_NPS_BYREF(%0%2[%4],%2)%8$
#define YH_NPS_STR_DEF(%0,%1,%2,%4,%3)%8$ YH_NPS_BYREF(%0%2[%4],%2)%8$

// Varargs.
//
// %0  = `const` (unused)
// %1  = Tag
// %2  = Name (unused)
// %5  = Prototype parameters
// %6  = Call parameters
#define YH_NPS_EXT(%0,%1,%2)%8$(%5)(%6)(%9,%4,%7) %8$(%5,%1...)(%6)(%9,%4,%7)

// References.
//
// %0  = `const` (unused)
// %1  = Tag (unused)
// %2  = Name
// %3  = Default (unused)
#define YH_NPS_REF(%0,%1,%2)%8$ YH_NPS_BYREF(&%2,%2)%8$
#define YH_NPS_REF_DEF(%0,%1,%2,%3)%8$ YH_NPS_BYREF(&%2,%2)%8$

// Variables.
//
// %0  = `const`
// %1  = Tag (unused)
// %2  = Name
// %3  = Default (unused)
#define YH_NPS_NUM(%0,%1,%2)%8$ YH_NPS_BYVAL(%0%2,%2)%8$
#define YH_NPS_NUM_DEF(%0,%1,%2,%3)%8$ YH_NPS_BYVAL(%0%2,%2)%8$

// Generate the parameter descriptions.
//
// %0  = Name in prototype
// %1  = Name in call
// %5  = Prototype parameters
// %6  = Call parameters
// %9  = Shift
// %4  = Existing values
// %7  = Prefix
#define YH_NPS_BYREF(%0,%1)%8$(%5)(%6)(%9,%4,%7) %8$(%5,%0)(%6,%1)(%9+1,%4,%7)
#define YH_NPS_BYVAL(%0,%1)%8$(%5)(%6)(%9,%4,%7) %8$(%5,%0)(%6,%1)(%9+1,1<<%9|%4,%7)

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
#define YH_NPS_END(%0)%8$(,%5)(,%6)(%9,%4,(%7,%1)) %8$_@Ky<%7%0>(%5);_@Ky<%1%0>(%5);_@Ky<%1%0>(%5)_@Ky(%4),%0(%6),_@yK();_@Ky<%7%0>(%5)
#define YH_NPS_NUL(%0)%8$()() YH_NPS_END(%0)%8$(,)(,)

// Helper macro to generate the unique function name without bloating the
// generated code multiple times.
#define _@Ky<%0> UNIQUE_FUNCTION<%0@...>

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

// TODO: Read this data directly in `Hooks_Continue_`.
#define continue(%0) Hooks_Continue_(AMX_Read(YSI_g_sNPSStack),AMX_Read(YSI_g_sNPSStack+cellbytes),%0)
#define AMX_Read(%0),) AMX_Read(%0))

stock _@yK(&a = 0, &b = 0, &c = 0)
{
	#pragma unused a, b, c
	// This function does nothing.  It merely exists to be called - an operation
	// which takes two cells, thus reserving two cells in the assembly.
}

new
	YSI_g_sNPSTrampoline,
	YSI_g_sNPSReplace,
	YSI_g_sNPSStack;

stock _@Ky(compressedFormat)
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
	switch (type)
	{
	case 1:
	{
		// Normal function call.
		printf("addr: %08x", addr);
	}
	case 2:
	{
		// Native function call.
		printf("ID: %d", addr);
		addr = -addr;
	}
	default:
	{
		// Bad.
		printf("no");
	}
	}

	AsmInitPtr(ctx, YSI_g_sNPSTrampoline + AMX_HEADER_COD, YSI_g_sNPSReplace - YSI_g_sNPSTrampoline);
	// Forward the function, storing the chain data in the heap.   Note that no
	// `PROC` is added to this new trambopoline:
	//
	//   https://www.youtube.com/watch?v=geHqnV4Mk_4
	//

	// Build the structure in the stack first.
	@emit PUSH         ref(YSI_g_sNPSStack)
	@emit PUSH.C       compressedFormat
	@emit PUSH.C       addr

	// Copy 16 bytes over (includes the return address).
	@emit HEAP         8
	@emit LCTRL        4
	@emit MOVS         8
	@emit STOR.alt     ref(YSI_g_sNPSStack)

	// Call, and return to here to clean up the heap.
	@emit STACK        16
	@emit CALL.abs     YSI_g_sNPSReplace







	@emit LOAD.pri     ref(YSI_g_sNPSStack)
	@emit STACK        -16
	@emit STACK        0
	@emit MOVS         16
	@emit STACK        8
	@emit POP.pri
	@emit STOR.pri     ref(YSI_g_sNPSStack)
	@emit POP.pri
	@emit HEAP         -16
	@emit SCTRL        6

//	// Pop the stack.
//	@emit LCTRL        2
//	@emit ADD.C        -8
//	@emit LOAD.I
//	@emit STOR.pri     ref(YSI_g_sNPSStack)
//
//	// Get the return address.
//	@emit LCTRL        2
//	@emit ADD.C        -4
//	@emit LOAD.I
//	@emit HEAP         -16
//	@emit SCTRL        6

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

stock Hooks_Continue_(target, args, GLOBAL_TAG_TYPES:...)
{
	static addr;
	#emit ADDR.pri     16
	#emit STOR.pri     addr

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

	// `CALL` or `SYSREQ`.
	if (target > 0)
	{
		// Subtract 8 from the parameter count.
		#emit LOAD.S.pri   8
		#emit ADD.C        0xFFFFFFF8 // -8
		#emit STOR.S.pri   16

		// Reset the current frame.
		#emit POP.pri
		#emit SCTRL        5

		// Get the target, while moving the return address.
		#emit POP.pri
		#emit POP.alt
		#emit SWAP.pri
		#emit LCTRL        8
		#emit SCTRL        6
	}
	else
	{
		//target = -target;
		static FRM, RET;

		// Save the bottom of the stack.
		#emit POP.pri
		#emit STOR.pri     FRM

		#emit POP.pri
		#emit STOR.pri     RET

		// Subtract 8 args.
		#emit POP.pri
		#emit ADD.C        0xFFFFFFF8 // -8

		// Get the native (negatively), and store the new args.
		#emit POP.alt
		#emit SWAP.pri

		// `pri` is `0` here, because it is the value of `args`, which was
		// driven to 0 in the code above.  Thus `pri = -alt` becomes just:
		#emit SUB

		#emit SYSREQ.pri

		// Returns to here.
		#emit PUSH         RET
		#emit PUSH         FRM
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

