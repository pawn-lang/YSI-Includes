# Internal

## How does this work?

y_master uses a wonderful, and under-utilised, feature of the language called "states".  Each running script is determined to either be in charge or not when they start.  The single script that is in charge is in state `y`, the others are in state `n` (there are more than two states, but the others are only for handover).  This code:

```pawn
foreign ExampleFunc(a);

global ExampleFunc(a)
{
}
```

Compiles as something like:

```pawn
public ExampleFunc(a) <n>
{
	return CallRemoteFunction("ExampleFunc", "i", a);
}

public ExampleFunc(a) <y>
{
}
```

If a script is in charge it calls the function directly (so there is no overhead from using a global function from in the same script).  If it isn't, it calls the remote version in another script.  Now without YSF there's no way to call a function in a single other script, so this will result in an infinite loop as the script will call itself, so we must add a second layer of functions:

```pawn
ExampleFunc(a) <n>
{
	return CallRemoteFunction("ExampleFunc_remote", "i", a);
}

public ExampleFunc_remote(a) <n>
{
	// Do nothing if not in charge.
}

public ExampleFunc_remote(a) <y>
{
	// Call the real version.
	return ExampleFunc(a);
}

ExampleFunc(a) <y>
{
}
```

Still if `ExampleFunc` is called from the master script directly the main code is invoked directly, but now if it isn't there's no infinite loop.  Whilst this code uses the suffix `_remote` for demonstration purposes, the real code uses the prefix `@@` for code-size and generation purposes.

## States

There are five states:

* `y` - Is the current master.
* `n` - Is not the current master.
* `m` - Dummy state used purely for determining automata in global/foreign macros.
* `p` - Was the master, now shut down and out the master system.
* `u` - Have stolen the mastership, but not yet been handed off too.
* `w` - Was the master, but not yet started looking for a new one.

Normal startup:

* Check for an existing master, and go to state `y` or `n` accordingly.  Simple.

Stealing startup:

* Check for an existing master.  If not found, go to state `y`.
* If one is found we need to steal it, so go to state `u` and call the remote `_YCM` function.
* The existing master will have `_YCM` called in state `y`, but see that it is no longer master.  Thus it will go to state `n` and pass off all assets to the new master.
* Other scripts will have `_YCM` called in state `n`, but since we've just set a new master they won't claim it.
* The new master will ALSO have the function `_YCM` called (because it is called in all scripts).  This is why we go to state `u` - to ignore this call and use it to simply move on to state `y`.

While in state `u` the new master acts as a full master for all handoff operations.

Shutdown:

The script shutting down goes to state `p`, then calls the remote `_YCM` function.  While in state `p` `_YCM` won't be called to retake the master, and other script (all in `n`) will behave as normal.

Multi-shutdown:

When the gamemode is ending, all modules associated with it ALSO shut down (not filterscripts though).  This would work without support, but there will be a lot of handing off to scripts that are about to end.  Instead:

* The gamemode signals all modules to end, this puts any masters in state `w`.
* The gamemode ends, passing off it's own master (via `_YCM`) to filterscripts maybe, but nothing in state `w`.
* Any modules that weren't previously master will be in state `n` not state `w` now, but in state `n` they explicitly check for this case so still won't claim the master.
* After the mode is shut down `_YCM` is called again in just the modules, and those in state `w` do the second half of their shutdown - passing off the master to any still running scripts.

