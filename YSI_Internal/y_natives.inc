#if defined _INC_y_natives
	#endinput
#endif
#define _INC_y_natives

/*+
 * <library name="y_natives">
 * <section>
 *  Description
 * </section>
 *  Obsolete, but still required by y_lock.
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

#include "y_compilerdata"
#include "y_globaltags"

/*#if defined _YSI_MINI_MODE
	// Remove all of "file" now.
	#undef fopen
	#undef fclose
	#undef ftemp
	#undef fremove
	#undef fwrite
	#undef fread
	#undef fseek
	#undef fexist

	// Remove dynamic call functions.
	#undef CallRemoteFunction
	#undef CallLocalFunction
#endif*/

/*native File:fopen(const name[], filemode: mode = io_readwrite) = fopen;
native bool:fclose(File: handle) = fclose;
native File:ftemp() = ftemp;
native bool:fremove(const name[]) = fremove;
native fwrite(File: handle, const string[]) = fwrite;
native fread(File: handle, string[], size = sizeof string, bool: pack = false) = fread;
native fseek(File: handle, position = 0, seek_whence: whence = seek_start) = fseek;
native fexist(const pattern[]) = fexist;
native CallRemoteFunction(const function[], const format[], GLOBAL_TAG_TYPES:...) = CallRemoteFunction;
native CallLocalFunction(const function[], const format[], GLOBAL_TAG_TYPES:...) = CallLocalFunction;*/

/*#if defined _YSI_MINI_MODE
	// Remove all of "file" now.
	#define fopen       _MMD(fopen)
	#define fclose      _MMD(fclose)
	#define ftemp       _MMD(ftemp)
	#define fremove     _MMD(fremove)
	#define fwrite      _MMD(fwrite)
	#define fread       _MMD(fread)
	#define fseek       _MMD(fseek)
	#define fexist      _MMD(fexist)

	// Remove dynamic call functions.
	#define CallRemoteFunction _MMD(CallRemoteFunction)
	#define CallLocalFunction  _MMD(CallLocalFunction)
#endif*/

#if defined YSI_LOCK_MODE
	new
		YSI_gLockData[21];
#endif

