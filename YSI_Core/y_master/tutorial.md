# Tutorial

## Introduction

I've seen this happen over and over again - people have a team helping them
develop a mode then one of the scripters gets annoyed and leaves, taking the
script with them (sometimes releasing it, sometimes setting up their own
server). Once this has happened there's nothing you can do about it, you need
safeguards in place from the start to ensure that it can't happen\*. This
tutorial uses the y_master and y_lock systems to develop and deploy full
scripts, without any one coder (except you as the lead) ever having access to
all the code, but still being able to script and test.

The basic idea is to split the script up in to modules - have each scripter work
on one module/part and distribute those modules as compiled filterscripts to the
other scripters. Then, when your code is ready to be put on the server, you just
compile everything in to one big script (if you want).

* You should also only use people you trust completely.

## Keywords

The basic technology (I say basic, it's one of the most complex libraries I've
ever written) behind this is the YSI y_master library. This system allows you to
write scripts and define functions that are not in the current script, instead
being in another script, but still compile and run everything. The syntax is
based on that of publics - using `forward` and `public` to define functions, but
instead uses `foreign` and `global`:

```pawn
foreign MyFunc(a, string:b[]);

global MyFunc(a, string:b[])
{
    printf("%d %s", a, b);
    return 1;
}
```

### `foreign`

The `foreign` keyword means "this function is defined somewhere, but not here",
and is used in basically the same way as `forward` (as seen above). One feature
common to most YSI libraries is the use of the `string:` tag on strings - this
MUST be used when an array is a string. When the array is not a string you leave
off the `string:` tag but instead you MUST follow the array with the size:

```pawn
foreign Func2(arr[], size);
```

Failure to do this will result in some very cryptic error messages (same as with
missing the `string:` tag as then the compiler will think that it's just a
normal array that should be followed by its size).

If `foreign` appears in a script, you can call that function in that script,
even if it never actually gets defined in the script:

```pawn
#define MASTER 4
#define YSI_IS_CLIENT
#include <YSI\y_master>

foreign MyFunc(a, string:b[]);

main()
{
    MyFunc(56, "hi there");
}
```

That above is a complete script - I'll come to what the stuff at the top means
later.

For this to work, however, you need another script (in this case a filterscript
as that code above is a gamemode), with the corresponding `global` declaration
to actually DO something.

### `global`

`global` is like `public` - it defines the function itself:

```pawn
global MyFunc(a, string:b[])
{
    printf("%d %d", a, b);
    return 1;
}
```

If `global` appears in a script you must also have `foreign` in that script (if
you don't you'll get a `forward` warning and the script might crash the server).
The filterscript partner to the gamemode above is:

```pawn
#define MASTER 4
#define YSI_IS_SERVER
#include <YSI\y_master>

foreign MyFunc(a, string:b[]);

global MyFunc(a, string:b[])
{
    printf("%d %s", a, b);
    return 1;
}
```

When the gamemode calls `MyFunc` THIS is the code that gets run, despite being
in another script. Under the hood this calls "CallRemoteFunction", but has the
added advantage of compile-time parameter checking. If you just did:

```pawn
CallRemoteFunction("MyFunc", "si", 56, "hi there");
```

The code will compile fun but will not run. For one thing `MyFunc` has been
misspelled as `MyFonc`, and the parameter specifiers are backwards (`si` instead
of `is`). As far as the compiler is concerned this is fine because it doesn't
know WHAT the function does, only that it takes a couple of strings and some
other things - as long as you do that it's happy.

y_master on the other hand, when using `foreign` and `global` will give relevant
warnings and errors when you misspell function names and get parameters wrong
(as with any other function call).

### `void:`

If a `global` function doesn't return something, it must be explicitly marked as such:

```pawn
global NoReturn()
{
    // Wrong.
}
```

```pawn
global void:NoReturn()
{
    // Right.
}
```

### `string:`

They can also return strings if they are declared using `string:`:

```pawn
global string:StringReturn()
{
    new
        ret[YSI_MAX_STRING];
    return ret;
}
```

The return string MUST have size `YSI_MAX_STRING`, but you can set how big this
is if you want (default 144):

```pawn
#define YSI_MAX_STRING 512
#include <YSI\y_master>
```

You can also return any other tag (`Float:`, `bool:` etc) as you please.

## Headers

Both code examples had headers before the function declaration:

```pawn
#define MASTER 4
#define YSI_IS_CLIENT
#include <YSI\y_master>
```

```pawn
#define MASTER 4
#define YSI_IS_SERVER
#include <YSI\y_master>
```

Lets look at each line individually:

### Master

```pawn
#define MASTER 4
```

Some scripts may have some code, other scripts might not. For example
filterscript `fs_streamer` might contain your streamer and filterscript
`fs_users` might hold your user system (admin levels etc). You don't want user
function calls going to the the streamer filterscript where they can't be used,
do you? Each independent library (or code section) has its own `MASTER` number
so that the scripts know where to send the relevant calls:

#### `funcs_users.inc`

This is using `MASTER` number 1.

```pawn
#define MASTER 1
#include <YSI\y_master>

static stock
    gsLoggedIn[MAX_PLAYERS];

foreign bool:IsLoggedIn(playerid);

global bool:IsLoggedIn(playerid)
{
    return gsLoggedIn[playerid];
}
```

#### `funcs_streamer.inc`

This is using `MASTER` number 2.

```pawn
#define MASTER 2
#include <YSI\y_master>

foreign AddObject(model, Float:x, Float:y, Float:z);

global AddObject(model, Float:x, Float:y, Float:z)
{
    new
        objectid = /* something */;
    return objectid;
}
```

#### `fs_streamer.pwn`

```pawn
#define YSI_IS_SERVER
#include <funcs_streamer>
```

#### `fs_users.pwn`

```pawn
#define YSI_IS_SERVER
#include <funcs_users>
```

#### `gamemode.pwn`

```pawn
#define YSI_IS_CLIENT
#include <funcs_streamer>
#include <funcs_users>

main()
{
}
```

When the gamemode calls `IsLoggedIn`, the code in `fs_users` will be called.
When the gamemode calls `AddObject`, the code in `fs_streamer` will be called
(pad both out as appropriate). The gamemode has BOTH includes, each using a
different `MASTER` value, but this is fine (and correct). All functions defined
after `MASTER` use that value until `MASTER` is redefined (note that you don't
need `#undef`):

#### `funcs_users.inc`

This is using `MASTER` number 1.

```pawn
#define YSI_IS_CLIENT

#define MASTER 1
#include <YSI\y_master>

static stock
    gsLoggedIn[MAX_PLAYERS];

foreign bool:IsLoggedIn(playerid);

global bool:IsLoggedIn(playerid)
{
    return gsLoggedIn[playerid];
}

#define MASTER 2
#include <YSI\y_master>

foreign AddObject(model, Float:x, Float:y, Float:z);

global AddObject(model, Float:x, Float:y, Float:z)
{
    new
        objectid = /* something */;
    return objectid;
}

main()
{
}
```

You also need to include `YSI\y_master` every time you reset `MASTER` (as the
above expanded code shows).

### `YSI_IS_`

The code above uses `YSI_IS_SERVER` in the filterscripts and `YSI_IS_CLIENT` in
the gamemode. This is because the both gamemode and `fs_streamer` have
`global AddObject`, and both the gamemode and `fs_users` have
`global IsLoggedIn`. If both scripts define the same function, how do we know
which one to call?

#### `YSI_IS_SERVER` and `YSI_IS_CLIENT`

The gamemode is set as `YSI_IS_CLIENT`. This means that any global function
definitions are just ignored (in fact they're set to `stock` functions so that
the compiler can remove them entirely). The filterscripts are set as
`YSI_IS_SERVER`, this means that any calls for a function they have go directly
to them, no other script. They are both `YSI_IS_SERVER` because they both have
different bits of code (set by different `MASTER` values) to handle.

#### Cloud

The other way to handle this is to not define anything. If you remove
`YSI_IS_SERVER` from the filterscripts and `YSI_IS_CLIENT` from the gamemode the
server will select one script to handle all requests when it starts (usually the
filterscripts as they load first). This means that the compiler will NOT remove
the extra code from the gamemode because it MAY be needed. This style is
internally referred to as "cloud" because the server selects one system to
handle everything from all available processing resources.

#### `YSI_IS_STUB`

There is one more type: `YSI_IS_STUB`. In this case it is actually an error to
have any `global` declarations in your mode - you can ONLY have `foreign`
declarations.

This script is fine:

```pawn
#define MASTER 4
#define YSI_IS_STUB
#include <YSI\y_master>

foreign MyFunc(a, string:b[]);

main()
{
    MyFunc(56, "hi there");
}
```

This script is wrong and will give an error because it contains `global`:

```pawn
#define MASTER 4
#define YSI_IS_STUB
#include <YSI\y_master>

foreign MyFunc(a, string:b[]);

global MyFunc(a, string:b[])
{
    printf("%d %s", a, b);
    return 1;
}

main()
{
    MyFunc(56, "hi there");
}
```

#### `YSI_NO_MASTER`

Using this instead of any of the compile options above entirely disables the YSI
master system and compiles everything as a single mode with no remote calls at
all.

#### Advanced

`YSI_IS_SERVER`, `YSI_IS_CLIENT` and `YSI_IS_STUB` define that setting for the
whole mode. You can modify these settings per module (i.e. every time you
include `YSI\y_master`:

```pawn
#define MASTER 4
#define YSIM_U_DISABLE
#include <YSI\y_master>
```

As with `MASTER`, this will change the setting until you next include
`YSI\y_master`. There are six definitions:

* **YSIM_S_ENABLE** - Turn on `SERVER` mode for the current `YSI\y_master`
  inclusion.
* **YSIM_S_DISABLE** - Turn off `SERVER` mode.
* **YSIM_C_ENABLE** - Turn on `CLIENT` mode.
* **YSIM_C_DISABLE** - Turn off `CLIENT` mode.
* **YSIM_U_ENABLE** - Turn on `STUB` mode. `S` was taken, so this is for `stUb`.
* **YSIM_U_DISABLE** - Turn off `STUB` mode. Note that every YSI library that
  uses y_master has this set. All YSI libraries also have the ability to revert
  all settings after they have been included, so are transparent to your use of
  the master system.

### `#include <YSI\y_master>`

`YSI\y_master` is the entry point to the master system, and unlike most includes
it can be imported many times with different settings each time:

```pawn
#define MASTER 4
#include <YSI\y_master>
#define MASTER 5
#include <YSI\y_master>
#define MASTER 6
#include <YSI\y_master>
```

You can use the default settings, which are `MASTER` number 23 (reserved for
`default`) and `CLOUD` mode simply by including it:

```pawn
#include <YSI\y_master>
```

It is recommended to do this after all other includes in your mode so that
things like commands do not inherit the previously set `MASTER` and not get
called as a result:

```pawn
// Uses "MASTER" number 25, but auto-reverts.
#include <YSI\y_commands>
// Uses "MASTER" number 2, but doesn't reset.
#include <funcs_streamer>
// Reset to defaults.
#include <YSI\y_master>

main()
{
}

YCMD:hi(playerid, params[], help)
{
}
```

The code above will set `YCMD:hi` to use `MASTER` number `23`. Note that this is
a special case master number designed to allow commands to be called where they
are defined when using `y_commands`. You don't want your command to not get
called just because you set `YSI_IS_CLIENT` when it is blatantly only defined in
one script (as used to happen, causing problems). If you DO want this to happen,
just set `MASTER` to something other than `23`.

Additionally, `MASTER` numbers over `15` are reserved for YSI use only.

## y_lock

The section on y_master was quite long as it's a complex system. This system on
the other hand is very simple:

```pawn
#define BIND_IP MAKE_LOCK_IP(127.0.0.1)
#include <YSI\y_lock>
```

```
bind 127.0.0.1
```

That's all you need - `YSI\y_lock` as the FIRST include in your script and
`bind 127.0.0.1` in `server.cfg` or `"bind": "127.0.0.1"` in `samp.json` (must
match the IP in `MAKE_LOCK_IP`). When you do this that script will ONLY run on
localhost, meaning that only one person can connect to it (the person also
playing on that computer). If they don't bind to the correct IP they will get
very strange behaviour.

## Mode Protection

Now that we've shown how "y_lock" can be used to only run scripts locally (i.e.
not online) and how "y_master" can be used to run code in other scripts
seamlessly, lets see how they can be combined to protect your mode from theft:

### Code

#### `funcs_users.inc`

This is using `MASTER` number 1.

```pawn
#define MASTER 1
#include <YSI\y_master>

foreign bool:IsLoggedIn(playerid);

#tryinclude <impl\impl_users.inc>
```

#### `impl\impl_users.inc`

```pawn
static stock
    gsLoggedIn[MAX_PLAYERS];

global bool:IsLoggedIn(playerid)
{
    return gsLoggedIn[playerid];
}
```

#### `funcs_streamer.inc`

```pawn
#define MASTER 2
#include <YSI\y_master>

foreign AddObject(model, Float:x, Float:y, Float:z);

#tryinclude <impl\impl_streamer.inc>
```

#### `impl\impl_streamer.inc`

```pawn
global AddObject(model, Float:x, Float:y, Float:z)
{
    new
        objectid = /* something */;
    return objectid;
}
```

#### `fs_streamer.pwn`

```pawn
#include <YSI\y_lock>

#define YSIM_S_ENABLE
#include <funcs_streamer>
```

#### `fs_users.pwn`

```pawn
#include <YSI\y_lock>

#define YSIM_S_ENABLE
#include <funcs_users>
```

#### `gamemode.pwn`

```pawn
#define YSI_IS_STUB
#include <YSI\y_lock>

#include <funcs_streamer>
#include <funcs_users>

main()
{
}
```

### Explanation

The code above entirely separates out concerns. The `global` declarations of the
`users` code are in a separate file to the `foreign` declarations, same with the
`streamer` code, and they use `#tryinclude` instead of `#include` to pull in the
full implementations. What's more, the gamemode sets `YSI_IS_STUB`, despite the
fact that it includes files that contain `global`.

The secret is that not everyone has every file. The person working on the
streamer will have `funcs_streamer.inc`, `impl\impl_streamer.inc` and
`fs_streamer.pwn`. They will also have `funcs_users.inc` but will NOT have
`impl\impl_users.inc` or `fs_users.pwn` If they try and include
`funcs_users.inc` to use some of the uses system functions they will need to do:

```pawn
#define YSIM_U_ENABLE
#include <funcs_users>

#define _YSIM_OVERRIDE 2
#include <YSI\y_master>
```

That will enable `STUB` mode, include `funcs_users.inc` to get the `foreign`
definitions, but not `impl\impl_users.inc` because they don't have it. It will
then REVERT to the settings before (for `MASTER` number 2) and continue with the
rest of the `impl_streamer.inc` code:

```pawn
#define MASTER 2
#include <YSI\y_master>

foreign AddObject(model, Float:x, Float:y, Float:z);

#tryinclude <impl\impl_streamer.inc>
```

#### `impl\impl_streamer.inc`

```pawn
#define YSIM_U_ENABLE
#include <funcs_users>

#define _YSIM_OVERRIDE 2
#include <YSI\y_master>

global AddObject(model, Float:x, Float:y, Float:z)
{
    new
        objectid = /* something */;
    /* Code now using the users system */;
    return objectid;
}
```

When you, as head scripter, decide to compile the whole mode for use you simply
do:

```pawn
//#define YSI_IS_STUB
//#include <YSI\y_lock>
#define YSI_NO_MASTER

#include <funcs_streamer>
#include <funcs_users>

main()
{
}
```

And, as you have every file all the code will be pulled together in to one big
mode. Note that `YSI_NO_MASTER` overrides every other setting for the master
system (there is `YSIM_T_ENABLE` and `YSIM_T_DISABLE` as well, but they're
untested).

On the other hand, when your scripters are testing things, you simply compile
all the filterscripts and give them out to people. These will be compiled and
locked, so they can only use them locally, but will contain all the code that
they don't have so they can still test the mode. For this to work your .pwn
files (`fs_streamer.pwn`, `fs_users.pwn`, `gamemode.pwn` etc) will have to be
skeleton files with all other code defined in includes so that you can pull it
all together as required.

This system can be integrated with a content versioning system such as SVN by
limiting file or directory access to different users so they can't download
every file, only the ones they're allowed to work on. This way only you ever
have every all the source code, and only you can run the mode on an IP other
than `127.0.0.1` - meaning that no-one else can steal it.
