#include "ASCIIRenderer.h"
#include <Windows.h>
#include "ConsoleColours.h"
#include "../Utils.h"

ASCIIRenderer::ASCIIRenderer()
:m_ScreenData(NULL)
,m_Width(0)
,m_Height(0)
,m_bInitialised(false)
{
}

ASCIIRenderer::~ASCIIRenderer()
{
	SAFE_DELETE_ARY(m_ScreenData);
}

void ASCIIRenderer::Initialise(int width, int height)
{
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	InitialisePixelSize();
	
	SetWindow(width, height);
	
	m_ScreenData = new CHAR_INFO[m_Width * m_Height];
	
	ClearScreen();

	m_bInitialised = true;
}

void ASCIIRenderer::InitialisePixelSize()
{
	//---Set up font size to look like pixel---
	PCONSOLE_FONT_INFOEX font_size = new CONSOLE_FONT_INFOEX();

	font_size->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(m_hConsole, false, font_size);

	font_size->dwFontSize.X = 8;	//Width of element in buffer
	font_size->dwFontSize.Y = 8;	//Hieght of element in buffer

	SetCurrentConsoleFontEx(m_hConsole, false, font_size);	//Set the new font size
}

void ASCIIRenderer::SetWindow(int Width, int Height)
{

	COORD MaxWindowSize = GetLargestConsoleWindowSize(m_hConsole);

	short targetWidth = min(MaxWindowSize.X, Width);
	short targetHeight = min(MaxWindowSize.Y, Height);

	m_Width = targetWidth;
	m_Height = targetHeight;
	
	SMALL_RECT rect = { 0, 0, targetWidth - 1, targetHeight - 1 };
	COORD coord = { targetWidth, targetHeight };

	bool bufferSizeSet = SetConsoleScreenBufferSize(m_hConsole, coord);
	bool windowInfoSet = SetConsoleWindowInfo(m_hConsole, TRUE, &rect);

	LPCTSTR windowTitle = "4107COMP Assignment 1";
	SetConsoleTitle(windowTitle);
}

void ASCIIRenderer::ClearScreen(WORD attributes)
{
	int numPixels = (m_Width * m_Height);
	for (int i = 0; i < numPixels; i++)
	{
		m_ScreenData[i].Char.UnicodeChar = 0;
		m_ScreenData[i].Char.AsciiChar = 0; // initialise screen to 0 as we create it
		m_ScreenData[i].Attributes = attributes;
	}
}

void ASCIIRenderer::SetPixel(int x, int y, CHAR_INFO* pPixelData)
{
	if (x >= 0 && x < m_Width && y >= 0 && y < m_Height && pPixelData->Attributes != 0)
	{
		m_ScreenData[x + (y * m_Width)] = *pPixelData;
	}
}

void ASCIIRenderer::Render()
{
	static COORD coord = { m_Width, m_Height };
	static COORD coord2 = { 0, 0 };
	static SMALL_RECT write = { 0, 0, m_Width-1, m_Height-1 };			// Region to write to

  	WriteConsoleOutput(m_hConsole, (const CHAR_INFO*)(m_ScreenData), coord, coord2, &write);
}
