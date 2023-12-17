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

#define WEAPONDATA_NO_AMMO 	" "
#define WEAPONDATA_45ACP 		".45 ACP"
#define WEAPONDATA_9MM 		"9mm"
#define WEAPONDATA_12GUAGE	"12 Guage"
#define WEAPONDATA_556MM		"5.56mm"
#define WEAPONDATA_762MM		"7.62mm"
#define WEAPONDATA_300MAGNUM	".300 Magnum"
#define WEAPONDATA_ROCKET		"Rocket"
#define WEAPONDATA_INVALID_RETURN -1

#define WEAPON_FIRE_TYPE_MELEE 0
#define WEAPON_FIRE_TYPE_PROJECTILE 1
#define WEAPON_FIRE_TYPE_INSTANT_HIT 2
#define WEAPON_FIRE_TYPE_AREA_EFFECT 3
#define WEAPON_FIRE_TYPE_USE 4
#define WEAPON_FIRE_TYPE_CAMERA 5
//P:D(Weapon_IsValid(weaponid));
//#define Weapon_IsValid(%0) (%0>=1 && %0<=18 || %0>=21 && %0<=46)
stock bool:Weapon_IsValid(weaponid)
{
	return (weaponid >= 1 && weaponid <= 18 || weaponid >= 21 && weaponid <= 46);
}

#if !defined YSI_WEAPDATA_MAX_STRING_SIZE
	#define YSI_WEAPDATA_MAX_STRING_SIZE (24)
#endif

//static stock YSI_g_InvalidReturn = -1;

static stock YSI_g_WeaponModels[47] = {
	0,331,333,
	334,335,336,
	337,338,339,
	341,321,321,
	323,324,325,
	326,342,343,
	344,
	WEAPONDATA_INVALID_RETURN,
	WEAPONDATA_INVALID_RETURN,
	WEAPONDATA_INVALID_RETURN
	,346,347,
	348,349,350,
	351,352,353,
	355,356,372,
	357,358,359,
	360,361,362,
	363,364,365,
	366,367,368,
	369,371	
};

static stock YSI_g_WeaponSlots[47] = {
	0,0,1,1,1,1,1,1,1,1,
	10,10,10,10,10,10,8,8,8,
	WEAPONDATA_INVALID_RETURN,
	WEAPONDATA_INVALID_RETURN,
	WEAPONDATA_INVALID_RETURN,
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
	WEAPONDATA_INVALID_RETURN, //{"No gun", 19, -1, 0 },
	WEAPONDATA_INVALID_RETURN, //{"No gun", 20, -1, 0 },
	WEAPONDATA_INVALID_RETURN, //{"No gun", 21, -1, 0 },
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
	WEAPON_FIRE_TYPE_CAMERA, //{"Camera", 43, 9, 367 },
	WEAPON_FIRE_TYPE_USE, //{"Night Vis Goggles", 44, 11, 368 },
	WEAPON_FIRE_TYPE_USE, //{"Thermal Goggles", 45, 11, 369 },
	WEAPON_FIRE_TYPE_USE  //{"Parachute", 46, 11, 371 }
};

stock Weapon_GetFireType(weaponid)
{
	return Weapon_IsValid(weaponid) ? YSI_g_WeaponFireType[weaponid] : (-1);
}

static stock Float:YSI_g_MinWeaponRange[47] = {
	1.6, //{"Fist", 0, 0, 0 },
	1.6, //{"Brass Knuckles", 1, 0, 331 },
	1.6, //{"Golf Club", 2, 1, 333 },
	1.6, //{"Nightstick", 3, 1, 334 },
	1.6, //{"Knife", 4, 1, 335 },
	1.6, //{"Baseball Bat", 5, 1, 336 },
	1.6, //{"Shovel", 6, 1, 337 },
	1.6, //{"Pool Cue", 7, 1, 338 },
	1.6, //{"Katana", 8, 1, 339 },
	1.6, //{"Chainsaw", 9, 1, 341 },
	1.6, //{"Double-ended Dildo", 10, 10, 321 },
	1.6, //{"Dildo", 11, 10, 321 },
	1.6, //{"Vibrator", 12, 10, 323 },
	1.6, //{"Silver Vibrator", 13, 10, 324 },
	1.6, //{"Flowers", 14, 10, 325 },
	1.6, //{"Cane", 15, 10, 326 },
	40.0, //{"Grenade", 16, 8, 342 },
	40.0, //{"Tear Gas", 17, 8, 343 },
	40.0, //{"Molotov Cocktail", 18, 8, 344 },
	WEAPONDATA_INVALID_RETURN, //{"No gun", 19, -1, 0 },
	WEAPONDATA_INVALID_RETURN, //{"No gun", 20, -1, 0 },
	WEAPONDATA_INVALID_RETURN, //{"No gun", 21, -1, 0 },
	30.0, //{"Colt .45", 22, 2, 346 },
	30.0, //{"Silenced Colt .45", 23, 2, 347 },
	30.0, //{"Desert Eagle", 24, 2, 348 },
	40.0, //{"Shotgun", 25, 3, 349 },
	30.0, //{"Sawnoff Shotgun", 26, 3, 350 },
	40.0, //{"Combat Shotgun", 27, 3, 351 },
	30.0, //{"Micro SMG", 28, 4, 352 },
	40.0, //{"MP5", 29, 4, 353 },
	70.0, //{"AK47", 30, 5, 355 },
	90.0, //{"M4", 31, 5, 356 },
	30.0, //{"Tec-9", 32, 4, 372 },
	100.0, //{"Country Rifle", 33, 6, 357 },
	100.0, //{"Sniper Rifle", 34, 6, 358 },
	40.0, //{"RPG", 35, 7, 359 },
	40.0, //{"HS Rocket", 36, 7, 360 },
	5.1, //{"Flamethrower", 37, 7, 361 },
	75.0, //{"Minigun", 38, 7, 362 },
	40.0, //{"Satchel Charge", 39, 8, 363 },
	25.0, //{"Detonator", 40, 12, 364 },
	6.1, //{"Spraycan", 41, 9, 365 },
	10.1, //{"Fire Extinguisher", 42, 9, 366 },
	100.0, //{"Camera", 43, 9, 367 },
	100.0, //{"Night Vis Goggles", 44, 11, 368 },
	100.0, //{"Thermal Goggles", 45, 11, 369 },
	25.0  //{"Parachute", 46, 11, 371 }
};

stock Float:Weapon_GetMinRange(weaponid)
{
	return Weapon_IsValid(weaponid) ? YSI_g_MinWeaponRange[weaponid] : (-1);
}

static stock Float:YSI_g_MaxWeaponRange[47] = {
	1.6, //{"Fist", 0, 0, 0 },
	1.6, //{"Brass Knuckles", 1, 0, 331 },
	1.6, //{"Golf Club", 2, 1, 333 },
	1.6, //{"Nightstick", 3, 1, 334 },
	1.6, //{"Knife", 4, 1, 335 },
	1.6, //{"Baseball Bat", 5, 1, 336 },
	1.6, //{"Shovel", 6, 1, 337 },
	1.6, //{"Pool Cue", 7, 1, 338 },
	1.6, //{"Katana", 8, 1, 339 },
	1.6, //{"Chainsaw", 9, 1, 341 },
	1.6, //{"Double-ended Dildo", 10, 10, 321 },
	1.6, //{"Dildo", 11, 10, 321 },
	1.6, //{"Vibrator", 12, 10, 323 },
	1.6, //{"Silver Vibrator", 13, 10, 324 },
	1.6, //{"Flowers", 14, 10, 325 },
	1.6, //{"Cane", 15, 10, 326 },
	40.0, //{"Grenade", 16, 8, 342 },
	40.0, //{"Tear Gas", 17, 8, 343 },
	40.0, //{"Molotov Cocktail", 18, 8, 344 },
	WEAPONDATA_INVALID_RETURN, //{"No gun", 19, -1, 0 },
	WEAPONDATA_INVALID_RETURN, //{"No gun", 20, -1, 0 },
	WEAPONDATA_INVALID_RETURN, //{"No gun", 21, -1, 0 },
	35.0, //{"Colt .45", 22, 2, 346 },
	35.0, //{"Silenced Colt .45", 23, 2, 347 },
	35.0, //{"Desert Eagle", 24, 2, 348 },
	40.0, //{"Shotgun", 25, 3, 349 },
	35.0, //{"Sawnoff Shotgun", 26, 3, 350 },
	40.0, //{"Combat Shotgun", 27, 3, 351 },
	35.0, //{"Micro SMG", 28, 4, 352 },
	45.0, //{"MP5", 29, 4, 353 },
	70.0, //{"AK47", 30, 5, 355 },
	90.0, //{"M4", 31, 5, 356 },
	35.0, //{"Tec-9", 32, 4, 372 },
	100.0, //{"Country Rifle", 33, 6, 357 },
	100.0, //{"Sniper Rifle", 34, 6, 358 },
	55.0, //{"RPG", 35, 7, 359 },
	55.0, //{"HS Rocket", 36, 7, 360 },
	5.1, //{"Flamethrower", 37, 7, 361 },
	75.0, //{"Minigun", 38, 7, 362 },
	40.0, //{"Satchel Charge", 39, 8, 363 },
	25.0, //{"Detonator", 40, 12, 364 },
	6.1, //{"Spraycan", 41, 9, 365 },
	10.1, //{"Fire Extinguisher", 42, 9, 366 },
	100.0, //{"Camera", 43, 9, 367 },
	100.0, //{"Night Vis Goggles", 44, 11, 368 },
	100.0, //{"Thermal Goggles", 45, 11, 369 },
	25.0  //{"Parachute", 46, 11, 371 }
};

stock Float:Weapon_GetMaxRange(weaponid)
{
	return Weapon_IsValid(weaponid) ? YSI_g_MaxWeaponRange[weaponid] : (-1);
}

static stock YSI_g_WeaponAmmoNames[47][YSI_WEAPDATA_MAX_STRING_SIZE] = {
	WEAPONDATA_NO_AMMO, //{"Fist", 0, 0, 0 },
	WEAPONDATA_NO_AMMO, //{"Brass Knuckles", 1, 0, 331 },
	WEAPONDATA_NO_AMMO, //{"Golf Club", 2, 1, 333 },
	WEAPONDATA_NO_AMMO, //{"Nightstick", 3, 1, 334 },
	WEAPONDATA_NO_AMMO, //{"Knife", 4, 1, 335 },
	WEAPONDATA_NO_AMMO, //{"Baseball Bat", 5, 1, 336 },
	WEAPONDATA_NO_AMMO, //{"Shovel", 6, 1, 337 },
	WEAPONDATA_NO_AMMO, //{"Pool Cue", 7, 1, 338 },
	WEAPONDATA_NO_AMMO, //{"Katana", 8, 1, 339 },
	WEAPONDATA_NO_AMMO, //{"Chainsaw", 9, 1, 341 },
	WEAPONDATA_NO_AMMO, //{"Double-ended Dildo", 10, 10, 321 },
	WEAPONDATA_NO_AMMO, //{"Dildo", 11, 10, 321 },
	WEAPONDATA_NO_AMMO, //{"Vibrator", 12, 10, 323 },
	WEAPONDATA_NO_AMMO, //{"Silver Vibrator", 13, 10, 324 },
	WEAPONDATA_NO_AMMO, //{"Flowers", 14, 10, 325 },
	WEAPONDATA_NO_AMMO, //{"Cane", 15, 10, 326 },
	WEAPONDATA_NO_AMMO, //{"Grenade", 16, 8, 342 },
	WEAPONDATA_NO_AMMO, //{"Tear Gas", 17, 8, 343 },
	WEAPONDATA_NO_AMMO, //{"Molotov Cocktail", 18, 8, 344 },
	WEAPONDATA_NO_AMMO, //{"No gun", 19, -1, 0 },
	WEAPONDATA_NO_AMMO, //{"No gun", 20, -1, 0 },
	WEAPONDATA_NO_AMMO, //{"No gun", 21, -1, 0 },
	WEAPONDATA_45ACP, //{"Colt .45", 22, 2, 346 },
	WEAPONDATA_45ACP, //{"Silenced Colt .45", 23, 2, 347 },
	WEAPONDATA_45ACP, //{"Desert Eagle", 24, 2, 348 },
	WEAPONDATA_12GUAGE, //{"Shotgun", 25, 3, 349 },
	WEAPONDATA_12GUAGE, //{"Sawnoff Shotgun", 26, 3, 350 },
	WEAPONDATA_12GUAGE, //{"Combat Shotgun", 27, 3, 351 },
	WEAPONDATA_9MM, //{"Micro SMG", 28, 4, 352 },
	WEAPONDATA_9MM, //{"MP5", 29, 4, 353 },
	WEAPONDATA_762MM, //{"AK47", 30, 5, 355 },
	WEAPONDATA_556MM, //{"M4", 31, 5, 356 },
	WEAPONDATA_9MM, //{"Tec-9", 32, 4, 372 },
	WEAPONDATA_762MM, //{"Country Rifle", 33, 6, 357 },
	WEAPONDATA_300MAGNUM, //{"Sniper Rifle", 34, 6, 358 },
	WEAPONDATA_ROCKET, //{"RPG", 35, 7, 359 },
	WEAPONDATA_ROCKET, //{"HS Rocket", 36, 7, 360 },
	WEAPONDATA_NO_AMMO, //{"Flamethrower", 37, 7, 361 },
	WEAPONDATA_762MM, //{"Minigun", 38, 7, 362 },
	WEAPONDATA_NO_AMMO, //{"Satchel Charge", 39, 8, 363 },
	WEAPONDATA_NO_AMMO, //{"Detonator", 40, 12, 364 },
	WEAPONDATA_NO_AMMO, //{"Spraycan", 41, 9, 365 },
	WEAPONDATA_NO_AMMO, //{"Fire Extinguisher", 42, 9, 366 },
	WEAPONDATA_NO_AMMO, //{"Camera", 43, 9, 367 },
	WEAPONDATA_NO_AMMO, //{"Night Vis Goggles", 44, 11, 368 },
	WEAPONDATA_NO_AMMO, //{"Thermal Goggles", 45, 11, 369 },
	WEAPONDATA_NO_AMMO  //{"Parachute", 46, 11, 371 }
};

stock bool:Weapon_GetAmmoName(weaponid, dest[], size = sizeof (dest))
{
	dest[0] = '\0';
    if (Weapon_IsValid(weaponid))
    {
        strcat(dest, YSI_g_WeaponAmmoNames[weaponid], size);
        return true;
    }
    return false;
}

static stock YSI_g_WeaponAnimGroups[47][YSI_WEAPDATA_MAX_STRING_SIZE] = {
	"null", //{"Fist", 0, 0, 0 },
	"null", //{"Brass Knuckles", 1, 0, 331 },
	"null", //{"Golf Club", 2, 1, 333 },
	"null", //{"Nightstick", 3, 1, 334 },
	"stealth_kn", //{"Knife", 4, 1, 335 },
	"null", //{"Baseball Bat", 5, 1, 336 },
	"null", //{"Shovel", 6, 1, 337 },
	"null", //{"Pool Cue", 7, 1, 338 },
	"null", //{"Katana", 8, 1, 339 },
	"null", //{"Chainsaw", 9, 1, 341 },
	"null", //{"Double-ended Dildo", 10, 10, 321 },
	"null", //{"Dildo", 11, 10, 321 },
	"null", //{"Vibrator", 12, 10, 323 },
	"null", //{"Silver Vibrator", 13, 10, 324 },
	"null", //{"Flowers", 14, 10, 325 },
	"null", //{"Cane", 15, 10, 326 },
	"grenade", //{"Grenade", 16, 8, 342 },
	"grenade", //{"Tear Gas", 17, 8, 343 },
	"grenade", //{"Molotov Cocktail", 18, 8, 344 },
	"null", //{"No gun", 19, -1, 0 },
	"null", //{"No gun", 20, -1, 0 },
	"null", //{"No gun", 21, -1, 0 },
	"colt45", //{"Colt .45", 22, 2, 346 },
	"silenced", //{"Silenced Colt .45", 23, 2, 347 },
	"pythonbad", //{"Desert Eagle", 24, 2, 348 },
	"shotgunbad", //{"Shotgun", 25, 3, 349 },
	"sawnoff", //{"Sawnoff Shotgun", 26, 3, 350 },
	"buddy", //{"Combat Shotgun", 27, 3, 351 },
	"colt45", //{"Micro SMG", 28, 4, 352 },
	"uzi", //{"MP5", 29, 4, 353 },
	"rifle", //{"AK47", 30, 5, 355 },
	"rifle", //{"M4", 31, 5, 356 },
	"colt45", //{"Tec-9", 32, 4, 372 },
	"sniper", //{"Country Rifle", 33, 6, 357 },
	"sniper", //{"Sniper Rifle", 34, 6, 358 },
	"rocket", //{"RPG", 35, 7, 359 },
	"rocket", //{"HS Rocket", 36, 7, 360 },
	"flame", //{"Flamethrower", 37, 7, 361 },
	"flame", //{"Minigun", 38, 7, 362 },
	"grenade", //{"Satchel Charge", 39, 8, 363 },
	"null", //{"Detonator", 40, 12, 364 },
	"spraycan", //{"Spraycan", 41, 9, 365 },
	"flame", //{"Fire Extinguisher", 42, 9, 366 },
	"rifle", //{"Camera", 43, 9, 367 },
	"goggles", //{"Night Vis Goggles", 44, 11, 368 },
	"goggles", //{"Thermal Goggles", 45, 11, 369 },
	"null"  //{"Parachute", 46, 11, 371 }
};

stock bool:Weapon_GetAnimGroup(weaponid, dest[], size = sizeof (dest))
{
	dest[0] = '\0';
    if (Weapon_IsValid(weaponid))
    {
        strcat(dest, YSI_g_WeaponAnimGroups[weaponid], size);
        return true;
    }
    return false;
}

static stock YSI_g_WeaponProAnimGroups[47][YSI_WEAPDATA_MAX_STRING_SIZE] = {
	"null", //{"Fist", 0, 0, 0 },
	"null", //{"Brass Knuckles", 1, 0, 331 },
	"null", //{"Golf Club", 2, 1, 333 },
	"null", //{"Nightstick", 3, 1, 334 },
	"stealth_kn", //{"Knife", 4, 1, 335 },
	"null", //{"Baseball Bat", 5, 1, 336 },
	"null", //{"Shovel", 6, 1, 337 },
	"null", //{"Pool Cue", 7, 1, 338 },
	"null", //{"Katana", 8, 1, 339 },
	"null", //{"Chainsaw", 9, 1, 341 },
	"null", //{"Double-ended Dildo", 10, 10, 321 },
	"null", //{"Dildo", 11, 10, 321 },
	"null", //{"Vibrator", 12, 10, 323 },
	"null", //{"Silver Vibrator", 13, 10, 324 },
	"null", //{"Flowers", 14, 10, 325 },
	"null", //{"Cane", 15, 10, 326 },
	"grenade", //{"Grenade", 16, 8, 342 },
	"grenade", //{"Tear Gas", 17, 8, 343 },
	"grenade", //{"Molotov Cocktail", 18, 8, 344 },
	"null", //{"No gun", 19, -1, 0 },
	"null", //{"No gun", 20, -1, 0 },
	"null", //{"No gun", 21, -1, 0 },
	"colt45pro", //{"Colt .45", 22, 2, 346 },
	"silencedpro", //{"Silenced Colt .45", 23, 2, 347 },
	"pythonpro", //{"Desert Eagle", 24, 2, 348 },
	"shotgunpro", //{"Shotgun", 25, 3, 349 },
	"sawnoffpro", //{"Sawnoff Shotgun", 26, 3, 350 },
	"buddypro", //{"Combat Shotgun", 27, 3, 351 },
	"colt45", //{"Micro SMG", 28, 4, 352 },
	"uzipro", //{"MP5", 29, 4, 353 },
	"rifle", //{"AK47", 30, 5, 355 },
	"rifle", //{"M4", 31, 5, 356 },
	"colt45pro", //{"Tec-9", 32, 4, 372 },
	"sniper", //{"Country Rifle", 33, 6, 357 },
	"sniper", //{"Sniper Rifle", 34, 6, 358 },
	"rocket", //{"RPG", 35, 7, 359 },
	"rocket", //{"HS Rocket", 36, 7, 360 },
	"flame", //{"Flamethrower", 37, 7, 361 },
	"flame", //{"Minigun", 38, 7, 362 },
	"grenade", //{"Satchel Charge", 39, 8, 363 },
	"null", //{"Detonator", 40, 12, 364 },
	"spraycan", //{"Spraycan", 41, 9, 365 },
	"flame", //{"Fire Extinguisher", 42, 9, 366 },
	"rifle", //{"Camera", 43, 9, 367 },
	"goggles", //{"Night Vis Goggles", 44, 11, 368 },
	"goggles", //{"Thermal Goggles", 45, 11, 369 },
	"null"  //{"Parachute", 46, 11, 371 }
};

stock bool:Weapon_GetProAnimGroup(weaponid, dest[], size = sizeof (dest))
{
	dest[0] = '\0';
    if (Weapon_IsValid(weaponid))
    {
        strcat(dest, YSI_g_WeaponProAnimGroups[weaponid], size);
        return true;
    }
    return false;
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

stock Weapon_GetSlot(weaponid)
{
	return Weapon_IsValid(weaponid) ? YSI_g_WeaponSlots[weaponid] : (WEAPONDATA_INVALID_RETURN);
}

stock Weapon_GetModelID(weaponid)
{
	return Weapon_IsValid(weaponid) ? YSI_g_WeaponModels[weaponid] : (WEAPONDATA_INVALID_RETURN);
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
	return WEAPONDATA_INVALID_RETURN;
}
