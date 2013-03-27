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
	14/04/12:
		Added pre-cached values from Slice to improve compilation speed.
	29/11/10:
		Added the ability to use "X11" prefixes in strings.
		Added colourspace resolution for converting {FF0000} to ~r~.
	25/11/10:
		First version.
</remarks>
\**--------------------------------------------------------------------------**/

		switch (hash)
		{
			// cached
			case 0x001EF6E6: return alpha | 0xFFFAFAAA;
			case 0xA087FD85: return alpha | 0xF8F8FFAA;
			case 0xCB44D544: return alpha | 0xF8F8FFAA;
			case 0x384FD5A5: return alpha | 0xF8F8FFAA;
			case 0x8832925F: return alpha | 0xF5F5F5AA;
			case 0xCA2199DE: return alpha | 0xF5F5F5AA;
			case 0x372C9A3F: return alpha | 0xF5F5F5AA;
			case 0xFCA9ADE3: return alpha | 0xDCDCDCAA;
			case 0x9D9A73E0: return alpha | 0xFFFAF0AA;
			case 0x1FF2437F: return alpha | 0xFFFAF0AA;
			case 0x2E5D5000: return alpha | 0xFFFAF0AA;
			case 0x743D3E33: return alpha | 0xFDF5E6AA;
			case 0xFBF3B0B2: return alpha | 0xFDF5E6AA;
			case 0xFBD124D3: return alpha | 0xFDF5E6AA;
			case 0x03557A55: return alpha | 0xFAF0E6AA;
			case 0x64A333B7: return alpha | 0xFAEBD7AA;
			case 0x31F4F736: return alpha | 0xFAEBD7AA;
			case 0x0DC193D7: return alpha | 0xFAEBD7AA;
			case 0x2F0A3A93: return alpha | 0xFFEFD5AA;
			case 0xDF532D12: return alpha | 0xFFEFD5AA;
			case 0xEDBE3993: return alpha | 0xFFEFD5AA;
			case 0x753F89CB: return alpha | 0xFFEBCDAA;
			case 0x9E09D46A: return alpha | 0xFFEBCDAA;
			case 0xF36A052B: return alpha | 0xFFEBCDAA;
			case 0x5A29AEE8: return alpha | 0xFFE4C4AA;
			case 0xBEEC2871: return alpha | 0xFFDAB9AA;
			case 0xD2735E30: return alpha | 0xFFDAB9AA;
			case 0x3F7E5E91: return alpha | 0xFFDAB9AA;
			case 0xA533943F: return alpha | 0xFFDEADAA;
			case 0x278B63DE: return alpha | 0xFFDEADAA;
			case 0x35F6705F: return alpha | 0xFFDEADAA;
			case 0x4148086C: return alpha | 0xFFE4B5AA;
			case 0x4D69AAC4: return alpha | 0xFFF8DCAA;
			case 0x0423AEB8: return alpha | 0xFFFFF0AA;
			case 0x5E6E74F7: return alpha | 0xFFFACDAA;
			case 0x53D3E836: return alpha | 0xFFFACDAA;
			case 0xC0DEE897: return alpha | 0xFFFACDAA;
			case 0x2F9243F0: return alpha | 0xFFF5EEAA;
			case 0x3A65C382: return alpha | 0xF0FFF0AA;
			case 0x85BFABFF: return alpha | 0xF5FFFAAA;
			case 0x3E7F98BE: return alpha | 0xF5FFFAAA;
			case 0x3A0B90FF: return alpha | 0xF5FFFAAA;
			case 0x02B9DEA6: return alpha | 0xF0FFFFAA;
			case 0x4CA0AE65: return alpha | 0xF0F8FFAA;
			case 0x1D7D7704: return alpha | 0xF0F8FFAA;
			case 0x8A887765: return alpha | 0xF0F8FFAA;
			case 0x9C55ADD0: return alpha | 0xE6E6FAAA;
			case 0x8A343E8E: return alpha | 0xFFF0F5AA;
			case 0xF0A6258D: return alpha | 0xFFF0F5AA;
			case 0x4606564E: return alpha | 0xFFF0F5AA;
			case 0x81D1ABAE: return alpha | 0xFFE4E1AA;
			case 0xCA61466D: return alpha | 0xFFE4E1AA;
			case 0x376C46CE: return alpha | 0xFFE4E1AA;
			case 0x02BAC220: return alpha | 0xFFFFFFAA;
			case 0x031DE11C: return alpha | 0x000000AA;
			case 0xCF335C6D: return alpha | 0x2F4F4FAA;
			case 0x2F72EB0B: return alpha | 0x2F4F4FAA;
			case 0x592E484D: return alpha | 0x2F4F4FAA;
			case 0x9300D1F1: return alpha | 0x2F4F4FAA;
			case 0x1C73D18F: return alpha | 0x2F4F4FAA;
			case 0x462F2ED1: return alpha | 0x2F4F4FAA;
			case 0x7450B48C: return alpha | 0x696969AA;
			case 0xFE7136CB: return alpha | 0x696969AA;
			case 0xFE4EAAEC: return alpha | 0x696969AA;
			case 0x7DA55710: return alpha | 0x696969AA;
			case 0x325A29CF: return alpha | 0x696969AA;
			case 0x32379DF0: return alpha | 0x696969AA;
			case 0xCAC5490B: return alpha | 0x708090AA;
			case 0x5F0F570A: return alpha | 0x708090AA;
			case 0xCC1A576B: return alpha | 0x708090AA;
			case 0x7BCC9C8F: return alpha | 0x708090AA;
			case 0x31011B0E: return alpha | 0x708090AA;
			case 0x9E0C1B6F: return alpha | 0x708090AA;
			case 0xB63C6543: return alpha | 0x778899AA;
			case 0x1E6DC7A1: return alpha | 0x778899AA;
			case 0x7F94CD23: return alpha | 0x778899AA;
			case 0xF3B88B47: return alpha | 0x778899AA;
			case 0xAB8B7EA5: return alpha | 0x778899AA;
			case 0x0CB28427: return alpha | 0x778899AA;
			case 0x001FD492: return alpha | 0xBEBEBEAA;
			case 0x001FE596: return alpha | 0xBEBEBEAA;
			case 0x7CD590AE: return alpha | 0xD3D3D3AA;
			case 0x320A0F2D: return alpha | 0xD3D3D3AA;
			case 0x9F150F8E: return alpha | 0xD3D3D3AA;
			case 0xCBCE3D2A: return alpha | 0xD3D3D3AA;
			case 0x60184B29: return alpha | 0xD3D3D3AA;
			case 0xCD234B8A: return alpha | 0xD3D3D3AA;
			case 0x3C27AA5B: return alpha | 0x191970AA;
			case 0x1D86A29A: return alpha | 0x191970AA;
			case 0x72E6D35B: return alpha | 0x191970AA;
			case 0x00202BBD: return alpha | 0x000080AA;
			case 0x7E7CC105: return alpha | 0x000080AA;
			case 0x4E8371C4: return alpha | 0x000080AA;
			case 0x4A0F6A05: return alpha | 0x000080AA;
			case 0x0CA8AFC8: return alpha | 0x6495EDAA;
			case 0xC1A6B3C7: return alpha | 0x6495EDAA;
			case 0xEFD618C8: return alpha | 0x6495EDAA;
			case 0x3A68D4C2: return alpha | 0x483D8BAA;
			case 0x3DE7CCA0: return alpha | 0x483D8BAA;
			case 0x67A329E2: return alpha | 0x483D8BAA;
			case 0x4CA9DEE0: return alpha | 0x6A5ACDAA;
			case 0x1D86A77F: return alpha | 0x6A5ACDAA;
			case 0x8A91A7E0: return alpha | 0x6A5ACDAA;
			case 0x7CD61441: return alpha | 0x7B68EEAA;
			case 0x5BF27B9F: return alpha | 0x7B68EEAA;
			case 0xE1FA3161: return alpha | 0x7B68EEAA;
			case 0x8820E838: return alpha | 0x8470FFAA;
			case 0xFB7EDBD6: return alpha | 0x8470FFAA;
			case 0x5CA5E158: return alpha | 0x8470FFAA;
			case 0xF4A557E8: return alpha | 0x0000CDAA;
			case 0xE11B3467: return alpha | 0x0000CDAA;
			case 0xEF8640E8: return alpha | 0x0000CDAA;
			case 0x4D1E85AE: return alpha | 0x4169E1AA;
			case 0x1DFB4E4D: return alpha | 0x4169E1AA;
			case 0x8B064EAE: return alpha | 0x4169E1AA;
			case 0x00153147: return alpha | 0x0000FFAA;
			case 0xFF2C837C: return alpha | 0x1E90FFAA;
			case 0xEBA25FFB: return alpha | 0x1E90FFAA;
			case 0xFA0D6C7C: return alpha | 0x1E90FFAA;
			case 0x0E73207C: return alpha | 0x00BFFFAA;
			case 0xBF4BA05A: return alpha | 0x00BFFFAA;
			case 0x1037C95C: return alpha | 0x00BFFFAA;
			case 0x9EFC047E: return alpha | 0x87CEEBAA;
			case 0x7E80195D: return alpha | 0x87CEEBAA;
			case 0x7E5D8D7E: return alpha | 0x87CEEBAA;
			case 0xDD214096: return alpha | 0x87CEFAAA;
			case 0xA909BC34: return alpha | 0x87CEFAAA;
			case 0x177B0576: return alpha | 0x87CEFAAA;
			case 0x4D2062C4: return alpha | 0x4682B4AA;
			case 0x1DFD2B63: return alpha | 0x4682B4AA;
			case 0x8B082BC4: return alpha | 0x4682B4AA;
			case 0xE9F97A9C: return alpha | 0xB0C4DEAA;
			case 0x9869BABA: return alpha | 0xB0C4DEAA;
			case 0xF990C03C: return alpha | 0xB0C4DEAA;
			case 0x4DB2D2FF: return alpha | 0xADD8E6AA;
			case 0x1E8F9B9E: return alpha | 0xADD8E6AA;
			case 0x8B9A9BFF: return alpha | 0xADD8E6AA;
			case 0xFF2B2F38: return alpha | 0xB0E0E6AA;
			case 0xEBA10BB7: return alpha | 0xB0E0E6AA;
			case 0xFA0C1838: return alpha | 0xB0E0E6AA;
			case 0x31A21592: return alpha | 0xAFEEEEAA;
			case 0x67B79B71: return alpha | 0xAFEEEEAA;
			case 0x634393B2: return alpha | 0xAFEEEEAA;
			case 0x31A57952: return alpha | 0x00CED1AA;
			case 0x67BAFF31: return alpha | 0x00CED1AA;
			case 0x6346F772: return alpha | 0x00CED1AA;
			case 0x35CE1CD1: return alpha | 0x48D1CCAA;
			case 0x475C9670: return alpha | 0x48D1CCAA;
			case 0x55C7A2F1: return alpha | 0x48D1CCAA;
			case 0xACAABB70: return alpha | 0x40E0D0AA;
			case 0x0019CD4A: return alpha | 0x00FFFFAA;
			case 0xDBF868E2: return alpha | 0xE0FFFFAA;
			case 0x7587EDE1: return alpha | 0xE0FFFFAA;
			case 0xE292EE42: return alpha | 0xE0FFFFAA;
			case 0x4DB12008: return alpha | 0x5F9EA0AA;
			case 0x1E8DE8A7: return alpha | 0x5F9EA0AA;
			case 0x8B98E908: return alpha | 0x5F9EA0AA;
			case 0x0DD22D24: return alpha | 0x66CDAAAA;
			case 0x1FE2B123: return alpha | 0x66CDAAAA;
			case 0x2E4DBDA4: return alpha | 0x66CDAAAA;
			case 0xB389C983: return alpha | 0x7FFFD4AA;
			case 0xAB86F312: return alpha | 0x006400AA;
			case 0x1DCBB0F1: return alpha | 0x006400AA;
			case 0x1957A932: return alpha | 0x006400AA;
			case 0x452B9C91: return alpha | 0x556B2FAA;
			case 0xCE1EF36F: return alpha | 0x556B2FAA;
			case 0xF7DA50B1: return alpha | 0x556B2FAA;
			case 0xAC41774B: return alpha | 0x8FBC8FAA;
			case 0x95F551A9: return alpha | 0x8FBC8FAA;
			case 0xE6E17AAB: return alpha | 0x8FBC8FAA;
			case 0xEDECA4E9: return alpha | 0x2E8B57AA;
			case 0xAB91A2E8: return alpha | 0x2E8B57AA;
			case 0xAB6F1709: return alpha | 0x2E8B57AA;
			case 0xC7617D0A: return alpha | 0x3CB371AA;
			case 0xED7566E8: return alpha | 0x3CB371AA;
			case 0x2A0FD86A: return alpha | 0x3CB371AA;
			case 0x350DDBE1: return alpha | 0x20B2AAAA;
			case 0x553D01FF: return alpha | 0x20B2AAAA;
			case 0xC3AE4B41: return alpha | 0x20B2AAAA;
			case 0xAB838F52: return alpha | 0x98FB98AA;
			case 0x1DC84D31: return alpha | 0x98FB98AA;
			case 0x19544572: return alpha | 0x98FB98AA;
			case 0x9F77A443: return alpha | 0x00FF7FAA;
			case 0xB5E355E2: return alpha | 0x00FF7FAA;
			case 0xC44E6263: return alpha | 0x00FF7FAA;
			case 0xAB88AD82: return alpha | 0x7CFC00AA;
			case 0x1DCD6B61: return alpha | 0x7CFC00AA;
			case 0x195963A2: return alpha | 0x7CFC00AA;
			case 0x03555530: return alpha | 0x00FF00AA;
			case 0x4C883DB5: return alpha | 0x7FFF00AA;
			case 0x4AE917E4: return alpha | 0x00FA9AAA;
			case 0x90F4BCA2: return alpha | 0x00FA9AAA;
			case 0x0A919A84: return alpha | 0x00FA9AAA;
			case 0xAE05C1CC: return alpha | 0xADFF2FAA;
			case 0x970854EB: return alpha | 0xADFF2FAA;
			case 0x0413554C: return alpha | 0xADFF2FAA;
			case 0xAB839497: return alpha | 0x32CD32AA;
			case 0x1DC85276: return alpha | 0x32CD32AA;
			case 0x19544AB7: return alpha | 0x32CD32AA;
			case 0xC4DDD10C: return alpha | 0x9ACD32AA;
			case 0xDB4982AB: return alpha | 0x9ACD32AA;
			case 0xE9B48F2C: return alpha | 0x9ACD32AA;
			case 0xBE22FD43: return alpha | 0x228B22AA;
			case 0xD48EAEE2: return alpha | 0x228B22AA;
			case 0xE2F9BB63: return alpha | 0x228B22AA;
			case 0x4C98E2D7: return alpha | 0x6B8E23AA;
			case 0x1B2ED196: return alpha | 0x6B8E23AA;
			case 0x8839D1F7: return alpha | 0x6B8E23AA;
			case 0xA3AF9409: return alpha | 0xBDB76BAA;
			case 0x1B0870C8: return alpha | 0xBDB76BAA;
			case 0x16946909: return alpha | 0xBDB76BAA;
			case 0x02FE12A7: return alpha | 0xF0E68CAA;
			case 0xA6C6E65F: return alpha | 0xEEE8AAAA;
			case 0x817685DE: return alpha | 0xEEE8AAAA;
			case 0x7D027E1F: return alpha | 0xEEE8AAAA;
			case 0x1D0B6551: return alpha | 0xFAFAD2AA;
			case 0xCECABE0F: return alpha | 0xFAFAD2AA;
			case 0x3AC16C11: return alpha | 0xFAFAD2AA;
			case 0xAE740153: return alpha | 0xFFFFE0AA;
			case 0x97769472: return alpha | 0xFFFFE0AA;
			case 0x048194D3: return alpha | 0xFFFFE0AA;
			case 0x83B71B1B: return alpha | 0xFFFF00AA;
			case 0x00147F05: return alpha | 0xFFD700AA;
			case 0x80B10935: return alpha | 0xEEDD82AA;
			case 0xB1549894: return alpha | 0xEEDD82AA;
			case 0x1E5F98F5: return alpha | 0xEEDD82AA;
			case 0x38752DBD: return alpha | 0xDAA520AA;
			case 0xA6CA4A1F: return alpha | 0xB8860BAA;
			case 0x8179E99E: return alpha | 0xB8860BAA;
			case 0x7D05E1DF: return alpha | 0xB8860BAA;
			case 0x499B8354: return alpha | 0xBC8F8FAA;
			case 0x7D7BDC13: return alpha | 0xBC8F8FAA;
			case 0x7907D454: return alpha | 0xBC8F8FAA;
			case 0xFD9D16AD: return alpha | 0xCD5C5CAA;
			case 0xEBA2D58C: return alpha | 0xCD5C5CAA;
			case 0xFA0DE20D: return alpha | 0xCD5C5CAA;
			case 0xEF5D9534: return alpha | 0x8B4513AA;
			case 0x9CB719B3: return alpha | 0x8B4513AA;
			case 0xAB222634: return alpha | 0x8B4513AA;
			case 0x5054803D: return alpha | 0xA0522DAA;
			case 0x001DE9BB: return alpha | 0xCD853FAA;
			case 0x67F34C86: return alpha | 0xDEB887AA;
			case 0x02B3A0BB: return alpha | 0xF5F5DCAA;
			case 0x03BFB578: return alpha | 0xF5DEB3AA;
			case 0x7D03AE06: return alpha | 0xF4A460AA;
			case 0x2CEF1EA5: return alpha | 0xF4A460AA;
			case 0x99FA1F06: return alpha | 0xF4A460AA;
			case 0x0000C822: return alpha | 0xD2B48CAA;
			case 0x29A6E191: return alpha | 0xD2691EAA;
			case 0xA9192590: return alpha | 0xB22222AA;
			case 0x035F5E87: return alpha | 0xA52A2AAA;
			case 0x30013BAB: return alpha | 0xE9967AAA;
			case 0x318F0CAA: return alpha | 0xE9967AAA;
			case 0x2D1B04EB: return alpha | 0xE9967AAA;
			case 0x6EB93949: return alpha | 0xFA8072AA;
			case 0x30C62C41: return alpha | 0xFFA07AAA;
			case 0x640E1D20: return alpha | 0xFFA07AAA;
			case 0xD1191D81: return alpha | 0xFFA07AAA;
			case 0x592A675B: return alpha | 0xFFA500AA;
			case 0x2C9F22BD: return alpha | 0xFF8C00AA;
			case 0xC1E9D5FC: return alpha | 0xFF8C00AA;
			case 0xBD75CE3D: return alpha | 0xFF8C00AA;
			case 0x032F2990: return alpha | 0xFF7F50AA;
			case 0x521060E8: return alpha | 0xF08080AA;
			case 0xAE9EE6A7: return alpha | 0xF08080AA;
			case 0x1BA9E708: return alpha | 0xF08080AA;
			case 0x71624DF3: return alpha | 0xFF6347AA;
			case 0xE90DEDB6: return alpha | 0xFF4500AA;
			case 0xD713AC95: return alpha | 0xFF4500AA;
			case 0xE57EB916: return alpha | 0xFF4500AA;
			case 0x00009E1A: return alpha | 0xFF0000AA;
			case 0x5C56A39C: return alpha | 0xFF69B4AA;
			case 0xE73135BB: return alpha | 0xFF69B4AA;
			case 0xE70EA9DC: return alpha | 0xFF69B4AA;
			case 0xE728BAEF: return alpha | 0xFF1493AA;
			case 0xCD5590EE: return alpha | 0xFF1493AA;
			case 0xC8E1892F: return alpha | 0xFF1493AA;
			case 0x00185D71: return alpha | 0xFFC0CBAA;
			case 0xCC8A2969: return alpha | 0xFFB6C1AA;
			case 0x7851BF48: return alpha | 0xFFB6C1AA;
			case 0xE55CBFA9: return alpha | 0xFFB6C1AA;
			case 0x1192806F: return alpha | 0xDB7093AA;
			case 0xFB30442D: return alpha | 0xDB7093AA;
			case 0xEAD8418F: return alpha | 0xDB7093AA;
			case 0x6EBA6B8B: return alpha | 0xB03060AA;
			case 0xD384B2EE: return alpha | 0xC71585AA;
			case 0x9BA25E2C: return alpha | 0xC71585AA;
			case 0x153F3C0E: return alpha | 0xC71585AA;
			case 0x0BE63FCD: return alpha | 0xD02090AA;
			case 0xF9EBFEAC: return alpha | 0xD02090AA;
			case 0x08570B2D: return alpha | 0xD02090AA;
			case 0x68E3711C: return alpha | 0xFF00FFAA;
			case 0x7C02B972: return alpha | 0xEE82EEAA;
			case 0x0019945D: return alpha | 0xDDA0DDAA;
			case 0x56F62DF8: return alpha | 0xDA70D6AA;
			case 0x80575559: return alpha | 0xBA55D3AA;
			case 0xE30CDFF8: return alpha | 0xBA55D3AA;
			case 0xF177EC79: return alpha | 0xBA55D3AA;
			case 0x21F6EFDA: return alpha | 0x9932CCAA;
			case 0x623B46B9: return alpha | 0x9932CCAA;
			case 0x5DC73EFA: return alpha | 0x9932CCAA;
			case 0xC8F0A854: return alpha | 0x9400D3AA;
			case 0xE86C0E73: return alpha | 0x9400D3AA;
			case 0xE3F806B4: return alpha | 0x9400D3AA;
			case 0xC8ED6C3A: return alpha | 0x8A2BE2AA;
			case 0xE868D259: return alpha | 0x8A2BE2AA;
			case 0xE3F4CA9A: return alpha | 0x8A2BE2AA;
			case 0x59864357: return alpha | 0xA020F0AA;
			case 0x46BFB5F8: return alpha | 0x9370DBAA;
			case 0x76815477: return alpha | 0x9370DBAA;
			case 0x84EC60F8: return alpha | 0x9370DBAA;
			case 0x8A9768DC: return alpha | 0xD8BFD8AA;
			case 0x01529777: return alpha | 0xFFFAFAAA;
			case 0x2C3AB156: return alpha | 0xFFFAFAAA;
			case 0x27C6A997: return alpha | 0xFFFAFAAA;
			case 0x0164AFF8: return alpha | 0xEEE9E9AA;
			case 0x2E8FD9F7: return alpha | 0xEEE9E9AA;
			case 0x2A1BD238: return alpha | 0xEEE9E9AA;
			case 0x0176C879: return alpha | 0xCDC9C9AA;
			case 0x30E50298: return alpha | 0xCDC9C9AA;
			case 0x2C70FAD9: return alpha | 0xCDC9C9AA;
			case 0x0188E0FA: return alpha | 0x8B8989AA;
			case 0x333A2B39: return alpha | 0x8B8989AA;
			case 0x2EC6237A: return alpha | 0x8B8989AA;
			case 0xEBD5C501: return alpha | 0xFFF5EEAA;
			case 0x1EE5B660: return alpha | 0xFFF5EEAA;
			case 0x7445E721: return alpha | 0xFFF5EEAA;
			case 0x60523602: return alpha | 0xEEE5DEAA;
			case 0x22F04781: return alpha | 0xEEE5DEAA;
			case 0x78507842: return alpha | 0xEEE5DEAA;
			case 0xD4CEA703: return alpha | 0xCDC5BFAA;
			case 0x26FAD8A2: return alpha | 0xCDC5BFAA;
			case 0x7C5B0963: return alpha | 0xCDC5BFAA;
			case 0x494B1804: return alpha | 0x8B8682AA;
			case 0x2B0569C3: return alpha | 0x8B8682AA;
			case 0x80659A84: return alpha | 0x8B8682AA;
			case 0xA9F2D548: return alpha | 0xFFEFDBAA;
			case 0x9E816FA6: return alpha | 0xFFEFDBAA;
			case 0xE57FDDA8: return alpha | 0xFFEFDBAA;
			case 0xF951DEC9: return alpha | 0xEEDFCCAA;
			case 0x41C8DD67: return alpha | 0xEEDFCCAA;
			case 0x88C74B69: return alpha | 0xEEDFCCAA;
			case 0x48B0E84A: return alpha | 0xCDC0B0AA;
			case 0xE5104B28: return alpha | 0xCDC0B0AA;
			case 0x2C0EB92A: return alpha | 0xCDC0B0AA;
			case 0x980FF1CB: return alpha | 0x8B8378AA;
			case 0x8857B8E9: return alpha | 0x8B8378AA;
			case 0xCF5626EB: return alpha | 0x8B8378AA;
			case 0x76C7B7B9: return alpha | 0xFFE4C4AA;
			case 0xFC1DC558: return alpha | 0xFFE4C4AA;
			case 0x0A88D1D9: return alpha | 0xFFE4C4AA;
			case 0xC3C1F47A: return alpha | 0xEED5B7AA;
			case 0xE85F9A39: return alpha | 0xEED5B7AA;
			case 0xF6CAA6BA: return alpha | 0xEED5B7AA;
			case 0x10BC313B: return alpha | 0xCDB79EAA;
			case 0xD4A16F1A: return alpha | 0xCDB79EAA;
			case 0xE30C7B9B: return alpha | 0xCDB79EAA;
			case 0x5DB66DFC: return alpha | 0x8B7D6BAA;
			case 0xC0E343FB: return alpha | 0x8B7D6BAA;
			case 0xCF4E507C: return alpha | 0x8B7D6BAA;
			case 0x039FCBA2: return alpha | 0xFFDAB9AA;
			case 0xE46D2CA0: return alpha | 0xFFDAB9AA;
			case 0x7FA79202: return alpha | 0xFFDAB9AA;
			case 0x07AA5CC3: return alpha | 0xEECBADAA;
			case 0x15608A01: return alpha | 0xEECBADAA;
			case 0xB09AEF63: return alpha | 0xEECBADAA;
			case 0x0BB4EDE4: return alpha | 0xCDAF95AA;
			case 0x4653E762: return alpha | 0xCDAF95AA;
			case 0xE18E4CC4: return alpha | 0xCDAF95AA;
			case 0x0FBF7F05: return alpha | 0x8B7765AA;
			case 0x774744C3: return alpha | 0x8B7765AA;
			case 0x1281AA25: return alpha | 0x8B7765AA;
			case 0xE55CC7B0: return alpha | 0xFFDEADAA;
			case 0x9F328E4E: return alpha | 0xFFDEADAA;
			case 0x253A4410: return alpha | 0xFFDEADAA;
			case 0x16502511: return alpha | 0xEECFA1AA;
			case 0xDA72C7EF: return alpha | 0xEECFA1AA;
			case 0x607A7DB1: return alpha | 0xEECFA1AA;
			case 0x47438272: return alpha | 0xCDB38BAA;
			case 0x15B30190: return alpha | 0xCDB38BAA;
			case 0x9BBAB752: return alpha | 0xCDB38BAA;
			case 0x7836DFD3: return alpha | 0x8B795EAA;
			case 0x50F33B31: return alpha | 0x8B795EAA;
			case 0xD6FAF0F3: return alpha | 0x8B795EAA;
			case 0xA3BE1688: return alpha | 0xFFFACDAA;
			case 0xC06060A6: return alpha | 0xFFFACDAA;
			case 0x989D3268: return alpha | 0xFFFACDAA;
			case 0xF31D2009: return alpha | 0xEEE9BFAA;
			case 0x63A7CE67: return alpha | 0xEEE9BFAA;
			case 0x3BE4A029: return alpha | 0xEEE9BFAA;
			case 0x427C298A: return alpha | 0xCDC9A5AA;
			case 0x06EF3C28: return alpha | 0xCDC9A5AA;
			case 0xDF2C0DEA: return alpha | 0xCDC9A5AA;
			case 0x91DB330B: return alpha | 0x8B8970AA;
			case 0xAA36A9E9: return alpha | 0x8B8970AA;
			case 0x82737BAB: return alpha | 0x8B8970AA;
			case 0x09AD2BD5: return alpha | 0xFFF8DCAA;
			case 0x3CBD1D34: return alpha | 0xFFF8DCAA;
			case 0x921D4DF5: return alpha | 0xFFF8DCAA;
			case 0x7E299CD6: return alpha | 0xEEE8CDAA;
			case 0x40C7AE55: return alpha | 0xEEE8CDAA;
			case 0x9627DF16: return alpha | 0xEEE8CDAA;
			case 0xF2A60DD7: return alpha | 0xCDC8B1AA;
			case 0x44D23F76: return alpha | 0xCDC8B1AA;
			case 0x9A327037: return alpha | 0xCDC8B1AA;
			case 0x67227ED8: return alpha | 0x8B8878AA;
			case 0x48DCD097: return alpha | 0x8B8878AA;
			case 0x9E3D0158: return alpha | 0x8B8878AA;
			case 0x2BCB6169: return alpha | 0xFFFFF0AA;
			case 0xB3B6B728: return alpha | 0xFFFFF0AA;
			case 0x20C1B789: return alpha | 0xFFFFF0AA;
			case 0x2E208A0A: return alpha | 0xEEEEE0AA;
			case 0x00B0F3E9: return alpha | 0xEEEEE0AA;
			case 0x6DBBF44A: return alpha | 0xEEEEE0AA;
			case 0x3075B2AB: return alpha | 0xCDCDC1AA;
			case 0x4DAB30AA: return alpha | 0xCDCDC1AA;
			case 0xBAB6310B: return alpha | 0xCDCDC1AA;
			case 0x32CADB4C: return alpha | 0x8B8B83AA;
			case 0x9AA56D6B: return alpha | 0x8B8B83AA;
			case 0x07B06DCC: return alpha | 0x8B8B83AA;
			case 0xF6A94493: return alpha | 0xF0FFF0AA;
			case 0x29B935F2: return alpha | 0xF0FFF0AA;
			case 0x7F1966B3: return alpha | 0xF0FFF0AA;
			case 0x6B25B594: return alpha | 0xE0EEE0AA;
			case 0x2DC3C713: return alpha | 0xE0EEE0AA;
			case 0x8323F7D4: return alpha | 0xE0EEE0AA;
			case 0xDFA22695: return alpha | 0xC1CDC1AA;
			case 0x31CE5834: return alpha | 0xC1CDC1AA;
			case 0x872E88F5: return alpha | 0xC1CDC1AA;
			case 0x541E9796: return alpha | 0x838B83AA;
			case 0x35D8E955: return alpha | 0x838B83AA;
			case 0x8B391A16: return alpha | 0x838B83AA;
			case 0x7978123F: return alpha | 0xFFF0F5AA;
			case 0xEEC1ABFD: return alpha | 0xFFF0F5AA;
			case 0x158DDA3F: return alpha | 0xFFF0F5AA;
			case 0xB4B84BE0: return alpha | 0xEEE0E5AA;
			case 0xFAF6D1DE: return alpha | 0xEEE0E5AA;
			case 0x21C30020: return alpha | 0xEEE0E5AA;
			case 0xEFF88581: return alpha | 0xCDC1C5AA;
			case 0x072BF7BF: return alpha | 0xCDC1C5AA;
			case 0x2DF82601: return alpha | 0xCDC1C5AA;
			case 0x2B38BF22: return alpha | 0x8B8386AA;
			case 0x13611DA0: return alpha | 0x8B8386AA;
			case 0x3A2D4BE2: return alpha | 0x8B8386AA;
			case 0xC6854EDF: return alpha | 0xFFE4E1AA;
			case 0xDC5B14DD: return alpha | 0xFFE4E1AA;
			case 0x77957A3F: return alpha | 0xFFE4E1AA;
			case 0xCA8FE000: return alpha | 0xEED5D2AA;
			case 0x0D4E723E: return alpha | 0xEED5D2AA;
			case 0xA888D7A0: return alpha | 0xEED5D2AA;
			case 0xCE9A7121: return alpha | 0xCDB7B5AA;
			case 0x3E41CF9F: return alpha | 0xCDB7B5AA;
			case 0xD97C3501: return alpha | 0xCDB7B5AA;
			case 0xD2A50242: return alpha | 0x8B7D7BAA;
			case 0x6F352D00: return alpha | 0x8B7D7BAA;
			case 0x0A6F9262: return alpha | 0x8B7D7BAA;
			case 0x2A619157: return alpha | 0xF0FFFFAA;
			case 0xB24CE716: return alpha | 0xF0FFFFAA;
			case 0x1F57E777: return alpha | 0xF0FFFFAA;
			case 0x2CB6B9F8: return alpha | 0xE0EEEEAA;
			case 0xFF4723D7: return alpha | 0xE0EEEEAA;
			case 0x6C522438: return alpha | 0xE0EEEEAA;
			case 0x2F0BE299: return alpha | 0xC1CDCDAA;
			case 0x4C416098: return alpha | 0xC1CDCDAA;
			case 0xB94C60F9: return alpha | 0xC1CDCDAA;
			case 0x31610B3A: return alpha | 0x838B8BAA;
			case 0x993B9D59: return alpha | 0x838B8BAA;
			case 0x06469DBA: return alpha | 0x838B8BAA;
			case 0x915D8211: return alpha | 0x836FFFAA;
			case 0x2F8075EF: return alpha | 0x836FFFAA;
			case 0xCABADB51: return alpha | 0x836FFFAA;
			case 0x95681332: return alpha | 0x7A67EEAA;
			case 0x6073D350: return alpha | 0x7A67EEAA;
			case 0xFBAE38B2: return alpha | 0x7A67EEAA;
			case 0x9972A453: return alpha | 0x6959CDAA;
			case 0x916730B1: return alpha | 0x6959CDAA;
			case 0x2CA19613: return alpha | 0x6959CDAA;
			case 0x9D7D3574: return alpha | 0x473C8BAA;
			case 0xC25A8E12: return alpha | 0x473C8BAA;
			case 0x5D94F374: return alpha | 0x473C8BAA;
			case 0x91D228DF: return alpha | 0x4876FFAA;
			case 0x2FF51CBD: return alpha | 0x4876FFAA;
			case 0xCB2F821F: return alpha | 0x4876FFAA;
			case 0x95DCBA00: return alpha | 0x436EEEAA;
			case 0x60E87A1E: return alpha | 0x436EEEAA;
			case 0xFC22DF80: return alpha | 0x436EEEAA;
			case 0x99E74B21: return alpha | 0x3A5FCDAA;
			case 0x91DBD77F: return alpha | 0x3A5FCDAA;
			case 0x2D163CE1: return alpha | 0x3A5FCDAA;
			case 0x9DF1DC42: return alpha | 0x27408BAA;
			case 0xC2CF34E0: return alpha | 0x27408BAA;
			case 0x5E099A42: return alpha | 0x27408BAA;
			case 0x0148D1D8: return alpha | 0x0000FFAA;
			case 0x2C30EBB7: return alpha | 0x0000FFAA;
			case 0x27BCE3F8: return alpha | 0x0000FFAA;
			case 0x015AEA59: return alpha | 0x0000EEAA;
			case 0x2E861458: return alpha | 0x0000EEAA;
			case 0x2A120C99: return alpha | 0x0000EEAA;
			case 0x016D02DA: return alpha | 0x0000CDAA;
			case 0x30DB3CF9: return alpha | 0x0000CDAA;
			case 0x2C67353A: return alpha | 0x0000CDAA;
			case 0x017F1B5B: return alpha | 0x00008BAA;
			case 0x3330659A: return alpha | 0x00008BAA;
			case 0x2EBC5DDB: return alpha | 0x00008BAA;
			case 0xDA548CCD: return alpha | 0x1E90FFAA;
			case 0x3CD5FC6B: return alpha | 0x1E90FFAA;
			case 0x3F5D0E0D: return alpha | 0x1E90FFAA;
			case 0x5FB1420E: return alpha | 0x1C86EEAA;
			case 0x8C3505EC: return alpha | 0x1C86EEAA;
			case 0x8EBC178E: return alpha | 0x1C86EEAA;
			case 0xE50DF74F: return alpha | 0x1874CDAA;
			case 0xDB940F6D: return alpha | 0x1874CDAA;
			case 0xDE1B210F: return alpha | 0x1874CDAA;
			case 0x6A6AAC90: return alpha | 0x104E8BAA;
			case 0x2AF318EE: return alpha | 0x104E8BAA;
			case 0x2D7A2A90: return alpha | 0x104E8BAA;
			case 0x91D405F5: return alpha | 0x63B8FFAA;
			case 0x2FF6F9D3: return alpha | 0x63B8FFAA;
			case 0xCB315F35: return alpha | 0x63B8FFAA;
			case 0x95DE9716: return alpha | 0x5CACEEAA;
			case 0x60EA5734: return alpha | 0x5CACEEAA;
			case 0xFC24BC96: return alpha | 0x5CACEEAA;
			case 0x99E92837: return alpha | 0x4F94CDAA;
			case 0x91DDB495: return alpha | 0x4F94CDAA;
			case 0x2D1819F7: return alpha | 0x4F94CDAA;
			case 0x9DF3B958: return alpha | 0x36648BAA;
			case 0xC2D111F6: return alpha | 0x36648BAA;
			case 0x5E0B7758: return alpha | 0x36648BAA;
			case 0x4E9C53ED: return alpha | 0x00BFFFAA;
			case 0x2BD818CA: return alpha | 0x00BFFFAA;
			case 0xE7F6132D: return alpha | 0x00BFFFAA;
			case 0x7F8FB14E: return alpha | 0x00B2EEAA;
			case 0xCF1F868B: return alpha | 0x00B2EEAA;
			case 0x8B3D80EE: return alpha | 0x00B2EEAA;
			case 0xB0830EAF: return alpha | 0x009ACDAA;
			case 0x7266F44C: return alpha | 0x009ACDAA;
			case 0x2E84EEAF: return alpha | 0x009ACDAA;
			case 0xE1766C10: return alpha | 0x00688BAA;
			case 0x15AE620D: return alpha | 0x00688BAA;
			case 0xD1CC5C70: return alpha | 0x00688BAA;
			case 0x4F5B276F: return alpha | 0x87CEFFAA;
			case 0x6DD38BCD: return alpha | 0x87CEFFAA;
			case 0xC31130AF: return alpha | 0x87CEFFAA;
			case 0x3B9CFC50: return alpha | 0x7EC0EEAA;
			case 0x71DE1CEE: return alpha | 0x7EC0EEAA;
			case 0xC71BC1D0: return alpha | 0x7EC0EEAA;
			case 0x27DED131: return alpha | 0x6CA6CDAA;
			case 0x75E8AE0F: return alpha | 0x6CA6CDAA;
			case 0xCB2652F1: return alpha | 0x6CA6CDAA;
			case 0x1420A612: return alpha | 0x4A708BAA;
			case 0x79F33F30: return alpha | 0x4A708BAA;
			case 0xCF30E412: return alpha | 0x4A708BAA;
			case 0x2270E227: return alpha | 0xB0E2FFAA;
			case 0xA72542A4: return alpha | 0xB0E2FFAA;
			case 0xE7028967: return alpha | 0xB0E2FFAA;
			case 0x71CFEBA8: return alpha | 0xA4D3EEAA;
			case 0xB35A6885: return alpha | 0xA4D3EEAA;
			case 0xF337AF48: return alpha | 0xA4D3EEAA;
			case 0xC12EF529: return alpha | 0x8DB6CDAA;
			case 0xBF8F8E66: return alpha | 0x8DB6CDAA;
			case 0xFF6CD529: return alpha | 0x8DB6CDAA;
			case 0x108DFEAA: return alpha | 0x607B8BAA;
			case 0xCBC4B447: return alpha | 0x607B8BAA;
			case 0x0BA1FB0A: return alpha | 0x607B8BAA;
			case 0x0F78EC3C: return alpha | 0xC6E2FFAA;
			case 0x7109257A: return alpha | 0xC6E2FFAA;
			case 0x0C438ADC: return alpha | 0xC6E2FFAA;
			case 0x13837D5D: return alpha | 0xB9D3EEAA;
			case 0xA1FC82DB: return alpha | 0xB9D3EEAA;
			case 0x3D36E83D: return alpha | 0xB9D3EEAA;
			case 0x178E0E7E: return alpha | 0x9FB6CDAA;
			case 0xD2EFE03C: return alpha | 0x9FB6CDAA;
			case 0x6E2A459E: return alpha | 0x9FB6CDAA;
			case 0x1B989F9F: return alpha | 0x6C7B8BAA;
			case 0x03E33D9D: return alpha | 0x6C7B8BAA;
			case 0x9F1DA2FF: return alpha | 0x6C7B8BAA;
			case 0xC0803FC0: return alpha | 0xC6E2FFAA;
			case 0x42FAE97E: return alpha | 0xC6E2FFAA;
			case 0xDE354EE0: return alpha | 0xC6E2FFAA;
			case 0xC48AD0E1: return alpha | 0xB9D3EEAA;
			case 0x73EE46DF: return alpha | 0xB9D3EEAA;
			case 0x0F28AC41: return alpha | 0xB9D3EEAA;
			case 0xC8956202: return alpha | 0x9FB6CDAA;
			case 0xA4E1A440: return alpha | 0x9FB6CDAA;
			case 0x401C09A2: return alpha | 0x9FB6CDAA;
			case 0xCC9FF323: return alpha | 0x6C7B8BAA;
			case 0xD5D501A1: return alpha | 0x6C7B8BAA;
			case 0x710F6703: return alpha | 0x6C7B8BAA;
			case 0xC1B7C46D: return alpha | 0xCAE1FFAA;
			case 0x8B809D2A: return alpha | 0xCAE1FFAA;
			case 0xC909046D: return alpha | 0xCAE1FFAA;
			case 0x64FF322E: return alpha | 0xBCD2EEAA;
			case 0x7996BF4B: return alpha | 0xBCD2EEAA;
			case 0xB71F268E: return alpha | 0xBCD2EEAA;
			case 0x08469FEF: return alpha | 0xA2B5CDAA;
			case 0x67ACE16C: return alpha | 0xA2B5CDAA;
			case 0xA53548AF: return alpha | 0xA2B5CDAA;
			case 0xAB8E0DB0: return alpha | 0x6E7B8BAA;
			case 0x55C3038D: return alpha | 0x6E7B8BAA;
			case 0x934B6AD0: return alpha | 0x6E7B8BAA;
			case 0x92667630: return alpha | 0xBFEFFFAA;
			case 0x30896A0E: return alpha | 0xBFEFFFAA;
			case 0xCBC3CF70: return alpha | 0xBFEFFFAA;
			case 0x96710751: return alpha | 0xB2DFEEAA;
			case 0x617CC76F: return alpha | 0xB2DFEEAA;
			case 0xFCB72CD1: return alpha | 0xB2DFEEAA;
			case 0x9A7B9872: return alpha | 0x9AC0CDAA;
			case 0x927024D0: return alpha | 0x9AC0CDAA;
			case 0x2DAA8A32: return alpha | 0x9AC0CDAA;
			case 0x9E862993: return alpha | 0x68838BAA;
			case 0xC3638231: return alpha | 0x68838BAA;
			case 0x5E9DE793: return alpha | 0x68838BAA;
			case 0x20AC0C13: return alpha | 0xE0FFFFAA;
			case 0x8781BC51: return alpha | 0xE0FFFFAA;
			case 0x22BC21B3: return alpha | 0xE0FFFFAA;
			case 0x24B69D34: return alpha | 0xD1EEEEAA;
			case 0xB87519B2: return alpha | 0xD1EEEEAA;
			case 0x53AF7F14: return alpha | 0xD1EEEEAA;
			case 0x28C12E55: return alpha | 0xB4CDCDAA;
			case 0xE9687713: return alpha | 0xB4CDCDAA;
			case 0x84A2DC75: return alpha | 0xB4CDCDAA;
			case 0x2CCBBF76: return alpha | 0x7A8B8BAA;
			case 0x1A5BD474: return alpha | 0x7A8B8BAA;
			case 0xB59639D6: return alpha | 0x7A8B8BAA;
			case 0x20E5E943: return alpha | 0xBBFFFFAA;
			case 0x65D321E1: return alpha | 0xBBFFFFAA;
			case 0x32CB17A3: return alpha | 0xBBFFFFAA;
			case 0x5C2622E4: return alpha | 0xAEEEEEAA;
			case 0x720847C2: return alpha | 0xAEEEEEAA;
			case 0x3F003D84: return alpha | 0xAEEEEEAA;
			case 0x97665C85: return alpha | 0x96CDCDAA;
			case 0x7E3D6DA3: return alpha | 0x96CDCDAA;
			case 0x4B356365: return alpha | 0x96CDCDAA;
			case 0xD2A69626: return alpha | 0x668B8BAA;
			case 0x8A729384: return alpha | 0x668B8BAA;
			case 0x576A8946: return alpha | 0x668B8BAA;
			case 0x9264C339: return alpha | 0x98F5FFAA;
			case 0x3087B717: return alpha | 0x98F5FFAA;
			case 0xCBC21C79: return alpha | 0x98F5FFAA;
			case 0x966F545A: return alpha | 0x8EE5EEAA;
			case 0x617B1478: return alpha | 0x8EE5EEAA;
			case 0xFCB579DA: return alpha | 0x8EE5EEAA;
			case 0x9A79E57B: return alpha | 0x7AC5CDAA;
			case 0x926E71D9: return alpha | 0x7AC5CDAA;
			case 0x2DA8D73B: return alpha | 0x7AC5CDAA;
			case 0x9E84769C: return alpha | 0x53868BAA;
			case 0xC361CF3A: return alpha | 0x53868BAA;
			case 0x5E9C349C: return alpha | 0x53868BAA;
			case 0xF15E5EA1: return alpha | 0x00F5FFAA;
			case 0x866C7BE0: return alpha | 0x00F5FFAA;
			case 0x87D2C4C1: return alpha | 0x00F5FFAA;
			case 0xF568EFC2: return alpha | 0x00E5EEAA;
			case 0x0BC93121: return alpha | 0x00E5EEAA;
			case 0x0D2F7A02: return alpha | 0x00E5EEAA;
			case 0xF97380E3: return alpha | 0x00C5CDAA;
			case 0x9125E662: return alpha | 0x00C5CDAA;
			case 0x928C2F43: return alpha | 0x00C5CDAA;
			case 0xFD7E1204: return alpha | 0x00868BAA;
			case 0x16829BA3: return alpha | 0x00868BAA;
			case 0x17E8E484: return alpha | 0x00868BAA;
			case 0x014D6DDB: return alpha | 0x00FFFFAA;
			case 0x2C3587BA: return alpha | 0x00FFFFAA;
			case 0x27C17FFB: return alpha | 0x00FFFFAA;
			case 0x015F865C: return alpha | 0x00EEEEAA;
			case 0x2E8AB05B: return alpha | 0x00EEEEAA;
			case 0x2A16A89C: return alpha | 0x00EEEEAA;
			case 0x01719EDD: return alpha | 0x00CDCDAA;
			case 0x30DFD8FC: return alpha | 0x00CDCDAA;
			case 0x2C6BD13D: return alpha | 0x00CDCDAA;
			case 0x0183B75E: return alpha | 0x008B8BAA;
			case 0x3335019D: return alpha | 0x008B8BAA;
			case 0x2EC0F9DE: return alpha | 0x008B8BAA;
			case 0xBE77301E: return alpha | 0x97FFFFAA;
			case 0xF0FF3F7B: return alpha | 0x97FFFFAA;
			case 0x19A64A5E: return alpha | 0x97FFFFAA;
			case 0xF9B769BF: return alpha | 0x8DEEEEAA;
			case 0x83D9217C: return alpha | 0x8DEEEEAA;
			case 0xAC802C5F: return alpha | 0x8DEEEEAA;
			case 0x34F7A360: return alpha | 0x79CDCDAA;
			case 0x16B3037D: return alpha | 0x79CDCDAA;
			case 0x3F5A0E60: return alpha | 0x79CDCDAA;
			case 0x7037DD01: return alpha | 0x528B8BAA;
			case 0xA98CE57E: return alpha | 0x528B8BAA;
			case 0xD233F061: return alpha | 0x528B8BAA;
			case 0x8244A5A2: return alpha | 0x97FFFFAA;
			case 0xDE0025FF: return alpha | 0x97FFFFAA;
			case 0x06A730E2: return alpha | 0x97FFFFAA;
			case 0xBD84DF43: return alpha | 0x8DEEEEAA;
			case 0x70DA0800: return alpha | 0x8DEEEEAA;
			case 0x998112E3: return alpha | 0x8DEEEEAA;
			case 0xF8C518E4: return alpha | 0x79CDCDAA;
			case 0x03B3EA01: return alpha | 0x79CDCDAA;
			case 0x2C5AF4E4: return alpha | 0x79CDCDAA;
			case 0x34055285: return alpha | 0x528B8BAA;
			case 0x968DCC02: return alpha | 0x528B8BAA;
			case 0xBF34D6E5: return alpha | 0x528B8BAA;
			case 0x8EB1D2D4: return alpha | 0x7FFFD4AA;
			case 0xC58397F3: return alpha | 0x7FFFD4AA;
			case 0xF3B2FCF4: return alpha | 0x7FFFD4AA;
			case 0x140E8815: return alpha | 0x76EEC6AA;
			case 0xF676F554: return alpha | 0x76EEC6AA;
			case 0x24A65A55: return alpha | 0x76EEC6AA;
			case 0x996B3D56: return alpha | 0x66CDAAAA;
			case 0x276A52B5: return alpha | 0x66CDAAAA;
			case 0x5599B7B6: return alpha | 0x66CDAAAA;
			case 0x1EC7F297: return alpha | 0x458B74AA;
			case 0x585DB016: return alpha | 0x458B74AA;
			case 0x868D1517: return alpha | 0x458B74AA;
			case 0xF19118DC: return alpha | 0xC1FFC1AA;
			case 0x9410D819: return alpha | 0xC1FFC1AA;
			case 0xB668FE9C: return alpha | 0xC1FFC1AA;
			case 0x40F0225D: return alpha | 0xB4EEB4AA;
			case 0xA045FDFA: return alpha | 0xB4EEB4AA;
			case 0xC29E247D: return alpha | 0xB4EEB4AA;
			case 0x904F2BDE: return alpha | 0x9BCD9BAA;
			case 0xAC7B23DB: return alpha | 0x9BCD9BAA;
			case 0xCED34A5E: return alpha | 0x9BCD9BAA;
			case 0xDFAE355F: return alpha | 0x698B69AA;
			case 0xB8B049BC: return alpha | 0x698B69AA;
			case 0xDB08703F: return alpha | 0x698B69AA;
			case 0xAA3025FA: return alpha | 0x54FF9FAA;
			case 0x85536358: return alpha | 0x54FF9FAA;
			case 0x8697205A: return alpha | 0x54FF9FAA;
			case 0x1EAC96FB: return alpha | 0x4EEE94AA;
			case 0x0AB01899: return alpha | 0x4EEE94AA;
			case 0x0BF3D59B: return alpha | 0x4EEE94AA;
			case 0x932907FC: return alpha | 0x43CD80AA;
			case 0x900CCDDA: return alpha | 0x43CD80AA;
			case 0x91508ADC: return alpha | 0x43CD80AA;
			case 0x07A578FD: return alpha | 0x2E8B57AA;
			case 0x1569831B: return alpha | 0x2E8B57AA;
			case 0x16AD401D: return alpha | 0x2E8B57AA;
			case 0xF0373283: return alpha | 0x9AFF9AAA;
			case 0x2FC21BA1: return alpha | 0x9AFF9AAA;
			case 0x597D78E3: return alpha | 0x9AFF9AAA;
			case 0xF441C3A4: return alpha | 0x90EE90AA;
			case 0x60B57902: return alpha | 0x90EE90AA;
			case 0x8A70D644: return alpha | 0x90EE90AA;
			case 0xF84C54C5: return alpha | 0x7CCD7CAA;
			case 0x91A8D663: return alpha | 0x7CCD7CAA;
			case 0xBB6433A5: return alpha | 0x7CCD7CAA;
			case 0xFC56E5E6: return alpha | 0x548B54AA;
			case 0xC29C33C4: return alpha | 0x548B54AA;
			case 0xEC579106: return alpha | 0x548B54AA;
			case 0xDFA0D7B4: return alpha | 0x00FF7FAA;
			case 0x2D8A8052: return alpha | 0x00FF7FAA;
			case 0xB3923614: return alpha | 0x00FF7FAA;
			case 0x10943515: return alpha | 0x00EE76AA;
			case 0x68CAB9F3: return alpha | 0x00EE76AA;
			case 0xEED26FB5: return alpha | 0x00EE76AA;
			case 0x41879276: return alpha | 0x00CD66AA;
			case 0xA40AF394: return alpha | 0x00CD66AA;
			case 0x2A12A956: return alpha | 0x00CD66AA;
			case 0x727AEFD7: return alpha | 0x008B45AA;
			case 0xDF4B2D35: return alpha | 0x008B45AA;
			case 0x6552E2F7: return alpha | 0x008B45AA;
			case 0x2AFD07E1: return alpha | 0x00FF00AA;
			case 0xB2E85DA0: return alpha | 0x00FF00AA;
			case 0x1FF35E01: return alpha | 0x00FF00AA;
			case 0x2D523082: return alpha | 0x00EE00AA;
			case 0xFFE29A61: return alpha | 0x00EE00AA;
			case 0x6CED9AC2: return alpha | 0x00EE00AA;
			case 0x2FA75923: return alpha | 0x00CD00AA;
			case 0x4CDCD722: return alpha | 0x00CD00AA;
			case 0xB9E7D783: return alpha | 0x00CD00AA;
			case 0x31FC81C4: return alpha | 0x008B00AA;
			case 0x99D713E3: return alpha | 0x008B00AA;
			case 0x06E21444: return alpha | 0x008B00AA;
			case 0x27B04706: return alpha | 0x7FFF00AA;
			case 0x5E820C25: return alpha | 0x7FFF00AA;
			case 0x8CB17126: return alpha | 0x7FFF00AA;
			case 0xAD0CFC47: return alpha | 0x76EE00AA;
			case 0x8F756986: return alpha | 0x76EE00AA;
			case 0xBDA4CE87: return alpha | 0x76EE00AA;
			case 0x3269B188: return alpha | 0x66CD00AA;
			case 0xC068C6E7: return alpha | 0x66CD00AA;
			case 0xEE982BE8: return alpha | 0x66CD00AA;
			case 0xB7C666C9: return alpha | 0x458B00AA;
			case 0xF15C2448: return alpha | 0x458B00AA;
			case 0x1F8B8949: return alpha | 0x458B00AA;
			case 0x914C8608: return alpha | 0xC0FF3EAA;
			case 0x2D28A006: return alpha | 0xC0FF3EAA;
			case 0xC8630568: return alpha | 0xC0FF3EAA;
			case 0x95571729: return alpha | 0xB3EE3AAA;
			case 0x5E1BFD67: return alpha | 0xB3EE3AAA;
			case 0xF95662C9: return alpha | 0xB3EE3AAA;
			case 0x9961A84A: return alpha | 0x9ACD32AA;
			case 0x8F0F5AC8: return alpha | 0x9ACD32AA;
			case 0x2A49C02A: return alpha | 0x9ACD32AA;
			case 0x9D6C396B: return alpha | 0x698B22AA;
			case 0xC002B829: return alpha | 0x698B22AA;
			case 0x5B3D1D8B: return alpha | 0x698B22AA;
			case 0x1CE9E662: return alpha | 0xCAFF70AA;
			case 0xC135D5DF: return alpha | 0xCAFF70AA;
			case 0xC75294E2: return alpha | 0xCAFF70AA;
			case 0xC0315423: return alpha | 0xBCEE68AA;
			case 0xAF4BF800: return alpha | 0xBCEE68AA;
			case 0xB568B703: return alpha | 0xBCEE68AA;
			case 0x6378C1E4: return alpha | 0xA2CD5AAA;
			case 0x9D621A21: return alpha | 0xA2CD5AAA;
			case 0xA37ED924: return alpha | 0xA2CD5AAA;
			case 0x06C02FA5: return alpha | 0x6E8B3DAA;
			case 0x8B783C42: return alpha | 0x6E8B3DAA;
			case 0x9194FB45: return alpha | 0x6E8B3DAA;
			case 0x2AA5C558: return alpha | 0xFFF68FAA;
			case 0xB2911B17: return alpha | 0xFFF68FAA;
			case 0x1F9C1B78: return alpha | 0xFFF68FAA;
			case 0x2CFAEDF9: return alpha | 0xEEE685AA;
			case 0xFF8B57D8: return alpha | 0xEEE685AA;
			case 0x6C965839: return alpha | 0xEEE685AA;
			case 0x2F50169A: return alpha | 0xCDC673AA;
			case 0x4C859499: return alpha | 0xCDC673AA;
			case 0xB99094FA: return alpha | 0xCDC673AA;
			case 0x31A53F3B: return alpha | 0x8B864EAA;
			case 0x997FD15A: return alpha | 0x8B864EAA;
			case 0x068AD1BB: return alpha | 0x8B864EAA;
			case 0x586F5306: return alpha | 0xFFEC8BAA;
			case 0x72E0ED04: return alpha | 0xFFEC8BAA;
			case 0xDED79B06: return alpha | 0xFFEC8BAA;
			case 0xFBB6C0C7: return alpha | 0xEEDC82AA;
			case 0x05BACF05: return alpha | 0xEEDC82AA;
			case 0x71B17D07: return alpha | 0xEEDC82AA;
			case 0x9EFE2E88: return alpha | 0xCDBE70AA;
			case 0x9894B106: return alpha | 0xCDBE70AA;
			case 0x048B5F08: return alpha | 0xCDBE70AA;
			case 0x42459C49: return alpha | 0x8B814CAA;
			case 0x2B6E9307: return alpha | 0x8B814CAA;
			case 0x97654109: return alpha | 0x8B814CAA;
			case 0xEE9D34C4: return alpha | 0xFFFFE0AA;
			case 0x0F1DBEE2: return alpha | 0xFFFFE0AA;
			case 0xF3C56884: return alpha | 0xFFFFE0AA;
			case 0x1F909225: return alpha | 0xEEEED1AA;
			case 0x4A5DF883: return alpha | 0xEEEED1AA;
			case 0x2F05A225: return alpha | 0xEEEED1AA;
			case 0x5083EF86: return alpha | 0xCDCDB4AA;
			case 0x859E3224: return alpha | 0xCDCDB4AA;
			case 0x6A45DBC6: return alpha | 0xCDCDB4AA;
			case 0x81774CE7: return alpha | 0x8B8B7AAA;
			case 0xC0DE6BC5: return alpha | 0x8B8B7AAA;
			case 0xA5861567: return alpha | 0x8B8B7AAA;
			case 0xA05523EC: return alpha | 0xFFFF00AA;
			case 0x25AB318B: return alpha | 0xFFFF00AA;
			case 0x34163E0C: return alpha | 0xFFFF00AA;
			case 0xED4F60AD: return alpha | 0xEEEE00AA;
			case 0x11ED066C: return alpha | 0xEEEE00AA;
			case 0x205812ED: return alpha | 0xEEEE00AA;
			case 0x3A499D6E: return alpha | 0xCDCD00AA;
			case 0xFE2EDB4D: return alpha | 0xCDCD00AA;
			case 0x0C99E7CE: return alpha | 0xCDCD00AA;
			case 0x8743DA2F: return alpha | 0x8B8B00AA;
			case 0xEA70B02E: return alpha | 0x8B8B00AA;
			case 0xF8DBBCAF: return alpha | 0x8B8B00AA;
			case 0x01481F96: return alpha | 0xFFD700AA;
			case 0x2C303975: return alpha | 0xFFD700AA;
			case 0x27BC31B6: return alpha | 0xFFD700AA;
			case 0x015A3817: return alpha | 0xEEC900AA;
			case 0x2E856216: return alpha | 0xEEC900AA;
			case 0x2A115A57: return alpha | 0xEEC900AA;
			case 0x016C5098: return alpha | 0xCDAD00AA;
			case 0x30DA8AB7: return alpha | 0xCDAD00AA;
			case 0x2C6682F8: return alpha | 0xCDAD00AA;
			case 0x017E6919: return alpha | 0x8B7500AA;
			case 0x332FB358: return alpha | 0x8B7500AA;
			case 0x2EBBAB99: return alpha | 0x8B7500AA;
			case 0x7D28D0EE: return alpha | 0xFFC125AA;
			case 0x1236EE2D: return alpha | 0xFFC125AA;
			case 0x139D370E: return alpha | 0xFFC125AA;
			case 0x8133620F: return alpha | 0xEEB422AA;
			case 0x9793A36E: return alpha | 0xEEB422AA;
			case 0x98F9EC4F: return alpha | 0xEEB422AA;
			case 0x853DF330: return alpha | 0xCD9B1DAA;
			case 0x1CF058AF: return alpha | 0xCD9B1DAA;
			case 0x1E56A190: return alpha | 0xCD9B1DAA;
			case 0x89488451: return alpha | 0x8B6914AA;
			case 0xA24D0DF0: return alpha | 0x8B6914AA;
			case 0xA3B356D1: return alpha | 0x8B6914AA;
			case 0x960E1DD0: return alpha | 0xFFB90FAA;
			case 0x7F95700E: return alpha | 0xFFB90FAA;
			case 0x4C8D65D0: return alpha | 0xFFB90FAA;
			case 0xD14E5771: return alpha | 0xEEAD0EAA;
			case 0x8BCA95EF: return alpha | 0xEEAD0EAA;
			case 0x58C28BB1: return alpha | 0xEEAD0EAA;
			case 0x0C8E9112: return alpha | 0xCD950CAA;
			case 0x97FFBBD0: return alpha | 0xCD950CAA;
			case 0x64F7B192: return alpha | 0xCD950CAA;
			case 0x47CECAB3: return alpha | 0x8B6508AA;
			case 0xA434E1B1: return alpha | 0x8B6508AA;
			case 0x712CD773: return alpha | 0x8B6508AA;
			case 0x8E4F2685: return alpha | 0xFFC1C1AA;
			case 0x8F75AA83: return alpha | 0xFFC1C1AA;
			case 0xB93107C5: return alpha | 0xFFC1C1AA;
			case 0x9259B7A6: return alpha | 0xEEB4B4AA;
			case 0xC06907E4: return alpha | 0xEEB4B4AA;
			case 0xEA246526: return alpha | 0xEEB4B4AA;
			case 0x966448C7: return alpha | 0xCD9B9BAA;
			case 0xF15C6545: return alpha | 0xCD9B9BAA;
			case 0x1B17C287: return alpha | 0xCD9B9BAA;
			case 0x9A6ED9E8: return alpha | 0x8B6969AA;
			case 0x224FC2A6: return alpha | 0x8B6969AA;
			case 0x4C0B1FE8: return alpha | 0x8B6969AA;
			case 0x4250B9DE: return alpha | 0xFF6A6AAA;
			case 0xFD9CA3FC: return alpha | 0xFF6A6AAA;
			case 0x3A37157E: return alpha | 0xFF6A6AAA;
			case 0x465B4AFF: return alpha | 0xEE6363AA;
			case 0x2E90015D: return alpha | 0xEE6363AA;
			case 0x6B2A72DF: return alpha | 0xEE6363AA;
			case 0x4A65DC20: return alpha | 0xCD5555AA;
			case 0x5F835EBE: return alpha | 0xCD5555AA;
			case 0x9C1DD040: return alpha | 0xCD5555AA;
			case 0x4E706D41: return alpha | 0x8B3A3AAA;
			case 0x9076BC1F: return alpha | 0x8B3A3AAA;
			case 0xCD112DA1: return alpha | 0x8B3A3AAA;
			case 0x6CF2890E: return alpha | 0xFF8247AA;
			case 0xF24896AD: return alpha | 0xFF8247AA;
			case 0x00B3A32E: return alpha | 0xFF8247AA;
			case 0xB9ECC5CF: return alpha | 0xEE7942AA;
			case 0xDE8A6B8E: return alpha | 0xEE7942AA;
			case 0xECF5780F: return alpha | 0xEE7942AA;
			case 0x06E70290: return alpha | 0xCD6839AA;
			case 0xCACC406F: return alpha | 0xCD6839AA;
			case 0xD9374CF0: return alpha | 0xCD6839AA;
			case 0x53E13F51: return alpha | 0x8B4726AA;
			case 0xB70E1550: return alpha | 0x8B4726AA;
			case 0xC57921D1: return alpha | 0x8B4726AA;
			case 0xACA6EFB7: return alpha | 0xFFD39BAA;
			case 0x41B50CF6: return alpha | 0xFFD39BAA;
			case 0x431B55D7: return alpha | 0xFFD39BAA;
			case 0xB0B180D8: return alpha | 0xEEC591AA;
			case 0xC711C237: return alpha | 0xEEC591AA;
			case 0xC8780B18: return alpha | 0xEEC591AA;
			case 0xB4BC11F9: return alpha | 0xCDAA7DAA;
			case 0x4C6E7778: return alpha | 0xCDAA7DAA;
			case 0x4DD4C059: return alpha | 0xCDAA7DAA;
			case 0xB8C6A31A: return alpha | 0x8B7355AA;
			case 0xD1CB2CB9: return alpha | 0x8B7355AA;
			case 0xD331759A: return alpha | 0x8B7355AA;
			case 0x2B676829: return alpha | 0xFFE7BAAA;
			case 0xB352BDE8: return alpha | 0xFFE7BAAA;
			case 0x205DBE49: return alpha | 0xFFE7BAAA;
			case 0x2DBC90CA: return alpha | 0xEED8AEAA;
			case 0x004CFAA9: return alpha | 0xEED8AEAA;
			case 0x6D57FB0A: return alpha | 0xEED8AEAA;
			case 0x3011B96B: return alpha | 0xCDBA96AA;
			case 0x4D47376A: return alpha | 0xCDBA96AA;
			case 0xBA5237CB: return alpha | 0xCDBA96AA;
			case 0x3266E20C: return alpha | 0x8B7E66AA;
			case 0x9A41742B: return alpha | 0x8B7E66AA;
			case 0x074C748C: return alpha | 0x8B7E66AA;
			case 0x000A1A93: return alpha | 0xFFA54FAA;
			case 0x0156F492: return alpha | 0xFFA54FAA;
			case 0x013468B3: return alpha | 0xFFA54FAA;
			case 0x000AA6F4: return alpha | 0xEE9A49AA;
			case 0x01690D13: return alpha | 0xEE9A49AA;
			case 0x01468134: return alpha | 0xEE9A49AA;
			case 0x000B3355: return alpha | 0xCD853FAA;
			case 0x017B2594: return alpha | 0xCD853FAA;
			case 0x015899B5: return alpha | 0xCD853FAA;
			case 0x000BBFB6: return alpha | 0x8B5A2BAA;
			case 0x018D3E15: return alpha | 0x8B5A2BAA;
			case 0x016AB236: return alpha | 0x8B5A2BAA;
			case 0x6E5A84C2: return alpha | 0xFF7F24AA;
			case 0x0368A201: return alpha | 0xFF7F24AA;
			case 0x04CEEAE2: return alpha | 0xFF7F24AA;
			case 0x726515E3: return alpha | 0xEE7621AA;
			case 0x88C55742: return alpha | 0xEE7621AA;
			case 0x8A2BA023: return alpha | 0xEE7621AA;
			case 0x766FA704: return alpha | 0xCD661DAA;
			case 0x0E220C83: return alpha | 0xCD661DAA;
			case 0x0F885564: return alpha | 0xCD661DAA;
			case 0x7A7A3825: return alpha | 0x8B4513AA;
			case 0x937EC1C4: return alpha | 0x8B4513AA;
			case 0x94E50AA5: return alpha | 0x8B4513AA;
			case 0xEDCCC8C1: return alpha | 0xFF3030AA;
			case 0x82DAE600: return alpha | 0xFF3030AA;
			case 0x84412EE1: return alpha | 0xFF3030AA;
			case 0xF1D759E2: return alpha | 0xEE2C2CAA;
			case 0x08379B41: return alpha | 0xEE2C2CAA;
			case 0x099DE422: return alpha | 0xEE2C2CAA;
			case 0xF5E1EB03: return alpha | 0xCD2626AA;
			case 0x8D945082: return alpha | 0xCD2626AA;
			case 0x8EFA9963: return alpha | 0xCD2626AA;
			case 0xF9EC7C24: return alpha | 0x8B1A1AAA;
			case 0x12F105C3: return alpha | 0x8B1A1AAA;
			case 0x14574EA4: return alpha | 0x8B1A1AAA;
			case 0x2B071138: return alpha | 0xFF4040AA;
			case 0xB2F266F7: return alpha | 0xFF4040AA;
			case 0x1FFD6758: return alpha | 0xFF4040AA;
			case 0x2D5C39D9: return alpha | 0xEE3B3BAA;
			case 0xFFECA3B8: return alpha | 0xEE3B3BAA;
			case 0x6CF7A419: return alpha | 0xEE3B3BAA;
			case 0x2FB1627A: return alpha | 0xCD3333AA;
			case 0x4CE6E079: return alpha | 0xCD3333AA;
			case 0xB9F1E0DA: return alpha | 0xCD3333AA;
			case 0x32068B1B: return alpha | 0x8B2323AA;
			case 0x99E11D3A: return alpha | 0x8B2323AA;
			case 0x06EC1D9B: return alpha | 0x8B2323AA;
			case 0x8B57421A: return alpha | 0xFF8C69AA;
			case 0x10AD4FB9: return alpha | 0xFF8C69AA;
			case 0x1F185C3A: return alpha | 0xFF8C69AA;
			case 0xD8517EDB: return alpha | 0xEE8262AA;
			case 0xFCEF249A: return alpha | 0xEE8262AA;
			case 0x0B5A311B: return alpha | 0xEE8262AA;
			case 0x254BBB9C: return alpha | 0xCD7054AA;
			case 0xE930F97B: return alpha | 0xCD7054AA;
			case 0xF79C05FC: return alpha | 0xCD7054AA;
			case 0x7245F85D: return alpha | 0x8B4C39AA;
			case 0xD572CE5C: return alpha | 0x8B4C39AA;
			case 0xE3DDDADD: return alpha | 0x8B4C39AA;
			case 0x70EF5FB2: return alpha | 0xFFA07AAA;
			case 0xDBB54790: return alpha | 0xFFA07AAA;
			case 0xC05CF132: return alpha | 0xFFA07AAA;
			case 0xA1E2BD13: return alpha | 0xEE9572AA;
			case 0x16F58131: return alpha | 0xEE9572AA;
			case 0xFB9D2AD3: return alpha | 0xEE9572AA;
			case 0xD2D61A74: return alpha | 0xCD8162AA;
			case 0x5235BAD2: return alpha | 0xCD8162AA;
			case 0x36DD6474: return alpha | 0xCD8162AA;
			case 0x03C977D5: return alpha | 0x8B5742AA;
			case 0x8D75F473: return alpha | 0x8B5742AA;
			case 0x721D9E15: return alpha | 0x8B5742AA;
			case 0x75C8702C: return alpha | 0xFFA500AA;
			case 0xFB1E7DCB: return alpha | 0xFFA500AA;
			case 0x09898A4C: return alpha | 0xFFA500AA;
			case 0xC2C2ACED: return alpha | 0xEE9A00AA;
			case 0xE76052AC: return alpha | 0xEE9A00AA;
			case 0xF5CB5F2D: return alpha | 0xEE9A00AA;
			case 0x0FBCE9AE: return alpha | 0xCD8500AA;
			case 0xD3A2278D: return alpha | 0xCD8500AA;
			case 0xE20D340E: return alpha | 0xCD8500AA;
			case 0x5CB7266F: return alpha | 0x8B5A00AA;
			case 0xBFE3FC6E: return alpha | 0x8B5A00AA;
			case 0xCE4F08EF: return alpha | 0x8B5A00AA;
			case 0x07C72C0E: return alpha | 0xFF7F00AA;
			case 0x131D726C: return alpha | 0xFF7F00AA;
			case 0x02C56FCE: return alpha | 0xFF7F00AA;
			case 0x8D23E14F: return alpha | 0xEE7600AA;
			case 0x627C7BED: return alpha | 0xEE7600AA;
			case 0x5224794F: return alpha | 0xEE7600AA;
			case 0x12809690: return alpha | 0xCD6600AA;
			case 0xB1DB856E: return alpha | 0xCD6600AA;
			case 0xA18382D0: return alpha | 0xCD6600AA;
			case 0x97DD4BD1: return alpha | 0x8B4500AA;
			case 0x013A8EEF: return alpha | 0x8B4500AA;
			case 0xF0E28C51: return alpha | 0x8B4500AA;
			case 0x2AD6DC41: return alpha | 0xFF7256AA;
			case 0xB2C23200: return alpha | 0xFF7256AA;
			case 0x1FCD3261: return alpha | 0xFF7256AA;
			case 0x2D2C04E2: return alpha | 0xEE6A50AA;
			case 0xFFBC6EC1: return alpha | 0xEE6A50AA;
			case 0x6CC76F22: return alpha | 0xEE6A50AA;
			case 0x2F812D83: return alpha | 0xCD5B45AA;
			case 0x4CB6AB82: return alpha | 0xCD5B45AA;
			case 0xB9C1ABE3: return alpha | 0xCD5B45AA;
			case 0x31D65624: return alpha | 0x8B3E2FAA;
			case 0x99B0E843: return alpha | 0x8B3E2FAA;
			case 0x06BBE8A4: return alpha | 0x8B3E2FAA;
			case 0x8E0056C4: return alpha | 0xFF6347AA;
			case 0x13566463: return alpha | 0xFF6347AA;
			case 0x21C170E4: return alpha | 0xFF6347AA;
			case 0xDAFA9385: return alpha | 0xEE5C42AA;
			case 0xFF983944: return alpha | 0xEE5C42AA;
			case 0x0E0345C5: return alpha | 0xEE5C42AA;
			case 0x27F4D046: return alpha | 0xCD4F39AA;
			case 0xEBDA0E25: return alpha | 0xCD4F39AA;
			case 0xFA451AA6: return alpha | 0xCD4F39AA;
			case 0x74EF0D07: return alpha | 0x8B3626AA;
			case 0xD81BE306: return alpha | 0x8B3626AA;
			case 0xE686EF87: return alpha | 0x8B3626AA;
			case 0x2DC190E7: return alpha | 0xFF4500AA;
			case 0xE90D7B05: return alpha | 0xFF4500AA;
			case 0x25A7EC87: return alpha | 0xFF4500AA;
			case 0x31CC2208: return alpha | 0xEE4000AA;
			case 0x1A00D866: return alpha | 0xEE4000AA;
			case 0x569B49E8: return alpha | 0xEE4000AA;
			case 0x35D6B329: return alpha | 0xCD3700AA;
			case 0x4AF435C7: return alpha | 0xCD3700AA;
			case 0x878EA749: return alpha | 0xCD3700AA;
			case 0x39E1444A: return alpha | 0x8B2500AA;
			case 0x7BE79328: return alpha | 0x8B2500AA;
			case 0xB88204AA: return alpha | 0x8B2500AA;
			case 0x0009F08B: return alpha | 0xFF0000AA;
			case 0x0156CA8A: return alpha | 0xFF0000AA;
			case 0x01343EAB: return alpha | 0xFF0000AA;
			case 0x000A7CEC: return alpha | 0xEE0000AA;
			case 0x0168E30B: return alpha | 0xEE0000AA;
			case 0x0146572C: return alpha | 0xEE0000AA;
			case 0x000B094D: return alpha | 0xCD0000AA;
			case 0x017AFB8C: return alpha | 0xCD0000AA;
			case 0x01586FAD: return alpha | 0xCD0000AA;
			case 0x000B95AE: return alpha | 0x8B0000AA;
			case 0x018D140D: return alpha | 0x8B0000AA;
			case 0x016A882E: return alpha | 0x8B0000AA;
			case 0xA36C3C00: return alpha | 0xFF1493AA;
			case 0xA717515E: return alpha | 0xFF1493AA;
			case 0xA4099280: return alpha | 0xFF1493AA;
			case 0x17E8AD01: return alpha | 0xEE1289AA;
			case 0x2C74069F: return alpha | 0xEE1289AA;
			case 0x296647C1: return alpha | 0xEE1289AA;
			case 0x8C651E02: return alpha | 0xCD1076AA;
			case 0xB1D0BBE0: return alpha | 0xCD1076AA;
			case 0xAEC2FD02: return alpha | 0xCD1076AA;
			case 0x00E18F03: return alpha | 0x8B0A50AA;
			case 0x372D7121: return alpha | 0x8B0A50AA;
			case 0x341FB243: return alpha | 0x8B0A50AA;
			case 0x0CB5C68D: return alpha | 0xFF6EB4AA;
			case 0xD684A82B: return alpha | 0xFF6EB4AA;
			case 0x2BC24D0D: return alpha | 0xFF6EB4AA;
			case 0xF8F79B6E: return alpha | 0xEE6AA7AA;
			case 0xDA8F394C: return alpha | 0xEE6AA7AA;
			case 0x2FCCDE2E: return alpha | 0xEE6AA7AA;
			case 0xE539704F: return alpha | 0xCD6090AA;
			case 0xDE99CA6D: return alpha | 0xCD6090AA;
			case 0x33D76F4F: return alpha | 0xCD6090AA;
			case 0xD17B4530: return alpha | 0x8B3A62AA;
			case 0xE2A45B8E: return alpha | 0x8B3A62AA;
			case 0x37E20070: return alpha | 0x8B3A62AA;
			case 0x014BFE02: return alpha | 0xFFB5C5AA;
			case 0x2C3417E1: return alpha | 0xFFB5C5AA;
			case 0x27C01022: return alpha | 0xFFB5C5AA;
			case 0x015E1683: return alpha | 0xEEA9B8AA;
			case 0x2E894082: return alpha | 0xEEA9B8AA;
			case 0x2A1538C3: return alpha | 0xEEA9B8AA;
			case 0x01702F04: return alpha | 0xCD919EAA;
			case 0x30DE6923: return alpha | 0xCD919EAA;
			case 0x2C6A6164: return alpha | 0xCD919EAA;
			case 0x01824785: return alpha | 0x8B636CAA;
			case 0x333391C4: return alpha | 0x8B636CAA;
			case 0x2EBF8A05: return alpha | 0x8B636CAA;
			case 0x113DCC9A: return alpha | 0xFFAEB9AA;
			case 0x8A4B8DB8: return alpha | 0xFFAEB9AA;
			case 0x2585F31A: return alpha | 0xFFAEB9AA;
			case 0x15485DBB: return alpha | 0xEEA2ADAA;
			case 0xBB3EEB19: return alpha | 0xEEA2ADAA;
			case 0x5679507B: return alpha | 0xEEA2ADAA;
			case 0x1952EEDC: return alpha | 0xCD8C95AA;
			case 0xEC32487A: return alpha | 0xCD8C95AA;
			case 0x876CADDC: return alpha | 0xCD8C95AA;
			case 0x1D5D7FFD: return alpha | 0x8B5F65AA;
			case 0x1D25A5DB: return alpha | 0x8B5F65AA;
			case 0xB8600B3D: return alpha | 0x8B5F65AA;
			case 0x00D65420: return alpha | 0xFF82ABAA;
			case 0xBCBC989D: return alpha | 0xFF82ABAA;
			case 0xAB5043A0: return alpha | 0xFF82ABAA;
			case 0x3C168DC1: return alpha | 0xEE799FAA;
			case 0x4F967A9E: return alpha | 0xEE799FAA;
			case 0x3E2A25A1: return alpha | 0xEE799FAA;
			case 0x7756C762: return alpha | 0xCD6889AA;
			case 0xE2705C9F: return alpha | 0xCD6889AA;
			case 0xD10407A2: return alpha | 0xCD6889AA;
			case 0xB2970103: return alpha | 0x8B475DAA;
			case 0x754A3EA0: return alpha | 0x8B475DAA;
			case 0x63DDE9A3: return alpha | 0x8B475DAA;
			case 0x8B58745C: return alpha | 0xFF34B3AA;
			case 0x10AE81FB: return alpha | 0xFF34B3AA;
			case 0x1F198E7C: return alpha | 0xFF34B3AA;
			case 0xD852B11D: return alpha | 0xEE30A7AA;
			case 0xFCF056DC: return alpha | 0xEE30A7AA;
			case 0x0B5B635D: return alpha | 0xEE30A7AA;
			case 0x254CEDDE: return alpha | 0xCD2990AA;
			case 0xE9322BBD: return alpha | 0xCD2990AA;
			case 0xF79D383E: return alpha | 0xCD2990AA;
			case 0x72472A9F: return alpha | 0x8B1C62AA;
			case 0xD574009E: return alpha | 0x8B1C62AA;
			case 0xE3DF0D1F: return alpha | 0x8B1C62AA;
			case 0x5099E2FE: return alpha | 0xFF3E96AA;
			case 0x0BE5CD1C: return alpha | 0xFF3E96AA;
			case 0x48803E9E: return alpha | 0xFF3E96AA;
			case 0x54A4741F: return alpha | 0xEE3A8CAA;
			case 0x3CD92A7D: return alpha | 0xEE3A8CAA;
			case 0x79739BFF: return alpha | 0xEE3A8CAA;
			case 0x58AF0540: return alpha | 0xCD3278AA;
			case 0x6DCC87DE: return alpha | 0xCD3278AA;
			case 0xAA66F960: return alpha | 0xCD3278AA;
			case 0x5CB99661: return alpha | 0x8B2252AA;
			case 0x9EBFE53F: return alpha | 0x8B2252AA;
			case 0xDB5A56C1: return alpha | 0x8B2252AA;
			case 0x1942940D: return alpha | 0xFF00FFAA;
			case 0x495A558C: return alpha | 0xFF00FFAA;
			case 0x2526F22D: return alpha | 0xFF00FFAA;
			case 0x058468EE: return alpha | 0xEE00EEAA;
			case 0xBDD6C68D: return alpha | 0xEE00EEAA;
			case 0x99A3632E: return alpha | 0xEE00EEAA;
			case 0xF1C63DCF: return alpha | 0xCD00CDAA;
			case 0x3253378E: return alpha | 0xCD00CDAA;
			case 0x0E1FD42F: return alpha | 0xCD00CDAA;
			case 0xDE0812B0: return alpha | 0x8B008BAA;
			case 0xA6CFA88F: return alpha | 0x8B008BAA;
			case 0x829C4530: return alpha | 0x8B008BAA;
			case 0x739436C9: return alpha | 0xFF83FAAA;
			case 0xF8EA4468: return alpha | 0xFF83FAAA;
			case 0x075550E9: return alpha | 0xFF83FAAA;
			case 0xC08E738A: return alpha | 0xEE7AE9AA;
			case 0xE52C1949: return alpha | 0xEE7AE9AA;
			case 0xF39725CA: return alpha | 0xEE7AE9AA;
			case 0x0D88B04B: return alpha | 0xCD69C9AA;
			case 0xD16DEE2A: return alpha | 0xCD69C9AA;
			case 0xDFD8FAAB: return alpha | 0xCD69C9AA;
			case 0x5A82ED0C: return alpha | 0x8B4789AA;
			case 0xBDAFC30B: return alpha | 0x8B4789AA;
			case 0xCC1ACF8C: return alpha | 0x8B4789AA;
			case 0x014D34EE: return alpha | 0xFFBBFFAA;
			case 0x2C354ECD: return alpha | 0xFFBBFFAA;
			case 0x27C1470E: return alpha | 0xFFBBFFAA;
			case 0x015F4D6F: return alpha | 0xEEAEEEAA;
			case 0x2E8A776E: return alpha | 0xEEAEEEAA;
			case 0x2A166FAF: return alpha | 0xEEAEEEAA;
			case 0x017165F0: return alpha | 0xCD96CDAA;
			case 0x30DFA00F: return alpha | 0xCD96CDAA;
			case 0x2C6B9850: return alpha | 0xCD96CDAA;
			case 0x01837E71: return alpha | 0x8B668BAA;
			case 0x3334C8B0: return alpha | 0x8B668BAA;
			case 0x2EC0C0F1: return alpha | 0x8B668BAA;
			case 0xC5A6F6EA: return alpha | 0xE066FFAA;
			case 0x4F995868: return alpha | 0xE066FFAA;
			case 0xC936364A: return alpha | 0xE066FFAA;
			case 0x1506006B: return alpha | 0xD15FEEAA;
			case 0xF2E0C629: return alpha | 0xD15FEEAA;
			case 0x6C7DA40B: return alpha | 0xD15FEEAA;
			case 0x646509EC: return alpha | 0xB452CDAA;
			case 0x962833EA: return alpha | 0xB452CDAA;
			case 0x0FC511CC: return alpha | 0xB452CDAA;
			case 0xB3C4136D: return alpha | 0x7A378BAA;
			case 0x396FA1AB: return alpha | 0x7A378BAA;
			case 0xB30C7F8D: return alpha | 0x7A378BAA;
			case 0xFD1EF92B: return alpha | 0xBF3EFFAA;
			case 0xB36EE329: return alpha | 0xBF3EFFAA;
			case 0xA316E08B: return alpha | 0xBF3EFFAA;
			case 0x827BAE6C: return alpha | 0xB23AEEAA;
			case 0x02CDECAA: return alpha | 0xB23AEEAA;
			case 0xF275EA0C: return alpha | 0xB23AEEAA;
			case 0x07D863AD: return alpha | 0x9A32CDAA;
			case 0x522CF62B: return alpha | 0x9A32CDAA;
			case 0x41D4F38D: return alpha | 0x9A32CDAA;
			case 0x8D3518EE: return alpha | 0x68228BAA;
			case 0xA18BFFAC: return alpha | 0x68228BAA;
			case 0x9133FD0E: return alpha | 0x68228BAA;
			case 0x76244C28: return alpha | 0x9B30FFAA;
			case 0xFB7A59C7: return alpha | 0x9B30FFAA;
			case 0x09E56648: return alpha | 0x9B30FFAA;
			case 0xC31E88E9: return alpha | 0x912CEEAA;
			case 0xE7BC2EA8: return alpha | 0x912CEEAA;
			case 0xF6273B29: return alpha | 0x912CEEAA;
			case 0x1018C5AA: return alpha | 0x7D26CDAA;
			case 0xD3FE0389: return alpha | 0x7D26CDAA;
			case 0xE269100A: return alpha | 0x7D26CDAA;
			case 0x5D13026B: return alpha | 0x551A8BAA;
			case 0xC03FD86A: return alpha | 0x551A8BAA;
			case 0xCEAAE4EB: return alpha | 0x551A8BAA;
			case 0x8C0F5789: return alpha | 0xAB82FFAA;
			case 0xE30DCCE7: return alpha | 0xAB82FFAA;
			case 0x5CAAAAC9: return alpha | 0xAB82FFAA;
			case 0xDB6E610A: return alpha | 0x9F79EEAA;
			case 0x86553AA8: return alpha | 0x9F79EEAA;
			case 0xFFF2188A: return alpha | 0x9F79EEAA;
			case 0x2ACD6A8B: return alpha | 0x8968CDAA;
			case 0x299CA869: return alpha | 0x8968CDAA;
			case 0xA339864B: return alpha | 0x8968CDAA;
			case 0x7A2C740C: return alpha | 0x5D478BAA;
			case 0xCCE4162A: return alpha | 0x5D478BAA;
			case 0x4680F40C: return alpha | 0x5D478BAA;
			case 0x3AF68BCD: return alpha | 0xFFE1FFAA;
			case 0x6B0E4D4C: return alpha | 0xFFE1FFAA;
			case 0x46DAE9ED: return alpha | 0xFFE1FFAA;
			case 0x273860AE: return alpha | 0xEED2EEAA;
			case 0xDF8ABE4D: return alpha | 0xEED2EEAA;
			case 0xBB575AEE: return alpha | 0xEED2EEAA;
			case 0x137A358F: return alpha | 0xCDB5CDAA;
			case 0x54072F4E: return alpha | 0xCDB5CDAA;
			case 0x2FD3CBEF: return alpha | 0xCDB5CDAA;
			case 0xFFBC0A70: return alpha | 0x8B7B8BAA;
			case 0xC883A04F: return alpha | 0x8B7B8BAA;
			case 0xA4503CF0: return alpha | 0x8B7B8BAA;
			case 0x01415CA2: return alpha | 0x000000AA;
			case 0x29E66661: return alpha | 0x000000AA;
			case 0x25725EA2: return alpha | 0x000000AA;
			case 0x01416DA6: return alpha | 0x000000AA;
			case 0x29E67765: return alpha | 0x000000AA;
			case 0x25726FA6: return alpha | 0x000000AA;
			case 0x01537523: return alpha | 0x030303AA;
			case 0x2C3B8F02: return alpha | 0x030303AA;
			case 0x27C78743: return alpha | 0x030303AA;
			case 0x01538627: return alpha | 0x030303AA;
			case 0x2C3BA006: return alpha | 0x030303AA;
			case 0x27C79847: return alpha | 0x030303AA;
			case 0x01658DA4: return alpha | 0x050505AA;
			case 0x2E90B7A3: return alpha | 0x050505AA;
			case 0x2A1CAFE4: return alpha | 0x050505AA;
			case 0x01659EA8: return alpha | 0x050505AA;
			case 0x2E90C8A7: return alpha | 0x050505AA;
			case 0x2A1CC0E8: return alpha | 0x050505AA;
			case 0x0177A625: return alpha | 0x080808AA;
			case 0x30E5E044: return alpha | 0x080808AA;
			case 0x2C71D885: return alpha | 0x080808AA;
			case 0x0177B729: return alpha | 0x080808AA;
			case 0x30E5F148: return alpha | 0x080808AA;
			case 0x2C71E989: return alpha | 0x080808AA;
			case 0x0189BEA6: return alpha | 0x0A0A0AAA;
			case 0x333B08E5: return alpha | 0x0A0A0AAA;
			case 0x2EC70126: return alpha | 0x0A0A0AAA;
			case 0x0189CFAA: return alpha | 0x0A0A0AAA;
			case 0x333B19E9: return alpha | 0x0A0A0AAA;
			case 0x2EC7122A: return alpha | 0x0A0A0AAA;
			case 0x019BD727: return alpha | 0x0D0D0DAA;
			case 0x35903186: return alpha | 0x0D0D0DAA;
			case 0x311C29C7: return alpha | 0x0D0D0DAA;
			case 0x019BE82B: return alpha | 0x0D0D0DAA;
			case 0x3590428A: return alpha | 0x0D0D0DAA;
			case 0x311C3ACB: return alpha | 0x0D0D0DAA;
			case 0x01ADEFA8: return alpha | 0x0F0F0FAA;
			case 0x37E55A27: return alpha | 0x0F0F0FAA;
			case 0x33715268: return alpha | 0x0F0F0FAA;
			case 0x01AE00AC: return alpha | 0x0F0F0FAA;
			case 0x37E56B2B: return alpha | 0x0F0F0FAA;
			case 0x3371636C: return alpha | 0x0F0F0FAA;
			case 0x01C00829: return alpha | 0x121212AA;
			case 0x3A3A82C8: return alpha | 0x121212AA;
			case 0x35C67B09: return alpha | 0x121212AA;
			case 0x01C0192D: return alpha | 0x121212AA;
			case 0x3A3A93CC: return alpha | 0x121212AA;
			case 0x35C68C0D: return alpha | 0x121212AA;
			case 0x01D220AA: return alpha | 0x141414AA;
			case 0x3C8FAB69: return alpha | 0x141414AA;
			case 0x381BA3AA: return alpha | 0x141414AA;
			case 0x01D231AE: return alpha | 0x141414AA;
			case 0x3C8FBC6D: return alpha | 0x141414AA;
			case 0x381BB4AE: return alpha | 0x141414AA;
			case 0x01E4392B: return alpha | 0x171717AA;
			case 0x3EE4D40A: return alpha | 0x171717AA;
			case 0x3A70CC4B: return alpha | 0x171717AA;
			case 0x01E44A2F: return alpha | 0x171717AA;
			case 0x3EE4E50E: return alpha | 0x171717AA;
			case 0x3A70DD4F: return alpha | 0x171717AA;
			case 0x26A5FF33: return alpha | 0x1A1A1AAA;
			case 0xFBDF5B12: return alpha | 0x1A1A1AAA;
			case 0xF76B5353: return alpha | 0x1A1A1AAA;
			case 0x26A61037: return alpha | 0x1A1A1AAA;
			case 0xFBDF6C16: return alpha | 0x1A1A1AAA;
			case 0xF76B6457: return alpha | 0x1A1A1AAA;
			case 0x28FB27D4: return alpha | 0x1C1C1CAA;
			case 0x48D997D3: return alpha | 0x1C1C1CAA;
			case 0x44659014: return alpha | 0x1C1C1CAA;
			case 0x28FB38D8: return alpha | 0x1C1C1CAA;
			case 0x48D9A8D7: return alpha | 0x1C1C1CAA;
			case 0x4465A118: return alpha | 0x1C1C1CAA;
			case 0x2B505075: return alpha | 0x1F1F1FAA;
			case 0x95D3D494: return alpha | 0x1F1F1FAA;
			case 0x915FCCD5: return alpha | 0x1F1F1FAA;
			case 0x2B506179: return alpha | 0x1F1F1FAA;
			case 0x95D3E598: return alpha | 0x1F1F1FAA;
			case 0x915FDDD9: return alpha | 0x1F1F1FAA;
			case 0x2DA57916: return alpha | 0x212121AA;
			case 0xE2CE1155: return alpha | 0x212121AA;
			case 0xDE5A0996: return alpha | 0x212121AA;
			case 0x2DA58A1A: return alpha | 0x212121AA;
			case 0xE2CE2259: return alpha | 0x212121AA;
			case 0xDE5A1A9A: return alpha | 0x212121AA;
			case 0x2FFAA1B7: return alpha | 0x242424AA;
			case 0x2FC84E16: return alpha | 0x242424AA;
			case 0x2B544657: return alpha | 0x242424AA;
			case 0x2FFAB2BB: return alpha | 0x242424AA;
			case 0x2FC85F1A: return alpha | 0x242424AA;
			case 0x2B54575B: return alpha | 0x242424AA;
			case 0x324FCA58: return alpha | 0x262626AA;
			case 0x7CC28AD7: return alpha | 0x262626AA;
			case 0x784E8318: return alpha | 0x262626AA;
			case 0x324FDB5C: return alpha | 0x262626AA;
			case 0x7CC29BDB: return alpha | 0x262626AA;
			case 0x784E941C: return alpha | 0x262626AA;
			case 0x34A4F2F9: return alpha | 0x292929AA;
			case 0xC9BCC798: return alpha | 0x292929AA;
			case 0xC548BFD9: return alpha | 0x292929AA;
			case 0x34A503FD: return alpha | 0x292929AA;
			case 0xC9BCD89C: return alpha | 0x292929AA;
			case 0xC548D0DD: return alpha | 0x292929AA;
			case 0x36FA1B9A: return alpha | 0x2B2B2BAA;
			case 0x16B70459: return alpha | 0x2B2B2BAA;
			case 0x1242FC9A: return alpha | 0x2B2B2BAA;
			case 0x36FA2C9E: return alpha | 0x2B2B2BAA;
			case 0x16B7155D: return alpha | 0x2B2B2BAA;
			case 0x12430D9E: return alpha | 0x2B2B2BAA;
			case 0x394F443B: return alpha | 0x2E2E2EAA;
			case 0x63B1411A: return alpha | 0x2E2E2EAA;
			case 0x5F3D395B: return alpha | 0x2E2E2EAA;
			case 0x394F553F: return alpha | 0x2E2E2EAA;
			case 0x63B1521E: return alpha | 0x2E2E2EAA;
			case 0x5F3D4A5F: return alpha | 0x2E2E2EAA;
			case 0x3BA46CDC: return alpha | 0x303030AA;
			case 0xB0AB7DDB: return alpha | 0x303030AA;
			case 0xAC37761C: return alpha | 0x303030AA;
			case 0x3BA47DE0: return alpha | 0x303030AA;
			case 0xB0AB8EDF: return alpha | 0x303030AA;
			case 0xAC378720: return alpha | 0x303030AA;
			case 0x26B817B4: return alpha | 0x333333AA;
			case 0xFE3483B3: return alpha | 0x333333AA;
			case 0xF9C07BF4: return alpha | 0x333333AA;
			case 0x26B828B8: return alpha | 0x333333AA;
			case 0xFE3494B7: return alpha | 0x333333AA;
			case 0xF9C08CF8: return alpha | 0x333333AA;
			case 0x290D4055: return alpha | 0x363636AA;
			case 0x4B2EC074: return alpha | 0x363636AA;
			case 0x46BAB8B5: return alpha | 0x363636AA;
			case 0x290D5159: return alpha | 0x363636AA;
			case 0x4B2ED178: return alpha | 0x363636AA;
			case 0x46BAC9B9: return alpha | 0x363636AA;
			case 0x2B6268F6: return alpha | 0x383838AA;
			case 0x9828FD35: return alpha | 0x383838AA;
			case 0x93B4F576: return alpha | 0x383838AA;
			case 0x2B6279FA: return alpha | 0x383838AA;
			case 0x98290E39: return alpha | 0x383838AA;
			case 0x93B5067A: return alpha | 0x383838AA;
			case 0x2DB79197: return alpha | 0x3B3B3BAA;
			case 0xE52339F6: return alpha | 0x3B3B3BAA;
			case 0xE0AF3237: return alpha | 0x3B3B3BAA;
			case 0x2DB7A29B: return alpha | 0x3B3B3BAA;
			case 0xE5234AFA: return alpha | 0x3B3B3BAA;
			case 0xE0AF433B: return alpha | 0x3B3B3BAA;
			case 0x300CBA38: return alpha | 0x3D3D3DAA;
			case 0x321D76B7: return alpha | 0x3D3D3DAA;
			case 0x2DA96EF8: return alpha | 0x3D3D3DAA;
			case 0x300CCB3C: return alpha | 0x3D3D3DAA;
			case 0x321D87BB: return alpha | 0x3D3D3DAA;
			case 0x2DA97FFC: return alpha | 0x3D3D3DAA;
			case 0x3261E2D9: return alpha | 0x404040AA;
			case 0x7F17B378: return alpha | 0x404040AA;
			case 0x7AA3ABB9: return alpha | 0x404040AA;
			case 0x3261F3DD: return alpha | 0x404040AA;
			case 0x7F17C47C: return alpha | 0x404040AA;
			case 0x7AA3BCBD: return alpha | 0x404040AA;
			case 0x34B70B7A: return alpha | 0x424242AA;
			case 0xCC11F039: return alpha | 0x424242AA;
			case 0xC79DE87A: return alpha | 0x424242AA;
			case 0x34B71C7E: return alpha | 0x424242AA;
			case 0xCC12013D: return alpha | 0x424242AA;
			case 0xC79DF97E: return alpha | 0x424242AA;
			case 0x370C341B: return alpha | 0x454545AA;
			case 0x190C2CFA: return alpha | 0x454545AA;
			case 0x1498253B: return alpha | 0x454545AA;
			case 0x370C451F: return alpha | 0x454545AA;
			case 0x190C3DFE: return alpha | 0x454545AA;
			case 0x1498363F: return alpha | 0x454545AA;
			case 0x39615CBC: return alpha | 0x474747AA;
			case 0x660669BB: return alpha | 0x474747AA;
			case 0x619261FC: return alpha | 0x474747AA;
			case 0x39616DC0: return alpha | 0x474747AA;
			case 0x66067ABF: return alpha | 0x474747AA;
			case 0x61927300: return alpha | 0x474747AA;
			case 0x3BB6855D: return alpha | 0x4A4A4AAA;
			case 0xB300A67C: return alpha | 0x4A4A4AAA;
			case 0xAE8C9EBD: return alpha | 0x4A4A4AAA;
			case 0x3BB69661: return alpha | 0x4A4A4AAA;
			case 0xB300B780: return alpha | 0x4A4A4AAA;
			case 0xAE8CAFC1: return alpha | 0x4A4A4AAA;
			case 0x26CA3035: return alpha | 0x4D4D4DAA;
			case 0x0089AC54: return alpha | 0x4D4D4DAA;
			case 0xFC15A495: return alpha | 0x4D4D4DAA;
			case 0x26CA4139: return alpha | 0x4D4D4DAA;
			case 0x0089BD58: return alpha | 0x4D4D4DAA;
			case 0xFC15B599: return alpha | 0x4D4D4DAA;
			case 0x291F58D6: return alpha | 0x4F4F4FAA;
			case 0x4D83E915: return alpha | 0x4F4F4FAA;
			case 0x490FE156: return alpha | 0x4F4F4FAA;
			case 0x291F69DA: return alpha | 0x4F4F4FAA;
			case 0x4D83FA19: return alpha | 0x4F4F4FAA;
			case 0x490FF25A: return alpha | 0x4F4F4FAA;
			case 0x2B748177: return alpha | 0x525252AA;
			case 0x9A7E25D6: return alpha | 0x525252AA;
			case 0x960A1E17: return alpha | 0x525252AA;
			case 0x2B74927B: return alpha | 0x525252AA;
			case 0x9A7E36DA: return alpha | 0x525252AA;
			case 0x960A2F1B: return alpha | 0x525252AA;
			case 0x2DC9AA18: return alpha | 0x545454AA;
			case 0xE7786297: return alpha | 0x545454AA;
			case 0xE3045AD8: return alpha | 0x545454AA;
			case 0x2DC9BB1C: return alpha | 0x545454AA;
			case 0xE778739B: return alpha | 0x545454AA;
			case 0xE3046BDC: return alpha | 0x545454AA;
			case 0x301ED2B9: return alpha | 0x575757AA;
			case 0x34729F58: return alpha | 0x575757AA;
			case 0x2FFE9799: return alpha | 0x575757AA;
			case 0x301EE3BD: return alpha | 0x575757AA;
			case 0x3472B05C: return alpha | 0x575757AA;
			case 0x2FFEA89D: return alpha | 0x575757AA;
			case 0x3273FB5A: return alpha | 0x595959AA;
			case 0x816CDC19: return alpha | 0x595959AA;
			case 0x7CF8D45A: return alpha | 0x595959AA;
			case 0x32740C5E: return alpha | 0x595959AA;
			case 0x816CED1D: return alpha | 0x595959AA;
			case 0x7CF8E55E: return alpha | 0x595959AA;
			case 0x34C923FB: return alpha | 0x5C5C5CAA;
			case 0xCE6718DA: return alpha | 0x5C5C5CAA;
			case 0xC9F3111B: return alpha | 0x5C5C5CAA;
			case 0x34C934FF: return alpha | 0x5C5C5CAA;
			case 0xCE6729DE: return alpha | 0x5C5C5CAA;
			case 0xC9F3221F: return alpha | 0x5C5C5CAA;
			case 0x371E4C9C: return alpha | 0x5E5E5EAA;
			case 0x1B61559B: return alpha | 0x5E5E5EAA;
			case 0x16ED4DDC: return alpha | 0x5E5E5EAA;
			case 0x371E5DA0: return alpha | 0x5E5E5EAA;
			case 0x1B61669F: return alpha | 0x5E5E5EAA;
			case 0x16ED5EE0: return alpha | 0x5E5E5EAA;
			case 0x3973753D: return alpha | 0x616161AA;
			case 0x685B925C: return alpha | 0x616161AA;
			case 0x63E78A9D: return alpha | 0x616161AA;
			case 0x39738641: return alpha | 0x616161AA;
			case 0x685BA360: return alpha | 0x616161AA;
			case 0x63E79BA1: return alpha | 0x616161AA;
			case 0x3BC89DDE: return alpha | 0x636363AA;
			case 0xB555CF1D: return alpha | 0x636363AA;
			case 0xB0E1C75E: return alpha | 0x636363AA;
			case 0x3BC8AEE2: return alpha | 0x636363AA;
			case 0xB555E021: return alpha | 0x636363AA;
			case 0xB0E1D862: return alpha | 0x636363AA;
			case 0x26DC48B6: return alpha | 0x666666AA;
			case 0x02DED4F5: return alpha | 0x666666AA;
			case 0xFE6ACD36: return alpha | 0x666666AA;
			case 0x26DC59BA: return alpha | 0x666666AA;
			case 0x02DEE5F9: return alpha | 0x666666AA;
			case 0xFE6ADE3A: return alpha | 0x666666AA;
			case 0x29317157: return alpha | 0x696969AA;
			case 0x4FD911B6: return alpha | 0x696969AA;
			case 0x4B6509F7: return alpha | 0x696969AA;
			case 0x2931825B: return alpha | 0x696969AA;
			case 0x4FD922BA: return alpha | 0x696969AA;
			case 0x4B651AFB: return alpha | 0x696969AA;
			case 0x2B8699F8: return alpha | 0x6B6B6BAA;
			case 0x9CD34E77: return alpha | 0x6B6B6BAA;
			case 0x985F46B8: return alpha | 0x6B6B6BAA;
			case 0x2B86AAFC: return alpha | 0x6B6B6BAA;
			case 0x9CD35F7B: return alpha | 0x6B6B6BAA;
			case 0x985F57BC: return alpha | 0x6B6B6BAA;
			case 0x2DDBC299: return alpha | 0x6E6E6EAA;
			case 0xE9CD8B38: return alpha | 0x6E6E6EAA;
			case 0xE5598379: return alpha | 0x6E6E6EAA;
			case 0x2DDBD39D: return alpha | 0x6E6E6EAA;
			case 0xE9CD9C3C: return alpha | 0x6E6E6EAA;
			case 0xE559947D: return alpha | 0x6E6E6EAA;
			case 0x3030EB3A: return alpha | 0x707070AA;
			case 0x36C7C7F9: return alpha | 0x707070AA;
			case 0x3253C03A: return alpha | 0x707070AA;
			case 0x3030FC3E: return alpha | 0x707070AA;
			case 0x36C7D8FD: return alpha | 0x707070AA;
			case 0x3253D13E: return alpha | 0x707070AA;
			case 0x328613DB: return alpha | 0x737373AA;
			case 0x83C204BA: return alpha | 0x737373AA;
			case 0x7F4DFCFB: return alpha | 0x737373AA;
			case 0x328624DF: return alpha | 0x737373AA;
			case 0x83C215BE: return alpha | 0x737373AA;
			case 0x7F4E0DFF: return alpha | 0x737373AA;
			case 0x34DB3C7C: return alpha | 0x757575AA;
			case 0xD0BC417B: return alpha | 0x757575AA;
			case 0xCC4839BC: return alpha | 0x757575AA;
			case 0x34DB4D80: return alpha | 0x757575AA;
			case 0xD0BC527F: return alpha | 0x757575AA;
			case 0xCC484AC0: return alpha | 0x757575AA;
			case 0x3730651D: return alpha | 0x787878AA;
			case 0x1DB67E3C: return alpha | 0x787878AA;
			case 0x1942767D: return alpha | 0x787878AA;
			case 0x37307621: return alpha | 0x787878AA;
			case 0x1DB68F40: return alpha | 0x787878AA;
			case 0x19428781: return alpha | 0x787878AA;
			case 0x39858DBE: return alpha | 0x7A7A7AAA;
			case 0x6AB0BAFD: return alpha | 0x7A7A7AAA;
			case 0x663CB33E: return alpha | 0x7A7A7AAA;
			case 0x39859EC2: return alpha | 0x7A7A7AAA;
			case 0x6AB0CC01: return alpha | 0x7A7A7AAA;
			case 0x663CC442: return alpha | 0x7A7A7AAA;
			case 0x3BDAB65F: return alpha | 0x7D7D7DAA;
			case 0xB7AAF7BE: return alpha | 0x7D7D7DAA;
			case 0xB336EFFF: return alpha | 0x7D7D7DAA;
			case 0x3BDAC763: return alpha | 0x7D7D7DAA;
			case 0xB7AB08C2: return alpha | 0x7D7D7DAA;
			case 0xB3370103: return alpha | 0x7D7D7DAA;
			case 0x26EE6137: return alpha | 0x7F7F7FAA;
			case 0x0533FD96: return alpha | 0x7F7F7FAA;
			case 0x00BFF5D7: return alpha | 0x7F7F7FAA;
			case 0x26EE723B: return alpha | 0x7F7F7FAA;
			case 0x05340E9A: return alpha | 0x7F7F7FAA;
			case 0x00C006DB: return alpha | 0x7F7F7FAA;
			case 0x294389D8: return alpha | 0x828282AA;
			case 0x522E3A57: return alpha | 0x828282AA;
			case 0x4DBA3298: return alpha | 0x828282AA;
			case 0x29439ADC: return alpha | 0x828282AA;
			case 0x522E4B5B: return alpha | 0x828282AA;
			case 0x4DBA439C: return alpha | 0x828282AA;
			case 0x2B98B279: return alpha | 0x858585AA;
			case 0x9F287718: return alpha | 0x858585AA;
			case 0x9AB46F59: return alpha | 0x858585AA;
			case 0x2B98C37D: return alpha | 0x858585AA;
			case 0x9F28881C: return alpha | 0x858585AA;
			case 0x9AB4805D: return alpha | 0x858585AA;
			case 0x2DEDDB1A: return alpha | 0x878787AA;
			case 0xEC22B3D9: return alpha | 0x878787AA;
			case 0xE7AEAC1A: return alpha | 0x878787AA;
			case 0x2DEDEC1E: return alpha | 0x878787AA;
			case 0xEC22C4DD: return alpha | 0x878787AA;
			case 0xE7AEBD1E: return alpha | 0x878787AA;
			case 0x304303BB: return alpha | 0x8A8A8AAA;
			case 0x391CF09A: return alpha | 0x8A8A8AAA;
			case 0x34A8E8DB: return alpha | 0x8A8A8AAA;
			case 0x304314BF: return alpha | 0x8A8A8AAA;
			case 0x391D019E: return alpha | 0x8A8A8AAA;
			case 0x34A8F9DF: return alpha | 0x8A8A8AAA;
			case 0x32982C5C: return alpha | 0x8C8C8CAA;
			case 0x86172D5B: return alpha | 0x8C8C8CAA;
			case 0x81A3259C: return alpha | 0x8C8C8CAA;
			case 0x32983D60: return alpha | 0x8C8C8CAA;
			case 0x86173E5F: return alpha | 0x8C8C8CAA;
			case 0x81A336A0: return alpha | 0x8C8C8CAA;
			case 0x34ED54FD: return alpha | 0x8F8F8FAA;
			case 0xD3116A1C: return alpha | 0x8F8F8FAA;
			case 0xCE9D625D: return alpha | 0x8F8F8FAA;
			case 0x34ED6601: return alpha | 0x8F8F8FAA;
			case 0xD3117B20: return alpha | 0x8F8F8FAA;
			case 0xCE9D7361: return alpha | 0x8F8F8FAA;
			case 0x37427D9E: return alpha | 0x919191AA;
			case 0x200BA6DD: return alpha | 0x919191AA;
			case 0x1B979F1E: return alpha | 0x919191AA;
			case 0x37428EA2: return alpha | 0x919191AA;
			case 0x200BB7E1: return alpha | 0x919191AA;
			case 0x1B97B022: return alpha | 0x919191AA;
			case 0x3997A63F: return alpha | 0x949494AA;
			case 0x6D05E39E: return alpha | 0x949494AA;
			case 0x6891DBDF: return alpha | 0x949494AA;
			case 0x3997B743: return alpha | 0x949494AA;
			case 0x6D05F4A2: return alpha | 0x949494AA;
			case 0x6891ECE3: return alpha | 0x949494AA;
			case 0x3BECCEE0: return alpha | 0x969696AA;
			case 0xBA00205F: return alpha | 0x969696AA;
			case 0xB58C18A0: return alpha | 0x969696AA;
			case 0x3BECDFE4: return alpha | 0x969696AA;
			case 0xBA003163: return alpha | 0x969696AA;
			case 0xB58C29A4: return alpha | 0x969696AA;
			case 0x270079B8: return alpha | 0x999999AA;
			case 0x07892637: return alpha | 0x999999AA;
			case 0x03151E78: return alpha | 0x999999AA;
			case 0x27008ABC: return alpha | 0x999999AA;
			case 0x0789373B: return alpha | 0x999999AA;
			case 0x03152F7C: return alpha | 0x999999AA;
			case 0x2955A259: return alpha | 0x9C9C9CAA;
			case 0x548362F8: return alpha | 0x9C9C9CAA;
			case 0x500F5B39: return alpha | 0x9C9C9CAA;
			case 0x2955B35D: return alpha | 0x9C9C9CAA;
			case 0x548373FC: return alpha | 0x9C9C9CAA;
			case 0x500F6C3D: return alpha | 0x9C9C9CAA;
			case 0x2BAACAFA: return alpha | 0x9E9E9EAA;
			case 0xA17D9FB9: return alpha | 0x9E9E9EAA;
			case 0x9D0997FA: return alpha | 0x9E9E9EAA;
			case 0x2BAADBFE: return alpha | 0x9E9E9EAA;
			case 0xA17DB0BD: return alpha | 0x9E9E9EAA;
			case 0x9D09A8FE: return alpha | 0x9E9E9EAA;
			case 0x2DFFF39B: return alpha | 0xA1A1A1AA;
			case 0xEE77DC7A: return alpha | 0xA1A1A1AA;
			case 0xEA03D4BB: return alpha | 0xA1A1A1AA;
			case 0x2E00049F: return alpha | 0xA1A1A1AA;
			case 0xEE77ED7E: return alpha | 0xA1A1A1AA;
			case 0xEA03E5BF: return alpha | 0xA1A1A1AA;
			case 0x30551C3C: return alpha | 0xA3A3A3AA;
			case 0x3B72193B: return alpha | 0xA3A3A3AA;
			case 0x36FE117C: return alpha | 0xA3A3A3AA;
			case 0x30552D40: return alpha | 0xA3A3A3AA;
			case 0x3B722A3F: return alpha | 0xA3A3A3AA;
			case 0x36FE2280: return alpha | 0xA3A3A3AA;
			case 0x32AA44DD: return alpha | 0xA6A6A6AA;
			case 0x886C55FC: return alpha | 0xA6A6A6AA;
			case 0x83F84E3D: return alpha | 0xA6A6A6AA;
			case 0x32AA55E1: return alpha | 0xA6A6A6AA;
			case 0x886C6700: return alpha | 0xA6A6A6AA;
			case 0x83F85F41: return alpha | 0xA6A6A6AA;
			case 0x34FF6D7E: return alpha | 0xA8A8A8AA;
			case 0xD56692BD: return alpha | 0xA8A8A8AA;
			case 0xD0F28AFE: return alpha | 0xA8A8A8AA;
			case 0x34FF7E82: return alpha | 0xA8A8A8AA;
			case 0xD566A3C1: return alpha | 0xA8A8A8AA;
			case 0xD0F29C02: return alpha | 0xA8A8A8AA;
			case 0x3754961F: return alpha | 0xABABABAA;
			case 0x2260CF7E: return alpha | 0xABABABAA;
			case 0x1DECC7BF: return alpha | 0xABABABAA;
			case 0x3754A723: return alpha | 0xABABABAA;
			case 0x2260E082: return alpha | 0xABABABAA;
			case 0x1DECD8C3: return alpha | 0xABABABAA;
			case 0x39A9BEC0: return alpha | 0xADADADAA;
			case 0x6F5B0C3F: return alpha | 0xADADADAA;
			case 0x6AE70480: return alpha | 0xADADADAA;
			case 0x39A9CFC4: return alpha | 0xADADADAA;
			case 0x6F5B1D43: return alpha | 0xADADADAA;
			case 0x6AE71584: return alpha | 0xADADADAA;
			case 0x3BFEE761: return alpha | 0xB0B0B0AA;
			case 0xBC554900: return alpha | 0xB0B0B0AA;
			case 0xB7E14141: return alpha | 0xB0B0B0AA;
			case 0x3BFEF865: return alpha | 0xB0B0B0AA;
			case 0xBC555A04: return alpha | 0xB0B0B0AA;
			case 0xB7E15245: return alpha | 0xB0B0B0AA;
			case 0x27129239: return alpha | 0xB3B3B3AA;
			case 0x09DE4ED8: return alpha | 0xB3B3B3AA;
			case 0x056A4719: return alpha | 0xB3B3B3AA;
			case 0x2712A33D: return alpha | 0xB3B3B3AA;
			case 0x09DE5FDC: return alpha | 0xB3B3B3AA;
			case 0x056A581D: return alpha | 0xB3B3B3AA;
			case 0x2967BADA: return alpha | 0xB5B5B5AA;
			case 0x56D88B99: return alpha | 0xB5B5B5AA;
			case 0x526483DA: return alpha | 0xB5B5B5AA;
			case 0x2967CBDE: return alpha | 0xB5B5B5AA;
			case 0x56D89C9D: return alpha | 0xB5B5B5AA;
			case 0x526494DE: return alpha | 0xB5B5B5AA;
			case 0x2BBCE37B: return alpha | 0xB8B8B8AA;
			case 0xA3D2C85A: return alpha | 0xB8B8B8AA;
			case 0x9F5EC09B: return alpha | 0xB8B8B8AA;
			case 0x2BBCF47F: return alpha | 0xB8B8B8AA;
			case 0xA3D2D95E: return alpha | 0xB8B8B8AA;
			case 0x9F5ED19F: return alpha | 0xB8B8B8AA;
			case 0x2E120C1C: return alpha | 0xBABABAAA;
			case 0xF0CD051B: return alpha | 0xBABABAAA;
			case 0xEC58FD5C: return alpha | 0xBABABAAA;
			case 0x2E121D20: return alpha | 0xBABABAAA;
			case 0xF0CD161F: return alpha | 0xBABABAAA;
			case 0xEC590E60: return alpha | 0xBABABAAA;
			case 0x306734BD: return alpha | 0xBDBDBDAA;
			case 0x3DC741DC: return alpha | 0xBDBDBDAA;
			case 0x39533A1D: return alpha | 0xBDBDBDAA;
			case 0x306745C1: return alpha | 0xBDBDBDAA;
			case 0x3DC752E0: return alpha | 0xBDBDBDAA;
			case 0x39534B21: return alpha | 0xBDBDBDAA;
			case 0x32BC5D5E: return alpha | 0xBFBFBFAA;
			case 0x8AC17E9D: return alpha | 0xBFBFBFAA;
			case 0x864D76DE: return alpha | 0xBFBFBFAA;
			case 0x32BC6E62: return alpha | 0xBFBFBFAA;
			case 0x8AC18FA1: return alpha | 0xBFBFBFAA;
			case 0x864D87E2: return alpha | 0xBFBFBFAA;
			case 0x351185FF: return alpha | 0xC2C2C2AA;
			case 0xD7BBBB5E: return alpha | 0xC2C2C2AA;
			case 0xD347B39F: return alpha | 0xC2C2C2AA;
			case 0x35119703: return alpha | 0xC2C2C2AA;
			case 0xD7BBCC62: return alpha | 0xC2C2C2AA;
			case 0xD347C4A3: return alpha | 0xC2C2C2AA;
			case 0x3766AEA0: return alpha | 0xC4C4C4AA;
			case 0x24B5F81F: return alpha | 0xC4C4C4AA;
			case 0x2041F060: return alpha | 0xC4C4C4AA;
			case 0x3766BFA4: return alpha | 0xC4C4C4AA;
			case 0x24B60923: return alpha | 0xC4C4C4AA;
			case 0x20420164: return alpha | 0xC4C4C4AA;
			case 0x39BBD741: return alpha | 0xC7C7C7AA;
			case 0x71B034E0: return alpha | 0xC7C7C7AA;
			case 0x6D3C2D21: return alpha | 0xC7C7C7AA;
			case 0x39BBE845: return alpha | 0xC7C7C7AA;
			case 0x71B045E4: return alpha | 0xC7C7C7AA;
			case 0x6D3C3E25: return alpha | 0xC7C7C7AA;
			case 0x3C10FFE2: return alpha | 0xC9C9C9AA;
			case 0xBEAA71A1: return alpha | 0xC9C9C9AA;
			case 0xBA3669E2: return alpha | 0xC9C9C9AA;
			case 0x3C1110E6: return alpha | 0xC9C9C9AA;
			case 0xBEAA82A5: return alpha | 0xC9C9C9AA;
			case 0xBA367AE6: return alpha | 0xC9C9C9AA;
			case 0x2724AABA: return alpha | 0xCCCCCCAA;
			case 0x0C337779: return alpha | 0xCCCCCCAA;
			case 0x07BF6FBA: return alpha | 0xCCCCCCAA;
			case 0x2724BBBE: return alpha | 0xCCCCCCAA;
			case 0x0C33887D: return alpha | 0xCCCCCCAA;
			case 0x07BF80BE: return alpha | 0xCCCCCCAA;
			case 0x2979D35B: return alpha | 0xCFCFCFAA;
			case 0x592DB43A: return alpha | 0xCFCFCFAA;
			case 0x54B9AC7B: return alpha | 0xCFCFCFAA;
			case 0x2979E45F: return alpha | 0xCFCFCFAA;
			case 0x592DC53E: return alpha | 0xCFCFCFAA;
			case 0x54B9BD7F: return alpha | 0xCFCFCFAA;
			case 0x2BCEFBFC: return alpha | 0xD1D1D1AA;
			case 0xA627F0FB: return alpha | 0xD1D1D1AA;
			case 0xA1B3E93C: return alpha | 0xD1D1D1AA;
			case 0x2BCF0D00: return alpha | 0xD1D1D1AA;
			case 0xA62801FF: return alpha | 0xD1D1D1AA;
			case 0xA1B3FA40: return alpha | 0xD1D1D1AA;
			case 0x2E24249D: return alpha | 0xD4D4D4AA;
			case 0xF3222DBC: return alpha | 0xD4D4D4AA;
			case 0xEEAE25FD: return alpha | 0xD4D4D4AA;
			case 0x2E2435A1: return alpha | 0xD4D4D4AA;
			case 0xF3223EC0: return alpha | 0xD4D4D4AA;
			case 0xEEAE3701: return alpha | 0xD4D4D4AA;
			case 0x30794D3E: return alpha | 0xD6D6D6AA;
			case 0x401C6A7D: return alpha | 0xD6D6D6AA;
			case 0x3BA862BE: return alpha | 0xD6D6D6AA;
			case 0x30795E42: return alpha | 0xD6D6D6AA;
			case 0x401C7B81: return alpha | 0xD6D6D6AA;
			case 0x3BA873C2: return alpha | 0xD6D6D6AA;
			case 0x32CE75DF: return alpha | 0xD9D9D9AA;
			case 0x8D16A73E: return alpha | 0xD9D9D9AA;
			case 0x88A29F7F: return alpha | 0xD9D9D9AA;
			case 0x32CE86E3: return alpha | 0xD9D9D9AA;
			case 0x8D16B842: return alpha | 0xD9D9D9AA;
			case 0x88A2B083: return alpha | 0xD9D9D9AA;
			case 0x35239E80: return alpha | 0xDBDBDBAA;
			case 0xDA10E3FF: return alpha | 0xDBDBDBAA;
			case 0xD59CDC40: return alpha | 0xDBDBDBAA;
			case 0x3523AF84: return alpha | 0xDBDBDBAA;
			case 0xDA10F503: return alpha | 0xDBDBDBAA;
			case 0xD59CED44: return alpha | 0xDBDBDBAA;
			case 0x3778C721: return alpha | 0xDEDEDEAA;
			case 0x270B20C0: return alpha | 0xDEDEDEAA;
			case 0x22971901: return alpha | 0xDEDEDEAA;
			case 0x3778D825: return alpha | 0xDEDEDEAA;
			case 0x270B31C4: return alpha | 0xDEDEDEAA;
			case 0x22972A05: return alpha | 0xDEDEDEAA;
			case 0x39CDEFC2: return alpha | 0xE0E0E0AA;
			case 0x74055D81: return alpha | 0xE0E0E0AA;
			case 0x6F9155C2: return alpha | 0xE0E0E0AA;
			case 0x39CE00C6: return alpha | 0xE0E0E0AA;
			case 0x74056E85: return alpha | 0xE0E0E0AA;
			case 0x6F9166C6: return alpha | 0xE0E0E0AA;
			case 0x3C231863: return alpha | 0xE3E3E3AA;
			case 0xC0FF9A42: return alpha | 0xE3E3E3AA;
			case 0xBC8B9283: return alpha | 0xE3E3E3AA;
			case 0x3C232967: return alpha | 0xE3E3E3AA;
			case 0xC0FFAB46: return alpha | 0xE3E3E3AA;
			case 0xBC8BA387: return alpha | 0xE3E3E3AA;
			case 0x2736C33B: return alpha | 0xE5E5E5AA;
			case 0x0E88A01A: return alpha | 0xE5E5E5AA;
			case 0x0A14985B: return alpha | 0xE5E5E5AA;
			case 0x2736D43F: return alpha | 0xE5E5E5AA;
			case 0x0E88B11E: return alpha | 0xE5E5E5AA;
			case 0x0A14A95F: return alpha | 0xE5E5E5AA;
			case 0x298BEBDC: return alpha | 0xE8E8E8AA;
			case 0x5B82DCDB: return alpha | 0xE8E8E8AA;
			case 0x570ED51C: return alpha | 0xE8E8E8AA;
			case 0x298BFCE0: return alpha | 0xE8E8E8AA;
			case 0x5B82EDDF: return alpha | 0xE8E8E8AA;
			case 0x570EE620: return alpha | 0xE8E8E8AA;
			case 0x2BE1147D: return alpha | 0xEBEBEBAA;
			case 0xA87D199C: return alpha | 0xEBEBEBAA;
			case 0xA40911DD: return alpha | 0xEBEBEBAA;
			case 0x2BE12581: return alpha | 0xEBEBEBAA;
			case 0xA87D2AA0: return alpha | 0xEBEBEBAA;
			case 0xA40922E1: return alpha | 0xEBEBEBAA;
			case 0x2E363D1E: return alpha | 0xEDEDEDAA;
			case 0xF577565D: return alpha | 0xEDEDEDAA;
			case 0xF1034E9E: return alpha | 0xEDEDEDAA;
			case 0x2E364E22: return alpha | 0xEDEDEDAA;
			case 0xF5776761: return alpha | 0xEDEDEDAA;
			case 0xF1035FA2: return alpha | 0xEDEDEDAA;
			case 0x308B65BF: return alpha | 0xF0F0F0AA;
			case 0x4271931E: return alpha | 0xF0F0F0AA;
			case 0x3DFD8B5F: return alpha | 0xF0F0F0AA;
			case 0x308B76C3: return alpha | 0xF0F0F0AA;
			case 0x4271A422: return alpha | 0xF0F0F0AA;
			case 0x3DFD9C63: return alpha | 0xF0F0F0AA;
			case 0x32E08E60: return alpha | 0xF2F2F2AA;
			case 0x8F6BCFDF: return alpha | 0xF2F2F2AA;
			case 0x8AF7C820: return alpha | 0xF2F2F2AA;
			case 0x32E09F64: return alpha | 0xF2F2F2AA;
			case 0x8F6BE0E3: return alpha | 0xF2F2F2AA;
			case 0x8AF7D924: return alpha | 0xF2F2F2AA;
			case 0x3535B701: return alpha | 0xF5F5F5AA;
			case 0xDC660CA0: return alpha | 0xF5F5F5AA;
			case 0xD7F204E1: return alpha | 0xF5F5F5AA;
			case 0x3535C805: return alpha | 0xF5F5F5AA;
			case 0xDC661DA4: return alpha | 0xF5F5F5AA;
			case 0xD7F215E5: return alpha | 0xF5F5F5AA;
			case 0x378ADFA2: return alpha | 0xF7F7F7AA;
			case 0x29604961: return alpha | 0xF7F7F7AA;
			case 0x24EC41A2: return alpha | 0xF7F7F7AA;
			case 0x378AF0A6: return alpha | 0xF7F7F7AA;
			case 0x29605A65: return alpha | 0xF7F7F7AA;
			case 0x24EC52A6: return alpha | 0xF7F7F7AA;
			case 0x39E00843: return alpha | 0xFAFAFAAA;
			case 0x765A8622: return alpha | 0xFAFAFAAA;
			case 0x71E67E63: return alpha | 0xFAFAFAAA;
			case 0x39E01947: return alpha | 0xFAFAFAAA;
			case 0x765A9726: return alpha | 0xFAFAFAAA;
			case 0x71E68F67: return alpha | 0xFAFAFAAA;
			case 0x3C3530E4: return alpha | 0xFCFCFCAA;
			case 0xC354C2E3: return alpha | 0xFCFCFCAA;
			case 0xBEE0BB24: return alpha | 0xFCFCFCAA;
			case 0x3C3541E8: return alpha | 0xFCFCFCAA;
			case 0xC354D3E7: return alpha | 0xFCFCFCAA;
			case 0xBEE0CC28: return alpha | 0xFCFCFCAA;
			case 0xF649CB43: return alpha | 0xFFFFFFAA;
			case 0xBFFCA922: return alpha | 0xFFFFFFAA;
			case 0xBB88A163: return alpha | 0xFFFFFFAA;
			case 0xF649DC47: return alpha | 0xFFFFFFAA;
			case 0xBFFCBA26: return alpha | 0xFFFFFFAA;
			case 0xBB88B267: return alpha | 0xFFFFFFAA;
			case 0x324F4678: return alpha | 0xA9A9A9AA;
			case 0x7D9E7117: return alpha | 0xA9A9A9AA;
			case 0x792A6958: return alpha | 0xA9A9A9AA;
			case 0xFE665374: return alpha | 0xA9A9A9AA;
			case 0xCC971D93: return alpha | 0xA9A9A9AA;
			case 0xC82315D4: return alpha | 0xA9A9A9AA;
			case 0x7E7502A9: return alpha | 0x00008BAA;
			case 0x4E7BB368: return alpha | 0x00008BAA;
			case 0x4A07ABA9: return alpha | 0x00008BAA;
			case 0xE79DE82C: return alpha | 0x008B8BAA;
			case 0xDCC1494B: return alpha | 0x008B8BAA;
			case 0xD84D418C: return alpha | 0x008B8BAA;
			case 0x215924FE: return alpha | 0x8B008BAA;
			case 0x4DE4205D: return alpha | 0x8B008BAA;
			case 0x4970189E: return alpha | 0x8B008BAA;
			case 0x2D20A0FC: return alpha | 0x8B0000AA;
			case 0xD29B1C1B: return alpha | 0x8B0000AA;
			case 0xCE27145C: return alpha | 0x8B0000AA;
			case 0x1D02D088: return alpha | 0x90EE90AA;
			case 0xD7DF4A47: return alpha | 0x90EE90AA;
			case 0x44EA4AA8: return alpha | 0x90EE90AA;
			
			/*case _I(S,N,O,W):
				return alpha | X11_SNOW;
			case _I(G,H,O,S,T,W,H,I,T,E):
				return alpha | X11_GHOST_WHITE;
			case _I(G,H,O,S,T,_,W,H,I,T,E):
				return alpha | X11_GHOST_WHITE;
			case _I(G,H,O,S,T, ,W,H,I,T,E):
				return alpha | X11_GHOST_WHITE;
			case _I(W,H,I,T,E,S,M,O,K,E):
				return alpha | X11_WHITE_SMOKE;
			case _I(W,H,I,T,E,_,S,M,O,K,E):
				return alpha | X11_WHITE_SMOKE;
			case _I(W,H,I,T,E, ,S,M,O,K,E):
				return alpha | X11_WHITE_SMOKE;
			case _I(G,A,I,N,S,B,O,R,O):
				return alpha | X11_GAINSBORO;
			case _I(F,L,O,R,A,L,W,H,I,T,E):
				return alpha | X11_FLORAL_WHITE;
			case _I(F,L,O,R,A,L,_,W,H,I,T,E):
				return alpha | X11_FLORAL_WHITE;
			case _I(F,L,O,R,A,L, ,W,H,I,T,E):
				return alpha | X11_FLORAL_WHITE;
			case _I(O,L,D,L,A,C,E):
				return alpha | X11_OLD_LACE;
			case _I(O,L,D,_,L,A,C,E):
				return alpha | X11_OLD_LACE;
			case _I(O,L,D, ,L,A,C,E):
				return alpha | X11_OLD_LACE;
			case _I(L,I,N,E,N):
				return alpha | X11_LINEN;
			case _I(A,N,T,I,Q,U,E,W,H,I,T,E):
				return alpha | X11_ANTIQUE_WHITE;
			case _I(A,N,T,I,Q,U,E,_,W,H,I,T,E):
				return alpha | X11_ANTIQUE_WHITE;
			case _I(A,N,T,I,Q,U,E, ,W,H,I,T,E):
				return alpha | X11_ANTIQUE_WHITE;
			case _I(P,A,P,A,Y,A,W,H,I,P):
				return alpha | X11_PAPAYA_WHIP;
			case _I(P,A,P,A,Y,A,_,W,H,I,P):
				return alpha | X11_PAPAYA_WHIP;
			case _I(P,A,P,A,Y,A, ,W,H,I,P):
				return alpha | X11_PAPAYA_WHIP;
			case _I(B,L,A,N,C,H,E,D,A,L,M,O,N,D):
				return alpha | X11_BLANCHED_ALMOND;
			case _I(B,L,A,N,C,H,E,D,_,A,L,M,O,N,D):
				return alpha | X11_BLANCHED_ALMOND;
			case _I(B,L,A,N,C,H,E,D, ,A,L,M,O,N,D):
				return alpha | X11_BLANCHED_ALMOND;
			case _I(B,I,S,Q,U,E):
				return alpha | X11_BISQUE;
			case _I(P,E,A,C,H,P,U,F,F):
				return alpha | X11_PEACH_PUFF;
			case _I(P,E,A,C,H,_,P,U,F,F):
				return alpha | X11_PEACH_PUFF;
			case _I(P,E,A,C,H, ,P,U,F,F):
				return alpha | X11_PEACH_PUFF;
			case _I(N,A,V,A,J,O,W,H,I,T,E):
				return alpha | X11_NAVAJO_WHITE;
			case _I(N,A,V,A,J,O,_,W,H,I,T,E):
				return alpha | X11_NAVAJO_WHITE;
			case _I(N,A,V,A,J,O, ,W,H,I,T,E):
				return alpha | X11_NAVAJO_WHITE;
			case _I(M,O,C,C,A,S,I,N):
				return alpha | X11_MOCCASIN;
			case _I(C,O,R,N,S,I,L,K):
				return alpha | X11_CORNSILK;
			case _I(I,V,O,R,Y):
				return alpha | X11_IVORY;
			case _I(L,E,M,O,N,C,H,I,F,F,O,N):
				return alpha | X11_LEMON_CHIFFON;
			case _I(L,E,M,O,N,_,C,H,I,F,F,O,N):
				return alpha | X11_LEMON_CHIFFON;
			case _I(L,E,M,O,N, ,C,H,I,F,F,O,N):
				return alpha | X11_LEMON_CHIFFON;
			case _I(S,E,A,S,H,E,L,L):
				return alpha | X11_SEASHELL;
			case _I(H,O,N,E,Y,D,E,W):
				return alpha | X11_HONEYDEW;
			case _I(M,I,N,T,C,R,E,A,M):
				return alpha | X11_MINT_CREAM;
			case _I(M,I,N,T,_,C,R,E,A,M):
				return alpha | X11_MINT_CREAM;
			case _I(M,I,N,T, ,C,R,E,A,M):
				return alpha | X11_MINT_CREAM;
			case _I(A,Z,U,R,E):
				return alpha | X11_AZURE;
			case _I(A,L,I,C,E,B,L,U,E):
				return alpha | X11_ALICE_BLUE;
			case _I(A,L,I,C,E,_,B,L,U,E):
				return alpha | X11_ALICE_BLUE;
			case _I(A,L,I,C,E, ,B,L,U,E):
				return alpha | X11_ALICE_BLUE;
			case _I(L,A,V,E,N,D,E,R):
				return alpha | X11_LAVENDER;
			case _I(L,A,V,E,N,D,E,R,B,L,U,S,H):
				return alpha | X11_LAVENDER_BLUSH;
			case _I(L,A,V,E,N,D,E,R,_,B,L,U,S,H):
				return alpha | X11_LAVENDER_BLUSH;
			case _I(L,A,V,E,N,D,E,R, ,B,L,U,S,H):
				return alpha | X11_LAVENDER_BLUSH;
			case _I(M,I,S,T,Y,R,O,S,E):
				return alpha | X11_MISTY_ROSE;
			case _I(M,I,S,T,Y,_,R,O,S,E):
				return alpha | X11_MISTY_ROSE;
			case _I(M,I,S,T,Y, ,R,O,S,E):
				return alpha | X11_MISTY_ROSE;
			case _I(W,H,I,T,E):
				return alpha | X11_WHITE;
			case _I(B,L,A,C,K):
				return alpha | X11_BLACK;
			case _I(D,A,R,K,S,L,A,T,E,G,R,A,Y):
				return alpha | X11_DARK_SLATE_GRAY;
			case _I(D,A,R,K,_,S,L,A,T,E,_,G,R,A,Y):
				return alpha | X11_DARK_SLATE_GRAY;
			case _I(D,A,R,K, ,S,L,A,T,E, ,G,R,A,Y):
				return alpha | X11_DARK_SLATE_GRAY;
			case _I(D,A,R,K,S,L,A,T,E,G,R,E,Y):
				return alpha | X11_DARK_SLATE_GREY;
			case _I(D,A,R,K,_,S,L,A,T,E,_,G,R,E,Y):
				return alpha | X11_DARK_SLATE_GREY;
			case _I(D,A,R,K, ,S,L,A,T,E, ,G,R,E,Y):
				return alpha | X11_DARK_SLATE_GREY;
			case _I(D,I,M,G,R,A,Y):
				return alpha | X11_DIM_GRAY;
			case _I(D,I,M,_,G,R,A,Y):
				return alpha | X11_DIM_GRAY;
			case _I(D,I,M, ,G,R,A,Y):
				return alpha | X11_DIM_GRAY;
			case _I(D,I,M,G,R,E,Y):
				return alpha | X11_DIM_GREY;
			case _I(D,I,M,_,G,R,E,Y):
				return alpha | X11_DIM_GREY;
			case _I(D,I,M, ,G,R,E,Y):
				return alpha | X11_DIM_GREY;
			case _I(S,L,A,T,E,G,R,A,Y):
				return alpha | X11_SLATE_GRAY;
			case _I(S,L,A,T,E,_,G,R,A,Y):
				return alpha | X11_SLATE_GRAY;
			case _I(S,L,A,T,E, ,G,R,A,Y):
				return alpha | X11_SLATE_GRAY;
			case _I(S,L,A,T,E,G,R,E,Y):
				return alpha | X11_SLATE_GREY;
			case _I(S,L,A,T,E,_,G,R,E,Y):
				return alpha | X11_SLATE_GREY;
			case _I(S,L,A,T,E, ,G,R,E,Y):
				return alpha | X11_SLATE_GREY;
			case _I(L,I,G,H,T,S,L,A,T,E,G,R,A,Y):
				return alpha | X11_LIGHT_SLATE_GRAY;
			case _I(L,I,G,H,T,_,S,L,A,T,E,_,G,R,A,Y):
				return alpha | X11_LIGHT_SLATE_GRAY;
			case _I(L,I,G,H,T, ,S,L,A,T,E, ,G,R,A,Y):
				return alpha | X11_LIGHT_SLATE_GRAY;
			case _I(L,I,G,H,T,S,L,A,T,E,G,R,E,Y):
				return alpha | X11_LIGHT_SLATE_GREY;
			case _I(L,I,G,H,T,_,S,L,A,T,E,_,G,R,E,Y):
				return alpha | X11_LIGHT_SLATE_GREY;
			case _I(L,I,G,H,T, ,S,L,A,T,E, ,G,R,E,Y):
				return alpha | X11_LIGHT_SLATE_GREY;
			case _I(G,R,A,Y):
				return alpha | X11_GRAY;
			case _I(G,R,E,Y):
				return alpha | X11_GREY;
			case _I(L,I,G,H,T,G,R,E,Y):
				return alpha | X11_LIGHT_GREY;
			case _I(L,I,G,H,T,_,G,R,E,Y):
				return alpha | X11_LIGHT_GREY;
			case _I(L,I,G,H,T, ,G,R,E,Y):
				return alpha | X11_LIGHT_GREY;
			case _I(L,I,G,H,T,G,R,A,Y):
				return alpha | X11_LIGHT_GRAY;
			case _I(L,I,G,H,T,_,G,R,A,Y):
				return alpha | X11_LIGHT_GRAY;
			case _I(L,I,G,H,T, ,G,R,A,Y):
				return alpha | X11_LIGHT_GRAY;
			case _I(M,I,D,N,I,G,H,T,B,L,U,E):
				return alpha | X11_MIDNIGHT_BLUE;
			case _I(M,I,D,N,I,G,H,T,_,B,L,U,E):
				return alpha | X11_MIDNIGHT_BLUE;
			case _I(M,I,D,N,I,G,H,T, ,B,L,U,E):
				return alpha | X11_MIDNIGHT_BLUE;
			case _I(N,A,V,Y):
				return alpha | X11_NAVY;
			case _I(N,A,V,Y,B,L,U,E):
				return alpha | X11_NAVY_BLUE;
			case _I(N,A,V,Y,_,B,L,U,E):
				return alpha | X11_NAVY_BLUE;
			case _I(N,A,V,Y, ,B,L,U,E):
				return alpha | X11_NAVY_BLUE;
			case _I(C,O,R,N,F,L,O,W,E,R,B,L,U,E):
				return alpha | X11_CORNFLOWER_BLUE;
			case _I(C,O,R,N,F,L,O,W,E,R,_,B,L,U,E):
				return alpha | X11_CORNFLOWER_BLUE;
			case _I(C,O,R,N,F,L,O,W,E,R, ,B,L,U,E):
				return alpha | X11_CORNFLOWER_BLUE;
			case _I(D,A,R,K,S,L,A,T,E,B,L,U,E):
				return alpha | X11_DARK_SLATE_BLUE;
			case _I(D,A,R,K,_,S,L,A,T,E,_,B,L,U,E):
				return alpha | X11_DARK_SLATE_BLUE;
			case _I(D,A,R,K, ,S,L,A,T,E, ,B,L,U,E):
				return alpha | X11_DARK_SLATE_BLUE;
			case _I(S,L,A,T,E,B,L,U,E):
				return alpha | X11_SLATE_BLUE;
			case _I(S,L,A,T,E,_,B,L,U,E):
				return alpha | X11_SLATE_BLUE;
			case _I(S,L,A,T,E, ,B,L,U,E):
				return alpha | X11_SLATE_BLUE;
			case _I(M,E,D,I,U,M,S,L,A,T,E,B,L,U,E):
				return alpha | X11_MEDIUM_SLATE_BLUE;
			case _I(M,E,D,I,U,M,_,S,L,A,T,E,_,B,L,U,E):
				return alpha | X11_MEDIUM_SLATE_BLUE;
			case _I(M,E,D,I,U,M, ,S,L,A,T,E, ,B,L,U,E):
				return alpha | X11_MEDIUM_SLATE_BLUE;
			case _I(L,I,G,H,T,S,L,A,T,E,B,L,U,E):
				return alpha | X11_LIGHT_SLATE_BLUE;
			case _I(L,I,G,H,T,_,S,L,A,T,E,_,B,L,U,E):
				return alpha | X11_LIGHT_SLATE_BLUE;
			case _I(L,I,G,H,T, ,S,L,A,T,E, ,B,L,U,E):
				return alpha | X11_LIGHT_SLATE_BLUE;
			case _I(M,E,D,I,U,M,B,L,U,E):
				return alpha | X11_MEDIUM_BLUE;
			case _I(M,E,D,I,U,M,_,B,L,U,E):
				return alpha | X11_MEDIUM_BLUE;
			case _I(M,E,D,I,U,M, ,B,L,U,E):
				return alpha | X11_MEDIUM_BLUE;
			case _I(R,O,Y,A,L,B,L,U,E):
				return alpha | X11_ROYAL_BLUE;
			case _I(R,O,Y,A,L,_,B,L,U,E):
				return alpha | X11_ROYAL_BLUE;
			case _I(R,O,Y,A,L, ,B,L,U,E):
				return alpha | X11_ROYAL_BLUE;
			case _I(B,L,U,E):
				return alpha | X11_BLUE;
			case _I(D,O,D,G,E,R,B,L,U,E):
				return alpha | X11_DODGER_BLUE;
			case _I(D,O,D,G,E,R,_,B,L,U,E):
				return alpha | X11_DODGER_BLUE;
			case _I(D,O,D,G,E,R, ,B,L,U,E):
				return alpha | X11_DODGER_BLUE;
			case _I(D,E,E,P,S,K,Y,B,L,U,E):
				return alpha | X11_DEEP_SKY_BLUE;
			case _I(D,E,E,P,_,S,K,Y,_,B,L,U,E):
				return alpha | X11_DEEP_SKY_BLUE;
			case _I(D,E,E,P, ,S,K,Y, ,B,L,U,E):
				return alpha | X11_DEEP_SKY_BLUE;
			case _I(S,K,Y,B,L,U,E):
				return alpha | X11_SKY_BLUE;
			case _I(S,K,Y,_,B,L,U,E):
				return alpha | X11_SKY_BLUE;
			case _I(S,K,Y, ,B,L,U,E):
				return alpha | X11_SKY_BLUE;
			case _I(L,I,G,H,T,S,K,Y,B,L,U,E):
				return alpha | X11_LIGHT_SKY_BLUE;
			case _I(L,I,G,H,T,_,S,K,Y,_,B,L,U,E):
				return alpha | X11_LIGHT_SKY_BLUE;
			case _I(L,I,G,H,T, ,S,K,Y, ,B,L,U,E):
				return alpha | X11_LIGHT_SKY_BLUE;
			case _I(S,T,E,E,L,B,L,U,E):
				return alpha | X11_STEEL_BLUE;
			case _I(S,T,E,E,L,_,B,L,U,E):
				return alpha | X11_STEEL_BLUE;
			case _I(S,T,E,E,L, ,B,L,U,E):
				return alpha | X11_STEEL_BLUE;
			case _I(L,I,G,H,T,S,T,E,E,L,B,L,U,E):
				return alpha | X11_LIGHT_STEEL_BLUE;
			case _I(L,I,G,H,T,_,S,T,E,E,L,_,B,L,U,E):
				return alpha | X11_LIGHT_STEEL_BLUE;
			case _I(L,I,G,H,T, ,S,T,E,E,L, ,B,L,U,E):
				return alpha | X11_LIGHT_STEEL_BLUE;
			case _I(L,I,G,H,T,B,L,U,E):
				return alpha | X11_LIGHT_BLUE;
			case _I(L,I,G,H,T,_,B,L,U,E):
				return alpha | X11_LIGHT_BLUE;
			case _I(L,I,G,H,T, ,B,L,U,E):
				return alpha | X11_LIGHT_BLUE;
			case _I(P,O,W,D,E,R,B,L,U,E):
				return alpha | X11_POWDER_BLUE;
			case _I(P,O,W,D,E,R,_,B,L,U,E):
				return alpha | X11_POWDER_BLUE;
			case _I(P,O,W,D,E,R, ,B,L,U,E):
				return alpha | X11_POWDER_BLUE;
			case _I(P,A,L,E,T,U,R,Q,U,O,I,S,E):
				return alpha | X11_PALE_TURQUOISE;
			case _I(P,A,L,E,_,T,U,R,Q,U,O,I,S,E):
				return alpha | X11_PALE_TURQUOISE;
			case _I(P,A,L,E, ,T,U,R,Q,U,O,I,S,E):
				return alpha | X11_PALE_TURQUOISE;
			case _I(D,A,R,K,T,U,R,Q,U,O,I,S,E):
				return alpha | X11_DARK_TURQUOISE;
			case _I(D,A,R,K,_,T,U,R,Q,U,O,I,S,E):
				return alpha | X11_DARK_TURQUOISE;
			case _I(D,A,R,K, ,T,U,R,Q,U,O,I,S,E):
				return alpha | X11_DARK_TURQUOISE;
			case _I(M,E,D,I,U,M,T,U,R,Q,U,O,I,S,E):
				return alpha | X11_MEDIUM_TURQUOISE;
			case _I(M,E,D,I,U,M,_,T,U,R,Q,U,O,I,S,E):
				return alpha | X11_MEDIUM_TURQUOISE;
			case _I(M,E,D,I,U,M, ,T,U,R,Q,U,O,I,S,E):
				return alpha | X11_MEDIUM_TURQUOISE;
			case _I(T,U,R,Q,U,O,I,S,E):
				return alpha | X11_TURQUOISE;
			case _I(C,Y,A,N):
				return alpha | X11_CYAN;
			case _I(L,I,G,H,T,C,Y,A,N):
				return alpha | X11_LIGHT_CYAN;
			case _I(L,I,G,H,T,_,C,Y,A,N):
				return alpha | X11_LIGHT_CYAN;
			case _I(L,I,G,H,T, ,C,Y,A,N):
				return alpha | X11_LIGHT_CYAN;
			case _I(C,A,D,E,T,B,L,U,E):
				return alpha | X11_CADET_BLUE;
			case _I(C,A,D,E,T,_,B,L,U,E):
				return alpha | X11_CADET_BLUE;
			case _I(C,A,D,E,T, ,B,L,U,E):
				return alpha | X11_CADET_BLUE;
			case _I(M,E,D,I,U,M,A,Q,U,A,M,A,R,I,N,E):
				return alpha | X11_MEDIUM_AQUAMARINE;
			case _I(M,E,D,I,U,M,_,A,Q,U,A,M,A,R,I,N,E):
				return alpha | X11_MEDIUM_AQUAMARINE;
			case _I(M,E,D,I,U,M, ,A,Q,U,A,M,A,R,I,N,E):
				return alpha | X11_MEDIUM_AQUAMARINE;
			case _I(A,Q,U,A,M,A,R,I,N,E):
				return alpha | X11_AQUAMARINE;
			case _I(D,A,R,K,G,R,E,E,N):
				return alpha | X11_DARK_GREEN;
			case _I(D,A,R,K,_,G,R,E,E,N):
				return alpha | X11_DARK_GREEN;
			case _I(D,A,R,K, ,G,R,E,E,N):
				return alpha | X11_DARK_GREEN;
			case _I(D,A,R,K,O,L,I,V,E,G,R,E,E,N):
				return alpha | X11_DARK_OLIVE_GREEN;
			case _I(D,A,R,K,_,O,L,I,V,E,_,G,R,E,E,N):
				return alpha | X11_DARK_OLIVE_GREEN;
			case _I(D,A,R,K, ,O,L,I,V,E, ,G,R,E,E,N):
				return alpha | X11_DARK_OLIVE_GREEN;
			case _I(D,A,R,K,S,E,A,G,R,E,E,N):
				return alpha | X11_DARK_SEA_GREEN;
			case _I(D,A,R,K,_,S,E,A,_,G,R,E,E,N):
				return alpha | X11_DARK_SEA_GREEN;
			case _I(D,A,R,K, ,S,E,A, ,G,R,E,E,N):
				return alpha | X11_DARK_SEA_GREEN;
			case _I(S,E,A,G,R,E,E,N):
				return alpha | X11_SEA_GREEN;
			case _I(S,E,A,_,G,R,E,E,N):
				return alpha | X11_SEA_GREEN;
			case _I(S,E,A, ,G,R,E,E,N):
				return alpha | X11_SEA_GREEN;
			case _I(M,E,D,I,U,M,S,E,A,G,R,E,E,N):
				return alpha | X11_MEDIUM_SEA_GREEN;
			case _I(M,E,D,I,U,M,_,S,E,A,_,G,R,E,E,N):
				return alpha | X11_MEDIUM_SEA_GREEN;
			case _I(M,E,D,I,U,M, ,S,E,A, ,G,R,E,E,N):
				return alpha | X11_MEDIUM_SEA_GREEN;
			case _I(L,I,G,H,T,S,E,A,G,R,E,E,N):
				return alpha | X11_LIGHT_SEA_GREEN;
			case _I(L,I,G,H,T,_,S,E,A,_,G,R,E,E,N):
				return alpha | X11_LIGHT_SEA_GREEN;
			case _I(L,I,G,H,T, ,S,E,A, ,G,R,E,E,N):
				return alpha | X11_LIGHT_SEA_GREEN;
			case _I(P,A,L,E,G,R,E,E,N):
				return alpha | X11_PALE_GREEN;
			case _I(P,A,L,E,_,G,R,E,E,N):
				return alpha | X11_PALE_GREEN;
			case _I(P,A,L,E, ,G,R,E,E,N):
				return alpha | X11_PALE_GREEN;
			case _I(S,P,R,I,N,G,G,R,E,E,N):
				return alpha | X11_SPRING_GREEN;
			case _I(S,P,R,I,N,G,_,G,R,E,E,N):
				return alpha | X11_SPRING_GREEN;
			case _I(S,P,R,I,N,G, ,G,R,E,E,N):
				return alpha | X11_SPRING_GREEN;
			case _I(L,A,W,N,G,R,E,E,N):
				return alpha | X11_LAWN_GREEN;
			case _I(L,A,W,N,_,G,R,E,E,N):
				return alpha | X11_LAWN_GREEN;
			case _I(L,A,W,N, ,G,R,E,E,N):
				return alpha | X11_LAWN_GREEN;
			case _I(G,R,E,E,N):
				return alpha | X11_GREEN;
			case _I(C,H,A,R,T,R,E,U,S,E):
				return alpha | X11_CHARTREUSE;
			case _I(M,E,D,I,U,M,S,P,R,I,N,G,G,R,E,E,N):
				return alpha | X11_MEDIUM_SPRING_GREEN;
			case _I(M,E,D,I,U,M,_,S,P,R,I,N,G,_,G,R,E,E,N):
				return alpha | X11_MEDIUM_SPRING_GREEN;
			case _I(M,E,D,I,U,M, ,S,P,R,I,N,G, ,G,R,E,E,N):
				return alpha | X11_MEDIUM_SPRING_GREEN;
			case _I(G,R,E,E,N,Y,E,L,L,O,W):
				return alpha | X11_GREEN_YELLOW;
			case _I(G,R,E,E,N,_,Y,E,L,L,O,W):
				return alpha | X11_GREEN_YELLOW;
			case _I(G,R,E,E,N, ,Y,E,L,L,O,W):
				return alpha | X11_GREEN_YELLOW;
			case _I(L,I,M,E,G,R,E,E,N):
				return alpha | X11_LIME_GREEN;
			case _I(L,I,M,E,_,G,R,E,E,N):
				return alpha | X11_LIME_GREEN;
			case _I(L,I,M,E, ,G,R,E,E,N):
				return alpha | X11_LIME_GREEN;
			case _I(Y,E,L,L,O,W,G,R,E,E,N):
				return alpha | X11_YELLOW_GREEN;
			case _I(Y,E,L,L,O,W,_,G,R,E,E,N):
				return alpha | X11_YELLOW_GREEN;
			case _I(Y,E,L,L,O,W, ,G,R,E,E,N):
				return alpha | X11_YELLOW_GREEN;
			case _I(F,O,R,E,S,T,G,R,E,E,N):
				return alpha | X11_FOREST_GREEN;
			case _I(F,O,R,E,S,T,_,G,R,E,E,N):
				return alpha | X11_FOREST_GREEN;
			case _I(F,O,R,E,S,T, ,G,R,E,E,N):
				return alpha | X11_FOREST_GREEN;
			case _I(O,L,I,V,E,D,R,A,B):
				return alpha | X11_OLIVE_DRAB;
			case _I(O,L,I,V,E,_,D,R,A,B):
				return alpha | X11_OLIVE_DRAB;
			case _I(O,L,I,V,E, ,D,R,A,B):
				return alpha | X11_OLIVE_DRAB;
			case _I(D,A,R,K,K,H,A,K,I):
				return alpha | X11_DARK_KHAKI;
			case _I(D,A,R,K,_,K,H,A,K,I):
				return alpha | X11_DARK_KHAKI;
			case _I(D,A,R,K, ,K,H,A,K,I):
				return alpha | X11_DARK_KHAKI;
			case _I(K,H,A,K,I):
				return alpha | X11_KHAKI;
			case _I(P,A,L,E,G,O,L,D,E,N,R,O,D):
				return alpha | X11_PALE_GOLDENROD;
			case _I(P,A,L,E,_,G,O,L,D,E,N,R,O,D):
				return alpha | X11_PALE_GOLDENROD;
			case _I(P,A,L,E, ,G,O,L,D,E,N,R,O,D):
				return alpha | X11_PALE_GOLDENROD;
			case _I(L,I,G,H,T,G,O,L,D,E,N,R,O,D,Y,E,L,L,O,W):
				return alpha | X11_LIGHT_GOLDENROD_YELLOW;
			case _I(L,I,G,H,T,_,G,O,L,D,E,N,R,O,D,_,Y,E,L,L,O,W):
				return alpha | X11_LIGHT_GOLDENROD_YELLOW;
			case _I(L,I,G,H,T, ,G,O,L,D,E,N,R,O,D, ,Y,E,L,L,O,W):
				return alpha | X11_LIGHT_GOLDENROD_YELLOW;
			case _I(L,I,G,H,T,Y,E,L,L,O,W):
				return alpha | X11_LIGHT_YELLOW;
			case _I(L,I,G,H,T,_,Y,E,L,L,O,W):
				return alpha | X11_LIGHT_YELLOW;
			case _I(L,I,G,H,T, ,Y,E,L,L,O,W):
				return alpha | X11_LIGHT_YELLOW;
			case _I(Y,E,L,L,O,W):
				return alpha | X11_YELLOW;
			case _I(G,O,L,D):
				return alpha | X11_GOLD;
			case _I(L,I,G,H,T,G,O,L,D,E,N,R,O,D):
				return alpha | X11_LIGHT_GOLDENROD;
			case _I(L,I,G,H,T,_,G,O,L,D,E,N,R,O,D):
				return alpha | X11_LIGHT_GOLDENROD;
			case _I(L,I,G,H,T, ,G,O,L,D,E,N,R,O,D):
				return alpha | X11_LIGHT_GOLDENROD;
			case _I(G,O,L,D,E,N,R,O,D):
				return alpha | X11_GOLDENROD;
			case _I(D,A,R,K,G,O,L,D,E,N,R,O,D):
				return alpha | X11_DARK_GOLDENROD;
			case _I(D,A,R,K,_,G,O,L,D,E,N,R,O,D):
				return alpha | X11_DARK_GOLDENROD;
			case _I(D,A,R,K, ,G,O,L,D,E,N,R,O,D):
				return alpha | X11_DARK_GOLDENROD;
			case _I(R,O,S,Y,B,R,O,W,N):
				return alpha | X11_ROSY_BROWN;
			case _I(R,O,S,Y,_,B,R,O,W,N):
				return alpha | X11_ROSY_BROWN;
			case _I(R,O,S,Y, ,B,R,O,W,N):
				return alpha | X11_ROSY_BROWN;
			case _I(I,N,D,I,A,N,R,E,D):
				return alpha | X11_INDIAN_RED;
			case _I(I,N,D,I,A,N,_,R,E,D):
				return alpha | X11_INDIAN_RED;
			case _I(I,N,D,I,A,N, ,R,E,D):
				return alpha | X11_INDIAN_RED;
			case _I(S,A,D,D,L,E,B,R,O,W,N):
				return alpha | X11_SADDLE_BROWN;
			case _I(S,A,D,D,L,E,_,B,R,O,W,N):
				return alpha | X11_SADDLE_BROWN;
			case _I(S,A,D,D,L,E, ,B,R,O,W,N):
				return alpha | X11_SADDLE_BROWN;
			case _I(S,I,E,N,N,A):
				return alpha | X11_SIENNA;
			case _I(P,E,R,U):
				return alpha | X11_PERU;
			case _I(B,U,R,L,Y,W,O,O,D):
				return alpha | X11_BURLYWOOD;
			case _I(B,E,I,G,E):
				return alpha | X11_BEIGE;
			case _I(W,H,E,A,T):
				return alpha | X11_WHEAT;
			case _I(S,A,N,D,Y,B,R,O,W,N):
				return alpha | X11_SANDY_BROWN;
			case _I(S,A,N,D,Y,_,B,R,O,W,N):
				return alpha | X11_SANDY_BROWN;
			case _I(S,A,N,D,Y, ,B,R,O,W,N):
				return alpha | X11_SANDY_BROWN;
			case _I(T,A,N):
				return alpha | X11_TAN;
			case _I(C,H,O,C,O,L,A,T,E):
				return alpha | X11_CHOCOLATE;
			case _I(F,I,R,E,B,R,I,C,K):
				return alpha | X11_FIREBRICK;
			case _I(B,R,O,W,N):
				return alpha | X11_BROWN;
			case _I(D,A,R,K,S,A,L,M,O,N):
				return alpha | X11_DARK_SALMON;
			case _I(D,A,R,K,_,S,A,L,M,O,N):
				return alpha | X11_DARK_SALMON;
			case _I(D,A,R,K, ,S,A,L,M,O,N):
				return alpha | X11_DARK_SALMON;
			case _I(S,A,L,M,O,N):
				return alpha | X11_SALMON;
			case _I(L,I,G,H,T,S,A,L,M,O,N):
				return alpha | X11_LIGHT_SALMON;
			case _I(L,I,G,H,T,_,S,A,L,M,O,N):
				return alpha | X11_LIGHT_SALMON;
			case _I(L,I,G,H,T, ,S,A,L,M,O,N):
				return alpha | X11_LIGHT_SALMON;
			case _I(O,R,A,N,G,E):
				return alpha | X11_ORANGE;
			case _I(D,A,R,K,O,R,A,N,G,E):
				return alpha | X11_DARK_ORANGE;
			case _I(D,A,R,K,_,O,R,A,N,G,E):
				return alpha | X11_DARK_ORANGE;
			case _I(D,A,R,K, ,O,R,A,N,G,E):
				return alpha | X11_DARK_ORANGE;
			case _I(C,O,R,A,L):
				return alpha | X11_CORAL;
			case _I(L,I,G,H,T,C,O,R,A,L):
				return alpha | X11_LIGHT_CORAL;
			case _I(L,I,G,H,T,_,C,O,R,A,L):
				return alpha | X11_LIGHT_CORAL;
			case _I(L,I,G,H,T, ,C,O,R,A,L):
				return alpha | X11_LIGHT_CORAL;
			case _I(T,O,M,A,T,O):
				return alpha | X11_TOMATO;
			case _I(O,R,A,N,G,E,R,E,D):
				return alpha | X11_ORANGE_RED;
			case _I(O,R,A,N,G,E,_,R,E,D):
				return alpha | X11_ORANGE_RED;
			case _I(O,R,A,N,G,E, ,R,E,D):
				return alpha | X11_ORANGE_RED;
			case _I(R,E,D):
				return alpha | X11_RED;
			case _I(H,O,T,P,I,N,K):
				return alpha | X11_HOT_PINK;
			case _I(H,O,T,_,P,I,N,K):
				return alpha | X11_HOT_PINK;
			case _I(H,O,T, ,P,I,N,K):
				return alpha | X11_HOT_PINK;
			case _I(D,E,E,P,P,I,N,K):
				return alpha | X11_DEEP_PINK;
			case _I(D,E,E,P,_,P,I,N,K):
				return alpha | X11_DEEP_PINK;
			case _I(D,E,E,P, ,P,I,N,K):
				return alpha | X11_DEEP_PINK;
			case _I(P,I,N,K):
				return alpha | X11_PINK;
			case _I(L,I,G,H,T,P,I,N,K):
				return alpha | X11_LIGHT_PINK;
			case _I(L,I,G,H,T,_,P,I,N,K):
				return alpha | X11_LIGHT_PINK;
			case _I(L,I,G,H,T, ,P,I,N,K):
				return alpha | X11_LIGHT_PINK;
			case _I(P,A,L,E,V,I,O,L,E,T,R,E,D):
				return alpha | X11_PALE_VIOLET_RED;
			case _I(P,A,L,E,_,V,I,O,L,E,T,_,R,E,D):
				return alpha | X11_PALE_VIOLET_RED;
			case _I(P,A,L,E, ,V,I,O,L,E,T, ,R,E,D):
				return alpha | X11_PALE_VIOLET_RED;
			case _I(M,A,R,O,O,N):
				return alpha | X11_MAROON;
			case _I(M,E,D,I,U,M,V,I,O,L,E,T,R,E,D):
				return alpha | X11_MEDIUM_VIOLET_RED;
			case _I(M,E,D,I,U,M,_,V,I,O,L,E,T,_,R,E,D):
				return alpha | X11_MEDIUM_VIOLET_RED;
			case _I(M,E,D,I,U,M, ,V,I,O,L,E,T, ,R,E,D):
				return alpha | X11_MEDIUM_VIOLET_RED;
			case _I(V,I,O,L,E,T,R,E,D):
				return alpha | X11_VIOLET_RED;
			case _I(V,I,O,L,E,T,_,R,E,D):
				return alpha | X11_VIOLET_RED;
			case _I(V,I,O,L,E,T, ,R,E,D):
				return alpha | X11_VIOLET_RED;
			case _I(M,A,G,E,N,T,A):
				return alpha | X11_MAGENTA;
			case _I(V,I,O,L,E,T):
				return alpha | X11_VIOLET;
			case _I(P,L,U,M):
				return alpha | X11_PLUM;
			case _I(O,R,C,H,I,D):
				return alpha | X11_ORCHID;
			case _I(M,E,D,I,U,M,O,R,C,H,I,D):
				return alpha | X11_MEDIUM_ORCHID;
			case _I(M,E,D,I,U,M,_,O,R,C,H,I,D):
				return alpha | X11_MEDIUM_ORCHID;
			case _I(M,E,D,I,U,M, ,O,R,C,H,I,D):
				return alpha | X11_MEDIUM_ORCHID;
			case _I(D,A,R,K,O,R,C,H,I,D):
				return alpha | X11_DARK_ORCHID;
			case _I(D,A,R,K,_,O,R,C,H,I,D):
				return alpha | X11_DARK_ORCHID;
			case _I(D,A,R,K, ,O,R,C,H,I,D):
				return alpha | X11_DARK_ORCHID;
			case _I(D,A,R,K,V,I,O,L,E,T):
				return alpha | X11_DARK_VIOLET;
			case _I(D,A,R,K,_,V,I,O,L,E,T):
				return alpha | X11_DARK_VIOLET;
			case _I(D,A,R,K, ,V,I,O,L,E,T):
				return alpha | X11_DARK_VIOLET;
			case _I(B,L,U,E,V,I,O,L,E,T):
				return alpha | X11_BLUE_VIOLET;
			case _I(B,L,U,E,_,V,I,O,L,E,T):
				return alpha | X11_BLUE_VIOLET;
			case _I(B,L,U,E, ,V,I,O,L,E,T):
				return alpha | X11_BLUE_VIOLET;
			case _I(P,U,R,P,L,E):
				return alpha | X11_PURPLE;
			case _I(M,E,D,I,U,M,P,U,R,P,L,E):
				return alpha | X11_MEDIUM_PURPLE;
			case _I(M,E,D,I,U,M,_,P,U,R,P,L,E):
				return alpha | X11_MEDIUM_PURPLE;
			case _I(M,E,D,I,U,M, ,P,U,R,P,L,E):
				return alpha | X11_MEDIUM_PURPLE;
			case _I(T,H,I,S,T,L,E):
				return alpha | X11_THISTLE;
			case _I(S,N,O,W,1):
				return alpha | X11_SNOW_1;
			case _I(S,N,O,W,_,1):
				return alpha | X11_SNOW_1;
			case _I(S,N,O,W, ,1):
				return alpha | X11_SNOW_1;
			case _I(S,N,O,W,2):
				return alpha | X11_SNOW_2;
			case _I(S,N,O,W,_,2):
				return alpha | X11_SNOW_2;
			case _I(S,N,O,W, ,2):
				return alpha | X11_SNOW_2;
			case _I(S,N,O,W,3):
				return alpha | X11_SNOW_3;
			case _I(S,N,O,W,_,3):
				return alpha | X11_SNOW_3;
			case _I(S,N,O,W, ,3):
				return alpha | X11_SNOW_3;
			case _I(S,N,O,W,4):
				return alpha | X11_SNOW_4;
			case _I(S,N,O,W,_,4):
				return alpha | X11_SNOW_4;
			case _I(S,N,O,W, ,4):
				return alpha | X11_SNOW_4;
			case _I(S,E,A,S,H,E,L,L,1):
				return alpha | X11_SEASHELL_1;
			case _I(S,E,A,S,H,E,L,L,_,1):
				return alpha | X11_SEASHELL_1;
			case _I(S,E,A,S,H,E,L,L, ,1):
				return alpha | X11_SEASHELL_1;
			case _I(S,E,A,S,H,E,L,L,2):
				return alpha | X11_SEASHELL_2;
			case _I(S,E,A,S,H,E,L,L,_,2):
				return alpha | X11_SEASHELL_2;
			case _I(S,E,A,S,H,E,L,L, ,2):
				return alpha | X11_SEASHELL_2;
			case _I(S,E,A,S,H,E,L,L,3):
				return alpha | X11_SEASHELL_3;
			case _I(S,E,A,S,H,E,L,L,_,3):
				return alpha | X11_SEASHELL_3;
			case _I(S,E,A,S,H,E,L,L, ,3):
				return alpha | X11_SEASHELL_3;
			case _I(S,E,A,S,H,E,L,L,4):
				return alpha | X11_SEASHELL_4;
			case _I(S,E,A,S,H,E,L,L,_,4):
				return alpha | X11_SEASHELL_4;
			case _I(S,E,A,S,H,E,L,L, ,4):
				return alpha | X11_SEASHELL_4;
			case _I(A,N,T,I,Q,U,E,W,H,I,T,E,1):
				return alpha | X11_ANTIQUE_WHITE_1;
			case _I(A,N,T,I,Q,U,E,_,W,H,I,T,E,_,1):
				return alpha | X11_ANTIQUE_WHITE_1;
			case _I(A,N,T,I,Q,U,E, ,W,H,I,T,E, ,1):
				return alpha | X11_ANTIQUE_WHITE_1;
			case _I(A,N,T,I,Q,U,E,W,H,I,T,E,2):
				return alpha | X11_ANTIQUE_WHITE_2;
			case _I(A,N,T,I,Q,U,E,_,W,H,I,T,E,_,2):
				return alpha | X11_ANTIQUE_WHITE_2;
			case _I(A,N,T,I,Q,U,E, ,W,H,I,T,E, ,2):
				return alpha | X11_ANTIQUE_WHITE_2;
			case _I(A,N,T,I,Q,U,E,W,H,I,T,E,3):
				return alpha | X11_ANTIQUE_WHITE_3;
			case _I(A,N,T,I,Q,U,E,_,W,H,I,T,E,_,3):
				return alpha | X11_ANTIQUE_WHITE_3;
			case _I(A,N,T,I,Q,U,E, ,W,H,I,T,E, ,3):
				return alpha | X11_ANTIQUE_WHITE_3;
			case _I(A,N,T,I,Q,U,E,W,H,I,T,E,4):
				return alpha | X11_ANTIQUE_WHITE_4;
			case _I(A,N,T,I,Q,U,E,_,W,H,I,T,E,_,4):
				return alpha | X11_ANTIQUE_WHITE_4;
			case _I(A,N,T,I,Q,U,E, ,W,H,I,T,E, ,4):
				return alpha | X11_ANTIQUE_WHITE_4;
			case _I(B,I,S,Q,U,E,1):
				return alpha | X11_BISQUE_1;
			case _I(B,I,S,Q,U,E,_,1):
				return alpha | X11_BISQUE_1;
			case _I(B,I,S,Q,U,E, ,1):
				return alpha | X11_BISQUE_1;
			case _I(B,I,S,Q,U,E,2):
				return alpha | X11_BISQUE_2;
			case _I(B,I,S,Q,U,E,_,2):
				return alpha | X11_BISQUE_2;
			case _I(B,I,S,Q,U,E, ,2):
				return alpha | X11_BISQUE_2;
			case _I(B,I,S,Q,U,E,3):
				return alpha | X11_BISQUE_3;
			case _I(B,I,S,Q,U,E,_,3):
				return alpha | X11_BISQUE_3;
			case _I(B,I,S,Q,U,E, ,3):
				return alpha | X11_BISQUE_3;
			case _I(B,I,S,Q,U,E,4):
				return alpha | X11_BISQUE_4;
			case _I(B,I,S,Q,U,E,_,4):
				return alpha | X11_BISQUE_4;
			case _I(B,I,S,Q,U,E, ,4):
				return alpha | X11_BISQUE_4;
			case _I(P,E,A,C,H,P,U,F,F,1):
				return alpha | X11_PEACH_PUFF_1;
			case _I(P,E,A,C,H,_,P,U,F,F,_,1):
				return alpha | X11_PEACH_PUFF_1;
			case _I(P,E,A,C,H, ,P,U,F,F, ,1):
				return alpha | X11_PEACH_PUFF_1;
			case _I(P,E,A,C,H,P,U,F,F,2):
				return alpha | X11_PEACH_PUFF_2;
			case _I(P,E,A,C,H,_,P,U,F,F,_,2):
				return alpha | X11_PEACH_PUFF_2;
			case _I(P,E,A,C,H, ,P,U,F,F, ,2):
				return alpha | X11_PEACH_PUFF_2;
			case _I(P,E,A,C,H,P,U,F,F,3):
				return alpha | X11_PEACH_PUFF_3;
			case _I(P,E,A,C,H,_,P,U,F,F,_,3):
				return alpha | X11_PEACH_PUFF_3;
			case _I(P,E,A,C,H, ,P,U,F,F, ,3):
				return alpha | X11_PEACH_PUFF_3;
			case _I(P,E,A,C,H,P,U,F,F,4):
				return alpha | X11_PEACH_PUFF_4;
			case _I(P,E,A,C,H,_,P,U,F,F,_,4):
				return alpha | X11_PEACH_PUFF_4;
			case _I(P,E,A,C,H, ,P,U,F,F, ,4):
				return alpha | X11_PEACH_PUFF_4;
			case _I(N,A,V,A,J,O,W,H,I,T,E,1):
				return alpha | X11_NAVAJO_WHITE_1;
			case _I(N,A,V,A,J,O,_,W,H,I,T,E,_,1):
				return alpha | X11_NAVAJO_WHITE_1;
			case _I(N,A,V,A,J,O, ,W,H,I,T,E, ,1):
				return alpha | X11_NAVAJO_WHITE_1;
			case _I(N,A,V,A,J,O,W,H,I,T,E,2):
				return alpha | X11_NAVAJO_WHITE_2;
			case _I(N,A,V,A,J,O,_,W,H,I,T,E,_,2):
				return alpha | X11_NAVAJO_WHITE_2;
			case _I(N,A,V,A,J,O, ,W,H,I,T,E, ,2):
				return alpha | X11_NAVAJO_WHITE_2;
			case _I(N,A,V,A,J,O,W,H,I,T,E,3):
				return alpha | X11_NAVAJO_WHITE_3;
			case _I(N,A,V,A,J,O,_,W,H,I,T,E,_,3):
				return alpha | X11_NAVAJO_WHITE_3;
			case _I(N,A,V,A,J,O, ,W,H,I,T,E, ,3):
				return alpha | X11_NAVAJO_WHITE_3;
			case _I(N,A,V,A,J,O,W,H,I,T,E,4):
				return alpha | X11_NAVAJO_WHITE_4;
			case _I(N,A,V,A,J,O,_,W,H,I,T,E,_,4):
				return alpha | X11_NAVAJO_WHITE_4;
			case _I(N,A,V,A,J,O, ,W,H,I,T,E, ,4):
				return alpha | X11_NAVAJO_WHITE_4;
			case _I(L,E,M,O,N,C,H,I,F,F,O,N,1):
				return alpha | X11_LEMON_CHIFFON_1;
			case _I(L,E,M,O,N,_,C,H,I,F,F,O,N,_,1):
				return alpha | X11_LEMON_CHIFFON_1;
			case _I(L,E,M,O,N, ,C,H,I,F,F,O,N, ,1):
				return alpha | X11_LEMON_CHIFFON_1;
			case _I(L,E,M,O,N,C,H,I,F,F,O,N,2):
				return alpha | X11_LEMON_CHIFFON_2;
			case _I(L,E,M,O,N,_,C,H,I,F,F,O,N,_,2):
				return alpha | X11_LEMON_CHIFFON_2;
			case _I(L,E,M,O,N, ,C,H,I,F,F,O,N, ,2):
				return alpha | X11_LEMON_CHIFFON_2;
			case _I(L,E,M,O,N,C,H,I,F,F,O,N,3):
				return alpha | X11_LEMON_CHIFFON_3;
			case _I(L,E,M,O,N,_,C,H,I,F,F,O,N,_,3):
				return alpha | X11_LEMON_CHIFFON_3;
			case _I(L,E,M,O,N, ,C,H,I,F,F,O,N, ,3):
				return alpha | X11_LEMON_CHIFFON_3;
			case _I(L,E,M,O,N,C,H,I,F,F,O,N,4):
				return alpha | X11_LEMON_CHIFFON_4;
			case _I(L,E,M,O,N,_,C,H,I,F,F,O,N,_,4):
				return alpha | X11_LEMON_CHIFFON_4;
			case _I(L,E,M,O,N, ,C,H,I,F,F,O,N, ,4):
				return alpha | X11_LEMON_CHIFFON_4;
			case _I(C,O,R,N,S,I,L,K,1):
				return alpha | X11_CORNSILK_1;
			case _I(C,O,R,N,S,I,L,K,_,1):
				return alpha | X11_CORNSILK_1;
			case _I(C,O,R,N,S,I,L,K, ,1):
				return alpha | X11_CORNSILK_1;
			case _I(C,O,R,N,S,I,L,K,2):
				return alpha | X11_CORNSILK_2;
			case _I(C,O,R,N,S,I,L,K,_,2):
				return alpha | X11_CORNSILK_2;
			case _I(C,O,R,N,S,I,L,K, ,2):
				return alpha | X11_CORNSILK_2;
			case _I(C,O,R,N,S,I,L,K,3):
				return alpha | X11_CORNSILK_3;
			case _I(C,O,R,N,S,I,L,K,_,3):
				return alpha | X11_CORNSILK_3;
			case _I(C,O,R,N,S,I,L,K, ,3):
				return alpha | X11_CORNSILK_3;
			case _I(C,O,R,N,S,I,L,K,4):
				return alpha | X11_CORNSILK_4;
			case _I(C,O,R,N,S,I,L,K,_,4):
				return alpha | X11_CORNSILK_4;
			case _I(C,O,R,N,S,I,L,K, ,4):
				return alpha | X11_CORNSILK_4;
			case _I(I,V,O,R,Y,1):
				return alpha | X11_IVORY_1;
			case _I(I,V,O,R,Y,_,1):
				return alpha | X11_IVORY_1;
			case _I(I,V,O,R,Y, ,1):
				return alpha | X11_IVORY_1;
			case _I(I,V,O,R,Y,2):
				return alpha | X11_IVORY_2;
			case _I(I,V,O,R,Y,_,2):
				return alpha | X11_IVORY_2;
			case _I(I,V,O,R,Y, ,2):
				return alpha | X11_IVORY_2;
			case _I(I,V,O,R,Y,3):
				return alpha | X11_IVORY_3;
			case _I(I,V,O,R,Y,_,3):
				return alpha | X11_IVORY_3;
			case _I(I,V,O,R,Y, ,3):
				return alpha | X11_IVORY_3;
			case _I(I,V,O,R,Y,4):
				return alpha | X11_IVORY_4;
			case _I(I,V,O,R,Y,_,4):
				return alpha | X11_IVORY_4;
			case _I(I,V,O,R,Y, ,4):
				return alpha | X11_IVORY_4;
			case _I(H,O,N,E,Y,D,E,W,1):
				return alpha | X11_HONEYDEW_1;
			case _I(H,O,N,E,Y,D,E,W,_,1):
				return alpha | X11_HONEYDEW_1;
			case _I(H,O,N,E,Y,D,E,W, ,1):
				return alpha | X11_HONEYDEW_1;
			case _I(H,O,N,E,Y,D,E,W,2):
				return alpha | X11_HONEYDEW_2;
			case _I(H,O,N,E,Y,D,E,W,_,2):
				return alpha | X11_HONEYDEW_2;
			case _I(H,O,N,E,Y,D,E,W, ,2):
				return alpha | X11_HONEYDEW_2;
			case _I(H,O,N,E,Y,D,E,W,3):
				return alpha | X11_HONEYDEW_3;
			case _I(H,O,N,E,Y,D,E,W,_,3):
				return alpha | X11_HONEYDEW_3;
			case _I(H,O,N,E,Y,D,E,W, ,3):
				return alpha | X11_HONEYDEW_3;
			case _I(H,O,N,E,Y,D,E,W,4):
				return alpha | X11_HONEYDEW_4;
			case _I(H,O,N,E,Y,D,E,W,_,4):
				return alpha | X11_HONEYDEW_4;
			case _I(H,O,N,E,Y,D,E,W, ,4):
				return alpha | X11_HONEYDEW_4;
			case _I(L,A,V,E,N,D,E,R,B,L,U,S,H,1):
				return alpha | X11_LAVENDER_BLUSH_1;
			case _I(L,A,V,E,N,D,E,R,_,B,L,U,S,H,_,1):
				return alpha | X11_LAVENDER_BLUSH_1;
			case _I(L,A,V,E,N,D,E,R, ,B,L,U,S,H, ,1):
				return alpha | X11_LAVENDER_BLUSH_1;
			case _I(L,A,V,E,N,D,E,R,B,L,U,S,H,2):
				return alpha | X11_LAVENDER_BLUSH_2;
			case _I(L,A,V,E,N,D,E,R,_,B,L,U,S,H,_,2):
				return alpha | X11_LAVENDER_BLUSH_2;
			case _I(L,A,V,E,N,D,E,R, ,B,L,U,S,H, ,2):
				return alpha | X11_LAVENDER_BLUSH_2;
			case _I(L,A,V,E,N,D,E,R,B,L,U,S,H,3):
				return alpha | X11_LAVENDER_BLUSH_3;
			case _I(L,A,V,E,N,D,E,R,_,B,L,U,S,H,_,3):
				return alpha | X11_LAVENDER_BLUSH_3;
			case _I(L,A,V,E,N,D,E,R, ,B,L,U,S,H, ,3):
				return alpha | X11_LAVENDER_BLUSH_3;
			case _I(L,A,V,E,N,D,E,R,B,L,U,S,H,4):
				return alpha | X11_LAVENDER_BLUSH_4;
			case _I(L,A,V,E,N,D,E,R,_,B,L,U,S,H,_,4):
				return alpha | X11_LAVENDER_BLUSH_4;
			case _I(L,A,V,E,N,D,E,R, ,B,L,U,S,H, ,4):
				return alpha | X11_LAVENDER_BLUSH_4;
			case _I(M,I,S,T,Y,R,O,S,E,1):
				return alpha | X11_MISTY_ROSE_1;
			case _I(M,I,S,T,Y,_,R,O,S,E,_,1):
				return alpha | X11_MISTY_ROSE_1;
			case _I(M,I,S,T,Y, ,R,O,S,E, ,1):
				return alpha | X11_MISTY_ROSE_1;
			case _I(M,I,S,T,Y,R,O,S,E,2):
				return alpha | X11_MISTY_ROSE_2;
			case _I(M,I,S,T,Y,_,R,O,S,E,_,2):
				return alpha | X11_MISTY_ROSE_2;
			case _I(M,I,S,T,Y, ,R,O,S,E, ,2):
				return alpha | X11_MISTY_ROSE_2;
			case _I(M,I,S,T,Y,R,O,S,E,3):
				return alpha | X11_MISTY_ROSE_3;
			case _I(M,I,S,T,Y,_,R,O,S,E,_,3):
				return alpha | X11_MISTY_ROSE_3;
			case _I(M,I,S,T,Y, ,R,O,S,E, ,3):
				return alpha | X11_MISTY_ROSE_3;
			case _I(M,I,S,T,Y,R,O,S,E,4):
				return alpha | X11_MISTY_ROSE_4;
			case _I(M,I,S,T,Y,_,R,O,S,E,_,4):
				return alpha | X11_MISTY_ROSE_4;
			case _I(M,I,S,T,Y, ,R,O,S,E, ,4):
				return alpha | X11_MISTY_ROSE_4;
			case _I(A,Z,U,R,E,1):
				return alpha | X11_AZURE_1;
			case _I(A,Z,U,R,E,_,1):
				return alpha | X11_AZURE_1;
			case _I(A,Z,U,R,E, ,1):
				return alpha | X11_AZURE_1;
			case _I(A,Z,U,R,E,2):
				return alpha | X11_AZURE_2;
			case _I(A,Z,U,R,E,_,2):
				return alpha | X11_AZURE_2;
			case _I(A,Z,U,R,E, ,2):
				return alpha | X11_AZURE_2;
			case _I(A,Z,U,R,E,3):
				return alpha | X11_AZURE_3;
			case _I(A,Z,U,R,E,_,3):
				return alpha | X11_AZURE_3;
			case _I(A,Z,U,R,E, ,3):
				return alpha | X11_AZURE_3;
			case _I(A,Z,U,R,E,4):
				return alpha | X11_AZURE_4;
			case _I(A,Z,U,R,E,_,4):
				return alpha | X11_AZURE_4;
			case _I(A,Z,U,R,E, ,4):
				return alpha | X11_AZURE_4;
			case _I(S,L,A,T,E,B,L,U,E,1):
				return alpha | X11_SLATE_BLUE_1;
			case _I(S,L,A,T,E,_,B,L,U,E,_,1):
				return alpha | X11_SLATE_BLUE_1;
			case _I(S,L,A,T,E, ,B,L,U,E, ,1):
				return alpha | X11_SLATE_BLUE_1;
			case _I(S,L,A,T,E,B,L,U,E,2):
				return alpha | X11_SLATE_BLUE_2;
			case _I(S,L,A,T,E,_,B,L,U,E,_,2):
				return alpha | X11_SLATE_BLUE_2;
			case _I(S,L,A,T,E, ,B,L,U,E, ,2):
				return alpha | X11_SLATE_BLUE_2;
			case _I(S,L,A,T,E,B,L,U,E,3):
				return alpha | X11_SLATE_BLUE_3;
			case _I(S,L,A,T,E,_,B,L,U,E,_,3):
				return alpha | X11_SLATE_BLUE_3;
			case _I(S,L,A,T,E, ,B,L,U,E, ,3):
				return alpha | X11_SLATE_BLUE_3;
			case _I(S,L,A,T,E,B,L,U,E,4):
				return alpha | X11_SLATE_BLUE_4;
			case _I(S,L,A,T,E,_,B,L,U,E,_,4):
				return alpha | X11_SLATE_BLUE_4;
			case _I(S,L,A,T,E, ,B,L,U,E, ,4):
				return alpha | X11_SLATE_BLUE_4;
			case _I(R,O,Y,A,L,B,L,U,E,1):
				return alpha | X11_ROYAL_BLUE_1;
			case _I(R,O,Y,A,L,_,B,L,U,E,_,1):
				return alpha | X11_ROYAL_BLUE_1;
			case _I(R,O,Y,A,L, ,B,L,U,E, ,1):
				return alpha | X11_ROYAL_BLUE_1;
			case _I(R,O,Y,A,L,B,L,U,E,2):
				return alpha | X11_ROYAL_BLUE_2;
			case _I(R,O,Y,A,L,_,B,L,U,E,_,2):
				return alpha | X11_ROYAL_BLUE_2;
			case _I(R,O,Y,A,L, ,B,L,U,E, ,2):
				return alpha | X11_ROYAL_BLUE_2;
			case _I(R,O,Y,A,L,B,L,U,E,3):
				return alpha | X11_ROYAL_BLUE_3;
			case _I(R,O,Y,A,L,_,B,L,U,E,_,3):
				return alpha | X11_ROYAL_BLUE_3;
			case _I(R,O,Y,A,L, ,B,L,U,E, ,3):
				return alpha | X11_ROYAL_BLUE_3;
			case _I(R,O,Y,A,L,B,L,U,E,4):
				return alpha | X11_ROYAL_BLUE_4;
			case _I(R,O,Y,A,L,_,B,L,U,E,_,4):
				return alpha | X11_ROYAL_BLUE_4;
			case _I(R,O,Y,A,L, ,B,L,U,E, ,4):
				return alpha | X11_ROYAL_BLUE_4;
			case _I(B,L,U,E,1):
				return alpha | X11_BLUE_1;
			case _I(B,L,U,E,_,1):
				return alpha | X11_BLUE_1;
			case _I(B,L,U,E, ,1):
				return alpha | X11_BLUE_1;
			case _I(B,L,U,E,2):
				return alpha | X11_BLUE_2;
			case _I(B,L,U,E,_,2):
				return alpha | X11_BLUE_2;
			case _I(B,L,U,E, ,2):
				return alpha | X11_BLUE_2;
			case _I(B,L,U,E,3):
				return alpha | X11_BLUE_3;
			case _I(B,L,U,E,_,3):
				return alpha | X11_BLUE_3;
			case _I(B,L,U,E, ,3):
				return alpha | X11_BLUE_3;
			case _I(B,L,U,E,4):
				return alpha | X11_BLUE_4;
			case _I(B,L,U,E,_,4):
				return alpha | X11_BLUE_4;
			case _I(B,L,U,E, ,4):
				return alpha | X11_BLUE_4;
			case _I(D,O,D,G,E,R,B,L,U,E,1):
				return alpha | X11_DODGER_BLUE_1;
			case _I(D,O,D,G,E,R,_,B,L,U,E,_,1):
				return alpha | X11_DODGER_BLUE_1;
			case _I(D,O,D,G,E,R, ,B,L,U,E, ,1):
				return alpha | X11_DODGER_BLUE_1;
			case _I(D,O,D,G,E,R,B,L,U,E,2):
				return alpha | X11_DODGER_BLUE_2;
			case _I(D,O,D,G,E,R,_,B,L,U,E,_,2):
				return alpha | X11_DODGER_BLUE_2;
			case _I(D,O,D,G,E,R, ,B,L,U,E, ,2):
				return alpha | X11_DODGER_BLUE_2;
			case _I(D,O,D,G,E,R,B,L,U,E,3):
				return alpha | X11_DODGER_BLUE_3;
			case _I(D,O,D,G,E,R,_,B,L,U,E,_,3):
				return alpha | X11_DODGER_BLUE_3;
			case _I(D,O,D,G,E,R, ,B,L,U,E, ,3):
				return alpha | X11_DODGER_BLUE_3;
			case _I(D,O,D,G,E,R,B,L,U,E,4):
				return alpha | X11_DODGER_BLUE_4;
			case _I(D,O,D,G,E,R,_,B,L,U,E,_,4):
				return alpha | X11_DODGER_BLUE_4;
			case _I(D,O,D,G,E,R, ,B,L,U,E, ,4):
				return alpha | X11_DODGER_BLUE_4;
			case _I(S,T,E,E,L,B,L,U,E,1):
				return alpha | X11_STEEL_BLUE_1;
			case _I(S,T,E,E,L,_,B,L,U,E,_,1):
				return alpha | X11_STEEL_BLUE_1;
			case _I(S,T,E,E,L, ,B,L,U,E, ,1):
				return alpha | X11_STEEL_BLUE_1;
			case _I(S,T,E,E,L,B,L,U,E,2):
				return alpha | X11_STEEL_BLUE_2;
			case _I(S,T,E,E,L,_,B,L,U,E,_,2):
				return alpha | X11_STEEL_BLUE_2;
			case _I(S,T,E,E,L, ,B,L,U,E, ,2):
				return alpha | X11_STEEL_BLUE_2;
			case _I(S,T,E,E,L,B,L,U,E,3):
				return alpha | X11_STEEL_BLUE_3;
			case _I(S,T,E,E,L,_,B,L,U,E,_,3):
				return alpha | X11_STEEL_BLUE_3;
			case _I(S,T,E,E,L, ,B,L,U,E, ,3):
				return alpha | X11_STEEL_BLUE_3;
			case _I(S,T,E,E,L,B,L,U,E,4):
				return alpha | X11_STEEL_BLUE_4;
			case _I(S,T,E,E,L,_,B,L,U,E,_,4):
				return alpha | X11_STEEL_BLUE_4;
			case _I(S,T,E,E,L, ,B,L,U,E, ,4):
				return alpha | X11_STEEL_BLUE_4;
			case _I(D,E,E,P,S,K,Y,B,L,U,E,1):
				return alpha | X11_DEEP_SKY_BLUE_1;
			case _I(D,E,E,P,_,S,K,Y,_,B,L,U,E,_,1):
				return alpha | X11_DEEP_SKY_BLUE_1;
			case _I(D,E,E,P, ,S,K,Y, ,B,L,U,E, ,1):
				return alpha | X11_DEEP_SKY_BLUE_1;
			case _I(D,E,E,P,S,K,Y,B,L,U,E,2):
				return alpha | X11_DEEP_SKY_BLUE_2;
			case _I(D,E,E,P,_,S,K,Y,_,B,L,U,E,_,2):
				return alpha | X11_DEEP_SKY_BLUE_2;
			case _I(D,E,E,P, ,S,K,Y, ,B,L,U,E, ,2):
				return alpha | X11_DEEP_SKY_BLUE_2;
			case _I(D,E,E,P,S,K,Y,B,L,U,E,3):
				return alpha | X11_DEEP_SKY_BLUE_3;
			case _I(D,E,E,P,_,S,K,Y,_,B,L,U,E,_,3):
				return alpha | X11_DEEP_SKY_BLUE_3;
			case _I(D,E,E,P, ,S,K,Y, ,B,L,U,E, ,3):
				return alpha | X11_DEEP_SKY_BLUE_3;
			case _I(D,E,E,P,S,K,Y,B,L,U,E,4):
				return alpha | X11_DEEP_SKY_BLUE_4;
			case _I(D,E,E,P,_,S,K,Y,_,B,L,U,E,_,4):
				return alpha | X11_DEEP_SKY_BLUE_4;
			case _I(D,E,E,P, ,S,K,Y, ,B,L,U,E, ,4):
				return alpha | X11_DEEP_SKY_BLUE_4;
			case _I(S,K,Y,B,L,U,E,1):
				return alpha | X11_SKY_BLUE_1;
			case _I(S,K,Y,_,B,L,U,E,_,1):
				return alpha | X11_SKY_BLUE_1;
			case _I(S,K,Y, ,B,L,U,E, ,1):
				return alpha | X11_SKY_BLUE_1;
			case _I(S,K,Y,B,L,U,E,2):
				return alpha | X11_SKY_BLUE_2;
			case _I(S,K,Y,_,B,L,U,E,_,2):
				return alpha | X11_SKY_BLUE_2;
			case _I(S,K,Y, ,B,L,U,E, ,2):
				return alpha | X11_SKY_BLUE_2;
			case _I(S,K,Y,B,L,U,E,3):
				return alpha | X11_SKY_BLUE_3;
			case _I(S,K,Y,_,B,L,U,E,_,3):
				return alpha | X11_SKY_BLUE_3;
			case _I(S,K,Y, ,B,L,U,E, ,3):
				return alpha | X11_SKY_BLUE_3;
			case _I(S,K,Y,B,L,U,E,4):
				return alpha | X11_SKY_BLUE_4;
			case _I(S,K,Y,_,B,L,U,E,_,4):
				return alpha | X11_SKY_BLUE_4;
			case _I(S,K,Y, ,B,L,U,E, ,4):
				return alpha | X11_SKY_BLUE_4;
			case _I(L,I,G,H,T,S,K,Y,B,L,U,E,1):
				return alpha | X11_LIGHT_SKY_BLUE_1;
			case _I(L,I,G,H,T,_,S,K,Y,_,B,L,U,E,_,1):
				return alpha | X11_LIGHT_SKY_BLUE_1;
			case _I(L,I,G,H,T, ,S,K,Y, ,B,L,U,E, ,1):
				return alpha | X11_LIGHT_SKY_BLUE_1;
			case _I(L,I,G,H,T,S,K,Y,B,L,U,E,2):
				return alpha | X11_LIGHT_SKY_BLUE_2;
			case _I(L,I,G,H,T,_,S,K,Y,_,B,L,U,E,_,2):
				return alpha | X11_LIGHT_SKY_BLUE_2;
			case _I(L,I,G,H,T, ,S,K,Y, ,B,L,U,E, ,2):
				return alpha | X11_LIGHT_SKY_BLUE_2;
			case _I(L,I,G,H,T,S,K,Y,B,L,U,E,3):
				return alpha | X11_LIGHT_SKY_BLUE_3;
			case _I(L,I,G,H,T,_,S,K,Y,_,B,L,U,E,_,3):
				return alpha | X11_LIGHT_SKY_BLUE_3;
			case _I(L,I,G,H,T, ,S,K,Y, ,B,L,U,E, ,3):
				return alpha | X11_LIGHT_SKY_BLUE_3;
			case _I(L,I,G,H,T,S,K,Y,B,L,U,E,4):
				return alpha | X11_LIGHT_SKY_BLUE_4;
			case _I(L,I,G,H,T,_,S,K,Y,_,B,L,U,E,_,4):
				return alpha | X11_LIGHT_SKY_BLUE_4;
			case _I(L,I,G,H,T, ,S,K,Y, ,B,L,U,E, ,4):
				return alpha | X11_LIGHT_SKY_BLUE_4;
			case _I(S,L,A,T,E,G,R,A,Y,1):
				return alpha | X11_SLATE_GRAY_1;
			case _I(S,L,A,T,E,_,G,R,A,Y,_,1):
				return alpha | X11_SLATE_GRAY_1;
			case _I(S,L,A,T,E, ,G,R,A,Y, ,1):
				return alpha | X11_SLATE_GRAY_1;
			case _I(S,L,A,T,E,G,R,A,Y,2):
				return alpha | X11_SLATE_GRAY_2;
			case _I(S,L,A,T,E,_,G,R,A,Y,_,2):
				return alpha | X11_SLATE_GRAY_2;
			case _I(S,L,A,T,E, ,G,R,A,Y, ,2):
				return alpha | X11_SLATE_GRAY_2;
			case _I(S,L,A,T,E,G,R,A,Y,3):
				return alpha | X11_SLATE_GRAY_3;
			case _I(S,L,A,T,E,_,G,R,A,Y,_,3):
				return alpha | X11_SLATE_GRAY_3;
			case _I(S,L,A,T,E, ,G,R,A,Y, ,3):
				return alpha | X11_SLATE_GRAY_3;
			case _I(S,L,A,T,E,G,R,A,Y,4):
				return alpha | X11_SLATE_GRAY_4;
			case _I(S,L,A,T,E,_,G,R,A,Y,_,4):
				return alpha | X11_SLATE_GRAY_4;
			case _I(S,L,A,T,E, ,G,R,A,Y, ,4):
				return alpha | X11_SLATE_GRAY_4;
				
			case _I(S,L,A,T,E,G,R,E,Y,1):
				return alpha | X11_SLATE_GREY_1;
			case _I(S,L,A,T,E,_,G,R,E,Y,_,1):
				return alpha | X11_SLATE_GREY_1;
			case _I(S,L,A,T,E, ,G,R,E,Y, ,1):
				return alpha | X11_SLATE_GREY_1;
			case _I(S,L,A,T,E,G,R,E,Y,2):
				return alpha | X11_SLATE_GREY_2;
			case _I(S,L,A,T,E,_,G,R,E,Y,_,2):
				return alpha | X11_SLATE_GREY_2;
			case _I(S,L,A,T,E, ,G,R,E,Y, ,2):
				return alpha | X11_SLATE_GREY_2;
			case _I(S,L,A,T,E,G,R,E,Y,3):
				return alpha | X11_SLATE_GREY_3;
			case _I(S,L,A,T,E,_,G,R,E,Y,_,3):
				return alpha | X11_SLATE_GREY_3;
			case _I(S,L,A,T,E, ,G,R,E,Y, ,3):
				return alpha | X11_SLATE_GREY_3;
			case _I(S,L,A,T,E,G,R,E,Y,4):
				return alpha | X11_SLATE_GREY_4;
			case _I(S,L,A,T,E,_,G,R,E,Y,_,4):
				return alpha | X11_SLATE_GREY_4;
			case _I(S,L,A,T,E, ,G,R,E,Y, ,4):
				return alpha | X11_SLATE_GREY_4;
				
			case _I(L,I,G,H,T,S,T,E,E,L,B,L,U,E,1):
				return alpha | X11_LIGHT_STEEL_BLUE_1;
			case _I(L,I,G,H,T,_,S,T,E,E,L,_,B,L,U,E,_,1):
				return alpha | X11_LIGHT_STEEL_BLUE_1;
			case _I(L,I,G,H,T, ,S,T,E,E,L, ,B,L,U,E, ,1):
				return alpha | X11_LIGHT_STEEL_BLUE_1;
			case _I(L,I,G,H,T,S,T,E,E,L,B,L,U,E,2):
				return alpha | X11_LIGHT_STEEL_BLUE_2;
			case _I(L,I,G,H,T,_,S,T,E,E,L,_,B,L,U,E,_,2):
				return alpha | X11_LIGHT_STEEL_BLUE_2;
			case _I(L,I,G,H,T, ,S,T,E,E,L, ,B,L,U,E, ,2):
				return alpha | X11_LIGHT_STEEL_BLUE_2;
			case _I(L,I,G,H,T,S,T,E,E,L,B,L,U,E,3):
				return alpha | X11_LIGHT_STEEL_BLUE_3;
			case _I(L,I,G,H,T,_,S,T,E,E,L,_,B,L,U,E,_,3):
				return alpha | X11_LIGHT_STEEL_BLUE_3;
			case _I(L,I,G,H,T, ,S,T,E,E,L, ,B,L,U,E, ,3):
				return alpha | X11_LIGHT_STEEL_BLUE_3;
			case _I(L,I,G,H,T,S,T,E,E,L,B,L,U,E,4):
				return alpha | X11_LIGHT_STEEL_BLUE_4;
			case _I(L,I,G,H,T,_,S,T,E,E,L,_,B,L,U,E,_,4):
				return alpha | X11_LIGHT_STEEL_BLUE_4;
			case _I(L,I,G,H,T, ,S,T,E,E,L, ,B,L,U,E, ,4):
				return alpha | X11_LIGHT_STEEL_BLUE_4;
			case _I(L,I,G,H,T,B,L,U,E,1):
				return alpha | X11_LIGHT_BLUE_1;
			case _I(L,I,G,H,T,_,B,L,U,E,_,1):
				return alpha | X11_LIGHT_BLUE_1;
			case _I(L,I,G,H,T, ,B,L,U,E, ,1):
				return alpha | X11_LIGHT_BLUE_1;
			case _I(L,I,G,H,T,B,L,U,E,2):
				return alpha | X11_LIGHT_BLUE_2;
			case _I(L,I,G,H,T,_,B,L,U,E,_,2):
				return alpha | X11_LIGHT_BLUE_2;
			case _I(L,I,G,H,T, ,B,L,U,E, ,2):
				return alpha | X11_LIGHT_BLUE_2;
			case _I(L,I,G,H,T,B,L,U,E,3):
				return alpha | X11_LIGHT_BLUE_3;
			case _I(L,I,G,H,T,_,B,L,U,E,_,3):
				return alpha | X11_LIGHT_BLUE_3;
			case _I(L,I,G,H,T, ,B,L,U,E, ,3):
				return alpha | X11_LIGHT_BLUE_3;
			case _I(L,I,G,H,T,B,L,U,E,4):
				return alpha | X11_LIGHT_BLUE_4;
			case _I(L,I,G,H,T,_,B,L,U,E,_,4):
				return alpha | X11_LIGHT_BLUE_4;
			case _I(L,I,G,H,T, ,B,L,U,E, ,4):
				return alpha | X11_LIGHT_BLUE_4;
			case _I(L,I,G,H,T,C,Y,A,N,1):
				return alpha | X11_LIGHT_CYAN_1;
			case _I(L,I,G,H,T,_,C,Y,A,N,_,1):
				return alpha | X11_LIGHT_CYAN_1;
			case _I(L,I,G,H,T, ,C,Y,A,N, ,1):
				return alpha | X11_LIGHT_CYAN_1;
			case _I(L,I,G,H,T,C,Y,A,N,2):
				return alpha | X11_LIGHT_CYAN_2;
			case _I(L,I,G,H,T,_,C,Y,A,N,_,2):
				return alpha | X11_LIGHT_CYAN_2;
			case _I(L,I,G,H,T, ,C,Y,A,N, ,2):
				return alpha | X11_LIGHT_CYAN_2;
			case _I(L,I,G,H,T,C,Y,A,N,3):
				return alpha | X11_LIGHT_CYAN_3;
			case _I(L,I,G,H,T,_,C,Y,A,N,_,3):
				return alpha | X11_LIGHT_CYAN_3;
			case _I(L,I,G,H,T, ,C,Y,A,N, ,3):
				return alpha | X11_LIGHT_CYAN_3;
			case _I(L,I,G,H,T,C,Y,A,N,4):
				return alpha | X11_LIGHT_CYAN_4;
			case _I(L,I,G,H,T,_,C,Y,A,N,_,4):
				return alpha | X11_LIGHT_CYAN_4;
			case _I(L,I,G,H,T, ,C,Y,A,N, ,4):
				return alpha | X11_LIGHT_CYAN_4;
			case _I(P,A,L,E,T,U,R,Q,U,O,I,S,E,1):
				return alpha | X11_PALE_TURQUOISE_1;
			case _I(P,A,L,E,_,T,U,R,Q,U,O,I,S,E,_,1):
				return alpha | X11_PALE_TURQUOISE_1;
			case _I(P,A,L,E, ,T,U,R,Q,U,O,I,S,E, ,1):
				return alpha | X11_PALE_TURQUOISE_1;
			case _I(P,A,L,E,T,U,R,Q,U,O,I,S,E,2):
				return alpha | X11_PALE_TURQUOISE_2;
			case _I(P,A,L,E,_,T,U,R,Q,U,O,I,S,E,_,2):
				return alpha | X11_PALE_TURQUOISE_2;
			case _I(P,A,L,E, ,T,U,R,Q,U,O,I,S,E, ,2):
				return alpha | X11_PALE_TURQUOISE_2;
			case _I(P,A,L,E,T,U,R,Q,U,O,I,S,E,3):
				return alpha | X11_PALE_TURQUOISE_3;
			case _I(P,A,L,E,_,T,U,R,Q,U,O,I,S,E,_,3):
				return alpha | X11_PALE_TURQUOISE_3;
			case _I(P,A,L,E, ,T,U,R,Q,U,O,I,S,E, ,3):
				return alpha | X11_PALE_TURQUOISE_3;
			case _I(P,A,L,E,T,U,R,Q,U,O,I,S,E,4):
				return alpha | X11_PALE_TURQUOISE_4;
			case _I(P,A,L,E,_,T,U,R,Q,U,O,I,S,E,_,4):
				return alpha | X11_PALE_TURQUOISE_4;
			case _I(P,A,L,E, ,T,U,R,Q,U,O,I,S,E, ,4):
				return alpha | X11_PALE_TURQUOISE_4;
			case _I(C,A,D,E,T,B,L,U,E,1):
				return alpha | X11_CADET_BLUE_1;
			case _I(C,A,D,E,T,_,B,L,U,E,_,1):
				return alpha | X11_CADET_BLUE_1;
			case _I(C,A,D,E,T, ,B,L,U,E, ,1):
				return alpha | X11_CADET_BLUE_1;
			case _I(C,A,D,E,T,B,L,U,E,2):
				return alpha | X11_CADET_BLUE_2;
			case _I(C,A,D,E,T,_,B,L,U,E,_,2):
				return alpha | X11_CADET_BLUE_2;
			case _I(C,A,D,E,T, ,B,L,U,E, ,2):
				return alpha | X11_CADET_BLUE_2;
			case _I(C,A,D,E,T,B,L,U,E,3):
				return alpha | X11_CADET_BLUE_3;
			case _I(C,A,D,E,T,_,B,L,U,E,_,3):
				return alpha | X11_CADET_BLUE_3;
			case _I(C,A,D,E,T, ,B,L,U,E, ,3):
				return alpha | X11_CADET_BLUE_3;
			case _I(C,A,D,E,T,B,L,U,E,4):
				return alpha | X11_CADET_BLUE_4;
			case _I(C,A,D,E,T,_,B,L,U,E,_,4):
				return alpha | X11_CADET_BLUE_4;
			case _I(C,A,D,E,T, ,B,L,U,E, ,4):
				return alpha | X11_CADET_BLUE_4;
			case _I(T,U,R,Q,U,O,I,S,E,1):
				return alpha | X11_TURQUOISE_1;
			case _I(T,U,R,Q,U,O,I,S,E,_,1):
				return alpha | X11_TURQUOISE_1;
			case _I(T,U,R,Q,U,O,I,S,E, ,1):
				return alpha | X11_TURQUOISE_1;
			case _I(T,U,R,Q,U,O,I,S,E,2):
				return alpha | X11_TURQUOISE_2;
			case _I(T,U,R,Q,U,O,I,S,E,_,2):
				return alpha | X11_TURQUOISE_2;
			case _I(T,U,R,Q,U,O,I,S,E, ,2):
				return alpha | X11_TURQUOISE_2;
			case _I(T,U,R,Q,U,O,I,S,E,3):
				return alpha | X11_TURQUOISE_3;
			case _I(T,U,R,Q,U,O,I,S,E,_,3):
				return alpha | X11_TURQUOISE_3;
			case _I(T,U,R,Q,U,O,I,S,E, ,3):
				return alpha | X11_TURQUOISE_3;
			case _I(T,U,R,Q,U,O,I,S,E,4):
				return alpha | X11_TURQUOISE_4;
			case _I(T,U,R,Q,U,O,I,S,E,_,4):
				return alpha | X11_TURQUOISE_4;
			case _I(T,U,R,Q,U,O,I,S,E, ,4):
				return alpha | X11_TURQUOISE_4;
			case _I(C,Y,A,N,1):
				return alpha | X11_CYAN_1;
			case _I(C,Y,A,N,_,1):
				return alpha | X11_CYAN_1;
			case _I(C,Y,A,N, ,1):
				return alpha | X11_CYAN_1;
			case _I(C,Y,A,N,2):
				return alpha | X11_CYAN_2;
			case _I(C,Y,A,N,_,2):
				return alpha | X11_CYAN_2;
			case _I(C,Y,A,N, ,2):
				return alpha | X11_CYAN_2;
			case _I(C,Y,A,N,3):
				return alpha | X11_CYAN_3;
			case _I(C,Y,A,N,_,3):
				return alpha | X11_CYAN_3;
			case _I(C,Y,A,N, ,3):
				return alpha | X11_CYAN_3;
			case _I(C,Y,A,N,4):
				return alpha | X11_CYAN_4;
			case _I(C,Y,A,N,_,4):
				return alpha | X11_CYAN_4;
			case _I(C,Y,A,N, ,4):
				return alpha | X11_CYAN_4;
			
			case _I(D,A,R,K,S,L,A,T,E,G,R,A,Y,1):
				return alpha | X11_DARK_SLATE_GRAY_1;
			case _I(D,A,R,K,_,S,L,A,T,E,_,G,R,A,Y,_,1):
				return alpha | X11_DARK_SLATE_GRAY_1;
			case _I(D,A,R,K, ,S,L,A,T,E, ,G,R,A,Y, ,1):
				return alpha | X11_DARK_SLATE_GRAY_1;
			case _I(D,A,R,K,S,L,A,T,E,G,R,A,Y,2):
				return alpha | X11_DARK_SLATE_GRAY_2;
			case _I(D,A,R,K,_,S,L,A,T,E,_,G,R,A,Y,_,2):
				return alpha | X11_DARK_SLATE_GRAY_2;
			case _I(D,A,R,K, ,S,L,A,T,E, ,G,R,A,Y, ,2):
				return alpha | X11_DARK_SLATE_GRAY_2;
			case _I(D,A,R,K,S,L,A,T,E,G,R,A,Y,3):
				return alpha | X11_DARK_SLATE_GRAY_3;
			case _I(D,A,R,K,_,S,L,A,T,E,_,G,R,A,Y,_,3):
				return alpha | X11_DARK_SLATE_GRAY_3;
			case _I(D,A,R,K, ,S,L,A,T,E, ,G,R,A,Y, ,3):
				return alpha | X11_DARK_SLATE_GRAY_3;
			case _I(D,A,R,K,S,L,A,T,E,G,R,A,Y,4):
				return alpha | X11_DARK_SLATE_GRAY_4;
			case _I(D,A,R,K,_,S,L,A,T,E,_,G,R,A,Y,_,4):
				return alpha | X11_DARK_SLATE_GRAY_4;
			case _I(D,A,R,K, ,S,L,A,T,E, ,G,R,A,Y, ,4):
				return alpha | X11_DARK_SLATE_GRAY_4;
			
			case _I(D,A,R,K,S,L,A,T,E,G,R,E,Y,1):
				return alpha | X11_DARK_SLATE_GREY_1;
			case _I(D,A,R,K,_,S,L,A,T,E,_,G,R,E,Y,_,1):
				return alpha | X11_DARK_SLATE_GREY_1;
			case _I(D,A,R,K, ,S,L,A,T,E, ,G,R,E,Y, ,1):
				return alpha | X11_DARK_SLATE_GREY_1;
			case _I(D,A,R,K,S,L,A,T,E,G,R,E,Y,2):
				return alpha | X11_DARK_SLATE_GREY_2;
			case _I(D,A,R,K,_,S,L,A,T,E,_,G,R,E,Y,_,2):
				return alpha | X11_DARK_SLATE_GREY_2;
			case _I(D,A,R,K, ,S,L,A,T,E, ,G,R,E,Y, ,2):
				return alpha | X11_DARK_SLATE_GREY_2;
			case _I(D,A,R,K,S,L,A,T,E,G,R,E,Y,3):
				return alpha | X11_DARK_SLATE_GREY_3;
			case _I(D,A,R,K,_,S,L,A,T,E,_,G,R,E,Y,_,3):
				return alpha | X11_DARK_SLATE_GREY_3;
			case _I(D,A,R,K, ,S,L,A,T,E, ,G,R,E,Y, ,3):
				return alpha | X11_DARK_SLATE_GREY_3;
			case _I(D,A,R,K,S,L,A,T,E,G,R,E,Y,4):
				return alpha | X11_DARK_SLATE_GREY_4;
			case _I(D,A,R,K,_,S,L,A,T,E,_,G,R,E,Y,_,4):
				return alpha | X11_DARK_SLATE_GREY_4;
			case _I(D,A,R,K, ,S,L,A,T,E, ,G,R,E,Y, ,4):
				return alpha | X11_DARK_SLATE_GREY_4;
			
			case _I(A,Q,U,A,M,A,R,I,N,E,1):
				return alpha | X11_AQUAMARINE_1;
			case _I(A,Q,U,A,M,A,R,I,N,E,_,1):
				return alpha | X11_AQUAMARINE_1;
			case _I(A,Q,U,A,M,A,R,I,N,E, ,1):
				return alpha | X11_AQUAMARINE_1;
			case _I(A,Q,U,A,M,A,R,I,N,E,2):
				return alpha | X11_AQUAMARINE_2;
			case _I(A,Q,U,A,M,A,R,I,N,E,_,2):
				return alpha | X11_AQUAMARINE_2;
			case _I(A,Q,U,A,M,A,R,I,N,E, ,2):
				return alpha | X11_AQUAMARINE_2;
			case _I(A,Q,U,A,M,A,R,I,N,E,3):
				return alpha | X11_AQUAMARINE_3;
			case _I(A,Q,U,A,M,A,R,I,N,E,_,3):
				return alpha | X11_AQUAMARINE_3;
			case _I(A,Q,U,A,M,A,R,I,N,E, ,3):
				return alpha | X11_AQUAMARINE_3;
			case _I(A,Q,U,A,M,A,R,I,N,E,4):
				return alpha | X11_AQUAMARINE_4;
			case _I(A,Q,U,A,M,A,R,I,N,E,_,4):
				return alpha | X11_AQUAMARINE_4;
			case _I(A,Q,U,A,M,A,R,I,N,E, ,4):
				return alpha | X11_AQUAMARINE_4;
			case _I(D,A,R,K,S,E,A,G,R,E,E,N,1):
				return alpha | X11_DARK_SEA_GREEN_1;
			case _I(D,A,R,K,_,S,E,A,_,G,R,E,E,N,_,1):
				return alpha | X11_DARK_SEA_GREEN_1;
			case _I(D,A,R,K, ,S,E,A, ,G,R,E,E,N, ,1):
				return alpha | X11_DARK_SEA_GREEN_1;
			case _I(D,A,R,K,S,E,A,G,R,E,E,N,2):
				return alpha | X11_DARK_SEA_GREEN_2;
			case _I(D,A,R,K,_,S,E,A,_,G,R,E,E,N,_,2):
				return alpha | X11_DARK_SEA_GREEN_2;
			case _I(D,A,R,K, ,S,E,A, ,G,R,E,E,N, ,2):
				return alpha | X11_DARK_SEA_GREEN_2;
			case _I(D,A,R,K,S,E,A,G,R,E,E,N,3):
				return alpha | X11_DARK_SEA_GREEN_3;
			case _I(D,A,R,K,_,S,E,A,_,G,R,E,E,N,_,3):
				return alpha | X11_DARK_SEA_GREEN_3;
			case _I(D,A,R,K, ,S,E,A, ,G,R,E,E,N, ,3):
				return alpha | X11_DARK_SEA_GREEN_3;
			case _I(D,A,R,K,S,E,A,G,R,E,E,N,4):
				return alpha | X11_DARK_SEA_GREEN_4;
			case _I(D,A,R,K,_,S,E,A,_,G,R,E,E,N,_,4):
				return alpha | X11_DARK_SEA_GREEN_4;
			case _I(D,A,R,K, ,S,E,A, ,G,R,E,E,N, ,4):
				return alpha | X11_DARK_SEA_GREEN_4;
			case _I(S,E,A,G,R,E,E,N,1):
				return alpha | X11_SEA_GREEN_1;
			case _I(S,E,A,_,G,R,E,E,N,_,1):
				return alpha | X11_SEA_GREEN_1;
			case _I(S,E,A, ,G,R,E,E,N, ,1):
				return alpha | X11_SEA_GREEN_1;
			case _I(S,E,A,G,R,E,E,N,2):
				return alpha | X11_SEA_GREEN_2;
			case _I(S,E,A,_,G,R,E,E,N,_,2):
				return alpha | X11_SEA_GREEN_2;
			case _I(S,E,A, ,G,R,E,E,N, ,2):
				return alpha | X11_SEA_GREEN_2;
			case _I(S,E,A,G,R,E,E,N,3):
				return alpha | X11_SEA_GREEN_3;
			case _I(S,E,A,_,G,R,E,E,N,_,3):
				return alpha | X11_SEA_GREEN_3;
			case _I(S,E,A, ,G,R,E,E,N, ,3):
				return alpha | X11_SEA_GREEN_3;
			case _I(S,E,A,G,R,E,E,N,4):
				return alpha | X11_SEA_GREEN_4;
			case _I(S,E,A,_,G,R,E,E,N,_,4):
				return alpha | X11_SEA_GREEN_4;
			case _I(S,E,A, ,G,R,E,E,N, ,4):
				return alpha | X11_SEA_GREEN_4;
			case _I(P,A,L,E,G,R,E,E,N,1):
				return alpha | X11_PALE_GREEN_1;
			case _I(P,A,L,E,_,G,R,E,E,N,_,1):
				return alpha | X11_PALE_GREEN_1;
			case _I(P,A,L,E, ,G,R,E,E,N, ,1):
				return alpha | X11_PALE_GREEN_1;
			case _I(P,A,L,E,G,R,E,E,N,2):
				return alpha | X11_PALE_GREEN_2;
			case _I(P,A,L,E,_,G,R,E,E,N,_,2):
				return alpha | X11_PALE_GREEN_2;
			case _I(P,A,L,E, ,G,R,E,E,N, ,2):
				return alpha | X11_PALE_GREEN_2;
			case _I(P,A,L,E,G,R,E,E,N,3):
				return alpha | X11_PALE_GREEN_3;
			case _I(P,A,L,E,_,G,R,E,E,N,_,3):
				return alpha | X11_PALE_GREEN_3;
			case _I(P,A,L,E, ,G,R,E,E,N, ,3):
				return alpha | X11_PALE_GREEN_3;
			case _I(P,A,L,E,G,R,E,E,N,4):
				return alpha | X11_PALE_GREEN_4;
			case _I(P,A,L,E,_,G,R,E,E,N,_,4):
				return alpha | X11_PALE_GREEN_4;
			case _I(P,A,L,E, ,G,R,E,E,N, ,4):
				return alpha | X11_PALE_GREEN_4;
			case _I(S,P,R,I,N,G,G,R,E,E,N,1):
				return alpha | X11_SPRING_GREEN_1;
			case _I(S,P,R,I,N,G,_,G,R,E,E,N,_,1):
				return alpha | X11_SPRING_GREEN_1;
			case _I(S,P,R,I,N,G, ,G,R,E,E,N, ,1):
				return alpha | X11_SPRING_GREEN_1;
			case _I(S,P,R,I,N,G,G,R,E,E,N,2):
				return alpha | X11_SPRING_GREEN_2;
			case _I(S,P,R,I,N,G,_,G,R,E,E,N,_,2):
				return alpha | X11_SPRING_GREEN_2;
			case _I(S,P,R,I,N,G, ,G,R,E,E,N, ,2):
				return alpha | X11_SPRING_GREEN_2;
			case _I(S,P,R,I,N,G,G,R,E,E,N,3):
				return alpha | X11_SPRING_GREEN_3;
			case _I(S,P,R,I,N,G,_,G,R,E,E,N,_,3):
				return alpha | X11_SPRING_GREEN_3;
			case _I(S,P,R,I,N,G, ,G,R,E,E,N, ,3):
				return alpha | X11_SPRING_GREEN_3;
			case _I(S,P,R,I,N,G,G,R,E,E,N,4):
				return alpha | X11_SPRING_GREEN_4;
			case _I(S,P,R,I,N,G,_,G,R,E,E,N,_,4):
				return alpha | X11_SPRING_GREEN_4;
			case _I(S,P,R,I,N,G, ,G,R,E,E,N, ,4):
				return alpha | X11_SPRING_GREEN_4;
			case _I(G,R,E,E,N,1):
				return alpha | X11_GREEN_1;
			case _I(G,R,E,E,N,_,1):
				return alpha | X11_GREEN_1;
			case _I(G,R,E,E,N, ,1):
				return alpha | X11_GREEN_1;
			case _I(G,R,E,E,N,2):
				return alpha | X11_GREEN_2;
			case _I(G,R,E,E,N,_,2):
				return alpha | X11_GREEN_2;
			case _I(G,R,E,E,N, ,2):
				return alpha | X11_GREEN_2;
			case _I(G,R,E,E,N,3):
				return alpha | X11_GREEN_3;
			case _I(G,R,E,E,N,_,3):
				return alpha | X11_GREEN_3;
			case _I(G,R,E,E,N, ,3):
				return alpha | X11_GREEN_3;
			case _I(G,R,E,E,N,4):
				return alpha | X11_GREEN_4;
			case _I(G,R,E,E,N,_,4):
				return alpha | X11_GREEN_4;
			case _I(G,R,E,E,N, ,4):
				return alpha | X11_GREEN_4;
			case _I(C,H,A,R,T,R,E,U,S,E,1):
				return alpha | X11_CHARTREUSE_1;
			case _I(C,H,A,R,T,R,E,U,S,E,_,1):
				return alpha | X11_CHARTREUSE_1;
			case _I(C,H,A,R,T,R,E,U,S,E, ,1):
				return alpha | X11_CHARTREUSE_1;
			case _I(C,H,A,R,T,R,E,U,S,E,2):
				return alpha | X11_CHARTREUSE_2;
			case _I(C,H,A,R,T,R,E,U,S,E,_,2):
				return alpha | X11_CHARTREUSE_2;
			case _I(C,H,A,R,T,R,E,U,S,E, ,2):
				return alpha | X11_CHARTREUSE_2;
			case _I(C,H,A,R,T,R,E,U,S,E,3):
				return alpha | X11_CHARTREUSE_3;
			case _I(C,H,A,R,T,R,E,U,S,E,_,3):
				return alpha | X11_CHARTREUSE_3;
			case _I(C,H,A,R,T,R,E,U,S,E, ,3):
				return alpha | X11_CHARTREUSE_3;
			case _I(C,H,A,R,T,R,E,U,S,E,4):
				return alpha | X11_CHARTREUSE_4;
			case _I(C,H,A,R,T,R,E,U,S,E,_,4):
				return alpha | X11_CHARTREUSE_4;
			case _I(C,H,A,R,T,R,E,U,S,E, ,4):
				return alpha | X11_CHARTREUSE_4;
			case _I(O,L,I,V,E,D,R,A,B,1):
				return alpha | X11_OLIVE_DRAB_1;
			case _I(O,L,I,V,E,_,D,R,A,B,_,1):
				return alpha | X11_OLIVE_DRAB_1;
			case _I(O,L,I,V,E, ,D,R,A,B, ,1):
				return alpha | X11_OLIVE_DRAB_1;
			case _I(O,L,I,V,E,D,R,A,B,2):
				return alpha | X11_OLIVE_DRAB_2;
			case _I(O,L,I,V,E,_,D,R,A,B,_,2):
				return alpha | X11_OLIVE_DRAB_2;
			case _I(O,L,I,V,E, ,D,R,A,B, ,2):
				return alpha | X11_OLIVE_DRAB_2;
			case _I(O,L,I,V,E,D,R,A,B,3):
				return alpha | X11_OLIVE_DRAB_3;
			case _I(O,L,I,V,E,_,D,R,A,B,_,3):
				return alpha | X11_OLIVE_DRAB_3;
			case _I(O,L,I,V,E, ,D,R,A,B, ,3):
				return alpha | X11_OLIVE_DRAB_3;
			case _I(O,L,I,V,E,D,R,A,B,4):
				return alpha | X11_OLIVE_DRAB_4;
			case _I(O,L,I,V,E,_,D,R,A,B,_,4):
				return alpha | X11_OLIVE_DRAB_4;
			case _I(O,L,I,V,E, ,D,R,A,B, ,4):
				return alpha | X11_OLIVE_DRAB_4;
			case _I(D,A,R,K,O,L,I,V,E,G,R,E,E,N,1):
				return alpha | X11_DARK_OLIVE_GREEN_1;
			case _I(D,A,R,K,_,O,L,I,V,E,_,G,R,E,E,N,_,1):
				return alpha | X11_DARK_OLIVE_GREEN_1;
			case _I(D,A,R,K, ,O,L,I,V,E, ,G,R,E,E,N, ,1):
				return alpha | X11_DARK_OLIVE_GREEN_1;
			case _I(D,A,R,K,O,L,I,V,E,G,R,E,E,N,2):
				return alpha | X11_DARK_OLIVE_GREEN_2;
			case _I(D,A,R,K,_,O,L,I,V,E,_,G,R,E,E,N,_,2):
				return alpha | X11_DARK_OLIVE_GREEN_2;
			case _I(D,A,R,K, ,O,L,I,V,E, ,G,R,E,E,N, ,2):
				return alpha | X11_DARK_OLIVE_GREEN_2;
			case _I(D,A,R,K,O,L,I,V,E,G,R,E,E,N,3):
				return alpha | X11_DARK_OLIVE_GREEN_3;
			case _I(D,A,R,K,_,O,L,I,V,E,_,G,R,E,E,N,_,3):
				return alpha | X11_DARK_OLIVE_GREEN_3;
			case _I(D,A,R,K, ,O,L,I,V,E, ,G,R,E,E,N, ,3):
				return alpha | X11_DARK_OLIVE_GREEN_3;
			case _I(D,A,R,K,O,L,I,V,E,G,R,E,E,N,4):
				return alpha | X11_DARK_OLIVE_GREEN_4;
			case _I(D,A,R,K,_,O,L,I,V,E,_,G,R,E,E,N,_,4):
				return alpha | X11_DARK_OLIVE_GREEN_4;
			case _I(D,A,R,K, ,O,L,I,V,E, ,G,R,E,E,N, ,4):
				return alpha | X11_DARK_OLIVE_GREEN_4;
			case _I(K,H,A,K,I,1):
				return alpha | X11_KHAKI_1;
			case _I(K,H,A,K,I,_,1):
				return alpha | X11_KHAKI_1;
			case _I(K,H,A,K,I, ,1):
				return alpha | X11_KHAKI_1;
			case _I(K,H,A,K,I,2):
				return alpha | X11_KHAKI_2;
			case _I(K,H,A,K,I,_,2):
				return alpha | X11_KHAKI_2;
			case _I(K,H,A,K,I, ,2):
				return alpha | X11_KHAKI_2;
			case _I(K,H,A,K,I,3):
				return alpha | X11_KHAKI_3;
			case _I(K,H,A,K,I,_,3):
				return alpha | X11_KHAKI_3;
			case _I(K,H,A,K,I, ,3):
				return alpha | X11_KHAKI_3;
			case _I(K,H,A,K,I,4):
				return alpha | X11_KHAKI_4;
			case _I(K,H,A,K,I,_,4):
				return alpha | X11_KHAKI_4;
			case _I(K,H,A,K,I, ,4):
				return alpha | X11_KHAKI_4;
			case _I(L,I,G,H,T,G,O,L,D,E,N,R,O,D,1):
				return alpha | X11_LIGHT_GOLDENROD_1;
			case _I(L,I,G,H,T,_,G,O,L,D,E,N,R,O,D,_,1):
				return alpha | X11_LIGHT_GOLDENROD_1;
			case _I(L,I,G,H,T, ,G,O,L,D,E,N,R,O,D, ,1):
				return alpha | X11_LIGHT_GOLDENROD_1;
			case _I(L,I,G,H,T,G,O,L,D,E,N,R,O,D,2):
				return alpha | X11_LIGHT_GOLDENROD_2;
			case _I(L,I,G,H,T,_,G,O,L,D,E,N,R,O,D,_,2):
				return alpha | X11_LIGHT_GOLDENROD_2;
			case _I(L,I,G,H,T, ,G,O,L,D,E,N,R,O,D, ,2):
				return alpha | X11_LIGHT_GOLDENROD_2;
			case _I(L,I,G,H,T,G,O,L,D,E,N,R,O,D,3):
				return alpha | X11_LIGHT_GOLDENROD_3;
			case _I(L,I,G,H,T,_,G,O,L,D,E,N,R,O,D,_,3):
				return alpha | X11_LIGHT_GOLDENROD_3;
			case _I(L,I,G,H,T, ,G,O,L,D,E,N,R,O,D, ,3):
				return alpha | X11_LIGHT_GOLDENROD_3;
			case _I(L,I,G,H,T,G,O,L,D,E,N,R,O,D,4):
				return alpha | X11_LIGHT_GOLDENROD_4;
			case _I(L,I,G,H,T,_,G,O,L,D,E,N,R,O,D,_,4):
				return alpha | X11_LIGHT_GOLDENROD_4;
			case _I(L,I,G,H,T, ,G,O,L,D,E,N,R,O,D, ,4):
				return alpha | X11_LIGHT_GOLDENROD_4;
			case _I(L,I,G,H,T,Y,E,L,L,O,W,1):
				return alpha | X11_LIGHT_YELLOW_1;
			case _I(L,I,G,H,T,_,Y,E,L,L,O,W,_,1):
				return alpha | X11_LIGHT_YELLOW_1;
			case _I(L,I,G,H,T, ,Y,E,L,L,O,W, ,1):
				return alpha | X11_LIGHT_YELLOW_1;
			case _I(L,I,G,H,T,Y,E,L,L,O,W,2):
				return alpha | X11_LIGHT_YELLOW_2;
			case _I(L,I,G,H,T,_,Y,E,L,L,O,W,_,2):
				return alpha | X11_LIGHT_YELLOW_2;
			case _I(L,I,G,H,T, ,Y,E,L,L,O,W, ,2):
				return alpha | X11_LIGHT_YELLOW_2;
			case _I(L,I,G,H,T,Y,E,L,L,O,W,3):
				return alpha | X11_LIGHT_YELLOW_3;
			case _I(L,I,G,H,T,_,Y,E,L,L,O,W,_,3):
				return alpha | X11_LIGHT_YELLOW_3;
			case _I(L,I,G,H,T, ,Y,E,L,L,O,W, ,3):
				return alpha | X11_LIGHT_YELLOW_3;
			case _I(L,I,G,H,T,Y,E,L,L,O,W,4):
				return alpha | X11_LIGHT_YELLOW_4;
			case _I(L,I,G,H,T,_,Y,E,L,L,O,W,_,4):
				return alpha | X11_LIGHT_YELLOW_4;
			case _I(L,I,G,H,T, ,Y,E,L,L,O,W, ,4):
				return alpha | X11_LIGHT_YELLOW_4;
			case _I(Y,E,L,L,O,W,1):
				return alpha | X11_YELLOW_1;
			case _I(Y,E,L,L,O,W,_,1):
				return alpha | X11_YELLOW_1;
			case _I(Y,E,L,L,O,W, ,1):
				return alpha | X11_YELLOW_1;
			case _I(Y,E,L,L,O,W,2):
				return alpha | X11_YELLOW_2;
			case _I(Y,E,L,L,O,W,_,2):
				return alpha | X11_YELLOW_2;
			case _I(Y,E,L,L,O,W, ,2):
				return alpha | X11_YELLOW_2;
			case _I(Y,E,L,L,O,W,3):
				return alpha | X11_YELLOW_3;
			case _I(Y,E,L,L,O,W,_,3):
				return alpha | X11_YELLOW_3;
			case _I(Y,E,L,L,O,W, ,3):
				return alpha | X11_YELLOW_3;
			case _I(Y,E,L,L,O,W,4):
				return alpha | X11_YELLOW_4;
			case _I(Y,E,L,L,O,W,_,4):
				return alpha | X11_YELLOW_4;
			case _I(Y,E,L,L,O,W, ,4):
				return alpha | X11_YELLOW_4;
			case _I(G,O,L,D,1):
				return alpha | X11_GOLD_1;
			case _I(G,O,L,D,_,1):
				return alpha | X11_GOLD_1;
			case _I(G,O,L,D, ,1):
				return alpha | X11_GOLD_1;
			case _I(G,O,L,D,2):
				return alpha | X11_GOLD_2;
			case _I(G,O,L,D,_,2):
				return alpha | X11_GOLD_2;
			case _I(G,O,L,D, ,2):
				return alpha | X11_GOLD_2;
			case _I(G,O,L,D,3):
				return alpha | X11_GOLD_3;
			case _I(G,O,L,D,_,3):
				return alpha | X11_GOLD_3;
			case _I(G,O,L,D, ,3):
				return alpha | X11_GOLD_3;
			case _I(G,O,L,D,4):
				return alpha | X11_GOLD_4;
			case _I(G,O,L,D,_,4):
				return alpha | X11_GOLD_4;
			case _I(G,O,L,D, ,4):
				return alpha | X11_GOLD_4;
			case _I(G,O,L,D,E,N,R,O,D,1):
				return alpha | X11_GOLDENROD_1;
			case _I(G,O,L,D,E,N,R,O,D,_,1):
				return alpha | X11_GOLDENROD_1;
			case _I(G,O,L,D,E,N,R,O,D, ,1):
				return alpha | X11_GOLDENROD_1;
			case _I(G,O,L,D,E,N,R,O,D,2):
				return alpha | X11_GOLDENROD_2;
			case _I(G,O,L,D,E,N,R,O,D,_,2):
				return alpha | X11_GOLDENROD_2;
			case _I(G,O,L,D,E,N,R,O,D, ,2):
				return alpha | X11_GOLDENROD_2;
			case _I(G,O,L,D,E,N,R,O,D,3):
				return alpha | X11_GOLDENROD_3;
			case _I(G,O,L,D,E,N,R,O,D,_,3):
				return alpha | X11_GOLDENROD_3;
			case _I(G,O,L,D,E,N,R,O,D, ,3):
				return alpha | X11_GOLDENROD_3;
			case _I(G,O,L,D,E,N,R,O,D,4):
				return alpha | X11_GOLDENROD_4;
			case _I(G,O,L,D,E,N,R,O,D,_,4):
				return alpha | X11_GOLDENROD_4;
			case _I(G,O,L,D,E,N,R,O,D, ,4):
				return alpha | X11_GOLDENROD_4;
			case _I(D,A,R,K,G,O,L,D,E,N,R,O,D,1):
				return alpha | X11_DARK_GOLDENROD_1;
			case _I(D,A,R,K,_,G,O,L,D,E,N,R,O,D,_,1):
				return alpha | X11_DARK_GOLDENROD_1;
			case _I(D,A,R,K, ,G,O,L,D,E,N,R,O,D, ,1):
				return alpha | X11_DARK_GOLDENROD_1;
			case _I(D,A,R,K,G,O,L,D,E,N,R,O,D,2):
				return alpha | X11_DARK_GOLDENROD_2;
			case _I(D,A,R,K,_,G,O,L,D,E,N,R,O,D,_,2):
				return alpha | X11_DARK_GOLDENROD_2;
			case _I(D,A,R,K, ,G,O,L,D,E,N,R,O,D, ,2):
				return alpha | X11_DARK_GOLDENROD_2;
			case _I(D,A,R,K,G,O,L,D,E,N,R,O,D,3):
				return alpha | X11_DARK_GOLDENROD_3;
			case _I(D,A,R,K,_,G,O,L,D,E,N,R,O,D,_,3):
				return alpha | X11_DARK_GOLDENROD_3;
			case _I(D,A,R,K, ,G,O,L,D,E,N,R,O,D, ,3):
				return alpha | X11_DARK_GOLDENROD_3;
			case _I(D,A,R,K,G,O,L,D,E,N,R,O,D,4):
				return alpha | X11_DARK_GOLDENROD_4;
			case _I(D,A,R,K,_,G,O,L,D,E,N,R,O,D,_,4):
				return alpha | X11_DARK_GOLDENROD_4;
			case _I(D,A,R,K, ,G,O,L,D,E,N,R,O,D, ,4):
				return alpha | X11_DARK_GOLDENROD_4;
			case _I(R,O,S,Y,B,R,O,W,N,1):
				return alpha | X11_ROSY_BROWN_1;
			case _I(R,O,S,Y,_,B,R,O,W,N,_,1):
				return alpha | X11_ROSY_BROWN_1;
			case _I(R,O,S,Y, ,B,R,O,W,N, ,1):
				return alpha | X11_ROSY_BROWN_1;
			case _I(R,O,S,Y,B,R,O,W,N,2):
				return alpha | X11_ROSY_BROWN_2;
			case _I(R,O,S,Y,_,B,R,O,W,N,_,2):
				return alpha | X11_ROSY_BROWN_2;
			case _I(R,O,S,Y, ,B,R,O,W,N, ,2):
				return alpha | X11_ROSY_BROWN_2;
			case _I(R,O,S,Y,B,R,O,W,N,3):
				return alpha | X11_ROSY_BROWN_3;
			case _I(R,O,S,Y,_,B,R,O,W,N,_,3):
				return alpha | X11_ROSY_BROWN_3;
			case _I(R,O,S,Y, ,B,R,O,W,N, ,3):
				return alpha | X11_ROSY_BROWN_3;
			case _I(R,O,S,Y,B,R,O,W,N,4):
				return alpha | X11_ROSY_BROWN_4;
			case _I(R,O,S,Y,_,B,R,O,W,N,_,4):
				return alpha | X11_ROSY_BROWN_4;
			case _I(R,O,S,Y, ,B,R,O,W,N, ,4):
				return alpha | X11_ROSY_BROWN_4;
			case _I(I,N,D,I,A,N,R,E,D,1):
				return alpha | X11_INDIAN_RED_1;
			case _I(I,N,D,I,A,N,_,R,E,D,_,1):
				return alpha | X11_INDIAN_RED_1;
			case _I(I,N,D,I,A,N, ,R,E,D, ,1):
				return alpha | X11_INDIAN_RED_1;
			case _I(I,N,D,I,A,N,R,E,D,2):
				return alpha | X11_INDIAN_RED_2;
			case _I(I,N,D,I,A,N,_,R,E,D,_,2):
				return alpha | X11_INDIAN_RED_2;
			case _I(I,N,D,I,A,N, ,R,E,D, ,2):
				return alpha | X11_INDIAN_RED_2;
			case _I(I,N,D,I,A,N,R,E,D,3):
				return alpha | X11_INDIAN_RED_3;
			case _I(I,N,D,I,A,N,_,R,E,D,_,3):
				return alpha | X11_INDIAN_RED_3;
			case _I(I,N,D,I,A,N, ,R,E,D, ,3):
				return alpha | X11_INDIAN_RED_3;
			case _I(I,N,D,I,A,N,R,E,D,4):
				return alpha | X11_INDIAN_RED_4;
			case _I(I,N,D,I,A,N,_,R,E,D,_,4):
				return alpha | X11_INDIAN_RED_4;
			case _I(I,N,D,I,A,N, ,R,E,D, ,4):
				return alpha | X11_INDIAN_RED_4;
			case _I(S,I,E,N,N,A,1):
				return alpha | X11_SIENNA_1;
			case _I(S,I,E,N,N,A,_,1):
				return alpha | X11_SIENNA_1;
			case _I(S,I,E,N,N,A, ,1):
				return alpha | X11_SIENNA_1;
			case _I(S,I,E,N,N,A,2):
				return alpha | X11_SIENNA_2;
			case _I(S,I,E,N,N,A,_,2):
				return alpha | X11_SIENNA_2;
			case _I(S,I,E,N,N,A, ,2):
				return alpha | X11_SIENNA_2;
			case _I(S,I,E,N,N,A,3):
				return alpha | X11_SIENNA_3;
			case _I(S,I,E,N,N,A,_,3):
				return alpha | X11_SIENNA_3;
			case _I(S,I,E,N,N,A, ,3):
				return alpha | X11_SIENNA_3;
			case _I(S,I,E,N,N,A,4):
				return alpha | X11_SIENNA_4;
			case _I(S,I,E,N,N,A,_,4):
				return alpha | X11_SIENNA_4;
			case _I(S,I,E,N,N,A, ,4):
				return alpha | X11_SIENNA_4;
			case _I(B,U,R,L,Y,W,O,O,D,1):
				return alpha | X11_BURLYWOOD_1;
			case _I(B,U,R,L,Y,W,O,O,D,_,1):
				return alpha | X11_BURLYWOOD_1;
			case _I(B,U,R,L,Y,W,O,O,D, ,1):
				return alpha | X11_BURLYWOOD_1;
			case _I(B,U,R,L,Y,W,O,O,D,2):
				return alpha | X11_BURLYWOOD_2;
			case _I(B,U,R,L,Y,W,O,O,D,_,2):
				return alpha | X11_BURLYWOOD_2;
			case _I(B,U,R,L,Y,W,O,O,D, ,2):
				return alpha | X11_BURLYWOOD_2;
			case _I(B,U,R,L,Y,W,O,O,D,3):
				return alpha | X11_BURLYWOOD_3;
			case _I(B,U,R,L,Y,W,O,O,D,_,3):
				return alpha | X11_BURLYWOOD_3;
			case _I(B,U,R,L,Y,W,O,O,D, ,3):
				return alpha | X11_BURLYWOOD_3;
			case _I(B,U,R,L,Y,W,O,O,D,4):
				return alpha | X11_BURLYWOOD_4;
			case _I(B,U,R,L,Y,W,O,O,D,_,4):
				return alpha | X11_BURLYWOOD_4;
			case _I(B,U,R,L,Y,W,O,O,D, ,4):
				return alpha | X11_BURLYWOOD_4;
			case _I(W,H,E,A,T,1):
				return alpha | X11_WHEAT_1;
			case _I(W,H,E,A,T,_,1):
				return alpha | X11_WHEAT_1;
			case _I(W,H,E,A,T, ,1):
				return alpha | X11_WHEAT_1;
			case _I(W,H,E,A,T,2):
				return alpha | X11_WHEAT_2;
			case _I(W,H,E,A,T,_,2):
				return alpha | X11_WHEAT_2;
			case _I(W,H,E,A,T, ,2):
				return alpha | X11_WHEAT_2;
			case _I(W,H,E,A,T,3):
				return alpha | X11_WHEAT_3;
			case _I(W,H,E,A,T,_,3):
				return alpha | X11_WHEAT_3;
			case _I(W,H,E,A,T, ,3):
				return alpha | X11_WHEAT_3;
			case _I(W,H,E,A,T,4):
				return alpha | X11_WHEAT_4;
			case _I(W,H,E,A,T,_,4):
				return alpha | X11_WHEAT_4;
			case _I(W,H,E,A,T, ,4):
				return alpha | X11_WHEAT_4;
			case _I(T,A,N,1):
				return alpha | X11_TAN_1;
			case _I(T,A,N,_,1):
				return alpha | X11_TAN_1;
			case _I(T,A,N, ,1):
				return alpha | X11_TAN_1;
			case _I(T,A,N,2):
				return alpha | X11_TAN_2;
			case _I(T,A,N,_,2):
				return alpha | X11_TAN_2;
			case _I(T,A,N, ,2):
				return alpha | X11_TAN_2;
			case _I(T,A,N,3):
				return alpha | X11_TAN_3;
			case _I(T,A,N,_,3):
				return alpha | X11_TAN_3;
			case _I(T,A,N, ,3):
				return alpha | X11_TAN_3;
			case _I(T,A,N,4):
				return alpha | X11_TAN_4;
			case _I(T,A,N,_,4):
				return alpha | X11_TAN_4;
			case _I(T,A,N, ,4):
				return alpha | X11_TAN_4;
			case _I(C,H,O,C,O,L,A,T,E,1):
				return alpha | X11_CHOCOLATE_1;
			case _I(C,H,O,C,O,L,A,T,E,_,1):
				return alpha | X11_CHOCOLATE_1;
			case _I(C,H,O,C,O,L,A,T,E, ,1):
				return alpha | X11_CHOCOLATE_1;
			case _I(C,H,O,C,O,L,A,T,E,2):
				return alpha | X11_CHOCOLATE_2;
			case _I(C,H,O,C,O,L,A,T,E,_,2):
				return alpha | X11_CHOCOLATE_2;
			case _I(C,H,O,C,O,L,A,T,E, ,2):
				return alpha | X11_CHOCOLATE_2;
			case _I(C,H,O,C,O,L,A,T,E,3):
				return alpha | X11_CHOCOLATE_3;
			case _I(C,H,O,C,O,L,A,T,E,_,3):
				return alpha | X11_CHOCOLATE_3;
			case _I(C,H,O,C,O,L,A,T,E, ,3):
				return alpha | X11_CHOCOLATE_3;
			case _I(C,H,O,C,O,L,A,T,E,4):
				return alpha | X11_CHOCOLATE_4;
			case _I(C,H,O,C,O,L,A,T,E,_,4):
				return alpha | X11_CHOCOLATE_4;
			case _I(C,H,O,C,O,L,A,T,E, ,4):
				return alpha | X11_CHOCOLATE_4;
			case _I(F,I,R,E,B,R,I,C,K,1):
				return alpha | X11_FIREBRICK_1;
			case _I(F,I,R,E,B,R,I,C,K,_,1):
				return alpha | X11_FIREBRICK_1;
			case _I(F,I,R,E,B,R,I,C,K, ,1):
				return alpha | X11_FIREBRICK_1;
			case _I(F,I,R,E,B,R,I,C,K,2):
				return alpha | X11_FIREBRICK_2;
			case _I(F,I,R,E,B,R,I,C,K,_,2):
				return alpha | X11_FIREBRICK_2;
			case _I(F,I,R,E,B,R,I,C,K, ,2):
				return alpha | X11_FIREBRICK_2;
			case _I(F,I,R,E,B,R,I,C,K,3):
				return alpha | X11_FIREBRICK_3;
			case _I(F,I,R,E,B,R,I,C,K,_,3):
				return alpha | X11_FIREBRICK_3;
			case _I(F,I,R,E,B,R,I,C,K, ,3):
				return alpha | X11_FIREBRICK_3;
			case _I(F,I,R,E,B,R,I,C,K,4):
				return alpha | X11_FIREBRICK_4;
			case _I(F,I,R,E,B,R,I,C,K,_,4):
				return alpha | X11_FIREBRICK_4;
			case _I(F,I,R,E,B,R,I,C,K, ,4):
				return alpha | X11_FIREBRICK_4;
			case _I(B,R,O,W,N,1):
				return alpha | X11_BROWN_1;
			case _I(B,R,O,W,N,_,1):
				return alpha | X11_BROWN_1;
			case _I(B,R,O,W,N, ,1):
				return alpha | X11_BROWN_1;
			case _I(B,R,O,W,N,2):
				return alpha | X11_BROWN_2;
			case _I(B,R,O,W,N,_,2):
				return alpha | X11_BROWN_2;
			case _I(B,R,O,W,N, ,2):
				return alpha | X11_BROWN_2;
			case _I(B,R,O,W,N,3):
				return alpha | X11_BROWN_3;
			case _I(B,R,O,W,N,_,3):
				return alpha | X11_BROWN_3;
			case _I(B,R,O,W,N, ,3):
				return alpha | X11_BROWN_3;
			case _I(B,R,O,W,N,4):
				return alpha | X11_BROWN_4;
			case _I(B,R,O,W,N,_,4):
				return alpha | X11_BROWN_4;
			case _I(B,R,O,W,N, ,4):
				return alpha | X11_BROWN_4;
			case _I(S,A,L,M,O,N,1):
				return alpha | X11_SALMON_1;
			case _I(S,A,L,M,O,N,_,1):
				return alpha | X11_SALMON_1;
			case _I(S,A,L,M,O,N, ,1):
				return alpha | X11_SALMON_1;
			case _I(S,A,L,M,O,N,2):
				return alpha | X11_SALMON_2;
			case _I(S,A,L,M,O,N,_,2):
				return alpha | X11_SALMON_2;
			case _I(S,A,L,M,O,N, ,2):
				return alpha | X11_SALMON_2;
			case _I(S,A,L,M,O,N,3):
				return alpha | X11_SALMON_3;
			case _I(S,A,L,M,O,N,_,3):
				return alpha | X11_SALMON_3;
			case _I(S,A,L,M,O,N, ,3):
				return alpha | X11_SALMON_3;
			case _I(S,A,L,M,O,N,4):
				return alpha | X11_SALMON_4;
			case _I(S,A,L,M,O,N,_,4):
				return alpha | X11_SALMON_4;
			case _I(S,A,L,M,O,N, ,4):
				return alpha | X11_SALMON_4;
			case _I(L,I,G,H,T,S,A,L,M,O,N,1):
				return alpha | X11_LIGHT_SALMON_1;
			case _I(L,I,G,H,T,_,S,A,L,M,O,N,_,1):
				return alpha | X11_LIGHT_SALMON_1;
			case _I(L,I,G,H,T, ,S,A,L,M,O,N, ,1):
				return alpha | X11_LIGHT_SALMON_1;
			case _I(L,I,G,H,T,S,A,L,M,O,N,2):
				return alpha | X11_LIGHT_SALMON_2;
			case _I(L,I,G,H,T,_,S,A,L,M,O,N,_,2):
				return alpha | X11_LIGHT_SALMON_2;
			case _I(L,I,G,H,T, ,S,A,L,M,O,N, ,2):
				return alpha | X11_LIGHT_SALMON_2;
			case _I(L,I,G,H,T,S,A,L,M,O,N,3):
				return alpha | X11_LIGHT_SALMON_3;
			case _I(L,I,G,H,T,_,S,A,L,M,O,N,_,3):
				return alpha | X11_LIGHT_SALMON_3;
			case _I(L,I,G,H,T, ,S,A,L,M,O,N, ,3):
				return alpha | X11_LIGHT_SALMON_3;
			case _I(L,I,G,H,T,S,A,L,M,O,N,4):
				return alpha | X11_LIGHT_SALMON_4;
			case _I(L,I,G,H,T,_,S,A,L,M,O,N,_,4):
				return alpha | X11_LIGHT_SALMON_4;
			case _I(L,I,G,H,T, ,S,A,L,M,O,N, ,4):
				return alpha | X11_LIGHT_SALMON_4;
			case _I(O,R,A,N,G,E,1):
				return alpha | X11_ORANGE_1;
			case _I(O,R,A,N,G,E,_,1):
				return alpha | X11_ORANGE_1;
			case _I(O,R,A,N,G,E, ,1):
				return alpha | X11_ORANGE_1;
			case _I(O,R,A,N,G,E,2):
				return alpha | X11_ORANGE_2;
			case _I(O,R,A,N,G,E,_,2):
				return alpha | X11_ORANGE_2;
			case _I(O,R,A,N,G,E, ,2):
				return alpha | X11_ORANGE_2;
			case _I(O,R,A,N,G,E,3):
				return alpha | X11_ORANGE_3;
			case _I(O,R,A,N,G,E,_,3):
				return alpha | X11_ORANGE_3;
			case _I(O,R,A,N,G,E, ,3):
				return alpha | X11_ORANGE_3;
			case _I(O,R,A,N,G,E,4):
				return alpha | X11_ORANGE_4;
			case _I(O,R,A,N,G,E,_,4):
				return alpha | X11_ORANGE_4;
			case _I(O,R,A,N,G,E, ,4):
				return alpha | X11_ORANGE_4;
			case _I(D,A,R,K,O,R,A,N,G,E,1):
				return alpha | X11_DARK_ORANGE_1;
			case _I(D,A,R,K,_,O,R,A,N,G,E,_,1):
				return alpha | X11_DARK_ORANGE_1;
			case _I(D,A,R,K, ,O,R,A,N,G,E, ,1):
				return alpha | X11_DARK_ORANGE_1;
			case _I(D,A,R,K,O,R,A,N,G,E,2):
				return alpha | X11_DARK_ORANGE_2;
			case _I(D,A,R,K,_,O,R,A,N,G,E,_,2):
				return alpha | X11_DARK_ORANGE_2;
			case _I(D,A,R,K, ,O,R,A,N,G,E, ,2):
				return alpha | X11_DARK_ORANGE_2;
			case _I(D,A,R,K,O,R,A,N,G,E,3):
				return alpha | X11_DARK_ORANGE_3;
			case _I(D,A,R,K,_,O,R,A,N,G,E,_,3):
				return alpha | X11_DARK_ORANGE_3;
			case _I(D,A,R,K, ,O,R,A,N,G,E, ,3):
				return alpha | X11_DARK_ORANGE_3;
			case _I(D,A,R,K,O,R,A,N,G,E,4):
				return alpha | X11_DARK_ORANGE_4;
			case _I(D,A,R,K,_,O,R,A,N,G,E,_,4):
				return alpha | X11_DARK_ORANGE_4;
			case _I(D,A,R,K, ,O,R,A,N,G,E, ,4):
				return alpha | X11_DARK_ORANGE_4;
			case _I(C,O,R,A,L,1):
				return alpha | X11_CORAL_1;
			case _I(C,O,R,A,L,_,1):
				return alpha | X11_CORAL_1;
			case _I(C,O,R,A,L, ,1):
				return alpha | X11_CORAL_1;
			case _I(C,O,R,A,L,2):
				return alpha | X11_CORAL_2;
			case _I(C,O,R,A,L,_,2):
				return alpha | X11_CORAL_2;
			case _I(C,O,R,A,L, ,2):
				return alpha | X11_CORAL_2;
			case _I(C,O,R,A,L,3):
				return alpha | X11_CORAL_3;
			case _I(C,O,R,A,L,_,3):
				return alpha | X11_CORAL_3;
			case _I(C,O,R,A,L, ,3):
				return alpha | X11_CORAL_3;
			case _I(C,O,R,A,L,4):
				return alpha | X11_CORAL_4;
			case _I(C,O,R,A,L,_,4):
				return alpha | X11_CORAL_4;
			case _I(C,O,R,A,L, ,4):
				return alpha | X11_CORAL_4;
			case _I(T,O,M,A,T,O,1):
				return alpha | X11_TOMATO_1;
			case _I(T,O,M,A,T,O,_,1):
				return alpha | X11_TOMATO_1;
			case _I(T,O,M,A,T,O, ,1):
				return alpha | X11_TOMATO_1;
			case _I(T,O,M,A,T,O,2):
				return alpha | X11_TOMATO_2;
			case _I(T,O,M,A,T,O,_,2):
				return alpha | X11_TOMATO_2;
			case _I(T,O,M,A,T,O, ,2):
				return alpha | X11_TOMATO_2;
			case _I(T,O,M,A,T,O,3):
				return alpha | X11_TOMATO_3;
			case _I(T,O,M,A,T,O,_,3):
				return alpha | X11_TOMATO_3;
			case _I(T,O,M,A,T,O, ,3):
				return alpha | X11_TOMATO_3;
			case _I(T,O,M,A,T,O,4):
				return alpha | X11_TOMATO_4;
			case _I(T,O,M,A,T,O,_,4):
				return alpha | X11_TOMATO_4;
			case _I(T,O,M,A,T,O, ,4):
				return alpha | X11_TOMATO_4;
			case _I(O,R,A,N,G,E,R,E,D,1):
				return alpha | X11_ORANGE_RED_1;
			case _I(O,R,A,N,G,E,_,R,E,D,_,1):
				return alpha | X11_ORANGE_RED_1;
			case _I(O,R,A,N,G,E, ,R,E,D, ,1):
				return alpha | X11_ORANGE_RED_1;
			case _I(O,R,A,N,G,E,R,E,D,2):
				return alpha | X11_ORANGE_RED_2;
			case _I(O,R,A,N,G,E,_,R,E,D,_,2):
				return alpha | X11_ORANGE_RED_2;
			case _I(O,R,A,N,G,E, ,R,E,D, ,2):
				return alpha | X11_ORANGE_RED_2;
			case _I(O,R,A,N,G,E,R,E,D,3):
				return alpha | X11_ORANGE_RED_3;
			case _I(O,R,A,N,G,E,_,R,E,D,_,3):
				return alpha | X11_ORANGE_RED_3;
			case _I(O,R,A,N,G,E, ,R,E,D, ,3):
				return alpha | X11_ORANGE_RED_3;
			case _I(O,R,A,N,G,E,R,E,D,4):
				return alpha | X11_ORANGE_RED_4;
			case _I(O,R,A,N,G,E,_,R,E,D,_,4):
				return alpha | X11_ORANGE_RED_4;
			case _I(O,R,A,N,G,E, ,R,E,D, ,4):
				return alpha | X11_ORANGE_RED_4;
			case _I(R,E,D,1):
				return alpha | X11_RED_1;
			case _I(R,E,D,_,1):
				return alpha | X11_RED_1;
			case _I(R,E,D, ,1):
				return alpha | X11_RED_1;
			case _I(R,E,D,2):
				return alpha | X11_RED_2;
			case _I(R,E,D,_,2):
				return alpha | X11_RED_2;
			case _I(R,E,D, ,2):
				return alpha | X11_RED_2;
			case _I(R,E,D,3):
				return alpha | X11_RED_3;
			case _I(R,E,D,_,3):
				return alpha | X11_RED_3;
			case _I(R,E,D, ,3):
				return alpha | X11_RED_3;
			case _I(R,E,D,4):
				return alpha | X11_RED_4;
			case _I(R,E,D,_,4):
				return alpha | X11_RED_4;
			case _I(R,E,D, ,4):
				return alpha | X11_RED_4;
			case _I(D,E,E,P,P,I,N,K,1):
				return alpha | X11_DEEP_PINK_1;
			case _I(D,E,E,P,_,P,I,N,K,_,1):
				return alpha | X11_DEEP_PINK_1;
			case _I(D,E,E,P, ,P,I,N,K, ,1):
				return alpha | X11_DEEP_PINK_1;
			case _I(D,E,E,P,P,I,N,K,2):
				return alpha | X11_DEEP_PINK_2;
			case _I(D,E,E,P,_,P,I,N,K,_,2):
				return alpha | X11_DEEP_PINK_2;
			case _I(D,E,E,P, ,P,I,N,K, ,2):
				return alpha | X11_DEEP_PINK_2;
			case _I(D,E,E,P,P,I,N,K,3):
				return alpha | X11_DEEP_PINK_3;
			case _I(D,E,E,P,_,P,I,N,K,_,3):
				return alpha | X11_DEEP_PINK_3;
			case _I(D,E,E,P, ,P,I,N,K, ,3):
				return alpha | X11_DEEP_PINK_3;
			case _I(D,E,E,P,P,I,N,K,4):
				return alpha | X11_DEEP_PINK_4;
			case _I(D,E,E,P,_,P,I,N,K,_,4):
				return alpha | X11_DEEP_PINK_4;
			case _I(D,E,E,P, ,P,I,N,K, ,4):
				return alpha | X11_DEEP_PINK_4;
			case _I(H,O,T,P,I,N,K,1):
				return alpha | X11_HOT_PINK_1;
			case _I(H,O,T,_,P,I,N,K,_,1):
				return alpha | X11_HOT_PINK_1;
			case _I(H,O,T, ,P,I,N,K, ,1):
				return alpha | X11_HOT_PINK_1;
			case _I(H,O,T,P,I,N,K,2):
				return alpha | X11_HOT_PINK_2;
			case _I(H,O,T,_,P,I,N,K,_,2):
				return alpha | X11_HOT_PINK_2;
			case _I(H,O,T, ,P,I,N,K, ,2):
				return alpha | X11_HOT_PINK_2;
			case _I(H,O,T,P,I,N,K,3):
				return alpha | X11_HOT_PINK_3;
			case _I(H,O,T,_,P,I,N,K,_,3):
				return alpha | X11_HOT_PINK_3;
			case _I(H,O,T, ,P,I,N,K, ,3):
				return alpha | X11_HOT_PINK_3;
			case _I(H,O,T,P,I,N,K,4):
				return alpha | X11_HOT_PINK_4;
			case _I(H,O,T,_,P,I,N,K,_,4):
				return alpha | X11_HOT_PINK_4;
			case _I(H,O,T, ,P,I,N,K, ,4):
				return alpha | X11_HOT_PINK_4;
			case _I(P,I,N,K,1):
				return alpha | X11_PINK_1;
			case _I(P,I,N,K,_,1):
				return alpha | X11_PINK_1;
			case _I(P,I,N,K, ,1):
				return alpha | X11_PINK_1;
			case _I(P,I,N,K,2):
				return alpha | X11_PINK_2;
			case _I(P,I,N,K,_,2):
				return alpha | X11_PINK_2;
			case _I(P,I,N,K, ,2):
				return alpha | X11_PINK_2;
			case _I(P,I,N,K,3):
				return alpha | X11_PINK_3;
			case _I(P,I,N,K,_,3):
				return alpha | X11_PINK_3;
			case _I(P,I,N,K, ,3):
				return alpha | X11_PINK_3;
			case _I(P,I,N,K,4):
				return alpha | X11_PINK_4;
			case _I(P,I,N,K,_,4):
				return alpha | X11_PINK_4;
			case _I(P,I,N,K, ,4):
				return alpha | X11_PINK_4;
			case _I(L,I,G,H,T,P,I,N,K,1):
				return alpha | X11_LIGHT_PINK_1;
			case _I(L,I,G,H,T,_,P,I,N,K,_,1):
				return alpha | X11_LIGHT_PINK_1;
			case _I(L,I,G,H,T, ,P,I,N,K, ,1):
				return alpha | X11_LIGHT_PINK_1;
			case _I(L,I,G,H,T,P,I,N,K,2):
				return alpha | X11_LIGHT_PINK_2;
			case _I(L,I,G,H,T,_,P,I,N,K,_,2):
				return alpha | X11_LIGHT_PINK_2;
			case _I(L,I,G,H,T, ,P,I,N,K, ,2):
				return alpha | X11_LIGHT_PINK_2;
			case _I(L,I,G,H,T,P,I,N,K,3):
				return alpha | X11_LIGHT_PINK_3;
			case _I(L,I,G,H,T,_,P,I,N,K,_,3):
				return alpha | X11_LIGHT_PINK_3;
			case _I(L,I,G,H,T, ,P,I,N,K, ,3):
				return alpha | X11_LIGHT_PINK_3;
			case _I(L,I,G,H,T,P,I,N,K,4):
				return alpha | X11_LIGHT_PINK_4;
			case _I(L,I,G,H,T,_,P,I,N,K,_,4):
				return alpha | X11_LIGHT_PINK_4;
			case _I(L,I,G,H,T, ,P,I,N,K, ,4):
				return alpha | X11_LIGHT_PINK_4;
			case _I(P,A,L,E,V,I,O,L,E,T,R,E,D,1):
				return alpha | X11_PALE_VIOLET_RED_1;
			case _I(P,A,L,E,_,V,I,O,L,E,T,_,R,E,D,_,1):
				return alpha | X11_PALE_VIOLET_RED_1;
			case _I(P,A,L,E, ,V,I,O,L,E,T, ,R,E,D, ,1):
				return alpha | X11_PALE_VIOLET_RED_1;
			case _I(P,A,L,E,V,I,O,L,E,T,R,E,D,2):
				return alpha | X11_PALE_VIOLET_RED_2;
			case _I(P,A,L,E,_,V,I,O,L,E,T,_,R,E,D,_,2):
				return alpha | X11_PALE_VIOLET_RED_2;
			case _I(P,A,L,E, ,V,I,O,L,E,T, ,R,E,D, ,2):
				return alpha | X11_PALE_VIOLET_RED_2;
			case _I(P,A,L,E,V,I,O,L,E,T,R,E,D,3):
				return alpha | X11_PALE_VIOLET_RED_3;
			case _I(P,A,L,E,_,V,I,O,L,E,T,_,R,E,D,_,3):
				return alpha | X11_PALE_VIOLET_RED_3;
			case _I(P,A,L,E, ,V,I,O,L,E,T, ,R,E,D, ,3):
				return alpha | X11_PALE_VIOLET_RED_3;
			case _I(P,A,L,E,V,I,O,L,E,T,R,E,D,4):
				return alpha | X11_PALE_VIOLET_RED_4;
			case _I(P,A,L,E,_,V,I,O,L,E,T,_,R,E,D,_,4):
				return alpha | X11_PALE_VIOLET_RED_4;
			case _I(P,A,L,E, ,V,I,O,L,E,T, ,R,E,D, ,4):
				return alpha | X11_PALE_VIOLET_RED_4;
			case _I(M,A,R,O,O,N,1):
				return alpha | X11_MAROON_1;
			case _I(M,A,R,O,O,N,_,1):
				return alpha | X11_MAROON_1;
			case _I(M,A,R,O,O,N, ,1):
				return alpha | X11_MAROON_1;
			case _I(M,A,R,O,O,N,2):
				return alpha | X11_MAROON_2;
			case _I(M,A,R,O,O,N,_,2):
				return alpha | X11_MAROON_2;
			case _I(M,A,R,O,O,N, ,2):
				return alpha | X11_MAROON_2;
			case _I(M,A,R,O,O,N,3):
				return alpha | X11_MAROON_3;
			case _I(M,A,R,O,O,N,_,3):
				return alpha | X11_MAROON_3;
			case _I(M,A,R,O,O,N, ,3):
				return alpha | X11_MAROON_3;
			case _I(M,A,R,O,O,N,4):
				return alpha | X11_MAROON_4;
			case _I(M,A,R,O,O,N,_,4):
				return alpha | X11_MAROON_4;
			case _I(M,A,R,O,O,N, ,4):
				return alpha | X11_MAROON_4;
			case _I(V,I,O,L,E,T,R,E,D,1):
				return alpha | X11_VIOLET_RED_1;
			case _I(V,I,O,L,E,T,_,R,E,D,_,1):
				return alpha | X11_VIOLET_RED_1;
			case _I(V,I,O,L,E,T, ,R,E,D, ,1):
				return alpha | X11_VIOLET_RED_1;
			case _I(V,I,O,L,E,T,R,E,D,2):
				return alpha | X11_VIOLET_RED_2;
			case _I(V,I,O,L,E,T,_,R,E,D,_,2):
				return alpha | X11_VIOLET_RED_2;
			case _I(V,I,O,L,E,T, ,R,E,D, ,2):
				return alpha | X11_VIOLET_RED_2;
			case _I(V,I,O,L,E,T,R,E,D,3):
				return alpha | X11_VIOLET_RED_3;
			case _I(V,I,O,L,E,T,_,R,E,D,_,3):
				return alpha | X11_VIOLET_RED_3;
			case _I(V,I,O,L,E,T, ,R,E,D, ,3):
				return alpha | X11_VIOLET_RED_3;
			case _I(V,I,O,L,E,T,R,E,D,4):
				return alpha | X11_VIOLET_RED_4;
			case _I(V,I,O,L,E,T,_,R,E,D,_,4):
				return alpha | X11_VIOLET_RED_4;
			case _I(V,I,O,L,E,T, ,R,E,D, ,4):
				return alpha | X11_VIOLET_RED_4;
			case _I(M,A,G,E,N,T,A,1):
				return alpha | X11_MAGENTA_1;
			case _I(M,A,G,E,N,T,A,_,1):
				return alpha | X11_MAGENTA_1;
			case _I(M,A,G,E,N,T,A, ,1):
				return alpha | X11_MAGENTA_1;
			case _I(M,A,G,E,N,T,A,2):
				return alpha | X11_MAGENTA_2;
			case _I(M,A,G,E,N,T,A,_,2):
				return alpha | X11_MAGENTA_2;
			case _I(M,A,G,E,N,T,A, ,2):
				return alpha | X11_MAGENTA_2;
			case _I(M,A,G,E,N,T,A,3):
				return alpha | X11_MAGENTA_3;
			case _I(M,A,G,E,N,T,A,_,3):
				return alpha | X11_MAGENTA_3;
			case _I(M,A,G,E,N,T,A, ,3):
				return alpha | X11_MAGENTA_3;
			case _I(M,A,G,E,N,T,A,4):
				return alpha | X11_MAGENTA_4;
			case _I(M,A,G,E,N,T,A,_,4):
				return alpha | X11_MAGENTA_4;
			case _I(M,A,G,E,N,T,A, ,4):
				return alpha | X11_MAGENTA_4;
			case _I(O,R,C,H,I,D,1):
				return alpha | X11_ORCHID_1;
			case _I(O,R,C,H,I,D,_,1):
				return alpha | X11_ORCHID_1;
			case _I(O,R,C,H,I,D, ,1):
				return alpha | X11_ORCHID_1;
			case _I(O,R,C,H,I,D,2):
				return alpha | X11_ORCHID_2;
			case _I(O,R,C,H,I,D,_,2):
				return alpha | X11_ORCHID_2;
			case _I(O,R,C,H,I,D, ,2):
				return alpha | X11_ORCHID_2;
			case _I(O,R,C,H,I,D,3):
				return alpha | X11_ORCHID_3;
			case _I(O,R,C,H,I,D,_,3):
				return alpha | X11_ORCHID_3;
			case _I(O,R,C,H,I,D, ,3):
				return alpha | X11_ORCHID_3;
			case _I(O,R,C,H,I,D,4):
				return alpha | X11_ORCHID_4;
			case _I(O,R,C,H,I,D,_,4):
				return alpha | X11_ORCHID_4;
			case _I(O,R,C,H,I,D, ,4):
				return alpha | X11_ORCHID_4;
			case _I(P,L,U,M,1):
				return alpha | X11_PLUM_1;
			case _I(P,L,U,M,_,1):
				return alpha | X11_PLUM_1;
			case _I(P,L,U,M, ,1):
				return alpha | X11_PLUM_1;
			case _I(P,L,U,M,2):
				return alpha | X11_PLUM_2;
			case _I(P,L,U,M,_,2):
				return alpha | X11_PLUM_2;
			case _I(P,L,U,M, ,2):
				return alpha | X11_PLUM_2;
			case _I(P,L,U,M,3):
				return alpha | X11_PLUM_3;
			case _I(P,L,U,M,_,3):
				return alpha | X11_PLUM_3;
			case _I(P,L,U,M, ,3):
				return alpha | X11_PLUM_3;
			case _I(P,L,U,M,4):
				return alpha | X11_PLUM_4;
			case _I(P,L,U,M,_,4):
				return alpha | X11_PLUM_4;
			case _I(P,L,U,M, ,4):
				return alpha | X11_PLUM_4;
			case _I(M,E,D,I,U,M,O,R,C,H,I,D,1):
				return alpha | X11_MEDIUM_ORCHID_1;
			case _I(M,E,D,I,U,M,_,O,R,C,H,I,D,_,1):
				return alpha | X11_MEDIUM_ORCHID_1;
			case _I(M,E,D,I,U,M, ,O,R,C,H,I,D, ,1):
				return alpha | X11_MEDIUM_ORCHID_1;
			case _I(M,E,D,I,U,M,O,R,C,H,I,D,2):
				return alpha | X11_MEDIUM_ORCHID_2;
			case _I(M,E,D,I,U,M,_,O,R,C,H,I,D,_,2):
				return alpha | X11_MEDIUM_ORCHID_2;
			case _I(M,E,D,I,U,M, ,O,R,C,H,I,D, ,2):
				return alpha | X11_MEDIUM_ORCHID_2;
			case _I(M,E,D,I,U,M,O,R,C,H,I,D,3):
				return alpha | X11_MEDIUM_ORCHID_3;
			case _I(M,E,D,I,U,M,_,O,R,C,H,I,D,_,3):
				return alpha | X11_MEDIUM_ORCHID_3;
			case _I(M,E,D,I,U,M, ,O,R,C,H,I,D, ,3):
				return alpha | X11_MEDIUM_ORCHID_3;
			case _I(M,E,D,I,U,M,O,R,C,H,I,D,4):
				return alpha | X11_MEDIUM_ORCHID_4;
			case _I(M,E,D,I,U,M,_,O,R,C,H,I,D,_,4):
				return alpha | X11_MEDIUM_ORCHID_4;
			case _I(M,E,D,I,U,M, ,O,R,C,H,I,D, ,4):
				return alpha | X11_MEDIUM_ORCHID_4;
			case _I(D,A,R,K,O,R,C,H,I,D,1):
				return alpha | X11_DARK_ORCHID_1;
			case _I(D,A,R,K,_,O,R,C,H,I,D,_,1):
				return alpha | X11_DARK_ORCHID_1;
			case _I(D,A,R,K, ,O,R,C,H,I,D, ,1):
				return alpha | X11_DARK_ORCHID_1;
			case _I(D,A,R,K,O,R,C,H,I,D,2):
				return alpha | X11_DARK_ORCHID_2;
			case _I(D,A,R,K,_,O,R,C,H,I,D,_,2):
				return alpha | X11_DARK_ORCHID_2;
			case _I(D,A,R,K, ,O,R,C,H,I,D, ,2):
				return alpha | X11_DARK_ORCHID_2;
			case _I(D,A,R,K,O,R,C,H,I,D,3):
				return alpha | X11_DARK_ORCHID_3;
			case _I(D,A,R,K,_,O,R,C,H,I,D,_,3):
				return alpha | X11_DARK_ORCHID_3;
			case _I(D,A,R,K, ,O,R,C,H,I,D, ,3):
				return alpha | X11_DARK_ORCHID_3;
			case _I(D,A,R,K,O,R,C,H,I,D,4):
				return alpha | X11_DARK_ORCHID_4;
			case _I(D,A,R,K,_,O,R,C,H,I,D,_,4):
				return alpha | X11_DARK_ORCHID_4;
			case _I(D,A,R,K, ,O,R,C,H,I,D, ,4):
				return alpha | X11_DARK_ORCHID_4;
			case _I(P,U,R,P,L,E,1):
				return alpha | X11_PURPLE_1;
			case _I(P,U,R,P,L,E,_,1):
				return alpha | X11_PURPLE_1;
			case _I(P,U,R,P,L,E, ,1):
				return alpha | X11_PURPLE_1;
			case _I(P,U,R,P,L,E,2):
				return alpha | X11_PURPLE_2;
			case _I(P,U,R,P,L,E,_,2):
				return alpha | X11_PURPLE_2;
			case _I(P,U,R,P,L,E, ,2):
				return alpha | X11_PURPLE_2;
			case _I(P,U,R,P,L,E,3):
				return alpha | X11_PURPLE_3;
			case _I(P,U,R,P,L,E,_,3):
				return alpha | X11_PURPLE_3;
			case _I(P,U,R,P,L,E, ,3):
				return alpha | X11_PURPLE_3;
			case _I(P,U,R,P,L,E,4):
				return alpha | X11_PURPLE_4;
			case _I(P,U,R,P,L,E,_,4):
				return alpha | X11_PURPLE_4;
			case _I(P,U,R,P,L,E, ,4):
				return alpha | X11_PURPLE_4;
			case _I(M,E,D,I,U,M,P,U,R,P,L,E,1):
				return alpha | X11_MEDIUM_PURPLE_1;
			case _I(M,E,D,I,U,M,_,P,U,R,P,L,E,_,1):
				return alpha | X11_MEDIUM_PURPLE_1;
			case _I(M,E,D,I,U,M, ,P,U,R,P,L,E, ,1):
				return alpha | X11_MEDIUM_PURPLE_1;
			case _I(M,E,D,I,U,M,P,U,R,P,L,E,2):
				return alpha | X11_MEDIUM_PURPLE_2;
			case _I(M,E,D,I,U,M,_,P,U,R,P,L,E,_,2):
				return alpha | X11_MEDIUM_PURPLE_2;
			case _I(M,E,D,I,U,M, ,P,U,R,P,L,E, ,2):
				return alpha | X11_MEDIUM_PURPLE_2;
			case _I(M,E,D,I,U,M,P,U,R,P,L,E,3):
				return alpha | X11_MEDIUM_PURPLE_3;
			case _I(M,E,D,I,U,M,_,P,U,R,P,L,E,_,3):
				return alpha | X11_MEDIUM_PURPLE_3;
			case _I(M,E,D,I,U,M, ,P,U,R,P,L,E, ,3):
				return alpha | X11_MEDIUM_PURPLE_3;
			case _I(M,E,D,I,U,M,P,U,R,P,L,E,4):
				return alpha | X11_MEDIUM_PURPLE_4;
			case _I(M,E,D,I,U,M,_,P,U,R,P,L,E,_,4):
				return alpha | X11_MEDIUM_PURPLE_4;
			case _I(M,E,D,I,U,M, ,P,U,R,P,L,E, ,4):
				return alpha | X11_MEDIUM_PURPLE_4;
			case _I(T,H,I,S,T,L,E,1):
				return alpha | X11_THISTLE_1;
			case _I(T,H,I,S,T,L,E,_,1):
				return alpha | X11_THISTLE_1;
			case _I(T,H,I,S,T,L,E, ,1):
				return alpha | X11_THISTLE_1;
			case _I(T,H,I,S,T,L,E,2):
				return alpha | X11_THISTLE_2;
			case _I(T,H,I,S,T,L,E,_,2):
				return alpha | X11_THISTLE_2;
			case _I(T,H,I,S,T,L,E, ,2):
				return alpha | X11_THISTLE_2;
			case _I(T,H,I,S,T,L,E,3):
				return alpha | X11_THISTLE_3;
			case _I(T,H,I,S,T,L,E,_,3):
				return alpha | X11_THISTLE_3;
			case _I(T,H,I,S,T,L,E, ,3):
				return alpha | X11_THISTLE_3;
			case _I(T,H,I,S,T,L,E,4):
				return alpha | X11_THISTLE_4;
			case _I(T,H,I,S,T,L,E,_,4):
				return alpha | X11_THISTLE_4;
			case _I(T,H,I,S,T,L,E, ,4):
				return alpha | X11_THISTLE_4;
			case _I(G,R,A,Y,0):
				return alpha | X11_GRAY_0;
			case _I(G,R,A,Y,_,0):
				return alpha | X11_GRAY_0;
			case _I(G,R,A,Y, ,0):
				return alpha | X11_GRAY_0;
			case _I(G,R,E,Y,0):
				return alpha | X11_GREY_0;
			case _I(G,R,E,Y,_,0):
				return alpha | X11_GREY_0;
			case _I(G,R,E,Y, ,0):
				return alpha | X11_GREY_0;
			case _I(G,R,A,Y,1):
				return alpha | X11_GRAY_1;
			case _I(G,R,A,Y,_,1):
				return alpha | X11_GRAY_1;
			case _I(G,R,A,Y, ,1):
				return alpha | X11_GRAY_1;
			case _I(G,R,E,Y,1):
				return alpha | X11_GREY_1;
			case _I(G,R,E,Y,_,1):
				return alpha | X11_GREY_1;
			case _I(G,R,E,Y, ,1):
				return alpha | X11_GREY_1;
			case _I(G,R,A,Y,2):
				return alpha | X11_GRAY_2;
			case _I(G,R,A,Y,_,2):
				return alpha | X11_GRAY_2;
			case _I(G,R,A,Y, ,2):
				return alpha | X11_GRAY_2;
			case _I(G,R,E,Y,2):
				return alpha | X11_GREY_2;
			case _I(G,R,E,Y,_,2):
				return alpha | X11_GREY_2;
			case _I(G,R,E,Y, ,2):
				return alpha | X11_GREY_2;
			case _I(G,R,A,Y,3):
				return alpha | X11_GRAY_3;
			case _I(G,R,A,Y,_,3):
				return alpha | X11_GRAY_3;
			case _I(G,R,A,Y, ,3):
				return alpha | X11_GRAY_3;
			case _I(G,R,E,Y,3):
				return alpha | X11_GREY_3;
			case _I(G,R,E,Y,_,3):
				return alpha | X11_GREY_3;
			case _I(G,R,E,Y, ,3):
				return alpha | X11_GREY_3;
			case _I(G,R,A,Y,4):
				return alpha | X11_GRAY_4;
			case _I(G,R,A,Y,_,4):
				return alpha | X11_GRAY_4;
			case _I(G,R,A,Y, ,4):
				return alpha | X11_GRAY_4;
			case _I(G,R,E,Y,4):
				return alpha | X11_GREY_4;
			case _I(G,R,E,Y,_,4):
				return alpha | X11_GREY_4;
			case _I(G,R,E,Y, ,4):
				return alpha | X11_GREY_4;
			case _I(G,R,A,Y,5):
				return alpha | X11_GRAY_5;
			case _I(G,R,A,Y,_,5):
				return alpha | X11_GRAY_5;
			case _I(G,R,A,Y, ,5):
				return alpha | X11_GRAY_5;
			case _I(G,R,E,Y,5):
				return alpha | X11_GREY_5;
			case _I(G,R,E,Y,_,5):
				return alpha | X11_GREY_5;
			case _I(G,R,E,Y, ,5):
				return alpha | X11_GREY_5;
			case _I(G,R,A,Y,6):
				return alpha | X11_GRAY_6;
			case _I(G,R,A,Y,_,6):
				return alpha | X11_GRAY_6;
			case _I(G,R,A,Y, ,6):
				return alpha | X11_GRAY_6;
			case _I(G,R,E,Y,6):
				return alpha | X11_GREY_6;
			case _I(G,R,E,Y,_,6):
				return alpha | X11_GREY_6;
			case _I(G,R,E,Y, ,6):
				return alpha | X11_GREY_6;
			case _I(G,R,A,Y,7):
				return alpha | X11_GRAY_7;
			case _I(G,R,A,Y,_,7):
				return alpha | X11_GRAY_7;
			case _I(G,R,A,Y, ,7):
				return alpha | X11_GRAY_7;
			case _I(G,R,E,Y,7):
				return alpha | X11_GREY_7;
			case _I(G,R,E,Y,_,7):
				return alpha | X11_GREY_7;
			case _I(G,R,E,Y, ,7):
				return alpha | X11_GREY_7;
			case _I(G,R,A,Y,8):
				return alpha | X11_GRAY_8;
			case _I(G,R,A,Y,_,8):
				return alpha | X11_GRAY_8;
			case _I(G,R,A,Y, ,8):
				return alpha | X11_GRAY_8;
			case _I(G,R,E,Y,8):
				return alpha | X11_GREY_8;
			case _I(G,R,E,Y,_,8):
				return alpha | X11_GREY_8;
			case _I(G,R,E,Y, ,8):
				return alpha | X11_GREY_8;
			case _I(G,R,A,Y,9):
				return alpha | X11_GRAY_9;
			case _I(G,R,A,Y,_,9):
				return alpha | X11_GRAY_9;
			case _I(G,R,A,Y, ,9):
				return alpha | X11_GRAY_9;
			case _I(G,R,E,Y,9):
				return alpha | X11_GREY_9;
			case _I(G,R,E,Y,_,9):
				return alpha | X11_GREY_9;
			case _I(G,R,E,Y, ,9):
				return alpha | X11_GREY_9;
			case _I(G,R,A,Y,1,0):
				return alpha | X11_GRAY_10;
			case _I(G,R,A,Y,_,1,0):
				return alpha | X11_GRAY_10;
			case _I(G,R,A,Y, ,1,0):
				return alpha | X11_GRAY_10;
			case _I(G,R,E,Y,1,0):
				return alpha | X11_GREY_10;
			case _I(G,R,E,Y,_,1,0):
				return alpha | X11_GREY_10;
			case _I(G,R,E,Y, ,1,0):
				return alpha | X11_GREY_10;
			case _I(G,R,A,Y,1,1):
				return alpha | X11_GRAY_11;
			case _I(G,R,A,Y,_,1,1):
				return alpha | X11_GRAY_11;
			case _I(G,R,A,Y, ,1,1):
				return alpha | X11_GRAY_11;
			case _I(G,R,E,Y,1,1):
				return alpha | X11_GREY_11;
			case _I(G,R,E,Y,_,1,1):
				return alpha | X11_GREY_11;
			case _I(G,R,E,Y, ,1,1):
				return alpha | X11_GREY_11;
			case _I(G,R,A,Y,1,2):
				return alpha | X11_GRAY_12;
			case _I(G,R,A,Y,_,1,2):
				return alpha | X11_GRAY_12;
			case _I(G,R,A,Y, ,1,2):
				return alpha | X11_GRAY_12;
			case _I(G,R,E,Y,1,2):
				return alpha | X11_GREY_12;
			case _I(G,R,E,Y,_,1,2):
				return alpha | X11_GREY_12;
			case _I(G,R,E,Y, ,1,2):
				return alpha | X11_GREY_12;
			case _I(G,R,A,Y,1,3):
				return alpha | X11_GRAY_13;
			case _I(G,R,A,Y,_,1,3):
				return alpha | X11_GRAY_13;
			case _I(G,R,A,Y, ,1,3):
				return alpha | X11_GRAY_13;
			case _I(G,R,E,Y,1,3):
				return alpha | X11_GREY_13;
			case _I(G,R,E,Y,_,1,3):
				return alpha | X11_GREY_13;
			case _I(G,R,E,Y, ,1,3):
				return alpha | X11_GREY_13;
			case _I(G,R,A,Y,1,4):
				return alpha | X11_GRAY_14;
			case _I(G,R,A,Y,_,1,4):
				return alpha | X11_GRAY_14;
			case _I(G,R,A,Y, ,1,4):
				return alpha | X11_GRAY_14;
			case _I(G,R,E,Y,1,4):
				return alpha | X11_GREY_14;
			case _I(G,R,E,Y,_,1,4):
				return alpha | X11_GREY_14;
			case _I(G,R,E,Y, ,1,4):
				return alpha | X11_GREY_14;
			case _I(G,R,A,Y,1,5):
				return alpha | X11_GRAY_15;
			case _I(G,R,A,Y,_,1,5):
				return alpha | X11_GRAY_15;
			case _I(G,R,A,Y, ,1,5):
				return alpha | X11_GRAY_15;
			case _I(G,R,E,Y,1,5):
				return alpha | X11_GREY_15;
			case _I(G,R,E,Y,_,1,5):
				return alpha | X11_GREY_15;
			case _I(G,R,E,Y, ,1,5):
				return alpha | X11_GREY_15;
			case _I(G,R,A,Y,1,6):
				return alpha | X11_GRAY_16;
			case _I(G,R,A,Y,_,1,6):
				return alpha | X11_GRAY_16;
			case _I(G,R,A,Y, ,1,6):
				return alpha | X11_GRAY_16;
			case _I(G,R,E,Y,1,6):
				return alpha | X11_GREY_16;
			case _I(G,R,E,Y,_,1,6):
				return alpha | X11_GREY_16;
			case _I(G,R,E,Y, ,1,6):
				return alpha | X11_GREY_16;
			case _I(G,R,A,Y,1,7):
				return alpha | X11_GRAY_17;
			case _I(G,R,A,Y,_,1,7):
				return alpha | X11_GRAY_17;
			case _I(G,R,A,Y, ,1,7):
				return alpha | X11_GRAY_17;
			case _I(G,R,E,Y,1,7):
				return alpha | X11_GREY_17;
			case _I(G,R,E,Y,_,1,7):
				return alpha | X11_GREY_17;
			case _I(G,R,E,Y, ,1,7):
				return alpha | X11_GREY_17;
			case _I(G,R,A,Y,1,8):
				return alpha | X11_GRAY_18;
			case _I(G,R,A,Y,_,1,8):
				return alpha | X11_GRAY_18;
			case _I(G,R,A,Y, ,1,8):
				return alpha | X11_GRAY_18;
			case _I(G,R,E,Y,1,8):
				return alpha | X11_GREY_18;
			case _I(G,R,E,Y,_,1,8):
				return alpha | X11_GREY_18;
			case _I(G,R,E,Y, ,1,8):
				return alpha | X11_GREY_18;
			case _I(G,R,A,Y,1,9):
				return alpha | X11_GRAY_19;
			case _I(G,R,A,Y,_,1,9):
				return alpha | X11_GRAY_19;
			case _I(G,R,A,Y, ,1,9):
				return alpha | X11_GRAY_19;
			case _I(G,R,E,Y,1,9):
				return alpha | X11_GREY_19;
			case _I(G,R,E,Y,_,1,9):
				return alpha | X11_GREY_19;
			case _I(G,R,E,Y, ,1,9):
				return alpha | X11_GREY_19;
			case _I(G,R,A,Y,2,0):
				return alpha | X11_GRAY_20;
			case _I(G,R,A,Y,_,2,0):
				return alpha | X11_GRAY_20;
			case _I(G,R,A,Y, ,2,0):
				return alpha | X11_GRAY_20;
			case _I(G,R,E,Y,2,0):
				return alpha | X11_GREY_20;
			case _I(G,R,E,Y,_,2,0):
				return alpha | X11_GREY_20;
			case _I(G,R,E,Y, ,2,0):
				return alpha | X11_GREY_20;
			case _I(G,R,A,Y,2,1):
				return alpha | X11_GRAY_21;
			case _I(G,R,A,Y,_,2,1):
				return alpha | X11_GRAY_21;
			case _I(G,R,A,Y, ,2,1):
				return alpha | X11_GRAY_21;
			case _I(G,R,E,Y,2,1):
				return alpha | X11_GREY_21;
			case _I(G,R,E,Y,_,2,1):
				return alpha | X11_GREY_21;
			case _I(G,R,E,Y, ,2,1):
				return alpha | X11_GREY_21;
			case _I(G,R,A,Y,2,2):
				return alpha | X11_GRAY_22;
			case _I(G,R,A,Y,_,2,2):
				return alpha | X11_GRAY_22;
			case _I(G,R,A,Y, ,2,2):
				return alpha | X11_GRAY_22;
			case _I(G,R,E,Y,2,2):
				return alpha | X11_GREY_22;
			case _I(G,R,E,Y,_,2,2):
				return alpha | X11_GREY_22;
			case _I(G,R,E,Y, ,2,2):
				return alpha | X11_GREY_22;
			case _I(G,R,A,Y,2,3):
				return alpha | X11_GRAY_23;
			case _I(G,R,A,Y,_,2,3):
				return alpha | X11_GRAY_23;
			case _I(G,R,A,Y, ,2,3):
				return alpha | X11_GRAY_23;
			case _I(G,R,E,Y,2,3):
				return alpha | X11_GREY_23;
			case _I(G,R,E,Y,_,2,3):
				return alpha | X11_GREY_23;
			case _I(G,R,E,Y, ,2,3):
				return alpha | X11_GREY_23;
			case _I(G,R,A,Y,2,4):
				return alpha | X11_GRAY_24;
			case _I(G,R,A,Y,_,2,4):
				return alpha | X11_GRAY_24;
			case _I(G,R,A,Y, ,2,4):
				return alpha | X11_GRAY_24;
			case _I(G,R,E,Y,2,4):
				return alpha | X11_GREY_24;
			case _I(G,R,E,Y,_,2,4):
				return alpha | X11_GREY_24;
			case _I(G,R,E,Y, ,2,4):
				return alpha | X11_GREY_24;
			case _I(G,R,A,Y,2,5):
				return alpha | X11_GRAY_25;
			case _I(G,R,A,Y,_,2,5):
				return alpha | X11_GRAY_25;
			case _I(G,R,A,Y, ,2,5):
				return alpha | X11_GRAY_25;
			case _I(G,R,E,Y,2,5):
				return alpha | X11_GREY_25;
			case _I(G,R,E,Y,_,2,5):
				return alpha | X11_GREY_25;
			case _I(G,R,E,Y, ,2,5):
				return alpha | X11_GREY_25;
			case _I(G,R,A,Y,2,6):
				return alpha | X11_GRAY_26;
			case _I(G,R,A,Y,_,2,6):
				return alpha | X11_GRAY_26;
			case _I(G,R,A,Y, ,2,6):
				return alpha | X11_GRAY_26;
			case _I(G,R,E,Y,2,6):
				return alpha | X11_GREY_26;
			case _I(G,R,E,Y,_,2,6):
				return alpha | X11_GREY_26;
			case _I(G,R,E,Y, ,2,6):
				return alpha | X11_GREY_26;
			case _I(G,R,A,Y,2,7):
				return alpha | X11_GRAY_27;
			case _I(G,R,A,Y,_,2,7):
				return alpha | X11_GRAY_27;
			case _I(G,R,A,Y, ,2,7):
				return alpha | X11_GRAY_27;
			case _I(G,R,E,Y,2,7):
				return alpha | X11_GREY_27;
			case _I(G,R,E,Y,_,2,7):
				return alpha | X11_GREY_27;
			case _I(G,R,E,Y, ,2,7):
				return alpha | X11_GREY_27;
			case _I(G,R,A,Y,2,8):
				return alpha | X11_GRAY_28;
			case _I(G,R,A,Y,_,2,8):
				return alpha | X11_GRAY_28;
			case _I(G,R,A,Y, ,2,8):
				return alpha | X11_GRAY_28;
			case _I(G,R,E,Y,2,8):
				return alpha | X11_GREY_28;
			case _I(G,R,E,Y,_,2,8):
				return alpha | X11_GREY_28;
			case _I(G,R,E,Y, ,2,8):
				return alpha | X11_GREY_28;
			case _I(G,R,A,Y,2,9):
				return alpha | X11_GRAY_29;
			case _I(G,R,A,Y,_,2,9):
				return alpha | X11_GRAY_29;
			case _I(G,R,A,Y, ,2,9):
				return alpha | X11_GRAY_29;
			case _I(G,R,E,Y,2,9):
				return alpha | X11_GREY_29;
			case _I(G,R,E,Y,_,2,9):
				return alpha | X11_GREY_29;
			case _I(G,R,E,Y, ,2,9):
				return alpha | X11_GREY_29;
			case _I(G,R,A,Y,3,0):
				return alpha | X11_GRAY_30;
			case _I(G,R,A,Y,_,3,0):
				return alpha | X11_GRAY_30;
			case _I(G,R,A,Y, ,3,0):
				return alpha | X11_GRAY_30;
			case _I(G,R,E,Y,3,0):
				return alpha | X11_GREY_30;
			case _I(G,R,E,Y,_,3,0):
				return alpha | X11_GREY_30;
			case _I(G,R,E,Y, ,3,0):
				return alpha | X11_GREY_30;
			case _I(G,R,A,Y,3,1):
				return alpha | X11_GRAY_31;
			case _I(G,R,A,Y,_,3,1):
				return alpha | X11_GRAY_31;
			case _I(G,R,A,Y, ,3,1):
				return alpha | X11_GRAY_31;
			case _I(G,R,E,Y,3,1):
				return alpha | X11_GREY_31;
			case _I(G,R,E,Y,_,3,1):
				return alpha | X11_GREY_31;
			case _I(G,R,E,Y, ,3,1):
				return alpha | X11_GREY_31;
			case _I(G,R,A,Y,3,2):
				return alpha | X11_GRAY_32;
			case _I(G,R,A,Y,_,3,2):
				return alpha | X11_GRAY_32;
			case _I(G,R,A,Y, ,3,2):
				return alpha | X11_GRAY_32;
			case _I(G,R,E,Y,3,2):
				return alpha | X11_GREY_32;
			case _I(G,R,E,Y,_,3,2):
				return alpha | X11_GREY_32;
			case _I(G,R,E,Y, ,3,2):
				return alpha | X11_GREY_32;
			case _I(G,R,A,Y,3,3):
				return alpha | X11_GRAY_33;
			case _I(G,R,A,Y,_,3,3):
				return alpha | X11_GRAY_33;
			case _I(G,R,A,Y, ,3,3):
				return alpha | X11_GRAY_33;
			case _I(G,R,E,Y,3,3):
				return alpha | X11_GREY_33;
			case _I(G,R,E,Y,_,3,3):
				return alpha | X11_GREY_33;
			case _I(G,R,E,Y, ,3,3):
				return alpha | X11_GREY_33;
			case _I(G,R,A,Y,3,4):
				return alpha | X11_GRAY_34;
			case _I(G,R,A,Y,_,3,4):
				return alpha | X11_GRAY_34;
			case _I(G,R,A,Y, ,3,4):
				return alpha | X11_GRAY_34;
			case _I(G,R,E,Y,3,4):
				return alpha | X11_GREY_34;
			case _I(G,R,E,Y,_,3,4):
				return alpha | X11_GREY_34;
			case _I(G,R,E,Y, ,3,4):
				return alpha | X11_GREY_34;
			case _I(G,R,A,Y,3,5):
				return alpha | X11_GRAY_35;
			case _I(G,R,A,Y,_,3,5):
				return alpha | X11_GRAY_35;
			case _I(G,R,A,Y, ,3,5):
				return alpha | X11_GRAY_35;
			case _I(G,R,E,Y,3,5):
				return alpha | X11_GREY_35;
			case _I(G,R,E,Y,_,3,5):
				return alpha | X11_GREY_35;
			case _I(G,R,E,Y, ,3,5):
				return alpha | X11_GREY_35;
			case _I(G,R,A,Y,3,6):
				return alpha | X11_GRAY_36;
			case _I(G,R,A,Y,_,3,6):
				return alpha | X11_GRAY_36;
			case _I(G,R,A,Y, ,3,6):
				return alpha | X11_GRAY_36;
			case _I(G,R,E,Y,3,6):
				return alpha | X11_GREY_36;
			case _I(G,R,E,Y,_,3,6):
				return alpha | X11_GREY_36;
			case _I(G,R,E,Y, ,3,6):
				return alpha | X11_GREY_36;
			case _I(G,R,A,Y,3,7):
				return alpha | X11_GRAY_37;
			case _I(G,R,A,Y,_,3,7):
				return alpha | X11_GRAY_37;
			case _I(G,R,A,Y, ,3,7):
				return alpha | X11_GRAY_37;
			case _I(G,R,E,Y,3,7):
				return alpha | X11_GREY_37;
			case _I(G,R,E,Y,_,3,7):
				return alpha | X11_GREY_37;
			case _I(G,R,E,Y, ,3,7):
				return alpha | X11_GREY_37;
			case _I(G,R,A,Y,3,8):
				return alpha | X11_GRAY_38;
			case _I(G,R,A,Y,_,3,8):
				return alpha | X11_GRAY_38;
			case _I(G,R,A,Y, ,3,8):
				return alpha | X11_GRAY_38;
			case _I(G,R,E,Y,3,8):
				return alpha | X11_GREY_38;
			case _I(G,R,E,Y,_,3,8):
				return alpha | X11_GREY_38;
			case _I(G,R,E,Y, ,3,8):
				return alpha | X11_GREY_38;
			case _I(G,R,A,Y,3,9):
				return alpha | X11_GRAY_39;
			case _I(G,R,A,Y,_,3,9):
				return alpha | X11_GRAY_39;
			case _I(G,R,A,Y, ,3,9):
				return alpha | X11_GRAY_39;
			case _I(G,R,E,Y,3,9):
				return alpha | X11_GREY_39;
			case _I(G,R,E,Y,_,3,9):
				return alpha | X11_GREY_39;
			case _I(G,R,E,Y, ,3,9):
				return alpha | X11_GREY_39;
			case _I(G,R,A,Y,4,0):
				return alpha | X11_GRAY_40;
			case _I(G,R,A,Y,_,4,0):
				return alpha | X11_GRAY_40;
			case _I(G,R,A,Y, ,4,0):
				return alpha | X11_GRAY_40;
			case _I(G,R,E,Y,4,0):
				return alpha | X11_GREY_40;
			case _I(G,R,E,Y,_,4,0):
				return alpha | X11_GREY_40;
			case _I(G,R,E,Y, ,4,0):
				return alpha | X11_GREY_40;
			case _I(G,R,A,Y,4,1):
				return alpha | X11_GRAY_41;
			case _I(G,R,A,Y,_,4,1):
				return alpha | X11_GRAY_41;
			case _I(G,R,A,Y, ,4,1):
				return alpha | X11_GRAY_41;
			case _I(G,R,E,Y,4,1):
				return alpha | X11_GREY_41;
			case _I(G,R,E,Y,_,4,1):
				return alpha | X11_GREY_41;
			case _I(G,R,E,Y, ,4,1):
				return alpha | X11_GREY_41;
			case _I(G,R,A,Y,4,2):
				return alpha | X11_GRAY_42;
			case _I(G,R,A,Y,_,4,2):
				return alpha | X11_GRAY_42;
			case _I(G,R,A,Y, ,4,2):
				return alpha | X11_GRAY_42;
			case _I(G,R,E,Y,4,2):
				return alpha | X11_GREY_42;
			case _I(G,R,E,Y,_,4,2):
				return alpha | X11_GREY_42;
			case _I(G,R,E,Y, ,4,2):
				return alpha | X11_GREY_42;
			case _I(G,R,A,Y,4,3):
				return alpha | X11_GRAY_43;
			case _I(G,R,A,Y,_,4,3):
				return alpha | X11_GRAY_43;
			case _I(G,R,A,Y, ,4,3):
				return alpha | X11_GRAY_43;
			case _I(G,R,E,Y,4,3):
				return alpha | X11_GREY_43;
			case _I(G,R,E,Y,_,4,3):
				return alpha | X11_GREY_43;
			case _I(G,R,E,Y, ,4,3):
				return alpha | X11_GREY_43;
			case _I(G,R,A,Y,4,4):
				return alpha | X11_GRAY_44;
			case _I(G,R,A,Y,_,4,4):
				return alpha | X11_GRAY_44;
			case _I(G,R,A,Y, ,4,4):
				return alpha | X11_GRAY_44;
			case _I(G,R,E,Y,4,4):
				return alpha | X11_GREY_44;
			case _I(G,R,E,Y,_,4,4):
				return alpha | X11_GREY_44;
			case _I(G,R,E,Y, ,4,4):
				return alpha | X11_GREY_44;
			case _I(G,R,A,Y,4,5):
				return alpha | X11_GRAY_45;
			case _I(G,R,A,Y,_,4,5):
				return alpha | X11_GRAY_45;
			case _I(G,R,A,Y, ,4,5):
				return alpha | X11_GRAY_45;
			case _I(G,R,E,Y,4,5):
				return alpha | X11_GREY_45;
			case _I(G,R,E,Y,_,4,5):
				return alpha | X11_GREY_45;
			case _I(G,R,E,Y, ,4,5):
				return alpha | X11_GREY_45;
			case _I(G,R,A,Y,4,6):
				return alpha | X11_GRAY_46;
			case _I(G,R,A,Y,_,4,6):
				return alpha | X11_GRAY_46;
			case _I(G,R,A,Y, ,4,6):
				return alpha | X11_GRAY_46;
			case _I(G,R,E,Y,4,6):
				return alpha | X11_GREY_46;
			case _I(G,R,E,Y,_,4,6):
				return alpha | X11_GREY_46;
			case _I(G,R,E,Y, ,4,6):
				return alpha | X11_GREY_46;
			case _I(G,R,A,Y,4,7):
				return alpha | X11_GRAY_47;
			case _I(G,R,A,Y,_,4,7):
				return alpha | X11_GRAY_47;
			case _I(G,R,A,Y, ,4,7):
				return alpha | X11_GRAY_47;
			case _I(G,R,E,Y,4,7):
				return alpha | X11_GREY_47;
			case _I(G,R,E,Y,_,4,7):
				return alpha | X11_GREY_47;
			case _I(G,R,E,Y, ,4,7):
				return alpha | X11_GREY_47;
			case _I(G,R,A,Y,4,8):
				return alpha | X11_GRAY_48;
			case _I(G,R,A,Y,_,4,8):
				return alpha | X11_GRAY_48;
			case _I(G,R,A,Y, ,4,8):
				return alpha | X11_GRAY_48;
			case _I(G,R,E,Y,4,8):
				return alpha | X11_GREY_48;
			case _I(G,R,E,Y,_,4,8):
				return alpha | X11_GREY_48;
			case _I(G,R,E,Y, ,4,8):
				return alpha | X11_GREY_48;
			case _I(G,R,A,Y,4,9):
				return alpha | X11_GRAY_49;
			case _I(G,R,A,Y,_,4,9):
				return alpha | X11_GRAY_49;
			case _I(G,R,A,Y, ,4,9):
				return alpha | X11_GRAY_49;
			case _I(G,R,E,Y,4,9):
				return alpha | X11_GREY_49;
			case _I(G,R,E,Y,_,4,9):
				return alpha | X11_GREY_49;
			case _I(G,R,E,Y, ,4,9):
				return alpha | X11_GREY_49;
			case _I(G,R,A,Y,5,0):
				return alpha | X11_GRAY_50;
			case _I(G,R,A,Y,_,5,0):
				return alpha | X11_GRAY_50;
			case _I(G,R,A,Y, ,5,0):
				return alpha | X11_GRAY_50;
			case _I(G,R,E,Y,5,0):
				return alpha | X11_GREY_50;
			case _I(G,R,E,Y,_,5,0):
				return alpha | X11_GREY_50;
			case _I(G,R,E,Y, ,5,0):
				return alpha | X11_GREY_50;
			case _I(G,R,A,Y,5,1):
				return alpha | X11_GRAY_51;
			case _I(G,R,A,Y,_,5,1):
				return alpha | X11_GRAY_51;
			case _I(G,R,A,Y, ,5,1):
				return alpha | X11_GRAY_51;
			case _I(G,R,E,Y,5,1):
				return alpha | X11_GREY_51;
			case _I(G,R,E,Y,_,5,1):
				return alpha | X11_GREY_51;
			case _I(G,R,E,Y, ,5,1):
				return alpha | X11_GREY_51;
			case _I(G,R,A,Y,5,2):
				return alpha | X11_GRAY_52;
			case _I(G,R,A,Y,_,5,2):
				return alpha | X11_GRAY_52;
			case _I(G,R,A,Y, ,5,2):
				return alpha | X11_GRAY_52;
			case _I(G,R,E,Y,5,2):
				return alpha | X11_GREY_52;
			case _I(G,R,E,Y,_,5,2):
				return alpha | X11_GREY_52;
			case _I(G,R,E,Y, ,5,2):
				return alpha | X11_GREY_52;
			case _I(G,R,A,Y,5,3):
				return alpha | X11_GRAY_53;
			case _I(G,R,A,Y,_,5,3):
				return alpha | X11_GRAY_53;
			case _I(G,R,A,Y, ,5,3):
				return alpha | X11_GRAY_53;
			case _I(G,R,E,Y,5,3):
				return alpha | X11_GREY_53;
			case _I(G,R,E,Y,_,5,3):
				return alpha | X11_GREY_53;
			case _I(G,R,E,Y, ,5,3):
				return alpha | X11_GREY_53;
			case _I(G,R,A,Y,5,4):
				return alpha | X11_GRAY_54;
			case _I(G,R,A,Y,_,5,4):
				return alpha | X11_GRAY_54;
			case _I(G,R,A,Y, ,5,4):
				return alpha | X11_GRAY_54;
			case _I(G,R,E,Y,5,4):
				return alpha | X11_GREY_54;
			case _I(G,R,E,Y,_,5,4):
				return alpha | X11_GREY_54;
			case _I(G,R,E,Y, ,5,4):
				return alpha | X11_GREY_54;
			case _I(G,R,A,Y,5,5):
				return alpha | X11_GRAY_55;
			case _I(G,R,A,Y,_,5,5):
				return alpha | X11_GRAY_55;
			case _I(G,R,A,Y, ,5,5):
				return alpha | X11_GRAY_55;
			case _I(G,R,E,Y,5,5):
				return alpha | X11_GREY_55;
			case _I(G,R,E,Y,_,5,5):
				return alpha | X11_GREY_55;
			case _I(G,R,E,Y, ,5,5):
				return alpha | X11_GREY_55;
			case _I(G,R,A,Y,5,6):
				return alpha | X11_GRAY_56;
			case _I(G,R,A,Y,_,5,6):
				return alpha | X11_GRAY_56;
			case _I(G,R,A,Y, ,5,6):
				return alpha | X11_GRAY_56;
			case _I(G,R,E,Y,5,6):
				return alpha | X11_GREY_56;
			case _I(G,R,E,Y,_,5,6):
				return alpha | X11_GREY_56;
			case _I(G,R,E,Y, ,5,6):
				return alpha | X11_GREY_56;
			case _I(G,R,A,Y,5,7):
				return alpha | X11_GRAY_57;
			case _I(G,R,A,Y,_,5,7):
				return alpha | X11_GRAY_57;
			case _I(G,R,A,Y, ,5,7):
				return alpha | X11_GRAY_57;
			case _I(G,R,E,Y,5,7):
				return alpha | X11_GREY_57;
			case _I(G,R,E,Y,_,5,7):
				return alpha | X11_GREY_57;
			case _I(G,R,E,Y, ,5,7):
				return alpha | X11_GREY_57;
			case _I(G,R,A,Y,5,8):
				return alpha | X11_GRAY_58;
			case _I(G,R,A,Y,_,5,8):
				return alpha | X11_GRAY_58;
			case _I(G,R,A,Y, ,5,8):
				return alpha | X11_GRAY_58;
			case _I(G,R,E,Y,5,8):
				return alpha | X11_GREY_58;
			case _I(G,R,E,Y,_,5,8):
				return alpha | X11_GREY_58;
			case _I(G,R,E,Y, ,5,8):
				return alpha | X11_GREY_58;
			case _I(G,R,A,Y,5,9):
				return alpha | X11_GRAY_59;
			case _I(G,R,A,Y,_,5,9):
				return alpha | X11_GRAY_59;
			case _I(G,R,A,Y, ,5,9):
				return alpha | X11_GRAY_59;
			case _I(G,R,E,Y,5,9):
				return alpha | X11_GREY_59;
			case _I(G,R,E,Y,_,5,9):
				return alpha | X11_GREY_59;
			case _I(G,R,E,Y, ,5,9):
				return alpha | X11_GREY_59;
			case _I(G,R,A,Y,6,0):
				return alpha | X11_GRAY_60;
			case _I(G,R,A,Y,_,6,0):
				return alpha | X11_GRAY_60;
			case _I(G,R,A,Y, ,6,0):
				return alpha | X11_GRAY_60;
			case _I(G,R,E,Y,6,0):
				return alpha | X11_GREY_60;
			case _I(G,R,E,Y,_,6,0):
				return alpha | X11_GREY_60;
			case _I(G,R,E,Y, ,6,0):
				return alpha | X11_GREY_60;
			case _I(G,R,A,Y,6,1):
				return alpha | X11_GRAY_61;
			case _I(G,R,A,Y,_,6,1):
				return alpha | X11_GRAY_61;
			case _I(G,R,A,Y, ,6,1):
				return alpha | X11_GRAY_61;
			case _I(G,R,E,Y,6,1):
				return alpha | X11_GREY_61;
			case _I(G,R,E,Y,_,6,1):
				return alpha | X11_GREY_61;
			case _I(G,R,E,Y, ,6,1):
				return alpha | X11_GREY_61;
			case _I(G,R,A,Y,6,2):
				return alpha | X11_GRAY_62;
			case _I(G,R,A,Y,_,6,2):
				return alpha | X11_GRAY_62;
			case _I(G,R,A,Y, ,6,2):
				return alpha | X11_GRAY_62;
			case _I(G,R,E,Y,6,2):
				return alpha | X11_GREY_62;
			case _I(G,R,E,Y,_,6,2):
				return alpha | X11_GREY_62;
			case _I(G,R,E,Y, ,6,2):
				return alpha | X11_GREY_62;
			case _I(G,R,A,Y,6,3):
				return alpha | X11_GRAY_63;
			case _I(G,R,A,Y,_,6,3):
				return alpha | X11_GRAY_63;
			case _I(G,R,A,Y, ,6,3):
				return alpha | X11_GRAY_63;
			case _I(G,R,E,Y,6,3):
				return alpha | X11_GREY_63;
			case _I(G,R,E,Y,_,6,3):
				return alpha | X11_GREY_63;
			case _I(G,R,E,Y, ,6,3):
				return alpha | X11_GREY_63;
			case _I(G,R,A,Y,6,4):
				return alpha | X11_GRAY_64;
			case _I(G,R,A,Y,_,6,4):
				return alpha | X11_GRAY_64;
			case _I(G,R,A,Y, ,6,4):
				return alpha | X11_GRAY_64;
			case _I(G,R,E,Y,6,4):
				return alpha | X11_GREY_64;
			case _I(G,R,E,Y,_,6,4):
				return alpha | X11_GREY_64;
			case _I(G,R,E,Y, ,6,4):
				return alpha | X11_GREY_64;
			case _I(G,R,A,Y,6,5):
				return alpha | X11_GRAY_65;
			case _I(G,R,A,Y,_,6,5):
				return alpha | X11_GRAY_65;
			case _I(G,R,A,Y, ,6,5):
				return alpha | X11_GRAY_65;
			case _I(G,R,E,Y,6,5):
				return alpha | X11_GREY_65;
			case _I(G,R,E,Y,_,6,5):
				return alpha | X11_GREY_65;
			case _I(G,R,E,Y, ,6,5):
				return alpha | X11_GREY_65;
			case _I(G,R,A,Y,6,6):
				return alpha | X11_GRAY_66;
			case _I(G,R,A,Y,_,6,6):
				return alpha | X11_GRAY_66;
			case _I(G,R,A,Y, ,6,6):
				return alpha | X11_GRAY_66;
			case _I(G,R,E,Y,6,6):
				return alpha | X11_GREY_66;
			case _I(G,R,E,Y,_,6,6):
				return alpha | X11_GREY_66;
			case _I(G,R,E,Y, ,6,6):
				return alpha | X11_GREY_66;
			case _I(G,R,A,Y,6,7):
				return alpha | X11_GRAY_67;
			case _I(G,R,A,Y,_,6,7):
				return alpha | X11_GRAY_67;
			case _I(G,R,A,Y, ,6,7):
				return alpha | X11_GRAY_67;
			case _I(G,R,E,Y,6,7):
				return alpha | X11_GREY_67;
			case _I(G,R,E,Y,_,6,7):
				return alpha | X11_GREY_67;
			case _I(G,R,E,Y, ,6,7):
				return alpha | X11_GREY_67;
			case _I(G,R,A,Y,6,8):
				return alpha | X11_GRAY_68;
			case _I(G,R,A,Y,_,6,8):
				return alpha | X11_GRAY_68;
			case _I(G,R,A,Y, ,6,8):
				return alpha | X11_GRAY_68;
			case _I(G,R,E,Y,6,8):
				return alpha | X11_GREY_68;
			case _I(G,R,E,Y,_,6,8):
				return alpha | X11_GREY_68;
			case _I(G,R,E,Y, ,6,8):
				return alpha | X11_GREY_68;
			case _I(G,R,A,Y,6,9):
				return alpha | X11_GRAY_69;
			case _I(G,R,A,Y,_,6,9):
				return alpha | X11_GRAY_69;
			case _I(G,R,A,Y, ,6,9):
				return alpha | X11_GRAY_69;
			case _I(G,R,E,Y,6,9):
				return alpha | X11_GREY_69;
			case _I(G,R,E,Y,_,6,9):
				return alpha | X11_GREY_69;
			case _I(G,R,E,Y, ,6,9):
				return alpha | X11_GREY_69;
			case _I(G,R,A,Y,7,0):
				return alpha | X11_GRAY_70;
			case _I(G,R,A,Y,_,7,0):
				return alpha | X11_GRAY_70;
			case _I(G,R,A,Y, ,7,0):
				return alpha | X11_GRAY_70;
			case _I(G,R,E,Y,7,0):
				return alpha | X11_GREY_70;
			case _I(G,R,E,Y,_,7,0):
				return alpha | X11_GREY_70;
			case _I(G,R,E,Y, ,7,0):
				return alpha | X11_GREY_70;
			case _I(G,R,A,Y,7,1):
				return alpha | X11_GRAY_71;
			case _I(G,R,A,Y,_,7,1):
				return alpha | X11_GRAY_71;
			case _I(G,R,A,Y, ,7,1):
				return alpha | X11_GRAY_71;
			case _I(G,R,E,Y,7,1):
				return alpha | X11_GREY_71;
			case _I(G,R,E,Y,_,7,1):
				return alpha | X11_GREY_71;
			case _I(G,R,E,Y, ,7,1):
				return alpha | X11_GREY_71;
			case _I(G,R,A,Y,7,2):
				return alpha | X11_GRAY_72;
			case _I(G,R,A,Y,_,7,2):
				return alpha | X11_GRAY_72;
			case _I(G,R,A,Y, ,7,2):
				return alpha | X11_GRAY_72;
			case _I(G,R,E,Y,7,2):
				return alpha | X11_GREY_72;
			case _I(G,R,E,Y,_,7,2):
				return alpha | X11_GREY_72;
			case _I(G,R,E,Y, ,7,2):
				return alpha | X11_GREY_72;
			case _I(G,R,A,Y,7,3):
				return alpha | X11_GRAY_73;
			case _I(G,R,A,Y,_,7,3):
				return alpha | X11_GRAY_73;
			case _I(G,R,A,Y, ,7,3):
				return alpha | X11_GRAY_73;
			case _I(G,R,E,Y,7,3):
				return alpha | X11_GREY_73;
			case _I(G,R,E,Y,_,7,3):
				return alpha | X11_GREY_73;
			case _I(G,R,E,Y, ,7,3):
				return alpha | X11_GREY_73;
			case _I(G,R,A,Y,7,4):
				return alpha | X11_GRAY_74;
			case _I(G,R,A,Y,_,7,4):
				return alpha | X11_GRAY_74;
			case _I(G,R,A,Y, ,7,4):
				return alpha | X11_GRAY_74;
			case _I(G,R,E,Y,7,4):
				return alpha | X11_GREY_74;
			case _I(G,R,E,Y,_,7,4):
				return alpha | X11_GREY_74;
			case _I(G,R,E,Y, ,7,4):
				return alpha | X11_GREY_74;
			case _I(G,R,A,Y,7,5):
				return alpha | X11_GRAY_75;
			case _I(G,R,A,Y,_,7,5):
				return alpha | X11_GRAY_75;
			case _I(G,R,A,Y, ,7,5):
				return alpha | X11_GRAY_75;
			case _I(G,R,E,Y,7,5):
				return alpha | X11_GREY_75;
			case _I(G,R,E,Y,_,7,5):
				return alpha | X11_GREY_75;
			case _I(G,R,E,Y, ,7,5):
				return alpha | X11_GREY_75;
			case _I(G,R,A,Y,7,6):
				return alpha | X11_GRAY_76;
			case _I(G,R,A,Y,_,7,6):
				return alpha | X11_GRAY_76;
			case _I(G,R,A,Y, ,7,6):
				return alpha | X11_GRAY_76;
			case _I(G,R,E,Y,7,6):
				return alpha | X11_GREY_76;
			case _I(G,R,E,Y,_,7,6):
				return alpha | X11_GREY_76;
			case _I(G,R,E,Y, ,7,6):
				return alpha | X11_GREY_76;
			case _I(G,R,A,Y,7,7):
				return alpha | X11_GRAY_77;
			case _I(G,R,A,Y,_,7,7):
				return alpha | X11_GRAY_77;
			case _I(G,R,A,Y, ,7,7):
				return alpha | X11_GRAY_77;
			case _I(G,R,E,Y,7,7):
				return alpha | X11_GREY_77;
			case _I(G,R,E,Y,_,7,7):
				return alpha | X11_GREY_77;
			case _I(G,R,E,Y, ,7,7):
				return alpha | X11_GREY_77;
			case _I(G,R,A,Y,7,8):
				return alpha | X11_GRAY_78;
			case _I(G,R,A,Y,_,7,8):
				return alpha | X11_GRAY_78;
			case _I(G,R,A,Y, ,7,8):
				return alpha | X11_GRAY_78;
			case _I(G,R,E,Y,7,8):
				return alpha | X11_GREY_78;
			case _I(G,R,E,Y,_,7,8):
				return alpha | X11_GREY_78;
			case _I(G,R,E,Y, ,7,8):
				return alpha | X11_GREY_78;
			case _I(G,R,A,Y,7,9):
				return alpha | X11_GRAY_79;
			case _I(G,R,A,Y,_,7,9):
				return alpha | X11_GRAY_79;
			case _I(G,R,A,Y, ,7,9):
				return alpha | X11_GRAY_79;
			case _I(G,R,E,Y,7,9):
				return alpha | X11_GREY_79;
			case _I(G,R,E,Y,_,7,9):
				return alpha | X11_GREY_79;
			case _I(G,R,E,Y, ,7,9):
				return alpha | X11_GREY_79;
			case _I(G,R,A,Y,8,0):
				return alpha | X11_GRAY_80;
			case _I(G,R,A,Y,_,8,0):
				return alpha | X11_GRAY_80;
			case _I(G,R,A,Y, ,8,0):
				return alpha | X11_GRAY_80;
			case _I(G,R,E,Y,8,0):
				return alpha | X11_GREY_80;
			case _I(G,R,E,Y,_,8,0):
				return alpha | X11_GREY_80;
			case _I(G,R,E,Y, ,8,0):
				return alpha | X11_GREY_80;
			case _I(G,R,A,Y,8,1):
				return alpha | X11_GRAY_81;
			case _I(G,R,A,Y,_,8,1):
				return alpha | X11_GRAY_81;
			case _I(G,R,A,Y, ,8,1):
				return alpha | X11_GRAY_81;
			case _I(G,R,E,Y,8,1):
				return alpha | X11_GREY_81;
			case _I(G,R,E,Y,_,8,1):
				return alpha | X11_GREY_81;
			case _I(G,R,E,Y, ,8,1):
				return alpha | X11_GREY_81;
			case _I(G,R,A,Y,8,2):
				return alpha | X11_GRAY_82;
			case _I(G,R,A,Y,_,8,2):
				return alpha | X11_GRAY_82;
			case _I(G,R,A,Y, ,8,2):
				return alpha | X11_GRAY_82;
			case _I(G,R,E,Y,8,2):
				return alpha | X11_GREY_82;
			case _I(G,R,E,Y,_,8,2):
				return alpha | X11_GREY_82;
			case _I(G,R,E,Y, ,8,2):
				return alpha | X11_GREY_82;
			case _I(G,R,A,Y,8,3):
				return alpha | X11_GRAY_83;
			case _I(G,R,A,Y,_,8,3):
				return alpha | X11_GRAY_83;
			case _I(G,R,A,Y, ,8,3):
				return alpha | X11_GRAY_83;
			case _I(G,R,E,Y,8,3):
				return alpha | X11_GREY_83;
			case _I(G,R,E,Y,_,8,3):
				return alpha | X11_GREY_83;
			case _I(G,R,E,Y, ,8,3):
				return alpha | X11_GREY_83;
			case _I(G,R,A,Y,8,4):
				return alpha | X11_GRAY_84;
			case _I(G,R,A,Y,_,8,4):
				return alpha | X11_GRAY_84;
			case _I(G,R,A,Y, ,8,4):
				return alpha | X11_GRAY_84;
			case _I(G,R,E,Y,8,4):
				return alpha | X11_GREY_84;
			case _I(G,R,E,Y,_,8,4):
				return alpha | X11_GREY_84;
			case _I(G,R,E,Y, ,8,4):
				return alpha | X11_GREY_84;
			case _I(G,R,A,Y,8,5):
				return alpha | X11_GRAY_85;
			case _I(G,R,A,Y,_,8,5):
				return alpha | X11_GRAY_85;
			case _I(G,R,A,Y, ,8,5):
				return alpha | X11_GRAY_85;
			case _I(G,R,E,Y,8,5):
				return alpha | X11_GREY_85;
			case _I(G,R,E,Y,_,8,5):
				return alpha | X11_GREY_85;
			case _I(G,R,E,Y, ,8,5):
				return alpha | X11_GREY_85;
			case _I(G,R,A,Y,8,6):
				return alpha | X11_GRAY_86;
			case _I(G,R,A,Y,_,8,6):
				return alpha | X11_GRAY_86;
			case _I(G,R,A,Y, ,8,6):
				return alpha | X11_GRAY_86;
			case _I(G,R,E,Y,8,6):
				return alpha | X11_GREY_86;
			case _I(G,R,E,Y,_,8,6):
				return alpha | X11_GREY_86;
			case _I(G,R,E,Y, ,8,6):
				return alpha | X11_GREY_86;
			case _I(G,R,A,Y,8,7):
				return alpha | X11_GRAY_87;
			case _I(G,R,A,Y,_,8,7):
				return alpha | X11_GRAY_87;
			case _I(G,R,A,Y, ,8,7):
				return alpha | X11_GRAY_87;
			case _I(G,R,E,Y,8,7):
				return alpha | X11_GREY_87;
			case _I(G,R,E,Y,_,8,7):
				return alpha | X11_GREY_87;
			case _I(G,R,E,Y, ,8,7):
				return alpha | X11_GREY_87;
			case _I(G,R,A,Y,8,8):
				return alpha | X11_GRAY_88;
			case _I(G,R,A,Y,_,8,8):
				return alpha | X11_GRAY_88;
			case _I(G,R,A,Y, ,8,8):
				return alpha | X11_GRAY_88;
			case _I(G,R,E,Y,8,8):
				return alpha | X11_GREY_88;
			case _I(G,R,E,Y,_,8,8):
				return alpha | X11_GREY_88;
			case _I(G,R,E,Y, ,8,8):
				return alpha | X11_GREY_88;
			case _I(G,R,A,Y,8,9):
				return alpha | X11_GRAY_89;
			case _I(G,R,A,Y,_,8,9):
				return alpha | X11_GRAY_89;
			case _I(G,R,A,Y, ,8,9):
				return alpha | X11_GRAY_89;
			case _I(G,R,E,Y,8,9):
				return alpha | X11_GREY_89;
			case _I(G,R,E,Y,_,8,9):
				return alpha | X11_GREY_89;
			case _I(G,R,E,Y, ,8,9):
				return alpha | X11_GREY_89;
			case _I(G,R,A,Y,9,0):
				return alpha | X11_GRAY_90;
			case _I(G,R,A,Y,_,9,0):
				return alpha | X11_GRAY_90;
			case _I(G,R,A,Y, ,9,0):
				return alpha | X11_GRAY_90;
			case _I(G,R,E,Y,9,0):
				return alpha | X11_GREY_90;
			case _I(G,R,E,Y,_,9,0):
				return alpha | X11_GREY_90;
			case _I(G,R,E,Y, ,9,0):
				return alpha | X11_GREY_90;
			case _I(G,R,A,Y,9,1):
				return alpha | X11_GRAY_91;
			case _I(G,R,A,Y,_,9,1):
				return alpha | X11_GRAY_91;
			case _I(G,R,A,Y, ,9,1):
				return alpha | X11_GRAY_91;
			case _I(G,R,E,Y,9,1):
				return alpha | X11_GREY_91;
			case _I(G,R,E,Y,_,9,1):
				return alpha | X11_GREY_91;
			case _I(G,R,E,Y, ,9,1):
				return alpha | X11_GREY_91;
			case _I(G,R,A,Y,9,2):
				return alpha | X11_GRAY_92;
			case _I(G,R,A,Y,_,9,2):
				return alpha | X11_GRAY_92;
			case _I(G,R,A,Y, ,9,2):
				return alpha | X11_GRAY_92;
			case _I(G,R,E,Y,9,2):
				return alpha | X11_GREY_92;
			case _I(G,R,E,Y,_,9,2):
				return alpha | X11_GREY_92;
			case _I(G,R,E,Y, ,9,2):
				return alpha | X11_GREY_92;
			case _I(G,R,A,Y,9,3):
				return alpha | X11_GRAY_93;
			case _I(G,R,A,Y,_,9,3):
				return alpha | X11_GRAY_93;
			case _I(G,R,A,Y, ,9,3):
				return alpha | X11_GRAY_93;
			case _I(G,R,E,Y,9,3):
				return alpha | X11_GREY_93;
			case _I(G,R,E,Y,_,9,3):
				return alpha | X11_GREY_93;
			case _I(G,R,E,Y, ,9,3):
				return alpha | X11_GREY_93;
			case _I(G,R,A,Y,9,4):
				return alpha | X11_GRAY_94;
			case _I(G,R,A,Y,_,9,4):
				return alpha | X11_GRAY_94;
			case _I(G,R,A,Y, ,9,4):
				return alpha | X11_GRAY_94;
			case _I(G,R,E,Y,9,4):
				return alpha | X11_GREY_94;
			case _I(G,R,E,Y,_,9,4):
				return alpha | X11_GREY_94;
			case _I(G,R,E,Y, ,9,4):
				return alpha | X11_GREY_94;
			case _I(G,R,A,Y,9,5):
				return alpha | X11_GRAY_95;
			case _I(G,R,A,Y,_,9,5):
				return alpha | X11_GRAY_95;
			case _I(G,R,A,Y, ,9,5):
				return alpha | X11_GRAY_95;
			case _I(G,R,E,Y,9,5):
				return alpha | X11_GREY_95;
			case _I(G,R,E,Y,_,9,5):
				return alpha | X11_GREY_95;
			case _I(G,R,E,Y, ,9,5):
				return alpha | X11_GREY_95;
			case _I(G,R,A,Y,9,6):
				return alpha | X11_GRAY_96;
			case _I(G,R,A,Y,_,9,6):
				return alpha | X11_GRAY_96;
			case _I(G,R,A,Y, ,9,6):
				return alpha | X11_GRAY_96;
			case _I(G,R,E,Y,9,6):
				return alpha | X11_GREY_96;
			case _I(G,R,E,Y,_,9,6):
				return alpha | X11_GREY_96;
			case _I(G,R,E,Y, ,9,6):
				return alpha | X11_GREY_96;
			case _I(G,R,A,Y,9,7):
				return alpha | X11_GRAY_97;
			case _I(G,R,A,Y,_,9,7):
				return alpha | X11_GRAY_97;
			case _I(G,R,A,Y, ,9,7):
				return alpha | X11_GRAY_97;
			case _I(G,R,E,Y,9,7):
				return alpha | X11_GREY_97;
			case _I(G,R,E,Y,_,9,7):
				return alpha | X11_GREY_97;
			case _I(G,R,E,Y, ,9,7):
				return alpha | X11_GREY_97;
			case _I(G,R,A,Y,9,8):
				return alpha | X11_GRAY_98;
			case _I(G,R,A,Y,_,9,8):
				return alpha | X11_GRAY_98;
			case _I(G,R,A,Y, ,9,8):
				return alpha | X11_GRAY_98;
			case _I(G,R,E,Y,9,8):
				return alpha | X11_GREY_98;
			case _I(G,R,E,Y,_,9,8):
				return alpha | X11_GREY_98;
			case _I(G,R,E,Y, ,9,8):
				return alpha | X11_GREY_98;
			case _I(G,R,A,Y,9,9):
				return alpha | X11_GRAY_99;
			case _I(G,R,A,Y,_,9,9):
				return alpha | X11_GRAY_99;
			case _I(G,R,A,Y, ,9,9):
				return alpha | X11_GRAY_99;
			case _I(G,R,E,Y,9,9):
				return alpha | X11_GREY_99;
			case _I(G,R,E,Y,_,9,9):
				return alpha | X11_GREY_99;
			case _I(G,R,E,Y, ,9,9):
				return alpha | X11_GREY_99;
			case _I(G,R,A,Y,1,0,0):
				return alpha | X11_GRAY_100;
			case _I(G,R,A,Y,_,1,0,0):
				return alpha | X11_GRAY_100;
			case _I(G,R,A,Y, ,1,0,0):
				return alpha | X11_GRAY_100;
			case _I(G,R,E,Y,1,0,0):
				return alpha | X11_GREY_100;
			case _I(G,R,E,Y,_,1,0,0):
				return alpha | X11_GREY_100;
			case _I(G,R,E,Y, ,1,0,0):
				return alpha | X11_GREY_100;
			case _I(D,A,R,K,G,R,E,Y):
				return alpha | X11_DARK_GREY;
			case _I(D,A,R,K,_,G,R,E,Y):
				return alpha | X11_DARK_GREY;
			case _I(D,A,R,K, ,G,R,E,Y):
				return alpha | X11_DARK_GREY;
			case _I(D,A,R,K,G,R,A,Y):
				return alpha | X11_DARK_GRAY;
			case _I(D,A,R,K,_,G,R,A,Y):
				return alpha | X11_DARK_GRAY;
			case _I(D,A,R,K, ,G,R,A,Y):
				return alpha | X11_DARK_GRAY;
			case _I(D,A,R,K,B,L,U,E):
				return alpha | X11_DARK_BLUE;
			case _I(D,A,R,K,_,B,L,U,E):
				return alpha | X11_DARK_BLUE;
			case _I(D,A,R,K, ,B,L,U,E):
				return alpha | X11_DARK_BLUE;
			case _I(D,A,R,K,C,Y,A,N):
				return alpha | X11_DARK_CYAN;
			case _I(D,A,R,K,_,C,Y,A,N):
				return alpha | X11_DARK_CYAN;
			case _I(D,A,R,K, ,C,Y,A,N):
				return alpha | X11_DARK_CYAN;
			case _I(D,A,R,K,M,A,G,E,N,T,A):
				return alpha | X11_DARK_MAGENTA;
			case _I(D,A,R,K,_,M,A,G,E,N,T,A):
				return alpha | X11_DARK_MAGENTA;
			case _I(D,A,R,K, ,M,A,G,E,N,T,A):
				return alpha | X11_DARK_MAGENTA;
			case _I(D,A,R,K,R,E,D):
				return alpha | X11_DARK_RED;
			case _I(D,A,R,K,_,R,E,D):
				return alpha | X11_DARK_RED;
			case _I(D,A,R,K, ,R,E,D):
				return alpha | X11_DARK_RED;
			case _I(L,I,G,H,T,G,R,E,E,N):
				return alpha | X11_LIGHT_GREEN;
			case _I(L,I,G,H,T,_,G,R,E,E,N):
				return alpha | X11_LIGHT_GREEN;
			case _I(L,I,G,H,T, ,G,R,E,E,N):
				return alpha | X11_LIGHT_GREEN;*/
		}
