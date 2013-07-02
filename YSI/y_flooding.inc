#undef _inc_y_flooding

#include "..\YSI_Server\y_flooding"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_flooding
	#endinput
#endif
#define _YSI_3_1_INC_y_flooding

static stock Use@@YSI_Server@y_flooding()
{
}

#pragma deprecated Use@@YSI_Server@y_flooding

forward YSI@y_flooding();

public YSI@y_flooding()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Server\y_flooding>
	
	Instead of:
	
		#include <YSI\y_flooding>
	*/
	Use@@YSI_Server@y_flooding();
}

