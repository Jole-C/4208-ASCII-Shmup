#include "Sprite.h"
#include "../Utils.h"
#include "ASCIIRenderer.h"

Sprite::Sprite()
:m_PixelData(NULL)
, m_bInitialised(false)
{
}

Sprite::~Sprite()
{
	for (int i = 0; i < m_Size.y; i++)
	{
		SAFE_DELETE_ARY(m_PixelData[i]);
	}

	SAFE_DELETE_ARY(m_PixelData);
}

void Sprite::Initialise(int* pixels, Vector2& size)
{
	if (m_bInitialised)
		return;

	m_Size = size;

	m_PixelData = new CHAR_INFO*[m_Size.y];

	for (int i = 0; i < m_Size.y; i++)
	{
		m_PixelData[i] = new CHAR_INFO[m_Size.x];
	}

	for (int y = 0; y < m_Size.y; y++)
	{
		for (int x = 0; x < m_Size.x; x++)
		{
			m_PixelData[y][x].Char.UnicodeChar = 0;
			m_PixelData[y][x].Char.AsciiChar = 0;
			m_PixelData[y][x].Attributes = pixels[x + (y*m_Size.x)];
		}
	}
	m_bInitialised = true;
}

void Sprite::Initialise(CHAR_INFO* pixels, Vector2& size)
{
	if (m_bInitialised)
		return;

	m_Size = size;

	m_PixelData = new CHAR_INFO*[m_Size.y];

	for (int i = 0; i < m_Size.y; i++)
	{
		m_PixelData[i] = new CHAR_INFO[m_Size.x];
	}

	for (int y = 0; y < m_Size.y; y++)
	{
		for (int x = 0; x < m_Size.x; x++)
		{
			m_PixelData[y][x] = pixels[x + (y*m_Size.x)];
		}
	}

	m_bInitialised = true;
}

void Sprite::Initialise(char* pixels, int attributes, Vector2& size)
{
	if (m_bInitialised)
		return;

	m_Size = size;

	m_PixelData = new CHAR_INFO*[m_Size.y];

	for (int i = 0; i < m_Size.y; i++)
	{
		m_PixelData[i] = new CHAR_INFO[m_Size.x];
	}

	for (int y = 0; y < m_Size.y; y++)
	{
		for (int x = 0; x < m_Size.x; x++)
		{
			m_PixelData[y][x].Char.UnicodeChar = 0;
			m_PixelData[y][x].Char.AsciiChar = pixels[x + (y*m_Size.x)];
			m_PixelData[y][x].Attributes = attributes;
		}
	}
	m_bInitialised = true;
}

void Sprite::Render(ASCIIRenderer* pRenderer)
{
	if (!m_bInitialised)
		return;

	if (pRenderer)
	{
		for (int y = 0; y < m_Size.y; y++)
		{
			for (int x = 0; x < m_Size.x; x++)
			{
				int posx = m_Position.x + x;
				int posy = m_Position.y + y;
				pRenderer->SetPixel(posx, posy, &m_PixelData[y][x]);
			}
		}
	}
}

bool Sprite::Collides(Sprite& otherSprite)
{
	if (m_Position.x < (otherSprite.GetPosition().x + otherSprite.GetSize().x) &&
		(m_Position.x + m_Size.x) > otherSprite.GetPosition().x &&

		m_Position.y < (otherSprite.GetPosition().y + otherSprite.GetSize().y) &&
		(m_Position.y + m_Size.y) > otherSprite.GetPosition().y)
	{
		return true;
	}
	return false;
}

