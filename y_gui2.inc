//#define Y_GUI_Y_ADJUST (3.0476190476)
//#define Y_GUI_Y_ADJUST (3.0)
//#define Y_GUI_Y_ADJUST (3.1060948081)

#include "y_iterate"
#include "y_playerset"
#include "y_hooks"

#define MAX_GUI_TEXT_LENGTH (32)
#define MAX_GUI_ELEMENTS (256)

#define NO_GUI (GUI:cellmin)

enum E_GUI_SLOT
{
	Float:E_GUI_SLOT_X,
	Float:E_GUI_SLOT_Y,
	Float:E_GUI_SLOT_W,
	Float:E_GUI_SLOT_H,
	E_GUI_SLOT_TEXT[MAX_GUI_TEXT_LENGTH char],
	E_GUI_SLOT_COLOUR,
	E_GUI_SLOT_BORDER,
	Text:E_GUI_SLOT_TD,
	E_GUI_SLOT_NEXT
}

static stock
	YSI_gsFreeSlot = 0,
	YSI_gsGUIData[MAX_GUI_ELEMENTS][E_GUI_SLOT];

hook OnScriptInit()
{
	for (new i = 0; i != MAX_GUI_ELEMENTS; ++i)
	{
		YSI_gsGUIData[i][E_GUI_SLOT_NEXT] = i + 1;
		YSI_gsGUIData[i][E_GUI_SLOT_TD] = Text:-1;
	}
	YSI_gsGUIData[MAX_GUI_ELEMENTS - 1][E_GUI_SLOT_NEXT] = cellmin;
}

stock Text:GUI_DrawBox(Float:x, Float:y, Float:width, Float:height, colour, string:text[] = "", border = 0)
{
	// Does the rendering for a part of a GUI.  I spent a long time callibrating
	// these display modifications, so they should be pretty accurate.  At least
	// they were tested at 1280 and 1680 (as that's as high as I can go).
	new
		//Text:hnd = TextDrawCreate(x, y, text);
		//Text:hnd = TextDrawCreate((x * 2.0 + width) / 2.0, 0.9308510638 * (y + 4.0), "_");
		Text:hnd = TextDrawCreate((x * 2.0 + width) / 2.0, (y + 3.4) / 1.0711904762 - 1.5, "_");
		//Text:hnd = TextDrawCreate((x * 2.0 + width) / 2.0, y, "_");
	TextDrawUseBox(hnd, true);
	// Subtract 8 to get the correct width (letter border maybe)...
	//TextDrawTextSize(hnd, 0.0, width - 8.0);
	// DON'T subtract when not on 640x480...
	// 4.0 works for 1280x960, 3.0485 works for 1280x960 AND 1680x1050, don't
	// know about larger but this I think is fairly well tweaked.
	TextDrawTextSize(hnd, 0.0, width - 3.0485); // - Y_GUI_Y_ADJUST);
	//TextDrawTextSize(hnd, x + width, height);
	//TextDrawTextSize(hnd, 0.1, 0.1);
	//TextDrawLetterSize(hnd, 1.0, height * 0.064);
	//TextDrawLetterSize(hnd, 1.0, height); // * 0.135);
	TextDrawLetterSize(hnd, 1.0, (height - 4.0) / 9.58); //10.29); // was 9.65
	TextDrawBoxColor(hnd, colour);
	TextDrawColor(hnd, 0x0000FFFF);
	TextDrawBackgroundColor(hnd, 0xFF0000FF);
	TextDrawSetOutline(hnd, 0);
	//TextDrawSetProportional(hnd, true);
	TextDrawAlignment(hnd, 2);
	return hnd;
}

stock GUI:GUI_Create(Float:x, Float:y, Float:width, Float:height, text[] = "", colour = 0xE4E4E4FF, border = 0)
{
	// Get the next free ID.
	if (YSI_gsFreeSlot == cellmin)
	{
		return NO_GUI;
	}
	new
		slot = YSI_gsFreeSlot;
	YSI_gsFreeSlot = YSI_gsGUIData[slot][E_GUI_SLOT_NEXT];
	YSI_gsGUIData[slot][E_GUI_SLOT_NEXT] = cellmin;
	YSI_gsGUIData[slot][E_GUI_SLOT_X] = x;
	YSI_gsGUIData[slot][E_GUI_SLOT_Y] = y;
	YSI_gsGUIData[slot][E_GUI_SLOT_W] = width;
	YSI_gsGUIData[slot][E_GUI_SLOT_H] = height;
	YSI_gsGUIData[slot][E_GUI_SLOT_COLOUR] = colour;
	YSI_gsGUIData[slot][E_GUI_SLOT_BORDER] = border;
	strpack(YSI_gsGUIData[slot][E_GUI_SLOT_TEXT], text);
	return GUI:slot;
}

static stock bool:GUI_Link(GUI:x, GUI:parent)
{
	if (x == NO_GUI || parent == NO_GUI)
	{
		return false;
	}
	new
		slot = YSI_gsGUIData[_:parent][E_GUI_SLOT_NEXT];
	YSI_gsGUIData[_:x][E_GUI_SLOT_NEXT] = slot;
	YSI_gsGUIData[_:parent][E_GUI_SLOT_NEXT] = _:x;
	return true;
}

stock GUI_Button(GUI:parent, Float:xOffset, Float:yOffset, Float:width, Float:height, text[])
{
	xOffset += YSI_gsGUIData[_:parent][E_GUI_SLOT_X];
	yOffset += YSI_gsGUIData[_:parent][E_GUI_SLOT_Y];
	return GUI_Link(GUI_Create(xOffset, yOffset, width, height, text, 0xC0C0C0FF), parent);
}

static stock GUI_ShowOne(gui[E_GUI_SLOT])
{
	if (gui[E_GUI_SLOT_TD] == -1)
	{
		gui[E_GUI_SLOT_TD] = GUI_DrawBox(gui[E_GUI_SLOT_X], gui[E_GUI_SLOT_Y], gui[E_GUI_SLOT_W], gui[E_GUI_SLOT_H], gui[E_GUI_SLOT_COLOUR], gui[E_GUI_SLOT_TEXT], gui[E_GUI_SLOT_BORDER]);
	}
	return gui[E_GUI_SLOT_NEXT];
}

#define GUI_Show PSF:_GUI_Show
stock _GUI_Show(@PlayerSet:players, GUI:gui)
{
	new
		cur = _:gui;
	while (cur != cellmin)
	{
		cur = GUI_ShowOne(YSI_gsGUIData[cur]);
	}
	foreach (new i : PS(players))
	{
		cur = _:gui;
		while (cur != cellmin)
		{
			TextDrawShowForPlayer(i, YSI_gsGUIData[cur][E_GUI_SLOT_TD]);
			cur = YSI_gsGUIData[cur][E_GUI_SLOT_NEXT];
		}
	}
}

stock GUI:GUI_Window(Float:x, Float:y, Float:width, Float:height, title[])
{
	new
		GUI:base = GUI_Create(x, y, width, height, _, 0xE4E4E4FF),
		GUI:other;
	if (base == NO_GUI)
	{
		return NO_GUI;
	}
	// Do window elements in reverse Z-order.
	// Close button.
	other = GUI_Create(x + width - 8.5, y + 1.5, 7.0, 7.0, "x", 0xC0C0C0FF);
	if (other == NO_GUI)
	{
		// Free "base".
		return NO_GUI;
	}
	GUI_Link(other, base);
	// Title bar.
	other = GUI_Create(x, y, width, 10.0, title, 0x0000FFFF);
	if (other == NO_GUI)
	{
		// Free "base".
		return NO_GUI;
	}
	GUI_Link(other, base);
	return base;
}
