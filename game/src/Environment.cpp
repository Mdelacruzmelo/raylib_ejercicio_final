#include "Door.h"
#include "Environment.h"

Environment::Environment()
{
	color = DARKGRAY;
}

Environment::Environment(Color colorInput)
{
	color = colorInput;
}

void Environment::Draw()
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), color);

	// Dibujar todas las puertas

	int topDoorsQuantity = 0;
	Door* topDoors;

	int bottomDoorsQuantity = 0;
	Door* bottomDoors;

	int rightDoorsQuantity = 0;
	Door* rightDoors;

	int leftDoorsQuantity = 0;

	Door* leftDoors;

	// Cuentame las puertas segun su ubicación
	Door* doors = new Door[doorQuantity];

	for (int i = 0; i < doorQuantity; i++) {
		switch (doors[i].GetDoorSide())
		{
		case SIDE_TOP:
			topDoors[topDoorsQuantity] = doors[i];
			topDoorsQuantity++;
			break;
		case SIDE_BOTTOM:
			bottomDoors[bottomDoorsQuantity] = doors[i];
			bottomDoorsQuantity++;
			break;
		case SIDE_RIGHT:
			rightDoors[rightDoorsQuantity] = doors[i];
			rightDoorsQuantity++;
			break;
		case SIDE_LEFT:
		default:
			leftDoors[leftDoorsQuantity] = doors[i];
			leftDoorsQuantity++;
			break;
		}
	}

	// Top doors, Y = 0.f

	float distanceXTopDoors = (float)GetScreenWidth() / (topDoorsQuantity + 1);
	for (int i = 1; i <= topDoorsQuantity; i++) {
		Vector2 posTopDraw = { distanceXTopDoors * i, 0.f };
		topDoors[i].Draw(posTopDraw);
	}

	// Bottom doors, Y = ScreenHeight - height

	float distanceXBottomDoors = (float)GetScreenWidth() / (bottomDoorsQuantity + 1);
	for (int i = 1; i <= bottomDoorsQuantity; i++) {
		Vector2 posBottomDraw = { distanceXBottomDoors * i, (GetScreenHeight() - topDoors[i].GetHeight()) };
		bottomDoors[i].Draw(posBottomDraw);
	}

	// Right doors, X = ScreenWidth - width

	float distanceYRightDoors = (float)GetScreenHeight() / (rightDoorsQuantity + 1);
	for (int i = 1; i <= rightDoorsQuantity; i++) {
		Vector2 posRightDraw = { GetScreenWidth() - rightDoors[i].GetWidth(), distanceYRightDoors * i };
		rightDoors[i].Draw(posRightDraw);
	}

	// Left doors, X = 0.f

	float distanceYLeftDoors = (float)GetScreenHeight() / (leftDoorsQuantity + 1);
	for (int i = 1; i <= leftDoorsQuantity; i++) {
		Vector2 posLeftDraw = { 0.f, distanceYLeftDoors * i };
		leftDoors[i].Draw(posLeftDraw);
	}

}

void Environment::Activate()
{
	active = true;
}

void Environment::Deactivate()
{
	active = false;
}

bool Environment::GetIsActivated()
{
	return active;
}

Color Environment::GetColor()
{
	return color;
}

void Environment::AddDoor(E_Side doorSide)
{
	int newDoorQuantity = doorQuantity + 1;
	Door* newDoors = new Door[newDoorQuantity];

	for (int i = 0; i < newDoorQuantity; i++) {
		// if (i < doorQuantity) newDoors[i] = doors[i];
		// else newDoors[i] = Door(doorSide, this);
	}

	// doors = newDoors;
}
