#if defined _INC_y_extra
	#endinput
#endif
#define _INC_y_extra

#tryinclude <sscanf2>
#tryinclude <sscanf3>

#if !defined sscanf || !defined WP_Hash
	#error y_extra requires plugins - please install sscanf and whirlpool.
#endif

// If you want to use y_extra, you need to use these (but nothing else).
#include "..\YSI_Visual\y_commands"
#include "..\YSI_Players\y_text"

#if defined _inc_y_users
	#include "extra\y_extra_users"
#endif

// Don't need to check for y_languages being included as it's done by y_text.
#include "extra\y_extra_languages"

#include "extra\y_extra_other"
