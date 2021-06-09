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

Also provides `bool:IsAndroidPlayer(playerid);` and `bool:IsPCPlayer(playerid);`.

