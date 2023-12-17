/**
 * <library
 *   name="y_utils - names"
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
 * <library>y_utils - names</library>
 * <summary>
 *   ReturnPlayerName
 * </summary>
 * <param name="playerid">Player whose name you want to get.</param>
 * <remarks>
 *   Get a player's name.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ReturnPlayerName(playerid)
{
	new
		name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, MAX_PLAYER_NAME - 1);
	return name;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - names</library>
 * <summary>
 *   GetPlayerRPName
 * </summary>
 * <param name="playerid">Player whose name you want to get.</param>
 * <param name="name">The destination array to save the name in.</param>
 * <param name="len">The length of the destination.</param>
 * <remarks>
 *   Get a player's name, with <c>_</c> replaced by <c> </c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:GetPlayerRPName(playerid, string:name[], len = sizeof (name))
{
	// Returns an unpacked string.
	if (GetPlayerName(playerid, name, len - 1))
	{
		// Replace `_` with ` `.
		len = -1;
		if (YSI_IsLocalVarPackedString__(name))
		{
			while ((len = strfind(name, __COMPILER_PACK"_", false, len + 1)) != -1)
			{
				name{len} = ' ';
			}
		}
		else
		{
			while ((len = strfind(name, __COMPILER_PACK"_", false, len + 1)) != -1)
			{
				name[len] = ' ';
			}
		}
		return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - names</library>
 * <summary>
 *   GetPlayerRPComponents
 * </summary>
 * <param name="playerid">Player whose name you want to get.</param>
 * <remarks>
 *   Get a player's name, split in to parts by <c>_</c>.
 * </remarks>
 * <returns>
 *   The number of parts extracted from the name.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock GetPlayerRPComponents(playerid, string:names[][], components = sizeof (names), len = sizeof (names[]))
{
	new
		i = 0,
		name[MAX_PLAYER_NAME + 1];
	// Returns an unpacked string.
	if (GetPlayerName(playerid, name, MAX_PLAYER_NAME))
	{
		// Split by `_`.
		--components;
		for (new p = -1, n; i < components && (n = strfind(name, __COMPILER_PACK"_", false, p + 1)) != -1; ++i, p = n)
		{
			strmid(names[i], name, p + 1, n, len);
		}
		strmid(names[i], name, p + 1, strlen(name), len);
		++i;
	}
	return i;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - names</library>
 * <summary>
 *   IsRPName
 * </summary>
 * <param name="name">The name to test.</param>
 * <param name="casing">Check for string casing?  I.e. allow <c>James</c> but
 *   not <c>james</c>.</param>
 * <param name="longNames">Allow more than two name parts?</param>
 * <remarks>
 *   Is this name in the form <c>First_Last</c>?  Note this doesn't handle names
 *   like "MacLeod", nor double-barralled surnames like "Smith-Thompson".
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:IsRPName(const string:name[], bool:casing = false, bool:longNames = false)
{
	if (YSI_IsLocalVarPackedString__(name))
	{
		new
			parts = 0,
			ch = name{0},
			pos = -1;
		if (ch == ' ' || ch == '_' || ch == '\0')
		{
			// Leading bad characters.
			return false;
		}
		if (casing)
		{
			do
			{
				if (NOT_IN_RANGE((ch = name{++pos}), 'A', 'Z' + 1))
				{
					// Not a capital letter.
					return false;
				}
				while ((ch = name{++pos}))
				{
					// Allow real spaces, YSF can enable that.
					if (ch == '_' || ch == ' ')
					{
						if (name{pos + 1} == '\0')
						{
							// Ends with `_`.
							return false;
						}
						break;
					}
					if (NOT_IN_RANGE(ch, 'a', 'z' + 1))
					{
						// Not a lower-case letter.
						return false;
					}
				}
				// Found a name part.
				++parts;
			}
			while (ch);
		}
		else
		{
			do
			{
				while ((ch = name{++pos}))
				{
					// Allow real spaces, YSF can enable that.
					if (ch == '_' || ch == ' ')
					{
						if (name{pos + 1} == '\0')
						{
							// Ends with `_`.
							return false;
						}
						break;
					}
					if (NOT_IN_RANGE(ch, 'a', 'z' + 1) && NOT_IN_RANGE(ch, 'A', 'Z' + 1))
					{
						// Not a valid name letter.
						return false;
					}
				}
				// Found a name part.
				++parts;
			}
			while (ch);
		}
		switch (parts)
		{
		case 1:
			// Not enough parts.
			return false;
		case 2:
			// Exactly two parts.
			return true;
		}
		// More parts.  Is this allowed?
		return longNames;
	}
	else
	{
		new
			parts = 0,
			ch = name[0],
			pos = -1;
		if (ch == ' ' || ch == '_' || ch == '\0')
		{
			// Leading bad characters.
			return false;
		}
		if (casing)
		{
			do
			{
				if (NOT_IN_RANGE((ch = name[++pos]), 'A', 'Z' + 1))
				{
					// Not a capital letter.
					return false;
				}
				while ((ch = name[++pos]))
				{
					// Allow real spaces, YSF can enable that.
					if (ch == '_' || ch == ' ')
					{
						if (name[pos + 1] == '\0')
						{
							// Ends with `_`.
							return false;
						}
						break;
					}
					if (NOT_IN_RANGE(ch, 'a', 'z' + 1))
					{
						// Not a lower-case letter.
						return false;
					}
				}
				// Found a name part.
				++parts;
			}
			while (ch);
		}
		else
		{
			do
			{
				while ((ch = name[++pos]))
				{
					// Allow real spaces, YSF can enable that.
					if (ch == '_' || ch == ' ')
					{
						if (name[pos + 1] == '\0')
						{
							// Ends with `_`.
							return false;
						}
						break;
					}
					if (NOT_IN_RANGE(ch, 'a', 'z' + 1) && NOT_IN_RANGE(ch, 'A', 'Z' + 1))
					{
						// Not a valid name letter.
						return false;
					}
				}
				// Found a name part.
				++parts;
			}
			while (ch);
		}
		switch (parts)
		{
		case 1:
			// Not enough parts.
			return false;
		case 2:
			// Exactly two parts.
			return true;
		}
		// More parts.  Is this allowed?
		return longNames;
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - names</library>
 * <summary>
 *   HasRPName
 * </summary>
 * <param name="playerid">Player whose name you want to test.</param>
 * <param name="casing">Check for string casing?  I.e. allow <c>James</c> but
 *   not <c>james</c>.</param>
 * <param name="longNames">Allow more than two name parts?</param>
 * <remarks>
 *   Is this player's name in the form <c>First_Last</c>?
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:HasRPName(playerid, bool:casing = false, bool:longNames = false)
{
	new
		name[MAX_PLAYER_NAME + 1];
	// Also check they are connected.
	return GetPlayerName(playerid, name, MAX_PLAYER_NAME) && IsRPName(name, casing, longNames);
}

/*-------------------------------------------------------------------------*//**
 * <library>y_utils - names</library>
 * <summary>
 *   ReturnPlayerRPName
 * </summary>
 * <param name="playerid">Player whose name you want to get.</param>
 * <remarks>
 *   Get a player's name, with <c>_</c> replaced by <c> </c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock ReturnPlayerRPName(playerid)
{
	new
		name[MAX_PLAYER_NAME];
	GetPlayerRPName(playerid, name, MAX_PLAYER_NAME);
	return name;
}

