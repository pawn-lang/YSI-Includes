#undef _inc_y_amx

#include "..\YSI-Storage\y_amx"

#if defined _YSI_3_1_INC_y_amx
	#endinput
#endif
#define _YSI_3_1_INC_y_amx

static stock Use@@YSI_Storage@y_amx()
{
}

#pragma deprecated Use@@YSI_Storage@y_amx

forward YSI@y_amx();

public YSI@y_amx()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Storage\y_amx>
	
	Instead of:
	
		#include <YSI\y_amx>
	*/
	Use@@YSI_Storage@y_amx();
}

