#assert MAX_PLAYERS >= 50

Test:000_y_groups_Global()
{
	// Need a certain number just to run this code.
	call OnPlayerConnect(42);
	ASSERT(Group_GetPlayer(GROUP_GLOBAL, 42));
	//call OnPlayerDisconnect(42, 0);
}

Test:y_groups_Valid()
{
	new
		Group:g = Group_Create("Valid"),
		Group:i = Group_Create("Invalid");
	Group_Destroy(i);
	ASSERT_TRUE(Group_IsValid(g));
	ASSERT_FALSE(Group_IsValid(i));
	ASSERT_FALSE(Group_IsValid(Group:3));
	Group_Destroy(g);
}

Test:y_groups_Create0()
{
	new
		Group:g = Group_Create();
	ASSERT(g != INVALID_GROUP);
	Group_Destroy(g);
}

Test:y_groups_Create0b()
{
	new
		Group:g0 = Group_Create("hello"),
		Group:g1 = Group_Create("there");
	ASSERT(g0 != INVALID_GROUP);
	ASSERT(g1 != INVALID_GROUP);
	ASSERT(g0 != g1);
	Group_Destroy(g0);
	Group_Destroy(g1);
}

Test:y_groups_Create1()
{
	new
		Group:g = Group_Create("Group 1");
	ASSERT(g != INVALID_GROUP);
	Group_Destroy(g);
}

Test:y_groups_GetID()
{
	new
		Group:g = Group_Create("Group 2");
	ASSERT(g == Group_GetID("Group 2"));
	ASSERT(!strcmp("Group 2", Group_GetName(g)));
	Group_Destroy(g);
}

Test:y_groups_GetGang0()
{
	new
		Group:g = Group_Create("Group 3");
	ASSERT_FALSE(Group_GetGang(g));
	Group_Destroy(g);
}

Test:y_groups_GetGang1()
{
	new
		Group:g = Group_Create("Group 4");
	Group_SetGang(g, true);
	ASSERT_TRUE(Group_GetGang(g));
	Group_Destroy(g);
}

Test:y_groups_GetGang2()
{
	new
		Group:g = Group_Create("Group 5");
	Group_SetGang(g, true);
	Group_SetGang(g, false);
	ASSERT_FALSE(Group_GetGang(g));
	Group_Destroy(g);
}

Test:y_groups_GetColour()
{
	new
		Group:g = Group_Create("Group 6");
	Group_SetColour(g, 0x11227654);
	ASSERT(Group_GetColor(g) == 0x112276AA);
	Group_SetColour(g, 0x76541122);
	ASSERT(Group_GetColor(g) == 0x765411AA);
	Group_SetColour(g, 0x65127412);
	ASSERT(Group_GetColor(g) == 0x651274AA);
	Group_Destroy(g);
}

Test:y_groups_Set1()
{
	new
		Group:g = Group_Create("Group 7");
	ASSERT(Group_GetCount(g) == 0);
	Group_SetPlayer(g, 42, true);
	ASSERT_TRUE(Group_GetPlayer(g, 42));
	ASSERT(Group_GetCount(g) == 1);
	new
		c = 0;
	foreach (new p : GroupMember[g])
	{
		ASSERT(p == 42);
		++c;
	}
	ASSERT(c == 1);
	Group_Destroy(g);
}

Test:y_groups_Set2()
{
	new
		Group:g = Group_Create("Group 8");
	ASSERT(Group_GetCount(g) == 0);
	//new k = Group_SetPlayer(g, 42, true);
	Group_SetPlayer(g, 42, true);
	ASSERT(Group_GetCount(g) == 1);
	Group_SetPlayer(g, 42, false);
	ASSERT(Group_GetCount(g) == 0);
	new
		c = 0;
	foreach (new p : GroupMember(g))
	{
		++c;
	}
	ASSERT(c == 0);
	Group_Destroy(g);
}

Test:y_groups_Set3()
{
	new
		Group:g = Group_Create("Group 8");
	Group_SetPlayer(g, 42, true);
	ASSERT(Group_GetCount(g) == 1);
	//W@(#On#PlayerDisconnect         ,x:#ii#,42, 0);
	call OnPlayerDisconnect(42, 0);
	//ASSERT(Group_GetCount(g) == 0);
	//call OnPlayerConnect(42);
	//ASSERT(Group_GetCount(g) == 0);
	Group_Destroy(g);
}

#define MASTER 60
#tryinclude "..\YSI_Core\y_master"
#tryinclude "..\..\YSI_Core\y_master"

#define _GROUP_MAKE_NAME<%0...%1> %0Test%1
#define _GROUP_MAKE_LIMIT 123

#tryinclude "y_groups\_funcs"
#tryinclude "_funcs"

static
	gPl,
	gEl,
	bool:gS;

Test_SetPlayer(el, playerid, bool:s)
{
	P:1("Test_SetPlayer called: %d %d %d", el, playerid, s);
	gPl = playerid;
	gEl = el;
	gS = s;
	return 1;
}

Test:0_y_groups_Connect0()
{
	gPl = INVALID_PLAYER_ID;
	gEl = 100;
	gS = false;
	//new
	//	Group:g = Group_Create();
	call OnPlayerConnect(45);
	ASSERT(gPl == INVALID_PLAYER_ID);
	ASSERT(gEl == 100);
	ASSERT(gS == false);
	//printf("%d %d %d", gPl, gEl, gS);
	Test_InitialiseFromGroups(7);
	ASSERT(gPl == 45);
	ASSERT(gEl == 7);
	ASSERT(gS == true);
	call OnPlayerDisconnect(45, 0);
}

Test:0_y_groups_Connect1()
{
	gPl = INVALID_PLAYER_ID;
	gEl = 100;
	gS = false;
	//new
	//	Group:g = Group_Create();
	Test_InitialiseFromGroups(8);
	ASSERT(gPl != INVALID_PLAYER_ID);
	ASSERT(gEl != 100);
	ASSERT(gS != false);
	call OnPlayerConnect(43);
	ASSERT(gPl == 43);
	ASSERT(gEl == 8);
	ASSERT(gS == true);
	call OnPlayerDisconnect(43, 0);
}

Test:y_groups_Chains()
{
	new
		Group:g = Group_Create();
	call OnPlayerConnect(44);
	ASSERT_FALSE(Group_GetPlayer(g, 44));
	Group_SetGlobalGroup(g, true);
	ASSERT_TRUE(Group_GetPlayer(g, 44));
	call OnPlayerDisconnect(44, 0);
}

Test:y_groups_Children0()
{
	new
		Group:g0 = Group_Create();
	ASSERT(!Group_GetGlobalGroup(g0));
	Group_Destroy(g0);
}

Test:y_groups_Children1()
{
	new
		Group:g0 = Group_Create(),
		Group:g1 = Group_Create(),
		Group:g2 = Group_Create();
	// Check groups ARE descendants of themselves.
	ASSERT(Group_IsDescendant(GROUP_GLOBAL, GROUP_GLOBAL));
	ASSERT(Group_IsDescendant(g0, g0));
	ASSERT(Group_IsDescendant(g1, g1));
	ASSERT(Group_IsDescendant(g2, g2));
	// Check there are no relationships at all.
	ASSERT(!Group_IsDescendant(g0, g1));
	ASSERT(!Group_IsDescendant(g0, g2));
	ASSERT(!Group_IsDescendant(g1, g0));
	ASSERT(!Group_IsDescendant(g1, g2));
	ASSERT(!Group_IsDescendant(g2, g0));
	ASSERT(!Group_IsDescendant(g2, g1));
	// Grlobal group.
	ASSERT(!Group_IsDescendant(GROUP_GLOBAL, g0));
	ASSERT(!Group_IsDescendant(GROUP_GLOBAL, g1));
	ASSERT(!Group_IsDescendant(GROUP_GLOBAL, g2));
	ASSERT(!Group_IsDescendant(g0, GROUP_GLOBAL));
	ASSERT(!Group_IsDescendant(g1, GROUP_GLOBAL));
	ASSERT(!Group_IsDescendant(g2, GROUP_GLOBAL));
	Group_Destroy(g0),
	Group_Destroy(g1),
	Group_Destroy(g2);
}

Test:y_groups_Children2()
{
	new
		Group:g0 = Group_Create(),
		Group:g1 = Group_Create(),
		Group:g2 = Group_Create();
	// Check groups are children of themselves.
	ASSERT(!Group_GetGroup(GROUP_GLOBAL, GROUP_GLOBAL));
	ASSERT(!Group_GetGroup(g0, g0));
	ASSERT(!Group_GetGroup(g1, g1));
	ASSERT(!Group_GetGroup(g2, g2));
	// Check there are no relationships at all.
	ASSERT(!Group_GetGroup(g0, g1));
	ASSERT(!Group_GetGroup(g0, g2));
	ASSERT(!Group_GetGroup(g1, g0));
	ASSERT(!Group_GetGroup(g1, g2));
	ASSERT(!Group_GetGroup(g2, g0));
	ASSERT(!Group_GetGroup(g2, g1));
	// Grlobal group.
	ASSERT(!Group_GetGroup(GROUP_GLOBAL, g0));
	ASSERT(!Group_GetGroup(GROUP_GLOBAL, g1));
	ASSERT(!Group_GetGroup(GROUP_GLOBAL, g2));
	ASSERT(!Group_GetGroup(g0, GROUP_GLOBAL));
	ASSERT(!Group_GetGroup(g1, GROUP_GLOBAL));
	ASSERT(!Group_GetGroup(g2, GROUP_GLOBAL));
	Group_Destroy(g0),
	Group_Destroy(g1),
	Group_Destroy(g2);
}

Test:y_groups_Children3()
{
	new
		Group:g0 = Group_Create(),
		Group:g1 = Group_Create(),
		Group:g2 = Group_Create();
	Group_AddChild(g0, g1);
	ASSERT(Group_IsDescendant(g0, g1));
	// Check there are no other relationships.
	ASSERT(!Group_IsDescendant(g0, g2));
	ASSERT(!Group_IsDescendant(g1, g0));
	ASSERT(!Group_IsDescendant(g1, g2));
	ASSERT(!Group_IsDescendant(g2, g0));
	ASSERT(!Group_IsDescendant(g2, g1));
	Group_Destroy(g0),
	Group_Destroy(g1),
	Group_Destroy(g2);
}

Test:y_groups_Children4()
{
	new
		Group:g0 = Group_Create(),
		Group:g1 = Group_Create(),
		Group:g2 = Group_Create();
	Group_AddChild(g0, g1);
	Group_AddChild(g1, g2);
	// Test chaining.
	ASSERT(Group_IsDescendant(g0, g1));
	ASSERT(Group_IsDescendant(g1, g2));
	ASSERT(Group_IsDescendant(g0, g2));
	// Check there are no reverse relationships.
	ASSERT(!Group_IsDescendant(g1, g0));
	ASSERT(!Group_IsDescendant(g2, g0));
	ASSERT(!Group_IsDescendant(g2, g1));
	Group_Destroy(g0),
	Group_Destroy(g1),
	Group_Destroy(g2);
}

Test:y_groups_Children5()
{
	new
		Group:g0 = Group_Create(),
		Group:g1 = Group_Create(),
		Group:g2 = Group_Create(),
		Group:g3 = Group_Create(),
		Group:g4 = Group_Create();
	Group_AddChild(g0, g1);
	Group_AddChild(g1, g2);
	Group_AddChild(g2, g0);
	Group_AddChild(g4, g0);
	// Test cycles don't hang.
	ASSERT(!Group_IsDescendant(g4, g3));
	ASSERT(!Group_IsDescendant(g3, g4));
	// Test cycles work.
	ASSERT(Group_IsDescendant(g4, g2));
	ASSERT(!Group_IsDescendant(g2, g4));
	ASSERT(Group_IsDescendant(g0, g2));
	ASSERT(Group_IsDescendant(g2, g0));
	Group_Destroy(g0),
	Group_Destroy(g1),
	Group_Destroy(g2);
	Group_Destroy(g3);
	Group_Destroy(g4);
}

Test:y_groups_Children6()
{
	new
		Group:g0 = Group_Create(),
		Group:g1 = Group_Create(),
		Group:g2 = Group_Create();
	Group_AddChild(g0, g1);
	Group_AddChild(g1, g2);
	// Test removal
	ASSERT(Group_IsDescendant(g0, g2));
	Group_RemoveChild(g1, g2);
	ASSERT(!Group_IsDescendant(g0, g2));
	Group_AddChild(g1, g2);
	ASSERT(Group_IsDescendant(g0, g2));
	Group_Destroy(g1);
	ASSERT(!Group_IsDescendant(g0, g2));
	Group_Destroy(g0),
	Group_Destroy(g2);
}

Test:y_groups_Children7()
{
	new
		Group:g0 = Group_Create(),
		Group:g1 = Group_Create(),
		Group:g2 = Group_Create();
	Group_AddChild(g0, g1);
	Group_AddChild(g1, g2);
	// Test chaining.
	ASSERT(Group_IsDescendant(g0, g1));
	ASSERT(Group_IsDescendant(g1, g2));
	ASSERT(Group_IsDescendant(g0, g2));
	// Check there are no reverse relationships.
	ASSERT(!Group_IsChild(g0, g2));
	Group_Destroy(g0),
	Group_Destroy(g1),
	Group_Destroy(g2);
}

Test:y_groups_ChildIterator0()
{
	new
		Group:g0 = Group_Create(),
		Group:g1 = Group_Create(),
		Group:g2 = Group_Create();
	Group_AddChild(g0, g1);
	Group_AddChild(g0, g2);
	new
		total = 0;
	foreach (new Group:g : GroupChild(g0))
	{
		++total;
	}
	ASSERT(total == 2);
	Group_Destroy(g0),
	Group_Destroy(g1),
	Group_Destroy(g2);
}

Test:y_groups_ChildIterator1()
{
	new
		Group:g0 = Group_Create(),
		Group:g1 = Group_Create(),
		Group:g2 = Group_Create();
	Group_AddChild(g0, g1);
	Group_AddChild(g0, g2);
	ASSERT(Group_IsValid(g0));
	ASSERT(Group_IsValid(g1));
	ASSERT(Group_IsValid(g2));
	foreach (new Group:g : GroupChild(g0))
	{
		Group_Destroy(g);
	}
	ASSERT(Group_IsValid(g0));
	ASSERT(!Group_IsValid(g1));
	ASSERT(!Group_IsValid(g2));
	Group_Destroy(g0),
	ASSERT(!Group_IsValid(g0));
}

Test:y_groups_ChildIterator2()
{
	new
		Group:g0 = Group_Create(),
		Group:g1 = Group_Create(),
		Group:g2 = Group_Create();
	Group_AddChild(g0, g1);
	Group_AddChild(g0, g2);
	ASSERT(Group_IsValid(g0));
	ASSERT(Group_IsValid(g1));
	ASSERT(Group_IsValid(g2));
	new
		total = 0;
	foreach (new Group:g : GroupChild[g0])
	{
		Group_Destroy(g);
		++total;
	}
	ASSERT(total == 2);
	ASSERT(Group_IsValid(g0));
	ASSERT(!Group_IsValid(g1));
	ASSERT(!Group_IsValid(g2));
	Group_Destroy(g0),
	ASSERT(!Group_IsValid(g0));
}

Test:y_groups_Iterator0()
{
	new
		Group:g0 = Group_Create(),
		Group:g1 = Group_Create(),
		Group:g2 = Group_Create();
	new
		total = 0;
	foreach (new Group:g : CreatedGroup)
	{
		++total;
	}
	ASSERT(total >= 3);
	total = 0;
	foreach (new Group:g : CreatedGroup())
	{
		++total;
	}
	ASSERT(total >= 3);
	Group_Destroy(g0),
	Group_Destroy(g1),
	Group_Destroy(g2);
}

#undef _GROUP_MAKE_LIMIT
#undef _GROUP_MAKE_NAME

#tryinclude "..\YSI_Core\y_master"
#tryinclude "..\..\YSI_Core\y_master"

