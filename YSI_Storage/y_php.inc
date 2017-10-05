#if defined _INC_y_php
	#endinput
#endif
#define _INC_y_php

/**
 * <library name="y_php">
 * <section>
 *  Description
 * </section>
 *  Sends and receives data from a PHP server with shmop installed.
 * <section>
 *  Version
 * </section>
 *  0.1
 * </library>
 *//** *//*
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

#if !defined HTTP
	#include <a_http>
#endif

#include "..\YSI_Core\y_utils"
#include "..\YSI_Internal\y_funcinc"
#include "..\YSI_Core\y_debug"
#include "..\YSI_Coding\y_timers"
#include "..\YSI_Coding\y_hooks"

#if !defined PHP_RECEIVE || !defined PHP_SEND
	#error You must define PHP_RECEIVE and PHP_SEND before including y_php.
#endif

#define PHP_HEADER_LENGTH (3)

static stock
	YSI_g_sID = 0,
	//YSI_g_sLen,
	YSI_g_sIndex = PHP_HEADER_LENGTH,
	YSI_g_sBuffer[2048] = "DR=";

/*
native PHP_SendString(string:name[], string:value[], bool:priority = false);
native PHP_SendFloat(string:name[], Float:value, bool:priority = false);
native PHP_SendBool(string:name[], bool:value, bool:priority = false);
native PHP_SendInt(string:name[], value, bool:priority = false);
*/

enum
{
	e_PHP_SEND_TYPE_STRING,
	e_PHP_SEND_TYPE_FLOAT,
	e_PHP_SEND_TYPE_BOOL,
	e_PHP_SEND_TYPE_INT
}

forward _PHP_Result(index, response, data[]);
forward _PHP_Ignore(index, response, data[]);

stock PHP_SendString(string:name[], string:value[], bool:priority = false)
{
	if (isnull(value))
	{
		return _PHP_Send(name, NULL, priority, e_PHP_SEND_TYPE_STRING);
	}
	else
	{
		return _PHP_Send(name, value, priority, e_PHP_SEND_TYPE_STRING);
	}
}

stock PHP_SendFloat(string:name[], Float:value, bool:priority = false)
{
	static
		sStr[6];
	PHP_EncodeFloat(_:value, sStr);
	return _PHP_Send(name, sStr, priority,  e_PHP_SEND_TYPE_FLOAT);
}

stock PHP_SendBool(string:name[], bool:value, bool:priority = false)
{
	if (value)
	{
		return _PHP_Send(name, "1", priority, e_PHP_SEND_TYPE_BOOL);
	}
	else
	{
		return _PHP_Send(name, "0", priority, e_PHP_SEND_TYPE_BOOL);
	}
}

stock PHP_SendInt(string:name[], value, bool:priority = false)
{
	static
		sStr[6];
	PHP_EncodeInt(value, sStr);
	return _PHP_Send(name, sStr, priority, e_PHP_SEND_TYPE_INT);
}

static stock _PHP_Send(string:name[], string:value[], bool:priority, type)
{
	new
		nlen = strlen(name);
	// Only loops twice max in reality.
	for ( ; ; )
	{
		switch (type)
		{
			case e_PHP_SEND_TYPE_STRING:
			{
				new
					vlen = strlen(value);
				if (vlen + nlen + 7 + YSI_g_sIndex < sizeof (YSI_g_sBuffer))
				{
					static
						sStr[6];
					PHP_EncodeInt(vlen, sStr);
					format(YSI_g_sBuffer[YSI_g_sIndex], sizeof (YSI_g_sBuffer), "%c%s%s%s%c", nlen | 0x80, name, sStr, value, 255);
					YSI_g_sIndex += vlen + nlen + 7;
					if (priority)
					{
						_PHP_ForceSend();
					}
					return 1;
				}
			}
			case e_PHP_SEND_TYPE_FLOAT, e_PHP_SEND_TYPE_INT:
			{
				if (nlen + 7 + YSI_g_sIndex < sizeof (YSI_g_sBuffer))
				{
					format(YSI_g_sBuffer[YSI_g_sIndex], sizeof (YSI_g_sBuffer), "%c%s%s%c", nlen | 0x80, name, value, 255);
					YSI_g_sIndex += nlen + 7;
					if (priority)
					{
						_PHP_ForceSend();
					}
					return 1;
				}
			}
			case e_PHP_SEND_TYPE_BOOL:
			{
				if (nlen + 2 + YSI_g_sIndex < sizeof (YSI_g_sBuffer))
				{
					format(YSI_g_sBuffer[YSI_g_sIndex], sizeof (YSI_g_sBuffer), "%c%s%c", nlen | 0x80, name, value[0]);
					YSI_g_sIndex += nlen + 2;
					if (priority)
					{
						_PHP_ForceSend();
					}
					return 1;
				}
			}
		}
		// Not enough space in the buffer.  Send the existing data, reset
		// "YSI_g_sIndex", and try again (just once).
		if (YSI_g_sIndex > PHP_HEADER_LENGTH)
		{
			_PHP_ForceSend();
		}
		else
		{
			break;
		}
	}
	return 0;
}

task _PHP_ForceSend[5000]()
{
	// This is run in all scripts, not just the master one, because there is no
	// "mtask".  In retrospect, that seems like an oversight.
	if (YSI_g_sIndex > PHP_HEADER_LENGTH)
	{
		// Send the data.
		HTTP(0, HTTP_POST, PHP_SEND, YSI_g_sBuffer, "_PHP_Ignore");
		YSI_g_sIndex = PHP_HEADER_LENGTH;
		// I don't think this is actually REQUIRED, but does no harm.
		YSI_g_sBuffer[PHP_HEADER_LENGTH] = '\0';
	}
}

static stock PHP_EncodeInt(value, dest[])
{
	dest[0] = (value >> 25 & 0x7F | 0x80);
	dest[1] = (value >> 18 & 0x7F | 0x80);
	dest[2] = (value >> 11 & 0x7F | 0x80);
	dest[3] = (value >> 4 & 0x7F | 0x80);
	dest[4] = (value & 0x0F | 0x80);
}

static stock PHP_EncodeFloat(value, dest[])
{
	dest[0] = (value >> 25 & 0x7F | 0x80);
	dest[1] = (value >> 18 & 0x7F | 0x80);
	dest[2] = (value >> 11 & 0x7F | 0x80);
	dest[3] = (value >> 4 & 0x7F | 0x80);
	// This is the only difference from "PHP_EncodeInt" (0x80 vs 0xC0).
	dest[4] = (value & 0x0F | 0xC0);
}

mhook OnScriptInit()
{
	if (!strcmp(PHP_RECEIVE, "http://", true, 7))
	{
		P:E("PHP_RECEIVE should exclude \"http://\".");
	}
	P:I("Starting PHP Connection...");
	P:I("Note that messages may take a few seconds to get going.");
	//YSI_g_sLen = strlen(PHP_RECEIVE) + 4;
	//SetTimer("_PHP_FireOne", 50, 0);
	// Send '0' only once at server start to reset PHP.
	HTTP(0, HTTP_HEAD, PHP_RECEIVE "?ID=0", "", "_PHP_Result");
	//new TODO;
	defer _PHP_FireOne[500](0, 0);
	defer _PHP_FireOne[5500](0, 0);
	//SetTimer("_PHP_FireOne", 500, 0);
	//SetTimer("_PHP_FireOne", 5500, 0);
	//PHP_FireOne();
	//PHP_FireOne();
	//PHP_FireOne();
	return 1;
}

timer _PHP_FireOne[10](res, to)
{
	static
		sAddr[64]; // = PHP_RECEIVE "?ID=?????&RE=???????????";
	YSI_g_sID = (YSI_g_sID + 1) & 0xFFFF;
	if (YSI_g_sID == 0) YSI_g_sID = 1;
	//valstr(sAddr[YSI_g_sLen], YSI_g_sID);
	format(sAddr, sizeof (sAddr), PHP_RECEIVE "?ID=%d&RE=%d&TO=%d", YSI_g_sID, res, to);
	P:1("_PHP_FireOne request: %s: ", sAddr);
	HTTP(YSI_g_sID, HTTP_GET, sAddr, "", "_PHP_Result");
}

static stock PHP_GetNum32(str[])
{
	return ((str[0] & ~0x80) << 25) | ((str[1] & ~0x80) << 18) | ((str[2] & ~0x80) << 11) | ((str[3] & ~0x80) << 4) | (str[4] & ~0xF0);
}

static stock PHP_GetNum8(str[])
{
	return str[0] & ~0x80;
}

static stock PHP_GetNum6(str[])
{
	return str[0] & ~0x40;
}

static stock bool:PHP_GetBool(str[])
{
	return str[0] == '1';
}

public _PHP_Ignore(index, response, data[])
{
	P:1("_PHP_Ignore: %i, %i, %s", index, response, data);
	return 0;
}

public _PHP_Result(index, response, data[])
{
	P:1("_PHP_Result called: %d %d %s", index, response, data);
	if (response == 200)
	{
		// Fire a replacement.
		//PHP_FireOne();
		if (index)
		{
			new
				res = 0;
			switch (data[0])
			{
				case '1':
				{
					//P:I("PHP: Got response.");
					// Now parse the data.
					//printf(data);
					static
						sFunc[32],
						bool:sTrue = true,
						bool:sFalse = false;
					for (new i = 1, len = strlen(data); i < len; )
					{
						//new
						//	flen = PHP_GetNum8(data[i]) + i + 1;
						//data[flen] = '\0';
						//format(sFunc, sizeof (sFunc), "%s@yP_", data[i + 1]);
						//i = flen;
						//printf("%d %d", i, data[i]);
						new
							flen = PHP_GetNum8(data[i++]);
						//printf("%d", flen);
						//data[flen] = '\0';
						format(sFunc, sizeof (sFunc), "%.*s@yP_", flen, data[i]);
						//printf("%s", sFunc);
						i += flen;
						//printf("%d", data[i]);
						if (data[i] & 0x80)
						{
							flen = PHP_GetNum32(data[i]);
							i += 5;
							if (data[i] == 255)
							{
								P:5("_PHP_Result: Got number.");
								// Number.
								/*if (data[i - 1] & 0x40)
								{
									CallRemoteFunction(sFunc, "f", flen);
								}
								else
								{
									CallRemoteFunction(sFunc, "i", flen);
								}*/
								CallRemoteFunction(sFunc, "i", flen);
								++i;
							}
							else
							{
								P:5("_PHP_Result: Got string.");
								// String.
								flen += i;
								data[flen] = '\0';
								CallRemoteFunction(sFunc, "s", data[i]);
								i = flen + 1;
							}
						}
						else if (data[i] & 0x40)
						{
							sFunc[flen] = '_';
							sFunc[flen + 3] = '@';
							// Function call.
							new
								params = PHP_GetNum6(data[i]),
								n = params * 4 + 8,
								heap = 0;
							static
								sFormat[64];
							++i;
							sFormat[params] = '\0';
							P:5("_PHP_Result: Got function %s.", sFunc);
							while (params--)
							{
								if (data[i] & 0x80)
								{
									flen = PHP_GetNum32(data[i]);
									i += 5;
									if (data[i] == 255)
									{
										P:5("_PHP_Result: Got number parameter (%d).", flen);
										sFormat[params] = 'i';
										// Number.
										#emit LOAD.S.pri flen
										#emit HEAP 4
										#emit STOR.I
										#emit PUSH.alt
										heap += 4;
										++i;
									}
									else
									{
										sFormat[params] = 's';
										// String
										flen += i;
										data[flen] = '\0';
										P:5("_PHP_Result: Got string parameter (%d: %s).", flen, data[i]);
										#emit LOAD.S.pri i
										#emit LOAD.S.alt data // Not ADDR.alt.
										#emit IDXADDR
										#emit PUSH.pri
										//CallRemoteFunction(sFunc, "s", data[i]);
										i = flen + 1;
									}
								}
								else if (data[i] == '1')
								{
									P:5("_PHP_Result: Got true parameter.");
									sFormat[params] = 'i';
									#emit PUSH.C sTrue
									++i;
								}
								else
								{
									P:5("_PHP_Result: Got false parameter.");
									sFormat[params] = 'i';
									#emit PUSH.C sFalse
									++i;
								}
							}
							P:5("_PHP_Result: Do function call.");
							// Push the static parameters and call the function.
							#emit PUSH.C         sFormat
							#emit PUSH.C         sFunc
							#emit PUSH.S         n
							#emit SYSREQ.C       CallRemoteFunction
							
							//n += 4;
							//#emit POP.pri
							// Save the return.
							#emit STOR.S.pri     res
							// Clear the stack, including the return.
							#emit LCTRL          4
							#emit LOAD.S.alt     n
							#emit ADD
							#emit ADD.C          4
							#emit SCTRL          4
							
							// Clear the heap.
							#emit LCTRL          2
							#emit LOAD.S.alt     heap
							#emit SUB
							#emit SCTRL          2
							
							// Have a return.
						}
						else if (data[i] == '1')
						{
							P:5("_PHP_Result: Got true.");
							CallRemoteFunction(sFunc, "i", sTrue);
							++i;
						}
						else
						{
							P:5("_PHP_Result: Got false.");
							CallRemoteFunction(sFunc, "i", sFalse);
							++i;
						}
					}
				}
				case '\0':
				{
					P:E("PHP: Empty response.");
				}
				default:
				{
					// Error or unknown.
					switch (data[1])
					{
						case '0':
						{
							P:E("PHP: ID out of bounds.");
						}
						case '1':
						{
							P:E("PHP: Could not open shared memory.");
						}
						case '2':
						{
							//P:E("PHP: ID out of bounds.");
							// Not an error!
						}
						case '3':
						{
							P:F("PHP: Server does not support Shared Memory Extensions (shmop).");
							// Fatal error (one of only two ever)!
							return;
						}
						default:
						{
							P:E("PHP: Unknown error: %s.", data[1]);
						}
					}
				}
			}
			//new TODO;
			defer _PHP_FireOne(res, index);
		}
	}
	else
	{
		defer _PHP_FireOne[5000](0, 0);
	}
}

#define phpdata%0(%1) %0@yP_(%1);public%0@yP_(%1)
#define phpfunc%0(%1) %0_yP@(%1);public%0_yP@(%1)

#define PHP:%0(%1) %0_yP@(%1);public %0_yP@(%1)

//#include "..\YSI_Core\y_master"

