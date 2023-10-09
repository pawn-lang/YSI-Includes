# Quick Start

## Introduction

y_text is the single most complex library in YSI 3.0, but using it is (hopefully) very simple. The library works on the idea from HTML/CSS/JavaScript of separation of content, style and logic. Most modes contain code like this:
```
SendClientMessage(playerid, COLOUR_RED, "Hello there");
```
That's all well and good, and VERY common. But if you have a typo you need to recompile your mode, if you want to change the colour you need to recompile your mode, and changing how the text displays (for example converting to text draws) is a lot more work. y_text on the other hand has just one display method:
```
Text_Send(playerid, $HELLO_MESSAGE);
```
The "HELLO_MESSAGE" text is defined in files, along with the style of the text, and can come in multiple languages, making this more equivalent to:
```
switch (PlayerLanguage(playerid))
{
    case ENGLISH:
        SendClientMessage(playerid, COLOUR_RED, "Hello there");
    case FRANCAISES:
        SendClientMessage(playerid, COLOUR_RED, "Bonjour il");
    // Etc..
}
```
By default y_languages supports five languages at once, but this can be increased VERY easilly.

## Text
There are three parts to displaying text: Creating the files, loading them, and displaying the text. Fortunately these are all quite simple.

### Defining
Let's say you decide you want two languages: English and Dutch (Nederlands)*. You first create two files, I'm going to name them "mode_text.EN" and "mode_text.NL" (the names aren't important, they just need to be consistent), and put them in "scriptfiles/YSI/text":
```
mode_text.EN:

[all]
HELLO_MESSAGE = Hello there
BYE_MESSAGE = Goodbye
mode_text.NL

[all]
HELLO_MESSAGE = Hello there
BYE_MESSAGE = Afscheid
```
These are both INI files with standard "KEY = Value" pairs. They also MUST contain sections (here "[all]" is a section), but the simplest way is to just have one.

You also need a third file called "mode_text_LANG_DATA.yml" in "scriptfiles/YSI", but I'll come to that later.

Note: I don't actually know Dutch, so these examples may be awful (Google translated).

### Loading
There are two stages to loading a text file, both shown in the code below:
```
loadtext mode_text[section1], mode_text[section2], other_text[what], other_text[where];
```
The "Langs_Add" line tells the language system which languages to load and gives the name of that language in that language (hence "Dutch" is "Nederlands"). It also defines the two letter short code for that language, which is used to select the exact file to load. "English" is defined as "EN" and the file is "mode_text.EN", simillarly "Dutch" is defined as "NL" and the file is "mode_text.NL". Note that this is the ONLY function in YSI that will give a warning if it is not used because YSI needs to know what languages to load for internal text (even if you don't use the system yourself).

### Displaying
This is possibly the simplest part:
```
Text_Send(playerid, $HELLO_MESSAGE);
```

"Text_Send" is a VERY clever function:

The first paramter ("playerid" above) can be one of a number of things: A single playerid, an array of players, a YSI player array, an array of IDs, "ALL_PLAYERS", "ALL_BOTS", "ALL_CHARACTERS", or a YSI group.
The second parameter is an identifier from a file (here "$HELLO_MESSAGE"). Note that the section with this message in MUST be loaded for the current file:
Good:
```
loadtext mode_text[all];

public OnPlayerConnect(playerid)
{
    Text_Send(playerid, $HELLO_MESSAGE);
}
```
Bad:
```
//loadtext mode_text[all];

public OnPlayerConnect(playerid)
{
    Text_Send(playerid, $HELLO_MESSAGE);
}
This may mean that you load a section in multiple files, but the system will only actually load it once, this is just to speed up lookups.

"Text_Send" also takes EXTENDED format parameters (all the existing ones and then some):
[my_section]
SOME_NUMBER = Your number is %d
loadtext my_file[my_section];

stock Func(playerid, num)
{
    Text_Send(playerid, $SOME_NUMBER, num);
}
```
## Targets
As mentioned, text can be sent to any number of people, meaning you no longer need "Text_SendToPlayer", "Text_SendToGroup", "Text_SendToAdmins", "Text_SendToAll" etc. The first three methods are designed to mimic existing code methods and make for simple integration in to existing modes. When you send a message to mutliple people using one of the methods below every player will get the message in their own language. These calls are also optimised for many people and multiple languages so are better than simply calling "Text_Send" in a loop (there is text buffering to re-use calculated output instead of re-running processing).

### Boolean Arrays
```
new
    bool:gIsAdmin[MAX_PLAYERS];

// Notice that this is only on one line, unlike the declaration above!  This is
// another system restriction but shouldn't be too bad.
loadtext some_file[some_section];

stock Func()
{
    Text_Send(@ gIsAdmin, $SOME_MESSAGE);
}
```
The above code will send the message "$SOME_MESSAGE" to everyone for whom "gIsAdmin" is TRUE (you can't do it for everyone who is FALSE). Note that "gIsAdmin" is not a YSI array (just a nomal array) so you need "@" on the front to convert it (another restriction I've tried to make as low-impact as possible).

### Player Lists
```
new
    gAdmins[MAX_PLAYERS] = {0, 42, 45, INVALID_PLAYER_ID, 27, ...};

// Notice that this is only on one line, unlike the declaration above!  This is
// another system restriction but shouldn't be too bad.
loadtext some_file[some_section];

stock Func()
{
    Text_Send(@ gAdmins, $SOME_MESSAGE);
}
```
This code is very similar to the previous code, but instead of an array of true/false, this is a list of player IDs, with "INVALID_PLAYER_ID" (or the end of the array) denoting the end of the list. The code above will send the message to players 0, 42 and 45. 27 WILL NOT get a message as their ID appears AFTER "INVALID_PLAYER_ID", denoting the end of the list.

### Custom Arrays
The first two methods are common, but possibly the more common method of storing data on players is through an enum array:
```
enum E_PLAYER_DATA
{
    E_PLAYER_DATA_SOMETHING,
    E_PLAYER_DATA_OTHER,
    bool:E_PLAYER_DATA_ADMIN
}

new
    gPlayerData[MAX_PLAYERS][E_PLAYER_DATA];


// Often you will want to send a message to everyone for whom "E_PLAYER_DATA_ADMIN" is true. This is (in "y_text" speak) a "custom" array:

stock Func()
{
    Text_Send(@ gPlayerData<E_PLAYER_DATA_ADMIN>, $SOME_MESSAGE);
}
```
This specifies that "gPlayerData" is a 2d enum array and only the "E_PLAYER_DATA_ADMIN" slot should be used. It should be noted that this line MAY give a warning about index tag mismatches, I don't know how to avoid this so just ignore it.

### Groups
YSI has a system called "y_groups". This is an abstraction from any system which collects people together for some reason (admin levels, factions, teams, jailed players etc) - it is designed to handle them all and can allow for people to be in multiple groups at once (admins can also be in factions etc). Groups are apart of YSI so are handled natively - i.e. they don't need converting with "@":
```
new
    Group:gAdmins;

public OnGameModeInit()
{
    gAdmins = Group_Create("Admins");
}

stock Func()
{
    // No "@" in front of the variable.
    Text_Send(gAdmins, $SOME_MESSAGE);
}
```
The code above will, unsurprisingly, send the message to everyone in the "gAdmins" group. Groups in general have been documented before in another tutorial so will not be covered further here.

### Player Arrays
This is the last of the array style calls. Many people know that boolean arrays such as in the first example are very inefficient, being 32x larger than they need to. YSI (and, many years later, other systems) instead use binary arrays to pack this data down - "y_playerarray" is one of these systems (based on "y_bit"), specially designed for players and y_text.
```
new
    PlayerArray:gAdmins<MAX_PLAYERS> = {PA_INIT:false, ...};

stock Func()
{
    // No "@" in front of the array.
    Text_Send(gAdmins, $SOME_MESSAGE);
}
```
This behaves exactly like the first target, but with less memory and slightly more efficiently.

### Single Players
You can of course just pass a single player to "Text_Send":

```
Text_Send(playerid, $SOME_MESSAGE);
```

### `y_playerset`
All the above player passing examples are not actually part of "y_text" specifically, but another library called "y_playerset". Any custom function can be written to take all these input options:
```
#define MyFunc(%0) PSF:_MyFunc(%0)
stock _MyFunc(@PlayerArray:players<MAX_PLAYERS>)
{
    // "players" is now a YSI "PlayerArray" of all the players passed at once.
    foreach (new playerid : PA(players))
    {
        // Uses "PA".
    }
}
#define MyFunc(%0) PSF:_MyFunc(%0)
stock _MyFunc(@PlayerVar:player)
{
    // This function will be called multiple times automatically, once for every
    // player passed in any array.
}
#define MyFunc(%0) PSF:_MyFunc(%0)
stock _MyFunc(@PlayerSet:players)
{
    // "players" is now a special compact representation of all the players
    // passed and can be used in iterators.  This is different to using
    // "@PlayerArray" as it's just a single variable, not all players at once.
    foreach (new playerid : PS(players))
    {
        // Uses "PS".
    }
}
```
## Styles
Obviously "Text_Send" has no included information as to HOW the text should be displayed - using "SendClientMessage", "GameText", "TextDraw" or anything else. This is all set in the "LANG_DATA" file:

### Example
```
scriptfiles/YSI/text/mode_text.EN

[all]
HELLO_MESSAGE = Hello there
BYE_MESSAGE = Goodbye
scriptfiles/YSI/text/mode_text.NL

[all]
HELLO_MESSAGE = Hello there
BYE_MESSAGE = Afscheid
scriptfiles/YSI/mode_text_LANG_DATA.yml

<YML>
	<group name="all">
		<entry name="HELLO_MESSAGE" style="client" colour="X11_RED" />
		<entry name="BYE_MESSAGE" style="3" time="4000" />
	</group>
</YML>
```
### XML
This is an XML file holding the style information for all text entries in the given file (here "mode_text_LANG_DATA.yml" holds the information for "mode_text". These elements are grouped together and each entry has a separate line.

#### style
"style" can be any of the following:

- client - Use "SendClientMessage".
- 0 - 6 - Use "GameText" styles 0 - 6.
- draw - Use "TextDraw".
- 3d - Use 3d text (not fully supported yet).
- player - Use "SendPlayerMessage".

The other options depend on the selected style

#### Style "client"
colour - AKA "color". The colour you want this text to start as. There are thousands of colours built in to the system that can be used by name, or you can specify a new colour and name it yourself for later use:
```
<YML>
	<group name="all">
		<entry name="HELLO_MESSAGE" style="client">
			<colour name="My_Green" hex="00FE00" />
		</entry>
	</group>
</YML>
```

Or just specify a new colour for a one-off use:

Code:
```
<YML>
	<group name="all">
		<entry name="HELLO_MESSAGE" style="client" colour="00FE00" />
	</group>
</YML>
```
#### Styles 0, 1, 2, 3, 4, 5, 6
The selected style determines which sort of "GameText" you would like to use to display the data.

time - The time to display this text for in milliseconds. Note that this may be ignored by certain game text styles.
colour - This is the same as the "colour" option for "client" and the system will match the specified colour as closely as possible for the start of the game text.

#### Stlye "draw"
textdraw - This specifies a textdraw style by name from the "y_td" library. This will be better documented later, but as with "colour" it can use an existing one or define a new one inline:
```
<YML>
	<group name="all">
		<entry name="HELLO_MESSAGE" style="draw">
			<textdraw box="YELLOW" background="0" color="green" y="134" x="132"
			  texty="0" textx="637" alignment="1" outline="1" proportional="1"
			  shadow="0" lettery="1" letterx="1" name="YSI_0003" time="10000">
			</textdraw>
		</entry>
	</group>
</YML>
```
Note that "y_td" adds a "time" parameter. There is also a script available on request to convert from the text draw editor file format to this format.

#### Style "3d" And Style "player"
These are not yet fully supported.

## Format
"Text_Send" can take format parameters, and it has been extended with a greater number than the default "format" function.

### Specifiers
- b - Boolean. This now works for negative numbers.
- c - Character.
- d, i - Integer (Decimal).
- f - Float.
- g - IEEE float (has "NAN" and "INFINITY").
- h, x - Hex (heX). This now works for negative numbers.
- l - Logical ("true" or "false"). Any number not 0 will be displayed as "true", 0 will be "false".
- n - commaNd. This was chosen as "%n" as it was the first new one added and at the time "%n" caused a crash in "format" (and "%c" was taken). In YSI commands can be renamed and different people can have different names for the same command. Using this will always give the correct name for the current player. The commands are specified using their "YCMD" syntax:
```
[comms]
COMM_MESSAGE = Command /%n
loadtext file[comms];

stock Func(playerid)
{
    // Show the player what "YCMD:hi" is called for them.
    Text_Send(playerid, $COMM_MESSAGE, YCMD:hi);
}
```
q - player ("q" is near "p", and "p" is unavailable for historical reasons). Show a player's name (I was sick of writing "GetPlayerName"):
```
[player]
PLAYER_MESSAGE = Player %d is %q
loadtext file[player];

stock Func(playerid)
{
    // Show the player their ID and what they are called.
    Text_Send(playerid, $PLAYER_MESSAGE, playerid, playerid);
}
```
s - String.
There are a few more from the old version of YSI that are not yet ported (including "p", "t" and "u").

### Modifiers
The default format can have specifiers like "%02s" to pad or restrict output length. YSI fully supports all these modifiers and adds two more experimental ones:

! - Defines a list of elements:
```
[list]
INTS_MESSAGE = List %!d
loadtext file[list];

stock Func(playerid)
{
    // Show the player a list of numbers.
    new
        arr[4] = {5, 6, 7, 8};
    Text_Send(playerid, $INTS_MESSAGE, arr, sizeof (arr));
}
[/list]
```
This will give an output of:

List 5, 6, 7, 8
? - Get the data from a function. This is a work in progress, but will display data similar to "!".

## Colours

### X11

As mentioned already, YSI (through "y_colours", aka "y_colors") has several thousand colours in-built and ready to use by name or define. Most of these colours can be seen here:

[1]

The full list is here, but without the actual colour shown, just the RGB:

[2]

Note that YSI also supports British spellings (i.e. "grey" as well as "gray" (the list misses "SlateGrey1" for example), and "colour" as well as "color").

These are known as the "X11" colours (being based on those found in the "X11" windowing system). They are available for use in a range of manners through YSI:
```
[some_text]
MESSAGE1 = Hi {X11_ALICE_BLUE}there ; With "X11" and underscores.
MESSAGE2 = Hi {X11 ALICE BLUE}there ; With "X11" and spaces.
MESSAGE3 = Hi {X11ALICEBLUE}there   ; With "X11".
MESSAGE4 = Hi {x11_aLiCe BlUe}there ; Space and case mixture.
MESSAGE5 = Hi {ALICE BLUE}there     ; Space only.
MESSAGE6 = Hi {ALICE_BLUE}there     ; Underscore only.
MESSAGE7 = Hi {ALICEBLUE}there      ; Nothing.
MESSAGE8 = Hi #ALICEBLUEthere       ; Alternate style.
// This is stand alone from y_text.
#include <YSI\y_colours>

#define COlOUR_ERROR_1 X11_SLATE_GREY
#define COlOUR_ERROR_2 X11_SLATEGREY
#define COlOUR_ERROR_3 X11_SLATE_GRAY
#define COlOUR_ERROR_4 X11_SLATEGRAY
```
When using the defines the colours MUST be prefixed with "X11_" and be upper-case, but the underscore is optional. When using the colour names in text directly (with "{}" or "#") there are more options. The "X11" prefix is optional and you can have spaces (though this can be disabled with "SetColoursCanHaveSpaces(boolet);"). The system is also clever enough to not need spaces after the colour name when using "#". Note however that it is not VERY clever:

[some_text]
AMBIGUOUS = #GOLDenter
You may want that code to show the word "enter" in the colour "GOLD"; however, it will display the word "ter" in the colour "GOLDEN". The match is "greedy" and will get the longest colour it can. This is easilly avoided:
```
[some_text]
OBVIOUS = {GOLD}enter
```

### Custom Colours

You can add your own colours to the system:
```
SetColour("WARNING", 0xFE0101AA); // AKA "SetColor".
```
You can also get colours (including the X11 colours) by name:
```
new colour = GetColour("WARNING"); // AKA "GetColor".
```
Once added you can use them in text (assuming they are added BEFORE the text files are loaded at the end of "OnGameModeInit" or "OnFilterScriptInit"):
```
[some_text]
CUSTOM = {WARNING}Warning!
loadtext file[some_text];

public OnGameModeInit()
{
    Langs_Add("EN", "English");
    SetColour("WARNING", 0xFE0101AA); // AKA "SetColor".
    return 1;
    // Files are loaded after this.
}
```
### Close
[FeK]DraKiNs introduced the idea of closing colours in this topic:

[3]

I have adopted this idea here too:
```
[some_text]
THREE = One{RED} Two{/} Three
"One" and "Three" here will be the same colour (or as close as possible when using "GameText" or "TextDraw"):

<YML>
	<group name="some_text">
		<entry name="THREE" style="client" color="GREEN" />
	</group>
</YML>
```
Using that style file the start colour will be "GREEN" and thus both parts will be green, without knowning in advance what colour will be selected in the style file.

### Fades
This was one of the hardest parts of "y_text" to write. Text can fade gradually from one colour to another:
```
[some_text]
FADE_TO_BLACK = {>GREEN}Fade To Black{<BLACK}
FADE_PARTIALLY = {>GREEN}Fade {</}Somewhere
```
These will give outputs that fade gently from one colour to another. This may significanlty reduce the length of string that can be shown as all those colour codes will take up a lot of space, but the default is to change colour every other character, not every character, and "y_text" can smoothly continue on the next line if it needs to. You cannot use fades with "#", and starting a new fade will instantly end the old one (">" to start and "<" to end).

## Languages

A player's language is set using "Langs_SetPlayerLanguage(playerid, Language:l);" The language ID ("Language:l") is returned by "Language:Langs_AddLanguage(string:code[], string:name[]);":
```
new
    Language:gLEnglish;

public OnGameModeInit()
{
    gLEnglish = Langs_Add("EN", "English"); // AKA "Langs_AddLanguage".
    return 1;
}

public OnPlayerConnect(playerid)
{
    Langs_SetPlayerLanguage(playerid, gLEnglish);
}
```
Everyone defaults to language 0 - always the first added language. "y_extra" includes a "YCMD:language" command to allow players to select their own language by first listing all available languages and then letting them select one from the list.

Other functions:

Language:Langs_GetPlayerLanguage(playerid); - Get a player's current language.
string:Langs_GetCode(Language:l); - Get the 2 letter code for the given language.
string:Langs_GetName(Language:l); - Get the full name for the given language.
Language:Langs_GetLanguageCount(); - Get the number of languages in the system.
string:Langs_GetLanguageCodes(); - Get all the short codes sparated by "|".
Language:Langs_GetLanguage(string:identifier[]); - Get the language ID from a string identifier (either 2 letter short code or full name).
Langs_RemoveLanguage(Language:l); - Remove the given language. Can not currently be called while anyone is still using the language.
The only important function is "Langs_AddLanguage", which is why YSI will give a warning if it is not used. Currently this function can ONLY be used in the script's "Init" function - either "OnGameModeInit" or "OnFilterScriptInit". "main" will not do and you will get an error in the server if it is not in the correct place.

## Advanced

### Long Lines

y_ini (on which the text files are based) has a default line length limit of 128*, clearly insufficient for certain text displays that can have 1024 characters. For this reason you can "group" text entries together using special naming syntax:
```
mode_text.EN

[section]
LONG_TEXT_1 = This is part of a long line of text.  
LONG_TEXT_2 = The text is linked by the "_1" and "_2" suffixes.
LONG_TEXT3 = This is NOT part of the long text.
```
Using a naming scheme of "IDENTIFIER_1", "IDENTIFIER_2", "IDENTIFIER_27" etc will tell the system that these items are all together as "IDENTIFIER". To format and display these items you only need the base name:
```
mode_text_LANG_DATA.yml

<YML>
	<group name="section">
		<entry name="LONG_TEXT" style="client" colour="X11_RED" />
	</group>
</YML>
Text_Send(playerid, $LONG_TEXT);
```
That will display the string "This is part of a long line of text.The text is linked by the "_1" and "_2" suffixes." to a player. There is no space between the lines because y_ini trims trailing spaces, they also appear on the same line because it's a better default. Both these behaviours can be overridden (see next section). The text "LONG_TEXT3" is NOT part of the long text because it is incorrectly named, the correct version would be "LONG_TEXT_3". Also note that the number order must relate to the text order, but need not be consecutive, the following is acceptable and will give the same output:
```
mode_text.EN

[section]
LONG_TEXT_42 = The text is linked by the "_1" and "_2" suffixes.
LONG_TEXT_27 = This is part of a long line of text.
```

Note: * I have plans to remove this limit and in the process speed up the system, but that's another issue entirely.

### Codes
I've tried to support as many escape codes as possible when loading files (including "\v", don't ask me why), and some new ones. In the old version of this code these escapes were printed literally, now they are parsed:

\n - Create a new line. For "ClientMessage" this will end the current line and start a new one, for "TextDraw" and "GameText" this will be translated in to "~n~". Note that in MOST circumstances colour fades can span new lines (I know that doesn't sound impressive, but it was HORRIBLE to code (took months)).
\s - Add a space. In the above examples the two lines are joined right next to each other as extra leading and trailing spaces are stripped out. This escape code is used to bypass that behaviour.
\t - Add a tab, and not just a tab character. This will actually work out the correct spacings and add relevant spaces in most cases (essentially this replicates the bahaviour of the tab character, as the real one is not supported in SA:MP text).
\% - Does the same as "%%" (displays a percent sign instead of starting a format code).
\\ - Displays a back slash.
\" - Shows a double quote. Not actually needed as an unescaped double quote will also work when reading from files.
\' - Single quote, see above.
\x<HEX>; - Insert the character with the given HEX code (0 - 9, A - F).
\<DEC>; - Insert the character with the given DECIMAL code (0 - 9).

### GameText Formats

You should know that in SA:MP "ClientMessage" uses "{RRGGBB}" for colours and "GameText" uses "~X~" instead. When using "y_text" these two versions (and a third "#COLOUR", introduced by RyDeR) are entirely interchangable and will be translated (and estimated where applicable) to the correct version at display time:
```
MULTI_TEXT = ~r~Red, {00FF00}Green, #BLUEBlue.
```
When using "ClientMessage", the "~r~" will be translated to the EXACT colour used by "GameText", not just any red (I spent ages recoding every used colour combination). When using "GameText" the "{00FF00}" and "#BLUE" will be translated to the nearest available "GameText" colour (also applies to "TextDraw").

Note also that the rendering is as smart as possible. For one thing the default "GameText" colour is not available through any "~X~" code, but the system will use it when it can. The system will also use the previous colour, so the following is a possible output:
```
~r~Some ~h~Colours
```
"Some" will be red and "~h~" will be lighter red - you don't need to do "~r~~h~" to get the lighter red when the previous colour was already red, thus saving space.

### Wrapping

If an output is too long to fit on one line "y_text" will attempt to show the output on multiple lines (e.g. in "ClientMessage"). In some cases this is not applicable and in others (e.g. "TextDraw") it is not yet supported (as calculating the location of the next line relies on character size knowledge the system doesn't yet have).

