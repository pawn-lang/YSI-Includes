#### Player_InSelection
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* Is this player currently in the class selection screen?
>* **Remarks:**
>	-
 
***

#### Player_HasSpawned
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* Has this player ever spawned?
>* **Remarks:**
>	-
 
***

#### Player_IsSpawned
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* Is this player spawned now?
>* **Remarks:**
>	Returns true if they are not in class selection, and if they have ever
>	spawned.  It could be that both "Player_IsSpawned" and "Player_InSelection"
>	return "false" - if they haven't even reached the class selection screen yet
>	(mainly happens in "OnPlayerConnect").
 
***

#### Class_OnPlayerConnect
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Reset all the data on this player's current classes.
 
***

#### Class_OnPlayerRequestClass
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `class`: class_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Not the first call of this function by y_classes.
 
***

#### Class_OnPlayerSpawn
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Sets a player's position based on skin.
 
***

#### _Class_IsActive
>* **Parameters:**
>	* `classid`: classid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### _Class_IsValid
>* **Parameters:**
>	* `classid`: classid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### _Class_Enabled
>* **Parameters:**
>	* `classid`: classid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Class_X
>* **Parameters:**
>	* `classid`: classid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Class_Y
>* **Parameters:**
>	* `classid`: classid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Class_Z
>* **Parameters:**
>	* `classid`: classid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Class_A
>* **Parameters:**
>	* `classid`: classid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Class_Skin
>* **Parameters:**
>	* `classid`: classid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Class_Class
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Creates three real player classes so you can scroll correctly with the
>	direction being detected.
 
***

#### Class_Goto
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `playerclass`: playerclass_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Does the visual faking through "SetPlayerSkin", and also calls
>	"SetSpawnInfo" to avoid any lag from "SetPlayerPos" under "OnPlayerSpawn".
 
***

#### Class_OnPlayerRequestSpawn
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Has inbuilt protection for a bug where selections aren't correctly
>	debounced so you can press shift twice at once which can mess up some
>	scripts (e.g. the example team selection script).  Calls
>	OnPlayerRequestSpawnEx with an additional class parameter.
 
***

#### Class_OnPlayerSpawn
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Sets a player's position based on skin.
 
***

#### Class_OnPlayerConnect
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Reset all the data on this player's current classes.
 
***

#### _CLASS_WEAPON_CODE
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Converts the variable arguments to an array.
 
***

#### Class_Add
>* **Parameters:**
>	* `skin`: skin_INFO
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `Float:a`: Float:a_INFO
>	* `...`: ..._INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Pretty much AddPlayerClass but allows greater control over the classes.
>	Now has infinate (MAX_CLASS_SPAWN_WEAPONS) spawn weapons.  This is one of
>	the few API functions which is not entirely remote.  This is because it has
>	variable parameters which is need to collect in to a single array to pass to
>	the remote function.
 
***

#### Class_AddEx
>* **Parameters:**
>	* `forgroup`: forgroup_INFO
>	* `setgroup`: setgroup_INFO
>	* `skin`: skin_INFO
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `Float:a`: Float:a_INFO
>	* `...`: ..._INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Pretty much AddPlayerClass but allows greater control over the classes.
>	Now has infinate (MAX_CLASS_SPAWN_WEAPONS) spawn weapons.
 
***

#### Class_AddForGroup
>* **Parameters:**
>	* `group`: group_INFO
>	* `skin`: skin_INFO
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `Float:a`: Float:a_INFO
>	* `...`: ..._INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Adds a class only people in the specified group can use.
 
***

#### Class_AddWithGroupSet
>* **Parameters:**
>	* `group`: group_INFO
>	* `skin`: skin_INFO
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `Float:a`: Float:a_INFO
>	* `...`: ..._INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Adds a class which puts you in the specified group when selected.
 
***

#### Class_AddClass
>* **Parameters:**
>	* `skin`: skin_INFO
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `Float:a`: Float:a_INFO
>	* `weapons[]`: weapons[]_INFO
>	* `count`: count_INFO
>	* `forgroup`: forgroup_INFO
>	* `asgroup`: asgroup_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Does the hard work.  This took a long time to get working correctly with the
>	new master system, infact getting just this one function to compile took a
>	major re-working of the macros to reduce the length of intermediate stages.
 
***

#### Class_HasGroup
>* **Parameters:**
>	* `classid`: classid_INFO
>	* `Group:group`: Group:group_INFO
>* **Returns:**
>	* Does this class add players to the given group on spawn?
>* **Remarks:**
>	-
 
***

#### Class_Enable
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Class_Delete
>* **Parameters:**
>	* `classid`: classid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Completely removes a class from the system.
 
***

#### Class_SetPlayer
>* **Parameters:**
>	* `classid`: classid_INFO
>	* `playerid`: playerid_INFO
>	* `set`: set_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Class_GetPlayer
>* **Parameters:**
>	* `classid`: classid_INFO
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Class_Get
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Class_OnPlayerRequestClass
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `class`: class_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	The input is one of the three real classes used to detect selected
>	direction of alteration.  Scans for a class the player is allowed to use
>	and hot swaps it out.  Uses SetPlayerSkin AND SetSpawnInfo to combat bugs
>	with calling this from OnPlayerRequestSpawn (e.g. the example team script).
>	Calls OnPlayerRequestClassEx with the current internal class not the real
>	one.
>	Last thing in the file to be simpler to call directly.  If we ever have a
>	more complex ALS hook on this callback the main body of this code will have
>	to be moved in to its own function.  As indeed it now does!
 
***

