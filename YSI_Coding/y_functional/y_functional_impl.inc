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

#define LAMBDA_i<%9>{%0}(%1)%8; _DO_LAMBDA|||i|||new _0|||0,|||<%9>{%0}(%1)%8;
#define LAMBDA_ii<%9>{%0}(%1)%8; _DO_LAMBDA|||ii|||new _0,_1|||0,0,|||<%9>{%0}(%1)%8;
#define LAMBDA_iii<%9>{%0}(%1)%8; _DO_LAMBDA|||iii|||new _0,_1,_2|||0,0,0,|||<%9>{%0}(%1)%8;
#define LAMBDA_iiii<%9>{%0}(%1)%8; _DO_LAMBDA|||iiii|||new _0,_1,_2,_3|||0,0,0,0,|||<%9>{%0}(%1)%8;
#define LAMBDA_iiiii<%9>{%0}(%1)%8; _DO_LAMBDA|||iiiii|||new _0,_1,_2,_3,_4|||0,0,0,0,0,|||<%9>{%0}(%1)%8;

#define _DO_LAMBDA|||%4|||%6|||%5|||<%9>{%0}(%1)%8; LAM@0()%8;{{{LAM@1();new I@T:_@YSII=I@T(~~"...YSII"),F@_@%4:YSII=F@_@%4:_@YSII;for(%6;I@F();)while(I@L(%5I@K(1)))Callback_Return_(_:(%0));LAM@2(%9((Inline_UI_(_:YSII),YSII)%1));|||}}LAM@4```()}

#if 0

LAM@0()%8;
{
	{
		LAM@1();
		new _@YSII=I@T(~~"...YSII"),F@_@%4:YSII=F@_@%4:_@YSII;
		for(%6;I@F();)
			while(I@L(%5I@K()))
				Callback_Return_(_:(%0));
		LAM@2(%9((Inline_UI_(_:YSII),YSII)%1));
	}
}
LAM@4```()

#endif

#define LAM@0()%8;{{{LAM@1();%1|||%5```()}{{{%3```(%4) LAM@0(%4-1)%8;{{{LAM@1(%4-1);%1|||%4-1%5(%4-1){{%3```(%4-1)

#define LAM@4%1(%0)

// Remove the closing brace for temporary processing.
#define LAM@2(%0);|||%5}} LAM@2(%0)LAM@5:%5;}
#define LAM@5:%4; ;}LAM@5(%4);

