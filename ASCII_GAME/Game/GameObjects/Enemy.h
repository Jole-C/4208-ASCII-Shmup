#pragma once
#include "../../Game/GameStates.h"
#include "../../Game/GameObjects/GameObject.h"
#include "../../Game/GameObjects/Particles/ParticlePixel.h"
#include "../../Game/GameObjects/Bullet.h"
#include "../../Game/GameObjects/ScoreDisplay.h"
#include "../../Core/Renderer/ConsoleColours.h"
#include "../GameStates.h"

#include <random>
#include <vector>

class PlayerController;
class Player;
class Sprite;

//the default enemy class
class Enemy : public GameObject
{

public:

	//functions
	void Initialise(ASCIIRenderer* renderer, ParticlePixelPool* particlePool, BulletPool* playerBulletPool, BulletPool* enemyBulletPool, Player* player, float _x, float _y, int enemyType);
	void Update();
	void Draw();
	void FlashWhite();
	float DistanceToPoint(int _x1, int _y1, int _x2, int _y2);
	double DegreesToRadians(int degrees);
	double AngleBetweenPoints(int _x1, int _y1, int _x2, int _y2);
	~Enemy();

	//derived functions
	virtual void Move();
	virtual void Fire();

	//derived variables
	float x; //the x position of the enemy
	float y; //the y position of the enemy
	float speed; //the speed of the enemy
	float flashtime = 0; //the amount of time the enemy should flash white for

	CHAR_INFO sprite; //the sprite of the enemy
	CHAR_INFO spriteWhite; //the white sprite of the enemy

	int hp = 3; //the health of the enemy
	int type; //the type of the enemy

	//the size of the enemy sprite
	Vector2 size = { 0, 0 };

	//a flag for whether the enemy should be removed or not
	bool canBeRemoved;

	//firing variables
	int fireCooldown;
	int maxFireCooldown;


	ParticlePixelPool* m_pParticlePixelPool = nullptr; //a pointer to the particle pool
	BulletPool* m_pPlayerBulletPool = nullptr; //a pointer to the player controller's bullet pool
	BulletPool* m_pEnemyBulletPool = nullptr; //a pointer to the enemy controller's bullet pool
	Player* m_pPlayer = nullptr; //a pointer to the player itself

};

class EnemyMove : public Enemy
{

public:

	//functions
	virtual void Move();
	virtual void Fire();

	//variables
	bool canBeRemoved = false; //flag for if the enemy can be removed
	int speed = (rand() % 4) + 1; //the speed at which the enemy moves
	int hp = 7; //the health of the enemy
	int type = 0; //the type of enemy, for use by some methods for identification purposes
	int flashTime = 100; //the time at which the enemy should flash white for

private:

	//the size of the sprite that the enemy uses
	Vector2 size = { 52, 19 };

};

class EnemyMoveFireAim : public Enemy
{

public:

	//functions
	virtual void Move();
	virtual void Fire();

	//variables
	bool canBeRemoved = false; //flag for if the enemy can be removed
	int speed = (rand() % 4) + 1; //the speed at which the enemy moves
	int hp = 5; //the health of the enemy
	int type = 1; //the type of enemy, for use by some methods for identification purposes
	int flashTime = 100; //the time at which the enemy should flash white for

private:

	//variables

	//firing variables
	float stopCooldown = 120;
	float maxStopCooldown = 120;
	float fireCooldown = 5;

	//the size of the sprite that the enemy uses
	Vector2 size = { 56, 19 };

};

class EnemyMoveFireForwards : public Enemy
{

public:

	//functions
	virtual void Move();
	virtual void Fire();

	//variables
	bool canBeRemoved = false; //flag for if the enemy can be removed
	
	//movement variables
	int speed = (rand() % 4) + 1; //speed to move at 
	int chosenX = rand() % 250 + 200; //the chosen x position to stop moving at

	int hp = 5; //the health of the enemy
	int type = 2; //the type of enemy, for use by some methods for identification purposes
	int fireType = rand() % 3; //the fire type of the enemy, for it to decide between the 3 firing states
	int flashTime = 100; //the time at which the enemy should flash white for

private:

	//variables

	//firing variables
	float stopCooldown = ((rand() % 10) * 6) + 120;
	float maxStopCooldown = stopCooldown;
	float fireCooldown = 5;

	//the size of the sprite that the enemy uses
	Vector2 size = { 52, 17 };

};

class EnemyController
{

public:

	//functions
	void HardReset(); //hard resets the entire enemy controller, clearing everything
	void InitialiseEnemyController(ASCIIRenderer* renderer, ParticlePixelPool* particlePixelPool, BulletPool* playerBulletPool, Player* player); //initialises the enemy controller, only to be called once
	void UpdateEnemies(); //updates all enemies
	void DrawEnemies(); //draws all enemies
	void ResetState(); //soft resets the enemy controller, does not clear anything
	Enemy* MakeEnemies(); //makes a new enemy

	//variables
	//a pool of bullets for use by all enemies
	BulletPool* m_pEnemyBulletPool = nullptr;

	//handle score and multiplier
	int score = 0;
	int multiplier = 1;
	int multiplierReset = 300;
	int multiplierKills = 0;

	int enemyFreezeTime = 70; //the amount of time to freeze an enemy in place for
	int maxEnemyFreezeTime = 70; //the max amount of time to reset enemyFreezeTime to
	int bossHP = 150; //the hp of the boss
	int gameDoneTimer = 150; //the time before the gameDone flag is set to true
	bool bossSpawned = false; //a variable to tell the game when a boss has been spawned

	//variables that allow for switching between game state and game won/game over states
	bool gameDone = false;
	bool gameWon = false;
	bool gameOver = false;

private:

	//variables
	ParticlePixelPool* m_pParticlePixelPool = nullptr; //a pointer to the game's particle system
	BulletPool* m_pPlayerBulletPool = nullptr; //a pointer to the player controller's bullet pool
	ScoreDisplay* m_pScoreDisplay = nullptr; //a pointer to the game's score display
	ASCIIRenderer* m_pRenderer = nullptr; //a pointer to the game's ascii renderer
	Player* m_pPlayer = nullptr; //a pointer to the player itself

	std::vector<Enemy*> enemyList; //a vector to store all enemies

	//variables that handle enemy spawning
	int totalEnemies = 50;
	int currentEnemies = 0;
	int enemySpawnCooldown = 120;
	int enemySpawnChance = 0;

};

class Boss : public Enemy
{

public:

	//functions
	void Update();
	void ResetFiringStates();
	void MoveState();
	void FireState();

	//variables
	E_BOSS_STATES bossState = E_INTRO; //the state of the boss

	//movement variables for the boss
	int x = 515;
	int y = 40;
	int baseY;
	double moveAngle = 0;

	//the boss hp, and the enemy type
	int hp = 100;
	int type = 3;

	//variables for firing bullets, these are randomised each time the game switches to a fire state
	int bulletsToFire;
	int bulletCooldown;
	int maxBulletCooldown;
	int bulletSpeed;
	int spreadCount = 3;
	int bulletSpeedIncrease = 0;
	float circularBulletCount = 5;

private:

	//variables
	Vector2 size = { 66, 20 };

};