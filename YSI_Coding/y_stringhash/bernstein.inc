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

/*

    888b      88                                    ,ad8888ba,                                            88 
    8888b     88                                   d8"'    `"8b                                           88 
    88 `8b    88                                  d8'                                                     88 
    88  `8b   88  ,adPPYba, 8b      db      d8    88            ,adPPYYba, ,adPPYba,  ,adPPYba,   ,adPPYb,88 
    88   `8b  88 a8P_____88 `8b    d88b    d8'    88            ""     `Y8 I8[    "" a8P_____88  a8"    `Y88 
    88    `8b 88 8PP"""""""  `8b  d8'`8b  d8'     Y8,           ,adPPPPP88  `"Y8ba,  8PP"""""""  8b       88 
    88     `8888 "8b,   ,aa   `8bd8'  `8bd8'       Y8a.    .a8P 88,    ,88 aa    ]8I "8b,   ,aa  "8a,   ,d88 
    88      `888  `"Ybbd8"'     YP      YP          `"Y8888Y"'  `"8bbdP"Y8 `"YbbdP"'  `"Ybbd8"'   `"8bbdP"Y8 

*/

// =============================
//  New syntax (case sensitive) 
// =============================

#define hb:%9()

// Scan prior string parts for the next letter, scan subsequent parts for the
// same letter.  The original string can be reconstructed by "%0%5%1".
//  
//  %0 - String before the current letter.
//  %1 - String after the current letter.
//  
//  %5 - The current letter.
//  %6 - The ASCII code for the current letter.
//  
//  %7 - Remainder.
//  %8 - Current sum.
//  

#define H_Db(%0,%5,%1,%6) hb:H_Nb%5(%0)H_Sb:%6]hb:@B%5:H_Nb%5(%1)

// Find the left-most pending sum component (will always be done first thanks to
// pre-processor orderings) and add it on to the current running total.
#define H_Sb:%6]%7|||%8||| %7|||(%8*33+%6)|||

// Finish off the sum.
#define H_Eb:|||%0||| %0

// Test for the current character.
#define @Ba:H_Nba(%1a%0)%7||| H_Db(%1,a,%0,97)%7|||
#define @Bb:H_Nbb(%1b%0)%7||| H_Db(%1,b,%0,98)%7|||
#define @Bc:H_Nbc(%1c%0)%7||| H_Db(%1,c,%0,99)%7|||
#define @Bd:H_Nbd(%1d%0)%7||| H_Db(%1,d,%0,100)%7|||
#define @Be:H_Nbe(%1e%0)%7||| H_Db(%1,e,%0,101)%7|||
#define @Bf:H_Nbf(%1f%0)%7||| H_Db(%1,f,%0,102)%7|||
#define @Bg:H_Nbg(%1g%0)%7||| H_Db(%1,g,%0,103)%7|||
#define @Bh:H_Nbh(%1h%0)%7||| H_Db(%1,h,%0,104)%7|||
#define @Bi:H_Nbi(%1i%0)%7||| H_Db(%1,i,%0,105)%7|||
#define @Bj:H_Nbj(%1j%0)%7||| H_Db(%1,j,%0,106)%7|||
#define @Bk:H_Nbk(%1k%0)%7||| H_Db(%1,k,%0,107)%7|||
#define @Bl:H_Nbl(%1l%0)%7||| H_Db(%1,l,%0,108)%7|||
#define @Bm:H_Nbm(%1m%0)%7||| H_Db(%1,m,%0,109)%7|||
#define @Bn:H_Nbn(%1n%0)%7||| H_Db(%1,n,%0,110)%7|||
#define @Bo:H_Nbo(%1o%0)%7||| H_Db(%1,o,%0,111)%7|||
#define @Bp:H_Nbp(%1p%0)%7||| H_Db(%1,p,%0,112)%7|||
#define @Bq:H_Nbq(%1q%0)%7||| H_Db(%1,q,%0,113)%7|||
#define @Br:H_Nbr(%1r%0)%7||| H_Db(%1,r,%0,114)%7|||
#define @Bs:H_Nbs(%1s%0)%7||| H_Db(%1,s,%0,115)%7|||
#define @Bt:H_Nbt(%1t%0)%7||| H_Db(%1,t,%0,116)%7|||
#define @Bu:H_Nbu(%1u%0)%7||| H_Db(%1,u,%0,117)%7|||
#define @Bv:H_Nbv(%1v%0)%7||| H_Db(%1,v,%0,118)%7|||
#define @Bw:H_Nbw(%1w%0)%7||| H_Db(%1,w,%0,119)%7|||
#define @Bx:H_Nbx(%1x%0)%7||| H_Db(%1,x,%0,120)%7|||
#define @By:H_Nby(%1y%0)%7||| H_Db(%1,y,%0,121)%7|||
#define @Bz:H_Nbz(%1z%0)%7||| H_Db(%1,z,%0,122)%7|||

#define @BA:H_NbA(%1A%0)%7||| H_Db(%1,A,%0,65)%7|||
#define @BB:H_NbB(%1B%0)%7||| H_Db(%1,B,%0,66)%7|||
#define @BC:H_NbC(%1C%0)%7||| H_Db(%1,C,%0,67)%7|||
#define @BD:H_NbD(%1D%0)%7||| H_Db(%1,D,%0,68)%7|||
#define @BE:H_NbE(%1E%0)%7||| H_Db(%1,E,%0,69)%7|||
#define @BF:H_NbF(%1F%0)%7||| H_Db(%1,F,%0,70)%7|||
#define @BG:H_NbG(%1G%0)%7||| H_Db(%1,G,%0,71)%7|||
#define @BH:H_NbH(%1H%0)%7||| H_Db(%1,H,%0,72)%7|||
#define @BI:H_NbI(%1I%0)%7||| H_Db(%1,I,%0,73)%7|||
#define @BJ:H_NbJ(%1J%0)%7||| H_Db(%1,J,%0,74)%7|||
#define @BK:H_NbK(%1K%0)%7||| H_Db(%1,K,%0,75)%7|||
#define @BL:H_NbL(%1L%0)%7||| H_Db(%1,L,%0,76)%7|||
#define @BM:H_NbM(%1M%0)%7||| H_Db(%1,M,%0,77)%7|||
#define @BN:H_NbN(%1N%0)%7||| H_Db(%1,N,%0,78)%7|||
#define @BO:H_NbO(%1O%0)%7||| H_Db(%1,O,%0,79)%7|||
#define @BP:H_NbP(%1P%0)%7||| H_Db(%1,P,%0,80)%7|||
#define @BQ:H_NbQ(%1Q%0)%7||| H_Db(%1,Q,%0,81)%7|||
#define @BR:H_NbR(%1R%0)%7||| H_Db(%1,R,%0,82)%7|||
#define @BS:H_NbS(%1S%0)%7||| H_Db(%1,S,%0,83)%7|||
#define @BT:H_NbT(%1T%0)%7||| H_Db(%1,T,%0,84)%7|||
#define @BU:H_NbU(%1U%0)%7||| H_Db(%1,U,%0,85)%7|||
#define @BV:H_NbV(%1V%0)%7||| H_Db(%1,V,%0,86)%7|||
#define @BW:H_NbW(%1W%0)%7||| H_Db(%1,W,%0,87)%7|||
#define @BX:H_NbX(%1X%0)%7||| H_Db(%1,X,%0,88)%7|||
#define @BY:H_NbY(%1Y%0)%7||| H_Db(%1,Y,%0,89)%7|||
#define @BZ:H_NbZ(%1Z%0)%7||| H_Db(%1,Z,%0,90)%7|||

#define @B0:H_Nb0(%10%0)%7||| H_Db(%1,0,%0,48)%7|||
#define @B1:H_Nb1(%11%0)%7||| H_Db(%1,1,%0,49)%7|||
#define @B2:H_Nb2(%12%0)%7||| H_Db(%1,2,%0,50)%7|||
#define @B3:H_Nb3(%13%0)%7||| H_Db(%1,3,%0,51)%7|||
#define @B4:H_Nb4(%14%0)%7||| H_Db(%1,4,%0,52)%7|||
#define @B5:H_Nb5(%15%0)%7||| H_Db(%1,5,%0,53)%7|||
#define @B6:H_Nb6(%16%0)%7||| H_Db(%1,6,%0,54)%7|||
#define @B7:H_Nb7(%17%0)%7||| H_Db(%1,7,%0,55)%7|||
#define @B8:H_Nb8(%18%0)%7||| H_Db(%1,8,%0,56)%7|||
#define @B9:H_Nb9(%19%0)%7||| H_Db(%1,9,%0,57)%7|||

#define @B_:H_Nb_(_%0)%7||| H_Db(,_,%0,95)%7|||

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

/*

    888b      88                                  88                                                            
    8888b     88                                  88                                                            
    88 `8b    88                                  88                                                            
    88  `8b   88  ,adPPYba, 8b      db      d8    88  ,adPPYb,d8 8b,dPPYba,   ,adPPYba,  8b,dPPYba,  ,adPPYba,  
    88   `8b  88 a8P_____88 `8b    d88b    d8'    88 a8"    `Y88 88P'   `"8a a8"     "8a 88P'   "Y8 a8P_____88  
    88    `8b 88 8PP"""""""  `8b  d8'`8b  d8'     88 8b       88 88       88 8b       d8 88         8PP"""""""  
    88     `8888 "8b,   ,aa   `8bd8'  `8bd8'      88 "8a,   ,d88 88       88 "8a,   ,a8" 88         "8b,   ,aa  
    88      `888  `"Ybbd8"'     YP      YP        88  `"YbbdP"Y8 88       88  `"YbbdP"'  88          `"Ybbd8"'  
                                                      aa,    ,88                                                
                                                       "Y8bbdP"                                                 

*/

// ===============================
//  New syntax (case insensitive) 
// ===============================

#define hc:%9()

// Scan prior string parts for the next letter, scan subsequent parts for the
// same letter.  The original string can be reconstructed by "%0%5%1".
//  
//  %0 - String before the current letter.
//  %1 - String after the current letter.
//  
//  %5 - The current letter.
//  %6 - The ASCII code for the current letter.
//  
//  %7 - Remainder.
//  %8 - Current sum.
//  

#define H_Dc(%0,%5,%1,%6) hc:H_Nc%5(%0)H_Sc:%6]hc:@C%5:H_Nc%5(%1)

#define H_Sc:%6]%7|||%8||| %7|||(%8*33+%6)|||
#define H_Ec:|||%0||| %0

// Test for the current character.
#define @Ca:H_Nca(%0a%1)%7||| H_Dc(%0,a,%1,65)%7|||
#define @Cb:H_Ncb(%0b%1)%7||| H_Dc(%0,b,%1,66)%7|||
#define @Cc:H_Ncc(%0c%1)%7||| H_Dc(%0,c,%1,67)%7|||
#define @Cd:H_Ncd(%0d%1)%7||| H_Dc(%0,d,%1,68)%7|||
#define @Ce:H_Nce(%0e%1)%7||| H_Dc(%0,e,%1,69)%7|||
#define @Cf:H_Ncf(%0f%1)%7||| H_Dc(%0,f,%1,70)%7|||
#define @Cg:H_Ncg(%0g%1)%7||| H_Dc(%0,g,%1,71)%7|||
#define @Ch:H_Nch(%0h%1)%7||| H_Dc(%0,h,%1,72)%7|||
#define @Ci:H_Nci(%0i%1)%7||| H_Dc(%0,i,%1,73)%7|||
#define @Cj:H_Ncj(%0j%1)%7||| H_Dc(%0,j,%1,74)%7|||
#define @Ck:H_Nck(%0k%1)%7||| H_Dc(%0,k,%1,75)%7|||
#define @Cl:H_Ncl(%0l%1)%7||| H_Dc(%0,l,%1,76)%7|||
#define @Cm:H_Ncm(%0m%1)%7||| H_Dc(%0,m,%1,77)%7|||
#define @Cn:H_Ncn(%0n%1)%7||| H_Dc(%0,n,%1,78)%7|||
#define @Co:H_Nco(%0o%1)%7||| H_Dc(%0,o,%1,79)%7|||
#define @Cp:H_Ncp(%0p%1)%7||| H_Dc(%0,p,%1,80)%7|||
#define @Cq:H_Ncq(%0q%1)%7||| H_Dc(%0,q,%1,81)%7|||
#define @Cr:H_Ncr(%0r%1)%7||| H_Dc(%0,r,%1,82)%7|||
#define @Cs:H_Ncs(%0s%1)%7||| H_Dc(%0,s,%1,83)%7|||
#define @Ct:H_Nct(%0t%1)%7||| H_Dc(%0,t,%1,84)%7|||
#define @Cu:H_Ncu(%0u%1)%7||| H_Dc(%0,u,%1,85)%7|||
#define @Cv:H_Ncv(%0v%1)%7||| H_Dc(%0,v,%1,86)%7|||
#define @Cw:H_Ncw(%0w%1)%7||| H_Dc(%0,w,%1,87)%7|||
#define @Cx:H_Ncx(%0x%1)%7||| H_Dc(%0,x,%1,88)%7|||
#define @Cy:H_Ncy(%0y%1)%7||| H_Dc(%0,y,%1,89)%7|||
#define @Cz:H_Ncz(%0z%1)%7||| H_Dc(%0,z,%1,90)%7|||

#define @CA:H_NcA(%0A%1)%7||| H_Dc(%0,A,%1,65)%7|||
#define @CB:H_NcB(%0B%1)%7||| H_Dc(%0,B,%1,66)%7|||
#define @CC:H_NcC(%0C%1)%7||| H_Dc(%0,C,%1,67)%7|||
#define @CD:H_NcD(%0D%1)%7||| H_Dc(%0,D,%1,68)%7|||
#define @CE:H_NcE(%0E%1)%7||| H_Dc(%0,E,%1,69)%7|||
#define @CF:H_NcF(%0F%1)%7||| H_Dc(%0,F,%1,70)%7|||
#define @CG:H_NcG(%0G%1)%7||| H_Dc(%0,G,%1,71)%7|||
#define @CH:H_NcH(%0H%1)%7||| H_Dc(%0,H,%1,72)%7|||
#define @CI:H_NcI(%0I%1)%7||| H_Dc(%0,I,%1,73)%7|||
#define @CJ:H_NcJ(%0J%1)%7||| H_Dc(%0,J,%1,74)%7|||
#define @CK:H_NcK(%0K%1)%7||| H_Dc(%0,K,%1,75)%7|||
#define @CL:H_NcL(%0L%1)%7||| H_Dc(%0,L,%1,76)%7|||
#define @CM:H_NcM(%0M%1)%7||| H_Dc(%0,M,%1,77)%7|||
#define @CN:H_NcN(%0N%1)%7||| H_Dc(%0,N,%1,78)%7|||
#define @CO:H_NcO(%0O%1)%7||| H_Dc(%0,O,%1,79)%7|||
#define @CP:H_NcP(%0P%1)%7||| H_Dc(%0,P,%1,80)%7|||
#define @CQ:H_NcQ(%0Q%1)%7||| H_Dc(%0,Q,%1,81)%7|||
#define @CR:H_NcR(%0R%1)%7||| H_Dc(%0,R,%1,82)%7|||
#define @CS:H_NcS(%0S%1)%7||| H_Dc(%0,S,%1,83)%7|||
#define @CT:H_NcT(%0T%1)%7||| H_Dc(%0,T,%1,84)%7|||
#define @CU:H_NcU(%0U%1)%7||| H_Dc(%0,U,%1,85)%7|||
#define @CV:H_NcV(%0V%1)%7||| H_Dc(%0,V,%1,86)%7|||
#define @CW:H_NcW(%0W%1)%7||| H_Dc(%0,W,%1,87)%7|||
#define @CX:H_NcX(%0X%1)%7||| H_Dc(%0,X,%1,88)%7|||
#define @CY:H_NcY(%0Y%1)%7||| H_Dc(%0,Y,%1,89)%7|||
#define @CZ:H_NcZ(%0Z%1)%7||| H_Dc(%0,Z,%1,90)%7|||

#define @C0:H_Nc0(%00%1)%7||| H_Dc(%0,0,%1,48)%7|||
#define @C1:H_Nc1(%01%1)%7||| H_Dc(%0,1,%1,49)%7|||
#define @C2:H_Nc2(%02%1)%7||| H_Dc(%0,2,%1,50)%7|||
#define @C3:H_Nc3(%03%1)%7||| H_Dc(%0,3,%1,51)%7|||
#define @C4:H_Nc4(%04%1)%7||| H_Dc(%0,4,%1,52)%7|||
#define @C5:H_Nc5(%05%1)%7||| H_Dc(%0,5,%1,53)%7|||
#define @C6:H_Nc6(%06%1)%7||| H_Dc(%0,6,%1,54)%7|||
#define @C7:H_Nc7(%07%1)%7||| H_Dc(%0,7,%1,55)%7|||
#define @C8:H_Nc8(%08%1)%7||| H_Dc(%0,8,%1,56)%7|||
#define @C9:H_Nc9(%09%1)%7||| H_Dc(%0,9,%1,57)%7|||

#define @C_:H_Nc_(%0_%1)%7||| H_Dc(%0,_,%1,95)%7|||

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
#define H_NcZ(%0) H_Ec:H_Rc

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

/*

      ,ad8888ba,   88          88      ,ad8888ba,                                            88 
     d8"'    `"8b  88          88     d8"'    `"8b                                           88 
    d8'        `8b 88          88    d8'                                                     88 
    88          88 88  ,adPPYb,88    88            ,adPPYYba, ,adPPYba,  ,adPPYba,   ,adPPYb,88 
    88          88 88 a8"    `Y88    88            ""     `Y8 I8[    "" a8P_____88  a8"    `Y88 
    Y8,        ,8P 88 8b       88    Y8,           ,adPPPPP88  `"Y8ba,  8PP"""""""  8b       88 
     Y8a.    .a8P  88 "8a,   ,d88     Y8a.    .a8P 88,    ,88 aa    ]8I "8b,   ,aa  "8a,   ,d88 
      `"Y8888Y"'   88  `"8bbdP"Y8      `"Y8888Y"'  `"8bbdP"Y8 `"YbbdP"'  `"Ybbd8"'   `"8bbdP"Y8 

*/

// =============================
//  Old syntax (case sensitive) 
// =============================

// Signify the end with two "@" symbols.
#define HASH@bernstein(%0) _REHASH@b(%0,@,@)

// Internal call.
#define _REHASH@b(%0,%1) _HASH@b_%0(%1,)(-1)

// The bit that actually does the work.
#define _DOHASH@b(%0,%1,%2)(%8) _HASH@b_%1(%2)((%8*33+%0))

// Space.
#define _HASH@b_(%0)(%8) _DOHASH@b(32,%0)(%8)

// Numbers.
#define _HASH@b_0(%0)(%8) _DOHASH@b(48,%0)(%8)
#define _HASH@b_1(%0)(%8) _DOHASH@b(49,%0)(%8)
#define _HASH@b_2(%0)(%8) _DOHASH@b(50,%0)(%8)
#define _HASH@b_3(%0)(%8) _DOHASH@b(51,%0)(%8)
#define _HASH@b_4(%0)(%8) _DOHASH@b(52,%0)(%8)
#define _HASH@b_5(%0)(%8) _DOHASH@b(53,%0)(%8)
#define _HASH@b_6(%0)(%8) _DOHASH@b(54,%0)(%8)
#define _HASH@b_7(%0)(%8) _DOHASH@b(55,%0)(%8)
#define _HASH@b_8(%0)(%8) _DOHASH@b(56,%0)(%8)
#define _HASH@b_9(%0)(%8) _DOHASH@b(57,%0)(%8)

// Upper case letters.
#define _HASH@b_A(%0)(%8) _DOHASH@b(65,%0)(%8)
#define _HASH@b_B(%0)(%8) _DOHASH@b(66,%0)(%8)
#define _HASH@b_C(%0)(%8) _DOHASH@b(67,%0)(%8)
#define _HASH@b_D(%0)(%8) _DOHASH@b(68,%0)(%8)
#define _HASH@b_E(%0)(%8) _DOHASH@b(69,%0)(%8)
#define _HASH@b_F(%0)(%8) _DOHASH@b(70,%0)(%8)
#define _HASH@b_G(%0)(%8) _DOHASH@b(71,%0)(%8)
#define _HASH@b_H(%0)(%8) _DOHASH@b(72,%0)(%8)
#define _HASH@b_I(%0)(%8) _DOHASH@b(73,%0)(%8)
#define _HASH@b_J(%0)(%8) _DOHASH@b(74,%0)(%8)
#define _HASH@b_K(%0)(%8) _DOHASH@b(75,%0)(%8)
#define _HASH@b_L(%0)(%8) _DOHASH@b(76,%0)(%8)
#define _HASH@b_M(%0)(%8) _DOHASH@b(77,%0)(%8)
#define _HASH@b_N(%0)(%8) _DOHASH@b(78,%0)(%8)
#define _HASH@b_O(%0)(%8) _DOHASH@b(79,%0)(%8)
#define _HASH@b_P(%0)(%8) _DOHASH@b(80,%0)(%8)
#define _HASH@b_Q(%0)(%8) _DOHASH@b(81,%0)(%8)
#define _HASH@b_R(%0)(%8) _DOHASH@b(82,%0)(%8)
#define _HASH@b_S(%0)(%8) _DOHASH@b(83,%0)(%8)
#define _HASH@b_T(%0)(%8) _DOHASH@b(84,%0)(%8)
#define _HASH@b_U(%0)(%8) _DOHASH@b(85,%0)(%8)
#define _HASH@b_V(%0)(%8) _DOHASH@b(86,%0)(%8)
#define _HASH@b_W(%0)(%8) _DOHASH@b(87,%0)(%8)
#define _HASH@b_X(%0)(%8) _DOHASH@b(88,%0)(%8)
#define _HASH@b_Y(%0)(%8) _DOHASH@b(89,%0)(%8)
#define _HASH@b_Z(%0)(%8) _DOHASH@b(90,%0)(%8)

// Underscore.
#define _HASH@b__(%0)(%8) _DOHASH@b(95,%0)(%8)

// Lower case letters.
#define _HASH@b_a(%0)(%8) _DOHASH@b(97,%0)(%8)
#define _HASH@b_b(%0)(%8) _DOHASH@b(98,%0)(%8)
#define _HASH@b_c(%0)(%8) _DOHASH@b(99,%0)(%8)
#define _HASH@b_d(%0)(%8) _DOHASH@b(100,%0)(%8)
#define _HASH@b_e(%0)(%8) _DOHASH@b(101,%0)(%8)
#define _HASH@b_f(%0)(%8) _DOHASH@b(102,%0)(%8)
#define _HASH@b_g(%0)(%8) _DOHASH@b(103,%0)(%8)
#define _HASH@b_h(%0)(%8) _DOHASH@b(104,%0)(%8)
#define _HASH@b_i(%0)(%8) _DOHASH@b(105,%0)(%8)
#define _HASH@b_j(%0)(%8) _DOHASH@b(106,%0)(%8)
#define _HASH@b_k(%0)(%8) _DOHASH@b(107,%0)(%8)
#define _HASH@b_l(%0)(%8) _DOHASH@b(108,%0)(%8)
#define _HASH@b_m(%0)(%8) _DOHASH@b(109,%0)(%8)
#define _HASH@b_n(%0)(%8) _DOHASH@b(110,%0)(%8)
#define _HASH@b_o(%0)(%8) _DOHASH@b(111,%0)(%8)
#define _HASH@b_p(%0)(%8) _DOHASH@b(112,%0)(%8)
#define _HASH@b_q(%0)(%8) _DOHASH@b(113,%0)(%8)
#define _HASH@b_r(%0)(%8) _DOHASH@b(114,%0)(%8)
#define _HASH@b_s(%0)(%8) _DOHASH@b(115,%0)(%8)
#define _HASH@b_t(%0)(%8) _DOHASH@b(116,%0)(%8)
#define _HASH@b_u(%0)(%8) _DOHASH@b(117,%0)(%8)
#define _HASH@b_v(%0)(%8) _DOHASH@b(118,%0)(%8)
#define _HASH@b_w(%0)(%8) _DOHASH@b(119,%0)(%8)
#define _HASH@b_x(%0)(%8) _DOHASH@b(120,%0)(%8)
#define _HASH@b_y(%0)(%8) _DOHASH@b(121,%0)(%8)
#define _HASH@b_z(%0)(%8) _DOHASH@b(122,%0)(%8)

// String end.
#define _HASH@b_@(%0)(%8) %8

/*

      ,ad8888ba,   88          88    88                                                            
     d8"'    `"8b  88          88    88                                                            
    d8'        `8b 88          88    88                                                            
    88          88 88  ,adPPYb,88    88  ,adPPYb,d8 8b,dPPYba,   ,adPPYba,  8b,dPPYba,  ,adPPYba,  
    88          88 88 a8"    `Y88    88 a8"    `Y88 88P'   `"8a a8"     "8a 88P'   "Y8 a8P_____88  
    Y8,        ,8P 88 8b       88    88 8b       88 88       88 8b       d8 88         8PP"""""""  
     Y8a.    .a8P  88 "8a,   ,d88    88 "8a,   ,d88 88       88 "8a,   ,a8" 88         "8b,   ,aa  
      `"Y8888Y"'   88  `"8bbdP"Y8    88  `"YbbdP"Y8 88       88  `"YbbdP"'  88          `"Ybbd8"'  
                                         aa,    ,88                                                
                                          "Y8bbdP"                                                 

*/

// ===============================
//  Old syntax (case insensitive) 
// ===============================

// Signify the end with two "@" symbols.
#define HASHi@bernstein(%0) _REHASH@ib(%0,@,@)

// Internal call.
#define _REHASH@ib(%0,%1) _HASH@ib_%0(%1,)(-1)

// The bit that actually does the work.
#define _DOHASH@ib(%0,%1,%2)(%8) _HASH@ib_%1(%2)((%8*33+%0))

// Space.
#define _HASH@ib_(%0)(%8) _DOHASH@ib(32,%0)(%8)

// Numbers.
#define _HASH@ib_0(%0)(%8) _DOHASH@ib(48,%0)(%8)
#define _HASH@ib_1(%0)(%8) _DOHASH@ib(49,%0)(%8)
#define _HASH@ib_2(%0)(%8) _DOHASH@ib(50,%0)(%8)
#define _HASH@ib_3(%0)(%8) _DOHASH@ib(51,%0)(%8)
#define _HASH@ib_4(%0)(%8) _DOHASH@ib(52,%0)(%8)
#define _HASH@ib_5(%0)(%8) _DOHASH@ib(53,%0)(%8)
#define _HASH@ib_6(%0)(%8) _DOHASH@ib(54,%0)(%8)
#define _HASH@ib_7(%0)(%8) _DOHASH@ib(55,%0)(%8)
#define _HASH@ib_8(%0)(%8) _DOHASH@ib(56,%0)(%8)
#define _HASH@ib_9(%0)(%8) _DOHASH@ib(57,%0)(%8)

// Upper case letters.
#define _HASH@ib_A(%0)(%8) _DOHASH@ib(65,%0)(%8)
#define _HASH@ib_B(%0)(%8) _DOHASH@ib(66,%0)(%8)
#define _HASH@ib_C(%0)(%8) _DOHASH@ib(67,%0)(%8)
#define _HASH@ib_D(%0)(%8) _DOHASH@ib(68,%0)(%8)
#define _HASH@ib_E(%0)(%8) _DOHASH@ib(69,%0)(%8)
#define _HASH@ib_F(%0)(%8) _DOHASH@ib(70,%0)(%8)
#define _HASH@ib_G(%0)(%8) _DOHASH@ib(71,%0)(%8)
#define _HASH@ib_H(%0)(%8) _DOHASH@ib(72,%0)(%8)
#define _HASH@ib_I(%0)(%8) _DOHASH@ib(73,%0)(%8)
#define _HASH@ib_J(%0)(%8) _DOHASH@ib(74,%0)(%8)
#define _HASH@ib_K(%0)(%8) _DOHASH@ib(75,%0)(%8)
#define _HASH@ib_L(%0)(%8) _DOHASH@ib(76,%0)(%8)
#define _HASH@ib_M(%0)(%8) _DOHASH@ib(77,%0)(%8)
#define _HASH@ib_N(%0)(%8) _DOHASH@ib(78,%0)(%8)
#define _HASH@ib_O(%0)(%8) _DOHASH@ib(79,%0)(%8)
#define _HASH@ib_P(%0)(%8) _DOHASH@ib(80,%0)(%8)
#define _HASH@ib_Q(%0)(%8) _DOHASH@ib(81,%0)(%8)
#define _HASH@ib_R(%0)(%8) _DOHASH@ib(82,%0)(%8)
#define _HASH@ib_S(%0)(%8) _DOHASH@ib(83,%0)(%8)
#define _HASH@ib_T(%0)(%8) _DOHASH@ib(84,%0)(%8)
#define _HASH@ib_U(%0)(%8) _DOHASH@ib(85,%0)(%8)
#define _HASH@ib_V(%0)(%8) _DOHASH@ib(86,%0)(%8)
#define _HASH@ib_W(%0)(%8) _DOHASH@ib(87,%0)(%8)
#define _HASH@ib_X(%0)(%8) _DOHASH@ib(88,%0)(%8)
#define _HASH@ib_Y(%0)(%8) _DOHASH@ib(89,%0)(%8)
#define _HASH@ib_Z(%0)(%8) _DOHASH@ib(90,%0)(%8)

// Underscore.
#define _HASH@ib__(%0)(%8) _DOHASH@ib(95,%0)(%8)

// Lower case letters.
#define _HASH@ib_a(%0)(%8) _DOHASH@ib(65,%0)(%8)
#define _HASH@ib_b(%0)(%8) _DOHASH@ib(66,%0)(%8)
#define _HASH@ib_c(%0)(%8) _DOHASH@ib(67,%0)(%8)
#define _HASH@ib_d(%0)(%8) _DOHASH@ib(68,%0)(%8)
#define _HASH@ib_e(%0)(%8) _DOHASH@ib(69,%0)(%8)
#define _HASH@ib_f(%0)(%8) _DOHASH@ib(70,%0)(%8)
#define _HASH@ib_g(%0)(%8) _DOHASH@ib(71,%0)(%8)
#define _HASH@ib_h(%0)(%8) _DOHASH@ib(72,%0)(%8)
#define _HASH@ib_i(%0)(%8) _DOHASH@ib(73,%0)(%8)
#define _HASH@ib_j(%0)(%8) _DOHASH@ib(74,%0)(%8)
#define _HASH@ib_k(%0)(%8) _DOHASH@ib(75,%0)(%8)
#define _HASH@ib_l(%0)(%8) _DOHASH@ib(76,%0)(%8)
#define _HASH@ib_m(%0)(%8) _DOHASH@ib(77,%0)(%8)
#define _HASH@ib_n(%0)(%8) _DOHASH@ib(78,%0)(%8)
#define _HASH@ib_o(%0)(%8) _DOHASH@ib(79,%0)(%8)
#define _HASH@ib_p(%0)(%8) _DOHASH@ib(80,%0)(%8)
#define _HASH@ib_q(%0)(%8) _DOHASH@ib(81,%0)(%8)
#define _HASH@ib_r(%0)(%8) _DOHASH@ib(82,%0)(%8)
#define _HASH@ib_s(%0)(%8) _DOHASH@ib(83,%0)(%8)
#define _HASH@ib_t(%0)(%8) _DOHASH@ib(84,%0)(%8)
#define _HASH@ib_u(%0)(%8) _DOHASH@ib(85,%0)(%8)
#define _HASH@ib_v(%0)(%8) _DOHASH@ib(86,%0)(%8)
#define _HASH@ib_w(%0)(%8) _DOHASH@ib(87,%0)(%8)
#define _HASH@ib_x(%0)(%8) _DOHASH@ib(88,%0)(%8)
#define _HASH@ib_y(%0)(%8) _DOHASH@ib(89,%0)(%8)
#define _HASH@ib_z(%0)(%8) _DOHASH@ib(90,%0)(%8)

// String end.
#define _HASH@ib_@(%0)(%8) %8
