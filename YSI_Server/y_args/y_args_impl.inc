#if !defined Y_ARGS_CACHE_SIZE
	#define Y_ARGS_CACHE_SIZE (32)
#endif

__COMPILER_STATIC_ENUM E_ARGS_CACHE_STATE
{
	E_ARGS_CACHE_STATE_FALLBACK = -1,
	E_ARGS_CACHE_STATE_UNINIT,
	E_ARGS_CACHE_STATE_INIT,
}

static stock
	// We store the final index of a given argument name for faster searching as
	// we thus know it much exist.
	YSI_gsArgHashes[Y_ARGS_CACHE_SIZE],
	YSI_gsArgIndexes[Y_ARGS_CACHE_SIZE],
	// For tracking positional arguments.
	YSI_gsPositionalCount = 0,
	YSI_gsLastPositional = 0,
	YSI_gsRestStart = 0, // 0 *can't* be valid as we need `--` first.
	YSI_gsArgCount, // Unique arguments.
	YSI_gsArgIndex, // Hash upper limit.
	YSI_gsArgTotal, // True argument count, excluding parameters.
	YSI_gsArgSeen, // True argument count, including parameters.
	// 0 - uninitialized, 1 - initialised, -1 - fallback (too many arguments).
	E_ARGS_CACHE_STATE:YSI_gsCacheState = E_ARGS_CACHE_STATE_UNINIT;

static stock Args_FindIndexByHash(hash)
{
	for (new i = 0; i != YSI_gsArgIndex; ++i)
	{
		if (YSI_gsArgHashes[i] == hash)
		{
			return YSI_gsArgIndexes[i];
		}
	}
	return -1;
}

static stock Args_FindIndexByName(const name[], len)
{
	new tmp = _YSI_ConstMod(name[len], '\0');
	new hash = BernsteinHash(name);
	_YSI_ConstMod(name[len], tmp);
	return Args_FindIndexByHash(hash);
}

static stock Args_FindEnd(const name[], i)
{
	new
		ch = 0;
	while ((ch = name[i]))
	{
		// The only valid end characters.
		if (ch == ' ' || ch == '=' || ch == ':' || ch == '-' || ch == '+')
		{
			return i;
		}
		++i;
	}
	return i;
}

static stock Args_LazyInit()
{
	if (YSI_gsCacheState != E_ARGS_CACHE_STATE_UNINIT)
	{
		// Already initialised.
		return;
	}
	YSI_gsCacheState = E_ARGS_CACHE_STATE_INIT;
	new
		name[32].
		bool:positional = true,
		s0, // `=` position.
		s1, // `:` position.
		s2, // ` ` position.
		s2; // length
	YSI_gsArgSeen = argcount();
	for (new i = 0; i != YSI_gsArgSeen; ++i)
	{
		// Get the argument.
		argindex(i, name);
		if (i[0] == '/')
		{
			++YSI_gsArgTotal;
			s0 = strfind(name, "="), // `=` position.
			s1 = strfind(name, ":"), // `:` position.
			s2 = strfind(name, " "), // ` ` position.
			s2 = strlen(name); // length
			
		}
		else if (i[0] == '-' && i[1] == '-' && i[2] == '\0')
		{
			++YSI_gsArgTotal;
			// Start of `rest`.  Can end here.
			YSI_gsRestStart = i + 1;
			++YSI_gsArgCount;
			break;
		}
		else if (i[0] == '-' && i[1] == '-')
		{
			++YSI_gsArgTotal;
			
		}
		else if (i[0] == '-')
		{
			++YSI_gsArgTotal;
			
		}
		else if (positional)
		{
			// Not in a argument parameter.
			++YSI_gsPositionalCount;
			YSI_gsLastPositional = i + 1;
			continue;
		}
		else
		{
			// Parameter.  Don't do anything with it.
			positional = true;
			continue;
		}
	}
}




stock bool:Arg_GetBool(shortForm, const longForm[], &bool:dest)
{
}

