#if !__COMPILER_USER_WARNING
	// If an unused variable warning points you here, see the message below.
	static const YSI_MAYBE_HEAP_MALLOC = 0;
	#endinput
#endif

#if !defined YSI_YES_HEAP_MALLOC
	#warning Heap allocation is VERY unstable.  Use `YSI_NO_HEAP_MALLOC` to disable it, or `YSI_YES_HEAP_MALLOC` to disable this warning.
#endif

