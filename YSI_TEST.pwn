#pragma dynamic 65536

// Enable the YSI internal tests.
#define YSI_TESTS

// Enable some slower tests.
#define YSI_HASHMAP_TESTS

// Fix many common issues.
#define YSI_NO_HEAP_MALLOC

// Close the server after finishing the tests.
#define TEST_AUTO_EXIT

// Disable the internal test verification system.
#define _YSI_NO_TEST_VERIFICATION

// Disable the startup version check.
#define _YSI_NO_VERSION_CHECK

// The mode name to use for file saving.
#define MODE_NAME "YSI_TEST"

// Use whirlpool for password hashing.
#define PP_WP

// Disable the `IsPlayerConnected` check in y_commands for testing.
#define Y_COMMANDS_NO_IPC

// Should the group system be included before or after other includes?
#if !defined GTYPE
	#error No group type given.
#endif

#if !defined _DEBUG
	#define _DEBUG -1
#endif

#define FIXES_Single 0

native WP_Hash(buffer[], len, const str[]);

#include <a_samp>
#tryinclude <fixes>

public OnGameModeInit()
{
	#if defined YSI_OnGameModeInit
		YSI_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit YSI_OnGameModeInit

#if defined YSI_OnGameModeInit
	forward YSI_OnGameModeInit();
#endif

#if GTYPE == 0
	#include <YSI_Players/y_groups>
#endif

// Failing tests are removed with "//", slow tests with "////".
#include <YSI_Coding\y_hooks>
#include <YSI_Coding/y_inline>
#include <YSI_Coding\y_malloc>
#include <YSI_Coding/y_remote>
#include <YSI_Coding\y_stringhash>
#include <YSI_Coding/y_timers>
#include <YSI_Coding\y_va>
#endinput

#include <YSI_Core/y_als>
#include <YSI_Core\y_cell>
#include <YSI_Core/y_debug>
#include <YSI_Coding\y_functional>
#include <YSI_Core/y_master>
#include <YSI_Core\y_testing>
#include <YSI_Core/y_utils>

#include <YSI_Data\y_bintree>
#include <YSI_Data/y_bit>
#include <YSI_Data\y_hashmap>
#include <YSI_Data/y_iterate>
#include <YSI_Data\y_jaggedarray>
#include <YSI_Data/y_playerarray>
#include <YSI_Data\y_playerset>

#if GTYPE == 1
	#include <YSI_Players/y_groups>
#endif
//#include <YSI_Players\y_languages>
//#include <YSI_Players\y_text>
//#include <YSI_Players\y_users>

#include <YSI_Server\y_colours>
#include <YSI_Server/y_flooding>
#include <YSI_Server\y_punycode>
#include <YSI_Server/y_scriptinit>
#include <YSI_Server\y_td>

#include <YSI_Storage/y_amx>
////#include <YSI_Storage\y_bitmap>
#include <YSI_Storage\y_ini>
//#include <YSI_Storage\y_php>
//#include <YSI_Storage\y_svar>
//#include <YSI_Storage\y_uvar>
#include <YSI_Storage/y_xml>

#include <YSI_Visual\y_areas>
//#include <YSI_Visual\y_classes>
#include <YSI_Visual/y_commands>
#include <YSI_Visual\y_dialog>
//#include <YSI_Visual\y_properties>
//#include <YSI_Visual\y_races>
//#include <YSI_Visual\y_zonenames>
#include <YSI_Visual/y_zonepulse>

//#pragma dynamic 4000

#if GTYPE == 2
	#include <YSI_Players\y_groups>
#endif

Tester2()
{
	new
		a0[10] = { 1,  2,  3, ...},
		ret;
	ret = LAM@0() + LAM@0(-1);{{{LAM@1(-1);new I@T:_@YSII=I@T(~~"...YSII"),F@_@ii:YSII=F@_@ii:_@YSII;for(new _0,_1;I@F();)while(I@L(0,0,I@K(1)))Callback_Return_(_:( _0 + _1 ));LAM@2(FoldL((Inline_UI_(_:YSII),YSII), 11, a0));}LAM@5(-1);}{{LAM@1();new I@T:_@YSII=I@T(~~"...YSII"),F@_@ii:YSII=F@_@ii:_@YSII;for(new _0,_1;I@F();)while(I@L(0,0,I@K(1)))Callback_Return_(_:( _0 * _1 ));LAM@2(FoldL((Inline_UI_(_:YSII),YSII), 11, a0));}LAM@5();}}
	Testing_Test(J@ == _:( 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 + 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 + 11), "%s %s (%d)", (_:SZB_:SZQ_:SZC_:SZN_:"\"ret ==  1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 + 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 + 11\""), (J@ = _:(ret)));
}

main()
{
	print("\n------------------------------");
	print("|                            |");
	print("|     YSI auto-test mode     |");
	print("|                            |");
	printf("| Compiler: 0x%04x           |", __Pawn);
	print("| Flags:                     |");
	printf("|  %24s  |", COMPILE_FLAGS);
	print("|                            |");
	print("------------------------------\n");
	//FIXES_ApplyAnimation(0, "", "", 0.0, 0, 0, 0, 0, 0, 0);
	//DisasmDump("YSI_TEST.asm");
	Tester2();
	//dynamic();
}

public OnScriptInit()
{
//	Langs_Add("English", "EN");
	return 1;
}

public OnTestsComplete(tests, fails)
{
	print("\n------------------------------");
	print("|                            |");
	print("|     YSI auto-test done     |");
	print("|                            |");
	printf("| Compiler: 0x%04x           |", __Pawn);
	print("| Flags:                     |");
	printf("|  %24s  |", COMPILE_FLAGS);
	print("|                            |");
	print("------------------------------\n");
}

