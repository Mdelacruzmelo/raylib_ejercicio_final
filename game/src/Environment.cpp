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
	DrawText(TextFormat("QUANTITY %d", doorQuantity), 10, 140, 24, WHITE);

	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), color);

	// Dibujar todas las puertas

	int topDoorsQuantity = 0;
	int bottomDoorsQuantity = 0;
	int rightDoorsQuantity = 0;
	int leftDoorsQuantity = 0;

	// Cuentame las puertas segun su ubicación

	for (int i = 0; i < doorQuantity; i++) {
		switch (doors[i].GetDoorSide())
		{
		case SIDE_TOP:
			topDoorsQuantity++;
			break;
		case SIDE_BOTTOM:
			bottomDoorsQuantity++;
			break;
		case SIDE_RIGHT:
			rightDoorsQuantity++;
			break;
		case SIDE_LEFT:
		default:
			leftDoorsQuantity++;
			break;
		}
	}

	// Separa espacio en la memoria para las puertas contadas

	Door* topDoors = new Door[topDoorsQuantity];
	Door* bottomDoors = new Door[bottomDoorsQuantity];
	Door* rightDoors = new Door[rightDoorsQuantity];
	Door* leftDoors = new Door[leftDoorsQuantity];

	int topDoorsCounter = 0;
	int bottomDoorsCounter = 0;
	int rightDoorsCounter = 0;
	int leftDoorsCounter = 0;

	// Setea el array de puertas segun ubicación

	for (int i = 0; i < doorQuantity; i++) {
		switch (doors[i].GetDoorSide())
		{
		case SIDE_TOP:
			topDoors[topDoorsCounter] = doors[i];
			topDoorsCounter++;
			break;
		case SIDE_BOTTOM:
			bottomDoors[bottomDoorsCounter] = doors[i];
			bottomDoorsCounter++;
			break;
		case SIDE_RIGHT:
			rightDoors[rightDoorsCounter] = doors[i];
			rightDoorsCounter++;
			break;
		case SIDE_LEFT:
		default:
			leftDoors[leftDoorsCounter] = doors[i];
			leftDoorsCounter++;
			break;
		}
	}

	// Top doors, Y = 0.f

	float distanceXTopDoors = (float)GetScreenWidth() / (topDoorsQuantity + 1);
	for (int i = 1; i <= topDoorsQuantity; i++) {
		Vector2 posTopDraw = { distanceXTopDoors * i, 0.f };
		topDoors[i - 1].Draw(posTopDraw);
	}

	// Bottom doors, Y = ScreenHeight - height

	float distanceXBottomDoors = (float)GetScreenWidth() / (bottomDoorsQuantity + 1);
	for (int i = 1; i <= bottomDoorsQuantity; i++) {
		Vector2 posBottomDraw = { distanceXBottomDoors * i, (GetScreenHeight() - topDoors[i - 1].GetHeight()) };
		bottomDoors[i - 1].Draw(posBottomDraw);
	}

	// Right doors, X = ScreenWidth - width

	float distanceYRightDoors = (float)GetScreenHeight() / (rightDoorsQuantity + 1);
	for (int i = 1; i <= rightDoorsQuantity; i++) {
		Vector2 posRightDraw = { GetScreenWidth() - rightDoors[i - 1].GetWidth(), distanceYRightDoors * i };
		rightDoors[i - 1].Draw(posRightDraw);
	}

	// Left doors, X = 0.f

	float distanceYLeftDoors = (float)GetScreenHeight() / (leftDoorsQuantity + 1);
	DrawText(TextFormat("ENTRANDO"), 10, 240, 24, WHITE);
	DrawText(TextFormat("FOR LOOP I = %d", leftDoorsQuantity), 10, 270, 24, WHITE);
	for (int i = 1; i <= leftDoorsQuantity; i++) {
		Vector2 posLeftDraw = { 0.f, distanceYLeftDoors * i };
		DrawText(TextFormat("ENTRE"), 10, 300, 24, WHITE);
		leftDoors[i - 1].Draw(posLeftDraw);
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
		if (i < doorQuantity) newDoors[i] = doors[i];
		else newDoors[i] = Door(doorSide);
	}

	doorQuantity = newDoorQuantity;
	doors = newDoors;
}
