#pragma once

#include "../../Core/Renderer/Sprite.h"
#include "../../Core/Renderer/ASCIIRenderer.h"
#include <vector>

class ASCIIRenderer;

//star object - does not interact with the world and is rendered as a background
class Star
{

public:

	//functions
	void Initialise(ASCIIRenderer* renderer);
	void Update();
	void Draw();

	//variables

	//movement variables
	int x = 512;
	int y = rand() % 96;
	int speed = rand() % 40 + 20;

	//decide whether to render the sprite
	bool render = true;

private:

	//variables
	ASCIIRenderer* m_pRenderer = nullptr;
	Sprite* m_pSprite = nullptr;

	std::vector<CHAR_INFO*> starSprites;
};

