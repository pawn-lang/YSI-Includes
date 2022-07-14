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
	Portions created by the Initial Developer are Copyright (c) 2022
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
	Cheaterman

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

// Create the default replacements.  I try to avoid defining replacements for
// the words `Player` and `Vehicle` - they're too important and fundamental.
DEFINE_HOOK_REPLACEMENT__(Checkpoint, CP );
DEFINE_HOOK_REPLACEMENT__(Collisions, Col);
DEFINE_HOOK_REPLACEMENT__(Container , Cnt);
DEFINE_HOOK_REPLACEMENT__(Inventory , Inv);
DEFINE_HOOK_REPLACEMENT__(TextDraw  , TD );
DEFINE_HOOK_REPLACEMENT__(Command   , Cmd);
DEFINE_HOOK_REPLACEMENT__(Dynamic   , Dyn);
DEFINE_HOOK_REPLACEMENT__(Action    , Act);
DEFINE_HOOK_REPLACEMENT__(Object    , Obj);
DEFINE_HOOK_REPLACEMENT__(Update    , Upd);

// SPECIAL HACK!  The streamer plugin already shortens "Checkpoint" to "CP", without this line
// y_hooks will try to expand it again to `OnPlayerEnterDynamicCheckpoint`, which is a valid
// callback name, but the wrong one.  Thus we prevent the final expansion with this seemingly
// pointless replacement.  This is an internal detail you don't really need to worry about.
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
	YSI_g_sReplacePtr = 0,
	YSI_g_sInitFSPtr = 0,
	YSI_g_sInitFSIdx = -1,
	YSI_g_sInitFSRep = 0,
	YSI_g_sInitGMPtr = 0,
	YSI_g_sInitGMIdx = -1,
	YSI_g_sInitGMRep = 0,
	YSI_g_sInitPublicDiff = 0,
	YSI_g_sActiveHooks = 0,
	bool:YSI_g_sSortedOnce = false,
	YSI_g_sName[Y_HOOKS_MAX_NAME],
	YSI_g_sHooks[MAX_Y_HOOKS],
	YSI_g_sCount = 0,
	YSI_g_sAddress = 0;

/*-------------------------------------------------------------------------*//**
 * <param name="name">Function name to modify.</param>
 * <remarks>
 *  Expands all name parts like "CP" and "Obj" to their full versions (in this
 *  example "Checkpoint" and "Object").
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Hooks_MakeLongName(name[Y_HOOKS_MAX_NAME])
{
	new
		end = 0,
		i = 0,
		pos = -1,
		idx = YSI_g_sReplacementsShortOrder[0];
	for ( ; ; )
	{
		// Allow for multiple replacements of the same string.
		if ((pos = strfind(name, YSI_g_sReplacements[idx][E_HOOK_NAME_REPLACEMENT_SHORT], false, pos + 1)) == -1)
		{
			// This code does assume that there's at least 1 replacement.
			if (++i == YSI_g_sReplacePtr)
			{
				break;
			}
			idx = YSI_g_sReplacementsShortOrder[i];
		}
		// This assumes CamelCase.  If the letter immediately following the end
		// of the string is lower-case, then the short word found is not a
		// complete word and should not be replaced.
		else if ('a' <= name[(end = pos + YSI_g_sReplacements[idx][E_HOOK_NAME_REPLACEMENT_MIN])] <= 'z')
		{
			continue;
		}
		else
		{
			Debug_Print5("Found hook name replacement: %d, %s", pos, YSI_g_sReplacements[idx][E_HOOK_NAME_REPLACEMENT_SHORT]);
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
			Debug_Print7("Hooks_MakeLongName main loop: [%d] = 0x%04x%04x \"%s\"", pos, name[pos] >>> 16, name[pos] & 0xFFFF, name);
			if (name[pos] < '\0')
			{
				// Negative number instead of a character.  Used to indicate
				// where a replacement should be inserted.  They are not done
				// inline in the loop above because some replacements may be
				// contained within others - we don't want those to be both done
				// within each other.
				Debug_Print5("Inserting hook name replacement: %d, %s", pos, YSI_g_sReplacements[name[pos] & ~0x80000000][E_HOOK_NAME_REPLACEMENT_LONG]);
				Debug_Print6("Current character: 0x%04x%04x", name[pos] >>> 16, name[pos] & 0xFFFF);
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
				Debug_Print6("New string: %s", name);
			}
		}
	}
	// It is possible for the expansions to become TOO big.
	return Hooks_MakeShortName(name);
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Function name to modify.</param>
 * <remarks>
 *  Compresses function names when required to fit within FUNCTION_LENGTH characters
 *  according to well defined rules (see "YSI_g_sReplacements").
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Hooks_MakeShortName(name[Y_HOOKS_MAX_NAME])
{
	// Easy one.
	new
		len = 0,
		pos = -1,
		idx = YSI_g_sReplacementsLongOrder[0];
	// Special fixes.inc hack.  Needs a half-case-sensitive check.
	//if (!strcmp(name, "On_On", true, 5))
	if ((name[0] | 0x20 == 'o') && (name[1] | 0x20 == 'n') && (name[2] == '_') && (name[3] == 'O') && (name[4] == 'n'))
	{
		strdel(name, 3, 5);
	}
	for (new i = 0; (len = strlen(name)) >= FUNCTION_LENGTH && i != YSI_g_sReplacePtr; )
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
	// Hard-code initialisation hooks, because they don't work too well in the
	// middle of the initialisation itself.
#if _YSI_SAFE_STARTUP || defined FILTERSCRIPT
	if (!strcmp(name, "OnFilterScriptInit"))
	{
		// Only needs renaming in filterscripts.
		name = "OnScriptInit@C";
		len = 14;
	}
#endif
#if _YSI_SAFE_STARTUP || !defined FILTERSCRIPT
	if (!strcmp(name, "OnGameModeInit"))
	{
		// Only needs renaming in gamemodes.
		name = "OnScriptInit@E";
		len = 14;
	}
#endif
	return len;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  This is the old version of <c>AMX_GetPublicEntry</c> that doesn't use a
 *  binary search, so is slower but more resiliant in this code which shuffles
 *  things around.  Also optimised for the local simple known use-case.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock bool:Hooks_GetPublicEntry(&buffer, const pattern[])
{
	new
		quick = (pattern[0]) | (pattern[1] << 8) | (pattern[2] << 16) | (pattern[3] << 24),
		//tmp,
		addr = 0,
		pos = AMX_HEADER_PUBLICS + 4,
		str[FUNCTION_LENGTH];
	do
	{
		#emit LREF.S.pri                pos
		#emit LOAD.alt                  AMX_BASE_ADDRESS
		#emit ADD
		#emit STOR.S.pri                addr
		//tmp = AMX_Read(addr);
		//printf("tmp = %08x, quick = %08x", tmp, quick);
		if (AMX_Read(addr) == quick)
		{
			AMX_ReadString(addr, str);
			if (strcmp(str, pattern) == 0)
			{
				buffer = pos - 4;
				return true;
			}
		}
		pos += 8;
	}
	while (pos < AMX_HEADER_NATIVES);
	return false;
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
	Debug_Print4("Hooks_GetPreloadLibraries called");
	--size,
	precount = 0;
	new
		publicTableEntry = 0,
		idx = 0;
	{
		new
			name[FUNCTION_LENGTH char],
			addr = 0;
		// This is called before we start mangling names, so no binary search
		// danger yet.
		while ((idx = AMX_GetPublicEntryPrefix(idx, publicTableEntry, _A<@CO_>)))
		{
			if (precount == size)
			{
				Debug_Error("y_hooks prehook array filled");
				break;
			}
			addr = AMX_Read(publicTableEntry);
			AMX_ReadString(AMX_Read(publicTableEntry + 4) + AMX_BASE_ADDRESS + 4, name),
			strunpack(preloads[precount][E_CHAIN_HOOK_NAME], name, 16),
			preloads[precount][E_CHAIN_HOOK_VALUE] = CallFunction(addr),
			++precount;
			if (strlen(name) > 15)
				Debug_Error("Overflow in prehook name \"%s\"", Unpack(name));
			// {
				// new buffer[FUNCTION_LENGTH];
				// strunpack(buffer, name);
				// printf("preload: %s", buffer);
			// }
			// Remove this public from the publics table.  Means that future public
			// function calls will be faster by having a smaller search space.
			Hooks_InvalidatePointer(publicTableEntry);
		}
	}
	// Sort the preload libraries.
	{
		new
			tmp[E_CHAIN_HOOK];
		for (publicTableEntry = precount - 1; publicTableEntry > 0; --publicTableEntry)
		{
			for (idx = 0; idx != publicTableEntry; ++idx)
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

_Y_HOOKS_STATIC stock Hooks_GetPreHooks(const preloads[][E_CHAIN_HOOK], precount, hooks[], &count)
{
	Debug_Print4("Hooks_GetPreHooks called");
	new
		idx = 0,
		lfunc[Y_HOOKS_MAX_NAME];
	// Collect all the functions with something like this name.
	Debug_Print2("Hooks_GetPreHooks start: %s", Unpack(YSI_g_sName));
	do
	{
		strcat(lfunc, YSI_g_sName),
		Hooks_MakeShortName(lfunc);
		Debug_Print5("Hooks_GetPreHooks: search = %s", Unpack(lfunc));
		Debug_Code1{new oc = count;}
		// Needs to be binary search safe, i.e. use fallback code.
		if (Hooks_GetPublicEntry(hooks[count], lfunc)) ++count;
		Debug_Code1{if (oc != count) { new buffer[FUNCTION_LENGTH]; AMX_ReadString(AMX_Read(hooks[oc] + 4) + AMX_BASE_ADDRESS, buffer); strunpack(buffer, buffer); Debug_Print5("Hooks_GetPreHooks: found = %s", buffer); }}
		StrCpy(lfunc, preloads[idx][E_CHAIN_HOOK_NAME]),
		strcat(lfunc, __COMPILER_UNPACK"_");
	}
	while (++idx <= precount);
}

/*-------------------------------------------------------------------------*//**
 * <param name="hooks">All the prehooks for this callback.</param>
 * <param name="num">The number of prehooks.</param>
 * <param name="ptr">A pointer to write the new stub address to.</param>
 * <param name="next">The pointer for the function called after y_hooks.</param>
 * <param name="name">The name of the callback being processed.</param>
 * <param name="namelen">Space available in the header to write text in.</param>
 * <param name="namewrite">Position in the header to write text in.</param>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetPointerRewrite(const hooks[], num, &ptr, &next, &namelen, &namewrite)
{
	Debug_Print4("Hooks_GetPointerRewrite called");
	Debug_Print5("Hooks_GetPointerRewrite: (%s), num: %d, hooks: %08x, %08x, %08x, %08x", YSI_g_sName, num, AMX_Read(hooks[0]), AMX_Read(hooks[1]), AMX_Read(hooks[2]), AMX_Read(hooks[3]));
	switch (num)
	{
		case 0:
		{
			next = 0;
			new
				len = strlen(YSI_g_sName);
			if (namelen >= len)
			{
				// We don't have an existing callback with this name, only hooks.
				// We need to add the name of the callback to the AMX header,
				// and we have enough space in which to do so.
				new
					str[FUNCTION_LENGTH];
				strpack(str, YSI_g_sName),
				AMX_WriteString(namewrite, str, len);
				
				// Update the space available.
				namelen -= len + 1;
				namewrite += len + 1;
				
				// Save the new name's address.
				return namewrite - len - AMX_BASE_ADDRESS - 1;
			}
			else
			{
				Debug_Fatal("Could not write function name in \"Hooks_MakePublicPointer\".");
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
	return 0;
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
	Debug_Print4("Hooks_GetStubEntry called");
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
					else Debug_Error("y_hooks could not extract state stub jump");
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
			Debug_Error("y_hooks attempting to redirect a PROC hook");
		}
	}
	return 0;
}

_Y_HOOKS_STATIC stock Hooks_ExtractName(tmpName[Y_HOOKS_MAX_NAME], const name[], const callback[])
{
	new
		ch,
		i = 0,
		j = 0;
	// Extract the name, ignoring any `"`s.
	if (callback[0] == 0)
	{
		// Derive the callback from the function name.
		while (name[i] < '0')
		{
			++i;
		}
		while ((ch = name[i++]) >= '0' && ch != '@')
		{
			tmpName[j++] = ch;
		}
		tmpName[j] = '\0',
		Hooks_MakeLongName(tmpName);
		// Return the legacy order.
		//if (ch == '@')
		//{
		//	order = strval(name[i]);
		//}
	}
	else
	{
		// Specified an exact callback, use it.
		while (callback[i] < '0')
		{
			++i;
		}
		while ((ch = callback[i++]) >= '0')
		{
			tmpName[j++] = ch;
		}
		tmpName[j] = '\0';
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="address">The hook implementation location.</param>
 * <param name="name">The name of the implementation function.</param>
 * <param name="callback">The optional hooked callback name.</param>
 * <param name="order">Where in the list to call this hook.</param>
 * <param name="fallback">Is this an old style <c>hook</c> callback?</param>
 * <returns>
 *  Should this function be added to the current list of hooks?
 * </returns>
 * <remarks>
 *  Called from inside the <c>@yH_</c> functions, to register themselves.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:_Hooks_AddPublicHook(address, const name[], const callback[] = "", order = cellmin, fallback = false) <y_hooks_scan : y_hooks_scan_first>
{
	#pragma unused address, order
	// Found a new callback to set up.
	Hooks_ExtractName(YSI_g_sName, name, callback);
	if (fallback)
	{
		// Because this function is a fallback type, all the others we want to
		// find should also be fallbacks.
		state y_hooks_scan : y_hooks_scan_fallback;
		return true;
	}
	else
	{
		Debug_Fatal("`hook public` is not implemented yet.");
		return false;
	}
}

stock bool:_Hooks_AddPublicHook(address, const name[], const callback[] = "", order = cellmin, fallback = false) <y_hooks_scan : y_hooks_scan_fallback>
{
	if (order != cellmin)
	{
		Debug_Warning("`.order` is not implemented yet.");
	}
	new
		tmpName[Y_HOOKS_MAX_NAME];
	if (fallback)
	{
		Hooks_ExtractName(tmpName, name, callback);
		YSI_g_sAddress = address;
		return strcmp(tmpName, YSI_g_sName) == 0;
	}
	else
	{
		// Not a fallback function, but we're in the fallback lookup state.
		return false;
	}
}

stock bool:_Hooks_AddPublicHook(address, const name[], const callback[] = "", order = cellmin, fallback = false) <>
{
	#pragma unused address, name, callback, order, fallback
	// We don't care about these hook types in any other state.
	return false;
}

/*-------------------------------------------------------------------------*//**
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

_Y_HOOKS_STATIC stock Hooks_GetAllHooks(idx, &namelen)
{
	Debug_Print4("Hooks_GetAllHooks called: %s %d", YSI_g_sName, idx);
	// Start from the very start - repeats the first item.
	new
		addr = 0,
		count = 0,
		tmpName[Y_HOOKS_MAX_NAME];
	// This call is also binary search safe as it accepts `idx` so has a known
	// start point (thus isn't using a binary search unless `idx` is `0` in
	// which case no name mangling has happened yet anyway).
	while ((idx = AMX_GetPublicEntryPrefix(idx, addr, _A<@yH_>)))
	{
		YSI_g_sHooks[count] = addr;
		if (AMX_Read(addr) == 0)
		{
			// Not a valid pointer, previously removed.
			continue;
		}
		// Call the hook stub, and see if it thinks it is a valid hook.
		if (CallFunction(AMX_Read(addr)))
		{
			// Replace the function pointer to the implementation.
			AMX_Write(addr, YSI_g_sAddress);
			// Record how much consecutive space we have to play with in the
			// AMX.  I'm slightly concerned that this code assumes that the
			// hooks are all consecutive, when they might not be thanks to
			// replacements.
			AMX_GetStringFromEntry(YSI_g_sHooks[count], tmpName),
			namelen += strlen(tmpName);
			Debug_Print6("Hooks_GetAllHooks found: %s ?= %s %d", YSI_g_sName, tmpName, idx);
			// Increment and count how many hooks of this type we have.
			if (++count == sizeof (YSI_g_sHooks))
			{
				Debug_Warning("Hooks_GetAllHooks: Potential overflow." "\n" \
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
	Debug_Print4("Hooks_DoAllHooks called");
	// Get the preloaders.
	new
		precount = 0,
		preloads[32][E_CHAIN_HOOK];
	Hooks_GetPreloadLibraries(preloads, precount);
	// Main loop
	new
		entry,
		idx = 0,
		// This records the amount of space available in the nametable currently
		// taken up by the names of hooks that we are about to destroy, and
		// where they are located.  Now includes all hooks together.
		namelen = 0,
		namewrite = 0;
	// Get the next hook type.  This is binary-search safe because it is the
	// first call before any name mangling has happened.
	while ((idx = AMX_GetPublicEntryPrefix(idx, entry, _A<@yH_>)))
	{
		if (namewrite == 0)
		{
			namewrite = AMX_BASE_ADDRESS + AMX_Read(entry + 4);
		}
		entry = AMX_Read(entry);
		if (entry == 0)
		{
			// Not a valid pointer, previously removed.
			continue;
		}
		// Invoke the function, which will result in our callback being called
		// to get the base function name (in to `YSI_g_sName`).
		state y_hooks_scan : y_hooks_scan_first;
		CallFunction(entry);
		// Move back to the first hook in this group (the one we just called).
		--idx;
		// Collect all the hooks of this function, and rewrite the call code.
		Hooks_Collate(preloads, precount, idx, namelen, namewrite);
		// Because we decremented `idx` this will re-test the same slot but
		// that's good because we do an insertion sort so some publics may have
		// been moved up (they also may not, but that's not a problem because in
		// that case the `== 0` check above will trigger and skip the repeat).
	}
}

_Y_HOOKS_STATIC stock Hooks_Collate(const preloads[][E_CHAIN_HOOK], precount, idx, &namelen, &namewrite)
{
	Debug_Print4("Hooks_Collate called: %s %d", Unpack(AMX_GetStringFromEntry), idx);
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
	//
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
	// Get all the hooks of this type.  They are stored alphabetically.
	YSI_g_sCount = Hooks_GetAllHooks(idx, namelen);
	new
		writePtr = YSI_g_sHooks[0], // Header for the first found hook.
		nextPtr = 0,
		pc = 0,
		ph[16];
	// Get the preloads.
	Hooks_GetPreHooks(preloads, precount, ph, pc),
	// Get where in the chain we are being inserted.
	precount = Hooks_GetPointerRewrite(ph, pc, writePtr, nextPtr, namelen, namewrite);
	// Add ALS hooks to the end of the list.
	if ((YSI_g_sHooks[YSI_g_sCount] = nextPtr)) ++YSI_g_sCount;
	// Write the code.
	new
		funcPtr = Hooks_GenerateCode(writePtr, pc > 1);
	if (pc == 0)
	{
		// Insert the new header in to the correct location in the public
		// functions header.  There's no point using a binary search here
		// because we need to loop through all lower entries anyway to shift
		// them down, thus we may as well combine that with the search operation
		// and save a step.
		for (new str[FUNCTION_LENGTH]; ; )
		{
			nextPtr = AMX_Read(writePtr + 12),
			AMX_ReadString(nextPtr + AMX_BASE_ADDRESS, str, sizeof (str));
			if (strcmp(str, YSI_g_sName) > 0)
			{
				// Save the new name's address.
				AMX_Write(writePtr + 4, precount);
				break;
			}
			// Shift this entry up.
			AMX_Write(writePtr + 4, nextPtr),
			nextPtr = AMX_Read(writePtr + 8),
			AMX_Write(writePtr, nextPtr),
			writePtr += 8;
		}
	}
	// Save the function pointer again so it can be used by
	// the rewrite code.
	AMX_Write(writePtr, funcPtr);
}

/*-------------------------------------------------------------------------*//**
 * <param name="count">Number of functions to call.</param>
 * <param name="write">Where to write the new function's pointer.</param>
 * <param name="hasprehooks">Needs to call other stuff first.</param>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_GenerateCode(write, bool:hasprehooks)
{
	Debug_Print4("Hooks_GenerateCode called");
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
		size = Hooks_WriteFunction(Hooks_GetDefaultReturn(YSI_g_sName));
	Debug_Print4("Hooks_GenerateCode %32s called: %6d %6d %08x %d", YSI_g_sName, hasprehooks, size, hasprehooks ? (write - AMX_HEADER_COD) : (write - AMX_BASE_ADDRESS), CGen_GetCodeSpace());
	if (size)
	{
		//AMX_Write(write, 40);
		if (hasprehooks) write = CGen_GetCodeSpace() + AMX_REAL_DATA;
		else write = CGen_GetCodeSpace() - AMX_HEADER_COD;
		CGen_AddCodeSpace(size);
	}
	else
	{
		size = AMX_Read(YSI_g_sHooks[0]);
		if (hasprehooks) write = size + (AMX_REAL_DATA + AMX_HEADER_COD);
		else write = size;
	}
	return write;
}

/*-------------------------------------------------------------------------*//**
 * <param name="tableEntry">The public function slot to destroy.</param>
 * <remarks>
 *  Basically, once we know a function has been included, wipe it from the AMX
 *  header.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_InvalidatePointer(tableEntry)
{
	Debug_Print4("Hooks_InvalidatePointer called");
	AMX_Write(tableEntry, 0);
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
 * <param name="name">The function to get the default return of.</param>
 * <returns>
 *  The default return for a callback, normally 1.
 * </returns>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetDefaultReturn(const name[Y_HOOKS_MAX_NAME])
{
	Debug_Print4("Hooks_GetDefaultReturn called");
	new
		dest[Y_HOOKS_MAX_NAME] = __COMPILER_UNPACK"@y_H";
	strcat(dest, name);
	Hooks_MakeShortName(dest);
	new
		ptr = 0;
	// Needs to be binary search safe.
	if (Hooks_GetPublicEntry(ptr, dest))
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
 * <param name="ret">The default return.</param>
 * <param name="skipable">Can future hooks be ignored on -1?</param>
 * <returns>
 *  The number of bytes written to memory.
 * </returns>
 * <remarks>
 *  Generate some new code, very nicely :D.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_WriteFunction(const ret = 1, const skipable = true)
{
	Debug_Print4("Hooks_WriteFunction called");
	if (YSI_g_sCount == 0)
	{
		Debug_Error("Hooks_WriteFunction: size is 0");
		return 0;
	}
	new
		bool:multiple = YSI_g_sCount != 1,
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
	@emit PUSH          AMX_Ref(YSI_g_sActiveHooks) // 5
	@emit ADDR.pri      -8              // 7
	@emit STOR.pri      AMX_Ref(YSI_g_sActiveHooks) // 9
	
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
			@emit CALL          (AMX_Read(YSI_g_sHooks[i]) + base) // 2
			Hooks_InvalidatePointer(YSI_g_sHooks[i]);
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
			if (++i == YSI_g_sCount) break;
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
		@emit CALL          (AMX_Read(YSI_g_sHooks[0]) + base)
		Hooks_InvalidatePointer(YSI_g_sHooks[0]);
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
	@emit STOR.pri      AMX_Ref(YSI_g_sActiveHooks)
	
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
 * <remarks>
 *  Goes through the whole of the public functions table and moves those
 *  without valid pointers to the start, then moves the start address up to
 *  after them.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_CompressPublics()
{
	Debug_Print4("Hooks_CompressPublics called");
	// Count the number of still active functions.
	new
		read = AMX_HEADER_NATIVES,
		write = AMX_HEADER_NATIVES,
		tmp;
	do
	{
		read -= 8;
		tmp = AMX_Read(read);
		if (tmp)
		{
			AMX_Write(write - 8, tmp),
			
			// Check if we should skip it anyway (i.e. is it one of the prefixes
			// we want removed).
			tmp = AMX_Read(read + 4);
			switch (AMX_Read(tmp + AMX_BASE_ADDRESS))
			{
			#if !defined YSI_TESTS
			case _A<@y_H>:
				// This is conditional because some tests use it somewhere.
				continue;
			#endif
			case
				// These need to be on separate lines because they're extremely
				// complex macros that the compiler will give up on if they're
				// all on one line (due to line length limits).
				_A<@_y_>,
				_A<@CO_>,
				_A<@Hy_>,
				_A<@_Hy>:
				continue;
			}
			// Neither an invalid pointer nor a removed name.
			AMX_Write(write - 4, tmp),
			write -= 8;
		}
	}
	while (read != AMX_HEADER_PUBLICS);
	// Get the difference from the old to the new publics table.
	YSI_g_sInitPublicDiff = write - AMX_HEADER_PUBLICS;
	// Move the start address UP to reduce the VM's search space.
	if (YSI_g_sInitPublicDiff)
	{
		// Update stored values in y_amx so they reflect the new structure.
		if (!Server_JITExists() || YSI_g_sSortedOnce)
		{
			tmp = AMX_Read(AMX_BASE_ADDRESS + 32),
			AMX_Write(AMX_BASE_ADDRESS + 32, tmp + YSI_g_sInitPublicDiff),
			AMX_HEADER_PUBLICS += YSI_g_sInitPublicDiff,
			ResetStaticAmxHeader(),
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
 *  Call the main hook run code, then advance the ALS chain.
 * </remarks>
 *//*------------------------------------------------------------------------**/

// New stuff.
stock _Hooks_AddReplacement(const longName[], const shortName[])
{
	// MAY need to strip spaces off the input strings, but I don't think so.
	if (YSI_g_sReplacePtr == MAX_HOOK_REPLACEMENTS)
	{
		Debug_Error("Insufficient space in the replacements table.");
		return;
	}
	strunpack(YSI_g_sReplacements[YSI_g_sReplacePtr][E_HOOK_NAME_REPLACEMENT_SHORT], shortName, 16),
	strunpack(YSI_g_sReplacements[YSI_g_sReplacePtr][E_HOOK_NAME_REPLACEMENT_LONG], longName, 16),
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
		idx0 = 0,
		idx1 = 0,
		temp = 0;
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
	Debug_Code1{for (new i = 0 ; i != YSI_g_sReplacePtr; ++i) Debug_Print0("Hook Replacement: %d, %d, %s, %s", YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_MIN], YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_MAX], YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_SHORT], YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_LONG]);}
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Call the main hook run code, then advance the ALS chain.
 * </remarks>
 * <transition keep="true" target="_ALS : _ALS_go"/>
 *//*------------------------------------------------------------------------**/

public OnCodeInit()
{
	Debug_Print1("Hooks_OnCodeInit called");
	state _ALS : _ALS_go;
	new
		idx = 0,
		publicTableEntry = 0;
	{
		// Get the replacements.
		if (Server_JITExists())
		{
			// Get the indexes of the startup functions that get recorded before
			// the JIT plugin compiles, but called after it.  We thus need to
			// fiddle the hooking to ensure that the correct functions are
			// always called.
			YSI_g_sInitFSIdx = funcidx("OnFilterScriptInit");
			YSI_g_sInitGMIdx = funcidx("OnGameModeInit");
		}
		// Loop over the redefinition functions and call them to have them call
		// the "_Hooks_AddReplacement" function above.  If we were being REALLY
		// clever, these functions could be removed from the public functions
		// table afterwards (there is already code in y_hooks for this) to
		// reduce its size.  Binary search safe as it is first.
		while ((idx = AMX_GetPublicEntryPrefix(idx, publicTableEntry, _A<@_yH>)))
		{
			// From "amx\dynamic_call.inc" - check it is included in
			// "y_hooks.inc".
			CallFunction(AMX_Read(publicTableEntry));
			Hooks_InvalidatePointer(publicTableEntry);
		}
		Hooks_SortReplacements();
		Hooks_DoAllHooks();
		Debug_Print1("Hooks_OnCodeInit chain");
		// Dump the generated callbacks for debugging.
		//DisasmDump("YSI_TEST.asm");
	}

	#if defined Hooks_OnCodeInit
		Hooks_OnCodeInit();
	#endif
	
	Hooks_CompressPublics();
	Debug_Print1("Hooks_OnCodeInit end");
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
		new tmp = AMX_Read(AMX_BASE_ADDRESS + 32);
		AMX_Write(AMX_BASE_ADDRESS + 32, tmp + YSI_g_sInitPublicDiff),
		AMX_HEADER_PUBLICS += YSI_g_sInitPublicDiff,
		ResetStaticAmxHeader(),
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
		base = AMX_HEADER_PUBLICS + YSI_g_sInitFSIdx * 8,
		stub = 0;
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
	__pragma("naked");
}

#if defined _ALS_numargs
	#undef numargs
#else
	#define _ALS_numargs
#endif
#define numargs Hooks_NumArgs

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
		for (new i = 0; cur; cur = AMX_Read(cur))
		{
			if (++i == 1)
			{
				print("[debug]");
				print("[debug] Parameter count corrections:");
				print("[debug]");
			}
			// Not 8, because `cur` is `- 8`.
			printf("[debug] The %s mangled argments (e.g. `<1073741823 arguments>`) below should read `<%d arguments>`", ValstrWithOrdinal(i), AMX_Read(cur + 16) / 4);
			//// Get the current parameter count.
			//printf("count: %d", count);
			//// Write this out to the lower parameter count copy.
			//AMX_Write(cur - count - 4, count);
			//// Fixed.
		}
		if (YSI_g_sActiveHooks)
		{
			print("[debug]");
			// Blank the active hooks value.  If this is the only public, this
			// will reset it after the public is foribly ended.  If it isn't, it
			// will be reset to a correct value when the next still active hook
			// ends.  This is only a problem if there are two crashes at once,
			// then the second corrections won't get displayed.
			YSI_g_sActiveHooks = 0;
		}
		//new trace[FUNCTION_LENGTH];
		//GetStackTrace(trace);
		//PrintStackTrace(trace);
	}
	return 1;
}

#if defined _ALS_OnRuntimeError
	#undef OnRuntimeError
#else
	#define _ALS_OnRuntimeError
#endif
#define OnRuntimeError Hooks_OnRuntimeError

#if defined Hooks_OnRuntimeError
	forward Hooks_OnRuntimeError(code, &bool:suppress);
#endif

