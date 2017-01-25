/**--------------------------------------------------------------------------**\
					=================================
					 y_uvar - Automatic data saving.
					=================================
Description:
	Declares data to be automatically saved and loaded on a per-player basis.
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
		Los - Portuguese translation.
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
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
	
Version:
	0.1.3
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
\**--------------------------------------------------------------------------**/

#if defined _INC_y_uvar
	#endinput
#endif
#define _INC_y_uvar

// y_uvars

#include "..\YSI_Internal\y_version"

#include "..\YSI_Storage\y_amx"
#include "..\YSI_Core\y_debug"
#include "..\YSI_Core\y_utils"

#include "..\YSI_Players\y_users"
#include "..\YSI_Storage\y_ini"

#include "..\YSI_Coding\y_hooks"

#include "..\YSI_Internal\y_stripnumbers"

// Third "uvar" version.
#define _YU@LE@E%0>
#define _YU@LT@E%0> ;

// Needs two levels of indirection to strip the excess commas (,%0,%1).
#define _YU@LO(,%0,%1,%2) %0@yA_();public %0@yA_(){N@(#....#%0,_:%1,_:%2,STRIP_NUMBERS:%0[0]|||%2:0|||);}

#define _YU@LE%0[%1][%3]%2> _YU@LO(%0,%1,%3) _YU@LE%2>

// Recursive local default string definition.
#define _YU@LJ(,%0,%1,%2) %0[%1][%2]
#define _YU@LT%0[%1][%3]%2> ,_YU@LJ(%0,%1,%3)_YU@LT%2>
#define _YU@LA%0[%1][%3]%2> _YU@LJ(%0,%1,%3)_YU@LT%2>

// Entry point for the loaders.  The structure of stored pvar data is:
//  
//  [0] - Pointer to next pvar in list (-1 for end).
//  [1] - Pointer to data.
//  [2] - Number of players.
//  [3] - Size of enum.
//  [4] - Start of name.
//  
// It is VERY important to note that using "%0[0][0]" when calling "N@" instead
// of "%0" gives a DIFFERENT address - we get the address of the first data
// element in the array, not the address of the start of the array pointer table
// which is used to index multi-dimensional arrays when the size is not known
// (which in this case it is).  This makes calculating offsets later possible.
#define uvar%0[%8][%1]%2; stock _YU@LA,%0[%8][%1]%2@E>_YU@LE,%0[%8][%1]%2@E>

//%0@yA_();public%0@yA_()N@(_:%0,#....#%0 _YA@LT %1,@E|||);

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
	YSI_g_sLastPlayers,
	YSI_g_sLastSize;

forward _y_uvar_include_@();

public _y_uvar_include_@()
{
	memset("", 0, 0);
	Player_WriteArray("", "", 0);
}

static stock Uvar_FindData(const name[], data[])
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
		if (!strcmp(data[4], name))
		{
			strcpy(YSI_g_sLastName, name);
			YSI_g_sLastSize = data[3];
			YSI_g_sLastPlayers = data[2];
			YSI_g_sLastAddr = data[1];
			//printf("found %s, %d, %d, %d", YSI_g_sLastName, YSI_g_sLastSize, YSI_g_sLastPlayers, YSI_g_sLastAddr);
			return;
		}
		p = data[0];
	}
	YSI_g_sLastAddr = -1;
}

forward OnUserData[y_uvar](playerid, name[], value[]);
public OnUserData[y_uvar](playerid, name[], value[])
{
	// See what the name of the loaded data was.
	new
		pos = strfind(name, "-");
	if (pos == -1)
	{
		if (strcmp(name, YSI_g_sLastName))
		{
			// Find the data.
			Uvar_FindData(name, "");
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
		//printf("call pos 0");
		name[pos] = '\0';
		pos = strval(name[pos + 1]) * ((MAX_INI_ENTRY_TEXT - 1) / 16 * 3);
		if (strcmp(name[2], YSI_g_sLastName, false))
		{
			// Find the data.
			Uvar_FindData(name[2], "");
		}
		if (YSI_g_sLastAddr == -1)
		{
			return;
		}
		// Get the offset in the array for this player.
		if (playerid < YSI_g_sLastPlayers)
		{
			new
				len = strlen(value),
				idx;
			pos += YSI_g_sLastSize * playerid;
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
}

/**--------------------------------------------------------------------------**\
<summary>N@</summary>
<param name="val[][]">Handle to the PAWN data array.</param>
<param name="volatile vardata[]">Handle to the memory location in which to store info.</param>
<param name="{K@, L@, M@, N@, _}:...">Array slot size information.</param>
<returns>
	-
</returns>
<remarks>
	This function modifies "vardata" well beyond its original limits to contain
	information on the structure of the enum used to define "val".  This code
	uses the name and size information passed in the additional parameters as
	strings, and makes assumptions about how the compiler lays out memory to
	combine all the passed strings in to one big string in what could be ROM,
	but in SA:MP isn't.  This takes a human readable(ish) description of the
	array elements and converts it in to a much simpler to read format for the
	computer to use later when loading and storing data.
	
	The description above is no longer the case.  This code now just saves the
	size of the data, the number of players in the array, the address of the
	data, a pointer to another data set and the name of this data.  This is by
	far much simpler than the old version.
</remarks>
\**--------------------------------------------------------------------------**/

stock N@(volatile const vardata[], playerCount, dataSize, &pointer)
{
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
	#emit LOAD.S.pri playerCount
	#emit SREF.S.pri sAddr
	sAddr += 4;
	#emit LOAD.S.pri dataSize
	#emit SREF.S.pri sAddr
	P:5("N@: %d %d %d %d %s", vardata[0], vardata[1], vardata[2], vardata[3], vardata[4]);
	P:5("N@: %d", YSI_g_sFirstUVarData);
}

hook OnScriptInit()
{
	// List them all.
	YSI_g_sFirstUVarData = -1;
	// Call all @yA_ functions to get all required data.
	new
		idx,
		buffer;
	while ((idx = AMX_GetPublicPointerSuffix(idx, buffer, _A<@yA_>)))
	{
		#emit PUSH.C     0
		#emit LCTRL      6
		#emit ADD.C      28
		#emit PUSH.pri
		#emit LOAD.S.pri buffer
		#emit SCTRL      6
	}
}

/*public OnPlayerLogout(playerid, uid)
{
	#if defined Uvar_OnPlayerLogout
		Uvar_OnPlayerLogout(playerid, uid);
	#endif
	Uvar_DoSavePlayer(playerid);
}

#if defined _ALS_OnPlayerLogout
	#undef OnPlayerLogout
#else
	#define _ALS_OnPlayerLogout
#endif
#if defined Uvar_OnPlayerLogout
	forward Uvar_OnPlayerLogout(playerid, uid);
#endif
#define OnPlayerLogout(%0) Uvar_OnPlayerLogout(%0)*/

/*public OnPlayerSaved(playerid, uid)
{
	#if defined Uvar_OnPlayerSaved
		Uvar_OnPlayerSaved(playerid, uid);
	#endif
	Uvar_DoSavePlayer(playerid);
}

#if defined _ALS_OnPlayerSaved
	#undef OnPlayerSaved
#else
	#define _ALS_OnPlayerSaved
#endif
#if defined Uvar_OnPlayerSaved
	forward Uvar_OnPlayerSaved(playerid, uid);
#endif
#define OnPlayerSaved(%0) Uvar_OnPlayerSaved(%0)*/

stock Uvar_Save(playerid)
{
	return _Player_ForceSave(playerid);
}

stock _Uvar_DoSavePlayer(playerid)
{
	// Loop through all the player data items and write them to a file.
	Player_SetTag("y_uvar");
	new
		p = YSI_g_sFirstUVarData,
		temp;
	while (p != -1)
	{
		// DO NOT CHANGE THE CODE BELOW HERE!!!
		// Call a function sort of.  This allows us to push an arbitrary address
		// as an array to a function.
		#emit LOAD.S.pri p
		// Get the max players.
		#emit ADD.C      8
		#emit STOR.S.pri temp
		#emit LREF.S.pri temp
		#emit STOR.S.pri temp
		if (playerid < temp)
		{
			// Get the data size.
			#emit LOAD.S.pri p
			#emit ADD.C      12
			#emit STOR.S.pri temp
			#emit LREF.S.pri temp
			#emit PUSH.pri
			// Get the data offset.
			#emit LOAD.S.alt playerid
			#emit SMUL
			#emit SMUL.C     4
			#emit MOVE.alt
			// Get the data pointer.
			#emit LOAD.S.pri p
			#emit ADD.C      4
			#emit STOR.S.pri temp
			#emit LREF.S.pri temp
			#emit ADD
			#emit PUSH.pri
			// Get the function name.
			#emit LOAD.S.pri p
			#emit ADD.C      16
			#emit PUSH.pri
			// Save the next pointer.
			#emit LREF.S.pri p
			#emit STOR.S.pri p
			// Now push the size of data put on the stack.
			#emit PUSH.C     12
			// Now get the return address and push it.
			#emit LCTRL      6
			#emit ADD.C      28
			#emit PUSH.pri
			// Call "Player_WriteArray" directly.
			#emit CONST.pri  Player_WriteArray
			#emit SCTRL      6
			// DO NOT CHANGE THE CODE ABOVE HERE!!!
		}
	}
}

hook OnPlayerConnect(playerid)
{
	P:1("hook Users_OnPlayerConnect called: %i", playerid);
	new
		p = YSI_g_sFirstUVarData,
		temp;
	while (p != -1)
	{
		// DO NOT CHANGE THE CODE BELOW HERE!!!
		// Call a function sort of.  This allows us to push an arbitrary address
		// as an array to a function.
		#emit LOAD.S.pri p
		// Get the max players.
		#emit ADD.C      8
		#emit STOR.S.pri temp
		#emit LREF.S.pri temp
		#emit STOR.S.pri temp
		if (playerid < temp)
		{
			// It might be faster here to just use "FILL"...
			// Get the data enum size.
			//#emit PUSH.C     8
			#emit LOAD.S.pri p
			#emit ADD.C      12
			#emit STOR.S.pri temp
			#emit LREF.S.pri temp
			#emit PUSH.pri
			// Set them all to "0".
			#emit PUSH.C     0
			// Get the data offset.
			#emit LOAD.S.alt playerid
			#emit SMUL
			#emit SMUL.C     4
			#emit MOVE.alt
			// Get the data pointer.
			#emit LOAD.S.pri p
			#emit ADD.C      4
			#emit STOR.S.pri temp
			#emit LREF.S.pri temp
			#emit ADD
			#emit PUSH.pri
			// Save the next pointer.
			#emit LREF.S.pri p
			#emit STOR.S.pri p
			// Now push the size of data put on the stack.
			#emit PUSH.C     12
			// Now get the return address and push it.
			#emit LCTRL      6
			#emit ADD.C      28
			#emit PUSH.pri
			// Call "memset" directly.
			#emit CONST.pri  memset
			#emit SCTRL      6
			// DO NOT CHANGE THE CODE ABOVE HERE!!!
		}
	}
}
