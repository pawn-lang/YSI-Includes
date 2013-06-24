Test:y_commands_Hashing()
{
	new
		dst0[32],
		dst1[32],
		hash0,
		hash1;
	// V1.
	Puny_Encode(dst0, "Hello\x102;you", .delimiter = '@');
	HashMap_Hash(dst0, hash0);
	// V2.
	new
		len = Puny_EncodeHash(dst1, "Hello\x102;you there", hash1, .delimiter = '@');
	// Same.
	ASSERT(!strcmp(dst0, dst1));
	ASSERT(hash0 == hash1);
	ASSERT(len == strlen(dst1));
}

Test:y_commands_
