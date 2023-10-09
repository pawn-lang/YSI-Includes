# Quick Start

This include allows you to quickly and easily define timer functions, that is functions which are to be called after a given time. The library provides two systems: tasks, which are functions that run all the time in the background (for example streamers); and timers, which are functions you can start, stop, and call on a delay at will.


## Example

### Without y_timers
```pawn
#include <a_samp>

forward RepeatingTimer();
forward DelayedTimer(playerid);

public RepeatingTimer()
{
	printf("Called every N seconds.");
}

public DelayedTimer(playerid)
{
	printf("May be called after N seconds");
}

main()
{
	SetTimer("RepeatingTimer", 1000, 1);
	SetTimerEx("DelayedTimer", 500, 0, "i", 42);
}
```
### With y_timers
```pawn
#include <YSI\y_timers>

task RepeatingTimer[1000]()
{
	printf("Called every 1 seconds.");
}

timer DelayedTimer[500](playerid)
{
	printf("May be called after 0.5 seconds");
}

main()
{
	defer DelayedTimer(42);
}
```
### Comparison
I don't know about you, but I think the second version looks much better. There are many advantages to this method:

Calling conventions are defined at the function itself - when you write a function you can define how it is called.
Times are defined with functions, so you don't have half of a function's information in one place, and more elsewhere.
Tasks with the same delays are automatically balanced to not occur at the same time. For example if you have three with a one second period, they will be called a third of a second apart.
Changing a function to a timer function no longer requires you to modify all the calls to it.
The compiler can check function parameters and function names are correct.

## Tasks

Tasks are functions that are called constantly at a given period. Defining these is now VERY simple:
```pawn
#include <YSI\y_timers>

task RepeatingFunction1[1000]()
{
	printf("Called every second, but not at the same time as RepeatingFunction2.");
}

task RepeatingFunction2[1000]()
{
	printf("Called every second, but not at the same time as RepeatingFunction1.");
}

ptask RepeatingFunction3[500](playerid)
{
	printf("Called every 500ms PER PLAYER (balanced internally).");
}
```
That is literally it. The full format is:
```pawn
task FUNCTION_NAME[DELAY]()
{
	CODE();
}

ptask FUNCTION_NAME[DELAY](playerid)
{
	CODE();
}
```
A task is called after the given delay constantly, so RepeatingFunction1 above will be called every second for as long as the server is running. RepeatingFunction3 above will be called twice a second for every player on the server for as long as a player is connected. No players means no timers running, seven players means seven timers running. Note that internally it might not be seven REAL timers, it just means that the function will be called seven times every half second, the system load-balances internally. These functions are also offset from each other - RepeatingFunction1 and RepeatingFunction2 both have the same fequency but will not be called at the same time ever to spread out server load.

### Calling
If you need to, you can still call timer functions directly:
```pawn
#include <YSI\y_timers>

task RepeatingFunction[1000]()
{
	printf("Called every second, and when called explicitly.");
}

main()
{
	RepeatingFunction();
}
```
### Notes
Tasks cannot have parameters (except playerid to ptasks) and the compiler will give errors if you try to add them (or more accurately, will give errors if you try use those parameters). This is because they are managed automatically and thus the system doesn't know what data you want to pass to them (and the data would be constant anyway).

The balancing algorithm is not perfect. If you have one timer at 400ms and one at 700ms, they will conflict once every 2.8s. This currently only offsets timers with the same periods, however cross-period-collisions are much rarer so not an issue most of the time.

## Timers
Timers (as ever) allow you to call functions after a given time, without needing to mess about with SetTimerEx:
```pawn
#include <YSI\y_timers>

timer DelayedTimer[500](playerid)
{
	printf("May be called after 0.5 seconds.");
}

main()
{
	defer DelayedTimer(42);
}
```
That will call DelayedTimer after 500ms, passing the value 42. The full format of the definition is:
```pawn
timer FUNCTION_NAME[DELAY](PARAMETERS)
{
	CODE();
}
```
The delay parameter can be anything that becomes a number - a macro sum, a constant, or even something using one of the parameters to the function:
```pawn
timer Timer1[6 * 4]()
{
}

timer Timer2[something](something)
{
}

#define TIME 1000

timer Timer3[TIME]()
{
}
```
These rules (except for using parameters) apply to tasks as well.

### Calling
There are three ways of calling timer functions:

### defer
This calls the function once after the time defined on the function:
```pawn
main()
{
	defer DelayedFunction(42);
}
```

### repeat

This calls the timer repeatedly after the delay defined on the timer. This is similar to tasks but you can stop the timer again:

```pawn
main()
{
	repeat DelayedFunction(42);
	new
		Timer:x = repeat DelayedFunction(42);
	stop x;
}
```

### Normal call

This simply calls the function instantly like a normal function:
```pawn
main()
{
	DelayedFunction(42);
}
```


### Control
The repeat example above gave one more little command: stop. This, quite simply, stops a running timer.

### Overrides
The two timer calls above can have their times changed from the defaults:
```pawn
#include <YSI\y_timers>

timer DelayedFunction[1000](playerid)
{
	printf("USUALLY called after 1 second.");
}

main()
{
	// Called instantly.
	DelayedFunction(42);
	// Called in 1 second (default).
	defer DelayedFunction(42);
	// Called in 200 ms (override).
	defer DelayedFunction[200](42);
	// Called every second (default).
	repeat DelayedFunction(100);
	// Called every 7 seconds (override).
	repeat DelayedFunction[7 * 1000](100);
}

```

### Arrays and Strings

Due to a bug in SetTimerEx you can not pass strings or arrays to delayed functions. I will admit this is my fault as I'm the one who wrote SetTimerEx in the first place, but it's not the fault of this library. However, this problem is now fixed, for both strings and arrays, when using y_timers:
```pawn
#include <YSI\y_timers>

// Arrays must ALWAYS be followed by their length.
// ALWAYS!
timer ArrayTimer[500](arr[], len)
{
	printf("Array (%d): %d, %d, ...", len, arr[0], arr[1]);
}

// Strings DO NOT need to be followed by their length, but MUST have
// a tag of "string:" (don't worry about tag mis-matches though).
timer StringTimer[500](string:str[])
{
	printf("String: %s", str);
}

main()
{
	new
		array[3] = {42, 43, 44};
	defer ArrayTimer(array, sizeof (array));
	defer StringTimer("Hi there");
}
```
