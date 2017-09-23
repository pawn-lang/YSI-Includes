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

#define INLINE_TYPE_VAR (0b00)
#define INLINE_TYPE_REF (0b10)
#define INLINE_TYPE_STR (0b01)
#define INLINE_TYPE_ARR (0b11)

enum E_CALLBACK_DATA
{
	// ===== ALWAYS FIRST  =====
	ResolvedAlloc:E_CALLBACK_DATA_ALLOC = 0, // Fully resolved memory address.
	// ===== ALWAYS SECOND =====
	Function:E_CALLBACK_DATA_POINTER = 1,    // Inline entry point.
	// ===== ALWAYS AFTER  =====
	E_CALLBACK_DATA_OFFSET,                  // Local variables size.
	E_CALLBACK_DATA_FORMAT[2]
}

static stock
	YSI_g_sRemoteFunctions  = -1, // Pointer to the remote function stubs list.
	YSI_g_sRemoteSpecifiers = -1, // Pointer to the remote function handlers.
	YSI_g_sRemoteStub       = -1, // The absolute address of the remote call stub.
	YSI_g_sRemoteStringsStart = -1,
	YSI_g_sRemoteStringsEnd   = -1,
	YSI_g_sPrevInlineFunc = 0,
	YSI_g_sPrevJumpOver = 0,
	YSI_g_sCurInlineLocals,  // Number of locals in current parent.
	YSI_g_sCurInlineParams,  // Number of parameters to current parent.
	YSI_g_sCurInlinePointer, // Storage for the inline function's return.
	YSI_g_sCurInlineEntry,   // Pointer to the start of the data segment.
	YSI_g_sCurInlineLoop,    // Pointer to the current loopback label.
	YSI_g_sCurInlineCode;    // Pointer to the start of user code.

static stock const
	YSI_g_scError[] = "\7\7\7*** YSI Error: Unrecognised compilation in y_inline.";

// Operators for doing "return" from inside an inline function.
#define inline_return YSI_gInlineRet+=
#define @return inline_return

stock
	InlineRet:YSI_gInlineRet;

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Calls functions we call via "SYSREQ.C".
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward _@_y_inline_@_();

public _@_y_inline_@_()
{
	strpack("", "");
	strcat("", "");
	strcmp("", "");
	strfind("", NULL);
	CallRemoteFunction("", "");
}

/*-------------------------------------------------------------------------*//**
 * <param name="from">Array of variable types.</param>
 * <param name="at">Type slot.</param>
 * <returns>
 *  The next variable type stored in the bit array.
 * </returns>
 * <remarks>
 *  Returns data from a bit array when it is known that only basic types are
 *  stored (i.e. no arrays with length parameters).
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Inline_DecodeSimple(from[],at));
#define Inline_DecodeSimple(%0,%1) (I@ = %0[(%1) >>> 5] & (2 << ((%1) & 0x1F)), (%1) += 2, I@)

// This used to be a compile-time macro to convert its parameters to the
// compressed format - it isn't anymore.  I tried to figure out if it was
// possible, and it probably is, but VERY hard, even compared to other macros
// I've written.
#define _F<%0> (#%0)

/*

    88b           d88            88                       db        88888888ba  88  
    888b         d888            ""                      d88b       88      "8b 88  
    88`8b       d8'88                                   d8'`8b      88      ,8P 88  
    88 `8b     d8' 88 ,adPPYYba, 88 8b,dPPYba,         d8'  `8b     88aaaaaa8P' 88  
    88  `8b   d8'  88 ""     `Y8 88 88P'   `"8a       d8YaaaaY8b    88""""""'   88  
    88   `8b d8'   88 ,adPPPPP88 88 88       88      d8""""""""8b   88          88  
    88    `888'    88 88,    ,88 88 88       88     d8'        `8b  88          88  
    88     `8'     88 `"8bbdP"Y8 88 88       88    d8'          `8b 88          88  

*/

stock Inline_Reset(callback[E_CALLBACK_DATA])
{
	return
		callback[E_CALLBACK_DATA_ALLOC] = ResolvedAlloc:0,
		callback[E_CALLBACK_DATA_POINTER] = Function:0,
		callback[E_CALLBACK_DATA_OFFSET] = 0,
		callback[E_CALLBACK_DATA_FORMAT] = 0,
		callback[E_CALLBACK_DATA_FORMAT + E_CALLBACK_DATA:1] = 0,
		0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="func">Public function to get.</param>
 * <param name="spec">The structure of the function's parameters.</param>
 * <returns>
 *  A pointer to the function.
 * </returns>
 * <remarks>
 *  Accepts the following parameter specifiers:
 *
 *      i - Integer (also x/c/d/h)
 *      f - Float (also g)
 *      s - String
 *      ai - Array (followed by length)
 *      v - Reference (&amp;var, any tag)
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Function:GetRemoteFunction(const func[], const spec[])
{
	if (YSI_g_sRemoteStub == -1)
	{
		// In this case everything is very simple because we know there can't be
		// any remote functions found so we can just make them instead of
		// wasting time searching.
		P:C(if (YSI_g_sRemoteFunctions != -1 || YSI_g_sRemoteSpecifiers != -1) P:E("Some, but not all, remote handlers installed."););
		// There are no handlers, so there is no stub written.
		YSI_g_sRemoteStub = Remote_WriteStubCode(),
		Remote_WriteJustSpec(ref(YSI_g_sRemoteSpecifiers), spec);
		return Function:Remote_WriteSpecAndFunc(ref(YSI_g_sRemoteFunctions), func, YSI_g_sRemoteSpecifiers, spec);
	}
	new
		fmatPtr = Remote_DoSearch(spec, YSI_g_sRemoteSpecifiers);
	if (fmatPtr == -1)
	{
		Remote_WriteJustSpec(ref(YSI_g_sRemoteSpecifiers), spec),
		fmatPtr = YSI_g_sRemoteSpecifiers;
	}
	else
	{
		// Found the specifier already defined, is this function already defined
		// for this specifier?
		new
			tmpPtr = AMX_Read(fmatPtr + 4),
			funcPtr = Remote_DoSearch(func, YSI_g_sRemoteFunctions);
		while (funcPtr != -1)
		{
			// Check if this instance of the function matches the specifier.
			if (AMX_Read(funcPtr + 2 * 4) == tmpPtr) return Function:(funcPtr + 3 * 4 - AMX_HEADER_COD);
			else funcPtr = Remote_DoSearch(func, AMX_Read(funcPtr));
		}
	}
	return Function:Remote_WriteSpecAndFunc(ref(YSI_g_sRemoteFunctions), func, fmatPtr, spec);
}

/*-------------------------------------------------------------------------*//**
 * <param name="func">Public function to get.</param>
 * <param name="spec">The structure of the function's parameters.</param>
 * <returns>
 *  A pointer to the function.
 * </returns>
 * <remarks>
 *  Accepts the following parameter specifiers:
 *
 *      i - Integer (also x/c/d/h)
 *      f - Float (also g)
 *      s - String
 *      ai - Array (followed by length)
 *      v - Reference (&amp;var, any tag)
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Function:GetLocalFunction(const func[], const spec[])
{
	// Get the function pointer.
	new
		fptr = funcidx(func);
	// Find the first match.
	if (fptr == -1) return Function:0;
	return Function:StoredF_WritePublicCode(fptr, spec);
}

/*-------------------------------------------------------------------------*//**
 * <param name="func">Function pointer to call.</param>
 * <param name="">The function's parameters.</param>
 * <remarks>
 *  Call the function in the given pointer with the given parameters.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock CallStoredFunction(Function:func, GLOBAL_TAG_TYPES:...)
{
	#pragma unused func
	new
		base,
		ctx[AsmContext];
	// Get this function.
	#emit CONST.pri  CallStoredFunction
	#emit LOAD.alt   AMX_HEADER_COD
	#emit ADD
	#emit STOR.S.pri base
	AsmInitPtr(ctx, base, 200);
	
	// Write safer code (to no longer crash).
	@emit PROC
	@emit LOAD.S.pri    12
	@emit JZER.rel      8
	@emit SCTRL         6
	@emit RETN
	
	// Recurse.
	#emit LCTRL         5
	#emit SCTRL         4
	#emit CONST.pri     CallStoredFunction
	#emit ADD.C         4
	#emit SCTRL         6
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Callback to find by name.</param>
 * <param name="ret">Where to store the pointer.</param>
 * <param name="expect">What parameters the function takes.</param>
 * <param name="remote">Is this function called on one or all scripts?</param>
 * <remarks>
 *  Looks up the callback by name.  If the name has the correct data embedded
 *  within it that's great and we use that directly.  Otherwise this function
 *  loops backwards over the callbacks currently in scope (mostly) to the start
 *  of the parent function.  If a match is still not found this looks for a
 *  public function of the same name.  If that isn't found either it gives up.
 *
 *  The new "remote" parameter returns instantly with a remote public function
 *  stub, and no stored data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Callback_Get(callback:name, ret[E_CALLBACK_DATA], expect[] = "", bool:remote = false)
{
	P:2("Callback_Get called: %s", name);
	Inline_Reset(ret);
	if (!(callback_tag:0 < name[0] < callback_tag:128))
	{
		P:3("Callback_Get: Found resolved callback.");
		// Resolved inline.
		return bool:memcpy(_:ret[E_CALLBACK_DATA:0], name[0], 0, _:E_CALLBACK_DATA * 4, _:E_CALLBACK_DATA);
	}
	else if (name[0] == callback_tag:'\03')
	{
		// This prefix is ALWAYS for publics not inlines.
		return bool:(ret[E_CALLBACK_DATA_POINTER] = (remote ? GetRemoteFunction(name[1], expect) : GetLocalFunction(name[1], expect)));
	}
	else if (remote)
	{
		// "remote" functions must always be done this way.
		return bool:(ret[E_CALLBACK_DATA_POINTER] = GetRemoteFunction(name, expect));
	}
	new
		pos = strfind(name, "\02"),
		frm = GetCurrentFramePreviousFrame(),
		prf = GetFramePreviousFrame(frm);
	if (pos == -1)
	{
		new
			cur = YSI_g_sPrevInlineFunc,
			parent = GetFrameFunction(prf),
			res;
		pos = strlen(name),
		frm = GetFrameReturn(frm);
		// Find the function by name.
		while (cur)
		{
			#emit PUSH.S      pos
			#emit PUSH.C      0
			#emit PUSH.S      name
			#emit PUSH.S      cur
			#emit PUSH.C      16
			#emit SYSREQ.C    strcmp
			#emit STACK       20
			#emit STOR.S.pri  res
			if (res == 0 && AMX_Read(cur + pos * 4) == '\02')
			{
				if (parent <= AMX_Read(cur + pos * 4 + 1 * 4) <= frm)
				{
					// Rewrite the value of "name" for the subsequent code.
					#emit LOAD.S.pri cur
					#emit STOR.S.pri name
					break;
				}
			}
			static const
				gsSearch[] = "\02";
			#emit PUSH.C      0
			#emit PUSH.C      0
			#emit PUSH.C      gsSearch
			#emit PUSH.S      cur
			#emit PUSH.C      16
			#emit SYSREQ.C    strfind
			#emit STACK       20
			#emit LOAD.S.alt  cur
			#emit IDXADDR
			#emit ADD.C       16
			#emit LOAD.I
			#emit STOR.S.pri  cur
		}
		if (!cur)
		{
			// Try publics...
			return bool:(ret[E_CALLBACK_DATA_POINTER] = GetLocalFunction(name, expect));
		}
	}
	static
		spec[2];
	Inline_EncodeFormatString(expect, spec),
	ret[E_CALLBACK_DATA_FORMAT] = spec,
	// Load this inline function's data in to our closure (and allocate memory).
	ret[E_CALLBACK_DATA_POINTER] = Function:name[pos + 1];
	new
		to = name[pos + 2],
		local = to >> 8, // Sign-extending!
		params = to & 0xFF,
		stack = params + local + 3,
		Alloc:a = malloc(stack); // Allocate closure space.
	// printf("local: %d, params: %d, stack: %d", local, params, stack);
	if (a)
	{
		// Get the stack size in bytes.
		stack <<= 2,
		// Get the address of the data.
		ret[E_CALLBACK_DATA_ALLOC] = Malloc_Resolve(a),
		frm = _:ret[E_CALLBACK_DATA_ALLOC],
		ret[E_CALLBACK_DATA_OFFSET] = stack,
		// Copy the stack over.  First get the frame of the function that used
		// an inline function, thus calling us indirectly.
		prf -= local << 2,
		// Adjust to the bottom of that stack, at least the bottom of the parts
		// we need (there may be more locals declared later that we don't need).
		// Copy "stack" bytes from "prf" to "frm".
		rawMemcpy(frm, prf, stack),
		// Save the "return" address for the inline to our fake stack.
		mset(a, local + 1, name[pos + 3]),
		// Save the parameter count (may be mangled by y_hooks).
		mset(a, local + 2, params << 2);
		P:2("Callback_Get end");
		return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="input">Callback to release.</param>
 * <remarks>
 *  Releases all the data associated with a given callback (closure storage).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Callback_Release(input[E_CALLBACK_DATA])
{
	// Check we were called by the correct frame.
	static
		ResolvedAlloc:ra,
		Alloc:a;
	if ((ra = input[E_CALLBACK_DATA_ALLOC]))
	{
		#emit CONST.alt     YSI_gMallocMemory
		#emit LOAD.pri      ra
		#emit SUB
		#emit SHR.C.pri     2
		#emit STOR.pri      a
		// Publics don't have any stored data.
		free(a),
		input[E_CALLBACK_DATA_ALLOC] = ResolvedAlloc:0;
	}
	return _:(input[E_CALLBACK_DATA_POINTER] = Function:0);
}

/*-------------------------------------------------------------------------*//**
 * <param name="func">Info on the restoration function.</param>
 * <remarks>
 *  Makes variables referenced, instead of valued.  When used after
 *  "Callback_Call" the values of any variables in the enclosing function that
 *  were modified in the inline function will be propgated so that their new
 *  values are seen by the original parent function (rather than that function
 *  still seeing the original values prior to the inline function modifying
 *  them).  Note that this does no checks at all at the minute - if you call an
 *  inline function whose parent is not currently on the stack, this will
 *  probably fail catastrophically!
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Callback_Restore(func[E_CALLBACK_DATA])
{
	if (func[E_CALLBACK_DATA_ALLOC])
	{
		// Copy the closure data back over the calling function.
		new
			frm = GetFramePreviousFrame(GetCurrentFramePreviousFrame()),
			ret = GetFrameReturn(frm),
			pfr = GetFramePreviousFrame(frm);
		rawMemcpy(frm + 12 + GetFrameParameterSize(frm) - func[E_CALLBACK_DATA_OFFSET], _:func[E_CALLBACK_DATA_ALLOC], func[E_CALLBACK_DATA_OFFSET]),
		SetFrameReturn(frm, ret),
		SetFramePreviousFrame(frm, pfr);
	}
	return 0;
}

/*

      ,ad8888ba,             88 88 88                          
     d8"'    `"8b            88 88 ""                          
    d8'                      88 88                             
    88            ,adPPYYba, 88 88 88 8b,dPPYba,   ,adPPYb,d8  
    88            ""     `Y8 88 88 88 88P'   `"8a a8"    `Y88  
    Y8,           ,adPPPPP88 88 88 88 88       88 8b       88  
     Y8a.    .a8P 88,    ,88 88 88 88 88       88 "8a,   ,d88  
      `"Y8888Y"'  `"8bbdP"Y8 88 88 88 88       88  `"YbbdP"Y8  
                                                   aa,    ,88  
                                                    "Y8bbdP"   

*/

/*-------------------------------------------------------------------------*//**
 * <param name="func">Info on the function to be called.</param>
 * <remarks>
 *  Takes an inline function handler and parameters, and either calls the
 *  public function while passing through the parameters, or just jumps to the
 *  carefully crafted inline function code.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Callback_Call(const func[E_CALLBACK_DATA], GLOBAL_TAG_TYPES:...)
{
	#pragma unused func
	new
		base,
		ctx[AsmContext];
	// Get this function.
	#emit CONST.pri  Callback_Call
	#emit LOAD.alt   AMX_HEADER_COD
	#emit ADD
	#emit STOR.S.pri base
	AsmInitPtr(ctx, base, 200);
	
	// Write safer code (to no longer crash).
	@emit PROC
	@emit LOAD.S.pri    12
	@emit ADD.C         4
	@emit LOAD.I
	@emit JZER.rel      8
	@emit SCTRL         6
	@emit RETN
	
	// Recurse.
	#emit LCTRL         5
	#emit SCTRL         4
	#emit CONST.pri     Callback_Call
	#emit ADD.C         4
	#emit SCTRL         6
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="func">Info on the function to be called.</param>
 * <param name="params">Array of data pointers.</param>
 * <param name="num">Size of the array.</param>
 * <remarks>
 *  This is very similar to Callback_Call, but takes an array of ADDRESSES
 *  instead of normal parameters.  This is designed to help support some
 *  experimental OO code I was working on...
 *
 *  If the target is a public function, the parameters are resolved and passed
 *  normally.  If the target is an inline function we are optimised for the
 *  common case, so move the data on to the stack (currently done value-by-value
 *  not all at once) and call "Callback_Call".
 *
 *  The new assembly is based on "rawMemset" in "y_utils".
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Callback_Array(const func[E_CALLBACK_DATA], const params[], num = sizeof (params))
{
	new
		base,
		ctx[AsmContext];
	// Get this function.
	#emit CONST.pri  Callback_Array
	#emit LOAD.alt   AMX_HEADER_COD
	#emit ADD
	#emit STOR.S.pri base
	AsmInitPtr(ctx, base, 200); // Don't need any more than that.
	
	// Start re-writing the function.  First copy "params" on to the stack.
	@emit PROC
	@emit LOAD.S.pri 20
	@emit JZER.rel   (26 * 4) // "num" is zero, do the simpler version.
	// @emit SHL.C.pri  2
	@emit SMUL.C     (-4)
	@emit STOR.pri   (base + 17 * 4)
	@emit NEG
	@emit STOR.pri   (base + 23 * 4)
	@emit ADD.C      4
	@emit STOR.pri   (base + 27 * 4)
	
	// Adjust the stack by "-num * 4" bytes.
	@emit STACK      0 // Value dynamically rewritten above.
	// Store the new pointer in "alt".
	@emit STACK      0 // Equivalent to: LCTRL 4; MOVE.alt (not rewritten).
	// Copy "num * 4" bytes from *pri to *alt (i.e. on to the stack).
	@emit LOAD.S.pri 16
	@emit MOVS       0 // Value dynamically rewritten above.
	
	// Call the next function.
	@emit PUSH.S     12
	@emit PUSH.C     0
	#emit CONST.pri  Callback_Call
	#emit STOR.S.pri base
	@emit CALL       (base + AMX_REAL_DATA + AMX_HEADER_COD)
	
	// End.
	@emit RETN
	
	// No parameters.  Call the inline function directly.
	@emit LOAD.S.pri 12
	@emit ADD.C      4
	@emit LOAD.I
	@emit SCTRL      6
	
	// Only here to appease the decompiler (sometimes).
	@emit NOP
	
	// Covertly call the newly re-written version of this function.
	#emit LCTRL      5
	#emit SCTRL      4
	#emit CONST.pri  Callback_Array
	#emit ADD.C      4
	#emit SCTRL      6
	
	// Never called, but includes the other function.
	return Callback_Call(func, params, num);
}

/*-------------------------------------------------------------------------*//**
 * <param name="func">The function to call on a delay.</param>
 * <param name="delay">how long before the first call?</param>
 * <param name="interval">How long between subsequent calls?</param>
 * <param name="repeat">How many times to call the function.</param>
 * <param name="format">The additional parameters' types.</param>
 * <param name="">The additional parameters.</param>
 * <remarks>
 *  Calls a function, which may be an inline function, after a given delay, and
 *  with the given regularity after that.  The parameters are slightly different
 *  to those in SetTimer - that takes only an interval and a repeat boolean.
 *  This instead takes two times - the first is the delay before the first call,
 *  the second is the delay between all subsequent calls (mainly to offset
 *  different timers within a given period).  The "repeat" parameter is also
 *  different - instead of being a boolean, it is a count.  "0" no longer means
 *  "don't repeat", but "repeat forever".  "1" no longer means "repeat forever",
 *  but "call once".  All other numbers (beside 0) specify an exact number of
 *  times to call the function before calling it no more.  This is in line with
 *  the "SetTimer_" and "SetTimerEx_" functions in the fixes2 plugin.
 * </remarks>
 *//*------------------------------------------------------------------------**/

/*

           db        ad88888ba  88b           d88     ad88888ba                                       
          d88b      d8"     "8b 888b         d888    d8"     "8b ,d                            ,d     
         d8'`8b     Y8,         88`8b       d8'88    Y8,         88                            88     
        d8'  `8b    `Y8aaaaa,   88 `8b     d8' 88    `Y8aaaaa, MM88MMM ,adPPYYba, 8b,dPPYba, MM88MMM  
       d8YaaaaY8b     `"""""8b, 88  `8b   d8'  88      `"""""8b, 88    ""     `Y8 88P'   "Y8   88     
      d8""""""""8b          `8b 88   `8b d8'   88            `8b 88    ,adPPPPP88 88           88     
     d8'        `8b Y8a     a8P 88    `888'    88    Y8a     a8P 88,   88,    ,88 88           88,    
    d8'          `8b "Y88888P"  88     `8'     88     "Y88888P"  "Y888 `"8bbdP"Y8 88           "Y888  

*/

/*-------------------------------------------------------------------------*//**
 * <param name="s">The array to store an inline function's data in.</param>
 * <param name="constFunc">Should this function copy the stack back?</param>
 * <remarks>
 *  AKA. Inline_Entry
 *
 *  This function gets the start of an inline function's code block.  It then
 *  removes itself from the compiled code so that it can never be called agian.
 *
 *  If "constFunc" is 3, copy the stack back, if it isn't don't.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock I@E(/* mutable */ const s[])
{
	P:2("Inline_Entry called: %s", s);
	new
		start = GetCurrentFrameReturn() - 24,
		ctx[DisasmContext];
	DisasmInit(ctx, start, start + 32);
	// Get parameter.
	// There is a chance that "s" has the same value as an opcode.  However, if
	// that is the case it will EITHER have the same value as "PUSH.C" OR the
	// same value as "PUSH.pri" - it can't have the same value as both, so this
	// code will still catch that case.
	if (!DisasmDecodeInsn(ctx) || DisasmGetOpcode(ctx) != OP_PUSH_C || DisasmGetOperand(ctx) != GetCurrentFrameParameter(0))
	{
		// Compiled with extra debug information.
		start -= 4,
		ctx[DisasmContext_nip] = ctx[DisasmContext_start_ip] -= 4,
		// This mode uses "CONST.pri x; PUSH.pri" instead of "PUSH.C x".
		DisasmDecodeInsn(ctx);
		if (DisasmGetOpcode(ctx) != OP_CONST_PRI || DisasmGetOperand(ctx) != GetCurrentFrameParameter(0)) return Debug_Print0(YSI_g_scError);
		DisasmDecodeInsn(ctx);
		if (DisasmGetOpcode(ctx) != OP_PUSH_PRI) return Debug_Print0(YSI_g_scError);
	}
	// Function parameter count.
	DisasmDecodeInsn(ctx);
	if (DisasmGetOpcode(ctx) != OP_PUSH_C || DisasmGetOperand(ctx) != 4) return Debug_Print0(YSI_g_scError);
	// Function call.
	DisasmDecodeInsn(ctx);
	if (DisasmGetOpcode(ctx) != OP_CALL) return Debug_Print0(YSI_g_scError);
	// Jump.
	DisasmDecodeInsn(ctx);
	if (DisasmGetOpcode(ctx) != OP_JZER) return Debug_Print0(YSI_g_scError);
	// Write out the jump for future calls.
	new
		addr1 = AMX_Read(YSI_g_sPrevJumpOver),
		addr2 = start + AMX_HEADER_COD,
		frm = DisasmGetOperand(ctx);
	if (YSI_g_sPrevJumpOver && addr1 == addr2 + AMX_REAL_ADDRESS - AMX_BASE_ADDRESS)
	{
		// Multiple inline functions in a row.  Jump over them all.
		AMX_Write(YSI_g_sPrevJumpOver, frm),
		YSI_g_sCurInlineEntry = start;
	}
	else if (YSI_g_sPrevJumpOver && addr1 == addr2 + AMX_REAL_ADDRESS - AMX_BASE_ADDRESS - 4 && Opcode:AMX_Read(addr2) == RelocateOpcode(OP_BREAK))
	{
		// Multiple inline functions in a row.  Jump over them all.
		AMX_Write(YSI_g_sPrevJumpOver, frm),
		YSI_g_sCurInlineEntry = start - 4;
	}
	else
	{
		new
			ctx2[AsmContext];
		AsmInitPtr(ctx2, addr2, 8),
		AsmEmitJump(ctx2, frm),
		YSI_g_sPrevJumpOver = addr2 + 4,
		YSI_g_sCurInlineEntry = start + 8;
	}
	// Store the pointer to the start of this new inline's available code.
	// =========================================================================
	// Save the data name pointer.
	addr2 = ref(s[strfind(s, ":")]),
	AMX_Write(addr2, '\02;'),
	AMX_Write(addr2 + 4, YSI_g_sCurInlineEntry),
	// Get the number of local variables already in the parent function.
	frm = GetCurrentFramePreviousFrame(),
	YSI_g_sCurInlineLocals = GetFrameLocalSize(frm),
	YSI_g_sCurInlineParams = GetFrameParameterSize(frm),
	// y_hooks mangles the parameter count.  In this case, the correct parameter
	// count is stored in the previous frame, which is the entry point for the
	// generated hook function stub.
	YSI_g_sCurInlineParams = (YSI_g_sCurInlineParams == -4) ? GetFrameParameterSize(GetFramePreviousFrame(frm)) : YSI_g_sCurInlineParams;
	P:C(if (YSI_g_sCurInlineParams < 0) P:E("Inline_Entry: Invalid parameter size."););
	// Save parameter counts, shifted for separate components.
	AMX_Write(addr2 + 8, (YSI_g_sCurInlineLocals ? (YSI_g_sCurInlineLocals << 6) : (-4 << 6)) | (YSI_g_sCurInlineParams >> 2)),
	// =========================================================================
	// Build a linked list of inlines that are in scope.
	AMX_Write(addr2 + 16, YSI_g_sPrevInlineFunc),
	YSI_g_sCurInlinePointer = addr2 + 12,
	YSI_g_sPrevInlineFunc = ref(s);
	// Return 1 to enter the main "inline" function block.
	return 1;
}

/*

           db        ad88888ba  88b           d88    8b           d8                                
          d88b      d8"     "8b 888b         d888    `8b         d8'                                
         d8'`8b     Y8,         88`8b       d8'88     `8b       d8'                                 
        d8'  `8b    `Y8aaaaa,   88 `8b     d8' 88      `8b     d8' ,adPPYYba, 8b,dPPYba, ,adPPYba,  
       d8YaaaaY8b     `"""""8b, 88  `8b   d8'  88       `8b   d8'  ""     `Y8 88P'   "Y8 I8[    ""  
      d8""""""""8b          `8b 88   `8b d8'   88        `8b d8'   ,adPPPPP88 88          `"Y8ba,   
     d8'        `8b Y8a     a8P 88    `888'    88         `888'    88,    ,88 88         aa    ]8I  
    d8'          `8b "Y88888P"  88     `8'     88          `8'     `"8bbdP"Y8 88         `"YbbdP"'  

*/

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  AKA. Inline_Allocator.
 *
 *  This function determines the exact address of the start of the main inline
 *  function container loop.  That is, the label that things like "continue"
 *  jump to so that we know how much space we have to play with and where it is.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock I@F()
{
	P:2("Inline_Allocator called");
	// This function takes up almost no space in a .pwn, but loads in a .amx.
	// Or at least as much as I want it to in order to give me code space to
	// play with.
	new
		start = GetCurrentFrameReturn(),
		ctx[DisasmContext];
	// "end" isn't currently used in "disasm", but we can't guarantee that.
	DisasmInit(ctx, start, start + 16);
	DisasmDecodeInsn(ctx);
	if (DisasmGetOpcode(ctx) != OP_JZER) return Debug_Print0(YSI_g_scError);
	// Get the end of the outer loop.
	YSI_g_sCurInlineCode = DisasmGetOperand(ctx);
	if (DisasmDecodeInsn(ctx) && DisasmGetOpcode(ctx) == OP_BREAK)
	{
		if (DisasmDecodeInsn(ctx) && DisasmGetOpcode(ctx) == OP_BREAK)
		{
			// Two breaks in a row - skip one.
			start += 4;
		}
		else Debug_Print0(YSI_g_scError);
	}
	// "start" now (hopefully) points to the main loop start address.
	YSI_g_sCurInlineLoop = start + 8;
	return 1;
}

/*

           db        ad88888ba  88b           d88    88888888888                      88  
          d88b      d8"     "8b 888b         d888    88                               88  
         d8'`8b     Y8,         88`8b       d8'88    88                               88  
        d8'  `8b    `Y8aaaaa,   88 `8b     d8' 88    88aaaaa     8b,dPPYba,   ,adPPYb,88  
       d8YaaaaY8b     `"""""8b, 88  `8b   d8'  88    88"""""     88P'   `"8a a8"    `Y88  
      d8""""""""8b          `8b 88   `8b d8'   88    88          88       88 8b       88  
     d8'        `8b Y8a     a8P 88    `888'    88    88          88       88 "8a,   ,d88  
    d8'          `8b "Y88888P"  88     `8'     88    88888888888 88       88  `"8bbdP"Y8  

*/

/*-------------------------------------------------------------------------*//**
 * <returns>
 *  0
 * </returns>
 * <remarks>
 *  AKA. Inline_Main.
 *
 *  The code before the start of the function is split in to three parts:
 *
 *  The first part comes before the start of the loop condition, and is where
 *  all the variables are initialised in the compiled code.  As we don't want to
 *  initialise any variables, this can be repurposed for function entry code.
 *  The address of this is stored in "entry", and it ends at "loop".
 *
 *  The second part is where the function loops back to.  This MUST start with a
 *  "RETN" instruction to end the function in all cases, so any startup code in
 *  the first segment must jump over that "RETN".  The remainder of this section
 *  can be used for any more entry or exit code that is required.  Note that
 *  it can also start with a "STACK" opcode when required.  This section starts
 *  at "loop" and ends at "code".
 *
 *  The final segment is not technically BEFORE the main function code but
 *  AFTER.  That's normally where the stack is restored, but we now have full
 *  control of that (so don't forget to write it in to the process exit code).
 *
 *  "Inline_Allocator" currently marks the end of the first segment, and
 *  "Inline_Main" marks the end of the second segment.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock
	YSI_g_sJumpAddress,
	YSI_g_sRequiredSpace;

forward Inline_OnAsmError(ctx[AsmContext], AsmError:error);

public Inline_OnAsmError(ctx[AsmContext], AsmError:error)
{
	if (numargs() == 1) error = AsmGetError(ctx);
	// Actually USE the error to write the "JUMP" instruction correctly.
	switch (error)
	{
		case ASM_ERROR_SPACE:
		{
			if (YSI_g_sJumpAddress) P:E("ASM_ERROR_SPACE in Inline_Main.");
			else
			{
				// Get where the last instruction started to be written.
				ctx[AsmContext_buffer_offset] = YSI_g_sJumpAddress = AsmGetPreviousWriteOffset(),
				// Calculate how much of the function header was NOT written.
				YSI_g_sRequiredSpace -= YSI_g_sJumpAddress,
				// Save the address of the "JUMP" operand for later.
				YSI_g_sJumpAddress += 4 + ctx[AsmContext_buffer],
				// Allocate space for writing the "JUMP" (previously skipped).
				ctx[AsmContext_buffer_size] = cellmax;
				// Jump over the function end.
				@emit JUMP    0
				new
					target = YSI_g_sCurInlineCode + AMX_HEADER_COD - ctx[AsmContext_buffer] - YSI_g_sRequiredSpace;
				// Pad everything with "NOP"s.
				while (ctx[AsmContext_buffer_offset] != target) @emit NOP
				// Write the jump target as here.
				AMX_Write(YSI_g_sJumpAddress, ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset] - AMX_BASE_ADDRESS + AMX_REAL_ADDRESS);
			}
		}
		case ASM_ERROR_OPCODE : P:E("ASM_ERROR_OPCODE in Inline_Main.");
		case ASM_ERROR_OPERAND: P:E("ASM_ERROR_OPERAND in Inline_Main.");
	}
}

// "tryemit"
// This macro detects when an opcode couldn't be written due to a lack of space
// in the buffer, then instantly re-writes the same opcode to the same context!
// The reason this works is that there is an error handler that is called BEFORE
// "amx_emit_" returns the error code, and that handler deals with all the
// complex reallocations and jumps required to move the code about (in this case
// to fit around the existing jumps in the code around where we are writing new
// code).
#define _@emit%0\32;%1\10;%3 if(asm_emit_(ctx,%1 ) == ASM_ERROR_SPACE) asm_emit_(ctx,%1 );

stock I@K(...)
{
	return numargs() * 3;
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

stock I@L(constFunc, ...)
{
	//new
	//	bool:constFunc = I@;
	P:2("Inline_Main called (%d)", numargs());
	// MOST IMPORTANT THING TO DO FIRST!  Get the address to jump back to.
	new
		ret = GetCurrentFrameReturn(),
		heapClean = 0,
		dctx[DisasmContext];
	DisasmInit(dctx, ret, ret + 20),
	// Get the next code instruction.
	DisasmDecodeInsn(dctx);
	// There is some heap to clean up, how much?
	if (DisasmGetOpcode(dctx) == OP_HEAP)
	{
		ret += 8,
		heapClean = DisasmGetOperand(dctx),
		DisasmDecodeInsn(dctx);
	}
	// Get the jump to the end of the main loop.
	if (DisasmGetOpcode(dctx) != OP_JZER) return Debug_Print0(YSI_g_scError);
	// Set this function to return to the end of the outer loop.
	SetCurrentFrameReturn(YSI_g_sCurInlineCode - AMX_REAL_ADDRESS - (AMX_HEADER_COD - AMX_BASE_ADDRESS));
	// =========================================================================
	//     NOW WE CAN DO THE MAIN FUNCTION CODE.
	// =========================================================================
	new
		argSize = GetFrameLocalSize(GetCurrentFramePreviousFrame());
	// Do we have enough space for everything.
	// Get the start of the user's function code.  The real start of THEIR code.
	ret += 8;
	if (DisasmDecodeInsn(dctx) && DisasmGetOpcode(dctx) == OP_BREAK) ret += 4;
	YSI_g_sCurInlineCode = ret;
	P:5("Inline_Main: YSI_g_sCurInlineEntry = %x", YSI_g_sCurInlineEntry);
	P:5("Inline_Main: YSI_g_sCurInlineLoop = %x", YSI_g_sCurInlineLoop);
	P:5("Inline_Main: YSI_g_sCurInlineCode = %x", YSI_g_sCurInlineCode);
	// Get the segment sizes and variable type counts.
	new
		args = numargs() - 1,
		varCount = 0;
	#define arrCount (args - varCount - strCount)
	#define strCount ret
	strCount = 0;
	for (new i = 1; i <= args; ++i)
	{
		switch (getarg(i))
		{
			case 0, -1:   ++varCount;
			case cellmax: ++strCount;
		}
	}
	P:5("Inline_Main: varCount = %d", varCount);
	P:5("Inline_Main: arrCount = %d", arrCount);
	P:5("Inline_Main: strCount = %d", strCount);
	// So-far, so-good.  The code above in preliminary tests seems to correctly
	// identify all the relevant and important points in the user code.
	new
		ctx[AsmContext];
	// =========================================================================
	//     CODE SPACE AVAILABLE
	// =========================================================================
	//  
	//  Inline_Entry: 6
	//  Vars: 2 v+r
	//  Arrays: 7 a
	//  JUMP: 2
	//  Inline_Allocator: 6
	//  
	//  Arrays: 6 a
	//  Vars: 5 v
	//  Refs: 6 r
	//  
	//  Inline_Main: 19
	//  
	//  Simple Total: 14 + 7v + 8r + 19
	//  Complex Total: 14 + 7v + 8r + 17a + 19
	//  
	//  Simple Required: 15 + 3v + 7r + 16
	//  Complex Required: 15 + 4v + 8r + 6a + 16
	//  
	// =========================================================================
	//     SEGMENT 1 - RESOLVE AND PUSH CLOSURE DATA AND PARAMETERS
	// =========================================================================
	YSI_g_sJumpAddress = 0,
	AsmInitPtr(ctx, YSI_g_sCurInlineEntry + AMX_HEADER_COD, YSI_g_sCurInlineLoop - YSI_g_sCurInlineEntry - 8),
	AsmSetErrorHandler(ctx, GetPublicAddressFromName("Inline_OnAsmError"));
	// Space for params + count.
	new
		// Size of stored closure data.
		offset = (YSI_g_sCurInlineParams + YSI_g_sCurInlineLocals + 12);
	if (varCount == args) // Only variables.
	{
		// =====================================================================
		//     SIMPLE CODE - NO ARRAYS OR STRINGS
		// =====================================================================
		if (YSI_g_sCurInlineLocals)
		{
			P:5("Inline_Main: TYPE 0");
			YSI_g_sRequiredSpace = 4 * 3 * args + 4 * 13;
			_@emit STACK      (-offset)
			_@emit ADDR.alt   (-offset) // Like "LCTRL 4; XCHG", but shorter.
			_@emit LREF.S.pri 12   // Load "func" variable.
			// Sadly "MOVS" checks that the destination is valid and in the stack, which
			// is what we didn't want.
			_@emit MOVS       offset
			// Reduce the stack again.  This is the shortest way I know (5 cells).
			_@emit STACK      (4 + YSI_g_sCurInlineLocals)
			_@emit PROC       // Set up the new frame.
			_@emit STACK      (-YSI_g_sCurInlineLocals) // Skip other locals again.
			new
				// Get the offset to the calling function's passed parameters.
				// 12 for this function's header, plus this function's parameters, plus
				// the last function's locals (currently none, MUST BE KEPT UP TO DATE),
				// plus the last function's header, plus the "func" variable.
				load = 12 + YSI_g_sCurInlineParams + 0 + 12 + 4,
				i = 0;
			while (i++ < args)
			{
				// Loop over the arguments and push them.
				_@emit LREF.S.pri load
				_@emit PUSH.pri
				load += 4;
			}
		}
		else
		{
			P:5("Inline_Main: TYPE 1 (%d, %d, %d, %d, %d)", offset, offset - 4, args, 4 * 3 * args + 4 * 9, 12 + YSI_g_sCurInlineParams + 0 + 12 + 4);
			// This is the simplest of the four versions of the code.  Here
			// there are no arrays to copy over, nor are there any local
			// variables from the closure.
			offset -= 4,
			YSI_g_sRequiredSpace = 4 * 3 * args + 4 * 9;
			_@emit STACK      (-offset)
			_@emit ADDR.alt   (-offset)
			_@emit LREF.S.pri 12
			_@emit MOVS       offset
			_@emit PROC
			new
				load = 12 + YSI_g_sCurInlineParams + 0 + 12 + 4,
				i = 0;
			while (i++ < args)
			{
				_@emit LREF.S.pri load
				_@emit PUSH.pri
				load += 4;
			}
			offset += 4;
		}
	}
	else
	{
		// =====================================================================
		//     COMPLEX CODE - ARRAYS OR STRINGS
		// =====================================================================
		if (YSI_g_sCurInlineLocals)
		{
			P:5("Inline_Main: TYPE 2");
			YSI_g_sRequiredSpace = 4 * 4 * varCount + 4 * 6 * arrCount + 4 * 14 * strCount + 4 * 13;
			_@emit STACK      (-offset)
			_@emit STACK      (YSI_g_sCurInlineLocals - argSize)
			_@emit LREF.S.pri 12
			_@emit MOVS       offset
			new
				load = 12 + 4,
				stor = -offset,
				i = 0;
			while (i < args)
			{
				if ((varCount = getarg(++i)) == cellmax)
				{
					// String.
					stor -= YSI_MAX_INLINE_STRING * 4;
					_@emit PUSH.C     YSI_MAX_INLINE_STRING
					_@emit PUSH.S     load // src = *cur
					_@emit ZERO.S     stor // dest[0] = '\0';
					_@emit PUSH.adr   stor // dst = &dest
					_@emit PUSH.C     12
					_@emit SYSREQ     "strcat"
					_@emit STACK      16
				}
				else
				{
					if ((varCount *= 4) <= 0)
					{
						// Normal variable.
						stor -= 4;
						_@emit LREF.S.pri load
						_@emit STOR.S.pri stor
					}
					else 
					{
						// Array.
						stor -= varCount;
						_@emit LOAD.S.pri load
						_@emit ADDR.alt   stor
						_@emit MOVS       varCount
					}
				}
				load += 4;
			}
			_@emit STACK      (4 + argSize)
			_@emit PROC
			_@emit STACK      (-argSize)
		}
		else
		{
			P:5("Inline_Main: TYPE 3");
			offset -= 4,
			YSI_g_sRequiredSpace = 4 * 4 * varCount + 4 * 6 * arrCount + 4 * 14 * strCount + 4 * 11;
			_@emit STACK      (-offset)
			_@emit ADDR.alt   (-offset)
			_@emit LREF.S.pri 12
			_@emit MOVS       offset
			_@emit PROC
			_@emit STACK      (-argSize)
			new
				load = 12 + YSI_g_sCurInlineParams + 0 + 12 + 4,
				stor = 0,
				i = 0;
			while (i < args)
			{
				if ((varCount = getarg(++i)) == cellmax)
				{
					// String.
					stor -= YSI_MAX_INLINE_STRING * 4;
					_@emit PUSH.C     YSI_MAX_INLINE_STRING
					_@emit PUSH.S     load // src = *cur
					_@emit ZERO.S     stor // dest[0] = '\0';
					_@emit PUSH.adr   stor // dst = &dest
					_@emit PUSH.C     12
					_@emit SYSREQ     "strcat"
					_@emit STACK      16
				}
				else
				{
					if ((varCount *= 4) <= 0)
					{
						// Normal variable.
						stor -= 4;
						_@emit LREF.S.pri load
						_@emit STOR.S.pri stor
					}
					else 
					{
						// Array.
						stor -= varCount;
						_@emit LOAD.S.pri load
						_@emit ADDR.alt   stor
						_@emit MOVS       varCount
					}
				}
				load += 4;
			}
			offset += 4;
		}
	}
	// =========================================================================
	//     SEGMENT 2 - SAVE REFERENCES BACK
	// =========================================================================
	if (YSI_g_sJumpAddress == 0)
	{
		// Fake an error.  This indirectly calls the "Inline_OnAsmError"
		// function above to fill the intervening space with NOPs.
		ctx[AsmContext_buffer_size] = 0;
		@emit NOP
	}
	// The maths should now be correct.
	AsmInitPtr(ctx, YSI_g_sCurInlineLoop + AMX_HEADER_COD, cellmax);
	if (argSize)
	{
		@emit STACK     argSize
		YSI_g_sJumpAddress = YSI_g_sCurInlineLoop + 16;
	}
	else
	{
		YSI_g_sJumpAddress = YSI_g_sCurInlineLoop + 8;
	}
	@emit ZERO.pri // Default return value.
	@emit RETN
	// Save this return address, so the instruction above goes to the one below.
	// Save references.
	new
		load = -offset,
		stor = 12 + 4,
		i = 0;
	while (i < args)
	{
		varCount = getarg(++i);
		switch (varCount)
		{
			case -1:
			{
				load -= 4;
				@emit LOAD.S.alt load
				@emit SREF.S.alt stor
			}
			case 0: load -= 4;
			case cellmax: load -= YSI_MAX_INLINE_STRING * 4;
			default: load -= varCount * 4;
		}
		stor += 4;
	}
	// Copy the closure back (if there is anything that needs copying).
	if (constFunc && (YSI_g_sCurInlineParams || YSI_g_sCurInlineLocals))
	{
		if (!YSI_g_sCurInlineLocals) offset -= 4;
		@emit STACK      (-offset)
		@emit PUSH.pri
		@emit ADDR.pri   (-offset)
		@emit LREF.S.alt 12
		@emit MOVS       offset
		@emit POP.pri
		@emit STACK      offset
	}
	// Finish.
	@emit RETN
	// =========================================================================
	//     STORE THE RETURN ADDRESS
	// =========================================================================
	AMX_Write(YSI_g_sCurInlinePointer, YSI_g_sJumpAddress),
	AMX_Write(YSI_g_sCurInlinePointer - 12, '\02;');
	// =========================================================================
	//     FUNCTION EPILOG
	// =========================================================================
	// Clean up the heap manually because we are jumping straight over the
	// original cleanup code - in fact we may have destroyed it entirely by
	// writing new code over it.
	#emit LCTRL      2
	#emit LOAD.S.alt heapClean
	#emit ADD
	#emit SCTRL      2
	
	// Cleanup.
	return 0;
	#undef strCount
	#undef arrCount
}

#undef _@emit

/*

    88888888ba              88          88 88                       
    88      "8b             88          88 ""                       
    88      ,8P             88          88                          
    88aaaaaa8P' 88       88 88,dPPYba,  88 88  ,adPPYba, ,adPPYba,  
    88""""""'   88       88 88P'    "8a 88 88 a8"     "" I8[    ""  
    88          88       88 88       d8 88 88 8b          `"Y8ba,   
    88          "8a,   ,a88 88b,   ,a8" 88 88 "8a,   ,aa aa    ]8I  
    88           `"YbbdP'Y8 8Y"Ybbd8"'  88 88  `"Ybbd8"' `"YbbdP"'  

*/

/*-------------------------------------------------------------------------*//**
 * <param name="addr">Function start address.</param>
 * <returns>
 *  Is the function at this address already hooked by us?
 * </returns>
 *//*------------------------------------------------------------------------**/

static stock StoredF_IsHooked(addr)
{
	// Find out if the given address points to a public function that we have
	// already hooked in to for faster calling.
	return AMX_Read(addr + AMX_HEADER_COD) == _:RelocateOpcode(OP_JUMP);
}

/*-------------------------------------------------------------------------*//**
 * <param name="ctx">Current code generation context.</param>
 * <param name="error">The error given.</param>
 * <remarks>
 *  This is a fatal error as there isn't really anything we can do about it.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward StoredF_OnPubGenError(ctx[AsmContext], AsmError:error);

public StoredF_OnPubGenError(ctx[AsmContext], AsmError:error)
{
	// This is very bad, in fact I'd say this is a fatal error.
	P:F("Inline_OnPubGenError called - Try increase\"YSI_Internal\\y_cgen.inc: _@_y_cgen_@_0\"'s code size");
}

/*-------------------------------------------------------------------------*//**
 * <param name="fptr">Function start address.</param>
 * <param name="spec">Function parameter types.</param>
 * <returns>
 *  the new function pointer.
 * </returns>
 * <remarks>
 *  Writes a stub for calling a public function with an alternate method.
 *  Because "CallStoredFunction" (the call entry point) takes all its parameters
 *  by reference and some of the actual function's parameters won't be, we have
 *  to generate the code to convert those that aren't to values only.  Also,
 *  because "CallStoredFunction" takes an extra parameter that's the address of
 *  the function to call, we have to wipe that from the stack and update the
 *  resulting frame header.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock StoredF_WritePublicCode(fptr, const spec[])
{
	new
		entry = AMX_HEADER_PUBLICS + fptr * 8;
	fptr = AMX_Read(entry);
	if (StoredF_IsHooked(fptr)) return fptr + 8;
	new
		ctx[AsmContext];
	CGen_UseCodeSpace(ctx),
	AsmSetErrorHandler(ctx, GetPublicAddressFromName("StoredF_OnPubGenError"));
	// Rewrite the function pointer.
	new
		nptr = CGen_GetCodeSpace() - AMX_HEADER_COD;
	AMX_Write(entry, nptr);
	// Get the absolute address of "fptr".
	fptr += AMX_HEADER_COD + AMX_REAL_DATA;
	// Jump to the original function when called in other ways.
	@emit JUMP          fptr
	// Inline calls use the address AFTER that jump to do extra work.
	// First, adjust the stack.
	@emit POP.alt       // Pop the previous frame.
	@emit POP.pri       // Pop the return address.
	@emit SWAP.pri      // Swap the return address and parameter count.
	@emit ADD.C         (-4) // Remove one parameter.
	@emit STOR.S.pri    12   // Save the new parameter count.
	// Update the frame pointer.
	@emit PROC          // Write a new frame pointer to update the stack.
	@emit SWAP.alt      // Swap the new "previous" frame with the real one.
	// Reify reference variables that shouldn't be so.
	new
		var = strlen(spec);
	entry = var * 4 + 8;
	while (var--)
	{
		switch (spec[var])
		{
			case 'a', 's', 'v': {} // No modification required.
			default:
			{
				// Resolve the reference's value.
				@emit LREF.S.alt entry
				@emit STOR.S.alt entry
			}
		}
		entry -= 4;
	}
	// Now we jump to the original function.
	@emit JUMP          (fptr + 4)
	CGen_AddCodeSpace(AsmGetCodeSize(ctx));
	return nptr + 8;
}

/*

    88888888ba                                                                       
    88      "8b                                           ,d                         
    88      ,8P                                           88                         
    88aaaaaa8P' ,adPPYba, 88,dPYba,,adPYba,   ,adPPYba, MM88MMM ,adPPYba, ,adPPYba,  
    88""""88'  a8P_____88 88P'   "88"    "8a a8"     "8a  88   a8P_____88 I8[    ""  
    88    `8b  8PP""""""" 88      88      88 8b       d8  88   8PP"""""""  `"Y8ba,   
    88     `8b "8b,   ,aa 88      88      88 "8a,   ,a8"  88,  "8b,   ,aa aa    ]8I  
    88      `8b `"Ybbd8"' 88      88      88  `"YbbdP"'   "Y888 `"Ybbd8"' `"YbbdP"'  

*/

#if 0
	enum E_REMOTE_FUNC_STUB
	{
		*E_REMOTE_FUNC_STUB_NEXT,
		*E_REMOTE_FUNC_STUB_NAME,
		CONST.pri /* SPEC ADDR */
		CONST.alt /* FUNC ADDR */
		JUMP      /* STUB ADDR */
	}
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="str">String to find.</param>
 * <param name="ptr">Start of the linked list.</param>
 * <remarks>
 *  Finds a given string in a given list.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Remote_DoSearch(const str[], ptr)
{
	// Given a start pointer and a string, find the pointer before this string.
	new
		result;
	while (ptr != -1)
	{
		#emit PUSH.C     0x7FFFFFFF
		#emit PUSH.C     0
		#emit PUSH.S     str
		#emit LOAD.S.pri ptr
		#emit ADD.C      4
		#emit PUSH.pri
		#emit LREF.S.pri 0xFFFFFFEC
		#emit SWAP.pri
		// Compare the strings.
		#emit PUSH.C     16
		#emit SYSREQ.C   strcmp
		#emit STACK      20
		#emit STOR.S.pri result
		// Result found.  Return.
		if (!result) return ptr;
		{}
		// Didn't find it yet, try the next one.
		#emit LREF.S.pri ptr
		#emit STOR.S.pri ptr
	}
	return -1;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  This rewrites itself to be the bulk of the call to "CallRemoteFunction".  It
 *  modifies the stack so that the parameters already pushed are the parameters
 *  passed to the native function.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Remote_WriteStubCode()
{
	new
		base,
		ctx[AsmContext];
	// Get this function.
	#emit CONST.pri  Remote_WriteStubCode
	#emit LOAD.alt   AMX_HEADER_COD
	#emit ADD
	#emit STOR.S.pri base
	AsmInitPtr(ctx, base, 200); // Don't need any more than that.
	
	// This function is jumped in to from "CallStoredFunction" via a
	// per-function stub.  Sadly, this means that the highly optimised 21 cell
	// version of the code that I wrote won't work.  It is now 30 in total,
	// excluding the stub code (which is, and was, an extra 5 cells).  This is
	// called with "alt" = function name, "pri" = specifier string.
	
	// Write the specifier string.
	@emit STOR.S.pri 12
	
	// Get the return address, and put the frame at the top of the stack.
	@emit POP.pri
	@emit SWAP.pri
	@emit ADD.C      (AMX_REAL_DATA + AMX_HEADER_COD) // Make absolute.
	@emit STOR.pri   (base + 26 * 4) // [JUMP ADDRESS]
	
	// We have popped from the stack, but the frame pointer is still wrong.  Get
	// the parameter count and replace that location with the function pointer.
	@emit LOAD.S.pri 8
	@emit STOR.S.alt 8
	
	// Update the parameter count.
	@emit ADD.C      8
	@emit STOR.pri   (base + 24 * 4) // [STACK ADDRESS]
	@emit ADD.C      (-4)
	@emit SWAP.pri
	
	// Stored the parameter count and got the frame pointer.
	@emit SCTRL      5
	
	// Call "CallRemoteFunction".
	@emit SYSREQ     "CallRemoteFunction"
	
	// End this function and return to the caller.
	@emit STACK      0  // [STACK ADDRESS]
	@emit JUMP       0  // [JUMP ADDRESS]
	
	// Unlike most other self-modifying functions, this one does NOT call itself
	// because it is called before it is required.  Instead we just return to
	// the caller that was preparing this setup in advance and pass it the
	// absolute address of the start of the function (for jump purposes).
	return base + AMX_REAL_DATA;
}

static stock Remote_RawStrpack(dest, const src[])
{
	static
		sRemoteStringsStart = -1,
		sRemoteStringsEnd   = -1;
	new
		len = (strlen(src) + 1) char * 4;
	if (sRemoteStringsStart + len > sRemoteStringsEnd)
	{
		static
			sPtr = -1;
		if (sPtr == -1)
		{
			// Get the malloc base pointer.
			#emit CONST.pri  YSI_gMallocMemory
			#emit STOR.pri   sPtr
		}
		// No space to copy this string.  Reallocate some memory.
		sRemoteStringsStart = _:malloc(1024) * 4 + sPtr,
		sRemoteStringsEnd   = sRemoteStringsStart + 1024 * 4;
	}
	{}
	#emit PUSH.C     1024
	#emit PUSH.S     src
	#emit LOAD.pri   sRemoteStringsStart
	#emit PUSH.pri
	#emit SREF.S.pri dest
	#emit LOAD.S.alt len
	#emit ADD
	#emit STOR.pri   sRemoteStringsStart
	#emit PUSH.C     12
	#emit SYSREQ.C   strpack
	#emit STACK      16
	return 0;
}

static stock Remote_WriteJustSpec(/* & */ sptr, const spec[])
{
	// Get the new write location.
	new
		ptr = CGen_GetCodeSpace();
	// Add to the front of the list
	AMX_Write(ptr, AMX_Read(sptr)),
	AMX_Write(sptr, ptr),
	// Store the specifier.
	Remote_RawStrpack(ptr + 4, spec);
	CGen_AddCodeSpace(2 * 4);
}

/*-------------------------------------------------------------------------*//**
 * <param name="fptr">Pointer in which to store the function.</param>
 * <param name="func">Name of the function.</param>
 * <param name="sptr">Pointer to the stored specifier string.</param>
 * <param name="spec">Usable specifier string.</param>
 * <returns>
 *  A pointer to the start of the newly generated code.
 * </returns>
 * <remarks>
 *  Generates a tiny function-specific stub that sets the values for the
 *  function and specifier strings to pass to "CallRemoteFunction", and checks
 *  for any empty strings - converting them to "NULL" instead.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Remote_WriteSpecAndFunc(/* & */ fptr, const func[], sptr, const spec[])
{
	new
		ptr = CGen_GetCodeSpace();
	// Add to the front of the list
	AMX_Write(ptr, AMX_Read(fptr)),
	AMX_Write(fptr, ptr),
	// Store the function name.
	Remote_RawStrpack(ptr + 4, func),
	sptr = AMX_Read(sptr + 4),
	AMX_Write(ptr + 8, sptr),
	// Write the code.
	CGen_AddCodeSpace(3 * 4); // Pointers.
	new
		ctx[AsmContext];
	CGen_UseCodeSpace(ctx);
	// Convert empty strings to "NULL" ("\0" -> "\1\0").
	new
		ss = 0;
	for (new i = 0, j = strlen(spec); i != j; ++i)
	{
		if (spec[i] == 's')
		{
			if (!ss++) @emit CONST.alt ref(NULL) // Get the string pointer.
			// A string, test and convert it.
			@emit LREF.S.pri (i * 4 + 16) // Load the first character.
			@emit JNZ.rel    8            // Not '\0', skip replacement.
			@emit STOR.S.alt (i * 4 + 16) // Write the new pointer to "NULL".
		}
	}
	@emit CONST.pri  sptr
	@emit CONST.alt  AMX_Read(ptr + 4)
	@emit JUMP       YSI_g_sRemoteStub // Jump to the standard stub code.
	// Skip over the newly written code and the stored specifier.
	CGen_AddCodeSpace(6 * 4 + (ss ? (ss * 6 * 4 + 2 * 4) : 0));
	// Return a direct SCTRL pointer to the code.
	return ptr + 3 * 4 - AMX_HEADER_COD;
}

/*

    88888888888                                             88 88                          
    88                                                      88 ""                          
    88                                                      88                             
    88aaaaa     8b,dPPYba,   ,adPPYba,  ,adPPYba,   ,adPPYb,88 88 8b,dPPYba,   ,adPPYb,d8  
    88"""""     88P'   `"8a a8"     "" a8"     "8a a8"    `Y88 88 88P'   `"8a a8"    `Y88  
    88          88       88 8b         8b       d8 8b       88 88 88       88 8b       88  
    88          88       88 "8a,   ,aa "8a,   ,a8" "8a,   ,d88 88 88       88 "8a,   ,d88  
    88888888888 88       88  `"Ybbd8"'  `"YbbdP"'   `"8bbdP"Y8 88 88       88  `"YbbdP"Y8  
                                                                               aa,    ,88  
                                                                                "Y8bbdP"   

*/

/*-------------------------------------------------------------------------*//**
 * <param name="from">Array of variable types.</param>
 * <param name="at">Type slot.</param>
 * <param name="len">Return for array sizes.</param>
 * <returns>
 *  The next variable type stored in the bit array, and the length of arrays.
 * </returns>
 * <remarks>
 *  Returns data from a bit array when the parameter could be basic (variable or
 *  reference), or an array with a length (includes strings).  This requries far
 *  more complex code to decode as the lengths may span multiple cells, types
 *  can't because they are always 2 bits and always start on an even bit.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Inline_DecodeComplex(from[], &at, &len)
{
	new
		slot = at >>> 5,
		// An encoded value is either 2 or 14 bits depending on type, so there
		// is no way to ever have odd offsets.  As a result there is no way for
		// a type to span two cells, so there's no need for complex switches.
		type = (from[slot] >>> (at & 0x1F)) & 0b11;
	at += 2;
	if (type & 0x01)
	{
		// Fast, cell boundary aware, length extraction.  The length is stored
		// -1 cell, so adjust for that too.
		switch (at & 0x1F)
		{
			// Start of the (next) cell.  For these two, doing "at += 2;"
			// spilled the pointer over in to the next cell.
			case 0: len = (from[slot + 1] & 0x0FFF) + 1;
			#define Inline_DecodeOne(%0) case %0:len=((from[slot]>>>%0)&0x0FFF)+1
			// Whole length in one (current) cell.
			Inline_DecodeOne(02);
			Inline_DecodeOne(04);
			Inline_DecodeOne(06);
			Inline_DecodeOne(08);
			Inline_DecodeOne(10);
			Inline_DecodeOne(12);
			Inline_DecodeOne(14);
			Inline_DecodeOne(16);
			Inline_DecodeOne(18);
			// End of the cell.
			case 20: len = (from[slot] >>> 20) + 1;
			// Two cells (let the compiler do the maths for us).
			#define Inline_DecodeTwo(%0) case %0:len=((from[slot]>>>%0)|((from[slot+1]&(0xFFF>>>(32-%0)))<<(32-%0)))+1
			Inline_DecodeTwo(22);
			Inline_DecodeTwo(24);
			Inline_DecodeTwo(26);
			Inline_DecodeTwo(28);
			Inline_DecodeTwo(30);
			P:C(default: P:E("Odd offset in y_inline."););
		}
		at += 12;
	}
	return type;
}

static stock Inline_EncodeFormatString(const str[], ret[2])
{
	new
		size = 0,
		complex = 0,
		b0,
		b1;
	for (new i = 0; ; ++i)
	{
		switch (str[i])
		{
			case '\0': break;
			case 'v':
			{
				// Add variable without length.
				b1 = (b1 << 2) | (b0 >>> 30),
				b0 = (b0 << 2) | INLINE_TYPE_REF,
				++size;
			}
			case 's', 'a':
			{
				if (str[i + 1] == '[')
				{
					new
						j = i + 2,
						len = 0;
					while ('0' <= str[j] <= '9') len = (len * 10) + (str[j++] - '0');
					--len,
					b1 = (b1 << 14) | (b0 >>> 18);
					// Add array with length.
					if (str[i] == 'a') b0 = (b0 << 14) | ((len & 0xFFF) << 2) | INLINE_TYPE_ARR;
					else b0 = (b0 << 14) | ((len & 0xFFF) << 2) | INLINE_TYPE_STR;
					if (str[j] != ']') --j;
					i = j,
					size += 7,
					complex = 1;
				}
				else
				{
					// Add variable without length.
					b1 = (b1 << 2) | (b0 >>> 30),
					b0 = (b0 << 2) | INLINE_TYPE_REF,
					++size;
				}
			}
			default:
			{
				// Add variable without length.
				b1 = (b1 << 2) | (b0 >>> 30),
				b0 = (b0 << 2) | INLINE_TYPE_VAR,
				++size;
			}
		}
	}
	// Add total size.
	ret[1] = (b1 << 6) | (b0 >>> 26),
	ret[0] = (b0 << 6) | ((size & 0b00011111) << 1) | (complex ^ 1);
}

/*

    88                                                                88  
    88              ,d                                                88  
    88              88                                                88  
    88 8b,dPPYba, MM88MMM ,adPPYba, 8b,dPPYba, 8b,dPPYba,  ,adPPYYba, 88  
    88 88P'   `"8a  88   a8P_____88 88P'   "Y8 88P'   `"8a ""     `Y8 88  
    88 88       88  88   8PP""""""" 88         88       88 ,adPPPPP88 88  
    88 88       88  88,  "8b,   ,aa 88         88       88 88,    ,88 88  
    88 88       88  "Y888 `"Ybbd8"' 88         88       88 `"8bbdP"Y8 88  

*/

/*-------------------------------------------------------------------------*//**
 * <summary>operator+</summary>
 * <param name="a">Dummy variable.</param>
 * <param name="b">Return value.</param>
 * <remarks>
 *  This is a prefix function that takes some value and returns it to the
 *  caller's caller.  This makes "@return" in inline functions work.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock InlineRet:operator+(InlineRet:a, _:b)
{
	#pragma unused a
	// Modify the return address.
	#emit LOAD.S.pri 0
	#emit ADD.C      4
	#emit LOAD.I
	#emit STOR.S.pri 4
	// Get the last function's parameters.
	#emit LOAD.S.pri 0
	#emit ADD.C      8
	#emit LOAD.I
	#emit LOAD.S.alt 0
	#emit ADD
	#emit ADDR.alt   0
	#emit SUB
	#emit STOR.S.pri 8
	// Load the return value.
	#emit LOAD.S.pri b
	// Copy the previous frame.
	#emit LREF.S.alt 0
	#emit STOR.S.alt 0
	// Do the return
	#emit RETN
	return InlineRet:0;
}

stock InlineRet:operator+(InlineRet:a, Float:b)
{
	#pragma unused a
	// Modify the return address.
	#emit LOAD.S.pri 0
	#emit ADD.C      4
	#emit LOAD.I
	#emit STOR.S.pri 4
	// Get the last function's parameters.
	#emit LOAD.S.pri 0
	#emit ADD.C      8
	#emit LOAD.I
	#emit LOAD.S.alt 0
	#emit ADD
	#emit ADDR.alt   0
	#emit SUB
	#emit STOR.S.pri 8
	// Load the return value.
	#emit LOAD.S.pri b
	// Copy the previous frame.
	#emit LREF.S.alt 0
	#emit STOR.S.alt 0
	// Do the return
	#emit RETN
	return InlineRet:0;
}

stock InlineRet:operator+(InlineRet:a, bool:b)
{
	#pragma unused a
	// Modify the return address.
	#emit LOAD.S.pri 0
	#emit ADD.C      4
	#emit LOAD.I
	#emit STOR.S.pri 4
	// Get the last function's parameters.
	#emit LOAD.S.pri 0
	#emit ADD.C      8
	#emit LOAD.I
	#emit LOAD.S.alt 0
	#emit ADD
	#emit ADDR.alt   0
	#emit SUB
	#emit STOR.S.pri 8
	// Load the return value.
	#emit LOAD.S.pri b
	// Copy the previous frame.
	#emit LREF.S.alt 0
	#emit STOR.S.alt 0
	// Do the return
	#emit RETN
	return InlineRet:0;
}

