/*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright C 2011
	the Initial Developer. All Rights Reserved.

Contributors:
	Y_Less
	koolk
	JoeBullet/Google63
	g_aSlice/Slice
	Misiur
	samphunter
	tianmeta
	maddinat0r
	spacemud
	Crayder
	Dayvison
	Ahmad45123
	Zeex
	irinel1996
	Yiin-
	Chaprnks
	Konstantinos
	Masterchen09
	Southclaws
	PatchwerkQWER
	m0k1
	paulommu
	udan111

Thanks:
	JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
	ZeeX - Very productive conversations.
	koolk - IsPlayerinAreaEx code.
	TheAlpha - Danish translation.
	breadfish - German translation.
	Fireburn - Dutch translation.
	yom - French translation.
	50p - Polish translation.
	Zamaroht - Spanish translation.
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

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

enum E_CHAIN_HOOK
{
	E_CHAIN_HOOK_NAME[16],
	E_CHAIN_HOOK_VALUE
}

DEFINE_HOOK_RETURN__(OnPlayerCommandText, 0);

DEFINE_HOOK_RETURN__(OnRconCommand, 0);

// Create the default replacements.
DEFINE_HOOK_REPLACEMENT__(Checkpoint, CP );
DEFINE_HOOK_REPLACEMENT__(Container , Cnt);
DEFINE_HOOK_REPLACEMENT__(Inventory , Inv);
DEFINE_HOOK_REPLACEMENT__(Dynamic   , Dyn);
DEFINE_HOOK_REPLACEMENT__(TextDraw  , TD );
DEFINE_HOOK_REPLACEMENT__(Update    , Upd);
DEFINE_HOOK_REPLACEMENT__(Object    , Obj);
DEFINE_HOOK_REPLACEMENT__(Command   , Cmd);
DEFINE_HOOK_REPLACEMENT__(DynamicCP , DynamicCP);

enum E_HOOK_NAME_REPLACEMENT_DATA
{
	E_HOOK_NAME_REPLACEMENT_SHORT[16],
	E_HOOK_NAME_REPLACEMENT_LONG[16],
	E_HOOK_NAME_REPLACEMENT_MIN,
	E_HOOK_NAME_REPLACEMENT_MAX
}

static stock
	YSI_g_sReplacements[MAX_HOOK_REPLACEMENTS][E_HOOK_NAME_REPLACEMENT_DATA],
	YSI_g_sReplacementsLongOrder[MAX_HOOK_REPLACEMENTS],
	YSI_g_sReplacementsShortOrder[MAX_HOOK_REPLACEMENTS],
	YSI_g_sReplacePtr,
	YSI_g_sInitFSPtr,
	YSI_g_sInitFSIdx = -1,
	YSI_g_sInitFSRep,
	YSI_g_sInitGMPtr,
	YSI_g_sInitGMIdx = -1,
	YSI_g_sInitGMRep,
	YSI_g_sInitPublicDiff,
	YSI_g_sActiveHooks = 0,
	bool:YSI_g_sSortedOnce = false;

/*-------------------------------------------------------------------------*//**
 * <param name="name">Function name to modify.</param>
 * <remarks>
 *  Expands all name parts like "CP" and "Obj" to their full versions (in this
 *  example "Checkpoint" and "Object").
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Hooks_MakeLongName(name[64])
{
	new
		end = 0,
		i = 0,
		pos = -1,
		idx = YSI_g_sReplacementsShortOrder[0];
	while (i != YSI_g_sReplacePtr)
	{
		// Allow for multiple replacements of the same string.
		if ((pos = strfind(name, YSI_g_sReplacements[idx][E_HOOK_NAME_REPLACEMENT_SHORT], false, pos + 1)) == -1)
		{
			++i,
			idx = YSI_g_sReplacementsShortOrder[i];
		}
		// This assumes CamelCase.  If the letter immediately following the end
		// of the string is lower-case, then the short word found is not a
		// complete word and should not be replaced.
		else if ('a' <= name[(end = pos + YSI_g_sReplacements[idx][E_HOOK_NAME_REPLACEMENT_MIN])] <= 'z')
			continue;
		else
		{
			P:5("Found hook name replacement: %d, %s", pos, YSI_g_sReplacements[idx][E_HOOK_NAME_REPLACEMENT_SHORT]);
			// Found a complete word according to CamelCase rules.
			strdel(name, pos + 1, end),
			name[pos] = 0x80000000 | idx;
		}
	}
	// All the replacements have been found and marked.  Now actually insert.
	// If "end" is "0", it means that it was never assigned to within the loop
	// above, which means that no replacements were found.
	if (end)
	{
		// "pos" must be "-1" at the start of this loop.
		while (name[++pos])
		{
			P:7("Hooks_MakeLongName main loop: [%d] = 0x%04x%04x \"%s\"", pos, name[pos] >>> 16, name[pos] & 0xFFFF, name);
			if (name[pos] < '\0')
			{
				// Negative number instead of a character.  Used to indicate
				// where a replacement should be inserted.  They are not done
				// inline in the loop above because some replacements may be
				// contained within others - we don't want those to be both done
				// within each other.
				P:5("Inserting hook name replacement: %d, %s", pos, YSI_g_sReplacements[name[pos] & ~0x80000000][E_HOOK_NAME_REPLACEMENT_LONG]);
				P:6("Current character: 0x%04x%04x", name[pos] >>> 16, name[pos] & 0xFFFF);
				// It took me ages to find a bug in this code.  For some reason,
				// "strins" was packing the result.  This was because the value
				// in "name[pos]" was not a real character, so was seen as an
				// indication that the string was packed.  I fixed it by moving
				// the assignment to "name[pos]" above "strins".  So while the
				// two lines look independent, they aren't!
				i = name[pos] & ~0x80000000,
				name[pos] = YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_LONG];
				// Use the original "strins" - we know this string is not
				// packed, but it might sometimes look like it is.  The "fixed"
				// version is designed for working with packed strings, but thus
				// breaks on not packed strings that just look packed.
				#if defined BAD_strins
					BAD_strins
				#else
					strins
				#endif
						(name, YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_LONG + E_HOOK_NAME_REPLACEMENT_DATA:1], pos + 1);
				pos += YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_MAX] - 1;
				P:6("New string: %s", name);
			}
		}
	}
	// It is possible for the expansions to become TOO big.
	return Hooks_MakeShortName(name);
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Function name to modify.</param>
 * <remarks>
 *  Compresses function names when required to fit within 32 characters
 *  according to well defined rules (see "YSI_g_sReplacements").
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Hooks_MakeShortName(name[64])
{
	// Easy one.
	new
		len,
		pos = -1,
		idx = YSI_g_sReplacementsLongOrder[0];
	for (new i = 0; (len = strlen(name)) >= 32 && i != YSI_g_sReplacePtr; )
	{
		if ((pos = strfind(name, YSI_g_sReplacements[idx][E_HOOK_NAME_REPLACEMENT_LONG], false, pos + 1)) == -1)
		{
			++i,
			idx = YSI_g_sReplacementsLongOrder[i];
		}
		else
		{
			strdel(name, pos, pos + YSI_g_sReplacements[idx][E_HOOK_NAME_REPLACEMENT_MAX]),
			strins(name, YSI_g_sReplacements[idx][E_HOOK_NAME_REPLACEMENT_SHORT], pos);
		}
	}
	return len;
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">The string to get the hooked function name from.</param>
 * <returns>
 *  The input string without y_hooks name decorations.
 * </returns>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_IsolateName(string:name[])
{
	P:4("Hooks_IsolateName called");
	new
		pos = strfind(name, "@", false, 4);
	// Make "pos" a legal value inside the error message.
	if (pos == -1) P:E("Invalid hook name: %s", unpack(name), ++pos);
	name[pos] = '\0',
	strdel(name, 0, 4);
}

/*-------------------------------------------------------------------------*//**
 * <param name="preloads">Desination in which to store all the preloads.</param>
 * <param name="precount">Number of found preload libraries.</param>
 * <param name="size">Maximum number of libraries to store.</param>
 * <remarks>
 *  Some includes, like "fixes.inc" and anti-cheats MUST come before all other
 *  includes in order for everything to function correctly (at least fixes.inc
 *  must).  This function looks for these definitions:
 *
 *      PRE_HOOK(FIXES)
 *
 *  Which tell y_hooks that any "FIXES_" prefixed callbacks are part of one of
 *  these chains.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetPreloadLibraries(preloads[][E_CHAIN_HOOK], &precount, size = sizeof (preloads))
{
	P:4("Hooks_GetPreloadLibraries called");
	--size,
	precount = 0;
	new
		entry,
		idx;
	{
		new
			name[32 char],
			addr;
		while ((idx = AMX_GetPublicEntryPrefix(idx, entry, _A<@CO_>)))
		{
			if (precount == size)
			{
				P:E("y_hooks prehook array filled");
				break;
			}
			addr = AMX_Read(entry);
			AMX_ReadString(AMX_Read(entry + 4) + AMX_BASE_ADDRESS + 4, name),
			strunpack(preloads[precount][E_CHAIN_HOOK_NAME], name, 16),
			preloads[precount][E_CHAIN_HOOK_VALUE] = CallFunction(addr),
			++precount;
			if (strlen(name) > 15)
				P:E("Overflow in prehook name \"%s\"", unpack(name));
			// {
				// new buffer[32];
				// strunpack(buffer, name);
				// printf("preload: %s", buffer);
			// }
			// Remove this public from the publics table.  Means that future public
			// function calls will be faster by having a smaller search space.
			Hooks_InvalidateName(entry);
		}
	}
	// Sort the preload libraries.
	{
		new
			tmp[E_CHAIN_HOOK];
		for (entry = precount - 1; entry > 0; --entry)
		{
			for (idx = 0; idx != entry; ++idx)
			{
				if (preloads[idx][E_CHAIN_HOOK_VALUE] > preloads[idx + 1][E_CHAIN_HOOK_VALUE])
				{
					tmp = preloads[idx],
					preloads[idx] = preloads[idx + 1],
					preloads[idx + 1] = tmp;
				}
			}
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="preloads">Names of libraries that come before y_hooks.</param>
 * <param name="precount">Number of pre libraries.</param>
 * <param name="name">Name of the callback.</param>
 * <param name="hooks">Destination in which to store the headers.</param>
 * <param name="count">Number of headers found.</param>
 * <remarks>
 *  Finds all the AMX file headers for functions with a similar name to the
 *  given callback that should be called before (or near) the given callback.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetPreHooks(const preloads[][E_CHAIN_HOOK], precount, const name[64], hooks[], &count)
{
	P:4("Hooks_GetPreHooks called");
	new
		idx,
		lfunc[64];
	// Collect all the functions with something like this name.
	P:2("Hooks_GetPreHooks start: %s", unpack(name));
	do
	{
		strcat(lfunc, name),
		Hooks_MakeShortName(lfunc);
		P:5("Hooks_GetPreHooks: search = %s", unpack(lfunc));
		P:C(new oc = count;);
		if (AMX_GetPublicEntry(0, hooks[count], lfunc, true)) ++count;
		P:C(if (oc != count) { new buffer[32]; AMX_ReadString(AMX_Read(hooks[count] + 4) + AMX_BASE_ADDRESS, buffer); P:5("Hooks_GetPreHooks: found = %s", unpack(buffer)); });
		strcpy(lfunc, preloads[idx][E_CHAIN_HOOK_NAME]),
		strcat(lfunc, "_");
	}
	while (++idx <= precount);
}

/*-------------------------------------------------------------------------*//**
 * <param name="hooks">All the prehooks for this callback.</param>
 * <param name="num">The number of prehooks.</param>
 * <param name="ptr">A pointer to write the new stub address to.</param>
 * <param name="next">The pointer for the function called after y_hooks.</param>
 * <param name="name">The name of the callback being processed.</param>
 * <param name="nlen">Space available in the header to write text in.</param>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetPointerRewrite(const hooks[], num, &ptr, &next, const name[], nlen)
{
	P:4("Hooks_GetPointerRewrite called");
	P:5("Hooks_GetPointerRewrite: (%s), num: %d, hoks: %08x, %08x, %08x, %08x", name, num, AMX_Read(hooks[0]), AMX_Read(hooks[1]), AMX_Read(hooks[2]), AMX_Read(hooks[3]));
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

/*-------------------------------------------------------------------------*//**
 * <param name="stub">Starting address of the function.</param>
 * <returns>
 *  The address at which the actual code in this function starts.
 * </returns>
 * <remarks>
 *  This handles three cases.  Regular functions end instantly as found.
 *  Functions that start with a switch (even before "PROC") are assumed to be
 *  state-based functions, and we find the most likely state to be used (i.e. we
 *  remove all future state changes).
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetStubEntry(stub)
{
	P:4("Hooks_GetStubEntry called");
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

/*-------------------------------------------------------------------------*//**
 * <param name="name">The name of the callback (with y_hooks prefix).</param>
 * <param name="hooks">Array in which to store the function headers.</param>
 * <param name="idx">Current position in the AMX header.</param>
 * <param name="namelen">Min bound of space used by all these names.</param>
 * <returns>
 *  The number of hooks found.
 * </returns>
 * <remarks>
 *  The name of the function currently being processed is derived from the first
 *  found hook.  This means we already know of one hook, but to simplify the
 *  code we get that one again here.  Above we only know the name not the
 *  address.  Hence the "- 1" in "i = idx - 1" (to go back one function name).
 *
 *  Our "namelen" variable already contains the full length of the first found
 *  hook - this is the length of "name", plus N extra characters.  The following
 *  are all valid, and may occur when orders are played with:
 *
 *      @yH_OnX@
 *      @yH_OnX@1
 *      @yH_OnX@01
 *      @yH_OnX@024
 *      @yH_OnX@ZZZ
 *      @yH_OnX@999@024
 *
 *  If we want to get the EXACT space taken up by all these hook names we would
 *  need to get the string of the name in this function then measure it.  There
 *  is really no point in doing this - if we have a second we will always have
 *  enough space for our new names.  Instead, we assume that they are all just
 *
 *      @yH_OnX@
 *
 *  And add on that minimum length accordingly (plus 1 for the NULL character).
 *
 *  This length is used if the original callback doesn't exist but hooks do.  In
 *  that case we need to add the callback to the AMX header, and there is a tiny
 *  chance that the original name will be longer than one hook's name.  In that
 *  case, having two or more hooks will (AFAIK) always ensure that we have
 *  enough space to write the longer name.
 *
 *  If there is only one hook, no original function, and the name of the hook is
 *  shorter than the name of the original function then we have an issue and
 *  will have to do something else instead.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetAllHooks(const name[], hooks[], idx, &namelen, size = sizeof (hooks))
{
	P:4("Hooks_GetAllHooks called: %s %d", name, idx);
	// Start from the very start - repeats the first item.
	new
		len = strlen(name) + 1,
		count,
		tmpName[64];
	while ((idx = AMX_GetPublicEntryPrefix(idx, hooks[count], _A<@yH_>)))
	{
		AMX_GetStringFromEntry(hooks[count], tmpName),
		len = strlen(tmpName),
		strunpack(tmpName, tmpName),
		Hooks_IsolateName(tmpName),
		Hooks_MakeLongName(tmpName);
		// Check if the fully expanded name is the name.
		P:6("Hooks_GetAllHooks found: %s ?= %s %d", name, tmpName, idx);
		if (!strcmp(tmpName, name))
		{
			Hooks_InvalidateName(hooks[count]);
			// Record how much consecutive space we have to play with in the
			// AMX.  I'm slightly concerned that this code assumes that the
			// hooks are all consecutive, when they might not be thanks to
			// replacements.
			if (count) namelen += len; // The first hook was already counted.
			// Increment and count how many hooks of this type we have.
			if (++count == size)
			{
				P:W("Hooks_GetAllHooks: Potential overflow." "\n" \
"\n" \
"	`MAX_Y_HOOKS` is currently `%d`, recompile with a higher value for more hooks of a single callback:" "\n" \
"\n" \
"	#define MAX_Y_HOOKS (%d)" "\n" \
"\n" \
, MAX_Y_HOOKS, MAX_Y_HOOKS * 2);
				break;
			}
		}
	}
	return count;
}

_Y_HOOKS_STATIC stock Hooks_DoAllHooks()
{
	P:4("Hooks_DoAllHooks called");
	// Get the preloaders.
	new
		precount = 0,
		preloads[32][E_CHAIN_HOOK];
	Hooks_GetPreloadLibraries(preloads, precount);
	// Main loop
	new
		name[32],
		idx;
	// Get the next hook type.
	while ((idx = AMX_GetPublicNamePrefix(idx, name, _A<@yH_>)))
	{
		// Collect all the hooks of this function, and rewrite the call code.
		Hooks_Collate(preloads, precount, name, idx - 1);
	}
}

_Y_HOOKS_STATIC stock Hooks_Collate(const preloads[][E_CHAIN_HOOK], precount, const name[32], idx)
{
	P:4("Hooks_Collate called: %s %d", unpack(name), idx);
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
		sHooks[MAX_Y_HOOKS];
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
		hookCount = Hooks_GetAllHooks(sName, sHooks, idx, namelen),
		writePtr = sHooks[0], // Header for the first found hook.
		nextPtr,
		pc, ph[16];
	// Get the preloads.
	Hooks_GetPreHooks(preloads, precount, sName, ph, pc),
	// Get where in the chain we are being inserted.
	Hooks_GetPointerRewrite(ph, pc, writePtr, nextPtr, sName, namelen);
	// Add ALS hooks to the end of the list.
	if ((sHooks[hookCount] = nextPtr)) ++hookCount;
	// Write the code.
	Hooks_GenerateCode(sName, sHooks, hookCount, writePtr, pc > 1);
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the function to generate.</param>
 * <param name="hooks">All the functions to call.</param>
 * <param name="count">Number of functions to call.</param>
 * <param name="write">Where to write the new function's pointer.</param>
 * <param name="hasprehooks">Needs to call other stuff first.</param>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_GenerateCode(const name[64], const hooks[], count, write, bool:hasprehooks)
{
	P:4("Hooks_GenerateCode called");
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

/*-------------------------------------------------------------------------*//**
 * <param name="entry">The public function slot to destroy.</param>
 * <remarks>
 *  Basically, once we know a function has been included, wipe it from the AMX
 *  header.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_InvalidateName(entry)
{
	P:4("Hooks_InvalidateName called");
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

/*-------------------------------------------------------------------------*//**
 * <param name="name">The function to get the address pointer of.</param>
 * <param name="write">Destination variable.</param>
 * <returns>
 *  The address at which this function's pointer is stored in the AMX header, if
 *  the function exists of course.
 * </returns>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetFunctionWritePoint(const name[], &write)
{
	P:4("Hooks_GetFunctionWritePoint called");
	AMX_GetPublicEntry(0, write, name, true);
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">The function to get the default return of.</param>
 * <returns>
 *  The default return for a callback, normally 1.
 * </returns>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetDefaultReturn(const name[64])
{
	P:4("Hooks_GetDefaultReturn called");
	new
		dest[64] = "@y_H";
	strcat(dest, name);
	Hooks_MakeShortName(dest);
	new
		ptr;
	if (AMX_GetPublicEntry(0, ptr, dest, true))
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

/*-------------------------------------------------------------------------*//**
 * <param name="pointers">The hooks to link together.</param>
 * <param name="size">The number of functions in the array.</param>
 * <param name="ret">The default return.</param>
 * <param name="skipable">Can future hooks be ignored on -1?</param>
 * <returns>
 *  The number of bytes written to memory.
 * </returns>
 * <remarks>
 *  Generate some new code, very nicely :D.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_WriteFunction(const pointers[], const size, const ret = 1, const skipable = true)
{
	P:4("Hooks_WriteFunction called");
	if (size == 0)
	{
		P:E("Hooks_WriteFunction: size is 0");
		return 0;
	}
	new
		bool:multiple = size != 1,
		base = (AMX_HEADER_COD - AMX_BASE_ADDRESS) + AMX_REAL_ADDRESS,
		ctx[AsmContext];
	// Make sure the underlying system doesn't change without us.  Now supported
	// natively.
	CGen_UseCodeSpace(ctx);
	
	// Start of the function.
	@emit PROC                          // 1
	
	// Allocate space for our "ret" variable at "frm - 4" (may be unused).
	@emit PUSH.C        ret             // 3
	
	// Create the current active hooks stack at "frm - 8".
	@emit PUSH          ref(YSI_g_sActiveHooks) // 5
	@emit ADDR.pri      -8              // 7
	@emit STOR.pri      ref(YSI_g_sActiveHooks) // 9
	
	// Copy the stack to itself (MOVS).
	// Allocate space.
	@emit LOAD.S.pri    8               // 11
	@emit JZER.label    Hooks_NoStackCopy // 13
	@emit MOVE.alt                      // 14
	@emit LCTRL         4               // 16
	@emit SUB                           // 17
	@emit SCTRL         4               // 19
	@emit XCHG                          // 20
	
	if (Server_JITExists())
	{
		// Need to use memcpy to move about in the stack.
		@emit PUSH.C        4096
		@emit PUSH.pri
		@emit PUSH.C        0
		@emit LCTRL         5
		@emit ADD.C         12
		@emit PUSH.pri
		@emit PUSH.alt
		@emit PUSH.C        20
		@emit SYSREQ        "memcpy"
		@emit STACK         24
	}
	else
	{
		// The "MOVS" OpCode only takes a constant, not a variable, so we need
		// to generate self-modifying code (just to be UBER meta)!  This code is
		// generated AFTER the file is loaded so we bypass the data segment
		// checks and can freely write wherever we want.
		@emit STOR.pri      (CGen_GetCodeSpace() + (27 * 4)) // 22
		
		// Do the copying.  "alt" is already "STK", load the "FRM" offset.
		@emit LCTRL         5           // 24
		@emit ADD.C         12          // 26
		// This is the instruction we want to modify...
		@emit MOVS          0           // 28 (- 1) = 27 (see above).
	}
	@emit Hooks_NoStackCopy:
	
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
				@emit JSLESS.label  Hooks_EndCall // 5
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
			@emit JUMP.label    Hooks_SkipInvert    // 10
			// This is the point the large "JSLESS" above goes to.
			// -1 = 0, -2 = 1
			@emit Hooks_EndCall:
			@emit INVERT
		}
	}
	else if (skipable)
	{
		// Still need this code as they may hook a function that doesn't exist,
		// but we still need to correctly process -1 or -2.
		@emit CALL          (AMX_Read(pointers[0]) + base)
		@emit ZERO.alt
		@emit JSGEQ.label   Hooks_SkipInvert
		@emit INVERT
	}
	else
	{
		// Just replace the original (turns out, this takes no code).  Basically
		// just discard everything we've written so far (reclaims the memory).
		return 0;
	}
	
	@emit Hooks_SkipInvert:
	
	// This is the point the small "JUMP" above goes to.
	@emit MOVE.alt
	
	// Pop from the active hooks stack.
	@emit LOAD.S.pri    -8
	@emit STOR.pri      ref(YSI_g_sActiveHooks)
	
	// Remove the whole stack then get the return value.
	@emit LCTRL         5
	@emit SCTRL         4
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

/*-------------------------------------------------------------------------*//**
 * <param name="addr0">The 1st address to read.</param>
 * <param name="addr1">The 2nd address to read.</param>
 * <returns>
 *  -1 - The first address is bigger.
 *  0  - The addresses are the same
 *  1  - The second address is bigger.
 * </returns>
 * <remarks>
 *  Reads two addresses, converts them to big endian, and compares them as four
 *  characters of a string at once.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_CompareNextCell(addr0, addr1)
{
//	P:4("Hooks_CompareNextCell called");
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

/*-------------------------------------------------------------------------*//**
 * <param name="idx0">The index of the 1st public.</param>
 * <param name="idx1">The index of the 2nd public.</param>
 * <remarks>
 *  Compares two public function entries, and if need-be, swaps them over.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_ComparePublics(idx0, idx1)
{
//	P:4("Hooks_ComparePublics called");
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

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Goes through the whole of the public functions table and sorts them all in
 *  to alphabetical order.  This is done as we move and rename some so we need
 *  to fix the virtual machine's binary search.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_SortPublics()
{
	P:4("Hooks_SortPublics called");
	// Count the number of still active functions.
	YSI_g_sInitPublicDiff = Hooks_CountInvalidPublics() * 8;
	new
		oldCount = (AMX_HEADER_NATIVES - AMX_HEADER_PUBLICS) / 8;
	// Now I need to SORT the functions, and I have honestly no idea how to do
	// that.  Fortunately I don't actually need to move the strings themselves
	// around as they just sit nicely in the nametable; I only need to sort the
	// pointers.
	for (new i = oldCount - 1; i > 0; --i)
	{
		for (new j = 0; j != i; ++j)
		{
			// This neatly moves all the functions with blanked names to the
			// start of the public functions table (which will soon be moved).
			Hooks_ComparePublics(j, j + 1);
		}
	}
	// Move the start address UP to reduce the VM's search space.
	if (YSI_g_sInitPublicDiff)
	{
		// Update stored values in y_amx so they reflect the new structure.
		if (!Server_JITExists() || YSI_g_sSortedOnce)
		{
			AMX_Write(AMX_BASE_ADDRESS + 32, AMX_Read(AMX_BASE_ADDRESS + 32) + YSI_g_sInitPublicDiff);
			AMX_HEADER_PUBLICS += YSI_g_sInitPublicDiff;
			ResetStaticAmxHeader();
			YSI_g_sSortedOnce = true;
		}
	}
	// TODO: Inform the fixes2 plugin of the change.  That stores indexes, not
	// addresses so it needs to update itself (somehow - I don't actually know
	// HOW it will do this...)  Probably inform it first, store the addresses,
	// then inform it again to track down and replace those addresses.
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Counts the number of public functions that have had their names erased.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_CountInvalidPublics()
{
	P:4("Hooks_CountInvalidPublics called");
	new
		idx,
		buf,
		count;
	// Search for functions whose names start with nothing.
	while ((idx = AMX_GetPublicEntryPrefix(idx, buf, 0)))
		++count;
	P:4("Hooks_CountInvalidPublics: Invalid = %d", count);
	return count;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Call the main hook run code, then advance the ALS chain.
 * </remarks>
 *//*------------------------------------------------------------------------**/

// New stuff.
stock _Hooks_AddReplacement(const longName[], const shortName[])
{
	// MAY need to strip spaces off the input strings, but I don't think so.
	if (YSI_g_sReplacePtr == MAX_HOOK_REPLACEMENTS)
	{
		P:E("Insufficient space in the replacements table.");
		return;
	}
	strcpy(YSI_g_sReplacements[YSI_g_sReplacePtr][E_HOOK_NAME_REPLACEMENT_SHORT], shortName, 16),
	strcpy(YSI_g_sReplacements[YSI_g_sReplacePtr][E_HOOK_NAME_REPLACEMENT_LONG] , longName , 16),
	YSI_g_sReplacements[YSI_g_sReplacePtr][E_HOOK_NAME_REPLACEMENT_MIN] = strlen(shortName),
	YSI_g_sReplacements[YSI_g_sReplacePtr][E_HOOK_NAME_REPLACEMENT_MAX] = strlen(longName),
	YSI_g_sReplacementsLongOrder[YSI_g_sReplacePtr] = YSI_g_sReplacePtr,
	YSI_g_sReplacementsShortOrder[YSI_g_sReplacePtr] = YSI_g_sReplacePtr,
	++YSI_g_sReplacePtr;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Once all the replacement strings have been found, sort them by the length of
 *  the short versions of the strings.  This is so that the longest (and special
 *  case, e.g. "DynamicCP"-> "DynamicCP") replacements are always done first.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Hooks_SortReplacements()
{
	new
		idx0,
		idx1,
		temp;
	for (new i = YSI_g_sReplacePtr - 1; i > 0; --i)
	{
		for (new j = 0; j != i; ++j)
		{
			// Sort the strings in order of their short replacement.
			idx0 = YSI_g_sReplacementsShortOrder[j],
			idx1 = YSI_g_sReplacementsShortOrder[j + 1];
			if (YSI_g_sReplacements[idx0][E_HOOK_NAME_REPLACEMENT_MIN] < YSI_g_sReplacements[idx1][E_HOOK_NAME_REPLACEMENT_MIN])
			{
				temp = YSI_g_sReplacementsShortOrder[j],
				YSI_g_sReplacementsShortOrder[j] = YSI_g_sReplacementsShortOrder[j + 1],
				YSI_g_sReplacementsShortOrder[j + 1] = temp;
			}
			// Sort the strings in order of their long replacement.
			idx0 = YSI_g_sReplacementsLongOrder[j],
			idx1 = YSI_g_sReplacementsLongOrder[j + 1];
			if (YSI_g_sReplacements[idx0][E_HOOK_NAME_REPLACEMENT_MAX] < YSI_g_sReplacements[idx1][E_HOOK_NAME_REPLACEMENT_MAX])
			{
				temp = YSI_g_sReplacementsLongOrder[j],
				YSI_g_sReplacementsLongOrder[j] = YSI_g_sReplacementsLongOrder[j + 1],
				YSI_g_sReplacementsLongOrder[j + 1] = temp;
			}
		}
	}
	P:C(for (new i = 0 ; i != YSI_g_sReplacePtr; ++i) P:0("Hook Replacement: %d, %d, %s, %s", YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_MIN], YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_MAX], YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_SHORT], YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_LONG]););
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Call the main hook run code, then advance the ALS chain.
 * </remarks>
 * <transition keep="true" target="_ALS : _ALS_go"/>
 *//*------------------------------------------------------------------------**/

public OnCodeInit()
{
	P:1("Hooks_OnCodeInit called");
	state _ALS : _ALS_go;
	// Get the replacements.
	new
		idx,
		entry;
	if (Server_JITExists())
	{
		// Get the indexes of the startup functions that get recorded before the
		// JIT plugin compiles, but called after it.  We thus need to fiddle the
		// hooking to ensure that the correct functions are always called.
		YSI_g_sInitFSIdx = funcidx("OnFilterScriptInit");
		YSI_g_sInitGMIdx = funcidx("OnGameModeInit");
	}
	// Loop over the redefinition functions and call them to have them call the
	// "_Hooks_AddReplacement" function above.  If we were being REALLY clever,
	// these functions could be removed from the public functions table
	// afterwards (there is already code in y_hooks for this) to reduce is size.
	while ((idx = AMX_GetPublicEntryPrefix(idx, entry, _A<@_yH>)))
	{
		// From "amx\dynamic_call.inc" - check it is included in "y_hooks.inc".
		CallFunction(AMX_Read(entry));
		Hooks_InvalidateName(entry);
	}
	Hooks_SortReplacements();
	Hooks_DoAllHooks();
	// Remove a few other superfluous publics.
	while ((idx = AMX_GetPublicEntryPrefix(idx, entry, _A<_@_y>)))
		Hooks_InvalidateName(entry);
	while ((idx = AMX_GetPublicEntryPrefix(idx, entry, _A<@CO_>)))
		Hooks_InvalidateName(entry);
	Hooks_SortPublics();
	P:1("Hooks_OnCodeInit chain");
	// Dump the generated callbacks for debugging.
	//DisasmDump("YSI_TEST.asm");
	#if defined Hooks_OnCodeInit
		Hooks_OnCodeInit();
	#endif
	P:1("Hooks_OnCodeInit end");
	if (Server_JITExists())
		Hooks_RepairJITInit();
	return 1;
}

#undef OnCodeInit
#define OnCodeInit Hooks_OnCodeInit
#if defined Hooks_OnCodeInit
	forward Hooks_OnCodeInit();
#endif

/**--------------------------------------------------------------------------**\
<summary>Hooks_RepairJITInit</summary>
<returns>
	-
</returns>
<remarks>
	When using the JIT, the initialisation functions may have already had their
	indexes looked up prior to calling the plugin.  It that case we need to keep
	the index constant, even if a different public is now in that slot.
	
	The stub is the function put in to that index, which redirects the first
	call to one of those publics to the correct place and restores whatever
	public was previously in that slot.
</remarks>
\**--------------------------------------------------------------------------**/

_Y_HOOKS_STATIC _Hooks_RepairStub()
{
	AMX_Write(AMX_HEADER_PUBLICS + YSI_g_sInitFSIdx * 8, YSI_g_sInitFSRep);
	AMX_Write(AMX_HEADER_PUBLICS + YSI_g_sInitGMIdx * 8, YSI_g_sInitGMRep);
	// Move the header up for searching.
	if (YSI_g_sInitPublicDiff)
	{
		AMX_Write(AMX_BASE_ADDRESS + 32, AMX_Read(AMX_BASE_ADDRESS + 32) + YSI_g_sInitPublicDiff);
		AMX_HEADER_PUBLICS += YSI_g_sInitPublicDiff;
		ResetStaticAmxHeader();
		YSI_g_sSortedOnce = true;
	}
}

_Y_HOOKS_STATIC _Hooks_RepairStubFS()
{
	_Hooks_RepairStub();
	#emit PUSH.C              0
	#emit LCTRL               6
	#emit ADD.C               36
	#emit LCTRL               8
	#emit PUSH.pri
	#emit LOAD.pri            YSI_g_sInitFSPtr
	#emit SCTRL               6
	return 1;
}

_Y_HOOKS_STATIC _Hooks_RepairStubGM()
{
	_Hooks_RepairStub();
	#emit PUSH.C              0
	#emit LCTRL               6
	#emit ADD.C               36
	#emit LCTRL               8
	#emit PUSH.pri
	#emit LOAD.pri            YSI_g_sInitGMPtr
	#emit SCTRL               6
	return 1;
}

_Y_HOOKS_STATIC Hooks_RepairJITInit()
{
	if (FALSE)
	{
		_Hooks_RepairStubFS();
		_Hooks_RepairStubGM();
	}
	// The pointer at this index needs to remain constant.  Replace it with a
	// pointer to a stub that resets the pointer then calls the real init hook.
	YSI_g_sInitFSPtr = GetPublicAddressFromName("OnFilterScriptInit");
	YSI_g_sInitGMPtr = GetPublicAddressFromName("OnGameModeInit");
	new
		base,
		stub;
	base = AMX_HEADER_PUBLICS + YSI_g_sInitFSIdx * 8;
	#emit CONST.pri           _Hooks_RepairStubFS
	#emit STOR.S.pri          stub
	YSI_g_sInitFSRep = AMX_Read(base),
	AMX_Write(base, stub);
	base = AMX_HEADER_PUBLICS + YSI_g_sInitGMIdx * 8;
	#emit CONST.pri           _Hooks_RepairStubGM
	#emit STOR.S.pri          stub
	YSI_g_sInitGMRep = AMX_Read(base),
	AMX_Write(base, stub);
}

#if !defined _ALS_numargs
	native BAD_numargs() = numargs;
#endif

stock Hooks_NumArgs()
{
	// Awkward code that allows us to jump backwards.  It might appear that this
	// code pushes something on the stack before the JZER that is never removed,
	// but labels reset the stack always so it gets unconditionally wiped out.
	#emit LOAD.S.alt          0
Hooks_NumArgs_load:
	#emit CONST.pri           8
	#emit ADD
	#emit LOAD.I
	#emit ZERO.alt
	#emit PUSH.pri
	#emit SGEQ
	#emit LREF.S.alt          0
	#emit JZER                Hooks_NumArgs_load
	#emit POP.pri
	#emit SHR.C.pri           2
	#emit RETN
	// Ideal code, that can't be used due to having a forward jump.
/*	#emit LOAD.S.pri          0
	#emit ADD.C               8
	#emit LOAD.I
	#emit ZERO.alt
	#emit JSLESS              Hooks_NumArgs_negative
	#emit SHR.C.pri           2
	#emit RETN
Hooks_NumArgs_negative:
	#emit LREF.S.pri          0
	#emit ADD.C               8
	#emit LOAD.I
	#emit SHR.C.pri           2
	#emit RETN*/
	__COMPILER_NAKED
}

#if defined _ALS_numargs
	#undef numargs
#else
	#define _ALS_numargs
#endif
#define numargs Hooks_NumArgs

static stock Hooks_Ordinal(n)
{
	new str[8];
	valstr(str, n);
	switch (n % 100)
	{
	case 11, 12, 13:
		strcat(str, "th");
	default:
		switch (n % 10)
		{
		case 1:
			strcat(str, "st");
		case 2:
			strcat(str, "nd");
		case 3:
			strcat(str, "rd");
		default:
			strcat(str, "th");
		}
	}
	return str;
}

public OnRuntimeError(code, &bool:suppress)
{
	#if defined Hooks_OnRuntimeError
		Hooks_OnRuntimeError(code, suppress);
	#endif
	if (!suppress)
	{
		// TODO: y_hooks relies on the parameter counts being mangled, so we
		// need to restore them after the current execution.  That's going to be
		// tricky.  First we need to work out where in the stack the code will
		// jump after this error is resolved, which will be wherever the current
		// `CallLocalFunction` returns to, or nowhere for a callback.  The
		// latter is easy because it means we have no work to do.  The former
		// isn't.
		//
		// Tiny tiny crashdetect overhead in every hook stub:
		//
		//   #emit PUSH        YSI_g_sActiveHooks
		//   #emit ADDR.pri    -8
		//   #emit STOR.pri    YSI_g_sActiveHooks
		//
		// This makes a stack of active hooks.  When a crash occurs, we walk
		// this stack and fix up all the parameter counts.
		new
			cur = YSI_g_sActiveHooks;
		for (new i; cur; cur = AMX_Read(cur))
		{
			if (++i == 1)
			{
				printf("[debug]");
				printf("[debug] Parameter count corrections:");
				printf("[debug]");
			}
			// Not 8, because `cur` is `- 8`.
			printf("[debug] The %s mangled argments (e.g. `<1073741823 arguments>`) below should read `<%d arguments>`", Hooks_Ordinal(i), AMX_Read(cur + 16) / 4);
			//// Get the current parameter count.
			//printf("count: %d", count);
			//// Write this out to the lower parameter count copy.
			//AMX_Write(cur - count - 4, count);
			//// Fixed.
		}
		if (YSI_g_sActiveHooks)
		{
			printf("[debug]");
			// Blank the active hooks value.  If this is the only public, this
			// will reset it after the public is foribly ended.  If it isn't, it
			// will be reset to a correct value when the next still active hook
			// ends.  This is only a problem if there are two crashes at once,
			// then the second corrections won't get displayed.
			YSI_g_sActiveHooks = 0;
		}
		//new trace[32];
		//GetStackTrace(trace);
		//PrintStackTrace(trace);
	}
	return 1;
}

// No ALS check because it is done in `y_scriptinit`.
#undef OnRuntimeError
#define OnRuntimeError Hooks_OnRuntimeError

#if defined Hooks_OnRuntimeError
	forward Hooks_OnRuntimeError(code, &bool:suppress);
#endif

