#define __asm(%0,%1,%2,%3) (((0x%3) << 24) | ((0x%2) << 16) | (0x%1 << 8) | (0x%0))

static
	YSI_g_sByteCode[1000] = {
		__asm(00,00,05,20), __asm(08,08,F1,E0), __asm(00,08,00,10), __asm(00,00,01,14),
		__asm(00,00,04,A8), __asm(00,00,05,20), __asm(08,00,05,20), __asm(FF,FF,FF,FF),
		__asm(00,00,00,38), __asm(00,00,00,70), __asm(00,00,00,98), __asm(00,00,00,98),
		__asm(00,00,00,98), __asm(00,00,00,98), __asm(00,00,00,08), __asm(00,00,00,9A),
		__asm(00,00,01,F0), __asm(00,00,00,9E), __asm(00,00,00,34), __asm(00,00,00,A2),
		__asm(00,00,03,2C), __asm(00,00,00,A6), __asm(00,00,02,4C), __asm(00,00,00,BC),
		__asm(00,00,02,A0), __asm(00,00,00,CF), __asm(00,00,00,90), __asm(00,00,00,DD),
		__asm(00,00,00,00), __asm(00,00,00,E1), __asm(00,00,00,00), __asm(00,00,00,E5),
		__asm(00,00,00,00), __asm(00,00,00,F1), __asm(00,00,00,00), __asm(00,00,00,F8),
		__asm(00,00,00,00), __asm(00,00,01,0B), __asm(5F,43,00,15), __asm(5F,47,00,5F),
		__asm(5F,4E,00,5F), __asm(6E,4F,00,5F), __asm(65,69,6C,43), __asm(68,43,74,6E),
		__asm(52,6B,63,65), __asm(6F,70,73,65), __asm(00,65,73,6E), __asm(69,46,6E,4F),
		__asm(72,65,74,6C), __asm(69,72,63,53), __asm(6E,49,74,70), __asm(4F,00,74,69),
		__asm(6F,63,52,6E), __asm(6D,6F,43,6E), __asm(64,6E,61,6D), __asm(5F,5F,53,00),
		__asm(49,53,59,00), __asm(74,65,73,00), __asm(70,6F,72,70), __asm(79,74,72,65),
		__asm(6D,65,6D,00), __asm(00,79,70,63), __asm(6C,6C,61,43), __asm(6F,6D,65,52),
		__asm(75,46,65,74), __asm(69,74,63,6E), __asm(73,00,6E,6F), __asm(6D,63,72,74),
		__asm(00,00,00,70), __asm(00,00,00,78), __asm(00,00,00,00), __asm(00,00,00,2E),
		__asm(00,00,00,1F), __asm(00,00,00,02), __asm(00,00,00,0F), __asm(00,00,00,70),
		__asm(00,00,00,0B), __asm(02,00,00,00), __asm(00,00,00,0F), __asm(00,00,00,6C),
		__asm(00,00,00,59), __asm(00,00,00,30), __asm(00,00,00,7B), __asm(00,00,00,00),
		__asm(00,00,00,27), __asm(00,00,00,00), __asm(00,00,00,24), __asm(00,00,00,27),
		__asm(00,00,00,40), __asm(00,00,00,27), __asm(00,00,00,1B), __asm(00,00,00,27),
		__asm(00,00,00,10), __asm(00,00,00,7B), __asm(00,00,00,01), __asm(00,00,00,2C),
		__asm(00,00,00,14), __asm(00,00,00,2B), __asm(00,00,00,1F), __asm(00,00,00,04),
		__asm(00,00,00,4E), __asm(00,00,00,20), __asm(00,00,00,04), __asm(00,00,00,78),
		__asm(00,00,00,00), __asm(00,00,00,2E), __asm(00,00,00,01), __asm(00,00,00,6C),
		__asm(00,00,00,04), __asm(00,00,00,10), __asm(00,00,00,3E), __asm(00,00,01,B0),
		__asm(00,00,00,03), __asm(00,00,00,10), __asm(00,00,00,02), __asm(00,00,00,6C),
		__asm(00,00,00,50), __asm(00,00,00,0C), __asm(00,00,00,01), __asm(00,00,00,4F),
		__asm(00,00,00,0F), __asm(00,00,00,6C), __asm(00,00,00,27), __asm(00,00,00,00),
		__asm(00,00,00,28), __asm(00,00,00,70), __asm(00,00,00,27), __asm(00,00,00,40),
		__asm(00,00,00,27), __asm(00,00,00,1B), __asm(00,00,00,27), __asm(00,00,00,10),
		__asm(00,00,00,7B), __asm(00,00,00,01), __asm(00,00,00,2C), __asm(00,00,00,14),
		__asm(00,00,00,27), __asm(00,00,00,00), __asm(00,00,00,01), __asm(00,00,00,70),
		__asm(00,00,00,57), __asm(00,00,00,04), __asm(00,00,00,11), __asm(FF,FF,FF,FC),
		__asm(00,00,00,04), __asm(00,00,00,10), __asm(00,00,00,45), __asm(00,00,00,02),
		__asm(00,00,00,4E), __asm(00,00,00,20), __asm(00,00,00,02), __asm(00,00,00,04),
		__asm(00,00,00,10), __asm(00,00,00,14), __asm(00,00,00,70), __asm(00,00,00,0F),
		__asm(00,00,00,70), __asm(00,00,00,27), __asm(02,00,00,00), __asm(00,00,00,29),
		__asm(00,00,00,10), __asm(00,00,00,27), __asm(00,00,00,00), __asm(00,00,00,29),
		__asm(00,00,00,0C), __asm(00,00,00,29), __asm(FF,FF,FF,FC), __asm(00,00,00,27),
		__asm(00,00,00,14), __asm(00,00,00,7B), __asm(00,00,00,02), __asm(00,00,00,2C),
		__asm(00,00,00,18), __asm(00,00,00,2C), __asm(00,00,00,04), __asm(00,00,00,33),
		__asm(00,00,01,E8), __asm(00,00,00,27), __asm(00,00,00,00), __asm(00,00,00,27),
		__asm(00,00,00,00), __asm(00,00,00,27), __asm(00,00,00,40), __asm(00,00,00,27),
		__asm(00,00,00,1B), __asm(00,00,00,27), __asm(00,00,00,10), __asm(00,00,00,7B),
		__asm(00,00,00,01), __asm(00,00,00,2C), __asm(00,00,00,14), __asm(00,00,00,59),
		__asm(00,00,00,30), __asm(00,00,00,2E), __asm(00,00,00,01), __asm(00,00,00,70),
		__asm(00,00,00,20), __asm(00,00,00,02), __asm(00,00,00,03), __asm(00,00,00,0C),
		__asm(00,00,00,24), __asm(00,00,00,57), __asm(00,00,00,04), __asm(00,00,00,24),
		__asm(00,00,00,27), __asm(00,00,00,44), __asm(00,00,00,27), __asm(00,00,00,40),
		__asm(00,00,00,27), __asm(00,00,00,10), __asm(00,00,00,7B), __asm(00,00,00,03),
		__asm(00,00,00,2C), __asm(00,00,00,14), __asm(00,00,00,59), __asm(00,00,00,30),
		__asm(00,00,00,2E), __asm(00,00,00,27), __asm(00,00,00,00), __asm(00,00,00,27),
		__asm(00,00,00,00), __asm(00,00,00,27), __asm(00,00,00,40), __asm(00,00,00,27),
		__asm(00,00,00,1B), __asm(00,00,00,27), __asm(00,00,00,10), __asm(00,00,00,7B),
		__asm(00,00,00,01), __asm(00,00,00,2C), __asm(00,00,00,14), __asm(00,00,00,1F),
		__asm(00,00,00,02), __asm(00,00,00,0F), __asm(00,00,00,70), __asm(00,00,00,59),
		__asm(00,00,00,30), __asm(00,00,00,2E), __asm(00,00,00,27), __asm(7F,FF,FF,FF),
		__asm(00,00,00,27), __asm(00,00,00,01), __asm(00,00,00,27), __asm(00,00,00,50),
		__asm(00,00,00,29), __asm(00,00,00,0C), __asm(00,00,00,27), __asm(00,00,00,10),
		__asm(00,00,00,7B), __asm(00,00,00,04), __asm(00,00,00,2C), __asm(00,00,00,14),
		__asm(00,00,00,36), __asm(00,00,03,24), __asm(00,00,00,27), __asm(00,00,00,00),
		__asm(00,00,00,27), __asm(00,00,00,1B), __asm(00,00,00,27), __asm(00,00,00,50),
		__asm(00,00,00,27), __asm(00,00,00,1B), __asm(00,00,00,27), __asm(00,00,00,10),
		__asm(00,00,00,7B), __asm(00,00,00,01), __asm(00,00,00,2C), __asm(00,00,00,14),
		__asm(00,00,00,54), __asm(00,00,00,30), __asm(00,00,00,59), __asm(00,00,00,30),
		__asm(00,00,00,2E), __asm(00,00,00,01), __asm(00,00,00,74), __asm(00,00,00,35),
		__asm(00,00,03,48), __asm(00,00,00,59), __asm(00,00,00,30), __asm(00,00,00,85),
		__asm(00,00,00,18), __asm(00,00,00,85), __asm(00,00,00,14), __asm(00,00,00,85),
		__asm(00,00,00,10), __asm(00,00,00,85), __asm(00,00,00,0C), __asm(00,00,00,27),
		__asm(00,00,00,48), __asm(00,00,00,27), __asm(00,00,00,50), __asm(00,00,00,27),
		__asm(00,00,00,18), __asm(00,00,00,7B), __asm(00,00,00,03), __asm(00,00,00,2C),
		__asm(00,00,00,1C), __asm(00,00,00,30), __asm(20,49,53,59), __asm(69,78,75,41),
		__asm(72,61,69,6C), __asm(75,52,20,79), __asm(6D,69,74,6E), __asm(28,20,2C,65),
		__asm(32,20,29,63), __asm(20,33,32,30), __asm(78,65,6C,41), __asm(5F,59,22,20),
		__asm(73,73,65,4C), __asm(6F,43,20,22), __asm(00,2E,65,6C), __asm(00,00,00,00),
		__asm(00,00,00,00), __asm(00,00,00,00), __asm(52,5F,5F,00), __asm(61,69,00,00),
		__asm(69,69,69,69), __asm(00,00,00,00), __asm(46,49,58,45), __asm(53,5F,4F,6E),
		__asm(43,6C,69,65), __asm(6E,74,43,68), __asm(65,63,6B,52), __asm(65,73,70,6F),
		__asm(6E,73,65,00), __asm(02,00,00,00), __asm(00,00,00,00), __asm(00,00,00,00)
	},
	YSI_g_sLastNative[64] = "-", // Invalid.
	YSI_g_sRequestedData = 0;

static stock bool:YAR_DumpFile()
{
	new
		File:f = fopen("ysi_aux_runtime.amx", io_write);
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
	// Data should always be aligned, I think.
	new
		pack[64 char],
		i = -1,
		// The data array we write the new name in to.  This is found strictly
		// at the start of DAT, so is at `*0x10`.
		o = __32(YSI_g_sByteCode[16 / cellbytes]);
	o = o / cellbytes;
	strpack(pack, name);
	do
	{
		++i;
		YSI_g_sByteCode[o] = swapchars(pack[i]);
		++o;
	}
	while (!Cell_HasZeroByte(pack[i]));
}

stock bool:HasNative(const name[])
{
	if (strcmp(name, YSI_g_sLastNative) == 0)
	{
		// The script is already loaded with this native.  Can just call it.
		return true;
	}
	
	YAR_WriteNative(name);

	if (!YAR_DumpFile())
	{
		return false;
	}

	// Reload the FS, and test that it did load.  If it didn't the native we
	// want to use probably doesn't exist.
	deleteproperty(27, "R__");
	YSI_SendRconCommand__("reloadfs ../scriptfiles/ysi_aux_runtime");
	if (existproperty(27, "R__"))
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
		YSI_SendRconCommand__("loadfs ../scriptfiles/ysi_aux_runtime");
	}

	return false;
}

stock bool:CallNative(const name[], &ret, const specifier[], GLOBAL_TAG_TYPES:...)
{
	// This call creates the filterscript.
	if (HasNative(name))
	{
		CallRemoteFunction("N__", specifier, ___(3));
		ret = getproperty(27, "R__");
		return true;
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

/*-------------------------------------------------------------------------*//**
 * <library>y_rconfix</library>
 * <remarks>
 *   This code is always needed, even if fixes.inc exists, because y_master can
 *   repeatedly load and unload it to use as a buffer filterscript.  Basically,
 *   because this FS is always loaded it ensures that 16 other filterscripts
 *   can't all be loaded at once.  So if 15 are loaded and we need an extra
 *   space to reload one while preserving data we can unload this one, use the
 *   spare space, then load this one back up again.
 * </remarks>
 *//*------------------------------------------------------------------------**/

y_rconfix_Load()
{
	// This is the old version from fixes.inc, just remove it.  Our version will
	// be correctly detected by fixes.inc and thus not replaced.
	YSI_SendRconCommand__("unloadfs ../scriptfiles/callbackfix");
	if (YSI_g_sLastNative[0] == '-')
	{
		// This is the location in the file of the pointer to the native we are
		// `*0x24 + 4`, replacing.  It should be the first native, so could be
		// found at i.e. one cell after the start of the native functions block.
		#if cellbits == 64
			new offset = YSI_g_sByteCode[36 / cellbytes] >>> 32;
		#elseif cellbits == 32
			new offset = YSI_g_sByteCode[36 / cellbytes];
		#else
			#error Unsupported `cellbits`.
		#endif
		// Rewrite the bytecode to include the name of the new native.
		YSI_g_sByteCode[offset] = __32(YSI_g_sByteCode[16 / cellbytes]);
		//offset = __32(YSI_g_sByteCode[0]) / cellbytes - 1;
		YSI_g_sByteCode[sizeof (YSI_g_sByteCode) - 1] = __OPEN_MP_VERSION;
		// Not loaded yet.  We don't care if the file already exists because
		// this is the first time we've got here this server run, thus the
		// available natives may have changed since the last time we wrote it.
		HasNative("heapspace");
	}
	else
	{
		YSI_SendRconCommand__("loadfs ../scriptfiles/ysi_aux_runtime");
	}
	if (fexist("ysi_aux_runtime.amx"))
	{
		#if defined YSI_FIX_CALLBACKS
			state OnClientCheckResponse : OnClientCheckResponse_GM;
		#endif
	}
	else
	{
		Debug_Warning("Could not load RconCommand/ClientCheckResponse fix FS.");
		Debug_Info("Ignore this error if the FS already loaded.");
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_rconfix</library>
 * <remarks>
 *   Unload the callback fix filterscript.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock y_rconfix_Unload()
{
	YSI_SendRconCommand__("unloadfs ../scriptfiles/ysi_aux_runtime");
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

//#pragma option -a
#define SPACE_IN_MB (128)

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
	__hea = 2,
	__stk = 4;

// Allocate a lot of space for temporary storage.
#pragma dynamic SPACE_IN_MB * 1024 * 1024 / cellbytes

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
native StrCmp(const string1[], const string2[], bool:ignorecase, length) = strcmp;
native bool:MemCpy(dest, const src[], index, bytes, max) = memcpy;

native CallRemoteFunction(const function[], const specifier[], ...) = CallRemoteFunction;

// Reserve space in the header for a function name up to 63 characters.
new const
	// This is at DAT address 0, which is brilliant for locating it.  It is also
	// dead space before the native name is written to it, so put something in.
	NATIVE[64 char] = !" ISYixuArailuR ymitn( ,e2 )c 320xelA_Y\" sseLoC \"\0.el",
	RESULT[] = !"R__",
	AI[] = !"ai",
	IIII[] = !"iiii",
	// Use the same string for everything, so we only need one.  And pack it.
	FIXES_RESPONSE[] = !"FIXES_OnClientCheckResponse";

new
	gAvailable = SPACE_IN_MB * 1024 * 1024 / cellbytes,
	// This might be a constant...
	gAllocated = 0;

new const
	// This is written by our loader, NOT the server.  We do this just to save
	// space in the header from not needing to make this `public`.  To
	// facilitate this, it is the very last thing in the file.
	__OPEN_MP_VERSION = 0;

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
	#emit SYSREQ.C     YSI

	// Save the return value.
	#emit PUSH.C       NATIVE
	#emit PUSH.pri
	#emit PUSH.C       RESULT
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
		SetProperty(27, RESULT, gAllocated, NATIVE);

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
		// We don't need the last parameter, so it doesn't matter what it is.
		// Save some space by re-using something irrelevant.
		SetProperty(27, RESULT, 0, NATIVE);
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
	#emit PUSH.C       RESULT
	#emit PUSH.C       args
	#emit SYSREQ.C     CallRemoteFunction
	#emit STACK        clear
}

public OnFilterScriptInit()
{
	// Force the `NATIVE` data to be in the output.
	SetProperty(27, RESULT, 0, NATIVE);
	#emit LCTRL        __hea
	#emit STOR.pri     gAllocated
}

// This callback just needs to exist in one filterscript.
public OnRconCommand(const cmd[])
{
	// The smallest I could make the assembly without `#emit`.
	if (StrCmp(cmd, FIXES_RESPONSE, true, cellmax) == 0)
	{
		// We used to use padding, but now the FS isn't packed (unfortunatley).
		return !SetProperty(27, FIXES_RESPONSE, 27, NATIVE);
	}
	return 0;
}

// This callback needs to invoke a different callback in GMs.
public OnClientCheckResponse(playerid, actionid, memaddr, retndata)
{
	if (__OPEN_MP_VERSION)
	{
		return 0;
	}
	// Invoke the global callback.
	return CallRemoteFunction(FIXES_RESPONSE, IIII, playerid, actionid, memaddr, retndata);
}

