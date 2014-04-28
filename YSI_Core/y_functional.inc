// Pretty much all we need.

#if defined _INC_y_functional
	#endinput
#endif
#define _INC_y_functional

#include "y_utils"
#include y_debug
#include "..\YSI_Storage\y_amx"
#include "..\YSI_Coding\y_inline"

#include "..\amx\disasm"
#include "..\amx\asm"
#include "..\amx\frame_info"

#include "y_functional/impl"
#include "y_functional/rewrite"

#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_functional/tests"
#endif

