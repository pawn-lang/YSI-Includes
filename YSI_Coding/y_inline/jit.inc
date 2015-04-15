/*

JITed y_inline.  Needs to be done ahead of time (much like the old version).

Basic process:

	1) Find everything that is an inline function, this will need pattern
	    searching again as in the old version.  Slow at startup, but not
	    terrible, and fine afterwards.  Note that I already scan the AMX for
	    certain patterns, so I can scan for this too at the same time maybe.
	
	2) Rewrite the code.  The new version reads the stack at run time, this
	    version can't so will need some more cunning method.
	

*/

static stock const
	YSI_g_scParameterCounts[Opcode] =
		{
			0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1,
			0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
			1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1,
			1, 0, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1, 0, 1, -1, 0, 0, 1, 0, 1, 1, 0,
			cellmin
		};

static stock
	YSI_g_sScanPatterns[128],
	YSI_g_sScanIndexes[8],
	YSI_g_sScanners = 0;

stock Scanner_AddPattern(...)
{
	if (YSI_g_sScanners == sizeof (YSI_g_sScanIndexes) - 1) return -1;
	new
		idx = YSI_g_sScanIndexes[YSI_g_sScanners],
		codes = numargs();
	
	
	
}



