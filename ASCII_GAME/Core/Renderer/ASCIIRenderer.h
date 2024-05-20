#pragma once

#include <Windows.h>
#include "ConsoleColours.h"

class ASCIIRenderer
{
public:
	ASCIIRenderer();
	~ASCIIRenderer();

	void Initialise(int width, int height);
	void InitialisePixelSize();


	void Render();

	void SetPixel(int x, int y, CHAR_INFO* pPixelData);
	void ClearScreen(WORD clearColour = F_BLACK);	

private:

	void SetWindow(int width, int height);
	

	HANDLE m_hConsole;
	CHAR_INFO* m_ScreenData;
	short m_Width;
	short m_Height;

	bool m_bInitialised;
};
