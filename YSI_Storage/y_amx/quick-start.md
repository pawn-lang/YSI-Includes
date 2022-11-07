# y_amx

```pawn
#include <YSI_Storage\y_amx>

public OnScriptInit()
{
	// List all the player callbacks in this script.
	new
		idx,
		name[FUNCTION_LENGTH];
	while ((idx = AMX_GetPublicName(idx, name, "OnPlayer")))
	{
		printf("Callback: %s", name);
	}
}
```

There are few important concepts from the AMX format you need to understand before using this library:

* ***table*** - A table is a part of the AMX header that lists something.  There are five headers - public functions, public variables ("PubVar"s), libraries, tags, and native functions.
* ***entry*** - An entry is a single item in one of the tables.  An entry contains a pointer to the data and a pointer to the name.  For public and native functions the pointer is to the code, for pubvars the pointer is to the data, libraries don't have a pointer (all NULL), and for tags the pointer is actually the tag value but this library still calls it a pointer.
* ***pointer*** - The first item in a table entry, with various meanings.  For public and native functions the pointer is to the code, for pubvars the pointer is to the data, libraries don't have a pointer (all NULL), and for tags the pointer is actually the tag value but this library still calls it a pointer.
* ***value*** - The data pointed to by a table entry pointer.  This only has real meaning for public variables, public functions do have information at the pointer address, but it is just the first opcode in the function (usually `PROC`).
* ***prefix*** - A prefix is the first four bytes of an entry's name.  Because this is a single cell pointed directly to by the name pointer in the entry it can be used for extremely fast filtering of functions.  Create a prefix with `_A<>`.
* ***suffix*** - Like a prefix, but far less useful.


