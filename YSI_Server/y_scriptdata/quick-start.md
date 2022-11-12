# Quick Start

```pawn
#include <YSI_Server\y_scriptdata>

public OnScriptInit()
{
	printf("%d", Script_IsFilterScript());
	printf("%d", Script_GetCompilerVersion());
	printf("%d", Script_CacheLoaded());
}
```

