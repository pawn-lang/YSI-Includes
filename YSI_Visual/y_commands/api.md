#### _Command_IsEmptySlot
>* **Parameters:**
>	* `idx`: idx_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Tests if the given slot is empty.
 
***

#### _Command_IsAlt
>* **Parameters:**
>	* `idx`: idx_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Tests if the given slot is an alternate command.
 
***

#### _Command_GetReal
>* **Parameters:**
>	* `ptr`: ptr_INFO
>	* `idx`: idx_INFO
>	* `name`: name_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Finds the original version of an alt command.  Updated to not contain long
>	chains (along with "Command_AddAlt").
 
***

#### Command_OnReceived
>* **Parameters:**
>	* `error`: error_INFO
>	* `playerid`: playerid_INFO
>	* `cmdtext`: cmdtext_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Call OnPlayerCommandReceived once the system knows how the player can use
>	this command (if they can).  The order of the parameters is such that the
>	error comes first.  This is because it is compile-time concatenated to make
>	the error enum value, and putting that parameter first means that we don't
>	need to ommit the space after any comma.
 
***

#### _Command_IsActive
>* **Parameters:**
>	* `command`: command_INFO
>* **Returns:**
>	* Is this command ID active?
>* **Remarks:**
>	Doesn't do any bounds checks - use "_Command_IsValid" for that.
 
***

#### _Command_IsValid
>* **Parameters:**
>	* `command`: command_INFO
>* **Returns:**
>	* Is this command ID valid?
>* **Remarks:**
>	Internal direct-access check.
 
***

#### _Command_IsPrefix
>* **Parameters:**
>	* `idx`: idx_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Checks to see if a character is a possible prefix character.  May use an
>	unsigned comparison.
 
***

#### _Command_GetPrefix
>* **Parameters:**
>	* `c`: c_INFO
>* **Returns:**
>	* The prefix for this command.
>* **Remarks:**
>	-
 
***

#### Command_Name
>* **Parameters:**
>	* `f`: f_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Command_GetID
>* **Parameters:**
>	* `function[]`: function[]_INFO
>* **Returns:**
>	* The ID of the passed function.
>* **Remarks:**
>	-
>	native Command_GetID(function[])
 
***

#### Command_AddAlt
>* **Parameters:**
>	* `oidx`: oidx_INFO
>	* `cmd[]`: cmd[]_INFO
>* **Returns:**
>	* The command's ID.
>* **Remarks:**
>	-
 
***

#### Command_ReProcess
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `cmdtext[]`: cmdtext[]_INFO
>	* `help`: help_INFO
>* **Returns:**
>	* true - success or hidden fail.
>	* false - fail.
>* **Remarks:**
>	Does all the command and error handling.
 
***

#### Command_GetPlayer
>* **Parameters:**
>	* `command`: command_INFO
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* Can this player use this command?
>* **Remarks:**
>	native bool:Command_GetPlayer(command, playerid);
 
***

#### Command_GetPlayerNamed
>* **Parameters:**
>	* `funcname[]`: funcname[]_INFO
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Like Command_GetPlayer but for a function name.
>	native bool:Command_GetPlayerNamed(funcname[], playerid);
 
***

#### Command_SetPlayer
>* **Parameters:**
>	* `command`: command_INFO
>	* `playerid`: playerid_INFO
>	* `bool:set`: bool:set_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	native bool:Command_SetPlayer(command, playerid, bool:set);
 
***

#### Command_SetPlayerNamed
>* **Parameters:**
>	* `funcname[]`: funcname[]_INFO
>	* `playerid`: playerid_INFO
>	* `set`: set_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Like Command_SetPlayer but for a function name.
>	native bool:Command_SetPlayerNamed(funcname[], playerid, bool:set);
 
***

#### Command_Find
>* **Parameters:**
>	* `cmd[]`: cmd[]_INFO
>* **Returns:**
>	* The array slot of this command, or -1.
>* **Remarks:**
>	-
 
***

#### Command_AddAltNamed
>* **Parameters:**
>	* `function[]`: function[]_INFO
>	* `altname[]`: altname[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Add an alternate command for an existing command.
>	native Command_AddAltNamed(function[], altname[]);
 
***

#### Command_Remove
>* **Parameters:**
>	* `func`: func_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	native Command_Remove(func);
 
***

#### Command_RemoveNamed
>* **Parameters:**
>	* `func`: func_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	native Command_RemoveNamed(string:func[]);
 
***

#### Command_IsValid
>* **Parameters:**
>	* `command`: command_INFO
>* **Returns:**
>	* Is this command ID valid?
>* **Remarks:**
>	-
 
***

#### Command_GetCurrent
>* **Parameters:**

>* **Returns:**
>	* The command currently being processed, or "COMMAND_NOT_FOUND".
>* **Remarks:**
>	-
 
***

#### Command_GetPlayerCommandCount
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the number of comamnds this player can use.
>	native Command_GetPlayerCommandCount(playerid);
 
***

#### Command_GetName
>* **Parameters:**
>	* `f`: f_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	native Command_GetName(funcid);
 
***

#### Command_GetDisplay
>* **Parameters:**
>	* `f`: f_INFO
>	* `p`: p_INFO
>* **Returns:**
>	* The name of a command for a single player.
>* **Remarks:**
>	Abstracted because there's a crash when chain returning a string from a
>	foreign function (see "Command_GetDisplayNamed").
>	native Command_GetDisplay(funcid, playerid);
 
***

#### Command_GetDisplayNamed
>* **Parameters:**
>	* `f[]`: f[]_INFO
>	* `p`: p_INFO
>* **Returns:**
>	* The name of a named function for one player.
>* **Remarks:**
>	Remote function call for Command_GetDisplayNameNamed - avoids needing to
>	expose users to the master system's odd way of returning strings.  This is
>	the only part I've not yet fixed up to be nice and hidden.
>	native string:Command_GetDisplayNamed(string:funcid[], playerid);
 
***

#### Command_GetNext
>* **Parameters:**
>	* `index`: index_INFO
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* The name of a command for a single player.
>* **Remarks:**
>	-
>	native Command_GetNext(index, playerid);
 
***

#### Command
>* **Parameters:**
>	* `start`: start_INFO
>* **Returns:**
>	* The next command.
>* **Remarks:**
>	Internal implementation of the "Command()" iterator for "foreach".  Returns
>	all the commands that exist.  Normally iterator functions take two
>	parameters, but this needs only one.  Really quite simple, but probably
>	faster this way as it has access to internal information.
 
***

#### PlayerCommand
>* **Parameters:**
>	* `pid`: pid_INFO
>	* `start`: start_INFO
>* **Returns:**
>	* The next command.
>* **Remarks:**
>	Internal implementation of the "PlayerCommand()" iterator for "foreach".
>	Returns all the commands this player can use.
>	This is similar to "Command_GetNext", but returns an ID not a string - I
>	actually think this way is slightly better.
 
***

#### Command_GetPrefix
>* **Parameters:**
>	* `c`: c_INFO
>* **Returns:**
>	* The prefix for this command ('/' by default).
>* **Remarks:**
>	-
 
***

#### Command_IsValidPrefix
>* **Parameters:**
>	* `prefix`: prefix_INFO
>* **Returns:**
>	* Is this a valid character for a prefix?
>* **Remarks:**
>	This is the ONLY place the list of valid prefixes is defined!  They are
>	symbols, not an alphanumerics, and under 128.
 
***

#### Command_IsPrefixUsed
>* **Parameters:**
>	* `prefix`: prefix_INFO
>* **Returns:**
>	* Is this a prefix used for any command?
>* **Remarks:**
>	-
 
***

#### Command_FlushPrefixes
>* **Parameters:**
>	* `prefix`: prefix_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	If one command uses a prefix, then STOPS using said prefix, the global list
>	of valid prefixes will need to be updated.
 
***

#### Command_SetPrefix
>* **Parameters:**
>	* `c`: c_INFO
>	* `prefix`: prefix_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Change what command to type "/x" vs "#x" for example.
 
***

#### Command_SetPrefixNamed
>* **Parameters:**
>	* `c`: c_INFO
>	* `prefix`: prefix_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Change what command to type "/x" vs "#x" for example.
 
***

#### Command_OnPlayerText
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `text[]`: text[]_INFO
>* **Returns:**
>	* 0 - Could not process the command.
>	* 1 - Called the command.
>* **Remarks:**
>	Used to implement alternate command prefixes.
 
***

#### Command_OnPlayerCommandText
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `cmdtext[]`: cmdtext[]_INFO
>* **Returns:**
>	* 0 - Could not process the command.
>	* 1 - Called the command.
>* **Remarks:**
>	The core of the command processor.  Now vsatly simplified.
>	This function first finds the command in our hash map.  If it exists, it
>	checks if the player can use it.  If they can, it checks if it is only in
>	the current script.  If it is it calls it directly, if it isn't it calls it
>	using "CallRemoteFunction", which takes in to account master states in
>	multiple scripts and the special master 23, which calls it in only one
>	other script.
 
***

#### HANDOFF
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Passes additional commands data to the new master.
 
***

#### _Command_Rebuild
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Rebuilds the hashmap of command pointers after a master script hands off.
 
***

#### Command_IncOPCR
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	This function, and the three other related ones, increment and decrement the
>	number of callbacks known to exist on the server.  If they are 0, there's no
>	point trying to call them on errors etc.
 
***

#### Command_GetEmptySlot
>* **Parameters:**

>* **Returns:**
>	* The first available slot in "YSI_g_sCommands".
>* **Remarks:**
>	-
 
***

#### Command_Add
>* **Parameters:**
>	* `cmd[]`: cmd[]_INFO
>	* `ptr`: ptr_INFO
>	* `id`: id_INFO
>* **Returns:**
>	* The command's ID.
>* **Remarks:**
>	This was an external API function, but there is no reason for it to be as it
>	is called for all found commands at mode start.
 
***

#### _Command_GetDisplay
>* **Parameters:**
>	* `f`: f_INFO
>	* `p`: p_INFO
>* **Returns:**
>	* The name of a command for a single player.
>* **Remarks:**
>	-
 
***

