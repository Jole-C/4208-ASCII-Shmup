#pragma once

#include "../GameObjects/Bullet.h"
#include "../GameObjects/Enemy.h"

//player representation in the game world, fires bullets and moves around among other things
class Player : public GameObject
{
public:

	//functions
	virtual void Update(); //update method overriden from gameobject
	virtual void Draw(); //draw method overriden from gameobject

	void Move(); //move the player
	void ResetState(); //resets player state
	void Fire(); //fires bullets
	void InitialiseRenderer(ASCIIRenderer* renderer);

	//variables
	BulletPool* m_pPlayerBulletPool = nullptr; //pointer to the player controller
	BulletPool* m_pEnemyBulletPool = nullptr; //pointer to the enemy bullet pool
	EnemyController* m_pEnemyController = nullptr; //pointer to the enemy controller
	ParticlePixelPool* m_pParticlePixelPool = nullptr; //pointer to the particle pool

	//x and y position of player
	double x = -30;
	double y = 40;

	//player lives and invincibility frames
	int lives = 3;
	int invincibilityCooldown = -1;

private:

	//variables

	//player friction
	double fric = 0.82;

	//player fire cooldown and max firecooldown
	double fireCooldown = 5;
	double maxFireCooldown = 5;

	//sprite size for player
	Vector2 size = { 54, 19 };

};

//controller of a player - talks to other objects and initialises as well as hard resets the player. controls bullet pools, and passes required pointers and references to the player
class PlayerController
{
public:

	//functions
	void HardReset(); //hard resets all player variables upon game over/game won, prevents need to create a new player
	void Init(ASCIIRenderer* renderer, ParticlePixelPool* particlePool); //initialises the player and the player controller
	void PassEnemyController(EnemyController* enemyController); //passes the enemy controller to the player - must be called after enemy controller creation (which in turn must be called after init)
	void Update(); //updates the bullet pool and player
	void Draw(); //draws the bullet pool and players

	//variables
	Player* m_pPlayer = nullptr; //pointer to the player created by this controller
	BulletPool* m_pPlayerBulletPool = nullptr; //pointer to a bullet pool created by this controller

private:


};

