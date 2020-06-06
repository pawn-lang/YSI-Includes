#if defined _INC_y_properties
	#endinput
#endif
#define _INC_y_properties

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

#include "..\..\YSI_Core\y_utils"

#if defined MAX_PROP_NAME
	#if MAX_PROP_NAME < (39 - PLAYER_BIT_ARRAY)
		#undef MAX_PROP_NAME
	#endif
#endif

#if !defined MAX_PROP_NAME
	#define MAX_PROP_NAME (39 - PLAYER_BIT_ARRAY)
#endif

#if !defined MAX_PROPERTIES
	#define MAX_PROPERTIES 256
#endif

#if !defined MAX_CHECKPOINTS
	#define MAX_CHECKPOINTS MAX_PROPERTIES
#endif

#if !defined GROUP_PROPERTY_BITS
	#if MAX_PROPERTIES <= 32
		#define GROUP_PROPERTY_BITS 2
	#else
		#define GROUP_PROPERTY_BITS Bit_Bits(MAX_PROPERTIES)
	#endif
#endif

#if !defined PLAYER_BIT_ARRAY
	#define PLAYER_BIT_ARRAY Bit_Bits(MAX_PLAYERS)
#endif

#define NO_PROPERTY -1
#define NO_CHECKPOINT -1

#if !defined WEAPON_ARMOUR
	#define WEAPON_ARMOUR 100
#endif

#define PROPERTY_SELL_PERCENT 60

#define PROPERTY_INCREASE_PERCENT 125

#define WEAPON_DATA_OFFSET (PLAYER_BIT_ARRAY - 2)

#define WEAPON_DATA (((getarg(pos++) & 0xFFF) << 20) | (getarg(pos++) & 0xFFFFF))

#define WEAPON_DATA_REM (((dat[pos++] & 0xFFF) << 20) | (dat[pos++] & 0xFFFFF))

#define WEAPON(%1) ((%1) << 24)

#define Property_OnPlayerLeaveCheckpointEx Property_OnPlayerLeaveCP
#define Property_OnPlayerEnterCheckpointEx Property_OnPlayerEnterCP

enum e_PROP_FLAGS:(+= 0x10000)
{
	e_PROP_FLAGS_LINK		= 0x0000FFFF,
	e_PROP_FLAGS_TYPES		= 0x00FF0000,
	e_PROP_FLAGS_TYPE_PROP	= 0x00010000,
	e_PROP_FLAGS_TYPE_BANK,
	e_PROP_FLAGS_TYPE_AMMU,
	e_PROP_FLAGS_TYPE_TELS,
	e_PROP_FLAGS_TYPE_TELT,
	e_PROP_FLAGS_TYPE_MONP,
	e_PROP_FLAGS_TYPE_HOUS,
	e_PROP_FLAGS_TYPE_MONA	= 0x00100000,
	e_PROP_FLAGS_TYPE_RSRC,
	e_PROP_FLAGS_FLAGS		= 0xFF000000,
	e_PROP_FLAGS_CUST_1		= 0x01000000,
	e_PROP_FLAGS_CUST_2		= 0x02000000,
	e_PROP_FLAGS_CUST_3		= 0x04000000,
	e_PROP_FLAGS_CUST_4		= 0x08000000,
	e_PROP_FLAGS_CUST_5		= 0x10000000,
	e_PROP_FLAGS_ACTIVE		= 0x80000000
}

enum E_PROP_DATA
{
	E_PROP_DATA_NAME[MAX_PROP_NAME],
	e_PROP_FLAGS:E_PROP_DATA_FLAGS,
	E_PROP_DATA_DATA_1,
	E_PROP_DATA_DATA_2,
	Bit:E_PROP_DATA_PLAYERS[PLAYER_BIT_ARRAY]
}

enum E_PROP_AMMU
{
	Menu:E_PROP_AMMU_MENU,
	E_PROP_AMMU_DATA
}

static
	YSI_g_sProperties[MAX_PROPERTIES][E_PROP_DATA],
	YSI_g_sMoney[MAX_PLAYERS],
	YSI_g_sPropCount[MAX_PLAYERS],
	YSI_g_sHouseCount[MAX_PLAYERS],
	BitArray:YSI_g_sPlayerProperties[MAX_PLAYERS]<MAX_PROPERTIES>,
	YSI_g_sSpawnWeapons[MAX_PLAYERS][13],
	YSI_g_sShopMenu[MAX_PLAYERS][E_PROP_AMMU],
	YSI_g_sRebuyDelay = 0,
	#if defined _YSI_VISUAL_PICKUPS
		YSI_g_sPickupPointers[MAX_DYN_PICKUPS],
		YSI_g_sPickupProps = 0,
		YSI_g_sPickupTimer[MAX_PLAYERS] = {-1, ...},
		YSI_g_sPlayerPickup[MAX_PLAYERS] = {NO_PICKUP, ...},
	#endif
	YSI_g_sAreaPointers[MAX_AREAS],
	YSI_g_sCheckpointPointers[MAX_CHECKPOINTS],
	YSI_g_sMaxPlayerHouses = cellmax,
	YSI_g_sMaxPlayerProps = cellmax,
	YSI_g_sCurrentHouse[MAX_PLAYERS] = {-1, ...};

loadtext core[ysi_properties];

/*-------------------------------------------------------------------------*//**
 * <param name="prop">Property to check.</param>
 *//*------------------------------------------------------------------------**/

P:D(bool:Property_IsActive(prop));
#define Property_IsActive(%1) \
	((%1) < MAX_PROPERTIES && (%1) >= 0 && YSI_g_sProperties[(%1)][E_PROP_DATA_FLAGS] & e_PROP_FLAGS_ACTIVE)

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Allows people to own as many properties as they like at once.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Property_ResetMaxProperties());
#define Property_ResetMaxProperties() \
	Property_SetMaxProperties(cellmax)

/*-------------------------------------------------------------------------*//**
 * <param name="slot">Custom flag to set.</param>
 * <param name="value">Value to set it to.</param>
 * <remarks>
 *  Can't be changed except from 0 to 1.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Property_SetOption(slot,value));
#define Property_SetOption(%1,%2) \
	((%2) ? e_PROP_FLAGS_CUST_%1 : e_PROP_FLAGS:0)

/*-------------------------------------------------------------------------*//**
 * <param name="slot">Custom flag to get.</param>
 * <param name="flags">flags cell to get it from.</param>
 *//*------------------------------------------------------------------------**/

P:D(Property_GetOption(slot,e_PROP_FLAGS:flags));
#define Property_GetOption(%1,%2) \
	(e_PROP_FLAGS_CUST_%1 & e_PROP_FLAGS:(%2))

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to gice a weapon to.</param>
 * <param name="slot">Weapon slot to give.</param>
 * <param name="ammo">Ammo to give.</param>
 * <remarks>
 *  Gives a player a weapon by slot instead of weaponid or assignes armour.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Property_GivePlayerWeapon(playerid,slot,ammo));
#define Property_GivePlayerWeapon(%1,%2,%3) \
	if ((%2) == 39) SetPlayerArmour((%1), 100.0); else GivePlayerWeapon(%1, Property_GetWeaponFromSlot(%2), %3)

/*-------------------------------------------------------------------------*//**
 * <param name="delay">Time till a property can be bought again.</param>
 *//*------------------------------------------------------------------------**/

stock Property_SetRebuyDelay(delay)
{
	YSI_g_sRebuyDelay = delay;
}

/*-------------------------------------------------------------------------*//**
 * <param name="property">Property to check.</param>
 * <returns>
 *  Is the property a valid active property.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Property_IsValid(property)
{
	return Property_IsActive(property);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to check.</param>
 * <param name="prop">Property to check.</param>
 * <param name="flags">Property flags for ownership type.</param>
 *//*------------------------------------------------------------------------**/

P:D(bool:Property_IsOwner(playerid,prop,e_PROP_FLAGS:flags));
#define Property_IsOwner(%1,%2,%3) \
	((Property_GetOption(2, (%3))) ? (!Bit_GetBit(YSI_g_sProperties[(%2)][E_PROP_DATA_PLAYERS], (%1))) : (!(_:YSI_g_sProperties[(%2)][E_PROP_DATA_PLAYERS][0] == (%1))))

/*-------------------------------------------------------------------------*//**
 * <param name="count">Number of ownable properties.</param>
 * <remarks>
 *  Sets the number of properties a player can own at once.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Property_SetMaxProperties(count)
{
	YSI_g_sMaxPlayerProps = count;
}

/*-------------------------------------------------------------------------*//**
 * <param name="count">Number of ownable houses.</param>
 * <remarks>
 *  Sets the number of houses a player can own at once.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Property_SetMaxHouses(count)
{
	YSI_g_sMaxPlayerHouses = count;
}

/*-------------------------------------------------------------------------*//**
 * <param name="property">Property to get the type of.</param>
 * <returns>
 *  0 if invalid or type.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Property_GetType(property)
{
	if (!Property_IsActive(property)) return 0;
	return _:(YSI_g_sProperties[property][E_PROP_DATA_FLAGS] & e_PROP_FLAGS_TYPES);
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Sets variable initial states.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HOOK__ OnScriptInit()
{
	P:2("Property_Property() start");
	P:5("Property_Property() 0");
	//Timer_Add("Property_Loop", PROPERTY_LOOP_GRANULARITY);
	P:5("Property_Property() 1");
	#if defined _YSI_CORE_COMMANDS
		ycmd("buy");
		ycmd("bank");
		ycmd("properties");
		ycmd("balance");
		ycmd("withdraw");
		ycmd("sell");
		ycmd("enter");
		ycmd("exit");
	#endif
	P:5("Property_Property() 2");
	for (new i = 0; i < MAX_AREAS; i++) YSI_g_sAreaPointers[i] = NO_PROPERTY;
	P:5("Property_Property() 3");
	for (new i = 0; i < MAX_CHECKPOINTS; i++) YSI_g_sCheckpointPointers[i] = NO_PROPERTY;
	#if defined _YSI_VISUAL_PICKUPS
		P:4("Property_Property() 4 " #MAX_DYN_PICKUPS);
		for (new i = 0; i < MAX_DYN_PICKUPS; i++) YSI_g_sPickupPointers[i] = NO_PROPERTY;
	#endif
	P:2("Property_Property() end");
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="property">Property to destroy.</param>
 *//*------------------------------------------------------------------------**/

stock DestroyProperty(property)
{
	if (!Property_IsActive(property)) return 0;
	new
		e_PROP_FLAGS:flags = YSI_g_sProperties[property][E_PROP_DATA_FLAGS];
	YSI_g_sProperties[property][E_PROP_DATA_FLAGS] = e_PROP_FLAGS:0;
	if (flags & e_PROP_FLAGS_TYPES >= e_PROP_FLAGS_TYPE_MONA)
	{
		YSI_g_sAreaPointers[_:(flags & e_PROP_FLAGS_LINK)] = NO_PROPERTY;
		Area_Delete(_:(flags & e_PROP_FLAGS_LINK));
	}
	else
	{
		#if defined _YSI_VISUAL_PICKUPS
			if ((flags & e_PROP_FLAGS_TYPES > e_PROP_FLAGS_TYPE_PROP) && Property_GetOption(5, flags))
			{
				Pickup_Remove(_:(flags & e_PROP_FLAGS_LINK));
				YSI_g_sPickupPointers[_:(flags & e_PROP_FLAGS_LINK)] = NO_PROPERTY;
			}
			else
		#endif
		{
			YSI_g_sCheckpointPointers[_:(flags & e_PROP_FLAGS_LINK)] = NO_PROPERTY;
			DestroyCheckpoint(_:(flags & e_PROP_FLAGS_LINK));
		}
	}
	for (new i = 0; i < MAX_PLAYERS; i++) Bit_Set(YSI_g_sPlayerProperties[i], property, 0, GROUP_PROPERTY_BITS);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="extX">X position of the external marker.</param>
 * <param name="extY">Y position of the external marker.</param>
 * <param name="extZ">Z position of the external marker.</param>
 * <param name="intX">X position of the internal marker.</param>
 * <param name="intY">Y position of the internal marker.</param>
 * <param name="intZ">Z position of the internal marker.</param>
 * <param name="interior">Interior ID of the house.</param>
 * <param name="world">Virtual world of the house.</param>
 * <param name="price">Price of the house.</param>
 * <param name="checkpoint">Use a checkpoint instead of a pickup.</param>
 * <remarks>
 *  Creates a buyable property (business).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock CreateHouse(Float:extX, Float:extY, Float:extZ, Float:intX, Float:intY, Float:intZ, interior, world, price, checkpoint = 0)
{
	P:2("CreateHouse() start 1");
	P:2("CreateHouse() start 2");
	new
		i = 0;
	while (i < MAX_PROPERTIES && Property_IsActive(i))
	{
		i++;
	}
	if (i == MAX_PROPERTIES) return NO_PROPERTY;
	new
		cp = 0;
	P:4("CreateHouse() Make");
	#if defined _YSI_VISUAL_PICKUPS
		if (!checkpoint)
		{
			if ((cp = Pickup_Add(1273, extX, extY, extZ, 0, -1)) == NO_PICKUP) return NO_PROPERTY;
			YSI_g_sPickupProps++;
		}
		else
	#else
		checkpoint = 1;
	#endif
	#pragma tabsize 4
			if ((cp = CreateCheckpoint(extX, extY, extZ, 3.0)) == NO_CHECKPOINT) return NO_PROPERTY;
	#pragma tabsize 4
	P:4("CreateHouse() Made");
	YSI_g_sProperties[i][E_PROP_DATA_FLAGS] = e_PROP_FLAGS_TYPE_HOUS | e_PROP_FLAGS_ACTIVE | e_PROP_FLAGS:cp | Property_SetOption(1, checkpoint);
	YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][0] = Bit:INVALID_PLAYER_ID;
	YSI_g_sProperties[i][E_PROP_DATA_DATA_1] = interior;
	YSI_g_sProperties[i][E_PROP_DATA_DATA_2] = world;
	
	P:4("CreateHouse() Save pos");
	YSI_g_sProperties[i][E_PROP_DATA_NAME][0] = _:extX;
	YSI_g_sProperties[i][E_PROP_DATA_NAME][1] = _:extY;
	YSI_g_sProperties[i][E_PROP_DATA_NAME][2] = _:extZ;
	YSI_g_sProperties[i][E_PROP_DATA_NAME][3] = _:intX;
	YSI_g_sProperties[i][E_PROP_DATA_NAME][4] = _:intY;
	YSI_g_sProperties[i][E_PROP_DATA_NAME][5] = _:intZ;
	YSI_g_sProperties[i][E_PROP_DATA_NAME][6] = price;

	P:4("CreateHouse() Save ID");
	#if defined _YSI_VISUAL_PICKUPS
		if (!checkpoint)
		{
			YSI_g_sPickupPointers[cp] = i;
		}
		else
	#endif
	#pragma tabsize 4
			YSI_g_sCheckpointPointers[cp] = i;
	#pragma tabsize 4
	return i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="name">Name of the property.</param>
 * <param name="x">X position.</param>
 * <param name="y">Y position.</param>
 * <param name="z">Z position.</param>
 * <param name="price">Cost of the property.</param>
 * <param name="reward">Money earnt from the property periodically.</param>
 * <param name="interval">How often you earn money.</param>
 * <param name="sell">Wether you need to seel the property of people can just buy you out.</param>
 * <param name="multi">Wether more than one person can own this property at once.</param>
 * <param name="reduce">Wether selling this property gets you less then you paid for it.</param>
 * <param name="increase">Wether buying this property will put the price up for the future.</param>
 * <param name="property">Wether this property uses a pickup instead of a checkpoint.</param>
 * <remarks>
 *  Creates a buyable property (business).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock CreateProperty(name[], Float:x, Float:y, Float:z, price, reward, interval = 60000, sell = 0, multi = 0, reduce = 0, increase = 0, pickup = 0)
{
	new
		i = 0;
	while (i < MAX_PROPERTIES && Property_IsActive(i))
	{
		i++;
	}
	if (i == MAX_PROPERTIES) return NO_PROPERTY;
	new
		cp = 0;
	#if defined _YSI_VISUAL_PICKUPS
		if (pickup)
		{
			if ((cp = Pickup_Add(1273, x, y, z, 0, -1)) == NO_PICKUP) return NO_PROPERTY;
			YSI_g_sPickupProps++;
		}
		else
	#endif
	#pragma tabsize 4
			if ((cp = CreateCheckpoint(x, y, z, 3.0)) == NO_CHECKPOINT) return NO_PROPERTY;
	#pragma tabsize 4
	YSI_g_sProperties[i][E_PROP_DATA_FLAGS] = e_PROP_FLAGS_TYPE_PROP | e_PROP_FLAGS_ACTIVE | e_PROP_FLAGS:cp | Property_SetOption(1, sell) | Property_SetOption(2, multi) | Property_SetOption(3, reduce) | Property_SetOption(4, increase) | Property_SetOption(5, pickup);
	if (multi) Bit_SetAll(YSI_g_sProperties[i][E_PROP_DATA_PLAYERS], 0, PLAYER_BIT_ARRAY);
	else YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][0] = Bit:INVALID_PLAYER_ID;
	YSI_g_sProperties[i][E_PROP_DATA_NAME][MAX_PROP_NAME - 1] = interval & 0xFFFFF;
	YSI_g_sProperties[i][E_PROP_DATA_DATA_1] = (interval & 0xFFFFF) | ((price & 0x00000FFF) << 20);
	YSI_g_sProperties[i][E_PROP_DATA_DATA_2] = (reward & 0x3FFFF) | ((price & 0x03FFF000) << 6);
	if (!isnull(name)) strcpy(YSI_g_sProperties[i][E_PROP_DATA_NAME], name, MAX_PROP_NAME - 1);
	else YSI_g_sProperties[i][E_PROP_DATA_NAME][0] = '\0';
	#if defined _YSI_VISUAL_PICKUPS
		if (pickup)
		{
			YSI_g_sPickupPointers[cp] = i;
		}
		else
	#endif
	#pragma tabsize 4
			YSI_g_sCheckpointPointers[cp] = i;
	#pragma tabsize 4
	return i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="x">X position.</param>
 * <param name="y">Y position.</param>
 * <param name="z">Z position.</param>
 * <param name="name">Name of the bank.</param>
 *//*------------------------------------------------------------------------**/

stock CreateBank(Float:x, Float:y, Float:z, name[] = "")
{
	new
		i = 0;
	while (i < MAX_PROPERTIES)
	{
		if (!Property_IsActive(i)) break;
		i++;
	}
	if (i == MAX_PROPERTIES) return NO_PROPERTY;
	new
		cp = CreateCheckpoint(x, y, z, 3.0);
	if (cp == NO_CHECKPOINT) return NO_PROPERTY;
	YSI_g_sProperties[i][E_PROP_DATA_FLAGS] = e_PROP_FLAGS_TYPE_BANK | e_PROP_FLAGS_ACTIVE | e_PROP_FLAGS:cp;
	if (!isnull(name)) strcpy(YSI_g_sProperties[i][E_PROP_DATA_NAME], name, MAX_PROP_NAME);
	else YSI_g_sProperties[i][E_PROP_DATA_NAME][0] = '\0';
	YSI_g_sCheckpointPointers[cp] = i;
	return i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="x">X position.</param>
 * <param name="y">Y position.</param>
 * <param name="z">Z position.</param>
 * <param name="spawn">Wether you spawn with the weapon.</param>
 * <param name="instant">Wether you get the weapon as soon as you buy it.</param>
 * <param name=""></param>
 * <remarks>
 *  spawn and instant can BOTH be 1.  The format of the additional parameters
 *  is:
 *
 *  weapon, ammo, price
 *
 *  They MUST come in sets of three of the function will fail.  Weapon is in
 *  the form of the WEAPON_ defines in a_samp or WEAPON_ARMOUR.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock CreateAmmunation(Float:x, Float:y, Float:z, spawn, instant, ...)
{
	new
		num = numargs();
	if (((num) <= 5) || (((num - 5) / 3) * 3 != (num - 5))) return NO_PROPERTY;
	new
		i = 0;
	while (i < MAX_PROPERTIES)
	{
		if (!Property_IsActive(i)) break;
		i++;
	}
	if (i == MAX_PROPERTIES) return NO_PROPERTY;
	new
		cp = CreateCheckpoint(x, y, z, 3.0);
	if (cp == NO_CHECKPOINT) return NO_PROPERTY;
	YSI_g_sProperties[i][E_PROP_DATA_FLAGS] = e_PROP_FLAGS_TYPE_AMMU | e_PROP_FLAGS_ACTIVE | e_PROP_FLAGS:cp | Property_SetOption(1, spawn) | Property_SetOption(2, instant);
	new
		pos = 5,
		count = 0;
	while (pos < num)
	{
		switch (getarg(pos++))
		{
			case WEAPON_BRASSKNUCKLE:
				YSI_g_sProperties[i][E_PROP_DATA_DATA_1] = WEAPON_DATA;
			case WEAPON_GOLFCLUB:
				YSI_g_sProperties[i][E_PROP_DATA_DATA_2] = WEAPON_DATA;
			case WEAPON_NITESTICK:
				YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][0] = Bit:WEAPON_DATA;
			case WEAPON_KNIFE:
				YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][1] = Bit:WEAPON_DATA;
			case WEAPON_BAT:
				#if PLAYER_BIT_ARRAY > 2
					YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][2] = Bit:WEAPON_DATA;
				#else
					YSI_g_sProperties[i][E_PROP_DATA_NAME][0 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
				#endif
			case WEAPON_SHOVEL:
				#if PLAYER_BIT_ARRAY > 3
					YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][3] = Bit:WEAPON_DATA;
				#else
					YSI_g_sProperties[i][E_PROP_DATA_NAME][1 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
				#endif
			case WEAPON_POOLSTICK:
				#if PLAYER_BIT_ARRAY > 4
					YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][4] = Bit:WEAPON_DATA;
				#else
					YSI_g_sProperties[i][E_PROP_DATA_NAME][2 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
				#endif
			case WEAPON_KATANA:
				#if PLAYER_BIT_ARRAY > 5
					YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][5] = Bit:WEAPON_DATA;
				#else
					YSI_g_sProperties[i][E_PROP_DATA_NAME][3 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
				#endif
			case WEAPON_CHAINSAW:
				#if PLAYER_BIT_ARRAY > 6
					YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][6] = Bit:WEAPON_DATA;
				#else
					YSI_g_sProperties[i][E_PROP_DATA_NAME][4 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
				#endif
			case WEAPON_DILDO:
				#if PLAYER_BIT_ARRAY > 7
					YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][7] = Bit:WEAPON_DATA;
				#else
					YSI_g_sProperties[i][E_PROP_DATA_NAME][5 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
				#endif
			case WEAPON_DILDO2:
				#if PLAYER_BIT_ARRAY > 8
					YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][8] = Bit:WEAPON_DATA;
				#else
					YSI_g_sProperties[i][E_PROP_DATA_NAME][6 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
				#endif
			case WEAPON_VIBRATOR:
				#if PLAYER_BIT_ARRAY > 9
					YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][9] = Bit:WEAPON_DATA;
				#else
					YSI_g_sProperties[i][E_PROP_DATA_NAME][7 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
				#endif
			case WEAPON_VIBRATOR2:
				#if PLAYER_BIT_ARRAY > 10
					YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][10] = Bit:WEAPON_DATA;
				#else
					YSI_g_sProperties[i][E_PROP_DATA_NAME][8 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
				#endif
			case WEAPON_FLOWER:
				#if PLAYER_BIT_ARRAY > 11
					YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][11] = Bit:WEAPON_DATA;
				#else
					YSI_g_sProperties[i][E_PROP_DATA_NAME][9 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
				#endif
			case WEAPON_CANE:
				#if PLAYER_BIT_ARRAY > 12
					YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][12] = Bit:WEAPON_DATA;
				#else
					YSI_g_sProperties[i][E_PROP_DATA_NAME][10 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
				#endif
			case WEAPON_GRENADE:
				#if PLAYER_BIT_ARRAY > 13
					YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][13] = Bit:WEAPON_DATA;
				#else
					YSI_g_sProperties[i][E_PROP_DATA_NAME][11 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
				#endif
			case WEAPON_TEARGAS:
				#if PLAYER_BIT_ARRAY > 14
					YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][14] = Bit:WEAPON_DATA;
				#else
					YSI_g_sProperties[i][E_PROP_DATA_NAME][12 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
				#endif
			case WEAPON_MOLTOV:
				#if PLAYER_BIT_ARRAY > 15
					YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][15] = Bit:WEAPON_DATA;
				#else
					YSI_g_sProperties[i][E_PROP_DATA_NAME][13 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
				#endif
			case WEAPON_COLT45:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][14 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_SILENCED:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][15 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_DEAGLE:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][16 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_SHOTGUN:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][17 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_SAWEDOFF:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][18 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_SHOTGSPA:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][19 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_UZI:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][20 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_MP5:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][21 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_AK47:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][22 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_M4:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][23 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_TEC9:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][24 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_RIFLE:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][25 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_SNIPER:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][26 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_ROCKETLAUNCHER:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][27 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_FLAMETHROWER:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][28 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_MINIGUN:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][29 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_SATCHEL:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][30 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_SPRAYCAN:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][31 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_FIREEXTINGUISHER:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][32 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_CAMERA:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][33 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_PARACHUTE:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][34 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			case WEAPON_ARMOUR:
				YSI_g_sProperties[i][E_PROP_DATA_NAME][35 - WEAPON_DATA_OFFSET] = WEAPON_DATA;
			default:
			{
				pos += 2;
				count--;
			}
		}
		count++;
	}
	YSI_g_sProperties[i][E_PROP_DATA_NAME][MAX_PROP_NAME - 1] = count;
	YSI_g_sCheckpointPointers[cp] = i;
	return i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="area">Reference to a defined area.</param>
 * <param name="money">How much you earn.</param>
 * <param name="interval">How often you earn.</param>
 * <remarks>
 *  This function has internal checking for invalid areas so you can just pass
 *  the return from an Area_ funtion directly.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock CreateMoneyArea(area, money = 100, interval = 10000)
{
	if (area == NO_AREA) return NO_PROPERTY;
	new
		i = 0;
	while (i < MAX_PROPERTIES)
	{
		if (!Property_IsActive(i)) break;
		i++;
	}
	if (i == MAX_PROPERTIES) return NO_PROPERTY;
	YSI_g_sProperties[i][E_PROP_DATA_FLAGS] = e_PROP_FLAGS_TYPE_MONA | e_PROP_FLAGS_ACTIVE | e_PROP_FLAGS:area;
	YSI_g_sProperties[i][E_PROP_DATA_DATA_1] = money;
	YSI_g_sProperties[i][E_PROP_DATA_DATA_2] = interval;
	YSI_g_sProperties[i][E_PROP_DATA_NAME][0] = interval;
	YSI_g_sAreaPointers[area] = i;
	return i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="x">X position.</param>
 * <param name="y">Y position.</param>
 * <param name="z">Z position.</param>
 * <param name="s">Size of checkpoint.</param>
 * <param name="money">How much you earn.</param>
 * <param name="interval">How often you earn.</param>
 * <remarks>
 *  Like CreateMoneyArea but you must be in a checkpoint.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock CreateMoneyPoint(Float:x, Float:y, Float:z, Float:s, money = 100, interval = 10000)
{
	new
		i = 0;
	while (i < MAX_PROPERTIES)
	{
		if (!Property_IsActive(i)) break;
		i++;
	}
	if (i == MAX_PROPERTIES) return NO_PROPERTY;
	new
		cp = CreateCheckpoint(x, y, z, s);
	if (cp == NO_CHECKPOINT) return NO_PROPERTY;
	YSI_g_sProperties[i][E_PROP_DATA_FLAGS] = e_PROP_FLAGS_TYPE_MONP | e_PROP_FLAGS_ACTIVE | e_PROP_FLAGS:cp;
	YSI_g_sProperties[i][E_PROP_DATA_DATA_1] = money;
	YSI_g_sProperties[i][E_PROP_DATA_DATA_2] = interval;
	YSI_g_sProperties[i][E_PROP_DATA_NAME][0] = interval;
	YSI_g_sCheckpointPointers[cp] = i;
	return i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="sx">Start X.</param>
 * <param name="sy">Start Y.</param>
 * <param name="sz">Start Z.</param>
 * <param name="tz">Target X.</param>
 * <param name="ty">Target Y.</param>
 * <param name="tz">Target Z.</param>
 * <param name="cost">Price to use the teleport.</param>
 * <param name="name">Name of the destination.</param>
 * <remarks>
 *  Will teleport you the moment you step in.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock CreateTeleport(Float:sx, Float:sy, Float:sz, Float:tx, Float:ty, Float:tz, cost = 0, name[] = "")
{
	new
		i = 0;
	while (i < MAX_PROPERTIES)
	{
		if (!Property_IsActive(i)) break;
		i++;
	}
	if (i == MAX_PROPERTIES) return NO_PROPERTY;
	new
		cp = CreateCheckpoint(sx, sy, sz, 3.0);
	if (cp == NO_CHECKPOINT) return NO_PROPERTY;
	YSI_g_sProperties[i][E_PROP_DATA_FLAGS] = e_PROP_FLAGS_TYPE_TELS | e_PROP_FLAGS_ACTIVE | e_PROP_FLAGS:cp;
	YSI_g_sProperties[i][E_PROP_DATA_DATA_1] = cost;
	YSI_g_sProperties[i][E_PROP_DATA_DATA_2] = _:tx;
	YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][0] = Bit:ty;
	YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][1] = Bit:tz;
	if (!isnull(name)) strcpy(YSI_g_sProperties[i][E_PROP_DATA_NAME], name, MAX_PROP_NAME);
	else YSI_g_sProperties[i][E_PROP_DATA_NAME][0] = '\0';
	YSI_g_sCheckpointPointers[cp] = i;
	return i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="area">Reference to a defined area.</param>
 * <param name="kick">Wether they should be kicked out not hurt.</param>
 * <param name="health">How much health should be removed every itteration they're in.</param>
 * <param name="invert">Not allowed to leave the area rather than enter.</param>
 * <param name="name">Name of the area.</param>
 * <remarks>
 *  If kick is 1 people will simply be constantly replaced outside the area
 *  from the direction they came.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock CreateForbiddenArea(area, kick = 0, health = 1000, invert = 0, name[] = "")
{
	if (area == NO_AREA) return NO_PROPERTY;
	new
		i = 0;
	while (i < MAX_PROPERTIES)
	{
		if (!Property_IsActive(i)) break;
		i++;
	}
	if (i == MAX_PROPERTIES) return NO_PROPERTY;
	YSI_g_sProperties[i][E_PROP_DATA_FLAGS] = e_PROP_FLAGS_TYPE_RSRC | e_PROP_FLAGS_ACTIVE | e_PROP_FLAGS:area | Property_SetOption(1, kick) | Property_SetOption(2, invert);
	YSI_g_sProperties[i][E_PROP_DATA_DATA_2] = health;
	if (!isnull(name)) strcpy(YSI_g_sProperties[i][E_PROP_DATA_NAME], name, MAX_PROP_NAME);
	else YSI_g_sProperties[i][E_PROP_DATA_NAME][0] = '\0';
	YSI_g_sAreaPointers[area] = i;
	return i;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who entered an area.</param>
 * <param name="area">Area they entered.</param>
 * <remarks>
 *  Internal callback from YSI_areas.
 * </remarks>
 *//*------------------------------------------------------------------------**/

Property_OnPlayerEnterArea(playerid, area)
{
	new
		prop = YSI_g_sAreaPointers[area];
	if (prop == NO_PROPERTY)
	{
		return 0;
	}
	if (YSI_g_sProperties[prop][E_PROP_DATA_FLAGS] & e_PROP_FLAGS_TYPES == e_PROP_FLAGS_TYPE_RSRC)
	{
		if (!Property_GetOption(2, YSI_g_sProperties[prop][E_PROP_DATA_FLAGS]))
		{
			if (YSI_g_sProperties[prop][E_PROP_DATA_NAME][0]) Text_SendFormat(playerid, "YSI_FORBIDDEN_2", YSI_g_sProperties[prop][E_PROP_DATA_NAME]);
			else Text_Send(playerid, $YSI_FORBIDDEN);
			Bit_Set(YSI_g_sPlayerProperties[playerid], prop, 1, GROUP_PROPERTY_BITS);
		}
	}
	else Bit_Set(YSI_g_sPlayerProperties[playerid], prop, 1, GROUP_PROPERTY_BITS);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who left an area.</param>
 * <param name="areaid">Area they left.</param>
 * <remarks>
 *  Internal callback from YSI_areas.
 * </remarks>
 *//*------------------------------------------------------------------------**/

Property_OnPlayerLeaveArea(playerid, area)
{
	new
		prop = YSI_g_sAreaPointers[area];
	if (prop == NO_PROPERTY)
	{
		return 0;
	}
	Bit_Set(YSI_g_sPlayerProperties[playerid], prop, (YSI_g_sProperties[prop][E_PROP_DATA_FLAGS] & e_PROP_FLAGS_TYPES == e_PROP_FLAGS_TYPE_RSRC && Property_GetOption(2, YSI_g_sProperties[prop][E_PROP_DATA_FLAGS])));
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who connected.</param>
 * <remarks>
 *  Internal callback.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HOOK__ OnPlayerConnect(playerid)
{
	YSI_g_sShopMenu[playerid][E_PROP_AMMU_MENU] = Menu:-1;
	Bit_SetAll(YSI_g_sPlayerProperties[playerid], false, GROUP_PROPERTY_BITS);
	for (new i = 0; i < 13; i++) YSI_g_sSpawnWeapons[playerid][i] = 0;
	YSI_g_sMoney[playerid] = 0;
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who connected.</param>
 * <remarks>
 *  Internal callback.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HOOK__ OnPlayerDisconnect(playerid, reason)
{
	FOREACH__ (new property : Bits(YSI_g_sPlayerProperties[playerid]))
	{
		new
			e_PROP_FLAGS:flags = YSI_g_sProperties[property][E_PROP_DATA_FLAGS];
		if (flags & e_PROP_FLAGS_ACTIVE)
		{
			if ((flags & e_PROP_FLAGS_TYPES) == e_PROP_FLAGS_TYPE_PROP)
			{
				if (Property_GetOption(2, flags))
				{
					if (_:Bit_GetBit(YSI_g_sProperties[property][E_PROP_DATA_PLAYERS], playerid))
					{
						Bit_Set(YSI_g_sProperties[property][E_PROP_DATA_PLAYERS], playerid, false);//, PLAYER_BIT_ARRAY);
					}
				}
				else
				{
					if (_:(YSI_g_sProperties[property][E_PROP_DATA_PLAYERS][0] == Bit:playerid))
					{
						YSI_g_sProperties[property][E_PROP_DATA_PLAYERS][0] = Bit:INVALID_PLAYER_ID;
					}
				}
				#pragma tabsize 4
				#if defined _YSI_VISUAL_PICKUPS
					if (Property_GetOption(5, flags))
						Pickup_Show(_:(flags & e_PROP_FLAGS_LINK), 1);
					else
				#endif
						Checkpoint_SetVisible(_:(flags & e_PROP_FLAGS_LINK), 1);
				#pragma tabsize 4
			}
			else if ((flags & e_PROP_FLAGS_TYPES) == e_PROP_FLAGS_TYPE_HOUS)
			{
				if (_:(YSI_g_sProperties[property][E_PROP_DATA_PLAYERS][0] == Bit:playerid))
				{
					YSI_g_sProperties[property][E_PROP_DATA_PLAYERS][0] = Bit:INVALID_PLAYER_ID;
				}
			}
		}
	}
	Bit_SetAll(YSI_g_sPlayerProperties[playerid], false);
	YSI_g_sPropCount[playerid] = 0;
	YSI_g_sHouseCount[playerid] = 0;
	YSI_g_sCurrentHouse[playerid] = -1;
	//YSI_g_sPickupTimer[playerid] = -1;
	//YSI_g_sPlayerPickup[playerid] = NO_PICKUP;
	//#pragma unused reason
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who spawned.</param>
 * <remarks>
 *  Internal callback.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HOOK__ OnPlayerSpawn(playerid)
{
	for (new i = 0; i < 12; i++) if (YSI_g_sSpawnWeapons[playerid][i]) GivePlayerWeapon(playerid, (YSI_g_sSpawnWeapons[playerid][i] >> 24) & 0xFF, YSI_g_sSpawnWeapons[playerid][i] & 0xFFFFFF);
	if (YSI_g_sSpawnWeapons[playerid][12]) SetPlayerArmour(playerid, 100.0);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who left a checkpoint.</param>
 * <param name="cpid">Checkpoint they left.</param>
 * <remarks>
 *  Internal callback from YSI_checkpoints.
 * </remarks>
 *//*------------------------------------------------------------------------**/

HOOK__ OnPlayerLeaveCPEx(playerid, cpid)
{
	new
		cp = YSI_g_sCheckpointPointers[cpid];
	if (cp == NO_CHECKPOINT)
	{
		return 0;
	}
	new
		flags = YSI_g_sProperties[cp][E_PROP_DATA_FLAGS],
		type = _:(_:flags & _:e_PROP_FLAGS_TYPES);
	if ((type != _:e_PROP_FLAGS_TYPE_HOUS || YSI_g_sProperties[cp][E_PROP_DATA_PLAYERS][0] != Bit:playerid) && (type != _:e_PROP_FLAGS_TYPE_PROP || !Property_IsOwner(playerid, cp, flags)))
	{
		Bit_Set(YSI_g_sPlayerProperties[playerid], cp, false);//, GROUP_PROPERTY_BITS);
	}
	return 1;
}

#if defined _YSI_VISUAL_PICKUPS
	/*---------------------------------------------------------------------*//**
	 *
	 * <param name="playerid">Player who picked up a pickup.</param>
	 * <param name="pickupid">Pickup they picked up.</param>
	 * <remarks>
	 *  Internal callback from YSI_pickups.
	 * </remarks>
	 *//*--------------------------------------------------------------------**/
	
	Property_OnPlayerPickUpPickup(playerid, pickupid)
	{
		P:2("Property_OnPlayerPickUpPickup() start");
		if (YSI_g_sPickupTimer[playerid] == -1)
		{
			P:4("Property_OnPlayerPickUpPickup() No timer");
			if (pickupid >= MAX_DYN_PICKUPS)
			{
				return 0;
			}
			P:4("Property_OnPlayerPickUpPickup() Valid pickup");
			new
				prop = YSI_g_sPickupPointers[pickupid];
			if (prop == NO_PROPERTY)
			{
				return 0;
			}
			P:4("Property_OnPlayerPickUpPickup() Valid property");
			YSI_g_sPlayerPickup[playerid] = pickupid;
			Bit_Set(YSI_g_sPlayerProperties[playerid], prop, 1, GROUP_PROPERTY_BITS);
			switch (_:(YSI_g_sProperties[prop][E_PROP_DATA_FLAGS] & e_PROP_FLAGS_TYPES))
			{
				case e_PROP_FLAGS_TYPE_PROP:
				{
					new
						data1 = YSI_g_sProperties[prop][E_PROP_DATA_DATA_2] & 0x3FFFF,
						data2 = ((YSI_g_sProperties[prop][E_PROP_DATA_DATA_2] >>> 6) & 0x03FFF000) | ((YSI_g_sProperties[prop][E_PROP_DATA_DATA_1] >>> 20) & 0x00000FFF);
					Text_SendFormat(playerid, "YSI_PROP_NAME", YSI_g_sProperties[prop][E_PROP_DATA_NAME], data1, data2);
					if (Property_GetOption(2, YSI_g_sProperties[prop][E_PROP_DATA_FLAGS]))
					{
						if (Bit_GetBit(YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS], playerid)) Text_Send(playerid, $YSI_PROP_YOURS);
						else Text_SendFormat(playerid, "YSI_PROP_BUY", "buy");
					}
					else
					{
						new
							owner = _:YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][0];
						if (owner == playerid) Text_Send(playerid, $YSI_PROP_YOURS);
						else if (IsPlayerConnected(owner)) Text_SendFormat(playerid, "YSI_PROP_OWNER", ReturnPlayerName(owner), owner);
						if (owner != playerid) Text_SendFormat(playerid, "YSI_PROP_BUY", "buy");
					}
				}
				case e_PROP_FLAGS_TYPE_HOUS:
				{
					new
						owner = _:YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][0];
					if (owner == INVALID_PLAYER_ID) Text_SendFormat(playerid, "YSI_PROP_BUY_HOUSE", "buy", YSI_g_sProperties[prop][E_PROP_DATA_NAME][6]);
					else if (owner == playerid) Text_SendFormat(playerid, "YSI_PROP_ENTER", "enter", "exit");
					else Text_SendFormat(playerid, "YSI_PROP_HOUSE_OWNED", ReturnPlayerName(owner));
				}
			}
			YSI_g_sPickupTimer[playerid] = YSI_SetTimerEx("Property_PickupTimeCheck", 500, 1, "ii", playerid, pickupid);
		}
		P:2("Property_OnPlayerPickUpPickup() end");
		return 1;
	}
	
	/*---------------------------------------------------------------------*//**
	 *
	 * <param name="playerid">Player who is on a pickup.</param>
	 * <param name="pickupid">Pickup to check.</param>
	 *
	 *  Checks if a player has moved away from a pickup.
	 * </remarks>
	 *//*--------------------------------------------------------------------**/
	
	public Property_PickupTimeCheck(playerid, pickupid)
	{
		if (!Pickup_IsPlayerOnPickup(playerid, pickupid))
		{
			KillTimer(YSI_g_sPickupTimer[playerid]);
			YSI_g_sPickupTimer[playerid] = -1;
			YSI_g_sPlayerPickup[playerid] = NO_PICKUP;
			new
				prop = YSI_g_sPickupPointers[pickupid];
			if (prop != NO_PROPERTY)
			{
				new
					flags = _:YSI_g_sProperties[prop][E_PROP_DATA_FLAGS],
					type = flags & _:e_PROP_FLAGS_TYPES;
				if ((type != _:e_PROP_FLAGS_TYPE_HOUS || YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][0] != Bit:playerid) && (type != _:e_PROP_FLAGS_TYPE_PROP || !Property_IsOwner(playerid, prop, flags)))
				{
					Bit_Set(YSI_g_sPlayerProperties[playerid], prop, 0, GROUP_PROPERTY_BITS);
				}
			}
		}
	}
#endif

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who entered a checkpoint.</param>
 * <param name="cpid">Checkpoint they entered.</param>
 * <remarks>
 *  Internal callback from YSI_checkpoints.
 * </remarks>
 *//*------------------------------------------------------------------------**/

Property_OnPlayerEnterCheckpointEx(playerid, cpid)
{
	if (cpid >= MAX_CHECKPOINTS)
	{
		return 0;
	}
	new
		prop = YSI_g_sCheckpointPointers[cpid];
	if (prop == NO_PROPERTY)
	{
		return 0;
	}
	new
		e_PROP_FLAGS:flag = YSI_g_sProperties[prop][E_PROP_DATA_FLAGS];
	switch (flag & e_PROP_FLAGS_TYPES)
	{
		case e_PROP_FLAGS_TYPE_PROP:
		{
			Text_SendFormat(playerid, "YSI_PROP_NAME", YSI_g_sProperties[prop][E_PROP_DATA_NAME], ((YSI_g_sProperties[prop][E_PROP_DATA_DATA_2] >>> 6) & 0x03FFF000) | ((YSI_g_sProperties[prop][E_PROP_DATA_DATA_1] >>> 20) & 0x00000FFF), YSI_g_sProperties[prop][E_PROP_DATA_DATA_2] & 0x3FFFF);
			if (Property_GetOption(2, flag))
			{
				if (Bit_GetBit(YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS], playerid)) Text_Send(playerid, $YSI_PROP_YOURS);
				else Text_SendFormat(playerid, "YSI_PROP_BUY", "buy");
			}
			else
			{
				new
					owner = _:YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][0];
				if (owner == playerid) Text_Send(playerid, $YSI_PROP_YOURS);
				else if (IsPlayerConnected(owner)) Text_SendFormat(playerid, "YSI_PROP_OWNER", ReturnPlayerName(owner), owner);
				if (owner != playerid) Text_SendFormat(playerid, "YSI_PROP_BUY", "buy");
			}
		}
		case e_PROP_FLAGS_TYPE_HOUS:
		{
			new
				owner = _:YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][0];
			if (owner == INVALID_PLAYER_ID) Text_SendFormat(playerid, "YSI_PROP_BUY_HOUSE", "buy", YSI_g_sProperties[prop][E_PROP_DATA_NAME][6]);
			else if (owner == playerid) Text_SendFormat(playerid, "YSI_PROP_ENTER", "enter", "exit");
			else Text_SendFormat(playerid, "YSI_PROP_HOUSE_OWNED", ReturnPlayerName(owner));
		}
		case e_PROP_FLAGS_TYPE_AMMU:
		{
			Property_GenerateAmmuMenu(playerid, prop, 0, 0);
			TogglePlayerControllable(playerid, 0);
		}
		case e_PROP_FLAGS_TYPE_BANK:
		{
			if (YSI_g_sProperties[prop][E_PROP_DATA_NAME][0]) Text_SendFormat(playerid, "YSI_BANK_NAME", YSI_g_sProperties[prop][E_PROP_DATA_NAME]);
			else Text_Send(playerid, $YSI_BANK_WELCOME);
			Text_SendFormat(playerid, "YSI_BANK_HELP1", "bank");
			Text_SendFormat(playerid, "YSI_BANK_HELP2", "withdraw");
			Text_SendFormat(playerid, "YSI_BANK_HELP3", "balance");
			Text_SendFormat(playerid, "YSI_BANK_BALANCE", YSI_g_sMoney[playerid]);
		}
		case e_PROP_FLAGS_TYPE_TELS:
		{
			if (GetPlayerMoney(playerid) >= YSI_g_sProperties[prop][E_PROP_DATA_DATA_1])
			{
				GivePlayerMoney(playerid, -YSI_g_sProperties[prop][E_PROP_DATA_DATA_1]);
				SetPlayerPos(playerid, Float:YSI_g_sProperties[prop][E_PROP_DATA_DATA_2], Float:YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][0], Float:YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][1]);
				if (YSI_g_sProperties[prop][E_PROP_DATA_NAME][0]) Text_SendFormat(playerid, "YSI_TELS_NAME", YSI_g_sProperties[prop][E_PROP_DATA_NAME]);
				else Text_Send(playerid, $YSI_TELS_TELE);
			}
			else Text_SendFormat(playerid, "YSI_TELS_MONEY", YSI_g_sProperties[prop][E_PROP_DATA_DATA_1]);
			return 1;
		}
		case e_PROP_FLAGS_TYPE_MONP: {}
		default:
		{
			return 0;
		}
	}
	Bit_Set(YSI_g_sPlayerProperties[playerid], prop, 1, GROUP_PROPERTY_BITS);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="ammu">Ammunation to get the weapon from.</param>
 * <param name="slot">Number of active slots to skip.</param>
 * <param name="page">Start slot.</param>
 * <remarks>
 *  Gets the slot active weapon from page start.  If you want the first one
 *  use page = 0 and slot = 0.  If you want the second use page = 0 and slot
 *  = 1 or slot = 0 and page > position of first.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Property_GetWeapon(ammu, slot, &page = 0)
{
	new
		weapon = 0;
	while (page < 40)
	{
		if (!page)
		{
			weapon = YSI_g_sProperties[ammu][E_PROP_DATA_DATA_1];
		}
		else if (page == 1)
		{
			weapon = YSI_g_sProperties[ammu][E_PROP_DATA_DATA_2];
		}
		else if (page < PLAYER_BIT_ARRAY + 2)
		{
			weapon = _:YSI_g_sProperties[ammu][E_PROP_DATA_PLAYERS][page - 2];
		}
		else
		{
			weapon = YSI_g_sProperties[ammu][E_PROP_DATA_NAME][page - (PLAYER_BIT_ARRAY + 2)];
		}
		if (weapon)
		{
			if (!slot) return weapon;
			else slot--;
		}
		page++;
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="weapon">Weapon slot to get the name of.</param>
 * <remarks>
 *  Gets a real weapon name based on the slot of the weapon, not the weapon id.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Property_WeaponName(weapon)
{
	static
		names[][18] = 
		{
			"Brassknuckle",			"Golfclub",		"Night Stick",		"Knife",
			"Bat",					"Shovel",		"Poolstick",		"Katana",
			"Chainsaw",				"Dildo",		"Dildo 2",			"Vibrator",
			"Vibrator 2",			"Flower",		"Cane",				"Grenade",
			"Teargas",				"Molotov",		"Colt 45",			"Silenced Pistol",
			"Desert Eagle",			"Shotgun",		"Sawnoff",			"Spaz 9",
			"Uzi",					"MP5",			"AK47",				"M4",
			"TEC9",					"Rifle",		"Sniper Rifle",		"Rocket Launcher",
			"Flame Thrower",		"Minigun",		"Satchel Charge",	"Spraycan",
			"Fire Extinguisher",	"Camera",		"Parachute",		"Armour"
		},
		none[18] = "NONE";
	if (weapon >=0 && weapon < sizeof (names)) return names[weapon];
	else return none;
}

/*-------------------------------------------------------------------------*//**
 * <param name="data">Compressed data.</param>
 * <remarks>
 *  Extracts the cost from the passed data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Property_WeaponCost(data));
#define Property_WeaponCost(%1) \
	((%1) & 0xFFFFF)

/*-------------------------------------------------------------------------*//**
 * <param name="data">Compressed data.</param>
 * <remarks>
 *  Extracts the ammo from the passed data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

P:D(Property_WeaponAmmo(data));
#define Property_WeaponAmmo(%1) \
	((%1) >> 20)

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who left a menu.</param>
 * <remarks>
 *  Internal callback.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define Property_OnPlayerExitedMenu Property_OnPlayerExited

Property_OnPlayerExitedMenu(playerid)
{
	if (GetPlayerMenu(playerid) == YSI_g_sShopMenu[playerid][E_PROP_AMMU_MENU])
	{
		new
			data = YSI_g_sShopMenu[playerid][E_PROP_AMMU_DATA];
		if (data & 0x01)
		{
			Property_GenerateAmmuMenu(playerid, data >> 16, 0, 0);
			return 1;
		}
	}
	YSI_g_sShopMenu[playerid][E_PROP_AMMU_MENU] = Menu:-1;
	TogglePlayerControllable(playerid, 1);
	YSI_g_sShopMenu[playerid][E_PROP_AMMU_DATA] = 0;
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="slot">Data slot to translate.</param>
 * <returns>
 *  weaponid represented by that slot.
 * </returns>
 *//*------------------------------------------------------------------------**/

static stock Property_GetWeaponFromSlot(slot)
{
	if (slot < 18) return slot + 1;
	else if (slot < 33) return slot + 4;
	else if (slot < 36) return slot + 5;
	else if (slot < 38) return slot + 6;
	else if (slot == 38) return WEAPON_PARACHUTE;
	else if (slot == 39) return WEAPON_ARMOUR;
	else return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to save the weapon for.</param>
 * <param name="weaponslot">Slot of the weapon.</param>
 * <param name="ammo">Ammo to save.</param>
 * <remarks>
 *  Saves weapons based on slots so you only have 13 spawn weapons based on
 *  real weapon slots (armour is slot 12).  This is similar to weapon slot
 *  sorting but it's sorting slots which are packed from original weapon
 *  numbers and missing some.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Property_SavePlayerWeapon(playerid, weaponslot, ammo)
{
	new
		slot = 0,
		weapon = 0;
	switch (weaponslot)
	{
		case 0: slot = 0, weapon = WEAPON(WEAPON_BRASSKNUCKLE);
		case 1, 2, 3, 4, 5, 6, 7, 8: slot = 1, weapon = WEAPON(weaponslot + 1);
		case 18, 19, 20: slot = 2, weapon = WEAPON(weaponslot + 4);
		case 21, 22, 23: slot = 3, weapon = WEAPON(weaponslot + 4);
		case 24, 25, 28: slot = 4, weapon = WEAPON(weaponslot + 4);
		case 26, 27: slot = 5, weapon = WEAPON(weaponslot + 4);
		case 29, 30: slot = 6, weapon = WEAPON(weaponslot + 4);
		case 31: slot = 7, weapon = WEAPON(WEAPON_ROCKETLAUNCHER); 
		case 32, 33: slot = 7, weapon = WEAPON(weaponslot + 5);
		case 15, 16, 17: slot = 8, weapon = WEAPON(weaponslot + 1);
		case 34: slot = 8, weapon = WEAPON(WEAPON_SATCHEL);
		case 35, 36, 37: slot = 9, weapon = WEAPON(weaponslot + 6);
		case 9, 10, 11, 12, 13, 14: slot = 10, weapon = WEAPON(weaponslot + 1);
		case 38: slot = 11, weapon = WEAPON(WEAPON_PARACHUTE);
		case 39: slot = 12, weapon = 1;
		default: return;
	}
	if (YSI_g_sSpawnWeapons[playerid][slot] & 0xFF000000 == weapon) YSI_g_sSpawnWeapons[playerid][slot] += ammo & 0x00FFFFFF;
	else YSI_g_sSpawnWeapons[playerid][slot] = (weapon & 0xFF000000) | (ammo & 0x00FFFFFF);
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to get the weapon for.</param>
 * <param name="slot">Slot to get.</param>
 * <param name="weaponslot">Return for the weapon type.</param>
 * <param name="ammo">Return for the ammo.</param>
 * <remarks>
 *  Gets a player's stored for spawn weapons.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Property_GetSlotWeapon(playerid, slot, &weapon, &ammo)
{
	if (playerid < 0 || playerid >= MAX_PLAYERS || slot < 0 || slot >= 13) return;
	weapon = (YSI_g_sSpawnWeapons[playerid][slot] & 0xFF000000) >> 24;
	ammo = YSI_g_sSpawnWeapons[playerid][slot] & 0x00FFFFFF;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to save weapons for.</param>
 * <remarks>
 *  Saves a players current spawn weapon data to an ini (i.e. their save file).
 *  110953013 is props in adler32
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Property_SaveWeapons(playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		new
			str[8] = "wslot";
		for (new i = 0; i <= 12; i++)
		{
			if (i >= 10)
			{
				new
					tens = i / 10;
				str[5] = tens + '0';
				str[6] = (i - (tens * 10)) + '0';
				str[7] = '\0';
			}
			else
			{
				str[5] = i + '0';
				str[6] = '\0';
			}
			Player_WriteInt(str, YSI_g_sSpawnWeapons[playerid][i]);
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to load weapons for.</param>
 * <param name="identifier">Slot data.</param>
 * <param name="text">Weapon data.</param>
 * <remarks>
 *  Called when a player logs in to load their previous weapons.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Property_LoadWeapons(playerid, identifier[], text[])
{
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		if (strcmp(identifier, "wslot", false, 5)) return;
		new
			slot = strval(identifier[5]);
		if (slot < 0 || slot > 12) return;
		YSI_g_sSpawnWeapons[playerid][slot] = strval(text);
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to save bank for.</param>
 * <remarks>
 *  Saves a players current bank data to an ini (i.e. their save file).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Property_SaveBank(playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS)
	{
		Player_WriteInt("bankmoney", YSI_g_sMoney[playerid]);
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to get bank for.</param>
 * <returns>
 *  Money in bank.
 * </returns>
 * <remarks>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Property_GetBank(playerid)
{
	if (playerid >= 0 && playerid < MAX_PLAYERS) return YSI_g_sMoney[playerid];
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to load bank for.</param>
 * <param name="identifier">Identifier name to check.</param>
 * <param name="text">Possibly bank amount.</param>
 * <remarks>
 *  Called when a player logs in to load their previous banked money.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Property_LoadBank(playerid, identifier[], text[])
{
	if (playerid >= 0 && playerid < MAX_PLAYERS && !strcmp(identifier, "bankmoney"))
	{
		YSI_g_sMoney[playerid] = strval(text);
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who selected a row.</param>
 * <param name="row">Row they selected.</param>
 * <remarks>
 *  Internal callback.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define Property_OnPlayerSelectedMenuRow Property_OnPlayerSelectedRow

Property_OnPlayerSelectedMenuRow(playerid, row)
{
	if (GetPlayerMenu(playerid) == YSI_g_sShopMenu[playerid][E_PROP_AMMU_MENU])
	{
		new
			data = YSI_g_sShopMenu[playerid][E_PROP_AMMU_DATA],
			slot = (data >> 8) & 0xFF,
			ammu = data >> 16,
			count = YSI_g_sProperties[ammu][E_PROP_DATA_NAME][MAX_PROP_NAME - 1];
		if (data & 0x01)
		{
			new
				weapon = 0,
				flags = _:YSI_g_sProperties[ammu][E_PROP_DATA_FLAGS],
				wdat = 0;
			wdat = Property_GetWeapon(ammu, slot, weapon);
			if (GetPlayerMoney(playerid) >= Property_WeaponCost(wdat))
			{
				if (Property_GetOption(1, flags)) Property_SavePlayerWeapon(playerid, weapon, Property_WeaponAmmo(wdat));
				if (Property_GetOption(2, flags)) Property_GivePlayerWeapon(playerid, weapon, Property_WeaponAmmo(wdat));
				GivePlayerMoney(playerid, 0 - Property_WeaponCost(wdat));
			}
			else Text_Send(playerid, $YSI_AMMU_NO_MONEY);
			Property_GenerateAmmuMenu(playerid, ammu, 0, 0);
		}
		else
		{
			if (count > slot && row == 11) Property_GenerateAmmuMenu(playerid, ammu, 0, slot);
			else if (count > 12)
			{
				if (slot > 11 && row == 0) Property_GenerateAmmuMenu(playerid, ammu, 0, ((slot - 12) / 11) * 11);
				else Property_GenerateAmmuMenu(playerid, ammu, 1, ((slot - 1) / 11) * 10 + row);
			}
			else
			{
				Property_GenerateAmmuMenu(playerid, ammu, 1, row);
			}
		}
		return 1;
	}
	else YSI_g_sShopMenu[playerid][E_PROP_AMMU_MENU] = Menu:-1;
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who watns the menu.</param>
 * <param name="ammu">Ammunation they're in.</param>
 * <param name="stage">Current menu view if any.</param>
 * <param name="page">Current menu page.</param>
 * <remarks>
 *  If slot is 0 the main selection will be displayed and page will represent
 *  the offset from the start if there are more than 12 weapons for sale.  If
 *  stage is 1 the individual confirmation menu for one weapon will show and
 *  page will determine which weapon to show.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Property_GenerateAmmuMenu(playerid, ammu, stage, page)
{
	new
		Menu:menu = CreateMenu("Ammunation", 2, 270.0, 150.0, 200.0, 50.0),
		slot = page;
	SetMenuColumnHeader(menu, 0, "Weapon");
	SetMenuColumnHeader(menu, 1, "Price");
	if (stage)
	{
		new
			start = 0,
			weapon = Property_GetWeapon(ammu, page, start);
		if (weapon)
		{
			AddMenuItem(menu, 0, Property_WeaponName(start));
			AddMenuItem(menu, 1, numstr(Property_WeaponCost(weapon)));
		}
	}
	else
	{
		new
			weapon = 0,
			start = 0,
			row = 0,
			end = page + 12,
			next = page,
			money = GetPlayerMoney(playerid);
		if (YSI_g_sProperties[ammu][E_PROP_DATA_NAME][MAX_PROP_NAME - 1] - page > 12) end--;
		if (YSI_g_sProperties[ammu][E_PROP_DATA_NAME][MAX_PROP_NAME - 1] > 12 && page)
		{
			end--;
			AddMenuItem(menu, 0, "Back...");
			AddMenuItem(menu, 1, " ");
		}
		while (slot < end && (weapon = Property_GetWeapon(ammu, next, start)))
		{
			new
				cost = Property_WeaponCost(weapon);
			AddMenuItem(menu, 0, Property_WeaponName(start));
			AddMenuItem(menu, 1, numstr(cost));
			if (cost > money) DisableMenuRow(menu, row);
			slot++;
			row++;
			start++;
			next = 0;
		}
		if (end != 12 && Property_GetWeapon(ammu, 0, start))
		{
			AddMenuItem(menu, 0, "Next...");
			AddMenuItem(menu, 1, " ");
		}
	}
	YSI_g_sShopMenu[playerid][E_PROP_AMMU_MENU] = menu;
	YSI_g_sShopMenu[playerid][E_PROP_AMMU_DATA] = ((ammu & 0xFFFF) << 16) | ((slot & 0xFF) << 8) | (stage ? 1 : 0) | 2;
	ShowMenuForPlayer(menu, playerid);
	DestroyMenu(menu);
}

/*-------------------------------------------------------------------------*//**
 * Command:
 *  sell
 * Parameters:
 *  <id> - Property to sell.
 * </returns>
 * <remarks>
 *  Sells a property you own if it can be sold.
 * </remarks>
 *//*------------------------------------------------------------------------**/

YCMD:sell(playerid, params[], help)
{
	P:2("ycmd_sell() start");
	if (help)
	{
		Text_Send(playerid, $YSI_SELL_HELP_1);
		Text_Send(playerid, $YSI_SELL_HELP_2);
		Text_Send(playerid, $YSI_SELL_HELP_3);
		Text_Send(playerid, $YSI_SELL_HELP_4);
	}
	else
	{
		P:3("ycmd_sell() not help %d", params[0]);
		if (params[0] >= '0' && params[0] <= '9')
		{
			P:5("ycmd_sell() params OK");
			new
				prop = strval(params);
			if (Property_IsActive(prop))
			{
				new
					e_PROP_FLAGS:flag = YSI_g_sProperties[prop][E_PROP_DATA_FLAGS];
				if ((flag & e_PROP_FLAGS_TYPES) == e_PROP_FLAGS_TYPE_PROP)
				{
					if (Property_GetOption(1, flag))
					{
						if (Property_GetOption(2, flag))
						{
							if (Bit_GetBit(YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS], playerid)) Bit_Set(YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS], playerid, 0, PLAYER_BIT_ARRAY);
							else return Text_Send(playerid, $YSI_SELL_CANT);
						}
						else
						{
							if (_:YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][0] == playerid) YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][0] = Bit:INVALID_PLAYER_ID;
							else return Text_Send(playerid, $YSI_SELL_CANT);
						}
						new
							cost = ((((YSI_g_sProperties[prop][E_PROP_DATA_DATA_2] >>> 6) & 0x03FFF000) | ((YSI_g_sProperties[prop][E_PROP_DATA_DATA_1] >>> 20) & 0x00000FFF)) * ((Property_GetOption(3, flag)) ? PROPERTY_SELL_PERCENT : 100)) / 100;
						Text_SendFormat(playerid, "YSI_SELL_SOLD", cost);
						#pragma tabsize 4
						#if defined _YSI_VISUAL_PICKUPS
							if (Property_GetOption(5, flag))
								Pickup_Show(_:(flag & e_PROP_FLAGS_LINK), 1);
							else
						#endif
								Checkpoint_SetVisible(_:(flag & e_PROP_FLAGS_LINK), 1);
						#pragma tabsize 4
						GivePlayerMoney(playerid, cost);
						YSI_g_sPropCount[playerid]--;
						Bit_Set(YSI_g_sPlayerProperties[playerid], prop, 0, GROUP_PROPERTY_BITS);
					}
					else Text_Send(playerid, $YSI_SELL_CANT);
					return 1;
				}
				else if ((flag & e_PROP_FLAGS_TYPES) == e_PROP_FLAGS_TYPE_PROP)
				{
					if (_:YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][0] == playerid)
					{
						new
							cost = YSI_g_sProperties[prop][E_PROP_DATA_NAME][0];
						Text_SendFormat(playerid, "YSI_SELL_SOLD", cost);
						GivePlayerMoney(playerid, cost);
						YSI_g_sHouseCount[playerid]--;
						Bit_Set(YSI_g_sPlayerProperties[playerid], prop, 0, GROUP_PROPERTY_BITS);
						YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][0] = Bit:INVALID_PLAYER_ID;
					}
					else Text_Send(playerid, $YSI_SELL_CANT);
					return 1;
				}
			}
		}
		Text_Send(playerid, $YSI_SELL_NO_ID);
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player who is banking money.</param>
 * <param name="amount">Amount of money they're banking.</param>
 * <remarks>
 *  Does banks and withdrawls.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Property_Bank(playerid, amount)
{
	if (IsPlayerInCheckpoint(playerid))
	{
		new
			cpid = Checkpoint_Get(playerid),
			prop = YSI_g_sCheckpointPointers[cpid];
		if (prop != NO_PROPERTY)
		{
			new
				e_PROP_FLAGS:flag = YSI_g_sProperties[prop][E_PROP_DATA_FLAGS];
			if (flag & e_PROP_FLAGS_TYPES == e_PROP_FLAGS_TYPE_BANK)
			{
				if ((amount > 0) ? (GetPlayerMoney(playerid) >= amount) : (YSI_g_sMoney[playerid] + amount >= 0))
				{
					YSI_g_sMoney[playerid] += amount;
					GivePlayerMoney(playerid, -amount);
				}
				else return 0;
			}
			else Text_Send(playerid, $YSI_BANK_NOT);
		}
		else Text_Send(playerid, $YSI_BANK_NOT);
	}
	else Text_Send(playerid, $YSI_BANK_CP);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * Command:
 *  bank
 * Parameters:
 *  <amount> - Value to bank.
 * </returns>
 * <remarks>
 *  Calls Property_Bank with positive input amount.
 * </remarks>
 *//*------------------------------------------------------------------------**/

YCMD:bank(playerid, params[], help)
{
	if (help)
	{
		Text_Send(playerid, $YSI_BANK_HELP_1);
		Text_Send(playerid, $YSI_BANK_HELP_2);
		Text_Send(playerid, $YSI_BANK_HELP_3);
		Text_SendFormat(playerid, "YSI_BANK_HELP_4", "bank");
	}
	else
	{
		new
			bank = strval(params);
		if (Property_Bank(playerid, bank)) Text_SendFormat(playerid, "YSI_BANK_BANKED", bank, YSI_g_sMoney[playerid]);
		else Text_Send(playerid, $YSI_BANK_INSUFFICIENT);
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * Command:
 *  balance
 * Parameters:
 *  -
 * </returns>
 * <remarks>
 *  Displays how much you have in the bank.  Does not require you to be in a
 *  bank.
 * </remarks>
 *//*------------------------------------------------------------------------**/

YCMD:balance(playerid, params[], help)
{
	if (help) Text_Send(playerid, $YSI_BAL_HELP);
	else Text_SendFormat(playerid, "YSI_BANK_BALANCE", YSI_g_sMoney[playerid]);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * Command:
 *  withdraw
 * Parameters:
 *  <amount> - Amount to withdraw.
 * </returns>
 * <remarks>
 *  Calls Property_Bank with negative input amount.
 * </remarks>
 *//*------------------------------------------------------------------------**/

YCMD:withdraw(playerid, params[], help)
{
	if (help)
	{
		Text_Send(playerid, $YSI_WITH_HELP1);
		Text_Send(playerid, $YSI_WITH_HELP2);
		Text_Send(playerid, $YSI_WITH_HELP3);
		Text_SendFormat(playerid, "YSI_WITH_HELP4", "withdraw");
	}
	else
	{
		new
			bank = -strval(params);
		if (Property_Bank(playerid, bank)) Text_SendFormat(playerid, "YSI_WITHDREW", bank, YSI_g_sMoney[playerid]);
		else Text_Send(playerid, $YSI_BANK_INSUFFUCUENT);
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * Command:
 *  buy
 * Parameters:
 *  -
 * </returns>
 * <remarks>
 *  Allows you to purchase the property you are at.
 * </remarks>
 *//*------------------------------------------------------------------------**/

YCMD:buy(playerid, params[], help)
{
	P:2("ycmd_buy() start");
	if (help)
	{
		Text_Send(playerid, $YSI_BUY_HELP_1);
		Text_Send(playerid, $YSI_BUY_HELP_2);
		Text_Send(playerid, $YSI_BUY_HELP_3);
		Text_Send(playerid, $YSI_BUY_HELP_4);
	}
	else
	{
		P:3("ycmd_buy() Not help");
		new
			cpid = 0,
			prop = NO_PROPERTY;
		if (IsPlayerInCheckpoint(playerid))
		{
			P:4("ycmd_buy() Checkpoint");
			cpid = Checkpoint_Get(playerid);
			if (cpid != NO_CHECKPOINT)
			{
				prop = YSI_g_sCheckpointPointers[cpid];
			}
		}
		#if defined _YSI_VISUAL_PICKUPS
		#pragma tabsize 4
		else if (YSI_g_sPickupTimer[playerid] != -1)
		{
				cpid = YSI_g_sPlayerPickup[playerid];
				if (cpid != NO_PICKUP)
				{
					prop = YSI_g_sPickupPointers[cpid];
				}
				P:4("ycmd_buy() Pickup %d", cpid);
		}
		#pragma tabsize 4
		#endif
		else
		{
			P:4("ycmd_buy() Not in a checkpoint");
			Text_Send(playerid, $YSI_PROP_CP);
			return 1;
		}
		P:4("ycmd_buy() Prop %d", prop);
		if (prop != NO_PROPERTY)
		{
			new
				e_PROP_FLAGS:flag = YSI_g_sProperties[prop][E_PROP_DATA_FLAGS];
			if (flag & e_PROP_FLAGS_TYPES == e_PROP_FLAGS_TYPE_PROP)
			{
				if (YSI_g_sPropCount[playerid] < YSI_g_sMaxPlayerProps)
				{
					new
						price = ((YSI_g_sProperties[prop][E_PROP_DATA_DATA_2] >>> 6) & 0x03FFF000) | ((YSI_g_sProperties[prop][E_PROP_DATA_DATA_1] >>> 20) & 0x00000FFF);
					if (GetPlayerMoney(playerid) >= price)
					{
						if (Property_GetOption(2, flag))
						{
							if (Bit_GetBit(YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS], playerid))
							{
								Text_Send(playerid, $YSI_PROP_OWN);
								return 1;
							}
							Bit_Set(YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS], playerid, 1, PLAYER_BIT_ARRAY);
						}
						else
						{
							new
								owner = _:YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][0];
							if (owner == playerid)
							{
								Text_Send(playerid, $YSI_PROP_OWN);
								return 1;
							}
							if (IsPlayerConnected(owner))
							{
								GivePlayerMoney(owner, price);
								Text_SendFormat(owner, "YSI_PROP_OUT", YSI_g_sProperties[prop][E_PROP_DATA_NAME], ReturnPlayerName(playerid), playerid);
							}
							YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][0] = Bit:playerid;
							if (Property_GetOption(1, flag))
							{
								#if defined _YSI_VISUAL_PICKUPS
									if (Property_GetOption(5, flag))
										Pickup_Show(cpid, 0);
									else
								#endif
										Checkpoint_SetVisible(cpid, 0);
							}
							else if (YSI_g_sRebuyDelay)
							{
								YSI_SetTimerEx("Property_ResetRebuy", YSI_g_sRebuyDelay, 0, "i", prop);
								#if defined _YSI_VISUAL_PICKUPS
									if (Property_GetOption(5, flag))
										Pickup_Show(cpid, 0);
									else
								#endif
										Checkpoint_SetVisible(cpid, 0);
							}
						}
						YSI_g_sPropCount[playerid]++;
						GivePlayerMoney(playerid, -price);
						Text_SendFormat(playerid, "YSI_PROP_BOUGHT", YSI_g_sProperties[prop][E_PROP_DATA_NAME], price);
						Text_SendToAllFormat("YSI_PROP_ANN", ReturnPlayerName(playerid), YSI_g_sProperties[prop][E_PROP_DATA_NAME]);
						if (Property_GetOption(4, flag))
						{
							price = (price * PROPERTY_INCREASE_PERCENT) / 100;
							YSI_g_sProperties[prop][E_PROP_DATA_DATA_1] = (YSI_g_sProperties[prop][E_PROP_DATA_DATA_1] & 0xFFFFF) | ((price & 0x00000FFF) << 20);
							YSI_g_sProperties[prop][E_PROP_DATA_DATA_2] = (YSI_g_sProperties[prop][E_PROP_DATA_DATA_2] & 0x3FFFF) | ((price & 0x03FFF000) << 6);
						}
						if (Property_GetOption(1, flag)) Text_SendFormat(playerid, "YSI_PROP_SELL", "sell", prop, (price * ((Property_GetOption(3, flag)) ? PROPERTY_SELL_PERCENT : 100)) / 100);
					}
					else Text_Send(playerid, $YSI_PROP_AFFORD);
				}
				else Text_Send(playerid, $YSI_PROP_MAX);
			}
			else if (flag & e_PROP_FLAGS_TYPES == e_PROP_FLAGS_TYPE_HOUS)
			{
				if (YSI_g_sHouseCount[playerid] < YSI_g_sMaxPlayerHouses)
				{
					new
						owner = _:YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][0];
					if (owner == INVALID_PLAYER_ID)
					{
						new
							price = YSI_g_sProperties[prop][E_PROP_DATA_NAME][6];
						if (GetPlayerMoney(playerid) >= price)
						{
							YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][0] = Bit:playerid;
							YSI_g_sHouseCount[playerid]++;
							GivePlayerMoney(playerid, -price);
							Text_SendFormat(playerid, "YSI_PROP_BOUGHT_HOUSE", price);
							Text_SendFormat(playerid, "YSI_PROP_SELL", "sell", prop, price);
						}
						else Text_Send(playerid, $YSI_PROP_AFFORD);
					}
					else if (owner == playerid) Text_Send(playerid, $YSI_PROP_YOURS);
					else Text_SendFormat(playerid, "YSI_PROP_HOUSE_OWNED", ReturnPlayerName(owner));
				}
				else Text_Send(playerid, $YSI_PROP_MAX_HOUSE);
			}
			else Text_Send(playerid, $YSI_PROP_NOT);
		}
		else Text_Send(playerid, $YSI_PROP_NOT);
	}
	return 1;
	#pragma unused params
}

/*-------------------------------------------------------------------------*//**
 * <param name="prop">Property to make available.</param>
 * <remarks>
 *  Makes a property available for purchase after a delay.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Property_ResetRebuy(property);
public Property_ResetRebuy(property)
{
	if (Property_IsActive(property))
	{
		new
			e_PROP_FLAGS:flag = YSI_g_sProperties[property][E_PROP_DATA_FLAGS];
		if ((flag & e_PROP_FLAGS_TYPES) == e_PROP_FLAGS_TYPE_PROP)
		{
			#pragma tabsize 4
			#if defined _YSI_VISUAL_PICKUPS
				if (Property_GetOption(5, flag))
					Pickup_Show(_:(flag & e_PROP_FLAGS_LINK), 1);
				else
			#endif
					Checkpoint_SetVisible(_:(flag & e_PROP_FLAGS_LINK), 1);
			#pragma tabsize 4
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Does the main processing for the library.  Removes or kills people in areas
 *  they shouldn't be and gives out money to people who earnt it.
 * </remarks>
 *//*------------------------------------------------------------------------**/

ptask Property_Loop[500](i)
{
	static
		Float:s_fLastGoodPos[MAX_PLAYERS][3];//,
	//	sLastTick = 0;
	//new
	//	currentTick = GetTickCount(),
	//	elapse = currentTick - sLastTick;
	/*for (new i = 0; i < MAX_PROPERTIES; i++)
	{
		new
			flags = YSI_g_sProperties[i][E_PROP_DATA_FLAGS];
		if (flags & _:e_PROP_FLAGS_ACTIVE)
		{
			switch (flags & _:e_PROP_FLAGS_TYPES)
			{
				case e_PROP_FLAGS_TYPE_MONP, e_PROP_FLAGS_TYPE_MONA:
				{
					new
						time = YSI_g_sProperties[i][E_PROP_DATA_DATA_2];
					if (!time) time = YSI_g_sProperties[i][E_PROP_DATA_NAME][0];
					time -= elapse;
					if (time < 0) time = 0;
					YSI_g_sProperties[i][E_PROP_DATA_DATA_2] = time;
				}
				case e_PROP_FLAGS_TYPE_PROP:
				{
					new
						time = YSI_g_sProperties[i][E_PROP_DATA_NAME][MAX_PROP_NAME - 1];
					if (!time) time = YSI_g_sProperties[i][E_PROP_DATA_DATA_1] & 0x000FFFFF;
					time -= elapse;
					if (time <= 0) time = 0;
					YSI_g_sProperties[i][E_PROP_DATA_NAME][MAX_PROP_NAME - 1] = time;
				}
			}
		}
	}
	FOREACH__ (Player, i)
	{*/
	P:3("Property_Loop() foreach start");
	new
		money = 0,
		bad = 0;
	for (new j = 0; j < GROUP_PROPERTY_BITS; j++)
	{
		new
			props = _:YSI_g_sPlayerProperties[i][j],
			slot = 1,
			bit = 0;
		while (props)
		{
			if (props & slot)
			{
				new
					property = (j * 32) + bit,
					flags = YSI_g_sProperties[property][E_PROP_DATA_FLAGS];
				if (flags & _:e_PROP_FLAGS_ACTIVE)
				{
					switch (flags & _:e_PROP_FLAGS_TYPES)
					{
						case e_PROP_FLAGS_TYPE_MONP, e_PROP_FLAGS_TYPE_MONA:
							if (!YSI_g_sProperties[property][E_PROP_DATA_DATA_2]) GivePlayerMoney(i, YSI_g_sProperties[property][E_PROP_DATA_DATA_1]);
						case e_PROP_FLAGS_TYPE_PROP:
						{
							if (((Property_GetOption(2, flags)) ? (_:Bit_GetBit(YSI_g_sProperties[property][E_PROP_DATA_PLAYERS], i)) : (_:(YSI_g_sProperties[property][E_PROP_DATA_PLAYERS][0] == Bit:i))) && !YSI_g_sProperties[property][E_PROP_DATA_NAME][MAX_PROP_NAME - 1]) money += YSI_g_sProperties[property][E_PROP_DATA_DATA_2] & 0x3FFFF;
						}
						case e_PROP_FLAGS_TYPE_RSRC:
						{
							if (Property_GetOption(1, flags))
							{
								SetPlayerPos(i, s_fLastGoodPos[i][0], s_fLastGoodPos[i][1], s_fLastGoodPos[i][2]);
								bad = 1;
							}
							else
							{
								new Float:health = 0.0;
								GetPlayerHealth(i, health);
								SetPlayerHealth(i, health - YSI_g_sProperties[property][E_PROP_DATA_DATA_2]);
							}
						}
					}
				}
				props ^= slot;
			}
			slot <<= 1;
			bit++;
		}
	}
	if (money)
	{
		Text_Send(i, $YSI_PROP_EARNT, money);
		GivePlayerMoney(i, money);
	}
	if (!bad) GetPlayerPos(i, s_fLastGoodPos[i][0], s_fLastGoodPos[i][1], s_fLastGoodPos[i][2]);
	P:3("Property_Loop() foreach end");
	//}
	//sLastTick = currentTick;
}

/*-------------------------------------------------------------------------*//**
 * <param name="flags">Property data to check.</param>
 * <param name="playerid">Player to check for.</param>
 *//*------------------------------------------------------------------------**/

P:D(bool:Property_IsPlayerProperty(e_PROP_FLAGS:flags,playerid));
#define Property_IsPlayerProperty(%1,%2) \
	((%1) & e_PROP_FLAGS_ACTIVE && (%1) & e_PROP_FLAGS_TYPES == e_PROP_FLAGS_TYPE_PROP && Checkpoint_HasPlayerNoWorld(_:((%1) & e_PROP_FLAGS_LINK), (%2)))

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to count for.</param>
 * <remarks>
 *  Gets the number of properties this player could theoretically own.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Property_GetPlayerPropCount(playerid)
{
	new
		count = 0;
	for (new i = 0; i < MAX_PROPERTIES; i++)
	{
		new
			e_PROP_FLAGS:flags = YSI_g_sProperties[i][E_PROP_DATA_FLAGS];
		if (Property_IsPlayerProperty(flags, playerid)) count++;
	}
	return count;
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to get properties of.</param>
 * <param name="properties">Array to return properties in.</param>
 * <remarks>
 *  Gets the properties currently owned by this player.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Property_GetPropertyBits(playerid, Bit:properties[])
{
	if (playerid < 0 || playerid >= MAX_PLAYERS) return 0;
	for (new i = 0; i < MAX_PROPERTIES; i++)
	{
		new
			e_PROP_FLAGS:flags = YSI_g_sProperties[i][E_PROP_DATA_FLAGS];
		if (flags & e_PROP_FLAGS_ACTIVE && flags & e_PROP_FLAGS_TYPES == e_PROP_FLAGS_TYPE_PROP && ((Property_GetOption(2, flags)) ? (_:Bit_GetBit(YSI_g_sProperties[i][E_PROP_DATA_PLAYERS], playerid)) : (_:(_:YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][0] == playerid)))) Bit_Set(properties, i, 1, GROUP_PROPERTY_BITS);
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * Command:
 *  properties
 * Parameters:
 *  <page> - Page of properties to view (optional).
 * </returns>
 * <remarks>
 *  Lista all properties available to a player and who owns them.
 * </remarks>
 *//*------------------------------------------------------------------------**/

YCMD:properties(playerid, params[], help)
{
	if (help)
	{
		Text_Send(playerid, $YSI_LIST_HELP_1);
		Text_Send(playerid, $YSI_LIST_HELP_2);
		Text_Send(playerid, $YSI_LIST_HELP_3);
		return 1;
	}
	new
		props = Property_GetPlayerPropCount(playerid),
		pages = (props + 7) / 8,
		page = strval(params);
	if (props > 8)
	{
		if (page)
		{
			if (page <= pages)
			{
				for (new i = 0, j = 0, k = (page - 1) * 8, n = k + 8; i < MAX_PROPERTIES && j < n; i++)
				{
					new
						e_PROP_FLAGS:flags = YSI_g_sProperties[i][E_PROP_DATA_FLAGS];
					if (Property_IsPlayerProperty(flags, playerid))
					{
						if (j >= k)
						{
							if (Property_GetOption(2, flags)) Text_SendFormat(playerid, "YSI_LIST_MULTI", YSI_g_sProperties[i][E_PROP_DATA_NAME], Bit_GetCount(YSI_g_sProperties[i][E_PROP_DATA_PLAYERS], PLAYER_BIT_ARRAY));
							else Text_SendFormat(playerid, "YSI_LIST_FORM", YSI_g_sProperties[i][E_PROP_DATA_NAME], ReturnPlayerName(_:YSI_g_sProperties[i][E_PROP_DATA_PLAYERS][0]));
						}
						j++;
					}
				}
			}
			else Text_SendFormat(playerid, "YSI_LIST_PAGES", "properties", pages);
		}
		else
		{
			Text_Send(playerid, $YSI_LIST_MORE);
			Text_SendFormat(playerid, "YSI_LIST_PAGES", "properties", pages);
		}
	}
	else if (props)
	{
		for (new j = 0, i = 0; i < props && j < MAX_PROPERTIES; j++)
		{
			new
				e_PROP_FLAGS:flags = YSI_g_sProperties[j][E_PROP_DATA_FLAGS];
			if (Property_IsPlayerProperty(flags, playerid))
			{
				if (Property_GetOption(2, flags)) Text_SendFormat(playerid, "YSI_LIST_MULTI", YSI_g_sProperties[j][E_PROP_DATA_NAME], Bit_GetCount(YSI_g_sProperties[j][E_PROP_DATA_PLAYERS], PLAYER_BIT_ARRAY));
				else Text_SendFormat(playerid, "YSI_LIST_FORM", YSI_g_sProperties[j][E_PROP_DATA_NAME], ReturnPlayerName(_:YSI_g_sProperties[j][E_PROP_DATA_PLAYERS][0]));
				i++;
			}
		}
	}
	else Text_Send(playerid, $YSI_LIST_NONE);
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="property">Property to get link of.</param>
 * <remarks>
 *  Returns a reference to the area or checkpoint used by this property or
 *  NO_PROPERTY on fail.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Property_GetLink(property)
{
	if (Property_IsActive(property)) return _:(YSI_g_sProperties[property][E_PROP_DATA_FLAGS] & e_PROP_FLAGS_LINK);
	return NO_PROPERTY;
}

/*-------------------------------------------------------------------------*//**
 * Command:
 *  enter
 * Parameters:
 *  -
 * </returns>
 * <remarks>
 *  Allows you to enter a house you own.
 * </remarks>
 *//*------------------------------------------------------------------------**/

YCMD:enter(playerid, params[], help)
{
	P:2("ycmd_enter() start");
	if (help)
	{
		Text_Send(playerid, $YSI_ENTER_HELP_1);
		Text_Send(playerid, $YSI_ENTER_HELP_2);
	}
	else
	{
		P:3("ycmd_enter() Not help");
		new
			cpid = 0,
			prop = NO_PROPERTY;
		if (IsPlayerInCheckpoint(playerid))
		{
			P:4("ycmd_enter() Checkpoint");
			cpid = Checkpoint_Get(playerid);
			if (cpid != NO_CHECKPOINT)
			{
				prop = YSI_g_sCheckpointPointers[cpid];
			}
		}
		#if defined _YSI_VISUAL_PICKUPS
			#pragma tabsize 4
			else if (YSI_g_sPickupTimer[playerid] != -1)
			{
				cpid = YSI_g_sPlayerPickup[playerid];
				if (cpid != NO_PICKUP)
				{
					prop = YSI_g_sPickupPointers[cpid];
				}
				P:4("ycmd_enter() Pickup %d", cpid);
			}
		#endif
		#pragma tabsize 4
		P:4("ycmd_enter() Prop %d", prop);
		if (prop != NO_PROPERTY)
		{
			new
				e_PROP_FLAGS:flag = YSI_g_sProperties[prop][E_PROP_DATA_FLAGS];
			if (flag & e_PROP_FLAGS_TYPES == e_PROP_FLAGS_TYPE_HOUS)
			{
				if (_:YSI_g_sProperties[prop][E_PROP_DATA_PLAYERS][0] == playerid)
				{
					SetPlayerInterior(playerid, YSI_g_sProperties[prop][E_PROP_DATA_DATA_1]);
					SetPlayerVirtualWorld(playerid, YSI_g_sProperties[prop][E_PROP_DATA_DATA_2]);
					SetPlayerPos(playerid, Float:YSI_g_sProperties[prop][E_PROP_DATA_NAME][3], Float:YSI_g_sProperties[prop][E_PROP_DATA_NAME][4], Float:YSI_g_sProperties[prop][E_PROP_DATA_NAME][5]);
					YSI_g_sCurrentHouse[playerid] = prop;
				}
				else Text_Send(playerid, $YSI_ENTER_NOT_YOURS);
			}
			else Text_Send(playerid, $YSI_ENTER_NO_HOUSE);
		}
		else Text_Send(playerid, $YSI_ENTER_NO_HOUSE);
	}
	return 1;
	#pragma unused params
}

/*-------------------------------------------------------------------------*//**
 * Command:
 *  exit
 * Parameters:
 *  -
 * </returns>
 * <remarks>
 *  Allows you to exit a house you own.
 * </remarks>
 *//*------------------------------------------------------------------------**/

YCMD:exit(playerid, params[], help)
{
	P:2("ycmd_enter() start");
	if (help)
	{
		Text_Send(playerid, $YSI_EXIT_HELP_1);
	}
	else
	{
		new
			prop = YSI_g_sCurrentHouse[playerid];
		if (prop != -1)
		{
			if (IsPlayerInRangeOfPoint(playerid, 3.0, Float:YSI_g_sProperties[prop][E_PROP_DATA_NAME][3], Float:YSI_g_sProperties[prop][E_PROP_DATA_NAME][4], Float:YSI_g_sProperties[prop][E_PROP_DATA_NAME][5]))
			{
				YSI_g_sCurrentHouse[playerid] = -1;
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerPos(playerid, Float:YSI_g_sProperties[prop][E_PROP_DATA_NAME][0], Float:YSI_g_sProperties[prop][E_PROP_DATA_NAME][1], Float:YSI_g_sProperties[prop][E_PROP_DATA_NAME][2]);
			}
			else Text_Send(playerid, $YSI_EXIT_NEAR);
		}
		else Text_Send(playerid, $YSI_EXIT_NOT_IN);
	}
	return 1;
}
