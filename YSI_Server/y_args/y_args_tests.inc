// .\omp-server.exe args -- test moo --opt=7 positional -c:8 -c:9 -c+ "-i=8,9" -i=10 -i:134 --help "this is a long string yeah" a -- the rest go here#
@testinit() y_args()
{
	Args_LazyInit();
}

@test(.group = "y_args") y_args()
{
	new str[32];
	ASSERT(Args_GetStringImpl('\0', "opt", str, sizeof (str)));
	ASSERT_SAME(str, "7");
	ASSERT(Args_GetStringImpl('c', "afsadfd", str, sizeof (str)));
	ASSERT_SAME(str, "+");
	ASSERT(!Args_GetStringImpl('a', "afsadfd", str, sizeof (str)));
	ASSERT_SAME(str, "");
	ASSERT(Args_GetStringImpl('c', "help", str, sizeof (str)));
	ASSERT_SAME(str, "this is a long string yeah");
	ASSERT(Args_GetRest(str, sizeof (str)));
	ASSERT_SAME(str, "the rest go here#");
	ASSERT_EQ(Args_GetIntArray('i', _, str, sizeof (str)), 4);
	ASSERT_EQ(str[0], 8);
	ASSERT_EQ(str[1], 9);
	ASSERT_EQ(str[2], 10);
	ASSERT_EQ(str[3], 134);
	new bool:b;
	ASSERT(Args_GetBool('c', _, b));
	ASSERT(b);
	new i;
	ASSERT(Args_GetInt('i', _, i));
	ASSERT_EQ(i, 134);
}

