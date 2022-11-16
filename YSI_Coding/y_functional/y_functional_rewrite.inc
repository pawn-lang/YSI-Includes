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
	Gamer_Z - GPS.`
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

/// <p/>

static stock
	/**
	 * <library>y_functional</library>
	 */
	YSI_g_sFunctionalLastEnd = cellmin,
	/**
	 * <library>y_functional</library>
	 */
	YSI_g_sFunctionalExpectedDepth = 0,
	/**
	 * <library>y_functional</library>
	 */
	YSI_g_sFunctionalStartPos = 0,
	/**
	 * <library>y_functional</library>
	 */
	YSI_g_sFunctionalEndPos = 0,
	/**
	 * <library>y_functional</library>
	 */
	YSI_g_sFunctionalAfterPos = 0;

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <remarks>
 *   Placeholder function used to deonte the start of lambda code.  All
 *   parameters are dummies, used for code scanning and generation space
 *   padding.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock LAM@1(idx = 0, pattern0 = 1, pattern1 = 1, pattern2 = 1, pattern3 = 1)
{
	#pragma unused idx, pattern0, pattern1, pattern2, pattern3
}
#define CALL@LAM@1%8() LAM@1%8(1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <remarks>
 *   Placeholder function used to deonte the end of lambda code.  The parameter
 *   is eventually used in the rewitten code to return the result.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock LAM@2(par)
{
	#pragma unused par
}
#define CALL@LAM@2%8() LAM@2%8(1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="idx">Used by nested lambda calls.</param>
 * <remarks>
 *   Marks the point in code where the lambda function gets called.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock LAM@0(idx = 0)
{
	#pragma unused idx
	return 0;
}
#define CALL@LAM@0%8() LAM@0%8(1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <remarks>
 *   The end of all the generated code; functions and calls.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock LAM@5(idx = 0, pattern0 = 1, pattern1 = 1, pattern2 = 1, pattern3 = 1, pattern4 = 1, pattern5 = 1, pattern6 = 1)
{
	#pragma unused idx, pattern0, pattern1, pattern2, pattern3, pattern4, pattern5, pattern6
	return 0;
}
#define CALL@LAM@5%8() LAM@5%8(1)

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="scanner">The code scanner that found a match.</param>
 * <remarks>
 *   Called when a scanner matches a <c>LAM@1()</c> call, denoting the start of
 *   a lambda function.  Just removes the call and stores the location.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Functional_FoundStart(const scanner[CodeScanner])
{
	if (YSI_g_sFunctionalStartPos != 0)
		return -1;
	Debug_Print4("Functional_FoundStart called");
	YSI_g_sFunctionalStartPos = CodeScanGetMatchAddressData(scanner);
	// NOP the call out.
	CodeScanNOPMatch(scanner);
	Debug_Print5("Functional_FoundStart done");
	if (YSI_g_sFunctionalExpectedDepth < 0)
	{
		YSI_g_sFunctionalExpectedDepth = CodeScanGetMatchStack(scanner);
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="scanner">The code scanner that found a match.</param>
 * <remarks>
 *   Called when a scanner matches a <c>LAM@2()</c> call, denoting the end of a
 *   lambda function.  Just removes the call and stores the location.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Functional_FoundEnd(const scanner[CodeScanner])
{
	// This must always immediately follow the corresponding `LAM@1`, so if we haven't seen the
	// correct one yet, don't do anything.
	if (YSI_g_sFunctionalStartPos == 0)
		return -1;
	if (YSI_g_sFunctionalEndPos != 0)
		return -1;
	Debug_Print4("Functional_FoundEnd called");
	YSI_g_sFunctionalEndPos = CodeScanGetMatchAddressData(scanner);
	CodeScanNOPMatch(scanner);
	Debug_Print5("Functional_FoundEnd done");
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="scanner">The code scanner that found a match.</param>
 * <remarks>
 *   Called when a scanner matches a <c>LAM@5()</c> call, denoting the end of
 *   the lambda call.  Just removes the call and stores the location.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Functional_FoundAfter(const scanner[CodeScanner])
{
	if (YSI_g_sFunctionalAfterPos != 0)
		return -1;
	Debug_Print4("Functional_FoundAfter called");
	YSI_g_sFunctionalAfterPos = CodeScanGetMatchAddressData(scanner);
	CodeScanNOPMatch(scanner);
	Debug_Print5("Functional_FoundAfter done");
	// Immediately end the scanner.
	if (YSI_g_sFunctionalAfterPos > YSI_g_sFunctionalLastEnd)
		YSI_g_sFunctionalLastEnd = YSI_g_sFunctionalAfterPos;
	return cellmin;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="scanner">The code scanner that found a match.</param>
 * <remarks>
 *   Used when a matcher finds a lambda call with an explicit nesting level.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Functional_FoundCall1(const scanner[CodeScanner])
{
	Functional_FoundCall(scanner, CodeScanGetMatchHole(scanner, 0));
}

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="scanner">The code scanner that found a match.</param>
 * <remarks>
 *   Used when a matcher finds a lambda call with a ZERO op for the nesting
 *   level.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Functional_FoundCall2(const scanner[CodeScanner])
{
	Functional_FoundCall(scanner, 0);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <param name="scanner">The code scanner that found a match.</param>
 * <param name="nestingLevel">How many lambdas deep this call is.</param>
 * <remarks>
 *   Once a lambda call is found this code is called to trigger a new set of
 *   scans to analyse the lambda function itself.  It then does the code
 *   generation based on the results.  This is to allow nested lambdas as the
 *   calls are found first, then the second set of scans run without preventing
 *   the call scanner from finding more results later.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Functional_FoundCall(const scanner[CodeScanner], nestingLevel)
{
	Debug_Print4("Functional_FoundCall called: %d", nestingLevel);
	
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
		OP(PUSH_C,             1)
		OP(PUSH_C,             1)
		OP(PUSH_C,             nestingLevel)
		OP(PUSH_C,             __5_cells)
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
		OP(CONST_PRI,          1)
		OP(PUSH_PRI)
		OP(CONST_PRI,          1)
		OP(PUSH_PRI)
		OP(CONST_PRI,          nestingLevel)
		OP(PUSH_PRI)
		OP(PUSH_C,             __5_cells)
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
			OP(CONST_PRI,          1)
			OP(PUSH_PRI)
			OP(CONST_PRI,          1)
			OP(PUSH_PRI)
			OP(ZERO_PRI)
			OP(PUSH_PRI)
			OP(PUSH_C,             __5_cells)
			OP(CALL,               &LAM@1)
		);
		CodeScanAddMatcher(second, lambdaStart2);
	}

#if __COMPILER_O2
	new lambdaStart3[CodeScanMatcher];
	CodeScanMatcherInit(lambdaStart3, &Functional_FoundStart);
	CodeScanMatcherPattern(lambdaStart3,
		OP(PUSH5_C,            1, 1, 1, 1, nestingLevel)
		OP(PUSH_C,             __5_cells)
		OP(CALL,               &LAM@1)
	);
	CodeScanAddMatcher(second, lambdaStart3);
#endif

	new lambdaEnd[CodeScanMatcher];
	CodeScanMatcherInit(lambdaEnd, &Functional_FoundEnd);
	CodeScanMatcherPattern(lambdaEnd,
		OP(PUSH_PRI)
		OP(PUSH_C,             __1_cell)
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
		OP(PUSH_C,             1)
		OP(PUSH_C,             1)
		OP(PUSH_C,             1)
		OP(PUSH_C,             nestingLevel)
		OP(PUSH_C,             __8_cells)
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
		OP(CONST_PRI,          1)
		OP(PUSH_PRI)
		OP(CONST_PRI,          1)
		OP(PUSH_PRI)
		OP(CONST_PRI,          1)
		OP(PUSH_PRI)
		OP(CONST_PRI,          nestingLevel)
		OP(PUSH_PRI)
		OP(PUSH_C,             __8_cells)
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
			OP(CONST_PRI,          1)
			OP(PUSH_PRI)
			OP(CONST_PRI,          1)
			OP(PUSH_PRI)
			OP(CONST_PRI,          1)
			OP(PUSH_PRI)
			OP(ZERO_PRI)
			OP(PUSH_PRI)
			OP(PUSH_C,             __8_cells)
			OP(CALL,               &LAM@5)
		);
		CodeScanAddMatcher(second, lambdaAfter2);
	}
	
#if __COMPILER_O2
	new lambdaAfter3[CodeScanMatcher];
	CodeScanMatcherInit(lambdaAfter3, &Functional_FoundAfter);
	CodeScanMatcherPattern(lambdaAfter3,
		OP(PUSH5_C,            1, 1, 1, 1, 1)
		OP(PUSH3_C,            1, 1, nestingLevel)
		OP(PUSH_C,             __8_cells)
		OP(CALL,               &LAM@5)
	);
	CodeScanAddMatcher(second, lambdaAfter3);
#endif

	YSI_g_sFunctionalStartPos = 0;
	YSI_g_sFunctionalEndPos = 0;
	YSI_g_sFunctionalAfterPos = 0;
	CodeScanRun(second);
	
	// We now have three bits of data - the call position (`callPos`), the start of the lambda code
	// (`YSI_g_sFunctionalStartPos`), and the end of the lambda code (`YSI_g_sFunctionalEndPos`).
	// Turn `callPos` in to a jump to `YSI_g_sFunctionalStartPos + 8`, `YSI_g_sFunctionalEndPos` in
	// to a jump back to `callPos + 8`, and `YSI_g_sFunctionalStartPos` in to a jump to
	// `YSI_g_sFunctionalAfterPos`.
	
	Debug_Print5("Functional_FoundCall: generating %d %d %d %d", callPos, YSI_g_sFunctionalStartPos, YSI_g_sFunctionalEndPos, YSI_g_sFunctionalAfterPos);
	new
		ctx[AsmContext],
		excess = CodeScanGetMatchStack(scanner) - YSI_g_sFunctionalExpectedDepth;
	AsmInitPtr(ctx, callPos, __4_cells);
	// The relative jumps are all `+ 8` internally, since they add on the size of the `JUMP` OP.
	@emit JUMP.rel         (YSI_g_sFunctionalStartPos - callPos)
	@emit LOAD.pri         AMX_Ref(I@)
	//@emit PUSH.C           -YSI_g_sFunctionalExpectedDepth
	//@emit CALL             0
	
	AsmInitPtr(ctx, YSI_g_sFunctionalEndPos, __2_cells);
	@emit STOR.pri         AMX_Ref(I@)
	
	AsmInitPtr(ctx, YSI_g_sFunctionalStartPos, __10_cells);
	if (excess)
	{
		@emit JUMP.rel         (YSI_g_sFunctionalAfterPos + __12_cells - YSI_g_sFunctionalStartPos)
		
		// Dump this bit of excess stack to the heap.
		@emit HEAP             excess
		@emit LCTRL            __stk
		@emit MOVS             excess
		@emit STACK            excess
	}
	else
	{
		@emit JUMP.rel         (YSI_g_sFunctionalAfterPos - YSI_g_sFunctionalStartPos)
	}
	//@emit PUSH.C           YSI_g_sFunctionalExpectedDepth
	//@emit CALL             0
	
	AsmInitPtr(ctx, YSI_g_sFunctionalAfterPos, __14_cells);
	if (excess)
	{
		// Dump this bit of excess stack to the heap.
		@emit STACK            -excess
		@emit STACK            0
		@emit LCTRL            __hea
		@emit ADD.C            -excess
		@emit MOVS             excess
		@emit SCTRL            __hea
		
		@emit JUMP.rel         (callPos - YSI_g_sFunctionalAfterPos - __12_cells)
	}
	else
	{
		@emit JUMP.rel         (callPos - YSI_g_sFunctionalAfterPos)
	}
	
	// Code was written - rescan the whole function.
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_functional</library>
 * <remarks>
 *   Initialise the system
 * </remarks>
 *//*------------------------------------------------------------------------**/

public OnCodeInit()
{
	Debug_Print2("Functional_OnCodeInit called");
	{
		// Look for any calls to `LAM@0`, then find the next call to `LAM@1`
		// with a matching parameter number (the exact value is unimportant;
		// however, for now we know that it is always `<= 0`, so if the
		// parameter is `> 0` ignore it - it's the code scanner itself).  Get
		// rid of all the calls and change them in to jumps to each other.
		
		new scanner[CodeScanner];
		CodeScanInit(scanner);
		
		new lambdaCall0[CodeScanMatcher];
		CodeScanMatcherInit(lambdaCall0, &Functional_FoundCall1);
		CodeScanMatcherPattern(lambdaCall0,
			OP(PUSH_C,             ???)
			OP(PUSH_C,             __1_cell)
			OP(CALL,               &LAM@0)
		);
		CodeScanAddMatcher(scanner, lambdaCall0);
		
		new lambdaCall1[CodeScanMatcher];
		CodeScanMatcherInit(lambdaCall1, &Functional_FoundCall1);
		CodeScanMatcherPattern(lambdaCall1,
			OP(CONST_PRI,          ???)
			OP(PUSH_PRI)
			OP(PUSH_C,             __1_cell)
			OP(CALL,               &LAM@0)
		);
		CodeScanAddMatcher(scanner, lambdaCall1);
		
		new lambdaCall2[CodeScanMatcher];
		CodeScanMatcherInit(lambdaCall2, &Functional_FoundCall2);
		CodeScanMatcherPattern(lambdaCall2,
			OP(ZERO_PRI)
			OP(PUSH_PRI)
			OP(PUSH_C,             __1_cell)
			OP(CALL,               &LAM@0)
		);
		CodeScanAddMatcher(scanner, lambdaCall2);
		
		// Run fast, with an explicit search function.
		CodeScanRunFast(scanner, &LAM@0);
	}

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

#if 0

// The original code is:

myVar = FoldR({ _0 + _1 }, arr, 0);

// The compiled code generated is:

myVar = LAM@0();
{
	LAM@1();
	inline Func(_0, _1) @return _0 + _1;
	LAM@2(FoldR("Func", arr, 0));
}

// The rewritten code is:

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

// This jumping about is done so that lambdas may be used in the middle of expressions.

#endif

