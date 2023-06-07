#ifndef DounatCatchers_H
#define DounatCatchers_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include "GameObject.h"
#include "Music.h"
#include "Sound.h"
#include <vector>

namespace Engine {

	enum class ScreenState {
		MAIN_MENU,
		IN_GAME,
		OPTION_MENU,
		GAME_OVER
	};

	class DounatCatchers :public Engine::Game
	{
	public:
		DounatCatchers(Setting* setting);
		~DounatCatchers();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		// Main Menu
		int currentButtonIndex = 0;
		int currentButtonGameOverIndex = 0;
		ScreenState screenState;
		vector<Sprite*> platforms;
		vector<Button*> buttons;
		vector<Sprite*> tiles;
		Sprite* backgroundSprite = NULL;
		Sprite* playerIdleSprite = NULL;
		Sprite* instructionSprite = NULL;
		Text* titleFront = NULL;
		Text* titleMiddle = NULL;
		Text* titleBack = NULL;
		Text* highestScoreText = NULL;
		Music* music = NULL;
		Sound* soundJump = NULL;
		Sound* soundRun = NULL;
		Sound* soundEat = NULL;
		Sound* soundMonster = NULL;
		Sound* soundGameOver = NULL;

		int highestScore, score = 0, finalScore = 0;

		void InitMainMenu();
		void InitInGame();
		void InitOptionMenu();
		void InitGameOver();

		void RenderMainMenu();
		void RenderInGame();
		void RenderOptionMenu();
		void RenderGameOver();

		void UpdateMainMenu();
		void UpdateInGame();
		void UpdateOptionMenu();
		void UpdateGameOver();

		void ResetGame();
		void LoadHighestScore();
		void SaveHighestScore();

		// Ingame
		Sprite* backgroundGameSprite = NULL;
		Sprite* monsterSprite = NULL;
		Sprite* monster2Sprite = NULL;
		Sprite* playerSprite = NULL;
		Sprite* donatSprite = NULL;
		Sprite* donatIconSprite = NULL;
		Sprite* chocoIconSprite = NULL;
		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;
		Texture* dotTexture = NULL;
		Text* scoreText = NULL;
		Text* text = NULL;
		Text* levelText = NULL;
		Text* donatText = NULL;
		Text* chocoText = NULL;
		Text* instructionText = NULL;
		vector<GameObject*> monsters;
		vector<GameObject*> monsters2;
		vector<GameObject*> donats;
		vector<GameObject*> chocos;


		float yVelocity = 0, gravity = 0, monsterVelocity = 0.15, monster2Velocity = 0.175, waveTimer = 0.0f, waveSpeedMultiplier = 0.0f;
		bool jump = false, debug = false, flip = true, gameOver = false, isChocoWave = false;
		float startingPlayerX = 0, startingPlayerY = 65, monsterX = 0, monsterY = 0, monster2X = 0, monster2Y = 0, donatX = 700, donatY, chocoX, chocoY;
		int direction = -1, wave = 0, random;

		float spawnMonsterDuration = 0, maxMonsterSpawnTime = 0, spawnMonster2Duration = 0, maxMonster2SpawnTime = 0, spawnDonatDuration = 0, maxDonatSpawnTime = 0, spawnChocoDuration = 0, maxChocoSpawnTime = 0;
		int numMonstersInPool = 0, numMonstersPerSpawn = 0, numMonsters2InPool = 0, numMonsters2PerSpawn = 0, numDonatsInPool = 0, numDonatsPerSpawn = 0, numChocosInPool = 0, numChocosPerSpawn = 0;

		void SpawnMonsterObjects();
		void SpawnMonster2Objects();
		void SpawnDonatObjects();
		void SpawnChocoObjects();
		Sprite* CreateMonsterSprite(Texture* texture);
		Sprite* CreateMonster2Sprite(Texture* texture);
		Sprite* CreateDonatSprite(Texture* texture);
		Sprite* CreateChocoSprite(Texture* texture);

		// Option 
		int currentButtonOptionIndex = 0;
		Sprite* boardSettingSprite = NULL;
		Sprite* titleSettingSprite = NULL;
		Sprite* monSprite = NULL;
		Sprite* moffSprite = NULL;
		Sprite* barSoundSprite = NULL;
		Sprite* barMusicSprite = NULL;
		Text* musicTitle = NULL;
		vector<Button*> buttonsOption;

		// Game Over
		Sprite* backgroundGameOverSprite = NULL;
		Sprite* boardGameOverSprite = NULL;
		Sprite* titleGameOverSprite = NULL;
		Text* yourScoreText = NULL;
		Text* finalScoreText = NULL;
		vector<Button*> buttonsGameOver;
	};
}

#endif

