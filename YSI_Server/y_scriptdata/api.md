y_scriptdata - v1.0
Utility functions for information about how and when the script was built.
(c) 2022 YSI contibutors, licensed under MPL 1.1

This file provides OnScriptInit and OnScriptExit which are called at the start and end of the current script, regardless of what the type of the script is. It also provides IS_FILTERSCRIPT as a (partial) replacement for FILTERSCRIPT which detects what the mode is at runtime for a more reliable system (but it is a run-time variable, not a compile-time constant).




Functions


Script_CacheLoaded:


Syntax


Script_CacheLoaded()
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



Script_CacheSaved:


Syntax


Script_CacheSaved()
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



Script_GetCompilerCodepage:


Syntax


Script_GetCompilerCodepage(version[], vlen)

Parameters


Name	Info
version	[]
vlen	

Returns
The codepage used to build this script, as a string.


Depends on
strcat
Estimated stack usage
5 cells



Script_GetCompilerString:


Syntax


Script_GetCompilerString(version[], os[], vlen, olen)

Parameters


Name	Info
version	[]
os	[]
vlen	
olen	

Returns
The version of the compiler used to build this script, as a string.


Depends on
FIXES_format
YSI_gscWindows
__Pawn
__PawnBuild
strcat
Estimated stack usage
11 cells



Script_GetCompilerVersion:


Syntax


Script_GetCompilerVersion()
Returns
The version of the compiler used to build this script.


Depends on
__Pawn
__PawnBuild
Estimated stack usage
1 cells



Script_GetIncludesString:


Syntax


Script_GetIncludesString(version[], vlen)

Parameters


Name	Info
version	[]
vlen	

Returns
The includes used to build this script, as a string.


Depends on
FIXES_format
__SAMP_INCLUDES_VERSION
Estimated stack usage
7 cells



Script_GetIncludesVersion:


Syntax


Script_GetIncludesVersion()
Returns
The includes used to build this script.


Remarks
Version examples:

0.3.DL R1 - 03D010
0.3.7 R3 - 037030
0.3.7 R2-2 - 037022
0.3.7 R1-2 - 037012
0.3.7 - 037000
0.3z R4 - 030740
0.3z R3 - 030730
0.3z R2-1 - 030721
0.3z R1-2 - 030712
0.3z - 030700
0.3x R2 patch 1 - 030621
0.3x R2 - 030620
0.3x R1-2 - 030612
0.3x - 030600
0.3e - 030500
0.3d - 030400
0.3c - 030300
0.3b - 030200
0.3a - 030100
0.2X - 02A000
0.2.2 R3 - 022300

Rough rules:


Uses (roughtly) BCD. Special versions are denoted outside 0-9.



  0.1.2c R4-5  | | ||  | |  0 1 23  4 5  =  0x012345  
(assuming c is the third revision)


0.2X becomes 02A000 because it is basically 0.2.3, but not, while higher than 0.2.2 so can't be 020400 (for example). Also, its a capital letter, so doesn't use the revision method.


P.S. Making a consistent scheme for SA:MP versions is REALLY hard.


open.mp releases can use `A` as the first digit.

Estimated stack usage
1 cells



Script_GetStartString:


Syntax


Script_GetStartString(output[], size)

Parameters


Name	Info
output	[]
size	

Returns
The time the script started, as a string.


Depends on
FIXES_format
Server_GetStartDateTime
Estimated stack usage
17 cells



Script_IsFilterscript:


Syntax


Script_IsFilterscript()
Tag
bool:


Returns
true if this script is determined to be a filterscript at runtime.


Estimated stack usage
1 cells



Script_IsGameMode:


Syntax


Script_IsGameMode()
Tag
bool:


Returns
true if this script is determined to be a gamemode at runtime.


Estimated stack usage
1 cells



Script_IsLinuxCompiler:


Syntax


Script_IsLinuxCompiler()
Tag
bool:


Returns
true if this script was compiled with a Linux compiler.


Estimated stack usage
1 cells



Script_IsWindowsCompiler:


Syntax


Script_IsWindowsCompiler()
Tag
bool:


Returns
true if this script was compiled with a Windows compiler.


Estimated stack usage
1 cells



Script_JITComplete:


Syntax


Script_JITComplete()
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



Server_IsGameMode:


Syntax


Server_IsGameMode()
Tag
bool:


Returns
true if this script is determined to be a gamemode at runtime.


Depends on
YSI_GAMEMODE
Estimated stack usage
1 cells


