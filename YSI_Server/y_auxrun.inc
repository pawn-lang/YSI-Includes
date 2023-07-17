#endinput

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

// This is the source code of the filterscript embedded in an array avove.  Feel
// free to recompile it yourself and compare the bytes.  I use compiler version
// 3.10.11, settings don't matter since these next few lines override them all
// anyway.
#pragma compress 0
#pragma option -O1
#pragma option -d0
#pragma option -;+
#pragma option -(+
#pragma pack 0

#define SPACE_IN_MB (128)

#pragma option -a

// A few conveniences.
const
	cellbytes = cellbits / charbits,
	__hea = 2,
	__stk = 4;

// Allocate a lot of space for temporary storage.
#pragma dynamic SPACE_IN_MB * 1024 * 1024 / cellbytes

#if cellbits == 64
	const SHIFT = 3;
#elseif cellbits == 32
	const SHIFT = 2;
#else
	#error Unknown bit width.
#endif

forward N__(); // Native
forward C__(); // Clear
forward S__(const data[], length); // Set
forward G__(address); // Get

// PUT NO NATIVES ABOVE `TheNative`!

// This is just a placeholder.  We rewrite the name when generating the FS.
native TheNative() = numargs;
native bool:SetProperty(id, const name[], value, const string[]) = setproperty;

// Custom versions of natives which allow us to pass raw addresses.
native bool:MemCpy(dest, const src[], index, bytes, max) = memcpy;
native CallRemoteFunction(const function[], const specifier[], arg1, arg2);

// Reserve space in the header for a function name up to 63 characters.
static const
	// This is at DAT address 4, which is brilliant for locating it.
	NAME[64 char] = !"NehTvita\0\0\0e", // "TheNative" C-ified.
	EMPTY[4 char] = "",
	RESULT[] = !"R__";

static
	gAllocated = 0;

// A fake state to never trigger address naught detection in crashdetect.
public C__() <skip_address_naught>
{
	// Never call this!
	#emit HALT         13 // Invalid state.
}

public C__() <>
{
	gAllocated = 0;
}

#pragma naked
public N__()
{
	const
		args = 4 * cellbytes,
		clear = 5 * cellbytes;
	// The correct parameters are already on the stack.  Reuse them.
	#emit SYSREQ.C     TheNative

	// Save the return value.
	#emit PUSH.C       EMPTY
	#emit PUSH.pri
	#emit PUSH.C       NAME
	#emit PUSH.C       42
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
	// Subtract `cellbytes` to ensure we have space for the hidden length.
	if ((SPACE_IN_MB * 1024 * 1024 / cellbytes - 1) - gAllocated >= length)
	{
		new dest;
		// First, re-allocate the heap.
		#emit LCTRL        __hea
		#emit LOAD.alt     gAllocated
		#emit SHL.C.alt    SHIFT
		#emit ADD
		#emit STOR.S.pri   dest
		#emit LOAD.S.alt   length
		#emit SHL.C.alt    SHIFT
		#emit ADD
		#emit SCTRL        __hea
		
		// Save the length to the slot.
		#emit LOAD.S.alt   length
		#emit SREF.S.alt   dest

		// gAllocated is the return address.  Mostly...  The cell immediately prior
		// is used to store the length of this segment, hidden away.
		SetProperty(42, RESULT, gAllocated + 1, EMPTY);
		MemCpy(dest, data, 0, length * cellbytes, SPACE_IN_MB * 1024 * 1024 / cellbytes);
		gAllocated = gAllocated + length + 1;
	}
	else
	{
		SetProperty(42, RESULT, 0, EMPTY);
	}
}

public G__(address)
{
	// Re-allocate the heap.
	#emit HEAP         0
	#emit LOAD.pri     gAllocated
	#emit SHL.C.pri    SHIFT
	#emit ADD
	#emit SCTRL        __hea

	// Get our offset.
	#emit LOAD.S.pri   address
	#emit SHL.C.pri    SHIFT
	#emit ADD
	#emit STOR.S.pri   address
	// Use `CallRemoteFunction` to pass the data back.
	CallRemoteFunction(RESULT, !"ai", address, address - cellbytes); 
}

main()
{
	// Force the `NAME` data to be in the output.
	SetProperty(42, NAME, 0, EMPTY);
}

