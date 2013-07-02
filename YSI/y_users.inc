#undef _inc_y_users

#include "..\YSI_Players\y_users"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_users
	#endinput
#endif
#define _YSI_3_1_INC_y_users

static stock Use@@YSI_Players@y_users()
{
}

#pragma deprecated Use@@YSI_Players@y_users

forward YSI@y_users();

public YSI@y_users()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Players\y_users>
	
	Instead of:
	
		#include <YSI\y_users>
	*/
	Use@@YSI_Players@y_users();
}

