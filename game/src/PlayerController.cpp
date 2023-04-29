#include "PlayerController.h"
#include <string>

PlayerController::PlayerController(Character* characterInput, HUD* hudInput)
{
	character = characterInput;
	hud = hudInput;
}

void PlayerController::Play()
{

	if (IsKeyPressed(KEY_E)) SetTypeHUD(H_PAUSE);

	if (checkingSlots) CheckSlots();

	if (character) {

		// HUD

		hud->Draw(typeHUD);

		// Attack aiming and radius

		Vector2 vDifference = Vector2{ mousePosition.x - character->GetPosition().x, mousePosition.y - character->GetPosition().y };
		float hipotenuse = (float)sqrt(pow(vDifference.x, 2) + pow(vDifference.y, 2));
		Vector2 normalizedAiming = Vector2{ vDifference.x / hipotenuse, vDifference.y / hipotenuse };
		Vector2 scaledVector = Vector2Scale(normalizedAiming, (character->GetAttackDistance() * 20));
		Vector2 endVector = Vector2Add(character->GetPosition(), scaledVector);

		switch (typeHUD)
		{
		case H_GAME:

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

			break;

		case H_PAUSE:

			if (hud->ButtonPressed() == RESUME) typeHUD = H_GAME;
			else if (hud->ButtonPressed() == HABILITIES) typeHUD = H_HABILITIES;
			else if (hud->ButtonPressed() == SAVE) typeHUD = H_SAVE_DATA;
			else if (hud->ButtonPressed() == LOAD) typeHUD = H_LOAD_DATA;
			else if (hud->ButtonPressed() == QUIT) typeHUD = H_MAIN_MENU;

			hud->RestartMainMenuButtons();

			break;

		case H_HABILITIES:
		case H_INIT_HABILITIES:

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
			break;

		case H_LOAD_DATA:
		case H_INIT_LOAD_DATA:

			if (hud->ButtonPressed()) {

				if (hud->GetInConfirmingModal()) {

					if (hud->IsDeletingSlot()) {

						DeleteSlotGame((E_GameSlot)hud->ButtonPressed() * -1);
						hud->Notify("Slot eliminado correctamente");
						hud->CloseConfirmModal();

					}
					else if (hud->ButtonPressed() == GO_BACK) hud->CloseConfirmModal();

				}
				else {

					if (hud->ButtonPressed() == GO_BACK) {

						if (typeHUD == H_INIT_LOAD_DATA) typeHUD = H_MAIN_MENU;
						else typeHUD = H_PAUSE;

					}

					if (hud->IsSelectingSlot()) {

						if (LoadGame(hud->ButtonPressed())) {

							if (typeHUD == H_INIT_LOAD_DATA) typeHUD = H_INIT_HABILITIES;
							else typeHUD = H_PAUSE;

						}
						else hud->Notify("Error en la carga de datos");

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

			break;

		case H_SAVE_DATA:

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
					else if (IsSlotOverwrite(hud->ButtonPressed())) {

						SaveGame(hud->ButtonPressed());
						// SaveSlotGame(hud->ButtonPressed());
						checkingSlots = true;
						hud->Notify("Partida guardada");
						hud->CloseConfirmModal();

						typeHUD = H_PAUSE;

					}

				}
				else {

					if (hud->ButtonPressed() == GO_BACK) {

						if (typeHUD == H_INIT_LOAD_DATA) typeHUD = H_MAIN_MENU;
						else typeHUD = H_PAUSE;

					}

					if (hud->IsSelectingSlot()) {

						if (IsSlotOverwrite(hud->ButtonPressed())) {

							hud->OpenConfirmModal(
								hud->ButtonPressed(),
								"Estas seguro que quieres sobreescribir el slot ?"
							);

						}
						else {

							SaveGame(hud->ButtonPressed());
							SaveSlotGame(hud->ButtonPressed());
							checkingSlots = true;
							hud->Notify("Partida guardada");

							typeHUD = H_PAUSE;

						}

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

			break;

		case H_MAIN_MENU:

			character->SetInitialData();
			character->SetIsInNewGame(true); // Escuchado por EnvironmentHandler

			if (hud->ButtonPressed()) {

				if (hud->ButtonPressed() == NEW) typeHUD = H_INIT_HABILITIES;
				else if (hud->ButtonPressed() == LOAD) typeHUD = H_INIT_LOAD_DATA;
				else if (hud->ButtonPressed() == QUIT) CloseWindow();

				hud->RestartMainMenuButtons();

			}

			break;

		case H_LOOSE_GAME:
			break;

		case H_WIN_GAME:
			break;

		default:
			break;
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
	slots = new bool[slotsQuantity] { false, false, false, false };

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

bool PlayerController::IsSlotOverwrite(int slot) {

	if (slot > 0 && slot <= slotsQuantity) return slots[slot - 1];

	return false;

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
	SavedData data = SavedData{};

	data.attack = character->GetAttack();
	data.defense = character->GetDefense();
	data.speed = character->GetSpeed();
	data.energy = character->GetEnergy();
	data.attackdistance = character->GetAttackDistance();
	data.health = character->GetHealth();
	data.shield = character->GetShield();
	data.experience = character->GetExperience();
	data.level = character->GetLevel();
	data.inventory1 = character->GetInventory()[0];
	data.inventory2 = character->GetInventory()[1];
	data.inventory3 = character->GetInventory()[2];
	data.inventory4 = character->GetInventory()[3];
	data.inventory5 = character->GetInventory()[4];
	data.environment = character->GetEnvironment();
	data.doorsData = character->GetLoadedDoorsData();
	data.locationx = character->GetPosition().x;
	data.locationy = character->GetPosition().y;
	data.abPoints = character->GetAbPoints();

	SetSlotWithSavedData(slot, data);

}

void PlayerController::SetSlotWithSavedData(int slot, SavedData data)
{

	std::string result =
		std::string(Converter::FloatToChar(data.attack)) + std::string("\n") +
		std::string(Converter::FloatToChar(data.defense)) + std::string("\n") +
		std::string(Converter::FloatToChar(data.speed)) + std::string("\n") +
		std::string(Converter::FloatToChar(data.energy)) + std::string("\n") +
		std::string(Converter::FloatToChar(data.attackdistance)) + std::string("\n") +
		std::string(Converter::FloatToChar(data.health)) + std::string("\n") +
		std::string(Converter::FloatToChar(data.shield)) + std::string("\n") +
		std::string(Converter::IntToChar(data.experience)) + std::string("\n") +
		std::string(Converter::IntToChar(data.level)) + std::string("\n") +
		std::string(Converter::IntToChar(data.inventory1)) + std::string("\n") +
		std::string(Converter::IntToChar(data.inventory2)) + std::string("\n") +
		std::string(Converter::IntToChar(data.inventory3)) + std::string("\n") +
		std::string(Converter::IntToChar(data.inventory4)) + std::string("\n") +
		std::string(Converter::IntToChar(data.inventory5)) + std::string("\n") +
		std::string(Converter::IntToChar(data.environment)) + std::string("\n") +
		std::string(data.doorsData) + std::string("\n") +
		std::string(Converter::FloatToChar(data.locationy)) + std::string("\n") +
		std::string(Converter::FloatToChar(data.locationy)) + std::string("\n") +
		std::string(Converter::IntToChar(data.abPoints));

	char* resultChar = new char[strlen(result.c_str()) + 1];
	strcpy(resultChar, result.c_str());

	SaveFileText(TextFormat("resources/savings/slot%d.txt", slot), resultChar);

}

SavedData PlayerController::GetSlotSavedData(int slot)
{

	char* fileText = LoadFileText(TextFormat("resources/savings/slot%d.txt", slot));

	const char* delimiter = "\n";
	int* count = new int[0];

	const char** resultsPointers = TextSplit(fileText, *delimiter, count);
	SavedData data = SavedData{};

	if (*count == 19) {

		data.attack = std::stof(std::string(resultsPointers[SAVED_ATTACK]));
		data.defense = std::stof(std::string(resultsPointers[SAVED_DEFENSE]));
		data.speed = std::stof(std::string(resultsPointers[SAVED_SPEED]));
		data.energy = std::stof(std::string(resultsPointers[SAVED_ENERGY]));
		data.attackdistance = std::stof(std::string(resultsPointers[SAVED_ATTACK_DISTANCE]));
		data.health = std::stof(std::string(resultsPointers[SAVED_HEALTH]));
		data.shield = std::stof(std::string(resultsPointers[SAVED_SHIELD]));
		data.experience = std::stof(std::string(resultsPointers[SAVED_EXPERIENCE]));
		data.level = std::stoi(std::string(resultsPointers[SAVED_LEVEL]));
		data.inventory1 = std::stoi(std::string(resultsPointers[SAVED_INVENTORY_1]));
		data.inventory2 = std::stoi(std::string(resultsPointers[SAVED_INVENTORY_2]));
		data.inventory3 = std::stoi(std::string(resultsPointers[SAVED_INVENTORY_3]));
		data.inventory4 = std::stoi(std::string(resultsPointers[SAVED_INVENTORY_4]));
		data.inventory5 = std::stoi(std::string(resultsPointers[SAVED_INVENTORY_5]));
		data.environment = std::stoi(std::string(resultsPointers[SAVED_ENVIRONMENT]));
		data.locationx = std::stof(std::string(resultsPointers[SAVED_LOCATION_X]));
		data.locationy = std::stof(std::string(resultsPointers[SAVED_LOCATION_Y]));
		data.abPoints = std::stof(std::string(resultsPointers[SAVED_AB_POINTS]));

		// Doors data

		std::string doorsCharPointer = resultsPointers[SAVED_DOORS_DATA];
		char* doorsChar = new char[doorsCharPointer.length()];
		strcpy(doorsChar, doorsCharPointer.c_str());

		data.doorsData = doorsChar;

	}

	return data;
}

bool PlayerController::LoadGame(int slot)
{
	SavedData data = GetSlotSavedData(slot);

	if (data.health) {
		character->SetData(data);
		return true;
	}

	return false;
}

void PlayerController::DeleteSlotGame(int slot)
{
	if (slot > 0 && slot <= slotsQuantity) {

		SlotData sSlot = GetSlotsMaster();

		// Setea la nueva longitud de texto a guardar
		int newLength = sSlot.count - 1;

		// Si al cargarte 1, almenos quedan slots, procesalos
		if (newLength > 0) {

			char* dataToSave = new char[(newLength * 2) - 1]; // * 2 - 1 --> para las comas

			int indexToSave = 0;
			static bool savedTheFirstData = false;

			for (int i = 0; i < newLength; i++) {

				// Si es justo el que estás borrando, dale con el siguiente
				if (std::stoi(sSlot.slotPointers[i]) == slot) indexToSave++;

				// Si el numero existe en el documento
				if (sSlot.slotPointers[indexToSave]) {

					// Movida con strcpy para convertir:  const char*  --->  char *
					std::string str1 = sSlot.slotPointers[indexToSave];
					char* record = new char[1];
					strcpy(record, str1.c_str());

					// Solo la primera vez me interesa setear bien el srtcat()
					if (!savedTheFirstData) {
						dataToSave = strcat(record, "");
						savedTheFirstData = true;
					}
					else dataToSave = strcat(dataToSave, record);

					// Si NO es el ultimo, ponle una coma después
					if (i != newLength - 1) dataToSave = strcat(dataToSave, ",");

					indexToSave++;
				}

			}

			savedTheFirstData = false;

			SaveFileText("resources/savings/slots.txt", dataToSave);

		}
		// si no, setea el documento a vacío
		else SaveFileText("resources/savings/slots.txt", "");

		slots[slot - 1] = false;

		// RestartCheckSlots();

	}

}

void PlayerController::SaveSlotGame(int slot)
{
	if (slot > 0 && slot <= slotsQuantity) {

		SlotData sSlot = GetSlotsMaster();

		if (sSlot.count > 0) {

			int newLength = sSlot.count + 2; // + el numero y la coma
			char* dataToSave = new char[newLength];

			char* slotsData = LoadFileText("resources/savings/slots.txt");

			std::string result = std::string(slotsData) + std::string(",") + std::string(Converter::IntToChar(slot));
			char* charResult = new char[strlen(result.c_str()) + 1];
			strcpy(charResult, result.c_str());

			SaveFileText("resources/savings/slots.txt", charResult);

		}
		else {

			SaveFileText("resources/savings/slots.txt", Converter::IntToChar(slot));

		}

		slots[slot - 1] = true;

		// RestartCheckSlots();

	}

}