/**
 * <library
 *   name="y_areas"
 *   version="0.3"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Handles area checks for player location based code not involving CPs."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <section>
 *     Functions
 *   </section>
 *   <subsection>
 *     Public
 *   </subsection><ul>
 *     <symbol name="Area_Loop">Main loop for checking who's where.</symbol>
 *     <symbol name="Area_Remote">Does minor functions remotely.</symbol>
 *     <symbol name="Area_AddRemote">Adds areas remotely.</symbol>
 *     <symbol name="YSIM_Areas">Master system interface.</symbol>
 *     <symbol name="Area_Broadcast">Recieves transmitted areas.</symbol>
 *     <symbol name="Area_UpdateEmpty">Resets the empty array after master change.</symbol>
 *   </ul><subsection>
 *     Core
 *   </subsection><ul>
 *     <symbol name="Area_Area">Constructor.</symbol>
 *     <symbol name="Area_CheckArea">Gets an area's type anx calls the relevant function.</symbol>
 *     <symbol name="Area_OnPlayerConnect">Called when a player connects.</symbol>
 *   </ul><subsection>
 *     Stock
 *   </subsection><ul>
 *     <symbol name="Area_Delete">Deletes an area.</symbol>
 *     <symbol name="Area_AddCube">Adds a cube.</symbol>
 *     <symbol name="Area_AddBox">Adds a box.</symbol>
 *     <symbol name="Area_AddCircle">Adds a circle.</symbol>
 *     <symbol name="Area_AddSphere">Adds a sphere.</symbol>
 *     <symbol name="Area_AddPoly">Adds a polygon.</symbol>
 *     <symbol name="Area_GetPlayerArea">Gets the area a player is in.</symbol>
 *     <symbol name="Area_SetPlayer">Sets wether a player can use this area.</symbol>
 *     <symbol name="Area_SetAllPlayers">Sets wether all players can use this area.</symbol>
 *     <symbol name="Area_SetAllWorlds">Sets wether all worlds have this are.</symbol>
 *     <symbol name="Area_SetWorld">Sets wether this world has this area.</symbol>
 *     <symbol name="Area_IsValid">Checks if an area is valid.</symbol>
 *   </ul><subsection>
 *     Static
 *   </subsection><ul>
 *     <symbol name="Area_IsInCircle">Checks if a player is in this circular area.</symbol>
 *     <symbol name="Area_IsInSphere">Checks if a player is in this spherical area.</symbol>
 *     <symbol name="Area_IsInPoly">Checks if a player is in this polygonal area.</symbol>
 *     <symbol name="Area_IsInCube">Checks if a player is in this cubic area.</symbol>
 *     <symbol name="Area_IsInBox">Checks if a player is in this rectangular area.</symbol>
 *     <symbol name="Area_AddToUnused">Adds a area pointer to the unused list.</symbol>
 *     <symbol name="Area_GetFreeSlot">Gets the next free area slot.</symbol>
 *   </ul><subsection>
 *     Inline
 *   </subsection><ul>
 *     <symbol name="Area_IsActive">Checks if an area is active.</symbol>
 *     <symbol name="Area_GetEmptySlotCount">Gets the number of empty slots.</symbol>
 *     <symbol name="Area_AddSlots">Removes slots from the unused count.</symbol>
 *   </ul><section>
 *     Callbacks
 *   </section><ul>
 *     <symbol name="OnPlayerEnterArea">Called when a player enters an area.</symbol>
 *     <symbol name="OnPlayerLeaveArea">Called when a player leaves an area.</symbol>
 *   </ul><section>
 *     Definitions
 *   </section><ul>
 *     <symbol name="MAX_AREAS">Max number of areas.</symbol>
 *     <symbol name="NO_AREA">Fail return.</symbol>
 *     <symbol name="AREA_NO_NEXT">Marker for end of a list.</symbol>
 *     <symbol name="AREA_WORLDS">Number of worlds an area can be in.</symbol>
 *     <symbol name="AREA_WORLD_COUNT">Number of cells required for a bit array of AREA_WORLDS.</symbol>
 *   </ul><section>
 *     Enums
 *   </section><ul>
 *     <symbol name="e_AREA_FLAGS">Flags for each area.</symbol>
 *     <symbol name="E_AREA">Structure for part of an areas data.</symbol>
 *   </ul><section>
 *     Variables
 *   </section>
 *   <subsection>
 *     Static
 *   </subsection><ul>
 *     <symbol name="YSI_g_sUnusedAreas">Pointer to the first unused area.</symbol>
 *     <symbol name="YSI_g_sLastUnused">Pointer to the last unused area.</symbol>
 *     <symbol name="YSI_g_sFreeCount">Number of unused slots.</symbol>
 *     <symbol name="YSI_g_sAreas">Array of area data.</symbol>
 *     <symbol name="YSI_g_sPlayerArea">Array of players' current areas.</symbol>
 *   </ul>
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

#if !defined _INC_y_areas
	#tryinclude "y_areas\y_areas_entry"
#endif
#if !defined _INC_y_areas
	#tryinclude "YSI_Visual\y_areas\y_areas_entry"
#endif
#if !defined _INC_y_areas
	#tryinclude "YSI\YSI_Visual\y_areas\y_areas_entry"
#endif
#if !defined _INC_y_areas
	#tryinclude <YSI_Visual\y_areas\y_areas_entry>
#endif
#if !defined _INC_y_areas
	#tryinclude <YSI\YSI_Visual\y_areas\y_areas_entry>
#endif
#if !defined _INC_y_areas
	#error Could not find y_areas
#endif

