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
	void SetTexturesLength(int textureLengthInput);
	void SetTextures(Texture2D* texturesInput);
	bool GetIsDestroyed();

private:

	bool arrivedToLoc = false;
	bool isExploding = false;
	bool destroyed = false;
	float explosionRadius = size / 1.5f;
	float explosionOpacity = 1;

	int textureLength;
	Texture2D* textures;
	int textureCounter = 0;

	Interactable* key = nullptr;
	Character* character = nullptr;
	Vector2 targetLoc = Vector2{ 0.f, 0.f };

};
