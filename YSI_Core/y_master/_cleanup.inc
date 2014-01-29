#if AUTO_INCLUDE_GUARD
	#undef _inc__cleanup
#endif

// Remote hook
#undef RH

// Remote timer
#undef RT

// Remote command
#undef RC

// Remote ALS
#undef RA

#undef Master_Caller

// New hooks
#undef master_hook
#undef master_task
#undef master_ptask
#undef master_func
#undef group_hook
#undef @foreign
#undef foreign
#undef global

//#undef Master_Init

// Clear any previous settings.
#undef YSIM_HAS_MASTER
#undef _YSIM_IS_CLIENT
#undef _YSIM_IS_SERVER
#undef _YSIM_IS_CLOUD
#undef _YSIM_IS_STUB

#undef _YCM
#undef MAKE_YCM
#undef _YCM@

#if defined YSIM_DEFINED
	// Everything else in this file will already be set.  This might not.
	#undef YSIM_DEFINED
#endif

#if defined _MASTER
	#undef _MASTER
#endif

