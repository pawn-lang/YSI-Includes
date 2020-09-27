#### Bitmap_DrawRectangle
>* **Parameters:**
>	* `Bitmap:ctx`: Bitmap:ctx_INFO
>	* `const minX`: const minX_INFO
>	* `const minY`: const minY_INFO
>	* `const maxX`: const maxX_INFO
>	* `const maxY`: const maxY_INFO
>	* `fillColour`: fillColour_INFO
>	* `lineColour = 0`: lineColour = 0_INFO
>	* `linePattern[] = \`: linePattern[] = \_INFO
>	* `fillPattern[] = \`: fillPattern[] = \_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This function draws a rectangle between two given co-ordinates.  It can also
>	draw a border around the rectangle OUTSIDE the specified area of the
>	rectangle.  If you want the border within the area specified you need to use
>	a smaller area.
 
***

#### Bitmap_DrawRectangle
>* **Parameters:**
>	* `Bitmap:ctx`: Bitmap:ctx_INFO
>	* `const x`: const x_INFO
>	* `const y`: const y_INFO
>	* `const Float:radius`: const Float:radius_INFO
>	* `fillColour`: fillColour_INFO
>	* `lineColour = 0`: lineColour = 0_INFO
>	* `linePattern[] = \`: linePattern[] = \_INFO
>	* `fillPattern[] = \`: fillPattern[] = \_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This function draws a circle centered on the given co-ordinates with the
>	given FLOAT radius, not an integer size because of diagonals. It can also
>	draw a border around the circle OUTSIDE the specified area of the circle.
>	If you want the border within the area specified you need to use a smaller
>	area.
 
***

#### Bitmap_DrawRectangle
>* **Parameters:**
>	* `Bitmap:ctx`: Bitmap:ctx_INFO
>	* `x`: x_INFO
>	* `y`: y_INFO
>	* `const Float:inner`: const Float:inner_INFO
>	* `const Float:outer`: const Float:outer_INFO
>	* `colour`: colour_INFO
>	* `pattern[] = \`: pattern[] = \_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	This function draws a ring centered on the given co-ordinates with the
>	given FLOAT radius, not an integer size because of diagonals.  This does not
>	draw a border as it is used for borders, and a border on a ring is ambiguous
>	- do you have it on the inside or not?  Better to let the user decide.
 
***

