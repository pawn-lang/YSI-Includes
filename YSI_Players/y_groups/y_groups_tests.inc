/*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright C 2011
	the Initial Developer. All Rights Reserved.

Contributors:
	Y_Less
	koolk
	JoeBullet/Google63
	g_aSlice/Slice
	Misiur
	samphunter
	tianmeta
	maddinat0r
	spacemud
	Crayder
	Dayvison
	Ahmad45123
	Zeex
	irinel1996
	Yiin-
	Chaprnks
	Konstantinos
	Masterchen09
	Southclaws
	PatchwerkQWER
	m0k1
	paulommu
	udan111

Thanks:
	JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
	ZeeX - Very productive conversations.
	koolk - IsPlayerinAreaEx code.
	TheAlpha - Danish translation.
	breadfish - German translation.
	Fireburn - Dutch translation.
	yom - French translation.
	50p - Polish translation.
	Zamaroht - Spanish translation.
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

#assert MAX_PLAYERS >= 50

TEST__ 000_y_groups_Global()
{
	// Need a certain number just to run this code.
	call OnPlayerConnect(42);
	ASSERT(Group_GetPlayer(GROUP_GLOBAL, 42));
	//call OnPlayerDisconnect(42, 0);
}

TEST__ y_groups_Valid()
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

TEST__ y_groups_Create0()
{
	new
		Group:g = Group_Create();
	ASSERT_NE(g, INVALID_GROUP);
	Group_Destroy(g);
}

TEST__ y_groups_Create0b()
{
	new
		Group:g0 = Group_Create("hello"),
		Group:g1 = Group_Create("there");
	ASSERT_NE(g0, INVALID_GROUP);
	ASSERT_NE(g1, INVALID_GROUP);
	ASSERT_NE(g0, g1);
	Group_Destroy(g0);
	Group_Destroy(g1);
}

TEST__ y_groups_Create1()
{
	new
		Group:g = Group_Create("Group 1");
	ASSERT_NE(g, INVALID_GROUP);
	Group_Destroy(g);
}

TEST__ y_groups_GetID()
{
	new
		Group:g = Group_Create("Group 2");
	ASSERT_EQ(g, Group_GetID("Group 2"));
	ASSERT_SAME(Group_GetName(g), "Group 2");
	Group_Destroy(g);
}
 
TEST__ y_groups_GetGang0()
{
	new
		Group:g = Group_Create("Group 3");
	ASSERT_FALSE(Group_GetGang(g));
	Group_Destroy(g);
}

TEST__ y_groups_GetGang1()
{
	new
		Group:g = Group_Create("Group 4");
	Group_SetGang(g, true);
	ASSERT_TRUE(Group_GetGang(g));
	Group_Destroy(g);
}

TEST__ y_groups_GetGang2()
{
	new
		Group:g = Group_Create("Group 5");
	Group_SetGang(g, true);
	Group_SetGang(g, false);
	ASSERT_FALSE(Group_GetGang(g));
	Group_Destroy(g);
}

TEST__ y_groups_GetColour()
{
	new
		Group:g = Group_Create("Group 6");
	Group_SetColour(g, 0x11227654);
	ASSERT_EQ(Group_GetColor(g), 0x112276AA);
	Group_SetColour(g, 0x76541122);
	ASSERT_EQ(Group_GetColor(g), 0x765411AA);
	Group_SetColour(g, 0x65127412);
	ASSERT_EQ(Group_GetColor(g), 0x651274AA);
	Group_Destroy(g);
}

TEST__ y_groups_Set1()
{
	new
		Group:g = Group_Create("Group 7");
	ASSERT_ZE(Group_GetCount(g));
	Group_SetPlayer(g, 42, true);
	ASSERT_TRUE(Group_GetPlayer(g, 42));
	ASSERT_EQ(Group_GetCount(g), 1);
	new
		c = 0;
	FOREACH__ (new p : GroupMember[g])
	{
		ASSERT_EQ(p, 42);
		++c;
	}
	ASSERT_EQ(c, 1);
	Group_Destroy(g);
}

TEST__ y_groups_Set2()
{
	new
		Group:g = Group_Create("Group 8");
	ASSERT_ZE(Group_GetCount(g));
	//new k = Group_SetPlayer(g, 42, true);
	Group_SetPlayer(g, 42, true);
	ASSERT_EQ(Group_GetCount(g), 1);
	Group_SetPlayer(g, 42, false);
	ASSERT_ZE(Group_GetCount(g));
	new
		c = 0;
	FOREACH__ (new p : GroupMember(g))
	{
		++c;
	}
	ASSERT_ZE(c);
	Group_Destroy(g);
}

TEST__ y_groups_Set3()
{
	new
		Group:g = Group_Create("Group 8");
	Group_SetPlayer(g, 42, true);
	ASSERT_EQ(Group_GetCount(g), 1);
	call OnPlayerDisconnect(42, 0);
	Group_Destroy(g);
}

TEST__ y_groups_SetBalanced0()
{
	new
		Group:g1 = Group_Create("Group 1"),
		Group:g2 = Group_Create("Group 2");
	
	call OnPlayerConnect(22);
	
	Group_SetPlayer(g2, 22, true);
	Group_SetBalanced(22, g1, g2);
	
	ASSERT(Group_GetCount(g1) == 0 && Group_GetCount(g2) == 1);
	
	call OnPlayerDisconnect(22, 0);
	
	Group_Destroy(g1);
	Group_Destroy(g2);
}

TEST__ y_groups_SetBalanced1()
{
	new
		Group:g1 = Group_Create("Group 1"),
		Group:g2 = Group_Create("Group 2");
	
	call OnPlayerConnect(23);
	call OnPlayerConnect(32);
	
	Group_SetBalanced(23, g1, g2);
	Group_SetBalanced(32, g1, g2);
	
	ASSERT(Group_GetCount(g1) == 1 && Group_GetCount(g2) == 1);
	
	call OnPlayerDisconnect(23, 0);
	call OnPlayerDisconnect(32, 0);
	
	Group_Destroy(g1);
	Group_Destroy(g2);
}

TEST__ y_groups_SetBalanced2()
{
	new
		Group:g1 = Group_Create("Group 1"),
		Group:g2 = Group_Create("Group 2"),
		Group:g3 = Group_Create("Group 3");
	
	call OnPlayerConnect(1);
	call OnPlayerConnect(2);
	call OnPlayerConnect(3);
	call OnPlayerConnect(4);
	call OnPlayerConnect(5);
	call OnPlayerConnect(6);
	
	Group_SetBalanced(1, g1, g2, g3);
	Group_SetBalanced(2, g1, g2, g3);
	Group_SetBalanced(3, g1, g2, g3);
	Group_SetBalanced(4, g1, g2, g3);
	Group_SetBalanced(5, g1, g2, g3);
	Group_SetBalanced(6, g1, g2, g3);
	
	ASSERT(Group_GetCount(g1) == 2 && Group_GetCount(g2) == 2 && Group_GetCount(g3) == 2);
	
	call OnPlayerDisconnect(1, 0);
	call OnPlayerDisconnect(2, 0);
	call OnPlayerDisconnect(3, 0);
	call OnPlayerDisconnect(4, 0);
	call OnPlayerDisconnect(5, 0);
	call OnPlayerDisconnect(6, 0);
	
	Group_Destroy(g1);
	Group_Destroy(g2);
	Group_Destroy(g3);
}

TEST__ y_groups_SetBalanced3()
{
	new
		Group:g[3];
	g[0] = Group_Create("Group 1");
	g[1] = Group_Create("Group 2");
	g[2] = Group_Create("Group 3");

	call OnPlayerConnect(0);
	call OnPlayerConnect(1);
	call OnPlayerConnect(2);
	call OnPlayerConnect(3);
	call OnPlayerConnect(4);
	call OnPlayerConnect(5);
	call OnPlayerConnect(6);

	Group_SetBalancedArray(0, g, sizeof(g));
	Group_SetBalancedArray(1, g, sizeof(g));
	Group_SetBalancedArray(2, g, sizeof(g));
	Group_SetBalancedArray(3, g, sizeof(g));
	Group_SetBalancedArray(4, g, sizeof(g));
	Group_SetBalancedArray(5, g, sizeof(g));
	Group_SetBalancedArray(6, g, sizeof(g));

	ASSERT_EQ(Group_GetCount(g[0]), 3);
	ASSERT_EQ(Group_GetCount(g[1]), 2);
	ASSERT_EQ(Group_GetCount(g[2]), 2);

	call OnPlayerDisconnect(0, 0);
	call OnPlayerDisconnect(1, 0);
	call OnPlayerDisconnect(2, 0);
	call OnPlayerDisconnect(3, 0);
	call OnPlayerDisconnect(4, 0);
	call OnPlayerDisconnect(5, 0);
	call OnPlayerDisconnect(6, 0);

	Group_Destroy(g[0]);
	Group_Destroy(g[1]);
	Group_Destroy(g[2]);
}

TEST__ y_groups_SetBalancedIn1()
{
	new
		Group:g[3];
	g[0] = Group_Create("Group 1");
	g[1] = Group_Create("Group 2");
	g[2] = Group_Create("Group 3");

	call OnPlayerConnect(0);
	call OnPlayerConnect(1);
	call OnPlayerConnect(2);
	call OnPlayerConnect(3);
	call OnPlayerConnect(4);
	call OnPlayerConnect(5);
	call OnPlayerConnect(6);
	
	Group_SetPlayer(g[0], 0, true);
	Group_SetPlayer(g[0], 1, true);
	Group_SetPlayer(g[0], 2, true);
	Group_SetPlayer(g[2], 3, true);
	Group_SetPlayer(g[2], 4, true);
	Group_SetPlayer(g[2], 5, true);

	Group_SetBalancedArray(6, g, sizeof(g));

	ASSERT_EQ(Group_GetCount(g[0]), 3);
	ASSERT_EQ(Group_GetCount(g[1]), 1);
	ASSERT_EQ(Group_GetCount(g[2]), 3);

	call OnPlayerDisconnect(0, 0);
	call OnPlayerDisconnect(1, 0);
	call OnPlayerDisconnect(2, 0);
	call OnPlayerDisconnect(3, 0);
	call OnPlayerDisconnect(4, 0);
	call OnPlayerDisconnect(5, 0);
	call OnPlayerDisconnect(6, 0);

	Group_Destroy(g[0]);
	Group_Destroy(g[1]);
	Group_Destroy(g[2]);
}

TEST__ y_groups_SetBalancedIn2()
{
	new
		Group:g[3];
	g[0] = Group_Create("Group 1");
	g[1] = Group_Create("Group 2");
	g[2] = Group_Create("Group 3");

	call OnPlayerConnect(0);
	call OnPlayerConnect(1);
	call OnPlayerConnect(2);
	call OnPlayerConnect(3);
	call OnPlayerConnect(4);
	call OnPlayerConnect(5);
	call OnPlayerConnect(6);
	
	Group_SetPlayer(g[0], 0, true);
	Group_SetPlayer(g[0], 1, true);
	Group_SetPlayer(g[0], 2, true);
	Group_SetPlayer(g[2], 3, true);
	Group_SetPlayer(g[2], 4, true);
	Group_SetPlayer(g[2], 5, true);

	Group_SetBalancedArray(0, g, sizeof(g));

	ASSERT_EQ(Group_GetCount(g[0]), 3);
	ASSERT_ZE(Group_GetCount(g[1]));
	ASSERT_EQ(Group_GetCount(g[2]), 3);

	call OnPlayerDisconnect(0, 0);
	call OnPlayerDisconnect(1, 0);
	call OnPlayerDisconnect(2, 0);
	call OnPlayerDisconnect(3, 0);
	call OnPlayerDisconnect(4, 0);
	call OnPlayerDisconnect(5, 0);
	call OnPlayerDisconnect(6, 0);

	Group_Destroy(g[0]);
	Group_Destroy(g[1]);
	Group_Destroy(g[2]);
}

TEST__ y_groups_SetBalancedIn3()
{
	new
		Group:g[3];
	g[0] = Group_Create("Group 1");
	g[1] = Group_Create("Group 2");
	g[2] = Group_Create("Group 3");

	call OnPlayerConnect(0);
	call OnPlayerConnect(1);
	call OnPlayerConnect(2);
	call OnPlayerConnect(3);
	call OnPlayerConnect(4);
	call OnPlayerConnect(5);
	call OnPlayerConnect(6);
	
	Group_SetPlayer(g[0], 0, true);
	Group_SetPlayer(g[0], 1, true);
	Group_SetPlayer(g[0], 2, true);
	Group_SetPlayer(g[2], 3, true);
	Group_SetPlayer(g[2], 4, true);
	Group_SetPlayer(g[2], 5, true);

	Group_SetBalancedArray(4, g, sizeof(g));

	ASSERT_EQ(Group_GetCount(g[0]), 3);
	ASSERT_ZE(Group_GetCount(g[1]));
	ASSERT_EQ(Group_GetCount(g[2]), 3);

	call OnPlayerDisconnect(0, 0);
	call OnPlayerDisconnect(1, 0);
	call OnPlayerDisconnect(2, 0);
	call OnPlayerDisconnect(3, 0);
	call OnPlayerDisconnect(4, 0);
	call OnPlayerDisconnect(5, 0);
	call OnPlayerDisconnect(6, 0);

	Group_Destroy(g[0]);
	Group_Destroy(g[1]);
	Group_Destroy(g[2]);
}

TEST__ y_groups_SetBalancedIn3a()
{
	new
		Group:g[3];
	g[0] = Group_Create("Group 1");
	g[1] = Group_Create("Group 2");
	g[2] = Group_Create("Group 3");

	call OnPlayerConnect(0);
	call OnPlayerConnect(1);
	call OnPlayerConnect(2);
	call OnPlayerConnect(3);
	call OnPlayerConnect(4);
	call OnPlayerConnect(5);
	call OnPlayerConnect(6);
	
	Group_SetPlayer(g[0], 0, true);
	Group_SetPlayer(g[0], 1, true);
	Group_SetPlayer(g[1], 2, true);
	Group_SetPlayer(g[1], 3, true);
	Group_SetPlayer(g[2], 4, true);
	Group_SetPlayer(g[2], 5, true);
	
	Group_SetPlayer(g[0], 6, true);

	Group_SetBalancedArray(0, g, sizeof(g));

	ASSERT_EQ(Group_GetCount(g[0]), 3);
	ASSERT_EQ(Group_GetCount(g[1]), 2);
	ASSERT_EQ(Group_GetCount(g[2]), 2);

	call OnPlayerDisconnect(0, 0);
	call OnPlayerDisconnect(1, 0);
	call OnPlayerDisconnect(2, 0);
	call OnPlayerDisconnect(3, 0);
	call OnPlayerDisconnect(4, 0);
	call OnPlayerDisconnect(5, 0);
	call OnPlayerDisconnect(6, 0);

	Group_Destroy(g[0]);
	Group_Destroy(g[1]);
	Group_Destroy(g[2]);
}

TEST__ y_groups_SetBalancedIn3b()
{
	new
		Group:g[3];
	g[0] = Group_Create("Group 1");
	g[1] = Group_Create("Group 2");
	g[2] = Group_Create("Group 3");

	call OnPlayerConnect(0);
	call OnPlayerConnect(1);
	call OnPlayerConnect(2);
	call OnPlayerConnect(3);
	call OnPlayerConnect(4);
	call OnPlayerConnect(5);
	call OnPlayerConnect(6);
	
	Group_SetPlayer(g[0], 0, true);
	Group_SetPlayer(g[0], 1, true);
	Group_SetPlayer(g[1], 2, true);
	Group_SetPlayer(g[1], 3, true);
	Group_SetPlayer(g[2], 4, true);
	Group_SetPlayer(g[2], 5, true);
	
	Group_SetPlayer(g[1], 6, true);

	Group_SetBalancedArray(0, g, sizeof(g));

	ASSERT_EQ(Group_GetCount(g[0]), 2);
	ASSERT_EQ(Group_GetCount(g[1]), 3);
	ASSERT_EQ(Group_GetCount(g[2]), 2);

	call OnPlayerDisconnect(0, 0);
	call OnPlayerDisconnect(1, 0);
	call OnPlayerDisconnect(2, 0);
	call OnPlayerDisconnect(3, 0);
	call OnPlayerDisconnect(4, 0);
	call OnPlayerDisconnect(5, 0);
	call OnPlayerDisconnect(6, 0);

	Group_Destroy(g[0]);
	Group_Destroy(g[1]);
	Group_Destroy(g[2]);
}

TEST__ y_groups_SetBalancedIn3c()
{
	new
		Group:g[3];
	g[0] = Group_Create("Group 1");
	g[1] = Group_Create("Group 2");
	g[2] = Group_Create("Group 3");

	call OnPlayerConnect(0);
	call OnPlayerConnect(1);
	call OnPlayerConnect(2);
	call OnPlayerConnect(3);
	call OnPlayerConnect(4);
	call OnPlayerConnect(5);
	call OnPlayerConnect(6);
	
	Group_SetPlayer(g[0], 0, true);
	Group_SetPlayer(g[0], 1, true);
	Group_SetPlayer(g[1], 2, true);
	Group_SetPlayer(g[1], 3, true);
	Group_SetPlayer(g[2], 4, true);
	Group_SetPlayer(g[2], 5, true);
	
	Group_SetPlayer(g[2], 6, true);

	Group_SetBalancedArray(0, g, sizeof(g));

	ASSERT_EQ(Group_GetCount(g[0]), 2);
	ASSERT_EQ(Group_GetCount(g[1]), 2);
	ASSERT_EQ(Group_GetCount(g[2]), 3);

	call OnPlayerDisconnect(0, 0);
	call OnPlayerDisconnect(1, 0);
	call OnPlayerDisconnect(2, 0);
	call OnPlayerDisconnect(3, 0);
	call OnPlayerDisconnect(4, 0);
	call OnPlayerDisconnect(5, 0);
	call OnPlayerDisconnect(6, 0);

	Group_Destroy(g[0]);
	Group_Destroy(g[1]);
	Group_Destroy(g[2]);
}

TEST__ y_groups_SetBalancedIn4()
{
	new
		Group:g[3];
	g[0] = Group_Create("Group 1");
	g[1] = Group_Create("Group 2");
	g[2] = Group_Create("Group 3");

	call OnPlayerConnect(0);
	call OnPlayerConnect(1);
	call OnPlayerConnect(2);
	call OnPlayerConnect(3);
	call OnPlayerConnect(4);
	call OnPlayerConnect(5);
	call OnPlayerConnect(6);
	
	Group_SetPlayer(g[0], 0, true);
	Group_SetPlayer(g[0], 1, true);
	Group_SetPlayer(g[1], 2, true);
	Group_SetPlayer(g[1], 3, true);
	Group_SetPlayer(g[2], 4, true);
	
	Group_SetPlayer(g[1], 6, true);

	Group_SetBalancedArray(2, g, sizeof(g));

	ASSERT_EQ(Group_GetCount(g[0]), 2);
	ASSERT_EQ(Group_GetCount(g[1]), 3);
	ASSERT_EQ(Group_GetCount(g[2]), 1);

	call OnPlayerDisconnect(0, 0);
	call OnPlayerDisconnect(1, 0);
	call OnPlayerDisconnect(2, 0);
	call OnPlayerDisconnect(3, 0);
	call OnPlayerDisconnect(4, 0);
	call OnPlayerDisconnect(5, 0);
	call OnPlayerDisconnect(6, 0);

	Group_Destroy(g[0]);
	Group_Destroy(g[1]);
	Group_Destroy(g[2]);
}

TEST__ y_groups_SetBalancedSingle()
{
	new
		Group:g1 = Group_Create("Group 1"),
		Group:result = Group:0;
	call OnPlayerConnect(0);
	
	result = Group_SetBalanced(0, g1, Group:11);
	ASSERT_EQ(result, g1);
	
	call OnPlayerDisconnect(0, 0);
	Group_Destroy(g1);
}

TEST__ y_groups_SetBalancedInvalid()
{
	new
		Group:result = Group:0;
	call OnPlayerConnect(0);
	
	result = Group_SetBalanced(0, Group:99, Group:88);
	ASSERT_EQ(result, INVALID_GROUP);
	
	call OnPlayerDisconnect(0, 0);
}

#define Y_GTEST_GROUP_NAME<%0...%1> %0Test%1
#define Y_GTEST_GROUP_LIMIT 123
#define Y_GTEST_GROUP_TAG _

#include "y_groups__include"

#define MASTER 60
#include "..\..\YSI_Core\y_master"

static
	gPl = 0,
	gEl = 0,
	bool:gS = false;

Test_SetPlayer(el, playerid, bool:s)
{
	P:1("Test_SetPlayer called: %d %d %d", el, playerid, s);
	gPl = playerid;
	gEl = el;
	gS = s;
	return 1;
}

TEST__ 0_y_groups_Connect0()
{
	gPl = INVALID_PLAYER_ID;
	gEl = 100;
	gS = false;
	//new
	//	Group:g = Group_Create();
	call OnPlayerConnect(45);
	ASSERT_EQ(gPl, INVALID_PLAYER_ID);
	ASSERT_EQ(gEl, 100);
	ASSERT_EQ(gS, false);
	//printf("%d %d %d", gPl, gEl, gS);
	Test_InitialiseFromGroups(7);
	ASSERT_EQ(gPl, 45);
	ASSERT_EQ(gEl, 7);
	ASSERT_EQ(gS, true);
	call OnPlayerDisconnect(45, 0);
}

TEST__ 0_y_groups_Connect1()
{
	gPl = INVALID_PLAYER_ID;
	gEl = 100;
	gS = false;
	//new
	//	Group:g = Group_Create();
	Test_InitialiseFromGroups(8);
	ASSERT_NE(gPl, INVALID_PLAYER_ID);
	ASSERT_NE(gEl, 100);
	ASSERT_NE(gS, false);
	call OnPlayerConnect(43);
	ASSERT_EQ(gPl, 43);
	ASSERT_EQ(gEl, 8);
	ASSERT_EQ(gS, true);
	call OnPlayerDisconnect(43, 0);
}

TEST__ y_groups_Chains()
{
	new
		Group:g = Group_Create();
	call OnPlayerConnect(44);
	ASSERT_FALSE(Group_GetPlayer(g, 44));
	Group_SetGlobalGroup(g, true);
	ASSERT_TRUE(Group_GetPlayer(g, 44));
	call OnPlayerDisconnect(44, 0);
}

TEST__ y_groups_Children0()
{
	new
		Group:g0 = Group_Create();
	ASSERT(!Group_GetGlobalGroup(g0));
	Group_Destroy(g0);
}

TEST__ y_groups_Children1()
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

TEST__ y_groups_Children2()
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

TEST__ y_groups_Children3()
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

TEST__ y_groups_Children4()
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

TEST__ y_groups_Children5()
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

TEST__ y_groups_Children6()
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

TEST__ y_groups_Children7()
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

TEST__ y_groups_ChildIterator0()
{
	new
		Group:g0 = Group_Create(),
		Group:g1 = Group_Create(),
		Group:g2 = Group_Create();
	Group_AddChild(g0, g1);
	Group_AddChild(g0, g2);
	new
		total = 0;
	FOREACH__ (new Group:g : GroupChild(g0))
	{
		++total;
	}
	ASSERT_EQ(total, 2);
	Group_Destroy(g0),
	Group_Destroy(g1),
	Group_Destroy(g2);
}

TEST__ y_groups_ChildIterator1()
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
	FOREACH__ (new Group:g : GroupChild(g0))
	{
		Group_Destroy(g);
	}
	ASSERT(Group_IsValid(g0));
	ASSERT(!Group_IsValid(g1));
	ASSERT(!Group_IsValid(g2));
	Group_Destroy(g0),
	ASSERT(!Group_IsValid(g0));
}

TEST__ y_groups_ChildIterator2()
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
	FOREACH__ (new Group:g : GroupChild[g0])
	{
		Group_Destroy(g);
		++total;
	}
	ASSERT_EQ(total, 2);
	ASSERT(Group_IsValid(g0));
	ASSERT(!Group_IsValid(g1));
	ASSERT(!Group_IsValid(g2));
	Group_Destroy(g0),
	ASSERT(!Group_IsValid(g0));
}

TEST__ y_groups_Iterator0()
{
	new
		Group:g0 = Group_Create(),
		Group:g1 = Group_Create(),
		Group:g2 = Group_Create();
	new
		total = 0;
	FOREACH__ (new Group:g : CreatedGroup)
	{
		++total;
	}
	ASSERT(total >= 3);
	total = 0;
	FOREACH__ (new Group:g : CreatedGroup())
	{
		++total;
	}
	ASSERT(total >= 3);
	Group_Destroy(g0),
	Group_Destroy(g1),
	Group_Destroy(g2);
}

