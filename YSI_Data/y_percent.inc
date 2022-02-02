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

