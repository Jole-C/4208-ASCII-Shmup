#pragma once

#include "../../Core/Renderer/AnimatedSprite.h"

class ASCIIRenderer;

extern const int SCREEN_WIDTH;

const int NUM_DIGITS = 10;
const int DIGIT_WIDTH = 8;
const int DIGIT_HEIGHT = 10;


class ScoreDisplay : public AnimatedSprite
{
public:

	ScoreDisplay();
	~ScoreDisplay();

	void Initialise(Vector2& position);
	void Update(float deltaTime);
	void Render(ASCIIRenderer* pRenderer);

	void SetDigitValue(int value);

private:

	bool m_bInitialised;

};

