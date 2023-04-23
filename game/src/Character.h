#pragma once
#include "raylib.h"
#include "InventoryItemsUtils.h"

class Character
{
public:
	Character();

	void Draw();
	void Move(Vector2 movement);
	void Attack(Vector2 endVector);

	Rectangle GetRect();
	Vector2 GetSize();
	int GetLevel();
	float GetNormalizedHealth();
	float GetNormalizedExperience();
	float GetAttackDistance();

	void SetIsInteracting(bool isInteractingInput);
	bool GetIsInteracting();

	bool GetIsTransporting();
	void SetIsTransporting(bool isTransportingInput);

	char* GetDoorTargetId();
	void SetDoorTargetId(char* doorTargetIdInput);

	Vector2 GetPosition();
	void SetPosition(Vector2 newPos);

	void AddHealth(float healthAdded);
	void ApplyDamage(float damage);
	void IncreaseSpeed();
	void IncreaseStrength();
	void IncreaseExperience();

	int GetInventorySize();
	int* GetInventory();
	void AddToInventory(E_ItemType item);
	bool IsInventorySpaceAvailable();

private:

	float velocity = 1.f;
	float initialAcceleration = 4.f;
	float acceleration = 4.f;
	float size = 40.f;
	float radius = size / 2;
	float attackDistance = 70.f;

	float health = 70.f;
	float maxHealth = 100.f;

	float initialAttack = 10.f;
	float attack = 10.f;
	float maxAttack = 100.f;

	int level = 1;

	float experience = 0.f;
	float maxExperience = 100.f;

	int inventorySize = 5;
	int* inventory = new int[5] {0, 0, 0, 0, 0};

	Vector2 pos = { 600.f, 540.f };

	bool isInteracting = false;
	bool isTransporting = false;
	char* doorTargetId;

};
