#pragma once
#include "../../Core/Renderer/ConsoleColours.h"
#include "../../Core/Renderer/Sprite.h"
#include "../../Core/Renderer/ASCIIRenderer.h"



class ASCIIRenderer;
class Sprite;

class GameObject
{
public:

	//functions
	virtual void Initialise(ASCIIRenderer* renderer, CHAR_INFO sprite[], Vector2 size); //init function. takes a given sprite, renderer and size
	virtual void Update() = 0; //update function that can be set by child objects
	virtual void Draw() = 0; //draw function that can be set by child objects
	void ChangeSprite(CHAR_INFO sprite[], Vector2 size); //changes the sprite

	//variables

	//bare minimum pointers
	ASCIIRenderer* m_pRenderer; //pointer to game renderer
	Sprite* m_pSprite; //game object sprite

	//movement variables
	float x; //x position of game object
	float y; //y position of game object
	float speed; //speed variable

private:

};