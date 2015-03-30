/**--------------------------------------------------------------------------**\
					========================================
					 y_stringhash - Fast string comparisons 
					========================================
Description:
	Allows you to hash strings at compile time to use them in a switch.
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI stringhash include.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2011
	the Initial Developer. All Rights Reserved.
	
	Contributors:
		ZeeX, koolk, JoeBullet/Google63, g_aSlice/Slice
	
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
		Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes
			for me to strive to better.
		Pixels^ - Running XScripters where the idea was born.
		Matite - Pestering me to release it and using it.
	
	Very special thanks to:
		Thiadmer - PAWN, whose limits continue to amaze me!
		Kye/Kalcor - SA:MP.
		SA:MP Team past, present and future - SA:MP.
	
Version:
	2.0
Changelog:
	06/03/11:
		Changed the order of some letters to better support numbers in _I.
	01/03/11:
		Rewrote compile-time hashes to not require commas.
	25/10/10:
		Updated comments.
		Added to YSI 1.0.
		Added FNV1 and FNV1a hashes to avoid collisions.
	19/08/10:
		First version.
Functions:
	stock:
		YHash - Generate a string hash at run time.
Definitions:
	_H - Generate a string hash at compile time.
	_I - Generate a case insensitive string hash at compile time.
\**--------------------------------------------------------------------------**/

Test:y_stringhash__Empty()
{
	new
		h0 = _H@b<>,
		h1 = _H@f<>,
		h2 = _H@a<>;
	ASSERT(h0 == -1);
	ASSERT(h1 == 2166136261);
	ASSERT(h2 == 2166136261);
	h1 = _H@b(),
	h2 = _H@f(),
	h0 = _H@a();
	ASSERT(h1 == -1);
	ASSERT(h2 == 2166136261);
	ASSERT(h0 == 2166136261);
	h2 = YHash("", .type = hash_bernstein),
	h0 = YHash("", .type = hash_fnv1),
	h1 = YHash("", .type = hash_fnv1a);
	ASSERT(h2 == -1);
	ASSERT(h0 == 2166136261);
	ASSERT(h1 == 2166136261);
	h2 = _H<>,
	h0 = _H();
	ASSERT(h2 == -1);
	ASSERT(h0 == -1);
}

Test:y_stringhash__Chars0()
{
	new
		hh;
	hh = _H<aabbccddeeff>;
	ASSERT(hh == YHash("aabbccddeeff", .type = hash_bernstein));
	hh = _H<gghhiijjkkll>;
	ASSERT(hh == YHash("gghhiijjkkll", .type = hash_bernstein));
	hh = _H<mmnnooppqqrr>;
	ASSERT(hh == YHash("mmnnooppqqrr", .type = hash_bernstein));
	hh = _H<ssttuuvvwwxx>;
	ASSERT(hh == YHash("ssttuuvvwwxx", .type = hash_bernstein));
	hh = _H<yyzz00112233>;
	ASSERT(hh == YHash("yyzz00112233", .type = hash_bernstein));
	hh = _H<445566778899>;
	ASSERT(hh == YHash("445566778899", .type = hash_bernstein));
	hh = _H<AABBCCDDEEFF>;
	ASSERT(hh == YHash("AABBCCDDEEFF", .type = hash_bernstein));
	hh = _H<GGHHIIJJKKLL>;
	ASSERT(hh == YHash("GGHHIIJJKKLL", .type = hash_bernstein));
	hh = _H<MMNNOOPPQQRR>;
	ASSERT(hh == YHash("MMNNOOPPQQRR", .type = hash_bernstein));
	hh = _H<SSTTUUVVWWXX>;
	ASSERT(hh == YHash("SSTTUUVVWWXX", .type = hash_bernstein));
	hh = _H<YYZZ  @@__yh>;
	ASSERT(hh == YHash("YYZZ  @@__yh", .type = hash_bernstein));
	hh = _I<aabbccddeeff>;
	ASSERT(hh == YHash("aabbccddeeff", .sensitive = false, .type = hash_bernstein));
	hh = _I<gghhiijjkkll>;
	ASSERT(hh == YHash("gghhiijjkkll", .sensitive = false, .type = hash_bernstein));
	hh = _I<mmnnooppqqrr>;
	ASSERT(hh == YHash("mmnnooppqqrr", .sensitive = false, .type = hash_bernstein));
	hh = _I<ssttuuvvwwxx>;
	ASSERT(hh == YHash("ssttuuvvwwxx", .sensitive = false, .type = hash_bernstein));
	hh = _I<yyzz00112233>;
	ASSERT(hh == YHash("yyzz00112233", .sensitive = false, .type = hash_bernstein));
	hh = _I<445566778899>;
	ASSERT(hh == YHash("445566778899", .sensitive = false, .type = hash_bernstein));
	hh = _I<AABBCCDDEEFF>;
	ASSERT(hh == YHash("AABBCCDDEEFF", .sensitive = false, .type = hash_bernstein));
	hh = _I<GGHHIIJJKKLL>;
	ASSERT(hh == YHash("GGHHIIJJKKLL", .sensitive = false, .type = hash_bernstein));
	hh = _I<MMNNOOPPQQRR>;
	ASSERT(hh == YHash("MMNNOOPPQQRR", .sensitive = false, .type = hash_bernstein));
	hh = _I<SSTTUUVVWWXX>;
	ASSERT(hh == YHash("SSTTUUVVWWXX", .sensitive = false, .type = hash_bernstein));
	hh = _I<YYZZ  @@__yh>;
	ASSERT(hh == YHash("YYZZ  @@__yh", .sensitive = false, .type = hash_bernstein));
}

Test:y_stringhash__Chars1()
{
	new
		hh;
	hh = _H@f<aabbccddeeff>;
	ASSERT(hh == YHash("aabbccddeeff", .type = hash_fnv1));
	hh = _H@f<gghhiijjkkll>;
	ASSERT(hh == YHash("gghhiijjkkll", .type = hash_fnv1));
	hh = _H@f<mmnnooppqqrr>;
	ASSERT(hh == YHash("mmnnooppqqrr", .type = hash_fnv1));
	hh = _H@f<ssttuuvvwwxx>;
	ASSERT(hh == YHash("ssttuuvvwwxx", .type = hash_fnv1));
	hh = _H@f<yyzz00112233>;
	ASSERT(hh == YHash("yyzz00112233", .type = hash_fnv1));
	hh = _H@f<445566778899>;
	ASSERT(hh == YHash("445566778899", .type = hash_fnv1));
	hh = _H@f<AABBCCDDEEFF>;
	ASSERT(hh == YHash("AABBCCDDEEFF", .type = hash_fnv1));
	hh = _H@f<GGHHIIJJKKLL>;
	ASSERT(hh == YHash("GGHHIIJJKKLL", .type = hash_fnv1));
	hh = _H@f<MMNNOOPPQQRR>;
	ASSERT(hh == YHash("MMNNOOPPQQRR", .type = hash_fnv1));
	hh = _H@f<SSTTUUVVWWXX>;
	ASSERT(hh == YHash("SSTTUUVVWWXX", .type = hash_fnv1));
	hh = _H@f<YYZZ  @@__yh>;
	ASSERT(hh == YHash("YYZZ  @@__yh", .type = hash_fnv1));
	hh = _I@f<aabbccddeeff>;
	ASSERT(hh == YHash("aabbccddeeff", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<gghhiijjkkll>;
	ASSERT(hh == YHash("gghhiijjkkll", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<mmnnooppqqrr>;
	ASSERT(hh == YHash("mmnnooppqqrr", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<ssttuuvvwwxx>;
	ASSERT(hh == YHash("ssttuuvvwwxx", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<yyzz00112233>;
	ASSERT(hh == YHash("yyzz00112233", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<445566778899>;
	ASSERT(hh == YHash("445566778899", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<AABBCCDDEEFF>;
	ASSERT(hh == YHash("AABBCCDDEEFF", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<GGHHIIJJKKLL>;
	ASSERT(hh == YHash("GGHHIIJJKKLL", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<MMNNOOPPQQRR>;
	ASSERT(hh == YHash("MMNNOOPPQQRR", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<SSTTUUVVWWXX>;
	ASSERT(hh == YHash("SSTTUUVVWWXX", .sensitive = false, .type = hash_fnv1));
	hh = _I@f<YYZZ  @@__yh>;
	ASSERT(hh == YHash("YYZZ  @@__yh", .sensitive = false, .type = hash_fnv1));
}

Test:y_stringhash__Chars2()
{
	new
		hh;
	hh = _H@a<aabbccddeeff>;
	ASSERT(hh == YHash("aabbccddeeff", .type = hash_fnv1a));
	hh = _H@a<gghhiijjkkll>;
	ASSERT(hh == YHash("gghhiijjkkll", .type = hash_fnv1a));
	hh = _H@a<mmnnooppqqrr>;
	ASSERT(hh == YHash("mmnnooppqqrr", .type = hash_fnv1a));
	hh = _H@a<ssttuuvvwwxx>;
	ASSERT(hh == YHash("ssttuuvvwwxx", .type = hash_fnv1a));
	hh = _H@a<yyzz00112233>;
	ASSERT(hh == YHash("yyzz00112233", .type = hash_fnv1a));
	hh = _H@a<445566778899>;
	ASSERT(hh == YHash("445566778899", .type = hash_fnv1a));
	hh = _H@a<AABBCCDDEEFF>;
	ASSERT(hh == YHash("AABBCCDDEEFF", .type = hash_fnv1a));
	hh = _H@a<GGHHIIJJKKLL>;
	ASSERT(hh == YHash("GGHHIIJJKKLL", .type = hash_fnv1a));
	hh = _H@a<MMNNOOPPQQRR>;
	ASSERT(hh == YHash("MMNNOOPPQQRR", .type = hash_fnv1a));
	hh = _H@a<SSTTUUVVWWXX>;
	ASSERT(hh == YHash("SSTTUUVVWWXX", .type = hash_fnv1a));
	hh = _H@a<YYZZ  @@__yh>;
	ASSERT(hh == YHash("YYZZ  @@__yh", .type = hash_fnv1a));
	hh = _I@a<aabbccddeeff>;
	ASSERT(hh == YHash("aabbccddeeff", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<gghhiijjkkll>;
	ASSERT(hh == YHash("gghhiijjkkll", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<mmnnooppqqrr>;
	ASSERT(hh == YHash("mmnnooppqqrr", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<ssttuuvvwwxx>;
	ASSERT(hh == YHash("ssttuuvvwwxx", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<yyzz00112233>;
	ASSERT(hh == YHash("yyzz00112233", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<445566778899>;
	ASSERT(hh == YHash("445566778899", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<AABBCCDDEEFF>;
	ASSERT(hh == YHash("AABBCCDDEEFF", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<GGHHIIJJKKLL>;
	ASSERT(hh == YHash("GGHHIIJJKKLL", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<MMNNOOPPQQRR>;
	ASSERT(hh == YHash("MMNNOOPPQQRR", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<SSTTUUVVWWXX>;
	ASSERT(hh == YHash("SSTTUUVVWWXX", .sensitive = false, .type = hash_fnv1a));
	hh = _I@a<YYZZ  @@__yh>;
	ASSERT(hh == YHash("YYZZ  @@__yh", .sensitive = false, .type = hash_fnv1a));
}

Test:y_stringhash__case()
{
	new
		h0,
		h1;
	h0 = _H<HEllO>;
	h1 = _H<HELLO>;
	ASSERT(h0 != h1);
	h0 = _I<HEllO>;
	h1 = _I<HELLO>;
	ASSERT(h0 == h1);
	h0 = _H@b<heLLo>;
	h1 = _H@b<HELLO>;
	ASSERT(h0 != h1);
	h0 = _I@b<heLLo>;
	h1 = _I@b<HELLO>;
	ASSERT(h0 == h1);
	h0 = _H@f<hello>;
	h1 = _H@f<HELLO>;
	ASSERT(h0 != h1);
	h0 = _I@f<hello>;
	h1 = _I@f<HELLO>;
	ASSERT(h0 == h1);
	h0 = _H@a<hElLo>;
	h1 = _H@a<HELLO>;
	ASSERT(h0 != h1);
	h0 = _I@a<hElLo>;
	h1 = _I@a<HELLO>;
	ASSERT(h0 == h1);
}

Test:y_stringhash__H1()
{
	new
		h0 = _H<hello>,
		h1 = _H<there>;
	ASSERT(h0 != h1);
}

Test:y_stringhash__I1()
{
	new
		h0 = _I<hello>,
		h1 = _I<HelLo>;
	ASSERT(h0 == h1);
}

Test:y_stringhash__H2()
{
	new
		h0 = _H(h,e,l,l,o),
		h1 = _H(t,h,e,r,e);
	ASSERT(h0 != h1);
}

Test:y_stringhash__I2()
{
	new
		h0 = _I(h,e,l,l,o),
		h1 = _I(H,E,L,L,O);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H3()
{
	new
		h0 = _H@b<hello>,
		h1 = _H@b<there>;
	ASSERT(h0 != h1);
}

Test:y_stringhash__I3()
{
	new
		h0 = _I@b<hello>,
		h1 = _I@b<HelLo>;
	ASSERT(h0 == h1);
}

Test:y_stringhash__H4()
{
	new
		h0 = _H@b(h,e,l,l,o),
		h1 = _H@b(t,h,e,r,e);
	ASSERT(h0 != h1);
}

Test:y_stringhash__I4()
{
	new
		h0 = _I@b(h,e,l,l,o),
		h1 = _I@b(H,E,L,L,O);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H5()
{
	new
		h0 = _H@f<hello>,
		h1 = _H@f<there>;
	ASSERT(h0 != h1);
}

Test:y_stringhash__I5()
{
	new
		h0 = _I@f<hello>,
		h1 = _I@f<HelLo>;
	ASSERT(h0 == h1);
}

Test:y_stringhash__H6()
{
	new
		h0 = _H@f(h,e,l,l,o),
		h1 = _H@f(t,h,e,r,e);
	ASSERT(h0 != h1);
}

Test:y_stringhash__I6()
{
	new
		h0 = _I@f(h,e,l,l,o),
		h1 = _I@f(H,E,L,L,O);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H7()
{
	new
		h0 = _H@a<hello>,
		h1 = _H@a<there>;
	ASSERT(h0 != h1);
}

Test:y_stringhash__I7()
{
	new
		h0 = _I@a<hello>,
		h1 = _I@a<HelLo>;
	ASSERT(h0 == h1);
}

Test:y_stringhash__H8()
{
	new
		h0 = _H@a(h,e,l,l,o),
		h1 = _H@a(t,h,e,r,e);
	ASSERT(h0 != h1);
}

Test:y_stringhash__I8()
{
	new
		h0 = _I@a(h,e,l,l,o),
		h1 = _I@a(H,E,L,L,O);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H3e()
{
	new
		h0 = _H@b<hello>,
		h1 = YHash("hello", .type = hash_bernstein);
	ASSERT(h0 == h1);
}

Test:y_stringhash__I3e()
{
	new
		h0 = _I@b<hello>,
		h1 = YHash("hello", .type = hash_bernstein, .sensitive = false);
	//printf("%04x%04x %04x%04x", h0 >>> 16, h0 & 0xFFFF, h1 >>> 16, h1 & 0xFFFF);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H4e()
{
	new
		h0 = _H@b(h,e,l,l,o),
		h1 = YHash("hello", .type = hash_bernstein);
	ASSERT(h0 == h1);
}

Test:y_stringhash__I4e()
{
	new
		h0 = _I@b(h,e,l,l,o),
		h1 = YHash("hello", .type = hash_bernstein, .sensitive = false);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H5e()
{
	new
		h0 = _H@f<hello>,
		h1 = YHash("hello", .type = hash_fnv1);
	ASSERT(h0 == h1);
}

Test:y_stringhash__I5e()
{
	new
		h0 = _I@f<hello>,
		h1 = YHash("hello", .type = hash_fnv1, .sensitive = false);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H6e()
{
	new
		h0 = _H@f(h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1);
	ASSERT(h0 == h1);
}

Test:y_stringhash__I6e()
{
	new
		h0 = _I@f(h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1, .sensitive = false);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H7e()
{
	new
		h0 = _H@a<hello>,
		h1 = YHash("hello", .type = hash_fnv1a);
	ASSERT(h0 == h1);
}

Test:y_stringhash__I7e()
{
	new
		h0 = _I@a<hello>,
		h1 = YHash("hello", .type = hash_fnv1a, .sensitive = false);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H8e()
{
	new
		h0 = _H@a(h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1a);
	ASSERT(h0 == h1);
}

Test:y_stringhash__I8e()
{
	new
		h0 = _I@a(h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1a, .sensitive = false);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H3d()
{
	new
		h0 = HASH:bernstein<hello>,
		h1 = YHash("hello", .type = hash_bernstein);
	ASSERT(h0 == h1);
}

Test:y_stringhash__I3d()
{
	new
		h0 = HASHi:bernstein<hello>,
		h1 = YHash("hello", .type = hash_bernstein, .sensitive = false);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H4d()
{
	new
		h0 = HASH(bernstein,h,e,l,l,o),
		h1 = YHash("hello", .type = hash_bernstein);
	ASSERT(h0 == h1);
}

Test:y_stringhash__I4d()
{
	new
		h0 = HASHi(bernstein,h,e,l,l,o),
		h1 = YHash("hello", .type = hash_bernstein, .sensitive = false);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H5d()
{
	new
		h0 = HASH:fnv1<hello>,
		h1 = YHash("hello", .type = hash_fnv1);
	ASSERT(h0 == h1);
}

Test:y_stringhash__I5d()
{
	new
		h0 = HASHi:fnv1<hello>,
		h1 = YHash("hello", .type = hash_fnv1, .sensitive = false);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H6d()
{
	new
		h0 = HASH(fnv1,h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1);
	ASSERT(h0 == h1);
}

Test:y_stringhash__I6d()
{
	new
		h0 = HASHi(fnv1,h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1, .sensitive = false);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H7d()
{
	new
		h0 = HASH:fnv1a<hello>,
		h1 = YHash("hello", .type = hash_fnv1a);
	ASSERT(h0 == h1);
}

Test:y_stringhash__I7d()
{
	new
		h0 = HASHi:fnv1a<hello>,
		h1 = YHash("hello", .type = hash_fnv1a, .sensitive = false);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H8d()
{
	new
		h0 = HASH(fnv1a,h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1a);
	ASSERT(h0 == h1);
}

Test:y_stringhash__I8d()
{
	new
		h0 = HASHi(fnv1a,h,e,l,l,o),
		h1 = YHash("hello", .type = hash_fnv1a, .sensitive = false);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H3c()
{
	new
		h0 = HASH:bernstein<hello>,
		h1 = _H(h,e,l,l,o);
	ASSERT(h0 == h1);
}

Test:y_stringhash__I3c()
{
	new
		h0 = HASHi:bernstein<hello>,
		h1 = _I(h,e,L,L,o);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H4c()
{
	new
		h0 = HASH(bernstein,h,e,l,l,o),
		h1 = _H<hello>;
	ASSERT(h0 == h1);
}

Test:y_stringhash__I4c()
{
	new
		h0 = HASHi(bernstein,h,e,l,l,o),
		h1 = _I<hellO>;
	ASSERT(h0 == h1);
}

Test:y_stringhash__H5c()
{
	new
		h0 = HASH:fnv1<hello>,
		h1 = _H@f(h,e,l,l,o);
	ASSERT(h0 == h1);
}

Test:y_stringhash__I5c()
{
	new
		h0 = HASHi:fnv1<hello>,
		h1 = _I@f(h,E,l,l,o);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H6c()
{
	new
		h0 = HASH(fnv1,h,e,l,l,o),
		h1 = _H@f<hello>;
	ASSERT(h0 == h1);
}

Test:y_stringhash__I6c()
{
	new
		h0 = HASHi(fnv1,h,e,l,l,o),
		h1 = _I@f<hElLO>;
	ASSERT(h0 == h1);
}

Test:y_stringhash__H7c()
{
	new
		h0 = HASH:fnv1a<hello>,
		h1 = _H@a(h,e,l,l,o);
	ASSERT(h0 == h1);
}

Test:y_stringhash__I7c()
{
	new
		h0 = HASHi:fnv1a<hello>,
		h1 = _I@a(H,e,l,l,o);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H8c()
{
	new
		h0 = HASH(fnv1a,h,e,l,l,o),
		h1 = _H@a<hello>;
	ASSERT(h0 == h1);
}

Test:y_stringhash__I8c()
{
	new
		h0 = HASHi(fnv1a,h,e,l,l,o),
		h1 = _I@a<HELLO>;
	ASSERT(h0 == h1);
}

Test:y_stringhash__H3b()
{
	new
		h0 = HASH:bernstein<hello>,
		h1 = HASH:bernstein<there>;
	ASSERT(h0 != h1);
}

Test:y_stringhash__I3b()
{
	new
		h0 = HASHi:bernstein<hello>,
		h1 = HASHi:bernstein<HelLo>;
	ASSERT(h0 == h1);
}

Test:y_stringhash__H4b()
{
	new
		h0 = HASH(bernstein,h,e,l,l,o),
		h1 = HASH(bernstein,t,h,e,r,e);
	ASSERT(h0 != h1);
}

Test:y_stringhash__I4b()
{
	new
		h0 = HASHi(bernstein,h,e,l,l,o),
		h1 = HASHi(bernstein,H,E,L,L,O);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H5b()
{
	new
		h0 = HASH:fnv1<hello>,
		h1 = HASH:fnv1<there>;
	ASSERT(h0 != h1);
}

Test:y_stringhash__I5b()
{
	new
		h0 = HASHi:fnv1<hello>,
		h1 = HASHi:fnv1<HelLo>;
	ASSERT(h0 == h1);
}

Test:y_stringhash__H6b()
{
	new
		h0 = HASH(fnv1,h,e,l,l,o),
		h1 = HASH(fnv1,t,h,e,r,e);
	ASSERT(h0 != h1);
}

Test:y_stringhash__I6b()
{
	new
		h0 = HASHi(fnv1,h,e,l,l,o),
		h1 = HASHi(fnv1,H,E,L,L,O);
	ASSERT(h0 == h1);
}

Test:y_stringhash__H7b()
{
	new
		h0 = HASH:fnv1a<hello>,
		h1 = HASH:fnv1a<there>;
	ASSERT(h0 != h1);
}

Test:y_stringhash__I7b()
{
	new
		h0 = HASHi:fnv1a<hello>,
		h1 = HASHi:fnv1a<HelLo>;
	ASSERT(h0 == h1);
}

Test:y_stringhash__H8b()
{
	new
		h0 = HASH(fnv1a,h,e,l,l,o),
		h1 = HASH(fnv1a,t,h,e,r,e);
	ASSERT(h0 != h1);
}

Test:y_stringhash__I8b()
{
	new
		h0 = HASHi(fnv1a,h,e,l,l,o),
		h1 = HASHi(fnv1a,H,E,L,L,O);
	ASSERT(h0 == h1);
}

