#undef _inc_y_lock

#include "..\YSI-Server\y_lock"

#if defined _YSI_3_1_INC_y_lock
	#endinput
#endif
#define _YSI_3_1_INC_y_lock

static stock Use@@YSI_Server@y_lock()
{
}

#pragma deprecated Use@@YSI_Server@y_lock

forward YSI@y_lock();

public YSI@y_lock()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Server\y_lock>
	
	Instead of:
	
		#include <YSI\y_lock>
	*/
	Use@@YSI_Server@y_lock();
}

