// Revert to the old scanning design, but using the new code scanner.

const INLINE_PATTERN_1 = _A<Alex>;
const INLINE_PATTERN_2 = _C<Alex>;
const INLINE_PATTERN_3 = _A<Cole>;
const INLINE_PATTERN_4 = _C<Cole>;

#define CALL@I@E I@E("", 0, 0, 0, 0)
#define CALL@I@F I@F()
#define CALL@I@L I@L()
#define CALL@I@K I@K(0)

forward Inline_FoundStart(scanner[CodeScanner]);
forward Inline_FoundMid(scanner[CodeScanner]);
forward Inline_FoundVar(scanner[CodeScanner]);
forward Inline_FoundRef(scanner[CodeScanner]);
forward Inline_FoundEnd(scanner[CodeScanner]);
forward Inline_FoundConst(scanner[CodeScanner]);

static stock
	YSI_g_sCurInlineState = 0, // Which part of the header scanning we are on.
	YSI_g_sCurInlineLocals,    // Container function locals.
	YSI_g_sCurInlinePassed,    // Inline function parameters.
	YSI_g_sCurInlineParams,    // Container function parameters (undetermined).
	YSI_g_sCurInlinePointer,   // The struct to store the inline data in.
	YSI_g_sCurInlineStart,     // The start of the code space.
	YSI_g_sCurInlineEnd,       // The end of the code space.
	YSI_g_sCurInlineLoop,      // The loopback pos if user code ends naturally.
	YSI_g_sCurInlineUser;      // The location of the user code.

public Inline_FoundStart(scanner[CodeScanner])
{
	if (YSI_g_sCurInlineState != 0)
		return 0;
	YSI_g_sCurInlineLocals = CodeScanGetMatchStack(scanner);
	YSI_g_sCurInlineParams = -1; // No way to know!
	YSI_g_sCurInlinePointer = CodeScanGetMatchHole(scanner, 0);
	YSI_g_sCurInlineStart = CodeScanGetMatchAddress(scanner);
	YSI_g_sCurInlineEnd = CodeScanGetMatchHole(scanner, 1);
	YSI_g_sCurInlineState = 1;
	return 0;
}

public Inline_FoundMid(scanner[CodeScanner])
{
	if (YSI_g_sCurInlineState != 1)
		return 0;
	YSI_g_sCurInlineLoop = CodeScanGetMatchAddress(scanner) + 6 * cellbytes;
	if (AMX_Read(YSI_g_sCurInlineLoop + AMX_HEADER_COD) == _:RelocateOpcode(OP_BREAK))
		YSI_g_sCurInlineLoop += cellbytes;
	YSI_g_sCurInlinePassed = CodeScanGetMatchStack(scanner) - YSI_g_sCurInlineLocals;
	YSI_g_sCurInlineState = 2;
	return 0;
}

static stock Inline_FoundDescriptor(scanner[CodeScanner], size)
{
	switch (size)
	{
		case 0:
		{
			// Variable.
			printf("Var");
		}
		case -1:
		{
			// Reference.
			printf("Reference");
		}
		case cellmin:
		{
			// String.
			printf("String");
		}
		default:
		{
			// Array in cells.
			printf("Array[%d]", size);
		}
	}
}

public Inline_FoundConst(scanner[CodeScanner])
{
	if (YSI_g_sCurInlineState != 2)
		return 0;
	YSI_g_sCurInlineState = 3 + CodeScanGetMatchHole(scanner, 0);
	return 0;
}

public Inline_FoundVar(scanner[CodeScanner])
{
	if (YSI_g_sCurInlineState < 3)
		return 0;
	Inline_FoundDescriptor(scanner, 0);
	return 0;
}

public Inline_FoundRef(scanner[CodeScanner])
{
	if (YSI_g_sCurInlineState < 3)
		return 0;
	Inline_FoundDescriptor(scanner, CodeScanGetMatchHole(scanner, 0));
	return 0;
}

public Inline_FoundEnd(scanner[CodeScanner])
{
	if (YSI_g_sCurInlineState < 3)
		return 0;
	YSI_g_sCurInlineUser = CodeScanGetMatchAddress(scanner) + CodeScanGetMatchLength(scanner);
	printf("End: %08x", YSI_g_sCurInlineUser);
	// Do the actual codegen here.
	Inline_DoCodeGen();
	// Restart scanning for the next inline.
	YSI_g_sCurInlineState = 0;
	return 0;
}

public OnCodeInit()
{
	new scanner[CodeScanner];
	CodeScanInit(scanner);
	
	// Optimised.
	new csm0[CodeScanMatcher];
	CodeScanMatcherInit(csm0, &Inline_FoundStart);
	CodeScanMatcherPattern(csm0,
		OP(PUSH_C, INLINE_PATTERN_4)
		OP(PUSH_C, INLINE_PATTERN_3)
		OP(PUSH_C, INLINE_PATTERN_2)
		OP(PUSH_C, INLINE_PATTERN_1)
		OP(PUSH_C, ???)
		OP(PUSH_C, 20)
		OP(CALL, &I@E)
		OP(JZER, ???)
	);
	CodeScanAddMatcher(scanner, csm0);
	
	// Unoptimised.
	new csm1[CodeScanMatcher];
	CodeScanMatcherInit(csm1, &Inline_FoundStart);
	CodeScanMatcherPattern(csm1,
		OP(CONST_PRI, INLINE_PATTERN_4)
		OP(PUSH_PRI)
		OP(CONST_PRI, INLINE_PATTERN_3)
		OP(PUSH_PRI)
		OP(CONST_PRI, INLINE_PATTERN_2)
		OP(PUSH_PRI)
		OP(CONST_PRI, INLINE_PATTERN_1)
		OP(PUSH_PRI)
		OP(CONST_PRI, ???)
		OP(PUSH_PRI)
		OP(PUSH_C, 20)
		OP(CALL, &I@E)
		OP(JZER, ???)
	);
	CodeScanAddMatcher(scanner, csm1);
	
	// Mid point.
	new csm2[CodeScanMatcher];
	CodeScanMatcherInit(csm2, &Inline_FoundMid);
	CodeScanMatcherPattern(csm2,
		OP(PUSH_C, 0)
		OP(CALL, &I@F)
		OP(JZER, ???)
	);
	CodeScanAddMatcher(scanner, csm2);
	
	// Normal parameter.
	//   
	//   ZERO.pri
	//   HEAP 4
	//   STOR.I
	//   PUSH.alt
	//   
	new csm3[CodeScanMatcher];
	CodeScanMatcherInit(csm3, &Inline_FoundVar);
	CodeScanMatcherPattern(csm3,
		OP(ZERO_PRI)
		OP(HEAP, 4)
		OP(STOR_I)
		OP(PUSH_ALT)
	);
	CodeScanAddMatcher(scanner, csm3);
	
	// Reference parameter.
	//   
	//   CONST.pri ffffffff
	//   HEAP 4
	//   STOR.I
	//   PUSH.alt
	//   
	// Array (with size in CELLS).
	//   
	//   CONST.pri a
	//   HEAP 4
	//   STOR.I
	//   PUSH.alt
	//   
	// String
	//   
	//   CONST.pri 80000000
	//   HEAP 4
	//   STOR.I
	//   PUSH.alt
	//   
	new csm4[CodeScanMatcher];
	CodeScanMatcherInit(csm4, &Inline_FoundRef);
	CodeScanMatcherPattern(csm4,
		OP(CONST_PRI, ???)
		OP(HEAP, 4)
		OP(STOR_I)
		OP(PUSH_ALT)
	);
	CodeScanAddMatcher(scanner, csm4);
	
	// End
	new csm5[CodeScanMatcher];
	CodeScanMatcherInit(csm5, &Inline_FoundEnd);
	CodeScanMatcherPattern(csm5,
		OP(CALL, &I@L)
		OP(HEAP, ???)
		OP(JZER, ???)
	);
	CodeScanAddMatcher(scanner, csm5);
	
	// Constness
	new csm6[CodeScanMatcher];
	CodeScanMatcherInit(csm6, &Inline_FoundConst);
	CodeScanMatcherPattern(csm6,
		OP(PUSH_C, ???)
		OP(PUSH_C, 4)
		OP(CALL, &I@K)
	);
	CodeScanAddMatcher(scanner, csm6);
	
	new csm7[CodeScanMatcher];
	CodeScanMatcherInit(csm7, &Inline_FoundConst);
	CodeScanMatcherPattern(csm7,
		OP(CONST_PRI, ???)
		OP(PUSH_PRI)
		OP(PUSH_C, 4)
		OP(CALL, &I@K)
	);
	CodeScanAddMatcher(scanner, csm7);
	
	// Run all the scanners in parallel.
	CodeScanRun(scanner);
	return 1;
}

#define LAMBDA_i<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0|||,0|||<%9>{%0}(%1)%8;
#define LAMBDA_ii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1|||,0,0|||<%9>{%0}(%1)%8;
#define LAMBDA_iii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1,_2|||,0,0,0|||<%9>{%0}(%1)%8;
#define LAMBDA_iiii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1,_2,_3|||,0,0,0,0|||<%9>{%0}(%1)%8;
#define LAMBDA_iiiii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1,_2,_3,_4|||,0,0,0,0,0|||<%9>{%0}(%1)%8;

#define _DO_LAMBDA|||%6|||%5|||<%9>{%0}(%1)%8; LAM@0()%8;{LAM@1();static const YSII[]="@:....";if(I@E(YSII))for(%6;I@F();)while(I@L(I@K()%5))YSI_gInlineRet+=(%0);LAM@2(%9(callback_tag:YSII%1));}

// Make sure there's a space after the "return".
#define return%0({%1}%2)%3; I@=%0({%1}%2)%3;return I@;

// The "INLINE" in the types here will override "PARSER@" to "PARSE@INLINE",
// because there is no colon (well not "because", but it helps).
#define inline%0(%1) MAKE_PARSER(INLINE,ARR:REF:STR:NUM:QAL::INLINE)(%0(%1))()0()

// Follows the "code-parse.inc" internal structure.  Ugly but required, since we
// are parsing functions, but not at a top level.
#define PARSER@INLINE:%0(%5)%6(%7)$ static %6[_:%0(%5)%6(%7) I@O$

#define INLINE_STR(%9,%9,%2,%9)%8$(%0)%1(%3) %8$(%0,%2[YSI_MAX_INLINE_STRING])%1(cellmin,%3)
#define INLINE_ARR(%9,%9,%2,%9)%8$(%0)%1(%3) %8$(%0,%2[%9])%1(%9,%3)
#define INLINE_NUM(%9,%9,%2)%8$(%0)%1(%3) %8$(%0,%2)%1(0,%3)
#define INLINE_REF(%9,%9,%2)%8$(%0)%1(%3) %8$(%0,%2)%1(-1,%3)

#define INLINE_END(%9)%8$(,%0)%1(%3) %8$#%9":....";if (I@E(%9))for(new %0;I@F();)while(I@L(%3I@K(%1)))

#define INLINE_NUL(%9)%8$()%1() %8$#%9":....";if (I@E(%9))for(;I@F();)while(I@L(I@K(%1)))

#define I@O$ 32]=

#define INLINE_const(%9)%8$(%0)%1(%2) %8$(%0)1(%2)

// Parameter type for passing callbacks about.
#define callback:%0) const callback_tag:callback_check:%0$$$
#define callback_tag:callback_check:%0,%1$$$ callback_tag:%0[],%1)
#define callback_check:%0$$$ %0[])

#define using%0\10;%1 callback_tag:@Ik:@Il:%0

// Get ONLY this ONE parameter (this is a VERY important stage)!
#define @Ik:@Il:%0, @Ip:@Iq:@Io:@Iu:@Iw:|||%0|||,
#define @Il:%0) @Ip:@Iq:@Io:@Iu:@Iw:|||%0|||)

#define @Ip:%9|||%0callback%1||| @Ir:@Is:"\03;"#%1||||
#define @Iq:%9|||%0public%1||| @Ir:@Is:"\03;"#%1||||
#define @Io:%9|||%0inline%1||| @In:@It:%0%1||||
#define @Iu:%9|||%0resolved%1||| @In:@It:%1[E_CALLBACK_DATA:0]||||
#define @Iw:|||%1||| @In:@It:#%1||||

// Callbacks with "On" in the name (often overidden by y_hooks and ALS).
#define @Ir:@Is:%0On%1|||| @In:@It:%0"On"#%1||||
#define @Is:%0|||| @In:@It:#%0|||| //Using_unknown_callback

// Callbacks with additional parameters (MUST have matching parameters (y_ini)).
#define @In:@It:%0(%1)%3||||%2) %0%3%2,.bExtra=true,.extra=%1)
#define @It:%0|||| %0

I@E(const name[], a = INLINE_PATTERN_1, b = INLINE_PATTERN_2, c = INLINE_PATTERN_3, d = INLINE_PATTERN_4)
{
	return 0;
}

I@F()
{
	return 0;
}

I@L(...)
{
	return 0;
}

I@K(n)
{
	return 0;
}

#if 0

// This:

Func()
{
	inline Inner(a, string:b[], c[64], &d)
	{
		// Code.
	}
}

// Becomes:

Func()
{
	static const Inner = 0;
	while (Inline_Start(Inner)) for (new a, string:b[], c[64], d; Inline_Def(0, cellmin, 64, -1); Inline_End())
	{
		// Code.
	}
}

// Rewrite "Inline_Start()" with entry code and a jump over the whole inline.

// Rewrite "Inline_Def" with 

// Where:

Inline_Start(const &name, a = INLINE_PATTERN_1, b = INLINE_PATTERN_2, c = INLINE_PATTERN_3, d = INLINE_PATTERN_4)
{
	// The four extra parameters are just for putting unique scannable patterns
	// in to the code so that we can locate these function calls and rewrite
	// them.
	#pragma unused a, b, c, d
	// It turns out that "const &" IS valid!  Pointless, but valid, which is
	// good because we want to bypass the compiler restrictions.
	// This allows us to write to a const reference without the compiler
	// objecting to it.  This is, of course, a TERRIBLE idea!  In fact, this is
	// only logically what happens, since this function is in reality never
	// called, only scanned for and rewritten.
	setarg(0, 0, inlineAddress);
	// NEVER loop.
	return 0;
}







#endif

static stock Inline_DoCodeGen()
{
}

