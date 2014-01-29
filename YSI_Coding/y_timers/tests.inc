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

