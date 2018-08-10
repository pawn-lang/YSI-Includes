#if defined _inc_y_groups__include
	#undef _inc_y_groups__include
#endif

#include "y_groups_setup"

// This file is included directly from any YSI library that wants to use groups,
// but groups are only enabled if the end-user explicitly includes y_groups.
// Thus we try include this file many many times and eventually (hopefully) get
// the functions.
#if !defined _Y_GROUPS_USER_REQUESTED
	#endinput
#endif

#if defined Y_COMMANDS_GROUP_NAME
	#define MASTER 51
	#define YSIM_U_DISABLE
	#include "..\..\YSI_Core\y_master"

	#define _GROUP_MAKE_LIMIT       Y_COMMANDS_GROUP_LIMIT
	#define _GROUP_MAKE_NAME        Y_COMMANDS_GROUP_NAME
	#define _GROUP_MAKE_TAG         Y_COMMANDS_GROUP_TAG
	#include "y_groups__funcs"
	#undef Y_COMMANDS_GROUP_LIMIT
	#undef Y_COMMANDS_GROUP_NAME
	#undef Y_COMMANDS_GROUP_TAG

	#include "..\..\YSI_Core\y_master"
#endif

#if defined Y_AREAS_GROUP_NAME
	#define MASTER 50
	#define YSIM_U_DISABLE
	#include "..\..\YSI_Core\y_master"

	#define _GROUP_MAKE_LIMIT       Y_AREAS_GROUP_LIMIT
	#define _GROUP_MAKE_NAME        Y_AREAS_GROUP_NAME
	#define _GROUP_MAKE_TAG         Y_AREAS_GROUP_TAG
	#include "y_groups__funcs"
	#undef Y_AREAS_GROUP_LIMIT
	#undef Y_AREAS_GROUP_NAME
	#undef Y_AREAS_GROUP_TAG

	#include "..\..\YSI_Core\y_master"
#endif

#if defined Y_CLASSES_GROUP_NAME
	#define MASTER 61
	#define YSIM_U_DISABLE
	#include "..\..\YSI_Core\y_master"

	#define _GROUP_MAKE_LIMIT       Y_CLASSES_GROUP_LIMIT
	#define _GROUP_MAKE_NAME        Y_CLASSES_GROUP_NAME
	#define _GROUP_MAKE_TAG         Y_CLASSES_GROUP_TAG
	#include "y_groups__funcs"
	#undef Y_CLASSES_GROUP_LIMIT
	#undef Y_CLASSES_GROUP_NAME
	#undef Y_CLASSES_GROUP_TAG

	#include "..\..\YSI_Core\y_master"
#endif

#if defined Y_RACES_GROUP_NAME
	#define MASTER 53
	#define YSIM_U_DISABLE
	#include "..\..\YSI_Core\y_master"

	#define _GROUP_MAKE_LIMIT       Y_RACES_GROUP_LIMIT
	#define _GROUP_MAKE_NAME        Y_RACES_GROUP_NAME
	#define _GROUP_MAKE_TAG         Y_RACES_GROUP_TAG
	#include "y_groups__funcs"
	#undef Y_RACES_GROUP_LIMIT
	#undef Y_RACES_GROUP_NAME
	#undef Y_RACES_GROUP_TAG

	#include "..\..\YSI_Core\y_master"
#endif

#if defined Y_GTEST_GROUP_NAME
	#define MASTER 60
	#include "..\..\YSI_Core\y_master"

	#define _GROUP_MAKE_LIMIT       Y_GTEST_GROUP_LIMIT
	#define _GROUP_MAKE_NAME        Y_GTEST_GROUP_NAME
	#define _GROUP_MAKE_TAG         Y_GTEST_GROUP_TAG
	#include "y_groups__funcs"
	#undef Y_GTEST_GROUP_LIMIT
	#undef Y_GTEST_GROUP_NAME
	#undef Y_GTEST_GROUP_TAG

	#include "..\..\YSI_Core\y_master"
#endif

//#if defined Y_TIMERS_GROUP_NAME
//	#define _GROUP_MAKE_LIMIT       Y_TIMERS_GROUP_LIMIT
//	#define _GROUP_MAKE_NAME        Y_TIMERS_GROUP_NAME
//	#define _GROUP_MAKE_TAG         Y_TIMERS_GROUP_TAG
//	#include "y_groups__funcs"
//	#undef Y_TIMERS_GROUP_LIMIT
//	#undef Y_TIMERS_GROUP_NAME
//	#undef Y_TIMERS_GROUP_TAG
//#endif
//
//#if defined Y_PROPERTIES_GROUP_NAME
//	#define _GROUP_MAKE_LIMIT       Y_PROPERTIES_GROUP_LIMIT
//	#define _GROUP_MAKE_NAME        Y_PROPERTIES_GROUP_NAME
//	#define _GROUP_MAKE_TAG         Y_PROPERTIES_GROUP_TAG
//	#include "y_groups__funcs"
//	#undef Y_PROPERTIES_GROUP_LIMIT
//	#undef Y_PROPERTIES_GROUP_NAME
//	#undef Y_PROPERTIES_GROUP_TAG
//#endif
//
//#if defined Y_DOBJ_GROUP_NAME
//	#define _GROUP_MAKE_LIMIT       Y_DOBJ_GROUP_LIMIT
//	#define _GROUP_MAKE_NAME        Y_DOBJ_GROUP_NAME
//	#define _GROUP_MAKE_TAG         Y_DOBJ_GROUP_TAG
//	#include "y_groups__funcs"
//	#undef Y_DOBJ_GROUP_LIMIT
//	#undef Y_DOBJ_GROUP_NAME
//	#undef Y_DOBJ_GROUP_TAG
//#endif
//
//#if defined Y_DAREA_GROUP_NAME
//	#define _GROUP_MAKE_LIMIT       Y_DAREA_GROUP_LIMIT
//	#define _GROUP_MAKE_NAME        Y_DAREA_GROUP_NAME
//	#define _GROUP_MAKE_TAG         Y_DAREA_GROUP_TAG
//	#include "y_groups__funcs"
//	#undef Y_DAREA_GROUP_LIMIT
//	#undef Y_DAREA_GROUP_NAME
//	#undef Y_DAREA_GROUP_TAG
//#endif
//
//#if defined Y_DCHECK_GROUP_NAME
//	#define _GROUP_MAKE_LIMIT       Y_DCHECK_GROUP_LIMIT
//	#define _GROUP_MAKE_NAME        Y_DCHECK_GROUP_NAME
//	#define _GROUP_MAKE_TAG         Y_DCHECK_GROUP_TAG
//	#include "y_groups__funcs"
//	#undef Y_DCHECK_GROUP_LIMIT
//	#undef Y_DCHECK_GROUP_NAME
//	#undef Y_DCHECK_GROUP_TAG
//#endif
//
//#if defined Y_DRACECP_GROUP_NAME
//	#define _GROUP_MAKE_LIMIT       Y_DRACECP_GROUP_LIMIT
//	#define _GROUP_MAKE_NAME        Y_DRACECP_GROUP_NAME
//	#define _GROUP_MAKE_TAG         Y_DRACECP_GROUP_TAG
//	#include "y_groups__funcs"
//	#undef Y_DRACECP_GROUP_LIMIT
//	#undef Y_DRACECP_GROUP_NAME
//	#undef Y_DRACECP_GROUP_TAG
//#endif
//
//#if defined Y_DMAPICON_GROUP_NAME
//	#define _GROUP_MAKE_LIMIT       Y_DMAPICON_GROUP_LIMIT
//	#define _GROUP_MAKE_NAME        Y_DMAPICON_GROUP_NAME
//	#define _GROUP_MAKE_TAG         Y_DMAPICON_GROUP_TAG
//	#include "y_groups__funcs"
//	#undef Y_DMAPICON_GROUP_LIMIT
//	#undef Y_DMAPICON_GROUP_NAME
//	#undef Y_DMAPICON_GROUP_TAG
//#endif

#if defined GROUP_LIBRARY_NAME
	#if defined GROUP_LIBRARY_SIZE
		// Include the generic group code for this new custom group.
		// User-inclusion.
		#define _GROUP_MAKE_LIMIT       GROUP_LIBRARY_SIZE
		#define _GROUP_MAKE_NAME        GROUP_LIBRARY_NAME
		#if defined GROUP_LIBRARY_TAGS
			#define _GROUP_MAKE_TAG         GROUP_LIBRARY_TAGS
		#else
			#define _GROUP_MAKE_TAG _
		#endif
		#include "y_groups__funcs"
		// Now remove the defines.
		#if defined GROUP_LIBRARY_TAGS
			#undef GROUP_LIBRARY_TAGS
		#endif
		#undef GROUP_LIBRARY_NAME
		#undef GROUP_LIBRARY_SIZE
	#else
		#error You must define both GROUP_LIBRARY_SIZE and GROUP_LIBRARY_NAME.
	#endif
#else
	#if defined GROUP_LIBRARY_SIZE
		#error You must define both GROUP_LIBRARY_SIZE and GROUP_LIBRARY_NAME.
	#endif
#endif

