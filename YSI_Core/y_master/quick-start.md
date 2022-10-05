# Quick Start

Imagine the following setup:

You have four developers, each with their own area of responsibility (mapping should, of course, be loaded at run-time, so isn't covered here):

* *Tom* - Job system and races.
* *Kate* - Vehicles and VIP rewards.
* *Jo* - Mini-missions.
* *xX_h4cker_gUr1_69_Xx* - Phones, admin commands, and minor systems.

All of a sudden, you discover that *xX_h4cker_gUr1_69_Xx* can't be trusted, after they quit and steal your code.  There are three possibilities:

1. Your code is a single monolithic file.  This is just stupid regardless of who tries to steal it.  Frankly you probably don't deserve it.

2. Your code is nicely split up, but all stored in one repository all your devs have complete access to.  *xX_h4cker_gUr1_69_Xx* gets away with the whole thing.

3. You are using y_master, so they can only steal their bits of the code and a few binary blobs (filterscripts).

So how does that work?  Each scripter has their own area of responsibility, and that code is stored in a small repo that only they and your central build server have access to.  When they make changes to their code, they use the following code to build a small filterscript (seen from *Tom's* view):

## tom.pwn

```pawn
#define JOB_MASTER 1
#define RACE_MASTER 1
#define VEHICLE_MASTER 0
#define VIP_MASTER 0
#define MM_MASTER 0
#define PHONE_MASTER 0
#define ADMIN_MASTER 0

#define FILTERSCRIPT // Just in case.

#include <a_samp>
#undef MAX_PLAYERS
#define MAX_PLAYERS 5 // Purely for small test servers.

// External includes go here.
#include <YSI_Core\y_master>

#include <mode\jobs>
#include <mode\races>
#include <mode\vehicles>
#include <mode\vip>
#include <mode\minimodes>
#include <mode\phone>
#include <mode\admin>
```

Everyone has the included files, but they don't contain the bulk of the source.  Instead they look like this:

## jobs.inc

```pawn
#if JOB_MASTER
  #define YSIM_S_ENABLE // Make this script in charge of jobs.
#else
  #define YSIM_U_ENABLE // The code is in another script entirely.
#endif

#define MASTER 4 // Unique value < 28 for the jobs system.
#include <YSI_Core\y_master> // Again.

// "forward" the functions here:
foreign JobID:GetCurrentJob(playerid);
foreign JobID:CreateJob(string:name[]); // Can also return `string:`.
foreign bool:IsPlayerInJob(playerid, JobID:jobid);
foreign void:DestroyJob(JobID:jobid); // Returns nothing (`void:`).

#if JOB_MASTER
  // We need the implementation.
  #include "jobs\detail"
#endif
```

Then Tom can implement the functions:

## jobs/detail.inc

```pawn
global JobID:GetCurrentJob(playerid)
{
  // Whatever...
  return JobID:55;
}

global bool:IsPlayerInJob(playerid, JobID:jobid)
{
  return _:jobid == 55 && IsPlayerVIP(playerid);
}

// More functions here...
```

When *Tom* compiles this script, he gets a very limited filterscript (5 max players) with all the job system built in.  Note that the example called `IsPlayerVIP`, which is *Kate's* responsibility and thus in a different script, but this code doesn't care where it is - you just call it like a normal function.  This limited filterscript is almost useless to a server - you can't run a full server with only 5 players, but you can do basic testing with 5 players.  Now Tom sends this filterscript to the other developers (or puts it in shared source control with the stub (non-`detail.inc`) includes that everyone has).  When they run a server, they build their own code normally and load *Tom's* filterscript.  Calling *Tom's* functions looks like a normal call, but will execute them in the filterscript instead.  So other developers have full access to these functions without the source code.

When you want to build the main mode that will go on your live server, this is done by a central build server.  No one person has access to all the code, only this build server can see everything.  That instead uses this script as an entry point:

## full.pwn

```pawn
// Totally disable all remote calls.
#define YSI_NO_MASTER 

// Compile all systems in to one AMX.
#define JOB_MASTER 1
#define RACE_MASTER 1
#define VEHICLE_MASTER 1
#define VIP_MASTER 1
#define MM_MASTER 1
#define PHONE_MASTER 1
#define ADMIN_MASTER 1

// Don't redefine `MAX_PLAYERS` (or do, to some better number).
#include <a_samp>

// External includes go here.
#include <YSI_Core\y_master>

// All these includes remain the same.
#include <mode\jobs>
#include <mode\races>
#include <mode\vehicles>
#include <mode\vip>
#include <mode\minimodes>
#include <mode\phone>
#include <mode\admin>
```

So when *xX_h4cker_gUr1_69_Xx* decides to steal your code, they can only steal a small bit of it from the repos they had access to, along with some shared headers and compiled filterscripts that can only handle 5 players.  This is totally useless for running a server.  You can even go further with the filterscripts and include anti-deamx and y_lock:

## tom-protected.pwn

```pawn
// ...
#define FILTERSCRIPT // Just in case.
public AntiDeAMX()
{
  // Whatever.
}

#include <YSI_Server\y_lock>
// ...
```

This will make it almost impossible to decompile (YSI also does a pretty good job of that), and *y_lock* means you need the following line in `server.cfg`:

```
bind 127.0.0.1
```

So now, all they stole was a 5 player server they can only run locally and can't decompile.  Meanwhile, your central build server compiles the whole script with normal function calls and thus zero overhead for a full working script.
