# API

## `Circular_Init`

Initialises the circular buffer, so it has a current count.

```pawn
Test:Circular_Init()
{
	new arr[5][5];
	Circular_Init(arr);
}
```

## `Circular_Push`

Adds data to the buffer, possibly rotating out old data.  Returns the slot just written to (the
highest slot that exists).

```pawn
Test:Circular_Push()
{
	new arr[5][5];
	new data[5] = { 5, 6, 7, 8, 9 };
	Circular_Init(arr);
	ASSERT_EQ(Circular_Push(arr, data), 0);
	ASSERT_EQ(arr[0][0], 5);
	ASSERT_EQ(arr[0][1], 6);
	ASSERT_EQ(arr[0][2], 7);
	ASSERT_EQ(arr[0][3], 8);
	ASSERT_EQ(arr[0][4], 9);
	ASSERT_EQ(Circular_Push(arr, data), 1);
	ASSERT_EQ(Circular_Push(arr, data), 2);
	ASSERT_EQ(Circular_Push(arr, data), 3);
	ASSERT_EQ(Circular_Push(arr, data), 4);
	ASSERT_EQ(Circular_Push(arr, data), 4);
	ASSERT_EQ(Circular_Push(arr, data), 4);
}
```

## `Circular_Count`

Gets the number of items in the buffer.

```pawn
Test:Circular_Count()
{
	new arr[5][5];
	new data[5] = { 5, 6, 7, 8, 9 };
	Circular_Init(arr);
	ASSERT_EQ(Circular_Count(arr), 0);
	Circular_Push(arr, data);
	ASSERT_EQ(Circular_Count(arr), 1);
}
```

## `Circular_Capacity`

Gets the total number of slots in the buffer.  Always the same.

```pawn
Test:Circular_Capacity()
{
	new arr[5][5];
	Circular_Init(arr);
	ASSERT_EQ(Circular_Capacity(arr), 5);
	Circular_Push(arr, data);
	ASSERT_EQ(Circular_Capacity(arr), 5);
}
```

## `Circular_Full`

Tests if the buffer is full (so more pushes will loose data).

```pawn
Test:Circular_Full()
{
	new arr[5][5];
	new data[5] = { 5, 6, 7, 8, 9 };
	Circular_Init(arr);
	ASSERT_EQ(Circular_Full(arr), 0);
	Circular_Push(arr, data);
	ASSERT_EQ(Circular_Full(arr), 0);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	Circular_Push(arr, data);
	ASSERT_EQ(Circular_Full(arr), 1);
}
```

## `Circular_Rotate`

This is similar to `Circular_Push` - it moves the items around, but doesn't add new data and doesn't
remove old data.  It just changes the order.  Returns the highest slot that exists.

Test:Circular_RotateContent()
{
	new buffer[5][10];
	Circular_Init(buffer);
	ASSERT_EQ(Circular_Push(buffer, "slot 0"), 0);
	ASSERT_EQ(Circular_Push(buffer, "slot 1"), 1);
	ASSERT_EQ(Circular_Push(buffer, "slot 2"), 2);
	ASSERT_EQ(Circular_Push(buffer, "slot 3"), 3);
	ASSERT_EQ(Circular_Push(buffer, "slot 4"), 4);
	ASSERT_SAME(buffer[0], "slot 0");
	ASSERT_SAME(buffer[1], "slot 1");
	ASSERT_SAME(buffer[2], "slot 2");
	ASSERT_SAME(buffer[3], "slot 3");
	ASSERT_SAME(buffer[4], "slot 4");
	ASSERT_EQ(Circular_Rotate(buffer), 4);
	ASSERT_SAME(buffer[0], "slot 1");
	ASSERT_SAME(buffer[1], "slot 2");
	ASSERT_SAME(buffer[2], "slot 3");
	ASSERT_SAME(buffer[3], "slot 4");
	ASSERT_SAME(buffer[4], "slot 0");
	ASSERT_EQ(Circular_Rotate(buffer), 4);
	ASSERT_SAME(buffer[0], "slot 2");
	ASSERT_SAME(buffer[1], "slot 3");
	ASSERT_SAME(buffer[2], "slot 4");
	ASSERT_SAME(buffer[3], "slot 0");
	ASSERT_SAME(buffer[4], "slot 1");
	ASSERT_EQ(Circular_Rotate(buffer), 4);
	ASSERT_SAME(buffer[0], "slot 3");
	ASSERT_SAME(buffer[1], "slot 4");
	ASSERT_SAME(buffer[2], "slot 0");
	ASSERT_SAME(buffer[3], "slot 1");
	ASSERT_SAME(buffer[4], "slot 2");
	ASSERT_EQ(Circular_Rotate(buffer), 4);
	ASSERT_SAME(buffer[0], "slot 4");
	ASSERT_SAME(buffer[1], "slot 0");
	ASSERT_SAME(buffer[2], "slot 1");
	ASSERT_SAME(buffer[3], "slot 2");
	ASSERT_SAME(buffer[4], "slot 3");
	ASSERT_EQ(Circular_Rotate(buffer), 4);
	ASSERT_SAME(buffer[0], "slot 0");
	ASSERT_SAME(buffer[1], "slot 1");
	ASSERT_SAME(buffer[2], "slot 2");
	ASSERT_SAME(buffer[3], "slot 3");
	ASSERT_SAME(buffer[4], "slot 4");
}

