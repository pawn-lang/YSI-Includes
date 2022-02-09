# Quick Start

Create new VM registers and use them via `LCTRL` and `SCTRL`.  Only registers above `255` are called
via this method.  `XCTRL 0` - `XCTRL 255` are reserved for the VM and plugins (e.g. crashdetect uses
`254` and `255`).  As with normal register reads/writes `pri` and `alt` are preserved across `SCTRL`
and `alt` is preserved across `LCTRL` (`pri` isn't - it is the return value).

```pawn
#include <YSI_Coding\y_ctrl>

new gVar = 5;

// Declare the `lctrl` handler.
@lctrl(1000) lctrl_1000(pri, alt)
{
	return gVar;
}

// Declare the `sctrl` handler.
@sctrl(1000) sctrl_1000(pri, alt)
{
	gVar = pri * 2;
}

main()
{
	new a = 0;
	#emit CONST.pri        100
	#emit SCTRL            1000
	#emit LCTRL            1000
	#emit STOR.S.pri       a
	printf("a = %d", a);
}
```

