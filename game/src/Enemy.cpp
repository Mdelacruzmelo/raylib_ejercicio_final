#include "Enemy.h"

Enemy::Enemy()
{
	SetRandomPosition();
}

void Enemy::SetTarget(Character* characterInput)
{
	character = characterInput;
}

void Enemy::Play()
{
	if (GetIsAlive()) {

		if (textures) {

			textureCounter += 1;
			static int textureIndex = 0;

			if (textureCounter % 10 == 0) textureIndex++;
			if (textureIndex >= textureLength - 1) textureIndex = 0;

			Draw(textures[textureIndex]);

		}

		Rectangle currentRec = Rectangle{ pos.x - (size / 2), pos.y - (size / 2), size, size };

		if (character != nullptr) {

			if (!arrivedToLoc && !isExploding) {

				float movX = 0.f;
				if (pos.x >= character->GetPosition().x + 10) movX = -1.f;
				else if (pos.x < character->GetPosition().x) movX = 1.f;

				float movY = 0.f;
				if (pos.y >= character->GetPosition().y + 10) movY = -1.f;
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
	else if (destroyed) Restart();

}

void Enemy::SetPosition(Vector2 posInput)
{
	pos = posInput;
	initialPos = posInput;
}

void Enemy::SetRandomPosition()
{
	int randomVal = GetRandomValue(0, 3);
	float posX = 100.f;
	float posY = -100.f;

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

	SetPosition(Vector2{ posX, posY });
}

void Enemy::Restart()
{
	pos = initialPos;
	destroyed = false;
	isExploding = false;
	alive = true;
	arrivedToLoc = false;
	explosionOpacity = 1;
	explosionRadius = size / 1.5f;
	SetRandomPosition();
}

void Enemy::Explode()
{
	isExploding = true;
	alive = false;
}

bool Enemy::GetIsExploding()
{
	return isExploding;
}

void Enemy::ReinitializeExplode()
{
	explosionRadius = size / 1.5f;
	explosionOpacity = 1;
}

void Enemy::SetTexturesLength(int textureLengthInput)
{
	textureLength = textureLengthInput;
}

void Enemy::SetTextures(Texture2D* texturesInput)
{
	textures = texturesInput;
}

bool Enemy::GetIsDestroyed()
{
	return destroyed;
}
