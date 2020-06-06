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

TEST__ y_stringhash__Empty()
{
	new
		h0 = _H@b<>,
		h1 = _H@f<>,
		h2 = _H@a<>;
	ASSERT_EQ(h0, 5381);
	ASSERT_EQ(h1, 2166136261);
	ASSERT_EQ(h2, 2166136261);
	h1 = _H@b(),
	h2 = _H@f(),
	h0 = _H@a();
	ASSERT_EQ(h1, 5381);
	ASSERT_EQ(h2, 2166136261);
	ASSERT_EQ(h0, 2166136261);
	h2 = YHash("", true, .type = hash_bernstein),
	h0 = YHash("", true, .type = hash_fnv1),
	h1 = YHash("", true, .type = hash_fnv1a);
	ASSERT_EQ(h2, 5381);
	ASSERT_EQ(h0, 2166136261);
	ASSERT_EQ(h1, 2166136261);
	h2 = _H<>,
	h0 = _H();
	ASSERT_EQ(h2, 5381);
	ASSERT_EQ(h0, 5381);
	h0 = _I@b<>,
	h1 = _I@f<>,
	h2 = _I@a<>;
	ASSERT_EQ(h0, 5381);
	ASSERT_EQ(h1, 2166136261);
	ASSERT_EQ(h2, 2166136261);
	h1 = _I@b(),
	h2 = _I@f(),
	h0 = _I@a();
	ASSERT_EQ(h1, 5381);
	ASSERT_EQ(h2, 2166136261);
	ASSERT_EQ(h0, 2166136261);
	h2 = YHash("", false, .type = hash_bernstein),
	h0 = YHash("", false, .type = hash_fnv1),
	h1 = YHash("", false, .type = hash_fnv1a);
	ASSERT_EQ(h2, 5381);
	ASSERT_EQ(h0, 2166136261);
	ASSERT_EQ(h1, 2166136261);
	h2 = _I<>,
	h0 = _I();
	ASSERT_EQ(h2, 5381);
	ASSERT_EQ(h0, 5381);
}

TEST__ y_stringhash__Chars0()
{
	new
		hh = 0;
	hh = _H<aabbccddeeff>;
	ASSERT_EQ(hh, YHash("aabbccddeeff", .type = hash_bernstein));
	hh = _H<gghhiijjkkll>;
	ASSERT_EQ(hh, YHash("gghhiijjkkll", .type = hash_bernstein));
	hh = _H<mmnnooppqqrr>;
	ASSERT_EQ(hh, YHash("mmnnooppqqrr", .type = hash_bernstein));
	hh = _H<ssttuuvvwwxx>;
	ASSERT_EQ(hh, YHash("ssttuuvvwwxx", .type = hash_bernstein));
	hh = _H<yyzz00112233>;
	ASSERT_EQ(hh, YHash("yyzz00112233", .type = hash_bernstein));
	hh = _H<445566778899>;
	ASSERT_EQ(hh, YHash("445566778899", .type = hash_bernstein));
	hh = _H<AABBCCDDEEFF>;
	ASSERT_EQ(hh, YHash("AABBCCDDEEFF", .type = hash_bernstein));
	hh = _H<GGHHIIJJKKLL>;
	ASSERT_EQ(hh, YHash("GGHHIIJJKKLL", .type = hash_bernstein));
	hh = _H<MMNNOOPPQQRR>;
	ASSERT_EQ(hh, YHash("MMNNOOPPQQRR", .type = hash_bernstein));
	hh = _H<SSTTUUVVWWXX>;
	ASSERT_EQ(hh, YHash("SSTTUUVVWWXX", .type = hash_bernstein));
	hh = _H<YYZZ  @@__yh>;
	ASSERT_EQ(hh, YHash("YYZZ  @@__yh", .type = hash_bernstein));
	hh = _I<aabbccddeeff>;
	ASSERT_EQ(hh, YHash("aabbccddeeff", .sensitive = false, .type = hash_bernstein));
	hh = _I<gghhiijjkkll>;
	ASSERT_EQ(hh, YHash("gghhiijjkkll", .sensitive = false, .type = hash_bernstein));
	hh = _I<mmnnooppqqrr>;
	ASSERT_EQ(hh, YHash("mmnnooppqqrr", .sensitive = false, .type = hash_bernstein));
	hh = _I<ssttuuvvwwxx>;
	ASSERT_EQ(hh, YHash("ssttuuvvwwxx", .sensitive = false, .type = hash_bernstein));
	hh = _I<yyzz00112233>;
	ASSERT_EQ(hh, YHash("yyzz00112233", .sensitive = false, .type = hash_bernstein));
	hh = _I<445566778899>;
	ASSERT_EQ(hh, YHash("445566778899", .sensitive = false, .type = hash_bernstein));
	hh = _I<AABBCCDDEEFF>;
	ASSERT_EQ(hh, YHash("AABBCCDDEEFF", .sensitive = false, .type = hash_bernstein));
	hh = _I<GGHHIIJJKKLL>;
	ASSERT_EQ(hh, YHash("GGHHIIJJKKLL", .sensitive = false, .type = hash_bernstein));
	hh = _I<MMNNOOPPQQRR>;
	ASSERT_EQ(hh, YHash("MMNNOOPPQQRR", .sensitive = false, .type = hash_bernstein));
	hh = _I<SSTTUUVVWWXX>;
	ASSERT_EQ(hh, YHash("SSTTUUVVWWXX", .sensitive = false, .type = hash_bernstein));
	hh = _I<YYZZ  @@__yh>;
	ASSERT_EQ(hh, YHash("YYZZ  @@__yh", .sensitive = false, .type = hash_bernstein));
	// Ignore cases.
	hh = _I<aabbccddeeff>;
	ASSERT_EQ(hh, YHash("AABBCCDDEEFF", .sensitive = false, .type = hash_bernstein));
	hh = _I<gghhiijjkkll>;
	ASSERT_EQ(hh, YHash("gghhiijjkkll", .sensitive = false, .type = hash_bernstein));
	hh = _I<mmnnooppqqrr>;
	ASSERT_EQ(hh, YHash("MMNNOOPPQQRR", .sensitive = false, .type = hash_bernstein));
	hh = _I<ssttuuvvwwxx>;
	ASSERT_EQ(hh, YHash("SSTTUUVVWWXX", .sensitive = false, .type = hash_bernstein));
	hh = _I<yyzz00112233>;
	ASSERT_EQ(hh, YHash("YYZZ00112233", .sensitive = false, .type = hash_bernstein));
	hh = _I<AABBCCDDEEFF>;
	ASSERT_EQ(hh, YHash("aabbccddeeff", .sensitive = false, .type = hash_bernstein));
	hh = _I<GGHHIIJJKKLL>;
	ASSERT_EQ(hh, YHash("GGHHIIJJKKLL", .sensitive = false, .type = hash_bernstein));
	hh = _I<MMNNOOPPQQRR>;
	ASSERT_EQ(hh, YHash("mmnnooppqqrr", .sensitive = false, .type = hash_bernstein));
	hh = _I<SSTTUUVVWWXX>;
	ASSERT_EQ(hh, YHash("ssttuuvvwwxx", .sensitive = false, .type = hash_bernstein));
	hh = _I<YYZZ  @@__yh>;
	ASSERT_EQ(hh, YHash("yyzz  @@__yh", .sensitive = false, .type = hash_bernstein));
}

TEST__ y_stringhash__Chars1()
{
	new
		hh = 0;
	hh = _H@f<aabbccddeeff>;
	ASSERT_EQ(hh, YHash("aabbccddeeff", .type = hash_fnv1));
	hh = _H@f<gghhiijjkkll>;
	ASSERT_EQ(hh, YHash("gghhiijjkkll", .type = hash_fnv1));
	hh = _H@f<mmnnooppqqrr>;
	ASSERT_EQ(hh, YHash("mmnnooppqqrr", .type = hash_fnv1));
	hh = _H@f<ssttuuvvwwxx>;
	ASSERT_EQ(hh, YHash("ssttuuvvwwxx", .type = hash_fnv1));
	hh = _H@f<yyzz00112233>;
	ASSERT_EQ(hh, YHash("yyzz00112233", .type = hash_fnv1));
	hh = _H@f<445566778899>;
	ASSERT_EQ(hh, YHash("445566778899", .type = hash_fnv1));
	hh = _H@f<AABBCCDDEEFF>;
	ASSERT_EQ(hh, YHash("AABBCCDDEEFF", .type = hash_fnv1));
	hh = _H@f<GGHHIIJJKKLL>;
	ASSERT_EQ(hh, YHash("GGHHIIJJKKLL", .type = hash_fnv1));
	hh = _H@f<MMNNOOPPQQRR>;
	ASSERT_EQ(hh, YHash("MMNNOOPPQQRR", .type = hash_fnv1));
	hh = _H@f<SSTTUUVVWWXX>;
	ASSERT_EQ(hh, YHash("SSTTUUVVWWXX", .type = hash_fnv1));
	hh = _H@f<YYZZ  @@__yh>;
	ASSERT_EQ(hh, YHash("YYZZ  @@__yh", .type = hash_fnv1));
	hh = _I@f<aabbccddeeff>;
	ASSERT_EQ(hh, YHash("aabbccddeeff", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<gghhiijjkkll>;
	ASSERT_EQ(hh, YHash("gghhiijjkkll", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<mmnnooppqqrr>;
	ASSERT_EQ(hh, YHash("mmnnooppqqrr", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<ssttuuvvwwxx>;
	ASSERT_EQ(hh, YHash("ssttuuvvwwxx", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<yyzz00112233>;
	ASSERT_EQ(hh, YHash("yyzz00112233", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<445566778899>;
	ASSERT_EQ(hh, YHash("445566778899", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<AABBCCDDEEFF>;
	ASSERT_EQ(hh, YHash("AABBCCDDEEFF", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<GGHHIIJJKKLL>;
	ASSERT_EQ(hh, YHash("GGHHIIJJKKLL", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<MMNNOOPPQQRR>;
	ASSERT_EQ(hh, YHash("MMNNOOPPQQRR", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<SSTTUUVVWWXX>;
	ASSERT_EQ(hh, YHash("SSTTUUVVWWXX", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<YYZZ  @@__yh>;
	ASSERT_EQ(hh, YHash("YYZZ  @@__yh", .sensitive = false, .type = hash_fnv1));
	// Ignore cases.
	hh = _I@f<aabbccddeeff>;
	ASSERT_EQ(hh, YHash("AABBCCDDEEFF", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<gghhiijjkkll>;
	ASSERT_EQ(hh, YHash("gghhiijjkkll", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<mmnnooppqqrr>;
	ASSERT_EQ(hh, YHash("MMNNOOPPQQRR", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<ssttuuvvwwxx>;
	ASSERT_EQ(hh, YHash("SSTTUUVVWWXX", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<yyzz00112233>;
	ASSERT_EQ(hh, YHash("YYZZ00112233", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<AABBCCDDEEFF>;
	ASSERT_EQ(hh, YHash("aabbccddeeff", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<GGHHIIJJKKLL>;
	ASSERT_EQ(hh, YHash("GGHHIIJJKKLL", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<MMNNOOPPQQRR>;
	ASSERT_EQ(hh, YHash("mmnnooppqqrr", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<SSTTUUVVWWXX>;
	ASSERT_EQ(hh, YHash("ssttuuvvwwxx", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<YYZZ  @@__yh>;
	ASSERT_EQ(hh, YHash("yyzz  @@__yh", .sensitive = false, .type = hash_fnv1));
}

TEST__ y_stringhash__Chars2()
{
	new
		hh = 0;
	hh = _H@a<aabbccddeeff>;
	ASSERT_EQ(hh, YHash("aabbccddeeff", .type = hash_fnv1a));
	hh = _H@a<gghhiijjkkll>;
	ASSERT_EQ(hh, YHash("gghhiijjkkll", .type = hash_fnv1a));
	hh = _H@a<mmnnooppqqrr>;
	ASSERT_EQ(hh, YHash("mmnnooppqqrr", .type = hash_fnv1a));
	hh = _H@a<ssttuuvvwwxx>;
	ASSERT_EQ(hh, YHash("ssttuuvvwwxx", .type = hash_fnv1a));
	hh = _H@a<yyzz00112233>;
	ASSERT_EQ(hh, YHash("yyzz00112233", .type = hash_fnv1a));
	hh = _H@a<445566778899>;
	ASSERT_EQ(hh, YHash("445566778899", .type = hash_fnv1a));
	hh = _H@a<AABBCCDDEEFF>;
	ASSERT_EQ(hh, YHash("AABBCCDDEEFF", .type = hash_fnv1a));
	hh = _H@a<GGHHIIJJKKLL>;
	ASSERT_EQ(hh, YHash("GGHHIIJJKKLL", .type = hash_fnv1a));
	hh = _H@a<MMNNOOPPQQRR>;
	ASSERT_EQ(hh, YHash("MMNNOOPPQQRR", .type = hash_fnv1a));
	hh = _H@a<SSTTUUVVWWXX>;
	ASSERT_EQ(hh, YHash("SSTTUUVVWWXX", .type = hash_fnv1a));
	hh = _H@a<YYZZ  @@__yh>;
	ASSERT_EQ(hh, YHash("YYZZ  @@__yh", .type = hash_fnv1a));
	hh = _I@a<aabbccddeeff>;
	ASSERT_EQ(hh, YHash("aabbccddeeff", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<gghhiijjkkll>;
	ASSERT_EQ(hh, YHash("gghhiijjkkll", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<mmnnooppqqrr>;
	ASSERT_EQ(hh, YHash("mmnnooppqqrr", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<ssttuuvvwwxx>;
	ASSERT_EQ(hh, YHash("ssttuuvvwwxx", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<yyzz00112233>;
	ASSERT_EQ(hh, YHash("yyzz00112233", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<445566778899>;
	ASSERT_EQ(hh, YHash("445566778899", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<AABBCCDDEEFF>;
	ASSERT_EQ(hh, YHash("AABBCCDDEEFF", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<GGHHIIJJKKLL>;
	ASSERT_EQ(hh, YHash("GGHHIIJJKKLL", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<MMNNOOPPQQRR>;
	ASSERT_EQ(hh, YHash("MMNNOOPPQQRR", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<SSTTUUVVWWXX>;
	ASSERT_EQ(hh, YHash("SSTTUUVVWWXX", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<YYZZ  @@__yh>;
	ASSERT_EQ(hh, YHash("YYZZ  @@__yh", .sensitive = false, .type = hash_fnv1a));
	// Ignore cases.
	hh = _I@a<aabbccddeeff>;
	ASSERT_EQ(hh, YHash("AABBCCDDEEFF", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<gghhiijjkkll>;
	ASSERT_EQ(hh, YHash("gghhiijjkkll", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<mmnnooppqqrr>;
	ASSERT_EQ(hh, YHash("MMNNOOPPQQRR", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<ssttuuvvwwxx>;
	ASSERT_EQ(hh, YHash("SSTTUUVVWWXX", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<yyzz00112233>;
	ASSERT_EQ(hh, YHash("YYZZ00112233", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<AABBCCDDEEFF>;
	ASSERT_EQ(hh, YHash("aabbccddeeff", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<GGHHIIJJKKLL>;
	ASSERT_EQ(hh, YHash("GGHHIIJJKKLL", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<MMNNOOPPQQRR>;
	ASSERT_EQ(hh, YHash("mmnnooppqqrr", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<SSTTUUVVWWXX>;
	ASSERT_EQ(hh, YHash("ssttuuvvwwxx", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<YYZZ  @@__yh>;
	ASSERT_EQ(hh, YHash("yyzz  @@__yh", .sensitive = false, .type = hash_fnv1a));
}

TEST__ y_stringhash__Letters1()
{
	new
		hh = 0;
	hh = _I<A>;
	ASSERT_EQ(hh, YHash("A", .sensitive = false));
	hh = _I<A>;
	ASSERT_EQ(hh, YHash("a", .sensitive = false));
	hh = _I<a>;
	ASSERT_EQ(hh, YHash("A", .sensitive = false));
	hh = _I<a>;
	ASSERT_EQ(hh, YHash("a", .sensitive = false));
	hh = _I<0>;
	ASSERT_EQ(hh, YHash("0", .sensitive = false));
	hh = _I<_>;
	ASSERT_EQ(hh, YHash("_", .sensitive = false));
	hh = _I<@>;
	ASSERT_EQ(hh, YHash("@", .sensitive = false));
}

TEST__ y_stringhash__Letters2()
{
	new
		hh = 0;
	hh = _H<A>;
	ASSERT_EQ(hh, YHash("A"));
	hh = _H<A>;
	ASSERT_NE(hh, YHash("a"));
	hh = _H<a>;
	ASSERT_NE(hh, YHash("A"));
	hh = _H<a>;
	ASSERT_EQ(hh, YHash("a"));
	hh = _H<0>;
	ASSERT_EQ(hh, YHash("0"));
	hh = _H<_>;
	ASSERT_EQ(hh, YHash("_"));
	hh = _H<@>;
	ASSERT_EQ(hh, YHash("@"));
}

TEST__ y_stringhash__case()
{
	new
		h0 = 0,
		h1 = 0;
	h0 = _H<HEllO>;
	h1 = _H<HELLO>;
	ASSERT_NE(h0, h1);
	h0 = _I<HEllO>;
	h1 = _I<HELLO>;
	ASSERT_EQ(h0, h1);
	h0 = _H@b<heLLo>;
	h1 = _H@b<HELLO>;
	ASSERT_NE(h0, h1);
	h0 = _I@b<heLLo>;
	h1 = _I@b<HELLO>;
	ASSERT_EQ(h0, h1);
	h0 = _H@f<hello>;
	h1 = _H@f<HELLO>;
	ASSERT_NE(h0, h1);
	h0 = _I@f<hello>;
	h1 = _I@f<HELLO>;
	ASSERT_EQ(h0, h1);
	h0 = _H@a<hElLo>;
	h1 = _H@a<HELLO>;
	ASSERT_NE(h0, h1);
	h0 = _I@a<hElLo>;
	h1 = _I@a<HELLO>;
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H1()
{
	new
		h0 = _H<hello>,
		h1 = _H<there>;
	ASSERT_NE(h0, h1);
}

TEST__ y_stringhash__I1()
{
	new
		h0 = _I<hello>,
		h1 = _I<HelLo>;
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H2()
{
	new
		h0 = _H(h,e,l,l,o),
		h1 = _H(t,h,e,r,e);
	ASSERT_NE(h0, h1);
}

TEST__ y_stringhash__I2()
{
	new
		h0 = _I(h,e,l,l,o),
		h1 = _I(H,E,L,L,O);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H3()
{
	new
		h0 = _H@b<hello>,
		h1 = _H@b<there>;
	ASSERT_NE(h0, h1);
}

TEST__ y_stringhash__I3()
{
	new
		h0 = _I@b<hello>,
		h1 = _I@b<HelLo>;
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H4()
{
	new
		h0 = _H@b(h,e,l,l,o),
		h1 = _H@b(t,h,e,r,e);
	ASSERT_NE(h0, h1);
}

TEST__ y_stringhash__I4()
{
	new
		h0 = _I@b(h,e,l,l,o),
		h1 = _I@b(H,E,L,L,O);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H5()
{
	new
		h0 = _H@f<hello>,
		h1 = _H@f<there>;
	ASSERT_NE(h0, h1);
}

TEST__ y_stringhash__I5()
{
	new
		h0 = _I@f<hello>,
		h1 = _I@f<HelLo>;
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H6()
{
	new
		h0 = _H@f(h,e,l,l,o),
		h1 = _H@f(t,h,e,r,e);
	ASSERT_NE(h0, h1);
}

TEST__ y_stringhash__I6()
{
	new
		h0 = _I@f(h,e,l,l,o),
		h1 = _I@f(H,E,L,L,O);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H7()
{
	new
		h0 = _H@a<hello>,
		h1 = _H@a<there>;
	ASSERT_NE(h0, h1);
}

TEST__ y_stringhash__I7()
{
	new
		h0 = _I@a<hello>,
		h1 = _I@a<HelLo>;
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H8()
{
	new
		h0 = _H@a(h,e,l,l,o),
		h1 = _H@a(t,h,e,r,e);
	ASSERT_NE(h0, h1);
}

TEST__ y_stringhash__I8()
{
	new
		h0 = _I@a(h,e,l,l,o),
		h1 = _I@a(H,E,L,L,O);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H3e()
{
	new
		h0 = _H@b<hello>,
		h1 = YHash("hello", .type = hash_bernstein);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I3e()
{
	new
		h0 = _I@b<hello>,
		h1 = YHash("hello", .type = hash_bernstein, .sensitive = false);
	//printf("%04x%04x %04x%04x", h0 >>> 16, h0 & 0xFFFF, h1 >>> 16, h1 & 0xFFFF);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H4e()
{
	new
		h0 = _H@b(h,e,l,l,o),
		h1 = YHash("hello", .type = hash_bernstein);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I4e()
{
	new
		h0 = _I@b(h,e,l,l,o),
		h1 = YHash("hello", .type = hash_bernstein, .sensitive = false);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H5e()
{
	new
		h0 = _H@f<hello>,
		h1 = YHash("hello", .type = hash_fnv1);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I5e()
{
	new
		h0 = _I@f<hello>,
		h1 = YHash("hello", .type = hash_fnv1, .sensitive = false);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H6e()
{
	new
		h0 = _H@f(h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I6e()
{
	new
		h0 = _I@f(h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1, .sensitive = false);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H7e()
{
	new
		h0 = _H@a<hello>,
		h1 = YHash("hello", .type = hash_fnv1a);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I7e()
{
	new
		h0 = _I@a<hello>,
		h1 = YHash("hello", .type = hash_fnv1a, .sensitive = false);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H8e()
{
	new
		h0 = _H@a(h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1a);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I8e()
{
	new
		h0 = _I@a(h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1a, .sensitive = false);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H3d()
{
	new
		h0 = HASH:bernstein<hello>,
		h1 = YHash("hello", .type = hash_bernstein);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I3d()
{
	new
		h0 = HASHi:bernstein<hello>,
		h1 = YHash("hello", .type = hash_bernstein, .sensitive = false);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H4d()
{
	new
		h0 = HASH(bernstein,h,e,l,l,o),
		h1 = YHash("hello", .type = hash_bernstein);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I4d()
{
	new
		h0 = HASHi(bernstein,h,e,l,l,o),
		h1 = YHash("hello", .type = hash_bernstein, .sensitive = false);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H5d()
{
	new
		h0 = HASH:fnv1<hello>,
		h1 = YHash("hello", .type = hash_fnv1);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I5d()
{
	new
		h0 = HASHi:fnv1<hello>,
		h1 = YHash("hello", .type = hash_fnv1, .sensitive = false);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H6d()
{
	new
		h0 = HASH(fnv1,h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I6d()
{
	new
		h0 = HASHi(fnv1,h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1, .sensitive = false);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H7d()
{
	new
		h0 = HASH:fnv1a<hello>,
		h1 = YHash("hello", .type = hash_fnv1a);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I7d()
{
	new
		h0 = HASHi:fnv1a<hello>,
		h1 = YHash("hello", .type = hash_fnv1a, .sensitive = false);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H8d()
{
	new
		h0 = HASH(fnv1a,h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1a);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I8d()
{
	new
		h0 = HASHi(fnv1a,h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1a, .sensitive = false);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H3c()
{
	new
		h0 = HASH:bernstein<hello>,
		h1 = _H(h,e,l,l,o);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I3c()
{
	new
		h0 = HASHi:bernstein<hello>,
		h1 = _I(h,e,L,L,o);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H4c()
{
	new
		h0 = HASH(bernstein,h,e,l,l,o),
		h1 = _H<hello>;
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I4c()
{
	new
		h0 = HASHi(bernstein,h,e,l,l,o),
		h1 = _I<hellO>;
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H5c()
{
	new
		h0 = HASH:fnv1<hello>,
		h1 = _H@f(h,e,l,l,o);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I5c()
{
	new
		h0 = HASHi:fnv1<hello>,
		h1 = _I@f(h,E,l,l,o);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H6c()
{
	new
		h0 = HASH(fnv1,h,e,l,l,o),
		h1 = _H@f<hello>;
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I6c()
{
	new
		h0 = HASHi(fnv1,h,e,l,l,o),
		h1 = _I@f<hElLO>;
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H7c()
{
	new
		h0 = HASH:fnv1a<hello>,
		h1 = _H@a(h,e,l,l,o);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I7c()
{
	new
		h0 = HASHi:fnv1a<hello>,
		h1 = _I@a(H,e,l,l,o);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H8c()
{
	new
		h0 = HASH(fnv1a,h,e,l,l,o),
		h1 = _H@a<hello>;
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__I8c()
{
	new
		h0 = HASHi(fnv1a,h,e,l,l,o),
		h1 = _I@a<HELLO>;
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H3b()
{
	new
		h0 = HASH:bernstein<hello>,
		h1 = HASH:bernstein<there>;
	ASSERT_NE(h0, h1);
}

TEST__ y_stringhash__I3b()
{
	new
		h0 = HASHi:bernstein<hello>,
		h1 = HASHi:bernstein<HelLo>;
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H4b()
{
	new
		h0 = HASH(bernstein,h,e,l,l,o),
		h1 = HASH(bernstein,t,h,e,r,e);
	ASSERT_NE(h0, h1);
}

TEST__ y_stringhash__I4b()
{
	new
		h0 = HASHi(bernstein,h,e,l,l,o),
		h1 = HASHi(bernstein,H,E,L,L,O);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H5b()
{
	new
		h0 = HASH:fnv1<hello>,
		h1 = HASH:fnv1<there>;
	ASSERT_NE(h0, h1);
}

TEST__ y_stringhash__I5b()
{
	new
		h0 = HASHi:fnv1<hello>,
		h1 = HASHi:fnv1<HelLo>;
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H6b()
{
	new
		h0 = HASH(fnv1,h,e,l,l,o),
		h1 = HASH(fnv1,t,h,e,r,e);
	ASSERT_NE(h0, h1);
}

TEST__ y_stringhash__I6b()
{
	new
		h0 = HASHi(fnv1,h,e,l,l,o),
		h1 = HASHi(fnv1,H,E,L,L,O);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H7b()
{
	new
		h0 = HASH:fnv1a<hello>,
		h1 = HASH:fnv1a<there>;
	ASSERT_NE(h0, h1);
}

TEST__ y_stringhash__I7b()
{
	new
		h0 = HASHi:fnv1a<hello>,
		h1 = HASHi:fnv1a<HelLo>;
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash__H8b()
{
	new
		h0 = HASH(fnv1a,h,e,l,l,o),
		h1 = HASH(fnv1a,t,h,e,r,e);
	ASSERT_NE(h0, h1);
}

TEST__ y_stringhash__I8b()
{
	new
		h0 = HASHi(fnv1a,h,e,l,l,o),
		h1 = HASHi(fnv1a,H,E,L,L,O);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash_PackedS()
{
	new
		h0 = YHash("hello", true),
		h1 = YHash(!"hello", true);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash_PackedI()
{
	new
		h0 = YHash(!"HEllo", false),
		h1 = YHash(!"heLLo", false);
	ASSERT_EQ(h0, h1);
}

TEST__ y_stringhash_PackedP()
{
	new
		h0 = YHash("HEllo", false),
		h1 = YHash(!"heLLo", false);
	ASSERT_EQ(h0, h1);
}

static stock _FIXES_Bernstein(const name[])
{
	new
		i = -1,
		ch = 0,
		hash = 5381;
	// In carcols.dat the vehicle names end at ",".  That makes this code
	// very specific to a few use-cases.  It also works for hashing server vars,
	// since they don't have commas.  Now case-insensitive.
	while ((ch = name[++i]) >= '0')
	{
		hash = (hash * 33) ^ (ch | 0x20);
	}
	return hash;
}

TEST__ y_stringhash__fixes_switch()
{
	// Lower-case.
	ASSERT_EQ(0x6A7D4118, YHash("gamemode0", false));
	ASSERT_EQ(0x6A7D4119, YHash("gamemode1", false));
	ASSERT_EQ(0x6A7D411A, YHash("gamemode2", false));
	ASSERT_EQ(0x6A7D411B, YHash("gamemode3", false));
	ASSERT_EQ(0x6A7D411C, YHash("gamemode4", false));
	ASSERT_EQ(0x6A7D411D, YHash("gamemode5", false));
	ASSERT_EQ(0x6A7D411E, YHash("gamemode6", false));
	ASSERT_EQ(0x6A7D411F, YHash("gamemode7", false));
	ASSERT_EQ(0x6A7D4110, YHash("gamemode8", false));
	ASSERT_EQ(0x6A7D4111, YHash("gamemode9", false));
	ASSERT_EQ(0xBA256409, YHash("gamemode10", false));
	ASSERT_EQ(0xBA256408, YHash("gamemode11", false));
	ASSERT_EQ(0xBA25640B, YHash("gamemode12", false));
	ASSERT_EQ(0xBA25640A, YHash("gamemode13", false));
	ASSERT_EQ(0xBA25640D, YHash("gamemode14", false));
	ASSERT_EQ(0xBA25640C, YHash("gamemode15", false));
	ASSERT_EQ(0x740D30D2, YHash("worldtime", false));
	ASSERT_EQ(0x2FB2D3BF, YHash("version", false));
	ASSERT_EQ(0xFBE0D5FE, YHash("lagcomp", false));
	ASSERT_EQ(0x19BECDF7, YHash("logtimeformat", false));
	ASSERT_EQ(0x62420997, YHash("nosign", false));
	ASSERT_EQ(0x9D57983F, YHash("plugins", false));
	ASSERT_EQ(0x3AFFC879, YHash("filterscripts", false));
	ASSERT_EQ(0xD93377B5, YHash("gamemodetext", false));
	ASSERT_EQ(0x74C01C1D, YHash("weather", false));
	ASSERT_EQ(0xB605A0C3, YHash("gravity", false));
	ASSERT_EQ(0x8FED0775, YHash("rcon\x7F;password", false));
	ASSERT_EQ(0x77E7547E, YHash("weburl", false));
	ASSERT_EQ(0x40736C5E, YHash("mapname", false));
	ASSERT_EQ(0x672924D7, YHash("language", false));
	ASSERT_EQ(0x0E9495C2, YHash("hostname", false));
	ASSERT_EQ(0x5D876F9A, YHash("password", false));
	ASSERT_EQ(0x7C706484, YHash("bind", false));
	// Upper-case.
	ASSERT_EQ(0x6A7D4118, YHash("GAMEMODE0", false));
	ASSERT_EQ(0x6A7D4119, YHash("GAMEMODE1", false));
	ASSERT_EQ(0x6A7D411A, YHash("GAMEMODE2", false));
	ASSERT_EQ(0x6A7D411B, YHash("GAMEMODE3", false));
	ASSERT_EQ(0x6A7D411C, YHash("GAMEMODE4", false));
	ASSERT_EQ(0x6A7D411D, YHash("GAMEMODE5", false));
	ASSERT_EQ(0x6A7D411E, YHash("GAMEMODE6", false));
	ASSERT_EQ(0x6A7D411F, YHash("GAMEMODE7", false));
	ASSERT_EQ(0x6A7D4110, YHash("GAMEMODE8", false));
	ASSERT_EQ(0x6A7D4111, YHash("GAMEMODE9", false));
	ASSERT_EQ(0xBA256409, YHash("GAMEMODE10", false));
	ASSERT_EQ(0xBA256408, YHash("GAMEMODE11", false));
	ASSERT_EQ(0xBA25640B, YHash("GAMEMODE12", false));
	ASSERT_EQ(0xBA25640A, YHash("GAMEMODE13", false));
	ASSERT_EQ(0xBA25640D, YHash("GAMEMODE14", false));
	ASSERT_EQ(0xBA25640C, YHash("GAMEMODE15", false));
	ASSERT_EQ(0x740D30D2, YHash("WORLDTIME", false));
	ASSERT_EQ(0x2FB2D3BF, YHash("VERSION", false));
	ASSERT_EQ(0xFBE0D5FE, YHash("LAGCOMP", false));
	ASSERT_EQ(0x19BECDF7, YHash("LOGTIMEFORMAT", false));
	ASSERT_EQ(0x62420997, YHash("NOSIGN", false));
	ASSERT_EQ(0x9D57983F, YHash("PLUGINS", false));
	ASSERT_EQ(0x3AFFC879, YHash("FILTERSCRIPTS", false));
	ASSERT_EQ(0xD93377B5, YHash("GAMEMODETEXT", false));
	ASSERT_EQ(0x74C01C1D, YHash("WEATHER", false));
	ASSERT_EQ(0xB605A0C3, YHash("GRAVITY", false));
	ASSERT_EQ(0x8FED0775, YHash("RCON\x7F;PASSWORD", false));
	ASSERT_EQ(0x77E7547E, YHash("WEBURL", false));
	ASSERT_EQ(0x40736C5E, YHash("MAPNAME", false));
	ASSERT_EQ(0x672924D7, YHash("LANGUAGE", false));
	ASSERT_EQ(0x0E9495C2, YHash("HOSTNAME", false));
	ASSERT_EQ(0x5D876F9A, YHash("PASSWORD", false));
	ASSERT_EQ(0x7C706484, YHash("BIND", false));
	// Middle-case.
	ASSERT_EQ(0x6A7D4118, YHash("GAmemode0", false));
	ASSERT_EQ(0x6A7D4119, YHash("gAMemode1", false));
	ASSERT_EQ(0x6A7D411A, YHash("gaMEmode2", false));
	ASSERT_EQ(0x6A7D411B, YHash("gamEMode3", false));
	ASSERT_EQ(0x6A7D411C, YHash("gameMOde4", false));
	ASSERT_EQ(0x6A7D411D, YHash("gamemODe5", false));
	ASSERT_EQ(0x6A7D411E, YHash("gamemoDE6", false));
	ASSERT_EQ(0x6A7D411F, YHash("GamemodE7", false));
	ASSERT_EQ(0x6A7D4110, YHash("Gamemode8", false));
	ASSERT_EQ(0x6A7D4111, YHash("gAmemode9", false));
	ASSERT_EQ(0xBA256409, YHash("gaMemode10", false));
	ASSERT_EQ(0xBA256408, YHash("gamEmode11", false));
	ASSERT_EQ(0xBA25640B, YHash("gameMode12", false));
	ASSERT_EQ(0xBA25640A, YHash("gamemOde13", false));
	ASSERT_EQ(0xBA25640D, YHash("gamemoDe14", false));
	ASSERT_EQ(0xBA25640C, YHash("gamemodE15", false));
	ASSERT_EQ(0x740D30D2, YHash("WORLDtime", false));
	ASSERT_EQ(0x2FB2D3BF, YHash("veRSIon", false));
	ASSERT_EQ(0xFBE0D5FE, YHash("lagCOMP", false));
	ASSERT_EQ(0x19BECDF7, YHash("LOGtimeFORMat", false));
	ASSERT_EQ(0x62420997, YHash("noSIGN", false));
	ASSERT_EQ(0x9D57983F, YHash("PLUGins", false));
	ASSERT_EQ(0x3AFFC879, YHash("filterSCRIPTs", false));
	ASSERT_EQ(0xD93377B5, YHash("gameMODEtext", false));
	ASSERT_EQ(0x74C01C1D, YHash("WEATHER", false));
	ASSERT_EQ(0xB605A0C3, YHash("GRAVITY", false));
	ASSERT_EQ(0x8FED0775, YHash("rcon\x7F;PASSword", false));
	ASSERT_EQ(0x77E7547E, YHash("WeBuRl", false));
	ASSERT_EQ(0x40736C5E, YHash("mApNaMe", false));
	ASSERT_EQ(0x672924D7, YHash("LaNgUaGe", false));
	ASSERT_EQ(0x0E9495C2, YHash("hOsTnAmE", false));
	ASSERT_EQ(0x5D876F9A, YHash("PAssWOrd", false));
	ASSERT_EQ(0x7C706484, YHash("biND", false));
	// Fixes.
	ASSERT_EQ(0x6A7D4118, _FIXES_Bernstein("GAmemode0"));
	ASSERT_EQ(0x6A7D4119, _FIXES_Bernstein("gAMemode1"));
	ASSERT_EQ(0x6A7D411A, _FIXES_Bernstein("gaMEmode2"));
	ASSERT_EQ(0x6A7D411B, _FIXES_Bernstein("gamEMode3"));
	ASSERT_EQ(0x6A7D411C, _FIXES_Bernstein("gameMOde4"));
	ASSERT_EQ(0x6A7D411D, _FIXES_Bernstein("gamemODe5"));
	ASSERT_EQ(0x6A7D411E, _FIXES_Bernstein("gamemoDE6"));
	ASSERT_EQ(0x6A7D411F, _FIXES_Bernstein("GamemodE7"));
	ASSERT_EQ(0x6A7D4110, _FIXES_Bernstein("Gamemode8"));
	ASSERT_EQ(0x6A7D4111, _FIXES_Bernstein("gAmemode9"));
	ASSERT_EQ(0xBA256409, _FIXES_Bernstein("gaMemode10"));
	ASSERT_EQ(0xBA256408, _FIXES_Bernstein("gamEmode11"));
	ASSERT_EQ(0xBA25640B, _FIXES_Bernstein("gameMode12"));
	ASSERT_EQ(0xBA25640A, _FIXES_Bernstein("gamemOde13"));
	ASSERT_EQ(0xBA25640D, _FIXES_Bernstein("gamemoDe14"));
	ASSERT_EQ(0xBA25640C, _FIXES_Bernstein("gamemodE15"));
	ASSERT_EQ(0x740D30D2, _FIXES_Bernstein("WORLDtime"));
	ASSERT_EQ(0x2FB2D3BF, _FIXES_Bernstein("veRSIon"));
	ASSERT_EQ(0xFBE0D5FE, _FIXES_Bernstein("lagCOMP"));
	ASSERT_EQ(0x19BECDF7, _FIXES_Bernstein("LOGtimeFORMat"));
	ASSERT_EQ(0x62420997, _FIXES_Bernstein("noSIGN"));
	ASSERT_EQ(0x9D57983F, _FIXES_Bernstein("PLUGins"));
	ASSERT_EQ(0x3AFFC879, _FIXES_Bernstein("filterSCRIPTs"));
	ASSERT_EQ(0xD93377B5, _FIXES_Bernstein("gameMODEtext"));
	ASSERT_EQ(0x74C01C1D, _FIXES_Bernstein("WEATHER"));
	ASSERT_EQ(0xB605A0C3, _FIXES_Bernstein("GRAVITY"));
	ASSERT_EQ(0x8FED0775, _FIXES_Bernstein("rcon_PASSword"));
	ASSERT_EQ(0x77E7547E, _FIXES_Bernstein("WeBuRl"));
	ASSERT_EQ(0x40736C5E, _FIXES_Bernstein("mApNaMe"));
	ASSERT_EQ(0x672924D7, _FIXES_Bernstein("LaNgUaGe"));
	ASSERT_EQ(0x0E9495C2, _FIXES_Bernstein("hOsTnAmE"));
	ASSERT_EQ(0x5D876F9A, _FIXES_Bernstein("PAssWOrd"));
	ASSERT_EQ(0x7C706484, _FIXES_Bernstein("biND"));
	
	ASSERT_EQ(0xF59D7562, _FIXES_Bernstein("cookielogging"));
	ASSERT_EQ(0x5DD3AB50, _FIXES_Bernstein("concookies"));
	ASSERT_EQ(0x24DF3EEB, _FIXES_Bernstein("db_log_queries"));
	ASSERT_EQ(0xD8FC2F7F, _FIXES_Bernstein("db_logging"));
	ASSERT_EQ(0xCEF27485, _FIXES_Bernstein("conseedtime"));
	ASSERT_EQ(0x0C43D2DD, _FIXES_Bernstein("lagcompmode"));
	ASSERT_EQ(0xB3AAF0EC, _FIXES_Bernstein("minconnectiontime"));
	ASSERT_EQ(0x2E17DD8D, _FIXES_Bernstein("playertimeout"));
	ASSERT_EQ(0xED02304A, _FIXES_Bernstein("ackslimit"));
	ASSERT_EQ(0x55A5C0C8, _FIXES_Bernstein("messageslimit"));
	ASSERT_EQ(0xBD012555, _FIXES_Bernstein("messageholelimit"));
	ASSERT_EQ(0x16C6DD58, _FIXES_Bernstein("chatlogging"));
	ASSERT_EQ(0x9420F5BA, _FIXES_Bernstein("weapon_rate"));
	ASSERT_EQ(0x5C8B384F, _FIXES_Bernstein("incar_rate"));
	ASSERT_EQ(0x01F89DEB, _FIXES_Bernstein("onfoot_rate"));
	ASSERT_EQ(0x57452FAC, _FIXES_Bernstein("maxnpc"));
	ASSERT_EQ(0x0BAD27EA, _FIXES_Bernstein("sleep"));
	ASSERT_EQ(0x0A9910C4, _FIXES_Bernstein("stream_rate"));
	ASSERT_EQ(0xE20F31D1, _FIXES_Bernstein("maxplayers"));
	
	ASSERT_EQ(0x5F92A936, _FIXES_Bernstein("announce"));
	ASSERT_EQ(0xFB6572C5, _FIXES_Bernstein("lanmode"));
	ASSERT_EQ(0x0B3513EF, _FIXES_Bernstein("query"));
	ASSERT_EQ(0x7C78F2F5, _FIXES_Bernstein("rcon"));
	ASSERT_EQ(0xA300A7ED, _FIXES_Bernstein("logqueries"));
	ASSERT_EQ(0x97EABC6B, _FIXES_Bernstein("timestamp"));
	ASSERT_EQ(0x57CBE04F, _FIXES_Bernstein("myriad"));
	
	ASSERT_EQ(YHash("Gamemode0", false), _FIXES_Bernstein("gAMEMODE0"));
	ASSERT_EQ(YHash("Gamemode1", false), _FIXES_Bernstein("gAMEMODE1"));
	ASSERT_EQ(YHash("Gamemode2", false), _FIXES_Bernstein("gAMEMODE2"));
	ASSERT_EQ(YHash("Gamemode3", false), _FIXES_Bernstein("gAMEMODE3"));
	ASSERT_EQ(YHash("Gamemode4", false), _FIXES_Bernstein("gAMEMODE4"));
	ASSERT_EQ(YHash("Gamemode5", false), _FIXES_Bernstein("gAMEMODE5"));
	ASSERT_EQ(YHash("Gamemode6", false), _FIXES_Bernstein("gAMEMODE6"));
	ASSERT_EQ(YHash("Gamemode7", false), _FIXES_Bernstein("gAMEMODE7"));
	ASSERT_EQ(YHash("Gamemode8", false), _FIXES_Bernstein("gAMEMODE8"));
	ASSERT_EQ(YHash("Gamemode9", false), _FIXES_Bernstein("gAMEMODE9"));
	ASSERT_EQ(YHash("Gamemode10", false), _FIXES_Bernstein("gAMEMODE10"));
	ASSERT_EQ(YHash("Gamemode11", false), _FIXES_Bernstein("gAMEMODE11"));
	ASSERT_EQ(YHash("Gamemode12", false), _FIXES_Bernstein("gAMEMODE12"));
	ASSERT_EQ(YHash("Gamemode13", false), _FIXES_Bernstein("gAMEMODE13"));
	ASSERT_EQ(YHash("Gamemode14", false), _FIXES_Bernstein("gAMEMODE14"));
	ASSERT_EQ(YHash("Gamemode15", false), _FIXES_Bernstein("gAMEMODE15"));
	ASSERT_EQ(YHash("Worldtime", false), _FIXES_Bernstein("wORLDTIME"));
	ASSERT_EQ(YHash("Version", false), _FIXES_Bernstein("vERSION"));
	ASSERT_EQ(YHash("Lagcomp", false), _FIXES_Bernstein("lAGCOMP"));
	ASSERT_EQ(YHash("Logtimeformat", false), _FIXES_Bernstein("lOGTIMEFORMAT"));
	ASSERT_EQ(YHash("Nosign", false), _FIXES_Bernstein("nOSIGN"));
	ASSERT_EQ(YHash("Plugins", false), _FIXES_Bernstein("pLUGINS"));
	ASSERT_EQ(YHash("Filterscripts", false), _FIXES_Bernstein("fILTERSCRIPTS"));
	ASSERT_EQ(YHash("Gamemodetext", false), _FIXES_Bernstein("gAMEMODETEXT"));
	ASSERT_EQ(YHash("Weather", false), _FIXES_Bernstein("wEATHER"));
	ASSERT_EQ(YHash("Gravity", false), _FIXES_Bernstein("gRAVITY"));
	ASSERT_EQ(YHash("Rcon\x7F;password", false), _FIXES_Bernstein("rCON_PASSWORD"));
	ASSERT_EQ(YHash("Weburl", false), _FIXES_Bernstein("wEBURL"));
	ASSERT_EQ(YHash("Mapname", false), _FIXES_Bernstein("mAPNAME"));
	ASSERT_EQ(YHash("Language", false), _FIXES_Bernstein("lANGUAGE"));
	ASSERT_EQ(YHash("Hostname", false), _FIXES_Bernstein("hOSTNAME"));
	ASSERT_EQ(YHash("Password", false), _FIXES_Bernstein("pASSWORD"));
	ASSERT_EQ(YHash("Bind", false), _FIXES_Bernstein("bIND"));
	
	ASSERT_EQ(YHash("Cookielogging", false), _FIXES_Bernstein("cOOKIELOGGING"));
	ASSERT_EQ(YHash("Concookies", false), _FIXES_Bernstein("cONCOOKIES"));
	ASSERT_EQ(YHash("Db\x7F;log\x7F;queries", false), _FIXES_Bernstein("dB_LOG_QUERIES"));
	ASSERT_EQ(YHash("Db\x7F;logging", false), _FIXES_Bernstein("dB_LOGGING"));
	ASSERT_EQ(YHash("Conseedtime", false), _FIXES_Bernstein("cONSEEDTIME"));
	ASSERT_EQ(YHash("Lagcompmode", false), _FIXES_Bernstein("lAGCOMPMODE"));
	ASSERT_EQ(YHash("Minconnectiontime", false), _FIXES_Bernstein("mINCONNECTIONTIME"));
	ASSERT_EQ(YHash("Playertimeout", false), _FIXES_Bernstein("pLAYERTIMEOUT"));
	ASSERT_EQ(YHash("Ackslimit", false), _FIXES_Bernstein("aCKSLIMIT"));
	ASSERT_EQ(YHash("Messageslimit", false), _FIXES_Bernstein("mESSAGESLIMIT"));
	ASSERT_EQ(YHash("Messageholelimit", false), _FIXES_Bernstein("mESSAGEHOLELIMIT"));
	ASSERT_EQ(YHash("Chatlogging", false), _FIXES_Bernstein("cHATLOGGING"));
	ASSERT_EQ(YHash("Weapon\x7F;rate", false), _FIXES_Bernstein("wEAPON_RATE"));
	ASSERT_EQ(YHash("Incar\x7F;rate", false), _FIXES_Bernstein("iNCAR_RATE"));
	ASSERT_EQ(YHash("Onfoot\x7F;rate", false), _FIXES_Bernstein("oNFOOT_RATE"));
	ASSERT_EQ(YHash("Maxnpc", false), _FIXES_Bernstein("mAXNPC"));
	ASSERT_EQ(YHash("Sleep", false), _FIXES_Bernstein("sLEEP"));
	ASSERT_EQ(YHash("Stream\x7F;rate", false), _FIXES_Bernstein("sTREAM_RATE"));
	ASSERT_EQ(YHash("Maxplayers", false), _FIXES_Bernstein("mAXPLAYERS"));
	
	ASSERT_EQ(YHash("Announce", false), _FIXES_Bernstein("aNNOUNCE"));
	ASSERT_EQ(YHash("Lanmode", false), _FIXES_Bernstein("lANMODE"));
	ASSERT_EQ(YHash("Query", false), _FIXES_Bernstein("qUERY"));
	ASSERT_EQ(YHash("Rcon", false), _FIXES_Bernstein("rCON"));
	ASSERT_EQ(YHash("Logqueries", false), _FIXES_Bernstein("lOGQUERIES"));
	ASSERT_EQ(YHash("Timestamp", false), _FIXES_Bernstein("tIMESTAMP"));
	ASSERT_EQ(YHash("Myriad", false), _FIXES_Bernstein("mYRIAD"));
	
	// Print.
	//printf("==========");
	//printf("%04x%04x", _FIXES_Bernstein("GAmemode0") >>> 16, _FIXES_Bernstein("GAmemode0") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("gAMemode1") >>> 16, _FIXES_Bernstein("gAMemode1") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("gaMEmode2") >>> 16, _FIXES_Bernstein("gaMEmode2") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("gamEMode3") >>> 16, _FIXES_Bernstein("gamEMode3") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("gameMOde4") >>> 16, _FIXES_Bernstein("gameMOde4") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("gamemODe5") >>> 16, _FIXES_Bernstein("gamemODe5") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("gamemoDE6") >>> 16, _FIXES_Bernstein("gamemoDE6") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("GamemodE7") >>> 16, _FIXES_Bernstein("GamemodE7") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("Gamemode8") >>> 16, _FIXES_Bernstein("Gamemode8") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("gAmemode9") >>> 16, _FIXES_Bernstein("gAmemode9") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("gaMemode10") >>> 16, _FIXES_Bernstein("gaMemode10") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("gamEmode11") >>> 16, _FIXES_Bernstein("gamEmode11") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("gameMode12") >>> 16, _FIXES_Bernstein("gameMode12") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("gamemOde13") >>> 16, _FIXES_Bernstein("gamemOde13") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("gamemoDe14") >>> 16, _FIXES_Bernstein("gamemoDe14") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("gamemodE15") >>> 16, _FIXES_Bernstein("gamemodE15") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("WORLDtime") >>> 16, _FIXES_Bernstein("WORLDtime") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("veRSIon") >>> 16, _FIXES_Bernstein("veRSIon") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("lagCOMP") >>> 16, _FIXES_Bernstein("lagCOMP") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("LOGtimeFORMat") >>> 16, _FIXES_Bernstein("LOGtimeFORMat") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("noSIGN") >>> 16, _FIXES_Bernstein("noSIGN") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("PLUGins") >>> 16, _FIXES_Bernstein("PLUGins") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("filterSCRIPTs") >>> 16, _FIXES_Bernstein("filterSCRIPTs") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("gameMODEtext") >>> 16, _FIXES_Bernstein("gameMODEtext") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("WEATHER") >>> 16, _FIXES_Bernstein("WEATHER") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("GRAVITY") >>> 16, _FIXES_Bernstein("GRAVITY") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("rcon_PASSword") >>> 16, _FIXES_Bernstein("rcon_PASSword") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("WeBuRl") >>> 16, _FIXES_Bernstein("WeBuRl") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("mApNaMe") >>> 16, _FIXES_Bernstein("mApNaMe") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("LaNgUaGe") >>> 16, _FIXES_Bernstein("LaNgUaGe") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("hOsTnAmE") >>> 16, _FIXES_Bernstein("hOsTnAmE") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("PAssWOrd") >>> 16, _FIXES_Bernstein("PAssWOrd") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("biND") >>> 16, _FIXES_Bernstein("biND") & 0xFFFF);
	//printf("==========");
	//printf("%04x%04x", _FIXES_Bernstein("cookielogging") >>> 16, _FIXES_Bernstein("cookielogging") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("concookies") >>> 16, _FIXES_Bernstein("concookies") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("db_log_queries") >>> 16, _FIXES_Bernstein("db_log_queries") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("db_logging") >>> 16, _FIXES_Bernstein("db_logging") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("conseedtime") >>> 16, _FIXES_Bernstein("conseedtime") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("lagcompmode") >>> 16, _FIXES_Bernstein("lagcompmode") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("minconnectiontime") >>> 16, _FIXES_Bernstein("minconnectiontime") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("playertimeout") >>> 16, _FIXES_Bernstein("playertimeout") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("ackslimit") >>> 16, _FIXES_Bernstein("ackslimit") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("messageslimit") >>> 16, _FIXES_Bernstein("messageslimit") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("messageholelimit") >>> 16, _FIXES_Bernstein("messageholelimit") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("chatlogging") >>> 16, _FIXES_Bernstein("chatlogging") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("weapon_rate") >>> 16, _FIXES_Bernstein("weapon_rate") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("incar_rate") >>> 16, _FIXES_Bernstein("incar_rate") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("onfoot_rate") >>> 16, _FIXES_Bernstein("onfoot_rate") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("maxnpc") >>> 16, _FIXES_Bernstein("maxnpc") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("sleep") >>> 16, _FIXES_Bernstein("sleep") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("stream_rate") >>> 16, _FIXES_Bernstein("stream_rate") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("maxplayers") >>> 16, _FIXES_Bernstein("maxplayers") & 0xFFFF);
	//printf("==========");
	//printf("%04x%04x", _FIXES_Bernstein("announce") >>> 16, _FIXES_Bernstein("announce") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("lanmode") >>> 16, _FIXES_Bernstein("lanmode") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("query") >>> 16, _FIXES_Bernstein("query") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("rcon") >>> 16, _FIXES_Bernstein("rcon") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("logqueries") >>> 16, _FIXES_Bernstein("logqueries") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("timestamp") >>> 16, _FIXES_Bernstein("timestamp") & 0xFFFF);
	//printf("%04x%04x", _FIXES_Bernstein("myriad") >>> 16, _FIXES_Bernstein("myriad") & 0xFFFF);
	//printf("==========");
}

