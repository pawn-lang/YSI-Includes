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
</remarks>
\**--------------------------------------------------------------------------**/

#include "internal\y_version"
#include "y_debug"

// Note: H_a, H_b, H_c, H_d, H_f and H_g are defined here, H_e in y_amx, H_z in
// y_masteronce, H_u in y_users, H_y in y_timers.
// ===================
//  Determine version 
// ===================

// Entry.
#define _H (_:_H_1:_H_0
#define _I (_:_H_3:_H_2
// Old.
#define _H_0(%0) HASH@bernstein(%0))
#define _H_2(%0) HASHi@bernstein(%0))
// New.
#define _H_1:_H_0<%0> H_Pb:@Ba:H_Nba(%0)<-1|||
#define _H_3:_H_2<%0> @Ca:H_Nca(%0)<-1|||

// Entry.
#define _H@b (_:_H0@b:_H1@b
#define _I@b (_:_H2@b:_H3@b
// Old.
#define _H0@b:_H1@b(%0) HASH@bernstein(%0))
#define _H2@b:_H3@b(%0) HASHi@bernstein(%0))
// New.
#define _H1@b<%0> @Ba:H_Nba(%0)<-1|||
#define _H3@b<%0> @Ca:H_Nca(%0)<-1|||

// Entry.
#define _H@f (_:_H0@f:_H1@f
#define _I@f (_:_H2@f:_H3@f
// Old.
#define _H0@f:_H1@f(%0) HASH@fnv1(%0))
#define _H2@f:_H3@f(%0) HASHi@fnv1(%0))
// New.
#define _H1@f<%0> @Ga:H_Nga(%0)<2166136261|||
#define _H3@f<%0> @Fa:H_Nfa(%0)<2166136261|||

// Entry.
#define _H@a (_:_H0@a:_H1@a
#define _I@a (_:_H2@a:_H3@a
// Old.
#define _H0@a:_H1@a(%0) HASH@fnv1a(%0))
#define _H2@a:_H3@a(%0) HASHi@fnv1a(%0))
// New.
#define _H1@a<%0> @Aa:H_Naa(%0)<2166136261|||
#define _H3@a<%0> @Da:H_Nda(%0)<2166136261|||

// Entry.
#define HASH  (_:_H_4:_H_5
#define HASHi (_:_H_6:_H_7
// Old.
#define _H_4:_H_5(%0,%1) HASH@%0(%1))
#define _H_6:_H_7(%0,%1) HASHi@%0(%1))
// New.
#define _H_5:%0<%1> HASh@%0(%1)
#define _H_7:%0<%1> HAShi@%0(%1)

#define HASh@bernstein(%0) @Ba:H_Nba(%0)<-1|||
#define HAShi@bernstein(%0) @Ca:H_Nca(%0)<-1|||
#define HASh@fnv1(%0) @Ga:H_Nga(%0)<2166136261|||
#define HAShi@fnv1(%0) @Fa:H_Nfa(%0)<2166136261|||
#define HASh@fnv1a(%0) @Aa:H_Naa(%0)<2166136261|||
#define HAShi@fnv1a(%0) @Da:H_Nda(%0)<2166136261|||

// =============
//  New version 
// =============

// ================
//  Bernstein hash 
// ================

// ================
//  Case sensitive 
// ================

#define hb:H_Sb(%0,%1£%2,%9,%3)[%4]{%5}<%6<%7||| hb:H_Sb(%0%1£,%2,%9,%3)[%4]{%5<%6}<%7|||
#define H_Sb(%0,%1,%9,%3)[%4]{%5}<%6||| @B%9:H_Nb%9(%0%1£%3)%5<%4<%6|||
#define H_Eb:H_Rb<%0<%1||| (%0_:H_Eb:H_Rb<%1|||)
#define H_Rb<%1||| (%1))
#define H_Db(%1,%9,%2,%8) hb:H_Sb(,%1,%9,%2)[%8+33*]{}

// Test for the current character.
#define @Ba:H_Nba(%1a%0) H_Db(%1,a,%0,97)
#define @Bb:H_Nbb(%1b%0) H_Db(%1,b,%0,98)
#define @Bc:H_Nbc(%1c%0) H_Db(%1,c,%0,99)
#define @Bd:H_Nbd(%1d%0) H_Db(%1,d,%0,100)
#define @Be:H_Nbe(%1e%0) H_Db(%1,e,%0,101)
#define @Bf:H_Nbf(%1f%0) H_Db(%1,f,%0,102)
#define @Bg:H_Nbg(%1g%0) H_Db(%1,g,%0,103)
#define @Bh:H_Nbh(%1h%0) H_Db(%1,h,%0,104)
#define @Bi:H_Nbi(%1i%0) H_Db(%1,i,%0,105)
#define @Bj:H_Nbj(%1j%0) H_Db(%1,j,%0,106)
#define @Bk:H_Nbk(%1k%0) H_Db(%1,k,%0,107)
#define @Bl:H_Nbl(%1l%0) H_Db(%1,l,%0,108)
#define @Bm:H_Nbm(%1m%0) H_Db(%1,m,%0,109)
#define @Bn:H_Nbn(%1n%0) H_Db(%1,n,%0,110)
#define @Bo:H_Nbo(%1o%0) H_Db(%1,o,%0,111)
#define @Bp:H_Nbp(%1p%0) H_Db(%1,p,%0,112)
#define @Bq:H_Nbq(%1q%0) H_Db(%1,q,%0,113)
#define @Br:H_Nbr(%1r%0) H_Db(%1,r,%0,114)
#define @Bs:H_Nbs(%1s%0) H_Db(%1,s,%0,115)
#define @Bt:H_Nbt(%1t%0) H_Db(%1,t,%0,116)
#define @Bu:H_Nbu(%1u%0) H_Db(%1,u,%0,117)
#define @Bv:H_Nbv(%1v%0) H_Db(%1,v,%0,118)
#define @Bw:H_Nbw(%1w%0) H_Db(%1,w,%0,119)
#define @Bx:H_Nbx(%1x%0) H_Db(%1,x,%0,120)
#define @By:H_Nby(%1y%0) H_Db(%1,y,%0,121)
#define @Bz:H_Nbz(%1z%0) H_Db(%1,z,%0,122)

#define @BA:H_NbA(%1A%0) H_Db(%1,A,%0,65)
#define @BB:H_NbB(%1B%0) H_Db(%1,B,%0,66)
#define @BC:H_NbC(%1C%0) H_Db(%1,C,%0,67)
#define @BD:H_NbD(%1D%0) H_Db(%1,D,%0,68)
#define @BE:H_NbE(%1E%0) H_Db(%1,E,%0,69)
#define @BF:H_NbF(%1F%0) H_Db(%1,F,%0,70)
#define @BG:H_NbG(%1G%0) H_Db(%1,G,%0,71)
#define @BH:H_NbH(%1H%0) H_Db(%1,H,%0,72)
#define @BI:H_NbI(%1I%0) H_Db(%1,I,%0,73)
#define @BJ:H_NbJ(%1J%0) H_Db(%1,J,%0,74)
#define @BK:H_NbK(%1K%0) H_Db(%1,K,%0,75)
#define @BL:H_NbL(%1L%0) H_Db(%1,L,%0,76)
#define @BM:H_NbM(%1M%0) H_Db(%1,M,%0,77)
#define @BN:H_NbN(%1N%0) H_Db(%1,N,%0,78)
#define @BO:H_NbO(%1O%0) H_Db(%1,O,%0,79)
#define @BP:H_NbP(%1P%0) H_Db(%1,P,%0,80)
#define @BQ:H_NbQ(%1Q%0) H_Db(%1,Q,%0,81)
#define @BR:H_NbR(%1R%0) H_Db(%1,R,%0,82)
#define @BS:H_NbS(%1S%0) H_Db(%1,S,%0,83)
#define @BT:H_NbT(%1T%0) H_Db(%1,T,%0,84)
#define @BU:H_NbU(%1U%0) H_Db(%1,U,%0,85)
#define @BV:H_NbV(%1V%0) H_Db(%1,V,%0,86)
#define @BW:H_NbW(%1W%0) H_Db(%1,W,%0,87)
#define @BX:H_NbX(%1X%0) H_Db(%1,X,%0,88)
#define @BY:H_NbY(%1Y%0) H_Db(%1,Y,%0,89)
#define @BZ:H_NbZ(%1Z%0) H_Db(%1,Z,%0,90)

#define @B0:H_Nb0(%10%0) H_Db(%1,0,%0,48)
#define @B1:H_Nb1(%11%0) H_Db(%1,1,%0,49)
#define @B2:H_Nb2(%12%0) H_Db(%1,2,%0,50)
#define @B3:H_Nb3(%13%0) H_Db(%1,3,%0,51)
#define @B4:H_Nb4(%14%0) H_Db(%1,4,%0,52)
#define @B5:H_Nb5(%15%0) H_Db(%1,5,%0,53)
#define @B6:H_Nb6(%16%0) H_Db(%1,6,%0,54)
#define @B7:H_Nb7(%17%0) H_Db(%1,7,%0,55)
#define @B8:H_Nb8(%18%0) H_Db(%1,8,%0,56)
#define @B9:H_Nb9(%19%0) H_Db(%1,9,%0,57)

#define @B_:H_Nb_(%1_%0) H_Db(%1,_,%0,95)
//#define hb@:H_Sb(@%0,%1) H_Db(%0)

// Find the next character to test.
#define H_Nba(%0) @Bb:H_Nbb(%0)
#define H_Nbb(%0) @Bc:H_Nbc(%0)
#define H_Nbc(%0) @Bd:H_Nbd(%0)
#define H_Nbd(%0) @Be:H_Nbe(%0)
#define H_Nbe(%0) @Bf:H_Nbf(%0)
#define H_Nbf(%0) @Bg:H_Nbg(%0)
#define H_Nbg(%0) @Bh:H_Nbh(%0)
#define H_Nbh(%0) @Bi:H_Nbi(%0)
#define H_Nbi(%0) @Bj:H_Nbj(%0)
#define H_Nbj(%0) @Bk:H_Nbk(%0)
#define H_Nbk(%0) @Bl:H_Nbl(%0)
#define H_Nbl(%0) @Bm:H_Nbm(%0)
#define H_Nbm(%0) @Bn:H_Nbn(%0)
#define H_Nbn(%0) @Bo:H_Nbo(%0)
#define H_Nbo(%0) @Bp:H_Nbp(%0)
#define H_Nbp(%0) @Bq:H_Nbq(%0)
#define H_Nbq(%0) @Br:H_Nbr(%0)
#define H_Nbr(%0) @Bs:H_Nbs(%0)
#define H_Nbs(%0) @Bt:H_Nbt(%0)
#define H_Nbt(%0) @Bu:H_Nbu(%0)
#define H_Nbu(%0) @Bv:H_Nbv(%0)
#define H_Nbv(%0) @Bw:H_Nbw(%0)
#define H_Nbw(%0) @Bx:H_Nbx(%0)
#define H_Nbx(%0) @By:H_Nby(%0)
#define H_Nby(%0) @Bz:H_Nbz(%0)
#define H_Nbz(%0) @B0:H_Nb0(%0)

#define H_NbA(%0) @BB:H_NbB(%0)
#define H_NbB(%0) @BC:H_NbC(%0)
#define H_NbC(%0) @BD:H_NbD(%0)
#define H_NbD(%0) @BE:H_NbE(%0)
#define H_NbE(%0) @BF:H_NbF(%0)
#define H_NbF(%0) @BG:H_NbG(%0)
#define H_NbG(%0) @BH:H_NbH(%0)
#define H_NbH(%0) @BI:H_NbI(%0)
#define H_NbI(%0) @BJ:H_NbJ(%0)
#define H_NbJ(%0) @BK:H_NbK(%0)
#define H_NbK(%0) @BL:H_NbL(%0)
#define H_NbL(%0) @BM:H_NbM(%0)
#define H_NbM(%0) @BN:H_NbN(%0)
#define H_NbN(%0) @BO:H_NbO(%0)
#define H_NbO(%0) @BP:H_NbP(%0)
#define H_NbP(%0) @BQ:H_NbQ(%0)
#define H_NbQ(%0) @BR:H_NbR(%0)
#define H_NbR(%0) @BS:H_NbS(%0)
#define H_NbS(%0) @BT:H_NbT(%0)
#define H_NbT(%0) @BU:H_NbU(%0)
#define H_NbU(%0) @BV:H_NbV(%0)
#define H_NbV(%0) @BW:H_NbW(%0)
#define H_NbW(%0) @BX:H_NbX(%0)
#define H_NbX(%0) @BY:H_NbY(%0)
#define H_NbY(%0) @BZ:H_NbZ(%0)
#define H_NbZ(%0) H_Eb:H_Rb

#define H_Nb0(%0) @B1:H_Nb1(%0)
#define H_Nb1(%0) @B2:H_Nb2(%0)
#define H_Nb2(%0) @B3:H_Nb3(%0)
#define H_Nb3(%0) @B4:H_Nb4(%0)
#define H_Nb4(%0) @B5:H_Nb5(%0)
#define H_Nb5(%0) @B6:H_Nb6(%0)
#define H_Nb6(%0) @B7:H_Nb7(%0)
#define H_Nb7(%0) @B8:H_Nb8(%0)
#define H_Nb8(%0) @B9:H_Nb9(%0)
#define H_Nb9(%0) @B_:H_Nb_(%0)

#define H_Nb_(%0) @BA:H_NbA(%0)

// ==================
//  Case insensitive 
// ==================

#define hc:H_Sc(%0,%1£%2,%9,%3)[%4]{%5}<%6<%7||| hc:H_Sc(%0%1£,%2,%9,%3)[%4]{%5<%6}<%7|||
#define H_Sc(%0,%1,%9,%3)[%4]{%5}<%6||| @C%9:H_Nc%9(%0%1£%3)%5<%4<%6|||
#define H_Ec:H_Rc<%0<%1||| (%0_:H_Ec:H_Rc<%1|||)
#define H_Rc<%1||| (%1))
#define H_Dc(%1,%9,%2,%8) hc:H_Sc(,%1,%9,%2)[%8+33*]{}

// Test for the current character.
#define @Ca:H_Nca(%1a%0) H_Dc(%1,a,%0,65)
#define @Cb:H_Ncb(%1b%0) H_Dc(%1,b,%0,66)
#define @Cc:H_Ncc(%1c%0) H_Dc(%1,c,%0,67)
#define @Cd:H_Ncd(%1d%0) H_Dc(%1,d,%0,68)
#define @Ce:H_Nce(%1e%0) H_Dc(%1,e,%0,69)
#define @Cf:H_Ncf(%1f%0) H_Dc(%1,f,%0,70)
#define @Cg:H_Ncg(%1g%0) H_Dc(%1,g,%0,71)
#define @Ch:H_Nch(%1h%0) H_Dc(%1,h,%0,72)
#define @Ci:H_Nci(%1i%0) H_Dc(%1,i,%0,73)
#define @Cj:H_Ncj(%1j%0) H_Dc(%1,j,%0,74)
#define @Ck:H_Nck(%1k%0) H_Dc(%1,k,%0,75)
#define @Cl:H_Ncl(%1l%0) H_Dc(%1,l,%0,76)
#define @Cm:H_Ncm(%1m%0) H_Dc(%1,m,%0,77)
#define @Cn:H_Ncn(%1n%0) H_Dc(%1,n,%0,78)
#define @Co:H_Nco(%1o%0) H_Dc(%1,o,%0,79)
#define @Cp:H_Ncp(%1p%0) H_Dc(%1,p,%0,80)
#define @Cq:H_Ncq(%1q%0) H_Dc(%1,q,%0,81)
#define @Cr:H_Ncr(%1r%0) H_Dc(%1,r,%0,82)
#define @Cs:H_Ncs(%1s%0) H_Dc(%1,s,%0,83)
#define @Ct:H_Nct(%1t%0) H_Dc(%1,t,%0,84)
#define @Cu:H_Ncu(%1u%0) H_Dc(%1,u,%0,85)
#define @Cv:H_Ncv(%1v%0) H_Dc(%1,v,%0,86)
#define @Cw:H_Ncw(%1w%0) H_Dc(%1,w,%0,87)
#define @Cx:H_Ncx(%1x%0) H_Dc(%1,x,%0,88)
#define @Cy:H_Ncy(%1y%0) H_Dc(%1,y,%0,89)
#define @Cz:H_Ncz(%1z%0) H_Dc(%1,z,%0,90)

#define @CA:H_NcA(%1A%0) H_Dc(%1,A,%0,65)
#define @CB:H_NcB(%1B%0) H_Dc(%1,B,%0,66)
#define @CC:H_NcC(%1C%0) H_Dc(%1,C,%0,67)
#define @CD:H_NcD(%1D%0) H_Dc(%1,D,%0,68)
#define @CE:H_NcE(%1E%0) H_Dc(%1,E,%0,69)
#define @CF:H_NcF(%1F%0) H_Dc(%1,F,%0,70)
#define @CG:H_NcG(%1G%0) H_Dc(%1,G,%0,71)
#define @CH:H_NcH(%1H%0) H_Dc(%1,H,%0,72)
#define @CI:H_NcI(%1I%0) H_Dc(%1,I,%0,73)
#define @CJ:H_NcJ(%1J%0) H_Dc(%1,J,%0,74)
#define @CK:H_NcK(%1K%0) H_Dc(%1,K,%0,75)
#define @CL:H_NcL(%1L%0) H_Dc(%1,L,%0,76)
#define @CM:H_NcM(%1M%0) H_Dc(%1,M,%0,77)
#define @CN:H_NcN(%1N%0) H_Dc(%1,N,%0,78)
#define @CO:H_NcO(%1O%0) H_Dc(%1,O,%0,79)
#define @CP:H_NcP(%1P%0) H_Dc(%1,P,%0,80)
#define @CQ:H_NcQ(%1Q%0) H_Dc(%1,Q,%0,81)
#define @CR:H_NcR(%1R%0) H_Dc(%1,R,%0,82)
#define @CS:H_NcS(%1S%0) H_Dc(%1,S,%0,83)
#define @CT:H_NcT(%1T%0) H_Dc(%1,T,%0,84)
#define @CU:H_NcU(%1U%0) H_Dc(%1,U,%0,85)
#define @CV:H_NcV(%1V%0) H_Dc(%1,V,%0,86)
#define @CW:H_NcW(%1W%0) H_Dc(%1,W,%0,87)
#define @CX:H_NcX(%1X%0) H_Dc(%1,X,%0,88)
#define @CY:H_NcY(%1Y%0) H_Dc(%1,Y,%0,89)
#define @CZ:H_NcZ(%1Z%0) H_Dc(%1,Z,%0,90)

#define @C0:H_Nc0(%10%0) H_Dc(%1,0,%0,48)
#define @C1:H_Nc1(%11%0) H_Dc(%1,1,%0,49)
#define @C2:H_Nc2(%12%0) H_Dc(%1,2,%0,50)
#define @C3:H_Nc3(%13%0) H_Dc(%1,3,%0,51)
#define @C4:H_Nc4(%14%0) H_Dc(%1,4,%0,52)
#define @C5:H_Nc5(%15%0) H_Dc(%1,5,%0,53)
#define @C6:H_Nc6(%16%0) H_Dc(%1,6,%0,54)
#define @C7:H_Nc7(%17%0) H_Dc(%1,7,%0,55)
#define @C8:H_Nc8(%18%0) H_Dc(%1,8,%0,56)
#define @C9:H_Nc9(%19%0) H_Dc(%1,9,%0,57)

#define @C_:H_Nc_(%1_%0) H_Dc(%1,_,%0,95)
//#define hc@:H_Sc(@%0,%1) H_Dc(%0)

// Find the next character to test.
#define H_Nca(%0) @Cb:H_Ncb(%0)
#define H_Ncb(%0) @Cc:H_Ncc(%0)
#define H_Ncc(%0) @Cd:H_Ncd(%0)
#define H_Ncd(%0) @Ce:H_Nce(%0)
#define H_Nce(%0) @Cf:H_Ncf(%0)
#define H_Ncf(%0) @Cg:H_Ncg(%0)
#define H_Ncg(%0) @Ch:H_Nch(%0)
#define H_Nch(%0) @Ci:H_Nci(%0)
#define H_Nci(%0) @Cj:H_Ncj(%0)
#define H_Ncj(%0) @Ck:H_Nck(%0)
#define H_Nck(%0) @Cl:H_Ncl(%0)
#define H_Ncl(%0) @Cm:H_Ncm(%0)
#define H_Ncm(%0) @Cn:H_Ncn(%0)
#define H_Ncn(%0) @Co:H_Nco(%0)
#define H_Nco(%0) @Cp:H_Ncp(%0)
#define H_Ncp(%0) @Cq:H_Ncq(%0)
#define H_Ncq(%0) @Cr:H_Ncr(%0)
#define H_Ncr(%0) @Cs:H_Ncs(%0)
#define H_Ncs(%0) @Ct:H_Nct(%0)
#define H_Nct(%0) @Cu:H_Ncu(%0)
#define H_Ncu(%0) @Cv:H_Ncv(%0)
#define H_Ncv(%0) @Cw:H_Ncw(%0)
#define H_Ncw(%0) @Cx:H_Ncx(%0)
#define H_Ncx(%0) @Cy:H_Ncy(%0)
#define H_Ncy(%0) @Cz:H_Ncz(%0)
#define H_Ncz(%0) @C0:H_Nc0(%0)

#define H_NcA(%0) @CB:H_NcB(%0)
#define H_NcB(%0) @CC:H_NcC(%0)
#define H_NcC(%0) @CD:H_NcD(%0)
#define H_NcD(%0) @CE:H_NcE(%0)
#define H_NcE(%0) @CF:H_NcF(%0)
#define H_NcF(%0) @CG:H_NcG(%0)
#define H_NcG(%0) @CH:H_NcH(%0)
#define H_NcH(%0) @CI:H_NcI(%0)
#define H_NcI(%0) @CJ:H_NcJ(%0)
#define H_NcJ(%0) @CK:H_NcK(%0)
#define H_NcK(%0) @CL:H_NcL(%0)
#define H_NcL(%0) @CM:H_NcM(%0)
#define H_NcM(%0) @CN:H_NcN(%0)
#define H_NcN(%0) @CO:H_NcO(%0)
#define H_NcO(%0) @CP:H_NcP(%0)
#define H_NcP(%0) @CQ:H_NcQ(%0)
#define H_NcQ(%0) @CR:H_NcR(%0)
#define H_NcR(%0) @CS:H_NcS(%0)
#define H_NcS(%0) @CT:H_NcT(%0)
#define H_NcT(%0) @CU:H_NcU(%0)
#define H_NcU(%0) @CV:H_NcV(%0)
#define H_NcV(%0) @CW:H_NcW(%0)
#define H_NcW(%0) @CX:H_NcX(%0)
#define H_NcX(%0) @CY:H_NcY(%0)
#define H_NcY(%0) @CZ:H_NcZ(%0)
#define H_NcZ(%0) H_EC:H_RC

#define H_Nc0(%0) @C1:H_Nc1(%0)
#define H_Nc1(%0) @C2:H_Nc2(%0)
#define H_Nc2(%0) @C3:H_Nc3(%0)
#define H_Nc3(%0) @C4:H_Nc4(%0)
#define H_Nc4(%0) @C5:H_Nc5(%0)
#define H_Nc5(%0) @C6:H_Nc6(%0)
#define H_Nc6(%0) @C7:H_Nc7(%0)
#define H_Nc7(%0) @C8:H_Nc8(%0)
#define H_Nc8(%0) @C9:H_Nc9(%0)
#define H_Nc9(%0) @C_:H_Nc_(%0)

#define H_Nc_(%0) @CA:H_NcA(%0)

// ===========
//  FNV1 hash 
// ===========

// ================
//  Case sensitive 
// ================

#define hg:H_Sg(%0,%1£%2,%9,%3)[%4]{%5}<%6<%7||| hg:H_Sg(%0%1£,%2,%9,%3)[%4]{%5<%6}<%7|||
#define H_Sg(%0,%1,%9,%3)[%4]{%5}<%6||| @G%9:H_Ng%9(%0%1£%3)%5<%4<%6|||
#define H_Eg:H_Rg<%0<%1||| (%0_:H_Eg:H_Rg<%1|||)
#define H_Rg<%1||| (%1))
#define H_Dg(%1,%9,%2,%8) hg:H_Sg(,%1,%9,%2)[%8^16777619*]{}

// Test for the current character.
#define @Ga:H_Nga(%1a%0) H_Dg(%1,a,%0,97)
#define @Gb:H_Ngb(%1b%0) H_Dg(%1,b,%0,98)
#define @Gc:H_Ngc(%1c%0) H_Dg(%1,c,%0,99)
#define @Gd:H_Ngd(%1d%0) H_Dg(%1,d,%0,100)
#define @Ge:H_Nge(%1e%0) H_Dg(%1,e,%0,101)
#define @Gf:H_Ngf(%1f%0) H_Dg(%1,f,%0,102)
#define @Gg:H_Ngg(%1g%0) H_Dg(%1,g,%0,103)
#define @Gh:H_Ngh(%1h%0) H_Dg(%1,h,%0,104)
#define @Gi:H_Ngi(%1i%0) H_Dg(%1,i,%0,105)
#define @Gj:H_Ngj(%1j%0) H_Dg(%1,j,%0,106)
#define @Gk:H_Ngk(%1k%0) H_Dg(%1,k,%0,107)
#define @Gl:H_Ngl(%1l%0) H_Dg(%1,l,%0,108)
#define @Gm:H_Ngm(%1m%0) H_Dg(%1,m,%0,109)
#define @Gn:H_Ngn(%1n%0) H_Dg(%1,n,%0,110)
#define @Go:H_Ngo(%1o%0) H_Dg(%1,o,%0,111)
#define @Gp:H_Ngp(%1p%0) H_Dg(%1,p,%0,112)
#define @Gq:H_Ngq(%1q%0) H_Dg(%1,q,%0,113)
#define @Gr:H_Ngr(%1r%0) H_Dg(%1,r,%0,114)
#define @Gs:H_Ngs(%1s%0) H_Dg(%1,s,%0,115)
#define @Gt:H_Ngt(%1t%0) H_Dg(%1,t,%0,116)
#define @Gu:H_Ngu(%1u%0) H_Dg(%1,u,%0,117)
#define @Gv:H_Ngv(%1v%0) H_Dg(%1,v,%0,118)
#define @Gw:H_Ngw(%1w%0) H_Dg(%1,w,%0,119)
#define @Gx:H_Ngx(%1x%0) H_Dg(%1,x,%0,120)
#define @Gy:H_Ngy(%1y%0) H_Dg(%1,y,%0,121)
#define @Gz:H_Ngz(%1z%0) H_Dg(%1,z,%0,122)

#define @GA:H_NgA(%1A%0) H_Dg(%1,A,%0,65)
#define @GB:H_NgB(%1B%0) H_Dg(%1,B,%0,66)
#define @GC:H_NgC(%1C%0) H_Dg(%1,C,%0,67)
#define @GD:H_NgD(%1D%0) H_Dg(%1,D,%0,68)
#define @GE:H_NgE(%1E%0) H_Dg(%1,E,%0,69)
#define @GF:H_NgF(%1F%0) H_Dg(%1,F,%0,70)
#define @GG:H_NgG(%1G%0) H_Dg(%1,G,%0,71)
#define @GH:H_NgH(%1H%0) H_Dg(%1,H,%0,72)
#define @GI:H_NgI(%1I%0) H_Dg(%1,I,%0,73)
#define @GJ:H_NgJ(%1J%0) H_Dg(%1,J,%0,74)
#define @GK:H_NgK(%1K%0) H_Dg(%1,K,%0,75)
#define @GL:H_NgL(%1L%0) H_Dg(%1,L,%0,76)
#define @GM:H_NgM(%1M%0) H_Dg(%1,M,%0,77)
#define @GN:H_NgN(%1N%0) H_Dg(%1,N,%0,78)
#define @GO:H_NgO(%1O%0) H_Dg(%1,O,%0,79)
#define @GP:H_NgP(%1P%0) H_Dg(%1,P,%0,80)
#define @GQ:H_NgQ(%1Q%0) H_Dg(%1,Q,%0,81)
#define @GR:H_NgR(%1R%0) H_Dg(%1,R,%0,82)
#define @GS:H_NgS(%1S%0) H_Dg(%1,S,%0,83)
#define @GT:H_NgT(%1T%0) H_Dg(%1,T,%0,84)
#define @GU:H_NgU(%1U%0) H_Dg(%1,U,%0,85)
#define @GV:H_NgV(%1V%0) H_Dg(%1,V,%0,86)
#define @GW:H_NgW(%1W%0) H_Dg(%1,W,%0,87)
#define @GX:H_NgX(%1X%0) H_Dg(%1,X,%0,88)
#define @GY:H_NgY(%1Y%0) H_Dg(%1,Y,%0,89)
#define @GZ:H_NgZ(%1Z%0) H_Dg(%1,Z,%0,90)

#define @G0:H_Ng0(%10%0) H_Dg(%1,0,%0,48)
#define @G1:H_Ng1(%11%0) H_Dg(%1,1,%0,49)
#define @G2:H_Ng2(%12%0) H_Dg(%1,2,%0,50)
#define @G3:H_Ng3(%13%0) H_Dg(%1,3,%0,51)
#define @G4:H_Ng4(%14%0) H_Dg(%1,4,%0,52)
#define @G5:H_Ng5(%15%0) H_Dg(%1,5,%0,53)
#define @G6:H_Ng6(%16%0) H_Dg(%1,6,%0,54)
#define @G7:H_Ng7(%17%0) H_Dg(%1,7,%0,55)
#define @G8:H_Ng8(%18%0) H_Dg(%1,8,%0,56)
#define @G9:H_Ng9(%19%0) H_Dg(%1,9,%0,57)

#define @G_:H_Ng_(%1_%0) H_Dg(%1,_,%0,95)
//#define hg@:H_Sg(@%0,%1) H_Dg(%0)

// Find the next character to test.
#define H_Nga(%0) @Gb:H_Ngb(%0)
#define H_Ngb(%0) @Gc:H_Ngc(%0)
#define H_Ngc(%0) @Gd:H_Ngd(%0)
#define H_Ngd(%0) @Ge:H_Nge(%0)
#define H_Nge(%0) @Gf:H_Ngf(%0)
#define H_Ngf(%0) @Gg:H_Ngg(%0)
#define H_Ngg(%0) @Gh:H_Ngh(%0)
#define H_Ngh(%0) @Gi:H_Ngi(%0)
#define H_Ngi(%0) @Gj:H_Ngj(%0)
#define H_Ngj(%0) @Gk:H_Ngk(%0)
#define H_Ngk(%0) @Gl:H_Ngl(%0)
#define H_Ngl(%0) @Gm:H_Ngm(%0)
#define H_Ngm(%0) @Gn:H_Ngn(%0)
#define H_Ngn(%0) @Go:H_Ngo(%0)
#define H_Ngo(%0) @Gp:H_Ngp(%0)
#define H_Ngp(%0) @Gq:H_Ngq(%0)
#define H_Ngq(%0) @Gr:H_Ngr(%0)
#define H_Ngr(%0) @Gs:H_Ngs(%0)
#define H_Ngs(%0) @Gt:H_Ngt(%0)
#define H_Ngt(%0) @Gu:H_Ngu(%0)
#define H_Ngu(%0) @Gv:H_Ngv(%0)
#define H_Ngv(%0) @Gw:H_Ngw(%0)
#define H_Ngw(%0) @Gx:H_Ngx(%0)
#define H_Ngx(%0) @Gy:H_Ngy(%0)
#define H_Ngy(%0) @Gz:H_Ngz(%0)
#define H_Ngz(%0) @G0:H_Ng0(%0)

#define H_NgA(%0) @GB:H_NgB(%0)
#define H_NgB(%0) @GC:H_NgC(%0)
#define H_NgC(%0) @GD:H_NgD(%0)
#define H_NgD(%0) @GE:H_NgE(%0)
#define H_NgE(%0) @GF:H_NgF(%0)
#define H_NgF(%0) @GG:H_NgG(%0)
#define H_NgG(%0) @GH:H_NgH(%0)
#define H_NgH(%0) @GI:H_NgI(%0)
#define H_NgI(%0) @GJ:H_NgJ(%0)
#define H_NgJ(%0) @GK:H_NgK(%0)
#define H_NgK(%0) @GL:H_NgL(%0)
#define H_NgL(%0) @GM:H_NgM(%0)
#define H_NgM(%0) @GN:H_NgN(%0)
#define H_NgN(%0) @GO:H_NgO(%0)
#define H_NgO(%0) @GP:H_NgP(%0)
#define H_NgP(%0) @GQ:H_NgQ(%0)
#define H_NgQ(%0) @GR:H_NgR(%0)
#define H_NgR(%0) @GS:H_NgS(%0)
#define H_NgS(%0) @GT:H_NgT(%0)
#define H_NgT(%0) @GU:H_NgU(%0)
#define H_NgU(%0) @GV:H_NgV(%0)
#define H_NgV(%0) @GW:H_NgW(%0)
#define H_NgW(%0) @GX:H_NgX(%0)
#define H_NgX(%0) @GY:H_NgY(%0)
#define H_NgY(%0) @GZ:H_NgZ(%0)
#define H_NgZ(%0) H_Eg:H_Rg

#define H_Ng0(%0) @G1:H_Ng1(%0)
#define H_Ng1(%0) @G2:H_Ng2(%0)
#define H_Ng2(%0) @G3:H_Ng3(%0)
#define H_Ng3(%0) @G4:H_Ng4(%0)
#define H_Ng4(%0) @G5:H_Ng5(%0)
#define H_Ng5(%0) @G6:H_Ng6(%0)
#define H_Ng6(%0) @G7:H_Ng7(%0)
#define H_Ng7(%0) @G8:H_Ng8(%0)
#define H_Ng8(%0) @G9:H_Ng9(%0)
#define H_Ng9(%0) @G_:H_Ng_(%0)

#define H_Ng_(%0) @GA:H_NgA(%0)

// ==================
//  Case insensitive 
// ==================

#define hf:H_Sf(%0,%1£%2,%9,%3)[%4]{%5}<%6<%7||| hf:H_Sf(%0%1£,%2,%9,%3)[%4]{%5<%6}<%7|||
#define H_Sf(%0,%1,%9,%3)[%4]{%5}<%6||| @F%9:H_Nf%9(%0%1£%3)%5<%4<%6|||
#define H_Ef:H_Rf<%0<%1||| (%0_:H_Ef:H_Rf<%1|||)
#define H_Rf<%1||| (%1))
#define H_Df(%1,%9,%2,%8) hf:H_Sf(,%1,%9,%2)[%8^16777619*]{}

// Test for the current character.
#define @Fa:H_Nfa(%1a%0) H_Df(%1,a,%0,65)
#define @Fb:H_Nfb(%1b%0) H_Df(%1,b,%0,66)
#define @Fc:H_Nfc(%1c%0) H_Df(%1,c,%0,67)
#define @Fd:H_Nfd(%1d%0) H_Df(%1,d,%0,68)
#define @Fe:H_Nfe(%1e%0) H_Df(%1,e,%0,69)
#define @Ff:H_Nff(%1f%0) H_Df(%1,f,%0,70)
#define @Fg:H_Nfg(%1g%0) H_Df(%1,g,%0,71)
#define @Fh:H_Nfh(%1h%0) H_Df(%1,h,%0,72)
#define @Fi:H_Nfi(%1i%0) H_Df(%1,i,%0,73)
#define @Fj:H_Nfj(%1j%0) H_Df(%1,j,%0,74)
#define @Fk:H_Nfk(%1k%0) H_Df(%1,k,%0,75)
#define @Fl:H_Nfl(%1l%0) H_Df(%1,l,%0,76)
#define @Fm:H_Nfm(%1m%0) H_Df(%1,m,%0,77)
#define @Fn:H_Nfn(%1n%0) H_Df(%1,n,%0,78)
#define @Fo:H_Nfo(%1o%0) H_Df(%1,o,%0,79)
#define @Fp:H_Nfp(%1p%0) H_Df(%1,p,%0,80)
#define @Fq:H_Nfq(%1q%0) H_Df(%1,q,%0,81)
#define @Fr:H_Nfr(%1r%0) H_Df(%1,r,%0,82)
#define @Fs:H_Nfs(%1s%0) H_Df(%1,s,%0,83)
#define @Ft:H_Nft(%1t%0) H_Df(%1,t,%0,84)
#define @Fu:H_Nfu(%1u%0) H_Df(%1,u,%0,85)
#define @Fv:H_Nfv(%1v%0) H_Df(%1,v,%0,86)
#define @Fw:H_Nfw(%1w%0) H_Df(%1,w,%0,87)
#define @Fx:H_Nfx(%1x%0) H_Df(%1,x,%0,88)
#define @Fy:H_Nfy(%1y%0) H_Df(%1,y,%0,89)
#define @Fz:H_Nfz(%1z%0) H_Df(%1,z,%0,90)

#define @FA:H_NfA(%1A%0) H_Df(%1,A,%0,65)
#define @FB:H_NfB(%1B%0) H_Df(%1,B,%0,66)
#define @FC:H_NfC(%1C%0) H_Df(%1,C,%0,67)
#define @FD:H_NfD(%1D%0) H_Df(%1,D,%0,68)
#define @FE:H_NfE(%1E%0) H_Df(%1,E,%0,69)
#define @FF:H_NfF(%1F%0) H_Df(%1,F,%0,70)
#define @FG:H_NfG(%1G%0) H_Df(%1,G,%0,71)
#define @FH:H_NfH(%1H%0) H_Df(%1,H,%0,72)
#define @FI:H_NfI(%1I%0) H_Df(%1,I,%0,73)
#define @FJ:H_NfJ(%1J%0) H_Df(%1,J,%0,74)
#define @FK:H_NfK(%1K%0) H_Df(%1,K,%0,75)
#define @FL:H_NfL(%1L%0) H_Df(%1,L,%0,76)
#define @FM:H_NfM(%1M%0) H_Df(%1,M,%0,77)
#define @FN:H_NfN(%1N%0) H_Df(%1,N,%0,78)
#define @FO:H_NfO(%1O%0) H_Df(%1,O,%0,79)
#define @FP:H_NfP(%1P%0) H_Df(%1,P,%0,80)
#define @FQ:H_NfQ(%1Q%0) H_Df(%1,Q,%0,81)
#define @FR:H_NfR(%1R%0) H_Df(%1,R,%0,82)
#define @FS:H_NfS(%1S%0) H_Df(%1,S,%0,83)
#define @FT:H_NfT(%1T%0) H_Df(%1,T,%0,84)
#define @FU:H_NfU(%1U%0) H_Df(%1,U,%0,85)
#define @FV:H_NfV(%1V%0) H_Df(%1,V,%0,86)
#define @FW:H_NfW(%1W%0) H_Df(%1,W,%0,87)
#define @FX:H_NfX(%1X%0) H_Df(%1,X,%0,88)
#define @FY:H_NfY(%1Y%0) H_Df(%1,Y,%0,89)
#define @FZ:H_NfZ(%1Z%0) H_Df(%1,Z,%0,90)

#define @F0:H_Nf0(%10%0) H_Df(%1,0,%0,48)
#define @F1:H_Nf1(%11%0) H_Df(%1,1,%0,49)
#define @F2:H_Nf2(%12%0) H_Df(%1,2,%0,50)
#define @F3:H_Nf3(%13%0) H_Df(%1,3,%0,51)
#define @F4:H_Nf4(%14%0) H_Df(%1,4,%0,52)
#define @F5:H_Nf5(%15%0) H_Df(%1,5,%0,53)
#define @F6:H_Nf6(%16%0) H_Df(%1,6,%0,54)
#define @F7:H_Nf7(%17%0) H_Df(%1,7,%0,55)
#define @F8:H_Nf8(%18%0) H_Df(%1,8,%0,56)
#define @F9:H_Nf9(%19%0) H_Df(%1,9,%0,57)

#define @F_:H_Nf_(%1_%0) H_Df(%1,_,%0,95)
//#define hf@:H_Sf(@%0,%1) H_Df(%0)

// Find the next character to test.
#define H_Nfa(%0) @Fb:H_Nfb(%0)
#define H_Nfb(%0) @Fc:H_Nfc(%0)
#define H_Nfc(%0) @Fd:H_Nfd(%0)
#define H_Nfd(%0) @Fe:H_Nfe(%0)
#define H_Nfe(%0) @Ff:H_Nff(%0)
#define H_Nff(%0) @Fg:H_Nfg(%0)
#define H_Nfg(%0) @Fh:H_Nfh(%0)
#define H_Nfh(%0) @Fi:H_Nfi(%0)
#define H_Nfi(%0) @Fj:H_Nfj(%0)
#define H_Nfj(%0) @Fk:H_Nfk(%0)
#define H_Nfk(%0) @Fl:H_Nfl(%0)
#define H_Nfl(%0) @Fm:H_Nfm(%0)
#define H_Nfm(%0) @Fn:H_Nfn(%0)
#define H_Nfn(%0) @Fo:H_Nfo(%0)
#define H_Nfo(%0) @Fp:H_Nfp(%0)
#define H_Nfp(%0) @Fq:H_Nfq(%0)
#define H_Nfq(%0) @Fr:H_Nfr(%0)
#define H_Nfr(%0) @Fs:H_Nfs(%0)
#define H_Nfs(%0) @Ft:H_Nft(%0)
#define H_Nft(%0) @Fu:H_Nfu(%0)
#define H_Nfu(%0) @Fv:H_Nfv(%0)
#define H_Nfv(%0) @Fw:H_Nfw(%0)
#define H_Nfw(%0) @Fx:H_Nfx(%0)
#define H_Nfx(%0) @Fy:H_Nfy(%0)
#define H_Nfy(%0) @Fz:H_Nfz(%0)
#define H_Nfz(%0) @F0:H_Nf0(%0)

#define H_NfA(%0) @FB:H_NfB(%0)
#define H_NfB(%0) @FC:H_NfC(%0)
#define H_NfC(%0) @FD:H_NfD(%0)
#define H_NfD(%0) @FE:H_NfE(%0)
#define H_NfE(%0) @FF:H_NfF(%0)
#define H_NfF(%0) @FG:H_NfG(%0)
#define H_NfG(%0) @FH:H_NfH(%0)
#define H_NfH(%0) @FI:H_NfI(%0)
#define H_NfI(%0) @FJ:H_NfJ(%0)
#define H_NfJ(%0) @FK:H_NfK(%0)
#define H_NfK(%0) @FL:H_NfL(%0)
#define H_NfL(%0) @FM:H_NfM(%0)
#define H_NfM(%0) @FN:H_NfN(%0)
#define H_NfN(%0) @FO:H_NfO(%0)
#define H_NfO(%0) @FP:H_NfP(%0)
#define H_NfP(%0) @FQ:H_NfQ(%0)
#define H_NfQ(%0) @FR:H_NfR(%0)
#define H_NfR(%0) @FS:H_NfS(%0)
#define H_NfS(%0) @FT:H_NfT(%0)
#define H_NfT(%0) @FU:H_NfU(%0)
#define H_NfU(%0) @FV:H_NfV(%0)
#define H_NfV(%0) @FW:H_NfW(%0)
#define H_NfW(%0) @FX:H_NfX(%0)
#define H_NfX(%0) @FY:H_NfY(%0)
#define H_NfY(%0) @FZ:H_NfZ(%0)
#define H_NfZ(%0) H_Ef:H_Rf

#define H_Nf0(%0) @F1:H_Nf1(%0)
#define H_Nf1(%0) @F2:H_Nf2(%0)
#define H_Nf2(%0) @F3:H_Nf3(%0)
#define H_Nf3(%0) @F4:H_Nf4(%0)
#define H_Nf4(%0) @F5:H_Nf5(%0)
#define H_Nf5(%0) @F6:H_Nf6(%0)
#define H_Nf6(%0) @F7:H_Nf7(%0)
#define H_Nf7(%0) @F8:H_Nf8(%0)
#define H_Nf8(%0) @F9:H_Nf9(%0)
#define H_Nf9(%0) @F_:H_Nf_(%0)

#define H_Nf_(%0) @FA:H_NfA(%0)

// ============
//  FNV1a hash 
// ============

// ================
//  Case sensitive 
// ================

#define ha:H_Sa(%0,%1£%2,%9,%3)[%4]{%5}<%6<%7||| ha:H_Sa(%0%1£,%2,%9,%3)[%4]{%5<%6}<%7|||
#define H_Sa(%0,%1,%9,%3)[%4]{%5}<%6||| @A%9:H_Na%9(%0%1£%3)%5<%4<%6|||
#define H_Ea:H_Ra<%0<%1||| (%0_:H_Ea:H_Ra<%1|||)
#define H_Ra<%1||| (%1))
#define H_Da(%1,%9,%2,%8) ha:H_Sa(,%1,%9,%2)[%8^16777619*]{}

// Test for the current character.
#define @Aa:H_Naa(%1a%0) H_Da(%1,a,%0,97)
#define @Ab:H_Nab(%1b%0) H_Da(%1,b,%0,98)
#define @Ac:H_Nac(%1c%0) H_Da(%1,c,%0,99)
#define @Ad:H_Nad(%1d%0) H_Da(%1,d,%0,100)
#define @Ae:H_Nae(%1e%0) H_Da(%1,e,%0,101)
#define @Af:H_Naf(%1f%0) H_Da(%1,f,%0,102)
#define @Ag:H_Nag(%1g%0) H_Da(%1,g,%0,103)
#define @Ah:H_Nah(%1h%0) H_Da(%1,h,%0,104)
#define @Ai:H_Nai(%1i%0) H_Da(%1,i,%0,105)
#define @Aj:H_Naj(%1j%0) H_Da(%1,j,%0,106)
#define @Ak:H_Nak(%1k%0) H_Da(%1,k,%0,107)
#define @Al:H_Nal(%1l%0) H_Da(%1,l,%0,108)
#define @Am:H_Nam(%1m%0) H_Da(%1,m,%0,109)
#define @An:H_Nan(%1n%0) H_Da(%1,n,%0,110)
#define @Ao:H_Nao(%1o%0) H_Da(%1,o,%0,111)
#define @Ap:H_Nap(%1p%0) H_Da(%1,p,%0,112)
#define @Aq:H_Naq(%1q%0) H_Da(%1,q,%0,113)
#define @Ar:H_Nar(%1r%0) H_Da(%1,r,%0,114)
#define @As:H_Nas(%1s%0) H_Da(%1,s,%0,115)
#define @At:H_Nat(%1t%0) H_Da(%1,t,%0,116)
#define @Au:H_Nau(%1u%0) H_Da(%1,u,%0,117)
#define @Av:H_Nav(%1v%0) H_Da(%1,v,%0,118)
#define @Aw:H_Naw(%1w%0) H_Da(%1,w,%0,119)
#define @Ax:H_Nax(%1x%0) H_Da(%1,x,%0,120)
#define @Ay:H_Nay(%1y%0) H_Da(%1,y,%0,121)
#define @Az:H_Naz(%1z%0) H_Da(%1,z,%0,122)

#define @AA:H_NaA(%1A%0) H_Da(%1,A,%0,65)
#define @AB:H_NaB(%1B%0) H_Da(%1,B,%0,66)
#define @AC:H_NaC(%1C%0) H_Da(%1,C,%0,67)
#define @AD:H_NaD(%1D%0) H_Da(%1,D,%0,68)
#define @AE:H_NaE(%1E%0) H_Da(%1,E,%0,69)
#define @AF:H_NaF(%1F%0) H_Da(%1,F,%0,70)
#define @AG:H_NaG(%1G%0) H_Da(%1,G,%0,71)
#define @AH:H_NaH(%1H%0) H_Da(%1,H,%0,72)
#define @AI:H_NaI(%1I%0) H_Da(%1,I,%0,73)
#define @AJ:H_NaJ(%1J%0) H_Da(%1,J,%0,74)
#define @AK:H_NaK(%1K%0) H_Da(%1,K,%0,75)
#define @AL:H_NaL(%1L%0) H_Da(%1,L,%0,76)
#define @AM:H_NaM(%1M%0) H_Da(%1,M,%0,77)
#define @AN:H_NaN(%1N%0) H_Da(%1,N,%0,78)
#define @AO:H_NaO(%1O%0) H_Da(%1,O,%0,79)
#define @AP:H_NaP(%1P%0) H_Da(%1,P,%0,80)
#define @AQ:H_NaQ(%1Q%0) H_Da(%1,Q,%0,81)
#define @AR:H_NaR(%1R%0) H_Da(%1,R,%0,82)
#define @AS:H_NaS(%1S%0) H_Da(%1,S,%0,83)
#define @AT:H_NaT(%1T%0) H_Da(%1,T,%0,84)
#define @AU:H_NaU(%1U%0) H_Da(%1,U,%0,85)
#define @AV:H_NaV(%1V%0) H_Da(%1,V,%0,86)
#define @AW:H_NaW(%1W%0) H_Da(%1,W,%0,87)
#define @AX:H_NaX(%1X%0) H_Da(%1,X,%0,88)
#define @AY:H_NaY(%1Y%0) H_Da(%1,Y,%0,89)
#define @AZ:H_NaZ(%1Z%0) H_Da(%1,Z,%0,90)

#define @A0:H_Na0(%10%0) H_Da(%1,0,%0,48)
#define @A1:H_Na1(%11%0) H_Da(%1,1,%0,49)
#define @A2:H_Na2(%12%0) H_Da(%1,2,%0,50)
#define @A3:H_Na3(%13%0) H_Da(%1,3,%0,51)
#define @A4:H_Na4(%14%0) H_Da(%1,4,%0,52)
#define @A5:H_Na5(%15%0) H_Da(%1,5,%0,53)
#define @A6:H_Na6(%16%0) H_Da(%1,6,%0,54)
#define @A7:H_Na7(%17%0) H_Da(%1,7,%0,55)
#define @A8:H_Na8(%18%0) H_Da(%1,8,%0,56)
#define @A9:H_Na9(%19%0) H_Da(%1,9,%0,57)

#define @A_:H_Na_(%1_%0) H_Da(%1,_,%0,95)
//#define ha@:H_Sa(@%0,%1) H_Da(%0)

// Find the next character to test.
#define H_Naa(%0) @Ab:H_Nab(%0)
#define H_Nab(%0) @Ac:H_Nac(%0)
#define H_Nac(%0) @Ad:H_Nad(%0)
#define H_Nad(%0) @Ae:H_Nae(%0)
#define H_Nae(%0) @Af:H_Naf(%0)
#define H_Naf(%0) @Ag:H_Nag(%0)
#define H_Nag(%0) @Ah:H_Nah(%0)
#define H_Nah(%0) @Ai:H_Nai(%0)
#define H_Nai(%0) @Aj:H_Naj(%0)
#define H_Naj(%0) @Ak:H_Nak(%0)
#define H_Nak(%0) @Al:H_Nal(%0)
#define H_Nal(%0) @Am:H_Nam(%0)
#define H_Nam(%0) @An:H_Nan(%0)
#define H_Nan(%0) @Ao:H_Nao(%0)
#define H_Nao(%0) @Ap:H_Nap(%0)
#define H_Nap(%0) @Aq:H_Naq(%0)
#define H_Naq(%0) @Ar:H_Nar(%0)
#define H_Nar(%0) @As:H_Nas(%0)
#define H_Nas(%0) @At:H_Nat(%0)
#define H_Nat(%0) @Au:H_Nau(%0)
#define H_Nau(%0) @Av:H_Nav(%0)
#define H_Nav(%0) @Aw:H_Naw(%0)
#define H_Naw(%0) @Ax:H_Nax(%0)
#define H_Nax(%0) @Ay:H_Nay(%0)
#define H_Nay(%0) @Az:H_Naz(%0)
#define H_Naz(%0) @A0:H_Na0(%0)

#define H_NaA(%0) @AB:H_NaB(%0)
#define H_NaB(%0) @AC:H_NaC(%0)
#define H_NaC(%0) @AD:H_NaD(%0)
#define H_NaD(%0) @AE:H_NaE(%0)
#define H_NaE(%0) @AF:H_NaF(%0)
#define H_NaF(%0) @AG:H_NaG(%0)
#define H_NaG(%0) @AH:H_NaH(%0)
#define H_NaH(%0) @AI:H_NaI(%0)
#define H_NaI(%0) @AJ:H_NaJ(%0)
#define H_NaJ(%0) @AK:H_NaK(%0)
#define H_NaK(%0) @AL:H_NaL(%0)
#define H_NaL(%0) @AM:H_NaM(%0)
#define H_NaM(%0) @AN:H_NaN(%0)
#define H_NaN(%0) @AO:H_NaO(%0)
#define H_NaO(%0) @AP:H_NaP(%0)
#define H_NaP(%0) @AQ:H_NaQ(%0)
#define H_NaQ(%0) @AR:H_NaR(%0)
#define H_NaR(%0) @AS:H_NaS(%0)
#define H_NaS(%0) @AT:H_NaT(%0)
#define H_NaT(%0) @AU:H_NaU(%0)
#define H_NaU(%0) @AV:H_NaV(%0)
#define H_NaV(%0) @AW:H_NaW(%0)
#define H_NaW(%0) @AX:H_NaX(%0)
#define H_NaX(%0) @AY:H_NaY(%0)
#define H_NaY(%0) @AZ:H_NaZ(%0)
#define H_NaZ(%0) H_Ea:H_Ra

#define H_Na0(%0) @A1:H_Na1(%0)
#define H_Na1(%0) @A2:H_Na2(%0)
#define H_Na2(%0) @A3:H_Na3(%0)
#define H_Na3(%0) @A4:H_Na4(%0)
#define H_Na4(%0) @A5:H_Na5(%0)
#define H_Na5(%0) @A6:H_Na6(%0)
#define H_Na6(%0) @A7:H_Na7(%0)
#define H_Na7(%0) @A8:H_Na8(%0)
#define H_Na8(%0) @A9:H_Na9(%0)
#define H_Na9(%0) @A_:H_Na_(%0)

#define H_Na_(%0) @AA:H_NaA(%0)

// ==================
//  Case insensitive 
// ==================

#define hd:H_Sd(%0,%1£%2,%9,%3)[%4]{%5}<%6<%7||| hd:H_Sd(%0%1£,%2,%9,%3)[%4]{%5<%6}<%7|||
#define H_Sd(%0,%1,%9,%3)[%4]{%5}<%6||| @D%9:H_Nd%9(%0%1£%3)%5<%4<%6|||
#define H_Ed:H_Rd<%0<%1||| (%0_:H_Ed:H_Rd<%1|||)
#define H_Rd<%1||| (%1))
#define H_Dd(%1,%9,%2,%8) hd:H_Sd(,%1,%9,%2)[%8^16777619*]{}

// Test for the current character.
#define @Da:H_Nda(%1a%0) H_Dd(%1,a,%0,65)
#define @Db:H_Ndb(%1b%0) H_Dd(%1,b,%0,66)
#define @Dc:H_Ndc(%1c%0) H_Dd(%1,c,%0,67)
#define @Dd:H_Ndd(%1d%0) H_Dd(%1,d,%0,68)
#define @De:H_Nde(%1e%0) H_Dd(%1,e,%0,69)
#define @Df:H_Ndf(%1f%0) H_Dd(%1,f,%0,70)
#define @Dg:H_Ndg(%1g%0) H_Dd(%1,g,%0,71)
#define @Dh:H_Ndh(%1h%0) H_Dd(%1,h,%0,72)
#define @Di:H_Ndi(%1i%0) H_Dd(%1,i,%0,73)
#define @Dj:H_Ndj(%1j%0) H_Dd(%1,j,%0,74)
#define @Dk:H_Ndk(%1k%0) H_Dd(%1,k,%0,75)
#define @Dl:H_Ndl(%1l%0) H_Dd(%1,l,%0,76)
#define @Dm:H_Ndm(%1m%0) H_Dd(%1,m,%0,77)
#define @Dn:H_Ndn(%1n%0) H_Dd(%1,n,%0,78)
#define @Do:H_Ndo(%1o%0) H_Dd(%1,o,%0,79)
#define @Dp:H_Ndp(%1p%0) H_Dd(%1,p,%0,80)
#define @Dq:H_Ndq(%1q%0) H_Dd(%1,q,%0,81)
#define @Dr:H_Ndr(%1r%0) H_Dd(%1,r,%0,82)
#define @Ds:H_Nds(%1s%0) H_Dd(%1,s,%0,83)
#define @Dt:H_Ndt(%1t%0) H_Dd(%1,t,%0,84)
#define @Du:H_Ndu(%1u%0) H_Dd(%1,u,%0,85)
#define @Dv:H_Ndv(%1v%0) H_Dd(%1,v,%0,86)
#define @Dw:H_Ndw(%1w%0) H_Dd(%1,w,%0,87)
#define @Dx:H_Ndx(%1x%0) H_Dd(%1,x,%0,88)
#define @Dy:H_Ndy(%1y%0) H_Dd(%1,y,%0,89)
#define @Dz:H_Ndz(%1z%0) H_Dd(%1,z,%0,90)

#define @DA:H_NdA(%1A%0) H_Dd(%1,A,%0,65)
#define @DB:H_NdB(%1B%0) H_Dd(%1,B,%0,66)
#define @DC:H_NdC(%1C%0) H_Dd(%1,C,%0,67)
#define @DD:H_NdD(%1D%0) H_Dd(%1,D,%0,68)
#define @DE:H_NdE(%1E%0) H_Dd(%1,E,%0,69)
#define @DF:H_NdF(%1F%0) H_Dd(%1,F,%0,70)
#define @DG:H_NdG(%1G%0) H_Dd(%1,G,%0,71)
#define @DH:H_NdH(%1H%0) H_Dd(%1,H,%0,72)
#define @DI:H_NdI(%1I%0) H_Dd(%1,I,%0,73)
#define @DJ:H_NdJ(%1J%0) H_Dd(%1,J,%0,74)
#define @DK:H_NdK(%1K%0) H_Dd(%1,K,%0,75)
#define @DL:H_NdL(%1L%0) H_Dd(%1,L,%0,76)
#define @DM:H_NdM(%1M%0) H_Dd(%1,M,%0,77)
#define @DN:H_NdN(%1N%0) H_Dd(%1,N,%0,78)
#define @DO:H_NdO(%1O%0) H_Dd(%1,O,%0,79)
#define @DP:H_NdP(%1P%0) H_Dd(%1,P,%0,80)
#define @DQ:H_NdQ(%1Q%0) H_Dd(%1,Q,%0,81)
#define @DR:H_NdR(%1R%0) H_Dd(%1,R,%0,82)
#define @DS:H_NdS(%1S%0) H_Dd(%1,S,%0,83)
#define @DT:H_NdT(%1T%0) H_Dd(%1,T,%0,84)
#define @DU:H_NdU(%1U%0) H_Dd(%1,U,%0,85)
#define @DV:H_NdV(%1V%0) H_Dd(%1,V,%0,86)
#define @DW:H_NdW(%1W%0) H_Dd(%1,W,%0,87)
#define @DX:H_NdX(%1X%0) H_Dd(%1,X,%0,88)
#define @DY:H_NdY(%1Y%0) H_Dd(%1,Y,%0,89)
#define @DZ:H_NdZ(%1Z%0) H_Dd(%1,Z,%0,90)

#define @D0:H_Nd0(%10%0) H_Dd(%1,0,%0,48)
#define @D1:H_Nd1(%11%0) H_Dd(%1,1,%0,49)
#define @D2:H_Nd2(%12%0) H_Dd(%1,2,%0,50)
#define @D3:H_Nd3(%13%0) H_Dd(%1,3,%0,51)
#define @D4:H_Nd4(%14%0) H_Dd(%1,4,%0,52)
#define @D5:H_Nd5(%15%0) H_Dd(%1,5,%0,53)
#define @D6:H_Nd6(%16%0) H_Dd(%1,6,%0,54)
#define @D7:H_Nd7(%17%0) H_Dd(%1,7,%0,55)
#define @D8:H_Nd8(%18%0) H_Dd(%1,8,%0,56)
#define @D9:H_Nd9(%19%0) H_Dd(%1,9,%0,57)

#define @D_:H_Nd_(%1_%0) H_Dd(%1,_,%0,95)
//#define hd@:H_Sd(@%0,%1) H_Dd(%0)

// Find the next character to test.
#define H_Nda(%0) @Db:H_Ndb(%0)
#define H_Ndb(%0) @Dc:H_Ndc(%0)
#define H_Ndc(%0) @Dd:H_Ndd(%0)
#define H_Ndd(%0) @De:H_Nde(%0)
#define H_Nde(%0) @Df:H_Ndf(%0)
#define H_Ndf(%0) @Dg:H_Ndg(%0)
#define H_Ndg(%0) @Dh:H_Ndh(%0)
#define H_Ndh(%0) @Di:H_Ndi(%0)
#define H_Ndi(%0) @Dj:H_Ndj(%0)
#define H_Ndj(%0) @Dk:H_Ndk(%0)
#define H_Ndk(%0) @Dl:H_Ndl(%0)
#define H_Ndl(%0) @Dm:H_Ndm(%0)
#define H_Ndm(%0) @Dn:H_Ndn(%0)
#define H_Ndn(%0) @Do:H_Ndo(%0)
#define H_Ndo(%0) @Dp:H_Ndp(%0)
#define H_Ndp(%0) @Dq:H_Ndq(%0)
#define H_Ndq(%0) @Dr:H_Ndr(%0)
#define H_Ndr(%0) @Ds:H_Nds(%0)
#define H_Nds(%0) @Dt:H_Ndt(%0)
#define H_Ndt(%0) @Du:H_Ndu(%0)
#define H_Ndu(%0) @Dv:H_Ndv(%0)
#define H_Ndv(%0) @Dw:H_Ndw(%0)
#define H_Ndw(%0) @Dx:H_Ndx(%0)
#define H_Ndx(%0) @Dy:H_Ndy(%0)
#define H_Ndy(%0) @Dz:H_Ndz(%0)
#define H_Ndz(%0) @D0:H_Nd0(%0)

#define H_NdA(%0) @DB:H_NdB(%0)
#define H_NdB(%0) @DC:H_NdC(%0)
#define H_NdC(%0) @DD:H_NdD(%0)
#define H_NdD(%0) @DE:H_NdE(%0)
#define H_NdE(%0) @DF:H_NdF(%0)
#define H_NdF(%0) @DG:H_NdG(%0)
#define H_NdG(%0) @DH:H_NdH(%0)
#define H_NdH(%0) @DI:H_NdI(%0)
#define H_NdI(%0) @DJ:H_NdJ(%0)
#define H_NdJ(%0) @DK:H_NdK(%0)
#define H_NdK(%0) @DL:H_NdL(%0)
#define H_NdL(%0) @DM:H_NdM(%0)
#define H_NdM(%0) @DN:H_NdN(%0)
#define H_NdN(%0) @DO:H_NdO(%0)
#define H_NdO(%0) @DP:H_NdP(%0)
#define H_NdP(%0) @DQ:H_NdQ(%0)
#define H_NdQ(%0) @DR:H_NdR(%0)
#define H_NdR(%0) @DS:H_NdS(%0)
#define H_NdS(%0) @DT:H_NdT(%0)
#define H_NdT(%0) @DU:H_NdU(%0)
#define H_NdU(%0) @DV:H_NdV(%0)
#define H_NdV(%0) @DW:H_NdW(%0)
#define H_NdW(%0) @DX:H_NdX(%0)
#define H_NdX(%0) @DY:H_NdY(%0)
#define H_NdY(%0) @DZ:H_NdZ(%0)
#define H_NdZ(%0) H_Ed:H_Rd

#define H_Nd0(%0) @D1:H_Nd1(%0)
#define H_Nd1(%0) @D2:H_Nd2(%0)
#define H_Nd2(%0) @D3:H_Nd3(%0)
#define H_Nd3(%0) @D4:H_Nd4(%0)
#define H_Nd4(%0) @D5:H_Nd5(%0)
#define H_Nd5(%0) @D6:H_Nd6(%0)
#define H_Nd6(%0) @D7:H_Nd7(%0)
#define H_Nd7(%0) @D8:H_Nd8(%0)
#define H_Nd8(%0) @D9:H_Nd9(%0)
#define H_Nd9(%0) @D_:H_Nd_(%0)

#define H_Nd_(%0) @DA:H_NdA(%0)

// =============
//  Old version 
// =============

// ================
//  Case sensitive 
// ================

// These are the default values
//#define HASH(%0,%1) HASH@%0(%1)

/*#define _H@b HASH@bernstein
#define _H@f HASH@fnv1
#define _H@a HASH@fnv1a*/

// ================
//  Bernstein hash 
// ================

// Signify the end with two "@" symbols.
#define HASH@bernstein(%0) _REHASH@b(%0,@,@)

// Internal call.
#define _REHASH@b(%0,%1) _HASH@b_%0(%1)

// The bit that actually does the work.
#define _DOHASH@b(%0,%1,%2) (_HASH@b_%1(%2)*33+%0)

// Space.
#define _HASH@b_(%0) _DOHASH@b(32,%0)

// Numbers.
#define _HASH@b_0(%0) _DOHASH@b(48,%0)
#define _HASH@b_1(%0) _DOHASH@b(49,%0)
#define _HASH@b_2(%0) _DOHASH@b(50,%0)
#define _HASH@b_3(%0) _DOHASH@b(51,%0)
#define _HASH@b_4(%0) _DOHASH@b(52,%0)
#define _HASH@b_5(%0) _DOHASH@b(53,%0)
#define _HASH@b_6(%0) _DOHASH@b(54,%0)
#define _HASH@b_7(%0) _DOHASH@b(55,%0)
#define _HASH@b_8(%0) _DOHASH@b(56,%0)
#define _HASH@b_9(%0) _DOHASH@b(57,%0)

// Upper case letters.
#define _HASH@b_A(%0) _DOHASH@b(65,%0)
#define _HASH@b_B(%0) _DOHASH@b(66,%0)
#define _HASH@b_C(%0) _DOHASH@b(67,%0)
#define _HASH@b_D(%0) _DOHASH@b(68,%0)
#define _HASH@b_E(%0) _DOHASH@b(69,%0)
#define _HASH@b_F(%0) _DOHASH@b(70,%0)
#define _HASH@b_G(%0) _DOHASH@b(71,%0)
#define _HASH@b_H(%0) _DOHASH@b(72,%0)
#define _HASH@b_I(%0) _DOHASH@b(73,%0)
#define _HASH@b_J(%0) _DOHASH@b(74,%0)
#define _HASH@b_K(%0) _DOHASH@b(75,%0)
#define _HASH@b_L(%0) _DOHASH@b(76,%0)
#define _HASH@b_M(%0) _DOHASH@b(77,%0)
#define _HASH@b_N(%0) _DOHASH@b(78,%0)
#define _HASH@b_O(%0) _DOHASH@b(79,%0)
#define _HASH@b_P(%0) _DOHASH@b(80,%0)
#define _HASH@b_Q(%0) _DOHASH@b(81,%0)
#define _HASH@b_R(%0) _DOHASH@b(82,%0)
#define _HASH@b_S(%0) _DOHASH@b(83,%0)
#define _HASH@b_T(%0) _DOHASH@b(84,%0)
#define _HASH@b_U(%0) _DOHASH@b(85,%0)
#define _HASH@b_V(%0) _DOHASH@b(86,%0)
#define _HASH@b_W(%0) _DOHASH@b(87,%0)
#define _HASH@b_X(%0) _DOHASH@b(88,%0)
#define _HASH@b_Y(%0) _DOHASH@b(89,%0)
#define _HASH@b_Z(%0) _DOHASH@b(90,%0)

// Underscore.
#define _HASH@b__(%0) _DOHASH@b(95,%0)

// Lower case letters.
#define _HASH@b_a(%0) _DOHASH@b(97,%0)
#define _HASH@b_b(%0) _DOHASH@b(98,%0)
#define _HASH@b_c(%0) _DOHASH@b(99,%0)
#define _HASH@b_d(%0) _DOHASH@b(100,%0)
#define _HASH@b_e(%0) _DOHASH@b(101,%0)
#define _HASH@b_f(%0) _DOHASH@b(102,%0)
#define _HASH@b_g(%0) _DOHASH@b(103,%0)
#define _HASH@b_h(%0) _DOHASH@b(104,%0)
#define _HASH@b_i(%0) _DOHASH@b(105,%0)
#define _HASH@b_j(%0) _DOHASH@b(106,%0)
#define _HASH@b_k(%0) _DOHASH@b(107,%0)
#define _HASH@b_l(%0) _DOHASH@b(108,%0)
#define _HASH@b_m(%0) _DOHASH@b(109,%0)
#define _HASH@b_n(%0) _DOHASH@b(110,%0)
#define _HASH@b_o(%0) _DOHASH@b(111,%0)
#define _HASH@b_p(%0) _DOHASH@b(112,%0)
#define _HASH@b_q(%0) _DOHASH@b(113,%0)
#define _HASH@b_r(%0) _DOHASH@b(114,%0)
#define _HASH@b_s(%0) _DOHASH@b(115,%0)
#define _HASH@b_t(%0) _DOHASH@b(116,%0)
#define _HASH@b_u(%0) _DOHASH@b(117,%0)
#define _HASH@b_v(%0) _DOHASH@b(118,%0)
#define _HASH@b_w(%0) _DOHASH@b(119,%0)
#define _HASH@b_x(%0) _DOHASH@b(120,%0)
#define _HASH@b_y(%0) _DOHASH@b(121,%0)
#define _HASH@b_z(%0) _DOHASH@b(122,%0)

// String end.
#define _HASH@b_@(%0) -1

// ===========
//  FNV1 hash 
// ===========

// Signify the end with two "@" symbols.
#define HASH@fnv1(%0) _REHASH@f(%0,@,@)

// Internal call.
#define _REHASH@f(%0,%1) _HASH@f_%0(%1)

// The bit that actually does the work.
#define _DOHASH@f(%0,%1,%2) (_HASH@f_%1(%2)*16777619^%0)

// Space.
#define _HASH@f_(%0) _DOHASH@f(32,%0)

// Numbers.
#define _HASH@f_0(%0) _DOHASH@f(48,%0)
#define _HASH@f_1(%0) _DOHASH@f(49,%0)
#define _HASH@f_2(%0) _DOHASH@f(50,%0)
#define _HASH@f_3(%0) _DOHASH@f(51,%0)
#define _HASH@f_4(%0) _DOHASH@f(52,%0)
#define _HASH@f_5(%0) _DOHASH@f(53,%0)
#define _HASH@f_6(%0) _DOHASH@f(54,%0)
#define _HASH@f_7(%0) _DOHASH@f(55,%0)
#define _HASH@f_8(%0) _DOHASH@f(56,%0)
#define _HASH@f_9(%0) _DOHASH@f(57,%0)

// Upper case letters.
#define _HASH@f_A(%0) _DOHASH@f(65,%0)
#define _HASH@f_B(%0) _DOHASH@f(66,%0)
#define _HASH@f_C(%0) _DOHASH@f(67,%0)
#define _HASH@f_D(%0) _DOHASH@f(68,%0)
#define _HASH@f_E(%0) _DOHASH@f(69,%0)
#define _HASH@f_F(%0) _DOHASH@f(70,%0)
#define _HASH@f_G(%0) _DOHASH@f(71,%0)
#define _HASH@f_H(%0) _DOHASH@f(72,%0)
#define _HASH@f_I(%0) _DOHASH@f(73,%0)
#define _HASH@f_J(%0) _DOHASH@f(74,%0)
#define _HASH@f_K(%0) _DOHASH@f(75,%0)
#define _HASH@f_L(%0) _DOHASH@f(76,%0)
#define _HASH@f_M(%0) _DOHASH@f(77,%0)
#define _HASH@f_N(%0) _DOHASH@f(78,%0)
#define _HASH@f_O(%0) _DOHASH@f(79,%0)
#define _HASH@f_P(%0) _DOHASH@f(80,%0)
#define _HASH@f_Q(%0) _DOHASH@f(81,%0)
#define _HASH@f_R(%0) _DOHASH@f(82,%0)
#define _HASH@f_S(%0) _DOHASH@f(83,%0)
#define _HASH@f_T(%0) _DOHASH@f(84,%0)
#define _HASH@f_U(%0) _DOHASH@f(85,%0)
#define _HASH@f_V(%0) _DOHASH@f(86,%0)
#define _HASH@f_W(%0) _DOHASH@f(87,%0)
#define _HASH@f_X(%0) _DOHASH@f(88,%0)
#define _HASH@f_Y(%0) _DOHASH@f(89,%0)
#define _HASH@f_Z(%0) _DOHASH@f(90,%0)

// Underscore.
#define _HASH@f__(%0) _DOHASH@f(95,%0)

// Lower case letters.
#define _HASH@f_a(%0) _DOHASH@f(97,%0)
#define _HASH@f_b(%0) _DOHASH@f(98,%0)
#define _HASH@f_c(%0) _DOHASH@f(99,%0)
#define _HASH@f_d(%0) _DOHASH@f(100,%0)
#define _HASH@f_e(%0) _DOHASH@f(101,%0)
#define _HASH@f_f(%0) _DOHASH@f(102,%0)
#define _HASH@f_g(%0) _DOHASH@f(103,%0)
#define _HASH@f_h(%0) _DOHASH@f(104,%0)
#define _HASH@f_i(%0) _DOHASH@f(105,%0)
#define _HASH@f_j(%0) _DOHASH@f(106,%0)
#define _HASH@f_k(%0) _DOHASH@f(107,%0)
#define _HASH@f_l(%0) _DOHASH@f(108,%0)
#define _HASH@f_m(%0) _DOHASH@f(109,%0)
#define _HASH@f_n(%0) _DOHASH@f(110,%0)
#define _HASH@f_o(%0) _DOHASH@f(111,%0)
#define _HASH@f_p(%0) _DOHASH@f(112,%0)
#define _HASH@f_q(%0) _DOHASH@f(113,%0)
#define _HASH@f_r(%0) _DOHASH@f(114,%0)
#define _HASH@f_s(%0) _DOHASH@f(115,%0)
#define _HASH@f_t(%0) _DOHASH@f(116,%0)
#define _HASH@f_u(%0) _DOHASH@f(117,%0)
#define _HASH@f_v(%0) _DOHASH@f(118,%0)
#define _HASH@f_w(%0) _DOHASH@f(119,%0)
#define _HASH@f_x(%0) _DOHASH@f(120,%0)
#define _HASH@f_y(%0) _DOHASH@f(121,%0)
#define _HASH@f_z(%0) _DOHASH@f(122,%0)

// String end.
#define _HASH@f_@(%0) 2166136261

// ============
//  FNV1a hash 
// ============

// Signify the end with two "@" symbols.
#define HASH@fnv1a(%0) _REHASH@a(%0,@,@)

// Internal call.
#define _REHASH@a(%0,%1) _HASH@a_%0(%1)

// The bit that actually does the work.
#define _DOHASH@a(%0,%1,%2) ((_HASH@a_%1(%2)^%0)*16777619)

// Space.
#define _HASH@a_(%0) _DOHASH@a(32,%0)

// Numbers.
#define _HASH@a_0(%0) _DOHASH@a(48,%0)
#define _HASH@a_1(%0) _DOHASH@a(49,%0)
#define _HASH@a_2(%0) _DOHASH@a(50,%0)
#define _HASH@a_3(%0) _DOHASH@a(51,%0)
#define _HASH@a_4(%0) _DOHASH@a(52,%0)
#define _HASH@a_5(%0) _DOHASH@a(53,%0)
#define _HASH@a_6(%0) _DOHASH@a(54,%0)
#define _HASH@a_7(%0) _DOHASH@a(55,%0)
#define _HASH@a_8(%0) _DOHASH@a(56,%0)
#define _HASH@a_9(%0) _DOHASH@a(57,%0)

// Upper case letters.
#define _HASH@a_A(%0) _DOHASH@a(65,%0)
#define _HASH@a_B(%0) _DOHASH@a(66,%0)
#define _HASH@a_C(%0) _DOHASH@a(67,%0)
#define _HASH@a_D(%0) _DOHASH@a(68,%0)
#define _HASH@a_E(%0) _DOHASH@a(69,%0)
#define _HASH@a_F(%0) _DOHASH@a(70,%0)
#define _HASH@a_G(%0) _DOHASH@a(71,%0)
#define _HASH@a_H(%0) _DOHASH@a(72,%0)
#define _HASH@a_I(%0) _DOHASH@a(73,%0)
#define _HASH@a_J(%0) _DOHASH@a(74,%0)
#define _HASH@a_K(%0) _DOHASH@a(75,%0)
#define _HASH@a_L(%0) _DOHASH@a(76,%0)
#define _HASH@a_M(%0) _DOHASH@a(77,%0)
#define _HASH@a_N(%0) _DOHASH@a(78,%0)
#define _HASH@a_O(%0) _DOHASH@a(79,%0)
#define _HASH@a_P(%0) _DOHASH@a(80,%0)
#define _HASH@a_Q(%0) _DOHASH@a(81,%0)
#define _HASH@a_R(%0) _DOHASH@a(82,%0)
#define _HASH@a_S(%0) _DOHASH@a(83,%0)
#define _HASH@a_T(%0) _DOHASH@a(84,%0)
#define _HASH@a_U(%0) _DOHASH@a(85,%0)
#define _HASH@a_V(%0) _DOHASH@a(86,%0)
#define _HASH@a_W(%0) _DOHASH@a(87,%0)
#define _HASH@a_X(%0) _DOHASH@a(88,%0)
#define _HASH@a_Y(%0) _DOHASH@a(89,%0)
#define _HASH@a_Z(%0) _DOHASH@a(90,%0)

// Underscore.
#define _HASH@a__(%0) _DOHASH@a(95,%0)

// Lower case letters.
#define _HASH@a_a(%0) _DOHASH@a(97,%0)
#define _HASH@a_b(%0) _DOHASH@a(98,%0)
#define _HASH@a_c(%0) _DOHASH@a(99,%0)
#define _HASH@a_d(%0) _DOHASH@a(100,%0)
#define _HASH@a_e(%0) _DOHASH@a(101,%0)
#define _HASH@a_f(%0) _DOHASH@a(102,%0)
#define _HASH@a_g(%0) _DOHASH@a(103,%0)
#define _HASH@a_h(%0) _DOHASH@a(104,%0)
#define _HASH@a_i(%0) _DOHASH@a(105,%0)
#define _HASH@a_j(%0) _DOHASH@a(106,%0)
#define _HASH@a_k(%0) _DOHASH@a(107,%0)
#define _HASH@a_l(%0) _DOHASH@a(108,%0)
#define _HASH@a_m(%0) _DOHASH@a(109,%0)
#define _HASH@a_n(%0) _DOHASH@a(110,%0)
#define _HASH@a_o(%0) _DOHASH@a(111,%0)
#define _HASH@a_p(%0) _DOHASH@a(112,%0)
#define _HASH@a_q(%0) _DOHASH@a(113,%0)
#define _HASH@a_r(%0) _DOHASH@a(114,%0)
#define _HASH@a_s(%0) _DOHASH@a(115,%0)
#define _HASH@a_t(%0) _DOHASH@a(116,%0)
#define _HASH@a_u(%0) _DOHASH@a(117,%0)
#define _HASH@a_v(%0) _DOHASH@a(118,%0)
#define _HASH@a_w(%0) _DOHASH@a(119,%0)
#define _HASH@a_x(%0) _DOHASH@a(120,%0)
#define _HASH@a_y(%0) _DOHASH@a(121,%0)
#define _HASH@a_z(%0) _DOHASH@a(122,%0)

// String end.
#define _HASH@a_@(%0) 2166136261

// ==================
//  Case insensitive 
// ==================

// These are the default values
//#define HASHi(%0,%1) HASHi@%0(%1)

//#define _I(%0) _REHASib(%0,@,@)

/*#define _I@b HASHi@bernstein
#define _I@f HASHi@fnv1
#define _I@a HASHi@fnv1a*/

// ================
//  Bernstein hash 
// ================

// Signify the end with two "@" symbols.
#define HASHi@bernstein(%0) _REHASH@ib(%0,@,@)

// Internal call.
#define _REHASH@ib(%0,%1) _HASH@ib_%0(%1)

// The bit that actually does the work.
#define _DOHASH@ib(%0,%1,%2) (_HASH@ib_%1(%2)*33+%0)

// Space.
#define _HASH@ib_(%0) _DOHASH@ib(32,%0)

// Numbers.
#define _HASH@ib_0(%0) _DOHASH@ib(48,%0)
#define _HASH@ib_1(%0) _DOHASH@ib(49,%0)
#define _HASH@ib_2(%0) _DOHASH@ib(50,%0)
#define _HASH@ib_3(%0) _DOHASH@ib(51,%0)
#define _HASH@ib_4(%0) _DOHASH@ib(52,%0)
#define _HASH@ib_5(%0) _DOHASH@ib(53,%0)
#define _HASH@ib_6(%0) _DOHASH@ib(54,%0)
#define _HASH@ib_7(%0) _DOHASH@ib(55,%0)
#define _HASH@ib_8(%0) _DOHASH@ib(56,%0)
#define _HASH@ib_9(%0) _DOHASH@ib(57,%0)

// Upper case letters.
#define _HASH@ib_A(%0) _DOHASH@ib(65,%0)
#define _HASH@ib_B(%0) _DOHASH@ib(66,%0)
#define _HASH@ib_C(%0) _DOHASH@ib(67,%0)
#define _HASH@ib_D(%0) _DOHASH@ib(68,%0)
#define _HASH@ib_E(%0) _DOHASH@ib(69,%0)
#define _HASH@ib_F(%0) _DOHASH@ib(70,%0)
#define _HASH@ib_G(%0) _DOHASH@ib(71,%0)
#define _HASH@ib_H(%0) _DOHASH@ib(72,%0)
#define _HASH@ib_I(%0) _DOHASH@ib(73,%0)
#define _HASH@ib_J(%0) _DOHASH@ib(74,%0)
#define _HASH@ib_K(%0) _DOHASH@ib(75,%0)
#define _HASH@ib_L(%0) _DOHASH@ib(76,%0)
#define _HASH@ib_M(%0) _DOHASH@ib(77,%0)
#define _HASH@ib_N(%0) _DOHASH@ib(78,%0)
#define _HASH@ib_O(%0) _DOHASH@ib(79,%0)
#define _HASH@ib_P(%0) _DOHASH@ib(80,%0)
#define _HASH@ib_Q(%0) _DOHASH@ib(81,%0)
#define _HASH@ib_R(%0) _DOHASH@ib(82,%0)
#define _HASH@ib_S(%0) _DOHASH@ib(83,%0)
#define _HASH@ib_T(%0) _DOHASH@ib(84,%0)
#define _HASH@ib_U(%0) _DOHASH@ib(85,%0)
#define _HASH@ib_V(%0) _DOHASH@ib(86,%0)
#define _HASH@ib_W(%0) _DOHASH@ib(87,%0)
#define _HASH@ib_X(%0) _DOHASH@ib(88,%0)
#define _HASH@ib_Y(%0) _DOHASH@ib(89,%0)
#define _HASH@ib_Z(%0) _DOHASH@ib(90,%0)

// Underscore.
#define _HASH@ib__(%0) _DOHASH@ib(95,%0)

// Lower case letters.
#define _HASH@ib_a(%0) _DOHASH@ib(65,%0)
#define _HASH@ib_b(%0) _DOHASH@ib(66,%0)
#define _HASH@ib_c(%0) _DOHASH@ib(67,%0)
#define _HASH@ib_d(%0) _DOHASH@ib(68,%0)
#define _HASH@ib_e(%0) _DOHASH@ib(69,%0)
#define _HASH@ib_f(%0) _DOHASH@ib(70,%0)
#define _HASH@ib_g(%0) _DOHASH@ib(71,%0)
#define _HASH@ib_h(%0) _DOHASH@ib(72,%0)
#define _HASH@ib_i(%0) _DOHASH@ib(73,%0)
#define _HASH@ib_j(%0) _DOHASH@ib(74,%0)
#define _HASH@ib_k(%0) _DOHASH@ib(75,%0)
#define _HASH@ib_l(%0) _DOHASH@ib(76,%0)
#define _HASH@ib_m(%0) _DOHASH@ib(77,%0)
#define _HASH@ib_n(%0) _DOHASH@ib(78,%0)
#define _HASH@ib_o(%0) _DOHASH@ib(79,%0)
#define _HASH@ib_p(%0) _DOHASH@ib(80,%0)
#define _HASH@ib_q(%0) _DOHASH@ib(81,%0)
#define _HASH@ib_r(%0) _DOHASH@ib(82,%0)
#define _HASH@ib_s(%0) _DOHASH@ib(83,%0)
#define _HASH@ib_t(%0) _DOHASH@ib(84,%0)
#define _HASH@ib_u(%0) _DOHASH@ib(85,%0)
#define _HASH@ib_v(%0) _DOHASH@ib(86,%0)
#define _HASH@ib_w(%0) _DOHASH@ib(87,%0)
#define _HASH@ib_x(%0) _DOHASH@ib(88,%0)
#define _HASH@ib_y(%0) _DOHASH@ib(89,%0)
#define _HASH@ib_z(%0) _DOHASH@ib(90,%0)

// String end.
#define _HASH@ib_@(%0) -1

// ===========
//  FNV1 hash 
// ===========

// Signify the end with two "@" symbols.
#define HASHi@fnv1(%0) _REHASH@if(%0,@,@)

// Internal call.
#define _REHASH@if(%0,%1) _HASH@if_%0(%1)

// The bit that actually does the work.
#define _DOHASH@if(%0,%1,%2) (_HASH@if_%1(%2)*16777619^%0)

// Space.
#define _HASH@if_(%0) _DOHASH@if(32,%0)

// Numbers.
#define _HASH@if_0(%0) _DOHASH@if(48,%0)
#define _HASH@if_1(%0) _DOHASH@if(49,%0)
#define _HASH@if_2(%0) _DOHASH@if(50,%0)
#define _HASH@if_3(%0) _DOHASH@if(51,%0)
#define _HASH@if_4(%0) _DOHASH@if(52,%0)
#define _HASH@if_5(%0) _DOHASH@if(53,%0)
#define _HASH@if_6(%0) _DOHASH@if(54,%0)
#define _HASH@if_7(%0) _DOHASH@if(55,%0)
#define _HASH@if_8(%0) _DOHASH@if(56,%0)
#define _HASH@if_9(%0) _DOHASH@if(57,%0)

// Upper case letters.
#define _HASH@if_A(%0) _DOHASH@if(65,%0)
#define _HASH@if_B(%0) _DOHASH@if(66,%0)
#define _HASH@if_C(%0) _DOHASH@if(67,%0)
#define _HASH@if_D(%0) _DOHASH@if(68,%0)
#define _HASH@if_E(%0) _DOHASH@if(69,%0)
#define _HASH@if_F(%0) _DOHASH@if(70,%0)
#define _HASH@if_G(%0) _DOHASH@if(71,%0)
#define _HASH@if_H(%0) _DOHASH@if(72,%0)
#define _HASH@if_I(%0) _DOHASH@if(73,%0)
#define _HASH@if_J(%0) _DOHASH@if(74,%0)
#define _HASH@if_K(%0) _DOHASH@if(75,%0)
#define _HASH@if_L(%0) _DOHASH@if(76,%0)
#define _HASH@if_M(%0) _DOHASH@if(77,%0)
#define _HASH@if_N(%0) _DOHASH@if(78,%0)
#define _HASH@if_O(%0) _DOHASH@if(79,%0)
#define _HASH@if_P(%0) _DOHASH@if(80,%0)
#define _HASH@if_Q(%0) _DOHASH@if(81,%0)
#define _HASH@if_R(%0) _DOHASH@if(82,%0)
#define _HASH@if_S(%0) _DOHASH@if(83,%0)
#define _HASH@if_T(%0) _DOHASH@if(84,%0)
#define _HASH@if_U(%0) _DOHASH@if(85,%0)
#define _HASH@if_V(%0) _DOHASH@if(86,%0)
#define _HASH@if_W(%0) _DOHASH@if(87,%0)
#define _HASH@if_X(%0) _DOHASH@if(88,%0)
#define _HASH@if_Y(%0) _DOHASH@if(89,%0)
#define _HASH@if_Z(%0) _DOHASH@if(90,%0)

// Underscore.
#define _HASH@if__(%0) _DOHASH@if(95,%0)

// Lower case letters.
#define _HASH@if_a(%0) _DOHASH@if(65,%0)
#define _HASH@if_b(%0) _DOHASH@if(66,%0)
#define _HASH@if_c(%0) _DOHASH@if(67,%0)
#define _HASH@if_d(%0) _DOHASH@if(68,%0)
#define _HASH@if_e(%0) _DOHASH@if(69,%0)
#define _HASH@if_f(%0) _DOHASH@if(70,%0)
#define _HASH@if_g(%0) _DOHASH@if(71,%0)
#define _HASH@if_h(%0) _DOHASH@if(72,%0)
#define _HASH@if_i(%0) _DOHASH@if(73,%0)
#define _HASH@if_j(%0) _DOHASH@if(74,%0)
#define _HASH@if_k(%0) _DOHASH@if(75,%0)
#define _HASH@if_l(%0) _DOHASH@if(76,%0)
#define _HASH@if_m(%0) _DOHASH@if(77,%0)
#define _HASH@if_n(%0) _DOHASH@if(78,%0)
#define _HASH@if_o(%0) _DOHASH@if(79,%0)
#define _HASH@if_p(%0) _DOHASH@if(80,%0)
#define _HASH@if_q(%0) _DOHASH@if(81,%0)
#define _HASH@if_r(%0) _DOHASH@if(82,%0)
#define _HASH@if_s(%0) _DOHASH@if(83,%0)
#define _HASH@if_t(%0) _DOHASH@if(84,%0)
#define _HASH@if_u(%0) _DOHASH@if(85,%0)
#define _HASH@if_v(%0) _DOHASH@if(86,%0)
#define _HASH@if_w(%0) _DOHASH@if(87,%0)
#define _HASH@if_x(%0) _DOHASH@if(88,%0)
#define _HASH@if_y(%0) _DOHASH@if(89,%0)
#define _HASH@if_z(%0) _DOHASH@if(90,%0)

// String end.
#define _HASH@if_@(%0) 2166136261

// ============
//  FNV1a hash 
// ============

// Signify the end with two "@" symbols.
#define HASHi@fnv1a(%0) _REHASH@ia(%0,@,@)

// Internal call.
#define _REHASH@ia(%0,%1) _HASH@ia_%0(%1)

// The bit that actually does the work.
#define _DOHASH@ia(%0,%1,%2) ((_HASH@ia_%1(%2)^%0)*16777619)

// Space.
#define _HASH@ia_(%0) _DOHASH@ia(32,%0)

// Numbers.
#define _HASH@ia_0(%0) _DOHASH@ia(48,%0)
#define _HASH@ia_1(%0) _DOHASH@ia(49,%0)
#define _HASH@ia_2(%0) _DOHASH@ia(50,%0)
#define _HASH@ia_3(%0) _DOHASH@ia(51,%0)
#define _HASH@ia_4(%0) _DOHASH@ia(52,%0)
#define _HASH@ia_5(%0) _DOHASH@ia(53,%0)
#define _HASH@ia_6(%0) _DOHASH@ia(54,%0)
#define _HASH@ia_7(%0) _DOHASH@ia(55,%0)
#define _HASH@ia_8(%0) _DOHASH@ia(56,%0)
#define _HASH@ia_9(%0) _DOHASH@ia(57,%0)

// Upper case letters.
#define _HASH@ia_A(%0) _DOHASH@ia(65,%0)
#define _HASH@ia_B(%0) _DOHASH@ia(66,%0)
#define _HASH@ia_C(%0) _DOHASH@ia(67,%0)
#define _HASH@ia_D(%0) _DOHASH@ia(68,%0)
#define _HASH@ia_E(%0) _DOHASH@ia(69,%0)
#define _HASH@ia_F(%0) _DOHASH@ia(70,%0)
#define _HASH@ia_G(%0) _DOHASH@ia(71,%0)
#define _HASH@ia_H(%0) _DOHASH@ia(72,%0)
#define _HASH@ia_I(%0) _DOHASH@ia(73,%0)
#define _HASH@ia_J(%0) _DOHASH@ia(74,%0)
#define _HASH@ia_K(%0) _DOHASH@ia(75,%0)
#define _HASH@ia_L(%0) _DOHASH@ia(76,%0)
#define _HASH@ia_M(%0) _DOHASH@ia(77,%0)
#define _HASH@ia_N(%0) _DOHASH@ia(78,%0)
#define _HASH@ia_O(%0) _DOHASH@ia(79,%0)
#define _HASH@ia_P(%0) _DOHASH@ia(80,%0)
#define _HASH@ia_Q(%0) _DOHASH@ia(81,%0)
#define _HASH@ia_R(%0) _DOHASH@ia(82,%0)
#define _HASH@ia_S(%0) _DOHASH@ia(83,%0)
#define _HASH@ia_T(%0) _DOHASH@ia(84,%0)
#define _HASH@ia_U(%0) _DOHASH@ia(85,%0)
#define _HASH@ia_V(%0) _DOHASH@ia(86,%0)
#define _HASH@ia_W(%0) _DOHASH@ia(87,%0)
#define _HASH@ia_X(%0) _DOHASH@ia(88,%0)
#define _HASH@ia_Y(%0) _DOHASH@ia(89,%0)
#define _HASH@ia_Z(%0) _DOHASH@ia(90,%0)

// Underscore.
#define _HASH@ia__(%0) _DOHASH@ia(95,%0)

// Lower case letters.
#define _HASH@ia_a(%0) _DOHASH@ia(65,%0)
#define _HASH@ia_b(%0) _DOHASH@ia(66,%0)
#define _HASH@ia_c(%0) _DOHASH@ia(67,%0)
#define _HASH@ia_d(%0) _DOHASH@ia(68,%0)
#define _HASH@ia_e(%0) _DOHASH@ia(69,%0)
#define _HASH@ia_f(%0) _DOHASH@ia(70,%0)
#define _HASH@ia_g(%0) _DOHASH@ia(71,%0)
#define _HASH@ia_h(%0) _DOHASH@ia(72,%0)
#define _HASH@ia_i(%0) _DOHASH@ia(73,%0)
#define _HASH@ia_j(%0) _DOHASH@ia(74,%0)
#define _HASH@ia_k(%0) _DOHASH@ia(75,%0)
#define _HASH@ia_l(%0) _DOHASH@ia(76,%0)
#define _HASH@ia_m(%0) _DOHASH@ia(77,%0)
#define _HASH@ia_n(%0) _DOHASH@ia(78,%0)
#define _HASH@ia_o(%0) _DOHASH@ia(79,%0)
#define _HASH@ia_p(%0) _DOHASH@ia(80,%0)
#define _HASH@ia_q(%0) _DOHASH@ia(81,%0)
#define _HASH@ia_r(%0) _DOHASH@ia(82,%0)
#define _HASH@ia_s(%0) _DOHASH@ia(83,%0)
#define _HASH@ia_t(%0) _DOHASH@ia(84,%0)
#define _HASH@ia_u(%0) _DOHASH@ia(85,%0)
#define _HASH@ia_v(%0) _DOHASH@ia(86,%0)
#define _HASH@ia_w(%0) _DOHASH@ia(87,%0)
#define _HASH@ia_x(%0) _DOHASH@ia(88,%0)
#define _HASH@ia_y(%0) _DOHASH@ia(89,%0)
#define _HASH@ia_z(%0) _DOHASH@ia(90,%0)

// String end.
#define _HASH@ia_@(%0) 2166136261

// ============
//  Other code 
// ============

enum e_HASH_TYPE
{
	hash_bernstein,
	hash_fnv1,
	hash_fnv1a
}

/**--------------------------------------------------------------------------**\
<summary>Hash</summary>
<param name="str">The string to hash.</param>
<param name="sensitive">Wether the hash is case sensitive or not.</param>
<returns>
	The reverse Bernstein hash of the string.
</returns>
<remarks>
	Based on Bernstein hash, but backwards to match the macros.  The only
	characters which can be used in the compile time version of this code are:
	a-z, A-Z, 0-9, _ and space.

native Hash(str[]);

</remarks>
\**--------------------------------------------------------------------------**/

stock YHash(const str[], bool:sensitive = true, e_HASH_TYPE:type = hash_bernstein, len = -1, pack = false)
{
	P:3("YHash called: \"%s\", %i, %i, %i, %i", str, _:sensitive, _:type, len, pack);
	
	pack = str[0] > 255;

	if (len == -1)
	{
		len = strlen(str);
	}
	if (pack)
	{
		switch (type)
		{
			case hash_bernstein:
			{
				new
					hash = -1;
				if (sensitive)
				{
					while (len--)
					{
						hash = hash * 33 + str{len};
					}
				}
				else
				{
					while (len--)
					{
						new
							ch = str{len};
						if ('a' <= ch <= 'z')
						{
							ch &= ~0x20;
						}
						hash = hash * 33 + ch;
					}
				}
				return hash;
			}
			case hash_fnv1:
			{
				new
					hash = 2166136261;
				if (sensitive)
				{
					while (len--)
					{
						hash = hash * 16777619 ^ str{len};
					}
				}
				else
				{
					while (len--)
					{
						new
							ch = str{len};
						if ('a' <= ch <= 'z')
						{
							ch &= ~0x20;
						}
						hash = hash * 16777619 ^ ch;
					}
				}
				return hash;
			}
			case hash_fnv1a:
			{
				new
					hash = 2166136261;
				if (sensitive)
				{
					while (len--)
					{
						hash = (hash ^ str{len}) * 16777619;
					}
				}
				else
				{
					while (len--)
					{
						new
							ch = str{len};
						if ('a' <= ch <= 'z')
						{
							ch &= ~0x20;
						}
						hash = (hash ^ ch) * 16777619;
					}
				}
				return hash;
			}
		}
	}
	else
	{
		switch (type)
		{
			case hash_bernstein:
			{
				new
					hash = -1;
				if (sensitive)
				{
					while (len--)
					{
						hash = hash * 33 + str[len];
					}
				}
				else
				{
					while (len--)
					{
						new
							ch = str[len];
						if ('a' <= ch <= 'z')
						{
							ch &= ~0x20;
						}
						hash = hash * 33 + ch;
					}
				}
				return hash;
			}
			case hash_fnv1:
			{
				new
					hash = 2166136261;
				if (sensitive)
				{
					while (len--)
					{
						hash = hash * 16777619 ^ str[len];
					}
				}
				else
				{
					while (len--)
					{
						new
							ch = str[len];
						if ('a' <= ch <= 'z')
						{
							ch &= ~0x20;
						}
						hash = hash * 16777619 ^ ch;
					}
				}
				return hash;
			}
			case hash_fnv1a:
			{
				new
					hash = 2166136261;
				if (sensitive)
				{
					while (len--)
					{
						hash = (hash ^ str[len]) * 16777619;
					}
				}
				else
				{
					while (len--)
					{
						new
							ch = str[len];
						if ('a' <= ch <= 'z')
						{
							ch &= ~0x20;
						}
						hash = (hash ^ ch) * 16777619;
					}
				}
				return hash;
			}
		}
	}
	return -1;
}
