/*----------------------------------------------------------------------------*\
					=================================
					 y_svar - Automatic data saving.
					=================================
Description:
	Declares data to be automatically saved and loaded for the whole server.
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
	
	The Original Code is the YSI utils include.
	
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
	0.1
Changelog:
	25/02/12:
		First version.
Functions:
	Stock:
		-
	Inline:
		-
Variables:
	Global:
		-
\*----------------------------------------------------------------------------*/

// y_uvars

#if !defined MODE_NAME
	#error Please define "MODE_NAME" before including y_svar.
#endif

#include "internal\y_version"

#include "y_amx"
#include "y_debug"
#include "y_utils"

#include "y_ini"

#include "y_hooks"

#include "internal\y_stripnumbers"

// Third "uvar" version.
#define _YS@LE@E%0>
#define _YS@LT@E%0> ;

// Needs two levels of indirection to strip the excess commas (,%0,%1).
#define _YS@LO(,%0,%2) %0@yS_();public %0@yS_(){M@(#...#%0,_:%2,STRIP_NUMBERS:%0|||%2:0|||);}

#define _YS@LE%0[%3]%2> _YS@LO(%0,%3) _YS@LE%2>

// Recursive local default string definition.
#define _YS@LJ(,%0,%2) %0[%2]
#define _YS@LT%0[%3]%2> ,_YS@LJ(%0,%3)_YS@LT%2>
#define _YS@LA%0[%3]%2> _YS@LJ(%0,%3)_YS@LT%2>

// Entry point for the loaders.  The structure of stored pvar data is:
//  
//  [0] - Pointer to next pvar in list (-1 for end).
//  [1] - Pointer to data.
//  [2] - Size of enum.
//  [3] - Start of name.
//  
#define svar%0[%1]%2; stock _YS@LA,%0[%1]%2@E>_YS@LE,%0[%1]%2@E>

//%0@yS_();public%0@yS_()M@(_:%0,#....#%0 _YA@LT %1,@E|||);

// This is a structure defining the data stored on the enum structure.
/*enum E_USERS_FAKE_DATA
{
	E_USERS_FAKE_DATA_NEXT,
	E_USERS_FAKE_DATA_DATA,
	E_USERS_FAKE_DATA_LEN,
	E_USERS_FAKE_DATA_STR[2]
}*/

static stock
	YSI_g_sFirstUVarData = -1,
	// These three variables are used to speed up data loading through caching.
	YSI_g_sLastName[32] = "\1\0",
	YSI_g_sLastAddr,
	YSI_g_sLastSize;

forward _y_svar_include_@();

public _y_svar_include_@()
{
	//memset("", 0, 0, 0);
	INI_WriteArray(INI_NO_FILE, "", "", 0);
}

static stock Svar_FindData(const name[], data[])
{
	// This function gets passed an empty string so that we can use "data" as a
	// string, while secretly changing the pointer in AMX code.
	new
		p = YSI_g_sFirstUVarData;
	while (p != -1)
	{
		// Modify our data pointer.
		#emit LOAD.S.pri p
		#emit STOR.S.pri data
		if (!strcmp(data[3], name))
		{
			strcpy(YSI_g_sLastName, name);
			YSI_g_sLastSize = data[2];
			YSI_g_sLastAddr = data[1];
			//printf("found %s, %d, %d, %d", YSI_g_sLastName, YSI_g_sLastSize, YSI_g_sLastPlayers, YSI_g_sLastAddr);
			return;
		}
		p = data[0];
	}
	YSI_g_sLastAddr = -1;
}

forward _Config_Load_y_svar(name[], value[]);

public _Config_Load_y_svar(name[], value[])
{
	P:1("_Config_Load_y_svar called: %s %s", name, value);
	// See what the name of the loaded data was.
	new
		pos = strfind(name, "-");
	if (pos == -1)
	{
		if (strcmp(name, YSI_g_sLastName))
		{
			// Find the data.
			Svar_FindData(name, "");
		}
		if (YSI_g_sLastAddr == -1)
		{
			return;
		}
		// Check that the data is the right size.
		P:C(if (strval(value) != YSI_g_sLastSize) P:E("uvar data changed in %s", YSI_g_sLastName););
	}
	else
	{
		// Get the position in the array of this data.
		name[pos] = '\0';
		pos = strval(name[pos + 1]) * ((MAX_INI_ENTRY_TEXT - 1) / 16 * 3);
		if (strcmp(name[2], YSI_g_sLastName, false))
		{
			// Find the data.
			Svar_FindData(name[2], "");
		}
		if (YSI_g_sLastAddr == -1)
		{
			return;
		}
		// This must come BEFORE the "#emit" due to bugs with braces.
		new
			len = strlen(value),
			idx;
		// Save this pointer to an array variable for simplicity.
		#emit LOAD.pri   YSI_g_sLastAddr
		#emit STOR.S.pri name
		// "pos" holds the offset of this data.  "value" always holds a
		// whole number of cells worth of data.
		while (idx + 16 <= len)
		{
			// Do the large chunks.
			name[pos++] = ((value[idx +  0] - '>') << 26)
						| ((value[idx +  1] - '>') << 20)
						| ((value[idx +  2] - '>') << 14)
						| ((value[idx +  3] - '>') <<  8)
						| ((value[idx +  4] - '>') <<  2)
						| ((value[idx +  5] - '>') >>  4);
			// Second cell.
			name[pos++] = ((value[idx +  5] - '>') << 28)
						| ((value[idx +  6] - '>') << 22)
						| ((value[idx +  7] - '>') << 16)
						| ((value[idx +  8] - '>') << 10)
						| ((value[idx +  9] - '>') <<  4)
						| ((value[idx + 10] - '>') >>  2);
			// Third cell.
			name[pos++] = ((value[idx + 10] - '>') << 30)
						| ((value[idx + 11] - '>') << 24)
						| ((value[idx + 12] - '>') << 18)
						| ((value[idx + 13] - '>') << 12)
						| ((value[idx + 14] - '>') <<  6)
						| ((value[idx + 15] - '>') >>  0);
			// 16 characters are used to encode 3 cells (12 bytes) by only
			// saving 6 bits per character to ensure that they are always
			// valid characters.  7 bits may be easier, but would mean the
			// encoding fit less well to small numbers of cells.
			idx += 16;
		}
		if (idx + 6 <= len)
		{
			// Save any few extra bytes.
			name[pos++] = ((value[idx +  0] - '>') << 26)
						| ((value[idx +  1] - '>') << 20)
						| ((value[idx +  2] - '>') << 14)
						| ((value[idx +  3] - '>') <<  8)
						| ((value[idx +  4] - '>') <<  2)
						| ((value[idx +  5] - '>') >>  4);
			if (idx + 11 <= len)
			{
				name[pos++] = ((value[idx +  5] - '>') << 28)
							| ((value[idx +  6] - '>') << 22)
							| ((value[idx +  7] - '>') << 16)
							| ((value[idx +  8] - '>') << 10)
							| ((value[idx +  9] - '>') <<  4)
							| ((value[idx + 10] - '>') >>  2);
			}
		}
	}
}

/*----------------------------------------------------------------------------*\
Function:
	M@
Params:
	val[][] - Handle to the PAWN data array.
	volatile vardata[] - Handle to the memory location in which to store info.
	{K@, L@, M@, N@, _}:... - Array slot size information.
Return:
	-
Notes:
	This function modifies "vardata" well beyond its original limits to contain
	information on the structure of the enum used to define "val".  This code
	uses the name and size information passed in the additional parameters as
	strings, and makes assumptions about how the compiler lays out memory to
	combine all the passed strings in to one big string in what could be ROM,
	but in SA:MP isn't.  This takes a human readable(ish) description of the
	array elements and converts it in to a much simpler to read format for the
	computer to use later when loading and storing data.
\*----------------------------------------------------------------------------*/

stock M@(volatile const vardata[], dataSize, &pointer)
{
	P:2("M@ called");
	new
		sAddr;
	// Store the basic data, including linked-list pointers and a pointer to the
	// location at which the data is stored.
	#emit LOAD.S.pri vardata
	#emit STOR.S.pri sAddr
	printf("", YSI_g_sFirstUVarData);
	#emit LOAD.pri   YSI_g_sFirstUVarData
	#emit SREF.S.pri sAddr
	YSI_g_sFirstUVarData = sAddr;
	sAddr += 4;
	#emit LOAD.S.pri pointer
	#emit SREF.S.pri sAddr
	sAddr += 4;
	#emit LOAD.S.pri dataSize
	#emit SREF.S.pri sAddr
	P:5("M@: %d %d %d %d %s", vardata[0], vardata[1], vardata[2], vardata[3], vardata[4]);
	P:5("M@: %d", YSI_g_sFirstUVarData);
}

hook OnScriptExit()
{
	P:1("Svar_OnScriptExit called");
	// Loop through all the player data items and write them to a file.
	new
		INI:__fwrite = INI_Open("YSI/" #MODE_NAME "_config.ini");
	if (__fwrite == INI_NO_FILE)
	{
		P:E("y_svar could not open data file for " #MODE_NAME);
		return;
	}
	INI_SetTag(__fwrite, "y_svar");
	new
		p = YSI_g_sFirstUVarData,
		temp;
	while (p != -1)
	{
		// DO NOT CHANGE THE CODE BELOW HERE!!!
		// Get the data size.
		#emit LOAD.S.pri p
		#emit ADD.C      8
		#emit STOR.S.pri temp
		#emit LREF.S.pri temp
		#emit PUSH.pri
		// Get the data pointer.
		#emit LOAD.S.pri p
		#emit ADD.C      4
		#emit STOR.S.pri temp
		#emit LREF.S.pri temp
		#emit PUSH.pri
		// Get the function name.
		#emit LOAD.S.pri p
		#emit ADD.C      12
		#emit PUSH.pri
		// Save the next pointer.
		#emit LREF.S.pri p
		#emit STOR.S.pri p
		// Now push the size of data put on the stack.
		#emit PUSH.S     __fwrite
		#emit PUSH.C     16
		// Now get the return address and push it.
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		// Call "Player_WriteArray" directly.
		#emit CONST.pri  INI_WriteArray
		#emit SCTRL      6
		// DO NOT CHANGE THE CODE ABOVE HERE!!!
	}
	INI_Close(__fwrite);
}

hook OnScriptInit()
{
	P:1("hook Svar_OnScriptInit called");
	// List them all.
	YSI_g_sFirstUVarData = -1;
	// Call all @yS_ functions to get all required data.
	new
		idx,
		buffer;
	while ((idx = AMX_GetPublicPointerSuffix(idx, buffer, _A<@yS_>)))
	{
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri buffer
		#emit SCTRL      6
	}
	// We don't need any of the reset code, but we do need the loading code.
	#if !defined _YSI_ONLY_ONE_CONFIG_LOAD
		#define _YSI_ONLY_ONE_CONFIG_LOAD
		INI_ParseFile("YSI/" #MODE_NAME "_config.ini", "_Config_Load_%s");
	#endif
}
