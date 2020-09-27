This file is, strictly speaking, an internal YSI library, which is why it is found under `YSI_Internal`.  However, as with several internal libraries, it has become slowly more generally useful, to the point where others may be able to use the API with no issues.  It handles several things:

1. Setting as many compiler options as possible for YSI to build.
2. Determining information about the compiler.
3. Attempting to fix certain compiler bugs.  These are often fixed in updated compilers, but YSI builds on the old and new compilers, so sadly sometimes still needs work-arounds.

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

## Compiler Pass

The PAWN compiler makes two passes over the code.  The first pass builds a list of all the functions that exist, and the second pass builds the code with this information.  This is why code using `#if defined Hooked_OnGameModeInit` works, even when that function is later in the code.  We can use this future knowledge to work out which pass the compiler is in and define symbols based on that:

```pawn
// 0 for first pass, 1 for second.
__COMPILER_PASS

// 1 for first pass, 0 for second.
__COMPILER_1ST_PASS

// 0 for first pass, 1 for second.
__COMPILER_2ND_PASS

// Same as above.
__COMPILER_FIRST_PASS
__COMPILER_SECOND_PASS
```

YSI also has the `P:D` macro, which only outputs code in the first pass (used for generating `#define` documentation with `-r`.  Thus:

```pawn
// 1 for first pass, 0 for second.  Used to indicate
// if the documented code is generated or not this pass.
__COMPILER_DOCUMENTING
```

## Compiler Information

The main use of y_compilerdata is to provide information about what the current version of the compiler can do, and is doing:

```pawn
// Always 0.
__COMPILER_UNIX

// Always 1
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

// 1 when `#warning` exists, 0 when is doesn't.
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

// Default value for any tag type.
__COMPILER_DEFAULT
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
