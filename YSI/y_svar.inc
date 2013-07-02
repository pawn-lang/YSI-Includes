#undef _inc_y_svar

#include "..\YSI_Storage\y_svar"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_svar
	#endinput
#endif
#define _YSI_3_1_INC_y_svar

static stock Use@@YSI_Storage@y_svar()
{
}

#pragma deprecated Use@@YSI_Storage@y_svar

forward YSI@y_svar();

public YSI@y_svar()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI_Storage\y_svar>
	
	Instead of:
	
		#include <YSI\y_svar>
	*/
	Use@@YSI_Storage@y_svar();
}

