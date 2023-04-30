#include "AIController.h"

AIController::AIController(Character* characterInput)
{
	character = characterInput;
	InitEnemies();
}


void AIController::InitEnemies()
{
	for (int i = 0; i < enemyTexturesLength; i++) {
		enemyTextures[i] = LoadTexture(TextFormat("resources/textures/parasite%d.png", i + 1));
	}

	for (int i = 0; i < enemyQuantity; i++) {

		enemies[i] = new Enemy();
		enemies[i]->SetTarget(character);

		int randomVal = GetRandomValue(0, 3);
		float posX = 100.f;
		float posY = -100.f;

		if (randomVal == 1) {
			posX = GetScreenWidth();
		}
		else if (randomVal == 2) {
			posY = GetScreenHeight();
		}
		else if (randomVal == 3) {
			posX = GetScreenWidth();
			posY = GetScreenHeight();
		}

		enemies[i]->SetPosition(Vector2{ posX, posY });
		enemies[i]->SetTextures(enemyTextures);
		enemies[i]->SetTexturesLength(enemyTexturesLength);

	}
}


void AIController::SpawnEnemies()
{
	dificultyCounter += 1;

	// Si el personaje tiene menos de la mitad de vida
	if (character->GetNormalizedHealth() < 0.3f) newDificulty = 0;

	if (dificultyCounter >= 300) {

		newDificulty += 1;
		dificultyCounter = 0;

	}

	if (
		dificulty != newDificulty &&
		enemyQuantitySpawned < enemyQuantity
		) {


		if (dificulty == 0) enemyQuantitySpawned = 1;
		else enemyQuantitySpawned += 1;
		dificulty = newDificulty;

	}

	for (int i = 0; i < enemyQuantitySpawned; i++) {

		enemies[i]->Play();

	}
}

void AIController::DeleteEnemies()
{
	for (int i = 0; i < enemyQuantity; i++) {
		enemies[i]->Restart();
	}
	enemyQuantitySpawned = 0;
}

void AIController::SpawnConsumable(E_ItemType typeInput)
{
	if (character != nullptr) {

		int newQuantity = consumableQuantity + 1;
		Consumable* newConsumables = new Consumable[newQuantity];

		for (int i = 0; i < newQuantity; i++) {

			if (i < consumableQuantity) newConsumables[i] = consumables[i];
			else {

				// Si el jugador esta en la mitad izquierda de la pantalla, ponlo en la derecha y viceversa

				float spawmLocX = character->GetPosition().x;
				if (spawmLocX < GetScreenWidth() / 2) spawmLocX = GetScreenWidth() / 2 + GetRandomValue(10, 50) - GetScreenWidth() / 4;
				else spawmLocX = GetScreenWidth() / 4 - GetRandomValue(10, 50);

				// Si el jugador esta en la mitad superior de la pantalla, ponlo en la inferior y viceversa

				float spawmLocY = character->GetPosition().y;
				if (spawmLocY < GetScreenHeight() / 2) spawmLocY = GetScreenHeight() / 2 + GetRandomValue(10, 50) + GetScreenHeight() / 4;
				else spawmLocY = GetScreenHeight() / 4 - GetRandomValue(10, 50);

				newConsumables[i] = Consumable(
					typeInput,
					character,
					Vector2{ spawmLocX, spawmLocY }
				);

			}
		}

		consumables = newConsumables;
		consumableQuantity = newQuantity;

	}

}

void AIController::SpawnConsumables()
{
	consumableHealthCounter += 1;

	if (consumableHealthCounter >= GetRandomValue(240, 360)) {

		// Si el personaje tiene menos de la mitad de vida
		// Y además no hemos spawneado otra pocion

		if (character->GetNormalizedHealth() < 0.5f && consumableQuantity == 0) {

			SpawnConsumable(I_POTION_HEALTH);
			consumableHealthCounter = 0;

		}
	}

	consumableSpeedCounter += 1;

	if (consumableSpeedCounter >= GetRandomValue(640, 1060)) {

		// Si hay más de 10 enemigos
		// Y además no hemos spawneado otra pocion

		if (enemyQuantity > 10 && consumableQuantity == 0) {

			SpawnConsumable(I_POTION_SPEED);
			consumableSpeedCounter = 0;

		}
	}

	for (int i = 0; i < consumableQuantity; i++) {

		consumables[i].Draw();

		if (consumables[i].GetGrabbed()) DeleteConsumable(i);

	}
}

void AIController::SpawnInteractables()
{
	if (interactableSpawnedQuantity < necessaryKeys)
		interactableTimer += 1.f;

	if (
		interactableSpawnedQuantity < necessaryKeys &&
		interactableTimer > 300
		) {

		interactableTimer = 0;

		for (int i = 0; i < enemyQuantitySpawned; i++) {

			if (enemies[i]->GetIsExploding()) {

				interactableSpawnedQuantity += 1;

				for (int i = 0; i < interactableQuantity; i++) {
					interactables[i] = Interactable(enemies[i]->GetPosition(), I_KEY, character);
				}
			}
		}

	}

	for (int i = 0; i < interactableSpawnedQuantity; i++) {

		if (interactables[i].GetGrabbed()) {
			interactables[i].Restart();
			interactableSpawnedQuantity--;
		}
		else interactables[i].Draw();

	}

}

void AIController::ClearAll() {

	DeleteEnemies();
	DeleteConsumables();
	DeleteInteractables();

}

void AIController::DeleteConsumables() {

	consumables = nullptr;
	consumableQuantity = 0;

}

void AIController::DeleteConsumable(int indexToDelete)
{

	int newQuantity = consumableQuantity - 1;
	Consumable* newConsumables = new Consumable[newQuantity];

	for (int i = 0; i < newQuantity; i++) {

		if (i > indexToDelete) newConsumables[i - 1] = consumables[i];
		else if (i < indexToDelete) newConsumables[i] = consumables[i];

	}

	consumables = newConsumables;
	consumableQuantity = newQuantity;

}

void AIController::DeleteInteractables()
{
	interactableSpawnedQuantity = 0;
}

void AIController::Play()
{
	SpawnEnemies();
	SpawnInteractables();
	SpawnConsumables();
}
