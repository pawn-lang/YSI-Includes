# Why are the functions `Sync`?

There are also `Async` versions of the functions.  These only work on Windows and might return before the operation has finished.  However; as my tests showed no significant performance improvements over the `Sync` versions, given the difficulties involved in working with async code, and the fact that they don't work on Linux; they were deprecated by the release of the first version.

