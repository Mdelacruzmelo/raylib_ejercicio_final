#include "Character.h"

Character::Character()
{
}

void Character::Draw() {
	DrawRectangle(
		pos.x - radius,
		pos.y - radius,
		size,
		size,
		WHITE
	);
}

void Character::Move(Vector2 movement)
{
	// velocity va del 1 al 10, me interesa dividirlo entre 10 para obtener decimales
	// al resultado de la division le sumo 1, para que la velocidad
	// de calculo sea 1 + 0.1 -> 1.1 ---- 1 + 0.2 -> 1.2 ---
	// Asi sucesivamente hasta el 1 + (10 / 10)  = 1 + 1 = 2 
	// velocidad maxima es el doble

	pos = Vector2{
		pos.x + ((1 + velocity / 10) * acceleration * movement.x),
		pos.y + ((1 + velocity / 10) * acceleration * movement.y)
	};
}

void Character::Attack(Vector2 endVector) {

	Vector2 circle1Center = { (endVector.x + pos.x) / 2,(endVector.y + pos.y) / 2 };
	DrawCircle(circle1Center.x, circle1Center.y, 30.f, RED);

	Vector2 circle2Center = { endVector.x, endVector.y };
	DrawCircle(circle2Center.x, circle2Center.y, 20.f, RED);

	// Todo, mirar cuando se ataca, con qué intersectan los circulos para afectar al objetivo del ataque

}

float Character::GetAttack()
{
	return attack;
}

float Character::GetDefense()
{
	return defense;
}

float Character::GetEnergy()
{
	return energy;
}

float Character::GetSpeed()
{
	return velocity;
}

int Character::GetAbPoints()
{
	return abilityPoints;
}

void Character::AddAbPoints(int add)
{
	abilityPoints += add;
}

void Character::SubstractAbPoints(int substract)
{
	abilityPoints -= substract;
}

Rectangle Character::GetRect()
{
	return Rectangle{ pos.x - (size / 2), pos.y - (size / 2), size, size };
}

Vector2 Character::GetSize()
{
	return Vector2{ size, size };
}

int Character::GetLevel()
{
	return level;
}

float Character::GetNormalizedHealth()
{
	return health / maxHealth;
}

float Character::GetNormalizedExperience()
{
	return experience / maxExperience;
}

float Character::GetAttackDistance()
{
	return attackDistance;
}

void Character::SetIsInteracting(bool isInteractingInput)
{
	isInteracting = isInteractingInput;
}

bool Character::GetIsInteracting()
{
	return isInteracting;
}

void Character::SetDoorTargetId(char* doorTargetIdInput)
{
	doorTargetId = doorTargetIdInput;
}

bool Character::GetIsTransporting()
{
	return isTransporting;
}

void Character::SetIsTransporting(bool isTransportingInput)
{
	isTransporting = isTransportingInput;
}

char* Character::GetDoorTargetId()
{
	return doorTargetId;
}

void Character::SetPosition(Vector2 newPos)
{
	pos = newPos;
}

void Character::AddHealth(float healthAdded)
{
	health += healthAdded;
}

void Character::ApplyDamage(float damage)
{
	health -= damage;
	if (health < 0) health = 0.f;
}

// Decrease

bool Character::IsSubstractAbility(int abNumber) {
	return
		(abNumber * -1) == 1 ||
		(abNumber * -1) == 2 ||
		(abNumber * -1) == 3 ||
		(abNumber * -1) == 4 ||
		(abNumber * -1) == 5;
}

void Character::DecreaseAbility(E_AbilityType abType)
{
	if ((abType * -1) == ATTACK) DecreaseAttack();
	if ((abType * -1) == DEFENSE) DecreaseDefense();
	if ((abType * -1) == VELOCITY)DecreaseVelocity();
	if ((abType * -1) == ENERGY) DecreaseEnergy();
	if ((abType * -1) == ATTACK_DISTANCE) DecreaseAttackDistance();
}

void Character::DecreaseAttack()
{
	attack -= 1.f;
}

void Character::DecreaseDefense()
{
	defense -= 1.f;
}

void Character::DecreaseVelocity()
{
	velocity -= 1.f;
}

void Character::DecreaseEnergy()
{
	energy -= 1.f;
}


void Character::DecreaseAttackDistance()
{
	attackDistance -= 1.f;
}


// Increases

bool Character::IsAddAbility(int abNumber) {
	return
		abNumber == 1 ||
		abNumber == 2 ||
		abNumber == 3 ||
		abNumber == 4 ||
		abNumber == 5;
}

void Character::IncreaseAbility(E_AbilityType abType)
{
	if (abType == ATTACK) IncreaseAttack();
	if (abType == DEFENSE) IncreaseDefense();
	if (abType == VELOCITY)IncreaseVelocity();
	if (abType == ENERGY) IncreaseEnergy();
	if (abType == ATTACK_DISTANCE) IncreaseAttackDistance();
}

void Character::IncreaseAttack()
{
	attack += 1.f;
}

void Character::IncreaseDefense()
{
	defense += 1.f;
}

void Character::IncreaseVelocity()
{
	velocity += 1.f;
}

void Character::IncreaseEnergy()
{
	energy += 1.f;
}


void Character::IncreaseAttackDistance()
{
	attackDistance += 1.f;
}


void Character::IncreaseExperience()
{
	experience += 2.f;
	if (experience >= maxExperience) {
		experience = 0;
		level = 2;
		AddAbPoints(1);
	}
}

int Character::GetInventorySize()
{
	return inventorySize;
}

int* Character::GetInventory()
{
	return inventory;
}

void Character::AddToInventory(E_ItemType item)
{
	for (int i = 0; i < inventorySize; i++) {

		if (inventory[i] == 0) {

			inventory[i] = item;
			return;

		}
	}
}

bool Character::IsInventorySpaceAvailable()
{
	bool freeSpace = false;

	for (int i = 0; i < inventorySize; i++) {

		if (inventory[i] == 0) {
			return true;
		}
	}
	return freeSpace;
}

Vector2 Character::GetPosition()
{
	return pos;
}
