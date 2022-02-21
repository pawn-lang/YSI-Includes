# Quick Start

## Weapon validity
In *y_weapondata* there is a function you can check for valid weapons with.
```pawn
new valid = Weapon_IsValid(weaponid);
```
## Weapon fire type
You can use `Weapon_GetFireType` to get a certain weapon's fire type.
```pawn
Weapon_GetFireType(weaponid);
```
It returns one of the fire types shown below, depending on given weapon's ID:
```pawn
WEAPON_FIRE_TYPE_MELEE 
WEAPON_FIRE_TYPE_PROJECTILE 
WEAPON_FIRE_TYPE_INSTANT_HIT 
WEAPON_FIRE_TYPE_AREA_EFFECT 
WEAPON_FIRE_TYPE_USE 
WEAPON_FIRE_TYPE_CAMERA 
```
## Weapon range
Get a certain weapon's minimum range using:
```pawn
Float:Weapon_GetMinRange(weaponid);
```
Or, get its maximum range using:
```pawn
Float:Weapon_GetMaxRange(weaponid);
```
## Ammo information
*y_weapondata* also provides some minimal information about the weapon ammo.
### Ammo names
Get a certain weapon's ammo name using:
```pawn
bool:Weapon_GetAmmoName(weaponid, dest[], size = sizeof (dest));
```
## Animation groups
Get a standard weapon's animation group using:
```pawn
bool:Weapon_GetAnimGroup(weaponid, dest[], size = sizeof (dest));
```
Get a `pro` weapon's animation group using:
```pawn
bool:Weapon_GetProAnimGroup(weaponid, dest[], size = sizeof (dest));
```
## Weapon slots
Get a weapon slot using:
```pawn
Weapon_GetSlot(weaponid);
```
## Models
Get a weapon model ID using:
```pawn
Weapon_GetModelID(weaponid);
```
**TIP:** You can also get a weapon ID from a model ID using:
```pawn
Weapon_GetIDFromModelID(modelid);
```
# Extra information
## Constants
```pawn
#if !defined YSI_WEAPDATA_MAX_STRING_SIZE
	#define YSI_WEAPDATA_MAX_STRING_SIZE (24)
#endif
```
If you want to increase the size, just define `YSI_WEAPDATA_MAX_STRING_SIZE` at the very top of your script code.
## Functions
```pawn
bool:Weapon_IsAssaultRifle
bool:Weapon_IsPistol
bool:Weapon_IsShotgun
bool:Weapon_IsSubmachineGun
bool:Weapon_IsRifle
```
