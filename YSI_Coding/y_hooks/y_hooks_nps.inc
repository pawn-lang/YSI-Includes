#define HOOK_NATIVE__%0(%1)

#define HOOK_PUBLIC__%0(%1) FUNC_PARSER(YH_NPS,ARR_MUL_CST:STR_CST_DEF:NUM_CST_DEF:REF_DEF:EXT_TAG:)(%0(%1))()()(1,0,(@H_y,@K_y))

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

#define YH_NPS_END(%0)%8$(,%5)(,%6)(%9,%4,(%7,%1)) %8$ \
	UNIQUE_FUNCTION<%7%0@...>(f__,a__,%5);                                     \
	UNIQUE_FUNCTION<%1%0@...>(%5);                                             \
	UNIQUE_FUNCTION<%1%0@...>(%5)                                              \
	{                                                                          \
		yH@_(%4);                                                              \
		%0(%6);                                                                \
	}                                                                          \
	UNIQUE_FUNCTION<%7%0@...>(f__,a__,%5)

#define YH_NPS_NUL(%0)%8$()()(%9,%4,(%7,%1)) %8$ \
	UNIQUE_FUNCTION<%7%0@...>(f__,a__);                                        \
	UNIQUE_FUNCTION<%1%0@...>();                                               \
	UNIQUE_FUNCTION<%1%0@...>()                                                \
	{                                                                          \
		yH@_(%4);                                                              \
		%0();                                                                  \
	}                                                                          \
	UNIQUE_FUNCTION<%7%0@...>(f__,a__)

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

#define continue(%0) Hooks_Continue_(f__,a__,%0)
#define a__,) a__)

stock yH@_(compressedFormat)
{
	// TODO:
	//
	// 1) Get the next function call address, being the original function.  This
	//    can also tell us if it is a native, public, or stock (which is a nice
	//    side-effect I wasn't planning).
	//
	// 2) Store the parameter format (`compressedFormat`).
	//
	// Do a double return - exit the calling function as well as this function,
	// so that the next call is never actually made.
	#emit POP.pri
	#emit SCTRL        5
	#emit SCTRL        4
	#emit RETN
}

stock Hooks_Continue_(target, args, ...)
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

