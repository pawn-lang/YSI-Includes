#undef _inc_y_td

#include "..\YSI_Server\y_td"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_td
	#endinput
#endif
#define _YSI_3_1_INC_y_td

static stock Use@@YSI_Server@y_td()
{
}

#pragma deprecated Use@@YSI_Server@y_td

forward YSI@y_td();

public YSI@y_td()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Server\y_td>
	
	Instead of:
	
		#include <YSI\y_td>
	*/
	Use@@YSI_Server@y_td();
}

