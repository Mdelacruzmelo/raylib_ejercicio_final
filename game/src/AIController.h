#pragma once
#include "raylib.h"
#include "Character.h"
#include "Enemy.h"
#include "Consumable.h"
#include "Interactable.h"
#include "InventoryItemsUtils.h"

class AIController
{
public:
	AIController(Character* characterInput);
	void Play();
	void SpawnEnemy();

	void SpawnConsumable(E_ItemType typeInput);
	void SpawnInteractable(E_ItemType typeInput);

	void ClearAll();
	void DeleteEnemies();
	void DeleteConsumable(int indexToDelete);
	void DeleteConsumables();
	void DeleteInteractable(int indexToDelete);
	void DeleteInteractables();


private:

	Character* character = nullptr;

	int counter = 0;
	int enemyQuantity = 0;
	Enemy* enemies = new Enemy[enemyQuantity];

	int consumableHealthCounter = 0;
	int consumableSpeedCounter = 0;
	int consumableQuantity = 0;
	Consumable* consumables = new Consumable[consumableQuantity];

	int interactableCounter = 0;
	int interactableQuantity = 0;
	Interactable* interactables = new Interactable[interactableQuantity];

	bool keySetted = false;

};
