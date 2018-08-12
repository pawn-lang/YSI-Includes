# Functions.

## `Server_IsGameMode()`

Returns `true` if the current script is running as a gamemode.

## `Server_IsFilterscript()`

Returns `true` if the current script is running as a filterscript.

## `Server_JITExists()`

Returns `true` if the JIT plugin is loaded.  Note that this does NOT mean that the code is JIT compiled, the compilation can still fail.

## `Server_JITComplete()`

Returns `true` if the code has been JIT compiled.

## `Server_CrashDetectExists()`

Returns `true` if the crashdetect plugin is loaded.

# Variables

## `YSI_FILTERSCRIPT`

`true` if the current script is running as a filterscript.

# Macros

## `PREINIT__`

Pre-initialisation functions (called before `OnScriptInit`).  Example:

```pawn
PREINIT__ VehicleStreamer()
{
	printf("Vehicle Streamer installed");
}
```

## `POSTINIT__`

Post-initialisation functions (called after `OnScriptInit`).  Example:

```pawn
POSTINIT__ VehicleStreamer()
{
	printf("Vehicle Streamer initialised");
}
```

## `FINAL__`

Creates a run-time constant, with compiler enforcement.  The value is set in the global scope.  Example:

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

# Callbacks

## `OnScriptInit()`

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

## `OnCodeInit()`

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

## `OnScriptExit()`

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

