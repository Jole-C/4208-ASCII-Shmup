#pragma once
#include "../Game/Gamestates.h"
#include "../Core/Renderer/Sprite.h"
#include "../Core/Renderer/ASCIIRenderer.h"
#include "../Core/Renderer/ConsoleColours.h"
#include "../Game/GameObjects/Particles/ParticlePixel.h"
#include <vector>

class ASCIIRenderer;
class Sprite;

class Menu
{
public:

	//functions
	void Initialise(ASCIIRenderer* renderer, ParticlePixelPool* particlePixelPool);
	void Update();
	void Draw();

	//variables
	ASCIIRenderer* m_pRenderer = nullptr;
	Sprite* logoSprite = nullptr;

	E_GAME_STATE gameState;

	int buttonCooldown = 30;

private:

	//functions
	void StartButton();
	void QuitButton();

	double Lerp(float _a, float _b, float _t);

	//variables
	int menuIndex = 0;
	float lerpTime = 0;
};

