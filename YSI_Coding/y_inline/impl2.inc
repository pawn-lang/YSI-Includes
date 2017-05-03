// Revert to the old scanning design, but using the new code scanner.

const INLINE_PATTERN_1 = _A<Alex>;
const INLINE_PATTERN_2 = _C<Alex>;
const INLINE_PATTERN_3 = _A<Cole>;
const INLINE_PATTERN_4 = _C<Cole>;

#define CALL@I@E I@E("", 0, 0, 0, 0)
#define CALL@I@F I@F()
#define CALL@I@L I@L()
#define CALL@I@K I@K(0)

#if !defined MAX_INLINE_PARAMETERS
	#define MAX_INLINE_PARAMETERS (32)
#endif

enum E_INLINE_DATA
{
	// The fake "parameters" for the inline function.
	E_INLINE_DATA_PARAMETERS[MAX_INLINE_PARAMETERS],
	E_INLINE_DATA_PARAMETER_COUNT,
	E_INLINE_DATA_STATE,   // Which part of the header scanning we are on.
	E_INLINE_DATA_LOCALS,  // Container function locals.
	E_INLINE_DATA_PASSED,  // Inline function parameters.
	E_INLINE_DATA_PARAMS,  // Container function parameters (undetermined).
	E_INLINE_DATA_POINTER, // The struct to store the inline data in.
	E_INLINE_DATA_START,   // The start of the writable code space.
	E_INLINE_DATA_BEYOND,  // The end of the user code.
	E_INLINE_DATA_LOOP,    // The loopback pos if user code ends naturally.
	E_INLINE_DATA_USER     // The location of the user code.
}

static stock Inline_FoundStart(scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	if (data[E_INLINE_DATA_STATE] != 0)
		return 0;
	data[E_INLINE_DATA_LOCALS] = CodeScanGetMatchStack(scanner);
	data[E_INLINE_DATA_PARAMS] = -1; // No way to know!
	data[E_INLINE_DATA_POINTER] = CodeScanGetMatchHole(scanner, 0);
	data[E_INLINE_DATA_START] = CodeScanGetMatchAddress(scanner);
	data[E_INLINE_DATA_BEYOND] = CodeScanGetMatchHole(scanner, 1);
	data[E_INLINE_DATA_STATE] = 1;
	data[E_INLINE_DATA_PARAMETER_COUNT] = 0;
	return 0;
}

static stock Inline_FoundMid(scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	if (data[E_INLINE_DATA_STATE] != 1)
		return 0;
	data[E_INLINE_DATA_LOOP] = CodeScanGetMatchAddress(scanner) + 6 * cellbytes;
	if (AMX_Read(data[E_INLINE_DATA_LOOP] + AMX_HEADER_COD) == _:RelocateOpcode(OP_BREAK))
		data[E_INLINE_DATA_LOOP] += cellbytes;
	data[E_INLINE_DATA_PASSED] = CodeScanGetMatchStack(scanner) - data[E_INLINE_DATA_LOCALS];
	data[E_INLINE_DATA_STATE] = 2;
	return 0;
}

static stock Inline_FoundDescriptor(size, data[E_INLINE_DATA])
{
	if (data[E_INLINE_DATA_PARAMETER_COUNT] == MAX_INLINE_PARAMETERS)
		P:F("y_inline: Max inline parameter count exceeded (%d).", MAX_INLINE_PARAMETERS);
	else switch (size)
	{
		case 0:
		{
			data[E_INLINE_DATA_PARAMETERS][data[E_INLINE_DATA_PARAMETER_COUNT]++] = 0;
		}
		case -1:
		{
			data[E_INLINE_DATA_PARAMETERS][data[E_INLINE_DATA_PARAMETER_COUNT]++] = -1;
			data[E_INLINE_DATA_STATE] |= 16;
		}
		case cellmax:
		{
			data[E_INLINE_DATA_PARAMETERS][data[E_INLINE_DATA_PARAMETER_COUNT]++] = cellmax;
			data[E_INLINE_DATA_STATE] |= 8;
		}
		default:
		{
			data[E_INLINE_DATA_PARAMETERS][data[E_INLINE_DATA_PARAMETER_COUNT]++] = size * 4;
			data[E_INLINE_DATA_STATE] |= 8;
		}
	}
}

static stock Inline_FoundConst(scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	if (data[E_INLINE_DATA_STATE] != 2)
		return 0;
	data[E_INLINE_DATA_STATE] = 3 + CodeScanGetMatchHole(scanner, 0);
	return 0;
}

static stock Inline_FoundVar(scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	if (data[E_INLINE_DATA_STATE] < 3)
		return 0;
	Inline_FoundDescriptor(0, data);
	return 0;
}

static stock Inline_FoundRef(scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	if (data[E_INLINE_DATA_STATE] < 3)
		return 0;
	Inline_FoundDescriptor(CodeScanGetMatchHole(scanner, 0), data);
	return 0;
}

static stock Inline_FoundEnd(scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	if (data[E_INLINE_DATA_STATE] < 3)
		return 0;
	data[E_INLINE_DATA_USER] = CodeScanGetMatchAddress(scanner) + CodeScanGetMatchLength(scanner);
	printf("End: %08x", data[E_INLINE_DATA_USER]);
	// Do the actual codegen here.
	Inline_DoCodeGen();
	// Remove the return for the inner loop, since it may now point to an
	// invalid address (in the middle of an OpCode we just wrote out).
	new
		Opcode:nop = RelocateOpcode(OP_NOP),
		addr = CodeScanGetMatchHole(scanner, 1) + AMX_HEADER_COD;
	AMX_Write(addr + 0, _:nop);
	AMX_Write(addr + 4, _:nop);
	// Restart scanning for the next inline.
	data[E_INLINE_DATA_STATE] = 0;
	return 0;
}

public OnCodeInit()
{
	new scanner[CodeScanner];
	CodeScanInit(scanner);
	
	// Allocate the inline scanning data on the stack, instead of globally.
	new data[E_INLINE_DATA];
	
	// Optimised.
	new csm0[CodeScanMatcher];
	CodeScanMatcherInit(csm0, &Inline_FoundStart);
	CodeScanMatcherData(csm0, ref(data));
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
	CodeScanMatcherData(csm1, ref(data));
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
	CodeScanMatcherData(csm2, ref(data));
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
	CodeScanMatcherData(csm3, ref(data));
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
	CodeScanMatcherData(csm4, ref(data));
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
	CodeScanMatcherData(csm5, ref(data));
	CodeScanMatcherPattern(csm5,
		OP(CALL, &I@L)
		OP(HEAP, ???)
		OP(JZER, ???)
	);
	CodeScanAddMatcher(scanner, csm5);
	
	// Constness
	new csm6[CodeScanMatcher];
	CodeScanMatcherInit(csm6, &Inline_FoundConst);
	CodeScanMatcherData(csm6, ref(data));
	CodeScanMatcherPattern(csm6,
		OP(PUSH_C, ???)
		OP(PUSH_C, 4)
		OP(CALL, &I@K)
	);
	CodeScanAddMatcher(scanner, csm6);
	
	new csm7[CodeScanMatcher];
	CodeScanMatcherInit(csm7, &Inline_FoundConst);
	CodeScanMatcherData(csm7, ref(data));
	CodeScanMatcherPattern(csm7,
		OP(CONST_PRI, ???)
		OP(PUSH_PRI)
		OP(PUSH_C, 4)
		OP(CALL, &I@K)
	);
	CodeScanAddMatcher(scanner, csm7);
	
	// Run all the scanners in parallel.
	// TODO: Try and determine rough types for parent function parameters, using
	// Opcodes like LREF, SREF, and IDXADDR (IDXARRAY?  Can't remember off the
	// top of my head).
	CodeScanRun(scanner);
	return 1;
}













#define LAMBDA_i<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0|||0,|||<%9>{%0}(%1)%8;
#define LAMBDA_ii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1|||0,0,|||<%9>{%0}(%1)%8;
#define LAMBDA_iii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1,_2|||0,0,0,|||<%9>{%0}(%1)%8;
#define LAMBDA_iiii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1,_2,_3|||0,0,0,0,|||<%9>{%0}(%1)%8;
#define LAMBDA_iiiii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1,_2,_3,_4|||0,0,0,0,0,|||<%9>{%0}(%1)%8;

#define _DO_LAMBDA|||%6|||%5|||<%9>{%0}(%1)%8; LAM@0()%8;{LAM@1();static const YSII[]="@:....";if(I@E(YSII))for(%6;I@F();)while(I@L(%5I@K()))YSI_gInlineRet+=(%0);LAM@2(%9(callback_tag:YSII%1));}

// Make sure there's a space after the "return".
#define return%0({%1}%2)%3; I@=%0({%1}%2)%3;return I@;

// The "INLINE" in the types here will override "PARSER@" to "PARSE@INLINE",
// because there is no colon (well not "because", but it helps).
#define inline%0(%1) MAKE_PARSER(INLINE,ARR:REF:STR:NUM:QAL::INLINE)(%0(%1))()0()

// Follows the "code-parse.inc" internal structure.  Ugly but required, since we
// are parsing functions, but not at a top level.
#define PARSER@INLINE:%0(%5)%6(%7)$ static %6[_:%0(%5)%6(%7) I@O$

#define INLINE_STR(%9,%9,%2,%9)%8$(%0)%1(%3) %8$(%0,%2[YSI_MAX_INLINE_STRING])%1(cellmax,%3)
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
	while (Inline_Start(Inner)) for (new a, string:b[], c[64], d; Inline_Def(0, cellmax, 64, -1); Inline_End())
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

static stock Inline_DoCodeGen(data[E_INLINE_DATA])
{
	// The code will be written between "E_INLINE_DATA_START" and
	// "E_INLINE_DATA_USER", except for a few bytes at "E_INLINE_DATA_LOOP",
	// which is the point that user code will return to when it ends, and so
	// should handle that case (mostly just a `STACK` and `RETN`).
	// 
	// In order to simplify the code generation, I use the `_@emit` macro, which
	// is the same as the `@emit` macro, but transparently handles the void for
	// "_LOOP" by running out of space, erroring, putting in the end code, and
	// reinitialising the assembly context after that gap.
	// 
	// =========================================================================
	//     NOW WE CAN DO THE MAIN FUNCTION CODE.
	// =========================================================================
	new
		argSize = data[E_INLINE_DATA_LOCALS];
	new
		ctx[AsmContext];
	// =========================================================================
	//     CODE SPACE AVAILABLE
	// =========================================================================
	//  
	//  Inline_Entry: 6
	//  Vars: 2 v+r
	//  Arrays: 7 a
	//  JUMP: 2
	//  Inline_Allocator: 6
	//  
	//  Arrays: 6 a
	//  Vars: 5 v
	//  Refs: 6 r
	//  
	//  Inline_Main: 19
	//  
	//  Simple Total: 14 + 7v + 8r + 19
	//  Complex Total: 14 + 7v + 8r + 17a + 19
	//  
	//  Simple Required: 15 + 3v + 7r + 16
	//  Complex Required: 15 + 4v + 8r + 6a + 16
	//  
	// =========================================================================
	//     SEGMENT 1 - RESOLVE AND PUSH CLOSURE DATA AND PARAMETERS
	// =========================================================================
	//YSI_g_sJumpAddress = 0,
	AsmInitPtr(ctx, data[E_INLINE_DATA_START] + AMX_HEADER_COD, data[E_INLINE_DATA_LOOP] - data[E_INLINE_DATA_START]);
//	AsmInitPtr(ctx, YSI_g_sCurInlineEntry + AMX_HEADER_COD, YSI_g_sCurInlineLoop - YSI_g_sCurInlineEntry - 8),
	AsmSetErrorHandler(ctx, GetPublicAddressFromName("Inline_OnAsmError"));
	// Space for params + count.
	new
		// Size of stored closure data.
		offset = (YSI_g_sCurInlineParams + YSI_g_sCurInlineLocals + 12);
	if (varCount == args) // Only variables.
	{
		// =====================================================================
		//     SIMPLE CODE - NO ARRAYS OR STRINGS
		// =====================================================================
		if (YSI_g_sCurInlineLocals)
		{
			P:5("Inline_Main: TYPE 0");
			YSI_g_sRequiredSpace = 4 * 3 * args + 4 * 13;
			_@emit STACK      (-offset)
			_@emit ADDR.alt   (-offset) // Like "LCTRL 4; XCHG", but shorter.
			_@emit LREF.S.pri 12   // Load "func" variable.
			// Sadly "MOVS" checks that the destination is valid and in the stack, which
			// is what we didn't want.
			_@emit MOVS       offset
			// Reduce the stack again.  This is the shortest way I know (5 cells).
			_@emit STACK      (4 + YSI_g_sCurInlineLocals)
			_@emit PROC       // Set up the new frame.
			_@emit STACK      (-YSI_g_sCurInlineLocals) // Skip other locals again.
			new
				// Get the offset to the calling function's passed parameters.
				// 12 for this function's header, plus this function's parameters, plus
				// the last function's locals (currently none, MUST BE KEPT UP TO DATE),
				// plus the last function's header, plus the "func" variable.
				load = 12 + YSI_g_sCurInlineParams + 0 + 12 + 4,
				i = 0;
			while (i++ < args)
			{
				// Loop over the arguments and push them.
				_@emit LREF.S.pri load
				_@emit PUSH.pri
				load += 4;
			}
		}
		else
		{
			P:5("Inline_Main: TYPE 1 (%d, %d, %d, %d, %d)", offset, offset - 4, args, 4 * 3 * args + 4 * 9, 12 + YSI_g_sCurInlineParams + 0 + 12 + 4);
			// This is the simplest of the four versions of the code.  Here
			// there are no arrays to copy over, nor are there any local
			// variables from the closure.
			offset -= 4,
			YSI_g_sRequiredSpace = 4 * 3 * args + 4 * 9;
			_@emit STACK      (-offset)
			_@emit ADDR.alt   (-offset)
			_@emit LREF.S.pri 12
			_@emit MOVS       offset
			_@emit PROC
			new
				load = 12 + YSI_g_sCurInlineParams + 0 + 12 + 4,
				i = 0;
			while (i++ < args)
			{
				_@emit LREF.S.pri load
				_@emit PUSH.pri
				load += 4;
			}
			offset += 4;
		}
	}
	else
	{
		// =====================================================================
		//     COMPLEX CODE - ARRAYS OR STRINGS
		// =====================================================================
		if (YSI_g_sCurInlineLocals)
		{
			P:5("Inline_Main: TYPE 2");
			YSI_g_sRequiredSpace = 4 * 4 * varCount + 4 * 6 * arrCount + 4 * 14 * strCount + 4 * 13;
			_@emit STACK      (-offset)
			_@emit STACK      (YSI_g_sCurInlineLocals - argSize)
			_@emit LREF.S.pri 12
			_@emit MOVS       offset
			new
				load = 12 + 4,
				stor = -offset,
				i = 0;
			while (i < args)
			{
				if ((varCount = getarg(++i)) == cellmax)
				{
					// String.
					stor -= YSI_MAX_INLINE_STRING * 4;
					_@emit PUSH.C     YSI_MAX_INLINE_STRING
					_@emit PUSH.S     load // src = *cur
					_@emit ZERO.S     stor // dest[0] = '\0';
					_@emit PUSH.adr   stor // dst = &dest
					_@emit PUSH.C     12
					_@emit SYSREQ     "strcat"
					_@emit STACK      16
				}
				else
				{
					if ((varCount *= 4) <= 0)
					{
						// Normal variable.
						stor -= 4;
						_@emit LREF.S.pri load
						_@emit STOR.S.pri stor
					}
					else 
					{
						// Array.
						stor -= varCount;
						_@emit LOAD.S.pri load
						_@emit ADDR.alt   stor
						_@emit MOVS       varCount
					}
				}
				load += 4;
			}
			_@emit STACK      (4 + argSize)
			_@emit PROC
			_@emit STACK      (-argSize)
		}
		else
		{
			P:5("Inline_Main: TYPE 3");
			offset -= 4,
			YSI_g_sRequiredSpace = 4 * 4 * varCount + 4 * 6 * arrCount + 4 * 14 * strCount + 4 * 11;
			_@emit STACK      (-offset)
			_@emit ADDR.alt   (-offset)
			_@emit LREF.S.pri 12
			_@emit MOVS       offset
			_@emit PROC
			_@emit STACK      (-argSize)
			new
				load = 12 + YSI_g_sCurInlineParams + 0 + 12 + 4,
				stor = 0,
				i = 0;
			while (i < args)
			{
				if ((varCount = getarg(++i)) == cellmax)
				{
					// String.
					stor -= YSI_MAX_INLINE_STRING * 4;
					_@emit PUSH.C     YSI_MAX_INLINE_STRING
					_@emit PUSH.S     load // src = *cur
					_@emit ZERO.S     stor // dest[0] = '\0';
					_@emit PUSH.adr   stor // dst = &dest
					_@emit PUSH.C     12
					_@emit SYSREQ     "strcat"
					_@emit STACK      16
				}
				else
				{
					if ((varCount *= 4) <= 0)
					{
						// Normal variable.
						stor -= 4;
						_@emit LREF.S.pri load
						_@emit STOR.S.pri stor
					}
					else 
					{
						// Array.
						stor -= varCount;
						_@emit LOAD.S.pri load
						_@emit ADDR.alt   stor
						_@emit MOVS       varCount
					}
				}
				load += 4;
			}
			offset += 4;
		}
	}
	// =========================================================================
	//     SEGMENT 2 - SAVE REFERENCES BACK
	// =========================================================================
	if (YSI_g_sJumpAddress == 0)
	{
		// Fake an error.  This indirectly calls the "Inline_OnAsmError"
		// function above to fill the intervening space with NOPs.
		ctx[AsmContext_buffer_size] = 0;
		@emit NOP
	}
	// The maths should now be correct.
	AsmInitPtr(ctx, YSI_g_sCurInlineLoop + AMX_HEADER_COD, cellmax);
	if (argSize)
	{
		@emit STACK     argSize
		YSI_g_sJumpAddress = YSI_g_sCurInlineLoop + 16;
	}
	else
	{
		YSI_g_sJumpAddress = YSI_g_sCurInlineLoop + 8;
	}
	@emit ZERO.pri // Default return value.
	@emit RETN
	// Save this return address, so the instruction above goes to the one below.
	// Save references.
	new
		load = -offset,
		stor = 12 + 4,
		i = 0;
	while (i < args)
	{
		varCount = getarg(++i);
		switch (varCount)
		{
			case -1:
			{
				load -= 4;
				@emit LOAD.S.alt load
				@emit SREF.S.alt stor
			}
			case 0: load -= 4;
			case cellmax: load -= YSI_MAX_INLINE_STRING * 4;
			default: load -= varCount * 4;
		}
		stor += 4;
	}
	// Copy the closure back (if there is anything that needs copying).
	if (constFunc && (YSI_g_sCurInlineParams || YSI_g_sCurInlineLocals))
	{
		if (!YSI_g_sCurInlineLocals) offset -= 4;
		@emit STACK      (-offset)
		@emit PUSH.pri
		@emit ADDR.pri   (-offset)
		@emit LREF.S.alt 12
		@emit MOVS       offset
		@emit POP.pri
		@emit STACK      offset
	}
	// Finish.
	@emit RETN
	// =========================================================================
	//     STORE THE RETURN ADDRESS
	// =========================================================================
	AMX_Write(YSI_g_sCurInlinePointer, YSI_g_sJumpAddress),
	AMX_Write(YSI_g_sCurInlinePointer - 12, '\02;');
}

