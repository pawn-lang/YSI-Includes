#Features

## Slot Written To

`Circular_Push` will return the slot it just wrote to, so you can use/manipulate it more:

```pawn
new slot = Circular_Push(buffer, data);
buffer[slot][3] = 7;
```

## Large Data/Enums

```pawn
static gBuffer[10][MY_HUGE_ENUM];

main()
{
	Circular_Init(gBuffer);
}
```

Now calling `Circular_Push` is efficient, even when the buffer is full.

## Copy-Free

The library manipulates the array header to move data.  So instead of copying the contents around
every time you push new data, instead it just changes a couple of pointers.  This makes it far more
efficient.

## `Circular_Rotate`.

This is similar to `Circular_Push`, but doesn't actually take any data.  You can use this when the
data you're writing is more complex and just need to know the slot.  For example when you're using
an enum you can do:

```pawn
new slot = Circular_Rotate(buffer);
buffer[slot][E_THING_1] = 5;
buffer[slot][E_THING_2] = 7.7;
// ...
```

