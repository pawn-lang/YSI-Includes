This file is, strictly speaking, an internal YSI library, which is why it is found under `YSI_Internal`.  However, as with several internal libraries, it has become slowly more generally useful, to the point where others may be able to use the API with no issues.  It handles several things:

1. Setting as many compiler options as possible for YSI to build.
2. Determining information about the compiler.
3. Attempting to fix certain compiler bugs.  These are often fixed in updated compilers, but YSI builds on the old and new compilers, so sadly sometimes still needs work-arounds.

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

As a general rule, just use `#if __COMPILER_1ST_PASS` and `#if !__COMPILER_1ST_PASS`, because passes 2 and 3 should be treated basically the same.  I debated how to expose them, and if `2ND` should be true in the third pass as well.  YSI also has the `P:D` macro, which only outputs code in the first pass (used for generating `#define` documentation with `-r`.  Thus there are two more macros which can be used to determine the *use* of the current pass, rather than the absolute number:

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

## `THIS__`

`THIS__` allows you to use a limited form of OO-like syntax, based on the variable `this`.  You need to define `this` at the top of a file, then undefine it at the end using `THIS__`:

```pawn
// Top.
#define this. THIS__(Entity)

// Code.
Float:SomeFunction(Entity:this)
{
	return this.GetAngle();
}

// End.
#undef this
```

Becomes:

```pawn
// Code.
Float:SomeFunction(Entity:this)
{
	return Entity_GetAngle(this);
}
```

`this` must have the tag specified in `THIS__`.

While normally there are YSI keywords so you can enable `this` as a short form of `THIS__`, you can't here because `this` is used as the variable operated on.  However, since `THIS__` only really appears once per file it is less in need of shortening.

There is currently no support for varaibles like `this.Data[ANGLE]`, but I'm thinking about how to achieve it.

