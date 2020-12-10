## Features

### Optional Parameters

The inline callbacks for y_dialogs very frequently don't need either the playerid nor the dialogid, so you can omit them:

This is valid:

```pawn
inline Inline(pid, did, response, listitem, string:inputtext[])
{
	#pragma unused pid, did
}
Dialog_ShowCallback(playerid, using inline Inline, "Title", "Caption", "Button 1");
```

However, to save time, this is also valid:

```pawn
inline Inline(response, listitem, string:inputtext[])
{
}
Dialog_ShowCallback(playerid, using inline Inline, "Title", "Caption", "Button 1");
```

Note that you must either have ALL the parameters or just those three - you can't mix and match any other combinations.  This also won't easily work for `using public` unless you give the type explicitly.

```pawn
public Public(response, listitem, string:inputtext[])
{
}
Dialog_ShowCallback(playerid, using public Public<iis>, "Title", "Caption", "Button 1");
```

