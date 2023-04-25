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

		if (IsKeyDown(KEY_A)) {

			if (character->GetPosition().x > (character->GetSize().x / 2)) movement.x = -1.f;
			else movement.x = 0.f;

		}

		if (IsKeyDown(KEY_D)) {

			if (character->GetPosition().x < (GetScreenWidth() - character->GetSize().x / 2)) movement.x = 1.f;
			else movement.x = 0.f;

		}
	}
	else movement.x = 0;

	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S)) {

		if (IsKeyDown(KEY_W)) {

			if (character->GetPosition().y - (character->GetSize().y / 2) > 0.f) movement.y = -1.f;
			else movement.y = 0.f;

		}
		if (IsKeyDown(KEY_S)) {

			// Border bottom = 80.f

			if (character->GetPosition().y < (GetScreenHeight() - 80.f)) movement.y = 1.f;
			else movement.y = 0.f;

		}
	}
	else movement.y = 0;

	DrawText(TextFormat("Character x: %f", character->GetPosition().x), 300, 300, 40, GREEN);
	DrawText(TextFormat("Move x: %f", movement.x), 300, 350, 40, GREEN);

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

		if (character->GetIsAlive()) character->Draw();
		else typeHUD = H_LOOSE_GAME;

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
			Vector2 scaledVector = Vector2Scale(normalizedAiming, (character->GetAttackDistance() * 20));
			Vector2 endVector = Vector2Add(character->GetPosition(), scaledVector);

			DrawLineV(character->GetPosition(), endVector, RED);

			// Movimiento

			character->Move(movement);

			// Atacar

			if (IsMouseButtonPressed(0)) character->Attack(endVector);
			else character->ReinitializeAttackCircles();

			// Interactuar

			/*if (character->GetIsInteracting())
				DrawText("INTERACTING", 300, 800, 40, WHITE);
			else
				DrawText("NOT INTERACTING", 300, 800, 40, WHITE);*/


			if (IsKeyPressed(KEY_SPACE)) {
				character->SetIsInteracting(true);
			}
			else {
				character->SetIsInteracting(false);
			}

			// Inventario
			if (
				IsKeyPressed(KEY_ONE) ||
				IsKeyPressed(KEY_TWO) ||
				IsKeyPressed(KEY_THREE) ||
				IsKeyPressed(KEY_FOUR) ||
				IsKeyPressed(KEY_FIVE)
				) {

				int numPressed = 0;

				if (IsKeyPressed(KEY_ONE)) numPressed = 1;
				if (IsKeyPressed(KEY_TWO)) numPressed = 2;
				if (IsKeyPressed(KEY_THREE)) numPressed = 3;
				if (IsKeyPressed(KEY_FOUR)) numPressed = 4;
				if (IsKeyPressed(KEY_FIVE)) numPressed = 5;

				hud->ItemNumberPress(numPressed);
				E_ItemType itemSelected = (E_ItemType)character->GetInventory()[numPressed - 1];

				if (itemSelected == I_POTION_HEALTH) {
					character->AddHealth(10.f);
					character->RemoveFromInventory(numPressed);
				}
				else if (itemSelected == I_POTION_STRENGTH) {
					character->IncreaseAttack();
					character->RemoveFromInventory(numPressed);
				}
				else if (itemSelected == I_POTION_SPEED) {
					if (!character->GetIsTempVelocityIncreased()) {
						character->IncreaseTempVelocity();
						character->RemoveFromInventory(numPressed);
					}
				}
				else if (itemSelected == I_EXPERIENCE) {
					character->IncreaseExperience();
					character->RemoveFromInventory(numPressed);
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

		else if (typeHUD == H_HABILITIES || typeHUD == H_INIT_HABILITIES) {

			if (hud->GetHabilityButtonPressed() != 0) {

				if (hud->GetHabilityButtonPressed() == 10) {
					if (typeHUD == H_INIT_HABILITIES) typeHUD = H_MAIN_MENU;
					else typeHUD = H_PAUSE;
				}

				if (hud->GetHabilityButtonPressed() == 11) {
					if (typeHUD == H_INIT_HABILITIES) typeHUD = H_GAME;
				}

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

		else if (typeHUD == H_MAIN_MENU) {

			if (hud->GetMainMenuButtonPressed() == 1) typeHUD = H_INIT_HABILITIES;
			else if (hud->GetMainMenuButtonPressed() == 2) typeHUD = H_LOAD_DATA;
			else if (hud->GetMainMenuButtonPressed() == 3) CloseWindow();

			hud->RestartMainMenuButtons();

		}
	}
}

void PlayerController::SetTypeHUD(E_TypeHUD typeHUDInput)
{
	typeHUD = typeHUDInput;
}

E_TypeHUD PlayerController::GetTypeHUD()
{
	return typeHUD;
}
