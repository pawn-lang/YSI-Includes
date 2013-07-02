#undef _inc_y_playerset

#include "..\YSI_Data\y_playerset"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_playerset
	#endinput
#endif
#define _YSI_3_1_INC_y_playerset

static stock Use@@YSI_Structures@y_playerset()
{
}

#pragma deprecated Use@@YSI_Structures@y_playerset

forward YSI@y_playerset();

public YSI@y_playerset()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Structures\y_playerset>
	
	Instead of:
	
		#include <YSI\y_playerset>
	*/
	Use@@YSI_Structures@y_playerset();
}

