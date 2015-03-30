/**--------------------------------------------------------------------------**\
                             ====================
                              GTA vehicles data.
                             ====================
Description:
	Basic functions for gathering data on various vehicle models.  Things like
	what sort of vehicle they are and what organisation they belong to.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version
	1.1 (the "License"); you may not use this file except in compliance with
	the License. You may obtain a copy of the License at
	[url]http://www.mozilla.org/MPL/[/url]
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI vehicle data include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
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
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	0.2
Changelog:
	15/03/15:
		Changed clamp ranges.
	01/06/14:
		First version.
Functions:
	Public:
		-
	Core:
		-
	Stock:
		-
	Static:
		-
	Inline:
		-
	API:
		-
Callbacks:
	-
Hooks:
	-
Definitions:
	-
Enums:
	-
Macros:
	-
Keywords:
	-
Tags:
	VIM - Vehicle Internal Modelid.
Variables:
	Global:
		YSI_gVehicleFlags - Data on vehicles.
		YSI_gVehicleNames - Names of vehicles.
	Static:
		-
Commands:
	-
Compile options:
	-
Operators:
	-
Iterators:
	-
\**--------------------------------------------------------------------------**/

#if defined _INC_y_vehicledata
	#endinput
#endif
#define _INC_y_vehicledata

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

#define VEHICLE_MODEL_MIN   (400)
#define VEHICLE_MODEL_MAX   (611)
#define VEHICLE_MODEL_COUNT (VEHICLE_MODEL_MAX - VEHICLE_MODEL_MIN + 1)

#define VIM_MODEL_MIN   (VEHICLE_MODEL_MIN - 1)
#define VIM_MODEL_MAX   (VEHICLE_MODEL_MAX + 1)
#define VIM_MODEL_COUNT (VEHICLE_MODEL_COUNT + 2)

#define CATEGORY_UNKNOWN        e_VEHICLE_FLAGS_CAT_Unknown

#define CATEGORY_AIRPLANE       e_VEHICLE_FLAGS_CAT_Airplane
#define CATEGORY_HELICOPTER     e_VEHICLE_FLAGS_CAT_Helicopter
#define CATEGORY_BIKE           e_VEHICLE_FLAGS_CAT_Bike
#define CATEGORY_CONVERTIBLE    e_VEHICLE_FLAGS_CAT_Convertible
#define CATEGORY_INDUSTRIAL     e_VEHICLE_FLAGS_CAT_Industrial
#define CATEGORY_LOWRIDER       e_VEHICLE_FLAGS_CAT_Lowrider
#define CATEGORY_OFFROAD        e_VEHICLE_FLAGS_CAT_OffRoad
#define CATEGORY_OFF_ROAD       e_VEHICLE_FLAGS_CAT_OffRoad
#define CATEGORY_PUBLIC         e_VEHICLE_FLAGS_CAT_Public
#define CATEGORY_SALOON         e_VEHICLE_FLAGS_CAT_Saloon
#define CATEGORY_SPORT          e_VEHICLE_FLAGS_CAT_Sport
#define CATEGORY_STATIONWAGON   e_VEHICLE_FLAGS_CAT_Station
#define CATEGORY_STATION_WAGON  e_VEHICLE_FLAGS_CAT_Station
#define CATEGORY_BOAT           e_VEHICLE_FLAGS_CAT_Boat
#define CATEGORY_TRAILER        e_VEHICLE_FLAGS_CAT_Trailer
#define CATEGORY_UNIQUE         e_VEHICLE_FLAGS_CAT_Unique
#define CATEGORY_RC             e_VEHICLE_FLAGS_CAT_RC

#define CATEGORY_AIRPLANES      e_VEHICLE_FLAGS_CAT_Airplane
#define CATEGORY_HELICOPTERS    e_VEHICLE_FLAGS_CAT_Helicopter
#define CATEGORY_BIKES          e_VEHICLE_FLAGS_CAT_Bike
#define CATEGORY_CONVERTIBLES   e_VEHICLE_FLAGS_CAT_Convertible
#define CATEGORY_LOWRIDERS      e_VEHICLE_FLAGS_CAT_Lowrider
#define CATEGORY_SALOONS        e_VEHICLE_FLAGS_CAT_Saloon
#define CATEGORY_SPORTS         e_VEHICLE_FLAGS_CAT_Sport
#define CATEGORY_STATIONWAGONS  e_VEHICLE_FLAGS_CAT_Station
#define CATEGORY_STATION_WAGONS e_VEHICLE_FLAGS_CAT_Station
#define CATEGORY_BOATS          e_VEHICLE_FLAGS_CAT_Boat
#define CATEGORY_TRAILERS       e_VEHICLE_FLAGS_CAT_Trailer
#define CATEGORY_UNIQUES        e_VEHICLE_FLAGS_CAT_Unique

#define Vehicle_GetCategory(%0)  VIM_GetCategory(Vehicle_GetVIM(%0))
#define Vehicle_IsValid(%0)      VIM_IsValid(Vehicle_GetVIM(%0))

#define Vehicle_IsCar(%0)        (_Vehicle_Is(Car       , %0))
#define Vehicle_IsTruck(%0)      (_Vehicle_Is(Truck     , %0))
#define Vehicle_IsVan(%0)        (_Vehicle_Is(Van       , %0))
#define Vehicle_IsFire(%0)       (_Vehicle_Is(Fire      , %0))
#define Vehicle_IsPolice(%0)     (_Vehicle_Is(Police    , %0))
#define Vehicle_IsFBI(%0)        (_Vehicle_Is(FBI       , %0))
#define Vehicle_IsSWAT(%0)       (_Vehicle_Is(SWAT      , %0))
#define Vehicle_IsMilitary(%0)   (_Vehicle_Is(Military  , %0))
#define Vehicle_IsWeaponised(%0) (_Vehicle_Is(Weaponised, %0))
#define Vehicle_IsHelicopter(%0) (_Vehicle_Is(Helicopter, %0))
#define Vehicle_IsBoat(%0)       (_Vehicle_Is(Boat      , %0))
#define Vehicle_IsPlane(%0)      (_Vehicle_Is(Plane     , %0))
#define Vehicle_IsBike(%0)       (_Vehicle_Is(Bike      , %0))
#define Vehicle_IsManual(%0)     (_Vehicle_Is(Manual    , %0))
#define Vehicle_IsAmbulance(%0)  (_Vehicle_Is(Ambulance , %0))
#define Vehicle_IsTaxi(%0)       (_Vehicle_Is(Taxi      , %0))
#define Vehicle_IsOnWater(%0)    (_Vehicle_Is(OnWater   , %0))
#define Vehicle_IsCoastguard(%0) (_Vehicle_Is(Coastguard, %0))
#define Vehicle_IsTrain(%0)      (_Vehicle_Is(Train     , %0))
#define Vehicle_IsLS(%0)         (_Vehicle_Is(LS        , %0))
#define Vehicle_IsSF(%0)         (_Vehicle_Is(SF        , %0))
#define Vehicle_IsLV(%0)         (_Vehicle_Is(LV        , %0))
#define Vehicle_IsTank(%0)       (_Vehicle_Is(Tank      , %0))
#define Vehicle_IsFlowerpot(%0)  (_Vehicle_Is(Flowerpot , %0))
#define Vehicle_IsTransport(%0)  (_Vehicle_Is(Transport , %0))

#define Model_GetCategory(%0)  VIM_GetCategory(Model_ToVIM((%0)))
#define Model_IsValid(%0)      VIM_IsValid(Model_ToVIM((%0)))

#define Model_IsCar(%0)        (_Model_Is(Car       , %0))
#define Model_IsTruck(%0)      (_Model_Is(Truck     , %0))
#define Model_IsVan(%0)        (_Model_Is(Van       , %0))
#define Model_IsFire(%0)       (_Model_Is(Fire      , %0))
#define Model_IsPolice(%0)     (_Model_Is(Police    , %0))
#define Model_IsFBI(%0)        (_Model_Is(FBI       , %0))
#define Model_IsSWAT(%0)       (_Model_Is(SWAT      , %0))
#define Model_IsMilitary(%0)   (_Model_Is(Military  , %0))
#define Model_IsWeaponised(%0) (_Model_Is(Weaponised, %0))
#define Model_IsHelicopter(%0) (_Model_Is(Helicopter, %0))
#define Model_IsBoat(%0)       (_Model_Is(Boat      , %0))
#define Model_IsPlane(%0)      (_Model_Is(Plane     , %0))
#define Model_IsBike(%0)       (_Model_Is(Bike      , %0))
#define Model_IsManual(%0)     (_Model_Is(Manual    , %0))
#define Model_IsAmbulance(%0)  (_Model_Is(Ambulance , %0))
#define Model_IsTaxi(%0)       (_Model_Is(Taxi      , %0))
#define Model_IsOnWater(%0)    (_Model_Is(OnWater   , %0))
#define Model_IsCoastguard(%0) (_Model_Is(Coastguard, %0))
#define Model_IsTrain(%0)      (_Model_Is(Train     , %0))
#define Model_IsLS(%0)         (_Model_Is(LS        , %0))
#define Model_IsSF(%0)         (_Model_Is(SF        , %0))
#define Model_IsLV(%0)         (_Model_Is(LV        , %0))
#define Model_IsTank(%0)       (_Model_Is(Tank      , %0))
#define Model_IsFlowerpot(%0)  (_Model_Is(Flowerpot , %0))
#define Model_IsTransport(%0)  (_Model_Is(Transport , %0))

#define VIM_GetCategory(%0)  (YSI_gVehicleFlags[(%0)] & e_VEHICLE_FLAGS_CATEGORY)
#define VIM_IsValid(%0)      (YSI_gVehicleFlags[(%0)] != e_VEHICLE_FLAGS_NONE)

#define VIM_IsCar(%0)        (_VIM_Is(Car       , %0))
#define VIM_IsTruck(%0)      (_VIM_Is(Truck     , %0))
#define VIM_IsVan(%0)        (_VIM_Is(Van       , %0))
#define VIM_IsFire(%0)       (_VIM_Is(Fire      , %0))
#define VIM_IsPolice(%0)     (_VIM_Is(Police    , %0))
#define VIM_IsFBI(%0)        (_VIM_Is(FBI       , %0))
#define VIM_IsSWAT(%0)       (_VIM_Is(SWAT      , %0))
#define VIM_IsMilitary(%0)   (_VIM_Is(Military  , %0))
#define VIM_IsWeaponised(%0) (_VIM_Is(Weaponised, %0))
#define VIM_IsHelicopter(%0) (_VIM_Is(Helicopter, %0))
#define VIM_IsBoat(%0)       (_VIM_Is(Boat      , %0))
#define VIM_IsPlane(%0)      (_VIM_Is(Plane     , %0))
#define VIM_IsBike(%0)       (_VIM_Is(Bike      , %0))
#define VIM_IsManual(%0)     (_VIM_Is(Manual    , %0))
#define VIM_IsAmbulance(%0)  (_VIM_Is(Ambulance , %0))
#define VIM_IsTaxi(%0)       (_VIM_Is(Taxi      , %0))
#define VIM_IsOnWater(%0)    (_VIM_Is(OnWater   , %0))
#define VIM_IsCoastguard(%0) (_VIM_Is(Coastguard, %0))
#define VIM_IsTrain(%0)      (_VIM_Is(Train     , %0))
#define VIM_IsLS(%0)         (_VIM_Is(LS        , %0))
#define VIM_IsSF(%0)         (_VIM_Is(SF        , %0))
#define VIM_IsLV(%0)         (_VIM_Is(LV        , %0))
#define VIM_IsTank(%0)       (_VIM_Is(Tank      , %0))
#define VIM_IsFlowerpot(%0)  (_VIM_Is(Flowerpot , %0))
#define VIM_IsTransport(%0)  (_VIM_Is(Transport , %0))

#define Vehicle_GetVIM(%0) (Model_ToVIM(GetVehicleModel((%0))))
#define Model_ToVIM(%0) (VIM:(_Model_Validate(%0)))

#define Vehicle_Name(%0) (VIM_Name(Vehicle_GetVIM(%0)))
#define Model_Name(%0) (VIM_Name(Model_ToVIM(%0)))
#define VIM_Name(%0) (YSI_gVehicleNames[(%0)])

/*

    88                                                                88  
    88              ,d                                                88  
    88              88                                                88  
    88 8b,dPPYba, MM88MMM ,adPPYba, 8b,dPPYba, 8b,dPPYba,  ,adPPYYba, 88  
    88 88P'   `"8a  88   a8P_____88 88P'   "Y8 88P'   `"8a ""     `Y8 88  
    88 88       88  88   8PP""""""" 88         88       88 ,adPPPPP88 88  
    88 88       88  88,  "8b,   ,aa 88         88       88 88,    ,88 88  
    88 88       88  "Y888 `"Ybbd8"' 88         88       88 `"8bbdP"Y8 88  

*/

enum e_VEHICLE_FLAGS (<<= 1)
{
	// There are 15 categories.
	e_VEHICLE_FLAGS_NONE            = 0,
	e_VEHICLE_FLAGS_CAT_Unknown     = 0,
	e_VEHICLE_FLAGS_CAT_Airplane    = 1,
	e_VEHICLE_FLAGS_CAT_Helicopter  = 2,
	e_VEHICLE_FLAGS_CAT_Bike        = 3,
	e_VEHICLE_FLAGS_CAT_Convertible = 4,
	e_VEHICLE_FLAGS_CAT_Industrial  = 5,
	e_VEHICLE_FLAGS_CAT_Lowrider    = 6,
	e_VEHICLE_FLAGS_CAT_OffRoad     = 7,
	e_VEHICLE_FLAGS_CAT_Public      = 8,
	e_VEHICLE_FLAGS_CAT_Saloon      = 9,
	e_VEHICLE_FLAGS_CAT_Sport       = 10,
	e_VEHICLE_FLAGS_CAT_Station     = 11,
	e_VEHICLE_FLAGS_CAT_Boat        = 12,
	e_VEHICLE_FLAGS_CAT_Trailer     = 13,
	e_VEHICLE_FLAGS_CAT_Unique      = 14,
	e_VEHICLE_FLAGS_CAT_RC          = 15,
	e_VEHICLE_FLAGS_CATEGORY        = 0x0F,
	e_VEHICLE_FLAGS_Car             = 0x10,
	e_VEHICLE_FLAGS_Truck,
	e_VEHICLE_FLAGS_Van,
	e_VEHICLE_FLAGS_Fire,
	e_VEHICLE_FLAGS_Police,
	e_VEHICLE_FLAGS_FBI,
	e_VEHICLE_FLAGS_SWAT,
	e_VEHICLE_FLAGS_Military,
	e_VEHICLE_FLAGS_Weaponised,
	e_VEHICLE_FLAGS_Helicopter,
	e_VEHICLE_FLAGS_Boat,
	e_VEHICLE_FLAGS_Plane,
	e_VEHICLE_FLAGS_Bike,
	e_VEHICLE_FLAGS_Manual,
	e_VEHICLE_FLAGS_Ambulance,
	e_VEHICLE_FLAGS_Taxi,
	e_VEHICLE_FLAGS_OnWater,
	e_VEHICLE_FLAGS_Coastguard,
	e_VEHICLE_FLAGS_Train,
	e_VEHICLE_FLAGS_LS,
	e_VEHICLE_FLAGS_SF,
	e_VEHICLE_FLAGS_LV,
	e_VEHICLE_FLAGS_Tank,
	e_VEHICLE_FLAGS_Flowerpot,
	e_VEHICLE_FLAGS_Transport
}

#define _VEHICLE_FLAGS<%0> e_VEHICLE_FLAGS_NONE| CAT_%0| END|
#define e_VEHICLE_FLAGS_NONE|%0\32;%1| e_VEHICLE_FLAGS_%1|e_VEHICLE_FLAGS_NONE|
#define e_VEHICLE_FLAGS_END|e_VEHICLE_FLAGS_NONE| e_VEHICLE_FLAGS_NONE

#define _Model_Validate(%0) ((clamp((%0), VIM_MODEL_MIN, VIM_MODEL_MAX) - VIM_MODEL_MIN))

#define _Vehicle_Is(%9,%0) _VIM_Is(%9, Vehicle_GetVIM((%0)))
#define _Model_Is(%9,%0) _VIM_Is(%9, Model_ToVIM((%0)))
#define _VIM_Is(%9,%0) (bool:(YSI_gVehicleFlags[(%0)] & e_VEHICLE_FLAGS_%9))

/*

This comment can be collapsed - it pushes line numbers down to match models.



































































*/

stock
	e_VEHICLE_FLAGS:YSI_gVehicleFlags[VIM:VIM_MODEL_COUNT] =
		{
			e_VEHICLE_FLAGS_NONE,
			_VEHICLE_FLAGS<OffRoad     | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Industrial  | Truck     >,
			_VEHICLE_FLAGS<Station     | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Unique      | Truck     >,
			_VEHICLE_FLAGS<Public      | Truck      | Weaponised | Fire>,
			_VEHICLE_FLAGS<Industrial  | Truck     >,
			_VEHICLE_FLAGS<Unique      | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Lowrider    | Car       >,
			_VEHICLE_FLAGS<Industrial  | Van       >,
			_VEHICLE_FLAGS<Industrial  | Van       >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Public      | Van        | Ambulance>,
			_VEHICLE_FLAGS<Helicopter  | Helicopter>,
			_VEHICLE_FLAGS<Station     | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Public      | Car        | Taxi>,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Industrial  | Car       >,
			_VEHICLE_FLAGS<Unique      | Van       >,
			_VEHICLE_FLAGS<OffRoad     | Car       >,
			_VEHICLE_FLAGS<Helicopter  | Helicopter | Weaponised | Military>,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Public      | Truck      | Police>,
			_VEHICLE_FLAGS<Unique      | Truck     >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Boat        | Boat       | Weaponised | Police>,
			_VEHICLE_FLAGS<Public      | Transport >,
			_VEHICLE_FLAGS<Public      | Weaponised | Military | Tank>,
			_VEHICLE_FLAGS<Public      | Truck      | Military>,
			_VEHICLE_FLAGS<Unique      | Car       >,
			_VEHICLE_FLAGS<Trailer     | Truck     >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Public      | Transport >,
			_VEHICLE_FLAGS<Public      | Car        | Taxi>,
			_VEHICLE_FLAGS<Convertible | Car       >,
			_VEHICLE_FLAGS<Industrial  | Van       >,
			_VEHICLE_FLAGS<RC          | Car       >,
			_VEHICLE_FLAGS<Unique      | Car       >,
			_VEHICLE_FLAGS<Industrial  | Truck     >,
			_VEHICLE_FLAGS<OffRoad     | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Boat        | Boat      >,
			_VEHICLE_FLAGS<Helicopter  | Boat       | Helicopter | OnWater>,
			_VEHICLE_FLAGS<Bike        | Bike      >,
			_VEHICLE_FLAGS<Unique      | Train     >,
			_VEHICLE_FLAGS<Trailer     | Truck     >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Boat        | Boat      >,
			_VEHICLE_FLAGS<Boat        | Boat      >,
			_VEHICLE_FLAGS<Boat        | Boat      >,
			_VEHICLE_FLAGS<Industrial  | Truck     >,
			_VEHICLE_FLAGS<Industrial  | Van       >,
			_VEHICLE_FLAGS<Unique      | Car       >,
			_VEHICLE_FLAGS<Station     | Car       >,
			_VEHICLE_FLAGS<Industrial  | Van       >,
			_VEHICLE_FLAGS<Airplane    | Boat       | Plane | OnWater>,
			_VEHICLE_FLAGS<Bike        | Bike      >,
			_VEHICLE_FLAGS<Bike        | Bike      >,
			_VEHICLE_FLAGS<Bike        | Bike      >,
			_VEHICLE_FLAGS<RC          | Plane     >,
			_VEHICLE_FLAGS<RC          | Helicopter>,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Bike        | Bike      >,
			_VEHICLE_FLAGS<Helicopter  | Helicopter>,
			_VEHICLE_FLAGS<OffRoad     | Car        | Military>,
			_VEHICLE_FLAGS<Bike        | Bike       | Car       >,
			_VEHICLE_FLAGS<Boat        | Boat       | Coastguard>,
			_VEHICLE_FLAGS<Boat        | Boat      >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Airplane    | Plane     >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Industrial  | Car       >,
			_VEHICLE_FLAGS<Station     | Car       >,
			_VEHICLE_FLAGS<Convertible | Car       >,
			_VEHICLE_FLAGS<Bike        | Bike       | Manual>,
			_VEHICLE_FLAGS<Industrial  | Van       >,
			_VEHICLE_FLAGS<Unique      | Transport >,
			_VEHICLE_FLAGS<Boat        | Boat      >,
			_VEHICLE_FLAGS<Unique      | Car       >,
			_VEHICLE_FLAGS<Unique      | Truck     >,
			_VEHICLE_FLAGS<Helicopter  | Helicopter>,
			_VEHICLE_FLAGS<Helicopter  | Helicopter>,
			_VEHICLE_FLAGS<OffRoad     | Car       >,
			_VEHICLE_FLAGS<Public      | Car        | FBI>,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Boat        | Boat      >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<OffRoad     | Car       >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Helicopter  | Helicopter | Police>,
			_VEHICLE_FLAGS<Industrial  | Van       >,
			_VEHICLE_FLAGS<Industrial  | Van       >,
			_VEHICLE_FLAGS<OffRoad     | Car       >,
			_VEHICLE_FLAGS<RC          | Helicopter>,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<OffRoad     | Car       >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Unique      | Transport >,
			_VEHICLE_FLAGS<Bike        | Bike       | Manual>,
			_VEHICLE_FLAGS<Bike        | Bike       | Manual>,
			_VEHICLE_FLAGS<Airplane    | Plane     >,
			_VEHICLE_FLAGS<Airplane    | Plane     >,
			_VEHICLE_FLAGS<Airplane    | Plane     >,
			_VEHICLE_FLAGS<Industrial  | Truck     >,
			_VEHICLE_FLAGS<Industrial  | Truck     >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Airplane    | Plane     >,
			_VEHICLE_FLAGS<Airplane    | Plane      | Weaponised | Military>,
			_VEHICLE_FLAGS<Bike        | Bike      >,
			_VEHICLE_FLAGS<Bike        | Bike      >,
			_VEHICLE_FLAGS<Public      | Bike       | Police>,
			_VEHICLE_FLAGS<Industrial  | Truck     >,
			_VEHICLE_FLAGS<Unique      | Truck     >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Public      | Truck      | FBI >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Unique     >,
			_VEHICLE_FLAGS<Industrial >,
			_VEHICLE_FLAGS<Unique     >,
			_VEHICLE_FLAGS<Convertible | Car       >,
			_VEHICLE_FLAGS<Lowrider    | Car       >,
			_VEHICLE_FLAGS<Lowrider    | Car       >,
			_VEHICLE_FLAGS<Lowrider    | Car       >,
			_VEHICLE_FLAGS<Unique      | Train     >,
			_VEHICLE_FLAGS<Unique      | Train     >,
			_VEHICLE_FLAGS<Unique      | Boat       | Car | OnWater>,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Industrial  | Car       >,
			_VEHICLE_FLAGS<Public      | Truck      | Weaponised | Fire>,
			_VEHICLE_FLAGS<Unique      | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Helicopter  | Helicopter>,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Industrial  | Van       >,
			_VEHICLE_FLAGS<Airplane    | Plane     >,
			_VEHICLE_FLAGS<Industrial  | Car       >,
			_VEHICLE_FLAGS<Convertible | Car       >,
			_VEHICLE_FLAGS<OffRoad     | Car       >,
			_VEHICLE_FLAGS<OffRoad     | Car       >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Station     | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Helicopter  | Helicopter>,
			_VEHICLE_FLAGS<RC          | Weaponised | Tank>,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Lowrider    | Car       >,
			_VEHICLE_FLAGS<Lowrider    | Car       >,
			_VEHICLE_FLAGS<OffRoad     | Car       >,
			_VEHICLE_FLAGS<Trailer     | Train     >,
			_VEHICLE_FLAGS<Trailer     | Train     >,
			_VEHICLE_FLAGS<Unique      | Car       >,
			_VEHICLE_FLAGS<Unique      | Car       >,
			_VEHICLE_FLAGS<OffRoad    >,
			_VEHICLE_FLAGS<Unique     >,
			_VEHICLE_FLAGS<Lowrider    | Car       >,
			_VEHICLE_FLAGS<Lowrider    | Car       >,
			_VEHICLE_FLAGS<Airplane    | Plane     >,
			_VEHICLE_FLAGS<Industrial  | Truck     >,
			_VEHICLE_FLAGS<OffRoad     | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Bike        | Bike      >,
			_VEHICLE_FLAGS<Industrial  | Van       >,
			_VEHICLE_FLAGS<Unique     >,
			_VEHICLE_FLAGS<Trailer     | Truck     >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Bike        | Bike      >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Unique      | Van       >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Trailer     | Train     >,
			_VEHICLE_FLAGS<Trailer     | Train     >,
			_VEHICLE_FLAGS<Airplane    | Plane     >,
			_VEHICLE_FLAGS<Airplane    | Plane     >,
			_VEHICLE_FLAGS<RC          | Flowerpot >,
			_VEHICLE_FLAGS<Boat        | Boat      >,
			_VEHICLE_FLAGS<Public      | Car        | Police | LS>,
			_VEHICLE_FLAGS<Public      | Car        | Police | SF>,
			_VEHICLE_FLAGS<Public      | Car        | Police | LV>,
			_VEHICLE_FLAGS<Public      | Car        | Police>,
			_VEHICLE_FLAGS<Industrial  | Car       >,
			_VEHICLE_FLAGS<Public      | Truck      | Weaponised | Police | SWAT>,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Industrial  | Car       >,
			_VEHICLE_FLAGS<Trailer    >,
			_VEHICLE_FLAGS<Trailer    >,
			_VEHICLE_FLAGS<Trailer    >,
			_VEHICLE_FLAGS<Industrial  | Van       >,
			_VEHICLE_FLAGS<Trailer    >,
			_VEHICLE_FLAGS<Trailer    >,
			e_VEHICLE_FLAGS_NONE
		},
	YSI_gVehicleNames[VIM:VIM_MODEL_COUNT][32 char] =
		{
			!"",
			!"Landstalker",
			!"Bravura",
			!"Buffalo",
			!"Linerunner",
			!"Perenniel",
			!"Sentinel",
			!"Dumper",
			!"Firetruck",
			!"Trashmaster",
			!"Stretch",
			!"Manana",
			!"Infernus",
			!"Voodoo",
			!"Pony",
			!"Mule",
			!"Cheetah",
			!"Ambulance",
			!"Leviathan",
			!"Moonbeam",
			!"Esperanto",
			!"Taxi",
			!"Washington",
			!"Bobcat",
			!"Mr Whoopee",
			!"BF Injection",
			!"Hunter",
			!"Premier",
			!"Enforcer",
			!"Securicar",
			!"Banshee",
			!"Predator",
			!"Bus",
			!"Rhino",
			!"Barracks",
			!"Hotknife",
			!"Article Trailer",
			!"Previon",
			!"Coach",
			!"Cabbie",
			!"Stallion",
			!"Rumpo",
			!"RC Bandit",
			!"Romero",
			!"Packer",
			!"Monster",
			!"Admiral",
			!"Squallo",
			!"Seasparrow",
			!"Pizzaboy",
			!"Tram",
			!"Article Trailer 2",
			!"Turismo",
			!"Speeder",
			!"Reefer",
			!"Tropic",
			!"Flatbed",
			!"Yankee",
			!"Caddy",
			!"Solair",
			!"Topfun Van (Berkley's RC)",
			!"Skimmer",
			!"PCJ-600",
			!"Faggio",
			!"Freeway",
			!"RC Baron",
			!"RC Raider",
			!"Glendale",
			!"Oceanic",
			!"Sanchez",
			!"Sparrow",
			!"Patriot",
			!"Quad",
			!"Coastguard",
			!"Dinghy",
			!"Hermes",
			!"Sabre",
			!"Rustler",
			!"ZR-350",
			!"Walton",
			!"Regina",
			!"Comet",
			!"BMX",
			!"Burrito",
			!"Camper",
			!"Marquis",
			!"Baggage",
			!"Dozer",
			!"Maverick",
			!"SAN News Maverick",
			!"Rancher",
			!"FBI Rancher",
			!"Virgo",
			!"Greenwood",
			!"Jetmax",
			!"Hotring Racer",
			!"Sandking",
			!"Blista Compact",
			!"Police Maverick",
			!"Boxville",
			!"Benson",
			!"Mesa",
			!"RC Goblin",
			!"Hotring Racer",
			!"Hotring Racer",
			!"Bloodring Banger",
			!"Rancher",
			!"Super GT",
			!"Elegant",
			!"Journey",
			!"Bike",
			!"Mountain Bike",
			!"Beagle",
			!"Cropduster",
			!"Stuntplane",
			!"Tanker",
			!"Roadtrain",
			!"Nebula",
			!"Majestic",
			!"Buccaneer",
			!"Shamal",
			!"Hydra",
			!"FCR-900",
			!"NRG-500",
			!"HPV1000",
			!"Cement Truck",
			!"Towtruck",
			!"Fortune",
			!"Cadrona",
			!"FBI Truck",
			!"Willard",
			!"Forklift",
			!"Tractor",
			!"Combine Harvester",
			!"Feltzer",
			!"Remington",
			!"Slamvan",
			!"Blade",
			!"Freight (Train)",
			!"Brownstreak (Train)",
			!"Vortex",
			!"Vincent",
			!"Bullet",
			!"Clover",
			!"Sadler",
			!"Firetruck LA",
			!"Hustler",
			!"Intruder",
			!"Primo",
			!"Cargobob",
			!"Tampa",
			!"Sunrise",
			!"Merit",
			!"Utility Van",
			!"Nevada",
			!"Yosemite",
			!"Windsor",
			!"Monster \"A\"",
			!"Monster \"B\"",
			!"Uranus",
			!"Jester",
			!"Sultan",
			!"Stratum",
			!"Elegy",
			!"Raindance",
			!"RC Tiger",
			!"Flash",
			!"Tahoma",
			!"Savanna",
			!"Bandito",
			!"Freight Flat Trailer (Train)",
			!"Streak Trailer (Train)",
			!"Kart",
			!"Mower",
			!"Dune",
			!"Sweeper",
			!"Broadway",
			!"Tornado",
			!"AT400",
			!"DFT-30",
			!"Huntley",
			!"Stafford",
			!"BF-400",
			!"Newsvan",
			!"Tug",
			!"Petrol Trailer",
			!"Emperor",
			!"Wayfarer",
			!"Euros",
			!"Hotdog",
			!"Club",
			!"Freight Box Trailer (Train)",
			!"Article Trailer 3",
			!"Andromada",
			!"Dodo",
			!"RC Cam",
			!"Launch",
			!"Police Car (LSPD)",
			!"Police Car (SFPD)",
			!"Police Car (LVPD)",
			!"Police Ranger",
			!"Picador",
			!"S.W.A.T.",
			!"Alpha",
			!"Phoenix",
			!"Glendale Shit",
			!"Sadler Shit",
			!"Baggage Trailer \"A\"",
			!"Baggage Trailer \"B\"",
			!"Tug Stairs Trailer",
			!"Boxville",
			!"Farm Trailer",
			!"Utility Trailer",
			!""
		};

#undef _VEHICLE_FLAGS
#undef e_VEHICLE_FLAGS_NONE
#undef e_VEHICLE_FLAGS_END

