#include "AIController.h"

AIController::AIController(Character* characterInput)
{
	character = characterInput;
}

void AIController::SpawnEnemy()
{
	int newEnemyQuantity = enemyQuantity + 1;
	Enemy* newEnemies = new Enemy[newEnemyQuantity];

	for (int i = 0; i < newEnemyQuantity; i++) {

		if (i < enemyQuantity) {

			newEnemies[i] = enemies[i];

		}
		else {

			newEnemies[i] = Enemy();

			if (character != nullptr) {

				newEnemies[i].SetTarget(character);

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


				newEnemies[i].SetPosition(Vector2{ posX, posY });
			}
		}

	}

	enemies = newEnemies;
	enemyQuantity = newEnemyQuantity;

}

void AIController::DeleteEnemies()
{
	enemyQuantity = 0;
	enemies = nullptr;
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

void AIController::SpawnInteractable(E_ItemType typeInput)
{
	if (character != nullptr) {

		int newQuantity = interactableQuantity + 1;
		Interactable* newInteractables = new Interactable[newQuantity];

		for (int i = 0; i < newQuantity; i++) {

			if (i < interactableQuantity) newInteractables[i] = interactables[i];
			else {

				// Si el jugador esta en la mitad izquierda de la pantalla, ponlo en la derecha y viceversa

				float spawmLocX = character->GetPosition().x;
				if (spawmLocX < GetScreenWidth() / 2) spawmLocX = GetScreenWidth() / 2 + GetRandomValue(10, 50) - GetScreenWidth() / 4;
				else spawmLocX = GetScreenWidth() / 4 - GetRandomValue(10, 50);

				// Si el jugador esta en la mitad superior de la pantalla, ponlo en la inferior y viceversa

				float spawmLocY = character->GetPosition().y;
				if (spawmLocY < GetScreenHeight() / 2) spawmLocY = GetScreenHeight() / 2 + GetRandomValue(10, 50) + GetScreenHeight() / 4;
				else spawmLocY = GetScreenHeight() / 4 - GetRandomValue(10, 50);

				if (typeInput == I_KEY) {
					spawmLocX += 100.f;
					spawmLocY -= 100.f;
				}

				newInteractables[i] = Interactable(
					Vector2{ spawmLocX, spawmLocY },
					typeInput,
					character
				);

			}
		}

		interactables = newInteractables;
		interactableQuantity = newQuantity;

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

	interactables = nullptr;
	interactableQuantity = 0;

}

void AIController::DeleteInteractable(int indexToDelete)
{
	int newQuantity = interactableQuantity - 1;
	Interactable* newInteractables = new Interactable[newQuantity];

	for (int i = 0; i < newQuantity; i++) {

		if (i > indexToDelete) newInteractables[i - 1] = interactables[i];
		else if (i < indexToDelete)	newInteractables[i] = interactables[i];

	}

	interactables = newInteractables;
	interactableQuantity = newQuantity;

}


void AIController::Play()
{

	// Enemigos 

	counter += 1;


	int minRateEnemy = 60;
	int maxRateEnemy = 90;

	// Si el personaje tiene menos de la mitad de vida

	if (character->GetNormalizedHealth() < 0.5f) {
		minRateEnemy = 140;
		maxRateEnemy = 240;
	}

	if (counter >= GetRandomValue(minRateEnemy, maxRateEnemy)) {

		// SpawnEnemy();
		counter = 0;

	}

	for (int i = 0; i < enemyQuantity; i++) enemies[i].Play();

	// Interactables

	interactableCounter += 1;

	if (interactableCounter >= GetRandomValue(20, 30)) {

		// Por cada 10 enemigos tendrás una llave
		// Y si no hay mas llaves en el campo

		if (enemyQuantity > 0 && enemyQuantity % 10 == 0 && interactableQuantity == 0) {

			SpawnInteractable(I_KEY);
			interactableCounter = 0;

		}
	}

	for (int i = 0; i < interactableQuantity; i++) {

		interactables[i].Draw();

		if (interactables[i].GetGrabbed()) DeleteInteractable(i);

	}

	// Consumibles

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