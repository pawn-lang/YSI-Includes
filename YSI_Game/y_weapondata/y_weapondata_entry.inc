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

//P:D(Weapon_IsValid(weaponid));
#define Weapon_IsValid(%0) (%0>=1 && %0<=18 || %0>=21 && %0<=46)

enum E_WEAPON_DATA
{
    Name[24],
    ID,
    Slot,
    Model
}

new YSI_g_WeaponInformation[47][E_WEAPON_DATA] = {
    {"No gun", 0, 0, 0 },
    {"Brass Knuckles", 1, 0, 331 },
    {"Golf Club", 2, 1, 333 },
    {"Nightstick", 3, 1, 334 },
    {"Knife", 4, 1, 335 },
    {"Baseball Bat", 5, 1, 336 },
    {"Shovel", 6, 1, 337 },
    {"Pool Cue", 7, 1, 338 },
    {"Katana", 8, 1, 339 },
    {"Chainsaw", 9, 1, 341 },
    {"Double-ended Dildo", 10, 10, 321 },
    {"Dildo", 11, 10, 321 },
    {"Vibrator", 12, 10, 323 },
    {"Silver Vibrator", 13, 10, 324 },
    {"Flowers", 14, 10, 325 },
    {"Cane", 15, 10, 326 },
    {"Grenade", 16, 8, 342 },
    {"Tear Gas", 17, 8, 343 },
    {"Molotov Cocktail", 18, 8, 344 },
    {"No gun", 19, -1, 0 },
    {"No gun", 20, -1, 0 },
    {"No gun", 21, -1, 0 },
    {"Colt .45", 22, 2, 346 },
    {"Silenced Colt .45", 23, 2, 347 },
    {"Desert Eagle", 24, 2, 348 },
    {"Shotgun", 25, 3, 349 },
    {"Sawnoff Shotgun", 26, 3, 350 },
    {"Combat Shotgun", 27, 3, 351 },
    {"Micro SMG", 28, 4, 352 },
    {"MP5", 29, 4, 353 },
    {"AK47", 30, 5, 355 },
    {"M4", 31, 5, 356 },
    {"Tec-9", 32, 4, 372 },
    {"Country Rifle", 33, 6, 357 },
    {"Sniper Rifle", 34, 6, 358 },
    {"RPG", 35, 7, 359 },
    {"HS Rocket", 36, 7, 360 },
    {"Flamethrower", 37, 7, 361 },
    {"Minigun", 38, 7, 362 },
    {"Satchel Charge", 39, 8, 363 },
    {"Detonator", 40, 12, 364 },
    {"Spraycan", 41, 9, 365 },
    {"Fire Extinguisher", 42, 9, 366 },
    {"Camera", 43, 9, 367 },
    {"Night Vis Goggles", 44, 11, 368 },
    {"Thermal Goggles", 45, 11, 369 },
    {"Parachute", 46, 11, 371 }
};

//P:D(Weapon_GetSlot(weaponid));
stock Weapon_GetSlot(weaponid)
{
	return YSI_g_WeaponInformation[weaponid][Slot];
}

//P:D(Weapon_GetModelID(weaponid));
stock Weapon_GetModelID(weaponid)
{
	return YSI_g_WeaponInformation[weaponid][Model];
}
