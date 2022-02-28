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

#if !defined FORMAT_FADE_STEP
	#define FORMAT_FADE_STEP 2
#endif

#define Y_RENDER_SCM_COLOUR_LEN (8)

//#define Y_RENDER_ONE_ARG 
//	if ((arg = getarg(curArg++) || TRUE))

// Loops through all possible arguments in lists, functions and singles.  See
// "case e_COMPRESS_FORMAT_DATA_CUSTOM:" for more details (an expanded macro
// version can be found there).
#define Y_RENDER_ARG for(new i=0,j=0,b=4;i!=2;++i)if(!i){if(ch&_:e_COMPRESS_FORMAT_DATA_FUNC){b=1,func="@yR_",va_getstring(func[4],curArg);if(funcidx(func)<0)func[b=2]='r';}else if(ch&_:e_COMPRESS_FORMAT_DATA_LIST)b=3;}else for(;(arg=b==1?W@(func,"iii",pid,(_:l),j):b==2?W@(func,"ii",(_:l),j):b==3?getarg(curArg,j++):getarg(curArg)),arg!=cellmin&&b||++curArg&0;b&=~4,++j)

// Make the correct specifier string for the data stored in the compressed
// specifier data.
#define Y_RENDER_SPECIFIER(%0) ((ch&_:e_COMPRESS_FORMAT_DATA_ZERO)?((ch&_:e_COMPRESS_FORMAT_DATA_LEFT)?(scFormats[3][6]='%0',scFormats[3]):(scFormats[2][5]='%0',scFormats[2])):((ch&_:e_COMPRESS_FORMAT_DATA_LEFT)?(scFormats[1][5]='%0',scFormats[1]):(scFormats[0][4]='%0',scFormats[0])))

// This makes hex and binary format specifiers display correctly with negative
// numbers in all cases (e.g. %5x etc).
#if YSI_MAX_STRING != 144
	#error Please update explicit YSI_MAX_STRING uses in the following line.
#endif
#define Y_RENDER_FIX_NEGATIVE(%0:%1) if(width>%1)arg=(ch&_:e_COMPRESS_FORMAT_DATA_LEFT)?((ch&_:e_COMPRESS_FORMAT_DATA_ZERO)?format(ts,144,"%"#%0"%0-*"#%0,arg>>>32/%1,width-(%1-1),arg&(1<<32/%1)-1):format(ts,144,"%"#%0"%-*"#%0,arg>>>32/%1,width-(%1-1),arg&(1<<32/%1)-1)):(ch&_:e_COMPRESS_FORMAT_DATA_ZERO)?format(ts,144,"%0*"#%0"%"#%0,width-1,arg>>>32/%1,arg&(1<<32/%1)-1):format(ts,144,"%*"#%0"%"#%0,width-1,arg>>>32/%1,arg&(1<<32/%1)-1);else format(ts,144,"%"#%0"%"#%0,arg>>>32/%1,arg&(1<<32/%1)-1)

// Try add a string to the current output.  This needs modifying to reset the
// whole function after a string is displayed.  "onlyOne" is set in the case
// where any line excess is cut off (e.g. in marquees).
//#define Y_RENDER_ADD(%1) switch(Format_DoAddString(pid,output,%1,p,maxlen,llen,strlen(%1),fakepos,fade)){case 1:++one;case 2:Format_DoTryShow(output,fade);}

#define Y_RENDER_DO_DISPLAY() {output[p]='\0';if(!none)Format_DoDisplay(pid,gInitialColour,output);if(onlyOne)return one;output[0]=p=0;llen=maxlen;++one;}

#define Y_RENDER_ADD(%1) for(new __added=0,__len=strlen((%1)),__done;(__added=Format_DoAddString(output,%1[__done],p,__len,llen,fakePos));__done+=__added,__len-=__added){if(fade)state y_render_fade:y_render_fade_fake;else Y_RENDER_DO_DISPLAY()}

//#define Y_RENDER_ADD_EX(%1,%2,%3) for(new __added=0,__len=(%3),__done=%2;(__added=Format_DoAddString(output,%1[__done],p,__len,llen,fakePos));__done+=__added,__len-=__added){if(fade)state y_render_fade:y_render_fade_fake;else Y_RENDER_DO_DISPLAY()}

#define Y_RENDER_CHAR(%1) while(!Format_DoAddChar(output,(%1),p,llen,fakePos)){if(fade)state y_render_fade:y_render_fade_fake;else Y_RENDER_DO_DISPLAY()}

// Helper macros to determine what a character is.  This could be modified to
// take in to account unicode letters, but that's hard.  I don't know enough
// about unicode, and frankly there are WAY too many characters to be listed
// here.  If other people want to modify this to support their language then
// good on them.
#define Y_TEXT_LETTER(%0) ('a'<=(%0)<='z'||'A'<=(%0)<='Z')
#define Y_TEXT_NUMBER(%0) ('0'<=(%0)<='9')

#define Y_RENDER_SCM_COLOUR_LEN (8)

#define e_FORMAT_FLAGS_INDEX (0x00FFFFFF)
#define e_FORMAT_FLAGS_REDO  (0x01000000)
#define e_FORMAT_FLAGS_ONE   (0x02000000)
#define e_FORMAT_FLAGS_NONE  (0x04000000)

static stock
	YSI_g_sListSep[4] = ", ",
	YSI_g_sFadeRedoTarget = 0,
	YSI_g_sFadeLength = 0,
	YSI_g_sFadeColour = 0,
	bool:YSI_g_sJustOne = false,
	YSI_g_sTempStyle[E_STYLE_DATA],
	YSI_g_sTemp3D[E_3D_DATA],
	YSI_g_sTempMaster = 0,
	Text:YSI_g_sBaseTD = TEXT_DRAW_NO_NEXT,
	gInitialColour = 0;

/*-------------------------------------------------------------------------*//**
 * <transition keep="true" target="y_render_show : y_render_show_scm" />
 *//*------------------------------------------------------------------------**/

stock _Text_SetDialogMode()
{
	YSI_g_sTempStyle[E_STYLE_DATA_TYPE] = e_STYLE_TYPE_DIALOG;
	state y_render_show : y_render_show_scm;
	YSI_g_sJustOne = true;
}

stock Format_SetListSeparator(const string:lst[])
{
	StrCpy(YSI_g_sListSep, lst);
}

/*-------------------------------------------------------------------------*//**
 * <transition keep="true" target="y_render_show : y_render_show_gt" />
 * <transition keep="true" target="y_render_show : y_render_show_scm" />
 * <transition keep="true" target="y_render_show : y_render_show_td" />
 * <transition keep="true" target="y_render_show : y_render_show_print" />
 *//*------------------------------------------------------------------------**/

stock _Format_SetStyleData(master, index, const style[E_STYLE_DATA], const label[E_3D_DATA])
{
	// =========================================================================
	//  
	#pragma unused index
	//  
	//      MAJOR WARNING:
	//  
	//  "Text_IsLocalOwner" DOES NOT PASS "INDEX" CORRECTLY AS IT DOESN'T KNOW
	//  WHAT IT SHOULD BE, DON'T FORGET THIS IF YOU EVER USE "index"...
	//  
	// =========================================================================
	YSI_g_sTempMaster = master;
	YSI_g_sTempStyle = style;
	YSI_g_sTemp3D = label;
	switch (style[E_STYLE_DATA_TYPE] & e_STYLE_TYPE_MASK)
	{
		case e_STYLE_TYPE_GT_0, e_STYLE_TYPE_GT_1, e_STYLE_TYPE_GT_2, e_STYLE_TYPE_GT_3, e_STYLE_TYPE_GT_4, e_STYLE_TYPE_GT_5, e_STYLE_TYPE_GT_6:
		{
			state y_render_show : y_render_show_gt;
			// Now that we know the style, we can store only the exact style.
			YSI_g_sTempStyle[E_STYLE_DATA_TYPE] = ((style[E_STYLE_DATA_TYPE] & e_STYLE_TYPE_MASK) >>> e_STYLE_TYPE_SHIFT) - e_STYLE_TYPE:1;
			YSI_g_sJustOne = true;
			// THIS IS NOT `YSI_MAX_STRING`.  Don't change it for that reason.
			return 144;
		}
		case e_STYLE_TYPE_CLIENT:
		{
			state y_render_show : y_render_show_scm;
			YSI_g_sJustOne = false;
			return 256;
		}
		case e_STYLE_TYPE_TD:
		{
			state y_render_show : y_render_show_td;
			YSI_g_sJustOne = true;
			// Anything with the ability to be longer than 1024 will require a
			// modification to the declaration of variables.
			return 1024;
		}
	}
	state y_render_show : y_render_show_print;
	return 1023;
}

static stock Format_InsertColour(str[], pos, &rem, &curCol, newCol, step) <y_render_show : y_render_show_scm>
{
	// This code doesn't yet deal with colours which are too close to have their
	// differences detected by the human eye (especially when there are spaces).
	curCol = newCol & 0x00FFFFFF;
	if (pos == 0)
	{
		gInitialColour = curCol;
		// Don't add the colour - this is handled in the text display function.
		return 0;
	}
	// Now try add the string version of the colour.
	//printf("rem: %d, required: %d", rem, Y_RENDER_SCM_COLOUR_LEN);
	if (rem < Y_RENDER_SCM_COLOUR_LEN + step)
	{
		// Not enough space to add a new colour.
		str[pos] = '\0';
		return -1;
	}
	// This may well cut characters off the end of the string, but don't worry,
	// well, you can worry because it may mean that some characters are parsed
	// multiple times, but there's not a lot you can do about it...  This is one
	// of the few places where the extra "+ 1" is taken in to account as format
	// uses it internally.
	format(str[pos], rem + 1, "{%06x}%s", curCol, str[pos]);
	rem -= Y_RENDER_SCM_COLOUR_LEN;
	return Y_RENDER_SCM_COLOUR_LEN;
}

static stock Format_InsertColour(str[], pos, &rem, &curCol, newCol, step) <>
{
	#pragma unused str, pos, rem, step
	curCol = newCol;
	return 0;
}

static stock Format_InsertColour(str[], pos, &rem, &curCol, newCol, step) <y_render_show : y_render_show_gt, y_render_show : y_render_show_td>
{
	// First get the closest GameText colour for the true colour.  I wrote a
	// function for this a LONG time ago, finally got around to using it!
	new
		ot = curCol & 0xFF,
		oc = curCol >>> 8;
	if (ot == 0 || ot == 'x')
	{
		// Still near the start, allow some of the special start colours.
		newCol = Colours_SAMPToGT(newCol & 0x00FFFFFF, oc);
	}
	else
	{
		// Can't use the oragey colour used at the start.
		newCol = Colours_SAMPToGT(newCol & 0x00FFFFFF, 3);
	}
	new
		nt = newCol & 0xFF,
		nc = (newCol >>> 8) * 3;
	curCol = newCol;
	// Compare them.
	static
		cs_hTags[] = "~x~~h~~h~~h~~h~~h~%s";
	if (nt == ot)
	{
		ot = nc - (oc * 3);
		if (ot == 0)
		{
			// No change, return 0 if there are enough charaters to show the
			// text that should come after this new colour.
			return rem >= step ? 0 : -1;
		}
		else if (ot > 0)
		{
			if (rem >= ot + step)
			{
				// Add enough "lighter" tags to change the old colour in to the
				// new colour.
				format(str[pos], rem + 1, cs_hTags[sizeof (cs_hTags) - 3 - ot], str[pos]);
				rem -= ot;
				return ot;
			}
			else
			{
				return -1;
			}
		}
	}
	if (rem < nc + step)
	{
		return -1;
	}
	// Subtract six from the size : 3 for "%s\0" and 3 for the extra "~x~"
	// needed as placeholder for the colour tag (added on the next line).
	format(str[pos], rem + 1, cs_hTags[sizeof (cs_hTags) - 6 - nc], str[pos]);
	str[pos + 1] = nt;
	rem -= nc + 3;
	return nc + 3;
}

static stock Format_AddColour(str[], pos, &rem, &curCol, newCol) <y_render_show : y_render_show_scm>
{
	// This code doesn't yet deal with colours which are too close to have their
	// differences detected by the human eye (especially when there are spaces).
	new
		rgb = newCol & 0x00FFFFFF;
	// Don't add the colour if there's no change from the last one.
	if (rgb == curCol)
	{
		return 0;
	}
	if (-0x5 <= ((rgb & 0x0FF) - (curCol & 0xFF)) <= 0x5)
	{
		if (-0x500 <= ((rgb & 0xFF00) - (curCol & 0xFF00)) <= 0x500)
		{
			if (-0x50000 <= ((rgb & 0xFF0000) - (curCol & 0xFF0000)) <= 0x50000)
			{
				// Haven't changed the colour.
				return 0;
			}
		}
	}
	if (YSI_g_sTempStyle[E_STYLE_DATA_TYPE] != e_STYLE_TYPE_DIALOG && pos == 0)
	{
		gInitialColour = newCol;
		// Don't add the colour - this is handled in the text display function.
		curCol = rgb;
		return 0;
	}
	// Now try add the string version of the colour.
	if (rem < Y_RENDER_SCM_COLOUR_LEN)
	{
		// Not enough space to add a new colour.
		str[pos] = '\0';
		return -1;
	}
	format(str[pos], rem + 1, "{%06x}", rgb);
	rem -= Y_RENDER_SCM_COLOUR_LEN;
	curCol = newCol;
	return Y_RENDER_SCM_COLOUR_LEN;
}

static stock Format_AddColour(str[], pos, &rem, &curCol, newCol) <>
{
	#pragma unused str, pos, rem
	curCol = newCol;
	return 0;
}

static stock Format_AddColour(str[], pos, &rem, &curCol, newCol) <y_render_show : y_render_show_gt, y_render_show : y_render_show_td>
{
	// First get the closest GameText colour for the true colour.  I wrote a
	// function for this a LONG time ago, finally got around to using it!
	new
		ot = curCol & 0xFF,
		oc = curCol >>> 8;
	if (ot == 0 || ot == 'x')
	{
		// Still near the start, allow some of the special start colours.
		newCol = Colours_SAMPToGT(newCol & 0x00FFFFFF, oc);
	}
	else
	{
		// Can't use the oragey colour used at the start.
		newCol = Colours_SAMPToGT(newCol & 0x00FFFFFF, 3);
	}
	new
		nt = newCol & 0xFF,
		nc = (newCol >>> 8) * 3;
	curCol = newCol;
	// Compare them.
	static
		cs_hTags[] = "~x~~h~~h~~h~~h~~h~";
	if (nt == ot)
	{
		ot = nc - (oc * 3);
		if (ot == 0)
		{
			return 0;
		}
		else if (ot > 0)
		{
			if (rem >= ot)
			{
				// Add enough "lighter" tags to change the old colour in to the
				// new colour.
				str[pos] = '\0';
				strcat(str[pos], cs_hTags[sizeof (cs_hTags) - 1 - ot], rem + 1);
				rem -= ot;
				return ot;
			}
			else
			{
				return -1;
			}
		}
	}
	if (rem < nc)
	{
		return -1;
	}
	// Subtract six from the size : 3 for "%s\0" and 3 for the extra "~x~"
	// needed as placeholder for the colour tag (added on the next line).
	//format(str[pos], rem + 1, cs_hTags[sizeof (cs_hTags) - 6 - nc], str[pos]);
	str[pos] = '\0';
	strcat(str[pos], cs_hTags[sizeof (cs_hTags) - 4 - nc], rem + 1);
	str[pos + 1] = nt;
	rem -= nc + 3;
	return nc + 3;
}

// str = input and output write array.
// pos = start position of the string to be faded.
// len = total remaining space in the string.
// endColour = target colour.
// gInitialColour = start and current colour.
// step = number of characters for each colour.
// offset = number of characters in the fade not being shown.
static stock Format_AddFade(str[], &pos, &len, endColour, &initialColour, step, offset) //<y_render_display : send_client_message>
{
	// Add a fade for a SendClientMessage.  This is called if a string is filled
	// up during a fade or the end of a fade is reached correctly.  In either
	// case the current fade will constiture the end of the known current string
	// so in actual fact no additionl text after the end of the fade will be
	// dropped.  This is also where we can save the data to appear in the fade
	// on the next line and re-show it.
	// Work out how many colours can be inserted at the specified step value
	// (i.e. how often a new colour appears) within the length from "pos" to the
	// end of "str".  This may be more than is required.  "len" is from "pos" to
	// the end of the string, NOT to the end of the characters requiring the
	// fade.  The length of the required fade is in "YSI_g_sFadeLength" so that the
	// value can be used in the future.
	new
		parts = (YSI_g_sFadeLength + step - 1) / step + offset,
		// We can insert all the colours and their texts in the given space.
		// Now we just need to figure out how...
		// First get the start and end colours.
		start = str[pos + 1] & 0x00FFFFFF; //~(Y_FORMAT_START_FADE | Y_FORMAT_ALWAYS_SET);
	// Remove the start and end colour markers.
	strdel(str, pos, pos + 2);
	// Find the colour components and component deltas.
	endColour &= 0x00FFFFFF; //~(Y_FORMAT_START_FADE | Y_FORMAT_ALWAYS_SET);
	new
		red = start >>> 16 & 0xFF,
		dred = ((endColour >>> 16 & 0xFF) - red) / parts,
		pred = initialColour >>> 16 & 0xFF,
		green = start >>> 8 & 0xFF,
		dgreen = ((endColour >>> 8 & 0xFF) - green) / parts,
		pgreen = initialColour >>> 8 & 0xFF,
		blue = start >>> 0 & 0xFF,
		dblue = ((endColour >>> 0 & 0xFF) - blue) / parts,
		pblue = initialColour >>> 0 & 0xFF;
	// Take old strings in to account.
	red += dred * offset;
	blue += dblue * offset;
	green += dgreen * offset;
	//strdel(str, pmax, pmax + 2);
	//startColour = gInitialColour;
	do
	{
		// Insert the new colour, if it is sufficiently different from the
		// existing colour to warrant being added new.
		if (-3 <= red - pred <= 3 && -3 <= blue - pblue <= 3 && -3 <= green - pgreen <= 3)
		{
			pos += step;
		}
		else
		{
			new
				upd = Format_InsertColour(str, pos, len, initialColour, red << 16 | green << 8 | blue, step);
			if (upd == -1)
			{
				// Didn't quite finish everything.  This is the number of
				//  characters left to process.
				return YSI_g_sFadeLength;
			}
			//initial += step;
			pos += step + upd;
			pred = red;
			pgreen = green;
			pblue = blue;
		}
		YSI_g_sFadeLength -= step;
		len -= step;
		red = red + dred & 0xFF;
		green = green + dgreen & 0xFF;
		blue = blue + dblue & 0xFF;
		// Could do something with "len" here if it runs out to signify that
		// more text needs to go on the next line of output.
	}
	while (YSI_g_sFadeLength > 0);
	// Correct for any excess characters.
	pos += YSI_g_sFadeLength;
	// This doesn't add the actual destination colour - that is added by virtue
	// of the fact that it is actually just a normal colour, so we can use the
	// standard colour code (whatever that may be) to add it in a more generic
	// way.
	return 0;
}

static stock Format_GetKeyString(output[YSI_MAX_STRING], key)
{
	output[0] = '\0';
	switch (key)
	{
	case e_PED_ANSWER_PHONE:
		output = "~k~~PED_ANSWER_PHONE~";
	case e_PED_DUCK:
		output = "~k~~PED_DUCK~";
	case e_PED_FIREWEAPON:
		output = "~k~~PED_FIREWEAPON~";
	case e_PED_FIREWEAPON_ALT:
		output = "~k~~PED_FIREWEAPON_ALT~";
	case e_PED_SPRINT:
		output = "~k~~PED_SPRINT~";
	case e_VEHICLE_ENTER_EXIT:
		output = "~k~~VEHICLE_ENTER_EXIT~";
	case e_PED_JUMPING:
		output = "~k~~PED_JUMPING~";
	case e_PED_LOCK_TARGET:
		output = "~k~~PED_LOCK_TARGET~";
	case e_PED_LOOKBEHIND:
		output = "~k~~PED_LOOKBEHIND~";
	case e_SNEAK_ABOUT:
		output = "~k~~SNEAK_ABOUT~";
	case e_VEHICLE_LOOKLEFT:
		output = "~k~~VEHICLE_LOOKLEFT~";
	case e_VEHICLE_LOOKRIGHT:
		output = "~k~~VEHICLE_LOOKRIGHT~";
	case e_GO_FORWARD:
		output = "~k~~GO_FORWARD~";
	case e_GO_BACK:
		output = "~k~~GO_BACK~";
	case e_GO_LEFT:
		output = "~k~~GO_LEFT~";
	case e_GO_RIGHT:
		output = "~k~~GO_RIGHT~";
	case e_VEHICLE_FIREWEAPON:
		output = "~k~~VEHICLE_FIREWEAPON~";
	case e_VEHICLE_HORN:
		output = "~k~~VEHICLE_HORN~";
	case e_VEHICLE_FIREWEAPON_ALT:
		output = "~k~~VEHICLE_FIREWEAPON_ALT~";
	case e_VEHICLE_ACCELERATE:
		output = "~k~~VEHICLE_ACCELERATE~";
	case e_VEHICLE_BRAKE:
		output = "~k~~VEHICLE_BRAKE~";
	case e_VEHICLE_HANDBRAKE:
		output = "~k~~VEHICLE_HANDBRAKE~";
	case e_VEHICLE_SUBMISSIONS:
		output = "~k~~VEHICLE_SUBMISSIONS~";
	case e_VEHICLE_LOOKBEHIND:
		output = "~k~~VEHICLE_LOOKBEHIND~" ;
	case e_VEHICLE_TURRETUP:
		output = "~k~~VEHICLE_TURRETUP~";
	case e_VEHICLE_TURRETDOWN:
		output = "~k~~VEHICLE_TURRETDOWN~";
	case e_VEHICLE_TURRETLEFT:
		output = "~k~~VEHICLE_TURRETLEFT~";
	case e_VEHICLE_TURRETRIGHT:
		output = "~k~~VEHICLE_TURRETRIGHT~";
	case e_VEHICLE_STEERUP:
		output = "~k~~VEHICLE_STEERUP~";
	case e_VEHICLE_STEERDOWN:
		output = "~k~~VEHICLE_STEERDOWN~";
	case e_VEHICLE_STEERLEFT:
		output = "~k~~VEHICLE_STEERLEFT~";
	case e_VEHICLE_STEERRIGHT:
		output = "~k~~VEHICLE_STEERRIGHT~";
	}
}

/*-------------------------------------------------------------------------*//**
 * <transition keep="true" target="y_render_fade : y_render_fade_fake" />
 *//*------------------------------------------------------------------------**/

static stock Format_DoEndFade(output[], &start, end, &rem, colour, &initial) //<>
{
	// If "colour" is 0 this is the end of a string before the close colour is
	// reached.  This fact is enforced by "Y_FORMAT_ALWAYS_SET", which ensures
	// that all colours, including black, are not 0 in the string to avoid PAWN
	// treating the colour as a NULL terminator or, as here, a no-colour marker.
	if (colour)
	{
		new
			offset = 0;
		if (YSI_g_sFadeLength)
		{
			initial = YSI_g_sFadeColour;
			offset = end - start - YSI_g_sFadeLength;
			//printf("parts: %d, %d, %d", offset, YSI_g_sFadeLength, end - start);
		}
		else
		{
			YSI_g_sFadeLength = end - start;
		}
		// "rem" will hold the number of characters AFTER the fade string on
		// entry, this needs fixing here to exclude them as they're being messed
		// with.
		rem += YSI_g_sFadeLength;
		//printf("length: %d", YSI_g_sFadeLength);
		// I wrote this code for the case where too much data has been found and
		// we needed a fake render to get the full length, but then found that
		// exactly the same code was needed for the default case too...
		//printf("Format_DoEndFade: %d %d %x %x %d", YSI_g_sFadeLength, /*YSI_g_sFadeLength +*/ rem, colour, initial, start);
		// Default step value is 1 and there is currently no way to change it.
		new
			ret = Format_AddFade(output, start, /*YSI_g_sFadeLength +*/ rem, colour, initial, FORMAT_FADE_STEP, offset);
		//printf("Format_DoEndFade: %d %d %x %x %d", YSI_g_sFadeLength, /*YSI_g_sFadeLength +*/ rem, colour, initial, start);
		YSI_g_sFadeColour = initial;
		return ret;
	}
	else
	{
		//printf("colour: %d", YSI_g_sFadeColour);
		// Quite simply, we just change state and return to the calling
		// function.  This allows this function to be called again when the true
		// fade end is reached and the length to be determined.  After that some
		// re-parsing will need to be done I'm afraid, but that will be handled
		// by code dealing with fades which fall over the end of a string, be it
		// due to this or to a known length string being pushed over the end due
		// to the insertion of the colour codes.  Note that this code is display
		// method independent - it works for SendClientMessage, GameText and
		// others.
		state y_render_fade : y_render_fade_fake;
		// The return here causes remaining code to continue as normal, but
		// makes certain functions just not run.
	}
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="out">The destination string.</param>
 * <param name="in">The data to add.</param>
 * <param name="oidx">The index in "out" at which to add data.</param>
 * <param name="len">The length of "in".</param>
 * <param name="orem">Space remaining in "out".</param>
 * <param name="fakePos">Like "oidx", but cumulative over line breaks.</param>
 * <returns>
 *  The amount of data from "in" not added to "out".
 * </returns>
 * <remarks>
 *  Takes an input string and adds it to an output string.  If the input string
 *  is too long to fit in the remainder of the output string, what has been
 *  added already (including part of the input string) is displayed and a new
 *  string is added.  Format_TryShow handles this, including adding formatting
 *  of colour fades, which may involve fake rendering of more of the string to
 *  determine how much of the remainder of the string needs processing to get
 *  the right colour.  This will also require a method of winding back the state
 *  to the point just after the initial input string was added to continue on to
 *  show the next string including newly determined fade data.
 * </remarks>
 * <transition keep="true" target="y_render_fade : y_render_fade_real" source="y_render_fade : y_render_fade_redo" />
 *//*------------------------------------------------------------------------**/

static stock Format_DoAddString(out[], const in[], &oidx, const len, &orem, &fakepos) <y_render_fade : y_render_fade_fake>
{
	#pragma unused out, in, oidx, orem
	fakepos += len;
	return 0;
}

static stock Format_DoAddString(out[], const in[], &oidx, const len, &orem, &fakepos) <y_render_fade : y_render_fade_redo>
{
	new
		temp = fakepos + len - YSI_g_sFadeRedoTarget;
	if (temp > 0)
	{
		state y_render_fade : y_render_fade_real;
		// This is where the string passes the target point of re-rendering.
		new
			other = YSI_g_sFadeRedoTarget - fakepos;
		fakepos += other;
		return Format_DoAddString(out, in[other], oidx, temp, orem, fakepos);
	}
	else
	{
		fakepos += len;
		return 0;
	}
}

static stock Format_DoAddString(out[], const in[], &oidx, const len, &orem, &fakepos) <y_render_fade : y_render_fade_real>
{
	P:4("Format_DoAddString <y_render_fade : render_real> called: \"%s\", \"%s\", %i, %i, %i, %i", out, in, oidx, len, orem, fakepos);
	// For now don't worry about fades over boundaries - they're just too hard
	// to get the code working on to start with, maybe later once this is all
	// working they can be added in.  It is a shame though as it will mean fades
	// don't always work.  I can cheat slightly though and have the full fade on
	// both halves of the break.  Or just warn people about fades like that.
	// 
	// NOTE: This code assumes that orem (output remaining) is always 1 less
	// than the true value.  This avoids awkward calculations when appending the
	// NULL terminator to strings.  When we run out of space it simply appends
	// it regardless of wether it thinks there is space or not.
	// 
	fakepos += len;
	if (len <= orem)
	{
		P:5("Format_DoStringSCM: p0.");
		memcpy(out[oidx], in, 0, len * 4, orem);
		orem -= len;
		oidx += len;
		// The whole string fit in - return true.
		return 0;
	}
	else
	{
		// Not the end of the string, but the end is required.
		// Change state to ignore future inputs.
		P:5("Format_DoStringSCM: p1.");
		// Copy as much data as possible.
		memcpy(out[oidx], in, 0, orem * 4, orem);
		//orem -= orem;
		//oidx += orem;
		// Don't need to adjust this further down as all the characters will be
		// added before the recursive call.
		oidx += orem;
		return len - orem;
	}
}

/*-------------------------------------------------------------------------*//**
 * <transition keep="true" target="y_render_fade : y_render_fade_real" source="y_render_fade : y_render_fade_redo" />
 *//*------------------------------------------------------------------------**/

static stock bool:Format_DoAddChar(out[], const in, &oidx, &orem, &fakepos) <y_render_fade : y_render_fade_fake>
{
	#pragma unused out, in, oidx, orem
	++fakepos;
	return true;
}

static stock bool:Format_DoAddChar(out[], const in, &oidx, &orem, &fakepos) <y_render_fade : y_render_fade_redo>
{
	if (fakepos == YSI_g_sFadeRedoTarget)
	{
		state y_render_fade : y_render_fade_real;
		// This should never actually fail...
		if (!orem) return false;
		--orem;
		out[oidx++] = in;
	}
	++fakepos;
	return true;
}

static stock bool:Format_DoAddChar(out[], const in, &oidx, &orem, &fakepos) <y_render_fade : y_render_fade_real>
{
	P:4("Format_DoAddChar: %c %d %d", in, oidx, orem);
	if (!orem) return false;
	--orem;
	out[oidx++] = in;
	++fakepos;
	return true;
}

static stock Format_DoDisplay(playerid, colour, out[]) <y_render_show : y_render_show_scm>
{
	P:2("Format_DoDisplay a: %d, %06x, \"%s\"", playerid, colour >>> 8, out);
	SendClientMessage(playerid, (colour << 8) | ((YSI_g_sTempStyle[E_STYLE_DATA_COLOUR] & 0x0F) * 0x11), out);
	//idx = 0;
	//out[0] = '\0';
}

static stock Format_DoDisplay(playerid, colour, out[]) <> //y_render_show : y_render_show_print>
{
	P:0("Format_DoDisplay b: %d, %06x, \"%s\"", playerid, colour >>> 8, out);
	//idx = 0;
	//out[0] = '\0';
}

static stock Format_DoDisplay(playerid, colour, out[]) <y_render_show : y_render_show_gt>
{
	#pragma unused colour
	P:2("Format_DoDisplay c: %d, %06x, \"%s\"", playerid, colour >>> 8, out);
	GameTextForPlayer(playerid, out, YSI_g_sTempStyle[E_STYLE_DATA_TIME], YSI_g_sTempStyle[E_STYLE_DATA_STYLE]);
	//SendClientMessage(playerid, (colour << 8) | ((YSI_g_sTempStyle[E_STYLE_DATA_COLOUR] & 0x0F) * 0x11), out);
	//GameTextForPlayer(playerid, out, 
	//SendClientMessage(playerid, colour, out);
	//idx = 0;
	//out[0] = '\0';
}

static stock Format_DoDisplay(playerid, colour, out[]) <y_render_show : y_render_show_td>
{
	#pragma unused colour
	P:2("Format_DoDisplay d: %d, %06x, \"%s\"", playerid, colour >>> 8, out);
	new
		Text:tmp = TD_Display(out, YSI_g_sTempStyle[E_STYLE_DATA_TD_ID]);
	out[0] = _:tmp;
	out[1] = '\0';
	TD_ShowForPlayer(playerid, tmp);
	TD_Garbage(tmp);
	// Link these TDs together for future manipulations.
	if (YSI_g_sBaseTD == TEXT_DRAW_NO_NEXT)
	{
		YSI_g_sBaseTD = tmp;
	}
	else
	{
		TD_Link(YSI_g_sBaseTD, tmp);
	}
	//SendClientMessage(playerid, (colour << 8) | ((YSI_g_sTempStyle[E_STYLE_DATA_COLOUR] & 0x0F) * 0x11), out);
	//GameTextForPlayer(playerid, out, 
	//SendClientMessage(playerid, colour, out);
	//idx = 0;
	//out[0] = '\0';
}

/*-------------------------------------------------------------------------*//**
 * <param name="playerid">Player to show the text to.</param>
 * <param name="out">What the text to show is.</param>
 *//*------------------------------------------------------------------------**/

stock Format_JustShow(playerid, const out[]) <y_render_show : y_render_show_scm>
{
	SendClientMessage(playerid, gInitialColour, out);
}

stock Format_JustShow(playerid, const out[]) <y_render_show : y_render_show_print>
{
	P:0("Format_DoDisplay: %d, \"%s\"", playerid, out);
}

stock Format_JustShow(playerid, const out[]) <y_render_show : y_render_show_gt>
{
	GameTextForPlayer(playerid, out, YSI_g_sTempStyle[E_STYLE_DATA_TIME], YSI_g_sTempStyle[E_STYLE_DATA_STYLE]);
}

stock Format_JustShow(playerid, const out[]) <y_render_show : y_render_show_td>
{
	TD_ShowForPlayer(playerid, Text:out[0]);
}

/*-------------------------------------------------------------------------*//**
 * <returns>
 *  The basic ID linking all displayed elements together where appropriate (for
 *  example SendClientMessage has no meaningful ID.  3D texts would, but that's
 *  not implemented.  So do game texts, but that's not implemented either, so
 *  really it's just text draws.
 * </returns>
 *//*------------------------------------------------------------------------**/

stock Text_GetLastID() <y_render_show : y_render_show_td>
{
	return _:YSI_g_sBaseTD;
}

stock Text_GetLastID() <>
{
	return -1;
}

/*-------------------------------------------------------------------------*//**
 * Generic function to handle rendering for all types of outputs.  Other functions
 * such as Format_AddColour are specialised for different text styles.  The faster
 * way to do this would be to store the characters removed from a string when
 * adding in fade data, but this is hard to code.  The simpler method is to fake
 * re-render the string, having previously determined the length of the string
 * which will be faded across.  Note that this may mean that some parts of the
 * string can get rendered many times, but we can just issue a performance warning
 * when the player uses fades which go over a line boundary.  That is the only time
 * in which it is a problem, more specifically it is only a problem when text in a
 * fade goes over a line boundardy before the end fade marker has been reached.
 * <transition keep="true" target="y_render_fade : y_render_fade_redo" />
 * <transition keep="true" target="y_render_fade : y_render_fade_real" />
 * <transition keep="true" target="y_render_fade : y_render_fade_fake" />
 *//*------------------------------------------------------------------------**/
//stock Format_Render(pid, Language:l, output[], maxlen, idx, target, string[], {Float,_}:...)
stock Format_Render(pid, Language:l, output[], maxlen, idx, target, string[], GLOBAL_TAG_TYPES:...)
{
	P:3("Format_Render called: %i, %i, %s, %i, %i, %i, %s (+%i)", pid, _:l, output, maxlen, idx, target, numargs() - 7);
	gInitialColour = (YSI_g_sTempStyle[E_STYLE_DATA_COLOUR] >>> 4) & 0x00FFFFFF;
	new
		colour = gInitialColour;
	YSI_g_sFadeLength = 0;
	YSI_g_sBaseTD = TEXT_DRAW_NO_NEXT;
	// Now the (mostly) tail-recursive function call.
Format_Render_start:
	static
		scFormats[][8] =
			{
				"%*.*d",  // 6 (6)
				"%-*.*d", // 7 (13)
				"%0*.*d", // 7 (20)
				"%0-*.*d" // 8 (28)
			},
		scSpecifier[8],
		// =====================================================================
		//  UPDATE Y_RENDER_FIX_NEGATIVE MACRO ON CHANGE!!!!!!!
		ts[YSI_MAX_STRING],
		//  Max handleable input string length is 128 (hopefully sufficient).
		// =====================================================================
		func[FUNCTION_LENGTH],
		scNewLineString[] = "~n~",
		scDialogLineString[] = "\r\n";
	new
		ch = 0,
		llen = maxlen,
		//output[128], // Always 128.
		p = 0,
		curArg = 7, // Account for additionaly pushed arguments.
		numArgs = numargs(),
		//llen = sizeof (output) - 1,
		arg = 0,
		none = (target & e_FORMAT_FLAGS_NONE),
		onlyOne = (target & e_FORMAT_FLAGS_ONE) | none | _:YSI_g_sJustOne,
		bool:fade = false,
		bool:nlInFade = false,
		// flags:
		//   1 = Just one output.
		//   2 = Newline found in fade.
		//   4 = In a fade.
		//flags = (target & e_FORMAT_FLAGS_ONE) ? 1 : 0,
		fakePos = 0,
		// Was only "one" string display used and is this not per-player text?
		one = 0,
		// Start location of the current fade.
		fadeStart = 0,
		fadeStartIdx = 0;//,
		//fadeStartText;
	//#emit LOAD.S.pri string
	//#emit STOR.S.pri fadeStartText
	if (target & e_FORMAT_FLAGS_REDO)
	{
		// We need to skip data, ignore everything before "target1".
		state y_render_fade : y_render_fade_redo;
	}
	else
	{
		state y_render_fade : y_render_fade_real;
	}
	target &= e_FORMAT_FLAGS_INDEX;
	/*new
		fadeCurArg = 0,
		fadeArg = 0,
		fadeIdx = 0;*/
	if ((YSI_g_sFadeRedoTarget = target))
	{
		YSI_g_sFadeRedoTarget &= ~Y_FORMAT_ALWAYS_SET;
		state y_render_fade : y_render_fade_redo;
	}
	else
	{
		state y_render_fade : y_render_fade_real;
	}
	/*ch = string[idx];
	if (ch > 0)
	{
		// Copy strings.
		++idx;
		Y_RENDER_ADD_EX(string, idx, ch - idx)
		idx = ch;
	}*/
	while ((ch = string[idx++]))
	{
		// TODO: Add {*} and #* format for variable colours.
		switch (ch)
		{
			case '\01':
			{
				// Null.
				break;
			}
			case '\02':
			{
				P:6("Text_Render: Format specifier %d", curArg);
				if (curArg == numArgs)
				{
					// Skip.
					P:W("Insufficient parameters to YSI format.");
					ts = "(null)";
					Y_RENDER_ADD(ts)
					continue;
				}
				// Format.
				ch = string[idx++];
				new
					width = (ch & _:e_COMPRESS_FORMAT_DATA_WIDTH),
					prec  = (ch & _:e_COMPRESS_FORMAT_DATA_PREC) >>> 12;
				// Get the true values of the various data bits.
				if (width == 0x0800)
				{
					width = getarg(curArg++);
				}
				if (prec == 0x0800)
				{
					prec = getarg(curArg++);
				}
				else if (prec == 0x0FFF)
				{
					prec = -1;
				}
				// Output the correct data type.
				switch (ch & 0xF0000000)
				{
					case e_COMPRESS_FORMAT_DATA_DEC:
					{
						P:6("Text_Render: Add d");
						scSpecifier = Y_RENDER_SPECIFIER(d);
						Y_RENDER_ARG
						{
							//p += Format_AddInt(output[p], llen, arg, width, ch);
							format(ts, sizeof (ts), scSpecifier, width, prec, arg);
							Y_RENDER_ADD(ts)
						}
					}
					case e_COMPRESS_FORMAT_DATA_HEX:
					{
						// This completely fixes (I hope) the problems with
						// displaying negative numbers as %h/%x numbers.
						P:6("Text_Render: Add h");
						scSpecifier = Y_RENDER_SPECIFIER(x);
						Y_RENDER_ARG
						{
							if (arg & 0x80000000)
							{
								Y_RENDER_FIX_NEGATIVE(x:8);
							}
							else
							{
								format(ts, sizeof (ts), scSpecifier, width, prec, arg);
							}
							Y_RENDER_ADD(ts)
						}
					}
					case e_COMPRESS_FORMAT_DATA_BIN:
					{
						P:6("Text_Render: Add b");
						scSpecifier = Y_RENDER_SPECIFIER(b);
						Y_RENDER_ARG
						{
							if (arg & 0x80000000)
							{
								Y_RENDER_FIX_NEGATIVE(b:32);
							}
							else
							{
								format(ts, sizeof (ts), scSpecifier, width, prec, arg);
							}
							Y_RENDER_ADD(ts)
						}
					}
					case e_COMPRESS_FORMAT_DATA_CHAR:
					{
						scSpecifier = Y_RENDER_SPECIFIER(c);
						Y_RENDER_ARG
						{
							//p += Format_AddInt(output[p], llen, arg, width, ch);
							format(ts, sizeof (ts), scSpecifier, width, prec, arg);
							Y_RENDER_ADD(ts)
						}
					}
					case e_COMPRESS_FORMAT_DATA_FLOAT:
					{
						scSpecifier = Y_RENDER_SPECIFIER(f);
						Y_RENDER_ARG
						{
							//p += Format_AddInt(output[p], llen, arg, width, ch);
							format(ts, sizeof (ts), scSpecifier, width, prec, arg);
							Y_RENDER_ADD(ts)
						}
					}
					case e_COMPRESS_FORMAT_DATA_IEEE:
					{
						Y_RENDER_ARG
						{
							if ((arg & 0x7F800000) == 0x7F800000)
							{
								scSpecifier = Y_RENDER_SPECIFIER(s);
								// One of the special numbers.
								if (arg & 0x007FFFFF)
								{
									// NAN.
									if (arg & 0x00400000)
									{
										// QNAN
										format(ts, sizeof (ts), scSpecifier, width, cellmax, "QNAN");
										Y_RENDER_ADD(ts)
									}
									else
									{
										// SNAN
										format(ts, sizeof (ts), scSpecifier, width, cellmax, "SNAN");
										Y_RENDER_ADD(ts)
									}
								}
								else
								{
									if (arg & 0x80000000)
									{
										// -INFINITY
										format(ts, sizeof (ts), scSpecifier, width, cellmax, "-INFINITY");
										Y_RENDER_ADD(ts)
									}
									else
									{
										// INFINITY
										format(ts, sizeof (ts), scSpecifier, width, cellmax, "INFINITY");
										Y_RENDER_ADD(ts)
									}
								}
							}
							else
							{
								scSpecifier = Y_RENDER_SPECIFIER(f);
								format(ts, sizeof (ts), scSpecifier, width, prec, arg);
								Y_RENDER_ADD(ts)
							}
						}
					}
					case e_COMPRESS_FORMAT_DATA_STRING:
					{
						scSpecifier = Y_RENDER_SPECIFIER(s);
						if (ch & _:e_COMPRESS_FORMAT_DATA_FUNC)
						{
							func = "@yR_";
							// Get the function name.
							for (new _k = 4; _k != FUNCTION_LENGTH; ++_k)
							{
								if (!(func[_k] = getarg(curArg, _k - 4)))
								{
									break;
								}
							}
							if (funcidx(func) == -1)
							{
								// Normal version.  This is ended by a null.
								// Other functions get the count in advance when
								// an index of -1 is passed.
								func[2] = 'r';
								// This code mimicks much of the internal
								// y_master code because wrapping this in a
								// macro is a) pointless and b) hard.  This code
								// is ALWAYS like this because of the nature of
								// it.
								new
									lst = setproperty(8, YSIM_CALLER),
									_j = 0;
								setproperty(8, YSIM_CALLER, Master_ID());
								for ( ; ; )
								{
									CallRemoteFunction(func, "ii", _:l, _j);
									// Resolve the string.
									getproperty(8, "", YSIM_STRING, Q@);
									strunpack(Q@, Q@);
									if (Q@[0])
									{
										if (_j)
										{
											// Separate the strings - hard coded
											// list format currently I'm afraid.
											//ts = ", ";
											//Y_RENDER_ADD(ts)
											Y_RENDER_ADD(YSI_g_sListSep)
										}
										format(ts, sizeof (ts), scSpecifier, width, prec, Q@);
										Y_RENDER_ADD(ts)
									}
									else
									{
										break;
									}
									++_j;
								}
								setproperty(8, YSIM_CALLER, lst);
							}
							else
							{
								// Player specific version.
								// Normal version.  This is ended by a null.
								// Other functions get the count in advance when
								// an index of -1 is passed.
								//func[2] = 'r';
								// This code mimicks much of the internal
								// y_master code because wrapping this in a
								// macro is a) pointless and b) hard.  This code
								// is ALWAYS like this because of the nature of
								// it.
								new
									lst = setproperty(8, YSIM_CALLER),
									_j = 0;
								setproperty(8, YSIM_CALLER, Master_ID());
								for ( ; ; )
								{
									CallRemoteFunction(func, "iii", pid, _:l, _j);
									// Resolve the string.
									getproperty(8, "", YSIM_STRING, Q@);
									strunpack(Q@, Q@);
									if (Q@[0])
									{
										if (_j)
										{
											// Separate the strings - hard coded
											// list format currently I'm afraid.
											//ts = ", ";
											//Y_RENDER_ADD(ts)
											Y_RENDER_ADD(YSI_g_sListSep)
										}
										// Could do with configuring this to not
										// need to call "Y_RENDER_SPECIFIER" every
										// time.
										format(ts, sizeof (ts), scSpecifier, width, prec, Q@);
										Y_RENDER_ADD(ts)
									}
									else
									{
										break;
									}
									++_j;
								}
								setproperty(8, YSIM_CALLER, lst);
								// Force the string to be rebuilt every time.
								++one;
							}
						}
						else
						{
							// Single parameter.  Can do this FAR better by just
							// using #emit to re-push the parameter directly.
							for (new _k = 0; _k != sizeof (ts); ++_k)
							{
								if (!(ts[_k] = getarg(curArg, _k)))
								{
									break;
								}
							}
							format(ts, sizeof (ts), scSpecifier, width, prec, ts);
							Y_RENDER_ADD(ts)
						}
						++curArg;
					}
					/*case e_COMPRESS_FORMAT_DATA_OCT:
					{
						Y_RENDER_ARG
						{
							//p += Format_AddInt(output[p], llen, arg, width, ch);
							//format(ts, sizeof (ts), Y_RENDER_SPECIFIER(f), width, prec, arg);
							ts[Format_AddOct(ts, sizeof (ts) - 1, arg, width, ch)] = '\0';
							Y_RENDER_ADD(ts)
						}
					}*/
					case e_COMPRESS_FORMAT_DATA_COMM:
					{
						scSpecifier = Y_RENDER_SPECIFIER(s);
						// Show a command.
						/*for(new _i=0,_b=4;_i!=2;++_i)
							if(_i==0)
							{
								if(ch&_:e_COMPRESS_FORMAT_DATA_FUNC)
								{
									_b=1,func="@yR_";
									for(new _k=4;_k!=FUNCTION_LENGTH;++_k)
										if(!(func[_k]=getarg(curArg,_k-4)))
											break;
									if(funcidx(func)==-1)func[2]='r',_b=2;
								}
								else if(ch&_:e_COMPRESS_FORMAT_DATA_LIST)
									_b=3;
							}
							else
								for(new _j=0;(arg=_b==1?W@(func,"iii",pid,(_:l),_j):_b==2?W@(func,"ii",(_:l),_j):_b==3?getarg(curArg,_j++):getarg(curArg)),(_j!=-1&&_b)?TRUE:++curArg&&FALSE;_b=_b==4?0:_b)*/
						Y_RENDER_ARG
						{
							//p += Format_AddInt(output[p], llen, arg, width, ch);
							//format(ts, sizeof (ts), Y_RENDER_SPECIFIER(f), width, prec, arg);
							// "arg" has the ID of the command, not the NAME of
							// the command which may change for different people
							// (need to find a way to return a single name for a
							// player which gets to the specified command).
							#if defined _inc_y_commands
								StrCpy(ts, Command_GetDisplay(arg, pid));
								if (ts[0])
								{
									format(ts, sizeof (ts), scSpecifier, width, prec, ts);
									Y_RENDER_ADD(ts)
								}
							#endif
							//ts[Format_AddOct(ts, sizeof (ts) - 1, arg, width, ch)] = '\0';
							//Y_RENDER_ADD(ts)
						}
					}
					/*case e_COMPRESS_FORMAT_DATA_SUFFIX:
					{
						scSpecifier = Y_RENDER_SPECIFIER(s);
						// TODO: Add language to this.
						//p += Format_AddSuffix(output[p], llen, getarg(curArg++), l);
						Y_RENDER_ARG
						{
							format(ts, sizeof (ts), scSpecifier, width, cellmax, Format_AddSuffix(arg, l));
							Y_RENDER_ADD(ts)
						}
					}
					case e_COMPRESS_FORMAT_DATA_UNSIGNED:
					{
						if (prec < 0) prec = 10;
						Y_RENDER_ARG
						{
							//p += Format_AddInt(output[p], llen, arg, width, ch);
							//format(ts, sizeof (ts), Y_RENDER_SPECIFIER(f), width, prec, arg);
							//ts[Format_AddOct(ts, sizeof (ts) - 1, arg, width, ch)] = '\0';
							ts[Format_AddNum(ts, sizeof (ts) - 1, arg, width, ch, prec, false)] = '\0';
							Y_RENDER_ADD(ts)
						}
					}
					case e_COMPRESS_FORMAT_DATA_SIGNED:
					{
						if (prec < 0) prec = 10;
						Y_RENDER_ARG
						{
							//p += Format_AddInt(output[p], llen, arg, width, ch);
							//format(ts, sizeof (ts), Y_RENDER_SPECIFIER(f), width, prec, arg);
							ts[Format_AddNum(ts, sizeof (ts) - 1, arg, width, ch, prec, true)] = '\0';
							Y_RENDER_ADD(ts)
						}
					}*/
					case e_COMPRESS_FORMAT_DATA_PLAYER:
					{
						Y_RENDER_ARG
						{
							//p += Format_AddInt(output[p], llen, arg, width, ch);
							GetPlayerName(arg, ts, sizeof (ts));
							format(ts, sizeof (ts), scSpecifier, width, prec, ts);
							Y_RENDER_ADD(ts)
						}
					}
					case e_COMPRESS_FORMAT_DATA_LOGICAL: 
					{
						scSpecifier = Y_RENDER_SPECIFIER(s);
						Y_RENDER_ARG
						{
							//p += Format_AddInt(output[p], llen, arg, width, ch);
							format(ts, sizeof (ts), scSpecifier, width, prec, arg ? ("true") : ("false"));
							Y_RENDER_ADD(ts)
						}
					}
					case e_COMPRESS_FORMAT_DATA_CUSTOM:
					{
						// Get the function we will be calling to do the format.
						// Slice caches these, but we don't because of the
						// extended versions (%k<DATE>) etc.
						new
							ffake[4 char],
							fidx = 0;
						ffake[0] = string[idx];
						if (ffake{1} == '@')
						{
							if (!AMX_GetPublicPointer(0, fidx, ffake))
							{
								continue;
							}
							++idx;
						}
						else
						{
							static
								sFunc2[FUNCTION_LENGTH] = "F";
							strunpack(sFunc2[1], string[idx], sizeof (sFunc2) - 1);
							// Limit the function name to the function length.
							sFunc2[sFunc2[1]] = '\0';
							idx += ceildiv(sFunc2[1], 4);
							sFunc2[1] = '@';
							if (!AMX_GetPublicPointer(0, fidx, sFunc2))
							{
								continue;
							}
						}
						// 
						//  "b":
						// 
						// "b" is the source type.  "1" = function, "2" = per-
						// player function, "3" = list, "4" = variable.  "0" is
						// a special case meaning "processed variable" and tells
						// the system to stop "j != -1 && b".
						// 
						//  "i":
						// 
						// "i" is the current processing stage - there are two.
						// The first looks at all the arguments and collects the
						// function or list data (if any).  The second loops
						// over all the passed arguments and does the format.
						// This is where the "b" check comes in, to only do that
						// inner loop once.  It is done this way simply to allow
						// us to use braces around the code to do the format.
						// 
						//  "j":
						// 
						// "j" is the main loop variable for the inner loop and
						// tracks which parameter part we are currently doing in
						// the case of function or list inputs.
						// 
						for (new i = 0, j = 0, b = 4; i != 2; ++i)
						{
							if (!i)
							{
								if (ch & _:e_COMPRESS_FORMAT_DATA_FUNC)
								{
									b = 1;
									func = "@yR_";
									va_getstring(func[4], curArg);
									if (funcidx(func) == -1)
									{
										b = 2;
										func[2] = 'r';
									}
								}
								else if (ch & _:e_COMPRESS_FORMAT_DATA_LIST)
								{
									b = 3;
								}
								ch &= FORMAT_FLAG_LEFT | FORMAT_FLAG_ZERO;
							}
							else
							{
								for (;
										// These lines ALWAYS get run because
										// they come before a comma in the "for"
										// conditional, but their result is
										// ignored.
										(arg = (b == 1)
											? W@(func, "iii", pid, (_:l), j)
											: (b == 2)
												? W@(func, "ii", (_:l), j)
												: (b == 3)
													? getarg(curArg, j++)
													: getarg(curArg)
										),
										// This is the true condition.  If the
										// first half fails then "curArg" is
										// incremented and the whole check
										// fails, otherwise, thanks to short-
										// circuiting, "curArg" is NOT
										// incremented.
										(arg != cellmin && b) || (++curArg & 0);
									// Only run the loop once when "b = 4".
									b &= ~4, ++j
									)
								{
									// Standard format code goes here.
									#emit PUSH.S       prec
									#emit PUSH.S       width
									#emit PUSH.S       ch
									// Get the source (assume constant for now,
									// i.e. no functions or lists yet).
									#emit PUSH.S       arg
									// Get a string if there is one.
									if (b == 1 || b == 2)
									{
										getproperty(8, "", YSIM_STRING, Q@);
										strunpack(Q@, Q@);
										if (IsNull(Q@))
										{
											++curArg;
											// Fix the stack.
											#emit POP.pri
											#emit POP.pri
											#emit POP.pri
											#emit POP.pri
											break;
										}
										#emit PUSH.C       Q@
									}
									else
									{
										#emit LCTRL        5
										#emit LOAD.S.alt   curArg
										#emit SHL.C.alt    2
										#emit ADD
										#emit LOAD.I
										#emit PUSH.pri
									}
									#emit PUSH.C       ts
									// Far more parameters that Slice's.
									#emit PUSH.C       24 // 4 * 6.
									// This code is almost common now!
									#emit LCTRL        6
									#emit ADD.C        28
									#emit PUSH.pri
									#emit LOAD.S.pri   fidx
									#emit SCTRL        6
									// Now we have returned from the custom
									// function.
									Y_RENDER_ADD(ts)
								}
							}
						}
					}
					/*case e_COMPRESS_FORMAT_DATA_DATE:
					{
						// Hard one - needs more interaction.
					}*/
				}
			}
			case '\03', -1:
			{
				P:6("Text_Render: Colour %d %d %d %d %d %06x %s", p, llen, fadeStart, fakePos, idx, colour & 0xFFFFFF, string);
				if (fade) //flags & 4)
				{
					p = fadeStart;
					new
						rem = Format_DoEndFade(output, p, fakePos, llen, string[idx], colour);
					if (rem || nlInFade) //(flags & 2))
					{
						// "rem" is the number of characters not processed.
						YSI_g_sFadeColour = colour;
						Y_RENDER_DO_DISPLAY()
						P:6("Format_Render: one stage: \"%s\"", output);
						// Subtract 2 to get the index in to the fade where the
						// letters start.  This is not as easy as it used to be
						// as we need to manipulate the stack to push the extra
						// parameters somehow.  Now changed to a fake tail-
						// recursive call so that we don't need to worry about
						// the stack.  This also explains why labels generate
						// extra stack manipulation code (to reset locals).
						//return Format_Render(pid, l, output, maxlen, fadeStartIdx, fakePos - fadeStart - rem | e_FORMAT_FLAGS_REDO, string);
						//#emit LOAD.S.pri fadeStartText
						//#emit STOR.S.pri string
						idx = fadeStartIdx;
						target = (fakePos - fadeStart - rem) | e_FORMAT_FLAGS_REDO;
						gInitialColour = colour;
						//YSI_g_sTempStyle[E_STYLE_DATA_COLOUR] = (YSI_g_sTempStyle[E_STYLE_DATA_COLOUR] & 0xF000000F) | (gInitialColour << 4);
						goto Format_Render_start;
						// We don't need these as they are only set when you
						// want less than 2 displays, and as to get to this
						// point you need to have shown at least noe item there
						// is no possible way they can be set the second time.
						//| (onlyOne ? e_FORMAT_FLAGS_ONE : 0) | (none ? e_FORMAT_FLAGS_NONE : 0);
					}
					//flags &= ~4;
					fade = false;
					fakePos += p - fadeStart;
				}
				if (string[idx] & Y_FORMAT_CLOSE_CURR)
				{
					// Get the initial display colour.
					//string[idx] |= (YSI_g_sTempStyle[E_STYLE_DATA_COLOUR] >>> 4) & 0x00FFFFFF;
					string[idx] = (string[idx] & 0xFF000000) | ((YSI_g_sTempStyle[E_STYLE_DATA_COLOUR] >>> 4) & 0x00FFFFFF);
				}
				if (string[idx] & Y_FORMAT_START_FADE)
				{
					//flags |= 4;
					fade = true;
					fadeStart = p;
					fadeStartIdx = idx - 1;
					string[fadeStartIdx] = -1;
					//#emit LOAD.S.pri string
					//#emit STOR.S.pri fadeStartText
					if (p < maxlen - 1)
					{
						output[p++] = '\03';
						output[p++] = string[idx++];
					}
				}
				else
				{
					// Just add the colour here normally.
					arg = Format_AddColour(output, p, llen, colour, string[idx++]); //& ~(Y_FORMAT_START_FADE | Y_FORMAT_ALWAYS_SET));
					switch (arg)
					{
						case -1:
						{
							Y_RENDER_DO_DISPLAY()
						}
						case 0:
						{
							// Do nothing.
						}
						default:
						{
							p += arg;
							fakePos += arg;
						}
					}
					/*else
					{
						p += arg;
					}
					currentColour = string[idx++];
					if (maxlen - pos > Y_RENDER_SCM_COLOUR_LEN)
					{
						format(output[pos], maxlen - pos, "{%06x}", currentColour & ~(Y_FORMAT_START_FADE | Y_FORMAT_ALWAYS_SET));
						pos += Y_RENDER_SCM_COLOUR_LEN;
					}
					else
					{
						output[pos] = '\0';
						printf("some stage: \"%s\"", output);
						output[0] = '\0';
						pos = 0;
					}*/
					//++idx;
				}
			}
			case '\04':
			{
				P:6("Text_Render: Key");
				Format_GetKeyString(ts, string[idx++] >>> 8);
				new __len=strlen(ts);
				if (llen < __len)
					Y_RENDER_DO_DISPLAY()
				llen -= __len,
				output[p] = '\0',
				p += __len,
				strcat(output, ts, maxlen);
			}
			case '\n':
			{
				P:6("Text_Render: NL");
				// Check for 2 character new lines (\n\r).
				if (string[idx] == '\r') ++idx;
				// Output the last string.
				if (fade) //flags & 4)
				{
					//flags |= 2;
					nlInFade = true;
					state y_render_fade : y_render_fade_fake;
				}
				else if ((YSI_g_sTempStyle[E_STYLE_DATA_TYPE] & e_STYLE_TYPE_MASK) < e_STYLE_TYPE_CLIENT)
				{
					// This works even for GTs which are always 0 by this point.
					Y_RENDER_ADD(scNewLineString)
				}
				else if (YSI_g_sTempStyle[E_STYLE_DATA_TYPE] == e_STYLE_TYPE_DIALOG)
				{
					//print("NL 1");
					// This works even for GTs which are always 0 by this point.
					Y_RENDER_ADD(scDialogLineString)
					//print("NL 2");
				}
				else
				{
					Y_RENDER_DO_DISPLAY()
					gInitialColour = colour;
				}
			}
			case '\r':
			{
				P:6("Text_Render: NL");
				// Check for 2 character new lines (\r\n).
				if (string[idx] == '\n') ++idx;
				// Output the last string.
				if (fade) //flags & 4)
				{
					//flags |= 2;
					nlInFade = true;
					state y_render_fade : y_render_fade_fake;
				}
				else if ((YSI_g_sTempStyle[E_STYLE_DATA_TYPE] & e_STYLE_TYPE_MASK) < e_STYLE_TYPE_CLIENT)
				{
					// This works even for GTs which are always 0 by this point.
					Y_RENDER_ADD(scNewLineString)
				}
				else if (YSI_g_sTempStyle[E_STYLE_DATA_TYPE] == e_STYLE_TYPE_DIALOG)
				{
					// This works even for GTs which are always 0 by this point.
					//print("NL 3");
					Y_RENDER_ADD(scDialogLineString)
					//print("NL 4");
				}
				else
				{
					Y_RENDER_DO_DISPLAY()
				}
			}
			case '\t':
			{
				// Omit this on dialogs.
				if (YSI_g_sTempStyle[E_STYLE_DATA_TYPE] != e_STYLE_TYPE_DIALOG)
				{
					// Somehow display a tab.  Maybe keep track of characters
					// displayed and show "n % 4" spaces.
					arg = 4 - (p & 0x03); // The number of spaces to add.
					static
						sTabs[] = "    ";
					for (new __added = 0; (__added = Format_DoAddString(output, sTabs[4 - arg], p, arg, llen, fakePos)); arg -= __added)
					{
						if (fade) //flags & 4)
						{
							state y_render_fade : y_render_fade_fake;
						}
						else
						{
							Y_RENDER_DO_DISPLAY()
						}
					}
				}
				else
				{
					 Y_RENDER_CHAR(ch)
				}
			}
			case '\06' .. '\08', '\11', '\12', '\14' .. '\32':
			{
				// Whitespace.  Just show a space, not the fancy character, no
				// idea what it could do.  Note that this range includes spaces.
				P:6("Text_Render: Space");
				Y_RENDER_CHAR(' ')
			}
			default:
			{
				P:6("Text_Render: Char");
				Y_RENDER_CHAR(ch)
			}
		}
		/*if (!(ch = string[idx]))
		{
			break;
		}
		// Copy strings.
		++idx;
		Y_RENDER_ADD_EX(string, idx, ch - idx)
		idx = ch;*/
		P:6("Text_Render: Loop: p = %d, llen = %d, output = \"%s\"", p, llen, (output[p] = '\0', output));
	}
	P:5("Text_Render: Final render?");
	if (p)
	{
		P:5("Text_Render: Yes!");
		output[p] = '\0';
		if (!none) Format_DoDisplay(pid, gInitialColour, output);
		++one;
	}
	P:5("Text_Render: p = %d, output = \"%s\"", p, output);
	P:C(idx=0;while ((ch = output[idx++]))printf("%04x%04x = %c", ch >>> 16, ch & 0xFFFF, ch););
	P:5("Text_Render end");
	return one;
}

