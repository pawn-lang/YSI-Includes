#### SetMaxConnections
>* **Parameters:**
>	* `max`: max_INFO
>	* `e_FLOOD_ACTION:action`: e_FLOOD_ACTION:action_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Sets the maximum connections allowed from a single IP.
>	Options:
>	e_FLOOD_ACTION_BLOCK - Kick the latest player on this IP.
>	e_FLOOD_ACTION_KICK - Kick all players on this IP.
>	e_FLOOD_ACTION_BAN - Ban the IP and have players time out.
>	e_FLOOD_ACTION_FBAN - Ban the IP and kick all the players instantly.
>	e_FLOOD_ACTION_GHOST - Silently force all players on the IP to reconnect.
>	e_FLOOD_ACTION_OTHER - Call a callback.
 
***

#### Flooding_UnbanIP
>* **Parameters:**
>	* `ip32`: ip32_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Timers, by default, are not good with strings, so we can't pass the IP to
>	unban in dot notation.  Fortunately, this is easilly solved.
 
***

#### OnPlayerConnect
>* **Parameters:**
>	* `playerid`: playerid_INFO
>* **Returns:**
>	* -
>* **Remarks:**
>	Checks for too many connections from the same IP address and acts
>	accordingly.
>	Could be edited to only loop through players once but I'm not sure the
>	extra code required would be faster anyway, definately not easier.
 
***

