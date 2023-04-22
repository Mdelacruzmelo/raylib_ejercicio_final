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

	void Draw(Character* characterRef);
	bool GetIsActivated();
	Color GetColor();
	void Activate();
	void Deactivate();
	void AddDoor(E_Side doorSide, char* doorIdInput);
	Door* GetDoor(char* doorIdInput);
	Door* GetDoors();
	int GetDoorQuantity();

private:

	bool active = false;
	int doorQuantity = 0;
	Color color;
	Door* doors;
	char* environmentId;
};
