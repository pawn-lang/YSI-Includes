static RandomString()
{
	new ret[32];
	new i = 0;
	new ch;
	while (random(8) && i != sizeof (ret) - 1)
	{
		ch = random(256);
		if (random(2))
		{
			ch |= random(256) << 8;
			if (random(2))
			{
				ch |= random(256) << 16;
				if (random(2))
				{
					ch |= random(256) << 24;
				}
			}
		}
		ret[i++] = ch;
	}
	ret[i] = '\0';
	return ret;
}

new YSI_g_sStrings[8192][32];
new YSI_g_sHashes[256];

#define ITERATIONS 100

PROFILE_INIT__ 000Setup()
{
	for (new i = 0; i != sizeof (YSI_g_sStrings); ++i)
	{
		printf("%d", i);
		YSI_g_sStrings[i] = RandomString();
	}
}

PROFILE__ 000Setup()
{
}

PROFILE_INIT__ Bernstein()
{
	for (new i = 0; i != sizeof (YSI_g_sHashes); ++i)
	{
		YSI_g_sHashes[i] = 0;
	}
}

PROFILE__ Bernstein[ITERATIONS]()
{
	for (new i = 0; i != sizeof (YSI_g_sStrings); ++i)
	{
		++YSI_g_sHashes[BernsteinHash(YSI_g_sStrings[i]) & 255];
	}
}

PROFILE_CLOSE__ Bernstein()
{
	for (new i = 0; i != sizeof (YSI_g_sHashes); ++i)
	{
		printf("%d", YSI_g_sHashes[i] / ITERATIONS / TIMING_ITERATIONS);
	}
}

PROFILE_INIT__ Jenkins()
{
	for (new i = 0; i != sizeof (YSI_g_sHashes); ++i)
	{
		YSI_g_sHashes[i] = 0;
	}
}

PROFILE__ Jenkins[ITERATIONS]()
{
	for (new i = 0; i != sizeof (YSI_g_sStrings); ++i)
	{
		++YSI_g_sHashes[JenkinsHash(YSI_g_sStrings[i]) & 255];
	}
}

PROFILE_CLOSE__ Jenkins()
{
	for (new i = 0; i != sizeof (YSI_g_sHashes); ++i)
	{
		printf("%d", YSI_g_sHashes[i] / ITERATIONS / TIMING_ITERATIONS);
	}
}

