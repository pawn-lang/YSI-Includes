static bool:MD_InASCOrder(const array[][], const slot, const size = sizeof (array))
{
	new
		prev = cellmin;
	for (new i = 0; i != size; ++i)
	{
		if (array[i][slot] < prev)
			return false;
		prev = array[i][slot];
	}
	return true;
}

static bool:MD_InDESCOrder(const array[][], const slot, const size = sizeof (array))
{
	new
		prev = cellmax;
	for (new i = 0; i != size; ++i)
	{
		if (array[i][slot] > prev)
			return false;
		prev = array[i][slot];
	}
	return true;
}

static bool:MD_InASCOrderFloat(const Float:array[][], const slot, const size = sizeof (array))
{
	new
		Float:prev = FLOAT_NEGATIVE_INFINITY;
	for (new i = 0; i != size; ++i)
	{
		new
			Float:next = array[i][slot];
		if (next == next)
		{
			// Number after NAN.
			if (prev != prev)
				return false;
			if (next < prev)
				return false;
		}
		prev = next;
	}
	return true;
}

static bool:MD_InDESCOrderFloat(const Float:array[][], const slot, const size = sizeof (array))
{
	new
		Float:prev = FLOAT_INFINITY;
	for (new i = 0; i != size; ++i)
	{
		new
			Float:next = array[i][slot];
		if (next == next)
		{
			// Number after NAN.
			if (prev != prev)
				return false;
			if (next > prev)
				return false;
		}
		prev = next;
	}
	return true;
}

Test:MD_SortNumASC()
{
	new
		array[100][3];
	for (new i = 0; i != sizeof (array); ++i)
	{
		array[i][0] = Random(-7654);
		ASSERT(-7654 < array[i][0] <= 0);
		array[i][1] = Random(50);
		ASSERT(0 <= array[i][1] < 50);
		array[i][2] = Random(-3214, -8912);
		ASSERT(-8912 <= array[i][2] < -3214);
	}
	SortDeepArray(array, 0, .order = SORT_ASC);
	ASSERT(MD_InASCOrder(array, 0));
	SortDeepArray(array, 2, .order = SORT_ASC);
	ASSERT(MD_InASCOrder(array, 2));
}

Test:MD_SortNumDESC()
{
	new
		array[100][5];
	for (new i = 0; i != sizeof (array); ++i)
	{
		for (new j = 0; j != sizeof (array[]); ++j)
		{
			array[i][j] = Random(100, 1000);
			ASSERT(100 <= array[i][j] < 1000);
		}
	}
	SortDeepArray(array, 0, .order = SORT_DESC);
	ASSERT(MD_InDESCOrder(array, 0));
	SortDeepArray(array, 2, .order = SORT_DESC);
	ASSERT(MD_InDESCOrder(array, 2));
}

Test:MD_SortNumASCFloat()
{
	new
		Float:array[100][4];
	for (new i = 0; i != sizeof (array); ++i)
	{
		array[i][0] = RandomFloat(-88.99);
		ASSERT(-88.99 < array[i][0] <= 0.0);
		array[i][1] = RandomFloat(765.0);
		ASSERT(0.0 <= array[i][1] < 765.0);
		array[i][2] = RandomFloat(-5000.0, 2000.0);
		ASSERT(-5000.0 <= array[i][2] < 2000.0);
		ASSERT(array[i][0] == array[i][0]);
		ASSERT(array[i][1] == array[i][1]);
		ASSERT(array[i][2] == array[i][2]);
		if (i > 10)
			array[i][3] = FLOAT_NAN;
		else
			array[i][3] = RandomFloat(10.0);
	}
	SortDeepArray(array, 0, .order = SORT_ASC);
	ASSERT(MD_InASCOrderFloat(array, 0));
	SortDeepArray(array, 2, .order = SORT_ASC);
	ASSERT(MD_InASCOrderFloat(array, 2));
	SortDeepArray(array, 3, .order = SORT_ASC);
	ASSERT(MD_InASCOrderFloat(array, 3));
}

Test:MD_SortNumDESCFloat()
{
	new
		Float:array[100][6];
	for (new i = 0; i != sizeof (array); ++i)
	{
		for (new j = 0; j != sizeof (array[]); ++j)
		{
			array[i][j] = RandomFloat(2000.0, -9000.0, random(4));
			ASSERT(-9000.0 <= array[i][j] < 2000.0);
		}
		ASSERT(array[i][0] == array[i][0]);
		ASSERT(array[i][1] == array[i][1]);
		ASSERT(array[i][2] == array[i][2]);
		ASSERT(array[i][3] == array[i][3]);
		ASSERT(array[i][4] == array[i][4]);
		if (i > 50)
			array[i][5] = FLOAT_NAN;
		else
			array[i][5] = RandomFloat(20.0);
	}
	SortDeepArray(array, 0, .order = SORT_DESC);
	ASSERT(MD_InDESCOrderFloat(array, 0));
	SortDeepArray(array, 2, .order = SORT_DESC);
	ASSERT(MD_InDESCOrderFloat(array, 2));
	SortDeepArray(array, 5, .order = SORT_DESC);
	ASSERT(MD_InDESCOrderFloat(array, 5));
}

enum MD_TEST_ENUM_TWO_DIRECTIONS
{
	E_SORT_ORDER:MD_TEST_ORDER_FIELD,
	MD_TEST_VALUE_FIELD
}

Comparator:MD_TEST_Comparator(left[MD_TEST_ENUM_TWO_DIRECTIONS], right[MD_TEST_ENUM_TWO_DIRECTIONS])
{
	// Put ascending slots first, then descending ones.
	if (left[MD_TEST_ORDER_FIELD] == SORT_ASC)
	{
		if (right[MD_TEST_ORDER_FIELD] == SORT_ASC)
			return left[MD_TEST_VALUE_FIELD] - right[MD_TEST_VALUE_FIELD];
		else
			return -1;
	}
	else
	{
		if (right[MD_TEST_ORDER_FIELD] == SORT_ASC)
			return 1;
		else
			return right[MD_TEST_VALUE_FIELD] - left[MD_TEST_VALUE_FIELD];
	}
}

Test:MD_Sort_ShuffleAndReset()
{
	new array[100][MD_TEST_ENUM_TWO_DIRECTIONS];
	new copied[100][MD_TEST_ENUM_TWO_DIRECTIONS];
	for (new i = 0; i != sizeof (array); ++i)
	{
		copied[i][MD_TEST_ORDER_FIELD] = array[i][MD_TEST_ORDER_FIELD] = random(2) ? SORT_ASC : SORT_DESC;
		copied[i][MD_TEST_VALUE_FIELD] = array[i][MD_TEST_VALUE_FIELD] = random(200);
	}
	SortArrayUsingComparator(array, MD_TEST_Comparator);
	ResetDeepArray(array);
	for (new i = 0; i != sizeof (array); ++i)
	{
		ASSERT(array[i][MD_TEST_VALUE_FIELD] == copied[i][MD_TEST_VALUE_FIELD]);
		ASSERT(array[i][MD_TEST_ORDER_FIELD] == copied[i][MD_TEST_ORDER_FIELD]);
	}
	ShuffleDeepArray(array);
	ResetDeepArray(array);
	for (new i = 0; i != sizeof (array); ++i)
	{
		ASSERT(array[i][MD_TEST_VALUE_FIELD] == copied[i][MD_TEST_VALUE_FIELD]);
		ASSERT(array[i][MD_TEST_ORDER_FIELD] == copied[i][MD_TEST_ORDER_FIELD]);
	}
	ShuffleDeepArray(array);
	ResetDeepArray(array);
	for (new i = 0; i != sizeof (array); ++i)
	{
		ASSERT(array[i][MD_TEST_VALUE_FIELD] == copied[i][MD_TEST_VALUE_FIELD]);
		ASSERT(array[i][MD_TEST_ORDER_FIELD] == copied[i][MD_TEST_ORDER_FIELD]);
	}
}

TestCompile:addressof()
{
	AddressOfGetNextCall_();
}

TestCompile:addressof_jit()
{
	AddressofResolve();
}

TestCompile:amx()
{
	GetAmxAddress();
	ReadAmxCell(0);
	WriteAmxCell(0, 0);
}

TestCompile:amx_base()
{
	GetAmxBaseAddressNow();
	GetAmxBaseAddress();
}

TestCompile:amx_header()
{
	new
		info[AMX_FUNCSTUBNT],
		amxhdr[AMX_HDR],
		plain_amxhdr[AMX_HDR_CELLS];
	GetRawAmxHeader(plain_amxhdr);
	GetAmxHeaderNow(amxhdr);
	ResetStaticAmxHeader();
	GetAmxHeader(amxhdr);
	GetAmxHeaderComponent(AMX_HDR:0);
	PrintAmxHeader();
	GetNumPublics(amxhdr);
	GetPublicIndexFromAddress(0);
	GetPublicInfo(0, info);
	GetPublicIndexFromName("");
	GetPublicAddressFromIndex(0);
	GetPublicAddressFromName("");
	GetPublicNameFromIndex(0, "");
	GetPublicNameFromAddress(0, "");
	HookPublic(0, 0);
	GetNumNatives(amxhdr);
	GetNativeIndexFromAddress(0);
	GetNativeInfo(0, info);
	GetNativeIndexFromName("");
	GetNativeAddressFromIndex(0);
	GetNativeAddressFromName("");
	GetNativeNameFromIndex(0, "");
	GetNativeNameFromAddress(0, "");
	HookNative(0, 0);
	GetNumPubVars(amxhdr);
	GetPubVarInfo(0, info);
	GetPubVarIndexFromName("");
	GetPubVarIndexFromAddress(0);
	GetPubVarAddressFromIndex(0);
	GetPubVarAddressFromName("");
	GetPubVarNameFromIndex(0, "");
	GetPubVarNameFromAddress(0, "");
	GetNumTags(amxhdr);
	GetTagInfo(0, info);
	GetTagIndexFromName("");
	GetTagIndexFromID(0);
	GetTagIDFromIndex(0);
	GetTagIDFromName("");
	GetTagNameFromIndex(0, "");
	GetTagNameFromID(0, "");
	IsTagIDStrong(0);
	IsTagIDWeak(0);
	IsTagIDEmpty(0);
	IsTagNameStrong("");
	IsTagNameWeak("");
	IsTagNameEmpty("");
	IsTagIndexStrong(0);
	IsTagIndexWeak(0);
	IsTagIndexEmpty(0);
}

TestCompile:amx_jit()
{
	GetJITGeneratorVersion();
	GetAmxJITBaseAddress();
	ResolveJITAddress(0);
}

TestCompile:amx_memory()
{
	ref(0);
	deref(0);
	argref(0);
	argderef(0);
	GetAmxHeapBase();
	GetAmxHeapTop();
	GetAmxStackBase();
	GetAmxStackBottom();
	GetAmxFrame();
	SetAmxHeapTop(0);
	SetAmxStackBottom(0);
	SetAmxFrame(0);
	SetAmxNextInstructionPointer(0);
}

TestCompile:asm()
{
	new
		ctx[AsmContext];
	AsmEmitLabelStringize(ctx, "");
	AsmEmitJumpStringize(ctx, "", false);
	AsmEmitOpcode(ctx, Opcode:0);
	AsmEmitOperand(ctx, 0);
	AsmEmitInstruction(ctx, Opcode:0);
	AsmGetJumpAddressFromOffset(ctx, 0);
	AsmEmitJumpInstruction(ctx, Opcode:0, 0);
	AsmEmitJumpLabelInstruction(ctx, Opcode:0, "");
	AsmInitPtr(ctx, 0, 0);
	AsmGetPreviousWriteOffset();
	AsmGetBufferSize(ctx);
	AsmInit(ctx, "");
	AsmGetCode(ctx);
	AsmGetCodeSize(ctx);
	AsmGetError(ctx);
	AsmSetError(ctx, AsmError:0);
	AsmClearError(ctx);
	AsmGetErrorHandler(ctx);
	AsmSetErrorHandler(ctx, 0);
	AsmSetErrorHandlerName(ctx, "");
	AsmEmitPadding(ctx);
	AsmEmitAdd(ctx);
	AsmEmitAddC(ctx, 0);
	AsmEmitAddrAlt(ctx, 0);
	AsmEmitAddrPri(ctx, 0);
	AsmEmitAlignAlt(ctx, 0);
	AsmEmitAlignPri(ctx, 0);
	AsmEmitAnd(ctx);
	AsmEmitBounds(ctx, 0);
	AsmEmitBreak(ctx);
	AsmEmitCall(ctx, 0);
	AsmEmitCallAbs(ctx, 0);
	AsmEmitCallLabelStringize(ctx, "");
	AsmEmitCmps(ctx, 0);
	AsmEmitConstAlt(ctx, 0);
	AsmEmitConstPri(ctx, 0);
	AsmEmitDec(ctx, 0);
	AsmEmitDecAlt(ctx);
	AsmEmitDecI(ctx);
	AsmEmitDecPri(ctx);
	AsmEmitDecS(ctx, 0);
	AsmEmitEq(ctx);
	AsmEmitEqCAlt(ctx, 0);
	AsmEmitEqCPri(ctx, 0);
	AsmEmitFill(ctx, 0);
	AsmEmitGeq(ctx);
	AsmEmitGrtr(ctx);
	AsmEmitHalt(ctx, 0);
	AsmEmitHeap(ctx, 0);
	AsmEmitIdxaddr(ctx);
	AsmEmitIdxaddrB(ctx, 0);
	AsmEmitInc(ctx, 0);
	AsmEmitIncAlt(ctx);
	AsmEmitIncI(ctx);
	AsmEmitIncPri(ctx);
	AsmEmitIncS(ctx, 0);
	AsmEmitInvert(ctx);
	AsmEmitJeq(ctx, 0);
	AsmEmitJeqRel(ctx, 0);
	AsmEmitJgeq(ctx, 0);
	AsmEmitJgeqRel(ctx, 0);
	AsmEmitJgrtr(ctx, 0);
	AsmEmitJgrtrRel(ctx, 0);
	AsmEmitJleq(ctx, 0);
	AsmEmitJleqRel(ctx, 0);
	AsmEmitJless(ctx, 0);
	AsmEmitJlessRel(ctx, 0);
	AsmEmitJneq(ctx, 0);
	AsmEmitJneqRel(ctx, 0);
	AsmEmitJnz(ctx, 0);
	AsmEmitJnzRel(ctx, 0);
	AsmEmitJsgeq(ctx, 0);
	AsmEmitJsgeqRel(ctx, 0);
	AsmEmitJsgrtr(ctx, 0);
	AsmEmitJsgrtrRel(ctx, 0);
	AsmEmitJsleq(ctx, 0);
	AsmEmitJsleqRel(ctx, 0);
	AsmEmitJsless(ctx, 0);
	AsmEmitJslessRel(ctx, 0);
	AsmEmitJump(ctx, 0);
	AsmEmitJumpRel(ctx, 0);
	AsmEmitJzer(ctx, 0);
	AsmEmitJzerRel(ctx, 0);
	AsmEmitJrel(ctx, 0);
	AsmEmitJeqLabelStringize(ctx, "");
	AsmEmitJgeqLabelStringize(ctx, "");
	AsmEmitJgrtrLabelStringize(ctx, "");
	AsmEmitJleqLabelStringize(ctx, "");
	AsmEmitJlessLabelStringize(ctx, "");
	AsmEmitJneqLabelStringize(ctx, "");
	AsmEmitJnzLabelStringize(ctx, "");
	AsmEmitJsgeqLabelStringize(ctx, "");
	AsmEmitJsgrtrLabelStringize(ctx, "");
	AsmEmitJsleqLabelStringize(ctx, "");
	AsmEmitJslessLabelStringize(ctx, "");
	AsmEmitJumpLabelStringize(ctx, "");
	AsmEmitJzerLabelStringize(ctx, "");
	AsmEmitJrelLabelStringize(ctx, "");
	AsmEmitLctrl(ctx, 0);
	AsmEmitLeq(ctx);
	AsmEmitLess(ctx);
	AsmEmitLidx(ctx);
	AsmEmitLidxB(ctx, 0);
	AsmEmitLoadAlt(ctx, 0);
	AsmEmitLoadPri(ctx, 0);
	AsmEmitLoad(ctx, 0);
	AsmEmitLoadI(ctx);
	AsmEmitLoadSAlt(ctx, 0);
	AsmEmitLoadSPri(ctx, 0);
	AsmEmitLodbI(ctx, 0);
	AsmEmitLrefAlt(ctx, 0);
	AsmEmitLrefPri(ctx, 0);
	AsmEmitLrefSAlt(ctx, 0);
	AsmEmitLrefSPri(ctx, 0);
	AsmEmitMoveAlt(ctx);
	AsmEmitMovePri(ctx);
	AsmEmitMovs(ctx, 0);
	AsmEmitNeg(ctx);
	AsmEmitNeq(ctx);
	AsmEmitNop(ctx);
	AsmEmitNot(ctx);
	AsmEmitOr(ctx);
	AsmEmitPopAlt(ctx);
	AsmEmitPopPri(ctx);
	AsmEmitProc(ctx);
	AsmEmitPushAdr(ctx, 0);
	AsmEmitPushAlt(ctx);
	AsmEmitPushC(ctx, 0);
	AsmEmitPushPri(ctx);
	AsmEmitPush(ctx, 0);
	AsmEmitPushS(ctx, 0);
	AsmEmitRet(ctx);
	AsmEmitRetn(ctx);
	AsmEmitSctrl(ctx, 0);
	AsmEmitSdiv(ctx);
	AsmEmitSdivAlt(ctx);
	AsmEmitSgeq(ctx);
	AsmEmitSgrtr(ctx);
	AsmEmitShl(ctx);
	AsmEmitShlCAlt(ctx, 0);
	AsmEmitShlCPri(ctx, 0);
	AsmEmitShrCAlt(ctx, 0);
	AsmEmitShrCPri(ctx, 0);
	AsmEmitShr(ctx);
	AsmEmitSignAlt(ctx);
	AsmEmitSignPri(ctx);
	AsmEmitSleq(ctx);
	AsmEmitSless(ctx);
	AsmEmitSmul(ctx);
	AsmEmitSmulC(ctx, 0);
	AsmEmitSshr(ctx);
	AsmEmitSrefAlt(ctx, 0);
	AsmEmitSrefPri(ctx, 0);
	AsmEmitSrefSAlt(ctx, 0);
	AsmEmitSrefSPri(ctx, 0);
	AsmEmitStack(ctx, 0);
	AsmEmitStorAlt(ctx, 0);
	AsmEmitStorPri(ctx, 0);
	AsmEmitStorI(ctx);
	AsmEmitStorSAlt(ctx, 0);
	AsmEmitStorSPri(ctx, 0);
	AsmEmitStrbI(ctx, 0);
	AsmEmitSub(ctx);
	AsmEmitSubAlt(ctx);
	AsmEmitSwapAlt(ctx);
	AsmEmitSwapPri(ctx);
	AsmEmitSysreqC(ctx, 0);
	AsmEmitSysreqD(ctx, 0);
	AsmEmitSysreqPri(ctx);
	AsmEmitUdiv(ctx);
	AsmEmitUdivAlt(ctx);
	AsmEmitUmul(ctx);
	AsmEmitXchg(ctx);
	AsmEmitXor(ctx);
	AsmEmitZero(ctx, 0);
	AsmEmitZeroAlt(ctx);
	AsmEmitZeroPri(ctx);
	AsmEmitZeroS(ctx, 0);
	AsmEmitSysreq(ctx, "");
	AsmEmitPopArgs(ctx, 0);
	AsmEmitPushArg(ctx, 0);
	AsmEmitPushNumArgs(ctx, 0);
	AsmGetArgOffset(0);
}

TestCompile:asm_macros()
{
}

TestCompile:codescan()
{
	new
		csm[CodeScanner],
		ret[CodeScanner],
		ctx[AsmContext],
		dctx[DisasmContext],
		searcher[CodeScanMatcher];
	CodeScanAddMatcher(csm, searcher);
	CodeScanMatcherInit_(searcher, 0);
	CodeScanMatcherData(searcher, 0);
	CodeScanMatcherPattern_(searcher);
	CodeScanStep(dctx, csm);
	CodeScanRun(csm);
	CodeScanInit(csm);
	CodeScanGetFunctionScanner(csm, ret, dctx);
	CodeScanGetMatchScanner(csm, ret, dctx);
	CodeScanGetFunctionDisasm(csm, dctx);
	CodeScanGetMatchDisasm(csm, dctx);
	CodeScanGetFunctionAsm(csm, ctx);
	CodeScanGetMatchAsm(csm, ctx);
	CodeScanGetMatchFunc(csm);
	CodeScanGetMatchAddress(csm);
	CodeScanGetMatchFuncData(csm);
	CodeScanGetMatchAddressData(csm);
	CodeScanGetMatchLength(csm);
	CodeScanGetMatchType(csm);
	CodeScanGetMatchHeap(csm);
	CodeScanGetMatchStack(csm);
	CodeScanGetMatchHole(csm, 0);
	CodeScanGetMatchName(csm, "");
}

TestCompile:disasm()
{
	new
		dctx[DisasmContext];
	DisasmInit(dctx);
	DisasmDecodeInsn(dctx);
	DisasmNext(dctx);
	DisasmNextInsn(dctx);
	DisasmGetOpcode(dctx);
	DisasmGetOperand(dctx);
	DisasmGetNumOperands(dctx);
	DisasmNeedReloc(dctx);
	DisasmReloc(0);
	DisasmGetNextIp(dctx);
	DisasmGetCurIp(dctx);
	DisasmGetRemaining(dctx);
	DisasmGetInsnName(dctx, "");
	DisasmGetOperandReloc(dctx);
	DisasmWriteCode(File:0);
	DisasmWriteDataRowChar(File:0, 0, 0, 0);
	DisasmWriteDataRowHex(File:0, 0, 0, 0);
	DisasmWriteData(File:0);
	DisasmWriteFile(File:0);
	DisasmWrite("");
	DisasmDump("");
}

//TestCompile:dynamic_call()
//{
//	Push(0);
//	PushString("");
//	Pop();
//	Call(0);
//	SysreqC(0);
//	SysreqD(0);
//	CallN(0, 0);
//	SysreqCN(0, 0);
//	SysreqDN(0, 0);
//	CallFunction(0);
//	CallNative(0);
//	CallNativeByAddress(0);
//}

TestCompile:frame_info()
{
	GetCurrentFrame();
	GetFramePreviousFrame(0);
	GetFrameReturn(0);
	SetFramePreviousFrame(0, 0);
	SetFrameReturn(0, 0);
	SetFrameParameterSize(0, 0);
	SetFrameParameterCount(0, 0);
	GetFrameTotalSize(0);
	GetFrameTotalCount(0);
	GetFrameNextFrame(0);
	GetFrameLocalSize(0);
	GetFrameLocalCount(0);
	GetFrameHeaderSize(0);
	GetFrameHeaderCount(0);
	GetFrameParameterSize(0);
	GetFrameParameterCount(0);
	GetFrameParameter(0, 0);
	GetFrameVariable(0, 0);
	GetFrameLocal(0, 0);
	SetFrameParameter(0, 0, 0);
	SetFrameVariable(0, 0, 0);
	SetFrameLocal(0, 0, 0);
	GetCurrentFramePreviousFrame();
	GetCurrentFrameReturn();
	GetCurrentFrameTotalSize();
	GetCurrentFrameTotalCount();
	GetCurrentFrameLocalSize();
	GetCurrentFrameLocalCount();
	GetCurrentFrameHeaderSize();
	GetCurrentFrameHeaderCount();
	GetCurrentFrameParameterSize();
	GetCurrentFrameParameter(0);
	GetCurrentFrameLocal(0);
	GetCurrentFrameParameterCount();
	SetCurrentFrameReturn(0);
	SetCurrentFramePreviousFrame(0);
	SetCurrentParameterSize(0);
	SetCurrentParameterCount(0);
	GetFrameFunction(0);
	GetCurrentFrameFunction();
}

//TestCompile:heap_alloc()
//{
//	HeapAllocBytes(0);
//	HeapAllocCells(0);
//	HeapRelease(0);
//}

//TestCompile:jit()
//{
//	IsJITPresent();
//}

TestCompile:opcode()
{
	RelocateOpcodeNow(Opcode:0);
	IsOpcodeValid(Opcode:0);
	RelocateOpcode(Opcode:0);
	UnrelocateOpcode(Opcode:0);
	GetOpcodeInstructionInformation(Opcode:0);
	GetOpcodeInstructionName(Opcode:0);
	GetOpcodeInstructionParameters(Opcode:0);
	GetOpcodeInstructionRelocatable(Opcode:0);
}

TestCompile:os()
{
	GetOS();
	IsWindows();
	IsLinux();
}

//TestCompile:phys_memory()
//{
//	refabs();
//	ReadPhysMemory(0, "");
//	WritePhysMemory(0, "");
//	ReadPhysMemoryCell(0);
//	WritePhysMemoryCell(0, 0);
//}

//TestCompile:profiler()
//{
//	ProfilerInit();
//	ProfilerWriteData("");
//}

//TestCompile:shellcode()
//{
//	RunShellcode(0);
//}

//TestCompile:stack_dump()
//{
//	DumpStack();
//}

//TestCompile:stack_trace()
//{
//	GetFunctionFromReturnAddress(0);
//	GetStackTrace("");
//	PrintStackTrace("");
//}

//TestCompile:import_table()
//{
//	GetImportPointer("");
//	GetImportAddress("");
//	
//}

//TestCompile:ShellExecute()
//{
//	ShellExecute("", "", "", 0);
//}

