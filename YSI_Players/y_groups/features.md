## `...`

Many functions in this documentation use the convention `...` in their names.  This is the same syntax as is used in the code itself, and means "any library".  For example, `Group_Set...Default` represents `Group_SetCommandDefault`, `Group_SetRaceDefault`, `Group_SetClassDefault`, and many more.  There are variants of every `...` function created for every library that uses group functions.  Thus you can always substitute `...` with whichever library your defining group permissions for.

## Global

The global group is the default group that everybody and everything is in.  It is a pre-defined group stored in `GROUP_GLOBAL`, thus all group functions will accept that as a group parameter.  Additionally, there are `Global` variants of many functions, such as `Group_Set...New` becoming `Group_SetGlobal...New`.  When you create a new server item managed by groups, it is automatically added to the global group.  When anyone joins the server, they are automatically added to the global group.  This means that by default everyone can see/use/do everything.

If you don't want something usable by the global group, just remove it:

```pawn
Group_SetGlobal(entityID, UNDEF); // Previously `false`.
```

If you don't want anything from a library to be usable by default (for example, disable all commands by default), use:

```pawn
Group_SetGlobalDefault(UNDEF);
```

Or, as with all groups:

```pawn
Group_SetDefault(GROUP_GLOBAL, UNDEF);
```

## `ALLOW`/`DENY`/`UNDEF`

There are three states that an entity can be in a group:

* `ALLOW` means that anyone in the group can use it (default for the global group).

* `UNDEF` means that the group doesn't have any effect on this entity.  Being in this group doesn't allow of prevent you from doing something (default for created groups).  If you are only in `UNDEF` groups (including the global group) you by default can't use an entity.  If you are in one `UNDEF` group and one `ALLOW` group, the `ALLOW` will be used and enable the entity for the player.

* `DENY` means that anyone in this group is absolutely NOT allowed to use an entity.  This overrides `ALLOW`, so if you're in a group with `ALLOW` set on an area, and another group with `DENY` set on the same area, you can't use the area.  A good example of this is a `gaoled` group, who can't use most commands:

```pawn
final gGaoled = Group_Create("gaoled");

Group_SetCommandDefault(gGaoled, DENY);

// Override the default for just this one command.
Group_SetCommand(gGaoled, YCMD:appeal, ALLOW);

// /gaol
YCMD:gaol()
{
	Group_SetPlayer(gGaoled, badPlayer, true); // Can no longer use commands.
}
```

Note that functions such as `Group_Set...` used to use `true`/`false`.  That old code will still work, but will now give a tag warning, since the input has changed.

## Check Permissions

`Group_Get...` will return the `ALLOW`/`DENY`/`UNDEF` value for an entity, but is deprecated because this used to return `bool`.  Old code will probably still work, until you start using the new `DENY` value (`ALLOW` is the old `true` and `UNDEF` is the old `false`).  Instead, use `Group_...Allowed`, which returns true on `ALLOW` or `Group_...Denied`, which returns true on `DENY`.  If they're both false, it's `UNDEF`:

```pawn
if (Group_PropertyAllowed(group, property))
{
	// This group allows it, but a player can still only use it if none of their
	// groups `DENY` it, and at least one `ALLOW`s it.
}
```
