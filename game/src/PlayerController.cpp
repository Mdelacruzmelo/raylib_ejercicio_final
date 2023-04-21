#include "PlayerController.h";
#include "raymath.h" // for vectors
#include <cmath> // for simple math

PlayerController::PlayerController()
{

}

void PlayerController::SetPawn(Character* characterInput) {
	character = characterInput;
}

void PlayerController::Play()
{
	// Movimiento

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

	// Mouse cursor

	mousePosition = GetMousePosition();

	DrawRectangle(
		mousePosition.x - cursorRadius,
		mousePosition.y - (cursorDepth / 2),
		cursorSize,
		cursorDepth,
		WHITE
	);
	DrawRectangle(
		mousePosition.x - (cursorDepth / 2),
		mousePosition.y - cursorRadius,
		cursorDepth,
		cursorSize,
		WHITE
	);

	if (character) {

		// Draw character

		character->Draw();

		// Linetrace

		DrawLineV(character->pos, mousePosition, Fade(WHITE, 0.1f));

		// Movimiento

		character->Move(movement);

		// Attack aiming and radius

		Vector2 vDifference = Vector2{ mousePosition.x - character->pos.x, mousePosition.y - character->pos.y };
		float hipotenuse = sqrt(pow(vDifference.x, 2) + pow(vDifference.y, 2));
		Vector2 normalizedAiming = Vector2{ vDifference.x / hipotenuse, vDifference.y / hipotenuse };
		Vector2 scaledVector = Vector2Scale(normalizedAiming, character->attackDistance);
		Vector2 endVector = Vector2Add(character->pos, scaledVector);

		DrawLineV(character->pos, endVector, RED);

		// Atacar

		if (IsMouseButtonPressed(0)) character->Attack(endVector);

		// HUD

		float vectorLength = Vector2Length(vDifference);
		DrawText(
			TextFormat("Vector length: %f", vectorLength),
			950,
			40,
			24,
			WHITE);

	}


}
