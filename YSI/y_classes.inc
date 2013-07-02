#undef _inc_y_classes

#include "..\YSI_Visual\y_classes"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_classes
	#endinput
#endif
#define _YSI_3_1_INC_y_classes

static stock Use@@YSI_Visual@y_classes()
{
}

#pragma deprecated Use@@YSI_Visual@y_classes

forward YSI@y_classes();

public YSI@y_classes()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI_Visual\y_classes>
	
	Instead of:
	
		#include <YSI\y_classes>
	*/
	Use@@YSI_Visual@y_classes();
}

