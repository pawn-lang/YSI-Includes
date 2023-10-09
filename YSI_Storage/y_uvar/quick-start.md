# Quick Start

This is very similar to y_svar, but for per-player data so requires y_users:

```pawn
#define MODE_NAME "Mode_Test_1"

#include <YSI\y_users>
#include <YSI\y_uvar>

enum E_PLAYER_DATA
{
    E_PLAYER_DATA_SKIN,
    Float:E_PLAYER_DATA_HEALTH
}

uvar gPlayerData[MAX_PLAYERS][E_PLAYER_DATA];
```
