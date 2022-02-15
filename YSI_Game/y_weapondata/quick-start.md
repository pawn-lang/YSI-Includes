# Introduction

I have time and again seen code defining properties of vehicles that uses loops or vast chunks of memory, when far far less is needed.  Many of those times I've even explained HOW to do it smaller, but no-one has, so I did.

Thus, I present ***y_vehicledata***.

The include has three prefixes - that is, three groups of functions - `Vehicle_`, `Model_`, and `VIM_`.  All three groups have the same functions, but take different inputs.

## Vehicle_

These functions take a `vehicleid`, i.e. a value returned by `CreateVehicle` or `GetPlayerSurfingVehicleID` etc.

## Model_[/list]

These functions take a `modelid`, i.e. an object as passed to `AddStaticVehicle` or returned by `GetVehicleModel` etc.

## VIM_[/list]

These functions take a special `VIM` variable, that is, one with a tag of `VIM:`.  `VIM` stands for Vehicle Internal Model, and is specific to this include (but others are free to use it if they want).  This is different to normal models in three ways:

* They are always valid.
* They can be used as indexes.
* They have a strong tag to differentiate them.

This second point is very important.  Standard model IDs start at 400 and go up to 611, so if you want to use them to index an array you either need 400 empty slots in the array, or to subtract 400 from the model ID (which is exactly what `VIM`s are).

# Functions

* `Vehicle_GetCategory(vehicleid)` - Return the category of the vehicle, as defined on [the wiki](https://open.mp/docs).  The return values are;

```pawn
CATEGORY_UNKNOWN
CATEGORY_AIRPLANE
CATEGORY_HELICOPTER
CATEGORY_BIKE
CATEGORY_CONVERTIBLE
CATEGORY_INDUSTRIAL
CATEGORY_LOWRIDER
CATEGORY_OFFROAD   // Two
CATEGORY_OFF_ROAD  // versions
CATEGORY_PUBLIC
CATEGORY_SALOON
CATEGORY_SPORT
CATEGORY_STATIONWAGON  // Two
CATEGORY_STATION_WAGON // versions
CATEGORY_BOAT
CATEGORY_TRAILER
CATEGORY_UNIQUE
CATEGORY_RC
```

Some vehicles may seem to fit in to multiple categories, more information on those can be got with the functions below.  These ONLY return data from the wiki.


* `Vehicle_IsValid(vehicleid)` - Checks if this vehicle is valid, by checking that the model is valid.
* `Vehicle_IsCar(vehicleid)` - This function, and those below, return various pieces of data on vehicles.  Several vehicles may have seemingly conflicting data, such as being listed as both a Boat AND a Plane (or Boat and Car for the Vortex).  Check the include for what vehicles have what flags.
* `Vehicle_IsTruck(vehicleid)` - 
* `Vehicle_IsVan(vehicleid)` - 
* `Vehicle_IsFire(vehicleid)` - 
* `Vehicle_IsPolice(vehicleid)` - 
* `Vehicle_IsFBI(vehicleid)` - 
* `Vehicle_IsSWAT(vehicleid)` - 
* `Vehicle_IsMilitary(vehicleid)` - 
* `Vehicle_IsWeaponised(vehicleid)` - Any vehicle that can "fire" something (including water).
* `Vehicle_IsHelicopter(vehicleid)` - 
* `Vehicle_IsBoat(vehicleid)` - 
* `Vehicle_IsPlane(vehicleid)` - 
* `Vehicle_IsBike(vehicleid)` - 
* `Vehicle_IsManual(vehicleid)` - This refers to pedal power, not stick-shift.
* `Vehicle_IsAmbulance(vehicleid)` - 
* `Vehicle_IsTaxi(vehicleid)` - 
* `Vehicle_IsOnWater(vehicleid)` - Vehicles not in `CATEGORY_BOAT` that can go on water.
* `Vehicle_IsCoastguard(vehicleid)` - 
* `Vehicle_IsTrain(vehicleid)` - Trailers and engines.
* `Vehicle_IsLS(vehicleid)` - For city-specific police vehicles.
* `Vehicle_IsSF(vehicleid)` - For city-specific police vehicles.
* `Vehicle_IsLV(vehicleid)` - For city-specific police vehicles.
* `Vehicle_IsTank(vehicleid)` - 
* `Vehicle_IsFlowerpot(vehicleid)` - 
* `Vehicle_IsTransport(vehicleid)` - 
* `Vehicle_GetName(vehicleid)` - Returns a 32 character packed string of the vehicle's name.


Equivalents exist for `Model_`, taking a modelid instead of a vehicleid - replace the `Vehicle_` prefix with `Model_`.

# VIM Conversion

Equivalents to all the above functions also exist for `VIM:` tagged variables - replace the `Vehicle_` prefix with `VIM_`.

There are two ways to get a `VIM:` variable - from a vehicleid or from a modelid:

```pawn
new
	VIM:vimFromVehicleID = Vehicle_GetVIM(vehicleid),
	VIM:vimFromModelID = Model_ToVIM(vehicleid),
```

Note the difference in `Get` and `To` - this is by design, as models are closer to VIMs than vehicleids are.

So why use these instead?  They just save a level of conversion:

```pawn
#define Vehicle_IsPoliceCar(%0) (Vehicle_IsCar(%0) && Vehicle_IsPolice(%0))
```

That is all fine, but internally calls several functions twice (including `GetVehicleModel`).  This is slightly better:

```pawn
#define Model_IsPoliceCar(%0) (Model_IsCar(%0) && Model_IsPolice(%0))
```

But that still has to do the "- 400" subtraction discussed earlier (and check that the result is valid).

Using VIM functions you can do the conversion and bounds checks once, then use the result far more efficiently:

```pawn
#define VIM_IsPoliceCar(%0) (VIM_IsCar(%0) && VIM_IsPolice(%0))

new
	VIM:vim = Vehicle_GetVIM(vehicleid);
if (VIM_IsPoliceCar(vim) || VIM_IsSWAT(vim))
{
	// Whatever.
}
```

