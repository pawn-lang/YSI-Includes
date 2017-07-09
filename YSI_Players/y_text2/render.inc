/*----------------------------------------------------------------------------*\
 |                                                                            | 
 |  How strings are stored in memory:                                         | 
 |                                                                            | 
 |  0) There is a single cell prefix of the total length.                     | 
 |  1) Normal characters are just normal characters.                          | 
 |  2) Specifiers and colours have the top two bits as "0b10" (since this is  | 
 |     not valid in unicode of any sort).  The third bit is then "0b0" for    | 
 |     specifiers with their data encoded, and "0b1" for colours with three   | 
 |     bytes of "RGB" data following (and some flags for fades etc).          | 
 |  3) The end of the string is a special specifier that does nothing (may    | 
 |     look like a colour to avoid additional encodings, since colours at the | 
 |     end are ignored anyway).                                               | 
 |  4) Each specifier is followed by a pointer to the PREVIOUS one (so the    | 
 |     final specifier starts two cells from the end of the string).          | 
 |  5) The pointer is combined with a parameter offset, so each specifier     | 
 |     knows which parameter it should be reading (the first if it needs      | 
 |     multiple).                                                             | 
 |                                                                            | 
 |  How to render a string:                                                   | 
 |                                                                            | 
 |  1) Jump to the final specifier to start rendering, following the list.    | 
 |  2) When a specifier, do it.                                               | 
 |  3) When a colour, wait, and convert the colour list to a forward list.    | 
 |  4) Keep track of how many characters are inserted.                        | 
 |  5) When on colours, use that tracking to adjust where the next colour is, | 
 |     and reset the count.                                                   | 
 |                                                                            | 
\*----------------------------------------------------------------------------*/



/**--------------------------------------------------------------------------**\
<summary>Text_RenderLoop</summary>
<param name="string:output[]">Where to write the result to.</param>
<param name="outputLength">Output string length.</param>
<param name="const string:input[]">Input string (without length prefix).</param>
<param name="const inputLength">Input string length.</param>
<param name="const Language:language">Output language.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

static stock Text_RenderLoop(string:output[], outputLength, const string:input[], const inputLength, const Language:language)
{
	//     
	//     ███████╗████████╗███████╗██████╗      ██╗
	//     ██╔════╝╚══██╔══╝██╔════╝██╔══██╗    ███║
	//     ███████╗   ██║   █████╗  ██████╔╝    ╚██║
	//     ╚════██║   ██║   ██╔══╝  ██╔═══╝      ██║
	//     ███████║   ██║   ███████╗██║          ██║
	//     ╚══════╝   ╚═╝   ╚══════╝╚═╝          ╚═╝
	//     
	// Regular specifiers.
	new
		outputIdx = 0,
		curSpecIndex = 0,
		prevSpecIndex,
		firstColourIndex = -1,
		prevColourIndex = -1,
		addedLength;
	while (outputLength > 0 && curSpecIndex != inputLength)
	{
		// There is always a specifier at the start of the string, it just might
		// not do anything.
		if (Specifier_IsColour(input, curSpecIndex))
		{
			if (outputLength < 2)
				break;
			addedLength = outputIdx + 1;
			// The colour linked list jumps are relative.
			if (firstColourIndex == -1)
				firstColourIndex = outputIdx;
			else
				output[prevColourIndex] = addedLength - prevColourIndex;
			output[outputIdx] = input[curSpecIndex];
			prevColourIndex = addedLength;
			output[addedLength] = -1;
			outputLength -= 2;
			outputIdx += 2;
		}
		else
		{
			addedLength = Text_DoSpecifier(Specifier_Read(input, curSpecIndex), language, output[outputIdx], outputLength);
			outputIdx += addedLength;
			outputLength -= addedLength;
		}
		// Move on.
		prevSpecIndex = curSpecIndex + 2;
		curSpecIndex = Specifier_Next(input, curSpecIndex);
		// A specifier is always followed by a length of normal text; however,
		// that length may be zero...
		addedLength = min(outputLength, curSpecIndex - prevSpecIndex);
		strcat(output[outputIdx], input[prevSpecIndex], addedLength + 1);
		outputIdx += addedLength;
		outputLength -= addedLength;
	}
	// "outputLength" is always one short to make this work.
	output[outputIdx] = '\0';
	//                                                 
	//     ███████╗████████╗███████╗██████╗     ██████╗ 
	//     ██╔════╝╚══██╔══╝██╔════╝██╔══██╗    ╚════██╗
	//     ███████╗   ██║   █████╗  ██████╔╝     █████╔╝
	//     ╚════██║   ██║   ██╔══╝  ██╔═══╝     ██╔═══╝ 
	//     ███████║   ██║   ███████╗██║         ███████╗
	//     ╚══════╝   ╚═╝   ╚══════╝╚═╝         ╚══════╝
	//
	// Colours.
}

/*
                                                                              
    88        88              88                                                  
    88        88              88                                                  
    88        88              88                                                  
    88aaaaaaaa88   ,adPPYba,  88  8b,dPPYba,    ,adPPYba,  8b,dPPYba,  ,adPPYba,  
    88""""""""88  a8P_____88  88  88P'    "8a  a8P_____88  88P'   "Y8  I8[    ""  
    88        88  8PP"""""""  88  88       d8  8PP"""""""  88           `"Y8ba,   
    88        88  "8b,   ,aa  88  88b,   ,a8"  "8b,   ,aa  88          aa    ]8I  
    88        88   `"Ybbd8"'  88  88`YbbdP"'    `"Ybbd8"'  88          `"YbbdP"'  
                                  88                                              
                                  88                                              

*/

static stock
	YSI_g_sSpecifier[8];

static stock
	YSI_g_sSpecTempl[][8] =
		{
			"%*.*d",  // 6 (6)
			"%-*.*d", // 7 (13)
			"%0*.*d", // 7 (20)
			"%0-*.*d" // 8 (28)
		};

#define Text_MakeSpecifier(%1,%0); switch((%1)&(e_SPECIFIER_IS_LEFT|e_SPECIFIER_IS_ZERO)){\
case e_SPECIFIER_IS_LEFT|e_SPECIFIER_IS_ZERO:YSI_g_sSpecifier=YSI_g_sSpecTempl[3],YSI_g_sSpecifier[6]=%0;\
case e_SPECIFIER_IS_ZERO:YSI_g_sSpecifier=YSI_g_sSpecTempl[2],YSI_g_sSpecifier[5]=%0;\
case e_SPECIFIER_IS_LEFT:YSI_g_sSpecifier=YSI_g_sSpecTempl[1],YSI_g_sSpecifier[5]=%0;\
default:YSI_g_sSpecifier=YSI_g_sSpecTempl[0],YSI_g_sSpecifier[4]=%0;}

/**--------------------------------------------------------------------------**\
<summary>Text_SimpleSpecifier</summary>
<param name="width">How wide to make the output string.</param>
<param name="prec">Settings for certain specifiers (dp etc).</param>
<param name="e_SPECIFIER_FLAGS:flags">Padding options.</param>
<param name="specifier">Which letter to use after "%".</param>
<param name="string:output[]">Where to write the result to.</param>
<param name="const outputLength">Output string length.</param>
<returns>
	The length of text added.
</returns>
<remarks>
	There is always one cell reserved in the output for NULL, so we can always
	write that out even when out of space.
</remarks>
\**--------------------------------------------------------------------------**/

static stock Text_SimpleSpecifier(width, prec, e_SPECIFIER_FLAGS:flags, specifier, string:output[], const outputLength)
{
	switch(flags & (e_SPECIFIER_IS_LEFT | e_SPECIFIER_IS_ZERO))
	{
		case e_SPECIFIER_IS_LEFT | e_SPECIFIER_IS_ZERO:
			YSI_g_sSpecTempl[3][6] = specifier,
			format(output, outputLength, YSI_g_sSpecTempl[3], width, prec, Text_ReadIntParam());
		case e_SPECIFIER_IS_ZERO:
			YSI_g_sSpecTempl[2][5] = specifier,
			format(output, outputLength, YSI_g_sSpecTempl[2], width, prec, Text_ReadIntParam());
		case e_SPECIFIER_IS_LEFT:
			YSI_g_sSpecTempl[1][5] = specifier,
			format(output, outputLength, YSI_g_sSpecTempl[1], width, prec, Text_ReadIntParam());
		default:
			YSI_g_sSpecTempl[0][4] = specifier,
			format(output, outputLength, YSI_g_sSpecTempl[0], width, prec, Text_ReadIntParam());
	}
	return strlen(output);
}

/**--------------------------------------------------------------------------**\
<summary>Text_DoSpecifier</summary>
<param name="Specifier:specifier">Information about what to insert.</param>
<param name="const Language:language">Output language.</param>
<param name="string:output[]">Where to write the result to.</param>
<param name="const outputLength">Output string length.</param>
<returns>
	The length of text added.
</returns>
<remarks>
	There is always one cell reserved in the output for NULL, so we can always
	write that out even when out of space.
</remarks>
\**--------------------------------------------------------------------------**/

static stock Text_DoSpecifier(Specifier:specifier, const Language:language, string:output[], const outputLength)
{
	new
		width = Specifier_GetWidth(specifier),
		prec  = Specifier_GetPrecision(specifier),
		e_SPECIFIER_FLAGS:flags = Text_GetPrecision(Specifier:specifier);
	switch (width)
	{
	// Must come first (for parameter reading ordering).
	case SPECIFIER_DEFAULT_WIDTH: width = 0;
	case SPECIFIER_STAR_WIDTH:    width = Text_ReadIntParam();
	}
	switch (prec)
	{
	// Must come second (for parameter reading ordering).
	case SPECIFIER_DEFAULT_PREC: prec = -1;
	case SPECIFIER_STAR_PREC:    prec = Text_ReadIntParam();
	}
	switch (Specifier_GetType(specifier))
	{
	case E_SPECIFIER_STRING  : return Text_DoSpecifierString     (width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_FLOAT   : return Text_DoSpecifierFloat      (width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_ARRAY   : return Text_DoSpecifierArray      (width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_HEX     : return Text_DoSpecifierHexadecimal(width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_DEC     : return Text_DoSpecifierDecimal    (width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_BIN     : return Text_DoSpecifierBinary     (width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_CHAR    : return Text_DoSpecifierChar       (width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_IEEE    : return Text_DoSpecifierIEEE       (width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_COMM    : return Text_DoSpecifierCommand    (width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_SUFFIX  : return Text_DoSpecifierSuffix     (width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_UNSIGNED: return Text_DoSpecifierUnsigned   (width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_SIGNED  : return Text_DoSpecifierSigned     (width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_PLAYER  : return Text_DoSpecifierPlayer     (width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_LOGICAL : return Text_DoSpecifierLogical    (width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_CUSTOM  : return Text_DoSpecifierCustom     (width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_DATE    : return Text_DoSpecifierDate       (width, prec, flags, language, output, outputLength);
	case E_SPECIFIER_OCT     : return Text_DoSpecifierOctal      (width, prec, flags, language, output, outputLength);
	}
	return 0;
}

//#define Text_MakeSpecifier(%0,%1) YSI_g_sSpecifier = ((SpecFlag_IsZeroPadded(%1)) \
//	? ((SpecFlag_IsLeftPadded(%1)) \
//		? (YSI_g_sSpecTempl[3][6] = (%0), YSI_g_sSpecTempl[3]) \
//		: (YSI_g_sSpecTempl[2][5] = (%0), YSI_g_sSpecTempl[2])) \
//	: ((SpecFlag_IsLeftPadded(%1)) \
//		? (YSI_g_sSpecTempl[1][5] = (%0), YSI_g_sSpecTempl[1]) \
//		: (YSI_g_sSpecTempl[0][4] = (%0), YSI_g_sSpecTempl[0])))

/*
                                                                                                  
     ad88888ba                                        88     ad88  88                                     
    d8"     "8b                                       ""    d8"    ""                                     
    Y8,                                                     88                                            
    `Y8aaaaa,    8b,dPPYba,    ,adPPYba,   ,adPPYba,  88  MM88MMM  88   ,adPPYba,  8b,dPPYba,  ,adPPYba,  
      `"""""8b,  88P'    "8a  a8P_____88  a8"     ""  88    88     88  a8P_____88  88P'   "Y8  I8[    ""  
            `8b  88       d8  8PP"""""""  8b          88    88     88  8PP"""""""  88           `"Y8ba,   
    Y8a     a8P  88b,   ,a8"  "8b,   ,aa  "8a,   ,aa  88    88     88  "8b,   ,aa  88          aa    ]8I  
     "Y88888P"   88`YbbdP"'    `"Ybbd8"'   `"Ybbd8"'  88    88     88   `"Ybbd8"'  88          `"YbbdP"'  
                 88                                                                                       
                 88                                                                                       

*/

static stock Text_DoSpecifierString     (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	Text_MakeSpecifier(flags, 's');
}

static stock Text_DoSpecifierFloat      (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	Text_MakeSpecifier(flags, 'f');
}

static stock Text_DoSpecifierArray      (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	//Text_MakeSpecifier(flags, 's');
}

static stock Text_DoSpecifierHexadecimal(width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	new
		arg = Text_ReadIntParam();
	if (arg & cellmin)
	{
		if (width>8)
			SpecFlag_IsLeftPadded(flags)
				? (SpecFlag_IsZeroPadded(flags)
					? format(ts, 130, "%x%0-*x", arg >>> 4, width - 7, arg & 15)
					: format(ts, 130, "%x%-*x", arg >>> 4, width - 7, arg & 15))
				: (SpecFlag_IsZeroPadded(flags)
					? format(ts, 130, "%0*x%x", width - 1, arg >>> 4, arg & 15)
					: format(ts, 130, "%*x%x", width - 1, arg >>> 4, arg & 15));
		else
			format(ts,130,"%x%x",arg>>>4,arg&15)
	}
	else
	{
		Text_SimpleSpecifier(width, prec, flags, 'x');
	}
}

static stock Text_DoSpecifierDecimal    (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	Text_MakeSpecifier(flags, 'd');
}

static stock Text_DoSpecifierBinary     (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	Text_MakeSpecifier(flags, 'b');
}

static stock Text_DoSpecifierChar       (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	Text_MakeSpecifier(flags, 'c');
}

static stock Text_DoSpecifierIEEE       (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	Text_MakeSpecifier(flags, 's');
	Text_MakeSpecifier(flags, 'f');
}

static stock Text_DoSpecifierCommand    (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	Text_MakeSpecifier(flags, 's');
}

static stock Text_DoSpecifierSuffix     (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	Text_MakeSpecifier(flags, 's');
}

static stock Text_DoSpecifierUnsigned   (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	//Text_MakeSpecifier(flags, 's');
}

static stock Text_DoSpecifierSigned     (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	Text_MakeSpecifier(flags, 's');
}

static stock Text_DoSpecifierPlayer     (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	Text_MakeSpecifier(flags, 's');
}

static stock Text_DoSpecifierLogical    (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	Text_MakeSpecifier(flags, 's');
}

static stock Text_DoSpecifierCustom     (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	Text_MakeSpecifier(flags, 's');
}

static stock Text_DoSpecifierDate       (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	Text_MakeSpecifier(flags, 's');
}

static stock Text_DoSpecifierOctal      (width, prec, e_SPECIFIER_FLAGS:flags, Language:language, string:output[], const outputLength)
{
	Text_MakeSpecifier(flags, 's');
}

