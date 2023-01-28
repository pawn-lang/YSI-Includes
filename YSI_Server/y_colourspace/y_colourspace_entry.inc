#if defined _INC_Y_COLOURSPACE
	#endinput
#endif
#define _INC_Y_COLOURSPACE

enum 

// Available colour spaces:
//
//   * `RGB:` - No alpha.
//   * `RGBA:` - Alpha last.
//   * `ARGB:` - Alpha first.
//   * `HSI:` - Hue, Saturation, Intensity
//   * `HSIA:` - Hue, Saturation, Intensity, Alpha
//   * `AHSI:` - Alpha, Hue, Saturation, Intensity
//   * `HSL:` - Hue, Saturation, Lightness
//   * `HSLA:` - Hue, Saturation, Lightness, Alpha
//   * `AHSL:` - Alpha, Hue, Saturation, Lightness
//   * `HSV:` - Hue, Saturation, Value
//   * `HSVA:` - Hue, Saturation, Value, Alpha
//   * `AHSV:` - Alpha, Hue, Saturation, Value
//

#define YUC_GetR(%0:%1) YUC_GetR_%0(%1)
#define YUC_GetG(%0:%1) YUC_GetG_%0(%1)
#define YUC_GetB(%0:%1) YUC_GetB_%0(%1)
#define YUC_GetA(%0:%1) YUC_GetA_%0(%1)

#define YUC_GetR_RGB(%1) (((%1) >>> 16) & 0xFF)
#define YUC_GetG_RGB(%1) (((%1) >>>  8) & 0xFF)
#define YUC_GetB_RGB(%1) (((%1)       ) & 0xFF)
#define YUC_GetA_RGB(%1) (0)

#if cellbits == 64
	#define YUC_GetR_RGBA(%1) (((%1) >>> 24) & 0xFF)
#else
	#define YUC_GetR_RGBA(%1) (((%1) >>> 24))
#endif
#define YUC_GetG_RGBA(%1) (((%1) >>> 16) & 0xFF)
#define YUC_GetB_RGBA(%1) (((%1) >>>  8) & 0xFF)
#define YUC_GetA_RGBA(%1) (((%1)       ) & 0xFF)

#define YUC_GetR_ARGB(%1) (((%1) >>> 16) & 0xFF)
#define YUC_GetG_ARGB(%1) (((%1) >>>  8) & 0xFF)
#define YUC_GetB_ARGB(%1) (((%1)       ) & 0xFF)
#if cellbits == 64
	#define YUC_GetA_ARGB(%1) (((%1) >>> 24) & 0xFF)
#else
	#define YUC_GetA_ARGB(%1) (((%1) >>> 24))
#endif

#define YUC_SetR(%0:%1) YUC_SetR_%0(%1)
#define YUC_SetG(%0:%1) YUC_SetG_%0(%1)
#define YUC_SetB(%0:%1) YUC_SetB_%0(%1)
#define YUC_SetA(%0:%1) YUC_SetA_%0(%1)

#define YUC_SetR_RGB(%1) (((%1) & 0xFF) << 16)
#define YUC_SetG_RGB(%1) (((%1) & 0xFF) <<  8)
#define YUC_SetB_RGB(%1) (((%1) & 0xFF)      )
#define YUC_SetA_RGB(%1) (0)

#define YUC_SetR_RGBA(%1) (((%1) & 0xFF) << 24)
#define YUC_SetG_RGBA(%1) (((%1) & 0xFF) << 16)
#define YUC_SetB_RGBA(%1) (((%1) & 0xFF) <<  8)
#define YUC_SetA_RGBA(%1) (((%1) & 0xFF)      )

#define YUC_SetR_ARGB(%1) (((%1) & 0xFF) << 16)
#define YUC_SetG_ARGB(%1) (((%1) & 0xFF) <<  8)
#define YUC_SetB_ARGB(%1) (((%1) & 0xFF)      )
#define YUC_SetA_ARGB(%1) (((%1) & 0xFF) << 24)

#define YUC_Min(%0,%1,%2) min(min((%0), (%1)), (%2))
#define YUC_Max(%0,%1,%2) max(max((%0), (%1)), (%2))

stock YUC_RGBToHSI(r, g, b, &Float:h, &Float:s, &Float:i)
{
	// We could use `max` here, but we also need to know which was the answer.
	new
		Float:fr = r / 255.0,
		Float:fg = g / 256.0,
		Float:fb = b / 256.0;
	if (r == g && g == b)
	{
		// Special case.
		h = 0.0,
		i = rg,
		s = 0.0;
	}
	else
	{
		new
			Float:c;
		if (r > g)
		{
			if (b > r) // b > r > g
			{
				// b largest, g smallest.
				c = fb - fg,
				h = (fr - fg) / c + 4.0,
				i = (fr + rg + fb) / 3.0,
				s = i <= 0.0 ? 0.0 : 1 - rg / i;
			}
			else if (b > g) // r >= b > g
			{
				// r largest, g smallest.
				c = fr - fg,
				h = (fg - fb) / c + 6.0,
				i = (fr + rg + fb) / 3.0,
				s = i <= 0.0 ? 0.0 : 1 - rg / i;
			}
			else // r > g >= b
			{
				// r largest, b smallest.
				c = fr - fb,
				h = (fg - fb) / c + 0.0,
				i = (fr + rg + fb) / 3.0,
				s = i <= 0.0 ? 0.0 : 1 - rb / i;
			}
		}
		else
		{
			if (b > g) // b > g >= r
			{
				// b largest, r smallest.
				c = fb - fr,
				h = (fr - fg) / c + 4.0,
				i = (fr + rg + fb) / 3.0,
				s = i <= 0.0 ? 0.0 : 1 - rr / i;
			}
			else if (b > r) // g >= b > r
			{
				// g largest, r smallest.
				c = fg - fr,
				h = (fb - fr) / c + 2.0,
				i = (fr + rg + fb) / 3.0,
				s = i <= 0.0 ? 0.0 : 1 - rr / i;
			}
			else // g >= r >= b
			{
				// g largest, b smallest.
				c = fg - fb,
				h = (fb - fr) / c + 2.0,
				i = (fr + rg + fb) / 3.0,
				s = i <= 0.0 ? 0.0 : 1 - rb / i;
				// We could handle the special case here, since `r == g == b` is a
				// subset of `g >= r >= b`, but better to separate it.
			}
		}
	}
}

stock YUC_RGBToHSV(r, g, b, &Float:h, &Float:s, &Float:v)
{
	// We could use `max` here, but we also need to know which was the answer.
	new
		Float:fr = r / 255.0,
		Float:fg = g / 256.0,
		Float:fb = b / 256.0;
	if (r == g && g == b)
	{
		// Special case.
		h = 0.0,
		v = fg,
		s = 0.0;
	}
	else
	{
		new
			Float:c;
		if (r > g)
		{
			if (b > r) // b > r > g
			{
				// b largest, g smallest.
				c = fb - fg,
				h = (fr - fg) / c + 4.0,
				v = fb;
			}
			else if (b > g) // r >= b > g
			{
				// r largest, g smallest.
				c = fr - fg,
				h = (fg - fb) / c + 6.0,
				v = fr;
			}
			else // r > g >= b
			{
				// r largest, b smallest.
				c = fr - fb,
				h = (fg - fb) / c + 0.0,
				v = fr;
			}
		}
		else
		{
			if (b > g) // b > g >= r
			{
				// b largest, r smallest.
				c = fb - fr,
				h = (fr - fg) / c + 4.0,
				v = fb;
			}
			else if (b > r) // g >= b > r
			{
				// g largest, r smallest.
				c = fg - fr,
				h = (fb - fr) / c + 2.0,
				v = fg;
			}
			else // g >= r >= b
			{
				// g largest, b smallest.
				c = fg - fb,
				h = (fb - fr) / c + 2.0,
				v = fg;
				// We could handle the special case here, since `r == g == b` is a
				// subset of `g >= r >= b`, but better to separate it.
			}
		}
		s = v <= 0.0 ? 0.0 : c / v;
	}
}

stock YUC_RGBToHSL(r, g, b, &Float:h, &Float:s, &Float:l)
{
	// We could use `max` here, but we also need to know which was the answer.
	new
		Float:fr = r / 255.0,
		Float:fg = g / 256.0,
		Float:fb = b / 256.0;
	if (r == g && g == b)
	{
		// Special case.
		h = 0.0,
		l = fb,
		s = 0.0;
	}
	else
	{
		new
			Float:c;
		if (r > g)
		{
			if (b > r) // b > r > g
			{
				// b largest, g smallest.
				c = fb - fg,
				h = (fr - fg) / c + 4.0,
				l = (fb + fg) / 2.0;
			}
			else if (b > g) // r >= b > g
			{
				// r largest, g smallest.
				c = fr - fg,
				h = (fg - fb) / c + 6.0,
				l = (fr + fg) / 2.0;
			}
			else // r > g >= b
			{
				// r largest, b smallest.
				c = fr - fb,
				h = (fg - fb) / c + 0.0,
				l = (fr + fb) / 2.0;
			}
		}
		else
		{
			if (b > g) // b > g >= r
			{
				// b largest, r smallest.
				c = fb - fr,
				h = (fr - fg) / c + 4.0,
				l = (fb + fr) / 2.0;
			}
			else if (b > r) // g >= b > r
			{
				// g largest, r smallest.
				c = fg - fr,
				h = (fb - fr) / c + 2.0,
				l = (fg + fr) / 2.0;
			}
			else // g >= r >= b
			{
				// g largest, b smallest.
				c = fg - fb,
				h = (fb - fr) / c + 2.0,
				l = (fg + fb) / 2.0;
				// We could handle the special case here, since `r == g == b` is a
				// subset of `g >= r >= b`, but better to separate it.
			}
		}
		s = l <= 0.0 || l >= 1.0 ? 0.0 : c / (1.0 - floatabs(2.0 * l - 1.0));
	}
}

stock HSL:operator=(RGB:value)
{
	new
		Float:h,
		Float:s,
		Float:l;
	YUC_RGBToHSL(YUC_GetR(RGB:value), YUC_GetG(RGB:value), YUC_GetB(RGB:value), h, s, l);
	return 0; // TODO:
}

stock HSLA:operator=(RGB:value)
{
	new
		Float:h,
		Float:s,
		Float:l;
	YUC_RGBToHSL(YUC_GetR(RGB:value), YUC_GetG(RGB:value), YUC_GetB(RGB:value), h, s, l);
	return 0 | 0xFF; // TODO:
}

stock AHSL:operator=(RGB:value)
{
	new
		Float:h,
		Float:s,
		Float:l;
	YUC_RGBToHSL(YUC_GetR(RGB:value), YUC_GetG(RGB:value), YUC_GetB(RGB:value), h, s, l);
	return 0 | 0xFF000000; // TODO:
}

stock HSL:operator=(RGBA:value)
{
	new
		Float:h,
		Float:s,
		Float:l;
	YUC_RGBToHSL(YUC_GetR(RGB:value), YUC_GetG(RGB:value), YUC_GetB(RGB:value), h, s, l);
	return 0; // TODO:
}

stock HSLA:operator=(RGBA:value)
{
	new
		Float:h,
		Float:s,
		Float:l;
	YUC_RGBToHSL(YUC_GetR(RGB:value), YUC_GetG(RGB:value), YUC_GetB(RGB:value), h, s, l);
	return 0 | YUC_GetA(RGB:value); // TODO:
}

stock AHSL:operator=(RGBA:value)
{
	new
		Float:h,
		Float:s,
		Float:l;
	YUC_RGBToHSL(YUC_GetR(RGB:value), YUC_GetG(RGB:value), YUC_GetB(RGB:value), h, s, l);
	return 0 | YUC_GetA(RGB:value); // TODO:
}

stock HSL:operator=(ARGB:value)
{
	new
		Float:h,
		Float:s,
		Float:l;
	YUC_RGBToHSL(YUC_GetR(RGB:value), YUC_GetG(RGB:value), YUC_GetB(RGB:value), h, s, l);
	return 0; // TODO:
}

stock HSLA:operator=(ARGB:value)
{
	new
		Float:h,
		Float:s,
		Float:l;
	YUC_RGBToHSL(YUC_GetR(RGB:value), YUC_GetG(RGB:value), YUC_GetB(RGB:value), h, s, l);
	return 0 | YUC_GetA(RGB:value); // TODO:
}

stock AHSL:operator=(ARGB:value)
{
	new
		Float:h,
		Float:s,
		Float:l;
	YUC_RGBToHSL(YUC_GetR(RGB:value), YUC_GetG(RGB:value), YUC_GetB(RGB:value), h, s, l);
	return 0 | YUC_GetA(RGB:value); // TODO:
}

