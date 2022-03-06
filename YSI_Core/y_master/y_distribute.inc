/*+
 * <library
 *   name="y_distribute"
 *   version="0.1"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="This library simplifies the task of sending data to the new master script when one takes over from another."
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

#define DISTRIBUTE(%0) %0_Dist()

#define __declspec_distributed%0; %0;static stock DIST_STRIP:DIST_DO:<%0>;
#define __declspec_dist_tagged%3:%0; %3:%0;static stock DIST_STRIP:DIST_DO:< %0>;
#define __declspec_dist_master%0[%1]%2; %0[%1]%2;static stock DIST_STRIP:DIST_MA:<%0%2>%1|;
#define __declspec_dist_mtagged%3:%0[%1]%2; %3:%0[%1]%2;static stock DIST_STRIP:DIST_MA:< %0%2>%1|;
#define __declspec_dist_special%3:%0; %3:%0;static stock DIST_ST2:DIST_SPEC:< %0>|||;
#define __declspec_dist_mspecial%3:%0; %3:%0;static stock DIST_ST2:DIST_MSPEC:< %0>|||;

#define DIST_DO:<%0>%1; %0_Dist()Distribute_Do(#%0"@Dist",_:%0%1);MASTER_FUNC__%0@Dist(a[],s)<_YCM:y,_YCM:u>Distribute_To(a,s,_:%0%1);
//#define DIST_DO:<%0>%1; %0_Dist()Distribute_Do(#%0"@Dist",true,%0%1);forward%0@Dist(a[],s);public%0@Dist(a[],s)Distribute_To(a,s,%0%1);

// #define Distribute_Do(%0|||%1) Distribute_Do(%0,%1)
// #define Distribute_To(%0|||%1) Distribute_To(%0,%1)

#define DIST_STRIP:%7<%0[%1]%3>%4; DIST_STRIP:%7<%0%3>%4,_:%1;
#define DIST_SPEC:%7<%0<%1>%3>%4|||%9; DIST_DO:%7<%0%3>%4,_:sizeof(%0%9);
#define DIST_MSPEC:%7<%0<%1>%3>%4|||%9; DIST_MA:%7<%0%3>%4,_:sizeof(%0%9);
#define DIST_ST2:%7<%0[%1]%3>%4|||%9; DIST_ST2:%7<%0%3>%4,_:%1|||%9[];

#define DIST_MA:<%0>%8|%1; %0_Dist()for(new i=0;i!=_:%8;++i)Distribute_So(#%0"@Dist",i,YSI_g_sMasterData,_:%0[i]%1);MASTER_FUNC__%0@Dist(i,m,a[],s)<_YCM:y,_YCM:u>YSI_g_sMasterData[i]=Bit:m,Distribute_To(a,s,_:%0[i]%1);

stock Distribute_Do(const func[], GLOBAL_TAG_TYPES:...)
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

/*-------------------------------------------------------------------------*//**
 * <param name="func">The name of the receiving function.</param>
 * <param name="idx">The index of the data being sent in its array.</param>
 * <param name="masters">This data's masters.</param>
 * <param name="">The data and array sizes.</param>
 * <remarks>
 *  This function takes the data from a given slot in an array, along with the
 *  master IDs for that data.  If the data is defined in more than the current
 *  script, then this script is removed and the remainder of the data is sent to
 *  the new master system.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Distribute_So(const func[], idx, const Bit:masters[], GLOBAL_TAG_TYPES:...)
{
	new
		m = _:masters[idx] & ~Master_ID();
	// Only owned by the current script - skip it.
	if (m)
	{
		// Get the data and the sizes.
		new
			size = 0,
			args = numargs(),
			curs = 4;
		while (curs < args) size = (size + 1) * getarg(--args);
		if (size == 0) size = 1;
		// Call CallRemoteFunction
		static const
			scArgs[] = "iiai";
		#emit PUSH.ADR    size
		// Get the actual data pointer.
		#emit PUSH.S      24
		#emit PUSH.ADR    m
		#emit PUSH.ADR    idx
		#emit PUSH.C      scArgs
		#emit PUSH.S      func
		#emit PUSH.C      24
		#emit SYSREQ.C    CallRemoteFunction
		#emit STACK       28
	}
}

/*-------------------------------------------------------------------------*//**
 * <param name="str">String to get the size of.</param>
 * <returns>
 *  The number of BYTES this string takes up including the NULL.
 * </returns>
 * <remarks>
 *  Caters for both packed and unpacked strings.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Distribute_To(const from[], ss, GLOBAL_TAG_TYPES:...)
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

