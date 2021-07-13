#include "y_interiors_decl"// decl-arations

/*

                                                              
88        88                            88                    
88        88                            88                    
88        88                            88                    
88aaaaaaaa88   ,adPPYba,    ,adPPYba,   88   ,d8   ,adPPYba,  
88""""""""88  a8"     "8a  a8"     "8a  88 ,a8"    I8[    ""  
88        88  8b       d8  8b       d8  8888[       `"Y8ba,   
88        88  "8a,   ,a8"  "8a,   ,a8"  88`"Yba,   aa    ]8I  
88        88   `"YbbdP"'    `"YbbdP"'   88   `Y8a  `"YbbdP"'  
                                                              
                                                              

*/

#define YSI_INTERIORS_TRUE 1
#define YSI_INTERIORS_FALSE 0

#define YSI_INTERIOR_ACTION_ENTER 0
#define YSI_INTERIOR_ACTION_EXIT 1

gYSI_InteriorLoadingTime(const playerid)
{
	TogglePlayerControllable(playerid,true);
}

YSI_OnPlayerNearEntrance(playerid);
public YSI_OnPlayerNearEntrance(playerid)
{
	new YSI_InteriorFunctionName[100];
	new YSI_InteriorActionid;
    TogglePlayerControllable(playerid,false);
	for(new i; i < MAX_INTERIORS; i++)
	{
		if( IsPlayerInRangeOfPoint( playerid, 1.5, gYSI_InteriorData[ i ][e_YSI_INTENTRANCE_X], \
		gYSI_InteriorData[ i ][e_YSI_INTENTRANCE_Y], gYSI_InteriorData[ i ][e_YSI_INTENTRANCE_Z]) \
		&& GetPlayerVirtualWorld( playerid ) == gYSI_InteriorData[ i ][e_YSI_INTERIOR_VWID_OUT] \
		&& !IsPlayerInAnyVehicle( playerid ))
		{
			YSI_InteriorActionid = 0;
			format(YSI_InteriorFunctionName,sizeof(YSI_InteriorFunctionName),
				"%s@_yI",gYSI_InteriorData[ i ][e_YSI_INTERIOR_NAME]);

			if(funcidx(YSI_InteriorFunctionName) != -1) CallLocalFunction(YSI_InteriorFunctionName,"ii",playerid,YSI_InteriorActionid);

			SetPlayerInterior( playerid, gYSI_InteriorData[ i ][e_YSI_INTERIOR_INTID] );
			SetPlayerVirtualWorld( playerid, gYSI_InteriorData[ i ][e_YSI_INTERIOR_VWID] );
			
			SetPlayerPos( playerid, gYSI_InteriorData[ i ][e_YSI_INTEXIT_X], gYSI_InteriorData[ i ][e_YSI_INTEXIT_Y], \
			gYSI_InteriorData[ i ][e_YSI_INTEXIT_Z] );
			
			SetPlayerFacingAngle( playerid, gYSI_InteriorData[ i ][e_YSI_INTEXIT_A] );
			SetCameraBehindPlayer( playerid );
			
			SetPlayerTime( playerid, 12, 0 );
			gYSI_InteriorLoadingTime(playerid);
			
		    gYSI_PlayersInterior[ playerid ] = i;
			
		}
		else if( IsPlayerInRangeOfPoint( playerid, 1.5, gYSI_InteriorData[ i ][e_YSI_INTEXIT_X], \
		gYSI_InteriorData[ i ][e_YSI_INTEXIT_Y], gYSI_InteriorData[ i ][e_YSI_INTEXIT_Z]) && \
		GetPlayerVirtualWorld( playerid ) == gYSI_InteriorData[ i ][e_YSI_INTERIOR_VWID])
		{
		    SetPlayerVirtualWorld( playerid, gYSI_InteriorData[ i ][e_YSI_INTERIOR_VWID_OUT] );
		    SetPlayerInterior( playerid, gYSI_InteriorData[ i ][e_YSI_INTERIOR_INTID_OUT] );
			
		    SetPlayerPos( playerid, gYSI_InteriorData[ i ][e_YSI_INTENTRANCE_X], gYSI_InteriorData[ i ][e_YSI_INTENTRANCE_Y], \
			gYSI_InteriorData[ i ][e_YSI_INTENTRANCE_Z] );
			
		    SetPlayerFacingAngle( playerid, gYSI_InteriorData[ i ][e_YSI_INTENTRANCE_A] );
		    SetCameraBehindPlayer( playerid );
			gYSI_InteriorLoadingTime(playerid);

			YSI_InteriorActionid = 1;
			format(YSI_InteriorFunctionName,sizeof(YSI_InteriorFunctionName),
				"%s@_yI",gYSI_InteriorData[ i ][e_YSI_INTERIOR_NAME]);

			if(funcidx(YSI_InteriorFunctionName) != -1) CallLocalFunction(YSI_InteriorFunctionName,"ii",playerid,YSI_InteriorActionid);

		    gYSI_PlayersInterior[ playerid ] = -1;
		}
    }
    return YSI_INTERIORS_TRUE;
}

hook OnPlayerDisconnect(playerid, reason)
{
	Interiors_ClearPlayerInteriorData(playerid);
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if( newkeys == KEY_SECONDARY_ATTACK)
	{
        if(GetPlayerState(playerid) == 1)
		{
			YSI_OnPlayerNearEntrance(playerid);
		}

        if( GetPlayerSpecialAction(playerid ) != SPECIAL_ACTION_NONE && \
		GetPlayerSpecialAction(playerid ) != SPECIAL_ACTION_CUFFED)
		{
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        }
	}
	return 1;
}

hook OnPlayerUpdate(playerid)
{
	for(new i; i < MAX_INTERIORS; i++)
	{
		if( IsPlayerInRangeOfPoint( playerid, 1.5, gYSI_InteriorData[ i ][e_YSI_INTENTRANCE_X], \
		gYSI_InteriorData[ i ][e_YSI_INTENTRANCE_Y], gYSI_InteriorData[ i ][e_YSI_INTENTRANCE_Z]) \
		&& GetPlayerVirtualWorld( playerid ) == gYSI_InteriorData[ i ][e_YSI_INTERIOR_VWID_OUT] \
		&& !IsPlayerInAnyVehicle( playerid ))
		{
			new YSI_InteriorName[100];
			format(YSI_InteriorName,sizeof(YSI_InteriorName),"Property: %s",gYSI_InteriorData[ i ][ e_YSI_INTERIOR_NAME ]);
			
			GameTextForPlayer(playerid, YSI_InteriorName, 5000, 2);
		}
	}
	return 1;
}

/*

                                                                                      
88b           d88              88                         db         88888888ba   88  
888b         d888              ""                        d88b        88      "8b  88  
88`8b       d8'88                                       d8'`8b       88      ,8P  88  
88 `8b     d8' 88  ,adPPYYba,  88  8b,dPPYba,          d8'  `8b      88aaaaaa8P'  88  
88  `8b   d8'  88  ""     `Y8  88  88P'   `"8a        d8YaaaaY8b     88""""""'    88  
88   `8b d8'   88  ,adPPPPP88  88  88       88       d8""""""""8b    88           88  
88    `888'    88  88,    ,88  88  88       88      d8'        `8b   88           88  
88     `8'     88  `"8bbdP"Y8  88  88       88     d8'          `8b  88           88  
                                                                                      
                                                                                      

*/

stock Interiors_Create3DLabelAndPickup( 
		const YSI_LabelString[], 
		Float:YSI_xPosition, 
		Float:YSI_yPosition, 
		Float:YSI_zPosition, 
		YSI_Interior, 
		YSI_VirtualWorld, 
		YSI_Pickupid, 
		Float:YSI_LabelRadius ) 
{
	if(isnull(YSI_LabelString))
		return YSI_INTERIORS_FALSE;

	if(YSI_Interior < 0)
		return YSI_INTERIORS_FALSE;

	if(YSI_VirtualWorld < 0)
		return YSI_INTERIORS_FALSE;

	if(YSI_LabelRadius <= 0)
		return YSI_INTERIORS_FALSE;

	if(YSI_Pickupid < 0)
		return YSI_INTERIORS_FALSE;

	CreateDynamic3DTextLabel(
							YSI_LabelString, 
							0x0059FFAA, 
							YSI_xPosition, 
							YSI_yPosition, 
							YSI_zPosition, 
							YSI_LabelRadius, 
							INVALID_PLAYER_ID, 
							INVALID_VEHICLE_ID, 
							0, 
							YSI_VirtualWorld, 
							YSI_Interior, 
							-1, 
							20.0);
	CreateDynamicPickup(
					YSI_Pickupid, 
					1, 
					YSI_xPosition, 
					YSI_yPosition, 
					YSI_zPosition, 
					YSI_VirtualWorld, 
					YSI_Interior);
	return YSI_INTERIORS_TRUE;
}

stock Interiors_CreateInterior(
		const YSI_InteriorName[], 
		Float:YSI_xEntrance, 
		Float:YSI_yEntrance, 
		Float:YSI_zEntrance, 
		Float:YSI_xExit, 
		Float:YSI_yExit, 
		Float:YSI_zExit, 
		YSI_eInteriorid, 
		YSI_xInteriorid, 
		YSI_eVirtualWorldid, 
		YSI_xVirtualWorldid)
{
	printf("Interior '%s' successfully created, entrance is set to: %f, %f, %f.",
			YSI_InteriorName,
			Float:YSI_xEntrance, 
			Float:YSI_yEntrance, 
			Float:YSI_zEntrance);

	gYSI_Interiorid++;

	strmid(gYSI_InteriorData[gYSI_Interiorid][e_YSI_INTERIOR_NAME], 
			YSI_InteriorName, 
			0, 
			strlen(YSI_InteriorName), 
			255);

	printf("Interior '%s' has an id %d.",YSI_InteriorName,gYSI_Interiorid);
	gYSI_InteriorData[gYSI_Interiorid][e_YSI_INTENTRANCE_X] = YSI_xEntrance;
	gYSI_InteriorData[gYSI_Interiorid][e_YSI_INTENTRANCE_Y] = YSI_yEntrance;
	gYSI_InteriorData[gYSI_Interiorid][e_YSI_INTENTRANCE_Z] = YSI_zEntrance;
	gYSI_InteriorData[gYSI_Interiorid][e_YSI_INTEXIT_X] = YSI_xExit;
	gYSI_InteriorData[gYSI_Interiorid][e_YSI_INTEXIT_Y] = YSI_yExit;
	gYSI_InteriorData[gYSI_Interiorid][e_YSI_INTEXIT_Z] = YSI_zExit;
	gYSI_InteriorData[gYSI_Interiorid][e_YSI_INTERIOR_INTID] = YSI_eInteriorid;
	gYSI_InteriorData[gYSI_Interiorid][e_YSI_INTERIOR_INTID_OUT] = YSI_xInteriorid;
	gYSI_InteriorData[gYSI_Interiorid][e_YSI_INTERIOR_VWID] = YSI_eVirtualWorldid;
	gYSI_InteriorData[gYSI_Interiorid][e_YSI_INTERIOR_VWID_OUT] = YSI_xVirtualWorldid;

	new YSI_EntranceLabelString[300];
	format(YSI_EntranceLabelString,sizeof(YSI_EntranceLabelString),"{ffffff}[ %s ]\n"col_white"Enter here!",YSI_InteriorName);

	Interiors_Create3DLabelAndPickup(YSI_EntranceLabelString, YSI_xEntrance,YSI_yEntrance,YSI_zEntrance, -1, -1, 19133, 2.0);

	Interiors_Create3DLabelAndPickup("Exit here!", YSI_xExit,YSI_yExit,YSI_zExit, -1, -1, 19133, 2.0);
	return YSI_INTERIORS_TRUE;
}

stock bool:Interiors_IsPlayerInInterior(playerid)
{
	if(gYSI_PlayersInterior[ playerid ] = -1) return false;
	else return true;
}

stock Interiors_ClearPlayerInteriorData(playerid)
{
	gYSI_PlayersInterior[playerid] = -1;
	return YSI_INTERIORS_TRUE;
}

stock Interiors_SetInteriorAngles(
		const YSI_CustomInteriorid,
		Float:YSI_aAngle,
		Float:YSI_bAngle)
{
	gYSI_InteriorData[YSI_CustomInteriorid][e_YSI_INTENTRANCE_A] = YSI_aAngle;
	gYSI_InteriorData[YSI_CustomInteriorid][e_YSI_INTEXIT_A] = YSI_bAngle;
	return YSI_INTERIORS_TRUE;
}

/*

                                                                                                 
88888888888                                                          db         88888888ba   88  
88                          ,d                                      d88b        88      "8b  88  
88                          88                                     d8'`8b       88      ,8P  88  
88aaaaa      8b,     ,d8  MM88MMM  8b,dPPYba,  ,adPPYYba,         d8'  `8b      88aaaaaa8P'  88  
88"""""       `Y8, ,8P'     88     88P'   "Y8  ""     `Y8        d8YaaaaY8b     88""""""'    88  
88              )888(       88     88          ,adPPPPP88       d8""""""""8b    88           88  
88            ,d8" "8b,     88,    88          88,    ,88      d8'        `8b   88           88  
88888888888  8P'     `Y8    "Y888  88          `"8bbdP"Y8     d8'          `8b  88           88  
                                                                                                 
                                                                                                 
*/

#define interiorcall%0(%1) \
	forward%0@_yI(%1,YSI_Actionid); \
	public%0@_yI(%1,YSI_Actionid)

#define hookinteriorcall%0(%1) \
	hook%0@_yI(%1,YSI_Actionid)

stock Interiors_SetPlayerInterior(YSI_p_Playerid, pYSI_Interiorid)
{
	if(pYSI_Interiorid < -1)
		return YSI_INTERIORS_FALSE;

	gYSI_PlayersInterior[YSI_p_Playerid] = pYSI_Interiorid;
	return YSI_INTERIORS_TRUE;
}

#define Interiors_InteriorActionPerformed(%0) \
	(YSI_Actionid == %0)