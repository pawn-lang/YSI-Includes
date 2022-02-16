#if defined _INC_y_weapondata
	#endinput
#endif
#define _INC_y_weapondata

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
	Cheaterman
	DEntisT

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

/*

    88b           d88            88                       db        88888888ba  88  
    888b         d888            ""                      d88b       88      "8b 88  
    88`8b       d8'88                                   d8'`8b      88      ,8P 88  
    88 `8b     d8' 88 ,adPPYYba, 88 8b,dPPYba,         d8'  `8b     88aaaaaa8P' 88  
    88  `8b   d8'  88 ""     `Y8 88 88P'   `"8a       d8YaaaaY8b    88""""""'   88  
    88   `8b d8'   88 ,adPPPPP88 88 88       88      d8""""""""8b   88          88  
    88    `888'    88 88,    ,88 88 88       88     d8'        `8b  88          88  
    88     `8'     88 `"8bbdP"Y8 88 88       88    d8'          `8b 88          88  

*/

#define WEAPON_FIRE_TYPE_MELEE 0
#define WEAPON_FIRE_TYPE_PROJECTILE 1
#define WEAPON_FIRE_TYPE_INSTANT_HIT 2
#define WEAPON_FIRE_TYPE_AREA_EFFECT 3
#define WEAPON_FIRE_TYPE_USE 4
#define WEAPON_FIRE_TYPE_CAMERA 5

static stock YSI_g_InvalidReturn = -1;

static stock YSI_g_WeaponModels[47] = {
	0,331,333,334,335,336,
    337,338,339,341,321,321,
	323,324,325,326,342,343,
	344,YSI_g_InvalidReturn,
	YSI_g_InvalidReturn,
	YSI_g_InvalidReturn
	,346,347,348,349,
	350,351,352,353,355,356,
	372,357,358,359,360,361,
	362,363,364,365,366,367,
   	368,369,371
	
};

static stock YSI_g_WeaponSlots[47] = {
	0,0,1,1,1,1,1,1,1,1,
	10,10,10,10,10,10,8,8,8,
	YSI_g_InvalidReturn,
	YSI_g_InvalidReturn,
	YSI_g_InvalidReturn,
	2,2,2,3,3,3,4,
	4,5,5,4,6,6,7,7,7,7,8,12,
	9,9,9,11,11,11
};

static stock YSI_g_WeaponFireType[47] = {
    WEAPON_FIRE_TYPE_MELEE, //{"Fist", 0, 0, 0 },
    WEAPON_FIRE_TYPE_MELEE, //{"Brass Knuckles", 1, 0, 331 },
    WEAPON_FIRE_TYPE_MELEE, //{"Golf Club", 2, 1, 333 },
    WEAPON_FIRE_TYPE_MELEE, //{"Nightstick", 3, 1, 334 },
    WEAPON_FIRE_TYPE_MELEE, //{"Knife", 4, 1, 335 },
    WEAPON_FIRE_TYPE_MELEE, //{"Baseball Bat", 5, 1, 336 },
    WEAPON_FIRE_TYPE_MELEE, //{"Shovel", 6, 1, 337 },
    WEAPON_FIRE_TYPE_MELEE, //{"Pool Cue", 7, 1, 338 },
    WEAPON_FIRE_TYPE_MELEE, //{"Katana", 8, 1, 339 },
    WEAPON_FIRE_TYPE_MELEE, //{"Chainsaw", 9, 1, 341 },
    WEAPON_FIRE_TYPE_MELEE, //{"Double-ended Dildo", 10, 10, 321 },
    WEAPON_FIRE_TYPE_MELEE, //{"Dildo", 11, 10, 321 },
    WEAPON_FIRE_TYPE_MELEE, //{"Vibrator", 12, 10, 323 },
    WEAPON_FIRE_TYPE_MELEE, //{"Silver Vibrator", 13, 10, 324 },
    WEAPON_FIRE_TYPE_MELEE, //{"Flowers", 14, 10, 325 },
    WEAPON_FIRE_TYPE_MELEE, //{"Cane", 15, 10, 326 },
    WEAPON_FIRE_TYPE_PROJECTILE, //{"Grenade", 16, 8, 342 },
    WEAPON_FIRE_TYPE_PROJECTILE, //{"Tear Gas", 17, 8, 343 },
    WEAPON_FIRE_TYPE_PROJECTILE, //{"Molotov Cocktail", 18, 8, 344 },
    YSI_g_InvalidReturn, //{"No gun", 19, -1, 0 },
    YSI_g_InvalidReturn, //{"No gun", 20, -1, 0 },
    YSI_g_InvalidReturn, //{"No gun", 21, -1, 0 },
    WEAPON_FIRE_TYPE_INSTANT_HIT, //{"Colt .45", 22, 2, 346 },
    WEAPON_FIRE_TYPE_INSTANT_HIT, //{"Silenced Colt .45", 23, 2, 347 },
    WEAPON_FIRE_TYPE_INSTANT_HIT, //{"Desert Eagle", 24, 2, 348 },
    WEAPON_FIRE_TYPE_INSTANT_HIT, //{"Shotgun", 25, 3, 349 },
    WEAPON_FIRE_TYPE_INSTANT_HIT, //{"Sawnoff Shotgun", 26, 3, 350 },
    WEAPON_FIRE_TYPE_INSTANT_HIT, //{"Combat Shotgun", 27, 3, 351 },
    WEAPON_FIRE_TYPE_INSTANT_HIT, //{"Micro SMG", 28, 4, 352 },
    WEAPON_FIRE_TYPE_INSTANT_HIT, //{"MP5", 29, 4, 353 },
    WEAPON_FIRE_TYPE_INSTANT_HIT, //{"AK47", 30, 5, 355 },
    WEAPON_FIRE_TYPE_INSTANT_HIT, //{"M4", 31, 5, 356 },
    WEAPON_FIRE_TYPE_INSTANT_HIT, //{"Tec-9", 32, 4, 372 },
    WEAPON_FIRE_TYPE_INSTANT_HIT, //{"Country Rifle", 33, 6, 357 },
    WEAPON_FIRE_TYPE_INSTANT_HIT, //{"Sniper Rifle", 34, 6, 358 },
    WEAPON_FIRE_TYPE_PROJECTILE, //{"RPG", 35, 7, 359 },
    WEAPON_FIRE_TYPE_PROJECTILE, //{"HS Rocket", 36, 7, 360 },
    WEAPON_FIRE_TYPE_AREA_EFFECT, //{"Flamethrower", 37, 7, 361 },
    WEAPON_FIRE_TYPE_INSTANT_HIT, //{"Minigun", 38, 7, 362 },
    WEAPON_FIRE_TYPE_PROJECTILE, //{"Satchel Charge", 39, 8, 363 },
    WEAPON_FIRE_TYPE_USE, //{"Detonator", 40, 12, 364 },
    WEAPON_FIRE_TYPE_AREA_EFFECT, //{"Spraycan", 41, 9, 365 },
    WEAPON_FIRE_TYPE_AREA_EFFECT, //{"Fire Extinguisher", 42, 9, 366 },
    WEAPON_FIRE_TYPE_AREA_CAMERA, //{"Camera", 43, 9, 367 },
    WEAPON_FIRE_TYPE_AREA_USE, //{"Night Vis Goggles", 44, 11, 368 },
    WEAPON_FIRE_TYPE_AREA_USE, //{"Thermal Goggles", 45, 11, 369 },
    WEAPON_FIRE_TYPE_AREA_USE  //{"Parachute", 46, 11, 371 }
};

//P:D(Weapon_IsValid(weaponid));
//#define Weapon_IsValid(%0) (%0>=1 && %0<=18 || %0>=21 && %0<=46)
stock bool:Weapon_IsValid(weaponid)
{
	return (weaponid >= 1 && weaponid <= 18 || weaponid >= 21 && weaponid <= 46);
}

stock bool:Weapon_IsAssaultRifle(weaponid)
{
	switch(weaponid)
	{
		case 30, 31: return true;
	}
	return false;
}

stock bool:Weapon_IsPistol(weaponid)
{
	switch(weaponid)
	{
		case 22, 23, 24: return true;
	}
	return false;
}

stock bool:Weapon_IsShotgun(weaponid)
{
	switch(weaponid)
	{
		case 25, 26, 27: return true;
	}
	return false;
}

stock bool:Weapon_IsSubmachineGun(weaponid)
{
	switch(weaponid)
	{
		case 28, 29, 32: return true;
	}
	return false;
}

stock bool:Weapon_IsRifle(weaponid)
{
	switch(weaponid)
	{
		case 33, 34: return true;
	}
	return false;
}

//P:D(Weapon_GetSlot(weaponid));
stock Weapon_GetSlot(weaponid)
{
	return YSI_g_WeaponSlots[weaponid];
}

//P:D(Weapon_GetModelID(weaponid));
stock Weapon_GetModelID(weaponid)
{
	return YSI_g_WeaponModels[weaponid];
}

stock Weapon_GetIDFromModelID(modelid)
{
	for(new i; i < 47; i++)
	{
		if(YSI_g_WeaponModels[i] == modelid)
		{
			return i;
		}
	}
	return -1;
}
