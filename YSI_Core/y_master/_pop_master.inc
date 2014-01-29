#if AUTO_INCLUDE_GUARD
	#undef _inc__pop_master
#endif

#if _YSIM_PUSH_INDEX < 1
	#define MASTER 0
	#endinput
#elseif _YSIM_PUSH_INDEX == 1
	#define MASTER _YSIM_STACK_SLOT_0
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 0
	#endinput
#elseif _YSIM_PUSH_INDEX == 2
	#define MASTER _YSIM_STACK_SLOT_1
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 1
	#endinput
#elseif _YSIM_PUSH_INDEX == 3
	#define MASTER _YSIM_STACK_SLOT_2
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 2
	#endinput
#elseif _YSIM_PUSH_INDEX == 4
	#define MASTER _YSIM_STACK_SLOT_3
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 3
	#endinput
#elseif _YSIM_PUSH_INDEX == 5
	#define MASTER _YSIM_STACK_SLOT_4
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 4
	#endinput
#elseif _YSIM_PUSH_INDEX == 6
	#define MASTER _YSIM_STACK_SLOT_5
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 5
	#endinput
#elseif _YSIM_PUSH_INDEX == 7
	#define MASTER _YSIM_STACK_SLOT_6
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 6
	#endinput
#elseif _YSIM_PUSH_INDEX == 8
	#define MASTER _YSIM_STACK_SLOT_7
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 7
	#endinput
#elseif _YSIM_PUSH_INDEX == 9
	#define MASTER _YSIM_STACK_SLOT_8
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 8
	#endinput
#elseif _YSIM_PUSH_INDEX == 10
	#define MASTER _YSIM_STACK_SLOT_9
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 9
	#endinput
#elseif _YSIM_PUSH_INDEX == 11
	#define MASTER _YSIM_STACK_SLOT_10
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 10
	#endinput
#elseif _YSIM_PUSH_INDEX == 12
	#define MASTER _YSIM_STACK_SLOT_11
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 11
	#endinput
#elseif _YSIM_PUSH_INDEX == 13
	#define MASTER _YSIM_STACK_SLOT_12
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 12
	#endinput
#elseif _YSIM_PUSH_INDEX == 14
	#define MASTER _YSIM_STACK_SLOT_13
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 13
	#endinput
#elseif _YSIM_PUSH_INDEX == 15
	#define MASTER _YSIM_STACK_SLOT_14
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 14
	#endinput
#elseif _YSIM_PUSH_INDEX == 16
	#define MASTER _YSIM_STACK_SLOT_15
	#undef _YSIM_PUSH_INDEX
	#define _YSIM_PUSH_INDEX 15
	#endinput
#endif
#error y_master MASTER stack impossibility.

