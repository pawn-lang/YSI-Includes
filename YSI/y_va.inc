#undef _inc_y_va

#include "..\YSI-Coding\y_va"

#if defined _YSI_3_1_INC_y_va
	#endinput
#endif
#define _YSI_3_1_INC_y_va

static stock Use@@YSI_Coding@y_va()
{
}

#pragma deprecated Use@@YSI_Coding@y_va

forward YSI@y_va();

public YSI@y_va()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Coding\y_va>
	
	Instead of:
	
		#include <YSI\y_va>
	*/
	Use@@YSI_Coding@y_va();
}

