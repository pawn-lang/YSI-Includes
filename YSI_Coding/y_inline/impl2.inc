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

// Revert to the old scanning design, but using the new code scanner.

const INLINE_PATTERN_1 = _C<Alex>;
const INLINE_PATTERN_2 = _C<_Y_L>;
const INLINE_PATTERN_3 = _C<ess_>;
const INLINE_PATTERN_4 = _C<Cole>;

forward Inline_MaybeFree_(ResolvedAlloc:a);

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
	E_INLINE_DATA_NAME,    // The address of the string with the name in.
	E_INLINE_DATA_STATE,   // Which part of the header scanning we are on.
	E_INLINE_DATA_LOCALS,  // Closure size.
	E_INLINE_DATA_STACK,   // Count of all locals.
	E_INLINE_DATA_POINTER, // The struct to store the inline data in.
	E_INLINE_DATA_START,   // The start of the writable code space.
	E_INLINE_DATA_BEYOND,  // The end of the user code (skip jump location).
	E_INLINE_DATA_USER     // The location of the user code.
}

static stock
	YSI_g_sJumpOffset,
	YSI_g_sCallbackCallAddress,
	// This is the start of the linked list of inline functions.  It goes backwards through the code
	// space, and should be used to find the nearest function matching the given name (as there may
	// be more than one).  It points to the start of the entry's data, but the first item in that
	// data is the function pointer, not the "next" pointer.  The start of the string with the name
	// in is 2 cells after this address.
	YSI_g_sInlineLinkedList;

static stock Inline_FoundStart(scanner[CodeScanner], data[E_INLINE_DATA] = "")
{
	P:4("Inline_FoundStart called");
	if (data[E_INLINE_DATA_STATE] != 0)
		return 0;
	P:5("Inline_FoundStart OK");
	data[E_INLINE_DATA_LOCALS] = CodeScanGetMatchStack(scanner);
	data[E_INLINE_DATA_START] = CodeScanGetMatchAddress(scanner);
	data[E_INLINE_DATA_BEYOND] = CodeScanGetMatchHole(scanner, 5);
	data[E_INLINE_DATA_NAME] = CodeScanGetMatchHole(scanner, 0);
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
	data[E_INLINE_DATA_STACK] = CodeScanGetMatchStack(scanner);
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
	Inline_StoreData(data);
	// Restart scanning for the next inline.
	data[E_INLINE_DATA_STATE] = 0;
	return 0;
}

static stock Inline_StoreData(data[E_INLINE_DATA])
{
	// `data[E_INLINE_DATA_NAME]` stores the address of a string with the inline function's name,
	// followed by extra space for storing: a pointer to the name, a pointer to the function, a
	// pointer to the next inline in the linked list of names, and something else?
	new
		header = data[E_INLINE_DATA_NAME];
	// Add a pointer to the function itself.
	AMX_Write(header, data[E_INLINE_DATA_NAME]);
	// Add this to the list.
	AMX_Write(header + cellbytes, YSI_g_sInlineLinkedList);
	YSI_g_sInlineLinkedList = header;
}

public OnCodeInit()
{
	new
		hdr[AMX_HDR];
	GetAmxHeader(hdr);
	YSI_g_sJumpOffset = GetAmxBaseAddress() + hdr[AMX_HDR_COD];
	#emit CONST.pri        Callback_CallHandler
	#emit STOR.pri         YSI_g_sCallbackCallAddress
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
		OP(STACK,              -4)
		OP(CONST_PRI,          ???)
		OP(INVERT)
		OP(INVERT)
		OP(PUSH_PRI)
		OP(PUSH_C,             4)
		OP(CALL,               &ref)
		OP(STOR_S_PRI,         ???)
		OP(STACK,              -4)
		OP(LOAD_S_PRI,         ???)
		OP(STOR_S_PRI,         ???)
		OP(PUSH_C,             INLINE_PATTERN_4)
		OP(PUSH_C,             INLINE_PATTERN_3)
		OP(PUSH_C,             INLINE_PATTERN_2)
		OP(PUSH_C,             INLINE_PATTERN_1)
		OP(PUSH_C,             16)
		OP(CALL,               &I@E)
		OP(JZER,               ???)
		OP(JUMP,               ???)
	);
	CodeScanAddMatcher(scanner, csm1a);
	
	// Unoptimised.
	new csm1b[CodeScanMatcher];
	CodeScanMatcherInit(csm1b, &Inline_FoundStart);
	CodeScanMatcherData(csm1b, ref(data));
	CodeScanMatcherPattern(csm1b,
		OP(STACK,              -4)
		OP(CONST_PRI,          ???)
		OP(INVERT)
		OP(INVERT)
		OP(PUSH_PRI)
		OP(PUSH_C,             4)
		OP(CALL,               &ref)
		OP(STOR_S_PRI,         ???)
		OP(STACK,              -4)
		OP(LOAD_S_PRI,         ???)
		OP(STOR_S_PRI,         ???)
		OP(CONST_PRI,          INLINE_PATTERN_4)
		OP(PUSH_PRI)
		OP(CONST_PRI,          INLINE_PATTERN_3)
		OP(PUSH_PRI)
		OP(CONST_PRI,          INLINE_PATTERN_2)
		OP(PUSH_PRI)
		OP(CONST_PRI,          INLINE_PATTERN_1)
		OP(PUSH_PRI)
		OP(PUSH_C,             16)
		OP(CALL,               &I@E)
		OP(JZER,               ???)
		OP(JUMP,               ???)
	);
	CodeScanAddMatcher(scanner, csm1b);
	
	// Mid point.
	new csm2a[CodeScanMatcher];
	CodeScanMatcherInit(csm2a, &Inline_FoundMid);
	CodeScanMatcherData(csm2a, ref(data));
	CodeScanMatcherPattern(csm2a,
		OP(PUSH_C,             0)
		OP(CALL,               &I@F)
		OP(JZER,               ???)
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
		OP(HEAP,               4)
		OP(STOR_I)
		OP(PUSH_ALT)
	);
	CodeScanAddMatcher(scanner, csm3a);
	
	new csm3b[CodeScanMatcher];
	CodeScanMatcherInit(csm3b, &Inline_FoundVar);
	CodeScanMatcherData(csm3b, ref(data));
	CodeScanMatcherPattern(csm3b,
		OP(ZERO_PRI)
		OP(HEAP,               4)
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
		OP(CONST_PRI,          ???)
		OP(HEAP,               4)
		OP(STOR_I)
		OP(PUSH_ALT)
	);
	CodeScanAddMatcher(scanner, csm4a);
	
	new csm4b[CodeScanMatcher];
	CodeScanMatcherInit(csm4b, &Inline_FoundRef);
	CodeScanMatcherData(csm4b, ref(data));
	CodeScanMatcherPattern(csm4b,
		OP(CONST_PRI,          ???)
		OP(HEAP,               4)
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
		OP(CALL,               &I@L)
		OP(HEAP,               ???)
		OP(JZER,               ???)
	);
	CodeScanAddMatcher(scanner, csm5a);
	
	// Constness
	new csm6a[CodeScanMatcher];
	CodeScanMatcherInit(csm6a, &Inline_FoundConst);
	CodeScanMatcherData(csm6a, ref(data));
	CodeScanMatcherPattern(csm6a,
		OP(PUSH_C,             ???)
		OP(PUSH_C,             4)
		OP(CALL,               &I@K)
	);
	CodeScanAddMatcher(scanner, csm6a);
	
	new csm6b[CodeScanMatcher];
	CodeScanMatcherInit(csm6b, &Inline_FoundConst);
	CodeScanMatcherData(csm6b, ref(data));
	CodeScanMatcherPattern(csm6b,
		OP(CONST_PRI,          ???)
		OP(PUSH_PRI)
		OP(PUSH_C,             4)
		OP(CALL,               &I@K)
	);
	CodeScanAddMatcher(scanner, csm6b);
	
	new csm6c[CodeScanMatcher];
	CodeScanMatcherInit(csm6c, &Inline_FoundConst2);
	CodeScanMatcherData(csm6c, ref(data));
	CodeScanMatcherPattern(csm6c,
		OP(ZERO_PRI)
		OP(PUSH_PRI)
		OP(PUSH_C,             4)
		OP(CALL,               &I@K)
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

Note:

    I just added two variables, so their declaration also exists, but the maths
	above hasn't been updated to reflect this fact.

*/











//#define LAMBDA_i<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0|||0,|||<%9>{%0}(%1)%8;
//#define LAMBDA_ii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1|||0,0,|||<%9>{%0}(%1)%8;
//#define LAMBDA_iii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1,_2|||0,0,0,|||<%9>{%0}(%1)%8;
//#define LAMBDA_iiii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1,_2,_3|||0,0,0,0,|||<%9>{%0}(%1)%8;
//#define LAMBDA_iiiii<%9>{%0}(%1)%8; _DO_LAMBDA|||new _0,_1,_2,_3,_4|||0,0,0,0,0,|||<%9>{%0}(%1)%8;
//
//#define _DO_LAMBDA|||%6|||%5|||<%9>{%0}(%1)%8; LAM@0()%8;{LAM@1();static const YSII[]="@:....";if(I@E(YSII))for(%6;I@F();)while(I@L(%5I@K()))YSI_gInlineRet+=(%0);LAM@2(%9(callback_tag:YSII%1));}

// Make sure there's a space after the "return".
#define return%0({%1}%2)%3; I@=%0({%1}%2)%3;return I@;

// The "INLINE" in the types here will override "PARSER@" to "PARSE@INLINE",
// because there is no colon (well not "because", but it helps).
#define inline%0(%1) MAKE_PARSER(INLINE,ARR:REF:STR:NUM:QAL::INLINE)(%0(%1))()0()#

// Follows the "code-parse.inc" internal structure.  Ugly but required, since we
// are parsing functions, but not at a top level.
#define PARSER@INLINE:%0(%5)%6(%7)$ new _@%6=ref(_:%0(%5)%6(%7) I@O$

#define INLINE_STR(%9,%9,%2,%9)%8$(%0)%1(%3)%4# %8$(%0,%2[YSI_MAX_INLINE_STRING])%1(cellmax,%3)%4s#
#define INLINE_ARR(%9,%9,%2,%9)%8$(%0)%1(%3)%4# %8$(%0,%2[%9])%1(%9,%3)%4a#
#define INLINE_NUM(%9,%9,%2)%8$(%0)%1(%3)%4# %8$(%0,%2)%1(0,%3)%4i#
#define INLINE_REF(%9,%9,%2)%8$(%0)%1(%3)%4# %8$(%0,%2)%1(-1,%3)%4v#

#define INLINE_END(%9)%8$(,%0)%1(%3)%4# %8$#..#%9),F@_@%4:%9=F@_@%4:_@%9;if (I@E()){}else for(new %0;I@F();)while(I@L(%3I@K(%1)))

#define INLINE_NUL(%9)%8$()%1()%4# %8$#..#%9),F@_@%4:%9=F@_@%4:_@%9;if (I@E()){}else for(;I@F();)while(I@L(I@K(%1)))

#define I@O$

#define INLINE_const(%9)%8$(%0)%1(%2) %8$(%0)1(%2)

// Parameter type for passing callbacks about.
#define using%0\32; using
#define usingcallback (@Ik:@Il:I@O$Inline_UP_())
#define usingpublic usingcallback
#define usinginline (@Ik:@Il:I@O$Inline_UI_())
#define usingresolved // Do nothing.



// Detect a `using` parameter that is not the last parameter.
#define @Ik:%9$%0)%1, %0,%1),

// Detect a `using` parameter that is the last parameter.
#define @Il:%9$%0)%1) %0,%1))

// Detect a callback with a tag.
#define @Ir:%9#%1<%0>),F@_@:%2$) @It:%9#%1),F@_@%0:%2$)

// Normally `F@_@` doesn't consume spaces because it is a valid tag on its own.  However, in this
// case we know that extra specifiers after the tag prefix exist so we can check fairly safely.
#define @It:%0),F@_@%9\32;%1:%2$) @It:%0),F@_@%9%1:%2$)

// Detect a callback that starts with "On".  These are often redefined and we
// want to keep the original.
#define @Is:%9#On%0),%2$) %9#On#%0),%2$)

// Callbacks with additional parameters (MUST have matching parameters (y_ini)).
#define @In:%0(%1)),%2$) %0),%2$),.bExtra=true,.extra=%1)

// Move the callback parameter inside the brackets.
#define Inline_UI_(),%0) Inline_UI_(_@%0,_:%0),%0)
#define Inline_UP_(),%0) Inline_UP_(_:@Ir:@Is:@In:#%0),F@_@:I@ I@O$)

#if 0

MyFunc(funcptr<>)
{
	
}

#endif

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

// Old API.
#define Callback_Call(%0,%1) Indirect_Call(%0[0], %0[1], %1)
//#define Callback_Get(%0,%1) Indirect_Call(%0[0], %0[1], %1)
//#define Callback_Release(%0,%1) Indirect_Call(%0[0], %0[1], %1)

__COMPILER_STATIC_ENUM E_INLINE_CALL
{
	/* 0 */ E_INLINE_CALL_NULL,
	/* 1 */ E_INLINE_CALL_HANDLER,
	/* 2 */ E_INLINE_CALL_CLAIM,
	/* 3 */ E_INLINE_CALL_RELEASE,
	/* 4 */ E_INLINE_CALL_TIMER, // To release unneeded inlines.
	/* 5 */ E_INLINE_CALL_SIZE,
	/* 6 */ E_INLINE_CALL_FUNCTION,
	/* 7 */ ResolvedAlloc:E_INLINE_CALL_PARAMS // At least the frame header.
}

static stock Callback_CallHandler(...)
{
	// This is called by `@`, and given the above enum in `INDIRECTION_DATA`.
	// Get the size, and update `INDIRECTION_DATA` to point to the data.
	#emit LOAD.alt         INDIRECTION_DATA    // 2
	#emit CONST.pri        5                   // 4
	#emit LIDX                                 // 5
	#emit PUSH.pri                             // 6
	#emit SHL.C.pri        2                   // 8
	#emit PUSH.pri                             // 9
	#emit XCHG                                 // 10
	#emit ADD.C            28                  // 12
	#emit PUSH.pri                             // 13
	// Grow the stack.
	// Call memcpy (put the native's parameters on the stack beyond `dest`).
	#emit PUSH.S           0xFFFFFFFC          // 15
	#emit PUSH.S           0xFFFFFFF8          // 17
	#emit PUSH.C           0                   // 19
	#emit PUSH.S           0xFFFFFFF4          // 21
	#emit PUSH.pri                             // 22
	#emit PUSH.C           20                  // 24
	#emit SYSREQ.C         memcpy              // 26
	#emit STACK            24                  // 28
	// "jump" in to the code.
	#emit LOAD.S.pri       0xFFFFFFF4          // 30
	#emit ADD.C            0xFFFFFFFC          // 32
	#emit LOAD.I                               // 33
	#emit SCTRL            6                   // 35
	
//Callback_Call_restore_stack:
	// The stack hasn't been restored yet, and we need it.
	#emit NOP                                  // 36
	#emit NOP                                  // 37
	// Padding to account for debug builds.
	// If the code decides to jump back to here, save the stack out again.
	#emit PUSH.S           0xFFFFFFFC          // 39
	#emit PUSH.S           0xFFFFFFF8          // 41
	#emit PUSH.C           0                   // 43
	#emit LCTRL            4                   // 45
	#emit PUSH.pri                             // 46
	#emit PUSH.S           0xFFFFFFF4          // 48
	#emit PUSH.C           20                  // 50
	#emit SYSREQ.C         memcpy              // 52
	#emit LCTRL            5                   // 54
	#emit SCTRL            4                   // 56
	#emit LOAD.pri         I@                  // 58
	#emit RETN                                 // 59
	__COMPILER_NAKED
}

/*-------------------------------------------------------------------------*//**
 * <param name="ctx">The code generation output context.</param>
 * <param name="parameters">Information on the fake parameter types.</param>
 * <param name="count">How many parameters there are.</param>
 * <remarks>
 *  Generates the code which copies the parameters from `Callback_Call` in to
 *  the local stack.  All those parameters are passed by reference, since the
 *  function is a varargs function.  Since an inline function's "input"
 *  parameters are just regular variables on the stack, they all need resolving,
 *  which is what this code does.  Regular variables are dereferenced, and
 *  arryas and strings are fully copied over.
 *
 *  Technically this doesn't ACTUALLY do the copy, but generates the code for
 *  the copy.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Inline_GenerateLocalsCopy(ctx[AsmContext], parameters[], count)
{
	new
		input = 12;
	for (new i = 0; i != count; ++i)
	{
		switch (parameters[i])
		{
		case -1, 0:
		{
			@emit LREF.S.pri       input
			@emit PUSH.pri
		}
		case cellmax:
		{
			@emit STACK            -(YSI_MAX_INLINE_STRING * cellbytes)
			@emit STACK            0
			@emit LOAD.S.pri       input
			@emit MOVS             (YSI_MAX_INLINE_STRING * cellbytes)
		}
		default:
		{
			@emit STACK            -(parameters[i])
			@emit STACK            0
			@emit LOAD.S.pri       input
			@emit MOVS             (parameters[i])
		}
		}
		input += cellbytes;
	}
	// Jump past the postamble, which puts a return address on the stack.
	@emit CALL.label       Inline_Start
}

/*-------------------------------------------------------------------------*//**
 * <param name="ctx">The code generation output context.</param>
 * <param name="parameters">Information on the fake parameter types.</param>
 * <param name="count">How many parameters there are.</param>
 * <remarks>
 *  When the inline function ends, any parameters that were defined as being
 *  passed by reference are copied back.  This is because true locals are never
 *  by reference, so we fake it.  There is one bug with this method - aliased
 *  variables won't work correctly:
 *
 *  <c>
 *      inline Func(&a, &b)
 *      {
 *  	    ++a; 
 *  	    printf("%d", b); 
 *      }
 *      
 *      new a = 10;
 *      Callback_Call(using inline Func, a, a);
 *  </c>
 *
 *  That will print <c>10</c> while the same code with a normal function will
 *  print <c>11</c> thanks to <c>a</c> and <c>b</c> being aliased.  Maybe I
 *  should add a <c>restrict</c> keyword, but even then I don't know how to
 *  solve unrestricted variables (at best I can warn for them).  And this is not
 *  a totally unheard of situation.  I have at least seen this for getting only
 *  a player's height:
 *
 *  <c>
 *      new z;
 *      GetPlayerPos(playerid, z, z, z);
 *  </c>
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

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
				@emit STACK            accumulate
			accumulate = 0;
			@emit POP.pri
			@emit SREF.S.pri       count * cellbytes + 12
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

static stock Inline_GeneratePreamble(ctx[AsmContext], locals)
{
	// This is sort of the start of the code.
	@emit Inline_Start:
	// Set the local frame.
	@emit STACK            0
	@emit LCTRL            5
	@emit XCHG
	@emit ADD.C            locals + 4
	@emit SCTRL            5
	@emit STOR.S.alt       0
	// Get the return address.
	@emit POP.pri
	@emit STOR.S.pri       4
}

static stock Inline_GeneratePostamble(ctx[AsmContext], parameters[], const count, bool:isConst, locals, inlineParams)
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
			@emit STOR.pri         ref(I@)
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
			@emit SCTRL            4
			accumulate = Inline_GenerateLocalsStore(ctx, parameters, count);
			@emit STACK            accumulate + locals - inlineParams
			// Restore the return value.
			@emit LOAD.pri         ref(I@)
		}
		// If we are here, we are in the context of `Callback_Call`, with no
		// locals on the stack.
		@emit STACK            12
		@emit RETN
	}
	else
	{
		@emit STOR.pri         ref(I@)
		if (needStore)
		{
			@emit MOVE.pri
			@emit SCTRL            4
			accumulate = Inline_GenerateLocalsStore(ctx, parameters, count);
			if (accumulate)
				@emit STACK            accumulate
		}
		else
		{
			// Go back down the stack, up to where the inline parameters began,
			// but not including them.  This will set us up the bomb (sorry,
			// couldn't resist).  This will set us up nicely for the jump in to
			// `Callback_CallHandler` for copying the stack back out again.
			@emit MOVE.pri
			@emit ADD.C            inlineParams
			@emit SCTRL            4
		}
		// Jump to `Callback_Call_restore_stack:` to perform common cleanup.
		@emit JUMP             YSI_g_sCallbackCallAddress + 37 * cellbytes
	}
}

static stock Inline_DoRetnGen(ctx[AsmContext], scanner[CodeScanner], data[E_INLINE_DATA])
{
	// Remove the return for the inner loop, since it may now point to an
	// invalid address (in the middle of an OpCode we just wrote out).
	new
		startaddr = data[E_INLINE_DATA_USER],
		endaddrDAT = CodeScanGetMatchHole(scanner, 1) - 8,
		endaddrCOD = endaddrDAT + YSI_g_sJumpOffset,
		nop = _:RelocateOpcode(OP_NOP),
		dctx[DisasmContext];
	// Using the local decompiler, go through the code and remove any jumps to
	// outside of [startaddr, endaddrDAT].  Convert them all to `RETN; NOP`.
	CodeScanGetMatchDisasm(scanner, dctx, CodeScanGetMatchLength(scanner));
	dctx[DisasmContext_end_ip] = endaddrDAT + AMX_HEADER_COD + 16;
	while (DisasmNext(dctx) != DISASM_DONE)
	{
		// Is this a jump?  The only jumps that can get out of this constraint
		// are `JUMP` ones - all others like `JNEQ` etc would be generated by
		// `if` statements and so constrained by syntax.  `JUMP` would come from
		// `break`, `continue`, or `goto`.
		if (DisasmGetOpcode(dctx) == OP_JUMP && !(startaddr <= DisasmGetOperandReloc(dctx) < endaddrDAT))
		{
			AMX_Write(DisasmGetCurIp(dctx) + 4, endaddrCOD);
		}
	}
	endaddrDAT += AMX_HEADER_COD;
	// Now at the end address, write the cleanup and return code.
	if (data[E_INLINE_DATA_STACK])
	{
		AMX_Write(endaddrDAT, _:RelocateOpcode(OP_STACK));
		AMX_Write(endaddrDAT + 4, data[E_INLINE_DATA_STACK]);
	}
	else
	{
		AMX_Write(endaddrDAT, nop);
		AMX_Write(endaddrDAT + 4, nop);
	}
	AMX_Write(endaddrDAT + 8, _:RelocateOpcode(OP_RETN));
	AMX_Write(endaddrDAT + 12, nop);
	// Push the inline address and current frame.
	@emit PUSH.C           data[E_INLINE_DATA_NAME]
	@emit PUSH.C           0
	// Jump past the whole inline code.  Also remove trailing stack codes that
	// would only remove our local data.
	dctx[DisasmContext_end_ip] += 8;
	if (DisasmNext(dctx) != DISASM_DONE && DisasmGetOpcode(dctx) == OP_STACK)
	{
		// Remove any stack cleanup that only deals with the inline function's
		// parameters.
		startaddr = DisasmGetOperand(dctx) - data[E_INLINE_DATA_STACK] + data[E_INLINE_DATA_LOCALS];
		if (startaddr == 0)
		{
			AMX_Write(endaddrDAT + 16, nop);
			AMX_Write(endaddrDAT + 20, nop);
			@emit JUMP             endaddrCOD + 24
		}
		else
		{
			// Less cleanup required, but still some.
			AMX_Write(endaddrDAT + 20, startaddr);
			@emit JUMP             endaddrCOD + 16
		}
	}
	else
	{
		@emit JUMP             endaddrCOD + 16
	}
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
	Inline_GeneratePostamble(ctx, data[E_INLINE_DATA_PARAMETERS], data[E_INLINE_DATA_PARAMETER_COUNT], bool:(data[E_INLINE_DATA_STATE] & 4), data[E_INLINE_DATA_STACK], data[E_INLINE_DATA_LOCALS]);
	Inline_GeneratePreamble(ctx, data[E_INLINE_DATA_STACK]);
	AsmEmitPadding(ctx);
}

public Inline_MaybeFree_(ResolvedAlloc:a)
{
	// `Callback_Get` kills the timer (maybe repeatedly, but that's fine).
	free(Malloc_Reconcile(a));
}

stock Inline_UI_(const func, &ret)
{
	// We use `&ret` instead of `return` so that we can keep the tags correct.  This also passes an
	// address that we know is the bottom of the part of the stack that we need to save for the
	// closure.  The bottom two variables in the stack must be preserved, since they store
	// information about the inline function (name and address), which may be required even in the
	// inline if it is called recursively.
//	assert(numargs() == 1);
//	new
//		ret[3];
//	return
//		// Get the handler.
//		ret[0] = 0,
//		// Get the first item.
//		ret[1] = getarg(1),
//		// Get the parent frame.
//		ret[2] = GetCurrentFramePreviousFrame(),
//		ret;
	// So it turns out - PAWN HAS DESTRUCTORS!  Why did I not know this?  And does it actually help
	// me at all?  No: 
	new
		frm = GetCurrentFramePreviousFrame(),
		ptr = ref(ret);
	while (ptr > frm)
	{
		// Find the frame the pointer is in.  This should just be the previous
		// frame, but we can't really guarantee that.
		frm = GetFramePreviousFrame(frm);
	}
	// Get the space required for the closure.
	new
		closure = frm - ptr + GetFrameHeaderSize(frm) + GetFrameParameterSize(frm),
		Alloc:data = malloc(closure + )
	
	
	ret = _:Malloc_Resolve
}

stock Inline_UP_(const func[])
{
	// Convert a function name to a pointer.
	I@ = GetPublicAddressFromName(func);
}

#endinput

// using inline
(_:_@%0 = Inline_UI_(%0), _@%0)

