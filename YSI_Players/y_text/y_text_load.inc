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
	Portions created by the Initial Developer are Copyright C 2011
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

// Custom specifier data.
#define F@k<%0>(%1) F@k%0(%1)

#if defined FORMAT_CUSTOM_SPEC_BUFFER_SIZE
	// Sorry, no can do.
	#undef FORMAT_CUSTOM_SPEC_BUFFER_SIZE
#endif
// =====================================================================
//  UPDATE Y_RENDER_FIX_NEGATIVE MACRO ON CHANGE!!!!!!!
#define FORMAT_CUSTOM_SPEC_BUFFER_SIZE  144
//  Also "ts" in y_textrender.
// =====================================================================

// This is NOT QUITE compatible with Slice's version.  I had to modify the
// "FMAT@2" macro to better support extended parameter options (width etc).
#define FormatSpecifier<'%1'>(%2[%3],%4)  FMAT@1:F@%1(%2[FORMAT_CUSTOM_SPEC_BUFFER_SIZE],FMAT@2:___unused,%4)
#if defined FMAT@2
	#undef FMAT@2
#endif
#define FMAT@2:___unused,%1[%2]%3)        %1[%2],__unused%3)
#define FMAT@1:%1(%2)                     forward %1(%2); public %1(%2)

#define FORMAT_FLAG_LEFT (_:e_COMPRESS_FORMAT_DATA_LEFT)
#define FORMAT_FLAG_ZERO (_:e_COMPRESS_FORMAT_DATA_ZERO)

#define FORMAT:%0(%1) FormatSpecifier<'%0'>(%1)

// Enumeration for the possible keys they can want.
enum e_GAME_TEXT_KEYS
{
	e_NO_KEY_SELECTED,
	e_PED_ANSWER_PHONE,
	e_PED_DUCK,
	e_PED_FIREWEAPON,
	e_PED_FIREWEAPON_ALT,
	e_PED_SPRINT,
	e_VEHICLE_ENTER_EXIT,
	e_PED_JUMPING,
	e_PED_LOCK_TARGET,
	e_PED_LOOKBEHIND,
	e_SNEAK_ABOUT,
	e_VEHICLE_LOOKLEFT,
	e_VEHICLE_LOOKRIGHT,
	e_GO_FORWARD,
	e_GO_BACK,
	e_GO_LEFT,
	e_GO_RIGHT,
	e_VEHICLE_FIREWEAPON,
	e_VEHICLE_HORN,
	e_VEHICLE_FIREWEAPON_ALT,
	e_VEHICLE_ACCELERATE,
	e_VEHICLE_BRAKE,
	e_VEHICLE_HANDBRAKE,
	e_VEHICLE_SUBMISSIONS,
	e_VEHICLE_LOOKBEHIND,
	e_VEHICLE_TURRETUP,
	e_VEHICLE_TURRETDOWN,
	e_VEHICLE_TURRETLEFT,
	e_VEHICLE_TURRETRIGHT,
	e_VEHICLE_STEERUP,
	e_VEHICLE_STEERDOWN,
	e_VEHICLE_STEERLEFT,
	e_VEHICLE_STEERRIGHT
}

// Can support up to 16 specifier types, more requires a rewrite, unfortunately
// there are currently 15, though I can't think of any more...
enum e_COMPRESS_FORMAT_DATA (+= 0x10000000)
{
	e_COMPRESS_FORMAT_DATA_WIDTH = 0x00000FFF, // 0x800 = *, 0 = none,
	e_COMPRESS_FORMAT_DATA_PREC  = 0x00FFF000, // 0xFFF = default
	e_COMPRESS_FORMAT_DATA_LEFT  = 0x01000000,
	e_COMPRESS_FORMAT_DATA_ZERO  = 0x02000000,
	e_COMPRESS_FORMAT_DATA_LIST  = 0x04000000, // Array of data
	e_COMPRESS_FORMAT_DATA_FUNC  = 0x08000000, // Function of data
	e_COMPRESS_FORMAT_DATA_TYPE  = 0xF0000000,
	e_COMPRESS_FORMAT_DATA_DEC   = 0x10000000, // Decimal   : d, i
	e_COMPRESS_FORMAT_DATA_HEX,                // Hex       : h, x
	e_COMPRESS_FORMAT_DATA_BIN,                // Binary    : b
	e_COMPRESS_FORMAT_DATA_CHAR,               // Character : c
	e_COMPRESS_FORMAT_DATA_FLOAT,              // Float     : f
	e_COMPRESS_FORMAT_DATA_IEEE,               // IEEE      : g
	e_COMPRESS_FORMAT_DATA_STRING,             // String    : s
	e_COMPRESS_FORMAT_DATA_OCT,                // Octal     : o
	e_COMPRESS_FORMAT_DATA_COMM,               // Command   : n
	e_COMPRESS_FORMAT_DATA_SUFFIX,             // Suffix    : p
	e_COMPRESS_FORMAT_DATA_UNSIGNED,           // Unsigned  : u
	e_COMPRESS_FORMAT_DATA_SIGNED,             // Signed    : t
	e_COMPRESS_FORMAT_DATA_PLAYER,             // Player    : q
	e_COMPRESS_FORMAT_DATA_LOGICAL,            // Logical   : l
	// TODO: Make "custom" ala Slice's formatex.
	//e_COMPRESS_FORMAT_DATA_DATE                // Date      : DATE
	e_COMPRESS_FORMAT_DATA_CUSTOM
}

#define Y_FORMAT_GT_LIGHTER (0x10000000)
#define Y_FORMAT_CLOSE_CURR (0x20000000)
#define Y_FORMAT_START_FADE (0x40000000)
#define Y_FORMAT_ALWAYS_SET (0x80000000)

#define Y_FORMAT_IS_INSERT ('\02')
#define Y_FORMAT_IS_COLOUR ('\03')
#define Y_FORMAT_IS_KEY    ('\04')

#define Y_COLOURS_CASE(%0:%1) case '%0':return ++iIn,ret|e_COMPRESS_FORMAT_DATA_%1|(e_COMPRESS_FORMAT_DATA:((width&0xFFF)|((prec&0xFFF)<<12)))
#define Y_ESCAPES_CASE(%0:%1) case '%0':(iOut+1<len)&&(output[iOut++]='%1'),++iIn

#define Y_FORMAT_STRING_SKIP(); //if(iOut+1<len)output[iOut]=0,lastChar=iOut++

/*-------------------------------------------------------------------------*//**
 * <param name="input">String to read from.</param>
 * <param name="idx">Current read index.</param>
 * <returns>
 *  e_GAME_TEXT_KEYS - Enum representation of keys.
 * </returns>
 * <remarks>
 *  Reads a GameText key identifier and compresses it essentially.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock e_GAME_TEXT_KEYS:Format_GetKeys(const input[], &idx)
{
	P:3("e_GAME_TEXT_KEYS:Format_GetKeys called: \"%s\", %i", input, idx);
	if (input[idx] != '~')
	{
		return e_NO_KEY_SELECTED;
	}
	if (input[++idx])
	{
		if (!strcmp(input[idx], !"PED_ANSWER_PHONE~", true, 17))
		{
			idx += 17;
			return e_PED_ANSWER_PHONE;
		}
		else if (!strcmp(input[idx], !"PED_DUCK~", true, 9))
		{
			idx += 9;
			return e_PED_DUCK;
		}
		else if (!strcmp(input[idx], !"PED_FIREWEAPON~", true, 15))
		{
			idx += 15;
			return e_PED_FIREWEAPON;
		}
		else if (!strcmp(input[idx], !"PED_FIREWEAPON_ALT~", true, 29))
		{
			idx += 29;
			return e_PED_FIREWEAPON_ALT;
		}
		else if (!strcmp(input[idx], !"PED_SPRINT~", true, 11))
		{
			idx += 11;
			return e_PED_SPRINT;
		}
		else if (!strcmp(input[idx], !"VEHICLE_ENTER_EXIT~", true, 19))
		{
			idx += 19;
			return e_VEHICLE_ENTER_EXIT;
		}
		else if (!strcmp(input[idx], !"PED_JUMPING~", true, 12))
		{
			idx += 12;
			return e_PED_JUMPING;
		}
		else if (!strcmp(input[idx], !"PED_LOCK_TARGET~", true, 16))
		{
			idx += 16;
			return e_PED_LOCK_TARGET;
		}
		else if (!strcmp(input[idx], !"PED_LOOKBEHIND~", true, 15))
		{
			idx += 15;
			return e_PED_LOOKBEHIND;
		}
		else if (!strcmp(input[idx], !"SNEAK_ABOUT~", true, 12))
		{
			idx += 12;
			return e_SNEAK_ABOUT;
		}
		else if (!strcmp(input[idx], !"VEHICLE_LOOKLEFT~", true, 17))
		{
			idx += 17;
			return e_VEHICLE_LOOKLEFT;
		}
		else if (!strcmp(input[idx], !"VEHICLE_LOOKRIGHT~", true, 18))
		{
			idx += 18;
			return e_VEHICLE_LOOKRIGHT;
		}
		else if (!strcmp(input[idx], !"GO_FORWARD~", true, 11))
		{
			idx += 11;
			return e_GO_FORWARD;
		}
		else if (!strcmp(input[idx], !"GO_BACK~", true, 8))
		{
			idx += 8;
			return e_GO_BACK;
		}
		else if (!strcmp(input[idx], !"GO_LEFT~", true, 8))
		{
			idx += 8;
			return e_GO_LEFT;
		}
		else if (!strcmp(input[idx], !"GO_RIGHT~", true, 9))
		{
			idx += 9;
			return e_GO_RIGHT;
		}
		else if (!strcmp(input[idx], !"VEHICLE_FIREWEAPON~", true, 19))
		{
			idx += 19;
			return e_VEHICLE_FIREWEAPON;
		}
		else if (!strcmp(input[idx], !"VEHICLE_HORN~", true, 13))
		{
			idx += 13;
			return e_VEHICLE_HORN;
		}
		else if (!strcmp(input[idx], !"VEHICLE_FIREWEAPON_ALT~", true, 23))
		{
			idx += 23;
			return e_VEHICLE_FIREWEAPON_ALT;
		}
		else if (!strcmp(input[idx], !"VEHICLE_ACCELERATE~", true, 19))
		{
			idx += 19;
			return e_VEHICLE_ACCELERATE;
		}
		else if (!strcmp(input[idx], !"VEHICLE_BRAKE~", true, 14))
		{
			idx += 14;
			return e_VEHICLE_BRAKE;
		}
		else if (!strcmp(input[idx], !"VEHICLE_HANDBRAKE~", true, 18))
		{
			idx += 18;
			return e_VEHICLE_HANDBRAKE;
		}
		else if (!strcmp(input[idx], !"VEHICLE_SUBMISSIONS~", true, 20))
		{
			idx += 20;
			return e_VEHICLE_SUBMISSIONS;
		}
		else if (!strcmp(input[idx], !"VEHICLE_LOOKBEHIND~" , true, 19))
		{
			idx += 19;
			return e_VEHICLE_LOOKBEHIND;
		}
		else if (!strcmp(input[idx], !"VEHICLE_TURRETUP~", true, 17))
		{
			idx += 17;
			return e_VEHICLE_TURRETUP;
		}
		else if (!strcmp(input[idx], !"VEHICLE_TURRETDOWN~", true, 19))
		{
			idx += 19;
			return e_VEHICLE_TURRETDOWN;
		}
		else if (!strcmp(input[idx], !"VEHICLE_TURRETLEFT~", true, 19))
		{
			idx += 19;
			return e_VEHICLE_TURRETLEFT;
		}
		else if (!strcmp(input[idx], !"VEHICLE_TURRETRIGHT~", true, 20))
		{
			idx += 20;
			return e_VEHICLE_TURRETRIGHT;
		}
		else if (!strcmp(input[idx], !"VEHICLE_STEERUP~", true, 16))
		{
			idx += 16;
			return e_VEHICLE_STEERUP;
		}
		else if (!strcmp(input[idx], !"VEHICLE_STEERDOWN~", true, 18))
		{
			idx += 18;
			return e_VEHICLE_STEERDOWN;
		}
		else if (!strcmp(input[idx], !"VEHICLE_STEERLEFT~", true, 18))
		{
			idx += 18;
			return e_VEHICLE_STEERLEFT;
		}
		else if (!strcmp(input[idx], !"VEHICLE_STEERRIGHT~", true, 19))
		{
			idx += 19;
			return e_VEHICLE_STEERRIGHT;
		}
	}
	return e_NO_KEY_SELECTED;
}

/*-------------------------------------------------------------------------*//**
 * <param name="input">The text to read in.</param>
 * <param name="output">The destination array.  Can be the same as "input".</param>
 * <param name="len">The length of the output array.</param>
 * <param name="pt">Special mode for parsing player text has "()" but no "%" or keys.</param>
 * <returns>
 *  The length of the string.
 * </returns>
 * <remarks>
 *  Takes a string input and converts it to a standardised representation, i.e.
 *  uses byte-codes instead of human readable codes to represent formats and
 *  colours.  This makes it faster to format in to any other representation,
 *  instead of having to convert between all possible combinations, we just have
 *  this to convert basically all formats at once (it can handle hybrids of all
 *  the different representations) to a single fast read format and then have
 *  fairly simple to write methods to convert that single format to any other
 *  format (see y_formatout.inc).
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Format_Standardise(input[], output[], len = sizeof (output), pt = false)
{
	P:2("Format_Standardise called: %s, %d, %d", input, len, pt);
	new
		ch,
		iIn = 0,
		iOut = 0, //1,
		bool:fade = false,
		colour,
		tmp,
		steps;//,
		//lastChar = 0;
	// Adjust len so we know we can fit the NULL.
	--len;
	while ((ch = input[iIn]))
	{
		// Update where the next element of interest is.
		//output[lastChar] = iOut;
		// This is now ALWAYS candelled by the next colour to be found, but the
		// {<COLOUR} syntax is still supported.  The reason is that I got
		// annoyed by that syntax almost instantly.
		fade = false;
		colour = -1;
		P:7("Format_Standardise: loop pt 1 %c %d %d", ch, iIn, iOut);
		switch (ch)
		{
			case '#':
			{
				// Hash colours introduced by RyDeR`.
				/*if (fade)
				{
					fade = false;
				}*/
				if (input[++iIn] == '\0')
				{
					continue;
				}
				// Try and find the named colour.
				#if _YSI_USE_X11
					if (!strcmp(input[iIn], "X11", true, 3))
					{
						iIn += 3;
						if (input[iIn] == ' ' || input[iIn] == '_')
						{
							++iIn;
						}
					}
					// This can't do custom colours as there's no way to tell
					// where they end.
					colour = GetColourStream(input, iIn); //Colours_DoHashParse(input[iIn], iIn);
					//return Colours_DoHashParse(input, idx);
					if (colour != 0)
					{
						colour >>>= 8;
						goto Format_Standardise_no_switch;
					}
				#endif
				// Need to accept 3 and 6 character hex codes.
				colour = 0;
				//idx = iIn;
				tmp = iIn;
				while ((ch = input[tmp++] | 0x20))
				{
					if ('0' <= ch <= '9')
					{
						colour = (colour << 4) | (ch - '0');
					}
					else if ('a' <= ch <= 'f')
					{
						colour = (colour << 4) | (ch - 'a' + 10);
					}
					else
					{
						if (tmp - iIn == 6)
						{
							iIn += 6;
						}
						else if (tmp - iIn > 3)
						{
							// Convert to 3 digit hex.
							// First strip off excess.
							colour >>>= 4 * (tmp - iIn - 4);
							iIn += 3;
							// Then dupilcate each value.
							colour = ((colour & 0x0F00) * 0x1100) | ((colour & 0x00F0) * 0x0110) | ((colour & 0x000F) * 0x0011);
							tmp = iIn;
						}
						else
						{
							// Invalid colour.
							iIn = tmp;
							colour = -1;
						}
						break;
					}
					if (tmp - iIn == 6)
					{
						iIn += 6;
						break;
					}
				}
				// Should never be reached.  Is called if the string isn't long
				// enough to even contain a full colour identifier.
				//continue;
				if (tmp - iIn)
				{
					iIn = tmp - 1;
					continue;
				}
				goto Format_Standardise_no_switch;
			}
			case '~': // Game Text style information
			{
				/*if (fade)
				{
					// These never start and always close fades.
					fade = false;
				}*/
				colour = Format_GTToSAMP(input, iIn);
				goto Format_Standardise_no_switch;
			}
			case '(': // Bracket
			{
				//if (pt)
				//{
				//	//if (iOut + 1 < len)
				//	//{
				//		/*if (fade)
				//		{
				//			fade = false;
				//		}*/
				//		input[iOut++] = '(';
				//	//}
				//	// Need more code here to handle players typing in colours,
				//	// when they may just be putting in something in brackets -
				//	// need to test if it matches a colour (or just use the "#"
				//	// style (could make this user specified).
				//}
				//else
				//{
					if (iOut + 1 < len)
					{
						output[iOut++] = ch;
					}
					++iIn;
					continue;
				//}
			}
			case '{': // Brace
			{
				/*if (fade)
				{
					fade = false;
				}*/
				colour = -3;
			}
			case '%':
			{
				++iIn;
				if (pt)
				{
					// Don't allow players to type "%d", just output it as is.
					if (iOut + 1 < len)
					{
						output[iOut++] = ch;
					}
				}
				else
				{
					switch ((ch = input[iIn]))
					{
						case '%', '#', '{', '(', '~':
						{
							if (iOut + 1 < len)
							{
								output[iOut++] = ch;
							}
							++iIn;
						}
						case '\0':
						{
							if (iOut + 1 < len)
							{
								output[iOut++] = '%';
							}
						}
						default:
						{
							ch = Format_GetSpecifier(input, iIn);
							if (ch)
							{
								if (e_COMPRESS_FORMAT_DATA:ch & e_COMPRESS_FORMAT_DATA_TYPE == e_COMPRESS_FORMAT_DATA_CUSTOM)
								{
									// If the return is
									// "e_COMPRESS_FORMAT_DATA_CUSTOM", then
									// "Format_GetSpecifier" doesn't increment
									// "iIn" enough so that we can read it here.
									if (input[iIn] == 'k')
									{
										P:7("Format_Standardise: \"k\" specifier %d, %d, %d", ch, iOut, len);
										// Slightly modified "my" style custom
										// specifier.
										//++iIn;
										if (input[iIn + 1] == '<' && (tmp = strfind(input, ">", false, iIn)) != -1)
										{
											// Compress the name and length.
											input[iIn] = tmp - iIn;
											input[iIn + 1] = 'k';
											input[tmp] = '\0';
											if (iOut + 2 + ceildiv(tmp - iIn, 4) <= len)
											{
												output[iOut++] = Y_FORMAT_IS_INSERT;
												output[iOut++] = ch;
												strpack(output[iOut], input[iIn], len);
												iOut += ceildiv(tmp - iIn, 4);
											}
											iIn = tmp + 1;
										}
										else
										{
											++iIn;
										}
									}
									else
									{
										// "Slice" style custom specifier.
										P:7("Format_Standardise: Slice specifier %d, %d, %d", ch, iOut, len);
										if (iOut + 3 <= len)
										{
											output[iOut++] = Y_FORMAT_IS_INSERT;
											output[iOut++] = ch;
											static
												sFullName[4 char] = !"F@_";
											sFullName{2} = input[iIn];
											output[iOut++] = sFullName[0];
										}
										++iIn;
									}
								}
								else
								{
									P:7("Format_Standardise: specifier %d, %d, %d", ch, iOut, len);
									if (iOut + 2 <= len)
									{
										output[iOut++] = Y_FORMAT_IS_INSERT;
										output[iOut++] = ch;
									}
								}
							}
						}
					}
				}
				Y_FORMAT_STRING_SKIP();
				continue;
			}
			case '\\':
			{
				++iIn;
				if (pt)
				{
					// Don't allow players to type "\n", just output it as is.
					if (iOut + 1 < len)
					{
						output[iOut++] = ch;
					}
				}
				else
				{
					switch ((ch = input[iIn]))
					{
						Y_ESCAPES_CASE(r:\r);
						Y_ESCAPES_CASE(n:\n);
						Y_ESCAPES_CASE(a:\a);
						Y_ESCAPES_CASE(b:\b);
						Y_ESCAPES_CASE(v:\v);
						Y_ESCAPES_CASE(t:\t);
						Y_ESCAPES_CASE(e:\e);
						Y_ESCAPES_CASE(f:\f);
						Y_ESCAPES_CASE(s: );
						Y_ESCAPES_CASE(%:%);
						// These two with quotes can't be macros.
						case '\'': (iOut + 1 < len) && (output[iOut++] = '\''), ++iIn;
						case '"' : (iOut + 1 < len) && (output[iOut++] = '"' ), ++iIn;
						case 'x':
						{
							new
								num = 0;
							for ( ; ; )
							{
								// I don't know what the length restrictions on this
								// are - pawn-lang.pdf isn't clear.
								ch = input[++iIn];
								if ('0' <= ch <= '9')
								{
									num = (num * 16) + (ch - '0');
								}
								else if ('a' <= ch <= 'z')
								{
									num = (num * 16) + (ch - 'a' + 10);
								}
								else if ('A' <= ch <= 'Z')
								{
									num = (num * 16) + (ch - 'A' + 10);
								}
								else
								{
									break;
								}
							}
							if (ch == ';')
							{
								++iIn;
							}
							if (iOut + 1 < len)
							{
								output[iOut++] = num;
							}
						}
						case '0' .. '9':
						{
							new
								num = ch - '0';
							++iIn;
							// This can only be three characters.
							if ('0' <= (ch = input[iIn]) <= '9')
							{
								num = (num * 10) + (ch - '0');
								++iIn;
								if ('0' <= (ch = input[iIn]) <= '9')
								{
									num = (num * 10) + (ch - '0');
									ch = input[++iIn];
								}
							}
							// To put a semi-colon straight after a number code, use
							// \; (I never knew what the point of that was before -
							// it's just a separator really here).
							if (ch == ';')
							{
								++iIn;
							}
							if (iOut + 1 < len)
							{
								output[iOut++] = num;
							}
						}
					}
				}
				// Unrecognised symbols are ignored (or the slash is anyway).
				continue;
			}
			case '\01' .. '\04':
			{
				// Ignore these characters.
				++iIn;
				continue;
			}
			case '\05' .. '\08', '\11', '\12', '\14' .. '\31':
			{
				// Excludes tabs and newlines.
				++iIn;
				if (pt)
				{
					// Don't allow players to type "\05", just output it as is.
					// They can't actually type this, but just in case!
					if (iOut + 1 < len)
					{
						// Make all these things spaces.
						output[iOut++] = ' ';
					}
				}
				else
				{
					// Don't allow players to type "\05", just output it as is.
					// They can't actually type this, but just in case!
					if (iOut + 1 < len)
					{
						// Make all these things spaces.
						output[iOut++] = ch;
					}
				}
				continue;
			}
			default:
			{
				// Just add the character.
				if (iOut + 1 < len)
				{
					output[iOut++] = ch;
				}
				++iIn;
				continue;
			}
		}
		P:7("Format_Standardise: loop pt 2");
		switch ((ch = input[++iIn]))
		{
			case '>':
			{
				// Start of a fade.
				//if (!fade)
				//{
				fade = true;
				//}
				ch = input[++iIn];
				if (ch == '[')
				{
					steps = 0;
					while ((ch = input[++iIn]))
					{
						// Parse the number of steps to use.
						if (ch == ']')
						{
							ch = input[++iIn];
							break;
						}
						else if ('0' <= ch <= '9')
						{
							steps = (steps * 10) + (ch - '0');
						}
						else
						{
							// INNER LOOP, NOT THE MAIN LOOP.
							continue;
						}
					}
				}
			}
			case '<':
			{
				// End of a fade.
				/*if (fade)
				{
					fade = false;
				}*/
				ch = input[++iIn];
			}
		}
		P:7("Format_Standardise: loop pt 3");
		// Close colours introduced by [FeK]DraKiNs.
		if (colour == -2)
		{
			colour = ')';
		}
		else
		{
			colour = '}';
		}
		if (ch == '/')
		{
			// Close colour.
			while ((ch = input[++iIn]))
			{
				if (ch == colour)
				{
					++iIn;
					break;
				}
			}
			// Ignore everything else, skip to the after bit.
			colour = -2;
			goto Format_Standardise_no_switch;
		}
		// Finally we can get the real colour.
		new
			tot = 0,
			bool:num = true,
			cur = iIn;
		//idx = iIn;
		P:7("Format_Standardise: loop pt 4");
		while (ch)
		{
			if (ch == colour)
			{
				break;
			}
			new
				ch2 = ch | 0x20;
			if (num)
			{
				// Check if it's still a valid HEX digit and increment.
				if ('0' <= ch <= '9')
				{
					tot = (tot << 4) | (ch - '0');
				}
				else if ('a' <= ch2 <= 'f')
				{
					tot = (tot << 4) | (ch2 - 'a' + 10);
				}
				else if (('g' <= ch2 <= 'z') || ch == '_' || ch == ' ')
				{
					// No, but still a valid identifier.
					num = false;
				}
				else
				{
					colour = -1;
					goto Format_Standardise_no_switch;
				}
			}
			else if (!(('0' <= ch <= '9') || ('a' <= ch2 <= 'z') || ch == '_' || ch == ' '))
			{
				// Not a valid identifier character.
				colour = -1;
				// Can't use "continue" here as we're in an inner loop.
				goto Format_Standardise_no_switch;
			}
			ch = input[++cur];
		}
		P:7("Format_Standardise: loop pt 5 %c %d %d %d %s", ch, iIn, cur, num, input[iIn]);
		//while ((ch = input[++idx]));
		if (ch == '\0')
		{
			// Not a valid end.
			//iIn = cur;
			continue;
		}
		++cur;
		if (cur == iIn + 1)
		{
			++iIn;
			continue;
		}
		if (num)
		{
			// The input was a number.
			colour = tot & 0x00FFFFFF;
		}
		else
		{
			// The input was a string.
			//if (input[iIn] | 0x20 == 'x' && input[iIn + 1] == '1' && input[iIn + 2] == '1')
			#if _YSI_USE_X11
				if (!strcmp(input[iIn], "X11", true, 3))
				{
					if (input[iIn + 3] == ' ' || input[iIn + 3] == '_')
					{
						colour = GetColourHash(YHash(input[iIn + 4], false, hash_bernstein, cur - iIn - 5), 1);
					}
					else
					{
						colour = GetColourHash(YHash(input[iIn + 3], false, hash_bernstein, cur - iIn - 4), 1);
					}
				}
				else
			#endif
			{
				colour = GetColourHash(YHash(input[iIn], false, hash_bernstein, cur - iIn - 1), 1);
			}
			#pragma tabsize 4
			if (!colour)
			{
				continue;
			}
			colour >>>= 8;
		}
		P:7("Format_Standardise: loop pt 6");
		iIn = cur;
		// One of the FEW labels in my code, because in here "break" ends the
		// loop enclosing the switch statement, instead of ending the current
		// case from the switch statement as in C.
Format_Standardise_no_switch:
		if (colour == -1)
		{
			continue;
		}
		else if (colour == -2)
		{
			if (iOut + 2 < len)
			{
				// Save the close.
				colour = Y_FORMAT_CLOSE_CURR;
				if (fade)
				{
					colour |= Y_FORMAT_START_FADE;
				}
				output[iOut++] = Y_FORMAT_IS_COLOUR;
				output[iOut++] = colour | Y_FORMAT_ALWAYS_SET;
			}
		}
		else if (colour & 0x0F000000)
		{
			// Players can't type these special things.
			if (!pt && iOut + 2 < len)
			{
				// Save the custom key.
				output[iOut++] = Y_FORMAT_IS_KEY;
				if (colour & 0xFF == 'k')
				{
					// Add the whole next key definition.
					ch = _:Format_GetKeys(input, iIn);
					if (ch != _:e_NO_KEY_SELECTED)
					{
						output[iOut++] = 'k' | (ch << 8);
					}
				}
				else
				{
					switch (colour & 0xFF)
					{
						case 'n':
						{
							output[iOut++] = '\n';
						}
						case ']':
						{
							output[iOut++] = '*';
						}
						default:
						{
							output[iOut++] = (colour & 0xFF) | Y_FORMAT_ALWAYS_SET;
						}
					}
					colour = colour >> 8 & 0xFF;
					if (iOut + 2 < len && colour)
					{
						// Save the special GameText "lighter" colour.
						output[iOut++] = Y_FORMAT_IS_COLOUR;
						output[iOut++] = colour | Y_FORMAT_GT_LIGHTER | Y_FORMAT_ALWAYS_SET;
					}
				}
			}
		}
		else
		{
			if (iOut + 2 < len)
			{
				// Save the normal colour.
				if (fade)
				{
					colour |= Y_FORMAT_START_FADE;
				}
				output[iOut++] = Y_FORMAT_IS_COLOUR;
				output[iOut++] = colour | Y_FORMAT_ALWAYS_SET;
			}
		}
		Y_FORMAT_STRING_SKIP();
		P:7("Format_Standardise: loop pt 7");
	}
	output[iOut] = '\0';
	/*if (lastChar == iOut + 1)
	{
		output[lastChar] = 0;
	}
	else
	{
		output[lastChar] = iOut;
	}*/
	P:5("Format_Standardise: end: %d %d,%d,%d,%d,%d", iOut, output[0], output[1], output[2], output[3], output[4]);
	/*else
	{
		return GetColourHash(YHash(input[start], false, hash_bernstein, cur - start - 1), 0) >>> 8;
	}*/
	return iOut;
}

/*-------------------------------------------------------------------------*//**
 * <param name="input">String to read from.</param>
 * <param name="iIn">Index to read from.</param>
 * <returns>
 *  Single cell representation of the current specifier.
 * </returns>
 * <remarks>
 *  Reads a series of characters from the input string and interprets them as a
 *  format specifier (e.g. "%d").  Also returns the new current string index.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Format_GetSpecifier(input[], &iIn)
{
	P:4("Format_GetSpecifier called: \"%s\", %i", input, iIn);
	new
		ch = input[iIn],
		e_COMPRESS_FORMAT_DATA:ret = e_COMPRESS_FORMAT_DATA:0,
		width,
		prec = -1;
	for ( ; ; )
	{
		switch (ch)
		{
			case '\0':
			{
				break;
			}
			case '!':
			{
				ret = (ret & ~e_COMPRESS_FORMAT_DATA_FUNC) | e_COMPRESS_FORMAT_DATA_LIST;
			}
			case '?':
			{
				ret = (ret & ~e_COMPRESS_FORMAT_DATA_LIST) | e_COMPRESS_FORMAT_DATA_FUNC;
			}
			case '-':
			{
				ret |= e_COMPRESS_FORMAT_DATA_LEFT;
			}
			case '.':
			{
				if ((ch = input[++iIn]) == '*')
				{
					prec = 0x800;
				}
				else
				{
					prec = 0;
					while ('0' <= ch <= '9')
					{
						prec = 10 * prec + (ch - '0');
						ch = input[++iIn];
					}
				}
				continue;
			}
			case '0':
			{
				ret |= e_COMPRESS_FORMAT_DATA_ZERO;
			}
			case '1' .. '9':
			{
				width = 0;
				do
				{
					width = 10 * width + (ch - '0');
					ch = input[++iIn];
				}
				while ('0' <= ch <= '9');
				continue;
			}
			case '*':
			{
				width = 0x800;
			}
			case 's':
			{
				++iIn;
				if (ret & e_COMPRESS_FORMAT_DATA_LIST)
				{
					printf("*** Internal Warning: Ignoring string list format specifier.");
					ret &= e_COMPRESS_FORMAT_DATA_LIST;
				}
				return ret | e_COMPRESS_FORMAT_DATA_STRING | (e_COMPRESS_FORMAT_DATA:((width & 0xFFF) | ((prec & 0xFFF) << 12)));
			}
			Y_COLOURS_CASE(b:BIN);
			Y_COLOURS_CASE(d','i:DEC);
			Y_COLOURS_CASE(h','x:HEX);
			Y_COLOURS_CASE(f:FLOAT);
			Y_COLOURS_CASE(g:IEEE);
			Y_COLOURS_CASE(o:OCT);
			// I *might* half-decouple "%n" so that this doesn't directly rely
			// on y_commands being included first.  Or I could do what y_classes
			// does to use y_groups without including it directly.
			Y_COLOURS_CASE(n:COMM);
			Y_COLOURS_CASE(p:SUFFIX);
			Y_COLOURS_CASE(u:UNSIGNED);
			Y_COLOURS_CASE(t:SIGNED);
			Y_COLOURS_CASE(q:PLAYER);
			Y_COLOURS_CASE(l:LOGICAL);
			default:
			{
				// I have removed the "%DATE% sequence and replaced it with the
				// custom system from Slice.  Ideally I'd like to support both
				// somehow, like make the "%XYZ%" format an option AND the "%q"
				// format an option - maybe default to mine and fall back on the
				// short version if a function isn't found.
				/*if (!strcmp(input, !"DATE%", true, 5))
				{
					iIn += 5;
					return ret | e_COMPRESS_FORMAT_DATA_DATE | (e_COMPRESS_FORMAT_DATA:((width & 0xFFF) | ((prec & 0xFFF) << 12)));
				}*/
				// Shut up the compiler.
				//break;
				return ret | e_COMPRESS_FORMAT_DATA_CUSTOM | (e_COMPRESS_FORMAT_DATA:((width & 0xFFF) | ((prec & 0xFFF) << 12)));
			}
		}
		ch = input[++iIn];
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">Input.</param>
 * <param name="idx">Read index.</param>
 * <returns>
 *  Colour.
 * </returns>
 * <remarks>
 *  Reads a GameText colour format and converts it to single-cell RGB.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock Format_GTToSAMP(const str[], &idx)
{
	P:4("Format_GTToSAMP called: \"%s\", %i", str, idx);
	new
		cur = idx;
	if (str[cur] == '~')
	{
		// Check the colour is correctly ended.
		new
			t = str[++cur];
		if (!t)
		{
			++idx;
			return -1;
		}
		if (str[++cur] != '~')
		{
			++idx;
			return -1;
		}
		++cur;
		// Get the number of ~h~s after the colour.
		new
			c = 0;
		while (str[cur] == '~')
		{
			if (str[cur + 1] | 0x20 == 'h' && str[cur + 2] == '~')
			{
				++c;
				cur += 3;
			}
			else
			{
				break;
			}
		}
		idx = cur;
		// Return the correct colour for the given string.
		switch (t)
		{
			case 'b':
			{
				switch (c)
				{
					case 0:
						return SAMP_GAME_TEXT_B >>> 8;
					case 1:
						return SAMP_GAME_TEXT_BH >>> 8;
					case 2:
						return SAMP_GAME_TEXT_BHH >>> 8;
					case 3:
						return SAMP_GAME_TEXT_BHHH >>> 8;
					default:
						return SAMP_GAME_TEXT_W >>> 8;
				}
			}
			case 'g':
			{
				switch (c)
				{
					case 0:
						return SAMP_GAME_TEXT_G >>> 8;
					case 1:
						return SAMP_GAME_TEXT_GH >>> 8;
					case 2:
						return SAMP_GAME_TEXT_GHH >>> 8;
					case 3:
						return SAMP_GAME_TEXT_GHHH >>> 8;
					case 4:
						return SAMP_GAME_TEXT_GHHHH >>> 8;
					default:
						return SAMP_GAME_TEXT_W >>> 8;
				}
			}
			case 'h':
			{
				switch (c)
				{
					case 0:
						return SAMP_GAME_TEXT_H >>> 8;
					case 1:
						return SAMP_GAME_TEXT_HH >>> 8;
					default:
						return SAMP_GAME_TEXT_W >>> 8;
				}
			}
			case 'l':
			{
				return SAMP_GAME_TEXT_L >>> 8;
			}
			case 'p':
			{
				switch (c)
				{
					case 0:
						return SAMP_GAME_TEXT_P >>> 8;
					case 1:
						return SAMP_GAME_TEXT_PH >>> 8;
					case 2:
						return SAMP_GAME_TEXT_PHH >>> 8;
					default:
						return SAMP_GAME_TEXT_W >>> 8;
				}
			}
			case 'r':
			{
				switch (c)
				{
					case 0:
						return SAMP_GAME_TEXT_R >>> 8;
					case 1:
						return SAMP_GAME_TEXT_RH >>> 8;
					case 2:
						return SAMP_GAME_TEXT_RHH >>> 8;
					case 3:
						return SAMP_GAME_TEXT_RHHH >>> 8;
					case 4:
						return SAMP_GAME_TEXT_RHHHH >>> 8;
					case 5:
						return SAMP_GAME_TEXT_RHHHHH >>> 8;
					default:
						return SAMP_GAME_TEXT_W >>> 8;
				}
			}
			case 'w':
			{
				return SAMP_GAME_TEXT_W >>> 8;
			}
			case 'y':
			{
				switch (c)
				{
					case 0:
						return SAMP_GAME_TEXT_Y >>> 8;
					case 1:
						return SAMP_GAME_TEXT_YH >>> 8;
					case 2:
						return SAMP_GAME_TEXT_YHH >>> 8;
					default:
						return SAMP_GAME_TEXT_W >>> 8;
				}
			}
			default:
			{
				// Return the fact there is a different GT sequence but keep a
				// record of the number of hs which came after it to avoid
				// excess processing.
				//idx -= (c + 1) * 3;
				return 0x0F000000 | t | (c << 8);
			}
		}
	}
	return -1;
}
