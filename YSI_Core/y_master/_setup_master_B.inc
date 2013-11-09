#undef _inc__setup_master_B

#if MASTER == 26
	#define _MASTER 26
	#define YSIM_STORED_SETTINGS YSIM_RECALL_26
	#if defined _YCM_A@
		#define YSIM_DEFINED
	#else
		#define _YCM_A@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_26 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_26 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_26 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_26 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_26 4
		#else
			#error Undefined master type on 26
		#endif
	#endif
	#define _YCM A@
	#define MAKE_YCM<%0...%1> %0A@%1
	#define _YCM@ _YCM_gA@
	#endinput
#elseif MASTER == 27
	#define _MASTER 27
	#define YSIM_STORED_SETTINGS YSIM_RECALL_27
	#if defined _YCM_B@
		#define YSIM_DEFINED
	#else
		#define _YCM_B@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_27 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_27 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_27 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_27 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_27 4
		#else
			#error Undefined master type on 27
		#endif
	#endif
	#define _YCM B@
	#define MAKE_YCM<%0...%1> %0B@%1
	#define _YCM@ _YCM_gB@
	#endinput
#elseif MASTER == 28
	#define _MASTER 28
	#define YSIM_STORED_SETTINGS YSIM_RECALL_28
	#if defined _YCM_C@
		#define YSIM_DEFINED
	#else
		#define _YCM_C@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_28 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_28 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_28 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_28 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_28 4
		#else
			#error Undefined master type on 28
		#endif
	#endif
	#define _YCM C@
	#define MAKE_YCM<%0...%1> %0C@%1
	#define _YCM@ _YCM_gC@
	#endinput
#elseif MASTER == 29
	#define _MASTER 29
	#define YSIM_STORED_SETTINGS YSIM_RECALL_29
	#if defined _YCM_D@
		#define YSIM_DEFINED
	#else
		#define _YCM_D@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_29 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_29 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_29 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_29 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_29 4
		#else
			#error Undefined master type on 29
		#endif
	#endif
	#define _YCM D@
	#define MAKE_YCM<%0...%1> %0D@%1
	#define _YCM@ _YCM_gD@
	#endinput
#elseif MASTER == 30
	#define _MASTER 30
	#define YSIM_STORED_SETTINGS YSIM_RECALL_30
	#if defined _YCM_E@
		#define YSIM_DEFINED
	#else
		#define _YCM_E@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_30 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_30 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_30 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_30 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_30 4
		#else
			#error Undefined master type on 30
		#endif
	#endif
	#define _YCM E@
	#define MAKE_YCM<%0...%1> %0E@%1
	#define _YCM@ _YCM_gE@
	#endinput
#elseif MASTER == 31
	#define _MASTER 31
	#define YSIM_STORED_SETTINGS YSIM_RECALL_31
	#if defined _YCM_F@
		#define YSIM_DEFINED
	#else
		#define _YCM_F@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_31 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_31 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_31 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_31 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_31 4
		#else
			#error Undefined master type on 31
		#endif
	#endif
	#define _YCM F@
	#define MAKE_YCM<%0...%1> %0F@%1
	#define _YCM@ _YCM_gF@
	#endinput
#elseif MASTER == 32
	#define _MASTER 32
	#define YSIM_STORED_SETTINGS YSIM_RECALL_32
	#if defined _YCM_G@
		#define YSIM_DEFINED
	#else
		#define _YCM_G@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_32 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_32 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_32 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_32 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_32 4
		#else
			#error Undefined master type on 32
		#endif
	#endif
	#define _YCM G@
	#define MAKE_YCM<%0...%1> %0G@%1
	#define _YCM@ _YCM_gG@
	#endinput
#elseif MASTER == 33
	#define _MASTER 33
	#define YSIM_STORED_SETTINGS YSIM_RECALL_33
	#if defined _YCM_H@
		#define YSIM_DEFINED
	#else
		#define _YCM_H@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_33 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_33 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_33 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_33 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_33 4
		#else
			#error Undefined master type on 33
		#endif
	#endif
	#define _YCM H@
	#define MAKE_YCM<%0...%1> %0H@%1
	#define _YCM@ _YCM_gH@
	#endinput
#elseif MASTER == 34
	#define _MASTER 34
	#define YSIM_STORED_SETTINGS YSIM_RECALL_34
	#if defined _YCM_I@
		#define YSIM_DEFINED
	#else
		#define _YCM_I@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_34 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_34 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_34 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_34 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_34 4
		#else
			#error Undefined master type on 34
		#endif
	#endif
	#define _YCM I@
	#define MAKE_YCM<%0...%1> %0I@%1
	#define _YCM@ _YCM_gI@
	#endinput
#elseif MASTER == 35
	#define _MASTER 35
	#define YSIM_STORED_SETTINGS YSIM_RECALL_35
	#if defined _YCM_J@
		#define YSIM_DEFINED
	#else
		#define _YCM_J@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_35 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_35 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_35 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_35 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_35 4
		#else
			#error Undefined master type on 35
		#endif
	#endif
	#define _YCM J@
	#define MAKE_YCM<%0...%1> %0J@%1
	#define _YCM@ _YCM_gJ@
	#endinput
#elseif MASTER == 36
	#define _MASTER 36
	#define YSIM_STORED_SETTINGS YSIM_RECALL_36
	#if defined _YCM_K@
		#define YSIM_DEFINED
	#else
		#define _YCM_K@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_36 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_36 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_36 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_36 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_36 4
		#else
			#error Undefined master type on 36
		#endif
	#endif
	#define _YCM K@
	#define MAKE_YCM<%0...%1> %0K@%1
	#define _YCM@ _YCM_gK@
	#endinput
#elseif MASTER == 37
	#define _MASTER 37
	#define YSIM_STORED_SETTINGS YSIM_RECALL_37
	#if defined _YCM_L@
		#define YSIM_DEFINED
	#else
		#define _YCM_L@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_37 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_37 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_37 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_37 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_37 4
		#else
			#error Undefined master type on 37
		#endif
	#endif
	#define _YCM L@
	#define MAKE_YCM<%0...%1> %0L@%1
	#define _YCM@ _YCM_gL@
	#endinput
#elseif MASTER == 38
	#define _MASTER 38
	#define YSIM_STORED_SETTINGS YSIM_RECALL_38
	#if defined _YCM_M@
		#define YSIM_DEFINED
	#else
		#define _YCM_M@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_38 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_38 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_38 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_38 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_38 4
		#else
			#error Undefined master type on 38
		#endif
	#endif
	#define _YCM M@
	#define MAKE_YCM<%0...%1> %0M@%1
	#define _YCM@ _YCM_gM@
	#endinput
#elseif MASTER == 39
	#define _MASTER 39
	#define YSIM_STORED_SETTINGS YSIM_RECALL_39
	#if defined _YCM_N@
		#define YSIM_DEFINED
	#else
		#define _YCM_N@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_39 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_39 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_39 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_39 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_39 4
		#else
			#error Undefined master type on 39
		#endif
	#endif
	#define _YCM N@
	#define MAKE_YCM<%0...%1> %0N@%1
	#define _YCM@ _YCM_gN@
	#endinput
#elseif MASTER == 40
	#define _MASTER 40
	#define YSIM_STORED_SETTINGS YSIM_RECALL_40
	#if defined _YCM_O@
		#define YSIM_DEFINED
	#else
		#define _YCM_O@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_40 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_40 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_40 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_40 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_40 4
		#else
			#error Undefined master type on 40
		#endif
	#endif
	#define _YCM O@
	#define MAKE_YCM<%0...%1> %0O@%1
	#define _YCM@ _YCM_gO@
	#endinput
#elseif MASTER == 41
	#define _MASTER 41
	#define YSIM_STORED_SETTINGS YSIM_RECALL_41
	#if defined _YCM_P@
		#define YSIM_DEFINED
	#else
		#define _YCM_P@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_41 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_41 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_41 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_41 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_41 4
		#else
			#error Undefined master type on 41
		#endif
	#endif
	#define _YCM P@
	#define MAKE_YCM<%0...%1> %0P@%1
	#define _YCM@ _YCM_gP@
	#endinput
#elseif MASTER == 42
	#define _MASTER 42
	#define YSIM_STORED_SETTINGS YSIM_RECALL_42
	#if defined _YCM_Q@
		#define YSIM_DEFINED
	#else
		#define _YCM_Q@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_42 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_42 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_42 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_42 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_42 4
		#else
			#error Undefined master type on 42
		#endif
	#endif
	#define _YCM Q@
	#define MAKE_YCM<%0...%1> %0Q@%1
	#define _YCM@ _YCM_gQ@
	#endinput
#elseif MASTER == 43
	#define _MASTER 43
	#define YSIM_STORED_SETTINGS YSIM_RECALL_43
	#if defined _YCM_R@
		#define YSIM_DEFINED
	#else
		#define _YCM_R@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_43 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_43 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_43 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_43 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_43 4
		#else
			#error Undefined master type on 43
		#endif
	#endif
	#define _YCM R@
	#define MAKE_YCM<%0...%1> %0R@%1
	#define _YCM@ _YCM_gR@
	#endinput
#elseif MASTER == 44
	#define _MASTER 44
	#define YSIM_STORED_SETTINGS YSIM_RECALL_44
	#if defined _YCM_S@
		#define YSIM_DEFINED
	#else
		#define _YCM_S@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_44 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_44 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_44 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_44 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_44 4
		#else
			#error Undefined master type on 44
		#endif
	#endif
	#define _YCM S@
	#define MAKE_YCM<%0...%1> %0S@%1
	#define _YCM@ _YCM_gS@
	#endinput
#elseif MASTER == 45
	#define _MASTER 45
	#define YSIM_STORED_SETTINGS YSIM_RECALL_45
	#if defined _YCM_T@
		#define YSIM_DEFINED
	#else
		#define _YCM_T@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_45 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_45 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_45 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_45 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_45 4
		#else
			#error Undefined master type on 45
		#endif
	#endif
	#define _YCM T@
	#define MAKE_YCM<%0...%1> %0T@%1
	#define _YCM@ _YCM_gT@
	#endinput
#elseif MASTER == 46
	#define _MASTER 46
	#define YSIM_STORED_SETTINGS YSIM_RECALL_46
	#if defined _YCM_U@
		#define YSIM_DEFINED
	#else
		#define _YCM_U@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_46 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_46 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_46 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_46 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_46 4
		#else
			#error Undefined master type on 46
		#endif
	#endif
	#define _YCM U@
	#define MAKE_YCM<%0...%1> %0U@%1
	#define _YCM@ _YCM_gU@
	#endinput
#elseif MASTER == 47
	#define _MASTER 47
	#define YSIM_STORED_SETTINGS YSIM_RECALL_47
	#if defined _YCM_V@
		#define YSIM_DEFINED
	#else
		#define _YCM_V@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_47 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_47 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_47 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_47 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_47 4
		#else
			#error Undefined master type on 47
		#endif
	#endif
	#define _YCM V@
	#define MAKE_YCM<%0...%1> %0V@%1
	#define _YCM@ _YCM_gV@
	#endinput
#elseif MASTER == 48
	#define _MASTER 48
	#define YSIM_STORED_SETTINGS YSIM_RECALL_48
	#if defined _YCM_W@
		#define YSIM_DEFINED
	#else
		#define _YCM_W@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_48 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_48 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_48 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_48 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_48 4
		#else
			#error Undefined master type on 48
		#endif
	#endif
	#define _YCM W@
	#define MAKE_YCM<%0...%1> %0W@%1
	#define _YCM@ _YCM_gW@
	#endinput
#elseif MASTER == 49
	#define _MASTER 49
	#define YSIM_STORED_SETTINGS YSIM_RECALL_49
	#if defined _YCM_X@
		#define YSIM_DEFINED
	#else
		#define _YCM_X@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_49 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_49 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_49 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_49 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_49 4
		#else
			#error Undefined master type on 49
		#endif
	#endif
	#define _YCM X@
	#define MAKE_YCM<%0...%1> %0X@%1
	#define _YCM@ _YCM_gX@
	#endinput
#elseif MASTER == 50
	#define _MASTER 50
	#define YSIM_STORED_SETTINGS YSIM_RECALL_50
	#if defined _YCM_Y@
		#define YSIM_DEFINED
	#else
		#define _YCM_Y@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_50 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_50 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_50 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_50 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_50 4
		#else
			#error Undefined master type on 50
		#endif
	#endif
	#define _YCM Y@
	#define MAKE_YCM<%0...%1> %0Y@%1
	#define _YCM@ _YCM_gY@
	#endinput
#elseif MASTER == 51
	#define _MASTER 51
	#define YSIM_STORED_SETTINGS YSIM_RECALL_51
	#if defined _YCM_Z@
		#define YSIM_DEFINED
	#else
		#define _YCM_Z@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_51 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_51 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_51 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_51 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_51 4
		#else
			#error Undefined master type on 51
		#endif
	#endif
	#define _YCM Z@
	#define MAKE_YCM<%0...%1> %0Z@%1
	#define _YCM@ _YCM_gZ@
	#endinput
#endif

