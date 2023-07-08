# Adding a new ownership type.

By default players, vehicles, and objects (both global and per-player) can "own" functions.  For example:

```pawn
new vehicleid = CreateVehicle(400, 0.0, 0.0, 3.0, 0.0, -1, -1, 10000);
inline const Repair()
{
	SetVehicleHealth(vehicleid, 1000.0);
}
Timer_CreateCallback(EBC(vehicleid, using inline Repair), 60000, 1);
```

That code will repair the vehicle after one minute, but only if the vehicle hasn't been destroyed in the interim.  Even if a new vehicle is created with the same ID before the time elapses, this function will still not be called.

Side note: You can't pass parameters to inline timer callbacks because closures exist, so there's no need to.

`y_ebc` hooks `DestroyVehicle`, so it knows how to reset all callbacks when a vehicle is destroyed.  If you want to add the same ownership ability to say streamer objects you need to do the same hooking.

First, due to a bug in old compilers you need to declare the tag (although YSI already declares the streamer tags, so you don't need to in this specific example):

```pawn
__COMPILER_TAG_DATA(DynamicObject, 0); // `0` is the default invalid value for this tag.
```

y_ebc strictly works on tags, so even if you don't use them in the streamer you still need to use them here.  To assign ownership do:

```pawn
new objectid = CreateDynamicObject(1337, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0);
inline const Move()
{
	SetDynamicObjectPos(objectid, 10.0, 10.0, 3.0);
}
Timer_CreateCallback(EBC(DynamicObject:objectid, using inline Move), 60000, 1);
```

This will NOT stop the callback if the object is destroyed because we haven't taught y_ebc how dynamic objects are destroyed.  It is very easy though - just hook the function:

```pawn
hook native DestroyDynamicObject(STREAMER_TAG_OBJECT:objectid)
{
	EBC_Deactivate(objectid, tagof(DynamicObject:));
	return continue(objectid);
}
```

If you have streamer tags enabled (which you should):

```pawn
hook native DestroyDynamicObject(DynamicObject:objectid)
{
	EBC_Deactivate(objectid);
	return continue(objectid);
}
```

The tag is automatic.

