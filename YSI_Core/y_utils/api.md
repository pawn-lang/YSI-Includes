# Constants

* `Float:FLOAT_INFINITY`: IEEE754 Infinity
* `Float:FLOAT_NEG_INFINITY`: IEEE754 -Infinity
* `Float:FLOAT_NEGATIVE_INFINITY`: IEEE754 -Infinity
* `Float:FLOAT_NAN`: IEEE754 Not A Number
* `Float:FLOAT_NOT_A_NUMBER`: IEEE754 Not A Number
* `Float:FLOAT_QNAN`: IEEE754 Not A Number (quiet)
* `Float:FLOAT_QUIET_NAN`: IEEE754 Not A Number (quiet)
* `Float:FLOAT_QUIET_NOT_A_NUMBER`: IEEE754 Not A Number (quiet)
* `Float:FLOAT_SNAN`: IEEE754 Not A Number (signalling)
* `Float:FLOAT_SIGNALING_NAN`: IEEE754 Not A Number (signalling)
* `Float:FLOAT_SIGNALING_NOT_A_NUMBER`: IEEE754 Not A Number (signalling)
* `Float:FLOAT_E`: e
* `Float:FLOAT_PI`: pi
* `Float:FLOAT_ROOT_2`: sqrt(2)

# Macros

## `NO_VALUE(%0)`

* **Parameters:**
    * `%0`: Another macro to test if is empty.
* **Returns:**
    * `true`: The macro has no value.
    * `false`: The macro has a defined value (including `0`).
* **Remarks:**
Differentiates between:

```pawn
#define MY_MACRO_A
NO_VALUE(MY_MACRO_A) // true
```

And:

```pawn
#define MY_MACRO_B 0
NO_VALUE(MY_MACRO_B) // false
```

## `__once`

* **Remarks:**
Use to only run a loop once.  Useful for scoping variables:

```pawn
for (new i = 0; __once; )
{
	// This loop happens once.
}
```

Can be combined with other conditions:

```pawn
for (new i = 0; __once && SomeCheck(); )
{
	// This loop happens maybe once.
}
```

This is seemingly the same as `if (SomeCheck())`, but useful mainly in macros.

# Functions

## `stock GetIP(playerid);`

* **Parameters:**
    * `playerid`: Player to get IP of.
* **Returns:**
    * IP as a 32bit int.


## `stock bool:UCMP(value, upper);`

* **Parameters:**
    * `value`: The unsigned number to compare.
    * `upper`: The upper limit.
* **Returns:**
    * An unsigned comparison between the two values.


## `stock bool:IsNaN(Float:value);`

* **Parameters:**
    * `value`: The IEEE754 floating point number (`Float:`) to check.
* **Returns:**
    * An IEEE754 floating-point number is defined as Not-A-Number when all the exponent bits are set, and the mantissa is non-zero.  The sign bit is ignored, so we first remove that and test the result is `> 0x7F800000`.  Because any signed number bigger than that must have all the MSBs set, plus at least one more.


## `stock bool:VALID_PLAYERID(playerid);`

* **Parameters:**
    * `playerid`: The player to check.
* **Returns:**
    * Is this a valid playerid (NOT, is the player connected).


## `stock bool:IS_IN_RANGE(value, lower, upper);`

* **Parameters:**
    * `value`: The number to compare.
    * `lower`: The lower limit.
    * `upper`: The upper limit.
* **Returns:**
    * Is the value in the given range.
* **Remarks:**
Equivalent to:

```pawn
(%1) <= (%0) < (%2)
```

 


## `stock bool:NOT_IN_RANGE(value, lower, upper);`

* **Parameters:**
    * `value`: The number to compare.
    * `lower`: The lower limit.
    * `upper`: The upper limit.
* **Returns:**
    * Is the value outside the given range.
* **Remarks:**
Equivalent to:

```pawn
(%1) <= (%0) < (%2)
```

 


## `stock ceildiv(numerator, denominator);`

* **Parameters:**
    * `numerator`: The top of the division.
    * `denominator`: The bottom of the division.
* **Returns:**
    * (numerator / denominator) rounded up.
* **Remarks:**
Normal integer division ALWAYS rounds down - this always rounds up.
 


## `stock floordiv(numerator, denominator);`

* **Parameters:**
    * `numerator`: The top of the division.
    * `denominator`: The bottom of the division.
* **Returns:**
    * (numerator / denominator) rounded down.
* **Remarks:**
Normal integer division ALWAYS rounds down - this also always rounds down,
making it a little pointless, but also more explicit in function.
 


## `stock bool:isnull(str[]);`

* **Parameters:**
    * `str`: String to check if is null.
* **Remarks:**
Uses a new shorter and branchless method, which also works with offsets so
this is valid:

```pawn

new str[32];
isnull(str[5]);
  
```
 


## `stock bool:isodd(value);`

* **Remarks:**
Check if the value is odd.


## `stock bool:iseven(value);`

* **Remarks:**
Check if the value is even.


## `stock strcpy(dest[], const src[], len = sizeof (dest));`

* **Remarks:**
Copy a string from `src` to `dest`.


## `stock StrToLower(str[], len = sizeof (str));`

* **Remarks:**
Convert a string to lower-case.


## `stock StrToUpper(str[], len = sizeof (str));`

* **Remarks:**
Convert a string to upper-case.


## `stock Random(min, max = cellmin);`

* **Parameters:**
    * `minmax`: Lower bound, or upper bound when only parameter.
    * `max`: Upper bound.
* **Remarks:**
Generate a random float between the given numbers (`min <= n < max`).
Default minimum is `0` (changes the parameter order).
 


## `stock Float:RandomFloat(Float:min, Float:max = FLOAT_NAN, dp = 2);`

* **Parameters:**
    * `minmax`: Lower bound, or upper bound when only parameter.
    * `max`: Upper bound.
    * `dp`: How small to make the differences
* **Remarks:**
Generate a random float between the given numbers (`min <= n < max`).  Default
minimum is `0.0` (changes the parameter order).
 


## `stock StripNL(str[]);`

* **Remarks:**
Remove whitespace from the end of a string.


## `stock StripR(str[]);`

* **Remarks:**
Remove whitespace from the end of a string.


## `stock StripL(str[]);`

* **Remarks:**
Remove whitespace from the start of a string.


## `stock Strip(str[]);`

* **Remarks:**
Remove whitespace from the start and end of a string.


## `stock endofline(const line[], pos);`

* **Parameters:**
    * `line`: String to check.
    * `pos`: Postion to start from.
* **Remarks:**
Checks if the current point in a line is the end of non-whitespace data.
 


## `stock chrfind(needle, const haystack[], start = 0);`

* **Parameters:**
    * `needle`: The character to find.
    * `haystack`: The string to find it in.
    * `start`: The offset to start from.
* **Returns:**
    * `-1`: Fail
	* `pos`: Success


## `stock chrfindp(needle, const haystack[], start = 0);`

* **Parameters:**
    * `needle`: The character to find.
    * `haystack`: The string to find it in.
    * `start`: The offset to start from.
* **Returns:**
    * `-1`: Fail
	* `pos`: Success
* **Remarks:**
Like `chrfind`, but with no upper-bounds check on `start`.
 


## `stock IPToInt(const ip[]);`

* **Remarks:**
Convert a dot notation IP string to to an integer.


## `stock BernsteinHash(const string[] /* 12 */);`

* **Parameters:**
    * `string`: the string to hash.
* **Returns:**
    * the bernstein hash of the input string
* **Remarks:**
This is a 32bit hash system so is not very secure, however we're only
using this as a string enumerator to uniquely identify strings easilly
and allow for a binary search of strings based on the hash of their name.
crc32, then jenkins were originally used however this is far faster, if a
little collision prone, but we're checking the strings manually anyway.
This doesn't matter as it would be done regardless of hash method, so this
doesn't need to be accounted for.  Speed is all that matters with at 
least a bit of non collision (the number of strings we're dealing with,
this should have none-few collisions).

I modified it slightly from the original code pasted by aru, to code
closer to the code http://www.burtleburtle.net/bob/hash/doobs.html
and to work with PAWN (and shaved 0.2us off the time for one call :D).

Uber reduced version (just for fun):

```pawn
b(s[]){new h=-1,i,j;while((j=s[i++]))h=h*33+j;return h;}
```

Update: Contrary to what I said above this is also used to identify colour
strings for the updated text system involving file based styling and this
is not checked for collisions as it's unimportant.  But this doesn't affect
the function at all, I just mentioned it here for "interest".
 


## `stock JenkinsHash(const string[] /* 12 */);`

* **Parameters:**
    * `string`: the string to hash.
* **Returns:**
    * the Jenkins hash of the input string
* **Remarks:**
This is a 32bit hash system so is not very secure, however we're only
using this as a string enumerator to uniquely identify strings easilly
and allow for a binary search of strings based on the hash of their name.
 


## `stock ishex(const str[]);`

* **Remarks:**
Check if a string looks like a hex number.
 


## `stock unpack(const str[]);`

* **Parameters:**
    * `str`: String to unpack
* **Returns:**
    * unpacked string
* **Remarks:**
Mainly used for debugging.
 


## `stock getstringarg(idx);`

* **Parameters:**
    * `idx`: Index of the string in the parameters.
* **Returns:**
    * string
* **Remarks:**
Is passed the result of getarg, which will be the address of a string (in
theory) and uses that for DMA to get the string.
 


## `stock va_return(const fmat[], GLOBAL_TAG_TYPES:...);`

* **Parameters:**
    * `fmat`: String format.
    * ``: Parameters.
* **Returns:**
    * Formatted string.
* **Remarks:**
Just wraps `format` and returns a string instead.

Has extra code to ensure that it works correct on the old compiler.
 


## `stock isnumeric(const str[]);`

* **Parameters:**
    * `str`: String to check
* **Remarks:**
Checks if a given string is numeric.
 


## `stock hexstr(const string[]);`


* **Parameters:**
    * `string`: String to convert to a number.
* **Returns:**
    * value of the passed hex string.
* **Remarks:**
Convert a hex string to a number.  Now stops on invalid characters.
 


## `stock bool:boolstr(const string[]);`


* **Parameters:**
    * `string`: String to try convert to a boolean.
* **Returns:**
    * bool: passed boolean.
* **Remarks:**
This can take a number of ways of representing booleans - 0, false and
nothing there.  Anything not one of those things (false is not case
sensitive) is assumed true.



## `stock binstr(const string[]);`


* **Parameters:**
    * `string`: String to try convert to a boolean.
* **Returns:**
    * bool: passed boolean.
* **Remarks:**
This takes a value in `0110101` (boolean) format and returns it as a
regular value.
 


## `stock Base64Encode(dest[], const src[], num = sizeof (src), len = sizeof (dest), offset = 0);`

* **Remarks:**
Encodes data using proper base64.  This code is complicated by the fact that
PAWN packed strings are backwards by cells in memory, so we need to do the
writes in what seems like a strange order.
 


## `stock Base64Decode(dest[], const src[], len = sizeof (dest), offset = 0);`

* **Remarks:**
Decodes data using proper base64.
 


## `stock rawMemcpy_(dest, src, index, numbytes, maxlength);`

* **Parameters:**
    * `dest`: Destination address.
    * `src`: Source data.
    * `numbytes`: Number of bytes to copy.
* **Remarks:**
Like memcpy, but takes addresses instead of arrays.  Also far less secure
because it doesn't check the destination size - it just assumes it is large
enough.
 
## `stock memset(arr[], val = 0, size = sizeof (arr));`

* **Parameters:**
    * `arr`: Array or address to set to a value.
    * `iValue`: What to set the cells to.
    * `iSize`: Number of cells to fill.
* **Remarks:**
Based on code by Slice:

http://forum.sa-mp.com/showthread.php?p=1606781#post1606781

Modified to use binary flags instead of a loop.

`memset` takes an array, the size of the array, and a value to fill it with
and sets the whole array to that value.

`rawmemset` is similar, but takes an AMX data segment address instead and
the size is in bytes, not cells.  However, the size must still be a multiple
of 4.
 


## `stock rawMemset(iAddress /* 12 */, iValue /* 16 */, iSize /* 20 */);`

* **Parameters:**
    * `iAddress`: Array or address to set to a value.
    * `iValue`: What to set the cells to.
    * `iSize`: Number of cells to fill.
* **Remarks:**
Based on code by Slice:

http://forum.sa-mp.com/showthread.php?p=1606781#post1606781

Modified to use binary flags instead of a loop.

`memset` takes an array, the size of the array, and a value to fill it with
and sets the whole array to that value.

`rawmemset` is similar, but takes an AMX data segment address instead and
the size is in bytes, not cells.  However, the size must still be a multiple
of 4.



## `stock ReturnPlayerName(playerid);`

* **Parameters:**
    * `playerid`: Player whose name you want to get.
* **Remarks:**
Now uses a global array to avoid repeated function calls.  Actually doesn't
because that causes issues with multiple scripts.
 


## `stock ftouch(const filename[]);`

* **Parameters:**
    * `filename`: The file to "touch".
* **Returns:**
    * `0`: File already exists.
    * `1`: File was created.
    * `-1`: File was not created.
* **Remarks:**
This "touches" a file in the Unix sense of creating it but not opening or
editing it in any way.
 


## `stock InterpolateColorLinear(startColour, endColour, Float:fraction);`

* **Parameters:**
    * `startColour`: One of the two colours.
    * `endColour`: The other of the two colours.
    * `fraction`: How far to interpolate between the colours.
* **Remarks:**
This function takes a value (fraction) which is a distance between the two
endpoints as a fraction.  This fraction is applied to the two colours given
to find a third colour at some point between those two colours.

This function performs linear interpolation between the colours, which isn't
usually the best way wrt human vision, but is fast.

The fraction is optional, and uses the second colour's alpha for blending
if not given.

## `stock InterpolateColourLinear(startColour, endColour, Float:fraction = FLOAT_NAN);`

* **Remarks:**
Alternate (deprecated) spelling of `InterpolateColourLinear`.
 


## `stock InterpolateColor(startColour, endColour, value, maxvalue, minvalue = 0);`

* **Remarks:**
Alternate (deprecated) spelling of `InterpolateColourLinear`.
 


## `stock InterpolateColour(startColour, endColour, value, maxvalue, minvalue = 0);`

* **Remarks:**
Alternate (deprecated) spelling of `InterpolateColourLinear`.
 


## `stock InterpolateColourGamma(startColour, endColour, Float:fraction = FLOAT_NAN);`

* **Parameters:**
    * `startColour`: One of the two colours.
    * `endColour`: The other of the two colours.
    * `fraction`: How far to interpolate between the colours.
* **Remarks:**
This function takes a value (fraction) which is a distance between the two
endpoints as a fraction.  This fraction is applied to the two colours given
to find a third colour at some point between those two colours.

This function performs gamma interpolation between the colours, which is a
good balance between complexity and perception.

The fraction is optional, and uses the second colour's alpha for blending
if not given.



## `stock InterpolateColorGamma(startColour, endColour, Float:fraction = FLOAT_NAN);`

* **Remarks:**
Alternate (deprecated) spelling of `InterpolateColourGamma`.
 


## `stock SRGBToCIE(colour, &Float:x, &Float:y, &Float:z);`

* **Parameters:**
    * `colour`: The sRGB colour to convert.
    * `x`: The x return value.
    * `y`: The y return value.
    * `z`: The z return value.
* **Remarks:**
Converts a colour from sRGB colour space to CIE XYZ colour space.  See:

https://en.wikipedia.org/wiki/SRGB#The_reverse_transformation_(sRGB_to_CIE_XYZ)




## `stock CIEToSRGB(a, Float:x, Float:y, Float:z);`

* **Parameters:**
    * `a`: The alpha to add on.
    * `x`: The x return value.
    * `y`: The y return value.
    * `z`: The z return value.
* **Remarks:**
Converts a colour from CIE XYZ colour space to sRGB colour space.  See:

https://en.wikipedia.org/wiki/SRGB#The_forward_transformation_(CIE_XYZ_to_sRGB)




## `stock InterpolateColourSRGB(startColour, endColour, Float:fraction = FLOAT_NAN);`

* **Parameters:**
    * `startColour`: One of the two colours.
    * `endColour`: The other of the two colours.
    * `fraction`: How far to interpolate between the colours.
* **Remarks:**
This function takes a value (fraction) which is a distance between the two
endpoints as a fraction.  This fraction is applied to the two colours given
to find a third colour at some point between those two colours.

This function performs full sRGB colour space interpolation, which is more
exact even than gamma interpolation, but also a lot slower.

The fraction is optional, and uses the second colour's alpha for blending
if not given.
 


## `stock InterpolateColorSRGB(startColour, endColour, Float:fraction = FLOAT_NAN);`

* **Remarks:**
  Alternate (deprecated) spelling of `InterpolateColourSRGB`.
 


## `stock GetNearestColourLinear(colour, const options[], count = sizeof (options));`

* **Parameters:**
    * `colour`: The RGB(A) colour to restrict.
    * `options`: The list of valid RGB(A) colour options.
    * `count`: The size of the options array.
* **Returns:**
    * The INDEX of the nearst colour.  Or `-1` for errors.
* **Remarks:**
Find the closest colour to the given colour from the array.  Uses RGB colour
space for the distance function, which is not very accurate.



## `stock GetNearestColourGamma(colour, const options[], count = sizeof (options));`

* **Parameters:**
    * `colour`: The RGB(A) colour to restrict.
    * `options`: The list of valid RGB(A) colour options.
    * `count`: The size of the options array.
* **Returns:**
    * The INDEX of the nearst colour.  Or `-1` for errors.
* **Remarks:**
Find the closest colour to the given colour from the array.  Uses gamma
colour space for slightly more accuracy.
 


## `stock GetNearestColourGammaCached(colour, const Float:options[][3], count = sizeof (options));`

* **Parameters:**
    * `colour`: The RGB(A) colour to restrict.
    * `options`: The list of valid gamma colour options.
    * `count`: The size of the options array.
* **Returns:**
    * The INDEX of the nearst colour.  Or `-1` for errors.
* **Remarks:**
Find the closest colour to the given colour from the array.  Uses gamma
colour space for slightly more accuracy.  Options are in gamma format.



## `stock GetNearestColourSRGB(colour, const options[], count = sizeof (options));`

* **Parameters:**
    * `colour`: The RGB(A) colour to restrict.
    * `options`: The list of valid RGB(A) colour options.
    * `count`: The size of the options array.
* **Returns:**
    * The INDEX of the nearst colour.  Or `-1` for errors.
* **Remarks:**
Find the closest colour to the given colour from the array.  Uses SRGB
colour space for the most accuracy.



## `stock GetNearestColourSRGBCached(colour, const Float:options[][3], count = sizeof (options));`

* **Parameters:**
    * `colour`: The RGB(A) colour to restrict.
    * `options`: The list of valid SRGB colour options.
    * `count`: The size of the options array.
* **Returns:**
    * The INDEX of the nearst colour.  Or `-1` for errors.
* **Remarks:**
Find the closest colour to the given colour from the array.  Uses SRGB
colour space for the most accuracy.  Options are in SRGB format.



## `stock SkipWhitespace(const str[], pos);`

* **Parameters:**
    * `str`: The string to skip over part of.
    * `pos`: The start of the whitespace.
* **Returns:**
    * The end of the whitespace.
* **Remarks:**
Doesn't skip over `NULL` terminators.
 


## `stock Trim(const str[], &start, &end);`

* **Parameters:**
    * `str`: The string to trim.
    * `start`: Start of the substring.
    * `end`: End of the substring.
* **Remarks:**
Modifies "start" and "end" to be tight on text in "str".  `Strip` removes
the characters from the end, so needs a modifiable string, this just tells
you where the ends are.
 


## `stock Sum(const arr[], num = sizeof (arr));`

* **Parameters:**
    * `arr`: The array whose values need summing.
    * `num`: The size of the array.
* **Returns:**
    * All the values in the array added together.


## `stock Mean(const arr[], num = sizeof (arr));`

* **Parameters:**
    * `arr`: The array whose values need averaging.
    * `num`: The size of the array.
* **Returns:**
    * The mathematical mean value of the array.


## `stock Mode(arr[], num = sizeof (arr));`

* **Parameters:**
    * `arr`: The array whose values need averaging.
    * `num`: The size of the array.
* **Returns:**
    * The mathematical modal value of the array.


## `stock Median(arr[], num = sizeof (arr));`

* **Parameters:**
    * `arr`: The array whose values need averaging.
    * `num`: The size of the array.
* **Returns:**
    * The mathematical median value of the array.


## `stock Range(const arr[], num = sizeof (arr));`

* **Parameters:**
    * `arr`: The array whose values need averaging.
    * `num`: The size of the array.
* **Returns:**
    * The mathematical range of the values of the array.


## `stock memcmp(arr1[], arr2[], count);`

* **Parameters:**
    * `arr1`: First array to compare.
    * `arr2`: Second array to compare.
    * `count`: How many cells to compare.
* **Returns:**
    * The difference (`0` if the same).


## `stock LevenshteinDistance(const a[], const b[]);`

* **Parameters:**
    * `a`: First string to compare.
    * `b`: Second string to compare.
* **Returns:**
    * The levenshtein difference (`0` if the same).


## `stock ValstrWithOrdinal(n);`

* **Parameters:**
    * `n`: The number to convert to a string with ordinal.
* **Returns:**
    * Stringises a number, then adds `st`/`nd`/`rd`/`th`.


## `stock PrintArg(n);`

* **Parameters:**
    * `n`: The numeric parameter position to print.
* **Returns:**
    * Prints a string passed as a vararg to the calling function.


## `stock File:ftemporary(name[], const ext[] = "tmp", len = sizeof (name), maxAge = YSI_TEMP_FILE_AGE);`

* **Parameters:**
    * `name`: Storage.
    * `ext`: Extension.
    * `len`: Maximum string length.
    * `maxAge`: Maximum temporary file age.
* **Remarks:**
Generate a random temporary filename and open it.  Also redefines `ftemp` to call this function instead if called with extra parameters.


## `stock Float:FloatAbs(Float:value);`

* **Parameters:**
    * `number`: The number to get the absolute value of.
* **Returns:**
    * The absolute value of a number.
* **Remarks:**
Get the absolute value of a number.  Easy in IEEE754, just remove the MSB.
 


## `stock Abs(number);`

* **Parameters:**
    * `number`: The number to get the absolute value of.
* **Returns:**
    * The absolute value of a number.
* **Remarks:**
Get the absolute value of a number.
 


