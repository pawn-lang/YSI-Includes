/**
 * <library
 *   name="y_utils - random"
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

#define YSI_RANGE(%0,%1) ((%1) - (%0))
#define YSI_RANDOM(%0,%1) (YSI_Random__(YSI_RANGE(%0, %1)) + (%0))

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <remarks>
 *   Relatively high quality 32-bit PRNG.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if cellbits == 32
	stock RandomMulberry32()
#else
	static stock RandomMulberry32__()
#endif
{
	static s = 0;

	// z = (s += 0x6D2B79F5);
	#emit LOAD.pri     s
	#emit ADD.C        0x6D2B79F5
	#emit STOR.pri     s

	// z = (z ^ z >>> 15) * (1 | z);
	#emit MOVE.alt
	#emit SHR.C.pri    15
	#emit XOR
	#emit PUSH.pri
	#emit CONST.pri    1
	#emit OR
	#emit POP.alt
	#emit UMUL

	// z ^= z + (z ^ z >>> 7) * (61 | z);
	#emit PUSH.pri
	#emit MOVE.alt
	#emit SHR.C.pri    7
	#emit XOR
	#emit PUSH.pri
	#emit CONST.pri    61
	#emit OR
	#emit POP.alt
	#emit UMUL
	#emit POP.alt
	#emit ADD
	#emit XOR

	// return z ^ z >>> 14;
	#emit MOVE.alt
	#emit SHR.C.pri    14
	#emit XOR
	#emit RETN

	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <remarks>
 *   Relatively high quality 32-bit PRNG.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if cellbits == 64
	stock RandomMulberry32()
#else
	static stock RandomMulberry32__()
#endif
{
	static s = 0;

	// z = (s += 0x6D2B79F5);
	#emit LOAD.pri     s
	#emit ADD.C        0x6D2B79F5
	#emit STOR.pri     s

	// z = (z ^ z >>> 15) * (1 | z);
	#emit CONST.alt    0xFFFFFFFF
	#emit AND
	#emit MOVE.alt
	#emit SHR.C.pri    15
	#emit XOR
	#emit PUSH.pri
	#emit CONST.pri    1
	#emit OR
	#emit POP.alt
	#emit UMUL

	// z ^= z + (z ^ z >>> 7) * (61 | z);
	#emit CONST.alt    0xFFFFFFFF
	#emit AND
	#emit PUSH.pri
	#emit MOVE.alt
	#emit SHR.C.pri    7
	#emit XOR
	#emit PUSH.pri
	#emit CONST.pri    61
	#emit OR
	#emit POP.alt
	#emit UMUL
	#emit POP.alt
	#emit ADD
	#emit XOR

	// return z ^ z >>> 14;
	#emit CONST.alt    0xFFFFFFFF
	#emit AND
	#emit MOVE.alt
	#emit SHR.C.pri    14
	#emit XOR
	#emit RETN

	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <remarks>
 *   Slightly lower quality 32-bit PRNG.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if cellbits == 32
	stock RandomSplitMix32()
#else
	static stock RandomSplitMix32__()
#endif
{
	static s = 0;

	// z = (s += 0x9E3779B9);
	#emit LOAD.pri     s
	#emit ADD.C        0x9E3779B9
	#emit STOR.pri     s

	// z ^= z >> 15;
	#emit MOVE.alt
	#emit SHR.C.pri    15
	#emit XOR

	// z *= 0x85EBCA6B;
	#emit CONST.alt    0x85EBCA6B
	#emit UMUL

	// z ^= z >> 13;
	#emit MOVE.alt
	#emit SHR.C.pri    13
	#emit XOR

	// z *= 0xC2B2AE35;
	#emit CONST.alt    0xC2B2AE35
	#emit UMUL

	// return z ^= z >> 16;
	#emit MOVE.alt
	#emit SHR.C.pri    16
	#emit XOR
	#emit RETN

	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <remarks>
 *   Slightly lower quality 32-bit PRNG.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#if cellbits == 64
	stock RandomSplitMix32()
#else
	static stock RandomSplitMix32__()
#endif
{
	static s = 0;

	// z = (s += 0x9E3779B9);
	#emit LOAD.pri     s
	#emit ADD.C        0x9E3779B9
	#emit STOR.pri     s

	// z ^= z >> 15;
	#emit CONST.alt    0xFFFFFFFF
	#emit AND
	#emit MOVE.alt
	#emit SHR.C.pri    15
	#emit XOR

	// z *= 0x85EBCA6B;
	#emit CONST.alt    0x85EBCA6B
	#emit UMUL

	// z ^= z >> 13;
	#emit CONST.alt    0xFFFFFFFF
	#emit AND
	#emit MOVE.alt
	#emit SHR.C.pri    13
	#emit XOR

	// z *= 0xC2B2AE35;
	#emit CONST.alt    0xC2B2AE35
	#emit UMUL

	// return z ^= z >> 16;
	#emit CONST.alt    0xFFFFFFFF
	#emit AND
	#emit MOVE.alt
	#emit SHR.C.pri    16
	#emit XOR
	#emit RETN

	__pragma("naked");
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <param name="minOrMax">Upper bound, or lower bound with 2+ parameters or when less than naught.</param>
 * <param name="max">Upper bound.</param>
 * <param>Value(s) to not return.</param>
 * <remarks>
 *   Generate a random number between the given numbers (min &lt;= n &lt; max).
 *   Default minimum is 0 (changes the parameter order).  This uses a compile-
 *   time macro to detect the number of parameters and adjust the implementation
 *   accordingly.  Also when there is only one parameter and it is below naught,
 *   it uses naught as the max and the parameter as the min instead.  Won't
 *   return the value <c>except</c> if it is between the limits.  So can be
 *   called with one, two, or three parameters.  Don't try
 *   <c>Random(0, _, 2);</c> for example, it won't work.  With more than two
 *   parameters all the rest are numbers that should not be returned.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Random(minOrMax, max, ...)
{
	// Here for documentation only.
	return 0;
}
 
/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <param name="min">Lower bound.</param>
 * <param name="max">Upper bound.</param>
 * <param name="">Values to not return.</param>
 * <remarks>
 *   Generate a random number between the given numbers (min &lt;= n &lt; max).
 *   Default minimum is 0 (changes the parameter order).  Won't return any of
 *   the extra parameter values, so you can do:
 *   <code>
 *     Random(0, 20, 11, 12, 13);
 *   </code>
 *   To randomly select <c>0-10, 14-19</c> (inclusive).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RandomMinMaxExceptMany(min, max, ...)
{
	assert(min < max);
	// This can't use the same technique as `RandomMinMaxExcept`, because the
	// exception values may not be unique.  That method would fail miserably
	// with `RandomMinMaxExceptMany(0, 4, 1, 1, 1, 1);`
	new args = numargs();
	//new valid = 0;
	//// Count how many excluded values are actually within the random selection
	//// range.
	//for (new i = 2; i != args; ++i)
	//{
	//	if (min <= getarg(i) < max)
	//	{
	//		++valid;
	//	}
	//}
	// Instead we will have to first check that there are valid candidates
	// returns.
	for (new i = min, j; i != max; ++i)
	{
		j = 1;
		while (++j != args)
		{
			// Check if any of the exceptions match this input value.
			if (getarg(j) == i)
			{
				break;
			}
		}
		if (j == args)
		{
			// There is at least one number that can be returned.
			for ( ; ; )
			{
				// Get a random number.
				i = YSI_RANDOM(min, max);
				// Check if it is invalid.
				j = 1;
				while (++j != args)
				{
					// Check if any of the exceptions match this input value.
					if (getarg(j) == i)
					{
						break;
					}
				}
				if (j == args)
				{
					// Not found;
					return i;
				}
			}
		}
	}
	// Will probably fail.  If you get an exception here you called the code
	// with an invalid set of values.
	assert(numargs() == 0);
	return max;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <param name="min">Lower bound.</param>
 * <param name="max">Upper bound.</param>
 * <param name="except">Value to not return.</param>
 * <remarks>
 *   Generate a random number between the given numbers (min &lt;= n &lt; max).
 *   Won't return the value <c>except</c> if it is between the limits.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RandomMinMaxExcept(min, max, except)
{
	assert(min < max);
	if (min <= except < max)
	{
		// Select from one fewer random numbers, and shift the results.
		return (max = YSI_Random__(max - 1 - min) + min) + _:(max >= except);
	}
	else
	{
		// The ignored value is outside the range we care about.
		return YSI_Random__(max - min) + min;
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <param name="min">Lower bound.</param>
 * <param name="max">Upper bound.</param>
 * <remarks>
 *   Generate a random number  between the given numbers (min &lt;= n &lt; max).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RandomMinMax(min, max)
{
	assert(min < max);
	return YSI_Random__(max - min) + min;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <param name="max">Upper bound.</param>
 * <remarks>
 *   Generate a random number between the given numbers (min &lt;= n &lt; max).
 *   Default minimum is 0 (changes the parameter order).  This uses a compile-
 *   time macro to detect the number of parameters and adjust the implementation
 *   accordingly.  Also when there is only one parameter and it is below naught,
 *   it uses naught as the max and the parameter as the min instead.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RandomMax(max)
{
	if (max < 0)
	{
		return -YSI_Random__(-max);
	}
	return YSI_Random__(max);
}

// The macro to detect one parameter.
#define Random(%0) RandomMax(%0)PP_DISCARD$

// The macro to detect two parameters.
#define RandomMax(%0,%1)PP_DISCARD$ RandomMinMax(%0,%1)PP_DISCARD$

// The macro to detect three parameters.
#define RandomMinMax(%0,%1,%2)PP_DISCARD$ RandomMinMaxExcept(%0,%1,%2)PP_DISCARD$

// The macro to detect many parameters.
#define RandomMinMaxExcept(%0,%1,%2,%3)PP_DISCARD$ RandomMinMaxExceptMany(%0,%1,%2,%3)PP_DISCARD$

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <param name="min">Lower bound, or upper bound when only parameter.</param>
 * <param name="max">Upper bound.</param>
 * <param name="dp">How small to make the differences</param>
 * <remarks>
 *   Generate a random float between the given numbers (min &lt;= n &lt; max).
 *   Default minimum is 0.0 (changes the parameter order).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Float:RandomFloatMinMax(Float:min, Float:max = FLOAT_NAN, dp = 2)
{
	switch (dp)
	{
	case 0: dp = _:(1.0);
	case 1: dp = _:(10.0);
	case 2: dp = _:(100.0);
	case 3: dp = _:(1000.0);
	case 4: dp = _:(10000.0);
	//case 5: dp = _:(100000.0);
	//case 6: dp = _:(1000000.0);
	default:
	{
		Debug_Warning("Large `dp` values may produce incorrect results.");
		dp = _:floatpower(10.0, float(dp));
	}
	}
	//printf("%02f", Float:dp);
	//printf("%02f", max * (Float:dp) - min * (Float:dp));
	//printf("%02f", floatround(max * (Float:dp) - min * (Float:dp)));
	//printf("%02f", float(random(floatround(max * (Float:dp) - min * (Float:dp)))) / (Float:dp));
	if (IsNaN(max))
	{
		if (min < 0.0)
			return -(float(random(floatround(-min * (Float:dp)))) / (Float:dp));
		return float(random(floatround(min * (Float:dp)))) / (Float:dp);
	}
	// Parameters are the wrong way around - do it anyway.
	if (max < min)
		return float(random(floatround(min * (Float:dp) - max * (Float:dp)))) / (Float:dp) + max;
	return float(random(floatround(max * (Float:dp) - min * (Float:dp)))) / (Float:dp) + min;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <param name="max">Upper bound.</param>
 * <remarks>
 *   Generate a random float between <c>0 &lt;= n &lt; max</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Float:RandomFloatMax(Float:max)
{
	return float(random(floatround(max * 8192.0))) / 8192.0;
}

// The macro to detect one parameter.
#define RandomFloat(%0) RandomFloatMax(%0)PP_DISCARD$

// The macro to detect two+ parameters.
#define RandomFloatMax(%0,%1)PP_DISCARD$ RandomFloatMinMax(%0,%1)PP_DISCARD$

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <summary>
 *   Get an array of random points in a circle.
 * </summary>
 * <param name="centreX">The x co-ordinate of the centre of the circle.</param>
 * <param name="centreY">The y co-ordinate of the centre of the circle.</param>
 * <param name="radius">The size (radius) of the circle.</param>
 * <param name="xs">The return array for the random x co-ordinates.</param>
 * <param name="ys">The return array for the random y co-ordinates.</param>
 * <param name="sx">The size of the x return array (must match <c>sy</c>.</param>
 * <param name="sy">The size of the y return array (must match <c>sx</c>.</param>
 * <remarks>
 *   Most basic method.  Generate points in a square and test them.  Simple but
 *   unbounded.  Good distribution.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RandomPointsInCircleSampled(Float:centreX, Float:centreY, Float:radius, Float:xs[], Float:ys[], sx = sizeof (xs), sy = sizeof (ys))
{
	assert(sx == sy);
	new Float:randX, Float:randY;
	new Float:minX = centreX - radius, Float:minY = centreY - radius;
	new Float:maxX = centreX + radius, Float:maxY = centreY + radius;
	for (sx = 0; sx != sy; )
	{
		randX = RandomFloat(minX, maxX);
		randY = RandomFloat(minY, maxY);
		if (VectorSize(centreX - randX, centreY - randY, 0.0) < radius)
		{
			xs[sx] = randX;
			ys[sx] = randY;
			++sx;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <summary>
 *   Get an array of random points in a circle.
 * </summary>
 * <param name="centreX">The x co-ordinate of the centre of the circle.</param>
 * <param name="centreY">The y co-ordinate of the centre of the circle.</param>
 * <param name="radius">The size (radius) of the circle.</param>
 * <param name="xs">The return array for the random x co-ordinates.</param>
 * <param name="ys">The return array for the random y co-ordinates.</param>
 * <param name="sx">The size of the x return array (must match <c>sy</c>.</param>
 * <param name="sy">The size of the y return array (must match <c>sx</c>.</param>
 * <remarks>
 *   Medium method.  Generate an angle and distance.  Fixed loop bounds, but
 *   worst distribution (although actually the best distribution if you want more
 *   near the centre, as in an explosion).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RandomPointsInCircleCentred(Float:centreX, Float:centreY, Float:radius, Float:xs[], Float:ys[], sx = sizeof (xs), sy = sizeof (ys))
{
	assert(sx == sy);
	new Float:randA, Float:randD;
	for (sx = 0; sx != sy; ++sx)
	{
		randA = RandomFloat(360.0);
		randD = RandomFloat(radius);
		xs[sx] = randD * floatsin(randA, degrees) + centreX;
		ys[sx] = randD * floatsin(randA, degrees) + centreY;
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <summary>
 *   Get an array of random points in a circle.
 * </summary>
 * <param name="centreX">The x co-ordinate of the centre of the circle.</param>
 * <param name="centreY">The y co-ordinate of the centre of the circle.</param>
 * <param name="radius">The size (radius) of the circle.</param>
 * <param name="xs">The return array for the random x co-ordinates.</param>
 * <param name="ys">The return array for the random y co-ordinates.</param>
 * <param name="sx">The size of the x return array (must match <c>sy</c>.</param>
 * <param name="sy">The size of the y return array (must match <c>sx</c>.</param>
 * <remarks>
 *   Best method.  Generate an angle and distance, but adjusted for a perfect
 *   distribution of points throughout the circle.  Fixed loop bounds.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RandomPointsInCircleDistributed(Float:centreX, Float:centreY, Float:radius, Float:xs[], Float:ys[], sx = sizeof (xs), sy = sizeof (ys))
{
	assert(sx == sy);
	new Float:randA, Float:randD;
	for (sx = 0; sx != sy; ++sx)
	{
		randA = RandomFloat(360.0);
		randD = radius * floatsqroot(RandomFloat(1.0));
		xs[sx] = randD * floatsin(randA, degrees) + centreX;
		ys[sx] = randD * floatsin(randA, degrees) + centreY;
	}
}

#define RandomPointsInCircle RandomPointsInCircleDistributed

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <summary>
 *   Get a random point in a circle.
 * </summary>
 * <param name="centreX">The x co-ordinate of the centre of the circle.</param>
 * <param name="centreY">The y co-ordinate of the centre of the circle.</param>
 * <param name="radius">The size (radius) of the circle.</param>
 * <param name="outX">The return for the random x co-ordinate.</param>
 * <param name="outY">The return for the random y co-ordinate.</param>
 * <remarks>
 *   Most basic method.  Generate points in a square and test them.  Simple but
 *   unbounded.  Good distribution.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RandomPointInCircleSampled(Float:centreX, Float:centreY, Float:radius, &Float:outX, &Float:outY)
{
	new Float:minX = centreX - radius, Float:minY = centreY - radius;
	new Float:maxX = centreX + radius, Float:maxY = centreY + radius;
	for ( ; ; )
	{
		outX = RandomFloat(minX, maxX);
		outY = RandomFloat(minY, maxY);
		if (VectorSize(centreX - outX, centreY - outY, 0.0) < radius)
		{
			return;
		}
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <summary>
 *   Get a random point in a circle.
 * </summary>
 * <param name="centreX">The x co-ordinate of the centre of the circle.</param>
 * <param name="centreY">The y co-ordinate of the centre of the circle.</param>
 * <param name="radius">The size (radius) of the circle.</param>
 * <param name="outX">The return for the random x co-ordinate.</param>
 * <param name="outY">The return for the random y co-ordinate.</param>
 * <remarks>
 *   Medium method.  Generate an angle and distance.  Fixed loop bounds, but
 *   worst distribution (although actually the best distribution if you want more
 *   near the centre, as in an explosion).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RandomPointInCircleCentred(Float:centreX, Float:centreY, Float:radius, &Float:outX, &Float:outY)
{
	new Float:randA = RandomFloat(360.0);
	new Float:randD = RandomFloat(radius);
	outX = randD * floatsin(randA, degrees) + centreX;
	outY = randD * floatsin(randA, degrees) + centreY;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <summary>
 *   Get a random point in a circle.
 * </summary>
 * <param name="centreX">The x co-ordinate of the centre of the circle.</param>
 * <param name="centreY">The y co-ordinate of the centre of the circle.</param>
 * <param name="radius">The size (radius) of the circle.</param>
 * <param name="outX">The return for the random x co-ordinate.</param>
 * <param name="outY">The return for the random y co-ordinate.</param>
 * <remarks>
 *   Best method.  Generate an angle and distance, but adjusted for a perfect
 *   distribution of points throughout the circle.  Fixed loop bounds.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock RandomPointInCircleDistributed(Float:centreX, Float:centreY, Float:radius, &Float:outX, &Float:outY)
{
	new Float:randA = RandomFloat(360.0);
	new Float:randD = radius * floatsqroot(RandomFloat(1.0));
	outX = randD * floatsin(randA, degrees) + centreX;
	outY = randD * floatsin(randA, degrees) + centreY;
}

#define RandomPointInCircle RandomPointInCircleDistributed

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <summary>
 *   TryPercentage(percentage);
 * </summary>
 * <param name="percentage">The likelihood of returning <c>true</c>.</param>
 * <returns>
 *   <c>true</c>, <c>percentage%</c> of the time; or <c>false</c>
 * </returns>
 * <remarks>
 *   Basically a percentage random number generator.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:TryPercentage(percentage)
{
	return random(100) < percentage;
}

#define TryPercentage(%0) (random(100) < (%0))
#define _ALS_TryPercentage

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <summary>
 *   TryPermille(permille);
 * </summary>
 * <param name="permille">The likelihood of returning <c>true</c>.</param>
 * <returns>
 *   <c>true</c>, <c>permille%o</c> of the time; or <c>false</c>
 * </returns>
 * <remarks>
 *   Basically a permille random number generator (that's out of 1000).  Could be
 *   used to replicate something with a <c>42.1%</c> chance of happening via:
 *   <br />
 *   <c>TryPermille(421)</c>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:TryPermille(permille)
{
	return random(1000) < permille;
}

#define TryPermille(%0) (random(1000) < (%0))
#define _ALS_TryPermille

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <summary>
 *   TryPPM(ppm);
 * </summary>
 * <param name="ppm">The likelihood of returning <c>true</c>.</param>
 * <returns>
 *   <c>true</c>, <c>ppm%oooo</c> of the time; or <c>false</c>
 * </returns>
 * <remarks>
 *   Basically a ppm random number generator (that's out of 1000000).  Could be
 *   used to replicate something with a <c>1.0001%</c> chance of happening via:
 *   <br />
 *   <c>TryPPM(10001)</c>
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:TryPPM(ppm)
{
	return random(1000000) < ppm;
}

#define TryPPM(%0) (random(1000000) < (%0))
#define _ALS_TryPPM

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <param name="output">The optional string to write to.</param>
 * <param name="cased">Allow both upper- and lower-case letters.</param>
 * <param name="grouped">Groups of characters have equal probability.</param>
 * <param name="len">The size of the string.</param>
 * <returns>
 *   A random character.
 * </returns>
 * <remarks>
 *   Can be used to return a character or a string.  Use the return value with
 *   no parameters for a single character, or pass a destination array for a
 *   string.
 *   <p />
 *   Selects letters from <c>A</c> to <c>Z</c>, or also <c>a</c> to <c>z</c> if
 *   <c>cased</c> is <c>true</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

/*stock RandomAlpha(output[] = "", cased = false, grouped = false, len = sizeof (output))
{
	// There are only two possible groups (upper- and lower-case letters), and
	// both have the same number of elements, so `grouped` being on or off will
	// give the same results.
	#pragma unused grouped
	new
		i = -1,
		ch;
	--len;
	do
	{
		if (cased)
		{
			ch = YSI_Random__(YSI_RANGE('A', 'Z' + 1) + YSI_RANGE('a', 'z' + 1)),
			ch =
				(ch >= YSI_RANGE('A', 'Z' + 1)) ? ch + ('a' - YSI_RANGE('A', 'Z' + 1)) :
				ch + 'A';
		}
		else
		{
			ch = YSI_RANDOM('A', 'Z' + 1);
		}
		output[++i] = ch;
	}
	while (i != len);
	output[len] = '\0';
	return ch;
}*/

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - random</library>
 * <param name="output">The optional string to write to.</param>
 * <param name="cased">Allow both upper- and lower-case letters.</param>
 * <param name="grouped">Groups of characters have equal probability.</param>
 * <param name="len">The size of the string.</param>
 * <returns>
 *   A random character.
 * </returns>
 * <remarks>
 *   Can be used to return a character or a string.  Use the return value with
 *   no parameters for a single character, or pass a destination array for a
 *   string.
 *   <p />
 *   Selects letters from <c>a</c> to <c>z</c>, <c>A</c> to <c>Z</c>, or
 *   numbers; with every character having equal likelihood.  Unless
 *   <c>grouped</c> is true, in which case numbers are just as likely to appear
 *   as upper- or lower-case letters.
 * </remarks>
 *//*------------------------------------------------------------------------**/

/*stock RandomAlphaNum(output[] = "", cased = false, grouped = false, len = sizeof (output))
{
	new
		i = -1,
		ch;
	--len;
	do
	{
		if (grouped)
		{
			if (cased) switch (YSI_Random__(3))
			{
			case 0:
				ch = YSI_RANDOM('0', '9' + 1);
			case 1:
				ch = YSI_RANDOM('A', 'Z' + 1);
			case 2:
				ch = YSI_RANDOM('a', 'z' + 1);
			}
			else switch (YSI_Random__(2))
			{
			case 0:
				ch = YSI_RANDOM('0', '9' + 1);
			case 1:
				ch = YSI_RANDOM('A', 'Z' + 1);
			}
		}
		else
		{
			if (cased)
			{
				ch = YSI_Random__(YSI_RANGE('0', '9' + 1) + YSI_RANGE('A', 'Z' + 1) + YSI_RANGE('a', 'z' + 1)),
				ch =
					(ch >= YSI_RANGE('A', 'Z' + 1) + YSI_RANGE('a', 'z' + 1)) ? ch + ('0' - YSI_RANGE('A', 'Z' + 1) - YSI_RANGE('a', 'z' + 1)) :
					(ch >= YSI_RANGE('A', 'Z' + 1)) ? ch + ('a' - YSI_RANGE('A', 'Z' + 1)) :
					ch + 'A';
			}
			else
			{
				ch = YSI_Random__(YSI_RANGE('0', '9' + 1) + YSI_RANGE('A', 'Z' + 1)),
				ch =
					(ch >= YSI_RANGE('A', 'Z' + 1)) ? ch + ('0' - YSI_RANGE('A', 'Z' + 1)) :
					ch + 'A';
			}
		}
		output[++i] = ch;
	}
	while (i != len);
	output[len] = '\0';
	return ch;
}*/

