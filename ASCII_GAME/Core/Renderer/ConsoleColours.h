#pragma once
#ifndef _CONSOLE_COLOURS_H_
#define _CONSOLE_COLOURS_H

#include <Windows.h>

/*
#define BACKGROUND_BRIGHT_RED		BACKGROUND_RED | BACKGROUND_INTENSITY
#define BACKGROUND_BRIGHT_GREEN		BACKGROUND_GREEN | BACKGROUND_INTENSITY
#define BACKGROUND_BRIGHT_BLUE		BACKGROUND_BLUE | BACKGROUND_INTENSITY

#define BACKGROUND_TURQOISE			BACKGROUND_BLUE | BACKGROUND_GREEN
#define BACKGROUND_SKYBLUE			BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY
#define BACKGROUND_PURPLE			BACKGROUND_BLUE | BACKGROUND_RED
#define BACKGROUND_PINK				BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY
#define BACKGROUND_MUSTARD			BACKGROUND_GREEN | BACKGROUND_RED
#define BACKGROUND_YELLOW			BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY

#define BACKGROUND_WHITE			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define BACKGROUND_GREY				BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
#define BACKGROUND_DARK_GREY		BACKGROUND_INTENSITY

#define BACKGROUND_BLACK			0

#define F_RED		FOREGROUND_RED | FOREGROUND_INTENSITY
#define FOREGROUND_BRIGHT_GREEN		FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define F_BLUE		FOREGROUND_BLUE | FOREGROUND_INTENSITY

#define FOREGROUND_TURQOISE			FOREGROUND_BLUE | FOREGROUND_GREEN
#define FOREGROUND_SKYBLUE			FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define FOREGROUND_PURPLE			FOREGROUND_BLUE | FOREGROUND_RED
#define FOREGROUND_PINK				FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY
#define FOREGROUND_MUSTARD			FOREGROUND_GREEN | FOREGROUND_RED
#define FOREGROUND_YELLOW			FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY

#define F_WHITE			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define FOREGROUND_GREY				FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define FOREGROUND_DARK_GREY		FOREGROUND_INTENSITY

#define F_BLACK			0
*/

#define BLACK 0
#define DARK_BLUE 0x0010
#define DARK_PURPLE 0x0020
#define DARK_GREEN 0x0030
#define BROWN 0x0040
#define DARK_GREY 0x0050
#define LIGHT_GREY 0x0060
#define WHITE 0x0070
#define RED 0x0080
#define ORANGE 0x0090
#define YELLOW 0x00A0
#define GREEN 0x00B0
#define BLUE 0x00C0
#define LAVENDER 0x00D0
#define PINK 0x00E0
#define LIGHT_PEACH 0x00F0

#define F_BLACK 0
#define F_DARK_BLUE 0x0001
#define F_DARK_PURPLE 0x0002
#define F_DARK_GREEN 0x0003
#define F_BROWN 0x0004
#define F_DARK_GREY 0x0005
#define F_LIGHT_GREY 0x0006
#define F_WHITE 0x0007
#define F_RED 0x0008
#define F_ORANGE 0x0009
#define F_YELLOW 0x000A
#define F_GREEN 0x000B
#define F_BLUE 0x000C
#define F_LAVENDER 0x000D
#define F_PINK 0x000E
#define F_LIGHT_PEACH 0x000F


//defines variables for easier explosions
/*#define COLOUR_RED[3] = { F_RED, F_ORANGE, F_YELLOW };
#define COLOUR_BLUE[3] = { F_DARK_BLUE, F_BLUE, F_WHITE };
#define COLOUR_GREY[3] = { F_DARK_GREY, F_LIGHT_GREY, WHITE };
*/

#endif
