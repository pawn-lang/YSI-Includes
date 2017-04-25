
remote stock yrt_1(hi);

static stock remote yrt_2(const hi, string:you[], there[], &other, &len = 7);

remote stock yrt_3(hi, string:you[], there[], len)
{
	#pragma unused hi, you, there, len
	// Impl...
	return 99;
}

remote Float:yrt_335(hi, string:you[], there[], len)
{
	#pragma unused hi, you, there, len
	// Impl...
	ASSERT(!strcmp(you, "the string passed"));
	return float(hi);
}

remote stock static void:yrt_4(hi)
{
	#pragma unused hi
}

static remote stock string:yrt_5(hi, const string:you[], there[], tt, &other, const len = 7)
{
	#pragma unused hi, you, there, tt, len
	new str[130];
	str = "Hello World";
	other += 5;
	return str;
}

remote Float:yrt_55(hi, const string:you[], there[], tt, &other, const len = 7)
{
	#pragma unused you, there, tt, len
	other = hi + 5;
	return 5.5;
}

remote stock Float:yrt_6(hi, string:you[], there[], len);

remote static void:yrt_7(&a, &b, c, &d)
{
	a = 8;
	b = a;
	c += d;
	d -= 4;
}

remote stock string:yrt_8();

remote Float:yrt_9();

Test:y_remote_1()
{
	
}

Test:y_remote_2()
{
	new arr[89], oo = sizeof (arr);
	ASSERT(yrt_2(789, "string", arr, oo) == 0);
	ASSERT(oo == sizeof (arr));
}

Test:y_remote_3()
{
	// Impl...
}

Test:y_remote_335()
{
	// Impl...
	new arr[3];
	ASSERT(yrt_335(89, "the string passed", arr, sizeof (arr)) == 89.0);
}

Test:y_remote_4()
{
}

Test:y_remote_5()
{
	new other = 42, arr[] = {5, 6, 7};
	ASSERT(!strcmp("Hello World", yrt_5(10, "hi", arr, sizeof (arr), other)));
	ASSERT(other == 47);
}

Test:y_remote_55()
{
	new other = 42, arr[] = {5, 6, 7};
	ASSERT(yrt_55(10, "hi", arr, sizeof (arr), other) == 5.5);
	ASSERT(other == 15);
}

Test:y_remote_6()
{
	
}

Test:y_remote_7()
{
	new a, b, c = 123, d = 456;
	yrt_7(a, b, c, d);
	ASSERT(a == 8);
	ASSERT(b == 8);
	ASSERT(c == 123);
	ASSERT(d == 452);
}

Test:y_remote_8()
{
	
}

Test:y_remote_9()
{
	X@(_:(55.8));
	ASSERT(yrt_9() == 0.0);
}

