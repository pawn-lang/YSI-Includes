/*+
 * <library name="y_version">
 * <section>
 *  Description
 * </section>
 *  Checks online to see if there is a newer version of YSI available.
 * <section>
 *  Version
 * </section>
 *  0.2
 * <section>
 *  Hooks
 * </section><ul>
 *  <symbol name="OnGameModeInit">Initialises things.</symbol>
 * </ul>
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

CHAIN_HOOK(YVers)
#undef CHAIN_ORDER
#define CHAIN_ORDER CHAIN_NEXT(YVers)

// Amazingly, this fixes hooking OnScriptInit...
CHAIN_FORWARD:YVers_OnScriptInit() = 1;

#define YSI_VERSION_RESPO               2

#define YSI_VERSION_MAJOR               5
#define YSI_VERSION_MINOR               03
#define YSI_VERSION_BUILD               0689

#define YSI_VERSION                     #YSI_VERSION_MAJOR "." #YSI_VERSION_MINOR "." #YSI_VERSION_BUILD

#if defined _YSI_NO_VERSION_CHECK
	
	public OnScriptInit()
	{
		#if defined YSI_LOCK_MODE
			new
				x = 10;
			YSI_gLockData[YSI_gLockData[2]++] += (YSI_gLockData[3] = floatround(floatpower(x, 2))) - 2;
			YSI_gLockData[YSI_gLockData[2]++] = (YSI_gLockData[3] | 0x09) & ~0x04;
			YSI_gLockData[2] *= (6 * x) - 5;
		#endif
		YVers_OnScriptInit();
		return 1;
	}
	
	#undef OnScriptInit
	#define OnScriptInit(%0) CHAIN_PUBLIC:YVers_OnScriptInit(%0)
	
#else
/*-------------------------------------------------------------------------*//*+
 * <returns>
 *  OnScriptInit
 * </returns>
 * <remarks>
 *      Constructor.  Checks to see if there is a new version available.  This
 *      code can not use ANY of the rest of YSI as it needs to be included by
 *      everything first.
 * </remarks>
 *//*------------------------------------------------------------------------**/
	
	#if !defined HTTP
	
		public OnScriptInit()
		{
			#if defined YSI_LOCK_MODE
				new
					x = 10;
				YSI_gLockData[0] = 'a' + 1;
				YSI_gLockData[YSI_gLockData[0] - 0x60] = x * 11;
				YSI_gLockData[x / 3] = x * 10;
				YSI_gLockData[1] = (YSI_gLockData[2] - YSI_gLockData[3]) / 2 + YSI_gLockData[3];
			#endif
			YSIPrint(" ");
			YSIPrint(" ");
			YSIPrint(" ");
			YSIPrint(" ======================================= ");
			YSIPrint(" |                                     | ");
			YSIPrint(" |        YSI version " YSI_VERSION "        | ");
			YSIPrint(" |        By Alex \"Y_Less\" Cole        | ");
			YSIPrint(" |                                     | ");
			YSIPrint(" |   Unable to check the latest YSI    | ");
			YSIPrint(" |  version, please watch the forums.  | ");
			YSIPrint(" |                                     | ");
			YSIPrint(" ======================================= ");
			YSIPrint(" ");
			YVers_OnScriptInit();
			return 1;
		}
		
		#undef OnScriptInit
		#define OnScriptInit(%0) CHAIN_PUBLIC:YVers_OnScriptInit(%0)
		
		#endinput
	#endif
	
	forward YVers_Callback(index, code, data[]);
	
	public OnScriptInit()
	{
		#if defined YSI_LOCK_MODE
			YSI_gLockData[0] += 1;
			for (new i = 0; i != 2; ++i)
			{
				YSI_gLockData[0] = YSI_gLockData[0] * 9 + 2;
			}
			YSI_gLockData[0] -= 1;
			YSI_gLockData[3] = YSI_gLockData[0];
			YSI_gLockData[0] -= 1;
			YSI_gLockData[2] = YSI_gLockData[0] + 11;
			YSI_gLockData[0] -= 1;
			YSI_gLockData[1] = YSI_gLockData[0] + 7;
		#endif
		YSIPrint(" ");
		YSIPrint(" ");
		YSIPrint(" ");
		YSIPrint(" ======================================= ");
		YSIPrint(" |                                     | ");
		YSIPrint(" |        YSI version " YSI_VERSION "        | ");
		YSIPrint(" |        By Alex \"Y_Less\" Cole        | ");
		//YSIPrint(" |                                     | ");
		//YSIPrint(" |  Checking the latest YSI version..  | ");
		YSIPrint(" |                                     | ");
		YSIPrint(" ======================================= ");
		YSIPrint(" ");
		// Call my server to check the current public YSI version.  v is the
		// current version and c is the version of data response which this code
		// can parse.  Note that the response data SHOULD be backward compatible
		// , but may not always be - hence the accept parameter.  This will
		// never send any data except the current version for targeted replies
		// (e.g. to ignore minor updates which aren't critical).  It MAY in the
		// future send what libraries are in use so that it only tells you to
		// upgrade if the libraries you are using have changed, but that will
		// take more work and I'm not going to do that for now (I'm not entirely
		// sure exactly how to do it (though I have an idea - note to self:
		// chain callbacks from repeated inclusions of this file in the same way
		// as ALS then call them BEFORE sending the HTTP)).  Note that due to
		// the way the internet works the server will know the IP of the server
		// which sent the request, but the ENTIRE current contents of the remote
		// page are (note: I won't update this comment every time the version
		// updates, but that's the gist of it):
		//  
		//  1
		//  1.01.0000
		//  
		// This remote script has now been updated to include changelog
		// information and keeps a record of what IPs are connecting.
		//HTTP(0, HTTP_GET, "version.ysi.tl/index.php?c=" #YSI_VERSION_RESPO "&v=" YSI_VERSION, "", "YVers_Callback");
		YVers_OnScriptInit();
		return 1;
	}
	
	#undef OnScriptInit
	#define OnScriptInit(%0) CHAIN_PUBLIC:YVers_OnScriptInit(%0)
	
	/*---------------------------------------------------------------------*//*+
	 *
	 * <param name="	index">Not used.</param>
	 * <param name="	code">Response code from the server.</param>
	 * <param name="	data[]">HTTP data sent from the server.</param>
	 * <remarks>
	 *  This is called when my server responds to the HTTP request sent above
	 *  (or when it doesn't).  This prints information on the current and any
	 *  future versions of YSI.  Note that it only does a strcmp to determine if
	 *  the version is newer - people can't have versions newer than the latest,
	 *  onlyolder or equal (unless they play with the version numbers, but then
	 *  that's their own fault).
	 * </remarks>
	 *//*--------------------------------------------------------------------**/
	
	public YVers_Callback(index, code, data[])
	{
		if (code == 200)
		{
			// Got the remote page.
			// The first line is the version data version.  This should be
			// forward compatible, so new data is always added to the end of the
			// file. Skip the first line - contains the response version.
			new
				pos = strfind(data, "\n") + 1;
			if (strcmp(data[pos], YSI_VERSION, false, 9))
			{
				//data[pos + 9] = '\0';
				YSIPrint(" ");
				YSIPrint(" ========================================== ");
				YSIPrint(" |                                        | ");
				YSIPrintF(" |  A new version (v%.9s) of YSI is  | ", data[pos]);
				YSIPrint(" |            available from:             | ");
				YSIPrint(" |                                        | ");
				YSIPrint(" |     www.y-less.com/YSI/YSI_1.0.zip     | ");
				if (data[0] == '2')
				{
					YSIPrint(" |                                        | ");
					YSIPrint(" | Changelog:                             | ");
					// Print the changelog.
					new
						last = pos + 13;
					for ( ; ; )
					{
						pos = strfind(data[last], "\n", false);
						if (pos == -1)
						{
							// To break out in the middle of a loop.
							break;
						}
						pos += last;
						data[pos - 1] = '\0';
						YSIPrintF(" | %38s | ", data[last]);
						last = pos + 1;
					}
				}
				YSIPrint(" |                                        | ");
				YSIPrint(" ========================================== ");
				YSIPrint(" ");
			}
		}
	}
	
#endif

