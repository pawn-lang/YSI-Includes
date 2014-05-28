/**--------------------------------------------------------------------------**\
					==============================
					 y_hooks - Hook any callback!
					==============================
Description:
	Automatically hooks any callbacks with a very simple syntax.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the SA:MP callback hooks include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2008
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
	Thanks:
		JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
		Peter, Cam - Support.
		ZeeX, g_aSlice/Slice, Popz, others - Very productive conversations.
		koolk - IsPlayerinAreaEx code.
		TheAlpha - Danish translation.
		breadfish - German translation.
		Fireburn - Dutch translation.
		yom - French translation.
		50p - Polish translation.
		Zamaroht - Spanish translation.
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	3.0
Changelog:
	23/03/14:
		Rewrote for better ordering.
	26/12/13:
		Added sections.
	15/04/13:
		Changed the assembly to be shorter by actually using the stack.
		Now slightly handles return values.
	14/04/13:
		Entirely new version - simpler, faster, and more generic.
	02/01/13:
		Rewrote the system to do away with ALS.
		Removed overflow checks in every callback.
		Streamlined code.
	14/04/12:
		Added crash fix from Slice, now returning correct values.
		Fixed ALS detection of mode callbacks.
	25/02/12:
		Extracted most of the code to a separate file.
	17/03/11:
		Second complete re-write using another new technique.  Now VERY fast!
		Updated OnPlayerUpdate code using Google63's SCTRL jump code.
	06/08/10:
		First version
\**--------------------------------------------------------------------------**/

/*

     ad88888ba                                              
    d8"     "8b              ,d                             
    Y8,                      88                             
    `Y8aaaaa,    ,adPPYba, MM88MMM 88       88 8b,dPPYba,   
      `"""""8b, a8P_____88   88    88       88 88P'    "8a  
            `8b 8PP"""""""   88    88       88 88       d8  
    Y8a     a8P "8b,   ,aa   88,   "8a,   ,a88 88b,   ,a8"  
     "Y88888P"   `"Ybbd8"'   "Y888  `"YbbdP'Y8 88`YbbdP"'   
                                               88           
                                               88           

*/

#define hook%1(%2) UNIQUE_FUNCTION<@yH_%1@...>(%2);UNIQUE_FUNCTION<@yH_%1@...>(%2)
#define rehook%1(%2) UNIQUE_FUNCTION<@yH_%1@...>(%2)
#define Hook:%0_%1(%2) @yH_%1@%0(%2);@yH_%1@%0(%2)
// Strip out extra spaces (nicely recursive)
#define @yH_%0\32;%1(%2) @yH_%1(%2)

enum E_HOOK_NAME_REPLACEMENT_DATA
{
	E_HOOK_NAME_REPLACEMENT_SHORT[4],
	E_HOOK_NAME_REPLACEMENT_LONG[11],
	E_HOOK_NAME_REPLACEMENT_MIN,
	E_HOOK_NAME_REPLACEMENT_LEN
}

#if !defined CHAIN_ORDER
	#define CHAIN_ORDER() 0
#endif

#define PRE_HOOK(%0) forward @CO_%0();public @CO_%0(){return CHAIN_ORDER()+1;}

enum E_PRE_HOOK
{
	E_PRE_HOOK_NAME[16],
	E_PRE_HOOK_VALUE
}

PRE_HOOK(HookChain)
#undef CHAIN_ORDER
#define CHAIN_ORDER @CO_HookChain

static stock _HookChain_IncludeStates() <_ALS : _ALS_x0, _ALS : _ALS_x1, _ALS : _ALS_x2, _ALS : _ALS_x3>
{
}

static stock _HookChain_IncludeStates() <_ALS : _ALS_go>
{
}

#define HOOK_FORWARD:%0_%2(%1); \
	forward %0_%2(%1); \
	public %0_%2(%1) <_ALS : _ALS_x0, _ALS : _ALS_x1> { return 1; } \
	public %0_%2(%1) <> { return 1; }

#define HOOK_RET:%0(%1) forward @RET%0(); public @RET%0()

HOOK_RET:OnPlayerCommandText()
{
	return 0;
}

HOOK_RET:OnRconCommand()
{
	return 0;
}

static stock
	YSI_g_sReplacements[][E_HOOK_NAME_REPLACEMENT_DATA] =
		{
			{"CP",  "Checkpoint", 2, 10},
			// For "SIF".
			{"Cnt", "Container",  3, 9},
			{"Inv", "Inventory",  3, 9},
			{"Dyn", "Dynamic",    3, 7},
			{"TD",  "TextDraw",   2, 8},
			{"Upd", "Update",     3, 6},
			{"Obj", "Object",     3, 6},
			{"Cmd", "Command",    3, 7}
		};

/**--------------------------------------------------------------------------**\
<summary>Hooks_MakeLongName</summary>
<param name="name">Function name to modify.</param>
<returns>
	-
</returns>
<remarks>
	Expands all name parts like "CP" and "Obj" to their full versions (in this
	example "Checkpoint" and "Object").
</remarks>
\**--------------------------------------------------------------------------**/

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

/**--------------------------------------------------------------------------**\
<summary>Hooks_MakeShortName</summary>
<param name="name">Function name to modify.</param>
<returns>
	-
</returns>
<remarks>
	Compresses function names when required to fit within 32 characters
	according to well defined rules (see "YSI_g_sReplacements").
</remarks>
\**--------------------------------------------------------------------------**/

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
	name[pos] = '\0',
	strdel(name, 0, 4);
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_GetPreloadLibraries</summary>
<param name="preloads">Desination in which to store all the preloads.</param>
<param name="precount">Number of found preload libraries.</param>
<param name="size">Maximum number of libraries to store.</param>
<returns>
	-
</returns>
<remarks>
	Some includes, like "fixes.inc" and anti-cheats MUST come before all other
	includes in order for everything to function correctly (at least fixes.inc
	must).  This function looks for these definitions:
	
	    PRE_HOOK(FIXES)
	
	Which tell y_hooks that any "FIXES_" prefixed callbacks are part of one of
	these chains.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetPreloadLibraries(preloads[][E_PRE_HOOK], &precount, size = sizeof (preloads))
{
	new
		first = 0,
		idx = 0,
		last = -8;
	--size,
	precount = 0,
	AMX_GetPublicEntryPrefix(0, first, _A<@CO_>);
	while ((idx = AMX_GetPublicEntryPrefix(idx, last, _A<@CO_>))) {}
	for (new i = first; i <= last; i += 8)
	{
		if (precount == size)
		{
			P:E("y_hooks prehook array filled");
			break;
		}
		new
			name[32],
			addr = AMX_Read(i);
		AMX_ReadString(AMX_Read(i + 4) + AMX_BASE_ADDRESS + 4, name),
		strunpack(preloads[precount][E_PRE_HOOK_NAME], name, 32),
		preloads[precount][E_PRE_HOOK_VALUE] = CallFunction(addr),
		++precount;
	}
	// Sort the preload libraries.
	for (new i = 0, tmp[E_PRE_HOOK]; i != precount; ++i)
	{
		for (new j = i + 1; j != precount; ++j)
		{
			// This neatly moves all the functions with blanked names to the
			// start of the public functions table (which will soon be moved).
			Hooks_ComparePublics(i, j);
			if (preloads[i][E_PRE_HOOK_VALUE] > preloads[j][E_PRE_HOOK_VALUE])
			{
				tmp = preloads[i],
				preloads[i] = preloads[j],
				preloads[j] = tmp;
			}
		}
	}
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_GetPreHooks</summary>
<param name="preloads">Names of libraries that come before y_hooks.</param>
<param name="precount">Number of pre libraries.</param>
<param name="name">Name of the callback.</param>
<param name="hooks">Destination in which to store the headers.</param>
<param name="count">Number of headers found.</param>
<returns>
	-
</returns>
<remarks>
	Finds all the AMX file headers for functions with a similar name to the
	given callback that should be called before (or near) the given callback.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetPreHooks(preloads[][E_PRE_HOOK], precount, name[64], hooks[], &count)
{
	new
		idx,
		lfunc[64];
	// Collect all the functions with something like this name.
	do
	{
		strcat(lfunc, name),
		Hooks_MakeShortName(lfunc);
		if (AMX_GetPublicEntry(0, hooks[count], lfunc, true)) ++count;
		strcpy(lfunc, preloads[idx][E_PRE_HOOK_NAME]),
		strcat(lfunc, "_");
	}
	while (++idx <= precount);
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_GetPointerRewrite</summary>
<param name="hooks">All the prehooks for this callback.</param>
<param name="num">The number of prehooks.</param>
<param name="ptr">A pointer to write the new stub address to.</param>
<param name="next">The pointer for the function called after y_hooks.</param>
<param name="name">The name of the callback being processed.</param>
<param name="nlen">Space available in the header to write text in.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetPointerRewrite(hooks[], num, &ptr, &next, name[], nlen)
{
	switch (num)
	{
		case 0:
		{
			next = 0;
			new
				len = strlen(name);
			if (nlen >= len)
			{
				// We don't have an existing callback with this name, only hooks.
				// We need to add the name of the callback to the AMX header,
				// and we have enough space in which to do so.
				new
					str[32];
				strpack(str, name),
				AMX_WriteString(AMX_BASE_ADDRESS + AMX_Read(ptr + 4), str, len);
			}
			else
			{
				P:F("Could not write function name in \"Hooks_MakePublicPointer\".");
				// TODO: Fix this.  Use an alternate memory location (the actual
				// code segment in which we are writing seems like a good
				// choice).
			}
		}
		case 1:
		{
			// No "fixes.inc", but this callback already exists.  In that case,
			// just replace the pointer address.
			next = ptr = hooks[0];
		}
		default:
		{
			// Special hooks.  Optimise them.
			for (new cur = 1; cur != num; ++cur)
			{
				ptr = hooks[cur];
				new
					tmp = AMX_Read(ptr),
					nt = Hooks_GetStubEntry(tmp);
				tmp += AMX_HEADER_COD,
				AMX_Write(tmp, _:RelocateOpcode(OP_JUMP));
				switch (nt)
				{
					case -1: ptr = tmp + 4, next = 0;
					case 0: next = 0;
					default:
					{
						ptr  = tmp + 4,
						next = tmp + nt,
						nt = AMX_Read(next),
						// Chain those not hooked.
						AMX_Write(ptr, nt),
						// Store the possible next address.
						AMX_Write(next, nt - (AMX_REAL_DATA + AMX_HEADER_COD));
					}
				}
			}
		}
	}
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_GetStubEntry</summary>
<param name="stub">Starting address of the function.</param>
<returns>
	The address at which the actual code in this function starts.
</returns>
<remarks>
	This handles three cases.  Regular functions end instantly as found.
	Functions that start with a switch (even before "PROC") are assumed to be
	state-based functions, and we find the most likely state to be used (i.e. we
	remove all future state changes).
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetStubEntry(stub)
{
	// Get the address of the next function from the ALS state stub.
	new
		ctx[DisasmContext];
	DisasmInit(ctx, stub, stub + 64);
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
					if (h1 == h2)      return  8 * 4; // Most likely.
					else if (h0 == h2) return 10 * 4;
					else if (h0 == h1) return 12 * 4;
					else P:E("y_hooks could not extract state stub jump");
				}
				else return -1;
			}
		}
		case OP_JUMP:
		{
			// Already replaced once (shouldn't happen, but may if two different
			// hooks use two different short versions of a callback).
			return 4; // DisasmGetOperand(ctx, 0);
		}
		case OP_PROC:
		{
			//return stub;
			P:E("y_hooks attempting to redirect a PROC hook");
		}
	}
	return 0;
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

_Y_HOOKS_STATIC stock Hooks_GetAllHooks(const name[], hooks[128], &idx, &namelen)
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

/**--------------------------------------------------------------------------**\
<summary></summary>
<param name=""></param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_DoAllHooks()
{
	// Get the preloaders.
	new
		precount = 0,
		preloads[8][E_PRE_HOOK];
	Hooks_GetPreloadLibraries(preloads, precount);
	// Main loop
	new
		name[32],
		idx;
	// Get the next hook type.
	while ((idx = AMX_GetPublicNamePrefix(idx, name, _A<@yH_>)))
	{
		// Collect all the hooks of this function, and rewrite the call code.
		Hooks_Collate(preloads, precount, name, idx);
	}
	Hooks_SortPublics();
}

/**--------------------------------------------------------------------------**\
<summary></summary>
<param name=""></param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_Collate(preloads[][E_PRE_HOOK], precount, name[32], &idx)
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
		sName[64],
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
	name{strfind(name, "@", false, 4) + 1} = '\0',
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
	strunpack(sName, name),
	Hooks_IsolateName(sName),
	Hooks_MakeLongName(sName);
	new
		// Get all the hooks of this type.  They are stored alphabetically.
		hookCount = Hooks_GetAllHooks(name, sHooks, idx, namelen),
		writePtr = sHooks[0], // Header for the first found hook.
		nextPtr,
		pc, ph[4];
	// Get the preloads.
	Hooks_GetPreHooks(preloads, precount, sName, ph, pc),
	// Get where in the chain we are being inserted.
	Hooks_GetPointerRewrite(ph, pc, writePtr, nextPtr, sName, namelen);
	// Add ALS hooks to the end of the list.
	if ((sHooks[hookCount] = nextPtr)) ++hookCount;
	// Write the code.
	Hooks_GenerateCode(sName, sHooks, hookCount, writePtr, pc > 1);
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_GenerateCode</summary>
<param name="name">Name of the function to generate.</param>
<param name="hooks">All the functions to call.</param>
<param name="count">Number of functions to call.</param>
<param name="write">Where to write the new function's pointer.</param>
<param name="hasprehooks">Needs to call other stuff first.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_GenerateCode(name[64], hooks[], count, write, bool:hasprehooks)
{
	// We now have:
	//  
	//  1) All the hooks of this function.
	//  2) The original function if it exists.
	//  3) Special ALS chained functions if they exists.
	//  
	// This took huge chunks of complex code in the old version.  Now not so
	// much!  I don't know if this code is faster (I suspect it is), but it is
	// absolutely simpler!
	new
		size = Hooks_WriteFunction(hooks, count, Hooks_GetDefaultReturn(name));
	P:4("Hooks_GenerateCode %32s called: %6d %6d %08x %d", name[4], hasprehooks, size, hasprehooks ? (write - AMX_HEADER_COD) : (write - AMX_BASE_ADDRESS), CGen_GetCodeSpace());
	if (size)
	{
		//AMX_Write(write, 40);
		if (hasprehooks) AMX_Write(write, CGen_GetCodeSpace() + AMX_REAL_DATA);
		else AMX_Write(write, CGen_GetCodeSpace() - AMX_HEADER_COD);
		CGen_AddCodeSpace(size);
	}
	else
	{
		if (hasprehooks) AMX_Write(write, AMX_Read(hooks[0]) + (AMX_REAL_DATA + AMX_HEADER_COD));
		else AMX_Write(write, AMX_Read(hooks[0]));
	}
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_InvalidateName</summary>
<param name="entry">The public function slot to destroy.</param>
<returns>
	-
</returns>
<remarks>
	Basically, once we know a function has been included, wipe it from the AMX
	header.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_InvalidateName(entry)
{
	AMX_Write(AMX_BASE_ADDRESS + AMX_Read(entry + 4), 0);
}

/*

    88888888888                                        88                            88               ad88             
    88                                           ,d    ""                            88              d8"               
    88                                           88                                  88              88                
    88aaaaa 88       88 8b,dPPYba,   ,adPPYba, MM88MMM 88  ,adPPYba,  8b,dPPYba,     88 8b,dPPYba, MM88MMM ,adPPYba,   
    88""""" 88       88 88P'   `"8a a8"     ""   88    88 a8"     "8a 88P'   `"8a    88 88P'   `"8a  88   a8"     "8a  
    88      88       88 88       88 8b           88    88 8b       d8 88       88    88 88       88  88   8b       d8  
    88      "8a,   ,a88 88       88 "8a,   ,aa   88,   88 "8a,   ,a8" 88       88    88 88       88  88   "8a,   ,a8"  
    88       `"YbbdP'Y8 88       88  `"Ybbd8"'   "Y888 88  `"YbbdP"'  88       88    88 88       88  88    `"YbbdP"'   

*/

/**--------------------------------------------------------------------------**\
<summary>Hooks_GetFunctionWritePoint</summary>
<param name="name">The function to get the address pointer of.</param>
<param name="write">Destination variable.</param>
<returns>
	The address at which this function's pointer is stored in the AMX header, if
	the function exists of course.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetFunctionWritePoint(name[], &write)
{
	AMX_GetPublicEntry(0, write, name, true);
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_GetDefaultReturn</summary>
<param name="name">The function to get the default return of.</param>
<returns>
	The default return for a callback, normally 1.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetDefaultReturn(name[64])
{
	strins(name, "@RET", 0);
	Hooks_MakeShortName(name);
	new
		ptr;
	if (AMX_GetPublicEntry(0, ptr, name, true))
	{
		// A "RET_OnWhatever" function exists - rationalise the return.
		return CallFunction(AMX_Read(ptr)) ? 1 : 0;
	}
	return 1;
}

/*

      ,ad8888ba,                       88                                                
     d8"'    `"8b                      88                                                
    d8'                                88                                                
    88             ,adPPYba,   ,adPPYb,88  ,adPPYba,  ,adPPYb,d8  ,adPPYba, 8b,dPPYba,   
    88            a8"     "8a a8"    `Y88 a8P_____88 a8"    `Y88 a8P_____88 88P'   `"8a  
    Y8,           8b       d8 8b       88 8PP""""""" 8b       88 8PP""""""" 88       88  
     Y8a.    .a8P "8a,   ,a8" "8a,   ,d88 "8b,   ,aa "8a,   ,d88 "8b,   ,aa 88       88  
      `"Y8888Y"'   `"YbbdP"'   `"8bbdP"Y8  `"Ybbd8"'  `"YbbdP"Y8  `"Ybbd8"' 88       88  
                                                      aa,    ,88                         
                                                       "Y8bbdP"                          

*/

/**--------------------------------------------------------------------------**\
<summary>Hooks_WriteFunction</summary>
<param name="pointers">The hooks to link together.</param>
<param name="size">The number of functions in the array.</param>
<param name="ret">The default return.</param>
<param name="skipable">Can future hooks be ignored on -1?</param>
<returns>
	The number of bytes written to memory.
</returns>
<remarks>
	Generate some new code, very nicely :D.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_WriteFunction(const pointers[], const size, const ret = 1, const skipable = true)
{
	new
		bool:multiple = size != 1,
		base = (AMX_HEADER_COD - AMX_BASE_ADDRESS) + AMX_REAL_ADDRESS,
		ctx[AsmContext];
	// Make sure the underlying system doesn't change without us.  Now supported
	// natively.
	CGen_UseCodeSpace(ctx);
	
	// Start of the function.
	@emit PROC              // 1
	
	// Allocate space for our "ret" variable at "frm - 4".
	if (multiple) @emit PUSH.C        ret // 3
	
	// Copy the stack to itself (MOVS).
	// Allocate space.
	@emit LOAD.S.alt    8   // 5
	@emit LCTRL         4   // 7
	@emit SUB               // 8
	@emit SCTRL         4   // 10
	@emit XCHG              // 11
	
	// The "MOVS" OpCode only takes a constant, not a variable, so we need to
	// generate self-modifying code (just to be UBER meta)!  This code is
	// generated AFTER the file is loaded so we bypass the data segment checks
	// and can freely write wherever we want.
	@emit STOR.pri      (CGen_GetCodeSpace() + (18 * 4) - (multiple ? 0 : 8)) // 13
	
	// Do the copying.  "alt" is already "STK", load the "FRM" offset.
	@emit LCTRL         5   // 15
	@emit ADD.C         12  // 17
	// This is the instruction we want to modify...
	@emit MOVS          0   // 19 (- 1)
	
	// Push the (fake) number of parameters.
	@emit PUSH.C        -4
	// Now loop over all our functions and insert "CALL" opcodes for them.
	if (multiple)
	{
		for (new i = 0; ; )
		{
			// Get the absolute offset from here.
			@emit CALL          (AMX_Read(pointers[i]) + base) // 2
			if (skipable)
			{
				// =====================================
				//  THIS SECTION IS CURRENTLY 10 CELLS. 
				// =====================================
				// Note: Including the original call...
				//  
				//  if (func() < 0) break;
				//  else ret = ret & func();
				//  
				@emit ZERO.alt      // 3
				@emit JSLESS.rel    ((size - i) * (10 * 4) - (5 * 4)) // 5
				// =========================
				//  JUMP OVER THIS SECTION. 
				// =========================
			}
			@emit LOAD.S.alt    -4   // 7
			if (ret) @emit AND       // 8
			else @emit OR            // 8
			// Loop and do the very first items last.
			if (++i == size) break;
			else @emit STOR.S.pri -4 // 10
		}
		if (skipable)
		{
			@emit JUMP.rel      4    // 10
			// This is the point the large "JSLESS" above goes to.
			// -1 = 0, -2 = 1
			@emit INVERT
		}
	}
	else if (skipable)
	{
		// Still need this code as they may hook a function that doesn't exist,
		// but we still need to correctly process -1 or -2.
		@emit CALL          (AMX_Read(pointers[0]) + base)
		@emit ZERO.alt
		@emit JSGEQ.rel     4
		@emit INVERT
	}
	else
	{
		// Just replace the original (turns out, this takes no code).  Basically
		// just discard everything we've written so far (reclaims the memory).
		return 0;
	}
	
	// This is the point the small "JUMP" above goes to.
	@emit MOVE.alt
	// Remove the whole stack then get the return value.
	@emit LCTRL         5
	@emit SCTRL         4
	//@emit LOAD.S.pri    -4
	@emit MOVE.pri
	
	// Return.
	@emit RETN
	
	// Return the number of bytes written.
	return ctx[AsmContext_buffer_offset];
}

/*

     ad88888ba                                 88                          
    d8"     "8b                          ,d    ""                          
    Y8,                                  88                                
    `Y8aaaaa,    ,adPPYba,  8b,dPPYba, MM88MMM 88 8b,dPPYba,   ,adPPYb,d8  
      `"""""8b, a8"     "8a 88P'   "Y8   88    88 88P'   `"8a a8"    `Y88  
            `8b 8b       d8 88           88    88 88       88 8b       88  
    Y8a     a8P "8a,   ,a8" 88           88,   88 88       88 "8a,   ,d88  
     "Y88888P"   `"YbbdP"'  88           "Y888 88 88       88  `"YbbdP"Y8  
                                                               aa,    ,88  
                                                                "Y8bbdP"   

*/

/**--------------------------------------------------------------------------**\
<summary>Hooks_CompareNextCell</summary>
<param name="addr0">The 1st address to read.</param>
<param name="addr1">The 2nd address to read.</param>
<returns>
	-1 - The first address is bigger.
	0  - The addresses are the same
	1  - The second address is bigger.
</returns>
<remarks>
	Reads two addresses, converts them to big endian, and compares them as four
	characters of a string at once.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_CompareNextCell(addr0, addr1)
{
	new
		s0 = Cell_ReverseBytes(AMX_Read(addr0)),
		s1 = Cell_ReverseBytes(AMX_Read(addr1));
	// Propogate NULLs.
	if (!(s0 & 0xFF000000)) s0 = 0;
	else if (!(s0 & 0x00FF0000)) s0 &= 0xFF000000;
	else if (!(s0 & 0x0000FF00)) s0 &= 0xFFFF0000;
	else if (!(s0 & 0x000000FF)) s0 &= 0xFFFFFF00;
	if (!(s1 & 0xFF000000)) s1 = 0;
	else if (!(s1 & 0x00FF0000)) s1 &= 0xFF000000;
	else if (!(s1 & 0x0000FF00)) s1 &= 0xFFFF0000;
	else if (!(s1 & 0x000000FF)) s1 &= 0xFFFFFF00;
	// We need the numbers to be compared as big-endian.  Now any trailing NULLs
	// don't matter at all.
	if (s1 > s0) return 1;
	else if (s1 < s0) return -1;
	else return 0;
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_ComparePublics</summary>
<param name="idx0">The index of the 1st public.</param>
<param name="idx1">The index of the 2nd public.</param>
<returns>
	-
</returns>
<remarks>
	Compares two public function entries, and if need-be, swaps them over.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_ComparePublics(idx0, idx1)
{
	idx0 = idx0 * 8 + AMX_HEADER_PUBLICS;
	idx1 = idx1 * 8 + AMX_HEADER_PUBLICS;
	new
		addr0 = AMX_BASE_ADDRESS + AMX_Read(idx0 + 4),
		addr1 = AMX_BASE_ADDRESS + AMX_Read(idx1 + 4);
	for ( ; ; )
	{
		switch (Hooks_CompareNextCell(addr0, addr1))
		{
			case -1:
			{
				// Swap them over.
				new
					tmpFunc = AMX_Read(idx0),
					tmpName = AMX_Read(idx0 + 4);
				AMX_Write(idx0, AMX_Read(idx1));
				AMX_Write(idx0 + 4, AMX_Read(idx1 + 4));
				AMX_Write(idx1, tmpFunc);
				AMX_Write(idx1 + 4, tmpName);
				return;
			}
			case 1:
			{
				// Already in order - good.
				return;
			}
			// case 0: // Loop.
		}
		addr0 += 4;
		addr1 += 4;
	}
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_SortPublics</summary>
<returns>
	-
</returns>
<remarks>
	Goes through the whole of the public functions table and sorts them all in
	to alphabetical order.  This is done as we move and rename some so we need
	to fix the virtual machine's binary search.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_SortPublics()
{
	// Count the number of still active functions.
	new
		diff = Hooks_CountInvalidPublics() * 8,
		oldCount = (AMX_HEADER_NATIVES - AMX_HEADER_PUBLICS) / 8;
	// Now I need to SORT the functions, and I have honestly no idea how to do
	// that.  Fortunately I don't actually need to move the strings themselves
	// around as they just sit nicely in the nametable; I only need to sort the
	// pointers.
	for (new i = 0; i != oldCount; ++i)
	{
		for (new j = i + 1; j != oldCount; ++j)
		{
			// This neatly moves all the functions with blanked names to the
			// start of the public functions table (which will soon be moved).
			Hooks_ComparePublics(i, j);
		}
	}
	// Move the start address UP to reduce the VM's search space.
	if (diff)
	{
		// Update stored values in y_amx so they reflect the new structure.
		AMX_Write(AMX_BASE_ADDRESS + 32, AMX_Read(AMX_BASE_ADDRESS + 32) + diff);
		AMX_HEADER_PUBLICS += diff;
		// I'd love to be able to update ZeeX's code as well, but I can't.
		// Issue pull request for this.
		ResetStaticAmxHeader();
	}
	// TODO: Inform the fixes2 plugin of the change.  That stores indexes, not
	// addresses so it needs to update itself (somehow - I don't actually know
	// HOW it will do this...)  Probably inform it first, store the addresses,
	// then inform it again to track down and replace those addresses.
}

/**--------------------------------------------------------------------------**\
<summary>Hooks_CountInvalidPublics</summary>
<returns>
	-
</returns>
<remarks>
	Counts the number of public functions that have had their names erased.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_CountInvalidPublics()
{
	new
		idx,
		buf,
		count;
	// Search for functions whose names start with nothing.
	while ((idx = AMX_GetPublicEntryPrefix(idx, buf, 0)))
	{
		++count;
	}
	P:4("Hooks_CountInvalidPublics: Invalid = %d", count);
	return count;
}

/**--------------------------------------------------------------------------**\
<summary>OnScriptInit</summary>
<returns>
	-
</returns>
<remarks>
	Call the main hook run code, then advance the ALS chain.
</remarks>
\**--------------------------------------------------------------------------**/

public OnScriptInit()
{
	P:1("Hooks_OnScriptInit called");
	state _ALS : _ALS_go;
	Hooks_DoAllHooks();
	P:1("Hooks_OnScriptInit chain");
	//DisasmDump("YSI_TEST.asm");
	HookChain_OnScriptInit();
	P:1("Hooks_OnScriptInit end");
	return 1;
}

HOOK_FORWARD:HookChain_OnScriptInit();
#if defined _ALS_OnScriptInit
	#undef OnScriptInit
#else
	#define _ALS_OnScriptInit
#endif
#define OnScriptInit(%0) HookChain_OnScriptInit(%0) <_ALS : _ALS_go>

