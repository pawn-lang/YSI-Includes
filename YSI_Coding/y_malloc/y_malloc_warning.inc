#if !__COMPILER_USER_WARNING
	// If an unused variable warning points you here, see the message below.
	static const YSI_MAYBE_HEAP_MALLOC = 0;
	#endinput
#endif

#warning y_malloc heap allocation is unstable.  Use `YSI_NO_HEAP_MALLOC` to disable it, or `YSI_YES_HEAP_MALLOC` to disable this warning: git.io/YSI_HEAP_MALLOC

