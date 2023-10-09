# Quick Start
y_colours contains definitions for hundreds of different colours, specifically San Andreas colours from "GameText" and the X11 set of standard colours. It also includes code for parsing colour names from text and defining and retrieving custom colours. This is a component of y_text, but does not include it.

For test builds, the following define will vastly increase compile times by ommiting the X11 colours, which consist of three very large files (internal\y_x11def, internal\y_x11parse, internal\y_x11switch), though the speed improvement is less pronounced than it used to be thanks to work by Slice removing the compile-time string hashing. Remember that it is best to remove this line before a final deployment build to regain the advantage of the wider array of colours. This should go above the library include:
```pawn
#define YSI_NO_X11
#include <YSI\y_colours>
```
The full set of colours included by default are shown in the attached image.

<img height="500" align="center" src="https://static.wikia.nocookie.net/ysi/images/6/65/Y_colours.png/revision/latest/scale-to-width-down/1000?cb=20130205002244">
