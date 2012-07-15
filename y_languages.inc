/*----------------------------------------------------------------------------*\
					==================================
					 Y Sever Includes - Language Code 
					==================================
Description:
	Handles language features - loading, listing and which one a player is.
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
	
	The Original Code is the YSI ini include.
	
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
	1.0
Changelog:
	02/12/11:
		Updated Langs_Add to accept the parameters in either order.
	01/05/11:
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
Operators:
	-
\*----------------------------------------------------------------------------*/

#include "internal\y_version"
#define YSIM_U_DISABLE
#include "y_master"

#include "y_hooks"

#if !defined MAX_LANGUAGES
	#define MAX_LANGUAGES (4)
#endif

#if !defined YSI_MAX_LANGUAGES
	#define YSI_MAX_LANGUAGES (Language:MAX_LANGUAGES)
#endif

#define NO_LANGUAGE (Language:-1)

#define MAX_LANGUAGE_NAME (16)

#define Language_IsValid(%0) (Language:0 <= (%0) < YSI_MAX_LANGUAGES && YSI_g_sLanguages[(%0)][0])

//#define FOREIGN forward
//#define GLOBAL stock

static stock
	Language:YSI_g_sPlayerLanguage[MAX_PLAYERS] = {NO_LANGUAGE, ...},
	YSI_g_sLanguageCodes[YSI_MAX_STRING],
	YSI_g_sLanguages[YSI_MAX_LANGUAGES][MAX_LANGUAGE_NAME],
	Language:YSI_g_sLanguageCount;

#define Langs_Add Langs_AddLanguage
#define Languages_Add Langs_AddLanguage
#define Languages_AddLanguage Langs_AddLanguage

foreign Language:_Langs_AddLanguage(string:code[], string:name[]);

global Language:_Langs_AddLanguage(string:code[], string:name[])
{
	// Get the 2 character language short code.
	P:2("_Langs_AddLanguage called: %s %s", code, name);
	static
		ins[4] = "XX|";
	if ('a' <= code[0] <= 'z')
	{
		ins[0] = code[0] & ~0x20;
	}
	else
	{
		if (!(ins[0] = code[0]))
		{
			if (strlen(name) == 2)
			{
				return _Langs_AddLanguage(name, code);
			}
			else
			{
				P:E("Langs_AddLanguage must have a 2 letter code");
				return NO_LANGUAGE;
			}
		}
	}
	if ('a' <= code[1] <= 'z')
	{
		ins[1] = code[1] & ~0x20;
	}
	else
	{
		if (!(ins[1] = code[1]))
		{
			if (strlen(name) == 2)
			{
				return _Langs_AddLanguage(name, code);
			}
			else
			{
				P:E("Langs_AddLanguage must have a 2 letter code");
				return NO_LANGUAGE;
			}
		}
	}
	if (code[2])
	{
		if (strlen(name) == 2)
		{
			return _Langs_AddLanguage(name, code);
		}
		else
		{
			P:E("Langs_AddLanguage must have a 2 letter code");
			return NO_LANGUAGE;
		}
	}
	new
		Language:add = YSI_g_sLanguageCount;
	for (new Language:i = Language:0; i != YSI_g_sLanguageCount; ++i)
	{
		if (!YSI_g_sLanguages[i][0])
		{
			// Add the new language here.
			add = i;
		}
		else if (!strcmp(YSI_g_sLanguages[i], name))
		{
			// Already exists.
			return i;
		}
	}
	if (add < YSI_MAX_LANGUAGES)
	{
		strins(YSI_g_sLanguageCodes, ins, _:add * 3);
		P:5("Langs_AddLanguage: Codes = %s", YSI_g_sLanguageCodes);
		strcpy(YSI_g_sLanguages[add], name, MAX_LANGUAGE_NAME);
		P:5("Langs_AddLanguage: New = %s (%d, %d)", YSI_g_sLanguages[add], _:add, Language_IsValid(add));
		++YSI_g_sLanguageCount;
		return add;
	}
	return NO_LANGUAGE;
}

#if _YSIM_IS_CLIENT
	// Don't give a warning if this is a client script.  Note that stubs are
	// disabled for this script so this is the only state that makes sense.
	stock
#endif
		Language:Langs_AddLanguage(string:code[], string:name[])
		{
			// This is done this way to give a compiler warning when it's not used.
			return _Langs_AddLanguage(code, name);
		}
#pragma tabsize 4

foreign Language:Langs_GetLanguageAt(id);

global Language:Langs_GetLanguageAt(id)
{
	for (new Language:x = Language:0; x != YSI_MAX_LANGUAGES; ++x)
	{
		if (YSI_g_sLanguages[x][0])
		{
			if (!id--)
			{
				return x;
			}
		}
	}
	return NO_LANGUAGE;
}

foreign Langs_RemoveLanguage(Language:l);

global Langs_RemoveLanguage(Language:l)
{
	if (Language_IsValid(l))
	{
		// Interestingly, this library is one of the few times I have used
		// native string functions rather than hand-rolled ones (except for
		// strcat used in strcpy).  It just so happens that they map well here.
		strdel(YSI_g_sLanguageCodes, _:l * 3, _:l * 3 + 3);
		YSI_g_sLanguages[l][0] = '\0';
		return 1;
	}
	return 0;
}

foreign Language:Langs_GetLanguage(string:identifier[]);

global Language:Langs_GetLanguage(string:identifier[])
{
	if (strlen(identifier) > 2)
	{
		// Search for the language by full name.
		for (new Language:i = Language:0; i != YSI_g_sLanguageCount; ++i)
		{
			if (YSI_g_sLanguages[i][0] && !strcmp(YSI_g_sLanguages[i], identifier, true))
			{
				return i;
			}
		}
	}
	else
	{
		// Search for the language by short name.
		new
			pos = strfind(YSI_g_sLanguageCodes, identifier, true);
		if (pos != -1)
		{
			return Language:(pos / 3);
		}
	}
	return NO_LANGUAGE;
}

foreign Language:Langs_GetLanguageCount();

global Language:Langs_GetLanguageCount()
{
	return YSI_g_sLanguageCount;
}

foreign string:Langs_GetLanguageCodes();

global string:Langs_GetLanguageCodes()
{
	// I don't quite know what this will do yet, as in how it will work...
	return YSI_g_sLanguageCodes;
}

foreign string:Langs_GetName(Language:l);

global string:Langs_GetName(Language:l)
{
	// I don't quite know what this will do yet, as in how it will work...
	new
		ret[YSI_MAX_STRING];
	if (Language_IsValid(l))
	{
		strcpy(ret, YSI_g_sLanguages[l]);
	}
	return ret;
}

foreign string:Langs_GetCode(Language:l);

global string:Langs_GetCode(Language:l)
{
	new
		ret[YSI_MAX_STRING];
	if (Language_IsValid(l))
	{
		strcpy(ret, YSI_g_sLanguageCodes[_:l * 3], 3);
	}
	return ret;
}

foreign bool:Langs_IsValid(Language:l);

global bool:Langs_IsValid(Language:l)
{
	return Language_IsValid(l);
}

foreign Language:Langs_GetPlayerLanguage(playerid);

global Language:Langs_GetPlayerLanguage(playerid)
{
	#if defined _YSI_SPECIAL_DEBUG
		#pragma unused playerid
		return Language:0;
	#else
		return YSI_g_sPlayerLanguage[playerid];
	#endif
}

foreign Language:Langs_SetPlayerLanguage(playerid, Language:l);

global Language:Langs_SetPlayerLanguage(playerid, Language:l)
{
	if (Language_IsValid(l))
	{
		return YSI_g_sPlayerLanguage[playerid] = l;
	}
	return NO_LANGUAGE;
}

foreign Language:Langs_SetPlayerCode(playerid, string:code[]);

global Language:Langs_SetPlayerCode(playerid, string:code[])
{
	return Langs_SetPlayerLanguage(playerid, Langs_GetLanguage(code));
}

mhook OnPlayerConnect(playerid)
{
	for (new Language:i = Language:0; i != YSI_g_sLanguageCount; ++i)
	{
		//printf("%s", YSI_g_sLanguages[i]);
		if (YSI_g_sLanguages[i][0])
		{
			// They have to default to some language, may as well be the first
			// valid one.
			YSI_g_sPlayerLanguage[playerid] = i;
			// May also add some special functions here to display the language
			// messages to a player in all languages, but I think that would be
			// better left to the mode writer, then they can integrate it in to
			// their own mode introduction.
			return 1;
		}
	}
	P:E("No languages set");
	return 0;
}

//#define YSI_SET_LAST_GROUP 21
#include "internal\y_grouprevert"
