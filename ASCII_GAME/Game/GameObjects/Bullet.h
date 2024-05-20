#pragma once
#include "../../Game/GameObjects/GameObject.h"
#include <vector>

//bullet object that directly interacts with the game world
class Bullet : public GameObject
{
public:

	//functions
	void Update(); //updates the bullet
	void Draw(); //draws the bullet

	void Move(); //moves the bullet
	void Set(float x, float y, bool isHostileToPlayer, float lifetime, double angle, float speed); //sets a bullet to a given position, giving the illusion of a new particle being created
	void InitialiseRenderer(ASCIIRenderer* renderer); //initialises the bullet renderer
	bool Available(); //returns true or false depending on whether the given bullet is available to become a new particle

	//variables
	float speed = 0; //speed of the bullet
	float hSpeed = 0; //cos calculations are converted to horizontal speed
	float vSpeed = 0; //sin calculations are converted to vertical speed
	float x = 0; //x position of the particle
	float y = 0; //y position of the particle
	float angle = 0; //angle of the particle used for sin and cos calculations
	float lifetime = -5; //lifetime of the particle

	bool isHostileToPlayer = false; //changes bullet parameters depending on whether the bullet destroys the player or not

private:

	//size of the sprite
	Vector2 size = {16, 8};

};

//controller of a set of bullets
class BulletPool
{
public:
	
	//functions
	void CreateBullet(float x, float y, bool isHostileToPlayer, float lifetime, float angle, float speed); //creates a bullet if it is available
	void HardReset(); //hard resets the entire pool, making all bullets available
	void InitialiseBulletPool(ASCIIRenderer* renderer, int bulletPoolSize); //initialises a bullet pool, should only be called once
	void Update(); //updates all bullets in the pool
	void Draw(); //draws all bullets in the pool

	//variables
	ASCIIRenderer* m_pRenderer = nullptr; //pointer to game renderer
	std::vector<Bullet*> bullets; //vector containing all bullets
	int poolSize; //number of bullets in the pool

private:

};