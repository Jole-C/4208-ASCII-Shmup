#pragma once

#include "../../../Core/Renderer/Sprite.h"
#include "../../../Core/Renderer/ASCIIRenderer.h"
#include "../../../Core/Renderer/ConsoleColours.h"
#include <vector>

class ASCIIRenderer;

//purely visual object that simply renders and moves a sprite - does not interact with game world
class ParticlePixel
{
public:

	//functions
	void Initialise(ASCIIRenderer* renderer, float _x, float _y, float _angle, float _speed, unsigned int _colour_const, float _lifetime); //initialises a new particle, should be called at pool creation
	void Update(); //updates the particle
	void Draw(); //draws the particle
	bool Available(); //returns true or false depending on whether the particle is available to become a new particle
	void Set(float _x, float _y, float _angle, float _speed, unsigned int _colour_const, float _lifetime); //sets the particles parameters to give the illusion of a new particle

	//variables

	//movement variables
	float x = 560; 
	float y = 560; 
	float hSpeed = 0; //cos calculation is converted to horizontal movement speed
	float vSpeed = 0; //sin calculation is converted to vertical movement speed
	float angle = 0; //angle of movement, used in sin and cos calculations

	//lifetime of the particle
	float lifetime = 0;

	unsigned int colour = F_BLACK; //default colour of the particle

	ASCIIRenderer* m_pRenderer = nullptr; //ascii renderer of the particle
	Sprite* m_pSprite = new Sprite(); //sprite of the particle

private:

};

//global controller of a group of particles, offers facilities for easier particle creation, such as premade effects to make code more streamlined. also offers several arrays with groups of colours,
//for random colour choosing
class ParticlePixelPool
{
public:

	//functions
	double DegreesToRadians(int degrees); //converts degrees to radians
	void InitialiseParticlePixelPool(ASCIIRenderer* renderer, int poolSize); //initialises a new particle pool
	void Create(ASCIIRenderer* renderer, float _x, float _y, float _angle, float _speed, unsigned int _colour_const, float _lifetime); //"creates" a new particle
	void HardReset(); //hard resets the entire system, making all particles available
	void Blast(ASCIIRenderer* renderer, float _x, float _y, float _amount, unsigned int _colours[3], int _maxSpread, int _baseAngle); //creates a "blast" of particles in an arc
	void Area(ASCIIRenderer* renderer, float _x, float _y, float _xMax, float _yMax, float _amount, unsigned int _colours[3]); //creates unmoving/slowmoving particles in a given square
	void Explosion(ASCIIRenderer* renderer, float _x, float _y, float _amount, unsigned int _colours[]); //creates an explosion
	void Update(); //updates all particles
	void Draw(); //draws all particles

	//variables
	int poolSize = 550; //amount of particles
	std::vector<ParticlePixel*> particles; //vector holding all particles assigned to this pool

	//defines variables for random colour choices
	unsigned int COLOUR_RED[3] = { F_RED, F_ORANGE, F_YELLOW };
	unsigned int COLOUR_BLUE[3] = { F_DARK_BLUE, F_BLUE, F_WHITE };
	unsigned int COLOUR_GREY[3] = { F_DARK_GREY, F_LIGHT_GREY, WHITE };

};

