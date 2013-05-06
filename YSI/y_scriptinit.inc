#undef _inc_y_scriptinit
#include "..\YSI-Server\y_scriptinit"

static stock Use@@YSI_Server@y_scriptinit()
{
}

#pragma deprecated Use@@YSI_Server@y_scriptinit

forward YSI@y_scriptinit();

public YSI@y_scriptinit()
{
	Use@@YSI_Server@y_scriptinit();
}

