#if defined _INC_y_cgen
	#endinput
#endif
#define _INC_y_cgen

/*+
 * <library name="y_cgen">
 * <section>
 *  Description
 * </section>
 *  Large chunks of code that isn't used, so that the space can be reclaimed and
 *  reused by other code generating functions.
 * <section>
 *  Version
 * </section>
 *  1.0
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

#include "..\..\YSI_Core\y_core\y_thirdpartyinclude"

CHAIN_HOOK(CGen)
#undef CHAIN_ORDER
#define CHAIN_ORDER CHAIN_NEXT(CGen)

#if !defined CGEN_MEMORY
	#define CGEN_MEMORY (10000)
#endif

static stock
	YSI_g_sCodeSpace = -1,
	YSI_g_sCodeEnd = -1;

static stock CGEN(&a = 1, &b = 1, &c = 1, &d = 1, &e = 1, &f = 1, &g = 1, &h = 1, &i = 1, &j = 1, &k = 1, &l = 1, &m = 1, &n = 1, &o = 1, &p = 1, &q = 1, &r = 1, &s = 1, &t = 1, &u = 1, &v = 1, &w = 1, &x = 1, &y = 1, &z = 1)
{
	// We use `= 1` instead of `= 0` because that takes slightly more code - it
	// is a `CONST.pri 1` not `ZERO.pri`.
	#pragma unused a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z
}

forward _@_y_cgen_@_0();

public _@_y_cgen_@_0()
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
	//   N = 16.25
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
		#error Too much codespace requested, please edit YSI_Coding\y_cgen\y_cgen
	#endif
}

forward _@_y_cgen_@_1();

public _@_y_cgen_@_1()
{
	// This function SHOULD come straight after "_@_y_hooks_@_0" in both the
	// public functions table and code segment if the compiler is true to form.
}

static stock CGen_GetAddr(const func[])
{
	return AMX_Read(funcidx(func) * 8 + AMX_HEADER_PUBLICS) + AMX_HEADER_COD;
}

static stock CGen_SetupCodeSpace()
{
	if (YSI_g_sCodeSpace != -1) return;
	YSI_g_sCodeSpace = CGen_GetAddr("_@_y_cgen_@_0"),
	YSI_g_sCodeEnd   = CGen_GetAddr("_@_y_cgen_@_1"),
	// Rewrite "_@_y_cgen_@_0" to just "return 0;".
	AMX_Write(YSI_g_sCodeSpace, _:RelocateOpcode(OP_PROC)),
	AMX_Write(YSI_g_sCodeSpace + 4, _:RelocateOpcode(OP_ZERO_PRI)),
	AMX_Write(YSI_g_sCodeSpace + 8, _:RelocateOpcode(OP_RETN)),
	YSI_g_sCodeSpace += 12;
}

public OnCodeInit()
{
	CGen_SetupCodeSpace();
	#if defined CGen_OnCodeInit
		CGen_OnCodeInit();
	#endif
	// Check that the code at this point is valid.  An OpCode is at most two
	// bytes (except "OP_SWITCH", but there are none of them in this area of
	// code because there are no "switch"es).  If the code here fails to
	// decompile, it is probably out of alignment - add a single "NOP" to bring
	// it back in to alignment.
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
	return 1;
}

#undef OnCodeInit
#define OnCodeInit CGen_OnCodeInit
#if defined CGen_OnCodeInit
	forward CGen_OnCodeInit();
#endif

forward CGen_OOM(ctx[AsmContext]);

public CGen_OOM(ctx[AsmContext])
{
	switch (AsmGetError(ctx))
	{
	case ASM_ERROR_OPCODE:
	{
		P:E("Unknown opcode written to code generation (CGen) space.");
	}
	case ASM_ERROR_OPERAND:
	{
		P:E("Invalid operand written to code generation (CGen) space.");
	}
	case ASM_ERROR_SPACE:
	{
		static excess = 0;
		// This is just an estimate of how much more space is required, assuming that each opcode
		// has (on average) half a parameter.
		excess += 6;
		P:F("Out of code generation (CGen) space.  The current value of `CGEN_MEMORY` is `%d`, please recompile with a higher value (approximately %d).", CGEN_MEMORY, CGEN_MEMORY + excess);
	}
	case ASM_ERROR_LABEL_OVERFLOW:
	{
		P:F("Out of label space.  The current value of `ASM_MAX_LABELS` is `%d`, please recompile with a higher value.", ASM_MAX_LABELS);
	}
	case ASM_ERROR_LABEL_DUPLICATE:
	{
		P:F("Duplicate label in code generation.");
	}
	}
	AsmClearError(ctx);
}

stock CGen_UseCodeSpace(ctx[AsmContext])
{
	AsmInitPtr(ctx, YSI_g_sCodeSpace, YSI_g_sCodeEnd - YSI_g_sCodeSpace);
	AsmSetErrorHandlerName(ctx, "CGen_OOM");
}

stock CGen_GetCodeSpace()
{
	return YSI_g_sCodeSpace;
}

stock CGen_AddCodeSpace(num)
{
	if (YSI_g_sCodeSpace == -1) P:E("YSI_g_sCodeSpace is -1 in \"CGen_AddCodeSpace\"");
	else YSI_g_sCodeSpace += num;
}

