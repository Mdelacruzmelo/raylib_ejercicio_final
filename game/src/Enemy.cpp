#include "Enemy.h"

Enemy::Enemy()
{
}

void Enemy::SetTarget(Character* characterInput)
{
	character = characterInput;
}

void Enemy::Play()
{
	if (GetIsAlive()) {

		Draw(RED);

		// rec = Rectangle{ pos.x, pos.y, width, height };
		// DrawRectangleRec(rec, RED);

		if (character != nullptr) {

			// MoveTo(character->GetPosition());

			if (!arrivedToLoc) {

				DrawText(TextFormat("Moving X %f", 1), 200, 200, 20, RED);
				DrawText(TextFormat("Moving Y %f", 1), 200, 250, 20, RED);

				float movX = 0.f;
				if (pos.x > character->GetPosition().x) movX = -1.f;
				else if (pos.x < character->GetPosition().x) movX = 1.f;

				float movY = 0.f;
				if (pos.y > character->GetPosition().y) movY = -1.f;
				else if (pos.y < character->GetPosition().y) movY = 1.f;

				// DrawText(TextFormat("Moving X %f", movX), 200, 200, 20, RED);
				// DrawText(TextFormat("Moving Y %f", movY), 200, 250, 20, RED);

				Move(Vector2{ movX ,movY });

				// Si ya no hace falta moverte, ya llegaste

				if (movX == 0.f && movY == 0.f) arrivedToLoc = true;
			}

		}
	}
}

void Enemy::SetPosition(Vector2 posInput)
{
	this->pos = posInput;
}