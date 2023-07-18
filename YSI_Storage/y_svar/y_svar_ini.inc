/*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (c) 2022
	the Initial Developer. All Rights Reserved.

Contributors:
	Y_Less
	koolk
	JoeBullet/Google63
	g_aSlice/Slice
	Misiur
	samphunter
	tianmeta
	maddinat0r
	spacemud
	Crayder
	Dayvison
	Ahmad45123
	Zeex
	irinel1996
	Yiin-
	Chaprnks
	Konstantinos
	Masterchen09
	Southclaws
	PatchwerkQWER
	m0k1
	paulommu
	udan111
	Cheaterman

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
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

// Third "uvar" version.
#define _YS@LE@E%0>
#define _YS@LT@E%0> ;

#define _YS@LM:%0[%1][%2] STRIP_NUMBERS:%0[%1]|||%2:0|||,sizeof(%0[])

// Needs two levels of indirection to strip the excess commas (,%0,%1).
#define _YS@LO(,%0,[%2]%4) %0@yS_();public %0@yS_(){M@(#...#%0,_:%2,STRIP_NUMBERS:_YS@LM:%0|||%2:0|||%4);}

#define _YS@LE%0[%3]%4,%2> _YS@LO(%0,[%3]%4) _YS@LE%2>

// Recursive local default string definition.
#define _YS@LJ(,%0,%2) %0%2
#define _YS@LT%0[%3]%4,%2> ,_YS@LJ(%0,[%3]%4)_YS@LT%2>
#define _YS@LA%0[%3]%4,%2> _YS@LJ(%0,[%3]%4)_YS@LT%2>

// Entry point for the loaders.  The structure of stored pvar data is:
//  
//  [0] - Pointer to next pvar in list (-1 for end).
//  [1] - Pointer to data.
//  [2] - Size of enum.
//  [3] - Start of name.
//  
//#define svar%0[%1]%2; stock _YS@LA,%0[%1]%2@E>_YS@LE,%0[%1]%2@E>
#define svar%0; stock _YS@LA,%0,@E>_YS@LE,%0,@E>

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
	YSI_g_sLastName[FUNCTION_LENGTH] = "\1\0",
	YSI_g_sLastAddr = 0,
	YSI_g_sLastSize = 0;

forward _y_svar_include_@();

public _y_svar_include_@()
{
	//MemSet(YSI_EMPTY, 0, 0, 0);
	INI_WriteArray(INI_NO_FILE, YSI_EMPTY, YSI_EMPTY, 0);
}

static stock Svar_FindData(const name[], const data[])
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
			StrCpy(YSI_g_sLastName, name);
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
	Debug_Print7("_Config_Load_y_svar called: %s %s", name, value);
	// See what the name of the loaded data was.
	new
		pos = strfind(name, "-");
	if (pos == -1)
	{
		if (strcmp(name, YSI_g_sLastName))
		{
			// Find the data.
			Svar_FindData(name, YSI_EMPTY);
		}
		if (YSI_g_sLastAddr == -1)
		{
			return;
		}
		// Check that the data is the right size.
		Debug_Code1{if (strval(value) != YSI_g_sLastSize) Debug_Error("uvar data changed in %s", YSI_g_sLastName);}
	}
	else
	{
		// Get the position in the array of this data.
		name[pos] = '\0';
		pos = strval(name[pos + 1]) * ((MAX_INI_ENTRY_TEXT - 1) / 16 * 3);
		if (strcmp(name[2], YSI_g_sLastName, false))
		{
			// Find the data.
			Svar_FindData(name[2], YSI_EMPTY);
		}
		if (YSI_g_sLastAddr == -1)
		{
			return;
		}
		// This must come BEFORE the "#emit" due to bugs with braces.
		new
			len = strlen(value),
			idx = 0;
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

/*-------------------------------------------------------------------------*//**
 * <param name="vardata">Handle to the memory location in which to store info.</param>
 * <param name="dataSize">The size of the array (first dimension).</param>
 * <param name="pointer">The start of the data.</param>
 * <param name="ds2">The second dimension of the data.</param>
 * <remarks>
 *   This function modifies "vardata" well beyond its original limits to contain
 *   information on the structure of the enum used to define "val".  This code
 *   uses the name and size information passed in the additional parameters as
 *   strings, and makes assumptions about how the compiler lays out memory to
 *   combine all the passed strings in to one big string in what could be ROM,
 *   but in SA:MP isn't.  This takes a human readable(ish) description of the
 *   array elements and converts it in to a much simpler to read format for the
 *   computer to use later when loading and storing data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock M@(volatile const vardata[], dataSize, &pointer, ds2 = 1)
{
	dataSize *= ds2;
	Debug_Print2("M@ called");
	new
		sAddr = 0;
	// Store the basic data, including linked-list pointers and a pointer to the
	// location at which the data is stored.
	#emit LOAD.S.pri vardata
	#emit STOR.S.pri sAddr
	printf(YSI_EMPTY, YSI_g_sFirstUVarData);
	#emit LOAD.pri   YSI_g_sFirstUVarData
	#emit SREF.S.pri sAddr
	YSI_g_sFirstUVarData = sAddr;
	sAddr += cellbytes;
	#emit LOAD.S.pri pointer
	#emit SREF.S.pri sAddr
	sAddr += cellbytes;
	#emit LOAD.S.pri dataSize
	#emit SREF.S.pri sAddr
	Debug_Print5("M@: %d %d %d %d %s", vardata[0], vardata[1], vardata[2], vardata[3], vardata[4]);
	Debug_Print5("M@: %d", YSI_g_sFirstUVarData);
}

HOOK__ OnScriptExit()
{
	Svar_Save();
}

Svar_Save()
{
	Debug_Print1("Svar_OnScriptExit called");
	// Loop through all the player data items and write them to a file.
	new
		INI:__fwrite = INI_Open("YSI/" #MODE_NAME "_config.ini");
	if (__fwrite == INI_NO_FILE)
	{
		Debug_Error("y_svar could not open data file for " #MODE_NAME);
		return;
	}
	INI_SetTag(__fwrite, "y_svar");
	new
		p = YSI_g_sFirstUVarData,
		temp = 0;
	while (p != -1)
	{
		// DO NOT CHANGE THE CODE BELOW HERE!!!
		// Get the data size.
		#emit LOAD.S.pri p
		#emit ADD.C      __2_cells
		#emit STOR.S.pri temp
		#emit LREF.S.pri temp
		#emit PUSH.pri
		// Get the data pointer.
		#emit LOAD.S.pri p
		#emit ADD.C      __1_cell
		#emit STOR.S.pri temp
		#emit LREF.S.pri temp
		#emit PUSH.pri
		// Get the function name.
		#emit LOAD.S.pri p
		#emit ADD.C      __3_cells
		#emit PUSH.pri
		// Save the next pointer.
		#emit LREF.S.pri p
		#emit STOR.S.pri p
		// Now push the size of data put on the stack.
		#emit PUSH.S     __fwrite
		#emit PUSH.C     __4_cells
		// Now get the return address and push it.
		#emit LCTRL      __cip
		#emit ADD.C      __9_cells
		#emit LCTRL      __jit_jump
		#emit PUSH.pri
		// Call "Player_WriteArray" directly.
		#emit CONST.pri  INI_WriteArray
		#emit SCTRL      __cip
		// DO NOT CHANGE THE CODE ABOVE HERE!!!
	}
	INI_Close(__fwrite);
}

public OnCodeInit()
{
	Debug_Print1("hook Svar_OnScriptInit called");
	// List them all.
	YSI_g_sFirstUVarData = -1;
	// Call all @yS_ functions to get all required data.
	new
		idx = 0,
		buffer = 0;
	while ((idx = AMX_GetPublicPointerSuffix(idx, buffer, _A<@yS_>)))
	{
		#emit PUSH.C     0
		#emit LCTRL      __cip
		#emit ADD.C      __9_cells
		#emit LCTRL      __jit_jump
		#emit PUSH.pri
		#emit LOAD.S.pri buffer
		#emit SCTRL      __cip
	}
	// We don't need any of the reset code, but we do need the loading code.
	#if !defined _YSI_ONLY_ONE_CONFIG_LOAD
		#define _YSI_ONLY_ONE_CONFIG_LOAD
		INI_ParseFile("YSI/" #MODE_NAME "_config.ini", "_Config_Load_%s");
	#endif
	
	#if defined SVar_OnCodeInit
		SVar_OnCodeInit();
	#endif
	return 1;
}

#undef OnCodeInit
#define OnCodeInit SVar_OnCodeInit
#if defined SVar_OnCodeInit
	forward SVar_OnCodeInit();
#endif

