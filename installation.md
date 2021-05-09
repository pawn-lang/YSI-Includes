# Installation

Use sampctl!

## With *sampctl*

```
sampctl package install pawn-lang/YSI-Includes@5.x
```

## Without *sampctl*

Download the latest version of the library and its dependencies from the following links:



Extract the *YSI* zip to `pawno/includes/`, the *amx_assembly* zip to `pawno/includes/amx`, the
*md-sort* zip to `pawno/includes/md-sort`, the *indirection* zip to `pawno/includes/indirection`,
and the *code-parse* zip to `pawno/includes/code-parse`.

## Compile-Time Options

YSI shows a lot of information when it starts up.  You can disable a lot of this with the following
defines:

```pawn
// Don't display the message about caching the code (with `YSI_YES_MODE_CACHE`).
#define YSI_NO_CACHE_MESSAGE

// Don't display the message about startup optimisation (it still happens, you just aren't told).
#define YSI_NO_OPTIMISATION_MESSAGE

// Don't check if this is the latest version of YSI.
#define YSI_NO_VERSION_CHECK


#include <YSI_Group\y_library>
```

## Caching

If the mode is too slow to start you can *cache* it.  This pre-optimises a lot of the mode, then
saves the result to `scriptfiles/YSI_CACHE.amx`.  This allows you to do the slow startup once, then
deploy the fast version to your server.

