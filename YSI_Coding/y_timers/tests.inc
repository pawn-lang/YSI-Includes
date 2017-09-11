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

#tryinclude "y_hooks"
#tryinclude "..\y_hooks"

static stock
	sgPlayerCounter[MAX_PLAYERS];

hook OnPlayerConnect(playerid)
{
	sgPlayerCounter[playerid] = 0;
}

ptask y_timers_PCounter[1000](playerid)
{
	// What an odd bug!  Putting this in a format breaks the format!
	++sgPlayerCounter[playerid];
	//printf("playerid: %d, %d", playerid, sgPlayerCounter[playerid]);
	//new
	//	b = sgPlayerCounter[playerid];
	//printf("playerid: %d, %d", playerid, b);
	va_SendClientMessage(playerid, 0xFF0000AA, "PLAYER COUNTER: %d", sgPlayerCounter[playerid]);
}

task y_timers_Counter[1000]()
{
	static
		sCounter = 0;
	va_SendClientMessageToAll(0x0000FFAA, "GLOBAL COUNTER: %d", sCounter++);
}

PTest:PCounter1(playerid)
{
	ASK("Is the red PLAYER COUNTER going up?");
}

PTest:PCounter2(playerid)
{
	pause y_timers_PCounter[playerid];
	ASK("Has the red PLAYER COUNTER stopped?");
}

PTest:Counter(playerid)
{
	ASK("Is the blue GLOBAL COUNTER going up?");
}

timer BigMessage1[4000](playerid)
{
	SendClientMessage(playerid, 0x00FF00AA, "BIG MESSAGE appearing once.");
}

timer BigMessage2[4000](playerid)
{
	SendClientMessage(playerid, 0x00FF00AA, "BIG MESSAGE appearing repeatedly.");
}

PTest:Timer1(playerid)
{
	defer BigMessage1(playerid);
	ASK("Is a green BIG MESSAGE appearing once after 4 seconds?");
}

static
	Timer:sgTimer;

PTest:Timer2(playerid)
{
	sgTimer = repeat BigMessage2(playerid);
	ASK("Is a green BIG MESSAGE appearing every 4 seconds?");
}

timer StopMessage1[4000](playerid)
{
	SendClientMessage(playerid, 0x00FF00AA, "BIG MESSAGE should stop now.");
	stop sgTimer;
}

PTest:Timer3(playerid)
{
	defer StopMessage1(playerid);
	ASK("Is the green BIG MESSAGE stopping appearing after 4 seconds?");
}

#tryinclude "y_hooks"
#tryinclude "..\y_hooks"

