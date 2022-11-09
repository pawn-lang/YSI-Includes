y_dumpamx - v1.0
==========================================
Generate a new AMX from the current state of code.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1


This library allows you to dump the current state of the AMX to a file. If this dumping is done by defining `YSI_YES_MODE_CACHE`, then the file will be generated after `OnCodeInit` is complete, with all YSI constructs pre-compiled and included in the resulting file. The new code will also start up and resume from the point after the dump was completed.



## Functions


### `DumpAMX_Write`:


#### Syntax


```pawn
DumpAMX_Write(filename[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`filename`	 | 	` [] ` The name of the output file.	 |

#### Tag
`bool:`


#### Remarks
Dump the currently running AMX to a file. Although the AMX has surely just been loaded *from* a file, this isn't pointless as a lot of code can be (and is, with YSI) modified on initial load. Thus this feature can do the generation once, and store the result in to a new file that can be loaded repeatedly. Of course this is still pointless if your code changes frequently, as the saving is quite slow and would need to be done after every compile. If a script is only likely to be loaded once after a compile, with subsequent loads being for a new version, these is no advantage to using this caching.


#### Depends on
* [`AMX_HDR`](#AMX_HDR)
* [`AMX_HDR_FLAGS`](#AMX_HDR_FLAGS)
* [`DumpAMX_WriteAMXCode`](#DumpAMX_WriteAMXCode)
* [`DumpAMX_WriteAMXData`](#DumpAMX_WriteAMXData)
* [`DumpAMX_WriteAMXHeader`](#DumpAMX_WriteAMXHeader)
* [`FIXES_fblockwrite`](#FIXES_fblockwrite)
* [`FIXES_fclose`](#FIXES_fclose)
* [`FIXES_flength`](#FIXES_flength)
* [`FIXES_fseek`](#FIXES_fseek)
* [`GetAmxHeader`](#GetAmxHeader)
* [`false`](#false)
* [`fopen`](#fopen)
* [`io_write`](#io_write)
* [`seek_start`](#seek_start)
* [`true`](#true)
#### Estimated stack usage
36 cells



