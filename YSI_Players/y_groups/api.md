#### GROUP_CHAIN
>* **Parameters:**
>	* `%9`: %9_INFO
>	* `%0`: %0_INFO
>	* `%1`: %1_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Calls the correct function to chain a function with the given number of
>	parameters, calls the function stored in a variable and passes parameters
>	BY REFERENCE - ALL of them!
 
***

#### GROUP_ADD
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This sets up a temporary environment, during which all items are ONLY added
>	to the specified group and no others, with no complex extra code required.
 
***

#### _Group_FakePlayer
>* **Parameters:**
>	* `p`: p_INFO
>	* `Bit:g[]`: Bit:g[]_INFO
>	* `s`: s_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Pretend the player is in all the groups they won't be in shortly so that
>	they have a complete blank slate when they connect - the system KNOWS they
>	are not in some groups and are in others.
>	Uses an unusual size in "g" to reduce the string length.
 
***

#### Group_IsValid
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>* **Returns:**
>	* bool: - Is the group active and valid?
>* **Remarks:**
>	-
 
***

#### Group_Destroy
>* **Parameters:**
>	* `Group:group`: Group:group_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### _Group_TryRemove
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Removes all groups purely owned by the calling script.
 
***

#### OnPlayerDisconnect
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `reason`: reason_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Removes this player from all groups.  Unfortunately there's no way to
>	combine multiple iterator removals to improve their efficiency - currently
>	they have to loop through all previous ones to find the one to modify to
>	skip over that player.  I did debate updating foreach to doubly-linked
>	lists for this reason - that would make reverse traversal and removal faster
>	by doubling memory consumption but only very slightly affecting adds.
 
***

#### OnPlayerConnect
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	The player may not have ACTUALLY joined the server, they may have just been
>	added to this newly loaded script.  In that case we need to initialise the
>	locally stored group data to the new data.  Of course, if this script is the
>	group master, then we need to do significantly more!  This is more complex
>	than other scripts with master as they don't have some things to do in non-
>	master scripts as well, whereas this one does.
 
***

#### _Group_InitPlayer
>* **Parameters:**
>	* `p`: p_INFO
>	* `master`: master_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Request all a player's groups from the master system.
 
***

#### _Group_SetSome
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `group`: group_INFO
>* **Returns:**
>	* A new array of groups.
>* **Remarks:**
>	Takes a group and adds a player to that group and every child group of
>	which they are not already a member.
 
***

#### Group_SetPlayer
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>	* `p`: p_INFO
>	* `bool:s`: bool:s_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Will in some cases update all settings, unless they are being added through
>	a recursive call due to being added to child groups.
>	There is an internal version that ONLY adds them to the group and DOES NOT
>	update any of their other settings.  As a result it has less checks in it.
 
***

#### _Group_SetPlayer
>* **Parameters:**
>	* `p`: p_INFO
>	* `Bit:g[bits<_MAX_GROUPS_G>]`: Bit:g[bits<_MAX_GROUPS_G>]_INFO
>	* `s`: s_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Pass a list of groups that the player is now in or not in.  This is a
>	complete replacement for their existing list of groups, and so multiple
>	updates can be done at once.
 
***

#### Group_SetBalancedInternal
>* **Parameters:**
>	* `p`: p_INFO
>	* `Group:gs[]`: Group:gs[]_INFO
>	* `c`: c_INFO
>* **Returns:**
>	* The group they have been added to.
>* **Remarks:**
>	Chains the call with "Group_SetPlayer" to use its hierarchy code.
 
***

#### Group_SetBalanced
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `{Group, _}:...`: {Group, _}:..._INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Puts a player in whichever of the given groups currently has the least
>	players.
 
***

#### Group_GetPlayer
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>	* `p`: p_INFO
>* **Returns:**
>	* Is this player in this group?
>* **Remarks:**
>	-
 
***

#### Group_GetName
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>* **Returns:**
>	* string:
>* **Remarks:**
>	Gets the name of a group.
 
***

#### Group_GetID
>* **Parameters:**
>	* `string:name[]`: string:name[]_INFO
>* **Returns:**
>	* Group: - The ID of the group with this name.
>* **Remarks:**
>	-
 
***

#### Group_SetGang
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>	* `bool:n`: bool:n_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	I actually can't remember what the "Gang" setting on a group does - I don't
>	think it actually does anything in the latest code version!
 
***

#### Group_GetGang
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>* **Returns:**
>	* bool:
>* **Remarks:**
>	I still don't remember what this once did!
 
***

#### Group_SetColor|Group_SetColour
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>	* `c`: c_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This colour is not actually currently used anywhere.
 
***

#### Group_GetColor|Group_GetColour
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>* **Returns:**
>	* An RGBA colour.
>* **Remarks:**
>	This colour is not actually currently used anywhere.
 
***

#### Group_GetCount
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>* **Returns:**
>	* The number of players in the group.
>* **Remarks:**
>	-
 
***

#### Group_Create
>* **Parameters:**
>	* `string:name[]`: string:name[]_INFO
>* **Returns:**
>	* The group ID with a tag of "Group:", or "INVALID_GROUP".
>* **Remarks:**
>	Group_Create - Local function to detect and "NULL"ify empty strings.
>	_Group_Create - Global function that does most of the work.
>	_Group_CreateChain - Remote function that updates all master scripts with
>	the new group's existence.
 
***

#### Group
>* **Parameters:**
>	* `Group:group`: Group:group_INFO
>	* `start`: start_INFO
>* **Returns:**
>	* The next player.
>* **Remarks:**
>	Internal implementation of the "Group()" iterator for "foreach".  Returns
>	all the players in a group one at a time.  Now just wraps the "GroupPlayers"
>	iterator that is only stored in the GROUP master script.
 
***

#### CreatedGroup
>* **Parameters:**
>	* `start`: start_INFO
>* **Returns:**
>	* The next group.
>* **Remarks:**
>	Internal implementation of the "CreatedGroup()" iterator for "foreach".
>	Returns all the groups that exist.
 
***

#### ChildGroup
>* **Parameters:**
>	* `parent`: parent_INFO
>	* `start`: start_INFO
>* **Returns:**
>	* The next group.
>* **Remarks:**
>	Internal implementation of the "ChildGroup()" iterator for "foreach".
>	Returns all the groups that are a child of the provided group.
 
***

#### _Y_G@C_0|_Y_G@C_1|_Y_G@C_2|_Y_G@C_3
>* **Parameters:**
>	* `func`: func_INFO
>	* `...`: ..._INFO
>* **Returns:**
>	* 0 - ALWAYS zero to make "_gchain" work properly.
>* **Remarks:**
>	Basically function indirection, call a function through a pointer and use
>	the compiler to figure out the assembly to generate instead of having a
>	run-time loop inside a single instance of this function.  Using just one
>	macro ("GROUP_CHAIN") one of these four functions are selected and called.
>	Adding more is fairly trivial too, the parameters are just:
>	#emit PUSH.S     <16 + n * 4>
>	#emit PUSH.S     ...
>	#emit PUSH.S     20
>	#emit PUSH.S     16
>	#emit PUSH.C     <n * 4>
 
***

#### Group_SetGroup
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>	* `el`: el_INFO
>	* `bool:s`: bool:s_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	IMPORTANT NOTE: Groups are SLIGHTLY different to other systems - if you
>	REMOVE a group from another group then players WILL NOT be removed from
>	that second group, or any child groups.
 
***

#### Group_SetGlobalGroup
>* **Parameters:**
>	* `el`: el_INFO
>	* `bool:s`: bool:s_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	If "s" is true, then one element is added to the global group.  False it is
>	removed.
 
***

#### Group_Get...
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>	* `Group:el`: Group:el_INFO
>* **Returns:**
>	* bool: Does the group have the element?
>* **Remarks:**
>	This has no "active" checks on the groups as if they aren't active but are
>	in range, then "YSI_g_sChildGroups" will return false anyway.  Extra checks
>	are therefore just a waste of time.
 
***

#### Group_GetGlobal...
>* **Parameters:**
>	* `Group:el`: Group:el_INFO
>* **Returns:**
>	* bool: Does the global group have the element?
>* **Remarks:**
>	-
 
***

#### Group_IsDescendant
>* **Parameters:**
>	* `Group:p`: Group:p_INFO
>	* `Group:c`: Group:c_INFO
>* **Returns:**
>	* bool: Is the second group related to the first?
>* **Remarks:**
>	Now uses implicit, not explicit, recursion.
 
***

#### _GROUP_INITIALISE
>* **Parameters:**
>	* `x`: x_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	The name is a macro, so this function isn't actually called this.  This is
>	called when a new element is created, and as such it is NOT chained to other
>	parts of the groups system because each part handles one type of element.
>	Loop through all players and set up the element for them if they are in a
>	group that this is also in by default.
>	If x is "_GROUP_MAKE_LIMIT" then this is the test used in OnPlayerConnect in
>	various libraries to see if the groups system exists, and if not locally
>	initialise the player instead of leaving it up to this system.
 
***

#### Group_Set...
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>	* `el`: el_INFO
>	* `bool:s`: bool:s_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	If "s" is true, then one element is added to the current group.  False it is
>	removed.
 
***

#### Group_Get...
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>	* `el`: el_INFO
>* **Returns:**
>	* bool: Does the group have the element?
>* **Remarks:**
>	-
 
***

#### Group_Set...Default
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>	* `bool:s`: bool:s_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	If "s" is true, then all elements are added to this group (i.e. the default
>	is set to true and all previous settings are wiped out).  If it is false
>	then all elements are removed and a full update is done.
 
***

#### Group_Set...New
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>	* `bool:s`: bool:s_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Similar to "Group_Set...Default", but doesn't reset all existing elements,
>	just sets the permissions for any future items.
 
***

#### Group_Exclusive...
>* **Parameters:**
>	* `Group:g`: Group:g_INFO
>	* `_GROUP_MAKE_TAG:el`: _GROUP_MAKE_TAG:el_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Add this element to ONLY this group and remove it from any others it might
>	already be in.  This is basically a simplified version of "GROUP_ADD".
 
***

#### Group_SetGlobal...
>* **Parameters:**
>	* `el`: el_INFO
>	* `bool:s`: bool:s_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	If "s" is true, then one element is added to the global group.  False it is
>	removed.
 
***

#### Group_GetGlobal...
>* **Parameters:**
>	* `el`: el_INFO
>* **Returns:**
>	* bool: Does the global group have the element?
>* **Remarks:**
>	-
 
***

#### Group_SetGlobal...Default
>* **Parameters:**
>	* `bool:s`: bool:s_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	If "s" is true, then all elements are added to the global group (i.e. the
>	default is set to true and all previous settings are wiped out).  If it is
>	false then all elements are removed and a full update is done.
 
***

#### Group_SetGlobal...New
>* **Parameters:**
>	* `bool:s`: bool:s_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	All elements created FROM THIS POINT ON will have this default setting.
 
***

#### Group_GlobalExclusive...
>* **Parameters:**
>	* `_GROUP_MAKE_TAG:el`: _GROUP_MAKE_TAG:el_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Add this element to ONLY the global group and remove it from any others it
>	might already be in.
 
***

#### Group_FullPlayerUpdate
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `el`: el_INFO
>	* `previous`: previous_INFO
>	* `current`: current_INFO
>	* `reference`: reference_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	I did have a good reason for calling this "FU", but I forgot it!  Anyway,
>	the state of some groups has changed - either a player's groups or an
>	elements groups have changed.  If the player could previously see the
>	element but now can't, hide it.  If the player previously couldn't see it
>	but now can, show it.  If there is no change do nothing.  The old version of
>	this library would just re-show the element even if they could already see
>	it, but this was a bad design as it could incur large overheads in other
>	libraries when they had to do IO to enable or disable something for a
>	player.
>	The change can be in either the player's groups or the element's groups,
>	either way this code will work regardless.
 
***

#### _yGI
>* **Parameters:**
>	* `&ni`: &ni_INFO
>	* `&na`: &na_INFO
>	* `&nu`: &nu_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This function is called when the group system first starts up to initialise
>	the global group and all the various function pointers.  The way the
>	"_gchain" macro works means that the fact that "ni" etc are references is
>	irrelevant; however, it does make the code LOOK much nicer and like
>	assigning to the variables does have some wider meaning.
>	If this is called with "ni = -1", it is special code to temporarily set or
>	restore the defaults for use with the "GROUP_ADD" macro.  So basically, it
>	is poor design giving two distinct uses to a single function.
 
***

#### _yGA
>* **Parameters:**
>	* `&group`: &group_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	The given group was just created, loop over all elements and make sure they
>	are NOT in this group - only the global group has a "default default" of
>	true.  We don't need to update any players with this as no-one will ever be
>	in a brand new group.
 
***

#### _yGU
>* **Parameters:**
>	* `&pid`: &pid_INFO
>	* `Bit:p[]`: Bit:p[]_INFO
>	* `Bit:c[]`: Bit:c[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	The player "pid" just joined or left a group (or groups - can do multiple).
>	Update their visibility accordingly.  This function is ONLY called if there
>	is a CHANGE - earlier functions confirm that they weren't already in (or
>	not) this group(s) before the call.
 
***

#### _GROUP_UNIQUE_FUNCTION
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Calls all functions to correctly include them in the AMX when required.
>	Also all variables as it turns out they were a problem too.
 
***

