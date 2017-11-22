// How to convert from old y_inline to new y_inline:
// 
// 1) Delete all `[E_CALLBACK_DATA]` everywhere.  This can optionally be
//   replaced by a specifier tag.  So what used to be:
// 
//     new cb[E_CALLBACK_DATA];
// 
//   Becomes:
// 
//     new funcptr<iiis>:cb;
// 
// 2) Replace `Callback_Get`, `Callback_Restore`, and `Callback_Release` with
//   `Inline_Get`, `Inline_Restore`, and `Inline_Release`.
// 
// 3) Replace `callback:` tags with specifier tags.  So:
// 
//     MyFunc(callback:x)
// 
//   Becomes:
// 
//     MyFunc(funcptr<fff>:cb)
// 
// Note that this is all optional.  Not doing so will continue to work, but
// give warnings.

// Revert to the old scanning design, but using the new code scanner.

const INLINE_PATTERN_1 = _C<Alex>;
const INLINE_PATTERN_2 = _C<_Y_L>;
const INLINE_PATTERN_3 = _C<ess_>;
const INLINE_PATTERN_4 = _C<Cole>;

#define CALL@I@E I@E(0, 0, 0, 0)
#define CALL@I@F I@F()
#define CALL@I@L I@L()
#define CALL@I@K I@K(0)
#define CALL@ref ref()

#define MAX_INLINE_PARAMETERS (32)

#define INLINE_DESCRIPTOR_VAR (0)
#define INLINE_DESCRIPTOR_REF (-1)
#define INLINE_DESCRIPTOR_STR (cellmax)

enum E_CALLBACK_DATA
{
	// Now only one item.
	ResolvedFunc:E_CALLBACK_DATA_ALLOC
}

enum E_INLINE_DATA
{
	// The fake "parameters" for the inline function.
	E_INLINE_DATA_PARAMETERS[MAX_INLINE_PARAMETERS],
	E_INLINE_DATA_PARAMETER_COUNT,
	E_INLINE_DATA_STATE,   // Which part of the header scanning we are on.
	E_INLINE_DATA_LOCALS,  // Container function locals.
	E_INLINE_DATA_PASSED,  // Inline function parameters.
	E_INLINE_DATA_POINTER, // The struct to store the inline data in.
	E_INLINE_DATA_START,   // The start of the writable code space.
	E_INLINE_DATA_BEYOND,  // The end of the user code (skip jump location).
	E_INLINE_DATA_USER     // The location of the user code.
}

static stock
	YSI_g_sJumpOffset,
	YSI_g_sCallbackCallAddress;

static stock Inline_FoundStart(scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	P:4("Inline_FoundStart called");
	if (data[E_INLINE_DATA_STATE] != 0)
		return 0;
	P:5("Inline_FoundStart OK");
	data[E_INLINE_DATA_LOCALS] = CodeScanGetMatchStack(scanner);
	data[E_INLINE_DATA_START] = CodeScanGetMatchAddress(scanner);
	data[E_INLINE_DATA_BEYOND] = CodeScanGetMatchHole(scanner, 5);
	data[E_INLINE_DATA_STATE] = 1;
	data[E_INLINE_DATA_PARAMETER_COUNT] = 0;
	return 0;
}

static stock Inline_FoundMid(scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	P:4("Inline_FoundMid called");
	if (data[E_INLINE_DATA_STATE] != 1)
		return 0;
	P:5("Inline_FoundMid OK");
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
		case INLINE_DESCRIPTOR_VAR:
		{
			data[E_INLINE_DATA_PARAMETERS][data[E_INLINE_DATA_PARAMETER_COUNT]++] = 0;
		}
		case INLINE_DESCRIPTOR_REF:
		{
			data[E_INLINE_DATA_PARAMETERS][data[E_INLINE_DATA_PARAMETER_COUNT]++] = -1;
			data[E_INLINE_DATA_STATE] |= 16;
		}
		case INLINE_DESCRIPTOR_STR:
		{
			data[E_INLINE_DATA_PARAMETERS][data[E_INLINE_DATA_PARAMETER_COUNT]++] = cellmax;
			data[E_INLINE_DATA_STATE] |= 8;
		}
		default:
		{
			data[E_INLINE_DATA_PARAMETERS][data[E_INLINE_DATA_PARAMETER_COUNT]++] = size * cellbytes;
			data[E_INLINE_DATA_STATE] |= 8;
		}
	}
}

static stock Inline_FoundConst(scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	P:4("Inline_FoundConst called");
	if (data[E_INLINE_DATA_STATE] != 2)
		return 0;
	P:5("Inline_FoundConst OK");
	data[E_INLINE_DATA_STATE] = 3 + CodeScanGetMatchHole(scanner, 0);
	return 0;
}

static stock Inline_FoundConst2(scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	P:4("Inline_FoundConst2 called");
	#pragma unused scanner
	// Can't use size to determine this match as two pieces of code are the same
	// size in the same place, but mean very different things.
	if (data[E_INLINE_DATA_STATE] != 2)
		return 0;
	P:5("Inline_FoundConst2 OK");
	data[E_INLINE_DATA_STATE] = 3;
	return 0;
}

static stock Inline_FoundVar(scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	P:4("Inline_FoundVar called");
	#pragma unused scanner
	if (data[E_INLINE_DATA_STATE] < 3)
		return 0;
	P:5("Inline_FoundVar OK");
	Inline_FoundDescriptor(0, data);
	return 0;
}

static stock Inline_FoundRef(scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	P:4("Inline_FoundRef called");
	if (data[E_INLINE_DATA_STATE] < 3)
		return 0;
	P:5("Inline_FoundRef OK");
	Inline_FoundDescriptor(CodeScanGetMatchHole(scanner, 0), data);
	return 0;
}

static stock Inline_FoundEnd(scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	P:4("Inline_FoundEnd called");
	if (data[E_INLINE_DATA_STATE] < 3)
		return 0;
	P:5("Inline_FoundEnd OK");
	data[E_INLINE_DATA_USER] = CodeScanGetMatchAddress(scanner) + CodeScanGetMatchLength(scanner);
	// Do the actual codegen here.
	Inline_DoCodeGen(scanner, data);
	// Restart scanning for the next inline.
	data[E_INLINE_DATA_STATE] = 0;
	return 0;
}

public OnCodeInit()
{
	new
		hdr[AMX_HDR];
	GetAmxHeader(hdr);
	YSI_g_sJumpOffset = GetAmxBaseAddress() + hdr[AMX_HDR_COD];
	#emit CONST.pri    Callback_Call
	#emit STOR.pri     YSI_g_sCallbackCallAddress
	YSI_g_sCallbackCallAddress += YSI_g_sJumpOffset;
	
	new scanner[CodeScanner];
	CodeScanInit(scanner);
	
	// Allocate the inline scanning data on the stack, instead of globally.
	new data[E_INLINE_DATA];
	
	// Optimised.
	new csm1a[CodeScanMatcher];
	CodeScanMatcherInit(csm1a, &Inline_FoundStart);
	CodeScanMatcherData(csm1a, ref(data));
	CodeScanMatcherPattern(csm1a,
		OP(STACK,      -4)
		OP(CONST_PRI,  ???)
		OP(INVERT)
		OP(INVERT)
		OP(PUSH_PRI)
		OP(PUSH_C,     4)
		OP(CALL,       &ref)
		OP(STOR_S_PRI, ???)
		OP(STACK,      -4)
		OP(LOAD_S_PRI, ???)
		OP(STOR_S_PRI, ???)
		OP(PUSH_C,     INLINE_PATTERN_4)
		OP(PUSH_C,     INLINE_PATTERN_3)
		OP(PUSH_C,     INLINE_PATTERN_2)
		OP(PUSH_C,     INLINE_PATTERN_1)
		OP(PUSH_C,     16)
		OP(CALL,       &I@E)
		OP(JZER,       ???)
		OP(JUMP,       ???)
	);
	CodeScanAddMatcher(scanner, csm1a);
	
	// Unoptimised.
	new csm1b[CodeScanMatcher];
	CodeScanMatcherInit(csm1b, &Inline_FoundStart);
	CodeScanMatcherData(csm1b, ref(data));
	CodeScanMatcherPattern(csm1b,
		OP(STACK,      -4)
		OP(CONST_PRI,  ???)
		OP(INVERT)
		OP(INVERT)
		OP(PUSH_PRI)
		OP(PUSH_C,     4)
		OP(CALL,       &ref)
		OP(STOR_S_PRI, ???)
		OP(STACK,      -4)
		OP(LOAD_S_PRI, ???)
		OP(STOR_S_PRI, ???)
		OP(CONST_PRI,  INLINE_PATTERN_4)
		OP(PUSH_PRI)
		OP(CONST_PRI,  INLINE_PATTERN_3)
		OP(PUSH_PRI)
		OP(CONST_PRI,  INLINE_PATTERN_2)
		OP(PUSH_PRI)
		OP(CONST_PRI,  INLINE_PATTERN_1)
		OP(PUSH_PRI)
		OP(PUSH_C,     16)
		OP(CALL,       &I@E)
		OP(JZER,       ???)
		OP(JUMP,       ???)
	);
	CodeScanAddMatcher(scanner, csm1b);
	
	// Mid point.
	new csm2a[CodeScanMatcher];
	CodeScanMatcherInit(csm2a, &Inline_FoundMid);
	CodeScanMatcherData(csm2a, ref(data));
	CodeScanMatcherPattern(csm2a,
		OP(PUSH_C,     0)
		OP(CALL,       &I@F)
		OP(JZER,       ???)
	);
	CodeScanAddMatcher(scanner, csm2a);
	
	// Normal parameter.
	//   
	//   ZERO.pri
	//   HEAP 4
	//   STOR.I
	//   PUSH.alt
	//   
	new csm3a[CodeScanMatcher];
	CodeScanMatcherInit(csm3a, &Inline_FoundVar);
	CodeScanMatcherData(csm3a, ref(data));
	CodeScanMatcherPattern(csm3a,
		OP(ZERO_PRI)
		OP(HEAP,       4)
		OP(STOR_I)
		OP(PUSH_ALT)
	);
	CodeScanAddMatcher(scanner, csm3a);
	
	new csm3b[CodeScanMatcher];
	CodeScanMatcherInit(csm3b, &Inline_FoundVar);
	CodeScanMatcherData(csm3b, ref(data));
	CodeScanMatcherPattern(csm3b,
		OP(ZERO_PRI)
		OP(HEAP,       4)
		OP(STOR_I)
		OP(MOVE_PRI)
		OP(PUSH_PRI)
	);
	CodeScanAddMatcher(scanner, csm3b);
	
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
	new csm4a[CodeScanMatcher];
	CodeScanMatcherInit(csm4a, &Inline_FoundRef);
	CodeScanMatcherData(csm4a, ref(data));
	CodeScanMatcherPattern(csm4a,
		OP(CONST_PRI,  ???)
		OP(HEAP,       4)
		OP(STOR_I)
		OP(PUSH_ALT)
	);
	CodeScanAddMatcher(scanner, csm4a);
	
	new csm4b[CodeScanMatcher];
	CodeScanMatcherInit(csm4b, &Inline_FoundRef);
	CodeScanMatcherData(csm4b, ref(data));
	CodeScanMatcherPattern(csm4b,
		OP(CONST_PRI,  ???)
		OP(HEAP,       4)
		OP(STOR_I)
		OP(MOVE_PRI)
		OP(PUSH_PRI)
	);
	CodeScanAddMatcher(scanner, csm4b);
	
	// End
	new csm5a[CodeScanMatcher];
	CodeScanMatcherInit(csm5a, &Inline_FoundEnd);
	CodeScanMatcherData(csm5a, ref(data));
	CodeScanMatcherPattern(csm5a,
		OP(CALL,       &I@L)
		OP(HEAP,       ???)
		OP(JZER,       ???)
	);
	CodeScanAddMatcher(scanner, csm5a);
	
	// Constness
	new csm6a[CodeScanMatcher];
	CodeScanMatcherInit(csm6a, &Inline_FoundConst);
	CodeScanMatcherData(csm6a, ref(data));
	CodeScanMatcherPattern(csm6a,
		OP(PUSH_C,     ???)
		OP(PUSH_C,     4)
		OP(CALL,       &I@K)
	);
	CodeScanAddMatcher(scanner, csm6a);
	
	new csm6b[CodeScanMatcher];
	CodeScanMatcherInit(csm6b, &Inline_FoundConst);
	CodeScanMatcherData(csm6b, ref(data));
	CodeScanMatcherPattern(csm6b,
		OP(CONST_PRI,  ???)
		OP(PUSH_PRI)
		OP(PUSH_C,     4)
		OP(CALL,       &I@K)
	);
	CodeScanAddMatcher(scanner, csm6b);
	
	new csm6c[CodeScanMatcher];
	CodeScanMatcherInit(csm6c, &Inline_FoundConst2);
	CodeScanMatcherData(csm6c, ref(data));
	CodeScanMatcherPattern(csm6c,
		OP(ZERO_PRI)
		OP(PUSH_PRI)
		OP(PUSH_C,     4)
		OP(CALL,       &I@K)
	);
	CodeScanAddMatcher(scanner, csm6c);
	
	// Run all the scanners in parallel.
	// TODO: Try and determine rough types for parent function parameters, using
	// Opcodes like LREF, SREF, and IDXADDR (IDXARRAY?  Can't remember off the
	// top of my head).
	CodeScanRun(scanner);
	return 1;
}

/*

At maximum optimisation we get...

    Via parameter passing:
    
         6 cells for a reference variable.
         6 cells for an array.
         6 cells for a string.
         5 cells for a normal variable.
    
    Via initial declaration:
    
         2 cells for a reference variable.
         7 cells for an array.
         7 cells for a string.
         2 cells for a normal variable.
    
    For a total of:
    
         8 cells for a reference variable.
        13 cells for an array.
        13 cells for a string.
         7 cells for a normal variable.

Plus:

    18 cells for the initial call to `I@E` (the last one contains the end
        address).
     8 cells for the call to `I@F` (the address after which is the loop repeat).
    20 cells for the call to `I@L` (the address after which is the start of
        code, and whose final part jumps to just after the code return jump,
        that we can co-opt for `RETN` and do away with the bounds check code).
     N useless cells at the end.

*/











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
#define PARSER@INLINE:%0(%5)%6(%7)$ new _@%6=ref(_:%0(%5)%6(%7) I@O$

#define INLINE_STR(%9,%9,%2,%9)%8$(%0)%1(%3) %8$(%0,%2[YSI_MAX_INLINE_STRING])%1(cellmax,%3)
#define INLINE_ARR(%9,%9,%2,%9)%8$(%0)%1(%3) %8$(%0,%2[%9])%1(%9,%3)
#define INLINE_NUM(%9,%9,%2)%8$(%0)%1(%3) %8$(%0,%2)%1(0,%3)
#define INLINE_REF(%9,%9,%2)%8$(%0)%1(%3) %8$(%0,%2)%1(-1,%3)

#define INLINE_END(%9)%8$(,%0)%1(%3) %8$#%9":...."),%9=_@%9;if (I@E()){}else for(new %0;I@F();)while(I@L(%3I@K(%1)))

#define INLINE_NUL(%9)%8$()%1() %8$#%9":...."),%9=_@%9;if (I@E()){}else for(;I@F();)while(I@L(I@K(%1)))

#define I@O$

#define INLINE_const(%9)%8$(%0)%1(%2) %8$(%0)1(%2)

// Parameter type for passing callbacks about.
#define using%0\10;%1 callback_tag:@Ik:@Il:%0
//#define using%0\32; using
//#define usingcallback
//#define usingpublic usingcallback
//#define usinginline
//#define usingresolved

#if 0

MyFunc(funcptr<>)
{
	
}

#endif

// Get ONLY this ONE parameter (this is a VERY important stage)!
//#define @Ik:@Il:%0, @Ip:@Iq:@Io:@Iu:@Iw:|||%0|||,
//#define @Il:%0) @Ip:@Iq:@Io:@Iu:@Iw:|||%0|||)

//#define @Ip:%9|||%0callback%1||| @Ir:@Is:"\03;"#%1||||
//#define @Iq:%9|||%0public%1||| @Ir:@Is:"\03;"#%1||||
//#define @Io:%9|||%0inline%1||| @In:@It:%0%1||||
//#define @Iu:%9|||%0resolved%1||| @In:@It:%1[E_CALLBACK_DATA:0]||||
//#define @Iw:|||%1||| @In:@It:#%1||||

// Callbacks with "On" in the name (often overidden by y_hooks and ALS).
#define @Ir:@Is:%0On%1|||| @In:@It:%0"On"#%1||||
#define @Is:%0|||| @In:@It:#%0|||| //Using_unknown_callback

// Callbacks with additional parameters (MUST have matching parameters (y_ini)).
#define @In:@It:%0(%1)%3||||%2) %0%3%2,.bExtra=true,.extra=%1)
#define @It:%0|||| %0

stock I@E(a = INLINE_PATTERN_1, b = INLINE_PATTERN_2, c = INLINE_PATTERN_3, d = INLINE_PATTERN_4)
{
	#pragma unused a, b, c, d
	return 0;
}

stock I@F()
{
	return 0;
}

stock I@L(...)
{
	return 0;
}

stock I@K(n)
{
	#pragma unused n
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

stock Callback_Call(callback:callback, GLOBAL_TAG_TYPES:...)
{
	#pragma unused callback
	//#emit PROC                  //  1
	#emit LREF.S.pri   12         //  3
	// Get the size.
	#emit ADD.C        0xFFFFFFFC //  5
	#emit LOAD.I                  //  6
	#emit MOVE.alt                //  7
	// Grow the stack. 
	#emit SHL.C.alt    2          //  9
	#emit LCTRL        4          // 11
	#emit SUB                     // 12
	#emit SCTRL        4          // 14
	// Call memcpy. 
	#emit SHR.C.alt    2          // 16
	#emit PUSH.alt                // 17
	#emit SHL.C.alt    2          // 19
	#emit PUSH.alt                // 20
	#emit PUSH.C       0          // 22
	#emit LREF.S.alt   12         // 24
	#emit PUSH.alt                // 25
	#emit PUSH.pri                // 26
	#emit PUSH.C       20         // 28
	#emit SYSREQ.C     memcpy     // 30
	#emit STACK        24         // 32
	// "jump" in to the code. 
	#emit LREF.S.pri   12         // 34
	// Get the size. 
	#emit ADD.C        4          // 36
	#emit LOAD.I                  // 37
	#emit SCTRL        8          // 39
	#emit SCTRL        6          // 41
	
	// There's a bug with jumping forward in assembly.  This label neatly
	// includes the `LCTRL`/`SCTRL` pair we were going to `#emit` anyway.
Callback_Call_nothing_to_save:    // 45
	#emit LOAD.pri     I@         // 47
	#emit RETN                    // 48
	
	// Padding to account for debug builds.
	#emit BREAK                   // 49
	#emit BREAK                   // 50
//Callback_Call_restore_stack:
	// If the code jumps back to here, restore then save the stack.
	#emit STOR.pri     I@         // 52
	// Get the data size to copy back out.
	#emit LREF.S.pri   12         // 54
	// Get the size.
	#emit ADD.C        0xFFFFFFFC // 56
	#emit LOAD.I                  // 57
	#emit BREAK                   // 58
	#emit BREAK                   // 59
//Callback_Call_save_stack:
	// If the code decides to jump back to here, save the stack out again.
	#emit CONST.alt    12
	#emit JSLEQ        Callback_Call_nothing_to_save
	// The stack hasn't been restored yet, and we need it.
	#emit STOR.pri     J@
	#emit STACK        0
	#emit SUB.alt
	#emit SCTRL        4
	#emit LOAD.alt     J@
	#emit PUSH.alt
	#emit SHL.C.alt    2
	#emit PUSH.alt
	#emit PUSH.C       0
	#emit LREF.S.alt   12
	#emit PUSH.pri
	#emit PUSH.alt
	#emit PUSH.C       20
	#emit SYSREQ.C     memcpy
	#emit LCTRL        5
	#emit SCTRL        4
	#emit LOAD.pri     I@
	#emit RETN
	return 0;
}

static stock Inline_GenerateLocalsCopy(ctx[AsmContext], parameters[], count)
{
	new
		input = 16;
	for (new i = 0; i != count; ++i)
	{
		switch (parameters[i])
		{
		case -1, 0:
		{
			// This is the smallest way to adjust `alt` that I can find.  This
			// would be the same number of cells, but one more instruction, and
			// much larger for anything not a single cell:
			//   
			//   @emit DEC.alt
			//   @emit DEC.alt
			//   @emit DEC.alt
			//   @emit DEC.alt
			//   
			// This would be equivalent, there's no compelling reason for
			// either right now other than clarity
			//   
			//   @emit CONST.pri    -4
			//   @emit ADD
			//   @emit MOVE.alt
			//   
			// Or:
			//   
			//   @emit CONST.pri    4
			//   @emit SUB.alt
			//   @emit MOVE.alt
			//   
			@emit LREF.S.pri   input
			@emit PUSH.pri
		}
		case cellmax:
		{
			@emit STACK        -(YSI_MAX_INLINE_STRING * cellbytes)
			@emit STACK        0
			@emit LOAD.S.pri   input
			@emit MOVS         (YSI_MAX_INLINE_STRING * cellbytes)
		}
		default:
		{
			@emit STACK        -(parameters[i])
			@emit STACK        0
			@emit LOAD.S.pri   input
			@emit MOVS         (parameters[i])
		}
		}
		input += cellbytes;
	}
}

static stock Inline_GenerateLocalsStore(ctx[AsmContext], parameters[], count)
{
	new
		accumulate = 0;
	while (count--)
	{
		switch (parameters[count])
		{
		case -1:
		{
			if (accumulate)
				@emit STACK        accumulate
			accumulate = 0;
			@emit POP.pri
			@emit SREF.S.pri       count * cellbytes + 16
		}
		case 0:
			accumulate += cellbytes;
		case cellmax:
			accumulate += YSI_MAX_INLINE_STRING * cellbytes;
		default:
			accumulate += parameters[count];
		}
	}
	// Return how much of this data was left on the stack.  We might need to
	// clear it, we might not...
	return accumulate;
}

static stock Inline_GeneratePostamble(ctx[AsmContext], parameters[], const count, bool:isConst)
{
	new
		bool:needStore = false,
		accumulate = 0;
	for (new i = 0; i != count; ++i)
	{
		if (parameters[i] == -1)
		{
			needStore = true;
			break;
		}
	}
	// When we "return" from the function, we end up here, with all our stack
	// data removed.  Put it back (which is easy, because the top should still
	// be in `alt` - actually, it might not in some cases).  Turns out that's
	// irrelevant, since the only time it can happen is if there are no locals
	// to save!
	if (isConst)
	{
		if (needStore)
		{
			// Back up `pri` somewhere for returning later.
			@emit STOR.pri     ref(I@)
			// The last stack location is still in `alt` from removing
			// everything from the stack.  This actually exploits the fact that
			// the value in `alt` after `STACK` is the value BEFORE the
			// adjustment, not after.  Normally this is very odd, and it was
			// changed for PAWN 4.0 here:
			//   
			//   https://github.com/compuphase/pawn/issues/35
			//   
			// This is the first case I've ever found where it is useful!
			@emit MOVE.pri
			@emit SCTRL        4
			Inline_GenerateLocalsStore(ctx, parameters, count);
			// Restore the return value.
			@emit LCTRL        5
			@emit SCTRL        4
			@emit LOAD.pri     ref(I@)
		}
		// If we are here, we arein the context of `Callback_Call`, with no
		// locals on the stack.
		@emit RETN
	}
	else
	{
		if (needStore)
		{
			@emit STOR.pri     ref(I@)
			// Get the data size to copy back out.
			@emit LREF.S.pri   12
			// Get the size.
			@emit ADD.C        -4
			@emit LOAD.I
			@emit STOR.pri     ref(J@)
			@emit MOVE.pri
			@emit SCTRL        4
			accumulate = Inline_GenerateLocalsStore(ctx, parameters, count);
			if (accumulate)
				@emit STACK        accumulate
			@emit LOAD.pri     ref(J@)
			@emit JUMP         YSI_g_sCallbackCallAddress + 50 * cellbytes // Callback_Call_save_stack
		}
		else
			@emit JUMP         YSI_g_sCallbackCallAddress + 59 * cellbytes // Callback_Call_restore_stack
	}
}

static stock Inline_DoRetnGen(ctx[AsmContext], scanner[CodeScanner], data[E_INLINE_DATA])
{
	// Remove the return for the inner loop, since it may now point to an
	// invalid address (in the middle of an OpCode we just wrote out).
	new
		startaddr = data[E_INLINE_DATA_USER],
		endaddr = CodeScanGetMatchHole(scanner, 1) - 8,
		target = endaddr + YSI_g_sJumpOffset,
		dctx[DisasmContext];
	// Using the local decompiler, go through the code and remove any jumps to
	// outside of [startaddr, endaddr].  Convert them all to `RETN; NOP`.
	CodeScanGetMatchDisasm(scanner, dctx, CodeScanGetMatchLength(scanner));
	dctx[DisasmContext_end_ip] = endaddr + AMX_HEADER_COD + 16;
	while (DisasmNext(dctx) != DISASM_DONE)
	{
		// Is this a jump?  The only jumps that can get out of this constraint
		// are `JUMP` ones - all others like `JNEQ` etc would be generated by
		// `if` statements and so constrained by syntax.  `JUMP` would come from
		// `break`, `continue`, or `goto`.
		if (DisasmGetOpcode(dctx) == OP_JUMP && !(startaddr <= DisasmGetOperandReloc(dctx) < endaddr))
		{
			AMX_Write(DisasmGetCurIp(dctx) + 4, target);
		}
	}
	// Now at the end address, write the cleanup and return code.
	if (data[E_INLINE_DATA_PASSED] + data[E_INLINE_DATA_LOCALS])
	{
		AMX_Write(endaddr + AMX_HEADER_COD +  0, _:RelocateOpcode(OP_STACK));
		AMX_Write(endaddr + AMX_HEADER_COD +  4, data[E_INLINE_DATA_PASSED] + data[E_INLINE_DATA_LOCALS]);
		AMX_Write(endaddr + AMX_HEADER_COD +  8, _:RelocateOpcode(OP_RETN));
		AMX_Write(endaddr + AMX_HEADER_COD + 12, _:RelocateOpcode(OP_NOP));
	}
	else
	{
		AMX_Write(endaddr + AMX_HEADER_COD +  0, _:RelocateOpcode(OP_NOP));
		AMX_Write(endaddr + AMX_HEADER_COD +  4, _:RelocateOpcode(OP_NOP));
		AMX_Write(endaddr + AMX_HEADER_COD +  8, _:RelocateOpcode(OP_NOP));
		AMX_Write(endaddr + AMX_HEADER_COD + 12, _:RelocateOpcode(OP_NOP));
	}
	dctx[DisasmContext_end_ip] += 8;
	if (DisasmNext(dctx) != DISASM_DONE && DisasmGetOpcode(dctx) == OP_STACK)
	{
		AMX_Write(endaddr + AMX_HEADER_COD + 16, _:RelocateOpcode(OP_NOP));
		AMX_Write(endaddr + AMX_HEADER_COD + 20, _:RelocateOpcode(OP_NOP));
		@emit JUMP         target + 24
	}
	else
		@emit JUMP         target + 16
}

#define CALL@Inline_OnAsmError Inline_OnAsmError("", ASM_ERROR_NONE)

static stock Inline_OnAsmError(ctx[AsmContext], AsmError:error)
{
	switch (numargs() == 1 ? AsmGetError(ctx) : error)
	{
	case ASM_ERROR_OPCODE:          P:E("ASM_ERROR_OPCODE in Inline_Main.");
	case ASM_ERROR_OPERAND:         P:E("ASM_ERROR_OPERAND in Inline_Main.");
	case ASM_ERROR_SPACE:           P:E("ASM_ERROR_SPACE in Inline_Main.");
	case ASM_ERROR_LABEL_OVERFLOW:  P:E("ASM_ERROR_LABEL_OVERFLOW in Inline_Main.");
	case ASM_ERROR_LABEL_DUPLICATE: P:E("ASM_ERROR_LABEL_DUPLICATE in Inline_Main.");
	case ASM_ERROR_NONE: return;
	default: P:E("Unknown error in Inline_Main.");
	}
	// TODO: Abort codegen.
}

static stock Inline_DoCodeGen(scanner[CodeScanner], data[E_INLINE_DATA])
{
	new
		ctx[AsmContext];
	AsmInitPtr(ctx, data[E_INLINE_DATA_START] + AMX_HEADER_COD, data[E_INLINE_DATA_USER] - data[E_INLINE_DATA_START]);
	AsmSetErrorHandler(ctx, addressof (Inline_OnAsmError));
	Inline_DoRetnGen(ctx, scanner, data);
	Inline_GenerateLocalsCopy(ctx, data[E_INLINE_DATA_PARAMETERS], data[E_INLINE_DATA_PARAMETER_COUNT]);
	// if (!JIT && remaining > 2) @emit JUMP user_code
	Inline_GeneratePostamble(ctx, data[E_INLINE_DATA_PARAMETERS], data[E_INLINE_DATA_PARAMETER_COUNT], bool:(data[E_INLINE_DATA_STATE] & 4));
	AsmEmitPadding(ctx);
}

