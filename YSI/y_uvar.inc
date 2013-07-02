#undef _inc_y_uvar

#include "..\YSI-Storage\y_uvar"

#if defined _YSI_3_1_INC_y_uvar
	#endinput
#endif
#define _YSI_3_1_INC_y_uvar

static stock Use@@YSI_Storage@y_uvar()
{
}

#pragma deprecated Use@@YSI_Storage@y_uvar

forward YSI@y_uvar();

public YSI@y_uvar()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Storage\y_uvar>
	
	Instead of:
	
		#include <YSI\y_uvar>
	*/
	Use@@YSI_Storage@y_uvar();
}

