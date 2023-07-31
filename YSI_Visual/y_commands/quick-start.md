# Quick Start

This library manages commands declared as:
```pawn
YCMD:name(playerid, params[], help)
{
    if (help)
    {
        // Display information about the command.
        return 1;
    }
    // Run the command.
    return 1;
}
```
You can create a command alias by doing:

```pawn
YCMD:alias(playerid, params[], help) = original_commandname;
```

# Backwards compatibility

Many existing SA:MP command processors already are using the syntax below, we all know and love, therefore it is available even in YSI: 

```pawn
CMD:name(playerid, params[])
{
    // Run the command.
    return 1;
}
```
This management includes listing of all commands, per-player permissions on exactly who can and can't use different commands, renaming of commands, and multiple script awareness.

"help" is used to maintain useful information about commands to display to interested users.
