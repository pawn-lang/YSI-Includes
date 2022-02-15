# Quick Start

Check if the weapon is valid.
```pawn
new bool:validweap = Weapon_IsValid(GetPlayerWeapon(playerid));
```
Get the weapon slot.
```pawn
new slot = Weapon_GetSlot(GetPlayerWeapon(playerid));
```
Get the weapon model ID.
```pawn
new model = Weapon_GetModelID(GetPlayerWeapon(playerid));
```

## Weapon types
Use these to check for weapon types.
```pawn
bool:Weapon_IsAssaultRifle(weaponid)
bool:Weapon_IsPistol(weaponid)
bool:Weapon_IsShotgun(weaponid)
bool:Weapon_IsSubmachineGun(weaponid)
bool:Weapon_IsRifle(weaponid)
```
