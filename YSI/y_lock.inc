#undef _inc_y_lock
#include "..\YSI-Server\y_lock"

static stock Use@@YSI_Server@y_lock()
{
}

#pragma deprecated Use@@YSI_Server@y_lock

forward YSI@y_lock();

public YSI@y_lock()
{
	Use@@YSI_Server@y_lock();
}

