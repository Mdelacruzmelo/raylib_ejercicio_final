#include "raylib.h"
#include "Character.h"
#include "PlayerController.h"
#include "EnvironmentHandler.h"
#include "Environment.h"
#include "HUD.h"

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
	EnvironmentHandler* envHandler = new EnvironmentHandler(character);

	// Environment 1

	Environment* env1 = new Environment(DARKGRAY);
	env1->Activate();
	env1->AddDoor(SIDE_RIGHT, "door_A");
	envHandler->Append(env1);

	// Environment 2

	Environment* env2 = new Environment(DARKPURPLE);
	env2->AddDoor(SIDE_LEFT, "door_B");
	env2->AddDoor(SIDE_BOTTOM, "door_C");
	envHandler->Append(env2);

	// Environment 3

	Environment* env3 = new Environment(BLACK);
	env3->AddDoor(SIDE_TOP, "door_D");
	envHandler->Append(env3);

	// Connections

	env1->GetDoor("door_A")->Target("door_B");
	env2->GetDoor("door_B")->Target("door_A");
	env3->GetDoor("door_D")->Target("door_C");
	env2->GetDoor("door_C")->Target("door_D");

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

