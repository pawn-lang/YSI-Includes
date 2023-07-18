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

/// <p/>

#define @y_L%0\32; @y_L
#define @y_S%0\32; @y_S
#define @y_L0000%0\32; @y_L0000
#define @y_S0000%0\32; @y_S0000

// The `LCTRL` and `SCTRL` codes are replaced by `CALL`s to these public
// functions.  We thus need to be exceptionally careful about the code run in
// them.  They need to set the parameters (since there was no value pushed), and
// preserve both `pri` and `alt` to pass to the child implementation.
#define @lctrl(%0)%1(%2) _F<@y_L>%0(); _F<@y_L>%0() { return %1(0, 0); } %1(%2)
#define @sctrl(%0)%1(%2) _F<@y_S>%0(); _F<@y_S>%0() { %1(0, 0); } %1(%2)

// The code found in the function.  Replaces everything, including `PROC` (so
// there is no frame update yet):

static stock
	/**
	 * <library>y_ctrl</library>
	 */
	YSI_g_sBaseRelocation,
	/**
	 * <library>y_ctrl</library>
	 */
	YSI_g_sLCTRLStubAddress,
	/**
	 * <library>y_ctrl</library>
	 */
	YSI_g_sSCTRLStubAddress;

#define CALL@CTRL_LCTRLStub%8() CTRL_LCTRLStub%8()
#define CALL@CTRL_SCTRLStub%8() CTRL_SCTRLStub%8()

/*-------------------------------------------------------------------------*//**
 * <library>y_ctrl</library>
 * <remarks>
 *   Initialise the library.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public OnCodeInit()
{
	{
		YSI_g_sBaseRelocation = -DisasmReloc(0);
		YSI_g_sLCTRLStubAddress = addressof (CTRL_LCTRLStub) + __1_cell + YSI_g_sBaseRelocation;
		YSI_g_sSCTRLStubAddress = addressof (CTRL_SCTRLStub) + __1_cell + YSI_g_sBaseRelocation;

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

		// Rewrite the functions after scanning so that we can still look up
		// their addresses before invalidating them all (not that we currently
		// do).

		// Loop over all `@y_L` (`LCTRL`) and `@y_S` (`SCTRL`) functions and
		// convert their file contents.
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

/*-------------------------------------------------------------------------*//**
 * <library>y_ctrl</library>
 * <remarks>
 *   For every custom readable control register we define we need a special
 *   call stub that can convert from passing the parameters in registers to
 *   passing the parameters on the stack, without clobbering <c>alt</c>.  A lot
 *   of the code is common to all of these stubs, and this function implements
 *   that common code.  The final handler and return addresses are passed to
 *   this, and the parameters are extracted from <c>pri</c> and <c>alt</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock CTRL_LCTRLStub()
{
	// The call to this function skips the `PROC` - we don't want it.

	// Save `pri` and `alt.
	#emit PUSH.alt
	#emit PUSH.pri

	// We can finally "enter" the function.
	#emit PUSH.C           __4_cells
	#emit PUSH.pri
	#emit PROC

	// Get the return address.
	#emit LOAD.S.pri       __param3_offset
	#emit STOR.S.pri       __return_offset

	// Push the `pri` and `alt` parameters.
	#emit PUSH.S           __param1_offset
	#emit PUSH.S           __param0_offset
	#emit PUSH.C           __2_cells

	// And set up a second function call.
	#emit LCTRL            __cip
	#emit ADD.C            __9_cells
	#emit LCTRL            __jit_jump
	#emit PUSH.pri
	#emit LOAD.S.pri       __param2_offset
	#emit SCTRL            __cip

	// We return to here, from which cleanup is easy.
	#emit LOAD.S.alt       __param1_offset
	#emit RETN
}

/*-------------------------------------------------------------------------*//**
 * <library>y_ctrl</library>
 * <remarks>
 *   For every custom writable control register we define we need a special
 *   call stub that can convert from passing the parameters in registers to
 *   passing the parameters on the stack, without clobbering the registers.  A
 *   lot of the code is common to all of these stubs, and this function
 *   implements that common code.  The final handler and return addresses are
 *   passed to this, and the parameters are extracted from <c>pri</c> and
 *   <c>alt</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock CTRL_SCTRLStub()
{
	// The call to this function skips the `PROC` - we don't want it.

	// Save `pri` and `alt.
	#emit PUSH.alt
	#emit PUSH.pri

	// We can finally "enter" the function.
	#emit PUSH.C           __4_cells
	#emit PUSH.pri
	#emit PROC

	// Get the return address.
	#emit LOAD.S.pri       __param3_offset
	#emit STOR.S.pri       __return_offset

	// Push the `pri` and `alt` parameters.
	#emit PUSH.S           __param1_offset
	#emit PUSH.S           __param0_offset
	#emit PUSH.C           __2_cells

	// And set up a second function call.
	#emit LCTRL            __cip
	#emit ADD.C            __9_cells
	#emit LCTRL            __jit_jump
	#emit PUSH.pri
	#emit LOAD.S.pri       __param2_offset
	#emit SCTRL            __cip

	// We return to here, from which cleanup is easy.
	#emit LOAD.S.alt       __param1_offset
	#emit LOAD.S.pri       __param0_offset
	#emit RETN
}

/*-------------------------------------------------------------------------*//**
 * <library>y_ctrl</library>
 * <param name="addr">The address to write to.</param>
 * <remarks>
 *   For every custom readable control register we define we need a special
 *   call stub that can convert from passing the parameters in registers to
 *   passing the parameters on the stack, without clobbering <c>alt</c>.  This
 *   generates those stubs.
 * </remarks>
 *//*------------------------------------------------------------------------**/

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
	AsmInitPtr(ctx, addr + AMX_HEADER_COD, __8_cells);

	// Write a function in case someone tries to call this public normally.
	@emit PROC
	@emit CALL.abs         addr + __4_cells
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
	//     PUSH.C              __2_cells
	//     CALL                %1
	//     RETN
	//
	// And the code we actually want is only eight cells.
}

/*-------------------------------------------------------------------------*//**
 * <library>y_ctrl</library>
 * <param name="addr">The address to write to.</param>
 * <remarks>
 *   For every custom writable control register we define we need a special
 *   call stub that can convert from passing the parameters in registers to
 *   passing the parameters on the stack, without clobbering the registers.
 *   This generates those stubs.
 * </remarks>
 *//*------------------------------------------------------------------------**/

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
	AsmInitPtr(ctx, addr + AMX_HEADER_COD, __8_cells);

	// Write a tiny empty function in case someone tries to call this public
	// normally.
	@emit PROC
	@emit CALL.abs         addr + __4_cells
	@emit RETN

	@emit PUSH.C           handlerAddress
	@emit JUMP             YSI_g_sSCTRLStubAddress
}

/*-------------------------------------------------------------------------*//**
 * <library>y_ctrl</library>
 * <param name="scanner">The codescan scanner that found a matching pattern.</param>
 * <remarks>
 *   This function is called for every single <c>LCTRL</c> in the compiled AMX,
 *   after they are found by the code scanner.  It checks if the found register
 *   load is for one of the new registers and replaces <c>LCTRL</c> with a
 *   special <c>CALL</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock CTRL_FoundLCTRL(const scanner[CodeScanner])
{
	Debug_Print6("CTRL_FoundLCTRL: Found LCTRL");
	new reg = CodeScanGetMatchHole(scanner, 0);
	if (0 <= reg <= 255)
	{
		// Reserved registers (VM and plugins).  Do nothing.
		return;
	}
	Debug_Print4("CTRL_FoundLCTRL Valid: %d", reg);
	new
		ctx[AsmContext];
	AsmInitPtr(ctx, CodeScanGetMatchAddress(scanner) + AMX_HEADER_COD, __2_cells);
	new
		ptr,
		name[FUNCTION_LENGTH];
	format(name, sizeof (name), #_F<@y_L>%d,reg);//NOSPACE!
	if (AMX_GetPublicPointer(0, ptr, name, true))
	{
		@emit CALL.abs         ptr + __4_cells
	}
	else
	{
		@emit NOP
		@emit NOP
	}
	Debug_Print5("CTRL_FoundLCTRL Name: %s, Index: %d, %d", name, ptr, AMX_GetPublicPointer(0, ptr, name, true));
}

/*-------------------------------------------------------------------------*//**
 * <library>y_ctrl</library>
 * <param name="scanner">The codescan scanner that found a matching pattern.</param>
 * <remarks>
 *   This function is called for every single <c>SCTRL</c> in the compiled AMX,
 *   after they are found by the code scanner.  It checks if the found register
 *   store is for one of the new registers and replaces <c>SCTRL</c> with a
 *   special <c>CALL</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock CTRL_FoundSCTRL(const scanner[CodeScanner])
{
	Debug_Print6("CTRL_FoundSCTRL: Found SCTRL");
	new reg = CodeScanGetMatchHole(scanner, 0);
	if (0 <= reg <= 255)
	{
		// Reserved registers (VM and plugins).  Do nothing.
		return;
	}
	Debug_Print4("CTRL_FoundSCTRL Valid: %d", reg);
	new
		ctx[AsmContext];
	AsmInitPtr(ctx, CodeScanGetMatchAddress(scanner) + AMX_HEADER_COD, __2_cells);
	new
		ptr,
		name[FUNCTION_LENGTH];
	format(name, sizeof (name), #_F<@y_S>%d,reg);//NOSPACE!
	if (AMX_GetPublicPointer(0, ptr, name, true))
	{
		@emit CALL.abs         ptr + __4_cells
	}
	else
	{
		@emit NOP
		@emit NOP
	}
	Debug_Print5("CTRL_FoundSCTRL Name: %s, Index: %d, %d", name, ptr, AMX_GetPublicPointer(0, ptr, name, true));
}

