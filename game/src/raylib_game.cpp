#include "raylib.h"
#include "raymath.h"

Font font = { 0 };
Music music = { 0 };
Sound fxCoin = { 0 };

// Pantalla

static const int screenWidth = 1200;
static const int screenHeight = 1080;

// Personaje

static const float velocity = 1.f;
static const float acceleration = 4.f;
static const float characterSize = 40.f;
static const float characterRadius = characterSize / 2;
Vector2 characterPosition = { 0.f, 0.f };

// Mouse

Vector2 mousePosition = { 0.f, 0.f };
static const float cursorSize = 50.f;
static const float cursorRadius = cursorSize / 2;
static const float cursorDepth = 5.f;

static void GameDrawing();

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

	while (!WindowShouldClose())
	{
		UpdateMusicStream(music);
		BeginDrawing();
		ClearBackground(BLACK);
		GameDrawing();
		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;
}

static void GameDrawing() {

	// Movimiento

	static Vector2 movement = { 0.f, 0.f };

	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
		if (IsKeyDown(KEY_A)) movement.x = -1.f;
		if (IsKeyDown(KEY_D)) movement.x = 1.f;
	}
	else movement.x = 0;


	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S)) {
		if (IsKeyDown(KEY_W)) movement.y = -1.f;
		if (IsKeyDown(KEY_S)) movement.y = 1.f;
	}
	else movement.y = 0;

	characterPosition = Vector2{
		characterPosition.x + (velocity * acceleration * movement.x),
		characterPosition.y + (velocity * acceleration * movement.y)
	};

	// Personaje

	DrawRectangle(
		characterPosition.x - characterRadius,
		characterPosition.y - characterRadius,
		characterSize,
		characterSize,
		WHITE
	);

	// Mouse

	Vector2 mousePosition = GetMousePosition();
	DrawRectangle(mousePosition.x - cursorRadius, mousePosition.y, cursorSize, cursorDepth, WHITE);
	DrawRectangle(mousePosition.x, mousePosition.y - cursorRadius, cursorDepth, cursorSize, WHITE);

	// Linetrace

	DrawLineV(characterPosition, mousePosition, WHITE);

}