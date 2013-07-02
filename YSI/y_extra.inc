#undef _inc_y_extra

#include "..\YSI_Extra\y_extra"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_extra
	#endinput
#endif
#define _YSI_3_1_INC_y_extra

static stock Use@@YSI_Extra@y_extra()
{
}

#pragma deprecated Use@@YSI_Extra@y_extra

forward YSI@y_extra();

public YSI@y_extra()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI_Extra\y_extra>
	
	Instead of:
	
		#include <YSI\y_extra>
	*/
	Use@@YSI_Extra@y_extra();
}

