#undef _inc_y_stringhash

#include "..\YSI_Coding\y_stringhash"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_stringhash
	#endinput
#endif
#define _YSI_3_1_INC_y_stringhash

static stock Use@@YSI_Coding@y_stringhash()
{
}

#pragma deprecated Use@@YSI_Coding@y_stringhash

forward YSI@y_stringhash();

public YSI@y_stringhash()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Coding\y_stringhash>
	
	Instead of:
	
		#include <YSI\y_stringhash>
	*/
	Use@@YSI_Coding@y_stringhash();
}

