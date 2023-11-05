## Introduction

This include finally allows you to declare natives for components, then detect whether they exist, and if not provide a fallback or other response.  Just using `native` will cause a mode to fail to load when it is missing a component (with very few details on what component is needed).  This include instead bypasses that and allows code to run, and gives programmers more control over what to do in the case of a missing (possibly required) component.

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

The true ("external") name of the native is the first parameter of the `@native` decorator, then the called function should have a slightly different name (here `TRY_CreateDynamicObject`).

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

