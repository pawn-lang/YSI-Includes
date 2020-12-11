# Do Not Use The `YSI` Directory

I long ago deprecated this directory in favour of smaller, more specific groupings of includes.  I tried to write error messages that told you this.  Every time you included `<YSI\y_timers>` you got an error saying:

	Use `#include <YSI_Coding\y_timers>`

I thought this was very clear.  You were including `<YSI\y_timers>`, the error said to include `<YSI_Coding\y_timers>` instead.  Sadly, many people just don't read at all.  I STILL can't teach these people how to read very very short simple messages, but I can try...

