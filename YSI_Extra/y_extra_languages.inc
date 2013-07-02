// Include pretty much 90% of YSI in one fell swoop!

loadtext core[ysi_langs];

YCMD:language(playerid, params[], help)
{
	if (help)
	{
		Text_Send(playerid, $YSI_LANGS_HELP);
	}
	else
	{
		new
			lang;
		if (sscanf(params, "i", lang))
		{
			new
				c = _:Langs_GetLanguageCount(),
				Language:i = Language:0;
			while (c)
			{
				new
					code[3];
				strcpy(code, Langs_GetCode(i));
				if (!isnull(code))
				{
					// They may not be in order.
					Text_Send(playerid, $YSI_LANGS_DISP, _:i, Langs_GetName(i), code);
					--c;
				}
				++i;
			}
			Text_Send(playerid, $YSI_LANGS_SET, YCMD:language);
		}
		else if (Langs_SetPlayerLanguage(playerid, Language:lang) == NO_LANGUAGE)
		{
			Text_Send(playerid, $YSI_LANGS_INV);
		}
		else
		{
			Text_Send(playerid, $YSI_LANGS_DONE, lang, Langs_GetName(Language:lang));
		}
	}
	return 1;
}
