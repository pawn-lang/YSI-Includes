# Quick Start

This is an internal library.  Don't use it.

```pawn
// Include YSI core.
#include <YSI_Core\y_utils>

// Include y_cgen.
#include <YSI_Coding\y_cgen\y_cgen>

// Include amx_assembly.
#include <amx\asm>

// Callback called during script init or JIT init.
public OnCodeInit()
{
	// Declare a new code generation context.  Must name it `ctx` for `@emit`.
	new ctx[AsmContext];
	
	// Point the context at spare `COD` segment memory.
	CGen_UseCodeSpace(ctx);
	
	// Generate your code.
	@emit PROC
	@emit RETN
	
	// Release the handle.
	CGen_AddCodeSpace(AsmGetCodeSize(ctx));
}
```

