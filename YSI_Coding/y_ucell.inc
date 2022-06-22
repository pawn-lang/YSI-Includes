y_ucell

#define uint: ucell:

bool:operator==(ucell:a, ucell:b)
{
	return (_:a == _:b);
}

bool:operator==(a, ucell:b)
{
	return (a >= 0 && a == _:b);
}

bool:operator==(ucell:a, b)
{
	return (b >= 0 && _:a == b);
}

ucell:operator+(ucell:a, ucell:b)
{
	return ucell:(_:a + _:b);
}

//ucell:operator+(ucell:a, b)
//{
//	// I don't know what the best semantics are here.
//	return ucell:(_:a + _:b);
//}

ucell:operator-(ucell:a, ucell:b)
{
	return ucell:(_:a - _:b);
}

ucell:operator*(ucell:a, ucell:b)
{
	#emit LOAD.S.pri a
	#emit LOAD.S.alt b
	#emit UMUL
	#emit RETN
	__pragma("naked");
}

ucell:operator/(ucell:a, ucell:b)
{
	#emit LOAD.S.pri a
	#emit LOAD.S.alt b
	#emit UDIV
	#emit RETN
	__pragma("naked");
}

ucell:operator%(ucell:a, ucell:b)
{
	#emit LOAD.S.pri a
	#emit LOAD.S.alt b
	#emit UDIV
	#emit MOVE.pri
	#emit RETN
	__pragma("naked");
}

static stock UCell_Format(output[], size, const string[], GLOBAL_TAG_TYPES:...)
{
	new
		i = 0,
		j = 0,
		ch = 0,
		flags = 0,
		width = 0,
		prec = 0,
		arg = 3;
	--size;
	while ((ch = string[i++]) && j < size)
	{
		if (flags)
		{
			if (ch == 'u')
			{
				// ucell value.
			}
			else if (IS_IN_RANGE(ch, '1', '9' + 1))
			{
				// Width or prec.
			}
			else if (ch == '%')
			{
				// Literal '%'.
			}
			else if (ch == '.')
			{
				// Swap to prec.
			}
			else if (ch == ' ')
			{
				// Leading space.
			}
			else if (ch == '0')
			{
				// Maybe leading 0.
			}
			else if (ch == '*')
			{
				// Dynamic width/prec.
			}
			else
			{
				//
			}
		}
	}
	output[j] = '\0';
}

hook function printf(const string[], GLOBAL_TAG_TYPES:...)
{
	static output[256];
	// TODO: Write the code.
	return continue(string, ___(1));
}

hook function format(output[], size, const string[], GLOBAL_TAG_TYPES:...)
{
	// TODO: Write the code.
	return continue(output, size, string, ___(3));
}

