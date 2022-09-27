# Quick Start

This library provides a block of memory within *COD* that you can write new instructions to as code in *DAT* won't execute.  This is used when you're generating all new code (as in *y_hooks*) rather than replacing existing code (as in *y_inline*).

```pawn
#include <YSI_Coding\y_cgen>

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

