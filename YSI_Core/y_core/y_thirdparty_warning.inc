#if !defined YSI_3P_WARNING
	#endinput
#endif

#if !__COMPILER_USER_WARNING
	#if YSI_3P_WARNING == 1
		#error Could not include "https://github.com/Zeex/amx_assembly" - ensure its files are in "include\amx_assembly\".
	#elseif YSI_3P_WARNING == 2
		#error Please update "https://github.com/Zeex/amx_assembly" to the latest version.
	#elseif YSI_3P_WARNING == 3
		#error Could not include "https://github.com/oscar-broman/md-sort" - ensure its files are in "include\md-sort\".
	#elseif YSI_3P_WARNING == 4
		#error Please update "https://github.com/oscar-broman/md-sort" to the latest version.
	#elseif YSI_3P_WARNING == 5
		#error Could not include "https://github.com/Y-Less/code-parse.inc" - ensure its files are in "include\code-parse\".
	#elseif YSI_3P_WARNING == 6
		#error Please update "https://github.com/Y-Less/code-parse.inc" to the latest version.
	#elseif YSI_3P_WARNING == 7
		#error Could not include "https://github.com/Y-Less/indirection" - ensure its files are in "include\indirection\".
	#elseif YSI_3P_WARNING == 8
		#error Please update "https://github.com/Y-Less/indirection" to the latest version.
	#endif

	#undef YSI_3P_WARNING
	#endinput
#endif

#if YSI_3P_WARNING == 1
	#warning Could not include "https://github.com/Zeex/amx_assembly" - ensure its files are in "include\amx_assembly\".
#elseif YSI_3P_WARNING == 2
	#warning Please update "https://github.com/Zeex/amx_assembly" to the latest version.
#elseif YSI_3P_WARNING == 3
	#warning Could not include "https://github.com/oscar-broman/md-sort" - ensure its files are in "include\md-sort\".
#elseif YSI_3P_WARNING == 4
	#warning Please update "https://github.com/oscar-broman/md-sort" to the latest version.
#elseif YSI_3P_WARNING == 5
	#warning Could not include "https://github.com/Y-Less/code-parse.inc" - ensure its files are in "include\code-parse\".
#elseif YSI_3P_WARNING == 6
	#warning Please update "https://github.com/Y-Less/code-parse.inc" to the latest version.
#elseif YSI_3P_WARNING == 7
	#warning Could not include "https://github.com/Y-Less/indirection" - ensure its files are in "include\indirection\".
#elseif YSI_3P_WARNING == 8
	#warning Please update "https://github.com/Y-Less/indirection" to the latest version.
#endif

#undef YSI_3P_WARNING
#define YSI_3P_ERROR

