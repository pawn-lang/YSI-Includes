# Profiling

Profiling is hard to get right.  VERY hard to get right.  It seems like "how long does this code take to run" shouldn't be a difficult question to answer, but it is, for several reasons:

0. Is it even worth profiling?  All of this should come AFTER determining which parts of your code actually need improving (this is done with profiling as well, but from something like the profiler plugin which does overview profiling, not this system which does micro benchmarking).  A slow function rarely called needs less work than a fast one constantly called.
1. Modern computers are very complex and do many things at once.  Simply subracting a start time from an end time only tells you how long your code took, plus anything else running simultaneously.
2. Modern computers are also very fast.  They literally do milliards of things a second.  Timing something that takes only a few thousand instructions is such a small time as to be almost unnoticable - the time can get lost in noise.
3. Are you actually timing the right thing?  This is a big question:
	* Is the data representitive?  If the real code will handle 10000 items, profiling on 100 may give the wrong answer.  If you are comparing two algorithms one could be O(N), while the other is O(log N + 200).  At 100 data the first algorithm will take 100 units of time, while the second will take 202 units - thus the first is faster for small data sets.  However, at 10000 data the first algorithm increases to 10000 units, while the second increases to only 204.
	* Do you cover all cases?  There's no point proving that one algorithm is faster in one case if real-world usage is another.  Quicksort is known to be much better at sorting data than bubblesort, but if you pass an already sorted array, bubblesort is faster.  Or when searching for a value, do you only test how long it takes to find the first value; or the first, the last, and several in between?  What about a value that doesn't even exist?  Is the failure case accounted for?
4. Ensure the code is idempotent.  If one run does all the work (e.g. sorting) and subsequent runs use that prepared data (i.e. a sorted array) then the code isn't actually doing anything you are trying to profile.
5. Repeat runs many times to improve the accuacy.  Jitter between runs mean that one may take 7ms, while the next takes 6ms, and another takes 8ms.  However, all three together averaged give 7ms, which gives a greater confidence in the results.
6. Are the results even relevant?  You can prove that one piece of code is 2% faster than another, but if that other code does twice as much that's an overall win.  Getting twice the functionality for only a 2% drop in performance is a GREAT result, and should probably be regarded as the better system despite the minor time loss.  I've very often seen people use system "A" instead of system "B" because it is faster, then add system "C" to do some extra bits.  However, system "B" already did what "C" adds, and "B" alone is faster than "A+C" together.  But people just see "A" is faster than "B" and assume that means it is better.

So many people post benchmarking results to "prove" one thing or another, when all they prove is that in one specific corner-case one system was marginally faster than another one once.  That's not a reliable result.  Any benchmarking results presented without at least a paragraph on methodology, limitations, and settings, can be safely ignored.

# Features

## 'ProfileInit:`

An optional initialisation function called before a profiling:

```pawn
ProfileInit:CodeToProfile()
{
	// CALLED JUST ONCE BEFORE THE PROFILING
}

Profile:CodeToProfile()
{
	// CODE GOES HERE
}
```

This can be used to set things up for the profiling, such as loading data.  HOWEVER, there is a HUGE warning - this function is only called ONCE, before ALL the profiling iterations are run.  It cannot be used to reset state between profiling repeats.  In fact, nothing can, so ensure the code being profiled is idempotent.  Even something like sorting an array can be problematic - if you sort the same array 1,000,000 times in-place, only the first run will actaully do anything; all subsequent runs may simply see an already sorted array and end early.  This can totally destroy results - bubbleosrt is an AWFUL sorting method in the general case (i.e. when data is not sorted), but it will end early for sorted data.  Quicksort is a MUCH better sorting method in the general case, but will try fully sort an already sorted array.  In this example 999,999 iterations will see a pre-sorted array and bubblesort will seem faster, even though it isn't.

## 'ProfileClose:`

An optional teardown function called after a profiling:

```pawn
Profile:CodeToProfile()
{
	// CODE GOES HERE
}

ProfileClose:CodeToProfile()
{
	// CALLED JUST ONCE AFTER THE PROFILING
}
```

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

## `INCLUDE_PROFILINGS`

By default profiling functions are not compiled, thus are not in the output AMX.  This is important, as they shouldn't be in live code.  However, to run them they obviously need including.  This macro compiles profiling functions, and provides several functions for running them:

```pawn
#define INCLUDE_PROFILINGS

#include <a_samp>
#include <YSI_Core\y_profiling>

Profile:CodeToProfile()
{
	// CODE GOES HERE
}

main()
{
	// Run all the profiles, with standard outputs.
	Profiling_RunAll();
	
	// OR:
	
	// Run all the profiles, but with less output, and report the number found.
	new profilings.
	Profiling_Run(profilings);
}
```

## `RUN_PROFILINGS`

99% of the time, you just want all the profilings to be run.  This macro is the same as `INCLUDE_PROFILINGS`, but automatically runs all the functions in `OnScriptInit`:

```pawn
#define RUN_PROFILINGS

#include <a_samp>
#include <YSI_Core\y_profiling>

Profile:CodeToProfile()
{
	// CODE GOES HERE
}

main() {}
```


## `YSI_PROFILINGS`

The same as `RUN_PROFILINGS`, but also compiles all YSI internal profiling functions.

## `PROFILINGS_FILE`

This macro allows you to write the timing results out to a file, as well as have them displayed in the console.  This file is in CSV format, with the first line as column headers.

Use:

```pawn
#define RUN_PROFILINGS
#define PROFILINGS_FILE(%0) %0".profile.csv"

#include <a_samp>
#include <YSI_Core\y_profiling>

Profile:CodeToProfile()
{
	// CODE GOES HERE
}

main() {}
```

Example Output (`CodeToProfile.profile.csv`):

```
timestamp,runs,repeats,results (ms)
1546082820,10,1000000,122,121,121,120,121,121,121,119,119,121
1546082822,10,1000000,123,124,123,123,121,121,121,120,122,122
```

* The timestamp is the unix timestamp at which the line was WRITTEN, not the time at which the profilings started or ended.
* "runs" is the number of times the whole profile was repeated.
* "repeats" is the number of times the code was run for each run.
* "results" are the total times for each run, in milliseconds.

The repeats help to time very short pieces of code.  The runs help to average.  The console reports average results (mean, mode, median, range).  Thus the even more accurate result for a single iteration would be: `sum(results) / (runs * repeats)`.

## Alternate Keywords

See [YSI_COMPATIBILITY_MODE](../../YSI_COMPATIBILITY_MODE.md) for details.

* `YSI_KEYWORD_Profile`: `Profile:Func()`
* `YSI_NO_KEYWORD_Profile`: `PROFILE__ Func()`
* `YSI_KEYWORD_ProfileInit`: `ProfileInit:Func()`
* `YSI_NO_KEYWORD_ProfileInit`: `PROFILE_INIT__ Func()`
* `YSI_KEYWORD_ProfileClose`: `ProfileClose:Func()`
* `YSI_NO_KEYWORD_ProfileClose`: `PROFILE_CLOSE__ Func()`

## `LIGHT_PROFILE_REPORT`

This define tells the system to print slightly less output to the console.

