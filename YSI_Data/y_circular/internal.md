# Internal Details

## Macros

The "Iterator:" macro generates two variables - one to store the main iterator
data (the array) and the other to store the number of items in the iterator (the
count):

```pawn
new
	Iterator:MyIter<7>;
```

Becomes:

```pawn
new
	// Number of items currently in the iterator.
	Iter_Single@MyIter,
	// The data in the iterator, plus internal data (all slots invalidated).
	Iterator@MyIter[7 + 1] = {14, 13, ...};
```

The names are designed to give vaguely meaningful errors - `Undefined symbol "Iterator@MyIter"` might give you some hint that an iterator is missing.  `Iter_Single` denotes a standard iterator, `Iter_Multi` denotes a multi-iterator both are the number of items currently
added to the iterator, and not the total size of the iterator.  "Iterator@MyIter"
is the values currently stored in the iterator.

Iterators are "linked lists", which means that each element points to the next
valid element. Before adding anything to the array it is declared using:

```pawn
Iterator@MyIter[7 + 1] = {7 * 2, 7 * 2 - 1, ...};
```

This declares the array as 7 cells big to store all the valid data, with an
extra cell to store the start point of the list. The initialisation data is
carefully crafted to be invalid. The use of "- 1" for the second value means
that the compiler attempts to infer a pattern to the array declaration using the
first two values (and determines that the pattern is that each slot is one less
than the previous slot). This means that the array starts off looking like:

```
14, 13, 12, 11, 10,  9,  8,  7
```

Most of those values are greater than 7, so they are invalid. Our extra slot
(the last one) has a value of "7" which is ALMOST valid. The code is designed
so that the last slot ALWAYS contains its own index, which equals the declared
size of the iterator. This is important for the linked list as will be shown
later.

After adding the values "0", "4", and "6" the array will look like:

```
 4, 13, 12, 11,  6,  9,  7,  0
``` 
 
FOUR slots have changed value - 0, 4, and 6 (the values we added to the
iterator), and slot 7 (our extra slot added by the "Iterator:" macro). Slots
1, 2, 3, and 5 have not been touched so are all still invalid (as shown by the
fact that they are all greater than the maximum valid slot value).

## Linked Lists

That's interesting, but why is it like that; and why is slot 0 "4", slot 4 "6"
etc? Each valid slot has a value LESS THAN OR EQUAL TO the iterator size. So
slot 0 is valid and has a value "<= 7" to prove it, as do slots 4, 6, and 7.
But wait, slot 7 CAN'T be valid because it is too big - only slots 0 to 6 are
within the declared range of the iterator, so why does it have a valid value
stored in it? More to the point, why is that last slot initially declared as
"7", when it shouldn't be valid?

Each valid slot's value is the index of the next valid slot. If we start at
slot 0 we get the value "4", jumping to slot 4 gives us the value "6", and slot
6 is the last item we initially added to the iterator:

```pawn
Iter_Add(MyIter, 0);
Iter_Add(MyIter, 4);
Iter_Add(MyIter, 6);
```

Already it should be clear how "foreach" can loop over only values that exist,
unlike "for" which must loop over every possible value. From the information
above we can write:

```pawn
for (new i = Iterator@MyIter[0]; ; i = Iterator@MyIter[i])
{
	printf("%d", i);
}
```

That will loop forever and output:

```
0
4
6
7
0
4
6
7
...
```

We need an end condition for the loop - which is exactly what we have the extra
slot at the end for. Slot 6 has the value "7", which is a value we have already
determined should be invalid, and indeed it is. So we can modify our loop to:

```pawn
for (new i = Iterator@MyIter[0]; i != 7; i = Iterator@MyIter[i])
{
	printf("%d", i);
}
```

New output:

```
0
4
6
```

## Start Point

Excellent. The linked list works and ends correctly - but does it START
correctly? In this example yes, but in the more general case NO! What happens
if we never added slot 0 to the iterator?

```pawn
new
	Iterator:MyIter<7>;
Iter_Add(MyIter, 4);
Iter_Add(MyIter, 6);
foreach (new i : MyIter)
{
	printf("%d", i);
}
```

The output SHOULD BE:

```
4
6
```

But if we use our loop above we get:

```
14
<crash>
```

The problem is here:

```pawn
new i = Iterator@MyIter[0];
```

After adding only the values "4" and "6", the array looks like:

```
14, 13, 12, 11,  6,  9,  7,  4
```

But we start at index 0, which has the value "14". We print that value, then
try use that value as an index in to the array. The array has size "7 + 1", so
accessing slot "14" is an out-of-bounds error and won't work (or will crash or
do any other unpredictable things). So instead we need:

```pawn
for (new i = Iterator@MyIter[4]; i != 7; i = Iterator@MyIter[i])
{
	printf("%d", i);
}
```

And if we never add ANY values to the array we still have the original:

```
14, 13, 12, 11, 10,  9,  8,  7
```

And the resulting required code is below (note that this will end instantly
because the value of slot 7 is "7", so the condition will fail immediately):

```pawn
for (new i = Iterator@MyIter[7]; i != 7; i = Iterator@MyIter[i])
{
	printf("%d", i);
}
```

In each case, the "new i" value must be initialised to the value stored in the
first valid slot - so we need to determine WHICH is the first valid slot. That
just so happens to be stored in the last slot of the array:

```pawn
for (new first = Iterator@MyIter[7], i = Iterator@MyIter[first]; i != 7; i = Iterator@MyIter[i])
{
	printf("%d", i);
}
```

This is, in essence, how "foreach" works, and that loop will now correctly
print all the added values (if any) in all cases.

## Improvements

Now we have a basic understanding of how "foreach" works under the hood, lets
look at how the macro itself works and generates significantly better code than
that presented above. The simplest way to present this is to show it:

Doing:

```pawn
foreach (new i : MyIter)
{
	printf("%d", i);
}
```

Gives:

```pawn
for (new i = 7; (i = Iterator@MyIter[i]) != 7; )
{
	printf("%d", i);
}
```

This is significantly simplified from the original version, but still
equivalent. The only possibly confusing part is the assignment within the
condition, but this is equivalent to:

```pawn
i = Iterator@MyIter[i];
if (i != 7)
{
	printf("%d", i);
}
else break;
```

The first action in the loop is to get the NEXT item, then use that item. Thus
we have to start with an item that is invalid or else the very first element
would always get skipped because we would have the first item and instantly get
the second item.

## Generic Loop Functions

It might help to think of the loop like this:

```pawn
for (new i = MyIter[7]; i != 7; i = MyIter[i])
{
}
```

Or more generically:

```pawn
for (new i = MyIter[START_SLOT]; i != END_VALUE; i = MyIter[i])
{
}
```

But slightly more efficient. It just so happens that "START_SLOT" and
"END_VALUE" are always the same, and always equal to the declared size of the
iterator). We can define and use the generic values:

```pawn
#define START_SLOT(%0) (sizeof (%0) - 1)
#define END_VALUE(%0)  (sizeof (%0) - 1)

for (new i = START_SLOT(Iterator@MyIter); (i = Iterator@MyIter[i]) != END_VALUE(Iterator@MyIter); )
{
	printf("%d", i);
}
```

These macros already exist in y_iterate so you don't even need the "YSII_Ag"
suffixes:

```pawn
for (new i = Iter_Begin(MyIter); (i = Iter_Next(MyIter, i)) != Iter_End(MyIter); )
{
}
```

That code is EXACTLY equivalent to the default "foreach" use, plus it gives you
more control over the looping should you so desire:

```pawn
stock PrintFivePlayers()
{
	new
		printed = 0;
	foreach (new i : Player)
	{
		printf("%d", i);
		// Limit the display.
		++printed;
		if (printed == 5) break;
	}
}
```

Using the alternate form:

```pawn
stock PrintFivePlayers()
{
	for (new i = Iter_Begin(Player), printed = 0; printed != 5 && (i = Iter_Next(MyIter, i)) != Iter_End(MyIter); ++printed)
	{
		printf("%d", i);
	}
}
```

Granted in this case the second version may be less appealing to look at, but it
does avoid the use of "break" and keeps all the loop end conditions in one
place. It also combines the efficiency of "foreach" with more code.

You may be tempted to "optimise" the loop by calling "Iter_End" just once with:

```pawn
stock PrintFivePlayers()
{
	for (new i = Iter_Begin(Player), printed = 0, end = Iter_End(MyIter); printed != 5 && (i = Iter_Next(MyIter, i)) != end; ++printed)
	{
		printf("%d", i);
	}
}
```

You can, and that will run, but "Iter_End" is actually a macro not a function
call and doing it this way is a rare case in which that will end up being LESS
efficient unfortunately.

## Reverse Iteration

Using similar methods to those above you can also go BACKWARDS through an
iterator:

```pawn
stock PrintPlayersBackwards()
{
	for (new i = Iter_End(Player); (i = Iter_Prev(MyIter, i)) != Iter_Begin(MyIter); )
	{
		printf("%d", i);
	}
}
```

However, while this was added to "y_iterate" for completeness sake, it is
INCREDIBLY inefficient and you are MUCH better off using this where possible:

```pawn
stock PrintPlayersBackwards()
{
	for (new i = MAX_PLAYERS; i--; )
	{
		if (IsPlayerConnected)
		{
			printf("%d", i);
		}
	}
}
```

This is because iterators are one-way (and very good at doing things one way),
but when you try and go backwards they can still only go forwards so must go all
theway through the whole loop until they hit the current value and know where
they came from for EVERY iteration. Tracing the loop would give something like:

```
7, 0, 4, 6, 7 - Print 6
7, 0, 4, 6 - Print 4
7, 0, 4 - Print 0
7, 0 - End
```
I did add efficient reverse iterators to the code once, but they doubled the
memory usage and were rarely (if ever) used so were basically worthless.

## `foreach` Types

We will now look at one important chunk of the macros in "y_iterate", used to
determine exactly which version of `foreach` has been entered. To understand
the macros however, we must first understand what we are trying to parse. The
following code demonstrates all the possible variations of `foreach` that can
appear in pawn:

```pawn
// Original version (implicit declaration):
foreach (Player, playerid)

// New version:
foreach (playerid : Player)

// New version with declaration:
foreach (new playerid : Player)

// New version with tag declaration:
foreach (new Group:group : PlayerGroup)
```

We need to write macros to correctly identify and process each of these versions
of the keyword. There is also an older version of the command that looked like:

```pawn
// Original version (no declaration):
foreachex (Player, playerid)
```

This was different from `foreach` in that it DIDN'T declare `playerid` as a new
variable, which the standard `foreach` keyword did. This has been deprecated in
the later versions of "y_iterate" because the `new` keyword is now explicit.
Fortunately, this version is much easier to express in the new system.

There are two things that we need to detect - number of colons, and number of
`new` keywords. Zero colons means the old syntax is in use, anything else is
the new syntax. You could in theory have:

```pawn
// Original version with tag (implicit declaration):
foreach (PlayerGroup, Group:group)
```

However, this was never supported and no tagged iterators were ever written for
this older version. We can therefore ignore this possibility.

At this point I'd love to detail the logical progression that led to my
development of these macros, in the hope that people could learn something from
the thought process, but quite simply I can't! I have no idea how I came up
with this system, it was just a lot of thinking resulting in a brainwave that I
can't explain - which is a real shame IMHO. As a result, I can only document
how the macros work.

Note that some of this section is now a little out of date.  The basic structure is still the same, but special iterator support has improved significantly since this was written.  Also, this still uses the old internal naming scheme of `@YSII_Ag`, not `Iterator@` (which is designed for better user readability).  Despite this, the explanation of what the macros do should still help with understanding the current versions.

### Redefining `new`

The main `foreach` macro actually revolves around this macro:

```pawn
#define new%0|||%9|||%1:%2||| %9|||%0|||%1|||%2|||
```

That actually redefines the `new` keyword to something different (I'm not too
happy about having to do this). Because it redefines such a pivotal parf of the
PAWN language, I have made sure that it does not match common code. As you can
see, the pattern for matching is this:

```pawn
new  |||  |||  :  |||
```

I've used spaces here instead of macro parameters (`%0` etc) to make the pattern
clearer and represent optional code typed by the user. If you have any `new`
variable declarations with this exact sequence of operators after it then I
apologise - this will probably break you code. But I think that's unlikely!

The replacement for the macro is:

```pawn
%9|||%0|||%1|||%2|||
```

We detect the `new` keyword, but we don't have it present in the replacement, so
this code looks for `new` and removes it. It also shuffles the remaining
parameters and removes the detected colon, but the result is still not valid
code.

To further understand the macro, lets look at it being used:

```pawn
#define foreach%1(%0) for (new Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||%0||| )
```

Here `%1` simply detects extra spaces and discards them. We then add the word
`new`, which as we've seen is instantly detected and removed. Why not simply
write:

```pawn
#define foreach%1(%0) for (Y_FOREACH_THIRD|||Y_FOREACH_SECOND|||%0||| )
```

You might think that would be the result of the macros after calling the `new`
macro, but you would be wrong - sometimes...

The key fact to note here is that the `new` macro looks for three sets of `|||`
AND a colon. We didn't write the colon in the replacement text for `foreach`,
so it must be part of the parameter `%0`. If we type:

```pawn
foreach (new playerid : Player)
```

We have `%1` as a single space (discarded) and `%0` as `new playerid : Player`.
Manually replacing macros gives:

```pawn
// Detect and replace `foreach`....
for (new Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||new playerid : Player||| )

// Detect and replace `new`...
for (Y_FOREACH_THIRD||| Y_FOREACH_SECOND|||new playerid ||| Player||| )
```

So what happens if we DON'T type a colon? The only time this happens is when we
use the old-style `foreach` syntax:

```pawn
foreach (Player, playerid)

// Detect and reaplce `foreach`:
for (new Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||Player, playerid||| )

// DO NOT replace `new` because there is no colon to match.
```

Compare the outputs side-by-side:

```pawn
foreach (new playerid : Player)
// Gives:
for (Y_FOREACH_THIRD||| Y_FOREACH_SECOND|||new playerid ||| Player||| )

foreach (Player, playerid)
// Gives:
for (new Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||Player, playerid||| )
```

Each `foreach` line declares a new variable (this fact is hidden in the second
one, which the main motivation for developing the new syntax). In the resulting
generated code each `for` loop has a `new` keyword somewhere in it, and each one
starts with a DIFFERENT macro. The first one starts with `Y_FOREACH_THIRD`, the
second one starts with `Y_FOREACH_SECOND` (don't worry that the first one isn't
called `Y_FOREACH_FIRST`, that's just because of the order I am describing the
macros in). This demonstrates why we remove the `new` keyword, and why we
shuffle the first two parameters around.

### Y_FOREACH_SECOND

This macro deals with the old version of the syntax, and is very simple to
parse. From the earlier parts of this tutorial, we know that the end product of
a `foreach` loop is:

```pawn
// This:
foreach (Iter, var)
// Or this:
foreach (new var : Iter)
// Becomes:
for (new var = sizeof (Iter@YSII_Ag) - 1; (var = Iter@YSII_Ag[var]) != sizeof (Iter@YSII_Ag) - 1; )
```

So we can very quickly construct the `Y_FOREACH_SECOND` macro and step through
its expansion:

```pawn
// Macro:
#define Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||%2,%1||| %1 = sizeof (%2@YSII_Ag) - 1; _:(%1 = %2@YSII_Ag[%1]) != sizeof (%2@YSII_Ag) - 1;

// Input:
foreach (Player, playerid)

// Steps:
// Detect and reaplce `foreach`...
for (new Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||Player, playerid||| )

// DO NOT replace `new` because there is no colon to match.

// Detect and replace `Y_FOREACH_SECOND`:
for (new  playerid = sizeof (Player@YSII_Ag) - 1; _:( playerid = Player@YSII_Ag[ playerid]) != sizeof (Player@YSII_Ag) - 1; )

// Done!
```

### Y_FOREACH_THIRD

If this macro is the first one listead, instead of `Y_FOREACH_SECOND`, then the
user used the new syntax instead of the old syntax, so let us parse that
instead (here `%9` stores the other macro name and discards it):

```pawn
// Macro:
#define Y_FOREACH_THIRD|||%9|||%1|||%2||| %1 = sizeof (%2@YSII_Ag) - 1; _:(%1 = %2@YSII_Ag[%1]) != sizeof (%2@YSII_Ag) - 1;

// Input:
foreach (new playerid : Player)

// Steps:
// Detect and reaplce `foreach`...
for (new Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||new playerid : Player||| )

// Detect and replace `new`...
for (Y_FOREACH_THIRD||| Y_FOREACH_SECOND|||new playerid ||| Player||| )

// Detect and replace `Y_FOREACH_THIRD`...
for (new playerid  = sizeof ( Player@YSII_Ag) - 1; _:(new playerid  =  Player@YSII_Ag[new playerid ]) != sizeof ( Player@YSII_Ag) - 1; )

// DO NOT replace `new` because there are no `|||`s to match.

// Done!
```

BAH! So close! The `new` keyword is still attached to the `playerid` symbol,
so every time we use one we use the other. In this case, we need to again
detect and remove the `new` keyword - an operation that we already wrote a macro
for:

```pawn
#define new%0|||%9|||%1:%2||| %9|||%0|||%1|||%2|||
```

This is where the `foreach` macros start getting really clever by repeatedly
calling this `new` macro with different macro names as parameters. The first
time we passed the two macros called `Y_FOREACH_SECOND` and `Y_FOREACH_THIRD`,
this time we will pass different ones. Let's have a second attempt at that
`Y_FOREACH_THIRD` macro:

```pawn
// We previously removed the colon, but now we must put it back to be detected.
#define Y_FOREACH_THIRD|||%9|||%1|||%2||| %1|||Y_FOREACH_FOURTH|||%1:%2|||

// If there is a `new` in `%1`, then `Y_FOREACH_FOURTH` will be run.
#define Y_FOREACH_FOURTH|||%0|||%1|||%2||| new %0 = sizeof (%2@YSII_Ag) - 1; _:(%0 = %2@YSII_Ag[%0]) != sizeof (%2@YSII_Ag) - 1;

// Input:
foreach (new playerid : Player)

// Steps:
// Detect and reaplce `foreach`...
for (new Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||new playerid : Player||| )

// Detect and replace `new`...
for (Y_FOREACH_THIRD||| Y_FOREACH_SECOND|||new playerid ||| Player||| )

// Detect and replace `Y_FOREACH_THIRD`...
for (new playerid |||Y_FOREACH_FOURTH|||new playerid : Player||| )

// Detect and replace `new` again...
for (Y_FOREACH_FOURTH||| playerid |||new playerid ||| Player||| )

// Detect and replace `Y_FOREACH_FOURTH`...
for (new  playerid  = sizeof ( Player@YSII_Ag) - 1; _:(  playerid  =  Player@YSII_Ag[  playerid ]) != sizeof ( Player@YSII_Ag) - 1; )

// DO NOT replace `new` because there are no `|||`s to match.

// Done!
```

By calling the `new` macro twice we have managed to strip off just the word
`new` from `playerid` so that we know it was present but can add it in only
where we want it.

### Why Redefine `new`?

There are a couple of ways to detect specific pieces of text - a define is one,
putting the text directly in the pattern is another. To detect the keyword
`new` we could do:

```pawn
#define new%0|||
```

Or:

```pawn
#define OTHER%0new%1|||
```

The first will detect anything starting with `new`, the second will detect
anything that starts with `OTHER` (just as an example) and that includes the
text `new` somewhere after it. The difference is in exactly how much is
matched. A define CALLED `new`, as the first one is, will search for only that
exact word - the word `newt` will NOT be matched. The second one will match
exactly the word `OTHER`, but then just searches for the three letters `n`, `e`,
and `w` in order after it, so WILL detect the following:

```pawn
MY OTHER newt|||
```

In that case, `%0` will be a single space and `%1` will be the letter `t`. This
is a subtle point when dealing with the pre-processor. This is important
because were we to use the second method, any variable name with `new` within it
would cause a compilation error:

```pawn
foreach (newt : Animal)
```

There is a second reason as well - the result if the match is NOT made. If we
do:

```pawn
#define S: MACRO_1 MACRO_2
#define MACRO_1%0MACRO_2%0new%1||| new %1; // Found `new`.
#define MACRO_2%1||| %1; // Didn't find `new`.
```

(Side note, the use of `%0` twice in that example is valid - the second one will
overwrite the contents of the first one, but both are discarded anyway).

Then doing:

```pawn
S: new var|||
```

Will give:

```pawn
new var;
```

But doing:

```pawn
S: printf("%d", var)|||
```

Will give:

```pawn
MACRO_1   printf("%d", var);
```

Because we couldn't find `new`, the `MACRO_1` macro is never matched and the
text remains, leaving us with the word `MACRO_1` in the source-code where it
shouldn't be, and thus giving a compilation error.

If we instead do something like:

```pawn
#define S: new MACRO_3|||
#define new%0|||%1||| new other,%1;
#define MACRO_3|||%1; %1
```

Then doing:

```pawn
S: var|||
```

Will give:

```pawn
new other, var;
```

And doing:

```pawn
S: var;
```

Will give:

```pawn
new var;
```

In the second case, we have an excess `new` left over from the first macro that
wasn't matched, but we have designed the macros such that this remainder is
still valid in this context, and so that we won't get any compile-time errors.
This is basically how all the macros in "y_iterate" are designed - if the `new`
keyword is not matched, it must be because we have a pattern that requires the
`new` keyword to be present and therefore leaving it in the source code output
is valid.

### The Remainder

The code presented so far is a little inaccurate, but is enough to describe the
basic principles on which the whole code block is based. They show how we use
the `new` keyword to detect certain patters and strip out certain words, and how
the macros are shuffled around so that different code is run when `new` is there
and when it isn't. Given this grounding, the remaining macros will not be
detailed to the same extent the first few are, but just to get you started, here
is the REAL version of Y_FOREACH_THIRD (note that `%1` and `%2` are the other
way around here to what they were before):

```pawn
#define Y_FOREACH_THIRD|||%0|||%1|||%2||| %1=Y_FOREACH_FIFTH|||Y_FOREACH_FOURTH|||%1:%2|||
```

`Y_FOREACH_FOURTH` is still there, but `Y_FOREACH_FIFTH` has been added,
separated from whatever is in `%1` by an equals sign (if `%1` is a variable, a
lack of delimiter here could cause the to names to merge and no longer be
valid), to run more code when there is no `new` keyword:

```pawn
#define Y_FOREACH_FIFTH|||Y_FOREACH_FOURTH|||%1:%2||| sizeof (%2@YSII_Ag) - 1; _:(%1 = %2@YSII_Ag[%1]) != sizeof (%2@YSII_Ag) - 1;
// Handles:
foreach (playerid : Player)
```

Note that again, the real macro is slightly different, but the extra indirection
handles iterator arrays and special iterators, it can basically be read as the
code above:

```pawn
#define Y_FOREACH_FIFTH|||Y_FOREACH_FOURTH|||%1:%2||| _Y_ITER_FOREACH_SIZE(%2);_:(%1=_Y_ITER_ARRAY$%2$YSII_Ag[%1])!=_Y_ITER_MAYBE_ARRAY(%2);
```

`_Y_ITER_MAYBE_ARRAY` gets the size of a slot in an iterator, for both normal
iterators and iterator arrays. `_Y_ITER_FOREACH_SIZE` does the same thing, but
can also detect special iterators defined with `()` syntax. `_Y_ITER_ARRAY`
gets the next slot in the current iterator for both normal iterators and arrays.

The real definition of `Y_FOREACH_FOURTH` is not actually a final output - it is
another redirection designed to try and detect declarations with tag overrides.
It adds in the macros `Y_FOREACH_SIXTH` and `Y_FOREACH_SEVENTH`:

```pawn
// Tries to detect a colon via `new` despite us not adding it back (as in 3rd).
#define Y_FOREACH_SEVENTH|||%9Y_FOREACH_SIXTH;%0|||%1|||%2||| new %0:%1 = %0:(sizeof (%2@YSII_Ag) - 1); _:(%1 = %0:_Y_ITER_ARRAY$%2$YSII_Ag[%1]) != sizeof (%2@YSII_Ag) - 1;
// Handles:
foreach (new Group:g : CreatedGroup)

#define Y_FOREACH_SIXTH;%1|||Y_FOREACH_SEVENTH|||%2||| %1 = sizeof (%2@YSII_Ag) - 1; _:(%1 = _Y_ITER_ARRAY$%2$YSII_Ag[%1]) != sizeof (%2@YSII_Ag) - 1;
// Handles:
foreach (new playerid : Player)
```

So to recap:

`Y_FOREACH_SECOND` - Generates code for the original syntax.
`Y_FOREACH_FIFTH` - Generates code for the new syntax with no `new`.
`Y_FOREACH_SEVENTH` - Generates code for the new syntax with tags.
`Y_FOREACH_SIXTH` - Generates the remainder of the new syntax (`new`, no tags).

The others just call `new` again to try resolve which version to use.

Hopefully from this description you should now be able to read and comprehend
this code, taken straight from "y_iterate":

```pawn
#define foreach%1(%0) for(new Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||%0|||)

// This allows us to use `new` multiple times - stripping off ONLY whole words.
#define new%0|||%9|||%1:%2||| %9|||%0|||%1|||%2|||

// This one is called if the new syntax is required, but the state of `new` is
// as-yet unknown.  This attempts to call `%1` as a macro, if it starts with
// `new` as a whole word then it will (and will also helpfully strip off the
// `new` keyword for us).
#define Y_FOREACH_THIRD|||%0|||%1|||%2||| %1=Y_FOREACH_FIFTH|||Y_FOREACH_FOURTH|||%1:%2|||

// This is called if the `new` macro is called for a second time.
#define Y_FOREACH_FOURTH|||%0=Y_FOREACH_FIFTH|||%1|||%2||| new Y_FOREACH_SIXTH;%0|||Y_FOREACH_SEVENTH|||%2|||

// This is called when there are tags on the `new` declaration.
#define Y_FOREACH_SEVENTH|||%9Y_FOREACH_SIXTH;%0|||%1|||%2||| new %0:%1=%0:_Y_ITER_FOREACH_SIZE(%2);_:(%1=%0:_Y_ITER_ARRAY$%2$YSII_Ag[%1])!=_Y_ITER_MAYBE_ARRAY(%2);

// This is called when there aren't.
#define Y_FOREACH_SIXTH;%0|||Y_FOREACH_SEVENTH|||%2||| %0=_Y_ITER_FOREACH_SIZE(%2);_:(%0=_Y_ITER_ARRAY$%2$YSII_Ag[%0])!=_Y_ITER_MAYBE_ARRAY(%2);

// This is called if `%1` didn't have `new` at the start.
#define Y_FOREACH_FIFTH|||Y_FOREACH_FOURTH|||%1:%2||| _Y_ITER_FOREACH_SIZE(%2);_:(%1=_Y_ITER_ARRAY$%2$YSII_Ag[%1])!=_Y_ITER_MAYBE_ARRAY(%2);

// This is the old version, but DON'T add `new` because that already exists from
// the failed `new` macro call above.
#define Y_FOREACH_SECOND|||Y_FOREACH_THIRD|||%1,%2||| %2=_Y_ITER_FOREACH_SIZE(%1);_:(%2=_Y_ITER_ARRAY$%1$YSII_Ag[%2])!=_Y_ITER_MAYBE_ARRAY(%1);
```
