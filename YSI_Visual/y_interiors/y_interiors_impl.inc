#include "y_interiors_decl"// decl-arations

/*

 .----------------.  .----------------.  .----------------.  .----------------.  .----------------. 
| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |
| |  ____  ____  | || |     ____     | || |     ____     | || |  ___  ____   | || |    _______   | |
| | |_   ||   _| | || |   .'    `.   | || |   .'    `.   | || | |_  ||_  _|  | || |   /  ___  |  | |
| |   | |__| |   | || |  /  .--.  \  | || |  /  .--.  \  | || |   | |_/ /    | || |  |  (__ \_|  | |
| |   |  __  |   | || |  | |    | |  | || |  | |    | |  | || |   |  __'.    | || |   '.___`-.   | |
| |  _| |  | |_  | || |  \  `--'  /  | || |  \  `--'  /  | || |  _| |  \ \_  | || |  |`\____) |  | |
| | |____||____| | || |   `.____.'   | || |   `.____.'   | || | |____||____| | || |  |_______.'  | |
| |              | || |              | || |              | || |              | || |              | |
| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |
 '----------------'  '----------------'  '----------------'  '----------------'  '----------------' 

*/

gYSI_InteriorLoadingTime(const playerid)
{
	TogglePlayerControllable(playerid,true);
}

YSI_OnPlayerNearEntrance(playerid);
public YSI_OnPlayerNearEntrance(playerid)
{
    TogglePlayerControllable(playerid,false);
	for(new i; i < MAX_INTERIORS; i++)
	{
		if( IsPlayerInRangeOfPoint( playerid, 1.5, gYSI_InteriorData[ i ][e_YSI_INTENTRANCE_X], \
		gYSI_InteriorData[ i ][e_YSI_INTENTRANCE_Y], gYSI_InteriorData[ i ][e_YSI_INTENTRANCE_Z]) \
		&& GetPlayerVirtualWorld( playerid ) == gYSI_InteriorData[ i ][e_YSI_INTERIOR_VWID_OUT] \
		&& !IsPlayerInAnyVehicle( playerid ))
		{

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

		    gYSI_PlayersInterior[ playerid ] = -1;
		}
    }
    return true;
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

/*

                                                                                         
                                                                                         
 __  __   ___            .--.   _..._                       _________   _...._      .--. 
|  |/  `.'   `.          |__| .'     '.                     \        |.'      '-.   |__| 
|   .-.  .-.   '         .--..   .-.   .                     \        .'```'.    '. .--. 
|  |  |  |  |  |    __   |  ||  '   '  |              __      \      |       \     \|  | 
|  |  |  |  |  | .:--.'. |  ||  |   |  |           .:--.'.     |     |        |    ||  | 
|  |  |  |  |  |/ |   \ ||  ||  |   |  |          / |   \ |    |      \      /    . |  | 
|  |  |  |  |  |`" __ | ||  ||  |   |  |          `" __ | |    |     |\`'-.-'   .'  |  | 
|__|  |__|  |__| .'.''| ||__||  |   |  |           .'.''| |    |     | '-....-'`    |__| 
                / /   | |_   |  |   |  |          / /   | |_  .'     '.                  
                \ \._,\ '/   |  |   |  |          \ \._,\ '/'-----------'                
                 `--'  `"    '--'   '--'           `--'  `"                              

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
	return 1;
}

stock bool:Interiors_IsPlayerInInterior(playerid)
{
	if(gYSI_PlayersInterior[ playerid ] = -1) return false;
	else return true;
}

stock Interiors_ClearPlayerInteriorData(playerid)
{
	gYSI_PlayersInterior[playerid] = -1;
	return 1;
}

stock Interiors_SetInteriorAngles(
		const YSI_CustomInteriorid,
		Float:YSI_aAngle,
		Float:YSI_bAngle)
{
	gYSI_InteriorData[YSI_CustomInteriorid][e_YSI_INTENTRANCE_A] = YSI_aAngle;
	gYSI_InteriorData[YSI_CustomInteriorid][e_YSI_INTEXIT_A] = YSI_bAngle;
	return 1;
}