#undef _inc__setup_master_A

#if MASTER == 0
	#define _MASTER 0
	#define YSIM_STORED_SETTINGS YSIM_RECALL_0
	#if defined _YCM_a@
		#define YSIM_DEFINED
	#else
		#define _YCM_a@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_0 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_0 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_0 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_0 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_0 4
		#else
			#error Undefined master type on 0
		#endif
	#endif
	#define _YCM a@
	#define MAKE_YCM<%0...%1> %0a@%1
	#define _YCM@ _YCM_ga@
	#endinput
#elseif MASTER == 1
	#define _MASTER 1
	#define YSIM_STORED_SETTINGS YSIM_RECALL_1
	#if defined _YCM_b@
		#define YSIM_DEFINED
	#else
		#define _YCM_b@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_1 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_1 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_1 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_1 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_1 4
		#else
			#error Undefined master type on 1
		#endif
	#endif
	#define _YCM b@
	#define MAKE_YCM<%0...%1> %0b@%1
	#define _YCM@ _YCM_gb@
	#endinput
#elseif MASTER == 2
	#define _MASTER 2
	#define YSIM_STORED_SETTINGS YSIM_RECALL_2
	#if defined _YCM_c@
		#define YSIM_DEFINED
	#else
		#define _YCM_c@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_2 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_2 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_2 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_2 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_2 4
		#else
			#error Undefined master type on 2
		#endif
	#endif
	#define _YCM c@
	#define MAKE_YCM<%0...%1> %0c@%1
	#define _YCM@ _YCM_gc@
	#endinput
#elseif MASTER == 3
	#define _MASTER 3
	#define YSIM_STORED_SETTINGS YSIM_RECALL_3
	#if defined _YCM_d@
		#define YSIM_DEFINED
	#else
		#define _YCM_d@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_3 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_3 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_3 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_3 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_3 4
		#else
			#error Undefined master type on 3
		#endif
	#endif
	#define _YCM d@
	#define MAKE_YCM<%0...%1> %0d@%1
	#define _YCM@ _YCM_gd@
	#endinput
#elseif MASTER == 4
	#define _MASTER 4
	#define YSIM_STORED_SETTINGS YSIM_RECALL_4
	#if defined _YCM_e@
		#define YSIM_DEFINED
	#else
		#define _YCM_e@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_4 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_4 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_4 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_4 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_4 4
		#else
			#error Undefined master type on 4
		#endif
	#endif
	#define _YCM e@
	#define MAKE_YCM<%0...%1> %0e@%1
	#define _YCM@ _YCM_ge@
	#endinput
#elseif MASTER == 5
	#define _MASTER 5
	#define YSIM_STORED_SETTINGS YSIM_RECALL_5
	#if defined _YCM_f@
		#define YSIM_DEFINED
	#else
		#define _YCM_f@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_5 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_5 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_5 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_5 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_5 4
		#else
			#error Undefined master type on 5
		#endif
	#endif
	#define _YCM f@
	#define MAKE_YCM<%0...%1> %0f@%1
	#define _YCM@ _YCM_gf@
	#endinput
#elseif MASTER == 6
	#define _MASTER 6
	#define YSIM_STORED_SETTINGS YSIM_RECALL_6
	#if defined _YCM_g@
		#define YSIM_DEFINED
	#else
		#define _YCM_g@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_6 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_6 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_6 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_6 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_6 4
		#else
			#error Undefined master type on 6
		#endif
	#endif
	#define _YCM g@
	#define MAKE_YCM<%0...%1> %0g@%1
	#define _YCM@ _YCM_gg@
	#endinput
#elseif MASTER == 7
	#define _MASTER 7
	#define YSIM_STORED_SETTINGS YSIM_RECALL_7
	#if defined _YCM_h@
		#define YSIM_DEFINED
	#else
		#define _YCM_h@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_7 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_7 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_7 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_7 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_7 4
		#else
			#error Undefined master type on 7
		#endif
	#endif
	#define _YCM h@
	#define MAKE_YCM<%0...%1> %0h@%1
	#define _YCM@ _YCM_gh@
	#endinput
#elseif MASTER == 8
	#define _MASTER 8
	#define YSIM_STORED_SETTINGS YSIM_RECALL_8
	#if defined _YCM_i@
		#define YSIM_DEFINED
	#else
		#define _YCM_i@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_8 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_8 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_8 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_8 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_8 4
		#else
			#error Undefined master type on 8
		#endif
	#endif
	#define _YCM i@
	#define MAKE_YCM<%0...%1> %0i@%1
	#define _YCM@ _YCM_gi@
	#endinput
#elseif MASTER == 9
	#define _MASTER 9
	#define YSIM_STORED_SETTINGS YSIM_RECALL_9
	#if defined _YCM_j@
		#define YSIM_DEFINED
	#else
		#define _YCM_j@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_9 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_9 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_9 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_9 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_9 4
		#else
			#error Undefined master type on 9
		#endif
	#endif
	#define _YCM j@
	#define MAKE_YCM<%0...%1> %0j@%1
	#define _YCM@ _YCM_gj@
	#endinput
#elseif MASTER == 10
	#define _MASTER 10
	#define YSIM_STORED_SETTINGS YSIM_RECALL_10
	#if defined _YCM_k@
		#define YSIM_DEFINED
	#else
		#define _YCM_k@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_10 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_10 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_10 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_10 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_10 4
		#else
			#error Undefined master type on 10
		#endif
	#endif
	#define _YCM k@
	#define MAKE_YCM<%0...%1> %0k@%1
	#define _YCM@ _YCM_gk@
	#endinput
#elseif MASTER == 11
	#define _MASTER 11
	#define YSIM_STORED_SETTINGS YSIM_RECALL_11
	#if defined _YCM_l@
		#define YSIM_DEFINED
	#else
		#define _YCM_l@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_11 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_11 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_11 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_11 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_11 4
		#else
			#error Undefined master type on 11
		#endif
	#endif
	#define _YCM l@
	#define MAKE_YCM<%0...%1> %0l@%1
	#define _YCM@ _YCM_gl@
	#endinput
#elseif MASTER == 12
	#define _MASTER 12
	#define YSIM_STORED_SETTINGS YSIM_RECALL_12
	#if defined _YCM_m@
		#define YSIM_DEFINED
	#else
		#define _YCM_m@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_12 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_12 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_12 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_12 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_12 4
		#else
			#error Undefined master type on 12
		#endif
	#endif
	#define _YCM m@
	#define MAKE_YCM<%0...%1> %0m@%1
	#define _YCM@ _YCM_gm@
	#endinput
#elseif MASTER == 13
	#define _MASTER 13
	#define YSIM_STORED_SETTINGS YSIM_RECALL_13
	#if defined _YCM_n@
		#define YSIM_DEFINED
	#else
		#define _YCM_n@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_13 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_13 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_13 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_13 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_13 4
		#else
			#error Undefined master type on 13
		#endif
	#endif
	#define _YCM n@
	#define MAKE_YCM<%0...%1> %0n@%1
	#define _YCM@ _YCM_gn@
	#endinput
#elseif MASTER == 14
	#define _MASTER 14
	#define YSIM_STORED_SETTINGS YSIM_RECALL_14
	#if defined _YCM_o@
		#define YSIM_DEFINED
	#else
		#define _YCM_o@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_14 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_14 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_14 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_14 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_14 4
		#else
			#error Undefined master type on 14
		#endif
	#endif
	#define _YCM o@
	#define MAKE_YCM<%0...%1> %0o@%1
	#define _YCM@ _YCM_go@
	#endinput
#elseif MASTER == 15
	#define _MASTER 15
	#define YSIM_STORED_SETTINGS YSIM_RECALL_15
	#if defined _YCM_p@
		#define YSIM_DEFINED
	#else
		#define _YCM_p@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_15 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_15 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_15 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_15 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_15 4
		#else
			#error Undefined master type on 15
		#endif
	#endif
	#define _YCM p@
	#define MAKE_YCM<%0...%1> %0p@%1
	#define _YCM@ _YCM_gp@
	#endinput
#elseif MASTER == 16
	#define _MASTER 16
	#define YSIM_STORED_SETTINGS YSIM_RECALL_16
	#if defined _YCM_q@
		#define YSIM_DEFINED
	#else
		#define _YCM_q@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_16 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_16 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_16 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_16 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_16 4
		#else
			#error Undefined master type on 16
		#endif
	#endif
	#define _YCM q@
	#define MAKE_YCM<%0...%1> %0q@%1
	#define _YCM@ _YCM_gq@
	#endinput
#elseif MASTER == 17
	#define _MASTER 17
	#define YSIM_STORED_SETTINGS YSIM_RECALL_17
	#if defined _YCM_r@
		#define YSIM_DEFINED
	#else
		#define _YCM_r@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_17 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_17 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_17 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_17 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_17 4
		#else
			#error Undefined master type on 17
		#endif
	#endif
	#define _YCM r@
	#define MAKE_YCM<%0...%1> %0r@%1
	#define _YCM@ _YCM_gr@
	#endinput
#elseif MASTER == 18
	#define _MASTER 18
	#define YSIM_STORED_SETTINGS YSIM_RECALL_18
	#if defined _YCM_s@
		#define YSIM_DEFINED
	#else
		#define _YCM_s@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_18 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_18 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_18 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_18 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_18 4
		#else
			#error Undefined master type on 18
		#endif
	#endif
	#define _YCM s@
	#define MAKE_YCM<%0...%1> %0s@%1
	#define _YCM@ _YCM_gs@
	#endinput
#elseif MASTER == 19
	#define _MASTER 19
	#define YSIM_STORED_SETTINGS YSIM_RECALL_19
	#if defined _YCM_t@
		#define YSIM_DEFINED
	#else
		#define _YCM_t@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_19 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_19 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_19 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_19 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_19 4
		#else
			#error Undefined master type on 19
		#endif
	#endif
	#define _YCM t@
	#define MAKE_YCM<%0...%1> %0t@%1
	#define _YCM@ _YCM_gt@
	#endinput
#elseif MASTER == 20
	#define _MASTER 20
	#define YSIM_STORED_SETTINGS YSIM_RECALL_20
	#if defined _YCM_u@
		#define YSIM_DEFINED
	#else
		#define _YCM_u@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_20 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_20 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_20 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_20 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_20 4
		#else
			#error Undefined master type on 20
		#endif
	#endif
	#define _YCM u@
	#define MAKE_YCM<%0...%1> %0u@%1
	#define _YCM@ _YCM_gu@
	#endinput
#elseif MASTER == 21
	#define _MASTER 21
	#define YSIM_STORED_SETTINGS YSIM_RECALL_21
	#if defined _YCM_v@
		#define YSIM_DEFINED
	#else
		#define _YCM_v@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_21 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_21 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_21 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_21 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_21 4
		#else
			#error Undefined master type on 21
		#endif
	#endif
	#define _YCM v@
	#define MAKE_YCM<%0...%1> %0v@%1
	#define _YCM@ _YCM_gv@
	#endinput
#elseif MASTER == 22
	#define _MASTER 22
	#define YSIM_STORED_SETTINGS YSIM_RECALL_22
	#if defined _YCM_w@
		#define YSIM_DEFINED
	#else
		#define _YCM_w@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_22 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_22 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_22 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_22 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_22 4
		#else
			#error Undefined master type on 22
		#endif
	#endif
	#define _YCM w@
	#define MAKE_YCM<%0...%1> %0w@%1
	#define _YCM@ _YCM_gw@
	#endinput
#elseif MASTER == 23
	#define _MASTER 23
	#define YSIM_STORED_SETTINGS YSIM_RECALL_23
	#if defined _YCM_x@
		#define YSIM_DEFINED
	#else
		#define _YCM_x@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_23 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_23 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_23 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_23 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_23 4
		#else
			#error Undefined master type on 23
		#endif
	#endif
	#define _YCM x@
	#define MAKE_YCM<%0...%1> %0x@%1
	#define _YCM@ _YCM_gx@
	#endinput
#elseif MASTER == 24
	#define _MASTER 24
	#define YSIM_STORED_SETTINGS YSIM_RECALL_24
	#if defined _YCM_y@
		#define YSIM_DEFINED
	#else
		#define _YCM_y@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_24 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_24 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_24 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_24 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_24 4
		#else
			#error Undefined master type on 24
		#endif
	#endif
	#define _YCM y@
	#define MAKE_YCM<%0...%1> %0y@%1
	#define _YCM@ _YCM_gy@
	#endinput
#elseif MASTER == 25
	#define _MASTER 25
	#define YSIM_STORED_SETTINGS YSIM_RECALL_25
	#if defined _YCM_z@
		#define YSIM_DEFINED
	#else
		#define _YCM_z@
		// Save the settings.
		#include "_resolve"
		#if !YSIM_HAS_MASTER
			#define YSIM_RECALL_25 0
		#elseif _YSIM_IS_CLIENT
			#define YSIM_RECALL_25 1
		#elseif _YSIM_IS_SERVER
			#define YSIM_RECALL_25 2
		#elseif _YSIM_IS_CLOUD
			#define YSIM_RECALL_25 3
		#elseif _YSIM_IS_STUB
			#define YSIM_RECALL_25 4
		#else
			#error Undefined master type on 25
		#endif
	#endif
	#define _YCM z@
	#define MAKE_YCM<%0...%1> %0z@%1
	#define _YCM@ _YCM_gz@
	#endinput
#endif

