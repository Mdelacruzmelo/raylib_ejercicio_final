#include "PlayerController.h"
#include "raymath.h" // for vectors
#include <cmath> // for simple math
#include "InventoryItemsUtils.h"
#include "AbilityUtils.h"

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

	// -------------------- TEST INTERACT --------------------

	if (IsKeyPressed(KEY_Q)) {
		// character->AddHealth(10.f);
		// character->ApplyDamage(10.f);
		// character->AddToInventory(I_POTION_SPEED);
		SetTypeHUD(H_HABILITIES);
	}
	if (IsKeyPressed(KEY_E)) {
		// character->IncreaseExperience();
		SetTypeHUD(H_PAUSE);
	}
	if (IsKeyPressed(KEY_R)) {
		// character->IncreaseExperience();
		SetTypeHUD(H_GAME);
	}

	SetMouseCursor(1);

	if (character) {

		// Draw character

		character->Draw();

		// HUD

		hud->Draw(typeHUD);

		if (typeHUD == H_GAME) {

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

			// Linetrace

			DrawLineV(character->GetPosition(), mousePosition, Fade(WHITE, 0.1f));

			// Attack aiming and radius

			Vector2 vDifference = Vector2{ mousePosition.x - character->GetPosition().x, mousePosition.y - character->GetPosition().y };
			float hipotenuse = (float)sqrt(pow(vDifference.x, 2) + pow(vDifference.y, 2));
			Vector2 normalizedAiming = Vector2{ vDifference.x / hipotenuse, vDifference.y / hipotenuse };
			Vector2 scaledVector = Vector2Scale(normalizedAiming, (character->GetAttackDistance() * 10));
			Vector2 endVector = Vector2Add(character->GetPosition(), scaledVector);

			DrawLineV(character->GetPosition(), endVector, RED);

			// Movimiento

			character->Move(movement);

			// Atacar

			if (IsMouseButtonPressed(0)) character->Attack(endVector);

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
					character->IncreaseAttack();
				}
				else if (itemSelected == I_POTION_SPEED) {
					character->IncreaseVelocity();
				}
				else if (itemSelected == I_EXPERIENCE) {
					character->IncreaseExperience();
				}
			}

		}

		else if (typeHUD == H_PAUSE) {

			if (hud->GetPauseButtonPressed() == 1) typeHUD = H_GAME;
			else if (hud->GetPauseButtonPressed() == 2) typeHUD = H_LOAD_DATA;
			else if (hud->GetPauseButtonPressed() == 3) typeHUD = H_HABILITIES;
			else if (hud->GetPauseButtonPressed() == 4) typeHUD = H_MAIN_MENU;

			hud->RestartPauseButtons();

			/*float vectorLength = Vector2Length(vDifference);
			DrawText(
				TextFormat("Vector length: %f", vectorLength),
				950,
				40,
				24,
				WHITE);*/
		}

		else if (typeHUD == H_HABILITIES) {

			if (hud->GetHabilityButtonPressed() != 0) {

				if (hud->GetHabilityButtonPressed() == 10) typeHUD = H_PAUSE;

				if (
					character->IsAddAbility(hud->GetHabilityButtonPressed()) &&
					character->GetAbPoints() > 0
					) {
					character->IncreaseAbility((E_AbilityType)hud->GetHabilityButtonPressed());
					character->SubstractAbPoints(1);
				}
				else if (character->IsSubstractAbility(hud->GetHabilityButtonPressed())) {
					character->DecreaseAbility((E_AbilityType)hud->GetHabilityButtonPressed());
					character->AddAbPoints(1);
				}

				// else if (hud->GetHabilityButtonPressed() == 2) typeHUD = H_LOAD_DATA;

				hud->RestartHabilityButtons(); // back to 0

			}


		}
	}
}

void PlayerController::SetTypeHUD(E_TypeHUD typeHUDInput)
{
	typeHUD = typeHUDInput;
}
