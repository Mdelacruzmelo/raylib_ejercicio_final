#include "Enemy.h"

Enemy::Enemy()
{
	texture = LoadTexture("resources/textures/police.png");
}

void Enemy::SetTarget(Character* characterInput)
{
	character = characterInput;
}

void Enemy::Play()
{
	if (GetIsAlive()) {

		Draw(texture);

		Rectangle currentRec = Rectangle{ pos.x - (size / 2), pos.y - (size / 2), size, size };

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
				character->GetAttackCircleCenter1(),
				character->GetAttackCircleRadius1(),
				currentRec
			);

			bool attackCollision2 = CheckCollisionCircleRec(
				character->GetAttackCircleCenter2(),
				character->GetAttackCircleRadius2(),
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

	if (hasKey) {

		DrawText("KEY SPAWNEDDASDASDFASDF ", 600, 800, 60, GREEN);
		key->Draw();

	}

}

void Enemy::AppendKey()
{
	hasKey = true;
}

void Enemy::SetPosition(Vector2 posInput)
{
	this->pos = posInput;
}

void Enemy::Explode()
{
	isExploding = true;

	if (hasKey) {

		key = new Interactable(pos, I_KEY, character);
		keySpawned = true;
	}

}

void Enemy::ReinitializeExplode()
{
	explosionRadius = size / 1.5f;
	explosionOpacity = 1;
}
