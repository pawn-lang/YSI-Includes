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

// How to convert from old y_inline to new y_inline:
// 
// 1) Delete all `[E_CALLBACK_DATA]` everywhere.  This can optionally be
//   replaced by a specifier tag.  So what used to be:
// 
//     new cb[E_CALLBACK_DATA];
// 
//   Becomes:
// 
//     new Func:cb<iiis>;
// 
// 2) Replace `Callback_Get` and `Callback_Release` with `Indirect_Claim` and
//    `Indirect_Release`.  But only if you plan to store the callback for use in
//    the future.  If you plan to use it immediately, just delete them.
// 
// 3) Use `Callback_Find` if you want to search for a callback by name.  This
//    means the old behviour of `Callback_Call` is now split between two
//    functions, both of which are optional depending on what you want to do.
// 
// 4) Replace `callback:` tags with specifier tags.  So:
// 
//     MyFunc(callback:x)
// 
//   Becomes:
// 
//     MyFunc(Func:cb<iiis>)
// 
// 5) Replace:
// 
//     Callback_Call(cb, your, params);
// 
//    With:
// 
//     @.cb(your, params);
// 
// 6) If you used plain strings as:
// 
//     MyFunc(callback_tag:"func");
// 
//    This has been entirely removed and must be:
// 
//     MyFunc(using func);
// 
//    Note the lack of `inline` or `callback`.  This was the syntax for plain
//    string searches, but plain strings were also possible.  Now they are not.
// 
// 7) If you used an inline that was not in scope as:
// 
//     {
//         inline Func() {}
//     }
//     {
//         Other(using Func);
//     }
// 
//    You now can't do that - it won't work.  The old code was not fully aware
//    of scopes and would attempt to find the nearest potential function.  The
//    new code is fully scope aware and will correct deal with it.
// 
// Note that this is all optional.  Not doing so will continue to work, but
// give warnings.

#if YSI_KEYWORD(inline)
	#define inline INLINE__
#endif
#if YSI_KEYWORD(inline_return)
	#define inline_return INLINE_RETURN__
#endif
#if YSI_KEYWORD(@return)
	#define @return INLINE_RETURN__
#endif

#define INLINE_RETURN__%0; {Callback_Return_(_:(%0));continue;}
#define callback: F@_@:

#define _F<%0> (#%0)

stock
	InlineRet:YSI_gInlineRet = InlineRet:0;

stock Callback_Return_(value)
{
	return value;
}

__COMPILER_STATIC_ENUM e_INLINE_FLAG (<<= 1)
{
	e_INLINE_FLAG_NONE = 0,
	// Public function, don't do any stack restoration.
	e_INLINE_FLAG_PUBLIC = 1,
	// Cleared after a non-const function has been called.  If the function is
	// never called, there's no point restoring.  If the function is deferred,
	// there's no point restoring.  If the function is `const`, there's no point
	// restoring.
	e_INLINE_FLAG_CONST
	// If any more flags are added, Callback_CallHandler_ needs updating, since
	// it sets the flags to exactly `0`.
}

__COMPILER_STATIC_ENUM E_INLINE_CALL
{
	/*  0 */ E_INLINE_CALL_NULL,
	/*  1 */ E_INLINE_CALL_HANDLER,
	/*  2 */ E_INLINE_CALL_CLAIM,
	/*  3 */ E_INLINE_CALL_RELEASE,
	/*  4 */ E_INLINE_CALL_METADATA,
	/*  5 */ E_INLINE_CALL_TIMER, // To release unneeded inlines.
	/*  6 */ E_INLINE_CALL_FLAGS,
	/*  7 */ E_INLINE_CALL_SIZE,
	/*  8 */ E_INLINE_CALL_SOURCE,
	/*  9 */ E_INLINE_CALL_FUNCTION,
	/* 10 */ ResolvedAlloc:E_INLINE_CALL_PARAMS // At least the frame header.
}

__COMPILER_STATIC_ENUM E_PUBLIC_CALL
{
	/*  0 */ E_PUBLIC_CALL_NULL,
	/*  1 */ E_PUBLIC_CALL_HANDLER,
	/*  2 */ E_PUBLIC_CALL_CLAIM,
	/*  3 */ E_PUBLIC_CALL_RELEASE,
	/*  4 */ E_PUBLIC_CALL_METADATA,
	/*  5 */ E_PUBLIC_CALL_TIMER, // To release unneeded remotes.
	/*  6 */ E_PUBLIC_CALL_FLAGS,
	/*  7 */ E_PUBLIC_CALL_SPECIFIER[32],
	/* 39 */ E_PUBLIC_CALL_FUNCTION[FUNCTION_LENGTH]
}

#if 0

// This:

Func()
{
	inline Inner(a, string:b[], c[64], &d)
	{
		// Code.
	}
}

// Becomes:

Func()
{
	static const Inner = 0;
	while (Inline_Start(Inner)) for (new a, string:b[], c[64], d; Inline_Def(0, cellmax, 64, -1); Inline_End())
	{
		// Code.
	}
}

// Rewrite "Inline_Start()" with entry code and a jump over the whole inline.

// Rewrite "Inline_Def" with 

// Where:

Inline_Start(const &name, a = INLINE_PATTERN_1, b = INLINE_PATTERN_2, c = INLINE_PATTERN_3, d = INLINE_PATTERN_4)
{
	// The four extra parameters are just for putting unique scannable patterns
	// in to the code so that we can locate these function calls and rewrite
	// them.
	#pragma unused a, b, c, d
	// It turns out that "const &" IS valid!  Pointless, but valid, which is
	// good because we want to bypass the compiler restrictions.
	// This allows us to write to a const reference without the compiler
	// objecting to it.  This is, of course, a TERRIBLE idea!  In fact, this is
	// only logically what happens, since this function is in reality never
	// called, only scanned for and rewritten.
	setarg(0, 0, inlineAddress);
	// NEVER loop.
	return 0;
}

#endif

// Revert to the old scanning design, but using the new code scanner.

__COMPILER_CONST_STATIC INLINE_PATTERN_1 = _C<Alex>;
__COMPILER_CONST_STATIC INLINE_PATTERN_2 = _C<_Y_L>;
__COMPILER_CONST_STATIC INLINE_PATTERN_3 = _C<ess_>;
__COMPILER_CONST_STATIC INLINE_PATTERN_4 = _C<Cole>;

forward Callback_Release_(ResolvedAlloc:a);
forward Inline_MaybeFree_(Alloc:slot);
forward Inline_MaybeConst_(ResolvedAlloc:slot);

#define CALL@I@F I@F()
#define CALL@I@L I@L()
#define CALL@I@K I@K(0)
#define CALL@I@T I@T(__ARR)

#define CALL@Inline_UI_ Inline_UI_(__REF)

#define CALL@Callback_Return_ Callback_Return_(0)

static stock
	YSI_g_sFakeE_INLINE_CALL[E_INLINE_CALL];
	
#define CALL@Callback_Claim_ Callback_Claim_(YSI_g_sFakeE_INLINE_CALL)

#define MAX_INLINE_PARAMETERS (32)

#define INLINE_DESCRIPTOR_VAR (0)
#define INLINE_DESCRIPTOR_REF (-1)
#define INLINE_DESCRIPTOR_STR (cellmax)

enum E_CALLBACK_DATA
{
	// Now only one item.
	E_CALLBACK_DATA_ALLOC
}

enum E_INLINE_DATA
{
	// The fake "parameters" for the inline function.
	E_INLINE_DATA_PARAMETERS[MAX_INLINE_PARAMETERS],
	E_INLINE_DATA_PARAMETER_COUNT,
	E_INLINE_DATA_NAME,    // The address of the string with the name in.
	E_INLINE_DATA_STATE,   // Which part of the header scanning we are on.
	E_INLINE_DATA_LOCALS,  // Closure size.
	E_INLINE_DATA_STACK,   // Count of all locals.
	E_INLINE_DATA_POINTER, // The struct to store the inline data in.
	E_INLINE_DATA_START,   // The start of the writable code space.
	E_INLINE_DATA_USER,    // The location of the user code.
	E_INLINE_DATA_CLEANUP  // The final address at which all inline local cleanup is done.
}

static stock
	YSI_g_sInlineEndPoint = 0,
	YSI_g_sJumpOffset = 0,
	YSI_g_sCallbackCallAddress = 0,
	// This is the start of the linked list of inline functions.  Each time a
	// function goes in to scope, the address of the local pointing to the
	// function header data is pushed to this stack.  Each time a function goes
	// out of scope a destructor is used to remove that inline from the list
	// again.  TODO:  If there is a crash, clear this list.
	YSI_g_sInlineLinkedList = 0;

stock I@T:I@T(const str[])
{
	#pragma unused str
	return I@T:0;
}

stock operator~(I@T:inlines[], size)
{
	{}
	// This destructor is actually only ever called once, even though it might
	// exist many times in the compiled code; the rest are replaced at init time
	// using information gathered here.
	#pragma unused inlines
	// Get the return address.
	#emit LOAD.S.alt       4
	// Read the code before the return.
	#emit LCTRL            0
	#emit ADD
	#emit MOVE.alt
	#emit LCTRL            1
	#emit SUB.alt
	#emit ADD.C            0xFFFFFFFC
	#emit STOR.S.pri       size
	#emit LREF.S.pri       size
	#emit STOR.S.pri       size
	{}
	// This code:
	//   
	//   YSI_g_sInlineLinkedList = DisasmReloc(size);
	//   
	// For some reason crashes with:
	//   
	//   https://github.com/pawn-lang/compiler/issues/318
	//   
	// Interestingly, it turns out the variable `YSI_g_sJumpOffset` already
	// existed locally with exactly the same value as the one used in
	// `DisasmReloc`, so the fix ends up actually being faster than the
	// original code (but less explicit).  For reference - it gets the previous
	// in-scope inline from the linked list, as a data segment address.
	YSI_g_sInlineLinkedList = size - YSI_g_sJumpOffset;
}

public Inline_MaybeFree_(Alloc:slot)
{
	// If this function is called, the given inline left the call stack without
	// being claimed.
	free(slot);
}

public Inline_MaybeConst_(ResolvedAlloc:slot)
{
	// If this function is called, the given inline has been claimed, but has
	// left the current scope, so can't have its closure written back to.
	KillTimer(AMX_Read(_:slot + _:E_INLINE_CALL_TIMER * cellbytes));
	AMX_Write(_:slot + _:E_INLINE_CALL_TIMER * cellbytes, 0);
}

static stock Inline_FoundStart(const scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	P:4("Inline_FoundStart called");
	if (data[E_INLINE_DATA_STATE] != 0)
		return 0;
	P:5("Inline_FoundStart OK");
	data[E_INLINE_DATA_LOCALS] = CodeScanGetMatchStack(scanner);
	data[E_INLINE_DATA_START] = CodeScanGetMatchAddress(scanner);
	data[E_INLINE_DATA_NAME] = CodeScanGetMatchHole(scanner, 0);
	data[E_INLINE_DATA_STATE] = 1;
	data[E_INLINE_DATA_PARAMETER_COUNT] = 0;
	return 0;
}

static stock Inline_FoundMid(const scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	P:4("Inline_FoundMid called");
	if (data[E_INLINE_DATA_STATE] != 1)
		return 0;
	P:5("Inline_FoundMid OK");
	data[E_INLINE_DATA_STACK] = CodeScanGetMatchStack(scanner);
	data[E_INLINE_DATA_STATE] = 2;
	data[E_INLINE_DATA_CLEANUP] = CodeScanGetMatchHole(scanner, 0);
	return 0;
}

static stock Inline_FoundDescriptor(size, data[E_INLINE_DATA])
{
	if (data[E_INLINE_DATA_PARAMETER_COUNT] == MAX_INLINE_PARAMETERS)
		P:F("y_inline: Max inline parameter count exceeded (%d).", MAX_INLINE_PARAMETERS);
	else switch (size)
	{
		case INLINE_DESCRIPTOR_VAR:
		{
			data[E_INLINE_DATA_PARAMETERS][data[E_INLINE_DATA_PARAMETER_COUNT]++] = INLINE_DESCRIPTOR_VAR;
		}
		case INLINE_DESCRIPTOR_REF:
		{
			data[E_INLINE_DATA_PARAMETERS][data[E_INLINE_DATA_PARAMETER_COUNT]++] = INLINE_DESCRIPTOR_REF;
			data[E_INLINE_DATA_STATE] |= 16;
		}
		case INLINE_DESCRIPTOR_STR:
		{
			data[E_INLINE_DATA_PARAMETERS][data[E_INLINE_DATA_PARAMETER_COUNT]++] = INLINE_DESCRIPTOR_STR;
			data[E_INLINE_DATA_STATE] |= 8;
		}
		default:
		{
			data[E_INLINE_DATA_PARAMETERS][data[E_INLINE_DATA_PARAMETER_COUNT]++] = size << __COMPILER_CELL_SHIFT;
			data[E_INLINE_DATA_STATE] |= 8;
		}
	}
}

static stock Inline_FoundConst(const scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	P:4("Inline_FoundConst called");
	if (data[E_INLINE_DATA_STATE] != 2)
		return 0;
	P:5("Inline_FoundConst OK");
	data[E_INLINE_DATA_STATE] = 3 + CodeScanGetMatchHole(scanner, 0);
	return 0;
}

static stock Inline_FoundConst2(const scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	P:4("Inline_FoundConst2 called");
	#pragma unused scanner
	// Can't use size to determine this match as two pieces of code are the same
	// size in the same place, but mean very different things.
	if (data[E_INLINE_DATA_STATE] != 2)
		return 0;
	P:5("Inline_FoundConst2 OK");
	data[E_INLINE_DATA_STATE] = 3;
	return 0;
}

static stock Inline_FoundVar(const scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	P:4("Inline_FoundVar called");
	#pragma unused scanner
	if (data[E_INLINE_DATA_STATE] < 3)
		return 0;
	P:5("Inline_FoundVar OK");
	Inline_FoundDescriptor(0, data);
	return 0;
}

static stock Inline_FoundRef(const scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	P:4("Inline_FoundRef called");
	if (data[E_INLINE_DATA_STATE] < 3)
		return 0;
	P:5("Inline_FoundRef OK");
	Inline_FoundDescriptor(CodeScanGetMatchHole(scanner, 0), data);
	return 0;
}

static stock Inline_FoundEnd(const scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	P:4("Inline_FoundEnd called");
	if (data[E_INLINE_DATA_STATE] < 3)
		return 0;
	P:5("Inline_FoundEnd OK");
	data[E_INLINE_DATA_USER] = CodeScanGetMatchAddress(scanner) + CodeScanGetMatchLength(scanner);
	// Do the actual codegen here.
	Inline_DoCodeGen(scanner, data);
	Inline_StoreData(data);
	// Restart scanning for the next inline.
	data[E_INLINE_DATA_STATE] = 0;
	return 0;
}

static stock Inline_StoreData(const data[E_INLINE_DATA])
{
	// `data[E_INLINE_DATA_NAME]` stores the address of a string with the inline
	// function's name, followed by extra space for storing: a pointer to the
	// name, a pointer to the function, a pointer to the next inline in the
	// linked list of names, and something else?
	new
		header = data[E_INLINE_DATA_NAME];
	// Add a pointer to the function itself (after `JUMP`).
	AMX_Write(header, data[E_INLINE_DATA_START] + 10 * cellbytes);
	// Store the local stack size at this point.
	AMX_Write(header + cellbytes, data[E_INLINE_DATA_LOCALS]);
	// Store the tag data.  TODO: Put this in the compiler with
	// `InlineName = tagof (InlineName);`.
	new
		tag[FUNCTION_LENGTH] = "F@_@";
	for (new cur = 0; cur != data[E_INLINE_DATA_PARAMETER_COUNT]; ++cur)
	{
		switch (data[E_INLINE_DATA_PARAMETERS][cur])
		{
		case INLINE_DESCRIPTOR_VAR:
			tag[cur + 4] = 'i';
		case INLINE_DESCRIPTOR_REF:
			tag[cur + 4] = 'v';
		case INLINE_DESCRIPTOR_STR:
			tag[cur + 4] = 's';
		default:
			tag[cur + 4] = 'a';
		}
	}
	AMX_Write(header + 2 * cellbytes, GetTagIDFromName(tag));
}

static stock Inline_FoundUsingInline(const scanner[CodeScanner])
{
	// Found a call to `using inline`.  Change it from (the equivalent of)
	// `(a = Inline_UI_(a), a)` to `Inline_UI_(a)`.  First, check that the two
	// holes are the same.  If they're not, this isn't what we want to optimise.
	if (CodeScanGetMatchHole(scanner, 0) != CodeScanGetMatchHole(scanner, 1))
		return 0;
	new
		ctx[AsmContext];
	switch (CodeScanGetMatchLength(scanner))
	{
		case 8 * cellbytes:
		{
			CodeScanGetMatchAsm(scanner, ctx, 6 * cellbytes);
			@emit PUSH.pri
			@emit NOP
		}
		case 10 * cellbytes:
		{
			CodeScanGetMatchAsm(scanner, ctx, 7 * cellbytes);
			@emit NOP
			@emit NOP
		}
	}
	return 0;
}

static stock Inline_FoundDestructor(const scanner[CodeScanner])
{
	// Found a call to `operator~(I@T:inlines[], size)`.  Get the offset of the
	// variable we store the linked list in.  Note that the linked list doesn't
	// point to this variable, but the next variable on the stack, the variable
	// containing the function header data.  So when we use the list, we need to
	// take that in to account; but not here.
	new
		func = CodeScanGetMatchHole(scanner, 0),
		ctx[AsmContext];
	CodeScanGetMatchAsm(scanner, ctx);
	if (YSI_g_sInlineEndPoint > CodeScanGetMatchAddress(scanner))
	{
		// Do not call inline function destructors in inlines.
		@emit NOP
		@emit NOP
		@emit NOP
		@emit NOP
	}
	else
	{
		// Remove this inline function from the linked list of inlines.
		@emit LOAD.S.pri       func
		@emit STOR.pri         AMX_Ref(YSI_g_sInlineLinkedList)
	}
	@emit NOP
	@emit NOP
	@emit NOP
	@emit NOP
	@emit NOP
	return 0;
}

static stock Inline_Found@return(const scanner[CodeScanner])
{
	new
		ctx[AsmContext];
	CodeScanGetMatchAsm(scanner, ctx);
	@emit POP.pri
	@emit STACK            CodeScanGetMatchStack(scanner)
	@emit RETN
	return 0;
}

#if !defined _ALS_OnRuntimeError
	forward OnRuntimeError(code, &bool:suppress);
#endif

public OnRuntimeError(code, &bool:suppress)
{
	// No inlines are in scope, because the scope just crashed.  Clear the list.
	YSI_g_sInlineLinkedList = 0;
	Inline_OnRuntimeError(code, suppress);
	return 1;
}

CHAIN_FORWARD:Inline_OnRuntimeError(code, &bool:suppress) = 1;
#if defined _ALS_OnRuntimeError
	#undef OnRuntimeError
#else
	#define _ALS_OnRuntimeError
#endif
#define OnRuntimeError(%0) CHAIN_PUBLIC:Inline_OnRuntimeError(%0)

#define CALL@Callback_CallHandler_ Callback_CallHandler_()

public OnCodeInit()
{
	P:2("Inline_OnCodeInit called");
	YSI_g_sJumpOffset = GetAmxBaseAddress() + AMX_HEADER_COD - AMX_BASE_ADDRESS;
	YSI_g_sCallbackCallAddress = addressof(Callback_CallHandler_) + YSI_g_sJumpOffset;
	if (FALSE)
	{
		// Ensure this function is included.  It causes HUGE issues when not.
		new tmp[2];
		strunpack(tmp, tmp);
	}
	
	new scanner[CodeScanner];
	CodeScanInit(scanner);
	
	// Allocate the inline scanning data on the stack, instead of globally.
	new data[E_INLINE_DATA];
	
	// Optimised.
	new csm1a[CodeScanMatcher];
	CodeScanMatcherInit(csm1a, &Inline_FoundStart);
	CodeScanMatcherData(csm1a, AMX_Ref(data[E_INLINE_DATA:0]));
	CodeScanMatcherPattern(csm1a,
		OP(STACK,              -4)
		OP(CONST_PRI,          ???)
		OP(INVERT)
		OP(INVERT)
		OP(PUSH_PRI)
		OP(PUSH_C,             4)
		OP(CALL,               &I@T)
		OP(STOR_S_PRI,         ???)
		OP(STACK,              -4)
		OP(LOAD_S_PRI,         ???)
		OP(STOR_S_PRI,         ???)
	);
	CodeScanAddMatcher(scanner, csm1a);
	
	// Unoptimised.
	new csm1b[CodeScanMatcher];
	CodeScanMatcherInit(csm1b, &Inline_FoundStart);
	CodeScanMatcherData(csm1b, AMX_Ref(data[E_INLINE_DATA:0]));
	CodeScanMatcherPattern(csm1b,
		OP(STACK,              -4)
		OP(CONST_PRI,          ???)
		OP(INVERT)
		OP(INVERT)
		OP(PUSH_PRI)
		OP(PUSH_C,             4)
		OP(CALL,               &I@T)
		OP(STOR_S_PRI,         ???)
		OP(STACK,              -4)
		OP(LOAD_S_PRI,         ???)
		OP(STOR_S_PRI,         ???)
	);
	CodeScanAddMatcher(scanner, csm1b);
	
	// Mid point.
	new csm2a[CodeScanMatcher];
	CodeScanMatcherInit(csm2a, &Inline_FoundMid);
	CodeScanMatcherData(csm2a, AMX_Ref(data[E_INLINE_DATA:0]));
	CodeScanMatcherPattern(csm2a,
		OP(PUSH_C,             0)
		OP(CALL,               &I@F)
		OP(JZER,               ???)
	);
	CodeScanAddMatcher(scanner, csm2a);
	
	// Normal parameter.
	//   
	//   ZERO.pri
	//   HEAP 4
	//   STOR.I
	//   PUSH.alt
	//   
	new csm3a[CodeScanMatcher];
	CodeScanMatcherInit(csm3a, &Inline_FoundVar);
	CodeScanMatcherData(csm3a, AMX_Ref(data[E_INLINE_DATA:0]));
	CodeScanMatcherPattern(csm3a,
		OP(ZERO_PRI)
		OP(HEAP,               4)
		OP(STOR_I)
		OP(PUSH_ALT)
	);
	CodeScanAddMatcher(scanner, csm3a);
	
	new csm3b[CodeScanMatcher];
	CodeScanMatcherInit(csm3b, &Inline_FoundVar);
	CodeScanMatcherData(csm3b, AMX_Ref(data[E_INLINE_DATA:0]));
	CodeScanMatcherPattern(csm3b,
		OP(ZERO_PRI)
		OP(HEAP,               4)
		OP(STOR_I)
		OP(MOVE_PRI)
		OP(PUSH_PRI)
	);
	CodeScanAddMatcher(scanner, csm3b);
	
	// Reference parameter.
	//   
	//   CONST.pri ffffffff
	//   HEAP 4
	//   STOR.I
	//   PUSH.alt
	//   
	// Array (with size in CELLS).
	//   
	//   CONST.pri a
	//   HEAP 4
	//   STOR.I
	//   PUSH.alt
	//   
	// String
	//   
	//   CONST.pri 80000000
	//   HEAP 4
	//   STOR.I
	//   PUSH.alt
	//   
	new csm4a[CodeScanMatcher];
	CodeScanMatcherInit(csm4a, &Inline_FoundRef);
	CodeScanMatcherData(csm4a, AMX_Ref(data[E_INLINE_DATA:0]));
	CodeScanMatcherPattern(csm4a,
		OP(CONST_PRI,          ???)
		OP(HEAP,               4)
		OP(STOR_I)
		OP(PUSH_ALT)
	);
	CodeScanAddMatcher(scanner, csm4a);
	
	new csm4b[CodeScanMatcher];
	CodeScanMatcherInit(csm4b, &Inline_FoundRef);
	CodeScanMatcherData(csm4b, AMX_Ref(data[E_INLINE_DATA:0]));
	CodeScanMatcherPattern(csm4b,
		OP(CONST_PRI,          ???)
		OP(HEAP,               4)
		OP(STOR_I)
		OP(MOVE_PRI)
		OP(PUSH_PRI)
	);
	CodeScanAddMatcher(scanner, csm4b);
	
	// End
	new csm5a[CodeScanMatcher];
	CodeScanMatcherInit(csm5a, &Inline_FoundEnd);
	CodeScanMatcherData(csm5a, AMX_Ref(data[E_INLINE_DATA:0]));
	CodeScanMatcherPattern(csm5a,
		OP(CALL,               &I@L)
		OP(HEAP,               ???)
		OP(JZER,               ???)
	);
	CodeScanAddMatcher(scanner, csm5a);
	
	// Constness
	new csm6a[CodeScanMatcher];
	CodeScanMatcherInit(csm6a, &Inline_FoundConst);
	CodeScanMatcherData(csm6a, AMX_Ref(data[E_INLINE_DATA:0]));
	CodeScanMatcherPattern(csm6a,
		OP(PUSH_C,             ???)
		OP(PUSH_C,             4)
		OP(CALL,               &I@K)
	);
	CodeScanAddMatcher(scanner, csm6a);
	
	new csm6b[CodeScanMatcher];
	CodeScanMatcherInit(csm6b, &Inline_FoundConst);
	CodeScanMatcherData(csm6b, AMX_Ref(data[E_INLINE_DATA:0]));
	CodeScanMatcherPattern(csm6b,
		OP(CONST_PRI,          ???)
		OP(PUSH_PRI)
		OP(PUSH_C,             4)
		OP(CALL,               &I@K)
	);
	CodeScanAddMatcher(scanner, csm6b);
	
	new csm6c[CodeScanMatcher];
	CodeScanMatcherInit(csm6c, &Inline_FoundConst2);
	CodeScanMatcherData(csm6c, AMX_Ref(data[E_INLINE_DATA:0]));
	CodeScanMatcherPattern(csm6c,
		OP(ZERO_PRI)
		OP(PUSH_PRI)
		OP(PUSH_C,             4)
		OP(CALL,               &I@K)
	);
	CodeScanAddMatcher(scanner, csm6c);
	
	// Replace code that was `(Inline_UI_(x), x)` with just `Inline_UI_()`.
	new csm7a[CodeScanMatcher];
	CodeScanMatcherInit(csm7a, &Inline_FoundUsingInline);
	CodeScanMatcherPattern(csm7a,
		OP(ADDR_PRI,           ???)
		OP(PUSH_PRI)
		OP(PUSH_C,             4)
		OP(CALL,               &Inline_UI_)
		OP(LOAD_S_PRI,         ???)
		OP(PUSH_PRI)
	);
	CodeScanAddMatcher(scanner, csm7a);
	
	new csm7b[CodeScanMatcher];
	CodeScanMatcherInit(csm7b, &Inline_FoundUsingInline);
	CodeScanMatcherPattern(csm7b,
		OP(PUSH_ADR,           ???)
		OP(PUSH_C,             4)
		OP(CALL,               &Inline_UI_)
		OP(PUSH_S,             ???)
	);
	CodeScanAddMatcher(scanner, csm7b);
	
	// Destructors.
	{
		// We can't directly get the address of a destructor.  Instead, we need
		// to create a local that will be destroyed and read the call from that.
		// Use `[2]` so it doesn't match the scanner later.
		new I@T:search[2] = {};
		// THIS BLOCK IS NOT POINTLESS!  IT CALLS A REQUIRED DESTRUCTOR.
	}
	// Now we have the destructor address, replace all calls to it.  I've never
	// seen this using `PUSH.adr` instead of `ADDR.pri`/`PUSH.pri`, even on
	// optimising builds.  `YSI_g_sInlineLinkedList` currently holds the address
	// of the `I@T:` destructor.  We used that as a temporary to return the
	// function address from the (seemingly) pointless block directly above
	// because `addressof` and `&` don't work for operators (I don't know a
	// generic solution to this problem, but it has only ever come up once and I
	// could get a non-portable solution in that one instance).
	new csm8a[CodeScanMatcher];
	CodeScanMatcherInit(csm8a, &Inline_FoundDestructor);
	CodeScanMatcherPattern(csm8a,
		OP(PUSH_C,             1)
		OP(ADDR_PRI,           ???)
		OP(PUSH_PRI)
		OP(PUSH_C,             8)
		OP(CALL,               YSI_g_sInlineLinkedList)
	);
	CodeScanAddMatcher(scanner, csm8a);
	
	// Detect `@return` and make it a real return.
	new csm9a[CodeScanMatcher];
	CodeScanMatcherInit(csm9a, &Inline_Found@return);
	CodeScanMatcherPattern(csm9a,
		OP(PUSH_C,             4)
		OP(CALL,               &Callback_Return_)
	);
	CodeScanAddMatcher(scanner, csm9a);
	
	// Reset the linked list whose variable we borrowed as a temporary.
	YSI_g_sInlineLinkedList = 0;
	
	// Run all the scanners in parallel.
	// TODO: Try and determine rough types for parent function parameters, using
	// Opcodes like LREF, SREF, and IDXADDR (IDXARRAY?  Can't remember off the
	// top of my head).
	CodeScanRunFast(scanner, &I@T);
	
	#if defined Inline_OnCodeInit
		Inline_OnCodeInit();
	#endif
	return 1;
}

#undef OnCodeInit
#define OnCodeInit Inline_OnCodeInit
#if defined Inline_OnCodeInit
	forward Inline_OnCodeInit();
#endif

/*

At maximum optimisation we get...

    Via parameter passing:
    
         6 cells for a reference variable.
         6 cells for an array.
         6 cells for a string.
         5 cells for a normal variable.
    
    Via initial declaration:
    
         2 cells for a reference variable.
         7 cells for an array.
         7 cells for a string.
         2 cells for a normal variable.
    
    For a total of:
    
         8 cells for a reference variable.
        13 cells for an array.
        13 cells for a string.
         7 cells for a normal variable.

Plus:

     8 cells for the call to `I@F` (the address after which is the loop repeat).
    20 cells for the call to `I@L` (the address after which is the start of
        code, and whose final part jumps to just after the code return jump,
        that we can co-opt for `RETN` and do away with the bounds check code).
     N useless cells at the end.

Note:

    I just added two variables, so their declaration also exists, but the maths
	above hasn't been updated to reflect this fact.

*/

// Make sure there's a space after the "return".
//#define return%0({%1}%2)%3; I@=%0({%1}%2)%3;return I@;

// The "INLINE" in the types here will override "PARSER@" to "PARSE@INLINE",
// because there is no colon (well not "because", but it helps).
#define INLINE__%0(%1) MAKE_PARSER(INLINE,ARR:REF:STR:NUM:QAL::INLINE)(%0(%1))()0()#
#define INLINE_CONST__%0(%1) MAKE_PARSER(INLINE,ARR:REF:STR:NUM:QAL::INLINE)(%0(%1))()1()#

// Follows the "code-parse.inc" internal structure.  Ugly but required, since we
// are parsing functions, but not at a top level.
#define PARSER@INLINE:%0(%5)%6(%7)$ new I@T:_@%6=I@T(_:%0(%5)%6(%7) I@O$

#define INLINE_STR(%9,%9,%2,%9)%8$(%0)%1(%3)%4# %8$(%0,%2[YSI_MAX_INLINE_STRING])%1(cellmax,%3)%4s#
#define INLINE_ARR(%9,%9,%2,%9)%8$(%0)%1(%3)%4# %8$(%0,%2[%9])%1(%9,%3)%4a#
#define INLINE_NUM(%9,%9,%2)%8$(%0)%1(%3)%4# %8$(%0,%2)%1(0,%3)%4i#
#define INLINE_REF(%9,%9,%2)%8$(%0)%1(%3)%4# %8$(%0,%2)%1(-1,%3)%4v#

// ".." is used to reserve memory at the start of the string for:
// 
//   +0 - Inline function start pointer.
//   +1 - Stack size.
#define INLINE_END(%9)%8$(,%0)%1(%3)%4# %8$#...#%9),F@_@%4:%9=F@_@%4:_@%9;for(new %0;I@F();)while(I@L(%3I@K(%1)))
#define INLINE_NUL(%9)%8$()%1()%4# %8$#...#%9),F@_@%4:%9=F@_@%4:_@%9;for(;I@F();)while(I@L(I@K(%1)))

#define I@O$

// Detect `const` in the function name, and strip it from the variable name.
#define INLINE_const(%9)%8$(%0)%1(%2) %8$(%0)1(%2)
#define _@const%0\32; _@

#define USING_INLINE__ (@Ik:@Il:Inline_UI_(),)
#define USING__%0\32; (@Ip:@Iq:@Iw:@Iv:@Io:@Iu:@Ia:@Ik:@Il:@Im:Callback_Find_(,I@),F@_@:I@)
#define USING_PUBLIC__ (@Ik:@Il:Inline_UP_(),)
#define USING_CALLBACK__ (@Ik:@Il:Inline_UP_(),)
#define USING_FUNCTION__ (@Ik:@Il:Inline_US_(),)
#define USING_STOCK__ (@Ik:@Il:Inline_US_(),)
#define USING_RESOLVED__ (@Ik:@Il:0,)
#define USING_ASYNC__ (@Ik:@Il:Inline_UA_(),)

// Old `using`.
#if YSI_KEYWORD(callback_tag)
	#define callback_tag: (@Ik:@Il:@Im:Callback_Find_(,I@),F@_@:I@)
#endif
#if YSI_KEYWORD(using)
	#define using USING__
#endif

// Parameter type for passing callbacks about.
#define @Ip:%0)inline @Ik:@Il:Inline_UI_(),)
#define @Iq:%0)callback @Ik:@Il:Inline_UP_(),)
#define @Iw:%0)function @Ik:@Il:Inline_US_(),)
#define @Iv:%0)stock @Ik:@Il:Inline_US_(),)
#define @Io:%0)public @Ik:@Il:Inline_UP_(),)
#define @Iu:%0)resolved @Ik:@Il:0,)
#define @Ia:%0)async @Ik:@Il:Inline_UA_(),)

// Detect a `using` parameter that is not the last parameter.  Actually handles
// nested calls quite nicely - `X(Y(using inline Z), 5)` should be detected as a
// final parameter, but this detects it instead and gives
// `X(Y(Inline_UI_(Z)), 5)`, which is still correct.  This only falls down on
// code like `X(Y(using inline Z) - 10, 5)`, which currently becomes
// `X(Y(Inline_UI_(Z - 10)), 5)`
#define @Ik:@Il:%0)%1, %0%1),

// Detect a `using` parameter that is the last parameter.
#define @Il:%0)%1) %0%1))

// Detect a callback with a tag.
#define @Ir:%9#%1<%0>),F@_@:%2$) @It:%9#%1,#%0),F@_@%0:%2$)

// Normally `F@_@` doesn't consume spaces because it is a valid tag on its own.
// However, in this case we know that extra specifiers after the tag prefix
// exist so we can check fairly safely.
#define @It:%0),F@_@%9\32;%1:%2$) @It:%0),F@_@%9%1:%2$)

// Detect a callback that starts with "On".  These are often redefined and we
// want to keep the original.
#define @Is:%9#On%0),%2$) %9#On#%0),%2$)

// Callbacks with additional parameters (MUST have matching parameters (y_ini)).
#define @In:%0(%1)%3),%2$) %0%3),%2$),.bExtra=true,.extra=%1)

// Move the callback parameter inside the brackets.
#define Inline_US_(),%0) I@,addressof(%0))
#define Inline_UI_(),%0) Inline_UI_(_:%0),%0)
#define Inline_UP_(),%0) Inline_UP_(_:@Ir:@Is:@In:#%0),F@_@:I@ I@O$)
#define @Im:Callback_Find_(,I@),F@_@:I@%0) Callback_Find_(#%0,I@),F@_@:I@)

stock I@F()
{
	return 0;
}

stock I@L(...)
{
	return 0;
}

stock I@K(n)
{
	#pragma unused n
	return 0;
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

#define Function: F@_@:
stock Function:GetRemoteFunction(const func[], const spec[])
{
	new
		Alloc:closure = malloc(_:E_PUBLIC_CALL);
	if (!closure)
		return Function:0;
	mset(closure, _:E_PUBLIC_CALL_NULL, 0);
	mset(closure, _:E_PUBLIC_CALL_HANDLER, _:addressof (Callback_RemoteHandler_<x>));
	mset(closure, _:E_PUBLIC_CALL_CLAIM, _:addressof (Callback_Claim_));
	mset(closure, _:E_PUBLIC_CALL_RELEASE, _:addressof (Callback_Release_<tResolvedAlloc:>));    
	mset(closure, _:E_PUBLIC_CALL_TIMER, YSI_SetTimerEx("Inline_MaybeFree_", 0, false, "i", _:closure));
	mset(closure, _:E_PUBLIC_CALL_FLAGS, e_INLINE_FLAG_PUBLIC);
	mset(closure, _:E_PUBLIC_CALL_METADATA, 0);
	msets(closure, _:E_PUBLIC_CALL_SPECIFIER, spec);
	msets(closure, _:E_PUBLIC_CALL_FUNCTION, func);
	return Function:Indirect_Ptr(Malloc_Resolve(closure));
}
#define GetRemoteFunction(&%0<%1>) (F@_@%1:GetRemoteFunction(#%0, #%1))

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
	P:4("GetLocalFunction called: %s, %s", func, spec);
	if (funcidx(func) == -1)
		return Function:0;
	P:6("GetLocalFunction: 0");
	new
		Alloc:closure = malloc(_:E_PUBLIC_CALL);
	if (!closure)
		return Function:0;
	P:6("GetLocalFunction: 1");
	mset(closure, _:E_PUBLIC_CALL_NULL, 0);
	mset(closure, _:E_PUBLIC_CALL_HANDLER, _:addressof (Callback_LocalHandler_<x>));
	mset(closure, _:E_PUBLIC_CALL_CLAIM, _:addressof (Callback_Claim_));
	mset(closure, _:E_PUBLIC_CALL_RELEASE, _:addressof (Callback_Release_<tResolvedAlloc:>));    
	mset(closure, _:E_PUBLIC_CALL_TIMER, YSI_SetTimerEx("Inline_MaybeFree_", 0, false, "i", _:closure));
	mset(closure, _:E_PUBLIC_CALL_FLAGS, e_INLINE_FLAG_PUBLIC);
	mset(closure, _:E_PUBLIC_CALL_METADATA, 0);
	msets(closure, _:E_PUBLIC_CALL_SPECIFIER, spec);
	msets(closure, _:E_PUBLIC_CALL_FUNCTION, func);
	new tmp[32];
	mgets(tmp, 32, closure, _:E_PUBLIC_CALL_SPECIFIER);
	return Function:Indirect_Ptr(Malloc_Resolve(closure));
}
#define GetLocalFunction(&%0<%1>) (F@_@%1:GetLocalFunction(#%0, #%1))

/*-------------------------------------------------------------------------*//**
 * <param name="func">Function pointer to call.</param>
 * <param name="">The function's parameters.</param>
 * <remarks>
 *  Call the function in the given pointer with the given parameters.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#pragma deprecated Use `@.func(params);`.
stock CallStoredFunction(Function:func, GLOBAL_TAG_TYPES:...)
{
	return Indirect_Call(_:func, 0, ___(1));
}

/*-------------------------------------------------------------------------*//**
 * <param name="string1">First string as a pointer.</param>
 * <param name="string2">Second string as a string.</param>
 * <param name="ignorecase">Do a case-insensitive search.</param>
 * <param name="length">Length of string to compare over.</param>
 * <remarks>
 *  Just <c>strcmp</c>, but pretending the first parameter is a value not an
 *  array so that we can trick the compiler in to accepting a pointer.
 * </remarks>
 *//*------------------------------------------------------------------------**/

native Inline_Strcmp(const string1, const string2[], bool:ignorecase=false, length=cellmax) = strcmp;

/*-------------------------------------------------------------------------*//**
 * <param name="frm">Frame to get the parameters from.</param>
 * <remarks>
 *  Deals with y_hooks parameter count mangling.  Stolen from <c>Hooks_NumArgs</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Inline_NumArgs(frm)
{
	#emit LOAD.S.alt          frm
Inline_NumArgs_load:
	#emit CONST.pri           8
	#emit ADD
	#emit LOAD.I
	#emit ZERO.alt
	#emit PUSH.pri
	#emit SGEQ
	#emit LREF.S.alt          frm
	#emit JZER                Inline_NumArgs_load
	#emit POP.pri
	#emit RETN
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Inline to find by name.</param>
 * <remarks>
 *  Traverses up the stack to find an in-scope inline with the same name AND
 *  SIGNATURE.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Callback_InlineByName(const name[], tag)
{
	new
		ptr = YSI_g_sInlineLinkedList;
	while (ptr)
	{
		// Get the pointer to the inline function data.
		new
			ret = AMX_Read(ptr);
		// Compare the tags.
		if (tag == 0 || tag == AMX_Read(ret + 2 * cellbytes))
		{
			// Compare the names.
			if (!Inline_Strcmp(ret + 3 * cellbytes, name))
			{
				new
					frm = ptr + AMX_Read(ret + cellbytes),
					args = Inline_NumArgs(frm),
					size = frm - ptr + 12 + args,
					Alloc:closure = malloc((size >>> __COMPILER_CELL_SHIFT) + (_:E_INLINE_CALL - 1));
				if (!closure)
					return 0;
				mset(closure, _:E_INLINE_CALL_NULL, 0);
				mset(closure, _:E_INLINE_CALL_HANDLER, _:addressof (Callback_CallHandler_<x>));
				mset(closure, _:E_INLINE_CALL_CLAIM, _:addressof (Callback_Claim_));
				mset(closure, _:E_INLINE_CALL_RELEASE, _:addressof (Callback_Release_<tResolvedAlloc:>));    
				mset(closure, _:E_INLINE_CALL_TIMER, YSI_SetTimerEx("Inline_MaybeFree_", 0, false, "i", _:closure));
				mset(closure, _:E_INLINE_CALL_FLAGS, e_INLINE_FLAG_CONST);
				mset(closure, _:E_INLINE_CALL_METADATA, 0);
				mset(closure, _:E_INLINE_CALL_SIZE, size);
				mset(closure, _:E_INLINE_CALL_SOURCE, ptr);
				mset(closure, _:E_INLINE_CALL_FUNCTION, AMX_Read(ret));
				new
					ResolvedAlloc:ra = Malloc_Resolve(closure);
				RawMemCpy(_:ra + _:E_INLINE_CALL_PARAMS * cellbytes, ptr, size);
				AMX_Write(_:ra + (_:E_INLINE_CALL_PARAMS + 2) * cellbytes + frm - ptr, args);
				return Indirect_Ptr(ra);
			}
		}
		// Read the next data.
		ptr = AMX_Read(ptr + cellbytes);
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Callback to find by name.</param>
 * <param name="dest">Where to store the function.</param>
 * <param name="remote">Is this function called on one or all scripts?</param>
 * <param name="tag">The tag of the return value for type reasons.</param>
 * <remarks>
 *  Replacement for <c>Callback_Get</c>.  Just returns a pointer, and no longer
 *  relies on strict control of where is called from.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Callback_Find_(const name[], &dest, bool:remote = false, tag = 0)
{
	P:4("Callback_Find_ 0");
	// Remote calls must always be publics.  Indirection handles publics
	// natively.  However, it doesn't handle it amazingly since it needs to
	// handle it very generically.
	if (remote)
	{
		P:6("Callback_Find_ 1");
		new
			tagname[FUNCTION_LENGTH];
		GetTagNameFromID(tag, tagname);
		return !!(dest = _:GetRemoteFunction(name, tagname[4]));
	}
	if (funcidx(name) == -1)
	{
		// Otherwise iterate through the in-scope inlines stack to see if any match
		// this name.
		return !!(dest = Callback_InlineByName(name, tag));
	}
	P:6("Callback_Find_ 3");
	new
		tagname[FUNCTION_LENGTH];
	GetTagNameFromID(tag, tagname);
	return !!(dest = _:GetLocalFunction(name, tagname[4]));
}

#define Callback_Find(%0,%1) Callback_Find_(%0,_:%1,.tag=tagof(%1))
#define Callback_Find_(%0,_:%1,%2,.tag=tagof(%3)) Callback_Find_(%0,_:%1,%2,tagof(%1))

// Old API.

/*-------------------------------------------------------------------------*//**
 * <param name="func">Info on the function to be called.</param>
 * <remarks>
 *  Takes an inline function handler and parameters, and either calls the
 *  public function while passing through the parameters, or just jumps to the
 *  carefully crafted inline function code.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#pragma deprecated Use `@.func(params);`.
stock Callback_Call(const func[E_CALLBACK_DATA], GLOBAL_TAG_TYPES:...)
{
	return Indirect_Call(func[E_CALLBACK_DATA_ALLOC], 0, ___(1));
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
 * </remarks>
 *//*------------------------------------------------------------------------**/

#pragma deprecated Use `Indirect_Array(_:func, tagof (func), params);`.
stock Callback_Array(const func[E_CALLBACK_DATA], const params[], num = sizeof (params))
{
	return Indirect_Array(func[E_CALLBACK_DATA_ALLOC], 0, params, num);
}

#pragma deprecated No longer required.
stock Inline_Reset(callback[E_CALLBACK_DATA])
{
	return (callback[E_CALLBACK_DATA_ALLOC] = 0);
}

native Callback_Strcat_(dest, const src[], len) = strcat;

/*-------------------------------------------------------------------------*//**
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

#pragma deprecated Remove or use `Indirect_Claim(func);`.
#if __COMPILER_BUG_317
	stock bool:Callback_Get_(__DUMMY_COMPILER_BUG_317_FIX__, {F@_@, _}:...)
	{
		#pragma unused __DUMMY_COMPILER_BUG_317_FIX__
#else
	stock bool:Callback_Get({F@_@, _}:...)
	{
#endif
		// Construct the old API arguments from the new prototype.  The new
		// prototype can take both old-style strings and new-style resolved
		// callbacks from `using inline`.
		new
			name[FUNCTION_LENGTH],
			numArgs = numargs(),
			ret = 0,
			expect[FUNCTION_LENGTH] = "F@_@",
			bool:remote = false;
		assert(2 + __COMPILER_BUG_317 <= numArgs <= 4 + __COMPILER_BUG_317);
		getstringarg(name, 0 + __COMPILER_BUG_317);
		if (numArgs >= 3 + __COMPILER_BUG_317)
		{
			getstringarg(expect[4], 2 + __COMPILER_BUG_317, sizeof (expect) - 4);
			if (numArgs == 4 + __COMPILER_BUG_317)
				remote = bool:getarg(3 + __COMPILER_BUG_317);
		}
		P:2("Callback_Get called: %d %s %s", numArgs, name, expect);
		// Check that the assumption made here is valid.  I can't imagine a
		// case, given the number of libraries in use here, where it couldn't
		// be!  We check this since any inline data pointer will point in to the
		// `DAT` segment relative to the start of `COD`.  Any bare string will
		// just be a normal string starting with an ASCII letter.  This is
		// different to in the indirection include which knows to resolve the
		// pointer before checking this, unlike here were we don't know the
		// type.
		assert(AMX_HEADER_DAT - AMX_HEADER_COD > 128);
		ret = getarg(0 + __COMPILER_BUG_317);
		if (ret == 0)
			return false;
		if (!(0 < ret < 128))
		{
			// Resolved inline.
			P:3("Callback_Get: Found resolved callback: %08x", ret);
			setarg(1 + __COMPILER_BUG_317, 0, ret);
			// Direct function pointer.
			Indirect_Claim(ret);
			ret = Indirect_DePtr_(ret);
			if (ret < 0 || AMX_Read(ret))
				return true;
			// Check the format, since we might have a new one to use here.
			numArgs = AMX_Read(ret + _:E_PUBLIC_CALL_HANDLER * cellbytes);
			if (numArgs == _:addressof (Callback_LocalHandler_<x>) || numArgs == _:addressof (Callback_RemoteHandler_<x>))
			{
				if (expect[4] && AMX_Read(ret + _:E_PUBLIC_CALL_SPECIFIER * cellbytes) == '\0')
				{
					// Given an explicit specifier here, not before.
					Callback_Strcat_(ret + _:E_PUBLIC_CALL_SPECIFIER * cellbytes, expect[4], 32);
				}
			}
			return true;
		}
		getstringarg(name, 0 + __COMPILER_BUG_317);
		// Wrap the new string-find API.
		if (Callback_Find_(name, ret, remote, GetTagIDFromName(expect)))
		{
			setarg(1 + __COMPILER_BUG_317, 0, ret);
			Indirect_Claim(ret);
			return true;
		}
		return false;
#if __COMPILER_BUG_317
	}
	#define Callback_Get(%0) Callback_Get_(0,%0)
#else
	// Make brace finders and code folders happy.
	}
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="input">Callback to release.</param>
 * <remarks>
 *  Releases all the data associated with a given callback (closure storage).
 * </remarks>
 *//*------------------------------------------------------------------------**/

#pragma deprecated Remove or use `Indirect_Release(func);`.
stock Callback_Release(const input[E_CALLBACK_DATA])
{
	Indirect_Release(input[E_CALLBACK_DATA_ALLOC]);
	return 0;
}

static stock Callback_Claim_(func[E_INLINE_CALL])
{
	KillTimer(func[E_INLINE_CALL_TIMER]);
	func[E_INLINE_CALL_TIMER] = YSI_SetTimerEx("Inline_MaybeConst_", 0, false, "i", AMX_Ref(func[E_INLINE_CALL_NULL]));
}

/*-------------------------------------------------------------------------*//**
 * <param name="">The parameters passed to this function via <see>@</see>.</param>
 * <remarks>
 *  When you call an inline function using <c>@.name</c>, the underlying
 *  <c>Indirect_Call</c> function jumps to a handler.  This is that handler.
 *  The code here copies the function closure then jumps to the start of the
 *  inline code.  Once that is completed, the inline jumps back to midway
 *  through this function to store the closure back again (if required).
 * </remarks>
 *//*------------------------------------------------------------------------**/

static Callback_CallHandler_(...)
{
	// This is called by `@`, and given the above enum in `INDIRECTION_DATA`.
	// Get the size, and update `INDIRECTION_DATA` to point to the data.
	#emit LOAD.alt         INDIRECTION_DATA    // 2
	#emit MOVE.pri                             // 3
	#emit ADD.C            40                  // 5, E_INLINE_CALL_PARAMS * cellbytes
	#emit PUSH.pri                             // 6
	#emit CONST.pri        7                   // 8, E_INLINE_CALL_SIZE
	#emit LIDX                                 // 9
	#emit PUSH.pri                             // 10
	#emit STACK            0                   // 12
	#emit SUB.alt                              // 13
	#emit SCTRL            4                   // 15
	// Grow the stack.
	// Call memcpy (put the native's parameters on the stack beyond `dest`).
	#emit PUSH.S           0xFFFFFFF8          // 17
	#emit PUSH.S           0xFFFFFFF8          // 19
	#emit PUSH.C           0                   // 21
	#emit PUSH.S           0xFFFFFFFC          // 23
	#emit PUSH.pri                             // 24
	#emit PUSH.C           20                  // 26
	#emit SYSREQ.C         memcpy              // 28
	#emit STACK            24                  // 30
	// "jump" in to the code.
	#emit LOAD.S.pri       0xFFFFFFFC          // 32
	#emit ADD.C            0xFFFFFFFC          // 34
	#emit LOAD.I                               // 35
	#emit SCTRL            6                   // 37
	
//Callback_Call_restore_stack:
	// The stack hasn't been restored yet, and we need it.
	#emit NOP                                  // 38
	#emit NOP                                  // 39
	// Padding to account for debug builds.
	// If the code decides to jump back to here, save the stack out again.
	#emit LCTRL            4                   // 41
	#emit PUSH.S           0xFFFFFFF8          // 43
	#emit PUSH.S           0xFFFFFFF8          // 45
	#emit PUSH.C           0                   // 47
	#emit PUSH.pri                             // 48
	#emit PUSH.S           0xFFFFFFFC          // 50
	#emit PUSH.C           20                  // 52
	#emit SYSREQ.C         memcpy              // 54
	
	// At this point, we've written the closure back to the structure.
	// Indicate to the original user that this is the case by clearing
	// `e_INLINE_FLAG_CONST` from the flags (actually clears all the flags,
	// since `e_INLINE_FLAG_PUBLIC` isn't set here either).
	#emit LOAD.S.pri       0xFFFFFFFC          // 56
	#emit ADD.C            0xFFFFFFF0          // 58 , E_INLINE_CALL_FLAGS - E_INLINE_CALL_PARAMS
	#emit MOVE.alt                             // 59
	#emit ZERO.pri                             // 60
	#emit STOR.I                               // 61
	
	#emit LCTRL            5                   // 63
	#emit SCTRL            4                   // 65
	#emit LOAD.pri         I@                  // 67
	#emit RETN                                 // 68
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <param name="">The parameters passed to this function via <see>@</see>.</param>
 * <remarks>
 *  When you call a remote function using <c>@.name</c>, the underlying
 *  <c>Indirect_Call</c> function jumps to a handler.  This is that handler.
 *  The code here simply wraps <c>CallRemoteFunction</c>, passing the specifier
 *  and function name stored in <c>INDIRECTION_DATA</c>, which is  assumed to be
 *  a pointer to <c>enum E_PUBLIC_CALL</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Callback_RemoteHandler_(...)
{
	#emit LOAD.S.alt       8
	#emit LCTRL            4
	#emit SUB
	#emit SCTRL            4
	
	// Call `memcpy` to make a new copy of the parameters for
	// `CallRemoteFunction`.
	#emit PUSH.alt
	#emit PUSH.alt
	#emit PUSH.C           0
	#emit PUSH.adr         12
	#emit PUSH.pri
	#emit PUSH.C           20
	#emit SYSREQ.C         memcpy
	#emit STACK 24
	
	// Push the specifier and function name.
	#emit LOAD.pri         INDIRECTION_DATA
	#emit ADD.C            28  // E_PUBLIC_CALL_SPECIFIER * cellbytes
	#emit PUSH.pri
	#emit ADD.C            128 // (E_PUBLIC_CALL_FUNCTION - E_PUBLIC_CALL_SPECIFIER) * cellbytes
	#emit PUSH.pri
	#emit LOAD.S.pri       8
	#emit ADD.C            8
	#emit PUSH.pri
	#emit SYSREQ.C         CallRemoteFunction
	
	// Store the return, then do the return.
	#emit MOVE.alt
	#emit LCTRL            5
	#emit SCTRL            4
	#emit MOVE.pri
	#emit RETN
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <param name="">The parameters passed to this function via <see>@</see>.</param>
 * <remarks>
 *  When you call a local function using <c>@.name</c>, the underlying
 *  <c>Indirect_Call</c> function jumps to a handler.  This is that handler.
 *  The code here simply wraps <c>CallLocalFunction</c>, passing the specifier
 *  and function name stored in <c>INDIRECTION_DATA</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Callback_LocalHandler_(...)
{
	#emit LOAD.S.alt       8
	#emit LCTRL            4
	#emit SUB
	#emit SCTRL            4
	
	// Call `memcpy` to make a new copy of the parameters for
	// `CallLocalFunction`.
	#emit PUSH.alt
	#emit PUSH.alt
	#emit PUSH.C           0
	#emit PUSH.adr         12
	#emit PUSH.pri
	#emit PUSH.C           20
	#emit SYSREQ.C         memcpy
	#emit STACK 24
	
	// Push the specifier and function name.
	#emit LOAD.pri         INDIRECTION_DATA
	#emit ADD.C            28  // E_PUBLIC_CALL_SPECIFIER * cellbytes
	#emit PUSH.pri
	#emit ADD.C            128 // (E_PUBLIC_CALL_FUNCTION - E_PUBLIC_CALL_SPECIFIER) * cellbytes
	#emit PUSH.pri
	#emit LOAD.S.pri       8
	#emit ADD.C            8
	#emit PUSH.pri
	#emit SYSREQ.C         CallLocalFunction
	
	// Store the return, then do the return.
	#emit MOVE.alt
	#emit LCTRL            5
	#emit SCTRL            4
	#emit MOVE.pri
	#emit RETN
	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <param name="ctx">The code generation output context.</param>
 * <param name="parameters">Information on the fake parameter types.</param>
 * <param name="count">How many parameters there are.</param>
 * <remarks>
 *  Generates the code which copies the parameters from <c>Callback_Call</c> in
 *  to the local stack.  All those parameters are passed by reference, since the
 *  function is a varargs function.  Since an inline function's "input"
 *  parameters are just regular variables on the stack, they all need resolving,
 *  which is what this code does.  Regular variables are dereferenced, and
 *  arryas and strings are fully copied over.
 *
 *  Technically this doesn't ACTUALLY do the copy, but generates the code for
 *  the copy.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Inline_GenerateLocalsCopy(ctx[AsmContext], const parameters[], count)
{
	new
		input = 12;
	for (new i = 0; i != count; ++i)
	{
		switch (parameters[i])
		{
		case -1, 0:
		{
			@emit LREF.S.pri       input
			@emit PUSH.pri
		}
		case cellmax:
		{
			@emit STACK            -(YSI_MAX_INLINE_STRING * cellbytes)
			@emit STACK            0
			@emit PUSH.C           YSI_MAX_INLINE_STRING
			@emit PUSH.S           input
			@emit PUSH.alt
			@emit PUSH.C           12
			@emit SYSREQ           "strunpack"
			@emit STACK            16
		}
		default:
		{
			@emit STACK            -(parameters[i])
			@emit STACK            0
			@emit LOAD.S.pri       input
			@emit MOVS             (parameters[i])
		}
		}
		input += cellbytes;
	}
	// Jump past the postamble, which puts a return address on the stack.
	@emit CALL.label       Inline_Start
}

/*-------------------------------------------------------------------------*//**
 * <param name="ctx">The code generation output context.</param>
 * <param name="parameters">Information on the fake parameter types.</param>
 * <param name="count">How many parameters there are.</param>
 * <remarks>
 *  When the inline function ends, any parameters that were defined as being
 *  passed by reference are copied back.  This is because true locals are never
 *  by reference, so we fake it.  There is one bug with this method - aliased
 *  variables won't work correctly:
 *
 *  <c>
 *      inline Func(&amp;a, &amp;b)
 *      {
 *  	    ++a; 
 *  	    printf("%d", b); 
 *      }
 *      
 *      new a = 10;
 *      Callback_Call(using inline Func, a, a);
 *  </c>
 *
 *  That will print <c>10</c> while the same code with a normal function will
 *  print <c>11</c> thanks to <c>a</c> and <c>b</c> being aliased.  Maybe I
 *  should add a <c>restrict</c> keyword, but even then I don't know how to
 *  solve unrestricted variables (at best I can warn for them).  And this is not
 *  a totally unheard of situation.  I have at least seen this for getting only
 *  a player's height:
 *
 *  <c>
 *      new z;
 *      GetPlayerPos(playerid, z, z, z);
 *  </c>
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Inline_GenerateLocalsStore(ctx[AsmContext], const parameters[], count)
{
	new
		accumulate = 0;
	while (count--)
	{
		switch (parameters[count])
		{
		case -1:
		{
			// Only use `alt` in here, since `Inline_GeneratePostamble` holds
			// the final stack value in `pri`.
			if (accumulate)
				@emit STACK            accumulate
			accumulate = 0;
			@emit POP.alt
			@emit SREF.S.alt       (count << __COMPILER_CELL_SHIFT) + 12
		}
		case 0:
			accumulate += cellbytes;
		case cellmax:
			accumulate += YSI_MAX_INLINE_STRING * cellbytes;
		default:
			accumulate += parameters[count];
		}
	}
	// Return how much of this data was left on the stack.  We might need to
	// clear it, we might not...
	return accumulate;
}

static stock Inline_GeneratePreamble(ctx[AsmContext], locals)
{
	// This is sort of the start of the code.
	@emit Inline_Start:
	// Set the local frame.
	@emit STACK            0
	@emit LCTRL            5
	@emit XCHG
	@emit ADD.C            locals + 4
	@emit SCTRL            5
	@emit STOR.S.alt       0
	// Get the return address.
	@emit POP.pri
	@emit STOR.S.pri       4
}

static stock Inline_GeneratePostamble(ctx[AsmContext], const parameters[], const count, bool:isConst, locals, inlineParams)
{
	new
		bool:needStore = false;
	for (new i = 0; i != count; ++i)
	{
		if (parameters[i] == -1)
		{
			needStore = true;
			break;
		}
	}
	// When we "return" from the function, we end up here, with all our stack
	// data removed.  Put it back (which is easy, because the top should still
	// be in `alt` - actually, it might not in some cases).  Turns out that's
	// irrelevant, since the only time it can happen is if there are no locals
	// to save!
	if (isConst)
	{
		if (needStore)
		{
			// Back up `pri` somewhere for returning later.
			@emit STOR.pri         AMX_Ref(I@)
			// This used to exploit the fact that the bottom of the stack was
			// still in `alt`, as in:
			//
			//   https://github.com/compuphase/pawn/issues/35
			//
			// However, that was brittle (it has already been changed in the
			// official distribution), and was inaccurate if there were extra
			// locals declared in the inline.
			@emit LOAD.S.pri       0xFFFFFFF8
			@emit STACK            0
			@emit ADD.C            locals - inlineParams
			@emit SUB.alt
			@emit SCTRL            4
			// We will remove everything from the stack later, as well as the
			// two values on the stack for `memcpy` restoration.
			@emit CONST.pri        8
			@emit ADD
			Inline_GenerateLocalsStore(ctx, parameters, count);
			// Restore the return value.
			@emit SCTRL            4
			@emit LOAD.pri         AMX_Ref(I@)
			@emit RETN
		}
		else
		{
			// If we are here, we are in the context of `Callback_Call`, with no
			// locals on the stack.
			@emit STACK            8
			@emit RETN
		}
	}
	else
	{
		@emit STOR.pri         AMX_Ref(I@)
		if (needStore)
		{
			@emit LOAD.S.alt       0xFFFFFFF8
			@emit LCTRL            4
			@emit ADD.C            inlineParams - locals
			@emit SUB
			@emit SCTRL            4
			new
				accumulate = Inline_GenerateLocalsStore(ctx, parameters, count);
			if (accumulate)
			{
				@emit STACK            accumulate
			}
		}
		else
		{
			// Go back down the stack, up to where the inline parameters began,
			// but not including them.  This will set us up the bomb (sorry,
			// couldn't resist).  This will set us up nicely for the jump in to
			// `Callback_CallHandler` for copying the stack back out again.
			@emit LOAD.S.alt       0xFFFFFFF8
			@emit LCTRL            4
			@emit SUB
			@emit SCTRL            4
		}
		// Jump to `Callback_Call_restore_stack:` to perform common cleanup.
		@emit JUMP             YSI_g_sCallbackCallAddress + 39 * cellbytes
	}
}

static stock Inline_DoRetnGen(ctx[AsmContext], const scanner[CodeScanner], const data[E_INLINE_DATA])
{
	// Remove the return for the inner loop, since it may now point to an
	// invalid address (in the middle of an OpCode we just wrote out).
	new
		startaddr = data[E_INLINE_DATA_USER],
		endaddrDAT = CodeScanGetMatchHole(scanner, 1) - 8,
		endaddrCOD = endaddrDAT + YSI_g_sJumpOffset,
		nop = _:RelocateOpcode(OP_NOP),
		dctx[DisasmContext];
	// Using the local decompiler, go through the code and remove any jumps to
	// outside of [startaddr, endaddrDAT].  Convert them all to `RETN; NOP`.
	CodeScanGetMatchDisasm(scanner, dctx, CodeScanGetMatchLength(scanner));
	dctx[DisasmContext_end_ip] = endaddrDAT + AMX_HEADER_COD + 16;
	while (DisasmNext(dctx) != DISASM_DONE)
	{
		// Is this a jump?  The only jumps that can get out of this constraint
		// are `JUMP` ones - all others like `JNEQ` etc would be generated by
		// `if` statements and so constrained by syntax.  `JUMP` would come from
		// `break`, `continue`, or `goto`.
		if (DisasmGetOpcode(dctx) == OP_JUMP && !(startaddr <= DisasmGetOperandReloc(dctx) < endaddrDAT))
		{
			AMX_Write(DisasmGetCurIp(dctx) + 4, endaddrCOD);
		}
	}
	// Save this end address for when we detect inline function destructor calls.  This way we don't
	// destruct the inline within itself.
	YSI_g_sInlineEndPoint = endaddrDAT;
	endaddrDAT += AMX_HEADER_COD;

	// Add the current inline to the linked list of in-scope inlines.  Also push
	// the inline address and current frame data.
	@emit PUSH             AMX_Ref(YSI_g_sInlineLinkedList)
	@emit PUSH.C           data[E_INLINE_DATA_NAME]
	@emit ADDR.alt         -data[E_INLINE_DATA_LOCALS]
	@emit STOR.alt         AMX_Ref(YSI_g_sInlineLinkedList)
	
	// Size of inline parameters.
	startaddr = data[E_INLINE_DATA_STACK] - data[E_INLINE_DATA_LOCALS];
	if (startaddr)
	{
		// Look for the next `stack`.
		dctx[DisasmContext_end_ip] = 0;
		while (DisasmNext(dctx) != DISASM_DONE && DisasmGetOpcode(dctx) != OP_STACK)
		{
			AMX_Write(endaddrDAT, _:DisasmGetOpcode(dctx));
			endaddrDAT += 4;
			for (startaddr = 0; startaddr < DisasmGetNumOperands(dctx); ++startaddr)
			{
				AMX_Write(endaddrDAT, _:DisasmGetOperand(dctx, startaddr));
				endaddrDAT += 4;
			}
			startaddr = 0;
		}
		@emit JUMP             endaddrDAT - AMX_HEADER_COD + YSI_g_sJumpOffset + 24
		AMX_Write(endaddrDAT     , _:RelocateOpcode(OP_STACK));
		AMX_Write(endaddrDAT + 4 , data[E_INLINE_DATA_STACK]);
		AMX_Write(endaddrDAT + 8 , _:RelocateOpcode(OP_ZERO_PRI));
		AMX_Write(endaddrDAT + 12, _:RelocateOpcode(OP_RETN));
		if (!startaddr)
		{
			// The write extended beyond the limit of where codescan was up to.  Adjust the stack
			// back down again by the size of the closure data (i.e. the data outside the current
			// inline).  This is AFTER the return, since we don't actually want the code to run,
			// just correct codescan's view of the world.
			AMX_Write(DisasmGetCurIp(dctx) + 4, -data[E_INLINE_DATA_LOCALS]);
		}
	}
	else if (data[E_INLINE_DATA_STACK])
	{
		// No parameters, but some stack.
		@emit JUMP             endaddrCOD + 16
		AMX_Write(endaddrDAT     , _:RelocateOpcode(OP_STACK));
		AMX_Write(endaddrDAT + 4 , data[E_INLINE_DATA_STACK]);
		AMX_Write(endaddrDAT + 8 , _:RelocateOpcode(OP_ZERO_PRI));
		AMX_Write(endaddrDAT + 12, _:RelocateOpcode(OP_RETN));
	}
	else
	{
		// No cleanup, no stack correction, no need to satisfy codescan.
		@emit JUMP             endaddrCOD + 16
		AMX_Write(endaddrDAT     , _:RelocateOpcode(OP_ZERO_PRI));
		AMX_Write(endaddrDAT + 4 , _:RelocateOpcode(OP_RETN));
		AMX_Write(endaddrDAT + 8 , nop);
		AMX_Write(endaddrDAT + 12, nop);
	}
}

#define CALL@Inline_OnAsmError Inline_OnAsmError("", ASM_ERROR_NONE)

static stock Inline_OnAsmError(const ctx[AsmContext], AsmError:error)
{
	switch (numargs() == 1 ? AsmGetError(ctx) : error)
	{
	case ASM_ERROR_OPCODE:          P:E("ASM_ERROR_OPCODE in Inline_Main.");
	case ASM_ERROR_OPERAND:         P:E("ASM_ERROR_OPERAND in Inline_Main.");
	case ASM_ERROR_SPACE:           P:E("ASM_ERROR_SPACE in Inline_Main.");
	case ASM_ERROR_LABEL_OVERFLOW:  P:E("ASM_ERROR_LABEL_OVERFLOW in Inline_Main.");
	case ASM_ERROR_LABEL_DUPLICATE: P:E("ASM_ERROR_LABEL_DUPLICATE in Inline_Main.");
	case ASM_ERROR_NONE: return;
	default: P:E("Unknown error in Inline_Main.");
	}
	// TODO: Abort codegen.
}

static stock Inline_DoCodeGen(const scanner[CodeScanner], const data[E_INLINE_DATA])
{
	new
		ctx[AsmContext];
	AsmInitPtr(ctx, data[E_INLINE_DATA_START] + AMX_HEADER_COD, data[E_INLINE_DATA_USER] - data[E_INLINE_DATA_START]);
	AsmSetErrorHandler(ctx, addressof (Inline_OnAsmError));
	Inline_DoRetnGen(ctx, scanner, data);
	Inline_GenerateLocalsCopy(ctx, data[E_INLINE_DATA_PARAMETERS], data[E_INLINE_DATA_PARAMETER_COUNT]);
	Inline_GeneratePostamble(ctx, data[E_INLINE_DATA_PARAMETERS], data[E_INLINE_DATA_PARAMETER_COUNT], bool:(data[E_INLINE_DATA_STATE] & 4), data[E_INLINE_DATA_STACK], data[E_INLINE_DATA_LOCALS]);
	Inline_GeneratePreamble(ctx, data[E_INLINE_DATA_STACK]);
	AsmEmitPadding(ctx);
}

public Callback_Release_(ResolvedAlloc:a)
{
	KillTimer(AMX_Read(_:a + _:E_INLINE_CALL_TIMER * cellbytes));
	free(Malloc_Reconcile(a));
}

#if __COMPILER_CONST_REF
	#pragma warning push
	#pragma warning disable 238
#endif
static stock Inline_Ref(const &ptr)
{
	#emit LOAD.S.pri       ptr
	#emit RETN
	__pragma("naked");
}
#if __COMPILER_CONST_REF
	#pragma warning pop
#endif

#if __COMPILER_CONST_REF
	#pragma warning push
	#pragma warning disable 238
#endif
stock Inline_UI_(const &header)
{
	// We use `&header` instead of `return` so that we can keep the tags
	// correct.  This also passes an address that we know is the bottom of the
	// part of the stack that we need to save for the closure.  The bottom two
	// variables in the stack must be preserved, since they store information
	// about the inline function (name and address), which may be required even
	// in the inline if it is called recursively.  The code is compiled to pass
	// `header` as the inline structure.  However, that is just for tag
	// checking, and we change that in assembly so that the return from this
	// function is truly what is pushed.
	// 
	// We can't use `AMX_Ref()` here because passing a `const &` to a `...` function
	// gets the address of a heap temporary, instead of the original.  Even
	// `const ...` doesn't solve this.
	P:3("Inline_UI_ called: %d", header);
	new
		ptr = Inline_Ref(header),
		frm = AMX_Read(header + cellbytes),
		args = Inline_NumArgs(ptr + frm),
		size = frm + 12 + args,
		// The size of the allocation makes very little difference, so even if
		// it isn't needed, we allocate extra memory here for the closure
		// storage.  The other option would be allocating it separately later
		// when we determine it is needed, but that would be no faster in the
		// common case, and slower in the uncommon case, so just do it together.
		Alloc:closure = malloc((size >>> __COMPILER_CELL_SHIFT) + (_:E_INLINE_CALL - 1));
	P:5("Inline_UI_: %d %d %d %d %d", ptr, frm, size, _:closure, AMX_Read(header));
	if (!closure)
		return 0;
	mset(closure, _:E_INLINE_CALL_NULL, 0);
	mset(closure, _:E_INLINE_CALL_HANDLER, _:addressof (Callback_CallHandler_<x>));
	mset(closure, _:E_INLINE_CALL_CLAIM, _:addressof (Callback_Claim_));
	mset(closure, _:E_INLINE_CALL_RELEASE, _:addressof (Callback_Release_<tResolvedAlloc:>));    
	mset(closure, _:E_INLINE_CALL_TIMER, YSI_SetTimerEx("Inline_MaybeFree_", 0, false, "i", _:closure));
	mset(closure, _:E_INLINE_CALL_FLAGS, e_INLINE_FLAG_CONST);
	mset(closure, _:E_INLINE_CALL_METADATA, 0);
	mset(closure, _:E_INLINE_CALL_SIZE, size);
	mset(closure, _:E_INLINE_CALL_SOURCE, ptr);
	mset(closure, _:E_INLINE_CALL_FUNCTION, AMX_Read(header));
	new
		ResolvedAlloc:ra = Malloc_Resolve(closure);
	RawMemCpy(_:ra + _:E_INLINE_CALL_PARAMS * cellbytes, ptr, size);
	AMX_Write(_:ra + (_:E_INLINE_CALL_PARAMS + 2) * cellbytes + frm, args);
	return Indirect_Ptr(ra);
}
#if __COMPILER_CONST_REF
	#pragma warning pop
#endif

stock Inline_UP_(const func[], const spec[] = "")
{
	// Convert a function name to a pointer.
	I@ = _:GetLocalFunction(func, spec);
}

/*-------------------------------------------------------------------------*//**
 * <param name="">Info on the restoration function.</param>
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

stock Callback_Restore_(...)
{
	assert(numargs() == 1);
	// Maintain the frame header.
	new
		closure = getarg(0);
	if (closure < 128)
		return false;
	closure = Indirect_DePtr(closure);
	if (closure < 0 || AMX_Read(closure))
		return true;
	// Called via a timer, or is const, or wasn't actually called, or is a public.
	if (AMX_Read(closure + _:E_INLINE_CALL_FLAGS * cellbytes) || !AMX_Read(closure + _:E_INLINE_CALL_TIMER * cellbytes))
	{
		return 0;
	}
	new
		ptr = AMX_Read(closure + _:E_INLINE_CALL_SOURCE * cellbytes),
		frm = AMX_Read(ptr) + cellbytes;
	frm = ptr + AMX_Read(frm);
	new
		ret = GetFrameReturn(frm),
		pfr = GetFramePreviousFrame(frm);
	RawMemCpy(ptr, closure + _:E_INLINE_CALL_PARAMS * cellbytes, AMX_Read(closure + _:E_INLINE_CALL_SIZE * cellbytes)),
	SetFrameReturn(frm, ret),
	SetFramePreviousFrame(frm, pfr);
	return 0;
}
#define Callback_Restore(%0) Callback_Restore_(_:%0)

stock Inline_Debug(ptr)
{
	// Get back to normal memory.
	new Alloc:data = Malloc_Reconcile(ResolvedAlloc:Indirect_DePtr(ptr));
	printf("ptr:                    %d", _:ptr);
	printf("resolved:               %d", _:Indirect_DePtr(ptr));
	#emit CONST.alt     YSI_gMallocMemory
	#emit STOR.S.alt    ptr
	printf("memory:                 %d", _:ptr);
	printf("slot:                   %d", _:data);
	printf("E_INLINE_CALL_NULL:     %d", mget(data, E_INLINE_CALL_NULL));
	printf("E_INLINE_CALL_HANDLER:  %d", mget(data, E_INLINE_CALL_HANDLER));
	printf("E_INLINE_CALL_CLAIM:    %d", mget(data, E_INLINE_CALL_CLAIM));
	printf("E_INLINE_CALL_RELEASE:  %d", mget(data, E_INLINE_CALL_RELEASE));
	printf("E_INLINE_CALL_METADATA: %d", mget(data, E_INLINE_CALL_METADATA));
	printf("E_INLINE_CALL_TIMER:    %d", mget(data, E_INLINE_CALL_TIMER));
	printf("E_INLINE_CALL_FLAGS:    %d", mget(data, E_INLINE_CALL_FLAGS));
	printf("E_INLINE_CALL_SIZE:     %d", mget(data, E_INLINE_CALL_SIZE));
	printf("E_INLINE_CALL_SOURCE:   %d", mget(data, E_INLINE_CALL_SOURCE));
	printf("E_INLINE_CALL_FUNCTION: %d", mget(data, E_INLINE_CALL_FUNCTION));
	printf("E_INLINE_CALL_PARAMS:   %d", _:Malloc_Reconcile(ResolvedAlloc:mget(data, E_INLINE_CALL_FUNCTION)));
}

