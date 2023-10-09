# Quick Start

ALS (the Advanced Library System) is a well established standard for hooking callbacks in multiple includes transparently, using a well known set of pre-processor directives to mitigate any collisions. y_als is a core module in YSI, though it is also quite an internal one in that it is only really used by YSI. However, it does provide a number of useful features that can make working with callbacks (especially large numbers of them) simpler. This library was originally developed to simplify the development of ALS hooks, but the actual code used within ALS has advanced to such a point that this library is now largely surplus to requirements. However, it still allows you to do things "for all" callbacks simply without having to worry about parameters/calling conventions/specifiers etc.

Some of the "improvements" here may seem minimal, but in a large library like YSI which can hook any given callback multiple times (and it does hook them all in at least one place), it makes a big time saving.


## Errors
### Use ALS_MAKE not ALS_PREFIX

This error comes up when converting from an older to a newer version of YSI. Previously y_als used the following syntax for generating unique symbol names:
```pawn
#define ALS_PREFIX Mode
```
However, due to changing requirements this was switched to:
```pawn
#define ALS_MAKE<%0...%1> %0Mode%1
```
The replacement is fairly mechanical, simply swap:

```
ALS_PREFIX
```
For:
```
ALS_MAKE<%0...%1>
```
And:
```
<prefix>
```
For:
```
%0<prefix>%1
```
(where <prefix> is whatever your prefix was previously).

## Example
Standard ALS hook:
```pawn
new
	bool:gHasOPC;

public OnGameModeInit()
{
	gHasOPC = funcidx("Hook_OnPlayerConnect") != -1;
	return CallLocalFunction("Hook_OnGameModeInit", "");
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit Hook_OnGameModeInit

forward OnGameModeInit();

public OnPlayerConnect(playerid)
{
	if (gHasOPC)
	{
		return CallLocalFunction("Hook_OnPlayerConnect", "i", playerid);
	}
	return 1;
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect Hook_OnPlayerConnect

forward OnPlayerConnect(playerid);
```

Using y_als:
```pawn
#define ALS_PREFIX Hook
#include <YSI\y_als>

ALS_DATA<>

public OnScriptInit()
{
	ALS_DETECT<ScriptInit>
	ALS_DETECT<PlayerConnect>
	ALS_CALL<ScriptInit>
}
#undef OnScriptInit
#define OnScriptInit Hook_ScriptInit

ALS_FORWARD<ScriptInit>

public OnPlayerConnect(playerid)
{
	ALS_CALL<PlayerConnect>
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect Hook_PlayerConnect

ALS_FORWARD<PlayerConnect>

#undef ALS_PREFIX
```
Note that this is not a fair comparison - the first code block will not work in a filterscript, the YSI version will.

### Explanation
Assuming you already understand ALS, this will go through every line of the second version in turn.
```pawn
#define ALS_PREFIX Hook
```
In the original version "Hook_OnPlayerConnect" was used, this is the same required prefix as there, but defined only once in a file to reduce typos mistakes (which are not detectable in strings).
```pawn
#include <YSI\y_als>
```
Just include the ALS code. Frankly you don't even need this if you've already included at least one YSI file (any of them - y_als is one of the globaly incldued "core" files because it makes hooks simpler.
```pawn
ALS_DATA<>
```
This is similar to the "gHasOPC" variable in the original code, providing memory in which to store wether or not another callback exists. The difference between this and the original version is that this is designed to efficiently handle all the default SA:MP callbacks (plus a few YSI ones) - currently it uses only 2 cells for them all.
```pawn
public OnScriptInit()
```
This is a YSI abstraction, it is either "OnGameModeInit" or "OnFilterScriptInit", depending on what the script is running as - basically it is called at the start of a script regardless of what the script is. What's more, you no longer need the "FILTERSCRIPT" definition for this to work - it figures it all out at runtime and so always works even if a user gets something wrong. This is frankly very useful for writing libraries!
```pawn
ALS_DETECT<ScriptInit>
```
This checks if there are any more of this callback that need chaining (as in the standard version of ALS). There is a slight limitation of the system in that you must do this even for callbacks that are only ever called once (such as "OnScriptInit"). Note the lack of "On" in this text for simplicitly.
```pawn
ALS_DETECT<PlayerConnect>
```
This checks to see if "Hook_PlayerConnect" exists, just the same as the "funcidx" code did in the original ALS version.
```pawn
ALS_CALL<ScriptInit>
```
If "Hook_ScriptInit" exists, call it and return the result. If it doesn't then just return the default value (1 for "OnScriptInit").
```pawn
#undef OnScriptInit
```
"OnScriptInit" is a YSI callback, which were all designed to be "ALS protected", as in you don't need the complex ALS macros to hook them, you just undefine the old version and define a new version.
```pawn
#define OnScriptInit Hook_ScriptInit
```
This renames the next version of the callback so that the calls can be chained (again as in ALS). Note again the lack of "On", this is to reduce symbol lengths for some longer callbacks.
```pawn
ALS_FORWARD<ScriptInit>
```
Forward the new version of the callback (i.e. "Hook_ScriptInit").
```pawn
public OnPlayerConnect(playerid)
```
This is just a normal (ALS hooked) callback WITH A PARAMETER.
```pawn
ALS_CALL<PlayerConnect>
```
This chains the current callback just as in the old version of ALS code, but with NO MENTION OF THE PARAMETER. Things like the "CallLocalFunction" specifier are abstracted - the system just knows to use "i" not "ssi" for example, it also doesn't chain the call if the other hooked function doesn't exist instead it returns the default return value. Again this is "1" for "OnPlayerConnect", but its "0" for "OnPlayerCommandText" and again the system knows this and does things properly.
```pawn
#if defined _ALS_OnPlayerConnect
```
This is just the standard ALS hook macro set, which is unfortunately needed still. This line sees if another hook already exists.
```pawn
#undef OnPlayerConnect
```
If another version of the hook already exists, remove the old hook renaming.
```pawn
#define _ALS_OnPlayerConnect
```
If this is the first hook on "OnPlayerConnect", tell subsequent libraries (if any) that at least one hook now exists, and has defined a pre-processor symbol called "OnPlayerConnect".
```pawn
#define OnPlayerConnect Hook_PlayerConnect
```
Create a pre-processor symbol called "OnPlayerConnect". This may be the same as a callback name, but the two symbol sets are entirely separate. 

Thus, if the pre-processor symbol with this name DOESN'T exist and we try "#undef" it, the compiler will give an error; however, if the pre-processor symbol with this name DOES exist and we don't "#undef" it, the compiler will give a warning - that's why the "`_ALS_OnPlayerConnect`" symbol is required.

```pawn
ALS_FORWARD<PlayerConnect>
```
Again, this forwards the callback correctly, without needing to know anything about the parameters of the function and thus possibly getting them wrong.
```pawn
#undef ALS_PREFIX
```
At the end of your file using "y_als", this is required for technical reasons (otherwise you can end up with multiple callbacks with the same name). Note that if you miss the "#define ALS_PREFIX" line but not the "#include <YSI\y_als>" line, you will get the default prefix of "Mode", but you still need to "#undef" it.

## Justification
So why does this exist in the first place, as on first glance it does seem quite pointless? The basic reason is that the code generation can be automated, in fact that's pretty much the only reason. All you need to change between "OnPlayerConnect" and "OnPlayerCommandText" is the function name for much of the code. You don't need to worry about parameters, specifiers ("i" or "is"), brackets (should there be a "[]" here or not), or tags. Plus it is a little quicker once you get used to it. This autmation becomes even more apparent when useing the library to extend its own functionality.

## Print Example
To show some more advanced features of the library, let's develop a system to print out a callback and all its parameters. At first glance this seems easy:
```pawn
public OnPlayerCommandText(playerid)
{
	printf("OnPlayerCommandText(%d)", playerid);
	return 1;
}
```
And yes, that is easy, until you want to do it for ALL callbacks using (say) regular expressions. This may not be something you ever do, but is something done in YSI with surprising regularity; not just printing callbacks, but just doing SOMETHING for ALL callbacks, in those cases it is better to let the compiler worry about tags, brackets, and strings, etc.

For this we need to look in to the library a little deeper. Opening up y_als shows multiple lines like this:
```pawn
#define ALS_R_DialogResponse 1
#define ALS_DO_DialogResponse<%0> %0<DialogResponse,iiiis>(more:playerid,more:dialogid,more:response,more:listitem,end_string:inputtext[])
```

The "ALS_R_" line is very simply just the default return value for that callback (note again the lack of "On" in all these lines for symbol length limit reasons). Nothing more really needs to be said about that, it's "1" in all but two places (one of those being a YSI callback).

The "ALS_DO_" line is a little more complex and will be broken down further:
```pawn
#define ALS_DO_DialogResponse<%0>
```
This defines the "ALS_DO_" line for the "OnDialogResponse" callback. This macro is actually an internal one. The value of the parameter "%0" will become another macro to get called.
```pawn
%0<...>(...)
```
This calls the "%0" macro, passing all the data available about this callback. The "<>"s enclose callback information, the "()"s enclose the callback parameters.
```pawn
DialogResponse,iiiis
```
This is the name of the callback again (so that is gets passed to the macro, though I have just figured out another way of doing this so you don't need it twice, but since this is all internal data that's already written it doesn't really matter), followed by the specifier for "CallLocalFunction" and similar functions. Note no spaces.
```pawn
more:playerid
```
This is the first parameter, or more to the point this is not the last parameter. Because it is not the last, there are "more" to come and the parameter is marked as such.
```pawn
,more:dialogid,more:response,more:listitem
```
These are also not the last parameter so are prefixed by "more:" to indicate this fact.
```pawn
end_string:inputtext[]
```
This IS the last parameter, so uses "end", it is also a string so uses "string". Although this example doesn't show them all, the full set (with examples from real callbacks) is:

- `more:playerid` - A parameter called "playerid" that isn't the last in the list.
- `Float:fRotX` - A parameter called "fRotX" that isn't the last in the list and has a tag of "Float".
- `tag:Text:none` - A parameter called "none" that isn't the last in the list and has a different tag (but is still an integer) (never used).
- `string:password[]` - A parameter called "password" that isn't the last in the list and is a string.
- `end:playerid` - A parameter called "playerid" that is the last in the list.
- `end_Float:fZ` - A parameter called "fZ" that is the last in the list and has a tag of "Float".
- `end_tag:PlayerText:playertextid` - A parameter called "playertextid" that is the last in the list and has a tag of "PlayerText" (but is still an integer).
- `end_string:inputtext[]` - A parameter called "inputtext" that is the last in the list and is a string.
- `none:` - A callback with no parameters.

Again note the lack of spaces. Because these are internal macros that users never need to see (or understand, this was really a waste of time for you to read :p), the format is tightly controlled to make other code simpler.

Speaking of other code, the "print" macro will be an example of a "%0" macro above, so will have the following format:
```pawn
#define DO_PRINT<%0,%1>(%2)
```
Here "%0" is the callback's name, "%1" is the callback's specifier, and "%2" is a DESCRIPTION of the callback's parameters. Thus part of the code becomes:
```pawn
#define DO_PRINT<%0,%1>(%2) printf("On"#%0"()");
// OR
#define DO_PRINT<%0,%1>(%2) printf(#On%0"()");
```
Now those two lines LOOK similar, but they're NOT! The first one will just print "OnPlayerConnect" (for example) all the time. The second one will print the current callback's name AFTER ALS substitutions have been done, so it could print "OnPlayerConnect" if it is the first callback in a chain or something else such as "Mode_PlayerConnect" depending on what came before. Which one you want is up to you, but this discussion will stick to the second one for now as it can make debugging slightly simpler.

Now the format specifier (for example "%d %s") is required. However, it turns out that generating that data from the parameters themselves (due to the descriptions) is actually easier to do:
```pawn
#define ALS_PS_more:%0,         "%d, "ALS_PS_
#define ALS_PS_string:%0[],     "%s, "ALS_PS_
#define ALS_PS_Float:%0,        "%f, "ALS_PS_
#define ALS_PS_tag:%3:%0,       "%d, "ALS_PS_
#define ALS_PS_end:%0)          "%d"
#define ALS_PS_none:%0)
#define ALS_PS_end_string:%0[]) "%s"
#define ALS_PS_end_Float:%0)    "%f"
#define ALS_PS_end_tag:%3:%0)   "%d"
```
Using that, and a variant on the inbuilt "ALS_RS_" macro (which converts parameters to their "call" equivalents; unlike the "ALS_KS_" macro, which converts them to their "function declaration" equivalents) results in:
```pawn
#define ALS_R2_more:%0,         ,%0 ALS_R2_
#define ALS_R2_string:%0[],     ,((%0[0])?(%0):NULL) ALS_R2_
#define ALS_R2_Float:%0,        ,(_:%0) ALS_R2_
#define ALS_R2_tag:%3:%0,       ,(_:%0) ALS_R2_
#define ALS_R2_end:%0)          ,%0)
#define ALS_R2_none:)           )
#define ALS_R2_end_string:%0[]) ,((%0[0])?(%0):NULL))
#define ALS_R2_end_Float:%0)    ,(_:%0))
#define ALS_R2_end_tag:%3:%0)   ,(_:%0))

#define DO_PRINT<%0,%1>(%2) printf(#On%0"("ALS_PS_%2)")"ALS_R2_%2);
```
Here I should point out the extra ")", which is detected and removed by the "end:" and "none:" "ALS_PS_" macros.

And a final piece of boilerplate to make the macro easy to use:
```pawn
#define PRINT<%0> ALS_DO:DO_PRINT<%0>
```
Results in the following code to fully debug the "OnPlayerConnect" callback with parameters:
```pawn
PRINT<PlayerConnect>
```
And have it just work. Same for any other callback. For reference, this generates the following code using "-l":
```pawn
printf(#Hook_OnPlayerConnect            "(""%d"")",playerid);
And in "OnDialogResponse":

printf(#S@@_OnDialogResponse           "(""%d, ""%d, ""%d, ""%d, ""%s"")",playerid dialogid,response,listitem,((inputtext[0])?(inputtext):NULL));
```
Here you can see the effect of the ALS expansion discussed earlier to give the final names, not the typed names. You can also see all the parameters nicely (and safely) printed correctly.

There is also the "q" macro:
```pawn
#define q,ALS_RS_none:) )
```
This is a macro that is used so:
```pawn
#%1#q,ALS_RS_%2)
```
Here "%1" is obviously the function specifier, followed by a comma, then followed by the parameters. However, if there are no parameters then the comma should not be there and the special "q" specifier (which is ignored normally) removes it. Unfortunately as specifiers were not used in the print example, the "ALS_R2_" macro had to do a similar thing.
