#if defined _INC_y_testing
	#endinput
#endif
#define _INC_y_testing

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
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

forward bool:_Testing_End();

#include "..\y_utils"
#include "..\..\YSI_Server\y_stringise"

CHAIN_HOOK(Testing)
#undef CHAIN_ORDER
#define CHAIN_ORDER CHAIN_NEXT(Testing)

#if defined YSI_TESTS
	#if defined INCLUDE_TESTS
		#error Incompatible testing options (YSI_TESTS + INCLUDE_TESTS)
	#endif
	#if !defined RUN_TESTS
		#define RUN_TESTS
	#endif
#endif

#if defined INCLUDE_TESTS
	#define RUN_TESTS
#elseif defined RUN_TESTS
	#define _AUTO_RUN_TESTS
#endif

#if defined LIGHT_TEST_REPORT
	#define TEST_REPORT(%0) H@()
#else
	#define TEST_REPORT(%0) printf(%0)
#endif

#define Y_TESTING_DIALOG_ID (0x7974) // "yt"

static stock const TEST_FAILED[] = "FAIL:";
static stock const TEST_PASSED[] = "PASS!";

#define ASSERT(%0) Testing_Test(%0,"%s %s",STRINGISE__(%0))
#define ASSERT_TRUE(%0) ASSERT(!!%0)
#define ASSERT_FALSE(%0) ASSERT(!%0)
#define ASSERT_NULL(%0) ASSERT_EQ(%0,0)
#define ASSERT_N:%1(%0) ASSERT_EQ(%0,%1)

#define ASK(%0) Testing_Ask(playerid,%0)

const Y_TESTING_TEST_SEARCH = _A<@yQ_>;
const Y_TESTING_PTEST_SEARCH = _A<@_Qy>;
const Y_TESTING_INIT  = _C<@y_Q>;
const Y_TESTING_TEST  = _C<@yQ_>;
const Y_TESTING_SHUT  = _C<@Qy_>;
const Y_TESTING_PINIT = _C<@Q_y>;
const Y_TESTING_PTEST = _C<@_Qy>;
const Y_TESTING_PSHUT = _C<@_yQ>;

stock _y@T(GLOBAL_TAG_TYPES:b, tag = tagof (b))
{
	#pragma unused b
	new ret1[16] = "%s %s (%.2f)";
	new ret2[16] = "%s %s (%d)";
	return (tag == tagof (Float:)) ? ret1 : ret2;
}

stock bool:_@yT(a, GLOBAL_TAG_TYPES:b, op, tag = tagof (b))
{
	if (tag == tagof (Float:))
	{
		switch (op)
		{
		case 0:
			// Approximately equal
			return Float:a - Float:b < 0.01 && Float:b - Float:a < 0.01;
		case 1:
			// Approximately equal
			return Float:a - Float:b >= 0.01 || Float:b - Float:a >= 0.01;
		case 2:
			return Float:a <= Float:b;
		case 3:
			return Float:a <  Float:b;
		case 4:
			return Float:a >= Float:b;
		case 5:
			return Float:a >  Float:b;
		}
	}
	else
	{
		switch (op)
		{
		case 0:
			// Approximately equal
			return a == b;
		case 1:
			// Approximately equal
			return a != b;
		case 2:
			return a <= b;
		case 3:
			return a <  b;
		case 4:
			return a >= b;
		case 5:
			return a >  b;
		}
	}
	return false;
}

// Numbers.
// Just don't do side-effects in assertations!
// `_EQ` and `_NE` now convert to float and check the values are close-enough.
// For ints the subtraction will always be whole, so fail or pass correctly.
#define ASSERT_EQ(%1,%0) Testing_Test(_@yT(J@,(%0),0),_y@T((%0)),STRINGISE__(%1 == %0),(J@=_:(((%0)^(%0))|(%1))))
#define ASSERT_NE(%1,%0) Testing_Test(_@yT(J@,(%0),1),_y@T((%0)),STRINGISE__(%1 != %0),(J@=_:(((%0)^(%0))|(%1))))
#define ASSERT_LE(%1,%0) Testing_Test(_@yT(J@,(%0),2),_y@T((%0)),STRINGISE__(%1 <= %0),(J@=_:(((%0)^(%0))|(%1))))
#define ASSERT_LT(%1,%0) Testing_Test(_@yT(J@,(%0),3),_y@T((%0)),STRINGISE__(%1 <  %0),(J@=_:(((%0)^(%0))|(%1))))
#define ASSERT_GE(%1,%0) Testing_Test(_@yT(J@,(%0),4),_y@T((%0)),STRINGISE__(%1 >= %0),(J@=_:(((%0)^(%0))|(%1))))
#define ASSERT_GT(%1,%0) Testing_Test(_@yT(J@,(%0),5),_y@T((%0)),STRINGISE__(%1 >  %0),(J@=_:(((%0)^(%0))|(%1))))

// Zeroes.
#define ASSERT_ZE(%1) Testing_Test(J@==0,"%s%s(%d)",STRINGISE__(%1==0),(J@=_:(%1)))
#define ASSERT_NZ(%1) Testing_Test(J@!=0,"%s%s(%d)",STRINGISE__(%1!=0),(J@=_:(%1)))

//Strings.
#define ASSERT_SAME(%1,%0) Testing_Test(strlen(%0)?(Q@[0]&&!strcmp(Q@,(%0))):(!Q@[0]),"%s%s(\"%s\")",STRINGISE__(%1 == %0),(strunpack(Q@,(%1)),Q@))
#define ASSERT_DIFF(%1,%0) Testing_Test(strlen(%0)?(!Q@[0]||strcmp(Q@,(%0))):(!!Q@[0]),"%s%s(\"%s\")",STRINGISE__(%1 != %0),(strunpack(Q@,(%1)),Q@))
#define ASSERT_NEAR(%1,%0) Testing_Test(strlen(%0)?(Q@[0]&&!strcmp(Q@,(%0),true)):(!Q@[0]),"%s%s(\"%s\")",STRINGISE__(%1 ~= %0),(strunpack(Q@,(%1)),Q@))

static stock
	YSI_g_sCurTest = 0,
	YSI_g_sCurHeap = 0,
	YSI_g_sFailTests = 0,
	YSI_g_sInTest = false,
	YSI_g_sTestResult = 0,
	YSI_g_sFailMessage[512],
	YSI_g_sPlayer = cellmax,
	bool:YSI_gTestComplete = false,
	bool:YSI_g_sAsked = false,
	YSI_g_sTests = 0,
	YSI_g_sChecks = 0,
	YSI_g_sPlayerFails = 0,
	YSI_g_sFails = 0,
	YSI_g_sCurrentGroup[32],
	Text:YSI_g_sQuestionTD = Text:INVALID_TEXT_DRAW;

stock
	YSI_gCurTestName[FUNCTION_LENGTH];

static stock const
	YSI_gscStringS[] = "s",
	YSI_gscString_[] = "";

#define Y_TESTING_S(%0) ((%0) == 1 ? YSI_gscString_ : YSI_gscStringS)

// Each function type has a dedicated three letter prefix associated with it:
//   
//   y_Q Init
//   yQ_ Test
//   Qy_ Close
//   
//   Q_y PInit
//   _Qy PTest
//   _yQ PClose
//   
// An "@" symbol is added to complete the four letter prefix, with its location
// determined by the function type - publics lead (obviously), static and stock
// implementations trail.  So the public function called "@y_Q<test>" would call
// the static function "y_Q@<test>".

#if defined RUN_TESTS
	#define TEST_INIT__%1() _F<@y_Q>%1();_F<@y_Q>%1()
	#define YTEST_PID0:%8$_F<@Q_y>%1();_F<@Q_y>%1() %8$_F<@y_Q>%1();_F<@y_Q>%1()
	
	// We can't do `#define YTEST_PID1 TEST__` or something similar as then
	// the result will be compressed in to `TEST__` and `YTEST_ARGS` will be
	// checked before the expansion of `TEST__`.  Thus we must exactly copy the
	// results of all these macros, with the addition of `%8$` of course.
	#if !__COMPILER_STRING_PACKING
		#define TEST__%1() bool:_F<@yQ_>%1();bool:_F<@yQ_>%1()for(_Testing_Start(_:"  "#%1),TEST_REPORT("*** Test %s start",YSI_gCurTestName);__once;_Testing_End())_F<yQ_@>%1();static _F<yQ_@>%1()
		#define YTEST_PID1:%8$bool:_F<@_Qy>%1();bool:_F<@_Qy>%1()%9(%9)%9;%9(%9) %8$bool:_F<@yQ_>%1();bool:_F<@yQ_>%1()for(_Testing_Start(_:"  "#%1),TEST_REPORT("*** Test %s start",YSI_gCurTestName);__once;_Testing_End())_F<yQ_@>%1();static _F<yQ_@>%1()
	#elseif cellbits == 32
		// Ensure there is always sufficient spacefor the failures linked list.
		#define TEST__%1() bool:_F<@yQ_>%1();bool:_F<@yQ_>%1()for(_Testing_Start(_:"        "#%1),TEST_REPORT("*** Test %s start",YSI_gCurTestName);__once;_Testing_End())_F<yQ_@>%1();static _F<yQ_@>%1()
		#define YTEST_PID1:%8$bool:_F<@_Qy>%1();bool:_F<@_Qy>%1()%9(%9)%9;%9(%9) %8$bool:_F<@yQ_>%1();bool:_F<@yQ_>%1()for(_Testing_Start(_:"        "#%1),TEST_REPORT("*** Test %s start",YSI_gCurTestName);__once;_Testing_End())_F<yQ_@>%1();static _F<yQ_@>%1()
	#elseif cellbits == 64
		#define TEST__%1() bool:_F<@yQ_>%1();bool:_F<@yQ_>%1()for(_Testing_Start(_:"                "#%1),TEST_REPORT("*** Test %s start",YSI_gCurTestName);__once;_Testing_End())_F<yQ_@>%1();static _F<yQ_@>%1()
		#define YTEST_PID1:%8$bool:_F<@_Qy>%1();bool:_F<@_Qy>%1()%9(%9)%9;%9(%9) %8$bool:_F<@yQ_>%1();bool:_F<@yQ_>%1()for(_Testing_Start(_:"                "#%1),TEST_REPORT("*** Test %s start",YSI_gCurTestName);__once;_Testing_End())_F<yQ_@>%1();static _F<yQ_@>%1()
	#else
		#error Unsupported packed string size.
	#endif
	#define TEST_CLOSE__%1() _F<@Qy_>%1();_F<@Qy_>%1()
	#define YTEST_PID2:%8$_F<@_yQ>%1();_F<@_yQ>%1() %8$_F<@Qy_>%1();_F<@Qy_>%1()
	
	// Default to having `playerid`, and fall back to no players otherwise.
	#define PTEST_INIT__%1(%2) u@(u[_:YTEST_PID0:YTEST_DROP:u@$_F<@Q_y>%1(%2);_F<@Q_y>%1(%2)
	#if !__COMPILER_STRING_PACKING
		#define PTEST__%1(%2) u@(u[_:YTEST_PID1:YTEST_ARGS:u@$bool:_F<@_Qy>%1(%2);bool:_F<@_Qy>%1(%2)for(_Testing_Start(_:"  "#%1),TEST_REPORT("*** Player Test %s start",YSI_gCurTestName);__once;_Testing_End())_F<_Qy@>%1(%2);static _F<_Qy@>%1(%2)
	#elseif cellbits == 32
		// Ensure there is always sufficient spacefor the failures linked list.
		#define PTEST__%1(%2) u@(u[_:YTEST_PID1:YTEST_ARGS:u@$bool:_F<@_Qy>%1(%2);bool:_F<@_Qy>%1(%2)for(_Testing_Start(_:"        "#%1),TEST_REPORT("*** Player Test %s start",YSI_gCurTestName);__once;_Testing_End())_F<_Qy@>%1(%2);static _F<_Qy@>%1(%2)
	#elseif cellbits == 64
		#define PTEST__%1(%2) u@(u[_:YTEST_PID1:YTEST_ARGS:u@$bool:_F<@_Qy>%1(%2);bool:_F<@_Qy>%1(%2)for(_Testing_Start(_:"                "#%1),TEST_REPORT("*** Player Test %s start",YSI_gCurTestName);__once;_Testing_End())_F<_Qy@>%1(%2);static _F<_Qy@>%1(%2)
	#else
		#error Unsupported packed string size.
	#endif
	#define PTEST_CLOSE__%1(%2) u@(u[_:YTEST_PID2:YTEST_DROP:u@$_F<@_yQ>%1(%2);_F<@_yQ>%1(%2)
	
	#define TEST_COMPILE__%1() forward _F<Q@y_>%1();public _F<Q@y_>%1(){if(FALSE)_F<Q@_y>%1();Debug_Warning("Compile test " #%1 " called.");}static stock _F<Q@_y>%1()

	// Use the `PTEST` definitions by default, as they can now detect no
	// `playerid` and fall back to `TEST` when it isn't present.
	#define @testinit(%2)%0(%1) PTEST_INIT__ %0(%1)<%2>
	#define @test(%2)%0(%1) PTEST__ %0(%1)<%2>
	#define @testclose(%2)%0(%1) PTEST_CLOSE__ %0(%1)<%2>
#else
	#define TEST_INIT__%1(%2) static stock _F<y_Q@>%1(%2)
	#define TEST__%1(%2) static stock bool:_F<yQ_@>%1(%2)
	#define TEST_CLOSE__%1(%2) static stock _F<Qy_@>%1(%2)
	
	#define PTEST_INIT__%1(%2) static stock _F<Q_y@>%1(%2)
	#define PTEST__%1(%2) static stock bool:_F<_Qy@>%1(%2)
	#define PTEST_CLOSE__%1(%2) static stock _F<_yQ@>%1(%2)

	// Use the `PTEST` definitions by default, as they can now detect no
	// `playerid` and fall back to `TEST` when it isn't present.
	#define @testinit(%2)%0(%1) PTEST_INIT__ %0(%1)
	#define @test(%2)%0(%1) PTEST__ %0(%1)
	#define @testclose(%2)%0(%1) PTEST_CLOSE__ %0(%1)
#endif

// Deal with extra parameters from `@hook`.
#define YTEST_DROP:%8$%0(%1);%0(%1)<%9> %8$%0(%1);%0(%1)
#define YTEST_ARGS:%8$%0(%1);%0(%1)for(%2(%3)%4)%5;%6(%7)<%9> %8$%0(%1);%0(%1)for(%2(%3,%9)%4)%5;%6(%7)

#if defined NO_PLAYER_TESTS
	#undef PTEST_INIT__
	#undef PTEST__
	#undef PTEST_CLOSE__
	#undef ASK

	#define YSI_NO_KEYWORD_PTestInit
	#define YSI_NO_KEYWORD_PTest
	#define YSI_NO_KEYWORD_PTestClose
#endif

#if YSI_KEYWORD(TestInit)
	#define TestInit:%1() TEST_INIT__ %1()
#endif
#if YSI_KEYWORD(Test)
	#define Test:%1() TEST__ %1()
#endif
#if YSI_KEYWORD(TestClose)
	#define TestClose:%1() TEST_CLOSE__ %1()
#endif
#if YSI_KEYWORD(TestBeforeEach)
	#define TestBeforeEach:%1() TEST_BEFORE_EACH__ %1()
#endif
#if YSI_KEYWORD(TestAfterEach)
	#define TestAfterEach:%1() TEST_AFTER_EACH__ %1()
#endif
#if YSI_KEYWORD(PTestInit)
	#define PTestInit:%1(%2) PTEST_INIT__ %1(%2)
#endif
#if YSI_KEYWORD(PTest)
	#define PTest:%1(%2) PTEST__ %1(%2)
#endif
#if YSI_KEYWORD(PTestClose)
	#define PTestClose:%1(%2) PTEST_CLOSE__ %1(%2)
#endif
#if YSI_KEYWORD(TestCompile)
	#define TestCompile:%1() TEST_COMPILE__ %1()
#endif

// 32-bit prefixes.
#define @y_Q%0\32; @y_Q
#define @yQ_%0\32; @yQ_
#define @Qy_%0\32; @Qy_
#define y_Q@%0\32; y_Q@
#define yQ_@%0\32; yQ_@
#define Qy_@%0\32; Qy_@

#define @Q_y%0\32; @Q_y
#define @_Qy%0\32; @_Qy
#define @_yQ%0\32; @_yQ
#define Q_y@%0\32; Q_y@
#define _Qy@%0\32; _Qy@
#define _yQ@%0\32; _yQ@

#define y@Q_%0\32; y@Q_
#define y@_Q%0\32; y@_Q
#define Q@_y%0\32; Q@_y
#define Q@y_%0\32; Q@y_

// 64-bit prefixes.
#define @y_Q0000%0\32; @y_Q0000
#define @yQ_0000%0\32; @yQ_0000
#define @Qy_0000%0\32; @Qy_0000
#define y_Q@0000%0\32; y_Q@0000
#define yQ_@0000%0\32; yQ_@0000
#define Qy_@0000%0\32; Qy_@0000

#define @Q_y0000%0\32; @Q_y0000
#define @_Qy0000%0\32; @_Qy0000
#define @_yQ0000%0\32; @_yQ0000
#define Q_y@0000%0\32; Q_y@0000
#define _Qy@0000%0\32; _Qy@0000
#define _yQ@0000%0\32; _yQ@0000

#define y@Q_0000%0\32; y@Q_000
#define y@_Q0000%0\32; y@_Q000
#define Q@_y0000%0\32; Q@_y000
#define Q@y_0000%0\32; Q@y_000

// Currently unused.
//#define _@Qy%0\32; _@Qy
//#define _@yQ%0\32; _@yQ
//#define y_@Q%0\32; y_@Q
//#define yQ@_%0\32; yQ@_
//#define Qy@_%0\32; Qy@_
//#define Q_@y%0\32; Q_@y
//#define _Q@y%0\32; _Q@y
//#define _y@Q%0\32; _y@Q
//
//#define _@Qy0000%0\32; _@Qy0000
//#define _@yQ0000%0\32; _@yQ0000
//#define y_@Q0000%0\32; y_@Q0000
//#define yQ@_0000%0\32; yQ@_0000
//#define Qy@_0000%0\32; Qy@_0000
//#define Q_@y0000%0\32; Q_@y0000
//#define _Q@y0000%0\32; _Q@y0000
//#define _y@Q0000%0\32; _y@Q0000

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the current function.</param>
 * <remarks>
 *   Gets a reference to the 
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock _Testing_Start(const name[], run = true, const group[] = "", slow = false) <y_testing_phase : y_testing_phase_determine>
{
	new ret = 0;
#if defined JUST_TEST
	#pragma unused slow, group
	// Never skip a `JUST_TEST` test, even if it is slow and we don't want
	// slow tests.  Always `[2]`, even with string packing.
	if (!run || strcmp(name[2], #JUST_TEST))
#elseif defined RUN_SLOW_TESTS
	#pragma unused name, slow
	if (!run)
#else
	#pragma unused name
	if (!run || slow)
#endif
	{
		// Never run.
		ret = 2;
	}
#if !defined JUST_TEST
	else switch (YSI_g_sCurrentGroup[0])
	{
	case '\0':
	{
		// Default (global) group.
		if (group[0])
		{
			ret = 1;
		}
	}
	case cellmin:
	{
		// Find a new group.
		YSI_g_sCurrentGroup[0] = '\0',
		strcat(YSI_g_sCurrentGroup, group);
		TEST_REPORT("******************************************");
		TEST_REPORT("****                                  ****");
		TEST_REPORT("**** Group: %25s ****", YSI_g_sCurrentGroup);
		TEST_REPORT("****                                  ****");
		TEST_REPORT("******************************************");
		TEST_REPORT(YSI_SPACE);
	}
	default:
	{
		// Any other group.
		if (strcmp(YSI_g_sCurrentGroup, group))
		{
			ret = 1;
		}
	}
	}
#endif
	{}
	// Now double return, to exit the call site as well.
	#emit LOAD.S.alt       ret
	#emit LOAD.S.pri       0
	#emit SCTRL            __frm
	#emit SCTRL            __stk
	#emit MOVE.pri
	#emit RETN
}

stock _Testing_Start(const name[], run = true, const group[] = "", slow = false) <y_testing_phase : y_testing_phase_call>
{
	#pragma unused run, group, slow
	YSI_gTestComplete = false;
	// Gets a reference to the name string, which is also an intrusive linked
	// list of failures.
	setarg(0, 0, 0); // Bypass `const`.
	setarg(0, 1, 0); //name[0] = name[1] = 0,
	YSI_g_sCurTest = AMX_Ref(name[0]);
	// My very first legitimate usage of `heapspace()` for something other than
	// as a dummy no-op function call!  I'm actually quite happy I found a use
	// for it!  Add 12 for the parameters to this function that we're about to
	// forget about (i.e the stack space we're about to free up).
	YSI_g_sCurHeap = heapspace() + 3 * cellbytes;
	Debug_Print3("_Testing_Start %d %d %s = %d", name[0], name[1], name[2], YSI_g_sCurTest);
	YSI_gCurTestName[0] = '\0',
	StrCpy(YSI_gCurTestName, name[2]);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to ask a question to.</param>
 * <param name="str">What to ask.</param>
 * <param name="va_args">Additional data.</param>
 * <remarks>
 *   Calls a dialog to ask the player if the given test actually passed.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if !defined DIALOG_STYLE
	#define DIALOG_STYLE: _:
#endif

#if !defined NO_PLAYER_TESTS
	native bool:YSI_ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE:style, const caption[], const info[], const button1[], const button2[]) = ShowPlayerDialog;

	stock Testing_Ask(playerid, const str[] = "", GLOBAL_TAG_TYPES:...)
	{
			#pragma unused str
			new
				i = 0,
				end = 0; // 12 + 4 + 4.
			// Get the stack position after `playerid`.
			#emit ADDR.pri         __param1_offset
			#emit STOR.S.pri       end
			// Get the stack position after everything.
			#emit ADDR.pri         __param0_offset
			#emit LOAD.S.alt       __args_offset
			#emit ADD
			#emit STOR.S.pri       i
			while (i > end)
			{
				i -= cellbytes;
				#emit LREF.S.pri       i
				#emit PUSH.pri
			}
			{}
			const size = sizeof (YSI_g_sFailMessage);
			#emit PUSH.C           size
			#emit PUSH.C           YSI_g_sFailMessage
			#emit LOAD.S.pri       __args_offset
			#emit ADD.C            __1_cell
			#emit PUSH.pri
			#emit SYSREQ.C         format
			// Remove the data from the stack.
			#emit POP.alt
			#emit LCTRL            __stk
			#emit ADD
			#emit SCTRL            __stk
			//format(YSI_g_sFailMessage, sizeof (YSI_g_sFailMessage), str, ___(2));
		#if defined YSI_DIALOG_ASK
			YSI_ShowPlayerDialog(playerid, Y_TESTING_DIALOG_ID, DIALOG_STYLE_MSGBOX, "Did the test pass?", YSI_g_sFailMessage, "Yes", "No");
		#else
			if (YSI_g_sQuestionTD != Text:INVALID_TEXT_DRAW)
			{
				TextDrawDestroy(YSI_g_sQuestionTD);
			}
			#if !defined TEXT_DRAW_FONT
				#define TEXT_DRAW_FONT: _:
			#endif
			#if !defined TEXT_DRAW_ALIGN
				#define TEXT_DRAW_ALIGN: _:
			#endif
			format(YSI_g_sFailMessage, sizeof (YSI_g_sFailMessage), "%s~n~                   ~r~(~k~~CONVERSATION_YES~/~k~~CONVERSATION_NO~)", YSI_g_sFailMessage),
			YSI_g_sQuestionTD = TextDrawCreate(400.0, 350.0, YSI_g_sFailMessage),
			TextDrawFont(YSI_g_sQuestionTD, TEXT_DRAW_FONT:1),
			TextDrawLetterSize(YSI_g_sQuestionTD, 0.3, 1.0),
			TextDrawTextSize(YSI_g_sQuestionTD, 600.0, 50.0),
			TextDrawSetOutline(YSI_g_sQuestionTD, 0),
			TextDrawSetShadow(YSI_g_sQuestionTD, 0),
			TextDrawAlignment(YSI_g_sQuestionTD, TEXT_DRAW_ALIGN:1),
			TextDrawColor(YSI_g_sQuestionTD, 0xFF7F37FF),
			TextDrawBackgroundColor(YSI_g_sQuestionTD, 0xFFFFFFFF),
			TextDrawBoxColor(YSI_g_sQuestionTD, 0x000000AA),
			TextDrawUseBox(YSI_g_sQuestionTD, true),
			TextDrawSetProportional(YSI_g_sQuestionTD, true),
			TextDrawSetSelectable(YSI_g_sQuestionTD, false),
			TextDrawShowForPlayer(playerid, YSI_g_sQuestionTD);
		#endif
			YSI_g_sAsked = true;
	}
#endif

stock Testing_Test(bool:x, const str[] = "", GLOBAL_TAG_TYPES:...)
{
	#pragma unused str
	Debug_Print3("Testing_Test called: %i, \"%s\"", x, str);
	++YSI_g_sChecks;
	static
		Testing_Test_msg[6],
		Testing_Test_FRM = 0,
		Testing_Test_RET = 0;
	if (!x)
	{
		++YSI_g_sFails;
#if defined INCLUDE_TESTS || defined RUN_TESTS
		Testing_Test_msg = TEST_FAILED;
#else
		// Awkward way to avoid `#emit` in `#if` bug, without an unreachable
		// code warning.
		if (TRUE) return;
#endif
	}
	else
	{
#if defined TEST_SHOW_PASSES && (defined INCLUDE_TESTS || defined RUN_TESTS)
		Testing_Test_msg = TEST_PASSED;
#else
		return;
#endif
	}
	{}
	// Modify the first two parameters to match the following call:
	//  
	//  Debug_PrintT(str, msg, ___(2));
	//  
	#emit LOAD.S.pri       __param1_offset
	#emit STOR.S.pri       __param0_offset
	#emit CONST.pri        Testing_Test_msg
	#emit STOR.S.pri       __param1_offset
	#emit POP.pri
	#emit STOR.pri         Testing_Test_FRM
	#emit POP.pri
	#emit STOR.pri         Testing_Test_RET
	#emit SYSREQ.C         printf
	#emit PUSH             Testing_Test_RET
	#emit PUSH             Testing_Test_FRM
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the current function.</param>
 * <remarks>
 *   Gets a reference to the 
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:_Testing_End()
{
	YSI_gTestComplete = true;
	new
		space = heapspace();
	++YSI_g_sChecks;
	if (YSI_g_sCurHeap != space)
	{
#if defined INCLUDE_TESTS || defined RUN_TESTS
		++YSI_g_sFails;
		printf("%s Heap allocation leak - was: %d, now: %d", TEST_FAILED, YSI_g_sCurHeap, space);
#endif
	}
	TEST_REPORT(YSI_SPACE);
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <param name="tests">Number of tests run.</param>
 * <param name="fails">Number of tests which failed.</param>
 * <param name="buffer">The name of the first test which failed.</param>
 * <returns>
 *   Wether all tests were sucessful or not.
 * </returns>
 * <remarks>
 *   -
 *
 * native Testing_Run(&amp;tests, &amp;fails, buffer[33] = "");
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Testing_Run(&tests, &checks, &fails, const lastfail[33] = "", bool:p = false)
{
	Server_DisableLongCall();
	Debug_Print3("bool:Testing_Run called: %i, %i, \"%s\", %i", tests, fails, lastfail, p);
	#pragma unused p, lastfail
#if defined RUN_TESTS
	Debug_Print2("Testing_Run() called");
	new
		bool:grouping,
		tmp,
		idx = 0,
		entry,
		buffer[FUNCTION_LENGTH];
	YSI_g_sCurTest = YSI_g_sFailTests = 0;
	#if defined JUST_TEST_GROUP
		YSI_g_sCurrentGroup = JUST_TEST_GROUP;
	#else
		YSI_g_sCurrentGroup[0] = '\0';
	#endif
	do
	{
		grouping = false;
		while ((idx = AMX_GetPublicEntryPrefix(idx, entry, Y_TESTING_TEST_SEARCH)))
		{
			AMX_GetStringFromEntry(entry, buffer);
			if (AMX_Read(entry) == 0)
			{
				// Previously finished test.
				continue;
			}
			state y_testing_phase : y_testing_phase_determine;
			#emit PUSH.C                    0
			#emit LCTRL                     __cip
			#emit ADD.C                     __9_cells
			#emit LCTRL                     __jmp
			#emit PUSH.pri
			#emit LREF.S.pri                entry
			#emit SCTRL                     __cip
			#emit STOR.S.pri                tmp
			switch (tmp)
			{
			#if defined JUST_TEST_GROUP
				case 1, 2:
			#else
				case 1:
				{
					// Skip for now.
					grouping = true;
					continue;
				}
				case 2:
			#endif
				{
					// Skip forever.
					AMX_Write(entry, 0);
					continue;
				}
			}
			state y_testing_phase : y_testing_phase_call;
			AMX_GetStringFromEntry(entry, buffer);
			Server_EnableLongCall();
			Server_RestartLongCall();
			// Call the setup function if there is one.
			buffer[0] = Y_TESTING_INIT;
			R@(buffer, YSI_EMPTY);
			// Call the test.
			buffer[0] = Y_TESTING_TEST;
			fails = YSI_g_sFails;
			Debug_Print5("Testing_Run(): Calling %s", Unpack(buffer[1]));
			YSI_g_sInTest = true,
			// Don't use `entry` here as a pointer directly, because then we
			// don't get any `amx_Exec` protections against crashes in tests.
			R@(buffer, YSI_EMPTY),
			YSI_g_sInTest = false;
			++YSI_g_sTests;
			if (!YSI_gTestComplete)
			{
#if defined INCLUDE_TESTS || defined RUN_TESTS
				++YSI_g_sFails;
				TEST_REPORT(YSI_SPACE);
				TEST_REPORT("%s %s", TEST_FAILED, "Test did not complete (possible crash).");
				TEST_REPORT(YSI_SPACE);
#endif
			}
			if (YSI_g_sFails != fails)
			{
				AMX_Write(YSI_g_sCurTest, YSI_g_sFailTests),
				AMX_Write(YSI_g_sCurTest + cellbytes, YSI_g_sFails - fails),
				YSI_g_sFailTests = YSI_g_sCurTest;
			}
#if !defined TEST_SHOW_PASSES
			else
			{
				TEST_REPORT(TEST_PASSED);
				TEST_REPORT(YSI_SPACE);
			}
#endif
			buffer[0] = Y_TESTING_SHUT;
			R@(buffer, YSI_EMPTY);
			Server_DisableLongCall();
			// Delete the pointer, which may have moved due to tests playing
			// with headers.
			buffer[0] = Y_TESTING_TEST;
			strunpack(buffer, buffer);
			if (AMX_GetPublicEntry(0, entry, buffer))
			{
				AMX_Write(entry, 0);
			}
		}
		YSI_g_sCurrentGroup[0] = cellmin;
	}
	while (grouping);
	tests = YSI_g_sTests;
	checks = YSI_g_sChecks;
	fails = YSI_g_sFails;
	Server_EnableLongCall();
	Server_RestartLongCall();
	return fails == 0;
#else
	#pragma unused tests, fails, lastfail
	return true;
#endif
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to test on.</param>
 * <param name="idx">Next test to run.</param>
 * <param name="tests">Number of tests run.</param>
 * <param name="checks">Number of checks made.</param>
 * <param name="fails">Number of tests which failed.</param>
 * <param name="buffer">The name of the first test which failed.</param>
 * <returns>
 *   Wether all tests were sucessful or not.
 * </returns>
 * <remarks>
 *   -
 *
 * native bool:Testing_Player(playerid, &amp;idx, &amp;tests, &amp;fails, lastfail[33] = "", bool:p = false);
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if !defined NO_PLAYER_TESTS
	stock bool:Testing_Player(playerid, &idx, &tests, &checks, &fails, const lastfail[33] = "", bool:p = false)
	{
		if (YSI_g_sPlayer == cellmax && !IsPlayerNPC(playerid)) //!Player_IsNPC(playerid))
		{
#if !defined LIGHT_TEST_REPORT
			Server_PrintIntroMessage("       STARTING PLAYER TESTS..."),
			Server_FinishIntroMessage();
#endif
			YSI_g_sTests = 0;
			YSI_g_sChecks = 0;
			YSI_g_sFails = 0;
			Testing_Next(playerid);
		}
	}

	#if !defined RUN_TESTS || !defined _AUTO_RUN_TESTS
		stock
	#endif
	Testing_Next(playerid)
	{
		if (YSI_g_sQuestionTD != Text:INVALID_TEXT_DRAW)
		{
			TextDrawDestroy(YSI_g_sQuestionTD);
			YSI_g_sQuestionTD = Text:INVALID_TEXT_DRAW;
		}
		Debug_Print2("Testing_Next() called");
		YSI_g_sInTest = false;
		new
			entry,
			tmp,
			next,
			buffer[FUNCTION_LENGTH];
		static
			bool:grouping;
		for ( ; ; )
		{
			// Get the last test (nicely fails for cellmax).
			if ((YSI_g_sPlayer = AMX_GetPublicEntryPrefix(YSI_g_sPlayer, entry, Y_TESTING_PTEST_SEARCH)))
			{
				AMX_GetStringFromEntry(entry, buffer);
				// Call the shutdown function if there is one.
				buffer[0] = Y_TESTING_PSHUT;
				Debug_Print5("Testing_Next(): Calling %s", Unpack(buffer));
				R@(buffer, "i", playerid);
				// Remove the test from the header.  This just uses normal
				// pointer writes, unless any player tests start messing with
				// the header (they shouldn't, as they are run after codegen).
				#emit ZERO.pri
				#emit SREF.S.pri                entry
			}
			// Update fail counts.
			if (YSI_g_sPlayerFails != YSI_g_sFails)
			{
				AMX_Write(YSI_g_sCurTest, YSI_g_sFailTests),
				AMX_Write(YSI_g_sCurTest + cellbytes, YSI_g_sFails - YSI_g_sPlayerFails),
				YSI_g_sFailTests = YSI_g_sCurTest,
				YSI_g_sPlayerFails = YSI_g_sFails;
			}
Testing_Next_retry:
			// Get the new test, but don't store the index.
			if ((next = AMX_GetPublicEntryPrefix(YSI_g_sPlayer, entry, Y_TESTING_PTEST_SEARCH)))
			{
				if (AMX_Read(entry) == 0)
				{
					// Previously finished test.
					YSI_g_sPlayer = next;
					goto Testing_Next_retry;
				}
				state y_testing_phase : y_testing_phase_determine;
				#emit PUSH.S                    playerid
				#emit PUSH.C                    __1_cell
				#emit LCTRL                     __cip
				#emit ADD.C                     __9_cells
				#emit LCTRL                     __jmp
				#emit PUSH.pri
				#emit LREF.S.pri                entry
				#emit SCTRL                     __cip
				#emit STOR.S.pri                tmp
				switch (tmp)
				{
				#if defined JUST_TEST_GROUP
					case 1, 2:
				#else
					case 1:
					{
						// Skip for now.
						YSI_g_sPlayer = next;
						grouping = true;
						goto Testing_Next_retry;
					}
					case 2:
				#endif
					{
						// Skip forever.
						AMX_Write(entry, 0);
						YSI_g_sPlayer = next;
						goto Testing_Next_retry;
					}
				}
				state y_testing_phase : y_testing_phase_call;
				AMX_GetStringFromEntry(entry, buffer);
				++YSI_g_sTests;
				YSI_g_sAsked = false;
				// Call the setup function if there is one.
				buffer[0] = Y_TESTING_PINIT;
				Debug_Print5("Testing_Next(): Calling %s", Unpack(buffer));
				R@(buffer, "i", playerid);
				// Call the test.
				buffer[0] = Y_TESTING_PTEST;
				Debug_Print5("Testing_Next(): Calling %s", Unpack(buffer));
				YSI_g_sInTest = true,
				// Don't use `entry` here as a pointer directly, because then we
				// don't get any `amx_Exec` protections against crashes in tests.
				R@(buffer, "i", playerid);
			}
			else if (grouping)
			{
				grouping = false;
				YSI_g_sPlayer = 0;
				YSI_g_sCurrentGroup[0] = cellmin;
				goto Testing_Next_retry;
			}
			else
			{
				YSI_g_sAsked = true;
				// No more tests.
				#if defined YSI_DIALOG_ASK
					printf("*** Test%s: %d, Check%s: %d, Fail%s: %d", Y_TESTING_S(YSI_g_sTests), YSI_g_sTests, Y_TESTING_S(YSI_g_sChecks), YSI_g_sChecks, Y_TESTING_S(YSI_g_sFails), YSI_g_sFails);
				#else
					printf("*** Test%s: %d, Check%s: %d, Fail%s: ???", Y_TESTING_S(YSI_g_sTests), YSI_g_sTests, Y_TESTING_S(YSI_g_sChecks), YSI_g_sChecks, Y_TESTING_S(YSI_g_sFails));
				#endif
				if (YSI_g_sFails)
				{
					// List all the failing tests, along with the number of "ASSERT"s
					// that didn't pass.
					while (YSI_g_sFailTests != 0)
					{
						printf("    - %s (%d)", AMX_Deref(YSI_g_sFailTests + 2 * cellbytes), AMX_Read(YSI_g_sFailTests + cellbytes)),
						YSI_g_sFailTests = AMX_Read(YSI_g_sFailTests);
					}
					print(YSI_SPACE);
				}
				else
				{
					#if !defined LIGHT_TEST_REPORT
						#if defined YSI_DIALOG_ASK
							Server_PrintIntroMessage("       ALL PLAYER TESTS PASSED!"),
							Server_FinishIntroMessage();
						#else
							Server_PrintIntroMessage("       PLEASE NOTE FAILED TESTS."),
							Server_FinishIntroMessage();
						#endif
					#endif
				}
				R@("OnPlayerTestsComplete", "iiii", playerid, YSI_g_sTests, YSI_g_sChecks, YSI_g_sFails);
			}
			// If the test needs a player but doesn't ask them anything
			// then we can't wait for "OnDialogResponse" to run the next
			// one.
			if (YSI_g_sAsked)
			{
				break;
			}
			else if (YSI_g_sPlayerFails == YSI_g_sFails)
			{
				TEST_REPORT(TEST_PASSED);
				TEST_REPORT(YSI_SPACE);
			}
		}
	}
	
	#if defined YSI_DIALOG_ASK
		public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
		{
			if (dialogid == Y_TESTING_DIALOG_ID)
			{
				++YSI_g_sChecks;
				if (response)
				{
					// Pass.
					TEST_REPORT(TEST_PASSED);
					TEST_REPORT(YSI_SPACE);
				}
				else
				{
					// Fail.
					TEST_REPORT("%s %s", TEST_FAILED, YSI_g_sFailMessage);
					++YSI_g_sFails;
				}
				Testing_Next(playerid);
				return 1;
			}
			#if defined Testing_OnDialogResponse
				return Testing_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
			#else
				return 1;
			#endif
		}
		
		#if defined _ALS_OnDialogResponse
			#undef OnDialogResponse
		#else
			#define _ALS_OnDialogResponse
		#endif
		#define OnDialogResponse Testing_OnDialogResponse
		#if defined Testing_OnDialogResponse
			forward Testing_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
		#endif
	#else
		#if !defined KEY
			#define KEY: _:
		#endif
		public OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys)
		{
			// TODO: Test if we are in a test before parsing the keys.
			if ((newkeys & KEY_NO) && !(oldkeys & KEY_NO))
			{
					// Fail.
					++YSI_g_sChecks;
					TEST_REPORT("%s %s", TEST_FAILED, YSI_g_sFailMessage);
					++YSI_g_sFails;
					Testing_Next(playerid);
				#if defined Testing_OnPlayerKeyStateChange
					return Testing_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
				#else
					return 1;
				#endif
			}
			else if ((newkeys & KEY_YES) && !(oldkeys & KEY_YES))
			{
					// Pass.
					TEST_REPORT(TEST_PASSED);
					TEST_REPORT(YSI_SPACE);
					Testing_Next(playerid);
				#if defined Testing_OnPlayerKeyStateChange
					return Testing_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
				#else
					return 1;
				#endif
			}
			else
			{
				#if defined Testing_OnPlayerKeyStateChange
					return Testing_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
				#else
					return 0;
				#endif
			}
		}
		
		#if defined _ALS_OnPlayerKeyStateChange
			#undef OnPlayerKeyStateChange
		#else
			#define _ALS_OnPlayerKeyStateChange
		#endif
		#define OnPlayerKeyStateChange Testing_OnPlayerKeyStateChange
		#if defined Testing_OnPlayerKeyStateChange
			forward Testing_OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys);
		#endif
	#endif
#endif

forward OnTestsComplete(tests, checks, fails);
forward OnPlayerTestsComplete(playerid, tests, checks, fails);

#if defined RUN_TESTS
	#if defined _AUTO_RUN_TESTS
		#if defined FILTERSCRIPT
			// Hook main in gamemodes.
			public OnFilterScriptInit()
			{
				#if defined Testing_OnFilterScriptInit
					Testing_OnFilterScriptInit();
				#endif
				Testing_RunAll();
			}
			
			#if defined _ALS_OnFilterScriptInit
				#undef OnFilterScriptInit
			#else
				#define _ALS_OnFilterScriptInit
			#endif
			#define OnFilterScriptInit Testing_OnFilterScriptInit
			#if defined Testing_OnFilterScriptInit
				forward Testing_OnFilterScriptInit();
			#endif
		#else
			// Hook main in gamemodes.
			#undef ALS_MAIN_RET_
			#define ALS_MAIN_RET_(%0)
			main()
			{
				#if defined Testing_main
					Testing_main();
				#endif
				Testing_RunAll();
			}
			
			#if defined _ALS_main
				#undef main
			#else
				#define _ALS_main
			#endif

			#if defined Testing_main
				forward Testing_main();
			#endif
			#undef ALS_MAIN_RET_
			#define ALS_MAIN_RET_ ALS_MRET_
			#define main( ALS_main_:Testing_main(
		#endif

		#if !defined NO_PLAYER_TESTS		
			public OnPlayerSpawn(playerid) //(Player:playerid)
			{
				if (YSI_g_sPlayer == cellmax && !IsPlayerNPC(playerid)) //!Player_IsNPC(playerid))
				{
					YSI_g_sCurTest = YSI_g_sFailTests = 0;
					#if !defined LIGHT_TEST_REPORT
						Server_PrintIntroMessage("       STARTING PLAYER TESTS..."),
						Server_FinishIntroMessage();
					#endif
					YSI_g_sTests = 0;
					YSI_g_sChecks = 0;
					YSI_g_sFails = 0;
					#if defined JUST_TEST_GROUP
						YSI_g_sCurrentGroup = JUST_TEST_GROUP;
					#else
						YSI_g_sCurrentGroup[0] = '\0';
					#endif
					Testing_Next(playerid);
				}
				#if defined Testing_OnPlayerSpawn
					return Testing_OnPlayerSpawn(playerid);
				#else
					return 1;
				#endif
			}
			
			#if defined _ALS_OnPlayerSpawn
				#undef OnPlayerSpawn
			#else
				#define _ALS_OnPlayerSpawn
			#endif
			#define OnPlayerSpawn Testing_OnPlayerSpawn
			#if defined Testing_OnPlayerSpawn
				forward Testing_OnPlayerSpawn(playerid);
			#endif
		#endif
	#endif

	#if !defined _ALS_OnRuntimeError
		forward OnRuntimeError(code, &bool:suppress);
	#endif
	
	public OnRuntimeError(code, &bool:suppress)
	{
		if (YSI_g_sInTest)
		{
			// Fail the current test if we see any runtime errors.  Requires the
			// crashdetect plugin to function, but not to compile and run.
			Testing_Test(false, "Runtime error detected");
		}
		return Testing_OnRuntimeError(code, suppress);
	}
	
	CHAIN_FORWARD:Testing_OnRuntimeError(code, &bool:suppress) = 1;
	#if defined _ALS_OnRuntimeError
		#undef OnRuntimeError
	#else
		#define _ALS_OnRuntimeError
	#endif
	#define OnRuntimeError(%0) CHAIN_PUBLIC:Testing_OnRuntimeError(%0)
#endif

stock Testing_RunAll()
{
	// Disable error messages (as we're likely to generate them).
	//state ysi_debug : off;
	new
		startTime = 0,
		endTime = 0,
		tests = 0,
		checks = 0,
		fails = 0;
	// The timing will be inaccurate since it will include many prints, but it
	// isn't that important to be accurate.
	startTime = tickcount();
#if !defined LIGHT_TEST_REPORT
	Server_PrintIntroMessage("           STARTING TESTS..."),
	Server_FinishIntroMessage();
#endif
	Testing_Run(tests, checks, fails, _, true);
#if !defined JUST_TEST && !defined JUST_TEST_GROUP && defined YSI_TESTS
	if (YSI_g_sTestResult != 9) print("*** Test system verification failed!");
	else
#endif
	{
		printf("*** Test%s: %d, Check%s: %d, Fail%s: %d", Y_TESTING_S(tests), tests, Y_TESTING_S(checks), checks, Y_TESTING_S(fails), fails);
		if (fails)
		{
			// List all the failing tests, along with the number of "ASSERT"s
			// that didn't pass.
			while (YSI_g_sFailTests != 0)
			{
				printf("    - %s (%d)", AMX_Deref(YSI_g_sFailTests + 2 * cellbytes), AMX_Read(YSI_g_sFailTests + cellbytes)),
				YSI_g_sFailTests = AMX_Read(YSI_g_sFailTests);
			}
			print(YSI_SPACE);
		}
		else
		{
#if !defined LIGHT_TEST_REPORT
			Server_PrintIntroMessage("           ALL TESTS PASSED!"),
			Server_FinishIntroMessage();
#endif
		}
	}
	endTime = tickcount();
	printf("*** Time: %dms", endTime - startTime);
	TEST_REPORT(YSI_SPACE);
	//state ysi_debug : on;
	R@("OnTestsComplete", "iii", tests, checks, fails);
	#if defined TEST_AUTO_EXIT
		SendRconCommand("exit");
	#endif
	//state ysi_debug : on;
}

#if !defined YSI_TESTS
	#endinput
#endif

// Meta tests.

stock Testing_TestRedirect(bool:x, const str[] = "", GLOBAL_TAG_TYPES:...)
{
	ASSERT(x == bool:YSI_g_sTestResult);
	ASSERT(str[0] != '\0');
	ASSERT(!strcmp(str, "%s %s", false, 5));
}

stock Testing_SurpressOneFail()
{
	--YSI_g_sFails;
}

@test(.group = "y_testing") y_testing_2()
{
	new
		t = YSI_g_sTests,
		c = YSI_g_sChecks,
		f = YSI_g_sFails;
	ASSERT(false == false);
	ASSERT(true == true);
	ASSERT(TRUE != FALSE);
	ASSERT(c + 3 == YSI_g_sChecks);
	ASSERT(f == YSI_g_sFails);
	ASSERT(c + 5 == YSI_g_sChecks);
	ASSERT(t == YSI_g_sTests);
	// Fail a fake test on purpose.
	//state ysi_debug : on;
	Debug_Info("The next test hasn't really failed...");
	Debug_Info(" - It is testing the test system.");
	//state ysi_debug : off;
	ASSERT(false);
	ASSERT(f + 1 == YSI_g_sFails); // Not a mistake.  Run this test twice to
	ASSERT(f + 1 == YSI_g_sFails); // ensure the first one didn't fail too.
	Testing_SurpressOneFail(); // Reduce the failure count.
}

@testinit() y_testing_1()
{
	YSI_g_sTestResult = 5;
}

@test(.group = "y_testing") y_testing_1()
{
	new
		x = YSI_g_sTestResult;
	ASSERT_EQ(FALSE, false);
	ASSERT_EQ(TRUE, true);
	ASSERT_NE(true, false);
	ASSERT(IsNull(NULL));
	ASSERT_TRUE(true);
	ASSERT_TRUE(!false);
	ASSERT_FALSE(false);
	ASSERT_FALSE(!true);
	// Test the messages themselves.
	#define Testing_Test Testing_TestRedirect
	YSI_g_sTestResult = false;
	ASSERT(false);
	YSI_g_sTestResult = true;
	ASSERT(true);
	#undef Testing_Test
	YSI_g_sTestResult = x + 3;
	ASSERT_EQ(YSI_g_sTestResult, 8);
}

@testclose() y_testing_1()
{
	++YSI_g_sTestResult;
}

static stock y_testing_Return7()
{
	return 7;
}

static stock y_testing_ReturnHello()
{
	new ret[32] = "Hello";
	return ret;
}

@test(.group = "y_testing") y_testing_Asserts()
{
	ASSERT_EQ(y_testing_Return7(), 7);
	ASSERT_NE(y_testing_Return7(), 8);
	ASSERT_LE(y_testing_Return7(), 7);
	ASSERT_LE(y_testing_Return7(), 8);
	ASSERT_LT(y_testing_Return7(), 8);
	ASSERT_GE(y_testing_Return7(), 7);
	ASSERT_GE(y_testing_Return7(), 6);
	ASSERT_GT(y_testing_Return7(), 6);
	ASSERT_ZE(y_testing_Return7() - 7);
	ASSERT_NZ(y_testing_Return7());
	ASSERT_SAME(y_testing_ReturnHello(), "Hello");
	ASSERT_DIFF(y_testing_ReturnHello(), "hello");
	ASSERT_NEAR(y_testing_ReturnHello(), "hello");
}

// Include these in a non-alphabetical order.
#include ".\libs\y_testing_b"
#include ".\libs\y_testing_g"
#include ".\libs\y_testing_d"
#include ".\libs\y_testing_i"
#include ".\libs\y_testing_e"
#include ".\libs\y_testing_h"
#include ".\libs\y_testing_a"
#include ".\libs\y_testing_j"
#include ".\libs\y_testing_c"
#include ".\libs\y_testing_f"

#include "..\y_core\y_utils_tests"
#include "..\y_core\y_als_tests"
#include "..\y_core\y_cell_tests"
#include "..\y_core\y_amx_tests"
#include "..\..\YSI_Coding\y_unique\y_unique_tests"

