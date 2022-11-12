y_scriptinit - v1.0
==========================================
OnScriptInit, OnCodeInit, and several utility functions for plugins and server option determination.
------------------------------------------
(c) 2022 YSI contibutors, licensed under MPL 1.1

This file provides `OnScriptInit` and `OnScriptExit` which are called at the start and end of the current script, regardless of what the type of the script is. It also provides `IS_FILTERSCRIPT` as a (partial) replacement for `FILTERSCRIPT` which detects what the mode is at runtime for a more reliable system (but it is a run-time variable, not a compile-time constant).




## Variables


### `YSI_FILTERSCRIPT`:

#### Tag
`bool:`


#### Remarks

`true` if the current script is running as a filterscript.



## Functions


### `ScriptInit_CallOnCodeInit`:


#### Syntax


```pawn
ScriptInit_CallOnCodeInit(jit, fs)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`jit`	 | 	`bool ` We are calling the callback from the JIT plugin.	 |
| 	`fs`	 | 	`bool ` We are calling the callback in a filterscript.	 |

#### Tag
`bool:`


#### Remarks
This is seemingly a lot of code just to call a callback, but it does more than that. Really this is `OnScriptInit` for this file - it calls other callbacks, dumps debug information, profiles the startup, and caches compilation results. These steps are all done regardless of which callback gets triggered first, hence why the code is abstracted.


#### Depends on
* [`E_SCRIPTINIT_STATE_RELOAD`](#E_SCRIPTINIT_STATE_RELOAD)
* [`FIXES_format`](#FIXES_format)
* [`GetTickCount`](#GetTickCount)
* [`R@`](#R@)
* [`ScriptInit_CodeInitFuncs_`](#ScriptInit_CodeInitFuncs_)
* [`Server_DisableLongCall`](#Server_DisableLongCall)
* [`Server_EnableLongCall`](#Server_EnableLongCall)
* [`Server_FinishIntroPart`](#Server_FinishIntroPart)
* [`Server_PrintIntroMessage`](#Server_PrintIntroMessage)
* [`Server_PrintIntroPart`](#Server_PrintIntroPart)
* [`YSI_EMPTY`](#YSI_EMPTY)
* [`YSI_SPACE`](#YSI_SPACE)
* [`YSI_g_sScriptInitState`](#YSI_g_sScriptInitState)
* [`YSI_gscInitMsgD`](#YSI_gscInitMsgD)
* [`true`](#true)
#### Estimated stack usage
41 cells



### `ScriptInit_Dump`:


#### Syntax


```pawn
ScriptInit_Dump(filename[], message[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`filename`	 | 	` [] ` Name of the file to write the dump to.	 |
| 	`message`	 | 	` [] ` Message to show in the console.	 |

#### Remarks
Write a disassembled version of the current state of the script to a file. This is by far the most powerful debugging technique I've ever had while developing YSI. It is generally called twice - once before `OnCodeInit` is run, and once after. That callback does all of the assembly-level transformations used to implement many of the advanced YSI features. Thus the two resulting dump files can be used to examine and compare the results of every code rewrite done, and see where things have gone wrong. Plus, if anyone has a complex bug I can ask for those two files and get a very complete view of what their script is trying to do, without needing any of their source.


#### Depends on
* [`DisasmWrite`](#DisasmWrite)
* [`FIXES_format`](#FIXES_format)
* [`GetYSIScriptfilesDir`](#GetYSIScriptfilesDir)
* [`PrintAmxHeader`](#PrintAmxHeader)
* [`Server_DisableLongCall`](#Server_DisableLongCall)
* [`Server_EnableLongCall`](#Server_EnableLongCall)
* [`Server_FinishIntroPart`](#Server_FinishIntroPart)
* [`Server_PrintIntroPart`](#Server_PrintIntroPart)
* [`YSI_SPACE`](#YSI_SPACE)
* [`YSI_gsStartTime`](#YSI_gsStartTime)
* [`YSI_gscDone`](#YSI_gscDone)
* [`YSI_gscInitMsgC`](#YSI_gscInitMsgC)
* [`YSI_gscInitMsgD`](#YSI_gscInitMsgD)
* [`fautocleanup`](#fautocleanup)
#### Estimated stack usage
57 cells



### `ScriptInit_GetStartTime`:


#### Syntax


```pawn
ScriptInit_GetStartTime()
```

#### Remarks
Store the earliest time of this script starting that we can.


#### Depends on
* [`YSI_gsStartDMY`](#YSI_gsStartDMY)
* [`YSI_gsStartHMS`](#YSI_gsStartHMS)
* [`YSI_gsStartTime`](#YSI_gsStartTime)
* [`getdate`](#getdate)
* [`gettime`](#gettime)
#### Estimated stack usage
13 cells



### `ScriptInit_PurgeTemporaries`:


#### Syntax


```pawn
ScriptInit_PurgeTemporaries()
```

#### Remarks
Delete temporary files that have reached their maximum age. Related to `ftemporary`, which only stores files for a limited period.


#### Depends on
* [`FIXES_fclose`](#FIXES_fclose)
* [`FIXES_fread`](#FIXES_fread)
* [`FIXES_fseek`](#FIXES_fseek)
* [`FIXES_fwrite`](#FIXES_fwrite)
* [`FIXES_strfind`](#FIXES_strfind)
* [`YSI_SPACE`](#YSI_SPACE)
* [`YSI_SetTimer__`](#YSI_SetTimer__)
* [`YSI_TEMP_FILE_NAME`](#YSI_TEMP_FILE_NAME)
* [`YSI_gsPurgeTimer`](#YSI_gsPurgeTimer)
* [`false`](#false)
* [`fexist`](#fexist)
* [`fopen`](#fopen)
* [`fremove`](#fremove)
* [`ftemporary_`](#ftemporary_)
* [`gettime`](#gettime)
* [`io_read`](#io_read)
* [`io_write`](#io_write)
* [`seek_start`](#seek_start)
* [`strlen`](#strlen)
* [`strval`](#strval)
* [`true`](#true)
#### Attributes
* `public`
#### Estimated stack usage
118 cells



### `Script_CacheLoaded`:


#### Syntax


```pawn
Script_CacheLoaded()
```

#### Tag
`bool:`


#### Returns
`true` if this script was loaded from `YSI_CACHE`.


#### Depends on
* [`E_SCRIPTINIT_STATE_NONE`](#E_SCRIPTINIT_STATE_NONE)
* [`E_SCRIPTINIT_STATE_RELOAD`](#E_SCRIPTINIT_STATE_RELOAD)
* [`YSI_g_sScriptInitState`](#YSI_g_sScriptInitState)
#### Estimated stack usage
1 cells



### `Script_CacheSaved`:


#### Syntax


```pawn
Script_CacheSaved()
```

#### Tag
`bool:`


#### Returns
`true` if this script was written to `YSI_CACHE`.


#### Depends on
* [`E_SCRIPTINIT_STATE_DUMPED`](#E_SCRIPTINIT_STATE_DUMPED)
* [`E_SCRIPTINIT_STATE_NONE`](#E_SCRIPTINIT_STATE_NONE)
* [`YSI_g_sScriptInitState`](#YSI_g_sScriptInitState)
#### Estimated stack usage
1 cells



### `Script_IsFilterscript`:


#### Syntax


```pawn
Script_IsFilterscript()
```

#### Tag
`bool:`


#### Returns
`true` if this script is determined to be a filterscript at runtime.


#### Estimated stack usage
1 cells



### `Script_IsGameMode`:


#### Syntax


```pawn
Script_IsGameMode()
```

#### Tag
`bool:`


#### Returns
`true` if this script is determined to be a gamemode at runtime.


#### Estimated stack usage
1 cells



### `Script_IsLinuxCompiler`:


#### Syntax


```pawn
Script_IsLinuxCompiler()
```

#### Tag
`bool:`


#### Returns
`true` if this script was compiled with a Linux compiler.


#### Estimated stack usage
1 cells



### `Script_IsWindowsCompiler`:


#### Syntax


```pawn
Script_IsWindowsCompiler()
```

#### Tag
`bool:`


#### Returns
`true` if this script was compiled with a Windows compiler.


#### Estimated stack usage
1 cells



### `Script_JITComplete`:


#### Syntax


```pawn
Script_JITComplete()
```

#### Tag
`bool:`


#### Returns
`true` if the JIT plugin has completed compilation.


#### Depends on
* [`E_SCRIPTINIT_STATE_JITED`](#E_SCRIPTINIT_STATE_JITED)
* [`E_SCRIPTINIT_STATE_NONE`](#E_SCRIPTINIT_STATE_NONE)
* [`YSI_g_sScriptInitState`](#YSI_g_sScriptInitState)
#### Estimated stack usage
1 cells



### `Server_Abort`:


#### Syntax


```pawn
Server_Abort(reason)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`reason`	 | 	The halt type.	 |

#### Remarks
Halt the server, or at least the current public, instantly.


#### Estimated stack usage
1 cells



### `Server_CacheLoaded`:


#### Syntax


```pawn
Server_CacheLoaded()
```

#### Tag
`bool:`


#### Returns
`true` if this script was loaded from `YSI_CACHE`.


#### Depends on
* [`E_SCRIPTINIT_STATE_NONE`](#E_SCRIPTINIT_STATE_NONE)
* [`E_SCRIPTINIT_STATE_RELOAD`](#E_SCRIPTINIT_STATE_RELOAD)
* [`YSI_g_sScriptInitState`](#YSI_g_sScriptInitState)
#### Estimated stack usage
1 cells



### `Server_CacheSaved`:


#### Syntax


```pawn
Server_CacheSaved()
```

#### Tag
`bool:`


#### Returns
`true` if this script was written to `YSI_CACHE`.


#### Depends on
* [`E_SCRIPTINIT_STATE_DUMPED`](#E_SCRIPTINIT_STATE_DUMPED)
* [`E_SCRIPTINIT_STATE_NONE`](#E_SCRIPTINIT_STATE_NONE)
* [`YSI_g_sScriptInitState`](#YSI_g_sScriptInitState)
#### Estimated stack usage
1 cells



### `Server_CrashDetectExists`:


#### Syntax


```pawn
Server_CrashDetectExists()
```

#### Tag
`bool:`


#### Returns
`true` if crashdetect exists.


#### Depends on
* [`false`](#false)
#### Estimated stack usage
1 cells



### `Server_DisableDetectAddr0`:


#### Syntax


```pawn
Server_DisableDetectAddr0()
```

#### Remarks
Disable crashdetect's ability to detect possibly unintended writes to address naught.


#### Estimated stack usage
1 cells



### `Server_DisableLongCall`:


#### Syntax


```pawn
Server_DisableLongCall()
```

#### Remarks
Disable the detection of slow functions, if crashdetect exists.


#### Estimated stack usage
1 cells



### `Server_EnableDetectAddr0`:


#### Syntax


```pawn
Server_EnableDetectAddr0()
```

#### Remarks
Enable crashdetect's ability to detect possibly unintended writes to address naught.


#### Estimated stack usage
1 cells



### `Server_EnableLongCall`:


#### Syntax


```pawn
Server_EnableLongCall()
```

#### Remarks
Enable the detection of slow functions, if crashdetect exists.


#### Estimated stack usage
1 cells



### `Server_FinishIntroMessage`:


#### Syntax


```pawn
Server_FinishIntroMessage()
```

#### Remarks
This is called after all the intro messages have been completed to add padding.


#### Depends on
* [`YSI_Print__`](#YSI_Print__)
* [`YSI_SPACE`](#YSI_SPACE)
* [`YSI_gsFirstHeader`](#YSI_gsFirstHeader)
* [`true`](#true)
#### Estimated stack usage
3 cells



### `Server_FinishIntroPart`:


#### Syntax


```pawn
Server_FinishIntroPart()
```

#### Remarks
If a box was previously partially written in to with `Server_PrintIntroPart` this closes the box off at the bottom. It basically just prints a line in the console.


#### Depends on
* [`YSI_Print__`](#YSI_Print__)
* [`YSI_gsNewPart`](#YSI_gsNewPart)
* [`YSI_gscHeader`](#YSI_gscHeader)
* [`YSI_gscSpacer`](#YSI_gscSpacer)
* [`true`](#true)
#### Estimated stack usage
3 cells



### `Server_GetLongCallDefault`:


#### Syntax


```pawn
Server_GetLongCallDefault()
```

#### Remarks
Get the default long call time for crashdetect. May not be the current setting. Simply stores the current value, resets it, restores the current and returns the old version.


#### Estimated stack usage
1 cells



### `Server_GetLongCallTime`:


#### Syntax


```pawn
Server_GetLongCallTime()
```

#### Returns
The current setting (in microseconds) for the slow code warning threshold. Or `0` if there is none.


#### Estimated stack usage
1 cells



### `Server_GetStartDateTime`:


#### Syntax


```pawn
Server_GetStartDateTime(&year, &month, &day, &hour, &minute, &second)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`year`	 | 	` & `	 |
| 	`month`	 | 	` & `	 |
| 	`day`	 | 	` & `	 |
| 	`hour`	 | 	` & `	 |
| 	`minute`	 | 	` & `	 |
| 	`second`	 | 	` & `	 |

#### Remarks
Get the start time of the script, previously determined by `ScriptInit_GetStartTime`, as a set of six components for time and date.


#### Depends on
* [`YSI_gsStartDMY`](#YSI_gsStartDMY)
* [`YSI_gsStartHMS`](#YSI_gsStartHMS)
#### Estimated stack usage
1 cells



### `Server_GetStartTime`:


#### Syntax


```pawn
Server_GetStartTime()
```

#### Remarks
Get the start time of the script, previously determined by `ScriptInit_GetStartTime`, as a unix timestamp.


#### Depends on
* [`YSI_gsStartTime`](#YSI_gsStartTime)
#### Estimated stack usage
1 cells



### `Server_HasDetectAddr0`:


#### Syntax


```pawn
Server_HasDetectAddr0()
```

#### Tag
`bool:`


#### Remarks
`true` if crashdetect is able to warn for writes to address naught.


#### Depends on
* [`false`](#false)
#### Estimated stack usage
1 cells



### `Server_HasLongCallControl`:


#### Syntax


```pawn
Server_HasLongCallControl()
```

#### Tag
`bool:`


#### Remarks
Is a version of the crashdetect plugin loaded that we can control long call detection in via registers. There were several releases where this just didn't work properly.


#### Depends on
* [`Server_DisableLongCall`](#Server_DisableLongCall)
* [`Server_EnableLongCall`](#Server_EnableLongCall)
* [`Server_IsLongCallEnabled`](#Server_IsLongCallEnabled)
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
3 cells



### `Server_IsDetectAddr0Enabled`:


#### Syntax


```pawn
Server_IsDetectAddr0Enabled()
```

#### Tag
`bool:`


#### Returns
`true` if crashdetect will warn for writes to address naught.


#### Depends on
* [`false`](#false)
#### Estimated stack usage
1 cells



### `Server_IsFilterscript`:


#### Syntax


```pawn
Server_IsFilterscript()
```

#### Tag
`bool:`


#### Returns
`true` if this script is determined to be a filterscript at runtime.


#### Depends on
* [`YSI_FILTERSCRIPT`](#YSI_FILTERSCRIPT)
#### Estimated stack usage
1 cells



### `Server_IsGameMode`:


#### Syntax


```pawn
Server_IsGameMode()
```

#### Tag
`bool:`


#### Returns
`true` if this script is determined to be a gamemode at runtime.


#### Depends on
* [`YSI_GAMEMODE`](#YSI_GAMEMODE)
#### Estimated stack usage
1 cells



### `Server_IsLinuxCompiler`:


#### Syntax


```pawn
Server_IsLinuxCompiler()
```

#### Tag
`bool:`


#### Returns
`true` if this script was compiled with a Linux compiler.


#### Depends on
* [`false`](#false)
#### Estimated stack usage
1 cells



### `Server_IsLinuxHost`:


#### Syntax


```pawn
Server_IsLinuxHost()
```

#### Tag
`bool:`


#### Returns
`true` if this script is running on a Linux server currently.


#### Depends on
* [`__cod`](#__cod)
* [`__dat`](#__dat)
#### Estimated stack usage
2 cells



### `Server_IsLongCallEnabled`:


#### Syntax


```pawn
Server_IsLongCallEnabled()
```

#### Tag
`bool:`


#### Returns
`true` if long call (slow code) detection is active.


#### Remarks
Check if the crashdetect plugin exists, and long call detection is enabled.


#### Depends on
* [`false`](#false)
#### Estimated stack usage
1 cells



### `Server_IsOpenMP`:


#### Syntax


```pawn
Server_IsOpenMP()
```

#### Tag
`bool:`


#### Returns
`true` if this script is running on an open.mp server currently.


#### Remarks

#### Depends on
* [`__flg`](#__flg)
* [`false`](#false)
#### Estimated stack usage
1 cells



### `Server_IsSAMP`:


#### Syntax


```pawn
Server_IsSAMP()
```

#### Tag
`bool:`


#### Returns
`true` if this script is running on a SA:MP server currently.


#### Depends on
* [`__flg`](#__flg)
* [`false`](#false)
#### Estimated stack usage
1 cells



### `Server_IsWindowsCompiler`:


#### Syntax


```pawn
Server_IsWindowsCompiler()
```

#### Tag
`bool:`


#### Returns
`true` if this script was compiled with a Windows compiler.


#### Depends on
* [`true`](#true)
#### Estimated stack usage
1 cells



### `Server_IsWindowsHost`:


#### Syntax


```pawn
Server_IsWindowsHost()
```

#### Tag
`bool:`


#### Returns
`true` if this script is running on a Windows server currently.


#### Depends on
* [`__cod`](#__cod)
* [`__dat`](#__dat)
#### Estimated stack usage
2 cells



### `Server_JITComplete`:


#### Syntax


```pawn
Server_JITComplete()
```

#### Tag
`bool:`


#### Returns
`true` if the JIT plugin has completed compilation.


#### Depends on
* [`E_SCRIPTINIT_STATE_JITED`](#E_SCRIPTINIT_STATE_JITED)
* [`E_SCRIPTINIT_STATE_NONE`](#E_SCRIPTINIT_STATE_NONE)
* [`YSI_g_sScriptInitState`](#YSI_g_sScriptInitState)
#### Estimated stack usage
1 cells



### `Server_PrintIntroMessage`:


#### Syntax


```pawn
Server_PrintIntroMessage(...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`...`	 | 		 |

#### Remarks
Every parameter to this function is a string, and they are all shown in order in the console, in a nice box. If this is the first call it also shows the amazing beautiful YSI header first.


#### Depends on
* [`Server_PrintYSIHeader`](#Server_PrintYSIHeader)
* [`YSI_Print__`](#YSI_Print__)
* [`YSI_SPACE`](#YSI_SPACE)
* [`YSI_VAPrintF`](#YSI_VAPrintF)
* [`YSI_gsFirstHeader`](#YSI_gsFirstHeader)
* [`YSI_gsObnoxiousHeader`](#YSI_gsObnoxiousHeader)
* [`YSI_gscHeader`](#YSI_gscHeader)
* [`YSI_gscSpacer`](#YSI_gscSpacer)
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`__frm`](#__frm)
* [`cellbytes`](#cellbytes)
* [`false`](#false)
* [`numargs`](#numargs)
#### Estimated stack usage
7 cells



### `Server_PrintIntroPart`:


#### Syntax


```pawn
Server_PrintIntroPart(...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`...`	 | 		 |

#### Remarks
Every parameter to this function is a string, and they are all shown in order in the console, in a nice box. Unlike `Server_PrintIntroMessage` this doesn't close the box, nor does it start a new one if one is already being written in to. Thus this one can append messages within a nice box in the console. If this is the first call it also shows the loved and adored YSI header first.


#### Depends on
* [`Server_PrintYSIHeader`](#Server_PrintYSIHeader)
* [`YSI_Print__`](#YSI_Print__)
* [`YSI_SPACE`](#YSI_SPACE)
* [`YSI_VAPrintF`](#YSI_VAPrintF)
* [`YSI_gsFirstHeader`](#YSI_gsFirstHeader)
* [`YSI_gsNewPart`](#YSI_gsNewPart)
* [`YSI_gsObnoxiousHeader`](#YSI_gsObnoxiousHeader)
* [`YSI_gscHeader`](#YSI_gscHeader)
* [`YSI_gscSpacer`](#YSI_gscSpacer)
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`__frm`](#__frm)
* [`cellbytes`](#cellbytes)
* [`false`](#false)
* [`numargs`](#numargs)
#### Estimated stack usage
7 cells



### `Server_PrintYSIHeader`:


#### Syntax


```pawn
Server_PrintYSIHeader()
```

#### Remarks
Print the awesome header that everyone loves in the console. You're welcomes everyone!


#### Depends on
* [`YSI_Print__`](#YSI_Print__)
#### Estimated stack usage
3 cells



### `Server_ResetLongCallTime`:


#### Syntax


```pawn
Server_ResetLongCallTime()
```

#### Remarks
Set the slow code threshold back to the default value.


#### Estimated stack usage
1 cells



### `Server_RestartLongCall`:


#### Syntax


```pawn
Server_RestartLongCall()
```

#### Remarks
Restart the current function's long call timer, if crashdetect exists. So the detection of slow code will only account for execution time after this point.


#### Estimated stack usage
1 cells



### `Server_SetLongCallTime`:


#### Syntax


```pawn
Server_SetLongCallTime(usTime)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`usTime`	 | 	The time in microseconds.	 |

#### Remarks
Set the time that crashdetect will use when detecting slow functions. Anything executing for longer than this time will trigger a warning.


#### Estimated stack usage
1 cells


