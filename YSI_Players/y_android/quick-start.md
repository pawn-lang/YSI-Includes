# y_android

Detects when a player is using the illegal Android client:

```pawn
#include <YSI_Players\y_android>

public OnAndroidCheck(playerid, bool:isDisgustingThiefToBeBanned)
{
	if (isDisgustingThiefToBeBanned)
	{
		Ban(playerid);
	}
}
```

Also provides `bool:IsAndroidPlayer(playerid);` and `bool:IsPCPlayer(playerid);`.  These functions will BOTH return `false` before the `OnAndroidCheck` callback has fired, so they are unreliable in places like `OnPlayerConnect`.  This is because of how the checks request data after the player has joined.
