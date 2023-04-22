#include "raylib.h"
#include "Character.h"
#include "PlayerController.h"
#include "EnvironmentHandler.h"
#include "Environment.h"

Font font = { 0 };
Music music = { 0 };
Sound fxCoin = { 0 };

static const int screenWidth = 1200;
static const int screenHeight = 1080;

int main(void)
{
	InitWindow(screenWidth, screenHeight, "raylib game template");
	InitAudioDevice();

	font = LoadFont("resources/mecha.png");
	music = LoadMusicStream("resources/ambient.ogg");
	fxCoin = LoadSound("resources/coin.wav");

	SetMusicVolume(music, 1.0f);
	PlayMusicStream(music);

	Character* character = new Character();

	PlayerController* controller = new PlayerController(character);

	EnvironmentHandler* envHandler = new EnvironmentHandler();

	Environment* env1 = new Environment(DARKGRAY);
	env1->Activate();
	env1->AddDoor(SIDE_LEFT);

	envHandler->Append(env1);

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		// UpdateMusicStream(music);

		BeginDrawing();

		ClearBackground(BLACK);

		envHandler->Draw();
		controller->Play();

		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;
}

