enum E_SPECIFIER_FIRST_CELL
{
	E_SPECIFIER_HEADER_1  = 0x80000000, // Always 1.
	E_SPECIFIER_HEADER_2  = 0x40000000, // Always 0.
	E_SPECIFIER_IS_COLOUR = 0x20000000,
	E_SPECIFIER_TYPE      = 0x0000001F,
	E_SPECIFIER_STRING    = 0,
	E_SPECIFIER_FLOAT     = 1,
	E_SPECIFIER_ARRAY     = 2,
	E_SPECIFIER_HEX       = 3,
	E_SPECIFIER_DEC       = 4,
	E_SPECIFIER_BIN       = 5,
	E_SPECIFIER_CHAR      = 6,
	E_SPECIFIER_IEEE      = 7,
	E_SPECIFIER_COMM      = 8,
	E_SPECIFIER_SUFFIX    = 9,
	E_SPECIFIER_UNSIGNED  = 10,
	E_SPECIFIER_SIGNED    = 11,
	E_SPECIFIER_PLAYER    = 12,
	E_SPECIFIER_LOGICAL   = 13,
	E_SPECIFIER_CUSTOM    = 14,
	E_SPECIFIER_DATE      = 15,
	E_SPECIFIER_OCT       = 16,
	E_SPECIFIER_WIDTH     = 0x000FFF00,
	E_SPECIFIER_FLAGS     = 0x0F000000,
	E_SPECIFIER_IS_LEFT   = 0x01000000,
	E_SPECIFIER_IS_ZERO   = 0x02000000,
	E_SPECIFIER_IS_LIST   = 0x04000000, // Array of data
	E_SPECIFIER_IS_FUNC   = 0x08000000, // Function of data
	// Colour information.
	E_SPECIFIER_IS_GTL    = 0x01000000,
	E_SPECIFIER_IS_CLOSE  = 0x02000000,
	E_SPECIFIER_IS_FADE   = 0x04000000,
	E_SPECIFIER_RGB       = 0x00FFFFFF,
}

enum e_SPECIFIER_FLAGS
{
	e_SPECIFIER_IS_LEFT   = 0x01000000,
	e_SPECIFIER_IS_ZERO   = 0x02000000,
	e_SPECIFIER_IS_LIST   = 0x04000000, // Array of data
	e_SPECIFIER_IS_FUNC   = 0x08000000, // Function of data
}

enum E_SPECIFIER_SECOND_CELL
{
	E_SPECIFIER_PREC      = 0x0FFF0000,
	E_SPECIFIER_NEXT      = 0x0000FFFF,
}

#define SPECIFIER_DEFAULT_WIDTH (0xFFF)
#define SPECIFIER_STAR_WIDTH    (0xFFE)

#define SPECIFIER_DEFAULT_PREC  (0xFFF)
#define SPECIFIER_STAR_PREC     (0xFFE)

#define E_SPECIFIER_FIRST_CELL:(%0,%1_0) E_SPECIFIER_FIRST_CELL:%0[%1]
#define E_SPECIFIER_SECOND_CELL:(%0,%1_1) E_SPECIFIER_SECOND_CELL:%0[%1+1]

/**--------------------------------------------------------------------------**\
<summary>Specifier_GetFlags</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	The specifier flags from the compressed data.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Specifier_GetFlags(%0) (e_SPECIFIER_FLAGS:(E_SPECIFIER_FIRST_CELL:(%0_0) & E_SPECIFIER_FLAGS))

/**--------------------------------------------------------------------------**\
<summary>Specifier_GetPrecision</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	The precision from this format specifier.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Specifier_GetPrecision(%0) (_:(E_SPECIFIER_SECOND_CELL:(%0_1) & E_SPECIFIER_PREC) >>> 16)

/**--------------------------------------------------------------------------**\
<summary>Specifier_GetColour</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	The precision from this format specifier.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Specifier_GetColour(%0) (_:(E_SPECIFIER_FIRST_CELL:(%0_0) & E_SPECIFIER_RGB))

/**--------------------------------------------------------------------------**\
<summary>Specifier_GetWidth</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	The width from this format specifier.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Specifier_GetWidth(%0) (_:(E_SPECIFIER_FIRST_CELL:(%0_0) & E_SPECIFIER_WIDTH) >>> 8)

/**--------------------------------------------------------------------------**\
<summary>Specifier_GetType</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	Is this a colour specifier?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Specifier_GetType(%0) ((E_SPECIFIER_FIRST_CELL:(%0_0) & E_SPECIFIER_TYPE))

/**--------------------------------------------------------------------------**\
<summary>Specifier_IsColour</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	Is this a colour specifier?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Specifier_IsColour(%0) (bool:(E_SPECIFIER_FIRST_CELL:(%0_0) & E_SPECIFIER_IS_COLOUR))

/**--------------------------------------------------------------------------**\
<summary>Specifier_IsLightGTColour</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	Does this colour use the special GameText "~h~" initial colours - colours
	that can't be set manually, can only be at the start of a string?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Specifier_IsLightGTColour(%0) (bool:(E_SPECIFIER_FIRST_CELL:(%0_0) & E_SPECIFIER_IS_GTL))

/**--------------------------------------------------------------------------**\
<summary>Specifier_IsFadeStart(/summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	Is this the start of a colour fade.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Specifier_IsFadeStart(%0) (bool:(E_SPECIFIER_FIRST_CELL:(%0_0) & E_SPECIFIER_IS_FADE))

/**--------------------------------------------------------------------------**\
<summary>Specifier_IsColour</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	Does this colour return to the default, instead of giving an exact colour?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Specifier_IsColourClose(%0) (bool:(E_SPECIFIER_FIRST_CELL:(%0_0) & E_SPECIFIER_IS_CLOSE))

/**--------------------------------------------------------------------------**\
<summary>Specifier_IsLeftPadded</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	Is this specifier padded on the left- or right-hand side?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Specifier_IsLeftPadded(%0) (bool:(E_SPECIFIER_FIRST_CELL:(%0_0) & E_SPECIFIER_IS_LEFT))

/**--------------------------------------------------------------------------**\
<summary>Specifier_IsZeroPadded</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	Is this specifier padded with zeros or spaces?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Specifier_IsZeroPadded(%0) (bool:(E_SPECIFIER_FIRST_CELL:(%0_0) & E_SPECIFIER_IS_ZERO))

/**--------------------------------------------------------------------------**\
<summary>Specifier_IsList</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	Is this specifier a list of items (to be delimited)?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Specifier_IsList(%0) (bool:(E_SPECIFIER_FIRST_CELL:(%0_0) & E_SPECIFIER_IS_LIST))

/**--------------------------------------------------------------------------**\
<summary>Specifier_IsFunction</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	Does this specifier's data come from a function we should call?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Specifier_IsFunction(%0) (bool:(E_SPECIFIER_FIRST_CELL:(%0_0) & E_SPECIFIER_IS_FUNC))

/**--------------------------------------------------------------------------**\
<summary>SpecFlag_IsLeftPadded</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	Is this specifier padded on the left- or right-hand side?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define SpecFlag_IsLeftPadded(%0) (bool:((%0) & e_SPECIFIER_IS_LEFT))

/**--------------------------------------------------------------------------**\
<summary>SpecFlag_IsZeroPadded</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	Is this specifier padded with zeros or spaces?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define SpecFlag_IsZeroPadded(%0) (bool:((%0) & e_SPECIFIER_IS_ZERO))

/**--------------------------------------------------------------------------**\
<summary>SpecFlag_IsList</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	Is this specifier a list of items (to be delimited)?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define SpecFlag_IsList(%0) (bool:((%0) & e_SPECIFIER_IS_LIST))

/**--------------------------------------------------------------------------**\
<summary>SpecFlag_IsFunction</summary>
<param name="specifier">The specifier data to analyse.</param>
<returns>
	Does this specifier's data come from a function we should call?
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define SpecFlag_IsFunction(%0) (bool:((%0) & e_SPECIFIER_IS_FUNC))

/**--------------------------------------------------------------------------**\
<summary>Specifier_Read</summary>
<param name="const string:input[]">Input string (without length prefix).</param>
<param name="const pos">Position in the string of the specifier.</param>
<returns>
	Both cells of the specifier.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Specifier_Read(%0,%1) E_SPECIFIER_FIRST_CELL:%0[%1],E_SPECIFIER_SECOND_CELL:%0[%1+1]

/**--------------------------------------------------------------------------**\
<summary>Specifier_Next</summary>
<param name="const string:input[]">Input string (without length prefix).</param>
<param name="const pos">Position in the string of the specifier.</param>
<returns>
	Get the next specifier address in the string.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define Specifier_Next(%0) (_:(E_SPECIFIER_SECOND_CELL:(%0_1) & E_SPECIFIER_NEXT))

#define Specifier:%0, E_SPECIFIER_FIRST_CELL:%0_0, E_SPECIFIER_SECOND_CELL:%0_1,

