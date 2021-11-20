// These functions are all so close in performance that I have to believe that
// the whole thing is IO bound.  I mean, one set of timing results looked like
// this:
//
//     Timing "CopyAsync"...
//               Mean = 78.50ms
//               Mode = 63.70ms
//             Median = 76.80ms
//              Range = 32.00ms
//
//     Timing "CopyHuge"...
//               Mean = 78.69ms
//               Mode = 72.09ms
//             Median = 79.09ms
//              Range = 15.19ms
//
//     Timing "CopyPawn"...
//               Mean = 78.59ms
//               Mode = 70.09ms
//             Median = 76.00ms
//              Range = 20.60ms
//
//     Timing "CopySync"...
//               Mean = 79.50ms
//               Mode = 64.09ms
//             Median = 79.00ms
//              Range = 30.50ms
//
// I've had less consistent results re-running the same test twice!  OK, it
// seems that choice of file really matters.  Calling the batch versions has a
// lot of overhead, but is very fast.  Pawn versions are the opposite.  I tried
// the test on a much larger file (old: 1,316,455 bytes, new: 22,018,319 bytes),
// and the results were VASTLY different:
//
//     Timing "CopyAsync"...
//               Mean = 85.69ms
//               Mode = 66.09ms
//             Median = 85.90ms
//              Range = 32.09ms
//
//     Timing "CopyHuge"...
//               Mean = 1808.59ms
//               Mode = 1732.80ms
//             Median = 1831.50ms
//              Range = 181.30ms
//
//     Timing "CopyPawn"...
//               Mean = 1712.19ms
//               Mode = 1562.09ms
//             Median = 1705.50ms
//              Range = 305.10ms
//
//     Timing "CopySync"...
//               Mean = 87.69ms
//               Mode = 71.40ms
//             Median = 87.59ms
//              Range = 29.29ms
//
// Testing on a tiny file (451 bytes):
//
//     Timing "CopyAsync"...
//               Mean = 90.30ms
//               Mode = 75.69ms
//             Median = 91.69ms
//              Range = 24.70ms
//
//     Timing "CopyHuge"...
//               Mean = 2.50ms
//               Mode = 2.40ms
//             Median = 2.40ms
//              Range = 2.59ms
//
//     Timing "CopyPawn"...
//               Mean = 2.29ms
//               Mode = 2.20ms
//             Median = 2.20ms
//              Range = 1.10ms
//
//     Timing "CopySync"...
//               Mean = 86.40ms
//               Mode = 66.80ms
//             Median = 88.69ms
//              Range = 36.00ms
//
// Testing a the medium file on battery (first results were on mains):
//
//     Timing "CopyAsync"...
//               Mean = 92.09ms
//               Mode = 79.90ms
//             Median = 93.19ms
//              Range = 22.20ms
//
//     Timing "CopyHuge"...
//               Mean = 104.40ms
//               Mode = 94.50ms
//             Median = 105.09ms
//              Range = 18.60ms
//
//     Timing "CopyPawn"...
//               Mean = 107.90ms
//               Mode = 87.50ms
//             Median = 107.50ms
//              Range = 38.29ms
//
//     Timing "CopySync"...
//               Mean = 103.90ms
//               Mode = 87.09ms
//             Median = 100.59ms
//              Range = 62.90ms
//

PROFILE__ CopyPawn[10]()
{
	FileCopy("i" TEST_EXT, "o" TEST_EXT);
	fremove("o" TEST_EXT);
}

PROFILE__ CopyHuge[10]()
{
	HugeCopy("i" TEST_EXT, "o" TEST_EXT);
	fremove("o" TEST_EXT);
}

PROFILE__ CopySync[10]()
{
	Files_CopySync("i" TEST_EXT, "o" TEST_EXT);
	fremove("o" TEST_EXT);
}

// "Z" to make it run last and not mess up the other profilings with its
// asyncronousness.
PROFILE__ CopyZAsync[10]()
{
	Files_CopyAsync("i" TEST_EXT, "o" TEST_EXT);
	fremove("o" TEST_EXT);
}

