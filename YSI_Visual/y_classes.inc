#if defined _INC_y_classes
	#endinput
#endif
#define _INC_y_classes

/**
 * <library name="y_classes">
 * <section>
 *  Description
 * </section>
 *  Allows greater control over classes so not everyone has every class.  Uses
 *  a form of compression for locations.
 * <section>
 *  Version
 * </section>
 *  0.1
 * <section>
 *  Functions
 * </section>
 * <subsection>
 * Public
 * </subsection><ul>
 *  <symbol name="Class_AddRemote">Adds a class to the remote master.</symbol>
 *  <symbol name="Class_Remote">Updates settings remotely.</symbol>
 * </ul><subsection>
 * Core
 * </subsection><ul>
 *  <symbol name="Class_Class">Sets up the system.</symbol>
 *  <symbol name="Class_OnPlayerRequestSpawn">Called when a player requests a spawn.</symbol>
 *  <symbol name="Class_OnPlayerRequestClass">Called when a player requests a class.</symbol>
 *  <symbol name="Class_OnPlayerConnect">Called when a player connects.</symbol>
 * </ul><subsection>
 * Stock
 * </subsection><ul>
 *  <symbol name="Class_Delete">Removes a class.</symbol>
 *  <symbol name="Class_SetPlayer">Sets whether or not a player can use a class.</symbol>
 *  <symbol name="Class_Disable">Disables a class.</symbol>
 *  <symbol name="Class_Enable">Enables a disabled class.</symbol>
 *  <symbol name="Class_AddForGroup">Adds a class to the system for only one group.</symbol>
 *  <symbol name="Class_Add">Adds a class to the system.</symbol>
 *  <symbol name="Class_AddEx">Adds a class to the system with group selection and setting.</symbol>
 *  <symbol name="Class_AddWithGroupSet">Adds a class and sets their group on selection.</symbol>
 *  <symbol name="Class_AllowReselection">Allows or disallows people to return to reselect a class.</symbol>
 *  <symbol name="Class_RequireSpawnLogin">Require people to login before spawning.</symbol>
 *  <symbol name="Class_RequireSelectionLogin">Require people to login before selecting.</symbol>
 *  <symbol name="Class_RequireSelectionReg">Require people to register before selecting.</symbol>
 *  <symbol name="Class_RequireSpawnReg">Require people to register before spawning.</symbol>
 * </ul><subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="Class_AddClass">Adds a class, wrapped by API and remote functions.</symbol>
 * </ul><subsection>
 * Inline
 * </subsection><ul>
 *  <symbol name="Class_IsActive">Checks a class is active.</symbol>
 *  <symbol name="Class_Enabled">Checks a class is enabled.</symbol>
 *  <symbol name="Class_IsValid">Checks a class is valid.</symbol>
 *  <symbol name="Class_X">Gets a classes x position.</symbol>
 *  <symbol name="Class_Y">Gets a classes y position.</symbol>
 *  <symbol name="Class_Z">Gets a classes z position.</symbol>
 *  <symbol name="Class_A">Gets a classes angle.</symbol>
 *  <symbol name="Class_Skin">Gets a classes skin.</symbol>
 * </ul><section>
 *  Definitions
 * </section><ul>
 *  <symbol name="MAX_CLASSES">Maximum number of classes storeable by the system.</symbol>
 *  <symbol name="CLASS_LEFT">Flag for last internal class viewed.</symbol>
 *  <symbol name="CLASS_MIDDLE">Flag for last internal class viewed.</symbol>
 *  <symbol name="CLASS_RIGHT">Flag for last internal class viewed.</symbol>
 * </ul><section>
 *  Enums
 * </section><ul>
 *  <symbol name="e_CLASS_FLAGS">Small data for individual classes.</symbol>
 *  <symbol name="E_CLASS">Class data structure.</symbol>
 * </ul><section>
 *  Variables
 * </section>
 * <subsection>
 * Static
 * </subsection><ul>
 *  <symbol name="YSI_g_sClasses">Data for classes.</symbol>
 *  <symbol name="YSI_g_sPlayerClass">Player's current classes.</symbol>
 *  <symbol name="YSI_g_sLeft">Handle for the first internal class.</symbol>
 *  <symbol name="YSI_g_sMiddle">Handle for the second internal class.</symbol>
 *  <symbol name="YSI_g_sRight">Handle for the third internal class.</symbol>
 *  <symbol name="YSI_g_sClassCount">Number of classes stored.</symbol>
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

#include "..\YSI_Internal\y_compilerdata"

stock _YSI_HAS_y_classes(_do_not_call_me_ever_, _like_never_)
{
	P:E("You called _YSI_HAS_y_classes!  Bad, don't do that!", _do_not_call_me_ever_, _like_never_);
	assert(false);
	return 0;
}

#include "..\YSI_Internal\y_version"

#if !defined MAX_CLASSES
	#define MAX_CLASSES                 (512)
#endif

#if !defined MAX_CLASS_SPAWN_WEAPONS
	#define MAX_CLASS_SPAWN_WEAPONS     (13)
#endif

#if !defined WEAPON_ARMOUR
	#define WEAPON_ARMOUR               (100)
#endif

#define INFINATE_ARMOUR                 (0x00800000)

#define MASTER 61
#define YSIM_U_DISABLE
#include "..\YSI_Core\y_master"

#include "..\YSI_Data\y_bit"
#include "..\YSI_Core\y_debug"
#include "..\YSI_Data\y_iterate"
#include "..\YSI_Data\y_playerarray"
#include "..\YSI_Data\y_iterate"
#include "..\YSI_Internal\y_natives"


#define _GROUP_MAKE_NAME<%0...%1> %0Class%1
#define _GROUP_MAKE_LIMIT         MAX_CLASSES
#include "..\YSI_Players\y_groups\_funcs"
//#include "..\YSI_Players\y_groups\y_classes"

#include "..\YSI_Coding\y_hooks"
#include "y_classes/classcontrol"
#include "..\YSI_Coding\y_hooks"
#include "y_classes/multiclass"

#if defined YSI_TESTS
	#include "..\YSI_Core\y_testing"
	#include "y_classes/tests"
#endif

// Reset.
#undef _GROUP_MAKE_LIMIT
#undef _GROUP_MAKE_NAME

#include "..\YSI_Core\y_master"

