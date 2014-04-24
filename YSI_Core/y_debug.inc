/**--------------------------------------------------------------------------**\
					==============================
					Y Sever Includes - Debug Setup
					==============================
Description:
	Ensures debug levels are set and defines debug functions.
	
	General debug levels:
	
	0 - No debug information.
	1 - Callbacks and timers.
	2 - Remote functions.
	3 - Stock functions.
	4 - Static functions.
	5 - Code.
	6 - Loops.
	7 - Extra loop code.
	
	If you use P:0 you get an optional debug print controlled by the global
	state ysi_debug - which is either on or off.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI debug include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
	Thanks:
		JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
		ZeeX - Very productive conversations.
		koolk - IsPlayerinAreaEx code.
		TheAlpha - Danish translation.
		breadfish - German translation.
		Fireburn - Dutch translation.
		yom - French translation.
		50p - Polish translation.
		Zamaroht - Spanish translation.
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	1.0
Changelog:
	06/08/10:
		Added new syntax.
		Added level 0 debugging with state controlled functions.
	15/04/07:
		First version.
Functions:
	Public:
		-
	Core:
		-
	Stock:
		-
	Static:
		-
	Inline:
		Debug_Code - Runs defined code if a certain level is active.
		Debug_Print - Prints the formatted string provided at the given level.
	API:
		-
Callbacks:
	-
Definitions:
	P:<0-6> - Print a message.
	P:C - Run debug code.
	P:E - Print an error message.
	P:W - Print a warning message.
Enums:
	-
Macros:
	-
Tags:
	-
Variables:
	Global:
		-
	Static:
		-
Commands:
	-
Compile options:
	_DEBUG - Debugging level to use.
Operators:
	-
</remarks>
\**--------------------------------------------------------------------------**/

#if defined _INC_y_debug
	#endinput
#endif
#define _INC_y_debug

#include "..\YSI_Internal\y_version"

#include "..\YSI_Internal\y_funcinc"

#include "..\YSI_Server\y_scriptinit"

#if !defined _DEBUG
	#define _DEBUG 0
#endif

stock YSI_gDebugLevel = 0;

#define P:%1(%2); Debug_Print%1(%2);
#define C:%1(%2); Debug_Code%1(%2);

/**--------------------------------------------------------------------------**\
<summary>Debug_Code</summary>
<param name="level">Debug level to run the code at.</param>
<param name="code">Code to run.</param>
<returns>
	-
</returns>
<remarks>
	Code is not a variable, it's a code chunk and may be written as so:
	
	Debug_Code1(if (bla == 2) { bla++; printf("%d", bla); });
	
	The code must all be on one line to avoid errors.
	This isn't really a function as the first parameter is part of the name.
</remarks>
\**--------------------------------------------------------------------------**/

#if _DEBUG == -1
	#define Debug_Code1(%1); { if (YSI_gDebugLevel >= 1) { %1 }}
	#define Debug_Code2(%1); { if (YSI_gDebugLevel >= 2) { %1 }}
	#define Debug_Code3(%1); { if (YSI_gDebugLevel >= 3) { %1 }}
	#define Debug_Code4(%1); { if (YSI_gDebugLevel >= 4) { %1 }}
	#define Debug_Code5(%1); { if (YSI_gDebugLevel >= 5) { %1 }}
	#define Debug_Code6(%1); { if (YSI_gDebugLevel >= 6) { %1 }}
	#define Debug_Code7(%1); { if (YSI_gDebugLevel >= 7) { %1 }}
#else
	#if _DEBUG >= 1
		#define Debug_Code1(%1); %1
	#else
		#define Debug_Code1(%1);
	#endif
	
	#if _DEBUG >= 2
		#define Debug_Code2(%1); %1
	#else
		#define Debug_Code2(%1);
	#endif
	
	#if _DEBUG >= 3
		#define Debug_Code3(%1); %1
	#else
		#define Debug_Code3(%1);
	#endif
	
	#if _DEBUG >= 4
		#define Debug_Code4(%1); %1
	#else
		#define Debug_Code4(%1);
	#endif
	
	#if _DEBUG >= 5
		#define Debug_Code5(%1); %1
	#else
		#define Debug_Code5(%1);
	#endif
	
	#if _DEBUG >= 6
		#define Debug_Code6(%1); %1
	#else
		#define Debug_Code6(%1);
	#endif
	
	#if _DEBUG >= 7
		#define Debug_Code7(%1); %1
	#else
		#define Debug_Code7(%1);
	#endif
#endif

#if _DEBUG != 0
	#define Debug_CodeX(%1); %1
#else
	#define Debug_CodeX(%1);
#endif

/**--------------------------------------------------------------------------**\
<summary>Debug_Print</summary>
<param name="level">Debug level to print at.</param>
<param name="format[]">Format.</param>
<param name="..."></param>
<returns>
	-
</returns>
<remarks>
	This isn't really a function as the first parameter is part of the name:
	
	Debug_Print4("variables: %d, %d", i, j);
</remarks>
\**--------------------------------------------------------------------------**/

#if _DEBUG == -1
	#define Debug_Print1(%1); { if (YSI_gDebugLevel >= 1) printf(%1); }
	#define Debug_Print2(%1); { if (YSI_gDebugLevel >= 2) printf(%1); }
	#define Debug_Print3(%1); { if (YSI_gDebugLevel >= 3) printf(%1); }
	#define Debug_Print4(%1); { if (YSI_gDebugLevel >= 4) printf(%1); }
	#define Debug_Print5(%1); { if (YSI_gDebugLevel >= 5) printf(%1); }
	#define Debug_Print6(%1); { if (YSI_gDebugLevel >= 6) printf(%1); }
	#define Debug_Print7(%1); { if (YSI_gDebugLevel >= 7) printf(%1); }
#else
	#if _DEBUG >= 1
		#define Debug_Print1(%1); printf(%1);
	#else
		#define Debug_Print1(%1);
	#endif
	
	#if _DEBUG >= 2
		#define Debug_Print2(%1); printf(%1);
	#else
		#define Debug_Print2(%1);
	#endif
	
	#if _DEBUG >= 3
		#define Debug_Print3(%1); printf(%1);
	#else
		#define Debug_Print3(%1);
	#endif
	
	#if _DEBUG >= 4
		#define Debug_Print4(%1); printf(%1);
	#else
		#define Debug_Print4(%1);
	#endif
	
	#if _DEBUG >= 5
		#define Debug_Print5(%1); printf(%1);
	#else
		#define Debug_Print5(%1);
	#endif
	
	#if _DEBUG >= 6
		#define Debug_Print6(%1); printf(%1);
	#else
		#define Debug_Print6(%1);
	#endif
	
	#if _DEBUG >= 7
		#define Debug_Print7(%1); printf(%1);
	#else
		#define Debug_Print7(%1);
	#endif
#endif

#define Debug_PrintE(%1); \
	Debug_Print0("\7\7\7*** YSI Error: " #%1);

#define Debug_PrintW(%1); \
	Debug_Print0("\7*** YSI Warning: " #%1);

#define Debug_PrintI(%1); \
	Debug_Print0("*** YSI Info: " #%1);

#define Debug_PrintF(%1); \
	Debug_Print0("\7\7\7\7\7*** YSI Fatal Error: " #%1);

#define Debug_PrintC(%1); \
	Debug_CodeX(%1);

stock Debug_Print0(const str[], {Float,_}:...) <ysi_debug : on>
{
	#emit STACK        8
	#emit SYSREQ.C     printf
	#emit STACK        0xFFFFFFF8
	#pragma unused str
	return 0;
}

stock Debug_Print0(const str[], {Float,_}:...) <>
{
	#pragma unused str
	return 0;
}

stock Debug_PrintArray(arr[], size)
{
	new
		str[96];
	switch (size)
	{
		case 0:
			str = "<>";
		case 1:
			format(str, sizeof (str), "<%d>", arr[0]);
		case 2:
			format(str, sizeof (str), "<%d, %d>", arr[0], arr[1]);
		case 3:
			format(str, sizeof (str), "<%d, %d, %d>", arr[0], arr[1], arr[2]);
		case 4:
			format(str, sizeof (str), "<%d, %d, %d, %d>", arr[0], arr[1], arr[2], arr[3]);
		case 5:
			format(str, sizeof (str), "<%d, %d, %d, %d, %d>", arr[0], arr[1], arr[2], arr[3], arr[4]);
		default:
			format(str, sizeof (str), "<%d, %d, %d, %d, %d, ... (+ %d)>", arr[0], arr[1], arr[2], arr[3], arr[4], size - 5);
	}
	return str;
}

public OnScriptInit()
{
	Debug_SetState();
	new
		s;
	// Test the ADDRESS of the variable, not the value.
	#emit CONST.pri YSI_FILTERSCRIPT
	#emit STOR.S.pri s
	if (s)
	{
		//goto Debug_OnScriptInit_no_fault();
		#if defined Debug_OnScriptInit
			return Debug_OnScriptInit();
		#else
			return 1;
		#endif
	}
	P:F("YSI_FILTERSCRIPT == 0");
	while (s != 10000000) ++s;
	#emit CONST.pri 0
	#emit SCTRL     6
	return 1;
}

static stock Debug_SetState() <ysi_debug : off>
{
}

static stock Debug_SetState() <>
{
	state ysi_debug : on;
}

#undef OnScriptInit
#define OnScriptInit Debug_OnScriptInit
#if defined Debug_OnScriptInit
	forward Debug_OnScriptInit();
#endif

stock DebugLevel(level = -1)
{
	if (0 <= level <= 7)
	{
		YSI_gDebugLevel = level;
	}
	return YSI_gDebugLevel;
}

