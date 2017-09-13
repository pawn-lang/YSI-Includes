#if defined _INC_y_classes
	#endinput
#endif
#define _INC_y_classes

/**
<file>
					y_classes
</file>
<section>
	Description
</section>
	Allows greater control over classes so not everyone has every class.  Uses
	a form of compression for locations.
<section>
	Version
</section>
	0.1
<section>
	Changelog
</section><ul>
	14/04/12:
		Readded OnRequestSpawn logic.
		Fixed Class_AddWithGroupSet.
		Improved GM/FS interaction.
	02/01/08:
		First '08 edit - Fixed minus numbers in spawn points.
	18/11/07:
		Improved location compression to allow larger areas.
		Moved position code to Class_OnPlayerSpawn to reduce overhead.
	10/10/07:
		Fixed spawn data problem.
	31/08/07:
		Added cheap master system - YSI_SLAVE_CLASSs can't be master.
	05/08/07:
		Fixed a few bugs with repeated selection.
	04/08/07:
		First version.
</ul><section>
	Functions
</section><ul>
<li><subsection>Public</subsection><ul>
<entry name="Class_AddRemote">Adds a class to the remote master.</entry>
<entry name="Class_Remote">Updates settings remotely.</entry>
</ul></li><li><subsection>Core</subsection><ul>
<entry name="Class_Class">Sets up the system.</entry>
<entry name="Class_OnPlayerRequestSpawn">Called when a player requests a spawn.</entry>
<entry name="Class_OnPlayerRequestClass">Called when a player requests a class.</entry>
<entry name="Class_OnPlayerConnect">Called when a player connects.</entry>
</ul></li><li><subsection>Stock</subsection><ul>
<entry name="Class_Delete">Removes a class.</entry>
<entry name="Class_SetPlayer">Sets whether or not a player can use a class.</entry>
<entry name="Class_Disable">Disables a class.</entry>
<entry name="Class_Enable">Enables a disabled class.</entry>
<entry name="Class_AddForGroup">Adds a class to the system for only one group.</entry>
<entry name="Class_Add">Adds a class to the system.</entry>
<entry name="Class_AddEx">Adds a class to the system with group selection and setting.</entry>
<entry name="Class_AddWithGroupSet">Adds a class and sets their group on selection.</entry>
<entry name="Class_AllowReselection">Allows or disallows people to return to reselect a class.</entry>
<entry name="Class_RequireSpawnLogin">Require people to login before spawning.</entry>
<entry name="Class_RequireSelectionLogin">Require people to login before selecting.</entry>
<entry name="Class_RequireSelectionReg">Require people to register before selecting.</entry>
<entry name="Class_RequireSpawnReg">Require people to register before spawning.</entry>
</ul></li><li><subsection>Static</subsection><ul>
<entry name="Class_AddClass">Adds a class, wrapped by API and remote functions.</entry>
</ul></li><li><subsection>Inline</subsection><ul>
<entry name="Class_IsActive">Checks a class is active.</entry>
<entry name="Class_Enabled">Checks a class is enabled.</entry>
<entry name="Class_IsValid">Checks a class is valid.</entry>
<entry name="Class_X">Gets a classes x position.</entry>
<entry name="Class_Y">Gets a classes y position.</entry>
<entry name="Class_Z">Gets a classes z position.</entry>
<entry name="Class_A">Gets a classes angle.</entry>
<entry name="Class_Skin">Gets a classes skin.</entry>
</ul></li></ul><section>
	Definitions
</section><ul>
<entry name="MAX_CLASSES">Maximum number of classes storeable by the system.</entry>
<entry name="CLASS_LEFT">Flag for last internal class viewed.</entry>
<entry name="CLASS_MIDDLE">Flag for last internal class viewed.</entry>
<entry name="CLASS_RIGHT">Flag for last internal class viewed.</entry>
</ul><section>
	Enums
</section><ul>
<entry name="e_CLASS_FLAGS">Small data for individual classes.</entry>
<entry name="E_CLASS">Class data structure.</entry>
</ul><section>
	Variables
</section><ul>
<li><subsection>Static</subsection><ul>
<entry name="YSI_g_sClasses">Data for classes.</entry>
<entry name="YSI_g_sPlayerClass">Player's current classes.</entry>
<entry name="YSI_g_sLeft">Handle for the first internal class.</entry>
<entry name="YSI_g_sMiddle">Handle for the second internal class.</entry>
<entry name="YSI_g_sRight">Handle for the third internal class.</entry>
<entry name="YSI_g_sClassCount">Number of classes stored.</entry>
</ul></li></ul>
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

