#include "PlayerController.h"
#include "raymath.h" // for vectors
#include <cmath> // for simple math

PlayerController::PlayerController(Character* characterInput)
{
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
		(int)(mousePosition.x - cursorRadius),
		(int)(mousePosition.y - (cursorDepth / 2)),
		(int)cursorSize,
		(int)cursorDepth,
		WHITE
	);
	DrawRectangle(
		(int)(mousePosition.x - (cursorDepth / 2)),
		(int)(mousePosition.y - cursorRadius),
		(int)cursorDepth,
		(int)cursorSize,
		WHITE
	);

	if (character) {

		// Draw character

		character->Draw();

		// Linetrace

		DrawLineV(character->GetPosition(), mousePosition, Fade(WHITE, 0.1f));

		// Movimiento

		character->Move(movement);

		// Attack aiming and radius

		Vector2 vDifference = Vector2{ mousePosition.x - character->GetPosition().x, mousePosition.y - character->GetPosition().y };
		float hipotenuse = (float)sqrt(pow(vDifference.x, 2) + pow(vDifference.y, 2));
		Vector2 normalizedAiming = Vector2{ vDifference.x / hipotenuse, vDifference.y / hipotenuse };
		Vector2 scaledVector = Vector2Scale(normalizedAiming, character->GetAttackDistance());
		Vector2 endVector = Vector2Add(character->GetPosition(), scaledVector);

		DrawLineV(character->GetPosition(), endVector, RED);

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

		// Interactuar

		if (IsKeyDown(KEY_SPACE) && !character->GetIsInteracting()) {
			character->SetIsInteracting(true);
		}
		else {
			character->SetIsInteracting(false);
		}

	}


}
