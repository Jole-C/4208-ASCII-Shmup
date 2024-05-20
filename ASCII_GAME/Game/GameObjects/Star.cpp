#include "Star.h"
#include "../../Core/Renderer/Sprite.h"
#include "../../Core/Renderer/ConsoleColours.h"
#include "../../Core/Utils.h"

CHAR_INFO spStar[24] = { {'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},
{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE},{'\xdb',F_DARK_BLUE}, };
CHAR_INFO spStar2[24] = { {'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},
{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY}, };
CHAR_INFO spStar3[24] = { {'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_LIGHT_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},
{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY},{'\xdb',F_DARK_GREY}, };

//initialises a star

void Star::Initialise(ASCIIRenderer* renderer)
{

	//set up renderer
	m_pRenderer = renderer;
	m_pSprite = new Sprite();

	//set up random star sprites
	starSprites.push_back(spStar);
	starSprites.push_back(spStar2);
	starSprites.push_back(spStar3);

	//initialise sprite by choosing a random sprite from the 3 choices
	m_pSprite->Initialise(starSprites[rand()%starSprites.size()], Vector2(24,1));

}

//updates the star
void Star::Update()
{

	//move to the left
	x -= speed;

	m_pSprite->SetPosition(x, y);

}

//draws the star
void Star::Draw()
{

	//render
	if (render == true)
	{
		m_pSprite->Render(m_pRenderer);
	}

}
