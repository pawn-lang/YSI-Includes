/*----------------------------------------------------------------------------*\
 | y_GUI
\*----------------------------------------------------------------------------*/


#include <a_samp>

#include "y_bit"


/*----------------------------------------------------------------------------*/


#if !defined MAX_GUIS
	#define MAX_GUIS							(32)
#endif

#if MAX_GUIS < 1
	#undef	MAX_GUIS
	#define MAX_GUIS							(1)
#endif



#if !defined MAX_GUI_ELEMENTS
	#define MAX_GUI_ELEMENTS						(16)
#endif

#if MAX_GUI_ELEMENTS < 1
	#undef  MAX_GUI_ELEMENTS
	#define MAX_GUI_ELEMENTS						(1)
#endif



#if !defined MAX_GUI_ELEMENTS_LENGTH
	#define MAX_GUI_ELEMENTS_LENGTH					(32)
#endif

#if MAX_GUI_ELEMENTS < 1
	#undef  MAX_GUI_ELEMENTS_LENGTH
	#define MAX_GUI_ELEMENTS_LENGTH					(16)
#endif

#define NO_GUI (GUI:-1)

/*----------------------------------------------------------------------------*/

#define GUI_IsValid(%0) ((GUI:0 <= (%0) < GUI:MAX_GUIS) && Bit_Get(YSI_g_sGUIBeingUsed, (%0)))

/*----------------------------------------------------------------------------*/

static stock
	BitArray: YSI_g_sGUIBeingUsed<MAX_GUIS>,										// Being used
	
	// Title variables
	BitArray: YSI_g_sGUITitleUsing<MAX_GUIS>,         // Using title
			  YSI_g_sGUITitleText[MAX_GUIS][64 char], // Title text (Packed)
	   Float: YSI_g_sGUITitlePos[MAX_GUIS][2],        // Position
	   Float: YSI_g_sGUITitleSize[MAX_GUIS][2],       // Size
			  YSI_g_sGUITitleColor[MAX_GUIS],									// Text color
	BitArray: YSI_g_sGUITitleBox<MAX_GUIS>,										// Using box
	   Float: YSI_g_sGUITitleBPos[MAX_GUIS][2],									// Box Position
	   Float: YSI_g_sGUITitleBSize[MAX_GUIS][2],									// Box Size
			  YSI_g_sGUITitleBColor[MAX_GUIS],									// Box color
	
	// Items (buttons)
	BitArray: YSI_g_sGUIItemUsing[MAX_GUIS]<MAX_GUI_ELEMENTS>,							// Using button
			  YSI_g_sGUIItemText[MAX_GUIS][MAX_GUI_ELEMENTS][MAX_GUI_ELEMENTS_LENGTH char],		// Button text (Packed string)
	   Float: YSI_g_sGUIItemPos[MAX_GUIS][MAX_GUI_ELEMENTS][2],							// Button position
	   Float: YSI_g_sGUIItemSize[MAX_GUIS][MAX_GUI_ELEMENTS][2],							// Button size
	   Float: YSI_g_sGUIItemBSize[MAX_GUIS][MAX_GUI_ELEMENTS],							// Buttom box size
	   		  YSI_g_sGUIItemColor[MAX_GUIS][MAX_GUI_ELEMENTS],							// Button color
	   		  YSI_g_sGUIItemBColor[MAX_GUIS][MAX_GUI_ELEMENTS],							// Button box color

	// Textdraws
	    Text: YSI_g_sGUITextTitle[MAX_GUIS][2],
	    Text: YSI_g_sGUITextButton[MAX_GUIS][MAX_GUI_ELEMENTS],



	// Per player variables
	BitArray: YSI_g_spGUIUsing<MAX_PLAYERS>,
			  YSI_g_spGUI[MAX_PLAYERS],
			  YSI_g_spGUITick[MAX_PLAYERS],
			  YSI_g_spGUIItem[MAX_PLAYERS];


/*----------------------------------------------------------------------------*/


stock
	GUI_ShowForPlayer(playerid, GUI: gui)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:gui))
			return 0;

		// ---------------------------------------------------------------------

		if (!Bit_Get(YSI_g_spGUIUsing, playerid))
			Bit_Let(YSI_g_spGUIUsing, playerid);

		// ---------------------------------------------------------------------

		YSI_g_spGUI[playerid]	  = _:gui;
		YSI_g_spGUIItem[playerid] = 0;

		// ---------------------------------------------------------------------

		if (Bit_Get(YSI_g_sGUITitleUsing, _:gui))
			TextDrawShowForPlayer(playerid, YSI_g_sGUITextTitle[_:gui][0]);

		if (Bit_Get(YSI_g_sGUITitleBox, _:gui))
			TextDrawShowForPlayer(playerid, YSI_g_sGUITextTitle[_:gui][1]);

		// ---------------------------------------------------------------------

		// Maybe you can use y_iterate here
		for (new pos; pos < MAX_GUI_ELEMENTS; pos ++)
			if (Bit_Get(YSI_g_sGUIItemUsing[_:gui], pos))
				TextDrawShowForPlayer(playerid, YSI_g_sGUITextButton[_:gui][pos]);

		// ---------------------------------------------------------------------

		return 1;
	}

stock
	GUI_HideForPlayer(playerid)
	{
		if (!Bit_Get(YSI_g_spGUIUsing, playerid))
			return 0;

		// ---------------------------------------------------------------------

		Bit_Vet(YSI_g_spGUIUsing, playerid);

		// ---------------------------------------------------------------------

		YSI_g_spGUI[playerid]	  = 0;
		YSI_g_spGUIItem[playerid] = 0;

		// ---------------------------------------------------------------------

		if (Bit_Get(YSI_g_sGUITitleUsing, _:gui))
			TextDrawHideForPlayer(playerid, YSI_g_sGUITextTitle[_:gui][0]);

		if (Bit_Get(YSI_g_sGUITitleBox, _:gui))
			TextDrawHideForPlayer(playerid, YSI_g_sGUITextTitle[_:gui][1]);

		// ---------------------------------------------------------------------

		// Maybe you can use y_iterate here
		for (new pos; pos < MAX_GUI_ELEMENTS; pos ++)
			if (Bit_Get(YSI_g_sGUIItemUsing[_:gui], pos))
				TextDrawHideForPlayer(playerid, YSI_g_sGUITextButton[_:gui][pos]);

		// ---------------------------------------------------------------------

		return 1;
	}


/*----------------------------------------------------------------------------*/


stock GUI:GUI_Create()
{
	for (new pos = 0; pos != MAX_GUIS; ++pos)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, pos))
		{
			Bit_Let(YSI_g_sGUIBeingUsed, pos);
			return GUI:pos;
		}
	}
	return NO_GUI;
}


/*----------------------------------------------------------------------------*/


stock
	GUI_Delete(GUI: Handle)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		// ---------------------------------------------------------------------

		Bit_Vet(YSI_g_sGUIBeingUsed, _:Handle);

		// ---------------------------------------------------------------------

		return 1;
	}


/*----------------------------------------------------------------------------*/


stock
	GUI_Title_Use(GUI: Handle)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		// ---------------------------------------------------------------------

		Bit_Let(YSI_g_sGUITitleUsing, _:Handle);
		Bit_Vet(YSI_g_sGUITitleBox, _:Handle);

		YSI_g_sGUITitleText[_:Handle][0]  = 0;
		YSI_g_sGUITitlePos[_:Handle][0]   = 0.0;
		YSI_g_sGUITitlePos[_:Handle][1]   = 0.0;
		YSI_g_sGUITitleSize[_:Handle][0]  = 0.0;
		YSI_g_sGUITitleSize[_:Handle][1]  = 0.0;
		YSI_g_sGUITitleColor[_:Handle]    = 0xFFFFFFFF;
		YSI_g_sGUITitleBPos[_:Handle][0]  = 0.0;
		YSI_g_sGUITitleBPos[_:Handle][1]  = 0.0;
		YSI_g_sGUITitleBSize[_:Handle][0] = 0.0;
		YSI_g_sGUITitleBSize[_:Handle][1] = 0.0;
		YSI_g_sGUITitleBColor[_:Handle]   = 0x00000077;

		// ---------------------------------------------------------------------

		return 1;
	}


/*----------------------------------------------------------------------------*/


stock
	GUI_Title_Remove(GUI: Handle)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		// ---------------------------------------------------------------------

		Bit_Vet(YSI_g_sGUITitleUsing, _:Handle);

		// ---------------------------------------------------------------------

		return 1;
	}


/*----------------------------------------------------------------------------*/


stock
	GUI_Title_SetText(GUI: Handle, Text[])
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		// ---------------------------------------------------------------------

		strpack(YSI_g_sGUITitleText[_:Handle], Text, 64);

		// ---------------------------------------------------------------------

		return 1;
	}


stock
	GUI_Title_GetText(GUI: Handle, Text[])
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		// ---------------------------------------------------------------------

		strunpack(Text, YSI_g_sGUITitleText[_:Handle], 64);

		// ---------------------------------------------------------------------

		return 1;
	}


/*----------------------------------------------------------------------------*/


stock
	GUI_Title_SetPos(GUI: Handle, Float: posX, Float: posY)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		// ---------------------------------------------------------------------

		YSI_g_sGUITitlePos[_:Handle][0] = posX;
		YSI_g_sGUITitlePos[_:Handle][1] = posY;

		// ---------------------------------------------------------------------

		return 1;
	}

stock
	GUI_Title_GetPos(GUI: Handle, &Float: posX, &Float: posY)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		// ---------------------------------------------------------------------

		posX = YSI_g_sGUITitlePos[_:Handle][0];
		posY = YSI_g_sGUITitlePos[_:Handle][1];

		// ---------------------------------------------------------------------

		return 1;
	}


/*----------------------------------------------------------------------------*/

stock
	GUI_Title_SetSize(GUI: Handle, Float: sizeX, Float: sizeY)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		// ---------------------------------------------------------------------

		YSI_g_sGUITitleSize[_:Handle][0] = sizeX;
		YSI_g_sGUITitleSize[_:Handle][1] = sizeY;

		// ---------------------------------------------------------------------

		return 1;
	}

stock
	GUI_Title_GetSize(GUI: Handle, &Float: sizeX, &Float: sizeY)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		// ---------------------------------------------------------------------

		sizeX = YSI_g_sGUITitleSize[_:Handle][0];
		sizeY = YSI_g_sGUITitleSize[_:Handle][1];

		// ---------------------------------------------------------------------

		return 1;
	}

/*----------------------------------------------------------------------------*/

#define GUI_Title_SetColour									 GUI_Title_SetColor
stock
	GUI_Title_SetColor(GUI: Handle, Color)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		// ---------------------------------------------------------------------

		YSI_g_sGUITitleColor[_:Handle] = Color;

		// ---------------------------------------------------------------------

		return 1;
	}

#define GUI_Title_GetColour									 GUI_Title_GetColor
stock
	GUI_Title_GetColor(GUI: Handle, &Color)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		// ---------------------------------------------------------------------

		Color = YSI_g_sGUITitleColor[_:Handle];

		// ---------------------------------------------------------------------

		return 1;
	}

/*----------------------------------------------------------------------------*/

stock
	GUI_Title_Box(GUI: Handle, bool: Use)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		// ---------------------------------------------------------------------

		if (Use)
		{
			Bit_Let(YSI_g_sGUITitleBox, _:Handle);
		}
		else
		{
			Bit_Vet(YSI_g_sGUITitleBox, _:Handle);
		}

		// ---------------------------------------------------------------------

		return 1;
	}

/*----------------------------------------------------------------------------*/

stock
	GUI_Title_SetBPos(GUI: Handle, Float: posX, Float: posY)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		if (!Bit_Get(YSI_g_sGUITitleBox, _:Handle))
			return -2;

		// ---------------------------------------------------------------------

		YSI_g_sGUITitleBPos[_:Handle][0] = posX;
		YSI_g_sGUITitleBPos[_:Handle][1] = posY;

		// ---------------------------------------------------------------------

		return 1;
	}

stock
	GUI_Title_GetBPos(GUI: Handle, &Float: posX, &Float: posY)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		if (!Bit_Get(YSI_g_sGUITitleBox, _:Handle))
			return -2;

		// ---------------------------------------------------------------------

		posX = YSI_g_sGUITitleBPos[_:Handle][0];
		posY = YSI_g_sGUITitleBPos[_:Handle][1];

		// ---------------------------------------------------------------------

		return 1;
	}

/*----------------------------------------------------------------------------*/

stock
	GUI_Title_SetBSize(GUI: Handle, Float: sizeX, Float: sizeY)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		if (!Bit_Get(YSI_g_sGUITitleBox, _:Handle))
			return -2;

		// ---------------------------------------------------------------------

		YSI_g_sGUITitleBSize[_:Handle][0] = sizeX;
		YSI_g_sGUITitleBSize[_:Handle][1] = sizeY;

		// ---------------------------------------------------------------------

		return 1;
	}

stock
	GUI_Title_GetBSize(GUI: Handle, &Float: sizeX, &Float: sizeY)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		if (!Bit_Get(YSI_g_sGUITitleBox, _:Handle))
			return -2;

		// ---------------------------------------------------------------------

		sizeX = YSI_g_sGUITitleBSize[_:Handle][0];
		sizeY = YSI_g_sGUITitleBSize[_:Handle][1];

		// ---------------------------------------------------------------------

		return 1;
	}

/*----------------------------------------------------------------------------*/

#define GUI_Title_SetBackgroundColor						GUI_Title_SetBColor
#define GUI_Title_SetBackgroundColour						GUI_Title_SetBColor
#define GUI_Title_SetBColour								GUI_Title_SetBColor
stock
	GUI_Title_SetBColor(GUI: Handle, Color)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		if (!Bit_Get(YSI_g_sGUITitleBox, _:Handle))
			return -2;

		// ---------------------------------------------------------------------

		YSI_g_sGUITitleBColor[_:Handle] = Color;

		// ---------------------------------------------------------------------

		return 1;
	}

#define GUI_Title_GetBackgroundColor						GUI_Title_GetBColor
#define GUI_Title_GetBackgroundColour						GUI_Title_GetBColor
#define GUI_Title_GetBColour								GUI_Title_GetBColor
stock
	GUI_Title_GetBColor(GUI: Handle, &Color)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
			return -1;

		if (!Bit_Get(YSI_g_sGUITitleBox, _:Handle))
			return -2;

		// ---------------------------------------------------------------------

		Color = YSI_g_sGUITitleBColor[_:Handle];

		// ---------------------------------------------------------------------

		return 1;
	}

/*----------------------------------------------------------------------------*/

stock
	GUI_Item_Use(GUI: Handle, ItemID, bool: Use)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		// ---------------------------------------------------------------------

		if (Use)
		{
			Bit_Let(YSI_g_sGUIItemUsing[_:Handle], ItemID);
		}
		else
		{
			Bit_Vet(YSI_g_sGUIItemUsing[_:Handle], ItemID);
		}

		// ---------------------------------------------------------------------

		return 1;
	}

/*----------------------------------------------------------------------------*/

stock
	GUI_Item_SetText(GUI: Handle, ItemID, Text[])
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUIItemUsing[_:Handle], ItemID))
			return -1;

		// ---------------------------------------------------------------------

		strpack(YSI_g_sGUIItemText[_:Handle][ItemID], Text, MAX_GUI_ELEMENTS_LENGTH);

		// ---------------------------------------------------------------------

		return 1;
	}

stock
	GUI_Item_GetText(GUI: Handle, ItemID, Dest[])
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUIItemUsing[_:Handle], ItemID))
			return -1;

		// ---------------------------------------------------------------------

		strunpack(Dest, YSI_g_sGUIItemText, MAX_GUI_ELEMENTS_LENGTH);

		// ---------------------------------------------------------------------

		return 1;
	}

/*----------------------------------------------------------------------------*/

stock
	GUI_Item_SetPos(GUI: Handle, ItemID, Float: posX, Float: posY)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUIItemUsing[_:Handle], ItemID))
			return -1;

		// ---------------------------------------------------------------------

		YSI_g_sGUIItemPos[_:Handle][ItemID][0] = posX;
		YSI_g_sGUIItemPos[_:Handle][ItemID][1] = posY;

		// ---------------------------------------------------------------------

		return 1;
	}

stock
	GUI_Item_GetPos(GUI: Handle, ItemID, &Float: posX, &Float: posY)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUIItemUsing[_:Handle], ItemID))
			return -1;

		// ---------------------------------------------------------------------

		posX = YSI_g_sGUIItemPos[_:Handle][ItemID][0];
		posY = YSI_g_sGUIItemPos[_:Handle][ItemID][1];

		// ---------------------------------------------------------------------

		return 1;
	}

/*----------------------------------------------------------------------------*/

stock
	GUI_Item_SetSize(GUI: Handle, ItemID, Float: sizeX, Float: sizeY)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUIItemUsing[_:Handle], ItemID))
			return -1;

		// ---------------------------------------------------------------------

		YSI_g_sGUIItemSize[_:Handle][ItemID][0] = sizeX;
		YSI_g_sGUIItemSize[_:Handle][ItemID][1] = sizeY;

		// ---------------------------------------------------------------------

		return 1;
	}

stock
	GUI_Item_GetSize(GUI: Handle, ItemID, &Float: sizeX, &Float: sizeY)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUIItemUsing[_:Handle], ItemID))
			return -1;

		// ---------------------------------------------------------------------

		sizeX = YSI_g_sGUIItemSize[_:Handle][ItemID][0];
		sizeY = YSI_g_sGUIItemSize[_:Handle][ItemID][1];

		// ---------------------------------------------------------------------

		return 1;
	}



/*----------------------------------------------------------------------------*/

stock
	GUI_Item_SetBSize(GUI: Handle, ItemID, Float: size)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUIItemUsing[_:Handle], ItemID))
			return -1;

		// ---------------------------------------------------------------------

		YSI_g_sGUIItemBSize[_:Handle][ItemID] = size;

		// ---------------------------------------------------------------------

		return 1;
	}

stock
	GUI_Item_GetBSize(GUI: Handle, ItemID, &Float: size)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUIItemUsing[_:Handle], ItemID))
			return -1;

		// ---------------------------------------------------------------------

		size = YSI_g_sGUIItemBSize[_:Handle][ItemID];

		// ---------------------------------------------------------------------

		return 1;
	}

/*----------------------------------------------------------------------------*/

#define GUI_Item_SetColour									  GUI_Item_SetColor
stock
	GUI_Item_SetColor(GUI: Handle, ItemID, Color)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUIItemUsing[_:Handle], ItemID))
			return -1;

		// ---------------------------------------------------------------------

		YSI_g_sGUIItemColor[_:Handle][ItemID] = Color;

		// ---------------------------------------------------------------------

		return 1;
	}

#define GUI_Item_GetColour									  GUI_Item_GetColor
stock
	GUI_Item_GetColor(GUI: Handle, ItemID, &Color)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUIItemUsing[_:Handle], ItemID))
			return -1;

		// ---------------------------------------------------------------------

		Color = YSI_g_sGUIItemColor[_:Handle][ItemID];

		// ---------------------------------------------------------------------

		return 1;
	}

/*----------------------------------------------------------------------------*/

#define GUI_Item_SetBColor							GUI_Item_SetBackgroundColor
#define GUI_Item_SetBColour							GUI_Item_SetBackgroundColor
#define GUI_Item_SetBackgroundColour				GUI_Item_SetBackgroundColor
stock
	GUI_Item_SetBackgroundColor(GUI: Handle, ItemID, Color)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUIItemUsing[_:Handle], ItemID))
			return -1;

		// ---------------------------------------------------------------------

		YSI_g_sGUIItemBColor[_:Handle][ItemID] = Color;

		// ---------------------------------------------------------------------

		return 1;
	}

#define GUI_Item_GetBColor							GUI_Item_GetBackgroundColor
#define GUI_Item_GetBColour							GUI_Item_GetBackgroundColor
#define GUI_Item_GetBackgroundColour				GUI_Item_GetBackgroundColor
stock
	GUI_Item_GetBackgroundColor(GUI: Handle, ItemID, &Color)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		if (!Bit_Get(YSI_g_sGUIItemUsing[_:Handle], ItemID))
			return -1;

		// ---------------------------------------------------------------------

		Color = YSI_g_sGUIItemBColor[_:Handle][ItemID];

		// ---------------------------------------------------------------------

		return 1;
	}

/*----------------------------------------------------------------------------*/

stock
	GUI_Update(GUI: Handle)
	{
		if (!Bit_Get(YSI_g_sGUIBeingUsed, _:Handle))
			return 0;

		// ---------------------------------------------------------------------

		if (Bit_Get(YSI_g_sGUITitleUsing, _:Handle))
		{
			new
				szString[64];

			strunpack(szString, YSI_g_sGUITitleText[_:Handle]);

			// Creating the textdraw -------------------------------------------
			YSI_g_sGUITextTitle[_:Handle][0] = TextDrawCreate(
													  			YSI_g_sGUITitlePos[_:Handle][0],
																YSI_g_sGUITitlePos[_:Handle][1],
																szString
															  );

			// Text size -------------------------------------------------------
			TextDrawLetterSize(
								 YSI_g_sGUITextTitle[_:Handle][0],
								 YSI_g_sGUITitleSize[_:Handle][0],
								 YSI_g_sGUITitleSize[_:Handle][1]
							   );

			// Text color ------------------------------------------------------
			TextDrawColor(
							YSI_g_sGUITextTitle[_:Handle][0],
							YSI_g_sGUITitleColor[_:Handle]
						  );
		}

		// ---------------------------------------------------------------------

		if (Bit_Get(YSI_g_sGUITitleBox, _:Handle))
		{
			// Creating the box ------------------------------------------------
			YSI_g_sGUITextTitle[_:Handle][1] = TextDrawCreate(
																YSI_g_sGUITitleBPos[_:Handle][0],
																YSI_g_sGUITitleBPos[_:Handle][1],
																"_"
															  );

			// Use box ---------------------------------------------------------
			TextDrawUseBox(
							 YSI_g_sGUITextTitle[_:Handle][1],
							 1
						   );

			// Box size --------------------------------------------------------
			TextDrawTextSize(
							   YSI_g_sGUITextTitle[_:Handle][1],
							   YSI_g_sGUITitleBPos[_:Handle][0] + YSI_g_sGUITitleBSize[_:Handle][0],
							   0.0
							 );

			TextDrawLetterSize(
								 YSI_g_sGUITextTitle[_:Handle][1],
								 1.0,
								 YSI_g_sGUITitleBSize[_:Handle][0] * 0.112957	// MAYBE this value isn't perfect
							   );

			// Box color -------------------------------------------------------
			TextDrawBoxColor(
							   YSI_g_sGUITextTitle[_:Handle][1],
							   YSI_g_sGUITitleBColor[_:Handle]
							 );
		}

		// ---------------------------------------------------------------------

		new
			szString[64];

		for (new Pos; Pos < MAX_GUIS; Pos ++)
		{
			if (Bit_Get(YSI_g_sGUIItemUsing[_:Handle], Pos))
			{
				strunpack(szString, YSI_g_sGUIItemText[_:Handle][Pos]);

				// Create the textdraw -----------------------------------------
				YSI_g_sGUITextButton[_:Handle][Pos] = TextDrawCreate(
																	   YSI_g_sGUIItemPos[_:Handle][Pos][0],
																	   YSI_g_sGUIItemPos[_:Handle][Pos][1],
																	   szString);

				// Alignment ---------------------------------------------------
				TextDrawAlignment(
									YSI_g_sGUITextButton[_:Handle][Pos],
									2
								  );

				// Size --------------------------------------------------------
				TextDrawLetterSize(
									 YSI_g_sGUITextButton[_:Handle][Pos],
									 YSI_g_sGUIItemSize[_:Handle][Pos][0],
									 YSI_g_sGUIItemSize[_:Handle][Pos][1]
								   );

				// Color -------------------------------------------------------
				TextDrawColor(
								YSI_g_sGUITextButton[_:Handle][Pos],
								YSI_g_sGUIItemColor[_:Handle][Pos]
							  );

				// Use box -----------------------------------------------------
				TextDrawUseBox(
								 YSI_g_sGUITextButton[_:Handle][Pos],
								 1
							   );

				// Box size ----------------------------------------------------
				TextDrawTextSize(
								   YSI_g_sGUITextButton[_:Handle][Pos],
								   0.0,
								   YSI_g_sGUIItemBSize[_:Handle][Pos]
								 );

				// Box color ---------------------------------------------------
				TextDrawBoxColor(
								   YSI_g_sGUITextButton[_:Handle][Pos],
								   YSI_g_sGUIItemBColor[_:Handle][Pos]
								 );
			}
		}

		// ---------------------------------------------------------------------

		return 1;
	}

/*-----------------------------------------*/