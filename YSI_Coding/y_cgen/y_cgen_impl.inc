/*+
 * <library
 *   name="y_cgen"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Large chunks of code that isn't used, so that the space can be reclaimed and reused by other code generating functions."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 *//** *//*
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

/// <p/>

CHAIN_HOOK(CGen)
#undef CHAIN_ORDER
#define CHAIN_ORDER CHAIN_NEXT(CGen)

#if !defined CGEN_MEMORY
	#if defined YSI_TESTS
		#define CGEN_MEMORY (50000)
	#else
		#define CGEN_MEMORY (10000)
	#endif
#endif

static stock
	/**
	 * <library>y_cgen</library>
	 */
	YSI_g_sCodeSpace = -1,
	/**
	 * <library>y_cgen</library>
	 */
	YSI_g_sCodeEnd = -1;

/*-------------------------------------------------------------------------*//**
 * <library>y_cgen</library>
 * <returns>
 * </returns>
 * <remarks>
 *   This is just a function that takes very little pawn code, but an awful lot
 *   of p-code, to call.  The pawn is just <c>CGEN()</c>, but thanks to having
 *   a huge number of reference parameters all with default constant values the
 *   generated assembly is massive, with twenty-six heap allocations and
 *   pushes.  It doesn't even do anything, just reserves a huge block of code
 *   space in which we can generate new code.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock CGEN(&a = 1, &b = 1, &c = 1, &d = 1, &e = 1, &f = 1, &g = 1, &h = 1, &i = 1, &j = 1, &k = 1, &l = 1, &m = 1, &n = 1, &o = 1, &p = 1, &q = 1, &r = 1, &s = 1, &t = 1, &u = 1, &v = 1, &w = 1, &x = 1, &y = 1, &z = 1)
{
	// We use `= 1` instead of `= 0` because that takes slightly more code - it
	// is a `CONST.pri 1` not `ZERO.pri`.
	#pragma unused a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z
}

forward @_y_cgen0_y_@();

/*-------------------------------------------------------------------------*//**
 * <library>y_cgen</library>
 * <remarks>
 *   Calls the <c>CGEN()</c> function a massive number of times, to generate a
 *   lot of useless assembly whose space we can reuse for useful code (i.e.
 *   <em>y_hooks</em> stubs).
 * </remarks>
 *//*------------------------------------------------------------------------**/

public @_y_cgen0_y_@()
{
	// Reserve a huge area of "COD" for our own use!
	// This is currently many calls to `CGEN()`, which takes up huge amounts of
	// space because of all the default parameters, which means we get to pass
	// loads without having them in code limiting the line lengths.  This gives:
	//   
	//   bytes_per_call = ((6 * 4 * 26) + 6)
	//   bytes_per_call = 630
	//   bytes_per_line = bytes_per_call * 16
	//   bytes_per_line = 10080 (~10KiB)
	//   
	#if CGEN_MEMORY >= 10000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 20000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 30000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 40000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 50000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 60000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 70000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 80000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 90000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 100000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 110000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 120000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 130000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 140000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 150000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 160000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 170000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 180000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 190000
		CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();CGEN();
	#endif
	#if CGEN_MEMORY >= 200000
		#error Too much codespace requested, please edit YSI_Coding\y_cgen\y_cgen_impl.inc
	#endif
}

forward @_y_cgen1_y_@();

/*-------------------------------------------------------------------------*//**
 * <library>y_cgen</library>
 * <remarks>
 *   Denotes the end of the unused code block, so very much relies on the
 *   compiler placing this function directly after <c>@_y_cgen0_y_@</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public @_y_cgen1_y_@()
{
	// This function SHOULD come straight after "@_y_hooks_@_0" in both the
	// public functions table and code segment if the compiler is true to form.
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cgen</library>
 * <param name="func">Function name to get the address of.</param>
 * <returns>
 *   The address of the function.
 * </returns>
 * <remarks>
 *   Why this doesn't use functions from in y_amx I don't know.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock CGen_GetAddr(const func[])
{
	return AMX_Read(funcidx(func) * __defsize_cells + AMX_HEADER_PUBLICS) + AMX_HEADER_COD;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cgen</library>
 * <remarks>
 *   Initialises the storage for unused code, and ensures that the functions
 *   being clobbered by said code are at least left in a semi-valid state.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock CGen_SetupCodeSpace()
{
	if (YSI_g_sCodeSpace != -1) return;
	YSI_g_sCodeSpace = CGen_GetAddr("@_y_cgen0_y_@"),
	YSI_g_sCodeEnd   = CGen_GetAddr("@_y_cgen1_y_@"),
	// Rewrite "@_y_cgen0_y_@" to just "return 0;".
	AMX_Write(YSI_g_sCodeSpace, _:RelocateOpcode(OP_PROC)),
	AMX_Write(YSI_g_sCodeSpace + __1_cell, _:RelocateOpcode(OP_ZERO_PRI)),
	AMX_Write(YSI_g_sCodeSpace + __2_cells, _:RelocateOpcode(OP_RETN)),
	YSI_g_sCodeSpace += __3_cells;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cgen</library>
 * <remarks>
 *   Initialise the library.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public OnCodeInit()
{
	{
		CGen_SetupCodeSpace();
		#if defined CGen_OnCodeInit
			CGen_OnCodeInit();
		#endif
		// Check that the code at this point is valid.  An OpCode is at most two
		// bytes (except "OP_SWITCH", but there are none of them in this area of
		// code because there are no "switch"es).  If the code here fails to
		// decompile, it is probably out of alignment - add a single "NOP" to
		// bring it back in to alignment.
		new
			ctx[DisasmContext];
		DisasmInit(ctx, YSI_g_sCodeSpace - AMX_HEADER_COD);
		for (new i = 0; i != 10; ++i)
		{
			if (DisasmNextInsn(ctx) == OP_NONE)
			{
				AMX_Write(YSI_g_sCodeSpace, _:RelocateOpcode(OP_NOP));
				return 1;
			}
		}
	}
	return 1;
}

#undef OnCodeInit
#define OnCodeInit CGen_OnCodeInit
#if defined CGen_OnCodeInit
	forward CGen_OnCodeInit();
#endif

forward CGen_OOM(ctx[AsmContext]);

/*-------------------------------------------------------------------------*//**
 * <library>y_cgen</library>
 * <param name="ctx">The <c>AsmContext</c> that ran out of space.</param>
 * <remarks>
 *   Called by amx_assembly when more code is written than there is space for,
 *   or on some other errors.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public CGen_OOM(ctx[AsmContext])
{
	switch (AsmGetError(ctx))
	{
	case ASM_ERROR_OPCODE:
	{
		Debug_Error("Unknown opcode written to code generation (CGen) space.");
	}
	case ASM_ERROR_OPERAND:
	{
		Debug_Error("Invalid operand written to code generation (CGen) space.");
	}
	case ASM_ERROR_SPACE:
	{
		// Just jump straight to the next CGEN step in the error.
		Debug_Fatal("Out of code generation (CGen) space.  The current value of `CGEN_MEMORY` is `%d`, please recompile with a higher value (approximately %d).", CGEN_MEMORY, ((CGEN_MEMORY / 10000) + 1) * CGEN_MEMORY);
		Debug_Info("    Note: This is perfectly safe and the recommended correct way to resolve this issue.");
	}
	case ASM_ERROR_LABEL_OVERFLOW:
	{
		Debug_Fatal("Out of label space.  The current value of `ASM_MAX_LABELS` is `%d`, please recompile with a higher value.", ASM_MAX_LABELS);
		Debug_Info("    Note: This is perfectly safe and the recommended correct way to resolve this issue.");
	}
	case ASM_ERROR_LABEL_DUPLICATE:
	{
		Debug_Fatal("Duplicate label in code generation.");
	}
	case ASM_ERROR_NONE:
	{
		// Do nothing, just for warning 244.
	}
	}
	AsmClearError(ctx);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cgen</library>
 * <param name="ctx">The assembly generation context.</param>
 * <remarks>
 *   Initialises the passed assembly generation context with a pointer in to
 *   our space code space region, complete with the remaining size and our
 *   error handler.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock CGen_UseCodeSpace(ctx[AsmContext])
{
	AsmInitPtr(ctx, YSI_g_sCodeSpace, YSI_g_sCodeEnd - YSI_g_sCodeSpace);
	AsmSetErrorHandlerName(ctx, "CGen_OOM");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cgen</library>
 * <returns>
 *   The next address with free code space.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock CGen_GetCodeSpace()
{
	return YSI_g_sCodeSpace;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_cgen</library>
 * <param name="num">How much to reduce the available code space by.</param>
 * <remarks>
 *   When a library has finished generating its code this function can be used
 *   to tell y_cgen how many cells it wrote, and thus move the space space
 *   pointer on by that much.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock CGen_AddCodeSpace(num)
{
	if (YSI_g_sCodeSpace == -1) Debug_Error("YSI_g_sCodeSpace is -1 in \"CGen_AddCodeSpace\"");
	else YSI_g_sCodeSpace += num;
}

