# Quick Start

A circular buffer is an array you can keep adding data to the end of, and once it reaches its
capacity the earliest data added will be removed.  For example:

```pawn
new buffer[4][1];
Circular_Init(buffer);
// Count: 0, Contents: - - - -
Circular_Push(buffer, 1);
// Count: 1, Contents: 1 - - -
Circular_Push(buffer, 2);
// Count: 2, Contents: 1 2 - -
Circular_Push(buffer, 3);
// Count: 3, Contents: 1 2 3 -
Circular_Push(buffer, 4);
// Count: 4, Contents: 1 2 3 4
Circular_Push(buffer, 5);
// Count: 4, Contents: 2 3 4 5
Circular_Push(buffer, 6);
// Count: 4, Contents: 3 4 5 6
Circular_Push(buffer, 7);
// Count: 4, Contents: 4 5 6 7
```

Because the buffer is defined as `[4]` it can only hold `4` items.  Once a fifth item is added the
first item is lost and all the other data shifts up one space.  And, because a circular buffer is
just a normal array, all normal array functions and accesses work normally.

This library is very simple.  There are two main functions and several auxiliary functions.  The
main functions are `Circular_Init` to initialise a circular buffer, and `Circular_Push` to add data
(both seen above).  The auxiliary functions are `Circular_Full`, to check if a circular buffer has
reached its capacity yet; `Circular_Count`, which does almost the same thing but returns a number
not a boolean; `Circular_Capacity`, which returns the maximum size; and `Circular_Rotate`, which
updates the pointers without copying data.

* `Circular_Full` is basically:

```pawn
bool:Circular_Full(buffer)
{
	return Circular_Count(buffer) == Circular_Capacity(buffer);
}
```

* `Circular_Capacity` is basically (exactly) `sizeof (buffer)`.

* `Circular_Count` is the only slightly interesting one, but once the buffer is full always returns
the same value (`Count:` in the example above).

* `Circular_Rotate` is like `Circular_Push` in that it rotates data and returns a new slot, but
doesn't clobber any old data.  You can use this to return a new slot, or cycle existing data.

