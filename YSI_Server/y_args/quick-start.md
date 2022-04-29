# Quick Start

This library allows you to read the script-specific command-line parameters in open.mp.  This feature is *only* available in open.mp because it relies on the `arg` pawn library.

```pawn
#include <YSI_Server\y_args>

main()
{
	// Get the `--help` parameter.
	new bool:help;
	if (Args_GetBool('h', "help", help) && help)
	{
		// *help* parameter passed and true.
	}
}
```

The code above can be invoked as something like:

```
.\omp-server.exe arg-test-script -- --help
```

Only parameters after the separate `--` are passed to the script, which can itself have its own `--`:

```
.\omp-server.exe arg-test-script -- --help -- script "rest" parameters.
```

Side note: because of the way quotes are processed on the command-line, the double quotes around `"rest"`in that example will NOT be passed in.

