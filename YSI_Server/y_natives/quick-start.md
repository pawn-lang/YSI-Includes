## Introduction

This include finally allows you to declare natives for components, then detect whether they exist, and if not provide a fallback or other response.  Just using `native` will cause a mode to fail to load when it is missing a component (in the default SA:MP server this gives very few details on exactly what is missing, but this is improved by both plugins and open.mp).  This include instead bypasses that and allows code to run, and gives programmers more control over what to do in the case of a missing (possibly required) component.

### Example 1: A required component

```pawn
#include <YSI_Server\y_natives>

@native("CreateDynamicObject") STREAMER_TAG_OBJECT:TRY_CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0);

main()
{
	TRY_CreateDynamicObject(1337, 0.0, 0.0, 10.0, 0.0, 0.0, 0.0);
}
```

Using `@native()` instead of `native` we can declare the function that needs a component (or legacy plugin), but the mode will start even if that component isn't loaded, and instead a message will be printed when you try to call the native function.  You can improve the message by default by specifying which component you expect the function to be defined by:

```pawn
#include <YSI_Server\y_natives>

@native("CreateDynamicObject", .requires = "streamer plugin") STREAMER_TAG_OBJECT:TRY_CreateDynamicObject(...);

main()
{
	TRY_CreateDynamicObject(1337, 0.0, 0.0, 10.0, 0.0, 0.0, 0.0);
}
```

The true ("external") name of the native is the first parameter of the `@native` decorator, then the called function should have a slightly different name; the "internal" name, here `TRY_CreateDynamicObject`.  Normal `native` syntax for the same would be:

```pawn
native STREAMER_TAG_OBJECT:TRY_CreateDynamicObject(/* params */) = CreateDynamicObject;
```

I went back and forth on using that syntax or the chosen decorator syntax, but since this is a decorator I think it is best to stick to the [well documented decorator syntax](https://github.com/pawn-lang/YSI-Includes/blob/5.x/annotations.md).

### Example 2: Checking first

The code from Example 1 will simply print a message to the console if the native function can't be found.  You can use `Server_HasNative` to explicitly check first and give some other response:

```pawn
#include <YSI_Server\y_natives>

@native("bcrypt_verify") bool:BCrypt_Check1(extra, const callback[], const password[], const hash[]);
@native("bcrypt_check") bool:BCrypt_Check2(const password[], const hash[], const callback[], const format[], ...);

BCryptCheck(const callback[], const password[], const hash[], extra)
{
	if (Server_HasNative("bcrypt_verify"))
	{
		BCrypt_Check1(extra, callback, password, hash);
	}
	else if (Server_HasNative("bcrypt_check"))
	{
		BCrypt_Check2(password, hash, callback, "i", extra);
	}
	else
	{
		printf("Neither BCrypt plugin found.  Please install one.")
	}
}
```

### Example 3: Fallbacks

Alternatively, instead of printing a message or explicitly checking for some functions, you could provide a fallback instead (this callback could do nothing more than print an error, as in previous examples):

```pawn
#include <YSI_Server\y_natives>

@native("frename") FRename(const oldname[], const newname[])
{
	new
		File:i = fopen(oldname, io_read),
		File:o = fopen(newname, io_write),
		str[64],
		len;
	if (!i)
	{
		if (o) fclose(o);
		return 0;
	}
	if (!o)
	{
		if (i) fclose(i);
		return 0;
	}
	while ((len = fblockread(i, str)))
	{
		fblockwrite(o, str, len);
	}
	fclose(i);
	fclose(o);
	fremove(oldname);
	return 1;
}
```

### Fallbacks Vs. Messages

If you provide no fallback a fatal error will be printed in the console (a fatal error in YSI also halts the script, because what else can be done if a function you are trying to use doesn't exist?)  A less fatal method would be to provide a fallback function that does nothing but print an error:

```pawn
#include <YSI_Server\y_natives>

@native("frename") Float:floatmod(Float:numerator, Float:denominator)
{
	#pragma unused numerator, denominator
	printf("No `floatmod` implementation found.");
	// This is trivially easy to implement in pawn, but that's not the example.
	return 0.0;
}
```

This message will be printed every time the function is called, as opposed to the default message which is only printed the first time.  You can also force the default message to print even when there is a fallback implementation:


```pawn
#include <YSI_Server\y_natives>

@native("frename", .print = true) Float:floatmod(Float:numerator, Float:denominator)
{
	// See, I told you.
	return floatfract(numerator / denominator) * denominator;
}
```

In that case only a warning will be used instead of a fatal error.  As documented elsewhere `.print = true` is standard pawn syntax and allows for giving just one optional argument and leaving the rest as default.  This is common in decorators.






