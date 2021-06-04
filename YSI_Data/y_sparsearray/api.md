## `Sparse_Set(SparseArray:array<>, index, value)`

Set the value at this slot in the array.

```pawn
Sparse_Set(array, 1, 100);
```

## `Sparse_Get(SparseArray:array<>, index, default = cellmin)`

Get the value at this slot in the array, or `default` if it isn't found.

```pawn
new value = Sparse_Get(array, 0);
printf("%d, %d", value != cellmin, value);
```

```pawn
new value = Sparse_Get(array, 4, -1);
printf("%d, %d", value != -1, value);
```

## `Sparse_UnSet(SparseArray:array<>, index)`

Delete this slot in the array.

```pawn
Sparse_UnSet(array, 2);
```

## `bool:Sparse_TryGet(SparseArray:array<>, index, &dest)`

Try get the value at this slot in the array, or return `false` if it doesn't exist.

```pawn
new value;
if (Sparse_TryGet(array, 3, value))
{
	printf("%d", value);
}
```

## `bool:Sparse_Contains(SparseArray:array<>, index)`

Check if this slot exists in the array.

```pawn
if (Sparse_Contains(array, 5))
{
	printf("yes");
}
```

## `bool:Sparse_Exchange(SparseArray:array<>, index, &oldValue)`
## `bool:Sparse_Exchange(SparseArray:array<>, index, &oldValue, newValue)`

Get the `value` at `index`, and return `true` if the slot existed.  If a new value is given this is
written to the slot instead, if no new value is given, the slot is deleted.

```pawn
new value;
if (Sparse_Exchange(array, 6, value, 99))
{
	printf("%d", value);
}
ASSERT(Sparse_Get(array, 6) == 99);
```

```pawn
new value;
if (Sparse_Exchange(array, 6, value))
{
	printf("%d", value);
}
ASSERT(!Sparse_Contains(array, 6));
```

