#pragma once
#include "raylib.h"
#include "Character.h"
#include "InventoryItemsUtils.h"
#include "Interactable.h"

class Enemy : public Character
{
public:
	Enemy();

	void Play();
	void Restart();
	void SetTarget(Character* characterInput);
	void SetPosition(Vector2 posInput);
	void SetRandomPosition();
	void Explode();
	bool GetIsExploding();
	void ReinitializeExplode();
	void SetTextures(Texture2D* texturesInput, int lengthInput);
	void SetDestroyTextures(Texture2D* texturesInput, int lengthInput);
	bool GetIsDestroyed();
	void SetBloodSounds(Sound* soundsInput, int soundsInputQuantity);

private:

	bool arrivedToLoc = false;
	bool isExploding = false;
	bool destroyed = false;
	float explosionRadius = size / 1.5f;
	float explosionOpacity = 1;
	float soundVolume = 0.4;

	int textureLength;
	int destroyTextureLength;
	int textureDestroyIndex = 0;
	Texture2D* textures;
	Texture2D* destroyTextures;
	int textureCounter = 0;
	int textureDestroyCounter = 0;

	Interactable* key = nullptr;
	Character* character = nullptr;
	Vector2 targetLoc = Vector2{ 0.f, 0.f };

	Sound* bloodSounds;
	int bloodSoundsQuantity;
};
