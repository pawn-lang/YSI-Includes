This file is, strictly speaking, an internal YSI library, which is why it is found under `YSI_Internal`.  However, as with several internal libraries, it has become slowly more generally useful, to the point where others may be able to use the API with no issues.  It handles several things:

1. Setting as many compiler options as possible for YSI to build.
2. Determining information about the compiler.
3. Attempting to fix certain compiler bugs.  These are often fixed in updated compilers, but YSI builds on the old and new compilers, so sadly sometimes still needs work-arounds.

## `cellbytes`

By default the compiler defines `cellbits`, which is the number of bits in a cell (normally thirty-two); however, the number of bytes in a cell (four) is very frequently needed (in my anecdotal experience it is vastly more common).  Thus YSI, amx_assembly, and several other libraries (even the open.mp official includes) all define this constant:

```pawn
#if !defined cellbytes
	const cellbytes = cellbits / charbits;
#endif
```

Now the chance of `charbits` ever being anything other than eight is basically 0%, but it is still used anyway.  Because of bugs with compiler documentation comments the version in YSI is:

```pawn
/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   The number of bytes in a cell.  There is the number of bits as a constant
 *   built-in, but not the number of bytes.
 * </remarks>
 */
#if defined cellbytes
	static stock YSI_cellbytes__ = 0;
#else
	const cellbytes = cellbits / charbits;
#endif
```

But that's functionally equivalent.

## String Returns

The original compiler has a code generation bug returning strings (actually arrays) from functions with variable arguments, i.e. this won't work correctly:

```pawn
Func(a, b, ...)
{
	new ret[32] = "hello";
	return ret;
}
```

The generated code assumes there are only the fixed parameters (two in this example), which is bad as array returns are done via a hidden last parameter.  This include provides a fix, which calls a function to do the correct operation on the original compiler, and is just `return` on the fixed compiler:

```pawn
Func(a, b, ...)
{
	new ret[32] = "hello";
	__COMPILER_STRING_RETURN(ret);
}
```

This could be extended to fix nested returns.  It is also aliased as the more correct `__COMPILER_ARRAY_RETURN`.

## Compiler Options

The library makes the following changes to the default build options:

```pawn
// Certain parts of YSI require `-;+`.
#pragma semicolon 1

// They also require `-(+`.
#pragma option -(+

// Always.
#pragma tabsize 4

// This line actually breaks `#pragma tabsize 0`, so code with it won't compile.
#define tabsize%00%0\10;%0 _DUMMY_do_not_use_tabsize_0

// Some compiler branches treat recursion as a mistake - it isn't, so disable that.
#pragma disablerecursion
```

All these options are buried in various `#if` statements to only apply where nescessary, and when the options even exist.

## Codepage

This code can detect the compiler being run with certain codepage settings.  However, this list is far from exhaustive and there may be some collisions between the supported codepages and untested codepages.  Most codepages can be detected, but each one needs unique code and so if you want a codepage adding please ask.  The value is stored in `__COMPILER_CODEPAGE`.

The current list of detected codepages are:

* `0` - None.  No option set.
* `-1` - Unknown.  A codepage was selected, but that one isn't detected yet.
* `874` – Windows Thai.
* `1250` – Windows Central Europe.
* `1251` – Windows Cyrillic.
* `1252` – Windows Western.
* `1253` – Windows Greek.
* `1254` – Windows Turkish.
* `1255` – Windows Hebrew.
* `1256` – Windows Arabic.
* `1257` – Windows Baltic.
* `1258` – Windows Vietnamese*.
* `932` - Japanese Shift-JIS.
* `936` - Simplified Chinese GBK.
* `949` - Korean Unified Hangul Code.
* `950` - Traditional Chinese Big5.
* `855` - Cyrillic.
* `872` - Cyrillic with Euro symbol.
* `708` – Arabic (ASMO 708).
* `720` – Arabic (Transparent ASMO).
* `737` – Greek.
* `775` = Latin-7.
* `850` – Latin-1.
* `852` – Latin-2.
* `855` – Cyrillic.
* `857` – Latin-5.
* `858` – Latin-1 with euro symbol.
* `860` – Portuguese.
* `861` – Icelandic.
* `862` – Hebrew.
* `863` – Canadian French.
* `864` – Arabic.
* `865` – Danish/Norwegian.
* `866` – Belarusian, Russian, Ukrainian.
* `869` – Greek.

\* This codepage probably won't compile due to its DBCS characters, but you can try.

Detecting a compiler codepage option (either `-c` or `#pragma codepage`) can be done by just testing that `__COMPILER_CODEPAGE` is non-zero.


## Compiler Pass

The PAWN compiler makes two or three passes over the code.  The first pass builds a list of all the functions that exist, and the second pass builds the code with this information - this is why code using `#if defined Hooked_OnGameModeInit` works, even when that function is later in the code.  The third pass is an emergency pass to correctly generate tag returns code without `forward` and gives a warning.  We can use this future knowledge to work out which pass the compiler is in and define symbols based on that:

```pawn
// 0 for first pass, 1 for second, 2 for third.
__COMPILER_PASS

// 1 for first pass, 0 for second, 0 for third.
__COMPILER_1ST_PASS

// 0 for first pass, 1 for second, 0 for third.
__COMPILER_2ND_PASS

// 0 for first pass, 0 for second, 1 for third.
__COMPILER_3RD_PASS

// Same as above.
__COMPILER_FIRST_PASS
__COMPILER_SECOND_PASS
__COMPILER_THIRD_PASS
```

As a general rule, just use `#if __COMPILER_1ST_PASS` and `#if !__COMPILER_1ST_PASS`, because passes 2 and 3 should be treated basically the same.  I debated how to expose them, and if `2ND` should be true in the third pass as well.  YSI also has the `FUNC_PAWNDOC` macro, which only outputs code in the first pass (used for generating `#define` documentation with `-r`.  Thus there are two more macros which can be used to determine the *use* of the current pass, rather than the absolute number:

```pawn
// 1 for first pass, 0 for second and third.  Used to indicate if the documented
// code is generated or not this pass.
__COMPILER_DOCUMENTING

// 0 for first pass, 1 for second and third.  Used to indicate if the compiled
// output is generated in this pass.
__COMPILER_GENERATING
```

## Compiler Information

The main use of y_compilerdata is to provide information about what the current version of the compiler can do, and is doing:

```pawn
// Always 0.
__COMPILER_UNIX

// Always 1.
__COMPILER_WINDOWS

// 0 or 1 depending on which OS is being used to COMPILE the code
// (not run the code).  The value corresponds to the macros above.
__COMPILER_OS

// 0 when using the default compiler, 1 otherwise.
__COMPILER_MODIFIED

// 1 when using the default compiler, 0 otherwise.
__COMPILER_OFFICIAL

// 1 when compiling with `-Z`, 0 otherwise (including on the old compiler).
__COMPILER_COMPAT

// 1 when include guards are in use (including on the old compiler), 0 otherwise.
__COMPILER_INCLUDE_GUARDS

// A placeholder to use instead of `return 0;`
// when a naked function doesn't need a return.
__COMPILER_NAKED

// `static enum` when that's allowed, `enum` otherwise.
__COMPILER_STATIC_ENUM

// `const static` when that's allowed, `const` otherwise.
__COMPILER_CONST_STATIC

// 1 when `{ {}, ... }` is allowed, 0 otherwise.
__COMPILER_NESTED_ELLIPSIS

// Correctly returns strings from vararg functions on all
// compilers.  Just a normal return when there's no bug.
__COMPILER_STRING_RETURN(str)

// 1 when the fix above runs extra code, 0 otherwise.
__COMPILER_BUGGED_STRING_RETURN

// 1 when you can't call `SYSREQ.C` on unused natives, 0 otherwise.
__COMPILER_BUGGED_SYSREQ

// 1 when `#pragma warning` exists, 0 when it doesn't.
__COMPILER_WARNING_SUPPRESSION

// 1 when `#warning` exists, 0 when it doesn't.
__COMPILER_USER_WARNING

// 1 when `const &` is a warning, 0 when is isn't.
__COMPILER_CONST_REF

// Size of the internal `sNAMEMAX` compiler define for max symbol length.  Default 31.
__COMPILER_sNAMEMAX

// Does this compiler suffer from issue #317?
__COMPILER_BUG_317

// Does this compiler have native `__nameof`?
__COMPILER_NAMEOF

// Does this compiler have native `__pragma`?
__COMPILER_PRAGMA

// Does this compiler have native `__emit`?
__COMPILER___EMIT

// Does this compiler have native `#pragma option`?
__COMPILER_OPTION

// Default value for any tag type.
__COMPILER_DEFAULT

// The value of `#pragma pack` so `0` (default) or `1` (default pack strings).
__COMPILER_STRING_PACKING

// The suffix to always pack strings, regardless of compiler settings.
// Example: `new string[] = __COMPILER_PACK"This is always packed.";
__COMPILER_PACK

// The suffix to always unpack strings, regardless of compiler settings.
// Example: `new string[] = __COMPILER_UKPACK"This is always unpacked.";
__COMPILER_UKPACK

// Are semi-colons required?  `1 = -;+`, `0 = -;-` (`0` also gives an error).
__COMPILER_SEMICOLON

// One of a limited number of codepages that the compiler might be using.
__COMPILER_CODEPAGE

// The compiler has native support for the AMXModX `decl` keyword.
__COMPILER_DECL

// The compiler has native support for #234 (i.e. `obj.Method()` syntax).
__COMPILER_THIS

// The script is being compiled with `-O2` on later versions.
__COMPILER_O2

// The compiler has native `__addressof` support.
__COMPILER_ADDRESSOF

// The optimisation level used by the compiler, on some versions.  `-1` if unknown.
__optimisation

// The `debug` constant, but with a better name.
__debug
```

## Default Values

When you declare a new variable it is by default `0`, even if that default doesn't make sense.  y_compilerdata adds a method to define defaults for any tag type.  Most tags are already defined, but you can add a new one with:

```pawn
// Set the default value for `Tag:` to `44`.
__COMPILER_TAG_DATA(Tag, 44);
```

For example, the following is already defined:

```pawn
__COMPILER_TAG_DATA(PlayerText3D, 65535);
```

To use this, assign from `__COMPILER_DEFAULT` (or `default()` with `YSI_KEYWORD_default`, enabled by default):

```pawn
new PlayerText3D:var = default();
```

This also works for returns and macros, so you can set a sane initial value without even knowing the tag. 

## Pragma

The default compiler has `#pragma`, the updated compiler adds `__pragma` for inline/macro pragma uses.  This include polyfills a couple of uses of it:

```pawn
// Disable the warning for unused local variables only.
__pragma("unused", var);

// Same as `__COMPILER_NAKED`.
__pragma("naked");
```

## `DECL__`

`DECL__` (or `decl` if the keyword is optionally enabled with `YSI_KEYWORD_decl` as is the default) can be used to declare variables without initialising them.  Their contents are rubbish ("garbage"[sic]).  This is somewhat useful for large arrays that will just be passed straight to other functions to be initialised, so the default naught initialisation is never needed:

```pawn
main()
{
	decl a, Float:b, c[32];
	printf("%d %f %s", a, b, c); // Prints rubbish.
}
```

Note that you can have multiple variables, including tags and arrays, in the `decl` declaration, but they must all be on the same line.  This will not work:

```pawn
main()
{
	// Many errors.
	DECL__
		a,
		Float:b,
		c[32];
	printf("%d %f %s", a, b, c);
}
```

Example:

```pawn
PrintPlayerData(playerid)
{
	decl name[MAX_PLAYER_NAME + 1], Float:health;
	GetPlayerName(playerid, name, sizeof (name));
	GetPlayerHealth(playerid, health);
	printf("name: %s, health: %f", name, health);
}
```

`name` and `health` are both initialised by function calls so there's no need to initialise them to something else first, hence using `decl` doesn't.

## `THIS__`

`THIS__` allows you to use a limited form of OO-like syntax, based on the variable `this`.  You need to define `this` at the top of a file using `THIS__`, then undefine it at the end:

```pawn
// Top.
#define this. THIS__(Entity)

// Code.
Float:this.SomeFunction()
{
	return this.GetAngle();
}

// End.
#undef this
```

Becomes:

```pawn
// Code.
Float:Entity_SomeFunction(Entity:this__)
{
	return Entity_GetAngle(this__);
}
```

You could, if you really really really want to do:

```pawn
// Top.
#define this. THIS__(Entity)
#define Entity:: THIS__(Entity)

// Code.
Float:Entity::SomeFunction()
{
	return this.GetAngle();
}

// End.
#undef this
```

However, people can't call the function using the `::` syntax, it only works here for declarations.  Thus it is instead likely more worth using explicit declarations with `this__`:

```pawn
// Top.
#define this. THIS__(Entity)

// Code.
Float:Entity_SomeFunction(Entity:this__)
{
	return this.GetAngle();
}

// End.
#undef this
```

And only use `this.` and `::` internally.

While normally there are YSI keywords so you can enable `this` as a short form of `THIS__`, you can't here because `this` is used as the variable operated on.  However, since `THIS__` only really appears once per file it is less in need of shortening.

There is currently no support for varaibles like `this.Data[ANGLE]`, but I'm thinking about how to achieve it.

## `__COMPILER_NAMED.`

Use to half replicate https://github.com/pawn-lang/compiler/issues/719, or at least indicate the intention to have parameters only used by their name:

```pawn
Function(__COMPILER_NAMED.arg = 5)
{
}
```

## String Packing

Under normal compiler settings strings are declared with `""` and packed strings with `!""`.  However, there's a setting to invert this - `#pragma pack`:

```pawn
#pragma pack 1
new str[] = "This string is unpacked.";
// `str` ends up as twenty-five cells big.
```

```pawn
#pragma pack 0
new str[] = "This string is packed.";
// `str` ends up as six cells big.
```

As you can also specify the default string packing behaviour on the command line it becomes almost impossible to know in code whether a string will be packed or not:

```pawn
new str[] = "This string may or may not be packed.";
// `str` ends up as ten or thirty-eight cells big.
```

*y_compilerdata* provide some facilities to write more controlled code, so you know that a string will be always packed or unpacked.  The following code always packs the string, regardless of compiler settings:

```pawn
new str[] = __COMPILER_PACK"This string is packed.";
// `str` ends up as six cells big.
```

Similarly we can always ensure that a string is always unpacked with:

```pawn
new str[] = __COMPILER_UNPACK"This string is unpacked.";
// `str` ends up as twenty-five cells big.
```

The test macro `__COMPILER_STRING_PACKING` has the value set by `#pragma pack`, so can be used to see which mode is in use.  In SA:MP this was mostly useless, but is more important now with open.mp fully supporting packed strings.

`__COMPILER_PACK` and `__COMPILER_UNPACK` form a pair of macros, with other macros provided for use with the default facilities (i.e. `!`).

## Prefixed And Basic Strings

Because `!""` and `""` may be packed or unpacked strings, depending on the value of `#pragma pack`, some new terminology has been introduced - prefix and basic strings.  `!""` is a prefix string, because it has a prefix of `!` (there's also the possible prefix of `\`, but that already has a name - a raw string).  `""` is a basic string because it doesn't have a prefix (again, it could have `\`, which would be a raw basic string).  A prefix string may be packed or unpacked, but for simplicity it is always prefixed.

`__COMPILER_PREFIX_CHARSOF` and `__COMPILER_BASIC_CHARSOF` count the number of characters (including `NULL`) in strings using `!""` and `""` respectively.  Although `!""` might be used for unpacked strings with `#pragma pack 0` the correct macro to use is still `__COMPILER_PREFIX_CHARSOF` because `!` was used, and vice-versa.  `__COMPILER_PREFIX_CHAR` and `__COMPILER_BASIC_CHAR` can then be used in place of `char` to declare an array large enough to hold that many prefix (`!""`) and basic (`""`) characters in an array (again including `NULL`):

```pawn
new input[] = !"This is packed by default.";

new copy[__COMPILER_PREFIX_CHARSOF(input) __COMPILER_BASIC_CHAR];
```

That code will count how many characters (including `NULL`) there are in the prefix string (via `__COMPILER_PREFIX_CHARSOF`), then declare an array large enough to hold that many characters in a basic array (using `__COMPILER_BASIC_CHAR`).  `__COMPILER_PREFIX_CHARSOF(input)` is always `27`, regardless of the value of `#pragma pack`, because there are that many characters (including `NULL`) in the string; they may be packed or unpacked, it doesn't matter.  With default settings `__COMPILER_BASIC_CHAR` will thus do nothing and declare this array to be `27` cells large, enough to hold all the input characters one per cell.  When default packing is enabled (`#pragma pack 0`) `__COMPILER_PREFIX_CHARSOF(input)` is still `27` because it is always `27`, but `__COMPILER_BASIC_CHAR` is now the same as `char` and thus declares `copy` as seven cells long, enough to store the whole string packed.

This example will declare two arrays of exactly the right size and pack or unpack the data from one to the other depending on compiler settings:

```pawn
new input[] = "This string is packed or unpacked.";

new output[__COMPILER_BASIC_CHARSOF(input) __COMPILER_PREFIX_CHAR];

#if __COMPILER_STRING_PACKING
	// Basic strings are packed, so unpack the input.
	strunpack(output, input);
#else
	// Basic strings are unpacked, so pack the input.
	strpack(output, input);
#endif
```

Note that there's no YSI equivalent for explicitly packed and unpacked strings because `char` and nothing are that.

You can use a combination of techniques to for example always unpack a string from an unknown start point:

```pawn
new input[] = !"unknown string";
new output[__COMPILER_PREFIX_CHARSOF(input)];
strunpack(output, input);
```

Here `input` may be packed or unpacked, we don't know.  `[__COMPILER_PREFIX_CHARSOF(input)]` declares an array with as many cells as there are characters in the input; no `char` suffix is used here so it is always cells.  `strunpack` checks if the input is packed or not before retreiving the data, so regardless of the packing of the input the output will be correctly unpacked in to a sufficiently large array.  The reason that plain `sizeof (input)` can't be used here is that the output array will be too small when `input` is packed; and while `sizeof (input) * cellbytes` will always make the output array large enough it may waste 75% of the space when the input is unpacked.

## Packed And Prefixed Strings

Just to clarify the last two sections...

There are two types of strings in question here - those that are packed (i.e. four characters per cell) and those that start with `!`.  Normally these are the same thing, this is the declaration of a packed string:

```pawn
new storage[12 char] = !"Hello World";
```

*However*, if you change compiler settings the meaning of `!` is swapped and that code errors; `!` no longer declares a packed string but an unpacked string (i.e. one character per cell) and thus the `storage` variable is too small (since it can only hold twelve bytes, not twelve characters).

So the facilities provided by *y_compilerdata* allow you to solve this problem in two ways.  Either you use `char` and ensure that the string is always packed, or you use `!` and ensure that the variable is declared correctly for strings using the prefix:

```pawn
new packedStorage[12 char] = __COMPILER_PACK"Hello World";

new prefixedStorage[12 __COMPILER_PREFIX_CHAR] = !"Hello World";
```

The first variable (`packedStorage`) will always take up exactly twelve bytes, and the string will always be packed regardless of compiler settings.  On the other hand the second variable (`prefixedStorage`) will always use the least space required to store the string, but the string may or may not be packed.

Just for completion's sake, the opposites are also possible:

```pawn
new unpackedStorage[12] = __COMPILER_UNPACK"Hello World";

new basicStorage[12 __COMPILER_BASIC_CHAR] = "Hello World";
```

