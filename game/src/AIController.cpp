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
				float posX = 0.f;
				float posY = 0.f;

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


				newEnemies[i].SetPosition(Vector2{ posX,posY });
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

void AIController::Play()
{

	// Enemies 
	counter += 1;

	if (counter >= GetRandomValue(40, 60)) {

		SpawnEnemy();
		counter = 0;

	}

	for (int i = 0; i < enemyQuantity; i++) {

		enemies[i].Play();

	}

}