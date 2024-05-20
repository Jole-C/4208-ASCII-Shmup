#include "GameObject.h"

//base gameobject class, all game objects that interact with the world derive from this
void GameObject::Initialise(ASCIIRenderer* renderer, CHAR_INFO sprite[], Vector2 size)
{

	//set up renderer
	m_pRenderer = renderer;
	m_pSprite = new Sprite();

	//initialise sprite
	m_pSprite->Initialise(sprite, size);

}

//changes the gameobject sprite
void GameObject::ChangeSprite(CHAR_INFO sprite[], Vector2 size)
{
	m_pSprite->Initialise(sprite, size);
}