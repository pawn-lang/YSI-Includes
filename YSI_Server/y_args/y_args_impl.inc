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

static stock Args_LazyInit()
{
	if (YSI_gsCacheState != E_ARGS_CACHE_STATE_UNINIT)
	{
		// Already initialised.
		return;
	}
	YSI_gsCacheState = E_ARGS_CACHE_STATE_INIT;
	new name[32];
	new bool:rest = false;
	new bool:positional = true;
	// Go backwards.  Makes tracking the final copy of an argument easier.
	for (new i = argcount(); --i; )
	{
		// Get the argument.
		argindex(i, name);
		if (i[0] == '/')
		{
			
		}
		else if (i[0] == '-' && i[1] == '-' && i[2] == '\0')
		{
			// Reset everything - everything to now was 
		}
		else if (i[0] == '-' && i[1] == '-')
		{
			
		}
		else if (i[0] == '-')
		{
			
		}
		if (YSI_gsArgIndex < Y_ARGS_CACHE_SIZE)
	}
	
	
}




stock bool:Arg_GetBool(shortForm, const longForm[], &bool:dest)
{
}

