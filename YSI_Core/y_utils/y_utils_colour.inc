/**
 * <library
 *   name="y_utils - colour"
 *   version="0.1.3"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Misc functions used throughout."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 *//** *//*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.

Contributors:
	Y_Less
	koolk
	JoeBullet/Google63
	g_aSlice/Slice
	Misiur
	samphunter
	tianmeta
	maddinat0r
	spacemud
	Crayder
	Dayvison
	Ahmad45123
	Zeex
	irinel1996
	Yiin-
	Chaprnks
	Konstantinos
	Masterchen09
	Southclaws
	PatchwerkQWER
	m0k1
	paulommu
	udan111
	Cheaterman

Thanks:
	JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
	ZeeX - Very productive conversations.
	koolk - IsPlayerinAreaEx code.
	TheAlpha - Danish translation.
	breadfish - German translation.
	Fireburn - Dutch translation.
	yom - French translation.
	50p - Polish translation.
	Zamaroht - Spanish translation.
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

/// <p/>

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <summary>
 *   InterpolateColourLinear(startColour, endColour, Float:fraction);
 * </summary>
 * <param name="startColour">One of the two colours.</param>
 * <param name="endColour">The other of the two colours.</param>
 * <param name="fraction">How far to interpolate between the colours.</param>
 * <remarks>
 *   This function takes a value (fraction) which is a distance between the two
 *   endpoints as a fraction.  This fraction is applied to the two colours given
 *   to find a third colour at some point between those two colours.
 *
 *   This function performs linear interpolation between the colours, which isn't
 *   usually the best way wrt human vision, but is fast.
 *
 *   The fraction is optional, and uses the second colour's alpha for blending
 *   if not given.
 * </remarks>
 *//*------------------------------------------------------------------------**/

// "Interpolation" is the technical name for what you are doing here.
stock InterpolateColourLinear(startColour, endColour, Float:fraction = FLOAT_NAN)
{
	new a = startColour & 0xFF;
	if (IsNaN(fraction))
	{
		// Extract the fraction from the second alpha.
		fraction = (endColour & 0xFF) / 255.0;
		// Use the first alpha for output transparency.
	}
	else
	{
		// Combine the alpha values to give a relative fraction and a final alpha.
		a = _:((a / 255.0) * (1.0 - fraction)),
		fraction = ((endColour & 0xFF) / 255.0) * fraction,

		// The final fraction is given comes from the relative ratio of the two alphas.
		a = _:(Float:a + fraction),
		fraction = fraction / Float:a,

		// The final alpha comes from their sum, as a fraction of 1.
		a = floatround(Float:a * 255.0);
	}
	if (fraction >= 1.0)
	{
		return endColour;
	}
    if (fraction <= 0.0)
	{
		return startColour;
	}
	new
		// Step 1: Get the starting colour components.
		r = startColour & 0xFF000000,
		g = startColour & 0x00FF0000,
		b = startColour & 0x0000FF00,
		// Manipulate the format of floats to multiply by 256 by increasing the exponent by 8.
		stage = floatround(Float:(_:fraction + 0x04000000)); // fraction * 256.0
	return
		// Step 2: Interpolate between the end points, and add to the start.
		// Step 3: Combine the individual components.
		(((r >>> 16) + ((endColour >>> 24       ) - (r >>> 24)) * stage) << 16 & 0xFF000000) |
		(((g >>>  8) + ((endColour >>> 16 & 0xFF) - (g >>> 16)) * stage) <<  8 & 0x00FF0000) |
		(((b       ) + ((endColour >>>  8 & 0xFF) - (b >>>  8)) * stage)       & 0x0000FF00) |
		(a & 0xFF);
	// Because we use a base of 256 instead of 100 to multiply the fractions, we would adjust the
	// numbers down via `>>> 8` instead of `/ 100`, but since we then shift them up again to their
	// final locations in the number we can skip a manipulation stage.
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <param name="startColour">One of the two colours.</param>
 * <param name="endColour">The other of the two colours.</param>
 * <param name="fraction">How far to interpolate between the colours.</param>
 * <remarks>
 *   This function takes a value (fraction) which is a distance between the two
 *   endpoints as a fraction.  This fraction is applied to the two colours given
 *   to find a third colour at some point between those two colours.
 *
 *   This function performs linear interpolation between the colours, which isn't
 *   usually the best way wrt human vision, but is fast.
 *
 *   The fraction is optional, and uses the second colour's alpha for blending
 *   if not given.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `InterpolateColourLinear` instead.
stock InterpolateColorLinear(startColour, endColour, Float:fraction)
{
	Debug_Warning("`InterpolateColorLinear()` called, please use `InterpolateColourLinear()` isntead,");
	return InterpolateColourLinear(startColour, endColour, value, maxvalue, minvalue);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <param name="startColour">One of the two colours.</param>
 * <param name="endColour">The other of the two colours.</param>
 * <param name="fraction">How far to interpolate between the colours.</param>
 * <remarks>
 *   This function takes a value (fraction) which is a distance between the two
 *   endpoints as a fraction.  This fraction is applied to the two colours given
 *   to find a third colour at some point between those two colours.
 *
 *   This function performs linear interpolation between the colours, which isn't
 *   usually the best way wrt human vision, but is fast.
 *
 *   The fraction is optional, and uses the second colour's alpha for blending
 *   if not given.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `InterpolateColourLinear` instead.
stock InterpolateColor(startColour, endColour, value, maxvalue, minvalue = 0)
{
	return InterpolateColourLinear(startColour, endColour, floatdiv(value - minvalue, maxvalue - minvalue));
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <param name="startColour">One of the two colours.</param>
 * <param name="endColour">The other of the two colours.</param>
 * <param name="fraction">How far to interpolate between the colours.</param>
 * <remarks>
 *   This function takes a value (fraction) which is a distance between the two
 *   endpoints as a fraction.  This fraction is applied to the two colours given
 *   to find a third colour at some point between those two colours.
 *
 *   This function performs linear interpolation between the colours, which isn't
 *   usually the best way wrt human vision, but is fast.
 *
 *   The fraction is optional, and uses the second colour's alpha for blending
 *   if not given.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `InterpolateColourLinear` instead.
stock InterpolateColour(startColour, endColour, value, maxvalue, minvalue = 0)
{
	return InterpolateColourLinear(startColour, endColour, floatdiv(value - minvalue, maxvalue - minvalue));
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <summary>
 *   InterpolateColourGamma(startColour, endColour, Float:fraction);
 * </summary>
 * <param name="startColour">One of the two colours.</param>
 * <param name="endColour">The other of the two colours.</param>
 * <param name="fraction">How far to interpolate between the colours.</param>
 * <remarks>
 *   This function takes a value (fraction) which is a distance between the two
 *   endpoints as a fraction.  This fraction is applied to the two colours given
 *   to find a third colour at some point between those two colours.
 *
 *   This function performs gamma interpolation between the colours, which is a
 *   good balance between complexity and perception.
 *
 *   The fraction is optional, and uses the second colour's alpha for blending
 *   if not given.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define FLOAT_GAMMA (2.2)
#define FLOAT_INVERSE_GAMMA (0.45454545454545454545454545454545) // 1 / 2.2

stock InterpolateColourGamma(startColour, endColour, Float:fraction = FLOAT_NAN)
{
	new a = startColour & 0xFF;
	if (IsNaN(fraction))
	{
		// Extract the fraction from the second alpha.
		fraction = (endColour & 0xFF) / 255.0;
		// Use the first alpha for output transparency.
	}
	else
	{
		// Combine the alpha values to give a relative fraction and a final alpha.
		a = _:((a / 255.0) * (1.0 - fraction)),
		fraction = ((endColour & 0xFF) / 255.0) * fraction,

		// The final fraction is given comes from the relative ratio of the two alphas.
		a = _:(Float:a + fraction),
		fraction = fraction / Float:a,

		// The final alpha comes from their sum, as a fraction of 1.
		a = floatround(Float:a * 255.0);
	}
	if (fraction >= 1.0)
	{
		return endColour;
	}
    if (fraction <= 0.0)
	{
		return startColour;
	}
	new
		// Gamma decode the colour channels.
		Float:r1 = floatpower((startColour >>> 24       ) / 255.0, FLOAT_GAMMA),
		Float:g1 = floatpower((startColour >>> 16 & 0xFF) / 255.0, FLOAT_GAMMA),
		Float:b1 = floatpower((startColour >>>  8 & 0xFF) / 255.0, FLOAT_GAMMA),
		Float:r2 = floatpower((endColour >>> 24       ) / 255.0, FLOAT_GAMMA),
		Float:g2 = floatpower((endColour >>> 16 & 0xFF) / 255.0, FLOAT_GAMMA),
		Float:b2 = floatpower((endColour >>>  8 & 0xFF) / 255.0, FLOAT_GAMMA),
		// Interpolate and encode.
		Float:r3 = floatpower(r1 + (r2 - r1) * fraction, FLOAT_INVERSE_GAMMA) * 255.0,
		Float:g3 = floatpower(g1 + (g2 - g1) * fraction, FLOAT_INVERSE_GAMMA) * 255.0,
		Float:b3 = floatpower(b1 + (b2 - b1) * fraction, FLOAT_INVERSE_GAMMA) * 255.0;
	// Recombine and return.
	return
		(floatround(r3) << 24 & 0xFF000000) |
		(floatround(g3) << 16 & 0x00FF0000) |
		(floatround(b3) <<  8 & 0x0000FF00) |
		(a & 0xFF);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <param name="startColour">One of the two colours.</param>
 * <param name="endColour">The other of the two colours.</param>
 * <param name="fraction">How far to interpolate between the colours.</param>
 * <remarks>
 *   This function takes a value (fraction) which is a distance between the two
 *   endpoints as a fraction.  This fraction is applied to the two colours given
 *   to find a third colour at some point between those two colours.
 *
 *   This function performs gamma interpolation between the colours, which is a
 *   good balance between complexity and perception.
 *
 *   The fraction is optional, and uses the second colour's alpha for blending
 *   if not given.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `InterpolateColourGamma` instead.
stock InterpolateColorGamma(startColour, endColour, Float:fraction = FLOAT_NAN)
{
	Debug_Warning("`InterpolateColorGamma()` called, please use `InterpolateColourGamma()` isntead,");
	return InterpolateColourGamma(startColour, endColour, fraction);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#define FLOAT_SRGB_ADJUST (14.025) // 0.055 * 255.0
#define FLOAT_SRGB_TRANSFORM_LOW  (3294.6) // 12.92 * 255.0
#define FLOAT_SRGB_TRANSFORM_HIGH (269.025) // 1.055 * 255.0
#define FLOAT_SRGB_GAMMA (2.4)
#define FLOAT_SRGB_CUTOFF (11) // 0.04045 * 255

#define FLOAT_CIE_ADJUST (14.025) // 0.055 * 255.0
#define FLOAT_CIE_TRANSFORM_LOW  (3294.6) // 12.92 * 255.0
#define FLOAT_CIE_TRANSFORM_HIGH (269.025) // 1.055 * 255.0
#define FLOAT_CIE_GAMMA     (0.41666666666666666666666666666667) // 1 / 2.4
#define FLOAT_CIE_CUTOFF    (0.0031308)

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <param name="r">The red colour component.</param>
 * <param name="g">The green colour component.</param>
 * <param name="b">The blue colour component.</param>
 * <param name="x">The x return value.</param>
 * <param name="y">The y return value.</param>
 * <param name="z">The z return value.</param>
 * <remarks>
 *   Performs one step of the sRGB to CIE colour space conversion process.  See:
 *
 *      https://en.wikipedia.org/wiki/SRGB#The_reverse_transformation_(sRGB_to_CIE_XYZ)
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock CIEMultiply(Float:r, Float:g, Float:b, &Float:x, &Float:y, &Float:z)
{
	// See: https://en.wikipedia.org/wiki/SRGB#The_reverse_transformation_(sRGB_to_CIE_XYZ)
	x = 0.4124 * r + 0.3576 * g + 0.1805 * b,
	y = 0.2126 * r + 0.7152 * g + 0.0722 * b,
	z = 0.0193 * r + 0.1192 * g + 0.9505 * b;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <summary>
 *   SRGBToCIE(colour, &amp;Float:x, &amp;Float:y, &amp;Float:z);
 * </summary>
 * <param name="colour">The sRGB colour to convert.</param>
 * <param name="x">The x return value.</param>
 * <param name="y">The y return value.</param>
 * <param name="z">The z return value.</param>
 * <remarks>
 *   Converts a colour from sRGB colour space to CIE XYZ colour space.  See:
 *
 *      https://en.wikipedia.org/wiki/SRGB#The_reverse_transformation_(sRGB_to_CIE_XYZ)
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock SRGBToCIE(colour, &Float:x, &Float:y, &Float:z)
{
	// See: https://en.wikipedia.org/wiki/SRGB#The_reverse_transformation_(sRGB_to_CIE_XYZ)
	new
		ir = colour >>> 24       ,
		ig = colour >>> 16 & 0xFF,
		ib = colour >>>  8 & 0xFF,
		Float:fr = ir < FLOAT_SRGB_CUTOFF
			? ir / FLOAT_SRGB_TRANSFORM_LOW
			: floatpower((ir + FLOAT_SRGB_ADJUST) / FLOAT_SRGB_TRANSFORM_HIGH, FLOAT_SRGB_GAMMA),
		Float:fg = ig < FLOAT_SRGB_CUTOFF
			? ig / FLOAT_SRGB_TRANSFORM_LOW
			: floatpower((ig + FLOAT_SRGB_ADJUST) / FLOAT_SRGB_TRANSFORM_HIGH, FLOAT_SRGB_GAMMA),
		Float:fb = ib < FLOAT_SRGB_CUTOFF
			? ib / FLOAT_SRGB_TRANSFORM_LOW
			: floatpower((ib + FLOAT_SRGB_ADJUST) / FLOAT_SRGB_TRANSFORM_HIGH, FLOAT_SRGB_GAMMA);
	x = 0.4124 * fr + 0.3576 * fg + 0.1805 * fb,
	y = 0.2126 * fr + 0.7152 * fg + 0.0722 * fb,
	z = 0.0193 * fr + 0.1192 * fg + 0.9505 * fb;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <summary>
 *   SRGBToCIE(colour, &amp;Float:x, &amp;Float:y, &amp;Float:z);
 * </summary>
 * <param name="a">The alpha to add on.</param>
 * <param name="x">The x return value.</param>
 * <param name="y">The y return value.</param>
 * <param name="z">The z return value.</param>
 * <remarks>
 *   Converts a colour from CIE XYZ colour space to sRGB colour space.  See:
 *
 *      https://en.wikipedia.org/wiki/SRGB#The_forward_transformation_(CIE_XYZ_to_sRGB)
 *
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock CIEToSRGB(a, Float:x, Float:y, Float:z)
{
	// See: https://en.wikipedia.org/wiki/SRGB#The_forward_transformation_(CIE_XYZ_to_sRGB)
	new
		// To linear.
		Float:fr = x *   3.2406 + y * -1.5372 + z * -0.4986,
		Float:fg = x * -0.9689 + y *   1.8758 + z *   0.0415,
		Float:fb = x *   0.0557 + y * -0.2040 + z *   1.0570,
		// To RGB.
		ir = fr <= FLOAT_CIE_CUTOFF
			? floatround(FLOAT_CIE_TRANSFORM_LOW * fr)
			: floatround(FLOAT_CIE_TRANSFORM_HIGH * floatpower(fr, FLOAT_CIE_GAMMA) - FLOAT_CIE_ADJUST),
		ig = fg <= FLOAT_CIE_CUTOFF
			? floatround(FLOAT_CIE_TRANSFORM_LOW * fg)
			: floatround(FLOAT_CIE_TRANSFORM_HIGH * floatpower(fg, FLOAT_CIE_GAMMA) - FLOAT_CIE_ADJUST),
		ib = fb <= FLOAT_CIE_CUTOFF
			? floatround(FLOAT_CIE_TRANSFORM_LOW * fb)
			: floatround(FLOAT_CIE_TRANSFORM_HIGH * floatpower(fb, FLOAT_CIE_GAMMA) - FLOAT_CIE_ADJUST);
	return (ir << 24) | (ig << 16 & 0x00FF0000) | (ib << 8 & 0x0000FF00) | (a & 0xFF);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <summary>
 *   InterpolateColourSRGB(startColour, endColour, Float:fraction);
 * </summary>
 * <param name="startColour">One of the two colours.</param>
 * <param name="endColour">The other of the two colours.</param>
 * <param name="fraction">How far to interpolate between the colours.</param>
 * <remarks>
 *   This function takes a value (fraction) which is a distance between the two
 *   endpoints as a fraction.  This fraction is applied to the two colours given
 *   to find a third colour at some point between those two colours.
 *
 *   This function performs full sRGB colour space interpolation, which is more
 *   exact even than gamma interpolation, but also a lot slower.
 *
 *   The fraction is optional, and uses the second colour's alpha for blending
 *   if not given.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock InterpolateColourSRGB(startColour, endColour, Float:fraction = FLOAT_NAN)
{
	new a = startColour & 0xFF;
	if (IsNaN(fraction))
	{
		// Extract the fraction from the second alpha.
		fraction = (endColour & 0xFF) / 255.0;
		// Use the first alpha for output transparency.
	}
	else
	{
		// Combine the alpha values to give a relative fraction and a final alpha.
		a = _:((a / 255.0) * (1.0 - fraction)),
		fraction = ((endColour & 0xFF) / 255.0) * fraction,

		// The final fraction is given comes from the relative ratio of the two alphas.
		a = _:(Float:a + fraction),
		fraction = fraction / Float:a,

		// The final alpha comes from their sum, as a fraction of 1.
		a = floatround(Float:a * 255.0);
	}
	if (fraction >= 1.0)
	{
		return endColour;
	}
    if (fraction <= 0.0)
	{
		return startColour;
	}
	new
		// Convert colour 1.
		Float:x1, Float:y1, Float:z1,
		Float:x2, Float:y2, Float:z2;
	SRGBToCIE(startColour, x1, y1, z1),
	SRGBToCIE(endColour, x2, y2, z2);
	// Now a simple linear interpolation.
	return CIEToSRGB(a, x1 + (x2 - x1) * fraction, y1 + (y2 - y1) * fraction, z1 + (z2 - z1) * fraction);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <param name="startColour">One of the two colours.</param>
 * <param name="endColour">The other of the two colours.</param>
 * <param name="fraction">How far to interpolate between the colours.</param>
 * <remarks>
 *   This function takes a value (fraction) which is a distance between the two
 *   endpoints as a fraction.  This fraction is applied to the two colours given
 *   to find a third colour at some point between those two colours.
 *
 *   This function performs full sRGB colour space interpolation, which is more
 *   exact even than gamma interpolation, but also a lot slower.
 *
 *   The fraction is optional, and uses the second colour's alpha for blending
 *   if not given.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if __COMPILER_WARNING_SUPPRESSION
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated Use `InterpolateColourSRGB` instead.
stock InterpolateColorSRGB(startColour, endColour, Float:fraction = FLOAT_NAN)
{
	Debug_Warning("`InterpolateColorSRGB()` called, please use `InterpolateColourSRGB()` isntead,");
	return InterpolateColourSRGB(startColour, endColour, fraction);
}

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <summary>
 *   GetNearestColourLinear(colour, const options[], count = sizeof (options));
 * </summary>
 * <param name="colour">The RGB(A) colour to restrict.</param>
 * <param name="options">The list of valid RGB(A) colour options.</param>
 * <param name="count">The size of the options array.</param>
 * <returns>
 *   The INDEX of the nearst colour.  Or <c>-1</c> for errors.
 * </returns>
 * <remarks>
 *   Find the closest colour to the given colour from the array.  Uses RGB colour
 *   space for the distance function, which is not very accurate.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock GetNearestColourLinear(colour, const options[], count = sizeof (options))
{
	new
		idx = -1,
		// Initial huge distance (everything else is closer).
		// We can use integers because there's no `floatsqrt` used.
		distance = cellmax,
		r1 = colour >>> 24,
		g1 = colour >>> 16 & 0xFF,
		b1 = colour >>>  8 & 0xFF,
		r2,
		g2,
		b2,
		cur;
	while (count--)
	{
		// Get the current colour.
		r2 = (options[count] >>> 24) - r1,
		g2 = (options[count] >>> 16 & 0xFF) - g1,
		b2 = (options[count] >>>  8 & 0xFF) - b1,
		// Find the distance.
		cur = (r2 * r2) + (g2 * g2) + (b2 * b2);
		if (cur < distance)
		{
			distance = cur,
			idx = count;
		}
	}
	
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <summary>
 *   GetNearestColourGamma(colour, const options[], count = sizeof (options));
 * </summary>
 * <param name="colour">The RGB(A) colour to restrict.</param>
 * <param name="options">The list of valid RGB(A) colour options.</param>
 * <param name="count">The size of the options array.</param>
 * <returns>
 *   The INDEX of the nearst colour.  Or <c>-1</c> for errors.
 * </returns>
 * <remarks>
 *   Find the closest colour to the given colour from the array.  Uses gamma
 *   colour space for slightly more accuracy.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock GetNearestColourGamma(colour, const options[], count = sizeof (options))
{
	new
		idx = -1,
		// Initial huge distance (everything else is closer).
		Float:distance = FLOAT_INFINITY,
		// Gamma decode the colour channels.
		Float:r1 = floatpower((colour >>> 24       ) / 100.0, FLOAT_GAMMA),
		Float:g1 = floatpower((colour >>> 16 & 0xFF) / 100.0, FLOAT_GAMMA),
		Float:b1 = floatpower((colour >>>  8 & 0xFF) / 100.0, FLOAT_GAMMA),
		Float:r2,
		Float:g2,
		Float:b2,
		Float:cur;
	while (count--)
	{
		// Get the current colour.
		r2 = floatpower((options[count] >>> 24       ) / 100.0, FLOAT_GAMMA) - r1,
		g2 = floatpower((options[count] >>> 16 & 0xFF) / 100.0, FLOAT_GAMMA) - g1,
		b2 = floatpower((options[count] >>>  8 & 0xFF) / 100.0, FLOAT_GAMMA) - b1,
		// Find the distance.
		cur = (r2 * r2) + (g2 * g2) + (b2 * b2);
		if (cur < distance)
		{
			distance = cur,
			idx = count;
		}
	}
	
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <summary>
 *   GetNearestColourGammaCached(colour, const options[], count = sizeof (options));
 * </summary>
 * <param name="colour">The RGB(A) colour to restrict.</param>
 * <param name="options">The list of valid gamma colour options.</param>
 * <param name="count">The size of the options array.</param>
 * <returns>
 *   The INDEX of the nearst colour.  Or <c>-1</c> for errors.
 * </returns>
 * <remarks>
 *   Find the closest colour to the given colour from the array.  Uses gamma
 *   colour space for slightly more accuracy.  Options are in gamma format.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock GetNearestColourGammaCached(colour, const Float:options[][3], count = sizeof (options))
{
	new
		idx = -1,
		// Initial huge distance (everything else is closer).
		Float:distance = FLOAT_INFINITY,
		// Gamma decode the colour channels.
		Float:r1 = floatpower((colour >>> 24       ) / 100.0, FLOAT_GAMMA),
		Float:g1 = floatpower((colour >>> 16 & 0xFF) / 100.0, FLOAT_GAMMA),
		Float:b1 = floatpower((colour >>>  8 & 0xFF) / 100.0, FLOAT_GAMMA),
		Float:r2,
		Float:g2,
		Float:b2,
		Float:cur;
	while (count--)
	{
		// Get the current colour.
		r2 = options[count][0] - r1,
		g2 = options[count][1] - g1,
		b2 = options[count][2] - b1,
		// Find the distance.
		cur = (r2 * r2) + (g2 * g2) + (b2 * b2);
		if (cur < distance)
		{
			distance = cur,
			idx = count;
		}
	}
	
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <summary>
 *   GetNearestColourGamma(colour, const options[], count = sizeof (options));
 * </summary>
 * <param name="colour">The RGB(A) colour to restrict.</param>
 * <param name="options">The list of valid RGB(A) colour options.</param>
 * <param name="count">The size of the options array.</param>
 * <returns>
 *   The INDEX of the nearst colour.  Or <c>-1</c> for errors.
 * </returns>
 * <remarks>
 *   Find the closest colour to the given colour from the array.  Uses SRGB
 *   colour space for the most accuracy.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock GetNearestColourSRGB(colour, const options[], count = sizeof (options))
{
	new
		idx = -1,
		// Initial huge distance (everything else is closer).
		Float:distance = FLOAT_INFINITY,
		Float:cur,
		Float:x1, Float:y1, Float:z1,
		Float:x2, Float:y2, Float:z2;
	// Gamma decode the colour channels.
	SRGBToCIE(colour, x1, y1, z1);
	while (count--)
	{
		// Get the current colour.
		SRGBToCIE(options[count], x2, y2, z2),
		x2 -= x1,
		y2 -= y1,
		z2 -= z1,
		// Find the distance.
		cur = (x2 * x2) + (y2 * y2) + (z2 * z2);
		if (cur < distance)
		{
			distance = cur,
			idx = count;
		}
	}
	
	return idx;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - colour</library>
 * <summary>
 *   GetNearestColourSRGBCached(colour, const options[], count = sizeof (options));
 * </summary>
 * <param name="colour">The RGB(A) colour to restrict.</param>
 * <param name="options">The list of valid SRGB colour options.</param>
 * <param name="count">The size of the options array.</param>
 * <returns>
 *   The INDEX of the nearst colour.  Or <c>-1</c> for errors.
 * </returns>
 * <remarks>
 *   Find the closest colour to the given colour from the array.  Uses SRGB
 *   colour space for the most accuracy.  Options are in SRGB format.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock GetNearestColourSRGBCached(colour, const Float:options[][3], count = sizeof (options))
{
	new
		idx = -1,
		// Initial huge distance (everything else is closer).
		Float:distance = FLOAT_INFINITY,
		Float:cur,
		Float:x1, Float:y1, Float:z1,
		Float:x2, Float:y2, Float:z2;
	// Gamma decode the colour channels.
	SRGBToCIE(colour, x1, y1, z1);
	while (count--)
	{
		// Get the current colour.
		x2 = options[count][0] - x1,
		y2 = options[count][1] - y1,
		z2 = options[count][2] - z1,
		// Find the distance.
		cur = (x2 * x2) + (y2 * y2) + (z2 * z2);
		if (cur < distance)
		{
			distance = cur,
			idx = count;
		}
	}
	
	return idx;
}

#undef FLOAT_GAMMA
#undef FLOAT_INVERSE_GAMMA

#undef FLOAT_CIE_ADJUST
#undef FLOAT_CIE_TRANSFORM_LOW
#undef FLOAT_CIE_TRANSFORM_HIGH
#undef FLOAT_CIE_GAMMA
#undef FLOAT_CIE_CUTOFF
#undef FLOAT_SRGB_ADJUST
#undef FLOAT_SRGB_TRANSFORM_LOW
#undef FLOAT_SRGB_TRANSFORM_HIGH
#undef FLOAT_SRGB_GAMMA
#undef FLOAT_SRGB_CUTOFF

