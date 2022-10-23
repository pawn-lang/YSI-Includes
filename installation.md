# Installation

Use sampctl!

## With *sampctl*

```
sampctl package install pawn-lang/YSI-Includes@5.x
```

## Without *sampctl*

Download the latest version of the library and its dependencies from:

https://github.com/pawn-lang/YSI-Includes/releases/download/nightly/YSI-Includes-nightly.zip

And extract the contents of the contained *YSI-Includes* directory to `pawno/includes/`.

## Compile-Time Options

YSI shows a lot of information when it starts up, and does some things that aren't necessary in
every script.  You can disable a lot of these with the following defines:

```pawn
// Don't display the message about caching the code (with `YSI_YES_MODE_CACHE`).
#define YSI_NO_CACHE_MESSAGE

// Don't display the message about startup optimisation (it still happens, you just aren't told).
#define YSI_NO_OPTIMISATION_MESSAGE

// Don't check if this is the latest version of YSI.
#define YSI_NO_VERSION_CHECK

// If there are no filterscripts also using YSI.
#define YSI_NO_MASTER

#include <YSI_Group\y_library>
```

