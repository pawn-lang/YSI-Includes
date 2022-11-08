# Quick Start

This library provides *lambda* functions, i.e. short functions inside expressions, plus a number of
functions that accept these functions and use them to perform basic operations.

```pawn
// Include y_functional.
#include <YSI_Coding\y_functional>

main()
{
	// This array will be mutated.
	new array[10] = {0, 1, 2, ...};

	// `Map` does the same thing to every element in an array.
	// `{...}` here is a lambda function, `_0` is an implicit argument, a single
	// value within the array.
	Map({_0 + 1}, array, array);

	// This is equivalent to:
	//
	//     for (new i = 0; i != sizeof (array); ++i)
	//     {
	//         new _0 = array[i];
	//         array[i] = _0 + 1;
	//     }
	//
}
```

