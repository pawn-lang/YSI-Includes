## What does this do?

This library provides basic wrappers to store a little bit of spread out data; for example when
you need to store how many arrests a player has made, but only a few players are police.  In this
case using a `MAX_PLAYERS` array to store the data can be very inefficient, because only a tiny
fraction of the memory will ever be used, but it is all allocated.

## How does it save memory?

Instead of allocating arrays at compile-time, this uses server functions to store the data
elsewhere, which means that only the indexes ever accessed are allocated memory.  The data is
stored in GVars, SVars, or properties, depending on script type and plugins.  It is basically just a
wrapper around those natives to provide indexed array access.

There is a caveat to this though: storing data in this way may APPEAR to use less memory in some
cases, but it can use more when the sparse array isn't very sparse (i.e. there is a lot of data
stored).  The AMX might be smaller, but you still need the data to be somewhere, and there are
additional overheads required, i.e. the slot names.

