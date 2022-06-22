/*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (c) 2022
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

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  <c>value + percent</c>
 * </summary>
 * <param name="value">The number to adjust.</param>
 * <param name="percent">The percentage amount to adjust it by.</param>
 * <returns>
 *  The number increased by the given percentage amount.
 * </returns>
 * <remarks>
 *  <code>
 *      const Percent:TWENTY_PERCENT = Percent:20;                              <br />
 *      new value = 5 + TWENTY_PERCENT; // = 5 * 1.2 = 6
 *  </code>
 * </remarks>
 *//*------------------------------------------------------------------------**/
stock operator+(value, Percent:percent)
{
	return (value * (100 + _:percent)) / 100;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  <c>percent + value</c>
 * </summary>
 * <param name="percent">The percentage amount to adjust.</param>
 * <param name="value">The number to adjust it by.</param>
 * <returns>
 *  Normal addition, applied to percentages.
 * </returns>
 *//*------------------------------------------------------------------------**/
stock Percent:operator+(Percent:percent, value)
{
	return Percent:((_:percent) + value);
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  <c>value + percent</c>
 * </summary>
 * <param name="value">The percentage to adjust.</param>
 * <param name="percent">The percentage amount to adjust it by.</param>
 * <returns>
 *  The percentage added by the given percentage amount.
 * </returns>
 *//*------------------------------------------------------------------------**/
stock Percent:operator+(Percent:value, Percent:percent)
{
	return Percent:((_:value) + (_:percent));
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  <c>value * percent</c>
 * </summary>
 * <param name="value">The number to adjust.</param>
 * <param name="percent">The percentage amount to adjust it by.</param>
 * <returns>
 *  The number multiplied by the given percentage amount.
 * </returns>
 * <remarks>
 *  <code>
 *      const Percent:TWENTY_PERCENT = Percent:20;                              <br />
 *      new value = 5 * TWENTY_PERCENT; // = 5 * 0.2 = 1
 *  </code>
 * </remarks>
 *//*------------------------------------------------------------------------**/
stock operator*(value, Percent:percent)
{
	return (value * (_:percent)) / 100;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  <c>percent * value</c>
 * </summary>
 * <param name="percent">The percentage amount to adjust.</param>
 * <param name="value">The number to adjust it by.</param>
 * <returns>
 *  Normal multiplication, applied to percentages.
 * </returns>
 *//*------------------------------------------------------------------------**/
stock Percent:operator*(Percent:percent, value)
{
	return Percent:((_:percent) * value);
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  <c>value * percent</c>
 * </summary>
 * <param name="value">The percentage to adjust.</param>
 * <param name="percent">The percentage amount to adjust it by.</param>
 * <returns>
 *  The percentage multiplied by the given percentage amount.
 * </returns>
 * <remarks>
 *  <code>
 *      const Percent:TWENTY_PERCENT = Percent:20;                              <br />
 *      new value = Percent:5 * TWENTY_PERCENT; // = 5 * 0.2 = Percent:1
 *  </code>
 * </remarks>
 *//*------------------------------------------------------------------------**/
stock Percent:operator*(Percent:value, Percent:percent)
{
	return Percent:(((_:value) * (_:percent)) / 100);
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  <c>value - percent</c>
 * </summary>
 * <param name="value">The number to adjust.</param>
 * <param name="percent">The percentage amount to adjust it by.</param>
 * <returns>
 *  The number decreased by the given percentage amount.
 * </returns>
 * <remarks>
 *  <code>
 *      const Percent:TWENTY_PERCENT = Percent:20;                              <br />
 *      new value = 5 - TWENTY_PERCENT; // = 5 * 0.8 = 4
 *  </code>
 * </remarks>
 *//*------------------------------------------------------------------------**/
stock operator-(value, Percent:percent)
{
	return (value * (100 - _:percent)) / 100;
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  <c>percent - value</c>
 * </summary>
 * <param name="percent">The percentage amount to adjust.</param>
 * <param name="value">The number to adjust it by.</param>
 * <returns>
 *  Normal subtraction, applied to percentages.
 * </returns>
 *//*------------------------------------------------------------------------**/
stock Percent:operator-(Percent:percent, value)
{
	return Percent:((_:percent) - value);
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  <c>value - percent</c>
 * </summary>
 * <param name="value">The percentage to adjust.</param>
 * <param name="percent">The percentage amount to adjust it by.</param>
 * <returns>
 *  The percentage subtracted from the given percentage amount.
 * </returns>
 *//*------------------------------------------------------------------------**/
stock Percent:operator-(Percent:value, Percent:percent)
{
	return Percent:((_:value) - (_:percent));
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  <c>value / percent</c>
 * </summary>
 * <param name="value">The number to adjust.</param>
 * <param name="percent">The percentage amount to adjust it by.</param>
 * <returns>
 *  Nothing.  Unimplemented
 * </returns>
 * <remarks>
 *  Dividing a number by a percentage value doesn't make sense.
 * </remarks>
 *//*------------------------------------------------------------------------**/
forward operator/(value, Percent:percent);

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  <c>value % percent</c>
 * </summary>
 * <param name="value">The number to adjust.</param>
 * <param name="percent">The percentage amount to adjust it by.</param>
 * <returns>
 *  Nothing.  Unimplemented
 * </returns>
 * <remarks>
 *  Taking a number modulo a percentage value doesn't make sense.  Shame we
 *  can't reuse the symbol as a percentage somehow.
 * </remarks>
 *//*------------------------------------------------------------------------**/
forward operator%(value, Percent:percent);

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  <c>percent / value</c>
 * </summary>
 * <param name="percent">The percentage amount to adjust.</param>
 * <param name="value">The number to adjust it by.</param>
 * <returns>
 *  Normal division, applied to percentages.
 * </returns>
 *//*------------------------------------------------------------------------**/
stock Percent:operator/(Percent:percent, value)
{
	return Percent:((_:percent) / value);
}

/*-------------------------------------------------------------------------*//**
 * <summary>
 *  <c>percent % value</c>
 * </summary>
 * <param name="percent">The percentage amount to adjust.</param>
 * <param name="value">The number to adjust it by.</param>
 * <returns>
 *  Normal modulus, applied to percentages.
 * </returns>
 *//*------------------------------------------------------------------------**/
stock Percent:operator%(Percent:percent, value)
{
	return Percent:((_:percent) % value);
}

