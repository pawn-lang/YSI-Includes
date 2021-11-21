# Quick Start

```pawn
#include <YSI_Server\y_files>

main()
{
	// Create a directory (Windows only).
	Files_CreateDirSync("subdir");
	// Move a file to it.
	Files_MoveSync("example.input", "subdir/example.output");
	// Copy it back out again.
	Files_CopySync("subdir/example.output", "example.output");
	// Clean up (remove the directory on Windows).
	Files_RemoveDirSync("subdir");
}
```

