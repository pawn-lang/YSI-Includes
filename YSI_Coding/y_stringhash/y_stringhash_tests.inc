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
	ASSERT_EQ(h0, -1);
	ASSERT_EQ(h1, 2166136261);
	ASSERT_EQ(h2, 2166136261);
	h1 = _H@b(),
	h2 = _H@f(),
	h0 = _H@a();
	ASSERT_EQ(h1, -1);
	ASSERT_EQ(h2, 2166136261);
	ASSERT_EQ(h0, 2166136261);
	h2 = YHash("", .type = hash_bernstein),
	h0 = YHash("", .type = hash_fnv1),
	h1 = YHash("", .type = hash_fnv1a);
	ASSERT_EQ(h2, -1);
	ASSERT_EQ(h0, 2166136261);
	ASSERT_EQ(h1, 2166136261);
	h2 = _H<>,
	h0 = _H();
	ASSERT_EQ(h2, -1);
	ASSERT_EQ(h0, -1);
}

TEST__ y_stringhash__Chars0()
{
	new
		hh;
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
		hh;
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
		hh;
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
		hh;
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
		hh;
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
		h0,
		h1;
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

