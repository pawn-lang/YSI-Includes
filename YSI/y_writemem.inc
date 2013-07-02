#undef _inc_y_writemem

#include "..\YSI-Internal\y_writemem"

#if defined _YSI_3_1_INC_y_writemem
	#endinput
#endif
#define _YSI_3_1_INC_y_writemem

static stock Use@@YSI_Internal@y_writemem()
{
}

#pragma deprecated Use@@YSI_Internal@y_writemem

forward YSI@y_writemem();

public YSI@y_writemem()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Internal\y_writemem>
	
	Instead of:
	
		#include <YSI\y_writemem>
	*/
	Use@@YSI_Internal@y_writemem();
}

