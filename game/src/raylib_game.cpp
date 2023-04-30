#include "raylib.h"
#include "Character.h"
#include "PlayerController.h"
#include "EnvironmentHandler.h"
#include "Environment.h"
#include "HUD.h"
#include "Enemy.h"
#include "AIController.h"

Font font = { 0 };
Music mainMenuTheme = { 0 };
Music gameTheme = { 0 };

static const int screenWidth = 1200;
static const int screenHeight = 1080;

int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "raylib game template");
	InitAudioDevice();

	font = LoadFont("resources/mecha.png");
	mainMenuTheme = LoadMusicStream("resources/sounds/mainMenuTheme.ogg");
	gameTheme = LoadMusicStream("resources/sounds/gameTheme.ogg");

	SetMusicVolume(gameTheme, 0.3f);


	SetMusicVolume(mainMenuTheme, 0.1f);
	PlayMusicStream(mainMenuTheme);
	SetTargetFPS(60);
	SetMouseCursor(1);

	Character* character = new Character();
	HUD* hud = new HUD(character);
	AIController* aiController = new AIController(character);
	PlayerController* controller = new PlayerController(character, hud, aiController);
	EnvironmentHandler* envHandler = new EnvironmentHandler(character, aiController);

	envHandler->SetAIController(aiController);
	envHandler->InitializeMap();

	while (!WindowShouldClose())
	{

		BeginDrawing();
		ClearBackground(BLACK);

		if (controller->GetTypeHUD() == H_GAME) {

			envHandler->Draw();
			aiController->Play();

		}

		if (controller->GetTypeHUD() == H_GAME || controller->GetTypeHUD() == H_PAUSE) {

			PlayMusicStream(gameTheme);
			UpdateMusicStream(gameTheme);
			StopMusicStream(mainMenuTheme);

			if (controller->GetTypeHUD() == H_PAUSE) SetMusicVolume(gameTheme, 0.1f);

		}
		else {
			UpdateMusicStream(mainMenuTheme);
			StopMusicStream(gameTheme);
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
