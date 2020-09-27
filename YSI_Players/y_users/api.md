#### Player_Reload
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Reload a player's basic data when they change name.
 
***

#### Player_Preload
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Loads a player's data to an array.
 
***

#### Player_TryLogin
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `password[]`: password[]_INFO
>	* `f`: f_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Tries to log in a player - hashes and checks their password and if it's
>	right calls the core login code.  It doesn't matter WHICH script does this
>	as they ALL get called and ALL track the login status of a player.
 
***

#### Player_ForceLogin
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Like "Player_TryLogin" but doesn't take a password so always works.
 
***

#### Player_RemoveEntry
>* **Parameters:**
>	* `name[]`: name[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for removing data.
 
***

#### Player_WriteString
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `data[]`: data[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for strings.
 
***

#### Player_WriteInt
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for integers.
 
***

#### Player_WriteHex
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for integers to be written as hex values.
 
***

#### Player_WriteBin
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for integers to be written as binary values.
 
***

#### Player_WriteBool
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for booleans.
 
***

#### Player_WriteFloat
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `Float:data`: Float:data_INFO
>	* `accuracy`: accuracy_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for floats.  Uses custom code instead of
>	format() as it's actually faster for something simple like this.
 
***

#### Player_HashPass
>* **Parameters:**
>	* `pass[]`: pass[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Based on my Dad's hash system but slightly modifed.  Updated for reverse
>	compatability with other login systems.  Needs more code for Whirlpool.
 
***

#### Player_TryRegister
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `string:password[]`: string:password[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Register the player with the given password if there is no-one else with the
>	name already.  Or log them in if the username and password match an existing
>	account.  Note that there is no "Player_ForceRegister" as it would do the
>	same thing with no less parameters (a password MUST be given to write in the
>	file).
 
***

#### Player_RewritePreload
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	When a player's preload data is modifed (new bit data or changed password),
>	it needs to be written back out to file.
 
***

#### Player_TryGroup
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `string:other[]`: string:other[]_INFO
>	* `string:password[]`: string:password[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Links a player with an existing player such that they share all stats.
 
***

#### Player_ForceGroup
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `string:other[]`: string:other[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Like "Player_TryGroup", but doesn't take a password and instead just uses
>	the password of the old player (hashed).
 
***

#### Player_Reload
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Reload a player's basic data when they change name.
 
***

#### Player_Preload
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Loads a player's data to an array.
 
***

#### _Player_IsLoggedIn
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -1 - Registered but not logged in.
>	* 0  - Not registered.
>	* 1+ - Logged in, and their YID.
>* **Remarks:**
>	This is a remote function called in existing scripts when a new script
>	starts.  If the player is logged in it returns their YID.  If a player is
>	registered but not logged in it returns "-1".  Otherwise it returns 0.
 
***

#### OnPlayerDisconnect
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `reason`: reason_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Logs the player out if they're logged in.
 
***

#### Player_TryLogin
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `password[]`: password[]_INFO
>	* `f`: f_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Tries to log in a player - hashes and checks their password and if it's
>	right calls the core login code.  It doesn't matter WHICH script does this
>	as they ALL get called and ALL track the login status of a player.
 
***

#### Player_ForceLogin
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Like "Player_TryLogin" but doesn't take a password so always works.
 
***

#### Player_RemoveEntry
>* **Parameters:**
>	* `name[]`: name[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for removing data.
 
***

#### Player_WriteString
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `data[]`: data[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for strings.
 
***

#### Player_WriteInt
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for integers.
 
***

#### Player_WriteHex
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for integers to be written as hex values.
 
***

#### Player_WriteBin
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for integers to be written as binary values.
 
***

#### Player_WriteBool
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for booleans.
 
***

#### Player_WriteFloat
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `Float:data`: Float:data_INFO
>	* `accuracy`: accuracy_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for floats.  Uses custom code instead of
>	format() as it's actually faster for something simple like this.
 
***

#### Player_HashPass
>* **Parameters:**
>	* `pass[]`: pass[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Based on my Dad's hash system but slightly modifed.  Updated for reverse
>	compatability with other login systems.  Needs more code for Whirlpool.
 
***

#### Player_TryRegister
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `string:password[]`: string:password[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Register the player with the given password if there is no-one else with the
>	name already.  Or log them in if the username and password match an existing
>	account.  Note that there is no "Player_ForceRegister" as it would do the
>	same thing with no less parameters (a password MUST be given to write in the
>	file).
 
***

#### Player_RewritePreload
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	When a player's preload data is modifed (new bit data or changed password),
>	it needs to be written back out to file.
 
***

#### Player_TryGroup
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `string:other[]`: string:other[]_INFO
>	* `string:password[]`: string:password[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Links a player with an existing player such that they share all stats.
 
***

#### Player_ForceGroup
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `string:other[]`: string:other[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Like "Player_TryGroup", but doesn't take a password and instead just uses
>	the password of the old player (hashed).
 
***

#### Player_Reload
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Reload a player's basic data when they change name.
 
***

#### Player_Preload
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Loads a player's data to an array.
 
***

#### Player_TryLogin
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `password[]`: password[]_INFO
>	* `f`: f_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Tries to log in a player - hashes and checks their password and if it's
>	right calls the core login code.  It doesn't matter WHICH script does this
>	as they ALL get called and ALL track the login status of a player.
 
***

#### Player_ForceLogin
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Like "Player_TryLogin" but doesn't take a password so always works.
 
***

#### Player_RemoveEntry
>* **Parameters:**
>	* `name[]`: name[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for removing data.
 
***

#### Player_WriteString
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `data[]`: data[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for strings.
 
***

#### Player_WriteInt
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for integers.
 
***

#### Player_WriteHex
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for integers to be written as hex values.
 
***

#### Player_WriteBin
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for integers to be written as binary values.
 
***

#### Player_WriteBool
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for booleans.
 
***

#### Player_WriteFloat
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `Float:data`: Float:data_INFO
>	* `accuracy`: accuracy_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Wrapper for Player_AddToBuffer for floats.  Uses custom code instead of
>	format() as it's actually faster for something simple like this.
 
***

#### Player_HashPass
>* **Parameters:**
>	* `pass[]`: pass[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Based on my Dad's hash system but slightly modifed.  Updated for reverse
>	compatability with other login systems.  Needs more code for Whirlpool.
 
***

#### Player_TryRegister
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `string:password[]`: string:password[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Register the player with the given password if there is no-one else with the
>	name already.  Or log them in if the username and password match an existing
>	account.  Note that there is no "Player_ForceRegister" as it would do the
>	same thing with no less parameters (a password MUST be given to write in the
>	file).
 
***

#### Player_RewritePreload
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	When a player's preload data is modifed (new bit data or changed password),
>	it needs to be written back out to file.
 
***

#### Player_TryGroup
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `string:other[]`: string:other[]_INFO
>	* `string:password[]`: string:password[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Links a player with an existing player such that they share all stats.
 
***

#### Player_ForceGroup
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `string:other[]`: string:other[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Like "Player_TryGroup", but doesn't take a password and instead just uses
>	the password of the old player (hashed).
 
***

