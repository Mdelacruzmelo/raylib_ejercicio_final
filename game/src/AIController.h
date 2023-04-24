#pragma once
#include "raylib.h"
#include "Character.h"
#include "Enemy.h"
#include "Consumable.h"
#include "InventoryItemsUtils.h"

class AIController
{
public:
	AIController(Character* characterInput);
	void Play();
	void SpawnEnemy();
	void DeleteEnemies();
	void DeleteEnemy(int numEnemy);
	void SpawnConsumable(E_ItemType typeInput);
	void DeleteConsumable(int indexToDelete);

private:

	Character* character = nullptr;

	int counter = 0;
	int enemyQuantity = 0;
	Enemy* enemies = new Enemy[enemyQuantity];

	int consumableHealthCounter = 0;
	int keyEnemyCounter = 0;
	int consumableSpeedCounter = 0;
	int consumableQuantity = 0;

	Consumable* consumables = new Consumable[consumableQuantity];
	bool keySetted = false;

};
