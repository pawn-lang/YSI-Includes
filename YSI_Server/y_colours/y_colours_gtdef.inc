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

// These are the RGB values for the gametext colours (got manually using GIMP).
// These need to be added in to the main system so you can type and use them.
#define SAMP_GAME_TEXT                  0x906210AA
#define SAMP_GAME_TEXT_                 0x906210AA
#define SAMP_GAME_TEXT_H                0xD89318AA
#define SAMP_GAME_TEXT_HH               0xFFFF36AA
#define SAMP_GAME_TEXT_X                0x906210AA
#define SAMP_GAME_TEXT_XH               0xD89318AA
#define SAMP_GAME_TEXT_XHH              0xFFFF36AA
#define SAMP_GAME_TEXT_R                0xB4191DAA
#define SAMP_GAME_TEXT_RH               0xFF252BAA
#define SAMP_GAME_TEXT_RHH              0xFF3740AA
#define SAMP_GAME_TEXT_RHHH             0xFF5260AA
#define SAMP_GAME_TEXT_RHHHH            0xFF7B90AA
#define SAMP_GAME_TEXT_RHHHHH           0xFFB8D8AA
#define SAMP_GAME_TEXT_G                0x36682CAA
#define SAMP_GAME_TEXT_GH               0x519C42AA
#define SAMP_GAME_TEXT_GHH              0x79EA63AA
#define SAMP_GAME_TEXT_GHHH             0xB5FF94AA
#define SAMP_GAME_TEXT_GHHHH            0xFFFFDEAA
#define SAMP_GAME_TEXT_B                0x323C7FAA
#define SAMP_GAME_TEXT_BH               0x4B5ABEAA
#define SAMP_GAME_TEXT_BHH              0x7087FFAA
#define SAMP_GAME_TEXT_BHHH             0xA8CAFFAA
#define SAMP_GAME_TEXT_Y                0xE2C063AA
#define SAMP_GAME_TEXT_YH               0xFFFF94AA
#define SAMP_GAME_TEXT_YHH              0xFFFFDEAA
#define SAMP_GAME_TEXT_P                0xA86EFCAA
#define SAMP_GAME_TEXT_PH               0xFCA5FFAA
#define SAMP_GAME_TEXT_PHH              0xFFF7FFAA
#define SAMP_GAME_TEXT_W                0xFFFFFFAA
#define SAMP_GAME_TEXT_L                0x000000AA
// Second spellings.
#define SAMP_GAMETEXT                   0x906210AA
#define SAMP_GAMETEXT_                  0x906210AA
#define SAMP_GAMETEXT_H                 0xD89318AA
#define SAMP_GAMETEXT_HH                0xFFFF36AA
#define SAMP_GAMETEXT_X                 0x906210AA
#define SAMP_GAMETEXT_XH                0xD89318AA
#define SAMP_GAMETEXT_XHH               0xFFFF36AA
#define SAMP_GAMETEXT_R                 0xB4191DAA
#define SAMP_GAMETEXT_RH                0xFF252BAA
#define SAMP_GAMETEXT_RHH               0xFF3740AA
#define SAMP_GAMETEXT_RHHH              0xFF5260AA
#define SAMP_GAMETEXT_RHHHH             0xFF7B90AA
#define SAMP_GAMETEXT_RHHHHH            0xFFB8D8AA
#define SAMP_GAMETEXT_G                 0x36682CAA
#define SAMP_GAMETEXT_GH                0x519C42AA
#define SAMP_GAMETEXT_GHH               0x79EA63AA
#define SAMP_GAMETEXT_GHHH              0xB5FF94AA
#define SAMP_GAMETEXT_GHHHH             0xFFFFDEAA
#define SAMP_GAMETEXT_B                 0x323C7FAA
#define SAMP_GAMETEXT_BH                0x4B5ABEAA
#define SAMP_GAMETEXT_BHH               0x7087FFAA
#define SAMP_GAMETEXT_BHHH              0xA8CAFFAA
#define SAMP_GAMETEXT_Y                 0xE2C063AA
#define SAMP_GAMETEXT_YH                0xFFFF94AA
#define SAMP_GAMETEXT_YHH               0xFFFFDEAA
#define SAMP_GAMETEXT_P                 0xA86EFCAA
#define SAMP_GAMETEXT_PH                0xFCA5FFAA
#define SAMP_GAMETEXT_PHH               0xFFF7FFAA
#define SAMP_GAMETEXT_W                 0xFFFFFFAA
#define SAMP_GAMETEXT_L                 0x000000AA
// Third spellings.
#define SAMP_GT                         0x906210AA
#define SAMP_GT_                        0x906210AA
#define SAMP_GT_H                       0xD89318AA
#define SAMP_GT_HH                      0xFFFF36AA
#define SAMP_GT_X                       0x906210AA
#define SAMP_GT_XH                      0xD89318AA
#define SAMP_GT_XHH                     0xFFFF36AA
#define SAMP_GT_R                       0xB4191DAA
#define SAMP_GT_RH                      0xFF252BAA
#define SAMP_GT_RHH                     0xFF3740AA
#define SAMP_GT_RHHH                    0xFF5260AA
#define SAMP_GT_RHHHH                   0xFF7B90AA
#define SAMP_GT_RHHHHH                  0xFFB8D8AA
#define SAMP_GT_G                       0x36682CAA
#define SAMP_GT_GH                      0x519C42AA
#define SAMP_GT_GHH                     0x79EA63AA
#define SAMP_GT_GHHH                    0xB5FF94AA
#define SAMP_GT_GHHHH                   0xFFFFDEAA
#define SAMP_GT_B                       0x323C7FAA
#define SAMP_GT_BH                      0x4B5ABEAA
#define SAMP_GT_BHH                     0x7087FFAA
#define SAMP_GT_BHHH                    0xA8CAFFAA
#define SAMP_GT_Y                       0xE2C063AA
#define SAMP_GT_YH                      0xFFFF94AA
#define SAMP_GT_YHH                     0xFFFFDEAA
#define SAMP_GT_P                       0xA86EFCAA
#define SAMP_GT_PH                      0xFCA5FFAA
#define SAMP_GT_PHH                     0xFFF7FFAA
#define SAMP_GT_W                       0xFFFFFFAA
#define SAMP_GT_L                       0x000000AA

#define SAMP_GAME_TEXT_h                0xD89318AA
#define SAMP_GAME_TEXT_hh               0xFFFF36AA
#define SAMP_GAME_TEXT_x                0x906210AA
#define SAMP_GAME_TEXT_xh               0xD89318AA
#define SAMP_GAME_TEXT_xhh              0xFFFF36AA
#define SAMP_GAME_TEXT_r                0xB4191DAA
#define SAMP_GAME_TEXT_rh               0xFF252BAA
#define SAMP_GAME_TEXT_rhh              0xFF3740AA
#define SAMP_GAME_TEXT_rhhh             0xFF5260AA
#define SAMP_GAME_TEXT_rhhhh            0xFF7B90AA
#define SAMP_GAME_TEXT_rhhhhh           0xFFB8D8AA
#define SAMP_GAME_TEXT_g                0x36682CAA
#define SAMP_GAME_TEXT_gh               0x519C42AA
#define SAMP_GAME_TEXT_ghh              0x79EA63AA
#define SAMP_GAME_TEXT_ghhh             0xB5FF94AA
#define SAMP_GAME_TEXT_ghhhh            0xFFFFDEAA
#define SAMP_GAME_TEXT_b                0x323C7FAA
#define SAMP_GAME_TEXT_bh               0x4B5ABEAA
#define SAMP_GAME_TEXT_bhh              0x7087FFAA
#define SAMP_GAME_TEXT_bhhh             0xA8CAFFAA
#define SAMP_GAME_TEXT_y                0xE2C063AA
#define SAMP_GAME_TEXT_yh               0xFFFF94AA
#define SAMP_GAME_TEXT_yhh              0xFFFFDEAA
#define SAMP_GAME_TEXT_p                0xA86EFCAA
#define SAMP_GAME_TEXT_ph               0xFCA5FFAA
#define SAMP_GAME_TEXT_phh              0xFFF7FFAA
#define SAMP_GAME_TEXT_w                0xFFFFFFAA
#define SAMP_GAME_TEXT_l                0x000000AA
// Second spellings.
#define SAMP_GAMETEXT_h                 0xD89318AA
#define SAMP_GAMETEXT_hh                0xFFFF36AA
#define SAMP_GAMETEXT_x                 0x906210AA
#define SAMP_GAMETEXT_xh                0xD89318AA
#define SAMP_GAMETEXT_xhh               0xFFFF36AA
#define SAMP_GAMETEXT_r                 0xB4191DAA
#define SAMP_GAMETEXT_rh                0xFF252BAA
#define SAMP_GAMETEXT_rhh               0xFF3740AA
#define SAMP_GAMETEXT_rhhh              0xFF5260AA
#define SAMP_GAMETEXT_rhhhh             0xFF7B90AA
#define SAMP_GAMETEXT_rhhhhh            0xFFB8D8AA
#define SAMP_GAMETEXT_g                 0x36682CAA
#define SAMP_GAMETEXT_gh                0x519C42AA
#define SAMP_GAMETEXT_ghh               0x79EA63AA
#define SAMP_GAMETEXT_ghhh              0xB5FF94AA
#define SAMP_GAMETEXT_ghhhh             0xFFFFDEAA
#define SAMP_GAMETEXT_b                 0x323C7FAA
#define SAMP_GAMETEXT_bh                0x4B5ABEAA
#define SAMP_GAMETEXT_bhh               0x7087FFAA
#define SAMP_GAMETEXT_bhhh              0xA8CAFFAA
#define SAMP_GAMETEXT_y                 0xE2C063AA
#define SAMP_GAMETEXT_yh                0xFFFF94AA
#define SAMP_GAMETEXT_yhh               0xFFFFDEAA
#define SAMP_GAMETEXT_p                 0xA86EFCAA
#define SAMP_GAMETEXT_ph                0xFCA5FFAA
#define SAMP_GAMETEXT_phh               0xFFF7FFAA
#define SAMP_GAMETEXT_w                 0xFFFFFFAA
#define SAMP_GAMETEXT_l                 0x000000AA
// Third spellings.
#define SAMP_GT_h                       0xD89318AA
#define SAMP_GT_hh                      0xFFFF36AA
#define SAMP_GT_x                       0x906210AA
#define SAMP_GT_xh                      0xD89318AA
#define SAMP_GT_xhh                     0xFFFF36AA
#define SAMP_GT_r                       0xB4191DAA
#define SAMP_GT_rh                      0xFF252BAA
#define SAMP_GT_rhh                     0xFF3740AA
#define SAMP_GT_rhhh                    0xFF5260AA
#define SAMP_GT_rhhhh                   0xFF7B90AA
#define SAMP_GT_rhhhhh                  0xFFB8D8AA
#define SAMP_GT_g                       0x36682CAA
#define SAMP_GT_gh                      0x519C42AA
#define SAMP_GT_ghh                     0x79EA63AA
#define SAMP_GT_ghhh                    0xB5FF94AA
#define SAMP_GT_ghhhh                   0xFFFFDEAA
#define SAMP_GT_b                       0x323C7FAA
#define SAMP_GT_bh                      0x4B5ABEAA
#define SAMP_GT_bhh                     0x7087FFAA
#define SAMP_GT_bhhh                    0xA8CAFFAA
#define SAMP_GT_y                       0xE2C063AA
#define SAMP_GT_yh                      0xFFFF94AA
#define SAMP_GT_yhh                     0xFFFFDEAA
#define SAMP_GT_p                       0xA86EFCAA
#define SAMP_GT_ph                      0xFCA5FFAA
#define SAMP_GT_phh                     0xFFF7FFAA
#define SAMP_GT_w                       0xFFFFFFAA
#define SAMP_GT_l                       0x000000AA

// These are the RGB values for the gametext colours (got manually using GIMP).
// These need to be added in to the main system so you can type and use them.
#define Y_GAME_TEXT                     0x90621000
#define Y_GAME_TEXT_                    0x90621000
#define Y_GAME_TEXT_H                   0xD8931800
#define Y_GAME_TEXT_HH                  0xFFFF3600
#define Y_GAME_TEXT_X                   0x90621000
#define Y_GAME_TEXT_XH                  0xD8931800
#define Y_GAME_TEXT_XHH                 0xFFFF3600
#define Y_GAME_TEXT_R                   0xB4191D00
#define Y_GAME_TEXT_RH                  0xFF252B00
#define Y_GAME_TEXT_RHH                 0xFF374000
#define Y_GAME_TEXT_RHHH                0xFF526000
#define Y_GAME_TEXT_RHHHH               0xFF7B9000
#define Y_GAME_TEXT_RHHHHH              0xFFB8D800
#define Y_GAME_TEXT_G                   0x36682C00
#define Y_GAME_TEXT_GH                  0x519C4200
#define Y_GAME_TEXT_GHH                 0x79EA6300
#define Y_GAME_TEXT_GHHH                0xB5FF9400
#define Y_GAME_TEXT_GHHHH               0xFFFFDE00
#define Y_GAME_TEXT_B                   0x323C7F00
#define Y_GAME_TEXT_BH                  0x4B5ABE00
#define Y_GAME_TEXT_BHH                 0x7087FF00
#define Y_GAME_TEXT_BHHH                0xA8CAFF00
#define Y_GAME_TEXT_Y                   0xE2C06300
#define Y_GAME_TEXT_YH                  0xFFFF9400
#define Y_GAME_TEXT_YHH                 0xFFFFDE00
#define Y_GAME_TEXT_P                   0xA86EFC00
#define Y_GAME_TEXT_PH                  0xFCA5FF00
#define Y_GAME_TEXT_PHH                 0xFFF7FF00
#define Y_GAME_TEXT_W                   0xFFFFFF00
#define Y_GAME_TEXT_L                   0x00000000
#define Y_GAMETEXT                      0x90621000
#define Y_GAMETEXT_                     0x90621000
#define Y_GAMETEXT_H                    0xD8931800
#define Y_GAMETEXT_HH                   0xFFFF3600
#define Y_GAMETEXT_X                    0x90621000
#define Y_GAMETEXT_XH                   0xD8931800
#define Y_GAMETEXT_XHH                  0xFFFF3600
#define Y_GAMETEXT_R                    0xB4191D00
#define Y_GAMETEXT_RH                   0xFF252B00
#define Y_GAMETEXT_RHH                  0xFF374000
#define Y_GAMETEXT_RHHH                 0xFF526000
#define Y_GAMETEXT_RHHHH                0xFF7B9000
#define Y_GAMETEXT_RHHHHH               0xFFB8D800
#define Y_GAMETEXT_G                    0x36682C00
#define Y_GAMETEXT_GH                   0x519C4200
#define Y_GAMETEXT_GHH                  0x79EA6300
#define Y_GAMETEXT_GHHH                 0xB5FF9400
#define Y_GAMETEXT_GHHHH                0xFFFFDE00
#define Y_GAMETEXT_B                    0x323C7F00
#define Y_GAMETEXT_BH                   0x4B5ABE00
#define Y_GAMETEXT_BHH                  0x7087FF00
#define Y_GAMETEXT_BHHH                 0xA8CAFF00
#define Y_GAMETEXT_Y                    0xE2C06300
#define Y_GAMETEXT_YH                   0xFFFF9400
#define Y_GAMETEXT_YHH                  0xFFFFDE00
#define Y_GAMETEXT_P                    0xA86EFC00
#define Y_GAMETEXT_PH                   0xFCA5FF00
#define Y_GAMETEXT_PHH                  0xFFF7FF00
#define Y_GAMETEXT_W                    0xFFFFFF00
#define Y_GAMETEXT_L                    0x00000000
#define Y_GT                            0x90621000
#define Y_GT_                           0x90621000
#define Y_GT_H                          0xD8931800
#define Y_GT_HH                         0xFFFF3600
#define Y_GT_X                          0x90621000
#define Y_GT_XH                         0xD8931800
#define Y_GT_XHH                        0xFFFF3600
#define Y_GT_R                          0xB4191D00
#define Y_GT_RH                         0xFF252B00
#define Y_GT_RHH                        0xFF374000
#define Y_GT_RHHH                       0xFF526000
#define Y_GT_RHHHH                      0xFF7B9000
#define Y_GT_RHHHHH                     0xFFB8D800
#define Y_GT_G                          0x36682C00
#define Y_GT_GH                         0x519C4200
#define Y_GT_GHH                        0x79EA6300
#define Y_GT_GHHH                       0xB5FF9400
#define Y_GT_GHHHH                      0xFFFFDE00
#define Y_GT_B                          0x323C7F00
#define Y_GT_BH                         0x4B5ABE00
#define Y_GT_BHH                        0x7087FF00
#define Y_GT_BHHH                       0xA8CAFF00
#define Y_GT_Y                          0xE2C06300
#define Y_GT_YH                         0xFFFF9400
#define Y_GT_YHH                        0xFFFFDE00
#define Y_GT_P                          0xA86EFC00
#define Y_GT_PH                         0xFCA5FF00
#define Y_GT_PHH                        0xFFF7FF00
#define Y_GT_W                          0xFFFFFF00
#define Y_GT_L                          0x00000000

#define Y_GAME_TEXT_h                   0xD8931800
#define Y_GAME_TEXT_hh                  0xFFFF3600
#define Y_GAME_TEXT_x                   0x90621000
#define Y_GAME_TEXT_xh                  0xD8931800
#define Y_GAME_TEXT_xhh                 0xFFFF3600
#define Y_GAME_TEXT_r                   0xB4191D00
#define Y_GAME_TEXT_rh                  0xFF252B00
#define Y_GAME_TEXT_rhh                 0xFF374000
#define Y_GAME_TEXT_rhhh                0xFF526000
#define Y_GAME_TEXT_rhhhh               0xFF7B9000
#define Y_GAME_TEXT_rhhhhh              0xFFB8D800
#define Y_GAME_TEXT_g                   0x36682C00
#define Y_GAME_TEXT_gh                  0x519C4200
#define Y_GAME_TEXT_ghh                 0x79EA6300
#define Y_GAME_TEXT_ghhh                0xB5FF9400
#define Y_GAME_TEXT_ghhhh               0xFFFFDE00
#define Y_GAME_TEXT_b                   0x323C7F00
#define Y_GAME_TEXT_bh                  0x4B5ABE00
#define Y_GAME_TEXT_bhh                 0x7087FF00
#define Y_GAME_TEXT_bhhh                0xA8CAFF00
#define Y_GAME_TEXT_y                   0xE2C06300
#define Y_GAME_TEXT_yh                  0xFFFF9400
#define Y_GAME_TEXT_yhh                 0xFFFFDE00
#define Y_GAME_TEXT_p                   0xA86EFC00
#define Y_GAME_TEXT_ph                  0xFCA5FF00
#define Y_GAME_TEXT_phh                 0xFFF7FF00
#define Y_GAME_TEXT_w                   0xFFFFFF00
#define Y_GAME_TEXT_l                   0x00000000

#define Y_GAMETEXT_h                    0xD8931800
#define Y_GAMETEXT_hh                   0xFFFF3600
#define Y_GAMETEXT_x                    0x90621000
#define Y_GAMETEXT_xh                   0xD8931800
#define Y_GAMETEXT_xhh                  0xFFFF3600
#define Y_GAMETEXT_r                    0xB4191D00
#define Y_GAMETEXT_rh                   0xFF252B00
#define Y_GAMETEXT_rhh                  0xFF374000
#define Y_GAMETEXT_rhhh                 0xFF526000
#define Y_GAMETEXT_rhhhh                0xFF7B9000
#define Y_GAMETEXT_rhhhhh               0xFFB8D800
#define Y_GAMETEXT_g                    0x36682C00
#define Y_GAMETEXT_gh                   0x519C4200
#define Y_GAMETEXT_ghh                  0x79EA6300
#define Y_GAMETEXT_ghhh                 0xB5FF9400
#define Y_GAMETEXT_ghhhh                0xFFFFDE00
#define Y_GAMETEXT_b                    0x323C7F00
#define Y_GAMETEXT_bh                   0x4B5ABE00
#define Y_GAMETEXT_bhh                  0x7087FF00
#define Y_GAMETEXT_bhhh                 0xA8CAFF00
#define Y_GAMETEXT_y                    0xE2C06300
#define Y_GAMETEXT_yh                   0xFFFF9400
#define Y_GAMETEXT_yhh                  0xFFFFDE00
#define Y_GAMETEXT_p                    0xA86EFC00
#define Y_GAMETEXT_ph                   0xFCA5FF00
#define Y_GAMETEXT_phh                  0xFFF7FF00
#define Y_GAMETEXT_w                    0xFFFFFF00
#define Y_GAMETEXT_l                    0x00000000

#define Y_GT_h                          0xD8931800
#define Y_GT_hh                         0xFFFF3600
#define Y_GT_x                          0x90621000
#define Y_GT_xh                         0xD8931800
#define Y_GT_xhh                        0xFFFF3600
#define Y_GT_r                          0xB4191D00
#define Y_GT_rh                         0xFF252B00
#define Y_GT_rhh                        0xFF374000
#define Y_GT_rhhh                       0xFF526000
#define Y_GT_rhhhh                      0xFF7B9000
#define Y_GT_rhhhhh                     0xFFB8D800
#define Y_GT_g                          0x36682C00
#define Y_GT_gh                         0x519C4200
#define Y_GT_ghh                        0x79EA6300
#define Y_GT_ghhh                       0xB5FF9400
#define Y_GT_ghhhh                      0xFFFFDE00
#define Y_GT_b                          0x323C7F00
#define Y_GT_bh                         0x4B5ABE00
#define Y_GT_bhh                        0x7087FF00
#define Y_GT_bhhh                       0xA8CAFF00
#define Y_GT_y                          0xE2C06300
#define Y_GT_yh                         0xFFFF9400
#define Y_GT_yhh                        0xFFFFDE00
#define Y_GT_p                          0xA86EFC00
#define Y_GT_ph                         0xFCA5FF00
#define Y_GT_phh                        0xFFF7FF00
#define Y_GT_w                          0xFFFFFF00
#define Y_GT_l                          0x00000000

// String versions.
#define GT__                "{906210}"
#define GT_H                "{D89318}"
#define GT_HH               "{FFFF36}"
#define GT_X                "{906210}"
#define GT_XH               "{D89318}"
#define GT_XHH              "{FFFF36}"
#define GT_R                "{B4191D}"
#define GT_RH               "{FF252B}"
#define GT_RHH              "{FF3740}"
#define GT_RHHH             "{FF5260}"
#define GT_RHHHH            "{FF7B90}"
#define GT_RHHHHH           "{FFB8D8}"
#define GT_G                "{36682C}"
#define GT_GH               "{519C42}"
#define GT_GHH              "{79EA63}"
#define GT_GHHH             "{B5FF94}"
#define GT_GHHHH            "{FFFFDE}"
#define GT_B                "{323C7F}"
#define GT_BH               "{4B5ABE}"
#define GT_BHH              "{7087FF}"
#define GT_BHHH             "{A8CAFF}"
#define GT_Y                "{E2C063}"
#define GT_YH               "{FFFF94}"
#define GT_YHH              "{FFFFDE}"
#define GT_P                "{A86EFC}"
#define GT_PH               "{FCA5FF}"
#define GT_PHH              "{FFF7FF}"
#define GT_W                "{FFFFFF}"
#define GT_L                "{000000}"
#define GT_h                "{D89318}"
#define GT_hh               "{FFFF36}"
#define GT_x                "{906210}"
#define GT_xh               "{D89318}"
#define GT_xhh              "{FFFF36}"
#define GT_r                "{B4191D}"
#define GT_rh               "{FF252B}"
#define GT_rhh              "{FF3740}"
#define GT_rhhh             "{FF5260}"
#define GT_rhhhh            "{FF7B90}"
#define GT_rhhhhh           "{FFB8D8}"
#define GT_g                "{36682C}"
#define GT_gh               "{519C42}"
#define GT_ghh              "{79EA63}"
#define GT_ghhh             "{B5FF94}"
#define GT_ghhhh            "{FFFFDE}"
#define GT_b                "{323C7F}"
#define GT_bh               "{4B5ABE}"
#define GT_bhh              "{7087FF}"
#define GT_bhhh             "{A8CAFF}"
#define GT_y                "{E2C063}"
#define GT_yh               "{FFFF94}"
#define GT_yhh              "{FFFFDE}"
#define GT_p                "{A86EFC}"
#define GT_ph               "{FCA5FF}"
#define GT_phh              "{FFF7FF}"
#define GT_w                "{FFFFFF}"
#define GT_l                "{000000}"
#define GAMETEXT_                 "{906210}"
#define GAMETEXT_H                "{D89318}"
#define GAMETEXT_HH               "{FFFF36}"
#define GAMETEXT_X                "{906210}"
#define GAMETEXT_XH               "{D89318}"
#define GAMETEXT_XHH              "{FFFF36}"
#define GAMETEXT_R                "{B4191D}"
#define GAMETEXT_RH               "{FF252B}"
#define GAMETEXT_RHH              "{FF3740}"
#define GAMETEXT_RHHH             "{FF5260}"
#define GAMETEXT_RHHHH            "{FF7B90}"
#define GAMETEXT_RHHHHH           "{FFB8D8}"
#define GAMETEXT_G                "{36682C}"
#define GAMETEXT_GH               "{519C42}"
#define GAMETEXT_GHH              "{79EA63}"
#define GAMETEXT_GHHH             "{B5FF94}"
#define GAMETEXT_GHHHH            "{FFFFDE}"
#define GAMETEXT_B                "{323C7F}"
#define GAMETEXT_BH               "{4B5ABE}"
#define GAMETEXT_BHH              "{7087FF}"
#define GAMETEXT_BHHH             "{A8CAFF}"
#define GAMETEXT_Y                "{E2C063}"
#define GAMETEXT_YH               "{FFFF94}"
#define GAMETEXT_YHH              "{FFFFDE}"
#define GAMETEXT_P                "{A86EFC}"
#define GAMETEXT_PH               "{FCA5FF}"
#define GAMETEXT_PHH              "{FFF7FF}"
#define GAMETEXT_W                "{FFFFFF}"
#define GAMETEXT_L                "{000000}"
#define GAMETEXT_h                "{D89318}"
#define GAMETEXT_hh               "{FFFF36}"
#define GAMETEXT_x                "{906210}"
#define GAMETEXT_xh               "{D89318}"
#define GAMETEXT_xhh              "{FFFF36}"
#define GAMETEXT_r                "{B4191D}"
#define GAMETEXT_rh               "{FF252B}"
#define GAMETEXT_rhh              "{FF3740}"
#define GAMETEXT_rhhh             "{FF5260}"
#define GAMETEXT_rhhhh            "{FF7B90}"
#define GAMETEXT_rhhhhh           "{FFB8D8}"
#define GAMETEXT_g                "{36682C}"
#define GAMETEXT_gh               "{519C42}"
#define GAMETEXT_ghh              "{79EA63}"
#define GAMETEXT_ghhh             "{B5FF94}"
#define GAMETEXT_ghhhh            "{FFFFDE}"
#define GAMETEXT_b                "{323C7F}"
#define GAMETEXT_bh               "{4B5ABE}"
#define GAMETEXT_bhh              "{7087FF}"
#define GAMETEXT_bhhh             "{A8CAFF}"
#define GAMETEXT_y                "{E2C063}"
#define GAMETEXT_yh               "{FFFF94}"
#define GAMETEXT_yhh              "{FFFFDE}"
#define GAMETEXT_p                "{A86EFC}"
#define GAMETEXT_ph               "{FCA5FF}"
#define GAMETEXT_phh              "{FFF7FF}"
#define GAMETEXT_w                "{FFFFFF}"
#define GAMETEXT_l                "{000000}"
#define GAME_TEXT_                 "{906210}"
#define GAME_TEXT_H                "{D89318}"
#define GAME_TEXT_HH               "{FFFF36}"
#define GAME_TEXT_X                "{906210}"
#define GAME_TEXT_XH               "{D89318}"
#define GAME_TEXT_XHH              "{FFFF36}"
#define GAME_TEXT_R                "{B4191D}"
#define GAME_TEXT_RH               "{FF252B}"
#define GAME_TEXT_RHH              "{FF3740}"
#define GAME_TEXT_RHHH             "{FF5260}"
#define GAME_TEXT_RHHHH            "{FF7B90}"
#define GAME_TEXT_RHHHHH           "{FFB8D8}"
#define GAME_TEXT_G                "{36682C}"
#define GAME_TEXT_GH               "{519C42}"
#define GAME_TEXT_GHH              "{79EA63}"
#define GAME_TEXT_GHHH             "{B5FF94}"
#define GAME_TEXT_GHHHH            "{FFFFDE}"
#define GAME_TEXT_B                "{323C7F}"
#define GAME_TEXT_BH               "{4B5ABE}"
#define GAME_TEXT_BHH              "{7087FF}"
#define GAME_TEXT_BHHH             "{A8CAFF}"
#define GAME_TEXT_Y                "{E2C063}"
#define GAME_TEXT_YH               "{FFFF94}"
#define GAME_TEXT_YHH              "{FFFFDE}"
#define GAME_TEXT_P                "{A86EFC}"
#define GAME_TEXT_PH               "{FCA5FF}"
#define GAME_TEXT_PHH              "{FFF7FF}"
#define GAME_TEXT_W                "{FFFFFF}"
#define GAME_TEXT_L                "{000000}"
#define GAME_TEXT_h                "{D89318}"
#define GAME_TEXT_hh               "{FFFF36}"
#define GAME_TEXT_x                "{906210}"
#define GAME_TEXT_xh               "{D89318}"
#define GAME_TEXT_xhh              "{FFFF36}"
#define GAME_TEXT_r                "{B4191D}"
#define GAME_TEXT_rh               "{FF252B}"
#define GAME_TEXT_rhh              "{FF3740}"
#define GAME_TEXT_rhhh             "{FF5260}"
#define GAME_TEXT_rhhhh            "{FF7B90}"
#define GAME_TEXT_rhhhhh           "{FFB8D8}"
#define GAME_TEXT_g                "{36682C}"
#define GAME_TEXT_gh               "{519C42}"
#define GAME_TEXT_ghh              "{79EA63}"
#define GAME_TEXT_ghhh             "{B5FF94}"
#define GAME_TEXT_ghhhh            "{FFFFDE}"
#define GAME_TEXT_b                "{323C7F}"
#define GAME_TEXT_bh               "{4B5ABE}"
#define GAME_TEXT_bhh              "{7087FF}"
#define GAME_TEXT_bhhh             "{A8CAFF}"
#define GAME_TEXT_y                "{E2C063}"
#define GAME_TEXT_yh               "{FFFF94}"
#define GAME_TEXT_yhh              "{FFFFDE}"
#define GAME_TEXT_p                "{A86EFC}"
#define GAME_TEXT_ph               "{FCA5FF}"
#define GAME_TEXT_phh              "{FFF7FF}"
#define GAME_TEXT_w                "{FFFFFF}"
#define GAME_TEXT_l                "{000000}"

// Clever versions.
#define _GT_                 906210
#define _GT_h                D89318
#define _GT_hh               FFFF36
#define _GT_x                906210
#define _GT_xh               D89318
#define _GT_xhh              FFFF36
#define _GT_r                B4191D
#define _GT_rh               FF252B
#define _GT_rhh              FF3740
#define _GT_rhhh             FF5260
#define _GT_rhhhh            FF7B90
#define _GT_rhhhhh           FFB8D8
#define _GT_g                36682C
#define _GT_gh               519C42
#define _GT_ghh              79EA63
#define _GT_ghhh             B5FF94
#define _GT_ghhhh            FFFFDE
#define _GT_b                323C7F
#define _GT_bh               4B5ABE
#define _GT_bhh              7087FF
#define _GT_bhhh             A8CAFF
#define _GT_y                E2C063
#define _GT_yh               FFFF94
#define _GT_yhh              FFFFDE
#define _GT_p                A86EFC
#define _GT_ph               FCA5FF
#define _GT_phh              FFF7FF
#define _GT_w                FFFFFF
#define _GT_l                000000

