// NOTE: This file has a lot of weird characters in it.  Be careful when
// editing it to not clobber the bytes.  This is because escape sequences don't
// work for being translated via codepages.
const __COMPILER_CODEPAGE_TEST_1 = 'ÿ'; // '\255'

#if __COMPILER_CODEPAGE_TEST_1 == 1103
	#define __COMPILER_CODEPAGE (1251)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_1 == 1746
	#define __COMPILER_CODEPAGE (1256)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_1 == 63638
	#define __COMPILER_CODEPAGE (1255)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_1 == 63688
	#define __COMPILER_CODEPAGE (874)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_1 == 63739
	#define __COMPILER_CODEPAGE (1253)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_1 == 63736
	#define __COMPILER_CODEPAGE (950)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_1 == 63735
	#define __COMPILER_CODEPAGE (949)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_1 == 63733
	#define __COMPILER_CODEPAGE (936)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_1 == 63731
	#define __COMPILER_CODEPAGE (932)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_1 == 729
	const __COMPILER_CODEPAGE_TEST_2 = 'þ'; // '\254'

	#if __COMPILER_CODEPAGE_TEST_2 == 355
		#define __COMPILER_CODEPAGE (1250)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_2 == 382
		#define __COMPILER_CODEPAGE (1257)
		#endinput
	#endif

	// Unknown.
	#define __COMPILER_CODEPAGE (-1)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_1 == 160
	const __COMPILER_CODEPAGE_TEST_2 = 'Ï'; // '\207'

	#if __COMPILER_CODEPAGE_TEST_2 == 8364
		#define __COMPILER_CODEPAGE (872)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_2 == 164
		#define __COMPILER_CODEPAGE (855)
		#endinput
	#endif

	// Unknown.
	#define __COMPILER_CODEPAGE (-1)
	#endinput
#endif

const __COMPILER_CODEPAGE_TEST_3 = '€'; // '\128'

#if __COMPILER_CODEPAGE_TEST_3 == 8364
	const __COMPILER_CODEPAGE_TEST_4 = 'Ž'; // '\142'
	const __COMPILER_CODEPAGE_TEST_5 = 'Ð'; // '\208'

	#if __COMPILER_CODEPAGE_TEST_4 == 381
		#define __COMPILER_CODEPAGE (1252)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_5 == 286
		#define __COMPILER_CODEPAGE (1254)
		#endinput
	#endif

	// Unknown.
	#define __COMPILER_CODEPAGE (-1)
	#endinput
#endif

// From our possibilities, it could be 1258, but we can't distinguish that in
// the pre-processor alone.  It needs a DBCS character constant, which is a
// syntax error when not using that codepage.  It needs:
// 
//     const __COMPILER_CODEPAGE_TEST_6 = 'AÃ’';
//
// But if the test fails because we aren't using that codepage, we get an error.

// None.
#define __COMPILER_CODEPAGE (0)

