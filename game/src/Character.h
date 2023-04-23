#pragma once
#include "raylib.h"
#include "InventoryItemsUtils.h"
#include "AbilityUtils.h"

class Character
{
public:
	Character();

	void Draw();
	void Draw(Color colorInput);
	bool GetIsAlive();
	void Die();

	void Move(Vector2 movement);
	void Attack(Vector2 endVector);

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
	int GetAbPoints();

	float GetAttack();
	float GetAttackDistance();
	float GetDefense();
	float GetEnergy();
	float GetSpeed();

	bool IsAddAbility(int abNumber);
	bool IsSubstractAbility(int abNumber);

	void IncreaseAbility(E_AbilityType abType);
	void IncreaseAttack();
	void IncreaseDefense();
	void IncreaseVelocity();
	void IncreaseEnergy();
	void IncreaseAttackDistance();

	void DecreaseAbility(E_AbilityType abType);
	void DecreaseAttack();
	void DecreaseDefense();
	void DecreaseVelocity();
	void DecreaseEnergy();
	void DecreaseAttackDistance();

	void IncreaseExperience();
	void AddAbPoints(int add);
	void SubstractAbPoints(int substract);

	int GetInventorySize();
	int* GetInventory();
	void AddToInventory(E_ItemType item);
	bool IsInventorySpaceAvailable();

protected:

	bool alive = true;

	float velocity = 1.f;
	float maxVelocity = 10.f;

	float initialAcceleration = 4.f;
	float acceleration = 4.f;

	float size = 40.f;
	float radius = size / 2;

	float initialAttackDistance = 5.f;
	float attackDistance = 5.f;
	float maxAttackDistance = 10.f;

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
	int abilityPoints = 10;

	float experience = 20.f;
	float maxExperience = 100.f;

	int inventorySize = 5;
	int* inventory = new int[5] {0, 0, 0, 0, 0};

	Vector2 pos = { 600.f, 540.f };
	Rectangle rec = Rectangle{ pos.x - radius, pos.y - radius, size, size };

	bool isInteracting = false;
	bool isTransporting = false;
	char* doorTargetId;

};
