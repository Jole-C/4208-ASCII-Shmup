#include "ScoreDisplay.h"
#include "../../Core/Renderer/ConsoleColours.h"


CHAR_INFO ScoreDigitSprite[NUM_DIGITS][DIGIT_WIDTH * DIGIT_HEIGHT] =
{
	{
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
	},
	{
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
	},
	{
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
	},
	{
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
	},
	{
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
	},
	{
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
	},
	{
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
	},
	{
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },
	},
	{
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
	},
	{
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK } ,{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,F_BLACK },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },
		{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE } ,{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,WHITE },{ ' ' ,F_BLACK },
	},
};

ScoreDisplay::ScoreDisplay()
	:m_bInitialised(false)
{
}

ScoreDisplay::~ScoreDisplay()
{
}

void ScoreDisplay::Initialise(Vector2& position)
{
	AnimatedSprite::Initialise(&ScoreDigitSprite[0][0], Vector3(DIGIT_WIDTH, DIGIT_HEIGHT, NUM_DIGITS));

	Vector2 startPosition(position.x - (AnimatedSprite::GetSize().x / 2), position.y - (AnimatedSprite::GetSize().y / 2));
	SetPosition(startPosition);

	SetAnimationFrame(0);

	m_bInitialised = true;
}

void ScoreDisplay::Update(float deltaTime)
{
	if (!m_bInitialised)
		return;	
}

void ScoreDisplay::SetDigitValue(int value)
{
	if (value >= 0 && value < NUM_DIGITS)
	{
		SetAnimationFrame(value);
	}
	else
	{
		SetAnimationFrame(0);
	}
}

void ScoreDisplay::Render(ASCIIRenderer* pRenderer)
{
	if (!m_bInitialised)
		return;

	AnimatedSprite::Render(pRenderer);
}

