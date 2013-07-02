#undef _inc_y_utils

#include "..\YSI-Core\y_utils"

#if defined _YSI_3_1_INC_y_utils
	#endinput
#endif
#define _YSI_3_1_INC_y_utils

static stock Use@@YSI_Code@y_utils()
{
}

#pragma deprecated Use@@YSI_Code@y_utils

forward YSI@y_utils();

public YSI@y_utils()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Code\y_utils>
	
	Instead of:
	
		#include <YSI\y_utils>
	*/
	Use@@YSI_Code@y_utils();
}

