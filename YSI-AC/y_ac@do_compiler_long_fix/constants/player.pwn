/**
 * <summary>The time (in ms) after a player is considered AFK.</summary>
 */
#define AC_AFK_TIME						1500

/**
 * <summary>Maximum ping allowed. Whoever has a bigger ping will be reported as cheater.</summary>
 */
#define AC_MAX_PING						500

/**
 * <summary>Every AC_SYNC_MAX_FAILS fails a cheat alert is triggered.</summary>
 */
#define AC_SYNC_MAX_FAILS				30

/**
 * Player states.
 */
enum _:AC_ePlayerState (<<= 1) {
	AC_psSpawn = 1,						// bitmask  0
	AC_psWasAFK,						// bitmask  1
	AC_psFreeze,						// bitmask  2
	AC_ps03,							// bitmask  3
	AC_ps04,							// bitmask  4
	AC_ps05,							// bitmask  5
	AC_ps06,							// bitmask  6
	AC_ps07,							// bitmask  7
	AC_ps08,							// bitmask  8
	AC_ps09,							// bitmask  9
	AC_ps10,							// bitmask 10
	AC_ps11,							// bitmask 11
	AC_ps12,							// bitmask 12
	AC_ps13,							// bitmask 13
	AC_ps14,							// bitmask 14
	AC_ps15,							// bitmask 15
	AC_ps16,							// bitmask 16
	AC_ps17,							// bitmask 17
	AC_ps18,							// bitmask 18
	AC_ps19,							// bitmask 19
	AC_ps20,							// bitmask 10
	AC_ps21,							// bitmask 21
	AC_ps22,							// bitmask 22
	AC_ps23,							// bitmask 23
	AC_ps24,							// bitmask 24
	AC_ps25,							// bitmask 25
	AC_ps26,							// bitmask 26
	AC_ps27,							// bitmask 27
	AC_ps28,							// bitmask 28
	AC_ps29,							// bitmask 29
	AC_ps30,							// bitmask 30
	AC_ps31,							// bitmask 31
};

/**
 * <summary>Sync types.</summary>
 */
enum _:AC_eSync {
	AC_sHealth,
	AC_sArmour
};
