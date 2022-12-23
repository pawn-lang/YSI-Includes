#if defined _INC_y_vehicledata
	#endinput
#endif
#define _INC_y_vehicledata

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
	Portions created by the Initial Developer are Copyright (c) 2022
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

#define Vehicle_IsCar(%0)          (_Vehicle_Is(Car        , %0))
#define Vehicle_IsTruck(%0)        (_Vehicle_Is(Truck      , %0))
#define Vehicle_IsVan(%0)          (_Vehicle_Is(Van        , %0))
#define Vehicle_IsFire(%0)         (_Vehicle_Is(Fire       , %0))
#define Vehicle_IsPolice(%0)       (_Vehicle_Is(Police     , %0))
#define Vehicle_IsFBI(%0)          (_Vehicle_Is(FBI        , %0))
#define Vehicle_IsSWAT(%0)         (_Vehicle_Is(SWAT       , %0))
#define Vehicle_IsMilitary(%0)     (_Vehicle_Is(Military   , %0))
#define Vehicle_IsWeaponised(%0)   (_Vehicle_Is(Weaponised , %0))
#define Vehicle_IsHelicopter(%0)   (_Vehicle_Is(Helicopter , %0))
#define Vehicle_IsBoat(%0)         (_Vehicle_Is(Boat       , %0))
#define Vehicle_IsPlane(%0)        (_Vehicle_Is(Plane      , %0))
#define Vehicle_IsBike(%0)         (_Vehicle_Is(Bike       , %0))
#define Vehicle_IsManual(%0)       (_Vehicle_Is(Manual     , %0))
#define Vehicle_IsAmbulance(%0)    (_Vehicle_Is(Ambulance  , %0))
#define Vehicle_IsTaxi(%0)         (_Vehicle_Is(Taxi       , %0))
#define Vehicle_IsOnWater(%0)      (_Vehicle_Is(OnWater    , %0))
#define Vehicle_IsCoastguard(%0)   (_Vehicle_Is(Coastguard , %0))
#define Vehicle_IsTrain(%0)        (_Vehicle_Is(Train      , %0))
#define Vehicle_IsLS(%0)           (_Vehicle_Is(LS         , %0))
#define Vehicle_IsSF(%0)           (_Vehicle_Is(SF         , %0))
#define Vehicle_IsLV(%0)           (_Vehicle_Is(LV         , %0))
#define Vehicle_IsTank(%0)         (_Vehicle_Is(Tank       , %0))
#define Vehicle_IsFlowerpot(%0)    (_Vehicle_Is(Flowerpot  , %0))
#define Vehicle_IsTransport(%0)    (_Vehicle_Is(Transport  , %0))
#define Vehicle_IsArmed(%0)        (_Vehicle_Is(Armed      , %0))
#define Vehicle_HasNumberPlate(%0) (_Vehicle_Is(NumberPlate, %0))

#define Model_GetCategory(%0)  VIM_GetCategory(Model_ToVIM((%0)))
#define Model_IsValid(%0)      VIM_IsValid(Model_ToVIM((%0)))

#define Model_IsCar(%0)          (_Model_Is(Car        , %0))
#define Model_IsTruck(%0)        (_Model_Is(Truck      , %0))
#define Model_IsVan(%0)          (_Model_Is(Van        , %0))
#define Model_IsFire(%0)         (_Model_Is(Fire       , %0))
#define Model_IsPolice(%0)       (_Model_Is(Police     , %0))
#define Model_IsFBI(%0)          (_Model_Is(FBI        , %0))
#define Model_IsSWAT(%0)         (_Model_Is(SWAT       , %0))
#define Model_IsMilitary(%0)     (_Model_Is(Military   , %0))
#define Model_IsWeaponised(%0)   (_Model_Is(Weaponised , %0))
#define Model_IsHelicopter(%0)   (_Model_Is(Helicopter , %0))
#define Model_IsBoat(%0)         (_Model_Is(Boat       , %0))
#define Model_IsPlane(%0)        (_Model_Is(Plane      , %0))
#define Model_IsBike(%0)         (_Model_Is(Bike       , %0))
#define Model_IsManual(%0)       (_Model_Is(Manual     , %0))
#define Model_IsAmbulance(%0)    (_Model_Is(Ambulance  , %0))
#define Model_IsTaxi(%0)         (_Model_Is(Taxi       , %0))
#define Model_IsOnWater(%0)      (_Model_Is(OnWater    , %0))
#define Model_IsCoastguard(%0)   (_Model_Is(Coastguard , %0))
#define Model_IsTrain(%0)        (_Model_Is(Train      , %0))
#define Model_IsLS(%0)           (_Model_Is(LS         , %0))
#define Model_IsSF(%0)           (_Model_Is(SF         , %0))
#define Model_IsLV(%0)           (_Model_Is(LV         , %0))
#define Model_IsTank(%0)         (_Model_Is(Tank       , %0))
#define Model_IsFlowerpot(%0)    (_Model_Is(Flowerpot  , %0))
#define Model_IsTransport(%0)    (_Model_Is(Transport  , %0))
#define Model_IsArmed(%0)        (_Model_Is(Armed      , %0))
#define Model_HasNumberPlate(%0) (_Model_Is(NumberPlate, %0))

#define VIM_GetCategory(%0)  (YSI_gVehicleFlags[(%0)] & e_VEHICLE_FLAGS_CATEGORY)
#define VIM_IsValid(%0)      (YSI_gVehicleFlags[(%0)] != e_VEHICLE_FLAGS_NONE)

#define VIM_IsCar(%0)          (_VIM_Is(Car        , %0))
#define VIM_IsTruck(%0)        (_VIM_Is(Truck      , %0))
#define VIM_IsVan(%0)          (_VIM_Is(Van        , %0))
#define VIM_IsFire(%0)         (_VIM_Is(Fire       , %0))
#define VIM_IsPolice(%0)       (_VIM_Is(Police     , %0))
#define VIM_IsFBI(%0)          (_VIM_Is(FBI        , %0))
#define VIM_IsSWAT(%0)         (_VIM_Is(SWAT       , %0))
#define VIM_IsMilitary(%0)     (_VIM_Is(Military   , %0))
#define VIM_IsWeaponised(%0)   (_VIM_Is(Weaponised , %0))
#define VIM_IsHelicopter(%0)   (_VIM_Is(Helicopter , %0))
#define VIM_IsBoat(%0)         (_VIM_Is(Boat       , %0))
#define VIM_IsPlane(%0)        (_VIM_Is(Plane      , %0))
#define VIM_IsBike(%0)         (_VIM_Is(Bike       , %0))
#define VIM_IsManual(%0)       (_VIM_Is(Manual     , %0))
#define VIM_IsAmbulance(%0)    (_VIM_Is(Ambulance  , %0))
#define VIM_IsTaxi(%0)         (_VIM_Is(Taxi       , %0))
#define VIM_IsOnWater(%0)      (_VIM_Is(OnWater    , %0))
#define VIM_IsCoastguard(%0)   (_VIM_Is(Coastguard , %0))
#define VIM_IsTrain(%0)        (_VIM_Is(Train      , %0))
#define VIM_IsLS(%0)           (_VIM_Is(LS         , %0))
#define VIM_IsSF(%0)           (_VIM_Is(SF         , %0))
#define VIM_IsLV(%0)           (_VIM_Is(LV         , %0))
#define VIM_IsTank(%0)         (_VIM_Is(Tank       , %0))
#define VIM_IsFlowerpot(%0)    (_VIM_Is(Flowerpot  , %0))
#define VIM_IsTransport(%0)    (_VIM_Is(Transport  , %0))
#define VIM_IsArmed(%0)        (_VIM_Is(Armed      , %0))
#define VIM_HasNumberPlate(%0) (_VIM_Is(NumberPlate, %0))

#define Vehicle_GetVIM(%0) (Model_ToVIM(GetVehicleModel((%0))))
#define Model_ToVIM(%0) (VIM:(_Model_Validate(%0)))

#define Vehicle_Name(%0) (VIM_Name(Vehicle_GetVIM(%0)))
#define Model_Name(%0) (VIM_Name(Model_ToVIM(%0)))
#define VIM_Name(%0) (YSI_gVehicleNames[(%0)])

native y_vehicledata_StrUnpack(dest[], const src[], size = sizeof (dest)) = strunpack;
// When using the `GetName` functions with an optional length the call becomes:
// `y_vehicledata_StrUnpack(dest, size, src)`, which is the wrong order for
// `strunpack`.  This correctly rearranges the parameters.
#define y_vehicledata_StrUnpack(%0,%1,%2) strunpack(%0,%2,%1)

// Vehicle_GetName(vehicleid, dest[], size = sizeof (dest));
#define Vehicle_GetName(%0,%1) y_vehicledata_StrUnpack(%1,VIM_Name(Vehicle_GetVIM(%0)))
// Model_GetName(modelid, dest[], size = sizeof (dest));
#define Model_GetName(%0,%1) y_vehicledata_StrUnpack(%1,VIM_Name(Model_ToVIM(%0)))
// VIM_GetName(VIM:vim, dest[], size = sizeof (dest));
#define VIM_GetName(%0,%1) y_vehicledata_StrUnpack(%1,YSI_gVehicleNames[(%0)])

#define Vehicle_TopSpeed(%0) (VIM_TopSpeed(Vehicle_GetVIM(%0)))
#define Model_TopSpeed(%0) (VIM_TopSpeed(Model_ToVIM(%0)))
#define VIM_TopSpeed(%0) (YSI_gVehicleTopSpeed[(%0)])

#define Vehicle_Seats(%0) (VIM_Seats(Vehicle_GetVIM(%0)))
#define Model_Seats(%0) (VIM_Seats(Model_ToVIM(%0)))
#define VIM_Seats(%0) (YSI_gVehicleSeats[(%0)])

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

enum e_VEHICLE_FLAGS:(<<= 1)
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
	e_VEHICLE_FLAGS_Truck,         // 0x00000020
	e_VEHICLE_FLAGS_Van,           // 0x00000040
	e_VEHICLE_FLAGS_Fire,          // 0x00000080
	e_VEHICLE_FLAGS_Police,        // 0x00000100
	e_VEHICLE_FLAGS_FBI,           // 0x00000200
	e_VEHICLE_FLAGS_SWAT,          // 0x00000400
	e_VEHICLE_FLAGS_Military,      // 0x00000800
	e_VEHICLE_FLAGS_Weaponised,    // 0x00001000
	e_VEHICLE_FLAGS_Helicopter,    // 0x00002000
	e_VEHICLE_FLAGS_Boat,          // 0x00004000
	e_VEHICLE_FLAGS_Plane,         // 0x00008000
	e_VEHICLE_FLAGS_Bike,          // 0x00010000
	e_VEHICLE_FLAGS_Manual,        // 0x00020000
	e_VEHICLE_FLAGS_Ambulance,     // 0x00040000
	e_VEHICLE_FLAGS_Taxi,          // 0x00080000
	e_VEHICLE_FLAGS_OnWater,       // 0x00100000
	e_VEHICLE_FLAGS_Coastguard,    // 0x00200000
	e_VEHICLE_FLAGS_Train,         // 0x00400000
	e_VEHICLE_FLAGS_LS,            // 0x00800000
	e_VEHICLE_FLAGS_SF,            // 0x01000000
	e_VEHICLE_FLAGS_LV,            // 0x02000000
	e_VEHICLE_FLAGS_Tank,          // 0x04000000
	e_VEHICLE_FLAGS_Flowerpot,     // 0x08000000
	e_VEHICLE_FLAGS_Transport,     // 0x10000000
	e_VEHICLE_FLAGS_Armed,         // 0x20000000
	e_VEHICLE_FLAGS_NumberPlate    // 0x40000000
}

// These macros just prepend `e_VEHICLE_FLAGS_` to every entry inside
// `_VEHICLE_FLAGS` so that:
//
//    _VEHICLE_FLAGS<Saloon | Car>
//
// Becomes:
//
//    e_VEHICLE_FLAGS_Saloon | e_VEHICLE_FLAGS_Car
//
// Which is more correct but less readable.
#define _VEHICLE_FLAGS<%0> e_VEHICLE_FLAGS_NONE| CAT_%0| END|
#define e_VEHICLE_FLAGS_NONE|%0\32;%1| e_VEHICLE_FLAGS_%1|e_VEHICLE_FLAGS_NONE|
#define e_VEHICLE_FLAGS_END|e_VEHICLE_FLAGS_NONE| e_VEHICLE_FLAGS_NONE

#define _Model_Validate(%0) ((clamp((%0), VIM_MODEL_MIN, VIM_MODEL_MAX) - VIM_MODEL_MIN))

#define _Vehicle_Is(%9,%0) _VIM_Is(%9, Vehicle_GetVIM((%0)))
#define _Model_Is(%9,%0) _VIM_Is(%9, Model_ToVIM((%0)))
#define _VIM_Is(%9,%0) (bool:(YSI_gVehicleFlags[(%0)] & e_VEHICLE_FLAGS_%9))

/*

This comment can be collapsed - it pushes line numbers down to match models.














































This comment can be collapsed - it pushes line numbers down to match models.

*/

#if defined __line
	#if __line != 391
		#error Model IDs not aligned with line numbers.
	#endif
#endif

stock
	e_VEHICLE_FLAGS:YSI_gVehicleFlags[VIM:VIM_MODEL_COUNT] =
		{
			e_VEHICLE_FLAGS_NONE, // This should remain on line 399 forever.
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
			_VEHICLE_FLAGS<Helicopter  | Helicopter | Weaponised | Military | Armed>,
			_VEHICLE_FLAGS<Saloon      | Car       >,
			_VEHICLE_FLAGS<Public      | Truck      | Police>,
			_VEHICLE_FLAGS<Unique      | Truck     >,
			_VEHICLE_FLAGS<Sport       | Car       >,
			_VEHICLE_FLAGS<Boat        | Boat       | Weaponised | Police | Armed>,
			_VEHICLE_FLAGS<Public      | Transport >,
			_VEHICLE_FLAGS<Public      | Weaponised | Military | Tank | Armed>,
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
			_VEHICLE_FLAGS<Helicopter  | Boat       | Helicopter | OnWater  | Armed>,
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
			_VEHICLE_FLAGS<RC          | Plane     | Armed>,
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
			_VEHICLE_FLAGS<Airplane    | Plane     | Armed>,
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
			_VEHICLE_FLAGS<Airplane    | Plane      | Weaponised | Military | Armed>,
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
			_VEHICLE_FLAGS<Trailer     | Truck     >,
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
			__COMPILER_PACK"",
			__COMPILER_PACK"Landstalker",
			__COMPILER_PACK"Bravura",
			__COMPILER_PACK"Buffalo",
			__COMPILER_PACK"Linerunner",
			__COMPILER_PACK"Perennial",
			__COMPILER_PACK"Sentinel",
			__COMPILER_PACK"Dumper",
			__COMPILER_PACK"Firetruck",
			__COMPILER_PACK"Trashmaster",
			__COMPILER_PACK"Stretch",
			__COMPILER_PACK"Manana",
			__COMPILER_PACK"Infernus",
			__COMPILER_PACK"Voodoo",
			__COMPILER_PACK"Pony",
			__COMPILER_PACK"Mule",
			__COMPILER_PACK"Cheetah",
			__COMPILER_PACK"Ambulance",
			__COMPILER_PACK"Leviathan",
			__COMPILER_PACK"Moonbeam",
			__COMPILER_PACK"Esperanto",
			__COMPILER_PACK"Taxi",
			__COMPILER_PACK"Washington",
			__COMPILER_PACK"Bobcat",
			__COMPILER_PACK"Mr Whoopee",
			__COMPILER_PACK"BF Injection",
			__COMPILER_PACK"Hunter",
			__COMPILER_PACK"Premier",
			__COMPILER_PACK"Enforcer",
			__COMPILER_PACK"Securicar",
			__COMPILER_PACK"Banshee",
			__COMPILER_PACK"Predator",
			__COMPILER_PACK"Bus",
			__COMPILER_PACK"Rhino",
			__COMPILER_PACK"Barracks",
			__COMPILER_PACK"Hotknife",
			__COMPILER_PACK"Article Trailer",
			__COMPILER_PACK"Previon",
			__COMPILER_PACK"Coach",
			__COMPILER_PACK"Cabbie",
			__COMPILER_PACK"Stallion",
			__COMPILER_PACK"Rumpo",
			__COMPILER_PACK"RC Bandit",
			__COMPILER_PACK"Romero",
			__COMPILER_PACK"Packer",
			__COMPILER_PACK"Monster",
			__COMPILER_PACK"Admiral",
			__COMPILER_PACK"Squalo",
			__COMPILER_PACK"Seasparrow",
			__COMPILER_PACK"Pizzaboy",
			__COMPILER_PACK"Tram",
			__COMPILER_PACK"Article Trailer 2",
			__COMPILER_PACK"Turismo",
			__COMPILER_PACK"Speeder",
			__COMPILER_PACK"Reefer",
			__COMPILER_PACK"Tropic",
			__COMPILER_PACK"Flatbed",
			__COMPILER_PACK"Yankee",
			__COMPILER_PACK"Caddy",
			__COMPILER_PACK"Solair",
			__COMPILER_PACK"Topfun Van (Berkley's RC)",
			__COMPILER_PACK"Skimmer",
			__COMPILER_PACK"PCJ-600",
			__COMPILER_PACK"Faggio",
			__COMPILER_PACK"Freeway",
			__COMPILER_PACK"RC Baron",
			__COMPILER_PACK"RC Raider",
			__COMPILER_PACK"Glendale",
			__COMPILER_PACK"Oceanic",
			__COMPILER_PACK"Sanchez",
			__COMPILER_PACK"Sparrow",
			__COMPILER_PACK"Patriot",
			__COMPILER_PACK"Quad",
			__COMPILER_PACK"Coastguard",
			__COMPILER_PACK"Dinghy",
			__COMPILER_PACK"Hermes",
			__COMPILER_PACK"Sabre",
			__COMPILER_PACK"Rustler",
			__COMPILER_PACK"ZR-350",
			__COMPILER_PACK"Walton",
			__COMPILER_PACK"Regina",
			__COMPILER_PACK"Comet",
			__COMPILER_PACK"BMX",
			__COMPILER_PACK"Burrito",
			__COMPILER_PACK"Camper",
			__COMPILER_PACK"Marquis",
			__COMPILER_PACK"Baggage",
			__COMPILER_PACK"Dozer",
			__COMPILER_PACK"Maverick",
			__COMPILER_PACK"SAN News Maverick",
			__COMPILER_PACK"Rancher",
			__COMPILER_PACK"FBI Rancher",
			__COMPILER_PACK"Virgo",
			__COMPILER_PACK"Greenwood",
			__COMPILER_PACK"Jetmax",
			__COMPILER_PACK"Hotring Racer",
			__COMPILER_PACK"Sandking",
			__COMPILER_PACK"Blista Compact",
			__COMPILER_PACK"Police Maverick",
			__COMPILER_PACK"Boxville",
			__COMPILER_PACK"Benson",
			__COMPILER_PACK"Mesa",
			__COMPILER_PACK"RC Goblin",
			__COMPILER_PACK"Hotring Racer \"A\"",
			__COMPILER_PACK"Hotring Racer \"B\"",
			__COMPILER_PACK"Bloodring Banger",
			__COMPILER_PACK"Rancher Lure",
			__COMPILER_PACK"Super GT",
			__COMPILER_PACK"Elegant",
			__COMPILER_PACK"Journey",
			__COMPILER_PACK"Bike",
			__COMPILER_PACK"Mountain Bike",
			__COMPILER_PACK"Beagle",
			__COMPILER_PACK"Cropduster",
			__COMPILER_PACK"Stuntplane",
			__COMPILER_PACK"Tanker",
			__COMPILER_PACK"Roadtrain",
			__COMPILER_PACK"Nebula",
			__COMPILER_PACK"Majestic",
			__COMPILER_PACK"Buccaneer",
			__COMPILER_PACK"Shamal",
			__COMPILER_PACK"Hydra",
			__COMPILER_PACK"FCR-900",
			__COMPILER_PACK"NRG-500",
			__COMPILER_PACK"HPV1000",
			__COMPILER_PACK"Cement Truck",
			__COMPILER_PACK"Towtruck",
			__COMPILER_PACK"Fortune",
			__COMPILER_PACK"Cadrona",
			__COMPILER_PACK"FBI Truck",
			__COMPILER_PACK"Willard",
			__COMPILER_PACK"Forklift",
			__COMPILER_PACK"Tractor",
			__COMPILER_PACK"Combine Harvester",
			__COMPILER_PACK"Feltzer",
			__COMPILER_PACK"Remington",
			__COMPILER_PACK"Slamvan",
			__COMPILER_PACK"Blade",
			__COMPILER_PACK"Freight (Train)",
			__COMPILER_PACK"Brownstreak (Train)",
			__COMPILER_PACK"Vortex",
			__COMPILER_PACK"Vincent",
			__COMPILER_PACK"Bullet",
			__COMPILER_PACK"Clover",
			__COMPILER_PACK"Sadler",
			__COMPILER_PACK"Firetruck LA",
			__COMPILER_PACK"Hustler",
			__COMPILER_PACK"Intruder",
			__COMPILER_PACK"Primo",
			__COMPILER_PACK"Cargobob",
			__COMPILER_PACK"Tampa",
			__COMPILER_PACK"Sunrise",
			__COMPILER_PACK"Merit",
			__COMPILER_PACK"Utility Van",
			__COMPILER_PACK"Nevada",
			__COMPILER_PACK"Yosemite",
			__COMPILER_PACK"Windsor",
			__COMPILER_PACK"Monster \"A\"",
			__COMPILER_PACK"Monster \"B\"",
			__COMPILER_PACK"Uranus",
			__COMPILER_PACK"Jester",
			__COMPILER_PACK"Sultan",
			__COMPILER_PACK"Stratum",
			__COMPILER_PACK"Elegy",
			__COMPILER_PACK"Raindance",
			__COMPILER_PACK"RC Tiger",
			__COMPILER_PACK"Flash",
			__COMPILER_PACK"Tahoma",
			__COMPILER_PACK"Savanna",
			__COMPILER_PACK"Bandito",
			__COMPILER_PACK"Freight Flat Trailer (Train)",
			__COMPILER_PACK"Streak Trailer (Train)",
			__COMPILER_PACK"Kart",
			__COMPILER_PACK"Mower",
			__COMPILER_PACK"Dune",
			__COMPILER_PACK"Sweeper",
			__COMPILER_PACK"Broadway",
			__COMPILER_PACK"Tornado",
			__COMPILER_PACK"AT400",
			__COMPILER_PACK"DFT-30",
			__COMPILER_PACK"Huntley",
			__COMPILER_PACK"Stafford",
			__COMPILER_PACK"BF-400",
			__COMPILER_PACK"Newsvan",
			__COMPILER_PACK"Tug",
			__COMPILER_PACK"Petrol Trailer",
			__COMPILER_PACK"Emperor",
			__COMPILER_PACK"Wayfarer",
			__COMPILER_PACK"Euros",
			__COMPILER_PACK"Hotdog",
			__COMPILER_PACK"Club",
			__COMPILER_PACK"Freight Box Trailer (Train)",
			__COMPILER_PACK"Article Trailer 3",
			__COMPILER_PACK"Andromada",
			__COMPILER_PACK"Dodo",
			__COMPILER_PACK"RC Cam",
			__COMPILER_PACK"Launch",
			__COMPILER_PACK"Police Car (LSPD)",
			__COMPILER_PACK"Police Car (SFPD)",
			__COMPILER_PACK"Police Car (LVPD)",
			__COMPILER_PACK"Police Ranger",
			__COMPILER_PACK"Picador",
			__COMPILER_PACK"S.W.A.T.",
			__COMPILER_PACK"Alpha",
			__COMPILER_PACK"Phoenix",
			__COMPILER_PACK"Glendale Shit",
			__COMPILER_PACK"Sadler Shit",
			__COMPILER_PACK"Baggage Trailer \"A\"",
			__COMPILER_PACK"Baggage Trailer \"B\"",
			__COMPILER_PACK"Tug Stairs Trailer",
			__COMPILER_PACK"Boxville",
			__COMPILER_PACK"Farm Trailer",
			__COMPILER_PACK"Utility Trailer",
			__COMPILER_PACK""
		},
	YSI_gVehicleTopSpeed[VIM:VIM_MODEL_COUNT] =
		{
			0,
			157,
			147,
			186,
			110,
			133,
			164,
			110,
			148,
			100,
			158,
			129,
			221,
			168,
			110,
			105,
			192,
			154,
			270,
			115,
			149,
			145,
			154,
			140,
			99,
			135,
			270,
			173,
			165,
			157,
			201,
			190,
			130,
			94,
			110,
			167,
			0,
			149,
			158,
			142,
			168,
			136,
			145,
			139,
			126,
			110,
			164,
			270,
			270,
			111,
			0,
			0,
			193,
			270,
			60,
			135,
			157,
			106,
			95,
			157,
			136,
			270,
			160,
			111,
			142,
			145,
			145,
			147,
			140,
			144,
			270,
			157,
			110,
			190,
			190,
			149,
			173,
			270,
			186,
			117,
			140,
			184,
			73,
			156,
			122,
			190,
			99,
			64,
			270,
			270,
			139,
			157,
			149,
			140,
			270,
			214,
			176,
			162,
			270,
			108,
			123,
			140,
			145,
			216,
			216,
			173,
			140,
			179,
			166,
			108,
			79,
			101,
			270,
			270,
			270,
			120,
			142,
			157,
			157,
			164,
			270,
			270,
			160,
			176,
			151,
			130,
			160,
			158,
			149,
			176,
			149,
			60,
			70,
			110,
			167,
			168,
			158,
			173,
			0,
			0,
			270,
			149,
			203,
			164,
			151,
			150,
			147,
			149,
			142,
			270,
			153,
			145,
			157,
			121,
			270,
			144,
			158,
			113,
			113,
			156,
			178,
			169,
			154,
			178,
			270,
			145,
			165,
			160,
			173,
			146,
			0,
			0,
			93,
			60,
			110,
			60,
			158,
			158,
			270,
			130,
			158,
			153,
			151,
			136,
			85,
			0,
			153,
			142,
			165,
			108,
			162,
			0,
			0,
			270,
			270,
			130,
			190,
			175,
			175,
			175,
			158,
			151,
			110,
			169,
			171,
			148,
			152,
			0,
			0,
			0,
			108,
			0,
			0,
			0
		},
	YSI_gVehicleSeats[VIM:VIM_MODEL_COUNT] = 
		{
			4, 
			2, 
			2, 
			2, 
			4, 
			4, 
			1, 
			2, 
			2, 
			4, 
			2, 
			2, 
			2, 
			4, 
			2, 
			2, 
			4, 
			2, 
			4, 
			2, 
			4, 
			2, 
			2, 
			2, 
			2, 
			1, 
			4, 
			4, 
			4, 
			2, 
			1, 
			9, 
			1, 
			2, 
			2, 
			1, 
			2, 
			9, 
			4, 
			2, 
			4, 
			1, 
			2, 
			2, 
			2, 
			4, 
			1, 
			2, 
			1, 
			2, 
			1, 
			2, 
			1, 
			1, 
			1, 
			2, 
			2, 
			2, 
			4, 
			4, 
			2, 
			2, 
			2, 
			2, 
			1, 
			1, 
			4, 
			4, 
			2, 
			2, 
			4, 
			2, 
			1, 
			1, 
			2, 
			2, 
			1, 
			2, 
			2, 
			4, 
			2, 
			1, 
			2, 
			3, 
			1, 
			1, 
			1, 
			4, 
			2, 
			2, 
			4, 
			2, 
			4, 
			1, 
			2, 
			2, 
			2, 
			4, 
			4, 
			2,
			2, 
			1, 
			2, 
			2, 
			2, 
			2, 
			2, 
			4, 
			2, 
			1, 
			1, 
			2, 
			1, 
			1, 
			2, 
			2, 
			4, 
			2, 
			2, 
			1, 
			1, 
			2, 
			2, 
			2, 
			2, 
			2, 
			2, 
			2, 
			2, 
			4, 
			1, 
			1, 
			1, 
			2, 
			2, 
			2, 
			2, 
			2, 
			2, 
			1, 
			4, 
			2, 
			2, 
			2, 
			2, 
			2, 
			4, 
			4, 
			2, 
			2, 
			4, 
			4,
			2, 
			1, 
			2, 
			2, 
			2, 
			2, 
			2, 
			2, 
			4, 
			4, 
			2, 
			2, 
			1, 
			2, 
			4, 
			4, 
			1, 
			1, 
			1, 
			1, 
			1, 
			2, 
			1, 
			2, 
			2, 
			2, 
			2, 
			4, 
			4, 
			2, 
			4, 
			1, 
			1, 
			4, 
			2, 
			2, 
			2, 
			2, 
			1, 
			1, 
			2, 
			2, 
			1, 
			1, 
			4, 
			4, 
			4, 
			2, 
			2, 
			2, 
			2, 
			2, 
			4, 
			2, 
			1, 
			1, 
			1, 
			4, 
			1, 
			1
		};
/*-------------------------------------------------------------------------*//**
 * <param name="vehicleid">The vehicleid to get speed.</param>
 * <returns>
 *   Current vehicle speed.
 * </returns>
 * <remarks>
 *   This function have returns in KM/H.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Vehicle_Speed(vehicleid)
{
	static 
		Float:Vx = 0.0,
		Float:Vy = 0.0,
		Float:Vz = 0.0
	;
	GetVehicleVelocity(vehicleid, Vx, Vy, Vz);
	return floatround(VectorSize(Vx, Vy, Vz) * 136.666667);
}

#undef _VEHICLE_FLAGS
#undef e_VEHICLE_FLAGS_NONE
#undef e_VEHICLE_FLAGS_END

#if defined YSI_TESTS
	#include "..\..\YSI_Core\y_utils"
	#include "y_vehicledata_tests"
#endif

