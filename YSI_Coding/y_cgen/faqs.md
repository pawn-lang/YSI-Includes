* `CGen_GetCodeSpace()`

Returns a pointer suitable for use with `AsmInitPtr()`:

```pawn
new ctx[AsmContext];
AsmInitPtr(CGen_GetCodeSpace());
// `@emit` etc go here.
```

* `CGen_UseCodeSpace(ctx)`

Wraps `CGen_GetCodeSpace()` and `AsmInitPtr()` together.  Also sets up proper error handlers so is the preferred initialisation method:

```pawn
new ctx[AsmContext];
CGen_UseCodeSpace(ctx);
// `@emit` etc go here.
```

* `CGen_AddCodeSpace(num)`

*y_cgen* provides a large block of code space to write to, and each time it is written to the next pointer must be updated.  This is done after all the generation for one single piece of code is finished by telling *y_cgen* how much code was written.  Thus the next write can continue on from that point:

```pawn
// `@emit` etc go here.
// Release the handle.
CGen_AddCodeSpace(AsmGetCodeSize(ctx));
```

