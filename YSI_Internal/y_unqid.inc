// y_textid

enum E_UNIQUE_ID
{
	E_UNIQUE_EXTERNAL,
	E_UNIQUE_REVISION,
	E_UNIQUE_INTERNAL,
	E_UNIQUE_FLAGS
	// Search using a hash map with 256 entries.
	E_UNIQUE_HASH_NEXT,
	// Combine multiple items in to a single initial ID.
	E_UNIQUE_LINK_NEXT
}

#define UniqueID:%0<%1> %0@ENTRIES[256],%0@IDS[%1][E_UNIQUE_ID],%0@EMPTY,%0@NEXT

stock _Unique_Lookup(entries[256], ids[][E_UNIQUE_ID], lookup, &id, &rev, &flags)
{
	new
		cur = entries[lookup & 0xFF]; // Get entry point.
	while (cur != -1)
	{
		if (ids[cur][E_UNIQUE_EXTERNAL] == lookup)
		{
			id = ids[cur][E_UNIQUE_INTERNAL],
			rev = ids[cur][E_UNIQUE_REVISION],
			flags = ids[cur][E_UNIQUE_FLAGS];
			if (ids[cur][E_UNIQUE_LINK_NEXT] != -1) return -1; // More data.
			else return 1;
		}
		cur = ids[cur][E_UNIQUE_HASH_NEXT];
	}
	return 0;
}
#define Unique_Lookup(%0, _Unique_Lookup(%0@ENTRIES,%0@IDS,

stock _Unique_InUse(entries[256], ids[][E_UNIQUE_ID], lookup)
{
	new
		cur = entries[lookup & 0xFF]; // Get entry point.
	while (cur != -1)
	{
		if (ids[cur][E_UNIQUE_EXTERNAL] == lookup) return 1;
		cur = ids[cur][E_UNIQUE_HASH_NEXT];
	}
	return 0;
}
#define Unique_InUse(%0, _Unique_InUse(%0@ENTRIES,%0@IDS,

stock _Unique_Assign(entries[256], ids[][E_UNIQUE_ID], &free, &next)
{
	if (free == -1) return 0;
	do
	{
		if (++next == 0) ++next;
	}
	while (_Unique_InUse(entries, ids, next));
	new
		tmp = ids[free][E_UNIQUE_HASH_NEXT];
	return
		// Copy the data.
		ids[free][E_UNIQUE_EXTERNAL] = next,
		++ids[free][E_UNIQUE_REVISION],
		// Allocate this in to the hash map.
		ids[free][E_UNIQUE_HASH_NEXT] = entries[next & 0xFF],
		entries[next & 0xFF] = free,
		free = tmp,
		// Return the ID.
		next;
}









