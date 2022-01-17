// NOTE: This file has a lot of weird characters in it.  Be careful when
// editing it to not clobber the bytes.  This is because escape sequences don't
// work for being translated via codepages.
//
// Adding a new codepage is surprisingly simple - just emulate the steps the
// compiler takes.  So the first test is `\xFF;` (`\255`), look at what that
// byte is in the new translation file.  If it is something unique relative to
// existing codepages then add that test and you're done.  If it is the same as
// an existing translation, find a character that is different between the two.
// If it is nothing/missing, move on to the next test.  If you get to the end
// and haven't managed to identify it yet, just add and test for a translated
// character in the file.
//

// DBCS tests.

// Use an unpacked raw string, to maybe get translations.
static stock const __COMPILER_CODEPAGE_TEST_6[] = __COMPILER_UKPACK\"AÒ";

#if sizeof (__COMPILER_CODEPAGE_TEST_6) == 2
	const __COMPILER_CODEPAGE_TEST_7 = 'AÒ';

	#if __COMPILER_CODEPAGE_TEST_7 == 7842
		#define __COMPILER_CODEPAGE (1258)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_7 == 1057
		// SO MANY codepages match this.
		//#define __COMPILER_CODEPAGE (1254)
		//#endinput
	#endif

	// Unknown.
	#define __COMPILER_CODEPAGE (-1)
	#endinput
#endif

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

// None.
#define __COMPILER_CODEPAGE (0)

