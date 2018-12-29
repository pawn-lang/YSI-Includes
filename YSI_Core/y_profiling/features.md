# Profiling

Profiling is hard to get right.  VERY hard to get right.  It seems like "how long does this code take to run" shouldn't be a difficult question to answer, but it is, for several reasons:

1. Modern computers are very complex and do many things at once.  Simply subracting a start time from an end time only tells you how long your code took, plus anything else running simultaneously.
2. Modern computers are also very fast.  They literally do milliards of things a second.  Timing something that takes only a few thousand instructions is such a small time as to be almost unnoticable - the time can get lost in noise.
3. Are you actually timing the right thing?  This is a big question:
	* Is the data representitive?  If the real code will handle 10000 items, profiling on 100 may give the wrong answer.  If you are comparing two algorithms one could be O(N), while the other is O(log N + 200).  At 100 data the first algorithm will take 100 units of time, while the second will take 202 units - thus the first is faster for small data sets.  However, at 10000 data the first algorithm increases to 10000 units, while the second increases to only 204.
	* Do you cover all cases?  There's no point proving that one algorithm is faster in one case if real-world usage is another.  Quicksort is known to be much better at sorting data than bubblesort, but if you pass an already sorted array, bubblesort is faster.  Or when searching for a value, do you only test how long it takes to find the first value; or the first, the last, and several in between?  What about a value that doesn't even exist?  Is the failure case accounted for?
4. Ensure the code is idempotent.  If one run does all the work (e.g. sorting) and subsequent runs use that prepared data (i.e. a sorted array) then the code isn't actually doing anything you are trying to profile.
5. Repeat runs many times to improve the accuacy.  Jitter between runs mean that one may take 7ms, while the next takes 6ms, and another takes 8ms.  However, all three together averaged give 7ms, which gives a greater confidence in the results.

# Features

## Iteration Counts

To get a more accurate timing, the code in the profiling function is run multiple times (thousands), and the results summed and averaged.  The exact number of repeats (default 1,000,000) can be customised at a per-profile level:

```pawn
Profile:CodeToProfile[100]()
{
	// CODE GOES HERE
}
```

Less iterations means less accuracy, but may also mean that the code completes in a reasonable time if it is quite slow.

The number of runs (default 10) can be customised globally:

```pawn
#define TIMING_ITERATIONS (20)
#include <YSI_Core\y_profiling>
```

