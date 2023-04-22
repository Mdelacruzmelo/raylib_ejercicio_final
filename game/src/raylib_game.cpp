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
	SetTargetFPS(60);

	Character* character = new Character();
	PlayerController* controller = new PlayerController(character);
	EnvironmentHandler* envHandler = new EnvironmentHandler(character);

	// Environment 1

	Environment* env1 = new Environment(DARKGRAY);
	env1->Activate();
	env1->AddDoor(SIDE_RIGHT, "door_A");
	envHandler->Append(env1);

	// Environment 2

	Environment* env2 = new Environment(DARKPURPLE);
	env2->AddDoor(SIDE_LEFT, "door_B");
	envHandler->Append(env2);

	env1->GetDoor("door_A")->Target("door_B");

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

