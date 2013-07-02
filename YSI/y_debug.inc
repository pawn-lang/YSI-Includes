#undef _inc_y_debug

#include "..\YSI-Core\y_debug"

#if defined _YSI_3_1_INC_y_debug
	#endinput
#endif
#define _YSI_3_1_INC_y_debug

static stock Use@@YSI_Code@y_debug()
{
}

#pragma deprecated Use@@YSI_Code@y_debug

forward YSI@y_debug();

public YSI@y_debug()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Code\y_debug>
	
	Instead of:
	
		#include <YSI\y_debug>
	*/
	Use@@YSI_Code@y_debug();
}

