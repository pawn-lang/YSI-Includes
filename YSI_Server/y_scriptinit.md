# y_scriptinit

Provides several new initialisation callbacks to avoid knowing what the current script type is.  The full initialisation order is:

* `OnCodeInit` - Called first to generate code.  No advanced YSI features are available here (including hooking this callback).
* `OnJITCompile` - If this is running in the JIT.
* `PREINIT__` - Special init functions, used for tiny setup code (more light-weight than hooks).
* `OnScriptInit` - Called when this script starts.  This is the most important callback as it is called once first, regardless of the script type, and all YSI features are now available.
* `POSTINIT__` - Special init functions, used for tiny setup code (more light-weight than hooks).
* `OnFilterScriptInit` - If this is a filterscript.
* `OnGameModeInit` - Once in a gamemode, possibly multiple times in a filterscript.

The shutdown order is:

* `OnGameModeExit` - Once in a gamemode, possibly multiple times in a filterscript.
* `OnFilterScriptExit` - If this is a filterscript.
* `OnScriptExit` - Called when this script ends, regardless of the type.

## YSI

For general YSI information, see the following links:

* [Installation](../installation.md)
* [Troubleshooting](../troubleshooting.md)

## Documentation

* [Quick Start](y_scriptinit/quick-start.md) - One very simple example of getting started with this library.
* [Features](y_scriptinit/features.md) - More features and examples.
* [FAQs](y_scriptinit/faqs.md) - Frequently Asked Questions, including errors and solutions.
* [API](y_scriptinit/api.md) - Full list of all functions and their meaning.
* [Internal](y_scriptinit/internal.md) - Internal developer documentation for the system.

## External Links

These are links to external documentation and tutorials; both first- and third-party.  Note that these may be incomplete, obsolete, or otherwise inaccurate.

