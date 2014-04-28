static stock
	YSI_g_sNextJumpPoint;

stock LAM@1()
{
	//printf("LAM@1");
	static
		addrLAM@1 = 0;
	if (!addrLAM@1)
	{
		#emit CONST.pri  LAM@1
		#emit STOR.pri   addrLAM@1
		addrLAM@1 += AMX_REAL_DATA + AMX_HEADER_COD;
		P:5("LAM@1: LAM@1 addresses = %d %d %d %d", GetAmxBaseAddress(), addrLAM@1 - (AMX_REAL_DATA + AMX_HEADER_COD), AMX_REAL_DATA + AMX_HEADER_COD, addrLAM@1);
		//printf("LAM@0: LAM@1 addresses = %d %d %d %d", GetAmxBaseAddress(), addrLAM@1 - (AMX_REAL_DATA + AMX_HEADER_COD), AMX_REAL_DATA + AMX_HEADER_COD, addrLAM@1);
	}
	// Rewrite our call code to jump to "YSI_g_sNextJumpPoint".  Then adjust
	// that to our return point, and jump to the new code.
	new
		addrRet = GetCurrentFrameReturn(),
		addrNext = YSI_g_sNextJumpPoint;
	SetCurrentFrameReturn(addrNext);
	YSI_g_sNextJumpPoint = addrRet,
	addrRet -= 16;
	{
		new
			dis[DisasmContext];
		DisasmInit(dis, addrRet);
		if (DisasmNextInsn(dis) != OP_PUSH_C || DisasmGetOperand(dis) != 0 ||
		    DisasmNextInsn(dis) != OP_CALL   || DisasmGetOperand(dis) != addrLAM@1)
		{
			P:E("Unknown call of LAM@1");
			return 0;
		}
	}
	{
		new
			ctx[AsmContext];
		AsmInitPtr(ctx, addrRet + AMX_HEADER_COD, 16);
		// Replace with a jump to a point after "@LAM@1".
		@emit JUMP  (addrNext + AMX_REAL_DATA + AMX_HEADER_COD)
		// Code to POP the result.
		@emit NOP
		@emit NOP
	}
	return 1;
}

stock LAM@2(par)
{
	//printf("LAM@2");
	#pragma unused par
	static
		addrLAM@2 = 0;
	if (!addrLAM@2)
	{
		#emit CONST.pri  LAM@2
		#emit STOR.pri   addrLAM@2
		addrLAM@2 += AMX_REAL_DATA + AMX_HEADER_COD;
		P:5("LAM@2: LAM@2 addresses = %d %d %d %d", GetAmxBaseAddress(), addrLAM@2 - (AMX_REAL_DATA + AMX_HEADER_COD), AMX_REAL_DATA + AMX_HEADER_COD, addrLAM@2);
		//printf("LAM@0: LAM@1 addresses = %d %d %d %d", GetAmxBaseAddress(), addrLAM@2 - (AMX_REAL_DATA + AMX_HEADER_COD), AMX_REAL_DATA + AMX_HEADER_COD, addrLAM@2);
	}
	// Rewrite our call code to jump to "YSI_g_sNextJumpPoint".  Then adjust
	// that to our return point, and jump to the new code.
	new
		addrRet = GetCurrentFrameReturn(),
		addrNext = YSI_g_sNextJumpPoint;
	SetCurrentFrameReturn(addrNext);
	YSI_g_sNextJumpPoint = addrRet,
	addrRet -= 16;
	{
		new
			dis[DisasmContext];
		
		DisasmInit(dis, addrRet);
		if (DisasmNextInsn(dis) != OP_PUSH_C || DisasmGetOperand(dis) != 4 ||
		    DisasmNextInsn(dis) != OP_CALL   || DisasmGetOperand(dis) != addrLAM@2)
		{
			P:E("Unknown call of LAM@2");
			return 0;
		}
	}
	{
		new
			ctx[AsmContext];
		AsmInitPtr(ctx, addrRet + AMX_HEADER_COD, 16);
		// Replace with a jump to a point after "LAM@0".
		@emit JUMP  (addrNext - 4 + AMX_REAL_DATA + AMX_HEADER_COD)
		// Code to POP the result.
		@emit NOP
		@emit NOP
	}
	return par;
}

stock LAM@0()
{
	static
		addrLAM@0 = 0,
		addrLAM@1 = 0;
	if (!addrLAM@1)
	{
		#emit CONST.pri  LAM@0
		#emit STOR.pri   addrLAM@0
		addrLAM@0 += AMX_REAL_DATA + AMX_HEADER_COD;
		P:5("LAM@0: LAM@0 addresses = %d %d %d %d", GetAmxBaseAddress(), addrLAM@0 - (AMX_REAL_DATA + AMX_HEADER_COD), AMX_REAL_DATA + AMX_HEADER_COD, addrLAM@0);
		//printf("LAM@0: LAM@0 addresses = %d %d %d %d", GetAmxBaseAddress(), addrLAM@0 - (AMX_REAL_DATA + AMX_HEADER_COD), AMX_REAL_DATA + AMX_HEADER_COD, addrLAM@0);
		#emit CONST.pri  LAM@1
		#emit STOR.pri   addrLAM@1
		addrLAM@1 += AMX_REAL_DATA + AMX_HEADER_COD;
		P:5("LAM@0: LAM@1 addresses = %d %d %d %d", GetAmxBaseAddress(), addrLAM@1 - (AMX_REAL_DATA + AMX_HEADER_COD), AMX_REAL_DATA + AMX_HEADER_COD, addrLAM@1);
		//printf("LAM@0: LAM@1 addresses = %d %d %d %d", GetAmxBaseAddress(), addrLAM@1 - (AMX_REAL_DATA + AMX_HEADER_COD), AMX_REAL_DATA + AMX_HEADER_COD, addrLAM@1);
	}
	// Get the return address.
	new
		addrRet = GetCurrentFrameReturn(),
		addrNext;
	
	YSI_g_sNextJumpPoint = addrRet,
	addrRet -= 16,
	SetCurrentFrameReturn(addrRet);
	{
		new
			dis[DisasmContext];
		// Move on until we find the next call to "@LAM@1".
		DisasmInit(dis, YSI_g_sNextJumpPoint);
		new
			Opcode:nxt = DisasmNextInsn(dis),
			i = 0;
		while (i != 100)
		{
			if (nxt == OP_PUSH_C && DisasmGetOperand(dis) == 0)
			{
				nxt = DisasmNextInsn(dis);
				if (nxt == OP_CALL && DisasmGetOperand(dis) == addrLAM@1)
				{
					P:6("LAM@0: Found %d", DisasmGetOperand(dis));
					break;
				}
			}
			else nxt = DisasmNextInsn(dis);
			++i;
		}
		if (i == 10)
		{
			P:E("Unable to find LAM@1");
			return 0;
		}
		addrNext = DisasmGetNextIp(dis) + AMX_REAL_DATA; // - AMX_HEADER_COD; //(AMX_REAL_DATA + AMX_HEADER_COD);
		// Go backwards to before this function was called.
		DisasmInit(dis, addrRet);
		if (DisasmNextInsn(dis) != OP_PUSH_C || DisasmGetOperand(dis) != 0 ||
		    DisasmNextInsn(dis) != OP_CALL   || DisasmGetOperand(dis) != addrLAM@0)
		{
			P:E("Unknown call of LAM@0");
			return 0;
		}
	}
	{
		new
			ctx[AsmContext];
		AsmInitPtr(ctx, addrRet + AMX_HEADER_COD, 16);
		// Replace with a jump to a point after "@LAM@1".
		@emit JUMP  addrNext
		// Code to POP the result.
		@emit NOP
		@emit POP.pri
	}
	return 1;
}

/*

- The original code is:

myVar = FoldR({ _0 + _1 }, arr, 0);

- The compiled code generated is:

myVar = @LAM0();
@LAM1();
inline Func(_0, _1) YSI_gInlineRet += _0 + _1;
@LAM2(FoldR("Func", arr, 0));

- The rewritten code is:

goto Func:

:Write
myVar = I@;
goto Cont;

:Func
// Inline code.
I@ = FoldR("Func", arr, 0);
goto Write;

:Cont

*/

