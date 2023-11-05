/*
                                                                                                                 
    88888888888  88  88                                                                     88                       
    88           ""  88    ,d                                                               ""                ,d     
    88               88    88                                                                                 88     
    88aaaaa      88  88  MM88MMM  ,adPPYba,  8b,dPPYba,  ,adPPYba,   ,adPPYba,  8b,dPPYba,  88  8b,dPPYba,  MM88MMM  
    88"""""      88  88    88    a8P_____88  88P'   "Y8  I8[    ""  a8"     ""  88P'   "Y8  88  88P'    "8a   88     
    88           88  88    88    8PP"""""""  88           `"Y8ba,   8b          88          88  88       d8   88     
    88           88  88    88,   "8b,   ,aa  88          aa    ]8I  "8a,   ,aa  88          88  88b,   ,a8"   88,    
    88           88  88    "Y888  `"Ybbd8"'  88          `"YbbdP"'   `"Ybbd8"'  88          88  88`YbbdP"'    "Y888  
                                                                                                88                   
                                                                                                88                   

*/

//#pragma option -a
#define SPACE_IN_MB (128)

// This is the source code of the filterscript embedded in an array in
// `y_rconfix`.  Feel free to recompile it yourself and compare the bytes.  I
// use compiler version 3.10.11; settings don't matter since these next few
// lines override them all anyway.

#pragma compress 0
#pragma option -O1
#pragma option -d0
#pragma option -;+
#pragma option -(+
#pragma option -Z-
#pragma pack 0

#if !defined __PawnBuild
	#error Requires compiler version 3.10.11.
#endif
#if __PawnBuild != 11
	#error Requires compiler version 3.10.11.
#endif

// A few conveniences.
const
	#if cellbits == 64
		SHIFT = 3,
	#elseif cellbits == 32
		SHIFT = 2,
	#else
		#error Unknown bit width.
	#endif
	cellbytes = cellbits / charbits,
	__dat = 1,
	__hea = 2,
	__stk = 4;

// Allocate a lot of space for temporary storage.
#pragma dynamic SPACE_IN_MB * 1024 * 1024 / cellbytes

#define open.mp __OPEN_MP_VERSION

forward OnFilterScriptInit();
forward OnRconCommand(const cmd[]);
forward OnClientCheckResponse(playerid, actionid, memaddr, retndata);

forward N__(); // Native
forward C__(); // Clear
forward S__(const data[], length); // Set
forward G__(address); // Get

// PUT NO NATIVES ABOVE HERE!
// This is just a placeholder.  We rewrite the name when generating the FS.
native YSI();

// Custom versions of natives, some of which allow us to pass raw addresses.
native bool:SetProperty(id, const name[], value, const string[]) = setproperty;
native StringCompare(const string1[], const string2[], bool:ignorecase, length) = strcmp;
native bool:MemoryCopy(dest, const src[], index, bytes, max) = memcpy;

native CallRemoteFunction(const function[], const specifier[], ...);

// Reserve space in the header for a function name up to 63 characters.
new const
	// This is at DAT address 0, which is brilliant for locating it.  It is also
	// dead space before the native name is written to it, so put something in.
	NATIVE[64 char] = !" ISYixuArailuR ymitn( ,e2 )c 320xelA_Y\" sseLoC \"\0.el",
	RESULT_A[] = !"R__",
	RESULT_B[] = !"Q__",
	AI[] = !"ai",
	IIII[] = !"iiii",
	// Use the same string for everything, so we only need one.  And pack it.
	FIXES_RESPONSE[] = !"FIXES_OnClientCheckResponse";

new
	gAvailable = SPACE_IN_MB * 1024 * 1024 / cellbytes,
	// This might be a constant...
	gAllocated = 0;

new const
	// The master ID.  Not of this script, but of the script that generated this
	// code.  Use `42` by default as that is what an earlier version of this
	// code always returned, so this remains backwards-compatible.  It is also
	// not a power of two, therefore not a valid Master ID.
	_@ = 42,
	// This is written by our loader, NOT the server.  We do this just to save
	// space in the header from not needing to make this `public`.  To
	// facilitate this, it is the very last thing in the file.
	open.mp = 0;

public C__()
{
	#emit LCTRL        __hea
	#emit STOR.pri     gAllocated
	gAvailable = SPACE_IN_MB * 1024 * 1024 / cellbytes;
}

#pragma naked
public N__()
{
	const
		args = 4 * cellbytes,
		clear = 5 * cellbytes;
	
	// Remove the return address.
	#emit POP.pri
	
	// The correct parameters are already on the stack.  Reuse them.
	#emit SYSREQ.C     YSI

	// Save the return value.
	#emit PUSH.C       NATIVE
	#emit PUSH.pri
	#emit PUSH.C       RESULT_A
	#emit PUSH.C       27
	#emit PUSH.C       args
	#emit SYSREQ.C     SetProperty

	// Clear the stack.  Getting the stack earlier isn't more efficient.
	#emit STACK        clear
	#emit POP.alt
	#emit LCTRL        __stk
	#emit ADD
	#emit SCTRL        __stk
	// This is a public entry point, so the return address is always `0`.  Not that
	// it matters, because we can just call `HALT` ourselves.  So we make it naked.
	#emit HALT         0
}

public S__(const data[], length)
{
	// Strictly `>` to ensure we have space for the hidden length.
	if (gAvailable > length)
	{
		gAvailable = gAvailable - length - 1;
		SetProperty(27, RESULT_A, gAllocated, NATIVE);

		new dest = 0;
		// First, re-allocate the heap.
		#emit LOAD.pri     gAllocated
		#emit ADD.C        cellbytes
		#emit STOR.S.pri   dest
		#emit LOAD.S.alt   length
		#emit SHL.C.alt    SHIFT
		#emit ADD
		#emit SCTRL        __hea

		// Save the length to the slot.
		#emit LOAD.S.alt   length
		#emit SREF.alt     gAllocated
		#emit STOR.pri     gAllocated

		// gAllocated is the return address.  The first cell is the length.
		MemoryCopy(dest, data, 0, length, SPACE_IN_MB * 1024 * 1024 / cellbytes);
	}
	else
	{
		// We don't need the last parameter, so it doesn't matter what it is.
		// Save some space by re-using something irrelevant.
		SetProperty(27, RESULT_A, 0, NATIVE);
	}
}

public G__(address)
{
	const
		args = 4 * cellbytes,
		clear = 5 * cellbytes;
	// Re-allocate the heap.
	#emit LOAD.pri     gAllocated
	#emit SCTRL        __hea

	// Push raw addresses to `CallRemoteFunction`.
	#emit LOAD.S.pri   address
	#emit PUSH.pri
	#emit ADD.C        cellbytes
	#emit PUSH.pri
	#emit PUSH.C       AI
	#emit PUSH.C       RESULT_A
	#emit PUSH.C       args
	#emit SYSREQ.C     CallRemoteFunction
	#emit STACK        clear
}

public OnFilterScriptInit()
{
	{
		new
			addr;
		// The first half of the address.
		#emit LCTRL        __dat
		#emit NEG
		// Get the pointer to the natives table.
		#emit ADD.C        36 // NOT 9 * cellbytes, the header doesn't change.
		#emit STOR.S.pri   addr
		#emit LREF.S.alt   addr
		#emit LCTRL        __dat
		#emit SUB.alt
		// Load the first cell of the first native.
		#emit STOR.S.pri   addr
		#emit LREF.S.pri   addr
		#emit STOR.S.pri   addr
		SetProperty(27, RESULT_A, addr, RESULT_A);
		// The second half of the address.
		#emit LCTRL        __dat
		#emit NEG
		#emit ADD.C        36 // NOT 9 * cellbytes, the header doesn't change.
		#emit STOR.S.pri   addr
		#emit LREF.S.alt   addr
		#emit LCTRL        __dat
		#emit SUB.alt
		// Load the second cell of the first native.
		#emit ADD.C        cellbytes
		#emit STOR.S.pri   addr
		#emit LREF.S.pri   addr
		#emit STOR.S.pri   addr
		SetProperty(27, RESULT_B, addr, RESULT_B);
	}
	// Clear the local stack.
	{}
	#emit LCTRL        __hea
	#emit STOR.pri     gAllocated
}

// This callback just needs to exist in one filterscript.
public OnRconCommand(const cmd[])
{
	// The smallest I could make the assembly without `#emit`.
	if (StringCompare(cmd, FIXES_RESPONSE, true, cellmax) == 0)
	{
		// We used to use padding, but now the FS isn't packed (unfortunatley).
		return !SetProperty(27, FIXES_RESPONSE, _@, NATIVE);
	}
	return 0;
}

// This callback needs to invoke a different callback in GMs.
public OnClientCheckResponse(playerid, actionid, memaddr, retndata)
{
	if (open.mp)
	{
		return 0;
	}
	// Invoke the global callback.
	return CallRemoteFunction(FIXES_RESPONSE, IIII, playerid, actionid, memaddr, retndata);
}

