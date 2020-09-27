#### Property_IsActive
>* **Parameters:**
>	* `prop`: prop_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Property_ResetMaxProperties
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Allows people to own as many properties as they like at
>	once.
 
***

#### Property_SetOption
>* **Parameters:**
>	* `slot`: slot_INFO
>	* `value`: value_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Can't be changed except from 0 to 1.
 
***

#### Property_GetOption
>* **Parameters:**
>	* `slot`: slot_INFO
>	* `flags`: flags_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Property_GivePlayerWeapon
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `slot`: slot_INFO
>	* `ammo`: ammo_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gives a player a weapon by slot instead of weaponid or assignes armour.
 
***

#### Property_SetRebuyDelay
>* **Parameters:**
>	* `delay`: delay_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Property_IsValid
>* **Parameters:**
>	* `property`: property_INFO
>* **Returns:**
>	* Is the property a valid active property.
>* **Remarks:**
>	-
 
***

#### Property_IsOwner
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `prop`: prop_INFO
>	* `flags`: flags_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Property_SetMaxProperties
>* **Parameters:**
>	* `count`: count_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Sets the number of properties a player can own at once.
 
***

#### Property_SetMaxHouses
>* **Parameters:**
>	* `count`: count_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Sets the number of houses a player can own at once.
 
***

#### Property_GetType
>* **Parameters:**
>	* `property`: property_INFO
>* **Returns:**
>	* 0 if invalid or type.
>* **Remarks:**
>	-
 
***

#### Property_Property
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Sets variable initial states.
 
***

#### DestroyProperty
>* **Parameters:**
>	* `property`: property_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### CreateHouse
>* **Parameters:**
>	* `Float:extX`: Float:extX_INFO
>	* `Float:extY`: Float:extY_INFO
>	* `Float:extZ`: Float:extZ_INFO
>	* `Float:intX`: Float:intX_INFO
>	* `Float:intY`: Float:intY_INFO
>	* `Float:intZ`: Float:intZ_INFO
>	* `interior`: interior_INFO
>	* `world`: world_INFO
>	* `price`: price_INFO
>	* `checkpoint`: checkpoint_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Creates a buyable property (business).
 
***

#### CreateProperty
>* **Parameters:**
>	* `name[]`: name[]_INFO
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `price`: price_INFO
>	* `reward`: reward_INFO
>	* `interval`: interval_INFO
>	* `sell`: sell_INFO
>	* `multi`: multi_INFO
>	* `reduce`: reduce_INFO
>* **Returns:**

>* **Remarks:**
>	Creates a buyable property (business).
 
***

#### CreateBank
>* **Parameters:**
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `name[]`: name[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### CreateAmmunation
>* **Parameters:**
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `spawn`: spawn_INFO
>	* `instant`: instant_INFO
>	* `...`: ..._INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	spawn and instant can BOTH be 1.  The format of the additional parameters
>	is:
>	weapon, ammo, price
>	They MUST come in sets of three of the function will fail.  Weapon is in
>	the form of the WEAPON_ defines in a_samp or WEAPON_ARMOUR.
 
***

#### CreateMoneyArea
>* **Parameters:**
>	* `area`: area_INFO
>	* `money`: money_INFO
>	* `interval`: interval_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This function has internal checking for invalid areas so you can just pass
>	the return from an Area_ funtion directly.
 
***

#### CreateMoneyPoint
>* **Parameters:**
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:z`: Float:z_INFO
>	* `Float:s`: Float:s_INFO
>	* `money`: money_INFO
>	* `interval`: interval_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Like CreateMoneyArea but you must be in a checkpoint.
 
***

#### CreateTeleport
>* **Parameters:**
>	* `Float:sx`: Float:sx_INFO
>	* `Float:sy`: Float:sy_INFO
>	* `Float:sz`: Float:sz_INFO
>	* `Float:tz`: Float:tz_INFO
>	* `Float:ty`: Float:ty_INFO
>	* `Float:tz`: Float:tz_INFO
>	* `cost`: cost_INFO
>	* `name[]`: name[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Will teleport you the moment you step in.
 
***

#### CreateForbiddenArea
>* **Parameters:**
>	* `area`: area_INFO
>	* `kick`: kick_INFO
>	* `health`: health_INFO
>	* `invert`: invert_INFO
>	* `name[]`: name[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	If kick is 1 people will simply be constantly replaced outside the area
>	from the direction they came.
 
***

#### Property_OnPlayerEnterArea
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `area`: area_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Internal callback from YSI_areas.
 
***

#### Property_OnPlayerLeaveArea
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `areaid`: areaid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Internal callback from YSI_areas.
 
***

#### Property_OnPlayerConnect
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Internal callback.
 
***

#### Property_OnPlayerConnect
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Internal callback.
 
***

#### Property_OnPlayerSpawn
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Internal callback.
 
***

#### Property_OnPlayerLeaveCheckpointEx
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `cpid`: cpid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Internal callback from YSI_checkpoints.
 
***

#### Property_OnPlayerPickUpPickup
>* **Parameters:**
>	* `	playerid`: 	playerid_INFO
>	* `	pickupid`: 	pickupid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Internal callback from YSI_pickups.
 
***

#### Property_PickupTimeCheck
>* **Parameters:**
>	* `	playerid`: 	playerid_INFO
>	* `	pickupid`: 	pickupid_INFO
>* **Returns:**
>	* -
>* **Remarks:**

 
***

#### Property_OnPlayerEnterCheckpointEx
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `cpid`: cpid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Internal callback from YSI_checkpoints.
 
***

#### Property_GetWeapon
>* **Parameters:**
>	* `ammu`: ammu_INFO
>	* `slot`: slot_INFO
>	* `&page`: &page_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the slot active weapon from page start.  If you want the first one
>	use page = 0 and slot = 0.  If you want the second use page = 0 and slot
>	= 1 or slot = 0 and page > position of first.
 
***

#### Property_WeaponName
>* **Parameters:**
>	* `weapon`: weapon_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets a real weapon name based on the slot of the weapon, not the weapon id.
 
***

#### Property_WeaponCost
>* **Parameters:**
>	* `data`: data_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Extracts the cost from the passed data.
 
***

#### Property_WeaponAmmo
>* **Parameters:**

>* **Returns:**

>* **Remarks:**
>	Extracts the ammo from the passed data.
 
***

#### Property_OnPlayerExitedMenu
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Internal callback.
 
***

#### Property_GetWeaponFromSlot
>* **Parameters:**
>	* `slot`: slot_INFO
>* **Returns:**
>	* weaponid represented by that slot.
>* **Remarks:**
>	-
 
***

#### Property_SavePlayerWeapon
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `weaponslot`: weaponslot_INFO
>	* `ammo`: ammo_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Saves weapons based on slots so you only have 13 spawn weapons based on
>	real weapon slots (armour is slot 12).  This is similar to weapon slot
>	sorting but it's sorting slots which are packed from original weapon
>	numbers and missing some.
 
***

#### Property_GetSlotWeapon
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `slot`: slot_INFO
>	* `weaponslot`: weaponslot_INFO
>	* `ammo`: ammo_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets a player's stored for spawn weapons.
 
***

#### Property_SaveWeapons
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Saves a players current spawn weapon data to an ini (i.e. their save file).
>	110953013 is props in adler32
 
***

#### Property_LoadWeapons
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `identifier[]`: identifier[]_INFO
>	* `text[]`: text[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Called when a player logs in to load their previous weapons.
 
***

#### Property_SaveBank
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Saves a players current bank data to an ini (i.e. their save file).
 
***

#### Property_GetBank
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* Money in bank.
>* **Remarks:**
>
 
***

#### Property_LoadBank
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `identifier[]`: identifier[]_INFO
>	* `text[]`: text[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Called when a player logs in to load their previous banked money.
 
***

#### Property_OnPlayerSelectedMenuRow
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `row`: row_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Internal callback.
 
***

#### Property_GenerateAmmuMenu
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `ammu`: ammu_INFO
>	* `stage`: stage_INFO
>	* `page`: page_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	If slot is 0 the main selection will be displayed and page will represent
>	the offset from the start if there are more than 12 weapons for sale.  If
>	stage is 1 the individual confirmation menu for one weapon will show and
>	page will determine which weapon to show.
 
***

#### Property_Bank
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `amount`: amount_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Does banks and withdrawls.
 
***

#### Property_ResetRebuy
>* **Parameters:**
>	* `prop`: prop_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Makes a property available for purchase after a delay.
 
***

#### Property_Loop
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Does the main processing for the library.  Removes or kills people in areas
>	they shouldn't be and gives out money to people who earnt it.
 
***

#### Property_IsPlayerProperty
>* **Parameters:**
>	* `flags`: flags_INFO
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### Property_GetPlayerPropCount
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the number of properties this player could theoretically own.
 
***

#### Property_GetPropertyBits
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `Bit:properties[]`: Bit:properties[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Gets the properties currently owned by this player.
 
***

#### Property_GetLink
>* **Parameters:**
>	* `property`: property_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Returns a reference to the area or checkpoint used by this property or
>	NO_PROPERTY on fail.
 
***

