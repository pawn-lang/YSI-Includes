#define Y_UTILS_NO_VALUE
#define Y_UTILS_VALUE (42)
#define Y_UTILS_INVALID (999999)

TestCompile:y_utils()
{
	#assert NO_VALUE(Y_UTILS_NO_VALUE)
	#assert !NO_VALUE(Y_UTILS_VALUE)
	#assert IS_IN_RANGE(Y_UTILS_VALUE, -30, 43)
	#assert !IS_IN_RANGE(Y_UTILS_VALUE, -30, 42)
	#assert NOT_IN_RANGE(Y_UTILS_VALUE, 0, 10)
	#assert !NOT_IN_RANGE(Y_UTILS_VALUE, 20, 100)
	#assert VALID_PLAYERID(Y_UTILS_VALUE)
	#assert !VALID_PLAYERID(Y_UTILS_INVALID)
	#assert UCMP(4, 100)
	#assert !UCMP(-4, 100)
	__TU(0, 0);
	#assert ceildiv(12, 3) == 4
	#assert ceildiv(11, 3) == 4
	#assert ceildiv(10, 3) == 4
	#assert ceildiv(9, 3) == 3
	#assert ceildiv(8, 3) == 3
	#assert floordiv(12, 3) == 4
	#assert floordiv(11, 3) == 3
	#assert floordiv(10, 3) == 3
	#assert floordiv(9, 3) == 3
	#assert floordiv(8, 3) == 2
	#assert isodd(3)
	#assert !isodd(8)
	#assert iseven(8)
	#assert !iseven(3)
	new str[32];
	ASSERT(isnull(str));
	StrToLower(str);
	StrToUpper(str);
	Random(0);
	RandomFloat(0.0);
	StripNL(str);
	StripR(str);
	StripL(str);
	Strip(str);
	endofline(str, 0);
	chrfind(' ', str);
	chrfindp(' ', str);
	IPToInt(str);
	bernstein(str);
	ishex(str);
	unpack(str);
	ASSERT(GetIP(0) == 0);
	returnstringarg(0);
	va_return(str);
	isnumeric(str);
}

