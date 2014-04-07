
/**--------------------------------------------------------------------------**\
<summary>
	Hooks_GenerateStub(const addr, const funcs[], const len);
</summary>
<param name="addr">The address at which to start writing new code.</param>
<param name="funcs">A list of all functions to be called (in order).</param>
<param name="len">The number of functions in "funcs".</param>
<returns>
	Success.
</returns>
<remarks>
	All this does is generate a stub function that is run the first time the
	hooked public is called.  This stub stores a list of the hooks to be called
	and calls "Hooks_StubGenerator" with this data.
</remarks>
\**--------------------------------------------------------------------------**/

static Hooks_GenerateStub()
{
}

forward Hooks_StubGenerator(hookCount, /* VERY VERY */ const _frm, /* VERY VERY */ const _ret, /* VERY VERY */ const paramCount);

public Hooks_StubGenerator(hookCount, /* VERY VERY */ const _frm, /* VERY VERY */ const _ret, /* VERY VERY */ const paramCount)
{
	if (numargs() == 4)
	{
		P:E("Hooks_StubGenerator: Called \"incorrectly\" (and by that I mean normally).");
		return;
	}
	assert(numargs() == 1);
	#pragma unused _frm, _ret
	// The parameter count for this function is WRONG!  But it is wrong by
	// design - the last three parameters are actually the previous function's
	// frame header, provided here as parameters through ASM magic.
	new
		frm = GetCurrentFrame(),
		ret = GetFrameReturn(frm),
		hooksPtr = CodToDat(ret);
	SetCurrentFrameReturn(ret - 8); // Jump back to the start of the stub.
	// Write the function entry code.
	// Loop over all the hooks for this function and write the call code for
	// each.
	// Write the function exit code.
	// End this function and remove just "hookCount" from the stack.
	return;
}











Hooks_GetBaseFunc(const name[], &fixes, &als)
{
	// This can return several functions.  For some callbacks, there are
	// alternative accepted names, the two different versions will go in "als1"
	// and "als2".  These are the functions to be called AFTER y_hooks.  In fact
	// scrap that!  There will NEVER be a time when both are in use at once!
	// ALS forms a linear chain regardless of the actual names used.  So instead
	// we now have "als" for getting the function to call after all y_hooks, and
	// "fixes" for the possible entry point to remap to our code.  This ensures
	// that "fixes.inc"'s callbacks always come first.
	new
		idx,
		func[32];
	// First, check if the basic name exists.
	fixes = 0, als = 0,
	format(func, sizeof (func), "On%s", Hooks_GetLongName(name)),
	idx = funcidx(func);
	if (idx == -1) return;
	als = PtrFromIdx(idx),
	// Next, check if we have fixes.inc.
	format(func, sizeof (func), "FIXES_On%s", Hooks_GetShortName(name)),
	idx = funcidx(func);
	if (idx == -1) return;
	fixes = PtrFromIdx(idx),
	als = GetFixesNext(fixes);
	// To complete this function, I need to know the generated code layout of
	// function state headers.  We can then redirect ALL elements of those
	// headers to our new code
}

Hooks_RedirectFixesState(stub, to)
{
	// Loop over every state defined in the function at "stub", and redirect
	// them all to "to".  I'm hoping that the number of states is defined in the
	// function stub itself.
	new
		numStates = stub + 8 + AMX_Read(stub) * 8;
	for (new addr = stub + 8; addr != numStates; addr += 8)
	{
		// TODO: TOTAL GUESS!
		AMX_Write(addr, to);
	}
}

// There are SO MANY special cases in this code!

static Hooks_RedirectPublic(name[], address, origin)
{
	// There are four possibilities in this code:
	//     
	//     1) There is a public, and that public is from "fixes.inc".
	//     2) There is a normal public.
	//     3) There is no public.
	//     4) There is no public, and the hook function's name is shorter than
	//         the original callback's name.  This only happens twice AFAIK:
	//           
	//           hook OnPlayerEnterRaceCP(playerid)
	//           
	//         Becomes:
	//           
	//           public @yH_OnPlayerEnterRaceCP@001
	//           
	//         Hooking:
	//           
	//           public OnPlayerEnterRaceCheckpoint
	//           
	//         OK, it seems even that isn't a special case (JUST), y_hooks adds
	//         8 characters to the original name, so we need to have lost more
	//         than that to name reductions.
	//         
	//         Thus, this may not be a problem at all!
	new
		idx = funcidx(name);
	if (idx == -1)
	{
		// There is no original function, so we need to use "origin".
		if (strlen(name
	}
	else
	{
		// There is a function, is it a callback in "fixes.inc"?
		#if defined _INC_SAMP_Community_Fixes || defined _inc_fixes
			#if !defined FIXES_UseStateHooks
				#error You must upgrade fixes.inc to use it with YSI 4.0.
			#endif
			// This only works with the latest fixes.inc using states for hooks
			// instead of ALS 7 (actually an older version of ALS).  Using
			// states means that the next function in the chain ALWAYS exists,
			// but just may do nothing in many cases.
			static
				func[32] = "FIXES_";
			if (name[0] == 'O' && name[1] == 'n' &&
				(Hooks_AppendShortName(func, name, 6), funcidx(func) != -1))
			{
				// Using fixes.inc, and this function has a fix hooked in.  We
				// may need to find a shorter version of the function name.  If
				// this returns true, then we have to replace the various state
				// calls with our new function, and add the existing state
				// functions to the chain.  This is also quite hard - if there
				// is only one state function, then we can just ignore it, but
				// if there are multiple ones, we need to determine which to
				// use.  The simplest way to do this that I can think of is to
				// use FIVE states:
				//   
				//   // Define five states.
				//   FixesHook() <fixes_hook : fixes_hook_1> {}
				//   FixesHook() <fixes_hook : fixes_hook_2> {}
				//   FixesHook() <fixes_hook : fixes_hook_3> {}
				//   FixesHook() <fixes_hook : fixes_hook_4> {}
				//   FixesHook() <fixes_hook : fixes_hook_5> {}
				//   
				// Then in fixes.inc, when hooking, we define:
				//   
				//   FIXES_OnFunc() <fixes_hook : fixes_hook_1, fixes_hook : fixes_hook_2> {}
				//   FIXES_OnFunc() <> {}
				//   #define OnFunc() FIXES_OnFunc() <fixes_hook : fixes_hook_5>
				//   
				// The first function defines "OnFunc" as using the "fixes_hook"
				// state.  The second function is the one called when no user
				// function is defined.  The first function has two states, the
				// second has either two or three pointing to it.  When we
				// examine the states table, we just look for any function
				// pointer that only appears once.  If there isn't one, there is
				// no user function of that name.  If there is one, then that
				// single pointer is the first regular ALS hook, and we need to
				// call it after all y_hooks functions.  So despite what I said
				// earlier about not being able to insert new calls in to the
				// middle of an ALS call chain, this proves we can when the call
				// chain is properly configured to support it.
				// 
				// Whatever we do, make sure that the "called" state is always
				// first in the state machine stub.  Interestingly, because
				// state machine stubs don't have "PROC" in them, and they just
				// redirect to full functions, we can invoke that function
				// directly and not go through the state machine in the
				// rewritten code (in fact, we can even try re-use the space in
				// the states stub to call our hooks before invoking "cgen".
			}
			else
		#endif
			{
				// We have a callback, but not from "fixes.inc".
			}
	}
}

static stock bool:Hooks_MakeShortName(name[])
{
	new
		pos;
	while (strlen(name) >= 32)
	{
		// This is the most common reduction as it saves the most characters in
		// one go.
		if ((pos = strfind(name, "Checkpoint")) != -1)
		{
			// "Checkpoint" -> "CP".
			strdel(name, pos, pos + 10),
			strins(name, "CP", pos);
		}
		else if ((pos = strfind(name, "TextDraw")) != -1)
		{
			// "TextDraw" -> "TD".
			strdel(name, pos, pos + 8),
			strins(name, "TD", pos);
		}
		else if ((pos = strfind(name, "Update")) != -1)
		{
			// "Update" -> "Upd".
			strdel(name, pos + 3, pos + 6);
		}
		else if ((pos = strfind(name, "Object")) != -1)
		{
			// "Object" -> "Obj".
			strdel(name, pos + 3, pos + 6);
		}
		else return false;
	}
	return true;
}

static stock Hooks_FindFixesFunc(const name[])
{
	// Return the next ALS function if there is one.  Decompile code to find it.
	static
		func[64] = "FIXES_";
	func[6] = '\0';
	strcat(func, name);
	Hooks_MakeShortName(func);
	// Check if there are any "fixes.inc" hooks to use.
	new
		idx = funcidx(func);
	if (idx == -1) return 0;
	idx = AMX_GetEntryPointer(AMX_GetEntryFromPublicIndex(idx));
	new
		next = Hooks_FindFixesHook(idx);
	if (next)
	{
		// Has a hooked callback.
		
	}
}

static stock Hooks_FindFixesHook(const stub)
{
	new
		dctx[DisasmContext];
	DisasmInit(dctx, stub);
	// Side-effect function.
	if (DisasmNextInsn(dctx) == OP_LOAD_PRI && DisasmNextInsn(dctx) == OP_SWITCH && DisasmNextInsn(dctx) == OP_CASETBL)
	{
		// Get the number of items in the casetable.
		if (DisasmGetNumOperands(dctx) == 3) // 2 means no used hook.
		{
			// Got a hook to return.  Find it.
			new
				h0 = DisasmGetOperand(dctx, 3),
				h1 = DisasmGetOperand(dctx, 5),
				h2 = DisasmGetOperand(dctx, 7);
			if (h1 == h2)      return h0; // Most likely.
			else if (h0 == h2) return h1;
			else if (h0 == h1) return h2;
			// new
				// wctx[AsmContext];
			// AsmInitPtr(wctx, stub, 8);
			// AsmEmitJump(wctx, h0);
		}
	}
	return 0;
}





