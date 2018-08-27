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

// Should the group system be included before or after other includes?
#if !defined GTYPE
	#error No group type given.
#endif

#if !defined _DEBUG
	#define _DEBUG -1
#endif

#define FIXES_Single 0

#include <a_samp>
#include <fixes>
#include <whirlpool>

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
	#include <YSI-Players/y_groups>
#endif

// Failing tests are removed with "//", slow tests with "////".
#include <YSI-Coding\y_hooks>
#include <YSI-Coding/y_inline>
#include <YSI-Coding\y_malloc>
#include <YSI-Coding/y_remote>
#include <YSI-Coding\y_stringhash>
#include <YSI-Coding/y_timers>
#include <YSI-Coding\y_va>

#include <YSI-Core/y_als>
#include <YSI-Core\y_cell>
#include <YSI-Core/y_debug>
#include <YSI-Coding\y_functional>
#include <YSI-Core/y_master>
#include <YSI-Core\y_testing>
#include <YSI-Core/y_utils>

#include <YSI-Data\y_bintree>
#include <YSI-Data/y_bit>
#include <YSI-Data\y_hashmap>
#include <YSI-Data/y_iterate>
#include <YSI-Data\y_jaggedarray>
#include <YSI-Data/y_playerarray>
#include <YSI-Data\y_playerset>

#if GTYPE == 1
	#include <YSI-Players/y_groups>
#endif
//#include <YSI-Players\y_languages>
//#include <YSI-Players\y_text>
//#include <YSI-Players\y_users>

#include <YSI-Server\y_colours>
#include <YSI-Server/y_flooding>
#include <YSI-Server\y_punycode>
#include <YSI-Server/y_scriptinit>
#include <YSI-Server\y_td>

#include <YSI-Storage/y_amx>
////#include <YSI-Storage\y_bitmap>
#include <YSI-Storage\y_ini>
//#include <YSI-Storage\y_php>
//#include <YSI-Storage\y_svar>
//#include <YSI-Storage\y_uvar>
#include <YSI-Storage/y_xml>

#include <YSI-Visual\y_areas>
//#include <YSI-Visual\y_classes>
#include <YSI-Visual/y_commands>
#include <YSI-Visual\y_dialog>
//#include <YSI-Visual\y_properties>
//#include <YSI-Visual\y_races>
//#include <YSI-Visual\y_zonenames>
#include <YSI-Visual/y_zonepulse>

#if GTYPE == 2
	#include <YSI-Players\y_groups>
#endif

main()
{
}

