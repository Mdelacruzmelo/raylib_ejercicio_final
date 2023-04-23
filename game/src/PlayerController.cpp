#include "PlayerController.h"
#include "raymath.h" // for vectors
#include <cmath> // for simple math
#include "InventoryItemsUtils.h"

PlayerController::PlayerController(Character* characterInput, HUD* hudInput)
{
	character = characterInput;
	hud = hudInput;
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
		hud->Draw();

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

		// Inventario
		if (
			IsKeyDown(KEY_ONE) ||
			IsKeyDown(KEY_TWO) ||
			IsKeyDown(KEY_THREE) ||
			IsKeyDown(KEY_FOUR) ||
			IsKeyDown(KEY_FIVE)
			) {

			int numPressed = 0;

			if (IsKeyDown(KEY_ONE)) numPressed = 1;
			if (IsKeyDown(KEY_TWO)) numPressed = 2;
			if (IsKeyDown(KEY_THREE)) numPressed = 3;
			if (IsKeyDown(KEY_FOUR)) numPressed = 4;
			if (IsKeyDown(KEY_FIVE)) numPressed = 5;

			hud->ItemNumberPress(numPressed);
			E_ItemType itemSelected = (E_ItemType)character->GetInventory()[numPressed - 1];

			if (itemSelected == I_POTION_HEALTH) {
				character->AddHealth(10.f);
			}
			else if (itemSelected == I_POTION_STRENGTH) {
				character->IncreaseStrength();
			}
			else if (itemSelected == I_POTION_SPEED) {
				character->IncreaseSpeed();
			}
			else if (itemSelected == I_EXPERIENCE) {
				character->IncreaseExperience();
			}
		}

		// -------------------- TEST INTERACT --------------------

		if (IsKeyPressed(KEY_Q)) {
			// character->AddHealth(10.f);
			// character->ApplyDamage(10.f);
			character->AddToInventory(I_POTION_SPEED);
		}
		if (IsKeyPressed(KEY_E)) {
			character->IncreaseExperience();
		}

	}


}
