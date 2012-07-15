

/*enum E_Y_WEAPONS_DATA
{
	E_Y_WEAPONS_DATA_NEXT
	E_Y_WEAPONS_DATA_LAST
	E_Y_WEAPONS_DATA_SLOT
	E_Y_WEAPONS_DATA_NEXT
}*/

static stock const
	YSI_g_scWeaponSlots[] =
		{
			0,  0,  1,  1,  1,  1,  1,  1,  1,  1,
			10, 10, 10, 10, 10, 10, 8,  8,  8,  2,
			2,  2,  3,  3,  3,  4,  4,  5,  5,  4,
			6,  6,  7,  7,  7,  7,  8,  12, 9,  9,
			9,  11, 11, 11
		};

// Store the ammo, -1 means does not have.
static stock
	YSI_g_sWeapons[MAX_PLAYERS][47 - 3],
	YSI_g_sSlots[MAX_PLAYERS],
	YSI_g_sCurrentSet[MAX_PLAYERS][13],
	PlayerArray:YSI_g_sHasConflict<MAX_PLAYERS>,
	PlayerArray:YSI_g_sHasExtras<MAX_PLAYERS>;

hook OnPlayerConnect(playerid)
{
	// Always have fists.
	YSI_g_sSlots = 1;
	// Have no other weapons though.
	for (new i = 0; i != sizeof (YSI_g_sWeapons[]); ++i)
	{
		YSI_g_sWeapons[playerid][i] = -1;
	}
	for (new i = 0; i != sizeof (YSI_g_sCurrentSet[]); ++i)
	{
		YSI_g_sCurrentSet[playerid][i] = 0;
	}
}

static stock Weapon_CountSlots(playerid)
{
	new
		count = 0,
		slots = YSI_g_sSlots[playerid];
	for (new j = 1; j != (1 << 13); j <<= 1)
	{
		if (slots & j)
		{
			++count;
		}
	}
	return count;
}

static stock Weapon_DoRemove(playerid, weaponid)
{
	new
		w[13],
		a[13];
	// Get existing weapons (minus one).
	for (new i = 0; i != 13; ++i)
	{
		GetPlayerWeaponData(playerid, i, w[i], a[i]);
		if (w[i] == weaponid)
		{
			w[i] = 0;
		}
	}
	// Get the current weapon and reset all.
	new
		s = GetPlayerWeapon(playerid);
	ResetPlayerWeapons(playerid);
	// Restore all weapons except the removed one.
	for (new i = 0; i != 13; ++i)
	{
		if (w[i])
		{
			GivePlayerWeapon(playerid,  w[i], a[i]);
		}
	}
	if (s != weaponid)
	{
		SetPlayerArmedWeapon(playerid, s);
	}
	return 1;
}

static stock Weapon_CheckExtra(playerid)
{
	// Check if we need (or no longer need) extra weapons to detect multiple
	// weapons in the same slot while not having enough weapons naturally to do
	// it cleanly.
	if (PA_Get(YSI_g_sHasExtras, playerid))
	{
		// Has extras already - do we still need them.
		new
			count = 0,
			slots = YSI_g_sSlots[playerid],
			w[13],
			a[13];
		// Get existing weapons (minus one).
		for (new i = 0, j = 1; i != 13; ++i, j <<= 1)
		{
			if (slots & j)
			{
				GetPlayerWeaponData(playerid, i, w[i], a[i]);
				++count;
			}
		}
		if (count < 3)
		{
		}
		else
		{
			// No longer need extras.
			if (
		}
	}
	else
	{
	}
	return 1;
}

static stock Weapon_DoGive(playerid, weaponid, id, ammo)
{
	ammo = max(ammo, 0);
	if (weaponid == WEAPON_SATCHEL)
	{
		// VERY special case - give them two weapons, neither of which are in
		// shared slots.  This means that a) we never need to check for slot
		// conflicts and b) we don't need to check if we need extra hidden
		// weapons to detect changing slots because there will be at least 3
		// slots in use (so remove any extra weapons they may have).
		if (PA_Get(YSI_g_sHasConflict, playerid))
		{
			// Has a conflict.
			if (PA_Get(YSI_g_sHasExtras, playerid))
			{
				// Has extra weapons to make up the difference.
				PA_Vet(YSI_g_sHasExtras, playerid);
				if (YSI_g_sSlots[playerid] & (1 << 10))
				{
					Weapon_DoRemove(playerid, WEAPON_FLOWER);
				}
				else
				{
					Weapon_DoRemove(playerid, WEAPON_FLOWER);
				}
			}
		}
		return 1;
	}
	new
		slot = YSI_g_scWeaponSlots[id];
	if (YSI_g_sWeapons[playerid][id] == -1)
	{
		// Don't already have this weapon.
		YSI_g_sWeapons[playerid][id] = ammo;
		if (YSI_g_sSlots[playerid] & (1 << slot))
		{
			// Already have a different weapon in this slot.
			PA_Let(YSI_g_sHasConflict, playerid);
			// Now we need to work out if we need extra fake slots.
			if (Weapon_CountSlots(playerid) < 3)
			{
				// We need at least three slots for this to work to detect when
				// the player changes weapon in one direction or the other.  One
				// of these will always be slot 0, as that can never be empty.
				// The other COULD be slot 10 or 12, but never both.
				if (YSI_g_sSlots[playerid] & (1 << 10))
				{
					// Give them the detonator (they will have no satchels).
				}
				else
				{
					// 
				}
			}
		}
		else
		{
			// Don't already have a weapon in this slot - just give them it.
			GivePlayerWeapon(playerid, weaponid, ammo);
			YSI_g_sCurrentSet[playerid][slot] = weaponid;
		}
	}
	else
	{
		YSI_g_sWeapons[playerid][id] += ammo;
		if (YSI_g_sCurrentSet[playerid][slot] == weaponid)
		{
			// They are currently holding the weapon, give them more ammo.
			GivePlayerWeapon(playerid, weaponid, ammo);
		}
		// Now we need to work out if we no longer need extra fake slots.
	}
	// Make sure we know there is a weapon in this slot.
	YSI_g_scWeaponSlots[id] |= (1 << slot);
	return 1;
}

stock Weapon_Give(playerid, weaponid, ammo)
{
	if (0 <= weaponid <= 18)
	{
		Weapon_DoGive(playerid, weaponid, weaponid, ammo);
	}
	else if (22 <= weaponid <= 46)
	{
		Weapon_DoGive(playerid, weaponid, weaponid - 3, ammo);
	}
}
