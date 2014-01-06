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
	1.1
Changelog:
	06/01/14:
		Used search hierarchy for greater speed.
	14/04/12:
		Added pre-cached values from Slice to improve compilation speed.
	29/11/10:
		Added the ability to use "X11" prefixes in strings.
		Added colourspace resolution for converting {FF0000} to ~r~.
	25/11/10:
		First version.
\**--------------------------------------------------------------------------**/

// These magic "&" numbers were generated automagically by scanning the
// whole set of colours repeatedly with different 5-bit masks
// (determined to be closest to the square root of the number of
// colours) to find the ones that gave the best distribution of colours
// per case.  The "& 0x01" splits the list almost perfectly in half.
// Go to line 1156 for the other half's start.
if (hash & 0x01)
{
	switch (hash & 0x02480120)
	{
		case 0x00000000:
			switch (hash)
			{
				case 0x8832925F: return 0xF5F5F500 | alpha;
				case 0x3C27AA5B: return 0x19197000 | alpha;
				case 0x7D027E1F: return 0xEEE8AA00 | alpha;
				case 0x048194D3: return 0xFFFFE000 | alpha;
				case 0x2CA19613: return 0x6959CD00 | alpha;
				case 0xFCB72CD1: return 0xB2DFEE00 | alpha;
				case 0xAC802C5F: return 0x8DEEEE00 | alpha;
				case 0x34055285: return 0x528B8B00 | alpha;
				case 0x24A65A55: return 0x76EEC600 | alpha;
				case 0x9410D819: return 0xC1FFC100 | alpha;
				case 0xF0373283: return 0x9AFF9A00 | alpha;
				case 0xBDA4CE87: return 0x76EE0000 | alpha;
				case 0x4C859499: return 0xCDC67300 | alpha;
				case 0x8133620F: return 0xEEB42200 | alpha;
				case 0x99B0E843: return 0x8B3E2F00 | alpha;
				case 0x25A7EC87: return 0xFF450000 | alpha;
				case 0x0CB5C68D: return 0xFF6EB400 | alpha;
				case 0x54A4741F: return 0xEE3A8C00 | alpha;
				case 0x2C354ECD: return 0xFFBBFF00 | alpha;
				case 0xC883A04F: return 0x8B7B8B00 | alpha;
				case 0x2DB7A29B: return 0x3B3B3B00 | alpha;
				case 0xFC15A495: return 0x4D4D4D00 | alpha;
				case 0x4D83FA19: return 0x4F4F4F00 | alpha;
				case 0x2931825B: return 0x69696900 | alpha;
				case 0xEC22C4DD: return 0x87878700 | alpha;
				case 0x24B5F81F: return 0xC4C4C400 | alpha;
				case 0x88A2B083: return 0xD9D9D900 | alpha;
				case 0x74056E85: return 0xE0E0E000 | alpha;
				case 0x3535C805: return 0xF5F5F500 | alpha;
			}
		case 0x00000020:
			switch (hash)
			{
				case 0xA533943F: return 0xFFDEAD00 | alpha;
				case 0x4CA0AE65: return 0xF0F8FF00 | alpha;
				case 0x0CB28427: return 0x77889900 | alpha;
				case 0x4DB2D2FF: return 0xADD8E600 | alpha;
				case 0x1192806F: return 0xDB709300 | alpha;
				case 0x2D163CE1: return 0x3A5FCD00 | alpha;
				case 0xB0830EAF: return 0x009ACD00 | alpha;
				case 0x3D36E83D: return 0xB9D3EE00 | alpha;
				case 0xC1B7C46D: return 0xCAE1FF00 | alpha;
				case 0xA53548AF: return 0xA2B5CD00 | alpha;
				case 0x84A2DC75: return 0xB4CDCD00 | alpha;
				case 0x998112E3: return 0x8DEEEE00 | alpha;
				case 0xC002B829: return 0x698B2200 | alpha;
				case 0xC0315423: return 0xBCEE6800 | alpha;
				case 0x6C965839: return 0xEEE68500 | alpha;
				case 0x013468B3: return 0xFFA54F00 | alpha;
				case 0x5CB7266F: return 0x8B5A0000 | alpha;
				case 0x01343EAB: return 0xFF000000 | alpha;
				case 0x2526F22D: return 0xFF00FF00 | alpha;
				case 0x01837E71: return 0x8B668B00 | alpha;
				case 0x1506006B: return 0xD15FEE00 | alpha;
				case 0x5D13026B: return 0x551A8B00 | alpha;
				case 0x34A4F2F9: return 0x29292900 | alpha;
				case 0xCC11F039: return 0x42424200 | alpha;
				case 0x3997A63F: return 0x94949400 | alpha;
				case 0x6891ECE3: return 0x94949400 | alpha;
				case 0x0C33887D: return 0xCCCCCC00 | alpha;
				case 0x3C231863: return 0xE3E3E300 | alpha;
			}
		case 0x00000100:
			switch (hash)
			{
				case 0xA087FD85: return 0xF8F8FF00 | alpha;
				case 0xF0A6258D: return 0xFFF0F500 | alpha;
				case 0xC1A6B3C7: return 0x6495ED00 | alpha;
				case 0x00153147: return 0x0000FF00 | alpha;
				case 0x00147F05: return 0xFFD70000 | alpha;
				case 0x7D05E1DF: return 0xB8860B00 | alpha;
				case 0x29A6E191: return 0xD2691E00 | alpha;
				case 0x59864357: return 0xA020F000 | alpha;
				case 0x7836DFD3: return 0x8B795E00 | alpha;
				case 0x7996BF4B: return 0xBCD2EE00 | alpha;
				case 0x3087B717: return 0x98F5FF00 | alpha;
				case 0x7037DD01: return 0x528B8B00 | alpha;
				case 0xBD84DF43: return 0x8DEEEE00 | alpha;
				case 0x10943515: return 0x00EE7600 | alpha;
				case 0xC135D5DF: return 0xCAFF7000 | alpha;
				case 0x9194FB45: return 0x6E8B3D00 | alpha;
				case 0x71B17D07: return 0xEEDC8200 | alpha;
				case 0xB93107C5: return 0xFFC1C100 | alpha;
				case 0x08379B41: return 0xEE2C2C00 | alpha;
				case 0x8D23E14F: return 0xEE760000 | alpha;
				case 0x01824785: return 0x8B636C00 | alpha;
				case 0x1D25A5DB: return 0x8B5F6500 | alpha;
				case 0x3C168DC1: return 0xEE799F00 | alpha;
				case 0x2DB79197: return 0x3B3B3B00 | alpha;
				case 0xFC15B599: return 0x4D4D4D00 | alpha;
				case 0x4D83E915: return 0x4F4F4F00 | alpha;
				case 0x29317157: return 0x69696900 | alpha;
				case 0xEC22B3D9: return 0x87878700 | alpha;
				case 0x6891DBDF: return 0x94949400 | alpha;
				case 0x3997B743: return 0x94949400 | alpha;
				case 0x35119703: return 0xC2C2C200 | alpha;
				case 0x74055D81: return 0xE0E0E000 | alpha;
				case 0x3535B701: return 0xF5F5F500 | alpha;
				case 0xCC971D93: return 0xA9A9A900 | alpha;
			}
		case 0x00000120:
			switch (hash)
			{
				case 0x64A333B7: return 0xFAEBD700 | alpha;
				case 0x00202BBD: return 0x00008000 | alpha;
				case 0x1D86A77F: return 0x6A5ACD00 | alpha;
				case 0x7587EDE1: return 0xE0FFFF00 | alpha;
				case 0x80B10935: return 0xEEDD8200 | alpha;
				case 0x9CB719B3: return 0x8B451300 | alpha;
				case 0x30013BAB: return 0xE9967A00 | alpha;
				case 0x00B0F3E9: return 0xEEEEE000 | alpha;
				case 0x2C30EBB7: return 0x0000FF00 | alpha;
				case 0xF9B769BF: return 0x8DEEEE00 | alpha;
				case 0xC58397F3: return 0x7FFFD400 | alpha;
				case 0x31A53F3B: return 0x8B864E00 | alpha;
				case 0xA5861567: return 0x8B8B7A00 | alpha;
				case 0x2C303975: return 0xFFD70000 | alpha;
				case 0xA434E1B1: return 0x8B650800 | alpha;
				case 0xCD112DA1: return 0x8B3A3A00 | alpha;
				case 0xACA6EFB7: return 0xFFD39B00 | alpha;
				case 0x3011B96B: return 0xCDBA9600 | alpha;
				case 0xE930F97B: return 0xCD705400 | alpha;
				case 0x2C3417E1: return 0xFFB5C500 | alpha;
				case 0xE9322BBD: return 0xCD299000 | alpha;
				case 0x34A503FD: return 0x29292900 | alpha;
				case 0xCC12013D: return 0x42424200 | alpha;
				case 0x351185FF: return 0xC2C2C200 | alpha;
				case 0x24B60923: return 0xC4C4C400 | alpha;
				case 0x0C337779: return 0xCCCCCC00 | alpha;
				case 0x88A29F7F: return 0xD9D9D900 | alpha;
				case 0x3C232967: return 0xE3E3E300 | alpha;
			}
		case 0x00080000:
			switch (hash)
			{
				case 0x592E484D: return 0x2F4F4F00 | alpha;
				case 0x452B9C91: return 0x556B2F00 | alpha;
				case 0x4C98E2D7: return 0x6B8E2300 | alpha;
				case 0x0019945D: return 0xDDA0DD00 | alpha;
				case 0x15AE620D: return 0x00688B00 | alpha;
				case 0x20AC0C13: return 0xE0FFFF00 | alpha;
				case 0x140E8815: return 0x76EEC600 | alpha;
				case 0xAD0CFC47: return 0x76EE0000 | alpha;
				case 0x000A1A93: return 0xFFA54F00 | alpha;
				case 0x018D3E15: return 0x8B5A2B00 | alpha;
				case 0x0009F08B: return 0xFF000000 | alpha;
				case 0x018D140D: return 0x8B000000 | alpha;
				case 0x341FB243: return 0x8B0A5000 | alpha;
				case 0xE539704F: return 0xCD609000 | alpha;
				case 0xBCBC989D: return 0xFF82AB00 | alpha;
				case 0x0D88B04B: return 0xCD69C900 | alpha;
				case 0x5CAAAAC9: return 0xAB82FF00 | alpha;
				case 0x311C3ACB: return 0x0D0D0D00 | alpha;
				case 0xB0AB8EDF: return 0x30303000 | alpha;
				case 0x290D4055: return 0x36363600 | alpha;
				case 0x34A8E8DB: return 0x8A8A8A00 | alpha;
				case 0x200BA6DD: return 0x91919100 | alpha;
				case 0x39BBE845: return 0xC7C7C700 | alpha;
				case 0xBC8B9283: return 0xE3E3E300 | alpha;
				case 0x308B76C3: return 0xF0F0F000 | alpha;
			}
		case 0x00080020:
			switch (hash)
			{
				case 0x743D3E33: return 0xFDF5E600 | alpha;
				case 0xE11B3467: return 0x0000CD00 | alpha;
				case 0xFD9D16AD: return 0xCD5C5C00 | alpha;
				case 0x2D1B04EB: return 0xE9967A00 | alpha;
				case 0x2C9F22BD: return 0xFF8C0000 | alpha;
				case 0x158DDA3F: return 0xFFF0F500 | alpha;
				case 0xC48AD0E1: return 0xB9D3EE00 | alpha;
				case 0xC909046D: return 0xCAE1FF00 | alpha;
				case 0x91A8D663: return 0x7CCD7C00 | alpha;
				case 0x013A8EEF: return 0x8B450000 | alpha;
				case 0x5CB99661: return 0x8B225200 | alpha;
				case 0x299CA869: return 0x8968CD00 | alpha;
				case 0x019BE82B: return 0x0D0D0D00 | alpha;
				case 0x3C8FBC6D: return 0x14141400 | alpha;
				case 0x98290E39: return 0x38383800 | alpha;
				case 0xE0AF3237: return 0x3B3B3B00 | alpha;
				case 0x1498363F: return 0x45454500 | alpha;
				case 0x301ED2B9: return 0x57575700 | alpha;
				case 0xD0BC527F: return 0x75757500 | alpha;
				case 0x500F6C3D: return 0x9C9C9C00 | alpha;
				case 0x6D3C3E25: return 0xC7C7C700 | alpha;
				case 0x54B9AC7B: return 0xCFCFCF00 | alpha;
				case 0x401C6A7D: return 0xD6D6D600 | alpha;
				case 0xA40922E1: return 0xEBEBEB00 | alpha;
			}
		case 0x00080100:
			switch (hash)
			{
				case 0xEDBE3993: return 0xFFEFD500 | alpha;
				case 0x753F89CB: return 0xFFEBCD00 | alpha;
				case 0x1D0B6551: return 0xFAFAD200 | alpha;
				case 0xD1191D81: return 0xFFA07A00 | alpha;
				case 0x592A675B: return 0xFFA50000 | alpha;
				case 0x980FF1CB: return 0x8B837800 | alpha;
				case 0x09AD2BD5: return 0xFFF8DC00 | alpha;
				case 0x993B9D59: return 0x838B8B00 | alpha;
				case 0xE50DF74F: return 0x1874CD00 | alpha;
				case 0x710F6703: return 0x6C7B8B00 | alpha;
				case 0x05BACF05: return 0xEEDC8200 | alpha;
				case 0x25AB318B: return 0xFFFF0000 | alpha;
				case 0x000B3355: return 0xCD853F00 | alpha;
				case 0xE90D7B05: return 0xFF450000 | alpha;
				case 0x000B094D: return 0xCD000000 | alpha;
				case 0xE52C1949: return 0xEE7AE900 | alpha;
				case 0xBDAFC30B: return 0x8B478900 | alpha;
				case 0x8C0F5789: return 0xAB82FF00 | alpha;
				case 0x311C29C7: return 0x0D0D0D00 | alpha;
				case 0xB0AB7DDB: return 0x30303000 | alpha;
				case 0x290D5159: return 0x36363600 | alpha;
				case 0x00BFF5D7: return 0x7F7F7F00 | alpha;
				case 0x34A8F9DF: return 0x8A8A8A00 | alpha;
				case 0x39BBD741: return 0xC7C7C700 | alpha;
				case 0x401C7B81: return 0xD6D6D600 | alpha;
				case 0xBC8BA387: return 0xE3E3E300 | alpha;
				case 0xA40911DD: return 0xEBEBEB00 | alpha;
				case 0x7D9E7117: return 0xA9A9A900 | alpha;
			}
		case 0x00080120:
			switch (hash)
			{
				case 0xFCA9ADE3: return 0xDCDCDC00 | alpha;
				case 0x85BFABFF: return 0xF5FFFA00 | alpha;
				case 0xCC1A576B: return 0x70809000 | alpha;
				case 0x60184B29: return 0xD3D3D300 | alpha;
				case 0x350DDBE1: return 0x20B2AA00 | alpha;
				case 0x553D01FF: return 0x20B2AA00 | alpha;
				case 0x4C883DB5: return 0x7FFF0000 | alpha;
				case 0x8839D1F7: return 0x6B8E2300 | alpha;
				case 0x001DE9BB: return 0xCD853F00 | alpha;
				case 0x00185D71: return 0xFFC0CB00 | alpha;
				case 0xCC8A2969: return 0xFFB6C100 | alpha;
				case 0x10BC313B: return 0xCDB79E00 | alpha;
				case 0xB09AEF63: return 0xEECBAD00 | alpha;
				case 0x2D1819F7: return 0x4F94CD00 | alpha;
				case 0xC12EF529: return 0x8DB6CD00 | alpha;
				case 0xCC9FF323: return 0x6C7B8B00 | alpha;
				case 0x2DA8D73B: return 0x7AC5CD00 | alpha;
				case 0x712CD773: return 0x8B650800 | alpha;
				case 0xB4BC11F9: return 0xCDAA7D00 | alpha;
				case 0x10AD4FB9: return 0xFF8C6900 | alpha;
				case 0x10AE81FB: return 0xFF34B300 | alpha;
				case 0xFD1EF92B: return 0xBF3EFF00 | alpha;
				case 0x019BD727: return 0x0D0D0D00 | alpha;
				case 0x3C8FAB69: return 0x14141400 | alpha;
				case 0x9828FD35: return 0x38383800 | alpha;
				case 0xE0AF433B: return 0x3B3B3B00 | alpha;
				case 0x1498253B: return 0x45454500 | alpha;
				case 0x301EE3BD: return 0x57575700 | alpha;
				case 0xD0BC417B: return 0x75757500 | alpha;
				case 0x200BB7E1: return 0x91919100 | alpha;
				case 0x500F5B39: return 0x9C9C9C00 | alpha;
				case 0x6D3C2D21: return 0xC7C7C700 | alpha;
				case 0x54B9BD7F: return 0xCFCFCF00 | alpha;
				case 0x308B65BF: return 0xF0F0F000 | alpha;
			}
		case 0x00400000:
			switch (hash)
			{
				case 0x35F6705F: return 0xFFDEAD00 | alpha;
				case 0x7CD61441: return 0x7B68EE00 | alpha;
				case 0x30C62C41: return 0xFFA07A00 | alpha;
				case 0x2C70FAD9: return 0xCDC9C900 | alpha;
				case 0xF951DEC9: return 0xEEDFCC00 | alpha;
				case 0x15608A01: return 0xEECBAD00 | alpha;
				case 0x40C7AE55: return 0xEEE8CD00 | alpha;
				case 0x9972A453: return 0x6959CD00 | alpha;
				case 0x91D228DF: return 0x4876FF00 | alpha;
				case 0x28C12E55: return 0xB4CDCD00 | alpha;
				case 0x01719EDD: return 0x00CDCD00 | alpha;
				case 0x40F0225D: return 0xB4EEB400 | alpha;
				case 0xF95662C9: return 0xB3EE3A00 | alpha;
				case 0x9076BC1F: return 0x8B3A3A00 | alpha;
				case 0xECF5780F: return 0xEE794200 | alpha;
				case 0x4DD4C059: return 0xCDAA7D00 | alpha;
				case 0x6CF7A419: return 0xEE3B3B00 | alpha;
				case 0xD8517EDB: return 0xEE826200 | alpha;
				case 0xF0E28C51: return 0x8B450000 | alpha;
				case 0x2C74069F: return 0xEE128900 | alpha;
				case 0x1942940D: return 0xFF00FF00 | alpha;
				case 0xBDD6C68D: return 0xEE00EE00 | alpha;
				case 0x2C71D885: return 0x08080800 | alpha;
				case 0x35C68C0D: return 0x12121200 | alpha;
				case 0x7CC28AD7: return 0x26262600 | alpha;
				case 0xC9F3221F: return 0x5C5C5C00 | alpha;
				case 0x39738641: return 0x61616100 | alpha;
				case 0x00C006DB: return 0x7F7F7F00 | alpha;
				case 0x2955A259: return 0x9C9C9C00 | alpha;
				case 0x39533A1D: return 0xBDBDBD00 | alpha;
				case 0xF577565D: return 0xEDEDED00 | alpha;
				case 0x39E00843: return 0xFAFAFA00 | alpha;
				case 0x4DE4205D: return 0x8B008B00 | alpha;
			}
		case 0x00400020:
			switch (hash)
			{
				case 0x55C7A2F1: return 0x48D1CC00 | alpha;
				case 0x19544AB7: return 0x32CD3200 | alpha;
				case 0x5054803D: return 0xA0522D00 | alpha;
				case 0xBD75CE3D: return 0xFF8C0000 | alpha;
				case 0xF177EC79: return 0xBA55D300 | alpha;
				case 0x0176C879: return 0xCDC9C900 | alpha;
				case 0x8857B8E9: return 0x8B837800 | alpha;
				case 0x3075B2AB: return 0xCDCDC100 | alpha;
				case 0x916730B1: return 0x6959CD00 | alpha;
				case 0x3CD5FC6B: return 0x1E90FF00 | alpha;
				case 0xF97380E3: return 0x00C5CD00 | alpha;
				case 0x6552E2F7: return 0x008B4500 | alpha;
				case 0x9D621A21: return 0xA2CD5A00 | alpha;
				case 0x81774CE7: return 0x8B8B7A00 | alpha;
				case 0x1CF058AF: return 0xCD9B1D00 | alpha;
				case 0x94E50AA5: return 0x8B451300 | alpha;
				case 0x84412EE1: return 0xFF303000 | alpha;
				case 0x4CE6E079: return 0xCD333300 | alpha;
				case 0x8D75F473: return 0x8B574200 | alpha;
				case 0x2DC190E7: return 0xFF450000 | alpha;
				case 0x29E66661: return 0x00000000 | alpha;
				case 0x01538627: return 0x03030300 | alpha;
				case 0x0177A625: return 0x08080800 | alpha;
				case 0x01C00829: return 0x12121200 | alpha;
				case 0x01E44A2F: return 0x17171700 | alpha;
				case 0xB555E021: return 0x63636300 | alpha;
				case 0x9CD34E77: return 0x6B6B6B00 | alpha;
				case 0x1942767D: return 0x78787800 | alpha;
				case 0x304314BF: return 0x8A8A8A00 | alpha;
				case 0xD56692BD: return 0xA8A8A800 | alpha;
				case 0x306734BD: return 0xBDBDBD00 | alpha;
				case 0x29605A65: return 0xF7F7F700 | alpha;
				case 0x71E67E63: return 0xFAFAFA00 | alpha;
			}
		case 0x00400100:
			switch (hash)
			{
				case 0x0DC193D7: return 0xFAEBD700 | alpha;
				case 0x1C73D18F: return 0x2F4F4F00 | alpha;
				case 0xAC41774B: return 0x8FBC8F00 | alpha;
				case 0x80575559: return 0xBA55D300 | alpha;
				case 0x20C1B789: return 0xFFFFF000 | alpha;
				case 0x2DC3C713: return 0xE0EEE000 | alpha;
				case 0x6DD38BCD: return 0x87CEFF00 | alpha;
				case 0x55C3038D: return 0x6E7B8B00 | alpha;
				case 0x20E5E943: return 0xBBFFFF00 | alpha;
				case 0xB9E7D783: return 0x00CD0000 | alpha;
				case 0xF5E1EB03: return 0xCD262600 | alpha;
				case 0xA1E2BD13: return 0xEE957200 | alpha;
				case 0x296647C1: return 0xEE128900 | alpha;
				case 0x00E18F03: return 0x8B0A5000 | alpha;
				case 0xD852B11D: return 0xEE30A700 | alpha;
				case 0xF1C63DCF: return 0xCD00CD00 | alpha;
				case 0x41D4F38D: return 0x9A32CD00 | alpha;
				case 0x2C71E989: return 0x08080800 | alpha;
				case 0x35C67B09: return 0x12121200 | alpha;
				case 0x7CC29BDB: return 0x26262600 | alpha;
				case 0xC9F3111B: return 0x5C5C5C00 | alpha;
				case 0xB555CF1D: return 0x63636300 | alpha;
				case 0x19428781: return 0x78787800 | alpha;
				case 0x2955B35D: return 0x9C9C9C00 | alpha;
				case 0xD566A3C1: return 0xA8A8A800 | alpha;
				case 0x306745C1: return 0xBDBDBD00 | alpha;
				case 0x39E01947: return 0xFAFAFA00 | alpha;
				case 0xDCC1494B: return 0x008B8B00 | alpha;
			}
		case 0x00400120:
			switch (hash)
			{
				case 0x95F551A9: return 0x8FBC8F00 | alpha;
				case 0x38752DBD: return 0xDAA52000 | alpha;
				case 0x71624DF3: return 0xFF634700 | alpha;
				case 0xC8E1892F: return 0xFF149300 | alpha;
				case 0x08570B2D: return 0xD0209000 | alpha;
				case 0x01529777: return 0xFFFAFA00 | alpha;
				case 0x7445E721: return 0xFFF5EE00 | alpha;
				case 0x88C74B69: return 0xEEDFCC00 | alpha;
				case 0xC0E343FB: return 0x8B7D6B00 | alpha;
				case 0x50F33B31: return 0x8B795E00 | alpha;
				case 0x99E74B21: return 0x3A5FCD00 | alpha;
				case 0x91D405F5: return 0x63B8FF00 | alpha;
				case 0xD5D501A1: return 0x6C7B8B00 | alpha;
				case 0x08469FEF: return 0xA2B5CD00 | alpha;
				case 0x65D321E1: return 0xBBFFFF00 | alpha;
				case 0x99D713E3: return 0x008B0000 | alpha;
				case 0x95571729: return 0xB3EE3A00 | alpha;
				case 0x58C28BB1: return 0xEEAD0E00 | alpha;
				case 0xB9C1ABE3: return 0xCD5B4500 | alpha;
				case 0x35D6B329: return 0xCD370000 | alpha;
				case 0xB8600B3D: return 0x8B5F6500 | alpha;
				case 0x79739BFF: return 0xEE3A8C00 | alpha;
				case 0x29E67765: return 0x00000000 | alpha;
				case 0x01537523: return 0x03030300 | alpha;
				case 0x0177B729: return 0x08080800 | alpha;
				case 0x01C0192D: return 0x12121200 | alpha;
				case 0x01E4392B: return 0x17171700 | alpha;
				case 0x3973753D: return 0x61616100 | alpha;
				case 0x9CD35F7B: return 0x6B6B6B00 | alpha;
				case 0x304303BB: return 0x8A8A8A00 | alpha;
				case 0x39534B21: return 0xBDBDBD00 | alpha;
				case 0xF5776761: return 0xEDEDED00 | alpha;
				case 0x29604961: return 0xF7F7F700 | alpha;
				case 0x71E68F67: return 0xFAFAFA00 | alpha;
			}
		case 0x00480000:
			switch (hash)
			{
				case 0xC0DEE897: return 0xFFFACD00 | alpha;
				case 0x1DFB4E4D: return 0x4169E100 | alpha;
				case 0x35CE1CD1: return 0x48D1CC00 | alpha;
				case 0x7D7BDC13: return 0xBC8F8F00 | alpha;
				case 0xE868D259: return 0x8A2BE200 | alpha;
				case 0x48DCD097: return 0x8B887800 | alpha;
				case 0x2DF82601: return 0xCDC1C500 | alpha;
				case 0xDC5B14DD: return 0xFFE4E100 | alpha;
				case 0x915D8211: return 0x836FFF00 | alpha;
				case 0x015AEA59: return 0x0000EE00 | alpha;
				case 0x91DDB495: return 0x4F94CD00 | alpha;
				case 0x75E8AE0F: return 0x6CA6CD00 | alpha;
				case 0xA1FC82DB: return 0xB9D3EE00 | alpha;
				case 0xF84C54C5: return 0x7CCD7C00 | alpha;
				case 0x015A3817: return 0xEEC90000 | alpha;
				case 0x98F9EC4F: return 0xEEB42200 | alpha;
				case 0x89488451: return 0x8B691400 | alpha;
				case 0x205DBE49: return 0xFFE7BA00 | alpha;
				case 0xEDCCC8C1: return 0xFF303000 | alpha;
				case 0x015E1683: return 0xEEA9B800 | alpha;
				case 0x30DFA00F: return 0xCD96CD00 | alpha;
				case 0x6C7DA40B: return 0xD15FEE00 | alpha;
				case 0x48D9A8D7: return 0x1C1C1C00 | alpha;
				case 0x915FCCD5: return 0x1F1F1F00 | alpha;
				case 0xC548D0DD: return 0x29292900 | alpha;
				case 0x816CDC19: return 0x59595900 | alpha;
				case 0x2DDBC299: return 0x6E6E6E00 | alpha;
				case 0x34ED6601: return 0x8F8F8F00 | alpha;
				case 0x1DECD8C3: return 0xABABAB00 | alpha;
				case 0x056A581D: return 0xB3B3B300 | alpha;
				case 0xF0CD161F: return 0xBABABA00 | alpha;
				case 0x2979E45F: return 0xCFCFCF00 | alpha;
			}
		case 0x00480020:
			switch (hash)
			{
				case 0x1DCBB0F1: return 0x00640000 | alpha;
				case 0xEDECA4E9: return 0x2E8B5700 | alpha;
				case 0xC44E6263: return 0x00FF7F00 | alpha;
				case 0x2CEF1EA5: return 0xF4A46000 | alpha;
				case 0xE86C0E73: return 0x9400D300 | alpha;
				case 0xE85F9A39: return 0xEED5B700 | alpha;
				case 0x7978123F: return 0xFFF0F500 | alpha;
				case 0xB94C60F9: return 0xC1CDCD00 | alpha;
				case 0x30DB3CF9: return 0x0000CD00 | alpha;
				case 0x99E92837: return 0x4F94CD00 | alpha;
				case 0xF15E5EA1: return 0x00F5FF00 | alpha;
				case 0x597D78E3: return 0x9AFF9A00 | alpha;
				case 0xC068C6E7: return 0x66CD0000 | alpha;
				case 0xED4F60AD: return 0xEEEE0000 | alpha;
				case 0x205812ED: return 0xEEEE0000 | alpha;
				case 0xF8DBBCAF: return 0x8B8B0000 | alpha;
				case 0x30DA8AB7: return 0xCDAD0000 | alpha;
				case 0xD1CB2CB9: return 0x8B735500 | alpha;
				case 0x004CFAA9: return 0xEED8AE00 | alpha;
				case 0x3CD92A7D: return 0xEE3A8C00 | alpha;
				case 0x394F443B: return 0x2E2E2E00 | alpha;
				case 0x34C934FF: return 0x5C5C5C00 | alpha;
				case 0xE559947D: return 0x6E6E6E00 | alpha;
				case 0x34ED54FD: return 0x8F8F8F00 | alpha;
				case 0xA17DB0BD: return 0x9E9E9E00 | alpha;
				case 0x3DFD9C63: return 0xF0F0F000 | alpha;
			}
		case 0x00480100:
			switch (hash)
			{
				case 0xD4CEA703: return 0xCDC5BF00 | alpha;
				case 0x91DB330B: return 0x8B897000 | alpha;
				case 0x35D8E955: return 0x838B8300 | alpha;
				case 0xD97C3501: return 0xCDB7B500 | alpha;
				case 0x017F1B5B: return 0x00008B00 | alpha;
				case 0xE9687713: return 0xB4CDCD00 | alpha;
				case 0x014D6DDB: return 0x00FFFF00 | alpha;
				case 0xAC7B23DB: return 0x9BCD9B00 | alpha;
				case 0x1569831B: return 0x2E8B5700 | alpha;
				case 0xB568B703: return 0xBCEE6800 | alpha;
				case 0xC0DE6BC5: return 0x8B8B7A00 | alpha;
				case 0x017E6919: return 0x8B750000 | alpha;
				case 0xF15C6545: return 0xCD9B9B00 | alpha;
				case 0xB9ECC5CF: return 0xEE794200 | alpha;
				case 0xC57921D1: return 0x8B472600 | alpha;
				case 0x01690D13: return 0xEE9A4900 | alpha;
				case 0x2D5C39D9: return 0xEE3B3B00 | alpha;
				case 0x74EF0D07: return 0x8B362600 | alpha;
				case 0x0168E30B: return 0xEE000000 | alpha;
				case 0x48D997D3: return 0x1C1C1C00 | alpha;
				case 0x915FDDD9: return 0x1F1F1F00 | alpha;
				case 0xC548BFD9: return 0x29292900 | alpha;
				case 0x816CED1D: return 0x59595900 | alpha;
				case 0x2DDBD39D: return 0x6E6E6E00 | alpha;
				case 0x2DFFF39B: return 0xA1A1A100 | alpha;
				case 0x056A4719: return 0xB3B3B300 | alpha;
				case 0xF0CD051B: return 0xBABABA00 | alpha;
				case 0x2979D35B: return 0xCFCFCF00 | alpha;
				case 0x3DFD8B5F: return 0xF0F0F000 | alpha;
			}
		case 0x00480120:
			switch (hash)
			{
				case 0x384FD5A5: return 0xF8F8FF00 | alpha;
				case 0xE1FA3161: return 0x7B68EE00 | alpha;
				case 0x1DFD2B63: return 0x4682B400 | alpha;
				case 0x1DC84D31: return 0x98FB9800 | alpha;
				case 0x1DCD6B61: return 0x7CFC0000 | alpha;
				case 0xE55CBFA9: return 0xFFB6C100 | alpha;
				case 0x7C5B0963: return 0xCDC5BF00 | alpha;
				case 0x41C8DD67: return 0xEEDFCC00 | alpha;
				case 0x607A7DB1: return 0xEECFA100 | alpha;
				case 0x91DBD77F: return 0x3A5FCD00 | alpha;
				case 0x617CC76F: return 0xB2DFEE00 | alpha;
				case 0x2C6BD13D: return 0x00CDCD00 | alpha;
				case 0xF0FF3F7B: return 0x97FFFF00 | alpha;
				case 0x68CAB9F3: return 0x00EE7600 | alpha;
				case 0x9D6C396B: return 0x698B2200 | alpha;
				case 0x2CFAEDF9: return 0xEEE68500 | alpha;
				case 0xD14E5771: return 0xEEAD0E00 | alpha;
				case 0x015899B5: return 0xCD853F00 | alpha;
				case 0xF5CB5F2D: return 0xEE9A0000 | alpha;
				case 0x01586FAD: return 0xCD000000 | alpha;
				case 0x30DE6923: return 0xCD919E00 | alpha;
				case 0x15485DBB: return 0xEEA2AD00 | alpha;
				case 0x1D5D7FFD: return 0x8B5F6500 | alpha;
				case 0x015F4D6F: return 0xEEAEEE00 | alpha;
				case 0x396FA1AB: return 0x7A378B00 | alpha;
				case 0x394F553F: return 0x2E2E2E00 | alpha;
				case 0x34C923FB: return 0x5C5C5C00 | alpha;
				case 0xE5598379: return 0x6E6E6E00 | alpha;
				case 0xA17D9FB9: return 0x9E9E9E00 | alpha;
				case 0x1DECC7BF: return 0xABABAB00 | alpha;
			}
		case 0x02000000:
			switch (hash)
			{
				case 0xAB839497: return 0x32CD3200 | alpha;
				case 0xD713AC95: return 0xFF450000 | alpha;
				case 0xDFA22695: return 0xC1CDC100 | alpha;
				case 0xC6854EDF: return 0xFFE4E100 | alpha;
				case 0x2A120C99: return 0x0000EE00 | alpha;
				case 0x8781BC51: return 0xE0FFFF00 | alpha;
				case 0x03B3EA01: return 0x79CDCD00 | alpha;
				case 0x0AB01899: return 0x4EEE9400 | alpha;
				case 0xFBB6C0C7: return 0xEEDC8200 | alpha;
				case 0x2A115A57: return 0xEEC90000 | alpha;
				case 0xA3B356D1: return 0x8B691400 | alpha;
				case 0x1B17C287: return 0xCD9B9B00 | alpha;
				case 0x0E220C83: return 0xCD661D00 | alpha;
				case 0x2A1538C3: return 0xEEA9B800 | alpha;
				case 0x739436C9: return 0xFF83FA00 | alpha;
				case 0xA316E08B: return 0xBF3EFF00 | alpha;
				case 0x16B70459: return 0x2B2B2B00 | alpha;
				case 0x328624DF: return 0x73737300 | alpha;
				case 0x6AB0CC01: return 0x7A7A7A00 | alpha;
				case 0x9AB4805D: return 0x85858500 | alpha;
				case 0x86173E5F: return 0x8C8C8C00 | alpha;
				case 0xBA00205F: return 0x96969600 | alpha;
				case 0x2E00049F: return 0xA1A1A100 | alpha;
				case 0x2E24249D: return 0xD4D4D400 | alpha;
				case 0x22972A05: return 0xDEDEDE00 | alpha;
				case 0x0A14985B: return 0xE5E5E500 | alpha;
				case 0x5B82DCDB: return 0xE8E8E800 | alpha;
			}
		case 0x02000020:
			switch (hash)
			{
				case 0xCF335C6D: return 0x2F4F4F00 | alpha;
				case 0x02B3A0BB: return 0xF5F5DC00 | alpha;
				case 0xFB30442D: return 0xDB709300 | alpha;
				case 0x76815477: return 0x9370DB00 | alpha;
				case 0x1281AA25: return 0x8B776500 | alpha;
				case 0x63A7CE67: return 0xEEE9BF00 | alpha;
				case 0x9A327037: return 0xCDC8B100 | alpha;
				case 0x77957A3F: return 0xFFE4E100 | alpha;
				case 0x2E84EEAF: return 0x009ACD00 | alpha;
				case 0xC31130AF: return 0x87CEFF00 | alpha;
				case 0xCB2652F1: return 0x6CA6CD00 | alpha;
				case 0xD233F061: return 0x528B8B00 | alpha;
				case 0xBF34D6E5: return 0x528B8B00 | alpha;
				case 0x07A578FD: return 0x2E8B5700 | alpha;
				case 0x5E820C25: return 0x7FFF0000 | alpha;
				case 0x1F909225: return 0xEEEED100 | alpha;
				case 0x2F05A225: return 0xEEEED100 | alpha;
				case 0x1236EE2D: return 0xFFC12500 | alpha;
				case 0xC711C237: return 0xEEC59100 | alpha;
				case 0xD684A82B: return 0xFF6EB400 | alpha;
				case 0x2E90C8A7: return 0x05050500 | alpha;
				case 0x26A61037: return 0x1A1A1A00 | alpha;
				case 0xFE3494B7: return 0x33333300 | alpha;
				case 0x7AA3BCBD: return 0x40404000 | alpha;
				case 0x66067ABF: return 0x47474700 | alpha;
				case 0x3BB69661: return 0x4A4A4A00 | alpha;
				case 0x37307621: return 0x78787800 | alpha;
				case 0x6AB0BAFD: return 0x7A7A7A00 | alpha;
				case 0xEA03D4BB: return 0xA1A1A100 | alpha;
				case 0x27129239: return 0xB3B3B300 | alpha;
				case 0xA627F0FB: return 0xD1D1D100 | alpha;
				case 0x2736D43F: return 0xE5E5E500 | alpha;
			}
		case 0x02000100:
			switch (hash)
			{
				case 0x7E80195D: return 0x87CEEB00 | alpha;
				case 0xBE22FD43: return 0x228B2200 | alpha;
				case 0x16946909: return 0xBDB76B00 | alpha;
				case 0x83B71B1B: return 0xFFFF0000 | alpha;
				case 0x2B0569C3: return 0x8B868200 | alpha;
				case 0xF2A60DD7: return 0xCDC8B100 | alpha;
				case 0xBAB6310B: return 0xCDCDC100 | alpha;
				case 0x13837D5D: return 0xB9D3EE00 | alpha;
				case 0x9E862993: return 0x68838B00 | alpha;
				case 0x3335019D: return 0x008B8B00 | alpha;
				case 0xB2911B17: return 0xFFF68F00 | alpha;
				case 0x2E90015D: return 0xEE636300 | alpha;
				case 0x32068B1B: return 0x8B232300 | alpha;
				case 0xD3A2278D: return 0xCD850000 | alpha;
				case 0x5224794F: return 0xEE760000 | alpha;
				case 0x2F812D83: return 0xCD5B4500 | alpha;
				case 0x0E0345C5: return 0xEE5C4200 | alpha;
				case 0xE686EF87: return 0x8B362600 | alpha;
				case 0xB2970103: return 0x8B475D00 | alpha;
				case 0x16B7155D: return 0x2B2B2B00 | alpha;
				case 0x3BB6855D: return 0x4A4A4A00 | alpha;
				case 0x328613DB: return 0x73737300 | alpha;
				case 0x3730651D: return 0x78787800 | alpha;
				case 0xB3370103: return 0x7D7D7D00 | alpha;
				case 0x9AB46F59: return 0x85858500 | alpha;
				case 0x86172D5B: return 0x8C8C8C00 | alpha;
				case 0xDA10F503: return 0xDBDBDB00 | alpha;
				case 0x22971901: return 0xDEDEDE00 | alpha;
				case 0x0A14A95F: return 0xE5E5E500 | alpha;
				case 0x5B82EDDF: return 0xE8E8E800 | alpha;
			}
		case 0x02000120:
			switch (hash)
			{
				case 0x9300D1F1: return 0x2F4F4F00 | alpha;
				case 0x7F94CD23: return 0x77889900 | alpha;
				case 0xEBA25FFB: return 0x1E90FF00 | alpha;
				case 0xEBA10BB7: return 0xB0E0E600 | alpha;
				case 0x67B79B71: return 0xAFEEEE00 | alpha;
				case 0xE73135BB: return 0xFF69B400 | alpha;
				case 0xAA36A9E9: return 0x8B897000 | alpha;
				case 0x9AA56D6B: return 0x8B8B8300 | alpha;
				case 0x2F8075EF: return 0x836FFF00 | alpha;
				case 0xDB940F6D: return 0x1874CD00 | alpha;
				case 0xCB315F35: return 0x63B8FF00 | alpha;
				case 0xE7028967: return 0xB0E2FF00 | alpha;
				case 0x4B356365: return 0x96CDCD00 | alpha;
				case 0x16829BA3: return 0x00868B00 | alpha;
				case 0x16B3037D: return 0x79CDCD00 | alpha;
				case 0xDE0025FF: return 0x97FFFF00 | alpha;
				case 0x2FA75923: return 0x00CD0000 | alpha;
				case 0x2A166FAF: return 0xEEAEEE00 | alpha;
				case 0xF6273B29: return 0x912CEE00 | alpha;
				case 0x2E90B7A3: return 0x05050500 | alpha;
				case 0x26A5FF33: return 0x1A1A1A00 | alpha;
				case 0xFE3483B3: return 0x33333300 | alpha;
				case 0x7AA3ABB9: return 0x40404000 | alpha;
				case 0x660669BB: return 0x47474700 | alpha;
				case 0xB336EFFF: return 0x7D7D7D00 | alpha;
				case 0xBA003163: return 0x96969600 | alpha;
				case 0xEA03E5BF: return 0xA1A1A100 | alpha;
				case 0x2712A33D: return 0xB3B3B300 | alpha;
				case 0x2E2435A1: return 0xD4D4D400 | alpha;
				case 0xDA10E3FF: return 0xDBDBDB00 | alpha;
				case 0x2736C33B: return 0xE5E5E500 | alpha;
				case 0x4A07ABA9: return 0x00008B00 | alpha;
			}
		case 0x02080000:
			switch (hash)
			{
				case 0x2F0A3A93: return 0xFFEFD500 | alpha;
				case 0x462F2ED1: return 0x2F4F4F00 | alpha;
				case 0x4A0F6A05: return 0x00008000 | alpha;
				case 0xA3AF9409: return 0xBDB76B00 | alpha;
				case 0xFA0DE20D: return 0xCD5C5C00 | alpha;
				case 0x07AA5CC3: return 0xEECBAD00 | alpha;
				case 0xF31D2009: return 0xEEE9BF00 | alpha;
				case 0xF6A94493: return 0xF0FFF000 | alpha;
				case 0x2F0BE299: return 0xC1CDCD00 | alpha;
				case 0xCB2F821F: return 0x4876FF00 | alpha;
				case 0xCF1F868B: return 0x00B2EE00 | alpha;
				case 0x0F28AC41: return 0xB9D3EE00 | alpha;
				case 0x2E8AB05B: return 0x00EEEE00 | alpha;
				case 0x16AD401D: return 0x2E8B5700 | alpha;
				case 0x6B2A72DF: return 0xEE636300 | alpha;
				case 0xFB9D2AD3: return 0xEE957200 | alpha;
				case 0x721D9E15: return 0x8B574200 | alpha;
				case 0xFFBC6EC1: return 0xEE6A5000 | alpha;
				case 0x2EBF8A05: return 0x8B636C00 | alpha;
				case 0xA339864B: return 0x8968CD00 | alpha;
				case 0xDF8ABE4D: return 0xEED2EE00 | alpha;
				case 0x5F3D4A5F: return 0x2E2E2E00 | alpha;
				case 0x370C341B: return 0x45454500 | alpha;
				case 0x960A1E17: return 0x52525200 | alpha;
				case 0x522E3A57: return 0x82828200 | alpha;
				case 0xCE9D625D: return 0x8F8F8F00 | alpha;
				case 0x32AA44DD: return 0xA6A6A600 | alpha;
				case 0xD29B1C1B: return 0x8B000000 | alpha;
			}
		case 0x02080020:
			switch (hash)
			{
				case 0x372C9A3F: return 0xF5F5F500 | alpha;
				case 0x3A0B90FF: return 0xF5FFFA00 | alpha;
				case 0xAB8B7EA5: return 0x77889900 | alpha;
				case 0x1E8DE8A7: return 0x5F9EA000 | alpha;
				case 0x970854EB: return 0xADFF2F00 | alpha;
				case 0xAE9EE6A7: return 0xF0808000 | alpha;
				case 0xE728BAEF: return 0xFF149300 | alpha;
				case 0x623B46B9: return 0x9932CC00 | alpha;
				case 0x7F1966B3: return 0xF0FFF000 | alpha;
				case 0x872E88F5: return 0xC1CDC100 | alpha;
				case 0x9F1DA2FF: return 0x6C7B8B00 | alpha;
				case 0xC29E247D: return 0xB4EEB400 | alpha;
				case 0xDB08703F: return 0x698B6900 | alpha;
				case 0x1EAC96FB: return 0x4EEE9400 | alpha;
				case 0x8A2BA023: return 0xEE762100 | alpha;
				case 0xDE99CA6D: return 0xCD609000 | alpha;
				case 0x0E1FD42F: return 0xCD00CD00 | alpha;
				case 0x522CF62B: return 0x9A32CD00 | alpha;
				case 0xC31E88E9: return 0x912CEE00 | alpha;
				case 0xCEAAE4EB: return 0x551A8B00 | alpha;
				case 0xE30DCCE7: return 0xAB82FF00 | alpha;
				case 0x333B08E5: return 0x0A0A0A00 | alpha;
				case 0x46BAB8B5: return 0x36363600 | alpha;
				case 0x321D76B7: return 0x3D3D3D00 | alpha;
				case 0xAE8C9EBD: return 0x4A4A4A00 | alpha;
				case 0x2B98B279: return 0x85858500 | alpha;
				case 0x07892637: return 0x99999900 | alpha;
				case 0x2BBCF47F: return 0xB8B8B800 | alpha;
				case 0xBEAA82A5: return 0xC9C9C900 | alpha;
				case 0xBB88B267: return 0xFFFFFF00 | alpha;
			}
		case 0x02080100:
			switch (hash)
			{
				case 0xB63C6543: return 0x77889900 | alpha;
				case 0xF3B88B47: return 0x77889900 | alpha;
				case 0xB389C983: return 0x7FFFD400 | alpha;
				case 0xC3AE4B41: return 0x20B2AA00 | alpha;
				case 0x6EB93949: return 0xFA807200 | alpha;
				case 0x6EBA6B8B: return 0xB0306000 | alpha;
				case 0x0A88D1D9: return 0xFFE4C400 | alpha;
				case 0xE30C7B9B: return 0xCDB79E00 | alpha;
				case 0x0FBF7F05: return 0x8B776500 | alpha;
				case 0xCABADB51: return 0x836FFF00 | alpha;
				case 0x2EBC5DDB: return 0x00008B00 | alpha;
				case 0xDE1B210F: return 0x1874CD00 | alpha;
				case 0x1B989F9F: return 0x6C7B8B00 | alpha;
				case 0x5E9DE793: return 0x68838B00 | alpha;
				case 0x928C2F43: return 0x00C5CD00 | alpha;
				case 0x868D1517: return 0x458B7400 | alpha;
				case 0xDFAE355F: return 0x698B6900 | alpha;
				case 0x1F8B8949: return 0x458B0000 | alpha;
				case 0x5B3D1D8B: return 0x698B2200 | alpha;
				case 0xFE2EDB4D: return 0xCDCD0000 | alpha;
				case 0x2EBBAB99: return 0x8B750000 | alpha;
				case 0x431B55D7: return 0xFFD39B00 | alpha;
				case 0xFB1E7DCB: return 0xFFA50000 | alpha;
				case 0x878EA749: return 0xCD370000 | alpha;
				case 0xBB3EEB19: return 0xEEA2AD00 | alpha;
				case 0xB30C7F8D: return 0x7A378B00 | alpha;
				case 0x5F3D395B: return 0x2E2E2E00 | alpha;
				case 0x370C451F: return 0x45454500 | alpha;
				case 0xAE8CAFC1: return 0x4A4A4A00 | alpha;
				case 0x960A2F1B: return 0x52525200 | alpha;
				case 0x522E4B5B: return 0x82828200 | alpha;
				case 0xEEAE3701: return 0xD4D4D400 | alpha;
			}
		case 0x02080120:
			switch (hash)
			{
				case 0x8A887765: return 0xF0F8FF00 | alpha;
				case 0x9E0C1B6F: return 0x70809000 | alpha;
				case 0x320A0F2D: return 0xD3D3D300 | alpha;
				case 0x8B9A9BFF: return 0xADD8E600 | alpha;
				case 0x67BAFF31: return 0x00CED100 | alpha;
				case 0xCE1EF36F: return 0x556B2F00 | alpha;
				case 0x2E8FD9F7: return 0xEEE9E900 | alpha;
				case 0x333A2B39: return 0x8B898900 | alpha;
				case 0x921D4DF5: return 0xFFF8DC00 | alpha;
				case 0x072BF7BF: return 0xCDC1C500 | alpha;
				case 0xCE9A7121: return 0xCDB7B500 | alpha;
				case 0x4E9C53ED: return 0x00BFFF00 | alpha;
				case 0x22BC21B3: return 0xE0FFFF00 | alpha;
				case 0x7E3D6DA3: return 0x96CDCD00 | alpha;
				case 0x5E1BFD67: return 0xB3EE3A00 | alpha;
				case 0x068AD1BB: return 0x8B864E00 | alpha;
				case 0x372D7121: return 0x8B0A5000 | alpha;
				case 0x3E2A25A1: return 0xEE799F00 | alpha;
				case 0x9EBFE53F: return 0x8B225200 | alpha;
				case 0x333B19E9: return 0x0A0A0A00 | alpha;
				case 0x46BAC9B9: return 0x36363600 | alpha;
				case 0x321D87BB: return 0x3D3D3D00 | alpha;
				case 0x2B98C37D: return 0x85858500 | alpha;
				case 0xCE9D7361: return 0x8F8F8F00 | alpha;
				case 0x0789373B: return 0x99999900 | alpha;
				case 0x32AA55E1: return 0xA6A6A600 | alpha;
				case 0x2BBCE37B: return 0xB8B8B800 | alpha;
				case 0xBEAA71A1: return 0xC9C9C900 | alpha;
				case 0xA62801FF: return 0xD1D1D100 | alpha;
				case 0xEEAE25FD: return 0xD4D4D400 | alpha;
				case 0xBB88A163: return 0xFFFFFF00 | alpha;
			}
		case 0x02400000:
			switch (hash)
			{
				case 0xFBD124D3: return 0xFDF5E600 | alpha;
				case 0x03557A55: return 0xFAF0E600 | alpha;
				case 0xFE7136CB: return 0x69696900 | alpha;
				case 0x9F77A443: return 0x00FF7F00 | alpha;
				case 0xA6C6E65F: return 0xEEE8AA00 | alpha;
				case 0x3AC16C11: return 0xFAFAD200 | alpha;
				case 0x774744C3: return 0x8B776500 | alpha;
				case 0xDA548CCD: return 0x1E90FF00 | alpha;
				case 0xCBC4B447: return 0x607B8B00 | alpha;
				case 0x97665C85: return 0x96CDCD00 | alpha;
				case 0x87D2C4C1: return 0x00F5FF00 | alpha;
				case 0x1EC7F297: return 0x458B7400 | alpha;
				case 0x1FF35E01: return 0x00FF0000 | alpha;
				case 0xB7C666C9: return 0x458B0000 | alpha;
				case 0x42459C49: return 0x8B814C00 | alpha;
				case 0x8F75AA83: return 0xFFC1C100 | alpha;
				case 0x966448C7: return 0xCD9B9B00 | alpha;
				case 0x7245F85D: return 0x8B4C3900 | alpha;
				case 0x2AD6DC41: return 0xFF725600 | alpha;
				case 0xE2705C9F: return 0xCD688900 | alpha;
				case 0x72472A9F: return 0x8B1C6200 | alpha;
				case 0x27C79847: return 0x03030300 | alpha;
				case 0x3A70CC4B: return 0x17171700 | alpha;
				case 0x2B544657: return 0x24242400 | alpha;
				case 0x3261E2D9: return 0x40404000 | alpha;
				case 0x1B61669F: return 0x5E5E5E00 | alpha;
				case 0x63E78A9D: return 0x61616100 | alpha;
				case 0x3754961F: return 0xABABAB00 | alpha;
				case 0xB7E15245: return 0xB0B0B000 | alpha;
				case 0x8AC17E9D: return 0xBFBFBF00 | alpha;
			}
		case 0x02400020:
			switch (hash)
			{
				case 0xCA61466D: return 0xFFE4E100 | alpha;
				case 0xE6E17AAB: return 0x8FBC8F00 | alpha;
				case 0xCF5626EB: return 0x8B837800 | alpha;
				case 0x3BE4A029: return 0xEEE9BF00 | alpha;
				case 0x2FF51CBD: return 0x4876FF00 | alpha;
				case 0x2270E227: return 0xB0E2FF00 | alpha;
				case 0xC3638231: return 0x68838B00 | alpha;
				case 0xCBC21C79: return 0x98F5FF00 | alpha;
				case 0xFFE29A61: return 0x00EE0000 | alpha;
				case 0x8743DA2F: return 0x8B8B0000 | alpha;
				case 0x2B676829: return 0xFFE7BA00 | alpha;
				case 0x9A41742B: return 0x8B7E6600 | alpha;
				case 0xB2F266F7: return 0xFF404000 | alpha;
				case 0xC2C2ACED: return 0xEE9A0000 | alpha;
				case 0x13566463: return 0xFF634700 | alpha;
				case 0x075550E9: return 0xFF83FA00 | alpha;
				case 0x2EC0C0F1: return 0x8B668B00 | alpha;
				case 0xF2E0C629: return 0xD15FEE00 | alpha;
				case 0x37E55A27: return 0x0F0F0F00 | alpha;
				case 0x2B505075: return 0x1F1F1F00 | alpha;
				case 0x2B74927B: return 0x52525200 | alpha;
				case 0x4B651AFB: return 0x69696900 | alpha;
				case 0x36C7D8FD: return 0x70707000 | alpha;
				case 0x3B722A3F: return 0xA3A3A300 | alpha;
				case 0xD347C4A3: return 0xC2C2C200 | alpha;
				case 0x2BE1147D: return 0xEBEBEB00 | alpha;
				case 0xD7F204E1: return 0xF5F5F500 | alpha;
				case 0xC354C2E3: return 0xFCFCFC00 | alpha;
				case 0x7E7502A9: return 0x00008B00 | alpha;
			}
		case 0x02400100:
			switch (hash)
			{
				case 0x2F72EB0B: return 0x2F4F4F00 | alpha;
				case 0xCAC5490B: return 0x70809000 | alpha;
				case 0x72E6D35B: return 0x19197000 | alpha;
				case 0x5BF27B9F: return 0x7B68EE00 | alpha;
				case 0xAE740153: return 0xFFFFE000 | alpha;
				case 0x0BE63FCD: return 0xD0209000 | alpha;
				case 0x27C6A997: return 0xFFFAFA00 | alpha;
				case 0xEBD5C501: return 0xFFF5EE00 | alpha;
				case 0x22F04781: return 0xEEE5DE00 | alpha;
				case 0x16502511: return 0xEECFA100 | alpha;
				case 0x3E41CF9F: return 0xCDB7B500 | alpha;
				case 0x2A619157: return 0xF0FFFF00 | alpha;
				case 0xFF4723D7: return 0xE0EEEE00 | alpha;
				case 0x2FF6F9D3: return 0x63B8FF00 | alpha;
				case 0x03E33D9D: return 0x6C7B8B00 | alpha;
				case 0x96710751: return 0xB2DFEE00 | alpha;
				case 0x0BF3D59B: return 0x4EEE9400 | alpha;
				case 0x97654109: return 0x8B814C00 | alpha;
				case 0x4E706D41: return 0x8B3A3A00 | alpha;
				case 0x53E13F51: return 0x8B472600 | alpha;
				case 0xBA5237CB: return 0xCDBA9600 | alpha;
				case 0x12F105C3: return 0x8B1A1A00 | alpha;
				case 0x4AF435C7: return 0xCD370000 | alpha;
				case 0x2BC24D0D: return 0xFF6EB400 | alpha;
				case 0x33D76F4F: return 0xCD609000 | alpha;
				case 0x3AF68BCD: return 0xFFE1FF00 | alpha;
				case 0x27C78743: return 0x03030300 | alpha;
				case 0x3A70DD4F: return 0x17171700 | alpha;
				case 0x2B54575B: return 0x24242400 | alpha;
				case 0x3261F3DD: return 0x40404000 | alpha;
				case 0x1B61559B: return 0x5E5E5E00 | alpha;
				case 0xB7E14141: return 0xB0B0B000 | alpha;
				case 0xD347B39F: return 0xC2C2C200 | alpha;
				case 0x2BE12581: return 0xEBEBEB00 | alpha;
			}
		case 0x02400120:
			switch (hash)
			{
				case 0x1FF2437F: return 0xFFFAF000 | alpha;
				case 0x1FE2B123: return 0x66CDAA00 | alpha;
				case 0x76C7B7B9: return 0xFFE4C400 | alpha;
				case 0xDA72C7EF: return 0xEECFA100 | alpha;
				case 0x82737BAB: return 0x8B897000 | alpha;
				case 0xEEC1ABFD: return 0xFFF0F500 | alpha;
				case 0x1F57E777: return 0xF0FFFF00 | alpha;
				case 0xE7F6132D: return 0x00BFFF00 | alpha;
				case 0x9264C339: return 0x98F5FF00 | alpha;
				case 0x27C17FFB: return 0x00FFFF00 | alpha;
				case 0x2FC21BA1: return 0x9AFF9A00 | alpha;
				case 0xBB6433A5: return 0x7CCD7C00 | alpha;
				case 0xEED26FB5: return 0x00EE7600 | alpha;
				case 0x06C02FA5: return 0x6E8B3D00 | alpha;
				case 0x726515E3: return 0xEE762100 | alpha;
				case 0x16F58131: return 0xEE957200 | alpha;
				case 0xB3C4136D: return 0x7A378B00 | alpha;
				case 0x2FD3CBEF: return 0xCDB5CD00 | alpha;
				case 0x37E56B2B: return 0x0F0F0F00 | alpha;
				case 0x2B506179: return 0x1F1F1F00 | alpha;
				case 0x2B748177: return 0x52525200 | alpha;
				case 0x63E79BA1: return 0x61616100 | alpha;
				case 0x4B6509F7: return 0x69696900 | alpha;
				case 0x36C7C7F9: return 0x70707000 | alpha;
				case 0x3B72193B: return 0xA3A3A300 | alpha;
				case 0x3754A723: return 0xABABAB00 | alpha;
				case 0x8AC18FA1: return 0xBFBFBF00 | alpha;
				case 0xD7F215E5: return 0xF5F5F500 | alpha;
				case 0xC354D3E7: return 0xFCFCFC00 | alpha;
			}
		case 0x02480000:
			switch (hash)
			{
				case 0x3F7E5E91: return 0xFFDAB900 | alpha;
				case 0x7BCC9C8F: return 0x70809000 | alpha;
				case 0xCECABE0F: return 0xFAFAD200 | alpha;
				case 0xA6CA4A1F: return 0xB8860B00 | alpha;
				case 0x035F5E87: return 0xA52A2A00 | alpha;
				case 0x3F5D0E0D: return 0x1E90FF00 | alpha;
				case 0xB35A6885: return 0xA4D3EE00 | alpha;
				case 0x73EE46DF: return 0xB9D3EE00 | alpha;
				case 0x4A5DF883: return 0xEEEED100 | alpha;
				case 0x8E4F2685: return 0xFFC1C100 | alpha;
				case 0x0368A201: return 0xFF7F2400 | alpha;
				case 0xE3DDDADD: return 0x8B4C3900 | alpha;
				case 0xDB5A56C1: return 0x8B225200 | alpha;
				case 0xA6CFA88F: return 0x8B008B00 | alpha;
				case 0x2ACD6A8B: return 0x8968CD00 | alpha;
				case 0xF76B6457: return 0x1A1A1A00 | alpha;
				case 0xE2CE2259: return 0x21212100 | alpha;
				case 0xE7786297: return 0x54545400 | alpha;
				case 0x2FFEA89D: return 0x57575700 | alpha;
				case 0x3BDAB65F: return 0x7D7D7D00 | alpha;
				case 0x56D89C9D: return 0xB5B5B500 | alpha;
				case 0x9F5EC09B: return 0xB8B8B800 | alpha;
				case 0xF649DC47: return 0xFFFFFF00 | alpha;
				case 0xD7DF4A47: return 0x90EE9000 | alpha;
			}
		case 0x02480020:
			switch (hash)
			{
				case 0xBEEC2871: return 0xFFDAB900 | alpha;
				case 0x5E6E74F7: return 0xFFFACD00 | alpha;
				case 0xF7DA50B1: return 0x556B2F00 | alpha;
				case 0xDB4982AB: return 0x9ACD3200 | alpha;
				case 0x02FE12A7: return 0xF0E68C00 | alpha;
				case 0x1E5F98F5: return 0xEEDD8200 | alpha;
				case 0xD6FAF0F3: return 0x8B795E00 | alpha;
				case 0x276A52B5: return 0x66CDAA00 | alpha;
				case 0x47CECAB3: return 0x8B650800 | alpha;
				case 0x465B4AFF: return 0xEE636300 | alpha;
				case 0xF24896AD: return 0xFF824700 | alpha;
				case 0xCACC406F: return 0xCD683900 | alpha;
				case 0x7A7A3825: return 0x8B451300 | alpha;
				case 0xCE4F08EF: return 0x8B5A0000 | alpha;
				case 0x1FCD3261: return 0xFF725600 | alpha;
				case 0xEBDA0E25: return 0xCD4F3900 | alpha;
				case 0x5679507B: return 0xEEA2AD00 | alpha;
				case 0xDFD8FAAB: return 0xCD69C900 | alpha;
				case 0x2FFAB2BB: return 0x24242400 | alpha;
				case 0x26CA3035: return 0x4D4D4D00 | alpha;
				case 0x02DED4F5: return 0x66666600 | alpha;
				case 0x7F4DFCFB: return 0x73737300 | alpha;
				case 0x26EE723B: return 0x7F7F7F00 | alpha;
				case 0x83F84E3D: return 0xA6A6A600 | alpha;
				case 0x6F5B0C3F: return 0xADADAD00 | alpha;
				case 0x3BFEF865: return 0xB0B0B000 | alpha;
				case 0x32CE86E3: return 0xD9D9D900 | alpha;
				case 0x3778D825: return 0xDEDEDE00 | alpha;
				case 0x8F6BE0E3: return 0xF2F2F200 | alpha;
			}
		case 0x02480100:
			switch (hash)
			{
				case 0x325A29CF: return 0x69696900 | alpha;
				case 0x7E7CC105: return 0x00008000 | alpha;
				case 0xAB6F1709: return 0x2E8B5700 | alpha;
				case 0xEAD8418F: return 0xDB709300 | alpha;
				case 0xEFF88581: return 0xCDC1C500 | alpha;
				case 0x926E71D9: return 0x7AC5CD00 | alpha;
				case 0x727AEFD7: return 0x008B4500 | alpha;
				case 0x2B6E9307: return 0x8B814C00 | alpha;
				case 0x06EC1D9B: return 0x8B232300 | alpha;
				case 0x0B5A311B: return 0xEE826200 | alpha;
				case 0x03C977D5: return 0x8B574200 | alpha;
				case 0x97DD4BD1: return 0x8B450000 | alpha;
				case 0xDAFA9385: return 0xEE5C4200 | alpha;
				case 0x17E8AD01: return 0xEE128900 | alpha;
				case 0x0B5B635D: return 0xEE30A700 | alpha;
				case 0xE3DF0D1F: return 0x8B1C6200 | alpha;
				case 0xFB7A59C7: return 0x9B30FF00 | alpha;
				case 0xD3FE0389: return 0x7D26CD00 | alpha;
				case 0x137A358F: return 0xCDB5CD00 | alpha;
				case 0xF76B5353: return 0x1A1A1A00 | alpha;
				case 0xE2CE1155: return 0x21212100 | alpha;
				case 0xE778739B: return 0x54545400 | alpha;
				case 0x2FFE9799: return 0x57575700 | alpha;
				case 0x83F85F41: return 0xA6A6A600 | alpha;
				case 0x6F5B1D43: return 0xADADAD00 | alpha;
				case 0x56D88B99: return 0xB5B5B500 | alpha;
				case 0x9F5ED19F: return 0xB8B8B800 | alpha;
				case 0x32CE75DF: return 0xD9D9D900 | alpha;
				case 0x8F6BCFDF: return 0xF2F2F200 | alpha;
				case 0xF649CB43: return 0xFFFFFF00 | alpha;
			}
		case 0x02480120:
			switch (hash)
			{
				case 0xF36A052B: return 0xFFEBCD00 | alpha;
				case 0x1E6DC7A1: return 0x77889900 | alpha;
				case 0xE2F9BB63: return 0x228B2200 | alpha;
				case 0x2BCB6169: return 0xFFFFF000 | alpha;
				case 0x4F5B276F: return 0x87CEFF00 | alpha;
				case 0x27DED131: return 0x6CA6CD00 | alpha;
				case 0xFF6CD529: return 0x8DB6CD00 | alpha;
				case 0x32CB17A3: return 0xBBFFFF00 | alpha;
				case 0x9A79E57B: return 0x7AC5CD00 | alpha;
				case 0x0BC93121: return 0x00E5EE00 | alpha;
				case 0xDF4B2D35: return 0x008B4500 | alpha;
				case 0x2AFD07E1: return 0x00FF0000 | alpha;
				case 0x8BCA95EF: return 0xEEAD0E00 | alpha;
				case 0x8EFA9963: return 0xCD262600 | alpha;
				case 0x627C7BED: return 0xEE760000 | alpha;
				case 0x63DDE9A3: return 0x8B475D00 | alpha;
				case 0xB36EE329: return 0xBF3EFF00 | alpha;
				case 0x07D863AD: return 0x9A32CD00 | alpha;
				case 0x46DAE9ED: return 0xFFE1FF00 | alpha;
				case 0x2FFAA1B7: return 0x24242400 | alpha;
				case 0x26CA4139: return 0x4D4D4D00 | alpha;
				case 0x02DEE5F9: return 0x66666600 | alpha;
				case 0x7F4E0DFF: return 0x73737300 | alpha;
				case 0x3BDAC763: return 0x7D7D7D00 | alpha;
				case 0x26EE6137: return 0x7F7F7F00 | alpha;
				case 0x3BFEE761: return 0xB0B0B000 | alpha;
				case 0x3778C721: return 0xDEDEDE00 | alpha;
			}
	}
}
else
{
	switch (hash & 0x000C1810)
	{
		case 0x00000000:
			switch (hash)
			{
				case 0x8A91A7E0: return 0x6A5ACD00 | alpha;
				case 0x4D2062C4: return 0x4682B400 | alpha;
				case 0x4DB12008: return 0x5F9EA000 | alpha;
				case 0xAB91A2E8: return 0x2E8B5700 | alpha;
				case 0x521060E8: return 0xF0808000 | alpha;
				case 0x4653E762: return 0xCDAF9500 | alpha;
				case 0xC06060A6: return 0xFFFACD00 | alpha;
				case 0x21C30020: return 0xEEE0E500 | alpha;
				case 0x5FB1420E: return 0x1C86EE00 | alpha;
				case 0xA4E1A440: return 0x9FB6CD00 | alpha;
				case 0xF441C3A4: return 0x90EE9000 | alpha;
				case 0x27B04706: return 0x7FFF0000 | alpha;
				case 0xC8630568: return 0xC0FF3E00 | alpha;
				case 0x9793A36E: return 0xEEB42200 | alpha;
				case 0x00B3A32E: return 0xFF824700 | alpha;
				case 0x39E1444A: return 0x8B250000 | alpha;
				case 0xB88204AA: return 0x8B250000 | alpha;
				case 0xAB5043A0: return 0xFF82AB00 | alpha;
				case 0x99A3632E: return 0xEE00EE00 | alpha;
				case 0x27C1470E: return 0xFFBBFF00 | alpha;
				case 0x3590428A: return 0x0D0D0D00 | alpha;
				case 0x3371636C: return 0x0F0F0F00 | alpha;
				case 0x01D220AA: return 0x14141400 | alpha;
				case 0x2260E082: return 0xABABAB00 | alpha;
				case 0x20420164: return 0xC4C4C400 | alpha;
				case 0x71B045E4: return 0xC7C7C700 | alpha;
				case 0x6F9166C6: return 0xE0E0E000 | alpha;
				case 0x4271A422: return 0xF0F0F000 | alpha;
			}
		case 0x00000010:
			switch (hash)
			{
				case 0x2F9243F0: return 0xFFF5EE00 | alpha;
				case 0x0E73207C: return 0x00BFFF00 | alpha;
				case 0xDD214096: return 0x87CEFA00 | alpha;
				case 0xF990C03C: return 0xB0C4DE00 | alpha;
				case 0xAB222634: return 0x8B451300 | alpha;
				case 0x47438272: return 0xCDB38B00 | alpha;
				case 0x15B30190: return 0xCDB38B00 | alpha;
				case 0x6C522438: return 0xE0EEEE00 | alpha;
				case 0x4C416098: return 0xC1CDCD00 | alpha;
				case 0x3330659A: return 0x00008B00 | alpha;
				case 0x1420A612: return 0x4A708B00 | alpha;
				case 0xCF30E412: return 0x4A708B00 | alpha;
				case 0x927024D0: return 0x9AC0CD00 | alpha;
				case 0xAA3025FA: return 0x54FF9F00 | alpha;
				case 0x85536358: return 0x54FF9F00 | alpha;
				case 0xB0B180D8: return 0xEEC59100 | alpha;
				case 0x2FB1627A: return 0xCD333300 | alpha;
				case 0xB9F1E0DA: return 0xCD333300 | alpha;
				case 0xA18382D0: return 0xCD660000 | alpha;
				case 0x37E20070: return 0x8B3A6200 | alpha;
				case 0x017165F0: return 0xCD96CD00 | alpha;
				case 0x95D3E598: return 0x1F1F1F00 | alpha;
				case 0x63B1411A: return 0x2E2E2E00 | alpha;
				case 0x619261FC: return 0x47474700 | alpha;
				case 0xB300A67C: return 0x4A4A4A00 | alpha;
				case 0xB0E1C75E: return 0x63636300 | alpha;
				case 0x3253C03A: return 0x70707000 | alpha;
				case 0x83C204BA: return 0x73737300 | alpha;
				case 0x81A3259C: return 0x8C8C8C00 | alpha;
				case 0x548362F8: return 0x9C9C9C00 | alpha;
				case 0x2D20A0FC: return 0x8B000000 | alpha;
			}
		case 0x00000800:
			switch (hash)
			{
				case 0x81D1ABAE: return 0xFFE4E100 | alpha;
				case 0xCD234B8A: return 0xD3D3D300 | alpha;
				case 0x67A329E2: return 0x483D8B00 | alpha;
				case 0xE292EE42: return 0xE0FFFF00 | alpha;
				case 0x0DD22D24: return 0x66CDAA00 | alpha;
				case 0x67F34C86: return 0xDEB88700 | alpha;
				case 0x7D03AE06: return 0xF4A46000 | alpha;
				case 0x0000C822: return 0xD2B48C00 | alpha;
				case 0x9E816FA6: return 0xFFEFDB00 | alpha;
				case 0x48B0E84A: return 0xCDC0B000 | alpha;
				case 0xE5104B28: return 0xCDC0B000 | alpha;
				case 0x9F328E4E: return 0xFFDEAD00 | alpha;
				case 0x2E208A0A: return 0xEEEEE000 | alpha;
				case 0x07B06DCC: return 0x8B8B8300 | alpha;
				case 0x9961A84A: return 0x9ACD3200 | alpha;
				case 0x72E0ED04: return 0xFFEC8B00 | alpha;
				case 0x5083EF86: return 0xCDCDB400 | alpha;
				case 0x6CF2890E: return 0xFF824700 | alpha;
				case 0x01702F04: return 0xCD919E00 | alpha;
				case 0x5A82ED0C: return 0x8B478900 | alpha;
				case 0x01416DA6: return 0x00000000 | alpha;
				case 0x25726FA6: return 0x00000000 | alpha;
				case 0x39616DC0: return 0x47474700 | alpha;
				case 0x37428EA2: return 0x91919100 | alpha;
				case 0x3523AF84: return 0xDBDBDB00 | alpha;
				case 0x32E08E60: return 0xF2F2F200 | alpha;
				case 0xBEE0CC28: return 0xFCFCFC00 | alpha;
			}
		case 0x00000810:
			switch (hash)
			{
				case 0xDF532D12: return 0xFFEFD500 | alpha;
				case 0x0423AEB8: return 0xFFFFF000 | alpha;
				case 0x53D3E836: return 0xFFFACD00 | alpha;
				case 0x8820E838: return 0x8470FF00 | alpha;
				case 0xAB838F52: return 0x98FB9800 | alpha;
				case 0xC8F0A854: return 0x9400D300 | alpha;
				case 0xD4A16F1A: return 0xCDB79E00 | alpha;
				case 0x31610B3A: return 0x838B8B00 | alpha;
				case 0x0C438ADC: return 0xC6E2FF00 | alpha;
				case 0xCBC3CF70: return 0xBFEFFF00 | alpha;
				case 0xC361CF3A: return 0x53868B00 | alpha;
				case 0xCED34A5E: return 0x9BCD9B00 | alpha;
				case 0xB8B049BC: return 0x698B6900 | alpha;
				case 0x91508ADC: return 0x43CD8000 | alpha;
				case 0x2A12A956: return 0x00CD6600 | alpha;
				case 0xD572CE5C: return 0x8B4C3900 | alpha;
				case 0x1952EEDC: return 0xCD8C9500 | alpha;
				case 0xEC32487A: return 0xCD8C9500 | alpha;
				case 0x12430D9E: return 0x2B2B2B00 | alpha;
				case 0xF9C08CF8: return 0x33333300 | alpha;
				case 0x2B6268F6: return 0x38383800 | alpha;
				case 0xE5234AFA: return 0x3B3B3B00 | alpha;
				case 0x3030EB3A: return 0x70707000 | alpha;
				case 0x294389D8: return 0x82828200 | alpha;
				case 0xD3116A1C: return 0x8F8F8F00 | alpha;
				case 0x27008ABC: return 0x99999900 | alpha;
				case 0xD0F28AFE: return 0xA8A8A800 | alpha;
				case 0x2260CF7E: return 0xABABAB00 | alpha;
				case 0xA3D2C85A: return 0xB8B8B800 | alpha;
				case 0x2E120C1C: return 0xBABABA00 | alpha;
				case 0xA1B3E93C: return 0xD1D1D100 | alpha;
				case 0xF3222DBC: return 0xD4D4D400 | alpha;
				case 0xF1034E9E: return 0xEDEDED00 | alpha;
			}
		case 0x00001000:
			switch (hash)
			{
				case 0x7450B48C: return 0x69696900 | alpha;
				case 0x4E8371C4: return 0x00008000 | alpha;
				case 0xB5E355E2: return 0x00FF7F00 | alpha;
				case 0x0413554C: return 0xADFF2F00 | alpha;
				case 0xEBA2D58C: return 0xCD5C5C00 | alpha;
				case 0x60523602: return 0xEEE5DE00 | alpha;
				case 0xA9F2D548: return 0xFFEFDB00 | alpha;
				case 0x8A729384: return 0x668B8B00 | alpha;
				case 0x8A70D644: return 0x90EE9000 | alpha;
				case 0x2D523082: return 0x00EE0000 | alpha;
				case 0x06E21444: return 0x008B0000 | alpha;
				case 0x8CB17126: return 0x7FFF0000 | alpha;
				case 0xC75294E2: return 0xCAFF7000 | alpha;
				case 0xEA70B02E: return 0x8B8B0000 | alpha;
				case 0xE76052AC: return 0xEE9A0000 | alpha;
				case 0xB2C23200: return 0xFF725600 | alpha;
				case 0x8E0056C4: return 0xFF634700 | alpha;
				case 0x21C170E4: return 0xFF634700 | alpha;
				case 0x27C01022: return 0xFFB5C500 | alpha;
				case 0x333391C4: return 0x8B636C00 | alpha;
				case 0x3253378E: return 0xCD00CD00 | alpha;
				case 0x4680F40C: return 0x5D478B00 | alpha;
				case 0x35903186: return 0x0D0D0D00 | alpha;
				case 0x33715268: return 0x0F0F0F00 | alpha;
				case 0x01D231AE: return 0x14141400 | alpha;
				case 0x61927300: return 0x47474700 | alpha;
				case 0xB300B780: return 0x4A4A4A00 | alpha;
				case 0x81A336A0: return 0x8C8C8C00 | alpha;
				case 0x2041F060: return 0xC4C4C400 | alpha;
				case 0x71B034E0: return 0xC7C7C700 | alpha;
				case 0x3C1110E6: return 0xC9C9C900 | alpha;
				case 0x6F9155C2: return 0xE0E0E000 | alpha;
				case 0x1D02D088: return 0x90EE9000 | alpha;
			}
		case 0x00001010:
			switch (hash)
			{
				case 0xFBF3B0B2: return 0xFDF5E600 | alpha;
				case 0x31A21592: return 0xAFEEEE00 | alpha;
				case 0x634393B2: return 0xAFEEEE00 | alpha;
				case 0x68E3711C: return 0xFF00FF00 | alpha;
				case 0xC3C1F47A: return 0xEED5B700 | alpha;
				case 0x8323F7D4: return 0xE0EEE000 | alpha;
				case 0x6073D350: return 0x7A67EE00 | alpha;
				case 0xC2D111F6: return 0x36648B00 | alpha;
				case 0x0183B75E: return 0x008B8B00 | alpha;
				case 0x8EB1D2D4: return 0x7FFFD400 | alpha;
				case 0xDFA0D7B4: return 0x00FF7F00 | alpha;
				case 0xB3923614: return 0x00FF7F00 | alpha;
				case 0x2F50169A: return 0xCDC67300 | alpha;
				case 0xB99094FA: return 0xCDC67300 | alpha;
				case 0xD331759A: return 0x8B735500 | alpha;
				case 0x12809690: return 0xCD660000 | alpha;
				case 0xFCF056DC: return 0xEE30A700 | alpha;
				case 0x95D3D494: return 0x1F1F1F00 | alpha;
				case 0x63B1521E: return 0x2E2E2E00 | alpha;
				case 0x3472B05C: return 0x57575700 | alpha;
				case 0x3253D13E: return 0x70707000 | alpha;
				case 0x83C215BE: return 0x73737300 | alpha;
				case 0x548373FC: return 0x9C9C9C00 | alpha;
				case 0x4271931E: return 0xF0F0F000 | alpha;
				case 0xC82315D4: return 0xA9A9A900 | alpha;
			}
		case 0x00001800:
			switch (hash)
			{
				case 0x31011B0E: return 0x70809000 | alpha;
				case 0xC7617D0A: return 0x3CB37100 | alpha;
				case 0x0A919A84: return 0x00FA9A00 | alpha;
				case 0x7851BF48: return 0xFFB6C100 | alpha;
				case 0x9BA25E2C: return 0xC7158500 | alpha;
				case 0x78507842: return 0xEEE5DE00 | alpha;
				case 0x13611DA0: return 0x8B838600 | alpha;
				case 0xFC22DF80: return 0x436EEE00 | alpha;
				case 0x9DF1DC42: return 0x27408B00 | alpha;
				case 0x2AF318EE: return 0x104E8B00 | alpha;
				case 0x0BA1FB0A: return 0x607B8B00 | alpha;
				case 0xC0803FC0: return 0xC6E2FF00 | alpha;
				case 0x8B809D2A: return 0xCAE1FF00 | alpha;
				case 0x3F003D84: return 0xAEEEEE00 | alpha;
				case 0xB352BDE8: return 0xFFE7BA00 | alpha;
				case 0xBFE3FC6E: return 0x8B5A0000 | alpha;
				case 0x1A00D866: return 0xEE400000 | alpha;
				case 0xB1D0BBE0: return 0xCD107600 | alpha;
				case 0xAEC2FD02: return 0xCD107600 | alpha;
				case 0x9133FD0E: return 0x68228B00 | alpha;
				case 0xFFF2188A: return 0x9F79EE00 | alpha;
				case 0x01415CA2: return 0x00000000 | alpha;
				case 0x25725EA2: return 0x00000000 | alpha;
				case 0xB0E1D862: return 0x63636300 | alpha;
				case 0xD3117B20: return 0x8F8F8F00 | alpha;
				case 0xD0F29C02: return 0xA8A8A800 | alpha;
				case 0x2E121D20: return 0xBABABA00 | alpha;
				case 0x3C10FFE2: return 0xC9C9C900 | alpha;
				case 0xA1B3FA40: return 0xD1D1D100 | alpha;
				case 0xF3223EC0: return 0xD4D4D400 | alpha;
				case 0x35239E80: return 0xDBDBDB00 | alpha;
				case 0xF1035FA2: return 0xEDEDED00 | alpha;
				case 0x32E09F64: return 0xF2F2F200 | alpha;
				case 0xBEE0BB24: return 0xFCFCFC00 | alpha;
			}
		case 0x00001810:
			switch (hash)
			{
				case 0xCA2199DE: return 0xF5F5F500 | alpha;
				case 0xD2735E30: return 0xFFDAB900 | alpha;
				case 0x00009E1A: return 0xFF000000 | alpha;
				case 0x7C02B972: return 0xEE82EE00 | alpha;
				case 0x44D23F76: return 0xCDC8B100 | alpha;
				case 0x67227ED8: return 0x8B887800 | alpha;
				case 0x9DF3B958: return 0x36648B00 | alpha;
				case 0x79F33F30: return 0x4A708B00 | alpha;
				case 0x2EC0F9DE: return 0x008B8B00 | alpha;
				case 0xF3B2FCF4: return 0x7FFFD400 | alpha;
				case 0xF19118DC: return 0xC1FFC100 | alpha;
				case 0x4250B9DE: return 0xFF6A6A00 | alpha;
				case 0x5F835EBE: return 0xCD555500 | alpha;
				case 0x99E11D3A: return 0x8B232300 | alpha;
				case 0x48803E9E: return 0xFF3E9600 | alpha;
				case 0xA4503CF0: return 0x8B7B8B00 | alpha;
				case 0x1242FC9A: return 0x2B2B2B00 | alpha;
				case 0xF9C07BF4: return 0x33333300 | alpha;
				case 0x2B6279FA: return 0x38383800 | alpha;
				case 0xE52339F6: return 0x3B3B3B00 | alpha;
				case 0x39615CBC: return 0x47474700 | alpha;
				case 0x34729F58: return 0x57575700 | alpha;
				case 0x3273FB5A: return 0x59595900 | alpha;
				case 0x3030FC3E: return 0x70707000 | alpha;
				case 0x0533FD96: return 0x7F7F7F00 | alpha;
				case 0x29439ADC: return 0x82828200 | alpha;
				case 0x37427D9E: return 0x91919100 | alpha;
				case 0x270079B8: return 0x99999900 | alpha;
				case 0xA3D2D95E: return 0xB8B8B800 | alpha;
				case 0x4970189E: return 0x8B008B00 | alpha;
			}
		case 0x00040000:
			switch (hash)
			{
				case 0x3A65C382: return 0xF0FFF000 | alpha;
				case 0xEF8640E8: return 0x0000CD00 | alpha;
				case 0xED7566E8: return 0x3CB37100 | alpha;
				case 0xAE05C1CC: return 0xADFF2F00 | alpha;
				case 0xD2A50242: return 0x8B7D7B00 | alpha;
				case 0x8C3505EC: return 0x1C86EE00 | alpha;
				case 0xA72542A4: return 0xB0E2FF00 | alpha;
				case 0xC8956202: return 0x9FB6CD00 | alpha;
				case 0x5C2622E4: return 0xAEEEEE00 | alpha;
				case 0x9125E662: return 0x00C5CD00 | alpha;
				case 0x34F7A360: return 0x79CDCD00 | alpha;
				case 0x8244A5A2: return 0x97FFFF00 | alpha;
				case 0xFC56E5E6: return 0x548B5400 | alpha;
				case 0xA05523EC: return 0xFFFF0000 | alpha;
				case 0xEA246526: return 0xEEB4B400 | alpha;
				case 0x3266E20C: return 0x8B7E6600 | alpha;
				case 0x7756C762: return 0xCD688900 | alpha;
				case 0xD10407A2: return 0xCD688900 | alpha;
				case 0xF39725CA: return 0xEE7AE900 | alpha;
				case 0x09E56648: return 0x9B30FF00 | alpha;
				case 0x30E5E044: return 0x08080800 | alpha;
				case 0x2EC70126: return 0x0A0A0A00 | alpha;
				case 0x3EE4E50E: return 0x17171700 | alpha;
				case 0xAC378720: return 0x30303000 | alpha;
				case 0x6AE70480: return 0xADADAD00 | alpha;
				case 0x3C3541E8: return 0xFCFCFC00 | alpha;
			}
		case 0x00040010:
			switch (hash)
			{
				case 0x1D86A29A: return 0x19197000 | alpha;
				case 0x5CA5E158: return 0x8470FF00 | alpha;
				case 0x19544572: return 0x98FB9800 | alpha;
				case 0x817685DE: return 0xEEE8AA00 | alpha;
				case 0x5C56A39C: return 0xFF69B400 | alpha;
				case 0x30E50298: return 0xCDC9C900 | alpha;
				case 0x2EC6237A: return 0x8B898900 | alpha;
				case 0x2C3587BA: return 0x00FFFF00 | alpha;
				case 0x8697205A: return 0x54FF9F00 | alpha;
				case 0x2AA5C558: return 0xFFF68F00 | alpha;
				case 0x2E856216: return 0xEEC90000 | alpha;
				case 0x2C6682F8: return 0xCDAD0000 | alpha;
				case 0x1E56A190: return 0xCD9B1D00 | alpha;
				case 0x06E70290: return 0xCD683900 | alpha;
				case 0xB8C6A31A: return 0x8B735500 | alpha;
				case 0x01468134: return 0xEE9A4900 | alpha;
				case 0x8B57421A: return 0xFF8C6900 | alpha;
				case 0xDBB54790: return 0xFFA07A00 | alpha;
				case 0xD574009E: return 0x8B1C6200 | alpha;
				case 0x4465A118: return 0x1C1C1C00 | alpha;
				case 0x93B5067A: return 0x38383800 | alpha;
				case 0x7F17C47C: return 0x40404000 | alpha;
				case 0x6D05E39E: return 0x94949400 | alpha;
				case 0x526483DA: return 0xB5B5B500 | alpha;
				case 0x3DC741DC: return 0xBDBDBD00 | alpha;
				case 0x8D16A73E: return 0xD9D9D900 | alpha;
			}
		case 0x00040800:
			switch (hash)
			{
				case 0x9F150F8E: return 0xD3D3D300 | alpha;
				case 0x3DE7CCA0: return 0x483D8B00 | alpha;
				case 0x8B064EAE: return 0x4169E100 | alpha;
				case 0xE9B48F2C: return 0x9ACD3200 | alpha;
				case 0x0BB4EDE4: return 0xCDAF9500 | alpha;
				case 0x6F352D00: return 0x8B7D7B00 | alpha;
				case 0xF337AF48: return 0xA4D3EE00 | alpha;
				case 0xDE354EE0: return 0xC6E2FF00 | alpha;
				case 0x8F756986: return 0x76EE0000 | alpha;
				case 0xF3C56884: return 0xFFFFE000 | alpha;
				case 0x14574EA4: return 0x8B1A1A00 | alpha;
				case 0x07C72C0E: return 0xFF7F0000 | alpha;
				case 0x02C56FCE: return 0xFF7F0000 | alpha;
				case 0x6CC76F22: return 0xEE6A5000 | alpha;
				case 0x4CB6AB82: return 0xCD5B4500 | alpha;
				case 0x0156CA8A: return 0xFF000000 | alpha;
				case 0x058468EE: return 0xEE00EE00 | alpha;
				case 0x646509EC: return 0xB452CD00 | alpha;
				case 0xF275EA0C: return 0xB23AEE00 | alpha;
				case 0x76244C28: return 0x9B30FF00 | alpha;
				case 0x54072F4E: return 0xCDB5CD00 | alpha;
				case 0x01658DA4: return 0x05050500 | alpha;
				case 0x1DB68F40: return 0x78787800 | alpha;
				case 0x30552D40: return 0xA3A3A300 | alpha;
				case 0xBC554900: return 0xB0B0B000 | alpha;
				case 0x3766AEA0: return 0xC4C4C400 | alpha;
				case 0xBA3669E2: return 0xC9C9C900 | alpha;
				case 0x2E364E22: return 0xEDEDED00 | alpha;
				case 0x8AF7C820: return 0xF2F2F200 | alpha;
				case 0xDC660CA0: return 0xF5F5F500 | alpha;
			}
		case 0x00040810:
			switch (hash)
			{
				case 0x9C55ADD0: return 0xE6E6FA00 | alpha;
				case 0x1037C95C: return 0x00BFFF00 | alpha;
				case 0x1957A932: return 0x00640000 | alpha;
				case 0x56F62DF8: return 0xDA70D600 | alpha;
				case 0x21F6EFDA: return 0x9932CC00 | alpha;
				case 0xE3F4CA9A: return 0x8A2BE200 | alpha;
				case 0x8A9768DC: return 0xD8BFD800 | alpha;
				case 0x0164AFF8: return 0xEEE9E900 | alpha;
				case 0x5DB66DFC: return 0x8B7D6B00 | alpha;
				case 0xE1766C10: return 0x00688B00 | alpha;
				case 0x2A16A89C: return 0x00EEEE00 | alpha;
				case 0x19A64A5E: return 0x97FFFF00 | alpha;
				case 0xD9374CF0: return 0xCD683900 | alpha;
				case 0x41B50CF6: return 0xFFD39B00 | alpha;
				case 0x0BE5CD1C: return 0xFF3E9600 | alpha;
				case 0x3334C8B0: return 0x8B668B00 | alpha;
				case 0x2DA58A1A: return 0x21212100 | alpha;
				case 0x3BA46CDC: return 0x30303000 | alpha;
				case 0x34B70B7A: return 0x42424200 | alpha;
				case 0xE3046BDC: return 0x54545400 | alpha;
				case 0x32740C5E: return 0x59595900 | alpha;
				case 0xCE6729DE: return 0x5C5C5C00 | alpha;
				case 0x2B86AAFC: return 0x6B6B6B00 | alpha;
				case 0x39858DBE: return 0x7A7A7A00 | alpha;
				case 0x05340E9A: return 0x7F7F7F00 | alpha;
				case 0x03152F7C: return 0x99999900 | alpha;
				case 0xEE77ED7E: return 0xA1A1A100 | alpha;
				case 0x2967CBDE: return 0xB5B5B500 | alpha;
				case 0x2724AABA: return 0xCCCCCC00 | alpha;
			}
		case 0x00041000:
			switch (hash)
			{
				case 0xCB44D544: return 0xF8F8FF00 | alpha;
				case 0x4606564E: return 0xFFF0F500 | alpha;
				case 0x7CD590AE: return 0xD3D3D300 | alpha;
				case 0xF4A557E8: return 0x0000CD00 | alpha;
				case 0xCD5590EE: return 0xFF149300 | alpha;
				case 0xD384B2EE: return 0xC7158500 | alpha;
				case 0x1EE5B660: return 0xFFF5EE00 | alpha;
				case 0x7FA79202: return 0xFFDAB900 | alpha;
				case 0xB3B6B728: return 0xFFFFF000 | alpha;
				case 0x7266F44C: return 0x009ACD00 | alpha;
				case 0xD2A69626: return 0x668B8B00 | alpha;
				case 0x06A730E2: return 0x97FFFF00 | alpha;
				case 0xEC579106: return 0x548B5400 | alpha;
				case 0x9894B106: return 0xCDBE7000 | alpha;
				case 0x7F95700E: return 0xFFB90F00 | alpha;
				case 0x4D47376A: return 0xCDBA9600 | alpha;
				case 0x88C55742: return 0xEE762100 | alpha;
				case 0x8D945082: return 0xCD262600 | alpha;
				case 0x31D65624: return 0x8B3E2F00 | alpha;
				case 0x27F4D046: return 0xCD4F3900 | alpha;
				case 0x7BE79328: return 0x8B250000 | alpha;
				case 0x0146572C: return 0xEE000000 | alpha;
				case 0x00D65420: return 0xFF82AB00 | alpha;
				case 0xC5A6F6EA: return 0xE066FF00 | alpha;
				case 0xC936364A: return 0xE066FF00 | alpha;
				case 0x0FC511CC: return 0xB452CD00 | alpha;
				case 0xCCE4162A: return 0x5D478B00 | alpha;
				case 0x30E5F148: return 0x08080800 | alpha;
				case 0x2EC7122A: return 0x0A0A0A00 | alpha;
				case 0x3EE4D40A: return 0x17171700 | alpha;
				case 0x1B97B022: return 0x91919100 | alpha;
				case 0x6D05F4A2: return 0x94949400 | alpha;
				case 0x6AE71584: return 0xADADAD00 | alpha;
				case 0x3DC752E0: return 0xBDBDBD00 | alpha;
				case 0x3C3530E4: return 0xFCFCFC00 | alpha;
			}
		case 0x00041010:
			switch (hash)
			{
				case 0x31F4F736: return 0xFAEBD700 | alpha;
				case 0x7DA55710: return 0x69696900 | alpha;
				case 0x6346F772: return 0x00CED100 | alpha;
				case 0xAB86F312: return 0x00640000 | alpha;
				case 0x03555530: return 0x00FF0000 | alpha;
				case 0x97769472: return 0xFFFFE000 | alpha;
				case 0x7907D454: return 0xBC8F8F00 | alpha;
				case 0x6B25B594: return 0xE0EEE000 | alpha;
				case 0xFAF6D1DE: return 0xEEE0E500 | alpha;
				case 0x5D94F374: return 0x473C8B00 | alpha;
				case 0x2E861458: return 0x0000EE00 | alpha;
				case 0x2C67353A: return 0x0000CD00 | alpha;
				case 0x92667630: return 0xBFEFFF00 | alpha;
				case 0x9E84769C: return 0x53868B00 | alpha;
				case 0xBE77301E: return 0x97FFFF00 | alpha;
				case 0xF676F554: return 0x76EEC600 | alpha;
				case 0x41879276: return 0x00CD6600 | alpha;
				case 0x64F7B192: return 0xCD950C00 | alpha;
				case 0x3A37157E: return 0xFF6A6A00 | alpha;
				case 0x0156F492: return 0xFFA54F00 | alpha;
				case 0x2B071138: return 0xFF404000 | alpha;
				case 0xA717515E: return 0xFF149300 | alpha;
				case 0x2585F31A: return 0xFFAEB900 | alpha;
				case 0x44659014: return 0x1C1C1C00 | alpha;
				case 0xAC37761C: return 0x30303000 | alpha;
				case 0x93B4F576: return 0x38383800 | alpha;
				case 0x7F17B378: return 0x40404000 | alpha;
				case 0x526494DE: return 0xB5B5B500 | alpha;
				case 0xFE665374: return 0xA9A9A900 | alpha;
				case 0xCE27145C: return 0x8B000000 | alpha;
			}
		case 0x00041800:
			switch (hash)
			{
				case 0x8A343E8E: return 0xFFF0F500 | alpha;
				case 0xEFD618C8: return 0x6495ED00 | alpha;
				case 0x90F4BCA2: return 0x00FA9A00 | alpha;
				case 0x80659A84: return 0x8B868200 | alpha;
				case 0xF8C518E4: return 0x79CDCD00 | alpha;
				case 0x60B57902: return 0x90EE9000 | alpha;
				case 0xDED79B06: return 0xFFEC8B00 | alpha;
				case 0x6A45DBC6: return 0xCDCDB400 | alpha;
				case 0x34163E0C: return 0xFFFF0000 | alpha;
				case 0x4A65DC20: return 0xCD555500 | alpha;
				case 0x6D57FB0A: return 0xEED8AE00 | alpha;
				case 0xF1D759E2: return 0xEE2C2C00 | alpha;
				case 0xFA451AA6: return 0xCD4F3900 | alpha;
				case 0x8C651E02: return 0xCD107600 | alpha;
				case 0xF8F79B6E: return 0xEE6AA700 | alpha;
				case 0xE2A45B8E: return 0x8B3A6200 | alpha;
				case 0xAA66F960: return 0xCD327800 | alpha;
				case 0x8D3518EE: return 0x68228B00 | alpha;
				case 0x86553AA8: return 0x9F79EE00 | alpha;
				case 0xBB575AEE: return 0xEED2EE00 | alpha;
				case 0x01659EA8: return 0x05050500 | alpha;
				case 0x3BA47DE0: return 0x30303000 | alpha;
				case 0x39859EC2: return 0x7A7A7A00 | alpha;
				case 0xBC555A04: return 0xB0B0B000 | alpha;
				case 0x3766BFA4: return 0xC4C4C400 | alpha;
				case 0xBA367AE6: return 0xC9C9C900 | alpha;
				case 0x8D16B842: return 0xD9D9D900 | alpha;
				case 0x8AF7D924: return 0xF2F2F200 | alpha;
				case 0xDC661DA4: return 0xF5F5F500 | alpha;
			}
		case 0x00041810:
			switch (hash)
			{
				case 0x32379DF0: return 0x69696900 | alpha;
				case 0x31A57952: return 0x00CED100 | alpha;
				case 0xB1549894: return 0xEEDD8200 | alpha;
				case 0x5DC73EFA: return 0x9932CC00 | alpha;
				case 0x9627DF16: return 0xEEE8CD00 | alpha;
				case 0x2CB6B9F8: return 0xE0EEEE00 | alpha;
				case 0x06469DBA: return 0x838B8B00 | alpha;
				case 0xFC24BC96: return 0x5CACEE00 | alpha;
				case 0x24B69D34: return 0xD1EEEE00 | alpha;
				case 0xB87519B2: return 0xD1EEEE00 | alpha;
				case 0xB59639D6: return 0x7A8B8B00 | alpha;
				case 0xFCB579DA: return 0x8EE5EE00 | alpha;
				case 0xA045FDFA: return 0xB4EEB400 | alpha;
				case 0xD2D61A74: return 0xCD816200 | alpha;
				case 0x5235BAD2: return 0xCD816200 | alpha;
				case 0x4F967A9E: return 0xEE799F00 | alpha;
				case 0x2DA57916: return 0x21212100 | alpha;
				case 0x34B71C7E: return 0x42424200 | alpha;
				case 0xE3045AD8: return 0x54545400 | alpha;
				case 0xCE6718DA: return 0x5C5C5C00 | alpha;
				case 0x2B8699F8: return 0x6B6B6B00 | alpha;
				case 0x1DB67E3C: return 0x78787800 | alpha;
				case 0x1B979F1E: return 0x91919100 | alpha;
				case 0x03151E78: return 0x99999900 | alpha;
				case 0xEE77DC7A: return 0xA1A1A100 | alpha;
				case 0x30551C3C: return 0xA3A3A300 | alpha;
				case 0x2967BADA: return 0xB5B5B500 | alpha;
				case 0x2724BBBE: return 0xCCCCCC00 | alpha;
				case 0x2E363D1E: return 0xEDEDED00 | alpha;
			}
		case 0x00080000:
			switch (hash)
			{
				case 0x02BAC220: return 0xFFFFFF00 | alpha;
				case 0x195963A2: return 0x7CFC0000 | alpha;
				case 0x1BA9E708: return 0xF0808000 | alpha;
				case 0x720847C2: return 0xAEEEEE00 | alpha;
				case 0x17E8E484: return 0x00868B00 | alpha;
				case 0x2D28A006: return 0xC0FF3E00 | alpha;
				case 0x2A49C02A: return 0x9ACD3200 | alpha;
				case 0x1CE9E662: return 0xCAFF7000 | alpha;
				case 0x6378C1E4: return 0xA2CD5A00 | alpha;
				case 0x0C99E7CE: return 0xCDCD0000 | alpha;
				case 0xC06907E4: return 0xEEB4B400 | alpha;
				case 0x6E5A84C2: return 0xFF7F2400 | alpha;
				case 0x82DAE600: return 0xFF303000 | alpha;
				case 0xB1DB856E: return 0xCD660000 | alpha;
				case 0xD81BE306: return 0x8B362600 | alpha;
				case 0x2E894082: return 0xEEA9B800 | alpha;
				case 0x2C6A6164: return 0xCD919E00 | alpha;
				case 0xF8EA4468: return 0xFF83FA00 | alpha;
				case 0x1018C5AA: return 0x7D26CD00 | alpha;
				case 0x273860AE: return 0xEED2EE00 | alpha;
				case 0x2C3BA006: return 0x03030300 | alpha;
				case 0x3A3A82C8: return 0x12121200 | alpha;
				case 0x381BA3AA: return 0x14141400 | alpha;
				case 0x685BA360: return 0x61616100 | alpha;
				case 0x270B20C0: return 0xDEDEDE00 | alpha;
				case 0x765A8622: return 0xFAFAFA00 | alpha;
			}
		case 0x00080010:
			switch (hash)
			{
				case 0x278B63DE: return 0xFFDEAD00 | alpha;
				case 0xBF4BA05A: return 0x00BFFF00 | alpha;
				case 0x177B0576: return 0x87CEFA00 | alpha;
				case 0x499B8354: return 0xBC8F8F00 | alpha;
				case 0xA9192590: return 0xB2222200 | alpha;
				case 0xE3F806B4: return 0x9400D300 | alpha;
				case 0x0188E0FA: return 0x8B898900 | alpha;
				case 0xF6CAA6BA: return 0xEED5B700 | alpha;
				case 0x253A4410: return 0xFFDEAD00 | alpha;
				case 0xC71BC1D0: return 0x7EC0EE00 | alpha;
				case 0x7109257A: return 0xC6E2FF00 | alpha;
				case 0x6E2A459E: return 0x9FB6CD00 | alpha;
				case 0x83D9217C: return 0x8DEEEE00 | alpha;
				case 0x932907FC: return 0x43CD8000 | alpha;
				case 0x2D8A8052: return 0x00FF7F00 | alpha;
				case 0x000AA6F4: return 0xEE9A4900 | alpha;
				case 0x017B2594: return 0xCD853F00 | alpha;
				case 0xD17B4530: return 0x8B3A6200 | alpha;
				case 0x5099E2FE: return 0xFF3E9600 | alpha;
				case 0x28FB27D4: return 0x1C1C1C00 | alpha;
				case 0x7CF8E55E: return 0x59595900 | alpha;
				case 0x4FD922BA: return 0x69696900 | alpha;
				case 0x4DBA439C: return 0x82828200 | alpha;
				case 0x3BA862BE: return 0xD6D6D600 | alpha;
				case 0x0E88A01A: return 0xE5E5E500 | alpha;
				case 0x215924FE: return 0x8B008B00 | alpha;
			}
		case 0x00080800:
			switch (hash)
			{
				case 0x5A29AEE8: return 0xFFE4C400 | alpha;
				case 0x4148086C: return 0xFFE4B500 | alpha;
				case 0x4D69AAC4: return 0xFFF8DC00 | alpha;
				case 0x0CA8AFC8: return 0x6495ED00 | alpha;
				case 0x8B082BC4: return 0x4682B400 | alpha;
				case 0x0019CD4A: return 0x00FFFF00 | alpha;
				case 0xDBF868E2: return 0xE0FFFF00 | alpha;
				case 0x8B98E908: return 0x5F9EA000 | alpha;
				case 0xAB88AD82: return 0x7CFC0000 | alpha;
				case 0xB4B84BE0: return 0xEEE0E500 | alpha;
				case 0x30896A0E: return 0xBFEFFF00 | alpha;
				case 0x576A8946: return 0x668B8B00 | alpha;
				case 0xF568EFC2: return 0x00E5EE00 | alpha;
				case 0x3F5A0E60: return 0x79CDCD00 | alpha;
				case 0x70DA0800: return 0x8DEEEE00 | alpha;
				case 0xEE982BE8: return 0x66CD0000 | alpha;
				case 0xDE8A6B8E: return 0xEE794200 | alpha;
				case 0x09898A4C: return 0xFFA50000 | alpha;
				case 0x06BBE8A4: return 0x8B3E2F00 | alpha;
				case 0x569B49E8: return 0xEE400000 | alpha;
				case 0x016A882E: return 0x8B000000 | alpha;
				case 0xCC1ACF8C: return 0x8B478900 | alpha;
				case 0x827BAE6C: return 0xB23AEE00 | alpha;
				case 0x2C3B8F02: return 0x03030300 | alpha;
				case 0x0189CFAA: return 0x0A0A0A00 | alpha;
				case 0x3BC8AEE2: return 0x63636300 | alpha;
				case 0x34DB4D80: return 0x75757500 | alpha;
				case 0xCC484AC0: return 0x75757500 | alpha;
				case 0xB7AB08C2: return 0x7D7D7D00 | alpha;
				case 0x39A9CFC4: return 0xADADAD00 | alpha;
				case 0xEC590E60: return 0xBABABA00 | alpha;
				case 0xD7BBCC62: return 0xC2C2C200 | alpha;
				case 0x44EA4AA8: return 0x90EE9000 | alpha;
			}
		case 0x00080810:
			switch (hash)
			{
				case 0xFF2B2F38: return 0xB0E0E600 | alpha;
				case 0x8179E99E: return 0xB8860B00 | alpha;
				case 0xC25A8E12: return 0x473C8B00 | alpha;
				case 0x6A6AAC90: return 0x104E8B00 | alpha;
				case 0x2D7A2A90: return 0x104E8B00 | alpha;
				case 0x0F78EC3C: return 0xC6E2FF00 | alpha;
				case 0x42FAE97E: return 0xC6E2FF00 | alpha;
				case 0x934B6AD0: return 0x6E7B8B00 | alpha;
				case 0x2DAA8A32: return 0x9AC0CD00 | alpha;
				case 0xC8780B18: return 0xEEC59100 | alpha;
				case 0x8A4B8DB8: return 0xFFAEB900 | alpha;
				case 0x1F198E7C: return 0xFF34B300 | alpha;
				case 0xDE5A0996: return 0x21212100 | alpha;
				case 0x2FC84E16: return 0x24242400 | alpha;
				case 0x36FA2C9E: return 0x2B2B2B00 | alpha;
				case 0x26B828B8: return 0x33333300 | alpha;
				case 0x2DA96EF8: return 0x3D3D3D00 | alpha;
				case 0x0089AC54: return 0x4D4D4D00 | alpha;
				case 0x2DC9AA18: return 0x54545400 | alpha;
				case 0xFE6ACD36: return 0x66666600 | alpha;
				case 0x9F28881C: return 0x85858500 | alpha;
				case 0x32982C5C: return 0x8C8C8C00 | alpha;
				case 0x2BAACAFA: return 0x9E9E9E00 | alpha;
				case 0x9D09A8FE: return 0x9E9E9E00 | alpha;
				case 0x30794D3E: return 0xD6D6D600 | alpha;
				case 0x298BEBDC: return 0xE8E8E800 | alpha;
				case 0x792A6958: return 0xA9A9A900 | alpha;
			}
		case 0x00081000:
			switch (hash)
			{
				case 0x9D9A73E0: return 0xFFFAF000 | alpha;
				case 0x9E09D46A: return 0xFFEBCD00 | alpha;
				case 0x3A68D4C2: return 0x483D8B00 | alpha;
				case 0x4AE917E4: return 0x00FA9A00 | alpha;
				case 0x1B0870C8: return 0xBDB76B00 | alpha;
				case 0x6DBBF44A: return 0xEEEEE000 | alpha;
				case 0x4DAB30AA: return 0xCDCDC100 | alpha;
				case 0xA888D7A0: return 0xEED5D200 | alpha;
				case 0x2C5AF4E4: return 0x79CDCD00 | alpha;
				case 0x3269B188: return 0x66CD0000 | alpha;
				case 0x7D28D0EE: return 0xFFC12500 | alpha;
				case 0x9259B7A6: return 0xEEB4B400 | alpha;
				case 0x0F885564: return 0xCD661D00 | alpha;
				case 0x75C8702C: return 0xFFA50000 | alpha;
				case 0x000B95AE: return 0x8B000000 | alpha;
				case 0xA4099280: return 0xFF149300 | alpha;
				case 0x495A558C: return 0xFF00FF00 | alpha;
				case 0x2E8A776E: return 0xEEAEEE00 | alpha;
				case 0x962833EA: return 0xB452CD00 | alpha;
				case 0xE269100A: return 0x7D26CD00 | alpha;
				case 0x3A3A93CC: return 0x12121200 | alpha;
				case 0x381BB4AE: return 0x14141400 | alpha;
				case 0x3BA873C2: return 0xD6D6D600 | alpha;
				case 0x270B31C4: return 0xDEDEDE00 | alpha;
				case 0x378AF0A6: return 0xF7F7F700 | alpha;
				case 0x765A9726: return 0xFAFAFA00 | alpha;
				case 0x4E7BB368: return 0x00008B00 | alpha;
			}
		case 0x00081010:
			switch (hash)
			{
				case 0x1DC85276: return 0x32CD3200 | alpha;
				case 0xC1E9D5FC: return 0xFF8C0000 | alpha;
				case 0x2C3AB156: return 0xFFFAFA00 | alpha;
				case 0x2A1BD238: return 0xEEE9E900 | alpha;
				case 0x9BBAB752: return 0xCDB38B00 | alpha;
				case 0x29B935F2: return 0xF0FFF000 | alpha;
				case 0x95681332: return 0x7A67EE00 | alpha;
				case 0x0148D1D8: return 0x0000FF00 | alpha;
				case 0x60EA5734: return 0x5CACEE00 | alpha;
				case 0x5E0B7758: return 0x36648B00 | alpha;
				case 0x1A5BD474: return 0x7A8B8B00 | alpha;
				case 0x617B1478: return 0x8EE5EE00 | alpha;
				case 0x5599B7B6: return 0x66CDAA00 | alpha;
				case 0xA40AF394: return 0x00CD6600 | alpha;
				case 0xFF8B57D8: return 0xEEE68500 | alpha;
				case 0x016AB236: return 0x8B5A2B00 | alpha;
				case 0x8B58745C: return 0xFF34B300 | alpha;
				case 0xDE0812B0: return 0x8B008B00 | alpha;
				case 0x26B817B4: return 0x33333300 | alpha;
				case 0x7CF8D45A: return 0x59595900 | alpha;
				case 0x685B925C: return 0x61616100 | alpha;
				case 0x4FD911B6: return 0x69696900 | alpha;
				case 0xB7AAF7BE: return 0x7D7D7D00 | alpha;
				case 0x4DBA3298: return 0x82828200 | alpha;
				case 0x9F287718: return 0x85858500 | alpha;
				case 0x9D0997FA: return 0x9E9E9E00 | alpha;
				case 0x0E88B11E: return 0xE5E5E500 | alpha;
			}
		case 0x00081800:
			switch (hash)
			{
				case 0x02B9DEA6: return 0xF0FFFF00 | alpha;
				case 0x4CA9DEE0: return 0x6A5ACD00 | alpha;
				case 0x99FA1F06: return 0xF4A46000 | alpha;
				case 0xF9EBFEAC: return 0xD0209000 | alpha;
				case 0x26FAD8A2: return 0xCDC5BF00 | alpha;
				case 0x494B1804: return 0x8B868200 | alpha;
				case 0x32CADB4C: return 0x8B8B8300 | alpha;
				case 0x2B38BF22: return 0x8B838600 | alpha;
				case 0x5E099A42: return 0x27408B00 | alpha;
				case 0x2BD818CA: return 0x00BFFF00 | alpha;
				case 0xB2E85DA0: return 0x00FF0000 | alpha;
				case 0xAF4BF800: return 0xBCEE6800 | alpha;
				case 0x8B783C42: return 0x6E8B3D00 | alpha;
				case 0x048B5F08: return 0xCDBE7000 | alpha;
				case 0x3A499D6E: return 0xCDCD0000 | alpha;
				case 0x4C0B1FE8: return 0x8B696900 | alpha;
				case 0xFF983944: return 0xEE5C4200 | alpha;
				case 0x000A7CEC: return 0xEE000000 | alpha;
				case 0x017AFB8C: return 0xCD000000 | alpha;
				case 0x014BFE02: return 0xFFB5C500 | alpha;
				case 0x754A3EA0: return 0x8B475D00 | alpha;
				case 0x4F995868: return 0xE066FF00 | alpha;
				case 0xA18BFFAC: return 0x68228B00 | alpha;
				case 0x0189BEA6: return 0x0A0A0A00 | alpha;
				case 0x32983D60: return 0x8C8C8C00 | alpha;
				case 0x39A9BEC0: return 0xADADAD00 | alpha;
				case 0x30795E42: return 0xD6D6D600 | alpha;
				case 0x298BFCE0: return 0xE8E8E800 | alpha;
				case 0x378ADFA2: return 0xF7F7F700 | alpha;
			}
		case 0x00081810:
			switch (hash)
			{
				case 0xA909BC34: return 0x87CEFA00 | alpha;
				case 0xE9F97A9C: return 0xB0C4DE00 | alpha;
				case 0x9869BABA: return 0xB0C4DE00 | alpha;
				case 0xACAABB70: return 0x40E0D000 | alpha;
				case 0x7E299CD6: return 0xEEE8CD00 | alpha;
				case 0x8B391A16: return 0x838B8300 | alpha;
				case 0x60E87A1E: return 0x436EEE00 | alpha;
				case 0x9A7B9872: return 0x9AC0CD00 | alpha;
				case 0x2CCBBF76: return 0x7A8B8B00 | alpha;
				case 0x996B3D56: return 0x66CDAA00 | alpha;
				case 0xB668FE9C: return 0xC1FFC100 | alpha;
				case 0x01481F96: return 0xFFD70000 | alpha;
				case 0x000BBFB6: return 0x8B5A2B00 | alpha;
				case 0x1F185C3A: return 0xFF8C6900 | alpha;
				case 0x254BBB9C: return 0xCD705400 | alpha;
				case 0x2C6B9850: return 0xCD96CD00 | alpha;
				case 0x28FB38D8: return 0x1C1C1C00 | alpha;
				case 0xDE5A1A9A: return 0x21212100 | alpha;
				case 0x2FC85F1A: return 0x24242400 | alpha;
				case 0x36FA1B9A: return 0x2B2B2B00 | alpha;
				case 0x2DA97FFC: return 0x3D3D3D00 | alpha;
				case 0x0089BD58: return 0x4D4D4D00 | alpha;
				case 0x2DC9BB1C: return 0x54545400 | alpha;
				case 0x3BC89DDE: return 0x63636300 | alpha;
				case 0xFE6ADE3A: return 0x66666600 | alpha;
				case 0x34DB3C7C: return 0x75757500 | alpha;
				case 0xCC4839BC: return 0x75757500 | alpha;
				case 0x2BAADBFE: return 0x9E9E9E00 | alpha;
				case 0xEC58FD5C: return 0xBABABA00 | alpha;
				case 0xD7BBBB5E: return 0xC2C2C200 | alpha;
			}
		case 0x000C0000:
			switch (hash)
			{
				case 0x376C46CE: return 0xFFE4E100 | alpha;
				case 0x4D1E85AE: return 0x4169E100 | alpha;
				case 0xCA8FE000: return 0xEED5D200 | alpha;
				case 0x8B3D80EE: return 0x00B2EE00 | alpha;
				case 0xB71F268E: return 0xBCD2EE00 | alpha;
				case 0x67ACE16C: return 0xA2B5CD00 | alpha;
				case 0x31FC81C4: return 0x008B0000 | alpha;
				case 0xF15C2448: return 0x458B0000 | alpha;
				case 0x914C8608: return 0xC0FF3E00 | alpha;
				case 0x11ED066C: return 0xEEEE0000 | alpha;
				case 0x224FC2A6: return 0x8B696900 | alpha;
				case 0x766FA704: return 0xCD661D00 | alpha;
				case 0x937EC1C4: return 0x8B451300 | alpha;
				case 0x099DE422: return 0xEE2C2C00 | alpha;
				case 0x2D2C04E2: return 0xEE6A5000 | alpha;
				case 0x31CC2208: return 0xEE400000 | alpha;
				case 0x58AF0540: return 0xCD327800 | alpha;
				case 0xDB6E610A: return 0x9F79EE00 | alpha;
				case 0x2A1CC0E8: return 0x05050500 | alpha;
				case 0x01AE00AC: return 0x0F0F0F00 | alpha;
				case 0x663CC442: return 0x7A7A7A00 | alpha;
				case 0x36FE2280: return 0xA3A3A300 | alpha;
				case 0x886C6700: return 0xA6A6A600 | alpha;
				case 0x864D87E2: return 0xBFBFBF00 | alpha;
				case 0x39CE00C6: return 0xE0E0E000 | alpha;
				case 0x570EE620: return 0xE8E8E800 | alpha;
				case 0x24EC41A2: return 0xF7F7F700 | alpha;
				case 0xD84D418C: return 0x008B8B00 | alpha;
			}
		case 0x000C0010:
			switch (hash)
			{
				case 0x031DE11C: return 0x00000000 | alpha;
				case 0x001FE596: return 0xBEBEBE00 | alpha;
				case 0xFF2C837C: return 0x1E90FF00 | alpha;
				case 0x9EFC047E: return 0x87CEEB00 | alpha;
				case 0x84EC60F8: return 0x9370DB00 | alpha;
				case 0xFC1DC558: return 0xFFE4C400 | alpha;
				case 0xE55CC7B0: return 0xFFDEAD00 | alpha;
				case 0x9E3D0158: return 0x8B887800 | alpha;
				case 0xB24CE716: return 0xF0FFFF00 | alpha;
				case 0x27BCE3F8: return 0x0000FF00 | alpha;
				case 0x016D02DA: return 0x0000CD00 | alpha;
				case 0xD2EFE03C: return 0x9FB6CD00 | alpha;
				case 0x015F865C: return 0x00EEEE00 | alpha;
				case 0xA98CE57E: return 0x528B8B00 | alpha;
				case 0x4C8D65D0: return 0xFFB90F00 | alpha;
				case 0xFD9CA3FC: return 0xFF6A6A00 | alpha;
				case 0x1FFD6758: return 0xFF404000 | alpha;
				case 0xFFECA3B8: return 0xEE3B3B00 | alpha;
				case 0xFCEF249A: return 0xEE826200 | alpha;
				case 0xF79C05FC: return 0xCD705400 | alpha;
				case 0x36DD6474: return 0xCD816200 | alpha;
				case 0x6DCC87DE: return 0xCD327800 | alpha;
				case 0x829C4530: return 0x8B008B00 | alpha;
				case 0x784E8318: return 0x26262600 | alpha;
				case 0xC9BCC798: return 0x29292900 | alpha;
				case 0x4B2EC074: return 0x36363600 | alpha;
				case 0x490FE156: return 0x4F4F4F00 | alpha;
				case 0x9A7E25D6: return 0x52525200 | alpha;
				case 0x985F46B8: return 0x6B6B6B00 | alpha;
				case 0x391D019E: return 0x8A8A8A00 | alpha;
				case 0x07BF80BE: return 0xCCCCCC00 | alpha;
				case 0x592DC53E: return 0xCFCFCF00 | alpha;
				case 0x324F4678: return 0xA9A9A900 | alpha;
			}
		case 0x000C0800:
			switch (hash)
			{
				case 0xFE4EAAEC: return 0x69696900 | alpha;
				case 0xD48EAEE2: return 0x228B2200 | alpha;
				case 0x318F0CAA: return 0xE9967A00 | alpha;
				case 0x039FCBA2: return 0xFFDAB900 | alpha;
				case 0xE46D2CA0: return 0xFFDAB900 | alpha;
				case 0xE18E4CC4: return 0xCDAF9500 | alpha;
				case 0x427C298A: return 0xCDC9A500 | alpha;
				case 0xDF2C0DEA: return 0xCDC9A500 | alpha;
				case 0x3A2D4BE2: return 0x8B838600 | alpha;
				case 0x71CFEBA8: return 0xA4D3EE00 | alpha;
				case 0xBF8F8E66: return 0x8DB6CD00 | alpha;
				case 0x401C09A2: return 0x9FB6CD00 | alpha;
				case 0x968DCC02: return 0x528B8B00 | alpha;
				case 0x9EFE2E88: return 0xCDBE7000 | alpha;
				case 0x04CEEAE2: return 0xFF7F2400 | alpha;
				case 0x0FBCE9AE: return 0xCD850000 | alpha;
				case 0xD16DEE2A: return 0xCD69C900 | alpha;
				case 0x02CDECAA: return 0xB23AEE00 | alpha;
				case 0xE7BC2EA8: return 0x912CEE00 | alpha;
				case 0x6B0E4D4C: return 0xFFE1FF00 | alpha;
				case 0x2A1CAFE4: return 0x05050500 | alpha;
				case 0x01ADEFA8: return 0x0F0F0F00 | alpha;
				case 0x3BECCEE0: return 0x96969600 | alpha;
				case 0xB58C29A4: return 0x96969600 | alpha;
				case 0x32BC6E62: return 0xBFBFBF00 | alpha;
				case 0x2BCF0D00: return 0xD1D1D100 | alpha;
				case 0xD59CED44: return 0xDBDBDB00 | alpha;
				case 0x39CDEFC2: return 0xE0E0E000 | alpha;
				case 0xC0FFAB46: return 0xE3E3E300 | alpha;
				case 0xA87D2AA0: return 0xEBEBEB00 | alpha;
				case 0xBFFCA922: return 0xFFFFFF00 | alpha;
				case 0xE79DE82C: return 0x008B8B00 | alpha;
			}
		case 0x000C0810:
			switch (hash)
			{
				case 0xFA0D6C7C: return 0x1E90FF00 | alpha;
				case 0x7E5D8D7E: return 0x87CEEB00 | alpha;
				case 0x032F2990: return 0xFF7F5000 | alpha;
				case 0xE90DEDB6: return 0xFF450000 | alpha;
				case 0xE70EA9DC: return 0xFF69B400 | alpha;
				case 0xC8ED6C3A: return 0x8A2BE200 | alpha;
				case 0x178E0E7E: return 0x9FB6CD00 | alpha;
				case 0xAB8E0DB0: return 0x6E7B8B00 | alpha;
				case 0x904F2BDE: return 0x9BCD9B00 | alpha;
				case 0x900CCDDA: return 0x43CD8000 | alpha;
				case 0xA24D0DF0: return 0x8B691400 | alpha;
				case 0x113DCC9A: return 0xFFAEB900 | alpha;
				case 0x876CADDC: return 0xCD8C9500 | alpha;
				case 0x254CEDDE: return 0xCD299000 | alpha;
				case 0xFFBC0A70: return 0x8B7B8B00 | alpha;
				case 0xFBDF6C16: return 0x1A1A1A00 | alpha;
				case 0x324FCA58: return 0x26262600 | alpha;
				case 0x300CCB3C: return 0x3D3D3D00 | alpha;
				case 0xC79DE87A: return 0x42424200 | alpha;
				case 0x190C2CFA: return 0x45454500 | alpha;
				case 0x291F69DA: return 0x4F4F4F00 | alpha;
				case 0x371E4C9C: return 0x5E5E5E00 | alpha;
				case 0x16ED4DDC: return 0x5E5E5E00 | alpha;
				case 0x26DC48B6: return 0x66666600 | alpha;
				case 0xE9CD8B38: return 0x6E6E6E00 | alpha;
				case 0xE7AEAC1A: return 0x87878700 | alpha;
				case 0x2DEDEC1E: return 0x87878700 | alpha;
				case 0x34FF6D7E: return 0xA8A8A800 | alpha;
				case 0x09DE4ED8: return 0xB3B3B300 | alpha;
				case 0x07BF6FBA: return 0xCCCCCC00 | alpha;
			}
		case 0x000C1000:
			switch (hash)
			{
				case 0x001EF6E6: return 0xFFFAFA00 | alpha;
				case 0x2E5D5000: return 0xFFFAF000 | alpha;
				case 0x1D7D7704: return 0xF0F8FF00 | alpha;
				case 0x5F0F570A: return 0x70809000 | alpha;
				case 0xC4DDD10C: return 0x9ACD3200 | alpha;
				case 0xA3BE1688: return 0xFFFACD00 | alpha;
				case 0x989D3268: return 0xFFFACD00 | alpha;
				case 0x0A6F9262: return 0x8B7D7B00 | alpha;
				case 0xC2CF34E0: return 0x27408B00 | alpha;
				case 0x8EBC178E: return 0x1C86EE00 | alpha;
				case 0x7F8FB14E: return 0x00B2EE00 | alpha;
				case 0x64FF322E: return 0xBCD2EE00 | alpha;
				case 0xFD7E1204: return 0x00868B00 | alpha;
				case 0xC29C33C4: return 0x548B5400 | alpha;
				case 0x4CDCD722: return 0x00CD0000 | alpha;
				case 0x586F5306: return 0xFFEC8B00 | alpha;
				case 0xEE9D34C4: return 0xFFFFE000 | alpha;
				case 0x859E3224: return 0xCDCDB400 | alpha;
				case 0x139D370E: return 0xFFC12500 | alpha;
				case 0x9C1DD040: return 0xCD555500 | alpha;
				case 0x2DBC90CA: return 0xEED8AE00 | alpha;
				case 0x074C748C: return 0x8B7E6600 | alpha;
				case 0xE20D340E: return 0xCD850000 | alpha;
				case 0x131D726C: return 0xFF7F0000 | alpha;
				case 0xC08E738A: return 0xEE7AE900 | alpha;
				case 0x014D34EE: return 0xFFBBFF00 | alpha;
				case 0x7A2C740C: return 0x5D478B00 | alpha;
				case 0x24EC52A6: return 0xF7F7F700 | alpha;
			}
		case 0x000C1010:
			switch (hash)
			{
				case 0x001FD492: return 0xBEBEBE00 | alpha;
				case 0x475C9670: return 0x48D1CC00 | alpha;
				case 0x1B2ED196: return 0x6B8E2300 | alpha;
				case 0xEF5D9534: return 0x8B451300 | alpha;
				case 0x03BFB578: return 0xF5DEB300 | alpha;
				case 0x46BFB5F8: return 0x9370DB00 | alpha;
				case 0xCF4E507C: return 0x8B7D6B00 | alpha;
				case 0x541E9796: return 0x838B8300 | alpha;
				case 0x0D4E723E: return 0xEED5D200 | alpha;
				case 0x9D7D3574: return 0x473C8B00 | alpha;
				case 0x95DE9716: return 0x5CACEE00 | alpha;
				case 0x966F545A: return 0x8EE5EE00 | alpha;
				case 0x5E9C349C: return 0x53868B00 | alpha;
				case 0x585DB016: return 0x458B7400 | alpha;
				case 0x997FD15A: return 0x8B864E00 | alpha;
				case 0x27BC31B6: return 0xFFD70000 | alpha;
				case 0x016C5098: return 0xCDAD0000 | alpha;
				case 0x332FB358: return 0x8B750000 | alpha;
				case 0x853DF330: return 0xCD9B1D00 | alpha;
				case 0x0C8E9112: return 0xCD950C00 | alpha;
				case 0xB70E1550: return 0x8B472600 | alpha;
				case 0x4C6E7778: return 0xCDAA7D00 | alpha;
				case 0xC05CF132: return 0xFFA07A00 | alpha;
				case 0x784E941C: return 0x26262600 | alpha;
				case 0x4B2ED178: return 0x36363600 | alpha;
				case 0x490FF25A: return 0x4F4F4F00 | alpha;
				case 0x9A7E36DA: return 0x52525200 | alpha;
				case 0x985F57BC: return 0x6B6B6B00 | alpha;
				case 0x663CB33E: return 0x7A7A7A00 | alpha;
				case 0x391CF09A: return 0x8A8A8A00 | alpha;
				case 0x36FE117C: return 0xA3A3A300 | alpha;
				case 0x886C55FC: return 0xA6A6A600 | alpha;
				case 0x864D76DE: return 0xBFBFBF00 | alpha;
				case 0x592DB43A: return 0xCFCFCF00 | alpha;
				case 0x570ED51C: return 0xE8E8E800 | alpha;
			}
		case 0x000C1800:
			switch (hash)
			{
				case 0xCBCE3D2A: return 0xD3D3D300 | alpha;
				case 0x2E4DBDA4: return 0x66CDAA00 | alpha;
				case 0x2A0FD86A: return 0x3CB37100 | alpha;
				case 0x640E1D20: return 0xFFA07A00 | alpha;
				case 0x153F3C0E: return 0xC7158500 | alpha;
				case 0xE57FDDA8: return 0xFFEFDB00 | alpha;
				case 0x2C0EB92A: return 0xCDC0B000 | alpha;
				case 0x06EF3C28: return 0xCDC9A500 | alpha;
				case 0x95DCBA00: return 0x436EEE00 | alpha;
				case 0x71DE1CEE: return 0x7EC0EE00 | alpha;
				case 0x108DFEAA: return 0x607B8B00 | alpha;
				case 0x866C7BE0: return 0x00F5FF00 | alpha;
				case 0x0D2F7A02: return 0x00E5EE00 | alpha;
				case 0x6CED9AC2: return 0x00EE0000 | alpha;
				case 0x8F0F5AC8: return 0x9ACD3200 | alpha;
				case 0xA37ED924: return 0xA2CD5A00 | alpha;
				case 0x0F1DBEE2: return 0xFFFFE000 | alpha;
				case 0x9A6ED9E8: return 0x8B696900 | alpha;
				case 0xF9EC7C24: return 0x8B1A1A00 | alpha;
				case 0xA36C3C00: return 0xFF149300 | alpha;
				case 0xDA8F394C: return 0xEE6AA700 | alpha;
				case 0x2FCCDE2E: return 0xEE6AA700 | alpha;
				case 0xC03FD86A: return 0x551A8B00 | alpha;
				case 0x371E5DA0: return 0x5E5E5E00 | alpha;
				case 0x16ED5EE0: return 0x5E5E5E00 | alpha;
				case 0xB58C18A0: return 0x96969600 | alpha;
				case 0x3BECDFE4: return 0x96969600 | alpha;
				case 0x34FF7E82: return 0xA8A8A800 | alpha;
				case 0xD59CDC40: return 0xDBDBDB00 | alpha;
				case 0xC0FF9A42: return 0xE3E3E300 | alpha;
				case 0xBFFCBA26: return 0xFFFFFF00 | alpha;
			}
		case 0x000C1810:
			switch (hash)
			{
				case 0x3E7F98BE: return 0xF5FFFA00 | alpha;
				case 0xFB7EDBD6: return 0x8470FF00 | alpha;
				case 0x1E8F9B9E: return 0xADD8E600 | alpha;
				case 0xFA0C1838: return 0xB0E0E600 | alpha;
				case 0xE57EB916: return 0xFF450000 | alpha;
				case 0xE30CDFF8: return 0xBA55D300 | alpha;
				case 0x3CBD1D34: return 0xFFF8DC00 | alpha;
				case 0x31CE5834: return 0xC1CDC100 | alpha;
				case 0xFBAE38B2: return 0x7A67EE00 | alpha;
				case 0xD1CC5C70: return 0x00688B00 | alpha;
				case 0x3B9CFC50: return 0x7EC0EE00 | alpha;
				case 0x53AF7F14: return 0xD1EEEE00 | alpha;
				case 0x30DFD8FC: return 0x00CDCD00 | alpha;
				case 0x1F9C1B78: return 0xFFF68F00 | alpha;
				case 0x960E1DD0: return 0xFFB90F00 | alpha;
				case 0x97FFBBD0: return 0xCD950C00 | alpha;
				case 0x70EF5FB2: return 0xFFA07A00 | alpha;
				case 0xF79D383E: return 0xCD299000 | alpha;
				case 0xFBDF5B12: return 0x1A1A1A00 | alpha;
				case 0x324FDB5C: return 0x26262600 | alpha;
				case 0xC9BCD89C: return 0x29292900 | alpha;
				case 0x300CBA38: return 0x3D3D3D00 | alpha;
				case 0xC79DF97E: return 0x42424200 | alpha;
				case 0x190C3DFE: return 0x45454500 | alpha;
				case 0x291F58D6: return 0x4F4F4F00 | alpha;
				case 0x26DC59BA: return 0x66666600 | alpha;
				case 0xE9CD9C3C: return 0x6E6E6E00 | alpha;
				case 0x2DEDDB1A: return 0x87878700 | alpha;
				case 0xE7AEBD1E: return 0x87878700 | alpha;
				case 0x09DE5FDC: return 0xB3B3B300 | alpha;
				case 0x32BC5D5E: return 0xBFBFBF00 | alpha;
				case 0x2BCEFBFC: return 0xD1D1D100 | alpha;
				case 0xA87D199C: return 0xEBEBEB00 | alpha;
			}
	}
}

