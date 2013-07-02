#undef _inc_y_testing

#include "..\YSI_Core\y_testing"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_testing
	#endinput
#endif
#define _YSI_3_1_INC_y_testing

static stock Use@@YSI_Code@y_testing()
{
}

#pragma deprecated Use@@YSI_Code@y_testing

forward YSI@y_testing();

public YSI@y_testing()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI_Code\y_testing>
	
	Instead of:
	
		#include <YSI\y_testing>
	*/
	Use@@YSI_Code@y_testing();
}

