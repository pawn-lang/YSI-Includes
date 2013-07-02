#undef _inc_y_master

#include "..\YSI_Core\y_master"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_master
	#endinput
#endif
#define _YSI_3_1_INC_y_master

static stock Use@@YSI_Code@y_master()
{
}

#pragma deprecated Use@@YSI_Code@y_master

forward YSI@y_master();

public YSI@y_master()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI_Code\y_master>
	
	Instead of:
	
		#include <YSI\y_master>
	*/
	Use@@YSI_Code@y_master();
}

