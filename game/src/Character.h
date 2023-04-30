#pragma once
#include "raylib.h"
#include "InventoryItemsUtils.h"
#include "Utils.h"

class Character
{
public:
	Character();

	void Draw();
	void Draw(Color colorInput);
	void DrawVelocityTempBar();
	bool GetIsAlive();
	void Die();
	void ReinitializeAttackCircles();

	void Move(Vector2 movement);
	void Attack(Vector2 endVector);

	Rectangle GetRect();
	Rectangle GetCollisionRect();
	Vector2 GetSize();
	int GetLevel();

	float GetNormalizedIncreasedVelocity();

	float GetExperience();
	float GetNormalizedExperience();

	void SetIsInteracting(bool isInteractingInput);
	bool GetIsInteracting();

	bool GetIsTransporting();
	void SetIsTransporting(bool isTransportingInput);

	char* GetDoorTargetId();
	void SetDoorTargetId(char* doorTargetIdInput);

	Vector2 GetPosition();
	void SetPosition(Vector2 newPos);

	void SetAngle(float newAngle);

	void AddHealth(float healthAdded);
	void ApplyDamage(float damage);
	int GetAbPoints();

	float GetAttack();
	float GetAttackDistance();

	float GetDefense();
	float GetNormalizedDefense();

	float GetSpeed();

	float GetEnergy();

	float GetHealth();
	float GetNormalizedHealth();

	float GetShield();
	float GetNormalizedShield();

	bool IsAddAbility(int abNumber);
	bool IsSubstractAbility(int abNumber);

	void IncreaseAbility(E_AbilityType abType);
	void IncreaseAttack();
	void IncreaseDefense();
	void IncreaseTempVelocity();
	bool GetIsTempVelocityIncreased();
	void RestoreVelocity();
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

	void SetEnvironment(int envInput);
	int GetEnvironment();

	void AddToInventory(E_ItemType item);
	void RemoveFromInventory(int numPressed);
	void ShowNoInventorySpace();
	void DrawMessageNoSpace();
	bool IsInventorySpaceAvailable();
	void UseKeyInventory();
	bool HasKey();

	float GetAttackCircleRadius1();
	float GetAttackCircleRadius2();
	Vector2 GetAttackCircleCenter1();
	Vector2 GetAttackCircleCenter2();

	void SetData(SavedData data);
	void SetInitialData();

	void SetIsLoadingData(bool loadingInput);
	bool GetIsLoadingData();

	int GetLoadedEnvironment();
	char* GetLoadedDoorsData();
	void SetLoadedDoorsData(char* doorsData);

	bool GetIsInNewGame();
	void SetIsInNewGame(bool isNewGameInput);

protected:

	bool alive = true;

	bool showingNoSpaceMessage = false;
	int counterNoSpaceMessage = 0;

	float initialTempVelocityCounter = 300;
	float tempVelocityCounter = 300;
	bool isVelocityTempIncreased = false;

	float initialVelocity = 1.f;
	float velocity = initialVelocity;
	float maxVelocity = 10.f;

	float initialAcceleration = 4.f;
	float acceleration = 4.f;

	float size = 40.f;
	float radius = size / 2;
	float sizeCollision = size * 1.5;
	float radiusCollision = sizeCollision / 2;

	float initialAttackDistance = 5.f;
	float attackDistance = initialAttackDistance;
	float maxAttackDistance = 10.f;

	float initialHealth = 20.f;
	float health = initialHealth;
	float maxHealth = 100.f;

	float initialEnergy = 1.f;
	float energy = initialEnergy;
	float maxEnergy = 10.f;

	float initialAttack = 1.f;
	float attack = initialAttack;
	float maxAttack = 10.f;

	float initialDefense = 1.f;
	float defense = initialDefense;
	float maxDefense = 10.f;

	float initialShield = 50.f;
	float shield = initialShield;
	float maxShield = 50.f;

	int initialLevel = 1;
	int level = initialLevel;

	int initialAbilityPoints = 3;
	int abilityPoints = initialAbilityPoints;

	float initialExperience = 0.f;
	float experience = initialExperience;
	float maxExperience = 100.f;

	int inventorySize = 5;
	int* inventory = new int[5] {0, 0, 0, 0, 0};

	char* loadedDoorsData;
	int loadedEnvironment = 0;
	bool isLoadingEnvironment = false;
	bool isLoadingDoors = false;
	bool isLoadingData = false;

	Vector2 initialPos = { 600.f, 540.f };
	Vector2 pos = initialPos;
	Rectangle rec = Rectangle{ pos.x - radius, pos.y - radius, size, size };
	Rectangle collisionRec = Rectangle{ pos.x - radius, pos.y - radius, size, size };

	Vector2 circle1Center;
	float circle1Radius = 0.f;

	Vector2 circle2Center;
	float circle2Radius = 0.f;

	bool isInteracting = false;
	bool isTransporting = false;
	char* doorTargetId;

	bool updatingSlots = false;
	bool inNewGame = false;

	float angle = 0.f;
	Texture2D texture;
	int copSize = 80;
};
