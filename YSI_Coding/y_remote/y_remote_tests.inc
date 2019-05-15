TODO(000, "Support localfunc and targetfunc");

REMOTE_FUNC__ stock yrt_1(hi);

REMOTE_FUNC__ stock yrt_3(hi, string:you[], there[], len)
{
	#pragma unused hi, you, there, len
	// Impl...
	return 99;
}

REMOTE_FUNC__ Float:yrt_335(hi, string:you[], there[], len)
{
	#pragma unused hi, you, there, len
	// Impl...
	ASSERT_SAME(you, "the string passed");
	return float(hi);
}

REMOTE_FUNC__ stock static void:yrt_4(hi)
{
	#pragma unused hi
}

REMOTE_FUNC__ static stock string:yrt_5(hi, const string:you[], there[], tt, &other, const len = 7)
{
	//printf("yrt_5 called");
	#pragma unused hi, you, there, tt, len
	new str[144];
	str = "Hello World";
	other += 5;
	return str;
}

REMOTE_FUNC__ stock Float:yrt_6(hi, string:you[], there[], len);

REMOTE_FUNC__ static void:yrt_7(&a, &b, c, &d)
{
	//printf("yrt_7 called");
	a = 8;
	b = a;
	c += d;
	d -= 4;
}

REMOTE_FUNC__ stock string:yrt_8();

TEST__ y_remote_1()
{
	
}

TODO(244, "Allocates too much heap with `len`.");
REMOTE_FUNC__ static stock yrt_2(const hi, string:you[], there[], &other, &len = 7);
REMOTE_FUNC__ static stock string:yrt_2b(const hi, string:you[], there[], &other, &len = 7);

TEST__ y_remote_2()
{
	new arr[89], oo = sizeof (arr);
	ASSERT_ZE(broadcastfunc yrt_2(789, "string", arr, oo));
	ASSERT_ZE(strlen(broadcastfunc yrt_2b(789, "string", arr, oo)));
	ASSERT_EQ(oo, sizeof (arr));
}

TEST__ y_remote_3()
{
	new
		other = 1111111,
		arr[10],
		str[YSI_MAX_STRING];
	str = localfunc yrt_5(5, "string", arr, sizeof (arr), other);
	ASSERT_SAME(str, "Hello World");
	ASSERT_EQ(other, 1111116);
	new
		a = 6789,
		b = 6789,
		c = 6789,
		d = 6789;
	localfunc yrt_7(a, b, c, d);
	ASSERT_EQ(a, 8);
	ASSERT_EQ(b, 8);
	ASSERT_EQ(c, 6789);
	ASSERT_EQ(d, 6785);
}

TEST__ y_remote_335()
{
	// Impl...
	new arr[3];
	ASSERT_EQ(yrt_335(89, "the string passed", arr, sizeof (arr)), 89.0);
}

TEST__ y_remote_4()
{
	new
		other = 1111111,
		arr[10],
		str[YSI_MAX_STRING];
	str = broadcastfunc yrt_5(5, "string", arr, sizeof (arr), other);
	ASSERT_SAME(str, "Hello World");
	ASSERT_EQ(other, 1111116);
	new
		a = 6789,
		b = 6789,
		c = 6789,
		d = 6789;
	broadcastfunc yrt_7(a, b, c, d);
	ASSERT_EQ(a, 8);
	ASSERT_EQ(b, 8);
	ASSERT_EQ(c, 6789);
	ASSERT_EQ(d, 6785);
}

TEST__ y_remote_5()
{
	new other = 42, arr[] = {5, 6, 7};
	ASSERT_SAME(yrt_5(10, "hi", arr, sizeof (arr), other), "Hello World");
	ASSERT_EQ(other, 47);
}

#if __COMPILER_MODIFIED

	REMOTE_FUNC__ Float:yrt_55(hi, const string:you[], there[], tt, &other, const len = 7)
	{
		// Figure out why this fails with the "len" parameter (allocates too much
		// heap data and doesn't fully clear it).
		#pragma unused you, there, tt, len
		other = hi + 5;
		return 5.5;
	}

	TEST__ y_remote_55()
	{
		new other = 42, arr[] = {5, 6, 7};
		ASSERT_EQ(yrt_55(10, "hi", arr, sizeof (arr), other), 5.5);
		ASSERT_EQ(other, 15);
	}

#endif

TEST__ y_remote_6()
{
	
}

TEST__ y_remote_7()
{
	new a, b, c = 123, d = 456;
	yrt_7(a, b, c, d);
	ASSERT_EQ(a, 8);
	ASSERT_EQ(b, 8);
	ASSERT_EQ(c, 123);
	ASSERT_EQ(d, 452);
}

TEST__ y_remote_8()
{
	
}

REMOTE_FUNC__ Float:yrt_9();

TEST__ y_remote_9()
{
	X@(_:(55.8));
	ASSERT_EQ(broadcastfunc yrt_9(), 0.0);
}

