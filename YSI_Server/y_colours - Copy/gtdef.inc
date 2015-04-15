/**--------------------------------------------------------------------------**\
					==========================
					 y_colours - X11 colours!
					==========================
Description:
	This holds the colour information that used to be part of the text system
	but which is far more useful than just for text.  This now supports the full
	set of X11 colours, both by name and by definition.  You can also define
	your own if you so choose (up to 32 - should be enough given that this
	includes the X11 colours).
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
	
	The Original Code is the YSI colours include.
	
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
	1.0
Changelog:
	16/03/15:
		Added SA:MP and GTA colours.
		Changed naming scheme for consistency.
	06/01/14:
		Added embeddable versions of all colours.
		Cached all macros for faster compilation.
		Added "GT" macro for "~r~" use in SA:MP text.
		Split gametext colours in to a separate file.
	20/02/12:
		Added broadcastfunc of colours.	
	29/11/10:
		Added the ability to use "X11" prefixes in strings.
		Added colourspace resolution for converting {FF0000} to ~r~.
	25/11/10:
		First version.
\**--------------------------------------------------------------------------**/

// These are the RGB values for the gametext colours (got manually using GIMP).
// These need to be added in to the main system so you can type and use them.
#define @GAME_TEXT                  0x906210AA
#define @GAME_TEXT_                 0x906210AA
#define @GAME_TEXT_H                0xD89318AA
#define @GAME_TEXT_HH               0xFFFF36AA
#define @GAME_TEXT_X                0x906210AA
#define @GAME_TEXT_XH               0xD89318AA
#define @GAME_TEXT_XHH              0xFFFF36AA
#define @GAME_TEXT_R                0xB4191DAA
#define @GAME_TEXT_RH               0xFF252BAA
#define @GAME_TEXT_RHH              0xFF3740AA
#define @GAME_TEXT_RHHH             0xFF5260AA
#define @GAME_TEXT_RHHHH            0xFF7B90AA
#define @GAME_TEXT_RHHHHH           0xFFB8D8AA
#define @GAME_TEXT_G                0x36682CAA
#define @GAME_TEXT_GH               0x519C42AA
#define @GAME_TEXT_GHH              0x79EA63AA
#define @GAME_TEXT_GHHH             0xB5FF94AA
#define @GAME_TEXT_GHHHH            0xFFFFDEAA
#define @GAME_TEXT_B                0x323C7FAA
#define @GAME_TEXT_BH               0x4B5ABEAA
#define @GAME_TEXT_BHH              0x7087FFAA
#define @GAME_TEXT_BHHH             0xA8CAFFAA
#define @GAME_TEXT_Y                0xE2C063AA
#define @GAME_TEXT_YH               0xFFFF94AA
#define @GAME_TEXT_YHH              0xFFFFDEAA
#define @GAME_TEXT_P                0xA86EFCAA
#define @GAME_TEXT_PH               0xFCA5FFAA
#define @GAME_TEXT_PHH              0xFFF7FFAA
#define @GAME_TEXT_W                0xFFFFFFAA
#define @GAME_TEXT_L                0x000000AA
// Second spellings.
#define @GAMETEXT                   0x906210AA
#define @GAMETEXT_                  0x906210AA
#define @GAMETEXT_H                 0xD89318AA
#define @GAMETEXT_HH                0xFFFF36AA
#define @GAMETEXT_X                 0x906210AA
#define @GAMETEXT_XH                0xD89318AA
#define @GAMETEXT_XHH               0xFFFF36AA
#define @GAMETEXT_R                 0xB4191DAA
#define @GAMETEXT_RH                0xFF252BAA
#define @GAMETEXT_RHH               0xFF3740AA
#define @GAMETEXT_RHHH              0xFF5260AA
#define @GAMETEXT_RHHHH             0xFF7B90AA
#define @GAMETEXT_RHHHHH            0xFFB8D8AA
#define @GAMETEXT_G                 0x36682CAA
#define @GAMETEXT_GH                0x519C42AA
#define @GAMETEXT_GHH               0x79EA63AA
#define @GAMETEXT_GHHH              0xB5FF94AA
#define @GAMETEXT_GHHHH             0xFFFFDEAA
#define @GAMETEXT_B                 0x323C7FAA
#define @GAMETEXT_BH                0x4B5ABEAA
#define @GAMETEXT_BHH               0x7087FFAA
#define @GAMETEXT_BHHH              0xA8CAFFAA
#define @GAMETEXT_Y                 0xE2C063AA
#define @GAMETEXT_YH                0xFFFF94AA
#define @GAMETEXT_YHH               0xFFFFDEAA
#define @GAMETEXT_P                 0xA86EFCAA
#define @GAMETEXT_PH                0xFCA5FFAA
#define @GAMETEXT_PHH               0xFFF7FFAA
#define @GAMETEXT_W                 0xFFFFFFAA
#define @GAMETEXT_L                 0x000000AA
// Third spellings.
#define @GT                         0x906210AA
#define @GT_                        0x906210AA
#define @GT_H                       0xD89318AA
#define @GT_HH                      0xFFFF36AA
#define @GT_X                       0x906210AA
#define @GT_XH                      0xD89318AA
#define @GT_XHH                     0xFFFF36AA
#define @GT_R                       0xB4191DAA
#define @GT_RH                      0xFF252BAA
#define @GT_RHH                     0xFF3740AA
#define @GT_RHHH                    0xFF5260AA
#define @GT_RHHHH                   0xFF7B90AA
#define @GT_RHHHHH                  0xFFB8D8AA
#define @GT_G                       0x36682CAA
#define @GT_GH                      0x519C42AA
#define @GT_GHH                     0x79EA63AA
#define @GT_GHHH                    0xB5FF94AA
#define @GT_GHHHH                   0xFFFFDEAA
#define @GT_B                       0x323C7FAA
#define @GT_BH                      0x4B5ABEAA
#define @GT_BHH                     0x7087FFAA
#define @GT_BHHH                    0xA8CAFFAA
#define @GT_Y                       0xE2C063AA
#define @GT_YH                      0xFFFF94AA
#define @GT_YHH                     0xFFFFDEAA
#define @GT_P                       0xA86EFCAA
#define @GT_PH                      0xFCA5FFAA
#define @GT_PHH                     0xFFF7FFAA
#define @GT_W                       0xFFFFFFAA
#define @GT_L                       0x000000AA

#define @GAME_TEXT_h                0xD89318AA
#define @GAME_TEXT_hh               0xFFFF36AA
#define @GAME_TEXT_x                0x906210AA
#define @GAME_TEXT_xh               0xD89318AA
#define @GAME_TEXT_xhh              0xFFFF36AA
#define @GAME_TEXT_r                0xB4191DAA
#define @GAME_TEXT_rh               0xFF252BAA
#define @GAME_TEXT_rhh              0xFF3740AA
#define @GAME_TEXT_rhhh             0xFF5260AA
#define @GAME_TEXT_rhhhh            0xFF7B90AA
#define @GAME_TEXT_rhhhhh           0xFFB8D8AA
#define @GAME_TEXT_g                0x36682CAA
#define @GAME_TEXT_gh               0x519C42AA
#define @GAME_TEXT_ghh              0x79EA63AA
#define @GAME_TEXT_ghhh             0xB5FF94AA
#define @GAME_TEXT_ghhhh            0xFFFFDEAA
#define @GAME_TEXT_b                0x323C7FAA
#define @GAME_TEXT_bh               0x4B5ABEAA
#define @GAME_TEXT_bhh              0x7087FFAA
#define @GAME_TEXT_bhhh             0xA8CAFFAA
#define @GAME_TEXT_y                0xE2C063AA
#define @GAME_TEXT_yh               0xFFFF94AA
#define @GAME_TEXT_yhh              0xFFFFDEAA
#define @GAME_TEXT_p                0xA86EFCAA
#define @GAME_TEXT_ph               0xFCA5FFAA
#define @GAME_TEXT_phh              0xFFF7FFAA
#define @GAME_TEXT_w                0xFFFFFFAA
#define @GAME_TEXT_l                0x000000AA
// Second spellings.
#define @GAMETEXT_h                 0xD89318AA
#define @GAMETEXT_hh                0xFFFF36AA
#define @GAMETEXT_x                 0x906210AA
#define @GAMETEXT_xh                0xD89318AA
#define @GAMETEXT_xhh               0xFFFF36AA
#define @GAMETEXT_r                 0xB4191DAA
#define @GAMETEXT_rh                0xFF252BAA
#define @GAMETEXT_rhh               0xFF3740AA
#define @GAMETEXT_rhhh              0xFF5260AA
#define @GAMETEXT_rhhhh             0xFF7B90AA
#define @GAMETEXT_rhhhhh            0xFFB8D8AA
#define @GAMETEXT_g                 0x36682CAA
#define @GAMETEXT_gh                0x519C42AA
#define @GAMETEXT_ghh               0x79EA63AA
#define @GAMETEXT_ghhh              0xB5FF94AA
#define @GAMETEXT_ghhhh             0xFFFFDEAA
#define @GAMETEXT_b                 0x323C7FAA
#define @GAMETEXT_bh                0x4B5ABEAA
#define @GAMETEXT_bhh               0x7087FFAA
#define @GAMETEXT_bhhh              0xA8CAFFAA
#define @GAMETEXT_y                 0xE2C063AA
#define @GAMETEXT_yh                0xFFFF94AA
#define @GAMETEXT_yhh               0xFFFFDEAA
#define @GAMETEXT_p                 0xA86EFCAA
#define @GAMETEXT_ph                0xFCA5FFAA
#define @GAMETEXT_phh               0xFFF7FFAA
#define @GAMETEXT_w                 0xFFFFFFAA
#define @GAMETEXT_l                 0x000000AA
// Third spellings.
#define @GT_h                       0xD89318AA
#define @GT_hh                      0xFFFF36AA
#define @GT_x                       0x906210AA
#define @GT_xh                      0xD89318AA
#define @GT_xhh                     0xFFFF36AA
#define @GT_r                       0xB4191DAA
#define @GT_rh                      0xFF252BAA
#define @GT_rhh                     0xFF3740AA
#define @GT_rhhh                    0xFF5260AA
#define @GT_rhhhh                   0xFF7B90AA
#define @GT_rhhhhh                  0xFFB8D8AA
#define @GT_g                       0x36682CAA
#define @GT_gh                      0x519C42AA
#define @GT_ghh                     0x79EA63AA
#define @GT_ghhh                    0xB5FF94AA
#define @GT_ghhhh                   0xFFFFDEAA
#define @GT_b                       0x323C7FAA
#define @GT_bh                      0x4B5ABEAA
#define @GT_bhh                     0x7087FFAA
#define @GT_bhhh                    0xA8CAFFAA
#define @GT_y                       0xE2C063AA
#define @GT_yh                      0xFFFF94AA
#define @GT_yhh                     0xFFFFDEAA
#define @GT_p                       0xA86EFCAA
#define @GT_ph                      0xFCA5FFAA
#define @GT_phh                     0xFFF7FFAA
#define @GT_w                       0xFFFFFFAA
#define @GT_l                       0x000000AA

// These are the RGB values for the gametext colours (got manually using GIMP).
// These need to be added in to the main system so you can type and use them.
#define _GAME_TEXT                     0x90621000
#define _GAME_TEXT_                    0x90621000
#define _GAME_TEXT_H                   0xD8931800
#define _GAME_TEXT_HH                  0xFFFF3600
#define _GAME_TEXT_X                   0x90621000
#define _GAME_TEXT_XH                  0xD8931800
#define _GAME_TEXT_XHH                 0xFFFF3600
#define _GAME_TEXT_R                   0xB4191D00
#define _GAME_TEXT_RH                  0xFF252B00
#define _GAME_TEXT_RHH                 0xFF374000
#define _GAME_TEXT_RHHH                0xFF526000
#define _GAME_TEXT_RHHHH               0xFF7B9000
#define _GAME_TEXT_RHHHHH              0xFFB8D800
#define _GAME_TEXT_G                   0x36682C00
#define _GAME_TEXT_GH                  0x519C4200
#define _GAME_TEXT_GHH                 0x79EA6300
#define _GAME_TEXT_GHHH                0xB5FF9400
#define _GAME_TEXT_GHHHH               0xFFFFDE00
#define _GAME_TEXT_B                   0x323C7F00
#define _GAME_TEXT_BH                  0x4B5ABE00
#define _GAME_TEXT_BHH                 0x7087FF00
#define _GAME_TEXT_BHHH                0xA8CAFF00
#define _GAME_TEXT_Y                   0xE2C06300
#define _GAME_TEXT_YH                  0xFFFF9400
#define _GAME_TEXT_YHH                 0xFFFFDE00
#define _GAME_TEXT_P                   0xA86EFC00
#define _GAME_TEXT_PH                  0xFCA5FF00
#define _GAME_TEXT_PHH                 0xFFF7FF00
#define _GAME_TEXT_W                   0xFFFFFF00
#define _GAME_TEXT_L                   0x00000000
#define _GAMETEXT                      0x90621000
#define _GAMETEXT_                     0x90621000
#define _GAMETEXT_H                    0xD8931800
#define _GAMETEXT_HH                   0xFFFF3600
#define _GAMETEXT_X                    0x90621000
#define _GAMETEXT_XH                   0xD8931800
#define _GAMETEXT_XHH                  0xFFFF3600
#define _GAMETEXT_R                    0xB4191D00
#define _GAMETEXT_RH                   0xFF252B00
#define _GAMETEXT_RHH                  0xFF374000
#define _GAMETEXT_RHHH                 0xFF526000
#define _GAMETEXT_RHHHH                0xFF7B9000
#define _GAMETEXT_RHHHHH               0xFFB8D800
#define _GAMETEXT_G                    0x36682C00
#define _GAMETEXT_GH                   0x519C4200
#define _GAMETEXT_GHH                  0x79EA6300
#define _GAMETEXT_GHHH                 0xB5FF9400
#define _GAMETEXT_GHHHH                0xFFFFDE00
#define _GAMETEXT_B                    0x323C7F00
#define _GAMETEXT_BH                   0x4B5ABE00
#define _GAMETEXT_BHH                  0x7087FF00
#define _GAMETEXT_BHHH                 0xA8CAFF00
#define _GAMETEXT_Y                    0xE2C06300
#define _GAMETEXT_YH                   0xFFFF9400
#define _GAMETEXT_YHH                  0xFFFFDE00
#define _GAMETEXT_P                    0xA86EFC00
#define _GAMETEXT_PH                   0xFCA5FF00
#define _GAMETEXT_PHH                  0xFFF7FF00
#define _GAMETEXT_W                    0xFFFFFF00
#define _GAMETEXT_L                    0x00000000
#define _GT                            0x90621000
#define _GT_                           0x90621000
#define _GT_H                          0xD8931800
#define _GT_HH                         0xFFFF3600
#define _GT_X                          0x90621000
#define _GT_XH                         0xD8931800
#define _GT_XHH                        0xFFFF3600
#define _GT_R                          0xB4191D00
#define _GT_RH                         0xFF252B00
#define _GT_RHH                        0xFF374000
#define _GT_RHHH                       0xFF526000
#define _GT_RHHHH                      0xFF7B9000
#define _GT_RHHHHH                     0xFFB8D800
#define _GT_G                          0x36682C00
#define _GT_GH                         0x519C4200
#define _GT_GHH                        0x79EA6300
#define _GT_GHHH                       0xB5FF9400
#define _GT_GHHHH                      0xFFFFDE00
#define _GT_B                          0x323C7F00
#define _GT_BH                         0x4B5ABE00
#define _GT_BHH                        0x7087FF00
#define _GT_BHHH                       0xA8CAFF00
#define _GT_Y                          0xE2C06300
#define _GT_YH                         0xFFFF9400
#define _GT_YHH                        0xFFFFDE00
#define _GT_P                          0xA86EFC00
#define _GT_PH                         0xFCA5FF00
#define _GT_PHH                        0xFFF7FF00
#define _GT_W                          0xFFFFFF00
#define _GT_L                          0x00000000

#define _GAME_TEXT_h                   0xD8931800
#define _GAME_TEXT_hh                  0xFFFF3600
#define _GAME_TEXT_x                   0x90621000
#define _GAME_TEXT_xh                  0xD8931800
#define _GAME_TEXT_xhh                 0xFFFF3600
#define _GAME_TEXT_r                   0xB4191D00
#define _GAME_TEXT_rh                  0xFF252B00
#define _GAME_TEXT_rhh                 0xFF374000
#define _GAME_TEXT_rhhh                0xFF526000
#define _GAME_TEXT_rhhhh               0xFF7B9000
#define _GAME_TEXT_rhhhhh              0xFFB8D800
#define _GAME_TEXT_g                   0x36682C00
#define _GAME_TEXT_gh                  0x519C4200
#define _GAME_TEXT_ghh                 0x79EA6300
#define _GAME_TEXT_ghhh                0xB5FF9400
#define _GAME_TEXT_ghhhh               0xFFFFDE00
#define _GAME_TEXT_b                   0x323C7F00
#define _GAME_TEXT_bh                  0x4B5ABE00
#define _GAME_TEXT_bhh                 0x7087FF00
#define _GAME_TEXT_bhhh                0xA8CAFF00
#define _GAME_TEXT_y                   0xE2C06300
#define _GAME_TEXT_yh                  0xFFFF9400
#define _GAME_TEXT_yhh                 0xFFFFDE00
#define _GAME_TEXT_p                   0xA86EFC00
#define _GAME_TEXT_ph                  0xFCA5FF00
#define _GAME_TEXT_phh                 0xFFF7FF00
#define _GAME_TEXT_w                   0xFFFFFF00
#define _GAME_TEXT_l                   0x00000000

#define _GAMETEXT_h                    0xD8931800
#define _GAMETEXT_hh                   0xFFFF3600
#define _GAMETEXT_x                    0x90621000
#define _GAMETEXT_xh                   0xD8931800
#define _GAMETEXT_xhh                  0xFFFF3600
#define _GAMETEXT_r                    0xB4191D00
#define _GAMETEXT_rh                   0xFF252B00
#define _GAMETEXT_rhh                  0xFF374000
#define _GAMETEXT_rhhh                 0xFF526000
#define _GAMETEXT_rhhhh                0xFF7B9000
#define _GAMETEXT_rhhhhh               0xFFB8D800
#define _GAMETEXT_g                    0x36682C00
#define _GAMETEXT_gh                   0x519C4200
#define _GAMETEXT_ghh                  0x79EA6300
#define _GAMETEXT_ghhh                 0xB5FF9400
#define _GAMETEXT_ghhhh                0xFFFFDE00
#define _GAMETEXT_b                    0x323C7F00
#define _GAMETEXT_bh                   0x4B5ABE00
#define _GAMETEXT_bhh                  0x7087FF00
#define _GAMETEXT_bhhh                 0xA8CAFF00
#define _GAMETEXT_y                    0xE2C06300
#define _GAMETEXT_yh                   0xFFFF9400
#define _GAMETEXT_yhh                  0xFFFFDE00
#define _GAMETEXT_p                    0xA86EFC00
#define _GAMETEXT_ph                   0xFCA5FF00
#define _GAMETEXT_phh                  0xFFF7FF00
#define _GAMETEXT_w                    0xFFFFFF00
#define _GAMETEXT_l                    0x00000000

#define _GT_h                          0xD8931800
#define _GT_hh                         0xFFFF3600
#define _GT_x                          0x90621000
#define _GT_xh                         0xD8931800
#define _GT_xhh                        0xFFFF3600
#define _GT_r                          0xB4191D00
#define _GT_rh                         0xFF252B00
#define _GT_rhh                        0xFF374000
#define _GT_rhhh                       0xFF526000
#define _GT_rhhhh                      0xFF7B9000
#define _GT_rhhhhh                     0xFFB8D800
#define _GT_g                          0x36682C00
#define _GT_gh                         0x519C4200
#define _GT_ghh                        0x79EA6300
#define _GT_ghhh                       0xB5FF9400
#define _GT_ghhhh                      0xFFFFDE00
#define _GT_b                          0x323C7F00
#define _GT_bh                         0x4B5ABE00
#define _GT_bhh                        0x7087FF00
#define _GT_bhhh                       0xA8CAFF00
#define _GT_y                          0xE2C06300
#define _GT_yh                         0xFFFF9400
#define _GT_yhh                        0xFFFFDE00
#define _GT_p                          0xA86EFC00
#define _GT_ph                         0xFCA5FF00
#define _GT_phh                        0xFFF7FF00
#define _GT_w                          0xFFFFFF00
#define _GT_l                          0x00000000

// String versions.
#define GT__                {906210}
#define GT_H                {D89318}
#define GT_HH               {FFFF36}
#define GT_X                {906210}
#define GT_XH               {D89318}
#define GT_XHH              {FFFF36}
#define GT_R                {B4191D}
#define GT_RH               {FF252B}
#define GT_RHH              {FF3740}
#define GT_RHHH             {FF5260}
#define GT_RHHHH            {FF7B90}
#define GT_RHHHHH           {FFB8D8}
#define GT_G                {36682C}
#define GT_GH               {519C42}
#define GT_GHH              {79EA63}
#define GT_GHHH             {B5FF94}
#define GT_GHHHH            {FFFFDE}
#define GT_B                {323C7F}
#define GT_BH               {4B5ABE}
#define GT_BHH              {7087FF}
#define GT_BHHH             {A8CAFF}
#define GT_Y                {E2C063}
#define GT_YH               {FFFF94}
#define GT_YHH              {FFFFDE}
#define GT_P                {A86EFC}
#define GT_PH               {FCA5FF}
#define GT_PHH              {FFF7FF}
#define GT_W                {FFFFFF}
#define GT_L                {000000}
#define GT_h                {D89318}
#define GT_hh               {FFFF36}
#define GT_x                {906210}
#define GT_xh               {D89318}
#define GT_xhh              {FFFF36}
#define GT_r                {B4191D}
#define GT_rh               {FF252B}
#define GT_rhh              {FF3740}
#define GT_rhhh             {FF5260}
#define GT_rhhhh            {FF7B90}
#define GT_rhhhhh           {FFB8D8}
#define GT_g                {36682C}
#define GT_gh               {519C42}
#define GT_ghh              {79EA63}
#define GT_ghhh             {B5FF94}
#define GT_ghhhh            {FFFFDE}
#define GT_b                {323C7F}
#define GT_bh               {4B5ABE}
#define GT_bhh              {7087FF}
#define GT_bhhh             {A8CAFF}
#define GT_y                {E2C063}
#define GT_yh               {FFFF94}
#define GT_yhh              {FFFFDE}
#define GT_p                {A86EFC}
#define GT_ph               {FCA5FF}
#define GT_phh              {FFF7FF}
#define GT_w                {FFFFFF}
#define GT_l                {000000}
#define GAMETEXT_                 {906210}
#define GAMETEXT_H                {D89318}
#define GAMETEXT_HH               {FFFF36}
#define GAMETEXT_X                {906210}
#define GAMETEXT_XH               {D89318}
#define GAMETEXT_XHH              {FFFF36}
#define GAMETEXT_R                {B4191D}
#define GAMETEXT_RH               {FF252B}
#define GAMETEXT_RHH              {FF3740}
#define GAMETEXT_RHHH             {FF5260}
#define GAMETEXT_RHHHH            {FF7B90}
#define GAMETEXT_RHHHHH           {FFB8D8}
#define GAMETEXT_G                {36682C}
#define GAMETEXT_GH               {519C42}
#define GAMETEXT_GHH              {79EA63}
#define GAMETEXT_GHHH             {B5FF94}
#define GAMETEXT_GHHHH            {FFFFDE}
#define GAMETEXT_B                {323C7F}
#define GAMETEXT_BH               {4B5ABE}
#define GAMETEXT_BHH              {7087FF}
#define GAMETEXT_BHHH             {A8CAFF}
#define GAMETEXT_Y                {E2C063}
#define GAMETEXT_YH               {FFFF94}
#define GAMETEXT_YHH              {FFFFDE}
#define GAMETEXT_P                {A86EFC}
#define GAMETEXT_PH               {FCA5FF}
#define GAMETEXT_PHH              {FFF7FF}
#define GAMETEXT_W                {FFFFFF}
#define GAMETEXT_L                {000000}
#define GAMETEXT_h                {D89318}
#define GAMETEXT_hh               {FFFF36}
#define GAMETEXT_x                {906210}
#define GAMETEXT_xh               {D89318}
#define GAMETEXT_xhh              {FFFF36}
#define GAMETEXT_r                {B4191D}
#define GAMETEXT_rh               {FF252B}
#define GAMETEXT_rhh              {FF3740}
#define GAMETEXT_rhhh             {FF5260}
#define GAMETEXT_rhhhh            {FF7B90}
#define GAMETEXT_rhhhhh           {FFB8D8}
#define GAMETEXT_g                {36682C}
#define GAMETEXT_gh               {519C42}
#define GAMETEXT_ghh              {79EA63}
#define GAMETEXT_ghhh             {B5FF94}
#define GAMETEXT_ghhhh            {FFFFDE}
#define GAMETEXT_b                {323C7F}
#define GAMETEXT_bh               {4B5ABE}
#define GAMETEXT_bhh              {7087FF}
#define GAMETEXT_bhhh             {A8CAFF}
#define GAMETEXT_y                {E2C063}
#define GAMETEXT_yh               {FFFF94}
#define GAMETEXT_yhh              {FFFFDE}
#define GAMETEXT_p                {A86EFC}
#define GAMETEXT_ph               {FCA5FF}
#define GAMETEXT_phh              {FFF7FF}
#define GAMETEXT_w                {FFFFFF}
#define GAMETEXT_l                {000000}
#define GAME_TEXT_                 {906210}
#define GAME_TEXT_H                {D89318}
#define GAME_TEXT_HH               {FFFF36}
#define GAME_TEXT_X                {906210}
#define GAME_TEXT_XH               {D89318}
#define GAME_TEXT_XHH              {FFFF36}
#define GAME_TEXT_R                {B4191D}
#define GAME_TEXT_RH               {FF252B}
#define GAME_TEXT_RHH              {FF3740}
#define GAME_TEXT_RHHH             {FF5260}
#define GAME_TEXT_RHHHH            {FF7B90}
#define GAME_TEXT_RHHHHH           {FFB8D8}
#define GAME_TEXT_G                {36682C}
#define GAME_TEXT_GH               {519C42}
#define GAME_TEXT_GHH              {79EA63}
#define GAME_TEXT_GHHH             {B5FF94}
#define GAME_TEXT_GHHHH            {FFFFDE}
#define GAME_TEXT_B                {323C7F}
#define GAME_TEXT_BH               {4B5ABE}
#define GAME_TEXT_BHH              {7087FF}
#define GAME_TEXT_BHHH             {A8CAFF}
#define GAME_TEXT_Y                {E2C063}
#define GAME_TEXT_YH               {FFFF94}
#define GAME_TEXT_YHH              {FFFFDE}
#define GAME_TEXT_P                {A86EFC}
#define GAME_TEXT_PH               {FCA5FF}
#define GAME_TEXT_PHH              {FFF7FF}
#define GAME_TEXT_W                {FFFFFF}
#define GAME_TEXT_L                {000000}
#define GAME_TEXT_h                {D89318}
#define GAME_TEXT_hh               {FFFF36}
#define GAME_TEXT_x                {906210}
#define GAME_TEXT_xh               {D89318}
#define GAME_TEXT_xhh              {FFFF36}
#define GAME_TEXT_r                {B4191D}
#define GAME_TEXT_rh               {FF252B}
#define GAME_TEXT_rhh              {FF3740}
#define GAME_TEXT_rhhh             {FF5260}
#define GAME_TEXT_rhhhh            {FF7B90}
#define GAME_TEXT_rhhhhh           {FFB8D8}
#define GAME_TEXT_g                {36682C}
#define GAME_TEXT_gh               {519C42}
#define GAME_TEXT_ghh              {79EA63}
#define GAME_TEXT_ghhh             {B5FF94}
#define GAME_TEXT_ghhhh            {FFFFDE}
#define GAME_TEXT_b                {323C7F}
#define GAME_TEXT_bh               {4B5ABE}
#define GAME_TEXT_bhh              {7087FF}
#define GAME_TEXT_bhhh             {A8CAFF}
#define GAME_TEXT_y                {E2C063}
#define GAME_TEXT_yh               {FFFF94}
#define GAME_TEXT_yhh              {FFFFDE}
#define GAME_TEXT_p                {A86EFC}
#define GAME_TEXT_ph               {FCA5FF}
#define GAME_TEXT_phh              {FFF7FF}
#define GAME_TEXT_w                {FFFFFF}
#define GAME_TEXT_l                {000000}

// Clever versions.
#define __hGT_                 906210
#define __hGT_h                D89318
#define __hGT_hh               FFFF36
#define __hGT_x                906210
#define __hGT_xh               D89318
#define __hGT_xhh              FFFF36
#define __hGT_r                B4191D
#define __hGT_rh               FF252B
#define __hGT_rhh              FF3740
#define __hGT_rhhh             FF5260
#define __hGT_rhhhh            FF7B90
#define __hGT_rhhhhh           FFB8D8
#define __hGT_g                36682C
#define __hGT_gh               519C42
#define __hGT_ghh              79EA63
#define __hGT_ghhh             B5FF94
#define __hGT_ghhhh            FFFFDE
#define __hGT_b                323C7F
#define __hGT_bh               4B5ABE
#define __hGT_bhh              7087FF
#define __hGT_bhhh             A8CAFF
#define __hGT_y                E2C063
#define __hGT_yh               FFFF94
#define __hGT_yhh              FFFFDE
#define __hGT_p                A86EFC
#define __hGT_ph               FCA5FF
#define __hGT_phh              FFF7FF
#define __hGT_w                FFFFFF
#define __hGT_l                000000

#define __@GT_                 0x906210AA
#define __@GT_h                0xD89318AA
#define __@GT_hh               0xFFFF36AA
#define __@GT_x                0x906210AA
#define __@GT_xh               0xD89318AA
#define __@GT_xhh              0xFFFF36AA
#define __@GT_r                0xB4191DAA
#define __@GT_rh               0xFF252BAA
#define __@GT_rhh              0xFF3740AA
#define __@GT_rhhh             0xFF5260AA
#define __@GT_rhhhh            0xFF7B90AA
#define __@GT_rhhhhh           0xFFB8D8AA
#define __@GT_g                0x36682CAA
#define __@GT_gh               0x519C42AA
#define __@GT_ghh              0x79EA63AA
#define __@GT_ghhh             0xB5FF94AA
#define __@GT_ghhhh            0xFFFFDEAA
#define __@GT_b                0x323C7FAA
#define __@GT_bh               0x4B5ABEAA
#define __@GT_bhh              0x7087FFAA
#define __@GT_bhhh             0xA8CAFFAA
#define __@GT_y                0xE2C063AA
#define __@GT_yh               0xFFFF94AA
#define __@GT_yhh              0xFFFFDEAA
#define __@GT_p                0xA86EFCAA
#define __@GT_ph               0xFCA5FFAA
#define __@GT_phh              0xFFF7FFAA
#define __@GT_w                0xFFFFFFAA
#define __@GT_l                0x000000AA

#define ___GT_                 0x90621000
#define ___GT_h                0xD8931800
#define ___GT_hh               0xFFFF3600
#define ___GT_x                0x90621000
#define ___GT_xh               0xD8931800
#define ___GT_xhh              0xFFFF3600
#define ___GT_r                0xB4191D00
#define ___GT_rh               0xFF252B00
#define ___GT_rhh              0xFF374000
#define ___GT_rhhh             0xFF526000
#define ___GT_rhhhh            0xFF7B9000
#define ___GT_rhhhhh           0xFFB8D800
#define ___GT_g                0x36682C00
#define ___GT_gh               0x519C4200
#define ___GT_ghh              0x79EA6300
#define ___GT_ghhh             0xB5FF9400
#define ___GT_ghhhh            0xFFFFDE00
#define ___GT_b                0x323C7F00
#define ___GT_bh               0x4B5ABE00
#define ___GT_bhh              0x7087FF00
#define ___GT_bhhh             0xA8CAFF00
#define ___GT_y                0xE2C06300
#define ___GT_yh               0xFFFF9400
#define ___GT_yhh              0xFFFFDE00
#define ___GT_p                0xA86EFC00
#define ___GT_ph               0xFCA5FF00
#define ___GT_phh              0xFFF7FF00
#define ___GT_w                0xFFFFFF00
#define ___GT_l                0x00000000

