/**--------------------------------------------------------------------------**\
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
	2.2
Changelog:
	02/02/13:
		Added bits and join timestamp to preload data.
		Added backwards compatible salting to the hash.
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
</remarks>
\**--------------------------------------------------------------------------**/

#define GetUsersSQLHost()     "localhost"
#define GetUsersSQLReadUser() "root"
#define GetUsersSQLReadPass() "pri=ret&~1;"
#define GetUsersSQLDB()       "y_users"
#define GetUsersSQLPort()     3306

#if !defined Y_USERS_SQL_HOST
	#define Y_USERS_SQL_HOST GetUsersSQLHost()
#endif
#if !defined Y_USERS_SQL_READ_USER
	#define Y_USERS_SQL_READ_USER GetUsersSQLReadUser()
#endif
#if !defined Y_USERS_SQL_READ_PASS
	#define Y_USERS_SQL_READ_PASS GetUsersSQLReadPass()
#endif
#if !defined Y_USERS_SQL_DB
	#define Y_USERS_SQL_DB GetUsersSQLDB()
#endif
#if !defined Y_USERS_SQL_PORT
	#define Y_USERS_SQL_PORT GetUsersSQLPort()
#endif

#if !defined Y_USERS_SQL_WRITE_USER
	#define Y_USERS_SQL_WRITE_USER Y_USERS_SQL_READ_USER
#endif
#if !defined Y_USERS_SQL_WRITE_PASS
	#define Y_USERS_SQL_WRITE_PASS Y_USERS_SQL_READ_PASS
#endif

#if !defined Y_USERS_SQL_MAKE_USER
	#define Y_USERS_SQL_MAKE_USER Y_USERS_SQL_READ_USER
#endif
#if !defined Y_USERS_SQL_MAKE_PASS
	#define Y_USERS_SQL_MAKE_PASS Y_USERS_SQL_READ_PASS
#endif

loadtext core[ysi_players];

enum E_USER_PRELOAD
{
	E_USER_PRELOAD_YID,
	Language:E_USER_PRELOAD_LANG,
	E_USER_PRELOAD_PASS[MAX_PASSWORD_LENGTH + 1],
	E_USER_PRELOAD_BITS,
	E_USER_PRELOAD_DATE
}

static stock
	YSI_g_sCurrentYID,
	YSI_g_sModeNameLength,
	YSI_g_sSQLBuffer[2048],
	YSI_g_sSQLQuery[256],
	SQL:YSI_g_sPreloadHandle,
	SQL:YSI_g_sLoadHandle,
	SQL:YSI_g_sWriteHandle,
	YSI_g_sPlayerYID[MAX_PLAYERS] = {-2, ...},
	YSI_g_sPreloadData[MAX_PLAYERS][E_USER_PRELOAD];

/**--------------------------------------------------------------------------**\
<summary>Player_Reload</summary>
<param name="playerid">Player who changed name.</param>
<returns>
	-
</returns>
<remarks>
	Reload a player's basic data when they change name.
</remarks>
\**--------------------------------------------------------------------------**/

stock Player_Reload(playerid)
{
	new
		name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof (name)),
	Player_Preload(name, YSI_g_sPreloadData[playerid]);
}

stock Player_SetPreload(playerid, data[E_USER_PRELOAD])
{
	if (0 <= playerid < MAX_PLAYERS)
	{
		YSI_g_sPreloadData[playerid] = data;
	}
}

/**--------------------------------------------------------------------------**\
<summary>Player_Preload</summary>
<param name="playerid">Player who is logging in.</param>
<returns>
	-
</returns>
<remarks>
	Loads a player's data to an array.
</remarks>
\**--------------------------------------------------------------------------**/

stock Player_Preload(string:name[], ret[E_USER_PRELOAD])
{
	// First, find the player's file.  This should be the ONLY place where the
	// password is to be loaded.
	P:4("Player_Preload called: %s", name);
	ret[E_USER_PRELOAD_YID] = -2,
	ret[E_USER_PRELOAD_PASS] = '\0',
	ret[E_USER_PRELOAD_LANG] = NO_LANGUAGE,
	ret[E_USER_PRELOAD_BITS] = 0,
	ret[E_USER_PRELOAD_DATE] = 0;
	new
		safeName[MAX_PLAYER_NAME];
	sql_escape_string(YSI_g_sPreloadHandle, name, safeName),
	format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery), "SELECT yid, password_hash, language, options, times FROM y_users_preload WHERE name='%s' LIMIT 0,1;", safeName);
	new
		Result:r = sql_query(YSI_g_sPreloadHandle, YSI_g_sSQLQuery);
	if (sql_error(r))
	{
		P:E("SQL Error: %s",  YSI_g_sSQLQuery);
		return
			sql_error_string(r, YSI_g_sSQLQuery),
			sql_free_result(r),
			0;
	}
	if (sql_num_rows(r))
	{
		// YID.
		sql_get_field(r, 0, YSI_g_sSQLQuery),
		ret[E_USER_PRELOAD_YID] = strval(YSI_g_sSQLQuery),
		// Hash.
		sql_get_field(r, 1, YSI_g_sSQLQuery),
		strcat(ret[E_USER_PRELOAD_PASS], YSI_g_sSQLQuery, MAX_PASSWORD_LENGTH + 1),
		// Language
		sql_get_field(r, 2, YSI_g_sSQLQuery),
		ret[E_USER_PRELOAD_LANG] = Langs_GetLanguage(YSI_g_sSQLQuery),
		// Load the 32 extra "bits".
		sql_get_field(r, 3, YSI_g_sSQLQuery),
		ret[E_USER_PRELOAD_BITS] = strval(YSI_g_sSQLQuery),
		// Load the user registration date (if they have one).
		sql_get_field(r, 4, YSI_g_sSQLQuery),
		ret[E_USER_PRELOAD_DATE] = strval(YSI_g_sSQLQuery);
		P:6("Player_Preload: %s %d %d %x %x", ret[E_USER_PRELOAD_PASS], ret[E_USER_PRELOAD_YID], _:ret[E_USER_PRELOAD_LANG], ret[E_USER_PRELOAD_BITS], ret[E_USER_PRELOAD_DATE]);
		return 1;
	}
	return
		ret[E_USER_PRELOAD_YID] = -1,
		0;
}

stock Language:Player_GetPreloadLanguage(playerid)
{
	return Language:YSI_g_sPreloadData[playerid][E_USER_PRELOAD_LANG];
}

stock Player_GetPreloadBits(playerid)
{
	return YSI_g_sPreloadData[playerid][E_USER_PRELOAD_BITS];
}

static remotefunc void:_Player_SetPreloadBits(playerid, bits)
{
	YSI_g_sPreloadData[playerid][E_USER_PRELOAD_BITS] = bits;
}

stock Player_SetPreloadBits(playerid, bits)
{
	broadcastfunc _Player_SetPreloadBits(playerid, bits);
	Player_RewritePreload(playerid);
}

stock Player_GetPreloadDate(playerid)
{
	if (0 <= YSI_g_sPreloadData[playerid][E_USER_PRELOAD_DATE] < 1234567890)
	{
		return -1;
	}
	return YSI_g_sPreloadData[playerid][E_USER_PRELOAD_DATE];
}

stock Player_IsRegistered(playerid)
{
	return YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID] >= 0;
}

hook OnScriptInit()
{
	sql_debug(LOG_NONE, LOG_ALL);
	#define SQL_CLEANUP(%0) if (sql_error((%0))){sql_error_string((%0),error),P:E("SQL Error: %s",error);return sql_free_result((%0)),sql_disconnect(mkH),0;}sql_free_result((%0))
	YSI_g_sModeNameLength = strlen(MODE_NAME),
	YSI_g_sPreloadHandle = sql_connect(SQL_HANDLER_MYSQL, Y_USERS_SQL_HOST, Y_USERS_SQL_READ_USER, Y_USERS_SQL_READ_PASS, Y_USERS_SQL_DB),
	P:5("Users_OnScriptInit: YSI_g_sPreloadHandle = %d", _:YSI_g_sPreloadHandle);
	YSI_g_sLoadHandle = sql_connect(SQL_HANDLER_MYSQL, Y_USERS_SQL_HOST, Y_USERS_SQL_READ_USER, Y_USERS_SQL_READ_PASS, Y_USERS_SQL_DB),
	P:5("Users_OnScriptInit: YSI_g_sLoadHandle = %d", _:YSI_g_sLoadHandle);
	YSI_g_sWriteHandle = sql_connect(SQL_HANDLER_MYSQL, Y_USERS_SQL_HOST, Y_USERS_SQL_WRITE_USER, Y_USERS_SQL_WRITE_PASS, Y_USERS_SQL_DB);
	P:5("Users_OnScriptInit: YSI_g_sWriteHandle = %d", _:YSI_g_sWriteHandle);
	// There are two main tables.
	new
		SQL:mkH = sql_connect(SQL_HANDLER_MYSQL, Y_USERS_SQL_HOST, Y_USERS_SQL_MAKE_USER, Y_USERS_SQL_MAKE_PASS, Y_USERS_SQL_DB),
		error[64],
		// Create the table for storing users.
		Result:r = sql_query(mkH,
		// Main table creation.
		"CREATE TABLE IF NOT EXISTS y_users_preload ("					\
			"row BIGINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,"	\
			"yid INT UNSIGNED NOT NULL, name VARCHAR(24),"				\
			"password_hash CHAR(128), language CHAR(2),"				\
			"options INT, times INT UNSIGNED, UNIQUE (name),"			\
			"INDEX (name) USING HASH) ENGINE InnoDB;");
	P:5("Users_OnScriptInit: mkH = %d", _:mkH);
	// "options" was "BIT(32)".
	#pragma tabsize 0 // BAD BAD BAD!  HACK HACK HACK!
	SQL_CLEANUP(r);
	#pragma tabsize 4 // RESTORE FROM THE UGLINESS!
	// Create the table for storing tags.
	r = sql_query(mkH,
		"CREATE TABLE IF NOT EXISTS y_users_modes ("					\
			"tagid BIGINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,"\
			"mode VARCHAR(32),"											\
			"tag VARCHAR(32),"											\
			"INDEX (mode) USING HASH,"									\
			"UNIQUE KEY (mode, tag)) ENGINE InnoDB;");
	#pragma tabsize 0 // BAD BAD BAD!  HACK HACK HACK!
	SQL_CLEANUP(r);
	#pragma tabsize 4 // RESTORE FROM THE UGLINESS!
	// Create the table for storing key/value pairs.
	r = sql_query(mkH,
		"CREATE TABLE IF NOT EXISTS y_users_keystore ("					\
			"row BIGINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,"	\
			"yid INT UNSIGNED NOT NULL,"								\
			"tagid BIGINT UNSIGNED NOT NULL,"							\
			"vkey VARCHAR(32),"											\
			"value VARCHAR(196),"										\
			"CONSTRAINT FOREIGN KEY (tagid)"							\
				"REFERENCES y_users_modes (tagid) ON DELETE CASCADE,"	\
			"UNIQUE KEY (yid, tagid, vkey)) ENGINE InnoDB;");
	#pragma tabsize 0 // BAD BAD BAD!  HACK HACK HACK!
	SQL_CLEANUP(r);
	#pragma tabsize 4 // RESTORE FROM THE UGLINESS!
	// Create an invalid user to initialise the "yid" column.  This also nicely
	// forbids empty names in the database by already having one.
	r = sql_query(mkH,
		"INSERT INTO y_users_preload VALUES(0, 0, '',"					\
		"'XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX',"\
		"'XX', 0, 0);");
	sql_free_result(r);
	sql_disconnect(mkH);
	return 1;
	#undef SQL_CLEANUP
}

hook OnScriptExit()
{
	sql_disconnect(YSI_g_sPreloadHandle),
	sql_disconnect(YSI_g_sLoadHandle),
	sql_disconnect(YSI_g_sWriteHandle);
}

hook OnPlayerConnect(playerid)
{
	P:1("Users_OnPlayerConnect called: %d", playerid);
	// -2 means unknown.
	YSI_g_sPlayerYID[playerid] = -2;
	broadcastfunc _Player_IsLoggedIn(playerid);
	if (existproperty(8, YSIM_LOG_IN))
	{
		new
			uid = getproperty(8, YSIM_LOG_IN);
		P:5("Users_OnPlayerConnect: Exists %d", uid);
		if (uid == -1)
		{
			new
				name[MAX_PLAYER_NAME];
			GetPlayerName(playerid, name, sizeof (name));
			Player_Preload(name, YSI_g_sPreloadData[playerid]);
		}
		else
		{
			// This DOES NOT use "broadcastfunc" as it's local only.
			Player_DoLogin(playerid, uid);
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
	P:2("Users_OnPlayerDisconnect called: %d %d %d", playerid, reason, YSI_g_sPlayerYID[playerid]);
	if (YSI_g_sPlayerYID[playerid] >= 0)
	{
		// DO NOT broadcastfunc this in case it's just because of one script being
		// unloaded, not the player actually leaving (and thus do everything in
		// different scripts separately).
		Player_SaveData(playerid, true);
	}
	YSI_g_sPlayerYID[playerid] = -2;
}

static remotefunc void:_Player_IsLoggedIn(playerid)
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

/**--------------------------------------------------------------------------**\
<summary>Player_TryLogin</summary>
<param name="playerid">Player who is logging in.</param>
<param name="password[]">Password they entered.</param>
<param name="f">Show the failed to login message?</param>
<returns>
	-
</returns>
<remarks>
	Tries to log in a player - hashes and checks their password and if it's
	right calls the core login code.  It doesn't matter WHICH script does this
	as they ALL get called and ALL track the login status of a player.
</remarks>
\**--------------------------------------------------------------------------**/

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
		hash[MAX_PASSWORD_LENGTH + 8 + 1];
	Player_HashPass(password, hash);
	format(hash[MAX_PASSWORD_LENGTH], sizeof (hash) - MAX_PASSWORD_LENGTH, "%04x%04x", YSI_g_sPreloadData[playerid][E_USER_PRELOAD_DATE] >>> 16, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_DATE] & 0xFFFF);
	Player_HashPass(hash, hash);
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
			if (YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS][0] && !strcmp(YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS], hash, false, MAX_PASSWORD_LENGTH))
			{
				// Wipe the password from memory.
				memset(YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS], 0, MAX_PASSWORD_LENGTH);
				// Extract the uid and call in to the login code.
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

/**--------------------------------------------------------------------------**\
<summary>Player_ForceLogin</summary>
<param name="playerid">Player who is logging in.</param>
<returns>
	-
</returns>
<remarks>
	Like "Player_TryLogin" but doesn't take a password so always works.
</remarks>
\**--------------------------------------------------------------------------**/

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
			// Extract the uid and call in to the login code.
			YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS] = '\0';
			Langs_SetPlayerLanguage(playerid, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_LANG]);
			broadcastfunc Player_DoLogin(playerid, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID]);
			Text_Send(playerid, $YSI_LOGIN_LOGIN);
			return 1;
		}
	}
	return 0;
}

forward y_users_SQLLoaded(playerid, uid, Result:r);

remotefunc void:Player_DoLogin(playerid, uid)
{
	// Called when a player logs in - either locally (new script) or globally
	// (actually only just logged in).
	YSI_g_sPlayerYID[playerid] = uid;
	static
		sQuery[196];
	format(sQuery, sizeof (sQuery), "SELECT md.tag,ks.vkey,ks.value FROM y_users_modes AS md JOIN y_users_keystore AS ks ON md.tagid=ks.tagid WHERE ks.yid=%d && md.mode='" #MODE_NAME "';", uid);
	sql_query(YSI_g_sLoadHandle, YSI_g_sSQLBuffer, QUERY_THREADED, "y_users_SQLLoaded", "iir", playerid, uid);
}

public y_users_SQLLoaded(playerid, uid, Result:r)
{
	static
		func[32] = "@yU_",
		name[32];
	if (sql_error(r))
	{
		sql_error_string(r, YSI_g_sSQLQuery),
		P:E("SQL Error: %s", YSI_g_sSQLQuery);
		return
			sql_free_result(r),
			0;
	}
	// Loop through all the results.
	new
		rows = sql_num_rows(r);
	for (new row = 0; row != rows; ++row)
	{
		// Load all the data in a YSI-compatible way.
		sql_next_row(r, row),
		sql_get_field(r, 0, func[4]),
		sql_get_field(r, 1, name),
		sql_get_field(r, 2, YSI_g_sSQLQuery),
		CallLocalFunction(func, "iss", playerid, name, YSI_g_sSQLQuery);
	}
	// Finally, they've logged in.
	call OnPlayerLogin(playerid, uid);
	return
		sql_free_result(r),
		1;
}

forward y_users_SQLCallback(id, Result:r);

public y_users_SQLCallback(id, Result:r)
{
	if (sql_error(r))
	{
		if (id == 3 && sql_error(r) == 1452) goto y_users_SQLCallback_done;
		sql_error_string(r, YSI_g_sSQLQuery),
		P:E("SQL Error: %s", YSI_g_sSQLQuery);
		return
			sql_free_result(r),
			0;
	}
y_users_SQLCallback_done:
	return
		sql_free_result(r),
		1;
}

/**--------------------------------------------------------------------------**\
<summary>Player_RemoveEntry</summary>
<param name="name[]">Item to remove.</param>
<returns>
	-
</returns>
<remarks>
	Wrapper for Player_AddToBuffer for removing data.
</remarks>
\**--------------------------------------------------------------------------**/

stock Player_RemoveEntry(name[])
{
	// First, flush the main buffer so we can add anything we might want to
	// remove.
	Player_FlushData();
	sql_escape_string(YSI_g_sWriteHandle, name, YSI_g_sSQLQuery),
	format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery), "DELETE FROM y_users_keystore WHERE yid=%d && tagid=@T && vkey='%s';", YSI_g_sCurrentYID, YSI_g_sSQLQuery),
	sql_query(YSI_g_sWriteHandle, YSI_g_sSQLQuery, QUERY_THREADED, "y_users_SQLCallback", "ir", 1);
}

/**--------------------------------------------------------------------------**\
<summary>Player_WriteString</summary>
<param name="name[]">Data name.</param>
<param name="data[]">Data.</param>
<returns>
	-
</returns>
<remarks>
	Wrapper for Player_AddToBuffer for strings.
</remarks>
\**--------------------------------------------------------------------------**/

stock Player_WriteString(name[], data[])
{
	static
		sPart[196 + 32 + 10 + 10 + 10];
	format(sPart, sizeof (YSI_g_sSQLBuffer), "(%d,@T,'", YSI_g_sCurrentYID);
	sql_escape_string(YSI_g_sWriteHandle, name, sPart[strlen(sPart)])
	strcat(sPart, "','")
	sql_escape_string(YSI_g_sWriteHandle, data, sPart[strlen(sPart)])
	strcat(sPart, "')")
	// Already has some query buffered.
	if (YSI_g_sSQLBuffer[0])
	{
		if (strlen(YSI_g_sSQLBuffer) < sizeof (YSI_g_sSQLBuffer) - 44 - 2 - strlen(sPart))
		{
			// Enough space for the new values and the standard suffix.
			strcat(YSI_g_sSQLBuffer, ",");
			goto Player_WriteString_run;
		}
		strcat(YSI_g_sSQLBuffer, "ON DUPLICATE KEY UPDATE value=values(value);");
		sql_query(YSI_g_sWriteHandle, YSI_g_sSQLBuffer, QUERY_THREADED, "y_users_SQLCallback", "ir", 3);
	}
	YSI_g_sSQLBuffer = "INSERT INTO y_users_keystore(yid,tagid,vkey,value)VALUES";
Player_WriteString_run:
	strcat(YSI_g_sSQLBuffer, sPart);
}

stock Player_WriteArray(const name[], data[], len)
{
//	INI_WriteArray(YSI_g_sPlayerWriteFile, name, data, len);
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>Player_WriteInt</summary>
<param name="name[]">Data name.</param>
<param name="data">Integer data.</param>
<returns>
	-
</returns>
<remarks>
	Wrapper for Player_AddToBuffer for integers.
</remarks>
\**--------------------------------------------------------------------------**/

stock Player_WriteInt(name[], data)
{
	static
		sVal[12];
	strval(sVal, data);
	Player_WriteString(name, sVal);
}

/**--------------------------------------------------------------------------**\
<summary>Player_WriteHex</summary>
<param name="name[]">Data name.</param>
<param name="data">Hex data.</param>
<returns>
	-
</returns>
<remarks>
	Wrapper for Player_AddToBuffer for integers to be written as hex values.
</remarks>
\**--------------------------------------------------------------------------**/

stock Player_WriteHex(name[], data)
{
	static
		sVal[11];
	format(sVal, sizeof (sVal), "0x%04x%04x", data >>> 16, data & 0xFFFF);
	Player_WriteString(name, data);
}

/**--------------------------------------------------------------------------**\
<summary>Player_WriteBin</summary>
<param name="name[]">Data name.</param>
<param name="data">Binary data.</param>
<returns>
	-
</returns>
<remarks>
	Wrapper for Player_AddToBuffer for integers to be written as binary values.
</remarks>
\**--------------------------------------------------------------------------**/

stock Player_WriteBin(name[], data)
{
	static const
		sc_values[] = !"0000" "0001" "0010" "0011" "0100" "0101" "0110" "0111" "1000" "1001" "1010" "1011" "1100" "1101" "1110" "1111";
	static
		str[35];
	new
		i = 10;
	do
	{
		str[--i] = sc_values[data & 0x0F];
		data >>>= 4;
	}
	while (data);
	// Convert the coalesced values to individual values.
	strunpack(str[i], str[i], 33);
	str[--i] = 'b';
	str[--i] = '0';
	Player_WriteString(name, str);
}

/**--------------------------------------------------------------------------**\
<summary>Player_WriteBool</summary>
<param name="name[]">Data name.</param>
<param name="data">Boolean data.</param>
<returns>
	-
</returns>
<remarks>
	Wrapper for Player_AddToBuffer for booleans.
</remarks>
\**--------------------------------------------------------------------------**/

stock Player_WriteBool(name[], bool:data)
{
	Player_WriteString(name, data ? ("true") : ("false"));
}

/**--------------------------------------------------------------------------**\
<summary>Player_WriteFloat</summary>
<param name="name[]">Data name.</param>
<param name="Float:data">Float data.</param>
<param name="accuracy">number of decimal places to write.</param>
<returns>
	-
</returns>
<remarks>
	Wrapper for Player_AddToBuffer for floats.  Uses custom code instead of
	format() as it's actually faster for something simple like this.
</remarks>
\**--------------------------------------------------------------------------**/

stock Player_WriteFloat(name[], Float:data, accuracy = 6)
{
	static
		str[16];
	format(str, sizeof (str), "%.*f", accuracy, data);
	Player_WriteString(name, str);
}

static stock Player_FlushData()
{
	if (YSI_g_sSQLBuffer[0])
	{
		new
			len = strlen(YSI_g_sSQLBuffer) + 44;
		if (len >= sizeof (YSI_g_sSQLBuffer))
		{
			P:E("Could not save y_users buffer (should not happen).");
			return 0;
		}
		strcat(YSI_g_sSQLBuffer, "ON DUPLICATE KEY UPDATE value=values(value);");
		sql_query(YSI_g_sWriteHandle, YSI_g_sSQLBuffer, QUERY_THREADED, "y_users_SQLCallback", "ir", 3),
		YSI_g_sSQLBuffer[0] = '\0';
	}
	return 1;
}

stock Player_SetTag(tag[])
{
	Player_FlushData();
	sql_escape_string(YSI_g_sWriteHandle, tag, YSI_g_sSQLQuery),
	// Run the second query.  Use "INSERT IGNORE" to add the tag only if it
	// doesn't exist already.  The length check here is wrong, but making it
	// correct would take more effort and we've already checked the length.
	// This stores the tagid in to a global MySQL variable.
	format(YSI_g_sSQLBuffer, sizeof (YSI_g_sSQLBuffer),
		"INSERT IGNORE INTO y_users_modes(tag,mode)VALUES('%s','" #MODE_NAME "');"		\
		"SELECT @T:=tagid FROM y_users_modes WHERE tag='%s'&&mode='" #MODE_NAME "';",
		YSI_g_sSQLQuery, YSI_g_sSQLQuery),
	sql_query(YSI_g_sWriteHandle, YSI_g_sSQLBuffer, QUERY_THREADED, "y_users_SQLCallback", "ir", 4),
	YSI_g_sSQLBuffer[0] = '\0';
}

stock Player_DeleteTag(tag[])
{
	// Uses "CASCADE ON DELETE".
	sql_escape_string(YSI_g_sWriteHandle, tag, YSI_g_sSQLQuery),
	format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery), "DELETE FROM y_users_modes WHERE tag='%s' && mode='" #MODE_NAME "';", YSI_g_sSQLQuery),
	sql_query(YSI_g_sWriteHandle, YSI_g_sSQLQuery, QUERY_THREADED, "y_users_SQLCallback", "ir", 5);
	// Any future data written to this tag will just fail the constraint.
}

stock Player_SaveData(playerid, bool:logout = false)
{
	// Just in case they decide to save a player's data in the middle of another
	// player's data being saved...
	new
		stk = YSI_g_sCurrentYID;
	if (YSI_g_sPlayerYID[playerid] >= 0)
	{
		// Flush any old data.
		Player_FlushData();
		// New player's data.
		YSI_g_sCurrentYID = YSI_g_sPlayerYID[playerid];
		Player_SetTag("--none--");
		CallLocalFunction("OnSavePlayerData", "ii", playerid, YSI_g_sCurrentYID);
		Player_SetTag("--none--");
		if (logout)
		{
			call OnPlayerLogout(playerid, YSI_g_sCurrentYID);
		}
		// Flush new data.
		Player_FlushData();
	}
	YSI_g_sCurrentYID = stk;
}

/**--------------------------------------------------------------------------**\
<summary>Player_HashPass</summary>
<param name="pass[]">Data to hash.</param>
<returns>
	-
</returns>
<remarks>
	Based on my Dad's hash system but slightly modifed.  Updated for reverse
	compatability with other login systems.  Needs more code for Whirlpool.
</remarks>
\**--------------------------------------------------------------------------**/

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
			s1 = (s1 + pass[i++]) % 65521,
			s2 = (s2 + s1) % 65521;
		}
		format(target, sizeof (target), "%" #MAX_PASSWORD_LENGTH "d", (s2 << 16) + s1);
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
			mod = i % MAX_PASSWORD_LENGTH,
			tmp = (i >= j) ? charset[(7 * i) % css] : pass[i],
			sum = (sum + chrfind(tmp, charset) + 1) % css,
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

/**--------------------------------------------------------------------------**\
<summary>Player_TryRegister</summary>
<param name="playerid">Player who is registering.</param>
<param name="string:password[]">The password they entered.</param>
<returns>
	-
</returns>
<remarks>
	Register the player with the given password if there is no-one else with the
	name already.  Or log them in if the username and password match an existing
	account.  Note that there is no "Player_ForceRegister" as it would do the
	same thing with no less parameters (a password MUST be given to write in the
	file).
</remarks>
\**--------------------------------------------------------------------------**/

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
		hash[MAX_PASSWORD_LENGTH + 1 + 8];
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
			// Get the salt.
			format(hash[MAX_PASSWORD_LENGTH], sizeof (hash) - MAX_PASSWORD_LENGTH, "%04x%04x", YSI_g_sPreloadData[playerid][E_USER_PRELOAD_DATE] >>> 16, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_DATE] & 0xFFFF);
			Player_HashPass(hash, hash);
			// Match the password.
			if (!strcmp(YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS], hash, false, MAX_PASSWORD_LENGTH) && YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS][0])
			{
				// Extract the uid and call in to the login code.
				YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS] = '\0';
				Langs_SetPlayerLanguage(playerid, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_LANG]);
				broadcastfunc Player_DoLogin(playerid, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID]);
				Text_Send(playerid, $YSI_LOGIN_LOGIN);
				return 1;
			}
			else
			{
				Text_Send(playerid, $YSI_REG_TAKEN);
				return 0;
			}
		}
	}
	Player_FlushData();
	new
		name[MAX_PLAYER_NAME + 1];
	GetPlayerName(playerid, name, sizeof (name));
	sql_escape_string(YSI_g_sWriteHandle, name, name);
	new
		d = gettime(),
		date[9];
	format(date, sizeof (date), "%04x%04x", d >>> 16, d & 0xFFFF),
	strcat(hash, date),
	Player_HashPass(hash, hash),
	format(YSI_g_sSQLBuffer, sizeof (YSI_g_sSQLBuffer),
		"SELECT @Y:=MAX(yid) FROM y_users_preload;"			\
		"INSERT INTO y_users_preload VALUES"				\
			"(DEFAULT, @Y + 1, '%s', '%s', '%s', 0, %d);"	\
		"SELECT (@Y + 1);",
		name, hash, Langs_GetCode(Langs_GetPlayerLanguage(playerid)), d);
	new
		Result:r = sql_query(YSI_g_sWriteHandle, YSI_g_sSQLBuffer);
	YSI_g_sSQLBuffer[0] = '\0';
	if (sql_error(r))
	{
		sql_error_string(r, YSI_g_sSQLQuery),
		P:E("SQL Error: %s", YSI_g_sSQLQuery);
		return
			Text_Send(playerid, $YSI_ADDU_INDER2),
			sql_free_result(r),
			0;
	}
	sql_get_field(r, 0, name),
	sql_free_result(r),
	broadcastfunc Player_DoLogin(playerid, strval(name)),
	Text_Send(playerid, $YSI_LOGIN_LOGIN);
	return 1;
}

#endinput

global Player_ChangePassword(playerid, string:password[])
{
	#pragma unused password
	new
		uid = Player_GetYID(playerid);
	if (uid < 0)
	{
		return 0;
	}
	// Create the new password.
	new
		hash[MAX_PASSWORD_LENGTH + 8 + 1];
	Player_HashPass(password, hash);
	format(hash[MAX_PASSWORD_LENGTH], sizeof (hash) - MAX_PASSWORD_LENGTH, "%04x%04x", YSI_g_sPreloadData[playerid][E_USER_PRELOAD_DATE] >>> 16, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_DATE] & 0xFFFF);
	Player_HashPass(hash, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS]);
	// Save it.
	Player_RewritePreload(playerid);
	// Wipe it.
	memset(YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS], 0, MAX_PASSWORD_LENGTH);
	return 1;
}

/**--------------------------------------------------------------------------**\
<summary>Player_RewritePreload</summary>
<param name="playerid">Player whose data should be saved.</param>
<returns>
	-
</returns>
<remarks>
	When a player's preload data is modifed (new bit data or changed password),
	it needs to be written back out to file.
</remarks>
\**--------------------------------------------------------------------------**/

static stock Player_RewritePreload(playerid)
{
	if (YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID] < 0)
	{
		return 0;
	}
	// First, find the player's file.  This should be the ONLY place where the
	// password is to be loaded.
	new
		name[MAX_PLAYER_NAME + 1];
	GetPlayerName(playerid, name, sizeof (name));
	P:4("Player_RewritePreload called: %s", name);
	#if _YSI_PLUGINS_MYSQL == 7
		// Right then, lets get coding...
		new
			query[110];
		mysql_format(YSI_g_sMySQL, query, "SELECT `uid`, `language`, `hash` FROM `y_users_register` WHERE `name` = '%e' LIMIT 0,1", name);
		mysql_function_query(YSI_g_sMySQL, query, true, "_Player_Preload", "ii", );
	#else
		new
			namelen = strlen(name),
			filename[] = USER_FILE_PATH "ind_X.YSI",
			File:fIndex;
		Player_GetIndexFile(filename, name[0]);
		fIndex = fopen(filename, io_readwrite);
		if (fIndex)
		{
			P:5("Player_RewritePreload: fIndex OK");
			new
				line[INDEX_DATA_LINE_LENGTH],
				len;
			while ((len = fread(fIndex, line)))
			{
				P:6("Player_RewritePreload: while");
				// Check if the line is the right length (could be one of three
				// lengths depending on newlines).  Skip blanks.
				if (len < INDEX_DATA_LINE_LENGTH - 3)
				{
					continue;
				}
				P:6("Player_RewritePreload: Not len");
				// Check the name on the line.
				if (!strcmp(line[MAX_INDEX_LENGTH + 1], name, false, namelen) && line[MAX_INDEX_LENGTH + 1 + namelen] == ' ')
				{
					P:6("Player_RewritePreload: checked name");
					fseek(fIndex, -len, seek_current);
					format(line, sizeof (line),
						"%0" #MAX_INDEX_LENGTH "d %" #MAX_PLAYER_NAME "s %" #MAX_PASSWORD_LENGTH "s %02s %04x%04x %04x%04x" INI_NEW_LINE,
						YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID],
						name,
						YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS],
						Langs_GetCode(Langs_GetPlayerLanguage(playerid)),
						YSI_g_sPreloadData[playerid][E_USER_PRELOAD_BITS] >>> 16, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_BITS] & 0xFFFF,
						YSI_g_sPreloadData[playerid][E_USER_PRELOAD_DATE] >>> 16, YSI_g_sPreloadData[playerid][E_USER_PRELOAD_DATE] & 0xFFFF);
					P:5("Player_RewritePreload: Writing: %s", line);
					fwrite(fIndex, line);
					fclose(fIndex);
					return 1;
				}
			}
			fclose(fIndex);
		}
		else if (fexist(filename))
		{
			P:E("Error reading index %c.", filename[0]);
			return 0;
		}
		//ret[E_USER_PRELOAD_YID] = -1;
	#endif
	return 0;
}

/**--------------------------------------------------------------------------**\
<summary>Player_TryGroup</summary>
<param name="playerid">Player who is joining a group.</param>
<param name="string:other[]">A player name already in the group.</param>
<param name="string:password[]">The password of the group.</param>
<returns>
	-
</returns>
<remarks>
	Links a player with an existing player such that they share all stats.
</remarks>
\**--------------------------------------------------------------------------**/

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
					uid = ret[E_USER_PRELOAD_YID],
					line[INDEX_DATA_LINE_LENGTH];
				// Use the loaded ID.
				format(line, sizeof (line), "%0" #MAX_INDEX_LENGTH "d %" #MAX_PLAYER_NAME "s %" #MAX_PASSWORD_LENGTH "s %02s" INI_NEW_LINE, uid, name, hash, Langs_GetCode(ret[E_USER_PRELOAD_LANG]));
				fwrite(fIndex, line);
				fclose(fIndex);
				format(filename, sizeof (filename), USER_FILE_PATH "%0" #MAX_INDEX_LENGTH "d.INI", uid);
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
				broadcastfunc Player_DoLogin(playerid, uid);
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

/**--------------------------------------------------------------------------**\
<summary>Player_ForceGroup</summary>
<param name="playerid">Player who is joining a group.</param>
<param name="string:other[]">A player name already in the group.</param>
<returns>
	-
</returns>
<remarks>
	Like "Player_TryGroup", but doesn't take a password and instead just uses
	the password of the old player (hashed).
</remarks>
\**--------------------------------------------------------------------------**/

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
				uid = ret[E_USER_PRELOAD_YID],
				line[INDEX_DATA_LINE_LENGTH];
			// Use the loaded ID.
			format(line, sizeof (line), "%0" #MAX_INDEX_LENGTH "d %" #MAX_PLAYER_NAME "s %" #MAX_PASSWORD_LENGTH "s %02s" INI_NEW_LINE, uid, name, ret[E_USER_PRELOAD_PASS], Langs_GetCode(ret[E_USER_PRELOAD_LANG]));
			fwrite(fIndex, line);
			fclose(fIndex);
			format(filename, sizeof (filename), USER_FILE_PATH "%0" #MAX_INDEX_LENGTH "d.INI", uid);
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
			broadcastfunc Player_DoLogin(playerid, uid);
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
		uid = -1;
	if (fHnd)
	{
		fread(fHnd, num);
		num[strfind(num, " ")] = '\0';
		uid = strval(num) + 1;
		valstr(num, uid);
		fseek(fHnd, 0, seek_start);
		fwrite(fHnd, num);
		fwrite(fHnd, "        ");
		fclose(fHnd);
	}
	return uid;
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
