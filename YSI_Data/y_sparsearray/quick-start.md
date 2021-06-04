# y_sparsearray

```pawn
#include <YSI_Data\y_sparsearray>

// Create the sparse array.
static SparseArray:gArrests<>;

public OnPlayerDisconnect(playerid, reason)
{
	// Remove this player from the array.
	Sparse_UnSet(gArrests, playerid);
}

MakeArrest(playerid)
{
	// Update their arrest count.
	new arrests = Sparse_Get(gArrests, playerid);
	if (arrests == cellmin)
	{
		// Default value.
		Sparse_Set(gArrests, playerid, 1);
	}
	else
	{
		Sparse_Set(gArrests, playerid, arrests + 1);
	}
}

bool:HasMadeArrests(playerid)
{
	// Has this player ever made any arrests?
	return Sparse_Contains(gArrests, playerid);
}
```

