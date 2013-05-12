SA-MP Anticheat
===============

This library provides protection against popular hacks.

Building
--------

You can build this library using the Python utility located in `pawncc/builder.py`. This utility merges all components in one single file.
Sample of usage: `pawncc/builder.py ./src ./Anticheat.inc`

Installation
------------

For this library to run normally it requires a __master script__. The master script represents the place where data is handled and the actual cheat detection process occurs. Additionally, if there is more than one script that modifies vital information the anticheat must be included in those aswell. Those scripts are called __slave scripts__. 

__WARNING!__ If there is more than one master instance per server the server might report players that aren't actually cheating.

1.    Include the Anticheat in your script:
	*	__Master (core)__:
	
			#define ANTICHEAT_MASTER
			#include <Anticheat>
	*	__Slave__: 
	
			#define ANTICHEAT_SLAVE
			#include <Anticheat>
2.	Compile your script.

<sup>_For more advanced information about this library, please read [NOTES.md](https://github.com/udan11/samp-anticheat/blob/master/NOTES.md)._</sup>