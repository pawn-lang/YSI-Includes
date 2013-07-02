#undef _inc_y_punycode

#include "..\YSI-Server\y_punycode"

#if defined _YSI_3_1_INC_y_punycode
	#endinput
#endif
#define _YSI_3_1_INC_y_punycode

static stock Use@@YSI_Server@y_punycode()
{
}

#pragma deprecated Use@@YSI_Server@y_punycode

forward YSI@y_punycode();

public YSI@y_punycode()
{
	/*
	YSI's structure has changed.  Please use:
	
		#include <YSI-Server\y_punycode>
	
	Instead of:
	
		#include <YSI\y_punycode>
	*/
	Use@@YSI_Server@y_punycode();
}

