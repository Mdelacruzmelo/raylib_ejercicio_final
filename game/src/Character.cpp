#include "Character.h"

Character::Character()
{
}

void Character::Draw() {

	Draw(WHITE);

}

void Character::Draw(Color colorInput) {

	rec = Rectangle{ pos.x - radius, pos.y - radius, size, size };

	if (alive) {

		DrawRectangleRec(rec, colorInput);

		if (isVelocityTempIncreased) DrawVelocityTempBar();

		if (showingNoSpaceMessage) DrawMessageNoSpace();
	}
}

void Character::DrawMessageNoSpace() {

	counterNoSpaceMessage += 1;

	DrawText("No more space", 250, 20, 24, WHITE);

	if (counterNoSpaceMessage >= 100) {

		showingNoSpaceMessage = false;
		counterNoSpaceMessage = 0;

	}

}

void Character::DrawVelocityTempBar() {

	// Dibujar barra de velocidad

	int addedX = 10;
	int tempVelocityBarWidth = size + (addedX * 2);
	int velMarginTop = 10;
	int startX = pos.x - radius - addedX;
	int startY = pos.y - size + velMarginTop;

	DrawText("SPEED +", startX, startY - 20, 14, BLUE);
	DrawRectangle(startX, startY, tempVelocityBarWidth, 5, GRAY);
	DrawRectangle(startX, startY, tempVelocityBarWidth * GetNormalizedIncreasedVelocity(), 5, BLUE);

	tempVelocityCounter -= 1;

	// DrawText(TextFormat("counter: %d", tempVelocityCounter), 400, 300, 50, RED);
	// DrawText(TextFormat("counter: %d", initialTempVelocityCounter), 400, 350, 50, RED);
	// DrawText(TextFormat("normalized: %f", GetNormalizedIncreasedVelocity()), 400, 400, 50, RED);

	if (tempVelocityCounter <= 0) RestoreVelocity();
}

void Character::ReinitializeAttackCircles() {

	// Reinitialize circle attacks

	circle1Center = { 0.f, 0.f };
	circle1Radius = 0.f;
	circle2Center = { 0.f, 0.f };
	circle2Radius = 0.f;
}

bool Character::GetIsAlive()
{
	return alive;
}

void Character::Die()
{
	alive = false;
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

	circle1Center = { (endVector.x + pos.x) / 2,(endVector.y + pos.y) / 2 };
	circle1Radius = 30.f;

	DrawCircle(circle1Center.x, circle1Center.y, circle1Radius, RED);

	circle2Center = { endVector.x, endVector.y };
	circle2Radius = 20.f;
	DrawCircle(circle2Center.x, circle2Center.y, circle2Radius, RED);

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
	return rec;
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

float Character::GetNormalizedIncreasedVelocity()
{
	return tempVelocityCounter / initialTempVelocityCounter;
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

void Character::IncreaseTempVelocity()
{
	isVelocityTempIncreased = true;
	velocity *= 14.5f;
}

bool Character::GetIsTempVelocityIncreased()
{
	return isVelocityTempIncreased;
}


void Character::RestoreVelocity()
{
	tempVelocityCounter = initialTempVelocityCounter;
	isVelocityTempIncreased = false;
	velocity = initialVelocity;
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
	experience += 1.f;
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

void Character::RemoveFromInventory(int numPressed)
{
	inventory[numPressed - 1] = 0;
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

void Character::ShowNoInventorySpace()
{
	showingNoSpaceMessage = true;
}


float Character::GetAttackCircleRadius1()
{
	return circle1Radius;
}

float Character::GetAttackCircleRadius2()
{
	return circle2Radius;
}

Vector2 Character::GetAttackCircleCenter1()
{
	return circle1Center;
}

Vector2 Character::GetAttackCircleCenter2()
{
	return circle2Center;
}

Vector2 Character::GetPosition()
{
	return pos;
}
