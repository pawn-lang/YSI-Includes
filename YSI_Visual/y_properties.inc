/**
 * <library name="y_properties">
 * <section>
 *  Description
 * </section>
 *  Handles properties and other common features for some modes.
 * <section>
 *  Version
 * </section>
 *  0.1
 * <section>
 *  Functions
 * </section>
 * <subsection>
 * Public
 * </subsection><ul>
 *  <symbol name="Property_Loop">Does the main system processing.</symbol>
 *  <symbol name="Property_AddPropRemote">Adds a property from another script.</symbol>
 *  <symbol name="Property_AddBankRemote">Adds a bank from another script.</symbol>
 *  <symbol name="Property_AddAmmuRemote">Adds an ammunation from another script.</symbol>
 *  <symbol name="Property_AddMARemote">Adds a money area from another script.</symbol>
 *  <symbol name="Property_AddMPRemote">Adds a money point from another script.</symbol>
 *  <symbol name="Property_AddTeleRemote">Adds a teleport from another script.</symbol>
 *  <symbol name="Property_AddFobRemote">Adds a forbidden area from another script.</symbol>
 *  <symbol name="Property_GetPropertyBitsReceive">Passes a player's properties.</symbol>
 *  <symbol name="Property_Remote">Remote wrapper for most minor functions.</symbol>
 *  <symbol name="YSIM_Properties">Master system callback.</symbol>
 *  <symbol name="Property_Broadcast">Called to save properties on master shutdown.</symbol>
 *  <symbol name="Property_PickupTimeCheck">Checks if a player is still stood on a pickup.</symbol>
 * </ul><subsection>
 * Core
 * </subsection><ul>
 *  <symbol name="Property_OnPlayerSelectedMenuRow">Called when someone selects something.</symbol>
 *  <symbol name="Property_OnPlayerExitedMenu">Called when someone exits a menu.</symbol>
 *  <symbol name="Property_OnPlayerEnterCheckpointEx">Called when someone enters a checkpoint (public).</symbol>
 *  <symbol name="Property_OnPlayerLeaveCheckpointEx">Called when someone leaves a checkpoint (public).</symbol>
 *  <symbol name="Property_OnPlayerPickUpPickup">Called when someone picks up a pickup (public).</symbol>
 *  <symbol name="Property_OnPlayerSpawn">Called when someone spawns.</symbol>
 *  <symbol name="Property_OnPlayerConnect">Called when comaone connects.</symbol>
 *  <symbol name="Property_OnPlayerLeaveArea">Called when someone leaves an area (public).</symbol>
 *  <symbol name="Property_OnPlayerEnterArea">Called when someone enters an area (public).</symbol>
 * </ul><subsection>
 * Stock
 * </subsection><ul>
 *  <symbol name="Property_GetPlayerPropCount">Gets the number of properties for a player.</symbol>
 *  <symbol name="Property_GetLink">Gets the area or checkpoint for a property.</symbol>
 *  <symbol name="Property_GetType">Gets a property's type.</symbol>
 *  <symbol name="Property_IsValid">Checks if a property is valid.</symbol>
 *  <symbol name="Property_Bank">Moves money to/from an account.</symbol>
 *  <symbol name="Property_SavePlayerWeapon">Saves a players weapon for spawn.</symbol>
 *  <symbol name="Property_SaveWeapons">Saves a player's spawn weapons.</symbol>
 *  <symbol name="Property_LoadWeapons">Loads a player's spawn weapons.</symbol>
 *  <symbol name="Property_SaveBank">Saves a player's banked money.</symbol>
 *  <symbol name="Property_LoadBank">Loads a player's banked money.</symbol>
 *  <symbol name="Property_GetBank">Gets a player's banked money.</symbol>
 *  <symbol name="Property_GetSlotWeapon">Gets a player's spawn weapons.</symbol>
 *  <symbol name="Property_GetPropertyBits">Gets a player's owned properties.</symbol>
 *  <symbol name="Property_SetRebuyDelay">Set a delay on rebuying properties.</symbol>
 * </ul><subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="Property_GetWeapon">Gets weapon data for a slotid slot.</symbol>
 *  <symbol name="Property_WeaponName">Gets a weapon name for a slotid.</symbol>
 *  <symbol name="Property_GetWeaponFromSlot">Gets a weaponid from a slotid.</symbol>
 *  <symbol name="Property_GenerateAmmuMenu">Generates the menu for ammunation.</symbol>
 * </ul><subsection>
 * Inline
 * </subsection><ul>
 *  <symbol name="Property_SetOption">Sets a property's custom flag.</symbol>
 *  <symbol name="Property_IsActive">Checks if a property is active.</symbol>
 *  <symbol name="Property_GetOption">Gets a property's custom flag.</symbol>
 *  <symbol name="Property_GivePlayerWeapon">Gives a player a weapon from it's slot.</symbol>
 *  <symbol name="Property_WeaponCost">Gets the cost of a slot,</symbol>
 *  <symbol name="Property_WeaponAmmo">Gets the ammo of a slot.</symbol>
 *  <symbol name="Property_IsPlayerProperty">Checks if a player can have a property.</symbol>
 * </ul><subsection>
 * API
 * </subsection><ul>
 *  <symbol name="CreateProperty">Creates a business.</symbol>
 *  <symbol name="CreateBank">Creates a bank.</symbol>
 *  <symbol name="CreateAmmunation">Creates an ammunation.</symbol>
 *  <symbol name="CreateMoneyArea">Creates a money area.</symbol>
 *  <symbol name="CreateMoneyPoint">Creates a money point.</symbol>
 *  <symbol name="CreateTeleport">Creates a teleport.</symbol>
 *  <symbol name="CreateForbiddenArea">Creates a forbidden area.</symbol>
 *  <symbol name="DestroyProperty">Deletes a property from the array.</symbol>
 * </ul><section>
 *  Definitions
 * </section><ul>
 *  <symbol name="PROPERTY_LOOP_GRANULARITY">Number of itterations of the main loop a second.</symbol>
 *  <symbol name="MAX_PROP_NAME">Max length of the name of a property.</symbol>
 *  <symbol name="MAX_PROPERTIES">Max number of properties.</symbol>
 *  <symbol name="NO_PROPERTY">Invalid return.</symbol>
 *  <symbol name="WEAPON_ARMOUR">Type for salling armour at ammunation.</symbol>
 *  <symbol name="PROPERTY_SELL_PERCENT">% of money got back for a reduced sale.</symbol>
 * </ul><section>
 *  Enums
 * </section><ul>
 *  e_PROP_FLAGS - Flags for property data.
 *  E_PROP_DATA - Data for a property.
 *  E_PROP_AMMU - Data for a persons current ammunation menu.
 *  <unnamed> - Tagless remote instructions, must have new ones added to the end.
 * </ul><section>
 *  Macros
 * </section><ul>
 *  <symbol name="WEAPON_DATA_OFFSET">Offset for saving weapons with variable size arrays,</symbol>
 *  <symbol name="WEAPON_DATA">Gets ammo and cost from parameters and compresses them.</symbol>
 *  <symbol name="WEAPON_DATA_REM">Like WEAPON_DATA but reads from an array instead.</symbol>
 *  <symbol name="WEAPON">Saves a weapon id in the top byte of a cell.</symbol>
 * </ul><section>
 *  Tags
 * </section><ul>
 *  <symbol name="e_PROP_FLAGS">Flags.</symbol>
 * </ul><section>
 *  Variables
 * </section>
 * <subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="YSI_g_sProperties">Array of all property data.</symbol>
 *  <symbol name="YSI_g_sMoney">Array of player's banked money.</symbol>
 *  <symbol name="YSI_g_sPlayerProperties">Bit array of properties a player has.</symbol>
 *  <symbol name="YSI_g_sSpawnWeapons">Array of weapons a player will spawn with.</symbol>
 *  <symbol name="YSI_g_sShopMenu">Array of players current menus.</symbol>
 *  <symbol name="YSI_g_sAreaPointers">Array of properties for each area.</symbol>
 *  <symbol name="YSI_g_sCheckpointPointers">Array of properties for each checkpoint.</symbol>
 *  <symbol name="YSI_g_sTempPropReq">Script has requested a player's properties.</symbol>
 *  <symbol name="YSI_g_sTempProp">Temporary store for properties.</symbol>
 *  <symbol name="YSI_g_sIsMaster">Is this script the global master.</symbol>
 * </ul><section>
 *  Commands
 * </section><ul>
 *  <symbol name="buy">Lets you buy your current property.</symbol>
 *  <symbol name="bank">Lets you bank money.</symbol>
 *  <symbol name="properties">Lists properties and their owners.</symbol>
 *  <symbol name="balance">Displays your current balance.</symbol>
 *  <symbol name="withdraw">Allows you to take out money.</symbol>
 *  <symbol name="sell">Allows you to sell a property.</symbol>
 * </ul><section>
 *  Properties
 * </section><ul>
 *  <symbol name="LReqProp">Return data from a remote script.</symbol>
 *  <symbol name="110953013">Return properties for a player.</symbol>
 * </ul>
 * </library>
 *//** *//*
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

#if !defined _INC_y_properties
	#tryinclude "y_properties\y_properties_entry"
#endif
#if !defined _INC_y_properties
	#tryinclude "YSI_Visual\y_properties\y_properties_entry"
#endif
#if !defined _INC_y_properties
	#tryinclude "YSI\YSI_Visual\y_properties\y_properties_entry"
#endif
#if !defined _INC_y_properties
	#tryinclude <YSI_Visual\y_properties\y_properties_entry>
#endif
#if !defined _INC_y_properties
	#tryinclude <YSI\YSI_Visual\y_properties\y_properties_entry>
#endif
#if !defined _INC_y_properties
	#error Could not find y_properties
#endif

