#if defined _INC_y_cgen
	#endinput
#endif
#define _INC_y_cgen

#include "..\YSI_Storage\y_amx"
#include "..\YSI_Internal\amx_assembly"

// We use "s" not a string literal as we are trying to use up code space, not
// data space!
#define _CODE_1 SetTimerEx(s,0,0,s,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define _CODE_2 _CODE_1;_CODE_1;_CODE_1;_CODE_1;_CODE_1;_CODE_1

static stock
	YSI_g_sCodeSpace = -1,
	YSI_g_sCodeEnd = -1;

forward _@_y_cgen_@_0();

public _@_y_cgen_@_0()
{
	// Reserve a huge area of "COD" for our own use!
	static
		s[] = "";
	// This reserves about 10kb of space in "COD".  If 10kb isn't enough I don't
	// know WHAT you're doing - that's enough space for about 200 hooks!
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	// These are blocks of 16 lines.  If you ever need to increase this space,
	// just duplicate a block of 16 lines.  Do not put multiple "_CODE_2;"
	// statements on one line - the pre-processor expands this so much that that
	// will probably just crash.
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
	_CODE_2;
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

forward OnCodeInit();

public OnCodeInit()
{
	CGen_SetupCodeSpace();
	#if defined CGen_OnCodeInit
		CGen_OnCodeInit();
	#endif
	// Can't use "memset" or another fast function because this is in the code
	// area, not the data area.  Clear out all the remainder AFTER other code
	// generations are complete to reduce the amount of wasted time but still
	// fill up the space with NOPs to avoid crashes.  An even better option
	// would be to start a decompilation, run it through a few OpCodes, and if
	// it passes do nothing, otherwise write one NOP and try again - the ASM
	// will at most be one cell out from code overwriting other code, so we will
	// only need to write a maximum of one cell to bring it back in line such
	// that the JIT doesn't see an unknown OpCode.
	new
		Opcode:nop = RelocateOpcode(OP_NOP);
	for (new i = YSI_g_sCodeSpace; i != YSI_g_sCodeEnd; i += 4)
		AMX_Write(i, _:nop);
	return 0; // Make the compiler happy.
}

#if defined CGen_OnCodeInit
	forward CGen_OnCodeInit();
#endif
#if defined _ALS_OnCodeInit
	#undef OnCodeInit
#else
	#define _ALS_OnCodeInit
#endif
#define OnCodeInit CGen_OnCodeInit

stock CGen_UseCodeSpace(ctx[AsmContext])
{
	AsmInitPtr(ctx, YSI_g_sCodeSpace, YSI_g_sCodeEnd - YSI_g_sCodeSpace);
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

#undef _CODE_2
#undef _CODE_1

