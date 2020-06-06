/*
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

#include "..\..\YSI_Core\y_utils"
#include "..\..\YSI_Storage\y_xml"

static stock
	XML:YSI_g_sXMLRules = NO_XML_FILE,
	#if defined _YSI_VISUAL_OBJECTS
		YSI_g_sRaceObjects[ceildiv(MAX_DYN_OBJECTS, 4)] = {-1, ...},
	#endif
	YSI_g_sCurRace = 0,
	YSI_g_sCurWorld = 0;

forward Loader_Spawn();
forward Loader_Check();
forward Loader_Obj();

/*-------------------------------------------------------------------------*//**
 * <remarks>
 * Defines the parsing rules for reading MTA XML maps.
 * </remarks>
 *//*------------------------------------------------------------------------**/

Loader_Loader()
{
	if (YSI_g_sXMLRules == NO_XML_FILE)
	{
		YSI_g_sXMLRules = XML_New();
		if (YSI_g_sXMLRules != NO_XML_FILE)
		{
			XML_AddHandler(YSI_g_sXMLRules, "object", "Loader_Obj");
			XML_AddHandler(YSI_g_sXMLRules, "checkpoint", "Loader_Check");
			XML_AddHandler(YSI_g_sXMLRules, "spawnpoint", "Loader_Spawn");
		}
	}
	return 1;
}

/*-------------------------------------------------------------------------*//**
 * <param name="filename">File to parse as an XML race file.</param>
 * <param name="laps">Number of laps to race for.</param>
 * <param name="entry">Cost of entry.</param>
 * <param name="countdown">Time to count down from for start.</param>
 * <param name="arial">Use arial checkpoints instead.</param>
 * <param name="fixedPrize">Set prize amounts manually.</param>
 * <param name="exitTime">Time allowed out a vehicle before fail.</param>
 * <param name="interior">The interior of the race.</param>
 * <param name="world">The world of the race.</param>
 * <param name="restart">Don't destroy the race on completion.</param>
 * <returns>Created race.</returns>
 * <remarks>
 * Tries to create a new race to save to then parses the file.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Loader_Parse(filename[], laps = 0, entry = 0, countdown = 3, bool:arial = false, bool:fixedPrize = true, exitTime = 0, interior = 0, world = 0, bool:restart = false)
{
	if (!fexist(filename)) return NO_RACE;
	new
		race = Race_Create(laps, entry, countdown, arial, fixedPrize, exitTime, interior, world, restart);
	if (race != NO_RACE)
	{
		YSI_g_sCurRace = race;
		YSI_g_sCurWorld = world;
		XML_Parse(YSI_g_sXMLRules, filename);
	}
	YSI_g_sCurWorld = 0;
	YSI_g_sCurRace = NO_RACE;
	return race;
}

/*-------------------------------------------------------------------------*//**
 * <param name="filename">File to parse.</param>
 * <param name="world">World for the objects to appear in or -1 for all.</param>
 * <remarks>
 * Parses a map file, loading only the objects.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Loader_ParseObjects(filename[], world = -1)
{
	YSI_g_sCurWorld = world;
	return XML_Parse(YSI_g_sXMLRules, filename);
}

/*-------------------------------------------------------------------------*//**
 * <param name="race">Race to remove objects for.</param>
 * <remarks>
 * Destroys all the objects created for a race loaded with the loader.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Loader_Unload(race)
{
	#if defined _YSI_VISUAL_OBJECTS
		new
			race1 = race << 8,
			race2 = race << 16,
			race3 = race << 24;
		for (new i = 0; i < sizeof (YSI_g_sRaceObjects); i++)
		{
			if (YSI_g_sRaceObjects[i] & 0xFF000000 == race3)
			{
				YSI_g_sRaceObjects[i] |= 0xFF000000;
				DestroyDynamicObject((i * 4) + 3);
			}
			if (YSI_g_sRaceObjects[i] & 0x00FF0000 == race2)
			{
				YSI_g_sRaceObjects[i] |= 0x00FF0000;
				DestroyDynamicObject((i * 4) + 2);
			}
			if (YSI_g_sRaceObjects[i] & 0x0000FF00 == race1)
			{
				YSI_g_sRaceObjects[i] |= 0x0000FF00;
				DestroyDynamicObject((i * 4) + 1);
			}
			if (YSI_g_sRaceObjects[i] & 0x000000FF == race)
			{
				YSI_g_sRaceObjects[i] |= 0x000000FF;
				DestroyDynamicObject((i * 4));
			}
		}
	#else
		#pragma unused race
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <param name="radians">Radian angle to convert to degrees.</param>
 * <returns>Float</returns>
 * <remarks>
 * Based on mtarad2deg made by Trix and fixed by Mike.  Converts radians to degrees
 * and rationalises.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Float:Loader_Convert(Float:radians)
{
	if (radians == 0.0)
	{
		return 0.0;
	}
	new Float:retval = (360.0 + (radians / 0.0174532925));
	while (retval >= 360.0) retval -= 360.0;
	while (retval < 0.0) retval += 360.0;
	return retval;
}

/*-------------------------------------------------------------------------*//**
 * <returns>CreateDynamicObject</returns>
 * <remarks>
 * Called when an end object tag is reached to create an object.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public Loader_Obj()
{
	#if defined _YSI_VISUAL_OBJECTS
		static
			name[MAX_XML_ENTRY_NAME],
			val[MAX_XML_ENTRY_TEXT];
		new
			Float:x = 0.0,
			Float:y = 0.0,
			Float:z = 0.0,
			Float:rx = 0.0,
			Float:ry = 0.0,
			Float:rz = 0.0,
			model = 0;
		while (XML_GetKeyValue(name, val))
		{
			if (!strcmp(name, "position", true))
			{
				new
					pos = 0;
				x = floatstr(val);
				pos = chrfind(' ', val, pos);
				y = floatstr(val[++pos]);
				pos = chrfind(' ', val, pos);
				z = floatstr(val[++pos]);
			}
			else if (!strcmp(name, "rotation", true))
			{
				new
					pos = 0;
				rz = floatstr(val);
				pos = chrfind(' ', val, pos);
				ry = floatstr(val[++pos]);
				pos = chrfind(' ', val, pos);
				rx = floatstr(val[++pos]);
			}
			else if (!strcmp(name, "model", true))
			{
				model = strval(val);
			}
		}
		new
			obj = CreateDynamicObject(model, x, y, z, Loader_Convert(rx), Loader_Convert(ry), Loader_Convert(rz));
		if (YSI_g_sCurWorld != -1)
		{
			Object_RemoveFromAllWorlds(obj);
			Object_AddToWorld(obj, YSI_g_sCurWorld);
		}
		#if defined _YSI_VISUAL_RACE
			new
				shift = (8 * (obj & 3)),
				mul = obj >>> 2;
			if (YSI_g_sCurRace != NO_RACE)
			{
				YSI_g_sRaceObjects[mul] = (YSI_g_sRaceObjects[mul] & ~(0xFF << shift)) | YSI_g_sCurRace << shift;
			}
		#endif
		return obj;
	#else
		return -1;
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <returns>Race_AddCheckpoint</returns>
 * <remarks>
 * Called when an end checkpoint tag is reached to add a checkpoint to a race.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public Loader_Check()
{
	#if defined _YSI_VISUAL_RACE
		if (YSI_g_sCurRace == NO_RACE) return -1;
		static
			name[MAX_XML_ENTRY_NAME],
			val[MAX_XML_ENTRY_TEXT];
		new
			Float:x = 0.0,
			Float:y = 0.0,
			Float:z = 0.0;
		while (XML_GetKeyValue(name, val))
		{
			if (!strcmp(name, "position", true))
			{
				new
					pos = 0;
				x = floatstr(val);
				pos = chrfind(' ', val, pos);
				y = floatstr(val[++pos]);
				pos = chrfind(' ', val, pos);
				z = floatstr(val[++pos]);
			}
		}
		return Race_AddCheckpoint(YSI_g_sCurRace, x, y, z);
	#else
		return -1;
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <returns>Race_AddStart</returns>
 * <remarks>
 * Called when an end spawnpoint tag is reached to add a startpoint to a race.
 * </remarks>
 *//*------------------------------------------------------------------------**/

public Loader_Spawn()
{
	#if defined _YSI_VISUAL_RACE
		if (YSI_g_sCurRace == NO_RACE) return -1;
		static
			name[MAX_XML_ENTRY_NAME],
			val[MAX_XML_ENTRY_TEXT];
		new
			Float:x = 0.0,
			Float:y = 0.0,
			Float:z = 0.0,
			Float:rz = 0.0;
		while (XML_GetKeyValue(name, val))
		{
			if (!strcmp(name, "position", true))
			{
				new
					pos = 0;
				x = floatstr(val);
				pos = chrfind(' ', val, pos);
				y = floatstr(val[++pos]);
				pos = chrfind(' ', val, pos);
				z = floatstr(val[++pos]);
			}
			else if (!strcmp(name, "rotation", true))
			{
				rz = floatstr(val);
			}
		}
		return Race_AddStart(YSI_g_sCurRace, x, y, z, rz);
	#else
		return 1;
	#endif
}

/*-------------------------------------------------------------------------*//**
 * <param name="trigger">Tag to trigger the callback.</param>
 * <param name="function">Function to call for the tag.</param>
 * <remarks>
 * Used to add custom handlers to non-default tags in the race file format.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Loader_AddHandler(trigger[], function[])
{
	if (YSI_g_sXMLRules != NO_XML_FILE) return XML_AddHandler(YSI_g_sXMLRules, trigger, function);
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <returns>Current race handle.</returns>
 *//*------------------------------------------------------------------------**/

stock Loader_GetRace()
{
	return YSI_g_sCurRace;
}

