# `YSI_NO_HEAP_MALLOC`

In almost all cases of issues, the solution is to define `YSI_NO_HEAP_MALLOC`.  So why is this not the default?  Simply because many people complained about the alternative.  With `YSI_NO_HEAP_MALLOC` your AMX is much larger because the allocation pool is embedded in the file.  But if you are having problems that's just the price you need to pay.

# Issues

## I keep running out of memory.

First, ensure you are `free`ing the memory when you are finished with it.  Failure to do this will result in a "memory leak".  If you are sure you are doing that, you might need a bigger pool of memory for y_malloc to use.  This is done with `MALLOC_MEMORY`:

```pawn
#define MALLOC_MEMORY (32768)
#include <YSI_Coding\y_malloc>
```

## My mode just stops working after several restarts.

This is a known issue with the heap allocation version of y_malloc.  To fix it, use the non-heap version by doing:

```pawn
#define YSI_NO_HEAP_MALLOC
#include <YSI_Coding\y_malloc>
```

This will make your mode larger (because the allocation pool is now included in the mode), but more stable.

# Errors

## `error 017: undefined symbol "_is_now_DYNAMIC_MEMORY_"`

This will occur on:

```pawn
#pragma dynamic 65536
```

The error tries to explain the problem.  y_malloc can allocate memory from the heap or from global memory.  If you are not using `YSI_NO_HEAP_MALLOC` it will use the heap (obviously), aka. dynamic memory.  Because of this, it needs to control how much dynamic memory there is.  Thus, instead of using `#pragma dynamic`, use `DYNAMIC_MEMORY`:


```pawn
#define DYNAMIC_MEMORY (65536)
#include <YSI_Coding\y_malloc>
```

## `warning 203: symbol is never used: "dynamic_is_now_DYNAMIC_MEMORY_"`

This happens when you have a variable or function called `dynamic` that isn't used.  Because of the way y_malloc overrides `#pragma dynamic`, ALL instances of `dynamic` are replaced.  So this:

```pawn
MyFunc(dynamic)
{
}
```

Becomes:

```pawn
MyFunc(dynamic_is_now_DYNAMIC_MEMORY_)
{
}
```

In most cases this ins't actually a problem - the variable declaration will be replaced, but so will all the uses, so they will still refer to the correct variable.  Note that this only happens without `YSI_NO_HEAP_MALLOC`.

## `error 017: undefined symbol "dynamic_is_now_DYNAMIC_MEMORY_"`

This is similar to the last warning, but when not all instances of `dynamic` have been replaced.  This only happens when some come before including y_malloc and some come after:

```pawn
dynamic() // Not replaced.
{
	printf("hi");
}

#include <YSI_Coding\y_malloc>

main()
{
	dynamic(); // Replaced.
}
```

To fix, use `YSI_NO_HEAP_MALLOC` or move the offending function:

```pawn
#include <YSI_Coding\y_malloc>

dynamic() // Not replaced.
{
	printf("hi");
}

main()
{
	dynamic(); // Replaced.
}
```

## `*** YSI Error: y_malloc with JIT requires "#define YSI_NO_HEAP_MALLOC"`

Full message:

```
*** YSI Error: y_malloc with JIT requires "#define YSI_NO_HEAP_MALLOC"
*** YSI Warning: JIT disabled
[jit] Compilation was disabled
```

The heap allocation method relies on a small bug in the PAWN VM (virtual machine).  This bug doesn't exist in the JIT VM, so that method can't be used with the JIT plugin.  If you compile y_malloc for heap allocation and try use the JIT it can't work, and will fall back on the original VM.  To use JIT, compile with `YSI_NO_HEAP_MALLOC`:

```pawn
#define YSI_NO_HEAP_MALLOC
#include <YSI_Coding\y_malloc>
```

