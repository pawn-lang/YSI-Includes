enum E_HOOK_NAME_REPLACEMENT_DATA
{
	E_HOOK_NAME_REPLACEMENT_SHORT[4],
	E_HOOK_NAME_REPLACEMENT_LONG[11],
	E_HOOK_NAME_REPLACEMENT_MIN,
	E_HOOK_NAME_REPLACEMENT_LEN
}

static stock
	YSI_g_sReplacements[][E_HOOK_NAME_REPLACEMENT_DATA] =
		{
			{"CP",  "Checkpoint", 2, 10},
			{"Dyn", "Dynamic",    3, 7},
			{"TD",  "TextDraw",   2, 8},
			{"Upd", "Update",     3, 6},
			{"Obj", "Object",     3, 6},
			{"Cmd", "Command",    3, 7}
		};

stock Hooks_MakeLongName(name[64])
{
	new
		len,
		i = 0,
		pos = -1;
	while (i != sizeof (YSI_g_sReplacements))
	{
		if ((pos = strfind(name, YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_SHORT], false, pos + 1)) != -1)
		{
			// Try this same string again.  We may have found a different word.
			if ('a' <= name[(len = pos + YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_MIN])] <= 'z') continue;
			else
			{
				// Found a complete word according to CamelCase rules.
				strdel(name, pos, len),
				strins(name, YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_LONG], pos),
				pos = -1;
			}
		}
		++i;
	}
	// It is possible for the expansions to become TOO big.
	return Hooks_MakeShortName(name);
}

Test:Hooks_MakeLongName0()
{
	new
		name[64];
	name = "OnUpd";
	ASSERT(Hooks_MakeLongName(name) == 8);
	ASSERT(!strcmp(name, "OnUpdate"));
	name = "OnUpdD";
	ASSERT(Hooks_MakeLongName(name) == 9);
	ASSERT(!strcmp(name, "OnUpdateD"));
	name = "OnUpda";
	ASSERT(Hooks_MakeLongName(name) == 6);
	ASSERT(!strcmp(name, "OnUpda"));
}

Test:Hooks_MakeLongName1()
{
	new
		name[64];
	name = "CP";
	ASSERT(Hooks_MakeLongName(name) == 10);
	ASSERT(!strcmp(name, "Checkpoint"));
	name = "TD";
	ASSERT(Hooks_MakeLongName(name) == 8);
	ASSERT(!strcmp(name, "TextDraw"));
	name = "Upd";
	ASSERT(Hooks_MakeLongName(name) == 6);
	ASSERT(!strcmp(name, "Update"));
	name = "Dyn";
	ASSERT(Hooks_MakeLongName(name) == 7);
	ASSERT(!strcmp(name, "Dynamic"));
	name = "Obj";
	ASSERT(Hooks_MakeLongName(name) == 6);
	ASSERT(!strcmp(name, "Object"));
	name = "Cmd";
	ASSERT(Hooks_MakeLongName(name) == 7);
	ASSERT(!strcmp(name, "Command"));
}

Test:Hooks_MakeLongName2()
{
	new
		name[64];
	name = "OnUpdTDCP";
	ASSERT(Hooks_MakeLongName(name) == 26);
	ASSERT(!strcmp(name, "OnUpdateTextDrawCheckpoint"));
	name = "OnUpdTDObjCmd";
	ASSERT(Hooks_MakeLongName(name) == 29);
	ASSERT(!strcmp(name, "OnUpdateTextDrawObjectCommand"));
	name = "OnUpdTDCPObjCmd";
	ASSERT(Hooks_MakeLongName(name) == 31);
	ASSERT(!strcmp(name, "OnUpdateTextDrawCPObjectCommand"));
}

stock Hooks_MakeShortName(name[64])
{
	// Easy one.
	new
		len = strlen(name);
	if (len >= 32)
	{
		new
			pos,
			i = 0;
		do
		{
			if ((pos = strfind(name, YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_LONG])) != -1)
			{
				strdel(name, pos, pos + YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_LEN]),
				strins(name, YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_SHORT], pos);
			}
		}
		while ((len = strlen(name)) >= 32 && ++i != sizeof (YSI_g_sReplacements));
	}
	return len;
}

Test:Hooks_MakeShortName1()
{
	new
		name[64];
	name = "OnPlayerEnterRaceCP";
	ASSERT(Hooks_MakeShortName(name) == 19);
	ASSERT(!strcmp(name, "OnPlayerEnterRaceCP"));
	name = "OnPlayerEnterRaceCheckpoint";
	ASSERT(Hooks_MakeShortName(name) == 27);
	ASSERT(!strcmp(name, "OnPlayerEnterRaceCheckpoint"));
	name = "OnPlayerEnterDynamicRaceCheckpoint";
	ASSERT(Hooks_MakeShortName(name) == 26);
	ASSERT(!strcmp(name, "OnPlayerEnterDynamicRaceCP"));
	name = "AAAAAAAAAAAAAAAAAAAUpdateTextDraw";
	Hooks_MakeShortName(name);
	ASSERT(!strcmp(name, "AAAAAAAAAAAAAAAAAAAUpdateTD"));
	name = "BBBBBAAAAAAAAAAAAAAAAAAAUpdateTextDraw";
	Hooks_MakeShortName(name);
	ASSERT(!strcmp(name, "BBBBBAAAAAAAAAAAAAAAAAAAUpdTD"));
}

Test:Hooks_MakeShortName2()
{
	new
		name[64];
	name = "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCCCCC";
	ASSERT(Hooks_MakeShortName(name) == 43);
	ASSERT(!strcmp(name, "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCCCCC"));
	name = "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCommandCCCC";
	ASSERT(Hooks_MakeShortName(name) == 45);
	ASSERT(!strcmp(name, "AAAAAAAAAAAAAABBBBBBBBBBBBBBBBCCCCCCCCCmdCCCC"));
}






/**--------------------------------------------------------------------------**\
<summary>Hooks_IsolateName</summary>
<param name="name">The string to get the hooked function name from.</param>
<returns>
	The input string without y_hooks name decorations.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_IsolateName(string:name[])
{
	new
		pos = strfind(name, "@", false, 4);
	// Make "pos" a legal value inside the error message.
	if (pos == -1) P:E("Invalid hook name: %s", unpack(name), ++pos);
	name{pos} = '\0';
	strdel(name, 0, 4);
}


// Get rid of the "@yH_" prefix and "@" suffix and change "CP" into "Checkpoint"
// etc.
#define Hooks_MakeBaseName(%0) ( \
	Hooks_IsolateName(name)    , \
	Hooks_MakeLongName(name)   )

Test:Hooks_BaseName0()
{
	new
		name[64];
	name = "@yH_
}

Test:Hooks_BaseName1()
{
}

Test:Hooks_BaseName2()
{
}

static stock Hooks_Collate(name[64], &idx)
{
	// This records the amount of space available in the nametable, currently
	// taken up by the names of hooks that we are about to destroy.
	new
		namelen = strlen(name);
	// For this function, note that:
	//   
	//   hook OnPlayerConnect(playerid)
	//   
	// Compiles as:
	//   
	//   public @yH_OnPlayerConnect@XXX(playerid)
	//   
	// Where "XXX" is some unique number (the exact value is irrelevant, it just
	// means that multiple hooks of the same function have different names).
	static
		sBase[64],
		sHooks[128];
	// Isolate the common prefix part:
	//   
	//   @yH_OnPlayerConnect@042
	//   
	// Becomes:
	//   
	//   @yH_OnPlayerConnect@
	//   
	// The numbers at the end are irrelevant, now we can just search for hooks
	// of this exact callback.
	name[strfind(name, "@", false, 4) + 1] = '\0',
	// The above now becomes:
	//   
	//   OnPlayerConnect
	//   
	// This also handles cases such as:
	//   
	//   @yH_OnPlayerEnterRaceCheckpoint@162
	//   
	// Being invalid (too long), so instead converts the shortened:
	//   
	//   @yH_OnPlayerEnterRaceCP@162
	//   
	// To:
	//   
	//   OnPlayerEnterRaceCheckpoint
	//   
	// Thus expanding common name length reductions.
	sBase = name,
	Hooks_MakeBaseName(sBase);
	new
		// See if the original function exists.
		original = funcidx(sBase),
		// See if a fixes.inc hook exists.
		fixes = Hooks_GetFixesFunc(sBase),
		// Get all the hooks of this type.  They are stored alphabetically.
		hookCount = Hooks_GetAllHooks(name, sHooks, idx, namelen);
	// We now have:
	//  
	//  1) All the hooks of this function.
	//  2) The original function if it exists.
	//  3) The FIXES_ ALS chained function if fixes.inc exists.
	//  
	// This took huge chunks of complex code in the old version.  Now not so
	// much!  I don't know if this code is faster (I suspect it is), but it is
	// absolutely simpler!
	// Get the AMX header entry from the public function index.
	original = (original == -1) ? (0) : (AMX_GetEntryFromPublicIndex(original)),
	// Get the AMX header entry from the public function index.
	fixes    = (fixes    == -1) ? (0) : (AMX_GetEntryFromPublicIndex(fixes   ));
	new
		stub = Hooks_GenerateStub(fixes ? Hooks_GetFixesChain(fixes) : (original ? AMX_GetEntryPointer(original) : 0), sHooks, hookCount);
	return Hooks_MakePublicPointer(original, fixes, sHooks[0], stub, namelen, sBase);
}

static stock Hooks_GetFixesChain(stub)
{
	// Get the address of the next function from the FIXES_ ALS state stub.
	new
		ctx[DisasmContext];
	DisasmInit(ctx, stub);
	switch (DisasmNextInsn(ctx))
	{
		case OP_LOAD_PRI:
		{
			if (DisasmNextInsn(ctx) == OP_SWITCH && DisasmNextInsn(ctx) == OP_CASETBL)
			{
				// Get the number of items in the casetable.
				if (DisasmGetNumOperands(ctx) == 3) // 2 means no used hook.
				{
					// Got a hook to return.  Find it.
					new
						h0 = DisasmGetOperand(ctx, 3),
						h1 = DisasmGetOperand(ctx, 5),
						h2 = DisasmGetOperand(ctx, 7);
					if (h1 == h2)      return h0; // Most likely.
					else if (h0 == h2) return h1;
					else if (h0 == h1) return h2;
				}
			}
		}
		case OP_JUMP:
		{
			// Already replaced once (shouldn't happen, but may if two different
			// hooks use two different short versions of a callback).
			return DisasmGetOperand(ctx, 0);
		}
	}
	return 0;
}

/**
**/

/**--------------------------------------------------------------------------**\
<summary>Hooks_MakePublicPointer</summary>
<param name="original">The AMX header for the original callback.</param>
<param name="fixes">The AMX header for the fixes.inc ALS state chain.</param>
<param name="first">The AMX header for the first found hook.</param>
<param name="func">The address of our new code.</param>
<param name="nlen">The length of the name of the first found hook.</param>
<param name="name">The name of the callback.</param>
<returns>
	-
</returns>
<remarks>
	Takes a variety of function pointers and rewrites one to point to our new
	code.  The one chosen depends on what functions already exist and need to be
	called when, but the logic isn't complex.  If "fixes.inc" exists, call that
	first then our code.  If an existing callback exists, redirect that.
	Otherwise create a whole new entry in the public functions header (or at
	least re-write an existing one).
</remarks>
\**--------------------------------------------------------------------------**/

static stock Hooks_MakePublicPointer(original, fixes, first, func, nlen, const name[])
{
	// We need to create an AMX header entry for "name", e.g. point
	// "OnPlayerConnect" at the correct function.
	if (fixes)
	{
		// Here, "fixes" points to the second item in the ALS chain.  "original"
		// points to the actual callback in "fixes.inc", which if it exists
		// means that we don't need to rewrite anything in the header, just
		// rewrite the states stub.
		// 
		// There is a remote chance that the stub has already been rewritten
		// once, in which case just replace that old jump with the new one.
		// Other code will need to account for that case to correct call the
		// remainder of the chain.
		Hooks_RedirectFixes(fixes, func);
	}
	else if (original)
	{
		// No "fixes.inc", but this callback already exists.  In that case, just
		// replace the pointer address.
		Hooks_RedirectPublic(original, func);
	}
	else
	{
		new
			len = strlen(name);
		if (nlen >= len)
		{
			// We don't have an existing callback with this name, only hooks.
			// We need to add the name of the callback to the AMX header, and we
			// have enough space in which to do so.
			AMX_WriteString(AMX_BASE_ADDRESS + AMX_Read(first + 4), name, len),
			// Point what used to be a hook at the new function.
			Hooks_RedirectPublic(first, func);
		}
		else
		{
			P:F("Could not write function name in \"Hooks_MakePublicPointer\".");
			// TODO: Fix this.  Use an alternate memory location (the actual
			// code segment in which we are writing seems like a good choice).
		}
	}
}

static stock Hooks_RedirectPublic(stub, to)
{
	#emit LOAD.S.pri to
	#emit SREF.S.pri stub
}

static stock Hooks_RedirectFixes(stub, to)
{
	stub += AMX_HEADER_COD + AMX_Read(stub),
	AMX_Write(stub, _:RelocateOpcode(OP_JUMP)),
	AMX_Write(stub + 4, to + (AMX_REAL_DATA + AMX_HEADER_COD));
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_GetAllHooks</summary>
<param name="name">The name of the callback (with y_hooks prefix).</param>
<param name="hooks">Array in which to store the function headers.</param>
<param name="idx">Current position in the AMX header.</param>
<param name="namelen">Min bound of space used by all these names.</param>
<returns>
	The number of hooks found.
</returns>
<remarks>
	The name of the function currently being processed is derived from the first
	found hook.  This means we already know of one hook, but to simplify the
	code we get that one again here.  Above we only know the name not the
	address.  Hence the "- 1" in "i = idx - 1" (to go back one function name).
	
	Our "namelen" variable already contains the full length of the first found
	hook - this is the length of "name", plus N extra characters.  The following
	are all valid, and may occur when orders are played with:
		
		@yH_OnX@
		@yH_OnX@1
		@yH_OnX@01
		@yH_OnX@024
		@yH_OnX@ZZZ
		@yH_OnX@999@024
		
	If we want to get the EXACT space taken up by all these hook names we would
	need to get the string of the name in this function then measure it.  There
	is really no point in doing this - if we have a second we will always have
	enough space for our new names.  Instead, we assume that they are all just
		
		@yH_OnX@
		
	And add on that minimum length accordingly (plus 1 for the NULL character).
	
	This length is used if the original callback doesn't exist but hooks do.  In
	that case we need to add the callback to the AMX header, and there is a tiny
	chance that the original name will be longer than one hook's name.  In that
	case, having two or more hooks will (AFAIK) always ensure that we have
	enough space to write the longer name.
	
	If there is only one hook, no original function, and the name of the hook is
	shorter than the name of the original function then we have an issue and
	will have to do something else instead.
</remarks>
\**--------------------------------------------------------------------------**/

static stock Hooks_GetAllHooks(const name[], hooks[128], &idx, &namelen)
{
	// Start from the very start - repeats the first item.
	new
		len = strlen(name) + 1,
		count,
		i = idx - 1;
	while ((i = AMX_GetPublicEntry(i, hooks[count], name)))
	{
		Hooks_InvalidateName(hooks[count]),
		idx = i;
		// Record how much consecutive space we have to play with in the AMX.
		if (count) namelen += len; // The first hook was already counted.
		// Increment and count how many hooks of this type we have.
		if (++count == sizeof (hooks))
		{
			P:W("Hooks_GetAllHooks: Potential overflow.");
			break;
		}
	}
	return count;
}

static stock Hooks_GetFixesFunc(const name[64])
{
	static
		fn[64];
	return
		fn = "FIXES_",
		strcat(fn, name),
		Hooks_MakeShortName(fn),
		funcidx(fn);
}

#endinput

// Main loop
static
	name[64];
new
	idx;
// Get the next hook type.
while ((idx = AMX_GetPublicNamePrefix(idx, name, _A<@yH_>)))
{
	// Collect all the hooks of this function, and rewrite the call code.
	Hooks_Collate(name, idx);
}

