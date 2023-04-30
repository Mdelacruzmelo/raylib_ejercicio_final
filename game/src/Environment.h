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
	int GetTopDoorQuantity();
	int GetBottomDoorQuantity();
	int GetRightDoorQuantity();
	int GetLeftDoorQuantity();

	Door* GetTopDoors();
	Door* GetBottomDoors();
	Door* GetRightDoors();
	Door* GetLeftDoors();

private:

	bool active = false;
	int doorQuantity = 0;
	Color color;
	Door* doors;

	int topDoorsQuantity = 0;
	int bottomDoorsQuantity = 0;
	int rightDoorsQuantity = 0;
	int leftDoorsQuantity = 0;

	Door* topDoors;
	Door* bottomDoors;
	Door* rightDoors;
	Door* leftDoors;

	char* environmentId;
};
