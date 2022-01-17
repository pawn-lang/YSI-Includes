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

/*

    88888888ba,                              88           88
    88      `"8b                             88           88
    88        `8b                            88           88
    88         88   ,adPPYba,   88       88  88,dPPYba,   88   ,adPPYba,
    88         88  a8"     "8a  88       88  88P'    "8a  88  a8P_____88
    88         8P  8b       d8  88       88  88       d8  88  8PP"""""""
    88      .a8P   "8a,   ,a8"  "8a,   ,a88  88b,   ,a8"  88  "8b,   ,aa
    88888888Y"'     `"YbbdP"'    `"YbbdP'Y8  8Y"Ybbd8"'   88   `"Ybbd8"'


*/

// Detect DBCS codepages.  There's a good chance that your code just won't
// compile if you're using one of these, but at least it can be detected.

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

/*

     ad88888ba   88                            88
    d8"     "8b  ""                            88
    Y8,                                        88
    `Y8aaaaa,    88  8b,dPPYba,    ,adPPYb,d8  88   ,adPPYba,
      `"""""8b,  88  88P'   `"8a  a8"    `Y88  88  a8P_____88
            `8b  88  88       88  8b       88  88  8PP"""""""
    Y8a     a8P  88  88       88  "8a,   ,d88  88  "8b,   ,aa
     "Y88888P"   88  88       88   `"YbbdP"Y8  88   `"Ybbd8"'
                                   aa,    ,88
                                    "Y8bbdP"

*/

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

#if __COMPILER_CODEPAGE_TEST_1 == 160
	const __COMPILER_CODEPAGE_TEST_2 = '˜'; // '\152'

	#if __COMPILER_CODEPAGE_TEST_2 == 9488
		#define __COMPILER_CODEPAGE (708)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_2 == 1569
		#define __COMPILER_CODEPAGE (720)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_2 == 945
		#define __COMPILER_CODEPAGE (737)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_2 == 1118
		#define __COMPILER_CODEPAGE (855)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_2 == 204
		#define __COMPILER_CODEPAGE (860)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_2 == 253
		#define __COMPILER_CODEPAGE (861)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_2 == 1512
		#define __COMPILER_CODEPAGE (862)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_2 == 164
		#define __COMPILER_CODEPAGE (863)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_2 == 187
		#define __COMPILER_CODEPAGE (864)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_2 == 1064
		#define __COMPILER_CODEPAGE (866)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_2 == 911
		#define __COMPILER_CODEPAGE (869)
		#endinput
	#endif

	const __COMPILER_CODEPAGE_TEST_4 = 'Ð'; // '\208'

	#if __COMPILER_CODEPAGE_TEST_4 == 261
		#define __COMPILER_CODEPAGE (775)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_4 == 273
		#define __COMPILER_CODEPAGE (852)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_4 == 240
		#define __COMPILER_CODEPAGE (850)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_4 == 9576
		#define __COMPILER_CODEPAGE (865)
		#endinput
	#endif

	const __COMPILER_CODEPAGE_TEST_5 = 'Ï'; // '\207'

	#if __COMPILER_CODEPAGE_TEST_5 == 8364
		#define __COMPILER_CODEPAGE (872)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_5 == 164
		#define __COMPILER_CODEPAGE (855)
		#endinput
	#endif

	// Unknown.
	#define __COMPILER_CODEPAGE (-1)
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

// Byte `\xFF;` (`\255`) is not translated.  Try some others.

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

