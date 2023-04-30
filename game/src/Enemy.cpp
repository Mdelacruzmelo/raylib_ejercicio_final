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

			soundVolume = 0.2f;
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

				if (CheckCollisionRecs(currentRec, character->GetRect())) {

					arrivedToLoc = true;
					alive = false;
					Explode();
					character->ApplyDamage(10.f);
					character->PlayHurtSound();
					character->SetIsJustHurt(true);
				}

			}

			bool bullet1Collision = CheckCollisionCircleRec(
				character->GetAttackCircleCenter1(),
				character->GetAttackCircleRadius1(),
				currentRec
			);

			bool bullet2Collision = CheckCollisionCircleRec(
				character->GetAttackCircleCenter2(),
				character->GetAttackCircleRadius2(),
				currentRec
			);

			if (bullet1Collision || bullet2Collision) {
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

			if (destroyTextures) {

				textureDestroyCounter += 1;

				if (textureDestroyCounter % 4 == 0)
					textureDestroyIndex++;

				if (textureDestroyIndex < destroyTextureLength)
					Draw(destroyTextures[textureDestroyIndex]);

			}
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
	textureCounter = 0;
	textureDestroyCounter = 0;
	destroyed = false;
	isExploding = false;
	alive = true;
	arrivedToLoc = false;
	explosionOpacity = 1;
	explosionRadius = size / 1.5f;
	SetRandomPosition();
	textureDestroyIndex = 0;
}

void Enemy::Explode()
{
	isExploding = true;
	alive = false;

	if (dieSounds) {

		int randomSoundIndex = GetRandomValue(0, dieSoundsQuantity - 1);
		SetSoundVolume(dieSounds[randomSoundIndex], 0.1f);
		PlaySound(dieSounds[randomSoundIndex]);

	}

	if (bloodSounds) {

		int randomBloodSoundIndex = GetRandomValue(0, bloodSoundsQuantity - 1);
		SetSoundVolume(bloodSounds[randomBloodSoundIndex], 1.f);
		PlaySound(bloodSounds[randomBloodSoundIndex]);
	}

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

void Enemy::SetTextures(Texture2D* texturesInput, int textureLengthInput)
{
	textures = texturesInput;
	textureLength = textureLengthInput;
}

void Enemy::SetDestroyTextures(Texture2D* destroyTexturesInput, int textureLengthInput)
{
	destroyTextures = destroyTexturesInput;
	destroyTextureLength = textureLengthInput;
}

bool Enemy::GetIsDestroyed()
{
	return destroyed;
}

void Enemy::SetBloodSounds(Sound* soundsInput, int soundsInputQuantity)
{
	bloodSounds = soundsInput;
	bloodSoundsQuantity = soundsInputQuantity;
}
