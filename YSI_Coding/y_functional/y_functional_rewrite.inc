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

static stock
	YSI_g_sFunctionalLastEnd = cellmin,
	YSI_g_sFunctionalExpectedDepth = 0,
	YSI_g_sFunctionalStartPos = 0,
	YSI_g_sFunctionalEndPos = 0,
	YSI_g_sFunctionalAfterPos = 0;

//static stock Functional_AddToStack()
//{
//	// Is this the first of a nested set of lambda calls?
//	// Get the desired stack size.  This is passed as the parameter count, not as a real parameter,
//	// to save instruction space.  So extract that.
//	new
//		size;
//		
//	#emit LOAD.S.pri       8
//	#emit STOR.S.pri       size
//	
//	
//	// Now when we return, we want to remove a lot of stuff from the stack - all the extra data that
//	// we just backed up to the heap.  To do this, we increase the parameter count to match the size
//	// of the data to drop, then return.
//	#emit ZERO.pri
//	#emit STOR.S.pri       8
//	
//	#emit RETN
//	return 0;
//}

stock LAM@1(idx = 0, pattern0 = 1, pattern1 = 1)
{
	#pragma unused idx, pattern0, pattern1
}
#define CALL@LAM@1 LAM@1(1)

stock LAM@2(par)
{
	#pragma unused par
}
#define CALL@LAM@2 LAM@2(1)

stock LAM@0(idx = 0)
{
	#pragma unused idx
	return 0;
}
#define CALL@LAM@0 LAM@0(1)

stock LAM@5(idx = 0, pattern0 = 1, pattern1 = 1, pattern2 = 1, pattern3 = 1)
{
	#pragma unused idx, pattern0, pattern1, pattern2, pattern3
	return 0;
}
#define CALL@LAM@5 LAM@5(1)

static stock Functional_FoundStart(const scanner[CodeScanner])
{
	if (YSI_g_sFunctionalStartPos != 0)
		return -1;
	P:4("Functional_FoundStart called");
	YSI_g_sFunctionalStartPos = CodeScanGetMatchAddressData(scanner);
	// NOP the call out.
	CodeScanNOPMatch(scanner);
	P:5("Functional_FoundStart done");
	if (YSI_g_sFunctionalExpectedDepth < 0)
	{
		YSI_g_sFunctionalExpectedDepth = CodeScanGetMatchStack(scanner);
	}
	return 0;
}

static stock Functional_FoundEnd(const scanner[CodeScanner])
{
	// This must always immediately follow the corresponding `LAM@1`, so if we haven't seen the
	// correct one yet, don't do anything.
	if (YSI_g_sFunctionalStartPos == 0)
		return -1;
	if (YSI_g_sFunctionalEndPos != 0)
		return -1;
	P:4("Functional_FoundEnd called");
	YSI_g_sFunctionalEndPos = CodeScanGetMatchAddressData(scanner);
	CodeScanNOPMatch(scanner);
	P:5("Functional_FoundEnd done");
	return 0;
}

static stock Functional_FoundAfter(const scanner[CodeScanner])
{
	if (YSI_g_sFunctionalAfterPos != 0)
		return -1;
	P:4("Functional_FoundAfter called");
	YSI_g_sFunctionalAfterPos = CodeScanGetMatchAddressData(scanner);
	CodeScanNOPMatch(scanner);
	P:5("Functional_FoundAfter done");
	// Immediately end the scanner.
	if (YSI_g_sFunctionalAfterPos > YSI_g_sFunctionalLastEnd)
		YSI_g_sFunctionalLastEnd = YSI_g_sFunctionalAfterPos;
	return cellmin;
}

static stock Functional_FoundCall1(const scanner[CodeScanner])
{
	Functional_FoundCall(scanner, CodeScanGetMatchHole(scanner, 0));
}
static stock Functional_FoundCall2(const scanner[CodeScanner])
{
	Functional_FoundCall(scanner, 0);
}

static stock Functional_FoundCall(const scanner[CodeScanner], nestingLevel)
{
	P:4("Functional_FoundCall called: %d", nestingLevel);
	
	// Found the code scanner itself - ignore this one.
	if (nestingLevel > 0)
	{
		return -1;
	}
	
	new
		callPos = CodeScanGetMatchAddressData(scanner);
	CodeScanNOPMatch(scanner);
	if (callPos > YSI_g_sFunctionalLastEnd)
	{
		YSI_g_sFunctionalExpectedDepth = -1;
	}
	
	// Start a new scanner at the point this scanner ended.
	new
		second[CodeScanner];
	CodeScanClone(second, scanner);
	
	new lambdaStart0[CodeScanMatcher];
	CodeScanMatcherInit(lambdaStart0, &Functional_FoundStart);
	CodeScanMatcherPattern(lambdaStart0,
		OP(PUSH_C,             1)
		OP(PUSH_C,             1)
		OP(PUSH_C,             nestingLevel)
		OP(PUSH_C,             12)
		OP(CALL,               &LAM@1)
	);
	CodeScanAddMatcher(second, lambdaStart0);
	
	new lambdaStart1[CodeScanMatcher];
	CodeScanMatcherInit(lambdaStart1, &Functional_FoundStart);
	CodeScanMatcherPattern(lambdaStart1,
		OP(CONST_PRI,          1)
		OP(PUSH_PRI)
		OP(CONST_PRI,          1)
		OP(PUSH_PRI)
		OP(CONST_PRI,          nestingLevel)
		OP(PUSH_PRI)
		OP(PUSH_C,             12)
		OP(CALL,               &LAM@1)
	);
	CodeScanAddMatcher(second, lambdaStart1);
	
	// Needs to stay in scope.
	new lambdaStart2[CodeScanMatcher];
	if (nestingLevel == 0)
	{
		CodeScanMatcherInit(lambdaStart2, &Functional_FoundStart);
		CodeScanMatcherPattern(lambdaStart2,
			OP(CONST_PRI,          1)
			OP(PUSH_PRI)
			OP(CONST_PRI,          1)
			OP(PUSH_PRI)
			OP(ZERO_PRI)
			OP(PUSH_PRI)
			OP(PUSH_C,             12)
			OP(CALL,               &LAM@1)
		);
		CodeScanAddMatcher(second, lambdaStart2);
	}
	
	new lambdaEnd[CodeScanMatcher];
	CodeScanMatcherInit(lambdaEnd, &Functional_FoundEnd);
	CodeScanMatcherPattern(lambdaEnd,
		OP(PUSH_PRI)
		OP(PUSH_C,             4)
		OP(CALL,               &LAM@2)
	);
	CodeScanAddMatcher(second, lambdaEnd);
	
	new lambdaAfter0[CodeScanMatcher];
	CodeScanMatcherInit(lambdaAfter0, &Functional_FoundAfter);
	CodeScanMatcherPattern(lambdaAfter0,
		OP(PUSH_C,             1)
		OP(PUSH_C,             1)
		OP(PUSH_C,             1)
		OP(PUSH_C,             1)
		OP(PUSH_C,             nestingLevel)
		OP(PUSH_C,             20)
		OP(CALL,               &LAM@5)
	);
	CodeScanAddMatcher(second, lambdaAfter0);
	
	new lambdaAfter1[CodeScanMatcher];
	CodeScanMatcherInit(lambdaAfter1, &Functional_FoundAfter);
	CodeScanMatcherPattern(lambdaAfter1,
		OP(CONST_PRI,          1)
		OP(PUSH_PRI)
		OP(CONST_PRI,          1)
		OP(PUSH_PRI)
		OP(CONST_PRI,          1)
		OP(PUSH_PRI)
		OP(CONST_PRI,          1)
		OP(PUSH_PRI)
		OP(CONST_PRI,          nestingLevel)
		OP(PUSH_PRI)
		OP(PUSH_C,             20)
		OP(CALL,               &LAM@5)
	);
	CodeScanAddMatcher(second, lambdaAfter1);
	
	new lambdaAfter2[CodeScanMatcher];
	if (nestingLevel == 0)
	{
		CodeScanMatcherInit(lambdaAfter2, &Functional_FoundAfter);
		CodeScanMatcherPattern(lambdaAfter2,
			OP(CONST_PRI,          1)
			OP(PUSH_PRI)
			OP(CONST_PRI,          1)
			OP(PUSH_PRI)
			OP(CONST_PRI,          1)
			OP(PUSH_PRI)
			OP(CONST_PRI,          1)
			OP(PUSH_PRI)
			OP(ZERO_PRI)
			OP(PUSH_PRI)
			OP(PUSH_C,             20)
			OP(CALL,               &LAM@5)
		);
		CodeScanAddMatcher(second, lambdaAfter2);
	}
	
	YSI_g_sFunctionalStartPos = 0;
	YSI_g_sFunctionalEndPos = 0;
	YSI_g_sFunctionalAfterPos = 0;
	CodeScanRun(second);
	
	// We now have three bits of data - the call position (`callPos`), the start of the lambda code
	// (`YSI_g_sFunctionalStartPos`), and the end of the lambda code (`YSI_g_sFunctionalEndPos`).
	// Turn `callPos` in to a jump to `YSI_g_sFunctionalStartPos + 8`, `YSI_g_sFunctionalEndPos` in
	// to a jump back to `callPos + 8`, and `YSI_g_sFunctionalStartPos` in to a jump to
	// `YSI_g_sFunctionalAfterPos`.
	
	P:5("Functional_FoundCall: generating %d %d %d %d", callPos, YSI_g_sFunctionalStartPos, YSI_g_sFunctionalEndPos, YSI_g_sFunctionalAfterPos);
	new
		ctx[AsmContext],
		excess = CodeScanGetMatchStack(scanner) - YSI_g_sFunctionalExpectedDepth;
	AsmInitPtr(ctx, callPos, 16);
	// The relative jumps are all `+ 8` internally, since they add on the size of the `JUMP` OP.
	@emit JUMP.rel         (YSI_g_sFunctionalStartPos - callPos)
	@emit LOAD.pri         ref(I@)
	//@emit PUSH.C           -YSI_g_sFunctionalExpectedDepth
	//@emit CALL             0
	
	AsmInitPtr(ctx, YSI_g_sFunctionalEndPos, 8);
	@emit STOR.pri         ref(I@)
	
	AsmInitPtr(ctx, YSI_g_sFunctionalStartPos, 40);
	if (excess)
	{
		@emit JUMP.rel         (YSI_g_sFunctionalAfterPos + 48 - YSI_g_sFunctionalStartPos)
		
		// Dump this bit of excess stack to the heap.
		@emit HEAP             excess
		@emit LCTRL            4
		@emit MOVS             excess
		@emit STACK            excess
	}
	else
	{
		@emit JUMP.rel         (YSI_g_sFunctionalAfterPos - YSI_g_sFunctionalStartPos)
	}
	//@emit PUSH.C           YSI_g_sFunctionalExpectedDepth
	//@emit CALL             0
	
	AsmInitPtr(ctx, YSI_g_sFunctionalAfterPos, 56);
	if (excess)
	{
		// Dump this bit of excess stack to the heap.
		@emit STACK            -excess
		@emit STACK            0
		@emit LCTRL            2
		@emit ADD.C            -excess
		@emit MOVS             excess
		@emit SCTRL            2
		
		@emit JUMP.rel         (callPos - YSI_g_sFunctionalAfterPos - 48)
	}
	else
	{
		@emit JUMP.rel         (callPos - YSI_g_sFunctionalAfterPos)
	}
	
	// Code was written - rescan the whole function.
	return 1;
}

public OnCodeInit()
{
	P:2("Functional_OnCodeInit called");
	// Look for any calls to `LAM@0`, then find the next call to `LAM@1` with a matching parameter
	// number (the exact value is unimportant; however, for now we know that it is always `<= 0`, so
	// if the parameter is `> 0` ignore it - it's the code scanner itself).  Get rid of all the
	// calls and change them in to jumps to each other.
	
	new scanner[CodeScanner];
	CodeScanInit(scanner);
	
	new lambdaCall0[CodeScanMatcher];
	CodeScanMatcherInit(lambdaCall0, &Functional_FoundCall1);
	CodeScanMatcherPattern(lambdaCall0,
		OP(PUSH_C,             ???)
		OP(PUSH_C,             4)
		OP(CALL,               &LAM@0)
	);
	CodeScanAddMatcher(scanner, lambdaCall0);
	
	new lambdaCall1[CodeScanMatcher];
	CodeScanMatcherInit(lambdaCall1, &Functional_FoundCall1);
	CodeScanMatcherPattern(lambdaCall1,
		OP(CONST_PRI,          ???)
		OP(PUSH_PRI)
		OP(PUSH_C,             4)
		OP(CALL,               &LAM@0)
	);
	CodeScanAddMatcher(scanner, lambdaCall1);
	
	new lambdaCall2[CodeScanMatcher];
	CodeScanMatcherInit(lambdaCall2, &Functional_FoundCall2);
	CodeScanMatcherPattern(lambdaCall2,
		OP(ZERO_PRI)
		OP(PUSH_PRI)
		OP(PUSH_C,             4)
		OP(CALL,               &LAM@0)
	);
	CodeScanAddMatcher(scanner, lambdaCall2);
	
	// Run fast, with an explicit search function.
	CodeScanRunFast(scanner, &LAM@0);
	
	#if defined Functional_OnCodeInit
		Functional_OnCodeInit();
	#endif
	return 1;
}

#undef OnCodeInit
#define OnCodeInit Functional_OnCodeInit
#if defined Functional_OnCodeInit
	forward Functional_OnCodeInit();
#endif

/*

- The original code is:

myVar = FoldR({ _0 + _1 }, arr, 0);

- The compiled code generated is:

myVar = @LAM0();
{
	@LAM1();
	inline Func(_0, _1) @return _0 + _1;
	@LAM2(FoldR("Func", arr, 0));
}

- The rewritten code is:

goto Func:

:Write
myVar = I@;
goto Cont;

{
	:Func
	inline Func(_0, _1) @return _0 + _1;
	I@ = FoldR("Func", arr, 0);
	goto Write;
}

:Cont

This jumping about is done so that lambdas may be used in the middle of expressions.

*/

