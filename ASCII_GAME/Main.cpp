#include <windows.h>
#include "Game\Game.h"


int main()
{
	
	//Define custom palette
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole, &info);

	info.ColorTable[0] = RGB(0, 0, 0);//BLACK
	info.ColorTable[1] = RGB(29, 43, 83);//DARK BLUE
	info.ColorTable[2] = RGB(126, 37, 83);//DARK PURPLE
	info.ColorTable[3] = RGB(0, 135, 81);//DARK GREEN
	info.ColorTable[4] = RGB(171, 82, 54);//BROWN
	info.ColorTable[5] = RGB(95, 87, 79);//DARK GREY 
	info.ColorTable[6] = RGB(194, 195, 199);//LIGHT GREY
	info.ColorTable[7] = RGB(255, 241, 232);//WHITE
	info.ColorTable[8] = RGB(255, 0, 77);//RED
	info.ColorTable[9] = RGB(255, 163, 0);//ORANGE
	info.ColorTable[10] = RGB(255, 236, 39);//YELLOW
	info.ColorTable[11] = RGB(0, 228, 54);//GREEN
	info.ColorTable[12] = RGB(41, 173, 255);//BLUE
	info.ColorTable[13] = RGB(131, 118, 156);//LAVENDER
	info.ColorTable[14] = RGB(255, 119, 168);//PINK
	info.ColorTable[15] = RGB(255, 204, 170);//LIGHT PEACH
	

	SetConsoleScreenBufferInfoEx(hConsole, &info);
	

	Game game;

	game.Initialise();

	game.Run();

	return 0;
}
