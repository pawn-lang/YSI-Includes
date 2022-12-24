# Profiling

Profiling is hard to get right.  VERY hard to get right.  It seems like "how long does this code take to run" shouldn't be a difficult question to answer, but it is, for several reasons:

0. Is it even worth profiling?  All of this should come AFTER determining which parts of your code actually need improving (this is done with profiling as well, but from something like the profiler plugin which does overview profiling, not this system which does micro benchmarking).  A slow function rarely called needs less work than a fast one constantly called.
1. Modern computers are very complex and do many things at once.  Simply subracting a start time from an end time only tells you how long your code took, plus anything else running simultaneously.
2. Modern computers are also very fast.  They literally do milliards of things a second.  Timing something that takes only a few thousand instructions is such a small time as to be almost unnoticable - the time can get lost in noise.
3. Are you actually timing the right thing?  This is a big question:
	* Is the data representitive?  If the real code will handle 10000 items, profiling on 100 may give the wrong answer.  If you are comparing two algorithms one could be O(N), while the other is O(log N + 200).  At 100 data the first algorithm will take 100 units of time, while the second will take 202 units - thus the first is faster for small data sets.  However, at 10000 data the first algorithm increases to 10000 units, while the second increases to only 204.
	* Do you cover all cases?  There's no point proving that one algorithm is faster in one case if real-world usage is another.  Quicksort is known to be much better at sorting data than bubblesort, but if you pass an already sorted array, bubblesort is faster.  Or when searching for a value, do you only test how long it takes to find the first value; or the first, the last, and several in between?  What about a value that doesn't even exist?  Is the failure case accounted for?
	* Are you comparing like-for-like features?  If you are comparing two pieces of code that must do the same thing, one has everything in-built and the other doesn't, then the second piece of code might be faster.  It is faster because it does less of the required work, but in real-world code you end up with additional code after the profiled part.  This is the command processor problem.  If one command processor checks permissions internally and another one doesn't, the one that doesn't check permissions might be faster to actually call the command.  But if the first thing that must then be done in the command is checking permissions, you lose the speed gain and more.
4. Ensure the code is idempotent.  If one run does all the work (e.g. sorting) and subsequent runs use that prepared data (i.e. a sorted array) then the code isn't actually doing anything you are trying to profile.
5. Repeat runs many times to improve the accuacy.  Jitter between runs mean that one may take 7ms, while the next takes 6ms, and another takes 8ms.  However, all three together averaged give 7ms, which gives a greater confidence in the results.
6. Are the results even relevant?  You can prove that one piece of code is 2% faster than another, but if that other code does twice as much that's an overall win.  Getting twice the functionality for only a 2% drop in performance is a GREAT result, and should probably be regarded as the better system despite the minor time loss.  I've very often seen people use system "A" instead of system "B" because it is faster, then add system "C" to do some extra bits.  However, system "B" already did what "C" adds, and "B" alone is faster than "A+C" together.  But people just see "A" is faster than "B" and assume that means it is better.

So many people post benchmarking results to "prove" one thing or another, when all they prove is that in one specific corner-case one system was marginally faster than another one once.  That's not a reliable result.  Any benchmarking results presented without at least a paragraph on methodology, limitations, and settings, can be safely ignored.

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

