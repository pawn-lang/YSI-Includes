y_scriptinit - v1.0
OnScriptInit, OnCodeInit, and equivalent exit functions.
(c) 2022 YSI contibutors, licensed under MPL 1.1

This file provides OnScriptInit and OnScriptExit which are called at the start and end of the current script, regardless of what the type of the script is. It also provides IS_FILTERSCRIPT as a (partial) replacement for FILTERSCRIPT which detects what the mode is at runtime for a more reliable system (but it is a run-time variable, not a compile-time constant).




Functions


ScriptInit_CallOnCodeInit:


Syntax


ScriptInit_CallOnCodeInit(jit, fs)

Parameters


Name	Info
jit	bool We are calling the callback from the JIT plugin.
fs	bool We are calling the callback in a filterscript.

Tag
bool:


Remarks
This is seemingly a lot of code just to call a callback, but it does more than that. Really this is OnScriptInit for this file - it calls other callbacks, dumps debug information, profiles the startup, and caches compilation results. These steps are all done regardless of which callback gets triggered first, hence why the code is abstracted.


Depends on
E_SCRIPTINIT_STATE_RELOAD
FIXES_format
GetTickCount
R@
ScriptInit_CodeInitFuncs_
Server_DisableLongCall
Server_EnableLongCall
Server_FinishIntroPart
Server_PrintIntroMessage
Server_PrintIntroPart
YSI_EMPTY
YSI_SPACE
YSI_g_sScriptInitState
YSI_gscInitMsgD
true
Estimated stack usage
41 cells



ScriptInit_Dump:


Syntax


ScriptInit_Dump(filename[], message[])

Parameters


Name	Info
filename	[] Name of the file to write the dump to.
message	[] Message to show in the console.

Remarks
Write a disassembled version of the current state of the script to a file. This is by far the most powerful debugging technique I've ever had while developing YSI. It is generally called twice - once before OnCodeInit is run, and once after. That callback does all of the assembly-level transformations used to implement many of the advanced YSI features. Thus the two resulting dump files can be used to examine and compare the results of every code rewrite done, and see where things have gone wrong. Plus, if anyone has a complex bug I can ask for those two files and get a very complete view of what their script is trying to do, without needing any of their source.


Depends on
DisasmWrite
FIXES_format
GetYSIScriptfilesDir
PrintAmxHeader
Server_DisableLongCall
Server_EnableLongCall
Server_FinishIntroPart
Server_PrintIntroPart
YSI_SPACE
YSI_gsStartTime
YSI_gscDone
YSI_gscInitMsgC
YSI_gscInitMsgD
fautocleanup
Estimated stack usage
57 cells



ScriptInit_GetStartTime:


Syntax


ScriptInit_GetStartTime()
Remarks
Store the earliest time of this script starting that we can.


Depends on
YSI_gsStartDMY
YSI_gsStartHMS
YSI_gsStartTime
getdate
gettime
Estimated stack usage
13 cells



ScriptInit_PurgeTemporaries:


Syntax


ScriptInit_PurgeTemporaries()
Remarks
Delete temporary files that have reached their maximum age. Related to ftemporary, which only stores files for a limited period.


Depends on
FIXES_fclose
FIXES_fread
FIXES_fseek
FIXES_fwrite
FIXES_strfind
YSI_SPACE
YSI_SetTimer__
YSI_TEMP_FILE_NAME
YSI_gsPurgeTimer
false
fexist
fopen
fremove
ftemporary_
gettime
io_read
io_write
seek_start
strlen
strval
true
Attributes
public
Estimated stack usage
118 cells



Server_FinishIntroMessage:


Syntax


Server_FinishIntroMessage()
Remarks
This is called after all the intro messages have been completed to add padding.


Depends on
YSI_Print__
YSI_SPACE
YSI_gsFirstHeader
true
Estimated stack usage
3 cells



Server_FinishIntroPart:


Syntax


Server_FinishIntroPart()
Remarks
If a box was previously partially written in to with Server_PrintIntroPart this closes the box off at the bottom. It basically just prints a line in the console.


Depends on
YSI_Print__
YSI_gsNewPart
YSI_gscHeader
YSI_gscSpacer
true
Estimated stack usage
3 cells



Server_PrintIntroMessage:


Syntax


Server_PrintIntroMessage(...)

Parameters


Name	Info
...	

Remarks
Every parameter to this function is a string, and they are all shown in order in the console, in a nice box. If this is the first call it also shows the amazing beautiful YSI header first.


Depends on
Server_PrintYSIHeader
YSI_Print__
YSI_SPACE
YSI_VAPrintF
YSI_gsFirstHeader
YSI_gsObnoxiousHeader
YSI_gscHeader
YSI_gscSpacer
__COMPILER_CELL_SHIFT
__frm
cellbytes
false
numargs
Estimated stack usage
7 cells



Server_PrintIntroPart:


Syntax


Server_PrintIntroPart(...)

Parameters


Name	Info
...	

Remarks
Every parameter to this function is a string, and they are all shown in order in the console, in a nice box. Unlike Server_PrintIntroMessage this doesn't close the box, nor does it start a new one if one is already being written in to. Thus this one can append messages within a nice box in the console. If this is the first call it also shows the loved and adored YSI header first.


Depends on
Server_PrintYSIHeader
YSI_Print__
YSI_SPACE
YSI_VAPrintF
YSI_gsFirstHeader
YSI_gsNewPart
YSI_gsObnoxiousHeader
YSI_gscHeader
YSI_gscSpacer
__COMPILER_CELL_SHIFT
__frm
cellbytes
false
numargs
Estimated stack usage
7 cells



Server_PrintYSIHeader:


Syntax


Server_PrintYSIHeader()
Remarks
Print the awesome header that everyone loves in the console. You're welcomes everyone!


Depends on
YSI_Print__
Estimated stack usage
3 cells


