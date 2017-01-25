Test:y_bintree_1()
{
	new BinaryInput:values<100>;
	for (new i = 0; i != sizeof (values); ++i)
	{
		values[i][E_BINTREE_INPUT_VALUE] = i;
		values[i][E_BINTREE_INPUT_POINTER] = i * 2 + 1;
	}
	new BinaryTree:tree<100>;
	Bintree_Generate(tree, values);
	for (new i = 0; i != sizeof (values); ++i)
	{
		ASSERT(Bintree_FindValue(tree, i) == i * 2 + 1);
	}
	for (new i = -100; i != 0; ++i)
	{
		ASSERT(Bintree_FindValue(tree, i) == BINTREE_NOT_FOUND);
	}
	for (new i = sizeof (values); i != 1000; ++i)
	{
		ASSERT(Bintree_FindValue(tree, i) == BINTREE_NOT_FOUND);
	}
	
}

