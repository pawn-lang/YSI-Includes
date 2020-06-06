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
	Portions created by the Initial Developer are Copyright C 2011
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
	/*E_USER_PRELOAD_PLAY_TIME,
	E_USER_PRELOAD_LAST_IP,
	E_USER_PRELOAD_LAST_LOGIN,*/
	E_USER_PRELOAD_DATE
}

static stock
	YSI_g_sCurrentYID = 0,
	YSI_g_sModeNameLength = 0,
	YSI_g_sSQLBuffer[2048],
	YSI_g_sSQLQuery[256],
	SQL:YSI_g_sPreloadHandle = SQL:0,
	SQL:YSI_g_sLoadHandle = SQL:0,
	SQL:YSI_g_sWriteHandle = SQL:0,
	YSI_g_sPlayerYID[MAX_PLAYERS] = {-2, ...},
	YSI_g_sPreloadData[MAX_PLAYERS][E_USER_PRELOAD];

forward y_users_SQLLoaded(playerid, uid, Result:r);
forward y_users_SQLCallback(id, Result:r);

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  This code loads the settings for accessing your database from a file.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define GetUsersSQLHost()     (Player_LoadDBSettings(),YSI_g_sUsersSQLHost)
#define GetUsersSQLReadUser() (Player_LoadDBSettings(),YSI_g_sUsersSQLReadUser)
#define GetUsersSQLReadPass() (Player_LoadDBSettings(),YSI_g_sUsersSQLReadPass)
#define GetUsersSQLDB()       (Player_LoadDBSettings(),YSI_g_sUsersSQLDB)
#define GetUsersSQLPort()     (Player_LoadDBSettings(),YSI_g_sUsersSQLPort)

static stock
	YSI_g_sUsersSQLHost[16]     = "localhost",
	YSI_g_sUsersSQLReadUser[16] = "y_users_make",
	YSI_g_sUsersSQLReadPass[16] = "y_users_make",
	YSI_g_sUsersSQLDB[16]       = "y_users",
	YSI_g_sUsersSQLPort         = 3306;

INI:YSI[y_users](name[], value[])
{
	INI_String("Host", YSI_g_sUsersSQLHost, sizeof (YSI_g_sUsersSQLHost));
	INI_String("User", YSI_g_sUsersSQLReadUser, sizeof (YSI_g_sUsersSQLReadUser));
	INI_String("Pass", YSI_g_sUsersSQLReadPass, sizeof (YSI_g_sUsersSQLReadPass));
	INI_String("DB", YSI_g_sUsersSQLDB, sizeof (YSI_g_sUsersSQLDB));
	INI_Int("Port", YSI_g_sUsersSQLPort);
	return 0;
}

static stock Player_LoadDBSettings()
{
	static
		bool:sLoad = true;
	if (sLoad)
	{
		INI_Load("YSI.ini");
		sLoad = false;
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who changed name.</param>
 * <remarks>
 *  Reload a player's basic data when they change name.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Player_Reload(playerid)
{
	new
		name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof (name)),
	Player_Preload(name, YSI_g_sPreloadData[playerid]);
}

stock Player_SetPreload(playerid, data[E_USER_PRELOAD])
{
	if (VALID_PLAYERID(playerid))
	{
		YSI_g_sPreloadData[playerid] = data;
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is logging in.</param>
 * <remarks>
 *  Loads a player's data to an array.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Player_Preload(string:name[], ret[E_USER_PRELOAD])
{
	// First, find the player's file.  This should be the ONLY place where the
	// password is to be loaded.
	P:4("Player_Preload called: %s", name);
	ret[E_USER_PRELOAD_YID] = -1,
	ret[E_USER_PRELOAD_PASS] = '\0',
	ret[E_USER_PRELOAD_LANG] = NO_LANGUAGE,
	ret[E_USER_PRELOAD_BITS] = 0,
	ret[E_USER_PRELOAD_DATE] = 0;
	new
		safeName[MAX_PLAYER_NAME];
	sql_escape_string(YSI_g_sPreloadHandle, name, safeName),
	// I don't normally like "SELECT *" but it is appropriate here.
	format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery), "SELECT yp.* FROM y_users_preload AS yp JOIN y_users_users WHERE name='%s';", safeName);
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
	switch (sql_num_rows(r))
	{
		case 0:
		{
			ret[E_USER_PRELOAD_YID] = 0;
		}
		case 1:
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
			// Load their total play time.
			// Load their last IP.
			// Load their last login.
		}
		default:
		{
			P:E("y_users found mutliple YID results for %s", name);
		}
	}
	return
		sql_free_result(r),
		(ret[E_USER_PRELOAD_YID] > 0);
}

stock Language:Player_GetPreloadLanguage(playerid)
{
	return Language:YSI_g_sPreloadData[playerid][E_USER_PRELOAD_LANG];
}

stock Player_GetPreloadBits(playerid)
{
	return YSI_g_sPreloadData[playerid][E_USER_PRELOAD_BITS];
}

remotefunc static void:_Player_SetPreloadBits(playerid, bits)
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
	return YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID] > 0;
}

HOOK__ OnScriptInit()
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
		"CREATE TABLE IF NOT EXISTS y_users_preload ("					\
			"yid INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,"		\
			"password_hash CHAR(128), language CHAR(2),"				\
			"options INT UNSIGNED, registered INT UNSIGNED,"				\
			"play_time INT UNSIGNED, last_ip INT UNSIGNED,"				\
			"last_seen DATETIME"										\
			") ENGINE InnoDB;");
	P:5("Users_OnScriptInit: mkH = %d", _:mkH);
	// "options" was "BIT(32)".
	#pragma tabsize 4 // BAD BAD BAD!  HACK HACK HACK!
	SQL_CLEANUP(r);
	#pragma tabsize 4 // RESTORE FROM THE UGLINESS!
	// Create the table for storing tags.
	r = sql_query(mkH,
		"CREATE TABLE IF NOT EXISTS y_users_modes ("					\
			"tagid INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,"	\
			"mode VARCHAR(32) NOT NULL,"								\
			"tag VARCHAR(32),"											\
			"INDEX (mode) USING HASH,"									\
			"UNIQUE KEY (mode, tag)"									\
			") ENGINE InnoDB;");
	#pragma tabsize 4 // BAD BAD BAD!  HACK HACK HACK!
	SQL_CLEANUP(r);
	#pragma tabsize 4 // RESTORE FROM THE UGLINESS!
	// Create the table to map names to YIDs.
	r = sql_query(mkH,
		"CREATE TABLE IF NOT EXISTS y_users_users ("					\
			"name VARCHAR(24) NOT NULL PRIMARY KEY,"					\
			"yid INT UNSIGNED,"											\
			"CONSTRAINT FOREIGN KEY (yid)"								\
				"REFERENCES y_users_preload (yid) ON DELETE CASCADE,"	\
			"INDEX (name) USING HASH"									\
			") ENGINE InnoDB;");
	#pragma tabsize 4 // BAD BAD BAD!  HACK HACK HACK!
	SQL_CLEANUP(r);
	#pragma tabsize 4 // RESTORE FROM THE UGLINESS!
	// Create the table for storing key/value pairs.
	r = sql_query(mkH,
		"CREATE TABLE IF NOT EXISTS y_users_keystore ("					\
			"yid INT UNSIGNED NOT NULL,"								\
			"tagid INT UNSIGNED NOT NULL,"								\
			"vkey VARCHAR(32) NOT NULL,"								\
			"value VARCHAR(196),"										\
			"CONSTRAINT FOREIGN KEY (tagid) REFERENCES y_users_modes (tagid) ON DELETE CASCADE," \
			"CONSTRAINT FOREIGN KEY (yid) REFERENCES y_users_preload (yid) ON DELETE CASCADE," \
			"UNIQUE KEY (yid, tagid, vkey), INDEX (yid)"				\
			") ENGINE InnoDB;");
	#pragma tabsize 4 // BAD BAD BAD!  HACK HACK HACK!
	SQL_CLEANUP(r);
	#pragma tabsize 4 // RESTORE FROM THE UGLINESS!
	// Create the table to map names to IPs.
	r = sql_query(mkH,
		"CREATE TABLE IF NOT EXISTS y_users_name_ips ("					\
			"row BIGINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,"	\
			"name VARCHAR(24) NOT NULL,"								\
			"one_ip INT UNSIGNED,"										\
			"validated BOOL," 											\
			"registered DATETIME,"										\
			"leave_time DATETIME"										\
			") ENGINE InnoDB;");
	// "validated" means that this name/IP combination logged in and was
	// confirmed to be a valid connecting user, not someone trying to spoof a
	// login.
	#pragma tabsize 4 // BAD BAD BAD!  HACK HACK HACK!
	SQL_CLEANUP(r);
	#pragma tabsize 4 // RESTORE FROM THE UGLINESS!
	// Create the table to map YIDs to IPs.
	r = sql_query(mkH,
		"CREATE TABLE IF NOT EXISTS y_users_yid_ips ("					\
			"row BIGINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,"	\
			"yid INT UNSIGNED NOT NULL,"								\
			"one_ip INT UNSIGNED,"										\
			"registered DATETIME,"										\
			"leave_time DATETIME"										\
			") ENGINE InnoDB;");
	#pragma tabsize 4 // BAD BAD BAD!  HACK HACK HACK!
	SQL_CLEANUP(r);
	#pragma tabsize 4 // RESTORE FROM THE UGLINESS!
	// Create the table to store failed logins.
	r = sql_query(mkH,
		"CREATE TABLE IF NOT EXISTS y_users_fails ("					\
			"row BIGINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,"	\
			"try_yid INT UNSIGNED NOT NULL,"							\
			"from_name VARCHAR(24),"									\
			"from_ip INT UNSIGNED,"										\
			"validated BOOL," 											\
			"attempt_time DATETIME"										\
			") ENGINE InnoDB;");
	#pragma tabsize 4 // BAD BAD BAD!  HACK HACK HACK!
	SQL_CLEANUP(r);
	#pragma tabsize 4 // RESTORE FROM THE UGLINESS!
	sql_disconnect(mkH);
	return 1;
	#undef SQL_CLEANUP
}

HOOK__ OnScriptExit()
{
	// Loop through all players.
	FOREACH__ (new i : Player)
	{
		Player_DoDisconnect(i);
	}
	sql_disconnect(YSI_g_sPreloadHandle),
	sql_disconnect(YSI_g_sLoadHandle),
	sql_disconnect(YSI_g_sWriteHandle);
}

HOOK__ OnPlayerConnect(playerid)
{
	P:1("Users_OnPlayerConnect called: %d", playerid);
	new
		name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof (name)),
	YSI_g_sPlayerYID[playerid] = 0,
	// -1 means unknown.
	YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID] = -1,
	YSI_g_sPreloadData[playerid][E_USER_PRELOAD_PASS] = '\0',
	YSI_g_sPreloadData[playerid][E_USER_PRELOAD_LANG] = NO_LANGUAGE,
	YSI_g_sPreloadData[playerid][E_USER_PRELOAD_BITS] = 0,
	YSI_g_sPreloadData[playerid][E_USER_PRELOAD_DATE] = 0;
	broadcastfunc _Player_IsLoggedIn(playerid);
	if (existproperty(8, YSIM_LOG_IN))
	{
		new
			uid = getproperty(8, YSIM_LOG_IN);
		P:5("Users_OnPlayerConnect: Exists %d", uid);
		// We need the preload data even if they're already logged in.
		if (uid)
		{
			Player_Preload(name, YSI_g_sPreloadData[playerid]);
			if (uid > 0)
			{
				// This DOES NOT use "broadcastfunc" as it's local only.
				Player_DoLogin(playerid, uid);
			}
		}
		deleteproperty(8, YSIM_LOG_IN);
	}
	else
	{
		new
			safeName[MAX_PLAYER_NAME],
			ip = GetIP(playerid);
		// Write this connection.
		sql_escape_string(YSI_g_sWriteHandle, name, safeName),
		format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery),
			"INSERT INTO y_users_name_ips VALUES (DEFAULT, '%s', 0x%04x%04x, 0, NOW(), 0)",
			safeName,
			ip >>> 16,
			ip & 0xFFFF),
		sql_query(YSI_g_sWriteHandle, YSI_g_sSQLQuery, QUERY_THREADED, "y_users_SQLCallback", "ir", 1);
		P:5("Users_OnPlayerConnect: Doesn't exist");
		Player_Preload(name, YSI_g_sPreloadData[playerid]);
		P:5("Users_OnPlayerConnect: Done Preload");
		// Can do checking in here to see if they just rejoined.
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to check.</param>
 * <returns>
 *  -1 - Registered but not logged in.
 *  0  - Not registered.
 *  1+ - Logged in, and their YID.
 * </returns>
 * <remarks>
 *  This is a remote function called in existing scripts when a new script
 *  starts.  If the player is logged in it returns their YID.  If a player is
 *  registered but not logged in it returns "-1".  Otherwise it returns 0.
 * </remarks>
 *//*------------------------------------------------------------------------**/

remotefunc static void:_Player_IsLoggedIn(playerid)
{
	P:4("_Player_IsLoggedIn called: %d %d", playerid, YSI_g_sPlayerYID[playerid]);
	if (YSI_g_sPlayerYID[playerid] > 0)
	{
		setproperty(8, YSIM_LOG_IN, YSI_g_sPlayerYID[playerid]);
	}
	else if (YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID] > 0)
	{
		setproperty(8, YSIM_LOG_IN, -1);
	}
	else
	{
		setproperty(8, YSIM_LOG_IN, 0);
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who left.</param>
 * <param name="reason">Why they left.</param>
 * <remarks>
 *  Logs the player out if they're logged in.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HOOK__ OnPlayerDisconnect(playerid, reason)
{
	Player_DoDisconnect(playerid);
}

static stock Player_DoDisconnect(playerid)
{
	new
		yid = YSI_g_sPlayerYID[playerid];
	P:2("Users_OnPlayerDisconnect called: %d %d %d", playerid, yid);
	if (yid > 0)
	{
		// DO NOT broadcastfunc this in case it's just because of one script being
		// unloaded, not the player actually leaving (and thus do everything in
		// different scripts separately).
		Player_SaveData(playerid, true);
		new
			name[MAX_PLAYER_NAME],
			ip = GetIP(playerid);
		GetPlayerName(playerid, name, sizeof (name)),
		// Write this connection.
		sql_escape_string(YSI_g_sWriteHandle, name, name),
		// Save the online time for this NAME.
		format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery),
			"UPDATE y_users_name_ips SET leave_time=NOW() WHERE name='%s' ORDER BY row DESC LIMIT 1;",
			name),
		sql_query(YSI_g_sWriteHandle, YSI_g_sSQLQuery, QUERY_THREADED, "y_users_SQLCallback", "ir", 1),
		// Save the total online time for this YID.
		format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery),
			"UPDATE y_users_preload SET last_ip=0x%04x%04x, last_seen=NOW(), play_time=play_time+("			\
				"SELECT (NOW()-leave_time) FROM y_users_yid_ips WHERE yid=%d ORDER BY row DESC LIMIT 1)"	\
				"WHERE yid=%d;",
			ip >>> 16, ip & 0xFFFF, yid, yid),
		sql_query(YSI_g_sWriteHandle, YSI_g_sSQLQuery, QUERY_THREADED, "y_users_SQLCallback", "ir", 1),
		// Save the current online time for this YID.
		format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery),
			"UPDATE y_users_yid_ips SET leave_time=NOW() WHERE yid=%d ORDER BY row DESC LIMIT 1;",
			yid),
		sql_query(YSI_g_sWriteHandle, YSI_g_sSQLQuery, QUERY_THREADED, "y_users_SQLCallback", "ir", 1);
		
	}
	YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID] = -1,
	YSI_g_sPlayerYID[playerid] = 0;
}

stock bool:Player_IsLoggedIn(playerid)
{
	// -2 should never be an issue, but if it is...
	return YSI_g_sPlayerYID[playerid] > 0;
}

stock Player_GetYID(playerid)
{
	return YSI_g_sPlayerYID[playerid];
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is logging in.</param>
 * <param name="password">Password they entered.</param>
 * <param name="f">Show the failed to login message?</param>
 * <remarks>
 *  Tries to log in a player - hashes and checks their password and if it's
 *  right calls the core login code.  It doesn't matter WHICH script does this
 *  as they ALL get called and ALL track the login status of a player.
 * </remarks>
 *//*------------------------------------------------------------------------**/

GLOBAL__ Player_TryLogin(playerid, string:password[])
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
		case -1:
		{
			Text_Send(playerid, $YSI_LOGIN_INDERR);
		}
		case 0:
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
				new
					name[MAX_PLAYER_NAME],
					safeName[MAX_PLAYER_NAME],
					ip = GetIP(playerid);
				GetPlayerName(playerid, name, sizeof (name)),
				// Write this connection.
				sql_escape_string(YSI_g_sWriteHandle, name, safeName),
				format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery),
					"INSERT INTO y_users_yid_ips VALUES (DEFAULT, %d, 0x%04x%04x, NOW(), NOW())",
					YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID],
					ip >>> 16,
					ip & 0xFFFF),
				sql_query(YSI_g_sWriteHandle, YSI_g_sSQLQuery, QUERY_THREADED, "y_users_SQLCallback", "ir", 1);
				return 1;
			}
			else
			{
				Text_Send(playerid, $YSI_LOGIN_WRONG);
				// Record the failed login in the database.
				new
					ip = GetIP(playerid);
				GetPlayerName(playerid, hash, sizeof (hash)),
				sql_escape_string(YSI_g_sWriteHandle, hash, hash),
				format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery),
					"INSERT INTO y_users_fails VALUES (DEFAULT, %d, '%s', 0x%04x%04x, 0, NOW())",
					YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID],
					hash,
					ip >>> 16,
					ip & 0xFFFF),
				sql_query(YSI_g_sWriteHandle, YSI_g_sSQLQuery, QUERY_THREADED, "y_users_SQLCallback", "ir", 1);
			}
		}
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is logging in.</param>
 * <remarks>
 *  Like "Player_TryLogin" but doesn't take a password so always works.
 * </remarks>
 *//*------------------------------------------------------------------------**/

GLOBAL__ Player_ForceLogin(playerid)
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
		case -1:
		{
			Text_Send(playerid, $YSI_LOGIN_INDERR);
		}
		case 0:
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
			new
				name[MAX_PLAYER_NAME],
				safeName[MAX_PLAYER_NAME],
				ip = GetIP(playerid);
			GetPlayerName(playerid, name, sizeof (name)),
			// Write this connection.
			sql_escape_string(YSI_g_sWriteHandle, name, safeName),
			format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery),
				"INSERT INTO y_users_yid_ips VALUES (DEFAULT, %d, 0x%04x%04x, NOW(), NOW())",
				YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID],
				ip >>> 16,
				ip & 0xFFFF),
			sql_query(YSI_g_sWriteHandle, YSI_g_sSQLQuery, QUERY_THREADED, "y_users_SQLCallback", "ir", 1);
			return 1;
		}
	}
	return 0;
}

remotefunc void:Player_DoLogin(playerid, uid)
{
	// Called when a player logs in - either locally (new script) or globally
	// (actually only just logged in).
	YSI_g_sPlayerYID[playerid] = uid;
	// We don't need to specify how to join the tables because the definitions
	// use a FOREIGN KEY CONSTRAINT to map them to each other.
	format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery), "SELECT tag, vkey, value FROM y_users_modes JOIN y_users_keystore WHERE yid=%d && mode='" #MODE_NAME "';", uid);
	sql_query(YSI_g_sLoadHandle, YSI_g_sSQLQuery, QUERY_THREADED, "y_users_SQLLoaded", "iir", playerid, uid);
	//UPDATE y_users_name_ips SET validated=1 WHERE name='%s' && one_ip=0x%04x%04x && leave_time=0
	//format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery), "SELECT tag, vkey, value FROM y_users_modes JOIN y_users_keystore WHERE yid=%d && mode='" #MODE_NAME "';", uid);
	//sql_query(YSI_g_sLoadHandle, YSI_g_sSQLQuery, QUERY_THREADED, "y_users_SQLLoaded", "iir", playerid, uid);
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
	// Finally, they've logged in.
	call OnPlayerLogin(playerid, uid);
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
	return
		sql_free_result(r),
		1;
}

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

/*-------------------------------------------------------------------------*//**
 * <param name="name">Item to remove.</param>
 * <remarks>
 *  Wrapper for Player_AddToBuffer for removing data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Player_RemoveEntry(name[])
{
	// First, flush the main buffer so we can add anything we might want to
	// remove.
	Player_FlushData();
	sql_escape_string(YSI_g_sWriteHandle, name, YSI_g_sSQLQuery),
	format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery), "DELETE FROM y_users_keystore WHERE yid=%d && tagid=@T && vkey='%s';", YSI_g_sCurrentYID, YSI_g_sSQLQuery),
	sql_query(YSI_g_sWriteHandle, YSI_g_sSQLQuery, QUERY_THREADED, "y_users_SQLCallback", "ir", 1);
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Data name.</param>
 * <param name="data">Data.</param>
 * <remarks>
 *  Wrapper for Player_AddToBuffer for strings.
 * </remarks>
 *//*------------------------------------------------------------------------**/

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

/*-------------------------------------------------------------------------*//**
 * <param name="name">Data name.</param>
 * <param name="data">Integer data.</param>
 * <remarks>
 *  Wrapper for Player_AddToBuffer for integers.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Player_WriteInt(name[], data)
{
	static
		sVal[12];
	strval(sVal, data);
	Player_WriteString(name, sVal);
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Data name.</param>
 * <param name="data">Hex data.</param>
 * <remarks>
 *  Wrapper for Player_AddToBuffer for integers to be written as hex values.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Player_WriteHex(name[], data)
{
	static
		sVal[11];
	format(sVal, sizeof (sVal), "0x%04x%04x", data >>> 16, data & 0xFFFF);
	Player_WriteString(name, data);
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Data name.</param>
 * <param name="data">Binary data.</param>
 * <remarks>
 *  Wrapper for Player_AddToBuffer for integers to be written as binary values.
 * </remarks>
 *//*------------------------------------------------------------------------**/

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

/*-------------------------------------------------------------------------*//**
 * <param name="name">Data name.</param>
 * <param name="data">Boolean data.</param>
 * <remarks>
 *  Wrapper for Player_AddToBuffer for booleans.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Player_WriteBool(name[], bool:data)
{
	Player_WriteString(name, data ? ("true") : ("false"));
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Data name.</param>
 * <param name="data">Float data.</param>
 * <param name="accuracy">number of decimal places to write.</param>
 * <remarks>
 *  Wrapper for Player_AddToBuffer for floats.  Uses custom code instead of
 *  format() as it's actually faster for something simple like this.
 * </remarks>
 *//*------------------------------------------------------------------------**/

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
	if (YSI_g_sPlayerYID[playerid] > 0)
	{
		// Flush any old data.
		Player_FlushData();
		// New player's data.
		YSI_g_sCurrentYID = YSI_g_sPlayerYID[playerid];
		Player_SetTag("");
		CallLocalFunction("OnSavePlayerData", "ii", playerid, YSI_g_sCurrentYID);
		if (logout)
		{
			Player_SetTag("");
			call OnPlayerLogout(playerid, YSI_g_sCurrentYID);
		}
		// Flush new data.
		Player_FlushData();
	}
	YSI_g_sCurrentYID = stk;
}

/*-------------------------------------------------------------------------*//**
 * <param name="pass">Data to hash.</param>
 * <remarks>
 *  Based on my Dad's hash system but slightly modifed.  Updated for reverse
 *  compatability with other login systems.  Needs more code for Whirlpool.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Player_HashPass(pass[], target[])
{
	#if defined PP_ADLER32
		new
			s1 = 1,
			s2 = 0,
			i = 0,
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
			j = strlen(pass),
			sum = 0,
			tmp = 0,
			i = 0,
			mod = 0;
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
// Only now it isn't, but honestly I'm no longer sure what this was fixing or if
// it is still needed or not.  Even if it isn't there's no point removing it as
// it was clearly important at some point in the past!

stock Player_SomeWeirdBugFix()
{
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is registering.</param>
 * <param name="password">The password they entered.</param>
 * <remarks>
 *  Register the player with the given password if there is no-one else with the
 *  name already.  Or log them in if the username and password match an existing
 *  account.  Note that there is no "Player_ForceRegister" as it would do the
 *  same thing with no less parameters (a password MUST be given to write in the
 *  file).
 * </remarks>
 *//*------------------------------------------------------------------------**/

GLOBAL__ Player_TryRegister(playerid, string:password[])
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
		case -1:
		{
			Text_Send(playerid, $YSI_LOGIN_INDERR);
			return 0;
		}
		case 0:
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
	// Flush pending updates as we need to use "YSI_g_sSQLBuffer", mainly
	// (entirely) because the hash pushes us well over the 256 limit for using
	// "YSI_g_sSQLQuery" so we need the larger buffer.
	Player_FlushData();
	new
		name[MAX_PLAYER_NAME + 1];
	GetPlayerName(playerid, name, sizeof (name)),
	sql_escape_string(YSI_g_sWriteHandle, name, name);
	// Hash the password a second time.
	new
		d = gettime(),
		date[9];
	format(date, sizeof (date), "%04x%04x", d >>> 16, d & 0xFFFF),
	strcat(hash, date),
	Player_HashPass(hash, hash),
	// Create a new YID, then associate this name with it.
	format(YSI_g_sSQLBuffer, sizeof (YSI_g_sSQLBuffer),
		"INSERT INTO y_users_preload VALUES (DEFAULT, '%s', '%s', 0, 0x%s, 0, 0, 0);"	\
		"SELECT @Y:=LAST_INSERT_ID();"													\
		"INSERT INTO y_users_users VALUES ('%s', @Y);"									\
		"SELECT @Y;",
		hash, Langs_GetCode(Langs_GetPlayerLanguage(playerid)), date, name);
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

GLOBAL__ Player_ChangePassword(playerid, string:password[])
{
	#pragma unused password
	new
		uid = Player_GetYID(playerid);
	if (uid <= 0)
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

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player whose data should be saved.</param>
 * <remarks>
 *  When a player's preload data is modifed (new bit data or changed password),
 *  it needs to be written back out to file.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Player_RewritePreload(playerid)
{
	if (YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID] <= 0)
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
		mysql_format(YSI_g_sMySQL, query, "SELECT `uid`, `language`, `hash` FROM `y_users_register` WHERE `name` = '%e' LIMIT 1", name);
		mysql_function_query(YSI_g_sMySQL, query, true, "_Player_Preload", "ii", );
	#else
		new
			namelen = strlen(name),
			filename[] = USER_FILE_PATH "ind_X.YSI",
			File:fIndex = File:0;
		Player_GetIndexFile(filename, name[0]);
		fIndex = fopen(filename, io_readwrite);
		if (fIndex)
		{
			P:5("Player_RewritePreload: fIndex OK");
			new
				line[INDEX_DATA_LINE_LENGTH],
				len = 0;
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
		//ret[E_USER_PRELOAD_YID] = 0;
	#endif
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is joining a group.</param>
 * <param name="other">A player name already in the group.</param>
 * <param name="password">The password of the group.</param>
 * <remarks>
 *  Links a player with an existing player such that they share all stats.
 * </remarks>
 *//*------------------------------------------------------------------------**/

GLOBAL__ Player_TryGroup(playerid, string:other[], string:password[])
{
	P:2("Player_TryGroup called");
	if (Player_IsLoggedIn(playerid))
	{
		// They are already logged in.
		Text_Send(playerid, $YSI_LOGIN_ALREADY);
		return 1;
	}
	switch (YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID])
	{
		case -1:
		{
			Text_Send(playerid, $YSI_LOGIN_INDERR);
			return 0;
		}
		case 0:
		{
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
		case -1:
		{
			Text_Send(playerid, $YSI_LOGIN_INDERR);
		}
		case 0:
		{
			Text_Send(playerid, $YSI_LOGIN_NOTF);
		}
		default:
		{
			new
				hash[MAX_PASSWORD_LENGTH + 1 + 8],
				d = ret[E_USER_PRELOAD_DATE],
				date[9];
			// Hash the password twice, second time with the salt.
			Player_HashPass(password, hash),
			format(date, sizeof (date), "%04x%04x", d >>> 16, d & 0xFFFF),
			strcat(hash, date),
			Player_HashPass(hash, hash);
			// Match the password.
			if (!strcmp(ret[E_USER_PRELOAD_PASS], hash, false, MAX_PASSWORD_LENGTH) && ret[E_USER_PRELOAD_PASS][0])
			{
				new
					name[MAX_PLAYER_NAME + 1];
				GetPlayerName(playerid, name, sizeof (name)),
				sql_escape_string(YSI_g_sWriteHandle, name, name),
				format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery),
					"INSERT INTO y_users_users VALUES ('%s', %d);",
					name, ret[E_USER_PRELOAD_YID]);
				new
					Result:r = sql_query(YSI_g_sWriteHandle, YSI_g_sSQLQuery);
				if (sql_error(r))
				{
					sql_error_string(r, YSI_g_sSQLQuery),
					P:E("SQL Error: %s", YSI_g_sSQLQuery);
					return
						Text_Send(playerid, $YSI_ADDU_INDER2),
						sql_free_result(r),
						0;
				}
				sql_free_result(r),
				// Copy over the preload data.
				YSI_g_sPreloadData[playerid] = ret,
				broadcastfunc Player_DoLogin(playerid, ret[E_USER_PRELOAD_YID]),
				Text_Send(playerid, $YSI_LOGIN_LOGIN);
			}
			else
			{
				Text_Send(playerid, $YSI_LOGIN_WRONG);
				return 0;
			}
		}
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is joining a group.</param>
 * <param name="other">A player name already in the group.</param>
 * <remarks>
 *  Like "Player_TryGroup", but doesn't take a password and instead just uses
 *  the password of the old player (hashed).
 * </remarks>
 *//*------------------------------------------------------------------------**/

GLOBAL__ Player_ForceGroup(playerid, string:other[])
{
	P:2("Player_ForceGroup called");
	if (Player_IsLoggedIn(playerid))
	{
		// They are already logged in.
		Text_Send(playerid, $YSI_LOGIN_ALREADY);
		return 1;
	}
	switch (YSI_g_sPreloadData[playerid][E_USER_PRELOAD_YID])
	{
		case -1:
		{
			Text_Send(playerid, $YSI_LOGIN_INDERR);
			return 0;
		}
		case 0:
		{
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
		case -1:
		{
			Text_Send(playerid, $YSI_LOGIN_INDERR);
		}
		case 0:
		{
			Text_Send(playerid, $YSI_LOGIN_NOTF);
		}
		default:
		{
			new
				name[MAX_PLAYER_NAME + 1];
			GetPlayerName(playerid, name, sizeof (name)),
			sql_escape_string(YSI_g_sWriteHandle, name, name),
			format(YSI_g_sSQLQuery, sizeof (YSI_g_sSQLQuery),
				"INSERT INTO y_users_users VALUES ('%s', %d);",
				name, ret[E_USER_PRELOAD_YID]);
			new
				Result:r = sql_query(YSI_g_sWriteHandle, YSI_g_sSQLQuery);
			if (sql_error(r))
			{
				sql_error_string(r, YSI_g_sSQLQuery),
				P:E("SQL Error: %s", YSI_g_sSQLQuery);
				return
					Text_Send(playerid, $YSI_ADDU_INDER2),
					sql_free_result(r),
					0;
			}
			sql_free_result(r),
			// Copy over the preload data.
			YSI_g_sPreloadData[playerid] = ret,
			broadcastfunc Player_DoLogin(playerid, ret[E_USER_PRELOAD_YID]),
			Text_Send(playerid, $YSI_LOGIN_LOGIN);
		}
	}
	return 1;
}
