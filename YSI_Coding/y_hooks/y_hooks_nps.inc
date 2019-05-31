#define HOOK_NATIVE__%0(%1)

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

#define continue(%0) Hooks_Continue_(func__,args__,%0)
#define args__,) args__)

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

