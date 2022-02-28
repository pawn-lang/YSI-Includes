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

#define @y_L%0\32; @y_L
#define @y_S%0\32; @y_S

// The `LCTRL` and `SCTRL` codes are replaced by `CALL`s to these public
// functions.  We thus need to be exceptionally careful about the code run in
// them.  They need to set the parameters (since there was no value pushed), and
// preserve both `pri` and `alt` to pass to the child implementation.
#define @lctrl(%0)%1(%2) @y_L%0(); @y_L%0() { return %1(0, 0); } %1(%2)
#define @sctrl(%0)%1(%2) @y_S%0(); @y_S%0() { %1(0, 0); } %1(%2)

// The code found in the function.  Replaces everything, including `PROC` (so
// there is no frame update yet):

static stock
	YSI_g_sBaseRelocation,
	YSI_g_sLCTRLStubAddress,
	YSI_g_sSCTRLStubAddress;

#define CALL@CTRL_LCTRLStub CTRL_LCTRLStub()
#define CALL@CTRL_SCTRLStub CTRL_SCTRLStub()

public OnCodeInit()
{
	YSI_g_sBaseRelocation = -DisasmReloc(0);
	YSI_g_sLCTRLStubAddress = addressof (CTRL_LCTRLStub) + 4 + YSI_g_sBaseRelocation;
	YSI_g_sSCTRLStubAddress = addressof (CTRL_SCTRLStub) + 4 + YSI_g_sBaseRelocation;

	// Scan for `LCTRL` and `SCTRL`.  Modify any that are >= 256 to calls.
	// Optimised.
	new scanner[CodeScanner];
	CodeScanInit(scanner);

	new lctrl[CodeScanMatcher];
	CodeScanMatcherInit(lctrl, &CTRL_FoundLCTRL);
	CodeScanMatcherPattern(lctrl,
		OP(LCTRL, ???)
	);
	CodeScanAddMatcher(scanner, lctrl);

	new sctrl[CodeScanMatcher];
	CodeScanMatcherInit(sctrl, &CTRL_FoundSCTRL);
	CodeScanMatcherPattern(sctrl,
		OP(SCTRL, ???)
	);
	CodeScanAddMatcher(scanner, sctrl);

	CodeScanRun(scanner);

	// Rewrite the functions after scanning so that we can still look up their
	// addresses before invalidating them all (not that we currently do).

	// Loop over all `@y_L` (`LCTRL`) and `@y_S` (`SCTRL`) functions and convert
	// their file contents.
	new
		idx = 0,
		addr;
	while ((idx = AMX_GetPublicPointerPrefix(idx, addr, _A<@y_L>)))
	{
		CTRL_WriteLCTRLStub(addr);
	}

	while ((idx = AMX_GetPublicPointerPrefix(idx, addr, _A<@y_S>)))
	{
		CTRL_WriteSCTRLStub(addr);
	}

	#if defined CTRL_OnCodeInit
		return CTRL_OnCodeInit();
	#else
		return 1;
	#endif
}

#if defined _ALS_OnCodeInit
	#undef OnCodeInit
#endif
#define _ALS_OnCodeInit
#define OnCodeInit( CTRL_OnCodeInit(
#if defined CTRL_OnCodeInit
	forward CTRL_OnCodeInit();
#endif

static stock CTRL_LCTRLStub()
{
	// The call to this function skips the `PROC` - we don't want it.

	// Save `pri` and `alt.
	#emit PUSH.alt
	#emit PUSH.pri

	// We can finally "enter" the function.
	#emit PUSH.C           16
	#emit PUSH.pri
	#emit PROC

	// Get the return address.
	#emit LOAD.S.pri       24
	#emit STOR.S.pri       4

	// Push the `pri` and `alt` parameters.
	#emit PUSH.S           16
	#emit PUSH.S           12
	#emit PUSH.C           8

	// And set up a second function call.
	#emit LCTRL            6
	#emit ADD.C            36
	#emit LCTRL            8
	#emit PUSH.pri
	#emit LOAD.S.pri       20
	#emit SCTRL            6

	// We return to here, from which cleanup is easy.
	#emit LOAD.S.alt       16
	#emit RETN
}

static stock CTRL_SCTRLStub()
{
	// The call to this function skips the `PROC` - we don't want it.

	// Save `pri` and `alt.
	#emit PUSH.alt
	#emit PUSH.pri

	// We can finally "enter" the function.
	#emit PUSH.C           16
	#emit PUSH.pri
	#emit PROC

	// Get the return address.
	#emit LOAD.S.pri       24
	#emit STOR.S.pri       4

	// Push the `pri` and `alt` parameters.
	#emit PUSH.S           16
	#emit PUSH.S           12
	#emit PUSH.C           8

	// And set up a second function call.
	#emit LCTRL            6
	#emit ADD.C            36
	#emit LCTRL            8
	#emit PUSH.pri
	#emit LOAD.S.pri       20
	#emit SCTRL            6

	// We return to here, from which cleanup is easy.
	#emit LOAD.S.alt       16
	#emit LOAD.S.pri       12
	#emit RETN
}

static stock CTRL_WriteLCTRLStub(addr)
{
	// Find the call target.
	new
		handlerAddress,
		dctx[DisasmContext];
	DisasmInit(dctx, addr);
	while (DisasmNext(dctx))
	{
		if (DisasmGetOpcode(dctx) == OP_CALL)
		{
			// Search the function for a call to the implementation.
			handlerAddress = DisasmGetOperandReloc(dctx);
			break;
		}
	}

	new
		ctx[AsmContext];
	AsmInitPtr(ctx, addr + AMX_HEADER_COD, 32);

	// Write a function in case someone tries to call this public normally.
	@emit PROC
	@emit CALL.abs         addr + 16
	@emit RETN

	// Push the implementation address and jump to the common register
	// preserving stub, so that `pri` and `alt` aren't clobbered (skipping
	// `PROC`).
	@emit PUSH.C           handlerAddress
	@emit JUMP             YSI_g_sLCTRLStubAddress

	// There is no way that can't fit within the code space reserved by the wrapper
	// public.  By my maths the smallest it can possibly be is nine cells:
	//
	//     PROC
	//     ZERO.pri
	//     PUSH.pri
	//     PUSH.pri
	//     PUSH.C              8
	//     CALL                %1
	//     RETN
	//
	// And the code we actually want is only eight cells.
}

static stock CTRL_WriteSCTRLStub(addr)
{
	// Find the call target.
	new
		handlerAddress,
		dctx[DisasmContext];
	DisasmInit(dctx, addr);
	while (DisasmNext(dctx))
	{
		if (dctx[DisasmContext_opcode] == OP_CALL)
		{
			handlerAddress = DisasmGetOperandReloc(dctx);
			break;
		}
	}

	new
		ctx[AsmContext];
	AsmInitPtr(ctx, addr + AMX_HEADER_COD, 32);

	// Write a tiny empty function in case someone tries to call this public
	// normally.
	@emit PROC
	@emit CALL.abs         addr + 16
	@emit RETN

	@emit PUSH.C           handlerAddress
	@emit JUMP             YSI_g_sSCTRLStubAddress
}

static stock CTRL_FoundLCTRL(const scanner[CodeScanner])
{
	new reg = CodeScanGetMatchHole(scanner, 0);
	if (0 <= reg <= 255)
	{
		// Reserved registers (VM and plugins).  Do nothing.
		return;
	}
	new
		ctx[AsmContext];
	AsmInitPtr(ctx, CodeScanGetMatchAddress(scanner) + AMX_HEADER_COD, 8);
	new
		ptr,
		name[FUNCTION_LENGTH];
	format(name, sizeof (name), "@y_L%d", reg);
	if (AMX_GetPublicPointer(0, ptr, name))
	{
		@emit CALL.abs         ptr + 16
	}
	else
	{
		@emit NOP
		@emit NOP
	}
}

static stock CTRL_FoundSCTRL(const scanner[CodeScanner])
{
	new reg = CodeScanGetMatchHole(scanner, 0);
	if (0 <= reg <= 255)
	{
		// Reserved registers (VM and plugins).  Do nothing.
		return;
	}
	new
		ctx[AsmContext];
	AsmInitPtr(ctx, CodeScanGetMatchAddress(scanner) + AMX_HEADER_COD, 8);
	new
		ptr,
		name[FUNCTION_LENGTH];
	format(name, sizeof (name), "@y_S%d", reg);
	if (AMX_GetPublicPointer(0, ptr, name))
	{
		@emit CALL.abs         ptr + 16
	}
	else
	{
		@emit NOP
		@emit NOP
	}
}

