## Check Timer Is Running

```pawn
	new Timer:t = defer TestTimer();
	if (Timer_IsRunning(t))
	{
	}
```

## Stop Repeatedly

```pawn
	new Timer:t = defer TestTimer();
	stop t;
	stop t;
	stop t;
	stop t;
```

