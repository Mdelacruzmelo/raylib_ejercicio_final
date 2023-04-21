#pragma once
#include "raylib.h"
#include "EnvironmentUtils.h"
#include "Door.h"

class Environment
{
public:
	Environment();

	void Draw();
	bool GetIsActivated();
	void Activate();
	void AddDoor(E_Side doorSide);

private:

	bool active = false;
	int doorQuantity = 0;
	Door* doors = new Door[doorQuantity];

};
