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

forward bool:_Testing_End();

#include "..\y_utils"
#include "..\..\YSI_Server\y_stringise"

#tryinclude "..\..\amx\amx_memory"
#tryinclude <amx_assembly\amx_memory>
#tryinclude "..\..\amx_assembly\amx_memory"
#tryinclude "..\..\..\amx_assembly\amx_memory"
#tryinclude "amx_memory"
#tryinclude <amx_memory>

CHAIN_HOOK(Testing)
#undef CHAIN_ORDER
#define CHAIN_ORDER CHAIN_NEXT(Testing)

#if !defined AMX_MEMORY_INC
	#error Could not include "https://github.com/Zeex/amx_assembly" - ensure its files are in "include\amx_assembly\"
#endif

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

#define ASSERT(%0) Testing_Test(%0, "%s %s", STRINGISE__(%0))
#define ASSERT_TRUE(%0) ASSERT(!!%0)
#define ASSERT_FALSE(%0) ASSERT(!%0)
#define ASSERT_NULL(%0) ASSERT(0 == %0)
#define ASSERT_N:%1(%0) ASSERT(%1 == %0)

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

// Numbers.
#define ASSERT_EQ(%1,%0) Testing_Test(J@ == _:(%0), "%s %s (%d)", STRINGISE__(%1 == %0), (J@ = _:(%1)))
#define ASSERT_NE(%1,%0) Testing_Test(J@ != _:(%0), "%s %s (%d)", STRINGISE__(%1 != %0), (J@ = _:(%1)))
#define ASSERT_LE(%1,%0) Testing_Test(J@ <= _:(%0), "%s %s (%d)", STRINGISE__(%1 <= %0), (J@ = _:(%1)))
#define ASSERT_LT(%1,%0) Testing_Test(J@ <  _:(%0), "%s %s (%d)", STRINGISE__(%1 <  %0), (J@ = _:(%1)))
#define ASSERT_GE(%1,%0) Testing_Test(J@ >= _:(%0), "%s %s (%d)", STRINGISE__(%1 >= %0), (J@ = _:(%1)))
#define ASSERT_GT(%1,%0) Testing_Test(J@ >  _:(%0), "%s %s (%d)", STRINGISE__(%1 >  %0), (J@ = _:(%1)))

// Zeroes.
#define ASSERT_ZE(%1) Testing_Test(J@ == 0, "%s %s (%d)", STRINGISE__(%1 == 0), (J@ = _:(%1)))
#define ASSERT_NZ(%1) Testing_Test(J@ != 0, "%s %s (%d)", STRINGISE__(%1 != 0), (J@ = _:(%1)))

// Strings.
#define ASSERT_SAME(%1,%0) Testing_Test(Q@[0] != '\0' && strcmp(Q@, (%0)      ) == 0, "%s %s (\"%s\")", STRINGISE__(%1 == %0), (strunpack(Q@, (%1)), Q@))
#define ASSERT_DIFF(%1,%0) Testing_Test(Q@[0] == '\0' || strcmp(Q@, (%0)      ) != 0, "%s %s (\"%s\")", STRINGISE__(%1 != %0), (strunpack(Q@, (%1)), Q@))
#define ASSERT_NEAR(%1,%0) Testing_Test(Q@[0] != '\0' && strcmp(Q@, (%0), true) == 0, "%s %s (\"%s\")", STRINGISE__(%1 ~= %0), (strunpack(Q@, (%1)), Q@))

static stock
	YSI_g_sCurTest = 0,
	YSI_g_sCurHeap = 0,
	YSI_g_sFailTests = 0,
	YSI_g_sInTest = false,
	YSI_g_sTestResult,
	YSI_g_sFailMessage[512],
	YSI_g_sPlayer = cellmax,
	bool:YSI_gTestComplete,
	bool:YSI_g_sAsked,
	YSI_g_sTests,
	YSI_g_sFails;

stock
	YSI_gCurTestName[32];

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
	#define TEST_INIT__%1() @y_Q%1();@y_Q%1()
	#define TEST__%1() bool:@yQ_%1();bool:@yQ_%1() for(new bool:__once = (_Testing_Start("\0\0"#%1), TEST_REPORT("*** Test %s start", YSI_gCurTestName) || true); __once; __once = _Testing_End())yQ_@%1();static yQ_@%1()
	#define TEST_CLOSE__%1() @Qy_%1();@Qy_%1()
	#define TEST_BEFORE_EACH__%1() forward y@Q_%1(); public y@Q_%1()
	#define TEST_AFTER_EACH__%1() forward y@_Q%1(); public y@_Q%1()
	
	#define PTEST_INIT__%1(%2) @Q_y%1(%2);@Q_y%1(%2)
	#define PTEST__%1(%2) bool:@_Qy%1(%2);bool:@_Qy%1(%2) for(new bool:__once = (_Testing_Start("\0\0"#%1), TEST_REPORT("*** Player Test %s start", YSI_gCurTestName) || true); __once; __once = _Testing_End())_Qy@%1(%2);static _Qy@%1(%2)
	#define PTEST_CLOSE__%1(%2) @_yQ%1(%2);@_yQ%1(%2)
	
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
	YSI_g_sCurTest = ref(name);
	// My very first legitimate usage of `heapspace()` for something other than
	// as a dummy no-op function call!  I'm actually quite happy I found a use
	// for it!
	YSI_g_sCurHeap = heapspace();
	P:3("_Testing_Start %d %d %s = %d", name[0], name[1], name[2], YSI_g_sCurTest);
	YSI_gCurTestName[0] = '\0',
	strcpy(YSI_gCurTestName, name[2]);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to ask a question to.</param>
 * <param name="str">What to ask.</param>
 * <param name="va_args">Additional data.</param>
 * <remarks>
 *  Calls a dialog to ask the player if the given test actually passed.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Testing_Ask(playerid, const str[] = "", GLOBAL_TAG_TYPES:...)
{
	#pragma unused str
	new
		i,
		end; // 12 + 4 + 4.
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
	ShowPlayerDialog(playerid, Y_TESTING_DIALOG_ID, DIALOG_STYLE_MSGBOX, "Did the test pass?", YSI_g_sFailMessage, "Yes", "No");
	YSI_g_sAsked = true;
}

stock Testing_Test(bool:x, const str[] = "", GLOBAL_TAG_TYPES:...)
{
	#pragma unused str
	P:3("Testing_Test called: %i, \"%s\"", x, str);
	++YSI_g_sTests;
	static
		Testing_Test_msg[6],
		Testing_Test_FRM,
		Testing_Test_RET;
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
	++YSI_g_sTests;
	if (YSI_g_sCurHeap != space)
	{
#if defined INCLUDE_TESTS || defined RUN_TESTS
		++YSI_g_sFails;
		printf("%s Heap allocation leak - was: %d, now: %d", TEST_FAILED, YSI_g_sCurHeap, space);
#endif
	}
	TEST_REPORT(" ");
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

stock bool:Testing_Run(&tests, &fails, const lastfail[33] = "", bool:p = false)
{
	P:3("bool:Testing_Run called: %i, %i, \"%s\", %i", tests, fails, lastfail, p);
	#pragma unused p, lastfail
#if defined RUN_TESTS
	P:2("Testing_Run() called");
	new
		idx,
		bidx,
		buffer2[32],
		buffer[32];
	YSI_g_sCurTest = YSI_g_sFailTests = 0;
	while ((idx = AMX_GetPublicNamePrefix(idx, buffer, Y_TESTING_TEST_SEARCH)))
	{
#if defined JUST_TEST
		if (strcmp(buffer[1], #JUST_TEST))
			continue;
#endif
		while ((bidx = AMX_GetPublicNamePrefix(bidx, buffer2, Y_TESTING_BEFORE)))
		{
			for (new i = 4; buffer{i} && buffer2{i}; ++i)
			{
				if (buffer{i} != buffer2{i})
					goto Testing_Run_before_fail;
			}
			CallLocalFunction(buffer2, "");
Testing_Run_before_fail:
		}
		// Call the setup function if there is one.
		buffer[0] = Y_TESTING_INIT,
		CallLocalFunction(buffer, ""),
		// Call the test.
		buffer[0] = Y_TESTING_TEST,
		fails = YSI_g_sFails;
		P:5("Testing_Run(): Calling %s", unpack(buffer[1]));
		YSI_g_sInTest = true,
		CallLocalFunction(buffer, ""),
		YSI_g_sInTest = false;
		++YSI_g_sTests;
		if (!YSI_gTestComplete)
		{
#if defined INCLUDE_TESTS || defined RUN_TESTS
			++YSI_g_sFails;
			printf("Test did not complete (possible crash).\n");
#endif
		}
		if (YSI_g_sFails != fails)
		{
			WriteAmxMemory(YSI_g_sCurTest, YSI_g_sFailTests),
			WriteAmxMemory(YSI_g_sCurTest + 4, YSI_g_sFails - fails),
			YSI_g_sFailTests = YSI_g_sCurTest;
		}
#if !defined TEST_SHOW_PASSES
		else
		{
			TEST_REPORT(TEST_PASSED);
			TEST_REPORT(" ");
		}
#endif
		buffer[0] = Y_TESTING_SHUT,
		CallLocalFunction(buffer, "");

		while ((bidx = AMX_GetPublicNamePrefix(bidx, buffer2, Y_TESTING_AFTER)))
		{
			for (new i = 4; buffer{i} && buffer2{i}; ++i)
			{
				if (buffer{i} != buffer2{i})
					goto Testing_Run_after_fail;
			}
			CallLocalFunction(buffer2, "");
Testing_Run_after_fail:
		}
	}
	tests = YSI_g_sTests;
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

stock bool:Testing_Player(playerid, &idx, &tests, &fails, const lastfail[33] = "", bool:p = false)
{
	P:3("bool:Testing_Player called: %i, %i, %i, %i, \"%s\", %i", playerid, idx, tests, fails, lastfail, p);
	#pragma unused p
	#if defined RUN_TESTS
		P:2("Testing_Player() called");
		new
			buffer[32];
#if defined JUST_TEST
Testing_Player_retry:
#endif
		if ((idx = AMX_GetPublicNamePrefix(YSI_g_sPlayer, buffer, Y_TESTING_PTEST_SEARCH)))
		{
#if defined JUST_TEST
			if (strcmp(buffer[1], #JUST_TEST))
				goto Testing_Player_retry;
#endif
			// Call the setup function if there is one.
			buffer[0] = Y_TESTING_PINIT,
			CallLocalFunction(buffer, ""),
			// Call the test.
			buffer[0] = Y_TESTING_PTEST,
			fails = YSI_g_sFails;
			P:5("Testing_Player(): Calling %s", unpack(buffer[1]));
			YSI_g_sInTest = true;
			CallLocalFunction(buffer, "");
#if !defined TEST_SHOW_PASSES
			if (YSI_g_sFails == fails)
			{
				TEST_REPORT(TEST_PASSED);
				TEST_REPORT(" ");
			}
#endif
		}
		tests = YSI_g_sTests;
		fails = YSI_g_sFails;
		return fails == 0;
	#else
		#pragma unused tests, fails, lastfail
		return true;
	#endif
}

forward OnTestsComplete(tests, fails);

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
			#define main forward Testing_main(); public Testing_main
		#endif
	#endif
	
	Testing_Next(playerid)
	{
		YSI_g_sInTest = false;
		new
			buffer[32];
		for ( ; ; )
		{
			new
				fails = YSI_g_sFails;
			// Get the last test (nicely fails for cellmax).
			while ((YSI_g_sPlayer = AMX_GetPublicNamePrefix(YSI_g_sPlayer, buffer, Y_TESTING_PTEST_SEARCH)))
			{
				// Call the shutdown function if there is one.
				buffer[0] = Y_TESTING_PSHUT,
				CallLocalFunction(buffer, "i", playerid);
			}
#if defined JUST_TEST
Testing_Next_retry:
#endif
			// Get the new test, but don't store the index.
			if (AMX_GetPublicNamePrefix(YSI_g_sPlayer, buffer, Y_TESTING_PTEST_SEARCH))
			{
#if defined JUST_TEST
				if (strcmp(buffer[1], #JUST_TEST))
					goto Testing_Next_retry;
#endif
				YSI_g_sAsked = false;
				// Call the setup function if there is one.
				buffer[0] = Y_TESTING_PINIT,
				CallLocalFunction(buffer, ""),
				// Call the test.
				buffer[0] = Y_TESTING_PTEST;
				P:5("Testing_Next(): Calling %s", unpack(buffer[1]));
				YSI_g_sInTest = true;
				CallLocalFunction(buffer, "i", playerid);
			}
			else
			{
				YSI_g_sAsked = true;
				// No more tests.
				printf("*** Tests: %d, Fails: %d", YSI_g_sTests, YSI_g_sFails);
				if (!YSI_g_sFails)
				{
					TEST_REPORT(" ");
					TEST_REPORT("  ||==========================||  ");
					TEST_REPORT("  || ALL PLAYER TESTS PASSED! ||  ");
					TEST_REPORT("  ||==========================||  ");
					TEST_REPORT(" ");
				}
			}
			// If the test needs a player but doesn't ask them anything
			// then we can't wait for "OnDialogResponse" to run the next
			// one.
			if (YSI_g_sAsked)
			{
				break;
			}
			else if (fails == YSI_g_sFails)
			{
				TEST_REPORT(TEST_PASSED);
			}
		}
	}
	
	public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
	{
		if (dialogid == Y_TESTING_DIALOG_ID)
		{
			++YSI_g_sTests;
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
	
	public OnPlayerSpawn(playerid)
	{
		if (YSI_g_sPlayer == cellmax && !IsPlayerNPC(playerid))
		{
			TEST_REPORT(" ");
			TEST_REPORT("  ||==========================||  ");
			TEST_REPORT("  || STARTING PLAYER TESTS... ||  ");
			TEST_REPORT("  ||==========================||  ");
			TEST_REPORT(" ");
			YSI_g_sTests = 0;
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

stock Testing_RunAll()
{
	// Disable error messages (as we're likely to generate them).
	//state ysi_debug : off;
	new
		startTime,
		endTime,
		tests,
		fails;
	// The timing will be inaccurate since it will include many prints, but it
	// isn't that important to be accurate.
	startTime = GetTickCount();
	TEST_REPORT(" ");
	TEST_REPORT("  ||===================||  ");
	TEST_REPORT("  || STARTING TESTS... ||  ");
	TEST_REPORT("  ||===================||  ");
	TEST_REPORT(" ");
	Testing_Run(tests, fails, _, true);
#if !defined JUST_TEST && defined YSI_TESTS
	if (YSI_g_sTestResult != 9) printf("*** Test system verification failed!");
	else
#endif
	{
		printf("*** Tests: %d, Fails: %d", tests, fails);
		if (fails)
		{
			// List all the failing tests, along with the number of "ASSERT"s
			// that didn't pass.
			while (YSI_g_sFailTests != 0)
			{
				printf("    - %s (%d)", deref(YSI_g_sFailTests + 8), ReadAmxMemory(YSI_g_sFailTests + 4)),
				YSI_g_sFailTests = ReadAmxMemory(YSI_g_sFailTests);
			}
		}
		else
		{
			TEST_REPORT(" ");
			TEST_REPORT("  ||===================||  ");
			TEST_REPORT("  || ALL TESTS PASSED! ||  ");
			TEST_REPORT("  ||===================||  ");
		}
		TEST_REPORT(" ");
	}
	endTime = GetTickCount();
	printf("*** Time: %dms", endTime - startTime);
	TEST_REPORT(" ");
	//state ysi_debug : on;
	CallLocalFunction("OnTestsComplete", "ii", tests, fails);
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
		f = YSI_g_sFails;
	ASSERT(false == false);
	ASSERT(true == true);
	ASSERT(TRUE != FALSE);
	ASSERT(t + 3 == YSI_g_sTests);
	ASSERT(f == YSI_g_sFails);
	ASSERT(t + 5 == YSI_g_sTests);
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
	ASSERT(isnull(NULL));
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

