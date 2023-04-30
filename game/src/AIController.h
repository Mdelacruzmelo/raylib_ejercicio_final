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

	void InitEnemies();
	void SpawnEnemies();

	void SpawnConsumable(E_ItemType typeInput);
	void SpawnConsumables();
	void InitConsumables();

	void InitInteractables();
	void SpawnInteractables();

	void ClearAll();
	void DeleteEnemies();

	void DeleteConsumable(int indexToDelete);
	void DeleteConsumables();

	void DeleteInteractables();


private:

	Character* character = nullptr;

	int counter = 0;
	int enemyQuantity = 10;
	int enemyQuantitySpawned = 0;
	Enemy** enemies = new Enemy * [enemyQuantity];

	int consumableHealthCounter = 0;
	int consumableSpeedCounter = 0;
	int consumableQuantity = 0;
	Consumable* consumables = new Consumable[consumableQuantity];
	Texture2D pillHealthTexture;
	Texture2D pillSpeedTexture;

	int necessaryKeys = 1;
	int interactableTimer = 0;
	int interactableQuantity = 1;
	int interactableSpawnedQuantity = 0;
	Interactable* interactables = new Interactable[interactableQuantity];
	Texture2D keyTexture;

	bool keySetted = false;
	int enemyTexturesLength = 4;
	Texture2D* enemyTextures = new Texture2D[enemyTexturesLength];
	int enemyDestroyTexturesLength = 5;
	Texture2D* enemyDestroyTextures = new Texture2D[enemyDestroyTexturesLength];

	int dificulty = 0;
	int newDificulty = 0;
	int dificultyCounter = 0;


};
