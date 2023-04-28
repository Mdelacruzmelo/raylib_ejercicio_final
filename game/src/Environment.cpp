#include "Environment.h"

Environment::Environment()
{
	color = DARKGRAY;
}

Environment::Environment(Color colorInput)
{
	color = colorInput;
}

void Environment::Draw(Character* characterRef)
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), color);

	// Dibujar Top doors, Y = 0.f

	float distanceXTopDoors = (float)GetScreenWidth() / (topDoorsQuantity + 1);
	for (int i = 0; i < topDoorsQuantity; i++) {
		Vector2 posTopDraw = { distanceXTopDoors * (i + 1), 0.f };
		topDoors[i].Draw(characterRef, posTopDraw);
	}

	// Dibujar Bottom doors, Y = ScreenHeight - height

	float distanceXBottomDoors = (float)GetScreenWidth() / (bottomDoorsQuantity + 1);
	for (int i = 0; i < bottomDoorsQuantity; i++) {
		Vector2 posBottomDraw = { distanceXBottomDoors * (i + 1), (GetScreenHeight() - bottomDoors[i].GetHeight()) };
		bottomDoors[i].Draw(characterRef, posBottomDraw);
	}

	// Dibujar Right doors, X = ScreenWidth - width

	float distanceYRightDoors = (float)GetScreenHeight() / (rightDoorsQuantity + 1);
	for (int i = 0; i < rightDoorsQuantity; i++) {
		Vector2 posRightDraw = { GetScreenWidth() - rightDoors[i].GetWidth(), distanceYRightDoors * (i + 1) };
		rightDoors[i].Draw(characterRef, posRightDraw);
	}

	// Dibujar Left doors, X = 0.f

	float distanceYLeftDoors = (float)GetScreenHeight() / (leftDoorsQuantity + 1);
	for (int i = 0; i < leftDoorsQuantity; i++) {
		Vector2 posLeftDraw = { 0.f, distanceYLeftDoors * (i + 1) };
		leftDoors[i].Draw(characterRef, posLeftDraw);
	}

	// DrawText(TextFormat("doors quantity %d", doorQuantity), 100, 330, 16, WHITE);

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

void Environment::AddDoor(E_Side doorSide, char* doorIdInput)
{
	// Intenté con un switch case y me salían warnings raros... 

	if (doorSide == SIDE_TOP) {

		int newTopDoorsQuantity = topDoorsQuantity + 1;
		Door* newTopDoors = new Door[newTopDoorsQuantity];

		for (int i = 0; i < newTopDoorsQuantity; i++) {
			if (i < topDoorsQuantity) newTopDoors[i] = topDoors[i];
			else newTopDoors[i] = Door(doorSide, doorIdInput);
		}

		topDoorsQuantity = newTopDoorsQuantity;
		topDoors = newTopDoors;

	}
	else if (doorSide == SIDE_BOTTOM) {

		int newBottomDoorsQuantity = bottomDoorsQuantity + 1;
		Door* newBottomDoors = new Door[newBottomDoorsQuantity];

		for (int i = 0; i < newBottomDoorsQuantity; i++) {
			if (i < bottomDoorsQuantity) newBottomDoors[i] = bottomDoors[i];
			else newBottomDoors[i] = Door(doorSide, doorIdInput);
		}

		bottomDoorsQuantity = newBottomDoorsQuantity;
		bottomDoors = newBottomDoors;

	}
	else if (doorSide == SIDE_RIGHT) {

		int newRightDoorsQuantity = rightDoorsQuantity + 1;
		Door* newRightDoors = new Door[newRightDoorsQuantity];

		for (int i = 0; i < newRightDoorsQuantity; i++) {
			if (i < rightDoorsQuantity) newRightDoors[i] = rightDoors[i];
			else newRightDoors[i] = Door(doorSide, doorIdInput);
		}

		rightDoorsQuantity = newRightDoorsQuantity;
		rightDoors = newRightDoors;

	}
	else {

		int newLeftDoorsQuantity = leftDoorsQuantity + 1;
		Door* newLeftDoors = new Door[newLeftDoorsQuantity];

		for (int i = 0; i < newLeftDoorsQuantity; i++) {
			if (i < leftDoorsQuantity) newLeftDoors[i] = leftDoors[i];
			else newLeftDoors[i] = Door(doorSide, doorIdInput);
		}

		leftDoorsQuantity = newLeftDoorsQuantity;
		leftDoors = newLeftDoors;

	}

	// Setear posiciones Top doors

	float distanceXTopDoors = (float)GetScreenWidth() / (topDoorsQuantity + 1);
	for (int i = 0; i < topDoorsQuantity; i++) {
		Vector2 posTopDraw = { distanceXTopDoors * (i + 1), 0.f };
		topDoors[i].SetPosition(posTopDraw);
	}

	// Setear posiciones Bottom doors

	float distanceXBottomDoors = (float)GetScreenWidth() / (bottomDoorsQuantity + 1);
	for (int i = 0; i < bottomDoorsQuantity; i++) {
		Vector2 posBottomDraw = { distanceXBottomDoors * (i + 1), (GetScreenHeight() - bottomDoors[i].GetHeight()) };
		bottomDoors[i].SetPosition(posBottomDraw);
	}

	// Setear posiciones Right doors

	float distanceYRightDoors = (float)GetScreenHeight() / (rightDoorsQuantity + 1);
	for (int i = 0; i < rightDoorsQuantity; i++) {
		Vector2 posRightDraw = { GetScreenWidth() - rightDoors[i].GetWidth(), distanceYRightDoors * (i + 1) };
		rightDoors[i].SetPosition(posRightDraw);
	}

	// Setear posiciones Left doors

	float distanceYLeftDoors = (float)GetScreenHeight() / (leftDoorsQuantity + 1);
	for (int i = 0; i < leftDoorsQuantity; i++) {
		Vector2 posLeftDraw = { 0.f, distanceYLeftDoors * (i + 1) };
		leftDoors[i].SetPosition(posLeftDraw);
	}


}

Door* Environment::GetDoor(char* doorIdInput)
{

	for (int i = 0; i < topDoorsQuantity; i++) {
		if (topDoors[i].GetId() == doorIdInput) {
			return &topDoors[i];
		}
	}

	for (int i = 0; i < bottomDoorsQuantity; i++) {
		if (bottomDoors[i].GetId() == doorIdInput) {
			return &bottomDoors[i];
		}
	}

	for (int i = 0; i < rightDoorsQuantity; i++) {
		if (rightDoors[i].GetId() == doorIdInput) {
			return &rightDoors[i];
		}
	}

	for (int i = 0; i < leftDoorsQuantity; i++) {
		if (leftDoors[i].GetId() == doorIdInput) {
			return &leftDoors[i];
		}
	}
}


Door* Environment::GetDoors()
{
	return doors;
}

int Environment::GetDoorQuantity()
{
	return doorQuantity;
}

int Environment::GetTopDoorQuantity()
{
	return topDoorsQuantity;
}

int Environment::GetBottomDoorQuantity()
{
	return bottomDoorsQuantity;
}

int Environment::GetRightDoorQuantity()
{
	return rightDoorsQuantity;
}

int Environment::GetLeftDoorQuantity()
{
	return leftDoorsQuantity;
}

Door* Environment::GetTopDoors()
{
	return topDoors;
}

Door* Environment::GetBottomDoors()
{
	return bottomDoors;
}

Door* Environment::GetRightDoors()
{
	return rightDoors;
}

Door* Environment::GetLeftDoors()
{
	return leftDoors;
}
