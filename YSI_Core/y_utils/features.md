## New Timers

`SetTimer` and `SetTimerEx` now take function references as well as string:

```pawn
static stock TimerFunc(playerid)
{
	SendClientMessage(playerid, COLOUR_MESSAGE, "Hello");
}

SetTimerEx(&TimerFunc, 1000, false, "i", playerid);
```

This has four advantages:

1. Using `&Func` here will check that the parameters given to `SetTimerEx` are valid for the target function (in a similar way to y_timers, but not quite as good - you still need to manually provide the specifier string).
2. If you never call the function that starts the timer, the function that the timer calls won't be compiled!  This way by far the main reason for doing this - to prevent several public functions strewn throughout YSI from being compiled if their corresponding features weren't used.
3. You can correctly scope a function to only the current file.
4. Doesn't bloat the header.  This isn't a huge advantage, but worth mentioning at least.

If you don't want to have the parameter checking, you can use the `SetTimerEx(&TimerFunc<i>, 1000, false, "i", playerid);` syntax instead.

