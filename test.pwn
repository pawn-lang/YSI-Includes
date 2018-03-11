#if !defined _DEBUG
	#define _DEBUG -1
#endif
#define FIXES_Single 0

// Currently "MTYPE 2" with "GTYPE 2" gives the most horrendous crash when the
// mode ends, that I've ever seen!
// "MTYPE 0", "GTYPE 2" also fails.  Won't fix!  Fixed!
#if !defined MTYPE
	#define MTYPE 1 // 0 - 3 (None  , Server, Cloud , Client)
#endif
#if !defined GTYPE
	#define GTYPE 1 // 0 - 3 (First , Middle, End   , None  )
#endif

#if MTYPE == 0
	#define YSI_NO_MASTER
#elseif MTYPE == 1
	#define YSI_IS_SERVER
#elseif MTYPE == 2
	//#define YSI_IS_CLOUD // Doesn't exist (default).
#elseif MTYPE == 3
	#error Can't run tests as "CLIENT" (MTYPE 3).
	#define YSI_IS_CLIENT
#endif

#define MODE_NAME "YSI_TEST"
#define PP_WP
#define YSI_HASHMAP_TESTS
#define Y_COMMANDS_NO_IPC
#define YSI_TESTS

native WP_Hash(buffer[], len, const str[]);

#include <a_samp>
#include <fixes>
#include <disasm>

//#include <YSI_Server\y_lock>

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

#pragma dynamic 65536

#if GTYPE == 0
	#include <YSI_Players\y_groups>
#endif

// Failing tests are removed with "//", slow tests with "////".
// #include "YSI_Coding\y_hooks"
// #include "YSI_Coding\y_inline"
// #include "YSI_Coding\y_malloc"
// #include "YSI_Coding\y_remote"
// #include "YSI_Coding\y_stringhash"
// #include "YSI_Coding\y_timers"
// #include "YSI_Coding\y_va"

// #include "YSI_Core\y_als"
// #include "YSI_Core\y_cell"
// #include "YSI_Core\y_debug"
// #include "YSI_Core\y_functional"
// #include "YSI_Core\y_master"
#include "YSI_Core\y_testing"
// #include "YSI_Core\y_utils"

// #include "YSI_Data\y_bintree"
// #include "YSI_Data\y_bit"
// #include "YSI_Data\y_hashmap"
// #include "YSI_Data\y_iterate"
// #include "YSI_Data\y_jaggedarray"
// #include "YSI_Data\y_playerarray"
// #include "YSI_Data\y_playerset"

// #if GTYPE == 1
// 	#include "YSI_Players\y_groups"
// #endif
#include "YSI_Players\y_languages"
// #include "YSI_Players\y_text"
// #include "YSI_Players\y_users"

// #include "YSI_Server\y_colours"
// #include "YSI_Server\y_flooding"
// #include "YSI_Server\y_punycode"
// #include "YSI_Server\y_scriptinit"
// #include "YSI_Server\y_td"

//#include "YSI_Storage\y_amx"
////#include "YSI_Storage\y_bitmap"
//#include "YSI_Storage\y_ini"
//#include "YSI_Storage\y_php"
//#include "YSI_Storage\y_svar"
//#include "YSI_Storage\y_uvar"
//#include "YSI_Storage\y_xml"

//#include "YSI_Visual\y_areas"
//#include "YSI_Visual\y_classes"
//#include "YSI_Visual\y_commands"
//#include "YSI_Visual\y_dialog"
//#include "YSI_Visual\y_properties"
// #include "YSI_Visual\y_races"
// #include "YSI_Visual\y_zonenames"
// #include "YSI_Visual\y_zonepulse"

// #if GTYPE == 2
// 	#include <YSI_Players\y_groups>
// #endif

main()
{
	print("\n------------------------------");
	print("|                            |");
	print("|     YSI auto-test mode     |");
	print("|                            |");
	printf("| Compiler: 0x%04x           |", __Pawn);
	print("|                            |");
	print("------------------------------\n");
	FIXES_ApplyAnimation(0, "", "", 0.0, 0, 0, 0, 0, 0, 0);
	//DisasmDump("YSI_TEST.asm");
}

public OnScriptInit()
{
	Langs_Add("English", "EN");
	return 1;
}

public OnTestsComplete(tests, fails)
{
	print("\n------------------------------");
	print("|                            |");
	print("|     YSI auto-test done     |");
	print("|                            |");
	printf("| Compiler: 0x%04x           |", __Pawn);
	print("|                            |");
	print("------------------------------\n");
}
