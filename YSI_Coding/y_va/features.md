# Features

## Pass Extra Parameters.

There is no reason that `___` is the only given parameter.

```pawn
PrintMore(const str[], ...)
{
	printf(str, 5, 6, ___(1), 7, 8);
}
```

## Skip Parameters.

There's also no reason why all the variable arguments must be passed on.

```pawn
PrintLess(...)
{
	if (numargs() < 5)
	{
		return;
	}
	printf("%d %d %d", ___(2));
}
```

## Reference Parameters.

`___` always passes things on by reference.  This will not work:

```pawn
NormalArg(a, b)
{
	printf("%d", ___(0));
}
```

But because both `...` and `&` are pass-by-reference, this will work:

```pawn
RefArg(&a, &b)
{
	printf("%d", ___(0));
}
```

## `va_args<>` and `va_start<>`

For backwards-compatibility with older versions of y_va (designed to look like C vararg functions), these are aliases for `...` and `___`:

```pawn
SendFormattedMessage1(playerid, colour, const msg[], ...)
{
	new str[128]
	format(str, sizeof (str), msg, ___(3));
}

SendFormattedMessage2(playerid, colour, const msg[], va_args<>)
{
	new str[128]
	va_format(str, sizeof (str), msg, va_start<3>);
}

```

Those two pieces of code are entirely equivalent - `va_format` is also a alias to `format` for compatibility reasons; with one exception...

## `GLOBAL_TAG_TYPES`

Technically, `va_args<>` is not `...`, but `GLOBAL_TAG_TYPES:...`.  The difference being that the latter accepts many tags, not just one.  The common way of writing this is `{Float, _}:...`, but this only accepts two tags - `Float` and `_` (integer, no tag).  `GLOBAL_TAG_TYPES` is defined as `{_,Language,Bit,Text,Menu,Style,XML,Bintree,Group,Timer,File,Float,Text3D,CUSTOM_TAG_TYPES}`, i.e. a lot of common tags.

## `CUSTOM_TAG_TYPES`

If you want to add more accepted tags to functions - especially internal YSI functions, simply define them in `CUSTOM_TAG_TYPES`:

```pawn
#define CUSTOM_TAG_TYPES Int,Hex
#include <YSI_Coding\y_va>
```

Make sure the define is before any YSI library.

## Extended Default Functions

Many of the default functions, such as `SendClientMessage`, and some common plugin functions, have been extended using *y_va* to accept variable parameters for formatting.  The full list is:

* `PlayerText:CreatePlayerTextDraw(playerid, Float:x, Float:y, const fmat[], GLOBAL_TAG_TYPES:...);`
* `SetPlayerChatBubble(playerid, const fmat[], colour, Float:drawDistance, expireTime, GLOBAL_TAG_TYPES:...);`
* `Text:TextDrawCreate(Float:x, Float:y, const fmat[], GLOBAL_TAG_TYPES:...);`
* `bool:TextDrawSetString(Text:text, const fmat[], GLOBAL_TAG_TYPES:...);`
* `bool:PlayerTextDrawSetString(playerid, PlayerText:text, const fmat[], GLOBAL_TAG_TYPES:...);`
* `bool:SendClientMessage(playerid, colour, const fmat[], GLOBAL_TAG_TYPES:...);`
* `bool:SendClientMessageToAll(colour, const fmat[], GLOBAL_TAG_TYPES:...);`
* `bool:SendPlayerMessageToPlayer(playerid, senderid, const fmat[], GLOBAL_TAG_TYPES:...);`
* `bool:SendPlayerMessageToAll(senderid, const fmat[], GLOBAL_TAG_TYPES:...);`
* `bool:GameTextForPlayer(playerid, const fmat[], time, style, GLOBAL_TAG_TYPES:...);`
* `bool:GameTextForAll(const fmat[], time, style, GLOBAL_TAG_TYPES:...);`
* `fwrite(File:fhnd, const fmat[], GLOBAL_TAG_TYPES:...);` AKA `fprintf`.
* `bool:SendRconCommand(const fmat[], GLOBAL_TAG_TYPES:...);`
* `bool:SetGameModeText(const fmat[], GLOBAL_TAG_TYPES:...);`
* `DBResult:DBQuery(DB:db, const fmat[], GLOBAL_TAG_TYPES:...);`
* `bool:ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE:style, const title[], const fmat[], const button1[], const button2[], GLOBAL_TAG_TYPES:...);`
* `Menu:CreateMenu(const fmat[], columns, Float:x, Float:y, Float:col1width, Float:col2width = 0.0, GLOBAL_TAG_TYPES:...);`
* `AddMenuItem(Menu:menuid, column, const fmat[], GLOBAL_TAG_TYPES:...);`
* `bool:SetMenuColumnHeader(Menu:menuid, column, const fmat[], GLOBAL_TAG_TYPES:...);`
* `bool:SetObjectMaterialText(objectid, const fmat[], materialIndex = 0, OBJECT_MATERIAL_SIZE:materialSize = OBJECT_MATERIAL_SIZE:90, const fontFace[] = "Arial", fontSize = 24, bool:bold = true, fontColour = 0xFFFFFFFF, backgroundColour = 0, OBJECT_MATERIAL_TEXT_ALIGN:textalignment = OBJECT_MATERIAL_TEXT_ALIGN:0, GLOBAL_TAG_TYPES:...);`
* `bool:SetPlayerObjectMaterialText(playerid, objectid, const fmat[], materialIndex = 0, OBJECT_MATERIAL_SIZE:materialSize = OBJECT_MATERIAL_SIZE:90, const fontFace[] = "Arial", fontSize = 24, bool:bold = true, fontColour = 0xFFFFFFFF, backgroundColour = 0, OBJECT_MATERIAL_TEXT_ALIGN:textalignment = OBJECT_MATERIAL_TEXT_ALIGN:0, GLOBAL_TAG_TYPES:...);`
* `Text3D:Create3DTextLabel(const fmat[], colour, Float:x, Float:y, Float:z, Float:drawDistance, virtualWorld, bool:testLOS = false, GLOBAL_TAG_TYPES:...);`
* `bool:Update3DTextLabelText(Text3D:textid, colour, const fmat[], GLOBAL_TAG_TYPES:...);`
* `PlayerText3D:CreatePlayer3DTextLabel(playerid, const fmat[], colour, Float:x, Float:y, Float:z, Float:drawDistance, parentPlayerid = INVALID_PLAYER_ID, parentVehicleid = INVALID_VEHICLE_ID, bool:testLOS = false, GLOBAL_TAG_TYPES:...);`
* `bool:UpdatePlayer3DTextLabelText(playerid, PlayerText3D:textid, colour, const fmat[], GLOBAL_TAG_TYPES:...);`
* `bool:SetSVarString(const svar[], const fmat[], GLOBAL_TAG_TYPES:...);`
* `bool:SetPVarString(playerid, const svar[], const fmat[], GLOBAL_TAG_TYPES:...);`
* `bool:AddServerRule(const name[], const fmat[], E_SERVER_RULE_FLAGS:flags = E_SERVER_RULE_FLAGS:4, GLOBAL_TAG_TYPES:...);`
* `bool:SetServerRule(const name[], const fmat[], GLOBAL_TAG_TYPES:...);`
* `bool:TextDrawSetStringForPlayer(Text:text, playerid, const fmat[], GLOBAL_TAG_TYPES:...);`;

If you don't want these redefinitions you can use the following define:

```pawn
#define YSI_NO_AUTO_VA
```

Before including YSI, then use the `va_` prefixed versions of the function names instead.  For example `va_SendClientMessage` for a formatting version of `SendClientMessage`.  These functions also short-circuit, so if there are no parameters to be formatted then `format` isn't called at all.

