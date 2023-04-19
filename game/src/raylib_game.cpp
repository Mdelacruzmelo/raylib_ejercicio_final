#include "raylib.h"

Font font = { 0 };
Music music = { 0 };
Sound fxCoin = { 0 };

static const int screenWidth = 1200;
static const int screenHeight = 1080;

static void UpdateDrawFrame(void);

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

	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		UpdateDrawFrame();
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;
}

static void UpdateDrawFrame(void)
{
	UpdateMusicStream(music);
	BeginDrawing();
	ClearBackground(BLACK);



	EndDrawing();
}
