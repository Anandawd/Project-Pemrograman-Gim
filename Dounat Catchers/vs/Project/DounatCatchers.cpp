#include "DounatCatchers.h"

using namespace Engine;
using namespace std;

DounatCatchers::DounatCatchers(Setting* setting) :Game(setting)
{
	screenState = ScreenState::MAIN_MENU;

	// Membaca highest score dari dalam file
	LoadHighestScore();
}

DounatCatchers::~DounatCatchers()
{
	// Menyimpan highest score ke dalam file
	SaveHighestScore();

	// delete semua sprite dan object
	delete backgroundSprite;
	delete playerIdleSprite;
	delete instructionSprite;
	delete titleFront;
	delete titleMiddle;
	delete titleBack;
	delete highestScoreText;
	delete music;
	delete soundJump;
	delete soundRun;
	delete soundEat;
	delete soundMonster;
	delete soundGameOver;

	delete backgroundGameSprite;
	delete monsterSprite;
	delete monster2Sprite;
	delete playerSprite;
	delete donatSprite;
	delete donatIconSprite;
	delete chocoIconSprite;
	delete dotSprite1;
	delete dotSprite2;
	delete dotSprite3;
	delete dotSprite4;
	delete dotTexture;
	delete scoreText;
	delete text;
	delete levelText;
	delete donatText;
	delete chocoText;
	delete instructionText;

	delete boardSettingSprite;
	delete titleSettingSprite;
	delete monSprite;
	delete moffSprite;
	delete barSoundSprite;
	delete barMusicSprite;
	delete musicTitle;

	delete backgroundGameOverSprite;
	delete boardGameOverSprite;
	delete titleGameOverSprite;
	delete yourScoreText;
	delete finalScoreText;
}

void DounatCatchers::Init()
{
	InitMainMenu();
	InitInGame();
	InitOptionMenu();
	InitGameOver();
}

void DounatCatchers::Update()
{
	if (ScreenState::MAIN_MENU == screenState) {
		UpdateMainMenu();
	}
	else if (ScreenState::IN_GAME == screenState) {
		UpdateInGame();
	}
	else if (ScreenState::OPTION_MENU == screenState) {
		UpdateOptionMenu();
	}
	else if (ScreenState::GAME_OVER == screenState) {
		UpdateGameOver();
	}
}

void DounatCatchers::Render()
{
	if (ScreenState::MAIN_MENU == screenState) {
		RenderMainMenu();
	}
	else if (ScreenState::IN_GAME == screenState) {
		RenderInGame();
	}
	else if (ScreenState::OPTION_MENU == screenState) {
		RenderOptionMenu();
	}
	else if (ScreenState::GAME_OVER == screenState) {
		RenderGameOver();
	}
}

void DounatCatchers::InitMainMenu()
{
	// Membuat background
	Texture* bgTexture = new Texture("assets/Background/background_menu.png");
	backgroundSprite = new Sprite(bgTexture, defaultSpriteShader, defaultQuad);
	backgroundSprite->SetSize(setting->screenWidth, setting->screenHeight);

	// Membuat Title
	titleFront = new Text("assets/Font/Abaddon-Bold.ttf", 72, defaultTextShader);
	titleFront->SetText("DOUNAT CATCHERS");
	titleFront->SetPosition(setting->screenWidth - 700, setting->screenHeight - 120);
	titleFront->SetColor(250, 153, 0);

	titleMiddle = new Text("assets/Font/Abaddon-Bold.ttf", 72, defaultTextShader);
	titleMiddle->SetText("DOUNAT CATCHERS");
	titleMiddle->SetPosition(setting->screenWidth - 698, setting->screenHeight - 122);
	titleMiddle->SetColor(255, 170, 0);

	titleBack = new Text("assets/Font/Abaddon-Bold.ttf", 72, defaultTextShader);
	titleBack->SetText("DOUNAT CATCHERS");
	titleBack->SetPosition(setting->screenWidth - 695, setting->screenHeight - 125);
	titleBack->SetColor(106, 72, 41);

	// Membuat Text Highest Score
	highestScoreText = new Text("assets/Font/Abaddon-Bold.ttf", 24, defaultTextShader);
	highestScoreText->SetPosition(40, setting->screenHeight - 40);
	highestScoreText->SetColor(106, 72, 41);

	// Membuat objek player
	Texture* playerTexture = new Texture("assets/Player/player.png");

	playerIdleSprite = new Sprite(playerTexture, defaultSpriteShader, defaultQuad);
	playerIdleSprite->SetNumXFrames(10);
	playerIdleSprite->SetNumYFrames(3);
	playerIdleSprite->AddAnimation("idle", 0, 3);
	playerIdleSprite->AddAnimation("run", 10, 19);
	playerIdleSprite->AddAnimation("jump", 20, 23);
	playerIdleSprite->SetAnimationDuration(400);
	playerIdleSprite->SetScale(6.5f);
	playerIdleSprite->SetPosition(0, 80);

	// Animation player idle
	playerIdleSprite->PlayAnim("idle");

	// Membuat objek intruction
	Texture* texInstruction = new Texture("assets/Misc/instruction.png");
	instructionSprite = new Sprite(texInstruction, defaultSpriteShader, defaultQuad);
	instructionSprite->SetNumXFrames(3);
	instructionSprite->SetNumYFrames(1);
	instructionSprite->AddAnimation("inmenuscreen", 0, 2);
	instructionSprite->SetAnimationDuration(1000);
	instructionSprite->SetPosition(setting->screenWidth - 505, 100);

	// Animation instruction
	instructionSprite->PlayAnim("inmenuscreen");

	// Membuat objek button
	Texture* btnTexture = new Texture("assets/Misc/button.png");

	Sprite* playSprite = new Sprite(btnTexture, defaultSpriteShader, defaultQuad);
	playSprite->SetNumXFrames(15);
	playSprite->SetNumYFrames(1);
	playSprite->AddAnimation("normal", 2, 2);
	playSprite->AddAnimation("hover", 2, 3);
	playSprite->AddAnimation("press", 3, 4);
	playSprite->SetAnimationDuration(400);

	Sprite* optionSprite = new Sprite(btnTexture, defaultSpriteShader, defaultQuad);
	optionSprite->SetNumXFrames(15);
	optionSprite->SetNumYFrames(1);
	optionSprite->AddAnimation("normal", 7, 7);
	optionSprite->AddAnimation("hover", 7, 8);
	optionSprite->AddAnimation("press", 8, 9);
	optionSprite->SetAnimationDuration(400);

	Sprite* exitSprite = new Sprite(btnTexture, defaultSpriteShader, defaultQuad);
	exitSprite->SetNumXFrames(15);
	exitSprite->SetNumYFrames(1);
	exitSprite->AddAnimation("normal", 12, 12);
	exitSprite->AddAnimation("hover", 12, 13);
	exitSprite->AddAnimation("press", 13, 14);
	exitSprite->SetAnimationDuration(400);

	// Membuat objek Button
	Button* playButton = new Button(playSprite, "play");
	playButton->SetPosition(setting->screenWidth - 392, setting->screenHeight - 265);
	buttons.push_back(playButton);

	Button* optionButton = new Button(optionSprite, "option");
	optionButton->SetPosition(setting->screenWidth - 392, setting->screenHeight - 365);
	buttons.push_back(optionButton);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition(setting->screenWidth - 392, setting->screenHeight - 465);
	buttons.push_back(exitButton);

	// Set Play Button into Active
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Menambahkan music
	music = new Music("assets/Music/music.ogg");
	music->SetVolume(50);
	music->Play(true);

	// Menambahkan sound effect
	soundJump = new Sound("assets/Music/jump.wav");
	soundJump->SetVolume(50);

	soundRun = new Sound("assets/Music/run.wav");
	soundRun->SetVolume(50);

	soundEat = new Sound("assets/Music/eat.wav");
	soundEat->SetVolume(50);

	soundMonster = new Sound("assets/Music/monster-roar.wav");
	soundMonster->SetVolume(50);

	soundGameOver = new Sound("assets/Music/game-over.wav");
	soundGameOver->SetVolume(50);

	// Menambahkan Input Mapping
	inputManager->AddInputMapping("next", SDLK_DOWN);
	inputManager->AddInputMapping("prev", SDLK_UP);
	inputManager->AddInputMapping("press", SDLK_RETURN);
}

void DounatCatchers::InitOptionMenu()
{
	// Membuat Title
	Texture* settingTitleTexture = new Texture("assets/Misc/setting-title.png");
	titleSettingSprite = new Sprite(settingTitleTexture, defaultSpriteShader, defaultQuad);
	titleSettingSprite->SetPosition(487, 586);

	// Membuat board
	Texture* boardTexture = new Texture("assets/Misc/setting-board.png");
	boardSettingSprite = new Sprite(boardTexture, defaultSpriteShader, defaultQuad);
	boardSettingSprite->SetPosition(204, 136);

	// Membuat objek button back
	Texture* btnBackTexture = new Texture("assets/Misc/back-to-mainmenu.png");
	Sprite* backSprite = new Sprite(btnBackTexture, defaultSpriteShader, defaultQuad);
	backSprite->SetNumXFrames(3);
	backSprite->SetNumYFrames(1);
	backSprite->AddAnimation("normal", 0, 0);
	backSprite->AddAnimation("hover", 0, 1);
	backSprite->AddAnimation("press", 1, 2);
	backSprite->SetAnimationDuration(400);

	// Membuat Music Title
	musicTitle = new Text("assets/Font/Abaddon-Bold.ttf", 32, defaultTextShader);
	musicTitle->SetText("MUSIC");
	musicTitle->SetPosition((setting->screenWidth / 2) - (musicTitle->GetScaleWidth() / 2), 473);
	musicTitle->SetColor(63, 151, 167);

	// Membuat objek music button
	Texture* btnMusicOnTexture = new Texture("assets/Misc/volume-on-btn.png");

	// music on
	monSprite = new Sprite(btnMusicOnTexture, defaultSpriteShader, defaultQuad);
	monSprite->SetNumXFrames(6);
	monSprite->SetNumYFrames(1);
	monSprite->AddAnimation("normal-off", 0, 0);
	monSprite->AddAnimation("hover-off", 0, 1);
	//monSprite->AddAnimation("press-to-on", 2, 3);
	monSprite->AddAnimation("hover-on", 3, 4);
	//monSprite->AddAnimation("press-to-off", 4, 5);
	monSprite->AddAnimation("normal-on", 3, 3);
	monSprite->SetAnimationDuration(400);

	monSprite->PlayAnim("normal-on");

	Texture* btnMusicOffTexture = new Texture("assets/Misc/volume-off-btn.png");

	// music off
	moffSprite = new Sprite(btnMusicOffTexture, defaultSpriteShader, defaultQuad);
	moffSprite->SetNumXFrames(6);
	moffSprite->SetNumYFrames(1);
	moffSprite->AddAnimation("normal-off", 0, 0);
	moffSprite->AddAnimation("hover-off", 0, 1);
	//moffSprite->AddAnimation("press-to-on", 2, 3);
	moffSprite->AddAnimation("hover-on", 3, 4);
	//moffSprite->AddAnimation("press-to-off", 4, 5);
	moffSprite->AddAnimation("normal-on", 3, 3);
	moffSprite->SetAnimationDuration(400);

	// Membuat objek button volume
	Texture* btnSoundTexture = new Texture("assets/Misc/se-volume-btn.png");

	Sprite* sevSprite = new Sprite(btnSoundTexture, defaultSpriteShader, defaultQuad);
	sevSprite->SetNumXFrames(5);
	sevSprite->SetNumYFrames(1);
	sevSprite->AddAnimation("normal", 0, 0);
	sevSprite->AddAnimation("hover", 0, 1);
	sevSprite->AddAnimation("volume-up", 1, 2);
	sevSprite->AddAnimation("volume-down", 3, 4);
	sevSprite->SetAnimationDuration(400);

	Texture* btnMusicTexture = new Texture("assets/Misc/music-volume-btn.png");

	Sprite* mvSprite = new Sprite(btnMusicTexture, defaultSpriteShader, defaultQuad);
	mvSprite->SetNumXFrames(5);
	mvSprite->SetNumYFrames(1);
	mvSprite->AddAnimation("normal", 0, 0);
	mvSprite->AddAnimation("hover", 0, 1);
	mvSprite->AddAnimation("volume-up", 1, 2);
	mvSprite->AddAnimation("volume-down", 3, 4);
	mvSprite->SetAnimationDuration(400);

	// Menambahkan objek button
	Button* backButton = new Button(backSprite, "back");
	backButton->SetPosition(25, 615);
	buttonsOption.push_back(backButton);

	Button* monButton = new Button(monSprite, "music-on");
	monButton->SetPosition(455, 419);
	buttonsOption.push_back(monButton);

	Button* moffButton = new Button(moffSprite, "music-off");
	moffButton->SetPosition(640, 419);
	buttonsOption.push_back(moffButton);

	Button* sevButton = new Button(sevSprite, "sound-effect");
	sevButton->SetPosition(414, 321);
	buttonsOption.push_back(sevButton);

	Button* mvButton = new Button(mvSprite, "music");
	mvButton->SetPosition(414, 223);
	buttonsOption.push_back(mvButton);

	// Set Play Button into Active
	currentButtonOptionIndex = 0;
	buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::HOVER);

	for (Button* b : buttonsOption) {
		if ("music-on" == b->GetButtonName()) {
			if (music->IsPaused() == false) {
				b->SetButtonState(Engine::ButtonState::NORMAL_ON);
			}
			break;
		}
		if ("music-off" == b->GetButtonName()) {
			if (music->IsPaused() == true) {
				b->SetButtonState(Engine::ButtonState::NORMAL_ON);
			}
			break;
		}
	}

	// Menambahkan bar volume
	Texture* barTexture = new Texture("assets/Misc/bar.png");
	barSoundSprite = new Sprite(barTexture, defaultSpriteShader, defaultQuad);
	barSoundSprite->SetNumXFrames(2);
	barSoundSprite->SetNumYFrames(1);
	barSoundSprite->AddAnimation("normal", 0, 0);
	barSoundSprite->PlayAnim("normal");
	barSoundSprite->SetPosition(442, 323);

	barMusicSprite = new Sprite(barTexture, defaultSpriteShader, defaultQuad);
	barMusicSprite->SetNumXFrames(2);
	barMusicSprite->SetNumYFrames(1);
	barMusicSprite->AddAnimation("normal", 0, 0);
	barMusicSprite->PlayAnim("normal");
	barMusicSprite->SetPosition(442, 225);
	barMusicSprite->SetSize(barMusicSprite->GetScaleWidth() * ((music->GetVolume() / 100) * 10), barMusicSprite->GetScaleHeight());

	// Menambahkan Input Mapping
	inputManager->AddInputMapping("next", SDLK_DOWN);
	inputManager->AddInputMapping("prev", SDLK_UP);
	inputManager->AddInputMapping("press", SDLK_RETURN);
	inputManager->AddInputMapping("mainmenu", SDLK_ESCAPE);
	inputManager->AddInputMapping("volumeup", SDLK_RIGHT);
	inputManager->AddInputMapping("volumedown", SDLK_LEFT);
}

void DounatCatchers::InitGameOver()
{
	// Membuat background
	Texture* bgTexture = new Texture("assets/Background/background_gameover.png");
	backgroundGameOverSprite = new Sprite(bgTexture, defaultSpriteShader, defaultQuad);
	backgroundGameOverSprite->SetSize(setting->screenWidth, setting->screenHeight);

	// Membuat Title
	Texture* titleTexture = new Texture("assets/Misc/title_gameover.png");
	titleGameOverSprite = new Sprite(titleTexture, defaultSpriteShader, defaultQuad);
	titleGameOverSprite->SetPosition((setting->screenWidth / 2) - (titleGameOverSprite->GetScaleWidth() / 2), setting->screenHeight - 141);

	// Membuat board
	Texture* boardTexture = new Texture("assets/Misc/board_gameover.png");
	boardGameOverSprite = new Sprite(boardTexture, defaultSpriteShader, defaultQuad);
	boardGameOverSprite->SetPosition((setting->screenWidth / 2) - (boardGameOverSprite->GetScaleWidth() / 2), setting->screenHeight - 526);

	// Membuat text your score
	yourScoreText = new Text("assets/Font/Abaddon-Bold.ttf", 28, defaultTextShader);
	yourScoreText->SetPosition(550, setting->screenHeight - 241);
	yourScoreText->SetColor(106, 72, 41);
	yourScoreText->SetText("YOUR SCORE:");

	// Membuat Score
	finalScoreText = new Text("assets/Font/Abaddon-Bold.ttf", 96, defaultTextShader);
	finalScoreText->SetPosition((setting->screenWidth / 2) - (finalScoreText->GetScaleWidth() / 2), setting->screenHeight - 334);
	finalScoreText->SetColor(106, 72, 41);

	// Membuat button
	Texture* btnTexture = new Texture("assets/Misc/button_gameover.png");

	Sprite* playAgainSprite = new Sprite(btnTexture, defaultSpriteShader, defaultQuad);
	playAgainSprite->SetNumXFrames(10);
	playAgainSprite->SetNumYFrames(1);
	playAgainSprite->AddAnimation("normal", 7, 7);
	playAgainSprite->AddAnimation("hover", 7, 8);
	playAgainSprite->AddAnimation("press", 8, 8);
	playAgainSprite->SetScale(0.7);
	playAgainSprite->SetAnimationDuration(400);

	Sprite* mainMenuSprite = new Sprite(btnTexture, defaultSpriteShader, defaultQuad);
	mainMenuSprite->SetNumXFrames(10);
	mainMenuSprite->SetNumYFrames(1);
	mainMenuSprite->AddAnimation("normal", 2, 2);
	mainMenuSprite->AddAnimation("hover", 2, 3);
	mainMenuSprite->AddAnimation("press", 3, 4);
	mainMenuSprite->SetScale(0.7);
	mainMenuSprite->SetAnimationDuration(400);

	// Membuat objek Button
	Button* playAgainButton = new Button(playAgainSprite, "play-again");
	playAgainButton->SetPosition(392, setting->screenHeight - 447);
	buttonsGameOver.push_back(playAgainButton);

	Button* mainMenuButton = new Button(mainMenuSprite, "main-menu");
	mainMenuButton->SetPosition(643, setting->screenHeight - 447);
	buttonsGameOver.push_back(mainMenuButton);

	// Set Play Button into Active
	currentButtonGameOverIndex = 0;
	buttonsGameOver[currentButtonGameOverIndex]->SetButtonState(Engine::ButtonState::HOVER);
}

void DounatCatchers::InitInGame()
{
	// Membuat background
	Texture* bgTexture = new Texture("assets/Background/background.png");
	backgroundGameSprite = new Sprite(bgTexture, defaultSpriteShader, defaultQuad);
	backgroundGameSprite->SetSize(setting->screenWidth, setting->screenHeight);

	// Membuat Text Score
	scoreText = new Text("assets/Font/Abaddon-Bold.ttf", 24, defaultTextShader);
	scoreText->SetPosition(32, setting->screenHeight - 40);
	scoreText->SetColor(106, 72, 41);
	score = 0;

	// Membuat teks Level
	levelText = new Text("assets/Font/Abaddon-Bold.ttf", 24, defaultTextShader);
	levelText->SetPosition(32, setting->screenHeight - 80);
	levelText->SetColor(106, 72, 41);

	// Membuat teks donat
	donatText = new Text("assets/Font/Abaddon-Bold.ttf", 24, defaultTextShader);
	donatText->SetPosition(32, setting->screenHeight - 120);
	donatText->SetColor(106, 72, 41);

	// Menambahkan icon donat
	Texture* donatIconTexture = new Texture("assets/Foods/donut.png");
	donatIconSprite = new Sprite(donatIconTexture, defaultSpriteShader, defaultQuad);
	donatIconSprite->SetNumXFrames(1);
	donatIconSprite->SetNumYFrames(1);
	donatIconSprite->SetPosition(120, setting->screenHeight - 124);

	// Membuat teks choco
	chocoText = new Text("assets/Font/Abaddon-Bold.ttf", 24, defaultTextShader);
	chocoText->SetPosition(32, setting->screenHeight - 160);
	chocoText->SetColor(106, 72, 41);

	// Menambahkan icon choco
	Texture* chocoIconTexture = new Texture("assets/Foods/choco.png");
	chocoIconSprite = new Sprite(chocoIconTexture, defaultSpriteShader, defaultQuad);
	chocoIconSprite->SetNumXFrames(1);
	chocoIconSprite->SetNumYFrames(1);
	chocoIconSprite->SetPosition(120, setting->screenHeight - 164);

	// Membuat teks instruction 
	instructionText = new Text("assets/Font/Abaddon-Bold.ttf", 24, defaultTextShader);
	instructionText->SetPosition((setting->screenWidth / 2) - (instructionText->GetScaleWidth() / 2), setting->screenHeight - 240);
	instructionText->SetColor(184, 236, 255);

	// Membuat Tiles
	Texture* platformTexture = new Texture("assets/Tiles/tile2.png");
	vec2 start = vec2(-32, 0);
	for (int i = 0; i < 21; i++) {
		Sprite* platformSprite = new Sprite(platformTexture, defaultSpriteShader, defaultQuad);
		platformSprite->SetPosition(start.x + i * 64, start.y);
		platformSprite->SetSize(64, 64);
		platformSprite->SetBoundingBoxSize(platformSprite->GetScaleWidth(), platformSprite->GetScaleHeight());
		platforms.push_back(platformSprite);
	}

	// Membuat player
	Texture* playerTexture = new Texture("assets/Player/player.png");

	playerSprite = new Sprite(playerTexture, defaultSpriteShader, defaultQuad);
	playerSprite->SetNumXFrames(10);
	playerSprite->SetNumYFrames(3);
	playerSprite->AddAnimation("idle", 0, 3);
	playerSprite->AddAnimation("run", 10, 19);
	playerSprite->AddAnimation("jump", 20, 23);
	playerSprite->SetAnimationDuration(80);
	playerSprite->SetScale(1.5f);
	playerSprite->SetPosition(startingPlayerX, startingPlayerY);

	playerSprite->SetBoundingBoxSize(playerSprite->GetScaleWidth() - (24 * playerSprite->GetScale()), playerSprite->GetScaleHeight() - (4 * playerSprite->GetScale()));

	// Spawn monster setting
	maxMonsterSpawnTime = 0;
	numMonstersPerSpawn = 1;
	numMonstersInPool = 1;

	// Membuat object monster
	Texture* monsterTexture = new Texture("assets/Enemies/monster.png");
	for (int i = 0; i < numMonstersInPool; i++) {
		GameObject* monster = new GameObject(CreateMonsterSprite(monsterTexture));
		monsters.push_back(monster);
	}


	// Spawn monster 2 setting
	maxMonster2SpawnTime = 0;
	numMonsters2PerSpawn = 1;
	numMonsters2InPool = 1;

	// Membuat object monster 2
	Texture* monster2Texture = new Texture("assets/Enemies/monster.png");
	for (int i = 0; i < numMonsters2InPool; i++) {
		GameObject* monster2 = new GameObject(CreateMonster2Sprite(monster2Texture));
		monsters2.push_back(monster2);
	}

	// Spawn donat setting
	maxDonatSpawnTime = 100;
	numDonatsPerSpawn = 1;
	numDonatsInPool = 1;

	// Membuat objek donat
	Texture* donatTexture = new Texture("assets/Foods/donat-idle.png");
	for (int i = 0; i < numDonatsInPool; i++) {
		GameObject* donat = new GameObject(CreateDonatSprite(donatTexture));
		donats.push_back(donat);
	}

	// Spawn choco setting
	maxChocoSpawnTime = 500;
	numChocosPerSpawn = 1;
	numChocosInPool = 1;

	// Membuat objek choco
	Texture* chocoTexture = new Texture("assets/Foods/choco-idle.png");
	for (int i = 0; i < numChocosInPool; i++) {
		GameObject* choco = new GameObject(CreateChocoSprite(chocoTexture));
		chocos.push_back(choco);
	}

	// Cek apakah wave merupakan kelipatan 5
	if (wave % 5 == 0) {
		isChocoWave = true;
	}
	else {
		isChocoWave = false;
	}

	// Add input mappings
	inputManager->AddInputMapping("mainmenu", SDLK_ESCAPE);
	inputManager->AddInputMapping("Run Right", SDLK_d);
	inputManager->AddInputMapping("Run Left", SDLK_a);
	inputManager->AddInputMapping("Jump", SDLK_SPACE);
	inputManager->AddInputMapping("Jump", SDLK_w);

	// This dot sprite is for visual debugging (to see the actual bounding box) 
	dotTexture = new Texture("dot.png");
	dotSprite1 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite2 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite3 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite4 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);

	// Set debug
	debug = true;
}

void DounatCatchers::RenderMainMenu()
{
	// Render background
	backgroundSprite->Draw();

	// Render instruction
	instructionSprite->Draw();

	// Render player
	playerIdleSprite->Draw();

	// Render title
	titleBack->Draw();
	titleMiddle->Draw();
	titleFront->Draw();

	// Render highest score
	highestScoreText->Draw();

	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
}

void DounatCatchers::RenderOptionMenu()
{
	// Render background
	backgroundSprite->Draw();

	// Render setting title
	titleSettingSprite->Draw();

	// Render board
	boardSettingSprite->Draw();

	// Render title
	musicTitle->Draw();

	// Render all buttons
	for (Button* b : buttonsOption) {
		b->Draw();
	}

	// Render bar
	barSoundSprite->Draw();
	barMusicSprite->Draw();
}

void DounatCatchers::RenderGameOver()
{
	// Render background
	backgroundGameOverSprite->Draw();

	// Render title
	titleGameOverSprite->Draw();

	// Render board
	boardGameOverSprite->Draw();

	// Render your score text
	yourScoreText->Draw();

	// Render score
	finalScoreText->Draw();

	// Render all button
	for (Button* b : buttonsGameOver) {
		b->Draw();
	}
}

void DounatCatchers::RenderInGame()
{
	// Render background
	backgroundGameSprite->Draw();

	// Render highest score
	highestScoreText->Draw();

	// Render score
	scoreText->Draw();

	// Render level text
	levelText->Draw();

	// Render donat text
	donatText->Draw();

	// Render donat icon
	donatIconSprite->Draw();

	// Render choco text
	chocoText->Draw();

	// Render choco icon
	chocoIconSprite->Draw();

	// Render instruction text
	instructionText->Draw();

	// Render platform
	for (Sprite* s : platforms) {
		s->Draw();
	}

	// Render player
	playerSprite->Draw();

	// Render all objects
	for (GameObject* monster : monsters) {
		monster->Draw();
	}

	if (wave != 0) {
		for (GameObject* monster2 : monsters2) {
			monster2->Draw();
		}
	}

	for (GameObject* donat : donats) {
		donat->Draw();
	}

	if (wave != 0 && isChocoWave) {
		for (GameObject* choco : chocos) {
			choco->Draw();
		}
	}

	/*
	// Render debug
	if (debug) {
		dotSprite1->Draw();
		dotSprite2->Draw();
		dotSprite3->Draw();
		dotSprite4->Draw();
	}
	*/
}

void DounatCatchers::UpdateMainMenu()
{
	// Update instruction animation
	instructionSprite->Update(GetGameTime());

	// Update player animation
	playerIdleSprite->Update(GetGameTime());

	// Update posisi highest score
	highestScoreText->SetPosition(40, setting->screenHeight - 40);

	// Update highest score
	highestScoreText->SetText("Highest Score : " + to_string(highestScore));

	if (inputManager->IsKeyReleased("next")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Next Button
		currentButtonIndex = currentButtonIndex < buttons.size() - 1 ? currentButtonIndex + 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (inputManager->IsKeyReleased("prev")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Prev Button
		currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (inputManager->IsKeyReleased("press")) {
		Button* b = buttons[currentButtonIndex];

		b->SetButtonState(Engine::ButtonState::PRESS);

		if ("play" == b->GetButtonName()) {
			screenState = Engine::ScreenState::IN_GAME;
		}
		else if ("option" == b->GetButtonName()) {
			screenState = Engine::ScreenState::OPTION_MENU;
		}
		else if ("exit" == b->GetButtonName()) {
			state = Engine::State::EXIT;
		}
	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(GetGameTime());
	}
}

void DounatCatchers::UpdateOptionMenu()
{
	// Update button active
	if (inputManager->IsKeyReleased("next")) {
		// Set previous button to normal state
		if ("music-on" == buttonsOption[currentButtonOptionIndex]->GetButtonName()) {
			if (music->IsPaused() == false) {
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::NORMAL_ON);
			}
			else {
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::NORMAL_OFF);
			}
		}
		else if ("music-off" == buttonsOption[currentButtonOptionIndex]->GetButtonName()) {
			if (music->IsPaused() == true) {
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::NORMAL_ON);
			}
			else {
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::NORMAL_OFF);
			}
		}
		else {
			buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		}

		// Next Button
		currentButtonOptionIndex = currentButtonOptionIndex < buttonsOption.size() - 1 ? currentButtonOptionIndex + 1 : currentButtonOptionIndex;

		// Set current button to hover state
		if ("music-on" == buttonsOption[currentButtonOptionIndex]->GetButtonName()) {
			if (music->IsPaused() == false)
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::HOVER_ON);
			else {
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::HOVER_OFF);
			}
		}
		else if ("music-off" == buttonsOption[currentButtonOptionIndex]->GetButtonName()) {
			if (music->IsPaused() == true)
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::HOVER_ON);
			else {
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::HOVER_OFF);
			}
		}
		else {
			buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::HOVER);
		}
	}

	if (inputManager->IsKeyReleased("prev")) {
		// Set previous button to normal state
		if ("music-on" == buttonsOption[currentButtonOptionIndex]->GetButtonName()) {
			if (music->IsPaused() == false)
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::NORMAL_ON);
			else {
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::NORMAL_OFF);
			}
		}
		else if ("music-off" == buttonsOption[currentButtonOptionIndex]->GetButtonName()) {
			if (music->IsPaused() == true)
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::NORMAL_ON);
			else {
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::NORMAL_OFF);
			}
		}
		else {
			buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		}

		// Prev Button
		currentButtonOptionIndex = currentButtonOptionIndex > 0 ? currentButtonOptionIndex - 1 : currentButtonOptionIndex;

		// Set current button to hover state
		if ("music-on" == buttonsOption[currentButtonOptionIndex]->GetButtonName()) {
			if (music->IsPaused() == false)
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::HOVER_ON);
			else {
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::HOVER_OFF);
			}
		}
		else if ("music-off" == buttonsOption[currentButtonOptionIndex]->GetButtonName()) {
			if (music->IsPaused() == true)
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::HOVER_ON);
			else {
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::HOVER_OFF);
			}
		}
		else if ("sound-effect" == buttonsOption[currentButtonOptionIndex]->GetButtonName()) {
			buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::HOVER);
		}
		else if ("music" == buttonsOption[currentButtonOptionIndex]->GetButtonName()) {
			buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::HOVER);
		}
		else {
			buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::HOVER);
		}
	}

	if (inputManager->IsKeyReleased("press")) {
		// Set current button to press state
		if ("back" == buttonsOption[currentButtonOptionIndex]->GetButtonName()) {
			buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::PRESS);
			screenState = Engine::ScreenState::MAIN_MENU;
		}

		else if ("music-on" == buttonsOption[currentButtonOptionIndex]->GetButtonName()) {
			buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::NORMAL_ON);
			buttonsOption[currentButtonOptionIndex + 1]->SetButtonState(Engine::ButtonState::NORMAL_OFF);
			music->Resume();
		}
		else if ("music-off" == buttonsOption[currentButtonOptionIndex]->GetButtonName()) {
			buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::NORMAL_ON);
			buttonsOption[currentButtonOptionIndex - 1]->SetButtonState(Engine::ButtonState::NORMAL_OFF);
			music->Pause();
		}
	}

	// Update bar
	int multiplerSoundBar = ((soundJump->GetVolume() * 10) / 100);
	barSoundSprite->SetSize((80 * multiplerSoundBar) - 8, 28);
	barSoundSprite->Update(GetGameTime());

	int multiplerMusicBar = ((music->GetVolume() * 10) / 100);
	barMusicSprite->SetSize((80 * multiplerMusicBar) - 8, 28);
	barMusicSprite->Update(GetGameTime());


	// Mengatur sound effect volume dan music volume
	if ("sound-effect" == buttonsOption[currentButtonOptionIndex]->GetButtonName()) {
		if (inputManager->IsKeyReleased("volumeup")) {
			if (soundJump->GetVolume() >= 0 && soundJump->GetVolume() <= 100) {
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::VOLUME_UP);
				soundJump->SetVolume(soundJump->GetVolume() + 10);
				soundRun->SetVolume(soundRun->GetVolume() + 10);
				soundEat->SetVolume(soundEat->GetVolume() + 10);
				soundMonster->SetVolume(soundMonster->GetVolume() + 10);
				soundGameOver->SetVolume(soundGameOver->GetVolume() + 10);
			}

		}
		else if (inputManager->IsKeyReleased("volumedown")) {
			if (soundJump->GetVolume() >= 0 && soundJump->GetVolume() <= 100) {
				buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::VOLUME_DOWN);
				soundJump->SetVolume(soundJump->GetVolume() - 10);
				soundRun->SetVolume(soundRun->GetVolume() - 10);
				soundEat->SetVolume(soundEat->GetVolume() - 10);
				soundMonster->SetVolume(soundMonster->GetVolume() - 10);
				soundGameOver->SetVolume(soundGameOver->GetVolume() - 10);
			}
		}
	}
	else if ("music" == buttonsOption[currentButtonOptionIndex]->GetButtonName()) {
		if (inputManager->IsKeyReleased("volumeup")) {
			buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::VOLUME_UP);
			music->SetVolume(music->GetVolume() + 10);
		}
		else if (inputManager->IsKeyReleased("volumedown")) {
			buttonsOption[currentButtonOptionIndex]->SetButtonState(Engine::ButtonState::VOLUME_DOWN);
			music->SetVolume(music->GetVolume() - 10);
		}
	}


	/*
	if (inputManager->IsKeyReleased("volumeup")) {
		music->SetVolume(music->GetVolume() + 10);
	}
	if (inputManager->IsKeyReleased("volumedown")) {
		music->SetVolume(music->GetVolume() - 10);
	}

	*/

	// Update All buttons
	for (Button* b : buttonsOption) {
		b->Update(GetGameTime());
	}
}

void DounatCatchers::UpdateGameOver()
{
	// Update final score
	finalScoreText->SetPosition((setting->screenWidth / 2) - (finalScoreText->GetScaleWidth() / 2) - 5, setting->screenHeight - 334);
	finalScoreText->SetText(to_string(finalScore));

	if (inputManager->IsKeyReleased("next")) {
		// Set previous button to normal state
		buttonsGameOver[currentButtonGameOverIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Next Button
		currentButtonGameOverIndex = currentButtonGameOverIndex < buttonsGameOver.size() - 1 ? currentButtonGameOverIndex + 1 : currentButtonGameOverIndex;
		// Set current button to hover state
		buttonsGameOver[currentButtonGameOverIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (inputManager->IsKeyReleased("prev")) {
		// Set previous button to normal state
		buttonsGameOver[currentButtonGameOverIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Prev Button
		currentButtonGameOverIndex = currentButtonGameOverIndex > 0 ? currentButtonGameOverIndex - 1 : currentButtonGameOverIndex;
		// Set current button to hover state
		buttonsGameOver[currentButtonGameOverIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (inputManager->IsKeyReleased("press")) {
		// Set current button to press state
		Button* b = buttonsGameOver[currentButtonGameOverIndex];
		b->SetButtonState(Engine::ButtonState::PRESS);

		if ("play-again" == b->GetButtonName()) {
			screenState = Engine::ScreenState::IN_GAME;
		}
		else if ("main-menu" == b->GetButtonName()) {
			screenState = Engine::ScreenState::MAIN_MENU;
		}
	}

	for (Button* b : buttonsGameOver) {
		b->Update(GetGameTime());
	}
}

void DounatCatchers::UpdateInGame()
{
	// Back to main menu
	if (inputManager->IsKeyReleased("mainmenu")) {
		ResetGame();
		screenState = ScreenState::MAIN_MENU;
	}

	// Mengubah posisi highest score
	highestScoreText->SetPosition(setting->screenWidth - highestScoreText->GetScaleWidth() - 32, setting->screenHeight - 40);

	// Update highest score
	highestScoreText->SetText("Highest Score : " + to_string(highestScore));

	// Update score
	scoreText->SetText("Your Score : " + to_string(score));

	// Update timer
	donatText->SetText("Donat        : +10 score");

	// Update timer
	chocoText->SetText("Choco        : +50 score");

	// Update timer
	instructionText->SetText("press A to walk left, press D to walk right, press W/SPACE to jump");
	instructionText->SetPosition((setting->screenWidth / 2) - (instructionText->GetScaleWidth() / 2), setting->screenHeight - 200);

	// Play anim idle
	playerSprite->PlayAnim("idle");

	// Move player sprite using keyboard
	vec2 oldPlayerPos = playerSprite->GetPosition();
	float x = oldPlayerPos.x, y = oldPlayerPos.y;
	if (inputManager->IsKeyPressed("Run Right")) {
		playerSprite->PlayAnim("run");
		x += 0.2f * GetGameTime();
		playerSprite->SetFlipHorizontal(false);
	}

	if (inputManager->IsKeyPressed("Run Left")) {
		playerSprite->PlayAnim("run");
		x -= 0.2f * GetGameTime();
		playerSprite->SetFlipHorizontal(true);
	}

	playerSprite->SetPosition(x, y);

	for (Sprite* s : platforms) {
		if (s->GetBoundingBox()->CollideWith(playerSprite->GetBoundingBox())) {
			x = oldPlayerPos.x;
			playerSprite->SetPosition(x, y);
			break;
		}
	}

	// jump player sprite
	float airTime = 0.0f;
	const float maxAirTime = 100.0f;
	const float jumpGravity = 0.15f;

	if (inputManager->IsKeyPressed("Jump") && !jump) {
		playerSprite->PlayAnim("jump");
		gravity = 2.0f;
		yVelocity = 2.0f;
		jump = true;
		airTime = 0.0f;
		soundJump->Play(false);
	}

	if (y > 0) {
		yVelocity -= jumpGravity;
		airTime += GetGameTime();
		if (airTime >= maxAirTime) {
			jump = false;
		}
	}
	else if (y < 0) {
		jump = false;
		yVelocity = 0;
		y = 0;
	}

	y += yVelocity * (1.5 * GetGameTime());
	playerSprite->SetPosition(x, y);

	for (Sprite* s : platforms) {
		if (s->GetBoundingBox()->CollideWith(playerSprite->GetBoundingBox())) {
			y = oldPlayerPos.y;
			playerSprite->SetPosition(x, y);
			yVelocity = 0;
			jump = false;
			break;
		}
	}

	playerSprite->Update(GetGameTime());

	// Time to spawn monster
	if (spawnMonsterDuration >= maxMonsterSpawnTime) {
		SpawnMonsterObjects();
		spawnMonsterDuration = 0;
	}

	// Update monster
	for (GameObject* o : monsters) {
		o->Update(GetGameTime());

		for (Sprite* s : platforms) {
			if (s->GetBoundingBox()->CollideWith(o->GetBoundingBox())) {
				monsterX += (direction * monsterVelocity * GetGameTime());
				monsterY = s->GetScaleHeight();
				o->SetFlipHorizontal(flip);
				o->SetPosition(monsterX, monsterY);
				break;
			}
		}
	}

	// Count spawn monster duration
	spawnMonsterDuration += 30 - GetGameTime();

	if (wave != 0) {
		// Time to spawn monster
		if (spawnMonster2Duration >= maxMonster2SpawnTime) {
			SpawnMonster2Objects();
			spawnMonster2Duration = 0;
		}

		// Update monster
		for (GameObject* o : monsters2) {
			o->Update(GetGameTime());

			for (Sprite* s : platforms) {
				if (s->GetBoundingBox()->CollideWith(o->GetBoundingBox())) {
					monster2X += (direction * monster2Velocity * GetGameTime());
					monster2Y = s->GetScaleHeight();
					o->SetFlipHorizontal(flip);
					o->SetPosition(monster2X, monster2Y);
					break;
				}
			}
		}

		// Count spawn monster duration
		spawnMonster2Duration += 30 - GetGameTime();

		// deteksi collision jika player terkena monster maka game over
		for (GameObject* monster2 : monsters2) {
			//monster->Update(GetGameTime());

			if (playerSprite->GetBoundingBox()->CollideWith(monster2->GetBoundingBox())) {
				gameOver = true;
				soundGameOver->Play(false);
				finalScore = score;
				screenState = ScreenState::GAME_OVER;
				monster2->SetIsDie();
				ResetGame();
				break;
			}
		}
	}

	// Time to spawn donat 
	if (spawnDonatDuration >= maxDonatSpawnTime) {
		SpawnDonatObjects();
		spawnDonatDuration = 0;
	}

	// Update donat
	for (GameObject* donat : donats) {
		donat->Update(GetGameTime());

		for (Sprite* s : platforms) {
			if (s->GetBoundingBox()->CollideWith(donat->GetBoundingBox())) {
				donatY = s->GetScaleHeight();
				donat->SetPosition(donatX, donatY);
				break;
			}
		}

		if (donat->IsDie()) {
			continue;
		}

		if (playerSprite->GetBoundingBox()->CollideWith(donat->GetBoundingBox())) {
			soundEat->Play(false);
			score += 10;
			donat->SetIsDie();
			break;
		}
		break;
	}

	// Count spawn monster duration
	spawnDonatDuration += GetGameTime();

	// Cek apakah wave merupakan kelipatan 5
	if (wave % 5 == 0) {
		isChocoWave = true;
	}
	else {
		isChocoWave = false;
	}

	// Time to spawn donat
	if (wave != 0 && isChocoWave) {
		if (spawnChocoDuration >= maxChocoSpawnTime) {
			SpawnChocoObjects();
			spawnChocoDuration = 0;
		}

		// Update donat to get score
		for (GameObject* choco : chocos) {
			choco->Update(GetGameTime());

			for (Sprite* s : platforms) {
				if (s->GetBoundingBox()->CollideWith(choco->GetBoundingBox())) {
					chocoY = s->GetScaleHeight();
					choco->SetPosition(chocoX, chocoY);
					break;
				}
			}

			if (choco->IsDie()) {
				continue;
			}

			if (playerSprite->GetBoundingBox()->CollideWith(choco->GetBoundingBox())) {
				soundEat->Play(false);
				score += 50;
				choco->SetIsDie();
				break;
			}
			break;
		}

		// Count spawn monster duration
		spawnChocoDuration += GetGameTime();
	}

	// Meningkatkan kecepatan monster berdasarkan wave
	waveTimer += GetGameTime();
	if (waveTimer >= 7000) {

		if (wave <= 2) {
			waveSpeedMultiplier = 1.0f + (wave * 0.05f); // kecepatan monster meningkat 5% setiap wave
		}
		else if (wave <= 4) {
			waveSpeedMultiplier = 1.0f + (wave * 0.04f); // kecepatan monster meningkat 4% setiap wave
		}
		else if (wave <= 6) {
			waveSpeedMultiplier = 1.0f + (wave * 0.03f); // kecepatan monster meningkat 3% setiap wave
		}
		else if (wave <= 8) {
			waveSpeedMultiplier = 1.0f + (wave * 0.02f); // kecepatan monster meningkat 2% setiap wave
		}
		else if (wave <= 10) {
			waveSpeedMultiplier = 1.0f + (wave * 0.01f); // kecepatan monster meningkat 1% setiap wave
		}
		else if (wave > 10) {
			waveSpeedMultiplier = 1.0f + (wave * 0.001f); // kecepatan monster meningkat 0.1% setiap wave
		}


		for (GameObject* monster : monsters) {
			monster->Update(GetGameTime());

			monsterVelocity *= waveSpeedMultiplier;
			monsterX += (direction * monsterVelocity * GetGameTime());
			monster->SetPosition(monsterX, monsterY);
		}

		for (GameObject* monster2 : monsters2) {
			monster2->Update(GetGameTime());

			monster2Velocity *= waveSpeedMultiplier;
			monster2X += (direction * monster2Velocity * GetGameTime());
			monster2->SetPosition(monster2X, monster2Y);
		}

		wave++;
		waveTimer = 0.0f;

	}

	// Update level 
	levelText->SetText("Level         : " + to_string(wave));

	// deteksi collision jika player terkena monster maka game over
	for (GameObject* monster : monsters) {
		monster->Update(GetGameTime());

		if (playerSprite->GetBoundingBox()->CollideWith(monster->GetBoundingBox())) {
			gameOver = true;
			soundGameOver->Play(false);
			finalScore = score;
			screenState = ScreenState::GAME_OVER;
			monster->SetIsDie();
			ResetGame();
			break;
		}
	}

	// deteksi collision jika player terkena monster2 maka game over
	for (GameObject* monster : monsters2) {
		monster->Update(GetGameTime());

		if (monster->IsDie()) {
			continue;
		}

		if (playerSprite->GetBoundingBox()->CollideWith(monster->GetBoundingBox())) {
			gameOver = true;
			soundGameOver->Play(false);
			finalScore = score;
			screenState = ScreenState::GAME_OVER;
			monster->SetIsDie();
			ResetGame();
			break;
		}
	}

	// Update level 
	levelText->SetText("Level         : " + to_string(wave));

	// Update highest score
	if (score > highestScore) {
		highestScore = score;
		highestScoreText->SetText("Highest Score : " + to_string(highestScore));
		SaveHighestScore();
	}
}

void DounatCatchers::ResetGame()
{
	playerSprite->SetPosition(startingPlayerX, startingPlayerY);

	for (GameObject* monster : monsters) {
		monsterX = setting->screenWidth;
		monsterY = 64;
		monster->SetPosition(monsterX, monsterY);
	}

	for (GameObject* monster2 : monsters2) {
		monster2X = setting->screenWidth;
		monster2Y = 64;
		monster2->SetPosition(monster2X, monster2Y);
	}

	for (GameObject* donat : donats) {
		int min = donat->GetWidth();
		int max = setting->screenWidth - donat->GetWidth() - 100;
		donatX = rand() % (max - min + 1) + min;
		donatY = 64 + donat->GetHeight();
		donat->SetPosition(donatX, donatY);
	}
	for (GameObject* choco : chocos) {
		int min = choco->GetWidth();
		int max = setting->screenWidth - choco->GetWidth() - 100;
		chocoX = rand() % (max - min + 1) + min;
		chocoY = 64 + choco->GetHeight();
		choco->SetPosition(chocoX, chocoY);
	}

	spawnMonsterDuration = 0;
	spawnMonster2Duration = 0;
	spawnDonatDuration = 0;
	spawnChocoDuration = 0;
	numMonstersInPool = 0;
	numMonsters2InPool = 0;
	numDonatsInPool = 1;
	numChocosInPool = 1;
	score = 0;
	wave = 0;
	waveTimer = 0;
	waveSpeedMultiplier = 0.0;
	monsterVelocity = 0.15;
	monster2Velocity = 0.175;
}

void DounatCatchers::LoadHighestScore()
{
	// baca nilai highest score dari file "highest_score.txt"
	ifstream file("highest_score.txt");
	if (file.good()) {
		file >> highestScore;
		file.close();
	}
}

void DounatCatchers::SaveHighestScore()
{
	// simpan nilai highest score ke dalam file "highest_score.txt"
	ofstream file("highest_score.txt");
	file << highestScore;
	file.close();
}

Sprite* DounatCatchers::CreateMonsterSprite(Texture* texture)
{
	Sprite* sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(6);
	sprite->SetNumYFrames(1);
	sprite->AddAnimation("walk", 0, 5);
	sprite->PlayAnim("walk");
	sprite->SetScale(2.3);
	sprite->SetAnimationDuration(200);

	sprite->SetBoundingBoxSize(sprite->GetScaleWidth() - (4 * sprite->GetScale()), sprite->GetScaleHeight() - (4 * sprite->GetScale()));

	return sprite;
}

Sprite* DounatCatchers::CreateMonster2Sprite(Texture* texture)
{
	Sprite* sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(6);
	sprite->SetNumYFrames(1);
	sprite->AddAnimation("walk", 0, 5);
	sprite->PlayAnim("walk");
	sprite->SetScale(2.3);
	sprite->SetAnimationDuration(200);

	sprite->SetBoundingBoxSize(sprite->GetScaleWidth() - (4 * sprite->GetScale()), sprite->GetScaleHeight() - (4 * sprite->GetScale()));

	return sprite;
}

Sprite* DounatCatchers::CreateDonatSprite(Texture* texture)
{
	Sprite* sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(2);
	sprite->SetNumYFrames(1);
	sprite->AddAnimation("idle", 0, 1);
	sprite->PlayAnim("idle");
	sprite->SetScale(1.0);
	sprite->SetAnimationDuration(400);

	sprite->SetBoundingBoxSize(sprite->GetScaleWidth() - (4 * sprite->GetScale()), sprite->GetScaleHeight() - (4 * sprite->GetScale()));

	return sprite;
}

Sprite* DounatCatchers::CreateChocoSprite(Texture* texture)
{
	Sprite* sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	sprite->SetNumXFrames(2);
	sprite->SetNumYFrames(1);
	sprite->AddAnimation("idle", 0, 1);
	sprite->PlayAnim("idle");
	sprite->SetScale(1.0);
	sprite->SetAnimationDuration(400);

	sprite->SetBoundingBoxSize(sprite->GetScaleWidth() - (4 * sprite->GetScale()), sprite->GetScaleHeight() - (4 * sprite->GetScale()));

	return sprite;
}

void DounatCatchers::SpawnMonsterObjects()
{
	//Find Die object to reuse for spawning
	int spawnCount = 0;
	for (GameObject* o : monsters) {
		if (spawnCount == numMonstersPerSpawn) {
			break;
		}
		if (o->IsDie()) {
			o->SetSpawn();
			monsterX = setting->screenWidth;
			monsterY = 64;
			o->SetPosition(monsterX, monsterY);

			soundMonster->Play(false);
			spawnCount++;
		}
	}
}

void DounatCatchers::SpawnMonster2Objects()
{
	//Find Die object to reuse for spawning
	int spawnCount = 0;
	for (GameObject* o : monsters2) {
		if (spawnCount == numMonsters2PerSpawn) {
			break;
		}
		if (o->IsDie()) {
			o->SetSpawn();
			monster2X = setting->screenWidth;
			monster2Y = 64;
			o->SetPosition(monster2X, monster2Y);

			soundMonster->Play(false);
			spawnCount++;
		}
	}
}

void DounatCatchers::SpawnDonatObjects()
{
	int spawnCount = 0;
	for (GameObject* donat : donats) {
		if (spawnCount == numMonstersPerSpawn) {
			break;
		}
		if (donat->IsDie()) {
			donat->SetSpawn();

			int min = donat->GetWidth();
			int max = setting->screenWidth - donat->GetWidth() - 100;
			donatX = rand() % (max - min + 1) + min;
			donatY = 64 + donat->GetHeight();
			donat->SetPosition(donatX, donatY);

			spawnCount++;
		}
	}
}

void DounatCatchers::SpawnChocoObjects()
{
	int spawnCount = 0;

	for (GameObject* choco : chocos) {
		if (spawnCount == numMonstersPerSpawn) {
			break;
		}
		if (choco->IsDie()) {
			choco->SetSpawn();

			int min = choco->GetWidth();
			int max = setting->screenWidth - choco->GetWidth() - 100;
			chocoX = rand() % (max - min + 1) + min;
			chocoY = 64 + choco->GetHeight();
			choco->SetPosition(chocoX, chocoY);

			spawnCount++;
		}
	}
}

int main(int argc, char** argv) {
	Engine::Setting* setting = new Engine::Setting();
	setting->windowTitle = "Dounat Catchers";
	setting->screenWidth = 1280;
	setting->screenHeight = 720;
	setting->windowFlag = Engine::WindowFlag::WINDOWED;
	setting->vsync = false;
	setting->targetFrameRate = 60;
	Engine::Game* game = new Engine::DounatCatchers(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}