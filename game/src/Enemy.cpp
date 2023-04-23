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

		Rectangle currentRec = Rectangle{ pos.x - (size / 2), pos.y - (size / 2), size, size };

		// Obtener radios de ataque y guardarlos para más adelante 

		Vector2 characterCircle1Center = character->GetAttackCircleCenter1();
		float characterCircle1Radius = character->GetAttackCircleRadius1();

		Vector2 characterCircle2Center = character->GetAttackCircleCenter2();
		float characterCircle2Radius = character->GetAttackCircleRadius2();

		// rec = Rectangle{ pos.x, pos.y, width, height };
		// DrawRectangleRec(rec, RED);

		if (character != nullptr) {

			// MoveTo(character->GetPosition());

			if (!arrivedToLoc && !isExploding) {

				float movX = 0.f;
				if (pos.x > character->GetPosition().x) movX = -1.f;
				else if (pos.x < character->GetPosition().x) movX = 1.f;

				float movY = 0.f;
				if (pos.y > character->GetPosition().y) movY = -1.f;
				else if (pos.y < character->GetPosition().y) movY = 1.f;

				Move(Vector2{ movX ,movY });

				bool collision = CheckCollisionRecs(currentRec, character->GetRect());

				if (collision) {

					arrivedToLoc = true;
					alive = false;
					Explode();
					character->ApplyDamage(10.f);

				}

			}

			bool attackCollision1 = CheckCollisionCircleRec(
				characterCircle1Center,
				characterCircle1Radius,
				currentRec
			);


			bool attackCollision2 = CheckCollisionCircleRec(
				characterCircle2Center,
				characterCircle2Radius,
				currentRec
			);


			if (attackCollision1 || attackCollision2) {
				Explode();
				character->IncreaseExperience();
				alive = false;
				arrivedToLoc = true;
			}

		}
	}
	else if (isExploding && !destroyed) {

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
		else destroyed = true;

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

void Enemy::ReinitializeExplode()
{
	explosionRadius = size / 1.5f;
	explosionOpacity = 1;
}
