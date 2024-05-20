#include "GameStates.h"
#include "GameObjects/Star.h"
#include "../Core/Renderer/Sprite.h"
#include <vector>
#include "../Game/GameObjects/ScoreDisplay.h"
#include "../Game/GameObjects/PlayerController.h"
#include "../Game/GameObjects/Particles/ParticlePixel.h"
#include "Menu.h"
#include "../Game/GameObjects/Enemy.h"
#include <string>

class ASCIIRenderer;
class Star;
class ScoreDisplay;

using namespace std;

class Game
{
public:

	//functions
	void Initialise();
	void Run();

	//variables
	int score = 0;
	
private:

	//functions
	void InitialiseRenderer();
	void InitialiseStars();
	void InitialiseObjects();
	void InitialiseStarRenderers();
	void InitialiseObjectRenderers();

	void Update();
	void UpdateStars();
	void UpdateObjects();
	void EnemyUpdate();

	void Render();
	void RenderScore(string scoreString);
	void RenderStars();
	void RenderObjects();

	void HardReset();

	//variables
	ASCIIRenderer* m_pRenderer = nullptr;
	PlayerController* m_pPlayerController = new PlayerController;
	ParticlePixelPool* m_pParticlePixelPool = new ParticlePixelPool;
	EnemyController* m_pEnemyController = new EnemyController;

	ScoreDisplay* m_pMultiplier = new ScoreDisplay();
	ScoreDisplay* m_pPlayerLives = new ScoreDisplay();

	Sprite* m_pMultiplierBar = new Sprite();
	Sprite* m_pBossHP = new Sprite();

	Menu* gameMenu = new Menu;

	bool m_bInitialised = false;
	bool m_bExitApp = false;
	bool bossSpawned = false;
	int bossWarningTime = 120;

	std::vector<Star*> stars;
	std::vector<ScoreDisplay*> scoreDisplayList;

	E_GAME_STATE gameState = E_GAME_STATE_MAIN_MENU;

	int starCount = 20;

	int textCooldown = 120;
};