#if defined _INC_y_mock
	#endinput
#endif
#define _INC_y_mock

#include "..\YSI_Coding\y_hooks"

static stock
	YSI_g_sMockFile[2024];

hook OnScriptInit()
{
	// Add a file.
	strcat(YSI_g_sMockFile, "YSI/test_ini/test1.ini\1" \
		"key0 = 42"       "\r\n" \
		"key1 = 43"       "\r\n" \
		"key2 = 45"       "\r\n" \
		"key4 = 46"       "\r\n" \
		"key3 = 47"       "\r\n" \
		""                "\r\n" \
		"[atag]"          "\r\n" \
		""                "\r\n" \
		"key0 = hello"    "\r\n" \
		"otherKey = 5.5"  "\r\n" \
		"myKey = false"   "\r\n" \
		""                "\r\n" \
		"[@@filter-tag2]" "\r\n" \
		""                "\r\n" \
		"filtered1 = yes" "\r\n" \
		"filtered2 = no"  "\r\n" \
		"\r\n\2");
	// Add a file.
	strcat(YSI_g_sMockFile, "YSI/test_ini/test2.ini\1" \
		"[tag0]"        "\r\n" \
		"key0 = 101"    "\r\n" \
		"key1 = 102"    "\r\n" \
		""              "\r\n" \
		"[tag1] : tag0" "\r\n" \
		""              "\r\n" \
		"key2 = 103"    "\r\n" \
		"key3 = 104"    "\r\n" \
		""              "\r\n" \
		"[tag2] : tag1" "\r\n" \
		""              "\r\n" \
		"key4 = 105"    "\r\n" \
		"key5 = 106"    "\r\n" \
		"; Overwrite"   "\r\n" \
		"key0 = 107"    "\r\n" \
		"\r\n\2");
}

static stock Mock_Compare(const name[], s, e)
{
	// Compare the file names, allowing "/" and "\" to match.
	new
		i = 0;
	while (s != e)
	{
		switch (name[i])
		{
			case '\0': return false;
			case '/', '\\': if (YSI_g_sMockFile[s] != '\\' && YSI_g_sMockFile[s] != '/') return false;
			default: if (YSI_g_sMockFile[s] != name[i]) return false;
		}
		++i;
		++s;
	}
	return name[i] == '\0';
}

stock File:Mock_fopen(const name[], filemode:mode = io_readwrite)
{
	// This function is not well optimised, but it doesn't need to be.  It only
	// provides a common and constant interface with which we can profile other
	// functions that read files.
	assert(mode == io_read);
	// Find the named file.
	new
		pos = 0,
		end;
	do
	{
		end = strfind(YSI_g_sMockFile, "\1", false, pos);
		//printf("Trying: %s %d %d", name, pos, end);
		if (Mock_Compare(name, pos, end)) return File:(end + 1);
		pos = strfind(YSI_g_sMockFile, "\2", false, pos) + 1;
	}
	while (YSI_g_sMockFile[pos]);
	return File:0;
}

stock Mock_fread(&File:handle, dest[], len = sizeof (dest))
{
	if (YSI_g_sMockFile[_:handle] == '\2') return 0;
	new
		ret = strfind(YSI_g_sMockFile[_:handle], "\r\n") + 2;
	strcpy(dest, YSI_g_sMockFile[_:handle], min(len, ret + 1));
	handle += File:ret;
	return ret;
}

stock Mock_fseek(&File:handle, position = 0, seek_whence:whence = seek_start)
{
	switch (whence)
	{
		case seek_start:
		{
			// Loop backwards.
			for (new i = _:handle; --i; )
			{
				if (YSI_g_sMockFile[i] == '\1')
				{
					handle = File:(position + i + 1);
					return 1;
				}
			}
		}
		case seek_current:
		{
			handle += File:position;
			return 1;
		}
		case seek_end:
		{
			handle = File:(strfind(YSI_g_sMockFile, "\2", false, _:handle) - position);
			return 1;
		}
	}
	return 0;
}

stock Mock_fclose(&File:handle)
{
	handle = File:0;
	return 0;
}

#if defined YSI_MOCK_READER
	#if defined _ALS_fopen
		#undef fopen
	#else
		#define _ALS_fopen
	#endif
	#define fopen Mock_fopen
	
	#if defined _ALS_fread
		#undef fread
	#else
		#define _ALS_fread
	#endif
	#define fread Mock_fread
	
	#if defined _ALS_fseek
		#undef fseek
	#else
		#define _ALS_fseek
	#endif
	#define fseek Mock_fseek
	
	#if defined _ALS_fclose
		#undef fclose
	#else
		#define _ALS_fclose
	#endif
	#define fclose Mock_fclose
#endif

