#### Area_GetEmptySlotCount
>* **Parameters:**

>* **Returns:**
>	* Number of unused area slots.
>* **Remarks:**
>	-
 
***

#### Area_AddSlots
>* **Parameters:**
>	* `num`: num_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Actually removes slots from the unused count.
 
***

#### Area_IsActive
>* **Parameters:**
>	* `area`: area_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	An area slot could be used but still invalid if it's not the first slot in
>	an area set.
 
***

#### Area_Debug
>* **Parameters:**
>	* `area`: area_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Area_GetFreeSlot
>* **Parameters:**

>* **Returns:**
>	* Next available slot.
>* **Remarks:**
>	Gets an empty slot, removes it from the unused list and returs a pointer.
 
***

#### Area_Delete
>* **Parameters:**
>	* `area`: area_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	You can only remove areas which are at the start of a list.
 
***

#### Area_DoRemove
>* **Parameters:**
>	* `zone`: zone_INFO
>	* `start`: start_INFO
>	* `end`: end_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Very tightly integrated with "Area_Delete", to the point where I could just
>	make them one function if I wanted (but I won't).
 
***

#### Area_GetZones
>* **Parameters:**
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>* **Returns:**
>	* All the zones this position overlaps.
>* **Remarks:**
>	The most zones you can be in at once is 9 - I_, I_S, I_E, I_SE, X_, X_S,
>	X_E, X_SE, Z_ (or similar corners - NOT in O_ though).
 
***

#### Area_DetermineZone
>* **Parameters:**
>	* `Float:minx`: Float:minx_INFO
>	* `Float:miny`: Float:miny_INFO
>	* `Float:maxx`: Float:maxx_INFO
>	* `Float:maxy`: Float:maxy_INFO
>	* `area`: area_INFO
>	* `last`: last_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Finds the smallest zone that this area will fit in completely.  Note that
>	due to a limitation in the code, any zones with a node touching the upper
>	edge of a zone will spill in to the next zone too.  Only lower zone edges
>	are inclusive.
 
***

#### Area_AddTo
>* **Parameters:**
>	* `area`: area_INFO
>	* `set`: set_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Area_SetAllWorlds
>* **Parameters:**
>	* `area`: area_INFO
>	* `set`: set_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Area_Add
>* **Parameters:**
>	* `type`: type_INFO
>	* `...`: ..._INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Types:
>	CUBE, Cube
>	CUBOID, Cuboid
>	BOX, Box
>	CIRCLE, Circle
>	OVAL, Oval
>	OVOID, Ovoid
>	SPHERE, Sphere
>	POLY, Poly
 
***

#### Area_AddCube
>* **Parameters:**
>	* `Float:minx`: Float:minx_INFO
>	* `Float:miny`: Float:miny_INFO
>	* `Float:minx`: Float:minx_INFO
>	* `Float:maxx`: Float:maxx_INFO
>	* `Float:maxy`: Float:maxy_INFO
>	* `Float:maxz`: Float:maxz_INFO
>* **Returns:**
>	* Area slot or NO_AREA
>* **Remarks:**
>	-
 
***

#### Area_AddBox
>* **Parameters:**
>	* `Float:minx`: Float:minx_INFO
>	* `Float:miny`: Float:miny_INFO
>	* `Float:maxx`: Float:maxx_INFO
>	* `Float:maxy`: Float:maxy_INFO
>* **Returns:**
>	* Area slot or NO_AREA
>* **Remarks:**
>	-
 
***

#### Area_AddCircle
>* **Parameters:**
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:r`: Float:r_INFO
>	* `Float:height`: Float:height_INFO
>	* `Float:depth`: Float:depth_INFO
>* **Returns:**
>	* Area slot or NO_AREA
>* **Remarks:**
>	Technically a cylinder, no lower bound (ceiling added cos there was a
>	spare slot in the 4 float design which may as well have been used).
 
***

#### Area_AddOval
>* **Parameters:**
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:rx`: Float:rx_INFO
>	* `Float:ry`: Float:ry_INFO
>	* `Float:height`: Float:height_INFO
>	* `Float:depth`: Float:depth_INFO
>* **Returns:**
>	* Area slot or NO_AREA
>* **Remarks:**
>	Technically a cylinder, no lower bound (ceiling added cos there was a
>	spare slot in the 4 float design which may as well have been used).
 
***

#### Area_AddSphere
>* **Parameters:**
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `Float:r`: Float:r_INFO
>* **Returns:**
>	* Area slot or NO_AREA
>* **Remarks:**
>	-
 
***

#### Area_AddOvoid
>* **Parameters:**
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `Float:rx`: Float:rx_INFO
>	* `Float:ry`: Float:ry_INFO
>	* `Float:rz`: Float:rz_INFO
>* **Returns:**
>	* Area slot or NO_AREA
>* **Remarks:**
>	-
 
***

#### Area_AddPoly
>* **Parameters:**
>	* `Float:...`: Float:..._INFO
>* **Returns:**
>	* Area slot or NO_AREA
>* **Remarks:**
>	Creates an irregular shape to detect players in.  This is a 2d area made
>	up of a load of XY points.  If an odd number of parameters is passed the
>	extra one is assumed to be a ceiling so you can ignore interiors or planes.
>	The height parameter goes first as it's easiest to check.
>	This is one of a few functions still written using the master system at a
>	low level (the other obvious one is "Class_Add").
 
***

#### Area_OnPlayerConnect
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Area_loop
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Main processing for the system.  Takes one player and checks if they're in
>	some sort of range of somewhere.
 
***

#### Area_CheckArea
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `world`: world_INFO
>	* `area`: area_INFO
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Checks if the given position is in the give area.  All parameters are passed
>	to avoid calling functions over and over and over again.  If the return is
>	not true, "area" is updated to the next one in the chain.
 
***

#### Area_IsInCircle
>* **Parameters:**
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `Float:bounds[]`: Float:bounds[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Checks if a point is in a given circle.
 
***

#### Area_IsInSphere
>* **Parameters:**
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `Float:bounds[]`: Float:bounds[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Checks if a point is in a given sphere.
 
***

#### Area_IsInOvoid
>* **Parameters:**
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `Float:bounds[]`: Float:bounds[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Checks if a point is in a given ovoid.
 
***

#### Area_IsInPoly
>* **Parameters:**
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `header`: header_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Based on IsPlayerInAreaEx by koolk in the useful functions topic.  The
>	passed pointer is the pointer to the first set of co-ordinates in a one-
>	way not looping linked list of points in the polygod as the data may be
>	spread throughout the areas array.  This is as otherwise there may be
>	enough free spaces but not in one block.
>	The code first checks if there is a height component as it's the easiest
>	to check thus may save a load of pointless processing.  If this passes it
>	then does the main loop.  This loops till there are no points left to do
>	(monitored by decreasing count).  When 2 points (four pieces of data) have
>	been checked the poiner for the data is moved on to the next group and the
>	checking continues.
>	For simplicity's sake (and thus speed's sake) the lower pointes from the
>	last check are saved amd used as the upper points for the next check to
>	avoid loads of repeated array accesses and saving the last array position.
 
***

#### Area_IsInCube
>* **Parameters:**
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `Float:lower[]`: Float:lower[]_INFO
>	* `Float:upper[]`: Float:upper[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Checks if a point is in a given cube.  This is another multi slot shape
>	but is much simpler than the poly as it's always 2 slots so we can easilly
>	get the data in one lump.
 
***

#### Area_IsInBox
>* **Parameters:**
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:bounds[]`: Float:bounds[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Checks if a point is in a given box.  There is no height check with this
>	one as any one area slot has 4 points which for this are upper and lower
>	x and y, adding a height check would make it require 2 slots and basically
>	make it a cube check.
 
***

#### Area_GetPlayerArea
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* The area a player is in or -1.
>* **Remarks:**
>	Deprecated.
 
***

#### _Area_SetPlayerAreas
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `idx`: idx_INFO
>	* `area`: area_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Sets a player as in a slot.
 
***

#### _Area_GetPlayerAreas|Area_GetPlayerAreas
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `idx`: idx_INFO
>* **Returns:**
>	* The area a player is in or -1.
>* **Remarks:**
>	Replaces Area_GetPlayerArea for multiple areas.  Includes an internal
>	version for tighter loops within this code to use once it is known that a
>	player exists, and without using the global function system.
 
***

#### Area_SetPlayer
>* **Parameters:**
>	* `area`: area_INFO
>	* `playerid`: playerid_INFO
>	* `set`: set_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Area_GetPlayer
>* **Parameters:**
>	* `area`: area_INFO
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Can the player USE this area (not are they in it)?
 
***

#### Area_SetWorld
>* **Parameters:**
>	* `area`: area_INFO
>	* `world`: world_INFO
>	* `set`: set_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Area_GetWorld
>* **Parameters:**
>	* `area`: area_INFO
>	* `world`: world_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Area_SetAllPlayers
>* **Parameters:**
>	* `area`: area_INFO
>	* `set`: set_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Area_IsValid
>* **Parameters:**
>	* `area`: area_INFO
>* **Returns:**
>	* Is the passed area valid and active.
>* **Remarks:**
>	-
 
***

#### Area_IsEmpty
>* **Parameters:**
>	* `area`: area_INFO
>* **Returns:**
>	* Is the passed area valid and empty.
>* **Remarks:**
>	Currently very slow as it has to loop through multiple players!  I may add
>	an entry counter to zones to make this O(1) instead of O(nm).
 
***

#### Area_SetCallback
>* **Parameters:**
>	* `area`: area_INFO
>	* `callback:callback`: callback:callback_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Adds a y_inline style callback (publics included) to an area to be called
>	when a player enters it.  This is NOT a remote function and instead records
>	the data locally to call functions in the correct script (or they'll just
>	end up crashing as you will be jumping to an arbitrary address in a script
>	that doesn't have sensible code at that address.
 
***

#### Area_DoEnter
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `areaid`: areaid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Area_DoLeave
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `areaid`: areaid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

