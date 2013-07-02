#undef _inc_y_xml

#include "..\YSI_Storage\y_xml"

#endinput

// Future deprecation...
#if defined _YSI_3_1_INC_y_xml
	#endinput
#endif
#define _YSI_3_1_INC_y_xml

static stock Use@@YSI_Storage@y_xml()
{
}

#pragma deprecated Use@@YSI_Storage@y_xml

forward YSI@y_xml();

public YSI@y_xml()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI_Storage\y_xml>
	
	Instead of:
	
		#include <YSI\y_xml>
	*/
	Use@@YSI_Storage@y_xml();
}

