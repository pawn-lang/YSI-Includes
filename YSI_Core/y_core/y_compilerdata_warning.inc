// This file is here to use `#warning` without giving an error on the old
// compiler.  Just enclosing it in `#if`/`#endif` is not enough.
#if !__COMPILER_USER_WARNING
	// Old compiler, doens't support `#warning`.
	#endinput
#endif

#if defined _inc_y_compilerdata_warning
	#undef _inc_y_compilerdata_warning
#endif

#if !defined Y_COMPILERDATA_WARNING
	#error y_compilerdata_warning called with no warning selected.
#endif

#if Y_COMPILERDATA_WARNING == 2
	#warning Semicolons were disabled (`-;-`).  Re-enabling them as YSI requires them.
#elseif Y_COMPILERDATA_WARNING == 3
	#warning YSI_MAX_STRING changed.  This may require explicit changes (but they will error for you).
#else
	#error y_compilerdata_warning called with an invalid warning selected.
	#endinput
#endif

#undef Y_COMPILERDATA_WARNING

