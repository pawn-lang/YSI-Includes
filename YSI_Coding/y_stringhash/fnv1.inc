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

#define hg:%9()
#define H_Dg(%0,%5,%1,%6) hg:H_Ng%5(%0)H_Sg:%6]hg:@G%5:H_Ng%5(%1)
#define H_Sg:%6]%7|||%8||| %7|||(%8*16777619^%6)|||
#define H_Eg:|||%0||| %0

// Test for the current character.
#define @Ga:H_Nga(%1a%0)%7||| H_Dg(%1,a,%0,97)%7|||
#define @Gb:H_Ngb(%1b%0)%7||| H_Dg(%1,b,%0,98)%7|||
#define @Gc:H_Ngc(%1c%0)%7||| H_Dg(%1,c,%0,99)%7|||
#define @Gd:H_Ngd(%1d%0)%7||| H_Dg(%1,d,%0,100)%7|||
#define @Ge:H_Nge(%1e%0)%7||| H_Dg(%1,e,%0,101)%7|||
#define @Gf:H_Ngf(%1f%0)%7||| H_Dg(%1,f,%0,102)%7|||
#define @Gg:H_Ngg(%1g%0)%7||| H_Dg(%1,g,%0,103)%7|||
#define @Gh:H_Ngh(%1h%0)%7||| H_Dg(%1,h,%0,104)%7|||
#define @Gi:H_Ngi(%1i%0)%7||| H_Dg(%1,i,%0,105)%7|||
#define @Gj:H_Ngj(%1j%0)%7||| H_Dg(%1,j,%0,106)%7|||
#define @Gk:H_Ngk(%1k%0)%7||| H_Dg(%1,k,%0,107)%7|||
#define @Gl:H_Ngl(%1l%0)%7||| H_Dg(%1,l,%0,108)%7|||
#define @Gm:H_Ngm(%1m%0)%7||| H_Dg(%1,m,%0,109)%7|||
#define @Gn:H_Ngn(%1n%0)%7||| H_Dg(%1,n,%0,110)%7|||
#define @Go:H_Ngo(%1o%0)%7||| H_Dg(%1,o,%0,111)%7|||
#define @Gp:H_Ngp(%1p%0)%7||| H_Dg(%1,p,%0,112)%7|||
#define @Gq:H_Ngq(%1q%0)%7||| H_Dg(%1,q,%0,113)%7|||
#define @Gr:H_Ngr(%1r%0)%7||| H_Dg(%1,r,%0,114)%7|||
#define @Gs:H_Ngs(%1s%0)%7||| H_Dg(%1,s,%0,115)%7|||
#define @Gt:H_Ngt(%1t%0)%7||| H_Dg(%1,t,%0,116)%7|||
#define @Gu:H_Ngu(%1u%0)%7||| H_Dg(%1,u,%0,117)%7|||
#define @Gv:H_Ngv(%1v%0)%7||| H_Dg(%1,v,%0,118)%7|||
#define @Gw:H_Ngw(%1w%0)%7||| H_Dg(%1,w,%0,119)%7|||
#define @Gx:H_Ngx(%1x%0)%7||| H_Dg(%1,x,%0,120)%7|||
#define @Gy:H_Ngy(%1y%0)%7||| H_Dg(%1,y,%0,121)%7|||
#define @Gz:H_Ngz(%1z%0)%7||| H_Dg(%1,z,%0,122)%7|||

#define @GA:H_NgA(%1A%0)%7||| H_Dg(%1,A,%0,65)%7|||
#define @GB:H_NgB(%1B%0)%7||| H_Dg(%1,B,%0,66)%7|||
#define @GC:H_NgC(%1C%0)%7||| H_Dg(%1,C,%0,67)%7|||
#define @GD:H_NgD(%1D%0)%7||| H_Dg(%1,D,%0,68)%7|||
#define @GE:H_NgE(%1E%0)%7||| H_Dg(%1,E,%0,69)%7|||
#define @GF:H_NgF(%1F%0)%7||| H_Dg(%1,F,%0,70)%7|||
#define @GG:H_NgG(%1G%0)%7||| H_Dg(%1,G,%0,71)%7|||
#define @GH:H_NgH(%1H%0)%7||| H_Dg(%1,H,%0,72)%7|||
#define @GI:H_NgI(%1I%0)%7||| H_Dg(%1,I,%0,73)%7|||
#define @GJ:H_NgJ(%1J%0)%7||| H_Dg(%1,J,%0,74)%7|||
#define @GK:H_NgK(%1K%0)%7||| H_Dg(%1,K,%0,75)%7|||
#define @GL:H_NgL(%1L%0)%7||| H_Dg(%1,L,%0,76)%7|||
#define @GM:H_NgM(%1M%0)%7||| H_Dg(%1,M,%0,77)%7|||
#define @GN:H_NgN(%1N%0)%7||| H_Dg(%1,N,%0,78)%7|||
#define @GO:H_NgO(%1O%0)%7||| H_Dg(%1,O,%0,79)%7|||
#define @GP:H_NgP(%1P%0)%7||| H_Dg(%1,P,%0,80)%7|||
#define @GQ:H_NgQ(%1Q%0)%7||| H_Dg(%1,Q,%0,81)%7|||
#define @GR:H_NgR(%1R%0)%7||| H_Dg(%1,R,%0,82)%7|||
#define @GS:H_NgS(%1S%0)%7||| H_Dg(%1,S,%0,83)%7|||
#define @GT:H_NgT(%1T%0)%7||| H_Dg(%1,T,%0,84)%7|||
#define @GU:H_NgU(%1U%0)%7||| H_Dg(%1,U,%0,85)%7|||
#define @GV:H_NgV(%1V%0)%7||| H_Dg(%1,V,%0,86)%7|||
#define @GW:H_NgW(%1W%0)%7||| H_Dg(%1,W,%0,87)%7|||
#define @GX:H_NgX(%1X%0)%7||| H_Dg(%1,X,%0,88)%7|||
#define @GY:H_NgY(%1Y%0)%7||| H_Dg(%1,Y,%0,89)%7|||
#define @GZ:H_NgZ(%1Z%0)%7||| H_Dg(%1,Z,%0,90)%7|||

#define @G0:H_Ng0(%10%0)%7||| H_Dg(%1,0,%0,48)%7|||
#define @G1:H_Ng1(%11%0)%7||| H_Dg(%1,1,%0,49)%7|||
#define @G2:H_Ng2(%12%0)%7||| H_Dg(%1,2,%0,50)%7|||
#define @G3:H_Ng3(%13%0)%7||| H_Dg(%1,3,%0,51)%7|||
#define @G4:H_Ng4(%14%0)%7||| H_Dg(%1,4,%0,52)%7|||
#define @G5:H_Ng5(%15%0)%7||| H_Dg(%1,5,%0,53)%7|||
#define @G6:H_Ng6(%16%0)%7||| H_Dg(%1,6,%0,54)%7|||
#define @G7:H_Ng7(%17%0)%7||| H_Dg(%1,7,%0,55)%7|||
#define @G8:H_Ng8(%18%0)%7||| H_Dg(%1,8,%0,56)%7|||
#define @G9:H_Ng9(%19%0)%7||| H_Dg(%1,9,%0,57)%7|||

#define @G_:H_Ng_(%1,_%0)%7||| H_Dg(%1,_,%0,95)%7|||
//#define hg@:H_Sg(@%0,%1)%7||| H_Dg(%0)%7|||

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

#define hf:%9()
#define H_Df(%0,%5,%1,%6) hf:H_Nf%5(%0)H_Sf:%6]hf:@F%5:H_Nf%5(%1)
#define H_Sf:%6]%7|||%8||| %7|||(%8*16777619^%6)|||
#define H_Ef:|||%0||| %0

// Test for the current character.
#define @Fa:H_Nfa(%1a%0)%7||| H_Df(%1,a,%0,65)%7|||
#define @Fb:H_Nfb(%1b%0)%7||| H_Df(%1,b,%0,66)%7|||
#define @Fc:H_Nfc(%1c%0)%7||| H_Df(%1,c,%0,67)%7|||
#define @Fd:H_Nfd(%1d%0)%7||| H_Df(%1,d,%0,68)%7|||
#define @Fe:H_Nfe(%1e%0)%7||| H_Df(%1,e,%0,69)%7|||
#define @Ff:H_Nff(%1f%0)%7||| H_Df(%1,f,%0,70)%7|||
#define @Fg:H_Nfg(%1g%0)%7||| H_Df(%1,g,%0,71)%7|||
#define @Fh:H_Nfh(%1h%0)%7||| H_Df(%1,h,%0,72)%7|||
#define @Fi:H_Nfi(%1i%0)%7||| H_Df(%1,i,%0,73)%7|||
#define @Fj:H_Nfj(%1j%0)%7||| H_Df(%1,j,%0,74)%7|||
#define @Fk:H_Nfk(%1k%0)%7||| H_Df(%1,k,%0,75)%7|||
#define @Fl:H_Nfl(%1l%0)%7||| H_Df(%1,l,%0,76)%7|||
#define @Fm:H_Nfm(%1m%0)%7||| H_Df(%1,m,%0,77)%7|||
#define @Fn:H_Nfn(%1n%0)%7||| H_Df(%1,n,%0,78)%7|||
#define @Fo:H_Nfo(%1o%0)%7||| H_Df(%1,o,%0,79)%7|||
#define @Fp:H_Nfp(%1p%0)%7||| H_Df(%1,p,%0,80)%7|||
#define @Fq:H_Nfq(%1q%0)%7||| H_Df(%1,q,%0,81)%7|||
#define @Fr:H_Nfr(%1r%0)%7||| H_Df(%1,r,%0,82)%7|||
#define @Fs:H_Nfs(%1s%0)%7||| H_Df(%1,s,%0,83)%7|||
#define @Ft:H_Nft(%1t%0)%7||| H_Df(%1,t,%0,84)%7|||
#define @Fu:H_Nfu(%1u%0)%7||| H_Df(%1,u,%0,85)%7|||
#define @Fv:H_Nfv(%1v%0)%7||| H_Df(%1,v,%0,86)%7|||
#define @Fw:H_Nfw(%1w%0)%7||| H_Df(%1,w,%0,87)%7|||
#define @Fx:H_Nfx(%1x%0)%7||| H_Df(%1,x,%0,88)%7|||
#define @Fy:H_Nfy(%1y%0)%7||| H_Df(%1,y,%0,89)%7|||
#define @Fz:H_Nfz(%1z%0)%7||| H_Df(%1,z,%0,90)%7|||

#define @FA:H_NfA(%1A%0)%7||| H_Df(%1,A,%0,65)%7|||
#define @FB:H_NfB(%1B%0)%7||| H_Df(%1,B,%0,66)%7|||
#define @FC:H_NfC(%1C%0)%7||| H_Df(%1,C,%0,67)%7|||
#define @FD:H_NfD(%1D%0)%7||| H_Df(%1,D,%0,68)%7|||
#define @FE:H_NfE(%1E%0)%7||| H_Df(%1,E,%0,69)%7|||
#define @FF:H_NfF(%1F%0)%7||| H_Df(%1,F,%0,70)%7|||
#define @FG:H_NfG(%1G%0)%7||| H_Df(%1,G,%0,71)%7|||
#define @FH:H_NfH(%1H%0)%7||| H_Df(%1,H,%0,72)%7|||
#define @FI:H_NfI(%1I%0)%7||| H_Df(%1,I,%0,73)%7|||
#define @FJ:H_NfJ(%1J%0)%7||| H_Df(%1,J,%0,74)%7|||
#define @FK:H_NfK(%1K%0)%7||| H_Df(%1,K,%0,75)%7|||
#define @FL:H_NfL(%1L%0)%7||| H_Df(%1,L,%0,76)%7|||
#define @FM:H_NfM(%1M%0)%7||| H_Df(%1,M,%0,77)%7|||
#define @FN:H_NfN(%1N%0)%7||| H_Df(%1,N,%0,78)%7|||
#define @FO:H_NfO(%1O%0)%7||| H_Df(%1,O,%0,79)%7|||
#define @FP:H_NfP(%1P%0)%7||| H_Df(%1,P,%0,80)%7|||
#define @FQ:H_NfQ(%1Q%0)%7||| H_Df(%1,Q,%0,81)%7|||
#define @FR:H_NfR(%1R%0)%7||| H_Df(%1,R,%0,82)%7|||
#define @FS:H_NfS(%1S%0)%7||| H_Df(%1,S,%0,83)%7|||
#define @FT:H_NfT(%1T%0)%7||| H_Df(%1,T,%0,84)%7|||
#define @FU:H_NfU(%1U%0)%7||| H_Df(%1,U,%0,85)%7|||
#define @FV:H_NfV(%1V%0)%7||| H_Df(%1,V,%0,86)%7|||
#define @FW:H_NfW(%1W%0)%7||| H_Df(%1,W,%0,87)%7|||
#define @FX:H_NfX(%1X%0)%7||| H_Df(%1,X,%0,88)%7|||
#define @FY:H_NfY(%1Y%0)%7||| H_Df(%1,Y,%0,89)%7|||
#define @FZ:H_NfZ(%1Z%0)%7||| H_Df(%1,Z,%0,90)%7|||

#define @F0:H_Nf0(%10%0)%7||| H_Df(%1,0,%0,48)%7|||
#define @F1:H_Nf1(%11%0)%7||| H_Df(%1,1,%0,49)%7|||
#define @F2:H_Nf2(%12%0)%7||| H_Df(%1,2,%0,50)%7|||
#define @F3:H_Nf3(%13%0)%7||| H_Df(%1,3,%0,51)%7|||
#define @F4:H_Nf4(%14%0)%7||| H_Df(%1,4,%0,52)%7|||
#define @F5:H_Nf5(%15%0)%7||| H_Df(%1,5,%0,53)%7|||
#define @F6:H_Nf6(%16%0)%7||| H_Df(%1,6,%0,54)%7|||
#define @F7:H_Nf7(%17%0)%7||| H_Df(%1,7,%0,55)%7|||
#define @F8:H_Nf8(%18%0)%7||| H_Df(%1,8,%0,56)%7|||
#define @F9:H_Nf9(%19%0)%7||| H_Df(%1,9,%0,57)%7|||

#define @F_:H_Nf_(%1_%0)%7||| H_Df(%1,_,%0,95)%7|||
//#define hf@:H_Sf(@%0,%1)%7||| H_Df(%0)%7|||

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
#define HASH@fnv1(%0) _REHASH@f(%0,@,@)

// Internal call.
#define _REHASH@f(%0,%1) _HASH@f_%0(%1,)(2166136261)

// The bit that actually does the work.
#define _DOHASH@f(%0,%1,%2)(%8) _HASH@f_%1(%2)((%8*16777619^%0))

// Space.
#define _HASH@f_(%0)(%8) _DOHASH@f(32,%0)(%8)

// Numbers.
#define _HASH@f_0(%0)(%8) _DOHASH@f(48,%0)(%8)
#define _HASH@f_1(%0)(%8) _DOHASH@f(49,%0)(%8)
#define _HASH@f_2(%0)(%8) _DOHASH@f(50,%0)(%8)
#define _HASH@f_3(%0)(%8) _DOHASH@f(51,%0)(%8)
#define _HASH@f_4(%0)(%8) _DOHASH@f(52,%0)(%8)
#define _HASH@f_5(%0)(%8) _DOHASH@f(53,%0)(%8)
#define _HASH@f_6(%0)(%8) _DOHASH@f(54,%0)(%8)
#define _HASH@f_7(%0)(%8) _DOHASH@f(55,%0)(%8)
#define _HASH@f_8(%0)(%8) _DOHASH@f(56,%0)(%8)
#define _HASH@f_9(%0)(%8) _DOHASH@f(57,%0)(%8)

// Upper case letters.
#define _HASH@f_A(%0)(%8) _DOHASH@f(65,%0)(%8)
#define _HASH@f_B(%0)(%8) _DOHASH@f(66,%0)(%8)
#define _HASH@f_C(%0)(%8) _DOHASH@f(67,%0)(%8)
#define _HASH@f_D(%0)(%8) _DOHASH@f(68,%0)(%8)
#define _HASH@f_E(%0)(%8) _DOHASH@f(69,%0)(%8)
#define _HASH@f_F(%0)(%8) _DOHASH@f(70,%0)(%8)
#define _HASH@f_G(%0)(%8) _DOHASH@f(71,%0)(%8)
#define _HASH@f_H(%0)(%8) _DOHASH@f(72,%0)(%8)
#define _HASH@f_I(%0)(%8) _DOHASH@f(73,%0)(%8)
#define _HASH@f_J(%0)(%8) _DOHASH@f(74,%0)(%8)
#define _HASH@f_K(%0)(%8) _DOHASH@f(75,%0)(%8)
#define _HASH@f_L(%0)(%8) _DOHASH@f(76,%0)(%8)
#define _HASH@f_M(%0)(%8) _DOHASH@f(77,%0)(%8)
#define _HASH@f_N(%0)(%8) _DOHASH@f(78,%0)(%8)
#define _HASH@f_O(%0)(%8) _DOHASH@f(79,%0)(%8)
#define _HASH@f_P(%0)(%8) _DOHASH@f(80,%0)(%8)
#define _HASH@f_Q(%0)(%8) _DOHASH@f(81,%0)(%8)
#define _HASH@f_R(%0)(%8) _DOHASH@f(82,%0)(%8)
#define _HASH@f_S(%0)(%8) _DOHASH@f(83,%0)(%8)
#define _HASH@f_T(%0)(%8) _DOHASH@f(84,%0)(%8)
#define _HASH@f_U(%0)(%8) _DOHASH@f(85,%0)(%8)
#define _HASH@f_V(%0)(%8) _DOHASH@f(86,%0)(%8)
#define _HASH@f_W(%0)(%8) _DOHASH@f(87,%0)(%8)
#define _HASH@f_X(%0)(%8) _DOHASH@f(88,%0)(%8)
#define _HASH@f_Y(%0)(%8) _DOHASH@f(89,%0)(%8)
#define _HASH@f_Z(%0)(%8) _DOHASH@f(90,%0)(%8)

// Underscore.
#define _HASH@f__(%0)(%8) _DOHASH@f(95,%0)(%8)

// Lower case letters.
#define _HASH@f_a(%0)(%8) _DOHASH@f(97,%0)(%8)
#define _HASH@f_b(%0)(%8) _DOHASH@f(98,%0)(%8)
#define _HASH@f_c(%0)(%8) _DOHASH@f(99,%0)(%8)
#define _HASH@f_d(%0)(%8) _DOHASH@f(100,%0)(%8)
#define _HASH@f_e(%0)(%8) _DOHASH@f(101,%0)(%8)
#define _HASH@f_f(%0)(%8) _DOHASH@f(102,%0)(%8)
#define _HASH@f_g(%0)(%8) _DOHASH@f(103,%0)(%8)
#define _HASH@f_h(%0)(%8) _DOHASH@f(104,%0)(%8)
#define _HASH@f_i(%0)(%8) _DOHASH@f(105,%0)(%8)
#define _HASH@f_j(%0)(%8) _DOHASH@f(106,%0)(%8)
#define _HASH@f_k(%0)(%8) _DOHASH@f(107,%0)(%8)
#define _HASH@f_l(%0)(%8) _DOHASH@f(108,%0)(%8)
#define _HASH@f_m(%0)(%8) _DOHASH@f(109,%0)(%8)
#define _HASH@f_n(%0)(%8) _DOHASH@f(110,%0)(%8)
#define _HASH@f_o(%0)(%8) _DOHASH@f(111,%0)(%8)
#define _HASH@f_p(%0)(%8) _DOHASH@f(112,%0)(%8)
#define _HASH@f_q(%0)(%8) _DOHASH@f(113,%0)(%8)
#define _HASH@f_r(%0)(%8) _DOHASH@f(114,%0)(%8)
#define _HASH@f_s(%0)(%8) _DOHASH@f(115,%0)(%8)
#define _HASH@f_t(%0)(%8) _DOHASH@f(116,%0)(%8)
#define _HASH@f_u(%0)(%8) _DOHASH@f(117,%0)(%8)
#define _HASH@f_v(%0)(%8) _DOHASH@f(118,%0)(%8)
#define _HASH@f_w(%0)(%8) _DOHASH@f(119,%0)(%8)
#define _HASH@f_x(%0)(%8) _DOHASH@f(120,%0)(%8)
#define _HASH@f_y(%0)(%8) _DOHASH@f(121,%0)(%8)
#define _HASH@f_z(%0)(%8) _DOHASH@f(122,%0)(%8)

// String end.
#define _HASH@f_@(%0)(%8) %8

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
#define HASHi@fnv1(%0) _REHASH@if(%0,@,@)

// Internal call.
#define _REHASH@if(%0,%1) _HASH@if_%0(%1,)(2166136261)

// The bit that actually does the work.
#define _DOHASH@if(%0,%1,%2)(%8) _HASH@if_%1(%2)((%8*16777619^%0))

// Space.
#define _HASH@if_(%0)(%8) _DOHASH@if(32,%0)(%8)

// Numbers.
#define _HASH@if_0(%0)(%8) _DOHASH@if(48,%0)(%8)
#define _HASH@if_1(%0)(%8) _DOHASH@if(49,%0)(%8)
#define _HASH@if_2(%0)(%8) _DOHASH@if(50,%0)(%8)
#define _HASH@if_3(%0)(%8) _DOHASH@if(51,%0)(%8)
#define _HASH@if_4(%0)(%8) _DOHASH@if(52,%0)(%8)
#define _HASH@if_5(%0)(%8) _DOHASH@if(53,%0)(%8)
#define _HASH@if_6(%0)(%8) _DOHASH@if(54,%0)(%8)
#define _HASH@if_7(%0)(%8) _DOHASH@if(55,%0)(%8)
#define _HASH@if_8(%0)(%8) _DOHASH@if(56,%0)(%8)
#define _HASH@if_9(%0)(%8) _DOHASH@if(57,%0)(%8)

// Upper case letters.
#define _HASH@if_A(%0)(%8) _DOHASH@if(65,%0)(%8)
#define _HASH@if_B(%0)(%8) _DOHASH@if(66,%0)(%8)
#define _HASH@if_C(%0)(%8) _DOHASH@if(67,%0)(%8)
#define _HASH@if_D(%0)(%8) _DOHASH@if(68,%0)(%8)
#define _HASH@if_E(%0)(%8) _DOHASH@if(69,%0)(%8)
#define _HASH@if_F(%0)(%8) _DOHASH@if(70,%0)(%8)
#define _HASH@if_G(%0)(%8) _DOHASH@if(71,%0)(%8)
#define _HASH@if_H(%0)(%8) _DOHASH@if(72,%0)(%8)
#define _HASH@if_I(%0)(%8) _DOHASH@if(73,%0)(%8)
#define _HASH@if_J(%0)(%8) _DOHASH@if(74,%0)(%8)
#define _HASH@if_K(%0)(%8) _DOHASH@if(75,%0)(%8)
#define _HASH@if_L(%0)(%8) _DOHASH@if(76,%0)(%8)
#define _HASH@if_M(%0)(%8) _DOHASH@if(77,%0)(%8)
#define _HASH@if_N(%0)(%8) _DOHASH@if(78,%0)(%8)
#define _HASH@if_O(%0)(%8) _DOHASH@if(79,%0)(%8)
#define _HASH@if_P(%0)(%8) _DOHASH@if(80,%0)(%8)
#define _HASH@if_Q(%0)(%8) _DOHASH@if(81,%0)(%8)
#define _HASH@if_R(%0)(%8) _DOHASH@if(82,%0)(%8)
#define _HASH@if_S(%0)(%8) _DOHASH@if(83,%0)(%8)
#define _HASH@if_T(%0)(%8) _DOHASH@if(84,%0)(%8)
#define _HASH@if_U(%0)(%8) _DOHASH@if(85,%0)(%8)
#define _HASH@if_V(%0)(%8) _DOHASH@if(86,%0)(%8)
#define _HASH@if_W(%0)(%8) _DOHASH@if(87,%0)(%8)
#define _HASH@if_X(%0)(%8) _DOHASH@if(88,%0)(%8)
#define _HASH@if_Y(%0)(%8) _DOHASH@if(89,%0)(%8)
#define _HASH@if_Z(%0)(%8) _DOHASH@if(90,%0)(%8)

// Underscore.
#define _HASH@if__(%0)(%8) _DOHASH@if(95,%0)(%8)

// Lower case letters.
#define _HASH@if_a(%0)(%8) _DOHASH@if(65,%0)(%8)
#define _HASH@if_b(%0)(%8) _DOHASH@if(66,%0)(%8)
#define _HASH@if_c(%0)(%8) _DOHASH@if(67,%0)(%8)
#define _HASH@if_d(%0)(%8) _DOHASH@if(68,%0)(%8)
#define _HASH@if_e(%0)(%8) _DOHASH@if(69,%0)(%8)
#define _HASH@if_f(%0)(%8) _DOHASH@if(70,%0)(%8)
#define _HASH@if_g(%0)(%8) _DOHASH@if(71,%0)(%8)
#define _HASH@if_h(%0)(%8) _DOHASH@if(72,%0)(%8)
#define _HASH@if_i(%0)(%8) _DOHASH@if(73,%0)(%8)
#define _HASH@if_j(%0)(%8) _DOHASH@if(74,%0)(%8)
#define _HASH@if_k(%0)(%8) _DOHASH@if(75,%0)(%8)
#define _HASH@if_l(%0)(%8) _DOHASH@if(76,%0)(%8)
#define _HASH@if_m(%0)(%8) _DOHASH@if(77,%0)(%8)
#define _HASH@if_n(%0)(%8) _DOHASH@if(78,%0)(%8)
#define _HASH@if_o(%0)(%8) _DOHASH@if(79,%0)(%8)
#define _HASH@if_p(%0)(%8) _DOHASH@if(80,%0)(%8)
#define _HASH@if_q(%0)(%8) _DOHASH@if(81,%0)(%8)
#define _HASH@if_r(%0)(%8) _DOHASH@if(82,%0)(%8)
#define _HASH@if_s(%0)(%8) _DOHASH@if(83,%0)(%8)
#define _HASH@if_t(%0)(%8) _DOHASH@if(84,%0)(%8)
#define _HASH@if_u(%0)(%8) _DOHASH@if(85,%0)(%8)
#define _HASH@if_v(%0)(%8) _DOHASH@if(86,%0)(%8)
#define _HASH@if_w(%0)(%8) _DOHASH@if(87,%0)(%8)
#define _HASH@if_x(%0)(%8) _DOHASH@if(88,%0)(%8)
#define _HASH@if_y(%0)(%8) _DOHASH@if(89,%0)(%8)
#define _HASH@if_z(%0)(%8) _DOHASH@if(90,%0)(%8)

// String end.
#define _HASH@if_@(%0)(%8) %8
