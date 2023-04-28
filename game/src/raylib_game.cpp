#include "raylib.h"
#include "Character.h"
#include "PlayerController.h"
#include "EnvironmentHandler.h"
#include "Environment.h"
#include "HUD.h"
#include "Enemy.h"
#include "AIController.h"

Font font = { 0 };
Music music = { 0 };
Sound fxCoin = { 0 };

static const int screenWidth = 1200;
static const int screenHeight = 1080;

int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "raylib game template");
	InitAudioDevice();

	font = LoadFont("resources/mecha.png");
	music = LoadMusicStream("resources/ambient.ogg");
	fxCoin = LoadSound("resources/coin.wav");

	SetMusicVolume(music, 1.0f);
	PlayMusicStream(music);
	SetTargetFPS(60);

	Character* character = new Character();
	HUD* hud = new HUD(character);
	PlayerController* controller = new PlayerController(character, hud);
	AIController* aiController = new AIController(character);
	EnvironmentHandler* envHandler = new EnvironmentHandler(character, aiController);

	envHandler->SetAIController(aiController);
	envHandler->InitializeMap();

	while (!WindowShouldClose())
	{
		// UpdateMusicStream(music);

		BeginDrawing();
		ClearBackground(BLACK);

		if (controller->GetTypeHUD() == H_GAME) {

			envHandler->Draw();
			aiController->Play();

		}

		if (character->GetIsLoadingData()) envHandler->LoadDataFromCharacter();
		if (character->GetIsInNewGame()) envHandler->Restart();

		controller->Play();
		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;
}

