#undef _inc_y_als

#include "..\YSI_Core\y_als"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_als
	#endinput
#endif
#define _YSI_3_1_INC_y_als

static stock Use@@YSI_Code@y_als()
{
}

#pragma deprecated Use@@YSI_Code@y_als

forward YSI@y_als();

public YSI@y_als()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI_Code\y_als>
	
	Instead of:
	
		#include <YSI\y_als>
	*/
	Use@@YSI_Code@y_als();
}

