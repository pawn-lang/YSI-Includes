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

#define Y_TESTING_TEST_SEARCH _A<@yQ_>
#define Y_TESTING_PTEST_SEARCH _A<@_Qy>
#define Y_TESTING_INIT  _C<@y_Q>
#define Y_TESTING_TEST  _C<@yQ_>
#define Y_TESTING_SHUT  _C<@Qy_>
#define Y_TESTING_PINIT _C<@Q_y>
#define Y_TESTING_PTEST _C<@_Qy>
#define Y_TESTING_PSHUT _C<@_yQ>
#define Y_TESTING_BEFORE _A<y@Q_>
#define Y_TESTING_AFTER _A<y@_Q>

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
	YSI_g_sFails = 0;

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
	#define TEST_INIT__%1() forward @y_Q%1(); public @y_Q%1()
	#define TEST__%1() forward bool:@yQ_%1(); public bool:@yQ_%1() for(_Testing_Start("\0\0"#%1), TEST_REPORT("*** Test %s start", YSI_gCurTestName); __once; _Testing_End())yQ_@%1();static yQ_@%1()
	#define TEST_CLOSE__%1() forward @Qy_%1(); public @Qy_%1()
	#define TEST_BEFORE_EACH__%1() forward y@Q_%1(); public y@Q_%1()
	#define TEST_AFTER_EACH__%1() forward y@_Q%1(); public y@_Q%1()
	
	#define PTEST_INIT__%1(%2) forward @Q_y%1(%2); public @Q_y%1(%2)
	#define PTEST__%1(%2) forward bool:@_Qy%1(%2); public bool:@_Qy%1(%2) for(_Testing_Start("\0\0"#%1), TEST_REPORT("*** Player Test %s start", YSI_gCurTestName); __once; _Testing_End())_Qy@%1(%2);static _Qy@%1(%2)
	#define PTEST_CLOSE__%1(%2) forward @_yQ%1(%2); public @_yQ%1(%2)
	
	#define TEST_COMPILE__%1() forward Q@y_%1();public Q@y_%1(){if(FALSE)Q@_y%1();P:W("Compile test " #%1 " called.");}static stock Q@_y%1()
#else
	#define TEST_INIT__%1() static stock y_Q@%1()
	#define TEST__%1() static stock bool:yQ_@%1()
	#define TEST_CLOSE__%1() static stock Qy_@%1()
	#define TEST_BEFORE_EACH__%1() stock y@Q_%1()
	#define TEST_AFTER_EACH__%1() stock y@_Q%1()
	
	#define PTEST_INIT__%1(%2) static stock Q_y@%1(%2)
	#define PTEST__%1(%2) static stock bool:_Qy@%1(%2)
	#define PTEST_CLOSE__%1(%2) static stock _yQ@%1(%2)
	
	#define TEST_COMPILE__%1() static stock Q@_y%1()
#endif

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

// Currently unused.
//#define _@Qy%0\32; _@Qy
//#define _@yQ%0\32; _@yQ
//#define y_@Q%0\32; y_@Q
//#define yQ@_%0\32; yQ@_
//#define Qy@_%0\32; Qy@_
//#define Q_@y%0\32; Q_@y
//#define _Q@y%0\32; _Q@y
//#define _y@Q%0\32; _y@Q

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the current function.</param>
 * <remarks>
 *  Gets a reference to the 
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock _Testing_Start(const name[])
{
	YSI_gTestComplete = false;
	// Gets a reference to the name string, which is also an intrusive linked
	// list of failures.
	setarg(0, 0, 0); // Bypass `const`.
	setarg(0, 1, 0); //name[0] = name[1] = 0,
	YSI_g_sCurTest = AMX_Ref(name[0]);
	// My very first legitimate usage of `heapspace()` for something other than
	// as a dummy no-op function call!  I'm actually quite happy I found a use
	// for it!
	YSI_g_sCurHeap = heapspace();
	P:3("_Testing_Start %d %d %s = %d", name[0], name[1], name[2], YSI_g_sCurTest);
	YSI_gCurTestName[0] = '\0',
	StrCpy(YSI_gCurTestName, name[2]);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to ask a question to.</param>
 * <param name="str">What to ask.</param>
 * <param name="va_args">Additional data.</param>
 * <remarks>
 *  Calls a dialog to ask the player if the given test actually passed.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if !defined DIALOG_STYLE
	#define DIALOG_STYLE: _:
#endif

#if !defined NO_PLAYER_TESTS
	native YSI_ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE:style, const caption[], const info[], const button1[], const button2[]) = ShowPlayerDialog;

	stock Testing_Ask(playerid, const str[] = "", GLOBAL_TAG_TYPES:...)
	{
			#pragma unused str
			new
				i = 0,
				end = 0; // 12 + 4 + 4.
			// Get the stack position after `playerid`.
			#emit ADDR.pri         16
			#emit STOR.S.pri       end
			// Get the stack position after everything.
			#emit ADDR.pri         12
			#emit LOAD.S.alt       8
			#emit ADD
			#emit STOR.S.pri       i
			while (i > end)
			{
				i -= 4;
				#emit LREF.S.pri       i
				#emit PUSH.pri
			}
			{}
			#emit PUSH.C           512
			#emit PUSH.C           YSI_g_sFailMessage
			#emit LOAD.S.pri       8
			#emit ADD.C            4
			#emit PUSH.pri
			#emit SYSREQ.C         format
			// Remove the data from the stack.
			#emit POP.alt
			#emit LCTRL            4
			#emit ADD
			#emit SCTRL            4
			//format(YSI_g_sFailMessage, sizeof (YSI_g_sFailMessage), str, ___(2));
		#if defined YSI_NO_DIALOG_ASK
			// For early open.mp testing
			format(YSI_g_sFailMessage, sizeof (YSI_g_sFailMessage), "TEST: %s (~k~~CONVERSATION_YES~ / ~k~~CONVERSATION_NO~)", YSI_g_sFailMessage),
			SendClientMessage(playerid, 0xFF8010FF, YSI_g_sFailMessage);
		#else
			YSI_ShowPlayerDialog(playerid, Y_TESTING_DIALOG_ID, DIALOG_STYLE_MSGBOX, "Did the test pass?", YSI_g_sFailMessage, "Yes", "No");
		#endif
			YSI_g_sAsked = true;
	}
#endif

stock Testing_Test(bool:x, const str[] = "", GLOBAL_TAG_TYPES:...)
{
	#pragma unused str
	P:3("Testing_Test called: %i, \"%s\"", x, str);
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
	//  P:T(str, msg, ___(2));
	//  
	#emit LOAD.S.pri       16
	#emit STOR.S.pri       12
	#emit CONST.pri        Testing_Test_msg
	#emit STOR.S.pri       16
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
 *  Gets a reference to the 
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
 *  Wether all tests were sucessful or not.
 * </returns>
 * <remarks>
 *  -
 *
 * native Testing_Run(&amp;tests, &amp;fails, buffer[33] = "");
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:Testing_Run(&tests, &checks, &fails, const lastfail[33] = "", bool:p = false)
{
	P:3("bool:Testing_Run called: %i, %i, \"%s\", %i", tests, fails, lastfail, p);
	#pragma unused p, lastfail
#if defined RUN_TESTS
	P:2("Testing_Run() called");
	new
		idx = 0,
		bidx = 0,
		buffer2[FUNCTION_LENGTH],
		buffer[FUNCTION_LENGTH];
	YSI_g_sCurTest = YSI_g_sFailTests = 0;
	while ((idx = AMX_GetPublicNamePrefix(idx, buffer, Y_TESTING_TEST_SEARCH)))
	{
#if defined JUST_TEST
		if (strcmp(buffer[1], #JUST_TEST))
			continue;
#endif
		Server_RestartLongCall();
		while ((bidx = AMX_GetPublicNamePrefix(bidx, buffer2, Y_TESTING_BEFORE)))
		{
			for (new i = 4; buffer{i} && buffer2{i}; ++i)
			{
				if (buffer{i} != buffer2{i})
					goto Testing_Run_before_fail;
			}
			R@(buffer2, YSI_EMPTY);
Testing_Run_before_fail:
		}
		// Call the setup function if there is one.
		buffer[0] = Y_TESTING_INIT,
		R@(buffer, YSI_EMPTY),
		// Call the test.
		buffer[0] = Y_TESTING_TEST,
		fails = YSI_g_sFails;
		P:5("Testing_Run(): Calling %s", Unpack(buffer[1]));
		YSI_g_sInTest = true,
		R@(buffer, YSI_EMPTY),
		YSI_g_sInTest = false;
		++YSI_g_sTests;
		if (!YSI_gTestComplete)
		{
#if defined INCLUDE_TESTS || defined RUN_TESTS
			++YSI_g_sFails;
			print("Test did not complete (possible crash).\n");
#endif
		}
		if (YSI_g_sFails != fails)
		{
			AMX_Write(YSI_g_sCurTest, YSI_g_sFailTests),
			AMX_Write(YSI_g_sCurTest + 4, YSI_g_sFails - fails),
			YSI_g_sFailTests = YSI_g_sCurTest;
		}
#if !defined TEST_SHOW_PASSES
		else
		{
			TEST_REPORT(TEST_PASSED);
			TEST_REPORT(YSI_SPACE);
		}
#endif
		buffer[0] = Y_TESTING_SHUT,
		R@(buffer, YSI_EMPTY);

		while ((bidx = AMX_GetPublicNamePrefix(bidx, buffer2, Y_TESTING_AFTER)))
		{
			for (new i = 4; buffer{i} && buffer2{i}; ++i)
			{
				if (buffer{i} != buffer2{i})
					goto Testing_Run_after_fail;
			}
			R@(buffer2, YSI_EMPTY);
Testing_Run_after_fail:
		}
	}
	tests = YSI_g_sTests;
	checks = YSI_g_sChecks;
	fails = YSI_g_sFails;
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
 *  Wether all tests were sucessful or not.
 * </returns>
 * <remarks>
 *  -
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
		P:2("Testing_Next() called");
		YSI_g_sInTest = false;
		new
			buffer[FUNCTION_LENGTH];
		for ( ; ; )
		{
			// Get the last test (nicely fails for cellmax).
			if ((YSI_g_sPlayer = AMX_GetPublicNamePrefix(YSI_g_sPlayer, buffer, Y_TESTING_PTEST_SEARCH)))
			{
				// Call the shutdown function if there is one.
				buffer[0] = Y_TESTING_PSHUT;
				P:5("Testing_Next(): Calling %s", Unpack(buffer));
				R@(buffer, "i", playerid);
			}
			// Update fail counts.
			if (YSI_g_sPlayerFails != YSI_g_sFails)
			{
				AMX_Write(YSI_g_sCurTest, YSI_g_sFailTests),
				AMX_Write(YSI_g_sCurTest + 4, YSI_g_sFails - YSI_g_sPlayerFails),
				YSI_g_sFailTests = YSI_g_sCurTest,
				YSI_g_sPlayerFails = YSI_g_sFails;
			}
#if defined JUST_TEST
			new next;
Testing_Next_retry:
			// Get the new test, but don't store the index.
			if ((next = AMX_GetPublicNamePrefix(YSI_g_sPlayer, buffer, Y_TESTING_PTEST_SEARCH)))
			{
				if (strcmp(buffer[1], #JUST_TEST))
				{
					YSI_g_sPlayer = next;
					goto Testing_Next_retry;
				}
#else
			if (AMX_GetPublicNamePrefix(YSI_g_sPlayer, buffer, Y_TESTING_PTEST_SEARCH))
			{
#endif
				++YSI_g_sTests;
				YSI_g_sAsked = false;
				// Call the setup function if there is one.
				buffer[0] = Y_TESTING_PINIT;
				P:5("Testing_Next(): Calling %s", Unpack(buffer));
				R@(buffer, "i", playerid);
				// Call the test.
				buffer[0] = Y_TESTING_PTEST;
				P:5("Testing_Next(): Calling %s", Unpack(buffer));
				YSI_g_sInTest = true;
				R@(buffer, "i", playerid);
			}
			else
			{
				YSI_g_sAsked = true;
				// No more tests.
				#if defined YSI_NO_DIALOG_ASK
					printf("*** Test%s: %d, Check%s: %d, Fail%s: ???", Y_TESTING_S(YSI_g_sTests), YSI_g_sTests, Y_TESTING_S(YSI_g_sChecks), YSI_g_sChecks, Y_TESTING_S(YSI_g_sFails));
				#else
					printf("*** Test%s: %d, Check%s: %d, Fail%s: %d", Y_TESTING_S(YSI_g_sTests), YSI_g_sTests, Y_TESTING_S(YSI_g_sChecks), YSI_g_sChecks, Y_TESTING_S(YSI_g_sFails), YSI_g_sFails);
				#endif
				if (YSI_g_sFails)
				{
					// List all the failing tests, along with the number of "ASSERT"s
					// that didn't pass.
					while (YSI_g_sFailTests != 0)
					{
						printf("    - %s (%d)", AMX_Deref(YSI_g_sFailTests + 8), AMX_Read(YSI_g_sFailTests + 4)),
						YSI_g_sFailTests = AMX_Read(YSI_g_sFailTests);
					}
					print(YSI_SPACE);
				}
				else
				{
					#if !defined LIGHT_TEST_REPORT
						#if defined YSI_NO_DIALOG_ASK
							Server_PrintIntroMessage("       PLEASE NOTE FAILED TESTS."),
							Server_FinishIntroMessage();
						#else
							Server_PrintIntroMessage("       ALL PLAYER TESTS PASSED!"),
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
			}
		}
	}
	
	#if defined YSI_NO_DIALOG_ASK
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
	#else
		public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
		{
			if (dialogid == Y_TESTING_DIALOG_ID)
			{
				++YSI_g_sChecks;
				if (response)
				{
					// Pass.
					TEST_REPORT(TEST_PASSED);
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
#if !defined JUST_TEST && defined YSI_TESTS
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
				printf("    - %s (%d)", AMX_Deref(YSI_g_sFailTests + 8), AMX_Read(YSI_g_sFailTests + 4)),
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

#if defined YSI_TESTS

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

TEST__ y_testing_2()
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
	P:I("The next test hasn't really failed...");
	P:I(" - It is testing the test system.");
	//state ysi_debug : off;
	ASSERT(false);
	ASSERT(f + 1 == YSI_g_sFails); // Not a mistake.  Run this test twice to
	ASSERT(f + 1 == YSI_g_sFails); // ensure the first one didn't fail too.
	Testing_SurpressOneFail(); // Reduce the failure count.
}

TEST_INIT__ y_testing_1()
{
	YSI_g_sTestResult = 5;
}

TEST__ y_testing_1()
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

TEST_CLOSE__ y_testing_1()
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

TEST__ y_testing_Asserts()
{
	ASSERT_EQ(y_testing_Return7(), 7);
	ASSERT_NE(y_testing_Return7(), 8);
	ASSERT_LE(y_testing_Return7(), 7);
	ASSERT_LE(y_testing_Return7(), 8);
	ASSERT_LT(y_testing_Return7(), 8);
	ASSERT_GE(y_testing_Return7(), 7);
	ASSERT_GE(y_testing_Return7(), 6);
	ASSERT_GT(y_testing_Return7(), 6);
	ASSERT_SAME(y_testing_ReturnHello(), "Hello");
	ASSERT_DIFF(y_testing_ReturnHello(), "hello");
	ASSERT_NEAR(y_testing_ReturnHello(), "hello");
}

#endif

#if defined YSI_TESTS
	#include "..\y_core\y_utils_tests"
	#include "..\y_core\y_als_tests"
	#include "..\y_core\y_cell_tests"
#endif

