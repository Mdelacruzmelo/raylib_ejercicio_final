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
	void AppendKey();
	void SetTarget(Character* characterInput);
	void SetPosition(Vector2 posInput);
	void Explode();
	void ReinitializeExplode();

private:

	bool arrivedToLoc = false;
	bool isExploding = false;
	bool destroyed = false;
	float explosionRadius = size / 1.5f;
	float explosionOpacity = 1;
	bool hasKey = false;
	bool keySpawned = false;

	Interactable* key = nullptr;
	Character* character = nullptr;
	Vector2 targetLoc = Vector2{ 0.f, 0.f };

};
