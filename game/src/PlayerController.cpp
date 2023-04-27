#include "PlayerController.h"
#include <string>

PlayerController::PlayerController(Character* characterInput, HUD* hudInput)
{
	character = characterInput;
	hud = hudInput;
}

void PlayerController::Play()
{

	// DrawText(TextFormat("Character x: %f", character->GetPosition().x), 300, 300, 40, GREEN);
	// DrawText(TextFormat("Move x: %f", movement.x), 300, 350, 40, GREEN);

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

	if (checkingSlots) CheckSlots();

	if (character) {

		// HUD

		hud->Draw(typeHUD);

		if (typeHUD == H_GAME) {

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


			// Draw character

			if (character->GetIsAlive()) character->Draw();
			else typeHUD = H_LOOSE_GAME;

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

			if (IsKeyPressed(KEY_SPACE)) character->SetIsInteracting(true);
			else character->SetIsInteracting(false);

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
				switch (itemSelected)
				{
				case I_POTION_HEALTH:

					character->AddHealth(10.f);
					character->RemoveFromInventory(numPressed);

					break;

				case I_POTION_STRENGTH:

					character->IncreaseAttack();
					character->RemoveFromInventory(numPressed);

					break;

				case I_POTION_SPEED:

					if (!character->GetIsTempVelocityIncreased()) {
						character->IncreaseTempVelocity();
						character->RemoveFromInventory(numPressed);
					}
					break;

				case I_EXPERIENCE:

					character->IncreaseExperience();
					character->RemoveFromInventory(numPressed);

					break;

				case I_KEY:
					break;

				default:
					break;
				}

			}

		}

		else if (typeHUD == H_PAUSE) {

			if (hud->ButtonPressed() == 1) typeHUD = H_GAME;
			else if (hud->ButtonPressed() == 2) typeHUD = H_LOAD_DATA;
			else if (hud->ButtonPressed() == 3) typeHUD = H_HABILITIES;
			else if (hud->ButtonPressed() == 4) typeHUD = H_MAIN_MENU;

			hud->RestartMainMenuButtons();

		}

		else if (typeHUD == H_HABILITIES || typeHUD == H_INIT_HABILITIES) {

			if (hud->ButtonPressed()) {

				if (hud->ButtonPressed() == GO_BACK) {

					if (typeHUD == H_INIT_HABILITIES) typeHUD = H_MAIN_MENU;
					else typeHUD = H_PAUSE;

				}

				if (hud->ButtonPressed() == GO_FORWARD) {
					if (typeHUD == H_INIT_HABILITIES) typeHUD = H_GAME;
				}

				if (
					character->IsAddAbility(hud->ButtonPressed()) &&
					character->GetAbPoints() > 0
					) {

					character->IncreaseAbility((E_AbilityType)hud->ButtonPressed());
					character->SubstractAbPoints(1);

				}
				else if (character->IsSubstractAbility(hud->ButtonPressed())) {

					character->DecreaseAbility((E_AbilityType)hud->ButtonPressed());
					character->AddAbPoints(1);

				}

				hud->RestartMainMenuButtons();

			}

		}

		else if (typeHUD == H_MAIN_MENU) {

			if (hud->ButtonPressed()) {

				if (hud->ButtonPressed() == 1) typeHUD = H_INIT_HABILITIES;
				else if (hud->ButtonPressed() == 2) typeHUD = H_INIT_LOAD_DATA;
				else if (hud->ButtonPressed() == 3) CloseWindow();

				hud->RestartMainMenuButtons();

			}

		}

		else if (typeHUD == H_LOAD_DATA || typeHUD == H_INIT_LOAD_DATA) {

			if (hud->ButtonPressed()) {

				if (hud->GetInConfirmingModal()) {

					if (hud->IsDeletingSlot()) {

						DeleteSlotGame((E_GameSlot)hud->ButtonPressed() * -1);
						hud->Notify("Slot eliminado correctamente");
						hud->CloseConfirmModal();

					}
					else if (hud->ButtonPressed() == GO_BACK) {

						hud->CloseConfirmModal();

					}

				}
				else {

					if (hud->ButtonPressed() == GO_BACK) {

						if (typeHUD == H_INIT_LOAD_DATA) typeHUD = H_MAIN_MENU;
						else typeHUD = H_PAUSE;

					}

					if (hud->IsSelectingSlot()) {

						LoadGame(hud->ButtonPressed());

					}

					else if (hud->IsDeletingSlot()) {

						hud->OpenConfirmModal(
							hud->ButtonPressed(),
							"Estas seguro que quieres eliminar el slot ?"
						);

					}

				}

				hud->RestartMainMenuButtons();

			}
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

SlotData PlayerController::GetSlotsMaster() {

	// Fichero maestro que nos dice que slots hay
	char* slotsData = LoadFileText("resources/savings/slots.txt");
	char* delimiter = ",";
	int* count = new int[0];

	// Slot pointers es un array tal que ["1","2","3","4"]
	const char** slotPointers = TextSplit(slotsData, *delimiter, count);

	return SlotData{ slotPointers , *count };
}

void PlayerController::CheckSlots()
{
	SlotData sSlot = GetSlotsMaster();

	// Seteamos todo a falso
	slots = new bool[4] { false, false, false, false };

	if (sSlot.count > 0) {

		// Recorremos de 0 a 3
		for (int i = 0; i < slotsQuantity; i++) {

			if (sSlot.slotPointers[i]) { // Si existe el index en el array de textos "slotPointers"

				int existingSlotNumber = std::stoi(sSlot.slotPointers[i]) - 1; // Convertimos el texto en numero y le restamos 1 de indice
				slots[existingSlotNumber] = true; // Setea el elemento del array de boleanos a true basando en el indice que me haya tocado

			}

		}

	}

	checkingSlots = false;
	hud->SetSlots(slots);
	hud->SetSlotsQuantity(slotsQuantity);

}

bool* PlayerController::GetSlotsAvailable()
{
	return slots;
}

int PlayerController::GetSlotsQuantity()
{
	return slotsQuantity;
}

bool PlayerController::IsSlotAvailable(int slot)
{
	if (slot >= 1 && slot <= 4) return slots[slot - 1];
	return false;
}

void PlayerController::RestartCheckSlots()
{
	checkingSlots = true;
}

void PlayerController::SaveGame(int slot)
{

}

void PlayerController::LoadGame(int slot)
{
	// DrawText(TextFormat("resources/savings/slot%d.txt", slot), 400, 400, 40, WHITE);

	char* fileText = LoadFileText(TextFormat("resources/savings/slot%d.txt", slot));

	const char* delimiter = "\n";
	int* count = new int[0];

	const char** resultsPointers = TextSplit(fileText, *delimiter, count);

	std::string str1 = resultsPointers[0];

	// SI FUNCIONA! 
	// DrawText(str1.c_str(), 400, 500, 40, WHITE);

}

void PlayerController::DeleteSlotGame(int slot)
{
	if (slot > 0 && slot <= slotsQuantity) {

		SlotData sSlot = GetSlotsMaster();

		// Setea la nueva longitud de texto a guardar
		int newLength = sSlot.count - 1;

		if (newLength > 0) {

			char* dataToSave = new char[(newLength * 2) - 1]; // * 2 - 1 --> para las comas
			int indexToSave = 0;
			static bool savedTheFirstData = false;

			for (int i = 0; i < newLength; i++) {

				if (std::stoi(sSlot.slotPointers[i]) == slot) indexToSave++;

				if (sSlot.slotPointers[indexToSave]) {

					// Movida con strcpy para convertir:  const char*  --->  char *
					std::string str1 = sSlot.slotPointers[indexToSave];
					char* record = new char[1];
					strcpy(record, str1.c_str());

					if (!savedTheFirstData) {
						dataToSave = strcat(record, "");
						savedTheFirstData = true;
					}
					else dataToSave = strcat(dataToSave, record);


					// Si NO es el ultimo, ponle una coma despu�s
					if (i != newLength - 1) dataToSave = strcat(dataToSave, ",");

					indexToSave++;
				}

			}

			savedTheFirstData = false;

			SaveFileText("resources/savings/slots.txt", dataToSave);

		}
		else SaveFileText("resources/savings/slots.txt", "");

		slots[slot - 1] = false;

		// RestartCheckSlots();

	}

}