#pragma once
#pragma warning(disable : 4430 )

#include "raylib.h"
#include "Door.h"
#include "EnvironmentUtils.h"
#include "Character.h"

class Environment
{
public:
	Environment();
	Environment(Color colorInput);

	void Draw(Character* characterInput);
	bool GetIsActivated();
	Color GetColor();
	void Activate();
	void Deactivate();
	void AddDoor(E_Side doorSide, char* doorIdInput);

private:

	bool active = false;
	int doorQuantity = 0;
	Color color;
	Door* doors;
	char* environmentId;
};
