# Quick Start

y_malloc provides `malloc`, which creates a variably sized array at run-time:

```pawn
new Alloc:arr = malloc(128); // Create an array with 128 slots*.

mset(arr, 5, 42); // Equivalent to `arr[5] = 42`.

printf("%d", mget(arr, 5)); // Equivalent to `printf("%d", arr[5]);`.

free(arr); // Get rid of the memory again.
```

`free` is important - once you are finished with a dynamic array you should release it again.  Otherwise you will eventually run out of memory and `malloc` will fail.  If malloc DOES fail, it returns `NO_ALLOC` (or just `0`):

```pawn
new Alloc:arr = malloc(16); // Create an array with 16 slots.

if (arr == NO_ALLOC) // Or just `if (!arr)`
{
	P:E("`malloc` failed.  Remember to free memory when you are finished with it.");
}
```

`malloc` will NOT initialise the memory, to set all the values to 0 use `calloc` instead.

\* Because of implementation details, the true size may be different, but it will be AT LEAST 128 cells.

