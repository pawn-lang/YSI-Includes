# FAQ

## Why Does My Loop Crash?
## AKA. Why Do I Get An Infinite Loop?

The most common cause of these issues is removing items from an iterator while in the iterator:

```pawn
foreach (new i : Iterator)
{
	Iter_Remove(Iterator, i);
}
```

In short, the reason for this is that `foreach` gets the next index from the current index, but if
you have removed the current index if can't be used any more.

This happens even if the `Iter_Remove` is nested in other function calls:

```pawn
foreach (new i : Iterator)
{
	Function(i);
}
```

```pawn
Function(index)
{
	Iter_Remove(Iterator, index);
}
```

The iterator is still modified during the loop.

The simple solution is `Iter_SafeRemove`.  This gets the previous still valid index first, **then**
removes the given index from the iterator.  So after the call the loop index needs to be updated:

```pawn
foreach (new i : Iterator)
{
	new prev;
	Iter_SafeRemove(Iterator, i, prev);
	SendClientMessage(i, COLOUR_MESSAGE, "A message to someone.");
	i = prev;
}
```

If the parameters to `Iter_SafeRemove` are the same variable twice, the value is *clobbered* by the
call and can't be used afterwards:

```pawn
foreach (new i : Iterator)
{
	Iter_SafeRemove(Iterator, i, i);
	SendClientMessage(i, COLOUR_NO, "This won't send correctly.");
}
```

So ensure it is last:

```pawn
foreach (new i : Iterator)
{
	SendClientMessage(i, COLOUR_YES, "This will send correctly.");
	Iter_SafeRemove(Iterator, i, i);
}
```

If the `Iter_SafeRemove` is in a nested function you need to ensure that the parameter can be
propagated back by passing it by reference:


```pawn
foreach (new i : Iterator)
{
	SendClientMessage(i, COLOUR_YES, "This will send correctly.");
	Function(i);
	SendClientMessage(i, COLOUR_NO, "This won't send correctly.");
}
```

```pawn
Function(&index)
{
	Iter_SafeRemove(Iterator, index, index);
}
```

The most common pattern seen that removes items from an iterator is looping over all items in the
iterator, doing something with them, and removing them all:

```pawn
foreach (new i : Iterator)
{
	DoThing(i);
	Remove(i);
}
```

In that case the simpler solution is `Iter_Clear` after the loop:

```pawn
foreach (new i : Iterator)
{
	DoThing(i);
}
Iter_Clear(Iterator);
```

## Why Do I Get A Negative Array Index Access?

This is a recent change designed to help spot the previous issue, that of using `Iter_Remove` from
inside a loop that uses it.  Before, doing so could result in an infinite loop, which is sometimes
hard to spot.  The code in `Iter_Remove` was slightly modified to replace the removed value with a
negative number (while still preserving reverse iteration properties).  This will often cause a
crash when you try and use that next iterator value, BUT this crash is identifiable with the
crashdetect plugin.  If you see a negative index value of `-123456789` this is almost certainly the
cause, but other values are also possible.  They will always be less than `-size`, the capacity of
the iterator as a negative number.  E.g. an index of `-1` cannot be from this change, but an index
of `-(MAX_PLAYERS + 10)` might be.

If you get this error see [the advice above](https://github.com/pawn-lang/YSI-Includes/blob/5.x/YSI_Data/y_foreach/faqs.md#why-does-my-loop-crash)
for how to resolve this issue.

## Why Did You ADD Negative Array Index Access?

As mentioned before - they are easier to spot.  A mistake which causes a loud error that can be
pinpointed is far better than a mistake which can cause wierd errors you might not notice.  If
crashdetect (yes, this does rely on using the plugin, but you would probably struggle to spot the
problem without it before anyway) can tell you the exact line of the invalid access with a message
as specific as trying to access index `-123456789` that's vastly better than randomly hanging.

