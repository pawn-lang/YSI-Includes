## Errors and Warnings.

* `warning 202: number of arguments does not match definition` on `Dialog_Show...`?

y_dialogs was vastly simplified to no longer use dialog IDs.  Since a user can only ever see one dialog, there is literally no need for an ID - the callback response is for whichever one they were looking at.  Previously the final parameter could be used to override the ID used by YSI, but since this change the ID is always the same (and internal - you don't need to know it*) the last parameter is pointless.  It used to just be silently ignored, but a warning that something changed is much better, thus the parameter was entirely removed.

Just remove the last parameter and prefer using `Dialog_ShowCallback` to process the data locally.

\* But if you really want to, it is `_A<_yD@>`, or `1078229343`.

* `error 017: undefined symbol "dialog"` on `Dialog_Show...`?

This is the same problem as the previous question, but when named parameter syntax was used as `Dialog_Show(playerid, style, title, text, button, .dialog = 42);`.

The solution is also the same: Just remove the last parameter and prefer using `Dialog_ShowCallback` to process the data locally.

* `warning 213: tag mismatch: expected tag "F@_@iiiis", but found "F@_@"` on `Dialog_ShowCallback`.

This is related to the recent y_inline improvement - it now checks that the callback given has the correct parameters.  For inline functions this is not a problem, but for publics, y_inline sadly can't determine the parameters:

```pawn
forward Response(pid, dialogid, response, listitem, string:inputtext[]);

public Response(pid, dialogid, response, listitem, string:inputtext[])
{
}

Dialog_ShowCallback(playerid, using public Response, style, title, text, button1, button2);
```

`Dialog_ShowCallback` requires a callback with specifier type `iiiis`.  This public DOES have those, but y_inline can't prove that so it defaults to none.  To remove this warning, you need to be explicit:

```pawn
forward Response(pid, dialogid, response, listitem, string:inputtext[]);

public Response(pid, dialogid, response, listitem, string:inputtext[])
{
}

Dialog_ShowCallback(playerid, using public Response<iiiis>, style, title, text, button1, button2);
```

Again, for inline functions the type is known.

* `warning 213: tag mismatch: expected tag "F@_@iiiis", but found ...` on `Dialog_ShowCallback`.

This is similar to the last warning, but when you pass an inline function with the wrong parameters.  For example:

```pawn
inline Response(pid, dialogid, response, listitem)
{
}
Dialog_ShowCallback(playerid, using inline Response, style, title, text, button1, button2);
```

Here the last parameter (`string:inputtext[]`) is missing - and the compiler tells you so.

