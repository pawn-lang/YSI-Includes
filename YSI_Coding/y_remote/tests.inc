TODO(000, "Support localfunc and targetfunc");

remotefunc stock yrt_1(hi);

TODO(244, "Allocates too much heap with `len`.");
remotefunc static stock yrt_2(const hi, string:you[], there[], &other, &len = 7);
remotefunc static stock string:yrt_2b(const hi, string:you[], there[], &other, &len = 7);

remotefunc stock yrt_3(hi, string:you[], there[], len)
{
	#pragma unused hi, you, there, len
	// Impl...
	return 99;
}

remotefunc Float:yrt_335(hi, string:you[], there[], len)
{
	#pragma unused hi, you, there, len
	// Impl...
	ASSERT(!strcmp(you, "the string passed"));
	return float(hi);
}

remotefunc stock static void:yrt_4(hi)
{
	#pragma unused hi
}

remotefunc static stock string:yrt_5(hi, const string:you[], there[], tt, &other, const len = 7)
{
	#pragma unused hi, you, there, tt, len
	new str[130];
	str = "Hello World";
	other += 5;
	return str;
}

remotefunc Float:yrt_55(hi, const string:you[], there[], tt, &other, const len = 7)
{
	// Figure out why this fails with the "len" parameter (allocates too much
	// heap data and doesn't fully clear it).
	#pragma unused you, there, tt, len
	other = hi + 5;
	return 5.5;
}

remotefunc stock Float:yrt_6(hi, string:you[], there[], len);

remotefunc static void:yrt_7(&a, &b, c, &d)
{
	a = 8;
	b = a;
	c += d;
	d -= 4;
}

remotefunc stock string:yrt_8();

remotefunc Float:yrt_9();

Test:y_remote_1()
{
	
}

Test:y_remote_2()
{
	new arr[89], oo = sizeof (arr);
	ASSERT(broadcastfunc yrt_2(789, "string", arr, oo) == 0);
	ASSERT(strlen(broadcastfunc yrt_2b(789, "string", arr, oo)) == 0);
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
	ASSERT(broadcastfunc yrt_9() == 0.0);
}

