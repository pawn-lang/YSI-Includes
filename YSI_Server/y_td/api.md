#### TD_IsValidStyle
>* **Parameters:**
>	* `Style:id`: Style:id_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_TD
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	Constructor.
 
***

#### TD_Parse
>* **Parameters:**
>	* `filename[]`: filename[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_LoadColour
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	XML callback for loading the <colour> tag.
 
***

#### TD_Create
>* **Parameters:**
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `Float:letterX`: Float:letterX_INFO
>	* `Float:letterY`: Float:letterY_INFO
>	* `Float:textX`: Float:textX_INFO
>	* `Float:textY`: Float:textY_INFO
>	* `colour`: colour_INFO
>	* `boxColour`: boxColour_INFO
>	* `bgColour`: bgColour_INFO
>	* `shadow`: shadow_INFO
>* **Returns:**

>* **Remarks:**
>	Creates a text draw style structure according to given
>	parameters, can be used to display any text in the given
>	style without repeated redefinitions.
 
***

#### TD_Textdraw
>* **Parameters:**

>* **Returns:**
>	* -
>* **Remarks:**
>	XML callback for loading the <textdraw> tag.
 
***

#### TD_Get
>* **Parameters:**
>	* `name[]`: name[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_GetID
>* **Parameters:**
>	* `hash`: hash_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_Create
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `name[]`: name[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Copies a text draw style and returns the new handle.
 
***

#### TD_GetStyleData
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `data[E_TD_DATA]`: data[E_TD_DATA]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_Name
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `name[]`: name[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_TextPosition
>* **Parameters:**
>	* `Text:textID`: Text:textID_INFO
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Moves a single bit of text, not all with a style.
 
***

#### TD_TextXPos
>* **Parameters:**
>	* `Text:textID`: Text:textID_INFO
>	* `Float:x`: Float:x_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Moves a single bit of text, not all with a style.
 
***

#### TD_TextYPos
>* **Parameters:**
>	* `Text:textID`: Text:textID_INFO
>	* `Float:y`: Float:y_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Moves a single bit of text, not all with a style.
 
***

#### TD_StylePosition
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Update is default false to not modify moved texts.
 
***

#### TD_StyleXPos
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `Float:x`: Float:x_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Update is default false to not modify moved texts.
 
***

#### TD_StyleYPos
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `Float:y`: Float:y_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Update is default false to not modify moved texts.
 
***

#### TD_LetterSize
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_LetterX
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `Float:x`: Float:x_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_LetterY
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `Float:y`: Float:y_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_TextSize
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `Float:x`: Float:x_INFO
>	* `Float:y`: Float:y_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_TextX
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `Float:x`: Float:x_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_TextY
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `Float:y`: Float:y_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_Alignment
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `alignment`: alignment_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Designed to take ta_align enum values and numbers.
 
***

#### TD_Colour
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `colour`: colour_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_UseBox
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `bool:use`: bool:use_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_BoxColour
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `colour`: colour_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_SetShadow
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `size`: size_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_SetOutline
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `size`: size_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_BackgroundColour
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `colour`: colour_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_Font
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `font`: font_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_SetProportional
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `bool:set`: bool:set_INFO
>	* `bool:update`: bool:update_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_SetTime
>* **Parameters:**
>	* `Style:styleID`: Style:styleID_INFO
>	* `time`: time_INFO
>	* `existing`: existing_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Doesn't update existing timed texts, just new ones.  Now does all of them.
 
***

#### TD_RenderInternal
>* **Parameters:**
>	* `text[]`: text[]_INFO
>	* `Style:id`: Style:id_INFO
>	* `Text:slot`: Text:slot_INFO
>* **Returns:**
>	* TextDraw id.
>* **Remarks:**
>	Basically the application layer, creates a text_draw with the
>	saved data.
 
***

#### TD_Render
>* **Parameters:**
>	* `text[]`: text[]_INFO
>	* `Style:id`: Style:id_INFO
>	* `Text:slot`: Text:slot_INFO
>* **Returns:**
>	* TextDraw id.
>* **Remarks:**
>	Basically the application layer, creates a text_draw with the
>	saved data.
 
***

#### TD_Update
>* **Parameters:**
>	* `Style:id`: Style:id_INFO
>	* `bool:pos`: bool:pos_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Loops through all texts displayed using the current render style and updates
>	their real display.
 
***

#### TD_UpdateOne
>* **Parameters:**
>	* `Text:slot`: Text:slot_INFO
>	* `Style:id`: Style:id_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Updates a single text's appearance.  Modified to use a timer with a delay of
>	1ms, to be called after the current slew of updates.  This means that doing
>	a whole load of modifications at once will all be committed to players at
>	the same time.  This used to be done with the optional "update" parameter.
 
***

#### TD_Delete
>* **Parameters:**
>	* `styleId`: styleId_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Just nulls the name to remove it's active marker.
 
***

#### TD_TryDestroy
>* **Parameters:**
>	* `Text:textDraw`: Text:textDraw_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Destroys this text draw only if it is marked for garbage collection.  It
>	does not however check that no-one can see the text draw, so those people
>	who can currently see it will loose it.
 
***

#### TD_Destroy
>* **Parameters:**
>	* `Text:textDraw`: Text:textDraw_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Optimised for multiple people.  Not very well though...
 
***

#### TD_Link
>* **Parameters:**

>* **Returns:**

>* **Remarks:**
>	Links two TDs so that manipulating one does the other too.  They are already
>	linked through their style, but that's only for style updates.  This handles
>	things like screen position updates etc.
 
***

#### TD_Display
>* **Parameters:**
>	* `text[]`: text[]_INFO
>	* `Style:id`: Style:id_INFO
>* **Returns:**
>	* Internal Text: id, not actual text draw's id.
>* **Remarks:**
>	Generates a text draw for to display to people.
 
***

#### TD_SetString
>* **Parameters:**
>	* `Text:td`: Text:td_INFO
>	* `text[]`: text[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Changes the text on people's screens quickly.
>	This function DOES NOT update linked TDs as the point is that they display
>	the same data in different ways, so will need to be updated in different
>	ways.
 
***

#### TD_DisplayHashed
>* **Parameters:**
>	* `text[]`: text[]_INFO
>	* `hash`: hash_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_DisplayNamed
>* **Parameters:**
>	* `text[]`: text[]_INFO
>	* `style[]`: style[]_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_ShowForPlayer
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `Text:textDraw`: Text:textDraw_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Now destroys any existing text draws using the same style in
>	the same place to avoid overlaps.
 
***

#### TD_HideForPlayer
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `Text:textDraw`: Text:textDraw_INFO
>	* `revision`: revision_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Public so the timer can call it to hide texts with a time set.
 
***

#### TD_ShowForAll
>* **Parameters:**
>	* `Text:textDraw`: Text:textDraw_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	-
 
***

#### TD_HideForAll
>* **Parameters:**
>	* `Text:textDraw`: Text:textDraw_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Destroys the real text draw if marked for garbage collection.
>	Hides all linked TDs.
 
***

#### TD_OnPlayerDisconnect
>* **Parameters:**
>	* `playerid`: playerid_INFO
>	* `reason`: reason_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Required to fix bugs in the textdraw system by hiding all
>	visible ones.
 
***

#### TD_Garbage
>* **Parameters:**
>	* `Text:textDraw`: Text:textDraw_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Tells the system to remove a text draw when no-one can see it
>	anymore to free up text draw slots.
>	Note that linked TDs don't share garbage status.  This is because I said so,
>	not for any good reason (other that I can't be bothered to code it up).
>	Ergo this behaviour is a feature, not a bug!
 
***

#### TD_Morph
>* **Parameters:**
>	* `Text:textDraw`: Text:textDraw_INFO
>	* `Style:style`: Style:style_INFO
>	* `time`: time_INFO
>	* `defer`: defer_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Entry point for changing the apperance of a text draw to look like another
>	one.  How smooth this is depends on the difference and the time given.  The
>	default update time is 50ms (20fps), which isn't too bad.  Don't modify
>	revision versions in here as if there is a hide timer, it still applies
>	regardless of what style is currently applied.
>	No longer takes a playerid parameter - it's just tough but easy to work
>	around using y_text.
 
***

