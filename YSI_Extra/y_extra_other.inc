// Include pretty much 90% of YSI in one fell swoop!

loadtext core[ysi_commands], core[ysi_help];

YCMD:commands(playerid, params[], help)
{
    if (help)
    {
        Text_Send(playerid, $YSI_COMM_HELP);
    }
    else
    {
        new
            count = Command_GetPlayerCommandCount(playerid);
        for (new i = 0; i != count; ++i)
        {
            Text_Send(playerid, $YSI_COMM_LIST, Command_GetNext(i, playerid));
        }
    }
    return 1;
}

YCMD:help(playerid, params[], help)
{
    if (help)
    {
        Text_Send(playerid, $YSI_HELP);
    }
    else
    {
        if (isnull(params))
        {
            Text_Send(playerid, $YSI_HELP);
        }
        else
        {
            Command_ReProcess(playerid, params, true);
        }
    }
    return 1;
}
