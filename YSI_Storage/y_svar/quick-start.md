# Quick Start

y_svar is BY FAR the simplest way of creating data that is saved for a server. It is very similar to y_uvar, but saves data that is server-wide, not per-player. Declaring an array with svar instead of new (or other methods) means that the variable is automatically (automagically) saved when the mode ends and loaded again when the mode restarts.


## Example

```pawn
#define MODE_NAME "SavedText"
#include <YSI\y_svar>

svar gSavedText[200];

public OnGameModeInit()
{
    printf("Saved Text: %s", gSavedText);
}

YCMD:settext(playerid, params[], help)
{
    if (help) return SendClientMessage(playerid, 0xFF0000AA, "Sets the saved text");
    strcpy(gSavedText, params);
    return 1;
}
```
The first time this code is ever run the saved text will be blank. However, after /settext has been called then gSavedText will be set AND SAVED. When the mode runs a second time this saved value will be loaded automatically and displayed when the server starts.

## Use

The use of this library is VERY simple. First, set a mode name to be used for saving the data and include y_svar:
```pawn
#define MODE_NAME "UniqueName"
#include <YSI\y_svar>
```

Then variables that should be saved can be declared using svar. Both enums and 2D arrays are supported; however, the variable MUST be on the same line as the svar:
```pawn
enum E_EXAMPLE
{
    E_EXAMPLE_A,
    Float:E_EXAMPLE_B,
    E_EXAMPLE_C[24]
}

svar gExampleEnum[E_EXAMPLE];
svar gExample1D[200];
svar gExample2D[200][200];
svar gExample2DEnum[200][E_EXAMPLE];
svar gExampleEnum2D[E_EXAMPLE][200];
In terms of code, these are prefectly normal variables:

main
{
    printf("E_EXAMPLE_A = %d", gExampleEnum[E_EXAMPLE_A]);
    gExample2DEnum[55][E_EXAMPLE_B] = 98.3;
}
```

### `static`

You can even declare static svar variables, that will only be accessible from the file in which they are declared:

static svar gExampleEnum[E_EXAMPLE];

### Saving

The saving is currently based on y_ini, but the backend is flexible and could be changed. However, this is not a major consideration as the only interaction with the storage system is during mode start and end; all other times these are as fast as normal variables.

## Restrictions
There are a few MINOR restrictions.

Firstly, svars MUST be 1D or 2D arrays - no single variables and no 3D+ arrays because of the way the macros work (but you CAN have an array of size [1]).
Secondly, as previously mentioned, svars MUST come on the same line as the svar declaration.
Technically, multiple svars can come on the same line:
```pawn
svar gExample1D[200], gExample2D[200][200];
```
However, the complexity of the underlying macros mean that this is likely to crash the compiler in all but the simplest of cases, so it is best to just avoid it and use multiple declarations.
