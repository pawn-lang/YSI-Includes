y_serverdata - v1.0
Utility functions for information about plugin and server options.
(c) 2022 YSI contibutors, licensed under MPL 1.1

This file provides OnScriptInit and OnScriptExit which are called at the start and end of the current script, regardless of what the type of the script is. It also provides IS_FILTERSCRIPT as a (partial) replacement for FILTERSCRIPT which detects what the mode is at runtime for a more reliable system (but it is a run-time variable, not a compile-time constant).




Variables


YSI_FILTERSCRIPT:

Tag
bool:


Remarks

true if the current script is running as a filterscript.



Functions


Server_Abort:


Syntax


Server_Abort(reason)

Parameters


Name	Info
reason	The halt type.

Remarks
Halt the server, or at least the current public, instantly.


Estimated stack usage
1 cells



Server_CacheLoaded:


Syntax


Server_CacheLoaded()
Tag
bool:


Returns
true if this script was loaded from YSI_CACHE.


Depends on
E_SCRIPTINIT_STATE_NONE
E_SCRIPTINIT_STATE_RELOAD
YSI_g_sScriptInitState
Estimated stack usage
1 cells



Server_CacheSaved:


Syntax


Server_CacheSaved()
Tag
bool:


Returns
true if this script was written to YSI_CACHE.


Depends on
E_SCRIPTINIT_STATE_DUMPED
E_SCRIPTINIT_STATE_NONE
YSI_g_sScriptInitState
Estimated stack usage
1 cells



Server_CrashDetectExists:


Syntax


Server_CrashDetectExists()
Tag
bool:


Returns
true if crashdetect exists.


Depends on
false
Estimated stack usage
1 cells



Server_DisableDetectAddr0:


Syntax


Server_DisableDetectAddr0()
Remarks
Disable crashdetect's ability to detect possibly unintended writes to address naught.


Estimated stack usage
1 cells



Server_DisableLongCall:


Syntax


Server_DisableLongCall()
Remarks
Disable the detection of slow functions, if crashdetect exists.


Estimated stack usage
1 cells



Server_EnableDetectAddr0:


Syntax


Server_EnableDetectAddr0()
Remarks
Enable crashdetect's ability to detect possibly unintended writes to address naught.


Estimated stack usage
1 cells



Server_EnableLongCall:


Syntax


Server_EnableLongCall()
Remarks
Enable the detection of slow functions, if crashdetect exists.


Estimated stack usage
1 cells



Server_GetCompilerString:


Syntax


Server_GetCompilerString(version[], os[], vlen, olen)

Parameters


Name	Info
version	[]
os	[]
vlen	
olen	

Returns
The version of the compiler used to build this script, as a string.


Remarks
The compiler version used isn't a feature of the server currently executing this code, hence this function is deprecated.


Depends on
Script_GetCompilerString
Estimated stack usage
7 cells



Server_GetCompilerVersion:


Syntax


Server_GetCompilerVersion()
Returns
The version of the compiler used to build this script.


Remarks
The compiler version used isn't a feature of the server currently executing this code, hence this function is deprecated.


Depends on
__Pawn
__PawnBuild
Estimated stack usage
1 cells



Server_GetJITString:


Syntax


Server_GetJITString(version[], vlen)

Parameters


Name	Info
version	[]
vlen	

Returns
The version of the JIT plugin loaded, if any, as a string.


Remarks
There is no native way to determine this, the code just tries to estimate based on some feature heuristics.


Depends on
Server_GetJITVersion
strcat
Estimated stack usage
5 cells



Server_GetJITVersion:


Syntax


Server_GetJITVersion()
Returns
The version of the JIT plugin loaded.


Remarks
There is no native way to determine this, the code just tries to estimate based on some feature heuristics.


Depends on
Script_JITComplete
Server_JITExists
__cip
__jmp
Estimated stack usage
3 cells



Server_GetLongCallDefault:


Syntax


Server_GetLongCallDefault()
Remarks
Get the default long call time for crashdetect. May not be the current setting. Simply stores the current value, resets it, restores the current and returns the old version.


Estimated stack usage
1 cells



Server_GetLongCallTime:


Syntax


Server_GetLongCallTime()
Returns
The current setting (in microseconds) for the slow code warning threshold. Or 0 if there is none.


Estimated stack usage
1 cells



Server_GetServerString:


Syntax


Server_GetServerString(version[], os[], vlen, olen)

Parameters


Name	Info
version	[]
os	[]
vlen	
olen	

Returns
The includes used to build this script, as a string.


Remarks
The includes used were taken as a proxy for the server version, but they are not a good substitute, hence this function is deprecated.


Depends on
Script_GetIncludesString
Estimated stack usage
7 cells



Server_GetServerVersion:


Syntax


Server_GetServerVersion()
Returns
The includes used to build this script.


Remarks
The includes used were taken as a proxy for the server version, but they are not a good substitute, hence this function is deprecated.


Depends on
Script_GetIncludesVersion
Estimated stack usage
3 cells



Server_GetStartDateTime:


Syntax


Server_GetStartDateTime(&year, &month, &day, &hour, &minute, &second)

Parameters


Name	Info
year	&
month	&
day	&
hour	&
minute	&
second	&

Remarks
Get the start time of the script, previously determined by ScriptInit_GetStartTime, as a set of six components for time and date.


Depends on
YSI_gsStartDMY
YSI_gsStartHMS
Estimated stack usage
1 cells



Server_GetStartTime:


Syntax


Server_GetStartTime()
Remarks
Get the start time of the script, previously determined by ScriptInit_GetStartTime, as a unix timestamp.


Depends on
YSI_gsStartTime
Estimated stack usage
1 cells



Server_HasDetectAddr0:


Syntax


Server_HasDetectAddr0()
Tag
bool:


Remarks
true if crashdetect is able to warn for writes to address naught.


Depends on
false
Estimated stack usage
1 cells



Server_HasLongCallControl:


Syntax


Server_HasLongCallControl()
Tag
bool:


Remarks
Is a version of the crashdetect plugin loaded that we can control long call detection in via registers. There were several releases where this just didn't work properly.


Depends on
Server_DisableLongCall
Server_EnableLongCall
Server_IsLongCallEnabled
false
true
Estimated stack usage
3 cells



Server_IsDetectAddr0Enabled:


Syntax


Server_IsDetectAddr0Enabled()
Tag
bool:


Returns
true if crashdetect will warn for writes to address naught.


Depends on
false
Estimated stack usage
1 cells



Server_IsFilterscript:


Syntax


Server_IsFilterscript()
Tag
bool:


Returns
true if this script is determined to be a filterscript at runtime.


Depends on
YSI_FILTERSCRIPT
Estimated stack usage
1 cells



Server_IsLinuxCompiler:


Syntax


Server_IsLinuxCompiler()
Tag
bool:


Returns
true if this script was compiled with a Linux compiler.


Depends on
false
Estimated stack usage
1 cells



Server_IsLinuxHost:


Syntax


Server_IsLinuxHost()
Tag
bool:


Returns
true if this script is running on a Linux server currently.


Depends on
__cod
__dat
Estimated stack usage
2 cells



Server_IsLongCallEnabled:


Syntax


Server_IsLongCallEnabled()
Tag
bool:


Returns
true if long call (slow code) detection is active.


Remarks
Check if the crashdetect plugin exists, and long call detection is enabled.


Depends on
false
Estimated stack usage
1 cells



Server_IsOpenMP:


Syntax


Server_IsOpenMP()
Tag
bool:


Returns
true if this script is running on an open.mp server currently.


Remarks

Depends on
__flg
false
Estimated stack usage
1 cells



Server_IsSAMP:


Syntax


Server_IsSAMP()
Tag
bool:


Returns
true if this script is running on a SA:MP server currently.


Depends on
__flg
false
Estimated stack usage
1 cells



Server_IsWindowsCompiler:


Syntax


Server_IsWindowsCompiler()
Tag
bool:


Returns
true if this script was compiled with a Windows compiler.


Depends on
true
Estimated stack usage
1 cells



Server_IsWindowsHost:


Syntax


Server_IsWindowsHost()
Tag
bool:


Returns
true if this script is running on a Windows server currently.


Depends on
__cod
__dat
Estimated stack usage
2 cells



Server_JITComplete:


Syntax


Server_JITComplete()
Tag
bool:


Returns
true if the JIT plugin has completed compilation.


Depends on
E_SCRIPTINIT_STATE_JITED
E_SCRIPTINIT_STATE_NONE
YSI_g_sScriptInitState
Estimated stack usage
1 cells



Server_ResetLongCallTime:


Syntax


Server_ResetLongCallTime()
Remarks
Set the slow code threshold back to the default value.


Estimated stack usage
1 cells



Server_RestartLongCall:


Syntax


Server_RestartLongCall()
Remarks
Restart the current function's long call timer, if crashdetect exists. So the detection of slow code will only account for execution time after this point.


Estimated stack usage
1 cells



Server_SetLongCallTime:


Syntax


Server_SetLongCallTime(usTime)

Parameters


Name	Info
usTime	The time in microseconds.

Remarks
Set the time that crashdetect will use when detecting slow functions. Anything executing for longer than this time will trigger a warning.


Estimated stack usage
1 cells


