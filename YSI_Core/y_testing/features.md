## `@test()` parameters

### `.run`

Will ensure this test is never run.  Useful for testing things at compile-time only, such as syntax and warnings:

```pawn
@test(.run = false) CompileTest()
{
	// Test the `foreach` syntax only.
	foreach (new i : Player)
	{
	}
}
```

### `.group`

Attach multiple tests together in to a single group.  Tests in the same group are collected together in the output, and only specific groups can be specified as being run.

```pawn
@test(.group = "Message Tests") SendClientMessage1(playerid)
{
	SendClientMessage(playerid, COLOUR_RED, "hi");
	ASK(playerid, "Did you see a message saying `hi`?");
}

@test(.group = "Message Tests") SendClientMessage2(playerid)
{
	SendClientMessage(playerid, COLOUR_RED, "you");
	ASK(playerid, "Did you see a message saying `you`?");
}

@test(.group = "Message Tests") GameTextForPlayer(playerid)
{
	GameTextForPlayer(playerid, 2, 5000, "hi");
	ASK(playerid, "Did you see a message saying `hi`?");
}
```

### `.slow`

Marks a test as being slow.  Slow tests are not run by default, even when `RUN_TESTS` is defined.  To run a slow test either also define `RUN_SLOW_TESTS` or specify this as the only test to be run with `JUST_TEST` (see below).

```pawn
@test(.slow = true) CountTo1000000000()
{
	new j = 0;
	for (new i = 0; i != 1000000000; ++i)
	{
		ASSERT(i == j);
		j += 1;
	}
}
```

## Compile-Time Options

### `RUN_TESTS`

Define this to auto-run all your custom tests.  This does not run YSI's tests.  If this is not defined the tests are not compiled at all and take up no space in the AMX.

### `RUN_SLOW_TESTS`

Define this to auto-run all your slow tests as well if `RUN_TESTS` is also defined.

### `JUST_TEST`

Define this to only run one single test.  Again this requires `RUN_TESTS` to be defined or no tests will be run (or exist).  This can be used when you are developing a new piece of code, rather than checking for regressions.  Even slow tests will always be run if specified in `JUST_TEST`.

```pawn
#define JUST_TEST MyNewTest
#define RUN_TESTS
#include <YSI_Core\y_testing>

@test() WontBeRun()
{
	ASSERT(FALSE);
}	

@test() MyNewTest()
{
	ASSERT(TRUE);
}
```

### `YSI_TESTS`

This includes all the YSI tests as well.  You probably don't want this.

### `YSI_DIALOG_ASK`

Use dialogs instead of `y`/`n` keys for getting user `ASK` responses.

### `JUST_TEST_GROUP`

Run all the tests in only one group.  Slow tests are not run by default in this case, unlike the `JUST_TEST` case and require `RUN_SLOW_TESTS`.  This takes a string, not a test name.

```pawn
#define JUST_TEST_GROUP "Main"
#define RUN_TESTS
#include <YSI_Core\y_testing>

@test(.group = "Other") WontBeRun()
{
	ASSERT(FALSE);
}	

@test() AlsoNotRun()
{
	ASSERT(FALSE);
}	

@test(.group = "Main") MyGroupedTest()
{
	ASSERT(TRUE);
}
```

## Assertions

There are multiple different ways to test if something is true, and the more specialist ones give better error messages when they fail.

```pawn
// Basic tests.
ASSERT(expr); // Test if `expr` is true.

// Number tests.
ASSERT_EQ(expr, num); // Test if `expr == num`, with the actual value given in a failure.
ASSERT_NE(expr, num); // Test if `expr != num`, with the actual value given in a failure.
ASSERT_LT(expr, num); // Test if `expr < num`, with the actual value given in a failure.
ASSERT_LE(expr, num); // Test if `expr <= num`, with the actual value given in a failure.
ASSERT_GT(expr, num); // Test if `expr > num`, with the actual value given in a failure.
ASSERT_GE(expr, num); // Test if `expr >= num`, with the actual value given in a failure.

// Zero tests.
ASSERT_ZE(expr); // Test if `expr == 0`, with the actual value given in a failure.
ASSERT_NZ(expr); // Test if `expr != 0`, with the actual value given in a failure.

// String tests.
ASSERT_SAME(expr, "string"); // Test if `expr == "string"`, with the actual value given in a failure.
ASSERT_DIFF(expr, "string"); // Test if `expr != "string"`, with the actual value given in a failure.
ASSERT_NEAR(expr, "string"); // Test if `expr == "string"`, ignoring case, with the actual value given in a failure.
```

These assertions will also give tag-mismatch warnings when appropriate, and can determine the tag types to customise their comparisons.  For example, using `ASSERT_EQ` on `Float:` variables will check that the two values are very close together, but will not check that they are precisely the same.  They will also use this tag information to more nicely format the different number types in failure messages.

## `ASK`

This is for player tests.  Often when testing that something happened on the client the only way to know for certain is to ask a player if they saw it happen.

```pawn
ASK(playerid, "question", {Float, _}:...);
```

This will give a client message (prompting for `n`/`y` key inputs) or a dialog (depending on settings) asking the player a question.  If they answer "yes" the test passes.  Unfortunately you can only feasibly have one `ASK` per `@test()`, while you can have hundreds of `ASSERT`s per `@test()`.  For convenience the question is formatted so you can do:

```pawn
ASK(playerid, "Can you see %d gangzones?", gangZonesCreated);
```

