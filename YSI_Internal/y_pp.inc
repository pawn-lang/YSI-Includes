#if defined _INC_y_pp
	#endinput
#endif
#define _INC_y_pp

/*+
 * <library name="y_pp">
 * <section>
 *  Description
 * </section>
 *  More complex processing in the pre-processor.
 * <section>
 *  Version
 * </section>
 *  1.0
 * </library>
 *//** *//*
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

/*-------------------------------------------------------------------------*//*+
 * <param name="%9">Number of times to repeat.</param>
 * <param name="%0">What to repeat.</param>
 * <param name="%1">What to insert between repetitions.</param>
 * <remarks>
 *  Does something in the pre-processor multiple times.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define PP_LOOP<%9>(%0)(%1) PP_LOOP@%9(%0)(%1)
#define PP_LOOP@0(%0)(%1)
#define PP_LOOP@1(%0)(%1) %0
#define PP_LOOP@2(%0)(%1) %0%1%0
#define PP_LOOP@3(%0)(%1) %0%1%0%1%0
#define PP_LOOP@4(%0)(%1) %0%1%0%1%0%1%0
#define PP_LOOP@5(%0)(%1) %0%1%0%1%0%1%0%1%0
#define PP_LOOP@6(%0)(%1) %0%1%0%1%0%1%0%1%0%1%0
#define PP_LOOP@7(%0)(%1) %0%1%0%1%0%1%0%1%0%1%0%1%0
#define PP_LOOP@8(%0)(%1) %0%1%0%1%0%1%0%1%0%1%0%1%0%1%0
#define PP_LOOP@9(%0)(%1) PP_LOOP@8(%0)(%1)%1PP_LOOP@1(%0)(%1)
#define PP_LOOP@10(%0)(%1) PP_LOOP@8(%0)(%1)%1PP_LOOP@2(%0)(%1)
#define PP_LOOP@11(%0)(%1) PP_LOOP@8(%0)(%1)%0PP_LOOP@3(%0)(%1)
#define PP_LOOP@12(%0)(%1) PP_LOOP@8(%0)(%1)%1PP_LOOP@4(%0)(%1)
#define PP_LOOP@13(%0)(%1) PP_LOOP@8(%0)(%1)%1PP_LOOP@5(%0)(%1)
#define PP_LOOP@14(%0)(%1) PP_LOOP@8(%0)(%1)%1PP_LOOP@6(%0)(%1)
#define PP_LOOP@15(%0)(%1) PP_LOOP@8(%0)(%1)%0PP_LOOP@7(%0)(%1)
#define PP_LOOP@16(%0)(%1) PP_LOOP@8(%0)(%1)%1PP_LOOP@8(%0)(%1)
#define PP_LOOP@17(%0)(%1) PP_LOOP@16(%0)(%1)%1PP_LOOP@1(%0)(%1)
#define PP_LOOP@18(%0)(%1) PP_LOOP@16(%0)(%1)%1PP_LOOP@2(%0)(%1)
#define PP_LOOP@19(%0)(%1) PP_LOOP@16(%0)(%1)%0PP_LOOP@3(%0)(%1)
#define PP_LOOP@20(%0)(%1) PP_LOOP@16(%0)(%1)%1PP_LOOP@4(%0)(%1)
#define PP_LOOP@21(%0)(%1) PP_LOOP@16(%0)(%1)%1PP_LOOP@5(%0)(%1)
#define PP_LOOP@22(%0)(%1) PP_LOOP@16(%0)(%1)%1PP_LOOP@6(%0)(%1)
#define PP_LOOP@23(%0)(%1) PP_LOOP@16(%0)(%1)%0PP_LOOP@7(%0)(%1)
#define PP_LOOP@24(%0)(%1) PP_LOOP@16(%0)(%1)%1PP_LOOP@8(%0)(%1)
#define PP_LOOP@25(%0)(%1) PP_LOOP@16(%0)(%1)%1PP_LOOP@9(%0)(%1)
#define PP_LOOP@26(%0)(%1) PP_LOOP@16(%0)(%1)%1PP_LOOP@10(%0)(%1)
#define PP_LOOP@27(%0)(%1) PP_LOOP@16(%0)(%1)%0PP_LOOP@11(%0)(%1)
#define PP_LOOP@28(%0)(%1) PP_LOOP@16(%0)(%1)%1PP_LOOP@12(%0)(%1)
#define PP_LOOP@29(%0)(%1) PP_LOOP@16(%0)(%1)%1PP_LOOP@13(%0)(%1)
#define PP_LOOP@30(%0)(%1) PP_LOOP@16(%0)(%1)%1PP_LOOP@14(%0)(%1)
#define PP_LOOP@31(%0)(%1) PP_LOOP@16(%0)(%1)%0PP_LOOP@15(%0)(%1)
#define PP_LOOP@32(%0)(%1) PP_LOOP@16(%0)(%1)%1PP_LOOP@16(%0)(%1)
#define PP_LOOP@33(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@1(%0)(%1)
#define PP_LOOP@34(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@2(%0)(%1)
#define PP_LOOP@35(%0)(%1) PP_LOOP@32(%0)(%1)%0PP_LOOP@3(%0)(%1)
#define PP_LOOP@36(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@4(%0)(%1)
#define PP_LOOP@37(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@5(%0)(%1)
#define PP_LOOP@38(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@6(%0)(%1)
#define PP_LOOP@39(%0)(%1) PP_LOOP@32(%0)(%1)%0PP_LOOP@7(%0)(%1)
#define PP_LOOP@40(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@8(%0)(%1)
#define PP_LOOP@41(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@9(%0)(%1)
#define PP_LOOP@42(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@10(%0)(%1)
#define PP_LOOP@43(%0)(%1) PP_LOOP@32(%0)(%1)%0PP_LOOP@11(%0)(%1)
#define PP_LOOP@44(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@12(%0)(%1)
#define PP_LOOP@45(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@13(%0)(%1)
#define PP_LOOP@46(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@14(%0)(%1)
#define PP_LOOP@47(%0)(%1) PP_LOOP@32(%0)(%1)%0PP_LOOP@15(%0)(%1)
#define PP_LOOP@48(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@16(%0)(%1)
#define PP_LOOP@49(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@17(%0)(%1)
#define PP_LOOP@50(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@18(%0)(%1)
#define PP_LOOP@51(%0)(%1) PP_LOOP@32(%0)(%1)%0PP_LOOP@19(%0)(%1)
#define PP_LOOP@52(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@20(%0)(%1)
#define PP_LOOP@53(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@21(%0)(%1)
#define PP_LOOP@54(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@22(%0)(%1)
#define PP_LOOP@55(%0)(%1) PP_LOOP@32(%0)(%1)%0PP_LOOP@23(%0)(%1)
#define PP_LOOP@56(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@24(%0)(%1)
#define PP_LOOP@57(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@25(%0)(%1)
#define PP_LOOP@58(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@26(%0)(%1)
#define PP_LOOP@59(%0)(%1) PP_LOOP@32(%0)(%1)%0PP_LOOP@27(%0)(%1)
#define PP_LOOP@60(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@28(%0)(%1)
#define PP_LOOP@61(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@29(%0)(%1)
#define PP_LOOP@62(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@30(%0)(%1)
#define PP_LOOP@63(%0)(%1) PP_LOOP@32(%0)(%1)%0PP_LOOP@31(%0)(%1)
#define PP_LOOP@64(%0)(%1) PP_LOOP@32(%0)(%1)%1PP_LOOP@32(%0)(%1)
#define PP_LOOP@65(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@1(%0)(%1)
#define PP_LOOP@66(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@2(%0)(%1)
#define PP_LOOP@67(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@3(%0)(%1)
#define PP_LOOP@68(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@4(%0)(%1)
#define PP_LOOP@69(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@5(%0)(%1)
#define PP_LOOP@70(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@6(%0)(%1)
#define PP_LOOP@71(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@7(%0)(%1)
#define PP_LOOP@72(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@8(%0)(%1)
#define PP_LOOP@73(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@9(%0)(%1)
#define PP_LOOP@74(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@10(%0)(%1)
#define PP_LOOP@75(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@11(%0)(%1)
#define PP_LOOP@76(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@12(%0)(%1)
#define PP_LOOP@77(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@13(%0)(%1)
#define PP_LOOP@78(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@14(%0)(%1)
#define PP_LOOP@79(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@15(%0)(%1)
#define PP_LOOP@80(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@16(%0)(%1)
#define PP_LOOP@81(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@17(%0)(%1)
#define PP_LOOP@82(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@18(%0)(%1)
#define PP_LOOP@83(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@19(%0)(%1)
#define PP_LOOP@84(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@20(%0)(%1)
#define PP_LOOP@85(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@21(%0)(%1)
#define PP_LOOP@86(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@22(%0)(%1)
#define PP_LOOP@87(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@23(%0)(%1)
#define PP_LOOP@88(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@24(%0)(%1)
#define PP_LOOP@89(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@25(%0)(%1)
#define PP_LOOP@90(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@26(%0)(%1)
#define PP_LOOP@91(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@27(%0)(%1)
#define PP_LOOP@92(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@28(%0)(%1)
#define PP_LOOP@93(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@29(%0)(%1)
#define PP_LOOP@94(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@30(%0)(%1)
#define PP_LOOP@95(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@31(%0)(%1)
#define PP_LOOP@96(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@32(%0)(%1)
#define PP_LOOP@97(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@33(%0)(%1)
#define PP_LOOP@98(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@34(%0)(%1)
#define PP_LOOP@99(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@35(%0)(%1)
#define PP_LOOP@100(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@36(%0)(%1)
#define PP_LOOP@101(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@37(%0)(%1)
#define PP_LOOP@102(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@38(%0)(%1)
#define PP_LOOP@103(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@39(%0)(%1)
#define PP_LOOP@104(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@40(%0)(%1)
#define PP_LOOP@105(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@41(%0)(%1)
#define PP_LOOP@106(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@42(%0)(%1)
#define PP_LOOP@107(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@43(%0)(%1)
#define PP_LOOP@108(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@44(%0)(%1)
#define PP_LOOP@109(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@45(%0)(%1)
#define PP_LOOP@110(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@46(%0)(%1)
#define PP_LOOP@111(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@47(%0)(%1)
#define PP_LOOP@112(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@48(%0)(%1)
#define PP_LOOP@113(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@49(%0)(%1)
#define PP_LOOP@114(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@50(%0)(%1)
#define PP_LOOP@115(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@51(%0)(%1)
#define PP_LOOP@116(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@52(%0)(%1)
#define PP_LOOP@117(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@53(%0)(%1)
#define PP_LOOP@118(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@54(%0)(%1)
#define PP_LOOP@119(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@55(%0)(%1)
#define PP_LOOP@120(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@56(%0)(%1)
#define PP_LOOP@121(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@57(%0)(%1)
#define PP_LOOP@122(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@58(%0)(%1)
#define PP_LOOP@123(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@59(%0)(%1)
#define PP_LOOP@124(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@60(%0)(%1)
#define PP_LOOP@125(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@61(%0)(%1)
#define PP_LOOP@126(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@62(%0)(%1)
#define PP_LOOP@127(%0)(%1) PP_LOOP@64(%0)(%1)%0PP_LOOP@63(%0)(%1)
#define PP_LOOP@128(%0)(%1) PP_LOOP@64(%0)(%1)%1PP_LOOP@64(%0)(%1)

