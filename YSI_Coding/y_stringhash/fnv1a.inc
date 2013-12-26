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

#define ha:%9()
#define H_Da(%0,%5,%1,%6) ha:H_Na%5(%0)H_Sa:%6]ha:@A%5:H_Na%5(%1)
#define H_Sa:%6]%7|||%8||| %7|||((%8^%6)*16777619)|||
#define H_Ea:|||%0||| %0

// Test for the current character.
#define @Aa:H_Naa(%1a%0)%7||| H_Da(%1,a,%0,97)%7|||
#define @Ab:H_Nab(%1b%0)%7||| H_Da(%1,b,%0,98)%7|||
#define @Ac:H_Nac(%1c%0)%7||| H_Da(%1,c,%0,99)%7|||
#define @Ad:H_Nad(%1d%0)%7||| H_Da(%1,d,%0,100)%7|||
#define @Ae:H_Nae(%1e%0)%7||| H_Da(%1,e,%0,101)%7|||
#define @Af:H_Naf(%1f%0)%7||| H_Da(%1,f,%0,102)%7|||
#define @Ag:H_Nag(%1g%0)%7||| H_Da(%1,g,%0,103)%7|||
#define @Ah:H_Nah(%1h%0)%7||| H_Da(%1,h,%0,104)%7|||
#define @Ai:H_Nai(%1i%0)%7||| H_Da(%1,i,%0,105)%7|||
#define @Aj:H_Naj(%1j%0)%7||| H_Da(%1,j,%0,106)%7|||
#define @Ak:H_Nak(%1k%0)%7||| H_Da(%1,k,%0,107)%7|||
#define @Al:H_Nal(%1l%0)%7||| H_Da(%1,l,%0,108)%7|||
#define @Am:H_Nam(%1m%0)%7||| H_Da(%1,m,%0,109)%7|||
#define @An:H_Nan(%1n%0)%7||| H_Da(%1,n,%0,110)%7|||
#define @Ao:H_Nao(%1o%0)%7||| H_Da(%1,o,%0,111)%7|||
#define @Ap:H_Nap(%1p%0)%7||| H_Da(%1,p,%0,112)%7|||
#define @Aq:H_Naq(%1q%0)%7||| H_Da(%1,q,%0,113)%7|||
#define @Ar:H_Nar(%1r%0)%7||| H_Da(%1,r,%0,114)%7|||
#define @As:H_Nas(%1s%0)%7||| H_Da(%1,s,%0,115)%7|||
#define @At:H_Nat(%1t%0)%7||| H_Da(%1,t,%0,116)%7|||
#define @Au:H_Nau(%1u%0)%7||| H_Da(%1,u,%0,117)%7|||
#define @Av:H_Nav(%1v%0)%7||| H_Da(%1,v,%0,118)%7|||
#define @Aw:H_Naw(%1w%0)%7||| H_Da(%1,w,%0,119)%7|||
#define @Ax:H_Nax(%1x%0)%7||| H_Da(%1,x,%0,120)%7|||
#define @Ay:H_Nay(%1y%0)%7||| H_Da(%1,y,%0,121)%7|||
#define @Az:H_Naz(%1z%0)%7||| H_Da(%1,z,%0,122)%7|||

#define @AA:H_NaA(%1A%0)%7||| H_Da(%1,A,%0,65)%7|||
#define @AB:H_NaB(%1B%0)%7||| H_Da(%1,B,%0,66)%7|||
#define @AC:H_NaC(%1C%0)%7||| H_Da(%1,C,%0,67)%7|||
#define @AD:H_NaD(%1D%0)%7||| H_Da(%1,D,%0,68)%7|||
#define @AE:H_NaE(%1E%0)%7||| H_Da(%1,E,%0,69)%7|||
#define @AF:H_NaF(%1F%0)%7||| H_Da(%1,F,%0,70)%7|||
#define @AG:H_NaG(%1G%0)%7||| H_Da(%1,G,%0,71)%7|||
#define @AH:H_NaH(%1H%0)%7||| H_Da(%1,H,%0,72)%7|||
#define @AI:H_NaI(%1I%0)%7||| H_Da(%1,I,%0,73)%7|||
#define @AJ:H_NaJ(%1J%0)%7||| H_Da(%1,J,%0,74)%7|||
#define @AK:H_NaK(%1K%0)%7||| H_Da(%1,K,%0,75)%7|||
#define @AL:H_NaL(%1L%0)%7||| H_Da(%1,L,%0,76)%7|||
#define @AM:H_NaM(%1M%0)%7||| H_Da(%1,M,%0,77)%7|||
#define @AN:H_NaN(%1N%0)%7||| H_Da(%1,N,%0,78)%7|||
#define @AO:H_NaO(%1O%0)%7||| H_Da(%1,O,%0,79)%7|||
#define @AP:H_NaP(%1P%0)%7||| H_Da(%1,P,%0,80)%7|||
#define @AQ:H_NaQ(%1Q%0)%7||| H_Da(%1,Q,%0,81)%7|||
#define @AR:H_NaR(%1R%0)%7||| H_Da(%1,R,%0,82)%7|||
#define @AS:H_NaS(%1S%0)%7||| H_Da(%1,S,%0,83)%7|||
#define @AT:H_NaT(%1T%0)%7||| H_Da(%1,T,%0,84)%7|||
#define @AU:H_NaU(%1U%0)%7||| H_Da(%1,U,%0,85)%7|||
#define @AV:H_NaV(%1V%0)%7||| H_Da(%1,V,%0,86)%7|||
#define @AW:H_NaW(%1W%0)%7||| H_Da(%1,W,%0,87)%7|||
#define @AX:H_NaX(%1X%0)%7||| H_Da(%1,X,%0,88)%7|||
#define @AY:H_NaY(%1Y%0)%7||| H_Da(%1,Y,%0,89)%7|||
#define @AZ:H_NaZ(%1Z%0)%7||| H_Da(%1,Z,%0,90)%7|||

#define @A0:H_Na0(%10%0)%7||| H_Da(%1,0,%0,48)%7|||
#define @A1:H_Na1(%11%0)%7||| H_Da(%1,1,%0,49)%7|||
#define @A2:H_Na2(%12%0)%7||| H_Da(%1,2,%0,50)%7|||
#define @A3:H_Na3(%13%0)%7||| H_Da(%1,3,%0,51)%7|||
#define @A4:H_Na4(%14%0)%7||| H_Da(%1,4,%0,52)%7|||
#define @A5:H_Na5(%15%0)%7||| H_Da(%1,5,%0,53)%7|||
#define @A6:H_Na6(%16%0)%7||| H_Da(%1,6,%0,54)%7|||
#define @A7:H_Na7(%17%0)%7||| H_Da(%1,7,%0,55)%7|||
#define @A8:H_Na8(%18%0)%7||| H_Da(%1,8,%0,56)%7|||
#define @A9:H_Na9(%19%0)%7||| H_Da(%1,9,%0,57)%7|||

#define @A_:H_Na_(%1_%0)%7||| H_Da(%1,_,%0,95)%7|||
//#define ha@:H_Sa(@%0,%1)%7||| H_Da(%0)%7|||

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

#define hd:%9()
#define H_Dd(%0,%5,%1,%6) hd:H_Nd%5(%0)H_Sd:%6]hd:@D%5:H_Nd%5(%1)
#define H_Sd:%6]%7|||%8||| %7|||((%8^%6)*16777619)|||
#define H_Ed:|||%0||| %0

// Test for the current character.
#define @Da:H_Nda(%1a%0)%7||| H_Dd(%1,a,%0,65)%7|||
#define @Db:H_Ndb(%1b%0)%7||| H_Dd(%1,b,%0,66)%7|||
#define @Dc:H_Ndc(%1c%0)%7||| H_Dd(%1,c,%0,67)%7|||
#define @Dd:H_Ndd(%1d%0)%7||| H_Dd(%1,d,%0,68)%7|||
#define @De:H_Nde(%1e%0)%7||| H_Dd(%1,e,%0,69)%7|||
#define @Df:H_Ndf(%1f%0)%7||| H_Dd(%1,f,%0,70)%7|||
#define @Dg:H_Ndg(%1g%0)%7||| H_Dd(%1,g,%0,71)%7|||
#define @Dh:H_Ndh(%1h%0)%7||| H_Dd(%1,h,%0,72)%7|||
#define @Di:H_Ndi(%1i%0)%7||| H_Dd(%1,i,%0,73)%7|||
#define @Dj:H_Ndj(%1j%0)%7||| H_Dd(%1,j,%0,74)%7|||
#define @Dk:H_Ndk(%1k%0)%7||| H_Dd(%1,k,%0,75)%7|||
#define @Dl:H_Ndl(%1l%0)%7||| H_Dd(%1,l,%0,76)%7|||
#define @Dm:H_Ndm(%1m%0)%7||| H_Dd(%1,m,%0,77)%7|||
#define @Dn:H_Ndn(%1n%0)%7||| H_Dd(%1,n,%0,78)%7|||
#define @Do:H_Ndo(%1o%0)%7||| H_Dd(%1,o,%0,79)%7|||
#define @Dp:H_Ndp(%1p%0)%7||| H_Dd(%1,p,%0,80)%7|||
#define @Dq:H_Ndq(%1q%0)%7||| H_Dd(%1,q,%0,81)%7|||
#define @Dr:H_Ndr(%1r%0)%7||| H_Dd(%1,r,%0,82)%7|||
#define @Ds:H_Nds(%1s%0)%7||| H_Dd(%1,s,%0,83)%7|||
#define @Dt:H_Ndt(%1t%0)%7||| H_Dd(%1,t,%0,84)%7|||
#define @Du:H_Ndu(%1u%0)%7||| H_Dd(%1,u,%0,85)%7|||
#define @Dv:H_Ndv(%1v%0)%7||| H_Dd(%1,v,%0,86)%7|||
#define @Dw:H_Ndw(%1w%0)%7||| H_Dd(%1,w,%0,87)%7|||
#define @Dx:H_Ndx(%1x%0)%7||| H_Dd(%1,x,%0,88)%7|||
#define @Dy:H_Ndy(%1y%0)%7||| H_Dd(%1,y,%0,89)%7|||
#define @Dz:H_Ndz(%1z%0)%7||| H_Dd(%1,z,%0,90)%7|||

#define @DA:H_NdA(%1A%0)%7||| H_Dd(%1,A,%0,65)%7|||
#define @DB:H_NdB(%1B%0)%7||| H_Dd(%1,B,%0,66)%7|||
#define @DC:H_NdC(%1C%0)%7||| H_Dd(%1,C,%0,67)%7|||
#define @DD:H_NdD(%1D%0)%7||| H_Dd(%1,D,%0,68)%7|||
#define @DE:H_NdE(%1E%0)%7||| H_Dd(%1,E,%0,69)%7|||
#define @DF:H_NdF(%1F%0)%7||| H_Dd(%1,F,%0,70)%7|||
#define @DG:H_NdG(%1G%0)%7||| H_Dd(%1,G,%0,71)%7|||
#define @DH:H_NdH(%1H%0)%7||| H_Dd(%1,H,%0,72)%7|||
#define @DI:H_NdI(%1I%0)%7||| H_Dd(%1,I,%0,73)%7|||
#define @DJ:H_NdJ(%1J%0)%7||| H_Dd(%1,J,%0,74)%7|||
#define @DK:H_NdK(%1K%0)%7||| H_Dd(%1,K,%0,75)%7|||
#define @DL:H_NdL(%1L%0)%7||| H_Dd(%1,L,%0,76)%7|||
#define @DM:H_NdM(%1M%0)%7||| H_Dd(%1,M,%0,77)%7|||
#define @DN:H_NdN(%1N%0)%7||| H_Dd(%1,N,%0,78)%7|||
#define @DO:H_NdO(%1O%0)%7||| H_Dd(%1,O,%0,79)%7|||
#define @DP:H_NdP(%1P%0)%7||| H_Dd(%1,P,%0,80)%7|||
#define @DQ:H_NdQ(%1Q%0)%7||| H_Dd(%1,Q,%0,81)%7|||
#define @DR:H_NdR(%1R%0)%7||| H_Dd(%1,R,%0,82)%7|||
#define @DS:H_NdS(%1S%0)%7||| H_Dd(%1,S,%0,83)%7|||
#define @DT:H_NdT(%1T%0)%7||| H_Dd(%1,T,%0,84)%7|||
#define @DU:H_NdU(%1U%0)%7||| H_Dd(%1,U,%0,85)%7|||
#define @DV:H_NdV(%1V%0)%7||| H_Dd(%1,V,%0,86)%7|||
#define @DW:H_NdW(%1W%0)%7||| H_Dd(%1,W,%0,87)%7|||
#define @DX:H_NdX(%1X%0)%7||| H_Dd(%1,X,%0,88)%7|||
#define @DY:H_NdY(%1Y%0)%7||| H_Dd(%1,Y,%0,89)%7|||
#define @DZ:H_NdZ(%1Z%0)%7||| H_Dd(%1,Z,%0,90)%7|||

#define @D0:H_Nd0(%10%0)%7||| H_Dd(%1,0,%0,48)%7|||
#define @D1:H_Nd1(%11%0)%7||| H_Dd(%1,1,%0,49)%7|||
#define @D2:H_Nd2(%12%0)%7||| H_Dd(%1,2,%0,50)%7|||
#define @D3:H_Nd3(%13%0)%7||| H_Dd(%1,3,%0,51)%7|||
#define @D4:H_Nd4(%14%0)%7||| H_Dd(%1,4,%0,52)%7|||
#define @D5:H_Nd5(%15%0)%7||| H_Dd(%1,5,%0,53)%7|||
#define @D6:H_Nd6(%16%0)%7||| H_Dd(%1,6,%0,54)%7|||
#define @D7:H_Nd7(%17%0)%7||| H_Dd(%1,7,%0,55)%7|||
#define @D8:H_Nd8(%18%0)%7||| H_Dd(%1,8,%0,56)%7|||
#define @D9:H_Nd9(%19%0)%7||| H_Dd(%1,9,%0,57)%7|||

#define @D_:H_Nd_(%1_%0)%7||| H_Dd(%1,_,%0,95)%7|||
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
#define HASH@fnv1a(%0) _REHASH@a(%0,@,@)

// Internal call.
#define _REHASH@a(%0,%1) _HASH@a_%0(%1,)(2166136261)

// The bit that actually does the work.
#define _DOHASH@a(%0,%1,%2)(%8) _HASH@a_%1(%2)(((%8^%0)*16777619))

// Space.
#define _HASH@a_(%0)(%8) _DOHASH@a(32,%0)(%8)

// Numbers.
#define _HASH@a_0(%0)(%8) _DOHASH@a(48,%0)(%8)
#define _HASH@a_1(%0)(%8) _DOHASH@a(49,%0)(%8)
#define _HASH@a_2(%0)(%8) _DOHASH@a(50,%0)(%8)
#define _HASH@a_3(%0)(%8) _DOHASH@a(51,%0)(%8)
#define _HASH@a_4(%0)(%8) _DOHASH@a(52,%0)(%8)
#define _HASH@a_5(%0)(%8) _DOHASH@a(53,%0)(%8)
#define _HASH@a_6(%0)(%8) _DOHASH@a(54,%0)(%8)
#define _HASH@a_7(%0)(%8) _DOHASH@a(55,%0)(%8)
#define _HASH@a_8(%0)(%8) _DOHASH@a(56,%0)(%8)
#define _HASH@a_9(%0)(%8) _DOHASH@a(57,%0)(%8)

// Upper case letters.
#define _HASH@a_A(%0)(%8) _DOHASH@a(65,%0)(%8)
#define _HASH@a_B(%0)(%8) _DOHASH@a(66,%0)(%8)
#define _HASH@a_C(%0)(%8) _DOHASH@a(67,%0)(%8)
#define _HASH@a_D(%0)(%8) _DOHASH@a(68,%0)(%8)
#define _HASH@a_E(%0)(%8) _DOHASH@a(69,%0)(%8)
#define _HASH@a_F(%0)(%8) _DOHASH@a(70,%0)(%8)
#define _HASH@a_G(%0)(%8) _DOHASH@a(71,%0)(%8)
#define _HASH@a_H(%0)(%8) _DOHASH@a(72,%0)(%8)
#define _HASH@a_I(%0)(%8) _DOHASH@a(73,%0)(%8)
#define _HASH@a_J(%0)(%8) _DOHASH@a(74,%0)(%8)
#define _HASH@a_K(%0)(%8) _DOHASH@a(75,%0)(%8)
#define _HASH@a_L(%0)(%8) _DOHASH@a(76,%0)(%8)
#define _HASH@a_M(%0)(%8) _DOHASH@a(77,%0)(%8)
#define _HASH@a_N(%0)(%8) _DOHASH@a(78,%0)(%8)
#define _HASH@a_O(%0)(%8) _DOHASH@a(79,%0)(%8)
#define _HASH@a_P(%0)(%8) _DOHASH@a(80,%0)(%8)
#define _HASH@a_Q(%0)(%8) _DOHASH@a(81,%0)(%8)
#define _HASH@a_R(%0)(%8) _DOHASH@a(82,%0)(%8)
#define _HASH@a_S(%0)(%8) _DOHASH@a(83,%0)(%8)
#define _HASH@a_T(%0)(%8) _DOHASH@a(84,%0)(%8)
#define _HASH@a_U(%0)(%8) _DOHASH@a(85,%0)(%8)
#define _HASH@a_V(%0)(%8) _DOHASH@a(86,%0)(%8)
#define _HASH@a_W(%0)(%8) _DOHASH@a(87,%0)(%8)
#define _HASH@a_X(%0)(%8) _DOHASH@a(88,%0)(%8)
#define _HASH@a_Y(%0)(%8) _DOHASH@a(89,%0)(%8)
#define _HASH@a_Z(%0)(%8) _DOHASH@a(90,%0)(%8)

// Underscore.
#define _HASH@a__(%0)(%8) _DOHASH@a(95,%0)(%8)

// Lower case letters.
#define _HASH@a_a(%0)(%8) _DOHASH@a(97,%0)(%8)
#define _HASH@a_b(%0)(%8) _DOHASH@a(98,%0)(%8)
#define _HASH@a_c(%0)(%8) _DOHASH@a(99,%0)(%8)
#define _HASH@a_d(%0)(%8) _DOHASH@a(100,%0)(%8)
#define _HASH@a_e(%0)(%8) _DOHASH@a(101,%0)(%8)
#define _HASH@a_f(%0)(%8) _DOHASH@a(102,%0)(%8)
#define _HASH@a_g(%0)(%8) _DOHASH@a(103,%0)(%8)
#define _HASH@a_h(%0)(%8) _DOHASH@a(104,%0)(%8)
#define _HASH@a_i(%0)(%8) _DOHASH@a(105,%0)(%8)
#define _HASH@a_j(%0)(%8) _DOHASH@a(106,%0)(%8)
#define _HASH@a_k(%0)(%8) _DOHASH@a(107,%0)(%8)
#define _HASH@a_l(%0)(%8) _DOHASH@a(108,%0)(%8)
#define _HASH@a_m(%0)(%8) _DOHASH@a(109,%0)(%8)
#define _HASH@a_n(%0)(%8) _DOHASH@a(110,%0)(%8)
#define _HASH@a_o(%0)(%8) _DOHASH@a(111,%0)(%8)
#define _HASH@a_p(%0)(%8) _DOHASH@a(112,%0)(%8)
#define _HASH@a_q(%0)(%8) _DOHASH@a(113,%0)(%8)
#define _HASH@a_r(%0)(%8) _DOHASH@a(114,%0)(%8)
#define _HASH@a_s(%0)(%8) _DOHASH@a(115,%0)(%8)
#define _HASH@a_t(%0)(%8) _DOHASH@a(116,%0)(%8)
#define _HASH@a_u(%0)(%8) _DOHASH@a(117,%0)(%8)
#define _HASH@a_v(%0)(%8) _DOHASH@a(118,%0)(%8)
#define _HASH@a_w(%0)(%8) _DOHASH@a(119,%0)(%8)
#define _HASH@a_x(%0)(%8) _DOHASH@a(120,%0)(%8)
#define _HASH@a_y(%0)(%8) _DOHASH@a(121,%0)(%8)
#define _HASH@a_z(%0)(%8) _DOHASH@a(122,%0)(%8)

// String end.
#define _HASH@a_@(%0)(%8) %8

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
#define HASHi@fnv1a(%0) _REHASH@ia(%0,@,@)

// Internal call.
#define _REHASH@ia(%0,%1) _HASH@ia_%0(%1,)(2166136261)

// The bit that actually does the work.
#define _DOHASH@ia(%0,%1,%2)(%8) _HASH@ia_%1(%2)(((%8^%0)*16777619))

// Space.
#define _HASH@ia_(%0)(%8) _DOHASH@ia(32,%0)(%8)

// Numbers.
#define _HASH@ia_0(%0)(%8) _DOHASH@ia(48,%0)(%8)
#define _HASH@ia_1(%0)(%8) _DOHASH@ia(49,%0)(%8)
#define _HASH@ia_2(%0)(%8) _DOHASH@ia(50,%0)(%8)
#define _HASH@ia_3(%0)(%8) _DOHASH@ia(51,%0)(%8)
#define _HASH@ia_4(%0)(%8) _DOHASH@ia(52,%0)(%8)
#define _HASH@ia_5(%0)(%8) _DOHASH@ia(53,%0)(%8)
#define _HASH@ia_6(%0)(%8) _DOHASH@ia(54,%0)(%8)
#define _HASH@ia_7(%0)(%8) _DOHASH@ia(55,%0)(%8)
#define _HASH@ia_8(%0)(%8) _DOHASH@ia(56,%0)(%8)
#define _HASH@ia_9(%0)(%8) _DOHASH@ia(57,%0)(%8)

// Upper case letters.
#define _HASH@ia_A(%0)(%8) _DOHASH@ia(65,%0)(%8)
#define _HASH@ia_B(%0)(%8) _DOHASH@ia(66,%0)(%8)
#define _HASH@ia_C(%0)(%8) _DOHASH@ia(67,%0)(%8)
#define _HASH@ia_D(%0)(%8) _DOHASH@ia(68,%0)(%8)
#define _HASH@ia_E(%0)(%8) _DOHASH@ia(69,%0)(%8)
#define _HASH@ia_F(%0)(%8) _DOHASH@ia(70,%0)(%8)
#define _HASH@ia_G(%0)(%8) _DOHASH@ia(71,%0)(%8)
#define _HASH@ia_H(%0)(%8) _DOHASH@ia(72,%0)(%8)
#define _HASH@ia_I(%0)(%8) _DOHASH@ia(73,%0)(%8)
#define _HASH@ia_J(%0)(%8) _DOHASH@ia(74,%0)(%8)
#define _HASH@ia_K(%0)(%8) _DOHASH@ia(75,%0)(%8)
#define _HASH@ia_L(%0)(%8) _DOHASH@ia(76,%0)(%8)
#define _HASH@ia_M(%0)(%8) _DOHASH@ia(77,%0)(%8)
#define _HASH@ia_N(%0)(%8) _DOHASH@ia(78,%0)(%8)
#define _HASH@ia_O(%0)(%8) _DOHASH@ia(79,%0)(%8)
#define _HASH@ia_P(%0)(%8) _DOHASH@ia(80,%0)(%8)
#define _HASH@ia_Q(%0)(%8) _DOHASH@ia(81,%0)(%8)
#define _HASH@ia_R(%0)(%8) _DOHASH@ia(82,%0)(%8)
#define _HASH@ia_S(%0)(%8) _DOHASH@ia(83,%0)(%8)
#define _HASH@ia_T(%0)(%8) _DOHASH@ia(84,%0)(%8)
#define _HASH@ia_U(%0)(%8) _DOHASH@ia(85,%0)(%8)
#define _HASH@ia_V(%0)(%8) _DOHASH@ia(86,%0)(%8)
#define _HASH@ia_W(%0)(%8) _DOHASH@ia(87,%0)(%8)
#define _HASH@ia_X(%0)(%8) _DOHASH@ia(88,%0)(%8)
#define _HASH@ia_Y(%0)(%8) _DOHASH@ia(89,%0)(%8)
#define _HASH@ia_Z(%0)(%8) _DOHASH@ia(90,%0)(%8)

// Underscore.
#define _HASH@ia__(%0)(%8) _DOHASH@ia(95,%0)(%8)

// Lower case letters.
#define _HASH@ia_a(%0)(%8) _DOHASH@ia(65,%0)(%8)
#define _HASH@ia_b(%0)(%8) _DOHASH@ia(66,%0)(%8)
#define _HASH@ia_c(%0)(%8) _DOHASH@ia(67,%0)(%8)
#define _HASH@ia_d(%0)(%8) _DOHASH@ia(68,%0)(%8)
#define _HASH@ia_e(%0)(%8) _DOHASH@ia(69,%0)(%8)
#define _HASH@ia_f(%0)(%8) _DOHASH@ia(70,%0)(%8)
#define _HASH@ia_g(%0)(%8) _DOHASH@ia(71,%0)(%8)
#define _HASH@ia_h(%0)(%8) _DOHASH@ia(72,%0)(%8)
#define _HASH@ia_i(%0)(%8) _DOHASH@ia(73,%0)(%8)
#define _HASH@ia_j(%0)(%8) _DOHASH@ia(74,%0)(%8)
#define _HASH@ia_k(%0)(%8) _DOHASH@ia(75,%0)(%8)
#define _HASH@ia_l(%0)(%8) _DOHASH@ia(76,%0)(%8)
#define _HASH@ia_m(%0)(%8) _DOHASH@ia(77,%0)(%8)
#define _HASH@ia_n(%0)(%8) _DOHASH@ia(78,%0)(%8)
#define _HASH@ia_o(%0)(%8) _DOHASH@ia(79,%0)(%8)
#define _HASH@ia_p(%0)(%8) _DOHASH@ia(80,%0)(%8)
#define _HASH@ia_q(%0)(%8) _DOHASH@ia(81,%0)(%8)
#define _HASH@ia_r(%0)(%8) _DOHASH@ia(82,%0)(%8)
#define _HASH@ia_s(%0)(%8) _DOHASH@ia(83,%0)(%8)
#define _HASH@ia_t(%0)(%8) _DOHASH@ia(84,%0)(%8)
#define _HASH@ia_u(%0)(%8) _DOHASH@ia(85,%0)(%8)
#define _HASH@ia_v(%0)(%8) _DOHASH@ia(86,%0)(%8)
#define _HASH@ia_w(%0)(%8) _DOHASH@ia(87,%0)(%8)
#define _HASH@ia_x(%0)(%8) _DOHASH@ia(88,%0)(%8)
#define _HASH@ia_y(%0)(%8) _DOHASH@ia(89,%0)(%8)
#define _HASH@ia_z(%0)(%8) _DOHASH@ia(90,%0)(%8)

// String end.
#define _HASH@ia_@(%0)(%8) %8
