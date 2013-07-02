/**
 * <summary>Stores a player's game data.</summary>
 */
enum _:AC_ePlayer {

	/**
	 * <summary>Player's last known state.</summary>
	 */
	AC_pState,
	
	/**
	 * <summary>Player's sync status.</summary>
	 */
	AC_pSync,
	
	/**
	 * <summary>Keeps track of player's sync failures.</summary>
	 */
	AC_pSyncFails[AC_eSync],

	/**
	 * <summary>Stores latest FPS measurements.</summary>
	 */
	AC_pFPS[AC_MAX_FPS_INDEX],
	
	/**
	 * <summary>Last FPS index used.</summary>
	 */
	AC_pFPSIndex,

	/**
	 * <summary>The time (in ms) when the player was last updated.</summary>
	 */
	AC_pLastUpdate,

	/**
	 * <summary>Player's health.</summary>
	 */
	Float:AC_pHealth,

	/**
	 * <summary>Player's armour.</summary>
	 */
	Float:AC_pArmour,

	/**
	 * <summary>Player's money.</summary>
	 */
	AC_pMoney,

	/**
	 * <summary>The latest time (in ms) when the player died.</summary>
	 */
	AC_pLastDeath,
	
	/**
	 * <summary>Player's latest known position.</summary>
	 */
	Float:AC_pPos[3],
	
	/**
	 * <summary>Player's latest known velocity.</summary>
	 */
	Float:AC_pVelocity[3],
	
	/**
	 * <summary>Player's weapons (ID and ammo).</summary>
	 * <remarks>Two fields are used instead of a bidimensional array because Pawn doesn't support 4D arrays.</remarks>
	 */
	AC_pWeaponsID[AC_MAX_WEAPON_SLOTS],
	AC_pWeaponsAmmo[AC_MAX_WEAPON_SLOTS],
	
	/**
	 * <summary>Player's special action.</summary>
	 */
	AC_pSpecialAction,
	
};

/**
 * <summary>Stores players' game data.</summary>
 */
stock AC_players[MAX_PLAYERS][AC_ePlayer];
