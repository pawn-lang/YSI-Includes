# Features

## `OnCodeInit`

Called first to generate code.  No advanced YSI features are available here (including hooking this callback).  If the JIT plugin is in use, this is called from `OnJITCompile`, which means it is the main place to perform code generation.  This is why not many YSI features are available - because they might not have been set up yet.

```pawn
ReturnFive()
{
	// To be changed to be correct!
	return 3;
}

public OnCodeInit()
{
	// Generate some code.
	new ctx[AsmContext];

	// Target `ReturnFive` for rewriting.
	AsmInitPtr(ctx, addressof (ReturnFive<>), 16);

	// Write the correct code (`ctx` is used implicitly here).
	@emit PROC
	@emit CONST.pri 5
	@emit RETN

	// Basic ALS forwarding only!
	#if defined Example_OnCodeInit
		Example_OnCodeInit();
	#endif
	return 1;
}

#undef OnCodeInit
#define OnCodeInit Example_OnCodeInit
#if defined Example_OnCodeInit
	forward Example_OnCodeInit();
#endif
```

## `OnScriptInit`

Called when this script starts.  This is the most important callback as it is called once first, regardless of the script type, and all YSI features are now available.

```pawn
// Hooks are now available, as are all other YSI features.
hook OnScriptInit()
{
	printf("================================");
	printf("||                            ||");
	printf("||      My Mode Started!      ||");
	printf("||                            ||");
	printf("================================");
	printf("||                            ||");
	printf("|| Context information:       ||");
	printf("||                            ||");
	printf("|| - Gamemode? %s            ||", Server_IsGameMode() ? ("yes") : ("no "));
	printf("|| - Filterscript? %s        ||", Server_IsFilterscript() ? ("yes") : ("no "));
	printf("|| - JIT plugin? %           ||", Server_JITExists() ? ("yes") : ("no "));
	printf("||   %s               ||"       , Server_JITComplete() ? ("(compiled)") : ("(failed)  "));
	printf("|| - CrashDetect plugin? %s  ||", Server_CrashDetectExists() ? ("yes") : ("no "));
	printf("||                            ||");
	printf("================================");
}
```

## `PREINIT__`

This is a macro for more light-weight initialisations.  It is called just before `OnScriptInit`, and is used for minor variables and settings.  Note that each `INIT__` function must have a unique name, unlike hooks*.

```pawn
PREINIT__ VehicleStreamer()
{
	printf("Vehicle Streamer installed");
}
```

\* Technically hooks also need a unique name, but that is taken care of by y_unique.

## `POSTINIT__`

This is identical to `PREINIT__`, but called after `OnScriptInit`.

```pawn
POSTINIT__ VehicleStreamer()
{
	printf("Vehicle Streamer initialised");
}
```

## `PREEXIT__`

This is identical to `PREINIT__`, but called before `OnScriptExit`.

## `POSTEXIT__`

This is identical to `PREINIT__`, but called after `OnScriptExit`.

```pawn
POSTINIT__ VehicleStreamer()
{
	printf("Vehicle Streamer initialised");
}
```

## `FINAL__`

Creates a run-time constant, with compiler enforcement.  The value is set in the global scope.

```pawn
#include <a_samp>
#include <YSI_Server\y_scriptinit>

FINAL__ gMaxPlayers = GetMaxPlayers();

main()
{
	// Set correctly.
	printf("%d", gMaxPlayers);

	// Compile-time error
	gMaxPlayers = 44;
}
```

This is also usable as `final` (without `YSI_NO_KEYWORD_final`).

Tags are also checked:

```pawn
FINAL__ Float:gMaxPlayers = GetMaxPlayers(); // Tag mismatch warning.
```

## `final`

Keyword-like macro for `FINAL__`.

```pawn
#include <a_samp>
#include <YSI_Server\y_scriptinit>

final gMaxPlayers = GetMaxPlayers();

main()
{
	// Set correctly.
	printf("%d", gMaxPlayers);

	// Compile-time error
	gMaxPlayers = 44;
}
```

## `YSI_KEYWORD_final`

When defined enables the `final` keyword:

```pawn
#define YSI_COMPATIBILITY_MODE
#define YSI_KEYWORD_final

#include <a_samp>
#include <YSI_Server\y_scriptinit>

final gMaxPlayers = GetMaxPlayers();
```

See [YSI_COMPATIBILITY_MODE](../../YSI_COMPATIBILITY_MODE.md) for more information.

## `YSI_NO_KEYWORD_final`

When defined disables the `final` keyword:

```pawn
#define YSI_NO_KEYWORD_final

#include <a_samp>
#include <YSI_Server\y_scriptinit>

final gMaxPlayers = GetMaxPlayers(); // Error.
```

See [YSI_COMPATIBILITY_MODE](../../YSI_COMPATIBILITY_MODE.md) for more information.

## `OnScriptExit`

Called when this script ends, regardless of the type.

```pawn
hook OnScriptExit()
{
	printf("================================");
	printf("||                            ||");
	printf("||       My Mode Ended!       ||");
	printf("||                            ||");
	printf("================================");
	printf("||                            ||");
	printf("|| It was a %s      ||", Server_IsGameMode() ? ("gamemode    ") : ("filterscript"));
	printf("||                            ||");
	printf("================================");
}
```

## Init Order

Due to the multiple different `Init` functions there now are, the order between initialisation functions has got sadly very complicated.  For the most part this doesn't matter, if you only stick to one.  The issue comes when combining them.  The full order is as follows:

* `OnCodeInit()`  This is the very first initialisation, and is used to actually generate new code.  Many special features like `hook` or `foreach` will probably not work in this callback, because the code hasn't been compiled fully yet.
* `OnYSIInit()`  A completely internal callback, used by YSI only.
* `OnJITCompile()`  If you're using the JIT plugin, this callback comes next, and can also be used to set up code.
* `PREINIT__`  Any functions declared with `PREEXIT__`.
* `OnScriptInit()`  The standard initialisation callback.  After all code initialisation is complete, and the same for all script types.
* `POSTINIT__`  Any functions declared with `POSTEXIT__`.
* `OnFilterScriptInit()`  If the script is loaded as a filterscript.
* `OnGameModeInit()`  Any time a gamemode starts.  May be called multiple times in a filterscript.
* `main()`  Called only in the gamemode.

You can also declare functions with `@init`:

* `@init(init_code) A() {}`  Called as part of `OnCodeInit`.
* `@init() B() {}`                    Called as part of `OnScriptInit`.
* `@init(init_script) C() {}`         Also called as part of `OnScriptInit`.
* `@init(.order = init_mode) D() {}`  Called as part of `OnGameModeInit`
* `@init(init_mode) E() {}`           Called as part of `OnFilterScriptInit`
* `@init(.order = init_main) F() {}`  Called as part of `main`

To make things even more complicated, there are of course hook orders to consider.  All hooks within each category are called in the order they are included in, unless explicitly overwritten:

* Pre-hooks.  See the y_hooks documentation for exactly how to declare these.  They don't rely on y_hooks, but ensure these functions are called first.
* y_hooks.  `hook`, `@hook`, `HOOK__`, etc.  The order within hooks can be controlled by `@###` suffixes on the function names.
* ALS.  The old style of hooks.
* `public`.  Finally the main function in the script.

