# Keywords

## `Profile:`

Declare a profiler function.

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

## Alternate Keywords

See [YSI_COMPATIBILITY_MODE](../../YSI_COMPATIBILITY_MODE.md) for details.

* `YSI_KEYWORD_Profile`: `Profile:Func()`
* `YSI_NO_KEYWORD_Profile`: `PROFILE__ Func()`
* `YSI_KEYWORD_ProfileInit`: `ProfileInit:Func()`
* `YSI_NO_KEYWORD_ProfileInit`: `PROFILE_INIT__ Func()`
* `YSI_KEYWORD_ProfileClose`: `ProfileClose:Func()`
* `YSI_NO_KEYWORD_ProfileClose`: `PROFILE_CLOSE__ Func()`

# Compile-Time Options

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

## `LIGHT_PROFILE_REPORT`

This define tells the system to print slightly less output to the console.

## `TIMING_ITERATIONS`

The global number of runs (default 10).

