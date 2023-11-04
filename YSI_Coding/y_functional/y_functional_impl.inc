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
	Portions created by the Initial Developer are Copyright (c) 2022
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
	Cheaterman

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

#define LAMBDA_i<%9>{%0}(%1)%8; _DO_LAMBDA|||i|||new _0|||0,|||<%9>{%0}(%1)%8;
#define LAMBDA_ii<%9>{%0}(%1)%8; _DO_LAMBDA|||ii|||new _0,_1|||0,0,|||<%9>{%0}(%1)%8;
#define LAMBDA_iii<%9>{%0}(%1)%8; _DO_LAMBDA|||iii|||new _0,_1,_2|||0,0,0,|||<%9>{%0}(%1)%8;
#define LAMBDA_iiii<%9>{%0}(%1)%8; _DO_LAMBDA|||iiii|||new _0,_1,_2,_3|||0,0,0,0,|||<%9>{%0}(%1)%8;
#define LAMBDA_iiiii<%9>{%0}(%1)%8; _DO_LAMBDA|||iiiii|||new _0,_1,_2,_3,_4|||0,0,0,0,0,|||<%9>{%0}(%1)%8;

#define _DO_LAMBDA|||%4|||%6|||%5|||<%9>{%0}(%1)%8; LAM@0()%8;{{{LAM@1();new I@T:_@YSII=I@T(~~"...YSII"),F@_@%4:YSII=F@_@%4:_@YSII;for(%6;I@F();)while(I@L(%5I@K(1)))Callback_Return_(_:(%0));LAM@2(%9((Inline_UI_(_:YSII,0),YSII)%1));|||}}LAM@4```()}

#if 0

LAM@0()%8;
{
	{
		LAM@1();
		new _@YSII=I@T(~~"...YSII"),F@_@%4:YSII=F@_@%4:_@YSII;
		for(%6;I@F();)
			while(I@L(%5I@K()))
				Callback_Return_(_:(%0));
		LAM@2(%9((Inline_UI_(_:YSII,0),YSII)%1));
	}
}
LAM@4```()

#endif

#define LAM@0()%8;{{{LAM@1();%1|||%5```()}{{{%3```(%4) LAM@0(%4-1)%8;{{{LAM@1(%4-1);%1|||%4-1%5(%4-1){{%3```(%4-1)

#define LAM@4%1(%0)

// Remove the closing brace for temporary processing.
#define LAM@2(%0);|||%5}} LAM@2(%0)LAM@5:%5;}
#define LAM@5:%4; ;}LAM@5(%4);

#define @lambda(%7,"%0")%1(%2) _:LAM@%7a:LAM@%7b:LAM@A:LAM@B:LAM@C:<%0>%1 PP_DEFER()(%2)

// The five base cases, which select a single parameter to be made fancy.  Can
// deal with the Nth parameter being last or not.
#define LAM@0a:LAM@0b:%8(%9)(%6,%7) %8(%9$%6$,%7)
#define LAM@0b:%8(%9)(%6) %8(%9$%6$)
#define LAM@1a:LAM@1b:%8(%9)(%0,%6,%7) %8(%9%0,$%6$,%7)
#define LAM@1b:%8(%9)(%0,%6) %8(%9%0,$%6$)
#define LAM@2a:LAM@2b:%8(%9)(%0,%1,%6,%7) %8(%9%0,%1,$%6$,%7)
#define LAM@2b:%8(%9)(%0,%1,%6) %8(%9%0,%1,$%6$)
#define LAM@3a:LAM@3b:%8(%9)(%0,%1,%2,%6,%7) %8(%9%0,%1,%2,$%6$,%7)
#define LAM@3b:%8(%9)(%0,%1,%2,%6) %8(%9%0,%1,%2,$%6$)
#define LAM@4a:LAM@4b:%8(%9)(%0,%1,%2,%3,%6,%7) %8(%9%0,%1,%2,%3,$%6$,%7)
#define LAM@4b:%8(%9)(%0,%1,%2,%3,%6) %8(%9%0,%1,%2,%3,$%6$)

// We need some clever recursion to deal with functions with more than around 9
// parameters, since there aren't that many `%` pre-processor symbols.  So we
// accumulate them five at a time and move them elsewhere.
#define LAM@5a:%0: LAM@_:LAM@0a:LAM@0b:
#define LAM@6a:%0: LAM@_:LAM@1a:LAM@1b:
#define LAM@7a:%0: LAM@_:LAM@2a:LAM@2b:
#define LAM@8a:%0: LAM@_:LAM@3a:LAM@3b:
#define LAM@9a:%0: LAM@_:LAM@4a:LAM@4b:
#define LAM@10a:%0: LAM@_:LAM@_:LAM@0a:LAM@0b:
#define LAM@11a:%0: LAM@_:LAM@_:LAM@1a:LAM@1b:
#define LAM@12a:%0: LAM@_:LAM@_:LAM@2a:LAM@2b:
#define LAM@13a:%0: LAM@_:LAM@_:LAM@3a:LAM@3b:
#define LAM@14a:%0: LAM@_:LAM@_:LAM@4a:LAM@4b:
#define LAM@15a:%0: LAM@_:LAM@_:LAM@_:LAM@0a:LAM@0b:
#define LAM@16a:%0: LAM@_:LAM@_:LAM@_:LAM@1a:LAM@1b:
#define LAM@17a:%0: LAM@_:LAM@_:LAM@_:LAM@2a:LAM@2b:
#define LAM@18a:%0: LAM@_:LAM@_:LAM@_:LAM@3a:LAM@3b:
#define LAM@19a:%0: LAM@_:LAM@_:LAM@_:LAM@4a:LAM@4b:
#define LAM@20a:%0: LAM@_:LAM@_:LAM@_:LAM@_:LAM@0a:LAM@0b:
#define LAM@21a:%0: LAM@_:LAM@_:LAM@_:LAM@_:LAM@1a:LAM@1b:
#define LAM@22a:%0: LAM@_:LAM@_:LAM@_:LAM@_:LAM@2a:LAM@2b:
#define LAM@23a:%0: LAM@_:LAM@_:LAM@_:LAM@_:LAM@3a:LAM@3b:
#define LAM@24a:%0: LAM@_:LAM@_:LAM@_:LAM@_:LAM@4a:LAM@4b:
#define LAM@25a:%0: LAM@_:LAM@_:LAM@_:LAM@_:LAM@_:LAM@0a:LAM@0b:
#define LAM@26a:%0: LAM@_:LAM@_:LAM@_:LAM@_:LAM@_:LAM@1a:LAM@1b:
#define LAM@27a:%0: LAM@_:LAM@_:LAM@_:LAM@_:LAM@_:LAM@2a:LAM@2b:
#define LAM@28a:%0: LAM@_:LAM@_:LAM@_:LAM@_:LAM@_:LAM@3a:LAM@3b:
#define LAM@29a:%0: LAM@_:LAM@_:LAM@_:LAM@_:LAM@_:LAM@4a:LAM@4b:
#define LAM@30a:%0: LAM@_:LAM@_:LAM@_:LAM@_:LAM@_:LAM@_:LAM@0a:LAM@0b:
#define LAM@31a:%0: LAM@_:LAM@_:LAM@_:LAM@_:LAM@_:LAM@_:LAM@1a:LAM@1b:
// There's a max of 32 parameters (IIRC, might be 256, but this is enough!)

// Recurse.
#define LAM@_:%8(%9)(%0,%1,%2,%3,%4,%6) %8(%9%0,%1,%2,%3,%4,)(%6)

// Detect `&`.
#define LAM@A:LAM@B:LAM@C:<%0>%1(%2$&%3$%4) %1(%2addressof(%3<%0>)%4)

// Detect lambdas.
#define LAM@B:LAM@C:<%0>%1(%2${%3}$%4) NAMBDA_%0:%1(%2{%3}%4)

// This is not recursive thanks to `PP_DEFER` above.
#define LAM@C:<%0>%1(%2$%3$%4) %1(%2%3%4)

#define NAMBDA_i: _NU_LAMBDA|||i|||new _0|||0,|||
#define NAMBDA_ii: _NU_LAMBDA|||ii|||new _0,_1|||0,0,|||
#define NAMBDA_iii: _NU_LAMBDA|||iii|||new _0,_1,_2|||0,0,0,|||
#define NAMBDA_iiii: _NU_LAMBDA|||iiii|||new _0,_1,_2,_3|||0,0,0,0,|||
#define NAMBDA_iiiii: _NU_LAMBDA|||iiiii|||new _0,_1,_2,_3,_4|||0,0,0,0,0,|||

#define _NU_LAMBDA|||%0|||%6|||%5|||%1(%2{%3}%4)%8; LAM@0()%8;{{{LAM@1();new I@T:_@YSII=I@T(~~"...YSII"),F@_@%0:YSII=F@_@%0:_@YSII;for(%6;I@F();)while(I@L(%5I@K(1)))Callback_Return_(_:(%3));LAM@2(%1(%2(Inline_UI_(_:YSII,0),YSII)%4));|||}}LAM@4```()}

