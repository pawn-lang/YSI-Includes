# Abstract

We present a new novel array-based data structure for storing bounded sets of integers with O(1)
complexity for almost
all operations (addition, removal, membership, and forward and reverse iteration) and just
one integer of overhead in storage beyond the values themselves.  This structure entirely relies on
the fact that it stores numbers, and so any generic implementations store the data along side the
array of numbers, with them essentially acting as IDs.  The basic observation to enable all this is
that each array index stores the next valid value, making iteration a simple matter of reading the
current index; but the novel extension to this is a clever encoding of invalid values to allow both
membership tests and iterating backwards.

# Introduction

Given a sorted set of integers, for example `5, 8, 15, 16, 23, 42`, we want a way to:

* Test if any given number is in the set.
* Given a number in the set, find the next or previous number.
* Add and remove numbers.

A dense array of just these values can test with a binary search, which is `O(log n)`; looping
through the values is trivial; but addition and removal requires shuffling, making it `O(n / 2)`.

A boolean array (`true` for membership, `false` otherwise) has `O(1)` tests (simply check the index)
and `O(1)` addtion/removal, but `O(n)` iteration in both directions.

We extend the boolean array by exchanging `true` for the next valid value (which must always be
higher than the current index) and `false` for lower values.  Membership tests thus become the `O(1)`
operation `a[i] > i` and iteration to find the next value is the lookup `a[i]`.  To enable reverse
iteration we set the value of the previous index to `prev + 1`.  If the previous value was already
valid it already had this value (since it was pointing to the very next slot).  If it is invalid,
the membership check still works as the value is `a[i] <= i` and we can iterate backwards using
`i = a[i - 1] - 1` (plus some bounds checks).  The initial value must be stored additionally, but
this is a mere single integer of overhead.

The intial example would thus look like, using `-`
for "don't care, as long as the value is less than the index" and `X` for some sentinel value:

```
start: 5

indices:  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22
values:   -,  -,  -,  -,  X,  8,  -,  6, 15,  -,  -,  -,  -,  -,  9, 16, 23,  -,  -,  -,  -,  -, 17

indices: 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45
values:  42,  -,  -,  -,  -,  -,  -,  -,  -,  -,  -,  -,  -,  -,  -,  -,  -,  -, 24,  X,  -,  -, 43
```

The most interesting index here is `15`, whose value is `16`.  This is both the next valid value
(`16`) and the previous valid value `+ 1` for the next slot.

Once you have efficient forward and reverse iteration, `O(1)` removal can be implemented.  Addition
is still `O(n / 2)` as you must loop through all the values first to find the previous valid value.
This can be done in `O(1)` operations with an extension - setting all invalid values to `prev + 1`,
but the extension itself makes addition and removal both more complex as more indexes need updating
together.  The extended array would look like:

```
start: 5

indices:  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22
values:   X,  X,  X,  X,  X,  8,  6,  6, 15,  9,  9,  9,  9,  9,  9, 16, 23, 17, 17, 17, 17, 17, 17

indices: 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45
values:  42, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  X, 43, 43, 43
```

This also enables querying the next/previous valid value to an invalid value in `O(1)` operations
(for next, get the previous first and advance).

