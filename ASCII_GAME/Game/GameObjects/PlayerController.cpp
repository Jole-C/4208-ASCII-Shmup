#include "PlayerController.h"

//////////////////////////////////////////////////////////////////////////////
//This class contains a player class and a player controller class.			//
//The player controller handles the bullet pool exclusively for the player,	//
//and also handles taking in and passing pointers to the player that it		//
//needs to function correctly.												//
//////////////////////////////////////////////////////////////////////////////

//player sprite
CHAR_INFO spPlayer[1026] = { {'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},
{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},
{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},
{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK}, };

/*
	PLAYER MOVEMENT
*/
//handles player controlling and movement
void Player::Move()
{

	//Draw the player "shield" (area to protect from enemies)
	m_pParticlePixelPool->Area(m_pRenderer, 10, 10, 15, 96, 10, m_pParticlePixelPool->COLOUR_BLUE);


	//if the player's lives are greater than 0, execute it's code
	if (lives > 0)
	{

		//if the player's x position is greater or equal to 30, IE if they are not performing the spawning intro, execute this code
		if (x >= 30)
		{

			//invincibility cooldown
			invincibilityCooldown -= 1;

			//move the player up and down
			if (GetKeyState(VK_UP) < 0)
			{
				speed -= 1;
			}
			else if (GetKeyState(VK_DOWN) < 0)
			{
				speed += 1;
			}

			//clamp the speed, apply it to the player, then apply friction to the speed
			if (speed > 5)
			{
				speed = 5;
			}
			else if (speed < -5)
			{
				speed = -5;
			}

			y += speed;
			speed *= fric;

			//bounce the player off the top and bottom of the screen by reversing their speed
			//make sure to set their position to either the top or button depending on where they bounce off, so they do not get stuck
			//if this didn't happen, they would constantly jitter as their speed is constantly reversed without them going anywhere or
			//being able to move properly
			if (y < 0)
			{

				y = 0;
				speed = -speed;

			}
			if (y > 87)
			{

				y = 87;
				speed = -speed;

			}

			//player trail
			m_pParticlePixelPool->Blast(m_pRenderer, x + 2, y + 6, 5, m_pParticlePixelPool->COLOUR_RED, 15, 180);

			//bullet collision
			int enemyBulletCount = static_cast<int>(m_pEnemyBulletPool->bullets.size());

			for (int i = 0; i < enemyBulletCount; i++)
			{

				//get bullet position
				Bullet* bullet = m_pEnemyBulletPool->bullets[i];
				Vector2 bulletPosition = Vector2(bullet->x, bullet->y);

				int bulletX = bulletPosition.x;
				int bulletY = bulletPosition.y;

				//calculate distance
				int distX = abs(bulletX - (x + 20));
				int distY = abs(bulletY - (y + 10));

				int max = max(distX, distY);

				//ensure that max will never be 0
				if (max == 0)
				{
					max = 1;
				}

				distX = distX / max;
				distY = distY / max;

				if (invincibilityCooldown <= 0)
				{

					if (sqrt((distY * distY) + (distX * distX)) * max < 4 && bullet->isHostileToPlayer == true && bullet->lifetime > 0)
					{

						//instantly make the bullet that just collided available, so that it no longer collides and can be reused by another enemy
						bullet->lifetime = -1;

						//lower the player's lives, and call the reset method
						ResetState();

					}

				}

			}

		}

		//player intro
		else
		{
			x += 5;
		}

	}

	//update sprite position
	m_pSprite->SetPosition(x, y);

}

/*
	resets player state
*/
void Player::ResetState()
{

	//create particles for a player explosion
	m_pParticlePixelPool->Explosion(m_pRenderer, x, y, 400, m_pParticlePixelPool->COLOUR_RED);

	//lower the player lives
	lives -= 1;

	//reset player "intro"
	x = -200;
	y = 40;
	speed = 0;

	//reset all bullets
	for (int i = 0; i < m_pPlayerBulletPool->bullets.size(); i++)
	{
		m_pPlayerBulletPool->bullets[i]->lifetime = -10;
	}

	//tell the enemy controller to reset itself
	m_pEnemyController->ResetState();

	//set invincibility frames
	invincibilityCooldown = 120;

	//reset the game if the player's lives are 0
	if (lives <= 0)
	{

		x = -1000;
		m_pEnemyController->gameOver = true;

	}
}

/*
	PLAYER FIRING
*/
void Player::Fire()
{

	//decrease the cooldown before the player can fire
	fireCooldown -= 1;

	//if the player can fire
	if (fireCooldown <= 0)
	{

		//set the fire cooldown variable to the max fire cooldown
		fireCooldown = maxFireCooldown;

		if (GetKeyState(VK_SPACE) < 0)
		{

			//creates a blast of particles when the player fires their gun
			m_pParticlePixelPool->Blast(m_pRenderer, x + 27, y + 7, 30, m_pParticlePixelPool->COLOUR_BLUE, 15, 0);

			//create a bullet from the pool
			m_pPlayerBulletPool->CreateBullet(x + 22, y + 5, false, 30, 0, 16);

		}

	}

}

/*
	INITIALISES PLAYER RENDERER
*/
void Player::InitialiseRenderer(ASCIIRenderer* renderer)
{
	Initialise(renderer, spPlayer, size);
}

/*
	UPDATES PLAYER
*/
void Player::Update()
{

	Move();

	Fire();

}

/*
	RENDERS PLAYER
*/
void Player::Draw()
{
	m_pSprite->Render(m_pRenderer);
}

/*
	HARD RESETS ENTIRE PLAYER CONTROLLER FOR NEW GAME
*/
void PlayerController::HardReset()
{

	m_pPlayer->ResetState();
	m_pPlayer->lives = 3;
	m_pPlayer->x = -200;
	m_pPlayerBulletPool->HardReset();

}

/*
	INITIALISES THE PLAYER CONTROLLER
*/
void PlayerController::Init(ASCIIRenderer* renderer, ParticlePixelPool* particlePool)
{

	//create a new player, and a pool for the player bullets
	m_pPlayer = new Player;
	m_pPlayerBulletPool = new BulletPool;

	//initialise the bullet pool
	m_pPlayerBulletPool->InitialiseBulletPool(renderer, 1000);

	//initialise player renderer, and give them the pointer to our bullet pool and the game's particle pool
	m_pPlayer->InitialiseRenderer(renderer);
	m_pPlayer->m_pPlayerBulletPool = m_pPlayerBulletPool;
	m_pPlayer->m_pParticlePixelPool = particlePool;

}

/*
	PASSES THE ENEMY CONTROLLER TO THE PLAYER CONTROLLER, AND SETS THE ENEMY BULLET POOL POINTER TO THE ONE IN THE ENEMY CONTROLLER
*/
void PlayerController::PassEnemyController(EnemyController* enemyController)
{

	m_pPlayer->m_pEnemyBulletPool = enemyController->m_pEnemyBulletPool;
	m_pPlayer->m_pEnemyController = enemyController;

}

/*
	UPDATES THE PLAYER CONTROLLER
*/
void PlayerController::Update()
{

	//update the player and bullet pool
	m_pPlayer->Update();
	m_pPlayerBulletPool->Update();

}

/*
	DRAWS THE PLAYER CONTROLLER
*/
void PlayerController::Draw()
{

	//draw the player bullet pool
	m_pPlayer->Draw();
	m_pPlayerBulletPool->Draw();

}