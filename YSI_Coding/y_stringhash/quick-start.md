# Quick Start

y_stringhash allows you to make compile-time hashes of simple strings.  What's a hash?  It's a semi-unique number assigned to a string, so you can see if two different strings are the same just by comparing the numbers instead of the whole strings.  For large numbers of string comparisons (such as a dictionary search) this can greatly save time over always using `strcmp`.  More importantly, because y_stringhash does this at compile-time, you can use the results in places which only take constants, such as `switch`.

`_H<>` is the basic interface.  To get the unique number for a string, simply use:

```pawn
new hash = _H<string goes here>;
```

The string must be a literal without `""`s:

```pawn
new hash1 = _H<Hello world>; // Correct.
new hash2 = _H<"Hello world">; // Won't compile.
new string[] = "Hello world";
new hash3 = _H<string>; // Will return the hash for `"string"` not `"Hello world"`.
```

The most common use is in `switch`:

```pawn
YCMD:buy(playerid, const params[], help)
{
	if (help)
	{
		SendClientMessage(playerid, COLOUR_HELP, "/buy command to demonstrate `_H<>`.");
		return 1;
	}
	switch (YHash(params))
	{
	case _H<gun>: // Give them a gun.
	case _H<health>: // Give them some health.
	case _H<car>: // Give them a car.
	}
	return 1;
}
```

`YHash(string)` is the run-time equivalent to `_H<>`.  The default hash used is called [djb2](http://www.cse.yorku.ca/~oz/hash.html), and is used all over YSI (referenced as "Bernstein").  There is a highly optimised implementation in y_utils, called `Bernstein()`.

