# y_profiling

Provides the `Profile:` macro for defining functions to profile and automatically running them when compiled with `RUN_PROFILINGS` defined.

Profiled code is repeated multiple times to get accurate results, AND the profiling is repeated multiple times to sum and average the results.  The code is equivalent to:

```pawn
for (new i = 0; i != runs; ++i)
{
	start = GetTickCount();
	for (new i = 0; i != repeats; ++i)
	{
		USER_CODE_HERE();
	}
	end = GetTickCount();
	result[i] = end - start;
}
```

This execution model, and the difference between `runs` and `repeats` is important for the rest of the documnetation.

PROFILING IS HARD!  Read the features for more details.

## YSI

For general YSI information, see the following links:

* [Installation](../installation.md)
* [Troubleshooting](../troubleshooting.md)

## Documentation

* [Quick Start](y_profiling/quick-start.md) - One very simple example of getting started with this library.
* [Features](y_profiling/features.md) - More features and examples.
* [FAQs](y_profiling/faqs.md) - Frequently Asked Questions, including errors and solutions.
* [API](y_profiling/api.md) - Full list of all functions and their meaning.
* [Internal](y_profiling/internal.md) - Internal developer documentation for the system.

## External Links

These are links to external documentation and tutorials; both first- and third-party.  Note that these may be incomplete, obsolete, or otherwise inaccurate.

