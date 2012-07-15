/*----------------------------------------------------------------------------*\
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
\*----------------------------------------------------------------------------*/

#include "internal\y_version"
#include "y_debug"

// Note: H_a, H_b, H_c, H_d, H_f and H_g are defined here, H_e in y_amx, H_z in
// y_masteronce, H_u in y_users, H_y in y_timers.
// ===================
//  Determine version 
// ===================

// Entry.
#define _H (_:_H_0:_H_1
#define _I (_:_H_2:_H_3
// Old.
#define _H_0:_H_1(%0) HASH@bernstein(%0))
#define _H_2:_H_3(%0) HASHi@bernstein(%0))
// New.
#define _H_1<%0> _:H_Rb(%0)) //HASh@bernstein(%0)
#define _H_3<%0> _:H_Rc(%0))

// Entry.
#define _H@b (_:_H0@b:_H1@b
#define _I@b (_:_H2@b:_H3@b
// Old.
#define _H0@b:_H1@b(%0) HASH@bernstein(%0))
#define _H2@b:_H3@b(%0) HASHi@bernstein(%0))
// New.
#define _H1@b<%0> _:H_Rb(%0))
#define _H3@b<%0> _:H_Rc(%0))

// Entry.
#define _H@f (_:_H0@f:_H1@f
#define _I@f (_:_H2@f:_H3@f
// Old.
#define _H0@f:_H1@f(%0) HASH@fnv1(%0))
#define _H2@f:_H3@f(%0) HASHi@fnv1(%0))
// New.
#define _H1@f<%0> _:H_Rg(%0))
#define _H3@f<%0> _:H_Rf(%0))

// Entry.
#define _H@a (_:_H0@a:_H1@a
#define _I@a (_:_H2@a:_H3@a
// Old.
#define _H0@a:_H1@a(%0) HASH@fnv1a(%0))
#define _H2@a:_H3@a(%0) HASHi@fnv1a(%0))
// New.
#define _H1@a<%0> _:H_Ra(%0))
#define _H3@a<%0> _:H_Rd(%0))

// Entry.
#define HASH  (_:_H_4:_H_5
#define HASHi (_:_H_6:_H_7
// Old.
#define _H_4:_H_5(%0,%1) HASH@%0(%1))
#define _H_6:_H_7(%0,%1) HASHi@%0(%1))
// New.
#define _H_5:%0<%1> HASh@%0(%1))
#define _H_7:%0<%1> HAShi@%0(%1))

#define HASh@bernstein(%0) (_:H_Rb(%0))
#define HAShi@bernstein(%0) (_:H_Rc(%0))
#define HASh@fnv1(%0) (_:H_Rg(%0))
#define HAShi@fnv1(%0) (_:H_Rg(%0))
#define HASh@fnv1a(%0) (_:H_Ra(%0))
#define HAShi@fnv1a(%0) (_:H_Rd(%0))

// =============
//  New version 
// =============

// ================
//  Bernstein hash 
// ================

// ================
//  Case sensitive 
// ================

// Do the next character test as this one failed.
#define H_Sb(%0,%1) H_Nb%1(%0)
// End of string test failed.
#define H_Eb(%0)    @Ba:H_Sb(%0,a)
// Do the single addition.
#define H_Db(%0,%1) (_:H_Rb(%0)*33+%1)
// Recurse through the string.
#define H_Rb(%0)    hb:H_Eb(%0)
// Test for the end of a string.
#define hb:H_Eb()   -1
// Find the length of a string at compile time.
//#define LEN(%0) _:(H_R(%0))

// Test for the current character.
#define @Ba:H_Sb(a%0,%1) H_Db(%0,97)
#define @Bb:H_Sb(b%0,%1) H_Db(%0,98)
#define @Bc:H_Sb(c%0,%1) H_Db(%0,99)
#define @Bd:H_Sb(d%0,%1) H_Db(%0,100)
#define @Be:H_Sb(e%0,%1) H_Db(%0,101)
#define @Bf:H_Sb(f%0,%1) H_Db(%0,102)
#define @Bg:H_Sb(g%0,%1) H_Db(%0,103)
#define @Bh:H_Sb(h%0,%1) H_Db(%0,104)
#define @Bi:H_Sb(i%0,%1) H_Db(%0,105)
#define @Bj:H_Sb(j%0,%1) H_Db(%0,106)
#define @Bk:H_Sb(k%0,%1) H_Db(%0,107)
#define @Bl:H_Sb(l%0,%1) H_Db(%0,108)
#define @Bm:H_Sb(m%0,%1) H_Db(%0,109)
#define @Bn:H_Sb(n%0,%1) H_Db(%0,110)
#define @Bo:H_Sb(o%0,%1) H_Db(%0,111)
#define @Bp:H_Sb(p%0,%1) H_Db(%0,112)
#define @Bq:H_Sb(q%0,%1) H_Db(%0,113)
#define @Br:H_Sb(r%0,%1) H_Db(%0,114)
#define @Bs:H_Sb(s%0,%1) H_Db(%0,115)
#define @Bt:H_Sb(t%0,%1) H_Db(%0,116)
#define @Bu:H_Sb(u%0,%1) H_Db(%0,117)
#define @Bv:H_Sb(v%0,%1) H_Db(%0,118)
#define @Bw:H_Sb(w%0,%1) H_Db(%0,119)
#define @Bx:H_Sb(x%0,%1) H_Db(%0,120)
#define @By:H_Sb(y%0,%1) H_Db(%0,121)
#define @Bz:H_Sb(z%0,%1) H_Db(%0,122)

#define @BA:H_Sb(A%0,%1) H_Db(%0,65)
#define @BB:H_Sb(B%0,%1) H_Db(%0,66)
#define @BC:H_Sb(C%0,%1) H_Db(%0,67)
#define @BD:H_Sb(D%0,%1) H_Db(%0,68)
#define @BE:H_Sb(E%0,%1) H_Db(%0,69)
#define @BF:H_Sb(F%0,%1) H_Db(%0,70)
#define @BG:H_Sb(G%0,%1) H_Db(%0,71)
#define @BH:H_Sb(H%0,%1) H_Db(%0,72)
#define @BI:H_Sb(I%0,%1) H_Db(%0,73)
#define @BJ:H_Sb(J%0,%1) H_Db(%0,74)
#define @BK:H_Sb(K%0,%1) H_Db(%0,75)
#define @BL:H_Sb(L%0,%1) H_Db(%0,76)
#define @BM:H_Sb(M%0,%1) H_Db(%0,77)
#define @BN:H_Sb(N%0,%1) H_Db(%0,78)
#define @BO:H_Sb(O%0,%1) H_Db(%0,79)
#define @BP:H_Sb(P%0,%1) H_Db(%0,80)
#define @BQ:H_Sb(Q%0,%1) H_Db(%0,81)
#define @BR:H_Sb(R%0,%1) H_Db(%0,82)
#define @BS:H_Sb(S%0,%1) H_Db(%0,83)
#define @BT:H_Sb(T%0,%1) H_Db(%0,84)
#define @BU:H_Sb(U%0,%1) H_Db(%0,85)
#define @BV:H_Sb(V%0,%1) H_Db(%0,86)
#define @BW:H_Sb(W%0,%1) H_Db(%0,87)
#define @BX:H_Sb(X%0,%1) H_Db(%0,88)
#define @BY:H_Sb(Y%0,%1) H_Db(%0,89)
#define @BZ:H_Sb(Z%0,%1) H_Db(%0,90)

#define @B0:H_Sb(0%0,%1) H_Db(%0,48)
#define @B1:H_Sb(1%0,%1) H_Db(%0,49)
#define @B2:H_Sb(2%0,%1) H_Db(%0,50)
#define @B3:H_Sb(3%0,%1) H_Db(%0,51)
#define @B4:H_Sb(4%0,%1) H_Db(%0,52)
#define @B5:H_Sb(5%0,%1) H_Db(%0,53)
#define @B6:H_Sb(6%0,%1) H_Db(%0,54)
#define @B7:H_Sb(7%0,%1) H_Db(%0,55)
#define @B8:H_Sb(8%0,%1) H_Db(%0,56)
#define @B9:H_Sb(9%0,%1) H_Db(%0,57)

#define @B_:H_Sb(_%0,%1) H_Db(%0,95)
//#define hb@:H_Sb(@%0,%1) H_Db(%0)

// Find the next character to test.
#define H_Nba(%0) @Bb:H_Sb(%0,b)
#define H_Nbb(%0) @Bc:H_Sb(%0,c)
#define H_Nbc(%0) @Bd:H_Sb(%0,d)
#define H_Nbd(%0) @Be:H_Sb(%0,e)
#define H_Nbe(%0) @Bf:H_Sb(%0,f)
#define H_Nbf(%0) @Bg:H_Sb(%0,g)
#define H_Nbg(%0) @Bh:H_Sb(%0,h)
#define H_Nbh(%0) @Bi:H_Sb(%0,i)
#define H_Nbi(%0) @Bj:H_Sb(%0,j)
#define H_Nbj(%0) @Bk:H_Sb(%0,k)
#define H_Nbk(%0) @Bl:H_Sb(%0,l)
#define H_Nbl(%0) @Bm:H_Sb(%0,m)
#define H_Nbm(%0) @Bn:H_Sb(%0,n)
#define H_Nbn(%0) @Bo:H_Sb(%0,o)
#define H_Nbo(%0) @Bp:H_Sb(%0,p)
#define H_Nbp(%0) @Bq:H_Sb(%0,q)
#define H_Nbq(%0) @Br:H_Sb(%0,r)
#define H_Nbr(%0) @Bs:H_Sb(%0,s)
#define H_Nbs(%0) @Bt:H_Sb(%0,t)
#define H_Nbt(%0) @Bu:H_Sb(%0,u)
#define H_Nbu(%0) @Bv:H_Sb(%0,v)
#define H_Nbv(%0) @Bw:H_Sb(%0,w)
#define H_Nbw(%0) @Bx:H_Sb(%0,x)
#define H_Nbx(%0) @By:H_Sb(%0,y)
#define H_Nby(%0) @Bz:H_Sb(%0,z)
#define H_Nbz(%0) @BA:H_Sb(%0,0)

#define H_NbA(%0) @BB:H_Sb(%0,B)
#define H_NbB(%0) @BC:H_Sb(%0,C)
#define H_NbC(%0) @BD:H_Sb(%0,D)
#define H_NbD(%0) @BE:H_Sb(%0,E)
#define H_NbE(%0) @BF:H_Sb(%0,F)
#define H_NbF(%0) @BG:H_Sb(%0,G)
#define H_NbG(%0) @BH:H_Sb(%0,H)
#define H_NbH(%0) @BI:H_Sb(%0,I)
#define H_NbI(%0) @BJ:H_Sb(%0,J)
#define H_NbJ(%0) @BK:H_Sb(%0,K)
#define H_NbK(%0) @BL:H_Sb(%0,L)
#define H_NbL(%0) @BM:H_Sb(%0,M)
#define H_NbM(%0) @BN:H_Sb(%0,N)
#define H_NbN(%0) @BO:H_Sb(%0,O)
#define H_NbO(%0) @BP:H_Sb(%0,P)
#define H_NbP(%0) @BQ:H_Sb(%0,Q)
#define H_NbQ(%0) @BR:H_Sb(%0,R)
#define H_NbR(%0) @BS:H_Sb(%0,S)
#define H_NbS(%0) @BT:H_Sb(%0,T)
#define H_NbT(%0) @BU:H_Sb(%0,U)
#define H_NbU(%0) @BV:H_Sb(%0,V)
#define H_NbV(%0) @BW:H_Sb(%0,W)
#define H_NbW(%0) @BX:H_Sb(%0,X)
#define H_NbX(%0) @BY:H_Sb(%0,Y)
#define H_NbY(%0) @BZ:H_Sb(%0,Z)
#define H_NbZ(%0) -1

#define H_Nb0(%0) @B1:H_Sb(%0,1)
#define H_Nb1(%0) @B2:H_Sb(%0,2)
#define H_Nb2(%0) @B3:H_Sb(%0,3)
#define H_Nb3(%0) @B4:H_Sb(%0,4)
#define H_Nb4(%0) @B5:H_Sb(%0,5)
#define H_Nb5(%0) @B6:H_Sb(%0,6)
#define H_Nb6(%0) @B7:H_Sb(%0,7)
#define H_Nb7(%0) @B8:H_Sb(%0,8)
#define H_Nb8(%0) @B9:H_Sb(%0,9)
#define H_Nb9(%0) @B_:H_Sb(%0,_)

#define H_Nb_(%0) @B_:H_Sb(%0,A)

// ==================
//  Case insensitive 
// ==================

// Do the next character test as this one failed.
#define H_Sc(%0,%1) H_Nc%1(%0)
// End of string test failed.
#define H_Ec(%0)    @Ca:H_Sc(%0,a)
// Do the single addition.
#define H_Dc(%0,%1) (_:H_Rc(%0)*33+%1)
// Recurse through the string.
#define H_Rc(%0)    hc:H_Ec(%0)
// Test for the end of a string.
#define hc:H_Ec()   -1
// Find the length of a string at compile time.
//#define LEN(%0) _:(I_R(%0))

// Test for the current character.
#define @Ca:H_Sc(a%0,%1) H_Dc(%0,65)
#define @Cb:H_Sc(b%0,%1) H_Dc(%0,66)
#define @Cc:H_Sc(c%0,%1) H_Dc(%0,67)
#define @Cd:H_Sc(d%0,%1) H_Dc(%0,68)
#define @Ce:H_Sc(e%0,%1) H_Dc(%0,69)
#define @Cf:H_Sc(f%0,%1) H_Dc(%0,70)
#define @Cg:H_Sc(g%0,%1) H_Dc(%0,71)
#define @Ch:H_Sc(h%0,%1) H_Dc(%0,72)
#define @Ci:H_Sc(i%0,%1) H_Dc(%0,73)
#define @Cj:H_Sc(j%0,%1) H_Dc(%0,74)
#define @Ck:H_Sc(k%0,%1) H_Dc(%0,75)
#define @Cl:H_Sc(l%0,%1) H_Dc(%0,76)
#define @Cm:H_Sc(m%0,%1) H_Dc(%0,77)
#define @Cn:H_Sc(n%0,%1) H_Dc(%0,78)
#define @Co:H_Sc(o%0,%1) H_Dc(%0,79)
#define @Cp:H_Sc(p%0,%1) H_Dc(%0,80)
#define @Cq:H_Sc(q%0,%1) H_Dc(%0,81)
#define @Cr:H_Sc(r%0,%1) H_Dc(%0,82)
#define @Cs:H_Sc(s%0,%1) H_Dc(%0,83)
#define @Ct:H_Sc(t%0,%1) H_Dc(%0,84)
#define @Cu:H_Sc(u%0,%1) H_Dc(%0,85)
#define @Cv:H_Sc(v%0,%1) H_Dc(%0,86)
#define @Cw:H_Sc(w%0,%1) H_Dc(%0,87)
#define @Cx:H_Sc(x%0,%1) H_Dc(%0,88)
#define @Cy:H_Sc(y%0,%1) H_Dc(%0,89)
#define @Cz:H_Sc(z%0,%1) H_Dc(%0,90)

#define @CA:H_Sc(A%0,%1) H_Dc(%0,65)
#define @CB:H_Sc(B%0,%1) H_Dc(%0,66)
#define @CC:H_Sc(C%0,%1) H_Dc(%0,67)
#define @CD:H_Sc(D%0,%1) H_Dc(%0,68)
#define @CE:H_Sc(E%0,%1) H_Dc(%0,69)
#define @CF:H_Sc(F%0,%1) H_Dc(%0,70)
#define @CG:H_Sc(G%0,%1) H_Dc(%0,71)
#define @CH:H_Sc(H%0,%1) H_Dc(%0,72)
#define @CI:H_Sc(I%0,%1) H_Dc(%0,73)
#define @CJ:H_Sc(J%0,%1) H_Dc(%0,74)
#define @CK:H_Sc(K%0,%1) H_Dc(%0,75)
#define @CL:H_Sc(L%0,%1) H_Dc(%0,76)
#define @CM:H_Sc(M%0,%1) H_Dc(%0,77)
#define @CN:H_Sc(N%0,%1) H_Dc(%0,78)
#define @CO:H_Sc(O%0,%1) H_Dc(%0,79)
#define @CP:H_Sc(P%0,%1) H_Dc(%0,80)
#define @CQ:H_Sc(Q%0,%1) H_Dc(%0,81)
#define @CR:H_Sc(R%0,%1) H_Dc(%0,82)
#define @CS:H_Sc(S%0,%1) H_Dc(%0,83)
#define @CT:H_Sc(T%0,%1) H_Dc(%0,84)
#define @CU:H_Sc(U%0,%1) H_Dc(%0,85)
#define @CV:H_Sc(V%0,%1) H_Dc(%0,86)
#define @CW:H_Sc(W%0,%1) H_Dc(%0,87)
#define @CX:H_Sc(X%0,%1) H_Dc(%0,88)
#define @CY:H_Sc(Y%0,%1) H_Dc(%0,89)
#define @CZ:H_Sc(Z%0,%1) H_Dc(%0,90)

#define @C0:H_Sc(0%0,%1) H_Dc(%0,48)
#define @C1:H_Sc(1%0,%1) H_Dc(%0,49)
#define @C2:H_Sc(2%0,%1) H_Dc(%0,50)
#define @C3:H_Sc(3%0,%1) H_Dc(%0,51)
#define @C4:H_Sc(4%0,%1) H_Dc(%0,52)
#define @C5:H_Sc(5%0,%1) H_Dc(%0,53)
#define @C6:H_Sc(6%0,%1) H_Dc(%0,54)
#define @C7:H_Sc(7%0,%1) H_Dc(%0,55)
#define @C8:H_Sc(8%0,%1) H_Dc(%0,56)
#define @C9:H_Sc(9%0,%1) H_Dc(%0,57)

#define @C_:H_Sc(_%0,%1) H_Dc(%0,95)
//#define hc@:H_Sc(@%0,%1) H_Dc(%0)

// Find the next character to test.
#define H_Nca(%0) @Cb:H_Sc(%0,b)
#define H_Ncb(%0) @Cc:H_Sc(%0,c)
#define H_Ncc(%0) @Cd:H_Sc(%0,d)
#define H_Ncd(%0) @Ce:H_Sc(%0,e)
#define H_Nce(%0) @Cf:H_Sc(%0,f)
#define H_Ncf(%0) @Cg:H_Sc(%0,g)
#define H_Ncg(%0) @Ch:H_Sc(%0,h)
#define H_Nch(%0) @Ci:H_Sc(%0,i)
#define H_Nci(%0) @Cj:H_Sc(%0,j)
#define H_Ncj(%0) @Ck:H_Sc(%0,k)
#define H_Nck(%0) @Cl:H_Sc(%0,l)
#define H_Ncl(%0) @Cm:H_Sc(%0,m)
#define H_Ncm(%0) @Cn:H_Sc(%0,n)
#define H_Ncn(%0) @Co:H_Sc(%0,o)
#define H_Nco(%0) @Cp:H_Sc(%0,p)
#define H_Ncp(%0) @Cq:H_Sc(%0,q)
#define H_Ncq(%0) @Cr:H_Sc(%0,r)
#define H_Ncr(%0) @Cs:H_Sc(%0,s)
#define H_Ncs(%0) @Ct:H_Sc(%0,t)
#define H_Nct(%0) @Cu:H_Sc(%0,u)
#define H_Ncu(%0) @Cv:H_Sc(%0,v)
#define H_Ncv(%0) @Cw:H_Sc(%0,w)
#define H_Ncw(%0) @Cx:H_Sc(%0,x)
#define H_Ncx(%0) @Cy:H_Sc(%0,y)
#define H_Ncy(%0) @Cz:H_Sc(%0,z)
#define H_Ncz(%0) @CA:H_Sc(%0,0)

#define H_NcA(%0) @CB:H_Sc(%0,B)
#define H_NcB(%0) @CC:H_Sc(%0,C)
#define H_NcC(%0) @CD:H_Sc(%0,D)
#define H_NcD(%0) @CE:H_Sc(%0,E)
#define H_NcE(%0) @CF:H_Sc(%0,F)
#define H_NcF(%0) @CG:H_Sc(%0,G)
#define H_NcG(%0) @CH:H_Sc(%0,H)
#define H_NcH(%0) @CI:H_Sc(%0,I)
#define H_NcI(%0) @CJ:H_Sc(%0,J)
#define H_NcJ(%0) @CK:H_Sc(%0,K)
#define H_NcK(%0) @CL:H_Sc(%0,L)
#define H_NcL(%0) @CM:H_Sc(%0,M)
#define H_NcM(%0) @CN:H_Sc(%0,N)
#define H_NcN(%0) @CO:H_Sc(%0,O)
#define H_NcO(%0) @CP:H_Sc(%0,P)
#define H_NcP(%0) @CQ:H_Sc(%0,Q)
#define H_NcQ(%0) @CR:H_Sc(%0,R)
#define H_NcR(%0) @CS:H_Sc(%0,S)
#define H_NcS(%0) @CT:H_Sc(%0,T)
#define H_NcT(%0) @CU:H_Sc(%0,U)
#define H_NcU(%0) @CV:H_Sc(%0,V)
#define H_NcV(%0) @CW:H_Sc(%0,W)
#define H_NcW(%0) @CX:H_Sc(%0,X)
#define H_NcX(%0) @CY:H_Sc(%0,Y)
#define H_NcY(%0) @CZ:H_Sc(%0,Z)
#define H_NcZ(%0) -1

#define H_Nc0(%0) @C1:H_Sc(%0,1)
#define H_Nc1(%0) @C2:H_Sc(%0,2)
#define H_Nc2(%0) @C3:H_Sc(%0,3)
#define H_Nc3(%0) @C4:H_Sc(%0,4)
#define H_Nc4(%0) @C5:H_Sc(%0,5)
#define H_Nc5(%0) @C6:H_Sc(%0,6)
#define H_Nc6(%0) @C7:H_Sc(%0,7)
#define H_Nc7(%0) @C8:H_Sc(%0,8)
#define H_Nc8(%0) @C9:H_Sc(%0,9)
#define H_Nc9(%0) @C_:H_Sc(%0,_)

#define H_Nc_(%0) @C0:H_Sc(%0,A)

// ===========
//  FNV1 hash 
// ===========

// ================
//  Case sensitive 
// ================

// Do the next character test as this one failed.
#define H_Sg(%0,%1) H_Ng%1(%0)
// End of string test failed.
#define H_Eg(%0)    @Ga:H_Sg(%0,a)
// Do the single addition.
#define H_Dg(%0,%1) (_:H_Rg(%0)*16777619^%1)
// Recurse through the string.
#define H_Rg(%0)    hg:H_Eg(%0)
// Test for the end of a string.
#define hg:H_Eg()   2166136261
// Find the length of a string at compile time.
//#define LEN(%0) _:(H_R(%0))

// Test for the current character.
#define @Ga:H_Sg(a%0,%1) H_Dg(%0,97)
#define @Gb:H_Sg(b%0,%1) H_Dg(%0,98)
#define @Gc:H_Sg(c%0,%1) H_Dg(%0,99)
#define @Gd:H_Sg(d%0,%1) H_Dg(%0,100)
#define @Ge:H_Sg(e%0,%1) H_Dg(%0,101)
#define @Gf:H_Sg(f%0,%1) H_Dg(%0,102)
#define @Gg:H_Sg(g%0,%1) H_Dg(%0,103)
#define @Gh:H_Sg(h%0,%1) H_Dg(%0,104)
#define @Gi:H_Sg(i%0,%1) H_Dg(%0,105)
#define @Gj:H_Sg(j%0,%1) H_Dg(%0,106)
#define @Gk:H_Sg(k%0,%1) H_Dg(%0,107)
#define @Gl:H_Sg(l%0,%1) H_Dg(%0,108)
#define @Gm:H_Sg(m%0,%1) H_Dg(%0,109)
#define @Gn:H_Sg(n%0,%1) H_Dg(%0,110)
#define @Go:H_Sg(o%0,%1) H_Dg(%0,111)
#define @Gp:H_Sg(p%0,%1) H_Dg(%0,112)
#define @Gq:H_Sg(q%0,%1) H_Dg(%0,113)
#define @Gr:H_Sg(r%0,%1) H_Dg(%0,114)
#define @Gs:H_Sg(s%0,%1) H_Dg(%0,115)
#define @Gt:H_Sg(t%0,%1) H_Dg(%0,116)
#define @Gu:H_Sg(u%0,%1) H_Dg(%0,117)
#define @Gv:H_Sg(v%0,%1) H_Dg(%0,118)
#define @Gw:H_Sg(w%0,%1) H_Dg(%0,119)
#define @Gx:H_Sg(x%0,%1) H_Dg(%0,120)
#define @Gy:H_Sg(y%0,%1) H_Dg(%0,121)
#define @Gz:H_Sg(z%0,%1) H_Dg(%0,122)

#define @GA:H_Sg(A%0,%1) H_Dg(%0,65)
#define @GB:H_Sg(B%0,%1) H_Dg(%0,66)
#define @GC:H_Sg(C%0,%1) H_Dg(%0,67)
#define @GD:H_Sg(D%0,%1) H_Dg(%0,68)
#define @GE:H_Sg(E%0,%1) H_Dg(%0,69)
#define @GF:H_Sg(F%0,%1) H_Dg(%0,70)
#define @GG:H_Sg(G%0,%1) H_Dg(%0,71)
#define @GH:H_Sg(H%0,%1) H_Dg(%0,72)
#define @GI:H_Sg(I%0,%1) H_Dg(%0,73)
#define @GJ:H_Sg(J%0,%1) H_Dg(%0,74)
#define @GK:H_Sg(K%0,%1) H_Dg(%0,75)
#define @GL:H_Sg(L%0,%1) H_Dg(%0,76)
#define @GM:H_Sg(M%0,%1) H_Dg(%0,77)
#define @GN:H_Sg(N%0,%1) H_Dg(%0,78)
#define @GO:H_Sg(O%0,%1) H_Dg(%0,79)
#define @GP:H_Sg(P%0,%1) H_Dg(%0,80)
#define @GQ:H_Sg(Q%0,%1) H_Dg(%0,81)
#define @GR:H_Sg(R%0,%1) H_Dg(%0,82)
#define @GS:H_Sg(S%0,%1) H_Dg(%0,83)
#define @GT:H_Sg(T%0,%1) H_Dg(%0,84)
#define @GU:H_Sg(U%0,%1) H_Dg(%0,85)
#define @GV:H_Sg(V%0,%1) H_Dg(%0,86)
#define @GW:H_Sg(W%0,%1) H_Dg(%0,87)
#define @GX:H_Sg(X%0,%1) H_Dg(%0,88)
#define @GY:H_Sg(Y%0,%1) H_Dg(%0,89)
#define @GZ:H_Sg(Z%0,%1) H_Dg(%0,90)

#define @G0:H_Sg(0%0,%1) H_Dg(%0,48)
#define @G1:H_Sg(1%0,%1) H_Dg(%0,49)
#define @G2:H_Sg(2%0,%1) H_Dg(%0,50)
#define @G3:H_Sg(3%0,%1) H_Dg(%0,51)
#define @G4:H_Sg(4%0,%1) H_Dg(%0,52)
#define @G5:H_Sg(5%0,%1) H_Dg(%0,53)
#define @G6:H_Sg(6%0,%1) H_Dg(%0,54)
#define @G7:H_Sg(7%0,%1) H_Dg(%0,55)
#define @G8:H_Sg(8%0,%1) H_Dg(%0,56)
#define @G9:H_Sg(9%0,%1) H_Dg(%0,57)

#define @G_:H_Sg(_%0,%1) H_Dg(%0,95)
//#define hg@:H_Sg(@%0,%1) H_Dg(%0)

// Find the next character to test.
#define H_Nga(%0) @Gb:H_Sg(%0,b)
#define H_Ngb(%0) @Gc:H_Sg(%0,c)
#define H_Ngc(%0) @Gd:H_Sg(%0,d)
#define H_Ngd(%0) @Ge:H_Sg(%0,e)
#define H_Nge(%0) @Gf:H_Sg(%0,f)
#define H_Ngf(%0) @Gg:H_Sg(%0,g)
#define H_Ngg(%0) @Gh:H_Sg(%0,h)
#define H_Ngh(%0) @Gi:H_Sg(%0,i)
#define H_Ngi(%0) @Gj:H_Sg(%0,j)
#define H_Ngj(%0) @Gk:H_Sg(%0,k)
#define H_Ngk(%0) @Gl:H_Sg(%0,l)
#define H_Ngl(%0) @Gm:H_Sg(%0,m)
#define H_Ngm(%0) @Gn:H_Sg(%0,n)
#define H_Ngn(%0) @Go:H_Sg(%0,o)
#define H_Ngo(%0) @Gp:H_Sg(%0,p)
#define H_Ngp(%0) @Gq:H_Sg(%0,q)
#define H_Ngq(%0) @Gr:H_Sg(%0,r)
#define H_Ngr(%0) @Gs:H_Sg(%0,s)
#define H_Ngs(%0) @Gt:H_Sg(%0,t)
#define H_Ngt(%0) @Gu:H_Sg(%0,u)
#define H_Ngu(%0) @Gv:H_Sg(%0,v)
#define H_Ngv(%0) @Gw:H_Sg(%0,w)
#define H_Ngw(%0) @Gx:H_Sg(%0,x)
#define H_Ngx(%0) @Gy:H_Sg(%0,y)
#define H_Ngy(%0) @Gz:H_Sg(%0,z)
#define H_Ngz(%0) @GA:H_Sg(%0,0)

#define H_NgA(%0) @GB:H_Sg(%0,B)
#define H_NgB(%0) @GC:H_Sg(%0,C)
#define H_NgC(%0) @GD:H_Sg(%0,D)
#define H_NgD(%0) @GE:H_Sg(%0,E)
#define H_NgE(%0) @GF:H_Sg(%0,F)
#define H_NgF(%0) @GG:H_Sg(%0,G)
#define H_NgG(%0) @GH:H_Sg(%0,H)
#define H_NgH(%0) @GI:H_Sg(%0,I)
#define H_NgI(%0) @GJ:H_Sg(%0,J)
#define H_NgJ(%0) @GK:H_Sg(%0,K)
#define H_NgK(%0) @GL:H_Sg(%0,L)
#define H_NgL(%0) @GM:H_Sg(%0,M)
#define H_NgM(%0) @GN:H_Sg(%0,N)
#define H_NgN(%0) @GO:H_Sg(%0,O)
#define H_NgO(%0) @GP:H_Sg(%0,P)
#define H_NgP(%0) @GQ:H_Sg(%0,Q)
#define H_NgQ(%0) @GR:H_Sg(%0,R)
#define H_NgR(%0) @GS:H_Sg(%0,S)
#define H_NgS(%0) @GT:H_Sg(%0,T)
#define H_NgT(%0) @GU:H_Sg(%0,U)
#define H_NgU(%0) @GV:H_Sg(%0,V)
#define H_NgV(%0) @GW:H_Sg(%0,W)
#define H_NgW(%0) @GX:H_Sg(%0,X)
#define H_NgX(%0) @GY:H_Sg(%0,Y)
#define H_NgY(%0) @GZ:H_Sg(%0,Z)
#define H_NgZ(%0) 2166136261

#define H_Ng0(%0) @G1:H_Sg(%0,1)
#define H_Ng1(%0) @G2:H_Sg(%0,2)
#define H_Ng2(%0) @G3:H_Sg(%0,3)
#define H_Ng3(%0) @G4:H_Sg(%0,4)
#define H_Ng4(%0) @G5:H_Sg(%0,5)
#define H_Ng5(%0) @G6:H_Sg(%0,6)
#define H_Ng6(%0) @G7:H_Sg(%0,7)
#define H_Ng7(%0) @G8:H_Sg(%0,8)
#define H_Ng8(%0) @G9:H_Sg(%0,9)
#define H_Ng9(%0) @G_:H_Sg(%0,_)

#define H_Ng_(%0) @G0:H_Sg(%0,A)

// ==================
//  Case insensitive 
// ==================

// Do the next character test as this one failed.
#define H_Sf(%0,%1) H_Nf%1(%0)
// End of string test failed.
#define H_Ef(%0)    @Fa:H_Sf(%0,a)
// Do the single addition.
#define H_Df(%0,%1) (_:H_Rf(%0)*16777619^%1)
// Recurse through the string.
#define H_Rf(%0)    hf:H_Ef(%0)
// Test for the end of a string.
#define hf:H_Ef()   2166136261
// Find the length of a string at compile time.
//#define LEN(%0) _:(I_R(%0))

// Test for the current character.
#define @Fa:H_Sf(a%0,%1) H_Df(%0,65)
#define @Fb:H_Sf(b%0,%1) H_Df(%0,66)
#define @Fc:H_Sf(c%0,%1) H_Df(%0,67)
#define @Fd:H_Sf(d%0,%1) H_Df(%0,68)
#define @Fe:H_Sf(e%0,%1) H_Df(%0,69)
#define @Ff:H_Sf(f%0,%1) H_Df(%0,70)
#define @Fg:H_Sf(g%0,%1) H_Df(%0,71)
#define @Fh:H_Sf(h%0,%1) H_Df(%0,72)
#define @Fi:H_Sf(i%0,%1) H_Df(%0,73)
#define @Fj:H_Sf(j%0,%1) H_Df(%0,74)
#define @Fk:H_Sf(k%0,%1) H_Df(%0,75)
#define @Fl:H_Sf(l%0,%1) H_Df(%0,76)
#define @Fm:H_Sf(m%0,%1) H_Df(%0,77)
#define @Fn:H_Sf(n%0,%1) H_Df(%0,78)
#define @Fo:H_Sf(o%0,%1) H_Df(%0,79)
#define @Fp:H_Sf(p%0,%1) H_Df(%0,80)
#define @Fq:H_Sf(q%0,%1) H_Df(%0,81)
#define @Fr:H_Sf(r%0,%1) H_Df(%0,82)
#define @Fs:H_Sf(s%0,%1) H_Df(%0,83)
#define @Ft:H_Sf(t%0,%1) H_Df(%0,84)
#define @Fu:H_Sf(u%0,%1) H_Df(%0,85)
#define @Fv:H_Sf(v%0,%1) H_Df(%0,86)
#define @Fw:H_Sf(w%0,%1) H_Df(%0,87)
#define @Fx:H_Sf(x%0,%1) H_Df(%0,88)
#define @Fy:H_Sf(y%0,%1) H_Df(%0,89)
#define @Fz:H_Sf(z%0,%1) H_Df(%0,90)

#define @FA:H_Sf(A%0,%1) H_Df(%0,65)
#define @FB:H_Sf(B%0,%1) H_Df(%0,66)
#define @FC:H_Sf(C%0,%1) H_Df(%0,67)
#define @FD:H_Sf(D%0,%1) H_Df(%0,68)
#define @FE:H_Sf(E%0,%1) H_Df(%0,69)
#define @FF:H_Sf(F%0,%1) H_Df(%0,70)
#define @FG:H_Sf(G%0,%1) H_Df(%0,71)
#define @FH:H_Sf(H%0,%1) H_Df(%0,72)
#define @FI:H_Sf(I%0,%1) H_Df(%0,73)
#define @FJ:H_Sf(J%0,%1) H_Df(%0,74)
#define @FK:H_Sf(K%0,%1) H_Df(%0,75)
#define @FL:H_Sf(L%0,%1) H_Df(%0,76)
#define @FM:H_Sf(M%0,%1) H_Df(%0,77)
#define @FN:H_Sf(N%0,%1) H_Df(%0,78)
#define @FO:H_Sf(O%0,%1) H_Df(%0,79)
#define @FP:H_Sf(P%0,%1) H_Df(%0,80)
#define @FQ:H_Sf(Q%0,%1) H_Df(%0,81)
#define @FR:H_Sf(R%0,%1) H_Df(%0,82)
#define @FS:H_Sf(S%0,%1) H_Df(%0,83)
#define @FT:H_Sf(T%0,%1) H_Df(%0,84)
#define @FU:H_Sf(U%0,%1) H_Df(%0,85)
#define @FV:H_Sf(V%0,%1) H_Df(%0,86)
#define @FW:H_Sf(W%0,%1) H_Df(%0,87)
#define @FX:H_Sf(X%0,%1) H_Df(%0,88)
#define @FY:H_Sf(Y%0,%1) H_Df(%0,89)
#define @FZ:H_Sf(Z%0,%1) H_Df(%0,90)

#define @F0:H_Sf(0%0,%1) H_Df(%0,48)
#define @F1:H_Sf(1%0,%1) H_Df(%0,49)
#define @F2:H_Sf(2%0,%1) H_Df(%0,50)
#define @F3:H_Sf(3%0,%1) H_Df(%0,51)
#define @F4:H_Sf(4%0,%1) H_Df(%0,52)
#define @F5:H_Sf(5%0,%1) H_Df(%0,53)
#define @F6:H_Sf(6%0,%1) H_Df(%0,54)
#define @F7:H_Sf(7%0,%1) H_Df(%0,55)
#define @F8:H_Sf(8%0,%1) H_Df(%0,56)
#define @F9:H_Sf(9%0,%1) H_Df(%0,57)

#define @F_:H_Sf(_%0,%1) H_Df(%0,95)
//#define hf@:H_Sf(@%0,%1) H_Df(%0)

// Find the next character to test.
#define H_Nfa(%0) @Fb:H_Sf(%0,b)
#define H_Nfb(%0) @Fc:H_Sf(%0,c)
#define H_Nfc(%0) @Fd:H_Sf(%0,d)
#define H_Nfd(%0) @Fe:H_Sf(%0,e)
#define H_Nfe(%0) @Ff:H_Sf(%0,f)
#define H_Nff(%0) @Fg:H_Sf(%0,g)
#define H_Nfg(%0) @Fh:H_Sf(%0,h)
#define H_Nfh(%0) @Fi:H_Sf(%0,i)
#define H_Nfi(%0) @Fj:H_Sf(%0,j)
#define H_Nfj(%0) @Fk:H_Sf(%0,k)
#define H_Nfk(%0) @Fl:H_Sf(%0,l)
#define H_Nfl(%0) @Fm:H_Sf(%0,m)
#define H_Nfm(%0) @Fn:H_Sf(%0,n)
#define H_Nfn(%0) @Fo:H_Sf(%0,o)
#define H_Nfo(%0) @Fp:H_Sf(%0,p)
#define H_Nfp(%0) @Fq:H_Sf(%0,q)
#define H_Nfq(%0) @Fr:H_Sf(%0,r)
#define H_Nfr(%0) @Fs:H_Sf(%0,s)
#define H_Nfs(%0) @Ft:H_Sf(%0,t)
#define H_Nft(%0) @Fu:H_Sf(%0,u)
#define H_Nfu(%0) @Fv:H_Sf(%0,v)
#define H_Nfv(%0) @Fw:H_Sf(%0,w)
#define H_Nfw(%0) @Fx:H_Sf(%0,x)
#define H_Nfx(%0) @Fy:H_Sf(%0,y)
#define H_Nfy(%0) @Fz:H_Sf(%0,z)
#define H_Nfz(%0) @FA:H_Sf(%0,0)

#define H_NfA(%0) @FB:H_Sf(%0,B)
#define H_NfB(%0) @FC:H_Sf(%0,C)
#define H_NfC(%0) @FD:H_Sf(%0,D)
#define H_NfD(%0) @FE:H_Sf(%0,E)
#define H_NfE(%0) @FF:H_Sf(%0,F)
#define H_NfF(%0) @FG:H_Sf(%0,G)
#define H_NfG(%0) @FH:H_Sf(%0,H)
#define H_NfH(%0) @FI:H_Sf(%0,I)
#define H_NfI(%0) @FJ:H_Sf(%0,J)
#define H_NfJ(%0) @FK:H_Sf(%0,K)
#define H_NfK(%0) @FL:H_Sf(%0,L)
#define H_NfL(%0) @FM:H_Sf(%0,M)
#define H_NfM(%0) @FN:H_Sf(%0,N)
#define H_NfN(%0) @FO:H_Sf(%0,O)
#define H_NfO(%0) @FP:H_Sf(%0,P)
#define H_NfP(%0) @FQ:H_Sf(%0,Q)
#define H_NfQ(%0) @FR:H_Sf(%0,R)
#define H_NfR(%0) @FS:H_Sf(%0,S)
#define H_NfS(%0) @FT:H_Sf(%0,T)
#define H_NfT(%0) @FU:H_Sf(%0,U)
#define H_NfU(%0) @FV:H_Sf(%0,V)
#define H_NfV(%0) @FW:H_Sf(%0,W)
#define H_NfW(%0) @FX:H_Sf(%0,X)
#define H_NfX(%0) @FY:H_Sf(%0,Y)
#define H_NfY(%0) @FZ:H_Sf(%0,Z)
#define H_NfZ(%0) 2166136261

#define H_Nf0(%0) @F1:H_Sf(%0,1)
#define H_Nf1(%0) @F2:H_Sf(%0,2)
#define H_Nf2(%0) @F3:H_Sf(%0,3)
#define H_Nf3(%0) @F4:H_Sf(%0,4)
#define H_Nf4(%0) @F5:H_Sf(%0,5)
#define H_Nf5(%0) @F6:H_Sf(%0,6)
#define H_Nf6(%0) @F7:H_Sf(%0,7)
#define H_Nf7(%0) @F8:H_Sf(%0,8)
#define H_Nf8(%0) @F9:H_Sf(%0,9)
#define H_Nf9(%0) @F_:H_Sf(%0,_)

#define H_Nf_(%0) @F0:H_Sf(%0,A)

// ============
//  FNV1a hash 
// ============

// ================
//  Case sensitive 
// ================

// Do the next character test as this one failed.
#define H_Sa(%0,%1) H_Na%1(%0)
// End of string test failed.
#define H_Ea(%0)    @Aa:H_Sa(%0,a)
// Do the single addition.
#define H_Da(%0,%1) ((_:H_Ra(%0)^%1)*16777619)
// Recurse through the string.
#define H_Ra(%0)    ha:H_Ea(%0)
// Test for the end of a string.
#define ha:H_Ea()   2166136261
// Find the length of a string at compile time.
//#define LEN(%0) _:(H_R(%0))

// Test for the current character.
#define @Aa:H_Sa(a%0,%1) H_Da(%0,97)
#define @Ab:H_Sa(b%0,%1) H_Da(%0,98)
#define @Ac:H_Sa(c%0,%1) H_Da(%0,99)
#define @Ad:H_Sa(d%0,%1) H_Da(%0,100)
#define @Ae:H_Sa(e%0,%1) H_Da(%0,101)
#define @Af:H_Sa(f%0,%1) H_Da(%0,102)
#define @Ag:H_Sa(g%0,%1) H_Da(%0,103)
#define @Ah:H_Sa(h%0,%1) H_Da(%0,104)
#define @Ai:H_Sa(i%0,%1) H_Da(%0,105)
#define @Aj:H_Sa(j%0,%1) H_Da(%0,106)
#define @Ak:H_Sa(k%0,%1) H_Da(%0,107)
#define @Al:H_Sa(l%0,%1) H_Da(%0,108)
#define @Am:H_Sa(m%0,%1) H_Da(%0,109)
#define @An:H_Sa(n%0,%1) H_Da(%0,110)
#define @Ao:H_Sa(o%0,%1) H_Da(%0,111)
#define @Ap:H_Sa(p%0,%1) H_Da(%0,112)
#define @Aq:H_Sa(q%0,%1) H_Da(%0,113)
#define @Ar:H_Sa(r%0,%1) H_Da(%0,114)
#define @As:H_Sa(s%0,%1) H_Da(%0,115)
#define @At:H_Sa(t%0,%1) H_Da(%0,116)
#define @Au:H_Sa(u%0,%1) H_Da(%0,117)
#define @Av:H_Sa(v%0,%1) H_Da(%0,118)
#define @Aw:H_Sa(w%0,%1) H_Da(%0,119)
#define @Ax:H_Sa(x%0,%1) H_Da(%0,120)
#define @Ay:H_Sa(y%0,%1) H_Da(%0,121)
#define @Az:H_Sa(z%0,%1) H_Da(%0,122)

#define @AA:H_Sa(A%0,%1) H_Da(%0,65)
#define @AB:H_Sa(B%0,%1) H_Da(%0,66)
#define @AC:H_Sa(C%0,%1) H_Da(%0,67)
#define @AD:H_Sa(D%0,%1) H_Da(%0,68)
#define @AE:H_Sa(E%0,%1) H_Da(%0,69)
#define @AF:H_Sa(F%0,%1) H_Da(%0,70)
#define @AG:H_Sa(G%0,%1) H_Da(%0,71)
#define @AH:H_Sa(H%0,%1) H_Da(%0,72)
#define @AI:H_Sa(I%0,%1) H_Da(%0,73)
#define @AJ:H_Sa(J%0,%1) H_Da(%0,74)
#define @AK:H_Sa(K%0,%1) H_Da(%0,75)
#define @AL:H_Sa(L%0,%1) H_Da(%0,76)
#define @AM:H_Sa(M%0,%1) H_Da(%0,77)
#define @AN:H_Sa(N%0,%1) H_Da(%0,78)
#define @AO:H_Sa(O%0,%1) H_Da(%0,79)
#define @AP:H_Sa(P%0,%1) H_Da(%0,80)
#define @AQ:H_Sa(Q%0,%1) H_Da(%0,81)
#define @AR:H_Sa(R%0,%1) H_Da(%0,82)
#define @AS:H_Sa(S%0,%1) H_Da(%0,83)
#define @AT:H_Sa(T%0,%1) H_Da(%0,84)
#define @AU:H_Sa(U%0,%1) H_Da(%0,85)
#define @AV:H_Sa(V%0,%1) H_Da(%0,86)
#define @AW:H_Sa(W%0,%1) H_Da(%0,87)
#define @AX:H_Sa(X%0,%1) H_Da(%0,88)
#define @AY:H_Sa(Y%0,%1) H_Da(%0,89)
#define @AZ:H_Sa(Z%0,%1) H_Da(%0,90)

#define @A0:H_Sa(0%0,%1) H_Da(%0,48)
#define @A1:H_Sa(1%0,%1) H_Da(%0,49)
#define @A2:H_Sa(2%0,%1) H_Da(%0,50)
#define @A3:H_Sa(3%0,%1) H_Da(%0,51)
#define @A4:H_Sa(4%0,%1) H_Da(%0,52)
#define @A5:H_Sa(5%0,%1) H_Da(%0,53)
#define @A6:H_Sa(6%0,%1) H_Da(%0,54)
#define @A7:H_Sa(7%0,%1) H_Da(%0,55)
#define @A8:H_Sa(8%0,%1) H_Da(%0,56)
#define @A9:H_Sa(9%0,%1) H_Da(%0,57)

#define @A_:H_Sa(_%0,%1) H_Da(%0,95)
//#define ha@:H_Sa(@%0,%1) H_Da(%0)

// Find the next character to test.
#define H_Naa(%0) @Ab:H_Sa(%0,b)
#define H_Nab(%0) @Ac:H_Sa(%0,c)
#define H_Nac(%0) @Ad:H_Sa(%0,d)
#define H_Nad(%0) @Ae:H_Sa(%0,e)
#define H_Nae(%0) @Af:H_Sa(%0,f)
#define H_Naf(%0) @Ag:H_Sa(%0,g)
#define H_Nag(%0) @Ah:H_Sa(%0,h)
#define H_Nah(%0) @Ai:H_Sa(%0,i)
#define H_Nai(%0) @Aj:H_Sa(%0,j)
#define H_Naj(%0) @Ak:H_Sa(%0,k)
#define H_Nak(%0) @Al:H_Sa(%0,l)
#define H_Nal(%0) @Am:H_Sa(%0,m)
#define H_Nam(%0) @An:H_Sa(%0,n)
#define H_Nan(%0) @Ao:H_Sa(%0,o)
#define H_Nao(%0) @Ap:H_Sa(%0,p)
#define H_Nap(%0) @Aq:H_Sa(%0,q)
#define H_Naq(%0) @Ar:H_Sa(%0,r)
#define H_Nar(%0) @As:H_Sa(%0,s)
#define H_Nas(%0) @At:H_Sa(%0,t)
#define H_Nat(%0) @Au:H_Sa(%0,u)
#define H_Nau(%0) @Av:H_Sa(%0,v)
#define H_Nav(%0) @Aw:H_Sa(%0,w)
#define H_Naw(%0) @Ax:H_Sa(%0,x)
#define H_Nax(%0) @Ay:H_Sa(%0,y)
#define H_Nay(%0) @Az:H_Sa(%0,z)
#define H_Naz(%0) @AA:H_Sa(%0,0)

#define H_NaA(%0) @AB:H_Sa(%0,B)
#define H_NaB(%0) @AC:H_Sa(%0,C)
#define H_NaC(%0) @AD:H_Sa(%0,D)
#define H_NaD(%0) @AE:H_Sa(%0,E)
#define H_NaE(%0) @AF:H_Sa(%0,F)
#define H_NaF(%0) @AG:H_Sa(%0,G)
#define H_NaG(%0) @AH:H_Sa(%0,H)
#define H_NaH(%0) @AI:H_Sa(%0,I)
#define H_NaI(%0) @AJ:H_Sa(%0,J)
#define H_NaJ(%0) @AK:H_Sa(%0,K)
#define H_NaK(%0) @AL:H_Sa(%0,L)
#define H_NaL(%0) @AM:H_Sa(%0,M)
#define H_NaM(%0) @AN:H_Sa(%0,N)
#define H_NaN(%0) @AO:H_Sa(%0,O)
#define H_NaO(%0) @AP:H_Sa(%0,P)
#define H_NaP(%0) @AQ:H_Sa(%0,Q)
#define H_NaQ(%0) @AR:H_Sa(%0,R)
#define H_NaR(%0) @AS:H_Sa(%0,S)
#define H_NaS(%0) @AT:H_Sa(%0,T)
#define H_NaT(%0) @AU:H_Sa(%0,U)
#define H_NaU(%0) @AV:H_Sa(%0,V)
#define H_NaV(%0) @AW:H_Sa(%0,W)
#define H_NaW(%0) @AX:H_Sa(%0,X)
#define H_NaX(%0) @AY:H_Sa(%0,Y)
#define H_NaY(%0) @AZ:H_Sa(%0,Z)
#define H_NaZ(%0) 2166136261

#define H_Na0(%0) @A1:H_Sa(%0,1)
#define H_Na1(%0) @A2:H_Sa(%0,2)
#define H_Na2(%0) @A3:H_Sa(%0,3)
#define H_Na3(%0) @A4:H_Sa(%0,4)
#define H_Na4(%0) @A5:H_Sa(%0,5)
#define H_Na5(%0) @A6:H_Sa(%0,6)
#define H_Na6(%0) @A7:H_Sa(%0,7)
#define H_Na7(%0) @A8:H_Sa(%0,8)
#define H_Na8(%0) @A9:H_Sa(%0,9)
#define H_Na9(%0) @A_:H_Sa(%0,_)

#define H_Na_(%0) @A0:H_Sa(%0,A)

// ==================
//  Case insensitive 
// ==================

// Do the next character test as this one failed.
#define H_Sd(%0,%1) H_Nd%1(%0)
// End of string test failed.
#define H_Ed(%0)    @Da:H_Sd(%0,a)
// Do the single addition.
#define H_Dd(%0,%1) ((_:H_Rd(%0)^%1)*16777619)
// Recurse through the string.
#define H_Rd(%0)    hd:H_Ed(%0)
// Test for the end of a string.
#define hd:H_Ed()   2166136261
// Find the length of a string at compile time.
//#define LEN(%0) _:(I_R(%0))

// Test for the current character.
#define @Da:H_Sd(a%0,%1) H_Dd(%0,65)
#define @Db:H_Sd(b%0,%1) H_Dd(%0,66)
#define @Dc:H_Sd(c%0,%1) H_Dd(%0,67)
#define @Dd:H_Sd(d%0,%1) H_Dd(%0,68)
#define @De:H_Sd(e%0,%1) H_Dd(%0,69)
#define @Df:H_Sd(f%0,%1) H_Dd(%0,70)
#define @Dg:H_Sd(g%0,%1) H_Dd(%0,71)
#define @Dh:H_Sd(h%0,%1) H_Dd(%0,72)
#define @Di:H_Sd(i%0,%1) H_Dd(%0,73)
#define @Dj:H_Sd(j%0,%1) H_Dd(%0,74)
#define @Dk:H_Sd(k%0,%1) H_Dd(%0,75)
#define @Dl:H_Sd(l%0,%1) H_Dd(%0,76)
#define @Dm:H_Sd(m%0,%1) H_Dd(%0,77)
#define @Dn:H_Sd(n%0,%1) H_Dd(%0,78)
#define @Do:H_Sd(o%0,%1) H_Dd(%0,79)
#define @Dp:H_Sd(p%0,%1) H_Dd(%0,80)
#define @Dq:H_Sd(q%0,%1) H_Dd(%0,81)
#define @Dr:H_Sd(r%0,%1) H_Dd(%0,82)
#define @Ds:H_Sd(s%0,%1) H_Dd(%0,83)
#define @Dt:H_Sd(t%0,%1) H_Dd(%0,84)
#define @Du:H_Sd(u%0,%1) H_Dd(%0,85)
#define @Dv:H_Sd(v%0,%1) H_Dd(%0,86)
#define @Dw:H_Sd(w%0,%1) H_Dd(%0,87)
#define @Dx:H_Sd(x%0,%1) H_Dd(%0,88)
#define @Dy:H_Sd(y%0,%1) H_Dd(%0,89)
#define @Dz:H_Sd(z%0,%1) H_Dd(%0,90)

#define @DA:H_Sd(A%0,%1) H_Dd(%0,65)
#define @DB:H_Sd(B%0,%1) H_Dd(%0,66)
#define @DC:H_Sd(C%0,%1) H_Dd(%0,67)
#define @DD:H_Sd(D%0,%1) H_Dd(%0,68)
#define @DE:H_Sd(E%0,%1) H_Dd(%0,69)
#define @DF:H_Sd(F%0,%1) H_Dd(%0,70)
#define @DG:H_Sd(G%0,%1) H_Dd(%0,71)
#define @DH:H_Sd(H%0,%1) H_Dd(%0,72)
#define @DI:H_Sd(I%0,%1) H_Dd(%0,73)
#define @DJ:H_Sd(J%0,%1) H_Dd(%0,74)
#define @DK:H_Sd(K%0,%1) H_Dd(%0,75)
#define @DL:H_Sd(L%0,%1) H_Dd(%0,76)
#define @DM:H_Sd(M%0,%1) H_Dd(%0,77)
#define @DN:H_Sd(N%0,%1) H_Dd(%0,78)
#define @DO:H_Sd(O%0,%1) H_Dd(%0,79)
#define @DP:H_Sd(P%0,%1) H_Dd(%0,80)
#define @DQ:H_Sd(Q%0,%1) H_Dd(%0,81)
#define @DR:H_Sd(R%0,%1) H_Dd(%0,82)
#define @DS:H_Sd(S%0,%1) H_Dd(%0,83)
#define @DT:H_Sd(T%0,%1) H_Dd(%0,84)
#define @DU:H_Sd(U%0,%1) H_Dd(%0,85)
#define @DV:H_Sd(V%0,%1) H_Dd(%0,86)
#define @DW:H_Sd(W%0,%1) H_Dd(%0,87)
#define @DX:H_Sd(X%0,%1) H_Dd(%0,88)
#define @DY:H_Sd(Y%0,%1) H_Dd(%0,89)
#define @DZ:H_Sd(Z%0,%1) H_Dd(%0,90)

#define @D0:H_Sd(0%0,%1) H_Dd(%0,48)
#define @D1:H_Sd(1%0,%1) H_Dd(%0,49)
#define @D2:H_Sd(2%0,%1) H_Dd(%0,50)
#define @D3:H_Sd(3%0,%1) H_Dd(%0,51)
#define @D4:H_Sd(4%0,%1) H_Dd(%0,52)
#define @D5:H_Sd(5%0,%1) H_Dd(%0,53)
#define @D6:H_Sd(6%0,%1) H_Dd(%0,54)
#define @D7:H_Sd(7%0,%1) H_Dd(%0,55)
#define @D8:H_Sd(8%0,%1) H_Dd(%0,56)
#define @D9:H_Sd(9%0,%1) H_Dd(%0,57)

#define @D_:H_Sd(_%0,%1) H_Dd(%0,95)
//#define hd@:H_Sd(@%0,%1) H_Dd(%0)

// Find the next character to test.
#define H_Nda(%0) @Db:H_Sd(%0,b)
#define H_Ndb(%0) @Dc:H_Sd(%0,c)
#define H_Ndc(%0) @Dd:H_Sd(%0,d)
#define H_Ndd(%0) @De:H_Sd(%0,e)
#define H_Nde(%0) @Df:H_Sd(%0,f)
#define H_Ndf(%0) @Dg:H_Sd(%0,g)
#define H_Ndg(%0) @Dh:H_Sd(%0,h)
#define H_Ndh(%0) @Di:H_Sd(%0,i)
#define H_Ndi(%0) @Dj:H_Sd(%0,j)
#define H_Ndj(%0) @Dk:H_Sd(%0,k)
#define H_Ndk(%0) @Dl:H_Sd(%0,l)
#define H_Ndl(%0) @Dm:H_Sd(%0,m)
#define H_Ndm(%0) @Dn:H_Sd(%0,n)
#define H_Ndn(%0) @Do:H_Sd(%0,o)
#define H_Ndo(%0) @Dp:H_Sd(%0,p)
#define H_Ndp(%0) @Dq:H_Sd(%0,q)
#define H_Ndq(%0) @Dr:H_Sd(%0,r)
#define H_Ndr(%0) @Ds:H_Sd(%0,s)
#define H_Nds(%0) @Dt:H_Sd(%0,t)
#define H_Ndt(%0) @Du:H_Sd(%0,u)
#define H_Ndu(%0) @Dv:H_Sd(%0,v)
#define H_Ndv(%0) @Dw:H_Sd(%0,w)
#define H_Ndw(%0) @Dx:H_Sd(%0,x)
#define H_Ndx(%0) @Dy:H_Sd(%0,y)
#define H_Ndy(%0) @Dz:H_Sd(%0,z)
#define H_Ndz(%0) @DA:H_Sd(%0,0)

#define H_NdA(%0) @DB:H_Sd(%0,B)
#define H_NdB(%0) @DC:H_Sd(%0,C)
#define H_NdC(%0) @DD:H_Sd(%0,D)
#define H_NdD(%0) @DE:H_Sd(%0,E)
#define H_NdE(%0) @DF:H_Sd(%0,F)
#define H_NdF(%0) @DG:H_Sd(%0,G)
#define H_NdG(%0) @DH:H_Sd(%0,H)
#define H_NdH(%0) @DI:H_Sd(%0,I)
#define H_NdI(%0) @DJ:H_Sd(%0,J)
#define H_NdJ(%0) @DK:H_Sd(%0,K)
#define H_NdK(%0) @DL:H_Sd(%0,L)
#define H_NdL(%0) @DM:H_Sd(%0,M)
#define H_NdM(%0) @DN:H_Sd(%0,N)
#define H_NdN(%0) @DO:H_Sd(%0,O)
#define H_NdO(%0) @DP:H_Sd(%0,P)
#define H_NdP(%0) @DQ:H_Sd(%0,Q)
#define H_NdQ(%0) @DR:H_Sd(%0,R)
#define H_NdR(%0) @DS:H_Sd(%0,S)
#define H_NdS(%0) @DT:H_Sd(%0,T)
#define H_NdT(%0) @DU:H_Sd(%0,U)
#define H_NdU(%0) @DV:H_Sd(%0,V)
#define H_NdV(%0) @DW:H_Sd(%0,W)
#define H_NdW(%0) @DX:H_Sd(%0,X)
#define H_NdX(%0) @DY:H_Sd(%0,Y)
#define H_NdY(%0) @DZ:H_Sd(%0,Z)
#define H_NdZ(%0) 2166136261

#define H_Nd0(%0) @D1:H_Sd(%0,1)
#define H_Nd1(%0) @D2:H_Sd(%0,2)
#define H_Nd2(%0) @D3:H_Sd(%0,3)
#define H_Nd3(%0) @D4:H_Sd(%0,4)
#define H_Nd4(%0) @D5:H_Sd(%0,5)
#define H_Nd5(%0) @D6:H_Sd(%0,6)
#define H_Nd6(%0) @D7:H_Sd(%0,7)
#define H_Nd7(%0) @D8:H_Sd(%0,8)
#define H_Nd8(%0) @D9:H_Sd(%0,9)
#define H_Nd9(%0) @D_:H_Sd(%0,_)

#define H_Nd_(%0) @D0:H_Sd(%0,A)

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

/*----------------------------------------------------------------------------*\
Function:
	Hash
Params:
	str - The string to hash.
	sensitive - Wether the hash is case sensitive or not.
Return:
	The reverse Bernstein hash of the string.
Notes:
	Based on Bernstein hash, but backwards to match the macros.  The only
	characters which can be used in the compile time version of this code are:
	a-z, A-Z, 0-9, _ and space.

native Hash(str[]);

\*----------------------------------------------------------------------------*/

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
