# Quick Start

```pawn
#include <YSI_Coding\y_inline>

CMD:pick(playerid, params[])
{
	// Called when the player responds to the dialog.
	inline const Response(pid, dialogid, response, listitem, string:inputtext[])
	{
		// `playerid` and `pid` are always the same - so we only really need
		// one of them (`pid` would be required if the inline was elsewhere).
		#pragma unused pid, dialogid, inputtext
		
		if (response)
		{
			va_SendClientMessage(playerid, COLOUR_MSG, "You picked: %d", listitem);
		}
		else
		{
			SendClientMessage(playerid, COLOUR_MSG, "You pressed cancel");
		}
	}
	Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_LIST, "Pick a number", "0\n1\n2\n3\n4", "OK", "Cancel");
	return 1;
}
```

