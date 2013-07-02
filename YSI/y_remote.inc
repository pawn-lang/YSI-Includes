#undef _inc_y_remote

#include "..\YSI-Coding\y_remote"

#if defined _YSI_3_1_INC_y_remote
	#endinput
#endif
#define _YSI_3_1_INC_y_remote

static stock Use@@YSI_Coding@y_remote()
{
}

#pragma deprecated Use@@YSI_Coding@y_remote

forward YSI@y_remote();

public YSI@y_remote()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Coding\y_remote>
	
	Instead of:
	
		#include <YSI\y_remote>
	*/
	Use@@YSI_Coding@y_remote();
}

