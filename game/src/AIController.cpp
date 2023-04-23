#include "AIController.h"

AIController::AIController(Character* characterInput)
{
	character = characterInput;
}

void AIController::AddEnemy()
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

				float posX = 0.f;
				float posY = 0.f;

				newEnemies[i].SetPosition(Vector2{ posX,posY });
			}
		}

	}

	enemies = newEnemies;
	enemyQuantity = newEnemyQuantity;

}

void AIController::Play()
{

	for (int i = 0; i < enemyQuantity; i++) {

		enemies[i].Play();

	}

}