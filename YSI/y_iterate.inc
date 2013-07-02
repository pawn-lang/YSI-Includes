#undef _inc_y_iterate

#include "..\YSI-Data\y_iterate"

#if defined _YSI_3_1_INC_y_iterate
	#endinput
#endif
#define _YSI_3_1_INC_y_iterate

static stock Use@@YSI_Structures@y_iterate()
{
}

#pragma deprecated Use@@YSI_Structures@y_iterate

forward YSI@y_iterate();

public YSI@y_iterate()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Structures\y_iterate>
	
	Instead of:
	
		#include <YSI\y_iterate>
	*/
	Use@@YSI_Structures@y_iterate();
}

