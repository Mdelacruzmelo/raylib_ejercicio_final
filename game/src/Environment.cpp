#include "Environment.h"

Environment::Environment()
{
}

void Environment::Draw()
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), YELLOW);
}

void Environment::Activate()
{
	active = true;
}

bool Environment::GetIsActivated()
{
	return active;
}

void Environment::AddDoor(E_Side doorSide)
{
	int newDoorQuantity = doorQuantity + 1;
	Door* newDoors = new Door[newDoorQuantity];

	for (int i = 0; i < newDoorQuantity; i++) {

		if (i < doorQuantity) newDoors[i] = doors[i];
		else newDoors[i] = Door(doorSide);
	}

	doors = newDoors;
}
