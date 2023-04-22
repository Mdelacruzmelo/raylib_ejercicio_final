#pragma once
#pragma warning(disable : 4430 )

#include "raylib.h"
#include "Door.h"
#include "EnvironmentUtils.h"

class Environment
{
public:
	Environment();
	Environment(Color colorInput);

	void Draw();
	bool GetIsActivated();
	Color GetColor();
	void Activate();
	void Deactivate();
	void AddDoor(E_Side doorSide);

private:

	bool active = false;
	int doorQuantity = 0;
	Color color;
	Door* doors;

};
