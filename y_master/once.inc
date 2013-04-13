/**--------------------------------------------------------------------------**\
                              ===================
                               YSI - Master Core
                              ===================
Description:
	There seems to be a bug with a compiler when using #emit in files included
	more than once, so this code has been moved to a file only included once.
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
	
	The Original Code is the YSI master include.
	
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
	0.2
Changelog:
	03/01/13:
		Added "@foreign" and "@global" for EXPLICIT Master_Caller use.
		Added "void:" return tag to simplify common code.
	07/08/10:
		Split in to y_masteronce.
		Added assembly for publics scanning.
	06/08/10:
		Managed the ultimate - got completely transparent inclusion!
	05/08/10:
		Completed new master system, now does all syncing and clients.
	06/10/09:
		Rewrote using states.
		Added remote function macros.
		Reduced the number of masters to a single one.  It must have them all.
		Vastly simplified the master model - ending the master ends everything.
	06/01/08:
		Added code to not pass data if no other script exists.
	17/11/07:
		Added code for a script to remove itself from the global list.
	11/10/07:
		Not first version but added documentation months late.
Functions:
	Public:
		-
	Core:
		-
	Stock:
		-
	Static:
		-
	Inline:
		-
	API:
		-
	Hooks:
		OnGameModeInit
		OnGameModeExit
Callbacks:
	-
Definitions:
	-
Enums:
	-
Macros:
	-
Tags:
	-
Variables:
	Global:
		_@ - ID of this script.
	Static:
		-
Commands:
	-
Compile options:
	-
Operators:
	-
Natives:
	-
</remarks>
\**--------------------------------------------------------------------------**/

#define _Y_MASTER_ONCE

// These parts should only be defined once ever.  This code is not dependent on
// the current MASTER value, it's all generic.

#include "internal\y_version"
#include "y_debug"
#include "y_hooks"
#include "internal\y_shortfunc"

#include "internal\y_natives"

#define _YSIM_COMPARE -1

#define MASTER_DATA<%0> static stock Bit:YSI_g_sMasterData[_:(%0)];
#define MASTER_RESET<%0> YSI_g_sMasterData[_:(%0)] = Bit:0;
#define MASTER_SET<%0> YSI_g_sMasterData[_:(%0)] = Bit:(1 << Master_Caller());
#define MASTER_ADD<%0> YSI_g_sMasterData[_:(%0)] |= Bit:(1 << Master_Caller());
#define MASTER_REMOVE<%0> YSI_g_sMasterData[_:(%0)] &= Bit:(~(1 << Master_Caller()));
#define MASTER_EMPTY<%0> if(!YSI_g_sMasterData[_:(%0)])

#if defined YSI_IS_CLIENT
	#if NO_VALUE(YSI_IS_CLIENT)
		#undef YSI_IS_CLIENT
		#define YSI_IS_CLIENT 100
	#endif
#endif

#if defined YSI_IS_SERVER
	#if NO_VALUE(YSI_IS_SERVER)
		#undef YSI_IS_SERVER
		#define YSI_IS_SERVER 100
	#endif
#endif

#if defined YSI_IS_STUB
	#if NO_VALUE(YSI_IS_STUB)
		#undef YSI_IS_STUB
		#define YSI_IS_STUB 100
	#endif
#endif

// Define all the alternate spellings once.
#define RF@cp  RF@pc
#define RF@pvc RF@pcv
#define RF@cpv RF@pcv
#define RF@cvp RF@pcv
#define RF@vpc RF@pcv
#define RF@vcp RF@pcv
#define RF@vp  RF@pv
#define RF@cv  RF@vc

#define RF@cpt  RF@pct
#define RF@tcp  RF@pct
#define RF@tpc  RF@pct
#define RF@ctp  RF@pct
#define RF@ptc  RF@pct
#define RF@tp  RF@pt
#define RF@tc  RF@ct

#define mhook master_hook

#define OnScriptClose Master_OnScriptClose
forward Master_OnScriptClose(script);

// These are the macros used by y_master for the recursive function definition
// structure, but they are not used unless a cloud-based "foreign" or "global"
// are used.

#define W@(@Zu:#%0:%1#,%2);return%3(%8) W@(@Zu:#%1,%2);return%0:%3(%0:%8)
#define Z@(%0string:i) S@(i)
#define V@(%0string:%1) F@()


// Second "foreign" declaration.
//#define @Zu:Y@();W@(#%0##,_YM@CX:,,);return%1(%2);}%3(%4);%5(%6)<%7> Y@();W@(#%0##,#);return%1(%2);}%3(%4);stock %5(%6)<%7>return @Zv:@Zq:%5&H@();
#define @Zu:#%0,_YM@C%8:,,);return%1(%2);}%5(%6)<%7> @Z%8:#%0,#);return%1(%2);}stock%5(%6)<%7>return @Zv:@Zq:%5&H@()
//#define @Zu:#%0,_YM@CX:,,) @Zl:#%0,#)


// Second "foreign" declaration.
// This has been updated to check for arrays, then check if the array is a
// string, instead of the old method which checked for those separately.
#define @Zn:@Zo:%2:#%0#%1|||%3[%4]|||%5,%6);%7}%8&H@(%9||| @Zm:@Zr:%2:#%0#%1|||%3|||%5,%6);%7}%8&H@(%9|||

#define @Zm:@Zr:%2:#%0#%1|||%4string:%3|||%5,%6);%7}%8&H@(%9||| @Zn:@Zo:%2:#%0s#%1,%3|||%5|||%6);%7}%8&H@(%9,%3|||
#define @Zr:%2:#%0#%1|||%3|||%5,%6);%7}%8&H@(%9||| @Zn:@Zo:%2:#%0a#%1,%3|||%5|||%6);%7}%8&H@(%9,%3|||

#define @Zo:%2:#%0#%1|||%3|||%5,%6);%7}%8&H@(%9||| @Zn:@Zo:%2:#%0i#%1,%3|||%5|||%6);%7}%8&H@(%9,%3|||

#define @Zp:%0||||||);%1}%2&H@(,%4||| @Zl:%0);%1}%2&H@(%4
#define @Zy:%0||||||);%1}%2&H@(,%4||| @Zj:%0);%1}%2&H@(%4

#define _YM@Cl:%0,%1);%2}%3(%9)<%4> @Zn:@Zo:@Zp:##|||%0|||%1);%2}stock%3(%9)<%4>return @Zv:@Zq:%3&H@(|||)
#define _YM@Cj:%0,%1);%2}%3(%9)<%4> @Zn:@Zo:@Zy:##|||%0|||%1);%2}stock%3(%9)<%4>return @Zv:@Zq:%3&H@(|||)

#define @Zl:%0);%8void:%3(%1);}%5<%6>return%4&%7; %0);}%5<%6>%7;
#define @Zj:%0);%8void:%3(%1);}%5<%6>return%4&%7; %0);%3(%1);}%5<%6>%7;

#define @Zv:@Zq:%9:%1&H@( %9:@Zw:@Zx:%9&H@(

#define @Zw:@Zx:%0string%2&H@( G@(
#define @Zx:%0&H@( H@(

#define @Zq:%1&H@( H@(

/*
// Second "foreign" declaration.
// This has been updated to check for arrays, then check if the array is a
// string, instead of the old method which checked for those separately.
#define @Zn:@Zo:@Zp:#%0#%1|||%3[%4]|||%5,%6);%7}%8&H@(%9||| @Zm:@Zr:#%0#%1|||%3|||%5,%6);%7}%8&H@(%9|||

#define @Zm:@Zr:#%0#%1|||%2string:%3|||%5,%6);%7}%8&H@(%9||| @Zn:@Zo:@Zp:#%0s#%1,%3|||%5|||%6);%7}%8&H@(%9,%3|||
#define @Zr:#%0#%1|||%3|||%5,%6);%7}%8&H@(%9||| @Zn:@Zo:@Zp:#%0a#%1,%3|||%5|||%6);%7}%8&H@(%9,%3|||

#define @Zo:@Zp:#%0#%1|||%3|||%5,%6);%7}%8&H@(%9||| @Zn:@Zo:@Zp:#%0i#%1,%3|||%5|||%6);%7}%8&H@(%9,%3|||

#define @Zp:%0||||||);%1}%2&H@(,%4||| %0);%1}%2&H@(%4

#define _YM@CX:%0,%1);%2}%8;%3(%9)<%4> @Zn:@Zo:@Zp:##|||%0|||%1);%2}%8;stock %3(%9)<%4>return @Zv:@Zq:%3&H@(|||);

#define @Zv:@Zq:%9:%1&H@( %9:@Zw:@Zx:%9&H@(

#define @Zw:@Zx:%0string%2&H@( G@(
#define @Zx:%0&H@( H@(

#define @Zq:%1&H@( H@(
*/
// "global" declaration.
#define @Zt:@Zb:@Zh:@Zi:%0(%1|||%2:%3|||%5,%6) @Zb:@Zh:@Zi:%0(%1|||%3|||%5,%6)
#define @Zb:@Zh:@Zi:%0(%1|||%3[%4]|||%5,%6) @Zt:@Zb:@Zh:@Zi:%0(%1,%3|||%5|||%6)
#define @Zh:@Zi:%0(%1|||%3|||%5,%6) @Zt:@Zb:@Zh:@Zi:%0(%1,%3|||%5|||%6)

#define @Zi:%0(,%1||||||) %0(%1)

#define @Zk:_YM@CP:%0(,,) %0()

#define _YM@CP:%0(%1,%2) @Zt:@Zb:@Zh:@Zi:%0(|||%1|||%2)

//#define X@(%0string:%1) R@(%1)
#define X@(@Zk:_YM@CP:%0string:%1(%2)) R@(@Zk:_YM@CP:%1(%2))

// This is nearly all I needed to add to "global" for "void:".  I doubt that
// "foreign" will be as simple!
#define @Zz:X@(@Zk:_YM@CP:%0void:%1(%2)) @Zk:_YM@CP:%1(%2)

#define YSIM_NOT_CLIENT (!YSIM_HAS_MASTER || !_YSIM_IS_CLIENT)

#define @global global

#include "y_shortfunc"

#if defined YSI_NO_MASTER
	#endinput
#endif

#define MAX_MASTERS 26

forward Master_Reassert();

enum _E_YCM
{
	_E_YCM@y,
	_E_YCM@n,
	_E_YCM@m,
	_E_YCM@p,
	_E_YCM@u
}

#define _YCM@y (_YCM@==_E_YCM@y)
#define _YCM@n (_YCM@==_E_YCM@n)
#define _YCM@m (_YCM@==_E_YCM@m)
#define _YCM@p (_YCM@==_E_YCM@p)
#define _YCM@u (_YCM@==_E_YCM@u)

static
	YSI_g_sMasterCount,
	YSI_g_sMasterData[MAX_MASTERS];

/**--------------------------------------------------------------------------**\
<summary>Master_GetNext</summary>
<returns>
	Next master ID to be assigned.
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

stock Master_GetNext()
{
	P:3("Master_GetNext called");
	new
		masters = getproperty(8, YSIM_MASTER),
		i = 0;
	while (i != 32)
	{
		if (!(masters & (1 << i)))
		{
			return i;
		}
		++i;
	}
	return -1;
}

/**--------------------------------------------------------------------------**\
Hook:
	OnGameModeInit
</returns>
<remarks>
	Constructor.  Gets the script a master ID.  Now ALWAYS gets an ID, even if
	the master system is disabled - doing otherwise is just too complicated.
</remarks>
\**--------------------------------------------------------------------------**/

public OnScriptInit()
{
	P:1("Master_OGM");
	if (!existproperty(8, YSIM_MASTER))
	{
		setproperty(8, YSIM_MASTER, 0);
	}
	// Properties get lost between script changes so we need to force a rebuild.
	CallRemoteFunction("Master_Reassert", "");
	new
		masters = getproperty(8, YSIM_MASTER),
		i = 0;
	while (i != 32)
	{
		if (!(masters & (1 << i)))
		{
			_@ = i;
			masters |= 1 << i;
			break;
		}
		++i;
	}
	if (i != 32)
	{
		setproperty(8, YSIM_MASTER, masters);
	}
	C:1(if (_@ == -1) P:E("MasterID not assigned"););
	// Make sure this is called before all other YSI initialisations, at least
	// all the ones which use the master system.
	#if defined YSIM_OnMasterSystemInit
		YSIM_OnMasterSystemInit();
	#endif
	// Just use one name...
	#if defined Master_OnScriptInit
		return Master_OnScriptInit();
	#else
		return 1;
	#endif
}

#undef OnScriptInit
#define OnScriptInit Master_OnScriptInit
#if defined Master_OnScriptInit
	forward Master_OnScriptInit();
#endif

#define OnMasterSystemInit YSIM_OnMasterSystemInit
#if defined YSIM_OnMasterSystemInit
	forward YSIM_OnMasterSystemInit();
#endif

/**--------------------------------------------------------------------------**\
Hook:
	OnGameModeExit
</returns>
<remarks>
	Destructor.
</remarks>
\**--------------------------------------------------------------------------**/

public OnScriptExit()
{
	P:1("MasterOnce_OnScriptExit called");
	// Loop through everything this script is master for and call the remote
	// function for it.  EXCEPT for this script itself!
	new
		func[4];
	for (new i = 0; i != YSI_g_sMasterCount; ++i)
	{
		// This is slightly slower for ending and starting scripts, but uses far
		// less heap space, and these values are rarely used, so may as well
		// pack them (which is what has happened here).
		func[0] = YSI_g_sMasterData[i] & 0xFF;
		func[1] = (YSI_g_sMasterData[i] >> 8) & 0xFF;
		func[2] = YSI_g_sMasterData[i] >> 16;
		CallLocalFunction(func, "");
		// The properties currently clear instantly, but that may not always be
		// the case.
	}
	setproperty(8, YSIM_MASTER, getproperty(8, YSIM_MASTER) & ~(1 << _@));
	#if defined YSIM_OnScriptExit
		YSIM_OnScriptExit();
	#endif
	CallRemoteFunction("Master_OnScriptClose", "i", _@);
	return 1;
}

#undef OnScriptExit
#define OnScriptExit YSIM_OnScriptExit
#if defined YSIM_OnScriptExit
	forward YSIM_OnScriptExit();
#endif

/**--------------------------------------------------------------------------**\
<summary>Master_Reassert</summary>
<returns>
	-
</returns>
<remarks>
	Rebuilds the collection of master data whenever a script is restarted.
</remarks>
\**--------------------------------------------------------------------------**/

public Master_Reassert()
{
	// Make sure that the caller parameter is always -1 by default.
	U@(8, YSIM_CALLER, -1);
	if (_@ != -1)
	{
		// Read this script's master value.
		setproperty(8, YSIM_MASTER, getproperty(8, YSIM_MASTER) | (1 << _@));
		// Readd this script's owned scripts.
		new
			func[4];
		for (new i = 0; i != YSI_g_sMasterCount; ++i)
		{
			// This is slightly slower for ending and starting scripts, but uses far
			// less heap space, and these values are rarely used, so may as well
			// pack them (which is what has happened here).
			func[0] = YSI_g_sMasterData[i] & 0xFF;
			func[1] = (YSI_g_sMasterData[i] >> 8) & 0xFF;
			func[2] = YSI_g_sMasterData[i] >> 16;
			setproperty(9, func, _@);
		}
	}
}

/**--------------------------------------------------------------------------**\
<summary>_Master_Get</summary>
<param name="library[]">The name of the library to try become master for.</param>
<returns>
	-
</returns>
<remarks>
	-
</remarks>
\**--------------------------------------------------------------------------**/

stock bool:_Master_Get(library[], bool:force = false)
{
	P:3("bool:_Master_Get called: \"%s\", %i", library, _:force);
	P:2("_Master_Get called");
	if (!force && existproperty(9, library))
	{
		new
			master = getproperty(9, library);
		P:4("_Master_Get: Prop exists: %d %d", master, _@);
		if (master != -1)
		{
			if (master == _@)
			{
				return true;
			}
			P:4("_Master_Get: Prop set");
			return false;
		}
	}
	P:4("_Master_Get: Get master.");
	setproperty(9, library, _@);
	P:4("_Master_Get: Set master.");
	// Add this library to the list.  The list is designed to only deal with
	// two or three character master names now!
	if (YSI_g_sMasterCount < MAX_MASTERS)
	{
		P:4("_Master_Get: Set master string.");
		YSI_g_sMasterData[YSI_g_sMasterCount++] = library[0] | (library[1] << 8) | (library[2] << 16);
		P:4("_Master_Get: Set master string.");
	}
	P:C(else P:E("Too many master scripts"););
	return true;
}
