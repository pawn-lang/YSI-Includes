/*----------------------------------------------------------------------------*\
					==========================
					 y_colours - X11 colours!
					==========================
Description:
	This holds the colour information that used to be part of the text system
	but which is far more useful than just for text.  This now supports the full
	set of X11 colours, both by name and by definition.  You can also define
	your own if you so choose (up to 32 - should be enough given that this
	includes the X11 colours).
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
	
	The Original Code is the YSI colours include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
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
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	1.0
Changelog:
	29/11/10:
		Added the ability to use "X11" prefixes in strings.
		Added colourspace resolution for converting {FF0000} to ~r~.
	25/11/10:
		First version.
\*----------------------------------------------------------------------------*/

#define _X11_SPACE_CHECK(%0) (checkSpace && str[(%0)] == ' ')
#define _X11_SPACE_SWITCH:  ' ':if(checkSpace)

/*(str[9] == ' ' || str[9] == '_')

((checkSpace && _X11_SPACE_CHECK()) || str[9] == '_')

(str[9] != ' ' && str[9] != '_')

(!(checkSpace && _X11_SPACE_CHECK(9)) && str[9] != '_')*/

	switch (str[0] | 0x20)
	{
		case 'a':
		{
			switch (str[1] | 0x20)
			{
				case 'l':
				{
					if (!str[2] || strcmp(str[2], !"ICE", true, 3))
					{
						return -1;
					}
					switch (str[5] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[5])
							{
								if (str[6] && !strcmp(str[6], !"BLUE", true, 4))
								{
									idx += 10;
									return X11_ALICE_BLUE;
								}
							}
						}
						case '_' | 0x20:
						{
							if (str[6] && !strcmp(str[6], !"BLUE", true, 4))
							{
								idx += 10;
								return X11_ALICE_BLUE;
							}
						}
						case 'b':
						{
							if (str[6] && !strcmp(str[6], !"LUE", true, 3))
							{
								idx += 9;
								return X11_ALICEBLUE;
							}
						}
					}
				}
				case 'n':
				{
					if (!str[2] || strcmp(str[2], !"TIQUE", true, 5))
					{
						return -1;
					}
					switch (str[7] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[7])
							{
								if (!str[8] || strcmp(str[8], !"WHITE", true, 5))
								{
									return -1;
								}
								switch (str[13] | 0x20)
								{
									case _X11_SPACE_SWITCH: // ' '
									{
										if (str[13])
										{
											switch (str[14] | 0x20)
											{
												case '1':
												{
													idx += 15;
													return X11_ANTIQUE_WHITE_1;
												}
												case '2':
												{
													idx += 15;
													return X11_ANTIQUE_WHITE_2;
												}
												case '3':
												{
													idx += 15;
													return X11_ANTIQUE_WHITE_3;
												}
												case '4':
												{
													idx += 15;
													return X11_ANTIQUE_WHITE_4;
												}
											}
										}
									}
									case '_' | 0x20:
									{
										switch (str[14] | 0x20)
										{
											case '1':
											{
												idx += 15;
												return X11_ANTIQUE_WHITE_1;
											}
											case '2':
											{
												idx += 15;
												return X11_ANTIQUE_WHITE_2;
											}
											case '3':
											{
												idx += 15;
												return X11_ANTIQUE_WHITE_3;
											}
											case '4':
											{
												idx += 15;
												return X11_ANTIQUE_WHITE_4;
											}
										}
									}
								}
								idx += 13;
								return X11_ANTIQUE_WHITE;
							}
						}
						case '_' | 0x20:
						{
							if (!str[8] || strcmp(str[8], !"WHITE", true, 5))
							{
								return -1;
							}
							switch (str[13] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[13])
									{
										switch (str[14] | 0x20)
										{
											case '1':
											{
												idx += 15;
												return X11_ANTIQUE_WHITE_1;
											}
											case '2':
											{
												idx += 15;
												return X11_ANTIQUE_WHITE_2;
											}
											case '3':
											{
												idx += 15;
												return X11_ANTIQUE_WHITE_3;
											}
											case '4':
											{
												idx += 15;
												return X11_ANTIQUE_WHITE_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[14] | 0x20)
									{
										case '1':
										{
											idx += 15;
											return X11_ANTIQUE_WHITE_1;
										}
										case '2':
										{
											idx += 15;
											return X11_ANTIQUE_WHITE_2;
										}
										case '3':
										{
											idx += 15;
											return X11_ANTIQUE_WHITE_3;
										}
										case '4':
										{
											idx += 15;
											return X11_ANTIQUE_WHITE_4;
										}
									}
								}
							}
							idx += 13;
							return X11_ANTIQUE_WHITE;
						}
						case 'w':
						{
							if (!str[8] || strcmp(str[8], !"HITE", true, 4))
							{
								return -1;
							}
							switch (str[12] | 0x20)
							{
								case '1':
								{
									idx += 13;
									return X11_ANTIQUEWHITE1;
								}
								case '2':
								{
									idx += 13;
									return X11_ANTIQUEWHITE2;
								}
								case '3':
								{
									idx += 13;
									return X11_ANTIQUEWHITE3;
								}
								case '4':
								{
									idx += 13;
									return X11_ANTIQUEWHITE4;
								}
							}
							idx += 12;
							return X11_ANTIQUEWHITE;
						}
					}
				}
				case 'q':
				{
					if (!str[2] || strcmp(str[2], !"UAMARINE", true, 8))
					{
						return -1;
					}
					switch (str[10] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[10])
							{
								switch (str[11] | 0x20)
								{
									case '1':
									{
										idx += 12;
										return X11_AQUAMARINE_1;
									}
									case '2':
									{
										idx += 12;
										return X11_AQUAMARINE_2;
									}
									case '3':
									{
										idx += 12;
										return X11_AQUAMARINE_3;
									}
									case '4':
									{
										idx += 12;
										return X11_AQUAMARINE_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[11] | 0x20)
							{
								case '1':
								{
									idx += 12;
									return X11_AQUAMARINE_1;
								}
								case '2':
								{
									idx += 12;
									return X11_AQUAMARINE_2;
								}
								case '3':
								{
									idx += 12;
									return X11_AQUAMARINE_3;
								}
								case '4':
								{
									idx += 12;
									return X11_AQUAMARINE_4;
								}
							}
						}
						case '1':
						{
							idx += 11;
							return X11_AQUAMARINE1;
						}
						case '2':
						{
							idx += 11;
							return X11_AQUAMARINE2;
						}
						case '3':
						{
							idx += 11;
							return X11_AQUAMARINE3;
						}
						case '4':
						{
							idx += 11;
							return X11_AQUAMARINE4;
						}
					}
					idx += 10;
					return X11_AQUAMARINE;
				}
				case 'z':
				{
					if (!str[2] || strcmp(str[2], !"URE", true, 3))
					{
						return -1;
					}
					switch (str[5] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[5])
							{
								switch (str[6] | 0x20)
								{
									case '1':
									{
										idx += 7;
										return X11_AZURE_1;
									}
									case '2':
									{
										idx += 7;
										return X11_AZURE_2;
									}
									case '3':
									{
										idx += 7;
										return X11_AZURE_3;
									}
									case '4':
									{
										idx += 7;
										return X11_AZURE_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[6] | 0x20)
							{
								case '1':
								{
									idx += 7;
									return X11_AZURE_1;
								}
								case '2':
								{
									idx += 7;
									return X11_AZURE_2;
								}
								case '3':
								{
									idx += 7;
									return X11_AZURE_3;
								}
								case '4':
								{
									idx += 7;
									return X11_AZURE_4;
								}
							}
						}
						case '1':
						{
							idx += 6;
							return X11_AZURE1;
						}
						case '2':
						{
							idx += 6;
							return X11_AZURE2;
						}
						case '3':
						{
							idx += 6;
							return X11_AZURE3;
						}
						case '4':
						{
							idx += 6;
							return X11_AZURE4;
						}
					}
					idx += 5;
					return X11_AZURE;
				}
			}
		}
		case 'b':
		{
			switch (str[1] | 0x20)
			{
				case 'e':
				{
					if (str[2] && !strcmp(str[2], !"IGE", true, 3))
					{
						idx += 5;
						return X11_BEIGE;
					}
				}
				case 'i':
				{
					if (!str[2] || strcmp(str[2], !"SQUE", true, 4))
					{
						return -1;
					}
					switch (str[6] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[6])
							{
								switch (str[7] | 0x20)
								{
									case '1':
									{
										idx += 8;
										return X11_BISQUE_1;
									}
									case '2':
									{
										idx += 8;
										return X11_BISQUE_2;
									}
									case '3':
									{
										idx += 8;
										return X11_BISQUE_3;
									}
									case '4':
									{
										idx += 8;
										return X11_BISQUE_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[7] | 0x20)
							{
								case '1':
								{
									idx += 8;
									return X11_BISQUE_1;
								}
								case '2':
								{
									idx += 8;
									return X11_BISQUE_2;
								}
								case '3':
								{
									idx += 8;
									return X11_BISQUE_3;
								}
								case '4':
								{
									idx += 8;
									return X11_BISQUE_4;
								}
							}
						}
						case '1':
						{
							idx += 7;
							return X11_BISQUE1;
						}
						case '2':
						{
							idx += 7;
							return X11_BISQUE2;
						}
						case '3':
						{
							idx += 7;
							return X11_BISQUE3;
						}
						case '4':
						{
							idx += 7;
							return X11_BISQUE4;
						}
					}
					idx += 6;
					return X11_BISQUE;
				}
				case 'l':
				{
					switch (str[2] | 0x20)
					{
						case 'a':
						{
							switch (str[3] | 0x20)
							{
								case 'c':
								{
									if (str[4] | 0x20 == 'k')
									{
										idx += 5;
										return X11_BLACK;
									}
								}
								case 'n':
								{
									if (!str[4] || strcmp(str[4], !"CHED", true, 4))
									{
										return -1;
									}
									switch (str[8] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[8])
											{
												if (str[9] && !strcmp(str[9], !"ALMOND", true, 6))
												{
													idx += 15;
													return X11_BLANCHED_ALMOND;
												}
											}
										}
										case '_' | 0x20:
										{
											if (str[9] && !strcmp(str[9], !"ALMOND", true, 6))
											{
												idx += 15;
												return X11_BLANCHED_ALMOND;
											}
										}
										case 'a':
										{
											if (str[9] && !strcmp(str[9], !"LMOND", true, 5))
											{
												idx += 14;
												return X11_BLANCHEDALMOND;
											}
										}
									}
								}
							}
						}
						case 'u':
						{
							if (str[3] | 0x20 != 'e')
							{
								return -1;
							}
							switch (str[4] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[4])
									{
										switch (str[5] | 0x20)
										{
											case '1':
											{
												idx += 6;
												return X11_BLUE_1;
											}
											case '2':
											{
												idx += 6;
												return X11_BLUE_2;
											}
											case '3':
											{
												idx += 6;
												return X11_BLUE_3;
											}
											case '4':
											{
												idx += 6;
												return X11_BLUE_4;
											}
											case 'v':
											{
												if (str[6] && !strcmp(str[6], !"IOLET", true, 5))
												{
													idx += 11;
													return X11_BLUE_VIOLET;
												}
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[5] | 0x20)
									{
										case '1':
										{
											idx += 6;
											return X11_BLUE_1;
										}
										case '2':
										{
											idx += 6;
											return X11_BLUE_2;
										}
										case '3':
										{
											idx += 6;
											return X11_BLUE_3;
										}
										case '4':
										{
											idx += 6;
											return X11_BLUE_4;
										}
										case 'v':
										{
											if (str[6] && !strcmp(str[6], !"IOLET", true, 5))
											{
												idx += 11;
												return X11_BLUE_VIOLET;
											}
										}
									}
								}
								case '1':
								{
									idx += 5;
									return X11_BLUE1;
								}
								case '2':
								{
									idx += 5;
									return X11_BLUE2;
								}
								case '3':
								{
									idx += 5;
									return X11_BLUE3;
								}
								case '4':
								{
									idx += 5;
									return X11_BLUE4;
								}
								case 'v':
								{
									if (str[5] && !strcmp(str[5], !"IOLET", true, 5))
									{
										idx += 10;
										return X11_BLUEVIOLET;
									}
								}
							}
							idx += 4;
							return X11_BLUE;
						}
					}
				}
				case 'r':
				{
					if (!str[2] || strcmp(str[2], !"OWN", true, 3))
					{
						return -1;
					}
					switch (str[5] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[5])
							{
								switch (str[6] | 0x20)
								{
									case '1':
									{
										idx += 7;
										return X11_BROWN_1;
									}
									case '2':
									{
										idx += 7;
										return X11_BROWN_2;
									}
									case '3':
									{
										idx += 7;
										return X11_BROWN_3;
									}
									case '4':
									{
										idx += 7;
										return X11_BROWN_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[6] | 0x20)
							{
								case '1':
								{
									idx += 7;
									return X11_BROWN_1;
								}
								case '2':
								{
									idx += 7;
									return X11_BROWN_2;
								}
								case '3':
								{
									idx += 7;
									return X11_BROWN_3;
								}
								case '4':
								{
									idx += 7;
									return X11_BROWN_4;
								}
							}
						}
						case '1':
						{
							idx += 6;
							return X11_BROWN1;
						}
						case '2':
						{
							idx += 6;
							return X11_BROWN2;
						}
						case '3':
						{
							idx += 6;
							return X11_BROWN3;
						}
						case '4':
						{
							idx += 6;
							return X11_BROWN4;
						}
					}
					idx += 5;
					return X11_BROWN;
				}
				case 'u':
				{
					if (!str[2] || strcmp(str[2], !"RLYWOOD", true, 7))
					{
						return -1;
					}
					switch (str[9] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[9])
							{
								switch (str[10] | 0x20)
								{
									case '1':
									{
										idx += 11;
										return X11_BURLYWOOD_1;
									}
									case '2':
									{
										idx += 11;
										return X11_BURLYWOOD_2;
									}
									case '3':
									{
										idx += 11;
										return X11_BURLYWOOD_3;
									}
									case '4':
									{
										idx += 11;
										return X11_BURLYWOOD_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[10] | 0x20)
							{
								case '1':
								{
									idx += 11;
									return X11_BURLYWOOD_1;
								}
								case '2':
								{
									idx += 11;
									return X11_BURLYWOOD_2;
								}
								case '3':
								{
									idx += 11;
									return X11_BURLYWOOD_3;
								}
								case '4':
								{
									idx += 11;
									return X11_BURLYWOOD_4;
								}
							}
						}
						case '1':
						{
							idx += 10;
							return X11_BURLYWOOD1;
						}
						case '2':
						{
							idx += 10;
							return X11_BURLYWOOD2;
						}
						case '3':
						{
							idx += 10;
							return X11_BURLYWOOD3;
						}
						case '4':
						{
							idx += 10;
							return X11_BURLYWOOD4;
						}
					}
					idx += 9;
					return X11_BURLYWOOD;
				}
			}
		}
		case 'c':
		{
			switch (str[1] | 0x20)
			{
				case 'a':
				{
					if (!str[2] || strcmp(str[2], !"DET", true, 3))
					{
						return -1;
					}
					switch (str[5] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[5])
							{
								if (!str[6] || strcmp(str[6], !"BLUE", true, 4))
								{
									return -1;
								}
								switch (str[10] | 0x20)
								{
									case _X11_SPACE_SWITCH: // ' '
									{
										if (str[10])
										{
											switch (str[11] | 0x20)
											{
												case '1':
												{
													idx += 12;
													return X11_CADET_BLUE_1;
												}
												case '2':
												{
													idx += 12;
													return X11_CADET_BLUE_2;
												}
												case '3':
												{
													idx += 12;
													return X11_CADET_BLUE_3;
												}
												case '4':
												{
													idx += 12;
													return X11_CADET_BLUE_4;
												}
											}
										}
									}
									case '_' | 0x20:
									{
										switch (str[11] | 0x20)
										{
											case '1':
											{
												idx += 12;
												return X11_CADET_BLUE_1;
											}
											case '2':
											{
												idx += 12;
												return X11_CADET_BLUE_2;
											}
											case '3':
											{
												idx += 12;
												return X11_CADET_BLUE_3;
											}
											case '4':
											{
												idx += 12;
												return X11_CADET_BLUE_4;
											}
										}
									}
								}
								idx += 10;
								return X11_CADET_BLUE;
							}
						}
						case '_' | 0x20:
						{
							if (!str[6] || strcmp(str[6], !"BLUE", true, 4))
							{
								return -1;
							}
							switch (str[10] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[10])
									{
										switch (str[11] | 0x20)
										{
											case '1':
											{
												idx += 12;
												return X11_CADET_BLUE_1;
											}
											case '2':
											{
												idx += 12;
												return X11_CADET_BLUE_2;
											}
											case '3':
											{
												idx += 12;
												return X11_CADET_BLUE_3;
											}
											case '4':
											{
												idx += 12;
												return X11_CADET_BLUE_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[11] | 0x20)
									{
										case '1':
										{
											idx += 12;
											return X11_CADET_BLUE_1;
										}
										case '2':
										{
											idx += 12;
											return X11_CADET_BLUE_2;
										}
										case '3':
										{
											idx += 12;
											return X11_CADET_BLUE_3;
										}
										case '4':
										{
											idx += 12;
											return X11_CADET_BLUE_4;
										}
									}
								}
							}
							idx += 10;
							return X11_CADET_BLUE;
						}
						case 'b':
						{
							if (!str[6] || strcmp(str[6], !"LUE", true, 3))
							{
								return -1;
							}
							switch (str[9] | 0x20)
							{
								case '1':
								{
									idx += 10;
									return X11_CADETBLUE1;
								}
								case '2':
								{
									idx += 10;
									return X11_CADETBLUE2;
								}
								case '3':
								{
									idx += 10;
									return X11_CADETBLUE3;
								}
								case '4':
								{
									idx += 10;
									return X11_CADETBLUE4;
								}
							}
							idx += 9;
							return X11_CADETBLUE;
						}
					}
				}
				case 'h':
				{
					switch (str[2] | 0x20)
					{
						case 'a':
						{
							if (!str[3] || strcmp(str[3], !"RTREUSE", true, 7))
							{
								return -1;
							}
							switch (str[10] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[10])
									{
										switch (str[11] | 0x20)
										{
											case '1':
											{
												idx += 12;
												return X11_CHARTREUSE_1;
											}
											case '2':
											{
												idx += 12;
												return X11_CHARTREUSE_2;
											}
											case '3':
											{
												idx += 12;
												return X11_CHARTREUSE_3;
											}
											case '4':
											{
												idx += 12;
												return X11_CHARTREUSE_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[11] | 0x20)
									{
										case '1':
										{
											idx += 12;
											return X11_CHARTREUSE_1;
										}
										case '2':
										{
											idx += 12;
											return X11_CHARTREUSE_2;
										}
										case '3':
										{
											idx += 12;
											return X11_CHARTREUSE_3;
										}
										case '4':
										{
											idx += 12;
											return X11_CHARTREUSE_4;
										}
									}
								}
								case '1':
								{
									idx += 11;
									return X11_CHARTREUSE1;
								}
								case '2':
								{
									idx += 11;
									return X11_CHARTREUSE2;
								}
								case '3':
								{
									idx += 11;
									return X11_CHARTREUSE3;
								}
								case '4':
								{
									idx += 11;
									return X11_CHARTREUSE4;
								}
							}
							idx += 10;
							return X11_CHARTREUSE;
						}
						case 'o':
						{
							if (!str[3] || strcmp(str[3], !"COLATE", true, 6))
							{
								return -1;
							}
							switch (str[9] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[9])
									{
										switch (str[10] | 0x20)
										{
											case '1':
											{
												idx += 11;
												return X11_CHOCOLATE_1;
											}
											case '2':
											{
												idx += 11;
												return X11_CHOCOLATE_2;
											}
											case '3':
											{
												idx += 11;
												return X11_CHOCOLATE_3;
											}
											case '4':
											{
												idx += 11;
												return X11_CHOCOLATE_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[10] | 0x20)
									{
										case '1':
										{
											idx += 11;
											return X11_CHOCOLATE_1;
										}
										case '2':
										{
											idx += 11;
											return X11_CHOCOLATE_2;
										}
										case '3':
										{
											idx += 11;
											return X11_CHOCOLATE_3;
										}
										case '4':
										{
											idx += 11;
											return X11_CHOCOLATE_4;
										}
									}
								}
								case '1':
								{
									idx += 10;
									return X11_CHOCOLATE1;
								}
								case '2':
								{
									idx += 10;
									return X11_CHOCOLATE2;
								}
								case '3':
								{
									idx += 10;
									return X11_CHOCOLATE3;
								}
								case '4':
								{
									idx += 10;
									return X11_CHOCOLATE4;
								}
							}
							idx += 9;
							return X11_CHOCOLATE;
						}
					}
				}
				case 'o':
				{
					if (str[2] | 0x20 != 'r')
					{
						return -1;
					}
					switch (str[3] | 0x20)
					{
						case 'a':
						{
							if (str[4] | 0x20 != 'l')
							{
								return -1;
							}
							switch (str[5] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[5])
									{
										switch (str[6] | 0x20)
										{
											case '1':
											{
												idx += 7;
												return X11_CORAL_1;
											}
											case '2':
											{
												idx += 7;
												return X11_CORAL_2;
											}
											case '3':
											{
												idx += 7;
												return X11_CORAL_3;
											}
											case '4':
											{
												idx += 7;
												return X11_CORAL_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[6] | 0x20)
									{
										case '1':
										{
											idx += 7;
											return X11_CORAL_1;
										}
										case '2':
										{
											idx += 7;
											return X11_CORAL_2;
										}
										case '3':
										{
											idx += 7;
											return X11_CORAL_3;
										}
										case '4':
										{
											idx += 7;
											return X11_CORAL_4;
										}
									}
								}
								case '1':
								{
									idx += 6;
									return X11_CORAL1;
								}
								case '2':
								{
									idx += 6;
									return X11_CORAL2;
								}
								case '3':
								{
									idx += 6;
									return X11_CORAL3;
								}
								case '4':
								{
									idx += 6;
									return X11_CORAL4;
								}
							}
							idx += 5;
							return X11_CORAL;
						}
						case 'n':
						{
							switch (str[4] | 0x20)
							{
								case 'f':
								{
									if (!str[5] || strcmp(str[5], !"LOWER", true, 5))
									{
										return -1;
									}
									switch (str[10] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[10])
											{
												if (str[11] && !strcmp(str[11], !"BLUE", true, 4))
												{
													idx += 15;
													return X11_CORNFLOWER_BLUE;
												}
											}
										}
										case '_' | 0x20:
										{
											if (str[11] && !strcmp(str[11], !"BLUE", true, 4))
											{
												idx += 15;
												return X11_CORNFLOWER_BLUE;
											}
										}
										case 'b':
										{
											if (str[11] && !strcmp(str[11], !"LUE", true, 3))
											{
												idx += 14;
												return X11_CORNFLOWERBLUE;
											}
										}
									}
								}
								case 's':
								{
									if (!str[5] || strcmp(str[5], !"ILK", true, 3))
									{
										return -1;
									}
									switch (str[8] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[8])
											{
												switch (str[9] | 0x20)
												{
													case '1':
													{
														idx += 10;
														return X11_CORNSILK_1;
													}
													case '2':
													{
														idx += 10;
														return X11_CORNSILK_2;
													}
													case '3':
													{
														idx += 10;
														return X11_CORNSILK_3;
													}
													case '4':
													{
														idx += 10;
														return X11_CORNSILK_4;
													}
												}
											}
										}
										case '_' | 0x20:
										{
											switch (str[9] | 0x20)
											{
												case '1':
												{
													idx += 10;
													return X11_CORNSILK_1;
												}
												case '2':
												{
													idx += 10;
													return X11_CORNSILK_2;
												}
												case '3':
												{
													idx += 10;
													return X11_CORNSILK_3;
												}
												case '4':
												{
													idx += 10;
													return X11_CORNSILK_4;
												}
											}
										}
										case '1':
										{
											idx += 9;
											return X11_CORNSILK1;
										}
										case '2':
										{
											idx += 9;
											return X11_CORNSILK2;
										}
										case '3':
										{
											idx += 9;
											return X11_CORNSILK3;
										}
										case '4':
										{
											idx += 9;
											return X11_CORNSILK4;
										}
									}
									idx += 8;
									return X11_CORNSILK;
								}
							}
						}
					}
				}
				case 'y':
				{
					if (!str[2] || strcmp(str[2], !"AN", true, 2))
					{
						return -1;
					}
					switch (str[4] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[4])
							{
								switch (str[5] | 0x20)
								{
									case '1':
									{
										idx += 6;
										return X11_CYAN_1;
									}
									case '2':
									{
										idx += 6;
										return X11_CYAN_2;
									}
									case '3':
									{
										idx += 6;
										return X11_CYAN_3;
									}
									case '4':
									{
										idx += 6;
										return X11_CYAN_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[5] | 0x20)
							{
								case '1':
								{
									idx += 6;
									return X11_CYAN_1;
								}
								case '2':
								{
									idx += 6;
									return X11_CYAN_2;
								}
								case '3':
								{
									idx += 6;
									return X11_CYAN_3;
								}
								case '4':
								{
									idx += 6;
									return X11_CYAN_4;
								}
							}
						}
						case '1':
						{
							idx += 5;
							return X11_CYAN1;
						}
						case '2':
						{
							idx += 5;
							return X11_CYAN2;
						}
						case '3':
						{
							idx += 5;
							return X11_CYAN3;
						}
						case '4':
						{
							idx += 5;
							return X11_CYAN4;
						}
					}
					idx += 4;
					return X11_CYAN;
				}
			}
		}
		case 'd':
		{
			switch (str[1] | 0x20)
			{
				case 'a':
				{
					if (!str[2] || strcmp(str[2], !"RK", true, 2))
					{
						return -1;
					}
					switch (str[4] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[4])
							{
								switch (str[5] | 0x20)
								{
									case 'b':
									{
										if (str[6] && !strcmp(str[6], !"LUE", true, 3))
										{
											idx += 9;
											return X11_DARK_BLUE;
										}
									}
									case 'c':
									{
										if (str[6] && !strcmp(str[6], !"YAN", true, 3))
										{
											idx += 9;
											return X11_DARK_CYAN;
										}
									}
									case 'g':
									{
										switch (str[6] | 0x20)
										{
											case 'o':
											{
												if (!str[7] || strcmp(str[7], !"LDENROD", true, 7))
												{
													return -1;
												}
												switch (str[14] | 0x20)
												{
													case _X11_SPACE_SWITCH: // ' '
													{
														if (str[14])
														{
															switch (str[15] | 0x20)
															{
																case '1':
																{
																	idx += 16;
																	return X11_DARK_GOLDENROD_1;
																}
																case '2':
																{
																	idx += 16;
																	return X11_DARK_GOLDENROD_2;
																}
																case '3':
																{
																	idx += 16;
																	return X11_DARK_GOLDENROD_3;
																}
																case '4':
																{
																	idx += 16;
																	return X11_DARK_GOLDENROD_4;
																}
															}
														}
													}
													case '_' | 0x20:
													{
														switch (str[15] | 0x20)
														{
															case '1':
															{
																idx += 16;
																return X11_DARK_GOLDENROD_1;
															}
															case '2':
															{
																idx += 16;
																return X11_DARK_GOLDENROD_2;
															}
															case '3':
															{
																idx += 16;
																return X11_DARK_GOLDENROD_3;
															}
															case '4':
															{
																idx += 16;
																return X11_DARK_GOLDENROD_4;
															}
														}
													}
												}
												idx += 14;
												return X11_DARK_GOLDENROD;
											}
											case 'r':
											{
												switch (str[7] | 0x20)
												{
													case 'a':
													{
														if (str[8] | 0x20 == 'y')
														{
															idx += 9;
															return X11_DARK_GRAY;
														}
													}
													case 'e':
													{
														switch (str[8] | 0x20)
														{
															case 'e':
															{
																if (str[9] | 0x20 == 'n')
																{
																	idx += 10;
																	return X11_DARK_GREEN;
																}
															}
															case 'y':
															{
																idx += 9;
																return X11_DARK_GREY;
															}
														}
													}
												}
											}
										}
									}
									case 'k':
									{
										if (str[6] && !strcmp(str[6], !"HAKI", true, 4))
										{
											idx += 10;
											return X11_DARK_KHAKI;
										}
									}
									case 'm':
									{
										if (str[6] && !strcmp(str[6], !"AGENTA", true, 6))
										{
											idx += 12;
											return X11_DARK_MAGENTA;
										}
									}
									case 'o':
									{
										switch (str[6] | 0x20)
										{
											case 'l':
											{
												if (!str[7] || strcmp(str[7], !"IVE", true, 3) || (!_X11_SPACE_CHECK(10) && str[10] != '_') || strcmp(str[11], !"GREEN", true, 5))
												//if (!str[7] || strcmp(str[7], !"IVE_GREEN", true, 9))
												{
													return -1;
												}
												switch (str[16] | 0x20)
												{
													case _X11_SPACE_SWITCH: // ' '
													{
														if (str[16])
														{
															switch (str[17] | 0x20)
															{
																case '1':
																{
																	idx += 18;
																	return X11_DARK_OLIVE_GREEN_1;
																}
																case '2':
																{
																	idx += 18;
																	return X11_DARK_OLIVE_GREEN_2;
																}
																case '3':
																{
																	idx += 18;
																	return X11_DARK_OLIVE_GREEN_3;
																}
																case '4':
																{
																	idx += 18;
																	return X11_DARK_OLIVE_GREEN_4;
																}
															}
														}
													}
													case '_' | 0x20:
													{
														switch (str[17] | 0x20)
														{
															case '1':
															{
																idx += 18;
																return X11_DARK_OLIVE_GREEN_1;
															}
															case '2':
															{
																idx += 18;
																return X11_DARK_OLIVE_GREEN_2;
															}
															case '3':
															{
																idx += 18;
																return X11_DARK_OLIVE_GREEN_3;
															}
															case '4':
															{
																idx += 18;
																return X11_DARK_OLIVE_GREEN_4;
															}
														}
													}
												}
												idx += 16;
												return X11_DARK_OLIVE_GREEN;
											}
											case 'r':
											{
												switch (str[7] | 0x20)
												{
													case 'a':
													{
														if (!str[8] || strcmp(str[8], !"NGE", true, 3))
														{
															return -1;
														}
														switch (str[11] | 0x20)
														{
															case _X11_SPACE_SWITCH: // ' '
															{
																if (str[11])
																{
																	switch (str[12] | 0x20)
																	{
																		case '1':
																		{
																			idx += 13;
																			return X11_DARK_ORANGE_1;
																		}
																		case '2':
																		{
																			idx += 13;
																			return X11_DARK_ORANGE_2;
																		}
																		case '3':
																		{
																			idx += 13;
																			return X11_DARK_ORANGE_3;
																		}
																		case '4':
																		{
																			idx += 13;
																			return X11_DARK_ORANGE_4;
																		}
																	}
																}
															}
															case '_' | 0x20:
															{
																switch (str[12] | 0x20)
																{
																	case '1':
																	{
																		idx += 13;
																		return X11_DARK_ORANGE_1;
																	}
																	case '2':
																	{
																		idx += 13;
																		return X11_DARK_ORANGE_2;
																	}
																	case '3':
																	{
																		idx += 13;
																		return X11_DARK_ORANGE_3;
																	}
																	case '4':
																	{
																		idx += 13;
																		return X11_DARK_ORANGE_4;
																	}
																}
															}
														}
														idx += 11;
														return X11_DARK_ORANGE;
													}
													case 'c':
													{
														if (!str[8] || strcmp(str[8], !"HID", true, 3))
														{
															return -1;
														}
														switch (str[11] | 0x20)
														{
															case _X11_SPACE_SWITCH: // ' '
															{
																if (str[11])
																{
																	switch (str[12] | 0x20)
																	{
																		case '1':
																		{
																			idx += 13;
																			return X11_DARK_ORCHID_1;
																		}
																		case '2':
																		{
																			idx += 13;
																			return X11_DARK_ORCHID_2;
																		}
																		case '3':
																		{
																			idx += 13;
																			return X11_DARK_ORCHID_3;
																		}
																		case '4':
																		{
																			idx += 13;
																			return X11_DARK_ORCHID_4;
																		}
																	}
																}
															}
															case '_' | 0x20:
															{
																switch (str[12] | 0x20)
																{
																	case '1':
																	{
																		idx += 13;
																		return X11_DARK_ORCHID_1;
																	}
																	case '2':
																	{
																		idx += 13;
																		return X11_DARK_ORCHID_2;
																	}
																	case '3':
																	{
																		idx += 13;
																		return X11_DARK_ORCHID_3;
																	}
																	case '4':
																	{
																		idx += 13;
																		return X11_DARK_ORCHID_4;
																	}
																}
															}
														}
														idx += 11;
														return X11_DARK_ORCHID;
													}
												}
											}
										}
									}
									case 'r':
									{
										if (str[6] && !strcmp(str[6], !"ED", true, 2))
										{
											idx += 8;
											return X11_DARK_RED;
										}
									}
									case 's':
									{
										switch (str[6] | 0x20)
										{
											case 'a':
											{
												if (str[7] && !strcmp(str[7], !"LMON", true, 4))
												{
													idx += 11;
													return X11_DARK_SALMON;
												}
											}
											case 'e':
											{
												if (str[7] | 0x20 != 'a' || (!_X11_SPACE_CHECK(8) && str[8] != '_') || strcmp(str[9], !"GREEN", true, 5))
												//if (!str[7] || strcmp(str[7], !"A_GREEN", true, 7))
												{
													return -1;
												}
												switch (str[14] | 0x20)
												{
													case _X11_SPACE_SWITCH: // ' '
													{
														if (str[14])
														{
															switch (str[15] | 0x20)
															{
																case '1':
																{
																	idx += 16;
																	return X11_DARK_SEA_GREEN_1;
																}
																case '2':
																{
																	idx += 16;
																	return X11_DARK_SEA_GREEN_2;
																}
																case '3':
																{
																	idx += 16;
																	return X11_DARK_SEA_GREEN_3;
																}
																case '4':
																{
																	idx += 16;
																	return X11_DARK_SEA_GREEN_4;
																}
															}
														}
													}
													case '_' | 0x20:
													{
														switch (str[15] | 0x20)
														{
															case '1':
															{
																idx += 16;
																return X11_DARK_SEA_GREEN_1;
															}
															case '2':
															{
																idx += 16;
																return X11_DARK_SEA_GREEN_2;
															}
															case '3':
															{
																idx += 16;
																return X11_DARK_SEA_GREEN_3;
															}
															case '4':
															{
																idx += 16;
																return X11_DARK_SEA_GREEN_4;
															}
														}
													}
												}
												idx += 14;
												return X11_DARK_SEA_GREEN;
											}
											case 'l':
											{
												if (!str[7] || strcmp(str[7], !"ATE", true, 3) || (!_X11_SPACE_CHECK(10) && str[10] != '_'))
												//if (!str[7] || strcmp(str[7], !"ATE_", true, 4))
												{
													return -1;
												}
												switch (str[11] | 0x20)
												{
													case 'b':
													{
														if (str[12] && !strcmp(str[12], !"LUE", true, 3))
														{
															idx += 15;
															return X11_DARK_SLATE_BLUE;
														}
													}
													case 'g':
													{
														if (str[12] | 0x20 != 'r')
														{
															return -1;
														}
														switch (str[13] | 0x20)
														{
															case 'a':
															{
																if (str[14] | 0x20 != 'y')
																{
																	return -1;
																}
																switch (str[15] | 0x20)
																{
																	case _X11_SPACE_SWITCH: // ' '
																	{
																		if (str[15])
																		{
																			switch (str[16] | 0x20)
																			{
																				case '1':
																				{
																					idx += 17;
																					return X11_DARK_SLATE_GRAY_1;
																				}
																				case '2':
																				{
																					idx += 17;
																					return X11_DARK_SLATE_GRAY_2;
																				}
																				case '3':
																				{
																					idx += 17;
																					return X11_DARK_SLATE_GRAY_3;
																				}
																				case '4':
																				{
																					idx += 17;
																					return X11_DARK_SLATE_GRAY_4;
																				}
																			}
																		}
																	}
																	case '_' | 0x20:
																	{
																		switch (str[16] | 0x20)
																		{
																			case '1':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GRAY_1;
																			}
																			case '2':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GRAY_2;
																			}
																			case '3':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GRAY_3;
																			}
																			case '4':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GRAY_4;
																			}
																		}
																	}
																}
																idx += 15;
																return X11_DARK_SLATE_GRAY;
															}
															case 'e':
															{
																if (str[14] | 0x20 != 'y')
																{
																	return -1;
																}
																switch (str[15] | 0x20)
																{
																	case _X11_SPACE_SWITCH: // ' '
																	{
																		if (str[15])
																		{
																			switch (str[16] | 0x20)
																			{
																				case '1':
																				{
																					idx += 17;
																					return X11_DARK_SLATE_GREY_1;
																				}
																				case '2':
																				{
																					idx += 17;
																					return X11_DARK_SLATE_GREY_2;
																				}
																				case '3':
																				{
																					idx += 17;
																					return X11_DARK_SLATE_GREY_3;
																				}
																				case '4':
																				{
																					idx += 17;
																					return X11_DARK_SLATE_GREY_4;
																				}
																			}
																		}
																	}
																	case '_' | 0x20:
																	{
																		switch (str[16] | 0x20)
																		{
																			case '1':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GREY_1;
																			}
																			case '2':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GREY_2;
																			}
																			case '3':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GREY_3;
																			}
																			case '4':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GREY_4;
																			}
																		}
																	}
																}
																idx += 15;
																return X11_DARK_SLATE_GRAY;
															}
														}
													}
												}
											}
										}
									}
									case 't':
									{
										if (str[6] && !strcmp(str[6], !"URQUOISE", true, 8))
										{
											idx += 14;
											return X11_DARK_TURQUOISE;
										}
									}
									case 'v':
									{
										if (str[6] && !strcmp(str[6], !"IOLET", true, 5))
										{
											idx += 11;
											return X11_DARK_VIOLET;
										}
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[5] | 0x20)
							{
								case 'b':
								{
									if (str[6] && !strcmp(str[6], !"LUE", true, 3))
									{
										idx += 9;
										return X11_DARK_BLUE;
									}
								}
								case 'c':
								{
									if (str[6] && !strcmp(str[6], !"YAN", true, 3))
									{
										idx += 9;
										return X11_DARK_CYAN;
									}
								}
								case 'g':
								{
									switch (str[6] | 0x20)
									{
										case 'o':
										{
											if (!str[7] || strcmp(str[7], !"LDENROD", true, 7))
											{
												return -1;
											}
											switch (str[14] | 0x20)
											{
												case _X11_SPACE_SWITCH: // ' '
												{
													if (str[14])
													{
														switch (str[15] | 0x20)
														{
															case '1':
															{
																idx += 16;
																return X11_DARK_GOLDENROD_1;
															}
															case '2':
															{
																idx += 16;
																return X11_DARK_GOLDENROD_2;
															}
															case '3':
															{
																idx += 16;
																return X11_DARK_GOLDENROD_3;
															}
															case '4':
															{
																idx += 16;
																return X11_DARK_GOLDENROD_4;
															}
														}
													}
												}
												case '_' | 0x20:
												{
													switch (str[15] | 0x20)
													{
														case '1':
														{
															idx += 16;
															return X11_DARK_GOLDENROD_1;
														}
														case '2':
														{
															idx += 16;
															return X11_DARK_GOLDENROD_2;
														}
														case '3':
														{
															idx += 16;
															return X11_DARK_GOLDENROD_3;
														}
														case '4':
														{
															idx += 16;
															return X11_DARK_GOLDENROD_4;
														}
													}
												}
											}
											idx += 14;
											return X11_DARK_GOLDENROD;
										}
										case 'r':
										{
											switch (str[7] | 0x20)
											{
												case 'a':
												{
													if (str[8] | 0x20 == 'y')
													{
														idx += 9;
														return X11_DARK_GRAY;
													}
												}
												case 'e':
												{
													switch (str[8] | 0x20)
													{
														case 'e':
														{
															if (str[9] | 0x20 == 'n')
															{
																idx += 10;
																return X11_DARK_GREEN;
															}
														}
														case 'y':
														{
															idx += 9;
															return X11_DARK_GREY;
														}
													}
												}
											}
										}
									}
								}
								case 'k':
								{
									if (str[6] && !strcmp(str[6], !"HAKI", true, 4))
									{
										idx += 10;
										return X11_DARK_KHAKI;
									}
								}
								case 'm':
								{
									if (str[6] && !strcmp(str[6], !"AGENTA", true, 6))
									{
										idx += 12;
										return X11_DARK_MAGENTA;
									}
								}
								case 'o':
								{
									switch (str[6] | 0x20)
									{
										case 'l':
										{
											if (!str[7] || strcmp(str[7], !"IVE", true, 3) || (!_X11_SPACE_CHECK(10) && str[10] != '_') || strcmp(str[11], !"GREEN", true, 5))
											{
												return -1;
											}
											switch (str[16] | 0x20)
											{
												case _X11_SPACE_SWITCH: // ' '
												{
													if (str[16])
													{
														switch (str[17] | 0x20)
														{
															case '1':
															{
																idx += 18;
																return X11_DARK_OLIVE_GREEN_1;
															}
															case '2':
															{
																idx += 18;
																return X11_DARK_OLIVE_GREEN_2;
															}
															case '3':
															{
																idx += 18;
																return X11_DARK_OLIVE_GREEN_3;
															}
															case '4':
															{
																idx += 18;
																return X11_DARK_OLIVE_GREEN_4;
															}
														}
													}
												}
												case '_' | 0x20:
												{
													switch (str[17] | 0x20)
													{
														case '1':
														{
															idx += 18;
															return X11_DARK_OLIVE_GREEN_1;
														}
														case '2':
														{
															idx += 18;
															return X11_DARK_OLIVE_GREEN_2;
														}
														case '3':
														{
															idx += 18;
															return X11_DARK_OLIVE_GREEN_3;
														}
														case '4':
														{
															idx += 18;
															return X11_DARK_OLIVE_GREEN_4;
														}
													}
												}
											}
											idx += 16;
											return X11_DARK_OLIVE_GREEN;
										}
										case 'r':
										{
											switch (str[7] | 0x20)
											{
												case 'a':
												{
													if (!str[8] || strcmp(str[8], !"NGE", true, 3))
													{
														return -1;
													}
													switch (str[11] | 0x20)
													{
														case _X11_SPACE_SWITCH: // ' '
														{
															if (str[11])
															{
																switch (str[12] | 0x20)
																{
																	case '1':
																	{
																		idx += 13;
																		return X11_DARK_ORANGE_1;
																	}
																	case '2':
																	{
																		idx += 13;
																		return X11_DARK_ORANGE_2;
																	}
																	case '3':
																	{
																		idx += 13;
																		return X11_DARK_ORANGE_3;
																	}
																	case '4':
																	{
																		idx += 13;
																		return X11_DARK_ORANGE_4;
																	}
																}
															}
														}
														case '_' | 0x20:
														{
															switch (str[12] | 0x20)
															{
																case '1':
																{
																	idx += 13;
																	return X11_DARK_ORANGE_1;
																}
																case '2':
																{
																	idx += 13;
																	return X11_DARK_ORANGE_2;
																}
																case '3':
																{
																	idx += 13;
																	return X11_DARK_ORANGE_3;
																}
																case '4':
																{
																	idx += 13;
																	return X11_DARK_ORANGE_4;
																}
															}
														}
													}
													idx += 11;
													return X11_DARK_ORANGE;
												}
												case 'c':
												{
													if (!str[8] || strcmp(str[8], !"HID", true, 3))
													{
														return -1;
													}
													switch (str[11] | 0x20)
													{
														case _X11_SPACE_SWITCH: // ' '
														{
															if (str[11])
															{
																switch (str[12] | 0x20)
																{
																	case '1':
																	{
																		idx += 13;
																		return X11_DARK_ORCHID_1;
																	}
																	case '2':
																	{
																		idx += 13;
																		return X11_DARK_ORCHID_2;
																	}
																	case '3':
																	{
																		idx += 13;
																		return X11_DARK_ORCHID_3;
																	}
																	case '4':
																	{
																		idx += 13;
																		return X11_DARK_ORCHID_4;
																	}
																}
															}
														}
														case '_' | 0x20:
														{
															switch (str[12] | 0x20)
															{
																case '1':
																{
																	idx += 13;
																	return X11_DARK_ORCHID_1;
																}
																case '2':
																{
																	idx += 13;
																	return X11_DARK_ORCHID_2;
																}
																case '3':
																{
																	idx += 13;
																	return X11_DARK_ORCHID_3;
																}
																case '4':
																{
																	idx += 13;
																	return X11_DARK_ORCHID_4;
																}
															}
														}
													}
													idx += 11;
													return X11_DARK_ORCHID;
												}
											}
										}
									}
								}
								case 'r':
								{
									if (str[6] && !strcmp(str[6], !"ED", true, 2))
									{
										idx += 8;
										return X11_DARK_RED;
									}
								}
								case 's':
								{
									switch (str[6] | 0x20)
									{
										case 'a':
										{
											if (str[7] && !strcmp(str[7], !"LMON", true, 4))
											{
												idx += 11;
												return X11_DARK_SALMON;
											}
										}
										case 'e':
										{
											//if (!str[7] || strcmp(str[7], !"A_GREEN", true, 7))
											if (str[7] | 0x20 != 'a' || (!_X11_SPACE_CHECK(8) && str[8] != '_') || strcmp(str[9], !"GREEN", true, 5))
											{
												return -1;
											}
											switch (str[14] | 0x20)
											{
												case _X11_SPACE_SWITCH: // ' '
												{
													if (str[14])
													{
														switch (str[15] | 0x20)
														{
															case '1':
															{
																idx += 16;
																return X11_DARK_SEA_GREEN_1;
															}
															case '2':
															{
																idx += 16;
																return X11_DARK_SEA_GREEN_2;
															}
															case '3':
															{
																idx += 16;
																return X11_DARK_SEA_GREEN_3;
															}
															case '4':
															{
																idx += 16;
																return X11_DARK_SEA_GREEN_4;
															}
														}
													}
												}
												case '_' | 0x20:
												{
													switch (str[15] | 0x20)
													{
														case '1':
														{
															idx += 16;
															return X11_DARK_SEA_GREEN_1;
														}
														case '2':
														{
															idx += 16;
															return X11_DARK_SEA_GREEN_2;
														}
														case '3':
														{
															idx += 16;
															return X11_DARK_SEA_GREEN_3;
														}
														case '4':
														{
															idx += 16;
															return X11_DARK_SEA_GREEN_4;
														}
													}
												}
											}
											idx += 14;
											return X11_DARK_SEA_GREEN;
										}
										case 'l':
										{
											//if (!str[7] || strcmp(str[7], !"ATE_", true, 4))
											if (!str[7] || strcmp(str[7], !"ATE", true, 3) || (!_X11_SPACE_CHECK(10) && str[10] != '_'))
											{
												return -1;
											}
											switch (str[11] | 0x20)
											{
												case 'b':
												{
													if (str[12] && !strcmp(str[12], !"LUE", true, 3))
													{
														idx += 15;
														return X11_DARK_SLATE_BLUE;
													}
												}
												case 'g':
												{
													if (str[12] | 0x20 != 'r')
													{
														return -1;
													}
													switch (str[13] | 0x20)
													{
														case 'a':
														{
															if (str[14] | 0x20 != 'y')
															{
																return -1;
															}
															switch (str[15] | 0x20)
															{
																case _X11_SPACE_SWITCH: // ' '
																{
																	if (str[15])
																	{
																		switch (str[16] | 0x20)
																		{
																			case '1':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GRAY_1;
																			}
																			case '2':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GRAY_2;
																			}
																			case '3':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GRAY_3;
																			}
																			case '4':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GRAY_4;
																			}
																		}
																	}
																}
																case '_' | 0x20:
																{
																	switch (str[16] | 0x20)
																	{
																		case '1':
																		{
																			idx += 17;
																			return X11_DARK_SLATE_GRAY_1;
																		}
																		case '2':
																		{
																			idx += 17;
																			return X11_DARK_SLATE_GRAY_2;
																		}
																		case '3':
																		{
																			idx += 17;
																			return X11_DARK_SLATE_GRAY_3;
																		}
																		case '4':
																		{
																			idx += 17;
																			return X11_DARK_SLATE_GRAY_4;
																		}
																	}
																}
															}
															idx += 15;
															return X11_DARK_SLATE_GRAY;
														}
														case 'e':
														{
															if (str[14] | 0x20 != 'y')
															{
																return -1;
															}
															switch (str[15] | 0x20)
															{
																case _X11_SPACE_SWITCH: // ' '
																{
																	if (str[15])
																	{
																		switch (str[16] | 0x20)
																		{
																			case '1':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GREY_1;
																			}
																			case '2':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GREY_2;
																			}
																			case '3':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GREY_3;
																			}
																			case '4':
																			{
																				idx += 17;
																				return X11_DARK_SLATE_GREY_4;
																			}
																		}
																	}
																}
																case '_' | 0x20:
																{
																	switch (str[16] | 0x20)
																	{
																		case '1':
																		{
																			idx += 17;
																			return X11_DARK_SLATE_GREY_1;
																		}
																		case '2':
																		{
																			idx += 17;
																			return X11_DARK_SLATE_GREY_2;
																		}
																		case '3':
																		{
																			idx += 17;
																			return X11_DARK_SLATE_GREY_3;
																		}
																		case '4':
																		{
																			idx += 17;
																			return X11_DARK_SLATE_GREY_4;
																		}
																	}
																}
															}
															idx += 15;
															return X11_DARK_SLATE_GRAY;
														}
													}
												}
											}
										}
									}
								}
								case 't':
								{
									if (str[6] && !strcmp(str[6], !"URQUOISE", true, 8))
									{
										idx += 14;
										return X11_DARK_TURQUOISE;
									}
								}
								case 'v':
								{
									if (str[6] && !strcmp(str[6], !"IOLET", true, 5))
									{
										idx += 11;
										return X11_DARK_VIOLET;
									}
								}
							}
						}
						case 'b':
						{
							if (str[5] && !strcmp(str[5], !"LUE", true, 3))
							{
								idx += 8;
								return X11_DARKBLUE;
							}
						}
						case 'c':
						{
							if (str[5] && !strcmp(str[5], !"YAN", true, 3))
							{
								idx += 8;
								return X11_DARKCYAN;
							}
						}
						case 'g':
						{
							switch (str[5] | 0x20)
							{
								case 'o':
								{
									if (!str[6] || strcmp(str[6], !"LDENROD", true, 7))
									{
										return -1;
									}
									switch (str[13] | 0x20)
									{
										case '1':
										{
											idx += 14;
											return X11_DARKGOLDENROD1;
										}
										case '2':
										{
											idx += 14;
											return X11_DARKGOLDENROD2;
										}
										case '3':
										{
											idx += 14;
											return X11_DARKGOLDENROD3;
										}
										case '4':
										{
											idx += 14;
											return X11_DARKGOLDENROD4;
										}
									}
									idx += 13;
									return X11_DARKGOLDENROD;
								}
								case 'r':
								{
									switch (str[6] | 0x20)
									{
										case 'a':
										{
											if (str[7] | 0x20 == 'y')
											{
												idx += 8;
												return X11_DARKGRAY;
											}
										}
										case 'e':
										{
											switch (str[7] | 0x20)
											{
												case 'e':
												{
													if (str[8] | 0x20 == 'n')
													{
														idx += 9;
														return X11_DARKGREEN;
													}
												}
												case 'y':
												{
													idx += 8;
													return X11_DARKGREY;
												}
											}
										}
									}
								}
							}
						}
						case 'k':
						{
							if (str[5] && !strcmp(str[5], !"HAKI", true, 4))
							{
								idx += 9;
								return X11_DARKKHAKI;
							}
						}
						case 'm':
						{
							if (str[5] && !strcmp(str[5], !"AGENTA", true, 6))
							{
								idx += 11;
								return X11_DARKMAGENTA;
							}
						}
						case 'o':
						{
							switch (str[5] | 0x20)
							{
								case 'l':
								{
									if (!str[6] || strcmp(str[6], !"IVEGREEN", true, 8))
									{
										return -1;
									}
									switch (str[14] | 0x20)
									{
										case '1':
										{
											idx += 15;
											return X11_DARKOLIVEGREEN1;
										}
										case '2':
										{
											idx += 15;
											return X11_DARKOLIVEGREEN2;
										}
										case '3':
										{
											idx += 15;
											return X11_DARKOLIVEGREEN3;
										}
										case '4':
										{
											idx += 15;
											return X11_DARKOLIVEGREEN4;
										}
									}
									idx += 14;
									return X11_DARKOLIVEGREEN;
								}
								case 'r':
								{
									switch (str[6] | 0x20)
									{
										case 'a':
										{
											if (!str[7] || strcmp(str[7], !"NGE", true, 3))
											{
												return -1;
											}
											switch (str[10] | 0x20)
											{
												case '1':
												{
													idx += 11;
													return X11_DARKORANGE1;
												}
												case '2':
												{
													idx += 11;
													return X11_DARKORANGE2;
												}
												case '3':
												{
													idx += 11;
													return X11_DARKORANGE3;
												}
												case '4':
												{
													idx += 11;
													return X11_DARKORANGE4;
												}
											}
											idx += 10;
											return X11_DARKORANGE;
										}
										case 'c':
										{
											if (!str[7] || strcmp(str[7], !"HID", true, 3))
											{
												return -1;
											}
											switch (str[10] | 0x20)
											{
												case '1':
												{
													idx += 11;
													return X11_DARKORCHID1;
												}
												case '2':
												{
													idx += 11;
													return X11_DARKORCHID2;
												}
												case '3':
												{
													idx += 11;
													return X11_DARKORCHID3;
												}
												case '4':
												{
													idx += 11;
													return X11_DARKORCHID4;
												}
											}
											idx += 10;
											return X11_DARKORCHID;
										}
									}
								}
							}
						}
						case 'r':
						{
							if (str[5] && !strcmp(str[5], !"ED", true, 2))
							{
								idx += 7;
								return X11_DARKRED;
							}
						}
						case 's':
						{
							switch (str[5] | 0x20)
							{
								case 'a':
								{
									if (str[6] && !strcmp(str[6], !"LMON", true, 4))
									{
										idx += 10;
										return X11_DARKSALMON;
									}
								}
								case 'e':
								{
									if (!str[6] || strcmp(str[6], !"AGREEN", true, 6))
									{
										return -1;
									}
									switch (str[12] | 0x20)
									{
										case '1':
										{
											idx += 13;
											return X11_DARKSEAGREEN1;
										}
										case '2':
										{
											idx += 13;
											return X11_DARKSEAGREEN2;
										}
										case '3':
										{
											idx += 13;
											return X11_DARKSEAGREEN3;
										}
										case '4':
										{
											idx += 13;
											return X11_DARKSEAGREEN4;
										}
									}
									idx += 12;
									return X11_DARKSEAGREEN;
								}
								case 'l':
								{
									if (!str[6] || strcmp(str[6], !"ATE", true, 3))
									{
										return -1;
									}
									switch (str[9] | 0x20)
									{
										case 'b':
										{
											if (str[10] && !strcmp(str[10], !"LUE", true, 3))
											{
												idx += 13;
												return X11_DARKSLATEBLUE;
											}
										}
										case 'g':
										{
											if (str[10] | 0x20 != 'r')
											{
												return -1;
											}
											switch (str[11] | 0x20)
											{
												case 'a':
												{
													if (str[12] | 0x20 != 'y')
													{
														return -1;
													}
													switch (str[13] | 0x20)
													{
														case '1':
														{
															idx += 14;
															return X11_DARKSLATEGRAY1;
														}
														case '2':
														{
															idx += 14;
															return X11_DARKSLATEGRAY2;
														}
														case '3':
														{
															idx += 14;
															return X11_DARKSLATEGRAY3;
														}
														case '4':
														{
															idx += 14;
															return X11_DARKSLATEGRAY4;
														}
													}
													idx += 13;
													return X11_DARKSLATEGRAY;
												}
												case 'e':
												{
													if (str[12] | 0x20 != 'y')
													{
														return -1;
													}
													switch (str[13] | 0x20)
													{
														case '1':
														{
															idx += 14;
															return X11_DARKSLATEGREY1;
														}
														case '2':
														{
															idx += 14;
															return X11_DARKSLATEGREY2;
														}
														case '3':
														{
															idx += 14;
															return X11_DARKSLATEGREY3;
														}
														case '4':
														{
															idx += 14;
															return X11_DARKSLATEGREY4;
														}
													}
													idx += 13;
													return X11_DARKSLATEGREY;
												}
											}
										}
									}
								}
							}
						}
						case 't':
						{
							if (str[5] && !strcmp(str[5], !"URQUOISE", true, 8))
							{
								idx += 13;
								return X11_DARKTURQUOISE;
							}
						}
						case 'v':
						{
							if (str[5] && !strcmp(str[5], !"IOLET", true, 5))
							{
								idx += 10;
								return X11_DARKVIOLET;
							}
						}
					}
				}
				case 'e':
				{
					if (!str[2] || strcmp(str[2], !"EP", true, 2))
					{
						return -1;
					}
					switch (str[4] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[4])
							{
								switch (str[5] | 0x20)
								{
									case 'p':
									{
										if (!str[6] || strcmp(str[6], !"INK", true, 3))
										{
											return -1;
										}
										switch (str[9] | 0x20)
										{
											case _X11_SPACE_SWITCH: // ' '
											{
												if (str[9])
												{
													switch (str[10] | 0x20)
													{
														case '1':
														{
															idx += 11;
															return X11_DEEP_PINK_1;
														}
														case '2':
														{
															idx += 11;
															return X11_DEEP_PINK_2;
														}
														case '3':
														{
															idx += 11;
															return X11_DEEP_PINK_3;
														}
														case '4':
														{
															idx += 11;
															return X11_DEEP_PINK_4;
														}
													}
												}
											}
											case '_' | 0x20:
											{
												switch (str[10] | 0x20)
												{
													case '1':
													{
														idx += 11;
														return X11_DEEP_PINK_1;
													}
													case '2':
													{
														idx += 11;
														return X11_DEEP_PINK_2;
													}
													case '3':
													{
														idx += 11;
														return X11_DEEP_PINK_3;
													}
													case '4':
													{
														idx += 11;
														return X11_DEEP_PINK_4;
													}
												}
											}
										}
										idx += 9;
										return X11_DEEP_PINK;
									}
									case 's':
									{
										//if (!str[6] || strcmp(str[6], !"KY_BLUE", true, 7))
										if (!str[6] || strcmp(str[6], !"KY", true, 2) || (!_X11_SPACE_CHECK(8) && str[8] != '_') || strcmp(str[9], !"BLUE", true, 4))
										{
											return -1;
										}
										switch (str[13] | 0x20)
										{
											case _X11_SPACE_SWITCH: // ' '
											{
												if (str[13])
												{
													switch (str[14] | 0x20)
													{
														case '1':
														{
															idx += 15;
															return X11_DEEP_SKY_BLUE_1;
														}
														case '2':
														{
															idx += 15;
															return X11_DEEP_SKY_BLUE_2;
														}
														case '3':
														{
															idx += 15;
															return X11_DEEP_SKY_BLUE_3;
														}
														case '4':
														{
															idx += 15;
															return X11_DEEP_SKY_BLUE_4;
														}
													}
												}
											}
											case '_' | 0x20:
											{
												switch (str[14] | 0x20)
												{
													case '1':
													{
														idx += 15;
														return X11_DEEP_SKY_BLUE_1;
													}
													case '2':
													{
														idx += 15;
														return X11_DEEP_SKY_BLUE_2;
													}
													case '3':
													{
														idx += 15;
														return X11_DEEP_SKY_BLUE_3;
													}
													case '4':
													{
														idx += 15;
														return X11_DEEP_SKY_BLUE_4;
													}
												}
											}
										}
										idx += 13;
										return X11_DEEP_SKY_BLUE;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[5] | 0x20)
							{
								case 'p':
								{
									if (!str[6] || strcmp(str[6], !"INK", true, 3))
									{
										return -1;
									}
									switch (str[9] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[9])
											{
												switch (str[10] | 0x20)
												{
													case '1':
													{
														idx += 11;
														return X11_DEEP_PINK_1;
													}
													case '2':
													{
														idx += 11;
														return X11_DEEP_PINK_2;
													}
													case '3':
													{
														idx += 11;
														return X11_DEEP_PINK_3;
													}
													case '4':
													{
														idx += 11;
														return X11_DEEP_PINK_4;
													}
												}
											}
										}
										case '_' | 0x20:
										{
											switch (str[10] | 0x20)
											{
												case '1':
												{
													idx += 11;
													return X11_DEEP_PINK_1;
												}
												case '2':
												{
													idx += 11;
													return X11_DEEP_PINK_2;
												}
												case '3':
												{
													idx += 11;
													return X11_DEEP_PINK_3;
												}
												case '4':
												{
													idx += 11;
													return X11_DEEP_PINK_4;
												}
											}
										}
									}
									idx += 9;
									return X11_DEEP_PINK;
								}
								case 's':
								{
									//if (!str[6] || strcmp(str[6], !"KY_BLUE", true, 7))
									if (!str[6] || strcmp(str[6], !"KY", true, 2) || (!_X11_SPACE_CHECK(8) && str[8] != '_') || strcmp(str[9], !"BLUE", true, 4))
									{
										return -1;
									}
									switch (str[13] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[13])
											{
												switch (str[14] | 0x20)
												{
													case '1':
													{
														idx += 15;
														return X11_DEEP_SKY_BLUE_1;
													}
													case '2':
													{
														idx += 15;
														return X11_DEEP_SKY_BLUE_2;
													}
													case '3':
													{
														idx += 15;
														return X11_DEEP_SKY_BLUE_3;
													}
													case '4':
													{
														idx += 15;
														return X11_DEEP_SKY_BLUE_4;
													}
												}
											}
										}
										case '_' | 0x20:
										{
											switch (str[14] | 0x20)
											{
												case '1':
												{
													idx += 15;
													return X11_DEEP_SKY_BLUE_1;
												}
												case '2':
												{
													idx += 15;
													return X11_DEEP_SKY_BLUE_2;
												}
												case '3':
												{
													idx += 15;
													return X11_DEEP_SKY_BLUE_3;
												}
												case '4':
												{
													idx += 15;
													return X11_DEEP_SKY_BLUE_4;
												}
											}
										}
									}
									idx += 13;
									return X11_DEEP_SKY_BLUE;
								}
							}
						}
						case 'p':
						{
							if (!str[5] || strcmp(str[5], !"INK", true, 3))
							{
								return -1;
							}
							switch (str[8] | 0x20)
							{
								case '1':
								{
									idx += 9;
									return X11_DEEPPINK1;
								}
								case '2':
								{
									idx += 9;
									return X11_DEEPPINK2;
								}
								case '3':
								{
									idx += 9;
									return X11_DEEPPINK3;
								}
								case '4':
								{
									idx += 9;
									return X11_DEEPPINK4;
								}
							}
							idx += 8;
							return X11_DEEPPINK;
						}
						case 's':
						{
							if (!str[5] || strcmp(str[5], !"KYBLUE", true, 6))
							{
								return -1;
							}
							switch (str[11] | 0x20)
							{
								case '1':
								{
									idx += 12;
									return X11_DEEPSKYBLUE1;
								}
								case '2':
								{
									idx += 12;
									return X11_DEEPSKYBLUE2;
								}
								case '3':
								{
									idx += 12;
									return X11_DEEPSKYBLUE3;
								}
								case '4':
								{
									idx += 12;
									return X11_DEEPSKYBLUE4;
								}
							}
							idx += 11;
							return X11_DEEPSKYBLUE;
						}
					}
				}
				case 'i':
				{
					if (str[2] | 0x20 != 'm')
					{
						return -1;
					}
					switch (str[3] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[3])
							{
								if (!str[4] || strcmp(str[4], !"GR", true, 2))
								{
									return -1;
								}
								switch (str[6] | 0x20)
								{
									case 'a':
									{
										if (str[7] | 0x20 == 'y')
										{
											idx += 8;
											return X11_DIM_GRAY;
										}
									}
									case 'e':
									{
										if (str[7] | 0x20 == 'y')
										{
											idx += 8;
											return X11_DIM_GREY;
										}
									}
								}
							}
						}
						case '_' | 0x20:
						{
							if (!str[4] || strcmp(str[4], !"GR", true, 2))
							{
								return -1;
							}
							switch (str[6] | 0x20)
							{
								case 'a':
								{
									if (str[7] | 0x20 == 'y')
									{
										idx += 8;
										return X11_DIM_GRAY;
									}
								}
								case 'e':
								{
									if (str[7] | 0x20 == 'y')
									{
										idx += 8;
										return X11_DIM_GREY;
									}
								}
							}
						}
						case 'g':
						{
							if (str[4] | 0x20 != 'r')
							{
								return -1;
							}
							switch (str[5] | 0x20)
							{
								case 'a':
								{
									if (str[6] | 0x20 == 'y')
									{
										idx += 7;
										return X11_DIMGRAY;
									}
								}
								case 'e':
								{
									if (str[6] | 0x20 == 'y')
									{
										idx += 7;
										return X11_DIMGREY;
									}
								}
							}
						}
					}
				}
				case 'o':
				{
					if (!str[2] || strcmp(str[2], !"DGER", true, 4))
					{
						return -1;
					}
					switch (str[6] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[6])
							{
								if (!str[7] || strcmp(str[7], !"BLUE", true, 4))
								{
									return -1;
								}
								switch (str[11] | 0x20)
								{
									case _X11_SPACE_SWITCH: // ' '
									{
										if (str[11])
										{
											switch (str[12] | 0x20)
											{
												case '1':
												{
													idx += 13;
													return X11_DODGER_BLUE_1;
												}
												case '2':
												{
													idx += 13;
													return X11_DODGER_BLUE_2;
												}
												case '3':
												{
													idx += 13;
													return X11_DODGER_BLUE_3;
												}
												case '4':
												{
													idx += 13;
													return X11_DODGER_BLUE_4;
												}
											}
										}
									}
									case '_' | 0x20:
									{
										switch (str[12] | 0x20)
										{
											case '1':
											{
												idx += 13;
												return X11_DODGER_BLUE_1;
											}
											case '2':
											{
												idx += 13;
												return X11_DODGER_BLUE_2;
											}
											case '3':
											{
												idx += 13;
												return X11_DODGER_BLUE_3;
											}
											case '4':
											{
												idx += 13;
												return X11_DODGER_BLUE_4;
											}
										}
									}
								}
								idx += 11;
								return X11_DODGER_BLUE;
							}
						}
						case '_' | 0x20:
						{
							if (!str[7] || strcmp(str[7], !"BLUE", true, 4))
							{
								return -1;
							}
							switch (str[11] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[11])
									{
										switch (str[12] | 0x20)
										{
											case '1':
											{
												idx += 13;
												return X11_DODGER_BLUE_1;
											}
											case '2':
											{
												idx += 13;
												return X11_DODGER_BLUE_2;
											}
											case '3':
											{
												idx += 13;
												return X11_DODGER_BLUE_3;
											}
											case '4':
											{
												idx += 13;
												return X11_DODGER_BLUE_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[12] | 0x20)
									{
										case '1':
										{
											idx += 13;
											return X11_DODGER_BLUE_1;
										}
										case '2':
										{
											idx += 13;
											return X11_DODGER_BLUE_2;
										}
										case '3':
										{
											idx += 13;
											return X11_DODGER_BLUE_3;
										}
										case '4':
										{
											idx += 13;
											return X11_DODGER_BLUE_4;
										}
									}
								}
							}
							idx += 11;
							return X11_DODGER_BLUE;
						}
						case 'b':
						{
							if (!str[7] || strcmp(str[7], !"LUE", true, 3))
							{
								return -1;
							}
							switch (str[10] | 0x20)
							{
								case '1':
								{
									idx += 11;
									return X11_DODGERBLUE1;
								}
								case '2':
								{
									idx += 11;
									return X11_DODGERBLUE2;
								}
								case '3':
								{
									idx += 11;
									return X11_DODGERBLUE3;
								}
								case '4':
								{
									idx += 11;
									return X11_DODGERBLUE4;
								}
							}
							idx += 10;
							return X11_DODGERBLUE;
						}
					}
				}
			}
		}
		case 'f':
		{
			switch (str[1] | 0x20)
			{
				case 'i':
				{
					if (!str[2] || strcmp(str[2], !"REBRICK", true, 7))
					{
						return -1;
					}
					switch (str[9] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[9])
							{
								switch (str[10] | 0x20)
								{
									case '1':
									{
										idx += 11;
										return X11_FIREBRICK_1;
									}
									case '2':
									{
										idx += 11;
										return X11_FIREBRICK_2;
									}
									case '3':
									{
										idx += 11;
										return X11_FIREBRICK_3;
									}
									case '4':
									{
										idx += 11;
										return X11_FIREBRICK_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[10] | 0x20)
							{
								case '1':
								{
									idx += 11;
									return X11_FIREBRICK_1;
								}
								case '2':
								{
									idx += 11;
									return X11_FIREBRICK_2;
								}
								case '3':
								{
									idx += 11;
									return X11_FIREBRICK_3;
								}
								case '4':
								{
									idx += 11;
									return X11_FIREBRICK_4;
								}
							}
						}
						case '1':
						{
							idx += 10;
							return X11_FIREBRICK1;
						}
						case '2':
						{
							idx += 10;
							return X11_FIREBRICK2;
						}
						case '3':
						{
							idx += 10;
							return X11_FIREBRICK3;
						}
						case '4':
						{
							idx += 10;
							return X11_FIREBRICK4;
						}
					}
					idx += 9;
					return X11_FIREBRICK;
				}
				case 'l':
				{
					if (!str[2] || strcmp(str[2], !"ORAL", true, 4))
					{
						return -1;
					}
					switch (str[6] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[6])
							{
								if (str[7] && !strcmp(str[7], !"WHITE", true, 5))
								{
									idx += 12;
									return X11_FLORAL_WHITE;
								}
							}
						}
						case '_' | 0x20:
						{
							if (str[7] && !strcmp(str[7], !"WHITE", true, 5))
							{
								idx += 12;
								return X11_FLORAL_WHITE;
							}
						}
						case 'w':
						{
							if (str[7] && !strcmp(str[7], !"HITE", true, 4))
							{
								idx += 11;
								return X11_FLORALWHITE;
							}
						}
					}
				}
				case 'o':
				{
					if (!str[2] || strcmp(str[2], !"REST", true, 4))
					{
						return -1;
					}
					switch (str[6] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[6])
							{
								if (str[7] && !strcmp(str[7], !"GREEN", true, 5))
								{
									idx += 12;
									return X11_FOREST_GREEN;
								}
							}
						}
						case '_' | 0x20:
						{
							if (str[7] && !strcmp(str[7], !"GREEN", true, 5))
							{
								idx += 12;
								return X11_FOREST_GREEN;
							}
						}
						case 'g':
						{
							if (str[7] && !strcmp(str[7], !"REEN", true, 4))
							{
								idx += 11;
								return X11_FORESTGREEN;
							}
						}
					}
				}
			}
		}
		case 'g':
		{
			switch (str[1] | 0x20)
			{
				case 'a':
				{
					if (str[2] && !strcmp(str[2], !"INSBORO", true, 7))
					{
						idx += 9;
						return X11_GAINSBORO;
					}
				}
				case 'h':
				{
					if (!str[2] || strcmp(str[2], !"OST", true, 3))
					{
						return -1;
					}
					switch (str[5] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[5])
							{
								if (str[6] && !strcmp(str[6], !"WHITE", true, 5))
								{
									idx += 11;
									return X11_GHOST_WHITE;
								}
							}
						}
						case '_' | 0x20:
						{
							if (str[6] && !strcmp(str[6], !"WHITE", true, 5))
							{
								idx += 11;
								return X11_GHOST_WHITE;
							}
						}
						case 'w':
						{
							if (str[6] && !strcmp(str[6], !"HITE", true, 4))
							{
								idx += 10;
								return X11_GHOSTWHITE;
							}
						}
					}
				}
				case 'o':
				{
					if (!str[2] || strcmp(str[2], !"LD", true, 2))
					{
						return -1;
					}
					switch (str[4] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[4])
							{
								switch (str[5] | 0x20)
								{
									case '1':
									{
										idx += 6;
										return X11_GOLD_1;
									}
									case '2':
									{
										idx += 6;
										return X11_GOLD_2;
									}
									case '3':
									{
										idx += 6;
										return X11_GOLD_3;
									}
									case '4':
									{
										idx += 6;
										return X11_GOLD_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[5] | 0x20)
							{
								case '1':
								{
									idx += 6;
									return X11_GOLD_1;
								}
								case '2':
								{
									idx += 6;
									return X11_GOLD_2;
								}
								case '3':
								{
									idx += 6;
									return X11_GOLD_3;
								}
								case '4':
								{
									idx += 6;
									return X11_GOLD_4;
								}
							}
						}
						case '1':
						{
							idx += 5;
							return X11_GOLD1;
						}
						case '2':
						{
							idx += 5;
							return X11_GOLD2;
						}
						case '3':
						{
							idx += 5;
							return X11_GOLD3;
						}
						case '4':
						{
							idx += 5;
							return X11_GOLD4;
						}
						case 'e':
						{
							if (!str[5] || strcmp(str[5], !"NROD", true, 4))
							{
								return -1;
							}
							switch (str[9] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[9])
									{
										switch (str[10] | 0x20)
										{
											case '1':
											{
												idx += 11;
												return X11_GOLDENROD_1;
											}
											case '2':
											{
												idx += 11;
												return X11_GOLDENROD_2;
											}
											case '3':
											{
												idx += 11;
												return X11_GOLDENROD_3;
											}
											case '4':
											{
												idx += 11;
												return X11_GOLDENROD_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[10] | 0x20)
									{
										case '1':
										{
											idx += 11;
											return X11_GOLDENROD_1;
										}
										case '2':
										{
											idx += 11;
											return X11_GOLDENROD_2;
										}
										case '3':
										{
											idx += 11;
											return X11_GOLDENROD_3;
										}
										case '4':
										{
											idx += 11;
											return X11_GOLDENROD_4;
										}
									}
								}
								case '1':
								{
									idx += 10;
									return X11_GOLDENROD1;
								}
								case '2':
								{
									idx += 10;
									return X11_GOLDENROD2;
								}
								case '3':
								{
									idx += 10;
									return X11_GOLDENROD3;
								}
								case '4':
								{
									idx += 10;
									return X11_GOLDENROD4;
								}
							}
							idx += 9;
							return X11_GOLDENROD;
						}
					}
					idx += 4;
					return X11_GOLD;
				}
				case 'r':
				{
					switch (str[2] | 0x20)
					{
						case 'a':
						{
							if (str[3] | 0x20 != 'y')
							{
								return -1;
							}
							switch (str[4] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[4])
									{
										switch (str[5] | 0x20)
										{
											case '0':
											{
												idx += 6;
												return X11_GRAY_0;
											}
											case '1':
											{
												switch (str[6] | 0x20)
												{
													case '0':
													{
														switch (str[7] | 0x20)
														{
															case '0':
															{
																idx += 8;
																return X11_GRAY_100;
															}
														}
														idx += 7;
														return X11_GRAY_10;
													}
													case '1':
													{
														idx += 7;
														return X11_GRAY_11;
													}
													case '2':
													{
														idx += 7;
														return X11_GRAY_12;
													}
													case '3':
													{
														idx += 7;
														return X11_GRAY_13;
													}
													case '4':
													{
														idx += 7;
														return X11_GRAY_14;
													}
													case '5':
													{
														idx += 7;
														return X11_GRAY_15;
													}
													case '6':
													{
														idx += 7;
														return X11_GRAY_16;
													}
													case '7':
													{
														idx += 7;
														return X11_GRAY_17;
													}
													case '8':
													{
														idx += 7;
														return X11_GRAY_18;
													}
													case '9':
													{
														idx += 7;
														return X11_GRAY_19;
													}
												}
												idx += 6;
												return X11_GRAY_1;
											}
											case '2':
											{
												switch (str[6] | 0x20)
												{
													case '0':
													{
														idx += 7;
														return X11_GRAY_20;
													}
													case '1':
													{
														idx += 7;
														return X11_GRAY_21;
													}
													case '2':
													{
														idx += 7;
														return X11_GRAY_22;
													}
													case '3':
													{
														idx += 7;
														return X11_GRAY_23;
													}
													case '4':
													{
														idx += 7;
														return X11_GRAY_24;
													}
													case '5':
													{
														idx += 7;
														return X11_GRAY_25;
													}
													case '6':
													{
														idx += 7;
														return X11_GRAY_26;
													}
													case '7':
													{
														idx += 7;
														return X11_GRAY_27;
													}
													case '8':
													{
														idx += 7;
														return X11_GRAY_28;
													}
													case '9':
													{
														idx += 7;
														return X11_GRAY_29;
													}
												}
												idx += 6;
												return X11_GRAY_2;
											}
											case '3':
											{
												switch (str[6] | 0x20)
												{
													case '0':
													{
														idx += 7;
														return X11_GRAY_30;
													}
													case '1':
													{
														idx += 7;
														return X11_GRAY_31;
													}
													case '2':
													{
														idx += 7;
														return X11_GRAY_32;
													}
													case '3':
													{
														idx += 7;
														return X11_GRAY_33;
													}
													case '4':
													{
														idx += 7;
														return X11_GRAY_34;
													}
													case '5':
													{
														idx += 7;
														return X11_GRAY_35;
													}
													case '6':
													{
														idx += 7;
														return X11_GRAY_36;
													}
													case '7':
													{
														idx += 7;
														return X11_GRAY_37;
													}
													case '8':
													{
														idx += 7;
														return X11_GRAY_38;
													}
													case '9':
													{
														idx += 7;
														return X11_GRAY_39;
													}
												}
												idx += 6;
												return X11_GRAY_3;
											}
											case '4':
											{
												switch (str[6] | 0x20)
												{
													case '0':
													{
														idx += 7;
														return X11_GRAY_40;
													}
													case '1':
													{
														idx += 7;
														return X11_GRAY_41;
													}
													case '2':
													{
														idx += 7;
														return X11_GRAY_42;
													}
													case '3':
													{
														idx += 7;
														return X11_GRAY_43;
													}
													case '4':
													{
														idx += 7;
														return X11_GRAY_44;
													}
													case '5':
													{
														idx += 7;
														return X11_GRAY_45;
													}
													case '6':
													{
														idx += 7;
														return X11_GRAY_46;
													}
													case '7':
													{
														idx += 7;
														return X11_GRAY_47;
													}
													case '8':
													{
														idx += 7;
														return X11_GRAY_48;
													}
													case '9':
													{
														idx += 7;
														return X11_GRAY_49;
													}
												}
												idx += 6;
												return X11_GRAY_4;
											}
											case '5':
											{
												switch (str[6] | 0x20)
												{
													case '0':
													{
														idx += 7;
														return X11_GRAY_50;
													}
													case '1':
													{
														idx += 7;
														return X11_GRAY_51;
													}
													case '2':
													{
														idx += 7;
														return X11_GRAY_52;
													}
													case '3':
													{
														idx += 7;
														return X11_GRAY_53;
													}
													case '4':
													{
														idx += 7;
														return X11_GRAY_54;
													}
													case '5':
													{
														idx += 7;
														return X11_GRAY_55;
													}
													case '6':
													{
														idx += 7;
														return X11_GRAY_56;
													}
													case '7':
													{
														idx += 7;
														return X11_GRAY_57;
													}
													case '8':
													{
														idx += 7;
														return X11_GRAY_58;
													}
													case '9':
													{
														idx += 7;
														return X11_GRAY_59;
													}
												}
												idx += 6;
												return X11_GRAY_5;
											}
											case '6':
											{
												switch (str[6] | 0x20)
												{
													case '0':
													{
														idx += 7;
														return X11_GRAY_60;
													}
													case '1':
													{
														idx += 7;
														return X11_GRAY_61;
													}
													case '2':
													{
														idx += 7;
														return X11_GRAY_62;
													}
													case '3':
													{
														idx += 7;
														return X11_GRAY_63;
													}
													case '4':
													{
														idx += 7;
														return X11_GRAY_64;
													}
													case '5':
													{
														idx += 7;
														return X11_GRAY_65;
													}
													case '6':
													{
														idx += 7;
														return X11_GRAY_66;
													}
													case '7':
													{
														idx += 7;
														return X11_GRAY_67;
													}
													case '8':
													{
														idx += 7;
														return X11_GRAY_68;
													}
													case '9':
													{
														idx += 7;
														return X11_GRAY_69;
													}
												}
												idx += 6;
												return X11_GRAY_6;
											}
											case '7':
											{
												switch (str[6] | 0x20)
												{
													case '0':
													{
														idx += 7;
														return X11_GRAY_70;
													}
													case '1':
													{
														idx += 7;
														return X11_GRAY_71;
													}
													case '2':
													{
														idx += 7;
														return X11_GRAY_72;
													}
													case '3':
													{
														idx += 7;
														return X11_GRAY_73;
													}
													case '4':
													{
														idx += 7;
														return X11_GRAY_74;
													}
													case '5':
													{
														idx += 7;
														return X11_GRAY_75;
													}
													case '6':
													{
														idx += 7;
														return X11_GRAY_76;
													}
													case '7':
													{
														idx += 7;
														return X11_GRAY_77;
													}
													case '8':
													{
														idx += 7;
														return X11_GRAY_78;
													}
													case '9':
													{
														idx += 7;
														return X11_GRAY_79;
													}
												}
												idx += 6;
												return X11_GRAY_7;
											}
											case '8':
											{
												switch (str[6] | 0x20)
												{
													case '0':
													{
														idx += 7;
														return X11_GRAY_80;
													}
													case '1':
													{
														idx += 7;
														return X11_GRAY_81;
													}
													case '2':
													{
														idx += 7;
														return X11_GRAY_82;
													}
													case '3':
													{
														idx += 7;
														return X11_GRAY_83;
													}
													case '4':
													{
														idx += 7;
														return X11_GRAY_84;
													}
													case '5':
													{
														idx += 7;
														return X11_GRAY_85;
													}
													case '6':
													{
														idx += 7;
														return X11_GRAY_86;
													}
													case '7':
													{
														idx += 7;
														return X11_GRAY_87;
													}
													case '8':
													{
														idx += 7;
														return X11_GRAY_88;
													}
													case '9':
													{
														idx += 7;
														return X11_GRAY_89;
													}
												}
												idx += 6;
												return X11_GRAY_8;
											}
											case '9':
											{
												switch (str[6] | 0x20)
												{
													case '0':
													{
														idx += 7;
														return X11_GRAY_90;
													}
													case '1':
													{
														idx += 7;
														return X11_GRAY_91;
													}
													case '2':
													{
														idx += 7;
														return X11_GRAY_92;
													}
													case '3':
													{
														idx += 7;
														return X11_GRAY_93;
													}
													case '4':
													{
														idx += 7;
														return X11_GRAY_94;
													}
													case '5':
													{
														idx += 7;
														return X11_GRAY_95;
													}
													case '6':
													{
														idx += 7;
														return X11_GRAY_96;
													}
													case '7':
													{
														idx += 7;
														return X11_GRAY_97;
													}
													case '8':
													{
														idx += 7;
														return X11_GRAY_98;
													}
													case '9':
													{
														idx += 7;
														return X11_GRAY_99;
													}
												}
												idx += 6;
												return X11_GRAY_9;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[5] | 0x20)
									{
										case '0':
										{
											idx += 6;
											return X11_GRAY_0;
										}
										case '1':
										{
											switch (str[6] | 0x20)
											{
												case '0':
												{
													switch (str[7] | 0x20)
													{
														case '0':
														{
															idx += 8;
															return X11_GRAY_100;
														}
													}
													idx += 7;
													return X11_GRAY_10;
												}
												case '1':
												{
													idx += 7;
													return X11_GRAY_11;
												}
												case '2':
												{
													idx += 7;
													return X11_GRAY_12;
												}
												case '3':
												{
													idx += 7;
													return X11_GRAY_13;
												}
												case '4':
												{
													idx += 7;
													return X11_GRAY_14;
												}
												case '5':
												{
													idx += 7;
													return X11_GRAY_15;
												}
												case '6':
												{
													idx += 7;
													return X11_GRAY_16;
												}
												case '7':
												{
													idx += 7;
													return X11_GRAY_17;
												}
												case '8':
												{
													idx += 7;
													return X11_GRAY_18;
												}
												case '9':
												{
													idx += 7;
													return X11_GRAY_19;
												}
											}
											idx += 6;
											return X11_GRAY_1;
										}
										case '2':
										{
											switch (str[6] | 0x20)
											{
												case '0':
												{
													idx += 7;
													return X11_GRAY_20;
												}
												case '1':
												{
													idx += 7;
													return X11_GRAY_21;
												}
												case '2':
												{
													idx += 7;
													return X11_GRAY_22;
												}
												case '3':
												{
													idx += 7;
													return X11_GRAY_23;
												}
												case '4':
												{
													idx += 7;
													return X11_GRAY_24;
												}
												case '5':
												{
													idx += 7;
													return X11_GRAY_25;
												}
												case '6':
												{
													idx += 7;
													return X11_GRAY_26;
												}
												case '7':
												{
													idx += 7;
													return X11_GRAY_27;
												}
												case '8':
												{
													idx += 7;
													return X11_GRAY_28;
												}
												case '9':
												{
													idx += 7;
													return X11_GRAY_29;
												}
											}
											idx += 6;
											return X11_GRAY_2;
										}
										case '3':
										{
											switch (str[6] | 0x20)
											{
												case '0':
												{
													idx += 7;
													return X11_GRAY_30;
												}
												case '1':
												{
													idx += 7;
													return X11_GRAY_31;
												}
												case '2':
												{
													idx += 7;
													return X11_GRAY_32;
												}
												case '3':
												{
													idx += 7;
													return X11_GRAY_33;
												}
												case '4':
												{
													idx += 7;
													return X11_GRAY_34;
												}
												case '5':
												{
													idx += 7;
													return X11_GRAY_35;
												}
												case '6':
												{
													idx += 7;
													return X11_GRAY_36;
												}
												case '7':
												{
													idx += 7;
													return X11_GRAY_37;
												}
												case '8':
												{
													idx += 7;
													return X11_GRAY_38;
												}
												case '9':
												{
													idx += 7;
													return X11_GRAY_39;
												}
											}
											idx += 6;
											return X11_GRAY_3;
										}
										case '4':
										{
											switch (str[6] | 0x20)
											{
												case '0':
												{
													idx += 7;
													return X11_GRAY_40;
												}
												case '1':
												{
													idx += 7;
													return X11_GRAY_41;
												}
												case '2':
												{
													idx += 7;
													return X11_GRAY_42;
												}
												case '3':
												{
													idx += 7;
													return X11_GRAY_43;
												}
												case '4':
												{
													idx += 7;
													return X11_GRAY_44;
												}
												case '5':
												{
													idx += 7;
													return X11_GRAY_45;
												}
												case '6':
												{
													idx += 7;
													return X11_GRAY_46;
												}
												case '7':
												{
													idx += 7;
													return X11_GRAY_47;
												}
												case '8':
												{
													idx += 7;
													return X11_GRAY_48;
												}
												case '9':
												{
													idx += 7;
													return X11_GRAY_49;
												}
											}
											idx += 6;
											return X11_GRAY_4;
										}
										case '5':
										{
											switch (str[6] | 0x20)
											{
												case '0':
												{
													idx += 7;
													return X11_GRAY_50;
												}
												case '1':
												{
													idx += 7;
													return X11_GRAY_51;
												}
												case '2':
												{
													idx += 7;
													return X11_GRAY_52;
												}
												case '3':
												{
													idx += 7;
													return X11_GRAY_53;
												}
												case '4':
												{
													idx += 7;
													return X11_GRAY_54;
												}
												case '5':
												{
													idx += 7;
													return X11_GRAY_55;
												}
												case '6':
												{
													idx += 7;
													return X11_GRAY_56;
												}
												case '7':
												{
													idx += 7;
													return X11_GRAY_57;
												}
												case '8':
												{
													idx += 7;
													return X11_GRAY_58;
												}
												case '9':
												{
													idx += 7;
													return X11_GRAY_59;
												}
											}
											idx += 6;
											return X11_GRAY_5;
										}
										case '6':
										{
											switch (str[6] | 0x20)
											{
												case '0':
												{
													idx += 7;
													return X11_GRAY_60;
												}
												case '1':
												{
													idx += 7;
													return X11_GRAY_61;
												}
												case '2':
												{
													idx += 7;
													return X11_GRAY_62;
												}
												case '3':
												{
													idx += 7;
													return X11_GRAY_63;
												}
												case '4':
												{
													idx += 7;
													return X11_GRAY_64;
												}
												case '5':
												{
													idx += 7;
													return X11_GRAY_65;
												}
												case '6':
												{
													idx += 7;
													return X11_GRAY_66;
												}
												case '7':
												{
													idx += 7;
													return X11_GRAY_67;
												}
												case '8':
												{
													idx += 7;
													return X11_GRAY_68;
												}
												case '9':
												{
													idx += 7;
													return X11_GRAY_69;
												}
											}
											idx += 6;
											return X11_GRAY_6;
										}
										case '7':
										{
											switch (str[6] | 0x20)
											{
												case '0':
												{
													idx += 7;
													return X11_GRAY_70;
												}
												case '1':
												{
													idx += 7;
													return X11_GRAY_71;
												}
												case '2':
												{
													idx += 7;
													return X11_GRAY_72;
												}
												case '3':
												{
													idx += 7;
													return X11_GRAY_73;
												}
												case '4':
												{
													idx += 7;
													return X11_GRAY_74;
												}
												case '5':
												{
													idx += 7;
													return X11_GRAY_75;
												}
												case '6':
												{
													idx += 7;
													return X11_GRAY_76;
												}
												case '7':
												{
													idx += 7;
													return X11_GRAY_77;
												}
												case '8':
												{
													idx += 7;
													return X11_GRAY_78;
												}
												case '9':
												{
													idx += 7;
													return X11_GRAY_79;
												}
											}
											idx += 6;
											return X11_GRAY_7;
										}
										case '8':
										{
											switch (str[6] | 0x20)
											{
												case '0':
												{
													idx += 7;
													return X11_GRAY_80;
												}
												case '1':
												{
													idx += 7;
													return X11_GRAY_81;
												}
												case '2':
												{
													idx += 7;
													return X11_GRAY_82;
												}
												case '3':
												{
													idx += 7;
													return X11_GRAY_83;
												}
												case '4':
												{
													idx += 7;
													return X11_GRAY_84;
												}
												case '5':
												{
													idx += 7;
													return X11_GRAY_85;
												}
												case '6':
												{
													idx += 7;
													return X11_GRAY_86;
												}
												case '7':
												{
													idx += 7;
													return X11_GRAY_87;
												}
												case '8':
												{
													idx += 7;
													return X11_GRAY_88;
												}
												case '9':
												{
													idx += 7;
													return X11_GRAY_89;
												}
											}
											idx += 6;
											return X11_GRAY_8;
										}
										case '9':
										{
											switch (str[6] | 0x20)
											{
												case '0':
												{
													idx += 7;
													return X11_GRAY_90;
												}
												case '1':
												{
													idx += 7;
													return X11_GRAY_91;
												}
												case '2':
												{
													idx += 7;
													return X11_GRAY_92;
												}
												case '3':
												{
													idx += 7;
													return X11_GRAY_93;
												}
												case '4':
												{
													idx += 7;
													return X11_GRAY_94;
												}
												case '5':
												{
													idx += 7;
													return X11_GRAY_95;
												}
												case '6':
												{
													idx += 7;
													return X11_GRAY_96;
												}
												case '7':
												{
													idx += 7;
													return X11_GRAY_97;
												}
												case '8':
												{
													idx += 7;
													return X11_GRAY_98;
												}
												case '9':
												{
													idx += 7;
													return X11_GRAY_99;
												}
											}
											idx += 6;
											return X11_GRAY_9;
										}
									}
								}
								case '0':
								{
									idx += 5;
									return X11_GRAY0;
								}
								case '1':
								{
									switch (str[5] | 0x20)
									{
										case '0':
										{
											switch (str[6] | 0x20)
											{
												case '0':
												{
													idx += 7;
													return X11_GRAY100;
												}
											}
											idx += 6;
											return X11_GRAY10;
										}
										case '1':
										{
											idx += 6;
											return X11_GRAY11;
										}
										case '2':
										{
											idx += 6;
											return X11_GRAY12;
										}
										case '3':
										{
											idx += 6;
											return X11_GRAY13;
										}
										case '4':
										{
											idx += 6;
											return X11_GRAY14;
										}
										case '5':
										{
											idx += 6;
											return X11_GRAY15;
										}
										case '6':
										{
											idx += 6;
											return X11_GRAY16;
										}
										case '7':
										{
											idx += 6;
											return X11_GRAY17;
										}
										case '8':
										{
											idx += 6;
											return X11_GRAY18;
										}
										case '9':
										{
											idx += 6;
											return X11_GRAY19;
										}
									}
									idx += 5;
									return X11_GRAY1;
								}
								case '2':
								{
									switch (str[5] | 0x20)
									{
										case '0':
										{
											idx += 6;
											return X11_GRAY20;
										}
										case '1':
										{
											idx += 6;
											return X11_GRAY21;
										}
										case '2':
										{
											idx += 6;
											return X11_GRAY22;
										}
										case '3':
										{
											idx += 6;
											return X11_GRAY23;
										}
										case '4':
										{
											idx += 6;
											return X11_GRAY24;
										}
										case '5':
										{
											idx += 6;
											return X11_GRAY25;
										}
										case '6':
										{
											idx += 6;
											return X11_GRAY26;
										}
										case '7':
										{
											idx += 6;
											return X11_GRAY27;
										}
										case '8':
										{
											idx += 6;
											return X11_GRAY28;
										}
										case '9':
										{
											idx += 6;
											return X11_GRAY29;
										}
									}
									idx += 5;
									return X11_GRAY2;
								}
								case '3':
								{
									switch (str[5] | 0x20)
									{
										case '0':
										{
											idx += 6;
											return X11_GRAY30;
										}
										case '1':
										{
											idx += 6;
											return X11_GRAY31;
										}
										case '2':
										{
											idx += 6;
											return X11_GRAY32;
										}
										case '3':
										{
											idx += 6;
											return X11_GRAY33;
										}
										case '4':
										{
											idx += 6;
											return X11_GRAY34;
										}
										case '5':
										{
											idx += 6;
											return X11_GRAY35;
										}
										case '6':
										{
											idx += 6;
											return X11_GRAY36;
										}
										case '7':
										{
											idx += 6;
											return X11_GRAY37;
										}
										case '8':
										{
											idx += 6;
											return X11_GRAY38;
										}
										case '9':
										{
											idx += 6;
											return X11_GRAY39;
										}
									}
									idx += 5;
									return X11_GRAY3;
								}
								case '4':
								{
									switch (str[5] | 0x20)
									{
										case '0':
										{
											idx += 6;
											return X11_GRAY40;
										}
										case '1':
										{
											idx += 6;
											return X11_GRAY41;
										}
										case '2':
										{
											idx += 6;
											return X11_GRAY42;
										}
										case '3':
										{
											idx += 6;
											return X11_GRAY43;
										}
										case '4':
										{
											idx += 6;
											return X11_GRAY44;
										}
										case '5':
										{
											idx += 6;
											return X11_GRAY45;
										}
										case '6':
										{
											idx += 6;
											return X11_GRAY46;
										}
										case '7':
										{
											idx += 6;
											return X11_GRAY47;
										}
										case '8':
										{
											idx += 6;
											return X11_GRAY48;
										}
										case '9':
										{
											idx += 6;
											return X11_GRAY49;
										}
									}
									idx += 5;
									return X11_GRAY4;
								}
								case '5':
								{
									switch (str[5] | 0x20)
									{
										case '0':
										{
											idx += 6;
											return X11_GRAY50;
										}
										case '1':
										{
											idx += 6;
											return X11_GRAY51;
										}
										case '2':
										{
											idx += 6;
											return X11_GRAY52;
										}
										case '3':
										{
											idx += 6;
											return X11_GRAY53;
										}
										case '4':
										{
											idx += 6;
											return X11_GRAY54;
										}
										case '5':
										{
											idx += 6;
											return X11_GRAY55;
										}
										case '6':
										{
											idx += 6;
											return X11_GRAY56;
										}
										case '7':
										{
											idx += 6;
											return X11_GRAY57;
										}
										case '8':
										{
											idx += 6;
											return X11_GRAY58;
										}
										case '9':
										{
											idx += 6;
											return X11_GRAY59;
										}
									}
									idx += 5;
									return X11_GRAY5;
								}
								case '6':
								{
									switch (str[5] | 0x20)
									{
										case '0':
										{
											idx += 6;
											return X11_GRAY60;
										}
										case '1':
										{
											idx += 6;
											return X11_GRAY61;
										}
										case '2':
										{
											idx += 6;
											return X11_GRAY62;
										}
										case '3':
										{
											idx += 6;
											return X11_GRAY63;
										}
										case '4':
										{
											idx += 6;
											return X11_GRAY64;
										}
										case '5':
										{
											idx += 6;
											return X11_GRAY65;
										}
										case '6':
										{
											idx += 6;
											return X11_GRAY66;
										}
										case '7':
										{
											idx += 6;
											return X11_GRAY67;
										}
										case '8':
										{
											idx += 6;
											return X11_GRAY68;
										}
										case '9':
										{
											idx += 6;
											return X11_GRAY69;
										}
									}
									idx += 5;
									return X11_GRAY6;
								}
								case '7':
								{
									switch (str[5] | 0x20)
									{
										case '0':
										{
											idx += 6;
											return X11_GRAY70;
										}
										case '1':
										{
											idx += 6;
											return X11_GRAY71;
										}
										case '2':
										{
											idx += 6;
											return X11_GRAY72;
										}
										case '3':
										{
											idx += 6;
											return X11_GRAY73;
										}
										case '4':
										{
											idx += 6;
											return X11_GRAY74;
										}
										case '5':
										{
											idx += 6;
											return X11_GRAY75;
										}
										case '6':
										{
											idx += 6;
											return X11_GRAY76;
										}
										case '7':
										{
											idx += 6;
											return X11_GRAY77;
										}
										case '8':
										{
											idx += 6;
											return X11_GRAY78;
										}
										case '9':
										{
											idx += 6;
											return X11_GRAY79;
										}
									}
									idx += 5;
									return X11_GRAY7;
								}
								case '8':
								{
									switch (str[5] | 0x20)
									{
										case '0':
										{
											idx += 6;
											return X11_GRAY80;
										}
										case '1':
										{
											idx += 6;
											return X11_GRAY81;
										}
										case '2':
										{
											idx += 6;
											return X11_GRAY82;
										}
										case '3':
										{
											idx += 6;
											return X11_GRAY83;
										}
										case '4':
										{
											idx += 6;
											return X11_GRAY84;
										}
										case '5':
										{
											idx += 6;
											return X11_GRAY85;
										}
										case '6':
										{
											idx += 6;
											return X11_GRAY86;
										}
										case '7':
										{
											idx += 6;
											return X11_GRAY87;
										}
										case '8':
										{
											idx += 6;
											return X11_GRAY88;
										}
										case '9':
										{
											idx += 6;
											return X11_GRAY89;
										}
									}
									idx += 5;
									return X11_GRAY8;
								}
								case '9':
								{
									switch (str[5] | 0x20)
									{
										case '0':
										{
											idx += 6;
											return X11_GRAY90;
										}
										case '1':
										{
											idx += 6;
											return X11_GRAY91;
										}
										case '2':
										{
											idx += 6;
											return X11_GRAY92;
										}
										case '3':
										{
											idx += 6;
											return X11_GRAY93;
										}
										case '4':
										{
											idx += 6;
											return X11_GRAY94;
										}
										case '5':
										{
											idx += 6;
											return X11_GRAY95;
										}
										case '6':
										{
											idx += 6;
											return X11_GRAY96;
										}
										case '7':
										{
											idx += 6;
											return X11_GRAY97;
										}
										case '8':
										{
											idx += 6;
											return X11_GRAY98;
										}
										case '9':
										{
											idx += 6;
											return X11_GRAY99;
										}
									}
									idx += 5;
									return X11_GRAY9;
								}
							}
							idx += 4;
							return X11_GRAY;
						}
						case 'e':
						{
							switch (str[3] | 0x20)
							{
								case 'e':
								{
									if (str[4] | 0x20 != 'n')
									{
										return -1;
									}
									switch (str[5] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[5])
											{
												switch (str[6] | 0x20)
												{
													case '1':
													{
														idx += 7;
														return X11_GREEN_1;
													}
													case '2':
													{
														idx += 7;
														return X11_GREEN_2;
													}
													case '3':
													{
														idx += 7;
														return X11_GREEN_3;
													}
													case '4':
													{
														idx += 7;
														return X11_GREEN_4;
													}
													case 'y':
													{
														if (str[7] && !strcmp(str[7], !"ELLOW", true, 5))
														{
															idx += 12;
															return X11_GREEN_YELLOW;
														}
													}
												}
											}
										}
										case '_' | 0x20:
										{
											switch (str[6] | 0x20)
											{
												case '1':
												{
													idx += 7;
													return X11_GREEN_1;
												}
												case '2':
												{
													idx += 7;
													return X11_GREEN_2;
												}
												case '3':
												{
													idx += 7;
													return X11_GREEN_3;
												}
												case '4':
												{
													idx += 7;
													return X11_GREEN_4;
												}
												case 'y':
												{
													if (str[7] && !strcmp(str[7], !"ELLOW", true, 5))
													{
														idx += 12;
														return X11_GREEN_YELLOW;
													}
												}
											}
										}
										case '1':
										{
											idx += 6;
											return X11_GREEN1;
										}
										case '2':
										{
											idx += 6;
											return X11_GREEN2;
										}
										case '3':
										{
											idx += 6;
											return X11_GREEN3;
										}
										case '4':
										{
											idx += 6;
											return X11_GREEN4;
										}
										case 'y':
										{
											if (str[6] && !strcmp(str[6], !"ELLOW", true, 5))
											{
												idx += 11;
												return X11_GREENYELLOW;
											}
										}
									}
									idx += 5;
									return X11_GREEN;
								}
								case 'y':
								{
									switch (str[4] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[4])
											{
												switch (str[5] | 0x20)
												{
													case '0':
													{
														idx += 6;
														return X11_GREY_0;
													}
													case '1':
													{
														switch (str[6] | 0x20)
														{
															case '0':
															{
																switch (str[7] | 0x20)
																{
																	case '0':
																	{
																		idx += 8;
																		return X11_GREY_100;
																	}
																}
																idx += 7;
																return X11_GREY_10;
															}
															case '1':
															{
																idx += 7;
																return X11_GREY_11;
															}
															case '2':
															{
																idx += 7;
																return X11_GREY_12;
															}
															case '3':
															{
																idx += 7;
																return X11_GREY_13;
															}
															case '4':
															{
																idx += 7;
																return X11_GREY_14;
															}
															case '5':
															{
																idx += 7;
																return X11_GREY_15;
															}
															case '6':
															{
																idx += 7;
																return X11_GREY_16;
															}
															case '7':
															{
																idx += 7;
																return X11_GREY_17;
															}
															case '8':
															{
																idx += 7;
																return X11_GREY_18;
															}
															case '9':
															{
																idx += 7;
																return X11_GREY_19;
															}
														}
														idx += 6;
														return X11_GREY_1;
													}
													case '2':
													{
														switch (str[6] | 0x20)
														{
															case '0':
															{
																idx += 7;
																return X11_GREY_20;
															}
															case '1':
															{
																idx += 7;
																return X11_GREY_21;
															}
															case '2':
															{
																idx += 7;
																return X11_GREY_22;
															}
															case '3':
															{
																idx += 7;
																return X11_GREY_23;
															}
															case '4':
															{
																idx += 7;
																return X11_GREY_24;
															}
															case '5':
															{
																idx += 7;
																return X11_GREY_25;
															}
															case '6':
															{
																idx += 7;
																return X11_GREY_26;
															}
															case '7':
															{
																idx += 7;
																return X11_GREY_27;
															}
															case '8':
															{
																idx += 7;
																return X11_GREY_28;
															}
															case '9':
															{
																idx += 7;
																return X11_GREY_29;
															}
														}
														idx += 6;
														return X11_GREY_2;
													}
													case '3':
													{
														switch (str[6] | 0x20)
														{
															case '0':
															{
																idx += 7;
																return X11_GREY_30;
															}
															case '1':
															{
																idx += 7;
																return X11_GREY_31;
															}
															case '2':
															{
																idx += 7;
																return X11_GREY_32;
															}
															case '3':
															{
																idx += 7;
																return X11_GREY_33;
															}
															case '4':
															{
																idx += 7;
																return X11_GREY_34;
															}
															case '5':
															{
																idx += 7;
																return X11_GREY_35;
															}
															case '6':
															{
																idx += 7;
																return X11_GREY_36;
															}
															case '7':
															{
																idx += 7;
																return X11_GREY_37;
															}
															case '8':
															{
																idx += 7;
																return X11_GREY_38;
															}
															case '9':
															{
																idx += 7;
																return X11_GREY_39;
															}
														}
														idx += 6;
														return X11_GREY_3;
													}
													case '4':
													{
														switch (str[6] | 0x20)
														{
															case '0':
															{
																idx += 7;
																return X11_GREY_40;
															}
															case '1':
															{
																idx += 7;
																return X11_GREY_41;
															}
															case '2':
															{
																idx += 7;
																return X11_GREY_42;
															}
															case '3':
															{
																idx += 7;
																return X11_GREY_43;
															}
															case '4':
															{
																idx += 7;
																return X11_GREY_44;
															}
															case '5':
															{
																idx += 7;
																return X11_GREY_45;
															}
															case '6':
															{
																idx += 7;
																return X11_GREY_46;
															}
															case '7':
															{
																idx += 7;
																return X11_GREY_47;
															}
															case '8':
															{
																idx += 7;
																return X11_GREY_48;
															}
															case '9':
															{
																idx += 7;
																return X11_GREY_49;
															}
														}
														idx += 6;
														return X11_GREY_4;
													}
													case '5':
													{
														switch (str[6] | 0x20)
														{
															case '0':
															{
																idx += 7;
																return X11_GREY_50;
															}
															case '1':
															{
																idx += 7;
																return X11_GREY_51;
															}
															case '2':
															{
																idx += 7;
																return X11_GREY_52;
															}
															case '3':
															{
																idx += 7;
																return X11_GREY_53;
															}
															case '4':
															{
																idx += 7;
																return X11_GREY_54;
															}
															case '5':
															{
																idx += 7;
																return X11_GREY_55;
															}
															case '6':
															{
																idx += 7;
																return X11_GREY_56;
															}
															case '7':
															{
																idx += 7;
																return X11_GREY_57;
															}
															case '8':
															{
																idx += 7;
																return X11_GREY_58;
															}
															case '9':
															{
																idx += 7;
																return X11_GREY_59;
															}
														}
														idx += 6;
														return X11_GREY_5;
													}
													case '6':
													{
														switch (str[6] | 0x20)
														{
															case '0':
															{
																idx += 7;
																return X11_GREY_60;
															}
															case '1':
															{
																idx += 7;
																return X11_GREY_61;
															}
															case '2':
															{
																idx += 7;
																return X11_GREY_62;
															}
															case '3':
															{
																idx += 7;
																return X11_GREY_63;
															}
															case '4':
															{
																idx += 7;
																return X11_GREY_64;
															}
															case '5':
															{
																idx += 7;
																return X11_GREY_65;
															}
															case '6':
															{
																idx += 7;
																return X11_GREY_66;
															}
															case '7':
															{
																idx += 7;
																return X11_GREY_67;
															}
															case '8':
															{
																idx += 7;
																return X11_GREY_68;
															}
															case '9':
															{
																idx += 7;
																return X11_GREY_69;
															}
														}
														idx += 6;
														return X11_GREY_6;
													}
													case '7':
													{
														switch (str[6] | 0x20)
														{
															case '0':
															{
																idx += 7;
																return X11_GREY_70;
															}
															case '1':
															{
																idx += 7;
																return X11_GREY_71;
															}
															case '2':
															{
																idx += 7;
																return X11_GREY_72;
															}
															case '3':
															{
																idx += 7;
																return X11_GREY_73;
															}
															case '4':
															{
																idx += 7;
																return X11_GREY_74;
															}
															case '5':
															{
																idx += 7;
																return X11_GREY_75;
															}
															case '6':
															{
																idx += 7;
																return X11_GREY_76;
															}
															case '7':
															{
																idx += 7;
																return X11_GREY_77;
															}
															case '8':
															{
																idx += 7;
																return X11_GREY_78;
															}
															case '9':
															{
																idx += 7;
																return X11_GREY_79;
															}
														}
														idx += 6;
														return X11_GREY_7;
													}
													case '8':
													{
														switch (str[6] | 0x20)
														{
															case '0':
															{
																idx += 7;
																return X11_GREY_80;
															}
															case '1':
															{
																idx += 7;
																return X11_GREY_81;
															}
															case '2':
															{
																idx += 7;
																return X11_GREY_82;
															}
															case '3':
															{
																idx += 7;
																return X11_GREY_83;
															}
															case '4':
															{
																idx += 7;
																return X11_GREY_84;
															}
															case '5':
															{
																idx += 7;
																return X11_GREY_85;
															}
															case '6':
															{
																idx += 7;
																return X11_GREY_86;
															}
															case '7':
															{
																idx += 7;
																return X11_GREY_87;
															}
															case '8':
															{
																idx += 7;
																return X11_GREY_88;
															}
															case '9':
															{
																idx += 7;
																return X11_GREY_89;
															}
														}
														idx += 6;
														return X11_GREY_8;
													}
													case '9':
													{
														switch (str[6] | 0x20)
														{
															case '0':
															{
																idx += 7;
																return X11_GREY_90;
															}
															case '1':
															{
																idx += 7;
																return X11_GREY_91;
															}
															case '2':
															{
																idx += 7;
																return X11_GREY_92;
															}
															case '3':
															{
																idx += 7;
																return X11_GREY_93;
															}
															case '4':
															{
																idx += 7;
																return X11_GREY_94;
															}
															case '5':
															{
																idx += 7;
																return X11_GREY_95;
															}
															case '6':
															{
																idx += 7;
																return X11_GREY_96;
															}
															case '7':
															{
																idx += 7;
																return X11_GREY_97;
															}
															case '8':
															{
																idx += 7;
																return X11_GREY_98;
															}
															case '9':
															{
																idx += 7;
																return X11_GREY_99;
															}
														}
														idx += 6;
														return X11_GREY_9;
													}
												}
											}
										}
										case '_' | 0x20:
										{
											switch (str[5] | 0x20)
											{
												case '0':
												{
													idx += 6;
													return X11_GREY_0;
												}
												case '1':
												{
													switch (str[6] | 0x20)
													{
														case '0':
														{
															switch (str[7] | 0x20)
															{
																case '0':
																{
																	idx += 8;
																	return X11_GREY_100;
																}
															}
															idx += 7;
															return X11_GREY_10;
														}
														case '1':
														{
															idx += 7;
															return X11_GREY_11;
														}
														case '2':
														{
															idx += 7;
															return X11_GREY_12;
														}
														case '3':
														{
															idx += 7;
															return X11_GREY_13;
														}
														case '4':
														{
															idx += 7;
															return X11_GREY_14;
														}
														case '5':
														{
															idx += 7;
															return X11_GREY_15;
														}
														case '6':
														{
															idx += 7;
															return X11_GREY_16;
														}
														case '7':
														{
															idx += 7;
															return X11_GREY_17;
														}
														case '8':
														{
															idx += 7;
															return X11_GREY_18;
														}
														case '9':
														{
															idx += 7;
															return X11_GREY_19;
														}
													}
													idx += 6;
													return X11_GREY_1;
												}
												case '2':
												{
													switch (str[6] | 0x20)
													{
														case '0':
														{
															idx += 7;
															return X11_GREY_20;
														}
														case '1':
														{
															idx += 7;
															return X11_GREY_21;
														}
														case '2':
														{
															idx += 7;
															return X11_GREY_22;
														}
														case '3':
														{
															idx += 7;
															return X11_GREY_23;
														}
														case '4':
														{
															idx += 7;
															return X11_GREY_24;
														}
														case '5':
														{
															idx += 7;
															return X11_GREY_25;
														}
														case '6':
														{
															idx += 7;
															return X11_GREY_26;
														}
														case '7':
														{
															idx += 7;
															return X11_GREY_27;
														}
														case '8':
														{
															idx += 7;
															return X11_GREY_28;
														}
														case '9':
														{
															idx += 7;
															return X11_GREY_29;
														}
													}
													idx += 6;
													return X11_GREY_2;
												}
												case '3':
												{
													switch (str[6] | 0x20)
													{
														case '0':
														{
															idx += 7;
															return X11_GREY_30;
														}
														case '1':
														{
															idx += 7;
															return X11_GREY_31;
														}
														case '2':
														{
															idx += 7;
															return X11_GREY_32;
														}
														case '3':
														{
															idx += 7;
															return X11_GREY_33;
														}
														case '4':
														{
															idx += 7;
															return X11_GREY_34;
														}
														case '5':
														{
															idx += 7;
															return X11_GREY_35;
														}
														case '6':
														{
															idx += 7;
															return X11_GREY_36;
														}
														case '7':
														{
															idx += 7;
															return X11_GREY_37;
														}
														case '8':
														{
															idx += 7;
															return X11_GREY_38;
														}
														case '9':
														{
															idx += 7;
															return X11_GREY_39;
														}
													}
													idx += 6;
													return X11_GREY_3;
												}
												case '4':
												{
													switch (str[6] | 0x20)
													{
														case '0':
														{
															idx += 7;
															return X11_GREY_40;
														}
														case '1':
														{
															idx += 7;
															return X11_GREY_41;
														}
														case '2':
														{
															idx += 7;
															return X11_GREY_42;
														}
														case '3':
														{
															idx += 7;
															return X11_GREY_43;
														}
														case '4':
														{
															idx += 7;
															return X11_GREY_44;
														}
														case '5':
														{
															idx += 7;
															return X11_GREY_45;
														}
														case '6':
														{
															idx += 7;
															return X11_GREY_46;
														}
														case '7':
														{
															idx += 7;
															return X11_GREY_47;
														}
														case '8':
														{
															idx += 7;
															return X11_GREY_48;
														}
														case '9':
														{
															idx += 7;
															return X11_GREY_49;
														}
													}
													idx += 6;
													return X11_GREY_4;
												}
												case '5':
												{
													switch (str[6] | 0x20)
													{
														case '0':
														{
															idx += 7;
															return X11_GREY_50;
														}
														case '1':
														{
															idx += 7;
															return X11_GREY_51;
														}
														case '2':
														{
															idx += 7;
															return X11_GREY_52;
														}
														case '3':
														{
															idx += 7;
															return X11_GREY_53;
														}
														case '4':
														{
															idx += 7;
															return X11_GREY_54;
														}
														case '5':
														{
															idx += 7;
															return X11_GREY_55;
														}
														case '6':
														{
															idx += 7;
															return X11_GREY_56;
														}
														case '7':
														{
															idx += 7;
															return X11_GREY_57;
														}
														case '8':
														{
															idx += 7;
															return X11_GREY_58;
														}
														case '9':
														{
															idx += 7;
															return X11_GREY_59;
														}
													}
													idx += 6;
													return X11_GREY_5;
												}
												case '6':
												{
													switch (str[6] | 0x20)
													{
														case '0':
														{
															idx += 7;
															return X11_GREY_60;
														}
														case '1':
														{
															idx += 7;
															return X11_GREY_61;
														}
														case '2':
														{
															idx += 7;
															return X11_GREY_62;
														}
														case '3':
														{
															idx += 7;
															return X11_GREY_63;
														}
														case '4':
														{
															idx += 7;
															return X11_GREY_64;
														}
														case '5':
														{
															idx += 7;
															return X11_GREY_65;
														}
														case '6':
														{
															idx += 7;
															return X11_GREY_66;
														}
														case '7':
														{
															idx += 7;
															return X11_GREY_67;
														}
														case '8':
														{
															idx += 7;
															return X11_GREY_68;
														}
														case '9':
														{
															idx += 7;
															return X11_GREY_69;
														}
													}
													idx += 6;
													return X11_GREY_6;
												}
												case '7':
												{
													switch (str[6] | 0x20)
													{
														case '0':
														{
															idx += 7;
															return X11_GREY_70;
														}
														case '1':
														{
															idx += 7;
															return X11_GREY_71;
														}
														case '2':
														{
															idx += 7;
															return X11_GREY_72;
														}
														case '3':
														{
															idx += 7;
															return X11_GREY_73;
														}
														case '4':
														{
															idx += 7;
															return X11_GREY_74;
														}
														case '5':
														{
															idx += 7;
															return X11_GREY_75;
														}
														case '6':
														{
															idx += 7;
															return X11_GREY_76;
														}
														case '7':
														{
															idx += 7;
															return X11_GREY_77;
														}
														case '8':
														{
															idx += 7;
															return X11_GREY_78;
														}
														case '9':
														{
															idx += 7;
															return X11_GREY_79;
														}
													}
													idx += 6;
													return X11_GREY_7;
												}
												case '8':
												{
													switch (str[6] | 0x20)
													{
														case '0':
														{
															idx += 7;
															return X11_GREY_80;
														}
														case '1':
														{
															idx += 7;
															return X11_GREY_81;
														}
														case '2':
														{
															idx += 7;
															return X11_GREY_82;
														}
														case '3':
														{
															idx += 7;
															return X11_GREY_83;
														}
														case '4':
														{
															idx += 7;
															return X11_GREY_84;
														}
														case '5':
														{
															idx += 7;
															return X11_GREY_85;
														}
														case '6':
														{
															idx += 7;
															return X11_GREY_86;
														}
														case '7':
														{
															idx += 7;
															return X11_GREY_87;
														}
														case '8':
														{
															idx += 7;
															return X11_GREY_88;
														}
														case '9':
														{
															idx += 7;
															return X11_GREY_89;
														}
													}
													idx += 6;
													return X11_GREY_8;
												}
												case '9':
												{
													switch (str[6] | 0x20)
													{
														case '0':
														{
															idx += 7;
															return X11_GREY_90;
														}
														case '1':
														{
															idx += 7;
															return X11_GREY_91;
														}
														case '2':
														{
															idx += 7;
															return X11_GREY_92;
														}
														case '3':
														{
															idx += 7;
															return X11_GREY_93;
														}
														case '4':
														{
															idx += 7;
															return X11_GREY_94;
														}
														case '5':
														{
															idx += 7;
															return X11_GREY_95;
														}
														case '6':
														{
															idx += 7;
															return X11_GREY_96;
														}
														case '7':
														{
															idx += 7;
															return X11_GREY_97;
														}
														case '8':
														{
															idx += 7;
															return X11_GREY_98;
														}
														case '9':
														{
															idx += 7;
															return X11_GREY_99;
														}
													}
													idx += 6;
													return X11_GREY_9;
												}
											}
										}
										case '0':
										{
											idx += 5;
											return X11_GREY0;
										}
										case '1':
										{
											switch (str[5] | 0x20)
											{
												case '0':
												{
													switch (str[6] | 0x20)
													{
														case '0':
														{
															idx += 7;
															return X11_GREY100;
														}
													}
													idx += 6;
													return X11_GREY10;
												}
												case '1':
												{
													idx += 6;
													return X11_GREY11;
												}
												case '2':
												{
													idx += 6;
													return X11_GREY12;
												}
												case '3':
												{
													idx += 6;
													return X11_GREY13;
												}
												case '4':
												{
													idx += 6;
													return X11_GREY14;
												}
												case '5':
												{
													idx += 6;
													return X11_GREY15;
												}
												case '6':
												{
													idx += 6;
													return X11_GREY16;
												}
												case '7':
												{
													idx += 6;
													return X11_GREY17;
												}
												case '8':
												{
													idx += 6;
													return X11_GREY18;
												}
												case '9':
												{
													idx += 6;
													return X11_GREY19;
												}
											}
											idx += 5;
											return X11_GREY1;
										}
										case '2':
										{
											switch (str[5] | 0x20)
											{
												case '0':
												{
													idx += 6;
													return X11_GREY20;
												}
												case '1':
												{
													idx += 6;
													return X11_GREY21;
												}
												case '2':
												{
													idx += 6;
													return X11_GREY22;
												}
												case '3':
												{
													idx += 6;
													return X11_GREY23;
												}
												case '4':
												{
													idx += 6;
													return X11_GREY24;
												}
												case '5':
												{
													idx += 6;
													return X11_GREY25;
												}
												case '6':
												{
													idx += 6;
													return X11_GREY26;
												}
												case '7':
												{
													idx += 6;
													return X11_GREY27;
												}
												case '8':
												{
													idx += 6;
													return X11_GREY28;
												}
												case '9':
												{
													idx += 6;
													return X11_GREY29;
												}
											}
											idx += 5;
											return X11_GREY2;
										}
										case '3':
										{
											switch (str[5] | 0x20)
											{
												case '0':
												{
													idx += 6;
													return X11_GREY30;
												}
												case '1':
												{
													idx += 6;
													return X11_GREY31;
												}
												case '2':
												{
													idx += 6;
													return X11_GREY32;
												}
												case '3':
												{
													idx += 6;
													return X11_GREY33;
												}
												case '4':
												{
													idx += 6;
													return X11_GREY34;
												}
												case '5':
												{
													idx += 6;
													return X11_GREY35;
												}
												case '6':
												{
													idx += 6;
													return X11_GREY36;
												}
												case '7':
												{
													idx += 6;
													return X11_GREY37;
												}
												case '8':
												{
													idx += 6;
													return X11_GREY38;
												}
												case '9':
												{
													idx += 6;
													return X11_GREY39;
												}
											}
											idx += 5;
											return X11_GREY3;
										}
										case '4':
										{
											switch (str[5] | 0x20)
											{
												case '0':
												{
													idx += 6;
													return X11_GREY40;
												}
												case '1':
												{
													idx += 6;
													return X11_GREY41;
												}
												case '2':
												{
													idx += 6;
													return X11_GREY42;
												}
												case '3':
												{
													idx += 6;
													return X11_GREY43;
												}
												case '4':
												{
													idx += 6;
													return X11_GREY44;
												}
												case '5':
												{
													idx += 6;
													return X11_GREY45;
												}
												case '6':
												{
													idx += 6;
													return X11_GREY46;
												}
												case '7':
												{
													idx += 6;
													return X11_GREY47;
												}
												case '8':
												{
													idx += 6;
													return X11_GREY48;
												}
												case '9':
												{
													idx += 6;
													return X11_GREY49;
												}
											}
											idx += 5;
											return X11_GREY4;
										}
										case '5':
										{
											switch (str[5] | 0x20)
											{
												case '0':
												{
													idx += 6;
													return X11_GREY50;
												}
												case '1':
												{
													idx += 6;
													return X11_GREY51;
												}
												case '2':
												{
													idx += 6;
													return X11_GREY52;
												}
												case '3':
												{
													idx += 6;
													return X11_GREY53;
												}
												case '4':
												{
													idx += 6;
													return X11_GREY54;
												}
												case '5':
												{
													idx += 6;
													return X11_GREY55;
												}
												case '6':
												{
													idx += 6;
													return X11_GREY56;
												}
												case '7':
												{
													idx += 6;
													return X11_GREY57;
												}
												case '8':
												{
													idx += 6;
													return X11_GREY58;
												}
												case '9':
												{
													idx += 6;
													return X11_GREY59;
												}
											}
											idx += 5;
											return X11_GREY5;
										}
										case '6':
										{
											switch (str[5] | 0x20)
											{
												case '0':
												{
													idx += 6;
													return X11_GREY60;
												}
												case '1':
												{
													idx += 6;
													return X11_GREY61;
												}
												case '2':
												{
													idx += 6;
													return X11_GREY62;
												}
												case '3':
												{
													idx += 6;
													return X11_GREY63;
												}
												case '4':
												{
													idx += 6;
													return X11_GREY64;
												}
												case '5':
												{
													idx += 6;
													return X11_GREY65;
												}
												case '6':
												{
													idx += 6;
													return X11_GREY66;
												}
												case '7':
												{
													idx += 6;
													return X11_GREY67;
												}
												case '8':
												{
													idx += 6;
													return X11_GREY68;
												}
												case '9':
												{
													idx += 6;
													return X11_GREY69;
												}
											}
											idx += 5;
											return X11_GREY6;
										}
										case '7':
										{
											switch (str[5] | 0x20)
											{
												case '0':
												{
													idx += 6;
													return X11_GREY70;
												}
												case '1':
												{
													idx += 6;
													return X11_GREY71;
												}
												case '2':
												{
													idx += 6;
													return X11_GREY72;
												}
												case '3':
												{
													idx += 6;
													return X11_GREY73;
												}
												case '4':
												{
													idx += 6;
													return X11_GREY74;
												}
												case '5':
												{
													idx += 6;
													return X11_GREY75;
												}
												case '6':
												{
													idx += 6;
													return X11_GREY76;
												}
												case '7':
												{
													idx += 6;
													return X11_GREY77;
												}
												case '8':
												{
													idx += 6;
													return X11_GREY78;
												}
												case '9':
												{
													idx += 6;
													return X11_GREY79;
												}
											}
											idx += 5;
											return X11_GREY7;
										}
										case '8':
										{
											switch (str[5] | 0x20)
											{
												case '0':
												{
													idx += 6;
													return X11_GREY80;
												}
												case '1':
												{
													idx += 6;
													return X11_GREY81;
												}
												case '2':
												{
													idx += 6;
													return X11_GREY82;
												}
												case '3':
												{
													idx += 6;
													return X11_GREY83;
												}
												case '4':
												{
													idx += 6;
													return X11_GREY84;
												}
												case '5':
												{
													idx += 6;
													return X11_GREY85;
												}
												case '6':
												{
													idx += 6;
													return X11_GREY86;
												}
												case '7':
												{
													idx += 6;
													return X11_GREY87;
												}
												case '8':
												{
													idx += 6;
													return X11_GREY88;
												}
												case '9':
												{
													idx += 6;
													return X11_GREY89;
												}
											}
											idx += 5;
											return X11_GREY8;
										}
										case '9':
										{
											switch (str[5] | 0x20)
											{
												case '0':
												{
													idx += 6;
													return X11_GREY90;
												}
												case '1':
												{
													idx += 6;
													return X11_GREY91;
												}
												case '2':
												{
													idx += 6;
													return X11_GREY92;
												}
												case '3':
												{
													idx += 6;
													return X11_GREY93;
												}
												case '4':
												{
													idx += 6;
													return X11_GREY94;
												}
												case '5':
												{
													idx += 6;
													return X11_GREY95;
												}
												case '6':
												{
													idx += 6;
													return X11_GREY96;
												}
												case '7':
												{
													idx += 6;
													return X11_GREY97;
												}
												case '8':
												{
													idx += 6;
													return X11_GREY98;
												}
												case '9':
												{
													idx += 6;
													return X11_GREY99;
												}
											}
											idx += 5;
											return X11_GREY9;
										}
									}
									idx += 4;
									return X11_GREY;
								}
							}
						}
					}
				}
			}
		}
		case 'h':
		{
			if (str[1] | 0x20 != 'o')
			{
				return -1;
			}
			switch (str[2] | 0x20)
			{
				case 'n':
				{
					if (!str[3] || strcmp(str[3], !"EYDEW", true, 5))
					{
						return -1;
					}
					switch (str[8] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[8])
							{
								switch (str[9] | 0x20)
								{
									case '1':
									{
										idx += 10;
										return X11_HONEYDEW_1;
									}
									case '2':
									{
										idx += 10;
										return X11_HONEYDEW_2;
									}
									case '3':
									{
										idx += 10;
										return X11_HONEYDEW_3;
									}
									case '4':
									{
										idx += 10;
										return X11_HONEYDEW_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[9] | 0x20)
							{
								case '1':
								{
									idx += 10;
									return X11_HONEYDEW_1;
								}
								case '2':
								{
									idx += 10;
									return X11_HONEYDEW_2;
								}
								case '3':
								{
									idx += 10;
									return X11_HONEYDEW_3;
								}
								case '4':
								{
									idx += 10;
									return X11_HONEYDEW_4;
								}
							}
						}
						case '1':
						{
							idx += 9;
							return X11_HONEYDEW1;
						}
						case '2':
						{
							idx += 9;
							return X11_HONEYDEW2;
						}
						case '3':
						{
							idx += 9;
							return X11_HONEYDEW3;
						}
						case '4':
						{
							idx += 9;
							return X11_HONEYDEW4;
						}
					}
					idx += 8;
					return X11_HONEYDEW;
				}
				case 't':
				{
					switch (str[3] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[3])
							{
								if (!str[4] || strcmp(str[4], !"PINK", true, 4))
								{
									return -1;
								}
								switch (str[8] | 0x20)
								{
									case _X11_SPACE_SWITCH: // ' '
									{
										if (str[8])
										{
											switch (str[9] | 0x20)
											{
												case '1':
												{
													idx += 10;
													return X11_HOT_PINK_1;
												}
												case '2':
												{
													idx += 10;
													return X11_HOT_PINK_2;
												}
												case '3':
												{
													idx += 10;
													return X11_HOT_PINK_3;
												}
												case '4':
												{
													idx += 10;
													return X11_HOT_PINK_4;
												}
											}
										}
									}
									case '_' | 0x20:
									{
										switch (str[9] | 0x20)
										{
											case '1':
											{
												idx += 10;
												return X11_HOT_PINK_1;
											}
											case '2':
											{
												idx += 10;
												return X11_HOT_PINK_2;
											}
											case '3':
											{
												idx += 10;
												return X11_HOT_PINK_3;
											}
											case '4':
											{
												idx += 10;
												return X11_HOT_PINK_4;
											}
										}
									}
								}
								idx += 8;
								return X11_HOT_PINK;
							}
						}
						case '_' | 0x20:
						{
							if (!str[4] || strcmp(str[4], !"PINK", true, 4))
							{
								return -1;
							}
							switch (str[8] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[8])
									{
										switch (str[9] | 0x20)
										{
											case '1':
											{
												idx += 10;
												return X11_HOT_PINK_1;
											}
											case '2':
											{
												idx += 10;
												return X11_HOT_PINK_2;
											}
											case '3':
											{
												idx += 10;
												return X11_HOT_PINK_3;
											}
											case '4':
											{
												idx += 10;
												return X11_HOT_PINK_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[9] | 0x20)
									{
										case '1':
										{
											idx += 10;
											return X11_HOT_PINK_1;
										}
										case '2':
										{
											idx += 10;
											return X11_HOT_PINK_2;
										}
										case '3':
										{
											idx += 10;
											return X11_HOT_PINK_3;
										}
										case '4':
										{
											idx += 10;
											return X11_HOT_PINK_4;
										}
									}
								}
							}
							idx += 8;
							return X11_HOT_PINK;
						}
						case 'p':
						{
							if (!str[4] || strcmp(str[4], !"INK", true, 3))
							{
								return -1;
							}
							switch (str[7] | 0x20)
							{
								case '1':
								{
									idx += 8;
									return X11_HOTPINK1;
								}
								case '2':
								{
									idx += 8;
									return X11_HOTPINK2;
								}
								case '3':
								{
									idx += 8;
									return X11_HOTPINK3;
								}
								case '4':
								{
									idx += 8;
									return X11_HOTPINK4;
								}
							}
							idx += 7;
							return X11_HOTPINK;
						}
					}
				}
			}
		}
		case 'i':
		{
			switch (str[1] | 0x20)
			{
				case 'n':
				{
					if (!str[2] || strcmp(str[2], !"DIAN", true, 4))
					{
						return -1;
					}
					switch (str[6] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[6])
							{
								if (!str[7] || strcmp(str[7], !"RED", true, 3))
								{
									return -1;
								}
								switch (str[10] | 0x20)
								{
									case _X11_SPACE_SWITCH: // ' '
									{
										if (str[10])
										{
											switch (str[11] | 0x20)
											{
												case '1':
												{
													idx += 12;
													return X11_INDIAN_RED_1;
												}
												case '2':
												{
													idx += 12;
													return X11_INDIAN_RED_2;
												}
												case '3':
												{
													idx += 12;
													return X11_INDIAN_RED_3;
												}
												case '4':
												{
													idx += 12;
													return X11_INDIAN_RED_4;
												}
											}
										}
									}
									case '_' | 0x20:
									{
										switch (str[11] | 0x20)
										{
											case '1':
											{
												idx += 12;
												return X11_INDIAN_RED_1;
											}
											case '2':
											{
												idx += 12;
												return X11_INDIAN_RED_2;
											}
											case '3':
											{
												idx += 12;
												return X11_INDIAN_RED_3;
											}
											case '4':
											{
												idx += 12;
												return X11_INDIAN_RED_4;
											}
										}
									}
								}
								idx += 10;
								return X11_INDIAN_RED;
							}
						}
						case '_' | 0x20:
						{
							if (!str[7] || strcmp(str[7], !"RED", true, 3))
							{
								return -1;
							}
							switch (str[10] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[10])
									{
										switch (str[11] | 0x20)
										{
											case '1':
											{
												idx += 12;
												return X11_INDIAN_RED_1;
											}
											case '2':
											{
												idx += 12;
												return X11_INDIAN_RED_2;
											}
											case '3':
											{
												idx += 12;
												return X11_INDIAN_RED_3;
											}
											case '4':
											{
												idx += 12;
												return X11_INDIAN_RED_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[11] | 0x20)
									{
										case '1':
										{
											idx += 12;
											return X11_INDIAN_RED_1;
										}
										case '2':
										{
											idx += 12;
											return X11_INDIAN_RED_2;
										}
										case '3':
										{
											idx += 12;
											return X11_INDIAN_RED_3;
										}
										case '4':
										{
											idx += 12;
											return X11_INDIAN_RED_4;
										}
									}
								}
							}
							idx += 10;
							return X11_INDIAN_RED;
						}
						case 'r':
						{
							if (!str[7] || strcmp(str[7], !"ED", true, 2))
							{
								return -1;
							}
							switch (str[9] | 0x20)
							{
								case '1':
								{
									idx += 10;
									return X11_INDIANRED1;
								}
								case '2':
								{
									idx += 10;
									return X11_INDIANRED2;
								}
								case '3':
								{
									idx += 10;
									return X11_INDIANRED3;
								}
								case '4':
								{
									idx += 10;
									return X11_INDIANRED4;
								}
							}
							idx += 9;
							return X11_INDIANRED;
						}
					}
				}
				case 'v':
				{
					if (!str[2] || strcmp(str[2], !"ORY", true, 3))
					{
						return -1;
					}
					switch (str[5] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[5])
							{
								switch (str[6] | 0x20)
								{
									case '1':
									{
										idx += 7;
										return X11_IVORY_1;
									}
									case '2':
									{
										idx += 7;
										return X11_IVORY_2;
									}
									case '3':
									{
										idx += 7;
										return X11_IVORY_3;
									}
									case '4':
									{
										idx += 7;
										return X11_IVORY_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[6] | 0x20)
							{
								case '1':
								{
									idx += 7;
									return X11_IVORY_1;
								}
								case '2':
								{
									idx += 7;
									return X11_IVORY_2;
								}
								case '3':
								{
									idx += 7;
									return X11_IVORY_3;
								}
								case '4':
								{
									idx += 7;
									return X11_IVORY_4;
								}
							}
						}
						case '1':
						{
							idx += 6;
							return X11_IVORY1;
						}
						case '2':
						{
							idx += 6;
							return X11_IVORY2;
						}
						case '3':
						{
							idx += 6;
							return X11_IVORY3;
						}
						case '4':
						{
							idx += 6;
							return X11_IVORY4;
						}
					}
					idx += 5;
					return X11_IVORY;
				}
			}
		}
		case 'k':
		{
			if (!str[1] || strcmp(str[1], !"HAKI", true, 4))
			{
				return -1;
			}
			switch (str[5] | 0x20)
			{
				case _X11_SPACE_SWITCH: // ' '
				{
					if (str[5])
					{
						switch (str[6] | 0x20)
						{
							case '1':
							{
								idx += 7;
								return X11_KHAKI_1;
							}
							case '2':
							{
								idx += 7;
								return X11_KHAKI_2;
							}
							case '3':
							{
								idx += 7;
								return X11_KHAKI_3;
							}
							case '4':
							{
								idx += 7;
								return X11_KHAKI_4;
							}
						}
					}
				}
				case '_' | 0x20:
				{
					switch (str[6] | 0x20)
					{
						case '1':
						{
							idx += 7;
							return X11_KHAKI_1;
						}
						case '2':
						{
							idx += 7;
							return X11_KHAKI_2;
						}
						case '3':
						{
							idx += 7;
							return X11_KHAKI_3;
						}
						case '4':
						{
							idx += 7;
							return X11_KHAKI_4;
						}
					}
				}
				case '1':
				{
					idx += 6;
					return X11_KHAKI1;
				}
				case '2':
				{
					idx += 6;
					return X11_KHAKI2;
				}
				case '3':
				{
					idx += 6;
					return X11_KHAKI3;
				}
				case '4':
				{
					idx += 6;
					return X11_KHAKI4;
				}
			}
			idx += 5;
			return X11_KHAKI;
		}
		case 'l':
		{
			switch (str[1] | 0x20)
			{
				case 'a':
				{
					switch (str[2] | 0x20)
					{
						case 'v':
						{
							if (!str[3] || strcmp(str[3], !"ENDER", true, 5))
							{
								return -1;
							}
							switch (str[8] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[8])
									{
										if (!str[9] || strcmp(str[9], !"BLUSH", true, 5))
										{
											return -1;
										}
										switch (str[14] | 0x20)
										{
											case _X11_SPACE_SWITCH: // ' '
											{
												if (str[14])
												{
													switch (str[15] | 0x20)
													{
														case '1':
														{
															idx += 16;
															return X11_LAVENDER_BLUSH_1;
														}
														case '2':
														{
															idx += 16;
															return X11_LAVENDER_BLUSH_2;
														}
														case '3':
														{
															idx += 16;
															return X11_LAVENDER_BLUSH_3;
														}
														case '4':
														{
															idx += 16;
															return X11_LAVENDER_BLUSH_4;
														}
													}
												}
											}
											case '_' | 0x20:
											{
												switch (str[15] | 0x20)
												{
													case '1':
													{
														idx += 16;
														return X11_LAVENDER_BLUSH_1;
													}
													case '2':
													{
														idx += 16;
														return X11_LAVENDER_BLUSH_2;
													}
													case '3':
													{
														idx += 16;
														return X11_LAVENDER_BLUSH_3;
													}
													case '4':
													{
														idx += 16;
														return X11_LAVENDER_BLUSH_4;
													}
												}
											}
										}
										idx += 14;
										return X11_LAVENDER_BLUSH;
									}
								}
								case '_' | 0x20:
								{
									if (!str[9] || strcmp(str[9], !"BLUSH", true, 5))
									{
										return -1;
									}
									switch (str[14] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[14])
											{
												switch (str[15] | 0x20)
												{
													case '1':
													{
														idx += 16;
														return X11_LAVENDER_BLUSH_1;
													}
													case '2':
													{
														idx += 16;
														return X11_LAVENDER_BLUSH_2;
													}
													case '3':
													{
														idx += 16;
														return X11_LAVENDER_BLUSH_3;
													}
													case '4':
													{
														idx += 16;
														return X11_LAVENDER_BLUSH_4;
													}
												}
											}
										}
										case '_' | 0x20:
										{
											switch (str[15] | 0x20)
											{
												case '1':
												{
													idx += 16;
													return X11_LAVENDER_BLUSH_1;
												}
												case '2':
												{
													idx += 16;
													return X11_LAVENDER_BLUSH_2;
												}
												case '3':
												{
													idx += 16;
													return X11_LAVENDER_BLUSH_3;
												}
												case '4':
												{
													idx += 16;
													return X11_LAVENDER_BLUSH_4;
												}
											}
										}
									}
									idx += 14;
									return X11_LAVENDER_BLUSH;
								}
								case 'b':
								{
									if (!str[9] || strcmp(str[9], !"LUSH", true, 4))
									{
										return -1;
									}
									switch (str[13] | 0x20)
									{
										case '1':
										{
											idx += 14;
											return X11_LAVENDERBLUSH1;
										}
										case '2':
										{
											idx += 14;
											return X11_LAVENDERBLUSH2;
										}
										case '3':
										{
											idx += 14;
											return X11_LAVENDERBLUSH3;
										}
										case '4':
										{
											idx += 14;
											return X11_LAVENDERBLUSH4;
										}
									}
									idx += 13;
									return X11_LAVENDERBLUSH;
								}
							}
							idx += 8;
							return X11_LAVENDER;
						}
						case 'w':
						{
							if (str[3] | 0x20 != 'n')
							{
								return -1;
							}
							switch (str[4] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[4])
									{
										if (str[5] && !strcmp(str[5], !"GREEN", true, 5))
										{
											idx += 10;
											return X11_LAWN_GREEN;
										}
									}
								}
								case '_' | 0x20:
								{
									if (str[5] && !strcmp(str[5], !"GREEN", true, 5))
									{
										idx += 10;
										return X11_LAWN_GREEN;
									}
								}
								case 'g':
								{
									if (str[5] && !strcmp(str[5], !"REEN", true, 4))
									{
										idx += 9;
										return X11_LAWNGREEN;
									}
								}
							}
						}
					}
				}
				case 'e':
				{
					if (!str[2] || strcmp(str[2], !"MON", true, 3))
					{
						return -1;
					}
					switch (str[5] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[5])
							{
								if (!str[6] || strcmp(str[6], !"CHIFFON", true, 7))
								{
									return -1;
								}
								switch (str[13] | 0x20)
								{
									case _X11_SPACE_SWITCH: // ' '
									{
										if (str[13])
										{
											switch (str[14] | 0x20)
											{
												case '1':
												{
													idx += 15;
													return X11_LEMON_CHIFFON_1;
												}
												case '2':
												{
													idx += 15;
													return X11_LEMON_CHIFFON_2;
												}
												case '3':
												{
													idx += 15;
													return X11_LEMON_CHIFFON_3;
												}
												case '4':
												{
													idx += 15;
													return X11_LEMON_CHIFFON_4;
												}
											}
										}
									}
									case '_' | 0x20:
									{
										switch (str[14] | 0x20)
										{
											case '1':
											{
												idx += 15;
												return X11_LEMON_CHIFFON_1;
											}
											case '2':
											{
												idx += 15;
												return X11_LEMON_CHIFFON_2;
											}
											case '3':
											{
												idx += 15;
												return X11_LEMON_CHIFFON_3;
											}
											case '4':
											{
												idx += 15;
												return X11_LEMON_CHIFFON_4;
											}
										}
									}
								}
								idx += 13;
								return X11_LEMON_CHIFFON;
							}
						}
						case '_' | 0x20:
						{
							if (!str[6] || strcmp(str[6], !"CHIFFON", true, 7))
							{
								return -1;
							}
							switch (str[13] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[13])
									{
										switch (str[14] | 0x20)
										{
											case '1':
											{
												idx += 15;
												return X11_LEMON_CHIFFON_1;
											}
											case '2':
											{
												idx += 15;
												return X11_LEMON_CHIFFON_2;
											}
											case '3':
											{
												idx += 15;
												return X11_LEMON_CHIFFON_3;
											}
											case '4':
											{
												idx += 15;
												return X11_LEMON_CHIFFON_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[14] | 0x20)
									{
										case '1':
										{
											idx += 15;
											return X11_LEMON_CHIFFON_1;
										}
										case '2':
										{
											idx += 15;
											return X11_LEMON_CHIFFON_2;
										}
										case '3':
										{
											idx += 15;
											return X11_LEMON_CHIFFON_3;
										}
										case '4':
										{
											idx += 15;
											return X11_LEMON_CHIFFON_4;
										}
									}
								}
							}
							idx += 13;
							return X11_LEMON_CHIFFON;
						}
						case 'c':
						{
							if (!str[6] || strcmp(str[6], !"HIFFON", true, 6))
							{
								return -1;
							}
							switch (str[12] | 0x20)
							{
								case '1':
								{
									idx += 13;
									return X11_LEMONCHIFFON1;
								}
								case '2':
								{
									idx += 13;
									return X11_LEMONCHIFFON2;
								}
								case '3':
								{
									idx += 13;
									return X11_LEMONCHIFFON3;
								}
								case '4':
								{
									idx += 13;
									return X11_LEMONCHIFFON4;
								}
							}
							idx += 12;
							return X11_LEMONCHIFFON;
						}
					}
				}
				case 'i':
				{
					switch (str[2] | 0x20)
					{
						case 'g':
						{
							if (!str[3] || strcmp(str[3], !"HT", true, 2))
							{
								return -1;
							}
							switch (str[5] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[5])
									{
										switch (str[6] | 0x20)
										{
											case 'b':
											{
												if (!str[7] || strcmp(str[7], !"LUE", true, 3))
												{
													return -1;
												}
												switch (str[10] | 0x20)
												{
													case _X11_SPACE_SWITCH: // ' '
													{
														if (str[10])
														{
															switch (str[11] | 0x20)
															{
																case '1':
																{
																	idx += 12;
																	return X11_LIGHT_BLUE_1;
																}
																case '2':
																{
																	idx += 12;
																	return X11_LIGHT_BLUE_2;
																}
																case '3':
																{
																	idx += 12;
																	return X11_LIGHT_BLUE_3;
																}
																case '4':
																{
																	idx += 12;
																	return X11_LIGHT_BLUE_4;
																}
															}
														}
													}
													case '_' | 0x20:
													{
														switch (str[11] | 0x20)
														{
															case '1':
															{
																idx += 12;
																return X11_LIGHT_BLUE_1;
															}
															case '2':
															{
																idx += 12;
																return X11_LIGHT_BLUE_2;
															}
															case '3':
															{
																idx += 12;
																return X11_LIGHT_BLUE_3;
															}
															case '4':
															{
																idx += 12;
																return X11_LIGHT_BLUE_4;
															}
														}
													}
												}
												idx += 10;
												return X11_LIGHT_BLUE;
											}
											case 'c':
											{
												switch (str[7] | 0x20)
												{
													case 'o':
													{
														if (str[8] && !strcmp(str[8], !"RAL", true, 3))
														{
															idx += 11;
															return X11_LIGHT_CORAL;
														}
													}
													case 'y':
													{
														if (!str[8] || strcmp(str[8], !"AN", true, 2))
														{
															return -1;
														}
														switch (str[10] | 0x20)
														{
															case _X11_SPACE_SWITCH: // ' '
															{
																if (str[10])
																{
																	switch (str[11] | 0x20)
																	{
																		case '1':
																		{
																			idx += 12;
																			return X11_LIGHT_CYAN_1;
																		}
																		case '2':
																		{
																			idx += 12;
																			return X11_LIGHT_CYAN_2;
																		}
																		case '3':
																		{
																			idx += 12;
																			return X11_LIGHT_CYAN_3;
																		}
																		case '4':
																		{
																			idx += 12;
																			return X11_LIGHT_CYAN_4;
																		}
																	}
																}
															}
															case '_' | 0x20:
															{
																switch (str[11] | 0x20)
																{
																	case '1':
																	{
																		idx += 12;
																		return X11_LIGHT_CYAN_1;
																	}
																	case '2':
																	{
																		idx += 12;
																		return X11_LIGHT_CYAN_2;
																	}
																	case '3':
																	{
																		idx += 12;
																		return X11_LIGHT_CYAN_3;
																	}
																	case '4':
																	{
																		idx += 12;
																		return X11_LIGHT_CYAN_4;
																	}
																}
															}
														}
														idx += 10;
														return X11_LIGHT_CYAN;
													}
												}
											}
											case 'g':
											{
												switch (str[7] | 0x20)
												{
													case 'o':
													{
														if (!str[8] || strcmp(str[8], !"LDENROD", true, 7))
														{
															return -1;
														}
														switch (str[15] | 0x20)
														{
															case _X11_SPACE_SWITCH: // ' '
															{
																if (str[15])
																{
																	switch (str[16] | 0x20)
																	{
																		case '1':
																		{
																			idx += 17;
																			return X11_LIGHT_GOLDENROD_1;
																		}
																		case '2':
																		{
																			idx += 17;
																			return X11_LIGHT_GOLDENROD_2;
																		}
																		case '3':
																		{
																			idx += 17;
																			return X11_LIGHT_GOLDENROD_3;
																		}
																		case '4':
																		{
																			idx += 17;
																			return X11_LIGHT_GOLDENROD_4;
																		}
																		case 'y':
																		{
																			if (str[17] && !strcmp(str[17], !"ELLOW", true, 5))
																			{
																				idx += 22;
																				return X11_LIGHT_GOLDENROD_YELLOW;
																			}
																		}
																	}
																}
															}
															case '_' | 0x20:
															{
																switch (str[16] | 0x20)
																{
																	case '1':
																	{
																		idx += 17;
																		return X11_LIGHT_GOLDENROD_1;
																	}
																	case '2':
																	{
																		idx += 17;
																		return X11_LIGHT_GOLDENROD_2;
																	}
																	case '3':
																	{
																		idx += 17;
																		return X11_LIGHT_GOLDENROD_3;
																	}
																	case '4':
																	{
																		idx += 17;
																		return X11_LIGHT_GOLDENROD_4;
																	}
																	case 'y':
																	{
																		if (str[17] && !strcmp(str[17], !"ELLOW", true, 5))
																		{
																			idx += 22;
																			return X11_LIGHT_GOLDENROD_YELLOW;
																		}
																	}
																}
															}
														}
														idx += 15;
														return X11_LIGHT_GOLDENROD;
													}
													case 'r':
													{
														switch (str[8] | 0x20)
														{
															case 'a':
															{
																if (str[9] | 0x20 == 'y')
																{
																	idx += 10;
																	return X11_LIGHT_GRAY;
																}
															}
															case 'e':
															{
																switch (str[9] | 0x20)
																{
																	case 'e':
																	{
																		if (str[10] | 0x20 == 'n')
																		{
																			idx += 11;
																			return X11_LIGHT_GREEN;
																		}
																	}
																	case 'y':
																	{
																		idx += 10;
																		return X11_LIGHT_GREY;
																	}
																}
															}
														}
													}
												}
											}
											case 'p':
											{
												if (!str[7] || strcmp(str[7], !"INK", true, 3))
												{
													return -1;
												}
												switch (str[10] | 0x20)
												{
													case _X11_SPACE_SWITCH: // ' '
													{
														if (str[10])
														{
															switch (str[11] | 0x20)
															{
																case '1':
																{
																	idx += 12;
																	return X11_LIGHT_PINK_1;
																}
																case '2':
																{
																	idx += 12;
																	return X11_LIGHT_PINK_2;
																}
																case '3':
																{
																	idx += 12;
																	return X11_LIGHT_PINK_3;
																}
																case '4':
																{
																	idx += 12;
																	return X11_LIGHT_PINK_4;
																}
															}
														}
													}
													case '_' | 0x20:
													{
														switch (str[11] | 0x20)
														{
															case '1':
															{
																idx += 12;
																return X11_LIGHT_PINK_1;
															}
															case '2':
															{
																idx += 12;
																return X11_LIGHT_PINK_2;
															}
															case '3':
															{
																idx += 12;
																return X11_LIGHT_PINK_3;
															}
															case '4':
															{
																idx += 12;
																return X11_LIGHT_PINK_4;
															}
														}
													}
												}
												idx += 10;
												return X11_LIGHT_PINK;
											}
											case 's':
											{
												switch (str[7] | 0x20)
												{
													case 'a':
													{
														if (!str[8] || strcmp(str[8], !"LMON", true, 4))
														{
															return -1;
														}
														switch (str[12] | 0x20)
														{
															case _X11_SPACE_SWITCH: // ' '
															{
																if (str[12])
																{
																	switch (str[13] | 0x20)
																	{
																		case '1':
																		{
																			idx += 14;
																			return X11_LIGHT_SALMON_1;
																		}
																		case '2':
																		{
																			idx += 14;
																			return X11_LIGHT_SALMON_2;
																		}
																		case '3':
																		{
																			idx += 14;
																			return X11_LIGHT_SALMON_3;
																		}
																		case '4':
																		{
																			idx += 14;
																			return X11_LIGHT_SALMON_4;
																		}
																	}
																}
															}
															case '_' | 0x20:
															{
																switch (str[13] | 0x20)
																{
																	case '1':
																	{
																		idx += 14;
																		return X11_LIGHT_SALMON_1;
																	}
																	case '2':
																	{
																		idx += 14;
																		return X11_LIGHT_SALMON_2;
																	}
																	case '3':
																	{
																		idx += 14;
																		return X11_LIGHT_SALMON_3;
																	}
																	case '4':
																	{
																		idx += 14;
																		return X11_LIGHT_SALMON_4;
																	}
																}
															}
														}
														idx += 12;
														return X11_LIGHT_SALMON;
													}
													case 'e':
													{
														//if (str[8] && !strcmp(str[8], !"A_GREEN", true, 7))
														if (str[8] | 0x20 == 'a' && (_X11_SPACE_CHECK(9) || str[9] == '_') && !strcmp(str[10], !"GREEN", true, 5))
														{
															idx += 15;
															return X11_LIGHT_SEA_GREEN;
														}
													}
													case 'k':
													{
														//if (!str[8] || strcmp(str[8], !"Y_BLUE", true, 6))
														if (str[8] | 0x20 != 'y' || (!_X11_SPACE_CHECK(9) && str[9] != '_') || strcmp(str[10], !"BLUE", true, 4))
														{
															return -1;
														}
														switch (str[14] | 0x20)
														{
															case _X11_SPACE_SWITCH: // ' '
															{
																if (str[14])
																{
																	switch (str[15] | 0x20)
																	{
																		case '1':
																		{
																			idx += 16;
																			return X11_LIGHT_SKY_BLUE_1;
																		}
																		case '2':
																		{
																			idx += 16;
																			return X11_LIGHT_SKY_BLUE_2;
																		}
																		case '3':
																		{
																			idx += 16;
																			return X11_LIGHT_SKY_BLUE_3;
																		}
																		case '4':
																		{
																			idx += 16;
																			return X11_LIGHT_SKY_BLUE_4;
																		}
																	}
																}
															}
															case '_' | 0x20:
															{
																switch (str[15] | 0x20)
																{
																	case '1':
																	{
																		idx += 16;
																		return X11_LIGHT_SKY_BLUE_1;
																	}
																	case '2':
																	{
																		idx += 16;
																		return X11_LIGHT_SKY_BLUE_2;
																	}
																	case '3':
																	{
																		idx += 16;
																		return X11_LIGHT_SKY_BLUE_3;
																	}
																	case '4':
																	{
																		idx += 16;
																		return X11_LIGHT_SKY_BLUE_4;
																	}
																}
															}
														}
														idx += 14;
														return X11_LIGHT_SKY_BLUE;
													}
													case 'l':
													{
														//if (!str[8] || strcmp(str[8], !"ATE_", true, 4))
														if (!str[8] || strcmp(str[8], !"ATE", true, 3) || (!_X11_SPACE_CHECK(11) && str[11] != '_'))
														{
															return -1;
														}
														switch (str[12] | 0x20)
														{
															case 'b':
															{
																if (str[13] && !strcmp(str[13], !"LUE", true, 3))
																{
																	idx += 16;
																	return X11_LIGHT_SLATE_BLUE;
																}
															}
															case 'g':
															{
																if (str[13] | 0x20 != 'r')
																{
																	return -1;
																}
																switch (str[14] | 0x20)
																{
																	case 'a':
																	{
																		if (str[15] | 0x20 == 'y')
																		{
																			idx += 16;
																			return X11_LIGHT_SLATE_GRAY;
																		}
																	}
																	case 'e':
																	{
																		if (str[15] | 0x20 == 'y')
																		{
																			idx += 16;
																			return X11_LIGHT_SLATE_GREY;
																		}
																	}
																}
															}
														}
													}
													case 't':
													{
														//if (!str[8] || strcmp(str[8], !"EEL_BLUE", true, 8))
														if (!str[8] || strcmp(str[8], !"EEL", true, 3) || (!_X11_SPACE_CHECK(11) && str[11] != '_') || strcmp(str[12], !"BLUE", true, 4))
														{
															return -1;
														}
														switch (str[16] | 0x20)
														{
															case _X11_SPACE_SWITCH: // ' '
															{
																if (str[16])
																{
																	switch (str[17] | 0x20)
																	{
																		case '1':
																		{
																			idx += 18;
																			return X11_LIGHT_STEEL_BLUE_1;
																		}
																		case '2':
																		{
																			idx += 18;
																			return X11_LIGHT_STEEL_BLUE_2;
																		}
																		case '3':
																		{
																			idx += 18;
																			return X11_LIGHT_STEEL_BLUE_3;
																		}
																		case '4':
																		{
																			idx += 18;
																			return X11_LIGHT_STEEL_BLUE_4;
																		}
																	}
																}
															}
															case '_' | 0x20:
															{
																switch (str[17] | 0x20)
																{
																	case '1':
																	{
																		idx += 18;
																		return X11_LIGHT_STEEL_BLUE_1;
																	}
																	case '2':
																	{
																		idx += 18;
																		return X11_LIGHT_STEEL_BLUE_2;
																	}
																	case '3':
																	{
																		idx += 18;
																		return X11_LIGHT_STEEL_BLUE_3;
																	}
																	case '4':
																	{
																		idx += 18;
																		return X11_LIGHT_STEEL_BLUE_4;
																	}
																}
															}
														}
														idx += 16;
														return X11_LIGHT_STEEL_BLUE;
													}
												}
											}
											case 'y':
											{
												if (!str[7] || strcmp(str[7], !"ELLOW", true, 5))
												{
													return -1;
												}
												switch (str[12] | 0x20)
												{
													case _X11_SPACE_SWITCH: // ' '
													{
														if (str[12])
														{
															switch (str[13] | 0x20)
															{
																case '1':
																{
																	idx += 14;
																	return X11_LIGHT_YELLOW_1;
																}
																case '2':
																{
																	idx += 14;
																	return X11_LIGHT_YELLOW_2;
																}
																case '3':
																{
																	idx += 14;
																	return X11_LIGHT_YELLOW_3;
																}
																case '4':
																{
																	idx += 14;
																	return X11_LIGHT_YELLOW_4;
																}
															}
														}
													}
													case '_' | 0x20:
													{
														switch (str[13] | 0x20)
														{
															case '1':
															{
																idx += 14;
																return X11_LIGHT_YELLOW_1;
															}
															case '2':
															{
																idx += 14;
																return X11_LIGHT_YELLOW_2;
															}
															case '3':
															{
																idx += 14;
																return X11_LIGHT_YELLOW_3;
															}
															case '4':
															{
																idx += 14;
																return X11_LIGHT_YELLOW_4;
															}
														}
													}
												}
												idx += 12;
												return X11_LIGHT_YELLOW;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[6] | 0x20)
									{
										case 'b':
										{
											if (!str[7] || strcmp(str[7], !"LUE", true, 3))
											{
												return -1;
											}
											switch (str[10] | 0x20)
											{
												case _X11_SPACE_SWITCH: // ' '
												{
													if (str[10])
													{
														switch (str[11] | 0x20)
														{
															case '1':
															{
																idx += 12;
																return X11_LIGHT_BLUE_1;
															}
															case '2':
															{
																idx += 12;
																return X11_LIGHT_BLUE_2;
															}
															case '3':
															{
																idx += 12;
																return X11_LIGHT_BLUE_3;
															}
															case '4':
															{
																idx += 12;
																return X11_LIGHT_BLUE_4;
															}
														}
													}
												}
												case '_' | 0x20:
												{
													switch (str[11] | 0x20)
													{
														case '1':
														{
															idx += 12;
															return X11_LIGHT_BLUE_1;
														}
														case '2':
														{
															idx += 12;
															return X11_LIGHT_BLUE_2;
														}
														case '3':
														{
															idx += 12;
															return X11_LIGHT_BLUE_3;
														}
														case '4':
														{
															idx += 12;
															return X11_LIGHT_BLUE_4;
														}
													}
												}
											}
											idx += 10;
											return X11_LIGHT_BLUE;
										}
										case 'c':
										{
											switch (str[7] | 0x20)
											{
												case 'o':
												{
													if (str[8] && !strcmp(str[8], !"RAL", true, 3))
													{
														idx += 11;
														return X11_LIGHT_CORAL;
													}
												}
												case 'y':
												{
													if (!str[8] || strcmp(str[8], !"AN", true, 2))
													{
														return -1;
													}
													switch (str[10] | 0x20)
													{
														case _X11_SPACE_SWITCH: // ' '
														{
															if (str[10])
															{
																switch (str[11] | 0x20)
																{
																	case '1':
																	{
																		idx += 12;
																		return X11_LIGHT_CYAN_1;
																	}
																	case '2':
																	{
																		idx += 12;
																		return X11_LIGHT_CYAN_2;
																	}
																	case '3':
																	{
																		idx += 12;
																		return X11_LIGHT_CYAN_3;
																	}
																	case '4':
																	{
																		idx += 12;
																		return X11_LIGHT_CYAN_4;
																	}
																}
															}
														}
														case '_' | 0x20:
														{
															switch (str[11] | 0x20)
															{
																case '1':
																{
																	idx += 12;
																	return X11_LIGHT_CYAN_1;
																}
																case '2':
																{
																	idx += 12;
																	return X11_LIGHT_CYAN_2;
																}
																case '3':
																{
																	idx += 12;
																	return X11_LIGHT_CYAN_3;
																}
																case '4':
																{
																	idx += 12;
																	return X11_LIGHT_CYAN_4;
																}
															}
														}
													}
													idx += 10;
													return X11_LIGHT_CYAN;
												}
											}
										}
										case 'g':
										{
											switch (str[7] | 0x20)
											{
												case 'o':
												{
													if (!str[8] || strcmp(str[8], !"LDENROD", true, 7))
													{
														return -1;
													}
													switch (str[15] | 0x20)
													{
														case _X11_SPACE_SWITCH: // ' '
														{
															if (str[15])
															{
																switch (str[16] | 0x20)
																{
																	case '1':
																	{
																		idx += 17;
																		return X11_LIGHT_GOLDENROD_1;
																	}
																	case '2':
																	{
																		idx += 17;
																		return X11_LIGHT_GOLDENROD_2;
																	}
																	case '3':
																	{
																		idx += 17;
																		return X11_LIGHT_GOLDENROD_3;
																	}
																	case '4':
																	{
																		idx += 17;
																		return X11_LIGHT_GOLDENROD_4;
																	}
																	case 'y':
																	{
																		if (str[17] && !strcmp(str[17], !"ELLOW", true, 5))
																		{
																			idx += 22;
																			return X11_LIGHT_GOLDENROD_YELLOW;
																		}
																	}
																}
															}
														}
														case '_' | 0x20:
														{
															switch (str[16] | 0x20)
															{
																case '1':
																{
																	idx += 17;
																	return X11_LIGHT_GOLDENROD_1;
																}
																case '2':
																{
																	idx += 17;
																	return X11_LIGHT_GOLDENROD_2;
																}
																case '3':
																{
																	idx += 17;
																	return X11_LIGHT_GOLDENROD_3;
																}
																case '4':
																{
																	idx += 17;
																	return X11_LIGHT_GOLDENROD_4;
																}
																case 'y':
																{
																	if (str[17] && !strcmp(str[17], !"ELLOW", true, 5))
																	{
																		idx += 22;
																		return X11_LIGHT_GOLDENROD_YELLOW;
																	}
																}
															}
														}
													}
													idx += 15;
													return X11_LIGHT_GOLDENROD;
												}
												case 'r':
												{
													switch (str[8] | 0x20)
													{
														case 'a':
														{
															if (str[9] | 0x20 == 'y')
															{
																idx += 10;
																return X11_LIGHT_GRAY;
															}
														}
														case 'e':
														{
															switch (str[9] | 0x20)
															{
																case 'e':
																{
																	if (str[10] | 0x20 == 'n')
																	{
																		idx += 11;
																		return X11_LIGHT_GREEN;
																	}
																}
																case 'y':
																{
																	idx += 10;
																	return X11_LIGHT_GREY;
																}
															}
														}
													}
												}
											}
										}
										case 'p':
										{
											if (!str[7] || strcmp(str[7], !"INK", true, 3))
											{
												return -1;
											}
											switch (str[10] | 0x20)
											{
												case _X11_SPACE_SWITCH: // ' '
												{
													if (str[10])
													{
														switch (str[11] | 0x20)
														{
															case '1':
															{
																idx += 12;
																return X11_LIGHT_PINK_1;
															}
															case '2':
															{
																idx += 12;
																return X11_LIGHT_PINK_2;
															}
															case '3':
															{
																idx += 12;
																return X11_LIGHT_PINK_3;
															}
															case '4':
															{
																idx += 12;
																return X11_LIGHT_PINK_4;
															}
														}
													}
												}
												case '_' | 0x20:
												{
													switch (str[11] | 0x20)
													{
														case '1':
														{
															idx += 12;
															return X11_LIGHT_PINK_1;
														}
														case '2':
														{
															idx += 12;
															return X11_LIGHT_PINK_2;
														}
														case '3':
														{
															idx += 12;
															return X11_LIGHT_PINK_3;
														}
														case '4':
														{
															idx += 12;
															return X11_LIGHT_PINK_4;
														}
													}
												}
											}
											idx += 10;
											return X11_LIGHT_PINK;
										}
										case 's':
										{
											switch (str[7] | 0x20)
											{
												case 'a':
												{
													if (!str[8] || strcmp(str[8], !"LMON", true, 4))
													{
														return -1;
													}
													switch (str[12] | 0x20)
													{
														case _X11_SPACE_SWITCH: // ' '
														{
															if (str[12])
															{
																switch (str[13] | 0x20)
																{
																	case '1':
																	{
																		idx += 14;
																		return X11_LIGHT_SALMON_1;
																	}
																	case '2':
																	{
																		idx += 14;
																		return X11_LIGHT_SALMON_2;
																	}
																	case '3':
																	{
																		idx += 14;
																		return X11_LIGHT_SALMON_3;
																	}
																	case '4':
																	{
																		idx += 14;
																		return X11_LIGHT_SALMON_4;
																	}
																}
															}
														}
														case '_' | 0x20:
														{
															switch (str[13] | 0x20)
															{
																case '1':
																{
																	idx += 14;
																	return X11_LIGHT_SALMON_1;
																}
																case '2':
																{
																	idx += 14;
																	return X11_LIGHT_SALMON_2;
																}
																case '3':
																{
																	idx += 14;
																	return X11_LIGHT_SALMON_3;
																}
																case '4':
																{
																	idx += 14;
																	return X11_LIGHT_SALMON_4;
																}
															}
														}
													}
													idx += 12;
													return X11_LIGHT_SALMON;
												}
												case 'e':
												{
													//if (str[8] && !strcmp(str[8], !"A_GREEN", true, 7))
													if (str[8] | 0x20 == 'a' && (_X11_SPACE_CHECK(9) || str[9] == '_') && !strcmp(str[10], !"GREEN", true, 5))
													{
														idx += 15;
														return X11_LIGHT_SEA_GREEN;
													}
												}
												case 'k':
												{
													//if (!str[8] || strcmp(str[8], !"Y_BLUE", true, 6))
													if (str[8] | 0x20 != 'y' || (!_X11_SPACE_CHECK(9) && str[9] != '_') || strcmp(str[10], !"BLUE", true, 4))
													{
														return -1;
													}
													switch (str[14] | 0x20)
													{
														case _X11_SPACE_SWITCH: // ' '
														{
															if (str[14])
															{
																switch (str[15] | 0x20)
																{
																	case '1':
																	{
																		idx += 16;
																		return X11_LIGHT_SKY_BLUE_1;
																	}
																	case '2':
																	{
																		idx += 16;
																		return X11_LIGHT_SKY_BLUE_2;
																	}
																	case '3':
																	{
																		idx += 16;
																		return X11_LIGHT_SKY_BLUE_3;
																	}
																	case '4':
																	{
																		idx += 16;
																		return X11_LIGHT_SKY_BLUE_4;
																	}
																}
															}
														}
														case '_' | 0x20:
														{
															switch (str[15] | 0x20)
															{
																case '1':
																{
																	idx += 16;
																	return X11_LIGHT_SKY_BLUE_1;
																}
																case '2':
																{
																	idx += 16;
																	return X11_LIGHT_SKY_BLUE_2;
																}
																case '3':
																{
																	idx += 16;
																	return X11_LIGHT_SKY_BLUE_3;
																}
																case '4':
																{
																	idx += 16;
																	return X11_LIGHT_SKY_BLUE_4;
																}
															}
														}
													}
													idx += 14;
													return X11_LIGHT_SKY_BLUE;
												}
												case 'l':
												{
													//if (!str[8] || strcmp(str[8], !"ATE_", true, 4))
													if (!str[8] || strcmp(str[8], !"ATE", true, 3) || (!_X11_SPACE_CHECK(11) && str[11] != '_'))
													{
														return -1;
													}
													switch (str[12] | 0x20)
													{
														case 'b':
														{
															if (str[13] && !strcmp(str[13], !"LUE", true, 3))
															{
																idx += 16;
																return X11_LIGHT_SLATE_BLUE;
															}
														}
														case 'g':
														{
															if (str[13] | 0x20 != 'r')
															{
																return -1;
															}
															switch (str[14] | 0x20)
															{
																case 'a':
																{
																	if (str[15] | 0x20 == 'y')
																	{
																		idx += 16;
																		return X11_LIGHT_SLATE_GRAY;
																	}
																}
																case 'e':
																{
																	if (str[15] | 0x20 == 'y')
																	{
																		idx += 16;
																		return X11_LIGHT_SLATE_GREY;
																	}
																}
															}
														}
													}
												}
												case 't':
												{
													//if (!str[8] || strcmp(str[8], !"EEL_BLUE", true, 8))
													if (!str[8] || strcmp(str[8], !"EEL", true, 3) || (!_X11_SPACE_CHECK(11) && str[11] != '_') || strcmp(str[12], !"BLUE", true, 4))
													{
														return -1;
													}
													switch (str[16] | 0x20)
													{
														case _X11_SPACE_SWITCH: // ' '
														{
															if (str[16])
															{
																switch (str[17] | 0x20)
																{
																	case '1':
																	{
																		idx += 18;
																		return X11_LIGHT_STEEL_BLUE_1;
																	}
																	case '2':
																	{
																		idx += 18;
																		return X11_LIGHT_STEEL_BLUE_2;
																	}
																	case '3':
																	{
																		idx += 18;
																		return X11_LIGHT_STEEL_BLUE_3;
																	}
																	case '4':
																	{
																		idx += 18;
																		return X11_LIGHT_STEEL_BLUE_4;
																	}
																}
															}
														}
														case '_' | 0x20:
														{
															switch (str[17] | 0x20)
															{
																case '1':
																{
																	idx += 18;
																	return X11_LIGHT_STEEL_BLUE_1;
																}
																case '2':
																{
																	idx += 18;
																	return X11_LIGHT_STEEL_BLUE_2;
																}
																case '3':
																{
																	idx += 18;
																	return X11_LIGHT_STEEL_BLUE_3;
																}
																case '4':
																{
																	idx += 18;
																	return X11_LIGHT_STEEL_BLUE_4;
																}
															}
														}
													}
													idx += 16;
													return X11_LIGHT_STEEL_BLUE;
												}
											}
										}
										case 'y':
										{
											if (!str[7] || strcmp(str[7], !"ELLOW", true, 5))
											{
												return -1;
											}
											switch (str[12] | 0x20)
											{
												case _X11_SPACE_SWITCH: // ' '
												{
													if (str[12])
													{
														switch (str[13] | 0x20)
														{
															case '1':
															{
																idx += 14;
																return X11_LIGHT_YELLOW_1;
															}
															case '2':
															{
																idx += 14;
																return X11_LIGHT_YELLOW_2;
															}
															case '3':
															{
																idx += 14;
																return X11_LIGHT_YELLOW_3;
															}
															case '4':
															{
																idx += 14;
																return X11_LIGHT_YELLOW_4;
															}
														}
													}
												}
												case '_' | 0x20:
												{
													switch (str[13] | 0x20)
													{
														case '1':
														{
															idx += 14;
															return X11_LIGHT_YELLOW_1;
														}
														case '2':
														{
															idx += 14;
															return X11_LIGHT_YELLOW_2;
														}
														case '3':
														{
															idx += 14;
															return X11_LIGHT_YELLOW_3;
														}
														case '4':
														{
															idx += 14;
															return X11_LIGHT_YELLOW_4;
														}
													}
												}
											}
											idx += 12;
											return X11_LIGHT_YELLOW;
										}
									}
								}
								case 'b':
								{
									if (!str[6] || strcmp(str[6], !"LUE", true, 3))
									{
										return -1;
									}
									switch (str[9] | 0x20)
									{
										case '1':
										{
											idx += 10;
											return X11_LIGHTBLUE1;
										}
										case '2':
										{
											idx += 10;
											return X11_LIGHTBLUE2;
										}
										case '3':
										{
											idx += 10;
											return X11_LIGHTBLUE3;
										}
										case '4':
										{
											idx += 10;
											return X11_LIGHTBLUE4;
										}
									}
									idx += 9;
									return X11_LIGHTBLUE;
								}
								case 'c':
								{
									switch (str[6] | 0x20)
									{
										case 'o':
										{
											if (str[7] && !strcmp(str[7], !"RAL", true, 3))
											{
												idx += 10;
												return X11_LIGHTCORAL;
											}
										}
										case 'y':
										{
											if (!str[7] || strcmp(str[7], !"AN", true, 2))
											{
												return -1;
											}
											switch (str[9] | 0x20)
											{
												case '1':
												{
													idx += 10;
													return X11_LIGHTCYAN1;
												}
												case '2':
												{
													idx += 10;
													return X11_LIGHTCYAN2;
												}
												case '3':
												{
													idx += 10;
													return X11_LIGHTCYAN3;
												}
												case '4':
												{
													idx += 10;
													return X11_LIGHTCYAN4;
												}
											}
											idx += 9;
											return X11_LIGHTCYAN;
										}
									}
								}
								case 'g':
								{
									switch (str[6] | 0x20)
									{
										case 'o':
										{
											if (!str[7] || strcmp(str[7], !"LDENROD", true, 7))
											{
												return -1;
											}
											switch (str[14] | 0x20)
											{
												case '1':
												{
													idx += 15;
													return X11_LIGHTGOLDENROD1;
												}
												case '2':
												{
													idx += 15;
													return X11_LIGHTGOLDENROD2;
												}
												case '3':
												{
													idx += 15;
													return X11_LIGHTGOLDENROD3;
												}
												case '4':
												{
													idx += 15;
													return X11_LIGHTGOLDENROD4;
												}
												case 'y':
												{
													if (str[15] && !strcmp(str[15], !"ELLOW", true, 5))
													{
														idx += 20;
														return X11_LIGHTGOLDENRODYELLOW;
													}
												}
											}
											idx += 14;
											return X11_LIGHTGOLDENROD;
										}
										case 'r':
										{
											switch (str[7] | 0x20)
											{
												case 'a':
												{
													if (str[8] | 0x20 == 'y')
													{
														idx += 9;
														return X11_LIGHTGRAY;
													}
												}
												case 'e':
												{
													switch (str[8] | 0x20)
													{
														case 'e':
														{
															if (str[9] | 0x20 == 'n')
															{
																idx += 10;
																return X11_LIGHTGREEN;
															}
														}
														case 'y':
														{
															idx += 9;
															return X11_LIGHTGREY;
														}
													}
												}
											}
										}
									}
								}
								case 'p':
								{
									if (!str[6] || strcmp(str[6], !"INK", true, 3))
									{
										return -1;
									}
									switch (str[9] | 0x20)
									{
										case '1':
										{
											idx += 10;
											return X11_LIGHTPINK1;
										}
										case '2':
										{
											idx += 10;
											return X11_LIGHTPINK2;
										}
										case '3':
										{
											idx += 10;
											return X11_LIGHTPINK3;
										}
										case '4':
										{
											idx += 10;
											return X11_LIGHTPINK4;
										}
									}
									idx += 9;
									return X11_LIGHTPINK;
								}
								case 's':
								{
									switch (str[6] | 0x20)
									{
										case 'a':
										{
											if (!str[7] || strcmp(str[7], !"LMON", true, 4))
											{
												return -1;
											}
											switch (str[11] | 0x20)
											{
												case '1':
												{
													idx += 12;
													return X11_LIGHTSALMON1;
												}
												case '2':
												{
													idx += 12;
													return X11_LIGHTSALMON2;
												}
												case '3':
												{
													idx += 12;
													return X11_LIGHTSALMON3;
												}
												case '4':
												{
													idx += 12;
													return X11_LIGHTSALMON4;
												}
											}
											idx += 11;
											return X11_LIGHTSALMON;
										}
										case 'e':
										{
											if (str[7] && !strcmp(str[7], !"AGREEN", true, 6))
											{
												idx += 13;
												return X11_LIGHTSEAGREEN;
											}
										}
										case 'k':
										{
											if (!str[7] || strcmp(str[7], !"YBLUE", true, 5))
											{
												return -1;
											}
											switch (str[12] | 0x20)
											{
												case '1':
												{
													idx += 13;
													return X11_LIGHTSKYBLUE1;
												}
												case '2':
												{
													idx += 13;
													return X11_LIGHTSKYBLUE2;
												}
												case '3':
												{
													idx += 13;
													return X11_LIGHTSKYBLUE3;
												}
												case '4':
												{
													idx += 13;
													return X11_LIGHTSKYBLUE4;
												}
											}
											idx += 12;
											return X11_LIGHTSKYBLUE;
										}
										case 'l':
										{
											if (!str[7] || strcmp(str[7], !"ATE", true, 3))
											{
												return -1;
											}
											switch (str[10] | 0x20)
											{
												case 'b':
												{
													if (str[11] && !strcmp(str[11], !"LUE", true, 3))
													{
														idx += 14;
														return X11_LIGHTSLATEBLUE;
													}
												}
												case 'g':
												{
													if (str[11] | 0x20 != 'r')
													{
														return -1;
													}
													switch (str[12] | 0x20)
													{
														case 'a':
														{
															if (str[13] | 0x20 == 'y')
															{
																idx += 14;
																return X11_LIGHTSLATEGRAY;
															}
														}
														case 'e':
														{
															if (str[13] | 0x20 == 'y')
															{
																idx += 14;
																return X11_LIGHTSLATEGREY;
															}
														}
													}
												}
											}
										}
										case 't':
										{
											if (!str[7] || strcmp(str[7], !"EELBLUE", true, 7))
											{
												return -1;
											}
											switch (str[14] | 0x20)
											{
												case '1':
												{
													idx += 15;
													return X11_LIGHTSTEELBLUE1;
												}
												case '2':
												{
													idx += 15;
													return X11_LIGHTSTEELBLUE2;
												}
												case '3':
												{
													idx += 15;
													return X11_LIGHTSTEELBLUE3;
												}
												case '4':
												{
													idx += 15;
													return X11_LIGHTSTEELBLUE4;
												}
											}
											idx += 14;
											return X11_LIGHTSTEELBLUE;
										}
									}
								}
								case 'y':
								{
									if (!str[6] || strcmp(str[6], !"ELLOW", true, 5))
									{
										return -1;
									}
									switch (str[11] | 0x20)
									{
										case '1':
										{
											idx += 12;
											return X11_LIGHTYELLOW1;
										}
										case '2':
										{
											idx += 12;
											return X11_LIGHTYELLOW2;
										}
										case '3':
										{
											idx += 12;
											return X11_LIGHTYELLOW3;
										}
										case '4':
										{
											idx += 12;
											return X11_LIGHTYELLOW4;
										}
									}
									idx += 11;
									return X11_LIGHTYELLOW;
								}
							}
						}
						case 'm':
						{
							if (str[3] | 0x20 != 'e')
							{
								return -1;
							}
							switch (str[4] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[4])
									{
										if (str[5] && !strcmp(str[5], !"GREEN", true, 5))
										{
											idx += 10;
											return X11_LIME_GREEN;
										}
									}
								}
								case '_' | 0x20:
								{
									if (str[5] && !strcmp(str[5], !"GREEN", true, 5))
									{
										idx += 10;
										return X11_LIME_GREEN;
									}
								}
								case 'g':
								{
									if (str[5] && !strcmp(str[5], !"REEN", true, 4))
									{
										idx += 9;
										return X11_LIMEGREEN;
									}
								}
							}
						}
						case 'n':
						{
							if (str[3] && !strcmp(str[3], !"EN", true, 2))
							{
								idx += 5;
								return X11_LINEN;
							}
						}
					}
				}
			}
		}
		case 'm':
		{
			switch (str[1] | 0x20)
			{
				case 'a':
				{
					switch (str[2] | 0x20)
					{
						case 'g':
						{
							if (!str[3] || strcmp(str[3], !"ENTA", true, 4))
							{
								return -1;
							}
							switch (str[7] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[7])
									{
										switch (str[8] | 0x20)
										{
											case '1':
											{
												idx += 9;
												return X11_MAGENTA_1;
											}
											case '2':
											{
												idx += 9;
												return X11_MAGENTA_2;
											}
											case '3':
											{
												idx += 9;
												return X11_MAGENTA_3;
											}
											case '4':
											{
												idx += 9;
												return X11_MAGENTA_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[8] | 0x20)
									{
										case '1':
										{
											idx += 9;
											return X11_MAGENTA_1;
										}
										case '2':
										{
											idx += 9;
											return X11_MAGENTA_2;
										}
										case '3':
										{
											idx += 9;
											return X11_MAGENTA_3;
										}
										case '4':
										{
											idx += 9;
											return X11_MAGENTA_4;
										}
									}
								}
								case '1':
								{
									idx += 8;
									return X11_MAGENTA1;
								}
								case '2':
								{
									idx += 8;
									return X11_MAGENTA2;
								}
								case '3':
								{
									idx += 8;
									return X11_MAGENTA3;
								}
								case '4':
								{
									idx += 8;
									return X11_MAGENTA4;
								}
							}
							idx += 7;
							return X11_MAGENTA;
						}
						case 'r':
						{
							if (!str[3] || strcmp(str[3], !"OON", true, 3))
							{
								return -1;
							}
							switch (str[6] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[6])
									{
										switch (str[7] | 0x20)
										{
											case '1':
											{
												idx += 8;
												return X11_MAROON_1;
											}
											case '2':
											{
												idx += 8;
												return X11_MAROON_2;
											}
											case '3':
											{
												idx += 8;
												return X11_MAROON_3;
											}
											case '4':
											{
												idx += 8;
												return X11_MAROON_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[7] | 0x20)
									{
										case '1':
										{
											idx += 8;
											return X11_MAROON_1;
										}
										case '2':
										{
											idx += 8;
											return X11_MAROON_2;
										}
										case '3':
										{
											idx += 8;
											return X11_MAROON_3;
										}
										case '4':
										{
											idx += 8;
											return X11_MAROON_4;
										}
									}
								}
								case '1':
								{
									idx += 7;
									return X11_MAROON1;
								}
								case '2':
								{
									idx += 7;
									return X11_MAROON2;
								}
								case '3':
								{
									idx += 7;
									return X11_MAROON3;
								}
								case '4':
								{
									idx += 7;
									return X11_MAROON4;
								}
							}
							idx += 6;
							return X11_MAROON;
						}
					}
				}
				case 'e':
				{
					if (!str[2] || strcmp(str[2], !"DIUM", true, 4))
					{
						return -1;
					}
					switch (str[6] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[6])
							{
								switch (str[7] | 0x20)
								{
									case 'a':
									{
										if (str[8] && !strcmp(str[8], !"QUAMARINE", true, 9))
										{
											idx += 17;
											return X11_MEDIUM_AQUAMARINE;
										}
									}
									case 'b':
									{
										if (str[8] && !strcmp(str[8], !"LUE", true, 3))
										{
											idx += 11;
											return X11_MEDIUM_BLUE;
										}
									}
									case 'o':
									{
										if (!str[8] || strcmp(str[8], !"RCHID", true, 5))
										{
											return -1;
										}
										switch (str[13] | 0x20)
										{
											case _X11_SPACE_SWITCH: // ' '
											{
												if (str[13])
												{
													switch (str[14] | 0x20)
													{
														case '1':
														{
															idx += 15;
															return X11_MEDIUM_ORCHID_1;
														}
														case '2':
														{
															idx += 15;
															return X11_MEDIUM_ORCHID_2;
														}
														case '3':
														{
															idx += 15;
															return X11_MEDIUM_ORCHID_3;
														}
														case '4':
														{
															idx += 15;
															return X11_MEDIUM_ORCHID_4;
														}
													}
												}
											}
											case '_' | 0x20:
											{
												switch (str[14] | 0x20)
												{
													case '1':
													{
														idx += 15;
														return X11_MEDIUM_ORCHID_1;
													}
													case '2':
													{
														idx += 15;
														return X11_MEDIUM_ORCHID_2;
													}
													case '3':
													{
														idx += 15;
														return X11_MEDIUM_ORCHID_3;
													}
													case '4':
													{
														idx += 15;
														return X11_MEDIUM_ORCHID_4;
													}
												}
											}
										}
										idx += 13;
										return X11_MEDIUM_ORCHID;
									}
									case 'p':
									{
										if (!str[8] || strcmp(str[8], !"URPLE", true, 5))
										{
											return -1;
										}
										switch (str[13] | 0x20)
										{
											case _X11_SPACE_SWITCH: // ' '
											{
												if (str[13])
												{
													switch (str[14] | 0x20)
													{
														case '1':
														{
															idx += 15;
															return X11_MEDIUM_PURPLE_1;
														}
														case '2':
														{
															idx += 15;
															return X11_MEDIUM_PURPLE_2;
														}
														case '3':
														{
															idx += 15;
															return X11_MEDIUM_PURPLE_3;
														}
														case '4':
														{
															idx += 15;
															return X11_MEDIUM_PURPLE_4;
														}
													}
												}
											}
											case '_' | 0x20:
											{
												switch (str[14] | 0x20)
												{
													case '1':
													{
														idx += 15;
														return X11_MEDIUM_PURPLE_1;
													}
													case '2':
													{
														idx += 15;
														return X11_MEDIUM_PURPLE_2;
													}
													case '3':
													{
														idx += 15;
														return X11_MEDIUM_PURPLE_3;
													}
													case '4':
													{
														idx += 15;
														return X11_MEDIUM_PURPLE_4;
													}
												}
											}
										}
										idx += 13;
										return X11_MEDIUM_PURPLE;
									}
									case 's':
									{
										switch (str[8] | 0x20)
										{
											case 'e':
											{
												//if (str[9] && !strcmp(str[9], !"A_GREEN", true, 7))
												if (str[9] | 0x20 == 'a' && (_X11_SPACE_CHECK(10) || str[10] == '_') && !strcmp(str[11], !"GREEN", true, 5))
												{
													idx += 16;
													return X11_MEDIUM_SEA_GREEN;
												}
											}
											case 'l':
											{
												//if (str[9] && !strcmp(str[9], !"ATE_BLUE", true, 8))
												if (str[9] && !strcmp(str[9], !"ATE", true, 3) && (_X11_SPACE_CHECK(12) || str[12] == '_') && !strcmp(str[13], !"BLUE", true, 4))
												{
													idx += 17;
													return X11_MEDIUM_SLATE_BLUE;
												}
											}
											case 'p':
											{
												//if (str[9] && !strcmp(str[9], !"RING_GREEN", true, 10))
												if (str[9] && !strcmp(str[9], !"RING", true, 4) && (_X11_SPACE_CHECK(13) || str[13] == '_') && !strcmp(str[14], !"GREEN", true, 5))
												{
													idx += 19;
													return X11_MEDIUM_SPRING_GREEN;
												}
											}
										}
									}
									case 't':
									{
										if (str[8] && !strcmp(str[8], !"URQUOISE", true, 8))
										{
											idx += 16;
											return X11_MEDIUM_TURQUOISE;
										}
									}
									case 'v':
									{
										//if (str[8] && !strcmp(str[8], !"IOLET_RED", true, 9))
										if (str[8] && !strcmp(str[8], !"IOLET", true, 5) && (_X11_SPACE_CHECK(13) || str[13] == '_') && !strcmp(str[14], !"RED", true, 3))
										{
											idx += 17;
											return X11_MEDIUM_VIOLET_RED;
										}
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[7] | 0x20)
							{
								case 'a':
								{
									if (str[8] && !strcmp(str[8], !"QUAMARINE", true, 9))
									{
										idx += 17;
										return X11_MEDIUM_AQUAMARINE;
									}
								}
								case 'b':
								{
									if (str[8] && !strcmp(str[8], !"LUE", true, 3))
									{
										idx += 11;
										return X11_MEDIUM_BLUE;
									}
								}
								case 'o':
								{
									if (!str[8] || strcmp(str[8], !"RCHID", true, 5))
									{
										return -1;
									}
									switch (str[13] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[13])
											{
												switch (str[14] | 0x20)
												{
													case '1':
													{
														idx += 15;
														return X11_MEDIUM_ORCHID_1;
													}
													case '2':
													{
														idx += 15;
														return X11_MEDIUM_ORCHID_2;
													}
													case '3':
													{
														idx += 15;
														return X11_MEDIUM_ORCHID_3;
													}
													case '4':
													{
														idx += 15;
														return X11_MEDIUM_ORCHID_4;
													}
												}
											}
										}
										case '_' | 0x20:
										{
											switch (str[14] | 0x20)
											{
												case '1':
												{
													idx += 15;
													return X11_MEDIUM_ORCHID_1;
												}
												case '2':
												{
													idx += 15;
													return X11_MEDIUM_ORCHID_2;
												}
												case '3':
												{
													idx += 15;
													return X11_MEDIUM_ORCHID_3;
												}
												case '4':
												{
													idx += 15;
													return X11_MEDIUM_ORCHID_4;
												}
											}
										}
									}
									idx += 13;
									return X11_MEDIUM_ORCHID;
								}
								case 'p':
								{
									if (!str[8] || strcmp(str[8], !"URPLE", true, 5))
									{
										return -1;
									}
									switch (str[13] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[13])
											{
												switch (str[14] | 0x20)
												{
													case '1':
													{
														idx += 15;
														return X11_MEDIUM_PURPLE_1;
													}
													case '2':
													{
														idx += 15;
														return X11_MEDIUM_PURPLE_2;
													}
													case '3':
													{
														idx += 15;
														return X11_MEDIUM_PURPLE_3;
													}
													case '4':
													{
														idx += 15;
														return X11_MEDIUM_PURPLE_4;
													}
												}
											}
										}
										case '_' | 0x20:
										{
											switch (str[14] | 0x20)
											{
												case '1':
												{
													idx += 15;
													return X11_MEDIUM_PURPLE_1;
												}
												case '2':
												{
													idx += 15;
													return X11_MEDIUM_PURPLE_2;
												}
												case '3':
												{
													idx += 15;
													return X11_MEDIUM_PURPLE_3;
												}
												case '4':
												{
													idx += 15;
													return X11_MEDIUM_PURPLE_4;
												}
											}
										}
									}
									idx += 13;
									return X11_MEDIUM_PURPLE;
								}
								case 's':
								{
									switch (str[8] | 0x20)
									{
										case 'e':
										{
											//if (str[9] && !strcmp(str[9], !"A_GREEN", true, 7))
											if (str[9] | 0x20 == 'a' && (_X11_SPACE_CHECK(10) || str[10] == '_') && !strcmp(str[11], !"GREEN", true, 5))
											{
												idx += 16;
												return X11_MEDIUM_SEA_GREEN;
											}
										}
										case 'l':
										{
											//if (str[9] && !strcmp(str[9], !"ATE_BLUE", true, 8))
											if (str[9] && !strcmp(str[9], !"ATE", true, 3) && (_X11_SPACE_CHECK(12) || str[12] == '_') && !strcmp(str[13], !"BLUE", true, 4))
											{
												idx += 17;
												return X11_MEDIUM_SLATE_BLUE;
											}
										}
										case 'p':
										{
											//if (str[9] && !strcmp(str[9], !"RING_GREEN", true, 10))
											if (str[9] && !strcmp(str[9], !"RING", true, 4) && (_X11_SPACE_CHECK(13) || str[13] == '_') && !strcmp(str[14], !"GREEN", true, 5))
											{
												idx += 19;
												return X11_MEDIUM_SPRING_GREEN;
											}
										}
									}
								}
								case 't':
								{
									if (str[8] && !strcmp(str[8], !"URQUOISE", true, 8))
									{
										idx += 16;
										return X11_MEDIUM_TURQUOISE;
									}
								}
								case 'v':
								{
									if (str[8] && !strcmp(str[8], !"IOLET", true, 5) && (_X11_SPACE_CHECK(13) || str[13] == '_') && !strcmp(str[14], !"RED", true, 3))
									//if (str[8] && !strcmp(str[8], !"IOLET_RED", true, 9))
									{
										idx += 17;
										return X11_MEDIUM_VIOLET_RED;
									}
								}
							}
						}
						case 'a':
						{
							if (str[7] && !strcmp(str[7], !"QUAMARINE", true, 9))
							{
								idx += 16;
								return X11_MEDIUMAQUAMARINE;
							}
						}
						case 'b':
						{
							if (str[7] && !strcmp(str[7], !"LUE", true, 3))
							{
								idx += 10;
								return X11_MEDIUMBLUE;
							}
						}
						case 'o':
						{
							if (!str[7] || strcmp(str[7], !"RCHID", true, 5))
							{
								return -1;
							}
							switch (str[12] | 0x20)
							{
								case '1':
								{
									idx += 13;
									return X11_MEDIUMORCHID1;
								}
								case '2':
								{
									idx += 13;
									return X11_MEDIUMORCHID2;
								}
								case '3':
								{
									idx += 13;
									return X11_MEDIUMORCHID3;
								}
								case '4':
								{
									idx += 13;
									return X11_MEDIUMORCHID4;
								}
							}
							idx += 12;
							return X11_MEDIUMORCHID;
						}
						case 'p':
						{
							if (!str[7] || strcmp(str[7], !"URPLE", true, 5))
							{
								return -1;
							}
							switch (str[12] | 0x20)
							{
								case '1':
								{
									idx += 13;
									return X11_MEDIUMPURPLE1;
								}
								case '2':
								{
									idx += 13;
									return X11_MEDIUMPURPLE2;
								}
								case '3':
								{
									idx += 13;
									return X11_MEDIUMPURPLE3;
								}
								case '4':
								{
									idx += 13;
									return X11_MEDIUMPURPLE4;
								}
							}
							idx += 12;
							return X11_MEDIUMPURPLE;
						}
						case 's':
						{
							switch (str[7] | 0x20)
							{
								case 'e':
								{
									if (str[8] && !strcmp(str[8], !"AGREEN", true, 6))
									{
										idx += 14;
										return X11_MEDIUMSEAGREEN;
									}
								}
								case 'l':
								{
									if (str[8] && !strcmp(str[8], !"ATEBLUE", true, 7))
									{
										idx += 15;
										return X11_MEDIUMSLATEBLUE;
									}
								}
								case 'p':
								{
									if (str[8] && !strcmp(str[8], !"RINGGREEN", true, 9))
									{
										idx += 17;
										return X11_MEDIUMSPRINGGREEN;
									}
								}
							}
						}
						case 't':
						{
							if (str[7] && !strcmp(str[7], !"URQUOISE", true, 8))
							{
								idx += 15;
								return X11_MEDIUMTURQUOISE;
							}
						}
						case 'v':
						{
							if (str[7] && !strcmp(str[7], !"IOLETRED", true, 8))
							{
								idx += 15;
								return X11_MEDIUMVIOLETRED;
							}
						}
					}
				}
				case 'i':
				{
					switch (str[2] | 0x20)
					{
						case 'd':
						{
							if (!str[3] || strcmp(str[3], !"NIGHT", true, 5))
							{
								return -1;
							}
							switch (str[8] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[8])
									{
										if (str[9] && !strcmp(str[9], !"BLUE", true, 4))
										{
											idx += 13;
											return X11_MIDNIGHT_BLUE;
										}
									}
								}
								case '_' | 0x20:
								{
									if (str[9] && !strcmp(str[9], !"BLUE", true, 4))
									{
										idx += 13;
										return X11_MIDNIGHT_BLUE;
									}
								}
								case 'b':
								{
									if (str[9] && !strcmp(str[9], !"LUE", true, 3))
									{
										idx += 12;
										return X11_MIDNIGHTBLUE;
									}
								}
							}
						}
						case 'n':
						{
							if (str[3] | 0x20 != 't')
							{
								return -1;
							}
							switch (str[4] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[4])
									{
										if (str[5] && !strcmp(str[5], !"CREAM", true, 5))
										{
											idx += 10;
											return X11_MINT_CREAM;
										}
									}
								}
								case '_' | 0x20:
								{
									if (str[5] && !strcmp(str[5], !"CREAM", true, 5))
									{
										idx += 10;
										return X11_MINT_CREAM;
									}
								}
								case 'c':
								{
									if (str[5] && !strcmp(str[5], !"REAM", true, 4))
									{
										idx += 9;
										return X11_MINTCREAM;
									}
								}
							}
						}
						case 's':
						{
							if (!str[3] || strcmp(str[3], !"TY", true, 2))
							{
								return -1;
							}
							switch (str[5] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[5])
									{
										if (!str[6] || strcmp(str[6], !"ROSE", true, 4))
										{
											return -1;
										}
										switch (str[10] | 0x20)
										{
											case _X11_SPACE_SWITCH: // ' '
											{
												if (str[10])
												{
													switch (str[11] | 0x20)
													{
														case '1':
														{
															idx += 12;
															return X11_MISTY_ROSE_1;
														}
														case '2':
														{
															idx += 12;
															return X11_MISTY_ROSE_2;
														}
														case '3':
														{
															idx += 12;
															return X11_MISTY_ROSE_3;
														}
														case '4':
														{
															idx += 12;
															return X11_MISTY_ROSE_4;
														}
													}
												}
											}
											case '_' | 0x20:
											{
												switch (str[11] | 0x20)
												{
													case '1':
													{
														idx += 12;
														return X11_MISTY_ROSE_1;
													}
													case '2':
													{
														idx += 12;
														return X11_MISTY_ROSE_2;
													}
													case '3':
													{
														idx += 12;
														return X11_MISTY_ROSE_3;
													}
													case '4':
													{
														idx += 12;
														return X11_MISTY_ROSE_4;
													}
												}
											}
										}
										idx += 10;
										return X11_MISTY_ROSE;
									}
								}
								case '_' | 0x20:
								{
									if (!str[6] || strcmp(str[6], !"ROSE", true, 4))
									{
										return -1;
									}
									switch (str[10] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[10])
											{
												switch (str[11] | 0x20)
												{
													case '1':
													{
														idx += 12;
														return X11_MISTY_ROSE_1;
													}
													case '2':
													{
														idx += 12;
														return X11_MISTY_ROSE_2;
													}
													case '3':
													{
														idx += 12;
														return X11_MISTY_ROSE_3;
													}
													case '4':
													{
														idx += 12;
														return X11_MISTY_ROSE_4;
													}
												}
											}
										}
										case '_' | 0x20:
										{
											switch (str[11] | 0x20)
											{
												case '1':
												{
													idx += 12;
													return X11_MISTY_ROSE_1;
												}
												case '2':
												{
													idx += 12;
													return X11_MISTY_ROSE_2;
												}
												case '3':
												{
													idx += 12;
													return X11_MISTY_ROSE_3;
												}
												case '4':
												{
													idx += 12;
													return X11_MISTY_ROSE_4;
												}
											}
										}
									}
									idx += 10;
									return X11_MISTY_ROSE;
								}
								case 'r':
								{
									if (!str[6] || strcmp(str[6], !"OSE", true, 3))
									{
										return -1;
									}
									switch (str[9] | 0x20)
									{
										case '1':
										{
											idx += 10;
											return X11_MISTYROSE1;
										}
										case '2':
										{
											idx += 10;
											return X11_MISTYROSE2;
										}
										case '3':
										{
											idx += 10;
											return X11_MISTYROSE3;
										}
										case '4':
										{
											idx += 10;
											return X11_MISTYROSE4;
										}
									}
									idx += 9;
									return X11_MISTYROSE;
								}
							}
						}
					}
				}
				case 'o':
				{
					if (str[2] && !strcmp(str[2], !"CCASIN", true, 6))
					{
						idx += 8;
						return X11_MOCCASIN;
					}
				}
			}
		}
		case 'n':
		{
			if (!str[1] || strcmp(str[1], !"AV", true, 2))
			{
				return -1;
			}
			switch (str[3] | 0x20)
			{
				case 'a':
				{
					if (!str[4] || strcmp(str[4], !"JO", true, 2))
					{
						return -1;
					}
					switch (str[6] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[6])
							{
								if (!str[7] || strcmp(str[7], !"WHITE", true, 5))
								{
									return -1;
								}
								switch (str[12] | 0x20)
								{
									case _X11_SPACE_SWITCH: // ' '
									{
										if (str[12])
										{
											switch (str[13] | 0x20)
											{
												case '1':
												{
													idx += 14;
													return X11_NAVAJO_WHITE_1;
												}
												case '2':
												{
													idx += 14;
													return X11_NAVAJO_WHITE_2;
												}
												case '3':
												{
													idx += 14;
													return X11_NAVAJO_WHITE_3;
												}
												case '4':
												{
													idx += 14;
													return X11_NAVAJO_WHITE_4;
												}
											}
										}
									}
									case '_' | 0x20:
									{
										switch (str[13] | 0x20)
										{
											case '1':
											{
												idx += 14;
												return X11_NAVAJO_WHITE_1;
											}
											case '2':
											{
												idx += 14;
												return X11_NAVAJO_WHITE_2;
											}
											case '3':
											{
												idx += 14;
												return X11_NAVAJO_WHITE_3;
											}
											case '4':
											{
												idx += 14;
												return X11_NAVAJO_WHITE_4;
											}
										}
									}
								}
								idx += 12;
								return X11_NAVAJO_WHITE;
							}
						}
						case '_' | 0x20:
						{
							if (!str[7] || strcmp(str[7], !"WHITE", true, 5))
							{
								return -1;
							}
							switch (str[12] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[12])
									{
										switch (str[13] | 0x20)
										{
											case '1':
											{
												idx += 14;
												return X11_NAVAJO_WHITE_1;
											}
											case '2':
											{
												idx += 14;
												return X11_NAVAJO_WHITE_2;
											}
											case '3':
											{
												idx += 14;
												return X11_NAVAJO_WHITE_3;
											}
											case '4':
											{
												idx += 14;
												return X11_NAVAJO_WHITE_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[13] | 0x20)
									{
										case '1':
										{
											idx += 14;
											return X11_NAVAJO_WHITE_1;
										}
										case '2':
										{
											idx += 14;
											return X11_NAVAJO_WHITE_2;
										}
										case '3':
										{
											idx += 14;
											return X11_NAVAJO_WHITE_3;
										}
										case '4':
										{
											idx += 14;
											return X11_NAVAJO_WHITE_4;
										}
									}
								}
							}
							idx += 12;
							return X11_NAVAJO_WHITE;
						}
						case 'w':
						{
							if (!str[7] || strcmp(str[7], !"HITE", true, 4))
							{
								return -1;
							}
							switch (str[11] | 0x20)
							{
								case '1':
								{
									idx += 12;
									return X11_NAVAJOWHITE1;
								}
								case '2':
								{
									idx += 12;
									return X11_NAVAJOWHITE2;
								}
								case '3':
								{
									idx += 12;
									return X11_NAVAJOWHITE3;
								}
								case '4':
								{
									idx += 12;
									return X11_NAVAJOWHITE4;
								}
							}
							idx += 11;
							return X11_NAVAJOWHITE;
						}
					}
				}
				case 'y':
				{
					switch (str[4] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[4])
							{
								if (str[5] && !strcmp(str[5], !"BLUE", true, 4))
								{
									idx += 9;
									return X11_NAVY_BLUE;
								}
							}
						}
						case '_' | 0x20:
						{
							if (str[5] && !strcmp(str[5], !"BLUE", true, 4))
							{
								idx += 9;
								return X11_NAVY_BLUE;
							}
						}
						case 'b':
						{
							if (str[5] && !strcmp(str[5], !"LUE", true, 3))
							{
								idx += 8;
								return X11_NAVYBLUE;
							}
						}
					}
					idx += 4;
					return X11_NAVY;
				}
			}
		}
		case 'o':
		{
			switch (str[1] | 0x20)
			{
				case 'l':
				{
					switch (str[2] | 0x20)
					{
						case 'd':
						{
							switch (str[3] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[3])
									{
										if (str[4] && !strcmp(str[4], !"LACE", true, 4))
										{
											idx += 8;
											return X11_OLD_LACE;
										}
									}
								}
								case '_' | 0x20:
								{
									if (str[4] && !strcmp(str[4], !"LACE", true, 4))
									{
										idx += 8;
										return X11_OLD_LACE;
									}
								}
								case 'l':
								{
									if (str[4] && !strcmp(str[4], !"ACE", true, 3))
									{
										idx += 7;
										return X11_OLDLACE;
									}
								}
							}
						}
						case 'i':
						{
							if (!str[3] || strcmp(str[3], !"VE", true, 2))
							{
								return -1;
							}
							switch (str[5] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[5])
									{
										if (!str[6] || strcmp(str[6], !"DRAB", true, 4))
										{
											return -1;
										}
										switch (str[10] | 0x20)
										{
											case _X11_SPACE_SWITCH: // ' '
											{
												if (str[10])
												{
													switch (str[11] | 0x20)
													{
														case '1':
														{
															idx += 12;
															return X11_OLIVE_DRAB_1;
														}
														case '2':
														{
															idx += 12;
															return X11_OLIVE_DRAB_2;
														}
														case '3':
														{
															idx += 12;
															return X11_OLIVE_DRAB_3;
														}
														case '4':
														{
															idx += 12;
															return X11_OLIVE_DRAB_4;
														}
													}
												}
											}
											case '_' | 0x20:
											{
												switch (str[11] | 0x20)
												{
													case '1':
													{
														idx += 12;
														return X11_OLIVE_DRAB_1;
													}
													case '2':
													{
														idx += 12;
														return X11_OLIVE_DRAB_2;
													}
													case '3':
													{
														idx += 12;
														return X11_OLIVE_DRAB_3;
													}
													case '4':
													{
														idx += 12;
														return X11_OLIVE_DRAB_4;
													}
												}
											}
										}
										idx += 10;
										return X11_OLIVE_DRAB;
									}
								}
								case '_' | 0x20:
								{
									if (!str[6] || strcmp(str[6], !"DRAB", true, 4))
									{
										return -1;
									}
									switch (str[10] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[10])
											{
												switch (str[11] | 0x20)
												{
													case '1':
													{
														idx += 12;
														return X11_OLIVE_DRAB_1;
													}
													case '2':
													{
														idx += 12;
														return X11_OLIVE_DRAB_2;
													}
													case '3':
													{
														idx += 12;
														return X11_OLIVE_DRAB_3;
													}
													case '4':
													{
														idx += 12;
														return X11_OLIVE_DRAB_4;
													}
												}
											}
										}
										case '_' | 0x20:
										{
											switch (str[11] | 0x20)
											{
												case '1':
												{
													idx += 12;
													return X11_OLIVE_DRAB_1;
												}
												case '2':
												{
													idx += 12;
													return X11_OLIVE_DRAB_2;
												}
												case '3':
												{
													idx += 12;
													return X11_OLIVE_DRAB_3;
												}
												case '4':
												{
													idx += 12;
													return X11_OLIVE_DRAB_4;
												}
											}
										}
									}
									idx += 10;
									return X11_OLIVE_DRAB;
								}
								case 'd':
								{
									if (!str[6] || strcmp(str[6], !"RAB", true, 3))
									{
										return -1;
									}
									switch (str[9] | 0x20)
									{
										case '1':
										{
											idx += 10;
											return X11_OLIVEDRAB1;
										}
										case '2':
										{
											idx += 10;
											return X11_OLIVEDRAB2;
										}
										case '3':
										{
											idx += 10;
											return X11_OLIVEDRAB3;
										}
										case '4':
										{
											idx += 10;
											return X11_OLIVEDRAB4;
										}
									}
									idx += 9;
									return X11_OLIVEDRAB;
								}
							}
						}
					}
				}
				case 'r':
				{
					switch (str[2] | 0x20)
					{
						case 'a':
						{
							if (!str[3] || strcmp(str[3], !"NGE", true, 3))
							{
								return -1;
							}
							switch (str[6] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[6])
									{
										switch (str[7] | 0x20)
										{
											case '1':
											{
												idx += 8;
												return X11_ORANGE_1;
											}
											case '2':
											{
												idx += 8;
												return X11_ORANGE_2;
											}
											case '3':
											{
												idx += 8;
												return X11_ORANGE_3;
											}
											case '4':
											{
												idx += 8;
												return X11_ORANGE_4;
											}
											case 'r':
											{
												if (!str[8] || strcmp(str[8], !"ED", true, 2))
												{
													return -1;
												}
												switch (str[10] | 0x20)
												{
													case _X11_SPACE_SWITCH: // ' '
													{
														if (str[10])
														{
															switch (str[11] | 0x20)
															{
																case '1':
																{
																	idx += 12;
																	return X11_ORANGE_RED_1;
																}
																case '2':
																{
																	idx += 12;
																	return X11_ORANGE_RED_2;
																}
																case '3':
																{
																	idx += 12;
																	return X11_ORANGE_RED_3;
																}
																case '4':
																{
																	idx += 12;
																	return X11_ORANGE_RED_4;
																}
															}
														}
													}
													case '_' | 0x20:
													{
														switch (str[11] | 0x20)
														{
															case '1':
															{
																idx += 12;
																return X11_ORANGE_RED_1;
															}
															case '2':
															{
																idx += 12;
																return X11_ORANGE_RED_2;
															}
															case '3':
															{
																idx += 12;
																return X11_ORANGE_RED_3;
															}
															case '4':
															{
																idx += 12;
																return X11_ORANGE_RED_4;
															}
														}
													}
												}
												idx += 10;
												return X11_ORANGE_RED;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[7] | 0x20)
									{
										case '1':
										{
											idx += 8;
											return X11_ORANGE_1;
										}
										case '2':
										{
											idx += 8;
											return X11_ORANGE_2;
										}
										case '3':
										{
											idx += 8;
											return X11_ORANGE_3;
										}
										case '4':
										{
											idx += 8;
											return X11_ORANGE_4;
										}
										case 'r':
										{
											if (!str[8] || strcmp(str[8], !"ED", true, 2))
											{
												return -1;
											}
											switch (str[10] | 0x20)
											{
												case _X11_SPACE_SWITCH: // ' '
												{
													if (str[10])
													{
														switch (str[11] | 0x20)
														{
															case '1':
															{
																idx += 12;
																return X11_ORANGE_RED_1;
															}
															case '2':
															{
																idx += 12;
																return X11_ORANGE_RED_2;
															}
															case '3':
															{
																idx += 12;
																return X11_ORANGE_RED_3;
															}
															case '4':
															{
																idx += 12;
																return X11_ORANGE_RED_4;
															}
														}
													}
												}
												case '_' | 0x20:
												{
													switch (str[11] | 0x20)
													{
														case '1':
														{
															idx += 12;
															return X11_ORANGE_RED_1;
														}
														case '2':
														{
															idx += 12;
															return X11_ORANGE_RED_2;
														}
														case '3':
														{
															idx += 12;
															return X11_ORANGE_RED_3;
														}
														case '4':
														{
															idx += 12;
															return X11_ORANGE_RED_4;
														}
													}
												}
											}
											idx += 10;
											return X11_ORANGE_RED;
										}
									}
								}
								case '1':
								{
									idx += 7;
									return X11_ORANGE1;
								}
								case '2':
								{
									idx += 7;
									return X11_ORANGE2;
								}
								case '3':
								{
									idx += 7;
									return X11_ORANGE3;
								}
								case '4':
								{
									idx += 7;
									return X11_ORANGE4;
								}
								case 'r':
								{
									if (!str[7] || strcmp(str[7], !"ED", true, 2))
									{
										return -1;
									}
									switch (str[9] | 0x20)
									{
										case '1':
										{
											idx += 10;
											return X11_ORANGERED1;
										}
										case '2':
										{
											idx += 10;
											return X11_ORANGERED2;
										}
										case '3':
										{
											idx += 10;
											return X11_ORANGERED3;
										}
										case '4':
										{
											idx += 10;
											return X11_ORANGERED4;
										}
									}
									idx += 9;
									return X11_ORANGERED;
								}
							}
							idx += 6;
							return X11_ORANGE;
						}
						case 'c':
						{
							if (!str[3] || strcmp(str[3], !"HID", true, 3))
							{
								return -1;
							}
							switch (str[6] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[6])
									{
										switch (str[7] | 0x20)
										{
											case '1':
											{
												idx += 8;
												return X11_ORCHID_1;
											}
											case '2':
											{
												idx += 8;
												return X11_ORCHID_2;
											}
											case '3':
											{
												idx += 8;
												return X11_ORCHID_3;
											}
											case '4':
											{
												idx += 8;
												return X11_ORCHID_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[7] | 0x20)
									{
										case '1':
										{
											idx += 8;
											return X11_ORCHID_1;
										}
										case '2':
										{
											idx += 8;
											return X11_ORCHID_2;
										}
										case '3':
										{
											idx += 8;
											return X11_ORCHID_3;
										}
										case '4':
										{
											idx += 8;
											return X11_ORCHID_4;
										}
									}
								}
								case '1':
								{
									idx += 7;
									return X11_ORCHID1;
								}
								case '2':
								{
									idx += 7;
									return X11_ORCHID2;
								}
								case '3':
								{
									idx += 7;
									return X11_ORCHID3;
								}
								case '4':
								{
									idx += 7;
									return X11_ORCHID4;
								}
							}
							idx += 6;
							return X11_ORCHID;
						}
					}
				}
			}
		}
		case 'p':
		{
			switch (str[1] | 0x20)
			{
				case 'a':
				{
					switch (str[2] | 0x20)
					{
						case 'l':
						{
							if (str[3] | 0x20 != 'e')
							{
								return -1;
							}
							switch (str[4] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[4])
									{
										switch (str[5] | 0x20)
										{
											case 'g':
											{
												switch (str[6] | 0x20)
												{
													case 'o':
													{
														if (str[7] && !strcmp(str[7], !"LDENROD", true, 7))
														{
															idx += 14;
															return X11_PALE_GOLDENROD;
														}
													}
													case 'r':
													{
														if (!str[7] || strcmp(str[7], !"EEN", true, 3))
														{
															return -1;
														}
														switch (str[10] | 0x20)
														{
															case _X11_SPACE_SWITCH: // ' '
															{
																if (str[10])
																{
																	switch (str[11] | 0x20)
																	{
																		case '1':
																		{
																			idx += 12;
																			return X11_PALE_GREEN_1;
																		}
																		case '2':
																		{
																			idx += 12;
																			return X11_PALE_GREEN_2;
																		}
																		case '3':
																		{
																			idx += 12;
																			return X11_PALE_GREEN_3;
																		}
																		case '4':
																		{
																			idx += 12;
																			return X11_PALE_GREEN_4;
																		}
																	}
																}
															}
															case '_' | 0x20:
															{
																switch (str[11] | 0x20)
																{
																	case '1':
																	{
																		idx += 12;
																		return X11_PALE_GREEN_1;
																	}
																	case '2':
																	{
																		idx += 12;
																		return X11_PALE_GREEN_2;
																	}
																	case '3':
																	{
																		idx += 12;
																		return X11_PALE_GREEN_3;
																	}
																	case '4':
																	{
																		idx += 12;
																		return X11_PALE_GREEN_4;
																	}
																}
															}
														}
														idx += 10;
														return X11_PALE_GREEN;
													}
												}
											}
											case 't':
											{
												if (!str[6] || strcmp(str[6], !"URQUOISE", true, 8))
												{
													return -1;
												}
												switch (str[14] | 0x20)
												{
													case _X11_SPACE_SWITCH: // ' '
													{
														if (str[14])
														{
															switch (str[15] | 0x20)
															{
																case '1':
																{
																	idx += 16;
																	return X11_PALE_TURQUOISE_1;
																}
																case '2':
																{
																	idx += 16;
																	return X11_PALE_TURQUOISE_2;
																}
																case '3':
																{
																	idx += 16;
																	return X11_PALE_TURQUOISE_3;
																}
																case '4':
																{
																	idx += 16;
																	return X11_PALE_TURQUOISE_4;
																}
															}
														}
													}
													case '_' | 0x20:
													{
														switch (str[15] | 0x20)
														{
															case '1':
															{
																idx += 16;
																return X11_PALE_TURQUOISE_1;
															}
															case '2':
															{
																idx += 16;
																return X11_PALE_TURQUOISE_2;
															}
															case '3':
															{
																idx += 16;
																return X11_PALE_TURQUOISE_3;
															}
															case '4':
															{
																idx += 16;
																return X11_PALE_TURQUOISE_4;
															}
														}
													}
												}
												idx += 14;
												return X11_PALE_TURQUOISE;
											}
											case 'v':
											{
												if (!str[6] || strcmp(str[6], !"IOLET", true, 5) || (!_X11_SPACE_CHECK(11) && str[11] != '_') || strcmp(str[12], !"RED", true, 3))
												//if (!str[6] || strcmp(str[6], !"IOLET_RED", true, 9))
												{
													return -1;
												}
												switch (str[15] | 0x20)
												{
													case _X11_SPACE_SWITCH: // ' '
													{
														if (str[15])
														{
															switch (str[16] | 0x20)
															{
																case '1':
																{
																	idx += 17;
																	return X11_PALE_VIOLET_RED_1;
																}
																case '2':
																{
																	idx += 17;
																	return X11_PALE_VIOLET_RED_2;
																}
																case '3':
																{
																	idx += 17;
																	return X11_PALE_VIOLET_RED_3;
																}
																case '4':
																{
																	idx += 17;
																	return X11_PALE_VIOLET_RED_4;
																}
															}
														}
													}
													case '_' | 0x20:
													{
														switch (str[16] | 0x20)
														{
															case '1':
															{
																idx += 17;
																return X11_PALE_VIOLET_RED_1;
															}
															case '2':
															{
																idx += 17;
																return X11_PALE_VIOLET_RED_2;
															}
															case '3':
															{
																idx += 17;
																return X11_PALE_VIOLET_RED_3;
															}
															case '4':
															{
																idx += 17;
																return X11_PALE_VIOLET_RED_4;
															}
														}
													}
												}
												idx += 15;
												return X11_PALE_VIOLET_RED;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[5] | 0x20)
									{
										case 'g':
										{
											switch (str[6] | 0x20)
											{
												case 'o':
												{
													if (str[7] && !strcmp(str[7], !"LDENROD", true, 7))
													{
														idx += 14;
														return X11_PALE_GOLDENROD;
													}
												}
												case 'r':
												{
													if (!str[7] || strcmp(str[7], !"EEN", true, 3))
													{
														return -1;
													}
													switch (str[10] | 0x20)
													{
														case _X11_SPACE_SWITCH: // ' '
														{
															if (str[10])
															{
																switch (str[11] | 0x20)
																{
																	case '1':
																	{
																		idx += 12;
																		return X11_PALE_GREEN_1;
																	}
																	case '2':
																	{
																		idx += 12;
																		return X11_PALE_GREEN_2;
																	}
																	case '3':
																	{
																		idx += 12;
																		return X11_PALE_GREEN_3;
																	}
																	case '4':
																	{
																		idx += 12;
																		return X11_PALE_GREEN_4;
																	}
																}
															}
														}
														case '_' | 0x20:
														{
															switch (str[11] | 0x20)
															{
																case '1':
																{
																	idx += 12;
																	return X11_PALE_GREEN_1;
																}
																case '2':
																{
																	idx += 12;
																	return X11_PALE_GREEN_2;
																}
																case '3':
																{
																	idx += 12;
																	return X11_PALE_GREEN_3;
																}
																case '4':
																{
																	idx += 12;
																	return X11_PALE_GREEN_4;
																}
															}
														}
													}
													idx += 10;
													return X11_PALE_GREEN;
												}
											}
										}
										case 't':
										{
											if (!str[6] || strcmp(str[6], !"URQUOISE", true, 8))
											{
												return -1;
											}
											switch (str[14] | 0x20)
											{
												case _X11_SPACE_SWITCH: // ' '
												{
													if (str[14])
													{
														switch (str[15] | 0x20)
														{
															case '1':
															{
																idx += 16;
																return X11_PALE_TURQUOISE_1;
															}
															case '2':
															{
																idx += 16;
																return X11_PALE_TURQUOISE_2;
															}
															case '3':
															{
																idx += 16;
																return X11_PALE_TURQUOISE_3;
															}
															case '4':
															{
																idx += 16;
																return X11_PALE_TURQUOISE_4;
															}
														}
													}
												}
												case '_' | 0x20:
												{
													switch (str[15] | 0x20)
													{
														case '1':
														{
															idx += 16;
															return X11_PALE_TURQUOISE_1;
														}
														case '2':
														{
															idx += 16;
															return X11_PALE_TURQUOISE_2;
														}
														case '3':
														{
															idx += 16;
															return X11_PALE_TURQUOISE_3;
														}
														case '4':
														{
															idx += 16;
															return X11_PALE_TURQUOISE_4;
														}
													}
												}
											}
											idx += 14;
											return X11_PALE_TURQUOISE;
										}
										case 'v':
										{
											if (!str[6] || strcmp(str[6], !"IOLET", true, 5) || (!_X11_SPACE_CHECK(11) && str[11] != '_') || strcmp(str[12], !"RED", true, 3))
											//if (!str[6] || strcmp(str[6], !"IOLET_RED", true, 9))
											{
												return -1;
											}
											switch (str[15] | 0x20)
											{
												case _X11_SPACE_SWITCH: // ' '
												{
													if (str[15])
													{
														switch (str[16] | 0x20)
														{
															case '1':
															{
																idx += 17;
																return X11_PALE_VIOLET_RED_1;
															}
															case '2':
															{
																idx += 17;
																return X11_PALE_VIOLET_RED_2;
															}
															case '3':
															{
																idx += 17;
																return X11_PALE_VIOLET_RED_3;
															}
															case '4':
															{
																idx += 17;
																return X11_PALE_VIOLET_RED_4;
															}
														}
													}
												}
												case '_' | 0x20:
												{
													switch (str[16] | 0x20)
													{
														case '1':
														{
															idx += 17;
															return X11_PALE_VIOLET_RED_1;
														}
														case '2':
														{
															idx += 17;
															return X11_PALE_VIOLET_RED_2;
														}
														case '3':
														{
															idx += 17;
															return X11_PALE_VIOLET_RED_3;
														}
														case '4':
														{
															idx += 17;
															return X11_PALE_VIOLET_RED_4;
														}
													}
												}
											}
											idx += 15;
											return X11_PALE_VIOLET_RED;
										}
									}
								}
								case 'g':
								{
									switch (str[5] | 0x20)
									{
										case 'o':
										{
											if (str[6] && !strcmp(str[6], !"LDENROD", true, 7))
											{
												idx += 13;
												return X11_PALEGOLDENROD;
											}
										}
										case 'r':
										{
											if (!str[6] || strcmp(str[6], !"EEN", true, 3))
											{
												return -1;
											}
											switch (str[9] | 0x20)
											{
												case '1':
												{
													idx += 10;
													return X11_PALEGREEN1;
												}
												case '2':
												{
													idx += 10;
													return X11_PALEGREEN2;
												}
												case '3':
												{
													idx += 10;
													return X11_PALEGREEN3;
												}
												case '4':
												{
													idx += 10;
													return X11_PALEGREEN4;
												}
											}
											idx += 9;
											return X11_PALEGREEN;
										}
									}
								}
								case 't':
								{
									if (!str[5] || strcmp(str[5], !"URQUOISE", true, 8))
									{
										return -1;
									}
									switch (str[13] | 0x20)
									{
										case '1':
										{
											idx += 14;
											return X11_PALETURQUOISE1;
										}
										case '2':
										{
											idx += 14;
											return X11_PALETURQUOISE2;
										}
										case '3':
										{
											idx += 14;
											return X11_PALETURQUOISE3;
										}
										case '4':
										{
											idx += 14;
											return X11_PALETURQUOISE4;
										}
									}
									idx += 13;
									return X11_PALETURQUOISE;
								}
								case 'v':
								{
									if (!str[5] || strcmp(str[5], !"IOLETRED", true, 8))
									{
										return -1;
									}
									switch (str[13] | 0x20)
									{
										case '1':
										{
											idx += 14;
											return X11_PALEVIOLETRED1;
										}
										case '2':
										{
											idx += 14;
											return X11_PALEVIOLETRED2;
										}
										case '3':
										{
											idx += 14;
											return X11_PALEVIOLETRED3;
										}
										case '4':
										{
											idx += 14;
											return X11_PALEVIOLETRED4;
										}
									}
									idx += 13;
									return X11_PALEVIOLETRED;
								}
							}
						}
						case 'p':
						{
							if (!str[3] || strcmp(str[3], !"AYA", true, 3))
							{
								return -1;
							}
							switch (str[6] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[6])
									{
										if (str[7] && !strcmp(str[7], !"WHIP", true, 4))
										{
											idx += 11;
											return X11_PAPAYA_WHIP;
										}
									}
								}
								case '_' | 0x20:
								{
									if (str[7] && !strcmp(str[7], !"WHIP", true, 4))
									{
										idx += 11;
										return X11_PAPAYA_WHIP;
									}
								}
								case 'w':
								{
									if (str[7] && !strcmp(str[7], !"HIP", true, 3))
									{
										idx += 10;
										return X11_PAPAYAWHIP;
									}
								}
							}
						}
					}
				}
				case 'e':
				{
					switch (str[2] | 0x20)
					{
						case 'a':
						{
							if (!str[3] || strcmp(str[3], !"CH", true, 2))
							{
								return -1;
							}
							switch (str[5] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[5])
									{
										if (!str[6] || strcmp(str[6], !"PUFF", true, 4))
										{
											return -1;
										}
										switch (str[10] | 0x20)
										{
											case _X11_SPACE_SWITCH: // ' '
											{
												if (str[10])
												{
													switch (str[11] | 0x20)
													{
														case '1':
														{
															idx += 12;
															return X11_PEACH_PUFF_1;
														}
														case '2':
														{
															idx += 12;
															return X11_PEACH_PUFF_2;
														}
														case '3':
														{
															idx += 12;
															return X11_PEACH_PUFF_3;
														}
														case '4':
														{
															idx += 12;
															return X11_PEACH_PUFF_4;
														}
													}
												}
											}
											case '_' | 0x20:
											{
												switch (str[11] | 0x20)
												{
													case '1':
													{
														idx += 12;
														return X11_PEACH_PUFF_1;
													}
													case '2':
													{
														idx += 12;
														return X11_PEACH_PUFF_2;
													}
													case '3':
													{
														idx += 12;
														return X11_PEACH_PUFF_3;
													}
													case '4':
													{
														idx += 12;
														return X11_PEACH_PUFF_4;
													}
												}
											}
										}
										idx += 10;
										return X11_PEACH_PUFF;
									}
								}
								case '_' | 0x20:
								{
									if (!str[6] || strcmp(str[6], !"PUFF", true, 4))
									{
										return -1;
									}
									switch (str[10] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[10])
											{
												switch (str[11] | 0x20)
												{
													case '1':
													{
														idx += 12;
														return X11_PEACH_PUFF_1;
													}
													case '2':
													{
														idx += 12;
														return X11_PEACH_PUFF_2;
													}
													case '3':
													{
														idx += 12;
														return X11_PEACH_PUFF_3;
													}
													case '4':
													{
														idx += 12;
														return X11_PEACH_PUFF_4;
													}
												}
											}
										}
										case '_' | 0x20:
										{
											switch (str[11] | 0x20)
											{
												case '1':
												{
													idx += 12;
													return X11_PEACH_PUFF_1;
												}
												case '2':
												{
													idx += 12;
													return X11_PEACH_PUFF_2;
												}
												case '3':
												{
													idx += 12;
													return X11_PEACH_PUFF_3;
												}
												case '4':
												{
													idx += 12;
													return X11_PEACH_PUFF_4;
												}
											}
										}
									}
									idx += 10;
									return X11_PEACH_PUFF;
								}
								case 'p':
								{
									if (!str[6] || strcmp(str[6], !"UFF", true, 3))
									{
										return -1;
									}
									switch (str[9] | 0x20)
									{
										case '1':
										{
											idx += 10;
											return X11_PEACHPUFF1;
										}
										case '2':
										{
											idx += 10;
											return X11_PEACHPUFF2;
										}
										case '3':
										{
											idx += 10;
											return X11_PEACHPUFF3;
										}
										case '4':
										{
											idx += 10;
											return X11_PEACHPUFF4;
										}
									}
									idx += 9;
									return X11_PEACHPUFF;
								}
							}
						}
						case 'r':
						{
							if (str[3] | 0x20 == 'u')
							{
								idx += 4;
								return X11_PERU;
							}
						}
					}
				}
				case 'i':
				{
					if (!str[2] || strcmp(str[2], !"NK", true, 2))
					{
						return -1;
					}
					switch (str[4] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[4])
							{
								switch (str[5] | 0x20)
								{
									case '1':
									{
										idx += 6;
										return X11_PINK_1;
									}
									case '2':
									{
										idx += 6;
										return X11_PINK_2;
									}
									case '3':
									{
										idx += 6;
										return X11_PINK_3;
									}
									case '4':
									{
										idx += 6;
										return X11_PINK_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[5] | 0x20)
							{
								case '1':
								{
									idx += 6;
									return X11_PINK_1;
								}
								case '2':
								{
									idx += 6;
									return X11_PINK_2;
								}
								case '3':
								{
									idx += 6;
									return X11_PINK_3;
								}
								case '4':
								{
									idx += 6;
									return X11_PINK_4;
								}
							}
						}
						case '1':
						{
							idx += 5;
							return X11_PINK1;
						}
						case '2':
						{
							idx += 5;
							return X11_PINK2;
						}
						case '3':
						{
							idx += 5;
							return X11_PINK3;
						}
						case '4':
						{
							idx += 5;
							return X11_PINK4;
						}
					}
					idx += 4;
					return X11_PINK;
				}
				case 'l':
				{
					if (!str[2] || strcmp(str[2], !"UM", true, 2))
					{
						return -1;
					}
					switch (str[4] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[4])
							{
								switch (str[5] | 0x20)
								{
									case '1':
									{
										idx += 6;
										return X11_PLUM_1;
									}
									case '2':
									{
										idx += 6;
										return X11_PLUM_2;
									}
									case '3':
									{
										idx += 6;
										return X11_PLUM_3;
									}
									case '4':
									{
										idx += 6;
										return X11_PLUM_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[5] | 0x20)
							{
								case '1':
								{
									idx += 6;
									return X11_PLUM_1;
								}
								case '2':
								{
									idx += 6;
									return X11_PLUM_2;
								}
								case '3':
								{
									idx += 6;
									return X11_PLUM_3;
								}
								case '4':
								{
									idx += 6;
									return X11_PLUM_4;
								}
							}
						}
						case '1':
						{
							idx += 5;
							return X11_PLUM1;
						}
						case '2':
						{
							idx += 5;
							return X11_PLUM2;
						}
						case '3':
						{
							idx += 5;
							return X11_PLUM3;
						}
						case '4':
						{
							idx += 5;
							return X11_PLUM4;
						}
					}
					idx += 4;
					return X11_PLUM;
				}
				case 'o':
				{
					if (!str[2] || strcmp(str[2], !"WDER", true, 4))
					{
						return -1;
					}
					switch (str[6] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[6])
							{
								if (str[7] && !strcmp(str[7], !"BLUE", true, 4))
								{
									idx += 11;
									return X11_POWDER_BLUE;
								}
							}
						}
						case '_' | 0x20:
						{
							if (str[7] && !strcmp(str[7], !"BLUE", true, 4))
							{
								idx += 11;
								return X11_POWDER_BLUE;
							}
						}
						case 'b':
						{
							if (str[7] && !strcmp(str[7], !"LUE", true, 3))
							{
								idx += 10;
								return X11_POWDERBLUE;
							}
						}
					}
				}
				case 'u':
				{
					if (!str[2] || strcmp(str[2], !"RPLE", true, 4))
					{
						return -1;
					}
					switch (str[6] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[6])
							{
								switch (str[7] | 0x20)
								{
									case '1':
									{
										idx += 8;
										return X11_PURPLE_1;
									}
									case '2':
									{
										idx += 8;
										return X11_PURPLE_2;
									}
									case '3':
									{
										idx += 8;
										return X11_PURPLE_3;
									}
									case '4':
									{
										idx += 8;
										return X11_PURPLE_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[7] | 0x20)
							{
								case '1':
								{
									idx += 8;
									return X11_PURPLE_1;
								}
								case '2':
								{
									idx += 8;
									return X11_PURPLE_2;
								}
								case '3':
								{
									idx += 8;
									return X11_PURPLE_3;
								}
								case '4':
								{
									idx += 8;
									return X11_PURPLE_4;
								}
							}
						}
						case '1':
						{
							idx += 7;
							return X11_PURPLE1;
						}
						case '2':
						{
							idx += 7;
							return X11_PURPLE2;
						}
						case '3':
						{
							idx += 7;
							return X11_PURPLE3;
						}
						case '4':
						{
							idx += 7;
							return X11_PURPLE4;
						}
					}
					idx += 6;
					return X11_PURPLE;
				}
			}
		}
		case 'r':
		{
			switch (str[1] | 0x20)
			{
				case 'e':
				{
					if (str[2] | 0x20 != 'd')
					{
						return -1;
					}
					switch (str[3] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[3])
							{
								switch (str[4] | 0x20)
								{
									case '1':
									{
										idx += 5;
										return X11_RED_1;
									}
									case '2':
									{
										idx += 5;
										return X11_RED_2;
									}
									case '3':
									{
										idx += 5;
										return X11_RED_3;
									}
									case '4':
									{
										idx += 5;
										return X11_RED_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[4] | 0x20)
							{
								case '1':
								{
									idx += 5;
									return X11_RED_1;
								}
								case '2':
								{
									idx += 5;
									return X11_RED_2;
								}
								case '3':
								{
									idx += 5;
									return X11_RED_3;
								}
								case '4':
								{
									idx += 5;
									return X11_RED_4;
								}
							}
						}
						case '1':
						{
							idx += 4;
							return X11_RED1;
						}
						case '2':
						{
							idx += 4;
							return X11_RED2;
						}
						case '3':
						{
							idx += 4;
							return X11_RED3;
						}
						case '4':
						{
							idx += 4;
							return X11_RED4;
						}
					}
					idx += 3;
					return X11_RED;
				}
				case 'o':
				{
					switch (str[2] | 0x20)
					{
						case 's':
						{
							if (str[3] | 0x20 != 'y')
							{
								return -1;
							}
							switch (str[4] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[4])
									{
										if (!str[5] || strcmp(str[5], !"BROWN", true, 5))
										{
											return -1;
										}
										switch (str[10] | 0x20)
										{
											case _X11_SPACE_SWITCH: // ' '
											{
												if (str[10])
												{
													switch (str[11] | 0x20)
													{
														case '1':
														{
															idx += 12;
															return X11_ROSY_BROWN_1;
														}
														case '2':
														{
															idx += 12;
															return X11_ROSY_BROWN_2;
														}
														case '3':
														{
															idx += 12;
															return X11_ROSY_BROWN_3;
														}
														case '4':
														{
															idx += 12;
															return X11_ROSY_BROWN_4;
														}
													}
												}
											}
											case '_' | 0x20:
											{
												switch (str[11] | 0x20)
												{
													case '1':
													{
														idx += 12;
														return X11_ROSY_BROWN_1;
													}
													case '2':
													{
														idx += 12;
														return X11_ROSY_BROWN_2;
													}
													case '3':
													{
														idx += 12;
														return X11_ROSY_BROWN_3;
													}
													case '4':
													{
														idx += 12;
														return X11_ROSY_BROWN_4;
													}
												}
											}
										}
										idx += 10;
										return X11_ROSY_BROWN;
									}
								}
								case '_' | 0x20:
								{
									if (!str[5] || strcmp(str[5], !"BROWN", true, 5))
									{
										return -1;
									}
									switch (str[10] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[10])
											{
												switch (str[11] | 0x20)
												{
													case '1':
													{
														idx += 12;
														return X11_ROSY_BROWN_1;
													}
													case '2':
													{
														idx += 12;
														return X11_ROSY_BROWN_2;
													}
													case '3':
													{
														idx += 12;
														return X11_ROSY_BROWN_3;
													}
													case '4':
													{
														idx += 12;
														return X11_ROSY_BROWN_4;
													}
												}
											}
										}
										case '_' | 0x20:
										{
											switch (str[11] | 0x20)
											{
												case '1':
												{
													idx += 12;
													return X11_ROSY_BROWN_1;
												}
												case '2':
												{
													idx += 12;
													return X11_ROSY_BROWN_2;
												}
												case '3':
												{
													idx += 12;
													return X11_ROSY_BROWN_3;
												}
												case '4':
												{
													idx += 12;
													return X11_ROSY_BROWN_4;
												}
											}
										}
									}
									idx += 10;
									return X11_ROSY_BROWN;
								}
								case 'b':
								{
									if (!str[5] || strcmp(str[5], !"ROWN", true, 4))
									{
										return -1;
									}
									switch (str[9] | 0x20)
									{
										case '1':
										{
											idx += 10;
											return X11_ROSYBROWN1;
										}
										case '2':
										{
											idx += 10;
											return X11_ROSYBROWN2;
										}
										case '3':
										{
											idx += 10;
											return X11_ROSYBROWN3;
										}
										case '4':
										{
											idx += 10;
											return X11_ROSYBROWN4;
										}
									}
									idx += 9;
									return X11_ROSYBROWN;
								}
							}
						}
						case 'y':
						{
							if (!str[3] || strcmp(str[3], !"AL", true, 2))
							{
								return -1;
							}
							switch (str[5] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[5])
									{
										if (!str[6] || strcmp(str[6], !"BLUE", true, 4))
										{
											return -1;
										}
										switch (str[10] | 0x20)
										{
											case _X11_SPACE_SWITCH: // ' '
											{
												if (str[10])
												{
													switch (str[11] | 0x20)
													{
														case '1':
														{
															idx += 12;
															return X11_ROYAL_BLUE_1;
														}
														case '2':
														{
															idx += 12;
															return X11_ROYAL_BLUE_2;
														}
														case '3':
														{
															idx += 12;
															return X11_ROYAL_BLUE_3;
														}
														case '4':
														{
															idx += 12;
															return X11_ROYAL_BLUE_4;
														}
													}
												}
											}
											case '_' | 0x20:
											{
												switch (str[11] | 0x20)
												{
													case '1':
													{
														idx += 12;
														return X11_ROYAL_BLUE_1;
													}
													case '2':
													{
														idx += 12;
														return X11_ROYAL_BLUE_2;
													}
													case '3':
													{
														idx += 12;
														return X11_ROYAL_BLUE_3;
													}
													case '4':
													{
														idx += 12;
														return X11_ROYAL_BLUE_4;
													}
												}
											}
										}
										idx += 10;
										return X11_ROYAL_BLUE;
									}
								}
								case '_' | 0x20:
								{
									if (!str[6] || strcmp(str[6], !"BLUE", true, 4))
									{
										return -1;
									}
									switch (str[10] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[10])
											{
												switch (str[11] | 0x20)
												{
													case '1':
													{
														idx += 12;
														return X11_ROYAL_BLUE_1;
													}
													case '2':
													{
														idx += 12;
														return X11_ROYAL_BLUE_2;
													}
													case '3':
													{
														idx += 12;
														return X11_ROYAL_BLUE_3;
													}
													case '4':
													{
														idx += 12;
														return X11_ROYAL_BLUE_4;
													}
												}
											}
										}
										case '_' | 0x20:
										{
											switch (str[11] | 0x20)
											{
												case '1':
												{
													idx += 12;
													return X11_ROYAL_BLUE_1;
												}
												case '2':
												{
													idx += 12;
													return X11_ROYAL_BLUE_2;
												}
												case '3':
												{
													idx += 12;
													return X11_ROYAL_BLUE_3;
												}
												case '4':
												{
													idx += 12;
													return X11_ROYAL_BLUE_4;
												}
											}
										}
									}
									idx += 10;
									return X11_ROYAL_BLUE;
								}
								case 'b':
								{
									if (!str[6] || strcmp(str[6], !"LUE", true, 3))
									{
										return -1;
									}
									switch (str[9] | 0x20)
									{
										case '1':
										{
											idx += 10;
											return X11_ROYALBLUE1;
										}
										case '2':
										{
											idx += 10;
											return X11_ROYALBLUE2;
										}
										case '3':
										{
											idx += 10;
											return X11_ROYALBLUE3;
										}
										case '4':
										{
											idx += 10;
											return X11_ROYALBLUE4;
										}
									}
									idx += 9;
									return X11_ROYALBLUE;
								}
							}
						}
					}
				}
			}
		}
		case 's':
		{
			switch (str[1] | 0x20)
			{
				case 'a':
				{
					switch (str[2] | 0x20)
					{
						case 'd':
						{
							if (!str[3] || strcmp(str[3], !"DLE", true, 3))
							{
								return -1;
							}
							switch (str[6] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[6])
									{
										if (str[7] && !strcmp(str[7], !"BROWN", true, 5))
										{
											idx += 12;
											return X11_SADDLE_BROWN;
										}
									}
								}
								case '_' | 0x20:
								{
									if (str[7] && !strcmp(str[7], !"BROWN", true, 5))
									{
										idx += 12;
										return X11_SADDLE_BROWN;
									}
								}
								case 'b':
								{
									if (str[7] && !strcmp(str[7], !"ROWN", true, 4))
									{
										idx += 11;
										return X11_SADDLEBROWN;
									}
								}
							}
						}
						case 'l':
						{
							if (!str[3] || strcmp(str[3], !"MON", true, 3))
							{
								return -1;
							}
							switch (str[6] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[6])
									{
										switch (str[7] | 0x20)
										{
											case '1':
											{
												idx += 8;
												return X11_SALMON_1;
											}
											case '2':
											{
												idx += 8;
												return X11_SALMON_2;
											}
											case '3':
											{
												idx += 8;
												return X11_SALMON_3;
											}
											case '4':
											{
												idx += 8;
												return X11_SALMON_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[7] | 0x20)
									{
										case '1':
										{
											idx += 8;
											return X11_SALMON_1;
										}
										case '2':
										{
											idx += 8;
											return X11_SALMON_2;
										}
										case '3':
										{
											idx += 8;
											return X11_SALMON_3;
										}
										case '4':
										{
											idx += 8;
											return X11_SALMON_4;
										}
									}
								}
								case '1':
								{
									idx += 7;
									return X11_SALMON1;
								}
								case '2':
								{
									idx += 7;
									return X11_SALMON2;
								}
								case '3':
								{
									idx += 7;
									return X11_SALMON3;
								}
								case '4':
								{
									idx += 7;
									return X11_SALMON4;
								}
							}
							idx += 6;
							return X11_SALMON;
						}
						case 'n':
						{
							if (!str[3] || strcmp(str[3], !"DY", true, 2))
							{
								return -1;
							}
							switch (str[5] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[5])
									{
										if (str[6] && !strcmp(str[6], !"BROWN", true, 5))
										{
											idx += 11;
											return X11_SANDY_BROWN;
										}
									}
								}
								case '_' | 0x20:
								{
									if (str[6] && !strcmp(str[6], !"BROWN", true, 5))
									{
										idx += 11;
										return X11_SANDY_BROWN;
									}
								}
								case 'b':
								{
									if (str[6] && !strcmp(str[6], !"ROWN", true, 4))
									{
										idx += 10;
										return X11_SANDYBROWN;
									}
								}
							}
						}
					}
				}
				case 'e':
				{
					if (str[2] | 0x20 != 'a')
					{
						return -1;
					}
					switch (str[3] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[3])
							{
								if (!str[4] || strcmp(str[4], !"GREEN", true, 5))
								{
									return -1;
								}
								switch (str[9] | 0x20)
								{
									case _X11_SPACE_SWITCH: // ' '
									{
										if (str[9])
										{
											switch (str[10] | 0x20)
											{
												case '1':
												{
													idx += 11;
													return X11_SEA_GREEN_1;
												}
												case '2':
												{
													idx += 11;
													return X11_SEA_GREEN_2;
												}
												case '3':
												{
													idx += 11;
													return X11_SEA_GREEN_3;
												}
												case '4':
												{
													idx += 11;
													return X11_SEA_GREEN_4;
												}
											}
										}
									}
									case '_' | 0x20:
									{
										switch (str[10] | 0x20)
										{
											case '1':
											{
												idx += 11;
												return X11_SEA_GREEN_1;
											}
											case '2':
											{
												idx += 11;
												return X11_SEA_GREEN_2;
											}
											case '3':
											{
												idx += 11;
												return X11_SEA_GREEN_3;
											}
											case '4':
											{
												idx += 11;
												return X11_SEA_GREEN_4;
											}
										}
									}
								}
								idx += 9;
								return X11_SEA_GREEN;
							}
						}
						case '_' | 0x20:
						{
							if (!str[4] || strcmp(str[4], !"GREEN", true, 5))
							{
								return -1;
							}
							switch (str[9] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[9])
									{
										switch (str[10] | 0x20)
										{
											case '1':
											{
												idx += 11;
												return X11_SEA_GREEN_1;
											}
											case '2':
											{
												idx += 11;
												return X11_SEA_GREEN_2;
											}
											case '3':
											{
												idx += 11;
												return X11_SEA_GREEN_3;
											}
											case '4':
											{
												idx += 11;
												return X11_SEA_GREEN_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[10] | 0x20)
									{
										case '1':
										{
											idx += 11;
											return X11_SEA_GREEN_1;
										}
										case '2':
										{
											idx += 11;
											return X11_SEA_GREEN_2;
										}
										case '3':
										{
											idx += 11;
											return X11_SEA_GREEN_3;
										}
										case '4':
										{
											idx += 11;
											return X11_SEA_GREEN_4;
										}
									}
								}
							}
							idx += 9;
							return X11_SEA_GREEN;
						}
						case 'g':
						{
							if (!str[4] || strcmp(str[4], !"REEN", true, 4))
							{
								return -1;
							}
							switch (str[8] | 0x20)
							{
								case '1':
								{
									idx += 9;
									return X11_SEAGREEN1;
								}
								case '2':
								{
									idx += 9;
									return X11_SEAGREEN2;
								}
								case '3':
								{
									idx += 9;
									return X11_SEAGREEN3;
								}
								case '4':
								{
									idx += 9;
									return X11_SEAGREEN4;
								}
							}
							idx += 8;
							return X11_SEAGREEN;
						}
						case 's':
						{
							if (!str[4] || strcmp(str[4], !"HELL", true, 4))
							{
								return -1;
							}
							switch (str[8] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[8])
									{
										switch (str[9] | 0x20)
										{
											case '1':
											{
												idx += 10;
												return X11_SEASHELL_1;
											}
											case '2':
											{
												idx += 10;
												return X11_SEASHELL_2;
											}
											case '3':
											{
												idx += 10;
												return X11_SEASHELL_3;
											}
											case '4':
											{
												idx += 10;
												return X11_SEASHELL_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[9] | 0x20)
									{
										case '1':
										{
											idx += 10;
											return X11_SEASHELL_1;
										}
										case '2':
										{
											idx += 10;
											return X11_SEASHELL_2;
										}
										case '3':
										{
											idx += 10;
											return X11_SEASHELL_3;
										}
										case '4':
										{
											idx += 10;
											return X11_SEASHELL_4;
										}
									}
								}
								case '1':
								{
									idx += 9;
									return X11_SEASHELL1;
								}
								case '2':
								{
									idx += 9;
									return X11_SEASHELL2;
								}
								case '3':
								{
									idx += 9;
									return X11_SEASHELL3;
								}
								case '4':
								{
									idx += 9;
									return X11_SEASHELL4;
								}
							}
							idx += 8;
							return X11_SEASHELL;
						}
					}
				}
				case 'i':
				{
					if (!str[2] || strcmp(str[2], !"ENNA", true, 4))
					{
						return -1;
					}
					switch (str[6] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[6])
							{
								switch (str[7] | 0x20)
								{
									case '1':
									{
										idx += 8;
										return X11_SIENNA_1;
									}
									case '2':
									{
										idx += 8;
										return X11_SIENNA_2;
									}
									case '3':
									{
										idx += 8;
										return X11_SIENNA_3;
									}
									case '4':
									{
										idx += 8;
										return X11_SIENNA_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[7] | 0x20)
							{
								case '1':
								{
									idx += 8;
									return X11_SIENNA_1;
								}
								case '2':
								{
									idx += 8;
									return X11_SIENNA_2;
								}
								case '3':
								{
									idx += 8;
									return X11_SIENNA_3;
								}
								case '4':
								{
									idx += 8;
									return X11_SIENNA_4;
								}
							}
						}
						case '1':
						{
							idx += 7;
							return X11_SIENNA1;
						}
						case '2':
						{
							idx += 7;
							return X11_SIENNA2;
						}
						case '3':
						{
							idx += 7;
							return X11_SIENNA3;
						}
						case '4':
						{
							idx += 7;
							return X11_SIENNA4;
						}
					}
					idx += 6;
					return X11_SIENNA;
				}
				case 'k':
				{
					if (str[2] | 0x20 != 'y')
					{
						return -1;
					}
					switch (str[3] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[3])
							{
								if (!str[4] || strcmp(str[4], !"BLUE", true, 4))
								{
									return -1;
								}
								switch (str[8] | 0x20)
								{
									case _X11_SPACE_SWITCH: // ' '
									{
										if (str[8])
										{
											switch (str[9] | 0x20)
											{
												case '1':
												{
													idx += 10;
													return X11_SKY_BLUE_1;
												}
												case '2':
												{
													idx += 10;
													return X11_SKY_BLUE_2;
												}
												case '3':
												{
													idx += 10;
													return X11_SKY_BLUE_3;
												}
												case '4':
												{
													idx += 10;
													return X11_SKY_BLUE_4;
												}
											}
										}
									}
									case '_' | 0x20:
									{
										switch (str[9] | 0x20)
										{
											case '1':
											{
												idx += 10;
												return X11_SKY_BLUE_1;
											}
											case '2':
											{
												idx += 10;
												return X11_SKY_BLUE_2;
											}
											case '3':
											{
												idx += 10;
												return X11_SKY_BLUE_3;
											}
											case '4':
											{
												idx += 10;
												return X11_SKY_BLUE_4;
											}
										}
									}
								}
								idx += 8;
								return X11_SKY_BLUE;
							}
						}
						case '_' | 0x20:
						{
							if (!str[4] || strcmp(str[4], !"BLUE", true, 4))
							{
								return -1;
							}
							switch (str[8] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[8])
									{
										switch (str[9] | 0x20)
										{
											case '1':
											{
												idx += 10;
												return X11_SKY_BLUE_1;
											}
											case '2':
											{
												idx += 10;
												return X11_SKY_BLUE_2;
											}
											case '3':
											{
												idx += 10;
												return X11_SKY_BLUE_3;
											}
											case '4':
											{
												idx += 10;
												return X11_SKY_BLUE_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[9] | 0x20)
									{
										case '1':
										{
											idx += 10;
											return X11_SKY_BLUE_1;
										}
										case '2':
										{
											idx += 10;
											return X11_SKY_BLUE_2;
										}
										case '3':
										{
											idx += 10;
											return X11_SKY_BLUE_3;
										}
										case '4':
										{
											idx += 10;
											return X11_SKY_BLUE_4;
										}
									}
								}
							}
							idx += 8;
							return X11_SKY_BLUE;
						}
						case 'b':
						{
							if (!str[4] || strcmp(str[4], !"LUE", true, 3))
							{
								return -1;
							}
							switch (str[7] | 0x20)
							{
								case '1':
								{
									idx += 8;
									return X11_SKYBLUE1;
								}
								case '2':
								{
									idx += 8;
									return X11_SKYBLUE2;
								}
								case '3':
								{
									idx += 8;
									return X11_SKYBLUE3;
								}
								case '4':
								{
									idx += 8;
									return X11_SKYBLUE4;
								}
							}
							idx += 7;
							return X11_SKYBLUE;
						}
					}
				}
				case 'l':
				{
					if (!str[2] || strcmp(str[2], !"ATE", true, 3))
					{
						return -1;
					}
					switch (str[5] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[5])
							{
								switch (str[6] | 0x20)
								{
									case 'b':
									{
										if (!str[7] || strcmp(str[7], !"LUE", true, 3))
										{
											return -1;
										}
										switch (str[10] | 0x20)
										{
											case _X11_SPACE_SWITCH: // ' '
											{
												if (str[10])
												{
													switch (str[11] | 0x20)
													{
														case '1':
														{
															idx += 12;
															return X11_SLATE_BLUE_1;
														}
														case '2':
														{
															idx += 12;
															return X11_SLATE_BLUE_2;
														}
														case '3':
														{
															idx += 12;
															return X11_SLATE_BLUE_3;
														}
														case '4':
														{
															idx += 12;
															return X11_SLATE_BLUE_4;
														}
													}
												}
											}
											case '_' | 0x20:
											{
												switch (str[11] | 0x20)
												{
													case '1':
													{
														idx += 12;
														return X11_SLATE_BLUE_1;
													}
													case '2':
													{
														idx += 12;
														return X11_SLATE_BLUE_2;
													}
													case '3':
													{
														idx += 12;
														return X11_SLATE_BLUE_3;
													}
													case '4':
													{
														idx += 12;
														return X11_SLATE_BLUE_4;
													}
												}
											}
										}
										idx += 10;
										return X11_SLATE_BLUE;
									}
									case 'g':
									{
										if (str[7] | 0x20 != 'r')
										{
											return -1;
										}
										switch (str[8] | 0x20)
										{
											case 'a':
											{
												if (str[9] | 0x20 != 'y')
												{
													return -1;
												}
												switch (str[10] | 0x20)
												{
													case _X11_SPACE_SWITCH: // ' '
													{
														if (str[10])
														{
															switch (str[11] | 0x20)
															{
																case '1':
																{
																	idx += 12;
																	return X11_SLATE_GRAY_1;
																}
																case '2':
																{
																	idx += 12;
																	return X11_SLATE_GRAY_2;
																}
																case '3':
																{
																	idx += 12;
																	return X11_SLATE_GRAY_3;
																}
																case '4':
																{
																	idx += 12;
																	return X11_SLATE_GRAY_4;
																}
															}
														}
													}
													case '_' | 0x20:
													{
														switch (str[11] | 0x20)
														{
															case '1':
															{
																idx += 12;
																return X11_SLATE_GRAY_1;
															}
															case '2':
															{
																idx += 12;
																return X11_SLATE_GRAY_2;
															}
															case '3':
															{
																idx += 12;
																return X11_SLATE_GRAY_3;
															}
															case '4':
															{
																idx += 12;
																return X11_SLATE_GRAY_4;
															}
														}
													}
												}
												idx += 10;
												return X11_SLATE_GRAY;
											}
											case 'e':
											{
												if (str[9] | 0x20 != 'y')
												{
													return -1;
												}
												switch (str[10] | 0x20)
												{
													case _X11_SPACE_SWITCH: // ' '
													{
														if (str[10])
														{
															switch (str[11] | 0x20)
															{
																case '1':
																{
																	idx += 12;
																	return X11_SLATE_GREY_1;
																}
																case '2':
																{
																	idx += 12;
																	return X11_SLATE_GREY_2;
																}
																case '3':
																{
																	idx += 12;
																	return X11_SLATE_GREY_3;
																}
																case '4':
																{
																	idx += 12;
																	return X11_SLATE_GREY_4;
																}
															}
														}
													}
													case '_' | 0x20:
													{
														switch (str[11] | 0x20)
														{
															case '1':
															{
																idx += 12;
																return X11_SLATE_GREY_1;
															}
															case '2':
															{
																idx += 12;
																return X11_SLATE_GREY_2;
															}
															case '3':
															{
																idx += 12;
																return X11_SLATE_GREY_3;
															}
															case '4':
															{
																idx += 12;
																return X11_SLATE_GREY_4;
															}
														}
													}
												}
												idx += 10;
												return X11_SLATE_GREY;
											}
										}
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[6] | 0x20)
							{
								case 'b':
								{
									if (!str[7] || strcmp(str[7], !"LUE", true, 3))
									{
										return -1;
									}
									switch (str[10] | 0x20)
									{
										case _X11_SPACE_SWITCH: // ' '
										{
											if (str[10])
											{
												switch (str[11] | 0x20)
												{
													case '1':
													{
														idx += 12;
														return X11_SLATE_BLUE_1;
													}
													case '2':
													{
														idx += 12;
														return X11_SLATE_BLUE_2;
													}
													case '3':
													{
														idx += 12;
														return X11_SLATE_BLUE_3;
													}
													case '4':
													{
														idx += 12;
														return X11_SLATE_BLUE_4;
													}
												}
											}
										}
										case '_' | 0x20:
										{
											switch (str[11] | 0x20)
											{
												case '1':
												{
													idx += 12;
													return X11_SLATE_BLUE_1;
												}
												case '2':
												{
													idx += 12;
													return X11_SLATE_BLUE_2;
												}
												case '3':
												{
													idx += 12;
													return X11_SLATE_BLUE_3;
												}
												case '4':
												{
													idx += 12;
													return X11_SLATE_BLUE_4;
												}
											}
										}
									}
									idx += 10;
									return X11_SLATE_BLUE;
								}
								case 'g':
								{
									if (str[7] | 0x20 != 'r')
									{
										return -1;
									}
									switch (str[8] | 0x20)
									{
										case 'a':
										{
											if (str[9] | 0x20 != 'y')
											{
												return -1;
											}
											switch (str[10] | 0x20)
											{
												case _X11_SPACE_SWITCH: // ' '
												{
													if (str[10])
													{
														switch (str[11] | 0x20)
														{
															case '1':
															{
																idx += 12;
																return X11_SLATE_GRAY_1;
															}
															case '2':
															{
																idx += 12;
																return X11_SLATE_GRAY_2;
															}
															case '3':
															{
																idx += 12;
																return X11_SLATE_GRAY_3;
															}
															case '4':
															{
																idx += 12;
																return X11_SLATE_GRAY_4;
															}
														}
													}
												}
												case '_' | 0x20:
												{
													switch (str[11] | 0x20)
													{
														case '1':
														{
															idx += 12;
															return X11_SLATE_GRAY_1;
														}
														case '2':
														{
															idx += 12;
															return X11_SLATE_GRAY_2;
														}
														case '3':
														{
															idx += 12;
															return X11_SLATE_GRAY_3;
														}
														case '4':
														{
															idx += 12;
															return X11_SLATE_GRAY_4;
														}
													}
												}
											}
											idx += 10;
											return X11_SLATE_GRAY;
										}
										case 'e':
										{
											if (str[9] | 0x20 != 'y')
											{
												return -1;
											}
											switch (str[10] | 0x20)
											{
												case _X11_SPACE_SWITCH: // ' '
												{
													if (str[10])
													{
														switch (str[11] | 0x20)
														{
															case '1':
															{
																idx += 12;
																return X11_SLATE_GREY_1;
															}
															case '2':
															{
																idx += 12;
																return X11_SLATE_GREY_2;
															}
															case '3':
															{
																idx += 12;
																return X11_SLATE_GREY_3;
															}
															case '4':
															{
																idx += 12;
																return X11_SLATE_GREY_4;
															}
														}
													}
												}
												case '_' | 0x20:
												{
													switch (str[11] | 0x20)
													{
														case '1':
														{
															idx += 12;
															return X11_SLATE_GREY_1;
														}
														case '2':
														{
															idx += 12;
															return X11_SLATE_GREY_2;
														}
														case '3':
														{
															idx += 12;
															return X11_SLATE_GREY_3;
														}
														case '4':
														{
															idx += 12;
															return X11_SLATE_GREY_4;
														}
													}
												}
											}
											idx += 10;
											return X11_SLATE_GRAY;
										}
									}
								}
							}
						}
						case 'b':
						{
							if (!str[6] || strcmp(str[6], !"LUE", true, 3))
							{
								return -1;
							}
							switch (str[9] | 0x20)
							{
								case '1':
								{
									idx += 10;
									return X11_SLATEBLUE1;
								}
								case '2':
								{
									idx += 10;
									return X11_SLATEBLUE2;
								}
								case '3':
								{
									idx += 10;
									return X11_SLATEBLUE3;
								}
								case '4':
								{
									idx += 10;
									return X11_SLATEBLUE4;
								}
							}
							idx += 9;
							return X11_SLATEBLUE;
						}
						case 'g':
						{
							if (str[6] | 0x20 != 'r')
							{
								return -1;
							}
							switch (str[7] | 0x20)
							{
								case 'a':
								{
									if (str[8] | 0x20 != 'y')
									{
										return -1;
									}
									switch (str[9] | 0x20)
									{
										case '1':
										{
											idx += 10;
											return X11_SLATEGRAY1;
										}
										case '2':
										{
											idx += 10;
											return X11_SLATEGRAY2;
										}
										case '3':
										{
											idx += 10;
											return X11_SLATEGRAY3;
										}
										case '4':
										{
											idx += 10;
											return X11_SLATEGRAY4;
										}
									}
									idx += 9;
									return X11_SLATEGRAY;
								}
								case 'e':
								{
									if (str[8] | 0x20 != 'y')
									{
										return -1;
									}
									switch (str[9] | 0x20)
									{
										case '1':
										{
											idx += 10;
											return X11_SLATEGREY1;
										}
										case '2':
										{
											idx += 10;
											return X11_SLATEGREY2;
										}
										case '3':
										{
											idx += 10;
											return X11_SLATEGREY3;
										}
										case '4':
										{
											idx += 10;
											return X11_SLATEGREY4;
										}
									}
									idx += 9;
									return X11_SLATEGREY;
								}
							}
						}
					}
				}
				case 'n':
				{
					if (!str[2] || strcmp(str[2], !"OW", true, 2))
					{
						return -1;
					}
					switch (str[4] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[4])
							{
								switch (str[5] | 0x20)
								{
									case '1':
									{
										idx += 6;
										return X11_SNOW_1;
									}
									case '2':
									{
										idx += 6;
										return X11_SNOW_2;
									}
									case '3':
									{
										idx += 6;
										return X11_SNOW_3;
									}
									case '4':
									{
										idx += 6;
										return X11_SNOW_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[5] | 0x20)
							{
								case '1':
								{
									idx += 6;
									return X11_SNOW_1;
								}
								case '2':
								{
									idx += 6;
									return X11_SNOW_2;
								}
								case '3':
								{
									idx += 6;
									return X11_SNOW_3;
								}
								case '4':
								{
									idx += 6;
									return X11_SNOW_4;
								}
							}
						}
						case '1':
						{
							idx += 5;
							return X11_SNOW1;
						}
						case '2':
						{
							idx += 5;
							return X11_SNOW2;
						}
						case '3':
						{
							idx += 5;
							return X11_SNOW3;
						}
						case '4':
						{
							idx += 5;
							return X11_SNOW4;
						}
					}
					idx += 4;
					return X11_SNOW;
				}
				case 'p':
				{
					if (!str[2] || strcmp(str[2], !"RING", true, 4))
					{
						return -1;
					}
					switch (str[6] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[6])
							{
								if (!str[7] || strcmp(str[7], !"GREEN", true, 5))
								{
									return -1;
								}
								switch (str[12] | 0x20)
								{
									case _X11_SPACE_SWITCH: // ' '
									{
										if (str[12])
										{
											switch (str[13] | 0x20)
											{
												case '1':
												{
													idx += 14;
													return X11_SPRING_GREEN_1;
												}
												case '2':
												{
													idx += 14;
													return X11_SPRING_GREEN_2;
												}
												case '3':
												{
													idx += 14;
													return X11_SPRING_GREEN_3;
												}
												case '4':
												{
													idx += 14;
													return X11_SPRING_GREEN_4;
												}
											}
										}
									}
									case '_' | 0x20:
									{
										switch (str[13] | 0x20)
										{
											case '1':
											{
												idx += 14;
												return X11_SPRING_GREEN_1;
											}
											case '2':
											{
												idx += 14;
												return X11_SPRING_GREEN_2;
											}
											case '3':
											{
												idx += 14;
												return X11_SPRING_GREEN_3;
											}
											case '4':
											{
												idx += 14;
												return X11_SPRING_GREEN_4;
											}
										}
									}
								}
								idx += 12;
								return X11_SPRING_GREEN;
							}
						}
						case '_' | 0x20:
						{
							if (!str[7] || strcmp(str[7], !"GREEN", true, 5))
							{
								return -1;
							}
							switch (str[12] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[12])
									{
										switch (str[13] | 0x20)
										{
											case '1':
											{
												idx += 14;
												return X11_SPRING_GREEN_1;
											}
											case '2':
											{
												idx += 14;
												return X11_SPRING_GREEN_2;
											}
											case '3':
											{
												idx += 14;
												return X11_SPRING_GREEN_3;
											}
											case '4':
											{
												idx += 14;
												return X11_SPRING_GREEN_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[13] | 0x20)
									{
										case '1':
										{
											idx += 14;
											return X11_SPRING_GREEN_1;
										}
										case '2':
										{
											idx += 14;
											return X11_SPRING_GREEN_2;
										}
										case '3':
										{
											idx += 14;
											return X11_SPRING_GREEN_3;
										}
										case '4':
										{
											idx += 14;
											return X11_SPRING_GREEN_4;
										}
									}
								}
							}
							idx += 12;
							return X11_SPRING_GREEN;
						}
						case 'g':
						{
							if (!str[7] || strcmp(str[7], !"REEN", true, 4))
							{
								return -1;
							}
							switch (str[11] | 0x20)
							{
								case '1':
								{
									idx += 12;
									return X11_SPRINGGREEN1;
								}
								case '2':
								{
									idx += 12;
									return X11_SPRINGGREEN2;
								}
								case '3':
								{
									idx += 12;
									return X11_SPRINGGREEN3;
								}
								case '4':
								{
									idx += 12;
									return X11_SPRINGGREEN4;
								}
							}
							idx += 11;
							return X11_SPRINGGREEN;
						}
					}
				}
				case 't':
				{
					if (!str[2] || strcmp(str[2], !"EEL", true, 3))
					{
						return -1;
					}
					switch (str[5] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[5])
							{
								if (!str[6] || strcmp(str[6], !"BLUE", true, 4))
								{
									return -1;
								}
								switch (str[10] | 0x20)
								{
									case _X11_SPACE_SWITCH: // ' '
									{
										if (str[10])
										{
											switch (str[11] | 0x20)
											{
												case '1':
												{
													idx += 12;
													return X11_STEEL_BLUE_1;
												}
												case '2':
												{
													idx += 12;
													return X11_STEEL_BLUE_2;
												}
												case '3':
												{
													idx += 12;
													return X11_STEEL_BLUE_3;
												}
												case '4':
												{
													idx += 12;
													return X11_STEEL_BLUE_4;
												}
											}
										}
									}
									case '_' | 0x20:
									{
										switch (str[11] | 0x20)
										{
											case '1':
											{
												idx += 12;
												return X11_STEEL_BLUE_1;
											}
											case '2':
											{
												idx += 12;
												return X11_STEEL_BLUE_2;
											}
											case '3':
											{
												idx += 12;
												return X11_STEEL_BLUE_3;
											}
											case '4':
											{
												idx += 12;
												return X11_STEEL_BLUE_4;
											}
										}
									}
								}
								idx += 10;
								return X11_STEEL_BLUE;
							}
						}
						case '_' | 0x20:
						{
							if (!str[6] || strcmp(str[6], !"BLUE", true, 4))
							{
								return -1;
							}
							switch (str[10] | 0x20)
							{
								case _X11_SPACE_SWITCH: // ' '
								{
									if (str[10])
									{
										switch (str[11] | 0x20)
										{
											case '1':
											{
												idx += 12;
												return X11_STEEL_BLUE_1;
											}
											case '2':
											{
												idx += 12;
												return X11_STEEL_BLUE_2;
											}
											case '3':
											{
												idx += 12;
												return X11_STEEL_BLUE_3;
											}
											case '4':
											{
												idx += 12;
												return X11_STEEL_BLUE_4;
											}
										}
									}
								}
								case '_' | 0x20:
								{
									switch (str[11] | 0x20)
									{
										case '1':
										{
											idx += 12;
											return X11_STEEL_BLUE_1;
										}
										case '2':
										{
											idx += 12;
											return X11_STEEL_BLUE_2;
										}
										case '3':
										{
											idx += 12;
											return X11_STEEL_BLUE_3;
										}
										case '4':
										{
											idx += 12;
											return X11_STEEL_BLUE_4;
										}
									}
								}
							}
							idx += 10;
							return X11_STEEL_BLUE;
						}
						case 'b':
						{
							if (!str[6] || strcmp(str[6], !"LUE", true, 3))
							{
								return -1;
							}
							switch (str[9] | 0x20)
							{
								case '1':
								{
									idx += 10;
									return X11_STEELBLUE1;
								}
								case '2':
								{
									idx += 10;
									return X11_STEELBLUE2;
								}
								case '3':
								{
									idx += 10;
									return X11_STEELBLUE3;
								}
								case '4':
								{
									idx += 10;
									return X11_STEELBLUE4;
								}
							}
							idx += 9;
							return X11_STEELBLUE;
						}
					}
				}
			}
		}
		case 't':
		{
			switch (str[1] | 0x20)
			{
				case 'a':
				{
					if (str[2] | 0x20 != 'n')
					{
						return -1;
					}
					switch (str[3] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[3])
							{
								switch (str[4] | 0x20)
								{
									case '1':
									{
										idx += 5;
										return X11_TAN_1;
									}
									case '2':
									{
										idx += 5;
										return X11_TAN_2;
									}
									case '3':
									{
										idx += 5;
										return X11_TAN_3;
									}
									case '4':
									{
										idx += 5;
										return X11_TAN_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[4] | 0x20)
							{
								case '1':
								{
									idx += 5;
									return X11_TAN_1;
								}
								case '2':
								{
									idx += 5;
									return X11_TAN_2;
								}
								case '3':
								{
									idx += 5;
									return X11_TAN_3;
								}
								case '4':
								{
									idx += 5;
									return X11_TAN_4;
								}
							}
						}
						case '1':
						{
							idx += 4;
							return X11_TAN1;
						}
						case '2':
						{
							idx += 4;
							return X11_TAN2;
						}
						case '3':
						{
							idx += 4;
							return X11_TAN3;
						}
						case '4':
						{
							idx += 4;
							return X11_TAN4;
						}
					}
					idx += 3;
					return X11_TAN;
				}
				case 'h':
				{
					if (!str[2] || strcmp(str[2], !"ISTLE", true, 5))
					{
						return -1;
					}
					switch (str[7] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[7])
							{
								switch (str[8] | 0x20)
								{
									case '1':
									{
										idx += 9;
										return X11_THISTLE_1;
									}
									case '2':
									{
										idx += 9;
										return X11_THISTLE_2;
									}
									case '3':
									{
										idx += 9;
										return X11_THISTLE_3;
									}
									case '4':
									{
										idx += 9;
										return X11_THISTLE_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[8] | 0x20)
							{
								case '1':
								{
									idx += 9;
									return X11_THISTLE_1;
								}
								case '2':
								{
									idx += 9;
									return X11_THISTLE_2;
								}
								case '3':
								{
									idx += 9;
									return X11_THISTLE_3;
								}
								case '4':
								{
									idx += 9;
									return X11_THISTLE_4;
								}
							}
						}
						case '1':
						{
							idx += 8;
							return X11_THISTLE1;
						}
						case '2':
						{
							idx += 8;
							return X11_THISTLE2;
						}
						case '3':
						{
							idx += 8;
							return X11_THISTLE3;
						}
						case '4':
						{
							idx += 8;
							return X11_THISTLE4;
						}
					}
					idx += 7;
					return X11_THISTLE;
				}
				case 'o':
				{
					if (!str[2] || strcmp(str[2], !"MATO", true, 4))
					{
						return -1;
					}
					switch (str[6] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[6])
							{
								switch (str[7] | 0x20)
								{
									case '1':
									{
										idx += 8;
										return X11_TOMATO_1;
									}
									case '2':
									{
										idx += 8;
										return X11_TOMATO_2;
									}
									case '3':
									{
										idx += 8;
										return X11_TOMATO_3;
									}
									case '4':
									{
										idx += 8;
										return X11_TOMATO_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[7] | 0x20)
							{
								case '1':
								{
									idx += 8;
									return X11_TOMATO_1;
								}
								case '2':
								{
									idx += 8;
									return X11_TOMATO_2;
								}
								case '3':
								{
									idx += 8;
									return X11_TOMATO_3;
								}
								case '4':
								{
									idx += 8;
									return X11_TOMATO_4;
								}
							}
						}
						case '1':
						{
							idx += 7;
							return X11_TOMATO1;
						}
						case '2':
						{
							idx += 7;
							return X11_TOMATO2;
						}
						case '3':
						{
							idx += 7;
							return X11_TOMATO3;
						}
						case '4':
						{
							idx += 7;
							return X11_TOMATO4;
						}
					}
					idx += 6;
					return X11_TOMATO;
				}
				case 'u':
				{
					if (!str[2] || strcmp(str[2], !"RQUOISE", true, 7))
					{
						return -1;
					}
					switch (str[9] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[9])
							{
								switch (str[10] | 0x20)
								{
									case '1':
									{
										idx += 11;
										return X11_TURQUOISE_1;
									}
									case '2':
									{
										idx += 11;
										return X11_TURQUOISE_2;
									}
									case '3':
									{
										idx += 11;
										return X11_TURQUOISE_3;
									}
									case '4':
									{
										idx += 11;
										return X11_TURQUOISE_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[10] | 0x20)
							{
								case '1':
								{
									idx += 11;
									return X11_TURQUOISE_1;
								}
								case '2':
								{
									idx += 11;
									return X11_TURQUOISE_2;
								}
								case '3':
								{
									idx += 11;
									return X11_TURQUOISE_3;
								}
								case '4':
								{
									idx += 11;
									return X11_TURQUOISE_4;
								}
							}
						}
						case '1':
						{
							idx += 10;
							return X11_TURQUOISE1;
						}
						case '2':
						{
							idx += 10;
							return X11_TURQUOISE2;
						}
						case '3':
						{
							idx += 10;
							return X11_TURQUOISE3;
						}
						case '4':
						{
							idx += 10;
							return X11_TURQUOISE4;
						}
					}
					idx += 9;
					return X11_TURQUOISE;
				}
			}
		}
		case 'v':
		{
			if (!str[1] || strcmp(str[1], !"IOLET", true, 5))
			{
				return -1;
			}
			switch (str[6] | 0x20)
			{
				case _X11_SPACE_SWITCH: // ' '
				{
					if (str[6])
					{
						if (!str[7] || strcmp(str[7], !"RED", true, 3))
						{
							return -1;
						}
						switch (str[10] | 0x20)
						{
							case _X11_SPACE_SWITCH: // ' '
							{
								if (str[10])
								{
									switch (str[11] | 0x20)
									{
										case '1':
										{
											idx += 12;
											return X11_VIOLET_RED_1;
										}
										case '2':
										{
											idx += 12;
											return X11_VIOLET_RED_2;
										}
										case '3':
										{
											idx += 12;
											return X11_VIOLET_RED_3;
										}
										case '4':
										{
											idx += 12;
											return X11_VIOLET_RED_4;
										}
									}
								}
							}
							case '_' | 0x20:
							{
								switch (str[11] | 0x20)
								{
									case '1':
									{
										idx += 12;
										return X11_VIOLET_RED_1;
									}
									case '2':
									{
										idx += 12;
										return X11_VIOLET_RED_2;
									}
									case '3':
									{
										idx += 12;
										return X11_VIOLET_RED_3;
									}
									case '4':
									{
										idx += 12;
										return X11_VIOLET_RED_4;
									}
								}
							}
						}
						idx += 10;
						return X11_VIOLET_RED;
					}
				}
				case '_' | 0x20:
				{
					if (!str[7] || strcmp(str[7], !"RED", true, 3))
					{
						return -1;
					}
					switch (str[10] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[10])
							{
								switch (str[11] | 0x20)
								{
									case '1':
									{
										idx += 12;
										return X11_VIOLET_RED_1;
									}
									case '2':
									{
										idx += 12;
										return X11_VIOLET_RED_2;
									}
									case '3':
									{
										idx += 12;
										return X11_VIOLET_RED_3;
									}
									case '4':
									{
										idx += 12;
										return X11_VIOLET_RED_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[11] | 0x20)
							{
								case '1':
								{
									idx += 12;
									return X11_VIOLET_RED_1;
								}
								case '2':
								{
									idx += 12;
									return X11_VIOLET_RED_2;
								}
								case '3':
								{
									idx += 12;
									return X11_VIOLET_RED_3;
								}
								case '4':
								{
									idx += 12;
									return X11_VIOLET_RED_4;
								}
							}
						}
					}
					idx += 10;
					return X11_VIOLET_RED;
				}
				case 'r':
				{
					if (!str[7] || strcmp(str[7], !"ED", true, 2))
					{
						return -1;
					}
					switch (str[9] | 0x20)
					{
						case '1':
						{
							idx += 10;
							return X11_VIOLETRED1;
						}
						case '2':
						{
							idx += 10;
							return X11_VIOLETRED2;
						}
						case '3':
						{
							idx += 10;
							return X11_VIOLETRED3;
						}
						case '4':
						{
							idx += 10;
							return X11_VIOLETRED4;
						}
					}
					idx += 9;
					return X11_VIOLETRED;
				}
			}
			idx += 6;
			return X11_VIOLET;
		}
		case 'w':
		{
			if (str[1] | 0x20 != 'h')
			{
				return -1;
			}
			switch (str[2] | 0x20)
			{
				case 'e':
				{
					if (!str[3] || strcmp(str[3], !"AT", true, 2))
					{
						return -1;
					}
					switch (str[5] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[5])
							{
								switch (str[6] | 0x20)
								{
									case '1':
									{
										idx += 7;
										return X11_WHEAT_1;
									}
									case '2':
									{
										idx += 7;
										return X11_WHEAT_2;
									}
									case '3':
									{
										idx += 7;
										return X11_WHEAT_3;
									}
									case '4':
									{
										idx += 7;
										return X11_WHEAT_4;
									}
								}
							}
						}
						case '_' | 0x20:
						{
							switch (str[6] | 0x20)
							{
								case '1':
								{
									idx += 7;
									return X11_WHEAT_1;
								}
								case '2':
								{
									idx += 7;
									return X11_WHEAT_2;
								}
								case '3':
								{
									idx += 7;
									return X11_WHEAT_3;
								}
								case '4':
								{
									idx += 7;
									return X11_WHEAT_4;
								}
							}
						}
						case '1':
						{
							idx += 6;
							return X11_WHEAT1;
						}
						case '2':
						{
							idx += 6;
							return X11_WHEAT2;
						}
						case '3':
						{
							idx += 6;
							return X11_WHEAT3;
						}
						case '4':
						{
							idx += 6;
							return X11_WHEAT4;
						}
					}
					idx += 5;
					return X11_WHEAT;
				}
				case 'i':
				{
					if (!str[3] || strcmp(str[3], !"TE", true, 2))
					{
						return -1;
					}
					switch (str[5] | 0x20)
					{
						case _X11_SPACE_SWITCH: // ' '
						{
							if (str[5])
							{
								if (str[6] && !strcmp(str[6], !"SMOKE", true, 5))
								{
									idx += 11;
									return X11_WHITE_SMOKE;
								}
							}
						}
						case '_' | 0x20:
						{
							if (str[6] && !strcmp(str[6], !"SMOKE", true, 5))
							{
								idx += 11;
								return X11_WHITE_SMOKE;
							}
						}
						case 's':
						{
							if (str[6] && !strcmp(str[6], !"MOKE", true, 4))
							{
								idx += 10;
								return X11_WHITESMOKE;
							}
						}
					}
					idx += 5;
					return X11_WHITE;
				}
			}
		}
		case 'y':
		{
			if (!str[1] || strcmp(str[1], !"ELLOW", true, 5))
			{
				return -1;
			}
			switch (str[6] | 0x20)
			{
				case _X11_SPACE_SWITCH: // ' '
				{
					if (str[6])
					{
						switch (str[7] | 0x20)
						{
							case '1':
							{
								idx += 8;
								return X11_YELLOW_1;
							}
							case '2':
							{
								idx += 8;
								return X11_YELLOW_2;
							}
							case '3':
							{
								idx += 8;
								return X11_YELLOW_3;
							}
							case '4':
							{
								idx += 8;
								return X11_YELLOW_4;
							}
							case 'g':
							{
								if (str[8] && !strcmp(str[8], !"REEN", true, 4))
								{
									idx += 12;
									return X11_YELLOW_GREEN;
								}
							}
						}
					}
				}
				case '_' | 0x20:
				{
					switch (str[7] | 0x20)
					{
						case '1':
						{
							idx += 8;
							return X11_YELLOW_1;
						}
						case '2':
						{
							idx += 8;
							return X11_YELLOW_2;
						}
						case '3':
						{
							idx += 8;
							return X11_YELLOW_3;
						}
						case '4':
						{
							idx += 8;
							return X11_YELLOW_4;
						}
						case 'g':
						{
							if (str[8] && !strcmp(str[8], !"REEN", true, 4))
							{
								idx += 12;
								return X11_YELLOW_GREEN;
							}
						}
					}
				}
				case '1':
				{
					idx += 7;
					return X11_YELLOW1;
				}
				case '2':
				{
					idx += 7;
					return X11_YELLOW2;
				}
				case '3':
				{
					idx += 7;
					return X11_YELLOW3;
				}
				case '4':
				{
					idx += 7;
					return X11_YELLOW4;
				}
				case 'g':
				{
					if (str[7] && !strcmp(str[7], !"REEN", true, 4))
					{
						idx += 11;
						return X11_YELLOWGREEN;
					}
				}
			}
			idx += 6;
			return X11_YELLOW;
		}
	}
