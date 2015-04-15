ign Command_ReProcess(p,string:c[],h);

global Command_ReProcess(playerid,string:cmdName[],help)
{
	static sCmd[64] = "@yC_", sPos, sReturn, sHash, e_COMMAND_ERRORS:sErr;
	// Check that the input is a valid command.  Note that changing the command prefix here would be VERY trivial!
	if ((sReturn = _:_Command_IsPrefix(cmdName[0])) && !cmdName[1]) return Command_OnReceived(INVALID_INPUT, playerid, cmdName);
	else if (isnull(cmdName)) return Command_OnReceived(INVALID_INPUT, playerid, NULL);
    #if !defined Y_COMMANDS_NO_IPC // Check for a valid player when debugging is disabled
    if (!IsPlayerConnected(playerid)) return Command_OnReceived(NO_PLAYER, playerid, cmdName);
	if (PA_Get(YSI_g_sDisabledPlayers, playerid)) return Command_OnReceived(DISABLED, playerid, cmdName);
	playerid:1("Commands_OnPlayerCommandText called: %d %s", playerid, cmdName);
	new prevID = YSI_g_sCurrentID; // To add "next" to the intrusive linked list.
	// Get the hashed version of the decoded string, skipping the possible  "/".
	sPos = Puny_EncodeHash(sCmd[4], cmdName[sReturn], sHash, .delimiter = '@') + sReturn;
	while (cmdName[sPos] == ' ') ++sPos; // Better/slower: ('\0' < cmdName[sPos] <= ' ').
	YSI_g_sCurrentID = HashMap_GetWithHash(YSI_g_sCommandMap, sCmd[4], sHash);
	playerid:5("Commands_OnPlayerCommandText: %s, %d, %d, %d", sCmd[4], sPos, sHash, YSI_g_sCurrentID);
	if (YSI_g_sCurrentID == COMMAND_NOT_FOUND) return YSI_g_sCurrentID = prevID, Command_OnReceived(UNDEFINED, playerid, cmdName);
    #if defined Y_COMMANDS_USE_CHARS // Not everything starts with '/', some are custom.
    // Have a prefix, but not the right one despite calling this function directly
    if (sReturn && _Command_GetPrefix(YSI_g_sCurrentID) != cmdName[0]) return Command_OnReceived(BAD_PREFIX, playerid, cmdName);
	playerid:5("Commands_OnPlayerCommandText: Use %d", _Command_GetPlayer(YSI_g_sCurrentID, playerid));
	if (_Command_GetPlayer(YSI_g_sCurrentID, playerid)) { // Can the player use this command?
    if (!Command_OnReceived(OK, playerid, cmdName)) return YSI_g_sCurrentID = prevID, 0;
    _Command_GetReal(sHash, YSI_g_sCurrentID, sCmd[4]); // Find the true version of the command (alts etc).
    P:5("Commands_OnPlayerCommandText: Read %d", YSI_g_sCurrentID);
    P:5("Commands_OnPlayerCommandText: Master %d %d", Master_ID(), _:MASTER_GET<YSI_g_sCurrentID>);
		#if YSIM_HAS_MASTER
			if (MASTER_EXCLUSIVE<YSI_g_sCurrentID>)
		#endif
