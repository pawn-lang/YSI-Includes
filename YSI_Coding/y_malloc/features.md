# Features

## Store Strings

### Write

```pawn
new Alloc:arr = malloc(16);

new idx = 0;

new str[] = "Hello World";

msets(arr, idx, str);
```

### Write Packed

```pawn
new Alloc:arr = malloc(16);

new idx = 5;

new str[] = "Hello World";

msets(arr, idx, str, true);
```

### Read

```pawn
new idx = 0;
 // copy the contents back to buffer.
new str[12];

mgets(str, sizeof (str), arr, idx);
```

### Read Packed

```pawn
new idx = 5;
 // copy the contents back to buffer.
new str[12];

mgets(str, sizeof (str), arr, idx, true);
```

## Store Arrays

### Write

```pawn
new Alloc:arr = malloc(64);

new idx = 32;

new src[32] = { 5, 10, ... };

mseta(arr, idx, src, sizeof (src));
```

### Read

```pawn
new idx = 32;

new dst[32];

mgeta(dst, sizeof (dst), arr, idx);
```

## Manipulate The Memory

### Initially Clear

I.E.  Initialise all the slots of the allocated memory to `0`.

```pawn
new Alloc:arr = calloc(16);
```

### Resize An Array

```pawn
new Alloc:arr = malloc(16);
arr = realloc(arr, 32);
```

If the reallocation fails, the old pointer remains valid:

```pawn
new Alloc:arr = malloc(16);
new Alloc:rea = realloc(arr, 32);
if (!rea)
{
	Debug_Error("Reallocation failed");
	free(arr);
}
```

### Allocate A String

This allocates enough memory to store a single string, then writes that string.

```pawn
new Alloc:arr = Malloc_NewS("Hello World"); // .pack = false
```

