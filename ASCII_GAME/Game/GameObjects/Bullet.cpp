#include "Bullet.h"
#include "../../Core/Renderer/ConsoleColours.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This class specifies a bullet object that moves in an angle at a speed with a specific sprite, and a controller to handle creating these bullets by resetting //
//the position of an available bullet. Other objects can access bullets to handle collisions																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Define bullet for friendly bullet sprite, EG player
//(16x8 size)
CHAR_INFO spBulletFriendly[128] = 
{ 
	{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_BLUE},{'\xdb',F_BLUE},
	{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
	{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
	{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},
	{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_BLUE},{'\xdb',F_BLUE},
	{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},
	{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{'\xdb',F_BLUE},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK}
};

//Define bullet for enemy bullet sprite, EG enemy
//(16x8 size)
CHAR_INFO spBulletEnemy[128] =
{
	{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_RED},{'\xdb',F_RED},
	{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_RED},{'\xdb',F_RED},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
	{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},
	{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_RED},{'\xdb',F_RED},
	{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_RED},{'\xdb',F_RED},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_RED},{'\xdb',F_RED},
	{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_WHITE},{'\xdb',F_RED},{'\xdb',F_RED},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},
	{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{'\xdb',F_RED},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK},{' ',F_BLACK}
};

/*
	INITIALISE A NEW BULLET
*/
void Bullet::InitialiseRenderer(ASCIIRenderer* renderer)
{

	//call the gameobject initialisation function, passing in sprite, game renderer, and sprite size
	Initialise(renderer, spBulletFriendly, size);

}


/*
	SET THE BULLET TO THE GIVEN PARAMETERS
*/
void Bullet::Set(float _x, float _y, bool _isHostileToPlayer, float _lifetime, double _angle, float _speed)
{

	//reset the bullet position and other parameters - to the player's eye, this looks like a new bullet
	x = _x;
	y = _y;
	angle = _angle;
	isHostileToPlayer = _isHostileToPlayer;
	lifetime = _lifetime;
	hSpeed = _speed * cos(_angle);
	vSpeed = _speed * sin(_angle);

	//initialise a different sprite depending on whether the bullet is hostile to the player or not
	if (_isHostileToPlayer == true)
	{
		Initialise(m_pRenderer, spBulletEnemy, size);
	}
	else
	{
		Initialise(m_pRenderer, spBulletFriendly, size);
	}

}


/*
	MOVE THE BULLET
*/
void Bullet::Move()
{

	//move the bullet and set the sprite position to match - the exact speed is calculated once for a single frame in the set method. This should increase performance with many bullets on screen
	x += hSpeed;
	y += vSpeed;
	m_pSprite->SetPosition(x, y);

	//decrease lifetime
	lifetime -= 1;

}

/*
	UPDATE THE BULLET
*/
void Bullet::Update()
{
	//call the movement function once a frame
	Move();
}

/*
	DRAW THE BULLET
*/
void Bullet::Draw()
{
	//render the player
	m_pSprite->Render(m_pRenderer);
}

/*
	CHECK IF A BULLET IS AVAILABLE
*/
bool Bullet::Available()
{
	//if the bullet's lifetime is less than 0, it is available to become a new bullet
	return lifetime <= 0;
}


/*
	INITIALISE A BULLET POOL
*/
void BulletPool::InitialiseBulletPool(ASCIIRenderer* renderer, int bulletPoolSize)
{

	//initialise all bullets then put them into a vector
	poolSize = bulletPoolSize;
	m_pRenderer = renderer;

	for (int i = 0; i < bulletPoolSize; i++)
	{

		Bullet* currentBullet = new Bullet;
		currentBullet->InitialiseRenderer(m_pRenderer);

		bullets.push_back(currentBullet);

	}

}

/*
	UPDATE ALL BULLETS
*/
void BulletPool::Update()
{

	//for each bullet in our pool, update it if it is available
	for (int i = 0; i < poolSize; i++)
	{

		if (bullets[i]->Available() == false)
		{
			bullets[i]->Update();
		}

	}

}

/*
	DRAW ALL BULLETS
*/
void BulletPool::Draw()
{

	//for each bullet in our pool, draw it if it is available
	for (int i = 0; i < poolSize; i++)
	{

		if (bullets[i]->Available() == false)
		{
			bullets[i]->Draw();
		}

	}

}

/*
	CREATE A BULLET
*/
void BulletPool::CreateBullet(float x, float y, bool isHostileToPlayer, float lifetime, float angle, float speed)
{

	//for each bullet in our pool, check in order for availability
	//for the first available bullet, reset it's position, and exit the loop
	for (int i = 0; i < poolSize; i++)
	{
		if (bullets[i]->Available())
		{
			bullets[i]->Set(x, y, isHostileToPlayer, lifetime, angle, speed);
			return;
		}    
	}

} 

/*
	MAKE ALL BULLETS AVAILABLE
*/
void BulletPool::HardReset()
{

	//resets all bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->lifetime = -1;
	}

}