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
/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   A string that is only two cells long is a DBCS character set is used, or is
 *   more otherwise.  We then use <c>sizeof</c> to determine which.  Note that
 *   one of those two cells is the null terminator, so the two characters
 *   compile to a single character.
 * </remarks>
 */
static stock const __COMPILER_CODEPAGE_TEST_0[] = \__COMPILER_UNPACK"AÒ";

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   If the script is determined to be using DBCS, we next need to know WHICH
 *   DBCS codepage.  Which unicode character is the given byte sequence
 *   converted to?
 * </remarks>
 */
#if sizeof (__COMPILER_CODEPAGE_TEST_0) == 2
	const __COMPILER_CODEPAGE_TEST_1 = 'AÒ';

	#if __COMPILER_CODEPAGE_TEST_1 == 7842
		#define __COMPILER_CODEPAGE (1258)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_1 == 1057
		// SO MANY codepages match this.
		//#define __COMPILER_CODEPAGE (1254)
		//#endinput
	#endif

	// Unknown.
	#define __COMPILER_CODEPAGE (-1)
	#endinput
#else
	const __COMPILER_CODEPAGE_TEST_1 = 0;
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

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   If the script is determined not to be using DBCS, we still need to
 *   determine the single byte codepage in use.  The best character to use for
 *   this is <c>'\255'</c>, which is a different unicode character in a large
 *   number of codepages.  If the resulting value is unique to one codepage, we
 *   know it is that codepage.  If it isn't then further differentiation is
 *   required.
 * </remarks>
 */
const __COMPILER_CODEPAGE_TEST_2 = 'ÿ'; // '\255'

#if __COMPILER_CODEPAGE_TEST_2 == 1103
	#define __COMPILER_CODEPAGE (1251)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_2 == 1746
	#define __COMPILER_CODEPAGE (1256)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_2 == 63638
	#define __COMPILER_CODEPAGE (1255)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_2 == 63688
	#define __COMPILER_CODEPAGE (874)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_2 == 63739
	#define __COMPILER_CODEPAGE (1253)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_2 == 63736
	#define __COMPILER_CODEPAGE (950)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_2 == 63735
	#define __COMPILER_CODEPAGE (949)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_2 == 63733
	#define __COMPILER_CODEPAGE (936)
	#endinput
#endif

#if __COMPILER_CODEPAGE_TEST_2 == 63731
	#define __COMPILER_CODEPAGE (932)
	#endinput
#endif

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   This differentiates between codepages who all translate <c>'\255'</c> to
 *   unicode character <c>'\u160'</c> (of which there are a surprising amount).
 * </remarks>
 */
#if __COMPILER_CODEPAGE_TEST_2 == 160
	const __COMPILER_CODEPAGE_TEST_3 = '˜'; // '\152'

	#if __COMPILER_CODEPAGE_TEST_3 == 9488
		#define __COMPILER_CODEPAGE (708)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_3 == 1569
		#define __COMPILER_CODEPAGE (720)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_3 == 945
		#define __COMPILER_CODEPAGE (737)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_3 == 1118
		#define __COMPILER_CODEPAGE (855)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_3 == 204
		#define __COMPILER_CODEPAGE (860)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_3 == 253
		#define __COMPILER_CODEPAGE (861)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_3 == 1512
		#define __COMPILER_CODEPAGE (862)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_3 == 164
		#define __COMPILER_CODEPAGE (863)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_3 == 187
		#define __COMPILER_CODEPAGE (864)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_3 == 1064
		#define __COMPILER_CODEPAGE (866)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_3 == 911
		#define __COMPILER_CODEPAGE (869)
		#endinput
	#endif
#else
	const __COMPILER_CODEPAGE_TEST_3 = 0;
#endif

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   This differentiates between codepages who all translate <c>'\255'</c> to
 *   unicode character <c>'\u160'</c> (of which there are a surprising amount),
 *   but which didn't match any of the previous tests.
 * </remarks>
 */
#if __COMPILER_CODEPAGE_TEST_2 == 160
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
#else
	const __COMPILER_CODEPAGE_TEST_4 = 0;
#endif

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   This differentiates between codepages who all translate <c>'\255'</c> to
 *   unicode character <c>'\u160'</c> (of which there are a surprising amount),
 *   but which didn't match any of the previous tests.
 * </remarks>
 */
#if __COMPILER_CODEPAGE_TEST_2 == 160
	const __COMPILER_CODEPAGE_TEST_5 = 'Ï'; // '\207'

	#if __COMPILER_CODEPAGE_TEST_5 == 8364
		#define __COMPILER_CODEPAGE (872)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_5 == 164
		#define __COMPILER_CODEPAGE (855)
		#endinput
	#endif
#else
	const __COMPILER_CODEPAGE_TEST_5 = 0;
#endif

#if __COMPILER_CODEPAGE_TEST_2 == 160
	// Unknown.
	#define __COMPILER_CODEPAGE (-1)
	#endinput
#endif

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   This differentiates between codepages who all translate <c>'\255'</c> to
 *   unicode character <c>'\u729'</c>.
 * </remarks>
 */
#if __COMPILER_CODEPAGE_TEST_2 == 729
	const __COMPILER_CODEPAGE_TEST_6 = 'þ'; // '\254'

	#if __COMPILER_CODEPAGE_TEST_6 == 355
		#define __COMPILER_CODEPAGE (1250)
		#endinput
	#endif

	#if __COMPILER_CODEPAGE_TEST_6 == 382
		#define __COMPILER_CODEPAGE (1257)
		#endinput
	#endif
#else
	const __COMPILER_CODEPAGE_TEST_6 = 0;
#endif

#if __COMPILER_CODEPAGE_TEST_2 == 729
	// Unknown.
	#define __COMPILER_CODEPAGE (-1)
	#endinput
#endif

// Byte `\xFF;` (`\255`) is not translated.  Try some others.

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   This differentiates between codepages that don't translate <c>'\255'</c> to
 *   anything (i.e. it remains the same).
 * </remarks>
 */
const __COMPILER_CODEPAGE_TEST_7 = '€'; // '\128'

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Check <c>'\128' == '\u8364' && '\142' == '\u381'</c>.
 * </remarks>
 */
#if __COMPILER_CODEPAGE_TEST_7 == 8364
	const __COMPILER_CODEPAGE_TEST_8 = 'Ž'; // '\142'

	#if __COMPILER_CODEPAGE_TEST_8 == 381
		#define __COMPILER_CODEPAGE (1252)
		#endinput
	#endif
#else
	const __COMPILER_CODEPAGE_TEST_8 = 0;
#endif

/**
 * <library>y_compilerdata</library>
 * <remarks>
 *   Check <c>'\128' == '\u8364' && '\208' == '\u286'</c>.
 * </remarks>
 */
#if __COMPILER_CODEPAGE_TEST_7 == 8364
	const __COMPILER_CODEPAGE_TEST_9 = 'Ð'; // '\208'

	#if __COMPILER_CODEPAGE_TEST_9 == 286
		#define __COMPILER_CODEPAGE (1254)
		#endinput
	#endif
#else
	const __COMPILER_CODEPAGE_TEST_9 = 0;
#endif

#if __COMPILER_CODEPAGE_TEST_7 == 8364
	// Unknown.
	#define __COMPILER_CODEPAGE (-1)
	#endinput
#endif

// None.
#define __COMPILER_CODEPAGE (0)

