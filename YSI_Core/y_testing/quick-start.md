## Example 1 - Simple test

This example defines a test, runs it automatically when the server starts, and checks that the result of a function call is `> 5`.

```pawn
#define RUN_TESTS // Auto-run tests.

#include <YSI_Core\y_testing>

@test() MyTest()
{
	ASSERT(MyFunctionCall() > 5);
}
```

## Example 2 - Player test

This example defines a test that needs a connected player, runs it automatically when the first player connects, and asks the player a y/n question.

```pawn
#define RUN_TESTS // Auto-run tests.

#include <YSI_Core\y_testing>

@test() MyPlayerTest(playerid)
{
	SetWeather(5);
	ASK(playerid, "Did the weather change?");
}
```

## Example 3 - Slow test

This defines a slow test.  Slow tests are not run by default as when there are a lot of tests they can significantly hamper turnaround, but sometimes they are required and can be explicitly enabled.

```pawn
#define RUN_TESTS // Auto-run tests.
#define RUN_SLOW_TESTS // Also slow tests.

#include <YSI_Core\y_testing>

@test(.slow = true) MySlowTest()
{
	for (new i = 0; i != 1000000; ++i)
	{
		for (new j = i; j != 1000000; ++j)
		{
			ASSERT(j >= i);
		}
	}
}
```

## Example 4 - Initialisation and closing

Some tests need things set up before the start (like database connections) and shut down again after they finish (even if they crash or fail).

```pawn
#define RUN_TESTS // Auto-run tests.
#define RUN_SLOW_TESTS // Also slow tests.

#include <YSI_Core\y_testing>

new Float:gPreviousHealth;

@testinit() MyCrashingTest(playerid)
{
	// Save their health to restore later.
	GetPlayerHealth(playerid, gPreviousHealth);
}

@test() MyCrashingTest(playerid)
{
	SetPlayerHealth(playerid, 20.0);
	new
		arr[5],
		idx = 5;
	// Oops, crashed.
	ASSERT(arr[idx] == 0);
}

@testclose() MyCrashingTest(playerid)
{
	// Restore their health.
	SetPlayerHealth(playerid, gPreviousHealth);
}
```

## Example 5 - Groups

You can collect a number of tests together as a single test suite.  You can then choose to only run tests in that one group:

```pawn
#define RUN_TESTS // Auto-run tests.
#define JUST_TEST_GROUP "suite" // Select the suite to run.

#include <YSI_Core\y_testing>

@test(.group = "suite") Test1()
{
}

@test(.group = "suite") Test2()
{
}

@test(.group = "suite") Test3()
{
}
```

