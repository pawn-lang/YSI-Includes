# Internal Details

Most of the functions are macros that wrap an internal function so it can take the buffer and its
sizes.  This is similar to how *y_iterate* works, but is less refined - there's not as much type
checking involved unfortunately.

`Circular_Init` swaps the final array header to a psudo-count.  `size + count` is the next slot to
be written to (in bytes), thus the count is actually negative.  Once the data has been written to
the final slot this is replaced with a normal array pointer and the cycling code is used instead.
The cycles work by rotating the pointers in the array header, NOT by copying all the data.  This is
way more efficient than copying huge arrays, but slightly less efficient than keeping both a read
and write pointer.  However, a read pointer would mean that the oldest data is not always in slot
`0`.

