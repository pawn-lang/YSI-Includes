/*----------------------------------------------------------------------------*-
					===================================
					 y_users - Registration functions.
					===================================
Description:
	Provides access to a user system for registering and saving users.
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
	
	The Original Code is the YSI malloc include.
	
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
	15/11/11:
		Added comments.
		Added language to the top-level player data (needed for login).
	11/11/11:
		First version.
Functions:
	Public
		-
	Core:
		-
	Stock:
		-
	Static:
		-
	Inline:
		-
	API:
		-
Callbacks:
	-
Definitions:
	-
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
	-
Operators:
	-
-*----------------------------------------------------------------------------*/

#if !defined MODE_NAME
	#error Please define "MODE_NAME" before including y_users.
#endif

#include <a_samp>

forward OnPlayerLogin(playerid, yid);

forward OnPlayerLogout(playerid, yid);

//#if !defined HAS_USER_CALLBACKS
//	#define HAS_USER_CALLBACKS
//#endif

#include "internal\y_version"

#include "y_text"

#include "y_remote"
#include "y_debug"
#include "y_ini"
#include "y_utils"
#include "y_timers"

#define YSIM_U_DISABLE
#include "y_master"
#define MAX_INDEX_LENGTH                8

#include "y_hooks"

#include "internal\y_natives"

#if defined PP_ADLER32
#elseif defined PP_MD5 && defined MD5_Hash
	#define MAX_PASSWORD_LENGTH             32
#elseif defined PP_SHA1
	#error SHA1 unsupported.
#elseif defined PP_YSI
	#define MAX_PASSWORD_LENGTH             16
#elseif defined WP_Hash
	#define MAX_PASSWORD_LENGTH             128
#else
	#define PP_YSI
	#define MAX_PASSWORD_LENGTH             16
#endif

#define INDEX_DATA_LINE_LENGTH          (MAX_INDEX_LENGTH + 1 + MAX_PLAYER_NAME + 1 + MAX_PASSWORD_LENGTH + 3 + 3)

#if !defined USER_FILE_PATH
	#define USER_FILE_PATH                  "YSI/users/"
	#define USER_FILE_LENGTH                10
#endif

//#define PINI:%0[%1](%2) %0_%1@yU_(%2);public %0_%1@yU_(%2)

#define OnUserData[%0](%1) @yU_%0(%1)
#define PINI:%0(%1) forward OnUserData[%0](%1);public OnUserData[%0](%1)

loadtext core[ysi_players];

enum E_USER_PRELOAD
{
	E_USER_PRELOAD_YID,
	Language:E_USER_PRELOAD_LANG,
	E_USER_PRELOAD_PASS[MAX_PASSWORD_LENGTH + 1]
}

static stock
	YSI_g_sPlayerIndexFile,
	INI:YSI_g_sPlayerWriteFile = INI_NO_FILE,
	YSI_g_sPlayerYID[MAX_PLAYERS] = {-2, ...},
	YSI_g_sCallbacks,
	YSI_g_sPreloadData[MAX_PLAYERS][E_USER_PRELOAD];

//#define Player_GetIndexFile(%0,%1) ((YSI_g_sPlayerIndexFile=%1[0]),%0[sizeof(%0)-5]=(('a'<=(YSI_g_sPlayerIndexFile|0x20)<='z')?(YSI_g_sPlayerIndexFile|0x20):(('0'<=YSI_g_sPlayerIndexFile<='9')?('0'):('_'))))
#define Player_GetIndexFile(%0,%1) ((YSI_g_sPlayerIndexFile=%1),%0[USER_FILE_LENGTH+4]=(('a'<=(YSI_g_sPlayerIndexFile|0x20)<='z')?(YSI_g_sPlayerIndexFile|0x20):(('0'<=YSI_g_sPlayerIndexFile<='9')?('0'):('_'))))

//foreign Player_DoLogout(playerid, yid);

foreign Player_TryRegister(playerid, string:password[]);

foreign Player_TryLogin(playerid, string:password[]);

foreign Player_TryGroup(playerid, string:other[], string:password[]);

// No longer global because the YID is shared in all scripts.
//foreign Player_GetYID(playerid);

foreign Player_ChangePassword(playerid, string:password[]);

foreign Player_ForceGroup(playerid, string:other[]);

foreign Player_ForceLogin(playerid);

/*----------------------------------------------------------------------------*\
Function:
	Player_Preload
Params:
	playerid - Player who is logging in.
Return:
	-
Notes:
	Loads a player's data to an array.
\*----------------------------------------------------------------------------*/

stock Player_Reload(playerid)
{
	new
		name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof (name));
	Player_Preload(name, YSI_g_sPreloadData[playerid]);
}

stock Player_SetPreload(playerid, data[E_USER_PRELOAD])
{
	if (0 <= playerid < MAX_PLAYERS)
	{
		YSI_g_sPreloadData[playerid] = data;
	}
}

stock Player_Preload(string:name[], ret[E_USER_PRELOAD])
{
	// First, find the player's file.  This should be the ONLY place where the
	// password is to be loaded.
	P:4("Player_Preload called: %s", name);
	ret[E_USER_PRELOAD_YID] = -2;
	ret[E_USER_PRELOAD_PASS] = '\0';
	ret[E_USER_PRELOAD_LANG] = NO_LANGUAGE;
	new
		namelen = strlen(name),
		filename[] = USER_FILE_PATH "ind_X.YSI",
		File:fIndex;
	Player_GetIndexFile(filename, name[0]);
	fIndex = fopen(filename, io_read);
	if (fIndex)
	{
		P:5("Player_Preload: fIndex OK");
		new
			line[INDEX_DATA_LINE_LENGTH];
		while (fread(fIndex, line))
		{
			P:6("Player_Preload: while");
			new
				len;
			len = strlen(line);
			// Check if the line is the right length (could be one of three
			// lengths depending on newlines).  Skip blanks.
			if (len < INDEX_DATA_LINE_LENGTH - 3)
			{
				continue;
			}
			P:6("Player_Preload: Not len");
			// Check the name on the line.
			if (!strcmp(line[MAX_INDEX_LENGTH + 1], name, false, namelen) && line[MAX_INDEX_LENGTH + 1 + namelen] == ' ')
			{
				P:6("Player_Preload: checked name");
				// Found the section on this one player.
				//P:6("Player_Preload: check pass: %s ?= %s", hash, line[MAX_INDEX_LENGTH + 1 + MAX_PLAYER_NAME + 1]);
				// Save the loaded data.
				line[MAX_INDEX_LENGTH] = '\0';
				//printf("line: %s", line);
				ret[E_USER_PRELOAD_YID] = strval(line);
				//printf("%d %d %d", ret[E_USER_PRELOAD_YID], strval(line), strval("00000022"));
				//printf("%d", strval(line));
				line[MAX_INDEX_LENGTH + 1 + MAX_PLAYER_NAME + 1 + MAX_PASSWORD_LENGTH + 1 + 2] = '\0';
				ret[E_USER_PRELOAD_LANG] = Langs_GetLanguage(line[MAX_INDEX_LENGTH + 1 + MAX_PLAYER_NAME + 1 + MAX_PASSWORD_LENGTH + 1]);
				strcat(ret[E_USER_PRELOAD_PASS], line[MAX_INDEX_LENGTH + 1 + MAX_PLAYER_NAME + 1], MAX_PASSWORD_LENGTH + 1);
				P:6("Player_Preload: %s %d %d", ret[E_USER_PRELOAD_PASS], ret[E_USER_PRELOAD_YID], _:ret[E_USER_PRELOAD_LANG]);
				fclose(fIndex);
				return 1;
			}
		}
		fclose(fIndex);
	}
	else if (fexist(filename))
	{
		P:E("Error reading index %c.", filename[0]);
		return -1;
	}
	ret[E_USER_PRELOAD_YID] = -1;
	return 0;
}

stock Language:Player_GetPreloadLanguage(playerid)
{
	return Language:YSI_g_sPreloadData[playerid][E_USER_PRELOAD_LANG];
}

stock Player_IsRegistered(playerid)
{
	return YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID] != -1;
}

hook OnScriptInit()
{
	switch (ftouch(USER_FILE_PATH "index.YSI"))
	{
		case -1:
		{
			P:E(USER_FILE_PATH "index.YSI does not exist and couldn't be created.");
		}
		case 1:
		{
			if (!Player_CreateNewID())
			{
				P:E(USER_FILE_PATH "index.YSI does not exist and couldn't be created.");
			}
		}
	}
	// NOT using "ALS" for chaining.
	if (funcidx("OnPlayerLogin") != -1)
	{
		YSI_g_sCallbacks |= 1;
	}
	if (funcidx("OnPlayerLogout") != -1)
	{
		YSI_g_sCallbacks |= 2;
	}
}

public OnGameModeInit()
{
	if (YSI_FILTERSCRIPT)
	{
		if (YSI_g_sCallbacks & 16)
		{
			CallLocalFunction("Users_OnGameModeInit", "");
		}
	}
	else
	{
		CallLocalFunction("Users_OnGameModeInit", "");
		Users_DoUpgrade();
	}
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit Users_OnGameModeInit

forward Users_OnGameModeInit();

public OnFilterScriptInit()
{
	if (funcidx("Users_OnGameModeInit") != -1)
	{
		YSI_g_sCallbacks |= 16;
	}
	// DO ALL (MOST) OTHER INITS FIRST.  ENSURE WE COME LATER.
	CallLocalFunction("Users_OnFilterScriptInit", "");
	Users_DoUpgrade();
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit Users_OnFilterScriptInit

forward Users_OnFilterScriptInit();

static stock Users_DoUpgrade()
{
	// Only ever do this upgrade once.
	switch (ftouch(USER_FILE_PATH "y_users_v2_1.YSI"))
	{
		case -1:
		{
			P:E("Could not upgrade user files.");
		}
		case 1:
		{
			// Do the upgrade to add languages to all files (could take a little
			// while, but needs doing).
			P:I("Please wait, upgrading user files.");
			new
				ch,
				filename[] = USER_FILE_PATH "ind_X.YSI",
				File:f,
				File:g,
				line[INDEX_DATA_LINE_LENGTH],
				//Language:def = Langs_GetLanguageAt(0),
				code[3];
			strcpy(code, Langs_GetCode(Langs_GetLanguageAt(0)));
			for (new i = -2; i != 26; ++i)
			{
				if (i == -2)
				{
					ch = '_';
				}
				else if (i == -1)
				{
					ch = '0';
				}
				else
				{
					ch = 'a' + i;
				}
				Player_GetIndexFile(filename, ch);
				f = fopen(filename, io_read);
				if (!f)
				{
					if (fexist(filename))
					{
						P:E("Upgrade %c failed.", filename[USER_FILE_LENGTH + 4]);
					}
					continue;
				}
				g = ftemp();
				if (!g)
				{
					fclose(f);
					P:E("Upgrade %c failed.", filename[USER_FILE_LENGTH + 4]);
					continue;
				}
				while (fread(f, line))
				{
					ch = strlen(line);
					if (ch > 3)
					{
						if (line[ch] - 2 < ' ')
						{
							// "/r/n" or "/n/r".
							// Copy the existing line ending.
							line[ch + 1] = line[ch - 2];
							line[ch + 2] = line[ch - 1];
							
							line[ch -  2] = ' ';
							line[ch -  1] = code[0];
							line[ch -  0] = code[1];
							
							line[ch + 3] = '\0';
							//line[ch - 1] = '\0';
							fwrite(g, line);
						}
						else
						{
							// "/n" or "/r".
							// Copy the existing line ending.
							line[ch + 2] = line[ch - 1];
							
							line[ch -  1] = ' ';
							line[ch -  0] = code[0];
							line[ch - -1] = code[1];
							
							line[ch + 3] = '\0';
							//line[ch - 1] = '\0';
							fwrite(g, line);
						}
					}
				}
				fseek(g);
				fclose(f);
				fremove(filename);
				f = fopen(filename, io_write);
				if (!f)
				{
					fclose(g);
					P:E("Upgrade %c failed.", filename[USER_FILE_LENGTH + 4]);
					continue;
				}
				while (fread(g, line))
				{
					fwrite(f, line);
				}
				fclose(f);
				fclose(g);
			}
			f = fopen(USER_FILE_PATH "index.YSI", io_append);
			if (f)
			{
				fwrite(f, "        ");
				fclose(f);
			}
			else
			{
				P:E("Upgrade index failed.");
			}
			P:I("Upgrade complete.");
		}
	}
}

/*hook OnScriptExit()
{
	_Player_CloseLogout();
}*/

hook OnPlayerConnect(playerid)
{
	P:1("Users_OnPlayerConnect called: %d", playerid);
	// -2 means unknown.
	YSI_g_sPlayerYID[playerid] = -2;
	broadcastfunc _Player_IsLoggedIn(playerid);
	if (existproperty(8, YSIM_LOG_IN))
	{
		new
			yid = getproperty(8, YSIM_LOG_IN);
		P:5("Users_OnPlayerConnect: Exists %d", yid);
		if (yid == -1)
		{
			new
				name[MAX_PLAYER_NAME];
			GetPlayerName(playerid, name, sizeof (name));
			Player_Preload(name, YSI_g_sPreloadData[playerid]);
		}
		else
		{
			// This DOES NOT use "broadcastfunc" as it's local only.
			Player_DoLogin(playerid, yid);
		}
		deleteproperty(8, YSIM_LOG_IN);
	}
	else
	{
		P:5("Users_OnPlayerConnect: Doesn't exist");
		new
			name[MAX_PLAYER_NAME];
		GetPlayerName(playerid, name, sizeof (name));
		Player_Preload(name, YSI_g_sPreloadData[playerid]);
		P:5("Users_OnPlayerConnect: Done Preload");
		// Can do checking in here to see if they just rejoined.
	}
	YSI_g_sPlayerYID[playerid] = -1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if (YSI_g_sPlayerYID[playerid] >= 0)
	{
		// DO NOT broadcastfunc this in case it's just because of one script being
		// unloaded, not the player actually leaving (and thus do everything in
		// different scripts separately).
		Player_DoLogout(playerid, YSI_g_sPlayerYID[playerid]);
	}
	YSI_g_sPlayerYID[playerid] = -2;
}

static remotefunc _Player_IsLoggedIn(playerid)
{
	P:4("_Player_IsLoggedIn called: %d %d", playerid, YSI_g_sPlayerYID[playerid]);
	if (YSI_g_sPlayerYID[playerid] != -2)
	{
		setproperty(8, YSIM_LOG_IN, YSI_g_sPlayerYID[playerid]);
	}
}

stock bool:Player_IsLoggedIn(playerid)
{
	// -2 should never be an issue, but if it is...
	return YSI_g_sPlayerYID[playerid] >= 0;
}

stock Player_GetYID(playerid)
{
	return YSI_g_sPlayerYID[playerid];
}

/*----------------------------------------------------------------------------*\
Function:
	Player_TryLogin
Params:
	playerid - Player who is logging in.
	password[] - Password they entered.
	f - Show the failed to login message?
Return:
	-
Notes:
	Tries to log in a player - hashes and checks their password and if it's
	right calls the core login code.  It doesn't matter WHICH script does this
	as they ALL get called and ALL track the login status of a player.
\*----------------------------------------------------------------------------*/

//stock Player_TryLogin(playerid, string:password[], f = 0)
//{
	//return _Player_TryLogin(playerid, password, f);
//}

global Player_TryLogin(playerid, string:password[])
{
	P:2("Player_TryLogin start");
	if (Player_IsLoggedIn(playerid))
	{
		// They are already logged in.
		Text_Send(playerid, $YSI_LOGIN_ALREADY);
		return 1;
	}
	new
		hash[MAX_PASSWORD_LENGTH + 1];
	Player_HashPass(password, hash);
	switch (YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID])
	{
		case -2:
		{
			Text_Send(playerid, $YSI_LOGIN_INDERR);
		}
		case -1:
		{
			Text_Send(playerid, $YSI_LOGIN_NOTF);
		}
		default:
		{
			// Match the password.
			if (!strcmp(YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS], hash, false, MAX_PASSWORD_LENGTH) && YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS][0])
			{
				// Extract the yid and call in to the login code.
				YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS] = '\0';
				Langs_SetPlayerLanguage(playerid, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_LANG]);
				broadcastfunc Player_DoLogin(playerid, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID]);
				Text_Send(playerid, $YSI_LOGIN_LOGIN);
				return 1;
			}
			else
			{
				Text_Send(playerid, $YSI_LOGIN_WRONG);
			}
		}
	}
	return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	Player_ForceLogin
Params:
	playerid - Player who is logging in.
Return:
	-
Notes:
	Like "Player_TryLogin" but doesn't take a password so always works.
\*----------------------------------------------------------------------------*/

global Player_ForceLogin(playerid)
{
	P:2("Player_TryLogin start");
	if (Player_IsLoggedIn(playerid))
	{
		// They are already logged in.
		Text_Send(playerid, $YSI_LOGIN_ALREADY);
		return 1;
	}
	switch (YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID])
	{
		case -2:
		{
			Text_Send(playerid, $YSI_LOGIN_INDERR);
		}
		case -1:
		{
			Text_Send(playerid, $YSI_LOGIN_NOTF);
		}
		default:
		{
			// Extract the yid and call in to the login code.
			YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS] = '\0';
			Langs_SetPlayerLanguage(playerid, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_LANG]);
			broadcastfunc Player_DoLogin(playerid, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID]);
			Text_Send(playerid, $YSI_LOGIN_LOGIN);
			return 1;
		}
	}
	return 0;
}

/*static*/ remotefunc Player_DoLogin(playerid, yid)
{
	// Called when a player logs in - either locally (new script) or globally
	// (actually only just logged in).
	YSI_g_sPlayerYID[playerid] = yid;
	// Load any "uvar" variables.
	// Call the hooks version of this.
	new
		filename[64];
	format(filename, sizeof (filename), USER_FILE_PATH "%0" #MAX_INDEX_LENGTH "d.INI", yid);
	// INI_ParseFile will ONLY load the data for THIS mode, as well as data
	// which is mode independent (though there should be none).
	INI_ParseFile(filename, "@yU_%s", .bExtra = true, .extra = playerid, .bLocal = true, .bFilter = false, .filter = #MODE_NAME);
	Hooks_OnPlayerLogin(playerid, yid);
	if (YSI_g_sCallbacks & 1)
	{
		//CallLocalFunction("OnPlayerLogin", "ii", playerid, yid);
		call OnPlayerLogin(playerid, yid);
	}
}

/*----------------------------------------------------------------------------*\
Function:
	Player_RemoveEntry
Params:
	name[] - Item to remove.
Return:
	-
Notes:
	Wrapper for Player_AddToBuffer for removing data.
\*----------------------------------------------------------------------------*/

stock Player_RemoveEntry(name[])
{
	INI_RemoveEntry(YSI_g_sPlayerWriteFile, name);
}

/*----------------------------------------------------------------------------*\
Function:
	Player_WriteString
Params:
	name[] - Data name.
	data[] - Data.
Return:
	-
Notes:
	Wrapper for Player_AddToBuffer for strings.
\*----------------------------------------------------------------------------*/

stock Player_WriteString(name[], data[])
{
	INI_WriteString(YSI_g_sPlayerWriteFile, name, data);
}

stock Player_WriteArray(const name[], data[], len)
{
	//printf("name = %s", name);
	//printf("data = %d, %d, %d", data[0], data[1], data[2]);
	//printf("len = %d", len);
	INI_WriteArray(YSI_g_sPlayerWriteFile, name, data, len);
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Player_WriteInt
Params:
	name[] - Data name.
	data - Integer data.
Return:
	-
Notes:
	Wrapper for Player_AddToBuffer for integers.
\*----------------------------------------------------------------------------*/

stock Player_WriteInt(name[], data)
{
	INI_WriteInt(YSI_g_sPlayerWriteFile, name, data);
}

/*----------------------------------------------------------------------------*\
Function:
	Player_WriteHex
Params:
	name[] - Data name.
	data - Hex data.
Return:
	-
Notes:
	Wrapper for Player_AddToBuffer for integers to be written as hex values.
\*----------------------------------------------------------------------------*/

stock Player_WriteHex(name[], data)
{
	INI_WriteHex(YSI_g_sPlayerWriteFile, name, data);
}

/*----------------------------------------------------------------------------*\
Function:
	Player_WriteBin
Params:
	name[] - Data name.
	data - Binary data.
Return:
	-
Notes:
	Wrapper for Player_AddToBuffer for integers to be written as binary values.
\*----------------------------------------------------------------------------*/

stock Player_WriteBin(name[], data)
{
	INI_WriteBin(YSI_g_sPlayerWriteFile, name, data);
}

/*----------------------------------------------------------------------------*\
Function:
	Player_WriteBool
Params:
	name[] - Data name.
	data - Boolean data.
Return:
	-
Notes:
	Wrapper for Player_AddToBuffer for booleans.
\*----------------------------------------------------------------------------*/

stock Player_WriteBool(name[], bool:data)
{
	INI_WriteBool(YSI_g_sPlayerWriteFile, name, data);
}

/*----------------------------------------------------------------------------*\
Function:
	Player_WriteFloat
Params:
	name[] - Data name.
	Float:data - Float data.
	accuracy - number of decimal places to write.
Return:
	-
Notes:
	Wrapper for Player_AddToBuffer for floats.  Uses custom code instead of
	format() as it's actually faster for something simple like this.
\*----------------------------------------------------------------------------*/

stock Player_WriteFloat(name[], Float:data, accuracy = 6)
{
	INI_WriteFloat(YSI_g_sPlayerWriteFile, name, data, accuracy);
}

stock Player_SetTag(tag[])
{
	// Make sure we ALWAYS store mode tags with a special prefix.
	new
		tag2[MAX_INI_TAG] = "@@" #MODE_NAME "-";
	strcat(tag2, tag);
	//printf("tag = %s, %s", tag, tag2);
	INI_SetTag(YSI_g_sPlayerWriteFile, tag2);
}

stock Player_DeleteTag(tag[])
{
	INI_DeleteTag(YSI_g_sPlayerWriteFile, tag);
}

//global Player_DoLogout(playerid, yid)
static stock Player_DoLogout(playerid, yid)
{
	/*INI:YSI_g_sOneLogoutFile = INI_NO_FILE
	YSI_g_sOneLogoutPerson = INVALID_PLAYER_ID*/
	new
		filename[64];
	format(filename, sizeof (filename), USER_FILE_PATH "%0" #MAX_INDEX_LENGTH "d.INI", yid);
	YSI_g_sPlayerWriteFile = INI_Open(filename);
	if (YSI_g_sPlayerWriteFile != INI_NO_FILE)
	{
		Hooks_OnPlayerLogout(playerid, yid);
		if (YSI_g_sCallbacks & 2)
		{
			call OnPlayerLogout(playerid, yid);
		}
		INI_Close(YSI_g_sPlayerWriteFile);
	}
	// Do ALL the saving from ONE place.  Detect one or many scripts ending.
	/*if (YSI_g_sOneLogoutFile == INI_NO_FILE)
	{
		new
			filename[64];
		format(filename, sizeof (filename), USER_FILE_PATH "%0" #MAX_INDEX_LENGTH "d.INI", yid);
		YSI_g_sOneLogoutFile = INI_Open(filename);
		YSI_g_sOneLogoutPerson = playerid;
	}
	else if (YSI_g_sOneLogoutPerson != playerid)
	{
		INI_Close(YSI_g_sOneLogoutFile);
	}
	// Will be called AFTER all "OnPlayerDisconnect" callbacks are called when
	// one player leaves, and if more leave it's still used for the last player
	// in the list.
	//defer _Player_CloseLogout();
	_Player_CloseLogout();
	// By now "YSI_g_sOneLogoutFile" contains a handle to the user's file,
	// either having just been opened, or invoked in a previous call to this
	// function from another script still running but loosing the player.
	// This could in theory be used from some force-logout script.
	YSI_g_sPlayerYID[playerid] = -1;*/
	return 1;
}

//static timer _Player_CloseLogout[0]()
/*static stock _Player_CloseLogout()
{
	if (YSI_g_sOneLogoutFile != INI_NO_FILE)
	{
		INI_Close(YSI_g_sOneLogoutFile);
		YSI_g_sOneLogoutFile = INI_NO_FILE;
		YSI_g_sOneLogoutPerson = INVALID_PLAYER_ID;
	}
}*/

/*----------------------------------------------------------------------------*\
Function:
	Player_HashPass
Params:
	pass[] - Data to hash.
Return:
	-
Notes:
	Based on my Dad's hash system but slightly modifed.  Updated for reverse
	compatability with other login systems.  Needs more code for Whirlpool.
\*----------------------------------------------------------------------------*/

static stock Player_HashPass(pass[], target[])
{
	#if defined PP_ADLER32
		new
			s1 = 1,
			s2 = 0,
			i,
			You_REALLY_shouldnt_use_Adler32;
		while (pass[i])
		{
			s1 = (s1 + pass[i++]) % 65521;
			s2 = (s2 + s1) % 65521;
		}
		//new
		//	target[MAX_PASSWORD_LENGTH + 1];
		format(target, sizeof (target), "%" #MAX_PASSWORD_LENGTH "d", (s2 << 16) + s1);
		//return target;
	#elseif defined PP_MD5 && defined MD5_Hash
		new
			You_REALLY_shouldnt_use_MD5;
		strcpy(target, MD5_Hash(pass, strlen(pass)));
	#elseif defined PP_SHA1
		#error SHA1 unsupported.
	#elseif defined PP_YSI
		static
			charset[] = "A,UbRgdnS#|rT_%5+ZvEK¬NF<9¦IH[(C)2O07 Y-Less]$Qw^?/om4;@'8k£Pp.c{&l\\3zay>DfxV:WXjuG6*!1\"i~=Mh`JB}qt",
			css = 99;
		new
			//target[MAX_PASSWORD_LENGTH + 1],
			j,
			sum = j,
			tmp = 0,
			i,
			mod;
		j = strlen(pass);
		for (i = 0; i < MAX_PASSWORD_LENGTH || i < j; i++)
		{
			mod = i % MAX_PASSWORD_LENGTH;
			tmp = (i >= j) ? charset[(7 * i) % css] : pass[i];
			sum = (sum + chrfind(tmp, charset) + 1) % css;
			target[mod] = charset[(sum + target[mod]) % css];
		}
		target[MAX_PASSWORD_LENGTH] = '\0';
		//return target;
	#elseif defined WP_Hash
		WP_Hash(target, MAX_PASSWORD_LENGTH + 1, pass);
	#else
		#error Whirlpool (or other) hash not found.
	#endif
}

// Hooray for bizare bugs!  I think this is because the function above is
// secretly a macro with "if/else" and a block statement, not a real function.

stock Player_SomeWeirdBugFix()
{
}

/*stock Anything0()
{
}*/

/*stock Anything1()
{
}

stock Anything2()
{
}

stock Anything3()
{
}*/

/*stock Anything4()
{
}

stock Anything5()
{
}

stock Anything6()
{
}

stock Anything7()
{
}*/

/*----------------------------------------------------------------------------*\
Function:
	Player_TryRegister
Params:
	playerid - Player who is registering.
	string:password[] - The password they entered.
Return:
	-
Notes:
	Register the player with the given password if there is no-one else with the
	name already.  Or log them in if the username and password match an existing
	account.  Note that there is no "Player_ForceRegister" as it would do the
	same thing with no less parameters (a password MUST be given to write in the
	file).
\*----------------------------------------------------------------------------*/

//#endinput
global Player_TryRegister(playerid, string:password[])
{
	P:2("Player_TryRegister called");
	if (Player_IsLoggedIn(playerid))
	{
		// They are already logged in.
		Text_Send(playerid, $YSI_LOGIN_ALREADY);
		return 1;
	}
	new
		hash[MAX_PASSWORD_LENGTH + 1];
	Player_HashPass(password, hash);
	switch (YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID])
	{
		case -2:
		{
			Text_Send(playerid, $YSI_LOGIN_INDERR);
		}
		case -1:
		{
		}
		default:
		{
			// Match the password.
			if (!strcmp(YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS], hash, false, MAX_PASSWORD_LENGTH) && YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS][0])
			{
				// Extract the yid and call in to the login code.
				YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS] = '\0';
				Langs_SetPlayerLanguage(playerid, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_LANG]);
				broadcastfunc Player_DoLogin(playerid, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID]);
				Text_Send(playerid, $YSI_LOGIN_LOGIN);
				return 1;
			}
			else
			{
				//Text_Send(playerid, $YSI_LOGIN_WRONG);
				Text_Send(playerid, $YSI_REG_TAKEN);
				return 0;
			}
		}
	}
	new
		name[MAX_PLAYER_NAME + 1];
	GetPlayerName(playerid, name, sizeof (name));
	//format(name, sizeof (name), "%" #MAX_PLAYER_NAME "s", name);
	new
		filename[64] = USER_FILE_PATH "ind_X.YSI",
		File:fIndex;//,
		//hash[MAX_PASSWORD_LENGTH + 1];
	//Player_HashPass(password, hash);
	Player_GetIndexFile(filename, name[0]);
	fIndex = fopen(filename, io_read);
	P:5("Player_TryRegister: fIndex");
	new
		line[INDEX_DATA_LINE_LENGTH];
	if ((fIndex = fopen(filename, io_append)))
	{
		P:5("Player_TryRegister: Write index.");
		// Write the new user to the index file.
		new
			yid = Player_GetNewID();
		if (yid == -1)
		{
			Text_Send(playerid, $YSI_LOGIN_INDERR);
			return 0;
		}
		format(line, sizeof (line), "%0" #MAX_INDEX_LENGTH "d %" #MAX_PLAYER_NAME "s %" #MAX_PASSWORD_LENGTH "s %02s" INI_NEW_LINE, yid, name, hash, Langs_GetCode(Langs_GetPlayerLanguage(playerid)));
		fwrite(fIndex, line);
		fclose(fIndex);
		format(filename, sizeof (filename), USER_FILE_PATH "%0" #MAX_INDEX_LENGTH "d.INI", yid);
		new
			INI:x = INI_Open(filename);
		if (x == INI_NO_FILE)
		{
			Text_Send(playerid, $YSI_LOGIN_NOLOAD);
		}
		else
		{
			INI_SetTag(x, "ysi_names");
			INI_WriteString(x, name, "name");
			INI_Close(x);
		}
		// Call in all scripts.
		broadcastfunc Player_DoLogin(playerid, yid);
		Text_Send(playerid, $YSI_LOGIN_LOGIN);
		return 1;
	}
	else
	{
		Text_Send(playerid, $YSI_ADDU_INDER2);
		return 0;
	}
}

global Player_ChangePassword(playerid, string:password[])
{
	#pragma unused password
	new
		yid = Player_GetYID(playerid);
	if (yid < 0)
	{
		return 0;
	}
	new
		filename[64];
	// Loop through all the names associated with this user.
	format(filename, sizeof (filename), USER_FILE_PATH "%0" #MAX_INDEX_LENGTH "d.INI", yid);
	/*inline Func(string:name[], string:value[])
	{
	}
	INI_ParseFile(filename, using inline Func, .bPassTag = true, .singleTag = "ysi_name");*/
	return 1;
}

/*----------------------------------------------------------------------------*\
Function:
	Player_TryGroup
Params:
	playerid - Player who is joining a group.
	string:other[] - A player name already in the group.
	string:password[] - The password of the group.
Return:
	-
Notes:
	Links a player with an existing player such that they share all stats.
\*----------------------------------------------------------------------------*/

//#endinput
global Player_TryGroup(playerid, string:other[], string:password[])
{
	P:2("Player_TryGroup called");
	if (Player_IsLoggedIn(playerid))
	{
		// They are already logged in.
		Text_Send(playerid, $YSI_LOGIN_ALREADY);
		return 1;
	}
	new
		hash[MAX_PASSWORD_LENGTH + 1];
	Player_HashPass(password, hash);
	// Check if the user is not registered already.
	switch (YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID])
	{
		case -2:
		{
			Text_Send(playerid, $YSI_LOGIN_INDERR);
			return 0;
		}
		case -1:
		{
			//Text_Send(playerid, $YSI_LOGIN_NOTF);
		}
		default:
		{
			Text_Send(playerid, $YSI_REG_TAKEN);
			return 0;
		}
	}
	// Check if the new data matches the old.
	new
		ret[E_USER_PRELOAD];
	Player_Preload(other, ret);
	switch (ret[E_USER_PRELOAD_YID])
	{
		case -2:
		{
			Text_Send(playerid, $YSI_LOGIN_INDERR);
		}
		case -1:
		{
			Text_Send(playerid, $YSI_LOGIN_NOTF);
		}
		default:
		{
			// Match the password.
			if (!strcmp(ret[E_USER_PRELOAD_PASS], hash, false, MAX_PASSWORD_LENGTH) && ret[E_USER_PRELOAD_PASS][0])
			{
				new
					name[MAX_PLAYER_NAME + 1];
				GetPlayerName(playerid, name, sizeof (name));
				new
					filename[64] = USER_FILE_PATH "ind_X.YSI";
				Player_GetIndexFile(filename, name[0]);
				new
					File:fIndex = fopen(filename, io_append);
				if (!fIndex)
				{
					Text_Send(playerid, $YSI_ADDU_INDERR2);
					return 0;
				}
				P:5("Player_TryGroup: Write index.");
				new
					yid = ret[E_USER_PRELOAD_YID],
					line[INDEX_DATA_LINE_LENGTH];
				// Use the loaded ID.
				format(line, sizeof (line), "%0" #MAX_INDEX_LENGTH "d %" #MAX_PLAYER_NAME "s %" #MAX_PASSWORD_LENGTH "s %02s" INI_NEW_LINE, yid, name, hash, Langs_GetCode(ret[E_USER_PRELOAD_LANG]));
				fwrite(fIndex, line);
				fclose(fIndex);
				format(filename, sizeof (filename), USER_FILE_PATH "%0" #MAX_INDEX_LENGTH "d.INI", yid);
				new
					INI:x = INI_Open(filename);
				if (x == INI_NO_FILE)
				{
					Text_Send(playerid, $YSI_LOGIN_NOLOAD);
				}
				else
				{
					// Add this name to the list of known names.
					INI_SetTag(x, "ysi_names");
					INI_WriteString(x, name, "name");
					INI_Close(x);
				}
				// Call in all scripts.
				Langs_SetPlayerLanguage(playerid, ret[E_USER_PRELOAD_LANG]);
				broadcastfunc Player_DoLogin(playerid, yid);
				Text_Send(playerid, $YSI_LOGIN_LOGIN);
				return 1;
			}
			else
			{
				Text_Send(playerid, $YSI_LOGIN_WRONG);
			}
		}
	}
	return 0;
}

/*----------------------------------------------------------------------------*\
Function:
	Player_ForceGroup
Params:
	playerid - Player who is joining a group.
	string:other[] - A player name already in the group.
Return:
	-
Notes:
	Like "Player_TryGroup", but doesn't take a password and instead just uses
	the password of the old player (hashed).
\*----------------------------------------------------------------------------*/

//#endinput

global Player_ForceGroup(playerid, string:other[])
{
	P:2("Player_ForceGroup called");
	if (Player_IsLoggedIn(playerid))
	{
		// They are already logged in.
		Text_Send(playerid, $YSI_LOGIN_ALREADY);
		return 1;
	}
	// Check if the user is not registered already.
	switch (YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID])
	{
		case -2:
		{
			Text_Send(playerid, $YSI_LOGIN_INDERR);
			return 0;
		}
		case -1:
		{
			//Text_Send(playerid, $YSI_LOGIN_NOTF);
		}
		default:
		{
			Text_Send(playerid, $YSI_REG_TAKEN);
			return 0;
		}
	}
	// Check if the new data matches the old.
	new
		ret[E_USER_PRELOAD];
	Player_Preload(other, ret);
	switch (ret[E_USER_PRELOAD_YID])
	{
		case -2:
		{
			Text_Send(playerid, $YSI_LOGIN_INDERR);
		}
		case -1:
		{
			Text_Send(playerid, $YSI_LOGIN_NOTF);
		}
		default:
		{
			new
				name[MAX_PLAYER_NAME + 1];
			GetPlayerName(playerid, name, sizeof (name));
			new
				filename[64] = USER_FILE_PATH "ind_X.YSI";
			Player_GetIndexFile(filename, name[0]);
			new
				File:fIndex = fopen(filename, io_append);
			if (!fIndex)
			{
				Text_Send(playerid, $YSI_ADDU_INDERR2);
				return 0;
			}
			P:5("Player_TryGroup: Write index.");
			new
				yid = ret[E_USER_PRELOAD_YID],
				line[INDEX_DATA_LINE_LENGTH];
			// Use the loaded ID.
			format(line, sizeof (line), "%0" #MAX_INDEX_LENGTH "d %" #MAX_PLAYER_NAME "s %" #MAX_PASSWORD_LENGTH "s %02s" INI_NEW_LINE, yid, name, ret[E_USER_PRELOAD_PASS], Langs_GetCode(ret[E_USER_PRELOAD_LANG]));
			fwrite(fIndex, line);
			fclose(fIndex);
			format(filename, sizeof (filename), USER_FILE_PATH "%0" #MAX_INDEX_LENGTH "d.INI", yid);
			new
				INI:x = INI_Open(filename);
			if (x == INI_NO_FILE)
			{
				Text_Send(playerid, $YSI_LOGIN_NOLOAD);
			}
			else
			{
				// Add this name to the list of known names.
				INI_SetTag(x, "ysi_names");
				INI_WriteString(x, name, "name");
				INI_Close(x);
			}
			// Call in all scripts.
			Langs_SetPlayerLanguage(playerid, ret[E_USER_PRELOAD_LANG]);
			broadcastfunc Player_DoLogin(playerid, yid);
			Text_Send(playerid, $YSI_LOGIN_LOGIN);
			return 1;
		}
	}
	return 0;
}

static stock Player_GetNewID()
{
	new
		File:fHnd = fopen(USER_FILE_PATH "index.YSI", io_readwrite),
		num[MAX_INDEX_LENGTH + 9],
		yid = -1;
	if (fHnd)
	{
		fread(fHnd, num);
		num[strfind(num, " ")] = '\0';
		yid = strval(num) + 1;
		valstr(num, yid);
		fseek(fHnd, 0, seek_start);
		fwrite(fHnd, num);
		fwrite(fHnd, "        ");
		fclose(fHnd);
	}
	return yid;
}

static stock Player_CreateNewID()
{
	new
		File:fHnd = fopen(USER_FILE_PATH "index.YSI", io_write);
	if (fHnd)
	{
		fwrite(fHnd, "-1        ");
		fclose(fHnd);
		return 1;
	}
	return 0;
}

// TODO:
//  
//  bool:Player_GetDetails(player, &Language:language);
//  
// Get the data on a registered player from a file.  Also returns their language
// now that I've promoted that to index file data (it's the ONLY thing though).

#include "internal\y_grouprevert"
