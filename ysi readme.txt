Alex "Y_Less" Cole's Server/Script Includes V0.1

0) Contents

	0 - Contents
	1 - About
		0 - General
		1 - History
		2 - Readme
			0 - Contents
			1 - About
			2 - Files
			3 - Installation
			4 - Use
			5 - Required Functions
			6 - Useable Functions
			7 - Internal Functions
			8 - Options
			9 - Technical Information
			10 - Changelog
			11 - Future
			12 - Legal
			13 - Credits
		3 - Conventions
	2 - Files
		0 - pawno/
			0 - new.pwn
		1 - pawno/include/
			0 - YSI.inc
		2 - pawno/include/YSI/
			0 - YSI_debug.own
			1 - YSI_dependencies.own
			2 - YSI_misc.own
			3 - YSI_post.own
		3 - pawno/include/YSI/Core/
			0 - YSI_bintree.own
			1 - YSI_bit.own
			2 - YSI_commands.own
			3 - YSI_format.own
			4 - YSI_help.own
			5 - YSI_INI.own
			6 - YSI_languages.own
			7 - YSI_player.own
			8 - YSI_text.own
		4 - pawno/include/YSI/Gamemode/
			0 - YSI_properties.own
		5 - pawno/include/YSI/Server/
			0 - YSI_modules.own
		6 - pawno/include/YSI/System/
			0 - YSI_default.own
			1 - YSI_group.own
			2 - YSI_script.own
		7 - pawno/include/YSI/Visual/
			0 - YSI_areas.own
			1 - YSI_checkpoints.own
			2 - YSI_objects.own
			3 - YSI_race.own
		8 - scriptfiles/YSI/
			0 - core.EN
			1 - core.DK
			2 - core.DE
			3 - core.NL
			4 - core.FR
			5 - core.PL
			6 - core_format.YSI
		9 - scriptfiles/YSI/users/
		10 - gamemodes/
			0 - _YSI_EXAMPLE_SCRIPTS_WANTED_.pwn
		11 - filterscripts/
			0 - _YSI_EXAMPLE_SCRIPTS_WANTED_.pwn
		12 - /
			0 - readme.txt
	3 - Installation
	4 - Use
		0 - General
		1 - Users
		2 - INI
			0 - Reading
			1 - Writing
		3 - Commands
			0 - General
			1 - Alternate Names
			2 - Prefixes
			3 - Shortcuts
			4 - /commands
			5 - Permissions
			6 - Warnings
		4 - Text and Languages
			0 - Overview
			1 - Languages
			2 - Loading Text
			3 - Displaying Text
			4 - Example
		5 - Groups
			0 - Explanation
			1 - Use
		6 - Help
		7 - Checkpoints
		8 - Areas
			0 - General
			1 - Types
				0 - Box
				1 - Cube
				2 - Sphere
				3 - Circle
				4 - Polys
			2 - Settings
		9 - Objects
			0 - General
			1 - Use
		10 - Races
			0 - Introduction
			1 - Definition
			2 - Addition
			3 - Starting
			4 - Processing
			5 - Finishing
		11 - Properties
			0 - General
			1 - API functions
				0 - CreateProperty
				1 - CreateBank
				2 - CreateAmmunation
				3 - CreateMoneyArea
				4 - CreateMoneyPoint
				5 - CreateTeleport
				6 - CreateForbiddenArea
	5 - Required Functions
		0 - YSI_debug.own
		1 - YSI_dependencies.own
		2 - YSI_misc.own
		3 - YSI_post.own
		4 - YSI_bintree.own
		5 - YSI_bit.own
		6 - YSI_commands.own
		7 - YSI_format.own
		8 - YSI_help.own
		9 - YSI_INI.own
		10 - YSI_languages.own
		11 - YSI_player.own
		12 - YSI_text.own
		13 - YSI_properties.own
		14 - YSI_modules.own
		15 - YSI_default.own
		16 - YSI_group.own
		17 - YSI_script.own
		18 - YSI_areas.own
		19 - YSI_checkpoints.own
		20 - YSI_objects.own
		21 - YSI_race.own
	6 - Useable Functions
		0 - YSI_debug.own
		1 - YSI_dependencies.own
		2 - YSI_misc.own
		3 - YSI_post.own
		4 - YSI_bintree.own
		5 - YSI_bit.own
		6 - YSI_commands.own
		7 - YSI_format.own
		8 - YSI_help.own
		9 - YSI_INI.own
		10 - YSI_languages.own
		11 - YSI_player.own
		12 - YSI_text.own
		13 - YSI_properties.own
		14 - YSI_modules.own
		15 - YSI_default.own
		16 - YSI_group.own
		17 - YSI_script.own
		18 - YSI_areas.own
		19 - YSI_checkpoints.own
		20 - YSI_objects.own
		21 - YSI_race.own
	7 - Internal Functions
		0 - YSI_debug.own
		1 - YSI_dependencies.own
		2 - YSI_misc.own
		3 - YSI_post.own
		4 - YSI_bintree.own
		5 - YSI_bit.own
		6 - YSI_commands.own
		7 - YSI_format.own
		8 - YSI_help.own
		9 - YSI_INI.own
		10 - YSI_languages.own
		11 - YSI_player.own
		12 - YSI_text.own
		13 - YSI_properties.own
		14 - YSI_modules.own
		15 - YSI_default.own
		16 - YSI_group.own
		17 - YSI_script.own
		18 - YSI_areas.own
		19 - YSI_checkpoints.own
		20 - YSI_objects.own
		21 - YSI_race.own
	8 - Options
	9 - Technical Information
	10 - Changelog
	11 - Future
	12 - Legal
	13 - Credits

===============================================================================

1) About.

1.0) General.

Y_Less' Server/Script Includes (aka YSI) are a set of libaraies designed to make coding of gamemode (especially larger ones) easy by providing a set of fast, stable, efficient and flexible functions to take the emphasis of coding away from HOW things are done to allow more time on WHAT is done.  Currently a basic RPG will take months of coding because things like checkpoint streaming, object streaming, properties etc all take large amounts of coding and integration to get working.  This library set provides all those facilities and more so you only need to worry about where to put your properties and how much they will cost, not whether you rememebered to add the checkpoint to the streaming system you are still not fully sure works properly.

The libraries were also written with speed as a major consideration employing some more advanced techniques such as lists and binary trees to offset the overhead a generic library such as this incurs.  On the whole these techniques offer considerable speed increase, some functions were written multiple times to get the most speed possible out of them.  And where systems are slower than custom counterparts the vast number of extra features should be more than enough to offset the marginal difference.  E.g. the custom command processor is slightly slower than standard searches using strcmp and strtok (especially for small numbers of commands) however this system has renamable functions, automatic called, registering and unregistering of commands, alternate names, optional prefixes and more so the almost negligable speed decrease is more than worth the extra flexability this gives.  Plus the fact that this command system gains very little extra processing time the more commands you add.  With strcmp and strtokif you double the number of commands you double the average processing time, with this doubling the number of commands adds a single comparison function to the processing.  More on the command processor and all other modules in section 2 (files).

Obviously it's not all good, as hinted at earlier there is extra overhead involved in systems like this as instead of your checkpoints been hard coded into your mode and streamer for example, they're stored and loaded from an array.  However due to a wide range of compile time options these overheads can be minimised by tweaking system settings to match your mode.  Things like memory usage and processing time can also be reduced by tweaking settings, this is covered more in section 6 (options).

1.1) History.

The system started unofficially around a year ago, I was developing the first version of SA:Underground (my "on-off-off some more" side project) and needed a way to handle multiple races easilly and load MTA maps as well as my own.  Thus the first version of YSI_race was born.

A little later I was developing my admin script (which has now been re-written about 4 times, almost every one better than other admin scripts and none released :(), based on my earlier messaging and logging script releases.  The latest version of this had a modules system for loading additional scripts for extended functionality and registering their functions with the central script.  It also had an advanced command parser including things like alternate names, prefixes, player permissions, help system and native support for %n for naming commands.  As well as these there was a language system, global user system and ini loader based on passed parameters not reread files (as I didn't like other implementations).  Obviously these were the starts of YSI_text, YSI_languages, YSI_modules (this is the only module in YSI less well developed than it's predecessor), YSI_players, YSI_INI, YSI_format (along with some SA:MP/AMXModX/Quake 3 code), YSI_help and YSI_commands.

At another point in time I had developed my areas script to end the days of complex property creation LVDMod involved, unfortunately mine was even more complicated as I added far too many features in a small space (there are just as many features in YSI_properties but better managed).  This was the basis of YSI_properties, YSI_areas and YSI_checkpoints  I also developed an object streaming system shortly before the release of 0.2 for testing purposes and a new MTA map loader to go with it.

Since these original scripts pretty much everything has been re-written from the ground up (the only original code I know of is Race_OnPlayerEnterRaceCheckpoint and that's been modifed for checkpoint types and variable names (although the general logic is all original)).  As a result some parts of YSI have been rewritten up to four or fives times from scratch, although each time with reference to the last.

1.2) Readme.

1.2.0) Contents.

Lists all the sections in this readme

1.2.1) About.

This section.  Tells you about the script and other associated items of possible interest.

1.2.2) Files.

Lists all the files in the YSI download and gives a brief explanation of what they're for.

1.2.3) Installation.

Explains briefly (as it's easy) how to install YSI into your mode.

1.2.4) Use.

This is one of the major sections.  It explains how to use the major parts of the major parts of YSI.  All the features you may want to use 90% of the time are covered here plus tips on improving your modes custom features and further streamlining development.

1.2.5) Required Functions.

These are all the functions listed down the right hand side which you have to call for the script to work properly.  Note however that almost all of these are called via the Script_ and Default_ interfaces so you don't actually need to worry about them (see section 4.0).  These are generally refered to as core functions in the code file headers though some may be inline or public.

Note: These are only required if you actually use the containing file.

1.2.6) Useable Functions.

These are functions you can use in your script to utilise YSI and do whatever you like.  This is the section most likely to be useful as a reference.  These are generally the API and stock functions in the file headers though some may be inline or public.

1.2.7) Internal Functions.

These are listed here for reference only, you can't use them in your script and they're not listed in the function list in PAWNO.  They are functions used within YSI and which should not be touched as they can mess things up if used improperly.  These are generally static functions in the file headers though some may be static stock, inline, public or core.

1.3) Conventions.

1.3.0) Developing.

There are a few conventions used throughout the code and documentation you should be aware of (mostly just if you're developing YSI itself, most of this is not required knowledge for using the script.

If you want to develop a new library it is requested you use these conventions otherwise you're just writing another library compatible with YSI, not a YSI library.  More on this in section <TO DO>.

1.3.1) Function Types.

Functions are listed in the file headers under a few headings:

core - These are functions required by the script.  They have no typing and will generate warnings if not used.

stock - These are the general library functions, if they're not used they will be excluded from the mode.

static - These are internal functions for the library and shouldn't (and can't) be called from outside the library.  static stock functions are listed here too.

API - These are functions which are common for the script and don't use the library naming scheme for clarity to less advanced coders and for compatability with functions they replace.  There is no set rule for this, I just do it when I feel like it and think it's worth it.

inline - These are not real functions but listed as functions.  They're define macros made to look like functions for speed after compiling as they're very simple bits of code where the overhead of calling a function would significantly affect their run time.

1.3.2) Function Naming.

For readability and clarity YSI uses an OO style system similar to C++ (class::method()) although not exactly the same.  There are few functions which don't follow this but they should be minimised (generally only the functions more likely to be widely used are APIed and even then not all).  The reason for this is reduction of likelyhood of conflicting functions in different libraries and it means functions follow a standard format.  The format is generally:

Filename_FunctionName()

(note the capitalisation) although the lead part doesn't have to be the filename, but preferably something related (the YSI_languages "class" (or what may be occasionally referred to as a class even though it's blatantly not) is just Langs_ as I couldn't be bothered writing Languages_ for every function).

The obvious exceptions to this rule are the YSI_misc and YSI_post files.  YSI_misc just has generic functions so they are just named as normal.  YSI_post is an error catcher for all files so has a number of functions to deal with errors from a number of files when they're not included.

Current prefixes (for collision avoidance):

Debug_, Bintree_, Bit_, Command_, Format_, Help_, INI_, Langs_, Player_, Text_, Property_, Modules_, Default_, Group_, Script_, Area_, Checkpoint_, Object_, Race_

Planned prefixes (so you don't nick my future plans :p) (read into these as you like):

XML_, Zone_, Vehicle_, Pickup_, Class_

The other exception to this rule (although this isn't an important thing at all, just a convention I like), for INI tag callbacks I use:

Filename_GeneralName_%s()

Where %s is obviously the tag name.

===============================================================================

2) Files.

2.0) pawno/

2.0.0) new.pwn

Replacement for the standard new.pwn replacing the public functions with their Script_ counterparts and adding a few other function calls to provide a prefectly compiling base to work off.

2.1) pawno/include/

2.1.0) YSI.inc

The main include file.  This defines all the natives* (within block comments to not affect the compiler) so they appear in PAWNO in the right hand side.  These functions are split up into the different files and in some cases there is a second split (represented by a space) between the functions in there.  These gaps separate standard functions (File_FunctionName()) and API functions (FunctionName()).  There is no difference in use but the standard functions tend to be slightly more advanced, the API fuctions are designed to be dead easy to use (however there aare standard functions which are also easy to use).

This file also includes all the other required files but displays all functions regardless of file compile options.

* "all the natives" refers to all the functions provided by the YSI system (which aren't strictly native) which can (and in some cases should) be called from your script.  For every function on the right you can use there is probably at least one more internally you can't use to protect the operation of the script.

2.2) pawno/include/YSI/

2.2.0) YSI_debug.own

Provides a number of debug functions so you can add debug information to your script without having to remember to remove it again.

2.2.1) YSI_dependencies.own

Processes your compile options to include only the required files and files which can be included given your options.

2.2.2) YSI_misc.own

Provides a largeish number of standard small functions to your script and the includes.

2.2.3) YSI_post.own

Catches errors generated by a incomplete compile set of librarie includes.  I.e. surpresses problems created by excluding certain libraries from your mode.

2.3) pawno/include/YSI/Core/

2.3.0) YSI_bintree.own

Provides an interface for using binary trees simply, used by the script.

2.3.1) YSI_bit.own

Provides bit array functions for the script and library so you don't have to waste entire cells for a single yes/no value per player, you can create bit arrays over 32 bits big to store the yes/no value for every player in only 7 cells not 200 (assuming 200 players).

2.3.2) YSI_commands.own

The new command processor.  Provides functions for adding and dynamically renaming commands and processes commands using a binary tree of hash values for speed.

2.3.3) YSI_format.own

PAWN implementation of the format() function originally written for AMXModX based on vsprintf from Quake 3.  Adds a few extra items such as octal radix and commands (due to their renamable nature).

2.3.4) YSI_help.own

Provides a /help function which allows you to type /help <command> and get help on that specific command (provided the command itself provides this functionality via the 'help' parameter).

2.3.5) YSI_INI.own

Provides highly optimised INI functions for reading and writing INI files without repeated disk accesses and slow file scanning per item as all other INI file implementations do.  Used by the user system and text system.

2.3.6) YSI_languages.own

Provides an interface to the text system for loading multiple files and languages for text used throughout the script to enable messages to be sent in different languages to different people.

2.3.7) YSI_player.own

Provides user systems and per player options for the script.

2.3.8) YSI_text.own

Handles text displays for different languages based on player settings.

2.4) pawno/include/YSI/Gamemode/

2.4.0) YSI_properties.own

Provides fairly high level mode interaction through the handling of multiple types of elements common to a range on modes including properties, ammunations, banks etc.

2.5) pawno/include/YSI/Server/

2.5.0) YSI_modules.own

Provides handling of modules loaded into the script.  Very out of date.

2.6) pawno/include/YSI/System/

2.6.0) YSI_default.own

Calls required functions at the correct times when these functions are called so you only need to worry about calling one function instead of them all in the correct orders.

2.6.1) YSI_group.own

Handles user groups, similar to teams and levels combined.

2.6.2) YSI_script.own

Hooks the callbacks, calls the functions in YSI_default.own and forwards them to your mode as Script_CallbackName().

2.7) pawno/include/YSI/Visual/

2.7.0) YSI_areas.own

Provides area detection in a range of shapes using optimised storage methods.

2.7.1) YSI_checkpoints.own

Provides checkpoint streaming.

2.7.2) YSI_objects.own

Provides object streaming, worlds for objects and more using lists based on a grid structure for speed.

2.7.3) YSI_race.own

Provides functions for creating and running races easilly.

2.8) scriptfiles/YSI/

2.8.0) core.EN

Standard text items in English.

2.8.1) core.DK

Standard text items in Danish.  Translated by TheAlpha.

2.8.2) core.DE

Standard text items in German.  Translated by breadfish.

2.8.3) core.NL

Standard text items in Dutch.  Translated by Fireburn.

2.8.4) core.FR

Standard text items in French.  Translated by yom.

3.8.4) core.PL

Standard text items in Polish.  Translated by 50p.

2.8.6) core_format.YSI

Holds the formatting information for all items in the core language files.

2.9) scriptfiles/YSI/users/

2.10) gamemodes/

2.10.0) _YSI_EXAMPLE_SCRIPTS_WANTED_.pwn

Basically an advert to appear first in people's open dialogue box.

2.11) filterscripts/

2.11.0) _YSI_EXAMPLE_SCRIPTS_WANTED_.pwn

Basically an advert to appear first in people's open dialogue box.

2.12) /

2.12.0) readme.txt

This file.

===============================================================================

3) Installation.

Installation is designed to be as easy as possible.  Provided you have installed the server with it's default directory structure (i.e. with pawno, filterscripts, gamemodes and (possibly if you have one) scriptfiles as child directories) then simply extract the contents of the archive to your server folder.  The files in the archive have the same structure as your server directory so they will all be put in the correct places.  Then simply open pawno and click new.

If you have moved your pawno directory somewhere else you will need to put YSI.inc and the YSI directory (and all children) in your pawno/include/ folder.

===============================================================================

4) Use.

4.0) General.

The easiest way to use YSI is install it and click new but there are more advanced options if you require.

YSI is designed to be highly scalable so beginners and more advanced coders can both use it at a their own level.  If you use the YSI new.pwn file all functions and script calls are already set up so you can just get on with coding as if it were a normal script.  If you choose to integrate YSI into an existing script there are a few more steps you need to take (it's often easier to copy your existing code into the YSI new.pwn file for fast integration).

Obviously YSI libraries require a few callbacks to call them so they know what to do when.  The easiest way as mentioned it to use the provided Script_ interface in new.pwn.  The second easiest way is to use the Default_ interface which calls all the required functions in the correct order.  If you choose to use neither of these methods you will have to call the callback functions in different files yourself from the callbacks.  To aid in this all those functions are not stock so if there is a file you need to call but don't the compiler will issue a warning for that function.  It should be obvious where most of these functions should be called from (e.g. Player_OnPlayerConnect should be called from OnPlayerConnect).  The only ones not named like that are the File_File functions (e.g. Player_Player) these should be called from your init function (OnFilterScriptInit or OnGameModeInit).  Also for efficiency of mode reasons Langs_Langs and Text_Text should be called after everything else.  Command_Parse should also be called with those two and definately after Command_Command.

4.1) Users.

YSI provides native support for users and login systems.  When a player logs in with /login (by default) first OnPlayerLogin(playerid, yid) is called, returning a 0 here refuses the login.  If the login succeedes their data is loaded from their personal file.  yid is their unique identifier used for their file and identification by the script.  All data in the file is grouped by tags so you could have a user file which looks like:

[ysi_core]
language = 0

[my_mode_1]
health = 100.0

[my_mode_2]
health = 50.0

As you can see there are two health values but based on the mode been run you can simply load one.  The ini loading system (which will be explained further in section 4.<TO DO>) reads values from the file and distributes them as required, this is faster and requires far less disk accesses than current methods which request data and load it item by item from the file.  To save the data for your current modes tag simply add the following function to your mode (and forward it):

public LoginDat_<mode_tag>(playerid, identifier[], text[])
{
}

Where <mode_tag> is the tag for this mode's data exactly as it appears in the ini.  E.g. for my_mode_1 in the example ini above (including parsing of certain values):

public LoginDat_my_mode_1(playerid, identifier[], text[])
{
	if (!strcmp(identifier, "health", true)) SetPlayerHealth(playerid, floatstr(text));
	else if (!strcmp(identifier, "wanted", true)) SetPlayerWantedLevel(playerid, strval(text));
}

Obviously that function would load the two items "health" and "wanted" from the ini however with the example above the wanted code would never be called, greatly reducing the need for error checking for either returning 0 or not returning anything required in other ini loading scripts.

When a player logs out OnPlayerLogout(playerid, yid) is called.  The first thing you need to do here is set the tag using Logout_SetTag(tagname[]), in our first example that would be:

Logout_SetTag("my_mode_1");

This ensures the data is saved correclty for this mode, not overwriting other mode's data.

You can then write the data you want saving using:

Logout_SaveString(name[], data[]);
Logout_SaveInt(name[], data);
Logout_SaveFloat(name[], Float:data);

These are just wrappers for the equivalent INI functions but abstract them slightly so you don't need to worry about the INI file handle.

The other commands involved in the user functions are /register and /groupnick.  The first command is fairly obvious in function, the second is similar to the /ns group command on IRC.  It adds your current nick to the stats of the nick specified providing you enter the correct password.

4.2) INI.

4.2.0) Reading

The INI functions in YSI are slightly different to other INI libraries available.  With other libraries you request a line from the INI file, the file is opened and every single line is read until the one you want is reached at which point the data you want is saved and the file closed.  If you then want another piece of data the same process is repeated which is obviously slow, inefficient and not very good on your disk due to the repeated file reads.

This INI library reads all the file at once and you save the data you want which means the file in only read once and if you have a large amount of data not used by any one mode a large amount of searching time will be saved too.  This is done by means of a custom callback system.  You call the INI_Parse function passing a file to parse and the format of the callback functions you want calling.  The call line for the text loading functions is:

INI_ParseFile(filename, "Text_Tag_%s")

The %s is for the tag currently being read so if filename was YSI/core.EN (the default English language file) the callbacks would be:

Text_Tag_ysi_properties
Text_Tag_ysi_race
Text_Tag_ysi_text
Text_Tag_ysi_commands
Text_Tag_ysi_langs
Text_Tag_ysi_help
Text_Tag_ysi_players

This is what the Text_RegisterTag functions in the various YSI files are for, they (if you look at the macro which defines them) create the callback function required to save these pieces of data.  Another example:

INI file (example.INI):

[size]
thing1 = 56
thing2 = 126

[colour]
thing1 = 12
thing2 = 98

PAWN file:

new
	gSize1,
	gColour1;

forward savedata_size(identifier[], data[]);
forward savedata_colour(identifier[], data[]);

main()
{
	INI_ParseFile("example.INI", "savedata_%s");
	return 1;
}

public savedata_size(identifier[], data[])
{
	if (!strcmp(identifier, "thing1")) gSize1 = strval(data);
}

public savedata_colour(identifier[], data[])
{
	if (!strcmp(identifier, "thing1")) gColour1 = strval(data);
}

Obviously after this code is run gSize1 will be 56 and gColour1 will be 12.  You can also include the filename in the callback name:

INI_ParseFile("example.INI", "savedata_%s_%s");
public savedata_size_example.INI(identifier[], data[]) {}

You can also have the filename first:

INI_ParseFile("example.INI", "savedata_%s_%s", true);
public savedata_example.INI_size(identifier[], data[]) {}

You can (as is shown in the player load examples) have a single extra parameter first for array identification:

INI_ParseFile("example.INI", "savedata_%s", false, true, 45);
public savedata_size(number, identifier[], data[]) {}

The first false means do not reverse format parameters (tag name and file name).  The true means include the extra parameter and the 45 is the extra parameter (which can be any single cell value).

The other major difference with this INI library is it fully supports INI comments (; delimited):

; This line won't be read
data = read value ; ignored ending of line

Comments on the ends of lines are also rewritten if the data on that line is changed so doing:

INI_WriteString(file, "data", "written value");

(see section 4.2.1).  Would result in:

; This line won't be read
data = written value ; ignored ending of line

4.2.1) Writing

Writing INI files works on a similar principle to that of reading them - disk access and entire file scans (and, in the case of writing, copies) are bad and time consuming.  For this reason a buffer system is employed.  The buffer system stores all data being written to the ini until you are done writing and close the ini or the buffer fills up.  When either of these events occur the file is loaded and copied, replacing all values in the file with their buffer equivalent where applicable and dunmping everything from the buffer not in the file already under their correct tag in the file.  The buffer is an intertwined list structure so tags can be changed repeatedly and all data added to the end of the buffer will still be associated with their correct tag.  The write process also uses multiple bit arrays to ensure text is not checked against if it's already been written to the file.

To start writing a new INI file simply use:

new INI:nameOfIniHandle = INI_Open("filename");

This will return a handle to the buffer being used for the file specifed or -1 if there are no available buffers.  To write data to the buffer you will first need to set the tag (or the data won't be saved):

INI_SetTag(nameOfIniHandle, "tag_name");

This will set the header for subsequent data to be stored under until the next header is set.  Data is written using:

INI_WriteString(nameOfIniHandle, "identifier1", "data");
INI_WriteInt(nameOfIniHandle, "identifier2", 42);
INI_WriteFloat(nameOfIniHandle, "identifier3", 42.0);

You can then close the file to write all the remaining data from the buffer to the file.

INI_Close(nameOfIniHandle);

That code above will produce an INI file called "filename" with the following data:

[tag_name]
identifier1 = data
identifier2 = 42
identifier3 = 42.000000

Floats are to 6dp by default but this can be altered with the optional extra parameter:

INI_WriteFloat(nameOfIniHandle, "identifier3", 42.0, 2);

Gives:

identifier3 = 42.00

4.3) Commands.

4.3.0) General

Commands in YSI are designed to be similar to DCMD but slightly easier.  As with DCMD you need a declaration and a function however unlike dcmd the declaration should not be in OnPlayerCommandText.  You merely have to declare the command's existence, not check it's called.  The other difference from dcmd is the number of parameters, with dcmd you had to put the command name, the variable you were checking against and the length of the command, none of that is nessecary with ycmd.  The function follows a similar naming convention as well, ycmd_commandname however there is an extra parameter (help) and the function must be public.  Example:

forward ycmd_kill(playerid, params[], help);		// Forward declaration for our public function.

public ycmd_kill(playerid, params[], help)			// Function header.
{
	if (help)										// If a player typed: /help kill (see section <TO DO>)
	{
		Text_Send(playerid, "KILL_COMMAND_HELP");	// Language specific message, see section <TO DO>
	}
	else											// If a player typed: /kill
	{
		SetPlayerHealth(playerid, 0.0);				// Kill the player who entered the command
	}
	return 1;										// Command executed return.
	#pragma unused params							// Not required on public functions but neater
}

Script_OnFilterScriptInit()							// Init function only called once (using the YSI Script_ interface).
{
	ycmd(kill);										// Initial declaration adding the kill command to the list of commands.
	return 1;
}

That example also introduced the start of the help and text/language systems in YSI, as well as used the Script_ interface.  If the only part of YSI you are using is the command processor your code may look more like this:

Command_(kill) return SetPlayerHealth(playerid, 0.0);	// The kill function with reduced header.

public OnFilterScriptInit()								// public not Script_.
{
	Command_Command();									// Must be called first.
	ycmd(kill);											// Commands go here.
	Command_Parse();									// Must be called last.
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	return Command_Process(playerid, cmdtext);			// Must be called here.
}

Here you can first see the Command_(name) function, this is a simple macro to replace all the many forwards and function declarations, it will expand to the same code as the first example.  The main disadvantage to this is the variables are not obviously declared (you can't see playerid being declared as it's hidden in a macro) thus it makes code ambiguous and possibly confusing (I stopped using it after confusing myself during debugging :)).

The other thing you will notice in that example is that as no part of the script besides commands is in use the Script_ interface has been removed (although it can still be used and will adapt to your compile options (see section 6).  Because of this the required Command functions have to be called manually.

4.3.1) Alternate Names.

The YSI command system has a unique feature - alternate names, these will overwrite the default name based on the function called.  As described in section 4.3.0 the command and the function it calls must be the same, as with DCMD, however this is not always feasable.  YSI has an inbuilt /commands command (see section <TO DO>) however your mode may also have a /commands command (although you should be using the server nature of YSI but this isn't fully developed yet...) which will cause problems if they both activate at once.  You can either find where the command and function are declared in YSI (plus every text reference (see section <TO DO>)) or your other mode and alter them, which is all well and good if you can code, or you can simply set an alternate name for the YSI /commands command and it will no longer respond to the original command.  To do this simply put:

Command_SetAltName("commands", "ysi commands");

Or whatever you want the new command to be.  The first parameter is the real command name (which is used extensively throughout YSI as it doesn't conflict internally) to identify what it is you are renaming.  The second parameter is the new command for people to type, but the original ycmd_commands function will still be called.  You also don't need to worry about things like text displaying (for example): "type /commands for a list of commands", YSI has inbuilt support within text to update command names (see section <TO DO>).

You also need to toggle the script to use the altnames, but this is minor:

Command_UseAltNames(1);

This still requires a small bit of coding knowledge on the part of the user but with a bit of clever coding you can easilly come up with something like:

INI file (YSI/options.INI):

[commands]
commands = ysi commands
help = ysi help
login = ysi login

In OnGameModeInit:

Command_UseAltNames(1);
INI_ParseFile("YSI/options.INI", "LoadedOptions_%s");

Elsewhere in your script:

forward LoadedOptions_commands(identifier[], text[]);

public LoadedOptions_commands(identifier[], text[])
{
	Command_SetAltName(identifier, text);
}

Few very basic functions knocked together in 30 seconds and you have written yourself a complete file based command name customisation system almost anyone can use.  This is only scratching the surface of YSI and think how long that would have taken to write using any other combination of system (a lot more that 7 lines (and it can easilly be made 4)).

4.3.2) Prefixes

In the last example of section 4.3.1 I gave an example of how to convert your commands to start with "ysi " (including the space, which is fully supported in YSI).  This is fine if you only want to prefix a couple (and will do for them all) but it's a hassle if you have a large amount of commands to rename, this is where prefixes come in:

Command_SetPrefix("ysi");

With that function all your commands are now:

commands,
help,
login,
etc

They've not changed, that's not right :(

Command_UsePrefix(1);

Gives:

ysicommands,
ysihelp,
ysilogin,
etc

But that's still not quite what you wanted, a quick fix later:

Command_UseSpace(1);

And you've got:

ysi commands,
ysi help,
ysi login,
etc

Much better :).  This can also be easilly integrated into using an INI system but you can do that yourself.

Warning:  If you were to combine the example prefix settings with the example altnames above you would end up with:

ysi ysi commands,
ysi ysi help,
ysi ysi login,
etc

4.3.3) Shortcuts.

Another YSI innovation, shortcuts allow players to do things like:

/a

And have them PERSONALLY configured as another command (this command does not even have to be part of the YSI system).  Currently shorcuts can only be a single character and ascend from the character 'a' through the ASCII character set.  Shorcuts, which part of the command system, are player specific so are classed as part of the Player code.  To add a shortcut use:

Player_AddShortcut('a', "commandname");

4.3.4) /commands

The commands function in YSI is inbuilt into the command processor.  This means you do not need to worry at all about it displaying all the commands, everything available to a player (see section 4.3.5) at any given moment will be displayed in the list, updating as required with alterations in commands and use rights.

/commands uses the Command_Name(funcname[]) function to get the real current name of a function.  Due to the original (and hopefully future) serverwide design of YSI this returns the real name in a property (property 179176128 - the adler32 hash of something I forgot but is "Command" (gotta love code comments)).  If you use this function don't forget to unpack the property string before using.

4.3.5) Permissions.

The YSI command suite has an inbuilt permissions system working on a per-player basis (this is based around the groups system (see section <TO DO>)).  There are no level or team restrictions on commands as you may have someone of equal level (it the conventional admin system sense) who you do not want abusing a certain command but you still want to give access to for other commands of that "level".  Under most systems at best this would have meant creating a whole new level between two others and setting their's to that, at worst it would have meant demoting meaning they couldn't use commands they should have been able to.  That is not a problem in YSI, simply do:

Command_SetPlayerUse("commandname", playerid, 0);

And they no longer have access to that command.  Conversely if you want to give a player temporary (or even permenant) access to a command you can simply do:

Command_SetPlayerUse("commandname", playerid, 1);

As mentioned earlier internally commands are referenced by their "real" name (i.e. the name of the function).  So even if you had used altnames to rename /commands to /thing_to_tell_me_commands you would still do:

Command_SetPlayerUse("commands", playerid, use);

You can still set group options as in team or admin level systems but that will be explained in greater depth in section <TO_DO>.  You can also use:

Command_SetPlayerUseByID(command, playerid, use);

But that would require you knowing the exact index in the internal array of the command you want to set (although this is obviously faster).

4.3.6) Warnings.

There are a number of reasons warnings can be issued when entering commands - you don't have permission to use them, you're a badly connected kicked player, you entered dodgey characters etc.  For each of these there are a number of options.  By default they all return 0, which will give an UNKNOWN COMMAND message from the server, but of course, this being YSI, you can change that:

Command_SetDisconnectReturn(set);
Sets what should be returned to players not connected (1 or 0)

Command_SetIllegalReturn(set);
Sets what should be returned to players who use illegal characters (1 or 0)

Command_SetDeniedReturn(set);
Sets what should be returned to players who try use a command they can't (1 or 0).  1 is best used with Command_UseDeniedMessage(1)

Command_UseDeniedMessage(set);
Sets whether the warning message (YSI_COMM_BLEVEL) should be shown to players who try use a command they can't use


4.4) Text and Languages.

4.4.0) Overview.

One of the major features of YSI is it's integrated language and text system.  Instead of typing what you want to appear on someone's screen directly into your mode you use refernces to loaded strings and put the real text in a file.  It sounds complicated but it's really not.

The whole point of the system is to allow people of different mother toungues to see server and system messages in their own language (subject to available translations of course).  Certain servers, such as certain Dutch or Russian ones, have a definate user base over two distinct major languages (Dutch and English and Russian and English (there may be major Dutch/Russian servers but for obvious reasons I don't play on them thus am not aware of any)).  In these cases there is a definate case for displaying messages in two languages, especially if the user can select which of the languages they would prefer to recieve messages in.

There are a number of obvious ways this can be achieved:

Display both:

SendClientMessage(playerid, 0xFF0000AA, "Example Message");
SendClientMessage(playerid, 0xFF0000AA, "Voorbeeld bericht");

Use comparisons for every single message you have:

if (gPlayerLanguage[playerid] == 1) SendClientMessage(playerid, 0xFF0000AA, "Example Message");
else SendClientMessage(playerid, 0xFF0000AA, "Voorbeeld bericht");

The first is almost always out of the question, especially for larger numbers of languages.  The second, even with switches, becomes unwieldy very quickly the more languages you add.  Plus with both of these methods you have to go all through your code to find every instance to add a language.

Compare those to:

Text_Send(playerid, "EXAMPLE_MESSAGE_NAME");

Then separate files for each language:

file.EN:

EXAMPLE_MESSAGE_NAME = Example Message

file.NL:

EXAMPLE_MESSAGE_NAME = Voorbeeld bericht

It may seem a bit bloated at first but it makes things A LOT easier in the long run, especially as it means you can change loaded languages and text displayed without even recompiling, very useful for released modes and others.

4.4.1) Languages.

The first thing you need to do to use the text system is load some text.  To do thins you need to select some files to load and select what languages to load them for.  You selection of language files may look like (for example):

core.EN
core.NL
core.FR
core_format.YSI
main.EN
main.NL
main_format.YSI

We don't need to worry about the _format.YSI files for now, they'll be explained in section <TO_DO>.  core.XX stores the data for the YSI libraries, in this example main.XX stores the text used in the custom mode.  XX is a lnguage identifier, based on the country shortcode: EN = English, NL = Dutch (Nederlands), FR = French (Français).

We need to load both core and main as the text from both the core script and the mode will be required (this may not always be the case depending on what modules of YSI you require).  To do this we add the following lines to an initialisation function (e.g. Script_OnFilterScriptInit):

Langs_AddFile("core");
Langs_AddFile("main");

There are no file extensions as they are determined by languages.  On the server we are on there are mostly English and French speaking people, so it is decided to only load the data for those languages, so the following functions are added:

Text_AddLanguage("EN", "English");
Text_AddLanguage("FR", "Français");

The first parameter identifies the files to load, the second is the name for the purposes of listing and requesting use of a language.

As you may have noticed there is no main.FR, if this is the case or if the main.FR file is missing certain entries the system will default to displaying the English equivalents.  English is the primary language in this example simply because it was added first, here French is the default language (this also means people joining the server will recieve messages in this language until they change):

Text_AddLanguage("FR", "Français");
Text_AddLanguage("EN", "English");

In this instance, if the French files were missing certain entries no other language would be displayed instead as french is the default so you would simple get an error message for text not found.

4.4.2) Loading Text.

Half the difficulty of loading text was covered in section 4.4.1 just by selecting files to load (and that wasn't exactly hard was it :D), the rest of the loading is done by the text engine but you still have to tell it what text you want to load.  These are selected lines from core.EN:

[ysi_properties]
YSI_PROP_NAME = Property: "%s" Cost: $%d Reward: $%d
YSI_PROP_BUY = Type "/%n" to buy
YSI_PROP_OWN = You already own this property

[ysi_race]
YSI_RACE_COUNTDOWN = %d
YSI_RACE_GO = GO GO GO!!!

As you can hopefully tell from the tags there's text here for properties and for races (the one consisting entirely of "%d" may seem pointless but:

YSI_RACE_COUNTDOWN = Start in: %d seconds

Is just as valid and may be what someone wants for their mode so it was left as a text entry).  If however you didn't want to use the YSI_property system it would be s bit of a waste of time, processing and memory to load them all and store them in the limited text buffer.  That is where tag registering comes in.

For every tag you want in a file you need to add:

Text_RegisterTag(tagname);

To your script.  There is a line in YSI_properties which looks like this:

Text_RegisterTag(ysi_properties);

If you don't include the properties code this line isn't compiled and the properties text is never saved.  What the function actually does is very similar to the Command_(name) function mentioned earlier.  It creates a public function for the INI loading system for that tag, that function then calls the text save system and passes the data over, but only the data with corresponding public functions is saved.  You don't need to worry about HOW it does it, all you need to know is that you mustn't use ""s around the text and you must place the line OUTSIDE other functions (it's actually a whole function, not a function call).

4.4.3) Displaying Text.

So you've loaded selected text from selected files in selected languages, (it wasn't really that hard was it?) - now you want to display it.

Unfortunately there's just a fraction more loading of data to do, fortunately you don't need to worry about any code for it.  The name_format.YSI files mentioned earlier hold the formatting information for your text items.  This means you can change all aspects of your text's appearence (excluding text_draw styling) without any recompiling.  Example of core_format.YSI:

[colours]
GREEN = 0x00FF00AA

[data]
name = YSI_PROP_NAME
color = GREEN

name YSI_PROP_BUY
time 5000
style 3

YSI_SELL_HELP_4
color = 0x00FF00AA

As you can see there are two sections to the file, the first defines colours in much the same way as people do:

#define COLOUR_GREEN 0x00FF00AA

in PAWN scripts.  These colours are used for defining styles in the second section so you can change things easilly, just as in scripts.  The second section defines the text's appearence, default is black SendClientMessage as that is 0, 0 but any aspect can be changed.  Options per text are:

name - Text identifier you are setting data for, identifier optional (as with YSI_SELL_HELP_4 above).
style - How you want the text to appear.  0 is SendClientMessage, anything else is that GameText style.
type - See style.
colour - The colour you want your SendClientMessage text.
color - See colour.
time - Time to display GameText message for.

colour can either be a hex number (0x prefix optional) or a string representing one of the predefined colours.

Note: You can spell colour correctly or you can drop the u if you really insist, I wrote the code to accept either.

Now you have the text loaded and the style information for that text there's not a lot left to do beyond show it:

Text_Send(playerid, "YSI_PROP_BUY");

Going on the stlye information above and the default text entry for this playerid should see:

Type "/%n" to buy

In GameText style 3 for 5 seconds (5000ms) (in actual fact they would see:

Type "/#n" to buy

Due to SA:MP character protection).

%n is a custom format code, it is the command code hinted at earlier.  Using the special Text_SendFormat function we can do:

Text_SendFormat(playerid, "YSI_PROP_BUY", "buy");

buy is the real name of the command but let's say you've used the command altname functionality to rename "/buy" to "/aquire this".  Using that send line the player would see:

Type "/aquire this" to buy

This also supports prefixes (however does not currently support shortcuts).  There are also functions for sending text to all players and groups of people (either custom or based on the inbuilt group system (see section <TO DO>)), and their format counterparts.  The multi-people functions have been optimised for a multi language system so each string for each language is only parsed once (most notable in the format system (YSI_format) so don't just loop through players.

The final thing to note about the text system is that you can choose to not display text very easilly, however not putting it in the source file will display a not found error.  To not show a piece of text at all simply do:

YSI_PROP_BUY

The system will load YSI_PROP_BUY and it's corresponding text (nothing) but instead of displaying a blank line in the chatbox (game text doesn't matter) it will not display the text at all.

4.4.4) Example.

main.EN:

[load]
; These will be loaded
WELCOME_MESSAGE = Welcome to the server %s
BYE_MESSAGE = Cya again
LEFT_MESSAGE = Player %d left			; Has no formatting data so black SendClientMessage
[dont_load]
; These won't be loaded
POINTLESS = Woop I won't waste space

main_format.YSI:

[colours]								; Start of colours section.
RED = 0xFF0000AA						; Define this colour (red).
[data]									; Start of data section.
name = WELCOME_MESSAGE
style = 0
color = RED
; "name = " part not required, style defaults to 0, uses color definition
BYE_MESSAGE
style = 3
; "name = " ommitted.  Will never be seen - time not set, defaults to 0 (shown for 0ms).
POINTLESS
style = 56
; Won't be loaded as unrequired, invalid style but doesn't matter

script.pwn:

#include <YSI>							// Include the YSI files

Text_RegisterTag(load);					// Register the [load] tag from main.XX

Script_OnFilterScriptInit()
{
	Langs_AddFile("core");				// Load standard text
	Langs_AddFile("main");				// Load custom text
	Langs_AddLanguage("EN", "English");	// Load for English language
	return 1;
}

Script_OnPlayerConnect(playerid)
{
	Text_SendFormat(playerid, "WELCOME_MESSAGE", ReturnPlayerName(playerid));
	// Send a formatted message, ReturnPlayerName function from YSI_misc.own
	return 1;
}

Script_OnPlayerDisconnect(playerid, reason)
{
	Text_Send(playerid, "BYE_MESSAGE");
	// Avoids the overhead of the format code
	Text_SendToAllFormat("LEFT_MESSAGE", playerid);
	return 1;
}

There are a few other function calls required to actually load the data but if you use the Script_ interface you don't need to worry about these, if you are bothered look them up in YSI_default.

4.5) Groups.

4.5.0) Explanation.

Another major new innovation in YSI is the idea of goups.  These are designed to extend the conventions of both admin levels and teams in other scripts.  In a nutshell a group is a collection of features a player in that group can use.  Players and features can be in multiple groups too so you can mix and match abilities

If may have been the case before that you had the following systems:

Level 1: Can start votekicks
Level 2: Can start votekicks and kick
Level 3: Can start votekicks, kick and ban

Having the power to kick and start votekicks is very pointless, if someone is misbehaving just kick them, simple.  Most admin systems simly rely purely on inheritance, what lower admins have higher admins have, this, as in the above example, may be redundant or there may be commands you want some admins to have but not others (e.g. admins of similar stature/level but different function).  You may also have an admin who plays constantly and bans many many cheaters but who abuses another function, ordinarily you would demote them, but the level down may not have ban powers.  So you would need to edit your system to include a level which could ban but not do this other function, which may not even be possible given the inherent nature of admin levels, so you're stuck.

As mentioned earlier you can simply remove their ability to use that command or create a new group.

Example above:

Group 1 - Can votekick
Group 2 - Can kick
Group 3 - Can ban

Player 1 is admin level 1 so is in group 1.
Player 2 is admin level 2 so is in group 2.
Player 3 is admin level 3 so is in groups 2 and 3.

In that way there is no redundancy.  You may also have team specific commands for (for example) cops and robbers.  Player 3 is also a cop so is now in groups 2, 3 and 4 however Player 4 is also a level 3 admin but in the robbers team so would be in groups 2, 3 and 5.

So far all this isn't that groundbreaking, you can do those things with a load of code, gTeam and an admin script.  But you can't easilly have a super admin with access to both team commands as gTeam will either be TEAM_COP or TEAM_ROBBER, but you can do with groups:

Player 5 groups = 2, 3, 4, 5

The other major advantage to groups is the ease of altering what is in what group, there are options for checkpoints, areas, objects and commands in the groups system so you can create gang bases, team objectives, admin only areas (although this would be a forbidden area admins DIDN'T have access to, which is slightly counter-intuative but obvious once you think about it (see section <TO_DO>)) etc.

When players join a server they are in the default group.  Every checkpoint, command, object etc you make gets added to the default group automatically for ease of use.  You can't remove players from the default group atm but you can remove items to make them non-usable/visible by default (you can add and remove players to all other groups).

This system again lends itself very heavily towards ini customistation and other dynamic mode creation systems.

4.5.1) Use.

To use a group simply start adding players and items:

Group_AddPlayer(playerid, 13);
Group_SetObject(13, 104, 1);
Group_SetDefaultObject(104, 0);

That code will add the player defined by playerid to group 13, add object 104 to group 13 and remove it from the default group.  If you use that code only people in group 13 (i.e. currently only playerid) will be able to see that object.

Group_AddPlayer(playerid2, 13);
Group_AddPlayer(playerid2, 14);
Group_SetObject(14, 105, 1);
Group_SetDefaultObject(105, 0);

Now playerid2 can also see object 104, additionally they can also see object 105, wheras playerid and everyone else can't.

There is also an optional naming system for groups:

Group_NameGroup(13, "Object 104 only");

However this feature is not developed and thus rather pointless for now (see section <TO_DO>).

The default login/logout system has functions for saving a player's groups so you don't even need to worry about that, just set them and they're saved.

4.6) Help.

The YSI help system is designed to be very simple to use.  The text for the default /help command is defined in core.XX and there are 10 lines incase you want to expand (as explained in section 4.4.3 any lines left blank will simply be skipped for smaller help functions).  There is also an extended help system for commands.  If you type /help <command> the help system will attempt to display help on that specific command.  All YSI core commands support this functionality however it must be coded per command.  As mentioned in section 4.3.0 the header of a command is:

ycmd_name(playerid, params[], help)

If you enter the command normally help is 0, if you use the /help system the command is called with help as 1 so, as shown in earlier commands, the following format is used:

ycmd_name(playerid, params[], help)
{
	if (help)
	{
		// Send command specific help message
	}
	else
	{
		// Process command
	}
	return 1;
}

If you do not have permission to use a command you also don't have permission to view help on the command.

When using the help function alt names are used but prefixes are not.

4.7) Checkpoints.

YSI has an inbuilt checkpoint streamer, simply add your checkpoint to the system and you're away:

CreateCheckpoint(xpos, ypos, zpos, size);

This will return a handle to your checkpoint or NO_CHECKPOINT on fail.  The handle is used in the new callbacks:

OnPlayerEnterCheckpointEx(playerid, cpid)
OnPlayerLeaveCheckpointEx(playerid, cpid)

As well as in other functions referencing the checkpoint.  These callbacks are already implemented in the Script_ interface so you shouldn't need to worry about them, use them as you would any other callback.

Obviously the creation has no playerid so is visible to all players (there are two optional parameters for global player and global world showing but these are depreciated by groups) in all worlds.  This is very different to the normal single checkpoint as you can set them to only be seen by one player, of course you can in YSI too.  You can either use the system functions:

Checkpoint_AddPlayer(cpid, playerid);
Checkpoint_RemovePlayer(cpid, playerid);
Checkpoint_AddVW(cpid, vwid);
Checkpoint_RemoveVW(cpid, vwid);

Or the group functions:

Group_SetCheckpoint(group, cpid, set);
Group_SetDefaultCheckpoint(cpid, set);

And of course you can destroy checkpoints as with normal ones:

DestroyCheckpoint(cpid);

There is also a special function:

Checkpoint_SetVisible(cpid, visible);

This basically removes the checkpoint from the streaming system but keeps it existing and retains all player and world visibility settings.

4.8) Areas.

4.8.0) General.

The areas system allows you to define a wide range of invisible sections of the map for triggering things.  There are many area detection systems already but as with everything in YSI we have tried to incorporate and improve all of these, in terms of feaures, flexibility, ease of use and speed.  The area system has a number of shapes you can create your area in, one of these is a generic polygon so in reality you can make any strightedged 2d shape you can imagine, however this is slower than other methods so basic shapes exist too.  The areas themselves don't actually do anything, when you enter them the custom callback OnPlayerEnterArea is called (and OnPlayerLeaveArea for leaving) and from there you can do what you like.

Area data is stored in groups of 4 floats for efficiency.  For most areas this is enough space to store all the required data however some areas (i.e. cubes and polygons) require more data so use several linked blocks.  For this reason area ids may not always be linear are you may not be able to make as many areas as your options define (see section <TO DO>).  Example:

Area_AddSphere(0.0, 0.0, 0.0, 10.0); // areaid 0
Area_AddCube(-200.0, -200.0, -200.0, -100.0, -100.0, -100.0); // areaid 1
Area_AddPoly(100.0, 100.0, 200.0, 100.0, 300.0, 200.0, 200.0, 300.0, 200.0, 200.0, 500.0); // areaid 3
Area_AddBox(-200.0, 100.0, -100.0, 300.0); // areaid 6

As you can see the different sizes of the different area uses skew the areaids (the next one would be 7 as Box is a single slot area).  The Poly function also has an odd number of parameters, this will be explained further in section 4.8.1.4.  Note that the larger sections do not need a consecutive free block, as long as you have enough space in the array to store all the data, no matter how jumbled the gaps are the data will be inserted (this is one of the instances of list structures in YSI but you don't need to worry about that).  If you add all your areas at the start they wont be mixed up, but if you keep adding and removing areas they may get jumbled.

To use areas effectively you need to use the correct types to detect what you want to detect.

4.8.1) Types.

4.8.1.0) Box.

This is a 2d rectangular area triggered when you're within the two defined corners:

Area_AddBox(Float:minx, Float:miny, Float:maxx, Float:maxy);

To use just get the co-ordinates of two opposite corners of the area you want and use the biggest and smallest x and y points in the appropriate positions.  To do this follow these instructions:

Go ingame.

Find the area you want to get.

Go to one corner and type /save.

Go to the DIAGONALLY OPPOSITE corner and type /save again.

Exit SA and open up savedpositions.txt in your SA directory.

The latest two entries are the ones you just saved, they should look something like these:

AddPlayerClass(137,1216.8715,-41.1225,1000.9531,126.9417,0,0,0,0,0,0); // First position
AddStaticVehicle(418,1205.7108,-23.9991,1000.9531,315.6512,0,0); // Second position

Note: to add comments to your saved lines automatically use "/save <comment here>" instead of "/save".

In both cases the X position is the second parameter, y 3rd, z 4th and angle (although we don't need it) is 5th.

From that info and the collected points we have:

x1 = 1216.8715
x2 = 1205.7108

y1 = -41.1225
y2 = -23.9991

We need the minimum and maximum of each of these (we can also drop a few dp as we don't need that much precision):

xmin = 1205.7
ymin = -41.1

xmax = 1216.9 (rounded, can just be left as 8)
ymax = -24.0 (again, rounded)

Don't forget that -24.0 is bigger than -41.1 as they're negative (I don't see how you possibly can, it's basic counting - you wouldn't forget 10 is bigger than 8, but apparently some people do).

Now we have our sorted points we can use our original function:

Area_AddBox(1205.7, -41.1, 1216.9, -24.0);

Example uses: Standard area checks, entering rooms/map areas.

4.8.1.1) Cube.

Similar to a box but with upper and lower limits:

Area_AddCube(Float:minx, Float:miny, Float:minaz Float:maxx, Float:maxy, Float:maxz);

You get the co-ordinates in exactly the same way as the box but this time the second corner must also be higher (or lower) than the first and you need to use x, y and s.

Because there are 6 pieces of information here cubes take up two data slots.

Example uses: Box triggers you want people to be able to fly over without being affected.

4.8.1.2) Sphere.

Detects when you are within a sphere around a point:

Area_AddSphere(Float:x, Float:y, Float:z, Float:radius);

There is only one point to collect ingame for this but you need to decide how far away you want to be from that point to trigger the detection.

Example uses: Targets for planes, object collision.

4.8.1.3) Circle.

Like a sphere but you only have to be near the point in 2 dimensions (you can be as high as you like (preferably only in in-game terms :p)):

Area_AddCircle(Float:x, Float:y, Float:z);

As a circle doesn't even use a whole data slot there is an optional height parameter:

Area_AddCircle(Float:x, Float:y, Float:z, Float:h = 10000.0);

This allows you to limit the top end of the circle, again for things like planes or possibly pickup detection (as these are easier than spheres for processing).

Example uses: Invisible checkpoints.

4.8.1.4) Polys.

These are a little more complex than the others but obviously more flexible.  The parameters are in sets of co-ordinate pairs, there is no need for sorting largest and smallest of each.  These pairs consist of an x and a y and the pairs go together like a join the dots so they MUST be in the correct order or you'll get the wrong shape.  Example:

0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0:

0.0, 1.0     1.0, 1.0
       *-----*
       |     |
       |     |
       |     |
       |     |
       |     |
       *-----*
0.0, 0.0     1.0, 0.0

The last and first co-ordinates are automatically joined.  Same co-ordinate pairs, different order:

0.0,0.0, 1.0,1.0, 1.0,0.0, 0.0,1.0:

0.0, 1.0     1.0, 1.0
       *     *
       |\   /|
       | \ / |
       |  X  |
       | / \ |
       |/   \|
       *     *
0.0, 0.0     1.0, 0.0

Obviously with the parameters being in pairs there will be an even number.  This can be used to out advantage - if you have an odd number of parameters in the call line the last singular one is assumed to be a max height parameter similar to the circle's height (and by similar I mean exactly the same).

A polygon is only valid if there are at least 3 points (try make a TWO d shape with less than 3 points), to enforce this and not cause problems the exact header for this (and to remind you of the parameters) is:

Area_AddPoly(Float:x1, Float:y1, Float:x2, Float:y2, Float:x3, Float:y3, Float:...);

The height parameter is not obvious due to the variable parameter length but it does exist.

The number of slots a poly takes is the number of parameters you give it / 4 rounded up: 4/4 = impossible, 6/4 = 2, 8/4 = 2, 10 / 4 = 3, 11/4 = 3 etc (4/4 is impossible as that's only 2 parameter pairs, you need at least 3).

Note: polygonal detection based on http://forum.sa-mp.com/index.php?topic=638.msg54680#msg54680 (IsPlayerInAreaEx by koolk).

4.8.2) Settings.

You have already had explained how to use each of the area types and how to detect when you enter or exit one, but as with all the libraries there are other functions for customising the behaviour:

Area_Delete(areaid);

Removes an area from the detection system.

Area_GetPlayerArea(playerid);

Gets a player's current area if they're in one.

Area_SetPlayer(areaid, playerid, set);

Sets wether or not an area can be triggered by this player.

Area_SetWorld(areaid, worldid, set);

Sets wether the area can be triggered in the specified virtual world.

And of course areas can also be goverened by groups.

4.9) Objects.

4.9.0) General.

The objects system is very advanced, employing a number of systems to make streaming as smooth and processor friendly as possible.  All this involves a lot of work under the hook which I'm going to explain briefly - skip to section 4.9.1 if you don't want to know/don't care.

Basically there can be potentially hundreds of players and thousands of objects on a server at any one time, that's a lot of processing which can by very intensive (due to large amounts of floating point calculations).  My original object streamer simply checked all the objects as you would expect, one by one per player every timer itteration.  This new version uses a grid system to reduce the workload significantly (and I have ideas for further optimisations and load reductions).  The whole world is split into lots of grid squares (and two special sections for moving objects and objects beyond the standard +/-3000 bounds) and every dynamic object, when created, is assigned to one of these grid squares (unsurprisingly the one it's in).  When processing the system first gets the player's position, gets a list of all grid squares you can possibly see with current view settings and processes only the objects in those groups (and of course the moving object list as they can be anywhere).

What makes this system even more complicated is I didn't want to restrict people on how many objects one grid section could have as it could have been a HUGE waste of memory (scratch that, is would have been one).  So I implemented a multiple list system into a single array so you could have loads of objects in one place and none in another with no major memory impact.  You will have noticed me mention lists before but they were all implemented later plus they were nowhere near as complicated as this has full deletion and insertion options which the others don't really have.

4.9.1) Use.

All the complex underpinnings are designed to give the end user as simple a time as possible.  To add an object to the system just use one of the following functions:

CreateDynamicObject(model, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0);

Creates an object for all to see.

CreatePlayerDynamicObject(playerid, model, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0);

Creates an object for one person to see.

CreateVWDynamicObject(virtualworld, model, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0);

Creates an object for people only in a certain virtual world to see

CreatePlayerVWDynamicObject(playerid, virtualworld, model, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0);

Creates an object for only one person in one world to see.

These are all just start points and can be fully view set using other Object functions, so an object created with the standard CreateDynamicObject can be set to only show for one player in one world using:

Object_RemoveFromAllPlayers(objectid);
Object_AddToPlayer(objectid, playerid);
Object_RemoveFromAllWorlds(objectid);
Object_AddToWorld(objectid, 12);

That will show objectid only in world 12 and only for playerid.  By default objects (like checkpoints and areas) are visible for all players in all worlds, just adding a player and world to that won't make any difference so you need to alter the default first.

All the native object functions have dynamic equivalents plus a few more I thought were missing in the first place, they're all fairly self explanatory (and explained in section <TO DO> even if not).

Again, as with areas and checkpoints group settings overrule object settings, so if a new player joins after you set the code above they will inherit the default group setting for the object which, unless altered, is to show them it.  However groups don't handle worlds so the world 12 restriction will still apply.  To alter this simply do:

Group_SetDefaultObject(objectid, 0);

It's very simple to write wrappers for these things so you can simply do something like:

SetObjectUniqueView(objectid, playerid, world)
{
	Group_SetDefaultObject(objectid, 0);
	Object_RemoveFromAllPlayers(objectid);
	Object_AddToPlayer(objectid, playerid);
	Object_RemoveFromAllWorlds(objectid);
	Object_AddToWorld(objectid, world);
}

Note: groups will even overrule creation funtions with player specific options.

There is also a new callback added: OnDynamicObjectMoved, it is very similar to the other ones but exists as the object moving may not actually exist for any player at the time of it's completion so the normal callbacks will never get called.

4.10) Races.

4.10.0) Introduction.

There are a few stages to creating a race: definition, addition, starting, processing and finishing.  Sounds complicated but as always we have tried to make the whole thing as simple as possible.  The main part YSI plays in races is during the processing stage, the rest requires some work - it's impossible to write the whole race, only provide functions to facilitate the creation of races.

YSI provides facilities for defining your start grid, checkpoints, race style, prizes, failure options and a whole lot more to make the experience as customisable as possible.

4.10.1) Definition.

To create a race there is actually only one thing you need to do:

new race = Race_Create();

You now have a race although not a very interesting one - 0 laps (sprint race), free entry, 3 second countdown, cars, fixed prize, exit fail, outside, world 0, no restart, no startpoints, no checkpoints (the last two being the main problem for an uninteresting race).  All those things don't mean a lot at the moment but they will become clear.  race holds the pointer to the race, this is needed as you can have multiple races simultaneously with YSI.

For now we will leave that line as it is and go on to making something slightly more interesting:

Race_AddStart(race, 803.76, 1682.11, 5.28, 0.0);

Race_AddCheckpoint(race, 813.44, 1713.02, 5.28);
Race_AddCheckpoint(race, 793.36, 1734.97, 6.30);
Race_AddCheckpoint(race, 774.23, 1722.76, 5.13);
Race_AddCheckpoint(race, 714.00, 1731.86, 4.29);
Race_AddCheckpoint(race, 742.22, 1696.25, 6.46);
Race_AddCheckpoint(race, 770.07, 1692.13, 5.28);

I did say SLIGHTLY more interesting :p.  We now have a race for one player (due to there only being one start point) from 803.76, 1682.11, 5.28 to 770.07, 1692.13, 5.28 via a couple of checkpoints.  Still rather pointless as there's no point (i.e. there's no prize):

Race_SetPrize(race, 0, 10000);
Race_SetPrize(race, 1, 5000);

Now if you come in position 0 (i.e. first) you will win $10,000 second (although impossible in a one player race) $5,000, any other position nothing.

This is still just free money though, can't have that, we'll have to charge for entry to the race:

Race_SetEntry(race, 1000);

Now you can only enter if you pay $1,000 - much better for prizes.  So now you're paying $1,000 to get $10,000, where is all the extra money coming from?  Nowhere atm but you can fix that:

Race_SetFixedWin(race, 0);

If you set this to 0 then the system will ignore the amounts you set for positional prizes and instead base what you win on how much the race costs.  E.g. If the race costs $1,000 to enter and 6 people enter there will be a $6,000 prize fund - $3,000 for 1st, $2,000 for second and $1,000 for 3rd (nothing after that (although this is configurable - see section <TO DO>).  However if only 4 people enter the fund is only $4,000 so 1st = $2000, 2nd = $1333 and 3rd = $666 (the lost dollar (due to rounding) can go to the event organiser (or you could send it to me :p)).  If you set fixed values but use fixedwin 0 the fixed values will simply be ignored.  Fixed prizes are on by default.

What other options are there?

Race_SetArial(race, 1);

Use the donut plane checkpoints instead of the large car ones for arial races.  Default 0.

Race_SetRestart(race, 1);

Keeps the race in memory after completion so you can restart it without having to reconstruct the whole thing.  Default 0.

Race_SetCountdown(race, 5);

Sets the number to count down from when the race is about it start.  Default 3.

Race_SetInterior(race, 3);

Used for indoor races to spawn people properly.  Default 0.

Race_SetWorld(race, 56);

Puts the racers in a separate virtual world.  Default 0.

Race_SetExitTime(race, 10000);

Time in milliseconds you're allowed to be out your vehicle during a race before you fail.  Default 0.

Race_SetLaps(race, 2);

Pretty obvious.  0 laps is a straight sprint, 1 ends at the first checkpoint after 1 lap, more that 1 ends at the first checkpoint after multiple laps.

That's a lot of functions to remember, but remember "For now we will leave that line as it is" referring to the Race_Create line?  The full header of Race_Create is:

stock Race_Create(laps = 0, entry = 0, countdown = 3, bool:arial = false, bool:fixedPrize = true, exitTime = 0, interior = 0, world = 0, bool:restart = false);

Now do you see where all those function defaults came from?  All the parameters in the Race_Create function are optional so you can do:

Race_Create(); // Uses all defaults

Race_Create(0, 0, 3, false, true, 0, 0, 0, false); // Still all defaults but expressed explicitly

Race_Create(3, 10000, 5, true, true, 60000, 45, 200, true); // 3 laps, $10,000 entry, 5 second countdown, arial checkpoints, fixed prize, 60 second amnesty outside vehicles, set in interior 45 and world 200, saves race data after race completion

Race_Create(.restart = true); // Little know PAWN function - keeps all defaults except the last

Race_Create(3, 1000, .world = 200); // 3 laps, $10,000 entry, set in world 200

Remember that which ever you use you can change the data with the other functions later.

4.10.2) Addition.

Addition is simply adding people to a race - it's not very interesting with no racers.

Race_PlayerJoin(playerid, race);

The race parameter isn't first this time but that's not major.  This function will add a player to the list of racers waiting for the race to start.  They won't be moved untill the countdown starts however.  If you want a player to drop out before a race has started use:

Race_PlayerLeave(playerid);

You can also use:

Race_PlayerLeave(playerid, 1);

Which will give them the money they paid to race back.  If a player drops out after the countdown has started the can't get their money back.

4.10.3) Starting:

To start a race simply do:

Race_Start(race);

This checks there are racers and that they're still valid for racing, sends them to the start line and starts the countdown.  You must check this function as if the countdown is started the function will return 1, if for some reason it isn't (no racers or no-one has a vehicle) it will return 0.  Races which return 0 are not removed from the system even if Race_SetRestart is not set.

4.10.4) Processing:

All the race processing is done by YSI as that's the whole point of the system, you don't need to do anything.

4.10.5) Finishing:

There are a few ways people can finish a race and there are callbacks for them all:

OnPlayerExitRace(playerid, race)

Called if a player leaves a race before completion (i.e. out their car too long or died).

OnPlayerFinishRace(playerid, race, position, prize, time)

Called when a player successfully completes a race.  Postion starts from 1 and time is in milliseconds.  The money is given to them by the script, it's just for the mode writer's reference (for saving or anything).

OnRaceEnd(race)

Called when a race is completely over (may be called the moment you start the race if all the entered racers have left the server or aren't in vehicles).

On finishing a race (however they finished) the racers will be returned to their previous positions but of course you can chage this as the callbacks are called after things like money awarding and position setting are done.

4.11) Properties.

4.11.0) General.

The YSI properties script introduces a number of common gamemode elements in an easy to use form for fast creation of modes and simple recreation of existing modes.  Some of the most popular things asked for in modes are features like buyable houses, forbidden areas and money points (due to the popularity of certain servers).  Up until now you required either an good knowledge of PAWN to create your own checkpoint streaming system or a good knowledge of PAWN to modify an existing one, either way you needed to know what you were doing.  There were also major limitations to every streaming/properties system (LVDMod (sintax, based on LVDM by jax) was very hardcoded and inflexible, xCheckpoint (Boylett) was only checkpoints, no streaming, LGareas (aka area script) (me) while trying to remove the complexities involved with LVDMod added complexities by being in an array format with all data required, it was also completely undynamice so entirely failed at it's goal.  Other streaming systems were so embedded in modes they were next to impossible to properly extract.

Thus this properties system was created to be simple to use, dynamic and have all the functionality of my areas script but without requiring everything to be defined.

Properties don't have use functions of their own, their useability is based entirely on their underlying checkpoint or area.  Properties use YSI_checkpoints and YSI_areas for detection (as that's what they're for).  To hide a property for a player hide the area or checkpoint for that player.  To get a property's marker use:

new cp_or_area = Property_GetLink(property);

Where property is the return value from one of the creation functions and cp_or_area is a pointer to either a checkpoint or area depending on the property type (see section 4.11.1).

4.11.1) API functions.

4.11.1.0) CreateProperty.

This obviously creates a buyable house at the specified co-ordinates (it's that sort of property, not the cross-script data transfer property).  There are a number of options for these mostly based on existing common parts of modes.  Cost, reward, resale price, sell only options (no buyouts), time between rewards and multi-owners (a new feature for YSI for gang or group ownership):

CreateProperty("Centre of the world", 0.0, 0.0, 5.0, 10000, 1000);

That is an example of a basic property setup.  The name is required for information on the property (it's not essential though).  The next three parameters are obviously the location of the property, then the price to buy it then the reward you get periodically for owning it:

CreateProperty("Centre of the world", 0.0, 0.0, 5.0, 10000, 100, 6000);

The additional parameter here is time between rewards, we've divided the reward by 10 so instead of 1000 every 60 seconds (60000ms - default) you get 100 every 6 seconds (6000ms).

CreateProperty("Centre of the world", 0.0, 0.0, 5.0, 10000, 1000, .sell = 1, .reduce = 1);

This will set properties so they can only be sold not bought out.  The example uses named parameters as some optional ones are skipped.  It also sets the sale value of a property to be less than what you bought it for (the exact amount is a constant for the script but configuable at compile time (see section <TO DO>), default is 60% of original cost).

CreateProperty("Centre of the world", 0.0, 0.0, 5.0, 10000, 1000, .increase = 1);

This basically adds inflation to your properties.  Every time you buy a property it increases the price by a predefined amount (default 25%).  This can hopefully be used to reduce repeated outbuyings without the need for selling only modes.  Note that if you use increase, sell and reduce you will get 75% of your purchase back (under default settings) as the price increase is applied before the sale cost is calculated and 1.00 * 1.25 * 0.60 = 0.75.

CreateProperty("Centre of the world", 0.0, 0.0, 5.0, 10000, 1000, multi = 1);

If the multi flag is set then buying a property will not remove the previous owner, instead you will both get the reward (I may later implement a system to divide the money between owners evenly).

Underlying system: Checkpoints.

4.11.1.1) CreateBank.

Creates a bank marker at the specified position.  This is a very simple function:

CreateBank(x, y, z);

Creates a bank at x, y, z.  Stepping into it prompts you with your balance and commands to bank, withdraw and view your balance.  Bank and withdraw you can only use in the marker, balance can be used anywhere (let's pretend it's the 21st century and you can access your account on your mobile :p).  There is one optional parameter:

CreateBank(x, y, z, "Screw You Over Bank");

This names the bank, it is purely aesthetic - the name if existant will display when you step in the marker (this could be combined with checkpoint player options to give players their own bank companies and branches if you're that anal about realism :p).

Underlying system: Checkpoints.

4.11.1.2) CreateAmmunation.

This is probably the most complicated property command to use (and to write), not really because it's hard but because all the others are so rediculously easy and this takes a bit of time.  The format is:

CreateAmmunation(x, y, z, spawn, instant, 
	weapon1, ammo1, price1,
	weapon2, ammo2, price2,
	...,
	weaponN, ammoN, priceN);

The first 5 parameters are required and it's generally advised you have at least one weapon for sale so you need at least 8 parameters (YSI.inc lists 8 and the variable part but this is not enforced in the code).

The first 5 are relatively simple x, y and z are the location of the shop obviously, spawn is a flag for wether players get the weapon when they spawn (i.e. sets items from the shop to be bought as spawn weapons), instant sets the weapons bought to be given to the player instantly.  These two options are not mutually exclusive (i.e. you can sell weapons for instant purchase and as spawn weapons at the same time).

The next load of parameters must be in groups of three (the function will return -1 if an invalid number of parameters (3n + 5 where n is the number of weapons you want to well) is sent.

weapon is an identifier of the weapon you want to buy:

WEAPON_BRASSKNUCKLE, WEAPON_GOLFCLUB, WEAPON_NITESTICK, WEAPON_KNIFE, WEAPON_BAT, WEAPON_SHOVEL, WEAPON_POOLSTICK, WEAPON_KATANA, WEAPON_CHAINSAW, WEAPON_DILDO, WEAPON_DILDO2, WEAPON_VIBRATOR, WEAPON_VIBRATOR2, WEAPON_FLOWER, WEAPON_CANE, WEAPON_GRENADE, WEAPON_TEARGAS, WEAPON_MOLTOV, WEAPON_COLT45, WEAPON_SILENCED, WEAPON_DEAGLE, WEAPON_SHOTGUN, WEAPON_SAWEDOFF, WEAPON_SHOTGSPA, WEAPON_UZI, WEAPON_MP5, WEAPON_AK47, WEAPON_M4, WEAPON_TEC9, WEAPON_RIFLE, WEAPON_SNIPER, WEAPON_ROCKETLAUNCHER, WEAPON_FLAMETHROWER, WEAPON_MINIGUN, WEAPON_SATCHEL, WEAPON_SPRAYCAN, WEAPON_FIREEXTINGUISHER, WEAPON_CAMERA, WEAPON_PARACHUTE, WEAPON_ARMOUR

These are the standard identifies from a_samp.inc plus WEAPON_ARMOUR for selling armour.  Any other identifiers you find won't do anything and will simply be skipped (including their ammo and price).

ammo is obviously how much ammo you want to sell the weapon with.  For melle weapons it is suggested that this is 1 as certain ones don't work with 0 ammo despite the fact they don't need ammo.

price is how much you want to charge for the weapon.  You may want to bear in mind that spawn weapons are a lot more valuable than instant gain weapons.

The ammunations use menus for purchasing however if you have more than 12 weapons in the list the menu will automatically split into multiple pages.

Example:

CreateAmmunation(2040.0568, 1343.4222, 10.6719, 1, 0,
	WEAPON_GRENADE,			9,		1000,
	WEAPON_DEAGLE,			200,	2000,
	WEAPON_TEC9,			500,	8000,
	WEAPON_SILENCED,		500,	1500,
	WEAPON_SHOTGSPA,		40,		5000,
	WEAPON_M4,				250,	6000,
	WEAPON_ROCKETLAUNCHER,	10,		25000,
	WEAPON_MINIGUN,			3000,	100000,
	WEAPON_RIFLE,			100,	5000,
	WEAPON_MP5,				300,	10000,
	WEAPON_SHOTGUN,			40,		5000,
	WEAPON_MOLTOV,			9,		9000,
	WEAPON_FLOWER,			1,		50,
	WEAPON_DILDO,			1,		50,
	WEAPON_SHOVEL,			1,		50,
	WEAPON_NITESTICK,		1,		50,
	WEAPON_DILDO2,			1,		50,
	WEAPON_CANE,			1,		50,
	WEAPON_SATCHEL,			15,		1500,
	WEAPON_PARACHUTE,		1,		200,
	WEAPON_SPRAYCAN,		350,	50,
	WEAPON_CAMERA,			25,		100,
	WEAPON_COLT45,			200,	1000,
	WEAPON_SAWEDOFF,		40,		5000,
	WEAPON_AK47,			350,	20000,
	WEAPON_ARMOUR,			200,	200
);

There are 26 items there, that's 3 pages of weapons each with clearly visible prices and ammo amounts to spawn with (if the list looks messed up a bit download notepad++ and set tab size to 4 (default)).

The menu works like the real ammunation menu to some extent.  There's no groupings but one you've selected a weapon there's a confirmation screen.  Exit on the confirmation returns to the list, exit on the list exits ammunation.  Weapons you can't afford are blanked out in the main list so you can't try buy them.

Underlying system: Checkpoints.

4.11.1.3) CreateMoneyArea.

Area properties work slightly differently to checkpoint ones.  Because there are so many types of area (see section 4.8.1) these require you to provide an area yourself via use of a pointer:

new moneyArea = Area_AddPoly(100.0, 100.0, 200.0, 100.0, 300.0, 200.0, 200.0, 300.0, 200.0, 200.0, 500.0);
CreateMoneyArea(moneyArea);

Alternatively the area systems are designed to correctly handle invalid inputs so this will not cause a problem if the area is not made (the system was actually designed for this):

CreateMoneyArea(Area_AddPoly(100.0, 100.0, 200.0, 100.0, 300.0, 200.0, 200.0, 300.0, 200.0, 200.0, 500.0));

Using default settings this will give you $100 every 10 seconds (10,000ms), this being YSI however you can of course easily change this:

CreateMoneyArea(moneyArea, 1000, 60000);

You will now get $1,000 every 60 seconds (I used the first example for clarity).

Underlying system: Areas.

4.11.1.4) CreateMoneyPoint.

Basically like CreateMoneyArea but you have to be in a checkpoint instead of an area:

CreateMoneyPoint(100.0, 200.0, 5.0, 10.0);

The first three are position of the point, the fourth parameter is the size of the checkpoint you have to stand in.  As with CreateMoneyArea there are two additional optional parameters for amount and interval (again with defaults 100 and 10,000):

CreateMoneyPoint(100.0, 200.0, 5.0, 10.0, 200, 20000);

Underlying system: Checkpoints.

4.11.1.5) CreateTeleport.

This creates a marker to send you to another point on the map instantly or (if applicable) when you pay):

CreateTeleport(100.0, 100.0, 5.0, 2000.0, 2000.0, 2000.0);

That will create a marker at 100.0, 100.0, 5.0 which when entered will automatically teleport the player to 2000.0, 2000.0, 2000.0.

You can also set a price for the teleport which will automatically be taken off the player when they enter (assuming they can afford it, if not they're not going anywhere):

CreateTeleport(100.0, 100.0, 5.0, 2000.0, 2000.0, 2000.0, 100);

You can also name the destination so a welcome message appears when you get to the other end (YSI_TELS_NAME):

CreateTeleport(100.0, 100.0, 5.0, 2000.0, 2000.0, 2000.0, 100, "very high in the air");

Underlying system: Checkpoints.

4.11.1.6) CreateForbiddenArea.

As with CreateMoneyArea this requires a passed area to operate:

new forbiddenArea = Area_AddPoly(100.0, 100.0, 200.0, 100.0, 300.0, 200.0, 200.0, 300.0, 200.0, 200.0, 500.0);
CreateForbiddenArea(forbiddenArea);

(Again you can put the Area function directly into the property function).  If you enter this area you will be killed instantly (more accurately you will loose 1000 health instantly but that kills most people).  If you don't want to kill people, merely keep them out do:

CreateForbiddenArea(forbiddenArea, .kick = 1);

This will kick them back to their last good position instead.  You can also make them die slowly as a deterrent:

CreateForbiddenArea(forbiddenArea, .health = 10);

Note: there is no interval setting for this function so you will need to adjust the amount of health lost accordingly (it's also not a float).  If you want to keep people in the area instead of out do:

CreateForbiddenArea(forbiddenArea, .invert = 1);

Health and kick settings will now be applied if you leave the area rather than enter it.  You can also name the area if you really want but this is just for a warning message on entry (YSI_FORBIDDEN_2):

CreateForbiddenArea(forbiddenArea, .name = "an admin only zone");

Finally note that using a forbidden area is being affected by it, not by being allowed in it so if you want people to be able to walk in the forbidden area remove them from the underlying area data.  Also if you spawn someone in an area they're not supposed to be in the system will either repeatedly kill them as they respawn back there or send them back to their previous position which could be anywhere (as it could be the last person in that slot's position).

Underlying system: Areas.

===============================================================================

5) Required Functions.

5.0) YSI_commands.

5.0.0) Command_Command();

Declares the commands command for script use.  Called from the start of OnGameModeInit or OnFilterScriptInit.

5.0.1) Command_Process(playerid, cmdtext[], help = 0);

playerid - Player to process a command for.
cmdtext[] - Command entered.
help - Wether help on a command is wanted or just the command itself.

Processes a player's input according to the commands entered into the system.  When help is 1 the function has been called from the help command so ignores prefixes and calls the function with a help parameter to display help on the command instead of executing the command.  Called from OnPlayerCommandText.

5.0.2) Command_Parse();

Once most commands are entered into the system this is called to sort the binary tree of hashes for more efficient searching.  Called from the end of OnGameModeInit or OnFilterScriptInit.

5.1) YSI_help();

5.1.0) Help_Help

5.2) YSI_languages.

5.2.0) Langs_Langs();

Loads requested files and functions for passing to text system.  Called from the end of OnGameModeInit or OnFilterScriptInit.

5.2.1) Language:Langs_AddLanguage(identifier[], name[]);

identifier[] - Shortcode for the langauge (e.g. EN), used for the filename extension.
name[] - Name of the language (e.g. English).

This adds a language to the list to be loaded.  This means all required text will (where possible) be loaded as an option in this language.  Called anywhere but mainly in OnGameModeInit or OnFilterScriptInit.

5.2.2) Langs_AddFile(filename[], path[] = "");

filename[] - File to load (excluding extension).
path[] - Where the file is located.

This adds a file to the list to be loaded so all required selected text from this file will be loaded in all applicable languages.  This excludes the file extension as the extension is a language identifier.  Called anywhere but mainly in OnGameModeInit or OnFilterScriptInit.

5.3) YSI_players.

5.3.0) Player_Player();

Sets up initial array values and defines the commands for use by the system.  Called from the start of OnGameModeInit or OnFilterScriptInit.

5.3.1) Player_OnPlayerConnect(playerid);

playerid - ID of player who connected.

Resets player specific variables.  Called from OnPlayerConnect.

5.3.2) Player_OnPlayerDisconnect(playerid, reason);

playerid - ID of player who left.
reason - Disconnection type (i.e. why they left).

Auto logs a player out and saves given data (assuming they're logged in, otherwise does nothing).  Called from OnPlayerDisconnect.



===============================================================================

6) Useable Functions.

6.0) YSI_debug.own.

6.0.0) Inline.

6.0.0.0) Debug_Code_<level>(code);

level - Debug level to run the code at.
code - Code to run.

This isn't really a function as the first parameter is part of the name and code is not a variable, it's a code chunk and may be written as so:
	
Debug_Code_1(if (bla == 2) { bla++; printf("%d", bla); });
	
The code must all be on one line to avoid errors.

This will, when used in conjunction with the _DEBUG option (see section <TO DO>) compile and execute the given code only if the required debug level is in effect.  Below the stated level the code will be ommitted.  This is to allow faster execution of non-debug builds without the need for loads of searching and removal or commenting of debug code, simply set the debug level to 0.

6.0.0.1) Debug_Print_<level>(format[], ...);

level - Debug level to print at.
format[] - Format.
...

This is very similar to Debug_Code_<level> (see section 5.0.0.0) in that it is only compiled for certain debug levels but it's just used for generic print statements as they're far more common for debugging than whole chunks of code:

Debug_Print_4("variables: %d, %d", i, j);

6.2) YSI_misc.own.

6.2.0) chrfind(needle, haystack[], start = 0);

needle - The character you want to find in the string.
haystack[] - The string you want to find it in.
start - The position in the string to start searching from	.

Like strfind this finds a specific thing in a string but is designed for finding single characters as strfind can be very slow.  This is FAR faster on characters.

chrfind('a', "abcdefga"); // 0
chrfind('e', "abcdefga"); // 4
chrfind('a', "abcdefga", 2); // 7

6.2.1) chrnfind(needle, haystack[], start = 0);

needle - The character to search for the end of.
haystack[] - The string to search .
start - The point to start searching from.

Like chrfind but searches for the first character which isn't the one specified (may sound useless but I wrote it cos I needed it):

chrnfind('a', "abcdefga"); // 1
chrnfind('a', "aaaab"); // 4
chrnfind('a', "bbaab", 2); // 4

6.2.2) strcpy(dest[], source[], max, len = -1);

dest[] - Location to copy the string too.
source[] - Location to copy the string from.
max - Size of target.
len - Length of string to copy.

Copies a string from one place to another.  You may wonder why it's not:

max = sizeof (dest)

but 3d arrays incorrectly return the size of the third dimension as 1 all the time and there are a lot of strings like that in YSI.

6.2.3) bernstein(string[]);

string[] - String to hash.

Generates a bernstein hash of a given string.  This is a very weak hash algorithm with quite a few collisions but it's very fast.  It is not used for sensitive data (such as passwords) and should never be but it is used for hash tables of strings in things like the text and command systems.  These do not need to be secure at all (as the text is there as well so they can't be secure) but they do need to be fast which this nicely fits the bill for.

In the text and command systems the resulting match is then checked using conventional string comparison methods to avoid collisions but defined colours from _format.YSI aren't (as they're really unimportant and this saves saving colour names for no real good reason).

6.2.4) StripNL(str[]);

str[] - String to remove characters for.

This function removes \r\n and other non-printable characters from the end of a string (including trailing spaces).  The original version was hugely bigger, probably slower and did less, this is a much better incarnation.  The resulting string is returned in str, not returned from the function.

6.2.5) strconcat(str1[], str2[]);

str1[] - First string.
str2[] - Second string.

Concatenates the two strings and returns the result.

6.2.6) QSort(numbers[], left, right);

numbers[] - Binary tree input array of data to sort.
left - Start point of the section of the array being sorted.
right - End point of the section of the array being sorted.

Do no


		strtolower - Makes a string lowercase.
		ReturnPlayerName - Returns a player's name.
		ishex - Checks if a string is a hex number.
		binstr - Converts a string to boolean.
		numstr - Converts a number to a string and returns it.
	Static:
		-
	Inline:
		QuickSort - Entry point for QSort.
		chrtolower - Makes a character lowercase.
		ceildiv - Rounded up integer division.
		floordiv - Rounded down integer division.
		iseven - Checks if a number is even.
		isodd - Checks if a number is odd.


5.3) YSI_post.own.
5.4) YSI_bintree.own.
5.5) YSI_bit.own.
5.6) YSI_commands.own.
5.7) YSI_format.own.
5.8) YSI_help.own.
5.9) YSI_INI.own.
5.10) YSI_languages.own.
5.11) YSI_player.own.
5.12) YSI_text.own.
5.13) YSI_properties.own.
5.14) YSI_modules.own.
5.15) YSI_default.own.
5.16) YSI_group.own.
5.17) YSI_script.own.
5.18) YSI_areas.own.
5.19) YSI_checkpoints.own.
5.20) YSI_objects.own.
5.21) YSI_race.own.
