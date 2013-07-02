#undef _inc_y_ini

#include "..\YSI-Storage\y_ini"

#if defined _YSI_3_1_INC_y_ini
	#endinput
#endif
#define _YSI_3_1_INC_y_ini

static stock Use@@YSI_Storage@y_ini()
{
}

#pragma deprecated Use@@YSI_Storage@y_ini

forward YSI@y_ini();

public YSI@y_ini()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Storage\y_ini>
	
	Instead of:
	
		#include <YSI\y_ini>
	*/
	Use@@YSI_Storage@y_ini();
}

