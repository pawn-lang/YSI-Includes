# Quick Start

```pawn
// Define this function in this script.
remotefunc void:LocalAndMaybeRemote(string:stringArg[], intArg, Float:floatArg)
{
	printf("%s, %d, %.2f", stringArg, intArg floatArg);
}

// Declare this function as in another script.
remotefunc OnlyRemote(arrayArg[], sizeArg);

main()
{
	// Call this function in all scripts at once.
	broadcastfunc LocalAndMaybeRemote("hello", 42, 4.2);

	// Try call this function only in the current script.  This will error because you can't
	// store a `void:` return.
	new ret = localfunc LocalAndMaybeRemote("hello", 42, 4.2);

	// Call this function in OTHER scripts, since it isn't here.  Arrays must be followed by their
	// length, strings don't need to be (hence `string:` to differentiate them).
	new arr[55];
	broadcastfunc OnlyRemote(arr, sizeof (arr));
}
```

