/**--------------------------------------------------------------------------**\
					================================
					y_distribute - Share master data
					================================
Description:
	This library simplifies the task of sending data to the new master script
	when one takes over from another.
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
	
	The Original Code is the YSI commands include.
	
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
	0.1
Changelog:
	17/07/13:
		First version.
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
		-
	Static:
		-
Commands:
	-
Compile options:
	-
\**--------------------------------------------------------------------------**/

#include "y_globaltags"
#include "..\YSI_Core\y_master"

/*

THIS:

static DISTRIBUTED_SIMPLE YSI_g_sSomeThing;

BECOMES:

static YSI_g_sSomeThing;

static stock YSI_g_sSomeThing_Dist() Distribute_Do("YSI_g_sSomeThing@Dist",_:DIST_SIZE_1:YSI_g_sSomeThing);

forward YSI_g_sSomeThing@Dist(a[], s)

public YSI_g_sSomeThing@Dist(a[], s)<>{}
public YSI_g_sSomeThing@Dist(a[], s)<_YCM:y> Distribute_To(a, s, DIST_SIZE1:YSI_g_sSomeThing);

*/

#define __declspec(%0) __declspec_%0

forward _@_y_distribute_@_();

public _@_y_distribute_@_()
{
	new
		a[1 char];
	CallRemoteFunction("", "");
	memcpy(a, "", 0, 0);
}

#define DISTRIBUTE(%0) %0_Dist()

#define __declspec_distributed%0; %0;static stock DIST_STRIP:DIST_DO:<%0>;
#define __declspec_dist_tagged%3:%0; %3:%0;static stock DIST_STRIP:DIST_DO:< %0>;
#define __declspec_dist_master%0[%1]%2; %0[%1]%2;static stock DIST_STRIP:DIST_MA:<%0%2>%1|;

#define DIST_DO:<%0>%1; %0_Dist()Distribute_Do(#%0"@Dist",_:%0%1);master_func%0@Dist(a[],s)<y>Distribute_To(a,s,_:%0%1);
//#define DIST_DO:<%0>%1; %0_Dist()Distribute_Do(#%0"@Dist",true,%0%1);forward%0@Dist(a[],s);public%0@Dist(a[],s)Distribute_To(a,s,%0%1);

#define DIST_STRIP:%7:<%0[%1]%3>%4; DIST_STRIP:%7:<%0%3>%4,_:%1;

#define DIST_MA:<%0>%8|%1; %0_Dist()for(new i=0;i!=_:%8;++i)Distribute_So(#%0"@Dist",i,MASTER_GET<i>,_:%0[i]%1);master_func%0@Dist(i,a[],s)<y>Distribute_To(a,s,_:%0[i]%1);

stock Distribute_Do(func[], GLOBAL_TAG_TYPES:...)
{
	// Get the data and the sizes.
	new
		size = 0,
		args = numargs(),
		curs = 2;
	//printf("%d %d", args, curs);
	while (curs < args) size = (size + 1) * getarg(--args);
	if (size == 0) size = 1;
	// Call CallRemoteFunction
	//printf("HELLO: %s %d %d", func, size, _MAX_GROUPS_G);
	static const
		scArgs[] = "ai";
	#emit PUSH.ADR    size
	// Get the actual data pointer.
	#emit PUSH.S      16
	#emit PUSH.C      scArgs
	#emit PUSH.S      func
	#emit PUSH.C      16
	#emit SYSREQ.C    CallRemoteFunction
	#emit STACK       20
}

stock Distribute_So(func[], idx, Bit:masters, GLOBAL_TAG_TYPES:...)
{
	// Only owned by the current script - skip it.
	if (masters == Bit:(1 << Master_ID())) return;
	// Get the data and the sizes.
	new
		size = 0,
		args = numargs(),
		curs = 4;
	while (curs < args) size = (size + 1) * getarg(--args);
	if (size == 0) size = 1;
	// Call CallRemoteFunction
	static const
		scArgs[] = "iai";
	#emit PUSH.ADR    size
	// Get the actual data pointer.
	#emit PUSH.S      24
	#emit PUSH.ADR    idx
	#emit PUSH.C      scArgs
	#emit PUSH.S      func
	#emit PUSH.C      20
	#emit SYSREQ.C    CallRemoteFunction
	#emit STACK       24
}

stock Distribute_To(from[], ss, GLOBAL_TAG_TYPES:...)
{
	// Get the data and the sizes.
	new
		size = 0,
		args = numargs(),
		curs = 3;
	while (curs < args) size = (size + 1) * getarg(--args);
	if (size == 0) size = 1;
	// Push the parameters for "memcpy".
	ss = min(ss, size);
	#emit PUSH.S      size
	#emit LOAD.S.pri  ss
	#emit SHL.C.pri   2
	#emit PUSH.pri
	#emit PUSH.C      0
	#emit PUSH.S      from
	#emit PUSH.S      20
	#emit PUSH.C      20
	#emit SYSREQ.C    memcpy
	#emit STACK       24
}

