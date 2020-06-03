# Features

## Modules

A module is a part of a mode.  People often talk about "modular coding" splitting code in to logically distinct includes, y_master modules simply takes this one step further by splitting code in to logically distinct assemblies (AMXs).  Each module contains some of the code used by the gamemode, and can be reloaded independently.  Find a bug in your fishing job?  Fix it and reload the fishing job code - without even resetting the data.  Modules can reload their code, and pass the existing data (i.e. current server state) to the new version.  So if someone is in the middle of a bank heist when you reload the code, they will STILL be in the middle of the bank heist after the reload.  Importantly, which data to maintain is explicit, so if something must be reset it can be.

The server directory by default looks like something this:

    - samp
      - gamemodes
      - filterscripts
      - pawno
      - plugins
      - scriptfiles
      - samp-server.exe
      - server.cfg

y_master adds a new directory - `modules`:

    - samp
      - gamemodes
      - filterscripts
      - modules
      - pawno
      - plugins
      - scriptfiles
      - samp-server.exe
      - server.cfg

Any scripts placed in here can be manipulated via the new console commands:

* `loadmodule` - Load a module from the `modules/` directory by name.  For example `loadmodule objects` will load file `modules/objects.amx`.
* `unloadmodule` - Unload a previously loaded module by name.
* `reloadmodule` - Reload a previously loaded module by name.  If there is no module with this name already loaded there will be a console warning, but the module will then still load.

** IMPORTANT NOTE: ** `reloadmodule` is different to `reloadfs` in one very important way.  `reloadfs` UNLOADS the old version of the filterscript THEN LOADS the new version.  `reloadmodule` LOADS the new version of the module FIRST, THEN UNLOADS the old version.  This allows the old version to pass control and data to the new version seamlessly if required, and is the basis of the hot-reloading feature enabled by modules.

## Controller Types

There are several types for libraries - "Server", "Client", "Cloud", and "Stub".

* A "Server" library is always in charge - when it loads it instantly takes over.
* A "Client" library is never in charge - it may still contain all the code for the library (since it was built from the same source) but most of that is optimised away.
* A "Stub" library is similar to a "Client" library but only contains `foreign` lines, no `global`s.  Similar to a C header file, this is used to share an API but not an implementation.
* The most interesting case is the "Cloud" library type.  This will negotiate with other running scripts to determine the best one to be in charge.

## Setting The Type

The controller type be set for an entire module, or per library.

For a whole module:

```pawn
// One of:
#define YSI_IS_SERVER
#define YSI_IS_CLIENT
#define YSI_IS_STUB
// No `YSI_IS_STUB` - that's the default.
```

Per library.  These override the module settings:

```pawn
// To enable a setting, one of:
#define YSIM_S_ENABLE // Server
#define YSIM_C_ENABLE // Client
#define YSIM_U_ENABLE // Stub

// To disable a setting, one of:
#define YSIM_S_DISABLE // Server
#define YSIM_C_DISABLE // Client
#define YSIM_U_DISABLE // Stub

// Then include the single library master setup:
#define MASTER 11
#include <YSI_Core\y_master>
```

## Choosing A Master

If two modules with the same library are loaded only one can be put in charge.  Which one depends on load order, type, and version.


A "Cloud" library may or may not be in charge.  When it is loaded it first checks:

1) Are any other modules already in charge?  If not, take control.
2) If they are, are they a server?  If yes, leave them in charge\*.
3) If not, what version are they?  If I'm higher, take control\*\*.
4) If no version is specified (default), its first-come, first-served.

\* Servers simply report their version as `cellmax` to combine two steps).

\*\* You could set a negative version number to always relinquish control to any other module, even those with no version specified.

If a server module is loaded whilst a cloud module is in charge it will always take control.  If two server modules are loaded at once the result is undefined.

