Test:Jagged_Declaration_1()
{
	new Jagged:array[5]<1, 2, 3, 4, 5>;
	ASSERT(jaggedsizeof(array[0]) == 1);
	ASSERT(jaggedsizeof(array[1]) == 2);
	ASSERT(jaggedsizeof(array[2]) == 3);
	ASSERT(jaggedsizeof(array[3]) == 4);
	ASSERT(jaggedsizeof(array[4]) >= 5);
}

Test:Jagged_Declaration_2()
{
	new Jagged:array[10]<1, 2, 3, 4, 5>;
	ASSERT(jaggedsizeof(array[0]) == 1);
	ASSERT(jaggedsizeof(array[1]) == 2);
	ASSERT(jaggedsizeof(array[2]) == 3);
	ASSERT(jaggedsizeof(array[3]) == 4);
	ASSERT(jaggedsizeof(array[4]) == 5);
}

Test:Jagged_Declaration_3()
{
	new Jagged:array[3]<12, 1, 1>;
	ASSERT(jaggedsizeof(array[0]) == 12);
	ASSERT(jaggedsizeof(array[1]) == 1);
	ASSERT(jaggedsizeof(array[2]) >= 1);
}

Test:Jagged_Resize()
{
	new array[3][6];
	Jagged_Resize(array, {0, 3}, {1, 12}, {2, 3});
	ASSERT(jaggedsizeof(array[0]) == 3);
	ASSERT(jaggedsizeof(array[1]) == 12);
	ASSERT(jaggedsizeof(array[2]) >= 3);
}

Test:Jagged_Rearrange_0()
{
	new array[3][6];
	array[0] = { 'h', 'i', '\0', 'h', 'o', 'w' };
	array[1] = { 'a', 'r', 'e', ' ', 'y', 'o' };
	array[2] = { 'u', '?', '\0', 'O', 'K', '\0' };
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are you?"));
	ASSERT(!strcmp(array[2], "u?"));
	Jagged_Resize(array, {0, 3}, {1, 12}, {2, 3});
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are yo"));
	ASSERT(!strcmp(array[2], "u?"));
}

Test:Jagged_Rearrange_1()
{
	new array[3][6];
	array[0] = { 'h', 'i', '\0', 'h', 'o', 'w' };
	array[1] = { 'a', 'r', 'e', ' ', 'y', 'o' };
	array[2] = { 'u', '?', '\0', 'O', 'K', '\0' };
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are you?"));
	ASSERT(!strcmp(array[2], "u?"));
	Jagged_Resize(array, {0, 3}, {1, 5}, {2, 3});
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are yu?"));
	ASSERT(!strcmp(array[2], "u?"));
}

Test:Jagged_Rearrange_2()
{
	new array[3][6];
	array[0] = { 'h', 'i', '\0', 'h', 'o', 'w' };
	array[1] = { 'a', 'r', 'e', ' ', 'y', 'o' };
	array[2] = { 'u', '?', '\0', 'O', 'K', '\0' };
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are you?"));
	ASSERT(!strcmp(array[2], "u?"));
	Jagged_Resize(array, {0, 9}, {1, 6}, {2, 3});
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are you?"));
	ASSERT(!strcmp(array[2], "u?"));
}

Test:Jagged_Rearrange_3()
{
	new array[3][6];
	array[0] = { 'h', 'i', '\0', 'h', 'o', 'w' };
	array[1] = { 'a', 'r', 'e', ' ', 'y', 'o' };
	array[2] = { 'u', '?', '\0', 'O', 'K', '\0' };
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are you?"));
	ASSERT(!strcmp(array[2], "u?"));
	Jagged_Resize(array, {0, 9}, {2, 3});
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are you?"));
	ASSERT(!strcmp(array[2], "u?"));
}

Test:Jagged_Rearrange_4()
{
	new array[3][6];
	array[0] = { 'h', 'i', '\0', 'h', 'o', 'w' };
	array[1] = { 'a', 'r', 'e', ' ', 'y', 'o' };
	array[2] = { 'u', '?', '\0', 'O', 'K', '\0' };
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "are you?"));
	ASSERT(!strcmp(array[2], "u?"));
	Jagged_Move(array, {0, 3}, {1, 12}, {2, 3});
	ASSERT(!strcmp(array[0], "hi"));
	ASSERT(!strcmp(array[1], "howare you?"));
	ASSERT(!strcmp(array[2], "OK"));
}

