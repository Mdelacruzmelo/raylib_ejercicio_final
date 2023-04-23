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

				float movX = 0.f;
				if (pos.x > character->GetPosition().x) movX = -1.f;
				else if (pos.x < character->GetPosition().x) movX = 1.f;

				float movY = 0.f;
				if (pos.y > character->GetPosition().y) movY = -1.f;
				else if (pos.y < character->GetPosition().y) movY = 1.f;

				Move(Vector2{ movX ,movY });

				bool collision = CheckCollisionPointRec(
					Vector2{ pos.x + (size / 2), pos.y + (size / 2) },
					character->GetRect()
				);

				if (collision) {

					arrivedToLoc = true;
					alive = false;
					Explode();
					character->ApplyDamage(10.f);

				}

			}

		}
	}
	else if (isExploding) {

		static float explosionRadius = size;
		static float explosionOpacity = 1;

		if (explosionOpacity > 0) {

			explosionRadius += 0.2f;
			explosionOpacity -= 0.01f;

			DrawCircle(
				pos.x,
				pos.y,
				explosionRadius,
				Fade(RED, explosionOpacity)
			);
		}

	}
}

void Enemy::SetPosition(Vector2 posInput)
{
	this->pos = posInput;
}

void Enemy::Explode()
{
	isExploding = true;
}
