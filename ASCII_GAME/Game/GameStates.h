#pragma once

//enum for game state switching
enum E_GAME_STATE
{
	E_GAME_STATE_MAIN_MENU,
	E_GAME_STATE_IN_GAME,
	E_GAME_STATE_LOSE_GAME,
	E_GAME_STATE_WIN_GAME,
};

//enum for boss states
enum E_BOSS_STATES
{
	E_INTRO,
	E_MOVE,
	E_FIRE_CIRCLE,
	E_FIRE_AT_PLAYER,
	E_FIRE_SPREAD,
	E_FIRE_FORWARDS,
};