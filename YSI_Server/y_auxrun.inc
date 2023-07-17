static stock
	YSI_g_sByteCode[1000],
	YSI_g_sLastNative[64] = "-", // Invalid.
	YSI_g_sRequestedData = 0;

// This is the location in the file of the pointer to the native we are
// replacing.  It should be the first native, so could be found at `*0x24 + 4`,
// i.e. one cell after the start of the native functions block.
FINAL__ NATIVE_POINTER_OFFSET = YSI_g_sByteCode[9] / cellbytes + 1;

// The data array we write the new name in to.  This is found strictly at the
// start of DAT, so is at `*0x10`.
FINAL__ NATIVE_NAME_OFFSET = YSI_g_sByteCode[4];

// The original name, for when servers restart with different plugins or
// components.  Always re-write the file out when the server starts, to ensure
// this gets reset.
FINAL__ NATIVE_NAME_RESET = YSI_g_sByteCode[NATIVE_POINTER_OFFSET];

static stock bool:YAR_DumpFile()
{
	new
		File:f = fopen("yar.amx", io_write);
	if (f)
	{
		fblockwrite(f, YSI_g_sByteCode);
		fclose(f);
		return true;
	}
	return false;
}

static stock YAR_WriteNative(const name[])
{
	new
		pack[64 char],
		i = -1,
		o = NATIVE_NAME_OFFSET / cellbytes;
	strpack(pack, name);
	do
	{
		++i;
		YSI_g_sByteCode[o] = swapchars(pack[i]);
		++o;
	}
	while (!Cell_HasZeroByte(pack[i]));
}

stock bool:YAR_CreateFileWithNative(const name[])
{
	if (strcmp(name, YSI_g_sLastNative) == 0)
	{
		// The script is already loaded with this native.  Can just call it.
		return true;
	}
	
	// Rewrite the bytecode to include the name of the new native.
	YSI_g_sByteCode[NATIVE_POINTER_OFFSET] = NATIVE_NAME_OFFSET;
	YAR_WriteNative(name);

	if (!YAR_DumpFile())
	{
		return false;
	}

	// Reload the FS, and test that it did load.  If it didn't the native we
	// want to use probably doesn't exist.
	deleteproperty(42, "R__");
	SendRconCommand("reloadfs ../scriptfiles/yar");
	if (existproperty(42, "R__"))
	{
		// Succeeded, the new native must exist.
		// Cache it.
		StrCpy(YSI_g_sLastNative, name);
		return true;
	}

	// Reset to the previous version (known safe).
	YAR_WriteNative(YSI_g_sLastNative);
	if (YAR_DumpFile())
	{
		SendRconCommand("loadfs ../scriptfiles/yar");
	}

	return false;
}

public R__(const data[], length)
{
	if (YSI_g_sRequestedData)
	{
		// Save it.
		YSI_g_sRequestedData = 0;
	}
}

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
// 3.10.11; settings don't matter since these next few lines override them all
// anyway.
#pragma compress 0
#pragma option -O1
#pragma option -d0
#pragma option -;+
#pragma option -(+
#pragma pack 0

#define SPACE_IN_MB (128)

//#pragma option -a

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

forward OnFilterScriptInit();
forward OnRconCommand(const cmd[]);
forward OnClientCheckResponse(playerid, actionid, memaddr, retndata);

forward N__(); // Native
forward C__(); // Clear
forward S__(const data[], length); // Set
forward G__(address); // Get

// PUT NO NATIVES ABOVE `TheNative`!
// This is just a placeholder.  We rewrite the name when generating the FS.
native TheNative() = heapspace;

// Custom versions of natives, some of which allow us to pass raw addresses.
native bool:SetProperty(id, const name[], value, const string[]) = setproperty;
native StrCmp(const string1[], const string2[], bool:ignorecase, length) = strcmp;
native bool:MemCpy(dest, const src[], index, bytes, max) = memcpy;
native CallResponseFunction(const function[], const specifier[], &playerid, &actionid, &memaddr, &retndata) = CallRemoteFunction;
native CallResultFunction(const function[], const specifier[], data, length) = CallRemoteFunction;

// Reserve space in the header for a function name up to 63 characters.
new const
	// This is at DAT address 0, which is brilliant for locating it.
	NATIVE[64 char] = !"paehcaps\0\0\0e", // "heapspace" C-ified.
	EMPTY[4 char] = "",
	RESULT[] = !"R__",
	// Use the same string for everything, so we only need one.  And pack it.
	FIXES_RESPONSE[] = !"FIXES_OnClientCheckResponse";

new
	gAvailable = SPACE_IN_MB * 1024 * 1024 / cellbytes,
	gAllocated = 0;

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
	// The correct parameters are already on the stack.  Reuse them.
	#emit SYSREQ.C     TheNative

	// Save the return value.
	#emit PUSH.C       EMPTY
	#emit PUSH.pri
	#emit PUSH.C       RESULT
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
	// Strictly `>` to ensure we have space for the hidden length.
	if (gAvailable > length)
	{
		gAvailable = gAvailable - length - 1;
		SetProperty(42, RESULT, gAllocated, EMPTY);

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
		MemCpy(dest, data, 0, length, SPACE_IN_MB * 1024 * 1024 / cellbytes);
	}
	else
	{
		SetProperty(42, RESULT, 0, EMPTY);
	}
}

public G__(address)
{
	// Re-allocate the heap.
	#emit LOAD.pri     gAllocated
	#emit SCTRL        __hea

	// Use `CallRemoteFunction` to pass the data back.
	CallResultFunction(RESULT, !"ai", address + cellbytes, address); 
}

public OnFilterScriptInit()
{
	// Force the `NATIVE` data to be in the output.
	SetProperty(42, RESULT, 0, NATIVE);
	#emit LCTRL        __hea
	#emit STOR.pri     gAllocated
}

// This callback just needs to exist in one filterscript.
public OnRconCommand(const cmd[])
{
	// The smallest I could make the assembly without `#emit`.
	if (StrCmp(cmd, FIXES_RESPONSE, true, cellmax) == 0)
	{
		// We used to use padding
		return !SetProperty(27, FIXES_RESPONSE, 27, EMPTY);
	}
	return 0;
}

// This callback needs to invoke a different callback in GMs.
public OnClientCheckResponse(playerid, actionid, memaddr, retndata)
{
	// Invoke the global callback.
	return CallResponseFunction(FIXES_RESPONSE, !"iiii", playerid, actionid, memaddr, retndata);
}

