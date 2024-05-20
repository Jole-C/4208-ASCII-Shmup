#include "Enemy.h"
#include "../../Core/Renderer/ConsoleColours.h"
#include "../../Game/GameObjects/PlayerController.h"
#include "../../Core/Renderer/Sprite.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This class defines the methods for each enemy and the boss, and also several methods for the enemy controller.				//
//The enemy controller is initialised by the game, taking in several necessary variables such as the player controller,			//
//the player itself, particle pool and bullet pool. It also takes in the game renderer.											//
//It then handles spawning, updating and destroying enemies and the boss, and tells the game when to switch to a win state.		//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//sets std namespace
using namespace std;

//(52x19 size) - default sprite and white sprite for the basic enemy
CHAR_INFO spEnemy[988] = { {' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},
{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},
{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},
{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},
{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK}, };
CHAR_INFO spEnemyWhite[988] = { {' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK}, };
//(56x20 size) - default sprite and white sprite for the aiming enemy
CHAR_INFO spEnemy2[1120] = { {' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},
{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_RED},{'\xdb',F_RED},
{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},
{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},
{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},
{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_PURPLE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK}, };
CHAR_INFO spEnemy2White[1120] = { {' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
};
//(52x17 size) - default sprite and white sprite for the forwards firing enemy
CHAR_INFO spEnemy3[884] = { {' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},
{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},
{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},
{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_ORANGE},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_BROWN},{'\xdb',F_BROWN},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_BROWN},{'\xdb',F_BROWN},
{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},
{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_BROWN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK}, };
CHAR_INFO spEnemy3White[884] = { {' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK}, };
//(66x20 size) - default sprite and white for the boss
CHAR_INFO spBoss[1320] = { {' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},
{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},
{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},
{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},
{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_DARK_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_GREEN},{'\xdb',F_GREEN},
{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_GREEN},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},
{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},
{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},
{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},
{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},
{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},
{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},
{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},
{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},
{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},
{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_LAVENDER},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},
{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
};
CHAR_INFO spBossWhite[1320] = { {' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},
};

//Enemy destructor - deletes the created sprite object, and creates an explosion effect for the enemy in question
Enemy::~Enemy()
{

	//create a death explosion
	m_pParticlePixelPool->Explosion(m_pRenderer, x, y, 100, m_pParticlePixelPool->COLOUR_RED);

	//delete the sprite object
	delete(m_pSprite);

}

/*
	ENEMY MATH METHODS
*/

//Calculate angle
double Enemy::AngleBetweenPoints(int _x1, int _y1, int _x2, int _y2)
{
	return atan2(_y2 - _y1, _x2 - _x1);
}

//Distance to point
float Enemy::DistanceToPoint(int _x1, int _y1, int _x2, int _y2)
{
	return sqrt(pow(_x2 - _x1, 2) + pow(_y2 - _y1, 2) * 1);
}

//Degrees to radians
double Enemy::DegreesToRadians(int degrees)
{
	return (degrees * 3.14159265359) / 180;
}

/*
	HARD RESETS THE ENEMY CONTROLLER
*/
void EnemyController::HardReset()
{

	//resets enemy list, clearing all pointers from it and deleting the memory stored in those pointers
	auto iterator = enemyList.begin();

	while (iterator != enemyList.end())
	{

		//remove every enemy from the list and the memory itself
		delete (*iterator);
		iterator = enemyList.erase(iterator);

	}

	//makes all bullets available
	m_pEnemyBulletPool->HardReset();

	//resets all variables
	score = 0;
	multiplier = 1;
	multiplierReset = 300;
	multiplierKills = 0;
	enemyFreezeTime = maxEnemyFreezeTime;
	bossHP = 150;
	gameDoneTimer = 150;
	bossSpawned = false;
	gameDone = false;
	gameWon = false;
	gameOver = false;

	totalEnemies = 50;
	currentEnemies = 0;
	enemySpawnCooldown = 120;

}

/*
	INITIALISE ENEMY CONTROLLER
*/
void EnemyController::InitialiseEnemyController(ASCIIRenderer* renderer, ParticlePixelPool* particlePixelPool, BulletPool* playerBulletPool, Player* player)
{

	//sets a renderer pointer
	m_pRenderer = renderer;

	//creates and initialises a bullet pool
	m_pEnemyBulletPool = new BulletPool;
	m_pEnemyBulletPool->InitialiseBulletPool(renderer, 75);

	//sets the player bullet pool, main particle pool, and player pointers
	m_pPlayerBulletPool = playerBulletPool;
	m_pParticlePixelPool = particlePixelPool;
	m_pPlayer = player;

}

/*
	RESET ENEMY CONTROLLER
*/
void EnemyController::ResetState()
{

	//make all enemy bullets available
	for (int i = 0; i < m_pEnemyBulletPool->bullets.size(); i++)
	{
		m_pEnemyBulletPool->bullets[i]->lifetime = -1;
	}

	//freeze all enemies for a few seconds
	enemyFreezeTime = maxEnemyFreezeTime;

	//reset score vars
	multiplier = 1;
	multiplierReset = 300;
	multiplierKills = 0;

}

/*
	ENEMY CONTROLLER CREATING ENEMIES
*/
Enemy* EnemyController::MakeEnemies()
{

	int enemyChoice = rand() % 3;
	Enemy* enemy = nullptr;

	int enemySpawnX;
	int enemySpawnY = rand() % 75;

	//spawn enemies off screen if the boss hasn't spawned, else spawn them on screen, and make an explosion
	if (bossSpawned == true)
	{
		enemySpawnX = 350;
		m_pParticlePixelPool->Explosion(m_pRenderer, enemySpawnX, enemySpawnY, 50, m_pParticlePixelPool->COLOUR_BLUE);
	}
	else
	{
		enemySpawnX = 512;
	}

	//Initialise the enemy based on the chosen enemy
	//for each choice, set the enemy variable to the correct enemy then initialise it
	switch (enemyChoice)
	{

		case 0:

			//creates enemy object
			enemy = new EnemyMove();

			//initialises the object
			enemy->Initialise(m_pRenderer, m_pParticlePixelPool, m_pPlayerBulletPool, m_pEnemyBulletPool, m_pPlayer, enemySpawnX, enemySpawnY, 0);

			break;

		case 1:

			//create enemy object
			enemy = new EnemyMoveFireAim();

			//initialise the object
			enemy->Initialise(m_pRenderer, m_pParticlePixelPool, m_pPlayerBulletPool, m_pEnemyBulletPool, m_pPlayer, enemySpawnX, enemySpawnY, 1);

			break;

		case 2:

			//create enemy object
			enemy = new EnemyMoveFireForwards();

			//initialise the object
			enemy->Initialise(m_pRenderer, m_pParticlePixelPool, m_pPlayerBulletPool, m_pEnemyBulletPool, m_pPlayer, enemySpawnX, enemySpawnY, 2);

			break;

		default:

			//create enemy object
			enemy = new EnemyMove();

			//initialise the object
			enemy->Initialise(m_pRenderer, m_pParticlePixelPool, m_pPlayerBulletPool, m_pEnemyBulletPool, m_pPlayer, enemySpawnX, enemySpawnY, 0);

			break;

	}

	return enemy;

}


/*
	ENEMY CONTROLLER UPDATING
*/
void EnemyController::UpdateEnemies()
{

	//Count down for game reset after dying or killing the boss
	if (gameWon == true || gameOver == true)
	{
		
		//lower the timer
		gameDoneTimer -= 1;

		//once the timer reaches 0
		if (gameDoneTimer <= 0)
		{
			//end the game
			gameDone = true;
		}

	}

	//Lower the enemy freeze time
	enemyFreezeTime -= 1;

	//If the enemies are not frozen, IE the player has not recently died, allow the enemy controller to do its thing (controlling multiplier, updating enemies, etc)
	if (enemyFreezeTime <= 0)
	{

		//Score multiplier increaser
		if (multiplierKills > multiplier * 3)
		{

			multiplierKills = 0;
			multiplier += 1;

		}

		//resets the  multiplier after a delay
		if (multiplierReset <= 0 && multiplier > 1)
		{

			multiplier = 1;
			multiplierReset = 300;

		}

		//clamp the multiplier reset counter and ensure it only goes down when the multiplier is above 1
		if (multiplier > 0 && enemySpawnCooldown <= 0)
		{
			multiplierReset -= 1;
		}
		else if (multiplierReset <= 0 || multiplierReset > 300)
		{
			multiplierReset = 300;
		}

		//Create a new enemy when required
		enemySpawnCooldown -= 1;
		if (currentEnemies < 5 && totalEnemies > 1 && enemySpawnCooldown <= 0)
		{

			//Decrease the total number of enemies left
			totalEnemies -= 1;

			//Increases the current on screen enemies
			currentEnemies += 1;

			//Create an enemy pointer assigned to a nullptr
			Enemy* enemy = MakeEnemies();

			//Push it to the back of the list
			enemyList.push_back(enemy);

		}
		//else if there is only 1 enemy left, spawn a boss
		else if (totalEnemies == 1 && enemySpawnCooldown <= 0)
		{

			//creates a boss
			Enemy* enemy = nullptr;

			//initialises the boss
			enemy = new Boss();
			enemy->Initialise(m_pRenderer, m_pParticlePixelPool, m_pPlayerBulletPool, m_pEnemyBulletPool, m_pPlayer, 512, 40, 3);

			//Push it to the back of the list
			enemyList.push_back(enemy);

			//lower the total enemies so another boss does not spawn
			totalEnemies -= 1;

		}

		//Use an iterator to loop through all enemies
		auto iterator = enemyList.begin();

		while (iterator != enemyList.end())
		{

			//check to see if the current enemy can be destroyed
			if ((*iterator)->canBeRemoved == true)
			{

				//if boss, reset the game
				if ((*iterator)->type == 3)
				{

					bossSpawned = false;
					gameWon = true;

				}

				//remove the enemy, clear it from the list, lower current enemy variable (so another enemy can spawn)
				currentEnemies -= 1;
				delete (*iterator);
				iterator = enemyList.erase(iterator);

			}
			//if not, iterate the iterator and update the enemy
			else
			{

				//update the enemy
				(*iterator)->Update();

				//if the enemy is a boss, let the game class know with this variable, and update the HP variable to match the one stored in the boss
				if ((*iterator)->type == 3)
				{

					bossSpawned = true;
					bossHP = (*iterator)->hp;

				}

				//iterate the iterator
				iterator += 1;

			}
		}

		//Update bullets
		m_pEnemyBulletPool->Update();

	}

}

/*
	ENEMY CONTROLLER DRAWING
*/
void EnemyController::DrawEnemies()
{

	//render enemies
	//Use an iterator to loop through all enemies
	auto iterator = enemyList.begin();

	while (iterator != enemyList.end())
	{

		//check to see if the current enemy can be destroyed
		if ((*iterator)->canBeRemoved == true)
		{

			//if boss, reset the game
			if ((*iterator)->type == 3)
			{

				bossSpawned = false;
				gameWon = true;

			}

			//remove the enemy if it is flagged to be removed
			currentEnemies -= 1;
			delete (*iterator);
			iterator = enemyList.erase(iterator);

			//increases score, multiplier kills, and increases the delay before the multiplier will be reset
			enemySpawnCooldown = 120;
			score += 100 * multiplier;
			multiplierKills += 1;
			multiplierReset += 60;

		}
		//if not, iterate the iterator and draw the enemy
		else
		{

			//draw the enemy
			(*iterator)->Draw();

			//if the enemy is a boss, let the game class know with this variable, and update the HP variable to match the one stored in the boss
			if ((*iterator)->type == 3)
			{

				bossSpawned = true;
				bossHP = (*iterator)->hp;

			}

			//iterate the iterator
			iterator += 1;

		}
	}

	//draw bullets stored in the enemy bullet pool
	m_pEnemyBulletPool->Draw();

	//randomly spawn enemies if the boss has been created
	if (bossSpawned == true)
	{

		if (enemySpawnCooldown <= 0)
		{

			for (int i = 0; i < 2; i++)
			{

				//make enemy
				Enemy* enemy = MakeEnemies();

				//Push it to the back of the list
				enemyList.push_back(enemy);

				enemySpawnCooldown = 300;

			}

		}

	}

}

/*
	ENEMY INITIALISATION METHOD FOR ALL ENEMIES
*/
void Enemy::Initialise(ASCIIRenderer* renderer, ParticlePixelPool* particlePool, BulletPool* playerBulletPool, BulletPool* enemyBulletPool, Player* player, float _x, float _y, int enemyType)
{

	//set up renderer
	m_pRenderer = renderer;
	m_pSprite = new Sprite();

	//initialise enemy sprite depending on type
	switch (enemyType)
	{

		case 0:

			m_pSprite->Initialise(spEnemy, Vector2(52, 19));

			break;

		case 1:

			m_pSprite->Initialise(spEnemy2, Vector2(56, 20));

			break;

		case 2:

			m_pSprite->Initialise(spEnemy3, Vector2(52, 17));

			break;

		case 3:

			m_pSprite->Initialise(spBoss, Vector2(66, 20));

			break;

		default:

			m_pSprite->Initialise(spEnemy, Vector2(52, 19));

			break;

	}

	//set position
	x = _x;
	y = _y;

	//set enemy type, to be used by the flashing white method for choosing which sprite to use for the flash, and which to return to
	type = enemyType;

	//set renderer and other pointers
	m_pParticlePixelPool = particlePool;
	m_pPlayerBulletPool = playerBulletPool;
	m_pEnemyBulletPool = enemyBulletPool;
	m_pPlayer = player;

}

/*
	UPDATES ENEMY
*/
//move the enemy - firing is handled elsewhere
void Enemy::Update()
{

	//move and set position, firing is called from within this method
	Move();
	FlashWhite();
	
	//set sprite position
	m_pSprite->SetPosition(x, y);

	//check if there's a player bullet close to the enemy
	for (int i = 0; i < 10; i++)
	{

		//get bullet position
		Bullet* bullet = m_pPlayerBulletPool->bullets[i];

		int bulletX = bullet->x;
		int bulletY = bullet->y;

		//check for distance to player bullets, or check for x position
		if ((DistanceToPoint(bulletX, bulletY, x, y) < 10 && bullet->isHostileToPlayer == false && bullet->lifetime > 0) || (x < 20))
		{

			//if hp is greater than 1, destroy the bullet, lower hp, set flash time for flashing sprite, else undo the sprite
			if (hp > 1)
			{

				bullet->lifetime = -1;
				flashtime = 15;
				hp -= 1;

			}
			//else if hp is lower than 1, flag the enemy to be removed from the game
			else
			{

				canBeRemoved = true;
				bullet->lifetime = -1;

				//if the x position is less than 0, then call the player's reset method and destroy them. do not do this otherwise, as killing an enemy will lose a life
				if (x < 20)
				{

					x = 1000;
					hp = -1;
					m_pPlayer->ResetState();

				}

			}
		}
	}

	//creates enemy smoke around the object if it's hp is low, as an indicator for the player
	if (hp == 1)
	{
		m_pParticlePixelPool->Area(m_pRenderer, x, y, x + 20, y + 15, 5, m_pParticlePixelPool->COLOUR_GREY);
	}

}

/*
	DRAW METHOD FOR ALL ENEMIES
*/
//draw the enemy
void Enemy::Draw()
{
	m_pSprite->Render(m_pRenderer);
}

//blank methods to be overriden by child enemies
void Enemy::Move()
{

}

void Enemy::Fire()
{

}

/*
	FLASH SPRITE WHITE
*/
//flash the sprite white
void Enemy::FlashWhite()
{

	//decrease flash time
	flashtime -= 1;

	//if flash time is greater than 0, switch the enemy sprite to a white silhouette
	if (flashtime > 0)
	{

		//depending on enemy type, switch the sprite to a white one
		switch (type)
		{

			case 0:

				//delete the old sprite to free up memory
				delete(m_pSprite);

				//create a new sprite, initialise it with the white sprite for the enemy, then set the position
				m_pSprite = new Sprite();
				ChangeSprite(spEnemyWhite, Vector2(52, 19));
				m_pSprite->SetPosition(x, y);

				break;

			case 1:

				delete(m_pSprite);

				m_pSprite = new Sprite();
				ChangeSprite(spEnemy2White, Vector2(56, 20));
				m_pSprite->SetPosition(x, y);

				break;

			case 2:

				delete(m_pSprite);

				m_pSprite = new Sprite();
				ChangeSprite(spEnemy3White, Vector2(52, 17));
				m_pSprite->SetPosition(x, y);

				break;

			case 3:

				delete(m_pSprite);

				m_pSprite = new Sprite();
				ChangeSprite(spBossWhite, Vector2(66, 20));
				m_pSprite->SetPosition(x, y);

				break;

			default:

				delete(m_pSprite);

				m_pSprite = new Sprite();
				ChangeSprite(spEnemyWhite, Vector2(52, 19));
				m_pSprite->SetPosition(x, y);

				break;

		}

	}
	//else, switch the sprite back to it's default sprite
	else
	{

		switch (type)
		{

			case 0:

				//delete the old sprite
				delete(m_pSprite);

				//create a new sprite that is the normal sprite, then set it's position
				m_pSprite = new Sprite();
				ChangeSprite(spEnemy, Vector2(52, 19));
				m_pSprite->SetPosition(x, y);

				break;

			case 1:

				delete(m_pSprite);

				m_pSprite = new Sprite();
				ChangeSprite(spEnemy2, Vector2(56, 20));
				m_pSprite->SetPosition(x, y);

				break;

			case 2:

				delete(m_pSprite);

				m_pSprite = new Sprite();
				ChangeSprite(spEnemy3, Vector2(52, 17));
				m_pSprite->SetPosition(x, y);

				break;

			case 3:

				delete(m_pSprite);

				m_pSprite = new Sprite();
				ChangeSprite(spBoss, Vector2(66, 20));
				m_pSprite->SetPosition(x, y);

				break;

			default:

				delete(m_pSprite);

				m_pSprite = new Sprite();
				ChangeSprite(spEnemy, Vector2(52, 19));
				m_pSprite->SetPosition(x, y);

				break;
		}

	}

}

//move and fire methods for enemy types

/*
	ENEMY MOVE METHODS
*/
void EnemyMove::Move()
{

	//flash the sprite white
	FlashWhite();

	x -= speed;

	//create a trail behind the enemy
	m_pParticlePixelPool->Blast(m_pRenderer, x + 52, y + 9, 2, m_pParticlePixelPool->COLOUR_RED, 12, 0);

}

//enemy does not fire
void EnemyMove::Fire()
{
	
}

/*
	AIMING ENEMY METHODS
*/
void EnemyMoveFireAim::Move()
{

	//flash the sprite white
	FlashWhite();

	stopCooldown -= 1;

	//move left
	if (stopCooldown > 60)
	{

		x -= speed;

		//create a trail behind the enemy
		m_pParticlePixelPool->Blast(m_pRenderer, x + 52, y + 9, 2, m_pParticlePixelPool->COLOUR_RED, 12, 0);

	}

	//stop, fire a bullet
	else if (stopCooldown < 30 && stopCooldown > 10)
	{

		fireCooldown -= 1;

		if (fireCooldown <= 0)
		{

			Fire();
			fireCooldown = 5;

		}

	}

	//move again, and repeat
	else if (stopCooldown <= 0)
	{

		fireCooldown = 5;
		stopCooldown = maxStopCooldown;

	}

}

void EnemyMoveFireAim::Fire()
{

	//get the angle from the enemy to the player
	float fireAngle = AngleBetweenPoints(x, y, m_pPlayer->x, m_pPlayer->y);

	//make a bullet pointed at that angle, assuming the ship isn't beyond an x threshold. This prevents them from firing unavoidable bullets at the player, causing them to die multiple times
	if (x > 50)
	{

		m_pEnemyBulletPool->CreateBullet(x, y + 8, true, 100, fireAngle, 5);

		//create a particle blast where the ship fires
		m_pParticlePixelPool->Blast(m_pRenderer, x, y + 8, 2, m_pParticlePixelPool->COLOUR_RED, 5, fireAngle);

	}

}


/*
	FORWARD FIRING ENEMY METHODS
*/
void EnemyMoveFireForwards::Move()
{

	//flash the sprite white
	FlashWhite();

	stopCooldown -= 1;

	//move until reaching the chosen x position
	if (x <= chosenX)
	{

		//move up and down if able to
		if (stopCooldown > 60)
		{

			//create a trail behind the enemy
			m_pParticlePixelPool->Blast(m_pRenderer, x + 52, y + 9, 2, m_pParticlePixelPool->COLOUR_RED, 12, 0);

			//keep the speed clamped
			if (y < 0)
			{
				speed = -speed;
			}
			else if (y > 87)
			{
				speed = -speed;
			}

			y += speed;

		}

		//else, stop and fire a bullet
		else if (stopCooldown < 30 && stopCooldown > 0)
		{

			fireCooldown -= 1;

			if (fireCooldown <= 0)
			{

				fireCooldown = 5;
				Fire();

			}

		}

		//move up and down again, randomise speed, and repeat
		else if (stopCooldown <= 0)
		{

			fireCooldown = 5;
			stopCooldown = maxStopCooldown;
			speed = rand() % 4 + (-2);

		}

	}

	//move left until chosen x position is reached
	else
	{
		x -= speed;
	}

}

void EnemyMoveFireForwards::Fire()
{

	//choose between bullet patterns to fire
	switch (fireType)
	{
		//fire bullets forwards
		case 0:

			m_pEnemyBulletPool->CreateBullet(x + 3, y + 8, true, 180, 3.14159, 3);

			break;

		//fire 2 bullets, 5 degrees off up and down
		case 1:

			m_pEnemyBulletPool->CreateBullet(x + 3, y + 8, true, 180, DegreesToRadians(180 + 5), 3);
			m_pEnemyBulletPool->CreateBullet(x + 3, y + 8, true, 180, DegreesToRadians(180 - 5), 3);

			break;

		//fires 3 bullets, a combination of 1 and 2
		case 2:

			m_pEnemyBulletPool->CreateBullet(x + 3, y + 8, true, 180, DegreesToRadians(180 + 30), 3);
			m_pEnemyBulletPool->CreateBullet(x + 3, y + 8, true, 180, DegreesToRadians(180), 3);
			m_pEnemyBulletPool->CreateBullet(x + 3, y + 8, true, 180, DegreesToRadians(180 - 30), 3);

			break;
	}

	//create a particle blast where the ship fires
	m_pParticlePixelPool->Blast(m_pRenderer, x + 3, y + 8, 2, m_pParticlePixelPool->COLOUR_RED, 5, 180);

}


/*
	BOSS METHODS
*/
void Boss::Update()
{

	//flash the sprite white
	FlashWhite();

	//boss trail
	m_pParticlePixelPool->Blast(m_pRenderer, x + 66, y + 10, 10, m_pParticlePixelPool->COLOUR_GREY, 15, 0);

	//player indicators for low hp
	//creates smoke
	if (hp < 50)
	{
		m_pParticlePixelPool->Area(m_pRenderer, x, y, x + 15, y + 15, 5, m_pParticlePixelPool->COLOUR_GREY);
	}

	//creates fire
	if (hp < 35)
	{
		m_pParticlePixelPool->Area(m_pRenderer, x, y, x + 15, y + 15, 5, m_pParticlePixelPool->COLOUR_RED);
	}

	//creates explosions
	if (hp < 20)
	{

		for (int i = 0; i < 3; i++)
		{

			int randomX = rand() % 30;
			int randomY = rand() % 15;

			m_pParticlePixelPool->Create(m_pRenderer, x + randomX, y + randomY, rand() % 360, rand() % 3, m_pParticlePixelPool->COLOUR_RED[rand() % 3], rand() % 30);

		}

	}



	//if the boss is in a move state
	if (bossState == E_MOVE)
	{
		MoveState();
	}

	//if the boss is not in the intro state and it is not in a move state, then it is in a fire state
	else if (bossState != E_INTRO && bossState != E_MOVE)
	{

		FireState();

		//use a sine wave to move the boss up and down a little, if it is not in the intro phase
		//move the sine wave up and down
		moveAngle += 0.1;

		if (moveAngle > 360)
		{
			moveAngle = 0;
		}

		//set the position of the boss to a "base y" set by the move state, + the sine wave
		y = baseY + sin(moveAngle) * 9;

	}

	//else if in the intro state
	else
	{

		//move to the left
		if (x > 300)
		{
			x -= 2;
		}
		//stop once the position is reached, and switch to a random fire state, resetting and randomising fire state variables
		else
		{

			ResetFiringStates();

			bossState = static_cast<E_BOSS_STATES>(2 + (rand() % 4 + 1));

		}

	}

	//collision
	for (int i = 0; i < 10; i++)
	{

		//get bullet position
		Bullet* bullet = m_pPlayerBulletPool->bullets[i];

		int bulletX = bullet->x;
		int bulletY = bullet->y;

		//check for distance to player bullets, or check for x position
		if ((DistanceToPoint(bulletX, bulletY, x, y) < 10 && bullet->isHostileToPlayer == false && bullet->lifetime > 0))
		{

			//if hp is greater than 1, lower hp and destroy the bullet
			if (hp > 1)
			{

				flashtime = 15;
				hp -= rand() % 3;
				bullet->lifetime = -1;

			}
			//if less than 1, tell the iterator the boss can be removed, then create an explosion
			else
			{

				canBeRemoved = true;
				bullet->lifetime = -1;

				//create a death explosion
				m_pParticlePixelPool->Explosion(m_pRenderer, x, y, 500, m_pParticlePixelPool->COLOUR_RED);

			}
		}
	}

	//set sprite position
	m_pSprite->SetPosition(x, y);

}


/*
	RESET FIRE STATES
*/
void Boss::ResetFiringStates()
{

	//reinitialise all firing variables
	bulletsToFire = 5 + rand() % 5;
	circularBulletCount = 5 + rand() % 5;
	bulletSpeed = rand() % 3 + 2;
	spreadCount = rand() % 3;
	bulletSpeedIncrease = 0;
	maxBulletCooldown = 30;
	bulletCooldown = 30;

}

/*
	SET MOVE STATES
*/
void Boss::MoveState()
{

	//create particles for teleport
	m_pParticlePixelPool->Explosion(m_pRenderer, x, y, 150, m_pParticlePixelPool->COLOUR_BLUE);

	//teleport (move to a random position)
	x = 200 + rand() % 200;
	y = 20 + rand() % 56;

	//set the base y variable to be used for the sine wave
	baseY = y;

	//set a random firing state
	ResetFiringStates();
	bossState = static_cast<E_BOSS_STATES>(3 + (rand() % 3));

}

/*
	FIRE STATES
*/
//fires different bullet patterns depending on the given state
void Boss::FireState()
{

	//decrease bullet cooldown
	bulletCooldown -= 1;

	//fire bullets
	if (bulletCooldown <= 0)
	{

		bulletCooldown = maxBulletCooldown - bulletSpeedIncrease * 3;

		switch (bossState)
		{

			//fires a circle of bullets
			case E_FIRE_CIRCLE:
			{

				//fire bullets in a circle with a base angle of the player
				for (int i = 0; i < circularBulletCount + bulletSpeedIncrease; i++)
				{

					float bulletAngle = AngleBetweenPoints(x, y, m_pPlayer->x, m_pPlayer->y) + DegreesToRadians((360 / circularBulletCount + bulletSpeedIncrease) * i);
					m_pEnemyBulletPool->CreateBullet(x, y, true, 120, bulletAngle, bulletSpeed + bulletSpeedIncrease);

					//create a particle blast
					m_pParticlePixelPool->Blast(m_pRenderer, x + 52, y + 9, 30, m_pParticlePixelPool->COLOUR_BLUE, 12, bulletAngle);

				}

				break;

			}

			//fires at the player directly
			case E_FIRE_AT_PLAYER:
			{

				double bulletAngle = AngleBetweenPoints(x, y, m_pPlayer->x, m_pPlayer->y + m_pPlayer->speed / 2);
				m_pEnemyBulletPool->CreateBullet(x, y, true, 120, bulletAngle, bulletSpeed + bulletSpeedIncrease);

				//create a particle blast
				m_pParticlePixelPool->Blast(m_pRenderer, x + 52, y + 9, 30, m_pParticlePixelPool->COLOUR_BLUE, 12, bulletAngle);

				break;

			}

			//fires forwards at a random y position
			case E_FIRE_FORWARDS:
			{

				//fire 3 bullets at a random y interval, but the x interval of the boss
				for (int i = 0; i < 3; i++)
				{
					m_pEnemyBulletPool->CreateBullet(x, y - 50 + rand() % 100, true, 120, DegreesToRadians(180), bulletSpeed + bulletSpeedIncrease);
				}

				//create a particle blast
				m_pParticlePixelPool->Blast(m_pRenderer, x + 52, y + 9, 30, m_pParticlePixelPool->COLOUR_BLUE, 12, 0);

				break;

			}

			//fires between 2, 3 and 5 bullets
			case E_FIRE_SPREAD:
			{

				switch (spreadCount)
				{
					
					//fire 3 bullets
					case 0:

						m_pEnemyBulletPool->CreateBullet(x, y, true, 120, DegreesToRadians(180 + 10), bulletSpeed + bulletSpeedIncrease);
						m_pEnemyBulletPool->CreateBullet(x, y, true, 120, DegreesToRadians(180), bulletSpeed + bulletSpeedIncrease);
						m_pEnemyBulletPool->CreateBullet(x, y, true, 120, DegreesToRadians(180 - 10), bulletSpeed + bulletSpeedIncrease);

						break;

					//fire 5 bullets
					case 1:

						m_pEnemyBulletPool->CreateBullet(x, y, true, 120, DegreesToRadians(180 + 15), bulletSpeed + bulletSpeedIncrease);
						m_pEnemyBulletPool->CreateBullet(x, y, true, 120, DegreesToRadians(180 + 10), bulletSpeed + bulletSpeedIncrease);
						m_pEnemyBulletPool->CreateBullet(x, y, true, 120, DegreesToRadians(180), bulletSpeed + bulletSpeedIncrease);
						m_pEnemyBulletPool->CreateBullet(x, y, true, 120, DegreesToRadians(180 - 10), bulletSpeed + bulletSpeedIncrease);
						m_pEnemyBulletPool->CreateBullet(x, y, true, 120, DegreesToRadians(180 - 15), bulletSpeed + bulletSpeedIncrease);

						break;

					//fire 2 bullets, with a random chance to fire a bullet aimed at the player
					case 2:

						m_pEnemyBulletPool->CreateBullet(x, y, true, 120, DegreesToRadians(180 + 10), bulletSpeed + bulletSpeedIncrease);
						m_pEnemyBulletPool->CreateBullet(x, y, true, 120, DegreesToRadians(180 - 10), bulletSpeed + bulletSpeedIncrease);

						//random chance to fire a bullet at the player
						if (rand() % 7 > 4)
						{
							m_pEnemyBulletPool->CreateBullet(x, y, true, 120, AngleBetweenPoints(x, y, m_pPlayer->x, m_pPlayer->y), bulletSpeed + bulletSpeedIncrease);
						}

					break;

				}

				//create a particle blast
				m_pParticlePixelPool->Blast(m_pRenderer, x + 52, y + 9, 2, m_pParticlePixelPool->COLOUR_BLUE, 12, 0);

				break;

			}

			//default firing state (circle)
			default:
			{

				for (int i = 0; i < circularBulletCount + bulletSpeedIncrease; i++)
				{

					float bulletAngle = AngleBetweenPoints(x, y, m_pPlayer->x, m_pPlayer->y) + DegreesToRadians((360 / circularBulletCount + bulletSpeedIncrease) * i);
					m_pEnemyBulletPool->CreateBullet(x, y, true, 120, bulletAngle, bulletSpeed + bulletSpeedIncrease);

				}

				//create a particle blast
				m_pParticlePixelPool->Blast(m_pRenderer, x + 52, y + 9, 2, m_pParticlePixelPool->COLOUR_BLUE, 12, 0);

				break;

			}

		}

		//increase the bullet speed modifier and decrease the total bullets to fire
		bulletSpeedIncrease += 1;
		bulletsToFire -= 1;

	}

	//if the total bullets is less than 0, switch to the move state
	if (bulletsToFire <= 0)
	{
		bossState = E_MOVE;
	}

}

