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
	YSI_g_sFunctionalStartPos,
	YSI_g_sFunctionalEndPos;

stock LAM@1(idx = 0)
{
	#pragma unused idx
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

static stock Functional_FoundStart(scanner[CodeScanner])
{
	YSI_g_sFunctionalStartPos = CodeScanGetMatchAddressData(scanner);
	// NOP the call out.
	CodeScanNOPMatch(scanner);
	return 0;
}

static stock Functional_FoundEnd(scanner[CodeScanner])
{
	// This must always immediately follow the corresponding `LAM@1`, so if we haven't seen the
	// correct one yet, don't do anything.
	if (YSI_g_sFunctionalStartPos == 0)
		return -1;
	YSI_g_sFunctionalEndPos = CodeScanGetMatchAddressData(scanner);
	// Immediately end the scanner.
	CodeScanNOPMatch(scanner);
	return cellmin;
}

static stock Functional_FoundCall(scanner[CodeScanner])
{
	new
		nestingLevel = CodeScanGetMatchHole(scanner, 0);
	// Found the code scanner itself - ignore this one.
	if (nestingLevel > 0)
		return -1;
	
	// Start a new scanner at the point this scanner ended.
	new
		second[CodeScanner]
	CodeScanClone(second, scanner);
	
	new lambdaStart0[CodeScanMatcher];
	CodeScanMatcherInit(lambdaStart0, &Functional_FoundStart);
	CodeScanMatcherPattern(lambdaStart0,
		OP(PUSH_C,             nestingLevel)
		OP(PUSH_C,             4)
		OP(CALL,               &LAM@1)
	);
	CodeScanAddMatcher(second, lambdaStart0);
	
	new lambdaStart1[CodeScanMatcher];
	CodeScanMatcherInit(lambdaStart1, &Functional_FoundStart);
	CodeScanMatcherPattern(lambdaStart1,
		OP(CONST_PRI,          nestingLevel)
		OP(PUSH_PRI)
		OP(PUSH_C,             4)
		OP(CALL,               &LAM@1)
	);
	CodeScanAddMatcher(second, lambdaStart1);
	
	new lambdaEnd[CodeScanMatcher];
	CodeScanMatcherInit(lambdaEnd, &Functional_FoundEnd);
	CodeScanMatcherPattern(lambdaEnd,
		OP(PUSH_PRI)
		OP(PUSH_C,             4)
		OP(CALL,               &LAM@2)
	);
	CodeScanAddMatcher(second, lambdaEnd);
	
	YSI_g_sFunctionalStartPos = 0;
	YSI_g_sFunctionalEndPos = 0;
	CodeScanRun(second);
	
	new
		callPos = CodeScanGetMatchAddressData(scanner);
	CodeScanNOPMatch(scanner);
	// We now have three bits of data - the call position (`callPos`), the start of the lambda code
	// (`YSI_g_sFunctionalStartPos`), and the end of the lambda code (`YSI_g_sFunctionalEndPos`).
	// Turn `callPos` in to a jump to `YSI_g_sFunctionalStartPos`, and `YSI_g_sFunctionalEndPos`
	// in to a jump back to `callPos + 8`.
	
	return 0;
}

hook OnCodeInit()
{
	// Look for any calls to `LAM@0`, then find the next call to `LAM@1` with a matching parameter
	// number (the exact value is unimportant; however, for now we know that it is always `<= 0`, so
	// if the parameter is `> 0` ignore it - it's the code scanner itself).  Get rid of all the
	// calls and change them in to jumps to each other.
	
	new scanner[CodeScanner];
	CodeScanInit(scanner);
	
	new lambdaCall0[CodeScanMatcher];
	CodeScanMatcherInit(lambdaCall0, &Functional_FoundCall);
	CodeScanMatcherPattern(lambdaCall0,
		OP(PUSH_C,             ???)
		OP(PUSH_C,             4)
		OP(CALL,               &LAM@0)
	);
	CodeScanAddMatcher(scanner, lambdaCall0);
	
	new lambdaCall1[CodeScanMatcher];
	CodeScanMatcherInit(lambdaCall1, &Functional_FoundCall);
	CodeScanMatcherPattern(lambdaCall1,
		OP(CONST_PRI,          ???)
		OP(PUSH_PRI)
		OP(PUSH_C,             4)
		OP(CALL,               &LAM@0)
	);
	CodeScanAddMatcher(scanner, lambdaCall1);
	
	CodeScanRun(scanner);
}

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

