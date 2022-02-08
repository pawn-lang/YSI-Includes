#define @y_L%0\32; @y_L
#define @y_S%0\32; @y_S

// The `LCTRL` and `SCTRL` codes are replaced by `CALL`s to these public
// functions.  We thus need to be exceptionally careful about the code run in
// them.  They need to set the parameters (since there was no value pushed), and
// preserve both `pri` and `alt` to pass to the child implementation.
#define @lctrl(%0)%1(%2) @y_L%0(); @y_L%0() { return %1(0,0); } %1(%2)
#define @sctrl(%0)%1(%2) @y_S%0(); @y_S%0() { %1(0,0); } %1(%2)

// The code found in the function.  Replaces everything, including `PROC` (so
// there is no frame update yet):

public OnCodeInit()
{
	// Scan for `LCTRL` and `SCTRL`.  Modify any that are >= 256 to calls.
	// Optimised.
	new scanner[CodeScanner];
	CodeScanInit(scanner);

	new lctrl[CodeScanMatcher];
	CodeScanMatcherInit(lctrl, &CTL_FoundLCTRL);
	CodeScanMatcherPattern(lctrl,
		OP(LCTRL, ???)
	);
	CodeScanAddMatcher(scanner, lctrl);

	new sctrl[CodeScanMatcher];
	CodeScanMatcherInit(sctrl, &CTL_FoundSCTRL);
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
		//name[FUNCTION_LENGTH char],
		//addr,
		//reg,
		entry;
	while ((idx = AMX_GetPublicEntryPrefix(idx, entry, _A<@y_L>)))
	{
		//addr = AMX_Read(entry);
		//AMX_ReadString(AMX_Read(entry + 4) + AMX_BASE_ADDRESS + 4, name);
		//reg = strval(name);
		// TODO: Invalidate entries.
		//CTL_WriteStub(addr);
		CTL_WriteStub(AMX_Read(entry));
	}

	while ((idx = AMX_GetPublicEntryPrefix(idx, entry, _A<@y_S>)))
	{
		CTL_WriteStub(AMX_Read(entry));
	}

	return 1;
}

static stock CTL_WriteStub(addr)
{
	// Find the call target.
	new
		target,
		dctx[DisasmContext];
	DisasmInit(dctx, addr);
	while (DisasmNext(dctx)) {
		if (dctx[DisasmContext_opcode] == OP_CALL) {
			target = DisasmGetOperand(dctx);
			break;
		}
	}

	new
		ctx[AsmContext];
	AsmInitPtr(ctx, addr + AMX_HEADER_COD, 32);
	// Search the function for a call to the implementation.

	// Pass `pri` and `alt` as parameters, and get the return address.
	@emit SWAP.alt
	@emit PUSH.pri

	// Push the parameter count.
	@emit PUSH.C           8

	// Push the return address.
	@emit PUSH.alt

	// Jump to the function.
	@emit JUMP             target
	@emit NOP
    
	// There is no way that can't fit within the code space reserved by the wrapper
	// public.  By my maths the smallest it can possibly be is ten cells:
	//
	//     PROC
	//     PUSH.C              0
	//     PUSH.C              0
	//     PUSH.C              8
	//     CALL                %1
	//     RETN
	//
	// And the code we actually want is only seven cells.  Even with `#pragma naked`
	// removing `PROC` and `RETN` we would have enough space.
}

static stock CTL_FoundLCTRL(const scanner[CodeScanner])
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
		@emit CALL.abs         ptr
	}
	else
	{
		@emit NOP
		@emit NOP
	}
}

static stock CTL_FoundSCTRL(const scanner[CodeScanner])
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
		@emit CALL.abs         ptr
	}
	else
	{
		@emit NOP
		@emit NOP
	}
}

