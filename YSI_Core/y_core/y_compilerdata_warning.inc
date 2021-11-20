#if Y_COMPILERDATA_WARNING == 0
	#warning ==========================================
	#warning |                                        |
	#warning | Using `YSI_TESTS` will produce a huge  |
	#warning | number of warnings.  However, they're  |
	#warning |  all in tests and actually test that   |
	#warning |    warnings are correctly produced.    |
	#warning |                                        |
	#warning ==========================================
#endif

#if Y_COMPILERDATA_WARNING == 1
	#warning Could not determine `sNAMEMAX`, falling back on 31.
#endif

#undef Y_COMPILERDATA_WARNING

