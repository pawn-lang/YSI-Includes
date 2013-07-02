#undef _inc__push_master

// This is purely a stack, but it is all in the pre-processor, so is
// unfortunately vastly more complex (or at least long) than it would be
// otherwise.  We need to COPY the values, not just reference them - that's
// where the long code code in, and the apparent repetition.

#if !defined _MASTER
	#endinput
#endif

#if defined _YSIM_PUSH_INDEX
	#if _YSIM_PUSH_INDEX < 1
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 1
		#if defined _YSIM_STACK_SLOT_0
			#undef _YSIM_STACK_SLOT_0
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_0 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_0 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_0 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_0 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_0 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_0 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_0 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_0 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_0 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_0 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_0 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_0 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_0 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_0 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_0 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_0 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_0 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_0 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_0 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_0 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_0 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_0 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_0 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_0 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_0 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_0 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 1
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 2
		#if defined _YSIM_STACK_SLOT_1
			#undef _YSIM_STACK_SLOT_1
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_1 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_1 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_1 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_1 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_1 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_1 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_1 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_1 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_1 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_1 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_1 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_1 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_1 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_1 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_1 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_1 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_1 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_1 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_1 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_1 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_1 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_1 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_1 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_1 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_1 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_1 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 2
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 3
		#if defined _YSIM_STACK_SLOT_2
			#undef _YSIM_STACK_SLOT_2
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_2 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_2 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_2 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_2 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_2 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_2 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_2 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_2 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_2 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_2 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_2 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_2 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_2 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_2 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_2 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_2 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_2 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_2 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_2 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_2 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_2 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_2 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_2 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_2 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_2 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_2 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 3
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 4
		#if defined _YSIM_STACK_SLOT_3
			#undef _YSIM_STACK_SLOT_3
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_3 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_3 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_3 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_3 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_3 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_3 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_3 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_3 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_3 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_3 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_3 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_3 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_3 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_3 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_3 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_3 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_3 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_3 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_3 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_3 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_3 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_3 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_3 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_3 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_3 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_3 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 4
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 5
		#if defined _YSIM_STACK_SLOT_4
			#undef _YSIM_STACK_SLOT_4
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_4 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_4 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_4 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_4 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_4 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_4 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_4 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_4 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_4 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_4 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_4 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_4 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_4 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_4 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_4 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_4 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_4 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_4 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_4 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_4 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_4 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_4 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_4 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_4 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_4 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_4 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 5
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 6
		#if defined _YSIM_STACK_SLOT_5
			#undef _YSIM_STACK_SLOT_5
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_5 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_5 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_5 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_5 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_5 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_5 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_5 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_5 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_5 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_5 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_5 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_5 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_5 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_5 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_5 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_5 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_5 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_5 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_5 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_5 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_5 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_5 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_5 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_5 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_5 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_5 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 6
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 7
		#if defined _YSIM_STACK_SLOT_6
			#undef _YSIM_STACK_SLOT_6
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_6 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_6 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_6 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_6 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_6 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_6 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_6 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_6 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_6 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_6 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_6 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_6 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_6 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_6 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_6 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_6 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_6 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_6 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_6 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_6 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_6 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_6 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_6 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_6 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_6 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_6 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 7
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 8
		#if defined _YSIM_STACK_SLOT_7
			#undef _YSIM_STACK_SLOT_7
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_7 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_7 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_7 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_7 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_7 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_7 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_7 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_7 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_7 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_7 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_7 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_7 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_7 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_7 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_7 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_7 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_7 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_7 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_7 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_7 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_7 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_7 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_7 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_7 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_7 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_7 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 8
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 9
		#if defined _YSIM_STACK_SLOT_8
			#undef _YSIM_STACK_SLOT_8
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_8 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_8 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_8 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_8 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_8 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_8 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_8 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_8 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_8 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_8 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_8 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_8 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_8 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_8 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_8 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_8 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_8 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_8 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_8 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_8 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_8 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_8 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_8 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_8 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_8 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_8 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 9
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 10
		#if defined _YSIM_STACK_SLOT_9
			#undef _YSIM_STACK_SLOT_9
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_9 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_9 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_9 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_9 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_9 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_9 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_9 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_9 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_9 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_9 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_9 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_9 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_9 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_9 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_9 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_9 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_9 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_9 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_9 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_9 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_9 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_9 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_9 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_9 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_9 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_9 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 10
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 11
		#if defined _YSIM_STACK_SLOT_10
			#undef _YSIM_STACK_SLOT_10
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_10 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_10 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_10 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_10 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_10 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_10 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_10 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_10 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_10 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_10 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_10 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_10 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_10 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_10 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_10 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_10 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_10 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_10 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_10 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_10 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_10 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_10 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_10 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_10 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_10 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_10 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 11
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 12
		#if defined _YSIM_STACK_SLOT_11
			#undef _YSIM_STACK_SLOT_11
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_11 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_11 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_11 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_11 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_11 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_11 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_11 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_11 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_11 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_11 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_11 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_11 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_11 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_11 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_11 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_11 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_11 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_11 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_11 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_11 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_11 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_11 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_11 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_11 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_11 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_11 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 12
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 13
		#if defined _YSIM_STACK_SLOT_12
			#undef _YSIM_STACK_SLOT_12
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_12 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_12 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_12 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_12 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_12 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_12 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_12 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_12 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_12 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_12 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_12 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_12 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_12 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_12 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_12 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_12 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_12 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_12 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_12 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_12 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_12 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_12 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_12 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_12 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_12 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_12 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 13
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 14
		#if defined _YSIM_STACK_SLOT_13
			#undef _YSIM_STACK_SLOT_13
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_13 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_13 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_13 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_13 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_13 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_13 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_13 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_13 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_13 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_13 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_13 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_13 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_13 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_13 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_13 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_13 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_13 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_13 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_13 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_13 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_13 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_13 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_13 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_13 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_13 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_13 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 14
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 15
		#if defined _YSIM_STACK_SLOT_14
			#undef _YSIM_STACK_SLOT_14
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_14 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_14 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_14 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_14 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_14 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_14 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_14 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_14 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_14 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_14 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_14 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_14 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_14 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_14 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_14 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_14 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_14 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_14 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_14 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_14 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_14 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_14 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_14 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_14 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_14 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_14 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 15
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 16
		#if defined _YSIM_STACK_SLOT_15
			#undef _YSIM_STACK_SLOT_15
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_15 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_15 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_15 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_15 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_15 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_15 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_15 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_15 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_15 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_15 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_15 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_15 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_15 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_15 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_15 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_15 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_15 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_15 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_15 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_15 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_15 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_15 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_15 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_15 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_15 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_15 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 16
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 17
		#if defined _YSIM_STACK_SLOT_16
			#undef _YSIM_STACK_SLOT_16
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_16 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_16 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_16 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_16 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_16 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_16 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_16 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_16 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_16 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_16 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_16 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_16 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_16 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_16 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_16 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_16 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_16 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_16 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_16 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_16 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_16 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_16 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_16 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_16 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_16 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_16 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 17
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 18
		#if defined _YSIM_STACK_SLOT_17
			#undef _YSIM_STACK_SLOT_17
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_17 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_17 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_17 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_17 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_17 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_17 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_17 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_17 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_17 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_17 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_17 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_17 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_17 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_17 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_17 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_17 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_17 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_17 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_17 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_17 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_17 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_17 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_17 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_17 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_17 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_17 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 18
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 19
		#if defined _YSIM_STACK_SLOT_18
			#undef _YSIM_STACK_SLOT_18
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_18 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_18 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_18 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_18 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_18 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_18 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_18 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_18 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_18 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_18 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_18 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_18 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_18 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_18 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_18 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_18 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_18 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_18 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_18 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_18 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_18 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_18 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_18 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_18 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_18 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_18 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 19
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 20
		#if defined _YSIM_STACK_SLOT_19
			#undef _YSIM_STACK_SLOT_19
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_19 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_19 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_19 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_19 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_19 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_19 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_19 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_19 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_19 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_19 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_19 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_19 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_19 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_19 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_19 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_19 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_19 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_19 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_19 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_19 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_19 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_19 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_19 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_19 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_19 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_19 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 20
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 21
		#if defined _YSIM_STACK_SLOT_20
			#undef _YSIM_STACK_SLOT_20
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_20 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_20 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_20 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_20 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_20 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_20 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_20 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_20 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_20 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_20 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_20 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_20 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_20 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_20 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_20 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_20 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_20 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_20 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_20 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_20 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_20 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_20 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_20 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_20 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_20 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_20 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 21
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 22
		#if defined _YSIM_STACK_SLOT_21
			#undef _YSIM_STACK_SLOT_21
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_21 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_21 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_21 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_21 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_21 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_21 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_21 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_21 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_21 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_21 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_21 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_21 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_21 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_21 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_21 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_21 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_21 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_21 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_21 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_21 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_21 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_21 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_21 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_21 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_21 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_21 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 22
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 23
		#if defined _YSIM_STACK_SLOT_22
			#undef _YSIM_STACK_SLOT_22
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_22 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_22 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_22 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_22 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_22 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_22 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_22 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_22 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_22 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_22 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_22 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_22 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_22 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_22 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_22 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_22 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_22 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_22 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_22 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_22 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_22 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_22 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_22 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_22 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_22 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_22 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 23
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 24
		#if defined _YSIM_STACK_SLOT_23
			#undef _YSIM_STACK_SLOT_23
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_23 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_23 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_23 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_23 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_23 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_23 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_23 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_23 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_23 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_23 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_23 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_23 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_23 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_23 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_23 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_23 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_23 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_23 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_23 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_23 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_23 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_23 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_23 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_23 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_23 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_23 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 24
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 25
		#if defined _YSIM_STACK_SLOT_24
			#undef _YSIM_STACK_SLOT_24
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_24 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_24 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_24 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_24 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_24 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_24 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_24 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_24 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_24 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_24 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_24 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_24 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_24 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_24 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_24 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_24 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_24 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_24 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_24 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_24 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_24 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_24 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_24 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_24 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_24 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_24 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 25
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 26
		#if defined _YSIM_STACK_SLOT_25
			#undef _YSIM_STACK_SLOT_25
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_25 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_25 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_25 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_25 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_25 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_25 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_25 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_25 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_25 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_25 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_25 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_25 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_25 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_25 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_25 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_25 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_25 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_25 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_25 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_25 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_25 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_25 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_25 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_25 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_25 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_25 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 26
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 27
		#if defined _YSIM_STACK_SLOT_26
			#undef _YSIM_STACK_SLOT_26
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_26 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_26 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_26 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_26 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_26 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_26 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_26 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_26 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_26 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_26 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_26 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_26 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_26 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_26 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_26 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_26 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_26 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_26 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_26 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_26 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_26 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_26 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_26 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_26 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_26 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_26 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 27
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 28
		#if defined _YSIM_STACK_SLOT_27
			#undef _YSIM_STACK_SLOT_27
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_27 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_27 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_27 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_27 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_27 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_27 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_27 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_27 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_27 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_27 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_27 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_27 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_27 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_27 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_27 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_27 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_27 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_27 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_27 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_27 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_27 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_27 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_27 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_27 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_27 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_27 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 28
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 29
		#if defined _YSIM_STACK_SLOT_28
			#undef _YSIM_STACK_SLOT_28
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_28 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_28 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_28 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_28 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_28 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_28 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_28 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_28 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_28 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_28 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_28 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_28 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_28 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_28 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_28 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_28 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_28 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_28 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_28 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_28 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_28 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_28 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_28 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_28 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_28 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_28 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 29
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 30
		#if defined _YSIM_STACK_SLOT_29
			#undef _YSIM_STACK_SLOT_29
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_29 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_29 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_29 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_29 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_29 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_29 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_29 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_29 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_29 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_29 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_29 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_29 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_29 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_29 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_29 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_29 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_29 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_29 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_29 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_29 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_29 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_29 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_29 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_29 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_29 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_29 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 30
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 31
		#if defined _YSIM_STACK_SLOT_30
			#undef _YSIM_STACK_SLOT_30
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_30 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_30 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_30 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_30 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_30 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_30 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_30 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_30 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_30 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_30 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_30 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_30 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_30 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_30 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_30 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_30 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_30 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_30 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_30 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_30 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_30 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_30 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_30 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_30 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_30 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_30 25
		#endif
	#elseif _YSIM_PUSH_INDEX == 31
		#undef _YSIM_PUSH_INDEX
		#define _YSIM_PUSH_INDEX 32
		#if defined _YSIM_STACK_SLOT_31
			#undef _YSIM_STACK_SLOT_31
		#endif
		#if     _MASTER == 0
			#define _YSIM_STACK_SLOT_31 0
		#elseif _MASTER == 1
			#define _YSIM_STACK_SLOT_31 1
		#elseif _MASTER == 2
			#define _YSIM_STACK_SLOT_31 2
		#elseif _MASTER == 3
			#define _YSIM_STACK_SLOT_31 3
		#elseif _MASTER == 4
			#define _YSIM_STACK_SLOT_31 4
		#elseif _MASTER == 5
			#define _YSIM_STACK_SLOT_31 5
		#elseif _MASTER == 6
			#define _YSIM_STACK_SLOT_31 6
		#elseif _MASTER == 7
			#define _YSIM_STACK_SLOT_31 7
		#elseif _MASTER == 8
			#define _YSIM_STACK_SLOT_31 8
		#elseif _MASTER == 9
			#define _YSIM_STACK_SLOT_31 9
		#elseif _MASTER == 10
			#define _YSIM_STACK_SLOT_31 10
		#elseif _MASTER == 11
			#define _YSIM_STACK_SLOT_31 11
		#elseif _MASTER == 12
			#define _YSIM_STACK_SLOT_31 12
		#elseif _MASTER == 13
			#define _YSIM_STACK_SLOT_31 13
		#elseif _MASTER == 14
			#define _YSIM_STACK_SLOT_31 14
		#elseif _MASTER == 15
			#define _YSIM_STACK_SLOT_31 15
		#elseif _MASTER == 16
			#define _YSIM_STACK_SLOT_31 16
		#elseif _MASTER == 17
			#define _YSIM_STACK_SLOT_31 17
		#elseif _MASTER == 18
			#define _YSIM_STACK_SLOT_31 18
		#elseif _MASTER == 19
			#define _YSIM_STACK_SLOT_31 19
		#elseif _MASTER == 20
			#define _YSIM_STACK_SLOT_31 20
		#elseif _MASTER == 21
			#define _YSIM_STACK_SLOT_31 21
		#elseif _MASTER == 22
			#define _YSIM_STACK_SLOT_31 22
		#elseif _MASTER == 23
			#define _YSIM_STACK_SLOT_31 23
		#elseif _MASTER == 24
			#define _YSIM_STACK_SLOT_31 24
		#elseif _MASTER == 25
			#define _YSIM_STACK_SLOT_31 25
		#endif
	#else
		#error y_master _MASTER stack overflow.
	#endif
#else
	#define _YSIM_PUSH_INDEX 1
	#if defined _YSIM_STACK_SLOT_0
		#undef _YSIM_STACK_SLOT_0
	#endif
	#if     _MASTER == 0
		#define _YSIM_STACK_SLOT_0 0
	#elseif _MASTER == 1
		#define _YSIM_STACK_SLOT_0 1
	#elseif _MASTER == 2
		#define _YSIM_STACK_SLOT_0 2
	#elseif _MASTER == 3
		#define _YSIM_STACK_SLOT_0 3
	#elseif _MASTER == 4
		#define _YSIM_STACK_SLOT_0 4
	#elseif _MASTER == 5
		#define _YSIM_STACK_SLOT_0 5
	#elseif _MASTER == 6
		#define _YSIM_STACK_SLOT_0 6
	#elseif _MASTER == 7
		#define _YSIM_STACK_SLOT_0 7
	#elseif _MASTER == 8
		#define _YSIM_STACK_SLOT_0 8
	#elseif _MASTER == 9
		#define _YSIM_STACK_SLOT_0 9
	#elseif _MASTER == 10
		#define _YSIM_STACK_SLOT_0 10
	#elseif _MASTER == 11
		#define _YSIM_STACK_SLOT_0 11
	#elseif _MASTER == 12
		#define _YSIM_STACK_SLOT_0 12
	#elseif _MASTER == 13
		#define _YSIM_STACK_SLOT_0 13
	#elseif _MASTER == 14
		#define _YSIM_STACK_SLOT_0 14
	#elseif _MASTER == 15
		#define _YSIM_STACK_SLOT_0 15
	#elseif _MASTER == 16
		#define _YSIM_STACK_SLOT_0 16
	#elseif _MASTER == 17
		#define _YSIM_STACK_SLOT_0 17
	#elseif _MASTER == 18
		#define _YSIM_STACK_SLOT_0 18
	#elseif _MASTER == 19
		#define _YSIM_STACK_SLOT_0 19
	#elseif _MASTER == 20
		#define _YSIM_STACK_SLOT_0 20
	#elseif _MASTER == 21
		#define _YSIM_STACK_SLOT_0 21
	#elseif _MASTER == 22
		#define _YSIM_STACK_SLOT_0 22
	#elseif _MASTER == 23
		#define _YSIM_STACK_SLOT_0 23
	#elseif _MASTER == 24
		#define _YSIM_STACK_SLOT_0 24
	#elseif _MASTER == 25
		#define _YSIM_STACK_SLOT_0 25
	#endif
#endif

#undef _MASTER
