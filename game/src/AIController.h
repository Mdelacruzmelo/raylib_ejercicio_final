#pragma once
#include "raylib.h"
#include "Character.h"
#include "Enemy.h"

class AIController
{
public:
	AIController(Character* characterInput);
	void Play();
	void SpawnEnemy();

private:
	int enemyQuantity = 0;
	Enemy* enemies = new Enemy[enemyQuantity];
	Character* character = nullptr;
	int counter = 0;

};