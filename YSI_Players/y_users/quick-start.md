# Quick Start

The y_users system is loosely based on player names, but multiple names can be assigned to the same account if desired. The system also has preload data, which is loaded using a player's name when they connect to give information about any potential accounts they may have before they log in. The basic use of the system for logging in and registering players is given below. More advanced information is available here.


## Use
Using y_users is very simple, there are two main functions that need calling: Player_TryRegister to register a new player and Player_TryLogin to log in existing players. These functions can be called from dialogs or commands depending on how a server's registration system is set up, and y_extra even does all this too, making y_users as easy to use as:
```pawn
#define MODE_NAME "MyMode"
#define PP_WP

native WP_Hash(target[], size, text[]);

#include <YSI\y_commands>
#include <YSI\y_users>
#include <YSI\y_extra>
```

That code includes y_commands for "/login" and "/register", and has two defines:
```pawn
#define MODE_NAME "MyMode"
```

This is required by y_users when saving data. If it didn't exist and a server switched between multiple modes then all the data would get confused and messed up.
```pawn
#define PP_WP

native WP_Hash(target[], size, text[]);
```

Defines with the prefix "PP_" mean Player Password, and are used to determine which hash algorithm should be used to encrypt passwords. The options are:

PP_WP: Whirlpool
PP_YSI: JSC Hash (the old default, but now you must specify)
PP_MD5: MD5
When using Whirlpool, the plugin is required, as is the native declaration shown above.
