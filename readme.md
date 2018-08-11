# YSI

## General Information

* [installation](installation.md)
* [troubleshooting](troubleshooting.md)
* [YSI_COMPATIBILTY_MODE](YSI_COMPATIBILTY_MODE.md)

## Libraries

### Coding

PAWN scripting improvements (i.e. new language features).

* [y_functional](YSI_Coding/y_functional.md)
* [y_hooks](YSI_Coding/y_hooks.md)
* [y_inline](YSI_Coding/y_inline.md)
* [y_malloc](YSI_Coding/y_malloc.md)
* [y_remote](YSI_Coding/y_remote.md)
* [y_stringhash](YSI_Coding/y_stringhash.md)
* [y_timers](YSI_Coding/y_timers.md)
* [y_unique](YSI_Coding/y_unique.md)
* [y_va](YSI_Coding/y_va.md)

### Core

Core libraries, used almost everywhere else.

* [y_als](YSI_Core/y_als.md)
* [y_cell](YSI_Core/y_cell.md)
* [y_debug](YSI_Core/y_debug.md)
* [y_master](YSI_Core/y_master.md)
* [y_profiling](YSI_Core/y_profiling.md)
* [y_testing](YSI_Core/y_testing.md)
* [y_utils](YSI_Core/y_utils.md)

### Data

Data structures and algorithms.

* [y_bintree](YSI_Data/y_bintree.md)
* [y_bit](YSI_Data/y_bit.md)
* [y_iterate](YSI_Data/y_iterate.md) (AKA y_foreach)
* [y_hashmap](YSI_Data/y_hashmap.md)
* [y_jaggedarray](YSI_Data/y_jaggedarray.md)
* [y_playerarray](YSI_Data/y_playerarray.md)
* [y_playerset](YSI_Data/y_playerset.md)
* [y_sortedarray](YSI_Data/y_sortedarray.md)
* [y_sparsearray](YSI_Data/y_sparsearray.md)

### Extra

Optional features.

* [y_extra](YSI_Extra/y_extra.md)
* [y_files](YSI_Extra/y_files.md)
* [y_streamer_plugin](YSI_Extra/y_streamer_plugin.md)

### Game

Libraries that provide information about the game.

* [y_vehicledata](YSI_Game/y_vehicledata.md)

### Players

Libraries for managing players.

* [y_groups](YSI_Players/y_groups.md)
* [y_languages](YSI_Players/y_languages.md)
* [y_text](YSI_Players/y_text.md)
* [y_users](YSI_Players/y_users.md)

### Server

Libraries for controlling the server.

* [y_colours](YSI_Server/y_colours.md) (AKA y_colors)
* [y_flooding](YSI_Server/y_flooding.md)
* [y_lock](YSI_Server/y_lock.md)
* [y_punycode](YSI_Server/y_punycode.md)
* [y_scriptinit](YSI_Server/y_scriptinit.md)
* [y_stringise](YSI_Server/y_stringise.md) (AKA y_stringize)
* [y_td](YSI_Server/y_td.md)

### Storage

Libraries for interacting with persistent data.

* [y_amx](YSI_Storage/y_amx.md)
* [y_bitmap](YSI_Storage/y_bitmap.md)
* [y_ini](YSI_Storage/y_ini.md)
* [y_php](YSI_Storage/y_php.md)
* [y_svar](YSI_Storage/y_svar.md)
* [y_uvar](YSI_Storage/y_uvar.md)
* [y_xml](YSI_Storage/y_xml.md)

### Visual

Libraries that have in-game visible effects.

* [y_areas](YSI_Visual/y_areas.md)
* [y_classes](YSI_Visual/y_classes.md)
* [y_commands](YSI_Visual/y_commands.md)
* [y_dialog](YSI_Visual/y_dialog.md)
* [y_loader](YSI_Visual/y_loader.md)
* [y_properties](YSI_Visual/y_properties.md)
* [y_races](YSI_Visual/y_races.md)
* [y_zonenames](YSI_Visual/y_zonenames.md)
* [y_zonepulse](YSI_Visual/y_zonepulse.md)

## What Does YSI Stand For?

No-one actually knows!  The original idea was "Y_Less' Server Includes", but "Script" and "Server" were frequently intermixed, and there are more devs than just Y_Less now, so the "Y" just became a recursive acronym for "YSI".  There are now several official meanings, each incorporating different aspects of YSI:

### YSI Script Includes

Core libraries.

### YSI Scripting Improvements

Coding libraries (pawn language extensions).

### YSI Server Includes

Game related stuff (commands, properties, text etc).

### YSI Script Incidentals

Extras, like login and commands.

### YSI Seriously Incomprehensible

The macros (though in their defense, writing macros to do the parsing within the compiler limitations is VERY hard).

### YSI Stupid Includes

y_tho.

