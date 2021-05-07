# Does This Copy?

No.  The circular buffer avoids large data copies by directly manipulating the array header.  This
is far more efficient than calling `memcpy` lots of times.

