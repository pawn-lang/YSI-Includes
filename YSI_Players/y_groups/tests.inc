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
	foreach (new p : Group(g))
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
	foreach (new p : Group(g))
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

#define GROUP_LIBRARY_NAME<%0...%1> %0Test%1
#define GROUP_LIBRARY_SIZE 100

#include "..\YSI_Players\y_groups"

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

Test:Chains()
{
	new
		Group:g = Group_Create();
	call OnPlayerConnect(44);
	ASSERT_FALSE(Group_GetPlayer(g, 44));
	Group_SetGlobalGroup(g, true);
	ASSERT_TRUE(Group_GetPlayer(g, 44));
	call OnPlayerDisconnect(44, 0);
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
