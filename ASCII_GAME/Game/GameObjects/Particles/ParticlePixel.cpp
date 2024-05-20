#include "ParticlePixel.h"
#define _USE_MATH_DEFINES
#include <math.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This class contains a particle object that simply moves in a direction with angle, colour and speed. It also contains		//
//A pool/Controller. This controller contains methods for creating particle effects, and handles a set number of particles.	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	INITIALISE A NEW PARTICLE
*/
void ParticlePixel::Initialise(ASCIIRenderer* renderer, float _x, float _y, float _angle, float _speed, unsigned int _colour_const, float _lifetime)
{

	//initialise particle with given paramaters
	m_pRenderer = renderer;
	colour = _colour_const;

	x = _x;
	y = _y;
	angle = _angle;
	hSpeed = _speed;
	vSpeed = _speed;
	lifetime = -1;

}

/*
	SET A PARTICLE TO A GIVEN POSITION WITH SET PARAMETERS
*/
void ParticlePixel::Set(float _x, float _y, float _angle, float _speed, unsigned int _colour_const, float _lifetime)
{

	//reset particle so it can be a different particle - the speed is calculated here to increase performance with many particles on screen
	colour = _colour_const;

	x = _x;
	y = _y;
	angle = _angle;
	hSpeed = _speed * cos(_angle);
	vSpeed = _speed * sin(_angle);
	lifetime = _lifetime;

}

/*
	UPDATE THE PARTICLE
*/
void ParticlePixel::Update()
{

	//move particle if it is available
	if (Available() == false)
	{

		x += hSpeed;
		y += vSpeed;

		m_pSprite->SetPosition(x, y);

	}

	//decrease lifetime
	lifetime -= 1;

}

/*
	DRAW THE PARTICLE
*/
void ParticlePixel::Draw()
{

	//draw particle if it is available
	if (lifetime > 0)
	{
		m_pSprite->Render(m_pRenderer);
	}

}

/*
	RETURN TRUE IF THE PARTICLE IS AVAILABLE FOR USE BY THE SYSTEM
*/
bool ParticlePixel::Available()
{
	//if lifetime is less than 0, set availability to become a new particle
	return lifetime <= 0;
}

//degrees to radians
double ParticlePixelPool::DegreesToRadians(int degrees)
{
	return (degrees * 3.14159265359) / 180;
}

/*
	INITIALISE THE PARTICLE POOL
*/
void ParticlePixelPool::InitialiseParticlePixelPool(ASCIIRenderer* renderer, int _poolSize)
{

	//sets the size of the pool and initialises all particles, then places them into a vector
	poolSize = _poolSize;

	for (int i = 0; i < poolSize; i++)
	{

		ParticlePixel* currentParticle = new ParticlePixel;
		currentParticle->Initialise(renderer, -10, -10, 0, 0, 0, 0);

		particles.push_back(currentParticle);

	}

}

/*
	UPDATE THE PARTICLE POOL
*/
void ParticlePixelPool::Update()
{

	//for each particle in our pool, update it
	for (int i = 0; i < poolSize; i++)
	{
		particles[i]->Update();
	}

}

/*
	DRAW THE PARTICLE POOL
*/
void ParticlePixelPool::Draw()
{

	//for each particle in our pool, draw it
	for (int i = 0; i < poolSize; i++)
	{
		particles[i]->Draw();
	}

}

/*
	CREATE A PARTICLE BY SETTING IT TO THE GIVEN PARAMETERS
*/
void ParticlePixelPool::Create(ASCIIRenderer* renderer, float _x, float _y, float _angle, float _speed, unsigned int _colour_const, float _lifetime)
{

	//for each particle in our pool, check order for availability
	//for the first available bullet, reset it to the given parameters, then exit the loop
	for (int i = 0; i < poolSize; i++)
	{

		if (particles[i]->Available())
		{

			//create a new sprite array local to this method, use it to initialise a new sprite. this handles colour changing
			//this array should be removed from memory after this method is finished, to conserve memory (rather than being initialised at the top)
			CHAR_INFO sprite[32] = { {' ',F_BLACK},{' ',F_BLACK},{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},
			{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},{'\xdb',_colour_const},{' ',F_BLACK},{' ',F_BLACK} };

			//delete the old sprite
			delete(particles[i]->m_pSprite);

			//initialise a new sprite
			particles[i]->m_pSprite = new Sprite();
			particles[i]->m_pSprite->Initialise(sprite,Vector2(8,4));

			//set the particle to the given parameters
			particles[i]->Set(_x, _y, (_angle * M_PI) / 180, _speed, _colour_const, _lifetime);

			//break out of the loop, as another particle is not needed
			return;

		}

	}

}

/*
	HARD RESET THE PARTICLE SYSTEM
*/
void ParticlePixelPool::HardReset()
{

	//hard resets all particles by making them all available
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i]->lifetime = -1;
	}

}

/*
	CREATE AN EXPLOSION EFFECT
*/
void ParticlePixelPool::Explosion(ASCIIRenderer* renderer, float _x, float _y, float _amount, unsigned int _colours[3])
{

	//create an explosion - makes code elsewhere look nicer
	for (int i = 0; i < _amount; i++)
	{
		Create(renderer, _x + 27, _y + 9, rand() % 360, rand() % 5 + 2, _colours[rand() % 3], rand() % 15 + 5);
	}

}

/*
	CREATE A BLAST EFFECT
*/
void ParticlePixelPool::Blast(ASCIIRenderer* renderer, float _x, float _y, float _amount, unsigned int _colours[3], int _maxSpread, int _baseAngle)
{

	//create a shotgun blast effect - makes code elsewhere look nicer
	for (int i = 0; i < _amount; i++)
	{

		//ensure that the base angle is never 0
		if (_maxSpread == 0)
		{
			_maxSpread = 1;
		}

		Create(renderer, _x, _y, _baseAngle + (rand() % (_maxSpread * 2)) - _maxSpread, rand() % 5 + 2, _colours[rand() % 3], rand() % 15 + 5);

	}

}

/*
	CREATES PARTICLES IN A GIVEN AREA
*/
void ParticlePixelPool::Area(ASCIIRenderer* renderer, float _x, float _y, float _xMax, float _yMax, float _amount, unsigned int _colours[3])
{
	
	//creates particles in the given area, note these particles do not have speed
	for (int i = 0; i < _amount; i++)
	{

		int randomX = _x + rand() % (int)(_xMax - _x);
		int randomY = _y + rand() % (int)(_yMax - _y);

		Create(renderer, randomX, randomY, rand() % 360, 0.2, _colours[rand() % 3], rand() % 30);

	}

}