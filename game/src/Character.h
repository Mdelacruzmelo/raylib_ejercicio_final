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

	float GetAttack();
	float GetAttackDistance();
	float GetDefense();
	float GetEnergy();
	float GetSpeed();

	Rectangle GetRect();
	Vector2 GetSize();
	int GetLevel();
	float GetNormalizedHealth();
	float GetNormalizedExperience();

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

	float velocity = 1.1f; // increase of 0.1f
	float maxVelocity = 2.f;

	float initialAcceleration = 4.f;
	float acceleration = 4.f;

	float size = 40.f;
	float radius = size / 2;

	float initialAttackDistance = 50.f;
	float attackDistance = 50.f;
	float maxAttackDistance = 100.f;

	float health = 70.f;
	float maxHealth = 100.f;

	float initialEnergy = 1.f;
	float energy = 1.f;
	float maxEnergy = 10.f;

	float initialAttack = 1.f;
	float attack = 1.f;
	float maxAttack = 10.f;

	float initialDefense = 1.f;
	float defense = 1.f;
	float maxDefense = 10.f;

	int level = 1;
	int habilityPoints = 10;

	float experience = 0.f;
	float maxExperience = 100.f;

	int inventorySize = 5;
	int* inventory = new int[5] {0, 0, 0, 0, 0};

	Vector2 pos = { 600.f, 540.f };

	bool isInteracting = false;
	bool isTransporting = false;
	char* doorTargetId;

};
