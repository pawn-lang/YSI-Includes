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
	YSI_g_sBlockStart = 0,
	YSI_g_sBlockEnd = 0,
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
	YSI_g_sAddress = 0,
	YSI_g_sNPSBaseCall = 0,
	YSI_g_sNPSTrampoline = 0,
	YSI_g_sNPSReplace = 0,
	YSI_g_sNPSStack = 0,
	YSI_g_sTempRet = 0;

//#if !defined YSI_gYVA2_DoPush__
//stock YSI_gYVA2_DoPush__ = 0;
//#endif

/*-------------------------------------------------------------------------*//**
 * <param name="name">Function name to modify.</param>
 * <remarks>
 *   Expands all name parts like "CP" and "Obj" to their full versions (in this
 *   example "Checkpoint" and "Object").
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
			name[pos] = cellmin | idx;
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
				Debug_Print5("Inserting hook name replacement: %d, %s", pos, YSI_g_sReplacements[name[pos] & ~cellmin][E_HOOK_NAME_REPLACEMENT_LONG]);
				Debug_Print6("Current character: 0x%04x%04x", name[pos] >>> 16, name[pos] & 0xFFFF);
				// It took me ages to find a bug in this code.  For some reason,
				// "strins" was packing the result.  This was because the value
				// in "name[pos]" was not a real character, so was seen as an
				// indication that the string was packed.  I fixed it by moving
				// the assignment to "name[pos]" above "strins".  So while the
				// two lines look independent, they aren't!
				i = name[pos] & ~cellmin,
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
 *   Compresses function names when required to fit within FUNCTION_LENGTH
 *   characters according to well defined rules (see "YSI_g_sReplacements").
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
 * <param name="preloads">Desination in which to store all the preloads.</param>
 * <param name="precount">Number of found preload libraries.</param>
 * <param name="size">Maximum number of libraries to store.</param>
 * <remarks>
 *   Some includes, like "fixes.inc" and anti-cheats MUST come before all other
 *   includes in order for everything to function correctly (at least fixes.inc
 *   must).  This function looks for these definitions:
 *
 *      PRE_HOOK(FIXES)
 *
 *   Which tell y_hooks that any "FIXES_" prefixed callbacks are part of one of
 *   these chains.
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
			tmp = 0;
		// This is called before we start mangling names, so no binary search
		// danger yet.
		while ((idx = AMX_GetPublicEntryPrefix(idx, publicTableEntry, _A<@CO_>)))
		{
			if (precount == size)
			{
				Debug_Error("y_hooks prehook array filled");
				break;
			}
			AMX_GetStringFromEntry(publicTableEntry, name),
			strunpack(preloads[precount][E_CHAIN_HOOK_NAME], name[1], 16);
			#emit PUSH.C                    0
			#emit LCTRL                     __cip
			#emit ADD.C                     __9_cells
			#emit LCTRL                     __jit_jump
			#emit PUSH.pri
			#emit LREF.S.pri                publicTableEntry
			#emit SCTRL                     __cip
			#emit STOR.S.pri                tmp
			preloads[precount][E_CHAIN_HOOK_VALUE] = tmp;
			++precount;
			if (strlen(name) > 15)
			{
				Debug_Error("Overflow in prehook name \"%s\"", Unpack(name));
			}
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
	Debug_Print4("Hooks_GetPreloadLibraries ended");
}

/*-------------------------------------------------------------------------*//**
 * <param name="preloads">Names of libraries that come before y_hooks.</param>
 * <param name="precount">Number of pre libraries.</param>
 * <param name="name">Name of the callback.</param>
 * <param name="hooks">Destination in which to store the headers.</param>
 * <param name="count">Number of headers found.</param>
 * <remarks>
 *   Finds all the AMX file headers for functions with a similar name to the
 *   given callback that should be called before (or near) the given callback.
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
		Debug_CodeX{new oc = count;}
		// Needs to be binary search safe, i.e. use fallback code.
		if (AMX_GetPublicEntry(0, hooks[count], lfunc, true)) ++count;
		Debug_Code1{if (oc != count) { new buffer[FUNCTION_LENGTH]; AMX_GetStringFromEntry(hooks[oc], buffer); strunpack(buffer, buffer); Debug_Print5("Hooks_GetPreHooks: found = %s", buffer); }}
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
				AMX_WriteUnpackedString(namewrite, YSI_g_sName);
				
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
 *   The address at which the actual code in this function starts.
 * </returns>
 * <remarks>
 *   This handles three cases.  Regular functions end instantly as found.
 *   Functions that start with a switch (even before "PROC") are assumed to be
 *   state-based functions, and we find the most likely state to be used (i.e.
 *   we remove all future state changes).
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
		while (name{i} < '0')
		{
			++i;
		}
		while ((ch = name{i++}) >= '0' && ch != '@')
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
		while (callback{i} < '0')
		{
			++i;
		}
		while ((ch = callback{i++}) >= '0')
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
 *   Should this function be added to the current list of hooks?
 * </returns>
 * <remarks>
 *   Called from inside the <c>@yH_</c> functions, to register themselves.
 * </remarks>
 *//*------------------------------------------------------------------------**/

// Was `_Hooks_AddPublicHook`
stock _@Hy(address, const name[], const callback[] = "", order = cellmin, fallback = false) <y_hooks_scan : y_hooks_scan_determine_type>
{
	#pragma unused address, order
	// Found a new callback to set up.
	Hooks_ExtractName(YSI_g_sName, name, callback);
	if (fallback)
	{
		// Because this function is a fallback type, all the others we want to
		// find should also be fallbacks.
		return 1;
	}
	else
	{
		Debug_Fatal("`hook public` is not implemented yet.");
		return 0;
	}
}

stock _@Hy(address, const name[], const callback[] = "", order = cellmin, fallback = false) <y_hooks_scan : y_hooks_scan_legacy_hook>
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
		return 0;
	}
}

stock _@Hy(address, const name[], const callback[] = "", order = cellmin, fallback = false) <>
{
	#pragma unused address, name, callback, order, fallback
	// We don't care about these hook types in any other state.
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="idx">Current position in the AMX header.</param>
 * <param name="namelen">Min bound of space used by all these names.</param>
 * <returns>
 *   The number of hooks found.
 * </returns>
 * <remarks>
 *   The name of the function currently being processed is derived from the
 *   first found hook.  This means we already know of one hook, but to simplify
 *   the code we get that one again here.  Above we only know the name not the
 *   address.  Hence the "- 1" in "i = idx - 1" (to go back one function name).
 *
 *   Our "namelen" variable already contains the full length of the first found
 *   hook - this is the length of "name", plus N extra characters.  The
 *   following are all valid, and may occur when orders are played with:
 *
 *      @yH_OnX@
 *      @yH_OnX@1
 *      @yH_OnX@01
 *      @yH_OnX@024
 *      @yH_OnX@ZZZ
 *      @yH_OnX@999@024
 *
 *   If we want to get the EXACT space taken up by all these hook names we would
 *   need to get the string of the name in this function then measure it.  There
 *   is really no point in doing this - if we have a second we will always have
 *   enough space for our new names.  Instead, we assume that they are all just
 *
 *      @yH_OnX@
 *
 *   And add on that minimum length accordingly (plus 1 for the NULL character).
 *
 *   This length is used if the original callback doesn't exist but hooks do.
 *   In that case we need to add the callback to the AMX header, and there is a
 *   tiny chance that the original name will be longer than one hook's name.  In
 *   that case, having two or more hooks will (AFAIK) always ensure that we have
 *   enough space to write the longer name.
 *
 *   If there is only one hook, no original function, and the name of the hook
 *   is shorter than the name of the original function then we have an issue and
 *   will have to do something else instead.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_GetAllHooks(addr)
{
	Debug_Print4("Hooks_GetAllHooks called: %s %d", YSI_g_sName, addr);
	// Start from the very start - repeats the first item.
	new
		count = 0,
		tmp;
	// This call is also binary search safe as it accepts `idx` so has a known
	// start point (thus isn't using a binary search unless `idx` is `0` in
	// which case no name mangling has happened yet anyway).
	//while ((idx = AMX_GetPublicEntryPrefix(idx, addr, _A<@yH_>)))
	for ( ; addr != YSI_g_sBlockEnd; addr += 8)
	{
		if (AMX_Read(addr) == 0)
		{
			continue;
		}
		YSI_g_sHooks[count] = addr;
		// Call the hook stub, and see if it thinks it is a valid hook.
		#emit PUSH.C                    0
		#emit LCTRL                     __cip
		#emit ADD.C                     36
		#emit LCTRL                     __jit_jump
		#emit PUSH.pri
		#emit LREF.S.pri                addr
		#emit SCTRL                     __cip
		#emit STOR.S.pri                tmp
		if (tmp)
		{
			Debug_Print6("Hooks_GetAllHooks found: %s %d", YSI_g_sName, (addr - YSI_g_sBlockStart) / __defsize_cells);
			// Replace the function pointer to the implementation.
			AMX_Write(addr, YSI_g_sAddress);
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

_Y_HOOKS_STATIC stock Hooks_Collate(const preloads[][E_CHAIN_HOOK], precount, entry, &namelen, &namewrite)
{
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
	YSI_g_sCount = Hooks_GetAllHooks(entry);
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
			nextPtr = __32(AMX_Read(writePtr + (__defsize_cells + cellbytes)));
			if (nextPtr)
			{
				// Is this the insertion point?
				AMX_ReadPackedString(nextPtr + AMX_BASE_ADDRESS, str, sizeof (str));
				if (strcmp(str, YSI_g_sName) > 0)
				{
					// Save the new name's address.
					#if cellbits == 64
						// But only write 32 bits.
						pc = AMX_Read(writePtr + cellbytes),
						pc = (pc & 0xFFFFFFFF00000000) | (precount & 0x00000000FFFFFFFF),
						AMX_Write(writePtr + cellbytes, pc);
					#else
						AMX_Write(writePtr + cellbytes, precount);
					#endif
					break;
				}
			}
			// Shift this entry up.
			#if cellbits == 64
				// But only write 32 bits.
				pc = AMX_Read(writePtr + cellbytes),
				pc = (pc & 0xFFFFFFFF00000000) | (nextPtr & 0x00000000FFFFFFFF),
				AMX_Write(writePtr + cellbytes, pc);
			#else
				AMX_Write(writePtr + cellbytes, nextPtr);
			#endif
			nextPtr = AMX_Read(writePtr + __defsize_cells),
			AMX_Write(writePtr, nextPtr),
			writePtr += __defsize_cells;
		}
		
		// Mark that there are now fewer header hook entries because we
		// reused one for a proper callback.
		YSI_g_sBlockEnd -= __defsize_cells;
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
 *   Basically, once we know a function has been included, wipe it from the AMX
 *   header.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC stock Hooks_InvalidatePointer(tableEntry)
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
 *   The default return for a callback, normally 1.
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
	if (AMX_GetPublicEntry(0, ptr, dest, true))
	{
		// A "RET_OnWhatever" function exists - rationalise the return.
		//ptr = AMX_Read(ptr);
		#emit PUSH.C                    0
		#emit LCTRL                     __cip
		#emit ADD.C                     __9_cells
		#emit LCTRL                     __jit_jump
		#emit PUSH.pri
		#emit LREF.S.pri                ptr
		#emit SCTRL                     __cip
		#emit EQ.C.pri                  1
		#emit STOR.S.pri                ptr
		return ptr;
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
 *   The number of bytes written to memory.
 * </returns>
 * <remarks>
 *   Generate some new code, very nicely :D.
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
	@emit ADDR.pri      __local1_offset             // 7
	@emit STOR.pri      AMX_Ref(YSI_g_sActiveHooks) // 9
	
	// Copy the stack to itself (MOVS).
	// Allocate space.
	@emit LOAD.S.pri    __args_offset     // 11
	@emit JZER.label    Hooks_NoStackCopy // 13
	@emit MOVE.alt                        // 14
	@emit LCTRL         __stk             // 16
	@emit SUB                             // 17
	@emit SCTRL         __stk             // 19
	@emit XCHG                            // 20
	
	if (Server_JITExists())
	{
		// Need to use memcpy to move about in the stack.
		@emit PUSH.C        4096
		@emit PUSH.pri
		@emit PUSH.C        0
		@emit LCTRL         __frm
		@emit ADD.C         __3_cells
		@emit PUSH.pri
		@emit PUSH.alt
		@emit PUSH.C        __5_cells
		@emit SYSREQ.C      nativeidxof(_YSI_ConstCpy__<aaiii>)
		@emit STACK         __6_cells
	}
	else
	{
		// The "MOVS" OpCode only takes a constant, not a variable, so we need
		// to generate self-modifying code (just to be UBER meta)!  This code is
		// generated AFTER the file is loaded so we bypass the data segment
		// checks and can freely write wherever we want.
		@emit STOR.pri      (CGen_GetCodeSpace() + (27 * cellbytes)) // 22
		
		// Do the copying.  "alt" is already "STK", load the "FRM" offset.
		@emit LCTRL         __frm           // 24
		@emit ADD.C         __3_cells       // 26
		// This is the instruction we want to modify...
		@emit MOVS          0           // 28 (- 1) = 27 (see above).
	}
	@emit Hooks_NoStackCopy:
	
	// Push the (fake) number of parameters.
	@emit PUSH.C        __m1_cell
	// Now loop over all our functions and insert "CALL" opcodes for them.
	if (multiple)
	{
		for (new i = 0; ; )
		{
			// Get the absolute offset from here.
			@emit CALL          (AMX_Read(YSI_g_sHooks[i]) + base) // 2
			if (!__32(AMX_Read(YSI_g_sHooks[i] + cellbytes)))
			{
				Hooks_InvalidatePointer(YSI_g_sHooks[i]);
			}
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
			@emit LOAD.S.alt    __local0_offset   // 7
			if (ret) @emit AND       // 8
			else @emit OR            // 8
			// Loop and do the very first items last.
			if (++i == YSI_g_sCount) break;
			else @emit STOR.S.pri __local0_offset // 10
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
		if (!AMX_Read(YSI_g_sHooks[0] + cellbytes))
		{
			Hooks_InvalidatePointer(YSI_g_sHooks[0]);
		}
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
	@emit LOAD.S.pri    __local1_offset
	@emit STOR.pri      AMX_Ref(YSI_g_sActiveHooks)
	
	// Remove the whole stack then get the return value.
	@emit LCTRL         __frm
	@emit SCTRL         __stk
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
 *   Goes through the whole of the public functions table and moves those
 *   without valid pointers to the start, then moves the start address up to
 *   after them.
 * </remarks>
 *//*------------------------------------------------------------------------**/

_Y_HOOKS_STATIC Hooks_CompressPublics()
{
	Debug_Print4("Hooks_CompressPublics called");
	// Count the number of still active functions.
	new
			read = AMX_HEADER_NATIVES,
			write = AMX_HEADER_NATIVES,
		#if cellbits == 64
			tmp,
		#endif
			name;
	do
	{
		read -= __defsize_cells,
		// Check if we should skip it anyway (i.e. is it one of the prefixes
		// we want removed).
		name = __32(AMX_Read(read + cellbytes));
		if (name == 0)
		{
			// No pointer, skip it.
			continue;
		}
		switch (AMX_Read(name + AMX_BASE_ADDRESS))
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
			_A<_@yH>,
			_A<@_Hy>,
			_A<@_yH>:
			continue;
		}
		// Neither an invalid pointer nor a removed name.
		write -= __defsize_cells;
		#if cellbits == 64
			// But only write 32 bits.
			tmp = AMX_Read(write + cellbytes),
			tmp = (tmp & 0xFFFFFFFF00000000) | (name & 0x00000000FFFFFFFF),
			AMX_Write(write + cellbytes, pc);
		#else
			AMX_Write(write + cellbytes, name);
		#endif
		name = AMX_Read(read),
		AMX_Write(write, name);
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
			// I think this offset remains constant in 64-bit, and because the
			// values are little-endian the addition still works as well without
			// any masking required.
			name = AMX_Read(AMX_BASE_ADDRESS + 32),
			AMX_Write(AMX_BASE_ADDRESS + 32, name + YSI_g_sInitPublicDiff),
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
 *   Call the main hook run code, then advance the ALS chain.
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
 *   Once all the replacement strings have been found, sort them by the length
 *   of the short versions of the strings.  This is so that the longest (and
 *   special case, e.g. "DynamicCP"-> "DynamicCP") replacements are always done
 *   first.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Hooks_SortReplacements()
{
	new
		idx0 = 0,
		idx = 0,
		temp = 0;
	for (new i = YSI_g_sReplacePtr - 1; i > 0; --i)
	{
		for (new j = 0; j != i; ++j)
		{
			// Sort the strings in order of their short replacement.
			idx0 = YSI_g_sReplacementsShortOrder[j],
			idx = YSI_g_sReplacementsShortOrder[j + 1];
			if (YSI_g_sReplacements[idx0][E_HOOK_NAME_REPLACEMENT_MIN] < YSI_g_sReplacements[idx][E_HOOK_NAME_REPLACEMENT_MIN])
			{
				temp = YSI_g_sReplacementsShortOrder[j],
				YSI_g_sReplacementsShortOrder[j] = YSI_g_sReplacementsShortOrder[j + 1],
				YSI_g_sReplacementsShortOrder[j + 1] = temp;
			}
			// Sort the strings in order of their long replacement.
			idx0 = YSI_g_sReplacementsLongOrder[j],
			idx = YSI_g_sReplacementsLongOrder[j + 1];
			if (YSI_g_sReplacements[idx0][E_HOOK_NAME_REPLACEMENT_MAX] < YSI_g_sReplacements[idx][E_HOOK_NAME_REPLACEMENT_MAX])
			{
				temp = YSI_g_sReplacementsLongOrder[j],
				YSI_g_sReplacementsLongOrder[j] = YSI_g_sReplacementsLongOrder[j + 1],
				YSI_g_sReplacementsLongOrder[j + 1] = temp;
			}
		}
	}
	Debug_Code1{for (new i = 0 ; i != YSI_g_sReplacePtr; ++i) Debug_Print0("Hook Replacement: %d, %d, %s, %s", YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_MIN], YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_MAX], YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_SHORT], YSI_g_sReplacements[i][E_HOOK_NAME_REPLACEMENT_LONG]);}
}

static stock Hooks_MallocState() <y_malloc_finalise : y_malloc_finalise_disabled>
{
}

static stock Hooks_MallocState() <y_malloc_finalise : y_malloc_finalise_enabled>
{
}

static stock Hooks_MallocState() <>
{
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *   Call the main hook run code, then advance the ALS chain.
 * </remarks>
 * <transition keep="true" target="_ALS : _ALS_go"/>
 *//*------------------------------------------------------------------------**/

public OnCodeInit()
{
	state y_malloc_finalise : y_malloc_finalise_disabled;
	// Step 1:
	//
	//   Get the replacements for legacy hooks.
	//
	Debug_Print1("Hooks_OnCodeInit called");
	state _ALS : _ALS_go;
	new
		idx = 0,
		entry = 0;
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
	// afterwards (there is already code in y_hooks for this) to reduce its
	// size.  Binary search safe as it is first.
	while ((idx = AMX_GetPublicEntryPrefix(idx, entry, _A<@_yH>)))
	{
		#emit PUSH.C                    0
		#emit LCTRL                     __cip
		#emit ADD.C                     __9_cells
		#emit LCTRL                     __jit_jump
		#emit PUSH.pri
		#emit LREF.S.pri                entry
		#emit SCTRL                     __cip
	}
	Hooks_SortReplacements();

	new
		// This records the amount of space available in the nametable currently
		// taken up by the names of hooks that we are about to destroy, and
		// where they are located.  Now includes all hooks together.
		heap = GetAmxHeapTop(),
		allocated = 32,
		nativeCount = 0,
		stockCount = 0,
		base = 0;
	// Initial space allocation for storing the NPS function list.
	HeapAllocCells(6 * 32);
	{
		// Get the preloaders.
		new
			namelen = 0,
			namewrite = 0,
			precount = 0,
			ret,
			bool:retry,
			//bool:newpub,
			preloads[32][E_CHAIN_HOOK];
		Hooks_GetPreloadLibraries(preloads, precount);
		
		// Step 2:
		//
		//   Now do the legacy hooks (hook type 1).
		//
		// Step 3:
		//
		//   Read the AMX header to loop over all the type 2 hook functions.
		//   These contain the call to `_yH@` which generates the trambopoline
		//   code.
		//
		//   From this data we build a list of all calls to replace.
		// In case there are no hooks.
		entry = -__defsize_cells;
		// Get the space of all the publics, then destroy them all.
		while ((idx = AMX_GetPublicEntryPrefix(idx, entry, _A<@yH_>)))
		{
			Debug_Print7("Hooks_OnCodeInit: idx = %08x", idx);
			namelen += AMX_GetLengthFromEntry(entry) + 1;
			base = AMX_Read(entry + cellbytes);
			if (namewrite == 0)
			{
				namewrite = AMX_BASE_ADDRESS + __32(base);
				YSI_g_sBlockStart = entry;
			}
			AMX_Write(entry + cellbytes, base & ~0xFFFFFFFF);
		}
		{
			new hdr[AMX_HDR];
			GetAmxHeader(hdr);
			base = GetAmxBaseAddress() + hdr[AMX_HDR_COD];
		}
		Debug_Print6("Hooks_OnCodeInit: base = %08x", base);
		YSI_g_sBlockEnd = entry + __defsize_cells;
		Debug_Print6("Hooks_OnCodeInit: YSI_g_sBlockStart = %08x, YSI_g_sBlockEnd = %08x", YSI_g_sBlockStart, YSI_g_sBlockEnd);
		// Get the next hook type.  This is binary-search safe because it is the
		// first call before any name mangling has happened.
		YSI_g_sNPSBaseCall = cellmin;
		do
		{
			retry = false;
			for (entry = YSI_g_sBlockStart; entry != YSI_g_sBlockEnd; entry += __defsize_cells)
			{
				if (AMX_Read(entry) == 0)
				{
					continue;
				}
				Debug_Print7("Hooks_OnCodeInit: entry = %08x, %08x", entry, AMX_Read(entry));
				// Invoke the function, which will result in our callback being
				// called to get the base function name (in to `YSI_g_sName`).
				state y_hooks_scan : y_hooks_scan_determine_type;
				YSI_g_sTempRet = YSI_g_sNPSTrampoline;
				#emit PUSH.C                    0
				#emit LCTRL                     __cip
				#emit ADD.C                     __11_cells
				#emit LCTRL                     __jit_jump
				#emit PUSH.pri
				#emit LREF.S.pri                entry
				#emit STOR.pri                  YSI_g_sNPSTrampoline
				#emit SCTRL                     __cip
				#emit STOR.S.pri                ret
				// Determine the callback type.
				switch (ret)
				{
				case 1: // `hook`
				{
					Debug_Print7("Hooks_OnCodeInit: type = hook");
					// Always restore `YSI_g_sNPSTrampoline` outside case `2`.
					YSI_g_sNPSTrampoline = YSI_g_sTempRet;
					state y_hooks_scan : y_hooks_scan_legacy_hook;
					Hooks_Collate(preloads, precount, entry, namelen, namewrite);
					// This will re-test the same slot but that's good because
					// we do an insertion sort so some publics may have been
					// moved up.  They also may not, but that's not a problem
					// because in that case the `== 0` check above will trigger
					// and skip the repeat.
					entry -= __defsize_cells;
				}
				case 2: // `hook stock`
				{
					Debug_Print7("Hooks_OnCodeInit: type = hook stock");
					if (YSI_g_sNPSStack != YSI_g_sNPSTrampoline)
					{
						YHNPS_Push(heap, allocated, nativeCount, stockCount, base, YSI_g_sNPSReplace, YSI_g_sNPSStack);
						YSI_g_sNPSStack = YSI_g_sNPSTrampoline;
					}
					// An NPS hook we don't need.
					Hooks_InvalidatePointer(entry);
				}
				case 3: // `hook stock`, for a not currently processed function.
				{
					Debug_Print7("Hooks_OnCodeInit: type = not processed");
					// Always restore `YSI_g_sNPSTrampoline` outside case `2`.
					YSI_g_sNPSTrampoline = YSI_g_sTempRet;
					retry = true;
				}
				//case 4: // `hook public`, which aren't processed in this loop.
				//{
				//	// Always restore `YSI_g_sNPSTrampoline` outside case `2`.
				//	YSI_g_sNPSTrampoline = YSI_g_sTempRet;
				//	newpub = true;
				//}
				default: // Anything else, gets dropped.
				{
					Debug_Print7("Hooks_OnCodeInit: type = other");
					// Always restore `YSI_g_sNPSTrampoline` outside case `2`.
					YSI_g_sNPSTrampoline = YSI_g_sTempRet;
					Hooks_InvalidatePointer(entry);
				}
				}
			}
			if (YSI_g_sNPSBaseCall != cellmin)
			{
				Debug_Print7("Hooks_OnCodeInit: final chain");
				// Store the final chain.
				YHNPS_Push(heap, allocated, nativeCount, stockCount, base, YSI_g_sNPSBaseCall, YSI_g_sNPSTrampoline);
				YSI_g_sNPSBaseCall = cellmin;
			}
			Debug_Print7("Hooks_OnCodeInit: retry: %d", retry);
		}
		while (retry);
		//while (newpub)
		//{
		//	newpub = false;
		//	// Loop backwards through the hooks, because public chains run the
		//	// other way.
		//	for (entry = YSI_g_sBlockEnd; entry != YSI_g_sBlockStart; )
		//	{
		//		entry -= __defsize_cells;
		//		if (AMX_Read(entry) == 0)
		//		{
		//			continue;
		//		}
		//		// Invoke the function, which will result in our callback being
		//		// called to get the base function name (in to `YSI_g_sName`).
		//		state y_hooks_scan : y_hooks_scan_determine_type;
		//		YSI_g_sTempRet = YSI_g_sNPSTrampoline;
		//		#emit PUSH.C                    0
		//		#emit LCTRL                     __cip
		//		#emit ADD.C                     __11_cells
		//		#emit LCTRL                     __jit_jump
		//		#emit PUSH.pri
		//		#emit LREF.S.pri                entry
		//		#emit STOR.pri                  YSI_g_sNPSTrampoline
		//		#emit SCTRL                     __cip
		//		#emit STOR.S.pri                ret
		//		// Determine the callback type.
		//		switch (ret)
		//		{
		//		case 3: // `hook public`, for a not currently processed function.
		//		{
		//			// Always restore `YSI_g_sNPSTrampoline` outside case `2`.
		//			YSI_g_sNPSTrampoline = YSI_g_sTempRet;
		//			newpub = true;
		//		}
		//		case 4: // `hook public`, which aren't processed in this loop.
		//		{
		//			// Always restore `YSI_g_sNPSTrampoline` outside case `2`.
		//			YSI_g_sNPSTrampoline = YSI_g_sTempRet;
		//		}
		//		default: // Anything else, gets dropped.
		//		{
		//			// Always restore `YSI_g_sNPSTrampoline` outside case `2`.
		//			YSI_g_sNPSTrampoline = YSI_g_sTempRet;
		//			Hooks_InvalidatePointer(entry);
		//		}
		//		}
		//	}
		//	if (YSI_g_sNPSBaseCall != cellmin)
		//	{
		//		// Store the final chain.
		//		YHNPS_Push(heap, allocated, nativeCount, stockCount, base, YSI_g_sNPSBaseCall, YSI_g_sNPSTrampoline);
		//		YSI_g_sNPSBaseCall = cellmin;
		//	}
		//}
	}
	
	// Step 4:
	//
	// With `-O2` this can generate invalid code on purpose - our fake `CALL.N`
	// operation.  Thus ensure all other generation is finished first to avoid
	// them getting confused.
	//
	Debug_Print1("Hooks_OnCodeInit chain");
	#if defined Hooks_OnCodeInit
		Hooks_CompressPublics();
		Hooks_OnCodeInit();
	#endif
	
	// Step 5:
	//
	//   Iterate over the entire mode and replace all relevant calls.
	//
	new
		Opcode:call = RelocateOpcode(OP_CALL),
		Opcode:nop = RelocateOpcode(OP_NOP),
		Opcode:proc = RelocateOpcode(OP_PROC),
		Opcode:o,
		reloc = (AMX_HEADER_COD - AMX_BASE_ADDRESS) + AMX_REAL_ADDRESS;
	if (IsOpcodeRelocationRequired())
	{
		for (new addr = AMX_HEADER_COD; addr < 0;)
		{
				switch ((o = UnrelocateOpcode(Opcode:AMX_Read(addr))))
				{
					case OP_SYSREQ_C:
					{
						// Check that the previous OP is `PUSH.C`.  That
						// represents a real native call, not our wrapper.  More
						// correctly, this code checks that the previous Opcode
						// isn't `PROC`, which only happens in our wrapper, we
						// just assume that it is `PUSH.C` otherwise.
						if (Opcode:AMX_Read(addr - __2_cells) == proc)
						{
							addr += __2_cells;
							continue;
						}
						idx = YHNPS_Find(heap, nativeCount, AMX_Read(addr + __1_cell));
				#if __COMPILER_O2
						base = 0;
				#endif
					}
					case OP_SYSREQ_D:
					{
						if (Opcode:AMX_Read(addr - __2_cells) == proc)
						{
							addr += __2_cells;
							continue;
						}
						idx = YHNPS_Find(heap + allocated * __4_cells, nativeCount, AMX_Read(addr + __1_cell));
				#if __COMPILER_O2
						base = 0;
				#endif
					}
				#if __COMPILER_O2
					case OP_SYSREQ_N:
					{
						idx = YHNPS_Find(heap, nativeCount, AMX_Read(addr + __1_cell)),
						base = 1;
					}
				#endif
					case OP_CALL:
					{
						idx = YHNPS_Find(heap + allocated * __2_cells, stockCount, AMX_Read(addr + __1_cell) - reloc);
						if (idx != cellmin)
						{
							// Write a different target address.
							AMX_Write(addr + __1_cell, idx);
						}
						addr += __2_cells;
						continue;
					}
					default:
					{
						addr += (0 <= _:o < sizeof (gAMXOpcodeBaseSizes)) ? (gAMXOpcodeBaseSizes[_:o]) : (__1_cell);
						continue;
					}
				}
				// `SYSREQ.C` is always followed by `STACK`, except with `#emit`
				// usage.  We need to change the pair in to a single `CALL`.
				// Don't forget `SYSREQ.D`.
				if (idx == cellmin)
				{
					addr += __2_cells;
				}
			#if __COMPILER_O2
				else if (base)
				{
					// sysreq.n
					// I need to somehow add pushing the number of parameters
					// here in a single cell.  The only thing we have going for
					// us here is that the code doesn't need to be JIT
					// compatible (so we can do clever things with stacks/
					// addresses if nescessary).
					AMX_Write(addr, _:call),
					AMX_Write(addr + __1_cell, idx),
					addr += __3_cells;
				}
			#endif
				else
				{
					// Write a different target address.
					AMX_Write(addr, _:call),
					AMX_Write(addr + __1_cell, idx),
					addr += __2_cells;
					if (UnrelocateOpcode(Opcode:AMX_Read(addr)) == OP_STACK)
					{
						AMX_Write(addr, _:nop),
						AMX_Write(addr + __1_cell, _:nop),
						addr += __2_cells;
					}
				}
		}
	}
	else
	{
			for (new addr = AMX_HEADER_COD; addr < 0;)
			{
				switch ((o = Opcode:AMX_Read(addr)))
				{
					case OP_SYSREQ_C:
					{
							// Check that the previous OP is `PUSH.C`.  That
							// represents a real native call, not our wrapper.
							if (Opcode:AMX_Read(addr - __2_cells) == proc)
							{
								addr += __2_cells;
								continue;
							}
							idx = YHNPS_Find(heap, nativeCount, AMX_Read(addr + __1_cell));
						#if __COMPILER_O2
							base = 0;
						#endif
					}
					case OP_SYSREQ_D:
					{
							if (HasSysreqD())
							{
								if (Opcode:AMX_Read(addr - __2_cells) == proc)
								{
									addr += __2_cells;
									continue;
								}
								idx = YHNPS_Find(heap + allocated * __4_cells, nativeCount, AMX_Read(addr + __1_cell));
						#if __COMPILER_O2
								base = 0;
							}
							else
							{
								idx = YHNPS_Find(heap, nativeCount, AMX_Read(addr + __1_cell));
								base = 1;
						#endif
							}
					}
					case OP_CALL:
					{
						idx = YHNPS_Find(heap + allocated * __2_cells, stockCount, AMX_Read(addr + __1_cell) - reloc);
						if (idx != cellmin)
						{
							// Write a different target address.
							AMX_Write(addr + __1_cell, idx);
						}
						addr += __2_cells;
						continue;
					}
					default:
					{
						addr += (0 <= _:o < sizeof (gAMXOpcodeBaseSizes)) ? (gAMXOpcodeBaseSizes[_:o]) : (__1_cell);
						continue;
					}
				}
				// `SYSREQ.C` is always followed by `STACK`, except with `#emit`
				// usage. We need to change the pair in to a single `CALL`.
				// Don't forget `SYSREQ.D`.
				if (idx == cellmin)
				{
					addr += __2_cells;
				}
			#if __COMPILER_O2
				else if (base)
				{
					// sysreq.n
					// I need to somehow add pushing the number of parameters
					// here in a single cell.  The only thing we have going for
					// us here is that the code doesn't need to be JIT
					// compatible (so we can do clever things with stacks/
					// addresses if nescessary).
					AMX_Write(addr, _:call),
					AMX_Write(addr + __1_cell, idx),
					addr += __3_cells;
				}
			#endif
				else
				{
					// Write a different target address.
					AMX_Write(addr, _:call),
					AMX_Write(addr + __1_cell, idx),
					addr += __2_cells;
					if (Opcode:AMX_Read(addr) == OP_STACK)
					{
						AMX_Write(addr, _:nop),
						AMX_Write(addr + __1_cell, _:nop),
						addr += __2_cells;
					}
				}
		}
	}

	// Step 6:
	//
	//   Generate `continue`.
	//
	Hooks_GenerateContinue();

	// Step 7:
	//
	//   Clean up and remove our excess publics.
	//
	YSI_g_sNPSStack = 0;
	HeapRelease(heap);
	
	Hooks_CompressPublics();
	Debug_Print1("Hooks_OnCodeInit end");
	if (Server_JITExists())
		Hooks_RepairJITInit();

	// This must be called after y_hooks is finished, but we don't know if it is
	// included.  So we use states set and cleared both there and here to ensure
	// that this is only called after one or both are complete.
	#if defined Malloc_Finalise
		Malloc_Finalise();
	#endif
	state y_malloc_finalise : y_malloc_finalise_enabled;
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
	AMX_Write(AMX_HEADER_PUBLICS + YSI_g_sInitFSIdx * __2_cells, YSI_g_sInitFSRep);
	AMX_Write(AMX_HEADER_PUBLICS + YSI_g_sInitGMIdx * __2_cells, YSI_g_sInitGMRep);
	// Move the header up for searching.
	if (YSI_g_sInitPublicDiff)
	{
		// As elsewhere this needs no changes in 64-bit.
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
	#emit LCTRL               __cip
	#emit ADD.C               __9_cells
	#emit LCTRL               __jit_jump
	#emit PUSH.pri
	#emit LOAD.pri            YSI_g_sInitFSPtr
	#emit SCTRL               __cip
	return 1;
}

_Y_HOOKS_STATIC _Hooks_RepairStubGM()
{
	_Hooks_RepairStub();
	#emit PUSH.C              0
	#emit LCTRL               __cip
	#emit ADD.C               __9_cells
	#emit LCTRL               __jit_jump
	#emit PUSH.pri
	#emit LOAD.pri            YSI_g_sInitGMPtr
	#emit SCTRL               __cip
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
		base = AMX_HEADER_PUBLICS + YSI_g_sInitFSIdx * __2_cells,
		stub = 0;
	#emit CONST.pri           _Hooks_RepairStubFS
	#emit STOR.S.pri          stub
	YSI_g_sInitFSRep = AMX_Read(base),
	AMX_Write(base, stub);
	base = AMX_HEADER_PUBLICS + YSI_g_sInitGMIdx * __2_cells;
	#emit CONST.pri           _Hooks_RepairStubGM
	#emit STOR.S.pri          stub
	YSI_g_sInitGMRep = AMX_Read(base),
	AMX_Write(base, stub);
}

stock Hooks_NumArgs()
{
	// Awkward code that allows us to jump backwards.  It might appear that this
	// code pushes something on the stack before the JZER that is never removed,
	// but labels reset the stack always so it gets unconditionally wiped out.
	#emit LOAD.S.alt          0
Hooks_NumArgs_load:
	#emit CONST.pri           __2_cells
	#emit ADD
	#emit LOAD.I
	#emit ZERO.alt
	#emit PUSH.pri
	#emit SGEQ
	#emit LREF.S.alt          0
	#emit JZER                Hooks_NumArgs_load
	#emit POP.pri
	#emit SHR.C.pri           __cell_shift
	#emit RETN
	// Ideal code, that can't be used due to having a forward jump.
/*	#emit LOAD.S.pri          0
	#emit ADD.C               __2_cells
	#emit LOAD.I
	#emit ZERO.alt
	#emit JSLESS              Hooks_NumArgs_negative
	#emit SHR.C.pri           __cell_shift
	#emit RETN
Hooks_NumArgs_negative:
	#emit LREF.S.pri          0
	#emit ADD.C               __2_cells
	#emit LOAD.I
	#emit SHR.C.pri           __cell_shift
	#emit RETN*/
	__pragma("naked");
}

#if defined _ALS_numargs
	#undef numargs
#else
	#define _ALS_numargs
#endif
#define numargs( Hooks_NumArgs(

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
		//   #emit ADDR.pri    __m2_cells
		//   #emit STOR.pri    YSI_g_sActiveHooks
		//
		// This makes a stack of active hooks.  When a crash occurs, we walk
		// this stack and fix up all the parameter counts.
		new
			cur = YSI_g_sActiveHooks,
			i = 0,
			prev;
		//for (new i = 0, prev; cur; cur = AMX_Read(cur))
		for ( ; ; )
		{
			if (cur == 0)
			{
				break;
			}
			if (++i == 1)
			{
				print("[debug]");
				print("[debug] Parameter count corrections:");
				print("[debug]");
			}
			// Not 8, because `cur` is `- 8`.
			printf("[debug] The %s mangled arguments (e.g. `<1073741823 arguments>`) below should read `<%d arguments>`", ValstrWithOrdinal(i), AMX_Read(cur + __4_cells) / cellbytes);
			//// Get the current parameter count.
			//printf("count: %d", count);
			//// Write this out to the lower parameter count copy.
			//AMX_Write(cur - count - __1_cell, count);
			//// Fixed.
			prev = cur;
			cur = AMX_Read(cur);
			if (cur <= prev)
			{
				print("[debug] Parameter count loop detected.");
				break;
			}
		}
		if (YSI_g_sActiveHooks)
		{
			print("[debug]");
			// Blank the active hooks value.  If this is the only public, this
			// will reset it after the public is foribly ended.  If it isn't, it
			// will be reset to a correct value when the next still active hook
			// ends.  This is only a problem if there are two crashes at once,
			// then the second corrections won't get displayed.
			//
			// Now reads the next item from the list again.
			YSI_g_sActiveHooks = AMX_Read(YSI_g_sActiveHooks);
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

/*

    888b      88  88888888ba    ad88888ba   
    8888b     88  88      "8b  d8"     "8b  
    88 `8b    88  88      ,8P  Y8,          
    88  `8b   88  88aaaaaa8P'  `Y8aaaaa,    
    88   `8b  88  88""""""'      `"""""8b,  
    88    `8b 88  88                   `8b  
    88     `8888  88           Y8a     a8P  
    88      `888  88            "Y88888P"   

*/

/**--------------------------------------------------------------------------**\
<summary>YHNPS_Find</summary>
<returns>
	-
</returns>
<remarks>
	We have a big sorted list of functions and their replacements in the heap.
	This code checks to see if a given native or function is in that replacement
	list, and if so finds the new version (the hook stub).
</remarks>
\**--------------------------------------------------------------------------**/

static stock YHNPS_Find(heap, end, value)
{
	new
		start = 0,
		mid = 0;
	--end;
	while (start <= end)
	{
		mid = (start + end) / 2;
		new
			diff = AMX_Read(heap + mid * __2_cells) - value;
		if (diff < 0)
		{
			start = mid + 1;
		}
		else if (diff > 0)
		{
			end = mid - 1;
		}
		else
		{
			return AMX_Read(heap + mid * __2_cells + __1_cell);
		}
	}
	return cellmin;
}

/**--------------------------------------------------------------------------**\
<summary>YHNPS_Insert</summary>
<returns>
	-
</returns>
<remarks>
	We have a big sorted list of functions and their replacements in the heap.
	This code checks to see if a given native or function is in that replacement
	list, and if not adds it, or replaces it with a newer hook.
</remarks>
\**--------------------------------------------------------------------------**/

static stock YHNPS_Insert(heap, count, value, ptr)
{
	new
		start = 0,
		mid = 0,
		end = count - 1;
	while (start <= end)
	{
		mid = (start + end) / 2;
		new
			diff = AMX_Read(heap + mid * __2_cells) - value;
		if (diff < 0)
		{
			start = mid + 1;
		}
		else if (diff > 0)
		{
			end = mid - 1;
		}
		else
		{
			return;
		}
	}
	if (start != count)
	{
		// Shift all the greater values up.
		RawMemCpy(heap + start * __2_cells + __2_cells, heap + start * __2_cells, (count - start) * __2_cells);
	}
	AMX_Write(heap + start * __2_cells, value);
	AMX_Write(heap + start * __2_cells + __1_cell, ptr);
}

Hooks_Continue_(GLOBAL_TAG_TYPES:...)
{
	return 0;
}

static stock YHNPS_Push(heap, &allocated, &nativeCount, &stockCount, base, find, replace)
{
	if (allocated == max(nativeCount, stockCount))
	{
		// Space to insert twice as many new hooks for each type.  The three
		// types each take two cells (old and new pointer) and are:
		//
		//   0 * allocated - `SYSREQ.C` indexes.
		//   8 * allocated - `CALL` addresses.
		//  16 * allocated - `SYSREQ.D` true pointers.
		//
		// The first and last ones are inserted together.
		HeapAllocCells(6 * allocated);
		// Move the arrays up in memory.
		if (nativeCount)
		{
			RawMemCpy(heap + allocated * __8_cells, heap + allocated * __4_cells, nativeCount * __2_cells);
		}
		if (stockCount)
		{
			RawMemCpy(heap + allocated * __4_cells, heap + allocated * __2_cells, stockCount * __2_cells);
		}
		allocated *= 2;
	}
	if (find < 0)
	{
		YHNPS_Insert(heap, nativeCount, -find, replace + base);
		if (HasSysreqD())
		{
			YHNPS_Insert(heap + allocated * __4_cells, nativeCount, GetNativeAddressFromIndex(-find), replace + base);
		}
		++nativeCount;
	}
	else
	{
		YHNPS_Insert(heap + allocated * __2_cells, stockCount, find, replace + base);
		++stockCount;
	}
}

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

#define continue(%0) Hooks_Continue_(%0)

static stock Hooks_RegisterNPSHook(compressedFormat, address, const string:name[], order)
{
	#pragma unused name
	#pragma unused order
	// Put us in the frame of the previous function.  Because `compressedFormat`
	// is in the same location in both this works fine and we can use the
	// variables as normal.
	#emit LOAD.S.pri   0
	#emit SCTRL        __frm
	#emit SCTRL        __stk
	// Get the next function call address, being the original function.  This
	// can also tell us if it is a native, public, or stock (which is a nice
	// side-effect I wasn't planning).
	new
		ctx[AsmContext],
		addr = 0,
		type = 0;
	// The naming is a bit ambiguous here.  `addr` is the address of the next
	// function in the chain (i.e. the function we're hooking), while `address`
	// is the address of the function we're replacing it with.
	//if (name[0])
	//{
	//	// Find the public in the header.
	//	if (AMX_GetPublicPointer(0, addr, name))
	//	{
	//		type = 1;
	//	}
	//	else
	//	{
	//		// TODO: This is the last item in the chain.
	//	}
	//}
	//else
	{
		new
			dctx[DisasmContext];
		DisasmInit(dctx, GetCurrentFrameReturn());
		while (DisasmNext(dctx))
		{
			switch (DisasmGetOpcode(dctx))
			{
			case OP_CALL:
			{
				addr = DisasmGetOperandReloc(dctx);
				type = 1;
			}
			case OP_SYSREQ_C:
			{
				addr = -DisasmGetOperand(dctx);
				type = -(YSI_g_sNPSTrampoline + 39 * cellbytes);
			}
			case OP_SYSREQ_D:
			{
				type = -(YSI_g_sNPSTrampoline + 39 * cellbytes);
			}
#if __COMPILER_O2
			case OP_SYSREQ_N:
			{
				addr = -DisasmGetOperand(dctx);
				type = -(YSI_g_sNPSTrampoline + 48 * cellbytes);
			}
#endif
			case OP_RETN:
			{
				// Loop through the code above until we hit a `RETN`.  At this
				// point the variables will be set to the most recent call.
				break;
			}
			}
		}
	}
	//if (type < 0)
	//{
	//	// Native function call.
	//	addr = -addr;
	//}
	if (YSI_g_sNPSBaseCall == cellmin)
	{
		// Newly found function to be hooked.  Carry on.
	}
	else if (YSI_g_sNPSBaseCall != addr)
	{
		// This is a hook for a different function.  We don't want this one
		// just yet, wait till the current hook is done with.
		#emit HEAP                 __m7_cells
		#emit LOAD.S.pri           0
		#emit SCTRL                __frm
		#emit SCTRL                __stk
		// Try this one again later.  Double return.
		#emit CONST.pri            3
		#emit RETN
	}

	YSI_g_sNPSReplace = address;
	AsmInitPtr(ctx, YSI_g_sNPSTrampoline + AMX_HEADER_COD, YSI_g_sNPSReplace - YSI_g_sNPSTrampoline);
	// Forward the function, storing the chain data in the heap.   Note that no
	// `PROC` is added to this new trambopoline:
	//
	//   https://www.youtube.com/watch?v=geHqnV4Mk_4
	//

	// Build the structure in the stack first.
#if __COMPILER_O2
	if (type == -(YSI_g_sNPSTrampoline + 48 * cellbytes))
	{
		// Extract the parameter count from the return address.  This is so we
		// can fake a `CALL.N <addr> <params>` op to replace the `SYSREQ.N` in
		// the same amount of space.  This is neither JIT nor cache-compatible.
		// (actually it might be cache-compatible).
		@emit POP.pri
		@emit ADD.C         AMX_HEADER_COD
		@emit STOR.pri      ref(J@)
		@emit LREF.alt      ref(J@)
		@emit PUSH.alt
		@emit ADD.C         (__1_cell - AMX_HEADER_COD)
		
		// Push and pop so that we can jump in to the middle of this code.
		@emit PUSH.pri
		@emit POP.pri
		
		// Chain the functions.
		if (YSI_g_sNPSBaseCall == addr)
		{
			@emit PUSH3.C       compressedFormat, (YSI_g_sNPSStack + __11_cells), __2_cells    // 5
			YSI_g_sNPSStack = YSI_g_sNPSTrampoline; // Replace.
		}
		else if (YSI_g_sNPSBaseCall == cellmin)
		{
			@emit PUSH3.C       compressedFormat, (type < 0 ? type : (addr + __11_cells)), __2_cells // 5
			YSI_g_sNPSStack = YSI_g_sNPSTrampoline;
		}
		else
		{
			@emit PUSH3.C       compressedFormat, (type < 0 ? type : (addr + __11_cells)), __2_cells // 5
		}
	}
	else
#endif
	{
		@emit POP.pri                                                           // 1
		@emit PUSH.C       compressedFormat                                     // 3

		// Chain the functions.
		//if (YSI_g_sNPSBaseCall == addr)
		//{
		//	@emit PUSH.C       YSI_g_sNPSStack                                  // 5
		//	YSI_g_sNPSStack = YSI_g_sNPSTrampoline; // Replace.
		//}
		//else if (YSI_g_sNPSBaseCall == cellmin)
		//{
		//	@emit PUSH.C       (type < 0 ? type : addr)                         // 5
		//	YSI_g_sNPSStack = YSI_g_sNPSTrampoline;
		//}
		//else
		//{
		//	@emit PUSH.C       (type < 0 ? type : addr)                         // 5
		//}
		if (YSI_g_sNPSBaseCall == cellmin)
		{
			@emit PUSH.C       (type < 0 ? type : addr)                         // 5
		}
		else
		{
			@emit PUSH.C       YSI_g_sNPSStack                                  // 5
		}
		YSI_g_sNPSStack = YSI_g_sNPSTrampoline;
		@emit PUSH.C       __2_cells                                            // 7
	}

	@emit PUSH.pri     // Save the return address again.                        // 8
	@emit PUSH         AMX_Ref(YSI_g_sNPSStack)                                 // 10

	// Copy 20 bytes over (includes the return address and fake param count).
	@emit HEAP         __5_cells                                                // 12
	@emit LCTRL        __stk                                                    // 14
	@emit MOVS         __5_cells                                                // 16
	@emit STOR.alt     AMX_Ref(YSI_g_sNPSStack)                                 // 18

	// Call, and return to here to clean up the heap.
	@emit STACK        __5_cells                                                // 20
	@emit CALL.abs     YSI_g_sNPSReplace                                        // 22

	// Put data (and return value) on the stack.
	@emit STACK        -__5_cells                                               // 24
	@emit STACK        0                                                        // 26
	@emit PUSH.pri                                                              // 27

	// Copy from the heap.
	@emit LOAD.pri     AMX_Ref(YSI_g_sNPSStack)                                 // 29
	@emit MOVS         __5_cells                                                // 31

	// Restore the return address and `continue` stack.
	@emit POP.pri                                                               // 32
	@emit POP.alt                                                               // 33
	@emit STOR.alt     AMX_Ref(YSI_g_sNPSStack)                                 // 35
	@emit HEAP         -__5_cells                                               // 37

	// Return from this "function", with our fake parameters and return address.
	// We do this instead of using `SCTRL 6`, as is the normal way, to preserve
	// `pri` as the return value.
	@emit PROC                                                                  // 38
	@emit RETN                                                                  // 39

	if (type < 0)
	{
		// Missed this one apparently...
		@emit SYSREQ.C     -addr
		//@emit SYSREQ.pri

		// Returns to here.
		@emit PUSH.alt
		@emit PUSH         AMX_Ref(YSI_g_sTempRet)
		@emit RETN
	}

	AsmEmitPadding(ctx);

	YSI_g_sNPSReplace = YSI_g_sNPSBaseCall; // Find
	YSI_g_sNPSBaseCall = addr;

	// Do a triple return - exit the calling function as well as this function,
	// so that the next call is never actually made.  This only looks like a
	// double return, but we are operating in the frame of the caller already.
	#emit HEAP                 __m7_cells
	#emit LOAD.S.pri           0
	#emit SCTRL                __frm
	#emit SCTRL                __stk
	#emit CONST.pri            2
	#emit RETN

	__pragma("naked");
}

stock _yH@(compressedFormat, address, order = cellmin, &a = 0, &b = 0, &c = 0, &d = 0, &e = 0, &f = 0, &g = 0) <y_hooks_scan : y_hooks_scan_determine_type>
{
	#pragma unused a, b, c, d, e, f, g
	// IMPORTANT NOTE:  Because of the way `Hooks_RegisterNPSHook` messes with
	// the stack the final parameter won't be the string we passed here, but
	// `a` from the extra parameters above.  But that's fine - either way it
	// points to nothing.
	return Hooks_RegisterNPSHook(compressedFormat, address, YSI_EMPTY, order);
}

stock _yH@(compressedFormat, address, order = cellmin, &a = 0, &b = 0, &c = 0, &d = 0, &e = 0, &f = 0, &g = 0) <>
{
	const cells0 = __3_cells + __10_cells;
	#pragma unused compressedFormat, address, order
	#pragma unused a, b, c, d, e, f, g

	// A double return.  We return `0` from this function because we don't care
	// about the current state.
	#emit HEAP                 __m7_cells
	#emit STACK                cells0
	#emit ZERO.pri
	#emit RETN

	__pragma("naked");
}

static stock Hooks_GenerateContinue(GLOBAL_TAG_TYPES:...)
{
	// This generates new code in a given location.  That location just happens
	// to entirely clobber `YHNPS_Push`, but we no longer need it.
	new
		ctx[AsmContext],
		ptr = _:addressof(Hooks_Continue_<>);

	AsmInitPtr(ctx, ptr + AMX_HEADER_COD, _:addressof(Hooks_RegisterNPSHook<iisi>) - ptr);

	@emit PROC
	@emit ADDR.pri     __args_offset
	@emit PUSH.pri

	// Load the bitmap of parameter types.
	@emit LOAD.pri     AMX_Ref(YSI_g_sNPSStack)
	@emit ADD.C        __4_cells
	@emit LOAD.I
	@emit MOVE.alt

	// Loop over it and dereference regular numbers.
	@emit Hooks_Continue_loop:

	@emit POP.pri
	@emit ADD.C        __1_cell
	@emit PUSH.pri

	// Check if `alt` is `0` (no parameters) or odd (move this parameter).
	@emit CONST.pri    1
	@emit SHR.C.alt    1
	@emit JGRTR.label  Hooks_Continue_done
	@emit AND
	@emit JZER.label   Hooks_Continue_loop

	// Adjust the given parameter.
	@emit LREF.S.pri   __local0_offset
	@emit LOAD.I
	@emit SREF.S.pri   __local0_offset
	@emit JUMP.label   Hooks_Continue_loop

	@emit Hooks_Continue_done:

	@emit POP.pri

	@emit LOAD.pri     AMX_Ref(YSI_g_sNPSStack)
	@emit ADD.C        __3_cells
	@emit LOAD.I

	// `alt` is `0` here, thanks to the loop above.
	@emit JSLEQ.label  Hooks_Continue_native

	@emit MOVE.alt
	@emit POP.pri
	@emit SCTRL        __frm

	// Jump to the function that calls the original native.
	@emit MOVE.pri
	@emit SCTRL        __cip

	@emit Hooks_Continue_native:

	// Save the bottom of the stack.
	@emit POP.alt
	@emit STOR.alt     AMX_Ref(YSI_g_sTempRet)
	@emit POP.alt

	// Jump to the next function in the chain.
	@emit NEG
	@emit SCTRL        __cip

	//// Missed this one apparently...
	//AsmEmitSysreqPri(ctx);
	////@emit SYSREQ.pri
    //
	//// Returns to here.
	//@emit PUSH.alt
	//@emit PUSH         AMX_Ref(YSI_g_sTempRet)
	//@emit RETN

	AsmEmitPadding(ctx);
}

