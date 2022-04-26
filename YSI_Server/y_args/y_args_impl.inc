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

static stock Args_ScanAndHash(const name[], i, &hash)
{
	hash = 5381;
	new
		ch = 0;
	while ((ch = name[i]))
	{
		switch (ch)
		{
		// The only valid end characters.
		case ' ', ':', '=', '-', '+':
			return i;
		}
		hash = hash * 33 ^ ch,
		++i;
	}
	return i;
}

static stock Args_TryAdd(hash, index)
{
	new i;
	while (i != YSI_gsArgIndex)
	{
		if (YSI_gsArgHashes[i] == hash)
		{
			break;
		}
		++i;
	}
	if (i == YSI_gsArgIndex)
	{
		// A new unique argument.
		++YSI_gsArgCount;
		if (YSI_gsArgIndex == Y_ARGS_CACHE_SIZE)
		{
			// Too many unique arguments.
			YSI_gsCacheState = E_ARGS_CACHE_STATE_FALLBACK;
		}
		else
		{
			YSI_gsArgHashes[YSI_gsArgIndex] = hash,
			YSI_gsArgIndexes[YSI_gsArgIndex] = index,
			++YSI_gsArgIndex;
		}
	}
	else
	{
		YSI_gsArgIndexes[i] = index;
	}
}

_Y_CORE_STATIC stock Args_LazyInit()
{
	if (YSI_gsCacheState != E_ARGS_CACHE_STATE_UNINIT)
	{
		// Already initialised.
		return;
	}
	YSI_gsCacheState = E_ARGS_CACHE_STATE_INIT;
	new
		name[32],
		bool:positional = true,
		hash,
		end;
	YSI_gsArgSeen = argcount();
	for (new i = 0; i != YSI_gsArgSeen; ++i)
	{
		// Get the argument.
		argindex(i, name);
		if (name[0] == '/')
		{
			++YSI_gsArgTotal,
			end = Args_ScanAndHash(name, 1, hash),
			// If the argument ended there (may) be a following parameter.
			positional = name[end] != '\0',
			Args_TryAdd(hash, i);
			P:6("Args_LazyInit: Argument: /%.*s, length: %d, hash: %d", end - 1, name[1], end - 1, hash);
		}
		else if (name[0] == '-' && name[1] == '-' && name[2] == '\0')
		{
			++YSI_gsArgTotal;
			// Start of `rest`.  Can end here.
			YSI_gsRestStart = i + 1;
			++YSI_gsArgCount;
			P:6("Args_LazyInit: Rest: %d", i + 1);
			break;
		}
		else if (name[0] == '-' && name[1] == '-')
		{
			++YSI_gsArgTotal,
			end = Args_ScanAndHash(name, 2, hash),
			// If the argument ended there (may) be a following parameter.
			positional = name[end] != '\0',
			Args_TryAdd(hash, i);
			P:6("Args_LazyInit: Argument: --%.*s, length: %d, hash: %d", end - 2, name[2], end - 2, hash);
		}
		else if (name[0] == '-')
		{
			positional = true;
			for (end = 1; (hash = 5381 * 33 ^ name[end++]); )
			{
				switch (hash)
				{
				case 5381 * 33 ^ '\0',
					 5381 * 33 ^ ' ',
					 5381 * 33 ^ '=',
					 5381 * 33 ^ '-',
					 5381 * 33 ^ '+':
				{
					break;
				}
				case 5381 * 33 ^ ':':
				{
					// Windows seems to treat this as an argument separator
					// even without a space.  Thus `-a:6` appears as two
					// separate `argv` entries.
					positional = false;
					break;
				}
				}
				Args_TryAdd(hash, i);
				P:6("Args_LazyInit: Argument: -%c, hash: %d", name[end - 1], hash);
			}
		}
		else if (positional)
		{
			// Not in a argument parameter.
			++YSI_gsPositionalCount;
			YSI_gsLastPositional = i;
			P:6("Args_LazyInit: Positional: %s", name);
		}
		else
		{
			// Parameter.  Don't do anything with it.
			positional = true;
			P:6("Args_LazyInit: Parameter: %s", name);
		}
	}
}

_Y_CORE_STATIC stock Args_CheckName(short, const long[], const name[], offset, len)
{
	if (name[offset] == '\0')
	{
	}
	else if (short == name[offset])
	{
		switch (name[offset + 1])
		{
		case '\0', ' ', ':', '=', '-', '+':
			return offset + 1;
		}
	}
	else if (strcmp(name[offset], long, false, len) == 0)
	{
		switch (name[offset + len])
		{
		case '\0', ' ', ':', '=', '-', '+':
			return offset + len;
		}
	}
	// Failure.
	return 0;
}

_Y_CORE_STATIC stock bool:Args_GetStringImpl(short, const long[], output[], size)
{
	new
		// Inline single character hash.
		idxLong = Args_FindIndexByHash(BernsteinHash(long)),
		idxShort = Args_FindIndexByHash(5381 * 33 ^ short),
		arg[YSI_MAX_STRING + 32];
	output[0] = '\0';
	if (idxShort > idxLong)
	{
		// Get the short-form parameter because it is LAST.  Also true when
		// `idxLong == -1`
		// We need to retrieve the argument, then check if it has `=`, `:`, `-`,
		// `+`, or other arguments together.
		argindex(idxShort, arg);
		P:5("Args_GetStringImpl: short %d = %s", idxShort, arg);
		switch (arg[2])
		{
		case ':':
		{
			if (idxShort + 1 < YSI_gsArgSeen)
			{
				argindex(idxShort + 1, output, size);
			}
		}
		case '=':
		{
			// We might miss three characters.
			strcat(output, arg[2], size);
		}
		case '-':
		{
			strcat(output, "-", size);
		}
		case '+':
		{
			strcat(output, "+", size);
		}
		}
		return true;
	}
	if (idxLong > idxShort)
	{
		// Get the long-form parameter because it is LAST.  Also true when
		// `idxShort == -1`
		argindex(idxLong, arg),
		idxShort = strlen(long) + (arg[0] == '/' ? 1 : 2);
		P:5("Args_GetStringImpl: long %d = %s, %d = %d ('%c')", idxLong, arg, idxShort, arg[idxShort], arg[idxShort]);
		switch (arg[idxShort])
		{
		case ':':
		{
			if (idxLong + 1 < YSI_gsArgSeen)
			{
				argindex(idxLong + 1, output, size);
			}
		}
		case '=', ' ':
		{
			strcat(output, arg[idxShort + 1], size);
		}
		case '-':
		{
			strcat(output, "-", size);
		}
		case '+':
		{
			strcat(output, "+", size);
		}
		case '\0':
		{
			if (idxLong + 1 < YSI_gsArgSeen)
			{
				argindex(idxLong + 1, output, size);
				P:5("Args_GetStringImpl: %s", output);
				if (output[0] == '-' || output[0] == '/')
				{
					output[0] = '\0';
				}
			}
		}
		}
		return true;
	}
	// Else they are the same, which can only happen when neither exists.
	return false;
}

_Y_CORE_STATIC stock bool:Args_GetStringFallback(short, const long[], output[], size)
{
	new
		len = strlen(long),
		name[YSI_MAX_STRING + 32],
		bool:found = false,
		bool:parameter = false,
		ch,
		end;
	output[0] = '\0';
	for (new i = 0; i != YSI_gsArgSeen; ++i)
	{
		// Get the argument.
		argindex(i, name);
		if (name[0] == '/')
		{
			parameter = false;
			if ((end = Args_CheckName(short, long, name, 1, len)))
			{
				found = true;
				switch (name[end])
				{
				case '\0':
				{
					output[0] = '\0',
					parameter = true;
				}
				case ':':
				{
					output[0] = '\0',
					strcat(output, name[end + 1], size);
					parameter = true;
				}
				case ' ', '=':
				{
					output[0] = '\0',
					strcat(output, name[end + 1], size);
				}
				case '-':
				{
					output[0] = '\0',
					strcat(output, "-", size);
				}
				case '+':
				{
					output[0] = '\0',
					strcat(output, "+", size);
				}
				}
			}
		}
		else if (name[0] == '-' && name[1] == '-' && name[2] == '\0')
		{
			// Got to `rest`.  Did we find the argument previously?
			break;
		}
		else if (name[0] == '-' && name[1] == '-')
		{
			parameter = false;
			if ((end = Args_CheckName('\0', long, name, 2, len)))
			{
				found = true;
				switch (name[end])
				{
				case '\0':
				{
					output[0] = '\0',
					parameter = true;
				}
				case ':':
				{
					output[0] = '\0',
					strcat(output, name[end + 1], size);
					parameter = true;
				}
				case ' ', '=':
				{
					output[0] = '\0',
					strcat(output, name[end + 1], size);
				}
				case '-':
				{
					output[0] = '\0',
					strcat(output, "-", size);
				}
				case '+':
				{
					output[0] = '\0',
					strcat(output, "+", size);
				}
				}
			}
		}
		else if (name[0] == '-')
		{
			parameter = false;
			end = 0;
			while ((ch = name[++end]))
			{
				if (ch == short)
				{
					output[0] = '\0',
					parameter = true;
				}
				else switch (ch)
				{
				case '\0':
				{
					if (parameter)
					{
						found = true;
						parameter = false;
					}
					break;
				}
				case ':':
				{
					if (parameter)
					{
						found = true;
						if (end == 2)
						{
							output[0] = '\0',
							strcat(output, name[3], size);
						}
						// Weird windows behaviour.  Don't reset `parameter`.
					}
					break;
				}
				case ' ', '=':
				{
					if (parameter)
					{
						found = true;
						if (end == 2)
						{
							output[0] = '\0',
							strcat(output, name[3], size);
						}
						parameter = false;
					}
					break;
				}
				case '-':
				{
					if (parameter)
					{
						found = true;
						if (end == 2)
						{
							output[0] = '\0',
							strcat(output, "-", size);
						}
						parameter = false;
					}
					break;
				}
				case '+':
				{
					if (parameter)
					{
						found = true;
						if (end == 2)
						{
							output[0] = '\0',
							strcat(output, "+", size);
						}
						parameter = false;
					}
					break;
				}
				}
			}
		}
		else if (parameter)
		{
			strcat(output, name, size),
			parameter = false;
		}
	}
	return found;
}

stock bool:Args_GetBool(shortForm, const longForm[], &bool:dest)
{
	if (YSI_gsCacheState == E_ARGS_CACHE_STATE_UNINIT)
	{
		Args_LazyInit();
	}
	// Doesn't need to be big to hold `false`.
	new
		output[8];
	if (YSI_gsCacheState == E_ARGS_CACHE_STATE_INIT)
	{
		// TODO:
	}
	else
	{
		if (!Args_GetStringFallback(shortForm, longForm, output, sizeof (output)))
		{
			return (dest = false);
		}
	}
	// Boolean parameters are `false` if they exactly one of:
	//
	//   1) Followed by `-`.
	//   2) Assigned `0`.
	//   3) Assigned `false`.
	//
	// Anything else is `true`.  Even seemingly falsey things like `null`.
	return
		dest = output[0] != '-'
			&& output[0] != '0'
			&& strcmp(output, "false", true),
		true;
}

